#include "overlays/lib/texture_scroll_channel.h"
#include "overlays/lib/transform_owner_inlines.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "sdk/main/libc_guess_00137290.h"
#include "main/heap.h"
#include "main/dma_queue.h"
#include "overlays/lib/semaphore.h"
#include "sdk/main/libdma_0012B2C8.h"
#include "sdk/main/libgraph_0012EAC8.h"
#include "sdk/main/libkernl_00121940.h"
#include "main/stream_thread.h"
#include "overlays/lib/image_capture.h"
#include "overlays/lib/palette_blend_channel.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/lib/text_0043A920.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/matrix_vu0.h"
#include "vu0.h"
#include "overlays/lib/cull_vu0.h"
#include "overlays/lib/text_00419A70.h"
#include "overlays/lib/text_0044ABE0.h"
#include "overlays/lib/quaternion_vu0.h"
#include "overlays/lib/direction_vu0.h"
#include "overlays/lib/quaternion_inlines.h"
#include "ee.h"
#include "overlays/lib/scratchpad_texture_cache.h"
#include "clamp.h"
#include "main/resident_data.h"
#include "overlays/lib/text_004DD440.h"
#include "overlays/lib/text_0046AE20.h"
#include "sdk/main/libm_guess_0013F3E0.h"
#include "include_asm.h"
#include "overlays/lib/render_buffer.h"
#include "overlays/lib/render_channel.h"
#include "overlays/lib/text_004DD440.h"
#include "overlays/lib/model.h"
#include "overlays/lib/transform_vu0.h"
#include "overlays/lib/palette_blend_vu0.h"

#define TEXTURE_TRANSFER_GIF_TAG 0x1000000000008004ULL
#define LIB_TEXTURE_TAG_MLPS 0x4D6C5073
#define LIB_TEXTURE_PRIORITY_MAX 10
#define LIB_TEXTURE_PRIORITY_MIN -10
#define LIB_TEXTURE_PRIORITY_KEEP -5
#define LIB_SCREEN_TEXT_FONT_SLOT 31
#define LIB_SCREEN_TEXT_FONT_KEY 11
#define LIB_SCREEN_TEXT_FONT_TAG 2
#define LIB_SCREEN_TEXT_FONT_PRIORITY 0x34BC0
#define LIB_SCREEN_TEXT_CELL_SIZE 16.01f
#define LIB_SCREEN_TEXT_FONT_TEX0 0x620000000ULL
#define LIB_SCREEN_TEXT_PRIM 0x356

/** Packet that sets up the GS for drawing screen text: TEX0_2, ALPHA_2, PRIM and RGBAQ in A+D form. */
struct LibScreenTextPacket
{
    GsGifTag tag;
    u64 tex0;
    u64 tex0_address;
    u64 alpha;
    u64 alpha_address;
    u64 prim;
    u64 prim_address;
    u32 rgba;
    float q;
    u64 rgbaq_address;
};

#define LIB_FRAME_PACKET_REGISTER_COUNT 11

/** Packet that resets the context-2 drawing state Lib relies on. */
struct LibFramePacket
{
    GsGifTag tag;
    GsRegisterValue registers[LIB_FRAME_PACKET_REGISTER_COUNT];
};

/** Lib's frame packet, 64 quadwords. TODO: init builds a LibPacketBuffer here, but I can only match this as a plain packet. */
extern "C" ResidentPacket D_0050CD60;

enum
{
    IMAGE_SEQUENCE_MAGIC = 0x41534946,
    IMAGE_SEQUENCE_LOOP = 0,
    IMAGE_SEQUENCE_PING_PONG = 1,
    IMAGE_SEQUENCE_CLAMP = 2
};

enum
{
    TEXTURE_TRANSFER_VIF_UNPACK = 0x6C060060,
    TEXTURE_TRANSFER_VIF_FLUSH = 0x11000000,
    TEXTURE_TRANSFER_QUADWORDS = 8,
    DMA_TAG_REFERENCE = 0x30000000,
    GS_TRANSFER_LOCAL_TO_LOCAL = 2
};

/** Offset and duration for one image in a FISA sequence. */
struct LibImageSequenceEntry
{
    u32 data_offset;
    u32 duration;
};

/** Fixed prefix followed by entry_count image-sequence entries. */
struct LibImageSequenceHeader
{
    u16 entry_count;
    u16 playback_mode;
    u32 duration;
};

extern "C" void func_004D6C20(LibUpdateList* list, void** items, u32* offsets);

extern "C" LibRenderDataRecord* func_00448910(u32 first_key, u32 second_key);

struct LibFieldPointer634
{
    u8 unk00[0x634];
    void* unk634;
};

#define HALF_PI 1.57079637050628662109375f

extern "C" ResidentDmaQueue* D_001B660C;

/**
 * @brief View an aligned matrix row as a vector.
 * @param matrix Source matrix.
 * @param index Row index.
 * @return Read-only row vector.
 */
static inline const FieldVec4A& matrix_row_vector(const LibMatrix44Value& matrix, s32 index)
{
    return *(const FieldVec4A*)matrix.m[index];
}

/**
 * @brief View an aligned matrix row as a writable vector.
 * @param matrix Destination matrix.
 * @param index Row index.
 * @return Writable row vector.
 */
static inline FieldVec4A& matrix_row_vector(LibMatrix44Value& matrix, s32 index)
{
    return *(FieldVec4A*)matrix.m[index];
}

/**
 * @brief Interpolate along the shorter quaternion arc and normalize the result.
 *
 * Same result as lib_quaternion_slerp, but the sines run on the VU0 microprogram while the CPU waits.
 * @param output Aligned destination quaternion; may alias either input.
 * @param first First aligned quaternion.
 * @param second Second aligned quaternion.
 * @param fraction Interpolation fraction.
 */
extern "C" void lib_quaternion_slerp_async(FieldVec4B* output, const FieldVec4B* first, const FieldVec4B* second, float fraction)
{
    float linear_threshold = 0.01f;
    float dot = ((first->x * second->x + first->y * second->y) + first->z * second->z) + first->w * second->w;
    float full_weight = 1.0f;
    bool negative;
    float angle;

    if (!(dot < 0.0f))
    {
        negative = false;
        angle = func_004CD010(dot);
    }
    else
    {
        negative = true;
        angle = func_004CD010(-dot);
    }

    if (angle < linear_threshold)
    {
        FieldVec4A weights;
        weights.y = fraction;
        weights.x = full_weight - fraction;

        if (negative)
        {
            vu0_quaternion_linear_negative(first, second, &weights);
        }
        else
        {
            vu0_quaternion_linear_positive(first, second, &weights);
        }
    }
    else if (negative)
    {
        func_004CD2C0(angle * (full_weight - fraction), angle * fraction, angle);
        vu0_quaternion_spherical_negative_wait(first, second);
    }
    else
    {
        func_004CD2C0(angle * (full_weight - fraction), angle * fraction, angle);
        vu0_quaternion_spherical_positive_wait(first, second);
    }

    vu0_quaternion_norm_begin();
    ee_prefetch(output);
    vu0_quaternion_norm_finish(output);
}

/**
 * @brief Convert a quaternion by mapping each matrix row from (x, y, z) to (x, -z, y).
 * @param quaternion Source quaternion.
 * @return Quaternion extracted from the converted matrix.
 */
extern "C" FieldVec4B func_004CD570(const FieldVec4B& quaternion)
{
    LibMatrix44Value source = func_004CE980(quaternion);
    LibMatrix44Value converted;
    FieldVec4B result;
    ((unsigned __int128*)&converted)[0] = 0;
    ((unsigned __int128*)&converted)[1] = 0;
    ((unsigned __int128*)&converted)[2] = 0;
    ((unsigned __int128*)&converted)[3] = 0;
    const FieldVec4A& source_row1 = matrix_row_vector(source, 1);
    FieldVec4A& row1 = matrix_row_vector(converted, 1);
    const FieldVec4A& source_row2 = matrix_row_vector(source, 2);
    FieldVec4A& row2 = matrix_row_vector(converted, 2);
    converted.m[0][0] = source.m[0][0];
    row1.x = source_row1.x;
    row2.x = source_row2.x;
    converted.m[0][1] = -source.m[0][2];
    row1.y = -source_row1.z;
    row2.y = -source_row2.z;
    converted.m[0][2] = source.m[0][1];
    row1.z = source_row1.y;
    row2.z = source_row2.y;
    converted.m[3][3] = 1.0f;
    lib_matrix_to_quaternion(&result, &converted);
    return result;
}

/**
 * @brief Interpolate along the shorter quaternion arc and normalize the result.
 * @param output Aligned destination quaternion; may alias either input.
 * @param first First aligned quaternion.
 * @param second Second aligned quaternion.
 * @param fraction Interpolation fraction.
 */
extern "C" void lib_quaternion_slerp(FieldVec4B* output, const FieldVec4B* first, const FieldVec4B* second, float fraction)
{
    float dot = ((first->x * second->x + first->y * second->y) + first->z * second->z) + first->w * second->w;
    bool negative;
    float angle;

    if (!(dot < 0.0f))
    {
        negative = false;
        angle = func_004CD010(dot);
    }
    else
    {
        negative = true;
        angle = func_004CD010(-dot);
    }

    if (angle < 0.01f)
    {
        FieldVec4A weights;
        weights.y = fraction;
        weights.x = 1.0f - fraction;

        if (negative)
        {
            vu0_quaternion_linear_negative(first, second, &weights);
        }
        else
        {
            vu0_quaternion_linear_positive(first, second, &weights);
        }
    }
    else if (negative)
    {
        FieldVec4A sines;
        func_004CA090(&sines, angle * (1.0f - fraction), angle * fraction, angle);
        vu0_quaternion_spherical_negative(first, second);
    }
    else
    {
        FieldVec4A sines;
        func_004CA090(&sines, angle * (1.0f - fraction), angle * fraction, angle);
        vu0_quaternion_spherical_positive(first, second);
    }

    vu0_quaternion_norm_begin();
    vu0_quaternion_norm_finish(output);
}

/**
 * @brief Build the unit quaternion for a rotation about an axis.
 * @param output Receives the quaternion.
 * @param axis_angle Axis in x, y and z, angle in radians in w.
 */
void lib_quaternion_from_axis_angle(FieldVec4B* output, const LibVector4* axis_angle)
{
    quaternion_from_axis_angle(output, axis_angle);
}

/**
 * @brief Normalize a quaternion in place.
 * @param quaternion Quaternion to normalize.
 */
void lib_normalize_quaternion(FieldVec4B* quaternion)
{
    normalize_quaternion(quaternion);
}

/**
 * @brief Build a quaternion's rotation matrix with the VU0 microprogram at 0x720.
 * @param quaternion Source quaternion.
 * @return Rotation matrix.
 */
static inline LibMatrix44Value quaternion_rotation_matrix(const void* quaternion)
{
    LibMatrix44Value result;
    vu0_start_microprogram_720_vf5(quaternion);
    vu0_wait_microprogram();
    vu0_store_vf8_vf11(&result);
    return result;
}

/**
 * @brief Extract rotation angles from a quaternion, through its rotation matrix.
 * @param angles Receives the angles about x, y and z.
 * @param quaternion Source quaternion.
 */
void func_004CD8C0(LibVector4* angles, const LibVector4* quaternion)
{
    LibVector4 result;
    FieldVec4B normalized(quaternion->x, quaternion->y, quaternion->z, quaternion->w);

    normalize_quaternion(&normalized);

    LibMatrix44Value matrix = quaternion_rotation_matrix(quaternion);

    result.z = -func_00142048(matrix.m[0][1]);
    float cosine = lib_cosine(result.z);

    if (cosine != 0.0f)
    {
        result.x = -func_004CD010(matrix.m[1][1] / cosine);

        if (-cosine * matrix.m[2][1] < 0.0f)
        {
            result.x = -result.x;
        }

        result.y = func_004CD010(matrix.m[0][0] / cosine);

        if (cosine * matrix.m[0][2] > 0.0f)
        {
            result.y = -result.y;
        }
    }
    else
    {
        result.x = 0.0f;
        result.y = 0.0f;
    }

    *reinterpret_cast<unsigned __int128*>(angles) = *reinterpret_cast<const unsigned __int128*>(&result);
}

/**
 * @brief Extract rotation components from a quaternion.
 * @param angles Destination rotation vector.
 * @param quaternion Source quaternion.
 */
void func_004CDA40(LibVector4* angles, const LibVector4* quaternion)
{
    LibVector4 result;
    FieldVec4B normalized(quaternion->x, quaternion->y, quaternion->z, quaternion->w);

    normalize_quaternion(&normalized);

    LibMatrix44Value matrix = quaternion_rotation_matrix(quaternion);

    result.x = -func_00142048(matrix.m[1][2]);
    float cosine = lib_cosine(result.x);

    if (cosine != 0.0f)
    {
        result.z = func_004CD010(matrix.m[1][1] / cosine);

        if (-cosine * matrix.m[1][0] < 0.0f)
        {
            result.z = -result.z;
        }

        result.y = func_004CD010(matrix.m[2][2] / cosine);

        if (cosine * matrix.m[2][0] > 0.0f)
        {
            result.y = -result.y;
        }
    }
    else
    {
        result.y = 0.0f;
        result.z = 0.0f;
    }

    *reinterpret_cast<unsigned __int128*>(angles) = *reinterpret_cast<const unsigned __int128*>(&result);
}

/**
 * @brief Build the unit quaternion for three rotation angles about the positive axes: the product (y * x) * z of the
 *        three rotations, normalized.
 * @param orientation Receives the quaternion.
 * @param angles Angles in radians about x, y and z.
 */
extern "C" void func_004CDBC0(LibVector4* orientation, const LibVector4* angles)
{
    LibVector4 x_axis;
    LibVector4 y_axis;
    LibVector4 z_axis;
    FieldVec4B x_rotation;
    FieldVec4B y_rotation;
    FieldVec4B z_rotation;
    FieldVec4B rotation;

    set_vector(&x_axis, 1.0f, 0.0f, 0.0f, angles->x);
    set_vector(&y_axis, 0.0f, 1.0f, 0.0f, angles->y);
    set_vector(&z_axis, 0.0f, 0.0f, 1.0f, angles->z);
    quaternion_from_axis_angle(&x_rotation, &x_axis);
    quaternion_from_axis_angle(&y_rotation, &y_axis);
    quaternion_from_axis_angle(&z_rotation, &z_axis);
    rotation = multiply_rotations(y_rotation, x_rotation);
    rotation = multiply_rotations(rotation, z_rotation);
    normalize_quaternion(&rotation);
    *reinterpret_cast<FieldVec4B*>(orientation) = rotation;
}

/**
 * @brief Build the unit quaternion for three rotation angles about the negative axes: the product (y * z) * x of the
 *        three rotations, normalized.
 * @param output Receives the quaternion.
 * @param angles Angles in radians about x, y and z.
 */
extern "C" void func_004CE040(LibVector4* output, const LibVector4* angles)
{
    LibVector4 x_axis;
    LibVector4 y_axis;
    LibVector4 z_axis;
    FieldVec4B x_rotation;
    FieldVec4B y_rotation;
    FieldVec4B z_rotation;
    FieldVec4B rotation;

    set_vector(&x_axis, -1.0f, 0.0f, 0.0f, angles->x);
    set_vector(&y_axis, 0.0f, -1.0f, 0.0f, angles->y);
    set_vector(&z_axis, 0.0f, 0.0f, -1.0f, angles->z);
    quaternion_from_axis_angle(&x_rotation, &x_axis);
    quaternion_from_axis_angle(&y_rotation, &y_axis);
    quaternion_from_axis_angle(&z_rotation, &z_axis);
    rotation = multiply_rotations(y_rotation, z_rotation);
    rotation = multiply_rotations(rotation, x_rotation);
    normalize_quaternion(&rotation);
    *reinterpret_cast<FieldVec4B*>(output) = rotation;
}

/**
 * @brief Build the unit quaternion for three rotation angles.
 *
 * The x and y angles turn about the negative axes and z about the positive axis. The result is the product
 * z * (x * y) of the three rotations, normalized.
 * @param output Receives the quaternion.
 * @param angles Angles in radians about x, y and z.
 */
void lib_quaternion_from_euler(FieldVec4B* output, const float* angles)
{
    LibVector4 x_axis;
    LibVector4 y_axis;
    LibVector4 z_axis;
    FieldVec4B x_rotation;
    FieldVec4B y_rotation;
    FieldVec4B z_rotation;
    FieldVec4B rotation;

    set_vector(&x_axis, -1.0f, 0.0f, 0.0f, angles[0]);
    set_vector(&y_axis, 0.0f, -1.0f, 0.0f, angles[1]);
    set_vector(&z_axis, 0.0f, 0.0f, 1.0f, angles[2]);
    quaternion_from_axis_angle(&x_rotation, &x_axis);
    quaternion_from_axis_angle(&y_rotation, &y_axis);
    quaternion_from_axis_angle(&z_rotation, &z_axis);
    rotation = multiply_rotations(x_rotation, y_rotation);
    *output = multiply_rotations(z_rotation, rotation);
    normalize_quaternion(output);
}

/**
 * @brief Build a quaternion's rotation matrix with the VU0 microprogram at 0x720.
 * @param quaternion Source quaternion.
 * @return Rotation matrix.
 */
LibMatrix44Value func_004CE930(const FieldVec4B& quaternion)
{
    LibMatrix44Value result;
    vu0_start_microprogram_720_vf5(&quaternion);
    vu0_wait_microprogram();
    vu0_store_vf8_vf11(&result);
    return result;
}

/**
 * @brief Build a matrix from quaternion products, retaining the quaternion's squared norm.
 * @param quaternion Quaternion components in x, y, z, w order.
 * @return Row-vector rotation matrix with the squared norm in its homogeneous diagonal.
 */
extern "C" LibMatrix44Value func_004CE980(const FieldVec4B& quaternion)
{
    LibMatrix44Value result;
    float xx = quaternion.x * quaternion.x;
    float yy = quaternion.y * quaternion.y;
    float zz = quaternion.z * quaternion.z;
    float ww = quaternion.w * quaternion.w;
    float xy = 2.0f * quaternion.x * quaternion.y;
    float wz = 2.0f * quaternion.w * quaternion.z;
    float yz = 2.0f * quaternion.y * quaternion.z;
    float wx = 2.0f * quaternion.w * quaternion.x;
    float xz = 2.0f * quaternion.x * quaternion.z;
    float wy = 2.0f * quaternion.w * quaternion.y;
    float w_plus_x = ww + xx;
    float w_minus_x = ww - xx;
    result.m[0][0] = w_plus_x - yy - zz;
    result.m[0][1] = xy + wz;
    result.m[0][2] = xz - wy;
    result.m[0][3] = 0.0f;
    FieldVec4A& row1 = matrix_row_vector(result, 1);
    row1.x = xy - wz;
    row1.y = (yy + w_minus_x) - zz;
    row1.z = yz + wx;
    row1.w = 0.0f;
    FieldVec4A& row2 = matrix_row_vector(result, 2);
    row2.x = xz + wy;
    row2.y = yz - wx;
    row2.z = zz + (w_minus_x - yy);
    row2.w = 0.0f;
    FieldVec4A& row3 = matrix_row_vector(result, 3);
    row3.x = 0.0f;
    row3.y = 0.0f;
    row3.z = 0.0f;
    row3.w = zz + (yy + w_plus_x);
    return result;
}

/**
 * @brief Add all four components to a quaternion and return its updated value.
 * @param first Quaternion to update.
 * @param second Quaternion components to add.
 * @return Copy of the updated quaternion.
 */
extern "C" FieldVec4B lib_quaternion_add_assign(FieldVec4B& first, const FieldVec4B& second)
{
    first.x = first.x + second.x;
    first.y = first.y + second.y;
    first.z = first.z + second.z;
    first.w = first.w + second.w;
    return first;
}

/**
 * @brief Multiply a quaternion by a second quaternion and return its updated value.
 * @param first Quaternion to update with first * second.
 * @param second Right-hand quaternion factor.
 * @return Copy of the updated quaternion.
 */
extern "C" FieldVec4B lib_quaternion_multiply_assign(FieldVec4B& first, const FieldVec4B& second)
{
    vu0_quaternion_multiply_assign(&first, &second);
    return first;
}

/**
 * @brief Divide a quaternion's conjugate by its squared norm.
 * @param quaternion Quaternion to invert.
 * @return Inverse quaternion.
 */
extern "C" FieldVec4B lib_quaternion_inverse(const FieldVec4B& quaternion)
{
    FieldVec4B result;
    float w = quaternion.w;
    float reciprocal_norm = 1.0f / (((quaternion.x * quaternion.x + quaternion.y * quaternion.y) + quaternion.z * quaternion.z) + w * w);
    result.w = w * reciprocal_norm;
    result.x = -quaternion.x * reciprocal_norm;
    result.y = -quaternion.y * reciprocal_norm;
    result.z = -quaternion.z * reciprocal_norm;
    return result;
}

/**
 * @brief Extract three rotation components from a matrix.
 * @param angles Destination for three floats.
 * @param matrix Transformation matrix.
 */
void func_004CEBA0(float* angles, const LibMatrix44Value* matrix)
{
    LibMatrix44Value rows;

    vu0_start_microprogram_830_matrix(matrix);
    vu0_wait_microprogram();
    vu0_store_vf1_vf4(&rows);
    angles[0] = -func_00142048(rows.m[1][2]);
    float cosine = lib_cosine(angles[0]);

    if (cosine != 0.0f)
    {
        angles[2] = func_004CD010(rows.m[1][1] / cosine);

        if (-cosine * rows.m[1][0] < 0.0f)
        {
            angles[2] = -angles[2];
        }

        angles[1] = func_004CD010(rows.m[2][2] / cosine);

        if (cosine * rows.m[2][0] > 0.0f)
        {
            angles[1] = -angles[1];
        }
    }
    else
    {
        angles[1] = 0.0f;
        angles[2] = 0.0f;
    }
}

/**
 * @brief Transpose a matrix.
 * @param input Source matrix.
 * @return Transposed matrix.
 */
LibMatrix44Value func_004CECD0(const LibMatrix44Value& input)
{
    LibMatrix44Value result;
    ee_transpose_matrix(&result, &input);
    return result;
}

/**
 * @brief Replace a position with direction angles toward a target, using the XY plane for heading.
 * @param value Source position, overwritten with elevation in x, heading in z, and w set to one.
 * @param target Target position; only x, y, and z are read.
 * @param y_angle Angle to store in the y component.
 */
extern "C" void lib_direction_angles_xy(LibVector4* value, const LibVector4* target, float y_angle)
{
    FieldVec4A delta;
    delta.x = target->x - value->x;
    delta.y = target->y - value->y;
    delta.z = target->z - value->z;
    float x_squared = delta.x * delta.x;
    float y_squared = delta.y * delta.y;

    if (x_squared == 0.0f && y_squared == 0.0f)
    {
        if (delta.z < 0.0f)
        {
            value->x = HALF_PI;
        }
        else
        {
            value->x = -HALF_PI;
        }

        value->z = 0.0f;
    }
    else
    {
        float horizontal_squared = x_squared + y_squared;
        float horizontal_distance = __sqrt(horizontal_squared, horizontal_squared);
        value->x = func_00142148(-delta.z, horizontal_distance);
        value->z = func_00142148(delta.x, delta.y);
    }

    value->y = y_angle;
    value->w = 1.0f;
}

/**
 * @brief Replace a position with direction angles toward a target, using the XZ plane for heading.
 * @param value Source position, overwritten with elevation in x, heading in y, and w set to one.
 * @param target Target position; only x, y, and z are read.
 * @param z_angle Angle to store in the z component.
 */
extern "C" void lib_direction_angles_xz(LibVector4* value, const LibVector4* target, float z_angle)
{
    float dx = target->x - value->x;
    float dy = target->y - value->y;
    float dz = target->z - value->z;
    FieldVec4A delta(dx, dy, dz, 0.0f);
    float x_squared = delta.x * delta.x;
    float z_squared = delta.z * delta.z;

    if (x_squared == 0.0f && z_squared == 0.0f)
    {
        if (delta.y < 0.0f)
        {
            value->x = HALF_PI;
        }
        else
        {
            value->x = -HALF_PI;
        }

        value->y = 0.0f;
    }
    else
    {
        float horizontal_squared = x_squared + z_squared;
        float horizontal_distance = __sqrt(horizontal_squared, horizontal_squared);
        value->x = func_00142148(-delta.y, horizontal_distance);
        value->y = func_00142148(delta.x, delta.z);
    }

    value->z = z_angle;
    value->w = 1.0f;
}

/**
 * @brief Invert an orthonormal rotation and its row-vector translation.
 * @param input Source matrix.
 * @param output Destination matrix, distinct from input.
 */
extern "C" void func_004CEF20(const LibMatrix44Value* input, LibMatrix44Value* output)
{
    ((unsigned __int128*)output)[0] = 0;
    ((unsigned __int128*)output)[1] = 0;
    ((unsigned __int128*)output)[2] = 0;
    ((unsigned __int128*)output)[3] = 0;
    output->m[0][0] = 1.0f;
    output->m[1][1] = 1.0f;
    output->m[2][2] = 1.0f;
    output->m[3][3] = 1.0f;
    s32 row;
    s32 column;

    for (row = 0; row < 3; row++)
    {
        for (column = 0; column < 3; column++)
        {
            float* output_row = output->m[row];
            const float* input_row = input->m[column];
            output_row[column] = input_row[row];
        }
    }

    vu0_inverse_translation(output, input);
}

/**
 * @brief Invert a rigid transform: transpose its rotation and rotate the negated translation back.
 * @param input Transform to invert.
 * @param output Receives the inverse.
 */
void func_004CEFD0(const LibMatrix44Value* input, LibMatrix44Value* output)
{
    LibVector4 translation;

    ((unsigned __int128*)output)[0] = 0;
    ((unsigned __int128*)output)[1] = 0;
    ((unsigned __int128*)output)[2] = 0;
    ((unsigned __int128*)output)[3] = 0;
    output->m[0][0] = 1.0f;
    output->m[1][1] = 1.0f;
    output->m[2][2] = 1.0f;
    output->m[3][3] = 1.0f;
    translation.x = input->m[0][3];
    translation.y = input->m[1][3];
    translation.z = input->m[2][3];
    vu0_rotate_translation_vf4(&translation, input);
    ee_transpose_matrix(output, input);
    vu0_store_vf4(&translation);
    matrix_row_vector(*output, 0).w = -translation.x;
    matrix_row_vector(*output, 1).w = -translation.y;
    matrix_row_vector(*output, 2).w = -translation.z;
}

/**
 * @brief Invert an orthonormal rotation and its translation column.
 * @param input Source transformation matrix.
 * @return Inverse transformation matrix.
 */
