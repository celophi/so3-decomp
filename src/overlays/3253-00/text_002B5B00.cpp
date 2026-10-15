#include "include_asm.h"
#include "overlays/3253-00/text_002B5B00.h"

extern "C" void func_0036ABF0(void* first, void* second, void* third, void* fourth, u32 flags);
extern "C" void func_00298370(void* object);
extern "C" void func_002A6040(void);
extern "C" void func_002A6780(void);
extern "C" void func_002B3270(void* object);
extern "C" void func_002825F0(void* object, s32 value);
extern "C" void func_002B3BC0(void* object, u8 value);
extern "C" void func_002B8FB0(void* receiver, s32 value);
extern "C" u8 func_003ADF00(void* object);
extern "C" u8 func_003C3B80(void* object);
extern "C" float func_4E70B0(float value);
extern "C" void func_4D7EB0(void* object);
extern "C" void func_003B09E0(void* object, s32 value);
extern "C" void func_003B0E50(void* object, s32 value);
extern "C" void func_002B39A0(void* object, s32 value);
extern "C" void func_100D60(void* object);
extern "C" void func_0026D7A0(void* object, s32 value);
extern "C" void func_100CB0(void* object);
extern "C" void func_00272990(void* object);
extern "C" void func_0026F920(void* object, s32 value);
extern "C" u32 func_4A1120(u32 value, const void* data);
extern "C" const u8 D_3E27A8[];
extern "C" const u8 D_3E22A8[];
extern "C" const u8 D_3E26F8[];
extern "C" const u8 D_3E2388[];
extern "C" const u8 D_3E2398[];
extern "C" const u8 D_3E23B0[];
extern "C" const u8 D_15A5C0[];
extern "C" const u8 D_15A5E0[];
extern "C" const u8 D_15B3B0[];
extern "C" const u8 D_15B3D4[];
extern "C" const u8 D_15B250[];
extern "C" const u8 D_15B274[];
extern "C" const u8 D_169320[];
extern "C" const u8 D_169344[];
extern "C" const u8 D_169EF0[];
extern "C" const u8 D_169F14[];
extern "C" const u8 D_15B520[];
extern "C" const u8 D_15B544[];
extern "C" const u8 D_15A6F0[];
extern "C" const u8 D_15A710[];
extern "C" const u8 D_15A71C[];
extern "C" const u8 D_15A734[];
extern "C" const u8 D_15A8C0[];
extern "C" const u8 D_15A8E4[];
extern "C" const u8 D_15A920[];
extern "C" const u8 D_15A940[];
extern "C" const u8 D_15A964[];
extern "C" const u8 D_15A9A0[];
extern "C" const u8 D_15A3E0[];
extern "C" const u8 D_15B060[];
extern "C" const u8 D_15B084[];
extern "C" const u8 D_15B380[];
extern "C" const u8 D_15AC00[];
extern "C" const u8 D_15ACC0[];
extern "C" const u8 D_157610[];
extern "C" const u8 D_157600[];
extern "C" const u8 D_1575F0[];
extern "C" const u8 D_15B140[];
extern "C" const u8 D_15B410[];
extern "C" u32 func_4A0B70(u32 value, const void* data);
extern "C" const u8 D_3E28A8[];
extern "C" float func_4E1F10(s32 value);
extern "C" void func_003C37C0(void* object, s32 value);
extern "C" void func_100D60(void* object);
extern "C" void func_002826F0(void);

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

struct FieldVtableB5CE0
{
    const void* vtable;
};

void* func_002B5CE0(void* receiver, s16 value)
{
    FieldVtableB5CE0* object = (FieldVtableB5CE0*)receiver;

    if (receiver != 0)
    {
        object->vtable = D_15A5C0;
        if (receiver != 0)
        {
            object->vtable = D_157610;
            func_4D7EB0(receiver);
            if (receiver != 0)
            {
                object->vtable = D_157600;
                if (receiver != 0)
                {
                    object->vtable = D_1575F0;
                }
            }
        }
        if (value > 0)
        {
            func_100D60(receiver);
        }
    }
    return receiver;
}

