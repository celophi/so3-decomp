#include "include_asm.h"
#include "overlays/boot/text_001DD3C0.h"

extern "C" {
void func_4CE4C0(void* destination, const float* source);

void func_001E0690(u8* object, const float* input)
{
    object[0x50] = 1;
    func_4CE4C0(object + 0x30, input);
}

void func_001E06C0(u8* object, const float* input)
{
    object[0x50] = 1;
    func_4CE4C0(object + 0x30, input);
}
}
