#include "include_asm.h"
#include "overlays/lib/text_00419A70.h"
#include "overlays/lib/text_004095C0.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/lib/widget_aggregate.h"
#include "overlays/lib/text_004BD360.h"
#include "main/resident_data.h"
#include "overlays/lib/item_allocation.h"
#include "overlays/lib/movie_player.h"
#include "sdk/main/libc_guess_00137290.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "sdk/main/libkernl_00121940.h"
#include "overlays/lib/text_0044ABE0.h"
#include "clamp.h"
#include "overlays/lib/memory_card.h"
#include "main/system.h"

#define LIB_GAME_DATA_RESOURCE 10
#define LIB_GAME_STATE_RECORD0C_FIXED_ID 29
#define LIB_RECORD0C_ITEM_TYPE_COUNT 200
#define LIB_ENTRY_VALUE_TABLE 0x76505730
#define LIB_ICON_SYS_SIZE 0x3C4
#define LIB_SAVE_DATA_SIZE 0x11ABA2
#define LIB_VALUE_TABLE_COUNT 51
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

/** Four-byte factor record of the D_00504AA0 table, indexed by factor ID minus one. */
typedef struct LibRecord504AA0
{
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
    u8* icon_sys;
    LibCardFileBuffer files[2];
    u8 unka4[0x230];
    LibCardFileRequest request;
    u8 unk2e4[0x4B4];
    u8* unk798;
    u8* unk79c;
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
extern "C" char D_004EC440[];

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

extern "C" const LibRecord504AA0 D_00504AA0[];

/** Starting values of LibValueTable::values, falling from 850 to 1. */
extern "C" const u16 D_00501D30[LIB_VALUE_TABLE_COUNT];

/** Item types func_0040BF50 picks from, one row per LibGameStateRecord0C ID minus one; zero entries are skipped. */
extern "C" const u16 D_00501EE0[][LIB_RECORD0C_ITEM_TYPE_COUNT];

/** Fol paid by func_0040C4C0, indexed by a record's place plus an offset for how few records are ranked. */
extern "C" const u16 D_005055D0[];

/** Factor values, ended by a zero factor. */
extern "C" const LibFactorValue D_005055A0[];

/** LibGameStateTimer::bitset_mask for each catalog category. */
extern "C" const u16 D_005055C0[];

/** Eleven codes; func_0040B360 maps a code to its one-based position here. */
extern "C" const u8 D_00505620[11];

/** Starting word of each LibGameStateRecord0C below LIB_GAME_STATE_RECORD0C_FIXED_ID; all zero in the shipped data. */
extern "C" const u16 D_00505630[];

/** Starting values of the LibGameStateRecord34 entries. */
extern "C" const LibGameStateInitial34 D_00505670[];

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
    LibFactorCounts* counts =
        &reinterpret_cast<LibSystemSettings*>(resident_find_entry(resident_get_entry_table(resident_get_system()), LIB_ENTRY_SYSTEM_SETTINGS))->factor_counts;

    for (s32 i = 0; i < 8; i++)
    {
        s32 factor = func_0040D930(record, i);

        if (factor)
        {
            lib_factor_count_lower(counts, (u16)factor);
        }
    }
}

/**
 * @brief Raise the stored count of each of an allocation's factors by one.
 * @param record Allocation record whose factors are counted.
 */
