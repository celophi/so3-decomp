#include "include_asm.h"
#include "overlays/1067-00/text_002D3BD0.h"
#include "overlays/1067-00/text_00202240.h"
#include "boot/resident_data.h"
#include "boot/resident_0010A0E0.h"
#include "overlays/0002-01/text_004CD3A0.h"

struct FieldReset2D4160
{
    u8 unk00[0x3C0];
    s32 unk3C0;
    s32 unk3C4;
    s32 unk3C8;
};

/** Partial receiver with an attached Field object at offset 0x40. */
typedef struct FieldAttached2D47A0
{
    u8 unk00[0x40];
    FieldClass150070* unk40;
} FieldAttached2D47A0;

extern u8 D_30EC10[];
extern "C" s32 func_11EE00(void* queue, void* object);


/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 14.
 */
s32 func_002D3BD0(FieldClass150070* object)
{
    return 14;
}

void func_002D3BE0(FieldClass150070* object)
{
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

void func_002D3C10(void* object)
{
}

s32 func_002D3C20(const FieldBufferSlots* object, s32 index)
{
    return object->unk134[index];
}

void* func_002D3C30(const FieldBufferSlots* object, s32 index)
{
    return object->unk128[index];
}

u8 func_002D3C40(FieldBufferSlots* object, void* allocation, s32 size, s32 index)
{
    if (index < 0)
    {
        return 0;
    }
    if (index > 2)
    {
        return 0;
    }
    if (size <= 0)
    {
        return 0;
    }
    if (object->unk11c[index] != 0)
    {
        return 0;
    }
    FieldBufferSlots* slot = (FieldBufferSlots*)((u8*)object + index * 4);
    slot->unk134[0] = size;
    slot->unk11c[0] = allocation;
    slot->unk128[0] = (void*)(((u32)slot->unk11c[0] + 127) & ~0x7F);
    return 1;
}

FieldResourceRecord* func_002D3CC0(const FieldBufferSlots* object, s32 index)
{
    if (index < 0)
    {
        return 0;
    }
    if (object->unk114 == 0)
    {
        return 0;
    }
    FieldResourceRecord* record = (FieldResourceRecord*)(((u32)object->unk114 + 127) & ~0x7F);
    for (s32 position = 0; ; position++)
    {
        if (position == index)
        {
            return record;
        }
        record = record->next_offset == 0 ? 0 : (FieldResourceRecord*)((u8*)record + record->next_offset);
        if (record == 0)
        {
            break;
        }
    }
    return 0;
}

u8 func_002D3D40(FieldBufferSlots* object, void* allocation, s32 size)
{
    object->unk118 = size;
    if (object->unk118 <= 0)
    {
        return 0;
    }
    if (object->unk114 != 0)
    {
        return 0;
    }
    object->unk114 = allocation;
    return 1;
}

void* func_002D3D80(const FieldBufferSlots* object, u8 index)
{
    if (index >= 64)
    {
        return 0;
    }
    return (void*)(((u32)object->unk14[index] + 127) & ~0x7F);
}

u8 func_002D3DC0(FieldBufferSlots* object, u8 index)
{
    if (index < 0)
    {
        return 0;
    }
    if (index >= 64)
    {
        return 0;
    }
    void* allocation = object->unk14[index];
    if (allocation == 0)
    {
        return 0;
    }
    func_11EE00(D_001B65F4, allocation);
    object->unk14[index] = 0;
    return 1;
}

u8 func_002D3E40(FieldBufferSlots* object, void* allocation, u8 index)
{
    if (allocation == 0)
    {
        return 0;
    }
    if (index < 0)
    {
        return 0;
    }
    if (index >= 64)
    {
        return 0;
    }
    if (object->unk14[index] != 0)
    {
        return 0;
    }
    object->unk14[index] = allocation;
    return 1;
}

void* func_002D3EB0(void* object)
{
    return D_30EC10;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D3EC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D4030);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D4100);

void func_002D4160(FieldReset2D4160* object)
{
    func_00202840(object);
    object->unk3C0 = 0;
    object->unk3C8 = 0;
    object->unk3C4 = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D4190);

void func_002D47A0(void* receiver)
{
    FieldAttached2D47A0* object = (FieldAttached2D47A0*)receiver;
    if (object->unk40 != 0)
    {
        func_004D65C0(object->unk40);
        object->unk40->func_001DD7B0();
        object->unk40 = 0;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D47F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D4930);

void func_002D4A30(FieldLinkedAttached2D4A30* list)
{
    FieldLinkedAttached2D4A30* current = list;
    for (;;)
    {
        current = current->next;
        if (list == current)
        {
            break;
        }
        if (current->unk40 == 0)
        {
            continue;
        }
        func_004D65C0(current->unk40);
        current->unk40->func_001DD7B0();
        current->unk40 = 0;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D4AA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D4B30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D4CA0);

/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 9.
 */
s32 func_002D4D40(FieldClass150070* object)
{
    return 9;
}

void func_002D4D50(FieldClass150070* object)
{
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D4D80);

void func_002D5060(FieldState2D5060* object)
{
    object->unk28 = 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D5070);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D5250);
