#include "include_asm.h"
#include "main/resident_00101260.h"

/**
 * @brief Get the resident system's resource queue.
 * @param object Resident system.
 * @return Resource queue at offset 0x15A24.
 */
ResidentResourceQueue* func_00101250(void* object)
{
    return (ResidentResourceQueue*)((char*)object + 0x15A24);
}
