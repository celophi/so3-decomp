#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/text_0043A920.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/matrix_vu0.h"
#include "overlays/lib/quaternion_vu0.h"
#include "ee.h"
#include "main/resident_001001E0.h"
#include "overlays/lib/text_004DD440.h"
#include "overlays/lib/text_0046AE20.h"
#include "sdk/main/libm_guess_0013F3E0.h"
#include "include_asm.h"
#include "overlays/lib/text_004DD440.h"
#include "main/resident_0010A0E0.h"

extern "C" void func_004D6C20(LibClass178DD0* list, void** items, u32* offsets);
extern "C" void func_004D00B0(LibClass178A90* object);

struct LibFieldPointer634
{
    u8 unk00[0x634];
    void* unk634;
};

#define HALF_PI 1.57079637050628662109375f

extern "C" LibClass178F30* D_001B6628;
extern "C" ResidentDmaQueue* D_001B660C;

struct LibPointerTableFields50
{
    u8 pad00[0x50];
    void** entries;
};

struct LibHalfwordToggleFields3E78
{
    u8 pad00[0x3E78];
    s16 unk3E78;
    s16 unk3E7A;
};

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
    func_004CBAC0(&result, &converted);
    return result;
}

/**
 * @brief Interpolate along the shorter quaternion arc and normalize the result.
 * @param output Aligned destination quaternion; may alias either input.
 * @param first First aligned quaternion.
 * @param second Second aligned quaternion.
 * @param fraction Interpolation fraction.
 */
extern "C" void func_004CD630(FieldVec4B* output, const FieldVec4B* first, const FieldVec4B* second, float fraction)
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CD810);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CD8A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CD8C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CDA40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CDBC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CE040);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CE4C0);

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
    delta.x = target->components[0] - value->components[0];
    delta.y = target->components[1] - value->components[1];
    delta.z = target->components[2] - value->components[2];
    float x_squared = delta.x * delta.x;
    float y_squared = delta.y * delta.y;
    if (x_squared == 0.0f && y_squared == 0.0f)
    {
        if (delta.z < 0.0f)
        {
            value->components[0] = HALF_PI;
        }
        else
        {
            value->components[0] = -HALF_PI;
        }
        value->components[2] = 0.0f;
    }
    else
    {
        float horizontal_squared = x_squared + y_squared;
        float horizontal_distance = __sqrt(horizontal_squared, horizontal_squared);
        value->components[0] = func_00142148(-delta.z, horizontal_distance);
        value->components[2] = func_00142148(delta.x, delta.y);
    }
    value->components[1] = y_angle;
    value->components[3] = 1.0f;
}

/**
 * @brief Replace a position with direction angles toward a target, using the XZ plane for heading.
 * @param value Source position, overwritten with elevation in x, heading in y, and w set to one.
 * @param target Target position; only x, y, and z are read.
 * @param z_angle Angle to store in the z component.
 */
extern "C" void lib_direction_angles_xz(LibVector4* value, const LibVector4* target, float z_angle)
{
    float dx = target->components[0] - value->components[0];
    float dy = target->components[1] - value->components[1];
    float dz = target->components[2] - value->components[2];
    FieldVec4A delta(dx, dy, dz, 0.0f);
    float x_squared = delta.x * delta.x;
    float z_squared = delta.z * delta.z;
    if (x_squared == 0.0f && z_squared == 0.0f)
    {
        if (delta.y < 0.0f)
        {
            value->components[0] = HALF_PI;
        }
        else
        {
            value->components[0] = -HALF_PI;
        }
        value->components[1] = 0.0f;
    }
    else
    {
        float horizontal_squared = x_squared + z_squared;
        float horizontal_distance = __sqrt(horizontal_squared, horizontal_squared);
        value->components[0] = func_00142148(-delta.y, horizontal_distance);
        value->components[1] = func_00142148(delta.x, delta.z);
    }
    value->components[2] = z_angle;
    value->components[3] = 1.0f;
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CF5E0);

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
    float cosine_x = func_00141BE0(angles[0]);
    float sine_x = func_00141DD0(angles[0]);
    float cosine_y = func_00141BE0(angles[1]);
    float sine_y = func_00141DD0(angles[1]);
    float cosine_z = func_00141BE0(angles[2]);
    float sine_z = func_00141DD0(angles[2]);
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
    float cosine = func_00141BE0(angle);
    float sine = func_00141DD0(angle);
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
void LibClass178A90::func_004CFFA0(const LibClass178A90* source)
{
    func_003EF780(&source->unk20);
    func_003EEF10(&source->unk30);
    func_003EEFF0(&source->unk40);
    unk80 = source->unk80;
    unk6a = source->unk6a;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_003EF740__14LibClass178A90Fv);

