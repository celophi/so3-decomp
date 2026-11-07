#include "include_asm.h"
#include "overlays/lib/particle_grid.h"
#include "overlays/lib/text_0047AE20.h"
#include "ee.h"
#include "vu0.h"
#include "main/resident_data.h"
#include "overlays/lib/emission.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/grid_frame_vu0.h"

extern void* __vt__7LibLink;
extern u8 D_00173A28[];
extern u8 D_00173F48[];
extern u8 D_00177188[];
extern u8 D_00174228[];
typedef struct WordNonzeroOwnertext_0047AE20
{
    u8 unk00[0x14];
    u32 unk14;
} WordNonzeroOwnertext_0047AE20;

typedef struct ByteGetterOwnertext_0047AE20
{
    u8 unk00[0x4D];
    u8 unk4d;
    u8 unk4e[0x8];
    u8 unk56;
} ByteGetterOwnertext_0047AE20;



typedef struct ByteSetterOwnertext_0047AE20
{
    u8 unk00[0x4D];
    u8 unk4d;
    u8 unk4e;
    u8 unk4f;
    u8 unk50[0x4];
    u8 unk54;
    u8 unk55;
    u8 unk56;
} ByteSetterOwnertext_0047AE20;



typedef struct WordSetterOwnertext_0047AE20
{
    u8 unk00[0x48];
    u32 unk48;
    u8 unk4c[0x4];
    u32 unk50;
} WordSetterOwnertext_0047AE20;



typedef struct WordGetterOwnertext_0047AE20
{
    u8 unk00[0xC];
    u32 unk0c;
    u32 unk10;
    u8 unk14[0x8];
    u32 unk1c;
    u8 unk20[0x28];
    u32 unk48;
    u8 unk4c[0x4];
    u32 unk50;
} WordGetterOwnertext_0047AE20;


typedef struct LibFloatFieldOwner0047AE20
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
} LibFloatFieldOwner0047AE20;

/**
 * @brief Store the value at receiver offset 0x44.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047AE20(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk44 = value;
}

/** Return the float member at receiver offset 0x44. */
float func_0047AE30(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    return receiver->unk44;
}

/** Return the float member at receiver offset 0x28. */
float func_0047AE40(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    return receiver->unk28;
}

/** Store the word at receiver offset 0x48. */
void func_0047AE50(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = (WordSetterOwnertext_0047AE20*)object;
    receiver->unk48 = value;
}

/** Return the word at receiver offset 0x48. */
u32 func_0047AE60(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk48;
}

/** Store the byte at receiver offset 0x4F. */
void func_0047AE70(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk4f = value;
}

/** Store the byte at receiver offset 0x4E. */
void func_0047AE80(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk4e = value;
}

/** Store the word at receiver offset 0x50. */
void func_0047AE90(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = (WordSetterOwnertext_0047AE20*)object;
    receiver->unk50 = value;
}

/** Return the word at receiver offset 0x50. */
u32 func_0047AEA0(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk50;
}

/** Store the byte at receiver offset 0x55. */
void func_0047AEB0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk55 = value;
}

/**
 * @brief Store the value at receiver offset 0x3C.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047AEC0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk3c = value;
}

/** Store the byte at receiver offset 0x54. */
void func_0047AED0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk54 = value;
}

/**
 * @brief Store the value at receiver offset 0x40.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047AEE0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk40 = value;
}

typedef struct ByteSourceStateOwnertext_0047AE20 { u8 pad00[0x57]; u8 state57; u8 pad58[0x48]; const u8* sourceA0; u32 valueA4; } ByteSourceStateOwnertext_0047AE20;
typedef struct TwoWordClearArgStateOwnertext_0047AE20 { u8 pad00[0x57]; u8 state57; u8 pad58[0x48]; void* unkA0; void* unkA4; } TwoWordClearArgStateOwnertext_0047AE20;
typedef struct FourQuadwordCopyTargetOwnertext_0047AE20
{
    u8 pad00[0x2C];
    u32 unk2C;
    u8 pad30[0x30];
    unsigned __int128 values60[4];
} FourQuadwordCopyTargetOwnertext_0047AE20;
typedef struct FourQuadwordCopySourceOwnertext_0047AE20
{
    u8 pad00[0x150];
    unsigned __int128 values150[4];
} FourQuadwordCopySourceOwnertext_0047AE20;
typedef struct TwoIndexTableEntryOwnertext_0047AE20
{
    u8 data[0x40];
} TwoIndexTableEntryOwnertext_0047AE20;
typedef struct TwoIndexTableAddressOwnertext_0047AE20
{
    u8 pad00[0x10];
    s32 count;
    u8 pad14[0xC];
    TwoIndexTableEntryOwnertext_0047AE20* entries;
} TwoIndexTableAddressOwnertext_0047AE20;
typedef struct SingleIndexTableAddressOwnertext_0047AE20
{
    u8 pad00[0x14];
    u8* base14;
} SingleIndexTableAddressOwnertext_0047AE20;

void func_0047AEF0(void* object, const u8* source, u32 value)
{
    ByteSourceStateOwnertext_0047AE20* receiver = (ByteSourceStateOwnertext_0047AE20*)object;
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

void func_0047AF30(void* object, s32 enabled)
{
    TwoWordClearArgStateOwnertext_0047AE20* receiver = (TwoWordClearArgStateOwnertext_0047AE20*)object;
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
void func_0047AF60(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk38 = value;
}

void func_0047AF70(void* object)
{
}

s32 func_0047AF80(void* object)
{
    return 0;
}

void func_0047AF90(void* object)
{
}

s32 func_0047AFA0(void* object)
{
    return 0;
}

void func_0047AFB0(void* object, const void* source)
{
    FourQuadwordCopyTargetOwnertext_0047AE20* receiver = (FourQuadwordCopyTargetOwnertext_0047AE20*)object;
    const FourQuadwordCopySourceOwnertext_0047AE20* values = (const FourQuadwordCopySourceOwnertext_0047AE20*)source;
    receiver->unk2C = 0;
    receiver->values60[0] = values->values150[0];
    receiver->values60[1] = values->values150[1];
    receiver->values60[2] = values->values150[2];
    receiver->values60[3] = values->values150[3];
}

void func_0047AFE0(void* object)
{
}

s32 func_0047AFF0(void* object)
{
    return 1;
}

typedef struct MappedEntry0047B000
{
    u8 unk00[0xF0];
} MappedEntry0047B000;

typedef struct MappedOwner0047B000
{
    u8 unk00[0x14];
    MappedEntry0047B000* entries;
} MappedOwner0047B000;

/**
 * @brief Return the mapped entry at offset 0xF0 of an indexed 0xF0-byte record.
 * @param object Owner whose record table is at offset 0x14.
 * @param index Record index.
 * @return The mapped entry, or null when the record address is null.
 */
void* func_0047B000(const void* object, s32 index)
{
    const MappedOwner0047B000* owner = (const MappedOwner0047B000*)object;
    MappedEntry0047B000* item = &owner->entries[index];
    void* result = item;
    if (item != 0)
    {
        result = (u8*)item + 0xF0;
    }
    return result;
}

/** One 16-byte value also accessed as four floats. */
typedef union RowFillVector
{
    float floats[4];
    unsigned __int128 packed;
} RowFillVector;

/** Partial view of a grid's emission settings used when filling secondary rows. */
struct RowFillOwner
{
    u8 unk00[0x10];
    s32 unk10;
    u8 unk14[0x14];
    float unk28;
    u8 unk2c[0x10];
    float unk3c;
    u8 unk40[0xD];
    u8 unk4d;
    u8 unk4e[2];

    /** Linked secondary emitter, or null. */
    LibClass173990* secondary_emitter;
};

/** Partial view of a grid cell: its position and secondary vector. */
struct RowFillCell
{
    /**
     * @brief Get the cell position.
     * @return The position vector.
     */
    const RowFillVector& position() const
    {
        return unk10;
    }

    u8 unk00[0x10];
    RowFillVector unk10;
    RowFillVector unk20;
    u8 unk30[0xC];
    float unk3c;
};

/** Partial view of a 64-byte secondary row element. */
struct RowFillElement
{
    u8 unk00[0x10];
    RowFillVector unk10;
    RowFillVector unk20;
    RowFillVector unk30;
};

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
extern "C" void func_0047B030(RowFillOwner* object, RowFillCell* cell, RowFillElement* row, s32 index, const RowFillVector* position_step, const RowFillVector* angle_pair,
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
            lib_compute_sine_cosine_pair(&first_trig, angles.floats[0]);
            lib_compute_sine_cosine_pair(&second_trig, angles.floats[1]);
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
                lib_compute_sine_cosine_pair(&first_trig, angles.floats[0]);
                lib_compute_sine_cosine_pair(&second_trig, angles.floats[1]);
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
extern "C" void func_0047B440(RowFillOwner* object, RowFillCell* cell, RowFillElement* row, s32 index, const RowFillVector* source)
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
void func_0047B540(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk28 = value;
}

/**
 * @brief Store the value at receiver offset 0x30.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047B550(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk30 = value;
}

/** Return the float member at receiver offset 0x30. */
float func_0047B560(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    return receiver->unk30;
}

/** Store the byte at receiver offset 0x4D. */
void func_0047B570(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk4d = value;
}

/** Return the unsigned byte at receiver offset 0x4D. */
u8 func_0047B580(const void* object)
{
    const ByteGetterOwnertext_0047AE20* receiver = (const ByteGetterOwnertext_0047AE20*)object;
    return receiver->unk4d;
}

/**
 * @brief Store the value at receiver offset 0x34.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047B590(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk34 = value;
}

/** Store the byte at receiver offset 0x56. */
void func_0047B5A0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk56 = value;
}

/** Return the unsigned byte at receiver offset 0x56. */
u8 func_0047B5B0(const void* object)
{
    const ByteGetterOwnertext_0047AE20* receiver = (const ByteGetterOwnertext_0047AE20*)object;
    return receiver->unk56;
}

