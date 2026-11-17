#ifndef SO3_MAIN_HEAP_H
#define SO3_MAIN_HEAP_H

#include "types.h"
#include "sdk/main/libkernl_00121940.h"
#include "ee.h"

#ifndef __cplusplus
typedef struct ResidentHeap ResidentHeap;
#endif

#define RESIDENT_HEAP_BLOCK_TAG 0x4D655279
#define RESIDENT_HEAP_BLOCK_MARKER 0x4058
#ifdef __cplusplus
class ResidentHeap;

/** Header in front of every block of a resident heap, allocated or free. */
struct ResidentHeapBlock
{
    s32 size;
    u8 flags;
    u8 allocated;
    u16 marker;
    ResidentHeapBlock* physical_previous;
    ResidentHeapBlock* physical_next;
    ResidentHeap* owner;
    ResidentHeapBlock* free_next;
    ResidentHeapBlock* free_previous;
    u32 tag;
};

/** A resident allocation heap: blocks carved from one memory range, with up to eight child heaps to fall back on. */
class ResidentHeap
{
    public:
        ResidentHeapBlock head;
        ResidentHeapBlock* free_anchor;
        void* memory;
        u8 use_fallbacks;
        u8 alternate;
        u8 unk2a[2];
        s32 alignment;
        s32 fallback_count;
        ResidentHeap* fallbacks[8];

        /** @brief Construct an empty heap with no memory, 16-byte alignment and child heaps enabled. */
        ResidentHeap();

        /** @brief Release heap storage and child heaps. */
        virtual ~ResidentHeap();
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Allocate a block from a resident heap.
 * @param heap Heap to allocate from.
 * @param size Requested payload size in bytes.
 * @return Allocation base, or null when no block is available.
 */
void* resident_heap_allocate(void* heap, s32 size);

/**
 * @brief Resize a block, releasing and replacing it when it must grow.
 *
 * Growing a block does not preserve its contents.
 *
 * @param memory Resident heap allocation to resize.
 * @param size Requested payload size in bytes.
 * @return Allocation base, or null if a replacement cannot be allocated.
 */
void* resident_heap_resize(void* memory, s32 size);

/**
 * @brief Return a block to its resident heap.
 * @param memory Allocation to release.
 */
void resident_heap_release(void* memory);

/** @brief Do nothing. */
void resident_heap_do_nothing(void);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {

    /**
     * @brief Give a heap memory of its own.
     * @param heap Heap.
     * @param size Usable size in bytes.
     * @return Nonzero on success, zero when the memory can't be allocated.
     */
    u32 resident_heap_create_memory(ResidentHeap* heap, u32 size);

    /**
     * @brief Give a heap a memory range to allocate from.
     * @param heap Heap.
     * @param address Start of the range, or null.
     * @param size Size of the range in bytes.
     * @return Nonzero on success, zero for a null range.
     */
    u32 resident_heap_set_range(ResidentHeap* heap, void* address, u32 size);

    /**
     * @brief Allocate from the top of a heap's free blocks, trying its child heaps first.
     * @param heap Heap.
     * @param size Requested payload size in bytes.
     * @return Allocation, or null when no block is available.
     */
    void* resident_heap_allocate_top(ResidentHeap* heap, s32 size);

    /**
     * @brief Measure a heap and its child heaps.
     * @param heap Heap to measure.
     * @param free_bytes Receives the total size of the free blocks.
     * @param used_bytes Receives the total size of the allocated blocks.
     * @return Largest allocation that would fit in one free block.
     */
    s32 resident_heap_measure(ResidentHeap* heap, s32* free_bytes, s32* used_bytes);

    /**
     * @brief Delete a heap's child heaps.
     * @param heap Heap.
     */
    void resident_heap_delete_children(ResidentHeap* heap);

    /**
     * @brief Add a child heap over a memory range.
     * @param heap Parent heap.
     * @param address Start of the child's range.
     * @param size Size of the child's range in bytes.
     * @return Nonzero when the child was added, zero when the parent is full or the child can't be made.
     */
    u32 resident_heap_add_child_range(ResidentHeap* heap, void* address, u32 size);

    /**
     * @brief Add a child heap with memory of its own.
     * @param heap Parent heap.
     * @param size Usable size of the child in bytes.
     * @return Nonzero when the child was added, zero when the parent is full or the child can't be made.
     */
    u32 resident_heap_add_child(ResidentHeap* heap, u32 size);
}
#endif

#endif
