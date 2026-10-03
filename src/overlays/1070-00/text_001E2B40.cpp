#include "include_asm.h"
#include "overlays/1070-00/text_001E2B40.h"

/** Minimal observed prefix containing the byte fields accessed here. */
struct FieldByteClear60
{
    u8 unk00[0x60];
    u8 unk60;
};

/** Minimal observed prefix containing the byte fields accessed here. */
struct FieldByteCopyA8
{
    u8 unk00[0x60];
    u8 unk60;
    u8 unk61[0x47];
    u8 unka8;
};

/** Observed signed input halfwords and the stored result bits. */
struct FieldHalfwordUpdate114
{
    u8 unk00[0xF0];
    u8 unkf0;
    u8 unkf1[0x1F];
    s16 unk110;
    s16 unk112;
    u16 unk114;
};

/** Minimal observed prefix containing the eight cleared word slots. */
struct FieldWordReset30
{
    u8 unk00[0x14];
    u32 unk14;
    u32 unk18;
    u32 unk1c;
    u32 unk20;
    u32 unk24;
    u32 unk28;
    u32 unk2c;
    u32 unk30;
};

/** Minimal observed prefix containing the accessed word bits. */
struct FieldWordAccess20
{
    u8 unk00[0x20];
    u32 unk20;
};

/** Minimal observed prefix containing the accessed word bits. */
struct FieldWordAccess24
{
    u8 unk00[0x24];
    u32 unk24;
};

/** Minimal observed prefix containing the accessed byte. */
struct FieldByteStore28
{
    u8 unk00[0x28];
    u8 unk28;
};

/** Minimal observed prefix containing the accessed byte. */
struct FieldSignedByteRead28
{
    u8 unk00[0x28];
    s8 unk28;
};

/** Minimal observed prefix containing the unsigned byte. */
struct FieldUnsignedByteAccess0C
{
    u8 unk00[0x0C];
    u8 unk0C;
};

/** Minimal observed prefix containing the unsigned byte. */
struct FieldUnsignedByteAccess08
{
    u8 unk00[0x08];
    u8 unk08;
};

/** Minimal observed prefix containing the unsigned halfword. */
struct FieldUnsignedHalfwordAccess0A
{
    u8 unk00[0x0A];
    u16 unk0A;
};

/** Minimal observed prefix containing the accessed word. */
struct FieldWordAccess98
{
    u8 unk00[0x98];
    u32 unk98;
};

/** Minimal observed prefix containing the accessed word. */
struct FieldWordAccess9C
{
    u8 unk00[0x9C];
    u32 unk9C;
};

/** Minimal observed prefix containing the accessed word. */
struct FieldWordAccess04
{
    u8 unk00[0x04];
    u32 unk04;
};

/** Minimal observed prefix containing the accessed word. */
struct FieldWordRead10
{
    u8 unk00[0x10];
    u32 unk10;
};

/** Minimal observed prefix containing the unsigned byte. */
struct FieldUnsignedByteAccess0D
{
    u8 unk00[0x0D];
    u8 unk0D;
};

/** Minimal observed prefix containing the unsigned byte. */
struct FieldByteStore12C
{
    u8 unk00[0x12C];
    u8 unk12C;
};

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E2B40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E2B80);

s32 func_001E2C20(void* object)
{
    return 4;
}

void func_001E2C30(void* object)
{
}

/**
 * @brief Copy an aligned 16-byte value to offset 0x20.
 * @param object Receiver containing the aligned destination value.
 * @param source Aligned value to copy.
 */
void func_001E2C40(FieldCopy2C40* object, const unsigned __int128* source)
{
    object->unk20 = *source;
}

void func_001E2C50(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E2C60);

void func_001E2D20(void* object)
{
}

void func_001E2D30(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E2D40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E2D90);

void func_001E2DD0(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E2DE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E2E00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E2E30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E2E80);

void func_001E2F20(FieldWordStateD4* object, u32 value)
{
    object->unkd4 = value;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E2F30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E2FC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E3030);

s32 func_001E3090(void* object)
{
    return 3;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E30A0);

void func_001E30D0(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E30E0);

