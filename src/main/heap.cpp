#include "include_asm.h"
#include "sdk/main/libc_guess_00137290.h"
#include "main/resident_data.h"

extern "C" {

/**
 * @brief Measure a heap and its fallback heaps.
 * @param heap Heap to measure.
 * @param free_bytes Receives the total size of the free blocks.
 * @param used_bytes Receives the total size of the allocated blocks.
 * @return Largest allocation that would fit in one free block.
 */
s32 resident_heap_measure(ResidentHeap* heap, s32* free_bytes, s32* used_bytes)
{
    s32 largest = 0;

    *used_bytes = 0;
    *free_bytes = 0;

    for (ResidentHeapBlock* block = heap->free_anchor->physical_previous; block != heap->free_anchor;
         block = block->physical_previous)
    {
        if (block->allocated)
        {
            *used_bytes += block->size;
        }
        else
        {
            *free_bytes += block->size;

            if (block->size > largest)
            {
                largest = block->size;
            }
        }
    }

    largest -= 0x10;

    if (largest < 0)
    {
        largest = 0;
    }

    if (heap->use_fallbacks)
    {
        for (s32 i = 0; i < heap->fallback_count; i++)
        {
            if (heap->fallbacks[i])
            {
                s32 fallback_free;
                s32 fallback_used;
                s32 fallback_largest = resident_heap_measure(heap->fallbacks[i], &fallback_free, &fallback_used);

                if (fallback_largest > largest)
                {
                    largest = fallback_largest;
                }

                *free_bytes += fallback_free;
                *used_bytes += fallback_used;
            }
        }
    }

    return largest;
}

/**
 * @brief Resize a block, releasing and replacing it when it must grow.
 *
 * Shrinking frees the space the block no longer needs, joining it to a free neighbour when there is one. Growing a
 * block does not preserve its contents.
 *
 * @param memory Resident heap allocation to resize.
 * @param size Requested payload size in bytes.
 * @return Allocation base, or null if a replacement cannot be allocated.
 */
void* resident_heap_resize(void* memory, s32 size)
{
    ResidentHeapBlock* block = (ResidentHeapBlock*)memory - 1;
    ResidentHeapBlock* rest;
    s32 alignment = block->owner->alignment;
    ResidentHeapBlock* anchor = block->owner->free_anchor;
    s32 rounded = -alignment & (size + 0x1F + alignment);

    if (block->size == rounded)
    {
        return memory;
    }

    if (rounded < block->size)
    {
        if (block->physical_previous->allocated && block->size - rounded < alignment + 0x20)
        {
            return memory;
        }

        rest = (ResidentHeapBlock*)((u8*)block + rounded);

        if (block->physical_previous->allocated)
        {
            rest->size = block->size - rounded;
            rest->physical_previous = block->physical_previous;
            rest->physical_next = block;
            rest->allocated = 0;
            rest->tag = 0;
            rest->marker = 0;

            ResidentHeapBlock* free;

            for (free = block->physical_next; free != anchor; free = free->physical_next)
            {
                if (!free->allocated)
                {
                    break;
                }
            }

            ResidentHeapBlock* following = free->free_next;
            rest->free_previous = free;
            rest->free_next = following;
            following->free_previous = rest;
            free->free_next = rest;
            block->physical_previous->physical_next = rest;
            block->physical_previous = rest;
        }
        else
        {
            ResidentHeapBlock merged = *block->physical_previous;
            rest->free_next = merged.free_next;
            rest->free_previous = merged.free_previous;
            rest->free_next->free_previous = rest;
            rest->free_previous->free_next = rest;
            ResidentHeapBlock* above = merged.physical_previous;
            above->physical_next = rest;
            rest->physical_next = block;
            rest->physical_previous = above;
            rest->allocated = 0;
            rest->tag = 0;
            rest->marker = 0;
            rest->size = merged.size + block->size - rounded;
            block->physical_previous = rest;
        }

        block->size = rounded;
        return memory;
    }

    resident_heap_release(memory);
    return resident_heap_allocate(block->owner, size);
}

/**
 * @brief Return a block to its heap, merging it with free neighbours and relinking the free list.
 * @param memory Allocation to release.
 */
void resident_heap_release(void* memory)
{
    ResidentHeapBlock* block = (ResidentHeapBlock*)((u8*)memory - 0x20);
    ResidentHeapBlock* previous_free = block->owner->free_anchor;
    ResidentHeapBlock* next_free;

    if (!block->physical_next->allocated)
    {
        previous_free = block->physical_next->free_previous;
        block->physical_previous->physical_next = block->physical_next;
        block->physical_next->physical_previous = block->physical_previous;
        block->physical_next->size += block->size;
        block = block->physical_next;
        next_free = block->free_next;
    }
    else
    {
        if (block->physical_previous->allocated)
        {
            next_free = previous_free->free_next;

            while ((u32)next_free < (u32)block && next_free != previous_free)
            {
                next_free = next_free->free_next;
            }

            previous_free = next_free->free_previous;
        }
        else
        {
            previous_free = block->physical_previous->free_previous;
        }
    }

    if (!block->physical_previous->allocated)
    {
        next_free = block->physical_previous->free_next;
        block->physical_previous->physical_previous->physical_next = block;
        block->size += block->physical_previous->size;
        block->physical_previous = block->physical_previous->physical_previous;
    }

    block->free_previous = previous_free;
    block->free_next = next_free;
    next_free->free_previous = block;
    previous_free->free_next = block;
    block->allocated = 0;
}

/**
 * @brief Allocate from the top of a heap's free blocks, trying its child heaps first.
 * @param heap Heap.
 * @param size Requested payload size in bytes.
 * @return Allocation, or null when no block is available.
 */
void* resident_heap_allocate_top(ResidentHeap* heap, s32 size)
{
    if (heap->use_fallbacks)
    {
        for (s32 i = heap->fallback_count - 1; i >= 0; i--)
        {
            if (heap->fallbacks[i])
            {
                void* memory = resident_heap_allocate_top(heap->fallbacks[i], size);

                if (memory)
                {
                    return memory;
                }
            }
        }
    }

    ResidentHeapBlock* block;
    s32 rounded;
    s32 alignment;
    ResidentHeapBlock* anchor;

    anchor = heap->free_anchor;
    alignment = heap->alignment;
    rounded = -alignment & (size + 0x1F + alignment);

    for (block = anchor->free_previous; block != anchor; block = block->free_previous)
    {
        if (block->size >= rounded && block->size - rounded > alignment + 0x20)
        {
            ResidentHeapBlock* taken = (ResidentHeapBlock*)((u8*)block + block->size - rounded);
            taken->size = rounded;
            taken->allocated = 1;
            taken->tag = RESIDENT_HEAP_BLOCK_TAG;
            taken->marker = RESIDENT_HEAP_BLOCK_MARKER;
            taken->owner = heap;
            block->physical_previous->physical_next = taken;
            taken->physical_previous = block->physical_previous;
            block->physical_previous = taken;
            taken->physical_next = block;
            block->size -= rounded;
            block->allocated = 0;
            block->tag = 0;
            block->marker = 0;
            return taken + 1;
        }
    }

    return 0;
}

/**
 * @brief Allocate from a heap, splitting a free block when there is room, then trying its child heaps.
 * @param receiver Heap.
 * @param size Requested payload size in bytes.
 * @return Allocation, or null when no block is available.
 */
void* resident_heap_allocate(void* receiver, s32 size)
{
    ResidentHeap* heap = (ResidentHeap*)receiver;
    ResidentHeapBlock* block;
    s32 rounded;
    s32 alignment;
    ResidentHeapBlock* anchor;

    if (heap->alternate)
    {
        return resident_heap_allocate_top(heap, size);
    }

    alignment = heap->alignment;
    anchor = heap->free_anchor;
    rounded = -alignment & (size + 0x1F + alignment);

    for (block = anchor->free_next; block != anchor; block = block->free_next)
    {
        if (block->size >= rounded)
        {
            ResidentHeapBlock* rest = (ResidentHeapBlock*)((u8*)block + rounded);
            s32 remaining = block->size - rounded;

            if (remaining > alignment + 0x20)
            {
                rest->size = remaining;
                rest->allocated = 0;
                rest->free_previous = block->free_previous;
                rest->free_next = block->free_next;
                block->free_previous->free_next = rest;
                block->free_next->free_previous = rest;
                block->physical_previous->physical_next = rest;
                rest->physical_previous = block->physical_previous;
                block->physical_previous = rest;
                rest->physical_next = block;
                block->size = rounded;
            }
            else
            {
                block->free_previous->free_next = block->free_next;
                block->free_next->free_previous = block->free_previous;
            }

            block->tag = RESIDENT_HEAP_BLOCK_TAG;
            block->marker = RESIDENT_HEAP_BLOCK_MARKER;
            block->owner = heap;
            block->allocated = 1;
            return block + 1;
        }
    }

    if (heap->use_fallbacks)
    {
        s32 count = heap->fallback_count;
        s32 i;

        for (i = 0; i < count; i++)
        {
            if (heap->fallbacks[i])
            {
                void* memory = resident_heap_allocate(heap->fallbacks[i], size);

                if (memory)
                {
                    return memory;
                }
            }
        }
    }

    return 0;
}

/**
 * @brief Give a heap a memory range to allocate from.
 * @param heap Heap.
 * @param address Start of the range, or null.
 * @param size Size of the range in bytes.
 * @return Nonzero on success, zero for a null range.
 */
u32 resident_heap_set_range(ResidentHeap* heap, void* address, u32 size)
{
    ResidentHeapBlock* block = (ResidentHeapBlock*)address;

    heap->free_anchor = &heap->head;

    if (address == 0)
    {
        return 0;
    }

    heap->alternate = 0;
    heap->free_anchor->size = 4;
    heap->free_anchor->allocated = 1;
    heap->free_anchor->physical_next = block;
    heap->free_anchor->physical_previous = block;
    heap->free_anchor->free_previous = block;
    heap->free_anchor->free_next = block;
    block->size = size;
    block->allocated = 0;
    block->physical_previous = block->physical_next = heap->free_anchor;
    block->free_previous = block->free_next = heap->free_anchor;
    return 1;
}

/**
 * @brief Give a heap memory of its own.
 * @param heap Heap.
 * @param size Usable size in bytes.
 * @return Nonzero on success, zero when the memory can't be allocated.
 */
u32 resident_heap_create_memory(ResidentHeap* heap, u32 size)
{
    heap->free_anchor = &heap->head;
    heap->memory = malloc_guess(size + heap->alignment + 0x20);

    if (heap->memory == 0)
    {
        return 0;
    }

    u32 payload = (u32)((ResidentHeapBlock*)heap->memory + 1);
    ResidentHeapBlock* block = (ResidentHeapBlock*)((payload + heap->alignment - 1) & -heap->alignment) - 1;
    heap->alternate = 0;
    heap->free_anchor->size = 4;
    heap->free_anchor->allocated = 1;
    heap->free_anchor->physical_next = block;
    heap->free_anchor->physical_previous = block;
    heap->free_anchor->free_previous = block;
    heap->free_anchor->free_next = block;
    block->size = size;
    block->allocated = 0;
    block->physical_previous = block->physical_next = heap->free_anchor;
    block->free_previous = block->free_next = heap->free_anchor;
    return 1;
}

/**
 * @brief Delete a heap's child heaps.
 * @param heap Heap.
 */
void resident_heap_delete_children(ResidentHeap* heap)
{
    for (s32 i = 0; i < heap->fallback_count; i++)
    {
        if (heap->fallbacks[i])
        {
            delete heap->fallbacks[i];
            heap->fallbacks[i] = 0;
        }
    }

    heap->fallback_count = 0;
}

/**
 * @brief Give a heap a memory range to allocate from.
 * @param heap Heap.
 * @param address Start of the range, or null.
 * @param size Size of the range in bytes.
 * @return True on success, false for a null range.
 */
static inline bool heap_set_memory(ResidentHeap* heap, void* address, u32 size)
{
    ResidentHeapBlock* block = (ResidentHeapBlock*)address;

    heap->free_anchor = &heap->head;

    if (address == 0)
    {
        return false;
    }

    heap->alternate = 0;
    heap->free_anchor->size = 4;
    heap->free_anchor->allocated = 1;
    heap->free_anchor->physical_next = block;
    heap->free_anchor->physical_previous = block;
    heap->free_anchor->free_previous = block;
    heap->free_anchor->free_next = block;
    block->size = size;
    block->allocated = 0;
    block->physical_previous = block->physical_next = heap->free_anchor;
    block->free_previous = block->free_next = heap->free_anchor;
    return true;
}

/**
 * @brief Add a child heap over a memory range.
 * @param heap Parent heap.
 * @param address Start of the child's range.
 * @param size Size of the child's range in bytes.
 * @return Nonzero when the child was added, zero when the parent is full or the child can't be made.
 */
u32 resident_heap_add_child_range(ResidentHeap* heap, void* address, u32 size)
{
    if (heap->fallback_count >= 8)
    {
        return 0;
    }

    ResidentHeap* child = new (0) ResidentHeap;
    child->alignment = heap->alignment;

    if (child == 0)
    {
        return 0;
    }

    if (!heap_set_memory(child, address, size))
    {
        delete child;
        return 0;
    }

    heap->fallbacks[heap->fallback_count++] = child;
    return 1;
}

/**
 * @brief Add a child heap with memory of its own.
 * @param heap Parent heap.
 * @param size Usable size of the child in bytes.
 * @return Nonzero when the child was added, zero when the parent is full or the child can't be made.
 */
u32 resident_heap_add_child(ResidentHeap* heap, u32 size)
{
    if (heap->fallback_count >= 8)
    {
        return 0;
    }

    ResidentHeap* child = new (0) ResidentHeap;
    child->alignment = heap->alignment;

    if (child == 0)
    {
        return 0;
    }

    if (!resident_heap_create_memory(child, size))
    {
        delete child;
        return 0;
    }

    heap->fallbacks[heap->fallback_count++] = child;
    return 1;
}

/** @brief Release heap storage and child heaps. */
ResidentHeap::~ResidentHeap()
{
    if (memory)
    {
        free_guess(memory);
    }

    for (s32 i = 0; i < fallback_count; i++)
    {
        if (fallbacks[i])
        {
            delete fallbacks[i];
            fallbacks[i] = 0;
        }
    }

    fallback_count = 0;
}

/** @brief Construct an empty heap with no memory, 16-byte alignment and child heaps enabled. */
ResidentHeap::ResidentHeap()
{
    alternate = 0;
    free_anchor = 0;
    alignment = 16;
    memory = 0;

    for (s32 i = 0; i < 8; i++)
    {
        fallbacks[i] = 0;
    }

    fallback_count = 0;
    use_fallbacks = 1;
}

/** @brief Do nothing. */
void resident_heap_do_nothing(void)
{
}
}
