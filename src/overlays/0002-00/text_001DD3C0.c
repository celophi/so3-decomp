#include "include_asm.h"
#include "overlays/0002-00/text_001DD3C0.h"

typedef struct FieldU16At06A
{
    u8 pad[0x6A];
    u16 value;
} FieldU16At06A;

typedef struct FieldU16At06C
{
    u8 pad[0x6C];
    u16 value;
} FieldU16At06C;

typedef struct FieldU8At018
{
    u8 pad[0x18];
    u8 value;
} FieldU8At018;

typedef struct FieldU8At060
{
    u8 pad[0x60];
    u8 value;
} FieldU8At060;

typedef struct FieldU8At79C
{
    u8 pad[0x79C];
    u8 value;
} FieldU8At79C;

typedef struct FieldU8At570
{
    u8 pad[0x570];
    u8 value;
} FieldU8At570;

typedef struct FieldU8At090
{
    u8 pad[0x90];
    u8 value;
} FieldU8At090;

typedef struct FieldU8At1D0
{
    u8 pad[0x1D0];
    u8 value;
} FieldU8At1D0;

typedef struct FieldU8At1E0
{
    u8 pad[0x1E0];
    u8 value;
} FieldU8At1E0;

typedef struct FieldU8At1F0
{
    u8 pad[0x1F0];
    u8 value;
} FieldU8At1F0;

typedef struct FieldU32At704
{
    u8 pad[0x704];
    u32 value;
} FieldU32At704;

typedef struct FieldU8At794
{
    u8 pad[0x794];
    u8 value;
} FieldU8At794;

typedef struct FieldS16AtDCE
{
    u8 pad[0xDCE];
    s16 value;
} FieldS16AtDCE;

typedef struct FieldU32AtDD0
{
    u8 pad[0xDD0];
    u32 value;
} FieldU32AtDD0;

typedef struct Record001E94E0
{
    u8 unk00[0x210];
    u8 value;
    u8 unk211[0x38C];
    u8 unk59d:3;
    u8 active:1;
    u8 unk59dhi:4;
} Record001E94E0;

extern u8 D_170D50[];
extern u8 D_50CD30[];
extern void func_4A4550(void* object);
extern void func_4A4510(void* object);
extern void func_4CE4C0(void* destination, const float* source);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DD3C0);

s32 func_001DD400(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DD410);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DD440);

void func_001DD4C0(void* object)
{
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DD4D0);

void func_001DD620(u8* object, float first, float second, float third)
{
    object[0x50] = 1;
    *(float*)(object + 0x20) = first;
    *(float*)(object + 0x24) = second;
    *(float*)(object + 0x28) = third;
    *(float*)(object + 0x2C) = 1.0f;
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DD640);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DDAA0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DDAC0);

void func_001DDED0(u8* object, float first, float second, float third)
{
    object[0x50] = 1;
    *(float*)(object + 0x40) = first;
    *(float*)(object + 0x44) = second;
    *(float*)(object + 0x48) = third;
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DDEF0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DFB70);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DFBD0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DFCE0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DFD50);

void func_001DFE30(void* object, u16 value)
{
    ((FieldU16At06A*)object)->value = value;
}

void func_001DFE40(void* object, u16 value)
{
    ((FieldU16At06C*)object)->value = value;
}

void* func_001DFE50(u32* object)
{
    object[3] = 0;
    object[2] = 0;
    object[1] = 0;
    object[0] = 0;
    return object;
}

void* func_001DFE70(void** object)
{
    *object = D_170D50;
    return object;
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DFE90);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DFF00);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DFFA0);

void func_001E0250(void* object, u8 value)
{
    ((FieldU8At018*)object)->value = value;
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E0260);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E0430);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E0490);

void func_001E04E0(void* object)
{
}

void func_001E04F0(void* object)
{
}

void func_001E0500(u8* object, const unsigned __int128* value)
{
    *(unsigned __int128*)(object + 0x20) = *value;
}

void func_001E0510(u8* object, const unsigned __int128* value)
{
    *(unsigned __int128*)(object + 0x20) = *value;
}

void func_001E0520(u8* object, float first, float second, float third)
{
    *(float*)(object + 0x20) = first;
    *(float*)(object + 0x24) = second;
    *(float*)(object + 0x28) = third;
    *(float*)(object + 0x2C) = 1.0f;
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E0540);

s32 func_001E05D0(void* object)
{
    return 3;
}

void func_001E05E0(void* object)
{
}

void func_001E05F0(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x20) = *value;
}

void func_001E0610(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x20) = *value;
}

void func_001E0630(u8* object, float first, float second, float third, float fourth)
{
    object[0x50] = 1;
    *(float*)(object + 0x30) = first;
    *(float*)(object + 0x34) = second;
    *(float*)(object + 0x38) = third;
    *(float*)(object + 0x3C) = fourth;
}

void func_001E0650(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x30) = *value;
}

void func_001E0670(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x30) = *value;
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E0690);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E06C0);

void func_001E06F0(u8* object, float first, float second, float third)
{
    float vector[4];
    object[0x50] = 1;
    vector[0] = first;
    vector[1] = second;
    vector[2] = third;
    vector[3] = 1.0f;
    func_4CE4C0(object + 0x30, vector);
}

void func_001E0730(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x40) = *value;
}

void func_001E0750(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x40) = *value;
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E0770);

void func_001E0860(void* object)
{
    ((FieldU8At060*)object)->value = 0;
}

void func_001E0870(void* object)
{
}

s32 func_001E0880(void* object)
{
    return 0;
}

