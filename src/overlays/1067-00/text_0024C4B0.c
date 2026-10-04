#include "include_asm.h"
#include "overlays/1067-00/text_0024C4B0.h"

/** Partial receiver with status bytes at offsets 0x331-0x334. */
typedef struct FieldStatus331
{
    u8 pad00[0x331];
    u8 state;
    u8 previous;
    u8 value;
    u8 unk334_0 : 1;
    u8 unk334_1_7 : 7;
} FieldStatus331;


INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024C4B0", func_0024C4B0);

void func_0024C540(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024C4B0", func_0020BD00__16FieldClass153570FP16FieldClass154D20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024C4B0", func_0024C6A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024C4B0", func_0024C6E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024C4B0", func_0024CA20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024C4B0", func_0024CB40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024C4B0", func_0024CC10);

s32 func_0024CC30(FieldObject153590* object)
{
    return 8;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024C4B0", func_0024CC40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024C4B0", func_0024CE10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024C4B0", func_0024CE80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024C4B0", func_0024CEF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024C4B0", func_0024CF90);

void func_0024D000(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024C4B0", func_0024D010);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024C4B0", func_0024D0A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024C4B0", func_0024D110);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024C4B0", func_0024D1C0__16FieldClass1535B0FPCc);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024C4B0", func_0024D2A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024C4B0", func_0024D3D0);

void func_0024D440(FieldStatus331* object, u8 value)
{
    object->previous = object->state;
    object->state = 3;
    object->unk334_0 = 0;
    object->value = value;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024C4B0", func_0024D470);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024C4B0", func_0024D610);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024C4B0", func_0024D730);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024C4B0", func_0024D8B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024C4B0", func_0024DA00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024C4B0", func_0024DA50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024C4B0", func_0024DC50);
