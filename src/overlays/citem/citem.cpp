#include "overlays/citem/citem.h"
#include "include_asm.h"
#include "main/resident_001001E0.h"
#include "main/resident_data.h"
#include "overlays/lib/ui_object.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_001E1590.h"
#include "overlays/1067-00/text_0023B1D0.h"
#include "overlays/lib/text_0044ABE0.h"
#include "main/resident_0010A0E0.h"
#include "overlays/1067-00/text_0028E240.h"
#include "main/resident_00101260.h"
#include "main/resident_0011EE70.h"
#include "overlays/lib/text_004095C0.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/1067-00/text_002E1870.h"
#include "overlays/lib/item_allocation.h"
#include "overlays/1067-00/text_002D3BD0.h"
#include "overlays/1067-00/text_002D5260.h"
#include "overlays/1067-00/text_002F9C90.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/1067-00/text_002AE9E0.h"
#include "overlays/lib/resource_widget_inlines.h"
#include "overlays/lib/list_indicator_inlines.h"
#include "overlays/lib/movement_widget_inlines.h"
#include "overlays/lib/text_00419A70.h"
#include "overlays/lib/marker_widget_inlines.h"
#include "overlays/1067-00/text_marker.h"

/** Half a degree, in radians. */
#define MODEL_TURN_STEP 0.008726646f

/** Thirty degrees, in radians. */
#define MODEL_TURN_LIMIT 0.5235988f

/** Event flag of the first valuable; the rest follow in order. */
#define ITEM_VALUABLE_FIRST_FLAG 1900

#define ITEM_STAT_WORD_XOR_KEY 0x7DE3F7E3
#define ITEM_STAT_HALFWORD_XOR_KEY 0x7E93

enum ItemMessageKey
{
    ITEM_MSG_SEPARATOR = 0x7E4,
    ITEM_MSG_TITLE = 0x1B58,
    ITEM_MSG_CATEGORY_NAME_BASE = 0x1B62,
    ITEM_MSG_CATEGORY_HELP_BASE = 0x1B6C,
    ITEM_MSG_EQUIP_WEAPON_HELP = 0x1B76,
    ITEM_MSG_EQUIP_ARMOR_HELP = 0x1B77,
    ITEM_MSG_EQUIP_ACCESSORY_1_HELP = 0x1B78,
    ITEM_MSG_EQUIP_ACCESSORY_2_HELP = 0x1B79,
    ITEM_MSG_USE_HELP = 0x1B7A,

    /** One past the last key the help window accepts. */
    ITEM_MSG_HELP_END = 0x1B7B,

    ITEM_MSG_BACK_PROMPT = 0x1B7D,
    ITEM_MSG_SELECT_PROMPT = 0x1B7E,
    ITEM_MSG_SORT_PROMPT = 0x1B80,
    ITEM_MSG_FACTOR_HEADING = 0x1B8C,
    ITEM_MSG_CAPTION = 0x1B8E,
    ITEM_MSG_EMPTY = 0x1B8F,
    ITEM_MSG_HP_MP_SEPARATOR = 0x1B93,
    ITEM_MSG_ATK = 0x1B94,
    ITEM_MSG_DEF = 0x1B96,
    ITEM_MSG_INT = 0x1B98,
    ITEM_MSG_STAT_UP = 0x1B99,
    ITEM_MSG_STAT_DOWN = 0x1B9A,
    ITEM_MSG_STAT_SAME = 0x1B9B,
    ITEM_MSG_STAT_NONE = 0x1B9C,
    ITEM_MSG_DROP_DETAILS_PROMPT = 0x1B9D,
    ITEM_MSG_BACK_USE_PROMPT = 0x1B9E,
    ITEM_MSG_SWITCH_BACK_PROMPT = 0x1B9F,
    ITEM_MSG_DETAILS_BACK_PROMPT = 0x1BA0,
    ITEM_MSG_DROP_TITLE = 0x1BA1,
    ITEM_MSG_DROP_QUESTION = 0x1BA2,
    ITEM_MSG_YES = 0x1BA3,
    ITEM_MSG_NO = 0x1BA4,

    /** Key 50000 is "(None)", so a one-based item type ID can be added directly. */
    ITEM_MSG_ITEM_NAME_BASE = 50000,

    ITEM_MSG_ITEM_DESCRIPTION_BASE = 55000,
    ITEM_MSG_FIRST_FACTOR_NAME = 70001,
    ITEM_MSG_VALUABLE_NAME_BASE = 75001,
    ITEM_MSG_VALUABLE_DESCRIPTION_BASE = 76001
};

/** Category window rows. Rows 0 to 6 are also the item definitions' category values. */
enum ItemCategory
{
    ITEM_CATEGORY_WEAPONS = 0,
    ITEM_CATEGORY_ARMOR = 1,
    ITEM_CATEGORY_ACCESSORIES = 2,
    ITEM_CATEGORY_USABLE = 3,
    ITEM_CATEGORY_FOOD = 4,
    ITEM_CATEGORY_OTHER = 5,
    ITEM_CATEGORY_MATERIALS = 6,
    ITEM_CATEGORY_VALUABLES = 7,
    ITEM_CATEGORY_COMBAT = 8,
    ITEM_CATEGORY_NEW = 9
};

// Sized like the u8 column parameter it feeds.
#pragma enumsalwaysint off
/** Column count of a selection widget. */
enum SelectorColumns
{
    SELECTOR_SINGLE_COLUMN = 1
};
#pragma enumsalwaysint reset

/** Bits of ItemCreationCategoryDefinition::usage_flags. */
enum
{
    ITEM_USE_IN_MENU = 1,
    ITEM_USE_IN_BATTLE = 2
};

enum
{
    ITEM_COLOR_NORMAL = 0x808080,
    ITEM_COLOR_SELECTED = 0x288080,
    ITEM_COLOR_DISABLED = 0x505080,
    ITEM_COLOR_NEW_ITEM = 0x508050,
    ITEM_COLOR_HEADING = 0x805050
};

/** Partial loaded-resource header containing the block's byte count. */
struct ItemAlignedResource
{
    u8 unk00[0x40];
    s32 byte_count;
};

/** Partial resource runtime containing the item-name and detail-code resource groups. */
struct FieldRuntime
{
    u8 unk00[0x514];
    s32 item_name_resource_slot;
    u32 item_name_base_key;
    s32 detail_resource_slot;
    u32 detail_base_key;
    u8 unk524[0x10];

    /** Screen scale and offset applied to menu coordinates. */
    float screen_scale_x;
    float screen_scale_y;
    float screen_offset_x;
    float screen_offset_y;
};

/** Packed allocation view with the four-bit equipped owner spanning bytes C and D. */
struct ItemAllocationOwnerView
{
    u8 unk00[12];
    u16 modification_number : 7;
    u16 equipped_owner : 4;
    u16 unk0d_high : 5;
    u16 checksum;
};

/** Partial 0xC4-byte character record with checksum-protected flags, HP and MP. */
typedef struct ItemCharacterStats
{
    u8 unk00[2];
    /** Selects the clamping rules used by the character stat setters. */
    s16 stat_limit_type;
    u8 unk04[4];
    u32 encoded_flags;
    s32 encoded_experience;
    u32 encoded_base_hp;
    u32 encoded_max_hp;
    u32 encoded_hp;
    u32 encoded_base_mp;
    u32 encoded_max_mp;
    u32 encoded_mp;
    float unk28;

    /** Fury is stored at sixteen times its displayed amount. */
    float scaled_max_fury;

    float scaled_fury;
    s32 encoded_base_attack;
    s32 encoded_effective_attack;
    s32 encoded_attack;
    s32 encoded_base_defense;
    s32 encoded_effective_defense;
    s32 encoded_defense;
    s32 encoded_base_agility;
    s32 encoded_effective_agility;
    s32 encoded_agility;
    s32 encoded_base_hit;
    s32 encoded_effective_hit;
    s32 encoded_hit;

    /** Intelligence is validated through the HIT checksum. */
    s32 encoded_base_intelligence;

    s32 encoded_effective_intelligence;
    s32 encoded_intelligence;
    u8 unk70[0x14];
    s32 level_checksum;
    u32 flags_experience_checksum;
    u32 hp_checksum;
    u32 mp_checksum;
    s32 attack_checksum;
    s32 defense_checksum;
    s32 agility_checksum;
    s32 hit_checksum;
    s32 knockback_power_checksum;
    u32 checksum_salt;
    u8 unkac[0x18];

    /** @brief Decode the protected flag word. @return Flags, or five when the check word is invalid. */
    u32 get_flags() const
    {
        s32 experience = encoded_experience;

        if (flags_experience_checksum != (checksum_salt ^ (experience ^ (encoded_flags + checksum_salt))))
        {
            return 5;
        }

        return encoded_flags ^ ITEM_STAT_WORD_XOR_KEY;
    }
} ItemCharacterStats;

/** Checksum-protected 0x114-byte character equipment record. */
class ItemCharacterEquipment
{
    public:
        u8 unk00[0xE];

        /** Highest valid index into encoded_equipment_ids. */
        s16 encoded_slot_limit;

        s16 encoded_equipment_ids[4];
        s16 encoded_sp;
        s16 encoded_cp;
        s32 unk1c;
        char character_name[24];
        u8 unk38[0xB8];
        u32 equipment_checksum;
        u8 unkf4[0x18];
        u32 checksum_salt;
        u32 unk110;

        /** @brief Test the stored equipment checksum. @return True when it agrees with the encoded IDs and the salt. */
        bool equipment_valid() const
        {
            return equipment_checksum ==
                   (checksum_salt ^ ((encoded_equipment_ids[1] + encoded_equipment_ids[2]) ^ (encoded_equipment_ids[3] + encoded_equipment_ids[0])));
        }

        /**
         * @brief Decode the item equipped in a slot.
         * @param index Equipment slot.
         * @return Item ID, or zero for an invalid checksum or slot.
         */
        s16 get_equipment_id(s32 index) const
        {
            if (!equipment_valid())
            {
                return 0;
            }

            if (index < 0)
            {
                return 0;
            }

            if (index > (encoded_slot_limit ^ ITEM_STAT_HALFWORD_XOR_KEY))
            {
                return 0;
            }

            return encoded_equipment_ids[index] ^ ITEM_STAT_HALFWORD_XOR_KEY;
        }

        /**
         * @brief Equip an item in a slot and update the equipment checksum, when the record and slot are valid.
         * @param index Equipment slot.
         * @param value Item ID.
         */
        void set_equipment_id(s32 index, s16 value)
        {
            if (equipment_valid() && index >= 0 && index <= (encoded_slot_limit ^ ITEM_STAT_HALFWORD_XOR_KEY))
            {
                encoded_equipment_ids[index] = value ^ ITEM_STAT_HALFWORD_XOR_KEY;
                equipment_checksum = checksum_salt ^ ((encoded_equipment_ids[1] + encoded_equipment_ids[2]) ^ (encoded_equipment_ids[3] + encoded_equipment_ids[0]));
            }
        }
};

/** @brief Read a character record's checksum salt. @param record Character stats. @return Salt. */
static inline u32 character_checksum_salt(ItemCharacterStats* record)
{
    return record->checksum_salt;
}

/** @brief Decode current HP, marking valid flags when its checksum fails. @param record Character stats. @return HP, or zero after corruption. */
static inline u32 character_hp(ItemCharacterStats* record)
{
    u32 first = record->encoded_base_hp;
    u32 salt = record->encoded_max_hp;
    u32 key = character_checksum_salt(record);
    u32 encoded = record->encoded_hp;
    u32 checksum = record->hp_checksum;

    if (checksum != ((first + salt) ^ encoded ^ key))
    {
        u32 flags = record->encoded_flags;
        s32 flag_salt = record->encoded_experience;

        if (record->flags_experience_checksum == ((flags + key) ^ flag_salt ^ key))
        {
            record->encoded_flags = ((flags ^ ITEM_STAT_WORD_XOR_KEY) | 1) ^ ITEM_STAT_WORD_XOR_KEY;
            s32 current_salt = record->encoded_experience;
            record->flags_experience_checksum = ((record->encoded_flags + record->checksum_salt) ^ current_salt) ^ record->checksum_salt;
        }

        return 0;
    }

    return encoded ^ ITEM_STAT_WORD_XOR_KEY;
}

/** @brief Decode maximum HP, marking valid flags when its checksum fails. @param record Character stats. @return Maximum HP, or zero after corruption. */
static inline u32 character_max_hp(ItemCharacterStats* record)
{
    u32 first = record->encoded_base_hp;
    u32 salt = record->encoded_max_hp;
    u32 key = character_checksum_salt(record);
    u32 encoded = record->encoded_hp;
    u32 checksum = record->hp_checksum;

    if (checksum != ((first + salt) ^ encoded ^ key))
    {
        u32 flags = record->encoded_flags;
        s32 flag_salt = record->encoded_experience;

        if (record->flags_experience_checksum == ((flags + key) ^ flag_salt ^ key))
        {
            record->encoded_flags = ((flags ^ ITEM_STAT_WORD_XOR_KEY) | 1) ^ ITEM_STAT_WORD_XOR_KEY;
            s32 current_salt = record->encoded_experience;
            record->flags_experience_checksum = ((record->encoded_flags + record->checksum_salt) ^ current_salt) ^ record->checksum_salt;
        }

        return 0;
    }

    return salt ^ ITEM_STAT_WORD_XOR_KEY;
}

/** @brief Decode current MP, marking valid flags when its checksum fails. @param record Character stats. @return MP, or zero after corruption. */
static inline u32 character_mp(ItemCharacterStats* record)
{
    u32 first = record->encoded_base_mp;
    u32 salt = record->encoded_max_mp;
    u32 key = character_checksum_salt(record);
    u32 encoded = record->encoded_mp;
    u32 checksum = record->mp_checksum;

    if (checksum != ((first + salt) ^ encoded ^ key))
    {
        u32 flags = record->encoded_flags;
        s32 flag_salt = record->encoded_experience;

        if (record->flags_experience_checksum == ((flags + key) ^ flag_salt ^ key))
        {
            record->encoded_flags = ((flags ^ ITEM_STAT_WORD_XOR_KEY) | 1) ^ ITEM_STAT_WORD_XOR_KEY;
            s32 current_salt = record->encoded_experience;
            record->flags_experience_checksum = ((record->encoded_flags + record->checksum_salt) ^ current_salt) ^ record->checksum_salt;
        }

        return 0;
    }

    return encoded ^ ITEM_STAT_WORD_XOR_KEY;
}

/** @brief Decode maximum MP, marking valid flags when its checksum fails. @param record Character stats. @return Maximum MP, or zero after corruption. */
static inline u32 character_max_mp(ItemCharacterStats* record)
{
    u32 first = record->encoded_base_mp;
    u32 salt = record->encoded_max_mp;
    u32 key = character_checksum_salt(record);
    u32 encoded = record->encoded_mp;
    u32 checksum = record->mp_checksum;

    if (checksum != ((first + salt) ^ encoded ^ key))
    {
        u32 flags = record->encoded_flags;
        s32 flag_salt = record->encoded_experience;

        if (record->flags_experience_checksum == ((flags + key) ^ flag_salt ^ key))
        {
            record->encoded_flags = ((flags ^ ITEM_STAT_WORD_XOR_KEY) | 1) ^ ITEM_STAT_WORD_XOR_KEY;
            s32 current_salt = record->encoded_experience;
            record->flags_experience_checksum = ((record->encoded_flags + record->checksum_salt) ^ current_salt) ^ record->checksum_salt;
        }

        return 0;
    }

    return salt ^ ITEM_STAT_WORD_XOR_KEY;
}

/** @brief Decode the protected flag word. @param record Character stats. @return Flags, or five when the check word is invalid. */
static inline u32 character_flags(ItemCharacterStats* record)
{
    u32 key = record->checksum_salt;
    u32 value = record->encoded_flags;
    s32 salt = record->encoded_experience;

    if (record->flags_experience_checksum != ((value + key) ^ salt ^ key))
    {
        return 5;
    }

    return value ^ ITEM_STAT_WORD_XOR_KEY;
}

/** Observed prefix of the resident entry-four block containing 3072 flags. */
class ItemFlagBlock
{
    public:
        /**
         * @brief Read one flag as a full-word truth value.
         * @param bit Nonnegative flag index.
         * @return One when set, or zero when clear or beyond the flag block.
         */
        s32 is_set(s32 bit) const
        {
            if (bit >= 3072)
            {
                return false;
            }

            return (flags[bit / 8] & (1 << (bit % 8))) != 0;
        }

        u32 unk00;
        u8 flags[384];
};

/** Partial display settings used to frame the details model. */
struct ItemDisplaySettings
{
    u8 unk00[0x18C];
    u8 widescreen;
};

/** Partial Field menu manager (vtable D_15B020) holding the active menu State. */
struct ItemMenuCallbacks
{
    u8 unk00[0x14];
    FieldClass153E30* state;
};

/** Partial runtime state; unk9a is set when the type list takes focus. */
struct ItemMenuRuntime
{
    u8 unk00[0x9A];
    u8 unk9a;
};

/** Partial resident menu reference. */
struct ItemMenuRef
{
    u8 unk00[4];
    ItemCharacterStats* characters;
    u8 unk08[4];
    ItemMenuRuntime* runtime;
    ItemMenuCallbacks* callbacks;
    u8 unk14[8];
    void* field_camera;
    FieldBufferSlots* resources;
};

extern ResidentObject1B64F8* D_001B64F8;
extern ItemMenuRef* D_001B643C;
extern u16 g_item_valuable_models[];
extern LibVector4 D_50CD30;
extern u64 D_004ED330[];
extern LibWidgetColors4C5590 g_item_drop_title_colors;
extern const char g_item_empty_name[];
extern LibCameraContext* D_001B6650;

// Lib defines these under C names without a shared declaration, and the record functions take this overlay's own types.
extern "C"
{
void func_4D00B0(void* object);
s32 lib_allocation_set_equipped_owner(ResidentObject1B64F8* inventory, s16 identifier, s32 owner);
void lib_character_recalculate_stats(ItemCharacterStats* record, ItemCharacterEquipment* equipment, const ItemCreationAllocationRecord* candidate, s32 index);
}

/**
 * @brief Show a help line when the help window exists.
 * @param window Help window, or null.
 * @param key Help line message key.
 */
static inline void set_item_window_message(ItemHelpWindow* window, s16 key)
{
    if (window != 0)
    {
        window->func_slot60(key);
    }
}

/** @brief Allocate and construct the native panel widget. @return The panel storage, or null. */
static inline LibClass178630* allocate_panel(void)
{
    return new (0) LibClass178630;
}

/** @brief Allocate the native text widget with an empty rectangle. @return The text-widget storage, or null. */
static inline LibObject178750* allocate_text_widget(void)
{
    return new (0) LibObject178750;
}

/** @brief Set the text mode and mark the widget for update. @param widget Text widget. @param mode Text mode. */
static inline void set_text_mode(LibObject178750* widget, u32 mode)
{
    widget->set_mode(mode);
}

/** @brief Set the packed text color and mark the widget for update. @param widget Text widget. @param color Packed color. */
static inline void set_text_color(LibObject178750* widget, u32 color)
{
    widget->set_color(color);
}

/** @brief Apply the window's text scale to one prompt. @param window Control help window. @param index Prompt index. */
static inline void scale_prompt(ItemControlHelpWindow* window, u32 index)
{
    LibObject178750* prompt = window->prompts[index];
    float scale = window->scale;
    prompt->unk84 = scale;
    prompt->unk80 = scale;
    prompt->unk3c = 1;
}

/**
 * @brief Return the 128-byte-aligned resource header.
 * @param buffer Completed resource buffer.
 * @return Aligned resource header.
 */
static inline ItemAlignedResource* aligned_resource(void* buffer)
{
    return reinterpret_cast<ItemAlignedResource*>((reinterpret_cast<u32>(buffer) + 0x7F) & ~0x7F);
}

/** @brief Delete an owned party selection and clear its pointer. @param selection Owned selection. */
static inline void release_record_selection(FieldRecordSelection*& selection)
{
    if (selection != 0)
    {
        delete selection;
        selection = 0;
    }
}

/**
 * @brief Allocate and populate a missing party selection.
 * @param controller Controller that owns the selection.
 * @return One after successful population, or zero if already present or initialization fails.
 */
static inline u8 create_record_selection(ItemController* controller)
{
    FieldRecordSelection* selection;

    if (controller->party != 0)
    {
        return 0;
    }

    selection = new (0) FieldRecordSelection;
    controller->party = selection;

    if (controller->party == 0)
    {
        return 0;
    }

    if ((u8)func_0028E3D0(controller->party) == 0)
    {
        return 0;
    }

    return 1;
}