static inline void raise_factor_counts(const ItemCreationAllocationRecord* record)
{
    LibFactorCounts* counts =
        &reinterpret_cast<LibSystemSettings*>(resident_find_entry(resident_get_entry_table(resident_get_system()), LIB_ENTRY_SYSTEM_SETTINGS))->factor_counts;

    for (s32 i = 0; i < 8; i++)
    {
        s32 factor = func_0040D930(record, i);

        if (factor)
        {
            lib_factor_count_raise(counts, (u16)factor);
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
        table->values[i] = D_00501D30[i];
        table->order[i] = i == 0 ? LIB_VALUE_TABLE_COUNT : i;
    }

    return resident_store_entry(resident_get_entry_table(resident_get_system()), table, LIB_ENTRY_VALUE_TABLE);
}

/**
 * @brief Read the five-bit unk14 field of a D_00504AA0 factor record.
 * @param id One-based record ID, below 0x2C0.
 * @return The field, or zero for an invalid ID.
 */
s32 func_0040B2F0(u16 id)
{
    s32 value = 0;

    if (id > 0 && id < 0x2C0)
    {
        value = D_00504AA0[id - 1].unk14;
    }

    return value;
}

/**
 * @brief Look up one of the eleven codes at D_00505620 by its one-based position.
 * @param id One-based position, 1 to 11.
 * @return The code, or zero for an invalid position.
 */
s32 func_0040B330(s32 id)
{
    s32 code = 0;

    if (id > 0 && id < 12)
    {
        code = D_00505620[id - 1];
    }

    return code;
}

/**
 * @brief Find a code's one-based position in the eleven codes at D_00505620.
 * @param code Code to look for.
 * @return The last matching position, or zero when the code isn't listed.
 */
s32 func_0040B360(s32 code)
{
    s32 id = 0;
    const u8* entry = D_00505620;

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

        if (!resident_archive_read_resource(archive, buffer, LIB_GAME_DATA_RESOURCE, 0))
        {
            return 0;
        }

        data = buffer;
    }

    if (!resident_decode_resource_block(resident_system_get_decoder(resident_get_system()), reinterpret_cast<ResidentResourceHeader*>(data), D_001B64F0, 0))
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

    const u16* value = D_00505630;
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

    const LibGameStateInitial34* initial = D_00505670;
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
 * listed item type from its D_00501EE0 row and list their IDs in unk11760.
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
            const u16* source = D_00501EE0[index];
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

    start_timer(free_timer, item_type, D_005055C0[D_001B64F0[item_type - 1].category]);
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
 * @brief Add a D_005055D0 payout for each ranked LibGameStateRecord0C with unk08 of at least 2 to the stored Fol.
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
            total += D_005055D0[offset + (record->unk07 - 1)];
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
 * @brief Add up the D_005055A0 values of an allocation's factors.
 * @param record Allocation record.
 * @return The total, at most 100; 100 when the factors add nothing and the allocation isn't equipped.
 */
s32 func_0040D680(const ItemCreationAllocationRecord* record)
{
    s32 total = 0;

    for (s32 i = 0; i < 8; i++)
    {
        u16 factor = func_0040D930(record, i);
        const LibFactorValue* entry = D_005055A0;
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
            price += D_00504AA0[factor - 1].price;
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
    object->files[0].name = D_004EC440;
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

/** @brief Allocate the head node and start empty. */
LibClass1721E0::LibClass1721E0()
{
    head = new (0) LibValueNode;

    if (head == 0)
    {
        throw;
    }

    head->next = 0;
    count = 0;
}

/** @brief Delete every node, then the head node. */
LibClass1721E0::~LibClass1721E0()
{
    func_00411D50(this);

    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

/**
 * @brief Append a value at the tail of a list.
 * @param list List to extend.
 * @param value Value to append.
 */
extern "C" void func_00411CC0(LibValueList* list, void* value)
{
    LibValueNode* node = new (0) LibValueNode;

    if (node != 0)
    {
        LibValueNode* tail;
        node->value = value;
        node->next = 0;
        tail = list->head;

        while (tail->next != 0)
        {
            tail = tail->next;
        }

        tail->next = node;
        list->count++;
    }
}

/**
 * @brief Delete every node after the head node and reset the count.
 * @param list List to clear.
 */
extern "C" void func_00411D50(LibValueList* list)
{
    LibValueNode* node = list->head->next;

    if (node == 0)
    {
        return;
    }

    while (node != 0)
    {
        LibValueNode* next = node->next;
        delete node;
        node = next;
    }

    list->head->next = 0;
    list->count = 0;
}

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

/** @brief Destroy the panel. */
LibClass1722E0::~LibClass1722E0()
{
}

/** @brief Called once the position reaches the target; the base version does nothing. */
void LibMovementState::on_arrived()
{
}

/**
 * @brief Update the aggregate index; the base does nothing.
 * @param index Requested index.
 */
void LibClass1723F0::func_00412C10(s32 index)
{
}

/**
 * @brief Update the aggregate float setting; the base does nothing.
 * @param value Requested setting.
 */
void LibClass1723F0::func_00412C20(float value)
{
}

/**
 * @brief Read the aggregate float setting.
 * @return Zero in the base.
 */
float LibClass1723F0::func_00412C30()
{
    return 0.0f;
}

/**
 * @brief Run the default container state hook; the base does nothing.
 * @param first First update flag.
 * @param second Second update flag.
 * @param third Third update flag.
 */
void LibContainer::func_00412C40(u32 first, u32 second, u32 third)
{
}

/** @brief Destroy the aggregate and the container. */
LibClass172320::~LibClass172320()
{
}

/** @brief Release the widget storage and destroy its base. */
ItemCreationClass1746A0::~ItemCreationClass1746A0()
{
}

/** @brief Destroy the indicator. */
LibListIndicator::~LibListIndicator()
{
}

/** @brief Release the widget storage and destroy its bases. */
ItemCreationClass175030::~ItemCreationClass175030()
{
}

/** @brief Release the widget storage and destroy its base. */
ItemCreationClass172600::~ItemCreationClass172600()
{
}

/** @brief Release the widget storage and destroy its base. */
ItemCreationClass172870::~ItemCreationClass172870()
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00412FE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00412FF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00413000);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00413010);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00413020);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00413460);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004135D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00413750);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004138E0);

/**
 * @brief Point the aggregate's list indicator at its scroll position, as a percentage.
 * @param aggregate Widget aggregate.
 */
extern "C" void func_00413BB0(LibClass1723F0* aggregate)
{
    aggregate->unk138.set_position(100.0f * (aggregate->unk2f0 + aggregate->unk304 * aggregate->unk2c4) /
                                   (aggregate->unk2fc * aggregate->unk2c4));
}

/**
 * @brief Set the aggregate's list up for a number of entries and pages, and remember where its parts start.
 * @param aggregate Widget aggregate.
 * @param count Entry count.
 * @param per_page Entries per page.
 * @param visible Pages shown at once.
 * @param x First value for unk2c0.
 * @param y Second value for unk2c4.
 * @param z Third value for unk2c8.
 */
extern "C" void func_00413C00(LibClass1723F0* aggregate, s32 count, s32 per_page, s32 visible, float x, float y, float z)
{
    aggregate->unk2f8 = count;
    aggregate->unk310 = per_page;
    aggregate->unk311 = visible;
    aggregate->unk2c0 = x;
    aggregate->unk2c4 = y;
    aggregate->unk2c8 = z;
    aggregate->unk2fc = (count + per_page - 1) / per_page;
    aggregate->unk300 = aggregate->unk2fc - visible;

    if (aggregate->unk300 < 0)
    {
        aggregate->unk300 = 0;
    }

    aggregate->unk304 = 0;
    aggregate->unk312 = 0;
    aggregate->unk30c = -1;
    aggregate->unk308 = -1;
    aggregate->unk2cc = aggregate->unk190.position.x;
    aggregate->unk2d0 = aggregate->unk190.position.y;
    aggregate->unk2d4 = aggregate->unk20c.unk18.unk00;
    aggregate->unk2d8 = aggregate->unk20c.unk18.unk04;
    aggregate->unk2dc = aggregate->unk20c.unk18.unk08;
    aggregate->unk2e0 = aggregate->unk260.unk18.unk00;
    aggregate->unk2e4 = aggregate->unk260.unk18.unk04;
    aggregate->unk2e8 = aggregate->unk260.unk18.unk08;
    aggregate->unk315 = 0;
    aggregate->unk2f4 = 3;
    aggregate->unk317 = 0;
    aggregate->unk318 = 0;
}

