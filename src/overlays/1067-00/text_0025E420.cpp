#include "include_asm.h"
#include "overlays/1067-00/text_0025E420.h"
#include "overlays/1067-00/text_00257750.h"


INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_0025E420);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_0025E4D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", __ct__16FieldClass153CD0Fv);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_0025E7D0);

struct SmallConditionalInput04
{
    u8 unk00[4];
    float unk04;
};

/**
 * @brief Write the output pair for positive or NaN input.
 * @param object Unused interface argument.
 * @param value Input whose float at offset 4 is tested.
 * @param zero_output Receives zero when the test passes; otherwise unchanged.
 * @param small_output Receives 0.05 when the test passes; otherwise unchanged.
 * @return One for positive or NaN input, otherwise zero.
 */
s32 func_0025E840(void* object, const void* value, float* zero_output, float* small_output)
{
    const struct SmallConditionalInput04* state = (const struct SmallConditionalInput04*)value;
    if (!(state->unk04 <= 0.0f))
    {
        *zero_output = 0.0f;
        *small_output = 0.05f;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_0025E880);

/**
 * @brief Report the receiver's fixed category.
 * @param object Unused receiver.
 * @return Always 16.
 */
s32 func_0025E910(FieldObject153CB0* object)
{
    return 16;
}

/**
 * @brief Report this object's default list kind.
 * @return Always 4.
 */
s32 FieldClass153CD0::get_default_list_kind()
{
    return 4;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_0025E930);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_0025E960);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_0025EAD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_0025EBC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_0025ED00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_0025ED80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_0025EDD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_0025EF40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_0025F030);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_0025F170);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_0025F1F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_0025F240);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_0025F2F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_0025F5A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_0025FAB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_0025FC50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_0025FF00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_00260410);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_002605B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_00260690);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_00260770);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_00260780);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_00260790);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0025E420", func_002607A0);