/**
 * @brief Store the value at receiver offset 0x44.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047B5C0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk44 = value;
}

/** Return the float member at receiver offset 0x44. */
float func_0047B5D0(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    return receiver->unk44;
}

/** Return the float member at receiver offset 0x28. */
float func_0047B5E0(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    return receiver->unk28;
}

/** Store the word at receiver offset 0x48. */
void func_0047B5F0(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = (WordSetterOwnertext_0047AE20*)object;
    receiver->unk48 = value;
}

/** Return the word at receiver offset 0x48. */
u32 func_0047B600(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk48;
}

/** Store the byte at receiver offset 0x4F. */
void func_0047B610(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk4f = value;
}

/** Store the byte at receiver offset 0x4E. */
void func_0047B620(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk4e = value;
}

/** Store the word at receiver offset 0x50. */
void func_0047B630(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = (WordSetterOwnertext_0047AE20*)object;
    receiver->unk50 = value;
}

/** Return the word at receiver offset 0x50. */
u32 func_0047B640(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk50;
}

/** Store the byte at receiver offset 0x55. */
void func_0047B650(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk55 = value;
}

/**
 * @brief Store the value at receiver offset 0x3C.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047B660(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk3c = value;
}

/** Store the byte at receiver offset 0x54. */
void func_0047B670(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk54 = value;
}

/**
 * @brief Store the value at receiver offset 0x40.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047B680(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk40 = value;
}

void func_0047B690(void* object, const u8* source, u32 value)
{
    ByteSourceStateOwnertext_0047AE20* receiver = (ByteSourceStateOwnertext_0047AE20*)object;
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

void func_0047B6D0(void* object, s32 enabled)
{
    TwoWordClearArgStateOwnertext_0047AE20* receiver = (TwoWordClearArgStateOwnertext_0047AE20*)object;
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
void func_0047B700(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk38 = value;
}

void func_0047B710(void* object)
{
}

s32 func_0047B720(void* object)
{
    return 0;
}

void func_0047B730(void* object)
{
}

s32 func_0047B740(void* object)
{
    return 0;
}

void func_0047B750(void* object, const void* source)
{
    FourQuadwordCopyTargetOwnertext_0047AE20* receiver = (FourQuadwordCopyTargetOwnertext_0047AE20*)object;
    const FourQuadwordCopySourceOwnertext_0047AE20* values = (const FourQuadwordCopySourceOwnertext_0047AE20*)source;
    receiver->unk2C = 0;
    receiver->values60[0] = values->values150[0];
    receiver->values60[1] = values->values150[1];
    receiver->values60[2] = values->values150[2];
    receiver->values60[3] = values->values150[3];
}

void func_0047B780(void* object)
{
}

s32 func_0047B790(void* object)
{
    return 1;
}

typedef struct MappedEntry0047B7A0
{
    u8 unk00[0xB0];
} MappedEntry0047B7A0;

typedef struct MappedOwner0047B7A0
{
    u8 unk00[0x14];
    MappedEntry0047B7A0* entries;
} MappedOwner0047B7A0;

/**
 * @brief Return the mapped entry at offset 0x80 of an indexed 0xB0-byte record.
 * @param object Owner whose record table is at offset 0x14.
 * @param index Record index.
 * @return The mapped entry, or null when the record address is null.
 */
void* func_0047B7A0(const void* object, s32 index)
{
    const MappedOwner0047B7A0* owner = (const MappedOwner0047B7A0*)object;
    MappedEntry0047B7A0* item = &owner->entries[index];
    void* result = item;
    if (item != 0)
    {
        result = (u8*)item + 0x80;
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
extern "C" void func_0047B7D0(RowFillOwner* object, RowFillCell* cell, RowFillElement* row, s32 index, const RowFillVector* position_step, const RowFillVector* angle_pair,
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
            lib_compute_sine_cosine_pair(&first_trig, angles.floats[0]);
            lib_compute_sine_cosine_pair(&second_trig, angles.floats[1]);
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
                lib_compute_sine_cosine_pair(&first_trig, angles.floats[0]);
                lib_compute_sine_cosine_pair(&second_trig, angles.floats[1]);
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
extern "C" void func_0047BBE0(RowFillOwner* object, RowFillCell* cell, RowFillElement* row, s32 index, const RowFillVector* source)
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
void func_0047BCE0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk28 = value;
}

/**
 * @brief Store the value at receiver offset 0x30.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047BCF0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk30 = value;
}

/** Return the float member at receiver offset 0x30. */
float func_0047BD00(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    return receiver->unk30;
}

/** Store the byte at receiver offset 0x4D. */
void func_0047BD10(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk4d = value;
}

/** Return the unsigned byte at receiver offset 0x4D. */
u8 func_0047BD20(const void* object)
{
    const ByteGetterOwnertext_0047AE20* receiver = (const ByteGetterOwnertext_0047AE20*)object;
    return receiver->unk4d;
}

/**
 * @brief Store the value at receiver offset 0x34.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047BD30(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk34 = value;
}

/** Store the byte at receiver offset 0x56. */
void func_0047BD40(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk56 = value;
}

/** Return the unsigned byte at receiver offset 0x56. */
u8 func_0047BD50(const void* object)
{
    const ByteGetterOwnertext_0047AE20* receiver = (const ByteGetterOwnertext_0047AE20*)object;
    return receiver->unk56;
}

/**
 * @brief Store the value at receiver offset 0x44.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047BD60(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk44 = value;
}

/** Return the float member at receiver offset 0x44. */
float func_0047BD70(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    return receiver->unk44;
}

/** Return the float member at receiver offset 0x28. */
float func_0047BD80(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    return receiver->unk28;
}

/** Store the word at receiver offset 0x48. */
void func_0047BD90(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = (WordSetterOwnertext_0047AE20*)object;
    receiver->unk48 = value;
}

/** Return the word at receiver offset 0x48. */
u32 func_0047BDA0(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk48;
}

/** Store the byte at receiver offset 0x4F. */
void func_0047BDB0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk4f = value;
}

/** Store the byte at receiver offset 0x4E. */
void func_0047BDC0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk4e = value;
}

/** Store the word at receiver offset 0x50. */
void func_0047BDD0(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = (WordSetterOwnertext_0047AE20*)object;
    receiver->unk50 = value;
}

/** Return the word at receiver offset 0x50. */
u32 func_0047BDE0(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk50;
}

/** Store the byte at receiver offset 0x55. */
void func_0047BDF0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk55 = value;
}

/**
 * @brief Store the value at receiver offset 0x3C.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047BE00(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk3c = value;
}

/** Store the byte at receiver offset 0x54. */
void func_0047BE10(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk54 = value;
}

/**
 * @brief Store the value at receiver offset 0x40.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047BE20(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk40 = value;
}

void func_0047BE30(void* object, const u8* source, u32 value)
{
    ByteSourceStateOwnertext_0047AE20* receiver = (ByteSourceStateOwnertext_0047AE20*)object;
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

void func_0047BE70(void* object, s32 enabled)
{
    TwoWordClearArgStateOwnertext_0047AE20* receiver = (TwoWordClearArgStateOwnertext_0047AE20*)object;
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
void func_0047BEA0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk38 = value;
}

void func_0047BEB0(void* object)
{
}

s32 func_0047BEC0(void* object)
{
    return 0;
}

void func_0047BED0(void* object)
{
}

s32 func_0047BEE0(void* object)
{
    return 0;
}

void func_0047BEF0(void* object, const void* source)
{
    FourQuadwordCopyTargetOwnertext_0047AE20* receiver = (FourQuadwordCopyTargetOwnertext_0047AE20*)object;
    const FourQuadwordCopySourceOwnertext_0047AE20* values = (const FourQuadwordCopySourceOwnertext_0047AE20*)source;
    receiver->unk2C = 0;
    receiver->values60[0] = values->values150[0];
    receiver->values60[1] = values->values150[1];
    receiver->values60[2] = values->values150[2];
    receiver->values60[3] = values->values150[3];
}

void func_0047BF20(void* object)
{
}

s32 func_0047BF30(void* object)
{
    return 1;
}

typedef struct MappedEntry0047BF40
{
    u8 unk00[0x80];
} MappedEntry0047BF40;

typedef struct MappedOwner0047BF40
{
    u8 unk00[0x14];
    MappedEntry0047BF40* entries;
} MappedOwner0047BF40;

/**
 * @brief Return the mapped entry at offset 0x80 of an indexed 0x80-byte record.
 * @param object Owner whose record table is at offset 0x14.
 * @param index Record index.
 * @return The mapped entry, or null when the record address is null.
 */