u8 func_001E3660(const FieldByteState14* object)
{
    return object->unk14;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E3670);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E3A70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E3AB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E40E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E41C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E4310);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E4390);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E43F0);

void func_001E4440(void* object)
{
}

s32 func_001E4450(void* object)
{
    return 3;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E4460);

void func_001E4490(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E44A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E44B0);

void* func_001E4540(void* object)
{
    return (u8*)object + 0x90;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E4550);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E45F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E46F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E4790);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E4820);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E48B0);

void func_001E4A00(unsigned __int128* first, unsigned __int128* second, const unsigned __int128* source)
{
    unsigned __int128 value = *source;
    *second = value;
    *first = value;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E4A10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E4A50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E4D90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E4EB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E4F90);

/**
 * @brief Copy an aligned 16-byte value to offset 0x20.
 * @param object Receiver containing the aligned destination value.
 * @param source Aligned value to copy.
 */
void func_001E5000(FieldCopy5000* object, const unsigned __int128* source)
{
    object->unk20 = *source;
}

/**
 * @brief Copy an aligned 16-byte value to offset 0x20.
 * @param object Receiver containing the aligned destination value.
 * @param source Aligned value to copy.
 */
void func_001E5010(FieldCopy5010* object, const unsigned __int128* source)
{
    object->unk20 = *source;
}

/**
 * @brief Store three floating-point values and set the following value to one.
 * @param object Receiver whose values are initialized.
 * @param first Value to store at offset 0x20.
 * @param second Value to store at offset 0x24.
 * @param third Value to store at offset 0x28.
 */
void func_001E5020(FieldFloatValues20* object, float first, float second, float third)
{
    object->unk20 = first;
    object->unk24 = second;
    object->unk28 = third;
    object->unk2c = 1.0f;
}

void func_001E5040(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E5050);

s32 func_001E5070(void* object)
{
    return 8;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E5080);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E5250);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E52C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E5330);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E53D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E5440);

/**
 * @brief Set the update byte to one and copy an aligned 16-byte value.
 * @param object Receiver containing the update byte and destination value.
 * @param source Aligned value to copy.
 */
void func_001E5750(FieldCopy5750* object, const unsigned __int128* source)
{
    object->unk50 = 1;
    object->unk20 = *source;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E5770);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E5AF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E5B40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E5BB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E5C50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E5D10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E5DA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E5DC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E5E60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E5EE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E60B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E6280);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E6410);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E6C20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E6C80);

s32 func_001E6D10(void* object)
{
    return 1;
}

s32 func_001E6D20(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E6D30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E6D40);

void func_001E6D60(FieldWordState70* object, u32 value)
{
    object->unk70 = value;
}

void func_001E6D70(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E6D80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E6E30);

void func_001E7020(FieldKeyedFlagElement28* object, s32 value)
{
    object->unk1c = 0.0f;
    object->unk20 = 0;
    object->unk24 = (float)value;
    object->unk2c_0 = 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E7050);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E7110);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E7190);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E72D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E73D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E73E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E73F0);

s32 func_001E7480(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E7490);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E74C0);

void func_001E7600(void* object, s32 value)
{
    FieldWordReset30* state = (FieldWordReset30*)object;

    state->unk14 = 0;
    state->unk18 = 0;
    state->unk1c = 0;
    state->unk20 = 0;
    state->unk24 = 0;
    state->unk28 = 0;
    state->unk2c = 0;
    state->unk30 = 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E7630);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E7770);

s32 func_001E77E0(void* object)
{
    return 0;
}

s32 func_001E77F0(void* object)
{
    return 11;
}

s32 func_001E7800(void* object)
{
    return 1;
}

s32 func_001E7810(void* object)
{
    return 0;
}

s32 func_001E7820(void* object)
{
    return 0;
}

s32 func_001E7830(const FieldWordState704* object)
{
    return object->unk704 != 0;
}

void* func_001E7840(void* object)
{
    return (u8*)object + 0x79C;
}

u8 func_001E7850(const FieldByteState794* object)
{
    return object->unk794;
}

s32 func_001E7860(void* object)
{
    return 0;
}

void func_001E7870(FieldByteFlagState210* object, u32 value)
{
    object->unk210 = value;
    object->unk59d_3 = 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E7890);