/**
 * @brief Allocate a coordinate node with its scalar values initially clear.
 * @return Allocated node, or null.
 */
static inline ItemCoordinateNode* allocate_coordinate_node(void)
{
    ItemCoordinateNode* node = new (0) ItemCoordinateNode;
    return node;
}

/**
 * @brief Store display bounds and mark them changed.
 * @param display Display to update.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Display width.
 * @param height Display height.
 */
static inline void set_text_bounds(LibObject178750* display, float x, float y, float width, float height)
{
    display->unk18.unk00 = x;
    display->unk18.unk04 = y;
    display->unk18.unk08 = width;
    display->unk18.unk0c = height;
    display->unk3c = 1;
}

/**
 * @brief Find an item type's category record.
 * @param value One-based item type, narrowed to a halfword.
 * @return Category record, or null outside one through ITEM_TYPE_COUNT.
 */
static inline ItemCreationCategoryRecord* item_category_record(s32 value)
{
    ResidentObject1B64F8* base = D_001B64F8;
    u16 index = value;
    bool valid = false;

    if (index > 0 && index <= ITEM_TYPE_COUNT)
    {
        valid = true;
    }

    if (valid)
    {
        return &base->item_types[index - 1];
    }

    return 0;
}

/**
 * @brief Collect an item type's unequipped allocations.
 * @param category Category record, or null.
 * @param records Receives the allocation records.
 * @param identifier Receives the one-based catalog identifier, or zero.
 * @return Number of records collected.
 */
static inline s32 item_category_allocations(ItemCreationCategoryRecord* category, ItemCreationAllocationRecord** records, u16& identifier)
{
    identifier = 0;
    s32 count = 0;

    if (category != 0)
    {
        u16 id = category->catalog_index + 1;
        identifier = id;
        count = lib_collect_unequipped_allocations(D_001B64F8, records, id);
    }

    return count;
}

/**
 * @brief Test an allocation record's checksum against its six packed halfwords.
 * @param record Allocation record to validate.
 * @return True when the stored checksum differs.
 */
static inline bool item_allocation_invalid(ItemCreationAllocationRecord* record)
{
    return record->checksum != (u16)((0x83CF << record->checksum_shift) ^
        ((((const u16*)record)[4] + (((const u16*)record)[0] + ((const u16*)record)[2])) ^
         (((const u16*)record)[1] + (((const u16*)record)[3] + ((const u16*)record)[5]))));
}

/**
 * @brief Read the catalog definition index from a valid allocation.
 * @param record Allocation record to read.
 * @return Definition index, or zero when the checksum differs.
 */
static inline u16 item_allocation_value(ItemCreationAllocationRecord* record)
{
    if (item_allocation_invalid(record))
    {
        return 0;
    }

    return record->definition_factors.bits.definition_index;
}

/**
 * @brief Set a resource display's brightness on all three colour channels.
 * @param object Resource display.
 * @param value Brightness.
 */
static inline void set_display_brightness(ItemCreationOptionResourceDisplay* object, float value)
{
    object->unk50.unk44 = value;
    object->unk50.unk48 = value;
    object->unk50.unk4c = value;
    object->unk3c = 1;
}

/**
 * @brief Decode a character's checksum-protected attack.
 * @param character Character stats.
 * @return Attack, or zero for an invalid checksum.
 */
static inline s32 character_attack(const ItemCharacterStats& character)
{
    if (character.attack_checksum != (character.checksum_salt ^ (character.encoded_attack ^ (character.encoded_base_attack + character.encoded_effective_attack))))
    {
        return 0;
    }

    return character.encoded_attack ^ ITEM_STAT_WORD_XOR_KEY;
}

/**
 * @brief Decode a character's checksum-protected defense.
 * @param character Character stats.
 * @return Defense, or zero for an invalid checksum.
 */
static inline s32 character_defense(const ItemCharacterStats& character)
{
    if (character.defense_checksum != (character.checksum_salt ^ (character.encoded_defense ^ (character.encoded_base_defense + character.encoded_effective_defense))))
    {
        return 0;
    }

    return character.encoded_defense ^ ITEM_STAT_WORD_XOR_KEY;
}

/**
 * @brief Decode a character's intelligence, which shares the HIT checksum.
 * @param character Character stats.
 * @return Intelligence, or zero for an invalid checksum.
 */
static inline s32 character_intelligence(const ItemCharacterStats& character)
{
    if (character.hit_checksum != (character.checksum_salt ^ (character.encoded_hit ^ (character.encoded_base_hit + character.encoded_effective_hit))))
    {
        return 0;
    }

    return character.encoded_intelligence ^ ITEM_STAT_WORD_XOR_KEY;
}

/**
 * @brief Set a widget's rectangle and mark it for update.
 * @param object Widget to place.
 * @param x Left edge.
 * @param y Top edge.
 * @param width Rectangle width.
 * @param height Rectangle height.
 */
static inline void set_widget_rectangle(LibClass178600* object, float x, float y, float width, float height)
{
    object->unk18.unk00 = x;
    object->unk18.unk04 = y;
    object->unk18.unk08 = width;
    object->unk18.unk0c = height;
    object->unk3c = 1;
}

/**
 * @brief Append a selectable position to a coordinate selector.
 * @param selector Coordinate selector.
 * @param x Horizontal coordinate.
 * @param y Vertical coordinate.
 */
static inline void append_selector_position(ItemCoordinateSelector* selector, float x, float y)
{
    selector->positions.append(ItemCoordinate(x, y));
}

/**
 * @brief Set a numeric widget's value and mark it for update.
 * @param widget Numeric widget.
 * @param value Value to show.
 */
static inline void set_numeric_value(LibObject174F20* widget, s32 value)
{
    widget->numeric_value = value;
    widget->unk3c = 1;
}

/**
 * @brief Add a horizontal offset to a display origin.
 * @param origin Display origin.
 * @param offset Horizontal offset.
 * @return Shifted horizontal coordinate.
 */
static inline float shifted_position(const float& origin, float offset)
{
    return origin + offset;
}

/**
 * @brief Set a selector's brightness and mark it for update.
 * @param selector Selector, or null.
 * @param brightness 128 for full brightness, 64 when dimmed.
 */
static inline void set_selector_brightness(FieldClass153130* selector, float brightness)
{
    if (selector != 0)
    {
        selector->ItemCreationClass185050::unk30 = brightness;
        selector->unk3c = 1;
    }
}

/**
 * @brief Test whether a selector is idle, so it ignores movement.
 * @param selector Coordinate selector to inspect.
 * @return One when its control byte is zero, otherwise zero.
 */
static inline s32 selector_is_idle(ItemCoordinateSelector* selector)
{
    return ((u32)selector->ItemCreationClass185050::unk35 > 0) ^ 1;
}

/** @brief Read the catalog entry's unsellable flag. @param definition Catalog entry. @return Flag as a byte. */
static inline u8 item_definition_unsellable(const ItemCreationCategoryDefinition* definition)
{
    return definition->unsellable;
}

/** @brief Store the window control byte. @param value Control value. */
void FieldClass15AE70::func_slot24(u8 value)
{
    unk0c = value;
}

/** @brief Read the window control byte. @return Control value. */
u8 FieldClass15AE70::func_slot28()
{
    return unk0c;
}

/** @brief Store the byte state code. @param value State code. */
void FieldClass15AE70::func_slot2c(u8 value)
{
    unk08 = value;
}

/** @brief Read the byte state code. @return State code. */
u8 FieldClass15AE70::func_slot30()
{
    return unk08;
}

/** @brief Store the halfword state flags. @param value State flags. */
void FieldClass15AE70::func_slot34(u16 value)
{
    unk0a = value;
}

/** @brief Read the halfword state flags. @return State flags. */
u16 FieldClass15AE70::func_slot38()
{
    return unk0a;
}

/** @brief Store the alternate window pointer. @param associated Pointer to store. */
void FieldClass15AE70::func_slot48(void* associated)
{
    unk9c = associated;
}

/** @brief Return the alternate window pointer. @return Stored pointer. */
void* FieldClass15AE70::func_slot4c()
{
    return unk9c;
}

/** @brief Store the resource source word. @param value Word to store. */
void FieldClass15AE70::func_slot50(u32 value)
{
    unk04 = value;
}

/** @brief Return the resource source word. @return Stored word. */
u32 FieldClass15AE70::func_slot54()
{
    return unk04;
}

/** @brief Return the nested widget container. @return Stored container. */
LibObject178660* FieldClass15AE70::func_slot58()
{
    return unk10;
}

/** @brief Default window hook; does nothing. @param text_key Unused. */
void FieldClass15AE70::func_slot60(s32 text_key)
{
}

/** @brief Default window hook; does nothing. */
void FieldClass15AE70::func_slot64()
{
}

/** @brief Default window hook; does nothing. */
void FieldClass15AE70::func_slot68()
{
}

/** @brief Default window hook; does nothing. */
void FieldClass15AE70::func_slot6c()
{
}

/** @brief Default window hook; does nothing. */
void FieldClass15AE70::func_slot78()
{
}

/** @brief Default window hook; does nothing. */
void FieldClass15AE70::func_slot7c()
{
}

/** @brief Default window hook; does nothing. */
void FieldClass15AE70::func_slot80()
{
}

/** @brief Default window hook; does nothing. */
void FieldClass15AE70::func_slot84()
{
}

/** @brief Default window hook; does nothing. */
void FieldClass15AE70::func_slot88()
{
}

/** @brief Default window hook; does nothing. */
void FieldClass15AE70::func_slot8c()
{
}

/** @brief Default window hook; does nothing. */
void FieldClass15AE70::func_slot90()
{
}

/** @brief Default window hook; does nothing. */
void FieldClass15AE70::func_slot94()
{
}

/** @brief Default window hook; does nothing. */
void FieldClass15AE70::func_slot98()
{
}

/** @brief Default window hook; does nothing. */
void FieldClass15AE70::func_slot9c()
{
}

/** @brief Default window hook; does nothing. */
void FieldClass15AE70::func_slota0()
{
}

/** @brief Default window hook; does nothing. */
void FieldClass15AE70::func_slota4()
{
}

/** @brief Default window hook; does nothing. */
void FieldClass15AE70::func_slota8()
{
}

/** @brief Default window hook; does nothing. */
void FieldClass15AE70::func_slotac()
{
}

/** @brief Default window hook. @return Zero. */
u8 FieldClass15AE70::func_slotb8()
{
    return 0;
}

/** @brief Default window hook. @return Zero. */
u8 FieldClass15AE70::func_slotbc()
{
    return 0;
}

/** @brief Default window hook. @return Zero. */
s32 FieldClass15AE70::func_slotc0()
{
    return 0;
}

/** @brief Default window hook. @return Zero. */
s32 FieldClass15AE70::func_slotc4()
{
    return 0;
}

/** @brief Default window hook. @return Zero. */
s32 FieldClass15AE70::func_slotc8()
{
    return 0;
}

/** @brief Default window hook. @return Zero. */
s32 FieldClass15AE70::func_slotcc()
{
    return 0;
}

/** @brief Default window hook. @return Zero. */
s32 FieldClass15AE70::func_slotd0()
{
    return 0;
}

/** @brief Default window hook. @return Zero. */
s32 FieldClass15AE70::func_slotd4()
{
    return 0;
}

/** @brief Default window hook. @return Zero. */
s32 FieldClass15AE70::func_slotd8()
{
    return 0;
}

/** @brief Default window hook. @return Zero. */
s32 FieldClass15AE70::func_slotdc()
{
    return 0;
}

/** @brief Default window hook; does nothing. */
void FieldClass15AE70::func_slote0()
{
}

/** @brief Default window hook; does nothing. */
void FieldClass15AE70::func_slote4()
{
}

/** @brief Read the second window control byte. @return Control value. */
u8 FieldClass15AE70::func_slote8()
{
    return unk0d;
}

/** @brief Store the second window control byte. @param value Control value. */
void FieldClass15AE70::func_slotec(u8 value)
{
    unk0d = value;
}

/** @brief Default window hook; does nothing. */
void FieldClass15AE70::func_slotf0()
{
}

/** @brief Return the focused window. @return Window that receives input. */
void* FieldClass153E30::func_00261150()
{
    return unk20;
}

/** @brief Send grid direction two and recolor Yes and No for the new cursor. */
void ItemDropConfirmWindow::func_slot74()
{
    if (!func_slot28())
    {
        if (grid->process_direction(2) != 1)
        {
            if (grid->unk114 != 0)
            {
                yes_text->set_color(ITEM_COLOR_NORMAL);
                no_text->set_color(ITEM_COLOR_SELECTED);
            }
            else
            {
                yes_text->set_color(ITEM_COLOR_SELECTED);
                no_text->set_color(ITEM_COLOR_NORMAL);
            }
        }
    }
}

/** @brief Send grid direction three and recolor Yes and No for the new cursor. */
void ItemDropConfirmWindow::func_slot70()
{
    if (!func_slot28())
    {
        if (grid->process_direction(3) != 1)
        {
            if (grid->unk114 != 0)
            {
                yes_text->set_color(ITEM_COLOR_NORMAL);
                no_text->set_color(ITEM_COLOR_SELECTED);
            }
            else
            {
                yes_text->set_color(ITEM_COLOR_SELECTED);
                no_text->set_color(ITEM_COLOR_NORMAL);
            }
        }
    }
}

/** @brief Give a window the focus. @param value Window that receives input. */
void FieldClass153E30::func_00263C70(void* value)
{
    unk20 = value;
}

/**
 * @brief Update gauge visibility and rebuild changed packets.
 * @param first Update enabled.
 * @param second Mark the packet changed.
 * @param third Allow drawing.
 */
void ItemHpMpGauge::func_0044B100(u32 first, u32 second, u32 third)
{
    if (queued_for_release != 0)
    {
        return;
    }

    unk63 = 0;

    if (first == 0)
    {
        return;
    }

    if (second != 0)
    {
        unkae = 1;
    }

    if (third == 0)
    {
        return;
    }

    if (unkae != 0)
    {
        ItemHpMpGaugeDrawer::unk00 = 0xFFFFFE - (ItemHpMpGaugeDrawer::unk04->unka0 << 4);
        func_002BC4F0(0, ItemHpMpGaugeDrawer::unk00, 128.0f);
    }

    unk63 = 1;
}

/**
 * @brief Initialize the gauge transform.
 * @param code Transform code.
 * @param first First transform flag.
 * @param source Transform source.
 * @param x Unused first coordinate.
 * @param y Unused second coordinate.
 * @param z Third coordinate.
 * @return One.
 */
s32 ItemHpMpGauge::initialize(s32 code, s32 first, void* source, float x, float y, float z)
{
    unk6c = 0x6006;
    LibClass171EC0::unk20.components[0] = 0.0f;
    LibClass171EC0::unk20.components[1] = 0.0f;
    LibClass171EC0::unk20.components[2] = 0.0f;
    LibClass171EC0::unk20.components[3] = 1.0f;
    set_codes_and_z(code, first, z, reinterpret_cast<u32>(source), 0);
    unkb4 = 0;
    unkb8 = 0;
    return 1;
}

/** @brief Complete DMA notification processing. @param value Unused notification value. */
void ItemHpMpGauge::func_003F4410(u32 value)
{
    func_4D00B0(this);
}

/** @brief Submit the drawing packet for DMA notification. */
void ItemHpMpGauge::func_003EEBE0()
{
    dma_pending = 1;

    if (unk08 != 0)
    {
        func_0011F770(unk08, this);
    }
}

/** @brief Release the drawing packet and base. */
inline ItemHpMpGaugeDrawer::~ItemHpMpGaugeDrawer()
{
}

/** @brief Release the drawing and transform bases. */
ItemHpMpGauge::~ItemHpMpGauge()
{
}

// The registers holding the packed vertex depth and bottom still come out swapped.
INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/citem", build_packet__19ItemHpMpGaugeDrawerFv);

/**
 * @brief Rebuild the drawing packet.
 * @param first Unused draw flag.
 * @param depth Unused drawing depth.
 * @param value Unused drawing value.
 */
void ItemHpMpGaugeDrawer::func_002BC4F0(u32 first, u32 depth, float value)
{
    ResidentPacket* packet = unk08;

    if (packet != 0)
    {
        packet->unk08 = packet->unk00 + 64;
        packet->unk0c = packet->unk08;
        packet->unk15 = 0;
        func_0011F140(packet, D_004ED330[0]);
        build_packet();
    }
}

/** @brief Return the loaded resource slot. @return Resource slot. */
u32 ItemController::get_resource_slot()
{
    return resource_slot;
}

/**
 * @brief Create the panel and the three prompts.
 * @param associated Resource source word.
 * @return One.
 */
s32 ItemControlHelpWindow::func_slotf4(u32 associated)
{
    LibClass178630* panel;
    this->width = 192.0f;
    this->height = 104.0f;
    FieldClass15AE70::func_slot14(associated, 0, 9, 0x578, 16.0f, 360.0f, 0.0f);
    panel = allocate_panel();
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, this->width, this->height, 88.0f);
    lib_container_attach_widget(this->unk10, panel);
    this->prompts[0] = allocate_text_widget();
    this->prompts[1] = allocate_text_widget();
    this->prompts[2] = allocate_text_widget();
    this->scale = 0.85f;
    this->unkc0 = 14.0f;
    this->row_spacing = 28.0f;
    this->text_x = 16.0f;
    this->text_y = this->height / 3.0f - this->row_spacing / 2.0f;
    this->unkd0 = 3.0f;
    this->prompts[0]->init_resource_rectangle(this->text_x, this->text_y, 0.0f, 0.0f, associated, ITEM_MSG_SORT_PROMPT, 0);
    this->prompts[1]->init_resource_rectangle(this->text_x, this->text_y + this->row_spacing, 0.0f, 0.0f, associated, ITEM_MSG_BACK_PROMPT, 0);
    this->prompts[2]->init_resource_rectangle(80.0f + this->text_x, this->text_y + this->row_spacing, 0.0f, 0.0f, associated, ITEM_MSG_SELECT_PROMPT, 0);
    scale_prompt(this, 0);
    scale_prompt(this, 1);
    scale_prompt(this, 2);
    lib_container_attach_widget(this->unk10, this->prompts[0]);
    lib_container_attach_widget(this->unk10, this->prompts[1]);
    lib_container_attach_widget(this->unk10, this->prompts[2]);
    this->prompts[0]->unk3f = 0;
    return 1;
}

