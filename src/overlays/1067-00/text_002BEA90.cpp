#include "include_asm.h"
#include "overlays/1067-00/field_class_154D40.h"
#include "overlays/1067-00/field_class_154EF0.h"
#include "overlays/1067-00/text_002BEA90.h"
#include "overlays/1067-00/text_002764D0.h"
#include "main/resident_data.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_00419A70.h"
#include "overlays/lib/text_0044ABE0.h"

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
struct FieldRuntime
{
    u8 pad00[0x5EC];
    float rate;
};

struct FieldProgressState
{
    u8 pad00[0xCE];
    u8 changed;
    u8 padCF[0x11];
    float progress;
    u8 padE4[0x174];
    u16 mode;
};

extern "C" FieldRuntime* D_001B657C;
extern "C" s8 D_30EAFC[];

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BEA90", __dt__16FieldClass159C30Fv);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BEA90", __dt__16FieldClass159D00Fv);

/** Partial FieldClass154E20 object with vtable D_159DD0 in main data. */
class FieldClass159DD0 : public FieldClass154E20
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass159DD0();
};

FieldClass159DD0::~FieldClass159DD0()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BEA90", func_002BEBD0);

/** Partial FieldClass1553B0 object with vtable D_159E10 in main data. */
class FieldClass159E10 : public FieldClass1553B0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass159E10();
};

FieldClass159E10::~FieldClass159E10()
{
}

extern "C" void func_002BED50(FieldBitFlags1C* self)
{
    self->active = false;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BEA90", func_002BED70);

extern "C" void func_002BF3F0(FieldInputBlock* self, const u8* data, s32 count)
{
    self->data = data;
    self->count = count;
    if (*self->data == 1)
    {
        self->unk34 = 1;
    }
    else
    {
        self->unk34 = 0;
    }
}

extern "C" int func_002BF430(void* object)
{
    return 0;
}

extern "C" void func_002BF440(void* object)
{
}

extern "C" float func_002BF450(void* object)
{
    return 100.0f;
}

extern "C" void func_002BF460(void* object)
{
}

extern "C" void func_002BF470(void* object)
{
}

extern "C" void func_002BF480(void* object)
{
}

extern "C" void func_002BF490(void* object)
{
}

extern "C" void func_002BF4A0(void* object)
{
}

extern "C" void func_002BF4B0(void* object)
{
}

extern "C" int func_002BF4C0(void* object)
{
    return 0;
}

extern "C" void func_002BF4D0(void* object)
{
}

extern "C" void func_002BF4E0(void* object)
{
}

extern "C" void func_002BF4F0(void* object)
{
}

extern "C" int func_002BF500(void* object)
{
    return 0;
}

extern "C" void func_002BF510(void* object)
{
}

extern "C" void func_002BF520(void* object)
{
}

extern "C" void func_002BF530(void* object)
{
}

extern "C" void func_002BF540(void* object)
{
}

extern "C" void func_002BF550(void* object)
{
}

extern "C" int func_002BF560(void* object)
{
    return 0;
}

extern "C" void func_002BF570(void* object)
{
}

extern "C" int func_002BF580(void* object)
{
    return 0;
}

extern "C" void func_002BF590(void* object)
{
}

extern "C" float func_002BF5A0(void* object)
{
    return 0.0f;
}

extern "C" void func_002BF5B0(void* object)
{
}

extern "C" void func_002BF5C0(void* object)
{
}

extern "C" int func_002BF5D0(void* object)
{
    return 0;
}

extern "C" void func_002BF5E0(void* object)
{
}

extern "C" int func_002BF5F0(void* object)
{
    return 0;
}

extern "C" void func_002BF600(void* object)
{
}

extern "C" float func_002BF610(void* object)
{
    return 0.0f;
}

extern "C" void func_002BF620(void* object)
{
}

FieldClass159E50::FieldClass159E50()
{
    unk04 = 0;
    unk14 = 0;
    unk18 = 0;
    unk1C = 0;
    unk20 = 0;
    unk24 = 0;
}

extern "C" FieldEntry90* func_002BF690(FieldCollection90* self, s32 index)
{
    return &self->entries[index];
}

extern "C" FieldCell40* func_002BF6B0(FieldGrid40* self, s32 row, s32 column)
{
    return &self->cells[row * (self->width - 1) + column];
}

extern "C" s32 func_002BF6D0(const FieldSignedWord1C* self)
{
    return self->value;
}

extern "C" s32 func_002BF6E0(const FieldSignedWord0C* self)
{
    return self->value;
}

extern "C" s32 func_002BF6F0(const FieldSignedWord10* self)
{
    return self->value;
}

extern "C" s32 func_002BF700(void* self)
{
    return 0x20;
}

extern "C" bool func_002BF710(const FieldPointer14* self)
{
    return self->value != 0;
}

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
extern "C" void func_002BF720(FieldClass159E50* object, const FieldClass159E50* other)
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
extern "C" void func_002BF760(FieldClass159E50* object, s32 rows, s32 columns)
{
    object->unk14 = 0;
    object->unk20 = 0;
    delete[] object->unk18;
    object->unk18 = new (0) FieldClass159E40[rows + 2];
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

FieldClass159E40::FieldClass159E40()
{
}

FieldClass159E40::~FieldClass159E40()
{
}

FieldClass159E50::~FieldClass159E50()
{
    delete[] unk18;
    delete unk1C;
    delete[] unk24;
}

extern "C" float func_002BFE60(void* object)
{
    return 1.0f;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BEA90", func_002BFE70);

extern "C" void func_002BFF40(FieldProgressState* self)
{
    if (self->mode == 1)
    {
        self->progress += 128.0f * D_001B657C->rate;
        if (self->progress >= 128.0f)
        {
            self->progress = 128.0f;
            self->mode = 0;
        }
        self->changed = 1;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BEA90", func_002BFF90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BEA90", func_002C00F0);

extern "C" void func_002C0390(FieldState100* state)
{
    if (state->unk100 == 0)
    {
        state->unk3b = 0;
        return;
    }
    if (state->unk3b == 0)
    {
        func_113EA0();
        func_4C74E0(state);
        func_462320(state, state->unk70, state->unkB8);
        state->unk3b = 1;
    }
}

/** Partial LibClass178600 widget with vtable D_159FE0 in main data. */
class FieldClass159FE0 : public LibClass178600
{
public:
    /** @brief Release the widget storage and destroy its base. */
    virtual ~FieldClass159FE0();
    LibStorageBlock0C unk40;
};

FieldClass159FE0::~FieldClass159FE0()
{
}

/** Partial LibObject178750 text widget with vtable D_15A010 in main data. */
class FieldClass15A010 : public LibObject178750
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass15A010();
};

FieldClass15A010::~FieldClass15A010()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BEA90", func_002C04D0);
