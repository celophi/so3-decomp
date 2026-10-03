#include "include_asm.h"
#include "overlays/citemcreation/text_00358440.h"
#include "overlays/citemcreation/text_003483C0.h"
#include "overlays/citemcreation/text_003684D0.h"
#include "overlays/1067-00/text_0023B1D0.h"
#include "overlays/1067-00/text_002D5260.h"

enum
{
    ITEM_CREATION_COLOR_DIM = 0x505050,
    ITEM_CREATION_COLOR_ASSIGNED = 0x1E8CFF,
    ITEM_CREATION_COLOR_BRIGHT = 0x808080,
    ITEM_CREATION_COLOR_SELECTED = 0x288080
};

/** Packed sixteen-byte allocation record checked before displaying its value. */
typedef struct ItemCreationAllocationRecord
{
    union
    {
        u16 raw;
        struct
        {
            u16 value : 10;
            u16 other : 6;
        } bits;
    } unk00;
    u16 unk02;
    u16 unk04;
    u16 unk06;
    u16 unk08;
    u16 unk0a;
    u8 unk0c;
    u8 unk0d_low : 3;
    u8 unk0d_shift : 2;
    u8 unk0d_high : 3;
    u16 unk0e;
} ItemCreationAllocationRecord;

/** Partial panel marker containing its visibility flag. */
struct ItemCreationPanelMarker
{
    u8 unk00[0x3F];
    u8 unk3f;
};

/** Partial resource display containing its active flag and resource byte. */
struct ItemCreationIndexedResourceDisplay
{
    u8 unk00[0x3F];
    u8 unk3f;
    u8 unk40[0x90];
    u8 unkd0;
};

/** Partial resident directory containing the item-resource buffers. */
typedef struct ItemCreationResourceDirectory
{
    struct ItemCreationCheckedRecord* unk00;
    u8 unk04[0x1C];
    FieldBufferSlots* unk20;
} ItemCreationResourceDirectory;

/** Partial record containing a checked value and its checksum fields. */
typedef struct ItemCreationCheckedRecord
{
    u8 unk00[0x34];
    u32 unk34;
    u8 unk38[0x6C];
    u16 unka4;
    u16 unka6;
} ItemCreationCheckedRecord;

/** Partial resident directory containing the current checked record. */
typedef struct ItemCreationRecordDirectory6430
{
    u8 unk00[4];
    ItemCreationCheckedRecord* unk04;
} ItemCreationRecordDirectory6430;

// These external interfaces are scoped here because their owning code is in other overlays.
extern "C"
{
    extern ItemCreationAllocationRecord* D_001B64F8;
    extern ItemCreationResourceDirectory* D_001B643C;
    extern ItemCreationRecordDirectory6430* D_001B6430;
    u16 func_457470(u16 seed, const u8* buffer, s32 length);
    u32 func_23B3B0(FieldState23B3A0* item, u16 flag);
    u16 func_23B3A0(FieldState23B3A0* item);
}

static inline bool valid_record_index(s16 index);
static inline ItemCreationAllocationRecord* allocation_record(s32 value);
static inline bool allocation_invalid(ItemCreationAllocationRecord* record);
static inline u16 allocation_value(ItemCreationAllocationRecord* record);
static inline u32 item_resource_index(u8 value);
static inline u32 item_available_resource_index(u16 value);
static inline u32 item_assigned_code(u8 value);

/**
 * @brief Test whether a signed item index identifies an allocation record.
 * @param index Signed item index.
 * @return True for indices from one through three thousand.
 */
static inline bool valid_record_index(s16 index)
{
    return index > 0 && index <= 3000;
}

/**
 * @brief Find an allocation record using the signed halfword item index.
 * @param value Item index to narrow to a signed halfword.
 * @return Allocation record, or null when the index is outside the table.
 */
static inline ItemCreationAllocationRecord* allocation_record(s32 value)
{
    ItemCreationAllocationRecord* records = D_001B64F8;
    s16 index = value;
    if (valid_record_index(index))
    {
        return &records[index - 1];
    }
    return 0;
}

/**
 * @brief Test the allocation record checksum against its packed halfword values.
 * @param record Allocation record to check.
 * @return True when its checksum differs from the calculated value.
 */
