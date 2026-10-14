#include "include_asm.h"
#include "overlays/lib/text_0047AE20.h"

typedef struct ByteGetterOwnertext_0047AE20
{
    u8 unk00[0x4D];
    u8 unk4d;
    u8 unk4e[0x8];
    u8 unk56;
} ByteGetterOwnertext_0047AE20;



typedef struct ByteSetterOwnertext_0047AE20
{
    u8 unk00[0x4D];
    u8 unk4d;
    u8 unk4e;
    u8 unk4f;
    u8 unk50[0x4];
    u8 unk54;
    u8 unk55;
    u8 unk56;
} ByteSetterOwnertext_0047AE20;



typedef struct WordSetterOwnertext_0047AE20
{
    u8 unk00[0x48];
    u32 unk48;
    u8 unk4c[0x4];
    u32 unk50;
} WordSetterOwnertext_0047AE20;



typedef struct WordGetterOwnertext_0047AE20
{
    u8 unk00[0xC];
    u32 unk0c;
    u32 unk10;
    u8 unk14[0x8];
    u32 unk1c;
    u8 unk20[0x28];
    u32 unk48;
    u8 unk4c[0x4];
    u32 unk50;
} WordGetterOwnertext_0047AE20;


typedef struct LibFloatFieldOwner0047AE20
{
    u8 unk00[0x28];
    float unk28;
    u8 unk2c[4];
    float unk30;
    float unk34;
    float unk38;
    float unk3c;
    float unk40;
    float unk44;
} LibFloatFieldOwner0047AE20;

/**
 * @brief Store the value at receiver offset 0x44.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047AE20(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk44 = value;
}

/** Return the float member at receiver offset 0x44. */
float func_0047AE30(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    return receiver->unk44;
}

/** Return the float member at receiver offset 0x28. */
float func_0047AE40(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    return receiver->unk28;
}

/** Store the word at receiver offset 0x48. */
void func_0047AE50(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = object;
    receiver->unk48 = value;
}

/** Return the word at receiver offset 0x48. */
u32 func_0047AE60(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk48;
}

/** Store the byte at receiver offset 0x4F. */
void func_0047AE70(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk4f = value;
}

/** Store the byte at receiver offset 0x4E. */
void func_0047AE80(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk4e = value;
}

/** Store the word at receiver offset 0x50. */
void func_0047AE90(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = object;
    receiver->unk50 = value;
}

/** Return the word at receiver offset 0x50. */
u32 func_0047AEA0(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk50;
}

/** Store the byte at receiver offset 0x55. */
void func_0047AEB0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk55 = value;
}

/**
 * @brief Store the value at receiver offset 0x3C.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047AEC0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk3c = value;
}

/** Store the byte at receiver offset 0x54. */
void func_0047AED0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk54 = value;
}

/**
 * @brief Store the value at receiver offset 0x40.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047AEE0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk40 = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047AEF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047AF30);

/**
 * @brief Store the value at receiver offset 0x38.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047AF60(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk38 = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047AF70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047AF80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047AF90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047AFA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047AFB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047AFE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047AFF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047B000);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047B030);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047B440);

/**
 * @brief Store the value at receiver offset 0x28.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047B540(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk28 = value;
}

/**
 * @brief Store the value at receiver offset 0x30.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047B550(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk30 = value;
}

/** Return the float member at receiver offset 0x30. */
float func_0047B560(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    return receiver->unk30;
}

/** Store the byte at receiver offset 0x4D. */
void func_0047B570(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk4d = value;
}

/** Return the unsigned byte at receiver offset 0x4D. */
u8 func_0047B580(const void* object)
{
    const ByteGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk4d;
}

/**
 * @brief Store the value at receiver offset 0x34.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047B590(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk34 = value;
}

/** Store the byte at receiver offset 0x56. */
void func_0047B5A0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk56 = value;
}

/** Return the unsigned byte at receiver offset 0x56. */
u8 func_0047B5B0(const void* object)
{
    const ByteGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk56;
}

/**
 * @brief Store the value at receiver offset 0x44.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047B5C0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk44 = value;
}

/** Return the float member at receiver offset 0x44. */
float func_0047B5D0(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    return receiver->unk44;
}

/** Return the float member at receiver offset 0x28. */
float func_0047B5E0(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    return receiver->unk28;
}

