#include "include_asm.h"
#include "overlays/lib/text_0043A920.h"
#include "overlays/lib/text_0049B820.h"
#include "overlays/lib/particle_grid.h"
#include "overlays/lib/text_0043BD00.h"
#include "main/resident_data.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/lib/row_fill.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/grid_frame.h"
#include "overlays/lib/grid_frame_vu0.h"
#include "overlays/lib/particle_history.h"
#include "overlays/lib/text_004CD3A0.h"
#include "vu0.h"
#include "ee.h"

extern "C" {

typedef struct WordNonzeroOwnertext_0043A920
{
    u8 unk00[0x14];
    u32 unk14;
} WordNonzeroOwnertext_0043A920;

typedef struct ByteGetterOwnertext_0043A920
{
    u8 unk00[0x4D];
    u8 unk4d;
    u8 unk4e[0x8];
    u8 unk56;
} ByteGetterOwnertext_0043A920;

typedef struct ByteSetterOwnertext_0043A920
{
    u8 unk00[0x4D];
    u8 unk4d;
    u8 unk4e;
    u8 unk4f;
    u8 unk50[0x4];
    u8 unk54;
    u8 unk55;
    u8 unk56;
} ByteSetterOwnertext_0043A920;

typedef struct WordSetterOwnertext_0043A920
{
    u8 unk00[0x48];
    u32 unk48;
    u8 unk4c[0x4];
    u32 unk50;
    u8 unk54[0x64];
    u32 unkb8;
    u32 unkbc;
} WordSetterOwnertext_0043A920;

typedef struct WordGetterOwnertext_0043A920
{
    u8 unk00[0x4];
    u32 unk04;
    u8 unk08[0x4];
    u32 unk0c;
    u32 unk10;
    u8 unk14[0x8];
    u32 unk1c;
    u8 unk20[0x20];
    u32 unk40;
    u8 unk44[0x4];
    u32 unk48;
    u8 unk4c[0x4];
    u32 unk50;
    u8 unk54[0x64];
    u32 unkb8;
    u32 unkbc;
} WordGetterOwnertext_0043A920;

typedef struct LibFloatFieldOwner0043A920
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
} LibFloatFieldOwner0043A920;

typedef struct ByteSourceStateOwnertext_0043A920 { u8 pad00[0x57]; u8 state57; u8 pad58[0x48]; const u8* sourceA0; u32 valueA4; } ByteSourceStateOwnertext_0043A920;

typedef struct TwoWordClearArgStateOwnertext_0043A920 { u8 pad00[0x57]; u8 state57; u8 pad58[0x48]; void* unkA0; void* unkA4; } TwoWordClearArgStateOwnertext_0043A920;

typedef struct FourQuadwordCopyTargetOwnertext_0043A920
{
    u8 pad00[0x2C];
    u32 unk2C;
    u8 pad30[0x30];
    unsigned __int128 values60[4];
} FourQuadwordCopyTargetOwnertext_0043A920;

typedef struct FourQuadwordCopySourceOwnertext_0043A920
{
    u8 pad00[0x150];
    unsigned __int128 values150[4];
} FourQuadwordCopySourceOwnertext_0043A920;

typedef struct TwoIndexTableEntryOwnertext_0043A920
{
    u8 data[0x40];
} TwoIndexTableEntryOwnertext_0043A920;

typedef struct TwoIndexTableAddressOwnertext_0043A920
{
    u8 pad00[0x10];
    s32 count;
    u8 pad14[0xC];
    TwoIndexTableEntryOwnertext_0043A920* entries;
} TwoIndexTableAddressOwnertext_0043A920;

typedef struct SingleIndexTableAddressOwnertext_0043A920
{
    u8 pad00[0x14];
    u8* base14;
} SingleIndexTableAddressOwnertext_0043A920;

extern void* __vt__7LibLink;

extern u8 D_00173A28[];

extern u8 D_00173F48[];

extern u8 D_00173F38[];

