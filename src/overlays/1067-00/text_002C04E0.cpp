#include "include_asm.h"
#include "overlays/1067-00/field_class_154D40.h"
#include "overlays/1067-00/field_class_154EF0.h"
#include "overlays/1067-00/text_002C04E0.h"
#include "main/resident_data.h"
#include "main/resident_0010A0E0.h"

/** Partial receiver with a float at offset 0x48. */
struct FieldFloat48
{
    u8 pad[0x48];
    float value;
};

extern "C" float D_001B6688;

struct FieldTable14
{
    u8 pad[0x14];
    u8* entries;
};

struct FieldGrid20
{
    u8 pad[0x10];
    u32 rows;
    u8 pad14[0xC];
    u8* entries;
};

struct FieldWord1C
{
    u8 pad[0x1C];
    u32 value;
};

struct FieldWord0C
{
    u8 pad[0xC];
    u32 value;
};

struct FieldWord10
{
    u8 pad[0x10];
    u32 value;
};

struct FieldWord14
{
    u8 pad[0x14];
    u32 value;
};

struct FieldFlags1C
{
    u8 pad[0x1C];
    u32 flags;
};

struct FieldByteCB
{
    u8 pad[0xCB];
    u8 value;
};

struct FieldBytePtr10
{
    u8 pad[0x10];
    FieldByteCB* target;
};

struct FieldBitFlags1C
{
    u8 pad[0x1C];
    u8 active : 1;
    u8 reserved : 7;
};

struct FieldInputBlock
{
    u8 pad[0x2C];
    const u8* data;
    s32 count;
    u8 unk34;
};

struct FieldEntry90
{
    u8 data[0x90];
};

struct FieldCollection90
{
    u8 pad[0x14];
    FieldEntry90* entries;
};

struct FieldCell40
{
    u8 data[0x40];
};

struct FieldGrid40
{
    u8 pad[0x10];
    s32 width;
    u8 pad14[0xC];
    FieldCell40* cells;
};

struct FieldSignedWord1C
{
    u8 pad[0x1C];
    s32 value;
};

struct FieldSignedWord0C
{
    u8 pad[0xC];
    s32 value;
};

struct FieldSignedWord10
{
    u8 pad[0x10];
    s32 value;
};

struct FieldPointer14
{
    u8 pad[0x14];
    void* value;
};

struct FieldState100
{
    u8 pad[0x3B];
    u8 unk3b;
    u8 pad3c[0x34];
    s32 unk70;
    u8 pad74[0x44];
    s32 unkB8;
    u8 padBC[0x44];
    s32 unk100;
};

struct FieldFloat2C
{
    u8 pad[0x2C];
    float value;
};

struct FieldEntry50
{
    u8 data[0x50];
};

struct FieldCollection50
{
    u8 pad[0x14];
    FieldEntry50* entries;
};
extern "C" void func_113EA0();
extern "C" void func_4C74E0(FieldState100* state);
extern "C" void func_462320(FieldState100* state, s32, s32);

struct FieldWord28
{
    u8 pad[0x28];
    u32 value;
};

struct FieldInputState
{
    u8 pad[0x2C];
    u8* input;
    u32 unk30;
    u8 mode;
};

struct FieldCollection
{
    u8 pad00[0xC];
    s32 unk0C;
    s32 unk10;
    char* unk14;
    u8 pad18[4];
    s32 unk1C;
    char* unk20;
};

struct FieldThing
{
    u8 pad00[0x45];
    s8 unk45;
};

struct FieldPair
{
    u8 pad00[0x40];
    FieldThing* first;
    FieldThing* second;
    u8 pad48[5];
    u8 flag0 : 1;
    u8 flag1 : 1;
    u8 flag2 : 1;
    u8 flag3 : 1;
    u8 flag4 : 1;
    u8 flag5 : 1;
    u8 flag6 : 1;
    u8 flag7 : 1;
};

struct FieldMotion
{
    u8 pad00[0x28];
    s32 unk28;
    u8 pad2C[4];
    float unk30;
    u8 pad34[8];
    s16 unk3C;
    s16 unk3E;
    u8 unk40;
    u8 unk41;
    u8 pad42[4];
    u8 unk46;
    u8 flag0 : 1;
    u8 flag1 : 1;
    u8 flag2 : 1;
    u8 flag3 : 1;
    u8 flag4 : 1;
    u8 flag5 : 1;
    u8 flag6 : 1;
    u8 flag7 : 1;
};