static inline bool allocation_invalid(ItemCreationAllocationRecord* record)
{
    const u16* words = (const u16*)record;
    return record->unk0e != (u16)((0x83CF << record->unk0d_shift) ^
        ((words[4] + (words[0] + words[2])) ^
         (words[1] + (words[3] + words[5]))));
}

/**
 * @brief Read the packed allocation value when the record checksum is valid.
 * @param record Allocation record to read.
 * @return Its ten-bit value, or zero when the checksum is invalid.
 */
static inline u16 allocation_value(ItemCreationAllocationRecord* record)
{
    if (allocation_invalid(record))
    {
        return 0;
    }
    return record->unk00.bits.value;
}

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
 * @brief Convert a halfword resource code to its allocation-table index.
 * @param value Resource code; zero denotes no resource.
 * @return Zero for no resource, or the resource code minus eleven.
 */
static inline u32 item_available_resource_index(u16 value)
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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00358440);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_003587F0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00358850);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00359240);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00359800);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00359860);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_003598E0);

void func_00359C80(ItemCreationTwoCheckedValueOwner* object)
{
    if (object->unkd0 != 0)
    {
        ItemCreationCheckedRecord* record = D_001B6430->unk04;
        const u8* end = (const u8*)&record->unka4;
        u16 checksum = record->unka4;
        ItemCreationValueDisplay* display;
        u32 value;

        if (checksum != (u16)func_457470(record->unka6, ((u8*)record + 0x26),
            end - ((const u8*)record + 0x26)))
        {
            value = 0;
        }
        else
        {
            value = record->unk34 ^ 0x7CE3C7F7;
        }
        display = object->unkd0;
        display->unkfc = value;
        display->unk3c = 1;
    }
    if (object->unkd8 != 0)
    {
        ItemCreationCheckedRecord* record = D_001B6430->unk04;
        const u8* end = (const u8*)&record->unka4;
        u16 checksum = record->unka4;
        ItemCreationValueDisplay* display;
        u32 value;

        if (checksum != (u16)func_457470(record->unka6, ((u8*)record + 0x26),
            end - ((const u8*)record + 0x26)))
        {
            value = 0;
        }
        else
        {
            value = record->unk34 ^ 0x7CE3C7F7;
        }
        display = object->unkd8;
        display->unkfc = value;
        display->unk3c = 1;
    }
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00359D70);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035A5C0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035A620);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035A770);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035AA10);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035AB80);

void func_0035AF70(void* object)
{
}

void func_0035AF80(void* object)
{
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035AF90);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035B310);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035B4E0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035B6E0);

void func_0035C3F0(void* object, u8 value)
{
    *(u8*)((u8*)object + 0x12C) = value;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035C400);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035C440);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035C520);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035C6A0);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035C910);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035CAD0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035CD00);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035D000);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035D0C0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035D1B0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035D6D0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035D7C0);

void func_0035E150(ItemCreationCheckedAllocationView* object, s16 value, s32 quantity, s8 index)
{
    object->unk10c = value;
    if (object->unk10c != 0)
    {
        ItemCreationAllocationRecord* record = allocation_record(object->unk10c);
        u16 decoded = allocation_value(record);
        u8 flag = record->unk0c & 0x7F;
        ItemCreationAllocationDisplay* display = object->unk11c[index];
        display->unkfc = decoded + 1;
        display->unkfe = flag;
        display->unk3c = 1;
        object->unk11c[index]->unk3f = 1;
        if (quantity == -1)
        {
            object->unk140[index]->unk3f = 0;
            object->unk128[index].unk04->unk3f = 0;
        }
        else
        {
            ItemCreationValueDisplay* quantity_display = object->unk140[index];
            quantity_display->unkfc = quantity;
            quantity_display->unk3c = 1;
            object->unk140[index]->unk3f = 1;
            object->unk128[index].unk04->unk3f = 1;
        }
    }
    else
    {
        object->unk11c[index]->unk3f = 0;
        object->unk128[index].unk04->unk3f = 0;
        object->unk140[index]->unk3f = 0;
    }
}

void func_0035E2D0(u8* object)
{
    u8* nested = *(u8**)(object + 0xAC);
    if (nested != 0)
    {
        *(float*)(nested + 0x70) = 128.0f;
        nested[0x3C] = 1;
    }
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035E300);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035E430);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035E510);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035E640);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035E770);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035F0A0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035F100);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035F1C0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035F2D0);