extern void func_004447E0(void* object, void* cell, void* row, s32 index, void* extra4, void* extra5, void* extra6, void* extra7, void* extra8);

/** @brief Destroy the transform. */
LibClass173B10::~LibClass173B10()
{
}

/**
 * @brief Read a transform's translation from its matrix, with a w of one.
 * @param result Receives the translation.
 * @param object Transform.
 */
static inline void lib_get_transform_translation(FieldVec4B& result, const LibTransform& object)
{
    result.x = object.transform.m[0][3];
    result.y = object.transform.m[1][3];
    result.z = object.transform.m[2][3];
    result.w = 1.0f;
}

/**
 * @brief Copy a matrix four rows at a time, each as one 128-bit value.
 * @param destination Matrix receiving the copy.
 * @param source Matrix to copy.
 */
static inline void lib_copy_matrix(LibMatrix44Value* destination, const LibMatrix44Value* source)
{
    ((unsigned __int128*)destination)[0] = ((const unsigned __int128*)source)[0];
    ((unsigned __int128*)destination)[1] = ((const unsigned __int128*)source)[1];
    ((unsigned __int128*)destination)[2] = ((const unsigned __int128*)source)[2];
    ((unsigned __int128*)destination)[3] = ((const unsigned __int128*)source)[3];
}

/** @brief Track the velocity of the transform's position, scaled by one plus unk210, after the first update. */
void LibClass173B10::update()
{
    if (!started)
    {
        if (!matrix_ready)
        {
            update_transform_matrix();
        }

        started = 1;
        *(unsigned __int128*)&velocity = 0;
        lib_get_transform_translation(previous_position, *this);
        return;
    }

    if (!matrix_ready)
    {
        update_transform_matrix();
    }

    FieldVec4B position;
    lib_get_transform_translation(position, *this);
    float scale = 60.0f * (1.0f / g_frame_ticks) * (1.0f + unk210);
    velocity.x = scale * (position.x - previous_position.x);
    velocity.y = scale * (position.y - previous_position.y);
    velocity.z = scale * (position.z - previous_position.z);
    previous_position.set(position);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_slot88__14LibClass173B10Fv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_slot84__14LibClass173B10Fv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_slot88__14LibClass173C40Fv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_0043C570);

/**
 * @brief Keep the last update's unk260 and unk270 and the transform matrix, then track the velocity of the transform's
 * position, scaled by one plus unk210, after the first update.
 */
void LibClass173C40::update()
{
    unk290.set(unk270);
    unk280.set(unk260);

    if (!started)
    {
        if (!matrix_ready)
        {
            update_transform_matrix();
        }

        lib_copy_matrix(&previous_transform, &transform);
        unk221 = 0;
        started = 1;
        *(unsigned __int128*)&velocity = 0;
        lib_get_transform_translation(previous_position, *this);
        return;
    }

    lib_copy_matrix(&previous_transform, &transform);

    if (!matrix_ready)
    {
        update_transform_matrix();
    }

    FieldVec4B position;
    lib_get_transform_translation(position, *this);
    float scale = 60.0f * (1.0f / g_frame_ticks) * (1.0f + unk210);
    velocity.x = scale * (position.x - previous_position.x);
    velocity.y = scale * (position.y - previous_position.y);
    velocity.z = scale * (position.z - previous_position.z);
    previous_position.set(position);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_slot84__14LibClass173C40Fv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_0043CBF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_0043CCE0);

/** @brief Destroy the transform. */
LibClass173C40::~LibClass173C40()
{
}

/** @brief Destroy the grid. */
LibClass173CD0::~LibClass173CD0()
{
}

s32 func_0043D0B0(void* object)
{
    return 0;
}

s32 func_0043D0C0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_0043D0D0);

