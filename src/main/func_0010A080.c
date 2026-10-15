#include "include_asm.h"
#include "main/resident_00101550.h"

typedef struct ResidentHelperObjectB0
{
    u8 unk00[0xB0];
    u32 unkB0;
} ResidentHelperObjectB0;

s32 func_0010A080(void* object, const s32* value)
{
    if (*value > 0)
    {
        ((ResidentHelperObjectB0*)object)->unkB0 = 1;
        return *value;
    }
    return 0;
}