/** @brief Destroy the widget. */
LibObject172410::~LibObject172410()
{
}

void LibWidget::func_00413D20()
{
}

// TODO: Declared here with a u8 variant: the definition in text_0045AD10 only matches with an s32 one, and this
// caller only matches loading the ID before the variant.
extern "C" void func_00463DD0(LibDrawWidget* widget, u16 id, u8 variant);

/**
 * @brief Lay the item code widget's text out off screen and measure it.
 * @param object Item code widget to measure.
 * @return Extent of the laid-out text.
 */
extern "C" LibTextExtent* func_00413D30(LibObject172410* object)
{
    LibDrawRecord records[0x40];
    object->begin_layout(records, 0.0f);
    func_00463DD0(object, object->unkfc, object->unkfe);
    object->func_004637A0(records, object->record_count);
    object->align_records_vertically(records, object->record_count);
    return &object->extent;
}

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

/**
 * @brief Read one of an item definition's eight factor IDs.
 * @param definition Item definition.
 * @param index Factor slot, 0 through 7.
 * @return Factor ID, or zero for an empty slot.
 */
static inline u16 definition_factor(const ItemCreationCategoryDefinition* definition, s32 index)
{
    u16 factor;

    switch (index)
    {
    case 0:
        factor = definition->initial_factor;
        break;
    case 1:
        factor = definition->factor1;
        break;
    case 2:
        factor = definition->factor2;
        break;
    case 3:
        factor = definition->factor3;
        break;
    case 4:
        factor = definition->factor4;
        break;
    case 5:
        factor = definition->factor5;
        break;
    case 6:
        factor = definition->factor6;
        break;
    case 7:
        factor = definition->final_factor;
        break;
    }

    return factor;
}

/**
 * @brief Calculate an item type's catalog price: its base price plus the price of each of its factors.
 * @param record Item type's category record.
 * @return The price, at most 99999999.
 */
u32 func_00414130(const ItemCreationCategoryRecord* record)
{
    const ItemCreationCategoryDefinition* definition = &D_001B64F0[record->catalog_index];
    u32 price = definition->base_price;

    for (s32 i = 0; i < 8; i++)
    {
        u16 factor = definition_factor(definition, i);

        if (factor)
        {
            price += D_00504AA0[factor - 1].price;
        }
    }

    if (price > 99999999)
    {
        price = 99999999;
    }

    return price;
}

/** @brief Destroy the widget. */
LibObject172440::~LibObject172440()
{
}

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

