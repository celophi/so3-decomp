#ifndef SO3_OVERLAYS_LIB_TEXT_004095C0_H
#define SO3_OVERLAYS_LIB_TEXT_004095C0_H

#include "types.h"
#include "main/item_category.h"

typedef struct FieldRecord FieldRecord;

typedef struct ItemCreationAllocationRecord ItemCreationAllocationRecord;

typedef struct ItemCreationCategoryDefinition ItemCreationCategoryDefinition;

typedef struct ResidentObject1B64F8 ResidentObject1B64F8;

typedef struct LibClass1721B0 LibClass1721B0;

/** Thirty-two-byte item definition with packed stats, factors and inventory flags. */
struct ItemCreationCategoryDefinition
{
    u32 base_price : 24;
    u32 stamina : 8;
    u32 attack : 14;
    u32 hit : 14;
    /** Variant added to character-specific weapon resource IDs. */
    u32 weapon_variant : 4;
    u32 agility : 14;
    u32 defense : 14;
    u32 category : 3;
    /** Unused catalog entry, excluded from invention candidate lists. */
    u32 unused : 1;
    u32 intelligence : 14;
    u32 equipment_mask : 10;
    u32 luck : 8;
#ifdef __cplusplus
    u32 sort_order : 10;
    u32 model_index : 10;
    u32 initial_factor : 10;
    u32 usage_flags : 2;
#else
    union
    {
        struct
        {
            u32 sort_order : 10;
            u32 model_index : 10;
            u32 initial_factor : 10;
            u32 usage_flags : 2;
        };
        /** Low halfword containing the ten-bit list-order key. */
        u16 sort_key_bits;
    };
#endif
    u8 unk14[3];
    u8 unk17_low : 6;
    u8 unlimited_stock : 1;
    /** Also selects the reserved 100-allocation inventory pool. */
    u8 unsellable : 1;
    u8 unk18[3];
    u8 unk1b_low : 6;
    /** May supply factors as the second item in synthesis. */
    u8 synthesis_material : 1;
    u8 unk1b_high : 1;
    u32 final_factor : 10;
    /** Base difficulty used by invention and Specify Plan. */
    u32 creation_difficulty : 7;
    u32 creation_skill_id : 3;
    u32 unk1c_high : 12;
};

/** Item allocation records in the game state. */
#define LIB_ALLOCATION_COUNT 3000

/** Twelve-byte and 0x34-byte records in the game state. */
#define LIB_GAME_STATE_RECORD0C_COUNT 38
#define LIB_GAME_STATE_RECORD34_COUNT 12

/** LibGameStateTimer and LibGameStateBitset entries in the game state. */
#define LIB_GAME_STATE_TIMER_COUNT 32
#define LIB_GAME_STATE_BITSET_COUNT 11

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

/** Twelve-byte game state record. */
typedef struct LibGameStateRecord0C
{
    u32 unk00;
    u16 unk04;
    u8 unk06;
    u8 unk07;
    u8 unk08;
    u8 unk09;
    u8 unk0a;
    u8 unk0b;
} LibGameStateRecord0C;

/** 0x34-byte game state record; only its setters are known. */
typedef struct LibGameStateRecord34
{
    u8 unk00[0x34];
} LibGameStateRecord34;

/** Six-byte game state entry that counts up once it has an item type. */
typedef struct LibGameStateTimer
{
    /** One-based item type ID, or zero when the entry is free. */
    u16 item_type;

    /** One bit per LibGameStateBitset, lowest first. */
    u16 bitset_mask;

    u16 elapsed;
} LibGameStateTimer;

/** 0x60-byte game state bitset indexed by item type ID minus one. */
typedef struct LibGameStateBitset
{
    u16 count;
    u8 bits[0x5E];
} LibGameStateBitset;

