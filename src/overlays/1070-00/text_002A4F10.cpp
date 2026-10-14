#include "include_asm.h"
#include "overlays/1070-00/text_002A4F10.h"

/** Partial callback interface with a method at offset 0x58. */
class FieldCallbackDispatch58
{
public:
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2c();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3c();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4c();
    virtual void slot50();
    virtual void slot54();
    virtual void callback(u32 first, u32 second);
};

extern "C" void func_002B0EE0(void* object, void* output);
extern "C" u8 D_173E50[];
extern "C" void* D_001B6620;
extern "C" void func_121E80(void* owner, void* object);

/** Partial receiver with a state byte at offset 0x60. */
typedef struct FieldState602B4510
{
    u8 unk00[0x60];
    u8 unk60;
} FieldState602B4510;

/** Partial state object with bit zero of a halfword at offset 0x6C. */
struct FieldFlagWord6C
{
    u8 unk00[0x6C];
    u16 unk6c;
};

/** Partial receiver containing a pointer to the state object at offset 0x1B4. */
struct FieldChildState1B4
{
    u8 unk00[0x1B4];
    FieldFlagWord6C* child;
};

/** Four 128-bit values beginning at source offset 0x150. */
struct FieldVectorCopySource150
{
    u8 unk00[0x150];
    unsigned __int128 values[4];
};

/** Four 128-bit destination values beginning at offset 0x60. */
struct FieldVectorCopyDestination60
{
    u8 unk00[0x2C];
    u32 unk2c;
    u8 unk30[0x30];
    unsigned __int128 values[4];
};

/** Partial output block with four reset bytes beginning at offset 0x130. */
struct FieldParticleOutput130
{
    u8 unk00[0x130];
    u8 state[4];
};

/** Partial particle state with an input pointer and value at offsets 0xA0/0xA4. */
struct FieldParticleInputA0
{
    u8 unk00[0x57];
    u8 unk57;
    u8 unk58[0x48];
    const u8* unka0;
    u32 unka4;
};

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002A4F10);

void func_002A5010(u8* object, float value)
{
    *(float*)(object + 0x28) = value;
}

void func_002A5020(u8* object, float value)
{
    *(float*)(object + 0x30) = value;
}

float func_002A5030(u8* object)
{
    return *(float*)(object + 0x30);
}

void func_002A5040(u8* object, u8 value)
{
    *(u8*)(object + 0x4D) = value;
}

u8 func_002A5050(u8* object)
{
    return *(u8*)(object + 0x4D);
}

void func_002A5060(u8* object, float value)
{
    *(float*)(object + 0x34) = value;
}

void func_002A5070(u8* object, u8 value)
{
    *(u8*)(object + 0x56) = value;
}

u8 func_002A5080(u8* object)
{
    return *(u8*)(object + 0x56);
}

void func_002A5090(u8* object, float value)
{
    *(float*)(object + 0x44) = value;
}

float func_002A50A0(u8* object)
{
    return *(float*)(object + 0x44);
}

float func_002A50B0(u8* object)
{
    return *(float*)(object + 0x28);
}

void func_002A50C0(u8* object, u32 value)
{
    *(u32*)(object + 0x48) = value;
}

u32 func_002A50D0(u8* object)
{
    return *(u32*)(object + 0x48);
}

void func_002A50E0(u8* object, u8 value)
{
    *(u8*)(object + 0x4F) = value;
}

void func_002A50F0(u8* object, u8 value)
{
    *(u8*)(object + 0x4E) = value;
}

void func_002A5100(u8* object, u32 value)
{
    *(u32*)(object + 0x50) = value;
}

u32 func_002A5110(u8* object)
{
    return *(u32*)(object + 0x50);
}

void func_002A5120(u8* object, u8 value)
{
    *(u8*)(object + 0x55) = value;
}

void func_002A5130(u8* object, float value)
{
    *(float*)(object + 0x3C) = value;
}

void func_002A5140(u8* object, u8 value)
{
    *(u8*)(object + 0x54) = value;
}

void func_002A5150(u8* object, float value)
{
    *(float*)(object + 0x40) = value;
}

void func_002A5160(void* receiver, const u8* input, u32 value)
{
	FieldParticleInputA0* object = (FieldParticleInputA0*)receiver;
    object->unka0 = input;
    object->unka4 = value;
    if (*object->unka0 == 1)
    {
        object->unk57 = 1;
    }
    else
    {
        object->unk57 = 0;
    }
}