void* func_0047BF40(const void* object, s32 index)
{
    const MappedOwner0047BF40* owner = (const MappedOwner0047BF40*)object;
    MappedEntry0047BF40* item = &owner->entries[index];
    void* result = item;
    if (item != 0)
    {
        result = (u8*)item + 0x80;
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
extern "C" void func_0047BF60(RowFillOwner* object, RowFillCell* cell, RowFillElement* row, s32 index, const RowFillVector* position_step, const RowFillVector* angle_pair,
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
            lib_compute_sine_cosine_pair(&first_trig, angles.floats[0]);
            lib_compute_sine_cosine_pair(&second_trig, angles.floats[1]);
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
                lib_compute_sine_cosine_pair(&first_trig, angles.floats[0]);
                lib_compute_sine_cosine_pair(&second_trig, angles.floats[1]);
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
extern "C" void func_0047C370(RowFillOwner* object, RowFillCell* cell, RowFillElement* row, s32 index, const RowFillVector* source)
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
void func_0047C470(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk28 = value;
}

/**
 * @brief Store the value at receiver offset 0x30.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047C480(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk30 = value;
}

/** Return the float member at receiver offset 0x30. */
float func_0047C490(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    return receiver->unk30;
}

/** Store the byte at receiver offset 0x4D. */
void func_0047C4A0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk4d = value;
}

/** Return the unsigned byte at receiver offset 0x4D. */
u8 func_0047C4B0(const void* object)
{
    const ByteGetterOwnertext_0047AE20* receiver = (const ByteGetterOwnertext_0047AE20*)object;
    return receiver->unk4d;
}

/**
 * @brief Store the value at receiver offset 0x34.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047C4C0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk34 = value;
}

/** Store the byte at receiver offset 0x56. */
void func_0047C4D0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk56 = value;
}

/** Return the unsigned byte at receiver offset 0x56. */
u8 func_0047C4E0(const void* object)
{
    const ByteGetterOwnertext_0047AE20* receiver = (const ByteGetterOwnertext_0047AE20*)object;
    return receiver->unk56;
}

/**
 * @brief Store the value at receiver offset 0x44.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047C4F0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk44 = value;
}

/** Return the float member at receiver offset 0x44. */
float func_0047C500(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    return receiver->unk44;
}

/** Return the float member at receiver offset 0x28. */
float func_0047C510(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    return receiver->unk28;
}

/** Store the word at receiver offset 0x48. */
void func_0047C520(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = (WordSetterOwnertext_0047AE20*)object;
    receiver->unk48 = value;
}

/** Return the word at receiver offset 0x48. */
u32 func_0047C530(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk48;
}

/** Store the byte at receiver offset 0x4F. */
void func_0047C540(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk4f = value;
}

/** Store the byte at receiver offset 0x4E. */
void func_0047C550(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk4e = value;
}

/** Store the word at receiver offset 0x50. */
void func_0047C560(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = (WordSetterOwnertext_0047AE20*)object;
    receiver->unk50 = value;
}

/** Return the word at receiver offset 0x50. */
u32 func_0047C570(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk50;
}

/** Store the byte at receiver offset 0x55. */
void func_0047C580(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk55 = value;
}

/**
 * @brief Store the value at receiver offset 0x3C.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047C590(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk3c = value;
}

/** Store the byte at receiver offset 0x54. */
void func_0047C5A0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk54 = value;
}

/**
 * @brief Store the value at receiver offset 0x40.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047C5B0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk40 = value;
}

void func_0047C5C0(void* object, const u8* source, u32 value)
{
    ByteSourceStateOwnertext_0047AE20* receiver = (ByteSourceStateOwnertext_0047AE20*)object;
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

void func_0047C600(void* object, s32 enabled)
{
    TwoWordClearArgStateOwnertext_0047AE20* receiver = (TwoWordClearArgStateOwnertext_0047AE20*)object;
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
void func_0047C630(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk38 = value;
}

void func_0047C640(void* object)
{
}

s32 func_0047C650(void* object)
{
    return 0;
}

void func_0047C660(void* object)
{
}

s32 func_0047C670(void* object)
{
    return 0;
}

void func_0047C680(void* object, const void* source)
{
    FourQuadwordCopyTargetOwnertext_0047AE20* receiver = (FourQuadwordCopyTargetOwnertext_0047AE20*)object;
    const FourQuadwordCopySourceOwnertext_0047AE20* values = (const FourQuadwordCopySourceOwnertext_0047AE20*)source;
    receiver->unk2C = 0;
    receiver->values60[0] = values->values150[0];
    receiver->values60[1] = values->values150[1];
    receiver->values60[2] = values->values150[2];
    receiver->values60[3] = values->values150[3];
}

void func_0047C6B0(void* object)
{
}

s32 func_0047C6C0(void* object)
{
    return 1;
}

typedef struct MappedEntry0047C6D0 { u8 unk00[0x90]; } MappedEntry0047C6D0;
typedef struct MappedOwner0047C6D0 { u8 unk00[0x14]; MappedEntry0047C6D0* entries; } MappedOwner0047C6D0;

void* func_0047C6D0(const void* object, s32 index)
{
    const MappedOwner0047C6D0* owner = (const MappedOwner0047C6D0*)object;
    MappedEntry0047C6D0* item = &owner->entries[index];
    void* result = item;
    if (item != 0)
    {
        result = (u8*)item + 0x60;
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
extern "C" void func_0047C700(RowFillOwner* object, RowFillCell* cell, RowFillElement* row, s32 index, const RowFillVector* position_step, const RowFillVector* angle_pair,
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
            lib_compute_sine_cosine_pair(&first_trig, angles.floats[0]);
            lib_compute_sine_cosine_pair(&second_trig, angles.floats[1]);
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
                lib_compute_sine_cosine_pair(&first_trig, angles.floats[0]);
                lib_compute_sine_cosine_pair(&second_trig, angles.floats[1]);
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
extern "C" void func_0047CB10(RowFillOwner* object, RowFillCell* cell, RowFillElement* row, s32 index, const RowFillVector* source)
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
void func_0047CC10(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk28 = value;
}

/**
 * @brief Store the value at receiver offset 0x30.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047CC20(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk30 = value;
}

/** Return the float member at receiver offset 0x30. */
float func_0047CC30(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    return receiver->unk30;
}

/** Store the byte at receiver offset 0x4D. */
void func_0047CC40(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk4d = value;
}

/** Return the unsigned byte at receiver offset 0x4D. */
u8 func_0047CC50(const void* object)
{
    const ByteGetterOwnertext_0047AE20* receiver = (const ByteGetterOwnertext_0047AE20*)object;
    return receiver->unk4d;
}

/**
 * @brief Store the value at receiver offset 0x34.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047CC60(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk34 = value;
}

/** Store the byte at receiver offset 0x56. */
void func_0047CC70(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk56 = value;
}

/** Return the unsigned byte at receiver offset 0x56. */
u8 func_0047CC80(const void* object)
{
    const ByteGetterOwnertext_0047AE20* receiver = (const ByteGetterOwnertext_0047AE20*)object;
    return receiver->unk56;
}

/**
 * @brief Store the value at receiver offset 0x44.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047CC90(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk44 = value;
}

/** Return the float member at receiver offset 0x44. */
float func_0047CCA0(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    return receiver->unk44;
}

/** Return the float member at receiver offset 0x28. */
float func_0047CCB0(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    return receiver->unk28;
}

/** Store the word at receiver offset 0x48. */
void func_0047CCC0(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = (WordSetterOwnertext_0047AE20*)object;
    receiver->unk48 = value;
}

/** Return the word at receiver offset 0x48. */
u32 func_0047CCD0(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk48;
}

/** Store the byte at receiver offset 0x4F. */
void func_0047CCE0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk4f = value;
}

/** Store the byte at receiver offset 0x4E. */
void func_0047CCF0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk4e = value;
}

/** Store the word at receiver offset 0x50. */
void func_0047CD00(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = (WordSetterOwnertext_0047AE20*)object;
    receiver->unk50 = value;
}

/** Return the word at receiver offset 0x50. */
u32 func_0047CD10(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk50;
}

/** Store the byte at receiver offset 0x55. */
void func_0047CD20(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk55 = value;
}

/**
 * @brief Store the value at receiver offset 0x3C.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047CD30(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk3c = value;
}

/** Store the byte at receiver offset 0x54. */
void func_0047CD40(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk54 = value;
}

/**
 * @brief Store the value at receiver offset 0x40.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047CD50(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk40 = value;
}

void func_0047CD60(void* object, const u8* source, u32 value)
{
    ByteSourceStateOwnertext_0047AE20* receiver = (ByteSourceStateOwnertext_0047AE20*)object;
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

void func_0047CDA0(void* object, s32 enabled)
{
    TwoWordClearArgStateOwnertext_0047AE20* receiver = (TwoWordClearArgStateOwnertext_0047AE20*)object;
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
void func_0047CDD0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk38 = value;
}

void func_0047CDE0(void* object)
{
}

s32 func_0047CDF0(void* object)
{
    return 0;
}

void func_0047CE00(void* object)
{
}

s32 func_0047CE10(void* object)
{
    return 0;
}

void func_0047CE20(void* object, const void* source)
{
    FourQuadwordCopyTargetOwnertext_0047AE20* receiver = (FourQuadwordCopyTargetOwnertext_0047AE20*)object;
    const FourQuadwordCopySourceOwnertext_0047AE20* values = (const FourQuadwordCopySourceOwnertext_0047AE20*)source;
    receiver->unk2C = 0;
    receiver->values60[0] = values->values150[0];
    receiver->values60[1] = values->values150[1];
    receiver->values60[2] = values->values150[2];
    receiver->values60[3] = values->values150[3];
}

void func_0047CE50(void* object)
{
}

s32 func_0047CE60(void* object)
{
    return 1;
}

typedef struct MappedEntry0047CE70 { u8 unk00[0x60]; } MappedEntry0047CE70;
typedef struct MappedOwner0047CE70 { u8 unk00[0x14]; MappedEntry0047CE70* entries; } MappedOwner0047CE70;

void* func_0047CE70(const void* object, s32 index)
{
    const MappedOwner0047CE70* owner = (const MappedOwner0047CE70*)object;
    MappedEntry0047CE70* item = &owner->entries[index];
    void* result = item;
    if (item != 0)
    {
        result = (u8*)item + 0x60;
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
extern "C" void func_0047CEA0(RowFillOwner* object, RowFillCell* cell, RowFillElement* row, s32 index, const RowFillVector* position_step, const RowFillVector* angle_pair,
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
            lib_compute_sine_cosine_pair(&first_trig, angles.floats[0]);
            lib_compute_sine_cosine_pair(&second_trig, angles.floats[1]);
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
                lib_compute_sine_cosine_pair(&first_trig, angles.floats[0]);
                lib_compute_sine_cosine_pair(&second_trig, angles.floats[1]);
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
extern "C" void func_0047D2B0(RowFillOwner* object, RowFillCell* cell, RowFillElement* row, s32 index, const RowFillVector* source)
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
void func_0047D3B0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk28 = value;
}

/**
 * @brief Store the value at receiver offset 0x30.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047D3C0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk30 = value;
}

/** Return the float member at receiver offset 0x30. */
float func_0047D3D0(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    return receiver->unk30;
}

