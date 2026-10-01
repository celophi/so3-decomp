#include "include_asm.h"
#include "boot/resident_data.h"
#include "boot/resident_0010A0E0.h"
#include "overlays/0002-01/text_004CD3A0.h"
#include "overlays/1067-00/field_runtime.h"
#include "overlays/1067-00/text_00212560.h"
#include "overlays/1067-00/text_0021DB80.h"


INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021DB80", func_0021DB80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021DB80", func_0021DBF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021DB80", func_0021DC60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021DB80", func_0021DD20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021DB80", func_0021DDD0);

typedef union FieldScriptStackWord
{
    u32 word;
    float number;
} FieldScriptStackWord;

typedef struct FieldScriptWord18
{
    u8 unk00[0x14];
    float unk14;
    u32 unk18;
    s32 depth;
    FieldScriptStackWord stack[256];
    u32 unk420;
    u32 unk424;
    u8 unk428[0x120];
    const u32* current;
    u8 unk54c[0x51];
    u8 unk59d_0 : 1;
    u8 unk59d_rest : 7;
} FieldScriptWord18;

extern void* func_13A678(void* destination, s32 value, u32 size);

s32 func_0021DE20(FieldScriptObject151D40* object, u32 count)
{
    FieldScriptWord18* state = (FieldScriptWord18*)object;
    state->unk18 = *state->current;
    return 0;
}

s32 func_0021DE40(FieldScriptObject151D40* object, u32 count)
{
    FieldScriptWord18* state = (FieldScriptWord18*)object;
    if (state->unk424 != 0) {
        state->unk18 = *state->current;
        return 0;
    }
    return 1;
}

s32 func_0021DE70(FieldScriptObject151D40* object, u32 count)
{
    FieldScriptWord18* state = (FieldScriptWord18*)object;
    FieldScriptStackWord* top = &state->stack[256];
    state->unk14 = (top - state->depth)->number;
    state->depth--;
    state->unk420 = state->stack[256 - state->depth].word;
    state->depth--;
    state->unk18 = state->stack[256 - state->depth].word;
    state->depth--;
    return 0;
}

s32 func_0021DEF0(FieldScriptObject151D40* object, u32 count)
{
    FieldScriptWord18* state = (FieldScriptWord18*)object;
    state->unk14 = (float)*state->current;
    return 1;
}

s32 func_0021DF30(FieldScriptObject151D40* object, u32 count)
{
    FieldScriptWord18* state = (FieldScriptWord18*)object;
    state->unk59d_0 = 1;
    state->unk14 = 1.0f;
    return 0;
}

s32 func_0021DF60(FieldScriptObject151D40* object, u32 count)
{
    FieldRuntimeValues* values = func_101440(func_101290(func_10D8E0()), 4);
    func_13A678(values->unk184, 0, sizeof(values->unk184));
    return 1;
}

s32 func_0021DFB0(FieldScriptObject151D40* object, u32 count)
{
    FieldScriptWord18* state = (FieldScriptWord18*)object;
    const u32* operand = state->current++;
    func_00217780(object, *operand + 0x5000, *state->current);
    return 1;
}

s32 func_0021DFF0(FieldScriptObject151D40* object, u32 count)
{
    FieldScriptWord18* state = (FieldScriptWord18*)object;
    u32 command = *state->current;
    u32 value = func_00217920(object, (command & 0xFFFF) + 0x5000);
    if (command & 0x40000)
    {
        value = (u8)!value;
    }
    switch (command & 0x30000)
    {
    case 0:
        state->unk424 = value;
        break;
    case 0x10000:
        state->unk424 &= value;
        break;
    case 0x20000:
        state->unk424 |= value;
        break;
    }
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021DB80", func_0021E0B0);

s32 func_0021E160(FieldScriptObject151D40* object, u32 count)
{
    FieldScriptWord18* state = (FieldScriptWord18*)object;
    const u32* operand = state->current++;
    u32 mask = *operand;
    u32 enabled = (*state->current & 1) != 0;
    if (enabled) {
        D_001B6430->context->unkd0 |= mask;
    } else {
        D_001B6430->context->unkd0 &= ~mask;
    }
    return 1;
}

s32 func_0021E1C0(FieldScriptObject151D40* object, u32 count)
{
    FieldScriptWord18* state = (FieldScriptWord18*)object;
    D_001B6430->context->unkb0 = *state->current;
    return 1;
}

s32 func_0021E1E0(FieldScriptObject151D40* object, u32 count)
{
    FieldScriptWord18* state = (FieldScriptWord18*)object;
    D_001B6430->context->unka8 = *state->current;
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021DB80", func_0021E200);

s32 func_0021E310(FieldScriptObject151D40* object, u32 count)
{
    FieldScriptWord18* state = (FieldScriptWord18*)object;
    D_001B6430->context->unkaa = *state->current;
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021DB80", func_0021E330);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021DB80", func_0021E780);

s32 func_0021E840(void* object)
{
    return 2;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021DB80", func_0021E850);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021DB80", func_0021EB00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021DB80", func_0021ED20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021DB80", func_0021F180);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021DB80", func_0021F1C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021DB80", func_0021F2D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021DB80", func_0021F470);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021DB80", func_0021F530);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021DB80", func_0021F6D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021DB80", func_0021F760);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021DB80", func_0021F7D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021DB80", func_0021F860);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021DB80", func_0021F900);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021DB80", func_0021F960);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021DB80", func_0021F9B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021DB80", func_0021FA70);

s32 func_0021FB30(FieldObject1522C0* object)
{
    return 3;
}

void func_0021FB40(FieldObject1522C0* object)
{
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021DB80", func_0021FB70);
