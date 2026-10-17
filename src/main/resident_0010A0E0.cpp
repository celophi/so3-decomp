#include "include_asm.h"
#include "main/resident_0010A0E0.h"
#include "main/resident_00101550.h"

/**
 * @brief Check whether the object release ring has no insertion slot available.
 * @param queue Deferred release queues.
 * @return True when the object ring is full, or false when it has space.
 */
static inline bool resident_object_release_ring_is_full(const ResidentReleaseQueues* queue)
{
    return queue->objects.read_index == queue->objects.write_index;
}

extern "C" {
void func_00118880(void* object);
void func_00114E00(void* value);
s32 iWakeupThread(s32 thread_id);
s32 StartThread(s32 thread_id, void* argument);
s32 SleepThread(void);
s32 func_00135320(double left, double right);
s32 func_00115000(void* object, s32 mode, s32 size);
typedef struct ResidentFloatQuadDA30
{
    float values[4];
} ResidentFloatQuadDA30;
extern const ResidentFloatQuadDA30 D_00144260;
typedef struct ConstantByteSetterOwnerresident_0010A0E0
{
    u8 unk00[0x1012];
    u8 unk1012;
} ConstantByteSetterOwnerresident_0010A0E0;



typedef struct WordSetterOwnerresident_0010A0E0
{
    u8 unk00[0x134];
    u32 unk134;
} WordSetterOwnerresident_0010A0E0;



typedef struct WordGetterOwnerresident_0010A0E0
{
    u8 unk00[0x8];
    u32 unk08;
    u8 unk0c[0xF8];
    u32 unk104;
    u8 unk108[0x4];
    u32 unk10c;
    u32 unk110;
    u8 unk114[0x4];
    u32 unk118;
} WordGetterOwnerresident_0010A0E0;

typedef struct ResidentPairSetter112D70
{
    u8 unk00[0x10];
    u32 unk10;
    void* unk14;
} ResidentPairSetter112D70;

typedef struct ResidentTwoByteClear15420
{
    u8 unk00[0x6C];
    u8 unk6C;
    u8 unk6D[0xD3];
    u8 unk140;
} ResidentTwoByteClear15420;

typedef struct ResidentThreadHandle114DD0
{
    u8 pad00[0x8];
    s32 unk08;
} ResidentThreadHandle114DD0;

typedef struct ResidentHalfwordSetter14560
{
    u8 pad00[0x10];
    s16 unk10;
} ResidentHalfwordSetter14560;

typedef struct ResidentThreadStartContext14EB0
{
    u8 pad00[0x8];
    s32 unk08;
} ResidentThreadStartContext14EB0;

typedef struct ResidentWordExchange10
{
    u8 unk00[0x10];
    u32 unk10;
} ResidentWordExchange10;

typedef struct ResidentWordAndFlag2F9
{
    u8 unk00[0x8];
    u32 unk08;
    u8 unk0c[0x2ED];
    u8 unk2F9;
} ResidentWordAndFlag2F9;

typedef struct ResidentDistanceRequestEA70
{
    u8 unk00[0x1390];
    void* target;
    float value;
    float distance_squared;
} ResidentDistanceRequestEA70;

typedef struct ResidentSixWordSetter152C0
{
    u8 unk00[0x15C];
    u32 unk15C;
    u32 unk160;
    u32 unk164;
    u32 unk168;
    u32 unk16C;
    u32 unk170;
} ResidentSixWordSetter152C0;

typedef struct ResidentFloatCopyTargetEAA0
{
    u8 pad00[0x139C];
    float values[4];
} ResidentFloatCopyTargetEAA0;

typedef struct ResidentByteAndWordResetB730
{
    u8 pad00[0x78];
    u8 unk78[4];
    u32 unk7C;
    u32 unk80;
    u32 unk84;
} ResidentByteAndWordResetB730;

typedef struct ResidentByteStoreAndHelperDA70
{
    void* unk00;
    u8 pad04[0x44C];
    u8 unk450;
} ResidentByteStoreAndHelperDA70;

typedef struct ResidentManagerEF50
{
    void* unk00;
    u8 pad04[0x14];
    void* unk18[7];
    u32 unk34;
} ResidentManagerEF50;


extern u8 D_001B6880[];
extern s32 D_001B640C;
extern ResidentManagerEF50* D_001B6410;
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

/** Clear bytes at 0x78-0x7B and copy the word at 0x84 to offsets 0x7C and 0x80. */
void func_0010B730(void* object)
{
    ResidentByteAndWordResetB730* receiver = (ResidentByteAndWordResetB730*)object;
    receiver->unk78[0] = 0;
    receiver->unk78[1] = 0;
    receiver->unk78[2] = 0;
    receiver->unk78[3] = 0;
    receiver->unk7C = receiver->unk84;
    receiver->unk80 = receiver->unk84;
}

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

/** Copy the default resident float quad into the receiver's float fields. */
void func_0010DA30(void* object)
{
    ResidentFloatQuadDA30 values = D_00144260;
    ResidentFloatCopyTargetEAA0* receiver = (ResidentFloatCopyTargetEAA0*)object;
    receiver->values[0] = values.values[0];
    receiver->values[1] = values.values[1];
    receiver->values[2] = values.values[2];
    receiver->values[3] = values.values[3];
}

/** Store the low byte at offset 0x450, then run the resident helper on the pointer at offset 0. */
void func_0010DA70(void* object, u32 value)
{
    ResidentByteStoreAndHelperDA70* receiver = (ResidentByteStoreAndHelperDA70*)object;
    receiver->unk450 = value;
    func_00108C40(receiver->unk00, 0, 0, 0, value & 0xFF);
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010DAA0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010DB10);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010DBB0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010DE90);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010DEF0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010DF70);