struct FieldNode
{
    u8 pad00[8];
    FieldNode* next;
    u8 pad0C[0x10];
    u32 flags;
    u8 pad20[0x44];
    u8 unk64;
};

struct FieldList
{
    u8 pad00[0x20];
    FieldNode sentinel;
    u8 pad88[0x9E];
    u8 unk126;
};

struct FieldState28
{
    u8 pad00[0x28];
    s32 unk28;
};

struct FieldSelector
{
    u8 pad00[0x2C];
    const u8* unk2C;
    void* unk30;
    u8 unk34;
};
extern "C" s8 D_30EAFC[];

FieldClass15A040::~FieldClass15A040()
{
}

extern "C" int func_002C0550(void* object)
{
    return 3;
}

extern "C" void func_002C0560(FieldWord28* self)
{
    self->value = 0;
}

extern "C" float func_002C0570(const FieldFloat2C* self)
{
    return self->value;
}

extern "C" int func_002C0580(void* object)
{
    return 1;
}

extern "C" FieldCell40* func_002C0590(FieldGrid40* self, s32 row, s32 column)
{
    return &self->cells[row * (self->width - 1) + column];
}

extern "C" FieldEntry50* func_002C05B0(FieldCollection50* self, s32 index)
{
    return &self->entries[index];
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C05D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C0AF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C0D90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C1190);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C1230);

/** Partial FieldClass154E20 object with vtable D_15A1E0 in main data. */
class FieldClass15A1E0 : public FieldClass154E20
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass15A1E0();
    /** @brief Create the grid for this object. */
    virtual void func_slot30();
};

FieldClass15A1E0::~FieldClass15A1E0()
{
}

extern "C" void func_002C1370(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_slot30__16FieldClass15A1E0Fv);

extern "C" int func_002C1580(void* object)
{
    return 0;
}

extern "C" void func_002C1590(void* object)
{
}

extern "C" float func_002C15A0(void* object)
{
    return 100.0f;
}

extern "C" void func_002C15B0(void* object)
{
}

extern "C" void func_002C15C0(void* object)
{
}

extern "C" void func_002C15D0(void* object)
{
}

extern "C" void func_002C15E0(void* object)
{
}

extern "C" void func_002C15F0(void* object)
{
}

extern "C" void func_002C1600(void* object)
{
}

extern "C" int func_002C1610(void* object)
{
    return 0;
}

extern "C" void func_002C1620(void* object)
{
}

extern "C" void func_002C1630(void* object)
{
}

extern "C" void func_002C1640(void* object)
{
}

extern "C" int func_002C1650(void* object)
{
    return 0;
}

extern "C" void func_002C1660(void* object)
{
}

extern "C" void func_002C1670(void* object)
{
}

extern "C" void func_002C1680(void* object)
{
}

extern "C" void func_002C1690(void* object)
{
}

extern "C" void func_002C16A0(void* object)
{
}

extern "C" int func_002C16B0(void* object)
{
    return 0;
}

extern "C" void func_002C16C0(void* object)
{
}

extern "C" int func_002C16D0(void* object)
{
    return 0;
}

extern "C" void func_002C16E0(void* object)
{
}

extern "C" float func_002C16F0(void* object)
{
    return 0.0f;
}

extern "C" void func_002C1700(void* object)
{
}

extern "C" void func_002C1710(void* object)
{
}

extern "C" int func_002C1720(void* object)
{
    return 0;
}

extern "C" void func_002C1730(void* object)
{
}

extern "C" int func_002C1740(void* object)
{
    return 0;
}

extern "C" void func_002C1750(void* object)
{
}

extern "C" float func_002C1760(void* object)
{
    return 0.0f;
}

extern "C" void func_002C1770(void* object)
{
}

FieldClass15A230::FieldClass15A230()
{
    unk04 = 0;
    unk14 = 0;
    unk18 = 0;
    unk1C = 0;
    unk20 = 0;
    unk24 = 0;
}

extern "C" u32 func_002C17E0(const FieldWord1C* object)
{
    return object->value;
}

extern "C" u32 func_002C17F0(const FieldWord0C* object)
{
    return object->value;
}

extern "C" u32 func_002C1800(const FieldWord10* object)
{
    return object->value;
}

extern "C" int func_002C1810(void* object)
{
    return 1;
}

