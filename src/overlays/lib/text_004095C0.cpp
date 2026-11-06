#include "include_asm.h"
#include "overlays/lib/text_004095C0.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/lib/text_004BD360.h"
#include "main/resident_data.h"
#include "main/resident_00101260.h"
#include "main/resident_00101550.h"
#include "main/resident_0010A0E0.h"
#include "overlays/lib/item_allocation.h"
#include "sdk/main/libc_guess_00137290.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "sdk/main/libkernl_00121940.h"
#include "main/resident_001001E0.h"
#include "overlays/lib/text_0044ABE0.h"
#include "clamp.h"
#include "overlays/lib/memory_card.h"

/** Archive key of the game data resource, which holds the item catalog. */
#define LIB_GAME_DATA_RESOURCE 10

/** Twelve-byte records from this one-based ID on get no starting word; this one gets byte 8 set to 3. */
#define LIB_GAME_STATE_RECORD0C_FIXED_ID 29

/** Item types in each D_501EE0 row. */
#define LIB_RECORD0C_ITEM_TYPE_COUNT 200

/** Resident entry table key of the LibValueTable. */
#define LIB_ENTRY_VALUE_TABLE 0x76505730

/** Sizes of the icon.sys and save data files. */
#define LIB_ICON_SYS_SIZE 0x3C4
#define LIB_SAVE_DATA_SIZE 0x11ABA2

/** Entries in each LibValueTable array. */
#define LIB_VALUE_TABLE_COUNT 51

/** Code lists at D_001B64CC and the entries in each. */
#define LIB_CODE_LIST_COUNT 10
#define LIB_CODE_LIST_ENTRY_COUNT 32

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
    u8 unk0a[0x16];
    s16 unk20;
    u8 unk22[0x10];
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

/** Starting halfword and byte of one LibGameStateRecord34. */
typedef struct LibGameStateInitial34
{
    u16 unk00;
    u8 unk02;
    u8 unk03;
} LibGameStateInitial34;

/** Two-byte entry of a LibCodeList; only its first byte is searched. */
typedef struct LibCodeListEntry
{
    u8 code;
    u8 unk01;
} LibCodeListEntry;

/** One of the ten 0x42-byte code lists at D_001B64CC. */
typedef struct LibCodeList
{
    LibCodeListEntry entries[LIB_CODE_LIST_ENTRY_COUNT];
    u8 unk40[2];
} LibCodeList;

/** One of the ten 0x56-byte code tables at D_001B64D0. */
typedef struct LibCodeTable
{
    LibCodeListEntry high_codes[26];
    LibCodeListEntry low_codes[16];
    u8 unk54[2];
} LibCodeTable;

/** Four-byte factor record of the D_504AA0 table, indexed by factor ID minus one. */
typedef struct LibRecord504AA0
{
    /** Price a factor adds to an item. */
    u32 price : 20;

    u32 unk14 : 5;
    u32 unk19 : 7;
} LibRecord504AA0;

/** 0xA0-byte table the game keeps in the resident entry table under LIB_ENTRY_VALUE_TABLE. */
typedef struct LibValueTable
{
    u32 unk00;
    u16 values[LIB_VALUE_TABLE_COUNT];
    u8 order[LIB_VALUE_TABLE_COUNT];
} LibValueTable;

/** Factor ID and the value func_0040D680 adds for it. */
typedef struct LibFactorValue
{
    u16 factor;
    u16 value;
} LibFactorValue;

/** Partial save data manager with vtable D_1721B0 in main data: a memory card, its card files and their request. */
struct LibClass1721B0
{
    u8 unk00[0x14];
    LibMemoryCard* card;
    s16 unk18;
    s16 unk1a;
    s16 unk1c;
    s16 unk1e;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    u8 unk26[0x5A];

    /** icon.sys contents. */
    u8* icon_sys;

    /** Card files the request points at. */
    LibCardFileBuffer files[2];

    u8 unka4[0x230];
    LibCardFileRequest request;
    u8 unk2e4[0x4B4];
    u8* unk798;
    u8* unk79c;

    /** Directory name shared by both card files. */
    char directory[0xD8];

    u16 unk878;
    u16 unk87a;
    s32 result;
    u8 unk880;
    u8 unk881[0xB];
    u8 unk88c[0x40];
    u8 unk8cc;
    u8 unk8cd[3];
    u32 unk8d0;
    u8 unk8d4;
    u8 unk8d5[7];
    u8 unk8dc[0x2E];
    u8 unk90a;
    u8 unk90b;
    u8 unk90c[0x64];
    u8 unk970;
    u8 unk971[0x13];
    u32 unk984;
    u32 unk988;
};

/** The icon.sys file name. */
extern "C" char D_4EC440[];

/** Three codes checked by func_0040A9B0. */
extern "C" u8 D_001B6198[3];

/** Three codes checked by func_0040A970. */
extern "C" u8 D_001B619C[3];

/** Allocation func_0040AFA0 makes and func_0040AF80 frees. */
extern "C" void* D_001B64AC;

/** Buffer func_0040B760 allocates for the item catalog at D_001B64F0. */
extern "C" u8* D_001B64EC;

extern "C" ItemCreationCategoryDefinition* D_001B64F4;

/** Code lists that func_0040AFA0 points into its loaded resource. */
extern "C" LibCodeList* D_001B64CC;

/** Code tables that func_0040AFA0 points into its loaded resource. */
extern "C" LibCodeTable* D_001B64D0;

extern "C" const LibRecord504AA0 D_504AA0[];

/** Starting values of LibValueTable::values, falling from 850 to 1. */
extern "C" const u16 D_501D30[LIB_VALUE_TABLE_COUNT];

