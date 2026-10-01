#include "include_asm.h"
#include "overlays/1067-00/text_002BEA90.h"

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BEA90", func_002BEA90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BEA90", func_002BEAF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BEA90", func_002BEB60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BEA90", func_002BEBD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BEA90", func_002BECB0);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BEA90", func_002BF630);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BEA90", func_002BF720);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BEA90", func_002BF760);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BEA90", func_002BFCC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BEA90", func_002BFD00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BEA90", func_002BFD80);

extern "C" float func_002BFE60(void* object)
{
    return 1.0f;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BEA90", func_002BFE70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BEA90", func_002BFF40);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BEA90", func_002C0400);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BEA90", func_002C0470);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BEA90", func_002C04D0);
