#include "include_asm.h"
#include "overlays/lib/text_004095C0.h"
#include "overlays/lib/text_0045AD10.h"
#include "main/resident_data.h"
#include "overlays/lib/item_allocation.h"

typedef struct HalfwordSetterOwnertext_004095C0
{
    u8 unk00[0x2];
    u16 unk02;
    u8 unk04[0x2C];
    u16 unk30;
} HalfwordSetterOwnertext_004095C0;



typedef struct ByteSetterOwnertext_004095C0
{
    u8 unk00[0x6];
    u8 unk06;
    u8 unk07[0x1];
    u8 unk08;
    u8 unk09;
    u8 unk0a[0x28];
    u8 unk32;
    u8 unk33;
    u8 unk34[0x8A0];
    u8 unk8d4;
    u8 unk8d5[0x35];
    u8 unk90a;
} ByteSetterOwnertext_004095C0;



typedef struct WordSetterOwnertext_004095C0
{
    u32 unk00;
} WordSetterOwnertext_004095C0;


extern "C" ResidentObject1B64F8* D_001B64F8;

/** Opaque 0x50-byte runtime resource slot. */
typedef struct LibCodeResourceSlot
{
    u8 bytes[0x50];
} LibCodeResourceSlot;
/** Partial sixteen-slot runtime table and code-resource selectors. */
typedef struct LibRuntimeCodeResources
{
    u8 pad00[0x14];
    LibCodeResourceSlot slots[16];
    s32 item_slot;
    u8 pad518[4];
    s32 factor_slot;
} LibRuntimeCodeResources;
/** Partial code-widget state and inherited initialization flag. */
typedef struct LibCodeWidgetState
{
    u8 pad00[0x39];
    u8 initialized;
    u8 pad3a[0x32];
    LibCodeResourceSlot* source;
    u8 pad70[0x88];
    u8 flag;
    u8 padf9[3];
    u16 code;
    u8 variation;
} LibCodeWidgetState;
extern "C" void func_00464870(void* object, float x, float y, float width, float height);
extern "C" s32 func_00464900(void* object, s32 first, s32 capacity, s32 second, s32 third);

/** Packed allocation view with the four-bit equipped owner spanning bytes C and D. */
typedef struct LibAllocationEquipmentView
{
    u8 unk00[12];
    u16 modification_number : 7;
    u16 equipped_owner : 4;
    u16 unk0d_high : 5;
    u16 checksum;
} LibAllocationEquipmentView;

/** Previous and next one-based allocation IDs in a resident category list. */
typedef struct LibInventoryAllocationLinks
{
    s16 previous;
    s16 next;
} LibInventoryAllocationLinks;

/** Resident allocation records, intrusive links and twelve-byte category entries. */
typedef struct LibInventoryAllocationLists
{
    LibAllocationEquipmentView allocations[3000];
    LibInventoryAllocationLinks links[3000];
    ItemCreationCategoryRecord item_types[750];
} LibInventoryAllocationLists;

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004095C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00409A10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00409DA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040A370);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040A520);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040A5C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040A970);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040A9B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040A9F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040AE00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040AF10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040AF80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040AFA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040B1F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040B250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040B2F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040B330);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040B360);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040B3A0);

/** Store the byte at receiver offset 0x33. */
void func_0040B640(void* object, u8 value)
{
    ByteSetterOwnertext_004095C0* receiver = static_cast<ByteSetterOwnertext_004095C0*>(object);
    receiver->unk33 = value;
}

/** Store the low halfword at receiver offset 0x30. */
void func_0040B650(void* object, u32 value)
{
    HalfwordSetterOwnertext_004095C0* receiver = static_cast<HalfwordSetterOwnertext_004095C0*>(object);
    receiver->unk30 = value;
}

/** Store the byte at receiver offset 0x32. */
void func_0040B660(void* object, u8 value)
{
    ByteSetterOwnertext_004095C0* receiver = static_cast<ByteSetterOwnertext_004095C0*>(object);
    receiver->unk32 = value;
}

/** Store the byte at receiver offset 0x8. */
void func_0040B670(void* object, u8 value)
{
    ByteSetterOwnertext_004095C0* receiver = static_cast<ByteSetterOwnertext_004095C0*>(object);
    receiver->unk08 = value;
}