extern "C" bool func_002C1820(const FieldWord14* object)
{
    return object->value != 0;
}

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
extern "C" void func_002C1830(FieldClass15A230* object, const FieldClass15A230* other)
{
    object->unk0C = other->unk0C;
    object->unk10 = other->unk10;
    object->resize(object->unk0C, object->unk10);
}

/**
 * @brief Reallocate the cells, the bit set and the secondary elements for a new size.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
extern "C" void func_002C1870(FieldClass15A230* object, s32 rows, s32 columns)
{
    object->unk14 = 0;
    object->unk20 = 0;
    delete[] object->unk18;
    object->unk18 = new (0) FieldClass15A220[rows + 2];
    if (object->unk18 == 0)
    {
        return;
    }
    delete object->unk1C;
    if (D_001B6684 != 0)
    {
        void* heap = func_00100C80(D_001B6684);
        object->unk1C = new (0) FieldBitset154E80(rows);
        if (object->unk1C == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            func_00100C80(heap);
            return;
        }
        if (object->unk1C->unk08 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            func_00100C80(heap);
            return;
        }
        func_00100C80(heap);
    }
    else
    {
        object->unk1C = new (0) FieldBitset154E80(rows);
        if (object->unk1C == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            return;
        }
        if (object->unk1C->unk08 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            return;
        }
    }
    if (columns > 1)
    {
        delete[] object->unk24;
        object->unk24 = new (0) FieldClass154E60[rows * (columns - 1) + 2];
        if (object->unk24 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            return;
        }
    }
    else
    {
        delete[] object->unk24;
        object->unk24 = 0;
    }
    if (object->unk18 != 0)
    {
        object->unk14 = (u8*)(object->unk18 + 1);
    }
    if (object->unk24 != 0)
    {
        object->unk20 = (u8*)(object->unk24 + 1);
    }
    object->unk0C = rows;
    object->unk10 = columns;
    object->unk1C->clear();
}

FieldClass15A220::FieldClass15A220()
{
}

FieldClass15A220::~FieldClass15A220()
{
}

FieldClass15A230::~FieldClass15A230()
{
    delete[] unk18;
    delete unk1C;
    delete[] unk24;
}

extern "C" float func_002C1F70(void* object)
{
    return 1.0f;
}

FieldClass15A300::~FieldClass15A300()
{
}

extern "C" int func_002C2000(void* object)
{
    return 3;
}

extern "C" void func_002C2010(FieldWord28* object)
{
    object->value = 0;
}

extern "C" float func_002C2020(void* object)
{
    return 2500.0f;
}

extern "C" int func_002C2040(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C2050);

extern "C" void func_002C2240(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C2250);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C2690);

/** Partial FieldClass154E20 object with vtable D_15A570 in main data. */
class FieldClass15A570 : public FieldClass154E20
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass15A570();
    /** @brief Create the grid for this object. */
    virtual void func_slot30();
};

FieldClass15A570::~FieldClass15A570()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_slot30__16FieldClass15A570Fv);

extern "C" void func_002C29D0(FieldInputState* state, u8* input, u32 unk30)
{
    state->input = input;
    state->unk30 = unk30;
    if (state->input[0] == 1)
    {
        state->mode = 1;
    }
    else
    {
        state->mode = 0;
    }
}

extern "C" int func_002C2A10(void* object)
{
    return 0;
}

extern "C" void func_002C2A20(void* object)
{
}

extern "C" float func_002C2A30(void* object)
{
    return 100.0f;
}

extern "C" void func_002C2A40(void* object)
{
}

extern "C" void func_002C2A50(void* object)
{
}

extern "C" void func_002C2A60(void* object)
{
}

extern "C" void func_002C2A70(void* object)
{
}

extern "C" void func_002C2A80(void* object)
{
}

extern "C" void func_002C2A90(void* object)
{
}

extern "C" int func_002C2AA0(void* object)
{
    return 0;
}

extern "C" void func_002C2AB0(void* object)
{
}

extern "C" void func_002C2AC0(void* object)
{
}

extern "C" void func_002C2AD0(void* object)
{
}

extern "C" int func_002C2AE0(void* object)
{
    return 0;
}

extern "C" void func_002C2AF0(void* object)
{
}

extern "C" void func_002C2B00(void* object)
{
}

extern "C" void func_002C2B10(void* object)
{
}

