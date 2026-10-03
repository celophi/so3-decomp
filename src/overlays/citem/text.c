#include "include_asm.h"
#include "overlays/citem/text.h"
#include "main/resident_001001E0.h"

#define ANGLE_STEP_RADIANS 0.008726646f
#define ANGLE_LIMIT_RADIANS 0.5235988f

struct ItemRecord
{
    void* methods;
    u32 unk04;
    u8 unk08;
    u8 unk09;
    u16 unk0a;
    u8 unk0c;
    u8 unk0d;
    u8 unk0e[2];
    u32 unk10;
    u8 unk14[0xC];
    u32 unk20;
    u8 unk24[0x74];
    u32 unk98;
    u32 unk9c;
};

struct StatusRecord
{
    u8 unk00[0x24];
    u32 unk24;
    s8 unk28;
    u8 unk29[0x13];
    u8 unk3c;
};

struct DisplayRecord
{
    void* methods;
    u8 unk04[0x5C];
    u8 unk60;
    u8 unk61[0x47];
    u8 unka8;
};

struct Record00349190
{
    u8 unk00[0x20];
    u32 unk20;
    u32 unk24;
    u32 unk28;
    float unk2c;
    u8 unk30[0x3C];
    u16 unk6c;
    u8 unk6e[0x46];
    u32 unkb4;
    u32 unkb8;
};

struct Record00349C50
{
    u8 unk00[0x38];
    u32 unk38;
};

struct Record0034C800
{
    u8 unk00[0x40];
    u32 unk40;
};

struct Record00349BF0
{
    u8 unk00[0x2C];
    void* unk2c;
};

struct Record0034C7A0
{
    u8 unk00[0x38];
    void* unk38;
};

struct Record0034C6A0
{
    void* methods;
    u8 unk04[0x3C];
    u8 unk40;
};

struct Record00350BD0
{
    u8 unk00[0x12C];
    u8 unk12c;
};

struct Record003540E0
{
    void* head;
    u32 count;
    void* methods;
};

struct Record003542F0
{
    void* head;
    u32 count;
    void* methods;
};

struct Record00354740
{
    void* head;
    u32 count;
    void* methods;
};

struct Record00353EF0
{
    void* methods;
    u8 unk04[0xE4];
    void* unke8;
    u8 unkec[0xC0];
    Record003542F0 embedded;
};

struct Record00350C20
{
    void* methods;
    u8 unk04[0xE4];
    void* unke8;
    u8 unkec[0x88];
    void* unk174;
};

struct SlotRecord
{
    u8 unk00[0x18];
    float unk18;
    float unk1c;
    u8 unk20[0x1C];
    u8 unk3c;
};

struct Record00350FC0
{
    u8 unk00[0xF0];
    struct SlotRecord* first[14];
    u8 unk128[0x10];
    struct SlotRecord* second[14];
    struct SlotRecord* third[14];
};

struct TransformRecord
{
    u8 unk00[0x20];
    Vector4 unk20;
    Vector4 unk30;
    Vector4 unk40;
    u8 unk50;
};

struct ScreenRecord
{
    u8 unk00[0x3C];
    u8 unk3c;
    u8 unk3d[0x33];
    float unk70;
};

struct ScreenOwner
{
    void* methods;
    u8 unk04[0xA4];
    struct ScreenRecord* unka8;
};

struct Record00353A50
{
    void* methods;
};

struct Record00352960
{
    void* methods;
};

struct Record00352EE0
{
    void* methods;
};

struct Record003531B0
{
    void* methods;
};

struct ItemListNode
{
    void* value;
    struct ItemListNode* next;
};

typedef struct ItemSortRecord
{
    u8 unk00[2];
    u16 table_index;
} ItemSortRecord;

typedef struct ItemSortDefinition
{
    u8 unk00[0x10];
    u16 sort_key_bits;
    u8 unk12[0xE];
} ItemSortDefinition;

struct ItemListOwner
{
    ItemListNode* head;
    u32 count;
};