/** @brief Pulse the comparison colors and compare each member's ATK, DEF and INT with the item equipped. */
void ItemEquipWindow::func_slot5c()
{
    ItemController* owner = static_cast<ItemController*>(D_001B643C->callbacks->state);

    pulse_level += pulse_step;

    if (pulse_level > 18)
    {
        pulse_step = -1;
    }

    if (pulse_level < 0)
    {
        pulse_step = 1;
    }

    for (s32 row = 0; row < 8; row++)
    {
        s16 index = row;
        s8 slot = party->slots[index];

        if (slot <= 0)
        {
            continue;
        }

        portraits[row]->unk3f = 1;
        stat_results[row][0]->unk3f = 1;
        stat_results[row][1]->unk3f = 1;
        stat_results[row][2]->unk3f = 1;
        ItemCreationAllocationRecord* allocation = owner->selected_allocation;

        if (allocation == 0)
        {
            set_display_brightness(portraits[row], 50.0f);
            lib_text_set_resource(stat_results[row][0], owner->get_resource_slot(), ITEM_MSG_STAT_NONE, 0);
            lib_text_set_resource(stat_results[row][1], owner->get_resource_slot(), ITEM_MSG_STAT_NONE, 0);
            lib_text_set_resource(stat_results[row][2], owner->get_resource_slot(), ITEM_MSG_STAT_NONE, 0);
            continue;
        }

        u16 equipment_mask = D_001B64F0[item_allocation_value(allocation)].equipment_mask;

        if (equipment_mask & (1 << (slot - 1)))
        {
            set_display_brightness(portraits[row], 128.0f);
        }
        else
        {
            set_display_brightness(portraits[row], 50.0f);
            lib_text_set_resource(stat_results[row][0], owner->get_resource_slot(), ITEM_MSG_STAT_NONE, 0);
            lib_text_set_resource(stat_results[row][1], owner->get_resource_slot(), ITEM_MSG_STAT_NONE, 0);
            lib_text_set_resource(stat_results[row][2], owner->get_resource_slot(), ITEM_MSG_STAT_NONE, 0);
            continue;
        }

        ItemCharacterStats* character = &reinterpret_cast<ItemCharacterStats*>(party->records)[index];
        ItemCharacterEquipment* equipment = &static_cast<ItemCharacterEquipment*>(party->unk04)[index];
        ItemCharacterStats character_copy = *character;
        ItemCharacterEquipment equipment_copy = *equipment;

        switch (static_cast<u8>(D_001B64F0[item_allocation_value(allocation)].category))
        {
        case ITEM_CATEGORY_WEAPONS:
            equipment_copy.set_equipment_id(0, lib_allocation_get_identifier(allocation));
            break;
        case ITEM_CATEGORY_ARMOR:
            equipment_copy.set_equipment_id(1, lib_allocation_get_identifier(allocation));
            break;
        case ITEM_CATEGORY_ACCESSORIES:
            equipment_copy.set_equipment_id(accessory_slot, lib_allocation_get_identifier(allocation));
            break;
        }

        lib_character_recalculate_stats(&character_copy, &equipment_copy, 0, -1);

        if (character_attack(character_copy) > character_attack(*character))
        {
            lib_text_set_resource(stat_results[row][0], owner->get_resource_slot(), ITEM_MSG_STAT_UP, 0);
            stat_results[row][0]->set_color(static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) |
                                          (static_cast<u64>(static_cast<u8>(static_cast<s32>(80.0f + 2.6666667f * pulse_level))) << 8) |
                                          (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) << 16));
        }
        else if (character_attack(character_copy) == character_attack(*character))
        {
            lib_text_set_resource(stat_results[row][0], owner->get_resource_slot(), ITEM_MSG_STAT_SAME, 0);
        }
        else
        {
            lib_text_set_resource(stat_results[row][0], owner->get_resource_slot(), ITEM_MSG_STAT_DOWN, 0);
            stat_results[row][0]->set_color(static_cast<u64>(static_cast<u8>(static_cast<s32>(80.0f + 2.6666667f * pulse_level))) |
                                          (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) << 8) |
                                          (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) << 16));
        }

        if (character_defense(character_copy) > character_defense(*character))
        {
            lib_text_set_resource(stat_results[row][1], owner->get_resource_slot(), ITEM_MSG_STAT_UP, 0);
            stat_results[row][1]->set_color(static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) |
                                          (static_cast<u64>(static_cast<u8>(static_cast<s32>(80.0f + 2.6666667f * pulse_level))) << 8) |
                                          (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) << 16));
        }
        else if (character_defense(character_copy) == character_defense(*character))
        {
            lib_text_set_resource(stat_results[row][1], owner->get_resource_slot(), ITEM_MSG_STAT_SAME, 0);
        }
        else
        {
            lib_text_set_resource(stat_results[row][1], owner->get_resource_slot(), ITEM_MSG_STAT_DOWN, 0);
            stat_results[row][1]->set_color(static_cast<u64>(static_cast<u8>(static_cast<s32>(80.0f + 2.6666667f * pulse_level))) |
                                          (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) << 8) |
                                          (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) << 16));
        }

        if (character_intelligence(character_copy) > character_intelligence(*character))
        {
            lib_text_set_resource(stat_results[row][2], owner->get_resource_slot(), ITEM_MSG_STAT_UP, 0);
            stat_results[row][2]->set_color(static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) |
                                          (static_cast<u64>(static_cast<u8>(static_cast<s32>(80.0f + 2.6666667f * pulse_level))) << 8) |
                                          (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) << 16));
        }
        else if (character_intelligence(character_copy) == character_intelligence(*character))
        {
            lib_text_set_resource(stat_results[row][2], owner->get_resource_slot(), ITEM_MSG_STAT_SAME, 0);
        }
        else
        {
            lib_text_set_resource(stat_results[row][2], owner->get_resource_slot(), ITEM_MSG_STAT_DOWN, 0);
            stat_results[row][2]->set_color(static_cast<u64>(static_cast<u8>(static_cast<s32>(80.0f + 2.6666667f * pulse_level))) |
                                          (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) << 8) |
                                          (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) << 16));
        }
    }
}

/**
 * @brief Switch between the two accessory slots for an accessory.
 * @return One when the selected item is an accessory, otherwise zero.
 */
s32 ItemEquipWindow::func_slotc0()
{
    ItemController* controller = static_cast<ItemController*>(D_001B643C->callbacks->state);
    ItemCreationAllocationRecord* allocation = controller->selected_allocation;

    if (allocation != 0)
    {
        u16 identifier = allocation->definition_index();

        if ((u8)D_001B64F0[identifier].category == ITEM_CATEGORY_ACCESSORIES)
        {
            accessory_slot = accessory_slot == 2 ? 3 : 2;

            if (accessory_slot == 2)
            {
                set_item_window_message(controller->help_window, ITEM_MSG_EQUIP_ACCESSORY_1_HELP);
            }

            if (accessory_slot == 3)
            {
                set_item_window_message(controller->help_window, ITEM_MSG_EQUIP_ACCESSORY_2_HELP);
            }

            return 1;
        }
    }

    return 0;
}

/** @brief Same as func_slotc0. @return Its result. */
s32 ItemEquipWindow::func_slotc4()
{
    return this->func_slotc0();
}

/** @brief Move the selector back one member, wrapping to the eighth. */
void ItemEquipWindow::func_slot70()
{
    ItemCoordinateSelector* selector = this->selector;
    s32 index;

    if (selector_is_idle(selector) != 0)
    {
        return;
    }

    index = selector->selected - 1;

    if (index < 0)
    {
        index = 7;
    }

    func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(selector), index, 0);
}

/** @brief Move the selector forward one member, wrapping after the eighth. */
void ItemEquipWindow::func_slot74()
{
    ItemCoordinateSelector* selector = this->selector;
    s32 index;

    if (selector_is_idle(selector) != 0)
    {
        return;
    }

    index = selector->selected + 1;

    if (index >= 8)
    {
        index = 0;
    }

    func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(selector), index, 0);
}

/** @brief Move the selector from the front row to the back row. */
void ItemEquipWindow::func_slot6c()
{
    ItemCoordinateSelector* selector = this->selector;
    s32 index;

    if (selector_is_idle(selector) != 0)
    {
        return;
    }

    switch (selector->selected)
    {
    case 0:
        index = 3;
        break;
    case 1:
        index = 5;
        break;
    case 2:
        index = 6;
        break;
    default:
        return;
    }

    func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(selector), index, 0);
}

/** @brief Move the selector from the back row to the front row. */
void ItemEquipWindow::func_slot68()
{
    ItemCoordinateSelector* selector = this->selector;
    s32 index;

    if (selector_is_idle(selector) != 0)
    {
        return;
    }

    switch (selector->selected)
    {
    case 3:
        index = 0;
        break;
    case 4:
        index = 1;
        break;
    case 5:
        index = 1;
        break;
    case 6:
        index = 2;
        break;
    case 7:
        index = 2;
        break;
    default:
        return;
    }

    func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(selector), index, 0);
}

/** @brief Close the window and return to the instance list, or to the type list when none remain. @return Two. */
u8 ItemEquipWindow::func_slotb4()
{
    ItemCreationAllocationRecord* records[100];
    ItemController* controller = static_cast<ItemController*>(D_001B643C->callbacks->state);

    if (lib_collect_unequipped_allocations(D_001B64F8, records, controller->selected_item_type) == 0)
    {
        controller->remove_child(this);
        controller->remove_child(this->func_slot44());
        FieldClass15AE70* associated = (FieldClass15AE70*)this->func_slot44();
        ItemTypeListWindow* list = static_cast<ItemTypeListWindow*>(associated->func_slot44());
        list->rebuild_list(0, -1);
        list->func_slot10c(1, 1);
        D_001B643C->callbacks->state->func_00263C70(list);
    }
    else
    {
        controller->remove_child(this);
        ItemInstanceListWindow* associated = static_cast<ItemInstanceListWindow*>(this->func_slot44());
        associated->detail_container->unkab = 1;
        controller->func_00263C70(associated);
    }

    return 2;
}

/**
 * @brief Equip the selected item on the selected member and recalculate their statistics.
 * @return Three when nobody is selected or the item can't be equipped, otherwise zero.
 */
u8 ItemEquipWindow::func_slotb0()
{
    ItemController* owner = static_cast<ItemController*>(D_001B643C->callbacks->state);
    s8 slot;
    ItemCharacterStats* character;
    ItemCharacterEquipment* equipment;
    ItemCreationAllocationRecord* allocation = owner->selected_allocation;
    FieldRecordSelection* party = this->party;
    s16 index = selector->selected;
    slot = party->slots[index];

    if (allocation != 0 && slot > 0)
    {
        character = &reinterpret_cast<ItemCharacterStats*>(party->records)[index];
        equipment = &static_cast<ItemCharacterEquipment*>(party->unk04)[index];

        if (allocation == 0)
        {
            return 3;
        }

        u8 equipped_owner = reinterpret_cast<ItemAllocationOwnerView*>(allocation)->equipped_owner;

        if (equipped_owner > 0)
        {
            return 3;
        }

        u16 equipment_mask = D_001B64F0[allocation->definition_index()].equipment_mask;

        if ((equipment_mask & (1 << (slot - 1))) == 0)
        {
            return 3;
        }

        switch (static_cast<u8>(D_001B64F0[allocation->definition_index()].category))
        {
        case ITEM_CATEGORY_WEAPONS:
            lib_allocation_set_equipped_owner(D_001B64F8, equipment->get_equipment_id(0), 0);
            lib_allocation_set_equipped_owner(D_001B64F8, lib_allocation_get_identifier(allocation), slot);
            equipment->set_equipment_id(0, lib_allocation_get_identifier(allocation));
            break;
        case ITEM_CATEGORY_ARMOR:
            lib_allocation_set_equipped_owner(D_001B64F8, equipment->get_equipment_id(1), 0);
            lib_allocation_set_equipped_owner(D_001B64F8, lib_allocation_get_identifier(allocation), slot);
            equipment->set_equipment_id(1, lib_allocation_get_identifier(allocation));
            break;
        case ITEM_CATEGORY_ACCESSORIES:
            lib_allocation_set_equipped_owner(D_001B64F8, equipment->get_equipment_id(accessory_slot), 0);
            lib_allocation_set_equipped_owner(D_001B64F8, lib_allocation_get_identifier(allocation), slot);
            equipment->set_equipment_id(accessory_slot, lib_allocation_get_identifier(allocation));
            break;
        }

        lib_character_recalculate_stats(character, equipment, 0, -1);
        resident_allocate_request(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
    }
    else
    {
        return 3;
    }

    static_cast<ItemInstanceListWindow*>(func_slot44())->refresh_instances(0);
    return 0;
}

/** @brief Restore the category help line and destroy the window. */
ItemEquipWindow::~ItemEquipWindow()
{
    if (message_changed != 0)
    {
        ItemController* controller = static_cast<ItemController*>(D_001B643C->callbacks->state);
        set_item_window_message(controller->help_window, controller->selected_category + ITEM_MSG_CATEGORY_HELP_BASE);
    }
}

/**
 * @brief Create the party panels with names, portraits and comparison labels, then show the equip help line.
 * @param associated Resource source word.
 * @return Zero when the selector couldn't be allocated, otherwise one.
 */
s32 ItemEquipWindow::func_slotf4(u32 associated)
{
    s32 source = associated;
    ItemController* owner = static_cast<ItemController*>(D_001B643C->callbacks->state);
    this->party = owner->selected_records();
    this->x = 12.0f;
    this->y = 216.0f;
    FieldClass15AE70::func_slot10(source, this->x, this->y, 15);
    this->selector = new (0) ItemCoordinateSelector;

    if (this->selector == 0)
    {
        return 0;
    }

    lib_moving_widget_init_position(this->selector, 0.0f, 0.0f);
    lib_container_attach_widget(this->unk10, this->selector);
    this->row_height = 128.0f;

    for (s32 row = 0; row < 8; row++)
    {
        float panel_y;
        float text_x;
        float text_y;
        float panel_x;
        float column_width;
        s32 column;

        if (row < 3)
        {
            column_width = 196.0f;
            panel_y = 0.0f;
            column = row;
        }
        else
        {
            panel_y = this->row_height;
            column = row - 3;
            column_width = 117.0f;
        }

        LibClass178630* panel = new (0) LibClass178630;
        panel_x = 8.0f + column_width * (float)column;
        lib_panel_init_rectangle(panel, 1, panel_x, panel_y, 3.0f + column_width, 2.0f + this->row_height, 88.0f);
        lib_container_attach_widget(this->unk10, panel);

        if (row < 3)
        {
            text_x = 85.0f + panel_x;
            text_y = 40.0f + panel_y;
        }
        else
        {
            text_x = 14.0f + panel_x;
            text_y = 66.0f + panel_y;
        }

        s16 index = row;
        s8 slot = this->party->slots[index];

        if (slot > 0)
        {
            if (row < 3)
            {
                LibObject175140* name = new (0) LibObject175140;
                name->func_00467AD0(16.0f + panel_x, 10.0f + panel_y, 0.0f, 0.0f,
                    static_cast<ItemCharacterEquipment*>(this->party->unk04)[index].character_name, 0);
                lib_container_attach_widget(this->unk10, name);
                name->set_scale(0.8f, 0.8f);
            }

            this->portraits[row] = new (0) ItemCreationOptionResourceDisplay;
            u8 character = slot;
            void* resource = field_get_aligned_allocation(D_001B643C->resources, character);
            FieldResourceRecord* record = field_find_resource_record(D_001B643C->resources, 4);
            this->portraits[row]->unkcc = resource;
            this->portraits[row]->unkd0 = character;

            if (row < 3)
            {
                this->portraits[row]->func_002D6440(14.0f + panel_x, 48.0f + panel_y, record);
                ItemCreationOptionResourceDisplay* portrait = this->portraits[row];
                portrait->unk50.unk34 = 0.8f;
                portrait->unk50.unk30 = 0.8f;
                portrait->unk3c = 1;
            }
            else
            {
                this->portraits[row]->func_002D6440(14.0f + panel_x, 12.0f + panel_y, record);
                ItemCreationOptionResourceDisplay* portrait = this->portraits[row];
                portrait->unk50.unk34 = 0.65f;
                portrait->unk50.unk30 = 0.65f;
                portrait->unk3c = 1;
            }

            this->portraits[row]->unk34 = 3;
            this->portraits[row]->unk3f = 0;
            lib_container_attach_widget(this->unk10, this->portraits[row]);
            LibObject178750* atk_label = new (0) LibObject178750;
            LibObject178750* def_label = new (0) LibObject178750;
            LibObject178750* int_label = new (0) LibObject178750;
            this->stat_results[row][0] = new (0) LibObject178750;
            this->stat_results[row][1] = new (0) LibObject178750;
            this->stat_results[row][2] = new (0) LibObject178750;

            if (row < 3)
            {
                atk_label->init_resource_rectangle(text_x, text_y, 0.0f, 0.0f, source, ITEM_MSG_ATK, 0);
                def_label->init_resource_rectangle(text_x, 26.0f + text_y, 0.0f, 0.0f, source, ITEM_MSG_DEF, 0);
                int_label->init_resource_rectangle(text_x, 52.0f + text_y, 0.0f, 0.0f, source, ITEM_MSG_INT, 0);
                atk_label->set_scale(0.8f, 0.8f);
                def_label->set_scale(0.8f, 0.8f);
                int_label->set_scale(0.8f, 0.8f);
                this->stat_results[row][0]->init_resource_rectangle(45.0f + text_x, 1.0f + (text_y - 3.0f), 0.0f, 0.0f, source, ITEM_MSG_STAT_UP, 0);
                this->stat_results[row][1]->init_resource_rectangle(45.0f + text_x, 2.0f + ((26.0f + text_y) - 3.0f), 0.0f, 0.0f, source, ITEM_MSG_STAT_DOWN, 0);
                this->stat_results[row][2]->init_resource_rectangle(45.0f + text_x, 4.0f + ((50.0f + text_y) - 3.0f), 0.0f, 0.0f, source, ITEM_MSG_STAT_SAME, 0);
            }
            else
            {
                atk_label->init_resource_rectangle(text_x, text_y, 0.0f, 0.0f, source, ITEM_MSG_ATK, 0);
                def_label->init_resource_rectangle(text_x, 19.0f + text_y, 0.0f, 0.0f, source, ITEM_MSG_DEF, 0);
                int_label->init_resource_rectangle(text_x, 38.0f + text_y, 0.0f, 0.0f, source, ITEM_MSG_INT, 0);
                atk_label->set_scale(0.68f, 0.68f);
                def_label->set_scale(0.68f, 0.68f);
                int_label->set_scale(0.68f, 0.68f);
                this->stat_results[row][0]->init_resource_rectangle(41.0f + text_x, text_y - 3.0f, 0.0f, 0.0f, source, ITEM_MSG_STAT_UP, 0);
                this->stat_results[row][1]->init_resource_rectangle(41.0f + text_x, (19.0f + text_y) - 3.0f, 0.0f, 0.0f, source, ITEM_MSG_STAT_DOWN, 0);
                this->stat_results[row][2]->init_resource_rectangle(41.0f + text_x, (38.0f + text_y) - 3.0f, 0.0f, 0.0f, source, ITEM_MSG_STAT_SAME, 0);
                this->stat_results[row][0]->set_scale(0.9f, 0.9f);
                this->stat_results[row][1]->set_scale(0.9f, 0.9f);
                this->stat_results[row][2]->set_scale(0.9f, 0.9f);
            }

            this->stat_results[row][0]->unk3f = 0;
            this->stat_results[row][1]->unk3f = 0;
            this->stat_results[row][2]->unk3f = 0;
            lib_container_attach_widget(this->unk10, atk_label);
            lib_container_attach_widget(this->unk10, def_label);
            lib_container_attach_widget(this->unk10, int_label);
            lib_container_attach_widget(this->unk10, this->stat_results[row][0]);
            lib_container_attach_widget(this->unk10, this->stat_results[row][1]);
            lib_container_attach_widget(this->unk10, this->stat_results[row][2]);
        }
        else
        {
            LibObject178750* empty = new (0) LibObject178750;
            empty->init_resource_rectangle(16.0f + panel_x, 10.0f + panel_y, 0.0f, 0.0f, source, ITEM_MSG_EMPTY, 0);
            set_widget_rectangle(empty, panel_x, (panel_y + this->row_height / 2.0f) - 9.6f, column_width, 24.0f);
            empty->set_mode(1);

            if (row < 3)
            {
                empty->set_scale(0.8f, 0.8f);
            }
            else
            {
                empty->set_scale(0.8f * 0.8f, 0.8f * 0.8f);
            }

            lib_container_attach_widget(this->unk10, empty);
        }

        if (row < 3)
        {
            append_selector_position(this->selector, 14.0f + panel_x, 88.0f + panel_y);
        }
        else
        {
            append_selector_position(this->selector, 14.0f + panel_x, 47.0f + panel_y);
        }
    }

    func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(this->selector), 0, 1);
    this->selector->unk3f = 0;
    this->unk10->LibClass174610::unkab = 0;
    ItemCreationAllocationRecord* allocation = owner->selected_allocation;

    if (allocation != 0)
    {
        if (static_cast<u8>(D_001B64F0[item_allocation_value(allocation)].category) == ITEM_CATEGORY_WEAPONS)
        {
            set_item_window_message(owner->help_window, ITEM_MSG_EQUIP_WEAPON_HELP);
            this->message_changed = 1;
        }

        if (static_cast<u8>(D_001B64F0[item_allocation_value(allocation)].category) == ITEM_CATEGORY_ARMOR)
        {
            set_item_window_message(owner->help_window, ITEM_MSG_EQUIP_ARMOR_HELP);
            this->message_changed = 1;
        }

        if (static_cast<u8>(D_001B64F0[item_allocation_value(allocation)].category) == ITEM_CATEGORY_ACCESSORIES)
        {
            set_item_window_message(owner->help_window, ITEM_MSG_EQUIP_ACCESSORY_1_HELP);
            this->message_changed = 1;
        }
    }

    return 1;
}

/** @brief Destroy the resource display base. */
ItemCreationClass175110::~ItemCreationClass175110()
{
}

/** @brief Destroy the movement storage and intrusive widget base. */
inline ItemCreationClass175030::~ItemCreationClass175030()
{
}

/** @brief Return the party selection. @return Party selection. */
FieldRecordSelection* ItemController::selected_records()
{
    return party;
}

