#include "overlays/lib/texture_scroll_channel.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "sdk/main/libdma_0012B2C8.h"
#include "sdk/main/libgraph_0012EAC8.h"
#include "main/resident_00101260.h"
#include "sdk/main/libkernl_00121940.h"
#include "overlays/lib/palette_blend_channel.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/lib/text_0043A920.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/matrix_vu0.h"
#include "vu0.h"
#include "overlays/lib/quaternion_vu0.h"
#include "overlays/lib/direction_vu0.h"
#include "overlays/lib/quaternion_inlines.h"
#include "ee.h"
#include "clamp.h"
#include "main/resident_data.h"
#include "main/resident_001001E0.h"
#include "overlays/lib/text_004DD440.h"
#include "overlays/lib/text_0046AE20.h"
#include "sdk/main/libm_guess_0013F3E0.h"
#include "include_asm.h"
#include "overlays/lib/render_buffer.h"
#include "overlays/lib/render_channel.h"
#include "overlays/lib/text_004DD440.h"
#include "main/resident_0010A0E0.h"

#define TEXTURE_TRANSFER_GIF_TAG 0x1000000000008004ULL

/** Request tag ('MlPs') whose misses are only loaded when an address is wanted. */
#define LIB_TEXTURE_TAG_MLPS 0x4D6C5073

/** Highest and lowest priority a cached texture's user can reach. */
#define LIB_TEXTURE_PRIORITY_MAX 10
#define LIB_TEXTURE_PRIORITY_MIN -10

/** Lowest priority at which a hit still moves a user's texture to the front. */
#define LIB_TEXTURE_PRIORITY_KEEP -5

/** VRAM slot the screen text font is uploaded to. */
#define LIB_SCREEN_TEXT_FONT_SLOT 31

/** Archive key of the screen text font image. */
#define LIB_SCREEN_TEXT_FONT_KEY 11

/** Resource queue tag and priority the font is read with. */
#define LIB_SCREEN_TEXT_FONT_TAG 2
#define LIB_SCREEN_TEXT_FONT_PRIORITY 0x34BC0

/** Character cell size in screen pixels, before the display's area scale. */
#define LIB_SCREEN_TEXT_CELL_SIZE 16.01f

/** TEX0 size and colour bits of the font: 256x256 (TW = TH = 8) with alpha (TCC). */
#define LIB_SCREEN_TEXT_FONT_TEX0 0x620000000ULL

/** PRIM for the text: textured, alpha-blended sprites with UV coordinates, in context 2. */
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

/** Registers Lib's frame packet resets at the start of each frame. */
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
    IMAGE_SEQUENCE_CLAMP = 2,
    RENDER_DATA_INLINE = 0,
    RENDER_DATA_SHARED = 1,
    RENDER_DATA_OFFSET = 4,
    RENDER_DATA_RESOLVED = 5
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

/** Resource record prefix whose data word can hold an offset or resolved pointer. */
struct LibRenderDataRecord
{
    u32 next_offset;
    s16 storage_kind;
    s16 index;
    u32 key08;
    u32 key0c;
    u8 unk10[0x10];
    void* resolved_data;
    u32 unk24;

    union
    {
        void* data;
        u32 data_offset;
    };

    u32 unk2c;
};

extern "C" void func_004D6C20(LibUpdateList* list, void** items, u32* offsets);
extern "C" LibRenderDataRecord* func_00448910(u32 first_key, u32 second_key);

struct LibFieldPointer634
{
    u8 unk00[0x634];
    void* unk634;
};

#define HALF_PI 1.57079637050628662109375f

extern "C" LibDisplayManager* D_001B6628;
extern "C" ResidentDmaQueue* D_001B660C;

/** @brief View an aligned matrix row as a vector. @param matrix Source matrix. @param index Row index. @return Read-only row vector. */
static inline const FieldVec4A& matrix_row_vector(const LibMatrix44Value& matrix, s32 index)
{
    return *(const FieldVec4A*)matrix.m[index];
}

