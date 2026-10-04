#include "include_asm.h"
#include "main/resident_data.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/1067-00/text_001ED7E0_callbacks.h"
#include "overlays/1067-00/text_0026EE10.h"



extern void func_45B110(void* object, void* value);

typedef struct FieldWords270E90
{
    u32 words[4];
} FieldWords270E90;

typedef struct FieldState270EE0
{
    u8 unk00[0x1D0];
    u32 value;
    u8 unk1d4[0x0C];
    u32 flags;
    u8 unk1e4[0x16];
    u8 unk1fa_0 : 1;
    u8 unk1fa_1 : 1;
    u8 unk1fa_2_7 : 6;
} FieldState270EE0;

typedef struct FieldState271750
{
    u8 unk00[0x3C];
    u32 state;
} FieldState271750;

typedef struct FieldFlag272290
{
    u8 unk00[0x1C];
    u8 unk1c_0 : 1;
    u8 unk1c_1_7 : 7;
} FieldFlag272290;

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026EE10);

void func_0026EEA0(void* object)
{
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

s32 func_0026EED0(const void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026EEE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026EFA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026F120);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026F1F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026F2C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026F3A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026F460);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026F670);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026F690);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026F6E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026F730);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026F780);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026F800);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026F870);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026F8F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026FA40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026FC00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026FE80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026FF10);

void func_0026FF70(FieldRoot26FF70* root)
{
    struct FieldClass151640* object = root->unkA8;
    FieldContext26FF70* context;
    func_0045B210(object, root->unkB0);
    func_45B110(object, root->unk7C);
    context = root->unkD8;
    if (context->unk8c != 0)
    {
        func_0020DDD0(object, context);
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026FFD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00270100);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00270190);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00270600);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_002706D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00270770);

FieldWords270E90* func_00270E90(FieldWords270E90* object)
{
    object->words[3] = 0;
    object->words[2] = 0;
    object->words[1] = 0;
    object->words[0] = 0;
    return object;
}

void func_00270EB0(FieldState270EE0* object, u32 flags)
{
    object->flags = flags;
    object->unk1fa_1 = (flags & 2) != 0;
}

void func_00270EE0(FieldState270EE0* object, u32 value, u32 flags)
{
    object->unk1fa_0 = 0;
    object->value = value;
    object->flags = flags;
    object->unk1fa_1 = (flags & 2) != 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00270F30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_002710C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00271130);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00271370);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_002714B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00271560);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_002715A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00271630);

s32 func_002716B0(const void* object)
{
    return 9;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_002716C0);

void func_00271750(FieldState271750* object)
{
    if (func_001F9120(object) == 1)
    {
        object->state = 10;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00271790);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_002717E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00271B50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00271C60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00271E60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00271FC0);

s32 func_00272080(const void* object)
{
    return 3;
}

void func_00272090(void* object)
{
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_002720C0);

void func_00272130(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00272140);

void func_002721A0(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_002721B0);

void func_00272220(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00272230);

void func_00272290(FieldFlag272290* object)
{
    object->unk1c_0 = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_002722B0);

void* func_00272350(void* object, s32 flags)
{
    return func_00271FC0((u8*)object - 0x14, flags);
}