/** Store the byte at receiver offset 0x9. */
void func_0040B680(void* object, u8 value)
{
    ByteSetterOwnertext_004095C0* receiver = static_cast<ByteSetterOwnertext_004095C0*>(object);
    receiver->unk09 = value;
}

/** Store the word at receiver offset 0x0. */
void func_0040B690(void* object, u32 value)
{
    WordSetterOwnertext_004095C0* receiver = static_cast<WordSetterOwnertext_004095C0*>(object);
    receiver->unk00 = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040B6A0);

/** Store the byte at receiver offset 0x6. */
void func_0040B6B0(void* object, u8 value)
{
    ByteSetterOwnertext_004095C0* receiver = static_cast<ByteSetterOwnertext_004095C0*>(object);
    receiver->unk06 = value;
}

/** Store the low halfword at receiver offset 0x2. */
void func_0040B6C0(void* object, u32 value)
{
    HalfwordSetterOwnertext_004095C0* receiver = static_cast<HalfwordSetterOwnertext_004095C0*>(object);
    receiver->unk02 = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040B6D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040B760);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040B7E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040B840);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040BB00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040BF50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040C180);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040C300);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040C4C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040C690);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040C7E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040C8F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040C9F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040CC70);

/**
 * @brief Collect a category's allocations that have no equipped owner.
 * @param state Resident allocation records, category links and category entries.
 * @param records Output array receiving unequipped allocation pointers.
 * @param category One-based category ID from one through seven hundred fifty.
 * @return Number of allocations collected, or zero for an invalid or empty category.
 */
s32 lib_collect_unequipped_allocations(const void* state, ItemCreationAllocationRecord** records, u16 category)
{
    const LibInventoryAllocationLists* inventory = (const LibInventoryAllocationLists*)state;
    bool valid = false;
    s32 category_index = category;
    if (category > 0 && category < 751)
    {
        valid = true;
    }
    s32 count;
    s32 identifier;
    if (!valid)
    {
        return 0;
    }
    category_index--;
    const ItemCreationCategoryRecord* category_record = (const ItemCreationCategoryRecord*)((const u8*)inventory +
        category_index * sizeof(ItemCreationCategoryRecord) + sizeof(inventory->allocations) + sizeof(inventory->links));
    identifier = category_record->allocation_list_head;
    count = 0;
    while (identifier != 0)
    {
        const LibAllocationEquipmentView* allocation;
        s32 index = (s16)identifier - 1;
        allocation = &inventory->allocations[index];
        u8 equipped_owner = allocation->equipped_owner;
        if (equipped_owner == 0)
        {
            *records++ = (ItemCreationAllocationRecord*)allocation;
            count++;
        }
        identifier = inventory->links[index].next;
    }
    return count;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040D050);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040D1E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040D260);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040D2E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040D680);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040D760);

/**
 * @brief Return a resident allocation ID unless a validated record suppresses it.
 * @param record Packed allocation record in the resident table.
 * @return One-based allocation ID, or zero when a valid record suppresses its ID.
 */
extern "C" s16 lib_allocation_get_identifier(const ItemCreationAllocationRecord* record)
{
    u32 suppress;
    s32 id;
    if (record->invalid())
    {
        suppress = 0;
    }
    else
    {
        suppress = record->factors_234.bits.suppress_allocation_id;
    }
    if (suppress)
    {
        id = 0;
    }
    else
    {
        id = (s16)(((u32)record - (u32)D_001B64F8) / sizeof(ItemCreationAllocationRecord) + 1);
    }
    return id;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040D930);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040DD20);

s32 func_0040E3A0(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040E3B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040E7F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040E930);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040EC10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040EE30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040F020);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040F0B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040F110);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040F210);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040F2E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040F3E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040F4F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040F740);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040F940);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040FAE0);

/** Store the byte at receiver offset 0x8D4. */
void func_0040FAF0(void* object, u8 value)
{
    ByteSetterOwnertext_004095C0* receiver = static_cast<ByteSetterOwnertext_004095C0*>(object);
    receiver->unk8d4 = value;
}