void func_0035F710(ItemCreationTwoColorOwner* object)
{
    if (object->unkcc != 0 && (u8)func_23B3B0(object->unkcc, 1) != 1)
    {
        u16 selected = func_23B3A0(object->unkcc);
        if (object->unkcc != 0)
        {
            s32 index;
            for (index = 0; index < 2; index++)
            {
                ItemCreationColorDisplay* display = object->unkb4[index];
                if (index == selected)
                {
                    display->unk94 = ITEM_CREATION_COLOR_SELECTED;
                    display->unk3c = 1;
                    func_0023B7E0(object->unkd0, (FieldTarget23B850*)display);
                }
                else
                {
                    display->unk94 = ITEM_CREATION_COLOR_BRIGHT;
                    display->unk3c = 1;
                }
            }
        }
    }
}

void func_0035F7F0(ItemCreationTwoColorOwner* object)
{
    if (object->unkcc != 0 && (u8)func_23B3B0(object->unkcc, 0) != 1)
    {
        u16 selected = func_23B3A0(object->unkcc);
        if (object->unkcc != 0)
        {
            s32 index;
            for (index = 0; index < 2; index++)
            {
                ItemCreationColorDisplay* display = object->unkb4[index];
                if (index == selected)
                {
                    display->unk94 = ITEM_CREATION_COLOR_SELECTED;
                    display->unk3c = 1;
                    func_0023B7E0(object->unkd0, (FieldTarget23B850*)display);
                }
                else
                {
                    display->unk94 = ITEM_CREATION_COLOR_BRIGHT;
                    display->unk3c = 1;
                }
            }
        }
    }
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035F8D0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035FBC0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035FC20);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035FCA0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00360020);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_003600E0);

void func_00360440(u8* object)
{
    FieldState23B3A0* item = *(FieldState23B3A0**)(object + 0xD4);
    if (item != 0 && (u8)func_23B3B0(item, 1) != 1)
    {
        u16 value = (u16)func_23B3A0(*(FieldState23B3A0**)(object + 0xD4));
        func_0035FCA0(object, value);
    }
}

void func_003604A0(u8* object)
{
    FieldState23B3A0* item = *(FieldState23B3A0**)(object + 0xD4);
    if (item != 0 && (u8)func_23B3B0(item, 0) != 1)
    {
        u16 value = (u16)func_23B3A0(*(FieldState23B3A0**)(object + 0xD4));
        func_0035FCA0(object, value);
    }
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00360500);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_003607E0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00360840);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_003608C0);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00360FD0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_003610D0);

void func_00361220(ItemCreationNineSlotView* object)
{
    s16 selected;

    if (object->unkb4 != 0)
    {
        selected = object->unkb4->unk114;
        for (s32 index = 0; index < 9; index++)
        {
            object->unkb8[index]->unk3f = 0;
        }
        for (s32 index = 0; index < 12; index++)
        {
            object->unkdc[index]->unk3f = 0;
            object->unk10c[index]->unk3f = 0;
        }
        if (object->unka8->unk57 != 0 && object->unkb4->unkAD != 0)
        {
            switch (selected)
            {
            case 0:
                object->unkb8[0]->unk3f = 1;
                break;
            case 1:
                object->unkb8[1]->unk3f = 1;
                break;
            case 2:
                object->unkb8[2]->unk3f = 1;
                break;
            case 3:
                object->unkdc[0]->unk3f = 1;
                object->unkdc[1]->unk3f = 1;
                object->unkdc[2]->unk3f = 1;
                object->unkdc[3]->unk3f = 1;
                break;
            case 4:
                object->unk10c[0]->unk3f = 1;
                object->unk10c[1]->unk3f = 1;
                object->unk10c[2]->unk3f = 1;
                object->unk10c[3]->unk3f = 1;
                break;
            case 5:
                object->unkb8[3]->unk3f = 1;
                break;
            case 6:
                object->unkb8[4]->unk3f = 1;
                break;
            case 7:
                object->unkb8[5]->unk3f = 1;
                break;
            case 8:
                object->unkdc[4]->unk3f = 1;
                object->unkdc[5]->unk3f = 1;
                object->unkdc[6]->unk3f = 1;
                object->unkdc[7]->unk3f = 1;
                break;
            case 9:
                object->unk10c[4]->unk3f = 1;
                object->unk10c[5]->unk3f = 1;
                object->unk10c[6]->unk3f = 1;
                object->unk10c[7]->unk3f = 1;
                break;
            case 10:
                object->unkb8[6]->unk3f = 1;
                break;
            case 11:
                object->unkb8[7]->unk3f = 1;
                break;
            case 12:
                object->unkb8[8]->unk3f = 1;
                break;
            case 13:
                object->unkdc[8]->unk3f = 1;
                object->unkdc[9]->unk3f = 1;
                object->unkdc[10]->unk3f = 1;
                object->unkdc[11]->unk3f = 1;
                break;
            case 14:
                object->unk10c[8]->unk3f = 1;
                object->unk10c[9]->unk3f = 1;
                object->unk10c[10]->unk3f = 1;
                object->unk10c[11]->unk3f = 1;
                break;
            }
        }
    }
}

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_003615C0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_003619D0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00361AB0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00361D40);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00362460);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_003625E0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00362760);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00362990);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00362AE0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00362B10);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00362B40);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00362B70);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00362BA0);