extern "C" LibMatrix44Value func_004CF0B0(const LibMatrix44Value& input)
{
    LibMatrix44Value result;
    FieldVec4B translation;
    ((unsigned __int128*)&result)[0] = 0;
    ((unsigned __int128*)&result)[1] = 0;
    ((unsigned __int128*)&result)[2] = 0;
    ((unsigned __int128*)&result)[3] = 0;
    result.m[0][0] = 1.0f;
    result.m[1][1] = 1.0f;
    result.m[2][2] = 1.0f;
    result.m[3][3] = 1.0f;

    for (s32 row = 0; row < 3; row++)
    {
        for (s32 column = 0; column < 3; column++)
        {
            float* output_row = result.m[row];
            const float* input_row = input.m[column];
            output_row[column] = input_row[row];
        }
    }

    translation.x = input.m[0][3];
    translation.y = input.m[1][3];
    translation.z = input.m[2][3];
    vu0_transform_translation(&translation, &input);
    result.m[0][3] = -translation.x;
    result.m[1][3] = -translation.y;
    result.m[2][3] = -translation.z;
    return result;
}

/**
 * @brief Invert a nonsingular matrix.
 * @param input Source matrix.
 * @param output Destination matrix, which may alias input.
 */
extern "C" void func_004CF1C0(const LibMatrix44Value* input, LibMatrix44Value* output)
{
    s32 permutation[4];
    LibMatrix44Value work;
    LibMatrix44Value scaled;
    vu0_inverse_load(input);
    permutation[0] = 0;
    vu0_inverse_maximum_row1();
    permutation[1] = 1;
    vu0_inverse_maximum_row2();
    permutation[2] = 2;
    vu0_inverse_maximum_row3();
    permutation[3] = 3;
    vu0_inverse_divide_x();
    *(FieldVec4A*)work.m[0] = matrix_row_vector(*input, 0);
    vu0_inverse_scale_row0();
    *(FieldVec4A*)work.m[1] = matrix_row_vector(*input, 1);
    vu0_inverse_scale_row1();
    vu0_inverse_store_row0(&scaled);
    *(FieldVec4A*)work.m[2] = matrix_row_vector(*input, 2);
    vu0_inverse_scale_row2();
    vu0_inverse_store_row1(&scaled);
    *(FieldVec4A*)work.m[3] = matrix_row_vector(*input, 3);
    vu0_inverse_scale_row3();
    vu0_inverse_store_row2(&scaled);
    s32 index;

    for (s32 column = 0; column < 4; column++)
    {
        float pivot_weight = -1.0f;

        for (s32 row = column; row < 4; row++)
        {
            const float* scaled_column = scaled.m[column];
            float candidate = scaled_column[permutation[row]];

            if (!(candidate <= pivot_weight))
            {
                pivot_weight = candidate;
                index = row;
            }
        }

        s32 pivot_row = permutation[index];

        if (index != column)
        {
            permutation[index] = permutation[column];
            permutation[column] = pivot_row;
        }

        s32 row;
        float* work_column = work.m[column];
        pivot_weight = 1.0f / work_column[pivot_row];

        for (row = column + 1; row < 4; row++)
        {
            s32 next_row = permutation[row];
            work_column[next_row] *= pivot_weight;
            float factor = work_column[next_row];

            for (index = column + 1; index < 4; index++)
            {
                float* work_row = work.m[index];
                work_row[next_row] -= factor * work_row[pivot_row];
            }
        }
    }

    for (s32 row = 0; row < 4; row++)
    {
        for (s32 column = 0; column < 4; column++)
        {
            s32 pivot_row = permutation[column];
            float value = (float)(pivot_row == row);

            for (s32 inner = 0; inner < column; inner++)
            {
                const float* work_row = work.m[inner];
                const float* output_row = output->m[row];
                value -= work_row[pivot_row] * output_row[inner];
            }

            output->m[row][column] = value;
        }

        for (s32 column = 3; column >= 0; column--)
        {
            float value = output->m[row][column];
            s32 pivot_row = permutation[column];

            for (s32 inner = column + 1; inner < 4; inner++)
            {
                const float* work_row = work.m[inner];
                const float* output_row = output->m[row];
                value -= work_row[pivot_row] * output_row[inner];
            }

            const float* work_row = work.m[column];
            float* output_row = output->m[row];
            output_row[column] = value / work_row[pivot_row];
        }
    }
}

/**
 * @brief Run a matrix through the VU0 microprogram at 0x2D0.
 * @param input Source matrix (vf1-vf4).
 * @return Result matrix.
 */
LibMatrix44Value func_004CF580(const LibMatrix44Value& input)
{
    LibMatrix44Value result;
    vu0_start_microprogram_2d0_vf1_vf4(&input);
    vu0_wait_microprogram();
    vu0_store_vf1_vf4(&result);
    return result;
}

/**
 * @brief Normalize the first three floating-point components in place.
 * @param value At least three components with nonzero squared length.
 */
void lib_normalize_vector3(float* value)
{
    float scale = ee_rsqrt(1.0f, value[0] * value[0] + value[1] * value[1] + value[2] * value[2]);
    value[0] *= scale;
    value[1] *= scale;
    value[2] *= scale;
}

/**
 * @brief Normalize four floating-point components in place, leaving a zero vector unchanged.
 * @param value Four components, such as a quaternion.
 */
void func_004CF640(float* value)
{
    float length = value[0] * value[0] + value[1] * value[1] + value[2] * value[2] + value[3] * value[3];

    if (length != 0.0f)
    {
        float scale = ee_rsqrt(1.0f, length);
        value[0] *= scale;
        value[1] *= scale;
        value[2] *= scale;
        value[3] *= scale;
    }
}

/**
 * @brief Multiply a matrix by a column vector.
 * @param matrix Source matrix.
 * @param value Source vector.
 * @return Transformed vector.
 */
extern "C" FieldVec4A func_004CF6C0(const LibMatrix44Value& matrix, const FieldVec4A& value)
{
    FieldVec4A result;
    result.x = matrix.m[0][0] * value.x + matrix.m[0][1] * value.y + matrix.m[0][2] * value.z + matrix.m[0][3] * value.w;
    result.y = matrix.m[1][0] * value.x + matrix.m[1][1] * value.y + matrix.m[1][2] * value.z + matrix.m[1][3] * value.w;
    result.z = matrix.m[2][0] * value.x + matrix.m[2][1] * value.y + matrix.m[2][2] * value.z + matrix.m[2][3] * value.w;
    result.w = matrix.m[3][0] * value.x + matrix.m[3][1] * value.y + matrix.m[3][2] * value.z + matrix.m[3][3] * value.w;
    return result;
}

/**
 * @brief Combine two matrices with the VU0 microprogram at 0x250.
 * @param left First matrix (vf1-vf4).
 * @param right Second matrix (vf5-vf8).
 * @return Combined matrix.
 */
LibMatrix44Value func_004CF7C0(const LibMatrix44Value& left, const LibMatrix44Value& right)
{
    LibMatrix44Value result;
    vu0_start_microprogram_250_vf1_vf8(&left, &right);
    vu0_wait_microprogram();
    vu0_store_vf1_vf4(&result);
    return result;
}

/**
 * @brief Multiply a row vector by a matrix.
 * @param value Source vector.
 * @param matrix Source matrix.
 * @return Transformed vector.
 */
extern "C" FieldVec4A func_004CF830(const FieldVec4A& value, const LibMatrix44Value& matrix)
{
    FieldVec4A result;
    result.x = value.x * matrix.m[0][0] + value.y * matrix.m[1][0] + value.z * matrix.m[2][0] + value.w * matrix.m[3][0];
    result.y = value.y * matrix.m[1][1] + value.x * matrix.m[0][1] + value.z * matrix.m[2][1] + value.w * matrix.m[3][1];
    result.z = value.y * matrix.m[1][2] + value.x * matrix.m[0][2] + value.z * matrix.m[2][2] + value.w * matrix.m[3][2];
    result.w = value.y * matrix.m[1][3] + value.x * matrix.m[0][3] + value.z * matrix.m[2][3] + value.w * matrix.m[3][3];
    return result;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CF930);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CFA30);

/**
 * @brief Compose a projection that exchanges depth and homogeneous coordinates with an inverse transform.
 * @param output Destination matrix.
 * @param input Orthonormal source transformation.
 * @param scale Projection scale, halved before division.
 * @param x_divisor Divisor for the horizontal scale.
 * @param y_divisor Divisor for the vertical scale.
 * @param x_offset Horizontal projection offset.
 * @param y_offset Vertical projection offset.
 */
extern "C" void func_004CFB20(LibMatrix44Value* output, const LibMatrix44Value& input, float scale, float x_divisor, float y_divisor,
                            float x_offset, float y_offset)
{
    LibMatrix44Value inverse = func_004CF0B0(input);
    LibMatrix44Value projection;
    ((unsigned __int128*)&projection)[0] = 0;
    ((unsigned __int128*)&projection)[1] = 0;
    ((unsigned __int128*)&projection)[2] = 0;
    ((unsigned __int128*)&projection)[3] = 0;
    projection.m[0][0] = 1.0f;
    projection.m[1][1] = 1.0f;
    projection.m[2][2] = 1.0f;
    projection.m[3][3] = 1.0f;
    projection.m[2][2] = 0.0f;
    projection.m[3][2] = 1.0f;
    projection.m[2][3] = 1.0f;
    projection.m[3][3] = 0.0f;
    projection.m[0][3] = x_offset;
    projection.m[1][3] = y_offset;
    float half_scale = 0.5f * scale;
    projection.m[0][0] = half_scale / x_divisor;
    projection.m[1][1] = half_scale / y_divisor;
    vu0_multiply_matrix(output, &projection, &inverse);
}

/**
 * @brief Compose a projection with third-column offsets with an inverse transform.
 * @param output Destination matrix.
 * @param input Orthonormal source transformation.
 * @param scale Projection scale, halved before division.
 * @param x_divisor Divisor for the horizontal scale.
 * @param y_divisor Divisor for the vertical scale.
 * @param x_offset Horizontal projection offset.
 * @param y_offset Vertical projection offset.
 */
extern "C" void func_004CFC50(LibMatrix44Value* output, const LibMatrix44Value& input, float scale, float x_divisor, float y_divisor,
                            float x_offset, float y_offset)
{
    LibMatrix44Value inverse = func_004CF0B0(input);
    LibMatrix44Value projection;
    ((unsigned __int128*)&projection)[0] = 0;
    ((unsigned __int128*)&projection)[1] = 0;
    ((unsigned __int128*)&projection)[2] = 0;
    ((unsigned __int128*)&projection)[3] = 0;
    projection.m[0][0] = 1.0f;
    projection.m[1][1] = 1.0f;
    projection.m[2][2] = 1.0f;
    projection.m[3][3] = 1.0f;
    projection.m[0][2] = x_offset;
    projection.m[1][2] = y_offset;
    float half_scale = 0.5f * scale;
    projection.m[0][0] = half_scale / x_divisor;
    projection.m[1][1] = half_scale / y_divisor;
    vu0_multiply_matrix(output, &projection, &inverse);
}

/**
 * @brief Build a perspective matrix with depth-range coefficients.
 * @param output Destination matrix.
 * @param x_scale Horizontal projection scale.
 * @param y_scale_factor Multiplier for the vertical projection scale.
 * @param x_offset Horizontal projection offset.
 * @param y_offset Vertical projection offset.
 * @param first_depth First depth-range coefficient.
 * @param second_depth Second depth-range coefficient.
 * @param near_plane Near clipping distance.
 * @param far_plane Far clipping distance.
 */
extern "C" void func_004CFD80(LibMatrix44Value* output, float x_scale, float y_scale_factor, float x_offset, float y_offset,
                            float first_depth, float second_depth, float near_plane, float far_plane)
{
    ((unsigned __int128*)output)[0] = 0;
    ((unsigned __int128*)output)[1] = 0;
    ((unsigned __int128*)output)[2] = 0;
    ((unsigned __int128*)output)[3] = 0;
    output->m[0][0] = x_scale;
    output->m[0][2] = x_offset;
    output->m[1][1] = y_scale_factor * x_scale;
    float span = far_plane - near_plane;
    output->m[1][2] = y_offset;
    output->m[2][2] = (first_depth * far_plane - second_depth * near_plane) / span;
    output->m[2][3] = (far_plane * near_plane * (second_depth - first_depth)) / span;
    output->m[3][2] = 1.0f;
}

/**
 * @brief Set the upper 3x3 rotation from three angles.
 * @param output Matrix whose rotation is updated.
 * @param angles Three rotation angles in radians.
 */
extern "C" void func_004CFDE0(LibMatrix44Value* output, const float* angles)
{
    float cosine_x = cosf_guess(angles[0]);
    float sine_x = sinf_guess(angles[0]);
    float cosine_y = cosf_guess(angles[1]);
    float sine_y = sinf_guess(angles[1]);
    float cosine_z = cosf_guess(angles[2]);
    float sine_z = sinf_guess(angles[2]);
    float sine_x_sine_y = sine_x * sine_y;
    output->m[0][0] = cosine_y * cosine_z - sine_z * sine_x_sine_y;
    output->m[1][0] = -cosine_x * sine_z;
    float cosine_y_sine_x = cosine_y * sine_x;
    output->m[2][0] = -sine_y * cosine_z - sine_z * cosine_y_sine_x;
    output->m[0][1] = cosine_y * sine_z + cosine_z * sine_x_sine_y;
    output->m[1][1] = cosine_x * cosine_z;
    output->m[2][1] = -sine_y * sine_z + cosine_z * cosine_y_sine_x;
    output->m[0][2] = cosine_x * sine_y;
    output->m[1][2] = -sine_x;
    output->m[2][2] = cosine_y * cosine_x;
}

/**
 * @brief Set the upper 3x3 rotation about the Y axis.
 * @param output Matrix whose rotation is updated.
 * @param angle Rotation angle in radians.
 */
extern "C" void func_004CFEE0(LibMatrix44Value* output, float angle)
{
    float cosine = cosf_guess(angle);
    float sine = sinf_guess(angle);
    output->m[0][0] = cosine;
    output->m[1][0] = 0.0f;
    output->m[2][0] = -sine;
    output->m[0][1] = 0.0f;
    output->m[1][1] = 1.0f;
    output->m[2][1] = 0.0f;
    output->m[0][2] = sine;
    output->m[1][2] = 0.0f;
    output->m[2][2] = cosine;
}

/** @brief Set the matrix to the identity transformation. */
void LibMatrix44Value::set_identity()
{
    ((unsigned __int128*)this)[0] = 0;
    ((unsigned __int128*)this)[1] = 0;
    ((unsigned __int128*)this)[2] = 0;
    ((unsigned __int128*)this)[3] = 0;
    m[0][0] = 1.0f;
    m[1][1] = 1.0f;
    m[2][2] = 1.0f;
    m[3][3] = 1.0f;
}

/**
 * @brief Clear all sixteen matrix components.
 * @param matrix Matrix to clear.
 */
extern "C" void func_004CFF80(LibMatrix44Value* matrix)
{
    ((unsigned __int128*)matrix)[0] = 0;
    ((unsigned __int128*)matrix)[1] = 0;
    ((unsigned __int128*)matrix)[2] = 0;
    ((unsigned __int128*)matrix)[3] = 0;
}

/**
 * @brief Copy the source transform through its virtual setters, then copy its manager and flags.
 * @param source Transform source.
 */
void LibTransformOwner::copy_transform_state(const LibTransformOwner* source)
{
    set_translation_vector(&source->translation);
    set_orientation(&source->orientation);
    set_scale_vector(&source->scale);
    display_manager = source->display_manager;
    draw_flags = source->draw_flags;
}

/** @brief Detach and queue the owner. */
void LibTransformOwner::destroy()
{
    lib_object_detach_owner(this);
    resident_enqueue_object(g_resident_release_queues, this);

    u32 mask = ~unk8c;
    u32 previous = D_001B65BC;
    unk8c &= mask;
    D_001B65BC &= mask;

    if (previous != D_001B65BC)
    {
        D_001B65C0 = 1;
    }

    unk8c = 0;
}

/** @brief Mark the base transform's matrix state ready. */
void LibTransformOwner::update_transform_matrix()
{
    matrix_ready = 1;
}

/**
 * @brief Return the base transform's null matrix pointer.
 * @return Null; the base has no matrix storage.
 */
const LibMatrix44Value* LibTransformOwner::get_transform_matrix()
{
    return 0;
}

/**
 * @brief Finish an object's packet once its DMA completes.
 *
 * If the object's packet is the one the renderer has in flight, clear that slot's busy flag and record how many timer
 * ticks it took. A main-list packet lets the packet queue start again; a bucket-list packet flags the display.
 * @param object Object whose packet completed.
 */
extern "C" void lib_finish_packet(LibTransformOwner* object)
{
    object->dma_pending = 0;
    object->unk62 = 1;

    if (object->unk65 == 0)
    {
        LibRenderer* renderer = static_cast<LibRenderer*>(g_renderer);

        if (renderer->main_packet == object)
        {
            renderer->main_packet_busy = 0;
            renderer->packet_ticks = TIMER0_COUNT - renderer->packet_start_time;
            func_004DC420(g_packet_queue, 1);
            renderer->main_packet = 0;
        }
    }
    else
    {
        LibRenderer* renderer = static_cast<LibRenderer*>(g_renderer);

        if (renderer->bucket_packet == object)
        {
            renderer->bucket_packet_busy = 0;
            renderer->packet_ticks = TIMER0_COUNT - renderer->packet_start_time;

            if (renderer->display != 0)
            {
                renderer->display->unk3E6A = 1;
            }
        }
    }
}

/**
 * @brief Report the list kind used when registration requests the default.
 * @return Sixteen.
 */
s32 LibImageRegistry::get_default_list_kind()
{
    return 16;
}

/** @brief Clear each registered resource's second state byte. */
void LibImageRegistry::update()
{
    s32 total = count;

    for (s32 i = 0; i < total; i++)
    {
        entries[i]->unk01 = 0;
    }
}

/**
 * @brief Remove a resource from the registry, keeping the rest in order.
 * @param registry Registry to search.
 * @param resource Resource to remove; nothing happens when it isn't registered.
 */
void func_004D0260(LibImageRegistry* registry, LibRenderResource* resource)
{
    for (s32 i = 0; i < registry->count; i++)
    {
        if (resource == registry->entries[i])
        {
            s32 last = registry->count - 1;

            for (; i < last; i++)
            {
                registry->entries[i] = registry->entries[i + 1];
            }

            registry->count--;
            return;
        }
    }
}

/**
 * @brief Append a resource to the registry.
 * @param registry Registry to fill.
 * @param resource Resource to add.
 * @return One, or zero when the registry is full.
 */
s32 func_004D02E0(LibImageRegistry* registry, LibRenderResource* resource)
{
    if (registry->count >= registry->capacity)
    {
        return 0;
    }

    registry->entries[registry->count++] = resource;
    return 1;
}

/** @brief Release the table, then detach from the owner. */
LibImageRegistry::~LibImageRegistry()
{
    delete[] entries;
}

/**
 * @brief Allocate an empty table.
 * @param capacity Number of resources the table can hold.
 */
LibImageRegistry::LibImageRegistry(s32 capacity)
{
    entries = new (0) LibRenderResource*[capacity];
    this->capacity = capacity;
    count = 0;
}

/**
 * @brief Start the object's DMA chain on channel 1 (VIF1).
 * @param channel DMA channel; unused.
 */
void LibClass178B70::submit_dma(u32 channel)
{
    dma_pending = 1;
    *D1_QWC = 0;
    *D1_TADR = reinterpret_cast<u32>(chain);
    *D_STAT = D_STAT_CIS1;
    *D1_CHCR = DMA_CHCR_START | DMA_CHCR_MODE_CHAIN | DMA_CHCR_DIR_FROM_MEMORY;
}

/**
 * @brief Finish the object's packet.
 * @param channel DMA channel; unused.
 */
void LibClass178B70::complete_dma(u32 channel)
{
    lib_finish_packet(this);
}

/** @brief Queue this object's DMA submission on the VIF1 queue. */
void LibClass178B70::render()
{
    resident_dma_queue_push(g_vif1_dma_queue, this);
}

/**
 * @brief Expire the layer's texture, refresh four of the display's draw register values in the renderer's
 *        per-layer packet, then chain that packet with a texture flush.
 * @param matrix View matrix; unused.
 * @param context Packet building context; unused.
 */
void LibClass178B70::build_packet(const void* matrix, void* context)
{
    u8 index = layer;
    LibRenderer* renderer = static_cast<LibRenderer*>(g_renderer);

    g_texture_cache->expire_texture(index + 0x100);
    u64* packet = reinterpret_cast<u64*>(reinterpret_cast<u32>(&renderer->draw_envs[1][index - 1]) | EE_UNCACHED_ACCELERATED);
    packet[4] = func_004DBCA0(renderer->display, 0);
    packet[6] = func_004DBCA0(renderer->display, 1);
    packet[8] = func_004DBCA0(renderer->display, 2);
    packet[10] = func_004DBCA0(renderer->display, 3);
    owner = static_cast<LibRenderer*>(g_renderer);
    u64* tags = reinterpret_cast<u64*>(reinterpret_cast<u32>(chain) | EE_UNCACHED_ACCELERATED);
    tags[0] = DMA_TAG(6, DMA_TAG_ID_REF, &static_cast<LibRenderer*>(owner)->draw_envs[1][layer - 1]);
    tags[2] = DMA_TAG(3, DMA_TAG_ID_CNT, 0);
    *reinterpret_cast<unsigned __int128*>(&tags[4]) = 0;
    reinterpret_cast<u32*>(tags)[11] = VIF_DIRECTHL(2);
    tags[6] = GIF_TAG_NREG(1) | GIF_TAG_EOP | 1;
    tags[7] = GIF_REGISTER_AD;
    tags[8] = 0;
    tags[9] = GS_REGISTER_TEXFLUSH;
    tags[10] = DMA_TAG_ID_END;
    unk63 = 1;
}

/** @brief Set the object's type ID after the base constructors. */
LibClass178B70::LibClass178B70()
{
    unk65 = 0;
    type_id = 0xB01;
}

/**
 * @brief Start the object's DMA chain on channel 1 (VIF1).
 * @param channel DMA channel; unused.
 */
void LibClass178C00::submit_dma(u32 channel)
{
    dma_pending = 1;
    *D1_QWC = 0;
    *D1_TADR = reinterpret_cast<u32>(chain);
    *D_STAT = D_STAT_CIS1;
    *D1_CHCR = DMA_CHCR_START | DMA_CHCR_MODE_CHAIN | DMA_CHCR_DIR_FROM_MEMORY;
}

/**
 * @brief Finish the object's packet.
 * @param channel DMA channel; unused.
 */
void LibClass178C00::complete_dma(u32 channel)
{
    lib_finish_packet(this);
}

/** @brief Queue this object's DMA submission on the VIF1 queue. */
void LibClass178C00::render()
{
    resident_dma_queue_push(g_vif1_dma_queue, this);
}

/**
 * @brief Build the layer's packets, then point the chain at the renderer's per-layer packet (6 quadwords) and its
 *        16-quadword block.
 * @param matrix View matrix; unused.
 * @param context Packet building context; unused.
 */
void LibClass178C00::build_packet(const void* matrix, void* context)
{
    func_004D0B10(static_cast<LibRenderer*>(g_renderer), layer);
    owner = static_cast<LibRenderer*>(g_renderer);
    u64* tags = reinterpret_cast<u64*>(reinterpret_cast<u32>(chain) | EE_UNCACHED_ACCELERATED);
    tags[0] = DMA_TAG(6, DMA_TAG_ID_REF, &static_cast<LibRenderer*>(owner)->draw_envs[0][layer - 1]);
    tags[2] = DMA_TAG(0x10, 0, &static_cast<LibRenderer*>(owner)->sprite_packets[layer - 1]);
    unk63 = 1;
}

/** @brief Set the object's type ID after the base constructors. */
LibClass178C00::LibClass178C00()
{
    unk65 = 0;
    type_id = 0xB00;
}

/**
 * @brief Set up one of the renderer's extra layers as a square render target, with its MLPS image header and info
 *        block built in place.
 * @param renderer Renderer.
 * @param layer Layer number, from 1.
 * @param size Width and height in pixels, a power of two.
 * @param manager Display manager the layer draws with.
 */
extern "C" void func_004D08D0(LibRenderer* renderer, s32 layer, s32 size, LibDisplayManager* manager)
{
    renderer->layers[layer - 1].size = size;
    renderer->layers[layer - 1].display_manager = manager;
    renderer->layers[layer - 1].unk08 = 0;
    renderer->layers[layer - 1].unk0c = 0;
    renderer->layers[layer - 1].unk0e = 0x40;
    renderer->layers[layer - 1].tag = LIB_TEXTURE_TAG_MLPS;
    renderer->layers[layer - 1].index = layer;
    renderer->layers[layer - 1].image = &renderer->layers[layer - 1].header;
    *reinterpret_cast<u32*>(renderer->layers[layer - 1].header.name) = LIB_TEXTURE_TAG_MLPS;
    renderer->layers[layer - 1].header.id = layer;
    renderer->layers[layer - 1].header.unk02 = 0;
    renderer->layers[layer - 1].header.image_offset = reinterpret_cast<u8*>(&renderer->layers[layer - 1].info) - reinterpret_cast<u8*>(&renderer->layers[layer - 1].header);
    renderer->layers[layer - 1].info.data_size = size * size * 2;
    renderer->layers[layer - 1].info.width = size;
    renderer->layers[layer - 1].info.height = size;

    s32 bits = 0;

    while (size != 0)
    {
        size >>= 1;
        bits++;
    }

    renderer->layers[layer - 1].info.width_log2 = bits - 1;
    renderer->layers[layer - 1].info.height_log2 = bits - 1;
}


/** @brief Set up the packet's fixed words: its tags and the register each write goes to. */
LibSpritePacket::LibSpritePacket()
{
    dma_tag[0] = 0;
    dma_tag[1] = 0;
    vif_flush = 0x11000000;
    vif_direct = 0x5100000F;
    gif_tag = 14 | GIF_TAG_EOP | GIF_TAG_NREG(1);
    gif_registers = 0;
    gif_register_fields.register0 = GIF_REGISTER_AD;
    fba.data = 0;
    fba.address = GS_REGISTER_FBA_1;
    test.address = GS_REGISTER_TEST_1;
    prim.address = GS_REGISTER_PRIM;
    rgbaq.address = GS_REGISTER_RGBAQ;

    for (s32 i = 0; i < 8; i++)
    {
        xyz[i].address = GS_REGISTER_XYZ2;
    }

    restore_test.address = GS_REGISTER_TEST_1;
    scissor.address = GS_REGISTER_SCISSOR_1;
    test.data = 0x30000;
    prim.data = GS_PRIM_SPRITE;
    FlushCache(0);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D0B10);

/**
 * @brief Bring the renderer in line with the active layer mask: (re)allocate or free the per-layer buffers when the
 *        mask changed, give every object that asked for layers a clone in each active one, and reset each active
 *        layer's camera to its square screen.
 * @param renderer Renderer.
 */