/** @brief Update the gauges and refresh each member's HP, MP, status badges and name color. */
void ItemUseWindow::func_slot5c()
{
    for (ItemListNode* node = gauges.head->next; node != 0; node = node->next)
    {
        static_cast<ItemHpMpGauge*>(node->value)->func_0044B100(1, 1, 1);
    }

    for (s32 row = 0; row < 8; ++row)
    {
        s16 index = row;

        if (party->slots[index] > 0)
        {
            ItemCharacterStats* character = &reinterpret_cast<ItemCharacterStats*>(party->records)[index];
            lib_character_recalculate_stats(character, &static_cast<ItemCharacterEquipment*>(party->unk04)[index], 0, -1);
            u32 hp = character_hp(character);
            LibObject174F20* hp_display = hp_values[row];
            hp_display->numeric_value = hp;
            hp_display->unk3c = 1;
            u32 mp = character_mp(character);
            LibObject174F20* mp_display = mp_values[row];
            mp_display->numeric_value = mp;
            mp_display->unk3c = 1;

            if (row < 3)
            {
                u32 max_hp = character_max_hp(character);
                LibObject174F20* max_hp_display = max_hp_values[row];
                max_hp_display->numeric_value = max_hp;
                max_hp_display->unk3c = 1;
                u32 max_mp = character_max_mp(character);
                LibObject174F20* max_mp_display = max_mp_values[row];
                max_mp_display->numeric_value = max_mp;
                max_mp_display->unk3c = 1;
            }

            status_badges[row][0]->unk3f = character_flags(character) & 2;
            status_badges[row][1]->unk3f = character_flags(character) & 8;
            status_badges[row][2]->unk3f = character_flags(character) & 4;

            if (character_flags(character) & 5)
            {
                portraits[row]->unk3f = 0;
                status_badges[row][3]->unk3f = 1;

                if (row < 3)
                {
                    LibObject175140* name = names[row];
                    name->unk94 = ITEM_COLOR_DISABLED;
                    name->unk3c = 1;
                }
            }
            else
            {
                portraits[row]->unk3f = 1;
                status_badges[row][3]->unk3f = 0;

                if (row < 3)
                {
                    LibObject175140* name = names[row];
                    name->unk94 = ITEM_COLOR_NORMAL;
                    name->unk3c = 1;
                }
            }
        }
    }
}

/** @brief Move the selector back one member, wrapping to the eighth. */
void ItemUseWindow::func_slot70()
{
    ItemCoordinateSelector* selector = this->selector;
    s32 index;

    if (selector_is_idle(selector) != 0)
    {
        return;
    }

    index = selector->selected - 1;

    if (index < 0)
    {
        index = 7;
    }

    func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(selector), index, 0);
}

/** @brief Move the selector forward one member, wrapping after the eighth. */
void ItemUseWindow::func_slot74()
{
    ItemCoordinateSelector* selector = this->selector;
    s32 index;

    if (selector_is_idle(selector) != 0)
    {
        return;
    }

    index = selector->selected + 1;

    if (index >= 8)
    {
        index = 0;
    }

    func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(selector), index, 0);
}

/** @brief Move the selector from the front row to the back row. */
void ItemUseWindow::func_slot6c()
{
    ItemCoordinateSelector* selector = this->selector;
    s32 index;

    if (selector_is_idle(selector) != 0)
    {
        return;
    }

    switch (selector->selected)
    {
    case 0:
        index = 3;
        break;
    case 1:
        index = 5;
        break;
    case 2:
        index = 6;
        break;
    default:
        return;
    }

    func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(selector), index, 0);
}

/** @brief Move the selector from the back row to the front row. */
void ItemUseWindow::func_slot68()
{
    ItemCoordinateSelector* selector = this->selector;
    s32 index;

    if (selector_is_idle(selector) != 0)
    {
        return;
    }

    switch (selector->selected)
    {
    case 3:
        index = 0;
        break;
    case 4:
        index = 1;
        break;
    case 5:
        index = 1;
        break;
    case 6:
        index = 2;
        break;
    case 7:
        index = 2;
        break;
    default:
        return;
    }

    func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(selector), index, 0);
}

/** @brief Close the window and return to the instance list, or to the type list when none remain. @return Two. */
u8 ItemUseWindow::func_slotb4()
{
    ItemCreationAllocationRecord* records[100];
    ItemController* controller = static_cast<ItemController*>(D_001B643C->callbacks->state);

    if (lib_collect_unequipped_allocations(D_001B64F8, records, controller->selected_item_type) == 0)
    {
        controller->remove_child(this);
        controller->remove_child(func_slot44());
        FieldClass15AE70* associated = static_cast<FieldClass15AE70*>(func_slot44());
        ItemTypeListWindow* list = static_cast<ItemTypeListWindow*>(associated->func_slot44());
        list->rebuild_list(0, -1);
        list->func_slot10c(1, 1);
        D_001B643C->callbacks->state->func_00263C70(list);
    }
    else
    {
        controller->remove_child(this);
        ItemInstanceListWindow* associated = static_cast<ItemInstanceListWindow*>(func_slot44());
        associated->detail_container->unkab = 1;
        controller->func_00263C70(associated);
    }

    return 2;
}

/** @brief Use the selected item on the selected member. @return Three when it can't be used, otherwise zero. */
u8 ItemUseWindow::func_slotb0()
{
    ItemController* owner = static_cast<ItemController*>(D_001B643C->callbacks->state);
    s32 selected = selector->selected;
    s8 slot = party->slots[static_cast<s16>(selected)];

    if (owner->selected_allocation != 0 && slot > 0)
    {
        switch (func_002E19D0(owner->selected_allocation, selected))
        {
        case -1:
        case 0:
            return 3;
        case 1:
            func_0040C9F0(D_001B64F8, lib_allocation_get_identifier(owner->selected_allocation));
            resident_allocate_request(D_001B65F8, 0x1B4, 0, 0, 0x7F, 0x40, 0);
            break;
        case 2:
            resident_allocate_request(D_001B65F8, 0x1B4, 0, 0, 0x7F, 0x40, 0);
            break;
        }
    }
    else
    {
        return 3;
    }

    static_cast<ItemInstanceListWindow*>(func_slot44())->refresh_instances(0);
    return 0;
}

/**
 * @brief Create the party panels with names, HP and MP, portraits, status badges, gauges and selector positions.
 * @param associated Resource source word.
 * @return Zero when the selector couldn't be allocated, otherwise one.
 */
s32 ItemUseWindow::func_slotf4(u32 associated)
{
    s32 source = associated;
    ItemController* owner = static_cast<ItemController*>(D_001B643C->callbacks->state);
    this->party = owner->selected_records();
    this->x = 12.0f;
    this->y = 216.0f;
    FieldClass15AE70::func_slot10(source, this->x, this->y, 15);
    this->selector = new (0) ItemCoordinateSelector;

    if (this->selector == 0)
    {
        return 0;
    }

    lib_moving_widget_init_position(this->selector, 0.0f, 0.0f);
    lib_container_attach_widget(this->unk10, this->selector);
    this->row_height = 128.0f;

    for (s32 row = 0; row < 8; row++)
    {
        float portrait_x;
        float panel_y;
        float badge_x;
        float badge_y;
        float value_x;
        float hp_row_y;
        float mp_row_y;
        float panel_x;
        float hp_y;
        float value_height;
        float column_width;
        float value_width;
        s32 column;

        if (row < 3)
        {
            column_width = 196.0f;
            panel_y = 0.0f;
            column = row;
        }
        else
        {
            panel_y = this->row_height;
            column = row - 3;
            column_width = 117.0f;
        }

        LibClass178630* panel = new (0) LibClass178630;
        panel_x = 8.0f + column_width * (float)column;
        lib_panel_init_rectangle(panel, 1, panel_x, panel_y, 3.0f + column_width, 2.0f + this->row_height, 88.0f);
        lib_container_attach_widget(this->unk10, panel);
        hp_row_y = 50.0f + panel_y;
        mp_row_y = 78.0f + panel_y;

        if (row < 3)
        {
            value_x = 68.0f + panel_x;
            badge_x = 98.0f + panel_x;
            badge_y = 36.0f + panel_y;
        }
        else
        {
            value_x = 8.0f + panel_x;
            badge_x = 65.0f + panel_x;
            badge_y = 12.0f + panel_y;
        }

        s16 index = row;
        s8 slot = this->party->slots[index];

        if (slot > 0)
        {
            if (row < 3)
            {
                this->names[row] = new (0) LibObject175140;
                this->names[row]->func_00467AD0(16.0f + panel_x, 10.0f + panel_y, 0.0f, 0.0f,
                    slot > 0 ? static_cast<ItemCharacterEquipment*>(this->party->unk04)[index].character_name : g_item_empty_name, 0);
                lib_container_attach_widget(this->unk10, this->names[row]);
                this->names[row]->set_scale(0.8f, 0.8f);

                if (reinterpret_cast<ItemCharacterStats*>(this->party->records)[index].get_flags() & 5)
                {
                    this->names[row]->set_color(ITEM_COLOR_DISABLED);
                }
                else
                {
                    this->names[row]->set_color(ITEM_COLOR_NORMAL);
                }
            }

            this->hp_values[row] = new (0) LibObject174F20;

            if (row < 3)
            {
                // TODO: I couldn't get a separate offset variable to match, so the column width doubles as the HP and MP row offset.
                column_width = 16.0f;
                hp_y = column_width + hp_row_y;
                value_height = 19.2f;
                value_width = 56.0f;
                lib_numeric_widget_init_rectangle(this->hp_values[row], 0, 1, 0, 3.0f + value_x, hp_y, value_width, value_height);
            }
            else
            {
                column_width = 16.0f;
                hp_y = column_width + hp_row_y;
                value_height = 19.2f;
                value_width = 56.0f;
                lib_numeric_widget_init_rectangle(this->hp_values[row], 0, 1, 0, 40.0f + value_x, hp_y, value_width, value_height);
            }

            this->hp_values[row]->set_scale(0.8f, 0.8f);
            set_numeric_value(this->hp_values[row], character_hp(&reinterpret_cast<ItemCharacterStats*>(this->party->records)[index]));
            lib_container_attach_widget(this->unk10, this->hp_values[row]);

            if (row < 3)
            {
                LibObject178750* separator = new (0) LibObject178750;
                separator->init_resource_rectangle(60.0f + value_x, hp_y, 0.0f, 0.0f, source, ITEM_MSG_HP_MP_SEPARATOR, 0);
                separator->set_scale(0.8f, 0.8f);
                lib_container_attach_widget(this->unk10, separator);
                this->max_hp_values[row] = new (0) LibObject174F20;
                lib_numeric_widget_init_rectangle(this->max_hp_values[row], 0, 1, 0, 61.0f + value_x, hp_y, value_width, value_height);
                this->max_hp_values[row]->set_scale(0.8f, 0.8f);
                set_numeric_value(this->max_hp_values[row], character_max_hp(&reinterpret_cast<ItemCharacterStats*>(this->party->records)[index]));
                lib_container_attach_widget(this->unk10, this->max_hp_values[row]);
            }

            this->mp_values[row] = new (0) LibObject174F20;

            if (row < 3)
            {
                column_width += mp_row_y;
                lib_numeric_widget_init_rectangle(this->mp_values[row], 1, 0, 0, 3.0f + value_x, column_width, value_width, 0.0f);
            }
            else
            {
                column_width += mp_row_y;
                lib_numeric_widget_init_rectangle(this->mp_values[row], 1, 0, 0, 40.0f + value_x, column_width, value_width, 0.0f);
            }

            this->mp_values[row]->set_scale(0.8f, 0.8f);
            set_numeric_value(this->mp_values[row], character_mp(&reinterpret_cast<ItemCharacterStats*>(this->party->records)[index]));
            lib_container_attach_widget(this->unk10, this->mp_values[row]);

            if (row < 3)
            {
                LibObject178750* separator = new (0) LibObject178750;
                separator->init_resource_rectangle(60.0f + value_x, column_width, 0.0f, 0.0f, source, ITEM_MSG_HP_MP_SEPARATOR, 0);
                separator->set_scale(0.8f, 0.8f);
                lib_container_attach_widget(this->unk10, separator);
                this->max_mp_values[row] = new (0) LibObject174F20;
                lib_numeric_widget_init_rectangle(this->max_mp_values[row], 1, 0, 0, 61.0f + value_x, column_width, value_width, 0.0f);
                this->max_mp_values[row]->set_scale(0.8f, 0.8f);
                set_numeric_value(this->max_mp_values[row], character_max_mp(&reinterpret_cast<ItemCharacterStats*>(this->party->records)[index]));
                lib_container_attach_widget(this->unk10, this->max_mp_values[row]);
            }

            this->portraits[row] = new (0) ItemCreationOptionResourceDisplay;
            u8 character = slot;
            void* resource = field_get_aligned_allocation(D_001B643C->resources, character);
            FieldResourceRecord* record = field_find_resource_record(D_001B643C->resources, 4);
            this->portraits[row]->unkcc = resource;
            this->portraits[row]->unkd0 = character;

            if (row < 3)
            {
                portrait_x = 14.0f + panel_x;
                this->portraits[row]->func_002D6440(portrait_x, 48.0f + panel_y, record);
                ItemCreationOptionResourceDisplay* portrait = this->portraits[row];
                portrait->unk50.unk34 = 0.8f;
                portrait->unk50.unk30 = 0.8f;
                portrait->unk3c = 1;
            }
            else
            {
                portrait_x = 14.0f + panel_x;
                this->portraits[row]->func_002D6440(portrait_x, 12.0f + panel_y, record);
                ItemCreationOptionResourceDisplay* portrait = this->portraits[row];
                portrait->unk50.unk34 = 0.65f;
                portrait->unk50.unk30 = 0.65f;
                portrait->unk3c = 1;
            }

            lib_container_attach_widget(this->unk10, this->portraits[row]);
            resource = field_get_aligned_allocation(D_001B643C->resources, 0);
            record = field_find_resource_record(D_001B643C->resources, 40);
            this->status_badges[row][0] = new (0) ItemCreationOptionResourceDisplay;
            this->status_badges[row][0]->unkcc = resource;
            this->status_badges[row][0]->unkd0 = 0;
            ItemCreationOptionResourceDisplay* badge = this->status_badges[row][0];
            badge->unk50.unk34 = 0.8f;
            badge->unk50.unk30 = 0.8f;
            badge->unk3c = 1;
            this->status_badges[row][0]->func_002D6440(badge_x, badge_y, record);
            this->status_badges[row][0]->unk3f = 0;
            lib_container_attach_widget(this->unk10, this->status_badges[row][0]);
            record = field_find_resource_record(D_001B643C->resources, 39);
            this->status_badges[row][1] = new (0) ItemCreationOptionResourceDisplay;
            this->status_badges[row][1]->unkcc = resource;
            this->status_badges[row][1]->unkd0 = 0;
            badge = this->status_badges[row][1];
            badge->unk50.unk34 = 0.8f;
            badge->unk50.unk30 = 0.8f;
            badge->unk3c = 1;

            if (row < 3)
            {
                this->status_badges[row][1]->func_002D6440(35.0f + badge_x, badge_y, record);
            }
            else
            {
                this->status_badges[row][1]->func_002D6440(25.0f + badge_x, badge_y, record);
            }

            this->status_badges[row][1]->unk3f = 0;
            lib_container_attach_widget(this->unk10, this->status_badges[row][1]);
            record = field_find_resource_record(D_001B643C->resources, 38);
            this->status_badges[row][2] = new (0) ItemCreationOptionResourceDisplay;
            this->status_badges[row][2]->unkcc = resource;
            this->status_badges[row][2]->unkd0 = 0;
            badge = this->status_badges[row][2];
            badge->unk50.unk34 = 0.8f;
            badge->unk50.unk30 = 0.8f;
            badge->unk3c = 1;

            if (row < 3)
            {
                this->status_badges[row][2]->func_002D6440(70.0f + badge_x, badge_y, record);
            }
            else
            {
                this->status_badges[row][2]->func_002D6440(25.0f + badge_x, 30.0f + badge_y, record);
            }

            this->status_badges[row][2]->unk3f = 0;
            lib_container_attach_widget(this->unk10, this->status_badges[row][2]);
            resource = field_get_aligned_allocation(D_001B643C->resources, (u8)(slot + 0x30));
            record = field_find_resource_record(D_001B643C->resources, 4);
            this->status_badges[row][3] = new (0) ItemCreationOptionResourceDisplay;
            this->status_badges[row][3]->unkcc = resource;
            this->status_badges[row][3]->unkd0 = 0;

            if (row < 3)
            {
                this->status_badges[row][3]->func_002D6440(portrait_x, 48.0f + panel_y, record);
                badge = this->status_badges[row][3];
                badge->unk50.unk34 = 0.8f;
                badge->unk50.unk30 = 0.8f;
                badge->unk3c = 1;
            }
            else
            {
                this->status_badges[row][3]->func_002D6440(portrait_x, 12.0f + panel_y, record);
                badge = this->status_badges[row][3];
                badge->unk50.unk34 = 0.65f;
                badge->unk50.unk30 = 0.65f;
                badge->unk3c = 1;
            }

            this->status_badges[row][3]->unk3f = reinterpret_cast<ItemCharacterStats*>(this->party->records)[index].get_flags() & 5;
            lib_container_attach_widget(this->unk10, this->status_badges[row][3]);
            ItemHpMpGauge* gauge = new (0) ItemHpMpGauge;
            gauge->character_id = slot;
            gauge->characters = D_001B643C->characters;
            LibCameraContext* context = D_001B6650;
            gauge->FieldClass159A70::unk1c = 0x800 - context->viewport_width / 2;
            gauge->FieldClass159A70::unk20 = 0x800 - context->viewport_height / 2;
            gauge->FieldClass159A70::unk24 = 0x800 + context->viewport_width / 2;
            gauge->FieldClass159A70::unk28 = 0x800 + context->viewport_height / 2;
            gauge->initialize(1, 0, 0, 0.0f, 0.0f, 0.0f);

            if (row < 3)
            {
                gauge->origin.x = 22.0f + value_x;
                gauge->origin.y = 32.0f + hp_row_y;
                gauge->row_spacing = 30.0f;
            }
            else
            {
                gauge->origin.x = 20.0f + value_x;
                gauge->origin.y = 32.0f + hp_row_y;
                gauge->row_spacing = 25.0f;
                gauge->FieldClass159A70::unk0c = 80.0f;
                gauge->FieldClass159A70::unk10 = 5.0f;
            }

            gauge->func_002BC370(0x80);
            gauge->FieldClass159A70::unk04 = this->unk10;
            lib_queue_display_object(D_001B657C, gauge);
            this->gauges.append(gauge);
            gauge->LibClass174610::unkab = 0;
        }
        else
        {
            LibObject178750* empty = new (0) LibObject178750;
            empty->init_resource_rectangle(16.0f + panel_x, 10.0f + panel_y, 0.0f, 0.0f, source, ITEM_MSG_EMPTY, 0);
            set_widget_rectangle(empty, panel_x, (panel_y + this->row_height / 2.0f) - 9.6f, column_width, 24.0f);
            empty->set_mode(1);

            if (row < 3)
            {
                empty->set_scale(0.8f, 0.8f);
            }
            else
            {
                empty->set_scale(0.8f * 0.8f, 0.8f * 0.8f);
            }

            empty->unk3f = 1;
            lib_container_attach_widget(this->unk10, empty);
        }

        if (row < 3)
        {
            append_selector_position(this->selector, 14.0f + panel_x, 88.0f + panel_y);
        }
        else
        {
            append_selector_position(this->selector, 14.0f + panel_x, 47.0f + panel_y);
        }
    }

    func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(this->selector), 0, 1);
    this->selector->unk3f = 0;
    this->unk10->LibClass174610::unkab = 0;

    for (ItemListNode* node = this->gauges.head->next; node != 0; node = node->next)
    {
        static_cast<LibClass174610*>(node->value)->unkab = 0;
    }

    if (owner->selected_allocation != 0)
    {
        set_item_window_message(owner->help_window, ITEM_MSG_USE_HELP);
        this->message_changed = 1;
    }

    return 1;
}

/** @brief Release the gauges and the window's widgets. */
void ItemUseWindow::func_slot0c()
{
    for (ItemListNode* node = this->gauges.head->next; node != 0; node = node->next)
    {
        static_cast<LibClass171EA0*>(node->value)->func_003EF740();
    }

    FieldClass15AE70::func_slot0c();
}

/** @brief Detach and queue the gauge for release. */
void ItemHpMpGauge::func_003EF740()
{
    queued_for_release = 1;
    func_0044B210(this);
    resident_enqueue_object(D_001B65F4, this);
}

/** @brief Restore the category help line and destroy the gauges and the window. */
ItemUseWindow::~ItemUseWindow()
{
    if (message_changed != 0)
    {
        ItemController* controller = static_cast<ItemController*>(D_001B643C->callbacks->state);
        set_item_window_message(controller->help_window, controller->selected_category + ITEM_MSG_CATEGORY_HELP_BASE);
    }
}

