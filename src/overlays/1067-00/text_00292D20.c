#include "include_asm.h"
#include "overlays/1067-00/text_00292D20.h"
#include "main/resident_data.h"

typedef struct FieldOwner18
{
    u8 pad[0x18];
    u32 value;
} FieldOwner18;

typedef struct FieldContextDE
{
    u8 pad[0xDE];
    u8 unkde_0_6 : 7;
    u8 unkde_7 : 1;
} FieldContextDE;


INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00292D20", func_00292D20);

s32 func_00292D50(FieldObject1573A0* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00292D20", func_00292D60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00292D20", func_00292E00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00292D20", func_00292EE0);

void func_00293350(FieldOwner18* object, u32 value)
{
    object->value = value;
    ((FieldContextDE*)D_001B6430->context)->unkde_7 = 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00292D20", func_00293380);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00292D20", func_00293490);
