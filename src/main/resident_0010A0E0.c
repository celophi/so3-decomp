#include "include_asm.h"
#include "main/resident_0010A0E0.h"

extern u8 D_001B6880[];
extern s32 D_001B640C;
extern u32 D_001CF8E0[56];

/** Heap block header and owner prefix used by allocation and release. */
typedef struct ResidentHeapBlock ResidentHeapBlock;
typedef struct ResidentHeapOwner
{
    u8 pad00[0x20];
    ResidentHeapBlock* free_anchor;
    u32 unk24;
    u8 use_fallbacks;
    u8 alternate;
    u8 pad2a[2];
    s32 alignment;
    s32 fallback_count;
    struct ResidentHeapOwner* fallbacks[];
} ResidentHeapOwner;
struct ResidentHeapBlock
{
    s32 size;
    u8 flags;
    u8 allocated;
    u16 marker;
    ResidentHeapBlock* physical_previous;
    ResidentHeapBlock* physical_next;
    ResidentHeapOwner* owner;
    ResidentHeapBlock* free_next;
    ResidentHeapBlock* free_previous;
    u32 tag;
};

static inline s32 resident_queue_unavailable(const ResidentObjectQueue* queue)
{
    return queue->read == queue->write;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010A0E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010A200);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010A310);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010A400);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010A450);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010A530);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010A650);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010A7A0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010AA30);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010B4C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010B510);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010B600);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010B730);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010B760);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010B810);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010BBF0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010BC00);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010BC10);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010BC50);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010BC90);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010BCD0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010BD10);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010BDA0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010BE80);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010BFA0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010C0E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010C200);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010C420);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010C550);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010C640);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010C6D0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010C700);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010C820);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010C8E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010CAA0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010CC40);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010CE00);

/**
 * @brief Advance the resident subtractive random sequence and return its next word.
 * @return Next unsigned word from the 55-element sequence.
 */
u32 resident_next_random_word(void)
{
    s32 i;
    s32 j;

    if (++D_001B640C > 55)
    {
        for (i = 24; i > 0; --i)
        {
            D_001CF8E0[i] -= D_001CF8E0[i + 31];
        }
        for (j = 25; j <= 55; ++j)
        {
            D_001CF8E0[j] -= D_001CF8E0[j - 24];
        }
        D_001B640C = 1;
    }
    return D_001CF8E0[D_001B640C];
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010D100);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010D710);

/** @brief Return the resident runtime owner. @return Runtime owner in resident storage. */
void* resident_get_runtime_owner(void)
{
    return D_001B6880;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010D8F0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010DA30);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010DA70);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010DAA0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010DB10);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010DBB0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010DE90);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010DEF0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010DF70);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010DFC0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010DFF0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010E060);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010E130);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010E200);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010E310);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010E4B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010EA70);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010EA90);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010EAA0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010EAD0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010EB90);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010EC00);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010ECF0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010ED20);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010ED90);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010EE50);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010EE60);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010EF50);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010EF80);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010EFD0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010F000);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010F250);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00110340);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001103E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00110480);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00110520);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001105E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001106B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00110920);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00110C10);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00110C60);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00110CE0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00110D80);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00110FB0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00111420);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00111860);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00111A90);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00111C50);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00111EF0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00112160);


/** One of the sixty resident request slots. */
typedef struct ResidentRequestSlot
{
    u8 active;
    u8 pending;
    u8 flags2;
    u8 flags3;
    u8 flags4;
    u8 selector;
    u8 unk06[2];
    s16 value;
    u8 unk0a[2];
    u32 unk0c;
    s32 identifier;
    u32 unk14;
    s32 unk18;
    u8 unk1c;
    u8 unk1d[3];
    void* target;
    u32 unk24;
    u32 unk28;
    u32 unk2c;
    u32 unk30;
    u8 unk34[8];
} ResidentRequestSlot;
/** Receiver prefix containing the cyclic slot cursor and request identifiers. */
struct ResidentRequest112400
{
    void* context;
    u8 unk04[0x10C];
    u8 state;
    u8 unk111[0x260];
    u8 unk371;
    u8 unk372[0x16A];
    u32 next_identifier;
    s32 cursor;
    ResidentRequestSlot slots[60];
};
extern void func_0010EE60(void* response, ResidentRequestSlot* slot);
extern s32 func_00108220(void* context, s32 first,
    void (*callback)(void*, ResidentRequestSlot*), ResidentRequestSlot* slot,
    s32 selected, s32 value, s32 arg3, s32 zero, s32 packed);

/** @brief Find a free slot while advancing and wrapping the allocation cursor. @param receiver Request receiver. @return Free slot index, or minus one. */
static inline s32 find_available_request_slot(ResidentRequest112400* receiver)
{
    s32 i;
    s32 slot;
    for (i = 0; i < 60; i++)
    {
        slot = receiver->cursor;
        if (receiver->slots[slot].active == 0)
        {
            receiver->cursor = slot + 1;
            if (slot + 1 >= 60)
            {
                receiver->cursor = 0;
            }
            return slot;
        }
        receiver->cursor = slot + 1;
        if (slot + 1 >= 60)
        {
            receiver->cursor = 0;
        }
    }
    return -1;
}

/** @brief Locate a request in its slot array. @param slots Slot array. @param index Valid slot index. @return Request slot. */
static inline ResidentRequestSlot* request_slot(ResidentRequestSlot* slots, s32 index)
{
    return &slots[index];
}