extern "C" void func_004D0F80(LibRenderer* renderer)
{
    if (D_001B65C0)
    {
        D_001B65C0 = 0;

        if (D_001B65BC)
        {
            if (!renderer->unk43d4)
            {
                renderer->unk43d4 = new (0) u8[0x2000];

                if (!renderer->unk43d4)
                {
                    return;
                }
            }

            u32 bit = 1;

            for (s32 i = 0; i < 32; i++)
            {
                if (D_001B65BC & bit)
                {
                    if (!renderer->unk43d8[i])
                    {
                        renderer->unk43d8[i] = new (0) u8[0x2000];

                        if (!renderer->unk43d8[i])
                        {
                            return;
                        }
                    }
                }
                else
                {
                    delete[] renderer->unk43d8[i];
                    renderer->unk43d8[i] = 0;
                }

                bit <<= 1;
            }
        }
        else if (renderer->unk43d4)
        {
            delete[] renderer->unk43d4;
            renderer->unk43d4 = 0;

            for (s32 i = 0; i < 32; i++)
            {
                delete[] renderer->unk43d8[i];
                renderer->unk43d8[i] = 0;
            }
        }
    }

    if (!D_001B65BC)
    {
        return;
    }

    LibListSentinel* node = &renderer->sentinel;

    for (;;)
    {
        node = node->next;

        if (&renderer->sentinel == node)
        {
            break;
        }

        LibTransformOwner* object = static_cast<LibTransformOwner*>(node);
        u32 pending = object->unk88;

        if (!pending)
        {
            continue;
        }

        s32 layer = 1;
        u32 bit = layer;

        while (pending)
        {
            if ((D_001B65BC & bit) && (pending & 1))
            {
                LibTransformOwner* copy = object->clone();

                if (copy)
                {
                    copy->layer = layer;
                    object->unk88 &= ~bit;
                    copy->unk88 = 0;
                    u32 mask = ~copy->unk8c;
                    u32 previous = D_001B65BC;
                    D_001B65BC &= mask;
                    copy->unk8c = 0;

                    if (previous != D_001B65BC)
                    {
                        D_001B65C0 = 1;
                    }

                    if (renderer->layers[layer - 1].display_manager)
                    {
                        copy->display_manager = renderer->layers[layer - 1].display_manager;
                    }

                    renderer->append_node(copy, LibUpdateList::DEFAULT_NODE_KIND);
                }
            }

            pending >>= 1;
            bit <<= 1;
            layer++;
        }
    }

    u32 active = D_001B65BC;

    if (!active)
    {
        return;
    }

    s32 index = 1;

    do
    {
        if (active & 1)
        {
            LibDisplayManager* manager = renderer->layers[index - 1].display_manager;

            if (manager)
            {
                LibCamera* camera = static_cast<LibCamera*>(manager->current_display);

                if (camera)
                {
                    s32 half = renderer->layers[index - 1].size / 2;
                    camera->screen_min.x = 2048 - half;
                    camera->screen_min.y = 2048 - half;
                    camera->screen_min.z = 20.0f;
                    camera->screen_min.w = 1.0f;
                    camera->screen_max.x = 2048 + half;
                    camera->screen_max.y = 2048 + half;
                    camera->screen_max.z = 40000.0f;
                    camera->screen_max.w = 1.0f;
                    camera->unk3c8 = 20;
                    camera->unk3cc = 0xFA00;
                    camera->unk3d2 = 0;
                    camera->pixel_aspect = 1.0f;
                    camera->update_projection();
                    manager->prepare_camera();
                }
            }
        }

        active >>= 1;
        index++;
    } while (active);
}

/** @brief Run the renderer's per-frame passes, then its light steps. */
void LibClass178C90::update()
{
    func_004D0F80(renderer);
    renderer->update_lights();
}

/** @brief Update the listed nodes, then make the next hit test start from the first node. */
void LibRenderer::func_slot3C()
{
    update_nodes();
    g_hit_test_restart = 0;
}

/**
 * @brief Run the renderer's light steps and hand the spot lights to the light list.
 * @param renderer Renderer.
 */
extern "C" void func_004D1320(LibRenderer* renderer)
{
    renderer->update_lights();
}

/**
 * @brief Sort a range of draw objects by depth, deepest first: an explicit-stack quicksort down to runs of ten,
 *        then one insertion pass.
 * @param renderer Renderer; unused.
 * @param items Objects to sort.
 * @param first First index.
 * @param last One past the last index.
 */
extern "C" void func_004D1360(LibRenderer* renderer, LibTransformOwner** items, s32 first, s32 last)
{
    s32 low_stack[32];
    s32 high_stack[32];
    s32 i;
    s32 j;
    s32 low;
    s32 high;
    s32 depth;

    if (first == last)
    {
        return;
    }

    low = first;
    high = last - 1;
    depth = 0;

    for (;;)
    {
        if (high - low < 10)
        {
            if (depth == 0)
            {
                break;
            }

            depth--;
            low = low_stack[depth];
            high = high_stack[depth];
        }

        float pivot = items[(low + high) / 2]->depth;
        i = low;
        j = high;

        for (;;)
        {
            while (items[i]->depth > pivot)
            {
                i++;
            }

            while (items[j]->depth < pivot)
            {
                j--;
            }

            if (i >= j)
            {
                break;
            }

            LibTransformOwner* swap = items[i];
            items[i] = items[j];
            items[j] = swap;
            i++;
            j--;
        }

        if (i - low > high - j)
        {
            if (i - low > 10)
            {
                low_stack[depth] = low;
                high_stack[depth] = i - 1;
                depth++;
            }

            low = j + 1;
        }
        else
        {
            if (high - j > 10)
            {
                low_stack[depth] = j + 1;
                high_stack[depth] = high;
                depth++;
            }

            high = i - 1;
        }
    }

    for (s32 k = first + 1; k < last; k++)
    {
        LibTransformOwner* item = items[k];
        float key = item->depth;

        for (j = k - 1; j >= first && items[j]->depth < key; j--)
        {
            items[j + 1] = items[j];
        }

        items[j + 1] = item;
    }
}

/**
 * @brief Sort a renderer's objects for one layer into a draw list: bucket them by draw bucket, sort four buckets by
 *        depth, then lay the buckets and the renderer's own passes out in drawing order.
 * @param renderer Renderer.
 * @param list Receives the objects.
 * @param layer Layer to collect; zero for the main list.
 * @return Number of objects written.
 */
extern "C" s32 func_004D1550(LibRenderer* renderer, LibTransformOwner** list, s32 layer)
{
    s32 counts[11];

    for (s32 bucket = 0; bucket < 11; bucket++)
    {
        counts[bucket] = 0;
    }

    s32 total = 0;
    LibTransformOwner*** buckets = renderer->buckets;
    s32 count = renderer->visible_count;

    if (!renderer->unk40ce)
    {
        for (s32 i = 0; i < count; i++)
        {
            LibTransformOwner* object = reinterpret_cast<LibTransformOwner**>(renderer->unk7c)[i];

            if (object->layer != layer)
            {
                continue;
            }

            object->unk63 = 0;

            if (object->draw_flags & 0x59)
            {
                continue;
            }

            if (object->draw_bucket != 0)
            {
                buckets[object->draw_bucket][counts[object->draw_bucket]++] = object;
            }
            else
            {
                list[total++] = object;
            }
        }
    }
    else
    {
        for (s32 i = 0; i < count; i++)
        {
            LibTransformOwner* object = reinterpret_cast<LibTransformOwner**>(renderer->unk7c)[i];

            if (object->layer != layer)
            {
                continue;
            }

            object->unk63 = 0;

            if (object->draw_flags & 0x59)
            {
                continue;
            }

            if (object->draw_bucket != 0)
            {
                buckets[object->draw_bucket][counts[object->draw_bucket]++] = object;
            }
            else if (object->unk66)
            {
                buckets[0][counts[0]] = object;
                counts[0]++;
            }
            else
            {
                list[total++] = object;
            }
        }
    }

    func_004D1360(renderer, renderer->buckets[2], 0, counts[2]);
    func_004D1360(renderer, renderer->buckets[3], 0, counts[3]);
    func_004D1360(renderer, renderer->buckets[5], 0, counts[5]);
    func_004D1360(renderer, renderer->buckets[7], 0, counts[7]);

    // TODO: The bucket loops are written `<= last` because that's what gives the target's `slti at` loop tests.
    if (renderer->unk40cc)
    {
        for (s32 bucket = 0; bucket <= 3; bucket++)
        {
            s32 size = counts[bucket];
            LibTransformOwner** source = renderer->buckets[bucket];

            for (s32 k = 0; k < size; k++)
            {
                list[k + total] = source[k];
            }

            total += size;
        }

        if (renderer->extra->enabled)
        {
            renderer->extra->unk63 = 0;
            list[total++] = renderer->extra;
        }

        if (renderer->unk40cd)
        {
            s32 size = counts[4];
            LibTransformOwner** source = renderer->buckets[4];

            for (s32 k = 0; k < size; k++)
            {
                list[k + total] = source[k];
            }

            total += size;

            if (layer == 0)
            {
                renderer->unk4458->unk63 = 0;
                list[total++] = renderer->unk4458;
            }

            for (s32 k = 0; k < counts[8]; k++)
            {
                list[k + total] = renderer->buckets[8][k];
            }

            total += counts[8];

            if (layer == 0)
            {
                renderer->unk445c->unk63 = 0;
                list[total++] = renderer->unk445c;
            }

            for (s32 bucket = 5; bucket <= 6; bucket++)
            {
                s32 size = counts[bucket];
                LibTransformOwner** source = renderer->buckets[bucket];

                for (s32 k = 0; k < size; k++)
                {
                    list[k + total] = source[k];
                }

                total += size;
            }
        }
        else
        {
            for (s32 bucket = 4; bucket <= 6; bucket++)
            {
                s32 size = counts[bucket];
                LibTransformOwner** source = renderer->buckets[bucket];

                for (s32 k = 0; k < size; k++)
                {
                    list[k + total] = source[k];
                }

                total += size;
            }
        }
    }
    else
    {
        if (renderer->unk40cd)
        {
            for (s32 bucket = 0; bucket <= 4; bucket++)
            {
                s32 size = counts[bucket];
                LibTransformOwner** source = renderer->buckets[bucket];

                for (s32 k = 0; k < size; k++)
                {
                    list[k + total] = source[k];
                }

                total += size;
            }

            if (layer == 0)
            {
                renderer->unk4458->unk63 = 0;
                list[total++] = renderer->unk4458;
            }

            for (s32 k = 0; k < counts[8]; k++)
            {
                list[k + total] = renderer->buckets[8][k];
            }

            total += counts[8];

            if (layer == 0)
            {
                renderer->unk445c->unk63 = 0;
                list[total++] = renderer->unk445c;
            }

            for (s32 bucket = 5; bucket <= 6; bucket++)
            {
                s32 size = counts[bucket];
                LibTransformOwner** source = renderer->buckets[bucket];

                for (s32 k = 0; k < size; k++)
                {
                    list[k + total] = source[k];
                }

                total += size;
            }
        }
        else
        {
            for (s32 bucket = 0; bucket <= 6; bucket++)
            {
                s32 size = counts[bucket];
                LibTransformOwner** source = renderer->buckets[bucket];

                for (s32 k = 0; k < size; k++)
                {
                    list[k + total] = source[k];
                }

                total += size;
            }
        }

        if (renderer->extra->enabled)
        {
            renderer->extra->unk63 = 0;
            list[total++] = renderer->extra;
        }
    }

    if (layer == 0)
    {
        if (renderer->unk4464->unkaf && !renderer->unk4464->unkae)
        {
            renderer->unk4464->unk63 = 0;
            list[total++] = renderer->unk4464;
        }

        if ((renderer->unk4464->unkaf && renderer->unk4464->unkae) ||
            (renderer->unk4468->unkaf && renderer->unk4468->unkae))
        {
            renderer->unk4460->unk63 = 0;
            list[total++] = renderer->unk4460;
        }
    }

    for (s32 k = 0; k < counts[7]; k++)
    {
        list[k + total] = renderer->buckets[7][k];
    }

    total += counts[7];

    if (layer == 0)
    {
        if (renderer->unk4464->unkaf && renderer->unk4464->unkae && counts[7] != 0)
        {
            renderer->unk4464->unk63 = 0;
            list[total++] = renderer->unk4464;
        }

        if (renderer->unk4468->unkaf)
        {
            renderer->unk4468->unk63 = 0;
            list[total++] = renderer->unk4468;
        }
    }

    if (!renderer->unk40cd)
    {
        if (layer == 0)
        {
            renderer->unk4458->unk63 = 0;
            list[total++] = renderer->unk4458;
        }

        for (s32 k = 0; k < counts[8]; k++)
        {
            list[k + total] = renderer->buckets[8][k];
        }

        total += counts[8];

        if (layer == 0)
        {
            renderer->unk445c->unk63 = 0;
            list[total++] = renderer->unk445c;
        }
    }

    for (s32 k = 0; k < counts[9]; k++)
    {
        list[k + total] = renderer->buckets[9][k];
    }

    total += counts[9];

    for (s32 k = 0; k < counts[10]; k++)
    {
        list[k + total] = renderer->buckets[10][k];
    }

    total += counts[10];

    // TODO: The game zeroes an empty count again before returning it; this keeps that.
    if (total == 0)
    {
        return 0;
    }

    return total;
}

/**
 * @brief Build this frame's draw list. With layered objects, the first object to name a layer in its mask gets that
 *        layer's start marker, the layer's own list and its end marker in front of it.
 */
void LibRenderer::func_004D2C70()
{
    if (D_001B65BC != 0 && unk43d4 != 0)
    {
        LibTransformOwner* firsts[32];
        s32 lasts[32];
        s32 layer_counts[32];
        s32 count;

        for (s32 layer = 0; layer < 32; layer++)
        {
            firsts[layer] = 0;
        }

        count = func_004D1550(this, reinterpret_cast<LibTransformOwner**>(unk43d4), 0);

        for (s32 i = 0; i < count; i++)
        {
            LibTransformOwner* entry = reinterpret_cast<LibTransformOwner**>(unk43d4)[i];
            entry->unk69 &= 0xE0;
            u32 mask = entry->unk8c;

            if (mask != 0)
            {
                for (s32 layer = 0; mask != 0; mask >>= 1, layer++)
                {
                    if (mask & 1)
                    {
                        if (firsts[layer] == 0)
                        {
                            firsts[layer] = entry;
                            entry->unk69 |= 4;
                        }

                        lasts[layer] = i;
                    }
                }
            }
        }

        for (s32 layer = 0; layer < 32; layer++)
        {
            layer_counts[layer] = 0;

            if (firsts[layer] == 0)
            {
                continue;
            }

            reinterpret_cast<LibTransformOwner**>(unk43d4)[lasts[layer]]->unk69 |= 8;

            if (unk43d8[layer] == 0)
            {
                continue;
            }

            layer_counts[layer] = func_004D1550(this, reinterpret_cast<LibTransformOwner**>(unk43d8[layer]), layer + 1);

            if (layer_counts[layer] == 0)
            {
                continue;
            }

            for (s32 k = 0; k < layer_counts[layer]; k++)
            {
                reinterpret_cast<LibTransformOwner**>(unk43d8[layer])[k]->unk69 &= 0xE0;
            }
        }

        s32 total = 0;

        for (s32 i = 0; i < count; i++)
        {
            LibTransformOwner* object = reinterpret_cast<LibTransformOwner**>(unk43d4)[i];

            if (object->unk69 & 4)
            {
                u32 mask = object->unk8c;

                for (s32 layer = 0; mask != 0; mask >>= 1, layer++)
                {
                    if (mask & 1)
                    {
                        // TODO: Byte offsets into the buffer give the target's base-first address adds; indexing a
                        // LibTransformOwner** puts the index first.
                        s32 layer_count = layer_counts[layer];
                        *reinterpret_cast<LibTransformOwner**>(&buffers[buffer_index][total++ * 4]) = &unk5770[layer];
                        unk5770[layer].unk63 = 0;

                        for (s32 k = 0; k < layer_count; k++)
                        {
                            *reinterpret_cast<LibTransformOwner**>(&buffers[buffer_index][total++ * 4]) =
                                reinterpret_cast<LibTransformOwner**>(unk43d8[layer])[k];
                        }

                        *reinterpret_cast<LibTransformOwner**>(&buffers[buffer_index][total++ * 4]) = &unk8770[layer];
                        unk8770[layer].unk63 = 0;
                    }
                }
            }

            *reinterpret_cast<LibTransformOwner**>(&buffers[buffer_index][total++ * 4]) = object;
        }

        list_counts[buffer_index] = total;
    }
    else
    {
        list_counts[buffer_index] = func_004D1550(this, reinterpret_cast<LibTransformOwner**>(buffers[buffer_index]), 0);
    }
}

/**
 * @brief Last light step: drop every listed model that sits behind one of the renderer's occluders, then free the
 *        sphere buffer func_004D3780 filled.
 * @param renderer Renderer.
 */
extern "C" void func_004D3290(LibRenderer* renderer)
{
    if (renderer->sphere_buffer == 0)
    {
        return;
    }

    LibCamera* camera = static_cast<LibCamera*>(renderer->manager->current_display);
    u32 occluders = renderer->unk40d8.node_count;

    if (occluders == 0 || camera == 0)
    {
        delete renderer->sphere_buffer;
        renderer->sphere_buffer = 0;
        return;
    }

    s32 occluder_count = func_00430E00(&renderer->unk40d8, camera, &renderer->unk4360);

    if (occluder_count != 0)
    {
        s32 sphere_index = 0;
        // TODO: count is declared before kept for the target's register order.
        s32 count;
        s32 kept = 0;
        float nearest = renderer->unk40d8.nearest_depth;
        count = renderer->visible_count;

        for (s32 i = 0; i < count; i++)
        {
            LibModel** visible = reinterpret_cast<LibModel**>(renderer->unk7c);
            LibModel* model = visible[i];
            visible[kept++] = model;
            u16 flags = model->draw_flags;

            if (flags & 0x459)
            {
                continue;
            }

            if (model->display_manager != 0 || model->depth < nearest)
            {
                sphere_index++;
                continue;
            }

            vu0_load_vf1(reinterpret_cast<LibVector4*>(renderer->sphere_buffer) + sphere_index++);
            vu0_first_occluder();
            LibOccluder* first = renderer->unk40d8.nodes[0];
            float depth = model->depth;

            for (s32 j = 0; j < occluder_count; j++)
            {
                if (depth < first->depth)
                {
                    vu0_skip_occluder();
                    continue;
                }

                vu0_start_microprogram_d58();
                // TODO: Never read; the game still loads it here.
                LibOccluder* next = renderer->unk40d8.nodes[j + 1];

                if (vu0_read_vi2() == 0)
                {
                    if (flags & 0x2000)
                    {
                        model->update_render_channels();
                    }

                    model->draw_flags |= 0x10;
                    kept--;
                    break;
                }
            }
        }

        renderer->visible_count = kept;
    }

    delete renderer->sphere_buffer;
    renderer->sphere_buffer = 0;
}

/**
 * @brief Second light step: drop every listed model whose oriented box misses the camera's view volume, along with its
 *        sphere in the sphere buffer.
 * @param renderer Renderer.
 */
extern "C" void func_004D3480(LibRenderer* renderer)
{
    if (!renderer->box_cull_enabled)
    {
        return;
    }

    LibCamera* camera = static_cast<LibCamera*>(renderer->manager->current_display);
    s32 count = renderer->visible_count;

    if (camera == 0)
    {
        return;
    }

    LibProjectionVolume volume;
    camera->build_projection_volume(&volume);
    s32 kept = 0;
    LibCullBox box;
    LibMatrix44Value matrix;
    LibVector4 center;
    s32 spheres = renderer->visible_count;

    for (s32 i = 0; i < count; i++)
    {
        LibModel** visible = reinterpret_cast<LibModel**>(renderer->unk7c);
        LibModel* model = visible[i];
        visible[kept++] = model;
        u16 flags = model->draw_flags;

        if (flags & 0x459)
        {
            continue;
        }

        if (model->display_manager != 0)
        {
            continue;
        }

        if (!model->unk66)
        {
            continue;
        }

        if (!model->get_box_cull_center(&box))
        {
            continue;
        }

        // TODO: As in func_004D4010, the named operands give the target's register order.
        const LibMatrix44Value* right = model->get_transform_matrix();
        LibMatrix44Value* product = &matrix;
        const LibMatrix44Value* left = &camera->view_matrix;
        vu0_multiply_matrix(product, left, right);
        ee_transpose_matrix(&matrix, &matrix);
        const LibVector4* local_center = &box.center;
        const LibMatrix44Value* rotation = &matrix;
        vu0_apply_matrix(rotation, local_center, &center);
        copy_vector(&box.center, &center);
        copy_vector(&box.axes[0], matrix_row(&matrix, 0));
        copy_vector(&box.axes[1], matrix_row(&matrix, 1));
        copy_vector(&box.axes[2], matrix_row(&matrix, 2));

        if (func_004CAB20(&volume, &box) != 0)
        {
            continue;
        }

        if (flags & 0x2000)
        {
            model->update_render_channels();
        }

        if (renderer->sphere_buffer != 0)
        {
            spheres--;

            for (s32 k = kept - 1; k < spheres; k++)
            {
                // TODO: Reading the buffer pointer once per operand is what gives the target's registers.
                copy_vector(&reinterpret_cast<LibVector4*>(renderer->sphere_buffer)[k],
                            &reinterpret_cast<LibVector4*>(renderer->sphere_buffer)[k + 1]);
            }
        }

        model->draw_flags |= 0x10;
        kept--;
    }

    renderer->visible_count = kept;
}

extern "C" s8 D_001B65D4;
extern "C" float D_00507250[4];

/**
 * @brief Load a camera's view-projection and depth-scaled view matrices for the sphere test.
 * @param camera Camera whose matrices are loaded.
 * @param scaled_view Depth-scaled, transposed view matrix.
 */
static inline void lib_load_cull_camera(LibCamera* camera, const LibMatrix44Value* scaled_view)
{
    camera->upload_clip_geometry();
    vu0_start_microprogram_1f0_vf5_vf8(&camera->view_matrix);
    vu0_copy_vf1_vf4_to_vf20_vf23();
    vu0_load_vf24_vf27(scaled_view);
}

/**
 * @brief Read whether a camera has fog.
 * @param camera Camera.
 * @return The camera's fog flag.
 */
static inline u8 lib_camera_fog_on(const LibCamera* camera)
{
    return camera->fog_enabled;
}


extern "C" s8 D_001B65D8;
extern "C" float D_00507260[4];

/**
 * @brief First light step: test every model in the renderer against its display's camera, fade the ones flagged to
 *        fade with distance, and list the visible ones with their depths.
 * @param renderer Renderer.
 */
extern "C" void func_004D3780(LibRenderer* renderer)
{
    float far_factor;
    float near_factor;

    if (renderer->light_list != 0)
    {
        func_004E9290(renderer->light_list);
    }

    LibCamera* camera = static_cast<LibCamera*>(renderer->manager->current_display);

    if (camera == 0)
    {
        return;
    }

    float distance = camera->projection_distance;
    camera->upload_clip_geometry();
    renderer->unk4360.set_identity();
    renderer->unk4360.m[0][0] = distance;
    renderer->unk4360.m[1][1] = distance;
    vu0_multiply_matrix(&renderer->unk4360, &renderer->unk4360, &camera->view_matrix);
    ee_transpose_matrix(&renderer->unk4360, &renderer->unk4360);
    vu0_load_vf24_vf27(&renderer->unk4360);

    bool fogged = lib_camera_fog_on(camera) ? true : false;
    float cull_depth = camera->near_fog_distance + camera->near_fog_fraction * (camera->far_fog_distance - camera->near_fog_distance);

    if (fogged)
    {
        camera->get_fog_factors(&far_factor, &near_factor);

        if (near_factor < 255.0f)
        {
            cull_depth = -1e20f;
        }
    }

    LibCamera* current = 0;
    vu0_start_microprogram_1f0_vf5_vf8(&camera->view_matrix);
    vu0_copy_vf1_vf4_to_vf20_vf23();

    // TODO: Same function-local static as in func_004D4010.
    if (!D_001B65D8)
    {
        D_00507260[0] = 0.0f;
        D_00507260[1] = 0.0f;
        D_00507260[2] = 1.0f;
        D_00507260[3] = 1.0f;
        D_001B65D8 = 1;
    }

    LibMatrix44Value scaled_view;
    FieldVec4A position(0.0f, 0.0f, 0.0f, 1.0f);
    FieldVec4A fog;
    FieldVec4A screen;
    FieldVec4A view_depth;
    u8 loaded = 0;
    bool keep_spheres = false;
    unsigned __int128* spheres;

    if (renderer->unk40d8.node_count != 0 && (renderer->unk40d2 == 1 || renderer->unk40d2 == 0))
    {
        keep_spheres = true;
        renderer->sphere_buffer = new (0) u8[0x8000];
        spheres = reinterpret_cast<unsigned __int128*>(renderer->sphere_buffer);
    }

    s32 count = 0;
    LibListSentinel* node = &renderer->sentinel;

    for (;;)
    {
        node = node->next;

        if (at_list_end(&renderer->sentinel, node))
        {
            break;
        }

        LibModel* model = static_cast<LibModel*>(node);
        u16 flags = model->draw_flags;

        if (flags & 0x49)
        {
            if (flags & 0x2000)
            {
                model->update_render_channels();
            }

            continue;
        }

        if (flags & 0x400)
        {
            if (!model->matrix_ready)
            {
                model->update_transform_matrix();
            }

            model->set_default_draw_bucket();
            *reinterpret_cast<unsigned __int128*>(&model->unk70) = *reinterpret_cast<unsigned __int128*>(&model->translation);
            model->depth = model->translation.z;
            model->draw_flags &= 0xFFEF;
            model->unk66 = 1;
            reinterpret_cast<LibModel**>(renderer->unk7c)[count++] = model;
            continue;
        }

        model->draw_flags = flags | 0x10;

        if (!model->matrix_ready)
        {
            model->update_transform_matrix();
        }

        if (model->display_manager != 0)
        {
            LibCamera* own = static_cast<LibCamera*>(model->display_manager->current_display);

            if (own == 0)
            {
                if (flags & 0x2000)
                {
                    model->update_render_channels();
                }

                continue;
            }

            if (own != current)
            {
                current = own;
                own->update_projection();
                float own_distance = own->projection_distance;
                scaled_view.set_identity();
                scaled_view.m[0][0] = own_distance;
                scaled_view.m[1][1] = own_distance;
                // TODO: As in func_004D4010, the named operands give the target's register order.
                LibMatrix44Value* product = &scaled_view;
                const LibMatrix44Value* left = &scaled_view;
                const LibMatrix44Value* right = &own->view_matrix;
                vu0_multiply_matrix(product, left, right);
                ee_transpose_matrix(&scaled_view, &scaled_view);
                loaded = 0;
            }

            if (!loaded)
            {
                lib_load_cull_camera(own, &scaled_view);
                loaded = 1;
            }
        }
        else if (loaded)
        {
            lib_load_cull_camera(camera, &renderer->unk4360);
            loaded = 0;
        }

        if (flags & 0x2)
        {
            const LibMatrix44Value* matrix;

            if (flags & 0x4000)
            {
                if (model->parent_transform != 0)
                {
                    matrix = model->parent_transform->get_transform_matrix();
                }
                else
                {
                    matrix = model->get_transform_matrix();
                }
            }
            else
            {
                matrix = model->get_transform_matrix();
            }

            vu0_start_microprogram_1f0_vf5_vf8(matrix);
            position.x = matrix_row(matrix, 0)->w;
            position.y = matrix_row(matrix, 1)->w;
            position.z = matrix_row(matrix, 2)->w;
            vu0_load_position_vf5(&position);
            vu0_start_microprogram_d0_vf8(D_00507260);
            float fade_distance = renderer->fade_distance;
            float fade_scale = 1.0f / fade_distance;
            vu0_wait_microprogram();
            vu0_read_vf6(&view_depth);

            if (!(view_depth.x <= 0.0f))
            {
                if (flags & 0x2000)
                {
                    model->update_render_channels();
                }

                continue;
            }

            if (flags & 0x800)
            {
                float depth = -view_depth.x;

                if (depth < fade_distance)
                {
                    float alpha = depth * fade_scale;

                    if (!(alpha <= 1.0f))
                    {
                        model->set_fade_alpha(1.0f, 2.0f);
                    }
                    else
                    {
                        model->set_fade_alpha(alpha, 2.0f);
                    }
                }
                else
                {
                    model->set_fade_alpha(1.0f, 2.0f);
                }
            }
        }

        const LibVector4* sphere = model->get_bounding_sphere();
        vu0_start_microprogram_b60_vf5(sphere);
        model->draw_bucket = 0;
        model->unk66 = 0;
        model->set_default_draw_bucket();
        // TODO: Never read; the game still loads it here.
        LibListSentinel* next = node->next;
        s32 outside = vu0_read_vi2();
        s32 inside = vu0_read_vi3();
        vu0_read_vf6(&model->unk70);

        if (outside != 0)
        {
            if (flags & 0x2000)
            {
                model->update_render_channels();
            }

            continue;
        }

        vu0_store_vf8(&screen);
        model->depth = screen.z;

        if (inside != 0)
        {
            model->unk66 = 1;

            if (keep_spheres)
            {
                *spheres++ = *reinterpret_cast<const unsigned __int128*>(sphere);
            }

            model->draw_flags &= 0xFFEF;
        }
        else
        {
            vu0_start_microprogram_c88();

            if (keep_spheres)
            {
                *spheres++ = *reinterpret_cast<const unsigned __int128*>(sphere);
            }

            model->draw_flags &= 0xFFEF;
            outside = vu0_read_vi2();
            model->unk66 = outside;
        }

        reinterpret_cast<LibModel**>(renderer->unk7c)[count++] = model;

        if (fogged)
        {
            vu0_store_vf9(&fog);

            if (cull_depth <= fog.z)
            {
                model->unk67 = 1;
            }
            else
            {
                model->unk67 = 0;
            }
        }
        else
        {
            model->unk67 = 0;
        }
    }

    renderer->visible_count = count;
}

