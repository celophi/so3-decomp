#include "include_asm.h"
#include "overlays/3253-00/text_00264D30.h"

extern "C" u8 D_15A5B0[];
extern "C" void func_00269FB0(void* object);
extern "C" void func_4D9140(void* object);
extern "C" u8 D_157590[];

struct N59Receiver78_00264D30
{
    u8 pad00[0x10];
    void* vtable;
    u8 pad14[0x64];
    u32 unk78;
};

struct WrapperPointer1FC
{
    u8 pad00[0x1FC];
    void* field1FC;
};

struct BattleValueField67680
{
    u8 pad00[0x0C];
    u8 active;
    u8 pad0D[0x07];
    u32 value14;
};

struct BattleResetFields69020
{
    u8 pad00[0x40];
    u32 value40;
    u32 pad44;
    s16 value48;
    s16 pad4A;
    s16 value4C;
    s16 value4E;
    s16 value50;
};

struct BattleOptionalField67970
{
    u8 pad00[0x618];
    u32 present;
};

struct BattleByteFlagState210
{
    u8 unk00[0x210];
    u8 unk210;
    u8 unk211[0x38C];
    u8 unk59d_0_2 : 3;
    u8 unk59d_3 : 1;
    u8 unk59d_4_7 : 4;
};

extern "C" void func_0026C550(void* object);
extern "C" void func_44CC40(void);
extern "C" void func_4EAB40(void* object);
extern "C" void func_4EABF0(void* object);


INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00264D30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00265530);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00265670);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002662E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00266640);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002666F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00266EE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00267050);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002670C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00267460);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00267510);

s32 func_00267670(void* object)
{
    return 3;
}

void func_00267680(void* object, u32 value)
{
    BattleValueField67680* state = (BattleValueField67680*)object;
    state->value14 = value;
    state->active = 1;
}

s32 func_00267690(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002676A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00267760);

s32 func_002677A0(void* object)
{
    return 5;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002677B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00267840);

s32 func_00267890(void* object)
{
    return 7;
}

s32 func_002678A0(void* object)
{
    return 0;
}

void func_002678B0(void* object, u8 value)
{
    BattleByteFlagState210* receiver = (BattleByteFlagState210*)object;
    receiver->unk210 = value;
    receiver->unk59d_3 = 1;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002678D0);

void* func_00267920(void* object)
{
    return (u8*)object + 0x90;
}

void* func_00267930(void* object)
{
    return (u8*)object + 0x1D0;
}

void* func_00267940(void* object)
{
    return (u8*)object + 0x1E0;
}

void* func_00267950(void* object)
{
    return (u8*)object + 0x1F0;
}

s32 func_00267960(void* object)
{
    return 0;
}

void* func_00267970(void* object)
{
    BattleOptionalField67970* state = (BattleOptionalField67970*)object;
    if (state->present != 0)
    {
        return (u8*)object + 0x620;
    }

    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00267990);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00267A20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00267A60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00267AD0);

s32 func_00267B20(void* object)
{
    return 6;
}

void func_00267B30(void* object)
{
    func_44CC40();
    func_4EAB40(object);
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00267B60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00267BD0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00267C10);

void func_00267C70(void* object)
{
}

void func_00267C80(void* object)
{
    u8* bytes = (u8*)object;
    bytes[0x60] = bytes[0xA8];
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00267C90);

void func_00267D30(void* object)
{
}

void func_00267D40(void* object)
{
}

void func_00267D50(void* object)
{
}

float func_00267D60(void* object)
{
    return 0.0f;
}

s32 func_00267D70(void* object)
{
    return 4;
}

void func_00267D80(void* object)
{
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00267D90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00267EF0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00268060);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00268180);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002682F0);

s32 func_00268380(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00268390);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002684D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00268530);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00268560);

s32 func_002685D0(void* object)
{
    return 0;
}

s32 func_002685E0(void* object)
{
    return 0;
}

s32 func_002685F0(void* object)
{
    return 0;
}

s32 func_00268600(void* object)
{
    return 0;
}

s32 func_00268610(const void* object)
{
    const u8* bytes = (const u8*)object;
    return *(const u32*)(bytes + 0x704) != 0;
}

void* func_00268620(void* object)
{
    return (u8*)object + 0x79C;
}

u8 func_00268630(const void* object)
{
    return ((const u8*)object)[0x794];
}

s32 func_00268640(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00268650);

void* func_002686C0(void* object, void* value)
{
    return value;
}

void* func_002686D0(void* object, void* value)
{
    return value;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002686E0);

void func_00268770(void* object)
{
    ((u8*)object)[0x60] = 6;
}

