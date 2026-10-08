#include "include_asm.h"
#include "overlays/1067-00/text_00293610.h"
#include "overlays/1067-00/text_0029E9E0.h"
#include "overlays/lib/text_0044ABE0.h"
#include "overlays/lib/text_0046AE20.h"

extern "C" float D_001B6688;
extern "C" u8 D_001B6448;
extern "C" float D_001B6690;
extern "C" void func_428670(void* object);
extern "C" void func_426C20(void* object);
extern "C" u8 func_452870(void* object, void* context);

/**
 * @brief Advance a nonnegative countdown and report whether it has expired.
 * @param delay Countdown to update; negative values remain disabled.
 * @return True once the countdown reaches zero.
 */
static inline bool update_delay(float& delay)
{
    if (delay < 0.0f)
    {
        return false;
    }
    if (delay > 0.0f)
    {
        delay -= D_001B6688;
        if (delay > 0.0f)
        {
            return false;
        }
        delay = 0.0f;
    }
    return true;
}

// Deleting destructor; needs the recovered class hierarchy.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00293610);

// Base destructor; needs the recovered class hierarchy.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_002936D0);

s32 func_00293740(FieldClass157400* object)
{
    return 5;
}

void func_00293750(FieldClass157400* object)
{
    float previous = object->delay;
    if (update_delay(object->delay))
    {
        if (previous > 0.0f)
        {
            func_428670(object);
        }
        func_426C20(object);
    }
}

u8 func_002937F0(FieldClass1587E8* object, void* context)
{
    float previous = D_001B6690;
    u8 result;
    if (D_001B6448)
    {
        D_001B6690 = 1.0f / 60.0f;
    }
    result = func_452870(object, context);
    D_001B6690 = previous;
    return result;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00293840);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00293A40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00294C30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00294F20);

extern "C" FieldScalarPair293610* func_00294FD0(FieldScalarPair293610* object)
{
    object->unk00 = 5.0f;
    object->unk04 = -1;
    return object;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00294FF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295090);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295100);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295180);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_002951F0);

FieldClass157540::~FieldClass157540()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_002952E0);

/**
 * @brief Resize the grid with the default heap selected.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
extern "C" void func_00295340(FieldClass157540* object, s32 rows, s32 columns)
{
    void* heap = func_00100C80(0);
    func_002A78C0(object, rows, columns);
    func_00100C80(heap);
}

FieldClass157610::~FieldClass157610()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295440);

/**
 * @brief Resize the grid with the default heap selected.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
extern "C" void func_002954A0(FieldClass157610* object, s32 rows, s32 columns)
{
    void* heap = func_00100C80(0);
    func_002A6910(object, rows, columns);
    func_00100C80(heap);
}

FieldClass157880::~FieldClass157880()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_002955A0);

/**
 * @brief Resize the grid with the default heap selected.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
extern "C" void func_00295600(FieldClass157880* object, s32 rows, s32 columns)
{
    void* heap = func_00100C80(0);
    func_002A70D0(object, rows, columns);
    func_00100C80(heap);
}

FieldClass157BC0::~FieldClass157BC0()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295700);

/**
 * @brief Resize the grid with the default heap selected.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
extern "C" void func_00295760(FieldClass157BC0* object, s32 rows, s32 columns)
{
    void* heap = func_00100C80(0);
    func_002A6910(object, rows, columns);
    func_00100C80(heap);
}

FieldClass157F00::~FieldClass157F00()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295860);

/**
 * @brief Resize the grid with the default heap selected.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
extern "C" void func_002958C0(FieldClass157F00* object, s32 rows, s32 columns)
{
    void* heap = func_00100C80(0);
    func_002A6170(object, rows, columns);
    func_00100C80(heap);
}

FieldClass158240::~FieldClass158240()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_002959C0);

/**
 * @brief Resize the grid with the default heap selected.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
extern "C" void func_00295A20(FieldClass158240* object, s32 rows, s32 columns)
{
    void* heap = func_00100C80(0);
    func_002A5A70(object, rows, columns);
    func_00100C80(heap);
}

bool func_00295A90(FieldObject158240* object)
{
    return *object->unkA0 != 1;
}

FieldClass1584B0::~FieldClass1584B0()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295B40);

/**
 * @brief Resize the grid with the default heap selected.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
extern "C" void func_00295BA0(FieldClass1584B0* object, s32 rows, s32 columns)
{
    void* heap = func_00100C80(0);
    func_002A5A70(object, rows, columns);
    func_00100C80(heap);
}

bool func_00295C10(FieldObject1584B0* object)
{
    return *object->unkA0 != 1;
}

/** Partial LibClass174C20 with vtable D_158800 in main data. */
class FieldClass158800 : public LibClass174C20
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass158800();
};