/** Store the byte at receiver offset 0x4D. */
void func_0047D3E0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk4d = value;
}

/** Return the unsigned byte at receiver offset 0x4D. */
u8 func_0047D3F0(const void* object)
{
    const ByteGetterOwnertext_0047AE20* receiver = (const ByteGetterOwnertext_0047AE20*)object;
    return receiver->unk4d;
}

/**
 * @brief Store the value at receiver offset 0x34.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047D400(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk34 = value;
}

/** Store the byte at receiver offset 0x56. */
void func_0047D410(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk56 = value;
}

/** Return the unsigned byte at receiver offset 0x56. */
u8 func_0047D420(const void* object)
{
    const ByteGetterOwnertext_0047AE20* receiver = (const ByteGetterOwnertext_0047AE20*)object;
    return receiver->unk56;
}

/**
 * @brief Store the value at receiver offset 0x44.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047D430(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk44 = value;
}

/** Return the float member at receiver offset 0x44. */
float func_0047D440(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    return receiver->unk44;
}

/** Return the float member at receiver offset 0x28. */
float func_0047D450(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    return receiver->unk28;
}

/** Store the word at receiver offset 0x48. */
void func_0047D460(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = (WordSetterOwnertext_0047AE20*)object;
    receiver->unk48 = value;
}

/** Return the word at receiver offset 0x48. */
u32 func_0047D470(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk48;
}

/** Store the byte at receiver offset 0x4F. */
void func_0047D480(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk4f = value;
}

/** Store the byte at receiver offset 0x4E. */
void func_0047D490(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk4e = value;
}

/** Store the word at receiver offset 0x50. */
void func_0047D4A0(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = (WordSetterOwnertext_0047AE20*)object;
    receiver->unk50 = value;
}

/** Return the word at receiver offset 0x50. */
u32 func_0047D4B0(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk50;
}

/** Store the byte at receiver offset 0x55. */
void func_0047D4C0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk55 = value;
}

/**
 * @brief Store the value at receiver offset 0x3C.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047D4D0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk3c = value;
}

/** Store the byte at receiver offset 0x54. */
void func_0047D4E0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk54 = value;
}

/**
 * @brief Store the value at receiver offset 0x40.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047D4F0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk40 = value;
}

void func_0047D500(void* object, const u8* source, u32 value)
{
    ByteSourceStateOwnertext_0047AE20* receiver = (ByteSourceStateOwnertext_0047AE20*)object;
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

void func_0047D540(void* object, s32 enabled)
{
    TwoWordClearArgStateOwnertext_0047AE20* receiver = (TwoWordClearArgStateOwnertext_0047AE20*)object;
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
void func_0047D570(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk38 = value;
}

void func_0047D580(void* object)
{
}

s32 func_0047D590(void* object)
{
    return 0;
}

void func_0047D5A0(void* object)
{
}

s32 func_0047D5B0(void* object)
{
    return 0;
}

void func_0047D5C0(void* object, const void* source)
{
    FourQuadwordCopyTargetOwnertext_0047AE20* receiver = (FourQuadwordCopyTargetOwnertext_0047AE20*)object;
    const FourQuadwordCopySourceOwnertext_0047AE20* values = (const FourQuadwordCopySourceOwnertext_0047AE20*)source;
    receiver->unk2C = 0;
    receiver->values60[0] = values->values150[0];
    receiver->values60[1] = values->values150[1];
    receiver->values60[2] = values->values150[2];
    receiver->values60[3] = values->values150[3];
}

void func_0047D5F0(void* object)
{
}

s32 func_0047D600(void* object)
{
    return 1;
}

typedef struct MappedEntry0047D610 { u8 unk00[0x60]; } MappedEntry0047D610;
typedef struct MappedOwner0047D610 { u8 unk00[0x14]; MappedEntry0047D610* entries; } MappedOwner0047D610;

void* func_0047D610(const void* object, s32 index)
{
    const MappedOwner0047D610* owner = (const MappedOwner0047D610*)object;
    MappedEntry0047D610* item = &owner->entries[index];
    void* result = item;
    if (item != 0)
    {
        result = (u8*)item + 0x30;
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
extern "C" void func_0047D640(RowFillOwner* object, RowFillCell* cell, RowFillElement* row, s32 index, const RowFillVector* position_step, const RowFillVector* angle_pair,
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
            lib_compute_sine_cosine_pair(&first_trig, angles.floats[0]);
            lib_compute_sine_cosine_pair(&second_trig, angles.floats[1]);
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
                lib_compute_sine_cosine_pair(&first_trig, angles.floats[0]);
                lib_compute_sine_cosine_pair(&second_trig, angles.floats[1]);
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
extern "C" void func_0047DA50(RowFillOwner* object, RowFillCell* cell, RowFillElement* row, s32 index, const RowFillVector* source)
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
void func_0047DB50(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk28 = value;
}

/**
 * @brief Store the value at receiver offset 0x30.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047DB60(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk30 = value;
}

/** Return the float member at receiver offset 0x30. */
float func_0047DB70(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    return receiver->unk30;
}

/** Store the byte at receiver offset 0x4D. */
void func_0047DB80(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk4d = value;
}

/** Return the unsigned byte at receiver offset 0x4D. */
u8 func_0047DB90(const void* object)
{
    const ByteGetterOwnertext_0047AE20* receiver = (const ByteGetterOwnertext_0047AE20*)object;
    return receiver->unk4d;
}

/**
 * @brief Store the value at receiver offset 0x34.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047DBA0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk34 = value;
}

/** Store the byte at receiver offset 0x56. */
void func_0047DBB0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk56 = value;
}

/** Return the unsigned byte at receiver offset 0x56. */
u8 func_0047DBC0(const void* object)
{
    const ByteGetterOwnertext_0047AE20* receiver = (const ByteGetterOwnertext_0047AE20*)object;
    return receiver->unk56;
}

/**
 * @brief Store the value at receiver offset 0x44.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047DBD0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk44 = value;
}

/** Return the float member at receiver offset 0x44. */
float func_0047DBE0(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    return receiver->unk44;
}

/** Return the float member at receiver offset 0x28. */
float func_0047DBF0(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    return receiver->unk28;
}

/** Store the word at receiver offset 0x48. */
void func_0047DC00(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = (WordSetterOwnertext_0047AE20*)object;
    receiver->unk48 = value;
}

/** Return the word at receiver offset 0x48. */
u32 func_0047DC10(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk48;
}

/** Store the byte at receiver offset 0x4F. */
void func_0047DC20(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk4f = value;
}

/** Store the byte at receiver offset 0x4E. */
void func_0047DC30(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk4e = value;
}

/** Store the word at receiver offset 0x50. */
void func_0047DC40(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = (WordSetterOwnertext_0047AE20*)object;
    receiver->unk50 = value;
}

/** Return the word at receiver offset 0x50. */
u32 func_0047DC50(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk50;
}

/** Store the byte at receiver offset 0x55. */
void func_0047DC60(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk55 = value;
}

/**
 * @brief Store the value at receiver offset 0x3C.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047DC70(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk3c = value;
}

/** Store the byte at receiver offset 0x54. */
void func_0047DC80(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = (ByteSetterOwnertext_0047AE20*)object;
    receiver->unk54 = value;
}

/**
 * @brief Store the value at receiver offset 0x40.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047DC90(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk40 = value;
}

void func_0047DCA0(void* object, const u8* source, u32 value)
{
    ByteSourceStateOwnertext_0047AE20* receiver = (ByteSourceStateOwnertext_0047AE20*)object;
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

void func_0047DCE0(void* object, s32 enabled)
{
    TwoWordClearArgStateOwnertext_0047AE20* receiver = (TwoWordClearArgStateOwnertext_0047AE20*)object;
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
void func_0047DD10(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = (LibFloatFieldOwner0047AE20*)object;
    receiver->unk38 = value;
}

void func_0047DD20(void* object)
{
}

s32 func_0047DD30(void* object)
{
    return 0;
}

void func_0047DD40(void* object)
{
}

s32 func_0047DD50(void* object)
{
    return 0;
}

void* func_0047DD60(void* object, s32 index)
{
    SingleIndexTableAddressOwnertext_0047AE20* receiver = (SingleIndexTableAddressOwnertext_0047AE20*)object;
    return receiver->base14 + index * 320;
}

void* func_0047DD80(void* object, s32 row, s32 column)
{
    TwoIndexTableAddressOwnertext_0047AE20* receiver = (TwoIndexTableAddressOwnertext_0047AE20*)object;
    return &receiver->entries[row * (receiver->count - 1) + column];
}

/** Return the word at receiver offset 0x1C. */
u32 func_0047DDA0(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk1c;
}

/** Return the word at receiver offset 0xC. */
u32 func_0047DDB0(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk0c;
}

/** Return the word at receiver offset 0x10. */
u32 func_0047DDC0(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk10;
}

s32 func_0047DDD0(void* object)
{
    return 31;
}

s32 func_0047DDE0(void* receiver)
{
    WordNonzeroOwnertext_0047AE20* object = (WordNonzeroOwnertext_0047AE20*)receiver;
    return object->unk14 != 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047DDF0);

void* func_0047DE50(void* object, s32 index)
{
    SingleIndexTableAddressOwnertext_0047AE20* receiver = (SingleIndexTableAddressOwnertext_0047AE20*)object;
    return receiver->base14 + index * 288;
}

void* func_0047DE70(void* object, s32 row, s32 column)
{
    TwoIndexTableAddressOwnertext_0047AE20* receiver = (TwoIndexTableAddressOwnertext_0047AE20*)object;
    return &receiver->entries[row * (receiver->count - 1) + column];
}

/** Return the word at receiver offset 0x1C. */
u32 func_0047DE90(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk1c;
}

/** Return the word at receiver offset 0xC. */
u32 func_0047DEA0(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk0c;
}

/** Return the word at receiver offset 0x10. */
u32 func_0047DEB0(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk10;
}