/**
 * @brief Test each object's bounding sphere against its display's camera and mark the visible ones for drawing.
 * @param object Renderer whose display manager gives the default camera.
 * @param count Number of objects.
 * @param entries Objects to test.
 */
extern "C" void func_004D4010(void* object, s32 count, void** entries)
{
    LibRenderer* renderer = static_cast<LibRenderer*>(object);
    LibCamera* camera = static_cast<LibCamera*>(renderer->manager->current_display);
    float far_factor;
    float near_factor;

    if (camera == 0)
    {
        return;
    }

    camera->update_projection();
    float distance = camera->projection_distance;
    camera->upload_clip_geometry();
    renderer->unk4360.set_identity();
    renderer->unk4360.m[0][0] = distance;
    renderer->unk4360.m[1][1] = distance;
    vu0_multiply_matrix(&renderer->unk4360, &renderer->unk4360, &camera->view_matrix);
    ee_transpose_matrix(&renderer->unk4360, &renderer->unk4360);
    vu0_load_vf24_vf27(&renderer->unk4360);

    bool fogged = lib_camera_fog_on(camera) ? true : false;
    // TODO: Never read here. func_004D3780 works out the same depth and uses it, so I think this was copied.
    float cull_depth = camera->near_fog_distance + camera->near_fog_fraction * (camera->far_fog_distance - camera->near_fog_distance);

    if (fogged)
    {
        camera->get_fog_factors(&far_factor, &near_factor);

        if (near_factor < 255.0f)
        {
            cull_depth = -1e20f;
        }
    }

    LibCamera* current = 0;
    vu0_start_microprogram_1f0_vf5_vf8(&camera->view_matrix);
    vu0_copy_vf1_vf4_to_vf20_vf23();

    // TODO: I think this is a function-local static vector and its guard byte. It sits in a rodata piece the
    // unit doesn't own yet, so it's written by hand through externs.
    if (!D_001B65D4)
    {
        D_00507250[0] = 0.0f;
        D_00507250[1] = 0.0f;
        D_00507250[2] = 1.0f;
        D_00507250[3] = 1.0f;
        D_001B65D4 = 1;
    }

    LibMatrix44Value scaled_view;
    // TODO: Never read, but the game still builds it on the stack.
    FieldVec4A origin(0.0f, 0.0f, 0.0f, 1.0f);
    u8 loaded = 0;

    for (s32 i = 0; i < count; i++)
    {
        LibTransformOwner* entry = static_cast<LibTransformOwner*>(entries[i]);
        u16 flags = entry->draw_flags;

        if (flags & 0x49)
        {
            continue;
        }

        if (flags & 0x400)
        {
            entry->draw_flags = flags & 0xFFEF;
            continue;
        }

        entry->draw_flags = flags | 0x10;

        if (!entry->matrix_ready)
        {
            entry->update_transform_matrix();
        }

        if (entry->display_manager != 0)
        {
            LibCamera* own = static_cast<LibCamera*>(entry->display_manager->current_display);

            if (own != current)
            {
                current = own;
                own->update_projection();
                float own_distance = own->projection_distance;
                scaled_view.set_identity();
                scaled_view.m[0][0] = own_distance;
                scaled_view.m[1][1] = own_distance;
                // TODO: Naming the operands is the only way I've found to get the target's register order.
                LibMatrix44Value* product = &scaled_view;
                const LibMatrix44Value* left = &scaled_view;
                const LibMatrix44Value* right = &own->view_matrix;
                vu0_multiply_matrix(product, left, right);
                ee_transpose_matrix(&scaled_view, &scaled_view);
                loaded = 0;
            }

            if (!loaded)
            {
                lib_load_cull_camera(own, &scaled_view);
                loaded = 1;
            }
        }
        else if (loaded)
        {
            lib_load_cull_camera(camera, &renderer->unk4360);
            loaded = 0;
        }

        vu0_start_microprogram_b60_vf5(entry->get_bounding_sphere());
        entry->draw_bucket = 0;
        entry->unk66 = 0;

        if (vu0_read_vi2() == 0)
        {
            entry->draw_flags &= ~0x10;
        }
    }
}

/**
 * @brief Test or wait for the renderer's packets in flight.
 * @param poll Nonzero to only test; zero to wait until none is in flight.
 * @return Whether a packet is in flight (when polling).
 */
bool LibRenderer::func_004D44D0(s32 poll)
{
    if (poll)
    {
        return main_packet_busy || bucket_packet_busy || unk40ca;
    }

    TIMER0_COUNT;

    // TODO: The DMA handlers clear these flags; the wait only re-reads them through volatile accesses.
    while (*(volatile u8*)&main_packet_busy || *(volatile u8*)&bucket_packet_busy || *(volatile u8*)&unk40ca)
    {
    }

    unk40c4 = 0;
    current_count = 0;
    return 0;
}

/**
 * @brief With interrupts off, flag the renderer's display once its main packet is done.
 * @param renderer Renderer.
 */
static inline void lib_flag_display_idle(LibRenderer* renderer)
{
    LibInterruptLock interrupts;

    if (!renderer->main_packet_busy && renderer->display != 0)
    {
        renderer->display->unk3E6A = 1;
    }
}

/**
 * @brief Kick the packet queue if a main packet is waiting, then render every object in the current list that is a
 *        bucket packet with work; with none, flag the display once the main packet is done.
 */
void LibRenderer::func_004D4560()
{
    {
        LibInterruptLock interrupts;

        if (main_packet != 0)
        {
            func_004DC420(g_packet_queue, 0);
        }
    }

    s32 count = current_count;
    bool idle = true;

    for (s32 i = 0; i < count; i++)
    {
        LibTransformOwner* object = reinterpret_cast<LibTransformOwner**>(cursor)[i];

        if (object->unk65 == 1 && object->unk63 != 0)
        {
            bucket_packet = object;
            bucket_packet_busy = 1;
            idle = false;
            object->render();
            unk40b0 = i + 1;
        }
    }

    if (idle)
    {
        lib_flag_display_idle(this);
    }
}

extern "C" void func_004D90B0(void* address, void* scratchpad);

/**
 * @brief Build the frame's packets: copy the texture cache to the scratchpad, build every object's packet in two
 *        passes (on VU0 while the microcode upload runs, then on the CPU with camera switches), start the objects that
 *        render their own main packet, and copy the cache back.
 */
void LibRenderer::func_004D4700()
{
    unk40d4 = g_texture_cache;
    g_texture_cache = new (EE_SCRATCHPAD) LibTextureCache;
    FlushCache(0);
    func_004D90B0(unk40d4, g_texture_cache);
    unk40cf = 1;
    s32 count = current_count;
    unk4090 = -1;
    u8 timed = 0;
    LibListObject* camera = manager->current_display;
    LibListObject* current = camera;

    {
        LibInterruptLock interrupts;
        unk40ca = 1;
    }

    for (s32 i = 0; i < count; i++)
    {
        reinterpret_cast<LibTransformOwner**>(cursor)[i]->unk62 = 0;
    }

    if (g_microcode_loader->unk06)
    {
        ee_wait_dma_condition();
        EnableDmac(D_001B6608->channel);

        for (s32 pass = 0; pass < 2; pass++)
        {
            for (s32 i = 0; i < count; i++)
            {
                if (!g_microcode_loader->unk06)
                {
                    break;
                }

                LibTransformOwner* object = reinterpret_cast<LibTransformOwner**>(cursor)[i];

                if (object->unk65 == pass && !object->unk63)
                {
                    if (object->display_manager != 0)
                    {
                        object->build_packet(object->display_manager->current_display, light_list);
                    }
                    else
                    {
                        object->build_packet(current, light_list);
                    }

                    if (object->unk69 & 8)
                    {
                        g_texture_cache->expire_texture(object->layer);
                    }
                }
            }
        }

        LibMicrocodeLoader* loader = g_microcode_loader;

        while (*(volatile u8*)&loader->unk06)
        {
        }

        manager->submit_camera();
    }
    else
    {
        manager->submit_camera();
        ee_wait_dma_condition();
        EnableDmac(D_001B6608->channel);
    }

    func_004DBEE0(g_packet_queue, 0);
    resident_sync_gs_path(g_input_system, 0, 0);

    for (s32 pass = 0; pass < 2; pass++)
    {
        for (s32 i = 0; i < count; i++)
        {
            LibTransformOwner* object = reinterpret_cast<LibTransformOwner**>(cursor)[i];

            if (object->unk65 != pass)
            {
                continue;
            }

            if (object->display_manager != 0)
            {
                LibListObject* display = object->display_manager->current_display;

                if (current != display)
                {
                    if (!object->display_manager->unk94)
                    {
                        object->display_manager->prepare_camera();
                    }

                    object->display_manager->submit_camera();
                }

                current = display;
            }
            else if (current != camera)
            {
                current = camera;

                if (!g_microcode_loader->unk06)
                {
                    manager->func_004DB0F0();
                    manager->submit_camera();
                }
            }

            if (!object->unk63)
            {
                u8 flags = object->unk69;
                object->build_packet(current, light_list);

                if (flags & 8)
                {
                    g_texture_cache->expire_texture(object->layer);
                }
            }

            if (pass == 0 && object->unk63)
            {
                if (!timed)
                {
                    timed = 1;
                    packet_start_time = TIMER0_COUNT;
                }

                main_packet = object;
                main_packet_busy = 1;
                object->render();
                unk408c = i + 1;
            }
        }
    }

    lib_restore_texture_cache(this);
}

/** @brief Start a frame: swap packet buffers and, with a list and a camera, build the frame's packets. */
void LibRenderer::begin_frame()
{
    func_004D9A80(D_001B65FC, 0);
    g_inverse_frame_ticks = 1.0f / g_frame_ticks;

    if (manager == 0)
    {
        func_004D99B0(D_001B65FC);
        return;
    }

    func_004D99B0(D_001B65FC);
    manager->prepare_camera();
    func_004C8390(manager);
    unk40cb = 0;
    unk40a0 = 0;
    unk408c = 0;
    packet_ticks = 0;
    cursor = buffers[buffer_index];
    current_count = list_counts[buffer_index];
    buffer_index ^= 1;
    main_packet = 0;
    packet_start_time = 0;

    if (current_count != 0 && manager->current_display != 0)
    {
        D_001B65C8 = func_004DBCA0(display, 0);
        unk40b0 = 0;
        func_004D4700();
        func_004D4560();
    }

    unk40ca = 0;
}

// TODO: The renderer's destructor inlines this member's destructor, so it's inline here; its out-of-line copy still
// comes from the vtable.
/** @brief Destroy the list. */
inline LibClass178B30::~LibClass178B30()
{
}

/** @brief Destroy the passes, buffers and member objects, then the list. */
LibRenderer::~LibRenderer()
{
    delete[] unk43d4;

    for (s32 i = 0; i < 32; i++)
    {
        delete[] unk43d8[i];
        cameras[i]->destroy();
    }

    unk4458->destroy();
    unk445c->destroy();
    unk4460->destroy();
    unk4464->destroy();
    unk4468->destroy();
    extra->destroy();
    delete[] unk7c;
}

LibClass178F30::~LibClass178F30()
{
}

// TODO: These two inline the whole base chain down to LibLink, which the unit's default depth stops short of, but
// level=7 for the whole unit breaks lib_list_add_chain_kind_offsets. I don't know yet what the real setting was.
#pragma push
#pragma inline_depth(7)

LibClass178C00::~LibClass178C00()
{
}

LibClass178B70::~LibClass178B70()
{
}

#pragma pop

extern "C" s16 D_004ED300[11];

/**
 * @brief Build the renderer's members, passes and per-layer cameras, then draw on a display.
 * @param target Display to draw on.
 */
LibRenderer::LibRenderer(LibCameraContext* target)
{
    light_list = 0;
    manager = 0;
    bucket_packet_busy = 0;
    main_packet_busy = 0;
    unk40ca = 0;
    unk40b4 = 0;
    unk40c4 = 0;
    fade_distance = 0.25f;
    unk40ce = 1;
    unk40cc = 0;
    unk40cd = 0;
    sphere_buffer = 0;
    unk40d2 = 0;
    box_cull_enabled = 1;
    buffer_index = 0;
    list_counts[0] = 0;
    list_counts[1] = 0;
    visible_count = 0;
    unk7c = new (0) u8[0x2000];
    cursor = 0;
    u32 address = 0x70000000;

    for (s32 i = 0; i < 11; i++)
    {
        buckets[i] = reinterpret_cast<LibTransformOwner**>(address);
        address += D_004ED300[i] * 4;
    }

    unk4458 = reinterpret_cast<LibRendererPass*>(new (0) LibClass174840(target));
    unk445c = reinterpret_cast<LibRendererPass*>(new (0) LibClass1747C0);
    unk4460 = reinterpret_cast<LibRendererPass*>(new (0) LibClass172750);
    unk4464 = reinterpret_cast<LibRendererPass*>(new (0) LibClass1726C0);
    unk4468 = reinterpret_cast<LibRendererPass*>(new (0) LibClass172630);
    extra = reinterpret_cast<LibRendererExtra*>(new (0) LibClass1727E0);
    unk43d4 = 0;

    for (s32 layer = 0; layer < 32; layer++)
    {
        cameras[layer] = new (0) LibCamera(target);
    }

    memset_guess(layers, 0, sizeof(layers));

    for (s32 layer = 0; layer < 32; layer++)
    {
        unk43d8[layer] = 0;
        cameras[layer]->horizontal_fov = 0.7853982f;
        cameras[layer]->set_centre(2048.0f, 2048.0f);
        cameras[layer]->width_scale = 1.0f;
        cameras[layer]->unk270 = 1.0f;
        cameras[layer]->unk3d1 = 1;
        unk8770[layer].layer = layer + 1;
        unk5770[layer].layer = layer + 1;
    }

    set_display(target);
    FlushCache(0);
}

#include "overlays/lib/display_manager_inlines.h"

/** @brief Forget the owning list, then destroy through the base. */
void LibClass178B70::destroy()
{
    owner = 0;
    LibTransformOwner::destroy();
}

/** @brief Forget the owning list, then destroy through the base. */
void LibClass178C00::destroy()
{
    owner = 0;
    LibTransformOwner::destroy();
}

LibClass178C90::~LibClass178C90()
{
}

/**
 * @brief Return the list kind.
 * @return Ten.
 */
s32 LibClass178C90::get_default_list_kind()
{
    return 10;
}

/** @brief Do nothing. */
void LibRenderer::func_slot38()
{
}

/**
 * @brief Hand the camera's view-projection matrix to the VU0 microprogram at 0x1F0.
 * @param camera Camera whose matrices are used.
 */
extern "C" void lib_load_camera_screen_matrix(const LibCamera* camera)
{
    LibMatrix44Value matrix = func_004CF7C0(camera->projection_matrix, camera->view_matrix);
    vu0_start_microprogram_1f0_vf5_vf8(&matrix);
}

/** @brief Initialize the transform subclass. */
LibClass172000::LibClass172000()
{
    unk65 = 1;
}

/** @brief Start at the origin. */
LibPositionTransform::LibPositionTransform()
{
    clear_vector(&translation);
    translation.w = 1.0f;
}

/**
 * @brief Find an indexed entry across the linked child channels.
 *
 * Only positive child counts consume part of the index.
 * @param index Entry index across the children; negative values reach the first nonempty child.
 * @return Entry pointer, or null when no child supplies the index.
 */
void* LibResourceBuffer::find_child_data(s32 index)
{
    if (children == 0)
    {
        return 0;
    }

    for (LibListSentinel* node = children->next; ; node = node->next)
    {
        if (children == node)
        {
            break;
        }

        LibRenderChannel* child = static_cast<LibRenderChannel*>(node);
        s32 count = child->get_entry_count();

        if (count > 0)
        {
            if (index < count)
            {
                return child->get_entry(index);
            }

            index -= count;
        }
    }

    return 0;
}

extern "C" LibImageRegistry* g_image_registry;

/** Lib heap, or null to use the C library. */
extern "C" ResidentHeap* D_001B6698;

/** Header shared by a resource's part records: each one gives its own size. */
struct LibResourceRecord
{
    u8 unk00[4];
    s16 size;
};

/**
 * @brief Borrow data for a resource and register it with the image registry.
 * @param resource Resource to fill.
 * @param data Data the resource doesn't own.
 */
extern "C" void func_004D5A50(LibResourceBuffer* resource, void* data)
{
    resource->data = data;
    resource->external_data = 1;
    func_004D02E0(g_image_registry, resource);
    resource->registered = 1;
}

/**
 * @brief Return the record at a resource's second cursor and move that cursor to the next one.
 * @param resource Resource to read.
 * @return The record, or null at the end.
 */
extern "C" void* func_004D5A90(LibResourceBuffer* resource)
{
    LibResourceRecord* record = static_cast<LibResourceRecord*>(resource->unk10);

    if (record->size == 0)
    {
        return 0;
    }

    resource->unk10 = reinterpret_cast<u8*>(record) + record->size;
    return record;
}

/**
 * @brief Return the record at a resource's cursor and move the cursor to the next one.
 * @param resource Resource to read.
 * @return The record, or null at the end.
 */
extern "C" void* func_004D5AC0(LibResourceBuffer* resource)
{
    LibResourceRecord* record = static_cast<LibResourceRecord*>(resource->record_cursor);

    if (record->size == 0)
    {
        return 0;
    }

    resource->record_cursor = reinterpret_cast<u8*>(record) + record->size;
    return record;
}

/**
 * @brief Return the payload size from a resource's chunk header.
 * @param resource Resource to measure.
 * @return Size in bytes, or zero without storage.
 */
extern "C" u32 func_004D5AF0(LibResourceBuffer* resource)
{
    LibResourceChunkHeader* chunk;

    if (resource->external_data)
    {
        chunk = static_cast<LibResourceChunkHeader*>(resource->data);
    }
    else
    {
        chunk = resource->data != 0 ? reinterpret_cast<LibResourceChunkHeader*>(RESIDENT_ALIGN_RESOURCE(resource->data)) : 0;
    }

    if (chunk == 0)
    {
        return 0;
    }

    return chunk->payload_size;
}

/**
 * @brief Return a resource's own payload, after the chunk header.
 * @param resource Resource to read.
 * @return Payload pointer, or null without storage.
 */
extern "C" u8* func_004D5B50(LibResourceBuffer* resource)
{
    if (resource->external_data)
    {
        return resource->data != 0 ? static_cast<u8*>(resource->data) + sizeof(LibResourceChunkHeader) : 0;
    }

    return resource->data != 0 ? reinterpret_cast<u8*>(RESIDENT_ALIGN_RESOURCE(resource->data)) + sizeof(LibResourceChunkHeader) : 0;
}

/**
 * @brief Point a resource's second cursor at its first record, 0x70 bytes into its storage.
 * @param resource Resource to rewind.
 */
extern "C" void func_004D5BB0(LibResourceBuffer* resource)
{
    if (resource->external_data)
    {
        resource->unk10 = resource->data != 0 ? static_cast<u8*>(resource->data) + 0x70 : 0;
    }
    else
    {
        resource->unk10 = resource->data != 0 ? reinterpret_cast<u8*>(RESIDENT_ALIGN_RESOURCE(resource->data)) + 0x70 : 0;
    }
}

/**
 * @brief Point a resource's record cursor at its first part record.
 *
 * The records start 0x60 bytes into the payload, taken from the override when one is set.
 * @param resource Resource to rewind.
 */
extern "C" void func_004D5C10(LibResourceBuffer* resource)
{
    if (resource->payload_override != 0)
    {
        resource->record_cursor = static_cast<u8*>(resource->payload_override) + 0x60;
    }
    else if (resource->external_data)
    {
        resource->record_cursor = resource->data != 0 ? static_cast<u8*>(resource->data) + 0x70 : 0;
    }
    else
    {
        resource->record_cursor = resource->data != 0 ? reinterpret_cast<u8*>(RESIDENT_ALIGN_RESOURCE(resource->data)) + 0x70 : 0;
    }
}

/** @brief Unregister the resource from the resource manager if it is registered. */
void LibResourceBuffer::unregister()
{
    if (registered)
    {
        registered = 0;
        release_textures();
        func_004D0260(g_image_registry, this);
    }
}

/** @brief Unregister the resource and release owned data. */
LibResourceBuffer::~LibResourceBuffer()
{
    if (registered)
    {
        release_textures();
        func_004D0260(g_image_registry, this);
    }

    if (!external_data)
    {
        ::operator delete(data);
    }
}

/**
 * @brief Return the list of the model's render channels; the base has none.
 * @return Null.
 */
LibListReceiver* LibModelBase::get_render_channels()
{
    return 0;
}

/** @brief Flag the owning renderer's first pass for a mesh with bit 0 of unk54 set, then update the color model. */
void LibModelBase::update()
{
    if (resource != 0)
    {
        LibMeshHeader* mesh = reinterpret_cast<LibMeshHeader*>(lib_resource_payload(resource));

        if (mesh->unk54 & 1)
        {
            static_cast<LibRenderer*>(owner)->unk4458->unk9c = 1;
        }
    }

    LibColorModel::update();
}

/**
 * @brief Read a mesh's render-data record count.
 * @param mesh Mesh header.
 * @return Number of records.
 */
static inline s32 mesh_record_count(const LibMeshHeader& mesh)
{
    return mesh.unk40;
}

/**
 * @brief Find the model's render-data record for an index and report its image's two keys, resolving an offset
 * record to a pointer on the way.
 * @param model Model whose mesh holds the records.
 * @param index Record index.
 * @param first_key Receives the image's first key.
 * @param second_key Receives the image's second key.
 */
extern "C" void func_004D5E10(LibModel* model, s32 index, u32* first_key, u32* second_key)
{
    LibMeshHeader* mesh = reinterpret_cast<LibMeshHeader*>(lib_resource_payload(model->resource));

    if (mesh->unk38 == 0)
    {
        return;
    }

    if (mesh->unk08 == 0)
    {
        return;
    }

    LibRenderDataRecord* record = reinterpret_cast<LibRenderDataRecord*>(reinterpret_cast<u8*>(mesh) + mesh->unk08);

    for (s32 i = 0; i < mesh_record_count(*mesh); i++)
    {
        s16 kind = record->storage_kind;

        if (record->index == index)
        {
            if (kind == RENDER_DATA_OFFSET)
            {
                kind = RENDER_DATA_RESOLVED;
                record->storage_kind = kind;
                record->data = reinterpret_cast<u8*>(record) + record->data_offset;
                record->resolved_data = record->data;
            }

            if (kind == RENDER_DATA_SHARED)
            {
                *first_key = record->key08;
                *second_key = record->key0c;
            }
            else if (kind == RENDER_DATA_INLINE)
            {
                LibImageDataHeader* image = reinterpret_cast<LibImageDataHeader*>(reinterpret_cast<u8*>(record) + sizeof(LibRenderDataRecord) + sizeof(LibResourceChunkHeader));
                *first_key = image->first_key;
                *second_key = image->second_key;
            }
            else if (kind == RENDER_DATA_RESOLVED)
            {
                LibImageDataHeader* image = static_cast<LibImageDataHeader*>(record->resolved_data);
                *first_key = image->first_key;
                *second_key = image->second_key;
            }

            return;
        }

        record = reinterpret_cast<LibRenderDataRecord*>(reinterpret_cast<u8*>(mesh) + record->next_offset);
    }
}

/**
 * @brief Return the size of a model's mesh payload: the size its header gives, or the chunk's payload size.
 * @param model Model to measure.
 * @return Size in bytes, or zero without a resource.
 */
extern "C" u32 func_004D5F50(LibModelBase* model)
{
    LibResourceBuffer* resource = model->resource;

    if (!resource)
    {
        return 0;
    }

    u32 size = reinterpret_cast<LibMeshHeader*>(lib_resource_payload(resource))->unk38;

    if (size)
    {
        return size;
    }

    return func_004D5AF0(resource);
}

/**
 * @brief Swap the object's bits in the resident flag word for a mesh's, and note when the word changed.
 * @param object Object whose bits change.
 * @param mesh Mesh whose resident mask the object takes.
 */
static inline void lib_model_take_resident_mask(LibTransformOwner* object, const LibMeshHeader* mesh)
{
    u32 mask = mesh->resident_mask;
    u32 previous = D_001B65BC;
    D_001B65BC &= ~object->unk8c;
    object->unk8c = mask;
    D_001B65BC |= mask;

    if (previous != D_001B65BC)
    {
        D_001B65C0 = 1;
    }
}

/** @brief Go back to the resource's own payload. */
void LibModelBase::clear_payload()
{
    if (resource != 0)
    {
        resource->payload_override = 0;
    }
}

/**
 * @brief Switch to a payload override.
 * @param payload Payload to draw instead of the resource's own.
 * @param set Packet set the payload goes in; unused here.
 */