/** @brief Stop the sound stream, or restore the volume, if the stream started either. */
void LibMovieStream::stop_sound()
{
    if (kind != 0 && unk31 != 0)
    {
        if (kind == LIB_MOVIE_STREAM_KIND_1)
        {
            resident_sound_stop_stream(sound);
        }
        else
        {
            resident_sound_restore_volume(sound);
        }
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004144F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004149B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00414AC0);

// TODO: The constructor inlines reset, an ordinary function, so I think the unit was built with auto-inlining, as
// text_00419A70 seems to be. This scoped pragma stands in for it until the flags are settled.
#pragma push
#pragma auto_inline on

/** @brief Clear the stream's read state for a new movie. */
void LibMovieStream::reset()
{
    position = 0;
    fill = 0;
    size = LIB_MOVIE_STREAM_DATA_SIZE;
    total = 0;
    unk20 = 0;
    kind = 0;
    unk28 = 0;
    unk33 = 0;
    unk31 = 0;
    unk32 = 0;
}

/** @brief Free the data buffer. */
LibMovieStream::~LibMovieStream()
{
    delete data;
}

/** @brief Allocate the stream's data buffer and clear its state. */
LibMovieStream::LibMovieStream()
{
    unk08 = 0;
    kind = 0;
    unk24 = 0;
    unk28 = 0;
    data = new (0) u8[LIB_MOVIE_STREAM_DATA_SIZE];
    reset();
}

#pragma pop

/**
 * @brief Take up to a size from the buffer's fill.
 * @param buffer Stream buffer.
 * @param size Bytes wanted.
 * @return Bytes taken.
 */
extern "C" s32 func_00414CE0(LibMovieStreamBuffer* buffer, s32 size)
{
    s32 taken = buffer->fill < size ? buffer->fill : size;
    buffer->fill -= taken;
    return taken;
}

/**
 * @brief Add up to a size to the buffer's fill and advance its position, wrapping at its size.
 * @param buffer Stream buffer.
 * @param size Bytes that arrived.
 * @return Bytes added.
 */
extern "C" s32 func_00414D30(LibMovieStreamBuffer* buffer, s32 size)
{
    s32 space = buffer->size - buffer->fill;
    s32 added = space < size ? space : size;
    buffer->position = (buffer->position + added) % buffer->size;
    buffer->fill += added;
    return added;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00414DB0);

/** libmpeg's timestamp callback data. */
struct LibMpegTimeStampData
{
    s32 type;
    u8 unk04[4];
    s64 pts;
    s64 dts;
};

extern "C" void func_004166F0(LibMovieRing* ring, LibMovieTimeStamp* stamp);

/**
 * @brief libmpeg callback that supplies the timestamps of the data the IPU is decoding.
 * @param mpeg libmpeg decoder; unused.
 * @param data Timestamp callback data that receives the timestamps.
 * @param user Decoder the callback was registered for.
 * @return Always 1.
 */
extern "C" s32 func_00414FB0(void* mpeg, void* data, void* user)
{
    LibMpegTimeStampData* timestamps = static_cast<LibMpegTimeStampData*>(data);
    LibMovieTimeStamp stamp;
    func_004166F0(static_cast<LibMovieDecoder*>(user), &stamp);
    timestamps->pts = stamp.pts;
    timestamps->dts = stamp.dts;
    return 1;
}

extern "C" void func_00416D60(LibMovieRing* ring);

/**
 * @brief libmpeg callback that restarts the IPU's DMA from the decoder's saved state.
 * @param mpeg libmpeg decoder; unused.
 * @param data Callback data; unused.
 * @param user Decoder the callback was registered for.
 * @return Always 1.
 */
extern "C" s32 func_00414FF0(void* mpeg, void* data, void* user)
{
    func_00416D60(static_cast<LibMovieDecoder*>(user));
    return 1;
}

extern "C" void func_00417460(LibMovieRing* ring);

/**
 * @brief libmpeg callback that stops the IPU's DMA and saves its state in the decoder.
 * @param mpeg libmpeg decoder; unused.
 * @param data Callback data; unused.
 * @param user Decoder the callback was registered for.
 * @return Always 1.
 */
extern "C" s32 func_00415010(void* mpeg, void* data, void* user)
{
    func_00417460(static_cast<LibMovieDecoder*>(user));
    return 1;
}

/**
 * @brief libmpeg background callback; nothing to do.
 * @param mpeg libmpeg decoder; unused.
 * @param data Callback data; unused.
 * @param user Decoder the callback was registered for; unused.
 * @return Always 1.
 */
s32 func_00415030(void* mpeg, void* data, void* user)
{
    return 1;
}

extern "C"
{
    /**
     * @brief Abort the picture libmpeg is decoding.
     * @param mpeg libmpeg decoder.
     */
    void sceMpegGetPictureAbort(void* mpeg);

    /** @brief Feed the decoder from the stream thread's side. */
    void func_00417740(LibMovieDecoder* decoder);
}

/**
 * @brief libmpeg callback while it waits for data: abort on START when the decoder allows skipping, otherwise count
 * the calls with nothing buffered, wake the feeding thread and feed the decoder.
 * @param mpeg libmpeg decoder.
 * @param data Callback data; unused.
 * @param user Decoder the callback was registered for.
 * @return Always 1.
 */
extern "C" s32 func_00415040(void* mpeg, void* data, void* user)
{
    LibMovieDecoder* decoder = static_cast<LibMovieDecoder*>(user);
    s32 buffered;

    if (decoder->unk15E644 != 0 && resident_pad_get_held(resident_system_get_input(resident_get_system()), 0) & 8)
    {
        sceMpegGetPictureAbort(mpeg);
        return 1;
    }

    {
        LibSemaphoreLock lock(&decoder->semaphore);
        buffered = (decoder->unkC999C & ~0x7FF) + decoder->unkC9998 * 0x800;
    }

    if (buffered == 0)
    {
        decoder->unk15E64C++;
    }
    else
    {
        decoder->unk15E64C = 0;
    }

    resident_thread_wake(decoder->thread);
    func_00417740(decoder);
    return 1;
}

/**
 * @brief libmpeg error callback; errors are ignored.
 * @param mpeg libmpeg decoder; unused.
 * @param data Callback data; unused.
 * @param user Decoder the callback was registered for; unused.
 * @return Always 0.
 */
s32 func_004152B0(void* mpeg, void* data, void* user)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_004152C0);

extern "C" s32 sceMpegReset(void* mpeg);

extern "C" void func_00418020(LibMovieRing* ring);

extern "C" void func_00419110(LibMovieState* state);

/**
 * @brief Reset libmpeg, the ring, the decoder state and the stream buffer for a new movie.
 * @param decoder Decoder to reset.
 * @return Always 0.
 */
extern "C" s32 func_004159E0(LibMovieDecoder* decoder)
{
    sceMpegReset(decoder->mpeg);
    decoder->unk15E658 = 0;
    func_00418020(decoder);
    func_00419110(decoder->state);
    decoder->input.position = 0;
    decoder->input.fill = 0;
    decoder->unk15E64C = 0;
    decoder->unk15E654 = 0;
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00415A70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00415D30);

extern "C" void func_00415A70(LibMovieDecoder* decoder);

/**
 * @brief Restart decoding from the stream buffer, wait until a decoded frame has been taken, then mark the decoder
 * stopped.
 * @param decoder Decoder to restart.
 */
extern "C" void func_00415E70(LibMovieDecoder* decoder)
{
    func_00418020(decoder);
    func_00419110(decoder->state);
    decoder->input.position = 0;
    decoder->input.fill = 0;
    decoder->unk15E64C = 0;
    func_00415A70(decoder);

    s32 ready;

    do
    {
        ready = decoder->state->ready_count;
    } while (ready >= LIB_MOVIE_FRAME_COUNT);

    decoder->stopped = 3;
}

/** Four bytes of MPEG start code, copied as one value. */
struct LibMpegCode
{
    u8 bytes[4];
};

/** MPEG sequence end code (00 00 01 B7). */
extern "C" LibMpegCode D_001B61A0;

extern "C" void func_00417D30(LibMovieRing* ring, s32 amount);

