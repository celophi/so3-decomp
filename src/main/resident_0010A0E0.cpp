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
void func_00118880(void* worker, s32 command, s32 argument);
void func_00114E00(void* value);
s32 iWakeupThread(s32 thread_id);
s32 StartThread(s32 thread_id, void* argument);
s32 SleepThread(void);
s32 func_00135320(double left, double right);
s32 func_00115000(void* object, s32 mode, s32 size);
typedef struct ResidentSpeakerAngles
{
    float angles[4];
} ResidentSpeakerAngles;
extern const ResidentSpeakerAngles D_00144260;
typedef struct ConstantByteSetterOwnerresident_0010A0E0
{
    u8 unk00[0x1012];
    u8 unk1012;
} ConstantByteSetterOwnerresident_0010A0E0;





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

typedef struct ResidentByteAndWordResetB730
{
    u8 pad00[0x78];
    u8 unk78[4];
    u32 unk7C;
    u32 unk80;
    u32 unk84;
} ResidentByteAndWordResetB730;

typedef struct ResidentManagerEF50
{
    void* unk00;
    u8 pad04[0x14];
    void* unk18[7];
    u32 unk34;
} ResidentManagerEF50;


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

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_random_below);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_random_range);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_rand);

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

/** @brief Get the resident system. @return g_system. */
ResidentSystem* resident_get_system(void)
{
    return &g_system;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010D8F0);

/**
 * @brief Put the four surround speakers back at their default angles.
 * @param sound Sound system.
 */
void resident_sound_reset_speaker_angles(ResidentSound* sound)
{
    ResidentSpeakerAngles angles = D_00144260;
    sound->speaker_angles[0] = angles.angles[0];
    sound->speaker_angles[1] = angles.angles[1];
    sound->speaker_angles[2] = angles.angles[2];
    sound->speaker_angles[3] = angles.angles[3];
}

/**
 * @brief Set the sound output mode.
 * @param sound Sound system.
 * @param mode Output mode: 1 mono, 0 stereo, 2 Dolby Pro Logic II, 3 headphones.
 */
void resident_sound_set_output_mode(ResidentSound* sound, s32 mode)
{
    sound->output_mode = mode;
    func_00108C40(sound->stream, 0, 0, 0, mode & 0xFF);
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010DAA0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_sound_set_volume_scale);

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

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_sound_get_voice_level);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010E4B0);

/**
 * @brief Set the object positional sounds are heard from.
 * @param sound Sound system.
 * @param listener Listening object.
 * @param value Stored with the listener; its use is unknown.
 * @param range Distance positional sounds reach.
 */
void resident_sound_set_listener(ResidentSound* sound, void* listener, float value, float range)
{
    sound->listener = listener;
    sound->unk1394 = value;
    sound->range_squared = range * range;
}

/**
 * @brief Set the angle of one surround speaker.
 * @param sound Sound system.
 * @param speaker Speaker index, 0 to 3.
 * @param angle Speaker angle in radians.
 */
void resident_sound_set_speaker_angle(ResidentSound* sound, s32 speaker, float angle)
{
    sound->speaker_angles[speaker] = angle;
}

/**
 * @brief Set the angles of all four surround speakers.
 * @param sound Sound system.
 * @param angles Four speaker angles in radians.
 */
void resident_sound_set_speaker_angles(ResidentSound* sound, const float* angles)
{
    sound->speaker_angles[0] = angles[0];
    sound->speaker_angles[1] = angles[1];
    sound->speaker_angles[2] = angles[2];
    sound->speaker_angles[3] = angles[3];
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

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_sound_stop_music);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010F250);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00110340);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001103E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00110480);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00110520);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001105E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001106B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_sound_stop);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_sound_is_active);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00110C60);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00110CE0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00110D80);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00110FB0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00111420);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00111860);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00111A90);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_sound_play_voice);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00111EF0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00112160);


extern void func_0010EE60(void* response, ResidentRequestSlot* slot);
extern s32 func_00108220(void* context, s32 first,
    void (*callback)(void*, ResidentRequestSlot*), ResidentRequestSlot* slot,
    s32 selected, s32 value, s32 arg3, s32 zero, s32 packed);

/** @brief Find a free slot while advancing and wrapping the allocation cursor. @param receiver Request receiver. @return Free slot index, or minus one. */
static inline s32 find_available_request_slot(ResidentSound* receiver)
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
s32 resident_sound_play(ResidentSound* receiver, s32 arg1, s32 arg2,
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
        if (!func_00108220(receiver->stream, 0, func_0010EE60, request,
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


INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_sound_is_music_playing);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_sound_load_bank);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_sound_play_music);

void func_00112D70(void* object, u32 value, void* pointer)
{
    ResidentPairSetter112D70* receiver = (ResidentPairSetter112D70*)object;
    receiver->unk10 = value;
    receiver->unk14 = pointer;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00112D80);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00112E70);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", __dt__13ResidentSoundFv);

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

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", __dt__14ResidentThreadFv);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00115000);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001150C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001151B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00115270);

/**
 * @brief Set the three BB Navigator files the install writes.
 * @param archive Resource archive.
 * @param first First file.
 * @param first_size Size of first.
 * @param second Second file.
 * @param second_size Size of second.
 * @param third Third file.
 * @param third_size Size of third.
 */