FieldClass158800::~FieldClass158800()
{
}

s32 func_00295C90(void* object)
{
    return 35;
}

/** Partial LibClass175320 with vtable D_158820 in main data. */
class FieldClass158820 : public LibClass175320
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass158820();
};

FieldClass158820::~FieldClass158820()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295D00);

extern "C" void func_00295D30(FieldVectorBuffer293610* object, u8 value, const FieldVector4* vector)
{
    if (object->unkC4 < object->unkC0)
    {
        object->unkB0[object->unkC4] = value;
        if (vector != 0)
        {
            object->unkB4[object->unkC4].packed = vector->packed;
        }
        object->unkC4++;
    }
}

void func_00295D90(FieldVectorBuffer293610* object)
{
}

bool func_00295DA0(FieldVectorBuffer293610* object)
{
    return true;
}

void func_00295DB0(FieldVectorBuffer293610* object, FieldObject175360* value)
{
    object->unkB8 = value;
}

FieldObject175360* func_00295DC0(FieldVectorBuffer293610* object)
{
    return object->unkB8;
}

void func_00295DD0(FieldVectorBuffer293610* object, FieldObject175370* value)
{
    object->unkBC = value;
}

FieldObject175370* func_00295DE0(FieldVectorBuffer293610* object)
{
    return object->unkBC;
}

void func_00295DF0(FieldObject1577B0Links* object, FieldObject175360* value)
{
    object->unkB0 = value;
}

FieldObject175360* func_00295E00(FieldObject1577B0Links* object)
{
    return object->unkB0;
}

void func_00295E10(FieldObject1577B0Links* object, FieldObject175370* value)
{
    object->unkB4 = value;
}

FieldObject175370* func_00295E20(FieldObject1577B0Links* object)
{
    return object->unkB4;
}

bool func_00295E30(FieldObject1583E0* object)
{
    return false;
}

bool func_00295E40(FieldObject158650* object)
{
    return false;
}

// Vector dispatcher; runtime layouts and vector-unit operations remain unresolved.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295E50);

/** Leading 0x140 bytes of a FieldElement2989C0. */
struct FieldElementHead2989C0
{
    u8 unk00[0x140];
};

/** Part at offset 0x140 of a FieldElement2989C0. */
struct FieldElementPart2989C0
{
    u8 unk00[0x30];
};

/** Partial 0x170-byte element whose second base starts at offset 0x140. */
struct FieldElement2989C0 : public FieldElementHead2989C0, public FieldElementPart2989C0
{
};

/** Partial owner of an element array at offset 0x14. */
struct FieldOwner2989C0
{
    u8 unk00[0x14];
    FieldElement2989C0* unk14;
};

/**
 * @brief Return an element's part at offset 0x140.
 * @param object Owner of the elements.
 * @param index Element index.
 * @return The element's part, or null when the element pointer is null.
 */
extern "C" FieldElementPart2989C0* func_002989C0(const FieldOwner2989C0* object, s32 index)
{
    return &object->unk14[index];
}