extern "C" void func_002C2B20(void* object)
{
}

extern "C" void func_002C2B30(void* object)
{
}

extern "C" int func_002C2B40(void* object)
{
    return 0;
}

extern "C" void func_002C2B50(void* object)
{
}

extern "C" int func_002C2B60(void* object)
{
    return 0;
}

extern "C" void func_002C2B70(void* object)
{
}

extern "C" float func_002C2B80(void* object)
{
    return 0.0f;
}

extern "C" void func_002C2B90(void* object)
{
}

extern "C" void func_002C2BA0(void* object)
{
}

extern "C" int func_002C2BB0(void* object)
{
    return 0;
}

extern "C" void func_002C2BC0(void* object)
{
}

extern "C" int func_002C2BD0(void* object)
{
    return 0;
}

extern "C" void func_002C2BE0(void* object)
{
}

extern "C" float func_002C2BF0(void* object)
{
    return 0.0f;
}

extern "C" void func_002C2C00(void* object)
{
}

FieldClass15A5C0::FieldClass15A5C0()
{
    unk04 = 0;
    unk14 = 0;
    unk18 = 0;
    unk1C = 0;
    unk20 = 0;
    unk24 = 0;
}

extern "C" char* func_002C2C70(FieldCollection* object, s32 index)
{
    return object->unk14 + index * 160;
}

extern "C" char* func_002C2C90(FieldCollection* object, s32 row, s32 column)
{
    return object->unk20 + (column + row * (object->unk10 - 1)) * 64;
}

extern "C" s32 func_002C2CB0(FieldCollection* object)
{
    return object->unk1C;
}

extern "C" s32 func_002C2CC0(FieldCollection* object)
{
    return object->unk0C;
}

extern "C" s32 func_002C2CD0(FieldCollection* object)
{
    return object->unk10;
}

extern "C" int func_002C2CE0(void* object)
{
    return 32;
}

extern "C" bool func_002C2CF0(FieldCollection* object)
{
    return object->unk14 != 0;
}

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
extern "C" void func_002C2D00(FieldClass15A5C0* object, const FieldClass15A5C0* other)
{
    object->unk0C = other->unk0C;
    object->unk10 = other->unk10;
    object->resize(object->unk0C, object->unk10);
}

/**
 * @brief Reallocate the cells, the bit set and the secondary elements for a new size.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
extern "C" void func_002C2D40(FieldClass15A5C0* object, s32 rows, s32 columns)
{
    object->unk14 = 0;
    object->unk20 = 0;
    delete[] object->unk18;
    object->unk18 = new (0) FieldClass15A5B0[rows + 2];
    if (object->unk18 == 0)
    {
        return;
    }
    delete object->unk1C;
    if (D_001B6684 != 0)
    {
        void* heap = func_00100C80(D_001B6684);
        object->unk1C = new (0) FieldBitset154E80(rows);
        if (object->unk1C == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            func_00100C80(heap);
            return;
        }
        if (object->unk1C->unk08 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            func_00100C80(heap);
            return;
        }
        func_00100C80(heap);
    }
    else
    {
        object->unk1C = new (0) FieldBitset154E80(rows);
        if (object->unk1C == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            return;
        }
        if (object->unk1C->unk08 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            return;
        }
    }
    if (columns > 1)
    {
        delete[] object->unk24;
        object->unk24 = new (0) FieldClass154E60[rows * (columns - 1) + 2];
        if (object->unk24 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            return;
        }
    }
    else
    {
        delete[] object->unk24;
        object->unk24 = 0;
    }
    if (object->unk18 != 0)
    {
        object->unk14 = (u8*)(object->unk18 + 1);
    }
    if (object->unk24 != 0)
    {
        object->unk20 = (u8*)(object->unk24 + 1);
    }
    object->unk0C = rows;
    object->unk10 = columns;
    object->unk1C->clear();
}

FieldClass15A5B0::FieldClass15A5B0()
{
}

FieldClass15A5B0::~FieldClass15A5B0()
{
}

FieldClass15A5C0::~FieldClass15A5C0()
{
    delete[] unk18;
    delete unk1C;
    delete[] unk24;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C3440);

extern "C" float func_002C3AC0(void* object)
{
    return 1.0f;
}

FieldClass15A690::~FieldClass15A690()
{
}

/** @brief Detach the object and add it to the resident release queue. @param object Object to release. */
extern "C" void func_002C3B70(void* object)
{
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C3BA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C41A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C4210);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C44C0);



INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C4790);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C49B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C4B50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C4E20);

extern "C" void func_002C4FC0(FieldPair* object, FieldThing* first, FieldThing* second)
{
    object->first = first;
    object->second = second;
    if (object->second->unk45 == D_30EAFC[object->first->unk45 * 16])
    {
        object->flag0 = 1;
    }
    else
    {
        object->flag0 = 0;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C5030);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C51A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C5330);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C53F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C5480);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C5590);

extern "C" void func_002C5640(FieldMotion* object, u8 value, s16 index, float rate)
{
    object->flag4 = 1;
    if (index != -1)
    {
        object->unk3E = index;
    }
    else
    {
        object->unk3E = object->unk3C;
    }
    object->unk46 = value;
    object->unk41 = 0;
    object->unk30 = rate;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C5690);

extern "C" void func_002C5A10(FieldMotion* object, s32 value, s32 mode, float rate)
{
    if (object->flag2 || object->flag0)
    {
        return;
    }
    object->flag0 = 1;
    object->flag1 = mode;
    object->unk40 = 0;
    object->unk28 = value;
    object->unk30 = rate;
}

void FieldClass15AAB0::func_001DD7B0()
{
    if (unk2C != 0)
    {
        unk2C->func_001DD7B0();
        unk2C = 0;
    }
    func_004D65C0(this);
    func_0011ED90(D_001B65F4, this);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C5AE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C7330);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C73C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C7460);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C7600);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C7680);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C76C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C7720);

extern "C" void func_002C7780(FieldList* object)
{
    FieldNode* node = &object->sentinel;
    for (;;)
    {
        node = node->next;
        if (&object->sentinel == node)
        {
            break;
        }
        if (node->flags & 0x10000)
        {
            node->unk64 = 1;
        }
    }
    object->unk126 = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C77C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C78B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C79C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C7A90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C7EE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C7FD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C83A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C8510);

FieldClass15A780::~FieldClass15A780()
{
}

FieldClass15A7A0::~FieldClass15A7A0()
{
}

FieldClass15A7C0::~FieldClass15A7C0()
{
}

extern "C" void func_002C95B0(FieldFloat48* object)
{
    if (object->value > 0.0f)
    {
        object->value -= D_001B6688;
    }
}

FieldClass15A800::~FieldClass15A800()
{
}

extern "C" int func_002C9660(void* object)
{
    return 3;
}

extern "C" void func_002C9670(FieldState28* object)
{
    object->unk28 = 0;
}

extern "C" void func_002C9680(void* object)
{
}

extern "C" float func_002C9690(void* object)
{
    return 2500.0f;
}

extern "C" int func_002C96B0(void* object)
{
    return 1;
}

/** Partial FieldClass154E20 object with vtable D_15AA70 in main data. */
class FieldClass15AA70 : public FieldClass154E20
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass15AA70();
    /** @brief Create the grid for this object. */
    virtual void func_slot30();
};

FieldClass15AA70::~FieldClass15AA70()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_slot30__16FieldClass15AA70Fv);

FieldClass15AAB0::~FieldClass15AAB0()
{
}

FieldClass15AAD0::~FieldClass15AAD0()
{
}

extern "C" int func_002C9A20(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C9A30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002C9B40);

extern "C" void func_002CA150(FieldSelector* object, const u8* value, void* context)
{
    object->unk2C = value;
    object->unk30 = context;
    if (*object->unk2C == 1)
    {
        object->unk34 = 1;
    }
    else
    {
        object->unk34 = 0;
    }
}

extern "C" void* func_002CA190(void* object)
{
    return 0;
}

extern "C" void func_002CA1A0(void* object)
{
}

extern "C" float func_002CA1B0(void* object)
{
    return 100.0f;
}

extern "C" void func_002CA1C0(void* object)
{
}

extern "C" void func_002CA1D0(void* object)
{
}

extern "C" void func_002CA1E0(void* object)
{
}

extern "C" void func_002CA1F0(void* object)
{
}

extern "C" void func_002CA200(void* object)
{
}

extern "C" void func_002CA210(void* object)
{
}

extern "C" int func_002CA220(void* object)
{
    return 0;
}

extern "C" void func_002CA230(void* object)
{
}

extern "C" void func_002CA240(void* object)
{
}

extern "C" void func_002CA250(void* object)
{
}