struct AngleState
{
    u8 unk00[0x6C];
    float unk6c;
};

struct AngleOwner
{
    u8 unk00[0x1B0];
    u8 unk1b0;
    u8 unk1b1[7];
    struct AngleState* unk1b8;
};

struct ControlScreen
{
    u8 unk00[0x3C];
    u8 unk3c;
    u8 unk3d[2];
    u8 unk3f;
    u8 unk40[0x30];
    float unk70;
};

struct ControlOwner
{
    u8 unk00[0xAC];
    struct ControlScreen* unkac;
};

struct Record0034E8B0
{
    u8 unk00[0xA8];
    struct ControlScreen* unka8;
    struct ControlScreen* unkac;
    u8 unkb0[0x88];
    struct ControlScreen* first[6];
    u8 unk150[0x24];
    struct ControlScreen* unk174;
    u8 unk178[8];
    struct ControlScreen* second[6];
};

/* Resident pointer viewed through the 32-byte item definition format. */
extern ItemSortDefinition* D_001B64F0;
extern u8 D_184280[];
extern u8 D_184390[];
extern u8 D_1844B0[];
extern u8 D_1849F0[];
extern u8 D_184AF0[];
extern u8 D_184BF0[];
extern u8 D_184CF0[];
extern u8 D_1844A0[];
extern u8 D_1843F0[];
extern u8 D_175110[];
extern u8 D_1848D0[];
extern u8 D_1849C4[];
extern u8 D_1847B0[];
extern u8 D_1848A4[];
extern u8 D_184ED8[];
extern u8 D_184EC8[];
extern u8 D_184EB8[];
extern u8 D_50CD30[];
extern void func_2CEAF0(void* object, s32 flags);
extern void func_100B40(void* object);
extern void func_4CE4C0(Vector4* destination, const Vector4* source);
extern void func_2BC410(Record00349BF0* record, s32 flag);
extern void func_4618F0(void* record, s32 flag);
extern void func_4C48B0(void* record, s32 flag);
extern void func_003541F0(Record003540E0* record);
extern void func_00354400(Record003542F0* record);
extern void func_003547C0(Record00354740* record);
extern void func_2CD9F0(void* record, s32 flag);
extern void func_4C4A90(void* object);
extern void func_44B110(void* object, s32 arg1, s32 arg2, void* arg3, float value, s32 flag);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003483C0);

ItemRecord* func_00348400(ItemRecord* item, s16 flag)
{
    if (item != 0)
    {
        item->methods = D_184280;
        func_2CEAF0(item, 0);
        if (flag > 0)
        {
            func_100B40(item);
        }
    }
    return item;
}

void func_00348460(ItemRecord* item, u8 value)
{
    item->unk0c = value;
}

u8 func_00348470(ItemRecord* item)
{
    return item->unk0c;
}

void func_00348480(ItemRecord* item, u8 value)
{
    item->unk08 = value;
}

u8 func_00348490(ItemRecord* item)
{
    return item->unk08;
}

void func_003484A0(ItemRecord* item, u16 value)
{
    item->unk0a = value;
}

u16 func_003484B0(ItemRecord* item)
{
    return item->unk0a;
}

void func_003484C0(ItemRecord* item, u32 value)
{
    item->unk98 = value;
}

u32 func_003484D0(ItemRecord* item)
{
    return item->unk98;
}

void func_003484E0(ItemRecord* item, u32 value)
{
    item->unk9c = value;
}

u32 func_003484F0(ItemRecord* item)
{
    return item->unk9c;
}

void func_00348500(ItemRecord* item, u32 value)
{
    item->unk04 = value;
}

u32 func_00348510(ItemRecord* item)
{
    return item->unk04;
}

u32 func_00348520(ItemRecord* item)
{
    return item->unk10;
}

void func_00348530(void* object)
{
}

void func_00348540(void* object)
{
}

void func_00348550(void* object)
{
}

void func_00348560(void* object)
{
}

void func_00348570(void* object)
{
}

void func_00348580(void* object)
{
}