extern "C" void func_00417E50(LibMovieRing* ring, u8** first, s32* first_size, u8** second, s32* second_size);

// TODO: func_00415D30 is the out-of-line copy of this, which the stream callbacks call; LibMovieDecoder::end_stream
// inlines it. This body gives the inlined copy, but its out-of-line copy doesn't keep first_size - head_size in a
// register the way func_00415D30 does, so the two aren't one function yet.
/**
 * @brief Copy a header and a body into the two parts of a ring buffer's free space.
 * @param first Start of the free space.
 * @param first_size Size of the part before the end of the ring.
 * @param second Start of the ring, for the part that wraps.
 * @param second_size Size of the wrapped part.
 * @param head Header bytes.
 * @param head_size Header size.
 * @param body Body bytes.
 * @param body_size Body size.
 * @return Bytes written, or 0 when they don't fit.
 */
static inline s32 lib_movie_ring_write(u8* first, s32 first_size, u8* second, s32 second_size, const u8* head,
                                       s32 head_size, const u8* body, s32 body_size)
{
    if (first_size + second_size < head_size + body_size)
    {
        return 0;
    }

    if (first_size <= head_size)
    {
        memcpy_guess(first, head, first_size);
        memcpy_guess(second, head + first_size, head_size - first_size);
        memcpy_guess(second + head_size - first_size, body, body_size);
    }
    else if (body_size >= first_size - head_size)
    {
        memcpy_guess(first, head, head_size);
        memcpy_guess(first + head_size, body, first_size - head_size);
        memcpy_guess(second, body + first_size - head_size, body_size - (first_size - head_size));
    }
    else
    {
        memcpy_guess(first, head, head_size);
        memcpy_guess(first + head_size, body, body_size);
    }

    return head_size + body_size;
}

/**
 * @brief Round unkC999C up to a whole 0x800-byte sector while holding its semaphore.
 * @param ring Ring to update.
 */
static inline void lib_movie_align_fill(LibMovieRing* ring)
{
    LibSemaphoreLock lock(&ring->semaphore);
    ring->unkC999C = (ring->unkC999C + 0x7FF) / 0x800 * 0x800;
}

/**
 * @brief Write an MPEG sequence end code into the ring buffer once, then round the fill up to a sector.
 * @return 1 when the end code was written, 0 when it already was or there is no room.
 */
s32 LibMovieDecoder::end_stream()
{
    u8* first;
    u8* second;
    // TODO: The original probably initialised a local array; MWCC copies such an initialiser from small data the
    // same way, but Lib's small data is in main, so this copies main's copy by name.
    LibMpegCode end_code = D_001B61A0;
    s32 first_size;
    s32 second_size;

    if (stopped == 2)
    {
        return 0;
    }

    func_00417E50(this, &first, &first_size, &second, &second_size);

    if (first_size + second_size < 4)
    {
        return 0;
    }

    u8* first_uncached = (u8*)((u32)first | UNCACHED_SEGMENT);
    u8* second_uncached = (u8*)((u32)second | UNCACHED_SEGMENT);
    func_00417D30(this, lib_movie_ring_write(first_uncached, first_size, second_uncached, second_size, end_code.bytes, 4, 0, 0));
    lib_movie_align_fill(this);

    if (stopped == 0)
    {
        stopped = 2;
    }

    return 1;
}

/**
 * @brief Queue the timestamps of stream data that just arrived in the ring buffer.
 * @param pts Presentation timestamp.
 * @param dts Decoding timestamp.
 * @param data Start of the data in the ring buffer.
 * @param length Length of the data.
 * @return 0 when the queue is full, otherwise 1.
 */
s32 LibMovieDecoder::add_timestamp(s64 pts, s64 dts, u8* data, s32 length)
{
    LibMovieTimeStamp stamp;
    stamp.pts = pts;
    stamp.dts = dts;
    stamp.position = data - sectors[0];
    stamp.length = length;
    return LibMovieRing::push_timestamp(&stamp);
}

extern "C" s32 sceMpegAddStrCallback(void* mpeg, s32 type, s32 channel, s32 (*callback)(void*, void*, void*),
                                     void* data);

/**
 * @brief Register a libmpeg stream callback on the decoder's libmpeg state.
 * @param decoder Decoder to register on.
 * @param type libmpeg stream type.
 * @param channel Stream channel.
 * @param callback Callback to run.
 * @param data Value passed to the callback.
 */
extern "C" void func_00416200(LibMovieDecoder* decoder, s32 type, s32 channel, s32 (*callback)(void*, void*, void*),
                              void* data)
{
    sceMpegAddStrCallback(decoder->mpeg, type, channel, callback, data);
}

extern "C" s32 sceMpegDelete(void* mpeg);

/** @brief Delete libmpeg's state, its work area and the decoder state. */
LibMovieDecoder::~LibMovieDecoder()
{
    sceMpegDelete(mpeg);
    delete mpeg_work;
    delete state;
}

/** libmpeg callback: the decoder, its callback data and the value it was registered with. */
typedef s32 (*LibMpegCallback)(void* mpeg, void* data, void* user);

/** libmpeg callback types. */
enum
{
    LIB_MPEG_CB_ERROR = 0,
    LIB_MPEG_CB_NODATA = 1,
    LIB_MPEG_CB_STOP_DMA = 2,
    LIB_MPEG_CB_RESTART_DMA = 3,
    LIB_MPEG_CB_BACKGROUND = 4,
    LIB_MPEG_CB_TIMESTAMP = 5
};

extern "C"
{
    s32 sceMpegCreate(void* mpeg, u8* work, s32 size);

    LibMpegCallback sceMpegAddCallback(void* mpeg, s32 type, LibMpegCallback callback, void* user);
}

