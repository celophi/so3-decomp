#include "include_asm.h"
#include "overlays/0075-00/text_00358440.h"
#include "overlays/0075-00/text_003483C0.h"
#include "overlays/0075-00/text_003684D0.h"
#include "overlays/1067-00/text_0023B1D0.h"
#include "overlays/1067-00/text_002D5260.h"

/** Partial resident directory containing the item-resource buffers. */
typedef struct ItemCreationResourceDirectory
{
    u8 unk00[0x20];
    FieldBufferSlots* unk20;
} ItemCreationResourceDirectory;

extern ItemCreationResourceDirectory* D_001B643C;

/**
 * @brief Convert an item byte to its allocation-table index.
 * @param value Item byte; zero denotes no item.
 * @return Zero for no item, or the item byte minus eleven.
 */
static inline u32 item_resource_index(u8 value)
{
    if (value == 0)
    {
        return 0;
    }
    return value - 11;
}

/**
 * @brief Convert an item byte to its assigned-item code.
 * @param value Item byte; zero denotes no item.
 * @return Zero for no item, or the item byte minus thirty-one.
 */
static inline u32 item_assigned_code(u8 value)
{
    if (value == 0)
    {
        return 0;
    }
    return value - 31;
}

extern u32 func_23B3B0(void* item, u32 flag);
extern u32 func_23B3A0(void* item);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00358440);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_003587F0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00358850);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00359240);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00359800);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00359860);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_003598E0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00359C80);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00359D70);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035A5C0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035A620);

void func_0035A6A0(ItemCreationPairOwner* object, u32 value, u32 alternate)
{
    s32 index;
    ItemCreationNested* nested;

    for (index = 0; index < 6; index++)
    {
        object->unk138[index]->unk3f = value;
        object->unk150[index]->unk3f = value;
    }
    nested = object->unk18c;
    if (nested != 0)
    {
        nested->unk3f = 1;
    }
    nested = object->unkac;
    if (nested != 0)
    {
        nested->unk3f = alternate;
        if (alternate != 0)
        {
            nested = object->unkac;
            nested->unk70 = 128.0f;
            nested->unk3c = 1;
        }
        else
        {
            nested = object->unkac;
            nested->unk70 = 64.0f;
            nested->unk3c = 1;
        }
    }
    nested = object->unka8;
    if (nested != 0)
    {
        nested->unk3f = alternate;
    }
}

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035A770);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035AA10);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035AB80);

void func_0035AF70(void* object)
{
}

void func_0035AF80(void* object)
{
}

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035AF90);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035B310);

void func_0035B480(u8* object, float start)
{
    s32 index;
    float value = start + 16.0f;
    index = 0;
    do
    {
        u8* first;
        u8* second;
        first = *(u8**)(object + 0x138);
        *(float*)(first + 0x1C) = value;
        first[0x3C] = 1;
        second = *(u8**)(object + 0x150);
        *(float*)(second + 0x1C) = value;
        second[0x3C] = 1;
        object += 4;
        value += 28.0f;
        index++;
    } while (index < 6);
}

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035B4E0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035B6E0);

void func_0035C3F0(void* object, u8 value)
{
    *(u8*)((u8*)object + 0x12C) = value;
}

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035C400);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035C440);

void func_0035C4D0(u8* object, void* unused, u32 value)
{
    u8* nested = *(u8**)(object + 0xAC);
    if (nested != 0)
    {
        nested[0x3F] = value;
        if (value != 0)
        {
            nested = *(u8**)(object + 0xAC);
            *(float*)(nested + 0x70) = 128.0f;
            nested[0x3C] = 1;
        }
        else
        {
            nested = *(u8**)(object + 0xAC);
            *(float*)(nested + 0x70) = 64.0f;
            nested[0x3C] = 1;
        }
    }
}

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035C520);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035C6A0);

