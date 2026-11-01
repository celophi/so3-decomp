#ifndef SO3_MAIN_RESIDENT_001001E0_H
#define SO3_MAIN_RESIDENT_001001E0_H

#include "types.h"
#include "sdk/main/libkernl_00121940.h"

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

/** Partial resident allocation header containing its two ownership markers. */
struct ResidentAllocationHeader
{
    u8 unk00[6];
    u16 marker;
    u8 unk08[0x14];
    u32 tag;
};

extern "C" void resident_heap_release(void* memory);
extern "C" void free_guess(void* memory);

/** @brief Release resident heap allocations or use the default free routine. @param memory Allocation, or null. */
inline void resident_delete(void* memory) throw()
{
    if (memory != 0)
    {
        ResidentAllocationHeader* header = (ResidentAllocationHeader*)((u8*)memory - 0x20);
        if (header->tag == 0x4D655279 && header->marker == 0x4058)
        {
            resident_heap_release(memory);
            return;
        }
        else
        {
            free_guess(memory);
        }
    }
}

/** Kernel semaphore that deletes itself when destroyed; vtable D_0014F9E0. */
class ResidentSemaphore
{
public:
    /** @brief Free a semaphore through the resident heap. @param memory Allocation, or null. */
    static void operator delete(void* memory) throw()
    {
        resident_delete(memory);
    }

    /** Kernel semaphore ID, or a negative value when none was created. */
    s32 id;

    /** @brief Delete the kernel semaphore, if one was created. */
    virtual ~ResidentSemaphore()
    {
        if (id >= 0)
        {
            DeleteSema(id);
        }
    }
};

/** The running program, with vtable D_0014F9F0; its constructor registers it in g_current_program. */
class ResidentProgram
{
public:
    /** @brief Run the program; it ends by switching to the next one, so it never returns. */
    virtual void run();
};

extern "C" {
#endif

/** Optional heap used by resident operator new and aligned decode buffers. */
extern void* g_allocation_heap;

/** The running program; its constructor registers it, and switching programs calls its run(). */
extern struct ResidentProgram* g_current_program;

/** Object that receives the IOP's SIF commands 0 to 3, or null; the sound system registers its stream. */
extern void* g_sif_command_receiver;

/** Load address of the overlay in each slot, or null for an empty slot. */
extern void* D_001B5FB0[];

/** Store a byte in the global at address 0x001B6420. */
void func_00100A40(u8 value);

/** @brief The new handler main installs: report through the hook, or print a message and exit. */
void resident_handle_out_of_memory(void);

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
struct ResidentResourceHeader;

/**
 * @brief Clear a decoded overlay's BSS and run its static initializers.
 * @param system Resident system.
 * @param overlay Decoded overlay image.
 * @param slot The overlay's slot in the resident overlay table D_001B5FB0.
 * @param size Decoded size of the overlay image; its BSS follows it.
 */
void resident_system_init_overlay(struct ResidentSystem* system, void* overlay, s32 slot, u32 size);

void func_00100AB0(void* object);

/**
 * @brief Allocate and free all memory between the program and the stack, so the C library claims it in one block.
 * @return Size of the block.
 */
u32 resident_prime_heap(void);

/**
 * @brief Allocate the system's status byte at a random heap address and mark it clean.
 * @param system Resident system.
 */
void resident_system_create_status(struct ResidentSystem* system);

/**
 * @brief Set an alarm from interrupt context, doubling the time in progressive mode so it lasts as long as in
 * interlaced mode.
 * @param system Resident system.
 * @param time Horizontal syncs to wait in interlaced mode.
 * @param handler Handler to call from interrupt context.
 * @param common Argument passed to the handler.
 * @return Alarm ID, or a negative value on failure.
 */
s32 resident_system_iset_alarm(struct ResidentSystem* system, u16 time, KernelAlarmHandler handler, void* common);

/**
 * @brief Set an alarm, doubling the time in progressive mode so it lasts as long as in interlaced mode.
 * @param system Resident system.
 * @param time Horizontal syncs to wait in interlaced mode.
 * @param handler Handler to call from interrupt context.
 * @param common Argument passed to the handler.
 * @return Alarm ID, or a negative value on failure.
 */
s32 resident_system_set_alarm(struct ResidentSystem* system, u16 time, KernelAlarmHandler handler, void* common);

/**
 * @brief Set progressive (525p) or interlaced output and reset the GS to match.
 * @param system Resident system.
 * @param progressive Nonzero for progressive output.
 */
void resident_system_set_progressive(struct ResidentSystem* system, u8 progressive);

/**
 * @brief Save main's stack and frame pointers, so each program can start from main's stack depth.
 * @param system Resident system.
 */
void resident_system_save_stack(struct ResidentSystem* system);

/**
 * @brief Decode an overlay into its slot and delete the loaded resource, then go back to main's stack depth and run
 * the new program, which never returns.
 * @param system Resident system.
 * @param source Loaded, compressed overlay resource; switching deletes it.
 * @param slot Slot in the resident overlay table D_001B5FB0.
 */
void resident_system_switch_program(struct ResidentSystem* system, struct ResidentResourceHeader* source, s32 slot);

/**
 * @brief Decode an overlay into its slot and run its static initializers.
 * @param system Resident system.
 * @param source Loaded, compressed overlay resource.
 * @param slot Slot in the resident overlay table D_001B5FB0.
 */
void resident_system_load_overlay(struct ResidentSystem* system, struct ResidentResourceHeader* source, s32 slot);

#ifdef __cplusplus
}
#endif

#endif
