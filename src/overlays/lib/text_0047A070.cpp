#include "include_asm.h"
#include "overlays/lib/text_0046AE20.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/row_fill.h"

extern "C" {

typedef struct HalfwordSetterOwnertext_0046AE20
{
    u8 unk00[0x6C];
    u16 unk6c;
} HalfwordSetterOwnertext_0046AE20;

typedef struct ByteGetterOwnertext_0046AE20
{
    u8 unk00[0x4D];
    u8 unk4d;
    u8 unk4e[0x8];
    u8 unk56;
} ByteGetterOwnertext_0046AE20;

typedef struct ByteSetterOwnertext_0046AE20
{
    u8 unk00[0x4D];
    u8 unk4d;
    u8 unk4e;
    u8 unk4f;
    u8 unk50[0x4];
    u8 unk54;
    u8 unk55;
    u8 unk56;
} ByteSetterOwnertext_0046AE20;

typedef struct WordSetterOwnertext_0046AE20
{
    u8 unk00[0x48];
    u32 unk48;
    u8 unk4c[0x4];
    u32 unk50;
    u8 unk54[0x5C];
    u32 unkb0;
    u32 unkb4;
    u32 unkb8;
    u32 unkbc;
} WordSetterOwnertext_0046AE20;

typedef struct WordGetterOwnertext_0046AE20
{
    u8 unk00[0x8];
    u32 unk08;
    u32 unk0c;
    u8 unk10[0x38];
    u32 unk48;
    u8 unk4c[0x4];
    u32 unk50;
    u8 unk54[0x5C];
    u32 unkb0;
    u32 unkb4;
    u32 unkb8;
    u32 unkbc;
} WordGetterOwnertext_0046AE20;

typedef struct LibFlagState59C
{
    u8 unk00[0x59C];
    u8 unk59c;
    u8 unk59d_0 : 1;
    u8 unk59d_1_7 : 7;
} LibFlagState59C;

typedef struct LibFloatFieldOwner0046AE20
{
    u8 unk00[0x28];
    float unk28;
    u8 unk2c[4];
    float unk30;
    float unk34;
    float unk38;
    float unk3c;
    float unk40;
    float unk44;
} LibFloatFieldOwner0046AE20;

typedef struct LibManagedEntry
{
    u8 unk00;
    u8 unk01[3];
    u32 unk04;
    void* handle;
    LibEntryMetadata* metadata;
} LibManagedEntry;

typedef struct LibEntryTableHeader
{
    u32 flags;
    s32 count;
} LibEntryTableHeader;

typedef struct LibTransformByteState
{
    u8 unk00[0x50];
    u8 transform_dirty;
} LibTransformByteState;

typedef struct LibObjectFlags6A
{
    u8 unk00[0x6A];
    u16 flags;
} LibObjectFlags6A;

typedef struct ByteSourceStateOwnertext_0046AE20 { u8 pad00[0x57]; u8 state57; u8 pad58[0x48]; const u8* sourceA0; u32 valueA4; } ByteSourceStateOwnertext_0046AE20;

typedef struct TwoWordClearArgStateOwnertext_0046AE20 { u8 pad00[0x57]; u8 state57; u8 pad58[0x48]; void* unkA0; void* unkA4; } TwoWordClearArgStateOwnertext_0046AE20;

typedef struct FourQuadwordCopyTargetOwnertext_0046AE20
{
    u8 pad00[0x2C];
    u32 unk2C;
    u8 pad30[0x30];
    unsigned __int128 values60[4];
} FourQuadwordCopyTargetOwnertext_0046AE20;

typedef struct FourQuadwordCopySourceOwnertext_0046AE20
{
    u8 pad00[0x150];
    unsigned __int128 values150[4];
} FourQuadwordCopySourceOwnertext_0046AE20;


/** Store the word at receiver offset 0xB0. */
void func_0047A070(void* object, u32 value)
{
    WordSetterOwnertext_0046AE20* receiver = (WordSetterOwnertext_0046AE20*)object;
    receiver->unkb0 = value;
}

/** Return the word at receiver offset 0xB0. */
u32 func_0047A080(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = (const WordGetterOwnertext_0046AE20*)object;
    return receiver->unkb0;
}

/** Store the word at receiver offset 0xB4. */
void func_0047A090(void* object, u32 value)
{
    WordSetterOwnertext_0046AE20* receiver = (WordSetterOwnertext_0046AE20*)object;
    receiver->unkb4 = value;
}

/** Return the word at receiver offset 0xB4. */
u32 func_0047A0A0(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = (const WordGetterOwnertext_0046AE20*)object;
    return receiver->unkb4;
}

/** Store the word at receiver offset 0xB0. */
void func_0047A0B0(void* object, u32 value)
{
    WordSetterOwnertext_0046AE20* receiver = (WordSetterOwnertext_0046AE20*)object;
    receiver->unkb0 = value;
}

/** Return the word at receiver offset 0xB0. */
u32 func_0047A0C0(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = (const WordGetterOwnertext_0046AE20*)object;
    return receiver->unkb0;
}

/** Store the word at receiver offset 0xB4. */
void func_0047A0D0(void* object, u32 value)
{
    WordSetterOwnertext_0046AE20* receiver = (WordSetterOwnertext_0046AE20*)object;
    receiver->unkb4 = value;
}

/** Return the word at receiver offset 0xB4. */
u32 func_0047A0E0(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = (const WordGetterOwnertext_0046AE20*)object;
    return receiver->unkb4;
}

s32 func_0047A0F0(void* object)
{
    return 0;
}

s32 func_0047A100(void* object)
{
    return 0;
}

s32 func_0047A110(void* object)
{
    return 0;
}

s32 func_0047A120(void* object)
{
    return 0;
}

/**
 * @brief Position a row using optional linear and angular steps.
 * @param object Grid settings whose count (minus one) gives the row length.
 * @param cell Cell supplying the initial position and secondary vector.
 * @param row First element of the row.
 * @param index Nonzero to initialize each stepped element's first auxiliary value.
 * @param position_step Displacement subtracted per element, or null to copy the cell position.
 * @param angle_pair Initial two angles in radians, or null for linear stepping only.
 * @param axis_radii Initial per-axis radii used with the two angles.
 * @param angle_step Change subtracted from the two angles per element.
 * @param radius_step Change subtracted from the three radii per element.
 */
extern "C" void func_0047A130(RowFillOwner* object, RowFillCell* cell, RowFillElement* row, s32 index, const RowFillVector* position_step, const RowFillVector* angle_pair,
                         const RowFillVector* axis_radii,
                         const RowFillVector* angle_step, const RowFillVector* radius_step)
{
    if (object->secondary_emitter != 0)
    {
        cell->unk3c = object->unk3c;
    }

    bool copy_secondary_vector = false;

    if (object->unk4d != 1 && object->unk4d != 3)
    {
        copy_secondary_vector = true;
    }

    if (position_step != 0)
    {
        if (angle_pair != 0)
        {
            const RowFillCell* source_cell = cell;
            RowFillVector position;
            RowFillVector radii;
            RowFillVector angles;
            LibVector4 second_trig;
            LibVector4 first_trig;
            s32 count = object->unk10 - 1;
            angles.packed = angle_pair->packed;
            radii.packed = axis_radii->packed;
            lib_compute_sine_cosine_pair(angles.floats[0], &first_trig);
            lib_compute_sine_cosine_pair(angles.floats[1], &second_trig);
            float previous_x = first_trig.z * (radii.floats[0] * second_trig.z);
            float previous_y = radii.floats[1] * first_trig.w;
            float previous_z = first_trig.z * (radii.floats[2] * second_trig.w);
            position.packed = source_cell->position().packed;
            position.floats[3] = 1.0f;

            for (s32 i = 0; i < count; i++)
            {
                angles.floats[0] -= angle_step->floats[0];
                angles.floats[1] -= angle_step->floats[1];
                radii.floats[0] -= radius_step->floats[0];
                radii.floats[1] -= radius_step->floats[1];
                radii.floats[2] -= radius_step->floats[2];
                lib_compute_sine_cosine_pair(angles.floats[0], &first_trig);
                lib_compute_sine_cosine_pair(angles.floats[1], &second_trig);
                float x = first_trig.z * (radii.floats[0] * second_trig.z);
                position.floats[0] += x - previous_x;
                previous_x = x;
                float y = radii.floats[1] * first_trig.w;
                position.floats[1] += y - previous_y;
                previous_y = y;
                float z = first_trig.z * (radii.floats[2] * second_trig.w);
                position.floats[2] += z - previous_z;
                previous_z = z;
                position.floats[0] -= position_step->floats[0];
                position.floats[1] -= position_step->floats[1];
                position.floats[2] -= position_step->floats[2];
                row->unk10.packed = position.packed;

                if (copy_secondary_vector)
                {
                    row->unk20 = source_cell->unk20;
                }

                row->unk30.packed = 0;

                if (index != 0)
                {
                    row->unk30.floats[0] = object->unk28;
                }

                row++;
            }
        }
        else
        {
            s32 count = object->unk10 - 1;
            RowFillVector position;
            position.packed = cell->position().packed;

            for (s32 i = 0; i < count; i++)
            {
                position.floats[0] -= position_step->floats[0];
                position.floats[1] -= position_step->floats[1];
                position.floats[2] -= position_step->floats[2];
                row->unk10.packed = position.packed;

                if (copy_secondary_vector)
                {
                    row->unk20 = cell->unk20;
                }

                row->unk30.packed = 0;

                if (index != 0)
                {
                    row->unk30.floats[0] = object->unk28;
                }

                row++;
            }
        }
    }
    else
    {
        s32 count = object->unk10 - 1;

        for (s32 i = 0; i < count; i++)
        {
            row->unk10 = cell->position();

            if (copy_secondary_vector)
            {
                row->unk20 = cell->unk20;
            }

            row->unk30.packed = 0;
            row++;
        }
    }
}

/**
 * @brief Fill a row of elements from a cell, or from an explicit vector.
 * @param object Owner whose count (minus one) gives the row length.
 * @param cell Cell whose vectors are copied.
 * @param row First element of the row.
 * @param index Unused.
 * @param source Vector copied to each element, or null to use the cell's position.
 */
extern "C" void func_0047A540(RowFillOwner* object, RowFillCell* cell, RowFillElement* row, s32 index, const RowFillVector* source)
{
    if (object->secondary_emitter != 0)
    {
        cell->unk3c = object->unk3c;
    }

    bool blend = false;

    if (object->unk4d != 1 && object->unk4d != 3)
    {
        blend = true;
    }

    s32 count = object->unk10 - 1;

    if (source == 0)
    {
        for (s32 i = 0; i < count; i++)
        {
            row->unk10 = cell->position();

            if (blend)
            {
                row->unk20 = cell->unk20;
            }

            row->unk30.packed = 0;
            row++;
        }
    }
    else
    {
        for (s32 i = 0; i < count; i++)
        {
            row->unk10 = *source;

            if (blend)
            {
                row->unk20 = cell->unk20;
            }

            row->unk30.packed = 0;
            row++;
        }
    }
}

/**
 * @brief Store the value at receiver offset 0x28.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047A640(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = (LibFloatFieldOwner0046AE20*)object;
    receiver->unk28 = value;
}

/**
 * @brief Store the value at receiver offset 0x30.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047A650(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = (LibFloatFieldOwner0046AE20*)object;
    receiver->unk30 = value;
}

/** Return the float member at receiver offset 0x30. */
float func_0047A660(void* object)
{
    LibFloatFieldOwner0046AE20* receiver = (LibFloatFieldOwner0046AE20*)object;
    return receiver->unk30;
}

/** Store the byte at receiver offset 0x4D. */
void func_0047A670(void* object, u8 value)
{
    ByteSetterOwnertext_0046AE20* receiver = (ByteSetterOwnertext_0046AE20*)object;
    receiver->unk4d = value;
}

/** Return the unsigned byte at receiver offset 0x4D. */
u8 func_0047A680(const void* object)
{
    const ByteGetterOwnertext_0046AE20* receiver = (const ByteGetterOwnertext_0046AE20*)object;
    return receiver->unk4d;
}

/**
 * @brief Store the value at receiver offset 0x34.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047A690(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = (LibFloatFieldOwner0046AE20*)object;
    receiver->unk34 = value;
}

/** Store the byte at receiver offset 0x56. */
void func_0047A6A0(void* object, u8 value)
{
    ByteSetterOwnertext_0046AE20* receiver = (ByteSetterOwnertext_0046AE20*)object;
    receiver->unk56 = value;
}

/** Return the unsigned byte at receiver offset 0x56. */
u8 func_0047A6B0(const void* object)
{
    const ByteGetterOwnertext_0046AE20* receiver = (const ByteGetterOwnertext_0046AE20*)object;
    return receiver->unk56;
}

/**
 * @brief Store the value at receiver offset 0x44.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047A6C0(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = (LibFloatFieldOwner0046AE20*)object;
    receiver->unk44 = value;
}

/** Return the float member at receiver offset 0x44. */
float func_0047A6D0(void* object)
{
    LibFloatFieldOwner0046AE20* receiver = (LibFloatFieldOwner0046AE20*)object;
    return receiver->unk44;
}

/** Return the float member at receiver offset 0x28. */
float func_0047A6E0(void* object)
{
    LibFloatFieldOwner0046AE20* receiver = (LibFloatFieldOwner0046AE20*)object;
    return receiver->unk28;
}

/** Store the word at receiver offset 0x48. */
void func_0047A6F0(void* object, u32 value)
{
    WordSetterOwnertext_0046AE20* receiver = (WordSetterOwnertext_0046AE20*)object;
    receiver->unk48 = value;
}

/** Return the word at receiver offset 0x48. */
u32 func_0047A700(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = (const WordGetterOwnertext_0046AE20*)object;
    return receiver->unk48;
}

/** Store the byte at receiver offset 0x4F. */
void func_0047A710(void* object, u8 value)
{
    ByteSetterOwnertext_0046AE20* receiver = (ByteSetterOwnertext_0046AE20*)object;
    receiver->unk4f = value;
}

/** Store the byte at receiver offset 0x4E. */
void func_0047A720(void* object, u8 value)
{
    ByteSetterOwnertext_0046AE20* receiver = (ByteSetterOwnertext_0046AE20*)object;
    receiver->unk4e = value;
}

/** Store the word at receiver offset 0x50. */
void func_0047A730(void* object, u32 value)
{
    WordSetterOwnertext_0046AE20* receiver = (WordSetterOwnertext_0046AE20*)object;
    receiver->unk50 = value;
}

/** Return the word at receiver offset 0x50. */
u32 func_0047A740(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = (const WordGetterOwnertext_0046AE20*)object;
    return receiver->unk50;
}

/** Store the byte at receiver offset 0x55. */
void func_0047A750(void* object, u8 value)
{
    ByteSetterOwnertext_0046AE20* receiver = (ByteSetterOwnertext_0046AE20*)object;
    receiver->unk55 = value;
}

/**
 * @brief Store the value at receiver offset 0x3C.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047A760(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = (LibFloatFieldOwner0046AE20*)object;
    receiver->unk3c = value;
}

/** Store the byte at receiver offset 0x54. */
void func_0047A770(void* object, u8 value)
{
    ByteSetterOwnertext_0046AE20* receiver = (ByteSetterOwnertext_0046AE20*)object;
    receiver->unk54 = value;
}

/**
 * @brief Store the value at receiver offset 0x40.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047A780(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = (LibFloatFieldOwner0046AE20*)object;
    receiver->unk40 = value;
}

void func_0047A790(void* object, const u8* source, u32 value)
{
    ByteSourceStateOwnertext_0046AE20* receiver = (ByteSourceStateOwnertext_0046AE20*)object;
    receiver->sourceA0 = source;
    receiver->valueA4 = value;

    if (*receiver->sourceA0 == 1)
    {
        receiver->state57 = 1;
    }
    else
    {
        receiver->state57 = 0;
    }
}

void func_0047A7D0(void* object, s32 enabled)
{
    TwoWordClearArgStateOwnertext_0046AE20* receiver = (TwoWordClearArgStateOwnertext_0046AE20*)object;
    receiver->unkA0 = 0;
    receiver->unkA4 = 0;

    if (enabled)
    {
        receiver->state57 = 1;
    }
    else
    {
        receiver->state57 = 0;
    }
}

/**
 * @brief Store the value at receiver offset 0x38.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047A800(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = (LibFloatFieldOwner0046AE20*)object;
    receiver->unk38 = value;
}

void func_0047A810(void* object, const void* source)
{
    FourQuadwordCopyTargetOwnertext_0046AE20* receiver = (FourQuadwordCopyTargetOwnertext_0046AE20*)object;
    const FourQuadwordCopySourceOwnertext_0046AE20* values = (const FourQuadwordCopySourceOwnertext_0046AE20*)source;
    receiver->unk2C = 0;
    receiver->values60[0] = values->values150[0];
    receiver->values60[1] = values->values150[1];
    receiver->values60[2] = values->values150[2];
    receiver->values60[3] = values->values150[3];
}

void func_0047A840(void* object)
{
}

s32 func_0047A850(void* object)
{
    return 1;
}

typedef struct MappedEntry0047A860
{
    u8 unk00[0x120];
} MappedEntry0047A860;

typedef struct MappedOwner0047A860
{
    u8 unk00[0x14];
    MappedEntry0047A860* entries;
} MappedOwner0047A860;

void* func_0047A860(const void* object, s32 index)
{
    const MappedOwner0047A860* owner = (const MappedOwner0047A860*)object;
    MappedEntry0047A860* item = &owner->entries[index];
    void* result = item;

    if (item != 0)
    {
        result = (u8*)item + 0xF0;
    }

    return result;
}

/**
 * @brief Position a row using optional linear and angular steps.
 * @param object Grid settings whose count (minus one) gives the row length.
 * @param cell Cell supplying the initial position and secondary vector.
 * @param row First element of the row.
 * @param index Nonzero to initialize each stepped element's first auxiliary value.
 * @param position_step Displacement subtracted per element, or null to copy the cell position.
 * @param angle_pair Initial two angles in radians, or null for linear stepping only.
 * @param axis_radii Initial per-axis radii used with the two angles.
 * @param angle_step Change subtracted from the two angles per element.
 * @param radius_step Change subtracted from the three radii per element.
 */
extern "C" void func_0047A890(RowFillOwner* object, RowFillCell* cell, RowFillElement* row, s32 index, const RowFillVector* position_step, const RowFillVector* angle_pair,
                         const RowFillVector* axis_radii,
                         const RowFillVector* angle_step, const RowFillVector* radius_step)
{
    if (object->secondary_emitter != 0)
    {
        cell->unk3c = object->unk3c;
    }

    bool copy_secondary_vector = false;

    if (object->unk4d != 1 && object->unk4d != 3)
    {
        copy_secondary_vector = true;
    }

    if (position_step != 0)
    {
        if (angle_pair != 0)
        {
            const RowFillCell* source_cell = cell;
            RowFillVector position;
            RowFillVector radii;
            RowFillVector angles;
            LibVector4 second_trig;
            LibVector4 first_trig;
            s32 count = object->unk10 - 1;
            angles.packed = angle_pair->packed;
            radii.packed = axis_radii->packed;
            lib_compute_sine_cosine_pair(angles.floats[0], &first_trig);
            lib_compute_sine_cosine_pair(angles.floats[1], &second_trig);
            float previous_x = first_trig.z * (radii.floats[0] * second_trig.z);
            float previous_y = radii.floats[1] * first_trig.w;
            float previous_z = first_trig.z * (radii.floats[2] * second_trig.w);
            position.packed = source_cell->position().packed;
            position.floats[3] = 1.0f;

            for (s32 i = 0; i < count; i++)
            {
                angles.floats[0] -= angle_step->floats[0];
                angles.floats[1] -= angle_step->floats[1];
                radii.floats[0] -= radius_step->floats[0];
                radii.floats[1] -= radius_step->floats[1];
                radii.floats[2] -= radius_step->floats[2];
                lib_compute_sine_cosine_pair(angles.floats[0], &first_trig);
                lib_compute_sine_cosine_pair(angles.floats[1], &second_trig);
                float x = first_trig.z * (radii.floats[0] * second_trig.z);
                position.floats[0] += x - previous_x;
                previous_x = x;
                float y = radii.floats[1] * first_trig.w;
                position.floats[1] += y - previous_y;
                previous_y = y;
                float z = first_trig.z * (radii.floats[2] * second_trig.w);
                position.floats[2] += z - previous_z;
                previous_z = z;
                position.floats[0] -= position_step->floats[0];
                position.floats[1] -= position_step->floats[1];
                position.floats[2] -= position_step->floats[2];
                row->unk10.packed = position.packed;

                if (copy_secondary_vector)
                {
                    row->unk20 = source_cell->unk20;
                }

                row->unk30.packed = 0;

                if (index != 0)
                {
                    row->unk30.floats[0] = object->unk28;
                }

                row++;
            }
        }
        else
        {
            s32 count = object->unk10 - 1;
            RowFillVector position;
            position.packed = cell->position().packed;

            for (s32 i = 0; i < count; i++)
            {
                position.floats[0] -= position_step->floats[0];
                position.floats[1] -= position_step->floats[1];
                position.floats[2] -= position_step->floats[2];
                row->unk10.packed = position.packed;

                if (copy_secondary_vector)
                {
                    row->unk20 = cell->unk20;
                }

                row->unk30.packed = 0;

                if (index != 0)
                {
                    row->unk30.floats[0] = object->unk28;
                }

                row++;
            }
        }
    }
    else
    {
        s32 count = object->unk10 - 1;

        for (s32 i = 0; i < count; i++)
        {
            row->unk10 = cell->position();

            if (copy_secondary_vector)
            {
                row->unk20 = cell->unk20;
            }

            row->unk30.packed = 0;
            row++;
        }
    }
}

/**
 * @brief Fill a row of elements from a cell, or from an explicit vector.
 * @param object Owner whose count (minus one) gives the row length.
 * @param cell Cell whose vectors are copied.
 * @param row First element of the row.
 * @param index Unused.
 * @param source Vector copied to each element, or null to use the cell's position.
 */
extern "C" void func_0047ACA0(RowFillOwner* object, RowFillCell* cell, RowFillElement* row, s32 index, const RowFillVector* source)
{
    if (object->secondary_emitter != 0)
    {
        cell->unk3c = object->unk3c;
    }

    bool blend = false;

    if (object->unk4d != 1 && object->unk4d != 3)
    {
        blend = true;
    }

    s32 count = object->unk10 - 1;

    if (source == 0)
    {
        for (s32 i = 0; i < count; i++)
        {
            row->unk10 = cell->position();

            if (blend)
            {
                row->unk20 = cell->unk20;
            }

            row->unk30.packed = 0;
            row++;
        }
    }
    else
    {
        for (s32 i = 0; i < count; i++)
        {
            row->unk10 = *source;

            if (blend)
            {
                row->unk20 = cell->unk20;
            }

            row->unk30.packed = 0;
            row++;
        }
    }
}

/**
 * @brief Store the value at receiver offset 0x28.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047ADA0(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = (LibFloatFieldOwner0046AE20*)object;
    receiver->unk28 = value;
}

/**
 * @brief Store the value at receiver offset 0x30.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047ADB0(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = (LibFloatFieldOwner0046AE20*)object;
    receiver->unk30 = value;
}

/** Return the float member at receiver offset 0x30. */
float func_0047ADC0(void* object)
{
    LibFloatFieldOwner0046AE20* receiver = (LibFloatFieldOwner0046AE20*)object;
    return receiver->unk30;
}

/** Store the byte at receiver offset 0x4D. */
void func_0047ADD0(void* object, u8 value)
{
    ByteSetterOwnertext_0046AE20* receiver = (ByteSetterOwnertext_0046AE20*)object;
    receiver->unk4d = value;
}

/** Return the unsigned byte at receiver offset 0x4D. */
u8 func_0047ADE0(const void* object)
{
    const ByteGetterOwnertext_0046AE20* receiver = (const ByteGetterOwnertext_0046AE20*)object;
    return receiver->unk4d;
}

/**
 * @brief Store the value at receiver offset 0x34.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047ADF0(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = (LibFloatFieldOwner0046AE20*)object;
    receiver->unk34 = value;
}

/** Store the byte at receiver offset 0x56. */
void func_0047AE00(void* object, u8 value)
{
    ByteSetterOwnertext_0046AE20* receiver = (ByteSetterOwnertext_0046AE20*)object;
    receiver->unk56 = value;
}

/** Return the unsigned byte at receiver offset 0x56. */
u8 func_0047AE10(const void* object)
{
    const ByteGetterOwnertext_0046AE20* receiver = (const ByteGetterOwnertext_0046AE20*)object;
    return receiver->unk56;
}

}