void func_00348590(void* object)
{
}

void func_003485A0(void* object)
{
}

void func_003485B0(void* object)
{
}

void func_003485C0(void* object)
{
}

void func_003485D0(void* object)
{
}

void func_003485E0(void* object)
{
}

void func_003485F0(void* object)
{
}

void func_00348600(void* object)
{
}

void func_00348610(void* object)
{
}

void func_00348620(void* object)
{
}

void func_00348630(void* object)
{
}

void func_00348640(void* object)
{
}

s32 func_00348650(void* object)
{
    return 0;
}

s32 func_00348660(void* object)
{
    return 0;
}

s32 func_00348670(void* object)
{
    return 0;
}

s32 func_00348680(void* object)
{
    return 0;
}

s32 func_00348690(void* object)
{
    return 0;
}

s32 func_003486A0(void* object)
{
    return 0;
}

s32 func_003486B0(void* object)
{
    return 0;
}

s32 func_003486C0(void* object)
{
    return 0;
}

s32 func_003486D0(void* object)
{
    return 0;
}

s32 func_003486E0(void* object)
{
    return 0;
}

void func_003486F0(void* object)
{
}

void func_00348700(void* object)
{
}

u8 func_00348710(ItemRecord* item)
{
    return item->unk0d;
}

void func_00348720(ItemRecord* item, u8 value)
{
    item->unk0d = value;
}

void func_00348730(void* object)
{
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00348740);

u32 func_003487B0(ItemRecord* item)
{
    return item->unk20;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003487C0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00348880);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00348940);

void func_003489F0(ItemRecord* item, u32 value)
{
    item->unk20 = value;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00348A00);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00348C40);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003490F0);

s32 func_00349190(Record00349190* record, s32 arg1, s32 arg2, void* arg3, float first, float second, float third)
{
    record->unk6c = 0x6006;
    record->unk20 = 0;
    record->unk24 = 0;
    record->unk28 = 0;
    record->unk2c = 1.0f;
    func_44B110(record, arg1, arg2, arg3, third, 0);
    record->unkb4 = 0;
    record->unkb8 = 0;
    return 1;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003491F0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00349210);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00349250);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003492F0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00349B90);

Record00349BF0* func_00349BF0(Record00349BF0* record, s16 flag)
{
    if (record != 0)
    {
        record->unk2c = D_1844A0;
        func_2BC410(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

u32 func_00349C50(Record00349C50* record)
{
    return record->unk38;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00349C60);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00349F80);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034AD00);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034AE60);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034AE90);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034AEE0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034AF30);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034AFB0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034B060);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034B1B0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034B770);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034B830);

Record0034C6A0* func_0034C6A0(Record0034C6A0* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_175110;
        func_4618F0(&record->unk40, -1);
        func_4C48B0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034C710);

Record0034C7A0* func_0034C7A0(Record0034C7A0* record, s16 flag)
{
    if (record != 0)
    {
        record->unk38 = D_1843F0;
        func_4618F0(record, -1);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

u32 func_0034C800(Record0034C800* record)
{
    return record->unk40;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034C810);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034CD10);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034CD60);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034CDB0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034CE30);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034CEE0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034D030);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034D170);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034E740);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034E7A0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034E7E0);

void func_0034E8B0(Record0034E8B0* record, u8 flag, s32 control_flag)
{
    record->first[0]->unk3f = flag;
    record->second[0]->unk3f = flag;
    record->first[1]->unk3f = flag;
    record->second[1]->unk3f = flag;
    record->first[2]->unk3f = flag;
    record->second[2]->unk3f = flag;
    record->first[3]->unk3f = flag;
    record->second[3]->unk3f = flag;
    record->first[4]->unk3f = flag;
    record->second[4]->unk3f = flag;
    record->first[5]->unk3f = flag;
    record->second[5]->unk3f = flag;
    if (record->unk174 != 0)
    {
        record->unk174->unk3f = 1;
    }
    if (record->unkac != 0)
    {
        record->unkac->unk3f = control_flag;
        if (control_flag != 0)
        {
            struct ControlScreen* screen = record->unkac;
            screen->unk70 = 128.0f;
            screen->unk3c = 1;
        }
        else
        {
            struct ControlScreen* screen = record->unkac;
            screen->unk70 = 64.0f;
            screen->unk3c = 1;
        }
    }
    if (record->unka8 != 0)
    {
        record->unka8->unk3f = control_flag;
    }
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034E980);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034EB40);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034EE60);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034EF40);

