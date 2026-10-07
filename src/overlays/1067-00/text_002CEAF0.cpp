#include "include_asm.h"
#include "overlays/1067-00/text_00202240.h"
#include "overlays/1067-00/text_002CEAF0.h"
#include "overlays/lib/text_004BD360.h"

/** Partial object with byte values at 0x18 and 0x88, and flags at 0x1A. */
typedef struct FieldD1440Object
{
    u8 pad00[0x18];
    u8 value18;
    u8 pad19;
    u16 flags;
    u8 pad1c[0x6C];
    u8 value88;
} FieldD1440Object;

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CEAF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CEBE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CECA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CED20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CEDA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CEE20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CEEA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CEF20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CEFA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CF010);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CF090);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CF110);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CF190);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CF200);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CF280);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CF300);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CF380);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CF400);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CF480);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CF500);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CF580);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CF600);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CF680);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CF700);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CF780);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CF800);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CF880);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CF900);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CF980);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CFA00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CFA80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CFB00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CFB80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CFC00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CFC80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CFD00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CFD80);

/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 3.
 */
s32 func_002CFE00(FieldClass150070* object)
{
    return 3;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CFE10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CFE40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CFF60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D08B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D0D30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D1100);

s32 func_002D1440(FieldD1440Object* object, u8 value, u32 flags)
{
    object->value18 = value;
    if (flags != 0)
    {
        object->flags = flags;
    }
    else
    {
        object->flags = 0;
    }
    if (((u16)flags) & 8)
    {
        object->value88 = 0;
    }
    else
    {
        object->value88 = 1;
    }
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D1480);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D14B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D1550);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D1640);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D18E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D1980);

/**
 * @brief Run the base release handler, detach the object, then delete it.
 * @param object Object to release.
 */
extern "C" void func_002D19E0(FieldClass150F90* object)
{
    object->FieldClass150F90::func_00204E40();
    func_004D65C0(object);
    object->func_001DD7B0();
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D1A20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D1A40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D1C10);

/** Partial owner of a Lib container with a state bit at offset 0x55. */
struct FieldOwner2D1D70
{
    u8 unk00[0x4C];
    LibObject178660* unk4c;
    u32 unk50;
    u8 unk54;
    u8 unk55_0_2 : 3;
    u8 unk55_3 : 1;
    u8 unk55_4_7 : 4;
};

/**
 * @brief Release the owned Lib container and clear the state bit.
 * @param owner Owner of the container.
 */
extern "C" void func_002D1D70(FieldOwner2D1D70* owner)
{
    owner->unk50 = 0;
    if (owner->unk4c != 0)
    {
        owner->unk4c->func_003EF740();
        owner->unk4c = 0;
    }
    owner->unk55_3 = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D1DD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D1DE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D1FD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D2020);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D2050);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D2170);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D2210);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D22B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D23B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D2420);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D3920);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D3990);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D3A50);

/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 4.
 */
s32 func_002D3BB0(FieldClass150070* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D3BC0);