/** @brief View an aligned matrix row as a writable vector. @param matrix Destination matrix. @param index Row index. @return Writable row vector. */
static inline FieldVec4A& matrix_row_vector(LibMatrix44Value& matrix, s32 index)
{
    return *(FieldVec4A*)matrix.m[index];
}

/**
 * @brief Interpolate along the shorter quaternion arc and normalize the result.
 * @param output Aligned destination quaternion; may alias either input.
 * @param first First aligned quaternion.
 * @param second Second aligned quaternion.
 * @param fraction Interpolation fraction.
 */
extern "C" void func_004CD3A0(FieldVec4B* output, const FieldVec4B* first, const FieldVec4B* second, float fraction)
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CD8C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CDA40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CDBC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CE040);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CE930);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CEBA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CECD0);

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

/** @brief Invert an orthonormal rotation and its row-vector translation. @param input Source matrix. @param output Destination matrix, distinct from input. */
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CEFD0);

/** @brief Invert an orthonormal rotation and its translation column. @param input Source transformation matrix. @return Inverse transformation matrix. */
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

/** @brief Invert a nonsingular matrix. @param input Source matrix. @param output Destination matrix, which may alias input. */
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CF580);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", lib_normalize_vector3);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CF640);

/** @brief Multiply a matrix by a column vector. @param matrix Source matrix. @param value Source vector. @return Transformed vector. */
extern "C" FieldVec4A func_004CF6C0(const LibMatrix44Value& matrix, const FieldVec4A& value)
{
    FieldVec4A result;
    result.x = matrix.m[0][0] * value.x + matrix.m[0][1] * value.y + matrix.m[0][2] * value.z + matrix.m[0][3] * value.w;
    result.y = matrix.m[1][0] * value.x + matrix.m[1][1] * value.y + matrix.m[1][2] * value.z + matrix.m[1][3] * value.w;
    result.z = matrix.m[2][0] * value.x + matrix.m[2][1] * value.y + matrix.m[2][2] * value.z + matrix.m[2][3] * value.w;
    result.w = matrix.m[3][0] * value.x + matrix.m[3][1] * value.y + matrix.m[3][2] * value.z + matrix.m[3][3] * value.w;
    return result;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CF7C0);

/** @brief Multiply a row vector by a matrix. @param value Source vector. @param matrix Source matrix. @return Transformed vector. */
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

/** @brief Set the upper 3x3 rotation from three angles. @param output Matrix whose rotation is updated. @param angles Three rotation angles in radians. */
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

/** @brief Set the upper 3x3 rotation about the Y axis. @param output Matrix whose rotation is updated. @param angle Rotation angle in radians. */
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

/** @brief Clear all sixteen matrix components. @param matrix Matrix to clear. */
extern "C" void func_004CFF80(LibMatrix44Value* matrix)
{
    ((unsigned __int128*)matrix)[0] = 0;
    ((unsigned __int128*)matrix)[1] = 0;
    ((unsigned __int128*)matrix)[2] = 0;
    ((unsigned __int128*)matrix)[3] = 0;
}

/** @brief Copy the source transform through its virtual setters, then copy its manager and flags. @param source Transform source. */
void LibTransformOwner::copy_transform_state(const LibTransformOwner* source)
{
    set_translation_vector(&source->translation);
    set_orientation(&source->orientation);
    set_scale_vector(&source->scale);
    unk80 = source->unk80;
    draw_flags = source->draw_flags;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", destroy__17LibTransformOwnerFv);

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
        LibRenderer* renderer = static_cast<LibRenderer*>(D_001B661C);

        if (renderer->main_packet == object)
        {
            renderer->main_packet_busy = 0;
            renderer->packet_ticks = TIMER0_COUNT - renderer->packet_start_time;
            func_004DC420(D_001B65DC, 1);
            renderer->main_packet = 0;
        }
    }
    else
    {
        LibRenderer* renderer = static_cast<LibRenderer*>(D_001B661C);

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

extern "C" s32 func_004D0160(void* object)
{
    return 16;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D0170);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D0260);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D02E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D0330);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D03D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D0460);

/**
 * @brief Finish the transform receiver's packet.
 * @param object Transform owner.
 */