/**
 * @brief Create libmpeg's state for a frame size, with a work area to match, and register the decoder's callbacks.
 * @param decoder Decoder to set up.
 * @param width Frame width in pixels.
 * @param height Frame height in pixels.
 */
extern "C" void func_004162F0(LibMovieDecoder* decoder, s32 width, s32 height)
{
    s32 work_size = width * height * 9 / 2 + 0x176C;
    decoder->width = width;
    decoder->height = height;
    decoder->mpeg_work = new (0) u8[work_size];
    sceMpegCreate(decoder->mpeg, decoder->mpeg_work, work_size);
    sceMpegAddCallback(decoder->mpeg, LIB_MPEG_CB_ERROR, func_004152B0, decoder);
    sceMpegAddCallback(decoder->mpeg, LIB_MPEG_CB_NODATA, func_00415040, decoder);
    sceMpegAddCallback(decoder->mpeg, LIB_MPEG_CB_STOP_DMA, func_00415010, decoder);
    sceMpegAddCallback(decoder->mpeg, LIB_MPEG_CB_RESTART_DMA, func_00414FF0, decoder);
    sceMpegAddCallback(decoder->mpeg, LIB_MPEG_CB_TIMESTAMP, func_00414FB0, decoder);
    sceMpegAddCallback(decoder->mpeg, LIB_MPEG_CB_BACKGROUND, func_00415030, decoder);
}

/**
 * @brief Replace the decoder's state, deleting the old one.
 * @param decoder Decoder to update.
 * @param state New state.
 */
extern "C" void func_00416450(LibMovieDecoder* decoder, LibMovieState* state)
{
    delete decoder->state;
    decoder->state = state;
}

/**
 * @brief Delete the decoder's state.
 * @param decoder Decoder to update.
 */
extern "C" void func_004164B0(LibMovieDecoder* decoder)
{
    delete decoder->state;
    decoder->state = 0;
}

/** @brief Initialize the decoder. */
LibMovieDecoder::LibMovieDecoder()
{
    input.position = 0;
    input.fill = 0;
    input.size = LIB_MOVIE_STREAM_BUFFER_SIZE;
    unk15E645 = 1;
    TIMER0_MODE = TIMER_MODE_CLOCK_HBLANK | TIMER_MODE_COUNT_ENABLE;
    unk15E658 = 0;
    unk15E644 = 1;
    stopped = 0;
    state = new (0) LibMovieState;
}

/**
 * @brief Round unkC999C up to a whole 0x800-byte sector while holding the semaphore.
 * @return Always 0.
 */
s32 LibMovieRing::end_stream()
{
    LibSemaphoreLock lock(&semaphore);
    unkC999C = (unkC999C + 0x7FF) / 0x800 * 0x800;
    return 0;
}

/**
 * @brief Find the timestamps of the data the IPU is decoding and mark them used, while holding the semaphore.
 * @param ring Ring whose queue is searched.
 * @param stamp Receives the timestamps, or -1 for both when no queued data covers the IPU's position.
 */
extern "C" void func_004166F0(LibMovieRing* ring, LibMovieTimeStamp* stamp)
{
    u32 madr = *D4_MADR;
    u32 bp = *IPU_BP;
    s32 bit = ring->saved_ipu_bp & 0x7F;
    u32 address = madr - (((bp >> 16) & 3) + ((bp >> 8) & 0xF)) * 16;
    s32 ring_bytes = ring->ring_sectors * 0x800;
    s32 found = 0;
    LibSemaphoreLock lock(&ring->semaphore);
    u32 position = address + (bit >> 3);
    stamp->pts = -1;
    stamp->dts = -1;
    s32 offset = (ring_bytes + position - (u32)ring->sectors) % ring_bytes;
    s32 count = ring->timestamp_count;
    s32 write = ring->timestamp_write;

    for (s32 i = 0; i < count && !found; i++)
    {
        s32 index = (i + (ring->timestamp_capacity + (write - count))) % ring->timestamp_capacity;
        s32 length = ring->timestamps[index].length;
        s32 covered = (offset + ring_bytes - ring->timestamps[index].position) % ring_bytes < length;

        if (covered)
        {
            stamp->pts = ring->timestamps[index].pts;
            stamp->dts = ring->timestamps[index].dts;
            ring->timestamps[index].pts = -1;
            ring->timestamps[index].dts = -1;
            found = 1;
            ring->timestamp_count = ring->timestamp_count > 1 ? 1 : ring->timestamp_count;
        }
    }
}

extern "C" void func_00416BC0(LibMovieRing* ring, LibMovieTimeStamp* stamp);

/**
 * @brief Add timestamps to the queue while holding the semaphore.
 * @param stamp Timestamps to add; the entry is skipped when both are negative.
 * @return 0 when the queue is full, otherwise 1.
 */
s32 LibMovieRing::push_timestamp(LibMovieTimeStamp* stamp)
{
    s32 added = 0;
    LibSemaphoreLock lock(&semaphore);

    if (timestamp_count < timestamp_capacity)
    {
        func_00416BC0(this, stamp);

        if (stamp->pts >= 0 || stamp->dts >= 0)
        {
            timestamps[timestamp_write].pts = stamp->pts;
            timestamps[timestamp_write].dts = stamp->dts;
            timestamps[timestamp_write].position = stamp->position;
            timestamps[timestamp_write].length = stamp->length;
            timestamp_count++;
            timestamp_write = (timestamp_write + 1) % timestamp_capacity;
        }

        added = 1;
    }

    return added;
}

