#include "include_asm.h"
#include "overlays/1067-00/text_002D8410.h"


/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 4.
 */
s32 func_002D8410(FieldClass150070* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D8410", func_002D8420);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D8410", func_002D84F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D8410", func_002D85E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D8410", func_002D9730);

void func_002D98A0(FieldClass150070* object)
{
    func_002D9730(object);
    func_004D65C0(object);
    delete object;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D8410", func_002D98F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D8410", func_002D9990);

void func_002D9F80(FieldState2D9F80* object)
{
    object->unk70_2 = 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D8410", func_002D9FA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D8410", func_002DA0C0);
