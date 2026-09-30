#include "include_asm.h"
#include "overlays/1067-00/text_002D3BD0.h"


INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D3BD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D3BE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D3C10);

s32 func_002D3C20(const FieldBufferSlots* object, s32 index)
{
    return object->unk134[index];
}

void* func_002D3C30(const FieldBufferSlots* object, s32 index)
{
    return object->unk128[index];
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D3C40);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D3DC0);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D3EB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D3EC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D4030);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D4100);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D4160);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D4190);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D47A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D47F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D4930);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D4A30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D4AA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D4B30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D4CA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D4D40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D4D50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D4D80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D5060);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D5070);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D5250);