/** Resident game state at D_001B64F8: allocation records, their category links and entries, and later records. */
typedef struct LibGameState
{
    LibAllocationEquipmentView allocations[LIB_ALLOCATION_COUNT];
    LibInventoryAllocationLinks links[LIB_ALLOCATION_COUNT];
    ItemCreationCategoryRecord item_types[ITEM_TYPE_COUNT];
    LibGameStateRecord0C unk10d88[LIB_GAME_STATE_RECORD0C_COUNT];
    LibGameStateRecord34 unk10f50[LIB_GAME_STATE_RECORD34_COUNT];
    LibGameStateTimer timers[LIB_GAME_STATE_TIMER_COUNT];
    LibGameStateBitset bitsets[LIB_GAME_STATE_BITSET_COUNT];
    u32 unk116a0;
    u32 unk116a4;
    s32 unk116a8;
    u32 unk116ac;
    s32 unk116b0;
    u8 unk116b4[0x6C];

    /** Count a LibGameStateTimer reaches before it fires. */
    u16 timer_limit;

    u16 unk11722;
    u16 unk11724;
    u16 unk11726;
    u8 unk11728[2];
    u16 unk1172a;
    u8 unk1172c[2];
    u16 unk1172e;
    u8 unk11730[0x30];
    u8 unk11760[0x1C];

    /** IDs of the active LibGameStateRecord0C entries, highest unk00 first, then zeros. */
    u8 record0c_order[LIB_GAME_STATE_RECORD0C_COUNT];

    u8 unk117a2;

    /** Active entries in record0c_order. */
    u8 record0c_order_count;

    u8 unk117a4;
    u8 unk117a5;
    u8 unk117a6[0x1E];
} LibGameState;

typedef ItemCreationCategoryRecord LibCategoryRecord;
typedef ItemCreationCategoryDefinition LibCategoryDefinition;

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Follow count list links from the object's first node. @return The node reached, or null if traversal ends early. */
void* func_00411DD0(void* object, s32 count);

/** Resident category catalog. */
extern ItemCreationCategoryDefinition* D_001B64F0;

/**
 * @brief Remove a flagged record from its category list and update the resident counts.
 * @param state Resident record and category-list storage.
 * @param identifier One-based signed record identifier from one through three thousand.
 * @return One on success, or zero when the identifier is invalid or the record is not flagged.
 */
s32 func_0040C9F0(void* state, s16 identifier);

/**
 * @brief Record which character has an allocation equipped and update its item type's counts.
 * @param inventory Resident game state.
 * @param identifier One-based allocation ID.
 * @param owner One-based character number, or zero to unequip.
 * @return One when the allocation is in use; zero for an invalid ID or a free allocation.
 */
s32 lib_allocation_set_equipped_owner(ResidentObject1B64F8* inventory, s16 identifier, s32 owner);

/**
 * @brief Remove the first unequipped allocation of an item type through func_0040C9F0.
 * @param state Game state.
 * @param item_type One-based item type ID.
 * @return func_0040C9F0's result, or zero when the item type has no unequipped allocation.
 */
s32 func_0040C8F0(LibGameState* state, u16 item_type);

/**
 * @brief Recount an item type's inventory, equipped and battle-usable items and update its flags.
 * @param state Game state.
 * @param item_type One-based item type ID.
 */
void func_0040D050(LibGameState* state, u16 item_type);

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
s16 func_0040CC70(LibGameState* state, u16 item_type, u8 modification_number, u8 creator_id, const u16* factors, bool new_item);

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
                               bool suppress_allocation_id);

/**
 * @brief Collect a category's allocation records that have no equipped owner.
 * @param state Resident record and category-list storage.
 * @param records Output array receiving pointers to the collected records.
 * @param category One-based category identifier from one through seven hundred fifty.
 * @return Number of collected records, or zero for an invalid identifier or empty list.
 */
s32 lib_collect_unequipped_allocations(const void* state, ItemCreationAllocationRecord** records, u16 category);

/**
 * @brief Return a packed record's table identifier unless its validated flag suppresses it.
 * @param record Packed item record to validate and locate in the resident table.
 * @return One-based table identifier, or zero for a valid checksum and bit 6 set in byte 7.
 */
s16 lib_allocation_get_identifier(const ItemCreationAllocationRecord* record);

/**
 * @brief Read one of eight ten-bit packed values when the record checksum is valid.
 * @param record Packed item record to validate and read.
 * @param index Packed value index from zero through seven.
 * @return The packed value, or zero for an invalid checksum or index.
 */
u16 func_0040D930(const ItemCreationAllocationRecord* record, u32 index);

/**
 * @brief Calculate eight comparison values for a protected entry and detail.
 * @param code Selected entry code.
 * @param entry Protected entry record, updated when its encoded values are repaired.
 * @param detail Protected detail record.
 * @param first First output value.
 * @param second Second output value.
 * @param third Third output value.
 * @param fourth Fourth output value.
 * @param fifth Fifth output value.
 * @param sixth Sixth output value.
 * @param seventh Seventh output value.
 * @param eighth Eighth output value.
 * @return Nonzero when the comparison values are available.
 */
u8 func_004095C0(s32 code, FieldRecord* entry, void* detail, s32* first, s32* second, s32* third, s32* fourth, s32* fifth, s32* sixth, s32* seventh,
                 s32* eighth);

/**
 * @brief Return the floating-point value 0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_00412C30(void* object);


/** Store the word at receiver offset 0x0. */
void func_0040B690(void* object, u32 value);

