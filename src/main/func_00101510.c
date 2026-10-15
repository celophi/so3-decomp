#include "include_asm.h"

/** Clear sixteen words at receiver offsets 0x40 through 0x7C and return the receiver. */
void* func_00101510(void* object)
{
    int count = 0;
    char* cursor = (char*)object;
    do
    {
        *(unsigned int*)(cursor + 0x40) = 0;
        *(unsigned int*)(cursor + 0x44) = 0;
        count += 8;
        *(unsigned int*)(cursor + 0x48) = 0;
        *(unsigned int*)(cursor + 0x4C) = 0;
        *(unsigned int*)(cursor + 0x50) = 0;
        *(unsigned int*)(cursor + 0x54) = 0;
        *(unsigned int*)(cursor + 0x58) = 0;
        *(unsigned int*)(cursor + 0x5C) = 0;
        cursor += 0x20;
    } while (count < 16);
    return object;
}
