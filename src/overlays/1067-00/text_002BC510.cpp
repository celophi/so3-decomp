#include "include_asm.h"
#include "main/resident_data.h"
#include "main/resident_0010A0E0.h"
#include "overlays/1067-00/text_002BC510.h"
#include "overlays/1067-00/text_002AE9E0.h"

struct FieldGlobal643C
{
    u8 unk00[4];
    s32 unk04;
};

struct FieldGlobal6650
{
    u8 unk00[0x3C6C];
    s16 unk3C6C;
    s16 unk3C6E;
};

struct FieldState2BDF70
{
    u8 unk00[0x1C];
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    u8 unk2C[0x18];
    u16 unk44;
    u8 unk46[2];
    s32 unk48;
};

extern "C" FieldGlobal643C* D_001B643C;

extern "C" void func_4D00B0(void* object);
extern "C" void func_44B210(void* object);
extern "C" void* D_001B6650;
extern "C" void func_4DCEA0(void* state, bool enabled, bool other);


FieldClass159A80::~FieldClass159A80()
{
}

/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 9.
 */
s32 func_002BC5A0(FieldClass150070* object)
{
    return 9;
}

void func_002BC5B0(FieldClass150070* object)
{
    func_0011ED90(D_001B65F4, object);
}

/**
 * @brief Reset the attached object's mode, then delete this object.
 * @param object Object to release.
 */
extern "C" void func_002BC5D0(FieldClass159A80* object)
{
    func_002BC650(object->unk14, object->unk18);
    object->func_001DD7B0();
}

bool func_002BC610(void* object, bool enabled)
{
    if (D_001B6650 == 0)
    {
        return false;
    }
    func_4DCEA0(D_001B6650, enabled, false);
    return true;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BC510", func_002BC650);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BC510", func_002BC790);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BC510", func_002BC8B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BC510", func_002BCE60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BC510", func_002BCFC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BC510", func_002BD050);

void func_002BD080(FieldState2BC510* object, s32 first, s32 second, s32 third, s32 fourth)
{
    object->unk4C = 1;
    object->unk50 = first;
    object->unk54 = second;
    object->unk58 = third;
    object->unk5C = fourth;
}

void func_002BD0A0(void* object)
{
    func_4D00B0(object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BC510", func_002BD0C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BC510", func_002BD100);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BC510", func_002BD190);

void func_002BD1F0(FieldState2BD1F0* object)
{
    object->unk124 = 1;
    func_44B210(object);
    func_0011ED90(D_001B65F4, object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BC510", func_002BD230);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BC510", func_002BD2D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BC510", func_002BD370);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BC510", func_002BDD70);

void func_002BDF60(FieldState2BC510* object, float first, float second)
{
    object->unk38 = first;
    object->unk3C = second;
}

bool func_002BDF70(FieldState2BDF70* object, u16 value)
{
    if (value == 0)
    {
        return false;
    }

    object->unk44 = value;
    object->unk48 = D_001B643C->unk04;
    FieldGlobal6650* state = static_cast<FieldGlobal6650*>(D_001B6650);
    object->unk1C = 0x800 - state->unk3C6C / 2;
    object->unk20 = 0x800 - state->unk3C6E / 2;
    object->unk24 = 0x800 + state->unk3C6C / 2;
    object->unk28 = 0x800 + state->unk3C6E / 2;
    return true;
}

/** Partial FieldClass159A70 with vtable D_159B50 in main data. */
class FieldClass159B50 : public FieldClass159A70
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass159B50();
};

FieldClass159B50::~FieldClass159B50()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BC510", func_002BE080);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002BC510", func_002BE090);