void resident_archive_set_navigator_files(ResidentArchive* archive, u8* first, s32 first_size, u8* second, s32 second_size, u8* third,
                                          s32 third_size)
{
    archive->navigator_files[0] = first;
    archive->navigator_file_sizes[0] = first_size;
    archive->navigator_files[1] = second;
    archive->navigator_file_sizes[1] = second_size;
    archive->navigator_files[2] = third;
    archive->navigator_file_sizes[2] = third_size;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_archive_set_system_files);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00115310);

/**
 * @brief Clear the pending hard disk unit error.
 * @param archive Resource archive.
 */
void resident_archive_clear_unit_error(ResidentArchive* archive)
{
    archive->unk140 = 0;
    archive->unk6c = 0;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_archive_has_unit_error);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_archive_query_unit);

/**
 * @brief Get the result of the last worker command.
 * @param archive Resource archive.
 * @return Zero on success, otherwise an error.
 */
s32 resident_archive_get_command_result(const ResidentArchive* archive)
{
    return archive->command_result;
}

/**
 * @brief Report whether a worker command is running.
 * @param archive Resource archive.
 * @return Nonzero while a command runs.
 */
s32 resident_archive_is_busy(const ResidentArchive* archive)
{
    return archive->busy;
}

/**
 * @brief Get the words the install still has to copy.
 * @param archive Resource archive.
 * @return Remaining words.
 */
s32 resident_archive_get_copy_remaining(const ResidentArchive* archive)
{
    return archive->copy_remaining;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_archive_is_unit_ready);

/**
 * @brief Set the buffer the install copies through.
 * @param archive Resource archive.
 * @param buffer Copy buffer, or null once the copy is done.
 */
void resident_archive_set_copy_buffer(ResidentArchive* archive, u8* buffer)
{
    archive->copy_buffer = buffer;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_archive_cancel_command);

/**
 * @brief Queue a command for the hard disk worker.
 * @param archive Resource archive.
 * @param command Worker command.
 * @param argument Command argument.
 */
void resident_archive_start_command(ResidentArchive* archive, s32 command, s32 argument)
{
    func_00118880(archive->unkEC, command, argument);
}

/**
 * @brief Get the free space the last space query found.
 * @param archive Resource archive.
 * @return Free space in bytes.
 */
u32 resident_archive_get_free_space(const ResidentArchive* archive)
{
    return archive->free_space;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_archive_get_install_size);

/**
 * @brief Sum the entries of every resource the install copies.
 * @param archive Resource archive.
 * @return Install size in words.
 */
s32 resident_archive_get_install_words(const ResidentArchive* archive)
{
    u32 total = 0;

    for (s32 i = 0; i < 0x1800; i++)
    {
        if (archive->install_flags[i] != 0)
        {
            total += archive->resource_entries[i];
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

/**
 * @brief Get the size of a resource, in whole 2048-byte blocks.
 * @param archive Resource archive.
 * @param key Resource key.
 * @return Resource size in bytes.
 */
u32 resident_get_resource_size(const ResidentArchive* archive, s32 key)
{
    return (archive->resource_entries[key] & 0x00FFFFFF) << 11;
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

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", __dt__15ResidentArchiveFv);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011D950);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_archive_get_clock);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011DA80);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011DBA0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011DC00);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011DD40);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", __dt__19ResidentClass14FC60Fv);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011DE00);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_input_attach_display);

/**
 * @brief Take the number of vblanks counted since the last call.
 * @param input Input system.
 * @return Vblanks since the last call.
 */
s32 resident_input_take_vblank_count(struct ResidentInputSystem* input)
{
    ResidentWordExchange10* receiver = (ResidentWordExchange10*)input;
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

/**
 * @brief Clear the pressed and held-since-clear latches of a pad.
 * @param input Input system.
 * @param slot Pad slot.
 */
void resident_pad_clear_latched(struct ResidentInputSystem* input, s32 slot)
{
    u16* values = (u16*)input;
    values[slot + 0x134] = 0;
    values[slot + 0x136] = 0;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_pad_get_repeated);

/**
 * @brief Get the buttons newly pressed since the latches were last cleared.
 * @param input Input system.
 * @param slot Pad slot.
 * @return Pressed button bits.
 */
u16 resident_pad_get_pressed(const struct ResidentInputSystem* input, s32 slot)
{
    const u16* values = (const u16*)((const u8*)input + 0x26C);
    return values[slot];
}

/**
 * @brief Get every button held at some point since the latches were last cleared.
 * @param input Input system.
 * @param slot Pad slot.
 * @return Held button bits.
 */
u16 resident_pad_get_held_since_clear(const struct ResidentInputSystem* input, s32 slot)
{
    const u16* values = (const u16*)((const u8*)input + 0x268);
    return values[slot];
}

/**
 * @brief Get the buttons a pad holds this frame.
 * @param input Input system.
 * @param slot Pad slot.
 * @return Held button bits.
 */
u16 resident_pad_get_held(const struct ResidentInputSystem* input, s32 slot)
{
    const u16* values = (const u16*)((const u8*)input + 0x260);
    return values[slot];
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_pad_set_stick_dpad);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_pad_set_vibration_enabled);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_pad_update_vibration);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_pad_set_vibration);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011E290);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_pad_get_sticks);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_input_handle_vblank);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_pad_update);

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
