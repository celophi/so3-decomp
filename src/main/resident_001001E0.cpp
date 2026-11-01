#include "include_asm.h"
#include "main/resident_001001E0.h"
#include "main/resident_0010A0E0.h"
#include "sdk/main/libgraph_0012EAC8.h"
#include "sdk/main/libc_guess_00131D18.h"
#include "sdk/main/libc_guess_00137290.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "sdk/main/libkernl_00121940.h"
#include "sdk/main/mslgcc_00142A40.h"

extern u8 D_001B6420;

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", func_001001E0);

void func_00100A40(u8 value)
{
    D_001B6420 = value;
}

/** Object that reports running out of memory in place of the default message; null by default. */
class ResidentMemoryHook
{
public:
    virtual void func_slot08();

    /** @brief Report running out of memory. @param data D_001CC510. */
    virtual void func_slot0c(void* data);
};

/** Partial resident state at D_001CC500, holding the out-of-memory hook. */
struct ResidentMemoryState
{
    ResidentMemoryHook* hook;
    u8 unk04;
    s32 unk08;
    s32 unk0c;
};

extern "C" {
extern ResidentMemoryState D_001CC500;
extern u8 D_001CC510[];

/** "Memory exhaused.\n" */
extern const char D_0014D660[];
}

/** @brief The new handler main installs: report through the hook, or print a message and exit. */
void resident_handle_out_of_memory(void)
{
    if (D_001CC500.hook != 0)
    {
        D_001CC500.hook->func_slot0c(D_001CC510);
    }
    else
    {
        printf(D_0014D660);
        exit(1);
    }
}

void func_00100AB0(void* object)
{
}

/**
 * @brief Allocate memory from the current heap, or from the default allocator when none is set.
 * @param size Number of bytes to allocate.
 * @param unused Second argument passed by callers; the resident implementation ignores it.
 * @return The allocated memory.
 */
void* operator new(u32 size, s32 unused)
{
    if (g_allocation_heap != 0)
    {
        return resident_heap_allocate(g_allocation_heap, size);
    }
    return ::operator new(size);
}

/**
 * @brief Allocate array memory from the current heap, or from the default allocator when none is set.
 * @param size Number of bytes to allocate.
 * @param unused Second argument passed by callers; the resident implementation ignores it.
 * @return The allocated memory.
 */
void* operator new[](u32 size, s32 unused)
{
    if (g_allocation_heap != 0)
    {
        return resident_heap_allocate(g_allocation_heap, size);
    }
    return ::operator new(size);
}

/** Partial resident allocation header containing its two ownership markers. */
struct ResidentAllocationHeader
{
    u8 unk00[6];
    u16 marker;
    u8 unk08[0x14];
    u32 tag;
};

// TODO: The destructors inline operator delete, but resident_system_create_status doesn't inline operator new[],
// so auto inlining seems to have been on only for this function.
#pragma push
#pragma auto_inline on

/** @brief Release resident heap allocations or use the default free routine. @param memory Allocation to release, or null. */
void operator delete(void* memory) throw()
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

#pragma pop

/** @brief Release resident heap arrays or use the default free routine. @param memory Allocation to release, or null. */
void operator delete[](void* memory) throw()
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

/** @brief Exchange the heap selected for resident new allocations. @param heap New heap, or null for the default allocator. @return Previous heap. */
void* resident_exchange_allocation_heap(void* heap)
{
    void* previous = g_allocation_heap;
    g_allocation_heap = heap;
    return previous;
}

/** @brief Read the heap selected for resident new allocations. @return Current heap, or null for the default allocator. */
void* resident_get_allocation_heap(void)
{
    return g_allocation_heap;
}

/** End of the program image, where the C library heap starts. */
extern "C" u8 _end[];

/** Size of the main thread's stack; the linker passes it as an address. */
extern "C" u8 _stack_size[];

