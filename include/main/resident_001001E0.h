#ifndef SO3_MAIN_RESIDENT_001001E0_H
#define SO3_MAIN_RESIDENT_001001E0_H

#include "types.h"

#ifdef __cplusplus
/**
 * @brief Allocate memory from the current heap, or from the default allocator when none is set.
 * @param size Number of bytes to allocate.
 * @param unused Second argument passed by callers; the resident implementation ignores it.
 * @return The allocated memory.
 */
void* operator new(u32 size, s32 unused);

/**
 * @brief Allocate array memory from the current heap, or from the default allocator when none is set.
 * @param size Number of bytes to allocate.
 * @param unused Second argument passed by callers; the resident implementation ignores it.
 * @return The allocated memory.
 */
void* operator new[](u32 size, s32 unused);

extern "C" {
#endif

/** Optional heap used by resident operator new and aligned decode buffers. */
extern void* g_allocation_heap;

/** The running program; its constructor registers it, and switching programs calls its run(). */
extern void* g_current_program;

/** Object that receives the IOP's SIF commands 0 to 3, or null; the sound system registers its stream. */
extern void* g_sif_command_receiver;

/** Store a byte in the global at address 0x001B6420. */
void func_00100A40(u8 value);

/**
 * @brief Replace the heap used by operator new and operator new[].
 * @param heap Heap to use, or null for the default allocator.
 * @return The previous heap.
 */
void* resident_exchange_allocation_heap(void* heap);

/**
 * @brief Read the heap used by operator new and operator new[].
 * @return The current heap, or null for the default allocator.
 */
void* resident_get_allocation_heap(void);

struct ResidentSystem;

/**
 * @brief Dispatch the loaded resource buffer through the resident system.
 * @param system Resident system.
 * @param destination Loaded resource buffer.
 * @param type Resource type.
 * @param size Resource payload size.
 */
void func_001011B0(struct ResidentSystem* system, void* destination, s32 type, u32 size);

void func_00100AB0(void* object);

/**
 * @brief Allocate the system's status byte at a random heap address and mark it clean.
 * @param system Resident system.
 */
void resident_system_create_status(struct ResidentSystem* system);

/**
 * @brief Set progressive (525p) or interlaced output and reset the GS to match.
 * @param system Resident system.
 * @param progressive Nonzero for progressive output.
 */
void resident_system_set_progressive(struct ResidentSystem* system, u8 progressive);

/**
 * @brief Load the overlay in a slot, delete the request, then unwind to main's stack and run the new program.
 * @param system Resident system.
 * @param program Request for the next program; switching deletes it.
 * @param slot Slot in the resident overlay table D_001B5FB0.
 */
void resident_system_switch_program(struct ResidentSystem* system, void* program, s32 slot);

/**
 * @brief Load the overlay in a slot and run its static initializers.
 * @param system Resident system.
 * @param program Overlay load request.
 * @param slot Slot in the resident overlay table D_001B5FB0.
 */
void resident_system_load_overlay(struct ResidentSystem* system, void* program, s32 slot);

#ifdef __cplusplus
}
#endif

#endif