/** Store the byte at receiver offset 0x90A. */
void func_0040FB00(void* object, u8 value)
{
    ByteSetterOwnertext_004095C0* receiver = static_cast<ByteSetterOwnertext_004095C0*>(object);
    receiver->unk90a = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040FB10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00410FE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00411050);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004110C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00411250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00411420);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00411620);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00411760);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00411830);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00411BC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00411C40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00411CC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00411D50);

extern "C" void* func_00411DD0(void* object, s32 count)
{
    void* node;
    s32 traversed;
    node = *(void**)(*(u8**)object + 4);
    traversed = 0;
    while (traversed < count)
    {
        if (node == 0)
        {
            return 0;
        }
        node = *(void**)((u8*)node + 4);
        traversed += 1;
    }
    return node;
}

void func_00411E10(void* object)
{
}

void func_00411E20(void* object)
{
}

extern "C" void func_00411E30(void* object)
{
    u8* bytes = (u8*)object;
    bytes[0x60] = bytes[0xA8];
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00411E40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00412110);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00412150);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004121F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004122C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00412360);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004127E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00412930);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00412B10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00412BA0);

void func_00412C00(void* object)
{
}

void func_00412C10(void* object)
{
}

void func_00412C20(void* object)
{
}

/**
 * @brief Return the floating-point value 0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_00412C30(void* object)
{
    return 0.0f;
}

void func_00412C40(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00412C50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00412D50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00412DC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00412E30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00412EC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00412F30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00412FA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00412FB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00412FC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00412FD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00412FE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00412FF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00413000);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00413010);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00413020);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00413460);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004135D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00413750);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004138E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00413BB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00413C00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00413CC0);

void LibClass178600::func_00413D20()
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00413D30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00413D90);

/**
 * @brief Initialize the item code widget's rectangle and drawing storage.
 * @param object Item code widget.
 * @param x Rectangle origin x.
 * @param y Rectangle origin y.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @param code Initial item code.
 * @param variation Code variation.
 * @param flag Drawing state flag.
 * @return One on successful initialization, otherwise zero.
 */
s32 lib_item_code_init_rectangle(LibObject172410* object, float x, float y, float width, float height, u16 code, u8 variation, u8 flag)
{
    LibCodeWidgetState* state = (LibCodeWidgetState*)object;
    LibRuntimeCodeResources* resources;
    state->flag = flag;
    func_00464870(object, x, y, width, height);
    resources = (LibRuntimeCodeResources*)D_001B657C;
    state->source = &resources->slots[resources->item_slot];
    if (!func_00464900(object, 0, 64, 0, 0))
    {
        return 0;
    }
    state->code = code;
    state->variation = variation;
    state->initialized = 1;
    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00414010);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00414130);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00414280);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004142E0);

/**
 * @brief Initialize the detail code widget's rectangle and drawing storage.
 * @param object Detail code widget.
 * @param code Initial detail code.
 * @param variation Code variation.
 * @param flag Drawing state flag.
 * @param x Rectangle origin x.
 * @param y Rectangle origin y.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return One on successful initialization, otherwise zero.
 */
s32 lib_detail_code_init_rectangle(LibObject172440* object, u16 code, u8 variation, u8 flag, float x, float y, float width, float height)
{
    LibCodeWidgetState* state = (LibCodeWidgetState*)object;
    LibRuntimeCodeResources* resources;
    state->flag = flag;
    func_00464870(object, x, y, width, height);
    resources = (LibRuntimeCodeResources*)D_001B657C;
    state->source = &resources->slots[resources->factor_slot];
    if (!func_00464900(object, 0, 128, 0, 0))
    {
        return 0;
    }
    state->code = code;
    state->variation = variation;
    state->initialized = 1;
    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00414490);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004144F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004149B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00414AC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00414BD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00414C00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00414C60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00414CE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00414D30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00414DB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00414FB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00414FF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00415010);

s32 func_00415030(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00415040);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004151F0);

s32 func_004152B0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004152C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004159E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00415A70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00415D30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00415E70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00415F20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004161C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00416200);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00416230);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004162F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00416450);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004164B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00416510);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004165E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004166F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00416980);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00416BC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00416D60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004173F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00417460);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00417740);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00417D30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00417E50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00418020);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00418240);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00418390);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00418460);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004184D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00418540);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004190C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00419110);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004191A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00419290);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00419330);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004193E0);

s32 func_004194F0(void* object)
{
    return 12;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00419500);
