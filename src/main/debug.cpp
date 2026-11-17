#include "include_asm.h"
#include "main/debug.h"
#include "main/packet.h"

/**
 * @brief Register a named value with the debug display; this build's version does nothing and returns -1.
 * @param name Name shown for the value, such as "StorageQueue Status".
 * @param value Value to show.
 * @param kind Unknown; both callers pass one.
 * @return -1.
 */
s32 resident_debug_register_value(const char* name, void* value, s32 kind)
{
    return -1;
}

void resident_debug_initialize(void)
{
}

/**
 * @brief Ignore a notification; the retail build's debug listener does nothing.
 * @param data Ignored.
 */
void ResidentDebugListener::notify(void* data)
{
}

/**
 * @brief Hook Lib calls after it installs a display, and boot before it restarts Lib; empty in the retail build.
 * @param display Display being installed.
 */
void resident_display_set_hook(void* display)
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