void func_002989F0(FieldObject158860* object, float value)
{
    object->unk28 = value;
}

void func_00298A00(FieldObject158860* object, float value)
{
    object->unk30 = value;
}

float func_00298A10(FieldObject158860* object)
{
    return object->unk30;
}

void func_00298A20(FieldObject158860* object, u8 value)
{
    object->unk4D = value;
}

u8 func_00298A30(FieldObject158860* object)
{
    return object->unk4D;
}

void func_00298A40(FieldObject158860* object, float value)
{
    object->unk34 = value;
}

void func_00298A50(FieldObject158860* object, u8 value)
{
    object->unk56 = value;
}

u8 func_00298A60(FieldObject158860* object)
{
    return object->unk56;
}

void func_00298A70(FieldObject158860* object, float value)
{
    object->unk44 = value;
}

float func_00298A80(FieldObject158860* object)
{
    return object->unk44;
}

float func_00298A90(FieldObject158860* object)
{
    return object->unk28;
}

void func_00298AA0(FieldObject158860* object, FieldObject158860Link48* value)
{
    object->unk48 = value;
}

FieldObject158860Link48* func_00298AB0(FieldObject158860* object)
{
    return object->unk48;
}

void func_00298AC0(FieldObject158860* object, u8 value)
{
    object->unk4F = value;
}

void func_00298AD0(FieldObject158860* object, u8 value)
{
    object->unk4E = value;
}

void func_00298AE0(FieldObject158860* object, FieldObject158860Link50* value)
{
    object->unk50 = value;
}

FieldObject158860Link50* func_00298AF0(FieldObject158860* object)
{
    return object->unk50;
}

void func_00298B00(FieldObject158860* object, u8 value)
{
    object->unk55 = value;
}

void func_00298B10(FieldObject158860* object, float value)
{
    object->unk3C = value;
}

void func_00298B20(FieldObject158860* object, u8 value)
{
    object->unk54 = value;
}

void func_00298B30(FieldObject158860* object, float value)
{
    object->unk40 = value;
}

void func_00298B40(FieldObject158860* object, u8* header, FieldResourceRecord273720* records)
{
    object->unkA0 = header;
    object->unkA4 = records;
    if (*object->unkA0 == 1)
    {
        object->unk57 = 1;
    }
    else
    {
        object->unk57 = 0;
    }
}

void func_00298B80(FieldObject158860* object, s32 enabled)
{
    object->unkA0 = 0;
    object->unkA4 = 0;
    if (enabled)
    {
        object->unk57 = 1;
    }
    else
    {
        object->unk57 = 0;
    }
}

void func_00298BB0(FieldObject158860* object, float value)
{
    object->unk38 = value;
}

void func_00298BC0(FieldObject157AF0* object, const FieldVectorSource150* source)
{
    object->unk2C = 0;
    object->unk60 = source->unk150;
    object->unk70 = source->unk160;
    object->unk80 = source->unk170;
    object->unk90 = source->unk180;
}

void func_00298BF0(FieldObject157AF0* object)
{
}

// Vector dispatcher; runtime layouts and vector-unit operations remain unresolved.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00298C00);

bool func_0029B6D0(FieldObject157AF0* object)
{
    return true;
}

void* func_0029B6E0(FieldClass158D00* object, s32 index)
{
    FieldClass158A18* item = &object->unk14[index];
    void* result = item;
    if (item != 0)
    {
        result = &item->unkF0;
    }
    return result;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_0029B710);

/**
 * @brief Fill a row of secondary elements from a cell (or an explicit vector).
 * @param object Grid owning the row.
 * @param cell Cell whose vectors are copied.
 * @param row First secondary element of the row.
 * @param index Unused.
 * @param source Vector copied to each element, or null to use the cell's.
 */
