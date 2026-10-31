#include "include_asm.h"
#include "main/resident_001001E0.h"
#include "main/resident_0010A0E0.h"

extern u8 D_001B6420;
extern "C" void* __nw__FUi(u32 size);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", func_001001E0);

void func_00100A40(u8 value)
{
    D_001B6420 = value;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", func_00100A50);

void func_00100AB0(void* object)
{
}

/** @brief Allocate through the selected heap or the default new allocator. @param size Byte count. @param unused Ignored second argument. @return Allocated memory. */
void* func_00100AC0(u32 size, s32 unused)
{
    if (D_001B6400 != 0)
    {
        return resident_heap_allocate(D_001B6400, size);
    }
    return __nw__FUi(size);
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", __nwa__FUii);

extern "C" void free_guess(void* memory);
/** Partial resident allocation header containing its two ownership markers. */
struct ResidentAllocationHeader
{
    u8 unk00[6];
    u16 marker;
    u8 unk08[0x14];
    u32 tag;
};

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


INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", func_00100BE0);

/** @brief Exchange the heap selected for resident new allocations. @param heap New heap, or null for the default allocator. @return Previous heap. */
void* resident_exchange_allocation_heap(void* heap)
{
    void* previous = D_001B6400;
    D_001B6400 = heap;
    return previous;
}

/** @brief Read the heap selected for resident new allocations. @return Current heap, or null for the default allocator. */
void* resident_get_allocation_heap(void)
{
    return D_001B6400;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", func_00100CA0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", func_00100D00);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", func_00100E70);

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

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", func_00100FC0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", func_00101000);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", resident_system_set_progressive);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", func_001010A0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", resident_system_switch_program);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", func_001011B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", resident_system_load_overlay);
