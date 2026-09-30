#include "include_asm.h"
#include "overlays/1067-00/text_002CABC0.h"

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CABC0", func_002CABC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CABC0", func_002CAE30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CABC0", func_002CB100);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CABC0", func_002CB1D0);

extern "C" void func_002CB5B0(FieldFlags1C* object, u32 flags) { object->flags |= flags; }

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CABC0", func_002CB5C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CABC0", func_002CB710);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CABC0", func_002CB9D0);

extern "C" int func_002CBAA0(void* object) { return 9; }

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CABC0", func_002CBAB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CABC0", func_002CBAE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CABC0", func_002CBB30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CABC0", func_002CCDF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CABC0", func_002CCE10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CABC0", func_002CCE30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CABC0", func_002CCED0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CABC0", func_002CD380);