void func_002A51A0(u8* object, u32 enabled)
{
    *(u32*)(object + 0xA0) = 0;
    *(u32*)(object + 0xA4) = 0;
    if (enabled != 0)
    {
        object[0x57] = 1;
    }
    else
    {
        object[0x57] = 0;
    }
}

void func_002A51D0(u8* object, float value)
{
    *(float*)(object + 0x38) = value;
}

void func_002A51E0(void* object)
{
}

s32 func_002A51F0(void* object)
{
    return 0;
}

void func_002A5200(void* object)
{
}

s32 func_002A5210(void* object)
{
    return 0;
}

void func_002A5220(void* destination, const void* source)
{
    FieldVectorCopyDestination60* output = (FieldVectorCopyDestination60*)destination;
    const FieldVectorCopySource150* input = (const FieldVectorCopySource150*)source;
    output->unk2c = 0;
    output->values[0] = input->values[0];
    output->values[1] = input->values[1];
    output->values[2] = input->values[2];
    output->values[3] = input->values[3];
}

void func_002A5250(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002A5260);

s32 func_002A7D30(void* object)
{
    return 1;
}

u8* func_002A7D40(u8* object, s32 index)
{
    u8* entry = *(u8**)(object + 0x14) + index * 96;
    if (entry != 0)
    {
        entry += 0x30;
    }
    return entry;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002A7D70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002A8180);

void func_002A8280(u8* object, float value)
{
    *(float*)(object + 0x28) = value;
}

void func_002A8290(u8* object, float value)
{
    *(float*)(object + 0x30) = value;
}

float func_002A82A0(u8* object)
{
    return *(float*)(object + 0x30);
}

void func_002A82B0(u8* object, u8 value)
{
    *(u8*)(object + 0x4D) = value;
}

u8 func_002A82C0(u8* object)
{
    return *(u8*)(object + 0x4D);
}

void func_002A82D0(u8* object, float value)
{
    *(float*)(object + 0x34) = value;
}

void func_002A82E0(u8* object, u8 value)
{
    *(u8*)(object + 0x56) = value;
}

u8 func_002A82F0(u8* object)
{
    return *(u8*)(object + 0x56);
}

void func_002A8300(u8* object, float value)
{
    *(float*)(object + 0x44) = value;
}

float func_002A8310(u8* object)
{
    return *(float*)(object + 0x44);
}

float func_002A8320(u8* object)
{
    return *(float*)(object + 0x28);
}

void func_002A8330(u8* object, u32 value)
{
    *(u32*)(object + 0x48) = value;
}

u32 func_002A8340(u8* object)
{
    return *(u32*)(object + 0x48);
}

void func_002A8350(u8* object, u8 value)
{
    *(u8*)(object + 0x4F) = value;
}

void func_002A8360(u8* object, u8 value)
{
    *(u8*)(object + 0x4E) = value;
}

void func_002A8370(u8* object, u32 value)
{
    *(u32*)(object + 0x50) = value;
}

u32 func_002A8380(u8* object)
{
    return *(u32*)(object + 0x50);
}

void func_002A8390(u8* object, u8 value)
{
    *(u8*)(object + 0x55) = value;
}

void func_002A83A0(u8* object, float value)
{
    *(float*)(object + 0x3C) = value;
}

void func_002A83B0(u8* object, u8 value)
{
    *(u8*)(object + 0x54) = value;
}

void func_002A83C0(u8* object, float value)
{
    *(float*)(object + 0x40) = value;
}

void func_002A83D0(void* receiver, const u8* input, u32 value)
{
    FieldParticleInputA0* object = (FieldParticleInputA0*)receiver;
    object->unka0 = input;
    object->unka4 = value;
    if (*object->unka0 == 1)
    {
        object->unk57 = 1;
    }
    else
    {
        object->unk57 = 0;
    }
}

void func_002A8410(u8* object, u32 enabled)
{
    *(u32*)(object + 0xA0) = 0;
    *(u32*)(object + 0xA4) = 0;
    if (enabled != 0)
    {
        object[0x57] = 1;
    }
    else
    {
        object[0x57] = 0;
    }
}

void func_002A8440(u8* object, float value)
{
    *(float*)(object + 0x38) = value;
}

void func_002A8450(void* object)
{
}

s32 func_002A8460(void* object)
{
    return 0;
}

void func_002A8470(void* object)
{
}