/**
 * @brief Forward the manager's first pointer and the argument to func_00107D90.
 * @param argument Value forwarded as the helper's second argument.
 */
void func_0010DFC0(void* argument)
{
    func_00107D90(D_001B6410->unk00, argument);
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010DFF0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010E060);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010E130);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010E200);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010E310);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010E4B0);

void func_0010EA70(ResidentRequest112400* request, void* target, float value, float distance)
{
    ResidentDistanceRequestEA70* receiver = (ResidentDistanceRequestEA70*)request;
    receiver->target = target;
    receiver->value = value;
    receiver->distance_squared = distance * distance;
}

/** Store the float at receiver offset 0x139C for index. */
void func_0010EA90(void* object, s32 index, float value)
{
    float* values = (float*)object;
    values[index + 0x4E7] = value;
}

/** Copy four floats to receiver offsets 0x139C, 0x13A0, 0x13A4, and 0x13A8. */
void func_0010EAA0(void* object, const float* values)
{
    ResidentFloatCopyTargetEAA0* receiver = (ResidentFloatCopyTargetEAA0*)object;
    receiver->values[0] = values[0];
    receiver->values[1] = values[1];
    receiver->values[2] = values[2];
    receiver->values[3] = values[3];
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010EAD0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010EB90);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010EC00);

/** Run the helper on the object's pointer when it is non-null. */
void func_0010ECF0(void* object)
{
    void* value = *(void**)object;
    if (value != 0) {
        func_001071A0(value, 0);
    }
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010ED20);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010ED90);

void func_0010EE50(void* object)
{
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010EE60);

/** Append the pointer at object offset zero to the resident manager array. */
void func_0010EF50(const void* object)
{
    ResidentManagerEF50* manager = D_001B6410;
    void* pointer = *(void**)object;
    u32 index = manager->unk34;
    manager->unk34 = index + 1;
    manager->unk18[index] = pointer;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010EF80);

s32 func_0010EFD0(void* object)
{
    return func_00107B10(*(void**)object, 0, 0, 0, 1) != 0;
}

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

void func_00112D70(void* object, u32 value, void* pointer)
{
    ResidentPairSetter112D70* receiver = (ResidentPairSetter112D70*)object;
    receiver->unk10 = value;
    receiver->unk14 = pointer;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00112D80);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00112E70);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00112F60);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00112FE0);

void func_00113180(void* object)
{
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00113190);

/**
 * @brief Resize a block, releasing and replacing it when it must grow.
 *
 * Growing a block does not preserve its contents.
 *
 * @param memory Resident heap allocation to resize.
 * @param size Requested payload size in bytes.
 * @return Allocation base, or null if a replacement cannot be allocated.
 */
INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_heap_resize);

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

