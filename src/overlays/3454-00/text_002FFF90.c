#include "include_asm.h"
#include "overlays/3454-00/text_002FFF90.h"

extern void func_002919A0(void* object);
extern void func_002A1390(void* object);
extern u32 func_473940(u32 value, const void* data);
extern const u8 D_3E3A60[];

typedef struct N57Owner2FECtext_002FFF90
{
    u8 unk00[0x50];
    u32 unk50;
    u8 unk54[0x2F98];
    u32 unk2fec;
} N57Owner2FECtext_002FFF90;

typedef struct ConditionalByteUpdate2FE0text_002FFF90
{
    u8 unk00[0xB88];
    u32 comparison;
    u8 unkB8C[0x2454];
    u8 matchFlag;
    u8 updateFlag;
} ConditionalByteUpdate2FE0text_002FFF90;

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_002FFF90);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00300430);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00300600);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00300AE0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00300D80);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00301900);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00301A20);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_003021A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_003023D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_003024F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00302960);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00302AE0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00302D10);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00302DA0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00302F80);

void func_00302FB0(void* object, u32 value)
{
    ConditionalByteUpdate2FE0text_002FFF90* receiver = object;
    receiver->updateFlag = 1;
    if (value == receiver->comparison)
    {
        receiver->matchFlag = 1;
    }
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00302FD0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00303450);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_003037D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00303A80);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00303C60);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00304390);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00304820);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00304D30);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00304EF0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_003051F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00305380);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_003054E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_003055B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00305680);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00305760);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00305830);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_003059A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00305A30);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00305A80);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00305B40);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00305C10);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00306290);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00306560);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00306920);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00306D60);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00306ED0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00307090);

typedef struct FieldByte2FE8
{
    u8 unk00[0x2FE8];
    u8 value;
} FieldByte2FE8;

void func_00307350(void* receiver)
{
    FieldByte2FE8* object = receiver;
    func_002919A0(receiver);
    object->value = 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00307380);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00307700);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00307890);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00307AE0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00307D30);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00307F60);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00308080);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_003080F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00308170);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00308440);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_003086F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00308820);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_003088D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00308AB0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00308BE0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00308D70);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00309030);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_003090A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00309190);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00309340);

void func_003093C0(void* receiver)
{
    N57Owner2FECtext_002FFF90* object = (N57Owner2FECtext_002FFF90*)receiver;
    func_002A1390(receiver);
    object->unk2fec = func_473940(object->unk50, D_3E3A60);
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00309400);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00309480);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_003095F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00309750);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00309970);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_00309DB0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030A010);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030A570);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030A720);

typedef struct FieldByte570
{
    u8 unk00[0x570];
    u8 value;
} FieldByte570;

void func_0030A850(void* receiver)
{
    FieldByte570* object = receiver;
    func_002919A0(receiver);
    object->value = 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030A880);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030ABD0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030B000);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030B370);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030B4D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030B840);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030BB60);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030BC50);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030BD90);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030BE20);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030C1F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030C2E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030C580);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030C6A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030CAE0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030CC10);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030CE50);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030CFC0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030D1B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030D270);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030D390);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030D5B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030D670);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030D720);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030E3C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030EC50);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030EF00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030F0F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030F800);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030F8C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030FB20);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030FD20);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_002FFF90", func_0030FF30);
