#include "include_asm.h"
#include "main/resident_00121860.h"
#include "main/resident_0011EE70.h"

s32 func_00121860(void* object)
{
    return -1;
}

void func_00121870(void)
{
}

void func_00121880(void* object)
{
}

void func_00121890(void* object)
{
}

/** @brief Free the packet storage unless it is borrowed. */
ResidentPacketBuffer::~ResidentPacketBuffer()
{
    if (!unk14)
    {
        delete unk04;
    }
}
