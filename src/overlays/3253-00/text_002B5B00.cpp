#include "include_asm.h"
#include "overlays/3253-00/text_002B5B00.h"

extern "C" void func_00298370(void* object);
extern "C" void func_002A6040(void);
extern "C" void func_002A6780(void);
extern "C" void func_002825F0(void* object, s32 value);
extern "C" void func_002B3BC0(void* object, u8 value);
extern "C" void func_002B8FB0(void* receiver, s32 value);
extern "C" u8 func_003ADF00(void* object);
extern "C" u8 func_003C3B80(void* object);
extern "C" u32 func_4A1120(u32 value, const void* data);
extern "C" const u8 D_3E27A8[];
extern "C" const u8 D_3E22A8[];
extern "C" const u8 D_3E26F8[];
extern "C" const u8 D_15B140[];
extern "C" u32 func_4A0B70(u32 value, const void* data);
extern "C" const u8 D_3E28A8[];
extern "C" float func_4E1F10(s32 value);
extern "C" void func_003C37C0(void* object, s32 value);
extern "C" void func_100D60(void* object);

struct FieldValue194
{
    u8 unk00[0x194];
    s32 unk194;
};

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B5B00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B5B30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B5B60);

s32 func_002B5C80(void* object)
{
    return 4;
}

void func_002B5C90(void* object)
{
}

struct FieldFloat04
{
    u8 unk00[4];
    float unk04;
};

s32 func_002B5CA0(void* object, const void* value, float* result0, float* result1)
{
    const FieldFloat04* input = (const FieldFloat04*)value;
    if (input->unk04 > 0.0f)
    {
        *result0 = 0.0f;
        *result1 = 0.05f;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B5CE0);

s32 func_002B5D70(void* object)
{
    return 14;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B5D80);

float func_002B5E10(void* receiver)
{
    FieldValue194* object = (FieldValue194*)receiver;
    float result = 0.0f;
    s32 child = object->unk194;
    if (child != 0)
    {
        result = func_4E1F10(child);
    }
    return result;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B5E40);

struct FieldWord14And338
{
    u8 unk00[0x14];
    u32 unk14;
    u8 unk18[0x320];
    u32 unk338;
};

void func_002B5F20(void* receiver)
{
    FieldWord14And338* object = (FieldWord14And338*)receiver;
    object->unk14 = object->unk338;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B5F30);

struct FieldByte60
{
    u8 unk00[0x60];
    u8 unk60;
};

void func_002B5FC0(void* receiver)
{
    FieldByte60* object = (FieldByte60*)receiver;
    object->unk60 = 8;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B5FD0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B60A0);

void func_002B60E0(void* receiver)
{
    FieldByte60* object = (FieldByte60*)receiver;
    object->unk60 = 8;
}

struct FieldByte493
{
    u8 unk00[0x493];
    u8 unk493;
};

void func_002B60F0(void* receiver)
{
    FieldByte493* object = (FieldByte493*)receiver;
    object->unk493 = 1;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B6100);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B6190);

s32 func_002B6250(void* object)
{
    return 14;
}

struct FieldByte04
{
    u32 unk00;
    u8 unk04;
};

void func_002B6260(void* receiver)
{
    FieldByte04* object = (FieldByte04*)receiver;
    object->unk04 = 1;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B6270);

struct FieldSignedHalfword18
{
    u8 unk00[0x18];
    s16 unk18;
};

s32 func_002B6300(void* receiver)
{
    FieldSignedHalfword18* object = (FieldSignedHalfword18*)receiver;
    return object->unk18;
}

void func_002B6310(void* object)
{
}

struct FieldWordsD3C
{
    u8 unk00[0xD3C];
    u32 unkD3C;
    u32 unkD40;
    u32 unkD44;
};

u32 func_002B6320(void* receiver)
{
    FieldWordsD3C* object = (FieldWordsD3C*)receiver;
    return object->unkD3C;
}

u32 func_002B6330(void* receiver)
{
    FieldWordsD3C* object = (FieldWordsD3C*)receiver;
    return object->unkD40;
}