s32 func_0047DEC0(void* object)
{
    return 47;
}

s32 func_0047DED0(void* receiver)
{
    WordNonzeroOwnertext_0047AE20* object = (WordNonzeroOwnertext_0047AE20*)receiver;
    return object->unk14 != 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047DEE0);

typedef struct MappedEntry0047DF40
{
    u8 unk00[0xF0];
} MappedEntry0047DF40;

typedef struct MappedOwner0047DF40
{
    u8 unk00[0x14];
    MappedEntry0047DF40* entries;
} MappedOwner0047DF40;

/**
 * @brief Return the address of an indexed 0xF0-byte record.
 * @param object Owner whose record table is at offset 0x14.
 * @param index Record index.
 * @return The record address.
 */
void* func_0047DF40(const void* object, s32 index)
{
    const MappedOwner0047DF40* owner = (const MappedOwner0047DF40*)object;
    return &owner->entries[index];
}

void* func_0047DF60(void* object, s32 row, s32 column)
{
    TwoIndexTableAddressOwnertext_0047AE20* receiver = (TwoIndexTableAddressOwnertext_0047AE20*)object;
    return &receiver->entries[row * (receiver->count - 1) + column];
}

/** Return the word at receiver offset 0x1C. */
u32 func_0047DF80(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk1c;
}

/** Return the word at receiver offset 0xC. */
u32 func_0047DF90(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk0c;
}

/** Return the word at receiver offset 0x10. */
u32 func_0047DFA0(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk10;
}

s32 func_0047DFB0(void* object)
{
    return 15;
}

s32 func_0047DFC0(void* receiver)
{
    WordNonzeroOwnertext_0047AE20* object = (WordNonzeroOwnertext_0047AE20*)receiver;
    return object->unk14 != 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047DFD0);

typedef struct MappedEntry0047E030
{
    u8 unk00[0xB0];
} MappedEntry0047E030;

typedef struct MappedOwner0047E030
{
    u8 unk00[0x14];
    MappedEntry0047E030* entries;
} MappedOwner0047E030;

/**
 * @brief Return the address of an indexed 0xB0-byte record.
 * @param object Owner whose record table is at offset 0x14.
 * @param index Record index.
 * @return The record address.
 */
void* func_0047E030(const void* object, s32 index)
{
    const MappedOwner0047E030* owner = (const MappedOwner0047E030*)object;
    return &owner->entries[index];
}

void* func_0047E050(void* object, s32 row, s32 column)
{
    TwoIndexTableAddressOwnertext_0047AE20* receiver = (TwoIndexTableAddressOwnertext_0047AE20*)object;
    return &receiver->entries[row * (receiver->count - 1) + column];
}

/** Return the word at receiver offset 0x1C. */
u32 func_0047E070(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk1c;
}

/** Return the word at receiver offset 0xC. */
u32 func_0047E080(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk0c;
}

/** Return the word at receiver offset 0x10. */
u32 func_0047E090(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk10;
}

s32 func_0047E0A0(void* object)
{
    return 39;
}

s32 func_0047E0B0(void* receiver)
{
    WordNonzeroOwnertext_0047AE20* object = (WordNonzeroOwnertext_0047AE20*)receiver;
    return object->unk14 != 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E0C0);

typedef struct MappedEntry0047E120
{
    u8 unk00[0x80];
} MappedEntry0047E120;

typedef struct MappedOwner0047E120
{
    u8 unk00[0x14];
    MappedEntry0047E120* entries;
} MappedOwner0047E120;

/**
 * @brief Return the address of an indexed 0x80-byte record.
 * @param object Owner whose record table is at offset 0x14.
 * @param index Record index.
 * @return The record address.
 */
void* func_0047E120(const void* object, s32 index)
{
    const MappedOwner0047E120* owner = (const MappedOwner0047E120*)object;
    return &owner->entries[index];
}

void* func_0047E130(void* object, s32 row, s32 column)
{
    TwoIndexTableAddressOwnertext_0047AE20* receiver = (TwoIndexTableAddressOwnertext_0047AE20*)object;
    return &receiver->entries[row * (receiver->count - 1) + column];
}

/** Return the word at receiver offset 0x1C. */
u32 func_0047E150(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk1c;
}

/** Return the word at receiver offset 0xC. */
u32 func_0047E160(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk0c;
}

/** Return the word at receiver offset 0x10. */
u32 func_0047E170(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk10;
}

s32 func_0047E180(void* object)
{
    return 7;
}

s32 func_0047E190(void* receiver)
{
    WordNonzeroOwnertext_0047AE20* object = (WordNonzeroOwnertext_0047AE20*)receiver;
    return object->unk14 != 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E1A0);

void* func_0047E200(void* object, s32 index)
{
    SingleIndexTableAddressOwnertext_0047AE20* receiver = (SingleIndexTableAddressOwnertext_0047AE20*)object;
    return receiver->base14 + index * 144;
}

void* func_0047E220(void* object, s32 row, s32 column)
{
    TwoIndexTableAddressOwnertext_0047AE20* receiver = (TwoIndexTableAddressOwnertext_0047AE20*)object;
    return &receiver->entries[row * (receiver->count - 1) + column];
}

/** Return the word at receiver offset 0x1C. */
u32 func_0047E240(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk1c;
}

/** Return the word at receiver offset 0xC. */
u32 func_0047E250(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk0c;
}

/** Return the word at receiver offset 0x10. */
u32 func_0047E260(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk10;
}

s32 func_0047E270(void* object)
{
    return 35;
}

s32 func_0047E280(void* receiver)
{
    WordNonzeroOwnertext_0047AE20* object = (WordNonzeroOwnertext_0047AE20*)receiver;
    return object->unk14 != 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E290);

void* func_0047E2F0(void* object, s32 index)
{
    SingleIndexTableAddressOwnertext_0047AE20* receiver = (SingleIndexTableAddressOwnertext_0047AE20*)object;
    return receiver->base14 + index * 96;
}

void* func_0047E310(void* object, s32 row, s32 column)
{
    TwoIndexTableAddressOwnertext_0047AE20* receiver = (TwoIndexTableAddressOwnertext_0047AE20*)object;
    return &receiver->entries[row * (receiver->count - 1) + column];
}

/** Return the word at receiver offset 0x1C. */
u32 func_0047E330(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk1c;
}

/** Return the word at receiver offset 0xC. */
u32 func_0047E340(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk0c;
}

/** Return the word at receiver offset 0x10. */
u32 func_0047E350(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk10;
}

s32 func_0047E360(void* object)
{
    return 3;
}

s32 func_0047E370(void* receiver)
{
    WordNonzeroOwnertext_0047AE20* object = (WordNonzeroOwnertext_0047AE20*)receiver;
    return object->unk14 != 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E380);

void* func_0047E3E0(void* object, s32 index)
{
    SingleIndexTableAddressOwnertext_0047AE20* receiver = (SingleIndexTableAddressOwnertext_0047AE20*)object;
    return receiver->base14 + index * 96;
}

void* func_0047E400(void* object, s32 row, s32 column)
{
    TwoIndexTableAddressOwnertext_0047AE20* receiver = (TwoIndexTableAddressOwnertext_0047AE20*)object;
    return &receiver->entries[row * (receiver->count - 1) + column];
}

/** Return the word at receiver offset 0x1C. */
u32 func_0047E420(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk1c;
}

/** Return the word at receiver offset 0xC. */
u32 func_0047E430(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk0c;
}

/** Return the word at receiver offset 0x10. */
u32 func_0047E440(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = (const WordGetterOwnertext_0047AE20*)object;
    return receiver->unk10;
}

s32 func_0047E450(void* object)
{
    return 33;
}

s32 func_0047E460(void* receiver)
{
    WordNonzeroOwnertext_0047AE20* object = (WordNonzeroOwnertext_0047AE20*)receiver;
    return object->unk14 != 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E470);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E4D0);

void* func_0047EA30(void* receiver)
{
    *(void**)receiver = &__vt__7LibLink;
    *(void**)receiver = D_00173A28;
    *(void**)receiver = D_00173F48;
    *(void**)receiver = D_00177188;
    return receiver;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047EA70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047EAF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047EBD0);

void* func_0047F130(void* receiver)
{
    *(void**)receiver = &__vt__7LibLink;
    *(void**)receiver = D_00173A28;
    *(void**)receiver = D_00173F48;
    *(void**)receiver = D_00174228;
    return receiver;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047F170);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047F250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047F7B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047F800);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047F890);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047F970);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047FEC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047FF10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047FFF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00480550);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_004805A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00480640);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00480720);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00480C80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00480CD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00480DB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00481310);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00481370);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00481420);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00481500);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00481A60);

/**
 * @brief Copy another grid's size and settings, reallocating this grid to match.
 *
 * LibClass176940's copy_settings (vtable slot 0xB4).
 * @param object Grid to update.
 * @param other Grid to copy.
 */
void func_00481AC0(LibGridEmitter* object, const LibGridEmitter* other)
{
    object->cell_count = other->cell_count;
    object->columns = other->columns;
    object->resize(object->cell_count, object->columns);
    object->unk28 = other->unk28;
    object->unk30 = other->unk30;
    object->unk34 = other->unk34;
    object->unk38 = other->unk38;
    object->unk48 = other->unk48;
    object->unk4C = other->unk4C;
    object->unk4D = other->unk4D;
    object->unk4E = other->unk4E;
    object->unk4F = other->unk4F;
    object->unk50 = other->unk50;
    object->unk54 = other->unk54;
    object->unk55 = other->unk55;
    object->unk3C = other->unk3C;
    object->frame_header = other->frame_header;
    object->frame_records = other->frame_records;
}

/** A vector whose fourth word can hold a frame index. */
typedef union GridFrameVector
{
    unsigned __int128 packed;
    float floats[4];

    struct
    {
        float xyz[3];
        s32 frame_index;
    } components;
} GridFrameVector;

