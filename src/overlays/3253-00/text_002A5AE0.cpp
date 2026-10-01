#include "include_asm.h"
#include "overlays/3253-00/text_002A5AE0.h"

struct BattleFloat714
{
    u8 pad[0x714];
    float value;
};

struct BattleFloat704
{
    u8 pad[0x704];
    float value;
};

struct BattleFloat6D0
{
    u8 pad[0x6D0];
    float value;
};

struct BattleObjectEC
{
    u8 pad[0xE8];
    u8 unkE8;
    u8 unkE9;
    u8 padEA[2];
    u8 unkEC;
};

struct BattleObject1F8
{
    u8 pad[0x1F8];
    u32 unk1F8;
};

struct BattleObject101
{
    u8 pad[0x101];
    u8 unk101;
};

struct BattleObject178
{
    u8 pad[0x14];
    u32 unk14;
    u8 pad18[0x178 - 0x18];
    u32 unk178;
};

struct BattleChild20B
{
    u8 pad[0x90];
    float unk90;
    u8 pad94[0x204 - 0x94];
    u8 unk204;
    u8 pad205[3];
    u8 unk208;
    u8 unk209;
    u8 pad20A;
    u8 unk20B;
};

struct BattleParent23
{
    BattleChild20B* children[8];
    u8 pad20[3];
    u8 selector;
};

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002A5AE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002A5B60);

void func_002A6030(void* object)
{
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002A6040);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002A60A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002A6570);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002A6780);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002A69F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002A7190);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002A7560);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002A7690);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002A7730);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002A78F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002A7A00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002A7AA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002A7B20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002A8290);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002A9410);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002A9910);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002A9AC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002A9B10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002A9B60);

s32 func_002ACB80(void* object)
{
    return 0;
}

s32 func_002ACB90(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002ACBA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002AD6F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002AD7E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002ADF60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002AE5F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002AE940);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002AEEA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002AEF40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002AEFD0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002AF300);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002AF3A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002AF430);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002AF860);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002AF900);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002AF9C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002AFDC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002AFE70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002AFF00);

void func_002AFF90(BattleFloat714* object, float next)
{
    if (object->value <= next)
    {
        object->value = next;
    }
}

void func_002AFFB0(BattleFloat704* object, float next)
{
    if (object->value <= next)
    {
        object->value = next;
    }
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002AFFD0);

void func_002B0000(BattleFloat6D0* object, float next)
{
    if (object->value <= next)
    {
        object->value = next;
    }
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B0020);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B0450);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B04B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B0540);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B05C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B0700);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B0860);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B08B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B0DA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B10C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B11B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B1250);

void func_002B14D0(void* object)
{
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B14E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B1800);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B19B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B1D60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B1E10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B1EB0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B1F80);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B2030);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B2110);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B21C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B2230);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B22F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B23B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B24A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B2560);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B2B70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B2C10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B30E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B3270);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B32B0);

void func_002B3380(BattleObjectEC* object)
{
    object->unkE8 = 0;
    object->unkE9 = 0;
    object->unkEC = 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B3390);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B3490);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B3600);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B3620);

void func_002B3690(BattleObject1F8* object, u32 value)
{
    object->unk1F8 = value;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B36A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B38A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B39A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B3A80);

void func_002B3B60(BattleParent23* object)
{
    BattleChild20B* child = object->children[object->selector];
    if (child)
    {
        child->unk204 = 0;
    }
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B3B90);

void func_002B3BC0(BattleParent23* object, u8 value)
{
    BattleChild20B* child = object->children[object->selector];
    if (child)
    {
        child->unk209 = value;
    }
}

void func_002B3BF0(BattleParent23* object)
{
    BattleChild20B* child = object->children[object->selector];
    if (child)
    {
        child->unk20B = 1;
    }
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B3C20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B3CA0);

void func_002B3CD0(BattleParent23* object, u8 value)
{
    BattleChild20B* child = object->children[object->selector];
    if (child)
    {
        child->unk208 = value;
    }
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B3D00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B3D40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B3D70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B3DA0);

void func_002B3DD0(BattleParent23* object, float value)
{
    BattleChild20B* child = object->children[object->selector];
    if (child)
    {
        child->unk90 = value;
    }
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B3E00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B3E80);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B3F20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B3FB0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B4360);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B4400);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B4490);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B4540);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B4660);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B46B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B48A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B48E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B4A90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B4B30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B5070);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B5150);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B5280);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B5380);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B5430);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B5490);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B54F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B5550);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B5670);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B5790);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B58A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B5900);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B5960);

void func_002B59C0(void* object)
{
}

s32 func_002B59D0(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B59E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B5A00);

void func_002B5A20(void* object)
{
}

void func_002B5A30(BattleObject101* object)
{
    object->unk101 = 1;
}

void func_002B5A40(BattleObject101* object)
{
    object->unk101 = 1;
}

void func_002B5A50(BattleObject101* object)
{
    object->unk101 = 1;
}

s32 func_002B5A60(void* object)
{
    return 1;
}

void func_002B5A70(BattleObject178* object)
{
    object->unk14 = object->unk178;
}

void func_002B5A80(void* object)
{
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002A5AE0", func_002B5A90);
