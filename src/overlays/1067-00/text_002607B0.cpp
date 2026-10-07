#include "include_asm.h"
#include "overlays/1067-00/text_002607B0.h"
#include "overlays/1067-00/text_001E1590.h"

extern "C" {
extern void* D_175290[];
extern void* D_153D40[];
extern void* D_153D50[];
extern void* D_153DD8[];
FieldObject262910* func_4DAD90(FieldObject262910* object);
void __dl__FPv(void* object);
FieldObject262E20* func_4E2940(FieldObject262E20* object, s16 flags);
}

struct FieldObject262E20
{
    void** table;
    u8 unk04[0x21C];
    void** secondary_table;
};

struct FieldObject262F70
{
    u8 unk00[0x24];
    void** table;
};

struct FieldObject262910
{
    void** table;
    u8 unk04[0x20C];
    u32 unk210;
    u32 unk214;
};

struct FieldObject262490
{
    u8 unk00[0x20];
    FieldVector2624 unk20;
    FieldVector2624 unk30;
    u8 unk40[0x10];
    u8 unk50;
    u8 unk51[0x82F];
    FieldVector2624 unk880;
    FieldVector2624 unk890;
};

struct FieldObject261810
{
    u8 unk00[0x24];
    void* unk24;
    void* unk28;
};

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_002607B0);

s32 func_00260840(FieldObject153D20* object)
{
    return 2;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_00260850);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_002608B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_002609E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_00260A70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_00260CE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_00260F30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_00260F60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_00261020);

void FieldClass153E00::func_slot1c()
{
    unk4c->func_001DD7B0();
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_002610E0);

void* FieldClass153E30::func_00261150()
{
    return unk20;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_00261160);

void func_00261810(FieldObject261810* object, void* first, void* second)
{
    object->unk24 = first;
    object->unk28 = second;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_00261820);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_002618B0);

s32 func_00261D20(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_00261D30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_00261E60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_00261FC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_00262020);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_00262120);

void func_00262490(FieldObject262490* object, const FieldVector2624* vector)
{
    object->unk890 = *vector;
    object->unk50 = 1;
    object->unk20 = *vector;
}

void func_002624B0(FieldVector262900* vector)
{
    vector->packed = 0;
}

void func_002624C0(FieldVector2624* first, FieldVector2624* second,
                   const FieldVector2624* source)
{
    *first = *second = *source;
}

FieldVector2624* func_002624D0(FieldVector2624* vector, float value)
{
    vector->x = value;
    vector->y = value;
    vector->z = value;
    vector->w = value;
    return vector;
}

FieldVector2624* func_002624F0(FieldVector2624* vector)
{
    return vector;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_00262500);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_002625C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_00262610);

void func_00262900(FieldVector262900* vector)
{
    vector->packed = 0;
    vector->floats[3] = 1.0f;
}

FieldObject262910* func_00262910(FieldObject262910* object)
{
    func_4DAD90(object);
    object->table = D_175290;
    object->unk210 = 0;
    object->unk214 = 0;
    return object;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_00262950);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_00262A80);

u16 func_00262B90(const FieldObject15AE70* object)
{
    return object->unk0A;
}

u8 func_00262BA0(const FieldObject15AE70* object)
{
    return object->unk08;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_00262BB0);

FieldObject262E20* func_00262E20(FieldObject262E20* object, s16 flags)
{
    if (object != 0)
    {
        object->table = D_153D50;
        object->secondary_table = D_153DD8;
        func_4E2940(object, 0);
        if (flags > 0)
        {
            __dl__FPv(object);
        }
    }
    return object;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_00262E90);

FieldObject262F70* func_00262F70(FieldObject262F70* object, s16 flags)
{
    if (object != 0)
    {
        object->table = D_153D40;
        if (flags > 0)
        {
            __dl__FPv(object);
        }
    }
    return object;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_00262FC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_00263080);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_002630F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_00263210);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_002632C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_00263330);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_002633C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_00263540);

s32 func_00263610(void* object)
{
    return 2;
}

void func_00263620(FieldObject262490* object, const FieldVector2624* vector)
{
    object->unk880 = *vector;
    object->unk50 = 1;
    object->unk30 = *vector;
}

void func_00263640(FieldObject262490* object, const FieldVector2624* vector)
{
    object->unk880 = *vector;
    object->unk50 = 1;
    object->unk30 = *vector;
}

void func_00263660(FieldObject262490* object, const FieldVector2624* vector)
{
    object->unk890 = *vector;
    object->unk50 = 1;
    object->unk20 = *vector;
}

s32 func_00263680(FieldObject153E00* object)
{
    return 3;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_00263690);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002607B0", func_002636A0);
