#include "include_asm.h"
#include "main/resident_data.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/1067-00/text_002541F0.h"

/** Partial resident context with a flag byte at offset 0xDF. */
typedef struct FieldContextDF
{
    u8 unk00[0xDF];
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 rest : 6;
} FieldContextDF;


s32 func_002541F0(FieldObject1537C0* object)
{
    return 3;
}

void func_00254200(void* object)
{
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002541F0", func_00254230);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002541F0", func_00254760);

s32 func_00254BD0(void)
{
    return ((FieldContextDF*)D_001B6430->context)->bit1 ? 0 : 8;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002541F0", func_00254C00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002541F0", func_00255270);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002541F0", func_00255350);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002541F0", func_002554C0);