/**
 * @brief Allocate and free all memory between the program and the stack, so the C library claims it in one block.
 * @return Size of the block.
 */
u32 resident_prime_heap(void)
{
    u32 stack = (u32)_stack_size + 0x1000;
    u32 size = 0x2000000 - ((u32)_end + stack + 0x1000);
    free_guess(malloc_guess(size - 0x10));
    return size - 0x10;
}

/** @brief Destroy every part of the system. */
ResidentSystem::~ResidentSystem()
{
}

/**
 * @brief Allocate the system's status byte at a random heap address and mark it clean.
 * @param system Resident system.
 */
void resident_system_create_status(ResidentSystem* system)
{
    // Never freed; it only moves the status byte to a different address on each boot.
    new (0) u8[(resident_rand() & 0x3FF) + 0x40];
    system->status = new (0) u8[0x10];
    *system->status = 0x66;
}

/**
 * @brief Set an alarm from interrupt context, doubling the time in progressive mode so it lasts as long as in
 * interlaced mode.
 * @param system Resident system.
 * @param time Horizontal syncs to wait in interlaced mode.
 * @param handler Handler to call from interrupt context.
 * @param common Argument passed to the handler.
 * @return Alarm ID, or a negative value on failure.
 */
s32 resident_system_iset_alarm(ResidentSystem* system, u16 time, KernelAlarmHandler handler, void* common)
{
    if (system->progressive)
    {
        time *= 2;
    }
    return iSetAlarm(time, handler, common);
}

/**
 * @brief Set an alarm, doubling the time in progressive mode so it lasts as long as in interlaced mode.
 * @param system Resident system.
 * @param time Horizontal syncs to wait in interlaced mode.
 * @param handler Handler to call from interrupt context.
 * @param common Argument passed to the handler.
 * @return Alarm ID, or a negative value on failure.
 */
s32 resident_system_set_alarm(ResidentSystem* system, u16 time, KernelAlarmHandler handler, void* common)
{
    if (system->progressive)
    {
        time *= 2;
    }
    return SetAlarm(time, handler, common);
}

/**
 * @brief Set progressive (525p) or interlaced output and reset the GS to match.
 * @param system Resident system.
 * @param progressive Nonzero for progressive output.
 */
void resident_system_set_progressive(ResidentSystem* system, u8 progressive)
{
    system->progressive = progressive;

    if (progressive)
    {
        sceGsResetGraph(0, SCE_GS_NOINTERLACE, SCE_GS_DTV480P, SCE_GS_FRAME);
    }
    else
    {
        sceGsResetGraph(0, SCE_GS_INTERLACE, SCE_GS_NTSC, SCE_GS_FRAME);
    }
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", func_001010A0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", resident_system_switch_program);

/**
 * @brief Clear a decoded overlay's BSS and run its static initializers.
 * @param system Resident system.
 * @param overlay Decoded overlay image.
 * @param slot The overlay's slot in the resident overlay table D_001B5FB0.
 * @param size Decoded size of the overlay image; its BSS follows it.
 */
void resident_system_init_overlay(ResidentSystem* system, void* overlay, s32 slot, u32 size)
{
    mwOverlayInit(overlay, size);
}

/** Load address of the overlay in each slot, or null for an empty slot. */
extern "C" void* D_001B5FB0[];

/**
 * @brief Decode an overlay into its slot and run its static initializers.
 * @param system Resident system.
 * @param source Loaded, compressed overlay resource.
 * @param slot Slot in the resident overlay table D_001B5FB0.
 */
void resident_system_load_overlay(ResidentSystem* system, ResidentResourceHeader* source, s32 slot)
{
    u32 size;
    void* overlay = D_001B5FB0[slot];

    if (overlay != 0)
    {
        resident_decode_resource_block(&system->decoder, source, overlay, 0);
        size = source->decoded_size;
        FlushCache(0);
        mwOverlayInit(overlay, size);
        FlushCache(2);
    }
}