/** @brief Mark the transform's matrix as ready. @param object Transform owner. */
extern "C" void func_004D0090(LibClass178A90* object)
{
    object->unk61 = 1;
}

extern "C" const void* func_004D00A0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D00B0);

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
 * @brief Forward the transform receiver to its state-update handler.
 * @param object Transform owner.
 */
extern "C" void func_004D04A0(LibClass178A90* object)
{
    func_004D00B0(object);
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
 * @brief Forward the transform receiver to its state-update handler.
 * @param object Transform owner.
 */
extern "C" void func_004D0720(LibClass178A90* object)
{
    func_004D00B0(object);
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D4560);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D4700);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D4BE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D4D00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D4EB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D4F60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5060);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5160);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5650);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D56B0);

/** @brief Clear the intrusive owner and invoke the base removal hook. @param object Transform owner to detach. */
extern "C" void func_004D5740(LibClass178A90* object)
{
    object->owner = 0;
    object->LibClass178A90::func_003EF740();
}

/** @brief Clear the intrusive owner and invoke the base removal hook. @param object Transform owner to detach. */
extern "C" void func_004D5760(LibClass178A90* object)
{
    object->owner = 0;
    object->LibClass178A90::func_003EF740();
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5870);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", __ct__14LibClass172000Fv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5940);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D59A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5A50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5A90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5AC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5AF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5B50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5BB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5C10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5C90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5CD0);

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
    LibClass171EA0* node = static_cast<LibClass171EA0*>(object);
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
extern "C" void lib_object_set_list_kind(LibClass171EA0* node, s32 kind)
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
extern "C" s32 lib_list_release_node_buffer(LibClass178DD0* owner)
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
extern "C" void lib_list_allocate_node_buffer(LibClass178DD0* owner, s32 node_count)
{
    owner->owned_node_buffer = new (0) void*[node_count];
    owner->node_buffer_capacity = node_count;
}

extern "C" void func_004D66F0(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D6700);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D6730);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D68F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D69A0);

/**
 * @brief Collect the list chain's nodes into an array grouped by list kind.
 * @param list First list whose nodes are collected.
 * @param items Array with room for every node in the chain.
 */
extern "C" void lib_list_collect_nodes_by_kind(LibClass178DD0* list, void** items)
{
    u32 offsets[LibClass178DD0::NODE_KIND_COUNT];
    u32 count = 0;
    for (s32 kind = 0; kind < LibClass178DD0::NODE_KIND_COUNT; ++kind)
    {
        offsets[kind] = count;
        count += list->node_counts_by_kind[kind];
    }
    if (list->next_list)
    {
        lib_list_add_chain_kind_offsets(list->next_list, offsets);
    }
    LibClass171E90* link = &list->sentinel;
    for (;;)
    {
        link = link->next;
        if (&list->sentinel == link)
        {
            break;
        }
        LibClass171EA0* node = reinterpret_cast<LibClass171EA0*>(link);
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
extern "C" inline void lib_list_add_chain_kind_offsets(LibClass178DD0* list, u32* offsets)
{
    u32 count = 0;
    for (s32 kind = 0; kind < LibClass178DD0::NODE_KIND_COUNT; ++kind)
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
void LibClass178DD0::remove_node(void* object)
{
    LibClass171EA0* node = static_cast<LibClass171EA0*>(object);
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
    LibClass178A70::unlink(object);
}

/**
 * @brief Transfer one node count from the node's stored kind to a new kind.
 * @param owner List whose per-kind counts are updated.
 * @param node Node supplying the old kind.
 * @param new_kind Kind whose count is incremented.
 */
extern "C" void lib_list_change_node_kind_counts(LibClass178DD0* owner, const LibClass171EA0* node, s32 new_kind)
{
    --owner->node_counts_by_kind[node->list_kind];
    ++owner->node_counts_by_kind[new_kind];
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", insert_node_after__14LibClass178DD0FPvPvi);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", prepend_node__14LibClass178DD0FPvi);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", append_node__14LibClass178DD0FPvi);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", __dt__14LibClass178DD0Fv);

/** @brief Initialize the inherited list, kind counts, and node-buffer state. */
LibClass178DD0::LibClass178DD0()
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D76C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D78F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D79F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D7AB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D7BA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D7C40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D7D40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D7E90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D8020);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D80B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D8130);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D8180);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D8700);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D8850);

