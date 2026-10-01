#include "include_asm.h"
#include "boot/resident_data.h"
#include "boot/resident_0010A0E0.h"
#include "overlays/0002-01/text_004CD3A0.h"
#include "overlays/1067-00/text_001DED80_callbacks.h"
#include "overlays/1067-00/text_00202240_callbacks.h"
#include "overlays/1067-00/text_0021FB80.h"
#include "overlays/1067-00/text_0022DC70.h"

#include "overlays/1067-00/text_002764D0.h"
#include "overlays/1067-00/text_002607B0.h"

typedef struct FieldTarget336B0
{
    u8 unk00[0x48];
    u32 value;
} FieldTarget336B0;

typedef struct FieldAttachment336B0
{
    u8 unk00[4];
    void* current;
    FieldTarget336B0* target;
} FieldAttachment336B0;

struct FieldObject234B0
{
    u8 unk00[0x1B0];
    FieldVector2624 vector;
    u8 unk1c0[0x44];
    u32 flags;
    u8 unk208[0x26C];
    float value;
    u8 unk478[0x14C];
    u8 current;
    u8 unk5c5;
    u8 previous;
};

struct FieldObject232640
{
    u8 unk00[0x388];
    void* table;
    u8 unk38c[0x28];
    u32 state;
    u8 unk3b8[3];
    u8 unk3bb_0_1 : 2;
    u8 mode : 1;
    u8 unk3bb_3_7 : 5;
    u8 unk3bc[0xC4];
    float value;
    u8 unk484[0x100];
    FieldAttachment336B0* attachment;
    u8 unk588[0x3C];
    u8 current;
    u8 previous;
    u8 unk5c6[6];
    u8 flags;
    u8 active : 1;
    u8 other : 7;
};

extern u8 D_3013A0[];
extern u8 D_3014A0[];
void func_4C96E0(void* object, float value);


typedef struct FieldObject22E3A0
{
    u8 unk00[0x78];
    float unk78;
    FieldObject31E30* nested;
} FieldObject22E3A0;

struct FieldObject22E170
{
    u8 unk00[0x10];
    FieldObject22E3A0* target;
};

struct FieldObject22DD50
{
    u8 unk00[0x10];
    FieldObject22E3A0* target;
    u8 unk14[8];
    float unk1c;
};

struct FieldObject22E380
{
    u8 unk00[0x10];
    FieldObject22E3A0* target;
    u8 unk14[8];
    float unk1c;
};

struct FieldObject239A10
{
    u8 unk00[0x69F];
    u8 unk69f_0 : 1;
    u8 unk69f_rest : 7;
};

typedef struct FieldObject31E30Attached
{
    u8 unk00[0x94];
    float unk94;
} FieldObject31E30Attached;

struct FieldObject31E30
{
    u8 unk00[0x144];
    FieldObject31E30Attached* attached;
    u8 unk148[0xBC];
    u32 flags;
    u8 unk208[0x338];
    float unk540;
};

typedef struct FieldObject32710Attached
{
    u8 unk00[0x48];
    FieldObject32710Result* target;
} FieldObject32710Attached;

struct FieldObject32710
{
    u8 unk00[0x588];
    FieldObject32710Attached* attached;
};

struct FieldObject239B60
{
    u8 unk00[0x20];
    FieldVector2624 unk20;
    u8 unk30[0x620];
    FieldVector2624 unk650;
    u8 unk660[0x20];
    float unk680;
    u8 unk684[4];
    float unk688;
    float unk68c;
};

struct FieldObject239880
{
    u8 unk00[0xC];
    u32 unk0c;
    u8 unk10[0x68];
    float unk78;
};

struct FieldObject2320D0
{
    u8 unk00[0x548];
    void* target;
};

struct FieldObject232090
{
    u8 unk00[0x4A4];
    s8 value;
    u8 active : 1;
    u8 other : 7;
};

struct FieldObject233470
{
    u8 unk00[0x204];
    u32 flags;
    u8 unk208[4];
    float unk20c;
    float unk210;
    float unk214;
};

struct FieldObject22E680
{
    u8 unk00[0x24];
    s32 unk24;
    u8 unk28[0x24];
    u8 unk4c_0_2 : 3;
    u8 unk4c_3 : 1;
    u8 unk4c_4_7 : 4;
    u8 unk4d[3];
    void* unk50;
    u8 unk54[0xC];
    u8 unk60;
};

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022DC70);

s32 func_0022DD50(FieldObject22DD50* object)
{
    func_00231E30(object->target->nested, object->unk1c);
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022DD80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022DDF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022DE40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022DF10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022E160);

s32 func_0022E170(FieldObject22E170* object)
{
    FieldObject22E3A0* target = object->target;
    s32 enabled = (target->nested->flags & 1) ? 1 : 0;
    if (enabled)
    {
        target->unk78 = 1.0f;
        return 0;
    }
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022E1B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022E2D0);

s32 func_0022E350(FieldObject22E170* object)
{
    func_001DEDF0(D_001B6430->context->unk04, object->target->nested);
    return 1;
}

s32 func_0022E380(FieldObject22E380* object)
{
    object->target->unk78 = object->unk1c;
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022E3A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022E420);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022E530);

void func_0022E650(FieldObject22E680* object)
{
    func_0027ABF0(object);
    object->unk50 = &object->unk60;
}