void func_0035C890(u8* object, float start)
{
    s32 index;
    float value = start + 16.0f;
    index = 0;
    do
    {
        u8* first;
        u8* second;
        u8* third;
        first = *(u8**)(object + 0xF0);
        *(float*)(first + 0x18) = 24.0f;
        *(float*)(first + 0x1C) = value;
        first[0x3C] = 1;
        second = *(u8**)(object + 0x138);
        *(float*)(second + 0x18) = 326.0f;
        *(float*)(second + 0x1C) = value;
        second[0x3C] = 1;
        third = *(u8**)(object + 0x168);
        *(float*)(third + 0x18) = 334.0f;
        *(float*)(third + 0x1C) = value;
        third[0x3C] = 1;
        object += 4;
        value += 28.0f;
        index++;
    } while (index < 12);
}

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035C910);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035CAD0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035CD00);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035D000);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035D0C0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035D1B0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035D6D0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035D7C0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035E150);

void func_0035E2D0(u8* object)
{
    u8* nested = *(u8**)(object + 0xAC);
    if (nested != 0)
    {
        *(float*)(nested + 0x70) = 128.0f;
        nested[0x3C] = 1;
    }
}

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035E300);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035E430);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035E510);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035E640);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035E770);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035F0A0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035F100);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035F1C0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035F2D0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035F710);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035F7F0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035F8D0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035FBC0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035FC20);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_0035FCA0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00360020);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_003600E0);

void func_00360440(u8* object)
{
    void* item = *(void**)(object + 0xD4);
    if (item != 0 && (u8)func_23B3B0(item, 1) != 1)
    {
        u16 value = (u16)func_23B3A0(*(void**)(object + 0xD4));
        func_0035FCA0(object, value);
    }
}

void func_003604A0(u8* object)
{
    void* item = *(void**)(object + 0xD4);
    if (item != 0 && (u8)func_23B3B0(item, 0) != 1)
    {
        u16 value = (u16)func_23B3A0(*(void**)(object + 0xD4));
        func_0035FCA0(object, value);
    }
}

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00360500);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_003607E0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00360840);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_003608C0);

void func_00360E60(ItemCreationNineSlotView* object, u16 mode)
{
    s32 index;

    switch (mode)
    {
    case 1:
        if (object->unkb4 != 0)
        {
            func_0023CEA0(object->unkb4, 1);
        }
        func_00361220(object);
        break;
    case 0:
        if (object->unka8->unk128 != 1)
        {
            if (object->unkac != 0)
            {
                func_0023CEA0(object->unkac, 0);
            }
            if (object->unkb0 != 0)
            {
                func_0023CEA0(object->unkb0, 0);
            }
        }
        else
        {
            if (object->unkb4 != 0)
            {
                func_0023CEA0(object->unkb4, 0);
            }
        }
        for (index = 0; index < 9; index++)
        {
            object->unkb8[index]->unk3f = 0;
        }
        for (index = 0; index < 12; index++)
        {
            object->unkdc[index]->unk3f = 0;
            object->unk10c[index]->unk3f = 0;
        }
        break;
    }
}

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00360FD0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_003610D0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00361220);

void func_003614B0(ItemCreationNineSlotView* object)
{
    void* allocation;
    u32 resource;
    s32 index;
    u32 value;
    FieldResourceRecord* record;

    object->unk190 = 0;
    for (index = 0; index < 9; index++)
    {
        value = object->unka8->unk68[(u16)index];
        if (value != 0)
        {
            resource = (u8)item_resource_index(value);
            allocation = func_002D3D80(D_001B643C->unk20, resource);
            record = func_002D3CC0(D_001B643C->unk20, 0x51);
            func_002D5CF0(object->unk13c[index], allocation, record, resource);
            object->unk13c[index]->unk3F = 1;
            object->unk190++;
            object->unk1f2[index] = item_assigned_code(value);
        }
        else
        {
            object->unk13c[index]->unk3F = 0;
            object->unk1f2[index] = 0;
        }
    }
}

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_003615C0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_003619D0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00361AB0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00361D40);

u8 func_003623C0(ItemCreationTripleState* object, u8 index)
{
    u8 present;
    u8 first = 0;
    u8 second = 0;
    u8 third = 0;
    switch (index)
    {
    case 0:
        first = object->unk1f2[0][0];
        second = object->unk1f2[0][1];
        third = object->unk1f2[0][2];
        break;
    case 1:
        first = object->unk1f2[1][0];
        second = object->unk1f2[1][1];
        third = object->unk1f2[1][2];
        break;
    case 2:
        first = object->unk1f2[2][0];
        second = object->unk1f2[2][1];
        third = object->unk1f2[2][2];
        break;
    }
    if (first == 0 && second == 0 && third == 0)
    {
        present = 0;
    }
    else
    {
        present = 1;
    }
    return present;
}

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00362460);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_003625E0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00362760);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00362990);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00362AE0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00362B10);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00362B40);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00362B70);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00362BA0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00363D20);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00363E40);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00363F10);