void func_00113EA0(void* object)
{
}

typedef struct ResidentPolledFlag13EB0
{
    u8 pad00[0x1011];
    volatile u8 flag;
} ResidentPolledFlag13EB0;

/** Return the state byte or wait for it to clear when requested. */
u32 func_00113EB0(void* object, s32 wait)
{
    ResidentPolledFlag13EB0* state = (ResidentPolledFlag13EB0*)object;
    if (wait != 0) {
        return state->flag;
    }
    while (state->flag != 0) {
    }
    return 0;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00113EF0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00113FD0);

/** Store 0x1 at receiver offset 0x1012. */
void func_001140F0(void* object)
{
    ConstantByteSetterOwnerresident_0010A0E0* receiver = (ConstantByteSetterOwnerresident_0010A0E0*)object;
    receiver->unk1012 = 0x1;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114100);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001142C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114330);

s32 func_001143E0(double left, double right)
{
    return func_00135320(left, right) > 0;
}

s32 func_00114400(double left, double right)
{
    return func_00135320(left, right) < 0;
}

s32 func_00114420(double left, double right)
{
    return func_00135320(left, right) == 0;
}

void func_00114450(void* object)
{
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114460);

s32 func_00114560(void* object, s16 value, s32 size)
{
    ResidentHalfwordSetter14560* receiver = (ResidentHalfwordSetter14560*)object;
    receiver->unk10 = value;
    return func_00115000(object, 50, size);
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114580);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114650);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114720);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114790);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114870);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001148B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114A00);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114BD0);

/** Return whether waking the resident thread succeeds. */
s32 func_00114DD0(const void* object)
{
    const ResidentThreadHandle114DD0* receiver = (const ResidentThreadHandle114DD0*)object;
    return iWakeupThread(receiver->unk08) >= 0;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114E00);

/** Return whether the resident thread sleep request succeeds. */
s32 func_00114E80(void)
{
    return SleepThread() >= 0;
}

/** Return whether the resident thread starts successfully. */
s32 func_00114EB0(void* object)
{
    ResidentThreadStartContext14EB0* receiver = (ResidentThreadStartContext14EB0*)object;
    return StartThread(receiver->unk08, object) >= 0;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114EE0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114F50);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00115000);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001150C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001151B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00115270);

/** Store six words at receiver offsets 0x15C through 0x170. */
void func_001152C0(void* object, u32 arg1, u32 arg2, u32 arg3,
                   u32 arg4, u32 arg5, u32 arg6)
{
    ResidentSixWordSetter152C0* receiver = (ResidentSixWordSetter152C0*)object;
    receiver->unk15C = arg1;
    receiver->unk168 = arg2;
    receiver->unk160 = arg3;
    receiver->unk16C = arg4;
    receiver->unk164 = arg5;
    receiver->unk170 = arg6;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001152E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00115310);

void func_00115420(void* object)
{
    ResidentTwoByteClear15420* receiver = (ResidentTwoByteClear15420*)object;
    receiver->unk140 = 0;
    receiver->unk6C = 0;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00115430);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00115460);

/** Return the word at receiver offset 0x110. */
u32 func_00115640(const void* object)
{
    const WordGetterOwnerresident_0010A0E0* receiver = (const WordGetterOwnerresident_0010A0E0*)object;
    return receiver->unk110;
}

/** Return the word at receiver offset 0x10C. */
u32 func_00115650(const void* object)
{
    const WordGetterOwnerresident_0010A0E0* receiver = (const WordGetterOwnerresident_0010A0E0*)object;
    return receiver->unk10c;
}

/** Return the word at receiver offset 0x118. */
u32 func_00115660(const void* object)
{
    const WordGetterOwnerresident_0010A0E0* receiver = (const WordGetterOwnerresident_0010A0E0*)object;
    return receiver->unk118;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00115670);

/** Store the word at receiver offset 0x134. */
void func_001156B0(void* object, u32 value)
{
    WordSetterOwnerresident_0010A0E0* receiver = (WordSetterOwnerresident_0010A0E0*)object;
    receiver->unk134 = value;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001156C0);

void func_00115810(void* object)
{
    func_00118880((u8*)object + 0xEC);
}

