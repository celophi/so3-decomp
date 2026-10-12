#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/matrix_vu0.h"
#include "overlays/lib/text_004DD440.h"
#include "overlays/lib/text_0046AE20.h"
#include "sdk/main/libm_guess_0013F3E0.h"
#include "include_asm.h"

extern "C" LibClass178F30* D_001B6628;

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CD3A0);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CD630);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CEA90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CEAE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CEB20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CEBA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CECD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CED40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004CEE30);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D0090);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D04A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D04C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D04F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D0640);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D06E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D0720);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D0740);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5740);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D5760);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D6230);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D6250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D62A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D6380);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D6430);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D6510);

/** Partial node prefix with its registered list owner at offset 0x10. */
struct LibOwnedObjectState
{
    u8 pad00[0x10];
    LibClass178DD0* owner;
};
/**
 * @brief Remove the object from its owner and clear the owner pointer.
 * @param object Object whose owner receives the removal callback.
 */
extern "C" void lib_object_detach_owner(void* object)
{
    LibOwnedObjectState* state = (LibOwnedObjectState*)object;
    if (state->owner)
    {
        state->owner->func_004D72A0(object);
    }
    state->owner = 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D6610);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D6660);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D66B0);

extern "C" void func_004D66F0(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D6700);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D6730);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D68F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D69A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D6AF0);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D6DF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D72A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D7380);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D73B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D7450);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D74F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", __dt__14LibClass178DD0Fv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", __ct__14LibClass178DD0Fv);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D8870);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D99E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D99F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D9A80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004D9AB0);

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
    func_004790C0(this, 1);
    func_004DA040(&unk1e0, source->func_003F4530());
    func_004DAB50(this);
    func_004790C0(this, 1);
    func_00479090(&unk1f0, source->func_003F4540());
    func_004DAB50(this);
    func_004790C0(this, 1);
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DA2B0);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004CD3A0", func_004DBB70);

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
