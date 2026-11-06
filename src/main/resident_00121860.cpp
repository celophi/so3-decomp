#include "include_asm.h"
#include "main/resident_00121860.h"
#include "main/resident_0011EE70.h"

/**
 * @brief Register a named value with the debug display; this build's version does nothing and returns -1.
 * @param name Name shown for the value, such as "StorageQueue Status".
 * @param value Value to show.
 * @param kind Unknown; both callers pass one.
 * @return -1.
 */
s32 func_00121860(const char* name, void* value, s32 kind)
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