void LibModelBase::select_payload(void* payload, u8 set)
{
    if (resource != 0)
    {
        resource->payload_override = payload;
    }
}

/**
 * @brief Draw the resource with a payload override.
 * @param payload Payload to draw instead of the resource's own.
 * @param set Packet set the payload goes in; unused here.
 */
void LibModelBase::load_payload(void* payload, u8 set)
{
    if (resource != 0)
    {
        resource->payload_override = payload;
    }
}

/**
 * @brief Turn fogging on or off, in the resource's primitives too: the FGE bit of every flagged part's primitive
 *        tags, written through the uncached segment.
 * @param enabled Nonzero for fog.
 */
void LibModelBase::set_fog_enabled(u8 enabled)
{
    if (fog_enabled != enabled && resource != 0)
    {
        LibMeshHeader* mesh = reinterpret_cast<LibMeshHeader*>(lib_resource_payload(resource));
        func_004D5C10(resource);
        s32 count = mesh->part_count;

        if (enabled)
        {
            for (s32 i = 0; i < count; i++)
            {
                LibMeshPartRecord* record = static_cast<LibMeshPartRecord*>(func_004D5AC0(resource));

                if (record->unk14 & 1)
                {
                    LibModelPart* part = reinterpret_cast<LibModelPart*>(reinterpret_cast<u32>(&record->part) | EE_UNCACHED_ACCELERATED);
                    part->first_tag_high |= GIF_TAG_HIGH_PRIM_FGE;
                    part->second_tag_high |= GIF_TAG_HIGH_PRIM_FGE;

                    if (part->unk84)
                    {
                        part->third_tag_high |= GIF_TAG_HIGH_PRIM_FGE;
                        part->fourth_tag_high |= GIF_TAG_HIGH_PRIM_FGE;
                    }
                }
            }
        }
        else
        {
            for (s32 i = 0; i < count; i++)
            {
                LibMeshPartRecord* record = static_cast<LibMeshPartRecord*>(func_004D5AC0(resource));

                if (record->unk14 & 1)
                {
                    LibModelPart* part = reinterpret_cast<LibModelPart*>(reinterpret_cast<u32>(&record->part) | EE_UNCACHED_ACCELERATED);
                    part->first_tag_high &= ~GIF_TAG_HIGH_PRIM_FGE;
                    part->second_tag_high &= ~GIF_TAG_HIGH_PRIM_FGE;

                    if (part->unk84)
                    {
                        part->third_tag_high &= ~GIF_TAG_HIGH_PRIM_FGE;
                        part->fourth_tag_high &= ~GIF_TAG_HIGH_PRIM_FGE;
                    }
                }
            }
        }

        fog_enabled = enabled;
        unk59d_0 = 1;
    }
}

extern "C" void func_004D6230(void* receiver, u32 arg1, u32 arg2)
{
    LibFieldPointer634* object = (LibFieldPointer634*)receiver;
    func_00448A10(object->unk634, arg1, arg2);
}

/** @brief Delete the resource when the model owns it, then forget it. */
void LibModelBase::release_resource()
{
    if (owns_resource)
    {
        delete resource;
    }

    resource = 0;
}

/**
 * @brief Borrow mesh data into the model's resource, give it the render channels and take its resident mask.
 * @param data Mesh data.
 * @return Always one.
 */
s32 LibModelBase::borrow_mesh(void* data)
{
    func_004D5A50(resource, data);
    resource->children = &get_render_channels()->sentinel;
    LibMeshHeader* header = reinterpret_cast<LibMeshHeader*>(lib_resource_active_payload(resource));

    if (header != 0)
    {
        lib_model_take_resident_mask(this, header);
    }

    return 1;
}

/**
 * @brief Draw a mesh resource the model doesn't own, and take its resident mask.
 * @param mesh Mesh resource.
 * @return Always one.
 */
s32 LibModelBase::set_resource(LibResourceBuffer* mesh)
{
    owns_resource = 0;
    resource = mesh;
    LibMeshHeader* header = reinterpret_cast<LibMeshHeader*>(lib_resource_active_payload(resource));

    if (header != 0)
    {
        lib_model_take_resident_mask(this, header);
    }

    return 1;
}

/**
 * @brief Own a draw buffer, give it the model's render channels and take its resident mask.
 * @param buffer Draw buffer to attach.
 * @return Always one.
 */
s32 LibModelBase::attach_draw_buffer(LibDrawBuffer* buffer)
{
    owns_resource = 1;
    resource = buffer;
    resource->children = &get_render_channels()->sentinel;
    LibMeshHeader* header = reinterpret_cast<LibMeshHeader*>(lib_resource_active_payload(resource));

    if (header != 0)
    {
        lib_model_take_resident_mask(this, header);
    }

    return 1;
}

/** @brief Release the resource when owned, then destroy the model. */
LibModelBase::~LibModelBase()
{
    if (resource)
    {
        if (owns_resource)
        {
            delete resource;
        }

        resource = 0;
    }
}

/**
 * @brief Remove the object from its owner and clear the owner pointer.
 * @param object Object whose owner receives the removal callback.
 */
extern "C" void lib_object_detach_owner(void* object)
{
    LibListObject* node = static_cast<LibListObject*>(object);

    if (node->owner)
    {
        node->owner->remove_node(object);
    }

    node->owner = 0;
}

/**
 * @brief Update the owner's kind counts, then store the node's list kind.
 * @param node Node whose list kind is changed.
 * @param kind Kind passed to the owner; its low halfword is stored in the node.
 */
extern "C" void lib_object_set_list_kind(LibListObject* node, s32 kind)
{
    if (node->owner)
    {
        lib_list_change_node_kind_counts(node->owner, node, kind);
    }

    node->list_kind = kind;
}

/**
 * @brief Release the owned node buffer when no node buffer is active.
 * @param owner List that owns the buffer.
 * @return One if the buffer was released, or zero while a buffer is active.
 */
extern "C" s32 lib_list_release_node_buffer(LibUpdateList* owner)
{
    if (owner->active_node_buffer)
    {
        return 0;
    }

    delete[] owner->owned_node_buffer;
    owner->owned_node_buffer = 0;
    owner->node_buffer_capacity = 0;
    return 1;
}

/**
 * @brief Allocate the owned node-pointer buffer and store its capacity.
 * @param owner List that owns the buffer.
 * @param node_count Number of node pointers to allocate.
 */
extern "C" void lib_list_allocate_node_buffer(LibUpdateList* owner, s32 node_count)
{
    owner->owned_node_buffer = new (0) void*[node_count];
    owner->node_buffer_capacity = node_count;
}

extern "C" void func_004D66F0(void* object)
{
}

/**
 * @brief Update one node of an update list.
 * @param list Update list that owns the node; unused.
 * @param node Node to update.
 */
void lib_update_list_update_node(void* list, void* node)
{
    static_cast<LibListObject*>(node)->update();
}

/**
 * @brief Update every node of this list and the lists chained after it: collect them into one buffer grouped by
 *        kind, then update each listed node in order. A node whose object_kind has bit 1 set is skipped, bit 2 clears
 *        its matrix state first, and bit 4 runs its update on the scratchpad stack.
 */
void LibUpdateList::update_nodes()
{
    ee_clear_breakpoints();
    active_node_count = node_count;

    if (next_list)
    {
        active_node_count += func_004D69A0(next_list);
    }

    if (active_node_count == 0)
    {
        return;
    }

    if (owned_node_buffer)
    {
        active_node_buffer = owned_node_buffer;
    }
    else
    {
        active_node_buffer = new (0) void*[active_node_count];
    }

    if (active_node_buffer == 0)
    {
        return;
    }

    lib_list_collect_nodes_by_kind(this, active_node_buffer);

    if (next_list)
    {
        func_004D68F0(next_list, this);
    }

    for (active_node_index = 0; active_node_index < active_node_count; active_node_index++)
    {
        LibListObject* node = static_cast<LibListObject*>(active_node_buffer[active_node_index]);

        if (node == 0 || !node->is_listed)
        {
            continue;
        }

        u8 kind = node->object_kind;

        if (kind)
        {
            if (kind & 2)
            {
                static_cast<LibTransformOwner*>(node)->matrix_ready = 0;
                static_cast<LibTransformOwner*>(node)->unk51 = 0;
            }

            if (kind & 1)
            {
                continue;
            }

            if (kind & 4)
            {
                ee_enter_scratchpad_stack();
                node->update();
                ee_leave_scratchpad_stack();
                continue;
            }
        }

        node->update();
    }

    active_node_index = -1;

    if (owned_node_buffer == 0)
    {
        delete[] active_node_buffer;
    }

    active_node_buffer = 0;

    if (next_list)
    {
        func_004D68F0(next_list, 0);
    }
}

// TODO: The target unrolls the recursion eight calls deep, which only happens with auto inlining and an inline depth
// of eight around it.
#pragma push
#pragma auto_inline on
#pragma inline_depth(8)

/**
 * @brief Give a list and every list chained after it the same active buffer owner.
 * @param list First list.
 * @param owner Owner of the active node buffer.
 */
extern "C" void func_004D68F0(LibUpdateList* list, LibUpdateList* owner)
{
    list->active_buffer_owner = owner;

    if (list->next_list)
    {
        func_004D68F0(list->next_list, owner);
    }
}

#pragma pop

// TODO: The target unrolls the recursion eight calls deep and calls the node count getter's out-of-line copy (kept
// in text_0046AE20) at the last level, so the getter is inline in this unit and auto inlining runs at depth eight.
#pragma push
#pragma auto_inline on
#pragma inline_depth(8)

/**
 * @brief Return how many nodes the list holds.
 * @return Node count.
 */
inline u32 LibListReceiver::get_node_count() const
{
    return node_count;
}

/**
 * @brief Count the nodes of a list and every list chained after it.
 * @param list First list.
 * @return Total node count.
 */
extern "C" s32 func_004D69A0(LibUpdateList* list)
{
    s32 count = list->get_node_count();

    if (list->next_list)
    {
        count += func_004D69A0(list->next_list);
    }

    return count;
}

#pragma pop

/**
 * @brief Collect the list chain's nodes into an array grouped by list kind.
 * @param list First list whose nodes are collected.
 * @param items Array with room for every node in the chain.
 */
extern "C" void lib_list_collect_nodes_by_kind(LibUpdateList* list, void** items)
{
    u32 offsets[LibUpdateList::NODE_KIND_COUNT];
    u32 count = 0;

    for (s32 kind = 0; kind < LibUpdateList::NODE_KIND_COUNT; ++kind)
    {
        offsets[kind] = count;
        count += list->node_counts_by_kind[kind];
    }

    if (list->next_list)
    {
        lib_list_add_chain_kind_offsets(list->next_list, offsets);
    }

    LibListSentinel* link = &list->sentinel;

    for (;;)
    {
        link = link->next;

        if (&list->sentinel == link)
        {
            break;
        }

        LibListObject* node = reinterpret_cast<LibListObject*>(link);
        items[offsets[node->list_kind]++] = node;
    }

    if (list->next_list)
    {
        func_004D6C20(list->next_list, items, offsets);
    }
}

// TODO: The target inlines the recursion three levels deep and calls the traversal helpers' out-of-line copies at the
// last level, so the helpers are inline here and auto inlining runs at depth three.
#pragma push
#pragma auto_inline on
#pragma inline_depth(3)

/**
 * @brief Read the signed index used to select a node output counter.
 * @param node Current list node.
 * @return The sign-extended index value.
 */
extern "C" inline s32 func_004D6DB0(const LibListNode* node)
{
    return node->unk0c;
}

/**
 * @brief Test whether a list traversal has reached its sentinel.
 * @param sentinel List sentinel.
 * @param node Current node.
 * @return True if node is the sentinel.
 */
extern "C" inline bool func_004D6DC0(const void* sentinel, const void* node)
{
    return sentinel == node;
}

/**
 * @brief Get the next node in a circular list traversal.
 * @param node Current node or list sentinel.
 * @return Next node, which may be the list sentinel.
 */
extern "C" inline LibListNode* func_004D6DD0(const LibListNode* node)
{
    return node->next;
}

/**
 * @brief Return the supplied object pointer.
 * @param object Object or subobject pointer.
 * @return The same pointer.
 */
extern "C" inline void* func_004D6DE0(void* object)
{
    return object;
}

/**
 * @brief Put the nodes of a list and every list chained after it into an array grouped by list kind.
 * @param list First list.
 * @param items Array with room for every node in the chain.
 * @param offsets Next free position for each list kind; advanced past each node placed.
 */
extern "C" void func_004D6C20(LibUpdateList* list, void** items, u32* offsets)
{
    LibListNode* node = static_cast<LibListNode*>(func_004D6DE0(list));

    for (;;)
    {
        node = func_004D6DD0(node);

        if (func_004D6DC0(list, node))
        {
            break;
        }

        items[offsets[func_004D6DB0(node)]++] = node;
    }

    if (list->next_list)
    {
        func_004D6C20(list->next_list, items, offsets);
    }
}

#pragma pop

/**
 * @brief Add each list's per-kind prefix sums to the chain's kind offsets.
 * @param list First list whose counts are added.
 * @param offsets Array of NODE_KIND_COUNT offsets to update.
 */
extern "C" inline void lib_list_add_chain_kind_offsets(LibUpdateList* list, u32* offsets)
{
    u32 count = 0;

    for (s32 kind = 0; kind < LibUpdateList::NODE_KIND_COUNT; ++kind)
    {
        offsets[kind] += count;
        count += list->node_counts_by_kind[kind];
    }

    if (list->next_list)
    {
        lib_list_add_chain_kind_offsets(list->next_list, offsets);
    }
}

/**
 * @brief Remove a registered node and clear its pending buffer entries.
 * @param object Node to remove.
 */
void LibUpdateList::remove_node(void* object)
{
    LibListObject* node = static_cast<LibListObject*>(object);
    --node_counts_by_kind[node->list_kind];
    node->is_listed = 0;
    node->owner = 0;
    void** buffer = active_node_buffer;

    if (buffer)
    {
        s32 count = active_node_count;
        s32 i = active_node_index + 1;

        for (; i < count; ++i)
        {
            if (buffer[i] == object)
            {
                buffer[i] = 0;
            }
        }
    }
    else if (active_buffer_owner)
    {
        s32 count = active_buffer_owner->active_node_count;
        void** owner_buffer = active_buffer_owner->active_node_buffer;
        s32 i = active_buffer_owner->active_node_index + 1;

        for (; i < count; ++i)
        {
            if (owner_buffer[i] == object)
            {
                owner_buffer[i] = 0;
            }
        }
    }

    LibListReceiver::unlink(object);
}

/**
 * @brief Transfer one node count from the node's stored kind to a new kind.
 * @param owner List whose per-kind counts are updated.
 * @param node Node supplying the old kind.
 * @param new_kind Kind whose count is incremented.
 */
extern "C" void lib_list_change_node_kind_counts(LibUpdateList* owner, const LibListObject* node, s32 new_kind)
{
    --owner->node_counts_by_kind[node->list_kind];
    ++owner->node_counts_by_kind[new_kind];
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", insert_node_after__13LibUpdateListFPvPvi);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", prepend_node__13LibUpdateListFPvi);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", append_node__13LibUpdateListFPvi);

/** @brief Destroy the list receiver and its sentinel. */
inline LibListReceiver::~LibListReceiver()
{
}

/** @brief Release the owned node buffer and destroy the list base. */
LibUpdateList::~LibUpdateList()
{
    delete[] owned_node_buffer;
}

/** @brief Initialize the inherited list, kind counts, and node-buffer state. */
LibUpdateList::LibUpdateList()
{
    for (s32 i = 0; i < NODE_KIND_COUNT; ++i)
    {
        node_counts_by_kind[i] = 0;
    }

    active_node_buffer = 0;
    next_list = 0;
    active_node_count = 0;
    unk58 = 0;
    active_node_index = -1;
    node_buffer_capacity = 0;
    owned_node_buffer = 0;
    active_buffer_owner = 0;
}

/**
 * @brief Set the default colours and cell size for the display's scale, put the cursor at a screen position and
 *        start the text packet with the font's drawing state.
 * @param x Left margin in screen pixels.
 * @param y Top line in screen pixels.
 */
void LibScreenText::begin(u16 x, u16 y)
{
    float scale_x;
    float scale_y;
    LibCameraContext* display;
    s32 top;
    s32 margin;
    LibScreenTextPacket* setup;
    u32 rgba;
    u64 tex0;

    if (packet == 0)
    {
        return;
    }

    color = 0x80FFFFFF;
    shadow_color = 0x80101010;
    g_display->get_area_scale(&scale_x, &scale_y);
    cell_width = (u8)(s32)(LIB_SCREEN_TEXT_CELL_SIZE * scale_x);
    cell_height = (u8)(s32)(0.5f * (LIB_SCREEN_TEXT_CELL_SIZE * scale_y));
    display = g_display;
    top = GS_COORDINATE_CENTRE - display->display_area.height / 2;
    margin = GS_COORDINATE_CENTRE - display->display_area.width / 2;
    left = cursor_x = (x + margin) << 4;
    cursor_y = (y + top) << 4;
    resident_packet_rewind(packet);
    setup = (LibScreenTextPacket*)resident_packet_reserve(packet, 0);

    if (setup == 0)
    {
        return;
    }

    setup->tag.tag = GIF_TAG_NREG(1) | 4;
    setup->tag.registers = 0;
    setup->tag.fields.register0 = GIF_REGISTER_AD;
    tex0 = (u64)g_vram_allocator->unk04[LIB_SCREEN_TEXT_FONT_SLOT] | LIB_SCREEN_TEXT_FONT_TEX0;
    setup->tex0 = tex0 | func_004DC800(g_vram_allocator, LIB_SCREEN_TEXT_FONT_SLOT, 0, 1);
    setup->tex0_address = GS_REGISTER_TEX0_2;
    setup->alpha = GS_ALPHA_NORMAL;
    setup->alpha_address = GS_REGISTER_ALPHA_2;
    setup->prim = LIB_SCREEN_TEXT_PRIM;
    setup->prim_address = GS_REGISTER_PRIM;
    rgba = color;
    setup->rgba = (rgba & 0xFF) | ((rgba >> 8) & 0xFF) << 8 | ((rgba >> 16) & 0xFF) << 16 | (rgba & 0xFF000000);
    setup->q = 1.0f;
    setup->rgbaq_address = GS_REGISTER_RGBAQ;
    resident_packet_align_cursor(packet, (u8*)(setup + 1));
}

/**
 * @brief Load and decode the font unless one is attached, upload it to its VRAM slot and restart the text at the
 *        top-left corner.
 */
void LibScreenText::load_font()
{
    u8* data;

    if (font_image == 0)
    {
        data = new (0) u8[resident_get_resource_size(g_resource_archive, LIB_SCREEN_TEXT_FONT_KEY)];
        resident_queue_resource_request(g_resource_queue, LIB_SCREEN_TEXT_FONT_KEY, data, LIB_SCREEN_TEXT_FONT_TAG, LIB_SCREEN_TEXT_FONT_PRIORITY, 0, 0, 0, 1);

        while (resident_find_resource_request(g_resource_queue, LIB_SCREEN_TEXT_FONT_KEY, (u32)data, LIB_SCREEN_TEXT_FONT_TAG, 0xFFFFFFFF, 0))
        {
        }

        font_image = resident_allocate_decode_buffer(g_resident_resource_decoder, (ResidentResourceHeader*)data, 0, 0);
        resident_decode_resource_block(g_resident_resource_decoder, (ResidentResourceHeader*)data, font_image, 0);
        operator delete(data);
        FlushCache(0);
        shared_font = 0;
    }

    func_004D8D20(font_image, LIB_SCREEN_TEXT_FONT_SLOT);
    begin(0, 0);
}

/** @brief Blend each selected palette entry between its start and end color by the blend weight, on VU0. */
void LibPaletteBlendChannel::update()
{
    if (target != 0)
    {
        LibImageHeader* image = target;
        float weights[4] __attribute__((aligned(16)));
        LibImagePalette* palette = reinterpret_cast<LibImagePalette*>(reinterpret_cast<u8*>(image) + image->palette_offset);
        weights[0] = blend;
        u32* colors = reinterpret_cast<u32*>(reinterpret_cast<u32>(palette->colors) | EE_UNCACHED_ACCELERATED);
        weights[1] = 1.0f - blend;
        vu0_load_vf3(weights);

        for (s32 i = 0; i < entry_count; i++)
        {
            u32* slot = &colors[palette_indices[i]];
            const LibVector4* start = &start_colors[i];
            const LibVector4* end = &end_colors[i];
            *slot = vu0_blend_color(start, end);
        }
    }
}

/**
 * @brief Bind the selected image from the source resource.
 *
 * A nonempty record list with no matching selector reports success and keeps
 * the previous target. Failed lookups also leave that target unchanged.
 * @param model Model the channel belongs to; unused.
 * @return False for a missing resource, empty record list or unsupported matching storage kind; true otherwise.
 */
bool LibPaletteBlendChannel::load_resource(LibModel* model)
{
    if (resource == 0)
    {
        return false;
    }

    u8* payload = lib_resource_payload(resource);
    u32 first = reinterpret_cast<LibResourcePayloadHeader*>(payload)->data_offset;

    if (first)
    {
        for (LibRenderDataRecord* record = reinterpret_cast<LibRenderDataRecord*>(payload + first); ; )
        {
            s16 kind = record->storage_kind;

            if (record->index == unk38)
            {
                if (kind == RENDER_DATA_INLINE || kind == RENDER_DATA_RESOLVED)
                {
                    if (record->data)
                    {
                        target = static_cast<LibImageHeader*>(record->data);
                    }
                    else
                    {
                        target = reinterpret_cast<LibImageHeader*>(reinterpret_cast<u8*>(record) + sizeof(LibRenderDataRecord) + sizeof(LibResourceChunkHeader));
                    }

                    break;
                }
                else
                {
                    return false;
                }
            }

            if (record->next_offset == 0)
            {
                break;
            }

            record = reinterpret_cast<LibRenderDataRecord*>(payload + record->next_offset);
        }
    }
    else
    {
        return false;
    }

    return true;
}

/** @brief Flush the data cache and initialize an empty palette blend. */
LibPaletteBlendChannel::LibPaletteBlendChannel()
{
    FlushCache(0);
    start_colors = 0;
    end_colors = 0;
    palette_indices = 0;
    entry_count = 0;
    blend = 0;
    target = 0;
    unk40 = 2;
}

/**
 * @brief Select the image for the stored frame position.
 *
 * The sequence duration must be nonzero and covered by its frame durations.
 */
void LibImageSequenceChannel::update()
{
    s32 remaining;
    s32 cycle;
    s32 index;
    const LibImageSequenceEntry* frame_info;
    u32 duration;
    LibRenderDataRecord* record;
    const LibImageSequenceHeader* header;

    record = target;

    if (record)
    {
        header = sequence;
        duration = header->duration;
        remaining = frame % duration;
        cycle = frame / duration;

        if (frame < 0)
        {
            cycle--;
        }

        if (cycle != 0)
        {
            switch (header->playback_mode)
            {
                case IMAGE_SEQUENCE_PING_PONG:
                    if (cycle & 1)
                    {
                        remaining = duration - remaining - 1;
                    }

                    break;
                case IMAGE_SEQUENCE_CLAMP:
                    if (cycle > 0)
                    {
                        remaining = duration - 1;
                    }

                    if (cycle < 0)
                    {
                        remaining = 0;
                    }

                    break;
            }
        }

        index = 0;
        frame_info = reinterpret_cast<const LibImageSequenceEntry*>(header + 1);

        for (; index < header->entry_count; index++)
        {
            remaining -= frame_info[index].duration;

            if (remaining < 0)
            {
                break;
            }
        }

        record->data = entries[index];
    }
}

/**
 * @brief Bind a resource record and build its image-pointer table.
 *
 * Offsets are relative to the first image chunk in the chain.
 * Rebinding does not release an older entry table.
 * @param record Resource record containing inline or resolved image chunks.
 * @param use_inline True to select inline chunks even when a data pointer is set.
 * @return True when a sequence is found and its pointer table is allocated.
 */
bool LibImageSequenceChannel::bind_record(LibRenderDataRecord* record, bool use_inline)
{
    target = record;

    if (target)
    {
        LibResourceChunkHeader* chunk;
        u8* base;

        if (target->data == 0 || use_inline)
        {
            chunk = reinterpret_cast<LibResourceChunkHeader*>(target + 1);
            base = reinterpret_cast<u8*>(chunk);
        }
        else
        {
            chunk = reinterpret_cast<LibResourceChunkHeader*>(static_cast<u8*>(target->data) - sizeof(LibResourceChunkHeader));
            base = reinterpret_cast<u8*>(chunk);
        }

        for (;;)
        {
            if (chunk->magic == IMAGE_SEQUENCE_MAGIC)
            {
                break;
            }

            chunk = lib_next_chunk(chunk);

            if (chunk == 0)
            {
                return false;
            }
        }

        sequence = reinterpret_cast<LibImageSequenceHeader*>(chunk + 1);
        entries = new(0) void*[sequence->entry_count];

        if (entries == 0)
        {
            return false;
        }

        const LibImageSequenceEntry* entry = reinterpret_cast<const LibImageSequenceEntry*>(sequence + 1);

        for (s32 index = 0; index < sequence->entry_count; index++, entry++)
        {
            entries[index] = base + entry->data_offset;
        }
    }
    else
    {
        return false;
    }

    return true;
}

/**
 * @brief Bind the selected record from the source resource.
 * @return True when no record is bound or binding succeeds; false for a missing resource or failed binding.
 */
bool LibImageSequenceChannel::load_resource()
{
    if (resource == 0)
    {
        return false;
    }

    u8* payload = lib_resource_payload(resource);
    target = 0;
    u32 first = reinterpret_cast<LibResourcePayloadHeader*>(payload)->data_offset;

    if (first)
    {
        for (LibRenderDataRecord* record = reinterpret_cast<LibRenderDataRecord*>(payload + first); ;)
        {
            s16 kind = record->storage_kind;

            if (record->index == unk38)
            {
                if (kind == RENDER_DATA_OFFSET)
                {
                    record->data = reinterpret_cast<u8*>(record) + record->data_offset;
                    record->resolved_data = record->data;
                    record->storage_kind = RENDER_DATA_RESOLVED;
                    return bind_record(record, false);
                }

                if (kind == RENDER_DATA_RESOLVED)
                {
                    record->data = record->resolved_data;
                    return bind_record(record, false);
                }

                if (kind == RENDER_DATA_INLINE)
                {
                    return bind_record(record, true);
                }

                if (kind == RENDER_DATA_SHARED)
                {
                    LibRenderDataRecord* shared = func_00448910(record->key08, record->key0c);

                    if (shared)
                    {
                        return bind_record(shared, true);
                    }
                }
            }

            if (record->next_offset == 0)
            {
                break;
            }

            record = reinterpret_cast<LibRenderDataRecord*>(payload + record->next_offset);
        }
    }

    return true;
}

/** @brief Release the image-pointer table and destroy the channel base. */
LibImageSequenceChannel::~LibImageSequenceChannel()
{
    delete[] entries;
}

/** @brief Initialize an empty image-sequence channel. */
LibImageSequenceChannel::LibImageSequenceChannel()
{
    resource = 0;
    entries = 0;
    sequence = 0;
    frame = 0;
    unk40 = 1;
    target = 0;
}