void func_0043D1F0(void* object, const void* source)
{
    FourQuadwordCopyTargetOwnertext_0043A920* receiver = (FourQuadwordCopyTargetOwnertext_0043A920*)object;
    const FourQuadwordCopySourceOwnertext_0043A920* values = (const FourQuadwordCopySourceOwnertext_0043A920*)source;
    receiver->unk2C = 0;
    receiver->values60[0] = values->values150[0];
    receiver->values60[1] = values->values150[1];
    receiver->values60[2] = values->values150[2];
    receiver->values60[3] = values->values150[3];
}

void func_0043D220(void* object)
{
}

s32 func_0043D230(void* object)
{
    return 1;
}

typedef struct MappedEntry0043D240
{
    u8 unk00[0x30];
} MappedEntry0043D240;

typedef struct MappedOwner0043D240
{
    u8 unk00[0x14];
    MappedEntry0043D240* entries;
} MappedOwner0043D240;

void* func_0043D240(const void* object, s32 index)
{
    const MappedOwner0043D240* owner = (const MappedOwner0043D240*)object;
    MappedEntry0043D240* item = &owner->entries[index];
    void* result = (void*)item;

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
extern "C" void func_0043D270(RowFillOwner* object, RowFillCell* cell, RowFillElement* row, s32 index, const RowFillVector* position_step, const RowFillVector* angle_pair,
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
            position.packed = cell->position().packed;
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
 * @brief Fill a row of secondary elements from a cell, or from an explicit vector.
 * @param object Grid owning the row.
 * @param cell Cell whose vectors are copied.
 * @param row First secondary element of the row.
 * @param index Unused.
 * @param source Vector copied to each element, or null to use the cell's position.
 */
void func_0043D670(LibGridEmitter* object, LibGridElement40* cell, LibGridRow40* row, s32 index, const LibGridVector4* source)
{
    if (object->secondary_emitter != 0)
    {
        cell->unk3C = object->unk3C;
    }

    bool blend = false;

    if (object->unk4D != 1 && object->unk4D != 3)
    {
        blend = true;
    }

    s32 count = object->columns - 1;

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
void func_0043D770(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    receiver->unk28 = value;
}

/**
 * @brief Store the value at receiver offset 0x30.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0043D780(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    receiver->unk30 = value;
}

/** Return the float member at receiver offset 0x30. */
float func_0043D790(void* object)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    return receiver->unk30;
}

/** Store the byte at receiver offset 0x4D. */
void func_0043D7A0(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = (ByteSetterOwnertext_0043A920*)object;
    receiver->unk4d = value;
}

/** Return the unsigned byte at receiver offset 0x4D. */
u8 func_0043D7B0(const void* object)
{
    const ByteGetterOwnertext_0043A920* receiver = (const ByteGetterOwnertext_0043A920*)object;
    return receiver->unk4d;
}

/**
 * @brief Store the value at receiver offset 0x34.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0043D7C0(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    receiver->unk34 = value;
}

/** Store the byte at receiver offset 0x56. */
void func_0043D7D0(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = (ByteSetterOwnertext_0043A920*)object;
    receiver->unk56 = value;
}

/** Return the unsigned byte at receiver offset 0x56. */
u8 func_0043D7E0(const void* object)
{
    const ByteGetterOwnertext_0043A920* receiver = (const ByteGetterOwnertext_0043A920*)object;
    return receiver->unk56;
}

/**
 * @brief Store the value at receiver offset 0x44.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0043D7F0(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    receiver->unk44 = value;
}

/** Return the float member at receiver offset 0x44. */
float func_0043D800(void* object)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    return receiver->unk44;
}

/** Return the float member at receiver offset 0x28. */
float func_0043D810(void* object)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    return receiver->unk28;
}

/** Store the word at receiver offset 0x48. */
void func_0043D820(void* object, u32 value)
{
    WordSetterOwnertext_0043A920* receiver = (WordSetterOwnertext_0043A920*)object;
    receiver->unk48 = value;
}

/** Return the word at receiver offset 0x48. */
u32 func_0043D830(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = (const WordGetterOwnertext_0043A920*)object;
    return receiver->unk48;
}

