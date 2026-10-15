#include "include_asm.h"
#include "overlays/lib/text_0046AE20.h"

extern "C" {
void func_0047A540(void* object, void* state, void* row);

void func_0047A040(void* object, u8* state, void* row)
{
    state[0x130] = 0;
    state[0x132] = 0;
    state[0x131] = 0;
    state[0x133] = 0;
    func_0047A540(object, state, row);
}
}
