#include "include_asm.h"
#include "main/resident_data.h"
#include "overlays/1067-00/text_001DED80_callbacks.h"
#include "overlays/1067-00/text_0027D380.h"

/** Partial listed object with a signed use count at offset 0x4D5. */
struct FieldCountedObject4D5
{
    u8 unk00[0x4D5];
    s8 unk4d5;
};


INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027D380", func_0027D380);

void FieldClass155810::func_slot20()
{
    FieldClass152740::func_slot20();
    func_004D65C0(this);
    func_001DD7B0();
}

void FieldClass155810::func_001DD7B0()
{
    if (unk14 != 0)
    {
        FieldCountedObject4D5* found = reinterpret_cast<FieldCountedObject4D5*>(
            func_001DEE30((FieldFlaggedListObject*)D_001B6430->context->unk04, unk270, 0x10000));
        if (found != 0 && found->unk4d5 > 0)
        {
            found->unk4d5--;
        }
    }
    delete this;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027D380", func_0027D570);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027D380", func_0027D760);

void FieldClass155B40::func_001DF360()
{
    FieldClass154EF0::func_001DF360();
    if (unk20_2)
    {
        FieldVec4A position = unk30;
        position.w = 10000.0f;
        unk18->unkA50 = position;
        func_slot20();
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027D380", func_0027DB20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027D380", func_0027DBD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027D380", func_0027DFF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027D380", func_0027E190);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027D380", func_0027E2E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027D380", func_0027E350);
