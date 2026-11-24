#include "include_asm.h"
#include "overlays/lib/scratchpad_texture_cache.h"
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
#include "sdk/main/libc_guess_0013C948.h"
#include "sdk/main/libc_0013C6D0.h"
#include "sdk/main/libc_0013CA60.h"
#include "sdk/main/libkernl_00121940.h"
#include "overlays/lib/text_0044ABE0.h"
#include "clamp.h"
#include "overlays/lib/memory_card.h"
#include "overlays/lib/text_00429B00.h"
#include "overlays/lib/character_record.h"
#include "main/system.h"
#include "main/input.h"

#define LIB_GAME_DATA_RESOURCE 10
#define LIB_GAME_STATE_RECORD0C_FIXED_ID 29
#define LIB_RECORD0C_ITEM_TYPE_COUNT 200
#define LIB_ENTRY_VALUE_TABLE 0x76505730
#define LIB_ICON_SYS_SIZE 0x3C4
#define LIB_SAVE_DATA_SIZE 0x11ABA2
#define LIB_VALUE_TABLE_COUNT 51
#define LIB_CODE_LIST_COUNT 10

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

/** Four-byte factor record of the D_00504AA0 table, indexed by factor ID minus one. */
typedef struct LibRecord504AA0
{
    u32 price : 20;
    u32 unk14 : 5;
    u32 battle_usable : 1;
    u32 unk1a : 2;
    u32 dropped : 1;
    u32 unk1d : 3;
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
/** Settings the save data keeps outside the system settings' checksums. */
struct LibSaveOptions
{
    u8 widescreen;
    u8 sealed_flag;
    u8 extra_flag;
    u8 universe_unlocked;
    u8 unk18D;
    u8 sound_output;
    u8 unk06[2];
    float speaker_angles[4];
};

/** Start of the save data: the CRCs that check it and the other save files. */
struct LibSaveDataHeader
{
    char title[0x10];
    u32 data_crc;
    u32 extra_data_crc;
    u32 icon_sys_crc;
    u32 unk980_crc;
};

/**
 * @brief Compute a CRC-32 (polynomial 0x04C11DB7, most significant bit first).
 * @param data Bytes.
 * @param size Byte count.
 * @return The CRC.
 */
static inline u32 lib_crc32(const u8* data, s32 size)
{
    u32 crc = 0xFFFFFFFF;

    for (s32 i = 0; i < size; i++)
    {
        crc ^= data[i] << 24;

        for (s32 bit = 0; bit < 8; bit++)
        {
            if (crc & 0x80000000)
            {
                crc = (crc << 1) ^ 0x4C11DB7;
            }
            else
            {
                crc <<= 1;
            }
        }
    }

    return ~crc;
}

struct LibClass1721B0 : public LibListObject
{
    /** @brief Start idle with no card, empty file and ID lists, and the save directory name. */
    LibClass1721B0();

    /** @brief Free the flag storage and the value list, then detach. */
    virtual ~LibClass1721B0();

    /**
     * @brief Report the list kind.
     * @return Four.
     */
    virtual s32 get_default_list_kind();

    /** @brief Free the buffers and the memory card object, then queue this object for release. */
    virtual void destroy();

    /** @brief Run the save. */
    virtual void update();

    LibMemoryCard* card;
    s16 unk18;
    s16 unk1a;
    s16 unk1c;
    s16 unk1e;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    u8 unk26[2];
    LibSystemSettings* settings;
    LibClass1721E0 values;
    u16 id_count;
    s16 ids[0x21];
    u8* unk7c;
    LibIconSys* icon_sys;
    LibCardFileBuffer files[37];
    LibCardFileRequest request;
    u8 unk2e4[0x4B4];
    u8* unk798;
    u8* unk79c;
    char directory[0x40];
    u8 entry_buffer[0x80];
    LibCardDirectoryEntry* entry;
    LibBitArray flags;
    u16 unk878;
    s16 unk87a;
    s32 result;
    u8 unk880;
    u8 unk881[3];
    u8* unk884;
    s32 unk888;
    u8 unk88c[0x40];
    u8 unk8cc;
    u8 unk8cd[3];
    u32 unk8d0;
    u8 unk8d4;
    u8 unk8d5[3];
    LibIconSys* unk8d8;
    u8 unk8dc[0x2E];
    u8 unk90a;
    u8 unk90b;
    u8 unk90c[4];
    u8* unk910;
    LibSaveOptions options;
    LibSaveDataHeader header;
    u8 unk94c[0x20];
    s32 unk96c;
    u8 unk970;
    u8 unk971[3];
    s32 unk974;
    u32 unk978;
    s32 unk97c;
    u8* unk980;
    u32 unk984;
    u32 unk988;
    u8 unk98c;
};

/** The icon.sys file name. */
extern "C" char D_004EC440[];

extern "C" char D_004EC3C0[];

extern "C" const char D_004EC340[];

extern "C" const char D_005056E0[];

extern "C" const u8 D_004EC480[];

extern "C" const u8 D_004EC4C0[];

extern "C" const u8 D_004EC4F0[];

extern "C" const u8 D_004EC520[];

extern "C" char D_004EC400[];

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

/** Code tables that func_0040AFA0 points into its loaded resource. */

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

/** One 0x14-byte record of the checksummed table at D_001B64B8. */
struct LibProtectedStatEntry
{
    u16 unk00;
    u16 unk02;
    u16 unk04;
    u16 unk06;
    u16 unk08;
    u16 checksum;
    u16 unk0c;
    u16 unk0e;
    u8 unk10;
    u8 unk11;
    u8 unk12;
};

extern "C" LibProtectedStatEntry* D_001B64B8;

/**
 * @brief Read a code's record from the table at D_001B64B8, replacing it with random values when its checksum fails,
 * and scale two of its values by the character's maximum MP and HP (as percentages, at least the record's minimums).
 * @param code One-based record code, 1 through 154.
 * @param entry Character record, or null not to scale.
 * @param detail Nonzero to keep the first two values (randomized too) when the checksum fails; otherwise they become 0.
 * @param first Receives value 0x00, or null.
 * @param second Receives value 0x02, or null.
 * @param third Receives value 0x10, or null.
 * @param fourth Receives value 0x11, or null.
 * @param fifth Receives value 0x08, or null.
 * @param sixth Receives value 0x12, or null.
 * @param seventh Receives value 0x04 scaled by the maximum MP, or null.
 * @param eighth Receives value 0x06 scaled by the maximum HP, or null.
 * @return Nonzero when the code is in range.
 */
u8 func_004095C0(s32 code, FieldRecord* entry, void* detail, s32* first, s32* second, s32* third, s32* fourth, s32* fifth,
                 s32* sixth, s32* seventh, s32* eighth)
{
    if (code - 1 < 0 || code - 1 >= 0x9A)
    {
        return 0;
    }

    LibProtectedStatEntry* stat = &D_001B64B8[code - 1];
    s32 value00 = stat->unk00;
    s32 value02 = stat->unk02;
    s32 value04 = stat->unk04;
    s32 value06 = stat->unk06;
    // TODO: value10-12 and min_mp are declared before their loads only because that puts the spill slots and
    // registers in the game's order; I haven't found a more natural shape that does.
    s32 value10;
    s32 value11;
    s32 value12;
    s32 value08 = stat->unk08;
    s32 min_mp;
    s32 min_hp = stat->unk0c;
    min_mp = stat->unk0e;
    value10 = stat->unk10;
    value11 = stat->unk11;
    value12 = stat->unk12;
    bool tampered;

    u16 sum = (value00 + value02 + value06 + value04 + min_hp + min_mp) * 18 + 0x1E99 - (value10 + value11 + value12) -
              code * 0xC1;

    if (sum == stat->checksum)
    {
        tampered = false;
    }
    else
    {
        value11 = resident_random_below(20) + 0x4B;
        value12 = resident_random_below(10) + 0x55;
        value10 = resident_random_below(4) + 0xA;
        tampered = true;
    }

    if (tampered)
    {
        value08 = (resident_next_random_word() & 0xFF) + 0x20;

        if (detail != 0)
        {
            value00 = resident_random_range(0x51, 0x61) + 0x7D;
            value02 = (code - 1) * 2 + 0x3C8;
            value04 = resident_random_range(0x51, 0x62) + 0x292;
            value06 = resident_random_range(0x4F, 0x5D) + 0x103;
        }
        else
        {
            value00 = 0;
            value02 = 0;
        }
    }

    if (entry != 0)
    {
        LibCharacterRecord* record = reinterpret_cast<LibCharacterRecord*>(entry);
        s32 hp_percent = value06;
        s32 mp_percent = value04;
        value06 = value06 * character_max_hp(record) / 100;
        value04 = value04 * character_max_mp(record) / 100;

        if (hp_percent > 0 && value06 <= 0)
        {
            value06 = 1;
        }

        if (mp_percent > 0 && value04 <= 0)
        {
            value04 = 1;
        }

        if (value06 < min_hp)
        {
            value06 = min_hp;
        }

        if (value04 < min_mp)
        {
            value04 = min_mp;
        }
    }

    if (first != 0)
    {
        *first = value00;
    }

    if (second != 0)
    {
        *second = value02;
    }

    if (seventh != 0)
    {
        *seventh = value04;
    }

    if (eighth != 0)
    {
        *eighth = value06;
    }

    if (third != 0)
    {
        *third = value10;
    }

    if (fourth != 0)
    {
        *fourth = value11;
    }

    if (sixth != 0)
    {
        *sixth = value12;
    }

    if (fifth != 0)
    {
        *fifth = value08;
    }

    return 1;
}

/**
 * @brief Point the fifth tactical skill state at one of the anti-attack auras the mask allows.
 *
 * A state already naming an allowed aura is kept. Otherwise the lowest allowed
 * aura is chosen, keeping the old state's sign, or the state is cleared when no
 * aura is allowed.
 * @param equipment Character equipment record.
 */
extern "C" void func_00409A10(LibCharacterEquipment* equipment)
{
    u32 mask = (u8)(equipment->encoded_anti_attack_aura_mask ^ 0x77);
    s32 state = tactical_skill_state(equipment, 4);
    bool negative;
    s32 aura;

    if (mask == 0)
    {
        if (state != 0)
        {
            set_tactical_skill_state(equipment, 4, 0);
        }

        return;
    }

    negative = false;

    if (state <= -1)
    {
        state = -state;
        negative = true;
    }

    if (state != 0 && (mask & (1 << (state - 1))))
    {
        return;
    }

    for (aura = 1;; aura++, mask >>= 1)
    {
        if (mask & 1)
        {
            if (negative)
            {
                aura = -aura;
            }

            set_tactical_skill_state(equipment, 4, aura);
            return;
        }
    }
}

/**
 * @brief Change a character's symbology mastery; outside code lists 2 and 9, adding to it also unlocks the 0x90 and 0x91
 * battle skills for codes in their tables once the character has both masteries. In code lists 2 and 9 the battle skill
 * mastery changes too.
 * @param equipment Character equipment record.
 * @param id One-based code list ID.
 * @param code Code.
 * @param amount Amount to add, or the new mastery.
 * @param replace Nonzero to set the mastery to the amount.
 * @return The changed mastery index (the battle skill's in code lists 2 and 9), or -1 when the list doesn't have the
 *         code.
 */
extern "C" s32 func_00409DA0(LibCharacterEquipment* equipment, s32 id, s32 code, s32 amount, s32 replace)
{
    s32 result = func_0040A9F0(equipment, id, code, 0, amount, replace);

    if (id == 2 || id == 9)
    {
        result = func_0040A9F0(equipment, id, code, 1, amount, replace);
    }
    else if (replace == 0)
    {
        s32 index = func_0040AF10(id, code);

        if (func_0040A9B0(code))
        {
            s32 skill = func_0040AE00(id, 0x90);

            if (skill >= 0 && lib_equipment_symbology_mastery(equipment, index) != 0 &&
                lib_equipment_battle_skill_mastery(equipment, skill) != 0)
            {
                func_0040A520(reinterpret_cast<FieldRecord*>(equipment), id, 0x90, amount, 0);
            }
        }

        if (func_0040A970(code))
        {
            s32 skill = func_0040AE00(id, 0x91);

            if (skill >= 0 && lib_equipment_symbology_mastery(equipment, index) != 0 &&
                lib_equipment_battle_skill_mastery(equipment, skill) != 0)
            {
                func_0040A520(reinterpret_cast<FieldRecord*>(equipment), id, 0x91, amount, 0);
            }
        }
    }

    return result;
}

/**
 * @brief Learn a symbology the character has no mastery of yet.
 * @param equipment Character equipment record.
 * @param id One-based code list ID.
 * @param code Symbology code.
 * @param level Level before learning; the new level is one more, at least one.
 * @return func_00409DA0's result, or -1 when the symbology already has mastery.
 */
extern "C" s32 func_0040A370(LibCharacterEquipment* equipment, s32 id, s32 code, s32 level)
{
    s32 index = func_0040AF10(id, code);

    if (lib_equipment_symbology_mastery(equipment, index) != 0)
    {
        return -1;
    }

    level++;

    if (level <= 0)
    {
        level = 1;
    }

    return func_00409DA0(equipment, id, code, level, 1);
}

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
    func_0040A9F0(reinterpret_cast<LibCharacterEquipment*>(entry), list_id, code, 1, first, second);

    if ((list_id == 2 || list_id == 9) && code > 0 && code < 30)
    {
        func_0040A9F0(reinterpret_cast<LibCharacterEquipment*>(entry), list_id, code, 0, first, second);
    }
}