void func_00364090(ItemCreationFourteenSlotView* object, u16 mode)
{
    s32 index;
    s32 selected;

    switch (mode)
    {
    case 1:
        if (object->unkb4 != 0)
        {
            func_0023CEA0(object->unkb4, 1);
        }
        if (object->unkb4 != 0)
        {
            selected = object->unkb4->unk114;
            for (index = 0; index < 14; index++)
            {
                if (selected == index)
                {
                    object->unkb8[index]->unk3f = 1;
                }
                else
                {
                    object->unkb8[index]->unk3f = 0;
                }
            }
        }
        break;
    case 0:
        if (object->unka8->unk128 != 1)
        {
            if (object->unkac != 0)
            {
                func_0023CEA0(object->unkac, 0);
            }
            if (object->unkb0 != 0)
            {
                func_0023CEA0(object->unkb0, 0);
            }
        }
        else
        {
            if (object->unkb4 != 0)
            {
                func_0023CEA0(object->unkb4, 0);
            }
        }
        for (index = 0; index < 14; index++)
        {
            object->unkb8[index]->unk3f = 0;
        }
        break;
    }
}

void func_003641F0(void* object)
{
}

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00364200);

u8 func_003644F0(ItemCreationFourteenSlotView* object)
{
    ItemCreationSelectedDisplayState* state = object->unka8;
    FieldObject23CEA0* display;
    u16 index;
    s32 inactive;
    const float* position;
    if (state == 0)
    {
        return 0;
    }
    display = object->unkb4;
    if (display == 0)
    {
        return 0;
    }
    inactive = !display->unkE5;
    if (inactive)
    {
        return 0;
    }
    if (state->unk47 != 1)
    {
        return 0;
    }
    index = display->unk114;
    position = &display->unkC0;
    func_0036A050(state, object, (s16)index);
    if (object->unka8->unk128 == 1)
    {
        FieldObject23CEA0* restore = object->unkac;
        FieldObject23CEA0* target;
        float x;
        float y;
        restore->unkE0 = 96.0f;
        restore->unkAE = 1;
        x = position[0];
        y = position[1];
        target = object->unkb0;
        target->unkC0 = x;
        target->unkC4 = y;
        target->unkE5 = 1;
        target->unkAE = 1;
        func_0023CEA0(object->unkb0, 1);
        target = object->unkb0;
        target->index = (s16)index;
        func_0023CB30(target);
        func_0023C7B0(object->unkb0);
        object->unkb4 = object->unkb0;
    }
    return 1;
}

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00364610);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_003646D0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_003647A0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00364870);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00364A40);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00364C60);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00364C90);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00364CC0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00364CF0);

void func_00364D20(ItemCreationFourteenSlotView* object)
{
    void* allocation;
    s32 index;
    u32 value;
    u32 resource;
    FieldResourceRecord* record;

    for (index = 0; index < 14; index++)
    {
        value = object->unka8->unk5a[(u16)index];
        if (value != 0)
        {
            resource = (u8)item_resource_index(value);
            allocation = func_002D3D80(D_001B643C->unk20, resource);
            record = func_002D3CC0(D_001B643C->unk20, 0x51);
            func_002D5CF0(object->unkf0[index], allocation, record, resource);
            object->unkf0[index]->unk3F = 1;
        }
        else
        {
            object->unkf0[index]->unk3F = 0;
        }
    }
}

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00364E00);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00364F50);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00365560);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00365600);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00365A50);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00365AC0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00365B30);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00365BF0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00365F20);

u32 func_00366040(void* object)
{
    return *(u32*)((u8*)object + 0x24);
}

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00366050);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_003661F0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00366CB0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00366D40);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00366E10);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00366F10);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00367100);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00367BD0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00367CA0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00367D80);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_003680F0);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00368150);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00368310);

INCLUDE_ASM("build/overlays/0075-00/asm/nonmatchings/text_00358440", func_00368370);