/** @brief Check whether the byte at receiver offset 0x6 is at least 0x1D. @param object Receiver containing the byte. @return One when the byte is at least 0x1D; otherwise zero. */
s32 func_0040B6A0(void* object);


/** Store the byte at receiver offset 0x33. */
void func_0040B640(void* object, u8 value);

/** Store the byte at receiver offset 0x32. */
void func_0040B660(void* object, u8 value);

/** Store the byte at receiver offset 0x8. */
void func_0040B670(void* object, u8 value);

/** Store the byte at receiver offset 0x9. */
void func_0040B680(void* object, u8 value);

/** Store the byte at receiver offset 0x6. */
void func_0040B6B0(void* object, u8 value);

/**
 * @brief Report which memory card slots are ready.
 * @param object Save data manager.
 * @return Bit 0 for slot 1 and bit 1 for slot 2, or zero while the card isn't ready.
 */
u16 func_0040F0B0(LibClass1721B0* object);

/**
 * @brief Start a card operation in a mode on slot 0 or 1, resetting the transfer state.
 * @param object Save data manager.
 * @param slot Memory card slot, 0 or 1.
 * @param mode Operation mode stored in unk878; modes 6 and 14 clear extra state.
 * @return One when started; zero without a memory card or for another slot.
 */
s32 func_0040F110(LibClass1721B0* object, u16 slot, u16 mode);

/**
 * @brief Store unk20 and reset the transfer state; a negative value also frees the two buffers.
 * @param object Save data manager.
 * @param value New unk20.
 */
void func_0040F210(LibClass1721B0* object, s16 value);

/**
 * @brief Clear the two card files and point the file request at them.
 * @param object Save data manager.
 * @return One.
 */
s32 func_0040F2E0(LibClass1721B0* object);

/**
 * @brief Clear the icon.sys buffer, reallocate and clear the save data buffer and point the file request at both.
 * @param object Save data manager.
 * @return One.
 */
s32 func_0040F3E0(LibClass1721B0* object);

/** Store the byte at receiver offset 0x8D4. */
void func_0040FAF0(void* object, u8 value);

/** Store the byte at receiver offset 0x90A. */
void func_0040FB00(void* object, u8 value);


/** Store the low halfword at receiver offset 0x30. */
void func_0040B650(void* object, u32 value);

/** Store the low halfword at receiver offset 0x2. */
void func_0040B6C0(void* object, u16 value);

/**
 * @brief Clear an allocation record, give it a random checksum shift and store its checksum.
 * @param record Allocation record.
 */
void func_0040B6D0(void* record);

/**
 * @brief Decode the item catalog and reset the resident game state for a new game.
 * @param data Game data resource, or null to load it from the archive here.
 * @return One on success, or zero when the catalog can't be loaded or decoded.
 */
s32 lib_reset_game_state(u8* data);

/**
 * @brief Check whether a code is one of the three codes at D_001B619C.
 * @param code Code to look for.
 * @return One when the code is listed, otherwise zero.
 */
s32 func_0040A970(s32 code);

/**
 * @brief Check whether a code is one of the three codes at D_001B6198.
 * @param code Code to look for.
 * @return One when the code is listed, otherwise zero.
 */
s32 func_0040A9B0(s32 code);

/**
 * @brief Run func_0040A9F0 for a code with flag 1, and again with flag 0 for codes 1 through 29 of code lists 2 and 9.
 * @param entry Protected entry record.
 * @param list_id One-based code list ID.
 * @param code Selected code.
 * @param first Passed through to func_0040A9F0.
 * @param second Passed through to func_0040A9F0.
 */
void func_0040A520(FieldRecord* entry, s32 list_id, s32 code, s32 first, s32 second);

s32 func_0040A9F0(FieldRecord* entry, s32 list_id, s32 code, s32 flag, s32 first, s32 second);

/**
 * @brief Find a code in one of the ten code tables at D_001B64D0.
 * @param id One-based code table ID.
 * @param code Code to look for: 129 through 154 in the high codes, 30 through 128 (or 1 through 29 for tables 2 and 9) in
 * the low codes.
 * @return The code's position, counting the 26 high codes first, or -1 when it isn't found.
 */
s32 func_0040AE00(s32 id, s32 code);

/**
 * @brief Find a code in one of the ten code lists at D_001B64CC.
 * @param id One-based code list ID.
 * @param code Code to look for.
 * @return Index of the code's entry in the list, or -1 for an invalid ID or a code that isn't listed.
 */
s32 func_0040AF10(s32 id, s32 code);