void func_00363D20(ItemCreationNineSlotView* object)
{
    s32 index;
    object->unk1f1 = object->unka8->unk57;
    for (index = 0; index < 3; index++)
    {
        if (index < object->unk1f1)
        {
            ItemCreationColorDisplay* display1;
            ItemCreationColorDisplay* display2;
            ItemCreationColorDisplay* display3;
            ItemCreationColorDisplay* display4;
            object->unk194[index]->unk3f = 1;
            object->unk1a0[index]->unk3f = 1;
            object->unk1ac[index]->unk3f = 1;
            display1 = object->unk1b8[index];
            display1->unk94 = ITEM_CREATION_COLOR_ASSIGNED;
            display1->unk3c = 1;
            display2 = object->unk1c4[index];
            display2->unk94 = ITEM_CREATION_COLOR_ASSIGNED;
            display2->unk3c = 1;
            display3 = object->unk1d0[index];
            display3->unk94 = ITEM_CREATION_COLOR_ASSIGNED;
            display3->unk3c = 1;
            display4 = object->unk1dc[index];
            display4->unk94 = ITEM_CREATION_COLOR_ASSIGNED;
            display4->unk3c = 1;
        }
        else
        {
            ItemCreationColorDisplay* display1;
            ItemCreationColorDisplay* display2;
            ItemCreationColorDisplay* display3;
            ItemCreationColorDisplay* display4;
            object->unk194[index]->unk3f = 0;
            object->unk1a0[index]->unk3f = 0;
            object->unk1ac[index]->unk3f = 0;
            display1 = object->unk1b8[index];
            display1->unk94 = ITEM_CREATION_COLOR_DIM;
            display1->unk3c = 1;
            display2 = object->unk1c4[index];
            display2->unk94 = ITEM_CREATION_COLOR_DIM;
            display2->unk3c = 1;
            display3 = object->unk1d0[index];
            display3->unk94 = ITEM_CREATION_COLOR_DIM;
            display3->unk3c = 1;
            display4 = object->unk1dc[index];
            display4->unk94 = ITEM_CREATION_COLOR_DIM;
            display4->unk3c = 1;
        }
    }
    func_0023CE80((FieldObject23CE80*)object->unkac, 5, object->unk1f1);
    func_0023CE80((FieldObject23CE80*)object->unkb0, 5, object->unk1f1);
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00363E40);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00363F10);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00364200);

u8 func_003644F0(ItemCreationFourteenSlotView* object)
{
    ItemCreationSelectedDisplayState* state = object->unka8;
    FieldObject23CEA0* display;
    u16 index;
    bool inactive;
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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00364610);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_003646D0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_003647A0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00364870);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00364A40);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00364C60);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00364C90);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00364CC0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00364CF0);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00364E00);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00364F50);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00365560);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00365600);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00365A50);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00365AC0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00365B30);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00365BF0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00365F20);

u32 func_00366040(void* object)
{
    return *(u32*)((u8*)object + 0x24);
}