void func_0034F2E0(AngleOwner* owner)
{
    if (owner->unk1b0 != 0)
    {
        struct AngleState* angle = owner->unk1b8;
        if (angle != 0)
        {
            float value = angle->unk6c;
            value -= ANGLE_STEP_RADIANS;
            if (value < 0.0f)
            {
                value = 0.0f;
            }
            angle->unk6c = value;
        }
    }
}

void func_0034F340(AngleOwner* owner)
{
    if (owner->unk1b0 != 0)
    {
        struct AngleState* angle = owner->unk1b8;
        if (angle != 0)
        {
            float value = angle->unk6c;
            value += ANGLE_STEP_RADIANS;
            if (value > ANGLE_LIMIT_RADIANS)
            {
                value = ANGLE_LIMIT_RADIANS;
            }
            angle->unk6c = value;
        }
    }
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034F3A0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034F970);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034F9F0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034FB80);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034FE70);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00350B60);

void func_00350BD0(Record00350BD0* record, u8 value)
{
    record->unk12c = value;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00350BE0);

Record00350C20* func_00350C20(Record00350C20* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_1847B0;
        record->unke8 = D_1848A4;
        if (record->unk174 != 0)
        {
            func_4C4A90(record->unk174);
        }
        func_2CD9F0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00350CB0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00350D50);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00350DD0);

void func_00350F70(ControlOwner* owner, s32 ignored, s32 flag)
{
    if (owner->unkac != 0)
    {
        owner->unkac->unk3f = flag;
        if (flag != 0)
        {
            struct ControlScreen* screen = owner->unkac;
            screen->unk70 = 128.0f;
            screen->unk3c = 1;
        }
        else
        {
            struct ControlScreen* screen = owner->unkac;
            screen->unk70 = 64.0f;
            screen->unk3c = 1;
        }
    }
}

void func_00350FC0(Record00350FC0* owner, float start)
{
    s32 index;
    float value = start + 16.0f;
    for (index = 0; index < 14; index++)
    {
        struct SlotRecord* slot = owner->first[index];
        slot->unk18 = 24.0f;
        slot->unk1c = value;
        slot->unk3c = 1;
        slot = owner->second[index];
        slot->unk18 = 326.0f;
        slot->unk1c = value;
        slot->unk3c = 1;
        slot = owner->third[index];
        slot->unk18 = 334.0f;
        slot->unk1c = value;
        slot->unk3c = 1;
        value += 28.0f;
    }
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00351040);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003512C0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00351770);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003518B0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00351D50);

s32 func_00351E40(const ItemListNode* left, const ItemListNode* right)
{
    const ItemSortRecord* first = (const ItemSortRecord*)left->value;
    const ItemSortRecord* second = (const ItemSortRecord*)right->value;
    const ItemSortDefinition* first_definition = &D_001B64F0[first->table_index];
    const ItemSortDefinition* second_definition = &D_001B64F0[second->table_index];
    return (first_definition->sort_key_bits & 0x3FF) - (second_definition->sort_key_bits & 0x3FF);
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00351E80);

ScreenOwner* func_00351F50(ScreenOwner* owner, s16 flag)
{
    if (owner != 0)
    {
        owner->methods = D_1849F0;
        func_2CEAF0(owner, 0);
        if (flag > 0)
        {
            func_100B40(owner);
        }
    }
    return owner;
}

void func_00351FB0(ScreenOwner* owner)
{
    struct ScreenRecord* screen = owner->unka8;
    if (screen != 0)
    {
        screen->unk70 = 128.0f;
        screen->unk3c = 1;
    }
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00351FE0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00352010);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003521D0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00352340);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003524B0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00352540);