/**
 * @brief Learn a symbology; codes 0x90 and 0x91 first learn each of their three table codes the character has no mastery of.
 * @param equipment Character equipment record.
 * @param id One-based code list ID.
 * @param code Symbology code.
 * @param level Level before learning; the new level is one more, at least one.
 */
extern "C" void func_0040A5C0(LibCharacterEquipment* equipment, s32 id, s32 code, s32 level)
{
    u32 i;

    level++;

    if (level <= 0)
    {
        level = 1;
    }

    if (code == 0x90)
    {
        for (i = 0; i < 3; i++)
        {
            if (lib_equipment_symbology_mastery(equipment, func_0040AF10(id, D_001B6198[i])) == 0)
            {
                func_0040A9F0(equipment, id, D_001B6198[i], 0, level, 1);
            }
        }
    }
    else if (code == 0x91)
    {
        for (i = 0; i < 3; i++)
        {
            if (lib_equipment_symbology_mastery(equipment, func_0040AF10(id, D_001B619C[i])) == 0)
            {
                func_0040A9F0(equipment, id, D_001B619C[i], 0, level, 1);
            }
        }
    }

    func_0040A520((FieldRecord*)equipment, id, code, level, 1);
}

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

/**
 * @brief Change a character's mastery of a code: a symbology (flag zero) or a battle skill. The mastery is set to the
 * amount, or moved away from zero by it.
 * @param equipment Character equipment record.
 * @param list_id One-based code list ID.
 * @param code Code.
 * @param flag Zero for a symbology, nonzero for a battle skill.
 * @param amount Amount to add, or the new mastery.
 * @param replace Nonzero to set the mastery to the amount.
 * @return The code's mastery index, or -1 when the list doesn't have the code.
 */
s32 func_0040A9F0(LibCharacterEquipment* equipment, s32 list_id, s32 code, s32 flag, s32 amount, s32 replace)
{
    s32 index;
    s32 mastery;

    if (flag == 0)
    {
        index = func_0040AF10(list_id, code);

        if (index == -1)
        {
            return -1;
        }

        mastery = lib_equipment_symbology_mastery(equipment, index);
    }
    else
    {
        index = func_0040AE00(list_id, code);

        if (index == -1)
        {
            return -1;
        }

        mastery = lib_equipment_battle_skill_mastery(equipment, index);
    }

    if (replace != 0)
    {
        mastery = amount;
    }
    else if (mastery >= 0)
    {
        mastery += amount;
    }
    else
    {
        mastery -= amount;
    }

    if (flag == 0)
    {
        store_symbology_mastery(equipment, index, mastery);
    }
    else
    {
        store_battle_skill_mastery(equipment, index, mastery);
    }

    return index;
}

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

/** One section of the game table resource: its offset from the start of the decoded resource and its size. */
struct LibTableSection
{
    u32 offset;
    u32 size;
};

/** Decoded game table resource (archive key 0x42C): a header, then its section list. */
struct LibTableResource
{
    u8 unk00[8];
    LibTableSection sections[13];
};

extern "C" u8* D_001B64B0;
extern "C" u8* D_001B64B4;
extern "C" u8* D_001B64BC;
extern "C" u8* D_001B64C0;
extern "C" u8* D_001B64C4;
extern "C" u8* D_001B64C8;
extern "C" u8* D_001B64D4;
extern "C" u8* D_001B64D8;
extern "C" u8* D_001B64DC;
extern "C" u8* D_001B64E0;
extern "C" u16* D_001B64E4;
extern "C" u8* D_001B64E8;
extern "C" u8 D_001B64A8;
extern "C" u8* D_00507C00[10];

/**
 * @brief Load and decode the game table resource at a random 16-byte offset inside a fresh allocation, then point
 *        the table globals into it.
 */
void func_0040AFA0(void)
{
    // TODO: The game reads both of these before setting them, so whatever the registers hold feeds the offset.
    u32 noise;
    u32 seed;
    u32 seconds = resident_input_get_seconds(resident_system_get_input(resident_get_system()));
    seed += seed + seconds;
    seed = noise + (TIMER0_COUNT + (seed + resident_next_random_word()));
    D_001B64AC = malloc_guess(0x2442);
    D_001B64B0 = static_cast<u8*>(D_001B64AC) + (seed & 0xF) * 16;
    FlushCache(0);
    u8* data = static_cast<u8*>(memalign(0x80, resident_get_resource_size(g_resource_archive, 0x42C)));
    FlushCache(0);
    resident_queue_resource_request(g_resource_queue, 0x42C, data, 0x80002000, 0x34BC0, 0, 0, 0, 1);

    while (resident_find_resource_request(g_resource_queue, 0x42C, (u32)data, 0x80002000, 0xFFFFFFFF, 0))
    {
    }

    resident_decode_resource_block(g_resident_resource_decoder, reinterpret_cast<ResidentResourceHeader*>(data),
                                   D_001B64B0, 0);
    free_guess(data);
    LibTableResource* resource = reinterpret_cast<LibTableResource*>(D_001B64B0);
    D_001B64C4 = D_001B64B0 + resource->sections[0].offset;
    D_00507C00[1] = 0;
    D_001B64C8 = D_001B64C4 + 0x500;
    D_00507C00[0] = D_001B64C4 + 0x122;
    D_00507C00[2] = D_001B64C4 + 0x190;
    D_00507C00[3] = D_001B64C4 + 0x1FE;
    D_00507C00[4] = D_001B64C4 + 0x26C;
    D_00507C00[5] = D_001B64C4 + 0x2DA;
    D_00507C00[6] = D_001B64C4 + 0x348;
    D_00507C00[7] = D_001B64C4 + 0x3B6;
    D_00507C00[8] = D_001B64C4 + 0x424;
    D_00507C00[9] = D_001B64C4 + 0x492;
    D_001B64C0 = D_001B64B0 + resource->sections[1].offset;
    D_001B64BC = D_001B64B0 + resource->sections[2].offset;
    D_001B64B8 = reinterpret_cast<LibProtectedStatEntry*>(D_001B64B0 + resource->sections[3].offset);
    D_001B64B4 = D_001B64B0 + resource->sections[4].offset;
    D_001B64CC = reinterpret_cast<LibCodeList*>(D_001B64B0 + resource->sections[5].offset);
    D_001B64D0 = reinterpret_cast<LibCodeTable*>(D_001B64B0 + resource->sections[6].offset);
    D_001B64D4 = D_001B64B0 + resource->sections[7].offset;
    D_001B64D8 = D_001B64B0 + resource->sections[8].offset;
    D_001B64DC = D_001B64B0 + resource->sections[9].offset;
    D_001B64E0 = D_001B64B0 + resource->sections[10].offset;
    D_001B64E4 = reinterpret_cast<u16*>(D_001B64B0 + resource->sections[11].offset);
    D_001B64E8 = D_001B64B0 + resource->sections[12].offset;
    D_001B64A8 = 0;
}

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

/** One 6-byte inventor record of D_00501DA0. */
struct LibInventorEntry
{
    u8 unk00[2];
    u8 skill;
    u8 unk03;
    s8 cost_bonus;
    u8 unk05;
};

extern "C" LibInventorEntry D_00501DA0[];

/**
 * @brief Let each working inventor try to create its item: on a skill roll it pays its cost (for paid work), adds the
 * item's difficulty to its progress and either creates the item or raises the item's shop stock.
 * @param state Game state.
 * @return One when an item was created.
 */
u8 func_0040BB00(LibGameState* state)
{
    u8 created = 0;
    LibSystemSettings* settings =
        reinterpret_cast<LibSystemSettings*>(resident_find_entry(resident_get_entry_table(resident_get_system()), LIB_ENTRY_SYSTEM_SETTINGS));
    s32 fol = settings_fol(settings);

    for (s32 i = 0; i < state->unk117a2; i++)
    {
        u8 inventor = state->unk11760[i];
        LibGameStateRecord0C* record = &state->unk10d88[inventor - 1];

        if (record->unk0a == 1)
        {
            // TODO: paid is declared ahead of its assignment only for the game's spill slot and load order.
            u8 paid;
            LibInventorEntry* entry = &D_00501DA0[inventor - 1];
            u16 item_type = record->unk04;
            paid = record->unk08 == 2;
            s32 skill = entry->skill;
            s32 bonus = entry->cost_bonus;
            u32 price = func_00414130(&state->item_types[item_type - 1]) / 10;
            s32 percent = bonus + (resident_random_below(11) + 0x5F);
            s32 cost = 0.5f + price * (float)percent / 100.0f;
            cost = cost > 0 ? cost : 1;
            u32 points = D_001B64F0[item_type - 1].creation_difficulty;
            bool success = (s32)resident_random_below(100) < skill + 45 - (s32)points;

            if (success)
            {
                if (paid)
                {
                    if (fol < cost)
                    {
                        continue;
                    }

                    fol -= cost;
                }

                points += record->unk00;
                points = points < 100000000 ? points : 99999999;
                record->unk00 = points;

                if (func_0040C300(state, item_type, inventor, paid, 1))
                {
                    func_0040C180(state, item_type);
                    created = 1;
                }
                else
                {
                    s32 range = 100 - D_001B64F0[item_type - 1].creation_difficulty;
                    s32 gain = (range / 20 + resident_random_below(range / 2)) / 6 + 1;
                    ItemCreationCategoryRecord* category = &state->item_types[item_type - 1];
                    s32 stock = gain + category->shop_stock;

                    if (stock < 0)
                    {
                        stock = 0;
                    }
                    else if (stock > 99)
                    {
                        stock = 99;
                    }

                    category->shop_stock = stock;
                }
            }
        }
    }

    set_settings_fol(settings, fol);
    return created;
}

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
s32 func_0040C300(LibGameState* state, u16 item_type, u8 inventor_id, u8 set_flag04, s32 set_flag08)
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

/** A LibGameStateRecord0C's ID and unk00 while the records are ranked. */
typedef struct LibGameStateRank
{
    s32 id;
    s32 value;
} LibGameStateRank;

/**
 * @brief Swap two ranking entries.
 * @param first First entry.
 * @param second Second entry.
 */
static inline void swap_ranks(LibGameStateRank* first, LibGameStateRank* second)
{
    s32 id = first->id;
    s32 value = first->value;
    first->id = second->id;
    first->value = second->value;
    second->id = id;
    second->value = value;
}

/**
 * @brief Rank the used LibGameStateRecord0C entries by unk00, highest first: list their IDs in record0c_order, give
 * each its place in unk07 (equal values share one) and count them in record0c_order_count.
 * @param state Game state.
 */
extern "C" void func_0040C690(LibGameState* state)
{
    LibGameStateRank ranks[LIB_GAME_STATE_RECORD0C_COUNT];
    LibGameStateRecord0C* record = state->unk10d88;
    LibGameStateRank* rank = ranks;

    for (s32 i = 0; i < LIB_GAME_STATE_RECORD0C_COUNT; i++)
    {
        s32 id = 0;
        s32 value = -1;

        if (record->unk08)
        {
            id = record->unk06;
            value = record->unk00;
        }

        rank->id = id;
        rank->value = value;
        record->unk07 = 0;
        rank++;
        record++;
    }

    for (s32 i = 0; i <= LIB_GAME_STATE_RECORD0C_COUNT - 2; i++)
    {
        for (s32 j = LIB_GAME_STATE_RECORD0C_COUNT - 1; j >= i + 1; j--)
        {
            LibGameStateRank* current = &ranks[j];
            LibGameStateRank* previous = current - 1;

            if (previous->value < current->value)
            {
                swap_ranks(current, previous);
            }
        }
    }

    s32 count = 0;
    s32 place = 0;
    s32 previous = 0;
    LibGameStateRank* entry = ranks;
    u8* order = state->record0c_order;

    for (s32 i = 0; i < LIB_GAME_STATE_RECORD0C_COUNT; i++)
    {
        s32 id = entry->id;
        *order = id;

        if (id)
        {
            if (entry->value != previous)
            {
                previous = entry->value;
                place = i + 1;
            }

            s32 index = (u8)id - 1;
            state->unk10d88[index].unk07 = place;
            count++;
        }

        entry++;
        order++;
    }

    state->record0c_order_count = count;
}

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

/**
 * @brief Test whether an allocation record is in use.
 * @param record Allocation record.
 * @return Its allocated flag.
 */
static inline bool allocation_in_use(const ItemCreationAllocationRecord* record)
{
    return record->allocated;
}

/**
 * @brief Read the one-based item type of an allocation.
 * @param record Allocation record.
 * @return Item type ID, or one when the record's checksum differs.
 */
static inline u16 allocation_item_type(ItemCreationAllocationRecord* record)
{
    return record->definition_index() + 1;
}

/**
 * @brief Remove an allocation in use from its item type's list and update the factor and inventory counts.
 * @param object Game state.
 * @param identifier One-based allocation ID.
 * @return One on success, or zero when the ID is invalid or the allocation is free.
 */
