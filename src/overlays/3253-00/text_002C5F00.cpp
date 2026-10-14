#include "include_asm.h"
#include "types.h"
#include "overlays/3253-00/text_002C5F00.h"

extern "C" u32 func_4A0B70(u32 value, const void* data);
extern "C" const u8 D_3E2B38[];

/** Packed four-component value initialized to the identity quaternion. */
union BattleQuaternionView
{
    unsigned __int128 packed;
    u32 components[4];
};

struct BattleHalfword6EView
{
    u8 pad00[0x6E];
    u16 value;
};

struct BattleVector4View
{
    float x;
    float y;
    float z;
    float w;
};

struct BattleObject5FA0View
{
    void* methods;
    u8 pad04[0x20C];
    u32 value210;
    u32 value214;
};

struct BattleObject67A0View
{
    void* methods;
    u8 pad04[0x2A4];
    void* handler;
    u8 pad2AC[0xA4];
    float value350;
    u8 pad354[0x19];
    u8 flag36D;
    u8 pad36E[0xF2];
    u32 value460;
    u32 value464;
    u32 value468;
    u8 pad46C[0x44];
    u8 flag4B0;
    u8 flag4B1;
};

struct BattleObject7760View
{
    u8 pad00[0x5BC];
    u8 flags;
};

extern "C" void func_4DD1F0(void* object);
extern "C" u32 D_17C610[];
extern "C" void func_003AE200(void* object);
extern "C" u32 D_15B600[];
extern "C" u32 D_15B624[];
extern "C" u8 func_003C3B80(void* object);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002C5F00);

extern "C" void func_002C5F60(BattleQuaternionView* value)
{
    value->packed = 0;
    value->components[3] = 0x3F800000;
}

extern "C" void func_002C5F70(BattleHalfword6EView* object, u16 value)
{
    object->value = value;
}

extern "C" BattleVector4View* func_002C5F80(BattleVector4View* value, float component)
{
    value->x = component;
    value->y = component;
    value->z = component;
    value->w = component;
    return value;
}

extern "C" BattleObject5FA0View* func_002C5FA0(BattleObject5FA0View* object)
{
    func_4DD1F0(object);
    object->methods = D_17C610;
    object->value210 = 0;
    object->value214 = 0;
    return object;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002C5FE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002C6270);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002C66B0);

extern "C" BattleObject67A0View* func_002C67A0(BattleObject67A0View* object)
{
    func_003AE200(object);
    object->methods = D_15B600;
    object->handler = D_15B624;
    object->flag36D = 0;
    object->flag4B0 = 0;
    object->flag4B1 = 0;
    object->value460 = 0;
    object->value464 = 0;
    object->value468 = 0;
    object->value350 = 20.0f;
    return object;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002C6800);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002C68C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002C6FC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002C75E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002C7630);

extern "C" s32 func_002C7760(BattleObject7760View* object)
{
    if (func_003C3B80(object) == 0)
    {
        return 0;
    }

    object->flags |= 0x80;
    return 1;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002C77B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002C7940);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002C8690);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002C8750);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002C8850);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002C93E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002C9430);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002C97D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002C9810);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002C9F50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CA010);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CA130);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CA2F0);

extern "C" void func_002CA3A0(void* object)
{
    struct NestedWordResultOwnertext_002C5F00
    {
        u8 unk00[0x50];
        u32 unk50;
        u8 unk54[0x3DC];
        u32 unk430;
        u8 unk434[0x30];
        u32 unk464;
    }* receiver = static_cast<struct NestedWordResultOwnertext_002C5F00*>(object);
    receiver->unk464 = func_4A0B70(receiver->unk50, D_3E2B38);
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CA3E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CB120);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CB220);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CB4A0);

extern "C" void func_002CB4F0(void* object)
{
    struct NestedWordResultOwnertext_002C5F00
    {
        u8 unk00[0x50];
        u32 unk50;
        u8 unk54[0x1CC];
        u32 unk220;
        u32 unk224;
    }* receiver = static_cast<struct NestedWordResultOwnertext_002C5F00*>(object);
    receiver->unk224 = func_4A0B70(receiver->unk50, D_3E2B38);
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CB530);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CBDE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CBEA0);

void func_002CBED0(void* object)
{
    ((u8*)object)[0x391] = 1;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CBEE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CC5A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CC650);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CC720);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CCB20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CD150);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CD2B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CD320);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CD670);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CD710);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CD7D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CDCB0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CDDB0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CDEF0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CE110);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CE640);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CE750);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CE9A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CEA90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CEAE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CEB40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CEC10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CEF30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CF250);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CF2A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CF340);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CF460);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CFBC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CFFA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002CFFD0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002D07F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002D08B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002D15D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002D1670);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002D1770);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002D1DA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002D1E70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002D23C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002D26E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002D2960);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002D3420);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002D34E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002D3630);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002D4810);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002D48B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002D4990);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002D53C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002D5490);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002C5F00", func_002D59D0);
