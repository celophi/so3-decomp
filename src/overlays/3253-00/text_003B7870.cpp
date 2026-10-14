#include "include_asm.h"
#include "overlays/3253-00/text_003B7870.h"

/** Partial nested state reached through the receiver's +0x50 pointer. */
struct BattleNestedStateView
{
    u8 pad00[0x20];
    u32 value20;
    u8 pad24[0x08];
    float value2C;
    u8 pad30[0x1C];
    float value4C;
    u8 pad50[0x10];
    u32 value60;
    u8 pad64[0x518];
    float value57C;
};

/** Receiver fields used by the nested state accessors. */
struct BattleStateOwnerView
{
    u8 pad00[0x44];
    u32 unk44;
    u8 pad48[0x08];
    BattleNestedStateView* state;
    u32 unk54;
    s32 state_index;
};

struct BattleWord1CView
{
    u8 pad00[0x1C];
    u32 value1C;
};

struct BattleIndexedEntryView
{
    u8 pad00[0x78];
    u32 state;
    u8 active;
};

struct BattleIndexedOwnerView
{
    u8 pad00[0x14];
    BattleIndexedEntryView* entries;
};

struct BattleRecordView
{
    float first;
    float second;
    u32 value08;
    u32 value0C;
    u32 value10;
    u32 value14;
    u8 pad18[0x08];
    u8 flags;
};

struct BattleRecordTableView
{
    u8 pad00[0x450];
    BattleRecordView records[1];
};

struct BattleFlag38CView
{
    u8 pad00[0x38C];
    u8 flags;
};

struct BattleFlag1CCView
{
    u8 pad00[0x1CC];
    u8 flags;
};

struct BattleReady36CView
{
    u8 pad00[0x36C];
    u8 ready;
};

struct BattleWord14View
{
    u8 pad00[0x14];
    u32 value14;
};

struct BattleByte1ACView
{
    u8 pad00[0x1AC];
    u8 value1AC;
};

struct BattleByte518View
{
    u8 pad00[0x518];
    u8 value518;
};

extern "C" float func_003C9460(BattleNestedStateView* state, s32 index);
extern "C" void func_003ADF00(void* object);
extern "C" void func_003AEAB0(void* object);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003B7870);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003B7930);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003B79F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003B7DF0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003B7F70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003B8210);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003B8390);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003B8400);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003B8530);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003B8600);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003B8980);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003B8A10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003B8A80);

s32 func_003B8B30(const void* object)
{
    const BattleWord14View* state = (const BattleWord14View*)object;
    return state->value14 != 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003B8B40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003B8C10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003B8CD0);

void func_003B8D30(void* object, s32 index)
{
    BattleIndexedOwnerView* owner = (BattleIndexedOwnerView*)object;
    BattleIndexedEntryView* entry = &owner->entries[index];
    entry->active = 1;
    entry->state = 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003B8D50);

u32 func_003B9000(void* object)
{
    BattleWord1CView* state = (BattleWord1CView*)object;
    return state->value1C;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003B9010);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003B9310);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003B9430);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003B98D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003B9930);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003B99F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003B9B30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003B9BB0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003B9E90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003B9F20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003BA170);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003BA850);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003BAAD0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003BAC90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003BAF70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003BB920);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003BBA40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003BC3A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003BC4A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003BC540);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003BC6C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003BCF10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003BD030);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003BD770);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003BD850);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003BD900);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003BDCE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003BE3D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003BE560);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003BEE00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003BEF60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003BF060);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003BF600);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003BFD20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003BFE40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003BFEE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C05D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C0940);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C1060);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C12A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C13A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C1440);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C1550);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C1730);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C1A80);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C1E10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C1F60);

void func_003C1FF0(void* object)
{
    BattleByte1ACView* state = (BattleByte1ACView*)object;
    state->value1AC = 2;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C2000);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C20C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C2FF0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C30E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C31A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C3270);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C3570);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C35C0);

void func_003C36B0(void* object, s32 index, u32 value)
{
    BattleRecordTableView* table = (BattleRecordTableView*)object;
    BattleRecordView* record = &table->records[index];
    record->flags |= 0x10;
    record->value14 = value;
}

void func_003C36E0(void* object, s32 index, u32 value)
{
    BattleRecordTableView* table = (BattleRecordTableView*)object;
    BattleRecordView* record = &table->records[index];
    record->flags |= 0x08;
    record->value10 = value;
}

void func_003C3710(void* object, s32 index, u32 value)
{
    BattleRecordTableView* table = (BattleRecordTableView*)object;
    BattleRecordView* record = &table->records[index];
    record->flags |= 0x04;
    record->value0C = value;
}

void func_003C3740(void* object, s32 index, u32 value)
{
    BattleRecordTableView* table = (BattleRecordTableView*)object;
    BattleRecordView* record = &table->records[index];
    record->flags |= 0x02;
    record->value08 = value;
}