extern "C" s32 func_0040C9F0(void* object, s16 identifier)
{
    LibGameState* state = static_cast<LibGameState*>(object);
    bool valid = false;

    if (identifier > 0 && identifier <= LIB_ALLOCATION_COUNT)
    {
        valid = true;
    }

    ItemCreationAllocationRecord* record =
        valid ? reinterpret_cast<ItemCreationAllocationRecord*>(&state->allocations[identifier - 1]) : 0;

    if (record == 0 || !allocation_in_use(record))
    {
        return 0;
    }

    u16 item_type = allocation_item_type(record);
    lower_factor_counts(record);
    record->allocated = 0;

    s32 type_index = item_type - 1;

    if (D_001B64F0[type_index].unsellable)
    {
        state->unk11722--;
    }
    else
    {
        state->unk11724--;
    }

    LibInventoryAllocationLinks* link = &state->links[identifier - 1];
    s16 previous = link->previous;
    s16 next = link->next;

    if (previous > 0)
    {
        s32 index = previous - 1;
        LibInventoryAllocationLinks* previous_link = &state->links[index];
        previous_link->next = next;
    }
    else
    {
        ItemCreationCategoryRecord* category = &state->item_types[type_index];
        category->allocation_list_head = next;
    }

    if (next > 0)
    {
        s32 index = next - 1;
        LibInventoryAllocationLinks* next_link = &state->links[index];
        next_link->previous = previous;
    }

    func_0040D050(state, item_type);
    return 1;
}

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

/**
 * @brief Calculate an allocation record's checksum from its six halfwords and stored shift.
 * @param record Allocation record.
 * @return Calculated checksum.
 */
static inline u16 allocation_halfword_checksum(ItemCreationAllocationRecord* record)
{
    return (0x83CF << record->checksum_shift)
         ^ ((((const u16*)record)[4] + (record->definition_factors.halves[0] + ((const u16*)record)[2])) ^ (((const u16*)record)[1] + (((const u16*)record)[3] + ((const u16*)record)[5])));
}

/**
 * @brief Store an allocation's catalog definition index after validating its checksum.
 * @param record Allocation record.
 * @param index Definition index.
 */
static inline void set_allocation_definition_index(ItemCreationAllocationRecord* record, u16 index)
{
    if (record->checksum == allocation_halfword_checksum(record))
    {
        record->definition_factors.bits.definition_index = index;
        record->checksum = allocation_halfword_checksum(record);
    }
}

/**
 * @brief Copy eight factor codes.
 * @param destination Destination codes.
 * @param source Source codes.
 */
static inline void copy_factor_codes(u16* destination, const u16* source)
{
    for (s32 i = 0; i < 8; i++)
    {
        *destination++ = *source++;
    }
}

/**
 * @brief Look up a factor's D_00504AA0 record.
 * @param factor One-based factor code.
 * @return Factor record.
 */
static inline const LibRecord504AA0* factor_record(u16 factor)
{
    return &D_00504AA0[factor - 1];
}

extern "C" void func_0040DD20(ItemCreationAllocationRecord* record, u32 slot, s32 factor);

/**
 * @brief Set up an allocation record for an item.
 * @param record Allocation record to configure.
 * @param item_code One-based item code.
 * @param modification_number Item type's factor-change count, or zero for an unmodified item.
 * @param factors Eight factor codes, or null for catalog defaults.
 * @param new_item Mark the item as new in inventory lists.
 * @param suppress_allocation_id Suppress the resident allocation identifier when the record checksum is valid.
 */
void lib_allocation_initialize(ItemCreationAllocationRecord* record, u16 item_code, u8 modification_number, const u16* factors, bool new_item,
                               bool suppress_allocation_id)
{
    u16 codes[8];
    bool battle_usable;
    s32 i;

    set_allocation_definition_index(record, item_code - 1);

    record->modification_number = modification_number;
    record->equipped_owner = 0;
    record->new_item = new_item;

    if (record->checksum == allocation_halfword_checksum(record))
    {
        record->factors_234.bits.suppress_allocation_id = suppress_allocation_id;
        record->checksum = allocation_halfword_checksum(record);
    }

    record->allocated = 1;

    if (factors == 0)
    {
        const ItemCreationCategoryDefinition* definition = &D_001B64F0[item_code - 1];
        codes[0] = definition->initial_factor;
        codes[1] = definition->factor1;
        codes[2] = definition->factor2;
        codes[3] = definition->factor3;
        codes[4] = definition->factor4;
        codes[5] = definition->factor5;
        codes[6] = definition->factor6;
        codes[7] = definition->final_factor;
    }
    else
    {
        copy_factor_codes(codes, factors);
    }

    battle_usable = false;

    for (i = 0; i < 8; i++)
    {
        s32 factor = codes[i];

        if (factor != 0)
        {
            const LibRecord504AA0* entry = factor_record(factor);

            if (entry->dropped)
            {
                factor = 0;
            }
            else if (entry->battle_usable)
            {
                battle_usable = true;
            }
        }

        func_0040DD20(record, i, factor);
    }

    record->battle_usable = battle_usable;
}

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

/** One packed word of an allocation record seen as three 10-bit fields. */
typedef struct LibAllocationFactorWord
{
    u32 low : 10;
    u32 middle : 10;
    u32 high : 10;
    u32 unused : 2;
} LibAllocationFactorWord;

// TODO: Only matches with common subexpressions off; the factor reads otherwise reuse the checksum's loads.
#pragma push
#pragma opt_common_subs off
/**
 * @brief Read one of an allocation's eight factor codes after validating its checksum.
 * @param record Allocation record.
 * @param index Factor slot, 0 to 7.
 * @return Factor code, or zero when the checksum differs or the slot is out of range.
 */
extern "C" u16 func_0040D930(const ItemCreationAllocationRecord* record, u32 index)
{
    const LibAllocationFactorWord* words = reinterpret_cast<const LibAllocationFactorWord*>(record);

    switch (index)
    {
        case 0:
            return record->invalid() ? 0 : (u16)words[0].middle;
        case 1:
            return record->invalid() ? 0 : record->definition_factors.bits.factor1;
        case 2:
            return record->invalid() ? 0 : record->factors_234.bits.factor2;
        case 3:
            return record->invalid() ? 0 : (u16)words[1].middle;
        case 4:
            return record->invalid() ? 0 : record->factors_234.bits.factor4;
        case 5:
            return record->invalid() ? 0 : record->factors_567.bits.factor5;
        case 6:
            return record->invalid() ? 0 : (u16)words[2].middle;
        case 7:
            return record->invalid() ? 0 : record->factors_567.bits.factor7;
    }

    return 0;
}
#pragma pop

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", func_0040DD20);

/**
 * @brief Report the list kind.
 * @return Four.
 */
s32 LibClass1721B0::get_default_list_kind()
{
    return 4;
}

extern "C" const char D_004EC300[];

/**
 * @brief Read whether the settings' sealed record has its first byte set, when the record passes its checksum.
 * @param settings System settings.
 * @return Whether the decoded byte is set; zero when the checksum fails.
 */
static inline u8 lib_settings_sealed_flag(LibSystemSettings* settings)
{
    if (settings->sealed_record.checksum != lib_compute_checksum(settings->sealed_record.key * LIB_RECORD_CHECKSUM_KEY_FACTOR, &settings->sealed_record, (u8*)&settings->sealed_record.checksum - (u8*)&settings->sealed_record))
    {
        return 0;
    }

    return (settings->sealed_record.unk00 ^ LIB_RECORD_XOR_BYTE) != 0;
}

/**
 * @brief Read the first byte of the settings' extra protected block when the block passes its checksum.
 * @param settings System settings.
 * @return The byte, or zero when the checksum fails.
 */
static inline u8 lib_settings_extra_flag(LibSystemSettings* settings)
{
    u8* data = &settings->extra_checksum_start;

    if (settings->extra_checksum != lib_compute_checksum(settings->extra_key, data, (u8*)&settings->extra_checksum - data))
    {
        return 0;
    }

    return settings->extra_checksum_start;
}

/**
 * @brief Check whether Universe difficulty is unlocked, trusting the flag only when its checksum passes.
 * @param settings System settings.
 * @return The unlock flag, or zero when the checksum fails.
 */
static inline u8 lib_settings_universe_unlocked(LibSystemSettings* settings)
{
    u8* data = &settings->extra_checksum_start;

    if (settings->extra_checksum != lib_compute_checksum(settings->extra_key, data, (u8*)&settings->extra_checksum - data))
    {
        return 0;
    }

    return settings->universe_unlocked;
}

/**
 * @brief Build the save data: clear its buffer, copy the options from the settings, and fill the header with the title
 * and the CRCs of the options, icon.sys and the extra file (or the loaded ones when there's nothing to compute).
 * @param object Save data manager.
 * @return One, or zero without settings.
 */
extern "C" s32 func_0040E3B0(LibClass1721B0* object)
{
    if (!object->settings)
    {
        return 0;
    }

    if (!object->unk910)
    {
        object->unk910 = new (0) u8[object->unk96c];
    }

    memset_guess(object->unk910, 0, object->unk96c);
    memset_guess(&object->options, 0, object->unk978);
    object->options.widescreen = object->settings->widescreen;
    object->options.sealed_flag = lib_settings_sealed_flag(object->settings);
    object->options.extra_flag = lib_settings_extra_flag(object->settings);
    object->options.universe_unlocked = lib_settings_universe_unlocked(object->settings);
    object->options.unk18D = object->settings->unk18D;
    object->options.sound_output = object->settings->sound_output;
    object->options.speaker_angles[0] = object->settings->speaker_angles[0];
    object->options.speaker_angles[1] = object->settings->speaker_angles[1];
    object->options.speaker_angles[2] = object->settings->speaker_angles[2];
    object->options.speaker_angles[3] = object->settings->speaker_angles[3];
    memcpy_guess(object->unk910 + (u8)object->unk974, &object->options, object->unk978);
    memset_guess(&object->header, 0, object->unk974);
    strcpy_guess(object->header.title, D_004EC300);
    object->header.extra_data_crc = lib_crc32(reinterpret_cast<u8*>(&object->options), object->unk978);

    if (object->icon_sys && object->unk98c == 1)
    {
        object->header.icon_sys_crc = lib_crc32(reinterpret_cast<u8*>(object->icon_sys), sizeof(LibIconSys));
    }
    else if (object->unk970)
    {
        object->header.icon_sys_crc = object->unk984;
    }
    else
    {
        object->header.icon_sys_crc = 0;
    }

    if (object->unk7c)
    {
        object->header.unk980_crc = lib_crc32(object->unk7c, 0xB3B0);
    }
    else if (object->unk970)
    {
        object->header.unk980_crc = object->unk988;
    }
    else
    {
        object->header.unk980_crc = 0;
    }

    object->header.data_crc = lib_crc32(reinterpret_cast<u8*>(&object->header), object->unk974);
    memcpy_guess(object->unk910, &object->header, object->unk974);
    return 1;
}

/**
 * @brief Clear the icon.sys buffer, allocate and clear the 0xB3B0-byte buffer and the save data buffer when missing,
 * and point the file request at all three.
 * @param object Save data manager.
 * @return One, or zero when an allocation fails.
 */
s32 func_0040E7F0(LibClass1721B0* object)
{
    if (object->icon_sys)
    {
        memset_guess(object->icon_sys, 0, LIB_ICON_SYS_SIZE);
    }

    u32 size = object->unk974 + object->unk978;

    if (object->unk79c == 0)
    {
        object->unk79c = new (0) u8[size];

        if (object->unk79c == 0)
        {
            return 0;
        }
    }

    if (object->unk79c)
    {
        memset_guess(object->unk79c, 0, size);
    }

    if (object->unk980 == 0)
    {
        object->unk980 = new (0) u8[0xB3B0];

        if (object->unk980 == 0)
        {
            return 0;
        }
    }

    if (object->unk980)
    {
        memset_guess(object->unk980, 0, 0xB3B0);
    }

    object->files[0].name = D_004EC440;
    object->files[0].data = object->icon_sys;
    object->files[0].size = LIB_ICON_SYS_SIZE;
    object->files[0].offset = 0;
    object->files[1].name = D_004EC3C0;
    object->files[1].data = object->unk980;
    object->files[1].size = 0xB3B0;
    object->files[1].offset = 0;
    object->files[2].name = object->directory;
    object->files[2].data = object->unk79c;
    object->files[2].size = size;
    object->files[2].offset = 0;
    object->request.directory = object->directory;
    object->request.file_count = 3;
    object->request.unk08 = 0;
    object->request.files = object->files;
    object->unk1a = 0;
    return 1;
}

/**
 * @brief Check the loaded save data, icon.sys and the 0xB3B0-byte buffer against the CRCs in the save data's header,
 * keeping the last two CRCs.
 * @param object Save data manager.
 * @return One when every CRC matches.
 */
extern "C" s32 func_0040E930(LibClass1721B0* object)
{
    LibSaveDataHeader* header = reinterpret_cast<LibSaveDataHeader*>(object->unk79c);

    if (!header)
    {
        return 0;
    }

    if (!object->icon_sys)
    {
        return 0;
    }

    if (!object->unk980)
    {
        return 0;
    }

    u32 data_crc = header->data_crc;
    u32 extra_data_crc = header->extra_data_crc;
    u32 icon_sys_crc = header->icon_sys_crc;
    u32 unk980_crc = header->unk980_crc;
    header->data_crc = 0;

    if (data_crc != lib_crc32(object->unk79c, object->unk974))
    {
        return 0;
    }

    if (extra_data_crc != lib_crc32(object->unk79c + object->unk974, object->unk978))
    {
        return 0;
    }

    if (icon_sys_crc == 0)
    {
        return 0;
    }

    u32 icon_crc = lib_crc32(reinterpret_cast<u8*>(object->icon_sys), sizeof(LibIconSys));

    if (icon_sys_crc != icon_crc)
    {
        return 0;
    }

    if (unk980_crc == 0)
    {
        return 0;
    }

    u32 unk980_check = lib_crc32(object->unk980, object->unk97c);

    if (unk980_crc != unk980_check)
    {
        return 0;
    }

    object->unk984 = icon_crc;
    object->unk988 = unk980_check;
    return 1;
}