Record00352960* func_00352960(Record00352960* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_184AF0;
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003529C0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00352AB0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00352B40);

Record00352EE0* func_00352EE0(Record00352EE0* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_184BF0;
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00352F40);

Record003531B0* func_003531B0(Record003531B0* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_184CF0;
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00353210);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00353270);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00353620);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00353700);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003537D0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00353850);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00353910);

void func_00353A30(void* object)
{
}

void func_00353A40(void* object)
{
}

Record00353A50* func_00353A50(Record00353A50* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_184390;
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00353AA0);

s32 func_00353B00(void* object)
{
    return 3;
}

void func_00353B10(void* object)
{
}

void func_00353B20(void* object)
{
}

void func_00353B30(TransformRecord* record, const Vector4* value)
{
    record->unk50 = 1;
    record->unk20 = *value;
}

void func_00353B50(TransformRecord* record, const Vector4* value)
{
    record->unk50 = 1;
    record->unk20 = *value;
}

void func_00353B70(TransformRecord* record, float x, float y, float z)
{
    record->unk50 = 1;
    record->unk20.x = x;
    record->unk20.y = y;
    record->unk20.z = z;
    record->unk20.w = 1.0f;
}

void func_00353B90(TransformRecord* record, float x, float y, float z, float w)
{
    record->unk50 = 1;
    record->unk30.x = x;
    record->unk30.y = y;
    record->unk30.z = z;
    record->unk30.w = w;
}

void func_00353BB0(TransformRecord* record, const Vector4* value)
{
    record->unk50 = 1;
    record->unk30 = *value;
}

void func_00353BD0(TransformRecord* record, const Vector4* value)
{
    record->unk50 = 1;
    record->unk30 = *value;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00353BF0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00353C20);

void func_00353C50(TransformRecord* record, float x, float y, float z)
{
    Vector4 value;
    record->unk50 = 1;
    value.x = x;
    value.y = y;
    value.z = z;
    value.w = 1.0f;
    func_4CE4C0(&record->unk30, &value);
}

void func_00353C90(TransformRecord* record, const Vector4* value)
{
    record->unk50 = 1;
    record->unk40 = *value;
}

void func_00353CB0(TransformRecord* record, const Vector4* value)
{
    record->unk50 = 1;
    record->unk40 = *value;
}

void func_00353CD0(TransformRecord* record, float x, float y, float z)
{
    record->unk50 = 1;
    record->unk40.x = x;
    record->unk40.y = y;
    record->unk40.z = z;
}

s32 func_00353CF0(void* object)
{
    return 0;
}

s32 func_00353D00(float value)
{
    return value < 0.0f;
}

u8* func_00353D20(void)
{
    return D_50CD30;
}

s32 func_00353D30(void* object)
{
    return 0;
}

void func_00353D40(void* object)
{
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00353D50);

void func_00353E10(void* object)
{
}

s32 func_00353E20(void* object)
{
    return 14;
}

void func_00353E30(DisplayRecord* display)
{
    display->unk60 = display->unka8;
}

DisplayRecord* func_00353E40(DisplayRecord* display, s16 flag)
{
    if (display != 0)
    {
        display->methods = D_1844B0;
        func_2CEAF0(display, 0);
        if (flag > 0)
        {
            func_100B40(display);
        }
    }
    return display;
}

void func_00353EA0(void* object)
{
}

void func_00353EB0(void* object)
{
}

void func_00353EC0(void* object)
{
}

s32 func_00353ED0(void* object)
{
    return 0;
}

s32 func_00353EE0(void* object)
{
    return 0;
}