void func_00366050(ItemCreationPanelView* object)
{
    if (object->unka8 != 0)
    {
        if (object->unkd8 != 0)
        {
            for (s32 index = 0; index < object->unkd8; index++)
            {
                ItemCreationPanelMarker* display = object->unke8[index];
                if (display != 0)
                {
                    if (index != object->unk10c)
                    {
                        ItemCreationListNode* node = (ItemCreationListNode*)func_0036F160((u8*)&object->unk38, index);
                        ItemCreationPanelMarker* other = (ItemCreationPanelMarker*)node->unk00;
                        if (other != 0)
                        {
                            if (object->unka8->unk4e[object->unkd0[index] - 1] == 0)
                            {
                                display->unk3f = 0;
                                other->unk3f = 1;
                            }
                            else
                            {
                                display->unk3f = 1;
                                other->unk3f = 0;
                            }
                        }
                    }
                    else
                    {
                        object->unk10d = object->unka8->unk57;
                        if (object->unk10d < 3)
                        {
                            ItemCreationValueDisplay* valueDisplay = object->unk120;
                            valueDisplay->unkfc = object->unk110[object->unk10d];
                            valueDisplay->unk3c = 1;
                        }
                        else
                        {
                            display->unk3f = 1;
                            if (object->unk120 != 0)
                            {
                                object->unk120->unk3f = 0;
                            }
                        }
                    }
                }
            }
            if (object->unke4 != 0)
            {
                ItemCreationCheckedRecord* record = D_001B643C->unk00;
                const u8* end = (const u8*)&record->unka4;
                u16 checksum = record->unka4;
                ItemCreationValueDisplay* display;
                u32 value;
                if (checksum != (u16)func_457470(record->unka6, ((u8*)record + 0x26),
                    end - ((const u8*)record + 0x26)))
                {
                    value = 0;
                }
                else
                {
                    value = record->unk34 ^ 0x7CE3C7F7;
                }
                display = object->unke4;
                display->unkfc = value;
                display->unk3c = 1;
            }
        }
    }
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_003661F0);

void func_00366CB0(ItemCreationCheckedValueOwner* object)
{
    if (object->unke4 != 0)
    {
        ItemCreationCheckedRecord* record = D_001B6430->unk04;
        const u8* end = (const u8*)&record->unka4;
        u16 checksum = record->unka4;
        ItemCreationValueDisplay* display;
        u32 value;

        if (checksum != (u16)func_457470(record->unka6, ((u8*)record + 0x26),
            end - ((const u8*)record + 0x26)))
        {
            value = 0;
        }
        else
        {
            value = record->unk34 ^ 0x7CE3C7F7;
        }
        display = object->unke4;
        display->unkfc = value;
        display->unk3c = 1;
    }
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00366D40);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00366E10);

void func_00366F10(ItemCreationAvailableResourceView* object)
{
    u16 resource;
    if (object->unk120 != 0)
    {
        if (object->unk120->unk48 != 0)
        {
            for (s32 index = 0; index < 9; index++)
            {
                ItemCreationIndexedResourceDisplay* display = object->unka8[index];
                if (display != 0)
                {
                    display->unk3f = 0;
                }
            }
            for (s32 index = 0; index < 14; index++)
            {
                ItemCreationIndexedResourceDisplay* display = object->unkcc[index];
                if (display != 0)
                {
                    display->unk3f = 0;
                }
            }
            object->unk124 = object->unk120->unk4d + 1;
            if (object->unk124 != 0)
            {
                s32 slot = 0;
                for (s32 index = 0; index < 14; index++)
                {
                    u8 value = object->unk120->unk5a[(u16)index];
                    if (value != 0)
                    {
                        resource = item_available_resource_index(value);
                        void* allocation = func_002D3D80(D_001B643C->unk20, resource);
                        FieldResourceRecord* record = func_002D3CC0(D_001B643C->unk20, 0x51);
                        object->unkcc[slot]->unkd0 = resource;
                        func_002D5CF0((FieldResourceDisplay2D5CF0*)object->unkcc[slot], allocation, record, 0);
                        object->unkcc[slot]->unk3f = 1;
                        slot++;
                    }
                }
                for (s32 index = 0; index < 9; index++)
                {
                    u8 value = object->unk120->unk68[(u16)index];
                    if (value != 0)
                    {
                        resource = item_available_resource_index(value);
                        void* allocation = func_002D3D80(D_001B643C->unk20, resource);
                        FieldResourceRecord* record = func_002D3CC0(D_001B643C->unk20, 0x51);
                        object->unka8[index]->unkd0 = resource;
                        func_002D5CF0((FieldResourceDisplay2D5CF0*)object->unka8[index], allocation, record, 0);
                        object->unka8[index]->unk3f = 1;
                    }
                }
            }
        }
    }
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00367100);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00367BD0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00367CA0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00367D80);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_003680F0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00368150);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00368310);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00368370);
