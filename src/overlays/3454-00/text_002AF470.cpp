#include "include_asm.h"
#include "overlays/3454-00/text_002AF470.h"

extern "C" void func_002B3100(void* object, void* context);
extern "C" void func_003776F0(void* first, void* second, void* third, void* fourth, u32 flags);
struct ObjectPointer04
{
    u32 unk00;
    void* unk04;
};

extern "C" u32 func_473390(u32 value, const void* data);
extern "C" u32 func_473940(u32 value, const void* data);
extern "C" void func_002A1390(void* object);
extern "C" void func_002919A0(void* object);
extern "C" const u8 D_3E0878[];
extern "C" const u8 D_3E06A8[];
extern "C" const u8 D_3E07B8[];

struct N57Owner2F0C
{
    u8 unk00[0x50];
    u32 unk50;
    u8 unk54[0x2EB8];
    u32 unk2f0c;
};

struct N57Owner2F24
{
    u8 unk00[0x50];
    u32 unk50;
    u8 unk54[0x2ED0];
    u32 unk2f24;
};

typedef struct ConstantByteSetterOwnertext_002AF470
{
    u8 unk00[0x4];
    u8 unk04;
    u8 unk05[0x5B];
    u8 unk60;
    u8 unk61[0xAC];
    u8 unk10d;
    u8 unk10e[0x395];
    u8 unk4a3;
} ConstantByteSetterOwnertext_002AF470;



typedef struct HalfwordGetterOwnertext_002AF470
{
    u8 unk00[0x18];
    s16 unk18;
} HalfwordGetterOwnertext_002AF470;



typedef struct ByteGetterOwnertext_002AF470
{
    u8 unk00[0xCD1];
    u8 unkcd1;
    u8 unkcd2[0x8];
    u8 unkcda;
    u8 unkcdb[0x4];
    u8 unkcdf;
    u8 unkce0[0x7];
    u8 unkce7;
    u8 unkce8[0x22E];
    u8 unkf16;
} ByteGetterOwnertext_002AF470;



typedef struct WordGetterOwnertext_002AF470
{
    u8 unk00[0xD30];
    u32 unkd30;
    u32 unkd34;
    u32 unkd38;
} WordGetterOwnertext_002AF470;

typedef struct NestedWordResultOwnertext_002AF470
{
    u8 unk00[0x50];
    u32 unk50;
    u8 unk54[0x418];
    u32 unk46c;
} NestedWordResultOwnertext_002AF470;


INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002AF470);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002AF4B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002AF540);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002AF5E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002AF6B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002AF710);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002AF910);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002AF950);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002AFA60);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002AFB00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B0020);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B0140);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B0240);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B02F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B0350);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B03B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B0410);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B0530);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B0650);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B0760);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B07C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B0820);

void func_002B0880(void* object)
{
}

s32 func_002B0890(void* object)
{
    return 4;
}

void func_002B08A0(void* receiver)
{
    ObjectPointer04* object = (ObjectPointer04*)receiver;
    func_002B1380(object->unk04);
}

void func_002B08C0(void* receiver)
{
    ObjectPointer04* object = (ObjectPointer04*)receiver;
    func_002B1300(object->unk04);
}

void func_002B08E0(void* object)
{
}

/** Store 0x1 at receiver offset 0x10D. */
void func_002B08F0(void* object)
{
    ConstantByteSetterOwnertext_002AF470* receiver = (ConstantByteSetterOwnertext_002AF470*)object;
    receiver->unk10d = 0x1;
}

/** Store 0x1 at receiver offset 0x10D. */
void func_002B0900(void* object)
{
    ConstantByteSetterOwnertext_002AF470* receiver = (ConstantByteSetterOwnertext_002AF470*)object;
    receiver->unk10d = 0x1;
}

/** Store 0x1 at receiver offset 0x10D. */
void func_002B0910(void* object)
{
    ConstantByteSetterOwnertext_002AF470* receiver = (ConstantByteSetterOwnertext_002AF470*)object;
    receiver->unk10d = 0x1;
}

s32 func_002B0920(void* object)
{
    return 1;
}