s32 func_002B5D70(void* object)
{
    return 14;
}

struct FieldVtableB5D80
{
    const void* vtable;
};

void* func_002B5D80(void* receiver, s16 value)
{
    FieldVtableB5D80* object = (FieldVtableB5D80*)receiver;

    if (receiver != 0)
    {
        object->vtable = D_15A5E0;
        if (receiver != 0)
        {
            object->vtable = D_157610;
            func_4D7EB0(receiver);
            if (receiver != 0)
            {
                object->vtable = D_157600;
                if (receiver != 0)
                {
                    object->vtable = D_1575F0;
                }
            }
        }
        if (value > 0)
        {
            func_100D60(receiver);
        }
    }
    return receiver;
}

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

struct FieldB5F30
{
    const void* vtable;
    u8 unk04[0xCC];
    const void* unkD0;
    const void* unkD4;
    u8 unkD8[0x1EC];
    const void* unk2C4;
};

void* func_002B5F30(void* receiver, s16 value)
{
    FieldB5F30* object = (FieldB5F30*)receiver;

    if (receiver != 0)
    {
        object->vtable = D_15A6F0;
        object->unkD0 = D_15A710;
        object->unkD4 = D_15A71C;
        object->unk2C4 = D_15A734;
        func_0026D7A0(receiver, 0);
        if (value > 0)
        {
            func_100D60(receiver);
        }
    }
    return receiver;
}

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

struct FieldB5FD0
{
    const void* vtable;
    u8 unk04[0x2A4];
    const void* unk2A8;
    u8 unk2AC[0x1C0];
    const void* unk46C;
    u8 unk470[0x68];
    void* unk4D8;
};

void* func_002B5FD0(void* receiver, s16 value)
{
    FieldB5FD0* object = (FieldB5FD0*)receiver;

    if (receiver != 0)
    {
        object->vtable = D_15A8C0;
        object->unk2A8 = D_15A8E4;
        object->unk46C = D_15A920;
        if (receiver != 0)
        {
            object->vtable = D_15A940;
            object->unk2A8 = D_15A964;
            object->unk46C = D_15A9A0;
            if (object->unk4D8 != 0)
            {
                func_100CB0(object->unk4D8);
                object->unk4D8 = 0;
            }
            func_00272990(receiver);
            func_0026F920(receiver, 0);
        }
        if (value > 0)
        {
            func_100D60(receiver);
        }
    }
    return receiver;
}

void func_002B60A0(u8* receiver, void* value1, void* value2, void* value3)
{
    u8* adjusted = receiver;
    if (adjusted != 0) {
        adjusted = adjusted + 0x290;
    }
    func_0036ABF0(receiver + 0x450, adjusted, value1, value2, 1);
}

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

void* func_002B6100(void* receiver, s16 value)
{
    FieldVtableB5D80* object = (FieldVtableB5D80*)receiver;

    if (receiver != 0)
    {
        object->vtable = D_15AC00;
        if (receiver != 0)
        {
            object->vtable = D_157610;
            func_4D7EB0(receiver);
            if (receiver != 0)
            {
                object->vtable = D_157600;
                if (receiver != 0)
                {
                    object->vtable = D_1575F0;
                }
            }
        }
        if (value > 0)
        {
            func_100D60(receiver);
        }
    }
    return receiver;
}

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

void* func_002B6270(void* receiver, s16 value)
{
    FieldVtableB5D80* object = (FieldVtableB5D80*)receiver;

    if (receiver != 0)
    {
        object->vtable = D_15ACC0;
        if (receiver != 0)
        {
            object->vtable = D_157610;
            func_4D7EB0(receiver);
            if (receiver != 0)
            {
                object->vtable = D_157600;
                if (receiver != 0)
                {
                    object->vtable = D_1575F0;
                }
            }
        }
        if (value > 0)
        {
            func_100D60(receiver);
        }
    }
    return receiver;
}

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

struct FieldListResult
{
    u32 unk00;
    s32 count;
    u64* values;
};