/**
 * @brief Open the equip or use window for the highlighted item.
 * @return Zero while the details are shown, three when the item can't be used, otherwise one.
 */
u8 ItemInstanceListWindow::func_slotb0()
{
    if (details_shown != 0)
    {
        return 0;
    }

    ItemCreationAllocationRecord* records[99];
    ItemController* owner = static_cast<ItemController*>(D_001B643C->callbacks->state);
    s32 count = lib_collect_unequipped_allocations(D_001B64F8, records, (u16)owner->selected_item_type);
    s32 selected = unk24;

    if (count != 0 && selected >= 0)
    {
        u16 identifier = records[0]->definition_index();

        switch ((u8)D_001B64F0[identifier].category)
        {
        case ITEM_CATEGORY_WEAPONS:
        case ITEM_CATEGORY_ARMOR:
        case ITEM_CATEGORY_ACCESSORIES:
        {
            ItemEquipWindow* window = new (0) ItemEquipWindow;
            window->func_slotf4(owner->get_resource_slot());
            window->func_slot40(this);
            window->selector->unk3f = 1;
            window->unk10->unkab = 1;
            owner->add_child(window);
            owner->func_00263C70(window);
            detail_container->unkab = 0;
            break;
        }
        case ITEM_CATEGORY_USABLE:
        case ITEM_CATEGORY_FOOD:
        case ITEM_CATEGORY_OTHER:
        case ITEM_CATEGORY_MATERIALS:
        {
            u16 identifier = records[selected]->definition_index();

            if (((u8)D_001B64F0[identifier].usage_flags & ITEM_USE_IN_MENU) == 0)
            {
                return 3;
            }

            ItemUseWindow* window = new (0) ItemUseWindow;
            window->func_slotf4(owner->get_resource_slot());
            window->func_slot40(this);
            window->selector->unk3f = 1;
            window->unk10->unkab = 1;

            for (ItemListNode* node = window->gauges.head->next; node != 0; node = node->next)
            {
                static_cast<LibClass174610*>(node->value)->unkab = 1;
            }

            owner->add_child(window);
            owner->func_00263C70(window);
            detail_container->unkab = 0;
            break;
        }
        }
    }

    return 1;
}

/** @brief Process list input, show the highlighted item's factors, and close the details once their model is released. */
void ItemInstanceListWindow::func_slot5c()
{
    if (D_001B643C->callbacks->state->func_00261150() == this && details_shown == 0)
    {
        FieldClass15AD40::func_slot5c();
    }
    else if (details_shown == 0)
    {
        func_002CDFB0(&static_cast<FieldStateCE420&>(*this));
    }

    if (D_001B643C->callbacks->state->func_00261150() == this)
    {
        ItemCreationClass175030* display = static_cast<ItemCreationClass175030*>(FieldStateCE420::unk04);
        display->unk30 = 128.0f;
        display->unk3c = 1;
    }
    else
    {
        ItemCreationClass175030* display = static_cast<ItemCreationClass175030*>(FieldStateCE420::unk04);
        display->unk30 = 64.0f;
        display->unk3c = 1;
    }

    ItemController* owner = static_cast<ItemController*>(D_001B643C->callbacks->state);
    ItemCreationAllocationRecord* records[99];

    u32 item_type = owner->selected_item_type;

    if (owner->selected_category != ITEM_CATEGORY_VALUABLES)
    {
        s32 count = lib_collect_unequipped_allocations(D_001B64F8, records, static_cast<u16>(item_type));
        s32 selected = unk24;

        if (count != 0 && selected >= 0)
        {
            s32 shown = 0;

            for (s32 index = 0; index < 8; index++)
            {
                u16 factor = func_0040D930(records[selected], index);

                // Factor 700 marks an empty slot, like zero.
                if (factor != 0 && factor != 700)
                {
                    LibObject172440* factor_widget = factors[shown];
                    factor_widget->unkfc = factor;
                    factor_widget->unk3c = 1;
                    factors[shown]->unk3f = 1;
                    shown++;
                }
            }

            for (; shown < 8; shown++)
            {
                factors[shown]->unk3f = 0;
            }

            LibObject172410* row = item_rows[unk28];
            set_selection_marker(row, row->unk94);
            u8 modification;
            ItemCreationAllocationRecord* record = records[selected];
            modification = record->modification_number;
            u16 identifier = record->definition_index();
            LibObject172410* name = selected_item;
            name->unkfc = identifier + 1;
            name->unkfe = modification;
            name->unk3c = 1;
            owner->selected_allocation = records[selected];
        }
        else
        {
            for (s32 index = 0; index < 8; index++)
            {
                factors[index]->unk3f = 0;
            }

            set_selection_marker(0, ITEM_COLOR_NORMAL);
            owner->selected_allocation = 0;
        }
    }
    else
    {
        owner->selected_allocation = 0;
    }

    for (s32 index = 0; index < 6; index++)
    {
        item_rows[index]->unk3f = 0;
        factor_marks[index]->unk3f = 0;
    }

    if (details_shown != 0)
    {
        category_label->unk3f = 1;
        selected_item->unk3f = 1;
        description->unk3f = 1;
        factor_heading->unk3f = 1;

        if (owner->selected_category == ITEM_CATEGORY_VALUABLES)
        {
            selected_item->unk3f = 0;
        }

        FieldStateCE420::unk04->unk3f = 0;
        FieldStateCE420::unk00->unk3f = 0;
        ItemCreationClass172870* marker = divider;
        marker->unk18.unk04 = 66.0f;
        marker->unk3c = 1;
        set_selection_marker(0, ITEM_COLOR_NORMAL);

        if (closing_details != 0 && func_002FD480(model) != 0)
        {
            details_shown = 0;
            closing_details = 0;
            details_prompt->unk3f = 1;
            lib_text_set_resource(details_prompt, owner->get_resource_slot(), ITEM_MSG_DROP_DETAILS_PROMPT, 0);
            LibObject178750* text = action_prompt;
            text->unk18.unk00 = 448.0f;
            text->unk18.unk04 = 330.0f;
            text->unk3c = 1;
            lib_text_set_resource(action_prompt, owner->get_resource_slot(), ITEM_MSG_BACK_USE_PROMPT, 0);

            if (model != 0)
            {
                model->func_001DD7B0();
                model = 0;
            }

            if (owner->selected_category == ITEM_CATEGORY_VALUABLES)
            {
                field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->callbacks), this);
                ItemTypeListWindow* list = static_cast<ItemTypeListWindow*>(func_slot44());
                list->rebuild_list(0, -1);
                list->func_slot10c(1, 1);
                D_001B643C->callbacks->state->func_00263C70(list);
                details_shown = 1;
            }
        }
    }
    else
    {
        category_label->unk3f = 0;
        selected_item->unk3f = 0;
        description->unk3f = 0;
        factor_heading->unk3f = 0;

        for (s32 index = 0; index < 6; index++)
        {
            item_rows[index]->unk3f = 1;
            factor_marks[index]->unk3f = 1;
        }

        FieldStateCE420::unk04->unk3f = 1;
        FieldStateCE420::unk00->unk3f = 1;
        ItemCreationClass172870* marker = divider;
        marker->unk18.unk04 = 160.0f;
        marker->unk3c = 1;
    }
}

/** @brief Destroy the list receiver and its head node. */
LibClass178A70::~LibClass178A70()
{
}

/**
 * @brief Rebuild the item type list for a category and reset the visible rows and cursor.
 * @param reset Nonzero to move the cursor back to the first row.
 * @param category Category to list, or -1 for the controller's selected category.
 */
void ItemTypeListWindow::rebuild_list(s32 reset, s32 category)
{
    item_types.clear();

    for (s32 index = 0; index < 24; index++)
    {
        new_item_types[index] = 0;
    }

    unk88 = 0;

    category = category == -1 ? controller->selected_category : category;

    FieldClass15AE60::unk8c = category;

    switch (category)
    {
    case ITEM_CATEGORY_VALUABLES:
        unk88 = controller->valuable_count;
        break;
    case ITEM_CATEGORY_COMBAT:
        ItemCreationCategoryRecord* entry = D_001B64F8->item_types;

        for (s32 index = 0; index < ITEM_TYPE_COUNT; index++, entry++)
        {
            if ((static_cast<u8>(D_001B64F0[entry->catalog_index].usage_flags) & ITEM_USE_IN_BATTLE) && entry->inventory_count > 0)
            {
                item_types.append(entry);
                unk88++;
            }
        }

        break;
    case ITEM_CATEGORY_WEAPONS:
    case ITEM_CATEGORY_ARMOR:
    case ITEM_CATEGORY_ACCESSORIES:
    case ITEM_CATEGORY_USABLE:
    case ITEM_CATEGORY_FOOD:
    case ITEM_CATEGORY_OTHER:
    case ITEM_CATEGORY_MATERIALS:
        for (s32 index = 1; index <= ITEM_TYPE_COUNT; index++)
        {
            ItemCreationCategoryRecord* entry = item_category_record(index);

            if (entry != 0 && category == static_cast<u8>(D_001B64F0[entry->catalog_index].category) && entry->inventory_count != 0)
            {
                ItemCreationAllocationRecord* records[100];
                u16 identifier;
                s32 count = item_category_allocations(entry, records, identifier);

                for (s32 record_index = 0; record_index < count; record_index++)
                {
                    if (records[record_index]->new_item)
                    {
                        new_item_types[identifier / 32] |= 1 << (identifier % 32);
                        break;
                    }
                }

                item_types.append(entry);
                unk88++;
            }
        }

        break;
    case ITEM_CATEGORY_NEW:
        for (s32 index = 1; index <= ITEM_TYPE_COUNT; index++)
        {
            ItemCreationCategoryRecord* entry = item_category_record(index);

            if (entry != 0)
            {
                ItemCreationAllocationRecord* records[100];
                u16 identifier;
                s32 count = item_category_allocations(entry, records, identifier);
                bool found = false;

                for (s32 record_index = 0; record_index < count; record_index++)
                {
                    found = records[record_index]->new_item;

                    if (found)
                    {
                        break;
                    }
                }

                if (found)
                {
                    new_item_types[identifier / 32] |= 1 << (identifier % 32);
                    item_types.append(entry);
                    unk88++;
                }
            }
        }

        break;
    default:
        return;
    }

    if (sort_enabled != 0)
    {
        item_types.sort(item_compare_sort_order, 0, 1);
    }

    s32 visible = unk88 >= 13 ? 13 : unk88;

    s32 start = unk22;

    if (unk88 < start + 13)
    {
        start = unk88 - 13;
    }

    if (start < 0)
    {
        start = 0;
    }

    s32 selected = unk28;

    if (selected >= visible)
    {
        selected = visible - 1;
    }

    if (selected < 0)
    {
        selected = 0;
    }

    if (reset != 0)
    {
        selected = 0;
        start = 0;
    }

    func_002CE420(&static_cast<FieldStateCE420&>(*this), 1, visible, 378, 28);
    configure_selection(unk88, start, selected);
}

/** @brief Clear the row widgets and link the controller. @param owner Parent item controller. */
ItemTypeListWindow::ItemTypeListWindow(ItemController* owner)
{
    for (s32 index = 0; index < 14; index++)
    {
        unk48[index] = 0;
        separators[index] = 0;
        counts[index] = 0;
    }

    // TODO: The only way I found to get the original's two stores is to clear the link before setting it.
    controller = 0;
    controller = owner;
    sort_enabled = 0;
    FieldClass15AD40();
}

/**
 * @brief Compare two item types by their catalog list order.
 * @param left First node, holding an item type record.
 * @param right Second node, holding an item type record.
 * @param comparison_arg Unused.
 * @return Negative, zero or positive as left sorts before, with or after right.
 */
s32 item_compare_sort_order(const ItemListNode* left, const ItemListNode* right, u32 comparison_arg)
{
    const ItemCreationCategoryRecord* first = static_cast<const ItemCreationCategoryRecord*>(left->value);
    const ItemCreationCategoryRecord* second = static_cast<const ItemCreationCategoryRecord*>(right->value);
    const ItemCreationCategoryDefinition* first_definition = &D_001B64F0[first->catalog_index];
    const ItemCreationCategoryDefinition* second_definition = &D_001B64F0[second->catalog_index];
    return first_definition->sort_order - second_definition->sort_order;
}

/**
 * @brief Create the item rows, factor widgets, description, prompts, cursor and scroll indicator.
 * @param associated Loaded resource slot.
 * @return One.
 */
s32 ItemInstanceListWindow::func_slot104(u32 associated)
{
    FieldClass15AE70::func_slot14(associated, 0, 9, 2400, 20.0f, 83.0f, 0.0f);
    FieldClass15AE60::unk3c = 1;
    detail_container = new (0) LibObject178660;
    lib_container_init(detail_container, 14, 20.0f, 83.0f, 0, 0.0f, 0);
    lib_queue_display_object(D_001B657C, detail_container);
    LibClass1746A0* clip = new (0) LibClass1746A0;
    LibClass1746A0* reset = new (0) LibClass1746A0;
    panel = new (0) LibClass178630;
    lib_panel_init_rectangle(panel, 1, 0.0f, 0.0f, 590.0f, 370.0f, 88.0f);
    lib_container_attach_widget(FieldClass15AE70::unk10, panel);
    lib_panel_init_transform(panel, 1500.0f);
    lib_scissor_init_rectangle(clip, 16.0f, 16.0f, 600.0f, 140.0f);
    lib_container_attach_widget(FieldClass15AE70::unk10, clip);
    void* allocation = field_get_aligned_allocation(D_001B643C->resources, 14);

    for (s32 index = 0; index < 6; index++)
    {
        FieldResourceRecord* record = field_find_resource_record(D_001B643C->resources, 60);
        factor_marks[index] = new (0) ItemCreationOptionResourceDisplay;
        factor_marks[index]->unkcc = allocation;
        factor_marks[index]->unkd0 = 14;
        float y = 16.0f + 28.0f * static_cast<float>(index);
        factor_marks[index]->func_002D6440(30.0f, y, record);
        ItemCreationOptionResourceDisplay* mark = factor_marks[index];
        mark->unk50.unk34 = 0.95f;
        mark->unk50.unk30 = 0.95f;
        mark->unk3c = 1;
        factor_marks[index]->unk3d = 0;
        lib_container_attach_widget(FieldClass15AE70::unk10, factor_marks[index]);
        item_rows[index] = new (0) LibObject172410;
        lib_item_code_init_rectangle(item_rows[index], 60.0f, y, 323.99997f, 21.599998f, 100, 0, 0);
        item_rows[index]->set_scale(0.9f, 0.9f);
        LibObject172410* text = item_rows[index];
        text->unkfa = 1;
        text->unk3c = 1;
        text = item_rows[index];
        text->unk88 = -1.0f;
        text->unk3c = 1;
        item_rows[index]->unk3d = 0;
        lib_container_attach_widget(FieldClass15AE70::unk10, item_rows[index]);
    }

    lib_scissor_init_reset(reset, 1);
    lib_container_attach_widget(FieldClass15AE70::unk10, reset);
    divider = new (0) ItemCreationClass172870;
    lib_marker_init_rectangle(divider, 24.0f, 160.0f, 550.0f, 4.0f);
    ItemCreationClass172870* marker = divider;
    marker->unk50 = 0xDC6464;
    marker->unk3c = 1;
    lib_container_attach_widget(FieldClass15AE70::unk10, divider);
    FieldRuntime* runtime = D_001B657C;
    runtime->detail_resource_slot = associated;
    runtime->detail_base_key = ITEM_MSG_FIRST_FACTOR_NAME;
    s32 index;

    for (index = 0; index < 8; index++)
    {
        factors[index] = new (0) LibObject172440;
        lib_detail_code_init_rectangle(factors[index], 0, 1, 0, 24.0f, static_cast<float>(175 + 22 * index), 0.0f, 0.0f);
        LibObject172440* text = factors[index];
        text->unk80 = 0.8f;
        text->unk84 = 0.8f;
        text->unk3c = 1;
        factors[index]->unk3f = 0;
        lib_container_attach_widget(detail_container, factors[index]);
    }

    ItemController* owner = static_cast<ItemController*>(D_001B643C->callbacks->state);
    category_label = new (0) LibObject178750;
    category_label->init_resource_rectangle(16.0f, 12.0f, 0.0f, 0.0f, associated, owner->selected_category + ITEM_MSG_CATEGORY_NAME_BASE, 0);
    LibObject178750* text = category_label;
    text->unk88 = -1.0f;
    text->unk3c = 1;
    category_label->set_scale(0.8f, 0.8f);
    category_label->set_color(ITEM_COLOR_HEADING);
    category_label->unk3f = 0;
    lib_container_attach_widget(FieldClass15AE70::unk10, category_label);
    selected_item = new (0) LibObject172410;
    lib_item_code_init_rectangle(selected_item, 24.0f, 34.0f, 561.6f, 31.199999f, 0, 0, 0);
    LibObject172410* code = selected_item;
    code->unkfc = owner->selected_item_type;
    code->unkfe = 0;
    code->unk3c = 1;
    selected_item->set_scale(1.3f, 1.3f);
    selected_item->unk3f = 0;
    lib_container_attach_widget(FieldClass15AE70::unk10, selected_item);

    if (owner->selected_category == ITEM_CATEGORY_VALUABLES)
    {
        LibObject178750* name = new (0) LibObject178750;
        name->init_resource_rectangle(24.0f, 34.0f, 0.0f, 0.0f, associated, owner->selected_item_type + ITEM_MSG_VALUABLE_NAME_BASE, 0);
        name->set_scale(1.3f, 1.3f);
        lib_container_attach_widget(FieldClass15AE70::unk10, name);
        description = new (0) LibObject178750;
        description->init_resource_rectangle(24.0f, 78.0f, 534.0f, 66.0f, associated, owner->selected_item_type + ITEM_MSG_VALUABLE_DESCRIPTION_BASE, 0);
    }
    else
    {
        description = new (0) LibObject178750;
        description->init_resource_rectangle(24.0f, 78.0f, 534.0f, 66.0f, associated, owner->selected_item_type + ITEM_MSG_ITEM_DESCRIPTION_BASE, 0);
    }

    description->set_mode(0);
    description->set_vertical_alignment(1);
    text = description;
    text->unk88 = -1.0f;
    text->unk3c = 1;
    description->set_scale(0.9f, 0.9f);
    description->unk3f = 0;
    lib_container_attach_widget(detail_container, description);
    factor_heading = new (0) LibObject178750;
    factor_heading->init_resource_rectangle(16.0f, 150.0f, 0.0f, 0.0f, associated, ITEM_MSG_FACTOR_HEADING, 0);
    factor_heading->set_scale(0.8f, 0.8f);
    factor_heading->set_color(ITEM_COLOR_HEADING);
    text = factor_heading;
    text->unk88 = -1.0f;
    text->unk3c = 1;
    factor_heading->unk3f = 0;
    lib_container_attach_widget(FieldClass15AE70::unk10, factor_heading);
    details_prompt = new (0) LibObject178750;
    details_prompt->init_resource_rectangle(400.0f, 295.0f, 0.0f, 0.0f, associated, ITEM_MSG_DROP_DETAILS_PROMPT, 1);
    lib_container_attach_widget(detail_container, details_prompt);
    action_prompt = new (0) LibObject178750;
    action_prompt->init_resource_rectangle(448.0f, 330.0f, 0.0f, 0.0f, associated, ITEM_MSG_BACK_USE_PROMPT, 1);
    lib_container_attach_widget(detail_container, action_prompt);
    FieldClass15AE60::unk34 = 28.0f;
    FieldClass15AE60::unk38 = 28.0f;
    FieldStateCE420::unk04 = new (0) LibClass175030;
    lib_moving_widget_init_position(static_cast<LibClass175030*>(FieldStateCE420::unk04), 28.0f, 28.0f);
    lib_container_attach_widget(FieldClass15AE70::unk10, FieldStateCE420::unk04);
    FieldStateCE420::unk04->unk3f = 0;
    FieldStateCE420::unk00 = new (0) LibClass1725D0;
    lib_list_indicator_init(static_cast<LibClass1725D0*>(FieldStateCE420::unk00), 558.0f, 14.0f, 140.0f, 10.0f, 0.0f);
    FieldStateCE420::unk00->unk3f = 0;
    lib_container_attach_widget(FieldClass15AE70::unk10, FieldStateCE420::unk00);
    func_002CE420(&static_cast<FieldStateCE420&>(*this), 1, 6, 378, 28);
    FieldClass15AE60::unk2b = 3;
    unk84 = 0;
    unk85 = 0;
    func_slot110(1);
    func_slot10c(1, 1);
    refresh_instances(1);
    return 1;
}