extern "C" int func_002CA260(void* object)
{
    return 0;
}

extern "C" void func_002CA270(void* object)
{
}

extern "C" void func_002CA280(void* object)
{
}

extern "C" void func_002CA290(void* object)
{
}

extern "C" void func_002CA2A0(void* object)
{
}

extern "C" void func_002CA2B0(void* object)
{
}

extern "C" int func_002CA2C0(void* object)
{
    return 0;
}

extern "C" void func_002CA2D0(void* object)
{
}

extern "C" int func_002CA2E0(void* object)
{
    return 0;
}

extern "C" void func_002CA2F0(void* object)
{
}

extern "C" float func_002CA300(void* object)
{
    return 0.0f;
}

extern "C" void func_002CA310(void* object)
{
}

extern "C" void func_002CA320(void* object)
{
}

extern "C" int func_002CA330(void* object)
{
    return 0;
}

extern "C" void func_002CA340(void* object)
{
}

extern "C" int func_002CA350(void* object)
{
    return 0;
}

extern "C" void func_002CA360(void* object)
{
}

extern "C" float func_002CA370(void* object)
{
    return 0.0f;
}

extern "C" void func_002CA380(void* object)
{
}

FieldClass15AB70::FieldClass15AB70()
{
    unk04 = 0;
    unk14 = 0;
    unk18 = 0;
    unk1C = 0;
    unk20 = 0;
    unk24 = 0;
}

extern "C" void* func_002CA3F0(FieldTable14* object, u32 index) { return object->entries + index * 0x40; }

extern "C" void* func_002CA400(FieldGrid20* object, u32 column, u32 row) { return object->entries + (column * (object->rows - 1) + row) * 0x40; }

extern "C" u32 func_002CA420(const FieldWord1C* object) { return object->value; }

extern "C" u32 func_002CA430(const FieldWord0C* object) { return object->value; }

extern "C" u32 func_002CA440(const FieldWord10* object) { return object->value; }

extern "C" int func_002CA450(void* object) { return 1; }

extern "C" bool func_002CA460(const FieldWord14* object) { return object->value != 0; }

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
extern "C" void func_002CA470(FieldClass15AB70* object, const FieldClass15AB70* other)
{
    object->unk0C = other->unk0C;
    object->unk10 = other->unk10;
    object->resize(object->unk0C, object->unk10);
}

/**
 * @brief Reallocate the cells, the bit set and the secondary elements for a new size.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
extern "C" void func_002CA4B0(FieldClass15AB70* object, s32 rows, s32 columns)
{
    object->unk14 = 0;
    object->unk20 = 0;
    delete[] object->unk18;
    object->unk18 = new (0) FieldClass15AB58[rows + 2];
    if (object->unk18 == 0)
    {
        return;
    }
    delete object->unk1C;
    if (D_001B6684 != 0)
    {
        void* heap = func_00100C80(D_001B6684);
        object->unk1C = new (0) FieldBitset154E80(rows);
        if (object->unk1C == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            func_00100C80(heap);
            return;
        }
        if (object->unk1C->unk08 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            func_00100C80(heap);
            return;
        }
        func_00100C80(heap);
    }
    else
    {
        object->unk1C = new (0) FieldBitset154E80(rows);
        if (object->unk1C == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            return;
        }
        if (object->unk1C->unk08 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            return;
        }
    }
    if (columns > 1)
    {
        delete[] object->unk24;
        object->unk24 = new (0) FieldClass154E60[rows * (columns - 1) + 2];
        if (object->unk24 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            return;
        }
    }
    else
    {
        delete[] object->unk24;
        object->unk24 = 0;
    }
    if (object->unk18 != 0)
    {
        object->unk14 = (u8*)(object->unk18 + 1);
    }
    if (object->unk24 != 0)
    {
        object->unk20 = (u8*)(object->unk24 + 1);
    }
    object->unk0C = rows;
    object->unk10 = columns;
    object->unk1C->clear();
}

FieldClass15AB58::FieldClass15AB58()
{
    unk30 = 60.0f;
}

FieldClass15AB58::~FieldClass15AB58()
{
}

FieldClass15AB70::~FieldClass15AB70()
{
    delete[] unk18;
    delete unk1C;
    delete[] unk24;
}

extern "C" float func_002CABA0(void* object) { return 1.0f; }

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002C04E0", func_002CABB0);