extern "C" void func_004D04A0(LibTransformOwner* object)
{
    lib_finish_packet(object);
}

/** Queue the DMA submission embedded at offset 0x90 when present. */
s32 func_004D04C0(void* object)
{
    DmaSubmission* submission = reinterpret_cast<DmaSubmission*>(object);
    if (object != 0)
    {
        submission = (DmaSubmission*)((u8*)submission + 0x90);
    }
    return func_00114100(g_vif1_dma_queue, submission);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D04F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D0640);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D06E0);

/**
 * @brief Finish the transform receiver's packet.
 * @param object Transform owner.
 */
extern "C" void func_004D0720(LibTransformOwner* object)
{
    lib_finish_packet(object);
}

/** Queue the DMA submission embedded at offset 0x90 when present. */
s32 func_004D0740(void* object)
{
    DmaSubmission* submission = reinterpret_cast<DmaSubmission*>(object);
    if (object != 0)
    {
        submission = (DmaSubmission*)((u8*)submission + 0x90);
    }
    return func_00114100(g_vif1_dma_queue, submission);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D0770);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D0830);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D08D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D0A30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D0B10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D0F80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D12A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D12F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D1320);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D1360);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D1550);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D2C70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D3290);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D3480);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D3780);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D4010);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D44D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D4560__11LibRendererFv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D4700__11LibRendererFv);

/** @brief Start a frame: swap packet buffers and, with a list and a camera, build the frame's packets. */
void LibRenderer::begin_frame()
{
    func_004D9A80(D_001B65FC, 0);
    D_001B668C = 1.0f / g_frame_ticks;

    if (manager == 0)
    {
        func_004D99B0(D_001B65FC);
        return;
    }

    func_004D99B0(D_001B65FC);
    func_004DB150(manager);
    func_004C8390(manager);
    unk40cb = 0;
    unk40a0 = 0;
    unk408c = 0;
    packet_ticks = 0;
    cursor = buffers[buffer_index];
    current_list = lists[buffer_index];
    buffer_index ^= 1;
    main_packet = 0;
    packet_start_time = 0;

    if (current_list != 0 && manager->current_display != 0)
    {
        D_001B65C8 = func_004DBCA0(display, 0);
        unk40b0 = 0;
        func_004D4700();
        func_004D4560();
    }

    unk40ca = 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D4D00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D4EB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D4F60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5060);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5160);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5650);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D56B0);

/** @brief Clear the intrusive owner and invoke the base removal hook. @param object Transform owner to detach. */
extern "C" void func_004D5740(LibTransformOwner* object)
{
    object->owner = 0;
    object->LibTransformOwner::destroy();
}

/** @brief Clear the intrusive owner and invoke the base removal hook. @param object Transform owner to detach. */
extern "C" void func_004D5760(LibTransformOwner* object)
{
    object->owner = 0;
    object->LibTransformOwner::destroy();
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5780);

extern "C" s32 func_004D5810(void* object)
{
    return 10;
}

extern "C" void func_004D5820(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5830);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5840);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5850);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5860);

/**
 * @brief Hand the camera's view-projection matrix to the VU0 microprogram at 0x1F0.
 * @param camera Camera whose matrices are used.
 */
extern "C" void lib_load_camera_screen_matrix(const LibClass179080* camera)
{
    LibMatrix44Value matrix = func_004CF7C0(camera->projection_matrix, camera->view_matrix);
    vu0_start_microprogram_1f0_vf5_vf8(&matrix);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", __ct__14LibClass172000Fv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5940);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5A50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5A90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5AC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5AF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5B50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5BB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5C10);

extern "C" void func_004486A0(LibResourceBuffer* resource);
extern "C" void func_004D0260(void* owner, LibResourceBuffer* resource);
extern "C" void* D_001B6640;

/** @brief Unregister the resource from the resource manager if it is registered. */
void LibResourceBuffer::unregister()
{
    if (registered)
    {
        registered = 0;
        func_004486A0(this);
        func_004D0260(D_001B6640, this);
    }
}

/** @brief Unregister the resource and release owned data. */
LibResourceBuffer::~LibResourceBuffer()
{
    if (registered)
    {
        func_004486A0(this);
        func_004D0260(D_001B6640, this);
    }

    if (!external_data)
    {
        ::operator delete(data);
    }
}

extern "C" s32 func_004D5D70(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5D80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5E10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5F50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5FE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D6000);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D6020);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D6040);