/** Return the word at receiver offset 0x104. */
u32 func_00115830(const void* object)
{
    const WordGetterOwnerresident_0010A0E0* receiver = (const WordGetterOwnerresident_0010A0E0*)object;
    return receiver->unk104;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00115840);

/** Sum each entry value when its resident flag word is nonzero. */
u32 func_001158A0(const void* object)
{
    const u8* entry = (const u8*)object;
    u32 total = 0;
    for (s32 index = 0; index < 0x1800; index++, entry += sizeof(u32)) {
        if (*(const u32*)(entry + 0xC17C) != 0) {
            total += *(const u32*)(entry + 0x617C);
        }
    }
    return total;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001158E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00118880);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00118A70);

void func_00118B80(void* object, void* value)
{
    func_00114E00(value);
}

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

void func_0011C6B0(void* object)
{
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011C6C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011C6E0);

/** Return bit 0 of the word at receiver offset 0xCC. */
s32 func_0011C7C0(const void* object)
{
    const u32* values = (const u32*)object;
    return (values[0x33] & 1) != 0;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011C7D0);

/** Return the descriptor's low 24-bit size value in bytes for key. */
u32 func_0011C8C0(struct ResidentObject1B65E4* object, s32 key)
{
    const u32* values = (const u32*)((const u8*)object + 0x617C);
    return (values[key] & 0x00FFFFFF) << 11;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011C8E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011CA60);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011CB00);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011CC00);

s32 func_0011CC00(void* object, void* arg1, void* arg2);

void func_0011D060(void* object, void* arg1, void* arg2)
{
    func_0011CC00(object, arg1, arg2);
}

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

/** Return and clear the word at receiver offset 0x10. */
u32 func_0011DF00(void* object)
{
    ResidentWordExchange10* receiver = (ResidentWordExchange10*)object;
    u32 value = receiver->unk10;
    receiver->unk10 = 0;
    return value;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011DF10);

/** Store the word at receiver offset 0x8 and clear its byte at offset 0x2F9. */
void func_0011DF60(void* object, u32 value)
{
    ResidentWordAndFlag2F9* receiver = (ResidentWordAndFlag2F9*)object;
    receiver->unk08 = value;
    receiver->unk2F9 = 0;
}

/** Return the word at receiver offset 0x8. */
u32 func_0011DF70(const void* object)
{
    const WordGetterOwnerresident_0010A0E0* receiver = (const WordGetterOwnerresident_0010A0E0*)object;
    return receiver->unk08;
}

/** Clear the word at receiver offset 0x8 and its byte at offset 0x2F9. */
void func_0011DF80(void* object)
{
    ResidentWordAndFlag2F9* receiver = (ResidentWordAndFlag2F9*)object;
    receiver->unk08 = 0;
    receiver->unk2F9 = 0;
}

/** Clear the halfwords at receiver offsets 0x268 and 0x26C for index. */
void func_0011DF90(void* object, s32 index)
{
    u16* values = (u16*)object;
    values[index + 0x134] = 0;
    values[index + 0x136] = 0;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011DFB0);

u16 func_0011DFF0(const void* object, s32 index)
{
    const u16* values = (const u16*)((const u8*)object + 0x26C);
    return values[index];
}

u16 func_0011E000(const void* object, s32 index)
{
    const u16* values = (const u16*)((const u8*)object + 0x268);
    return values[index];
}

u16 func_0011E010(const void* object, s32 index)
{
    const u16* values = (const u16*)((const u8*)object + 0x260);
    return values[index];
}

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

/**
 * @brief Release pending allocations, then destroy pending objects and flush the cache.
 * @param queues Deferred release queues to drain.
 */
INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_drain_release_queues);

/**
 * @brief Queue an object for destruction by its virtual destructor.
 * @param queue Deferred release queues.
 * @param object Object to destroy later; null succeeds without insertion.
 * @return One on success, or zero when the object ring is full.
 */
s32 resident_enqueue_object(ResidentReleaseQueues* queue, void* object)
{
    if (object == 0)
    {
        return 1;
    }

    if (resident_object_release_ring_is_full(queue))
    {
        return 0;
    }

    queue->objects.entries[queue->objects.write_index++] = object;

    if (queue->objects.write_index >= 0x400)
    {
        queue->objects.write_index = 0;
    }

    return 1;
}
}