struct FieldListReceiver
{
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0C() = 0;
    virtual void slot10() = 0;
    virtual void slot14() = 0;
    virtual void slot18() = 0;
    virtual void slot1C() = 0;
    virtual void slot20() = 0;
    virtual void slot24() = 0;
    virtual FieldListResult* getList() = 0;
};

s32 func_002B6580(void* receiver)
{
    FieldListReceiver* object = (FieldListReceiver*)receiver;
    FieldListResult* list = object->getList();

    if (list != 0)
    {
        s32 count = list->count;
        u64* values = list->values;
        s32 i = 0;

        while (i < count)
        {
            if (*values != 0)
            {
                return 1;
            }
            i++;
            values++;
        }
    }
    return 0;
}

struct FieldBitsetResult
{
    s32 count;
    u32 unk04;
    u64* words;
};

s32 func_002B6600(void* receiver)
{
    FieldListReceiver* object = (FieldListReceiver*)receiver;
    FieldBitsetResult* list = (FieldBitsetResult*)object->getList();

    if (list == 0)
    {
        return 0;
    }
    s32 count = list->count;
    s32 set_count = 0;
    u32 index = 0;
    while ((s32)index < count)
    {
        if ((list->words[index >> 6] >> (index & 0x3F)) & 1)
        {
            set_count++;
        }
        index++;
    }
    return set_count;
}

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

struct FieldVtableSubobject290
{
    const void* vtable;
    u8 unk04[0x2A4];
    const void* unk2A8;
};

void* func_002B68C0(void* receiver, s16 value)
{
    FieldVtableSubobject290* object = (FieldVtableSubobject290*)receiver;

    if (receiver != 0)
    {
        object->vtable = D_15B060;
        object->unk2A8 = D_15B084;
        if (receiver != 0)
        {
            object->vtable = D_169320;
            object->unk2A8 = D_169344;
            func_003B0E50((u8*)receiver + 0x290, 0);
            func_002B39A0(receiver, 0);
        }
        if (value > 0)
        {
            func_100D60(receiver);
        }
    }
    return receiver;
}

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

void* func_002BB7E0(void* receiver)
{
    u8* object = (u8*)receiver;

    func_002826F0();
    *(const void**)object = D_15B140;
    *(u32*)(object + 0x2EA0) = 0;
    *(s16*)(object + 0x2EA4) = -1;
    *(s16*)(object + 0x2EA6) = -1;
    *(s32*)(object + 0x2EA8) = -1;
    *(u32*)(object + 0x2EAC) = 0;
    *(s16*)(object + 0x2EB0) = -1;
    *(s16*)(object + 0x2EB2) = -1;
    *(s32*)(object + 0x2EB4) = -1;
    *(u32*)(object + 0x2EB8) = 0;
    *(s16*)(object + 0x2EBC) = -1;
    *(s16*)(object + 0x2EBE) = -1;
    *(s32*)(object + 0x2EC0) = -1;
    *(u32*)(object + 0x2EC4) = 0;
    *(s16*)(object + 0x2EC8) = -1;
    *(s16*)(object + 0x2ECA) = -1;
    *(s32*)(object + 0x2ECC) = -1;
    *(u32*)(object + 0x2ED0) = 0;
    *(u32*)(object + 0x2EF0) = 0;
    *(s32*)(object + 0x2EF8) = -1;
    *(u32*)(object + 0x2F00) = 0;
    *(u32*)(object + 0x2F04) = 0;
    *(s16*)(object + 0x2F28) = 0;
    *(float*)(object + 0x66C) = 1.0f;
    object[0x2F2A] = 0;
    return receiver;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BB880);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BB9A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BC1B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BC240);

void* func_002BC470(void* receiver, s16 value)
{
    FieldVtableSubobject290* object = (FieldVtableSubobject290*)receiver;

    if (receiver != 0)
    {
        object->vtable = D_15B250;
        object->unk2A8 = D_15B274;
        if (receiver != 0)
        {
            object->vtable = D_169320;
            object->unk2A8 = D_169344;
            func_003B0E50((u8*)receiver + 0x290, 0);
            func_002B39A0(receiver, 0);
        }
        if (value > 0)
        {
            func_100D60(receiver);
        }
    }
    return receiver;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BC510);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BC610);

