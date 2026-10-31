#include "include_asm.h"
#include "main/resident_data.h"
#include "main/resident_0010A0E0.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/1067-00/text_0020E4B0.h"
#include "overlays/1067-00/text_00200710.h"

/** Partial field context with a word at offset 0x50. */
typedef struct FieldContextE4C0
{
    u8 unk00[0x50];
    u32 value;
} FieldContextE4C0;


float func_0020E4B0(void* object)
{
    return g_frame_ticks;
}

s32 func_0020E4C0(void* object)
{
    return ((FieldContextE4C0*)D_001B6430->context)->value != 0;
}

s32 func_0020E4E0(void* object)
{
    return 1;
}

s32 func_0020E4F0(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", get_character_name__16FieldClass1516A0Fi);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020E560);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", refresh_field_character_state__16FieldClass1516A0Fv);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", has_no_pending_field_work__16FieldClass1516A0Fv);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020E6A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", get_field_request_state__16FieldClass1516A0FSc);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", get_field_request_progress__16FieldClass1516A0FSc);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", clear_field_requests__16FieldClass1516A0FScUi);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", queue_field_request__16FieldClass1516A0FiiiiiUi);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", set_field_object_value__16FieldClass1516A0Fiif);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", resolve_field_object_display_position__16FieldClass1516A0FPfPfiff);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020EF20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020EF90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020F050);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020F110);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020F230);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020F490);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020F520);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020F560);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020F5D0);

/** @brief Detach the object and add it to the resident release queue. @param object Object to release. */
extern "C" void func_0020F6C0(void* object)
{
    lib_object_detach_owner(object);
    resident_enqueue_object(g_resident_release_queues, object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020F6F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", __dt__16FieldClass1516A0Fv);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", __ct__16FieldClass1516A0Fv);

/** @brief Initialize the script registers, stack depth and command flags. */
FieldClass150DC0::FieldClass150DC0()
{
    number = 0.0f;
    stack_depth = 0;
    instruction_index = 0;
    unk420 = 0;
    unk424 = 0;
    unk4c8_0 = 0;
    unk4c8_1 = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020F9D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020F9E0);