void* func_001E78E0(void* object)
{
    return (u8*)object + 0x90;
}

void* func_001E78F0(void* object)
{
    return (u8*)object + 0x1D0;
}

void* func_001E7900(void* object)
{
    return (u8*)object + 0x1E0;
}

void* func_001E7910(void* object)
{
    return (u8*)object + 0x1F0;
}

void func_001E7920(FieldCopy7920* object, const unsigned __int128* source)
{
    object->unk50 = 1;
    object->unk20 = *source;
}

void func_001E7940(FieldFloatUpdate7940* object, float first, float second, float third)
{
    object->unk50 = 1;
    object->unk20 = first;
    object->unk24 = second;
    object->unk28 = third;
    object->unk2c = 1.0f;
}

void func_001E7960(FieldFloatUpdate7960* object, float first, float second, float third, float fourth)
{
    object->unk50 = 1;
    object->unk30 = first;
    object->unk34 = second;
    object->unk38 = third;
    object->unk3c = fourth;
}

void func_001E7980(FieldCopy7980* object, const unsigned __int128* source)
{
    object->unk50 = 1;
    object->unk30 = *source;
}

void func_001E79A0(FieldCopy79A0* object, const unsigned __int128* source)
{
    object->unk50 = 1;
    object->unk30 = *source;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E79C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E79F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E7A20);

void func_001E7A60(FieldCopy7A60* object, const unsigned __int128* source)
{
    object->unk50 = 1;
    object->unk40 = *source;
}

void func_001E7A80(FieldCopy7A80* object, const unsigned __int128* source)
{
    object->unk50 = 1;
    object->unk40 = *source;
}

void func_001E7AA0(FieldFloatUpdate7AA0* object, float first, float second, float third)
{
    object->unk50 = 1;
    object->unk40 = first;
    object->unk44 = second;
    object->unk48 = third;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E7AC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E8260);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E82C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E83A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E8430);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E84B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E8A20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E8A70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E8C40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E8E80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E95E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E9650);

s32 func_001E96B0(void* object)
{
    return 0;
}

s32 func_001E96C0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E96D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E96E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E96F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E9740);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E97A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E9850);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E9860);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E9870);

void func_001E9AE0(void* object)
{
}

s32 func_001E9AF0(void* object)
{
    return 2;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E9B00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E9B70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E9C70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E9DE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001E9F30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EA040);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EA100);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EA1F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EA280);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EA2F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EA7B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EA970);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EAA80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EAD20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EAD50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EAE30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EB2D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EB440);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EB4A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EB530);

s32 func_001EB5A0(void* object)
{
    return 16;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EB5B0);

void func_001EB5E0(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EB5F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EB690);

u16 func_001EB720(const FieldHalfwordState94* object)
{
    return object->unk94;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EB730);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EB8B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EB9A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EBA50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EBB00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EBB90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EBBF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EBC50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EBCC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EBD40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EBDC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EBE20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EBE90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EBFA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EC010);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EC1B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EC280);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EC300);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EC380);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EC3F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EC4D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EC500);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EC700);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EC820);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EC910);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EC980);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001ECAA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001ECB30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001ECB90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001ECD70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001ECE10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001ECEA0);

void func_001ED200(void* object)
{
    FieldHalfwordUpdate114* state = (FieldHalfwordUpdate114*)object;

    state->unk114 = state->unk110 * state->unkf0 + state->unk112;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001ED220);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001ED4D0);

void func_001ED580(FieldDimensionState* object, float first, float second)
{
    object->unkfc = first;
    object->unk100 = second;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001ED590);

void func_001ED5A0(FieldDimensionState* object, s32 first, s32 second)
{
    object->unkf0 = first;
    object->unkf1 = second;
    object->unk10c = object->unkf0 * object->unkf1 - 1;
}

void func_001ED5C0(FieldByteStateAD* object, u8 value)
{
    object->unkad = value;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001ED5D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001ED600);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001ED680);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001ED750);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001ED7F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001ED8E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001ED9A0);

void func_001EDA00(void* object)
{
    FieldByteClear60* state = (FieldByteClear60*)object;

    state->unk60 = 0;
}