/** @brief Reserve and dispatch a request with an unused identifier. @param receiver Request receiver. @param arg1 Request value. @param arg2 Request selector. @param arg3 Forwarded dispatch value. @param arg4 Stored value and upper packed byte. @param arg5 Next packed byte. @param arg6 Lower packed halfword. @return Request identifier, zero on failure, one when disabled, or minus one when unavailable. */
s32 resident_allocate_request(ResidentRequest112400* receiver, s32 arg1, s32 arg2,
                  s32 arg3, s32 arg4, s32 arg5, s32 arg6)
{
    s32 slot;
    s32 i;
    if (receiver->unk371)
    {
        return 1;
    }
    if (receiver->state == 9)
    {
        return -1;
    }
    slot = find_available_request_slot(receiver);
    if (slot == -1)
    {
        return -1;
    }
    do
    {
        for (i = 0; i < 60; i++)
        {
            if (receiver->slots[i].active &&
                receiver->slots[i].identifier == receiver->next_identifier)
            {
                receiver->next_identifier = (receiver->next_identifier + 1) & 0x7FFFFFFF;
                break;
            }
        }
    } while (i != 60);
    {
        ResidentRequestSlot* const request = request_slot(receiver->slots, slot);
        s32* identifier;
        request->unk24 = 0;
        request->unk28 = 0;
        request->active = 1;
        request->pending = 0;
        request->flags2 = 0;
        request->flags4 = 0;
        request->flags3 = 0;
        identifier = &receiver->slots[slot].identifier;
        *identifier = receiver->next_identifier;
        request->target = 0;
        request->unk30 = 0;
        request->selector = arg2;
        request->value = arg1;
        request->unk18 = arg4;
        request->unk1c = 0;
        if (!func_00108220(receiver->context, 0, func_0010EE60, request,
                          ((s32*)((u8*)receiver + 0x454))[arg2], arg1, arg3, 0,
                          ((u32)arg6 & 0xFFFF) | (((u32)arg4 << 24) | ((u32)arg5 << 16))))
        {
            request->active = 0;
            return 0;
        }
        receiver->next_identifier = (receiver->next_identifier + 1) & 0x7FFFFFFF;
        return *identifier;
    }
}


INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00112610);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001126D0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00112990);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00112D70);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00112D80);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00112E70);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00112F60);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00112FE0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00113180);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00113190);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001132F0);

/** @brief Return a block to its heap, coalesce free neighbors, and restore the free-list links. @param memory Allocated payload pointer. */
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

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001135B0);

extern void* func_001135B0(ResidentHeapOwner* heap, s32 size);

/** @brief Allocate from the heap, splitting a free block when possible and searching fallback heaps on failure. @param receiver Heap owner. @param size Requested payload bytes. @return Allocated payload, or null. */
void* resident_heap_allocate(void* receiver, s32 size)
{
    ResidentHeapOwner* heap = (ResidentHeapOwner*)receiver;
    ResidentHeapBlock* block;
    s32 rounded;
    s32 alignment;
    ResidentHeapBlock* anchor;
    if (heap->alternate)
    {
        return func_001135B0(heap, size);
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
            block->tag = 0x4D655279;
            block->marker = 0x4058;
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

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001138B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00113930);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00113A10);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00113AB0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00113C40);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00113D60);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00113E40);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00113EA0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00113EB0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00113EF0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00113FD0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001140F0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114100);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001142C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114330);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001143E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114400);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114420);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114450);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114460);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114560);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114580);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114650);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114720);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114790);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114870);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001148B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114A00);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114BD0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114DD0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114E00);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114E80);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114EB0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114EE0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114F50);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00115000);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001150C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001151B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00115270);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001152C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001152E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00115310);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00115420);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00115430);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00115460);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00115640);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00115650);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00115660);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00115670);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001156B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001156C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00115810);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00115830);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00115840);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001158A0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001158E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00118880);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00118A70);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00118B80);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00118BA0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00118C70);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00119650);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011B5C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011B6A0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011B870);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011BA90);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011BC80);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011BE20);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011BFD0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011C120);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011C6B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011C6C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011C6E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011C7C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011C7D0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011C8C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011C8E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011CA60);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011CB00);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011CC00);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011D060);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011D080);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011D320);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011D470);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011D840);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011D950);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011D9A0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011DA80);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011DBA0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011DC00);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011DD40);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011DDA0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011DE00);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011DEE0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011DF00);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011DF10);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011DF60);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011DF70);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011DF80);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011DF90);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011DFB0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011DFF0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011E000);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011E010);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011E020);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011E030);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011E060);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011E210);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011E290);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011E320);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011E440);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011E540);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011E970);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011E9E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011EA80);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011EC30);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011ECD0);

/** @brief Submit an object to the resident ring queue. @param queue Queue receiver. @param object Object to submit; null succeeds without insertion. @return One on success, or zero when no slot is available. */
s32 resident_enqueue_object(ResidentObjectQueue* queue, void* object)
{
    if (object == 0)
    {
        return 1;
    }
    if (resident_queue_unavailable(queue))
    {
        return 0;
    }
    queue->entries[queue->write++] = object;
    if (queue->write >= 0x400)
    {
        queue->write = 0;
    }
    return 1;
}