struct FieldWords50And5D0
{
    u8 unk00[0x50];
    u32 unk50;
    u8 unk54[0x57C];
    u32 unk5D0;
    u32 unk5D4;
    u8 unk5D8[8];
    u32 unk5E0;
};

void func_002BCCB0(void* receiver)
{
    FieldWords50And5D0* object = (FieldWords50And5D0*)receiver;
    u32 resource;

    func_002B3270(receiver);
    resource = object->unk50;
    object->unk5E0 = func_4A0B70(resource, D_3E2388);
    object->unk5D0 = func_4A1120(resource, D_3E2398);
    object->unk5D4 = func_4A1120(resource, D_3E23B0);
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BCD20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BD140);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BD230);

void* func_002BDF20(void* receiver, s16 value)
{
    FieldVtableSubobject290* object = (FieldVtableSubobject290*)receiver;

    if (receiver != 0)
    {
        object->vtable = D_169EF0;
        object->unk2A8 = D_169F14;
        if (receiver != 0)
        {
            object->vtable = D_169320;
            object->unk2A8 = D_169344;
            func_003B0E50((u8*)receiver + 0x290, 0);
            func_002B39A0(receiver, 0);
        }
        if (value > 0)
        {
            func_100D60(receiver);
        }
    }
    return receiver;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BDFC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BE2D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BE610);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BE730);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BE850);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BED70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BF0B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BFB30);

struct FieldInitializerBFCD0
{
    const void* vtable;
    u32 unk04;
    u32 unk08;
    u8 unk0C[2];
    u8 unk0E;
    u8 unk0F;
    u32 unk10;
    s32 unk14;
    s32 unk18;
    u32 unk1C;
    u32 unk20;
    u8 unk24[0x10];
    u32 unk34;
    u8 unk38[4];
    u32 unk3C;
    u8 unk40[4];
    u32 unk44;
    u8 unk48[4];
    u32 unk4C;
    u8 unk50[4];
    u32 unk54;
    u8 unk58[4];
    u32 unk5C;
    u8 unk60[4];
    u32 unk64;
    u8 unk68[4];
    u32 unk6C;
    u32 unk70;
    u32 unk74;
    u32 unk78;
    u8 unk7C[0x10];
    u32 unk8C;
    u8 unk90;
    u8 unk91;
};

void* func_002BFCD0(void* receiver)
{
    FieldInitializerBFCD0* object = (FieldInitializerBFCD0*)receiver;

    object->vtable = D_1575F0;
    object->vtable = D_157600;
    object->unk04 = 0;
    object->unk08 = 0;
    object->vtable = D_157610;
    object->unk0E = 0;
    object->unk0F = 0;
    object->unk10 = 0;
    object->vtable = D_15A3E0;
    object->unk14 = -1;
    object->unk18 = -1;
    object->unk1C = 0;
    object->unk20 = 0;
    object->vtable = D_15B380;
    object->unk34 = 0;
    object->unk3C = 0;
    object->unk44 = 0;
    object->unk4C = 0;
    object->unk54 = 0;
    object->unk5C = 0;
    object->unk64 = 0;
    object->unk6C = 0;
    object->unk70 = 0;
    object->unk74 = 0;
    object->unk78 = 0;
    object->unk8C = 0;
    object->unk90 = 0;
    object->unk91 = 0;
    return receiver;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BFD80);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002BFDD0);

struct FieldC0A40
{
    u8 unk00[0x60];
    unsigned __int128 unk60;
    u8 unk70[0x414];
    float unk484;
    float unk488;
};

union FieldC0A40State
{
    unsigned __int128 packed;
    float values[4];
};