/** Per-cell frame playback state. */
typedef struct GridFrameState
{
    s32 reverse;
    s32 frame_index;
    float remaining_time;
    s32 boundary_count;
} GridFrameState;

/** An animated vector, its rate, and the cell's frame playback state. */
typedef struct GridFrameMotion
{
    GridFrameVector value;
    GridFrameVector rate;
    GridFrameState frame;
} GridFrameMotion;

typedef struct GridRowElement
{
    u8 unk00[0x30];
    GridFrameVector unk30;
} GridRowElement;

/** Output record containing an updated vector and an optional frame index. */
typedef struct GridOutputRecord
{
    u8 unk00[0x20];
    GridFrameVector frame_vector;
} GridOutputRecord;

typedef struct GridBitset
{
    u8 unk00[0x8];
    u64* unk08;
} GridBitset;

typedef struct GridFrameHeader
{
    u8 frame_count;
    u8 unk01[2];
    u8 loop_mode;
} GridFrameHeader;

/** A 0x50-byte frame record with its duration measured in frames. */
typedef struct GridFrameRecord
{
    u8 unk00[0xC];
    float duration_frames;
    u8 unk10[0x40];
} GridFrameRecord;

/**
 * @brief Clear an active cell bit.
 * @param object Bit set owning the storage.
 * @param index Unsigned cell index.
 */
static inline void grid_clear_cell_bit(GridBitset* object, u32 index)
{
    u32 word_index = index >> 6;
    u64 keep_mask = ~((u64)1 << (index & 63));
    object->unk08[word_index] &= keep_mask;
}

typedef struct GridCell00481B90
{
    u8 unk00[0x30];
    GridFrameMotion motion;
} GridCell00481B90;

typedef struct GridOwner00481B90
{
    u8 unk00[0xC];
    s32 unk0C;
    s32 unk10;
    GridCell00481B90* unk14;
    u8 unk18[4];
    GridBitset* unk1C;
    GridRowElement* unk20;
    u8 unk24[8];
    s32 unk2C;
    float unk30;
    u8 unk34[0x18];
    u8 unk4C;
    u8 unk4d[0xA];
    u8 skip_frame_playback;
    u8 unk58[0x48];
    GridFrameHeader* frame_header;
    GridFrameRecord* frame_records;
} GridOwner00481B90;

/**
 * @brief Get a 0x60-byte cell's motion state at offset 0x30.
 * @param cell Cell to read.
 * @return The motion state, or null when the cell address is null.
 */
static inline GridFrameMotion* grid_cell_motion_00481B90(GridCell00481B90* cell)
{
    GridFrameMotion* motion = (GridFrameMotion*)cell;
    if (cell != 0)
    {
        motion = &cell->motion;
    }
    return motion;
}

/**
 * @brief Advance active cells' frame vectors and playback state into an output batch.
 * @param object Grid owning the cells and frame resource.
 * @param capacity Output-entry budget, counted in steps of the grid column count.
 * @param output Output records, with each cell written at the start of its row.
 * @param preserve_row_vector Nonzero to retain the saved xyz components in the first row element.
 */
void func_00481B90(GridOwner00481B90* object, s32 capacity, GridOutputRecord* output, s32 preserve_row_vector)
{
    s32 columns = object->unk10;
    s32 index = object->unk2C;
    s32 cells = object->unk0C;
    u64* words = object->unk1C->unk08;
    u64 mask = (u64)1 << (index & 63);
    s32 word_index = index / 64;
    u64 active_word = words[word_index++];

    if (object->skip_frame_playback != 0)
    {
        s32 consumed = 0;
        vu0_set_grid_frame_delta(g_frame_seconds);

        if (columns == 1)
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;

                mask <<= 1;
                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }
                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_00481B90(&object->unk14[index]);
                vu0_load_grid_frame_vectors(&state->value, &state->rate);
                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
        else
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;
                GridFrameVector* previous;

                mask <<= 1;
                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }
                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_00481B90(&object->unk14[index]);
                previous = &object->unk20[index * (columns - 1)].unk30;
                if (preserve_row_vector == 0)
                {
                    previous->packed = state->value.packed;
                }
                vu0_load_grid_frame_vectors(&state->value, &state->rate);
                previous->components.frame_index = 0;
                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
    }
    else
    {
        s32 consumed = 0;
        s32 frame_count = object->frame_header->frame_count;
        s32 loop_mode = object->frame_header->loop_mode;
        s32 boundary_limit = (s32)object->unk30;
        float frame_seconds = 1.0f / 60.0f;
        vu0_set_grid_frame_delta(g_frame_seconds);

        if (columns == 1)
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;
                GridFrameState* frame;
                s32 frame_index;

                mask <<= 1;
                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }
                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_00481B90(&object->unk14[index]);
                frame = &state->frame;
                if (object->unk4C == 4 && boundary_limit < frame->boundary_count)
                {
                    grid_clear_cell_bit(object->unk1C, index);
                    index++;
                    continue;
                }

                frame->remaining_time -= g_frame_seconds;
                frame_index = frame->frame_index;
                vu0_load_grid_frame_vectors(&state->value, &state->rate);
                while (frame->remaining_time <= 0.0f)
                {
                    frame_index += frame->reverse != 0 ? -1 : 1;
                    if (frame_index >= frame_count)
                    {
                        switch (loop_mode)
                        {
                            case 0:
                                frame_index = 0;
                                break;
                            case 1:
                                frame->reverse = 1;
                                frame_index--;
                                break;
                            case 2:
                                frame_index--;
                                break;
                        }
                        frame->boundary_count++;
                    }
                    else if (frame_index < 0)
                    {
                        frame->reverse = 0;
                        frame_index = 0;
                        frame->boundary_count++;
                    }
                    frame->frame_index = frame_index;
                    frame->remaining_time += frame_seconds * object->frame_records[frame_index].duration_frames;
                }

                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                output->frame_vector.components.frame_index = frame_index;
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
        else
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;
                GridFrameState* frame;
                GridFrameVector* previous;
                s32 frame_index;

                mask <<= 1;
                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }
                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_00481B90(&object->unk14[index]);
                frame = &state->frame;
                if (object->unk4C == 4 && boundary_limit < frame->boundary_count)
                {
                    grid_clear_cell_bit(object->unk1C, index);
                    index++;
                    continue;
                }

                frame->remaining_time -= g_frame_seconds;
                frame_index = frame->frame_index;
                previous = &object->unk20[index * (columns - 1)].unk30;
                if (preserve_row_vector == 0)
                {
                    previous->packed = state->value.packed;
                }
                previous->components.frame_index = frame_index;
                vu0_load_grid_frame_vectors(&state->value, &state->rate);
                while (frame->remaining_time <= 0.0f)
                {
                    frame_index += frame->reverse != 0 ? -1 : 1;
                    if (frame_index >= frame_count)
                    {
                        switch (loop_mode)
                        {
                            case 0:
                                frame_index = 0;
                                break;
                            case 1:
                                frame->reverse = 1;
                                frame_index--;
                                break;
                            case 2:
                                frame_index--;
                                break;
                        }
                        frame->boundary_count++;
                    }
                    else if (frame_index < 0)
                    {
                        frame->reverse = 0;
                        frame_index = 0;
                        frame->boundary_count++;
                    }
                    frame->frame_index = frame_index;
                    frame->remaining_time += frame_seconds * object->frame_records[frame_index].duration_frames;
                }

                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                output->frame_vector.components.frame_index = frame_index;
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
    }
}

/** Aligned vector with floating-point and raw-word views. */
union HistoryQuad
{
    unsigned __int128 raw;
    float value[4];
    u32 word[4];

    /**
     * @brief Get the vector's four floating-point components.
     * @return The first component.
     */
    float* data()
    {
        return value;
    }

    /**
     * @brief Get the vector's four floating-point components.
     * @return The first component.
     */
    const float* data() const
    {
        return value;
    }

    /**
     * @brief Copy a vector as one 128-bit value.
     * @param other Vector to copy.
     * @return This vector.
     */
    HistoryQuad& operator=(const HistoryQuad& other)
    {
        raw = other.raw;
        return *this;
    }
};

/** History record with position, attributes, and control words. */
struct HistoryRecord
{
    HistoryQuad unk00;
    HistoryQuad position;
    HistoryQuad attributes;
    HistoryQuad control;
};

/** Three-vector output record. */
typedef struct HistoryOutput
{
    HistoryQuad position;
    HistoryQuad attributes;
    HistoryQuad control;
} HistoryOutput;

typedef struct HistoryMask
{
    u8 unk00[8];
    const u64* unk08;
} HistoryMask;


/** Source record of size 0x60 with position and attribute vectors. */
typedef struct HistorySource60
{
    HistoryQuad unk00;
    HistoryQuad position;
    HistoryQuad attributes;
    u8 unk30[0x30];
} HistorySource60;

/** Observed receiver prefix for selected-group history output. */
typedef struct HistoryReceiver60
{
    u8 unk00[0xC];
    s32 limit;
    s32 samples;
    HistorySource60* source;
    u32 unk18;
    HistoryMask* mask;
    HistoryRecord* history;
    u32 unk24;
    union
    {
        float value;
        u32 bits;
    } unk28;
    s32 index;
    float unk30;
    float decrement;
    u8 unk38[0xC];
    float scale;
    u8 unk48[5];
    u8 mode;
    u8 unk4e[8];
    u8 policy;
} HistoryReceiver60;

/**
 * @brief Write the history samples of each selected group into consecutive output records.
 * @param object Receiver owning the selection mask, sources and history.
 * @param capacity Output-record budget.
 * @param output First output record.
 * @param stamp Nonzero to stamp each group's control word with the receiver's value at offset 0x28.
 */