struct N57Word14And178
{
    u8 unk00[0x14];
    u32 unk14;
    u8 unk18[0x160];
    u32 unk178;
};

/** Copy the word at receiver offset 0x178 to offset 0x14. */
void func_002B0930(void* object)
{
    N57Word14And178* receiver = (N57Word14And178*)object;
    receiver->unk14 = receiver->unk178;
}

void func_002B0940(void* object)
{
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B0950);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B0980);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B09B0);

s32 func_002B0AD0(void* object)
{
    return 4;
}

void func_002B0AE0(void* object)
{
}

struct SmallConditionalInput04
{
    u8 unk00[4];
    float unk04;
};

extern "C" s32 func_002B0AF0(void* object, const void* value, float* zero_output, float* small_output)
{
    const SmallConditionalInput04* state = (const SmallConditionalInput04*)value;
    if (!(state->unk04 <= 0.0f))
    {
        *zero_output = 0.0f;
        *small_output = 0.05f;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B0B30);

s32 func_002B0BC0(void* object)
{
    return 14;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B0BD0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B0C60);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B0C90);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B0D70);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B0D80);

/** Store 0x8 at receiver offset 0x60. */
void func_002B0E10(void* object)
{
    ConstantByteSetterOwnertext_002AF470* receiver = (ConstantByteSetterOwnertext_002AF470*)object;
    receiver->unk60 = 0x8;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B0E20);

void func_002B0EF0(u8* receiver, void* value1, void* value2, void* value3)
{
    u8* adjusted = receiver;
    if (adjusted != 0) {
        adjusted = adjusted + 0x290;
    }
    func_003776F0(receiver + 0x460, adjusted, value1, value2, 1);
}

/** Store 0x8 at receiver offset 0x60. */
void func_002B0F30(void* object)
{
    ConstantByteSetterOwnertext_002AF470* receiver = (ConstantByteSetterOwnertext_002AF470*)object;
    receiver->unk60 = 0x8;
}

/** Store 0x1 at receiver offset 0x4A3. */
void func_002B0F40(void* object)
{
    ConstantByteSetterOwnertext_002AF470* receiver = (ConstantByteSetterOwnertext_002AF470*)object;
    receiver->unk4a3 = 0x1;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B0F50);

/** Store 0x1 at receiver offset 0x4. */
void func_002B0FE0(void* object)
{
    ConstantByteSetterOwnertext_002AF470* receiver = (ConstantByteSetterOwnertext_002AF470*)object;
    receiver->unk04 = 0x1;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B0FF0);

/** Return the signed halfword at receiver offset 0x18. */
s16 func_002B1080(const void* object)
{
    const HalfwordGetterOwnertext_002AF470* receiver = (const HalfwordGetterOwnertext_002AF470*)object;
    return receiver->unk18;
}

void func_002B1090(void* object)
{
}

/** Return the word at receiver offset 0xD30. */
u32 func_002B10A0(const void* object)
{
    const WordGetterOwnertext_002AF470* receiver = (const WordGetterOwnertext_002AF470*)object;
    return receiver->unkd30;
}

/** Return the word at receiver offset 0xD34. */
u32 func_002B10B0(const void* object)
{
    const WordGetterOwnertext_002AF470* receiver = (const WordGetterOwnertext_002AF470*)object;
    return receiver->unkd34;
}

/** Return the word at receiver offset 0xD38. */
u32 func_002B10C0(const void* object)
{
    const WordGetterOwnertext_002AF470* receiver = (const WordGetterOwnertext_002AF470*)object;
    return receiver->unkd38;
}

/** Return the unsigned byte at receiver offset 0xCDF. */
u8 func_002B10D0(const void* object)
{
    const ByteGetterOwnertext_002AF470* receiver = (const ByteGetterOwnertext_002AF470*)object;
    return receiver->unkcdf;
}

/** Return the unsigned byte at receiver offset 0xCDA. */
u8 func_002B10E0(const void* object)
{
    const ByteGetterOwnertext_002AF470* receiver = (const ByteGetterOwnertext_002AF470*)object;
    return receiver->unkcda;
}

