#include "include_asm.h"
#include "types.h"

extern "C" void func_003776F0(void* first, void* second, void* third, void* fourth, u32 flags);
extern "C" void func_0035D2B0(void* object, s32 value);

extern "C" void func_00338840(void* object, s32 value);

extern "C" void func_00335240(void* object, s32 value);

extern "C" void func_0032E520(void* object, s32 value);
#include "overlays/3454-00/text_00370690.h"

extern "C" {
void func_0027E740(void* object);
void func_0027EAF0(void* object);
s32 func_0027E420(void);
void func_00318860(void* object);
void func_003527E0(void* object);
void func_003B41F0(void* object);
INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00370690);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00370710);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00370780);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00370840);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003708B0);

void func_00370920(void* object)
{
    func_00318860(object);
}

void func_00370940(void* object)
{
    func_00318860(object);
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00370960);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003709D0);

void func_00370A40(void* object)
{
}

void func_00370A50(void* object)
{
    u8* state = static_cast<u8*>(object);
    if (*(u32*)(state + 0x284) == 0)
    {
        func_003B41F0(state + 0xD0);
        state[0x1DD] = 0;
        (*(u32*)(state + 0x284))++;
    }
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00370A90);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00370B00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00370B70);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00370BE0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00370C50);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00370CC0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00370D30);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00370DA0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00370E10);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00370E80);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00370EF0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00370F60);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00370FD0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00371040);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003710B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00371120);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00371190);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00371250);

void func_003712C0(void* object)
{
    func_0032E520(object, 0);
}

extern "C" void func_003712E0(void* object)
{
    func_0032E520(object, 1);
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00371300);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003713F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00371460);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003714D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00371540);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003715B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00371620);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00371690);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003716F0);

void func_00371730(void* object)
{
    func_00335240(object, 0);
}

extern "C" void func_00371750(void* object)
{
    func_00335240(object, 1);
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00371770);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003717E0);

struct FloatField6A8_00370690 { u8 pad[0x6A8]; float value; };

void func_00371850(void* object)
{
    if (((FloatField6A8_00370690*)object)->value == 0.0f)
    {
        func_0027EAF0(object);
    }
}

void func_00371890(void* object)
{
    if (((FloatField6A8_00370690*)object)->value == 0.0f)
    {
        func_0027E740(object);
    }
}

s32 func_003718D0(void* object)
{
    if (((FloatField6A8_00370690*)object)->value != 0.0f)
    {
        return 0;
    }
    return func_0027E420();
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00371910);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00371960);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003719B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00371A00);

extern "C" void func_00371A70(void* object)
{
    func_00338840(object, 2);
}

extern "C" void func_00371A90(void* object)
{
    func_00338840(object, 5);
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00371AB0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00371B20);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00371B90);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00371C00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00371C70);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00371CE0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00371D50);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00371DC0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00371E30);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00371EA0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00371F10);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00371F70);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00371FE0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00372050);

void func_003720C0(void* object)
{
    if (((FloatField6A8_00370690*)object)->value == 0.0f)
    {
        func_0027EAF0(object);
    }
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00372100);

s32 func_00372150(void* object)
{
    if (((FloatField6A8_00370690*)object)->value != 0.0f)
    {
        return 0;
    }
    return func_0027E420();
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00372190);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003721E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00372230);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003722A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00372310);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00372380);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003723F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00372460);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003724C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00372530);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003725F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00372650);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003726C0);

void func_00372730(void* object)
{
    if (((FloatField6A8_00370690*)object)->value == 0.0f)
    {
        func_0027EAF0(object);
    }
}

void func_00372770(void* object)
{
    if (((FloatField6A8_00370690*)object)->value == 0.0f)
    {
        func_0027E740(object);
    }
}

s32 func_003727B0(void* object)
{
    if (((FloatField6A8_00370690*)object)->value != 0.0f)
    {
        return 0;
    }
    return func_0027E420();
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003727F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00372840);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00372890);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003728E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00372950);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003729C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00372A30);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00372A70);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00372AB0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00372B40);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00372BB0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00372C00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00372C70);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00372CE0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00372D50);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00372DC0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00372E30);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00372EA0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00372F10);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00372F80);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00372FF0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00373060);

void func_003730D0(void* object)
{
    func_003527E0(object);
}

void func_003730F0(void* object)
{
    func_003527E0(object);
}

void func_00373110(void* object)
{
    func_003527E0(object);
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00373130);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003731A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00373210);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00373280);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003732F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00373360);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003733D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00373440);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003734B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00373570);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003735E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003736A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00373710);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00373780);

void func_003737F0(void* object)
{
    func_0035D2B0(object, 0);
}

extern "C" void func_00373810(void* object)
{
    func_0035D2B0(object, 1);
}

void func_00373830(void* object)
{
    if (((FloatField6A8_00370690*)object)->value == 0.0f)
    {
        func_0027EAF0(object);
    }
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00373870);

s32 func_003738D0(void* object)
{
    if (((FloatField6A8_00370690*)object)->value != 0.0f)
    {
        return 0;
    }
    return func_0027E420();
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00373910);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00373960);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003739E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00373A30);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00373AA0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00373B10);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00373B80);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00373BF0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00373C70);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00373CE0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00373D50);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00373DC0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00373DD0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00373E40);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00373EE0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00373F50);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00373FC0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374030);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003740A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374110);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374160);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003741B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374220);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374290);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003742E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374330);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003743A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003744C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003745E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003746F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374700);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374710);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374720);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374730);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374740);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374750);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374760);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374770);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374780);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374790);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003747A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003747B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003747C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003747D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003747E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003747F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374800);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374810);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374820);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374830);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374840);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374850);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374860);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374870);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374880);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374890);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003748A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003748B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003748C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003748D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003748E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003748F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374900);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374910);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374920);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374930);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374940);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374950);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374960);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374970);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374980);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374990);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003749A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003749B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003749C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003749D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003749E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003749F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374A00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374A10);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374A20);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374A30);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374A40);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374A50);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374A60);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374A70);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374A80);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374A90);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374AA0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374AB0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374AC0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374AD0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374AE0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374AF0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374B00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374B10);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374B20);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374B30);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374B40);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374B50);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374B60);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374B70);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374B80);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374B90);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374BA0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374BB0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374C70);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00374E50);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003750E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00375180);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00375240);

void func_00375280(u8* receiver, void* value1, void* value2, void* value3)
{
    u8* adjusted = receiver;
    if (adjusted != 0) {
        adjusted = adjusted + 0xD0;
    }
    func_003776F0(receiver + 0x220, adjusted, value1, value2, 1);
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003752C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00375380);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00375600);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003756C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00375980);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00375A70);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00375C80);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00375F30);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00375FA0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00376050);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00376410);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003766F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003768E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00376990);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00376C90);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00376FF0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00377080);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003770D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00377130);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00377190);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003772A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003773A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00377550);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00377630);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003776F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003779B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003779E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00377A40);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_0037B590);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_0037B6D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_0037B8C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_0037BB30);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_0037BD80);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_0037BE60);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_0037CB90);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_0037CE00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_0037CFD0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_0037D290);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_0037D400);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_0037D8E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_0037DAA0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_0037DC00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_0037DC70);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_0037DEE0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_0037E2E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_0037E480);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_0037E5E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_0037F930);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_0037FD20);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_0037FE70);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_003800C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00380250);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_00370690", func_00380530);

}