void func_001EDA10(void* object)
{
}

s32 func_001EDA20(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EDA30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EDA50);

void func_001EDA60(void* object)
{
}

s32 func_001EDA70(void* object)
{
    return 0;
}

void func_001EDA80(void* object)
{
}

void func_001EDA90(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EDAA0);

void func_001EDB10(void* object)
{
}

void func_001EDB20(void* object)
{
    FieldByteCopyA8* state = (FieldByteCopyA8*)object;

    state->unk60 = state->unka8;
}

s32 func_001EDB30(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EDB40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EDB90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EDBA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EDBB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EDBC0);

s32 func_001EDBD0(const FieldTimeState* object)
{
    s32 value = 0;
    value += object->hours * 3600;
    value += object->minutes * 60;
    value += object->seconds;
    return value;
}

void func_001EDC10(FieldTimeState* object, u32 value)
{
    object->unk00 = value;
}

void func_001EDC20(FieldTimeState* object, u32 seconds)
{
    if (seconds == 0)
    {
        object->unk00 = object->hours = object->minutes = object->seconds = 0;
    }
    else
    {
        object->seconds = seconds % 60;
        object->minutes = (seconds / 60) % 60;
        if (seconds >= 3600000)
        {
            object->hours = 999;
            object->minutes = 59;
            object->seconds = 59;
        }
        else
        {
            object->hours = seconds / 3600;
        }
    }
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EDCE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EDD00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EDDB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EDE60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EDF50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EE010);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EE110);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EE160);

void func_001EE190(void* object, u32 value)
{
    FieldWordAccess20* state = (FieldWordAccess20*)object;

    state->unk20 = value;
}

u32 func_001EE1A0(const void* object)
{
    const FieldWordAccess20* state = (const FieldWordAccess20*)object;

    return state->unk20;
}

void func_001EE1B0(void* object, u32 value)
{
    FieldWordAccess24* state = (FieldWordAccess24*)object;

    state->unk24 = value;
}

u32 func_001EE1C0(const void* object)
{
    const FieldWordAccess24* state = (const FieldWordAccess24*)object;

    return state->unk24;
}

void func_001EE1D0(void* object, u32 value)
{
    FieldByteStore28* state = (FieldByteStore28*)object;

    state->unk28 = value;
}

s32 func_001EE1E0(const void* object)
{
    const FieldSignedByteRead28* state = (const FieldSignedByteRead28*)object;

    return state->unk28;
}

s32 func_001EE1F0(void* object)
{
    return 0;
}

s32 func_001EE200(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EE210);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EE220);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EE230);

s32 func_001EE240(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EE250);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EE260);

void func_001EE270(void* object)
{
}

void func_001EE280(void* object)
{
}

void func_001EE290(void* object)
{
}

s32 func_001EE2A0(void* object)
{
    return 0;
}

s32 func_001EE2B0(void* object)
{
    return 0;
}

s32 func_001EE2C0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EE2D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EE370);

void func_001EE3D0(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EE3E0);

void func_001EE490(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EE4A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EE530);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EE570);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EE5E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EE670);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EE7D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EE800);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EE8A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EE930);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EE9D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EEA50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EEB10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EEBA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EEC20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EEC70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EECE0);

void func_001EED50(void* object, u32 value)
{
    FieldUnsignedByteAccess0C* state = (FieldUnsignedByteAccess0C*)object;

    state->unk0C = value;
}

u32 func_001EED60(const void* object)
{
    const FieldUnsignedByteAccess0C* state = (const FieldUnsignedByteAccess0C*)object;

    return state->unk0C;
}

void func_001EED70(void* object, u32 value)
{
    FieldUnsignedByteAccess08* state = (FieldUnsignedByteAccess08*)object;

    state->unk08 = value;
}

u32 func_001EED80(const void* object)
{
    const FieldUnsignedByteAccess08* state = (const FieldUnsignedByteAccess08*)object;

    return state->unk08;
}

void func_001EED90(void* object, u32 value)
{
    FieldUnsignedHalfwordAccess0A* state = (FieldUnsignedHalfwordAccess0A*)object;

    state->unk0A = value;
}

