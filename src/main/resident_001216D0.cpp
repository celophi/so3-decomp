#include "include_asm.h"
#include "main/resident_0011EE70.h"

extern "C" {
void func_4CE4C0(void* destination, const float* source);

void func_001216D0(u8* object, const float* input)
{
    object[0x50] = 1;
    func_4CE4C0(object + 0x30, input);
}

void func_00121700(u8* object, const float* input)
{
    object[0x50] = 1;
    func_4CE4C0(object + 0x30, input);
}
}