s32 func_002A8480(void* object)
{
    return 0;
}

u8* func_002A8490(u8* object, s32 index)
{
    return *(u8**)(object + 0x14) + index * 368;
}

u8* func_002A84B0(u8* object, s32 row, s32 column)
{
    s32 width = *(s32*)(object + 0x10) - 1;
    u8* data = *(u8**)(object + 0x20);
    return data + (row * width + column) * 64;
}

u32 func_002A84D0(u8* object)
{
    return *(u32*)(object + 0x1C);
}

u32 func_002A84E0(u8* object)
{
    return *(u32*)(object + 0xC);
}

u32 func_002A84F0(u8* object)
{
    return *(u32*)(object + 0x10);
}

s32 func_002A8500(void* object)
{
    return 63;
}

s32 func_002A8510(u8* object)
{
    return *(u32*)(object + 0x14) != 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", __ct__16FieldClass173A80Fv);

u8* func_002A8580(u8* object, s32 index)
{
    return *(u8**)(object + 0x14) + index * 288;
}

u8* func_002A85A0(u8* object, s32 row, s32 column)
{
    s32 width = *(s32*)(object + 0x10) - 1;
    u8* data = *(u8**)(object + 0x20);
    return data + (row * width + column) * 64;
}

u32 func_002A85C0(u8* object)
{
    return *(u32*)(object + 0x1C);
}

u32 func_002A85D0(u8* object)
{
    return *(u32*)(object + 0xC);
}

u32 func_002A85E0(u8* object)
{
    return *(u32*)(object + 0x10);
}

s32 func_002A85F0(void* object)
{
    return 47;
}

s32 func_002A8600(u8* object)
{
    return *(u32*)(object + 0x14) != 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", __ct__16FieldClass1739B0Fv);

u8* func_002A8670(u8* object, s32 index)
{
    return *(u8**)(object + 0x14) + index * 176;
}

u8* func_002A8690(u8* object, s32 row, s32 column)
{
    s32 width = *(s32*)(object + 0x10) - 1;
    u8* data = *(u8**)(object + 0x20);
    return data + (row * width + column) * 64;
}

u32 func_002A86B0(u8* object)
{
    return *(u32*)(object + 0x1C);
}

u32 func_002A86C0(u8* object)
{
    return *(u32*)(object + 0xC);
}

u32 func_002A86D0(u8* object)
{
    return *(u32*)(object + 0x10);
}

s32 func_002A86E0(void* object)
{
    return 39;
}

s32 func_002A86F0(u8* object)
{
    return *(u32*)(object + 0x14) != 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", __ct__16FieldClass1738E0Fv);

u8* func_002A8760(u8* object, s32 index)
{
    return *(u8**)(object + 0x14) + index * 144;
}

u8* func_002A8780(u8* object, s32 row, s32 column)
{
    s32 width = *(s32*)(object + 0x10) - 1;
    u8* data = *(u8**)(object + 0x20);
    return data + (row * width + column) * 64;
}

u32 func_002A87A0(u8* object)
{
    return *(u32*)(object + 0x1C);
}

u32 func_002A87B0(u8* object)
{
    return *(u32*)(object + 0xC);
}

u32 func_002A87C0(u8* object)
{
    return *(u32*)(object + 0x10);
}

s32 func_002A87D0(void* object)
{
    return 35;
}

s32 func_002A87E0(u8* object)
{
    return *(u32*)(object + 0x14) != 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", __ct__16FieldClass173810Fv);

u8* func_002A8850(u8* object, s32 index)
{
    return *(u8**)(object + 0x14) + index * 96;
}

u8* func_002A8870(u8* object, s32 row, s32 column)
{
    s32 width = *(s32*)(object + 0x10) - 1;
    u8* data = *(u8**)(object + 0x20);
    return data + (row * width + column) * 64;
}

u32 func_002A8890(u8* object)
{
    return *(u32*)(object + 0x1C);
}

u32 func_002A88A0(u8* object)
{
    return *(u32*)(object + 0xC);
}

u32 func_002A88B0(u8* object)
{
    return *(u32*)(object + 0x10);
}

s32 func_002A88C0(void* object)
{
    return 33;
}

s32 func_002A88D0(u8* object)
{
    return *(u32*)(object + 0x14) != 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002A88E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002A8E50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002A8E90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", __dt__16FieldClass173810Fv);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002A8FF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002A9560);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002A95B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002A9630);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", __dt__16FieldClass1738E0Fv);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002A97A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002A9D10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002A9D60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002A9DF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", __dt__16FieldClass1739B0Fv);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002A9F70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002AA4E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002AA540);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002AA5E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", __dt__16FieldClass173A80Fv);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002AA770);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002AACE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002AAD50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002AAE00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002AAEC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002AAF90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002AB730);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002AB800);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002ABFA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002AC070);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002AC850);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002AC920);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002AD0C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002AD190);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002AD260);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002AD7B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002ADE30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002AE630);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002AE710);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002AEE50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002AEF40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002AF050);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B05D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", __dt__16FieldClass1736B0Fv);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", __ct__16FieldClass1736B0Fv);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B07F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B0850);