/** Item types func_0040BF50 picks from, one row per LibGameStateRecord0C ID minus one; zero entries are skipped. */
extern "C" const u16 D_501EE0[][LIB_RECORD0C_ITEM_TYPE_COUNT];

/** Fol paid by func_0040C4C0, indexed by a record's place plus an offset for how few records are ranked. */
extern "C" const u16 D_5055D0[];

/** Factor values, ended by a zero factor. */
extern "C" const LibFactorValue D_5055A0[];

/** LibGameStateTimer::bitset_mask for each catalog category. */
extern "C" const u16 D_5055C0[];

/** Eleven codes; func_0040B360 maps a code to its one-based position here. */
extern "C" const u8 D_505620[11];

/** Starting word of each LibGameStateRecord0C below LIB_GAME_STATE_RECORD0C_FIXED_ID; all zero in the shipped data. */
extern "C" const u16 D_505630[];

/** Starting values of the LibGameStateRecord34 entries. */
extern "C" const LibGameStateInitial34 D_505670[];

/**
 * @brief Return the resident game state.
 * @return Game state at D_001B64F8.
 */
static inline LibGameState* lib_game_state()
{
    return reinterpret_cast<LibGameState*>(D_001B64F8);
}

/**
 * @brief Start a game state timer.
 * @param timer Free timer.
 * @param item_type One-based item type ID.
 * @param mask Bitsets to mark when the timer finishes.
 */
static inline void start_timer(LibGameStateTimer* timer, u16 item_type, u16 mask)
{
    timer->item_type = item_type;
    timer->bitset_mask = mask;
    timer->elapsed = 0;
}

/**
 * @brief Finish a game state timer: mark its item type in the bitsets it names, flag the item type and free the timer.
 * @param state Game state.
 * @param timer Running timer.
 */
static inline void finish_timer(LibGameState* state, LibGameStateTimer* timer)
{
    u16 item_type = timer->item_type;
    u32 mask = timer->bitset_mask;
    LibGameStateBitset* bitset = state->bitsets;

    for (s32 i = 0; i < LIB_GAME_STATE_BITSET_COUNT; i++)
    {
        if (mask & 1)
        {
            s32 index = item_type - 1;
            bitset->bits[index / 8] |= 1 << (index & 7);
            bitset->count++;
        }

        bitset++;
        mask >>= 1;
    }

    s32 type_index = item_type - 1;
    ItemCreationCategoryRecord* record = &state->item_types[type_index];
    record->flags |= 0x10;
    state->unk1172e++;
    timer->item_type = 0;
}

/**
 * @brief Read the stored Fol after validating the settings checksum.
 * @param settings System settings.
 * @return Decoded Fol, or zero when the checksum is invalid.
 */
static inline u32 settings_fol(LibSystemSettings* settings)
{
    u16 checksum = settings->checksum;
    u32 value;

    if (checksum != lib_compute_checksum(settings->key, &settings->checksum_start, (u8*)&settings->checksum - &settings->checksum_start))
    {
        value = 0;
    }
    else
    {
        value = settings->encoded_fol ^ LIB_RECORD_XOR_WORD;
    }

    return value;
}

/**
 * @brief Store a new Fol amount, limited to 0 through 99999999, when the settings checksum is valid, and reseal the checksum.
 * @param settings System settings.
 * @param value Fol to store.
 */
static inline void set_settings_fol(LibSystemSettings* settings, s32 value)
{
    u16 checksum = settings->checksum;

    if (checksum == lib_compute_checksum(settings->key, &settings->checksum_start, (u8*)&settings->checksum - &settings->checksum_start))
    {
        value += 40597;
        value = clamp(value, 40597, 100040596);
        value -= 40597;
        settings->encoded_fol = value ^ LIB_RECORD_XOR_WORD;
        settings->key = resident_next_random_word();
        settings->checksum = lib_compute_checksum(settings->key, &settings->checksum_start, (u8*)&settings->checksum - &settings->checksum_start);
    }
}

/**
 * @brief Collect a category's allocations that have no equipped owner.
 * @param state Resident allocation records, category links and category entries.
 * @param records Output array receiving unequipped allocation pointers.
 * @param category One-based category ID from one through seven hundred fifty.
 * @return Number of allocations collected, or zero for an invalid or empty category.
 */
