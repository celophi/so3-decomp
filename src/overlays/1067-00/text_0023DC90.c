#include "include_asm.h"
#include "overlays/0002-01/text_004CD3A0.h"
#include "overlays/1067-00/text_0023DC90.h"
#include "overlays/1067-00/text_0027E520.h"


struct FieldObject24B6B0
{
    u8 unk00[0x80];
    void* target;
    u32 unk84;
    s32 value;
};

typedef struct FieldContextDC49880
{
    u8 unk00[0x7C];
    void* active;
} FieldContextDC49880;

extern void func_00249760(FieldObject24B6B0* object, void* target, const void* value);

struct FieldObject24C380
{
    u8 unk00[0x120];
    u8 field;
};

struct FieldObject24B490
{
    u8 unk00[0x7C];
    void* target;
};

struct FieldObject24B4C0
{
    u8 unk00[0x6C];
    u16 value;
};

struct FieldObject24A410
{
    u8 unk00[0x588];
    void* owned;
    u8 state;
    u8 unk58D[3];
    u8 flag0 : 1;
    u8 rest : 7;
};

extern void func_0023DDD0(FieldObject24A410* object);

struct FieldObject24C300
{
    u8 unk00[0x590];
    u8 flag0 : 1;
    u8 flag1 : 1;
    u8 unused : 6;
};

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0023DC90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0023DDD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0023DE30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0023DE90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0023E0C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0023E1B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0023E2A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0023E2F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0023E3D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0023E4E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0023E610);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0023E9E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0023EAE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0023EF20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0023F1E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0023FBC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0023FE70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00240000);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_002400C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00240240);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00240B20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00240CB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_002416D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00242080);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00243AB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00243B30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00243FD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_002447E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00245360);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00245650);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00245860);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00245A20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00245B20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00246230);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00246360);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_002468A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00246960);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00246B50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00246B90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00247940);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00247DB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00247F20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_002485B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00248C50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00248F60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00249000);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_002491F0);

s32 func_00249280(FieldObject1533E0* object)
{
    return 2;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00249290);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00249580);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00249600);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00249760);

void func_00249880(FieldObject24B6B0* object, const void* value)
{
    FieldContextDC49880* context = (FieldContextDC49880*)D_001B6430->context->unk08->unkdc;
    if (object->target != 0 && context != 0 && context->active != 0)
    {
        func_00249760(object, object->target, value);
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_002498D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00249960);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00249AB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00249B90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00249D40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00249E90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_00249FE0);

void func_0024A030(void* object, void* value, float strength)
{
    if (D_001B6458 != 0)
    {
        func_0027EB80(D_001B6458, value, 1, strength);
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0024A060);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0024A2D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0024A3C0);

void func_0024A410(FieldObject24A410* object)
{
    func_0023DDD0(object);
    object->flag0 = 0;
    object->state = 0;
    if (object->owned != 0)
    {
        func_004D65C0(object->owned);
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0024A470);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0024A750);

void func_0024A8A0(void* owner, FieldPairAt08* target, s8 first, s8 second)
{
    if (target != 0) {
        target->unk08 = first;
        target->unk09 = second;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0024A8C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0024A950);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0024AA10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0024B240);

void* func_0024B490(const FieldObject24B490* object)
{
    return object->target;
}

void* func_0024B4A0(const ResidentContext08* context)
{
    return context->unkdc;
}

ResidentContext08* func_0024B4B0(ResidentContextRef* ref)
{
    return ref->context->unk08;
}

u16 func_0024B4C0(const FieldObject24B4C0* object)
{
    return object->value;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0024B4D0);

void func_0024B6B0(FieldObject24B6B0* object, s32 value)
{
    if (value != -1)
    {
        object->value = value;
    }
    if (object->target != 0)
    {
        func_0024B4D0(object, object->target);
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0024B6F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0024B780);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0024BB10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0024BBB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0024BE00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0024BFE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0024C0B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0024C200);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0024C260);

void func_0024C300(FieldObject24C300* object)
{
    u8 flags = object->flag0 | object->flag1;
    if (flags == 0)
    {
        func_00246960(object);
    }
}

void func_0024C340(FieldObject24C300* object)
{
    u8 flags = object->flag0 | object->flag1;
    if (flags == 0)
    {
        func_002468A0(object);
    }
}

void* func_0024C380(FieldObject24C380* object)
{
    return &object->field;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0024C390);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0024C450);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0024C490);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023DC90", func_0024C4A0);