void func_0022E680(FieldObject22E680* object)
{
    object->unk50 = &object->unk60;
    object->unk4c_3 = 0;
    object->unk24 = -3;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022E6B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022E750);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022E7F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022E890);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022E930);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022E9D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022EA70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022EB10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022EBB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022EC50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022ECF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022ED90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022EE30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022EED0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022EF70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022F010);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022F0B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022F150);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022F1F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022F290);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022F330);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022F3D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022F470);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022F510);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022F5B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022F650);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022F6F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022F790);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022F830);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022F8D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022F970);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022FA10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022FAB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022FB50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022FBF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022FC90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022FD30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022FDD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022FE70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022FF10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0022FFB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00230050);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_002300F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00230190);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00230230);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_002302D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00230370);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00230410);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_002304B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00230550);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_002305F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00230690);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00230730);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_002307D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00230AE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00230E60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00230EB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00230F20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00230FC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00231080);

s32 func_00231110(FieldObject152EB0* object)
{
    return 9;
}

void func_00231120(FieldObject152EB0* object)
{
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00231150);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_002316A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_002318C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00231B30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00231B90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00231D50);

void func_00231E30(FieldObject31E30* object, float value)
{
    object->unk540 = value;
    if (object->attached != 0)
    {
        object->attached->unk94 = value;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00231E50);

void func_00232090(FieldObject232090* object, s8 value)
{
    if (value > 4)
    {
        value = 4;
    }
    object->value = value;
    object->active = 1;
}

void func_002320D0(FieldObject2320D0* object, u8 value)
{
    if (object->target != 0)
    {
        func_00206200(object->target, value);
    }
}

void func_00232100(FieldObject2320D0* object, u8 enable, s32 update)
{
    func_00204370(object, enable, update);
    if (object->target != 0)
    {
        func_00206200(object->target, enable);
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00232150);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00232360);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00232450);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00232520);

void func_00232640(FieldObject232640* object, u8 flags)
{
    if ((flags & 4) == 0)
    {
        object->table = object->mode ? D_3014A0 : D_3013A0;
        object->state = 0;
    }
}

void func_00232690(FieldObject232640* object, u8 flags, float value)
{
    if (object->current != 3)
    {
        object->previous = object->current;
    }
    object->current = 3;
    object->active = 0;
    object->flags = flags;
    object->value = value;
    if ((flags & 4) == 0)
    {
        object->table = object->mode ? D_3014A0 : D_3013A0;
        object->state = 0;
    }
}

FieldObject32710Result* func_00232710(FieldObject32710* object)
{
    if (object->attached == 0)
    {
        return 0;
    }
    return object->attached->target;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00232730);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00232890);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00232940);

s32 func_00232A10(void* object)
{
    if (func_00202620(object) == 0)
    {
        return 0;
    }
    func_00234110(object);
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00232A60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00232AE0);

void func_00233470(FieldObject233470* object, float first, float second, float third)
{
    s32 set = (object->flags & 0x100) ? 1 : 0;
    if (!set)
    {
        object->unk20c = second;
        object->unk210 = third;
        object->unk214 = first;
        object->flags |= 0x100;
    }
}

void func_002334B0(FieldObject234B0* object)
{
    object->flags &= ~0x40;
    object->current = object->previous;
    if ((object->flags & 0x20) == 0 && (object->flags & 0x2000000) == 0)
    {
        func_002274F0(object, &object->vector, 0.25f);
    }
    object->value = 15.0f;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00233520);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00233620);

void func_00233660(FieldObject232640* object)
{
    func_00202580(object);
    object->table = object->mode ? D_3014A0 : D_3013A0;
    object->state = 0;
}

void func_002336B0(FieldObject232640* object, s32 state)
{
    object->state = state;
    if (state == 0xFF)
    {
        FieldAttachment336B0* attachment = object->attachment;
        if (attachment != 0)
        {
            if (attachment->current != 0)
            {
                func_4C96E0(attachment->current, 0.0f);
            }
            if (attachment->target != 0)
            {
                attachment->target->value = 0;
            }
        }
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00233710);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00233950);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00234000);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00234110);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00235110);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_002351F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_002353E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00235540);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00235E80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00237420);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_002374D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00237710);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_002377D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_002378E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_002379A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00237B30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00238060);

void func_00238520(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00238530);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00238700);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_002387D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00238880);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00238940);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00238C00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00238CF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00239460);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_002394C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_002395B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00239720);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_002397B0);

s32 func_00239880(FieldObject239880* object)
{
    if (object->unk78 > 0.0f)
    {
        return 1;
    }
    return object->unk0c != 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_002398B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00239940);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00239970);

void func_00239A10(FieldObject239A10* object, u32 enabled)
{
    object->unk69f_0 = enabled;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00239A30);

void func_00239B60(FieldObject239B60* object, float first, float second, float third)
{
    object->unk650 = object->unk20;
    object->unk680 = first;
    object->unk688 = second;
    object->unk68c = third;
}

s32 func_00239B80(void* object)
{
    return func_002351F0(object) != 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_00239BA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0023A4C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0023A5C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0023A650);

void func_0023A6E0(FieldObject1530A0* object)
{
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0023A710);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0023AB00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0023AD00__16FieldClass1530C0Fv);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0023AD60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0023AE00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0023AEB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0023AFA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0023B0C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0023B170);

s32 func_0023B1A0(FieldObject1530D0* object)
{
    return 12;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0023B1B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022DC70", func_0023B1C0);