u32 func_002B6340(void* receiver)
{
    FieldWordsD3C* object = (FieldWordsD3C*)receiver;
    return object->unkD44;
}

struct FieldByteCEE
{
    u8 unk00[0xCEE];
    u8 unkCEE;
};

u8 func_002B6350(void* receiver)
{
    FieldByteCEE* object = (FieldByteCEE*)receiver;
    return object->unkCEE;
}

struct FieldByteCEA
{
    u8 unk00[0xCEA];
    u8 unkCEA;
};

u8 func_002B6360(void* receiver)
{
    FieldByteCEA* object = (FieldByteCEA*)receiver;
    return object->unkCEA;
}

struct FieldByteCE1
{
    u8 unk00[0xCE1];
    u8 unkCE1;
};

u8 func_002B6370(void* receiver)
{
    FieldByteCE1* object = (FieldByteCE1*)receiver;
    return object->unkCE1;
}

s32 func_002B6380(void* object)
{
    return 0;
}

s32 func_002B6390(void* object)
{
    return 0;
}

s32 func_002B63A0(void* object)
{
    return 0;
}

void func_002B63B0(void* object)
{
}

s32 func_002B63C0(void* object)
{
    return 0;
}

s32 func_002B63D0(void* object)
{
    return 0;
}

struct FieldByteF26
{
    u8 unk00[0xF26];
    u8 unkF26;
};

u8 func_002B63E0(void* receiver)
{
    FieldByteF26* object = (FieldByteF26*)receiver;
    return object->unkF26;
}

struct FieldMaskedWordCD8AndD24
{
    u8 unk00[0xCD8];
    u32 unkCD8;
    u8 unkCDC[0x48];
    u32 unkD24;
};

u32 func_002B63F0(void* receiver)
{
    FieldMaskedWordCD8AndD24* object = (FieldMaskedWordCD8AndD24*)receiver;
    return object->unkD24 ^ (object->unkCD8 & 0xFD93E028);
}

s32 func_002B6410(void* object)
{
    return 0;
}

s32 func_002B6420(void* object)
{
    return 0;
}

s32 func_002B6430(void* object)
{
    return 0;
}

s32 func_002B6440(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B6450);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B6580);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B6600);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B6690);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B6780);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B6790);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B67A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B67B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B67C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B67D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B67E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B67F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B6800);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B6810);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B6820);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B6830);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B6840);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B6850);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B6860);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B6870);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B6880);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B6890);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B68A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B68B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B68C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B6960);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B6A50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B7190);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B7280);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B7760);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B7D10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B88C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B8970);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B8A00);

struct FieldByte448
{
    u8 unk00[0x448];
    u8 unk448;
};

s32 func_002B8CD0(void* receiver)
{
    FieldByte448* object = (FieldByte448*)receiver;
    object->unk448 = 0;
    if (func_003ADF00(receiver) == 0)
    {
        return 0;
    }
    func_002B3BC0((u8*)receiver + 0x1F0, 1);
    return 1;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B8D20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B8FB0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B91F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B92D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B93E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B95A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B9B50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B9BD0);

struct FieldHalfword2F28
{
    u8 unk00[0x2F28];
    s16 unk2F28;
};

void func_002B9CB0(void* receiver, s32 value)
{
    FieldHalfword2F28* object = (FieldHalfword2F28*)receiver;
    if ((value & 0xFF) == 8)
    {
        object->unk2F28 = 1;
    }
    func_002A6040();
}

struct FieldBytesCE1CEE
{
    u8 unk00[0xCE1];
    u8 unkCE1;
    u8 unkCE2[0x0C];
    u8 unkCEE;
};

void func_002B9CF0(void* receiver, s32 value)
{
    FieldBytesCE1CEE* object = (FieldBytesCE1CEE*)receiver;
    if (object->unkCE1 != 0 && object->unkCEE == 0x21)
    {
        func_002B8FB0(receiver, value);
    }
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B9D30);