/** Store the word at receiver offset 0x48. */
void func_0047B5F0(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = object;
    receiver->unk48 = value;
}

/** Return the word at receiver offset 0x48. */
u32 func_0047B600(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk48;
}

/** Store the byte at receiver offset 0x4F. */
void func_0047B610(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk4f = value;
}

/** Store the byte at receiver offset 0x4E. */
void func_0047B620(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk4e = value;
}

/** Store the word at receiver offset 0x50. */
void func_0047B630(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = object;
    receiver->unk50 = value;
}

/** Return the word at receiver offset 0x50. */
u32 func_0047B640(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk50;
}

/** Store the byte at receiver offset 0x55. */
void func_0047B650(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk55 = value;
}

/**
 * @brief Store the value at receiver offset 0x3C.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047B660(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk3c = value;
}

/** Store the byte at receiver offset 0x54. */
void func_0047B670(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk54 = value;
}

/**
 * @brief Store the value at receiver offset 0x40.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047B680(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk40 = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047B690);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047B6D0);

/**
 * @brief Store the value at receiver offset 0x38.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047B700(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk38 = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047B710);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047B720);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047B730);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047B740);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047B750);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047B780);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047B790);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047B7A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047B7D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047BBE0);

/**
 * @brief Store the value at receiver offset 0x28.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047BCE0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk28 = value;
}

/**
 * @brief Store the value at receiver offset 0x30.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047BCF0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk30 = value;
}

/** Return the float member at receiver offset 0x30. */
float func_0047BD00(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    return receiver->unk30;
}

/** Store the byte at receiver offset 0x4D. */
void func_0047BD10(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk4d = value;
}

/** Return the unsigned byte at receiver offset 0x4D. */
u8 func_0047BD20(const void* object)
{
    const ByteGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk4d;
}

/**
 * @brief Store the value at receiver offset 0x34.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047BD30(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk34 = value;
}

/** Store the byte at receiver offset 0x56. */
void func_0047BD40(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk56 = value;
}

/** Return the unsigned byte at receiver offset 0x56. */
u8 func_0047BD50(const void* object)
{
    const ByteGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk56;
}

/**
 * @brief Store the value at receiver offset 0x44.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047BD60(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk44 = value;
}

/** Return the float member at receiver offset 0x44. */
float func_0047BD70(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    return receiver->unk44;
}

/** Return the float member at receiver offset 0x28. */
float func_0047BD80(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    return receiver->unk28;
}

/** Store the word at receiver offset 0x48. */
void func_0047BD90(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = object;
    receiver->unk48 = value;
}

/** Return the word at receiver offset 0x48. */
u32 func_0047BDA0(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk48;
}

/** Store the byte at receiver offset 0x4F. */
void func_0047BDB0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk4f = value;
}

/** Store the byte at receiver offset 0x4E. */
void func_0047BDC0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk4e = value;
}

/** Store the word at receiver offset 0x50. */
void func_0047BDD0(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = object;
    receiver->unk50 = value;
}

/** Return the word at receiver offset 0x50. */
u32 func_0047BDE0(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk50;
}

/** Store the byte at receiver offset 0x55. */
void func_0047BDF0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk55 = value;
}

/**
 * @brief Store the value at receiver offset 0x3C.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047BE00(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk3c = value;
}

/** Store the byte at receiver offset 0x54. */
void func_0047BE10(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk54 = value;
}

/**
 * @brief Store the value at receiver offset 0x40.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047BE20(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk40 = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047BE30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047BE70);

/**
 * @brief Store the value at receiver offset 0x38.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047BEA0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk38 = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047BEB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047BEC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047BED0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047BEE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047BEF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047BF20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047BF30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047BF40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047BF60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047C370);

/**
 * @brief Store the value at receiver offset 0x28.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047C470(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk28 = value;
}

/**
 * @brief Store the value at receiver offset 0x30.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047C480(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk30 = value;
}

/** Return the float member at receiver offset 0x30. */
float func_0047C490(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    return receiver->unk30;
}

/** Store the byte at receiver offset 0x4D. */
void func_0047C4A0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk4d = value;
}

/** Return the unsigned byte at receiver offset 0x4D. */
u8 func_0047C4B0(const void* object)
{
    const ByteGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk4d;
}