extern "C" void func_004822B0(HistoryReceiver60* object, s32 capacity, HistoryOutput* output, u32 stamp)
{
    s32 samples = object->samples;
    s32 index = object->index;
    s32 limit = object->limit;
    const u64* masks = object->mask->unk08;
    u64 bit = (u64)1 << (index & 63);
    s32 mask_index = index / 64;
    s32 processed = 0;
    u64 mask = masks[mask_index++];
    switch (object->policy)
    {
        case 0:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
        case 1:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
        case 2:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad position;
                            position = source->position;
                            lib_normalize_vector3(position.value);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad position;
                            position = source->position;
                            lib_normalize_vector3(position.value);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad position;
                            position = source->position;
                            lib_normalize_vector3(position.value);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad position;
                            position = source->position;
                            lib_normalize_vector3(position.value);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad position;
                            position = source->position;
                            lib_normalize_vector3(position.value);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            HistorySource60* source = &object->source[index - 1];
                            s32 history_index = index * (samples - 1) - 1;
                            HistoryQuad position;
                            position = source->position;
                            lib_normalize_vector3(position.value);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad position;
                            position = source->position;
                            lib_normalize_vector3(position.value);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad position;
                            position = source->position;
                            lib_normalize_vector3(position.value);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
    }
}

/**
 * @brief Copy another grid's size and settings, reallocating this grid to match.
 *
 * LibClass176530's copy_settings (vtable slot 0xB4).
 * @param object Grid to update.
 * @param other Grid to copy.
 */
void func_00484D80(LibGridEmitter* object, const LibGridEmitter* other)
{
    object->cell_count = other->cell_count;
    object->columns = other->columns;
    object->resize(object->cell_count, object->columns);
    object->unk28 = other->unk28;
    object->unk30 = other->unk30;
    object->unk34 = other->unk34;
    object->unk38 = other->unk38;
    object->unk48 = other->unk48;
    object->unk4C = other->unk4C;
    object->unk4D = other->unk4D;
    object->unk4E = other->unk4E;
    object->unk4F = other->unk4F;
    object->unk50 = other->unk50;
    object->unk54 = other->unk54;
    object->unk55 = other->unk55;
    object->unk3C = other->unk3C;
    object->frame_header = other->frame_header;
    object->frame_records = other->frame_records;
}

typedef struct GridCell00484E50
{
    u8 unk00[0x60];
} GridCell00484E50;

typedef struct GridOwner00484E50
{
    u8 unk00[0xC];
    s32 unk0C;
    s32 unk10;
    GridCell00484E50* unk14;
    u8 unk18[4];
    GridBitset* unk1C;
    GridRowElement* unk20;
    u8 unk24[8];
    s32 unk2C;
    float unk30;
    u8 unk34[0x18];
    u8 unk4C;
    u8 unk4d[0xA];
    u8 skip_frame_playback;
    u8 unk58[0x48];
    GridFrameHeader* frame_header;
    GridFrameRecord* frame_records;
} GridOwner00484E50;

/**
 * @brief Get a 0x60-byte cell's motion state at offset 0x60.
 * @param cell Cell to read.
 * @return The motion state, or null when the cell address is null.
 */
static inline GridFrameMotion* grid_cell_motion_00484E50(GridCell00484E50* cell)
{
    GridFrameMotion* motion = (GridFrameMotion*)cell;
    if (cell != 0)
    {
        motion = (GridFrameMotion*)((u8*)cell + 0x60);
    }
    return motion;
}

/**
 * @brief Advance active cells' frame vectors and playback state into an output batch.
 * @param object Grid owning the cells and frame resource.
 * @param capacity Output-entry budget, counted in steps of the grid column count.
 * @param output Output records, with each cell written at the start of its row.
 * @param preserve_row_vector Nonzero to retain the saved xyz components in the first row element.
 */
void func_00484E50(GridOwner00484E50* object, s32 capacity, GridOutputRecord* output, s32 preserve_row_vector)
{
    s32 columns = object->unk10;
    s32 index = object->unk2C;
    s32 cells = object->unk0C;
    u64* words = object->unk1C->unk08;
    u64 mask = (u64)1 << (index & 63);
    s32 word_index = index / 64;
    u64 active_word = words[word_index++];

    if (object->skip_frame_playback != 0)
    {
        s32 consumed = 0;
        vu0_set_grid_frame_delta(g_frame_seconds);

        if (columns == 1)
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;

                mask <<= 1;
                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }
                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_00484E50(&object->unk14[index]);
                vu0_load_grid_frame_vectors(&state->value, &state->rate);
                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
        else
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;
                GridFrameVector* previous;

                mask <<= 1;
                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }
                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_00484E50(&object->unk14[index]);
                previous = &object->unk20[index * (columns - 1)].unk30;
                if (preserve_row_vector == 0)
                {
                    previous->packed = state->value.packed;
                }
                vu0_load_grid_frame_vectors(&state->value, &state->rate);
                previous->components.frame_index = 0;
                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
    }
    else
    {
        s32 consumed = 0;
        s32 frame_count = object->frame_header->frame_count;
        s32 loop_mode = object->frame_header->loop_mode;
        s32 boundary_limit = (s32)object->unk30;
        float frame_seconds = 1.0f / 60.0f;
        vu0_set_grid_frame_delta(g_frame_seconds);

        if (columns == 1)
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;
                GridFrameState* frame;
                s32 frame_index;

                mask <<= 1;
                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }
                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_00484E50(&object->unk14[index]);
                frame = &state->frame;
                if (object->unk4C == 4 && boundary_limit < frame->boundary_count)
                {
                    grid_clear_cell_bit(object->unk1C, index);
                    index++;
                    continue;
                }

                frame->remaining_time -= g_frame_seconds;
                frame_index = frame->frame_index;
                vu0_load_grid_frame_vectors(&state->value, &state->rate);
                while (frame->remaining_time <= 0.0f)
                {
                    frame_index += frame->reverse != 0 ? -1 : 1;
                    if (frame_index >= frame_count)
                    {
                        switch (loop_mode)
                        {
                            case 0:
                                frame_index = 0;
                                break;
                            case 1:
                                frame->reverse = 1;
                                frame_index--;
                                break;
                            case 2:
                                frame_index--;
                                break;
                        }
                        frame->boundary_count++;
                    }
                    else if (frame_index < 0)
                    {
                        frame->reverse = 0;
                        frame_index = 0;
                        frame->boundary_count++;
                    }
                    frame->frame_index = frame_index;
                    frame->remaining_time += frame_seconds * object->frame_records[frame_index].duration_frames;
                }

                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                output->frame_vector.components.frame_index = frame_index;
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
        else
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;
                GridFrameState* frame;
                GridFrameVector* previous;
                s32 frame_index;

                mask <<= 1;
                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }
                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_00484E50(&object->unk14[index]);
                frame = &state->frame;
                if (object->unk4C == 4 && boundary_limit < frame->boundary_count)
                {
                    grid_clear_cell_bit(object->unk1C, index);
                    index++;
                    continue;
                }

                frame->remaining_time -= g_frame_seconds;
                frame_index = frame->frame_index;
                previous = &object->unk20[index * (columns - 1)].unk30;
                if (preserve_row_vector == 0)
                {
                    previous->packed = state->value.packed;
                }
                previous->components.frame_index = frame_index;
                vu0_load_grid_frame_vectors(&state->value, &state->rate);
                while (frame->remaining_time <= 0.0f)
                {
                    frame_index += frame->reverse != 0 ? -1 : 1;
                    if (frame_index >= frame_count)
                    {
                        switch (loop_mode)
                        {
                            case 0:
                                frame_index = 0;
                                break;
                            case 1:
                                frame->reverse = 1;
                                frame_index--;
                                break;
                            case 2:
                                frame_index--;
                                break;
                        }
                        frame->boundary_count++;
                    }
                    else if (frame_index < 0)
                    {
                        frame->reverse = 0;
                        frame_index = 0;
                        frame->boundary_count++;
                    }
                    frame->frame_index = frame_index;
                    frame->remaining_time += frame_seconds * object->frame_records[frame_index].duration_frames;
                }

                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                output->frame_vector.components.frame_index = frame_index;
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
    }
}

/**
 * @brief Write the history samples of each selected group into consecutive output records.
 * @param object Receiver owning the selection mask, sources and history.
 * @param capacity Output-record budget.
 * @param output First output record.
 * @param stamp Nonzero to stamp each group's control word with the receiver's value at offset 0x28.
 */
extern "C" void func_00485570(HistoryReceiver60* object, s32 capacity, HistoryOutput* output, u32 stamp)
{
    s32 samples = object->samples;
    s32 index = object->index;
    s32 limit = object->limit;
    const u64* masks = object->mask->unk08;
    u64 bit = (u64)1 << (index & 63);
    s32 mask_index = index / 64;
    s32 processed = 0;
    u64 mask = masks[mask_index++];
    switch (object->policy)
    {
        case 0:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
        case 1:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
        case 2:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad position;
                            position = source->position;
                            lib_normalize_vector3(position.value);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad position;
                            position = source->position;
                            lib_normalize_vector3(position.value);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad position;
                            position = source->position;
                            lib_normalize_vector3(position.value);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad position;
                            position = source->position;
                            lib_normalize_vector3(position.value);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad position;
                            position = source->position;
                            lib_normalize_vector3(position.value);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            HistorySource60* source = &object->source[index - 1];
                            s32 history_index = index * (samples - 1) - 1;
                            HistoryQuad position;
                            position = source->position;
                            lib_normalize_vector3(position.value);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad position;
                            position = source->position;
                            lib_normalize_vector3(position.value);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            HistorySource60* source = &object->source[index - 1];
                            HistoryQuad position;
                            position = source->position;
                            lib_normalize_vector3(position.value);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
    }
}

/**
 * @brief Copy another grid's size and settings, reallocating this grid to match.
 *
 * LibClass1762C0's copy_settings (vtable slot 0xB4).
 * @param object Grid to update.
 * @param other Grid to copy.
 */
