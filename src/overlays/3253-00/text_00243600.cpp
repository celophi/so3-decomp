#include "include_asm.h"
#include "overlays/3253-00/text_00243600.h"

extern "C" void func_459DB0(void* object);
extern "C" void func_459960(void* object);

struct BattleByte92
{
    u8 unk00[0x92];
    u8 unk92;
};

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00243600);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00243860);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00243BF0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00243C50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00244530);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00244B80);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00244C70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00245220);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00245290);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00245750);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_002457C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00245850);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_002458A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00245950);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_002459C0);

extern "C" void func_4D45F0(void);

extern "C" void func_00245A80(void)
{
    func_4D45F0();
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00245AA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00246250);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00246460);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00246680);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_002471F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00247820);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00248660);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00248A70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00248D00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00248EB0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00248FB0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00249470);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00249550);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024A020);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024A400);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024A600);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024A6D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024A760);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024A840);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024A8F0);

extern "C" s32 func_0024A960(void* receiver, void* arg1, s32 arg2, s32 arg3)
{
    BattleByte92* object = (BattleByte92*)receiver;
    object->unk92 = 0;
    return func_0024A980(receiver, arg1, arg2, arg3);
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024A980);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024AB60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024ABF0);

void func_0024AD60(void* object)
{
    func_459DB0((u8*)object + 0x5A4);
    func_459960(object);
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024AD90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024B0B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024B100);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024B1B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024B270);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024B2E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024B570);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024B590);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024B670);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024B820);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024B8F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024BAB0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024BF30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024C3D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024C500);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024C7E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024CD20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024D170);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024D670);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024E4E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024E870);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024E9A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024F190);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024F8D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024F9C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024FCA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_0024FE80);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00250560);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00250640);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_002507C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_002508A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00250960);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00250980);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00250A30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00250B30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00250B60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00250DF0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00250F80);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00251420);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00251890);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00251B00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00251E40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00252360);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_002529B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00252F40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00243600", func_00253480);
