#include "include_asm.h"
#include "overlays/3454-00/text_002BF510.h"

typedef struct ConstantByteSetterOwnertext_002BF510
{
    u8 unk00[0x39D];
    u8 unk39d;
} ConstantByteSetterOwnertext_002BF510;

typedef struct NestedWordResultOwnertext_002BF510
{
    u8 unk00[0x50];
    u32 unk50;
    u8 unk54[0x1DC];
    u32 unk230;
    u32 unk234;
    u8 unk238[0x228];
    u32 unk460;
    u8 unk464[0x10];
    u32 unk474;
} NestedWordResultOwnertext_002BF510;

extern u32 func_473390(u32 value, const void* data);
extern const u8 D_3E08F0[];
extern const u8 D_3E06E0[];



INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002BF510);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002BF560);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002BF720);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C02F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C03B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C04B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C0DB0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C0E00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C1060);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C10A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C18B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C1970);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C1A90);

void func_002C1B40(void* object)
{
    NestedWordResultOwnertext_002BF510* receiver = object;
    receiver->unk474 = func_473390(receiver->unk50, D_3E08F0);
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C1B80);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C2970);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C2A70);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C2C10);

void func_002C2C60(void* object)
{
    NestedWordResultOwnertext_002BF510* receiver = object;
    receiver->unk234 = func_473390(receiver->unk50, D_3E08F0);
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C2CA0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C3620);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C36E0);

/** Store 0x1 at receiver offset 0x39D. */
void func_002C3710(void* object)
{
    ConstantByteSetterOwnertext_002BF510* receiver = object;
    receiver->unk39d = 0x1;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C3720);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C3BD0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C3C80);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C3D50);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C40C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C4560);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C4620);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C4690);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C4A00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C4AA0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C4B60);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C4EF0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C4FF0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C5130);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C5350);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C56D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C57E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C5A30);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C5B30);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C5B80);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C5C50);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C5D70);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C6080);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C60D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C6170);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C6290);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C68A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C6C80);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C6CB0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C73F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C74B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C7520);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C7570);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C7ED0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C7F70);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C7FE0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C80E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C8620);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C86F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C8A10);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C8C60);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C8E60);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C9710);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C97D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002C9920);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CA850);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CA8F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CA9D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CB0E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CB1B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CB4B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CBA20);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CBCA0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CBD80);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CC190);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CC3A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CC400);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CC5C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CC6B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CCCB0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CCDA0);

void func_002CCE00(void* object)
{
    NestedWordResultOwnertext_002BF510* receiver = object;
    receiver->unk460 = func_473390(receiver->unk50, D_3E06E0);
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CCE40);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CCFC0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CD060);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CD130);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CD480);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CD4C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CD5C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CD730);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CDCA0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CE680);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CE840);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CEEC0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CEFE0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CF100);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002BF510", func_002CF490);