void func_003C3770(void* object, s32 index, float first, float second)
{
    BattleRecordTableView* table = (BattleRecordTableView*)object;
    BattleRecordView* record = &table->records[index];
    record->flags |= 0x01;
    record->first = first;
    record->second = second;
}

void func_003C37A0(void* object, s32 index)
{
    /* This callback accesses the record array at +0x450 from the owner. */
    BattleRecordView* record = (BattleRecordView*)((u8*)object + index * sizeof(BattleRecordView) + 0x450);
    record->flags |= 0x20;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C37C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C3800);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C38B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C3B80);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C3BC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C3CA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C3CE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C3EB0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C3F40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C3FC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C40E0);

void func_003C4680(void* object)
{
    BattleFlag38CView* state = (BattleFlag38CView*)object;
    state->flags |= 0x20;
    func_003ADF00(object);
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C46B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C46F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C48C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C4940);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C4A60);

void func_003C5010(void* object)
{
    BattleFlag1CCView* state = (BattleFlag1CCView*)object;
    state->flags |= 0x20;
    func_003AEAB0(object);
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C5040);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C53C0);

void func_003C5430(void* object)
{
    BattleReady36CView* state = (BattleReady36CView*)object;
    if (state->ready == 0)
    {
        state->ready = 1;
    }
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C5450);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C57D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C5840);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C59C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C5A20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C5A80);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C5BA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C5C80);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C5EA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C5F70);

void* func_003C6040(void* object)
{
    BattleStateOwnerView* owner = (BattleStateOwnerView*)object;
    return &owner->state->value60;
}

float func_003C6050(void* object)
{
    BattleStateOwnerView* owner = (BattleStateOwnerView*)object;
    return owner->state->value4C;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C6060);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C60F0);

float func_003C6120(void* object)
{
    BattleStateOwnerView* owner = (BattleStateOwnerView*)object;
    return owner->state->value2C * (1.0f / 128.0f);
}

void func_003C6140(void* object)
{
}

void func_003C6150(void* object)
{
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C6160);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C6390);

void* func_003C6420(void* object)
{
    BattleStateOwnerView* owner = (BattleStateOwnerView*)object;
    return &owner->state->value20;
}

float func_003C6430(void* object)
{
    BattleStateOwnerView* owner = (BattleStateOwnerView*)object;
    return owner->state->value57C;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C6440);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C64D0);

void func_003C6530(void* object)
{
    BattleStateOwnerView* owner = (BattleStateOwnerView*)object;
    func_003C9460(owner->state, owner->state_index);
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C6550);

s32 func_003C65C0(void* object)
{
    return 3;
}

s32 func_003C65D0(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C65E0);

void func_003C6660(void* object)
{
}

s32 func_003C6670(void* object)
{
    return 1;
}

s32 func_003C6680(void* object)
{
    return 3;
}

s32 func_003C6690(void* object)
{
    return 1;
}

void func_003C66A0(void* object)
{
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C66B0);

s32 func_003C6800(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C6810);

void func_003C6890(void* object)
{
}

s32 func_003C68A0(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C68B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C6950);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C69C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C6A20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C6A60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C6AC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C6B00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C6B60);

void func_003C6BA0(void* object)
{
}

s32 func_003C6BB0(void* object)
{
    return 1;
}

s32 func_003C6BC0(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C6BD0);
INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C6C00);

s32 func_003C6C30(void* object)
{
    return 3;
}

s32 func_003C6C40(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C6C50);

s32 func_003C6DA0(void* object)
{
    return 1;
}

void func_003C6DB0(void* object)
{
    BattleByte518View* state = (BattleByte518View*)object;
    state->value518 = 1;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C6DC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C6EB0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C6F90);
INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C6FC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C6FF0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C7060);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C70D0);

void func_003C7140(void* object)
{
}

s32 func_003C7150(void* object)
{
    return 3;
}

void func_003C7160(void* object)
{
}

s32 func_003C7170(void* object)
{
    return 1;
}

void func_003C7180(void* object)
{
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C7190);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C7230);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C72F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C73B0);

s32 func_003C7450(void* object)
{
    return 3;
}

void func_003C7460(void* object)
{
    BattleStateOwnerView* owner = (BattleStateOwnerView*)object;
    owner->unk44 = 0;
}

float func_003C7470(void* object)
{
    return 1.0f;
}

s32 func_003C7480(void* object)
{
    return 1;
}

s32 func_003C7490(void* object)
{
    return 3;
}

void func_003C74A0(void* object)
{
    BattleStateOwnerView* owner = (BattleStateOwnerView*)object;
    owner->unk44 = 0;
}

float func_003C74B0(void* object)
{
    return 1.0f;
}

s32 func_003C74C0(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003B7870", func_003C74D0);