/** Return the unsigned byte at receiver offset 0xCD1. */
u8 func_002B10F0(const void* object)
{
    const ByteGetterOwnertext_002AF470* receiver = (const ByteGetterOwnertext_002AF470*)object;
    return receiver->unkcd1;
}

/** Return the unsigned byte at receiver offset 0xCE7. */
u8 func_002B1100(const void* object)
{
    const ByteGetterOwnertext_002AF470* receiver = (const ByteGetterOwnertext_002AF470*)object;
    return receiver->unkce7;
}

s32 func_002B1110(void* object)
{
    return 0;
}

s32 func_002B1120(void* object)
{
    return 0;
}

s32 func_002B1130(void* object)
{
    return 0;
}

void func_002B1140(void* object)
{
}

s32 func_002B1150(void* object)
{
    return 0;
}

s32 func_002B1160(void* object)
{
    return 0;
}

/** Return the unsigned byte at receiver offset 0xF16. */
u8 func_002B1170(const void* object)
{
    const ByteGetterOwnertext_002AF470* receiver = (const ByteGetterOwnertext_002AF470*)object;
    return receiver->unkf16;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B1180);

s32 func_002B11A0(void* object)
{
    return 0;
}

s32 func_002B11B0(void* object)
{
    return 0;
}

s32 func_002B11C0(void* object)
{
    return 0;
}

s32 func_002B11D0(void* object)
{
    return 0;
}

s32 func_002B11E0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B11F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B1300);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B1380);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B1410);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B1500);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B1510);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B1520);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B1530);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B1540);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B1550);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B1560);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B1570);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B1580);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B1590);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B15A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B15B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B15C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B15D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B15E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B15F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B1600);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B1610);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B1620);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B1630);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B1640);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B16E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B17D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B1CE0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B1DD0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B2050);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B22F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B2AF0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B2BA0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B2C30);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B2F00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B2F50);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B3100);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B3260);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B3340);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B3450);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B3610);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B3A20);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B3AB0);

void func_002B3BE0(u8* object, void* context)
{
    if (object[0xCD1] != 0) {
        if (object[0xCDF] == 0x21) {
            func_002B3100(object, context);
        }
    }
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B3C20);

struct FieldByte570
{
    u8 unk00[0x570];
    u8 value;
};

extern "C" void func_002B3D20(void* receiver)
{
    FieldByte570* object = (FieldByte570*)receiver;
    func_002919A0(receiver);
    object->value = 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B3D50);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B40C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B4380);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B4830);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B4A50);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B4BD0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B4EC0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B5090);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B5230);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B53F0);

void func_002B5490(void* receiver)
{
    N57Owner2F0C* object = (N57Owner2F0C*)receiver;
    func_002A1390(receiver);
    object->unk2f0c = func_473940(object->unk50, D_3E06A8);
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B54D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B5570);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B5690);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B5C60);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B5CF0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B5F10);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B5FB0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B60B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B6460);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B64D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B6950);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B6A60);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B7470);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B7510);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B7820);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B7B60);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B7C80);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B7DA0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B8150);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B8480);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B8B90);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B8D30);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B8DE0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B8E30);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B9900);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B99A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B9A60);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B9CC0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002B9F00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BA280);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BA350);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BA580);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BA6B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BA870);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BAAA0);

void func_002BAB10(void* receiver)
{
    N57Owner2F24* object = (N57Owner2F24*)receiver;
    func_002A1390(receiver);
    object->unk2f24 = func_473390(object->unk50, D_3E07B8);
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BAB50);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BABD0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BADB0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BAFF0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BB0B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BB1B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BC990);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BCA50);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BCA80);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BCAB0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BCB50);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BCC80);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BCCD0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BCD40);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BCEC0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BCF30);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BD0D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BD890);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BD950);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BD9A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BDAC0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BDE00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BDE50);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BDEA0);

void func_002BDF20(void* object)
{
    NestedWordResultOwnertext_002AF470* receiver = (NestedWordResultOwnertext_002AF470*)object;
    receiver->unk46c = func_473390(receiver->unk50, D_3E0878);
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BDF60);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BE170);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BE290);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BE3D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BE7E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BE8D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BE930);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BE9F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BEFF0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BF390);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002AF470", func_002BF3E0);