/** Store the byte at receiver offset 0x4F. */
void func_0043D840(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = (ByteSetterOwnertext_0043A920*)object;
    receiver->unk4f = value;
}

/** Store the byte at receiver offset 0x4E. */
void func_0043D850(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = (ByteSetterOwnertext_0043A920*)object;
    receiver->unk4e = value;
}

/** Store the word at receiver offset 0x50. */
void func_0043D860(void* object, u32 value)
{
    WordSetterOwnertext_0043A920* receiver = (WordSetterOwnertext_0043A920*)object;
    receiver->unk50 = value;
}

/** Return the word at receiver offset 0x50. */
u32 func_0043D870(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = (const WordGetterOwnertext_0043A920*)object;
    return receiver->unk50;
}

/** Store the byte at receiver offset 0x55. */
void func_0043D880(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = (ByteSetterOwnertext_0043A920*)object;
    receiver->unk55 = value;
}

/**
 * @brief Store the value at receiver offset 0x3C.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0043D890(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    receiver->unk3c = value;
}

/** Store the byte at receiver offset 0x54. */
void func_0043D8A0(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = (ByteSetterOwnertext_0043A920*)object;
    receiver->unk54 = value;
}

/**
 * @brief Store the value at receiver offset 0x40.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0043D8B0(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    receiver->unk40 = value;
}

void func_0043D8C0(void* object, const u8* source, u32 value)
{
    ByteSourceStateOwnertext_0043A920* receiver = (ByteSourceStateOwnertext_0043A920*)object;
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

void func_0043D900(void* object, s32 enabled)
{
    TwoWordClearArgStateOwnertext_0043A920* receiver = (TwoWordClearArgStateOwnertext_0043A920*)object;
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
void func_0043D930(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    receiver->unk38 = value;
}

void func_0043D940(void* object)
{
}

s32 func_0043D950(void* object)
{
    return 0;
}

void func_0043D960(void* object)
{
}

s32 func_0043D970(void* object)
{
    return 0;
}

void* func_0043D980(void* object, s32 index)
{
    SingleIndexTableAddressOwnertext_0043A920* receiver = (SingleIndexTableAddressOwnertext_0043A920*)object;
    return receiver->base14 + index * 48;
}

void* func_0043D9A0(void* object, s32 row, s32 column)
{
    TwoIndexTableAddressOwnertext_0043A920* receiver = (TwoIndexTableAddressOwnertext_0043A920*)object;
    return &receiver->entries[row * (receiver->count - 1) + column];
}

/** Return the word at receiver offset 0x1C. */
u32 func_0043D9C0(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = (const WordGetterOwnertext_0043A920*)object;
    return receiver->unk1c;
}

/** Return the word at receiver offset 0xC. */
u32 func_0043D9D0(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = (const WordGetterOwnertext_0043A920*)object;
    return receiver->unk0c;
}

/** Return the word at receiver offset 0x10. */
u32 func_0043D9E0(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = (const WordGetterOwnertext_0043A920*)object;
    return receiver->unk10;
}

/**
 * @brief Report a selected cell.
 * @return One.
 */
s32 LibClass173E70::func_slot3C()
{
    return 1;
}

s32 func_0043DA00(void* receiver)
{
    WordNonzeroOwnertext_0043A920* object = (WordNonzeroOwnertext_0043A920*)receiver;
    return object->unk14 != 0;
}