/**
 * @brief Store the value at receiver offset 0x34.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047C4C0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk34 = value;
}

/** Store the byte at receiver offset 0x56. */
void func_0047C4D0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk56 = value;
}

/** Return the unsigned byte at receiver offset 0x56. */
u8 func_0047C4E0(const void* object)
{
    const ByteGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk56;
}

/**
 * @brief Store the value at receiver offset 0x44.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047C4F0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk44 = value;
}

/** Return the float member at receiver offset 0x44. */
float func_0047C500(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    return receiver->unk44;
}

/** Return the float member at receiver offset 0x28. */
float func_0047C510(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    return receiver->unk28;
}

/** Store the word at receiver offset 0x48. */
void func_0047C520(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = object;
    receiver->unk48 = value;
}

/** Return the word at receiver offset 0x48. */
u32 func_0047C530(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk48;
}

/** Store the byte at receiver offset 0x4F. */
void func_0047C540(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk4f = value;
}

/** Store the byte at receiver offset 0x4E. */
void func_0047C550(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk4e = value;
}

/** Store the word at receiver offset 0x50. */
void func_0047C560(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = object;
    receiver->unk50 = value;
}

/** Return the word at receiver offset 0x50. */
u32 func_0047C570(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk50;
}

/** Store the byte at receiver offset 0x55. */
void func_0047C580(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk55 = value;
}

/**
 * @brief Store the value at receiver offset 0x3C.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047C590(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk3c = value;
}

/** Store the byte at receiver offset 0x54. */
void func_0047C5A0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk54 = value;
}

/**
 * @brief Store the value at receiver offset 0x40.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047C5B0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk40 = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047C5C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047C600);

/**
 * @brief Store the value at receiver offset 0x38.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047C630(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk38 = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047C640);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047C650);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047C660);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047C670);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047C680);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047C6B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047C6C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047C6D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047C700);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047CB10);

/**
 * @brief Store the value at receiver offset 0x28.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047CC10(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk28 = value;
}

/**
 * @brief Store the value at receiver offset 0x30.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047CC20(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk30 = value;
}

/** Return the float member at receiver offset 0x30. */
float func_0047CC30(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    return receiver->unk30;
}

/** Store the byte at receiver offset 0x4D. */
void func_0047CC40(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk4d = value;
}

/** Return the unsigned byte at receiver offset 0x4D. */
u8 func_0047CC50(const void* object)
{
    const ByteGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk4d;
}

/**
 * @brief Store the value at receiver offset 0x34.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047CC60(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk34 = value;
}

/** Store the byte at receiver offset 0x56. */
void func_0047CC70(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk56 = value;
}

/** Return the unsigned byte at receiver offset 0x56. */
u8 func_0047CC80(const void* object)
{
    const ByteGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk56;
}

/**
 * @brief Store the value at receiver offset 0x44.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047CC90(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk44 = value;
}

/** Return the float member at receiver offset 0x44. */
float func_0047CCA0(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    return receiver->unk44;
}

/** Return the float member at receiver offset 0x28. */
float func_0047CCB0(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    return receiver->unk28;
}

/** Store the word at receiver offset 0x48. */
void func_0047CCC0(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = object;
    receiver->unk48 = value;
}

/** Return the word at receiver offset 0x48. */
u32 func_0047CCD0(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk48;
}

/** Store the byte at receiver offset 0x4F. */
void func_0047CCE0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk4f = value;
}

/** Store the byte at receiver offset 0x4E. */
void func_0047CCF0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk4e = value;
}

/** Store the word at receiver offset 0x50. */
void func_0047CD00(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = object;
    receiver->unk50 = value;
}

/** Return the word at receiver offset 0x50. */
u32 func_0047CD10(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk50;
}

/** Store the byte at receiver offset 0x55. */
void func_0047CD20(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk55 = value;
}

/**
 * @brief Store the value at receiver offset 0x3C.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047CD30(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk3c = value;
}

/** Store the byte at receiver offset 0x54. */
void func_0047CD40(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk54 = value;
}

