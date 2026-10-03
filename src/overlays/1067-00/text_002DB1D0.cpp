#include "include_asm.h"
#include "main/resident_data.h"
#include "main/resident_0010A0E0.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/1067-00/text_002DB1D0.h"


INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DB1D0", func_002DB1D0);

/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 5.
 */
s32 func_002DB270(FieldClass150070* object)
{
    return 5;
}

/**
 * @brief Detach this object and add it to the resident object queue.
 * @param object Object to detach and queue.
 */
void func_002DB280(FieldClass150070* object)
{
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DB1D0", func_002DB2B0);

/**
 * @brief Set bit zero of the byte at offset 0x60.
 * @param object Object with the state byte.
 */
void func_002DBB50(FieldObjectDBB50* object)
{
    object->unk60_0 = 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DB1D0", func_002DBB70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DB1D0", func_002DBC40);