void func_002B0920(void* destination, const void* source)
{
    FieldVectorCopyDestination60* output = (FieldVectorCopyDestination60*)destination;
    const FieldVectorCopySource150* input = (const FieldVectorCopySource150*)source;
    output->unk2c = 0;
    output->values[0] = input->values[0];
    output->values[1] = input->values[1];
    output->values[2] = input->values[2];
    output->values[3] = input->values[3];
}

void func_002B0950(void* object, const void* source)
{
    u32* destinationWords = (u32*)object;
    const u32* sourceWords = (const u32*)source;
    destinationWords[3] = sourceWords[3];
    destinationWords[4] = sourceWords[4];
    ((FieldCallbackDispatch58*)object)->callback(destinationWords[3], destinationWords[4]);
}

void func_002B0990(void* object, const void* source)
{
    u32* destinationWords = (u32*)object;
    const u32* sourceWords = (const u32*)source;
    destinationWords[3] = sourceWords[3];
    destinationWords[4] = sourceWords[4];
    ((FieldCallbackDispatch58*)object)->callback(destinationWords[3], destinationWords[4]);
}

void func_002B09D0(void* object, const void* source)
{
    u32* destinationWords = (u32*)object;
    const u32* sourceWords = (const u32*)source;
    destinationWords[3] = sourceWords[3];
    destinationWords[4] = sourceWords[4];
    ((FieldCallbackDispatch58*)object)->callback(destinationWords[3], destinationWords[4]);
}

void func_002B0A10(void* object, const void* source)
{
    u32* destinationWords = (u32*)object;
    const u32* sourceWords = (const u32*)source;
    destinationWords[3] = sourceWords[3];
    destinationWords[4] = sourceWords[4];
    ((FieldCallbackDispatch58*)object)->callback(destinationWords[3], destinationWords[4]);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B0A50);

void func_002B0A80(void* object, void* output)
{
    FieldParticleOutput130* state = (FieldParticleOutput130*)output;
    state->state[0] = 0;
    state->state[2] = 0;
    state->state[1] = 0;
    state->state[3] = 0;
    func_002B0EE0(object, output);
}

void func_002B0AB0(void* object)
{
}

s32 func_002B0AC0(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B0AD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B0EE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B0FE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B1160);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B1330);

void func_002B1B10(void* object)
{
}

s32 func_002B1B20(void* object)
{
    return 0;
}

void func_002B1B30(void* object)
{
}

s32 func_002B1B40(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B1B50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B1CD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B1EA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B2020);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B21F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B2370);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B2540);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B25A0);

float func_002B2680(void* object)
{
    return 1.0f;
}

float func_002B2690(void* object)
{
    return 1.0f;
}

float func_002B26A0(void* object)
{
    return 1.0f;
}

float func_002B26B0(void* object)
{
    return 1.0f;
}

void func_002B26C0(void* object, const void* source)
{
    u32* destinationWords = (u32*)object;
    const u32* sourceWords = (const u32*)source;
    destinationWords[3] = sourceWords[3];
    destinationWords[4] = sourceWords[4];
    ((FieldCallbackDispatch58*)object)->callback(destinationWords[3], destinationWords[4]);
}

float func_002B2700(void* object)
{
    return 1.0f;
}

/**
 * @brief Initialize the receiver, then pass it to the shared owner.
 * @param object Receiver to initialize and process.
 */
void func_002B2710(void* object)
{
    func_4D7EB0(object);
    func_121E80(D_001B6620, object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B2740);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B28C0);