void func_00268780(void* object)
{
    ((u8*)object)[0x60] = 10;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00268790);

void func_00268820(void* object)
{
    ((u8*)object)[0x60] = 9;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00268830);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00268860);

void func_00268940(void* object)
{
    u8* bytes = (u8*)object;
    bytes[0x60] = bytes[0x125];
}

s32 func_00268950(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00268960);

void func_002689F0(void* object)
{
    ((u8*)object)[0x60] = 6;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00268A00);

s32 func_00268A90(void* object)
{
    return 12;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00268AA0);

s32 func_00268B30(void* object)
{
    return 5;
}

void func_00268B40(void* object)
{
}

s32 func_00268B50(void* object)
{
    return 1;
}

s32 func_00268B60(void* object)
{
    return 1;
}

s32 func_00268B70(void* object)
{
    return 5;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00268B80);

void func_00268C10(void* object)
{
    ((u8*)object)[0x60] = 9;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00268C20);

void func_00268CB0(void* object)
{
    ((u8*)object)[0x60] = 6;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00268CC0);

void func_00268D50(void* object)
{
    ((u8*)object)[0x60] = 9;
}

void func_00268D60(void* object)
{
    ((u8*)object)[0x60] = 7;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00268D70);

void func_00269020(void* object)
{
    BattleResetFields69020* state = (BattleResetFields69020*)object;
    state->value48 = 0;
    state->value4C = -1;
    state->value40 = 0;
    state->value4E = -1;
    state->value50 = -1;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269040);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269180);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269190);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002691A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002691B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002691C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002691D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002691E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002691F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269200);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269210);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269220);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269230);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269240);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269250);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269260);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269270);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269280);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269290);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002692A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002692B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002692C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002692D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002692E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002692F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269300);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269310);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269320);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269330);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269340);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269350);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269360);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269370);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269380);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269390);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002693A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002693B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002693C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002693D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002693E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002693F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002694D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269510);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269570);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269650);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002696F0);

void func_00269D50(void* object)
{
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269D60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269E80);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00269FB0);

void* func_0026A0A0(void* object)
{
    ((WrapperPointer1FC*)object)->field1FC = D_15A5B0;
    func_00269FB0(object);
    return object;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026A0E0);

void func_0026A3F0(void* object)
{
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026A400);

void func_0026A8F0(void* object)
{
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026A900);

void func_0026A970(void* object)
{
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026A980);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026ADE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026AE50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026AFC0);

s32 func_0026B020(const void* object, s32 index)
{
    const u8* bytes = (const u8*)object;
    return bytes[index + 0xA4] == 4;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026B040);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026B2B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026B2E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026B5B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026B5E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026B6C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026B710);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026B800);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026B900);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026B950);

void* func_0026B990(void* receiver)
{
    N59Receiver78_00264D30* object = (N59Receiver78_00264D30*)receiver;
    func_4D9140(receiver);
    object->vtable = D_157590;
    object->unk78 = 0;
    return receiver;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026B9D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026C470);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026C550);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026CC10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026CC60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026CD30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026CD90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026CE90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026D050);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026D1D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026D350);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026D7A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026D900);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026DB30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026DB70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026DCC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026DF00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026E080);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026E390);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026E550);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026E580);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026F0C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026F200);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026F650);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026F750);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026F850);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026F920);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026FA50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026FC50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026FDC0);

s32 func_0026FEB0(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026FEC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_0026FF40);

void func_0026FFF0(void* object)
{
    func_0026C550(object);
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00270010);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00270090);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002700E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00270530);

void func_00270580(void* receiver)
{
    u8* object = (u8*)receiver;
    *(u8*)(object + 0x64) = 1;
    *(volatile u32*)0x10009020 = 0;
    *(volatile u32*)0x10009030 = *(u32*)(object + 0x110);
    *(volatile u32*)0x1000E010 = 2;
    *(volatile u32*)0x10009000 = 0x105;
}

void func_002705C0(void* object)
{
    func_4EABF0(object);
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002705E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00270610);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00271010);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002712B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00271560);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00271A90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00271B50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00271CE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00271CF0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00271D90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00271E40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00271EC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002721E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00272270);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00272450);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00272650);

void func_00272980(void* object)
{
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00272990);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002729E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00272AF0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00273130);

void func_00273A70(void* object)
{
}

void func_00273A80(void* object)
{
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00273A90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00273B90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00273BE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00273C80);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00273F10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00274070);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002740B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002741C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002746C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_002747B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00274A70);

void func_00274AC0(void* object)
{
    func_4EABF0(object);
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00274AE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00264D30", func_00274B10);