Record00353EF0* func_00353EF0(Record00353EF0* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_1848D0;
        record->unke8 = D_1849C4;
        func_003542F0(&record->embedded, -1);
        func_2CD9F0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

void func_00353F70(StatusRecord* state, u32 value)
{
    state->unk24 = value;
}

u32 func_00353F80(StatusRecord* state)
{
    return state->unk24;
}

void func_00353F90(StatusRecord* state, s8 value)
{
    state->unk28 = value;
}

s8 func_00353FA0(StatusRecord* state)
{
    return state->unk28;
}

s32 func_00353FB0(void* object)
{
    return 0;
}

s32 func_00353FC0(void* object)
{
    return 0;
}

void func_00353FD0(void* object)
{
}

void func_00353FE0(void* object)
{
}

void func_00353FF0(void* object)
{
}

void func_00354000(void* object)
{
}

s32 func_00354010(void* object)
{
    return 0;
}

s32 func_00354020(void* object)
{
    return 0;
}

s32 func_00354030(void* object)
{
    return 0;
}

s32 func_00354040(void* object)
{
    return 4;
}

u32 func_00354050(StatusRecord* state)
{
    return state->unk3c & 1;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354060);

Record003540E0* func_003540E0(Record003540E0* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_184ED8;
        func_003541F0(record);
        if (record->head != 0)
        {
            func_100B40(record->head);
            record->head = 0;
        }
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354160);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003541F0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354270);

Record003542F0* func_003542F0(Record003542F0* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_184EC8;
        func_00354400(record);
        if (record->head != 0)
        {
            func_100B40(record->head);
            record->head = 0;
        }
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

void func_00354370(ItemListOwner* owner, void* value)
{
    ItemListNode* node = (ItemListNode*)func_00100AC0(sizeof(ItemListNode), 0);
    if (node != 0)
    {
        ItemListNode* tail;
        node->value = value;
        node->next = 0;
        tail = owner->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        owner->count++;
    }
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354400);

ItemListNode* func_00354480(ItemListOwner* owner, s32 index)
{
    ItemListNode* node = owner->head->next;
    s32 i;
    for (i = 0; i < index; i++)
    {
        if (node == 0)
        {
            return 0;
        }
        node = node->next;
    }
    return node;
}

void func_003544C0(ItemListOwner* owner, void* value)
{
    ItemListNode* node = (ItemListNode*)func_00100AC0(sizeof(ItemListNode), 0);
    if (node != 0)
    {
        ItemListNode* tail;
        node->value = value;
        node->next = 0;
        tail = owner->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        owner->count++;
    }
}

void func_00354550(ItemListOwner* owner, void* value)
{
    ItemListNode* node = (ItemListNode*)func_00100AC0(sizeof(ItemListNode), 0);
    if (node != 0)
    {
        ItemListNode* tail;
        node->value = value;
        node->next = 0;
        tail = owner->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        owner->count++;
    }
}

ItemListNode* func_003545E0(ItemListOwner* owner, s32 index)
{
    ItemListNode* node = owner->head->next;
    s32 i;
    for (i = 0; i < index; i++)
    {
        if (node == 0)
        {
            return 0;
        }
        node = node->next;
    }
    return node;
}

void func_00354620(ItemListOwner* owner, void* value)
{
    ItemListNode* node = (ItemListNode*)func_00100AC0(sizeof(ItemListNode), 0);
    if (node != 0)
    {
        ItemListNode* tail;
        node->value = value;
        node->next = 0;
        tail = owner->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        owner->count++;
    }
}

void func_003546B0(ItemListOwner* owner, void* value)
{
    ItemListNode* node = (ItemListNode*)func_00100AC0(sizeof(ItemListNode), 0);
    if (node != 0)
    {
        ItemListNode* tail;
        node->value = value;
        node->next = 0;
        tail = owner->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        owner->count++;
    }
}

Record00354740* func_00354740(Record00354740* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_184EB8;
        func_003547C0(record);
        if (record->head != 0)
        {
            func_100B40(record->head);
            record->head = 0;
        }
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003547C0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354840);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003548F0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354980);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354AA0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354AB0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354AC0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354AD0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354AE0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354AF0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354B00);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354B10);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354B20);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354B30);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354B40);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354B50);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354B60);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354B70);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354B80);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354B90);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354BA0);