void* func_004D8870(const void* object, s32 index)
{
    const LibPointerTableFields50* state = (const LibPointerTableFields50*)object;
    return state->entries[index];
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D8890);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D8970);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D8A80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D8AC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D8C20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D8D20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D9030);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D90B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D9130);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D9200);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D9250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D92C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D9300);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D93A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D9590);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D9670);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D9810);

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
void LibClass178EA0::func_003EEBD0()
{
    if (unk6a & 0x380)
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
            if (camera->unk61 == 0)
            {
                camera->func_004D0090();
            }
            LibVector4 angles;
            const float* camera_angles = camera->rotation_angles;
            func_004CDA40(&angles, &unk30);
            if (unk6a & 0x80)
            {
                angles.components[0] = -camera_angles[0];
            }
            if (unk6a & 0x100)
            {
                angles.components[1] = camera_angles[1];
            }
            if (unk6a & 0x200)
            {
                angles.components[2] = -camera_angles[2];
            }
            angles.components[1] += 3.1415927f;
            func_003EEF60(&angles);
            unk61 = 0;
        }
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D9E70);

/** @brief Copy local transform state, then copy its inherited state. @param source Transform source. */
void LibClass178EA0::func_004D9F40(const LibClass178EA0* source)
{
    if (source->unk6a & 0x20)
    {
        unk6a |= 0x20;
    }
    func_004DA050(this, source->unk200);
    func_00479090(&unk1d0, source->func_003F4520());
    func_004DAB50(this);
    lib_transform_set_dirty(this, 1);
    func_004DA040(&unk1e0, source->func_003F4530());
    func_004DAB50(this);
    lib_transform_set_dirty(this, 1);
    func_00479090(&unk1f0, source->func_003F4540());
    func_004DAB50(this);
    lib_transform_set_dirty(this, 1);
    unk20c = source->unk20c;
    unk208 = source->unk208;
    LibClass178A90::func_004CFFA0(source);
}

/** @brief Copy a complete local vector. @param output Destination vector. @param input Source vector. */
extern "C" void func_004DA040(LibVector4* output, const LibVector4* input)
{
    output->packed = input->packed;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DA050);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DA0F0);

extern "C" u16 func_004DA2B0(const LibClass178EA0* object)
{
    return object->unk20c;
}

/** @brief Mark each transform in the parent chain dirty. @param object First transform, or null. */
extern "C" void lib_invalidate_transform_chain(LibClass178EA0* object)
{
    while (object != 0)
    {
        object->unk61 = 0;
        object = object->unk208;
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DA2F0);

/** @brief Extract the transform's translation column. @param object Transform owner. @return Translation coordinates with homogeneous component one. */
extern "C" FieldVec4B func_004DA6F0(const LibClass178EA0* object)
{
    FieldVec4B result;
    result.x = object->transform.m[0][3];
    result.y = object->transform.m[1][3];
    result.z = object->transform.m[2][3];
    result.w = 1.0f;
    return result;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DA730);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D0090__14LibClass178EA0Fv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DAB50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", __dt__14LibClass178EA0Fv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DAD90);

extern "C" s32 func_004DAFD0(void* object)
{
    return 8;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DAFE0);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DB7F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DB9E0);

void func_004DBB70(void* object)
{
    LibHalfwordToggleFields3E78* state = (LibHalfwordToggleFields3E78*)object;
    state->unk3E78 = 0;
    state->unk3E7A ^= 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DBB90);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DCC10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DCCA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DCD10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DCDA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DCDE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DCEA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DCFA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DCFF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DD310);