/**
 * @brief Append DMA references for the active texture transfers.
 * @param packet Packet cursor with room for up to four DMA tags.
 * @return Packet cursor after the appended tags.
 */
void* LibTextureScrollChannel::append_packets(void* packet)
{
    DmaSourceTag* cursor = static_cast<DmaSourceTag*>(packet);

    for (s32 i = 0; i < TRANSFER_COUNT; i++)
    {
        if (transfer_enabled[i])
        {
            cursor->control = (static_cast<u64>(reinterpret_cast<u32>(&transfers[i])) << 32) | (DMA_TAG_REFERENCE | TEXTURE_TRANSFER_QUADWORDS);
            cursor++;
        }
    }

    return cursor;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", prepare_packets__23LibTextureScrollChannelFP12LibTransformUi);

/** @brief Initialize four inactive texture-transfer templates. */
LibTextureScrollChannel::LibTextureScrollChannel()
{
    y_offset = 0;
    x_offset = 0;
    FlushCache(0);
    unk40 = 0;
    LibTextureTransferPacket* packet = reinterpret_cast<LibTextureTransferPacket*>(reinterpret_cast<u32>(transfers) | 0x30000000);

    for (s32 i = 0; i < TRANSFER_COUNT; i++, packet++)
    {
        memset_guess(packet, 0, sizeof(LibTextureTransferPacket));
        packet->vif_unpack[0] = 0;
        packet->vif_unpack[1] = 0;
        packet->vif_unpack[2] = 0;
        packet->vif_unpack[3] = TEXTURE_TRANSFER_VIF_UNPACK;
        packet->gif_tag = TEXTURE_TRANSFER_GIF_TAG;
        packet->gif_registers = GIF_REGISTER_AD;
        packet->buffer_register = GS_REGISTER_BITBLTBUF;
        packet->position_register = GS_REGISTER_TRXPOS;
        packet->size_register = GS_REGISTER_TRXREG;
        packet->direction = GS_TRANSFER_LOCAL_TO_LOCAL;
        packet->direction_register = GS_REGISTER_TRXDIR;
        packet->texture_flush_register = GS_REGISTER_TEXFLUSH;
        packet->unk74 = 0;
        packet->unk78 = 0;
        packet->vif_flush = TEXTURE_TRANSFER_VIF_FLUSH;
        transfer_enabled[i] = 0;
    }
}

/**
 * @brief Report the stored sequence's image count.
 * @return Image count, or zero when no sequence header is stored.
 */
s32 LibImageSequenceChannel::get_entry_count()
{
    if (sequence)
    {
        return sequence->entry_count;
    }

    return 0;
}

/**
 * @brief Read an indexed image pointer.
 * @param index Caller-validated image index.
 * @return Image pointer at index.
 */
void* LibImageSequenceChannel::get_entry(s32 index)
{
    return entries[index];
}

/** @brief Destroy the channel and its intrusive-link base. */
LibTextureScrollChannel::~LibTextureScrollChannel()
{
}

/**
 * @brief Compare two strings for equality up to a signed character limit.
 * @param first First string.
 * @param second Second string.
 * @param count Maximum characters to compare; nonpositive limits compare none.
 * @return Zero when the compared characters match, otherwise one.
 */
extern "C" s32 lib_compare_bounded_strings(const char* first, const char* second, s32 count)
{
    s32 index;

    for (index = 0; index < count; index++)
    {
        if (first[index] != second[index])
        {
            return 1;
        }

        if (first[index] == 0)
        {
            return 0;
        }
    }

    return 0;
}

#define LIB_VRAM_CLEAR_SIZE 256

/** @brief Fill all of VRAM with zeros, one 256x256 32-bit upload at a time. */
void lib_clear_vram(void)
{
    GsLoadImage image;
    u8* zeros;
    s32 pass;

    resident_sync_gs_path(resident_system_get_input(resident_get_system()), 0, 0);
    zeros = new (0) u8[LIB_VRAM_CLEAR_SIZE * LIB_VRAM_CLEAR_SIZE * sizeof(u32)];

    if (zeros == 0)
    {
        return;
    }

    memset_guess(zeros, 0, LIB_VRAM_CLEAR_SIZE * LIB_VRAM_CLEAR_SIZE * sizeof(u32));

    for (pass = 0; pass < GS_VRAM_WORDS / (LIB_VRAM_CLEAR_SIZE * LIB_VRAM_CLEAR_SIZE); pass++)
    {
        sceGsSetDefLoadImage(&image, pass * (LIB_VRAM_CLEAR_SIZE * LIB_VRAM_CLEAR_SIZE) / GS_VRAM_BLOCK_WORDS,
                             LIB_VRAM_CLEAR_SIZE / GS_BUFFER_WIDTH_PIXELS, GS_PSMCT32, 0, 0, LIB_VRAM_CLEAR_SIZE, LIB_VRAM_CLEAR_SIZE);
        FlushCache(0);
        sceGsExecLoadImage(&image, zeros);
        resident_sync_gs_path(resident_system_get_input(resident_get_system()), 0, 0);
    }

    operator delete(zeros);
}

/**
 * @brief Set the area and depth that new colour fades use.
 * @param rect Area in screen pixels.
 * @param depth Depth the fades draw at.
 */
extern "C" void lib_set_color_fade_area(const LibScreenRect* rect, s32 depth)
{
    D_0050CD40 = *rect;
    D_001B6694 = depth;
}

/** @brief Rebuild Lib's frame packet, which resets the context-2 drawing state, and send it. */
void lib_begin_frame_packet(void)
{
    LibFramePacket* packet;

    resident_packet_rewind(&D_0050CD60);
    packet = (LibFramePacket*)resident_packet_reserve(&D_0050CD60, 0);
    packet->tag.tag = GIF_TAG_NREG(1) | GIF_TAG_EOP | LIB_FRAME_PACKET_REGISTER_COUNT;
    packet->tag.registers = 0;
    packet->tag.fields.register0 = GIF_REGISTER_AD;
    packet->registers[0].data = 1;
    packet->registers[0].address = GS_REGISTER_TEXFLUSH;
    packet->registers[1].data = 4;
    packet->registers[1].address = GS_REGISTER_TEXCLUT;
    packet->registers[2].data = 0x61;
    packet->registers[2].address = GS_REGISTER_TEX1_2;
    packet->registers[3].data = GS_ALPHA_NORMAL;
    packet->registers[3].address = GS_REGISTER_ALPHA_2;
    packet->registers[4].data = 0x5000D;
    packet->registers[4].address = GS_REGISTER_TEST_2;
    packet->registers[5].data = 0;
    packet->registers[5].address = GS_REGISTER_FBA_2;
    packet->registers[6].data = 0;
    packet->registers[6].address = GS_REGISTER_PABE;
    packet->registers[7].data = 1;
    packet->registers[7].address = GS_REGISTER_PRMODECONT;
    packet->registers[8].data = 0x8000008080ULL;
    packet->registers[8].address = GS_REGISTER_TEXA;
    packet->registers[9].data = 0xFFFFFFF0ULL;
    packet->registers[9].address = GS_REGISTER_CLAMP_1;
    packet->registers[10].data = 0xFFFFFFF0ULL;
    packet->registers[10].address = GS_REGISTER_CLAMP_2;
    packet++;
    resident_packet_align_cursor(&D_0050CD60, (u8*)packet);
    resident_packet_submit(&D_0050CD60, 0);
}

/** Packet that loads a 16 by 16 CT32 image into VRAM, with the pixels it reads. */
struct LibImageUpload16
{
    GsLoadImage image;
    const void* colors;
};

extern "C" s16 func_004DC970(LibVramAllocator* vram, s16 format, s16 size, s32 slot);

/** "Vram exhaused\n" */
extern "C" const char D_00507270[];

/**
 * @brief Reserve VRAM for a 16 by 16 CT32 image and queue its upload.
 * @param colors Pixels to upload.
 * @param slot VRAM slot to reuse, or -1 for a new one.
 * @return The slot, or -1 when the packet can't be allocated.
 */
extern "C" s16 func_004D8C20(const void* colors, s32 slot)
{
    LibImageUpload16* upload = new (0) LibImageUpload16;

    if (upload == 0)
    {
        return -1;
    }

    s32 index = func_004DC970(g_vram_allocator, 0, 0x100, slot);

    if (index == -1)
    {
        printf(D_00507270);
    }

    sceGsSetDefLoadImage(&upload->image, (g_vram_allocator->allocations[index] >> 5) & 0x3FFF, 1, 0, 0, 0, 16, 16);
    upload->colors = colors;
    FlushCache(0);
    func_004DC4F0(g_packet_queue, 1, 1, upload, 0, 0);
    return index;
}

extern "C" s16 func_004DCB30(LibVramAllocator* vram, s16 format, s16 width, s16 height, s32 slot);

/**
 * @brief Reserve VRAM for an image and its palette and queue their uploads.
 * @param image Image chunk.
 * @param slot VRAM slot to reuse, or -1 for a new one.
 * @return The image's slot in the low half and the palette's in the high half, or -1 when a packet can't be
 *         allocated.
 */
s32 func_004D8D20(u8* image, s32 slot)
{
    s16 palette_index;
    LibImageHeader* header;
    LibImageInfo* info;

    header = reinterpret_cast<LibImageHeader*>(image + 0x10);
    palette_index = 0;
    info = reinterpret_cast<LibImageInfo*>(reinterpret_cast<u8*>(header) + header->image_offset);

    if (header->unk02 != 0)
    {
        LibImageUpload16* upload = new (0) LibImageUpload16;

        if (upload == 0)
        {
            return -1;
        }

        LibImagePalette* palette = reinterpret_cast<LibImagePalette*>(reinterpret_cast<u8*>(header) + header->palette_offset);
        palette_index = func_004DC970(g_vram_allocator, header->palette_format, header->palette_size / 4, slot);

        if (palette_index == -1)
        {
            printf(D_00507270);
        }

        sceGsSetDefLoadImage(&upload->image, (g_vram_allocator->allocations[palette_index] >> 5) & 0x3FFF,
                             (palette->bitbltbuf >> 48) & 0x3F, header->palette_format, 0, 0, palette->trxreg & 0xFFF,
                             (palette->trxreg >> 32) & 0xFFF);
        upload->colors = palette->colors;
        FlushCache(0);
        func_004DC4F0(g_packet_queue, 1, 1, upload, 0, 0);
    }

    s32 width = info->width;
    s32 height = info->height;
    s32 format = info->texture_code;
    s32 area_width;
    s32 area_height;
    s32 area_format;

    if (header->flags & LIB_IMAGE_SWIZZLED)
    {
        switch (format)
        {
        case 0x14:
            area_width = width << 1;
            area_height = height << 2;
            break;
        case 0x13:
            area_width = width << 1;
            area_height = height << 1;
            break;
        case 2:
        case 0xA:
            area_width = width;
            area_height = height << 1;
            break;
        default:
            area_width = width;
            area_height = height;
            break;
        }

        area_format = format;
        format = 0;
    }
    else
    {
        area_width = width;
        area_height = height;
        area_format = format;
    }

    u8* pixels = reinterpret_cast<u8*>(header) + info->pixel_offset;
    s16 index = func_004DCB30(g_vram_allocator, area_format, area_width, area_height, slot);

    if (index == -1)
    {
        printf(D_00507270);
    }

    LibImageUpload16* upload = new (0) LibImageUpload16;

    if (upload == 0)
    {
        return -1;
    }

    sceGsSetDefLoadImage(&upload->image, g_vram_allocator->unk04[index] & 0x3FFF, width >> 6, format, 0, 0, width,
                         height);
    upload->colors = pixels + 0x80;
    FlushCache(0);
    func_004DC4F0(g_packet_queue, 1, 1, upload, 0, 0);
    return index | palette_index << 16;
}

/**
 * @brief Stop the channel 8 queue and start a 0x291-quadword transfer from the scratchpad.
 * @param address Main memory address.
 * @param scratchpad Scratchpad address.
 */
extern "C" void func_004D9030(void* address, void* scratchpad)
{
    ResidentDmaQueue* queue = D_001B6604;
    queue->current = 0;
    DisableDmac(queue->channel);
    *D8_MADR = (u32)address;
    *D8_SADR = (u32)scratchpad;
    *D8_QWC = 0x291;
    *D_STAT = D_STAT_CIS8;
    *D_PCR = D_PCR_CPC8;
    *D8_CHCR = DMA_CHCR_START | DMA_CHCR_DIR_FROM_MEMORY;
}

/**
 * @brief Stop the channel 9 queue and start a 0x291-quadword transfer to the scratchpad.
 * @param address Main memory address.
 * @param scratchpad Scratchpad address.
 */
extern "C" void func_004D90B0(void* address, void* scratchpad)
{
    ResidentDmaQueue* queue = D_001B6608;
    queue->current = 0;
    DisableDmac(queue->channel);
    *D9_MADR = (u32)address;
    *D9_SADR = (u32)scratchpad;
    *D9_QWC = 0x291;
    *D_STAT = D_STAT_CIS9;
    *D_PCR = D_PCR_CPC9;
    *D9_CHCR = DMA_CHCR_START | DMA_CHCR_DIR_FROM_MEMORY;
}

/**
 * @brief Check whether no lookup has stamped a block since the stamps were cleared.
 * @param block Block to check.
 * @return Whether the block has no stamp.
 */
static inline bool lib_texture_block_expired(const LibTextureBlock* block)
{
    if (block->stamp)
    {
        return false;
    }

    return true;
}

/** @brief Release every block no lookup has stamped since the stamps were cleared; with none stamped, empty the cache. */
void LibTextureCache::release_unstamped()
{
    LibTextureBlock* list = blocks;
    bool stamped = false;
    u32 index;

    for (index = list[0].next_block; index != 0; index = list[index].next_block)
    {
        if (lib_texture_block_expired(&list[index]))
        {
            continue;
        }

        stamped = true;
        break;
    }

    if (stamped)
    {
        for (index = list[0].next_block; index != 0;)
        {
            u32 next_block = list[index].next_block;

            if (list[index].stamp == 0)
            {
                release_block(index);
            }

            index = next_block;
        }
    }
    else
    {
        reset();
    }
}

/**
 * @brief Detach the user from every cached copy of a texture.
 * @param tag Texture tag.
 * @param id Texture ID.
 */
void LibTextureCache::detach_user(u32 tag, u32 id)
{
    for (u32 index = next[0]; index != 0; index = next[index])
    {
        if (blocks[index].id == id && entries[index].tag == tag)
        {
            entries[index].user = 0;
        }
    }
}

/**
 * @brief Release the most recently used cached copy of a texture.
 * @param tag Texture tag.
 * @param id Texture ID.
 */
void LibTextureCache::release_texture(u32 tag, u32 id)
{
    for (u32 index = next[0]; index != 0; index = next[index])
    {
        if (blocks[index].id == id && entries[index].tag == tag)
        {
            release_block(index);
            return;
        }
    }
}

/**
 * @brief Clear the stamp of every block holding a texture ID, and the cache's own stamp.
 * @param id Texture ID.
 */
void LibTextureCache::expire_texture(u32 id)
{
    stamp = 0;

    for (u32 index = blocks[0].next_block; index != 0; index = blocks[index].next_block)
    {
        if (blocks[index].id == id)
        {
            blocks[index].stamp = 0;
        }
    }
}

/**
 * @brief Build the CLUT half of TEX0 for the CLUT a slot last found.
 * @param slot Slot whose CLUT to use.
 * @param entry CLUT entry offset (CSA).
 * @param load_mode 0 to always load the CLUT, 1 to load it and keep CBP 0, 2 not to load it; anything else loads it
 *        and keeps CBP 1.
 * @return CBP, CPSM, CSA and CLD in TEX0's layout.
 */
u64 LibTextureCache::get_clut_tex0(s16 slot, s16 entry, s32 load_mode)
{
    u64 csa = GS_TEX0_CSA((u32)(entry & 0x1F));
    u64 cld;

    switch (load_mode)
    {
    case 0:
        cld = GS_TEX0_CLD(1);
        break;
    case 1:
        cld = GS_TEX0_CLD(2);
        break;
    case 2:
        cld = 0;
        break;
    default:
        cld = GS_TEX0_CLD(4);
        break;
    }

    return cld | (cluts[clut_slot_entries[slot]].tex0 | csa);
}

/**
 * @brief Look up a cached texture, loading it on a miss.
 * @param request Texture to load on a miss, or null to only look.
 * @param tag Request tag.
 * @param id Texture ID.
 * @param slot Slot whose last hit is recorded.
 * @param unk5 Passed to the loader on a miss.
 * @param want_address Nonzero to return the texture's VRAM address.
 * @param user Object whose priority a hit on a user-owned texture lowers.
 * @return VRAM word address of the texture, or 0.
 */
u32 LibTextureCache::find_texture(LibTextureRequest* request, u32 tag, s32 id, s32 slot, u16 unk5, s32 want_address, LibTextureUser* user)
{
    u32 index;

    for (index = next[0]; index != 0; index = next[index])
    {
        if (blocks[index].id == id && entries[index].tag == tag)
        {
            blocks[index].stamp = stamp;

            if (entries[index].user == 0)
            {
                if (next[0] != index)
                {
                    move_to_front(index);
                }

                slot_entries[slot] = index;

                // TODO: hits only test the flag's low byte and the miss path tests all of it; I'm not sure why yet.
                if (!(u8)want_address)
                {
                    return 0;
                }

                return (entries[index].tex0 & 0x3FFF) * GS_VRAM_BLOCK_WORDS;
            }
            else
            {
                s32 priority = entries[index].user->priority;

                if (next[0] != index && priority >= LIB_TEXTURE_PRIORITY_KEEP)
                {
                    move_to_front(index);
                }

                slot_entries[slot] = index;

                if (!(u8)want_address)
                {
                    priority++;
                    priority = clamp_high(priority, LIB_TEXTURE_PRIORITY_MAX);
                    entries[index].user->priority = priority;
                    return 0;
                }

                priority -= 2;
                priority = clamp_low(priority, LIB_TEXTURE_PRIORITY_MIN);
                user->priority = priority;
                return (entries[index].tex0 & 0x3FFF) * GS_VRAM_BLOCK_WORDS;
            }
        }
    }

    if ((tag == LIB_TEXTURE_TAG_MLPS && !want_address) || request == 0)
    {
        return 0;
    }

    return func_004A7100(this, request, tag, id, slot, unk5, user);
}

/**
 * @brief Release every loaded block that overlaps the last part of the texture area.
 * @param size Size of the part, counted back from the end of the area.
 */
void LibTextureCache::release_area_end(u32 size)
{
    u32 index = blocks[0].next_block;
    u32 start;
    u32 end = texture_address + texture_size;
    start = end - size;

    for (; index != 0; index = blocks[index].next_block)
    {
        if (blocks[index].state == 1)
        {
            u32 first = blocks[index].address;
            u32 last = first + blocks[index].size;

            if ((first >= start && first < end) || (last >= start && last < end) || (start >= first && last > end))
            {
                release_block(index);
            }
        }
    }
}

/** @brief Empty the cache: one free block over the whole texture area, no textures and no CLUTs. */
void LibTextureCache::reset()
{
    for (s32 index = 0; index < LIB_TEXTURE_CACHE_ENTRY_COUNT; index++)
    {
        blocks[index].state = LIB_TEXTURE_BLOCK_UNUSED;
        slot_entries[index] = 0;
    }

    s32 count = clut_count;

    for (s32 index = 0; index < count; index++)
    {
        clut_used[index] = 0;
        cluts[index].id = 0;
        clut_slot_entries[index] = 0;
    }

    blocks[1].address = texture_address;
    blocks[1].size = texture_size;
    blocks[1].previous_block = 0;
    blocks[1].next_block = 0;
    blocks[1].state = LIB_TEXTURE_BLOCK_FREE;
    blocks[0].address = 0;
    blocks[0].size = 0;
    blocks[0].stamp = 0;
    blocks[0].previous_block = 1;
    blocks[0].next_block = 1;
    blocks[0].state = LIB_TEXTURE_BLOCK_HEAD;
    blocks[0].id = 0;
    unk04 = 2;
    next[0] = 0;
    previous[0] = 0;
    next_clut = 0;
    unk220c = 0;
    stamp = 0;
}

#define LIB_TEXTURE_CACHE_MIN_CLUTS 8
#define LIB_TEXTURE_CACHE_TEXTURE_ALIGNMENT 0x800
#define LIB_TEXTURE_CACHE_CLUT_BYTES 0x100
#define LIB_VRAM_NEW_SLOT -1

/** "Too many clut size.\n" */
extern "C" const char lib_texture_cache_clut_error[];

/** "Cannot allocate vram cache.\n" */
extern "C" const char lib_texture_cache_vram_error[];

/**
 * @brief Allocate an aligned area from the texture side of the VRAM allocator.
 * @param vram Allocator.
 * @param size Size in bytes.
 * @param alignment Alignment in bytes.
 * @param slot Slot to reuse, or LIB_VRAM_NEW_SLOT.
 * @return Slot of the area, or -1 when VRAM is full.
 */
extern "C" s16 func_004DCA70(LibVramAllocator* vram, u32 size, u32 alignment, s16 slot);

/**
 * @brief Allocate an area from the CLUT side of the VRAM allocator.
 * @param vram Allocator.
 * @param size Size in bytes.
 * @param slot Slot to reuse, or LIB_VRAM_NEW_SLOT.
 * @return Slot of the area, or -1 when VRAM is full.
 */
extern "C" s16 func_004DC8B0(LibVramAllocator* vram, u32 size, s16 slot);

/**
 * @brief Allocate the texture and CLUT areas in VRAM and reset the cache.
 * @param size Size of the texture area in bytes.
 * @param count Number of CLUTs to hold; rounded up to a power of two, at least 8. At most 64.
 */
LibTextureCache::LibTextureCache(s32 size, s32 count)
{
    if (count > LIB_TEXTURE_CACHE_MAX_CLUTS)
    {
        printf(lib_texture_cache_clut_error);
        throw;
    }

    s32 capacity = 1;

    if (count > 1)
    {
        do
        {
            capacity <<= 1;
        } while (capacity < count);
    }

    if (capacity < LIB_TEXTURE_CACHE_MIN_CLUTS)
    {
        capacity = LIB_TEXTURE_CACHE_MIN_CLUTS;
    }

    texture_slot = func_004DCA70(g_vram_allocator, size, LIB_TEXTURE_CACHE_TEXTURE_ALIGNMENT, LIB_VRAM_NEW_SLOT);
    clut_slot = func_004DC8B0(g_vram_allocator, capacity * LIB_TEXTURE_CACHE_CLUT_BYTES, LIB_VRAM_NEW_SLOT);
    texture_address = (g_vram_allocator->unk04[texture_slot] & 0x3FFF) << 6;
    clut_address = ((g_vram_allocator->allocations[texture_slot] >> 5) & 0x3FFF) << 6;
    texture_size = size;
    clut_count = capacity;
    reset();

    if (!is_allocated())
    {
        printf(lib_texture_cache_vram_error);
        throw;
    }
}

LibTextureCache::LibTextureCache()
{
}

extern "C" void func_004D99B0(LibBusyObject* object)
{
    while (object->busy)
    {
    }
}

/** Global VIF0 tag chains for the low channel numbers. */
extern "C" u32 D_001B62A0[2];

/**
 * @brief Mark the transfer done.
 * @param dma_channel DMA channel; unused.
 */
void LibVif0Channel::complete_dma(u32 dma_channel)
{
    busy = 0;
}

/**
 * @brief Start the channel's VIF0 tag chain.
 * @param dma_channel DMA channel; unused.
 */
void LibVif0Channel::submit_dma(u32 dma_channel)
{
    if (channel >= 0x80)
    {
        *D0_QWC = 0;
        *D0_TADR = tags[channel - 0x80];
        *D_STAT = D_STAT_CIS0;
        *D0_CHCR = DMA_CHCR_START | DMA_CHCR_TAG_TRANSFER | DMA_CHCR_MODE_CHAIN | DMA_CHCR_DIR_FROM_MEMORY;
    }
    else
    {
        *D0_QWC = 0;
        *D0_TADR = D_001B62A0[channel];
        *D_STAT = D_STAT_CIS0;
        *D0_CHCR = DMA_CHCR_START | DMA_CHCR_TAG_TRANSFER | DMA_CHCR_MODE_CHAIN | DMA_CHCR_DIR_FROM_MEMORY;
    }
}

/**
 * @brief Queue the object for DMA after marking it busy and storing its channel.
 * @param object Transfer object implementing the DMA callbacks.
 * @param channel DMA channel selector stored at offset 0x51.
 * @return Queue insertion result.
 */
extern "C" s32 func_004D9A80(LibBusyObject* object, u8 channel)
{
    object->busy = 1;
    object->channel = channel;
    // The queue invokes the submission callbacks through the object's vtable.
    return resident_dma_queue_push(D_001B660C, reinterpret_cast<DmaSubmission*>(object));
}

/**
 * @brief Queue the object again when its DMA channel changes.
 * @param object Transfer object implementing the DMA callbacks.
 * @param channel Requested DMA channel.
 */
extern "C" void func_004D9AB0(LibBusyObject* object, u8 channel)
{
    if (object->channel == channel)
    {
        return;
    }

    object->busy = 1;
    object->channel = channel;
    resident_dma_queue_push(D_001B660C, reinterpret_cast<DmaSubmission*>(object));
}

/** @brief Start idle with no channel and seed VU0's random register. */
LibVif0Channel::LibVif0Channel()
{
    channel = 0xFF;
    busy = 0;
    unk54 = 0;
    vu0_random_seed(resident_next_random_word());
}

/**
 * @brief Nothing to do once the upload finishes.
 * @param channel DMA channel; unused.
 */
void LibMicrocodeLoader::complete_dma(u32 channel)
{
}

/**
 * @brief Send the resident microcode upload chain on VIF1.
 * @param channel DMA channel; unused.
 */
void LibMicrocodeLoader::submit_dma(u32 channel)
{
    *D1_QWC = 0;
    *D1_TADR = reinterpret_cast<u32>(lib_vu1_upload_chain);
    *D_STAT = D_STAT_CIS1;
    *D1_CHCR = DMA_CHCR_START | DMA_CHCR_TAG_TRANSFER | DMA_CHCR_MODE_CHAIN | DMA_CHCR_DIR_FROM_MEMORY;
}

/** DMA tags that upload each VU1 microprogram, in program order. */
struct LibProgramTagTable
{
    const u64* tags[LIB_VU1_PROGRAM_COUNT];
};

extern "C" const LibProgramTagTable D_004ED3B0;

/**
 * @brief Return the DMA tag that uploads a microprogram.
 * @param program Program index.
 * @return DMA REF tag.
 */
u64 LibMicrocodeLoader::get_program_tag(s32 program)
{
    LibProgramTagTable table = D_004ED3B0;
    return *table.tags[program];
}

/**
 * @brief Switch to a microprogram.
 * @param program Program index.
 * @return The program's data when it has to be uploaded, or null when it's already loaded.
 */
const void* LibMicrocodeLoader::select_program(s32 program)
{
    if (current_program == program)
    {
        return 0;
    }

    current_program = program;
    return lib_vu1_programs[program];
}

/** @brief Forget the loaded program and queue the resident microcode upload. */
void LibMicrocodeLoader::start_upload()
{
    unk04 = 0;
    current_program = LIB_VU1_PROGRAM_NONE;
    resident_dma_queue_push(g_vif1_dma_queue, this);
}

/** @brief Start with no program and an empty upload packet. */
LibMicrocodeLoader::LibMicrocodeLoader()
{
    for (s32 i = 0; i < 3; i++)
    {
        unk14[i] = 0;
        unk20[i] = 0;
    }

    flush = VIF_FLUSH;
    unk06 = 0;
    FlushCache(0);
}

/** @brief Destroy the printer: free the font image unless it is shared, and the packet. */
LibScreenText::~LibScreenText()
{
    if (!shared_font)
    {
        delete font_image;
    }

    delete packet;
}

/** @brief Apply the enabled camera-facing rotation components. */
void LibTransform::update()
{
    if (draw_flags & (LIB_DRAW_FACE_CAMERA_X | LIB_DRAW_FACE_CAMERA_Y | LIB_DRAW_FACE_CAMERA_Z))
    {
        LibCamera* camera;

        if (display_manager != 0)
        {
            camera = static_cast<LibCamera*>(display_manager->current_display);
        }
        else
        {
            camera = static_cast<LibCamera*>(g_display_manager->current_display);
        }

        if (camera != 0)
        {
            if (camera->matrix_ready == 0)
            {
                camera->update_transform_matrix();
            }

            LibVector4 angles;
            const float* camera_angles = camera->rotation_angles;
            func_004CDA40(&angles, &orientation);

            if (draw_flags & LIB_DRAW_FACE_CAMERA_X)
            {
                angles.x = -camera_angles[0];
            }

            if (draw_flags & LIB_DRAW_FACE_CAMERA_Y)
            {
                angles.y = camera_angles[1];
            }

            if (draw_flags & LIB_DRAW_FACE_CAMERA_Z)
            {
                angles.z = -camera_angles[2];
            }

            angles.y += 3.1415927f;
            set_rotation_vector(&angles);
            matrix_ready = 0;
        }
    }
}

/**
 * @brief Mark the inverse as rebuilt and invert the transposed matrix, with the cheaper routine when the transform
 *        has no scale.
 * @param transform Transform whose inverse is rebuilt.
 */
void func_004D9E70(LibTransform* transform)
{
    LibVector4 error;

    vu0_start_microprogram_7f0_rows(&transform->transform);
    transform->unk20e_2 = 1;
    vu0_wait_microprogram();
    vu0_scale_error_vf6();
    vu0_read_vf6(&error);

    if (error.x < 1e-6f && error.y < 1e-6f && error.z < 1e-6f)
    {
        func_004CEF20(&transform->transposed_transform, &transform->inverse_transform);
    }
    else
    {
        func_004CF1C0(&transform->transposed_transform, &transform->inverse_transform);
    }
}

/**
 * @brief Copy local transform state and its inherited state.
 * @param source Transform to copy.
 */
void LibTransform::copy_offset_transform_state(const LibTransform* source)
{
    if (source->draw_flags & 0x20)
    {
        draw_flags |= 0x20;
    }

    func_004DA050(this, source->unk200);
    func_00479090(&offset_translation, source->get_offset_translation());
    lib_rebuild_offset_transform(this);
    lib_transform_set_dirty(this, 1);
    func_004DA040(&offset_rotation, source->get_offset_rotation());
    lib_rebuild_offset_transform(this);
    lib_transform_set_dirty(this, 1);
    func_00479090(&offset_scale, source->get_offset_scale());
    lib_rebuild_offset_transform(this);
    lib_transform_set_dirty(this, 1);
    unk20c = source->unk20c;
    parent_transform = source->parent_transform;
    LibTransformOwner::copy_transform_state(source);
}

/**
 * @brief Copy a complete local vector.
 * @param output Destination vector.
 * @param input Source vector.
 */
extern "C" void func_004DA040(LibVector4* output, const LibVector4* input)
{
    copy_vector(output, input);
}

/**
 * @brief Store the local scalar and update its threshold flag.
 *
 * With LIB_DRAW_FLAG_0020 set, LIB_DRAW_FLAG_0040 marks a scalar below one half; under a parent the scalar is
 * first multiplied by the chain's combined factor (which already includes it).
 * @param object Transform receiver.
 * @param value Local scalar value.
 */
void func_004DA050(LibTransform* object, float value)
{
    object->unk200 = value;

    if ((object->unk20c & 0x200) && object->parent_transform != 0)
    {
        value *= func_004DA0F0(object);
    }

    if (object->get_draw_flags() & LIB_DRAW_FLAG_0020)
    {
        if (value >= 0.5f)
        {
            object->draw_flags &= ~LIB_DRAW_FLAG_0040;
        }
        else
        {
            object->draw_flags |= LIB_DRAW_FLAG_0040;
        }
    }
}

// TODO: The target unrolls the recursion five calls deep and calls the flag getter out of line at the sixth, whose
// copy then follows this function; that only happens with auto inlining and an inline depth of five.
#pragma push
#pragma auto_inline on
#pragma inline_depth(5)

/**
 * @brief Return the transform's flags.
 * @param object Transform.
 * @return Flags.
 */
inline u16 func_004DA2B0(const LibTransform* object)
{
    return object->unk20c;
}

/**
 * @brief Multiply the transform's factor by its parents' while they have flag 0x200 set.
 * @param transform Transform.
 * @return Combined factor.
 */
extern "C" float func_004DA0F0(LibTransform* transform)
{
    if (func_004DA2B0(transform) & 0x200)
    {
        if (transform->parent_transform != 0)
        {
            return transform->unk200 * func_004DA0F0(transform->parent_transform);
        }

        return transform->unk200;
    }

    return transform->unk200;
}

#pragma pop

/**
 * @brief Mark each transform in the parent chain dirty.
 * @param object First transform, or null.
 */
extern "C" void lib_invalidate_transform_chain(LibTransform* object)
{
    for (; object != 0; object = object->parent_transform)
    {
        object->matrix_ready = 0;
    }
}

#define LIB_IK_ALIGNED_COSINE 0.99999988f
#define LIB_IK_SETTLED_DISTANCE 1.0f


/**
 * @brief Turn the joints above a transform so that it reaches toward a target (cyclic coordinate descent).
 * @param end Transform at the end of the chain.
 * @param target Target point, in the same space as the base transforms.
 * @param links Most parent joints to turn per iteration.
 * @param iterations Most passes over the chain.
 * @param include_root Nonzero to also turn the chain's root.
 * @param weight Fraction of each joint's full correction to apply.
 */
extern "C" void lib_solve_ik_chain(LibTransform* end, const LibVector4* target, s32 links, s32 iterations, s32 include_root, float weight)
{
    LibVector4 position;
    LibVector4 start;
    LibVector4 current;
    LibMatrix44Value inverse;
    LibVector4 dot;
    LibVector4 axis;
    FieldVec4B rotation;

    if (!end->matrix_ready)
    {
        end->update_transform_matrix();
    }

    for (s32 iteration = 0; iteration < iterations; iteration++)
    {
        start.x = end->transform.m[0][3];
        start.y = end->transform.m[1][3];
        start.z = end->transform.m[2][3];
        start.w = 1.0f;

        LibTransform* joint = end;

        for (s32 link = 0; link < links; link++)
        {
            LibTransform* child = joint;
            joint = joint->parent_transform;

            if (joint == 0)
            {
                break;
            }

            if (!include_root && joint->parent_transform == 0)
            {
                break;
            }

            func_004CEFD0(lib_get_parent_matrix(child), &inverse);
            position.x = end->base_transform.m[0][3];
            position.y = end->base_transform.m[1][3];
            position.z = end->base_transform.m[2][3];
            position.w = 1.0f;
            ee_transpose_matrix(&inverse, &inverse);
            vu0_direction_pair_begin(&inverse, &position, target);

            // TODO: I'm guessing the threshold was a local here; it's the only shape that loads it between the two VU0 blocks.
            float limit = LIB_IK_ALIGNED_COSINE;

            vu0_direction_pair_dot_cross();
            vu0_direction_pair_store_dot(&dot);

            if (dot.x < limit)
            {
                vu0_store_unit_cross(&axis);
                axis.w = weight * func_004CD010(dot.x);
                lib_quaternion_from_axis_angle(&rotation, &axis);
                vu0_quaternion_multiply_assign(&rotation, reinterpret_cast<const FieldVec4B*>(&joint->orientation));
                joint->copy_orientation(reinterpret_cast<const LibVector4*>(&rotation));

                LibTransform* dirty = end;

                for (s32 i = 0; i <= link; i++)
                {
                    dirty->matrix_ready = 0;
                    dirty = dirty->parent_transform;
                }

                end->update_transform_matrix();
            }
        }

        current.x = end->base_transform.m[0][3];
        current.y = end->base_transform.m[1][3];
        current.z = end->base_transform.m[2][3];
        current.w = 1.0f;

        if (fabsf(current.x - start.x) < LIB_IK_SETTLED_DISTANCE && fabsf(current.y - start.y) < LIB_IK_SETTLED_DISTANCE && fabsf(current.z - start.z) < LIB_IK_SETTLED_DISTANCE)
        {
            break;
        }
    }
}

/**
 * @brief Extract the transform's translation column.
 * @param object Transform owner.
 * @return Translation coordinates with homogeneous component one.
 */
extern "C" FieldVec4B func_004DA6F0(const LibTransform* object)
{
    FieldVec4B result;
    result.x = object->transform.m[0][3];
    result.y = object->transform.m[1][3];
    result.z = object->transform.m[2][3];
    result.w = 1.0f;
    return result;
}

#define LIB_TRANSFORM_FLAGS_01C0 0x1C0

/**
 * @brief Work out a transform's world position from its scale, rotation, translation, parent and offset, without
 *        touching its cached matrices.
 * @param object Transform.
 * @param position Receives the position, with w set to one.
 */
extern "C" void func_004DA730(LibTransform* object, LibVector4* position)
{
    LibTransform* parent = object->parent_transform;
    const LibMatrix44Value* parent_matrix = parent != 0 ? &parent->base_transform : 0;
    LibMatrix44Value result;

    vu0_load_scale_vf17(&object->scale);
    vu0_load_rotation_vf5(&object->orientation);
    vu0_load_translation_vf16(&object->translation);
    vu0_start_microprogram_728();

    if (parent_matrix != 0)
    {
        vu0_load_rows_vf1_vf3(parent_matrix);
        ee_prefetch(&object->offset_transform);
        vu0_start_microprogram_ae8();

        if (!(object->unk20c & LIB_TRANSFORM_FLAGS_01C0))
        {
            vu0_wait_microprogram();
            vu0_start_microprogram_830_scale_rows();
        }

        LibMatrix44Value* output = &result;
        vu0_load_matrix_vf5_vf7_vf4(&object->offset_transform);
        vu0_multiply_store_result_vf4(output);
    }
    else
    {
        vu0_scale_rotation_rows();
        LibMatrix44Value* output = &result;
        vu0_load_matrix_vf5_vf8(&object->offset_transform);
        vu0_multiply_store_result_vf8(output);
    }

    position->x = result.m[0][3];
    position->y = result.m[1][3];
    position->z = result.m[2][3];
    position->w = 1.0f;
}

/** @brief Update the cached transformation matrices. */
void LibTransform::update_transform_matrix()
{
    LibTransform* parent = parent_transform;
    const LibMatrix44Value* parent_matrix;

    if (parent != 0)
    {
        if (!parent->matrix_ready)
        {
            parent->update_transform_matrix();
            transform_dirty = 1;
        }
        else if (parent->unk51)
        {
            transform_dirty = 1;
        }

        parent_matrix = &parent->base_transform;
    }
    else
    {
        parent_matrix = 0;
    }

    if (!transform_dirty)
    {
        matrix_ready = 1;
        return;
    }

    vu0_load_scale_vf17(&scale);
    vu0_load_rotation_vf5(&orientation);
    vu0_load_translation_vf16(&translation);
    vu0_start_microprogram_728();
    unk20e_0 = 0;
    unk20e_1 = 0;
    unk20e_2 = 0;
    matrix_ready = 1;

    if (parent_matrix != 0)
    {
        vu0_load_rows_vf1_vf3(parent_matrix);
        ee_prefetch(&offset_transform);
        vu0_start_microprogram_ae8();
        unk20e_3 = 0;
        transform_dirty = 0;
        unk51 = 1;

        if (!(unk20c & LIB_TRANSFORM_FLAGS_01C0))
        {
            vu0_wait_microprogram();
            vu0_start_microprogram_830_scale_rows();
        }

        LibMatrix44Value* result = &transform;
        const LibMatrix44Value* offset = &offset_transform;
        LibMatrix44Value* base = &base_transform;
        vu0_load_matrix_vf5_vf7_vf4(offset);
        ee_prefetch(base);
        vu0_multiply_store_vf4(base, result);
    }
    else
    {
        unk20e_3 = 0;
        transform_dirty = 0;
        unk51 = 1;
        vu0_scale_rotation_rows();
        LibMatrix44Value* result = &transform;
        const LibMatrix44Value* offset = &offset_transform;
        LibMatrix44Value* base = &base_transform;
        vu0_load_matrix_vf5_vf8(offset);
        ee_prefetch(base);
        vu0_multiply_store_vf8(base, result);
    }
}

/**
 * @brief Rebuild the offset matrix from the stored translation, quaternion and scale.
 * @param object Transform whose offset matrix is updated.
 */
static inline void rebuild_offset_transform(LibTransform* object)
{
    LibMatrix44Value scale;
    LibMatrix44Value rotation;

    func_004CFF80(&scale);
    scale.m[0][0] = object->offset_scale.x;
    scale.m[1][1] = object->offset_scale.y;
    scale.m[2][2] = object->offset_scale.z;
    scale.m[3][3] = 1.0f;
    vu0_load_rotation_vf5(&object->offset_rotation);
    vu0_load_translation_vf16(&object->offset_translation);
    vu0_start_microprogram_728();
    rotation.m[3][0] = 0.0f;
    rotation.m[3][1] = 0.0f;
    rotation.m[3][2] = 0.0f;
    rotation.m[3][3] = 1.0f;
    vu0_wait_microprogram();
    vu0_store_rows_vf8_vf10(&rotation);
    LibMatrix44Value* output = &object->offset_transform;
    vu0_multiply_matrix(output, &rotation, &scale);
}

/**
 * @brief Rebuild the offset matrix from the stored translation, quaternion and scale.
 * @param object Transform whose offset matrix is updated.
 */
void lib_rebuild_offset_transform(LibTransform* object)
{
    rebuild_offset_transform(object);
}


// TODO: Another destructor that inlines its whole base chain down to LibLink; see LibClass178C00's above.
#pragma push
#pragma inline_depth(7)

/** @brief Stop the object being a sound target if it is one, then destroy the transform owner. */
LibTransform::~LibTransform()
{
    if (unk20e_4)
    {
        resident_sound_clear_target(g_sound, reinterpret_cast<ResidentSoundEmitter*>(this));
    }
}

#pragma pop

/** @brief Initialize the object and its transform state. */
LibTransform::LibTransform()
{
    offset_scale.x = 1.0f;
    offset_scale.y = 1.0f;
    offset_scale.z = 1.0f;
    offset_scale.w = 1.0f;
    unk200 = 1.0f;
    parent_transform = 0;
    unk20c = 0x1FF;
    unk20e_0 = 0;
    unk20e_1 = 0;
    unk20e_2 = 0;
    unk20e_3 = 0;
    unk20e_4 = 0;
    type_id = 2;
    *reinterpret_cast<unsigned __int128*>(&offset_translation) = 0;
    offset_translation.w = 1.0f;
    *reinterpret_cast<unsigned __int128*>(&offset_rotation) = 0;
    offset_rotation.w = 1.0f;
    base_transform.set_identity();
    transform.set_identity();
    rebuild_offset_transform(this);
}

/**
 * @brief Return the list kind.
 * @return Eight.
 */
s32 LibClass178F30::get_default_list_kind()
{
    return 8;
}

/**
 * @brief Turn the display's effect on or off and pick its level.
 * @param display Display the effect applies to.
 * @param enabled Nonzero to turn the effect on.
 * @param first_flag Passed to the display unchanged.
 * @param second_flag Passed to the display and kept here.
 * @param level Effect level; it picks the two scales passed to the display.
 * @param mask Passed to the display unchanged.
 */
void LibDisplayManager::set_display_effect(LibCameraContext* display, bool enabled, bool first_flag, bool second_flag, s32 level, u32 mask)
{
    float first_scale;
    float second_scale;

    effect_enabled = enabled;

    if (effect_enabled)
    {
        if (level == 1)
        {
            first_scale = 1.0f;
            second_scale = 1.0f;
        }
        else if (level == 2)
        {
            first_scale = 0.5f;
            second_scale = 2.0f;
        }
        else if (level == 3)
        {
            first_scale = 0.2f;
            second_scale = 4.0f;
        }
        else if (level < 9)
        {
            first_scale = 0.15f;
            second_scale = 6.0f;
        }
        else
        {
            first_scale = 0.1f;
            second_scale = 12.0f;
        }

        effect_display = display;
        unk96 = second_flag;
        effect_level = level;
        func_004DCDE0(display, true, first_flag, second_flag, level, mask, first_scale, second_scale);
        func_004DE500(display);
    }
    else
    {
        effect_display = 0;
    }
}

/** @brief Run LibCamera::func_004E1E70 on the current camera, if there is one. */
void LibDisplayManager::func_004DB0F0()
{
    if (current_display != 0)
    {
        static_cast<LibCamera*>(current_display)->func_004E1E70();
    }
}

/** @brief Queue the current camera, if there is one, for VIF1 DMA. */
void LibDisplayManager::submit_camera()
{
    if (current_display != 0)
    {
        static_cast<LibCamera*>(current_display)->enqueue_submission();
    }
}

/** @brief Set unk94 and write the current camera's matrices, if there is one. */
void LibDisplayManager::prepare_camera()
{
    unk94 = 1;

    if (current_display != 0)
    {
        static_cast<LibCamera*>(current_display)->func_004E2120();
    }
}

/**
 * @brief Update the nodes and, with the depth effect on, project each level's far and near distances through the
 *        current camera into the effect display's depths, then rebuild its effect packets.
 */
void LibClass178F30::update()
{
    s32 i;

    unk94 = 0;
    update_nodes();

    if (effect_enabled)
    {
        LibCamera* camera = static_cast<LibCamera*>(current_display);
        float half_width = (camera->screen_max.x - camera->screen_min.x) / 2.0f;
        float distance = half_width / func_00141EC0(0.34906584f);
        float scale = camera->unk244 / distance;
        float step = 200.0f * (camera->unk24c * (camera->unk24c * (scale * (scale * (distance * distance / (camera->projection_distance * camera->projection_distance))))));
        vu0_start_microprogram_1f0_vf5_vf8(&camera->projection_matrix);
        s32 level = effect_level;

        for (i = 0; i < level; i++)
        {
            FieldVec4A far_point(0.0f, 0.0f, camera->unk244 + step * (1.0f + i), 1.0f);

            if (!(far_point.z <= camera->screen_max.z))
            {
                far_point.z = camera->screen_max.z;
            }

            vu0_start_microprogram_vf5(&far_point);
            vu0_wait_microprogram();
            vu0_read_vf6(&far_point);
            effect_display->set_effect_first_depth(i, (s32)far_point.z);

            if (unk96)
            {
                FieldVec4A near_point(0.0f, 0.0f, camera->unk244 - 0.2f * step * (1.0f + i), 1.0f);

                if (near_point.z < 10.0f)
                {
                    near_point.z = 10.0f;
                }

                vu0_start_microprogram_vf5(&near_point);
                vu0_wait_microprogram();
                vu0_read_vf6(&near_point);
                effect_display->set_effect_second_depth(i, (s32)near_point.z);
            }
        }

        func_004DE500(effect_display);
    }
}

/** 0x80-byte packet a ring slot holds: two float quadwords around ten doubleword fields. */
struct LibRingPacket
{
    float unk00[4];
    u64 unk10;
    u64 unk18;
    u64 unk20;
    u64 unk28;
    u64 unk30;
    u64 unk38;
    u64 unk40;
    u64 unk48;
    u64 unk50;
    u64 unk58;
    float unk60[4];
    u64 unk70;
    u64 unk78;
};

/**
 * @brief Copy a packet into the ring's next slot (wrapping from 254 back to one), clear its words at 0x60 and 0x68 and
 * store a value at 0x20, all through the uncached accelerated view.
 * @param ring Packet ring.
 * @param packet Packet to copy.
 * @param value Doubleword stored at 0x20.
 * @return The slot.
 */
extern "C" LibRingPacket* func_004DB410(LibPacketRing* ring, const LibRingPacket* packet, u64 value)
{
    if (++ring->next_slot >= 0xFF)
    {
        ring->next_slot = 1;
    }

    LibRingPacket* slot = reinterpret_cast<LibRingPacket*>(ring->slots[ring->next_slot]);
    LibRingPacket* uncached = reinterpret_cast<LibRingPacket*>((u32)slot | EE_UNCACHED_ACCELERATED);
    *uncached = *packet;
    *reinterpret_cast<u64*>((u32)&slot->unk60 | EE_UNCACHED_ACCELERATED) = 0;
    *reinterpret_cast<u64*>((u32)&slot->unk60[2] | EE_UNCACHED_ACCELERATED) = 0;
    *reinterpret_cast<u64*>((u32)&slot->unk20 | EE_UNCACHED_ACCELERATED) = value;
    return slot;
}

/** @brief Flush the data cache and start writing at slot one. */
LibPacketRing::LibPacketRing()
{
    FlushCache(0);
    next_slot = 1;
}

/**
 * @brief Free memory from the Lib heap when one is installed, otherwise from the C library.
 * @param memory Allocation, or null.
 */
extern "C" void func_004DB570(void* memory)
{
    if (memory != 0)
    {
        if (D_001B6698 != 0)
        {
            resident_heap_release(memory);
        }
        else
        {
            free_guess(memory);
        }
    }
}

/**
 * @brief Allocate memory from the Lib heap when one is installed, otherwise from the C library.
 * @param size Size in bytes.
 * @return Allocation, or null.
 */
extern "C" void* func_004DB5B0(u32 size)
{
    void* memory;

    if (D_001B6698 != 0)
    {
        memory = resident_heap_allocate(D_001B6698, size);
    }
    else
    {
        memory = malloc_guess(size);
    }

    if (memory == 0)
    {
        return 0;
    }

    return memory;
}

/**
 * @brief Build a clear packet like build_clear, for the second drawing context (TEST_2, PRIM context bit).
 * @param clear Packet to fill.
 * @param depth_method Depth test restored after the clear; 0 leaves depth testing off.
 * @param x Left edge in GS coordinates.
 * @param y Top edge in GS coordinates.
 * @param width Width in pixels.
 * @param height Height in pixels.
 * @param red Red component.
 * @param green Green component.
 * @param blue Blue component.
 * @param alpha Alpha component.
 * @param depth Depth the cleared pixels get.
 */
void LibCameraContext::func_004DB600(LibScreenClear* clear, s16 depth_method, s16 x, s16 y, s16 width, s16 height, u8 red,
                                     u8 green, u8 blue, u8 alpha, u32 depth)
{
    clear->test.address = GS_REGISTER_TEST_2;
    clear->test.data = 0x30000;
    clear->prim.address = GS_REGISTER_PRIM;
    clear->prim.data = GS_PRIM_SPRITE | 0x200;
    clear->color.address = GS_REGISTER_RGBAQ;
    clear->color.data = (u64)red | (u64)green << 8 | (u64)blue << 16 | (u64)alpha << 24 | (u64)0x3F800000 << 32;
    s32 strips = width / 32;
    s32 i;
    GsRegisterValue* vertex;

    for (i = 0; i < strips; i++)
    {
        vertex = &clear->vertices[i * 2];
        vertex->address = GS_REGISTER_XYZ2;
        vertex->data = (u64)depth << 32 | ((u64)(y << 4) << 16 | ((x + i * 32) << 4));
        vertex = &clear->vertices[i * 2 + 1];
        vertex->address = GS_REGISTER_XYZ2;
        vertex->data = (u64)depth << 32 | ((x + i * 32 + 32) << 4 | (u64)((y + height) << 4) << 16);
    }

    // TODO: Padding vertices go to XYZ3, which doesn't draw; only holding the address in a local matches.
    u64 no_kick = GS_REGISTER_XYZ3;

    for (; i < LIB_SCREEN_CLEAR_STRIP_COUNT; i++)
    {
        vertex = &clear->vertices[i * 2];
        vertex->address = no_kick;
        vertex->data = (u64)depth << 32 | (x << 4 | (u64)(y << 4) << 16);
        vertex = &clear->vertices[i * 2 + 1];
        vertex->address = no_kick;
        vertex->data = (u64)depth << 32 | (x << 4 | (u64)(y << 4) << 16);
    }

    clear->restore_test.address = GS_REGISTER_TEST_2;

    if (depth_method)
    {
        clear->restore_test.data = (u64)(depth_method & 3) << 17 | 0x10000;
    }
    else
    {
        clear->restore_test.data = 0x30000;
    }

    ee_sync();
}

/**
 * @brief Build a packet that clears a rectangle in 32-pixel-wide sprite strips with depth testing off, then restores
 *        the depth test.
 * @param clear Packet to fill.
 * @param depth_method Depth test restored after the clear; 0 leaves depth testing off.
 * @param x Left edge in GS coordinates.
 * @param y Top edge in GS coordinates.
 * @param width Width in pixels.
 * @param height Height in pixels.
 * @param red Red component.
 * @param green Green component.
 * @param blue Blue component.
 * @param alpha Alpha component.
 * @param depth Depth the cleared pixels get.
 */
void LibCameraContext::build_clear(LibScreenClear* clear, s16 depth_method, s16 x, s16 y, s16 width, s16 height, u8 red,
                                   u8 green, u8 blue, u8 alpha, u32 depth)
{
    clear->test.address = GS_REGISTER_TEST_1;
    clear->test.data = 0x30000;
    clear->prim.address = GS_REGISTER_PRIM;
    clear->prim.data = GS_PRIM_SPRITE;
    clear->color.address = GS_REGISTER_RGBAQ;
    clear->color.data = (u64)red | (u64)green << 8 | (u64)blue << 16 | (u64)alpha << 24 | (u64)0x3F800000 << 32;
    s32 strips = width / 32;
    s32 i;
    GsRegisterValue* vertex;

    for (i = 0; i < strips; i++)
    {
        clear->vertices[i * 2].address = GS_REGISTER_XYZ2;
        clear->vertices[i * 2].data = (u64)depth << 32 | ((u64)(y << 4) << 16 | ((x + i * 32) << 4));
        clear->vertices[i * 2 + 1].address = GS_REGISTER_XYZ2;
        // TODO: The game computes this value before the vertex address; only this assignment form does that.
        (vertex = &clear->vertices[i * 2 + 1])->data =
            (u64)depth << 32 | ((x + i * 32 + 32) << 4 | (u64)((y + height) << 4) << 16);
    }

    u64 no_kick = GS_REGISTER_XYZ3;

    for (; i < LIB_SCREEN_CLEAR_STRIP_COUNT; i++)
    {
        clear->vertices[i * 2].address = no_kick;
        clear->vertices[i * 2].data = (u64)depth << 32 | (x << 4 | (u64)(y << 4) << 16);
        clear->vertices[i * 2 + 1].address = no_kick;
        vertex = &clear->vertices[i * 2 + 1];
        vertex->data = (u64)depth << 32 | (x << 4 | (u64)(y << 4) << 16);
    }

    clear->restore_test.address = GS_REGISTER_TEST_1;

    if (depth_method)
    {
        clear->restore_test.data = (u64)(depth_method & 3) << 17 | 0x10000;
    }
    else
    {
        clear->restore_test.data = 0x30000;
    }

    ee_sync();
}

/**
 * @brief Queue the packets that draw a rectangle into both draw buffers, using the next free pair of packets.
 * @param display Display.
 * @param x Rectangle left edge.
 * @param y Rectangle top edge.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return Nonzero when the packets were queued; zero when all six pairs are in use or the rectangle is empty.
 */
extern "C" s32 func_004DB9E0(LibCameraContext* display, s32 x, s32 y, s32 width, s32 height)
{
    if (display->unk3E78 >= 6)
    {
        return 0;
    }

    if (width <= 0 || height <= 0)
    {
        return 0;
    }

    u32 depth_mask = 0xFFFF;

    if (display->display_area.depth_format == 0x30)
    {
        depth_mask = 0xFFFFFFFF;
    }
    else if (display->display_area.depth_format == 0x31)
    {
        depth_mask = 0xFFFFFF;
    }

    s32 set = display->unk3E7A;

    for (s32 i = 0; i < 2; i++)
    {
        s32 index = display->unk3E78 * 2 + i + 6;
        display->packet_sizes[set][index] = func_004DEA70(
            display, display->packets[set][index] + 0x40, i != 0,
            display->buffers[0].environment.context2.frame.base_pointer, display->display_area.unk10,
            display->display_area.width, display->display_area.height, display->display_area.base_width,
            display->display_area.base_height, depth_mask, 0, 0x80, 0, 0, 0, 1, x, y, width, height);
    }

    display->unk3E78++;
    FlushCache(0);
    return 1;
}

void func_004DBB70(LibCameraContext* display)
{
    display->unk3E78 = 0;
    display->unk3E7A ^= 1;
}

/**
 * @brief Get the scale from screen pixels to the draw area. Interlaced output draws one field, so it counts y in
 *        field lines.
 * @param x Receives the horizontal scale.
 * @param y Receives the vertical scale.
 */
void LibCameraContext::get_area_scale(float* x, float* y)
{
    *x = (float)display_area.width / display_area.base_width;
    ResidentSystem* system = resident_get_system();
    float ratio = (float)display_area.height / display_area.base_height;
    *y = ratio * (1.0f + system->progressive);
}

/**
 * @brief Return the frame buffer page of the draw buffer the display is on.
 * @param display Display to read.
 * @return FRAME base pointer of the second drawing context of draw buffer 0 or 1.
 */
extern "C" u16 func_004DBC70(LibCameraContext* display)
{
    return display->current_buffer == 0 ? display->buffers[0].environment.context2.frame.base_pointer :
                                          display->buffers[1].environment.context2.frame.base_pointer;
}

/**
 * @brief Read one register of the first drawing context of the draw buffer the display is on, as its raw word.
 * @param display Display to read.
 * @param index 0 FRAME, 1 ZBUF, 2 XYOFFSET, 3 SCISSOR, 4 TEST.
 * @return The register, or zero for another index.
 */
extern "C" u64 func_004DBCA0(LibCameraContext* display, s32 index)
{
    if (display->current_buffer == 0)
    {
        switch (index)
        {
        case 0:
            return *reinterpret_cast<const u64*>(&display->buffers[0].environment.context1.frame);
        case 1:
            return *reinterpret_cast<const u64*>(&display->buffers[0].environment.context1.depth_buffer);
        case 2:
            return display->buffers[0].environment.context1.offset;
        case 3:
            return *reinterpret_cast<const u64*>(&display->buffers[0].environment.context1.scissor);
        case 4:
            return *reinterpret_cast<const u64*>(&display->buffers[0].environment.context1.test);
        }
    }
    else
    {
        switch (index)
        {
        case 0:
            return *reinterpret_cast<const u64*>(&display->buffers[1].environment.context1.frame);
        case 1:
            return *reinterpret_cast<const u64*>(&display->buffers[1].environment.context1.depth_buffer);
        case 2:
            return display->buffers[1].environment.context1.offset;
        case 3:
            return *reinterpret_cast<const u64*>(&display->buffers[1].environment.context1.scissor);
        case 4:
            return *reinterpret_cast<const u64*>(&display->buffers[1].environment.context1.test);
        }
    }

    return 0;
}

/**
 * @brief Test whether any slot after the write index, up to the read index, holds an operation other than 5.
 * @param queue Packet queue.
 * @return One when such an operation is found, otherwise zero.
 */
s32 func_004DBD80(LibPacketQueue* queue)
{
    LibInterruptLock interrupts;
    s16 index = queue->write_index + 1;

    if (index >= queue->capacity)
    {
        index = 0;
    }

    if (index == queue->read_index)
    {
        return 0;
    }

    do
    {
        if (queue->entries[index].operation != 5)
        {
            return 1;
        }

        index++;

        if (index >= queue->capacity)
        {
            index = 0;
        }
    } while (index != queue->read_index);

    return 0;
}

/**
 * @brief Sync the GS path once the packet queue is full; with a zero flag, wait for that.
 * @param queue Packet queue.
 * @param flag Nonzero checks once and syncs with that value; zero waits until the queue is full and syncs with zero.
 * @return The sync result, or 0x8000 when the queue had room.
 */
s32 func_004DBEE0(LibPacketQueue* queue, s32 flag)
{
    do
    {
        s16 next = queue->write_index + 1;

        if (next >= queue->capacity)
        {
            next = 0;
        }

        if (next == queue->read_index)
        {
            if (flag)
            {
                return resident_sync_gs_path(resident_system_get_input(resident_get_system()), (u8)flag, 0);
            }

            return resident_sync_gs_path(resident_system_get_input(resident_get_system()), 0, 0);
        }
    } while (!flag);

    return 0x8000;
}

/**
 * @brief Finish the packet operation at the queue's head: release an image upload's buffers when asked and tell
 * the operation's completion object.
 * @param queue Packet queue.
 */
void func_004DBFB0(LibPacketQueue* queue)
{
    if (!queue->unk0E)
    {
        return;
    }

    s32 read_index = queue->read_index;

    if (read_index >= queue->capacity)
    {
        read_index = 0;
    }

    s16 next = queue->write_index + 1;

    if (next >= queue->capacity)
    {
        next = 0;
    }

    if (next == read_index)
    {
        queue->unk0E = 0;
    }

    s32 operation = queue->entries[queue->write_index].operation;
    u16 flags = queue->entries[queue->write_index].flags;
    queue->entries[queue->write_index].flags = 0;
    const void* packet = queue->entries[queue->write_index].packet;
    ResidentReleaseQueues* release = resident_system_get_release_queues(&g_system);

    switch (operation)
    {
    case LIB_PACKET_LOAD_IMAGE:
        if (flags & LIB_PACKET_FREE_PIXELS)
        {
            resident_queue_allocation_release(release, (void*)static_cast<const LibImageUpload*>(packet)->pixels);
        }

        if (flags & LIB_PACKET_FREE_RECORD)
        {
            resident_queue_allocation_release(release, (void*)packet);
        }

        break;
    }

    if (queue->entries[queue->write_index].completion)
    {
        queue->entries[queue->write_index].completion->on_packet_complete((u32)packet);
    }

    queue->unk11 = 0;
}

/**
 * @brief DMA channel 2 interrupt handler: finish the current packet operation and start the next.
 * @param channel DMA channel.
 * @return One.
 */
s32 func_004DC140(s32 channel)
{
    if (channel == 2)
    {
        func_004DBFB0(g_interrupt_packet_queue);
        func_004DC200(g_interrupt_packet_queue, 1);
    }

    ee_exit_handler();
    return 1;
}

/**
 * @brief Test whether a live entry holds an operation for a packet.
 * @param queue Packet queue.
 * @param operation Operation number.
 * @param packet Packet or object the operation is for.
 * @return One when such an entry is queued.
 */
s32 func_004DC180(LibPacketQueue* queue, u16 operation, const void* packet)
{
    for (s32 i = 0; i < queue->capacity; i++)
    {
        if ((queue->entries[i].flags & LIB_PACKET_ENTRY_LIVE) && queue->entries[i].operation == operation && queue->entries[i].packet == packet)
        {
            return 1;
        }
    }

    return 0;
}

extern "C" const char lib_packet_queue_bad_operation_error[];
extern "C" const char lib_packet_queue_bad_operation_detail[];

/**
 * @brief Start the next queued packet operation when the queue has work and is enabled.
 * @param queue Packet queue.
 * @param value Passed on by the DMA completion path; func_004DC420 passes zero.
 */
void func_004DC200(LibPacketQueue* queue, s32 value)
{
    if (!queue->unk0E)
    {
        return;
    }

    if (!queue->enabled)
    {
        return;
    }

    s16 next = queue->write_index + 1;
    queue->write_index = next;

    if (next >= queue->capacity)
    {
        queue->write_index = 0;
    }

    s32 operation = queue->entries[queue->write_index].operation;
    const void* packet = queue->entries[queue->write_index].packet;

    if ((u32)packet >= EE_SCRATCHPAD)
    {
        packet = (const void*)((u32)packet | DMA_ADDRESS_SCRATCHPAD);
    }

    u32 size = queue->entries[queue->write_index].value;
    queue->unk11 = 1;

    switch (operation)
    {
    case LIB_PACKET_LOAD_IMAGE:
        sceGsExecLoadImage((GsLoadImage*)&static_cast<const LibImageUpload*>(packet)->packet, (void*)static_cast<const LibImageUpload*>(packet)->pixels);
        break;

    case 2:
        sceDmaSendN(sceDmaGetChan(2), (void*)packet, size);
        break;

    case 3:
    {
        DmaChannel* channel = sceDmaGetChan(2);
        channel->chcr.tag_transfer_enable = 0;
        sceDmaSend(channel, (void*)packet);
        break;
    }

    case 4:
    {
        DmaChannel* channel = sceDmaGetChan(2);

        if (!size)
        {
            size = (*(const u64*)packet & 0x7FFF) + 1;
        }

        sceDmaSendN(channel, (void*)packet, size);
        break;
    }

    case 5:
        resident_stream_dma_take_channel((ResidentStreamDma*)packet);
        func_004DBFB0(queue);
        func_004DC200(queue, 1);
        break;

    case 6:
        func_004332F0((LibImageCapture*)packet);
        func_004DBFB0(queue);
        break;

    default:
        scePrintf(lib_packet_queue_bad_operation_error, operation, queue->write_index, queue->entries[queue->write_index].operation);
        scePrintf(lib_packet_queue_bad_operation_detail, packet, size, queue->read_index);
        break;
    }
}

/**
 * @brief Let queued packets start, or hold them back.
 *
 * Enabling a queue that has work waiting and isn't sending kicks the next operation.
 * @param queue Packet queue.
 * @param enable Nonzero lets packets start.
 */
void func_004DC420(LibPacketQueue* queue, s32 enable)
{
    LibInterruptLock interrupts;

    if (enable)
    {
        queue->enabled = 1;

        if (queue->unk0E && !queue->unk11)
        {
            func_004DC200(queue, 0);
        }
    }
    else
    {
        queue->enabled = 0;
    }
}

/**
 * @brief Queue a packet operation, and start the queue if it's idle.
 * @param queue Packet queue.
 * @param operation Operation number.
 * @param flags Operation flags.
 * @param packet Packet to send, or the object the operation is for.
 * @param value Operation value, such as a quadword count.
 * @param completion Object told when the operation finishes, or null.
 * @return One when queued, zero when the queue is full.
 */
u8 func_004DC4F0(LibPacketQueue* queue, u32 operation, u32 flags, const void* packet, u32 value, void* completion)
{
    if (queue->write_index == queue->read_index)
    {
        return 0;
    }

    LibInterruptLock interrupts;
    queue->entries[queue->read_index].operation = operation;
    queue->entries[queue->read_index].flags = (u16)flags | LIB_PACKET_ENTRY_LIVE;
    queue->entries[queue->read_index].packet = packet;
    queue->entries[queue->read_index].value = value;
    queue->entries[queue->read_index].completion = static_cast<LibDmaCallbacks*>(completion);
    queue->read_index++;

    if (queue->read_index >= queue->capacity)
    {
        queue->read_index = 0;
    }

    if (!queue->unk0E)
    {
        queue->unk0E = 1;
        func_004DC200(queue, 0);
    }

    return 1;
}

/** @brief Remove the interrupt handler, stop the channel and finish the operation in flight. */
LibPacketQueue::~LibPacketQueue()
{
    if (unk0F)
    {
        DisableDmac(2);
    }

    RemoveDmacHandler(2, unk00);
    unk0E = 0;
    DmaChannel* channel = sceDmaGetChan(2);
    read_index = write_index + 1;

    if (read_index >= capacity)
    {
        read_index = 0;
    }

    sceDmaPause(channel);
    func_004DBFB0(this);
    delete[] entries;
}

/**
 * @brief Allocate the entries and install the DMA channel 2 interrupt handler.
 * @param capacity Number of entries.
 */
LibPacketQueue::LibPacketQueue(s16 capacity)
{
    this->capacity = capacity;
    entries = new (0) LibPacketQueueEntry[this->capacity];
    enabled = 1;
    write_index = this->capacity - 1;
    read_index = 0;
    unk0E = 0;
    unk11 = 0;
    g_interrupt_packet_queue = this;
    unk00 = AddDmacHandler(2, func_004DC140, 0);
    unk0F = EnableDmac(2) != 0;
}

/**
 * @brief Measure how far the allocator's unk14 address is past its base address.
 * @param vram VRAM allocator.
 * @return Distance in words.
 */
u32 func_004DC7F0(LibVramAllocator* vram)
{
    return vram->unk14 - vram->base_address;
}

/**
 * @brief Build the CLUT half of a TEX0 value for a VRAM slot.
 * @param vram Allocator holding the slot's CLUT address.
 * @param slot VRAM slot.
 * @param entry CLUT entry offset (CSA).
 * @param mode CLUT load mode.
 * @return CBP, CSA and CLD bits of TEX0.
 */
u64 func_004DC800(LibVramAllocator* vram, s16 slot, s16 entry, s32 mode)
{
    u64 csa = ((u64)entry & 0x1F) << 56;
    u64 cld;

    switch (mode)
    {
    case 0:
        // TODO: Only signed constants here leave out the zero extension the other cases get; maybe a macro.
        cld = (slot & 1) ? (s64)4 << 61 : (s64)5 << 61;
        break;
    case 1:
        cld = 2ULL << 61;
        break;
    case 2:
        cld = 0;
        break;
    default:
        cld = 4ULL << 61;
        break;
    }

    return cld | (csa | ((u64)vram->allocations[slot] << 32));
}

/**
 * @brief Allocate VRAM after the allocator's base address and record it in a slot.
 *
 * The slot gets the upper word of a TEX0 with the address as CBP, in 64-word blocks.
 * @param vram VRAM allocator.
 * @param size Size in words.
 * @param slot Slot to record the allocation in, or LIB_VRAM_NEW_SLOT for the next free one.
 * @return The slot, or -1 when there's no slot or room left.
 */
extern "C" s16 func_004DC8B0(LibVramAllocator* vram, u32 size, s16 slot)
{
    s32 index = slot;

    if (index == LIB_VRAM_NEW_SLOT)
    {
        index = vram->allocation_count++;

        if (vram->allocation_count >= vram->allocation_capacity)
        {
            return -1;
        }
    }

    if (vram->base_address + size >= vram->unk14)
    {
        return -1;
    }

    vram->allocations[index] = (((u64)vram->base_address & ~0x3F) << 31) >> 32;
    size = (size + 0x3F) & ~0x3F;
    vram->base_address += size;
    return index;
}

/**
 * @brief Words a CLUT entry takes in VRAM for a CLUT pixel format.
 * @param format CLUT pixel format (CPSM).
 * @return One for format 0, two for the rest.
 */
static inline s32 clut_entry_words(s16 format)
{
    switch (format)
    {
    case 0:
        return 1;
    default:
        return 2;
    }
}

/**
 * @brief Allocate VRAM for a CLUT after the allocator's base address and record its TEX0 CBP and CPSM in a slot.
 *
 * A slot holds the upper word of TEX0: CBP (the address in 64-word blocks) at bit 37 and CPSM at bit 51.
 * @param vram VRAM allocator.
 * @param format CLUT pixel format (CPSM); a nonzero format takes two words per entry.
 * @param size Entry count.
 * @param slot Slot to record the allocation in, or LIB_VRAM_NEW_SLOT for the next free one.
 * @return The slot, or -1 when there's no slot or room left.
 */
extern "C" s16 func_004DC970(LibVramAllocator* vram, s16 format, s16 size, s32 slot)
{
    s32 index = (s16)slot;

    if (index == LIB_VRAM_NEW_SLOT)
    {
        index = vram->allocation_count++;

        if (vram->allocation_count >= vram->allocation_capacity)
        {
            return -1;
        }
    }

    u32 words = clut_entry_words(format);
    words *= size;

    if (vram->base_address + words >= vram->unk14)
    {
        return -1;
    }

    vram->allocations[index] = ((((u64)vram->base_address & ~0x3F) << 31) | ((u64)format << 51)) >> 32;
    words = (words + 0x3F) & ~0x3F;
    vram->base_address += words;
    return index;
}

/**
 * @brief Allocate an aligned area from the texture side of the VRAM allocator.
 * @param vram Allocator.
 * @param size Size in bytes.
 * @param alignment Alignment in bytes.
 * @param slot Slot to reuse, or -1 for a new one.
 * @return Slot of the area, or -1 when VRAM is full.
 */
extern "C" s16 func_004DCA70(LibVramAllocator* vram, u32 size, u32 alignment, s16 slot)
{
    s32 index = slot;

    vram->base_address = (vram->base_address + alignment - 1) & -alignment;

    if (index == -1)
    {
        index = vram->unk04_count++;

        if (vram->unk04_count >= vram->unk04_capacity)
        {
            return -1;
        }
    }

    if (vram->base_address + size >= vram->unk14)
    {
        return -1;
    }

    vram->unk04[index] = (u64)(vram->base_address >> 6);
    vram->base_address += (size + 63) & ~63;
    return index;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DCB30);

/**
 * @brief Empty the allocator and make it start allocating at a VRAM page.
 * @param vram Allocator.
 * @param page First VRAM page to hand out.
 */
void lib_vram_reset(LibVramAllocator* vram, u32 page)
{
    vram->base_address = page * GS_VRAM_PAGE_WORDS;

    for (s32 i = 0; i < vram->unk04_capacity; i++)
    {
        vram->unk04[i] = 0;
    }

    for (s32 i = 0; i < vram->allocation_capacity; i++)
    {
        vram->allocations[i] = 0;
    }

    vram->unk04_count = 0;
    vram->allocation_count = 0;
}

/** @brief Free the allocation tables. */
LibVramAllocator::~LibVramAllocator()
{
    delete[] unk04;
    delete[] allocations;
}

/**
 * @brief Allocate the two tables, with the end address at 0x100000 words.
 * @param first_capacity Entries in unk04.
 * @param allocation_capacity Entries in allocations.
 */
LibVramAllocator::LibVramAllocator(s16 first_capacity, s16 allocation_capacity)
{
    unk04 = new (0) u32[first_capacity];
    allocations = new (0) u32[allocation_capacity];
    unk04_capacity = first_capacity;
    this->allocation_capacity = allocation_capacity;
    unk14 = 0x100000;
}

/**
 * @brief Store a new unk3E40 and rewrite the word the context's unk3E38 points at from its top half and unk3E44.
 * @param display Camera context; nothing happens without a packet at unk3E34.
 * @param value New unk3E40.
 */
extern "C" void func_004DCDA0(LibCameraContext* display, s32 value)
{
    if (display->unk3E34)
    {
        display->unk3E40 = value;
        *display->unk3E38 = (u32)(display->unk3E44 | ((display->unk3E40 >> 16) << 24));
    }
}

#define LIB_EFFECT_BUFFER_SIZE 0x5460
#define LIB_EFFECT_LEVEL_MAX 6

/**
 * @brief Set up the display's effect with the scales its level picked.
 *
 * Level zero turns the effect off and levels above six are clamped. Turning it on the first time allocates the two
 * effect buffers; if either allocation fails both are freed and the effect stays off.
 * @param display Display.
 * @param enabled Turn the effect on.
 * @param first_flag Effect flag.
 * @param second_flag Effect flag.
 * @param level Effect level.
 * @param mask Effect mask.
 * @param first_scale First scale.
 * @param second_scale Second scale.
 */
void func_004DCDE0(LibCameraContext* display, bool enabled, bool first_flag, bool second_flag, s32 level, u32 mask,
                   float first_scale, float second_scale)
{
    if (level == 0)
    {
        enabled = false;
    }

    if (level > LIB_EFFECT_LEVEL_MAX)
    {
        level = LIB_EFFECT_LEVEL_MAX;
    }

    display->effect_enabled = enabled;
    display->effect_first_flag = first_flag;
    display->effect_second_flag = second_flag;
    display->effect_level = level;
    display->effect_first_scale = first_scale;
    display->effect_second_scale = second_scale;
    display->effect_mask = mask;

    if (enabled && display->effect_buffers[0] == 0)
    {
        display->effect_buffers[0] = new (0) u8[LIB_EFFECT_BUFFER_SIZE];
        display->effect_buffers[1] = new (0) u8[LIB_EFFECT_BUFFER_SIZE];

        if (display->effect_buffers[0] == 0 || display->effect_buffers[1] == 0)
        {
            ::operator delete(display->effect_buffers[0]);
            ::operator delete(display->effect_buffers[1]);
            display->effect_buffers[0] = 0;
            display->effect_buffers[1] = 0;
            display->effect_enabled = 0;
        }
    }
}

/**
 * @brief Turn the display output on or off. Circuit 1 only comes on when the display allows it (0x3E64).
 * @param enabled Show read circuit 2.
 * @param circuit1 Also show read circuit 1.
 */
void LibCameraContext::set_output(bool enabled, bool circuit1)
{
    s32 i;

    if (enabled)
    {
        for (i = 0; i < LIB_DISPLAY_BUFFER_COUNT; i++)
        {
            display_environments[i].pmode.circuit2 = 1;

            if (circuit1)
            {
                if (unk3E64)
                {
                    display_environments[i].pmode.circuit1 = 1;
                }
            }
            else
            {
                display_environments[i].pmode.circuit1 = 0;
            }
        }
    }
    else
    {
        for (i = 0; i < LIB_DISPLAY_BUFFER_COUNT; i++)
        {
            display_environments[i].pmode.circuit1 = 0;
            display_environments[i].pmode.circuit2 = 0;
        }
    }
}

/** @brief Rebuild the scaled display's packets, if it's scaled and has a draw area. */
void LibCameraContext::refresh_scaled_packets()
{
    if (display_area.scaled && display_area.width > 0 && display_area.height > 0)
    {
        build_scaled_packets();
    }
}

/**
 * @brief Offset a draw environment's contexts by half a pixel on odd fields.
 * @param environment Environment whose context-1 and context-2 offsets are set.
 * @param field Field being drawn.
 */
static inline void set_half_offset(LibDrawEnvironment* environment, u32 field)
{
    sceGsSetHalfOffset(&environment->context1, GS_COORDINATE_CENTRE, GS_COORDINATE_CENTRE, field);
    sceGsSetHalfOffset2(&environment->context2, GS_COORDINATE_CENTRE, GS_COORDINATE_CENTRE, field);
}

/**
 * @brief Wait for the next field and set the draw buffers' half-pixel offsets for it.
 * @param frame Render iteration, which picks the draw buffer.
 * @return Field the frame is drawn for (always 0 for progressive output).
 */
u32 LibCameraContext::wait_for_field(s32 frame)
{
    ResidentInputSystem* input = resident_system_get_input(&g_system);
    u32 field;

    if (unk3E68 != 0)
    {
        unk3E68--;
    }

    if (unk3E65 != 0 && frame >= 0)
    {
        shown_buffers[unk3E69 ^ 1] = (frame - 1) % LIB_DISPLAY_BUFFER_COUNT;
    }

    if (unk3E66 != 0)
    {
        shown_buffers[0] = (frame - 1) % LIB_DISPLAY_BUFFER_COUNT;
    }

    unk3E6B = 1;
    field = resident_input_wait_vblank(input, 0) ^ 1;

    if (resident_get_system()->progressive)
    {
        field = 0;
    }

    if (display_area.scaled)
    {
        return field;
    }

    unk3E50 = field ^ 1;

    if (unk3E65 != 0)
    {
        field = unk3E69;
        unk3E69 = field ^ 1;
    }

    if (unk3E66 != 0)
    {
        unk3E69 = 0;
        field = 0;
    }

    // TODO: display_area.scaled was already handled above; this second test is the only shape I found that matches.
    if (!display_area.scaled)
    {
        unk3E4C = field;

        if (frame_buffer_count == LIB_DISPLAY_BUFFER_COUNT)
        {
            switch (frame % LIB_DISPLAY_BUFFER_COUNT)
            {
            case 0:
                set_half_offset(&buffers[0].environment, field);
                break;
            case 1:
                set_half_offset(&buffers[1].environment, field);
                break;
            case 2:
                set_half_offset(&buffers[2].environment, field);
                break;
            }
        }
        else if (frame & 1)
        {
            set_half_offset(&buffers[1].environment, field);
            set_half_offset(&environments[1], field);
        }
        else
        {
            set_half_offset(&buffers[0].environment, field);
            set_half_offset(&environments[0], field);
        }
    }

    return field;
}

/**
 * @brief Rebuild the clear packets of a screen's two draw buffers in a colour: the first at the screen's size, the
 *        second at its view size, both centred, with the depth test of the second buffer's first context.
 * @param display Display that owns the screen.
 * @param index Screen index.
 * @param red Red component.
 * @param green Green component.
 * @param blue Blue component.
 * @param alpha Alpha component.
 */
extern "C" void func_004DD310(LibCameraContext* display, s32 index, u8 red, u8 green, u8 blue, u8 alpha)
{
    s16 width = display->screens[index].width;
    s16 height = display->screens[index].height;
    s32 depth_method = display->screens[index].buffers[1].environment.context1.test.depth_method;

    display->func_004DB600(&display->screens[index].buffers[0].clear, depth_method,
                           GS_COORDINATE_CENTRE - (width >> 1), GS_COORDINATE_CENTRE - (height >> 1), width, height,
                           red, green, blue, alpha, 0);
    width = display->screens[index].view_width;
    height = display->screens[index].view_height;
    display->func_004DB600(&display->screens[index].buffers[1].clear, depth_method,
                           GS_COORDINATE_CENTRE - (width >> 1), GS_COORDINATE_CENTRE - (height >> 1), width, height,
                           red, green, blue, alpha, 0);
}