/**
 * @brief Store the value at receiver offset 0x40.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047CD50(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk40 = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047CD60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047CDA0);

/**
 * @brief Store the value at receiver offset 0x38.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047CDD0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk38 = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047CDE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047CDF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047CE00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047CE10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047CE20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047CE50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047CE60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047CE70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047CEA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047D2B0);

/**
 * @brief Store the value at receiver offset 0x28.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047D3B0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk28 = value;
}

/**
 * @brief Store the value at receiver offset 0x30.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047D3C0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk30 = value;
}

/** Return the float member at receiver offset 0x30. */
float func_0047D3D0(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    return receiver->unk30;
}

/** Store the byte at receiver offset 0x4D. */
void func_0047D3E0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk4d = value;
}

/** Return the unsigned byte at receiver offset 0x4D. */
u8 func_0047D3F0(const void* object)
{
    const ByteGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk4d;
}

/**
 * @brief Store the value at receiver offset 0x34.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047D400(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk34 = value;
}

/** Store the byte at receiver offset 0x56. */
void func_0047D410(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk56 = value;
}

/** Return the unsigned byte at receiver offset 0x56. */
u8 func_0047D420(const void* object)
{
    const ByteGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk56;
}

/**
 * @brief Store the value at receiver offset 0x44.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047D430(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk44 = value;
}

/** Return the float member at receiver offset 0x44. */
float func_0047D440(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    return receiver->unk44;
}

/** Return the float member at receiver offset 0x28. */
float func_0047D450(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    return receiver->unk28;
}

/** Store the word at receiver offset 0x48. */
void func_0047D460(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = object;
    receiver->unk48 = value;
}

/** Return the word at receiver offset 0x48. */
u32 func_0047D470(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk48;
}

/** Store the byte at receiver offset 0x4F. */
void func_0047D480(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk4f = value;
}

/** Store the byte at receiver offset 0x4E. */
void func_0047D490(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk4e = value;
}

/** Store the word at receiver offset 0x50. */
void func_0047D4A0(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = object;
    receiver->unk50 = value;
}

/** Return the word at receiver offset 0x50. */
u32 func_0047D4B0(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk50;
}

/** Store the byte at receiver offset 0x55. */
void func_0047D4C0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk55 = value;
}

/**
 * @brief Store the value at receiver offset 0x3C.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047D4D0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk3c = value;
}

/** Store the byte at receiver offset 0x54. */
void func_0047D4E0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk54 = value;
}

/**
 * @brief Store the value at receiver offset 0x40.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047D4F0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk40 = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047D500);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047D540);

/**
 * @brief Store the value at receiver offset 0x38.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047D570(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk38 = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047D580);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047D590);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047D5A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047D5B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047D5C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047D5F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047D600);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047D610);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047D640);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047DA50);

/**
 * @brief Store the value at receiver offset 0x28.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047DB50(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk28 = value;
}

/**
 * @brief Store the value at receiver offset 0x30.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047DB60(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk30 = value;
}

/** Return the float member at receiver offset 0x30. */
float func_0047DB70(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    return receiver->unk30;
}

/** Store the byte at receiver offset 0x4D. */
void func_0047DB80(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk4d = value;
}

/** Return the unsigned byte at receiver offset 0x4D. */
u8 func_0047DB90(const void* object)
{
    const ByteGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk4d;
}

/**
 * @brief Store the value at receiver offset 0x34.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047DBA0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk34 = value;
}

/** Store the byte at receiver offset 0x56. */
void func_0047DBB0(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk56 = value;
}

/** Return the unsigned byte at receiver offset 0x56. */
u8 func_0047DBC0(const void* object)
{
    const ByteGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk56;
}

/**
 * @brief Store the value at receiver offset 0x44.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047DBD0(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk44 = value;
}

/** Return the float member at receiver offset 0x44. */
float func_0047DBE0(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    return receiver->unk44;
}

/** Return the float member at receiver offset 0x28. */
float func_0047DBF0(void* object)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    return receiver->unk28;
}

/** Store the word at receiver offset 0x48. */
void func_0047DC00(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = object;
    receiver->unk48 = value;
}

/** Return the word at receiver offset 0x48. */
u32 func_0047DC10(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk48;
}

/** Store the byte at receiver offset 0x4F. */
void func_0047DC20(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk4f = value;
}

/** Store the byte at receiver offset 0x4E. */
void func_0047DC30(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk4e = value;
}