/**
 * @brief Shorten the oldest queued timestamps whose data new stream data has overwritten in the ring buffer.
 * @param ring Ring whose queue is trimmed.
 * @param stamp Timestamps of the new data.
 */
extern "C" void func_00416BC0(LibMovieRing* ring, LibMovieTimeStamp* stamp)
{
    s32 index = (ring->timestamp_capacity + (ring->timestamp_write - ring->timestamp_count)) % ring->timestamp_capacity;
    s32 ring_bytes = ring->ring_sectors * 0x800;
    s32 more = 1;

    if (ring->timestamp_count > 0)
    {
        do
        {
            LibMovieTimeStamp* entry = &ring->timestamps[index];

            if (entry->length == 0 || stamp->length == 0)
            {
                break;
            }

            s32 overlaps = (entry->position + ring_bytes - stamp->position) % ring_bytes < stamp->length;

            if (overlaps)
            {
                s32 overlap = stamp->position + stamp->length - entry->position;
                overlap = overlap < entry->length ? overlap : entry->length;
                entry->position = (entry->position + overlap) % ring_bytes;
                entry->length -= overlap;

                if (entry->length == 0)
                {
                    if (entry->pts >= 0)
                    {
                        entry->pts = -1;
                        entry->dts = -1;
                        entry->position = 0;
                        entry->length = 0;
                    }

                    s32 remaining = ring->timestamp_count - 1;
                    ring->timestamp_count = remaining > 0 ? remaining : 0;
                }
            }
            else
            {
                more = 0;
            }

            index = (index + 1) % ring->timestamp_capacity;
        } while (more);
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00416D60);

/**
 * @brief Stop the IPU's DMA channels and save their registers and the IPU's state while holding the semaphore.
 * Channel 3 is stopped once the IPU's input FIFO has drained.
 * @param ring Ring that keeps the saved registers.
 */
extern "C" void func_00417460(LibMovieRing* ring)
{
    LibSemaphoreLock lock(&ring->semaphore);
    ring->unkC99D0 = 0;

    {
        LibInterruptLock interrupts;
        *D_ENABLEW = *D_ENABLER | D_ENABLE_SUSPEND;
        *D4_CHCR = DMA_CHCR_DIR_FROM_MEMORY | DMA_CHCR_MODE_CHAIN;
        *D_ENABLEW = *D_ENABLER & ~D_ENABLE_SUSPEND;
    }

    ring->saved_d4_madr = *D4_MADR;
    ring->saved_d4_tadr = *D4_TADR;
    ring->saved_d4_qwc = *D4_QWC;
    ring->saved_d4_chcr = *D4_CHCR;

    while (*IPU_CTRL & IPU_CTRL_IFC)
    {
    }

    {
        LibInterruptLock interrupts;
        *D_ENABLEW = *D_ENABLER | D_ENABLE_SUSPEND;
        *D3_CHCR = 0;
        *D_ENABLEW = *D_ENABLER & ~D_ENABLE_SUSPEND;
    }

    ring->saved_d3_madr = *D3_MADR;
    ring->saved_d3_qwc = *D3_QWC;
    ring->saved_d3_chcr = *D3_CHCR;
    ring->saved_ipu_bp = *IPU_BP;
    ring->saved_ipu_ctrl = *IPU_CTRL;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00417740);

/**
 * @brief Add to unkC999C and unkC99D8 while holding its semaphore.
 * @param ring Ring to update.
 * @param amount Amount added to both.
 */
extern "C" void func_00417D30(LibMovieRing* ring, s32 amount)
{
    LibSemaphoreLock lock(&ring->semaphore);
    ring->unkC999C += amount;
    ring->unkC99D8 += amount;
}

/**
 * @brief Find the free space in the ring buffer while holding its semaphore.
 * @param ring Ring to query.
 * @param first Receives the start of the free space.
 * @param first_size Receives the size of the part before the end of the ring.
 * @param second Receives the ring's start when the free space wraps, or null.
 * @param second_size Receives the size of the wrapped part, or 0.
 */
extern "C" void func_00417E50(LibMovieRing* ring, u8** first, s32* first_size, u8** second, s32* second_size)
{
    LibSemaphoreLock lock(&ring->semaphore);
    s32 start = (ring->unkC9994 + ring->unkC9998) * 0x800;
    s32 free = (ring->ring_sectors - 2 - ring->unkC9998) * 0x800;
    s32 offset = (start + ring->unkC999C) % ring->ring_size;
    s32 size = free - ring->unkC999C;
    bool wraps = ring->ring_size - offset < size;

    if (!wraps)
    {
        *first = (u8*)ring->sectors + offset;
        *first_size = size;
        *second = 0;
        *second_size = 0;
    }
    else
    {
        *first = (u8*)ring->sectors + offset;
        *first_size = ring->ring_size - offset;
        *second = ring->sectors[0];
        *second_size = size - (ring->ring_size - offset);
    }
}

/**
 * @brief Empty the ring and its timestamp queue, rebuild the DMA chain that feeds it to the IPU sector by sector, and
 * point DMA channel 4 at the chain, stopped.
 * @param ring Ring to reset.
 */
extern "C" void func_00418020(LibMovieRing* ring)
{
    ring->unkC9994 = 0;
    ring->unkC9998 = 0;
    ring->unkC999C = 0;
    ring->unkC99D0 = 1;
    ring->timestamp_count = 0;
    ring->timestamp_write = 0;

    for (s32 i = 0; i < ring->timestamp_capacity; i++)
    {
        ring->timestamps[i].pts = -1;
        ring->timestamps[i].dts = -1;
        ring->timestamps[i].position = 0;
        ring->timestamps[i].length = 0;
    }

    for (s32 i = 0; i < ring->ring_sectors; i++)
    {
        *(u64*)((u32)ring->tags[i] | UNCACHED_SEGMENT) = DMA_TAG(LIB_MOVIE_SECTOR_SIZE / 16, DMA_TAG_ID_REF, (u8*)ring->sectors + i * LIB_MOVIE_SECTOR_SIZE);
    }

    *(u64*)((u32)ring->tags[ring->ring_sectors] | UNCACHED_SEGMENT) = DMA_TAG(0, DMA_TAG_ID_NEXT, ring->tags);
    *D4_QWC = 0;
    *D4_MADR = (u32)ring->sectors;
    *D4_TADR = (u32)ring->tags;

    {
        LibInterruptLock interrupts;
        *D_ENABLEW = *D_ENABLER | D_ENABLE_SUSPEND;
        *D4_CHCR = DMA_CHCR_DIR_FROM_MEMORY | DMA_CHCR_MODE_CHAIN;
        *D_ENABLEW = *D_ENABLER & ~D_ENABLE_SUSPEND;
    }
}

/** @brief Stop DMA channel 4 and delete the semaphore. */
LibMovieRing::~LibMovieRing()
{
    {
        LibInterruptLock interrupts;
        *D_ENABLEW = *D_ENABLER | D_ENABLE_SUSPEND;
        *D4_CHCR = DMA_CHCR_DIR_FROM_MEMORY | DMA_CHCR_MODE_CHAIN;
        *D_ENABLEW = *D_ENABLER & ~D_ENABLE_SUSPEND;
    }

    *D4_QWC = 0;
    *D4_MADR = 0;
    *D4_TADR = 0;
}

/** @brief Set up an empty ring, its DMA chain and its semaphore. */
LibMovieRing::LibMovieRing()
    : ring_sectors(LIB_MOVIE_RING_SECTORS), ring_size(LIB_MOVIE_RING_SECTORS * 0x800), unkC99D8(0),
      timestamp_capacity(LIB_MOVIE_TIMESTAMP_CAPACITY)
{
    semaphore.create(1, 1);
    func_00418020(this);
}

/**
 * @brief Free the frames that have been shown.
 * @param state Decoder state.
 */
extern "C" void func_004184D0(LibMovieState* state)
{
    for (s32 i = 0; i < LIB_MOVIE_FRAME_COUNT; i++)
    {
        if (state->frame_states[i] == LIB_MOVIE_FRAME_SHOWN)
        {
            state->frame_states[i] = LIB_MOVIE_FRAME_FREE;

            if (state->ready_count > 0)
            {
                state->ready_count--;
            }
        }
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00418540);

/**
 * @brief Find the frame buffer to decode into next.
 * @param state Decoder state.
 * @return The current frame buffer, or null when every frame is waiting to be shown.
 */
extern "C" u8* func_004190C0(LibMovieState* state)
{
    bool full = state->ready_count == state->frame_count;

    if (full)
    {
        return 0;
    }

    return state->frames[state->current];
}

/**
 * @brief Free both frames and restart the frame count for a new movie.
 * @param state Decoder state.
 */
extern "C" void func_00419110(LibMovieState* state)
{
    for (s32 i = 0; i < LIB_MOVIE_FRAME_COUNT; i++)
    {
        state->frame_states[i] = LIB_MOVIE_FRAME_FREE;
    }

    state->unk80B8 = 2;
    state->unk80BC = state->unk80B8;
    state->ready_count = 0;
    state->current = 0;
    state->unk80A8 = 0;
    state->current_frame = 0;
    state->unk80D0 = state->unk80D4;
}

/**
 * @brief Mark the current frame decoded and move on to the other one, with interrupts disabled.
 * @param state Decoder state.
 */
extern "C" void func_004191A0(LibMovieState* state)
{
    LibInterruptLock interrupts;
    state->frame_states[state->current] = LIB_MOVIE_FRAME_READY;
    state->ready_count++;
    state->current = (state->current + 1) % LIB_MOVIE_FRAME_COUNT;
}

/** @brief Free the frame buffers. */
LibMovieState::~LibMovieState()
{
    for (s32 i = 0; i < LIB_MOVIE_FRAME_COUNT; i++)
    {
        delete[] allocations[i];
    }
}

/**
 * @brief Allocate both frame buffers for a frame size, aligned to 64 bytes.
 * @param state Decoder state.
 * @param width Frame width in pixels.
 * @param height Frame height in pixels.
 */
extern "C" void func_00419330(LibMovieState* state, s32 width, s32 height)
{
    for (s32 i = 0; i < LIB_MOVIE_FRAME_COUNT; i++)
    {
        state->allocations[i] = new (0) u8[width * height * 4 + 0x40];
        state->frames[i] = (u8*)(((u32)state->allocations[i] + 0x3F) & ~0x3F);
    }

    state->width = width;
    state->height = height;
}

/** @brief Start with no frame buffers, both frames free, and the default words and scale. */
LibMovieState::LibMovieState()
{
    current = 0;
    ready_count = 0;
    frame_count = LIB_MOVIE_FRAME_COUNT;
    unk80A8 = 0;

    for (s32 i = 0; i < LIB_MOVIE_FRAME_COUNT; i++)
    {
        frame_states[i] = LIB_MOVIE_FRAME_FREE;
        allocations[i] = 0;
    }

    set_words(0x800, 0x800, 1);
    set_scale(1.0f, 1.0f);
    widescreen = 0;
    unk80B8 = 2;
    unk80BC = unk80B8;
    current_frame = 0;
    unk80D4 = 8;
    unk80CC = 0;
}

s32 func_004194F0(void* object)
{
    return 12;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_00419500);
