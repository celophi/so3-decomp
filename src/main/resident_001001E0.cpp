#include "include_asm.h"
#include "main/resident_001001E0.h"
#include "main/resident_0010A0E0.h"

extern void* D_001B6400;
extern "C" void* __nw__FUi(u32 size);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", func_001001E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", func_00100A40);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", func_00100A50);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", func_00100AB0);

/** @brief Allocate through the selected heap or the default new allocator. @param size Byte count. @param unused Ignored second argument. @return Allocated memory. */
void* func_00100AC0(u32 size, s32 unused)
{
    if (D_001B6400 != 0)
    {
        return resident_heap_allocate(D_001B6400, size);
    }
    return __nw__FUi(size);
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", func_00100B00);

extern "C" void func_00139928(void* memory);
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
            func_00139928(memory);
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

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", func_00100F60);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", func_00100FC0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", func_00101000);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", func_00101040);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", func_001010A0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", func_001010D0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", func_001011B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_001001E0", func_001011D0);
