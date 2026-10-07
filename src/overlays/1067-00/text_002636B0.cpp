#include "include_asm.h"
#include "overlays/1067-00/text_002636B0.h"
#include "overlays/1067-00/text_0026E460.h"

/** Partial receiver and guarded nested state for the constant reset. */
typedef struct FieldInnerC000
{
    u8 pad00[0x3C];
    u8 active;
    u8 pad3d[0x33];
    float value;
} FieldInnerC000;

typedef struct FieldOuterC000
{
    u8 pad00[0xD4];
    FieldInnerC000* inner;
} FieldOuterC000;


INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002636B0);

void func_002636F0(u32* word, u32 value)
{
    *word = value;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00263700);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002637C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002637E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00263890);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00263940);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00263A30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00263AF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00263BF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00263C40);

void func_00263C70(FieldObject153E20* object, void* value)
{
    object->unk20 = value;
}

void func_00263C80(FieldObject153E20* object, void* value)
{
    object->unk24 = value;
}

void* func_00263C90(const FieldObject153E20* object)
{
    return object->unk24;
}

void func_00263CA0(FieldObject153E20* object, s8 value)
{
    object->unk28 = value;
}

s8 func_00263CB0(const FieldObject153E20* object)
{
    return object->unk28;
}

s32 func_00263CC0(void* object)
{
    return 0;
}

s32 func_00263CD0(void* object)
{
    return 0;
}

s32 func_00263CE0(void* object)
{
    return 0;
}

s32 func_00263CF0(void* object)
{
    return 0;
}

void func_00263D00(void* object)
{
}

s32 func_00263D10(void* object)
{
    return 0;
}

void func_00263D20(void* object)
{
}

void func_00263D30(void* object)
{
}

void func_00263D40(void* object)
{
}

s32 func_00263D50(void* object)
{
    return 0;
}

s32 func_00263D60(void* object)
{
    return 0;
}

s32 func_00263D70(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00263D80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00263E20);

void func_00263E80(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00263E90);

void func_00263F40(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00263F50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00263FD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264010);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264080);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264110);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264200);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264230);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002642D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264360);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002643E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264460);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002644F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264580);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264600);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264650);

void func_002646C0(FieldObject15AE70* object, u8 value)
{
    object->unk0C = value;
}

u8 func_002646D0(const FieldObject15AE70* object)
{
    return object->unk0C;
}

void func_002646E0(FieldObject15AE70* object, u8 value)
{
    object->unk08 = value;
}

void func_002646F0(FieldObject15AE70* object, u16 value)
{
    object->unk0A = value;
}

void func_00264700(FieldObject15AE70* object, void* value)
{
    object->unk98 = value;
}

void* func_00264710(const FieldObject15AE70* object)
{
    return object->unk98;
}

void func_00264720(FieldObject15AE70* object, void* value)
{
    object->unk9C = value;
}

void* func_00264730(const FieldObject15AE70* object)
{
    return object->unk9C;
}

void func_00264740(FieldObject15AE70* object, void* value)
{
    object->unk04 = value;
}

void* func_00264750(const FieldObject15AE70* object)
{
    return object->unk04;
}

void* func_00264760(const FieldObject15AE70* object)
{
    return object->unk10;
}

void func_00264770(void* object)
{
}

void func_00264780(void* object)
{
}

void func_00264790(void* object)
{
}

void func_002647A0(void* object)
{
}

void func_002647B0(void* object)
{
}

void func_002647C0(void* object)
{
}

void func_002647D0(void* object)
{
}

void func_002647E0(void* object)
{
}

void func_002647F0(void* object)
{
}

void func_00264800(void* object)
{
}

void func_00264810(void* object)
{
}

void func_00264820(void* object)
{
}

void func_00264830(void* object)
{
}

void func_00264840(void* object)
{
}

void func_00264850(void* object)
{
}

void func_00264860(void* object)
{
}

void func_00264870(void* object)
{
}

void func_00264880(void* object)
{
}

void func_00264890(void* object)
{
}

void func_002648A0(void* object)
{
}

s32 func_002648B0(void* object)
{
    return 0;
}

s32 func_002648C0(void* object)
{
    return 0;
}

s32 func_002648D0(void* object)
{
    return 0;
}

s32 func_002648E0(void* object)
{
    return 0;
}

s32 func_002648F0(void* object)
{
    return 0;
}

s32 func_00264900(void* object)
{
    return 0;
}

s32 func_00264910(void* object)
{
    return 0;
}

s32 func_00264920(void* object)
{
    return 0;
}

s32 func_00264930(void* object)
{
    return 0;
}

s32 func_00264940(void* object)
{
    return 0;
}

void func_00264950(void* object)
{
}

void func_00264960(void* object)
{
}

u8 func_00264970(const FieldObject15AE70* object)
{
    return object->unk0D;
}

void func_00264980(FieldObject15AE70* object, u8 value)
{
    object->unk0D = value;
}

void func_00264990(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002649A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264A30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264AC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264C50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264CB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264CE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264D30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264E10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264ED0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002650F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00265130);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00265360);

void func_00265490(FieldObject15AD40* object, u8 value)
{
    object->unk12C = value;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002654A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00265810);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00265870);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002658E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00265A70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00265C40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00265D90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00265FC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00266060);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00266190);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002666C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00266730);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00266820);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002669A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002669C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002669E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00266A60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00266B90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00266EB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002672C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00267330);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00267390);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00267410);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00267500);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002675F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00267690);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00267720);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002678F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00267DD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00267E30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00267EE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00267FA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00267FF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00268040);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002680E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00268170);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00268370);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002687B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00268810);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00268990);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00268A80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00268B10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002690C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00269120);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002691A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00269340);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00269670);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00269F20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00269FC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026A110);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026A210);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026A2A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026A330);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026A650);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026BD60);

void FieldClass1547D0::func_slot0c()
{
    FieldClass150070* item = 0;
    while (func_0026E5F0(unkfc, &item))
    {
        item->func_001DD7B0();
    }
    func_0026E570(unkfc);
    FieldClass15AE70::func_slot0c();
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026BEA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026BF10);

void func_0026C000(FieldOuterC000* object)
{
    FieldInnerC000* inner = object->inner;
    if (inner != 0)
    {
        inner->value = 128.0f;
        inner->active = 1;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026C030);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026C1B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026C1E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026C650);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026CB00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026CB20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026CB40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026CB60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026CC80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026D140);

void FieldClass1548D0::func_slot0c()
{
    FieldClass15AE70::func_slot0c();
    FieldClass150070* item = 0;
    while (func_0026E7E0(unkb8, &item))
    {
        item->func_001DD7B0();
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026D560);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026D5D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026D6A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026DA90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026DAF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026DF90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026E050);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026E0F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026E170);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026E1A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026E210);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026E2E0);

void func_0026E390(void* object)
{
}

u8 func_0026E3A0(const FieldObject15AE70* object)
{
    return 0;
}

u8 func_0026E3B0(const FieldObject15AE70* object)
{
    return 0;
}

u8 func_0026E3C0(const FieldObject1549D0* object)
{
    return object->unk3C;
}

void* func_0026E3D0(const FieldObject1549D0* object)
{
    return object->unk38;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026E3E0);