/**
 * @brief Reallocate the cells, the bit set and the secondary elements for a new size.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
void LibClass173E70::resize(s32 rows, s32 columns)
{
    unk14 = 0;
    unk20 = 0;
    delete[] unk18;
    unk18 = new (0) LibClass173F48[rows + 2];

    if (unk18 == 0)
    {
        return;
    }

    delete unk1c;

    if (g_field_allocation_heap != 0)
    {
        void* heap = resident_exchange_allocation_heap(g_field_allocation_heap);
        unk1c = new (0) LibGridBitset(rows);

        if (unk1c == 0)
        {
            delete[] unk18;
            unk18 = 0;
            resident_exchange_allocation_heap(heap);
            return;
        }

        if (unk1c->bits == 0)
        {
            delete[] unk18;
            unk18 = 0;
            delete unk1c;
            unk1c = 0;
            resident_exchange_allocation_heap(heap);
            return;
        }

        resident_exchange_allocation_heap(heap);
    }
    else
    {
        unk1c = new (0) LibGridBitset(rows);

        if (unk1c == 0)
        {
            delete[] unk18;
            unk18 = 0;
            return;
        }

        if (unk1c->bits == 0)
        {
            delete[] unk18;
            unk18 = 0;
            delete unk1c;
            unk1c = 0;
            return;
        }
    }

    if (columns > 1)
    {
        delete[] unk24;
        unk24 = new (0) LibClass173F38[rows * (columns - 1) + 2];

        if (unk24 == 0)
        {
            delete[] unk18;
            unk18 = 0;
            delete unk1c;
            unk1c = 0;
            return;
        }
    }
    else
    {
        delete[] unk24;
        unk24 = 0;
    }

    if (unk18 != 0)
    {
        unk14 = unk18 + 1;
    }

    if (unk24 != 0)
    {
        unk20 = unk24 + 1;
    }

    unk0c = rows;
    unk10 = columns;
    unk1c->clear();
}

/** @brief Construct the element. */
LibClass173F38::LibClass173F38()
{
}

/** @brief Destroy the element. */
LibClass173F38::~LibClass173F38()
{
}

/** @brief Release the cells, the bit set and the secondary elements. */
LibClass173E70::~LibClass173E70()
{
    delete[] unk18;
    delete unk1c;
    delete[] unk24;
}

/**
 * @brief Copy another grid's size and emission settings.
 * @param source Grid to copy.
 */
void LibClass173DA0::copy_settings(const LibClass173A40* source)
{
    const LibClass173DA0* other = static_cast<const LibClass173DA0*>(source);

    unk0c = other->unk0c;
    unk10 = other->unk10;
    resize(unk0c, unk10);
    unk28 = other->unk28;
    unk30 = other->unk30;
    unk34 = other->unk34;
    unk38 = other->unk38;
    unk48 = other->unk48;
    unk4c = other->unk4c;
    unk4d = other->unk4d;
    unk4e = other->unk4e;
    unk4f = other->unk4f;
    unk50 = other->unk50;
    unk54 = other->unk54;
    unk55 = other->unk55;
    unk3c = other->unk3c;
    unka0 = other->unka0;
    unka4 = other->unka4;
}

/**
 * @brief Advance active cells' frame vectors and playback state into an output batch.
 * @param object Grid owning the cells and frame resource.
 * @param capacity Output-entry budget, counted in steps of the grid column count.
 * @param output Output records, with each cell written at the start of its row.
 * @param preserve_row_vector Nonzero to retain the saved xyz components in the first row element.
 */
extern "C" void func_0043E2F0(GridOwner0043E2F0* object, s32 capacity, GridOutputRecord* output, s32 preserve_row_vector)
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

                state = grid_cell_motion_0043E2F0(&object->unk14[index]);
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

                state = grid_cell_motion_0043E2F0(&object->unk14[index]);
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

                state = grid_cell_motion_0043E2F0(&object->unk14[index]);
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

                state = grid_cell_motion_0043E2F0(&object->unk14[index]);
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
 * @brief Copy selected group histories and extend the caller's VU0 bounds.
 * @param object Receiver containing selection masks, source records, and histories.
 * @param capacity Output-record count at which processing stops before the next group.
 * @param output Destination array of three-vector records.
 * @param stamp Nonzero to copy the receiver's raw word at 0x28 into control records.
 */