/**
 * @brief Record in the settings' unk25_bit6 and unk18D whether the loaded trophy flags were valid.
 * @param object Save data manager.
 * @param value Whether the checksum held.
 */
static inline void set_trophy_flags_valid(LibClass1721B0* object, bool value)
{
    if (object->settings)
    {
        object->settings->unk25_bit6 = value;
    }

    if (object->settings)
    {
        object->settings->unk18D = value;
    }
}

/**
 * @brief Copy the trophy flags, trophy key and checksum out of the loaded save data into the settings, record in the
 * settings whether their checksum holds, and free the save data.
 * @param object Save data manager.
 * @return Whether the checksum holds; zero when no save data is loaded.
 */
extern "C" s32 func_0040EC10(LibClass1721B0* object)
{
    u8* data = object->unk79c;

    if (!data)
    {
        return 0;
    }

    s32 valid;

    if (*reinterpret_cast<s32*>(data) == 0)
    {
        valid = 0;
    }
    else
    {
        u8* source = data + 0x4B4;
        LibTrophyFlags* flags = &object->settings->trophy_flags;
        u8 bits[(LIB_TROPHY_COUNT + 7) / 8];
        memset_guess(bits, 0, sizeof(bits));
        memcpy_guess(bits, source, sizeof(bits));

        for (s32 i = 0; i < LIB_TROPHY_COUNT; i++)
        {
            u32 byte = (u32)i >> 3;
            u32 bit = i & 7;

            if (bits[i / 8] & (1 << (i % 8)))
            {
                flags->flags.bytes[byte] |= 1LL << bit;
            }
            else
            {
                flags->flags.bytes[byte] &= ~(1LL << bit);
            }
        }

        flags->trophy_key = *reinterpret_cast<s32*>(data);
        memcpy_guess(&flags->checksum_seed, source + sizeof(bits), 8);
        u32 seed = flags->checksum_seed;
        u32 checksum;
        lib_trophy_flags_checksum(flags, &seed, &checksum);
        valid = flags->checksum == checksum;
    }

    if (valid)
    {
        set_trophy_flags_valid(object, true);
    }
    else
    {
        set_trophy_flags_valid(object, false);
    }

    if (object->unk79c)
    {
        delete[] object->unk79c;
        object->unk79c = 0;
    }

    return valid;
}

/**
 * @brief Check the trophy flags against their stored checksum.
 * @param flags Trophy flags.
 * @return Nonzero when the checksum holds.
 */
static inline s32 lib_trophy_flags_checksum_holds(LibTrophyFlags* flags)
{
    u32 seed = flags->checksum_seed;
    u32 checksum;
    lib_trophy_flags_checksum(flags, &seed, &checksum);
    return flags->checksum == checksum;
}

/**
 * @brief Copy the settings' trophy flags with their checksum seed and checksum into the trophy buffer when their
 * checksum holds and their trophy key matches the save's; otherwise clear the flags.
 * @param object Save data manager.
 * @return One when the buffer was filled.
 */
extern "C" s32 func_0040EE30(LibClass1721B0* object)
{
    LibTrophyFlags* flags = &object->settings->trophy_flags;

    if (!flags)
    {
        return 0;
    }

    if (!flags)
    {
        return 0;
    }

    if (!lib_trophy_flags_checksum_holds(flags))
    {
        flags->flags.clear();
        return 0;
    }

    memset_guess(object->unk2e4, 0, sizeof(object->unk2e4));
    *reinterpret_cast<s32*>(object->unk2e4) = flags->trophy_key;

    if (*reinterpret_cast<s32*>(object->unk2e4) != *reinterpret_cast<s32*>(object->unk88c))
    {
        return 0;
    }

    object->unk888 = flags->flags.size;
    u32* seal = &flags->checksum_seed;
    u8* bytes = flags->flags.bytes;

    if (object->unk884 == 0)
    {
        object->unk884 = new (0) u8[object->unk888 + 8];
    }

    if (!object->unk884)
    {
        return 0;
    }

    memcpy_guess(object->unk884, bytes, object->unk888);
    memcpy_guess(object->unk884 + object->unk888, seal, 8);
    return 1;
}

/**
 * @brief Append a value and its ID.
 * @param object Receiver.
 * @param value Value to append; null is refused.
 * @param id ID, 0 to 299.
 * @return One when both were added, otherwise zero.
 */
extern "C" s32 func_0040F020(LibClass1721B0* object, void* value, s32 id)
{
    if (id < 0)
    {
        return 0;
    }

    if (id >= 300)
    {
        return 0;
    }

    if (value == 0)
    {
        return 0;
    }

    func_00411CC0(&object->values, value);
    object->ids[object->id_count] = id;
    object->id_count++;
    return 1;
}

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
    object->files[0].offset = 0;

    for (s32 i = 0; i < sizeof(object->unk8dc); i++)
    {
        object->unk8dc[i] = 0;
    }

    object->files[1].name = object->directory;
    object->files[1].data = object->unk8dc;
    object->files[1].size = 0x2E;
    object->files[1].offset = 0x4B4;
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
    object->files[0].offset = 0;
    object->files[1].name = object->directory;
    object->files[1].data = object->unk79c;
    object->files[1].size = LIB_SAVE_DATA_SIZE;
    object->files[1].offset = 0;
    object->request.directory = object->directory;
    object->request.file_count = 2;
    object->request.unk08 = 0;
    object->request.files = object->files;
    object->unk1a = 0;
    return 1;
}

/**
 * @brief Point the file request at the save's files for writing: the two header blocks, one trophy record per listed
 * ID, the trophy flags, the extra file and icon.sys.
 * @param object Save data manager.
 * @return One, or zero without a memory card or when the trophy flags don't check out.
 */
extern "C" s32 func_0040F4F0(LibClass1721B0* object)
{
    if (!object->card)
    {
        return 0;
    }

    u8 ready = func_0040EE30(object);

    if (!ready)
    {
        return 0;
    }

    func_00432710(object->card, 2);
    func_0040F940(object);
    object->files[0].name = object->directory;
    object->files[0].data = object->unk88c;
    object->files[0].size = 0x40;
    object->files[0].offset = 0;
    object->files[1].name = object->directory;
    object->files[1].data = object->unk884;
    object->files[1].size = 0x2E;
    object->files[1].offset = 0x4B4;

    for (s32 i = 0; i < object->id_count; i++)
    {
        object->files[i + 2].name = object->directory;
        object->files[i + 2].data = *static_cast<void**>(func_00411DD0(&object->values, i));
        object->files[i + 2].size = LIB_TROPHY_RECORD_SIZE;
        object->files[i + 2].offset = object->ids[i] * LIB_TROPHY_RECORD_SIZE + 0x4E2;
    }

    object->files[object->id_count + 2].name = object->directory;
    object->files[object->id_count + 2].data = object->unk2e4;
    object->files[object->id_count + 2].size = sizeof(object->unk2e4);
    object->files[object->id_count + 2].offset = 0;
    object->files[object->id_count + 3].name = D_004EC400;
    object->files[object->id_count + 3].data = object->unk7c;
    object->files[object->id_count + 3].size = 0x7F16;
    object->files[object->id_count + 3].offset = 0;
    object->files[object->id_count + 4].name = D_004EC440;
    object->files[object->id_count + 4].data = object->icon_sys;
    object->files[object->id_count + 4].size = LIB_ICON_SYS_SIZE;
    object->files[object->id_count + 4].offset = 0;
    object->request.directory = object->directory;
    object->request.file_count = object->id_count + 5;
    object->request.unk08 = 0;
    object->request.files = object->files;
    object->unk1a = 0;
    return 1;
}

/** One encoded trophy record. */
struct LibTrophyRecordBuffer
{
    u8 bytes[LIB_TROPHY_RECORD_SIZE];
};

/**
 * @brief Build a fresh save: free the old buffers, fill a new save data buffer with the trophy key and 300 copies of
 * an empty trophy record, and point the file request at the four save files.
 * @param object Save data manager.
 * @return One, or zero without a memory card or when the allocation fails.
 */
extern "C" s32 func_0040F740(LibClass1721B0* object)
{
    if (!object->card)
    {
        return 0;
    }

    func_00432710(object->card, 0x202);
    func_0040F940(object);

    if (object->unk798 != 0)
    {
        delete_array(object->unk798);
    }

    if (object->unk79c != 0)
    {
        delete_array(object->unk79c);
    }

    if (!object->unk798)
    {
        object->unk798 = new (0) u8[0x11ABA2];
    }

    if (!object->unk798)
    {
        return 0;
    }

    memset_guess(object->unk798, 0, 0x11ABA2);
    s32 key = object->settings->trophy_flags.trophy_key;
    memcpy_guess(object->unk798, &key, sizeof(key));
    LibTrophyRecordBuffer* record = new (0) LibTrophyRecordBuffer;
    memset_guess(record, 0, sizeof(*record));
    lib_trophy_record_encode(record);
    u8* copy = object->unk798 + 0x4E2;

    for (s32 i = 0; i < LIB_TROPHY_COUNT; i++)
    {
        memcpy_guess(copy, record, sizeof(*record));
        copy += sizeof(*record);
    }

    delete record;
    object->files[0].name = D_004EC440;
    object->files[0].data = object->unk8d8;
    object->files[0].size = LIB_ICON_SYS_SIZE;
    object->files[0].offset = 0;
    object->files[1].name = object->directory;
    object->files[1].data = object->unk798;
    object->files[1].size = 0x11ABA2;
    object->files[1].offset = 0;
    object->files[2].name = D_004EC400;
    object->files[2].data = object->unk7c;
    object->files[2].size = 0x7F16;
    object->files[2].offset = 0;
    object->files[3].name = D_004EC440;
    object->files[3].data = object->icon_sys;
    object->files[3].size = LIB_ICON_SYS_SIZE;
    object->files[3].offset = 0;
    object->request.directory = object->directory;
    object->request.file_count = 4;
    object->request.unk08 = 0;
    object->request.files = object->files;
    object->unk1a = 0;
    return 1;
}

/**
 * @brief Fill the icon.sys buffer: header, background, lights, title and the save's icon file for all three views.
 * @param object Save data manager.
 * @return One.
 */
extern "C" s32 func_0040F940(LibClass1721B0* object)
{
    if (object->icon_sys)
    {
        memset_guess(object->icon_sys, 0, LIB_ICON_SYS_SIZE);
    }

    object->icon_sys->magic[0] = 'P';
    object->icon_sys->magic[1] = 'S';
    object->icon_sys->magic[2] = '2';
    object->icon_sys->magic[3] = 'D';
    char title[sizeof(object->icon_sys->title)];
    char unused[sizeof(object->icon_sys->title)];
    memset_guess(title, 0, sizeof(title));
    memset_guess(unused, 0, sizeof(unused));
    strcpy_guess(title, D_004EC340);
    strcat(title, D_005056E0);
    strcpy_guess(object->icon_sys->title, title);
    object->icon_sys->title_line_offset = 10;
    object->icon_sys->background_alpha = 0x40;
    memcpy_guess(object->icon_sys->background_colors, D_004EC480, sizeof(object->icon_sys->background_colors));
    memcpy_guess(object->icon_sys->light_directions, D_004EC4C0, sizeof(object->icon_sys->light_directions));
    memcpy_guess(object->icon_sys->light_colors, D_004EC4F0, sizeof(object->icon_sys->light_colors));
    memcpy_guess(object->icon_sys->ambient_color, D_004EC520, sizeof(object->icon_sys->ambient_color));
    memcpy_guess(object->icon_sys->list_icon, D_004EC400, strlen(D_004EC400));
    memcpy_guess(object->icon_sys->copy_icon, D_004EC400, strlen(D_004EC400));
    memcpy_guess(object->icon_sys->delete_icon, D_004EC400, strlen(D_004EC400));
    return 1;
}

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004095C0", update__14LibClass1721B0Fv);

/** @brief Destroy the flags. */
LibTrophyFlags::~LibTrophyFlags()
{
}

/**
 * @brief Advance the icon.sys write: start the transfer, then rewrite the icon file and transfer it, then wait for
 *        it; a failure sets the step (unk1a) to -1.
 * @param object Save data manager.
 * @return The last card call's result, or -1 without a card.
 */
extern "C" s16 func_004110C0(LibClass1721B0* object)
{
    s16 result = -1;

    if (object->card != 0)
    {
        switch (object->unk1a)
        {
        case 0:
            result = lib_memory_card_start_transfer(object->card, object->unk1c, &object->request);

            if (result == 0)
            {
                object->unk1a++;
            }

            break;
        case 1:
            result = lib_memory_card_get_result(object->card, object->unk1c, &object->result);

            if (result != 0 && result == 1)
            {
                if (object->result >= 0)
                {
                    if (object->icon_sys)
                    {
                        memset_guess(object->icon_sys, 0, sizeof(LibIconSys));
                    }

                    func_004317B0(object->card, 2);
                    object->files[0].name = D_004EC440;
                    object->files[0].data = object->icon_sys;
                    object->files[0].size = sizeof(LibIconSys);
                    object->files[0].offset = 0;
                    object->request.directory = object->directory;
                    object->request.file_count = 1;
                    object->request.unk08 = 0;
                    object->request.files = object->files;
                    result = lib_memory_card_start_transfer(object->card, object->unk1c, &object->request);

                    if (result == 0)
                    {
                        object->unk1a++;
                    }
                }
                else
                {
                    object->unk1a = -1;
                }
            }

            break;
        case 2:
            result = lib_memory_card_get_result(object->card, object->unk1c, &object->result);

            if (result != 0 && result == 1)
            {
                object->unk1a = -1;
            }

            break;
        }

    }

    return result;
}