u32 func_001EEDA0(const void* object)
{
    const FieldUnsignedHalfwordAccess0A* state = (const FieldUnsignedHalfwordAccess0A*)object;

    return state->unk0A;
}

void func_001EEDB0(void* object, u32 value)
{
    FieldWordAccess98* state = (FieldWordAccess98*)object;

    state->unk98 = value;
}

u32 func_001EEDC0(const void* object)
{
    const FieldWordAccess98* state = (const FieldWordAccess98*)object;

    return state->unk98;
}

void func_001EEDD0(void* object, u32 value)
{
    FieldWordAccess9C* state = (FieldWordAccess9C*)object;

    state->unk9C = value;
}

u32 func_001EEDE0(const void* object)
{
    const FieldWordAccess9C* state = (const FieldWordAccess9C*)object;

    return state->unk9C;
}

void func_001EEDF0(void* object, u32 value)
{
    FieldWordAccess04* state = (FieldWordAccess04*)object;

    state->unk04 = value;
}

u32 func_001EEE00(const void* object)
{
    const FieldWordAccess04* state = (const FieldWordAccess04*)object;

    return state->unk04;
}

u32 func_001EEE10(const void* object)
{
    const FieldWordRead10* state = (const FieldWordRead10*)object;

    return state->unk10;
}

void func_001EEE20(void* object)
{
}

void func_001EEE30(void* object)
{
}

void func_001EEE40(void* object)
{
}

void func_001EEE50(void* object)
{
}

void func_001EEE60(void* object)
{
}

void func_001EEE70(void* object)
{
}

void func_001EEE80(void* object)
{
}

void func_001EEE90(void* object)
{
}

void func_001EEEA0(void* object)
{
}

void func_001EEEB0(void* object)
{
}

void func_001EEEC0(void* object)
{
}

void func_001EEED0(void* object)
{
}

void func_001EEEE0(void* object)
{
}

void func_001EEEF0(void* object)
{
}

void func_001EEF00(void* object)
{
}

void func_001EEF10(void* object)
{
}

void func_001EEF20(void* object)
{
}

void func_001EEF30(void* object)
{
}

void func_001EEF40(void* object)
{
}

void func_001EEF50(void* object)
{
}

s32 func_001EEF60(void* object)
{
    return 0;
}

s32 func_001EEF70(void* object)
{
    return 0;
}

s32 func_001EEF80(void* object)
{
    return 0;
}

s32 func_001EEF90(void* object)
{
    return 0;
}

s32 func_001EEFA0(void* object)
{
    return 0;
}

s32 func_001EEFB0(void* object)
{
    return 0;
}

s32 func_001EEFC0(void* object)
{
    return 0;
}

s32 func_001EEFD0(void* object)
{
    return 0;
}

s32 func_001EEFE0(void* object)
{
    return 0;
}

s32 func_001EEFF0(void* object)
{
    return 0;
}

void func_001EF000(void* object)
{
}

void func_001EF010(void* object)
{
}

u32 func_001EF020(const void* object)
{
    const FieldUnsignedByteAccess0D* state = (const FieldUnsignedByteAccess0D*)object;

    return state->unk0D;
}

void func_001EF030(void* object, u32 value)
{
    FieldUnsignedByteAccess0D* state = (FieldUnsignedByteAccess0D*)object;

    state->unk0D = value;
}

void func_001EF040(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EF050);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EF0E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EF170);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EF330);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EF390);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EF3C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EF410);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EF4F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EF580);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EF5F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EF660);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EF6C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EF770);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EF8E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EF980);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EF9C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EFA40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EFAB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EFB10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EFD30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EFD70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001EFFA0);

void func_001F00D0(void* object, u32 value)
{
    FieldByteStore12C* state = (FieldByteStore12C*)object;

    state->unk12C = value;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F00E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F0470);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F04D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F0540);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F0610);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F07E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F0930);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F0AF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F0B90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F0CC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F1220);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F1290);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F1380);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F1500);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F1520);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F1540);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F15C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F16F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F19D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F1E10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F1E80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F1EE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F1FC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F20A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F2180);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F22F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F2440);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F25B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F28F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F2950);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F29D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001E2B40", func_001F2AC0);