extern "C" void func_0043EA10(LibHistoryReceiver43EA10* object, s32 capacity, LibHistoryOutput30* output, u32 stamp)
{
    s32 samples = object->samples;
    s32 index = object->index;
    s32 limit = object->limit;
    const u64* masks = object->mask->bits;
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
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }

                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource30* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
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
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }

                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource30* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
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
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }

                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource30* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
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
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }

                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource30* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
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
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }

                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource30* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
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
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }

                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource30* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
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
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }

                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource30* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
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
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }

                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource30* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
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
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }

                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource30* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
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
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }

                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource30* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
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
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }

                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource30* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
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
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }

                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource30* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
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
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }

                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource30* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
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
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }

                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource30* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
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
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }

                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource30* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
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
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }

                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource30* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
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
                            LibHistorySource30* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;

                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }

                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
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
                            LibHistorySource30* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;

                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }

                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
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
                            LibHistorySource30* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;

                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }

                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
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
                            LibHistorySource30* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;

                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }

                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
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
                            LibHistorySource30* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;

                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }

                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
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
                            LibHistorySource30* source = &object->source[index - 1];
                            s32 history_index = index * (samples - 1) - 1;
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;

                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }

                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
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
                            LibHistorySource30* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;

                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }

                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
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
                            LibHistorySource30* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;

                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }

                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
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
 * @brief Copy another grid's size and resize this grid to match.
 * @param source Grid to copy.
 */
void LibClass173E70::copy_settings(const LibClass173A40* source)
{
    unk0c = source->unk0c;
    unk10 = source->unk10;
    resize(unk0c, unk10);
}

float func_00441520(void* object)
{
    return 1.0f;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_00441530);

LibClass173F80::~LibClass173F80()
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_00441660);

/**
 * @brief Clear the cell word at offset 0x1C, then reset the cell through func_00441C10.
 * @param object Grid.
 * @param state Cell.
 * @param row Row passed on.
 */
void func_00441B30(void* object, u8* state, void* row)
{
    *(s32*)(state + 0x1C) = 0;
    func_00441C10(object, state, row);
}

/**
 * @brief Clear the cell word at offset 0x1C, then pass everything on to func_00441BE0.
 * @param object Grid.
 * @param cell Cell.
 * @param row Row passed on.
 * @param index Index passed on.
 * @param extra4 Passed on.
 * @param extra5 Passed on.
 * @param extra6 Passed on.
 * @param extra7 Passed on.
 * @param extra8 Passed on.
 */
void func_00441B50(void* object, void* cell, void* row, s32 index, void* extra4, void* extra5, void* extra6, void* extra7,
                   void* extra8)
{
    *(s32*)((u8*)cell + 0x1C) = 0;
    func_00441BE0(object, cell, row, index, extra4, extra5, extra6, extra7, extra8);
}

void func_00441B80(void* object)
{
}

s32 func_00441B90(void* object)
{
    return 1;
}

/** Store the word at receiver offset 0xB8. */
void func_00441BA0(void* object, u32 value)
{
    WordSetterOwnertext_0043A920* receiver = (WordSetterOwnertext_0043A920*)object;
    receiver->unkb8 = value;
}

/** Return the word at receiver offset 0xB8. */
u32 func_00441BB0(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = (const WordGetterOwnertext_0043A920*)object;
    return receiver->unkb8;
}

/** Store the word at receiver offset 0xBC. */
void func_00441BC0(void* object, u32 value)
{
    WordSetterOwnertext_0043A920* receiver = (WordSetterOwnertext_0043A920*)object;
    receiver->unkbc = value;
}

/** Return the word at receiver offset 0xBC. */
u32 func_00441BD0(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = (const WordGetterOwnertext_0043A920*)object;
    return receiver->unkbc;
}

void func_00441BE0(void* object, void* cell, void* row, s32 index, void* extra4, void* extra5, void* extra6, void* extra7, void* extra8)
{
    u8* state = (u8*)cell;
    state[0x130] = 0;
    state[0x132] = 0;
    state[0x131] = 0;
    state[0x133] = 0;
    func_004447E0(object, cell, row, index, extra4, extra5, extra6, extra7, extra8);
}

}