void func_00488040(LibGridEmitter* object, const LibGridEmitter* other)
{
    object->cell_count = other->cell_count;
    object->columns = other->columns;
    object->resize(object->cell_count, object->columns);
    object->unk28 = other->unk28;
    object->unk30 = other->unk30;
    object->unk34 = other->unk34;
    object->unk38 = other->unk38;
    object->unk48 = other->unk48;
    object->unk4C = other->unk4C;
    object->unk4D = other->unk4D;
    object->unk4E = other->unk4E;
    object->unk4F = other->unk4F;
    object->unk50 = other->unk50;
    object->unk54 = other->unk54;
    object->unk55 = other->unk55;
    object->unk3C = other->unk3C;
    object->frame_header = other->frame_header;
    object->frame_records = other->frame_records;
}

typedef struct GridCell00488110
{
    u8 unk00[0x60];
    GridFrameMotion motion;
} GridCell00488110;

typedef struct GridOwner00488110
{
    u8 unk00[0xC];
    s32 unk0C;
    s32 unk10;
    GridCell00488110* unk14;
    u8 unk18[4];
    GridBitset* unk1C;
    GridRowElement* unk20;
    u8 unk24[8];
    s32 unk2C;
    float unk30;
    u8 unk34[0x18];
    u8 unk4C;
    u8 unk4d[0xA];
    u8 skip_frame_playback;
    u8 unk58[0x48];
    GridFrameHeader* frame_header;
    GridFrameRecord* frame_records;
} GridOwner00488110;

/**
 * @brief Get a 0x90-byte cell's motion state at offset 0x60.
 * @param cell Cell to read.
 * @return The motion state, or null when the cell address is null.
 */
static inline GridFrameMotion* grid_cell_motion_00488110(GridCell00488110* cell)
{
    GridFrameMotion* motion = (GridFrameMotion*)cell;
    if (cell != 0)
    {
        motion = &cell->motion;
    }
    return motion;
}

/**
 * @brief Advance active cells' frame vectors and playback state into an output batch.
 * @param object Grid owning the cells and frame resource.
 * @param capacity Output-entry budget, counted in steps of the grid column count.
 * @param output Output records, with each cell written at the start of its row.
 * @param preserve_row_vector Nonzero to retain the saved xyz components in the first row element.
 */
void func_00488110(GridOwner00488110* object, s32 capacity, GridOutputRecord* output, s32 preserve_row_vector)
{
    s32 columns = object->unk10;
    s32 index = object->unk2C;
    s32 cells = object->unk0C;
    u64* words = object->unk1C->unk08;
    u64 mask = (u64)1 << (index & 63);
    s32 word_index = index / 64;
    u64 active_word = words[word_index++];

    if (object->skip_frame_playback != 0)
    {
        s32 consumed = 0;
        vu0_set_grid_frame_delta(g_frame_seconds);

        if (columns == 1)
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;

                mask <<= 1;
                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }
                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_00488110(&object->unk14[index]);
                vu0_load_grid_frame_vectors(&state->value, &state->rate);
                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
        else
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;
                GridFrameVector* previous;

                mask <<= 1;
                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }
                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_00488110(&object->unk14[index]);
                previous = &object->unk20[index * (columns - 1)].unk30;
                if (preserve_row_vector == 0)
                {
                    previous->packed = state->value.packed;
                }
                vu0_load_grid_frame_vectors(&state->value, &state->rate);
                previous->components.frame_index = 0;
                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
    }
    else
    {
        s32 consumed = 0;
        s32 frame_count = object->frame_header->frame_count;
        s32 loop_mode = object->frame_header->loop_mode;
        s32 boundary_limit = (s32)object->unk30;
        float frame_seconds = 1.0f / 60.0f;
        vu0_set_grid_frame_delta(g_frame_seconds);

        if (columns == 1)
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;
                GridFrameState* frame;
                s32 frame_index;

                mask <<= 1;
                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }
                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_00488110(&object->unk14[index]);
                frame = &state->frame;
                if (object->unk4C == 4 && boundary_limit < frame->boundary_count)
                {
                    grid_clear_cell_bit(object->unk1C, index);
                    index++;
                    continue;
                }

                frame->remaining_time -= g_frame_seconds;
                frame_index = frame->frame_index;
                vu0_load_grid_frame_vectors(&state->value, &state->rate);
                while (frame->remaining_time <= 0.0f)
                {
                    frame_index += frame->reverse != 0 ? -1 : 1;
                    if (frame_index >= frame_count)
                    {
                        switch (loop_mode)
                        {
                            case 0:
                                frame_index = 0;
                                break;
                            case 1:
                                frame->reverse = 1;
                                frame_index--;
                                break;
                            case 2:
                                frame_index--;
                                break;
                        }
                        frame->boundary_count++;
                    }
                    else if (frame_index < 0)
                    {
                        frame->reverse = 0;
                        frame_index = 0;
                        frame->boundary_count++;
                    }
                    frame->frame_index = frame_index;
                    frame->remaining_time += frame_seconds * object->frame_records[frame_index].duration_frames;
                }

                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                output->frame_vector.components.frame_index = frame_index;
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
        else
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;
                GridFrameState* frame;
                GridFrameVector* previous;
                s32 frame_index;

                mask <<= 1;
                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }
                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_00488110(&object->unk14[index]);
                frame = &state->frame;
                if (object->unk4C == 4 && boundary_limit < frame->boundary_count)
                {
                    grid_clear_cell_bit(object->unk1C, index);
                    index++;
                    continue;
                }

                frame->remaining_time -= g_frame_seconds;
                frame_index = frame->frame_index;
                previous = &object->unk20[index * (columns - 1)].unk30;
                if (preserve_row_vector == 0)
                {
                    previous->packed = state->value.packed;
                }
                previous->components.frame_index = frame_index;
                vu0_load_grid_frame_vectors(&state->value, &state->rate);
                while (frame->remaining_time <= 0.0f)
                {
                    frame_index += frame->reverse != 0 ? -1 : 1;
                    if (frame_index >= frame_count)
                    {
                        switch (loop_mode)
                        {
                            case 0:
                                frame_index = 0;
                                break;
                            case 1:
                                frame->reverse = 1;
                                frame_index--;
                                break;
                            case 2:
                                frame_index--;
                                break;
                        }
                        frame->boundary_count++;
                    }
                    else if (frame_index < 0)
                    {
                        frame->reverse = 0;
                        frame_index = 0;
                        frame->boundary_count++;
                    }
                    frame->frame_index = frame_index;
                    frame->remaining_time += frame_seconds * object->frame_records[frame_index].duration_frames;
                }

                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                output->frame_vector.components.frame_index = frame_index;
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
    }
}

/** Source record of size 0x90 with position and attribute vectors. */
typedef struct HistorySource90
{
    HistoryQuad unk00;
    HistoryQuad position;
    HistoryQuad attributes;
    u8 unk30[0x60];
} HistorySource90;

/** Observed receiver prefix for selected-group history output. */
typedef struct HistoryReceiver90
{
    u8 unk00[0xC];
    s32 limit;
    s32 samples;
    HistorySource90* source;
    u32 unk18;
    HistoryMask* mask;
    HistoryRecord* history;
    u32 unk24;
    union
    {
        float value;
        u32 bits;
    } unk28;
    s32 index;
    float unk30;
    float decrement;
    u8 unk38[0xC];
    float scale;
    u8 unk48[5];
    u8 mode;
    u8 unk4e[8];
    u8 policy;
} HistoryReceiver90;

/**
 * @brief Write the history samples of each selected group into consecutive output records.
 * @param object Receiver owning the selection mask, sources and history.
 * @param capacity Output-record budget.
 * @param output First output record.
 * @param stamp Nonzero to stamp each group's control word with the receiver's value at offset 0x28.
 */
extern "C" void func_00488830(HistoryReceiver90* object, s32 capacity, HistoryOutput* output, u32 stamp)
{
    s32 samples = object->samples;
    s32 index = object->index;
    s32 limit = object->limit;
    const u64* masks = object->mask->unk08;
    u64 bit = (u64)1 << (index & 63);
    s32 mask_index = index / 64;
    s32 processed = 0;
    u64 mask = masks[mask_index++];
    switch (object->policy)
    {
        case 0:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource90* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource90* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource90* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource90* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource90* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource90* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource90* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource90* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
        case 1:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource90* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource90* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource90* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource90* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource90* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource90* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource90* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_position = &current->position;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistorySource90* source = &object->source[index - 1];
                            HistoryQuad* current_position = &current->position;
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
        case 2:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            HistorySource90* source = &object->source[index - 1];
                            HistoryQuad position;
                            position = source->position;
                            lib_normalize_vector3(position.value);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            HistorySource90* source = &object->source[index - 1];
                            HistoryQuad position;
                            position = source->position;
                            lib_normalize_vector3(position.value);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            HistorySource90* source = &object->source[index - 1];
                            HistoryQuad position;
                            position = source->position;
                            lib_normalize_vector3(position.value);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            HistorySource90* source = &object->source[index - 1];
                            HistoryQuad position;
                            position = source->position;
                            lib_normalize_vector3(position.value);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            HistorySource90* source = &object->source[index - 1];
                            HistoryQuad position;
                            position = source->position;
                            lib_normalize_vector3(position.value);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            HistorySource90* source = &object->source[index - 1];
                            s32 history_index = index * (samples - 1) - 1;
                            HistoryQuad position;
                            position = source->position;
                            lib_normalize_vector3(position.value);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            HistorySource90* source = &object->source[index - 1];
                            HistoryQuad position;
                            position = source->position;
                            lib_normalize_vector3(position.value);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            HistorySource90* source = &object->source[index - 1];
                            HistoryQuad position;
                            position = source->position;
                            lib_normalize_vector3(position.value);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                HistoryOutput* out = &output[sample];
                                HistoryRecord* current = &object->history[history_index--];
                                HistoryRecord* previous = current - 1;
                                HistoryQuad* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                HistoryQuad* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            HistoryOutput* out = &output[1];
                            HistoryRecord* current = &object->history[history_index];
                            HistoryQuad* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            HistoryQuad* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
    }
}