/**
 * @brief Recount the items and clamp the cursor, or open the details for a valuable.
 * @param reset Nonzero to move the cursor back to the first row.
 */
void ItemInstanceListWindow::refresh_instances(s32 reset)
{
    unk88 = 0;
    ItemController* owner = static_cast<ItemController*>(D_001B643C->callbacks->state);

    u32 item_type = owner->selected_item_type;

    if (owner->selected_category == ITEM_CATEGORY_VALUABLES)
    {
        s32 key = g_item_valuable_models[static_cast<u16>(item_type)] + 0x88;

        if (model == 0)
        {
            model = new (0) FieldClass15BB90;
            field_request_model_resource(model, key);
            model->unk5b = 1;
            field_replace_model_camera(model, D_001B643C->field_camera);
            field_attach_model_display(model);

            if (reinterpret_cast<ItemDisplaySettings*>(resident_find_entry(resident_get_entry_table(resident_get_runtime_owner()), 1))->widescreen != 0)
            {
                func_002FD1B0(reinterpret_cast<FieldFloatState5C*>(model), 0.5235988f, 600.0f, 0.34906584f, 120.0f, 35.0f);
            }
            else
            {
                func_002FD1B0(reinterpret_cast<FieldFloatState5C*>(model), 0.5235988f, 500.0f, 0.34906584f, 90.0f, 50.0f);
            }

            D_001B6614->append_node(model, -1);
        }

        details_shown = 1;
        details_prompt->unk3f = 0;
        lib_text_set_resource(details_prompt, owner->get_resource_slot(), ITEM_MSG_DROP_DETAILS_PROMPT, 0);
        LibObject178750* prompt = action_prompt;
        prompt->unk18.unk00 = 518.0f;
        prompt->unk3c = 1;
        lib_text_set_resource(action_prompt, owner->get_resource_slot(), ITEM_MSG_DETAILS_BACK_PROMPT, 0);
        selected_item->unk3f = 0;
        FieldStateCE420::unk04->unk3d = 0;
        FieldStateCE420::unk00->unk3d = 0;
        LibClass178600* marker = divider;
        marker->unk18.unk04 = 66.0f;
        marker->unk3c = 1;
    }
    else
    {
        ItemCreationAllocationRecord* records[99];
        unk88 = lib_collect_unequipped_allocations(D_001B64F8, records, static_cast<u16>(item_type));
        s32 visible = unk88;

        if (visible >= 5)
        {
            visible = 5;
        }

        s32 start = unk22;

        if (unk88 < start + 5)
        {
            start = unk88 - 5;
        }

        if (start < 0)
        {
            start = 0;
        }

        s32 selected = unk28;

        if (selected >= visible)
        {
            selected = visible - 1;
        }

        if (selected < 0)
        {
            selected = 0;
        }

        if (reset != 0)
        {
            selected = 0;
            start = 0;
        }

        func_002CE420(&static_cast<FieldStateCE420&>(*this), 1, visible, 378, 28);
        configure_selection(unk88, start, selected);
    }
}

/**
 * @brief Close the window and return to the instance list.
 * @return Zero while input is blocked, otherwise two.
 */
u8 ItemDropConfirmWindow::func_slotb4()
{
    if (func_slot28())
    {
        return 0;
    }

    ItemController* owner = static_cast<ItemController*>(D_001B643C->callbacks->state);
    owner->remove_child(this);
    ItemInstanceListWindow* window = static_cast<ItemInstanceListWindow*>(func_slot44());
    window->detail_container->unkab = 1;
    owner->func_00263C70(window);
    return 2;
}

/**
 * @brief Drop the selected item on Yes, then return to the instance list or the type list.
 * @return Zero while input is blocked, the back result when No is selected, otherwise one.
 */
u8 ItemDropConfirmWindow::func_slotb0()
{
    if (func_slot28())
    {
        return 0;
    }

    if (grid != 0 && grid->unk114 != 0)
    {
        return func_slotb4();
    }

    ItemController* owner = static_cast<ItemController*>(D_001B643C->callbacks->state);
    func_0040C9F0(D_001B64F8, lib_allocation_get_identifier(owner->selected_allocation));
    ItemCreationAllocationRecord* records[99];
    u16 identifier = owner->selected_allocation->definition_index();

    if (lib_collect_unequipped_allocations(D_001B64F8, records, identifier + 1) == 0)
    {
        owner->remove_child(this);
        owner->remove_child(func_slot44());
        ItemTypeListWindow* list = static_cast<ItemTypeListWindow*>(static_cast<ItemInstanceListWindow*>(func_slot44())->func_slot44());
        list->rebuild_list(0, -1);
        list->func_slot10c(1, 1);
        D_001B643C->callbacks->state->func_00263C70(list);
    }
    else
    {
        owner->remove_child(this);
        ItemInstanceListWindow* window = static_cast<ItemInstanceListWindow*>(func_slot44());
        window->detail_container->unkab = 1;
        window->refresh_instances(0);
        owner->func_00263C70(window);
    }

    return 1;
}

/** @brief Destroy the window. */
ItemDropConfirmWindow::~ItemDropConfirmWindow()
{
}

/** @brief Enable the Yes/No grid while this is the focused window. */
void ItemDropConfirmWindow::func_slot5c()
{
    void* active = D_001B643C->callbacks->state->func_00261150();
    func_0023CEA0(this->grid, active == this);
    D_001B643C->callbacks->state->func_00261150();
}

/**
 * @brief Create the panels, the title and question, and the Yes/No grid.
 * @param associated Resource source word.
 * @return One.
 */
s32 ItemDropConfirmWindow::func_slotf4(u32 associated)
{
    LibClass178630* panel;
    LibObject178750* text;
    FieldObject23CEA0* grid;
    LibWidgetColors4C5590 colors;
    FieldClass15AE70::func_slot10(associated, 145.0f, 170.0f, 13);
    panel = allocate_panel();
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 350.0f, 176.0f, 88.0f);
    lib_container_attach_widget(this->unk10, panel);
    unk14.append(panel);
    panel = allocate_panel();
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 350.0f, 48.0f, 88.0f);
    lib_container_attach_widget(this->unk10, panel);
    colors = g_item_drop_title_colors;
    lib_panel_set_colors(panel, &colors);
    unk14.append(panel);
    text = allocate_text_widget();
    text->init_resource_rectangle(0.0f, 12.0f, 350.0f, 48.0f, associated, ITEM_MSG_DROP_TITLE, 0);
    set_text_mode(text, 1);
    lib_container_attach_widget(this->unk10, text);
    text = allocate_text_widget();
    text->init_resource_rectangle(0.0f, 64.0f, 350.0f, 64.0f, associated, ITEM_MSG_DROP_QUESTION, 0);
    set_text_mode(text, 1);
    lib_container_attach_widget(this->unk10, text);
    this->yes_text = allocate_text_widget();
    this->no_text = allocate_text_widget();
    this->yes_text->init_resource_rectangle(122.0f, 132.0f, 0.0f, 0.0f, associated, ITEM_MSG_YES, 0);
    lib_container_attach_widget(this->unk10, this->yes_text);
    this->no_text->init_resource_rectangle(212.0f, 132.0f, 0.0f, 0.0f, associated, ITEM_MSG_NO, 0);
    lib_container_attach_widget(this->unk10, this->no_text);
    grid = new (0) FieldObject23CEA0;
    this->grid = grid;
    func_0023CE80((FieldObject23CE80*)this->grid, 2, 1);
    func_0023CE60((FieldObject23CE80*)this->grid, 80.0f, 0.0f);
    this->grid->unkF2 = 0;
    func_0023CF50((FieldObject23CEB0*)this->grid, 1, 265.0f, 302.0f);
    this->grid->unkad = 0;
    unk74.append(this->grid);

    if (this->grid->unk114 != 0)
    {
        set_text_color(this->yes_text, ITEM_COLOR_NORMAL);
        set_text_color(this->no_text, ITEM_COLOR_SELECTED);
    }
    else
    {
        set_text_color(this->yes_text, ITEM_COLOR_SELECTED);
        set_text_color(this->no_text, ITEM_COLOR_NORMAL);
    }

    return 1;
}

/**
 * @brief Ask whether to drop the highlighted item.
 * @return Zero while the details are shown, three for an item that can't be dropped, otherwise one.
 */
u8 ItemInstanceListWindow::func_slotbc()
{
    if (details_shown != 0)
    {
        return 0;
    }

    ItemCreationAllocationRecord* records[99];
    ItemController* owner = static_cast<ItemController*>(D_001B643C->callbacks->state);
    s32 count = lib_collect_unequipped_allocations(D_001B64F8, records, (u16)owner->selected_item_type);
    s32 selected = unk24;

    if (count != 0 && selected >= 0)
    {
        ItemCreationAllocationRecord* allocation = records[selected];
        u16 identifier = allocation->definition_index();

        if (item_definition_unsellable(&D_001B64F0[identifier]) == 0)
        {
            ItemDropConfirmWindow* window = new (0) ItemDropConfirmWindow;
            window->func_slotf4(owner->get_resource_slot());
            window->func_slot40(this);
            owner->add_child(window);
            owner->func_00263C70(window);
        }
        else
        {
            return 3;
        }
    }

    return 1;
}

/** @brief Detach the panel and destroy the window. */
ItemInstanceListWindow::~ItemInstanceListWindow()
{
    if (panel != 0)
    {
        lib_panel_detach(panel);
    }
}

/** @brief Release the detail container and the window's widgets. */
void ItemInstanceListWindow::func_slot0c()
{
    detail_container->func_003EF740();
    FieldClass15AE70::func_slot0c();
}

/** @brief Turn the details model back, down to zero. */
void ItemInstanceListWindow::func_slot6c()
{
    if (this->details_shown != 0)
    {
        FieldClass15BB90* angle = this->model;

        if (angle != 0)
        {
            float value = angle->values[2];
            value -= MODEL_TURN_STEP;

            if (value < 0.0f)
            {
                value = 0.0f;
            }

            angle->values[2] = value;
        }
    }
}

/** @brief Turn the details model, up to thirty degrees. */
void ItemInstanceListWindow::func_slot68()
{
    if (this->details_shown != 0)
    {
        FieldClass15BB90* angle = this->model;

        if (angle != 0)
        {
            float value = angle->values[2];
            value += MODEL_TURN_STEP;

            if (value > MODEL_TURN_LIMIT)
            {
                value = MODEL_TURN_LIMIT;
            }

            angle->values[2] = value;
        }
    }
}

/**
 * @brief Show or hide the rows and the cursor.
 * @param rows Visibility of each item row and its factor marks.
 * @param cursor Nonzero shows the cursor and indicator at full brightness; zero hides them and dims the cursor.
 */
void ItemInstanceListWindow::func_slot10c(u32 value, u32 alternate)
{
    item_rows[0]->unk3f = value;
    factor_marks[0]->unk3f = value;
    item_rows[1]->unk3f = value;
    factor_marks[1]->unk3f = value;
    item_rows[2]->unk3f = value;
    factor_marks[2]->unk3f = value;
    item_rows[3]->unk3f = value;
    factor_marks[3]->unk3f = value;
    item_rows[4]->unk3f = value;
    factor_marks[4]->unk3f = value;
    item_rows[5]->unk3f = value;
    factor_marks[5]->unk3f = value;

    if (panel != 0)
    {
        panel->unk3f = 1;
    }

    if (FieldClass15AE60::unk04 != 0)
    {
        FieldClass15AE60::unk04->unk3f = alternate;

        if (alternate != 0)
        {
            LibClass175030* control = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
            control->ItemCreationClass185050::unk30 = 128.0f;
            control->unk3c = 1;
        }
        else
        {
            LibClass175030* control = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
            control->ItemCreationClass185050::unk30 = 64.0f;
            control->unk3c = 1;
        }
    }

    if (FieldClass15AE60::unk00 != 0)
    {
        FieldClass15AE60::unk00->unk3f = alternate;
    }
}

/** @brief Position the rows. @param start Vertical offset. */
void ItemInstanceListWindow::set_scroll_position(float offset)
{
    ItemController* controller = static_cast<ItemController*>(D_001B643C->callbacks->state);

    if (controller->selected_category != ITEM_CATEGORY_VALUABLES)
    {
        float y = 16.0f + offset;

        s32 row = 0;

        do
        {
            LibClass178600* screen = item_rows[row];
            screen->unk18.unk04 = y;
            screen->unk3c = 1;
            screen = factor_marks[row];
            screen->unk18.unk04 = y;
            screen->unk3c = 1;
            y += 28.0f;
            row++;
        } while (row < 6);
    }
}

/** @brief Fill the visible rows. @param start First list index. */
void ItemInstanceListWindow::refresh_rows(s32 start)
{
    ItemCreationAllocationRecord* records[99];
    ItemController* owner = static_cast<ItemController*>(D_001B643C->callbacks->state);

    if (owner->selected_category != ITEM_CATEGORY_VALUABLES)
    {
        u32 item_type = owner->selected_item_type;
        s32 index;
        func_0013A678(records, 0, sizeof(records));
        unk88 = lib_collect_unequipped_allocations(D_001B64F8, records, (u16)item_type);

        for (index = 0; index < 6; index++)
        {
            if (records[start + index] != 0)
            {
                LibObject172410* row = item_rows[index];
                u8 modification = records[start + index]->modification_number;
                s32 factor_count = 0;
                s32 slot;
                void* allocation;
                FieldResourceRecord* record;
                row->unkfc = item_type;
                row->unkfe = modification;
                row->unk3c = 1;

                for (slot = 0; slot < 8; slot++)
                {
                    u16 factor = func_0040D930(records[start + index], slot);

                    // Factor 700 marks an empty slot, like zero.
                    if (factor != 0 && factor != 700)
                    {
                        factor_count++;
                    }
                }

                allocation = field_get_aligned_allocation(D_001B643C->resources, 14);
                record = field_find_resource_record(D_001B643C->resources, factor_count + 60);
                func_002D5CF0(factor_marks[index], allocation, record, 14);
                item_rows[index]->unk3d = 1;
                factor_marks[index]->unk3d = 1;
            }
            else
            {
                item_rows[index]->unk3d = 0;
                factor_marks[index]->unk3d = 0;
            }
        }
    }
}

/**
 * @brief Show or hide the details for the highlighted item.
 * @return Zero.
 */