/** Store the word at receiver offset 0x50. */
void func_0047DC40(void* object, u32 value)
{
    WordSetterOwnertext_0047AE20* receiver = object;
    receiver->unk50 = value;
}

/** Return the word at receiver offset 0x50. */
u32 func_0047DC50(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk50;
}

/** Store the byte at receiver offset 0x55. */
void func_0047DC60(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk55 = value;
}

/**
 * @brief Store the value at receiver offset 0x3C.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047DC70(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk3c = value;
}

/** Store the byte at receiver offset 0x54. */
void func_0047DC80(void* object, u8 value)
{
    ByteSetterOwnertext_0047AE20* receiver = object;
    receiver->unk54 = value;
}

/**
 * @brief Store the value at receiver offset 0x40.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047DC90(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk40 = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047DCA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047DCE0);

/**
 * @brief Store the value at receiver offset 0x38.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047DD10(void* object, float value)
{
    LibFloatFieldOwner0047AE20* receiver = object;
    receiver->unk38 = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047DD20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047DD30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047DD40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047DD50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047DD60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047DD80);

/** Return the word at receiver offset 0x1C. */
u32 func_0047DDA0(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk1c;
}

/** Return the word at receiver offset 0xC. */
u32 func_0047DDB0(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk0c;
}

/** Return the word at receiver offset 0x10. */
u32 func_0047DDC0(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk10;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047DDD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047DDE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047DDF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047DE50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047DE70);

/** Return the word at receiver offset 0x1C. */
u32 func_0047DE90(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk1c;
}

/** Return the word at receiver offset 0xC. */
u32 func_0047DEA0(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk0c;
}

/** Return the word at receiver offset 0x10. */
u32 func_0047DEB0(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk10;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047DEC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047DED0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047DEE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047DF40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047DF60);

/** Return the word at receiver offset 0x1C. */
u32 func_0047DF80(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk1c;
}

/** Return the word at receiver offset 0xC. */
u32 func_0047DF90(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk0c;
}

/** Return the word at receiver offset 0x10. */
u32 func_0047DFA0(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk10;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047DFB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047DFC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047DFD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E030);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E050);

/** Return the word at receiver offset 0x1C. */
u32 func_0047E070(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk1c;
}

/** Return the word at receiver offset 0xC. */
u32 func_0047E080(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk0c;
}

/** Return the word at receiver offset 0x10. */
u32 func_0047E090(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk10;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E0A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E0B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E0C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E120);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E130);

/** Return the word at receiver offset 0x1C. */
u32 func_0047E150(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk1c;
}

/** Return the word at receiver offset 0xC. */
u32 func_0047E160(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk0c;
}

/** Return the word at receiver offset 0x10. */
u32 func_0047E170(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk10;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E180);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E190);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E1A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E200);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E220);

/** Return the word at receiver offset 0x1C. */
u32 func_0047E240(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk1c;
}

/** Return the word at receiver offset 0xC. */
u32 func_0047E250(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk0c;
}

/** Return the word at receiver offset 0x10. */
u32 func_0047E260(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk10;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E270);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E280);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E290);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E2F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E310);

/** Return the word at receiver offset 0x1C. */
u32 func_0047E330(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk1c;
}

/** Return the word at receiver offset 0xC. */
u32 func_0047E340(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk0c;
}

/** Return the word at receiver offset 0x10. */
u32 func_0047E350(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk10;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E360);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E370);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E380);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E3E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E400);

/** Return the word at receiver offset 0x1C. */
u32 func_0047E420(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk1c;
}

/** Return the word at receiver offset 0xC. */
u32 func_0047E430(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk0c;
}

/** Return the word at receiver offset 0x10. */
u32 func_0047E440(const void* object)
{
    const WordGetterOwnertext_0047AE20* receiver = object;
    return receiver->unk10;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E450);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E460);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E470);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047E4D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047EA30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047EA70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047EAF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047EBD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047F130);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047F170);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047F250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047F7B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047F800);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047F890);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047F970);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047FEC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047FF10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_0047FFF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00480550);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_004805A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00480640);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00480720);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00480C80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00480CD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00480DB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00481310);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00481370);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00481420);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00481500);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00481A60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00481AC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00481B90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_004822B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00484D80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00484E50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00485570);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00488040);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00488110);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0047AE20", func_00488830);