s32 func_002C0A40(void* receiver)
{
    FieldC0A40* object = (FieldC0A40*)receiver;
    FieldC0A40State state;
    float* value;
    float increment;

    if (func_003ADF00(receiver) == 0)
    {
        return 0;
    }
    state.packed = object->unk60;
    value = &state.values[1];
    object->unk484 = *value;
    increment = func_4E70B0(object->unk488);
    *value = increment * 10.0f + *value;
    object->unk60 = state.packed;
    func_003B09E0((u8*)receiver + 0x290, 1);
    return 1;
}

struct FieldReleaseObject
{
    virtual void slot08() = 0;
    virtual void slot0C() = 0;
    virtual void release() = 0;
};

struct FieldC0AE0
{
    const void* vtable;
    u8 unk04[0x2A4];
    const void* unk2A8;
    u8 unk2AC[0x1CC];
    FieldReleaseObject* unk478;
};

void* func_002C0AE0(void* receiver, s16 value)
{
    FieldC0AE0* object = (FieldC0AE0*)receiver;

    if (receiver != 0)
    {
        object->vtable = D_15B3B0;
        object->unk2A8 = D_15B3D4;
        if (object->unk478 != 0)
        {
            object->unk478->release();
            object->unk478 = 0;
        }
        if (receiver != 0)
        {
            object->vtable = D_169320;
            object->unk2A8 = D_169344;
            func_003B0E50((u8*)receiver + 0x290, 0);
            func_002B39A0(receiver, 0);
        }
        if (value > 0)
        {
            func_100D60(receiver);
        }
    }
    return receiver;
}

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

void* func_002C2070(void* receiver, s16 value)
{
    if (receiver != 0)
    {
        FieldVtable* object = (FieldVtable*)receiver;
        object->vtable = D_15B410;
        func_002825F0(receiver, 0);
        if (value > 0)
        {
            func_100D60(receiver);
        }
    }
    return receiver;
}

struct FieldInitializer2EA0
{
    const void* vtable;
    u8 unk04[0x2E9C];
    u32 unk2EA0;
    s16 unk2EA4;
    s16 unk2EA6;
    s32 unk2EA8;
    u32 unk2EAC;
    s16 unk2EB0;
    s16 unk2EB2;
    s32 unk2EB4;
    u32 unk2EB8;
    s16 unk2EBC;
    s16 unk2EBE;
    s32 unk2EC0;
    u32 unk2EC4;
    s16 unk2EC8;
    s16 unk2ECA;
    s32 unk2ECC;
    u8 unk2ED0[0x3C];
    u8 unk2F0C;
};

void* func_002C20D0(void* receiver)
{
    FieldInitializer2EA0* object = (FieldInitializer2EA0*)receiver;

    func_002826F0();
    object->vtable = D_15B410;
    object->unk2EA0 = 0;
    object->unk2EA4 = -1;
    object->unk2EA6 = -1;
    object->unk2EA8 = -1;
    object->unk2EAC = 0;
    object->unk2EB0 = -1;
    object->unk2EB2 = -1;
    object->unk2EB4 = -1;
    object->unk2EB8 = 0;
    object->unk2EBC = -1;
    object->unk2EBE = -1;
    object->unk2EC0 = -1;
    object->unk2EC4 = 0;
    object->unk2EC8 = -1;
    object->unk2ECA = -1;
    object->unk2ECC = -1;
    object->unk2F0C = 0;
    return receiver;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C2150);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C2330);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C2570);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C2630);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002B5B00", func_002C2720);

void* func_002C3FE0(void* receiver, s16 value)
{
    FieldVtableSubobject290* object = (FieldVtableSubobject290*)receiver;

    if (receiver != 0)
    {
        object->vtable = D_15B520;
        object->unk2A8 = D_15B544;
        if (receiver != 0)
        {
            object->vtable = D_169EF0;
            object->unk2A8 = D_169F14;
            if (receiver != 0)
            {
                object->vtable = D_169320;
                object->unk2A8 = D_169344;
                func_003B0E50((u8*)receiver + 0x290, 0);
                func_002B39A0(receiver, 0);
            }
        }
        if (value > 0)
        {
            func_100D60(receiver);
        }
    }
    return receiver;
}

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