u8 ItemInstanceListWindow::func_slotb8()
{
    ItemController* owner = static_cast<ItemController*>(D_001B643C->callbacks->state);

    if (owner->selected_category == ITEM_CATEGORY_VALUABLES)
    {
        return 0;
    }

    if (details_shown != 0)
    {
        field_cancel_model_request(model);
        closing_details = 1;
        resident_allocate_request(D_001B65F8, 2, 0, 0, 0x7F, 0x40, 0);
    }
    else
    {
        ItemCreationAllocationRecord* records[99];
        s32 count = lib_collect_unequipped_allocations(D_001B64F8, records, (u16)owner->selected_item_type);
        s32 selected = unk24;

        if (count != 0 && selected >= 0)
        {
            u16 identifier = records[selected]->definition_index();
            s32 key = (u16)D_001B64F0[identifier].model_index + 0x88;

            if (model == 0)
            {
                model = new (0) FieldClass15BB90;
                field_request_model_resource(model, key);
                model->unk5b = 1;
                field_replace_model_camera(model, D_001B643C->field_camera);
                field_attach_model_display(model);

                if (reinterpret_cast<ItemDisplaySettings*>(resident_find_entry(resident_get_entry_table(resident_get_runtime_owner()), 1))->widescreen != 0)
                {
                    func_002FD1B0(reinterpret_cast<FieldFloatState5C*>(model), 0.5235988f, 600.0f, 0.34906584f, 120.0f, 35.0f);
                }
                else
                {
                    func_002FD1B0(reinterpret_cast<FieldFloatState5C*>(model), 0.5235988f, 500.0f, 0.34906584f, 90.0f, 50.0f);
                }

                D_001B6614->append_node(model, -1);
            }

            details_shown = 1;
            details_prompt->unk3f = 0;
            lib_text_set_resource(details_prompt, owner->get_resource_slot(), ITEM_MSG_DROP_DETAILS_PROMPT, 0);
            LibObject178750* text = action_prompt;
            text->unk18.unk00 = 425.0f;
            text->unk18.unk04 = 337.0f;
            text->unk3c = 1;
            lib_text_set_resource(action_prompt, owner->get_resource_slot(), ITEM_MSG_SWITCH_BACK_PROMPT, 0);
            resident_allocate_request(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
        }
    }

    return 0;
}

/**
 * @brief Close the details, or return to the type list.
 * @return Two.
 */
u8 ItemInstanceListWindow::func_slotb4()
{
    if (details_shown != 0)
    {
        if (model != 0)
        {
            field_cancel_model_request(model);
            closing_details = 1;
        }

        return 2;
    }

    ItemController* owner = static_cast<ItemController*>(D_001B643C->callbacks->state);
    owner->remove_child(this);
    ItemTypeListWindow* list = static_cast<ItemTypeListWindow*>(func_slot44());
    list->rebuild_list(0, -1);
    list->func_slot10c(1, 1);
    D_001B643C->callbacks->state->func_00263C70(list);
    return 2;
}

/**
 * @brief Open the instance list for the highlighted item type.
 * @return Three for an empty list, zero without a controller or for Valuables, otherwise one.
 */
u8 ItemTypeListWindow::func_slotb0()
{
    if (unk88 == 0)
    {
        return 3;
    }

    if (controller == 0)
    {
        return 0;
    }

    ItemInstanceListWindow* window = new (0) ItemInstanceListWindow;
    window->func_slot104(controller->get_resource_slot());
    window->func_slot40(this);
    controller->add_child(window);
    controller->func_00263C70(window);

    if (FieldClass15AE60::unk04 != 0)
    {
        LibClass175030* selector = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
        selector->ItemCreationClass185050::unk30 = 64.0f;
        selector->unk3c = 1;
    }

    if (controller->selected_category == ITEM_CATEGORY_VALUABLES)
    {
        resident_allocate_request(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
        return 0;
    }

    return 1;
}

/**
 * @brief Create the row widgets, the clip region, the cursor and the scroll indicator.
 * @param associated Resource source word.
 * @return One.
 */
s32 ItemTypeListWindow::func_slot104(u32 associated)
{
    FieldClass15AE60::pad30[0] = 1;
    FieldClass15AE60::unk3c = 1;
    FieldClass15AE70::func_slot14(associated, 0, 9, 0x708, 216.0f, 72.0f, 0.0f);
    LibClass1746A0* clip = new (0) LibClass1746A0;
    LibClass1746A0* reset = new (0) LibClass1746A0;
    lib_scissor_init_rectangle(clip, 18.0f, 14.0f, 378.0f, 366.0f);
    lib_container_attach_widget(FieldClass15AE70::unk10, clip);

    for (s32 index = 0; index < 14; index++)
    {
        unk48[index] = new (0) LibObject178750;
        separators[index] = new (0) LibObject178750;
        counts[index] = new (0) LibObject174F20;
        float y = 16.0f + 28.0f * (float)index;
        reinterpret_cast<LibObject178750*>(unk48[index])->init_resource_rectangle(22.0f, y, 0.0f, 0.0f, associated, ITEM_MSG_ITEM_NAME_BASE, 0);
        separators[index]->init_resource_rectangle(326.0f, y - 4.0f, 0.0f, 0.0f, associated, ITEM_MSG_SEPARATOR, 1);
        lib_numeric_widget_init_rectangle(counts[index], index, associated, 1, 334.0f, y, 28.0f, 24.0f);

        LibClass174EF0* name = static_cast<LibClass174EF0*>(unk48[index]);
        name->unk88 = -1.0f;
        name->unk3c = 1;
        static_cast<LibClass174EF0*>(unk48[index])->set_scale(0.9f, 0.9f);
        lib_container_attach_widget(FieldClass15AE70::unk10, unk48[index]);
        lib_container_attach_widget(FieldClass15AE70::unk10, separators[index]);
        lib_container_attach_widget(FieldClass15AE70::unk10, counts[index]);
    }

    lib_scissor_init_reset(reset, 1);
    lib_container_attach_widget(FieldClass15AE70::unk10, reset);
    FieldClass15AE60::unk34 = 20.0f;
    FieldClass15AE60::unk38 = 28.0f;
    FieldClass15AE60::unk04 = new (0) LibClass175030;
    lib_moving_widget_init_position(static_cast<LibClass175030*>(FieldClass15AE60::unk04), 20.0f, 28.0f);
    lib_container_attach_widget(FieldClass15AE70::unk10, FieldClass15AE60::unk04);
    FieldClass15AE60::unk04->unk3f = 0;
    FieldClass15AE60::unk00 = new (0) LibClass1725D0;
    lib_list_indicator_init(static_cast<LibClass1725D0*>(FieldClass15AE60::unk00), 376.0f, 16.0f, 362.0f, 10.0f, 0.0f);
    lib_container_attach_widget(FieldClass15AE70::unk10, FieldClass15AE60::unk00);
    func_002CE420(&static_cast<FieldStateCE420&>(*this), 1, 13, 378, 28);
    FieldClass15AE60::unk2b = 3;
    unk84 = 0;
    unk85 = 0;
    func_slot10c(1, 0);
    rebuild_list(1, 0);
    return 1;
}

/** @brief Default storage release hook; does nothing. */
void ItemCreationClass185050::func_slot0c()
{
}

/** @brief Process list input, publish the highlighted item type and move the row marker. */
void ItemTypeListWindow::func_slot5c()
{
    if (D_001B643C->callbacks->state->func_00261150() == this)
    {
        FieldClass15AD40::func_slot5c();

        if (FieldClass15AE60::unk8c == ITEM_CATEGORY_VALUABLES)
        {
            s16 selected = unk24;

            if (selected >= 0)
            {
                ItemController* owner = controller;
                s32 entry;

                if (selected >= owner->valuable_count)
                {
                    entry = -1;
                }
                else
                {
                    entry = owner->valuables[selected];
                }

                owner->selected_item_type = entry;
            }
        }
        else
        {
            ItemListNode* node = item_types.at(unk24);

            if (node != 0)
            {
                ItemCreationCategoryRecord* record = static_cast<ItemCreationCategoryRecord*>(node->value);
                controller->selected_item_type = (u16)(record->catalog_index + 1);
            }
        }

        if (unk24 >= 0 && unk88 != 0)
        {
            LibClass174EF0* display = static_cast<LibClass174EF0*>(unk48[unk28]);
            set_selection_marker(display, display->unk94);
        }
        else
        {
            set_selection_marker(0, ITEM_COLOR_NORMAL);
        }
    }
    else
    {
        set_selection_marker(0, ITEM_COLOR_NORMAL);
    }
}

/** @brief Fill the visible rows with names and counts. @param start First list index. */
void ItemTypeListWindow::refresh_rows(s32 start)
{
    if (controller != 0)
    {
        if (FieldClass15AE60::unk8c == ITEM_CATEGORY_VALUABLES)
        {
            for (s32 index = 0; index < 14; index++)
            {
                s32 entry;

                if (index + start >= controller->valuable_count)
                {
                    entry = -1;
                }
                else
                {
                    entry = controller->valuables[start + index];
                }

                if (entry >= 0)
                {
                    lib_text_set_resource(reinterpret_cast<LibObject178750*>(unk48[index]), func_slot54(), entry + ITEM_MSG_VALUABLE_NAME_BASE, 0);
                    static_cast<LibClass174EF0*>(unk48[index])->set_color(ITEM_COLOR_NORMAL);
                    LibObject174F20* numeric = counts[index];
                    numeric->numeric_value = 1;
                    numeric->unk3c = 1;
                    unk48[index]->unk3d = 1;
                    counts[index]->unk3d = 1;
                    separators[index]->unk3d = 1;
                }
                else
                {
                    unk48[index]->unk3d = 0;
                    counts[index]->unk3d = 0;
                    separators[index]->unk3d = 0;
                }
            }
        }
        else
        {
            ItemListNode* node = item_types.at(start);

            for (s32 index = 0; index < 14; index++)
            {
                if (node != 0)
                {
                    s32 text_key;
                    ItemCreationCategoryRecord* record = static_cast<ItemCreationCategoryRecord*>(node->value);

                    if (record != 0)
                    {
                        s32 identifier = (u16)(record->catalog_index + 1);
                        text_key = identifier + ITEM_MSG_ITEM_NAME_BASE;

                        if ((new_item_types[identifier / 32] & (1 << (identifier % 32))) != 0)
                        {
                            static_cast<LibClass174EF0*>(unk48[index])->set_color(ITEM_COLOR_NEW_ITEM);
                        }
                        else
                        {
                            static_cast<LibClass174EF0*>(unk48[index])->set_color(ITEM_COLOR_NORMAL);
                        }

                        lib_text_set_resource(reinterpret_cast<LibObject178750*>(unk48[index]), func_slot54(), text_key, 0);
                        LibObject174F20* numeric = counts[index];
                        numeric->numeric_value = record->inventory_count;
                        numeric->unk3c = 1;
                        unk48[index]->unk3d = 1;
                        counts[index]->unk3d = 1;
                        separators[index]->unk3d = 1;
                    }

                    node = node->next;
                }
                else
                {
                    unk48[index]->unk3d = 0;
                    counts[index]->unk3d = 0;
                    separators[index]->unk3d = 0;
                }
            }
        }
    }
}

/** @brief Destroy the item type list and the Field window. */
ItemTypeListWindow::~ItemTypeListWindow()
{
}

/** @brief Set the list flag. @param value Flag value to store. */
void FieldClass15AD40::func_slot110(u8 value)
{
    unk84 = value;
}

/** @brief Toggle sorting and refresh the visible rows. @return Zero for Valuables, otherwise one. */
u8 ItemTypeListWindow::func_slotbc()
{
    if (this->FieldClass15AE60::unk8c == ITEM_CATEGORY_VALUABLES)
    {
        return 0;
    }

    this->sort_enabled = !this->sort_enabled;

    if (this->sort_enabled != 0)
    {
        this->item_types.sort(item_compare_sort_order, 0, 1);
    }
    else
    {
        this->rebuild_list(0, -1);
    }

    this->refresh_rows(this->unk22);
    return 1;
}

/** @brief Hide the cursor and return to the category window. @return Two. */
u8 ItemTypeListWindow::func_slotb4()
{
    this->func_slot10c(0, 0);
    FieldClass15AE70* associated = static_cast<FieldClass15AE70*>(this->func_slot44());
    associated->func_slot64();
    D_001B643C->callbacks->state->func_00263C70(associated);
    return 2;
}

/**
 * @brief Show or hide the cursor.
 * @param unused Unused.
 * @param cursor Nonzero shows the cursor at full brightness; zero hides it and dims it.
 */
void ItemTypeListWindow::func_slot10c(u32 unused, u32 cursor)
{
    if (FieldClass15AE60::unk04 != 0)
    {
        FieldClass15AE60::unk04->unk3f = cursor;

        if (cursor != 0)
        {
            LibClass175030* control = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
            control->ItemCreationClass185050::unk30 = 128.0f;
            control->unk3c = 1;
        }
        else
        {
            LibClass175030* control = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
            control->ItemCreationClass185050::unk30 = 64.0f;
            control->unk3c = 1;
        }
    }
}

/** @brief Position the row widgets. @param start Base vertical coordinate. */
void ItemTypeListWindow::set_scroll_position(float start)
{
    s32 index;
    float value = start + 16.0f;

    for (index = 0; index < 14; index++)
    {
        LibClass178600* slot = unk48[index];
        slot->unk18.unk00 = 24.0f;
        slot->unk18.unk04 = value;
        slot->unk3c = 1;
        slot = separators[index];
        slot->unk18.unk00 = 326.0f;
        slot->unk18.unk04 = value;
        slot->unk3c = 1;
        slot = counts[index];
        slot->unk18.unk00 = 334.0f;
        slot->unk18.unk04 = value;
        slot->unk3c = 1;
        value += 28.0f;
    }
}

/**
 * @brief Create and attach the panel.
 * @param associated Resource source word.
 * @return One.
 */
s32 ItemListPanel::func_slotf4(u32 associated)
{
    LibClass178630* panel;
    FieldClass15AE70::func_slot14(associated, 0, 9, 0x578, 204.0f, 72.0f, 0.0f);
    panel = allocate_panel();
    lib_panel_init_rectangle(panel, 1, 0.0f, 0.0f, 412.0f, 396.0f, 88.0f);
    lib_container_attach_widget(this->unk10, panel);
    return 1;
}

/** @brief Destroy the panel window. */
ItemListPanel::~ItemListPanel()
{
}

/** @brief Restore the selector brightness. */
void ItemCategoryWindow::func_slot64()
{
    set_selector_brightness(selector, 128.0f);
}

/** @brief Handle Back by setting window state one with flag 0x80. @return Two. */
u8 ItemCategoryWindow::func_slotb4()
{
    this->set_state(1, 0x80);
    return 2;
}

/**
 * @brief Enter the type list for the highlighted category.
 * @return Zero while the selector is missing or idle, otherwise one.
 */
u8 ItemCategoryWindow::func_slotb0()
{
    if (selector == 0)
    {
        return 0;
    }

    bool idle = !selector->ItemCreationClass185050::unk35;

    if (idle)
    {
        return 0;
    }

    set_selector_brightness(selector, 64.0f);

    u16 selected = selector->func_0023B3A0();
    type_list->func_slot10c(1, 1);
    type_list->func_slot110(1);

    if (selected == ITEM_CATEGORY_VALUABLES)
    {
        if (controller->control_help_window != 0)
        {
            controller->control_help_window->prompts[0]->unk3f = 0;
        }
    }
    else
    {
        ItemController* owner;
        ItemControlHelpWindow* control_help = controller->control_help_window;

        if (control_help != 0)
        {
            owner = static_cast<ItemController*>(D_001B643C->callbacks->state);
            lib_text_set_resource(control_help->prompts[0], owner->get_resource_slot(), ITEM_MSG_SORT_PROMPT, 0);
            lib_text_set_resource(control_help->prompts[1], owner->get_resource_slot(), ITEM_MSG_BACK_PROMPT, 0);
            lib_text_set_resource(control_help->prompts[2], owner->get_resource_slot(), ITEM_MSG_SELECT_PROMPT, 0);
            control_help->prompts[0]->unk3f = 1;
        }
    }

    if (D_001B643C->runtime != 0)
    {
        D_001B643C->runtime->unk9a = 1;
    }

    D_001B643C->callbacks->state->func_00263C70(type_list);
    return 1;
}

/** @brief Move down a category, then update the highlight, the help line and the type list. */
void ItemCategoryWindow::func_slot6c()
{
    if (selector != 0 && selector->func_0023B3B0(1) != 1)
    {
        u16 selected = selector->func_0023B3A0();
        s16 row = selected;

        if (selector != 0)
        {
            for (s32 index = 0; index < label_count; index++)
            {
                LibObject178750* label = static_cast<LibObject178750*>(unk2c.at(index)->value);

                if (index == row)
                {
                    set_text_color(label, ITEM_COLOR_SELECTED);
                    highlight->func_0023B7E0(label);
                }
                else
                {
                    set_text_color(label, ITEM_COLOR_NORMAL);
                }
            }
        }

        s16 key = selected + ITEM_MSG_CATEGORY_HELP_BASE;
        set_item_window_message(controller->help_window, key);
        type_list->rebuild_list(1, selector->func_0023B3A0());
        type_list->func_slot10c(1, 0);
    }
}

/** @brief Move up a category, then update the highlight, the help line and the type list. */
void ItemCategoryWindow::func_slot68()
{
    if (selector != 0 && selector->func_0023B3B0(0) != 1)
    {
        u16 selected = selector->func_0023B3A0();
        s16 row = selected;

        if (selector != 0)
        {
            for (s32 index = 0; index < label_count; index++)
            {
                LibObject178750* label = static_cast<LibObject178750*>(unk2c.at(index)->value);

                if (index == row)
                {
                    set_text_color(label, ITEM_COLOR_SELECTED);
                    highlight->func_0023B7E0(label);
                }
                else
                {
                    set_text_color(label, ITEM_COLOR_NORMAL);
                }
            }
        }

        s16 key = selected + ITEM_MSG_CATEGORY_HELP_BASE;
        set_item_window_message(controller->help_window, key);
        type_list->rebuild_list(1, selector->func_0023B3A0());
        type_list->func_slot10c(1, 0);
    }
}

/** @brief Publish the highlighted category and hide the Sort prompt while this window is focused. */
void ItemCategoryWindow::func_slot5c()
{
    if (D_001B643C->callbacks->state->func_00261150() == this)
    {
        ItemController* owner = static_cast<ItemController*>(D_001B643C->callbacks->state);
        owner->selected_category = selector->func_0023B3A0();

        if (owner->control_help_window != 0)
        {
            owner->control_help_window->prompts[0]->unk3f = 0;
        }
    }
}

/**
 * @brief Create the panel, the category labels and icons, the selector and its highlight.
 * @param associated Resource source word.
 * @return Zero when the type list window is missing, otherwise one.
 */
s32 ItemCategoryWindow::func_slotf4(u32 associated)
{
    type_list = static_cast<ItemTypeListWindow*>(func_slot4c());

    if (type_list == 0)
    {
        return 0;
    }

    FieldClass15AE70::func_slot14(associated, 0, 9, 0x708, 16.0f, 72.0f, 0.0f);
    LibClass178630* panel = allocate_panel();
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 192.0f, 288.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    label_count = 10;

    for (s32 index = 0; index < label_count; index++)
    {
        LibObject178750* label = allocate_text_widget();
        float y = 16.0f + 26.0f * static_cast<float>(index);
        label->init_resource_rectangle(42.0f, y, 0.0f, 0.0f, associated, index + ITEM_MSG_CATEGORY_NAME_BASE, 0);
        label->unk88 = -1.0f;
        label->unk3c = 1;
        label->set_scale(0.9f, 0.9f);
        lib_container_attach_widget(unk10, label);
        unk2c.append(label);

        ItemCreationOptionResourceDisplay* icon = new (0) ItemCreationOptionResourceDisplay;
        void* allocation = field_get_aligned_allocation(D_001B643C->resources, 14);
        FieldResourceRecord* record = field_find_resource_record(D_001B643C->resources, index + 50);
        icon->unkcc = allocation;
        icon->unkd0 = 14;
        icon->func_002D6440(16.0f, y, record);
        lib_container_attach_widget(unk10, icon);
    }

    selector = new (0) FieldClass153130;
    // TODO: Binding the row top through a reference is the only way I found to get the original's constant order.
    const float& top = 28.0f;
    SelectorColumns columns = SELECTOR_SINGLE_COLUMN;
    selector->func_0023B530(columns, label_count, 1, 0, 1, 20.0f, top, 0.0f, 26.0f);
    lib_container_attach_widget(unk10, selector);

    LibObject178750* first_label = static_cast<LibObject178750*>(unk2c.at(0)->value);
    highlight = new (0) FieldClass153170;
    highlight->func_0023B850(first_label, ITEM_COLOR_SELECTED);
    lib_container_attach_widget(unk10, highlight);

    if (selector != 0)
    {
        for (s32 index = 0; index < label_count; index++)
        {
            LibObject178750* label = static_cast<LibObject178750*>(unk2c.at(index)->value);

            if (index == 0)
            {
                set_text_color(label, ITEM_COLOR_SELECTED);
                highlight->func_0023B7E0(label);
            }
            else
            {
                set_text_color(label, ITEM_COLOR_NORMAL);
            }
        }
    }

    return 1;
}

/** @brief Destroy the window. */
ItemCategoryWindow::~ItemCategoryWindow()
{
}

/** @brief Hold the help line at its start for 120 frames, then scroll it left and wrap. */
void ItemHelpWindow::func_slot5c()
{
    LibObject178750* display = this->text_display;
    float x = display->unk18.unk00;
    float y = display->unk18.unk04;
    float width = display->unk18.unk08;
    float height = display->unk18.unk0c;

    if (this->scrolling == 0)
    {
        set_text_bounds(display, this->start_x, y, width, height);
        this->delay_frames++;

        if (!((float)this->delay_frames <= 120.0f))
        {
            this->delay_frames = 0;
            this->scrolling = 1;
        }

        return;
    }

    float left = this->clip_x;
    x -= 108.0f * D_001B6690;

    if (x < left - (float)this->scroll_extent)
    {
        x = 2.0f + (left + this->clip_width);
    }

    set_text_bounds(display, x, y, width, height);
}

/**
 * @brief Show a help line and restart its hold, for keys in this overlay's help range.
 * @param text_key Message key; only keys 7020 through 7034 are accepted.
 */
void ItemHelpWindow::func_slot60(s32 text_key)
{
    if (text_key >= ITEM_MSG_CATEGORY_HELP_BASE && text_key < ITEM_MSG_HELP_END)
    {
        scrolling = 0;
        delay_frames = 0;
        lib_text_set_resource(text_display, func_slot54(), text_key, 1);
        scroll_extent = (s32)lib_text_measure_bounds(text_display)->unk08 + 6;
    }
}

/**
 * @brief Create the title, the caption and the clipped help line, then show the first line.
 * @param associated Resource source word.
 * @return Zero when a widget couldn't be allocated, otherwise one.
 */
s32 ItemHelpWindow::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot14(associated, 0, 9, 0x578, 16.0f, 16.0f, 0.0f);

    LibObject178750* label = new (0) LibObject178750;
    label->init_resource_rectangle(16.0f, 6.0f, 0.0f, 0.0f, associated, ITEM_MSG_TITLE, 0);
    lib_container_attach_widget(unk10, label);
    unk2c.append(label);

    LibObject178750* caption = new (0) LibObject178750;
    caption->init_resource_rectangle(36.0f, 40.0f, 0.0f, 0.0f, associated, ITEM_MSG_CAPTION, 0);
    caption->set_scale(0.65f, 0.65f);
    lib_container_attach_widget(unk10, caption);
    unk2c.append(caption);

    text_display = new (0) LibObject178750;
    LibClass1746A0* clip = new (0) LibClass1746A0;
    LibClass1746A0* reset = new (0) LibClass1746A0;

    if (text_display == 0 || clip == 0 || reset == 0)
    {
        return 0;
    }

    label_width = lib_text_measure_bounds(label)->unk08;
    clip_x = 18.0f + label_width;
    // TODO: Adding through a const reference is the only way I found to get the original's load order.
    clip_width = 640.0f - (16.0f + shifted_position(clip_x, 32.0f));
    start_x = 24.0f + label_width;
    lib_scissor_init_rectangle(clip, clip_x, 0.0f, clip_width, 56.0f);
    lib_container_attach_widget(unk10, clip);
    unk20.append(clip);

    text_display->init_resource_rectangle(start_x, 6.0f, 0.0f, 0.0f, associated, ITEM_MSG_CATEGORY_HELP_BASE, 0);
    lib_container_attach_widget(unk10, text_display);
    unk2c.append(text_display);

    lib_scissor_init_reset(reset, 1);
    lib_container_attach_widget(unk10, reset);
    unk20.append(reset);

    func_slot60(ITEM_MSG_CATEGORY_HELP_BASE);
    return 1;
}

/** @brief Destroy the window. */
ItemHelpWindow::~ItemHelpWindow()
{
}

/**
 * @brief Create and attach the three tiles.
 * @param associated Resource source word.
 * @return One.
 */
s32 ItemResourceWindow::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot14(associated, 0, 9, 0x4B0, 16.0f, 16.0f, 0.0f);
    left_tile = new (0) ItemCreationOptionResourceDisplay;
    middle_tile = new (0) ItemCreationOptionResourceDisplay;
    right_tile = new (0) ItemCreationOptionResourceDisplay;

    void* allocation = field_get_aligned_allocation(D_001B643C->resources, 11);
    left_tile->unkcc = allocation;
    middle_tile->unkcc = allocation;
    right_tile->unkcc = allocation;
    left_tile->unkd0 = 11;
    middle_tile->unkd0 = 11;
    right_tile->unkd0 = 11;

    left_tile->func_002D6440(0.0f, 0.0f, field_find_resource_record(D_001B643C->resources, 5));
    middle_tile->func_002D6440(256.0f, 0.0f, field_find_resource_record(D_001B643C->resources, 6));
    right_tile->func_002D6440(512.0f, 0.0f, field_find_resource_record(D_001B643C->resources, 7));

    lib_container_attach_widget(unk10, left_tile);
    lib_container_attach_widget(unk10, middle_tile);
    lib_container_attach_widget(unk10, right_tile);
    return 1;
}

/** @brief Destroy the window. */
ItemResourceWindow::~ItemResourceWindow()
{
}

/** @brief Release the loaded resources, detach the controller, and queue its receiver. */
void ItemController::func_slot5c()
{
    if (resource_slot != 0)
    {
        lib_release_resource_slot(D_001B657C, resource_slot);
    }

    lib_object_detach_owner(&static_cast<FieldClass153E30&>(*this));
    func_001DD7B0();
    field_queue_allocation_release(D_001B643C->resources, 14);
}