struct FieldByte579
{
    u8 unk00[0x579];
    u8 unk579;
};

void func_002B9E30(void* receiver)
{
    FieldByte579* object = (FieldByte579*)receiver;
    func_00298370(receiver);
    object->unk579 = 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002B9E60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BA1D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BA640);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BAAE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BACD0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BAE50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BB140);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BB310);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BB4B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BB680);

struct FieldWords50And2EEC
{
    u8 unk00[0x50];
    u32 unk50;
    u8 unk54[0x2E98];
    u32 unk2EEC;
};

void func_002BB740(void* receiver)
{
    FieldWords50And2EEC* object = (FieldWords50And2EEC*)receiver;
    func_002A6780();
    object->unk2EEC = func_4A1120(object->unk50, D_3E22A8);
}

struct FieldVtable
{
    const void* vtable;
};

void* func_002BB780(void* receiver, s16 value)
{
    if (receiver != 0)
    {
        FieldVtable* object = (FieldVtable*)receiver;
        object->vtable = D_15B140;
        func_002825F0(receiver, 0);
        if (value > 0)
        {
            func_100D60(receiver);
        }
    }
    return receiver;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BB7E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BB880);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BB9A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BC1B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BC240);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BC470);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BC510);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BC610);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BCCB0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BCD20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BD140);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BD230);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BDF20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BDFC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BE2D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BE610);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BE730);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BE850);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BED70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BF0B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BFB30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BFCD0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BFD80);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BFDD0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C0A40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C0AE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C0BA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C0F60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C1390);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C17D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C18A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C1AD0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C1BD0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C1D90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C1FC0);

struct FieldWords50And2F04
{
    u8 unk00[0x50];
    u32 unk50;
    u8 unk54[0x2EB0];
    u32 unk2F04;
};

void func_002C2030(void* receiver)
{
    FieldWords50And2F04* object = (FieldWords50And2F04*)receiver;
    func_002A6780();
    object->unk2F04 = func_4A0B70(object->unk50, D_3E26F8);
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C2070);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C20D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C2150);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C2330);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C2570);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C2630);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C2720);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C3FE0);

struct FieldByte5BE
{
    u8 unk00[0x5BE];
    u8 unk5BE;
};

void func_002C40A0(void* receiver)
{
    FieldByte5BE* object = (FieldByte5BE*)receiver;
    func_003C37C0(receiver, 0);
    object->unk5BE = 1;
}

void func_002C40D0(void* receiver)
{
    FieldByte5BE* object = (FieldByte5BE*)receiver;
    func_003C37C0(receiver, 0);
    object->unk5BE = 1;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C4100);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C4180);

struct FieldBytes38EAnd5BC
{
    u8 unk00[0x38E];
    u8 unk38E;
    u8 unk38F[0x22D];
    u8 unk5BC;
};

s32 func_002C42B0(void* receiver)
{
    FieldBytes38EAnd5BC* object = (FieldBytes38EAnd5BC*)receiver;
    if (func_003C3B80(receiver) == 0)
    {
        return 0;
    }
    object->unk38E = 1;
    object->unk5BC = 0xF;
    return 1;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C4300);

struct FieldWords50And450
{
    u8 unk00[0x50];
    u32 unk50;
    u8 unk54[0x3FC];
    u32 unk450;
};

void func_002C4540(void* receiver)
{
    FieldWords50And450* object = (FieldWords50And450*)receiver;
    object->unk450 = func_4A1120(object->unk50, D_3E27A8);
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C4580);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C4800);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C4FC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C5080);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C51A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C5620);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C5670);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C56E0);

struct FieldWords50And45C
{
    u8 unk00[0x50];
    u32 unk50;
    u8 unk54[0x408];
    u32 unk45C;
};

void func_002C5800(void* receiver)
{
    FieldWords50And45C* object = (FieldWords50And45C*)receiver;
    object->unk45C = func_4A0B70(object->unk50, D_3E28A8);
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C5840);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C5A50);