/**
 * @brief Advance the save directory check: read the card's directory, wait, look the save's entry up, wait, mark
 *        the entry and write it back, wait.
 * @param object Save data manager.
 * @return The last card call's result, or -1 without a card.
 */
extern "C" s16 func_00411250(LibClass1721B0* object)
{
    s16 result = -1;

    if (object->card != 0)
    {
        switch (object->unk1a)
        {
        case 0:
            result = func_004324D0(object->card, object->unk1c, &object->request);

            if (result == 0)
            {
                object->unk1a++;
            }

            break;
        case 1:
            result = lib_memory_card_get_result(object->card, object->unk1c, &object->result);

            if (result != 0 && result == 1 && result >= 0)
            {
                result = -1;
                object->unk1a++;
            }

            break;
        case 2:
            result = lib_memory_card_probe_file(object->card, object->unk1c, object->directory, 0, 1,
                                                reinterpret_cast<u8*>(object->entry));

            if (result != -1)
            {
                object->unk1a++;
            }

            break;
        case 3:
            result = lib_memory_card_get_result(object->card, object->unk1c, &object->result);

            if (result != 0 && result == 1 && result >= 0)
            {
                result = -1;
                object->unk1a++;
            }

            break;
        case 4:
            object->entry->attributes |= 8;
            result = func_004323E0(object->card, object->unk1c, object->directory, 4,
                                   reinterpret_cast<u8*>(object->entry));

            if (result != -1)
            {
                object->unk1a++;
            }

            break;
        case 5:
            result = lib_memory_card_get_result(object->card, object->unk1c, &object->result);

            if (result != 0 && result == 1)
            {
                object->unk1a++;
            }

            break;
        }
    }

    return result;
}

/** Lib's main update list. */
extern "C" LibUpdateList* g_update_list;

/**
 * @brief Create the memory card object with both slots open, the icon buffers and the 300 save flags.
 * @param object Save data manager.
 * @param mode Stored at unk90b.
 * @return One, or zero when an allocation failed.
 */
extern "C" s32 func_00411420(LibClass1721B0* object, u8 mode)
{
    object->card = new (0) LibMemoryCard;

    if (object->card == 0)
    {
        return 0;
    }

    lib_memory_card_init(object->card, g_update_list);
    lib_memory_card_open_slot(object->card, 0, 0, 0);
    lib_memory_card_open_slot(object->card, 1, 1, 0);
    object->unk18 = 0;
    object->icon_sys = new (0) LibIconSys;

    if (object->icon_sys == 0)
    {
        return 0;
    }

    if (object->icon_sys)
    {
        memset_guess(object->icon_sys, 0, sizeof(LibIconSys));
    }

    object->flags.resize(300);
    object->flags.clear();
    object->unk90b = mode;
    object->unk8d8 = new (0) LibIconSys;

    if (object->unk8d8 == 0)
    {
        return 0;
    }

    memset_guess(object->unk8d8, 0, sizeof(LibIconSys));
    return 1;
}

/**
 * @brief Free a block and clear the pointer to it, when there is one.
 * @param block Pointer to the block.
 */
static inline void lib_delete_block(u8*& block)
{
    if (block)
    {
        delete block;
        block = 0;
    }
}

/**
 * @brief Free an icon buffer and clear the pointer to it, when there is one.
 * @param block Pointer to the buffer.
 */
static inline void lib_delete_block(LibIconSys*& block)
{
    if (block)
    {
        delete block;
        block = 0;
    }
}

/**
 * @brief Free an array and clear the pointer to it, when there is one.
 * @param block Pointer to the array.
 */
static inline void lib_delete_array(u8*& block)
{
    if (block)
    {
        delete[] block;
        block = 0;
    }
}

/** @brief Free the buffers and the memory card object, then queue this object for release. */
void LibClass1721B0::destroy()
{
    func_00411D50(&values);

    if (unk884)
    {
        lib_delete_block(unk884);
    }

    if (icon_sys)
    {
        lib_delete_block(icon_sys);
    }

    if (unk798)
    {
        lib_delete_array(unk798);
    }

    if (unk79c)
    {
        lib_delete_array(unk79c);
    }

    if (card)
    {
        lib_object_detach_owner(card);
        card->destroy();
    }

    if (unk910)
    {
        lib_delete_array(unk910);
    }

    if (unk980)
    {
        lib_delete_array(unk980);
    }

    if (unk8d8)
    {
        lib_delete_block(unk8d8);
    }

    resident_enqueue_object(g_resident_release_queues, this);
}

/** @brief Free the flag storage and the value list, then detach. */
LibClass1721B0::~LibClass1721B0()
{
}

/** Directory name the save data lives in. */
extern "C" const char D_004EC2C0[];

/** Suffix appended to the directory name. */
extern "C" const char D_00505700[];

/**
 * @brief Join two strings into a buffer when they fit, leaving the buffer alone otherwise.
 * @param buffer Destination.
 * @param size Size of the destination.
 * @param first First string, or null to do nothing.
 * @param second String appended to the first, or null.
 */
static inline void lib_join_name(char* buffer, u32 size, const char* first, const char* second)
{
    if (first != 0 && strlen(first) + strlen(second) + 1 <= size)
    {
        memset_guess(buffer, 0, size);
        strcpy_guess(buffer, first);

        if (second != 0)
        {
            strcat(buffer, second);
        }
    }
}

LibClass1721B0::LibClass1721B0()
{
    card = 0;
    unk18 = 0;
    unk1c = -1;
    unk1e = -1;
    unk20 = -1;
    unk87a = -1;
    unk878 = 0;
    result = -1;
    icon_sys = 0;
    unk798 = 0;
    unk79c = 0;
    unk1a = -1;
    id_count = 0;
    unk7c = 0;
    settings = 0;
    settings = reinterpret_cast<LibSystemSettings*>(resident_find_entry(resident_get_entry_table(resident_get_system()), LIB_ENTRY_SYSTEM_SETTINGS));

    for (s32 i = 0; i < 37; i++)
    {
        files[i].name = 0;
        files[i].data = 0;
        files[i].size = 0;
        files[i].offset = 0;
    }

    request.directory = 0;
    request.file_count = 0;
    request.unk08 = 0;
    request.files = 0;
    id_count = 0;

    for (s32 i = 0; i < 0x20; i++)
    {
        ids[i] = -1;
    }

    memset_guess(entry_buffer, 0, sizeof(entry_buffer));
    entry = reinterpret_cast<LibCardDirectoryEntry*>((reinterpret_cast<u32>(entry_buffer) + 0x3F) & ~0x3F);
    lib_join_name(directory, sizeof(directory), D_004EC2C0, D_00505700);
    unk880 = 0;
    unk884 = 0;
    unk888 = 0;
    unk90b = 0;
    unk90c[0] = 0;
    unk90c[1] = 0;
    unk910 = 0;
    unk96c = 0;
    unk970 = 0;
    unk974 = 0x40;
    unk978 = 0x18;
    unk97c = 0xB3B0;
    unk96c = unk974 + unk978;
    unk980 = 0;
    unk984 = 0;
    unk988 = 0;
    unk98c = 0;
    unk8cc = 0;

    for (s32 i = 0; i < 0x40; i++)
    {
        unk88c[i] = 0;
    }

    unk8cd[0] = 0;
    unk8cd[1] = 0;
    unk8d0 = 0;
    unk8d4 = 0;
    unk8d8 = 0;
    unk90a = 0;

    for (s32 i = 0; i < sizeof(unk8dc); i++)
    {
        unk8dc[i] = 0;
    }
}

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

/**
 * @brief Called when the selected index changes; the base does nothing.
 * @param index Selected index.
 */
void LibClass1721F0::notify_index(s32 index)
{
}

/** @brief Called when the selection is cancelled; the base does nothing. */
void LibClass1721F0::notify_cancel()
{
}

/** @brief Draw in the bucket stored at unka8. */
void LibCallbackTransform::set_default_draw_bucket()
{
    draw_bucket = unka8;
}

/**
 * @brief Show or hide every row and the six aggregate widgets.
 * @param list List to change.
 * @param visible Nonzero to show them.
 */
static inline void aggregate_set_rows_visible(LibClass1721F0* list, u8 visible)
{
    for (s32 i = 0; i < list->unk4a0; i++)
    {
        static_cast<LibAggregateRow*>(list->rows[i])->set_visible(list, visible);
    }

    list->unk90.unk3d = visible;
    list->unk20c.unk3d = visible;
    list->unk260.unk3d = visible;
    list->unke4.unk3d = visible;
    list->unk138.unk3d = visible;
    list->unk190.unk3d = visible;
}

/**
 * @brief Run the list's open, select and close states, after applying a pending index.
 * @param first First update flag, unused here.
 * @param second Second update flag, unused here.
 * @param third Third update flag, unused here.
 */
void LibClass1721F0::func_00412C40(bool first, bool second, bool third)
{
    if (unk318 != 0)
    {
        func_00412C10(unk304);
        unk318 = 0;
    }

    if (unk4a4 == 0)
    {
        return;
    }

    switch (unk4a4)
    {
    case 1:
        unk00.transition_state = 1;
        unk4a4++;
        break;

    case 2:
        if (unk00.in_transition_state(0))
        {
            unk317 = 1;
            aggregate_set_rows_visible(this, 1);
            func_004138E0(&static_cast<LibClass1723F0&>(*this), unk304, unk312, unk2f8);
            unk4a4++;
        }

        break;

    case 3:
        if (func_004135D0(&static_cast<LibClass1723F0&>(*this)))
        {
            s32 result = func_00413460(&static_cast<LibClass1723F0&>(*this));

            if (result > 0)
            {
                if (!unk4a8)
                {
                    resident_sound_play(g_sound, 1, 0, 0, 127, 64, 0);
                }

                notify_index(unk30c);
            }
            else if (result < 0)
            {
                if (!unk4a9)
                {
                    resident_sound_play(g_sound, 2, 0, 0, 127, 64, 0);
                }

                notify_cancel();
            }

            if (result != 0)
            {
                unk4a4 = 0;
                return;
            }

            func_00413020();
        }

        func_00413750(&static_cast<LibClass1723F0&>(*this));
        break;

    case 4:
        unk317 = 0;
        aggregate_set_rows_visible(this, 0);
        unk00.transition_state = 5;
        unk4a4++;
        break;

    case 5:
        if (unk00.in_transition_state(0))
        {
            unk4a4 = 0;
            unkab = 0;
        }

        break;
    }
}

/**
 * @brief Read the float setting of the selected row.
 * @return The row's setting.
 */
float LibClass1721F0::func_00412C30()
{
    return static_cast<LibAggregateRow*>(rows[unk312])->get_setting(this);
}

/**
 * @brief Arrange the rows downwards from a height, one row spacing apart.
 * @param value Height of the first row before the 16-unit margin.
 */
void LibClass1721F0::func_00412C20(float value)
{
    float y = 16.0f + value;

    for (s32 i = 0; i < unk4a0; i++)
    {
        static_cast<LibAggregateRow*>(rows[i])->position_row(this, 32.0f, y);
        y += unk2c4;
    }
}

/**
 * @brief Refresh the visible rows for a starting index and hide the rows past the last entry.
 * @param index First entry index shown.
 */
void LibClass1721F0::func_00412C10(s32 index)
{
    for (s32 row_index = 0; row_index < unk4a0; index++, row_index++)
    {
        LibAggregateRow* row = static_cast<LibAggregateRow*>(rows[row_index]);

        if (index < unk2f8)
        {
            row->set_visible(this, 1);
            row->refresh_row(this, index);
        }
        else
        {
            row->set_visible(this, 0);
        }
    }
}

/**
 * @brief Show or hide every row and the six aggregate widgets.
 * @param visible Nonzero to show them.
 */
void LibClass1721F0::set_rows_visible(u8 visible)
{
    aggregate_set_rows_visible(this, visible);
}

/**
 * @brief Set the list up: its frame, scissors, markers, indicator, cursor and rows.
 * @param count Number of entries.
 * @param flags Bit 0 opens the list with its transition, bits 1 and 2 show the two markers, bits 3 and 4 mute the
 *              confirm and cancel sounds.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width List width.
 * @param height List height.
 * @param row_height Height of one row.
 * @param timing Scroll timing passed to the aggregate.
 * @return One on success, or zero when a widget or row couldn't be set up.
 */