extern "C" void func_0029BB20(FieldClass157AF0* object, FieldClass158A18* cell, FieldClass154E60* row, s32 index, const FieldVector4* source)
{
    if (object->unk50 != 0)
    {
        cell->unk3C = object->unk3C;
    }
    bool blend = false;
    if (object->unk4D != 1 && object->unk4D != 3)
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

void func_0029BC20(FieldObject157AF0* object, float value)
{
    object->unk28 = value;
}

void func_0029BC30(FieldObject157AF0* object, float value)
{
    object->unk30 = value;
}

float func_0029BC40(const FieldObject157AF0* object)
{
    return object->unk30;
}

void func_0029BC50(FieldObject157AF0* object, u8 value)
{
    object->unk4D = value;
}

u8 func_0029BC60(const FieldObject157AF0* object)
{
    return object->unk4D;
}

void func_0029BC70(FieldObject157AF0* object, float value)
{
    object->unk34 = value;
}

void func_0029BC80(FieldObject157AF0* object, u8 value)
{
    object->unk56 = value;
}

u8 func_0029BC90(const FieldObject157AF0* object)
{
    return object->unk56;
}

void func_0029BCA0(FieldObject157AF0* object, float value)
{
    object->unk44 = value;
}

float func_0029BCB0(const FieldObject157AF0* object)
{
    return object->unk44;
}

float func_0029BCC0(const FieldObject157AF0* object)
{
    return object->unk28;
}

void func_0029BCD0(FieldObject157AF0* object, FieldLinkedObject157AF0* value)
{
    object->unk48 = value;
}

FieldLinkedObject157AF0* func_0029BCE0(const FieldObject157AF0* object)
{
    return object->unk48;
}

void func_0029BCF0(FieldObject157AF0* object, u8 value)
{
    object->unk4F = value;
}

void func_0029BD00(FieldObject157AF0* object, u8 value)
{
    object->unk4E = value;
}

void func_0029BD10(FieldObject157AF0* object, FieldLinkedObject157AF0* value)
{
    object->unk50 = value;
}

FieldLinkedObject157AF0* func_0029BD20(const FieldObject157AF0* object)
{
    return object->unk50;
}

void func_0029BD30(FieldObject157AF0* object, u8 value)
{
    object->unk55 = value;
}

void func_0029BD40(FieldObject157AF0* object, float value)
{
    object->unk3C = value;
}

void func_0029BD50(FieldObject157AF0* object, u8 value)
{
    object->unk54 = value;
}

void func_0029BD60(FieldObject157AF0* object, float value)
{
    object->unk40 = value;
}

void func_0029BD70(FieldObject157AF0* object, u8* header, FieldResourceRecord273720* records)
{
    object->unkA0 = header;
    object->unkA4 = records;
    if (*object->unkA0 == 1)
    {
        object->unk57 = 1;
    }
    else
    {
        object->unk57 = 0;
    }
}

void func_0029BDB0(FieldObject157AF0* object, s32 enabled)
{
    object->unkA0 = 0;
    object->unkA4 = 0;
    if (enabled)
    {
        object->unk57 = 1;
    }
    else
    {
        object->unk57 = 0;
    }
}

void func_0029BDE0(FieldObject157AF0* object, float value)
{
    object->unk38 = value;
}

void func_0029BDF0(FieldObject157AF0* object, FieldObject175360* value)
{
}

FieldObject175360* func_0029BE00(FieldObject157AF0* object)
{
    return 0;
}

void func_0029BE10(FieldObject157AF0* object, FieldObject175370* value)
{
}

FieldObject175370* func_0029BE20(FieldObject157AF0* object)
{
    return 0;
}

void func_0029BE30(FieldObject157BC0* object, const FieldVectorSource150* source)
{
    object->unk2C = 0;
    object->unk60 = source->unk150;
    object->unk70 = source->unk160;
    object->unk80 = source->unk170;
    object->unk90 = source->unk180;
}

void func_0029BE60(void* object)
{
}

// Vector dispatcher; runtime layouts and vector-unit operations remain unresolved.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_0029BE70);
