#include "include_asm.h"
#include "main/resident_data.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/1067-00/text_002DA0D0.h"


INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DA0D0", func_002DA0D0);

/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 9.
 */
s32 func_002DA170(FieldClass150070* object)
{
    return 9;
}

void func_002DA180(FieldClass150070* object)
{
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DA0D0", func_002DA1B0);

FieldQuad4DA0D0 func_002DACE0(FieldQuad4DA0D0* destination, const FieldQuad4DA0D0* source)
{
    *destination = *source;
    return *destination;
}

FieldCopyRecordDestDA0D0* func_002DAD30(FieldCopyRecordDestDA0D0* destination, const FieldCopyRecordSourceDA0D0* source)
{
    destination->unk00 = source->unk00;
    destination->unk04 = source->unk04;
    destination->unk08 = source->unk08;
    destination->unk10 = source->unk10;
    destination->unk20 = source->unk20;
    destination->unk30 = source->unk30;
    destination->unk40 = source->unk40;
    destination->unk50 = source->unk50;
    destination->unk60 = source->unk60;
    destination->unk70 = source->unk70;
    destination->unk74 = source->unk74;
    destination->unk78 = source->unk78;
    destination->unk7c = source->unk7c;
    destination->unk80 = source->unk80;
    destination->unk81 = source->unk81;
    return destination;
}

void func_002DADD0(FieldFlag2DADD0* object)
{
    object->unk2c_0 = 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DA0D0", func_002DADF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DA0D0", func_002DB080);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DA0D0", func_002DB1C0);