s32 LibClass1721F0::init(s32 count, s32 flags, float x, float y, float width, float height, float row_height, float timing)
{
    lib_container_init(this, 5, x, y, 0, 0.0f, 0);
    unk490 = x;
    unk494 = y;
    unk498 = width;
    unk49c = height;
    s32 visible_rows = (s32)(height - 32.0f) / row_height;
    unk4a0 = visible_rows + 2;

    if (unk4a0 <= 0 || unk4a0 > 32)
    {
        return 0;
    }

    if (!unk00.init_frame(width, height))
    {
        return 0;
    }

    lib_container_attach_widget(this, &unk00);

    if (!lib_scissor_init_rectangle(&unk90, 32.0f, 16.0f, width - 66.0f, height - 32.0f))
    {
        return 0;
    }

    lib_container_attach_widget(this, &unk90);

    if (!func_0041AD10(&unk20c, 32.0f, 16.0f, width - 66.0f, row_height))
    {
        return 0;
    }

    if (flags & 2)
    {
        lib_container_attach_widget(this, &unk20c);
    }

    if (!lib_marker_init_rectangle(&unk260, 32.0f, 40.0f, width - 66.0f, 2.25f))
    {
        return 0;
    }

    if (flags & 4)
    {
        lib_container_attach_widget(this, &unk260);
    }

    for (s32 index = 0; index < 32; index++)
    {
        rows[index] = 0;
    }

    for (s32 index = 0; index < unk4a0; index++)
    {
        void* row = create_row(index);

        if (!row)
        {
            return 0;
        }

        rows[index] = row;
    }

    if (!lib_scissor_init_reset(&unke4, 1))
    {
        return 0;
    }

    lib_container_attach_widget(this, &unke4);

    if (!lib_list_indicator_init(&unk138, width - 26.0f, 16.0f, height - 32.0f, 100.0f, 0.0f))
    {
        return 0;
    }

    lib_container_attach_widget(this, &unk138);

    if (!lib_moving_widget_init_position(&unk190, 32.0f, 30.0f))
    {
        return 0;
    }

    lib_container_attach_widget(this, &unk190);
    aggregate_set_rows_visible(this, 0);
    func_00413C00(&static_cast<LibClass1723F0&>(*this), count, 1, visible_rows, width - 66.0f, row_height, timing);
    unk4a8 = (flags & 8) != 0;
    unk4a9 = (flags & 0x10) != 0;
    unk4aa = (flags & 1) != 0;

    if (unk4aa)
    {
        unk00.unk8c = 1;
        unk00.transition_state = 0;
        unk00.needs_redraw = 1;
        unk4a4 = 2;
    }
    else
    {
        unkab = 0;
        unk4a4 = 0;
    }

    return 1;
}

/** @brief Destroy the panel. */
inline LibClass1722E0::~LibClass1722E0()
{
}

/** @brief Release the widget storage and destroy its base. */
inline ItemCreationClass1746A0::~ItemCreationClass1746A0()
{
}

/** @brief Destroy the indicator. */
inline LibListIndicator::~LibListIndicator()
{
}

/** @brief Release the widget storage and destroy its bases. */
inline ItemCreationClass175030::~ItemCreationClass175030()
{
}

/** @brief Release the widget storage and destroy its base. */
inline ItemCreationClass172600::~ItemCreationClass172600()
{
}

/** @brief Release the widget storage and destroy its base. */
inline ItemCreationClass172870::~ItemCreationClass172870()
{
}

// TODO: the list's destructor inlines LibClass172320's but calls LibClass1723F0's, and LibClass172320's own copy
// inlines LibClass1723F0's but calls the widgets', so I've scoped the inline depth to one around these two.
#pragma push
#pragma inline_depth(1)

/** @brief Destroy the aggregate and the container. */
inline LibClass172320::~LibClass172320()
{
}

/** @brief Detach the remaining widgets and delete the rows. */
LibClass1721F0::~LibClass1721F0()
{
    for (;;)
    {
        LibListSentinel* node = sentinel.next;

        if (&sentinel == node)
        {
            break;
        }

        func_004C6120(this, static_cast<LibWidget*>(node));
    }

    for (s32 i = 0; i < 32; i++)
    {
        if (rows[i])
        {
            delete static_cast<LibAggregateRow*>(rows[i]);
            rows[i] = 0;
        }
    }
}

#pragma pop

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
void LibContainer::func_00412C40(bool first, bool second, bool third)
{
}

/**
 * @brief Put the two markers on the selected cell, and give a marker with no width of its own the selected row's.
 * @param aggregate Widget aggregate.
 */
static inline void aggregate_place_markers(LibClass1723F0* aggregate)
{
    aggregate->unk20c.set_position(aggregate->unk2d4 + aggregate->unk2c0 * (float)(aggregate->unk312 % aggregate->unk310),
                                   aggregate->unk2d8 + aggregate->unk2c4 * (float)(aggregate->unk312 / aggregate->unk310));

    if (aggregate->unk2dc == 0.0f)
    {
        aggregate->unk20c.set_width(aggregate->func_00412C30());
    }

    aggregate->unk260.set_position(aggregate->unk2e0 + aggregate->unk2c0 * (float)(aggregate->unk312 % aggregate->unk310),
                                   aggregate->unk2e4 + aggregate->unk2c4 * (float)(aggregate->unk312 / aggregate->unk310));

    if (aggregate->unk2e8 == 0.0f)
    {
        aggregate->unk260.set_width(aggregate->func_00412C30());
    }
}

/**
 * @brief Set the scroll indicator's position from the first row shown and the scroll offset.
 * @param aggregate Widget aggregate.
 */
static inline void aggregate_update_indicator(LibClass1723F0* aggregate)
{
    aggregate->unk138.set_position(100.0f * (aggregate->unk2f0 + (float)aggregate->unk304 * aggregate->unk2c4) /
                                   ((float)aggregate->unk2fc * aggregate->unk2c4));
}

/**
 * @brief Apply pad input to the selection, scrolling and paging, and count down the page repeat delays.
 * @return True when the selection or scroll position changed.
 */
bool LibClass1723F0::func_00413020()
{
    bool changed = false;
    s32 selection = unk312;
    s32 row_step = 0;
    u16 buttons = g_field_runtime->inputs[unk315].unk04;
    s32 page_step = 0;

    if (buttons & 0x10)
    {
        if (selection < unk310)
        {
            row_step--;
        }
        else
        {
            selection -= unk310;
        }
    }
    else if (buttons & 0x40)
    {
        if (selection >= unk310 * (unk311 - 1))
        {
            row_step++;
        }
        else
        {
            selection += unk310;
        }
    }
    else if (buttons & 0x80)
    {
        if (unk310 > 1)
        {
            if (selection == 0)
            {
                selection = unk310 - 1;
                row_step--;
            }
            else
            {
                selection--;
            }
        }
    }
    else if (buttons & 0x20)
    {
        if (unk310 > 1)
        {
            if (selection == unk310 * unk311 - 1)
            {
                row_step++;
                selection = unk310 * (unk311 - 1);
            }
            else
            {
                selection++;
            }
        }
    }
    else if ((buttons & 0x400) && page_repeat_delay[0] <= 0.0f)
    {
        if (unk304 > 0)
        {
            page_step--;
        }
        else
        {
            selection %= unk310;
        }

        page_repeat_delay[0] = 4.0f;
        page_repeat_delay[1] = 0.0f;
    }
    else if ((buttons & 0x800) && page_repeat_delay[1] <= 0.0f)
    {
        if (unk304 < unk300)
        {
            page_step++;
        }
        else
        {
            selection = selection % unk310 + unk310 * (unk311 - 1);
        }

        page_repeat_delay[0] = 0.0f;
        page_repeat_delay[1] = 4.0f;
    }

    if (selection != unk312)
    {
        unk312 = selection;
        float duration;

        if (row_step != 0)
        {
            duration = unk2c8 / 60.0f;
        }
        else
        {
            duration = 0.05f;
        }

        unk190.set_move_target(unk2cc + unk2c0 * (selection % unk310), unk2d0 + unk2c4 * (selection / unk310), duration);
        changed = true;
    }

    if ((row_step < 0 && unk304 > 0) || (row_step > 0 && unk304 < unk300))
    {
        unk313 = row_step;
        unk314 = 1;
        changed = true;
        page_repeat_delay[1] = 0.0f;
        page_repeat_delay[0] = 0.0f;
    }

    if (page_step != 0)
    {
        if (page_step < 0)
        {
            unk304 -= unk311;

            if (unk304 < 0)
            {
                unk304 = 0;
            }
        }
        else
        {
            unk304 += unk311;

            if (unk304 > unk300)
            {
                unk304 = unk300;
            }
        }

        func_00412C10(unk304);
        aggregate_update_indicator(this);
        changed = true;
    }

    if (changed)
    {
        resident_sound_play(g_sound, 0, 0, 0, 127, 64, 0);
    }

    float rate = g_field_runtime->rate;

    for (s32 i = 0; i < 2; i++)
    {
        float delay = page_repeat_delay[i];

        if (delay > 0.0f)
        {
            delay -= rate;
        }

        page_repeat_delay[i] = delay;
    }

    return changed;
}

/**
 * @brief Read the result of a running selection from the pad and record the chosen entry.
 * @param aggregate Widget aggregate.
 * @return Positive when an entry was chosen, negative when the selection was cancelled, otherwise zero.
 */
extern "C" s32 func_00413460(LibClass1723F0* aggregate)
{
    // TODO: a goto is the only way I've found to leave the loop from inside the switch without an extra test.
    s32 result = 0;
    aggregate->unk308 = aggregate->unk312 + aggregate->unk304 * aggregate->unk310 + 1;
    u32 mask = aggregate->unk2f4;
    u16 pressed = g_field_runtime->inputs[aggregate->unk315].unk02;

    for (s32 i = 0; i < 4; i++, mask >>= 1)
    {
        if (mask & 1)
        {
            switch (i)
            {
            case 0:
                if (pressed & g_field_runtime->button_map->buttons[1])
                {
                    result = -1;
                    goto done;
                }

                break;

            case 1:
                if (pressed & g_field_runtime->button_map->buttons[0])
                {
                    result = 1;
                    goto done;
                }

                break;

            case 2:
                if (pressed & g_field_runtime->button_map->buttons[2])
                {
                    result = 2;
                    goto done;
                }

                break;

            case 3:
                if (pressed & g_field_runtime->button_map->buttons[3])
                {
                    result = 3;
                    goto done;
                }

                break;
            }
        }
    }

done:
    if (result < 0)
    {
        aggregate->unk30c = 0;
        aggregate->unk316 = 0;
    }
    else if (result > 0)
    {
        if (aggregate->unk308 <= aggregate->unk2f8)
        {
            aggregate->unk30c = aggregate->unk308;
            aggregate->unk316 = result;
        }
        else
        {
            result = 0;
        }
    }

    return result;
}

/**
 * @brief Test whether the aggregate takes input this frame, and place the markers when it does.
 * @param aggregate Widget aggregate.
 * @return One when the cursor has arrived and no scroll is running, otherwise zero.
 */
extern "C" u8 func_004135D0(LibClass1723F0* aggregate)
{
    u8 ready = aggregate->unk190.arrived && aggregate->unk314 == 0;

    if (ready)
    {
        aggregate_place_markers(aggregate);
    }

    return ready;
}

/**
 * @brief Run a pending row scroll and update the scroll indicator.
 * @param aggregate Widget aggregate.
 */
extern "C" void func_00413750(LibClass1723F0* aggregate)
{
    if (aggregate->unk314 == 1)
    {
        aggregate->unk2f0 = 0.0f;
        aggregate->unk314 = 2;

        if (aggregate->unk313 < 0)
        {
            aggregate->func_00412C10(aggregate->unk304 - 1);
            aggregate->unk2ec = -aggregate->unk2c4;
        }
    }

    if (aggregate->unk314 == 2)
    {
        float per_frame = aggregate->unk2c4 / aggregate->unk2c8;
        float step = per_frame * g_field_runtime->rate;

        if (aggregate->unk313 < 0)
        {
            aggregate->unk2f0 -= step;
            aggregate->unk2ec += step;

            if (!(aggregate->unk2ec < 0.0f))
            {
                aggregate->unk2f0 = 0.0f;
                aggregate->unk2ec = 0.0f;
                aggregate->unk304--;
                aggregate->unk314 = 0;
            }
        }
        else
        {
            aggregate->unk2f0 += step;
            aggregate->unk2ec -= step;

            if (aggregate->unk2ec <= -aggregate->unk2c4)
            {
                aggregate->unk2f0 = 0.0f;
                aggregate->unk2ec = 0.0f;
                aggregate->unk304++;
                aggregate->func_00412C10(aggregate->unk304);
                aggregate->unk314 = 0;
            }
        }

        aggregate->func_00412C20(aggregate->unk2ec);
        aggregate_update_indicator(aggregate);
    }
}

/**
 * @brief Start a selection: set the entry count and position, refresh the rows and place the cursor and markers.
 * @param aggregate Widget aggregate.
 * @param first First entry index shown.
 * @param selected Selected row.
 * @param count Number of entries.
 */
extern "C" void func_004138E0(LibClass1723F0* aggregate, s32 first, s32 selected, s32 count)
{
    aggregate->unk2f8 = count;
    aggregate->unk2fc = (aggregate->unk2f8 + aggregate->unk310 - 1) / aggregate->unk310;
    aggregate->unk300 = aggregate->unk2fc - aggregate->unk311;

    if (aggregate->unk300 < 0)
    {
        aggregate->unk300 = 0;
    }

    aggregate->unk304 = first;
    aggregate->unk312 = selected;
    aggregate->unk308 = selected + first * aggregate->unk310 + 1;
    aggregate->unk30c = -1;
    aggregate->func_00412C10(aggregate->unk304);
    aggregate->unk2f0 = 0.0f;
    aggregate->unk2ec = 0.0f;
    aggregate->unk314 = 0;
    aggregate->func_00412C20(aggregate->unk2ec);
    aggregate->unk190.snap_to(aggregate->unk2cc + aggregate->unk2c0 * (float)(aggregate->unk312 % aggregate->unk310),
                              aggregate->unk2d0 + aggregate->unk2c4 * (float)(aggregate->unk312 / aggregate->unk310));
    aggregate_place_markers(aggregate);
    aggregate->unk138.set_extent(100.0f * (float)aggregate->unk311 / (float)aggregate->unk2fc);
    aggregate_update_indicator(aggregate);
    aggregate->page_repeat_delay[1] = 0.0f;
    aggregate->page_repeat_delay[0] = 0.0f;
}

