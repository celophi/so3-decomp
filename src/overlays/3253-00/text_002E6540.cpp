#include "include_asm.h"
#include "overlays/3253-00/text_002E6540.h"

extern "C" void func_002EDC10(void* object, void* context);
extern "C" void func_003AF250(void* object);
extern "C" void func_002B3270(void* object);
extern "C" u32 func_4A0B70(u32 value, const void* data);
extern "C" const u8 D_3E3600[];
extern "C" const u8 D_3E42F8[];

struct N57Owner5D0
{
    u8 unk00[0x50];
    u32 unk50;
    u8 unk54[0x57C];
    u32 unk5d0;
};

struct N57Owner500
{
    u8 unk00[0x50];
    u32 unk50;
    u8 unk54[0x4AC];
    u32 unk500;
};

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002E6540);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002E65B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002E6910);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002E6B70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002E6DC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002E6E60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002E74B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002E7A80);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002E8390);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002E8450);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002E91A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002E9250);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002E9310);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002E93E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002E9B50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002E9F90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002EA270);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002EA340);

void func_002EA900(void* receiver)
{
    N57Owner5D0* object = (N57Owner5D0*)receiver;
    func_002B3270(receiver);
    object->unk5d0 = func_4A0B70(object->unk50, D_3E3600);
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002EA940);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002EAE70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002EB050);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002EB130);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002EB910);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002EBA20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002EBE80);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002EC480);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002ECA90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002ECBA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002ECCB0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002ED120);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002ED2D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002ED590);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002ED690);

void func_002ED890(u8* object, void* context)
{
    if (object[0xCE1] != 0) {
        if (object[0xCEE] == 0x36) {
            func_002EDC10(object, context);
        }
    }
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002ED8D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002ED920);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002ED980);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002EDA10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002EDA60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002EDC10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002EDED0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002EE270);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002EE440);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002EED90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002EEE60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002EF650);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002EF720);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002EFC70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002EFF40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002EFF70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F0040);

extern "C" void func_002F0A00(void* object)
{
    u8* receiver = static_cast<u8*>(object);
    func_003AF250(receiver + 0x290);
    receiver[0x391] = 0;
}

void func_002F0A30(void* receiver)
{
    N57Owner500* object = (N57Owner500*)receiver;
    func_002B3270(receiver);
    object->unk500 = func_4A0B70(object->unk50, D_3E42F8);
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F0A70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F0C60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F0D30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F1520);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F15F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F1E30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F25C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F2CC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F3230);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F3270);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F39D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F3A80);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F3B50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F4380);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F4890);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F48C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F49C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F4BF0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F5050);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F54C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F5740);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F5B60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F5D70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F5F50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F6130);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F61E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F6240);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F62C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_002E6540", func_002F6320);