s32 func_002B2950(FieldResourceList14* object, s32 first, s32 second)
{
    FieldListNode* node = &object->unk14;
    s32 count = 0;
    for (;;)
    {
        node = node->next;
        if (&object->unk14 == node)
        {
            break;
        }
        FieldResourceListEntry* entry = (FieldResourceListEntry*)node;
        if (entry->unk49_1 &&
            (((entry->unk1c == 0x43484152 || entry->unk1c == 0x41545243) &&
              first == (u16)entry->unk20) ||
             (entry->unk1c == 0x414E494D && second == (u16)entry->unk20)))
        {
            count++;
        }
    }
    return count;
}

void func_002B29F0(FieldResourceList14* object, s32 first, s32 second)
{
    FieldListNode* node = &object->unk14;
    for (;;)
    {
        node = node->next;
        if (&object->unk14 == node)
        {
            break;
        }
        FieldResourceListEntry* entry = (FieldResourceListEntry*)node;
        u8 enabled = entry->unk49_1;
        if (enabled && (enabled ? entry->unk49_3 : 1) &&
            (((entry->unk1c == 0x43484152 || entry->unk1c == 0x41545243) &&
              first == (u16)entry->unk20) ||
             (entry->unk1c == 0x414E494D && second == (u16)entry->unk20)))
        {
            entry->unk40--;
        }
    }
}

void func_002B2AB0(FieldResourceList14* object, s32 first, s32 second)
{
    FieldListNode* node = &object->unk14;
    for (;;)
    {
        node = node->next;
        if (&object->unk14 == node)
        {
            break;
        }
        FieldResourceListEntry* entry = (FieldResourceListEntry*)node;
        u8 enabled = entry->unk49_1;
        if (enabled && (enabled ? entry->unk49_3 : 1) &&
            (((entry->unk1c == 0x43484152 || entry->unk1c == 0x41545243) &&
              first == (u16)entry->unk20) ||
             (entry->unk1c == 0x414E494D && second == (u16)entry->unk20)))
        {
            entry->unk40++;
        }
    }
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B2B70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B2CC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B3010);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B3090);

u32 func_002B3140(FieldResourceList14* object, u32 kind, u32 key)
{
    FieldListNode* node = &object->unk14;
    FieldListNode* sentinel = node;
    for (;;)
    {
        node = node->next;
        if (!node || sentinel == node)
        {
            break;
        }
        FieldResourceListEntry* entry = (FieldResourceListEntry*)node;
        if (kind == entry->unk1c && key == entry->unk20)
        {
            return entry->unk49_1 ? entry->unk18 : entry->unk14;
        }
    }
    return 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B31C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B3310);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B33A0);

/**
 * @brief Initialize the receiver, then pass it to the shared owner.
 * @param object Receiver to initialize and process.
 */
void func_002B3410(void* object)
{
    func_4D7EB0(object);
    func_121E80(D_001B6620, object);
}

s32 func_002B3440(void* object)
{
    return 12;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B3450);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B3550);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B3560);

s32 func_002B3640(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B3650);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B3710);

extern "C" void func_002B3800(void* receiver)
{
    FieldChildState1B4* object = (FieldChildState1B4*)receiver;
    if (object->child != 0)
    {
        object->child->unk6c |= 1;
    }
}

extern "C" void func_002B3820(void* receiver)
{
    FieldChildState1B4* object = (FieldChildState1B4*)receiver;
    if (object->child != 0)
    {
        object->child->unk6c &= 0xFFFE;
    }
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B3840);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B3B80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B3C90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B43C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B44A0);

void func_002B4510(void* object)
{
    FieldState602B4510* state = (FieldState602B4510*)object;
    state->unk60 = 4;
}

s32 func_002B4520(void* object)
{
    return 14;
}

void func_002B4530(void* object)
{
}

void func_002B4540(void* object)
{
    func_121E80(D_001B6620, object);
}

void func_002B4560(void* object)
{
}

void func_002B4570(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B4580);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B4620);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B4680);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B4740);

FieldResetState24* func_002B47D0(FieldResetState24* object)
{
    object->unk24 = D_173E50;
    object->unk00 = 0;
    FieldResetState24* result = object;
    object->unk14 = 0;
    object->unk18 = 0;
    object->unk1c = 0;
    object->unk20 = 0;
    object->unk10 = 0;
    object->unk0e = 0;
    object->unk0c = 0;
    object->unk04 = 0;
    object->unk08 = 0;
    return result;
}

void func_002B4810(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B4820);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B4830);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B48C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B4910);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B4C50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002A4F10", func_002B4D20);