/**
 * @brief Point the aggregate's list indicator at its scroll position, as a percentage.
 * @param aggregate Widget aggregate.
 */
extern "C" void func_00413BB0(LibClass1723F0* aggregate)
{
    aggregate_update_indicator(aggregate);
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

/**
 * @brief Lay the item code out in the scratchpad and draw it, once; when fitting is on, a code wider or taller than the
 *        widget is laid out again at a smaller scale, and the scale is put back after drawing.
 */
void LibObject172410::draw()
{
    if (unkfc == 0)
    {
        unk3b = 0;
        return;
    }

    if (!unk3b)
    {
        lib_restore_texture_cache(static_cast<LibRenderer*>(g_renderer));
        LibDrawRecord* records = reinterpret_cast<LibDrawRecord*>(0x70000000);
        float scale_x = draw_scale;
        float scale_y = draw_scale_y;
        begin_layout(records, 0.0f);
        func_00463DD0(this, unkfc, unkfe);
        func_004637A0(records, record_count);
        align_records_vertically(records, record_count);

        if (unkfa)
        {
            bool fitted = false;
            LibUiRect16* box = &unk18;
            LibTextExtent* size = &extent;

            if (!(size->width <= box->unk08))
            {
                draw_scale = scale_x * (box->unk08 / size->width);
                fitted = true;
            }

            if (!(size->height <= box->unk0c))
            {
                draw_scale_y = scale_y * (box->unk0c / size->height);
                fitted = true;
            }

            if (fitted)
            {
                begin_layout(records, 0.0f);
                func_00463DD0(this, unkfc, unkfe);
                func_004637A0(records, record_count);
                align_records_vertically(records, record_count);
            }
        }

        draw_records(records, record_count);
        draw_scale = scale_x;
        draw_scale_y = scale_y;
        unk3b = 1;
    }
}

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

/**
 * @brief Collect the codes of the game state bitsets an item type is marked in, one bit per code.
 * @param record Item type's category record.
 * @param mask Receives the 64-bit code mask as two words.
 */
extern "C" void func_00414010(const ItemCreationCategoryRecord* record, u32* mask)
{
    u32 codes[2];
    LibGameStateBitset* bitset;
    s32 i;
    u32* low;
    u32* high;

    // TODO: The target keeps both word addresses in registers across the loop; these pointers are how I got that.
    low = &codes[0];
    high = &codes[1];
    *high = 0;
    *low = 0;
    bitset = lib_game_state()->bitsets;

    for (i = 0; i < LIB_GAME_STATE_BITSET_COUNT; i++)
    {
        u16 item_type = record->catalog_index + 1;
        s32 index = item_type - 1;

        if ((u8)(bitset->bits[index / 8] & (1 << (index & 7))))
        {
            s32 code = func_0040B330(i + 1);

            if (code)
            {
                s32 bit = code - 1;
                codes[bit / 32] |= 1 << (bit & 31);
            }
        }

        bitset++;
    }

    mask[0] = *low;
    mask[1] = *high;
}

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

/**
 * @brief Lay out the text for a 16-bit ID glyph by glyph.
 * @param widget Widget to lay out into.
 * @param id ID passed to the code lookup.
 * @param variant Second lookup argument.
 */
extern "C" void func_00463C00(LibDrawWidget* widget, s32 id, u8 variant);

/** @brief Lay the detail code out in the scratchpad and draw it, once. */
void LibObject172440::draw()
{
    if (unkfc == 0)
    {
        unk3b = 0;
        return;
    }

    if (!unk3b)
    {
        lib_restore_texture_cache(static_cast<LibRenderer*>(g_renderer));
        LibDrawRecord* records = reinterpret_cast<LibDrawRecord*>(0x70000000);
        begin_layout(records, 0.0f);
        func_00463C00(this, unkfc, unkfe);
        func_004637A0(records, record_count);
        align_records_vertically(records, record_count);
        draw_records(records, record_count);
        unk3b = 1;
    }
}

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

/** Stream data libmpeg hands to a stream callback: the payload sits in the demultiplexer's ring. */
struct LibMpegStreamData
{
    s32 type;
    u8* header;
    u8* data;
    s32 length;
    s64 pts;
    s64 dts;
};

extern "C" s32 func_00415D30(u8* first, s32 first_size, u8* second, s32 second_size, const u8* head, s32 head_size, const u8* body,
                             s32 body_size);

/**
 * @brief Split a stream's free space into the part up to the end of its ring and the part that wraps.
 * @param stream Stream to look at.
 * @param first Receives the start of the free space.
 * @param first_size Receives the size of the part before the end of the ring.
 * @param second Receives the start of the ring when the free space wraps, otherwise null.
 * @param second_size Receives the size of the wrapped part.
 */
static inline void movie_stream_free_space(LibMovieStream* stream, u8** first, s32* first_size, u8** second, s32* second_size)
{
    s32 free_size = stream->size - stream->fill;

    if (stream->size - stream->position >= free_size)
    {
        *first = stream->data + stream->position;
        *first_size = free_size;
        *second = 0;
        *second_size = 0;
    }
    else
    {
        *first = stream->data + stream->position;
        *first_size = stream->size - stream->position;
        *second = stream->data;
        *second_size = free_size - (stream->size - stream->position);
    }
}

/**
 * @brief Copy a packet's payload, minus its four-byte header, out of the demultiplexer's ring into a stream's ring.
 * @param stream Stream receiving the payload.
 * @param packet Packet from libmpeg.
 * @return One when the payload was copied, or zero when it didn't fit.
 */
static inline s32 movie_stream_write(LibMovieStream* stream, LibMpegStreamData* packet)
{
    LibMovieStreamBuffer* buffer = stream->buffer;
    s32 size = buffer->size;
    u8* head = packet->data + 4;
    u8* end = buffer->data + size;

    if (!(head < end))
    {
        head -= size;
    }

    s32 head_size = end - head;
    u8* body = buffer->data;
    s32 length = packet->length - 4;
    head_size = head_size < length ? head_size : length;
    s32 body_size = length - head_size;
    u8* first;
    s32 first_size;
    u8* second;
    s32 second_size;
    movie_stream_free_space(stream, &first, &first_size, &second, &second_size);
    s32 written = func_00415D30(first, first_size, second, second_size, head, head_size, body, body_size);
    stream->position = (stream->position + written) % stream->size;
    stream->fill += written;
    stream->total += written;
    return written > 0;
}

/**
 * @brief Stream callback for the second kind of sound stream: mark the stream's kind and take the payload.
 * @param mpeg libmpeg decoder; unused.
 * @param packet Stream data.
 * @param stream Stream the callback was registered for.
 * @return One when the payload was copied, or zero when it didn't fit.
 */
extern "C" s32 func_004149B0(void* mpeg, LibMpegStreamData* packet, LibMovieStream* stream)
{
    stream->kind = 2;
    return movie_stream_write(stream, packet);
}

/**
 * @brief Stream callback for the first kind of sound stream: mark the stream's kind and take the payload.
 * @param mpeg libmpeg decoder; unused.
 * @param packet Stream data.
 * @param stream Stream the callback was registered for.
 * @return One when the payload was copied, or zero when it didn't fit.
 */
extern "C" s32 func_00414AC0(void* mpeg, LibMpegStreamData* packet, LibMovieStream* stream)
{
    stream->kind = 1;
    return movie_stream_write(stream, packet);
}

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
static inline s32 lib_ring_copy(u8* first, s32 first_size, u8* second, s32 second_size, const u8* head, s32 head_size, const u8* body,
                                s32 body_size)
{
    if (first_size + second_size < head_size + body_size)
    {
        return 0;
    }

    if (head_size >= first_size)
    {
        memcpy_guess(first, head, first_size);
        memcpy_guess(second, head + first_size, head_size - first_size);
        memcpy_guess(second + head_size - first_size, body, body_size);
    }
    else
    {
        s32 remaining = first_size - head_size;

        if (body_size >= remaining)
        {
            memcpy_guess(first, head, head_size);
            memcpy_guess(first + head_size, body, remaining);
            memcpy_guess(second, body + first_size - head_size, body_size - remaining);
        }
        else
        {
            memcpy_guess(first, head, head_size);
            memcpy_guess(first + head_size, body, body_size);
        }
    }

    return head_size + body_size;
}

extern "C" void func_00417D30(LibMovieRing* ring, s32 amount);

extern "C" void func_00417E50(LibMovieRing* ring, u8** first, s32* first_size, u8** second, s32* second_size);

/**
 * @brief Copy a video packet's payload out of the demultiplexer's ring into the decoder's ring and record its
 * timestamps.
 * @param mpeg Demultiplexer; unused.
 * @param packet Packet from libmpeg.
 * @param decoder Decoder receiving the payload.
 * @return One when the payload was copied, or zero when it didn't fit.
 */
extern "C" s32 func_00414DB0(void* mpeg, LibMpegStreamData* packet, LibMovieDecoder* decoder)
{
    LibMovieStreamBuffer* buffer = &decoder->input;
    s32 size = buffer->size;
    u8* end;
    u32 head_size;
    u8* body;
    u32 length;
    s32 body_size;
    s32 first_size;
    s32 second_size;
    u8* first;
    u8* second;
    u8* first_uncached;
    u8* head;
    u8* second_uncached;

    head = packet->data;
    end = buffer->data + size;
    head_size = end - head;
    body = buffer->data;
    length = packet->length;
    head_size = head_size < length ? head_size : length;
    body_size = length - head_size;
    func_00417E50(decoder, &first, &first_size, &second, &second_size);
    first_uncached = (u8*)((u32)first | UNCACHED_SEGMENT);
    second_uncached = (u8*)((u32)second | UNCACHED_SEGMENT);
    s32 written = lib_ring_copy(first_uncached, first_size, second_uncached, second_size, head, head_size, body, body_size);

    if (written > 0)
    {
        decoder->add_timestamp(packet->pts, packet->dts, first, written);
    }

    func_00417D30(decoder, written);
    return written > 0;
}

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

    /**
     * @brief Move the ring's DMA chain on.
     * @param decoder Decoder whose ring is fed.
     * @return True while sectors are queued.
     */
    bool func_00417740(LibMovieDecoder* decoder);
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

extern "C"
{
    /**
     * @brief Tell whether libmpeg has reached the end of the stream.
     * @param mpeg libmpeg decoder.
     * @return Nonzero at the end.
     */
    s32 sceMpegIsEnd(void* mpeg);

    /**
     * @brief Decode the next picture.
     * @param mpeg libmpeg decoder.
     * @param image Destination image.
     * @param macroblocks Size of the destination in macroblocks.
     * @return Nonzero on success.
     */
    s32 sceMpegGetPicture(void* mpeg, void* image, s32 macroblocks);

    /**
     * @brief Take a free frame to decode into.
     * @param state Movie state.
     * @return The frame, or null when none is free.
     */
    u8* func_004190C0(LibMovieState* state);

    /**
     * @brief Mark the frame being decoded as ready.
     * @param state Movie state.
     */
    void func_004191A0(LibMovieState* state);

    extern ResidentDmaQueue* D_001B6604;
    extern ResidentDmaQueue* D_001B6608;
}

/**
 * @brief Wait until the ring is not being changed, by taking and releasing its semaphore.
 * @param decoder Movie decoder.
 */
static inline void lib_movie_decoder_sync(LibMovieDecoder* decoder)
{
    LibSemaphoreLock lock(&decoder->semaphore);
}

/**
 * @brief Read how many whole sectors the decoder's ring holds, under its semaphore.
 * @param decoder Movie decoder.
 * @return Bytes in whole sectors.
 */
static inline s32 lib_movie_ring_sectors(LibMovieDecoder* decoder)
{
    s32 buffered;

    {
        LibSemaphoreLock lock(&decoder->semaphore);
        buffered = decoder->unkC999C & ~0x7FF;
    }

    return buffered;
}

/**
 * @brief Decode the next picture into a free frame once enough data is buffered (before the first picture, 512 KB
 *        while the disc is still reading), with channels 8 and 9 stopped; a paced movie then waits out the rest of
 *        the frame time on timer 0.
 * @param decoder Movie decoder.
 * @return 0 after a picture or when there is nothing to do yet, -1 once the stream has ended.
 */
extern "C" s32 func_004152C0(LibMovieDecoder* decoder)
{
    if (sceMpegIsEnd(decoder->mpeg))
    {
        if (decoder->state->ready_count >= 2)
        {
            return -1;
        }

        decoder->stopped = 3;
        return -1;
    }

    if (decoder->stopped == 1)
    {
        if (decoder->state->ready_count >= 2)
        {
            return -1;
        }

        decoder->stopped = 3;
        return -1;
    }

    s32 buffered;

    {
        LibSemaphoreLock lock(&decoder->semaphore);
        buffered = (decoder->unkC999C & ~0x7FF) + decoder->unkC9998 * 0x800;
    }

    if (buffered == 0)
    {
        return 0;
    }

    if (decoder->stopped != 2 && g_resource_archive->read_busy)
    {
        if ((!decoder->unk15E654 && lib_movie_ring_sectors(decoder) < 0x80000) ||
            lib_movie_ring_sectors(decoder) < 0x2800)
        {
            return 0;
        }
    }

    decoder->unk15E654 = 1;
    lib_movie_decoder_sync(decoder);

    decoder->unk15E650 = lib_movie_ring_sectors(decoder);
    u8* frame = func_004190C0(decoder->state);

    if (!frame)
    {
        return 0;
    }

    u8* image = reinterpret_cast<u8*>(reinterpret_cast<u32>(frame) | UNCACHED_SEGMENT);
    s32 start = TIMER0_COUNT;
    D_001B6604->wait_idle();
    D_001B6608->wait_idle();
    D_001B6604->stop();
    D_001B6608->stop();
    sceMpegGetPicture(decoder->mpeg, image, 0x460);
    decoder->unk15E658++;
    EnableDmac(D_001B6604->channel);
    EnableDmac(D_001B6608->channel);
    s32 limit = 0x106;

    if (resident_get_system()->progressive)
    {
        limit = 0x20C;
    }

    if (decoder->unk15E645)
    {
        // TODO: the wait keeps the elapsed time in memory, which only volatile gives me so far.
        volatile s32 elapsed;

        do
        {
            elapsed = TIMER0_COUNT - start;

            if (elapsed < 0)
            {
                elapsed += 0x8000;
            }
        } while (elapsed < limit);
    }

    if (decoder->stopped == 1)
    {
        if (decoder->state->ready_count >= 2)
        {
            return -1;
        }

        decoder->stopped = 3;
        return -1;
    }

    // TODO: The game tests libmpeg's frame count here and never uses the result, so the comparison is a guess.
    bool first_picture = false;

    if (*reinterpret_cast<s32*>(decoder->mpeg + 8) == 0)
    {
        first_picture = true;
    }

    func_004191A0(decoder->state);
    return 0;
}

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

extern "C" void func_00113EA0(void);

/**
 * @brief Decode pictures until libmpeg reaches the end of the stream or the decoder is stopped: wait for buffered data
 * and a free frame, then decode into the frame with channels 8 and 9 stopped.
 * @param decoder Decoder.
 * @return 1 at the end of the stream, -1 when the decoder was stopped.
 */
extern "C" s32 func_00415A70(LibMovieDecoder* decoder)
{
    s32 result = 1;

    while (!sceMpegIsEnd(decoder->mpeg))
    {
        if (decoder->stopped == 1)
        {
            result = -1;
            break;
        }

        s32 buffered;

        {
            LibSemaphoreLock lock(&decoder->semaphore);
            buffered = (decoder->unkC999C & ~0x7FF) + decoder->unkC9998 * 0x800;
        }

        if (buffered == 0)
        {
            continue;
        }

        u8* frame;

        do
        {
            frame = func_004190C0(decoder->state);
        } while (frame == 0 || decoder->state->unk80BC <= 1);

        (void)TIMER0_COUNT;
        u8* image = reinterpret_cast<u8*>(reinterpret_cast<u32>(frame) | UNCACHED_SEGMENT);
        func_00113EA0();
        D_001B6604->wait_idle();
        D_001B6608->wait_idle();
        D_001B6604->stop();
        D_001B6608->stop();
        sceMpegGetPicture(decoder->mpeg, image, decoder->width / 16 * decoder->height / 16);
        EnableDmac(D_001B6604->channel);
        EnableDmac(D_001B6608->channel);

        if (decoder->stopped == 1)
        {
            result = -1;
            break;
        }

        // TODO: The game tests libmpeg's frame count here and never uses the result, so the comparison is a guess.
        bool first_picture = false;

        if (*reinterpret_cast<s32*>(decoder->mpeg + 8) == 0)
        {
            first_picture = true;
        }

        func_004191A0(decoder->state);
    }

    sceMpegReset(decoder->mpeg);
    return result;
}

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
extern "C" inline s32 func_00415D30(u8* first, s32 first_size, u8* second, s32 second_size, const u8* head, s32 head_size, const u8* body,
                                    s32 body_size)
{
    if (first_size + second_size < head_size + body_size)
    {
        return 0;
    }

    if (head_size >= first_size)
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
    func_00417D30(this, func_00415D30(first_uncached, first_size, second_uncached, second_size, end_code.bytes, 4, 0, 0));
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

/**
 * @brief Move the ring's DMA chain on while holding the semaphore: with channel 4 paused, drop the sectors the IPU has
 *        read since the last call, append the whole sectors buffered since (REF tags, REFE on the last), and restart
 *        the channel from where it stopped.
 * @param decoder Decoder whose ring is fed.
 * @return True while sectors are queued.
 */
extern "C" bool func_00417740(LibMovieDecoder* decoder)
{
    LibSemaphoreLock lock(&decoder->semaphore);

    if (!decoder->unkC99D0)
    {
        return false;
    }

    {
        LibInterruptLock interrupts;
        *D_ENABLEW = *D_ENABLER | D_ENABLE_SUSPEND;
        *D4_CHCR = DMA_CHCR_DIR_FROM_MEMORY | DMA_CHCR_MODE_CHAIN;
        *D_ENABLEW = *D_ENABLER & ~D_ENABLE_SUSPEND;
    }

    u32 chcr = *D4_CHCR;
    u32 madr = *D4_MADR;
    s32 index;

    if (madr == reinterpret_cast<u32>(decoder->tags[decoder->ring_sectors + 1]))
    {
        index = 0;
    }
    else
    {
        index = (madr - reinterpret_cast<u32>(decoder->sectors)) / LIB_MOVIE_SECTOR_SIZE;
    }

    s32 consumed = (index + decoder->ring_sectors - decoder->unkC9994) % decoder->ring_sectors;
    decoder->unkC9994 = (decoder->unkC9994 + consumed) % decoder->ring_sectors;
    decoder->unkC9998 -= consumed;
    index = (decoder->unkC9994 + decoder->unkC9998) % decoder->ring_sectors;
    s32 count = decoder->unkC999C / LIB_MOVIE_SECTOR_SIZE;
    decoder->unkC999C %= LIB_MOVIE_SECTOR_SIZE;
    u8 extended = 0;

    if (count > 0)
    {
        s32 last = (decoder->ring_sectors + (decoder->unkC9994 + decoder->unkC9998 - 1)) % decoder->ring_sectors;
        *(u64*)((u32)decoder->tags[last] | UNCACHED_SEGMENT) =
            DMA_TAG(LIB_MOVIE_SECTOR_SIZE / 16, DMA_TAG_ID_REF, (u8*)decoder->sectors + last * LIB_MOVIE_SECTOR_SIZE);
        extended = 1;
    }

    for (s32 i = 0; i < count; i++)
    {
        if (i == count - 1)
        {
            *(u64*)((u32)decoder->tags[index] | UNCACHED_SEGMENT) =
                DMA_TAG(LIB_MOVIE_SECTOR_SIZE / 16, DMA_TAG_ID_REFE, (u8*)decoder->sectors + index * LIB_MOVIE_SECTOR_SIZE);
        }
        else
        {
            *(u64*)((u32)decoder->tags[index] | UNCACHED_SEGMENT) =
                DMA_TAG(LIB_MOVIE_SECTOR_SIZE / 16, DMA_TAG_ID_REF, (u8*)decoder->sectors + index * LIB_MOVIE_SECTOR_SIZE);
        }

        index = (index + 1) % decoder->ring_sectors;
    }

    decoder->unkC9998 += count;

    if (decoder->unkC9998)
    {
        if (extended)
        {
            chcr = (chcr & 0x0FFFFFFF) | DMA_TAG_ID_REF;
        }

        LibInterruptLock interrupts;
        *D_ENABLEW = *D_ENABLER | D_ENABLE_SUSPEND;
        *D4_CHCR = chcr | DMA_CHCR_START;
        *D_ENABLEW = *D_ENABLER & ~D_ENABLE_SUSPEND;
    }

    if (decoder->unkC9998)
    {
        return true;
    }

    return 0;
}

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

extern "C"
{
    /**
     * @brief Demultiplex a PSS stream chunk into libmpeg's ring.
     * @param mpeg libmpeg decoder.
     * @param data Stream data.
     * @param size Bytes of stream data.
     * @param ring Ring buffer.
     * @param ring_size Ring buffer size.
     * @return Bytes consumed.
     */
    s32 sceMpegDemuxPssRing(void* mpeg, u8* data, s32 size, u8* ring, s32 ring_size);

    /**
     * @brief Keep the movie's sound stream fed.
     * @param stream Movie stream.
     * @return Bytes handed to the sound stream.
     */
    s32 func_004144F0(LibMovieStream* stream);
}

/**
 * @brief Read how much the archive still has to read for its streaming read, under its semaphore.
 * @param archive Resource archive.
 * @return Bytes left to read.
 */
static inline s32 lib_archive_pending(ResidentArchive* archive)
{
    (void)archive->disc_thread.semaphore.wait();
    s32 remaining = archive->disc_thread.unk88;
    (void)archive->disc_thread.semaphore.signal();
    return remaining;
}

/**
 * @brief Feed the decoder from the disc while a movie plays: take what the archive's ring holds (at most 0x1E000
 *        bytes, half that for a skippable movie), end the stream on a sequence end code or on the movie's own end
 *        marker, otherwise demultiplex it into libmpeg's ring; end the stream once the archive has nothing left to
 *        read. Sleeps between passes.
 */
void LibMovieThread::run()
{
    for (;;)
    {
        if (player->is_playing)
        {
            ResidentArchive* archive = g_resource_archive;

            if (archive->read_busy || lib_archive_pending(archive) > 0)
            {
                u8* data;
                s32 size = resident_archive_get_ring_positions(g_resource_archive, reinterpret_cast<u32*>(&data));

                func_00414D30(&decoder->input, size);

                if (player->unk15E796)
                {
                    size = (size > 0x1E000) ? 0x1E000 : size;
                    size /= 2;
                }
                else
                {
                    size = (size > 0x1E000) ? 0x1E000 : size;
                }

                if (size > 0)
                {
                    u8 ended = 0;

                    if (data[0] == 0 && data[1] == 0 && data[2] == 1 && data[3] == 0xB9 && size == 0x800)
                    {
                        decoder->end_stream();
                        ended = 1;
                    }
                    else if (player->unk15E797 && player->unk15E7A0 == size)
                    {
                        s32 i;

                        for (i = 0; i < 8; i++)
                        {
                            if (player->unk15E798[i] != data[i])
                            {
                                break;
                            }
                        }

                        if (i == 8)
                        {
                            decoder->end_stream();
                            ended = 1;
                        }
                    }

                    if (!ended)
                    {
                        // TODO: The mpeg argument only lands in the game's register with the decoder in a local,
                        // and the ring start only keeps its two additions when it reads the member again.
                        LibMovieDecoder* target = decoder;
                        size = sceMpegDemuxPssRing(target->mpeg, data, size, decoder->input.aligned_data(),
                                                   LIB_MOVIE_STREAM_BUFFER_SIZE);
                        func_00414CE0(&decoder->input, size);
                        resident_archive_consume_ring(g_resource_archive, size);
                    }
                }
                else
                {
                    resident_archive_consume_ring(g_resource_archive, 0);
                }

                func_004144F0(stream);
            }
            else if (decoder->stopped != 2)
            {
                decoder->end_stream();
            }
        }

        resident_thread_sleep();
    }
}

extern "C"
{
    /**
     * @brief Ask libmpeg whether its reference buffers are empty.
     * @param mpeg libmpeg decoder.
     * @return Nonzero when they are.
     */
    s32 sceMpegIsRefBuffEmpty(void* mpeg);

    /**
     * @brief Decode the next picture into a free frame once enough data is buffered.
     * @param decoder Movie decoder.
     * @return 0 after a picture or when there is nothing to do yet, -1 once the stream has ended.
     */
    s32 func_004152C0(LibMovieDecoder* decoder);
}

/**
 * @brief Tell whether the decoder has used up its input: nothing left in the ring and libmpeg's reference buffers
 *        empty.
 * @param decoder Movie decoder.
 * @return Nonzero when drained.
 */
static inline s32 lib_movie_drained(LibMovieDecoder* decoder)
{
    s32 buffered;

    {
        LibSemaphoreLock lock(&decoder->semaphore);
        buffered = (decoder->unkC999C & ~0x7FF) + decoder->unkC9998 * 0x800;
    }

    bool drained = buffered == 0;

    if (drained)
    {
        drained = sceMpegIsRefBuffEmpty(decoder->mpeg);
    }

    return drained;
}

/**
 * @brief Stop the movie once it has finished; otherwise wake the reading thread and, unless the movie can be
 *        skipped and this is an odd frame, wait for the last packet and decode the next picture.
 */
void LibMoviePlayer::update()
{
    if (!is_playing)
    {
        return;
    }

    s32 state = decoder.stopped;

    if (state == 3 || (state == 2 && (lib_movie_drained(&decoder) || decoder.unk15E64C > 10)) || unk15E790 > 20)
    {
        is_playing = 0;
        g_resource_queue->unk2c = 0;
        resident_archive_do_nothing(g_resource_archive);
        resident_archive_stop_ring_read(g_resource_archive);
        stream.stop_sound();
        return;
    }

    resident_thread_wake(thread);

    if (unk15E796 && (g_input_system->vblank_total & 1))
    {
        return;
    }

    if (unk63)
    {
        // TODO: the wait reloads the flag every pass, which only volatile gives me so far.
        while (!*(volatile u8*)&unk62)
        {
        }
    }

    func_004152C0(&decoder);
}

// TODO: the compiler emits its out-of-line copies of inline destructors with whatever inline depth is set here at
// the end of the file. The list aggregate's copies (LibClass172320, LibClass1723F0) only match at depth one.
#pragma inline_depth(1)