static inline s32 collect_unequipped(const void* state, ItemCreationAllocationRecord** records, u16 category)
{
    const LibGameState* inventory = (const LibGameState*)state;
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

/**
 * @brief Lower the stored count of each of an allocation's factors by one.
 * @param record Allocation record whose factors are counted.
 */
static inline void lower_factor_counts(const ItemCreationAllocationRecord* record)
{
    u8* counts =
        reinterpret_cast<LibSystemSettings*>(resident_find_entry(resident_get_entry_table(resident_get_system()), LIB_ENTRY_SYSTEM_SETTINGS))->unkA8;

    for (s32 i = 0; i < 8; i++)
    {
        s32 factor = func_0040D930(record, i);

        if (factor)
        {
            func_00456F90(counts, factor);
        }
    }
}

/**
 * @brief Raise the stored count of each of an allocation's factors by one.
 * @param record Allocation record whose factors are counted.
 */
static inline void raise_factor_counts(const ItemCreationAllocationRecord* record)
{
    u8* counts =
        reinterpret_cast<LibSystemSettings*>(resident_find_entry(resident_get_entry_table(resident_get_system()), LIB_ENTRY_SYSTEM_SETTINGS))->unkA8;

    for (s32 i = 0; i < 8; i++)
    {
        s32 factor = func_0040D930(record, i);

        if (factor)
        {
            func_00456FE0(counts, factor);
        }
    }
}

/**
 * @brief Free a byte array and clear the pointer to it.
 * @param bytes Pointer to the array, or to null.
 */
static inline void delete_array(u8*& bytes)
{
    if (bytes != 0)
    {
        delete[] bytes;
        bytes = 0;
    }
}

/**
 * @brief Check whether an item type has an inventor.
 * @param record Item type record.
 * @return True when the inventor ID is nonzero.
 */
static inline bool has_inventor(const ItemCreationCategoryRecord* record)
{
    if (record->inventor_id)
    {
        return true;
    }

    return false;
}

/**
 * @brief Check whether a game state timer has an item type.
 * @param timer Timer to check.
 * @return True when the timer is running.
 */
static inline bool timer_active(const LibGameStateTimer* timer)
{
    if (timer->item_type)
    {
        return true;
    }

    return false;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004095C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00409A10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00409DA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040A370);

/**
 * @brief Run func_0040A9F0 for a code with flag 1, and again with flag 0 for codes 1 through 29 of code lists 2 and 9.
 * @param entry Protected entry record.
 * @param list_id One-based code list ID.
 * @param code Selected code.
 * @param first Passed through to func_0040A9F0.
 * @param second Passed through to func_0040A9F0.
 */
void func_0040A520(FieldRecord* entry, s32 list_id, s32 code, s32 first, s32 second)
{
    func_0040A9F0(entry, list_id, code, 1, first, second);

    if ((list_id == 2 || list_id == 9) && code > 0 && code < 30)
    {
        func_0040A9F0(entry, list_id, code, 0, first, second);
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040A5C0);

/**
 * @brief Check whether a code is one of the three codes at D_001B619C.
 * @param code Code to look for.
 * @return One when the code is listed, otherwise zero.
 */
s32 func_0040A970(s32 code)
{
    for (u32 i = 0; i < 3; i++)
    {
        if (D_001B619C[i] == code)
        {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Check whether a code is one of the three codes at D_001B6198.
 * @param code Code to look for.
 * @return One when the code is listed, otherwise zero.
 */
s32 func_0040A9B0(s32 code)
{
    for (u32 i = 0; i < 3; i++)
    {
        if (D_001B6198[i] == code)
        {
            return 1;
        }
    }

    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040A9F0);

/**
 * @brief Find a code in one of the ten code tables at D_001B64D0.
 * @param id One-based code table ID.
 * @param code Code to look for: 129 through 154 in the high codes, 30 through 128 (or 1 through 29 for tables 2 and 9) in
 * the low codes.
 * @return The code's position, counting the 26 high codes first, or -1 when it isn't found.
 */
s32 func_0040AE00(s32 id, s32 code)
{
    s32 index = id - 1;

    if (index < 0 || index >= LIB_CODE_LIST_COUNT)
    {
        return -1;
    }

    LibCodeListEntry* entry;
    s32 count;
    s32 base;

    if (code >= 129 && code < 155)
    {
        entry = D_001B64D0[index].high_codes;
        base = 0;
        count = 26;
    }
    else if (code >= 30 && code <= 128 || (id - 1 == 1 || id - 1 == 8) && code > 0 && code < 30)
    {
        entry = D_001B64D0[id - 1].low_codes;
        count = 16;
        base = 26;
    }
    else
    {
        return -1;
    }

    for (s32 i = 0; i < count; i++)
    {
        if (entry->code == code)
        {
            return i + base;
        }

        entry++;
    }

    return -1;
}

/**
 * @brief Find a code in one of the ten code lists at D_001B64CC.
 * @param id One-based code list ID.
 * @param code Code to look for.
 * @return Index of the code's entry in the list, or -1 for an invalid ID or a code that isn't listed.
 */
s32 func_0040AF10(s32 id, s32 code)
{
    s32 index = id - 1;

    if (index < 0 || index >= LIB_CODE_LIST_COUNT)
    {
        return -1;
    }

    LibCodeListEntry* entry = D_001B64CC[index].entries;

    for (s32 i = 0; i < LIB_CODE_LIST_ENTRY_COUNT; i++)
    {
        if (entry->code == code)
        {
            return i;
        }

        entry++;
    }

    return -1;
}

/** @brief Free the allocation func_0040AFA0 made. */
void func_0040AF80(void)
{
    free_guess(D_001B64AC);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040AFA0);

/** @brief Remove the value table from the resident entry table and free it. */
void func_0040B1F0(void)
{
    ResidentEntryTable* table = resident_get_entry_table(resident_get_system());
    void* entry = reinterpret_cast<void*>(resident_find_entry(table, LIB_ENTRY_VALUE_TABLE));
    resident_remove_entry(table, LIB_ENTRY_VALUE_TABLE);
    operator delete(entry);
}

/**
 * @brief Create the value table and store it in the resident entry table.
 * @return One when it was stored, or zero when the table is full.
 */
u32 func_0040B250()
{
    LibValueTable* table = new (0) LibValueTable;
    table->unk00 = 0;

    for (s32 i = 0; i < LIB_VALUE_TABLE_COUNT; i++)
    {
        table->values[i] = D_501D30[i];
        table->order[i] = i == 0 ? LIB_VALUE_TABLE_COUNT : i;
    }

    return func_001014B0(resident_get_entry_table(resident_get_system()), table, LIB_ENTRY_VALUE_TABLE);
}

/**
 * @brief Read the five-bit unk14 field of a D_504AA0 factor record.
 * @param id One-based record ID, below 0x2C0.
 * @return The field, or zero for an invalid ID.
 */
s32 func_0040B2F0(u16 id)
{
    s32 value = 0;

    if (id > 0 && id < 0x2C0)
    {
        value = D_504AA0[id - 1].unk14;
    }

    return value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040B330);

/**
 * @brief Find a code's one-based position in the eleven codes at D_505620.
 * @param code Code to look for.
 * @return The last matching position, or zero when the code isn't listed.
 */
s32 func_0040B360(s32 code)
{
    s32 id = 0;
    const u8* entry = D_505620;

    for (s32 i = 0; i < 11; i++)
    {
        if (*entry == code)
        {
            id = i + 1;
        }

        entry++;
    }

    return id;
}

/**
 * @brief Decode the item catalog and reset the resident game state for a new game.
 * @param data Game data resource, or null to load it from the archive here.
 * @return One on success, or zero when the catalog can't be loaded or decoded.
 */
s32 lib_reset_game_state(u8* data)
{
    u8* buffer = 0;

    if (data == 0)
    {
        ResidentArchive* archive = resident_get_archive(resident_get_system());
        buffer = static_cast<u8*>(memalign(RESIDENT_RESOURCE_ALIGNMENT, resident_get_resource_size(archive, LIB_GAME_DATA_RESOURCE)));

        if (buffer == 0)
        {
            return 0;
        }

        FlushCache(0);

        if (!func_0011CA60(archive, buffer, LIB_GAME_DATA_RESOURCE, 0))
        {
            return 0;
        }

        data = buffer;
    }

    if (!resident_decode_resource_block(func_001012B0(resident_get_system()), reinterpret_cast<ResidentResourceHeader*>(data), D_001B64F0, 0))
    {
        return 0;
    }

    if (buffer != 0)
    {
        free_guess(buffer);
        FlushCache(0);
    }

    LibGameState* state = lib_game_state();
    memset_guess(state, 0, sizeof(LibGameState));
    LibAllocationEquipmentView* allocation = state->allocations;

    for (s32 i = 0; i < LIB_ALLOCATION_COUNT; i++)
    {
        func_0040B6D0(allocation);
        allocation++;
    }

    ItemCreationCategoryRecord* item_type = state->item_types;

    for (s32 i = 0; i < ITEM_TYPE_COUNT; i++)
    {
        func_0040B6C0(item_type, i);
        item_type++;
    }

    const u16* value = D_505630;
    LibGameStateRecord0C* record = state->unk10d88;

    for (s32 i = 0; i < LIB_GAME_STATE_RECORD0C_COUNT; i++)
    {
        func_0040B6B0(record, i + 1);

        if (!func_0040B6A0(record))
        {
            func_0040B690(record, *value);
            func_0040B680(record, 1);
        }
        else if (i + 1 == LIB_GAME_STATE_RECORD0C_FIXED_ID)
        {
            func_0040B670(record, 3);
        }

        value++;
        record++;
    }

    const LibGameStateInitial34* initial = D_505670;
    LibGameStateRecord34* entry = state->unk10f50;

    for (s32 i = 0; i < LIB_GAME_STATE_RECORD34_COUNT; i++)
    {
        func_0040B660(entry, i + 1);
        func_0040B650(entry, initial->unk00);
        func_0040B640(entry, initial->unk02);
        initial++;
        entry++;
    }

    state->unk116a0 = 18000;
    state->unk116a4 = 36000;
    state->unk116ac = 108000;
    state->timer_limit = 18000;
    FlushCache(0);
    return 1;
}

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

/** Return whether the byte at receiver offset 0x6 is at least 0x1D. */
s32 func_0040B6A0(void* object)
{
    ByteSetterOwnertext_004095C0* receiver = static_cast<ByteSetterOwnertext_004095C0*>(object);
    return (receiver->unk06 < 0x1D) ^ 1;
}

/** Store the byte at receiver offset 0x6. */
void func_0040B6B0(void* object, u8 value)
{
    ByteSetterOwnertext_004095C0* receiver = static_cast<ByteSetterOwnertext_004095C0*>(object);
    receiver->unk06 = value;
}

/** Store the low halfword at receiver offset 0x2. */
void func_0040B6C0(void* object, u16 value)
{
    HalfwordSetterOwnertext_004095C0* receiver = static_cast<HalfwordSetterOwnertext_004095C0*>(object);
    receiver->unk02 = value;
}

/**
 * @brief Clear an allocation record, give it a random checksum shift and store its checksum.
 * @param record Allocation record.
 */
void func_0040B6D0(void* record)
{
    ItemCreationAllocationRecord* allocation = static_cast<ItemCreationAllocationRecord*>(record);
    *(unsigned __int128*)allocation = 0;
    allocation->checksum_shift = resident_next_random_word() & 3;
    allocation->checksum = allocation->calculate_checksum();
}

/**
 * @brief Allocate the item catalog buffer and the resident game state.
 * @return One when the game state was allocated; zero when either allocation fails.
 */
s32 func_0040B760()
{
    u8* buffer = new (0) u8[0x5E7C];

    if (buffer == 0)
    {
        return 0;
    }

    D_001B64EC = buffer;
    D_001B64F0 = reinterpret_cast<ItemCreationCategoryDefinition*>((reinterpret_cast<u32>(buffer) + 0x7F) & ~0x7F);
    // The catalog's byte size is added as an element count, so this points far past the buffer.
    D_001B64F4 = D_001B64F0 + sizeof(ItemCreationCategoryDefinition) * ITEM_TYPE_COUNT;
    D_001B64F8 = reinterpret_cast<ResidentObject1B64F8*>(new (0) LibGameState);
    return D_001B64F8 != 0;
}

/**
 * @brief Run the game state's func_0040BB00 and func_0040C690 updates and restart its random countdown.
 * @param state Game state.
 */
void func_0040B7E0(LibGameState* state)
{
    if (func_0040BB00(state))
    {
        state->unk117a4 = 1;
    }

    func_0040C690(state);
    state->unk116a8 = 0;
    state->unk117a5 = 1;
}

/**
 * @brief Advance the game state by one frame: its two countdowns and every running LibGameStateTimer.
 * @param state Game state.
 * @return Nonzero when an update or a finished timer changed the state this frame.
 */
u8 func_0040B840(LibGameState* state)
{
    state->unk117a4 = 0;

    if (--state->unk116a8 <= 0)
    {
        if (!state->unk117a5)
        {
            if (func_0040BB00(state))
            {
                state->unk117a4 = 1;
            }

            func_0040C690(state);
        }

        for (s32 i = 0; i < state->unk117a2; i++)
        {
            s32 index = state->unk11760[i] - 1;
            state->unk10d88[index].unk0a = 0;
        }

        func_0040BF50(state);
        state->unk116a8 = state->unk116a0 + resident_random_below(state->unk116a4);
        state->unk117a5 = 0;
    }

    if (--state->unk116b0 <= 0)
    {
        func_0040C4C0(state);
        state->unk116b0 = state->unk116ac;
    }

    LibGameStateTimer* timer = state->timers;

    for (s32 i = 0; i < LIB_GAME_STATE_TIMER_COUNT; i++)
    {
        if (timer_active(timer))
        {
            if (++timer->elapsed >= state->timer_limit)
            {
                finish_timer(state, timer);
                state->unk117a4 = 1;
            }
        }

        timer++;
    }

    return state->unk117a4;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040BB00);

/**
 * @brief Pick 11 to 15 random LibGameStateRecord0C entries with unk08 and unk09 set and unk0a clear, give each a random
 * listed item type from its D_501EE0 row and list their IDs in unk11760.
 * @param state Game state.
 */
void func_0040BF50(LibGameState* state)
{
    u8 candidates[LIB_GAME_STATE_RECORD0C_FIXED_ID - 1];
    u16 items[LIB_RECORD0C_ITEM_TYPE_COUNT];
    s32 count = 0;
    u8* candidate = candidates;
    LibGameStateRecord0C* record = state->unk10d88;

    for (s32 i = 0; i < LIB_GAME_STATE_RECORD0C_FIXED_ID - 1; i++)
    {
        if (record->unk08 && record->unk09 && !record->unk0a)
        {
            *candidate++ = record->unk06;
            count++;
        }

        record++;
    }

    s32 picked = 0;

    if (count > 0)
    {
        s32 limit = resident_random_below(5) + 11;

        if (count < limit)
        {
            limit = count;
        }

        u8* slot = state->unk11760;

        do
        {
            s32 pick = resident_random_below(count);
            u8* entry = &candidates[pick];
            u8 id = *entry;
            s32 index = id - 1;
            const u16* source = D_501EE0[index];
            s32 item_count = 0;
            u16* item = items;

            for (s32 j = 0; j < LIB_RECORD0C_ITEM_TYPE_COUNT; j++)
            {
                u16 item_type = *source;

                if (item_type > 0 && !D_001B64F0[item_type - 1].unused)
                {
                    *item++ = item_type;
                    item_count++;
                }

                source++;
            }

            u16 chosen = items[resident_random_below(item_count)];
            LibGameStateRecord0C* chosen_record = &state->unk10d88[index];
            chosen_record->unk0a = 1;
            chosen_record->unk04 = chosen;
            count--;
            picked++;
            *slot++ = id;

            for (; pick < count; pick++)
            {
                entry[0] = entry[1];
                entry++;
            }
        } while (picked < limit);
    }

    state->unk117a2 = picked;
}

/**
 * @brief Start a game state timer for an item type, finishing the most recently started timer when none is free.
 * @param state Game state.
 * @param item_type One-based item type ID.
 */
void func_0040C180(LibGameState* state, u16 item_type)
{
    LibGameStateTimer* free_timer = 0;
    u32 newest = 0xFFFFFFFF;
    LibGameStateTimer* newest_timer;
    LibGameStateTimer* timer = state->timers;

    for (s32 i = 0; i < LIB_GAME_STATE_TIMER_COUNT; i++)
    {
        if (timer_active(timer))
        {
            if (timer->elapsed < newest)
            {
                newest = timer->elapsed;
                newest_timer = timer;
            }
        }
        else
        {
            free_timer = timer;
            break;
        }

        timer++;
    }

    if (free_timer == 0)
    {
        finish_timer(state, newest_timer);
        free_timer = newest_timer;
    }

    start_timer(free_timer, item_type, D_5055C0[D_001B64F0[item_type - 1].category]);
}

/**
 * @brief Give an item type its inventor, set its flags and add a random amount to its shop stock.
 * @param state Game state.
 * @param item_type One-based item type ID.
 * @param inventor_id Inventor to record.
 * @param set_flag04 Nonzero to set flag 0x04 on the item type.
 * @param set_flag08 Nonzero to set flag 0x08 and count the item type in unk11726 (flag 0x04 set) or unk1172a.
 * @return One when the inventor was recorded; zero for an unlimited-stock item type or one that already has an inventor.
 */
s32 func_0040C300(LibGameState* state, u16 item_type, u8 inventor_id, s32 set_flag04, s32 set_flag08)
{
    ItemCreationCategoryRecord* record = &state->item_types[item_type - 1];

    if (D_001B64F0[record->catalog_index].unlimited_stock || has_inventor(record))
    {
        return 0;
    }

    record->inventor_id = inventor_id;

    if (set_flag04)
    {
        record->flags |= 0x4;
    }

    if (set_flag08)
    {
        record->flags |= 0x8;
        u8 flag04 = record->flags & 0x4;

        if (flag04)
        {
            state->unk11726++;
        }
        else
        {
            state->unk1172a++;
        }
    }

    record->flags &= ~0x2;
    s32 range = 100 - D_001B64F0[item_type - 1].creation_difficulty;
    s32 stock = (range / 20 + resident_random_below(range / 2)) / 6 + 1;
    stock += record->shop_stock;

    if (stock < 0)
    {
        stock = 0;
    }
    else if (stock > 99)
    {
        stock = 99;
    }

    record->shop_stock = stock;
    return 1;
}

/**
 * @brief Add a D_5055D0 payout for each ranked LibGameStateRecord0C with unk08 of at least 2 to the stored Fol.
 * @param state Game state.
 */
void func_0040C4C0(LibGameState* state)
{
    s32 total = 0;
    s32 offset = 30 - state->record0c_order_count;

    if (offset < 0)
    {
        offset = 0;
    }

    u8* order = state->record0c_order;

    for (s32 i = 0; i < state->record0c_order_count; i++, order++)
    {
        s32 index = *order - 1;
        LibGameStateRecord0C* record = &state->unk10d88[index];

        if (record->unk08 >= 2)
        {
            total += D_5055D0[offset + (record->unk07 - 1)];
        }
    }

    if (total > 0)
    {
        LibSystemSettings* settings =
            reinterpret_cast<LibSystemSettings*>(resident_find_entry(resident_get_entry_table(resident_get_system()), LIB_ENTRY_SYSTEM_SETTINGS));
        s32 fol = settings_fol(settings);
        set_settings_fol(settings, fol + total);
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040C690);

/**
 * @brief Record which character has an allocation equipped and update its item type's counts.
 * @param inventory Resident game state.
 * @param identifier One-based allocation ID.
 * @param owner One-based character number, or zero to unequip.
 * @return One when the allocation is in use; zero for an invalid ID or a free allocation.
 */
s32 lib_allocation_set_equipped_owner(ResidentObject1B64F8* inventory, s16 identifier, s32 owner)
{
    LibGameState* state = reinterpret_cast<LibGameState*>(inventory);
    bool valid = false;

    if (identifier > 0 && identifier <= LIB_ALLOCATION_COUNT)
    {
        valid = true;
    }

    ItemCreationAllocationRecord* record;

    if (valid)
    {
        record = reinterpret_cast<ItemCreationAllocationRecord*>(&state->allocations[identifier - 1]);
    }
    else
    {
        record = 0;
    }

    if (record == 0 || !record->allocated)
    {
        return 0;
    }

    reinterpret_cast<LibAllocationEquipmentView*>(record)->equipped_owner = owner;
    func_0040D050(state, record->definition_index() + 1);
    return 1;
}

/**
 * @brief Remove the first unequipped allocation of an item type through func_0040C9F0.
 * @param state Game state.
 * @param item_type One-based item type ID.
 * @return func_0040C9F0's result, or zero when the item type has no unequipped allocation.
 */
s32 func_0040C8F0(LibGameState* state, u16 item_type)
{
    ItemCreationAllocationRecord* records[100];

    if (collect_unequipped(state, records, item_type) == 0)
    {
        return 0;
    }

    return func_0040C9F0(state, lib_allocation_get_identifier(records[0]));
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040C9F0);

/**
 * @brief Allocate a new item of a type, link it into its item type's list and update the counts.
 * @param state Game state.
 * @param item_type One-based item type ID.
 * @param modification_number Factor-change count passed to lib_allocation_initialize.
 * @param creator_id Creator recorded as the item type's first creator when it has none.
 * @param factors Eight factor codes, or null for catalog defaults.
 * @param new_item Mark the item as new in inventory lists.
 * @return One-based allocation ID, or zero for an invalid item type, a full pool or twenty items of the type.
 */
s16 func_0040CC70(LibGameState* state, u16 item_type, u8 modification_number, u8 creator_id, const u16* factors, bool new_item)
{
    bool valid = false;

    if (item_type > 0 && item_type <= ITEM_TYPE_COUNT)
    {
        valid = true;
    }

    if (!valid)
    {
        return 0;
    }

    u8 unsellable = D_001B64F0[item_type - 1].unsellable;
    s16 identifier = 0;
    s16 candidate;
    s32 count;

    if (unsellable)
    {
        candidate = 1;
        count = 100;
    }
    else
    {
        candidate = 101;
        count = 2900;
    }

    ItemCreationAllocationRecord* allocation = reinterpret_cast<ItemCreationAllocationRecord*>(&state->allocations[candidate - 1]);

    for (s32 i = 0; i < count; i++)
    {
        if (!allocation->allocated)
        {
            identifier = candidate;
            break;
        }

        allocation++;
        candidate++;
    }

    if (identifier == 0)
    {
        return 0;
    }

    ItemCreationCategoryRecord* record = &state->item_types[item_type - 1];

    if ((u8)(record->inventory_count + record->equipped_count) >= 20)
    {
        return 0;
    }

    record->inventory_count++;
    s32 head = record->allocation_list_head;
    s32 index = identifier - 1;
    LibInventoryAllocationLinks* link = &state->links[index];
    record->allocation_list_head = identifier;
    link->previous = 0;
    link->next = head;

    if (head != 0)
    {
        s32 head_index = (s16)head - 1;
        LibInventoryAllocationLinks* head_link = &state->links[head_index];
        head_link->previous = identifier;
    }

    if (new_item)
    {
        record->flags |= 0x1;
    }

    if (!D_001B64F0[record->catalog_index].unlimited_stock && !has_inventor(record))
    {
        record->flags |= 0x2;
    }

    if (record->first_creator_id == 0)
    {
        record->first_creator_id = creator_id;
    }

    ItemCreationAllocationRecord* created = reinterpret_cast<ItemCreationAllocationRecord*>(&state->allocations[index]);
    lib_allocation_initialize(created, item_type, modification_number, factors, new_item, false);

    if (created->battle_usable)
    {
        record->flags |= 0x20;
        record->battle_usable_count++;
    }

    raise_factor_counts(created);

    if (unsellable)
    {
        state->unk11722++;
    }
    else
    {
        state->unk11724++;
    }

    return identifier;
}

/**
 * @brief Collect a category's allocations that have no equipped owner.
 * @param state Resident allocation records, category links and category entries.
 * @param records Output array receiving unequipped allocation pointers.
 * @param category One-based category ID from one through seven hundred fifty.
 * @return Number of allocations collected, or zero for an invalid or empty category.
 */
s32 lib_collect_unequipped_allocations(const void* state, ItemCreationAllocationRecord** records, u16 category)
{
    return collect_unequipped(state, records, category);
}

/**
 * @brief Recount an item type's inventory, equipped and battle-usable items and update its flags.
 * @param state Game state.
 * @param item_type One-based item type ID.
 */
void func_0040D050(LibGameState* state, u16 item_type)
{
    s32 inventory_count = 0;
    s32 equipped_count = 0;
    s32 battle_usable_count = 0;
    bool has_new = false;
    bool has_battle_usable;
    ItemCreationCategoryRecord* record = &state->item_types[item_type - 1];
    has_battle_usable = false;
    s32 identifier = record->allocation_list_head;

    while (identifier != 0)
    {
        ItemCreationAllocationRecord* allocation;
        s32 index = (s16)identifier - 1;
        allocation = reinterpret_cast<ItemCreationAllocationRecord*>(&state->allocations[index]);
        u8 equipped_owner = state->allocations[index].equipped_owner;

        if (equipped_owner == 0)
        {
            inventory_count++;

            if (allocation->new_item)
            {
                has_new = true;
            }

            if (allocation->battle_usable)
            {
                battle_usable_count++;
                has_battle_usable = true;
            }
        }
        else
        {
            equipped_count++;
        }

        identifier = state->links[index].next;
    }

    record->inventory_count = inventory_count;
    record->equipped_count = equipped_count;
    record->battle_usable_count = battle_usable_count;

    if (has_new)
    {
        record->flags |= 0x1;
    }
    else
    {
        record->flags &= ~0x1;
    }

    if (has_battle_usable)
    {
        record->flags |= 0x20;
    }
    else
    {
        record->flags &= ~0x20;
    }

    if (!D_001B64F0[record->catalog_index].unlimited_stock && !has_inventor(record) && inventory_count > 0)
    {
        record->flags |= 0x2;
    }
    else
    {
        record->flags &= ~0x2;
    }
}

/**
 * @brief Lower the stored count of each of an allocation's factors by one.
 * @param object Unused.
 * @param record Allocation record whose factors are counted.
 */
void func_0040D1E0(void* object, const ItemCreationAllocationRecord* record)
{
    lower_factor_counts(record);
}

/**
 * @brief Raise the stored count of each of an allocation's factors by one.
 * @param object Unused.
 * @param record Allocation record whose factors are counted.
 */
void func_0040D260(void* object, const ItemCreationAllocationRecord* record)
{
    raise_factor_counts(record);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", lib_allocation_initialize);

/**
 * @brief Add up the D_5055A0 values of an allocation's factors.
 * @param record Allocation record.
 * @return The total, at most 100; 100 when the factors add nothing and the allocation isn't equipped.
 */
s32 func_0040D680(const ItemCreationAllocationRecord* record)
{
    s32 total = 0;

    for (s32 i = 0; i < 8; i++)
    {
        u16 factor = func_0040D930(record, i);
        const LibFactorValue* entry = D_5055A0;
        u16 key = entry->factor;

        while (key > 0)
        {
            if (key == factor)
            {
                total += entry->value;
                break;
            }

            entry++;
            key = entry->factor;
        }
    }

    if (total > 100)
    {
        total = 100;
    }

    if (total == 0)
    {
        u8 equipped_owner = reinterpret_cast<const LibAllocationEquipmentView*>(record)->equipped_owner;

        if (equipped_owner == 0)
        {
            total = 100;
        }
    }

    return total;
}

/**
 * @brief Calculate an allocation's price: its catalog base price plus the price of each factor.
 * @param record Allocation record.
 * @return The price, at most 99999999.
 */
u32 func_0040D760(ItemCreationAllocationRecord* record)
{
    u32 price = D_001B64F0[record->definition_index()].base_price;

    for (s32 i = 0; i < 8; i++)
    {
        u16 factor = func_0040D930(record, i);

        if (factor)
        {
            price += D_504AA0[factor - 1].price;
        }
    }

    if (price > 99999999)
    {
        price = 99999999;
    }

    return price;
}

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

/**
 * @brief Report which memory card slots are ready.
 * @param object Save data manager.
 * @return Bit 0 for slot 1 and bit 1 for slot 2, or zero while the card isn't ready.
 */
u16 func_0040F0B0(LibClass1721B0* object)
{
    LibMemoryCard* card = object->card;

    if (!card->ready)
    {
        return 0;
    }

    u16 mask = 0;
    LibMemoryCardSlot* slots = card->slots;

    if (slots[0].card_state == LIB_MEMORY_CARD_STATE_READY)
    {
        mask |= 0x1;
    }

    if (slots[1].card_state == LIB_MEMORY_CARD_STATE_READY)
    {
        mask |= 0x2;
    }

    return mask;
}

/**
 * @brief Start a card operation in a mode on slot 0 or 1, resetting the transfer state.
 * @param object Save data manager.
 * @param slot Memory card slot, 0 or 1.
 * @param mode Operation mode stored in unk878; modes 6 and 14 clear extra state.
 * @return One when started; zero without a memory card or for another slot.
 */
s32 func_0040F110(LibClass1721B0* object, u16 slot, u16 mode)
{
    if (object->card == 0)
    {
        return 0;
    }

    bool valid;

    if (slot != 0 && slot != 1)
    {
        valid = false;
    }
    else
    {
        valid = true;
    }

    if (!valid)
    {
        return 0;
    }

    if (object->unk90b == 1 && object->unk20 == 4 && mode == 16)
    {
        object->unk970 = 1;
    }
    else
    {
        object->unk970 = 0;
        object->unk984 = 0;
        object->unk988 = 0;
    }

    object->unk878 = mode;
    object->unk1c = slot;
    object->unk1e = -1;
    object->unk18 = 0;
    object->unk20 = 0;
    object->unk22 = 0;
    object->unk24 = 0;
    object->unk87a = 0;

    if (mode == 6)
    {
        object->unk880 = 0;
        object->unk8d0 = 0;
    }

    if (mode == 14)
    {
        object->unk8cd[slot] = 0;
    }

    return 1;
}

/**
 * @brief Store unk20 and reset the transfer state; a negative value also frees the two buffers.
 * @param object Save data manager.
 * @param value New unk20.
 */
void func_0040F210(LibClass1721B0* object, s16 value)
{
    object->unk20 = value;
    object->unk18 = 0;
    object->unk1c = -1;
    object->unk87a = 1;

    if (object->unk878 == 6)
    {
        if (object->unk20 > 0)
        {
            if (object->unk880)
            {
                object->unk880 = 0;
            }
            else
            {
                object->unk880 = 1;
            }
        }
        else
        {
            object->unk880 = 0;
        }
    }

    if (value < 0)
    {
        if (object->unk798 != 0)
        {
            delete_array(object->unk798);
        }

        if (object->unk79c != 0)
        {
            delete_array(object->unk79c);
        }
    }
}

/**
 * @brief Clear the two card files and point the file request at them.
 * @param object Save data manager.
 * @return One.
 */
s32 func_0040F2E0(LibClass1721B0* object)
{
    for (s32 i = 0; i < 0x40; i++)
    {
        object->unk88c[i] = 0;
    }

    object->files[0].name = object->directory;
    object->files[0].data = object->unk88c;
    object->files[0].size = 0x40;
    object->files[0].unk0C = 0;

    for (s32 i = 0; i < sizeof(object->unk8dc); i++)
    {
        object->unk8dc[i] = 0;
    }

    object->files[1].name = object->directory;
    object->files[1].data = object->unk8dc;
    object->files[1].size = 0x2E;
    object->files[1].unk0C = 0x4B4;
    object->request.directory = object->directory;
    object->request.file_count = 2;
    object->request.unk08 = 0;
    object->request.files = object->files;
    object->unk1a = 0;
    return 1;
}

/**
 * @brief Clear the icon.sys buffer, reallocate and clear the save data buffer and point the file request at both.
 * @param object Save data manager.
 * @return One.
 */
s32 func_0040F3E0(LibClass1721B0* object)
{
    if (object->icon_sys)
    {
        memset_guess(object->icon_sys, 0, LIB_ICON_SYS_SIZE);
    }

    if (object->unk798 != 0)
    {
        delete_array(object->unk798);
    }

    if (object->unk79c != 0)
    {
        delete_array(object->unk79c);
    }

    if (object->unk79c == 0)
    {
        object->unk79c = new (0) u8[LIB_SAVE_DATA_SIZE];
    }

    memset_guess(object->unk79c, 0, LIB_SAVE_DATA_SIZE);
    object->files[0].name = D_4EC440;
    object->files[0].data = object->icon_sys;
    object->files[0].size = LIB_ICON_SYS_SIZE;
    object->files[0].unk0C = 0;
    object->files[1].name = object->directory;
    object->files[1].data = object->unk79c;
    object->files[1].size = LIB_SAVE_DATA_SIZE;
    object->files[1].unk0C = 0;
    object->request.directory = object->directory;
    object->request.file_count = 2;
    object->request.unk08 = 0;
    object->request.files = object->files;
    object->unk1a = 0;
    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040F4F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040F740);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040F940);

/**
 * @brief Clear the byte at receiver offset 0x8D4.
 * @param object Receiver.
 * @return The halfword at receiver offset 0x20.
 */
s16 func_0040FAE0(void* object)
{
    ByteSetterOwnertext_004095C0* receiver = static_cast<ByteSetterOwnertext_004095C0*>(object);
    receiver->unk8d4 = 0;
    return receiver->unk20;
}

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", __dt__14LibTrophyFlagsFv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", __dt__11LibBitArrayFv);

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

/** @brief Draw in the bucket stored at unka8. */
void LibCallbackTransform::set_default_draw_bucket()
{
    draw_bucket = unka8;
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

void LibWidget::func_00413D20()
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
    object->set_rectangle(x, y, width, height);
    resources = (LibRuntimeCodeResources*)g_field_runtime;
    state->source = &resources->slots[resources->item_slot];
    if (!object->allocate_storage(0, 64, 0, 0))
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
    object->set_rectangle(x, y, width, height);
    resources = (LibRuntimeCodeResources*)g_field_runtime;
    state->source = &resources->slots[resources->factor_slot];
    if (!object->allocate_storage(0, 128, 0, 0))
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", __dt__14LibMovieStreamFv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", __ct__14LibMovieStreamFv);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", __ct__15LibMovieDecoderFv);

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
