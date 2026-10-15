#include "include_asm.h"
#include "overlays/lib/text_0043A920.h"

extern "C" {
void func_00444BF0(void* object, void* state, void* row);

void func_00441C10(void* object, u8* state, void* row)
{
    state[0x130] = 0;
    state[0x132] = 0;
    state[0x131] = 0;
    state[0x133] = 0;
    func_00444BF0(object, state, row);
}
}