extern "C" void func_004D6230(void* receiver, u32 arg1, u32 arg2)
{
    LibFieldPointer634* object = (LibFieldPointer634*)receiver;
    func_00448A10(object->unk634, arg1, arg2);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D6250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D62A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D6380);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D6430);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D6510);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D6700);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", update_nodes__13LibUpdateListFv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D68F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D69A0);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D6C20);

extern "C" s32 func_004D6DB0(const LibListNode* node)
{
    return node->unk0c;
}

extern "C" s32 func_004D6DC0(const void* sentinel, const void* node)
{
    return sentinel == node;
}

extern "C" LibListNode* func_004D6DD0(const LibListNode* node)
{
    return node->next;
}

extern "C" void* func_004D6DE0(void* object)
{
    return object;
}

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", __dt__13LibUpdateListFv);

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
    D_001B6650->get_area_scale(&scale_x, &scale_y);
    cell_width = (u8)(s32)(LIB_SCREEN_TEXT_CELL_SIZE * scale_x);
    cell_height = (u8)(s32)(0.5f * (LIB_SCREEN_TEXT_CELL_SIZE * scale_y));
    display = D_001B6650;
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
    tex0 = (u64)D_001B65E0->unk04[LIB_SCREEN_TEXT_FONT_SLOT] | LIB_SCREEN_TEXT_FONT_TEX0;
    setup->tex0 = tex0 | func_004DC800(D_001B65E0, LIB_SCREEN_TEXT_FONT_SLOT, 0, 1);
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", update__22LibPaletteBlendChannelFv);

/**
 * @brief Bind the selected image from the source resource.
 *
 * A nonempty record list with no matching selector reports success and keeps
 * the previous target. Failed lookups also leave that target unchanged.
 * @return False for a missing resource, empty record list or unsupported matching storage kind; true otherwise.
 */