/**
 * @brief Read the five-bit unk14 field of a D_504AA0 factor record.
 * @param id One-based record ID, below 0x2C0.
 * @return The field, or zero for an invalid ID.
 */
s32 func_0040B2F0(u16 id);

/**
 * @brief Find a code's one-based position in the eleven codes at D_505620.
 * @param code Code to look for.
 * @return The last matching position, or zero when the code isn't listed.
 */
s32 func_0040B360(s32 code);

/**
 * @brief Clear the byte at receiver offset 0x8D4.
 * @param object Receiver.
 * @return The halfword at receiver offset 0x20.
 */
s16 func_0040FAE0(void* object);

/**
 * @brief Allocate the item catalog buffer and the resident game state.
 * @return One when the game state was allocated; zero when either allocation fails.
 */
s32 func_0040B760();

/**
 * @brief Run the game state's func_0040BB00 and func_0040C690 updates and restart its random countdown.
 * @param state Game state.
 */
void func_0040B7E0(LibGameState* state);

/**
 * @brief Advance the game state by one frame: its two countdowns and every running LibGameStateTimer.
 * @param state Game state.
 * @return Nonzero when an update or a finished timer changed the state this frame.
 */
u8 func_0040B840(LibGameState* state);

s32 func_0040BB00(LibGameState* state);

/**
 * @brief Start a game state timer for an item type, finishing the most recently started timer when none is free.
 * @param state Game state.
 * @param item_type One-based item type ID.
 */
void func_0040C180(LibGameState* state, u16 item_type);

/**
 * @brief Give an item type its inventor, set its flags and add a random amount to its shop stock.
 * @param state Game state.
 * @param item_type One-based item type ID.
 * @param inventor_id Inventor to record.
 * @param set_flag04 Nonzero to set flag 0x04 on the item type.
 * @param set_flag08 Nonzero to set flag 0x08 and count the item type in unk11726 (flag 0x04 set) or unk1172a.
 * @return One when the inventor was recorded; zero for an unlimited-stock item type or one that already has an inventor.
 */
s32 func_0040C300(LibGameState* state, u16 item_type, u8 inventor_id, s32 set_flag04, s32 set_flag08);


/**
 * @brief Pick 11 to 15 random LibGameStateRecord0C entries with unk08 and unk09 set and unk0a clear, give each a random
 * listed item type from its D_501EE0 row and list their IDs in unk11760.
 * @param state Game state.
 */
void func_0040BF50(LibGameState* state);

/**
 * @brief Add a D_5055D0 payout for each ranked LibGameStateRecord0C with unk08 of at least 2 to the stored Fol.
 * @param state Game state.
 */
void func_0040C4C0(LibGameState* state);

void func_0040C690(LibGameState* state);

/**
 * @brief Lower the stored count of each of an allocation's factors by one.
 * @param object Unused.
 * @param record Allocation record whose factors are counted.
 */
void func_0040D1E0(void* object, const ItemCreationAllocationRecord* record);

/**
 * @brief Raise the stored count of each of an allocation's factors by one.
 * @param object Unused.
 * @param record Allocation record whose factors are counted.
 */
void func_0040D260(void* object, const ItemCreationAllocationRecord* record);

/**
 * @brief Add up the D_5055A0 values of an allocation's factors.
 * @param record Allocation record.
 * @return The total, at most 100; 100 when the factors add nothing and the allocation isn't equipped.
 */
s32 func_0040D680(const ItemCreationAllocationRecord* record);

/**
 * @brief Calculate an allocation's price: its catalog base price plus the price of each factor.
 * @param record Allocation record.
 * @return The price, at most 99999999.
 */
u32 func_0040D760(ItemCreationAllocationRecord* record);

/** Return the fixed integer value 4. */
s32 func_0040E3A0(void* object);

/** Return the fixed integer value 1. */
s32 func_00415030(void* object);

/** Return the fixed integer value 12. */
s32 func_004194F0(void* object);

/** Return the fixed value 0. */
s32 func_004152B0(void* object);

void func_00411E10(void* object);
void func_00411E20(void* object);
void func_00412C00(void* object);
void func_00412C10(void* object);
void func_00412C20(void* object);
void func_00412C40(void* object);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Free the allocation func_0040AFA0 made. */
void func_0040AF80(void);

/** @brief Remove the value table from the resident entry table and free it. */
void func_0040B1F0(void);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
    u32 func_0040AFA0();

    /**
     * @brief Create the value table and store it in the resident entry table.
     * @return One when it was stored, or zero when the table is full.
     */
    u32 func_0040B250();
}
#endif

#endif