s32 func_001E0890(void* object, float value)
{
    return value < 0.0f;
}

void* func_001E08B0(void* object)
{
    return D_50CD30;
}

void func_001E08C0(void* object)
{
}

s32 func_001E08D0(void* object)
{
    return 0;
}

void func_001E08E0(void* object)
{
}

void func_001E08F0(void* object)
{
}

s32 func_001E0900(void* object)
{
    return 2;
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E0910);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E0970);

u32 func_001E0AD0(void* object)
{
    return ((FieldU32AtDD0*)object)->value;
}

s16 func_001E0AE0(void* object)
{
    return ((FieldS16AtDCE*)object)->value;
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E0AF0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E0C30);

void func_001E0DE0(BootState1E1A40* object, u8 mode)
{
    if (mode == 1 || mode == 2)
    {
        object->unkD34 = mode;
        func_001E1A40(object, 0);
    }
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E0E20);

/**
 * @brief Return a mode's stored byte, or zero for an unsupported mode.
 * @param object State holding the mode values.
 * @param mode Mode 0 or 1 to query.
 * @return The stored byte, or zero when the mode is unsupported.
 */
static inline u8 state_mode_value(BootState1E1A40* object, u16 mode)
{
    if (mode != 0 && mode != 1)
    {
        return 0;
    }
    return object->unkD37[mode];
}

u8 func_001E1410(BootState1E1A40* object, u16 mode, u16 kind)
{
    u8 value = 0;
    if (mode != 0 && mode != 1)
    {
        return 0;
    }
    if (kind == 1)
    {
        if (mode == 0)
        {
            if (!object->unk29)
            {
                value = 0;
            }
            else
            {
                value = object->unk2B;
            }
        }
        else if (mode == 1)
        {
            if (!object->unk2A)
            {
                value = 0;
            }
            else
            {
                value = object->unk2C;
            }
        }
    }
    else
    {
        value = state_mode_value(object, mode);
    }
    if (object->unk28)
    {
        func_001E1A40(object, 0);
    }
    return value;
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E1500);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E17C0);

void func_001E1A40(BootState1E1A40* object, s16 mode)
{
    s32 selected = mode;
    object->unk18 = mode;
    object->unk1A = -1;
    object->unk1E = 0;
    object->unk1C = 0;
    object->unk2D = 0;
    if (selected == 0)
    {
        object->unk29 = 0;
        object->unk2B = 0;
        object->unk28 = 0;
        object->unk1E = 0;
        object->unkD37[0] = 0;
        object->unkD35[0] = 0;
    }
    if (selected == 1)
    {
        object->unk2A = 0;
        object->unk2C = 0;
        object->unkD37[1] = 0;
        object->unkD35[1] = 0;
    }
    if (selected == 0 || selected == 1)
    {
        object->unkDFC[selected] = -1;
        object->unkE04[selected] = -1;
    }
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E1AD0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E1CD0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E1D40);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E1DD0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E1F50);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E1FE0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E3F80);

s32 func_001E3FE0(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E3FF0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E4610);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E4760);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E4B50);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E4CE0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E5090);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E5250);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E5510);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E63B0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E6C60);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E8D80);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E8DD0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E9070);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E92D0);

float func_001E9380(void* object)
{
    return 0.0f;
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E9390);

s32 func_001E9400(void* object)
{
    return 0;
}

s32 func_001E9410(void* object)
{
    return 0;
}

s32 func_001E9420(void* object, s32 value)
{
    return value;
}

s32 func_001E9430(void* object, s32 value)
{
    return value;
}

s32 func_001E9440(void* object)
{
    return 0;
}

s32 func_001E9450(void* object)
{
    return 0;
}

s32 func_001E9460(void* object)
{
    return ((FieldU32At704*)object)->value != 0;
}

u8* func_001E9470(void* object)
{
    return &((FieldU8At79C*)object)->value;
}

u8 func_001E9480(void* object)
{
    return ((FieldU8At794*)object)->value;
}

s32 func_001E9490(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E94A0);

u8* func_001E94D0(void* object)
{
    return &((FieldU8At570*)object)->value;
}

void func_001E94E0(Record001E94E0* object, u8 value)
{
    object->value = value;
    object->active = 1;
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E9500);

u8* func_001E9550(void* object)
{
    return &((FieldU8At090*)object)->value;
}

u8* func_001E9560(void* object)
{
    return &((FieldU8At1D0*)object)->value;
}

u8* func_001E9570(void* object)
{
    return &((FieldU8At1E0*)object)->value;
}

u8* func_001E9580(void* object)
{
    return &((FieldU8At1F0*)object)->value;
}

void func_001E9590(u8* object)
{
    func_4A4550(object - 0x640);
}

void func_001E95A0(u8* object)
{
    func_4A4510(object - 0x640);
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E95B0);

s32 func_001E9640(void* object)
{
    return 0;
}

void func_001E9650(u32* object)
{
    object[8] = 0;
    object[9] = 0;
    object[10] = 0;
    object[11] = 0;
    object[12] = 0;
    object[13] = 0;
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E9670);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E97F0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E9860);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EA350);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EA480);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EA6A0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EA920);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EA9B0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EAA40);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EACC0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EACD0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EAE80);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EB0E0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EB210);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EB350);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EBCF0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EBEA0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EBF80);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EC010);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EC2E0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EC360);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EC3C0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EC430);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EC490);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EC630);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EC910);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EC990);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EC9F0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001ECA60);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001ECAC0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001ECC60);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001ECF30);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001ECFA0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001ED000);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001ED060);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001ED200);