/** @brief Collect the owned valuables and create the menu windows. @return One. */
s32 ItemController::init_windows()
{
    ItemFlagBlock* flag_block = reinterpret_cast<ItemFlagBlock*>(resident_find_entry(resident_get_entry_table(resident_get_runtime_owner()), 4));

    if (flag_block != 0)
    {
        valuable_count = 0;

        for (s32 index = 0; index < ITEM_VALUABLE_COUNT; index++)
        {
            bool owned = flag_block->is_set(index + ITEM_VALUABLE_FIRST_FLAG);

            if (owned == true)
            {
                valuables[valuable_count++] = index;
            }
        }
    }

    if (unk5c != 1)
    {
        resource_window = new (0) ItemResourceWindow;
        help_window = new (0) ItemHelpWindow;
        category_window = new (0) ItemCategoryWindow(this);
        type_list_window = new (0) ItemTypeListWindow(this);
        control_help_window = new (0) ItemControlHelpWindow;
        list_panel = new (0) ItemListPanel;
        resource_window->func_slotf4(resource_slot);
        FieldClass153E30::add_child(resource_window);
        resource_window->func_slot40(0);
        help_window->func_slotf4(resource_slot);
        FieldClass153E30::add_child(help_window);
        unk24 = help_window;
        help_window->func_slot40(resource_window);
        category_window->func_slot48(type_list_window);
        category_window->func_slotf4(resource_slot);
        FieldClass153E30::add_child(category_window);
        list_panel->func_slotf4(resource_slot);
        FieldClass153E30::add_child(list_panel);
        type_list_window->func_slot40(category_window);
        type_list_window->func_slot104(resource_slot);
        FieldClass153E30::add_child(type_list_window);
        control_help_window->func_slotf4(resource_slot);
        FieldClass153E30::add_child(control_help_window);
        unk20 = category_window;
    }

    windows_initialized = 1;
    return 1;
}

/**
 * @brief Load the completed menu resource and create the windows.
 * @param buffer Completed resource buffer.
 * @return Window creation result, or zero for a null buffer.
 */
s32 ItemController::on_resource_loaded(void* buffer)
{
    if (buffer == 0)
    {
        return 0;
    }

    ItemAlignedResource* resource = aligned_resource(buffer);
    s32 allocation_size = resource->byte_count + 128;
    void* previous_heap = resident_get_allocation_heap();
    void* resource_heap = D_001B6430->context->unk70;
    void* heap_probe = resident_heap_allocate(resource_heap, allocation_size);

    if (heap_probe != 0)
    {
        resident_heap_release(heap_probe);
        resident_exchange_allocation_heap(resource_heap);
    }

    resource_slot = lib_load_resource_slot(D_001B657C, resource);
    resident_exchange_allocation_heap(previous_heap);
    FieldRuntime* runtime = D_001B657C;
    runtime->item_name_resource_slot = resource_slot;
    runtime->item_name_base_key = ITEM_MSG_ITEM_NAME_BASE + 1;
    return init_windows();
}

/**
 * @brief Allocate and populate a missing party selection.
 * @return One after creating and populating the selection; otherwise zero.
 */
u8 ItemController::func_00264110()
{
    u8 created = create_record_selection(this);

    if (created == 0)
    {
        return 0;
    }

    resident_find_entry(resident_get_entry_table(resident_get_runtime_owner()), 4);
    return 1;
}

/** @brief Release the party selection and queue the controller's Field receiver. */
void ItemController::func_001DD7B0()
{
    if (party != 0)
    {
        release_record_selection(party);
    }

    FieldClass153E30* receiver = this;
    resident_enqueue_object(D_001B65F4, receiver);
}

/** @brief Remove the items listed in record_identifiers when requested, then destroy the bases. */
ItemController::~ItemController()
{
    if (remove_flagged_records != 0)
    {
        for (s32 index = 0; index < 5; index++)
        {
            s16 identifier = record_identifiers[index];

            if (identifier != 0)
            {
                func_0040C9F0(D_001B64F8, identifier);
            }
        }
    }
}

/** @brief Initialize the controller's bases and clear its window and selection state. */
ItemController::ItemController()
{
    resource_slot = 0;
    windows_initialized = 0;
    party = 0;
    resource_window = 0;
    help_window = 0;
    category_window = 0;
    type_list_window = 0;
    control_help_window = 0;
    list_panel = 0;
    selected_allocation = 0;
    unk5c = 0;
    // TODO: The original clears this byte twice. My guess is the second one was meant for unk5d.
    unk5c = 0;
    unk5e = 0;
    unka8 = 0;
    remove_flagged_records = 0;

    for (s32 index = 0; index < 5; index++)
    {
        record_identifiers[index] = 0;
    }

    for (s32 index = 0; index < ITEM_VALUABLE_COUNT; index++)
    {
        valuables[index] = 0;
    }
}

/** @brief Leave the default DMA notification hook unchanged. @param value Unused notification value. */
void LibClass171FF0::func_003EFA90(u32 value)
{
}

/** @brief Leave the default DMA completion hook unchanged. @param value Unused notification value. */
void LibClass171FF0::func_003F4410(u32 value)
{
}

/** @brief Report the intrusive object kind. @return Three. */
s32 ItemCoordinateSelector::get_default_list_kind()
{
    return 3;
}

/** @brief Leave the default update hook unchanged. */
void ItemCoordinateSelector::update()
{
}

/** @brief Leave the default notification hook unchanged. */
void ItemCoordinateSelector::func_003EEBE0()
{
}

/** @brief Copy the translation vector and mark the transform dirty. @param value Translation vector. */
void LibClass178A90::func_003EF770(const LibVector4* value)
{
    transform_dirty = 1;
    unk20.packed = value->packed;
}

/** @brief Copy the translation vector and mark the transform dirty. @param value Translation vector. */
void LibClass178A90::func_003EF780(const LibVector4* value)
{
    transform_dirty = 1;
    unk20.packed = value->packed;
}

/** @brief Set the translation coordinates and mark the transform dirty. @param x Horizontal translation. @param y Vertical translation. @param z Third translation component. */
void LibClass178A90::func_003EF790(float x, float y, float z)
{
    transform_dirty = 1;
    unk20.components[0] = x;
    unk20.components[1] = y;
    unk20.components[2] = z;
    unk20.components[3] = 1.0f;
}

/** @brief Set all quaternion components and mark the transform dirty. @param x First component. @param y Second component. @param z Third component. @param w Fourth component. */
void LibClass171EF0::func_003EEED0(float x, float y, float z, float w)
{
    transform_dirty = 1;
    unk30.components[0] = x;
    unk30.components[1] = y;
    unk30.components[2] = z;
    unk30.components[3] = w;
}

/** @brief Copy the quaternion and mark the transform dirty. @param value Quaternion components. */
void LibClass171EF0::func_003EEEF0(const LibVector4* value)
{
    transform_dirty = 1;
    unk30.packed = value->packed;
}

/** @brief Copy the quaternion and mark the transform dirty. @param value Quaternion components. */
void LibClass171EF0::func_003EEF10(const LibVector4* value)
{
    transform_dirty = 1;
    unk30.packed = value->packed;
}

/** @brief Update the rotation state and mark the transform dirty. @param value Rotation components. */
void LibClass171EF0::func_003EEF30(const LibVector4* value)
{
    transform_dirty = 1;
    func_004CE4C0(unk30.components, value->components);
}

/** @brief Update the rotation state and mark the transform dirty. @param value Rotation components. */
void LibClass171EF0::func_003EEF60(const LibVector4* value)
{
    transform_dirty = 1;
    func_004CE4C0(unk30.components, value->components);
}

/** @brief Set the rotation components and mark the transform dirty. @param x First component. @param y Second component. @param z Third component. */
void LibClass171EF0::func_003EEF90(float x, float y, float z)
{
    transform_dirty = 1;
    LibVector4 value;
    value.components[0] = x;
    value.components[1] = y;
    value.components[2] = z;
    value.components[3] = 1.0f;
    func_004CE4C0(unk30.components, value.components);
}

/** @brief Copy the scale vector and mark the transform dirty. @param value Scale vector. */
void LibClass171EF0::func_003EEFD0(const LibVector4* value)
{
    transform_dirty = 1;
    unk40.packed = value->packed;
}

/** @brief Copy the scale vector and mark the transform dirty. @param value Scale vector. */
void LibClass171EF0::func_003EEFF0(const LibVector4* value)
{
    transform_dirty = 1;
    unk40.packed = value->packed;
}

/** @brief Set the scale coordinates and mark the transform dirty. @param x First scale component. @param y Second scale component. @param z Third scale component. */
void LibClass171EF0::func_003EF010(float x, float y, float z)
{
    transform_dirty = 1;
    unk40.components[0] = x;
    unk40.components[1] = y;
    unk40.components[2] = z;
}

/** @brief Return the default output status. @param output Unused output object. @return Zero. */
s32 LibClass178A90::func_003EEE20(void* output)
{
    return 0;
}

/** @brief Test whether the supplied value is negative. @param value Value to test. @param mode Unused mode. @return One if negative, otherwise zero. */
s32 LibClass178A90::func_003EEE30(float value, float mode)
{
    s32 result = 1;

    if (!(value < 0.0f))
    {
        result = 0;
    }

    return result;
}

/** @brief Return the default transform vector. @return Resident vector pointer. */
const LibVector4* LibClass178A90::func_003EFAA0()
{
    return &D_50CD30;
}

/** @brief Return the default transform receiver. @return Null. */
LibClass178A90* LibClass178A90::func_003EEE50()
{
    return 0;
}

/** @brief Leave the default transform release hook unchanged. */
void LibClass178A90::func_003EEE60()
{
}

/** @brief Destroy the positions and the movement base. */
ItemCoordinateSelector::~ItemCoordinateSelector()
{
}

/** @brief Report the transform kind. @return Fourteen. */
s32 ItemHpMpGauge::get_default_list_kind()
{
    return 14;
}

/** @brief Restore the saved transform state. */
void ItemHpMpGauge::func_003F4420()
{
    unk60 = unka8;
}

/** @brief Destroy the window. */
ItemControlHelpWindow::~ItemControlHelpWindow()
{
}

/** @brief Default window update; does nothing. */
void FieldClass15AE70::func_slot5c()
{
}

/** @brief Default window hook; does nothing. */
void FieldClass15AE70::func_slot70()
{
}

/** @brief Default window hook; does nothing. */
void FieldClass15AE70::func_slot74()
{
}

/** @brief Default confirm handler. @return Zero. */
u8 FieldClass15AE70::func_slotb0()
{
    return 0;
}

/** @brief Default back handler. @return Zero. */
u8 FieldClass15AE70::func_slotb4()
{
    return 0;
}

/** @brief Store the pointer at offset 0x24. @param value Pointer to store. */
void FieldClass153E30::func_00263C80(void* value)
{
    unk24 = value;
}

/** @brief Return the pointer at offset 0x24. @return Stored pointer. */
void* FieldClass153E30::func_00263C90()
{
    return unk24;
}

/** @brief Store the signed byte at offset 0x28. @param value Byte to store. */
void FieldClass153E30::func_00263CA0(s8 value)
{
    unk28 = value;
}

/** @brief Return the signed byte at offset 0x28. @return Stored byte. */
s8 FieldClass153E30::func_00263CB0()
{
    return unk28;
}

/** @brief Default receiver hook. @return Zero. */
s32 FieldClass153E30::func_slot60()
{
    return 0;
}

/** @brief Default receiver hook. @return Zero. */
s32 FieldClass153E30::func_slot64()
{
    return 0;
}

/** @brief Default receiver hook; does nothing. */
void FieldClass153E30::func_slot68()
{
}

/** @brief Default receiver hook; does nothing. */
void FieldClass153E30::func_slot70()
{
}

/** @brief Default receiver hook; does nothing. */
void FieldClass153E30::func_slot74()
{
}

/** @brief Default receiver hook; does nothing. */
void FieldClass153E30::func_slot78()
{
}

/** @brief Default receiver hook. @return Zero. */
s32 FieldClass153E30::func_slot7c()
{
    return 0;
}

/** @brief Default receiver hook. @return Zero. */
s32 FieldClass153E30::func_slot80()
{
    return 0;
}

/** @brief Default receiver hook. @return Zero. */
s32 FieldClass153E30::func_slot84()
{
    return 0;
}

/** @brief Report this object's default list kind. @return Four. */
s32 ItemController::get_default_list_kind()
{
    return 4;
}

/** @brief Report whether window setup finished. @return Setup flag. */
u8 ItemController::windows_ready()
{
    return windows_initialized;
}

/** @brief Allocate the sentinel and initialize the empty list. */
ItemGaugeList::ItemGaugeList()
{
    head = new (0) ItemListNode;

    if (head == 0)
    {
        throw;
    }

    head->next = 0;
    count = 0;
}

/** @brief Release the links and sentinel without destroying the gauges. */
ItemGaugeList::~ItemGaugeList()
{
    clear();

    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

/**
 * @brief Add a gauge to the end of the list.
 * @param gauge Gauge stored in the node. The caller owns it.
 */
void ItemGaugeList::append(void* gauge)
{
    ItemListNode* node = (ItemListNode*)func_00100AC0(sizeof(ItemListNode), 0);

    if (node != 0)
    {
        ItemListNode* tail;
        node->value = gauge;
        node->next = 0;
        tail = head;

        while (tail->next != 0)
        {
            tail = tail->next;
        }

        tail->next = node;
        count++;
    }
}

/** @brief Delete the list nodes after the sentinel and reset the list count. */
void ItemGaugeList::clear()
{
    ItemListNode* node = head->next;

    if (node == 0)
    {
        return;
    }

    while (node != 0)
    {
        ItemListNode* next = node->next;
        delete node;
        node = next;
    }

    head->next = 0;
    count = 0;
}

/** @brief Allocate the sentinel and initialize the empty list. */
ItemTypeList::ItemTypeList()
{
    head = new (0) ItemListNode;

    if (head == 0)
    {
        throw;
    }

    head->next = 0;
    count = 0;
}

/** @brief Release the links and sentinel without destroying the records. */
ItemTypeList::~ItemTypeList()
{
    clear();

    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

/**
 * @brief Add an item type record to the end of the list.
 * @param record Item type record.
 */
void ItemTypeList::append(ItemCreationCategoryRecord* record)
{
    ItemListNode* node = (ItemListNode*)func_00100AC0(sizeof(ItemListNode), 0);

    if (node != 0)
    {
        ItemListNode* tail;
        node->value = record;
        node->next = 0;
        tail = head;

        while (tail->next != 0)
        {
            tail = tail->next;
        }

        tail->next = node;
        count++;
    }
}

/** @brief Delete the list nodes after the sentinel and reset the list count. */
void ItemTypeList::clear()
{
    ItemListNode* node = head->next;

    if (node == 0)
    {
        return;
    }

    while (node != 0)
    {
        ItemListNode* next = node->next;
        delete node;
        node = next;
    }

    head->next = 0;
    count = 0;
}

/**
 * @brief Return the node at `index`. Index zero is the first node after the sentinel.
 * @param index Zero-based index among the value nodes.
 * @return The node at that index, or null if the list ends first.
 */
ItemListNode* ItemTypeList::at(s32 index)
{
    ItemListNode* node = head->next;
    s32 step;

    for (step = 0; step < index; step++)
    {
        if (node == 0)
        {
            return 0;
        }

        node = node->next;
    }

    return node;
}

/**
 * @brief Add a node holding `value` to the end of the list.
 * @param value Pointer stored in the node. The caller owns it.
 */
void FieldClass15AFE8::append(void* value)
{
    FieldListNode* node = (FieldListNode*)func_00100AC0(sizeof(FieldListNode), 0);

    if (node != 0)
    {
        FieldListNode* tail;
        node->value = value;
        node->next = 0;
        tail = head;

        while (tail->next != 0)
        {
            tail = tail->next;
        }

        tail->next = node;
        count++;
    }
}

/**
 * @brief Add a node holding `value` to the end of the list.
 * @param value Pointer stored in the node. The caller owns it.
 */
void FieldClass15AF88::append(void* value)
{
    FieldListNode* node = (FieldListNode*)func_00100AC0(sizeof(FieldListNode), 0);

    if (node != 0)
    {
        FieldListNode* tail;
        node->value = value;
        node->next = 0;
        tail = head;

        while (tail->next != 0)
        {
            tail = tail->next;
        }

        tail->next = node;
        count++;
    }
}

/**
 * @brief Return the node at `index`. Index zero is the first node after the sentinel.
 * @param index Zero-based index among the value nodes.
 * @return The node at that index, or null if the list ends first.
 */
FieldListNode* FieldClass15AF88::at(s32 index)
{
    FieldListNode* node = head->next;
    s32 step;

    for (step = 0; step < index; step++)
    {
        if (node == 0)
        {
            return 0;
        }

        node = node->next;
    }

    return node;
}

/**
 * @brief Add a node holding `value` to the end of the list.
 * @param value Pointer stored in the node. The caller owns it.
 */
void FieldClass15AF78::append(void* value)
{
    FieldListNode* node = (FieldListNode*)func_00100AC0(sizeof(FieldListNode), 0);

    if (node != 0)
    {
        FieldListNode* tail;
        node->value = value;
        node->next = 0;
        tail = head;

        while (tail->next != 0)
        {
            tail = tail->next;
        }

        tail->next = node;
        count++;
    }
}

/**
 * @brief Add a node holding `value` to the end of the list.
 * @param value Pointer stored in the node. The caller owns it.
 */
void FieldClass15AF68::append(void* value)
{
    FieldListNode* node = (FieldListNode*)func_00100AC0(sizeof(FieldListNode), 0);

    if (node != 0)
    {
        FieldListNode* tail;
        node->value = value;
        node->next = 0;
        tail = head;

        while (tail->next != 0)
        {
            tail = tail->next;
        }

        tail->next = node;
        count++;
    }
}

/** @brief Release the positions and the sentinel. */
ItemCoordinateList::~ItemCoordinateList()
{
    clear();

    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

/** @brief Delete the position nodes after the sentinel and reset the list count. */
void ItemCoordinateList::clear()
{
    ItemCoordinateNode* node = head->next;

    if (node == 0)
    {
        return;
    }

    while (node != 0)
    {
        ItemCoordinateNode* next = node->next;
        delete node;
        node = next;
    }

    head->next = 0;
    count = 0;
}

/**
 * @brief Add a position to the end of the list.
 * @param position Position to add.
 */
void ItemCoordinateList::append(ItemCoordinate position)
{
    ItemCoordinateNode* node = allocate_coordinate_node();

    if (node != 0)
    {
        ItemCoordinateNode* tail;

        node->x = position.x;
        node->y = position.y;
        node->next = 0;
        tail = head;

        while (tail->next != 0)
        {
            tail = tail->next;
        }

        tail->next = node;
        count++;
    }
}

/** @brief Allocate the sentinel and initialize the empty list. */
ItemCoordinateList::ItemCoordinateList()
{
    head = new (0) ItemCoordinateNode;

    if (head == 0)
    {
        throw;
    }

    head->next = 0;
    count = 0;
}

/**
 * @brief Sort the list by moving links; the payloads and sentinel stay put.
 * @param compare Signed node comparator, returning zero for equal nodes.
 * @param comparison_arg Argument forwarded to each comparator call.
 * @param ascending Nonzero for ascending order, zero for descending order.
 */
void ItemTypeList::sort(ItemListComparator compare, u32 comparison_arg, s32 ascending)
{
    ItemListNode* position = head;
    ItemListNode* previous;

    // Selection sort: find the extreme node after position, then move it to position->next.
    while (position != 0)
    {
        ItemListNode* scan = position->next;
        ItemListNode* selected_previous = position;

        if (scan != 0)
        {
            while (scan != 0)
            {
                s32 result = compare(selected_previous->next, scan, comparison_arg);

                if (ascending != 0)
                {
                    if (result > 0)
                    {
                        selected_previous = previous;
                    }
                }
                else if (result < 0)
                {
                    selected_previous = previous;
                }

                previous = scan;
                scan = scan->next;
            }

            if (selected_previous != position)
            {
                if (selected_previous == position->next)
                {
                    ItemListNode* selected = selected_previous->next;
                    ItemListNode* next = selected->next;
                    position->next = selected;
                    position->next->next = selected_previous;
                    selected_previous->next = next;
                }
                else
                {
                    ItemListNode* first = position->next;
                    ItemListNode* selected = selected_previous->next;
                    ItemListNode* next = selected->next;
                    position->next = selected;
                    position->next->next = first->next;
                    selected_previous->next = first;
                    first->next = next;
                }
            }

            position = position->next;
        }
        else
        {
            break;
        }
    }
}
