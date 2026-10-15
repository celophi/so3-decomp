#include "include_asm.h"
#include "main/resident_00101550.h"

typedef struct ResidentHelperObjectAC110
{
    u8 unk00[0xAC];
    u32 unkAC;
    u8 unkB0[0x60];
    u32 unk110;
} ResidentHelperObjectAC110;

s32 func_0010A0B0(void* object, const s32* value)
{
    if (*value > 0)
    {
        ((ResidentHelperObjectAC110*)object)->unk110 = 1;
        ((ResidentHelperObjectAC110*)object)->unkAC = 1;
        return *value;
    }
    return 0;
}