bool LibPaletteBlendChannel::load_resource()
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
                        target = static_cast<LibImageDataHeader*>(record->data);
                    }
                    else
                    {
                        target = reinterpret_cast<LibImageDataHeader*>(reinterpret_cast<u8*>(record) + sizeof(LibRenderDataRecord) + sizeof(LibResourceChunkHeader));
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

/** Side of the square 32-bit image lib_clear_vram uploads each pass. */
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D8C20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D8D20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D9030);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D90B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D9130);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D9200);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D9250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D92C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D9300);

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
u32 LibTextureCache::find_texture(LibTextureRequest* request, u32 tag, u32 id, s32 slot, s32 unk5, s32 want_address, LibTextureUser* user)
{
    u32 index;

    for (index = next[0]; index != 0; index = next[index])
    {
        if (keys[index].id == id && entries[index].tag == tag)
        {
            keys[index].stamp = stamp;

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D9590);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D9670);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", __ct__15LibTextureCacheFii);

extern "C" void* func_004D99A0(void* object)
{
    return object;
}

extern "C" void func_004D99B0(LibBusyObject* object)
{
    while (object->busy)
    {
    }
}

/** @brief Clear the object's busy flag. @param object Object to release. */
extern "C" void func_004D99E0(LibBusyObject* object)
{
    object->busy = 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D99F0);

/** @brief Queue the object for DMA after marking it busy and storing its channel. @param object Transfer object implementing the DMA callbacks. @param channel DMA channel selector stored at offset 0x51. @return Queue insertion result. */
extern "C" s32 func_004D9A80(LibBusyObject* object, u8 channel)
{
    object->busy = 1;
    object->channel = channel;
    // The queue invokes the submission callbacks through the object's vtable.
    return func_00114100(D_001B660C, reinterpret_cast<DmaSubmission*>(object));
}

/** @brief Queue the object again when its DMA channel changes. @param object Transfer object implementing the DMA callbacks. @param channel Requested DMA channel. */
extern "C" void func_004D9AB0(LibBusyObject* object, u8 channel)
{
    if (object->channel == channel)
    {
        return;
    }

    object->busy = 1;
    object->channel = channel;
    func_00114100(D_001B660C, reinterpret_cast<DmaSubmission*>(object));
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D9AF0);

extern "C" void func_004D9B50(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D9B60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D9BA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D9BF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D9C30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D9C60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D9CD0);

/** @brief Apply the enabled camera-facing rotation components. */
void LibTransform::update()
{
    if (draw_flags & 0x380)
    {
        LibClass179080* camera;
        if (unk80 != 0)
        {
            camera = static_cast<LibClass179080*>(unk80->current_display);
        }
        else
        {
            camera = static_cast<LibClass179080*>(D_001B6628->current_display);
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
            if (draw_flags & 0x80)
            {
                angles.x = -camera_angles[0];
            }
            if (draw_flags & 0x100)
            {
                angles.y = camera_angles[1];
            }
            if (draw_flags & 0x200)
            {
                angles.z = -camera_angles[2];
            }
            angles.y += 3.1415927f;
            set_rotation_vector(&angles);
            matrix_ready = 0;
        }
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D9E70);

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

/** @brief Copy a complete local vector. @param output Destination vector. @param input Source vector. */
extern "C" void func_004DA040(LibVector4* output, const LibVector4* input)
{
    copy_vector(output, input);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DA050);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DA0F0);

extern "C" u16 func_004DA2B0(const LibTransform* object)
{
    return object->unk20c;
}

/** @brief Mark each transform in the parent chain dirty. @param object First transform, or null. */
extern "C" void lib_invalidate_transform_chain(LibTransform* object)
{
    for (; object != 0; object = object->parent_transform)
    {
        object->matrix_ready = 0;
    }
}

/** Joints are left alone once the end and the target directions are this close. */
#define LIB_IK_ALIGNED_COSINE 0.99999988f

/** Iterations stop once the end moves less than this along every axis. */
#define LIB_IK_SETTLED_DISTANCE 1.0f

/**
 * @brief Read the parent's combined matrix, updating the parent first if needed.
 * @param object Transform whose parent is read.
 * @return Parent's base transform, or null without a parent.
 */
static inline const LibMatrix44Value* lib_get_parent_matrix(LibTransform* object)
{
    if (object->parent_transform == 0)
    {
        return 0;
    }

    if (!object->parent_transform->matrix_ready)
    {
        object->parent_transform->update_transform_matrix();

        if (object->parent_transform->unk51)
        {
            object->transform_dirty = 1;
        }
    }

    return &object->parent_transform->base_transform;
}

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

/** @brief Extract the transform's translation column. @param object Transform owner. @return Translation coordinates with homogeneous component one. */
extern "C" FieldVec4B func_004DA6F0(const LibTransform* object)
{
    FieldVec4B result;
    result.x = object->transform.m[0][3];
    result.y = object->transform.m[1][3];
    result.z = object->transform.m[2][3];
    result.w = 1.0f;
    return result;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DA730);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", update_transform_matrix__12LibTransformFv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", lib_rebuild_offset_transform);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", __dt__12LibTransformFv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DAD90);

extern "C" s32 func_004DAFD0(void* object)
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DB0F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DB120);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DB150);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DB190);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DB3E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DB3F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DB400);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DB410);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DB530);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DB570);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DB5B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DB600);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", build_clear__16LibCameraContextFP14LibScreenClearsssssUcUcUcUcUi);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DB9E0);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DBC70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DBCA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DBD80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DBEE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DBFB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DC140);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DC180);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DC200);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DC420);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DC4F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DC680);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DC750);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DC7F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DC800);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DC8B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DC970);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DCA70);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DCCA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DCD10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DCDA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DCDE0);

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
    if (scaled && display_area.width > 0 && display_area.height > 0)
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
    field = func_0011DF10(input, 0) ^ 1;

    if (resident_get_system()->progressive)
    {
        field = 0;
    }

    if (scaled)
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

    // TODO: scaled was already handled above; this second test is the only shape I found that matches.
    if (!scaled)
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DD310);
