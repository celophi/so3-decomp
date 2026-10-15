#include "overlays/cstatus/text.h"
#include "main/resident_data.h"
#include "main/resident_001001E0.h"
#include "main/resident_0010A0E0.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "sdk/main/libc_guess_0013C948.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_0028E240.h"
#include "overlays/1067-00/text_002F9C90.h"
#include "overlays/1067-00/field_runtime.h"
#include "overlays/1067-00/text_001E1590.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_00419A70.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/1067-00/text_002D3BD0.h"
#include "overlays/1067-00/text_002D5260.h"
#include "overlays/lib/text_0044ABE0.h"
#include "overlays/lib/resource_widget_inlines.h"
#include "overlays/lib/marker_widget_inlines.h"
#include "overlays/lib/list_indicator_inlines.h"
#include "overlays/lib/scalar_indicator_inlines.h"
#include "overlays/lib/movement_widget_inlines.h"
#include "overlays/lib/text_003F90C0.h"
#include "overlays/lib/text_004095C0.h"
#include "overlays/lib/item_allocation.h"

#define STATUS_STAT_WORD_XOR_KEY 0x7DE3F7E3
#define STATUS_STAT_HALFWORD_XOR_KEY 0x7E93
#define STATUS_BATTLE_SKILL_XOR_KEY 0x77

/** Message keys from the status resource and shared menu bank. */
enum StatusTextKey
{
    STATUS_TEXT_SLASH = 0x7E7,
    STATUS_TEXT_MINOR_ATTACK_BUTTON = 0x80A,
    STATUS_TEXT_MAJOR_ATTACK_BUTTON = 0x80B,
    STATUS_TEXT_NONE = 0x822,
    STATUS_TEXT_HEADING = 0x1388,
    STATUS_TEXT_CHARACTER_HELP = 0x138A,
    STATUS_TEXT_NAME_HELP = 0x138B,
    STATUS_TEXT_HP = 0x138D,
    STATUS_TEXT_MP = 0x138E,
    STATUS_TEXT_LEVEL = 0x138F,
    STATUS_TEXT_EXPERIENCE = 0x1390,
    STATUS_TEXT_NEXT_LEVEL = 0x1391,
    STATUS_TEXT_ATTACK = 0x1393,
    STATUS_TEXT_DEFENSE = 0x1394,
    STATUS_TEXT_AGILITY = 0x1395,
    STATUS_TEXT_HIT = 0x1396,
    STATUS_TEXT_INTELLIGENCE = 0x1397,
    STATUS_TEXT_MAX_LEVEL = 0x1398,
    STATUS_TEXT_WEAPON = 0x1399,
    STATUS_TEXT_ARMOR = 0x139A,
    STATUS_TEXT_ACCESSORY_1 = 0x139B,
    STATUS_TEXT_ACCESSORY_2 = 0x139C,
    STATUS_TEXT_SKILLS = 0x139D,
    STATUS_TEXT_SP = 0x139E,
    STATUS_TEXT_CP = 0x139F,
    STATUS_TEXT_SHORT_RANGE = 0x13A0,
    STATUS_TEXT_LONG_RANGE = 0x13A1,
    STATUS_TEXT_SUPPORT_1 = 0x13A2,
    STATUS_TEXT_SUPPORT_2 = 0x13A3,
    STATUS_TEXT_HIRAGANA = 0x13A8,
    STATUS_TEXT_KATAKANA = 0x13A9,
    STATUS_TEXT_ALPHANUMERIC = 0x13AA,
    STATUS_TEXT_BACKSPACE = 0x13AB,
    STATUS_TEXT_DEFAULT_NAME = 0x13AC,
    STATUS_TEXT_CANCEL = 0x13AD,
    STATUS_TEXT_CONFIRM = 0x13AE,
    STATUS_TEXT_HIRAGANA_GRID = 0x13AF,
    STATUS_TEXT_HIRAGANA_GRID_TAIL = 0x13B0,
    STATUS_TEXT_HIRAGANA_DIACRITICS = 0x13B1,
    STATUS_TEXT_KATAKANA_GRID = 0x13B2,
    STATUS_TEXT_KATAKANA_GRID_TAIL = 0x13B3,
    STATUS_TEXT_KATAKANA_GRID_SPACE = 0x13B4,
    STATUS_TEXT_DIGIT_GRID_LEFT = 0x13B5,
    STATUS_TEXT_DIGIT_GRID_RIGHT = 0x13B6,
    STATUS_TEXT_LETTER_GRID_LEFT = 0x13B7,
    STATUS_TEXT_LETTER_GRID_RIGHT = 0x13B8,
    STATUS_TEXT_SYMBOL_GRID_LEFT = 0x13B9,
    STATUS_TEXT_SYMBOL_GRID_RIGHT = 0x13BA,
    STATUS_TEXT_CHARACTER_SURNAME_BASE = 0x13BB,
    STATUS_TEXT_NAME_UNDERLINE = 0x13C6,
    STATUS_TEXT_NAME_SHADOW = 0x13C7,
    STATUS_TEXT_BLANK = 0x13C8,
    STATUS_TEXT_STATUS = 0x13C9,
    STATUS_TEXT_MEMBER_HINT = 0x13CA,
    STATUS_TEXT_NAME_HINT = 0x13CB,
    STATUS_TEXT_COLOR_SETUP_HINT = 0x13CC,
    STATUS_TEXT_COLOR_CHANGE_HINT = 0x13CD,
    STATUS_TEXT_HIRAGANA_GLYPH_BASE = 0x157C,
    STATUS_TEXT_KATAKANA_GLYPH_BASE = 0x15E0,
    STATUS_TEXT_ALPHABET_SYMBOL_GRID = 0x16DB,
    STATUS_TEXT_ALPHANUMERIC_GLYPH_BASE = 0x170C,
    STATUS_TEXT_BATTLE_SKILL_BASE = 0x18FF,
};

/** Character modes used by the name-entry grid. */
enum StatusNameGridMode
{
    STATUS_NAME_HIRAGANA = 0,
    STATUS_NAME_KATAKANA = 1,
    STATUS_NAME_ALPHANUMERIC = 2
};

/** Command cells in the name grid's first column, eleven cells per row. */
enum StatusNameCommand
{
    STATUS_NAME_COMMAND_HIRAGANA = 0,
    STATUS_NAME_COMMAND_KATAKANA = 11,
    STATUS_NAME_COMMAND_ALPHANUMERIC = 22,
    STATUS_NAME_COMMAND_BACKSPACE = 33,
    STATUS_NAME_COMMAND_DEFAULT = 44,
    STATUS_NAME_COMMAND_CANCEL = 55,
    STATUS_NAME_COMMAND_UNUSED_ROW_6 = 66,
    STATUS_NAME_COMMAND_UNUSED_ROW_7 = 77,
    STATUS_NAME_COMMAND_CONFIRM = 88
};

/** Ordered grid labels stored at the start of the name window text list. */
enum StatusNameGridLabel
{
    STATUS_NAME_GRID_HIRAGANA_MAIN = 0,
    STATUS_NAME_GRID_HIRAGANA_TAIL = 1,
    STATUS_NAME_GRID_HIRAGANA_DIACRITICS = 2,
    STATUS_NAME_GRID_KATAKANA_MAIN = 3,
    STATUS_NAME_GRID_KATAKANA_TAIL = 4,
    STATUS_NAME_GRID_KATAKANA_SPACE = 5,
    STATUS_NAME_GRID_DIGITS_LEFT = 6,
    STATUS_NAME_GRID_DIGITS_RIGHT = 7,
    STATUS_NAME_GRID_LETTERS_LEFT = 8,
    STATUS_NAME_GRID_LETTERS_RIGHT = 9,
    STATUS_NAME_GRID_SYMBOLS_LEFT = 10,
    STATUS_NAME_GRID_SYMBOLS_RIGHT = 11,
    STATUS_NAME_GRID_LABEL_COUNT = 12
};

/** Windows selected by the status receiver. */
enum StatusWindowKind
{
    STATUS_WINDOW_CHARACTER = 0,
    STATUS_WINDOW_NAME = 1
};

/** Outgoing and incoming effects bracket the active-window change. */
enum StatusWindowTransitionPhase
{
    STATUS_TRANSITION_IDLE = 0,
    STATUS_TRANSITION_START = 1,
    STATUS_TRANSITION_SWITCH_WINDOW = 2,
    STATUS_TRANSITION_FINISH = 3
};

/** Bytes used by saved names; kana diacritics modify the preceding character. */
enum StatusNameByte
{
    STATUS_NAME_SPACE = 0x20,
    STATUS_NAME_HIRAGANA_DELIMITER = 0x7E,
    STATUS_NAME_DAKUTEN = 0xDE,
    STATUS_NAME_HANDAKUTEN = 0xDF
};

/** Checksum-protected 0xC4-byte character statistics. */
struct StatusCharacterRecord
{
    s16 character_id;
    /** Selects the clamping rules used by the character stat setters. */
    s16 stat_limit_type;
    s16 encoded_level;
    s16 encoded_base_level;
    s32 encoded_flags;
    s32 encoded_experience;
    s32 encoded_base_hp;
    s32 encoded_max_hp;
    s32 encoded_hp;
    s32 encoded_base_mp;
    s32 encoded_max_mp;
    s32 encoded_mp;
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
    /** The resident INT helpers validate these values through the HIT checksum. */
    s32 encoded_base_intelligence;
    s32 encoded_effective_intelligence;
    s32 encoded_intelligence;
    s16 encoded_base_knockback_power;
    s16 encoded_effective_knockback_power;
    s16 encoded_knockback_power;
    s16 encoded_base_knockback_resistance;
    s16 encoded_effective_knockback_resistance;
    s16 encoded_knockback_resistance;
    s16 encoded_base_critical_rate;
    s16 encoded_effective_critical_rate;
    s16 encoded_critical_rate;
    s32 level_checksum;
    s32 flags_experience_checksum;
    s32 hp_checksum;
    s32 mp_checksum;
    s32 attack_checksum;
    s32 defense_checksum;
    s32 agility_checksum;
    s32 hit_checksum;
    s32 knockback_power_checksum;
    s32 checksum_salt;
    s32 critical_rate_checksum;
    s32 knockback_resistance_checksum;
    s32 unkb4[3];
    s32 unkc0;

    /** @brief Decode current HP, marking valid flags when the HP checksum fails. @return Current HP, or zero for corruption. */
    u32 get_hp()
    {
        u32 value = encoded_hp;
        if (hp_checksum != ((encoded_base_hp + encoded_max_hp) ^ encoded_hp ^ checksum_salt))
        {
            u32 flags = encoded_flags;
            s32 flag_salt = encoded_experience;
            if (flags_experience_checksum == ((flags + checksum_salt) ^ flag_salt ^ checksum_salt))
            {
                encoded_flags = ((flags ^ STATUS_STAT_WORD_XOR_KEY) | 1) ^ STATUS_STAT_WORD_XOR_KEY;
                s32 current_key = checksum_salt;
                flags = encoded_flags;
                s32 current_experience = encoded_experience;
                flags_experience_checksum = current_key ^ (current_experience ^ (flags + current_key));
            }
            return 0;
        }
        return value ^ STATUS_STAT_WORD_XOR_KEY;
    }
    /** @brief Decode maximum HP, marking valid flags when the HP checksum fails. @return Maximum HP, or zero for corruption. */
    u32 get_max_hp()
    {
        u32 value = encoded_max_hp;
        if (hp_checksum != ((encoded_base_hp + encoded_max_hp) ^ encoded_hp ^ checksum_salt))
        {
            u32 flags = encoded_flags;
            s32 flag_salt = encoded_experience;
            if (flags_experience_checksum == ((flags + checksum_salt) ^ flag_salt ^ checksum_salt))
            {
                encoded_flags = ((flags ^ STATUS_STAT_WORD_XOR_KEY) | 1) ^ STATUS_STAT_WORD_XOR_KEY;
                s32 current_key = checksum_salt;
                flags = encoded_flags;
                s32 current_experience = encoded_experience;
                flags_experience_checksum = current_key ^ (current_experience ^ (flags + current_key));
            }
            return 0;
        }
        return value ^ STATUS_STAT_WORD_XOR_KEY;
    }
    /** @brief Decode current MP, marking valid flags when the MP checksum fails. @return Current MP, or zero for corruption. */
    u32 get_mp()
    {
        u32 value = encoded_mp;
        if (mp_checksum != ((encoded_base_mp + encoded_max_mp) ^ encoded_mp ^ checksum_salt))
        {
            u32 flags = encoded_flags;
            s32 flag_salt = encoded_experience;
            if (flags_experience_checksum == ((flags + checksum_salt) ^ flag_salt ^ checksum_salt))
            {
                encoded_flags = ((flags ^ STATUS_STAT_WORD_XOR_KEY) | 1) ^ STATUS_STAT_WORD_XOR_KEY;
                s32 current_key = checksum_salt;
                flags = encoded_flags;
                s32 current_experience = encoded_experience;
                flags_experience_checksum = current_key ^ (current_experience ^ (flags + current_key));
            }
            return 0;
        }
        return value ^ STATUS_STAT_WORD_XOR_KEY;
    }
    /** @brief Decode maximum MP, marking valid flags when the MP checksum fails. @return Maximum MP, or zero for corruption. */
    u32 get_max_mp()
    {
        u32 value = encoded_max_mp;
        if (mp_checksum != ((encoded_base_mp + encoded_max_mp) ^ encoded_mp ^ checksum_salt))
        {
            u32 flags = encoded_flags;
            s32 flag_salt = encoded_experience;
            if (flags_experience_checksum == ((flags + checksum_salt) ^ flag_salt ^ checksum_salt))
            {
                encoded_flags = ((flags ^ STATUS_STAT_WORD_XOR_KEY) | 1) ^ STATUS_STAT_WORD_XOR_KEY;
                s32 current_key = checksum_salt;
                flags = encoded_flags;
                s32 current_experience = encoded_experience;
                flags_experience_checksum = current_key ^ (current_experience ^ (flags + current_key));
            }
            return 0;
        }
        return value ^ STATUS_STAT_WORD_XOR_KEY;
    }
    /** @brief Decode the protected level. @return Level, or one for an invalid checksum. */
    s32 get_level() const
    {
        if (level_checksum != (checksum_salt ^ (encoded_level ^ (encoded_base_level + checksum_salt))))
        {
            return 1;
        }
        return encoded_level ^ STATUS_STAT_HALFWORD_XOR_KEY;
    }
    /** @brief Decode the protected experience. @return Experience, or zero for an invalid checksum. */
    s32 get_experience() const
    {
        if (flags_experience_checksum != (checksum_salt ^ (encoded_experience ^ (encoded_flags + checksum_salt))))
        {
            return 0;
        }
        return encoded_experience ^ STATUS_STAT_WORD_XOR_KEY;
    }
    /** @brief Decode the protected attack value. @return Attack, or zero for an invalid checksum. */
    s32 get_attack() const
    {
        if (attack_checksum != (checksum_salt ^ (encoded_attack ^ (encoded_base_attack + encoded_effective_attack))))
        {
            return 0;
        }
        return encoded_attack ^ STATUS_STAT_WORD_XOR_KEY;
    }
    /** @brief Decode the protected defense value. @return Defense, or zero for an invalid checksum. */
    s32 get_defense() const
    {
        if (defense_checksum != (checksum_salt ^ (encoded_defense ^ (encoded_base_defense + encoded_effective_defense))))
        {
            return 0;
        }
        return encoded_defense ^ STATUS_STAT_WORD_XOR_KEY;
    }
    /** @brief Decode the protected agility value. @return Agility, or zero for an invalid checksum. */
    s32 get_agility() const
    {
        if (agility_checksum != (checksum_salt ^ (encoded_agility ^ (encoded_base_agility + encoded_effective_agility))))
        {
            return 0;
        }
        return encoded_agility ^ STATUS_STAT_WORD_XOR_KEY;
    }
    /** @brief Decode the protected HIT value. @return HIT, or zero for an invalid checksum. */
    s32 get_hit() const
    {
        if (hit_checksum != (checksum_salt ^ (encoded_hit ^ (encoded_base_hit + encoded_effective_hit))))
        {
            return 0;
        }
        return encoded_hit ^ STATUS_STAT_WORD_XOR_KEY;
    }
    /** @brief Decode INT after validating the HIT checksum. @return INT, or zero when the HIT checksum is invalid. */
    s32 get_intelligence() const
    {
        if (hit_checksum != (checksum_salt ^ (encoded_hit ^ (encoded_base_hit + encoded_effective_hit))))
        {
            return 0;
        }
        return encoded_intelligence ^ STATUS_STAT_WORD_XOR_KEY;
    }
};

/** Opaque 0x508-byte table initialized by the Lib experience-table constructor. */
struct StatusExperienceTable
{
    u8 unknown[0x508];
    /** @brief Initialize the experience table and its encoded table offset. */
    StatusExperienceTable();
};
/** @brief Persistent status flags from save section four. */
struct StatusFlagsSection
{
    u8 unknown[0x22];
    u8 flags;
};

/** Checksum-protected 0x114-byte character equipment and skill data. */
struct StatusCharacterEquipment
{
    s16 encoded_base_luck;
    s16 encoded_effective_luck;
    s16 encoded_luck;
    s16 encoded_base_stamina;
    s16 encoded_effective_stamina;
    s16 encoded_stamina;
    s16 encoded_equipment_slot_count;
    s16 encoded_slot_limit;
    s16 encoded_equipment_ids[4];
    s16 encoded_sp;
    s16 encoded_cp;
    u8 unk1c[4];
    char character_name[24];
    u8 battle_strategy;
    /** Strategy saved when the tactics selection window opens. */
    u8 previous_battle_strategy;
    u8 unk3a;
    u8 encoded_anti_attack_aura_mask;
    u8 encoded_status_skill_levels[5];
    u8 encoded_battle_skill_indices[6];
    u8 encoded_tactical_skill_states[7];
    s16 encoded_symbology_mastery[32];
    s16 encoded_battle_skill_mastery[42];
    /** Damage responses in earth, water, fire, wind order. */
    u8 elemental_damage_responses[4];
    u8 attack_element_mask;
    /** Variant index used with character-specific resource groups. */
    u8 character_resource_variant;
    u32 luck_checksum;
    u32 stamina_checksum;
    u32 equipment_checksum;
    u32 sp_cp_checksum;
    u32 symbology_mastery_checksum;
    u32 battle_skill_mastery_checksum;
    u32 tactical_skill_states_checksum;
    u32 battle_skill_indices_checksum;
    u32 status_skill_levels_checksum;
    u32 checksum_salt;
    u32 unk110;
    /** @brief Decode a protected equipment allocation ID. @param index Signed equipment slot index. @return Allocation ID, or zero for an invalid checksum or index. */
    s16 get_allocation_id(s32 index) const
    {
        if (equipment_checksum != (checksum_salt ^ ((encoded_equipment_ids[1] + encoded_equipment_ids[2]) ^ (encoded_equipment_ids[3] + encoded_equipment_ids[0]))))
        {
            return 0;
        }
        if (index < 0)
        {
            return 0;
        }
        if ((encoded_slot_limit ^ STATUS_STAT_HALFWORD_XOR_KEY) < index)
        {
            return 0;
        }
        return encoded_equipment_ids[index] ^ STATUS_STAT_HALFWORD_XOR_KEY;
    }
    /** @brief Decode protected SP. @return SP, or zero for an invalid checksum. */
    s32 get_sp() const
    {
        s32 salt = checksum_salt;
        s16 value = encoded_sp;
        if (sp_cp_checksum != (salt ^ (value ^ (encoded_cp + salt))))
        {
            return 0;
        }
        return value ^ STATUS_STAT_HALFWORD_XOR_KEY;
    }
    /** @brief Decode protected CP. @return CP, or zero for an invalid checksum. */
    s32 get_cp() const
    {
        s32 salt = checksum_salt;
        s16 value = encoded_cp;
        if (sp_cp_checksum != (salt ^ (encoded_sp ^ (value + salt))))
        {
            return 0;
        }
        return value ^ STATUS_STAT_HALFWORD_XOR_KEY;
    }
};

/** Saved section containing the ten fixed-width character names. */
struct StatusNameSection
{
    u8 unk00[0xC6B0];
    s8 names[10][24];
};
/** Typed display payload and forward link in a status list. */
struct StatusDisplayNode
{
    LibClass178600* value;
    StatusDisplayNode* next;
};

/** Saved section flag selecting the nested status display geometry. */
struct StatusWindowSection
{
    u8 unk00[0x18C];
    u8 enabled;
};

/** Partial saved section containing variant limits and their checksum. */
struct StatusVariantSection
{
    u8 unk00[0x1A0];
    u8 values[4];
    u16 checksum;
    u16 seed;
};

/** Resource descriptor with its signed size at offset 0x40. */
struct StatusAlignedResource
{
    u8 unk00[0x40];
    s32 size;
};
/** Partial Field runtime containing the active resource and request code. */
struct StatusRuntimeResource
{
    u8 unk00[0x514];
    s32 resource;
    u32 code;
};
/** Status resource receiver with its resident vtable at 0x188CC0. */
struct StatusResourceState : public FieldClass153E30
{
    /** @brief Initialize the resource handle, selection, and transition state. */
    StatusResourceState();
    /** @brief Destroy the owned record selection and the Field receiver base. */
    virtual ~StatusResourceState();
    /** @brief Report the status receiver type. @return Four. */
    virtual s32 func_001DF3D0();
    /** @brief Submit this receiver to the resident object queue. */
    virtual void func_001DD7B0();
    /** @brief Switch between record and name windows through a timed transition. */
    virtual void func_001DF360();
    /** @brief Leave the status receiver unchanged. */
    virtual void func_001DD410();
    /** @brief Report the receiver state. @return One. */
    virtual u8 func_00264110();
    /** @brief Set the active window. @param value Window pointer to store. */
    virtual void func_00263C70(void* value);
    /** @brief Get the active window. @return Stored window pointer. */
    virtual void* func_00261150();
    /** @brief Set the text window. @param value Window pointer to store. */
    virtual void func_00263C80(void* value);
    /** @brief Get the text window. @return Stored text window pointer. */
    virtual void* func_00263C90();
    /** @brief Set the receiver byte. @param value Signed byte to store. */
    virtual void func_00263CA0(s8 value);
    /** @brief Get the receiver byte. @return Stored signed byte. */
    virtual s8 func_00263CB0();
    /** @brief Get the loaded resource handle. @return Resource handle. */
    virtual u32 func_00263CC0();
    /** @brief Report whether window setup finished. @return Setup flag. */
    virtual u8 func_00261D20();
    /**
     * @brief Load the completed status resource and finish receiver setup.
     * @param buffer Completed resource buffer, or null.
     * @return Zero without a buffer, otherwise the receiver setup result.
     */
    virtual s32 func_001E1820(void* buffer);
    /**
     * @brief Create and attach the status windows and record selection.
     * @return One after setup succeeds, or zero otherwise.
     */
    virtual s32 func_00263CD0();
    /** @brief Release the status resource, queue this receiver, and clear its allocation slots. */
    virtual void func_slot5c();
    /** @brief Report the default command result. @return Zero. */
    virtual s32 func_slot60();
    /** @brief Report the default command result. @return Zero. */
    virtual s32 func_slot64();
    /** @brief Leave the resource state unchanged. */
    virtual void func_slot68();
    /** @brief Get the record selection. @return Owned record selection. */
    virtual FieldRecordSelection* selected_records();
    /** @brief Default receiver callback with no action. */
    virtual void func_slot70();
    /** @brief Default receiver callback with no action. */
    virtual void func_slot74();
    /** @brief Default receiver callback with no action. */
    virtual void func_slot78();
    /** @brief Default receiver callback returning zero. @return Zero. */
    virtual s32 func_slot7c();
    /** @brief Default receiver callback returning zero. @return Zero. */
    virtual s32 func_slot80();
    /** @brief Default receiver callback returning zero. @return Zero. */
    virtual s32 func_slot84();
    s32 resource;
    u8 setup_complete : 1;
    u8 unknown_38 : 7;
    u8 unknown_39[3];
    FieldRecordSelection* selection;
    u16 requested_window;
    u16 transition_phase;
    StatusCharacterWindow* character_window;
};

/** Partial effect with transition value and display mode. */
struct StatusTransitionEffect
{
    u8 unk00[0xC0];
    s32 value;
    u8 unkc4[0x2C];
    u8 mode;
};
/** Partial Field context receiver holding the active transition effect. */
struct StatusTransitionOwner
{
    u8 unk00[0x5A4];
    StatusTransitionEffect* effect;
};
extern "C" void* func_0020F230(ResidentContextObject38* state, u32 index, u32 first, u32 second, s32 mode, u32 third, u32 flags, float duration, float x, float y);
extern "C" s32 func_0022A160(void* object);
extern "C" void func_004DCEA0(void* object, s32 enabled, s32 other);
extern "C" void* D_001B6650;
extern "C" s32 D_001B6694;

struct StatusRuntimeCallbacks;

/** Partial resident runtime view used by this overlay. */
struct StatusRuntime
{
    u8 unk00[0xC];
    void* menu_controller;
    StatusRuntimeCallbacks* callbacks;
    u8 unk14[8];
    void* model_camera;
    FieldBufferSlots* slots;
};

/** Partial resident callback state used by status transitions. */
struct StatusRuntimeCallbacks
{
    u8 unk00[0x14];
    StatusResourceState* status_receiver;
    u8 unk18[0x48];
    u8 input_enabled;
};

typedef struct StatusWidgetNode
{
    void* value;
    struct StatusWidgetNode* next;
    /** @brief Release the link without destroying its payload. */
    ~StatusWidgetNode()
    {
    }
} StatusWidgetNode;

struct StatusWidgetList
{
    StatusWidgetNode* head;
    s32 count;
    void* methods;
};

extern StatusRuntime* D_001B643C;
extern "C" s32 func_002CFE40(void* object, s16 index);

extern "C" void* func_100AC0(s32 size, s32 flags);

/** @brief Apply an allocation to character statistics and equipment. */
extern "C" s32 func_003F9890(StatusCharacterRecord*, StatusCharacterEquipment*, ItemCreationAllocationRecord*, s32);
/** @brief Compute the experience remaining for the requested level and optionally return its threshold. */
extern "C" s32 func_004028C0(StatusExperienceTable*, s32, StatusCharacterRecord*, s32*);
extern "C" ItemCreationAllocationRecord* D_001B64F8;

/**
 * @brief Read an assigned battle-skill index when its checksum is valid.
 * @param record Character equipment containing the battle-skill assignments.
 * @param index Signed entry index, from zero through five.
 * @return Decoded entry, or zero for an invalid checksum or index.
 */
static inline s32 status_battle_skill_index(StatusCharacterEquipment* record, s32 index)
{
    u32 checksum = 0x8D3C43F9;
    for (s32 entry = 0; entry < 6; entry++)
    {
        checksum ^= record->encoded_battle_skill_indices[entry];
        checksum = checksum * 2 + 0x31;
    }
    if (record->battle_skill_indices_checksum != checksum)
    {
        return 0;
    }
    if (index < 0)
    {
        return 0;
    }
    if (static_cast<u32>(index) >= 6)
    {
        return 0;
    }
    return record->encoded_battle_skill_indices[index] ^ STATUS_BATTLE_SKILL_XOR_KEY;
}

/**
 * @brief Set a caption rectangle and mark it for refresh.
 * @param target Caption widget.
 * @param x Horizontal origin.
 * @param y Vertical origin.
 * @param width Caption width.
 * @param height Caption height.
 */
static inline void set_status_record_rectangle(LibObject178750* target, float x, float y, float width, float height)
{
    target->unk18.unk00 = x;
    target->unk18.unk04 = y;
    target->unk18.unk08 = width;
    target->unk18.unk0c = height;
    target->unk3c = 1;
}

/**
 * @brief Initialize a resource display.
 * @param display Resource display to initialize.
 * @param record Resource record to display.
 * @param x Horizontal position.
 * @param y Vertical position.
 */
static inline void initialize_status_resource(ItemCreationOptionResourceDisplay* display, FieldResourceRecord* record, float x, float y)
{
    func_002D6440(display, record, x, y);
}

/** @brief Set widget coordinates and request refresh. @param widget Display widget. @param x Horizontal coordinate. @param y Vertical coordinate. */
static inline void set_status_widget_position(LibClass178600* widget, float x, float y)
{
    widget->unk18.unk00 = x;
    widget->unk18.unk04 = y;
    widget->unk3c = 1;
}

/** @brief Move each non-null display by the current scroll delta. @param list Display list to move. @param object Window supplying the delta. */
template <class List>
static inline void move_status_display_list(List* list, StatusCharacterWindow* object)
{
    StatusWidgetNode* node = list->head->next;
    while (node != 0)
    {
        LibClass178600* widget = static_cast<LibClass178600*>(node->value);
        if (widget != 0)
        {
            set_status_widget_position(widget, widget->unk18.unk00,
                                       widget->unk18.unk04 + object->scroll_delta);
        }
        node = node->next;
    }
}

/** @brief Set resource display scales and request refresh. @param display Resource display. @param x Horizontal scale. @param y Vertical scale. */
static inline void set_status_resource_scale(LibClass175110* display, float x, float y)
{
    display->unk50.unk34 = y;
    display->unk50.unk30 = x;
    display->unk3c = 1;
}

/** @brief Align a resource descriptor to 128 bytes. @param buffer Raw resource buffer. @return Aligned resource descriptor. */
static inline StatusAlignedResource* aligned_status_resource(void* buffer)
{
    return reinterpret_cast<StatusAlignedResource*>((reinterpret_cast<u32>(buffer) + 0x7F) & ~0x7F);
}

/** @brief Restore the character window after a selection command. @param object Selection window to detach. */
static inline void close_status_selection(StatusNameWindow* object)
{
    StatusResourceState* target = D_001B643C->callbacks->status_receiver;
    target->remove_child(object);
    target->requested_window = STATUS_WINDOW_CHARACTER;
    target->character_window->func_slot20(0);
    target->func_00263C70(target->character_window);
    target->transition_phase = STATUS_TRANSITION_START;
    D_001B643C->callbacks->input_enabled = 0;
}

/** @brief Set vertical glyph spacing and request refresh. @param label Text widget. @param value Vertical spacing. */
static inline void set_label_spacing_y(LibObject178750* label, float value)
{
    label->unk8c = value;
    label->unk3c = 1;
}

/** @brief Get the current character record. @param selection Current record selection. @return Selected character record. */
static inline StatusCharacterRecord* status_character(FieldRecordSelection* selection)
{
    return &reinterpret_cast<StatusCharacterRecord*>(selection->records)[selection->current];
}

/** @brief Get the signed current record index. @param selection Current record selection. @return Signed record index. */
static inline s8 status_selected_index(FieldRecordSelection* selection)
{
    return selection->current;
}

/** @brief Get the character-record table. @param selection Current record selection. @return Record table. */
static inline FieldRecord* status_record_table(FieldRecordSelection* selection)
{
    return selection->records;
}

/** @brief Get the current character equipment. @param selection Current record selection. @return Selected equipment record. */
static inline StatusCharacterEquipment* status_equipment(FieldRecordSelection* selection)
{
    return &static_cast<StatusCharacterEquipment*>(selection->unk04)[selection->current];
}

/** @brief Update a numeric display and mark it dirty. @param widget Numeric display. @param value Display value. */
static inline void status_set_numeric(LibObject174F20* widget, u32 value)
{
    widget->numeric_value = value;
    widget->unk3c = 1;
}

/** @brief Find a one-based item allocation. @param index Signed allocation ID. @return Allocation record, or null outside one through three thousand. */
static inline ItemCreationAllocationRecord* status_allocation(s16 index)
{
    ItemCreationAllocationRecord* base = D_001B64F8;
    u8 valid = index >= 1 && index <= 3000;
    if (valid)
    {
        return &base[index - 1];
    }
    return 0;
}

/** @brief Update an equipment display and mark it dirty. @param widget Equipment display. @param item Display item code. @param modification Item modification number. */
static inline void status_set_item(LibObject172410* widget, u16 item, u8 modification)
{
    widget->unkfc = item;
    widget->unkfe = modification;
    widget->unk3c = 1;
}

/** @brief Set text spacing and mark the widget dirty. @param widget Text widget. @param spacing Character spacing. */
static inline void status_set_spacing(LibClass174EF0* widget, float spacing)
{
    widget->unk88 = spacing;
    widget->unk3c = 1;
}

/** @brief Set a divider color and mark the widget dirty. @param widget Divider widget. @param color Packed color. */
static inline void status_set_marker_color(ItemCreationClass172870* widget, u32 color)
{
    widget->unk50 = color;
    widget->unk3c = 1;
}

/** @brief Set the item display flag and mark the widget dirty. @param widget Item widget. @param flag Display flag. */
static inline void status_set_item_flag(LibObject172410* widget, u8 flag)
{
    widget->unkfa = flag;
    widget->unk3c = 1;
}

/** @brief Find a stat row position. @param origin First row position. @param row Row index. @return Row position. */
static inline float status_row_y(float origin, s32 row)
{
    return origin + 24.0f * static_cast<float>(row);
}

/**
 * @brief Destroy an owned object and clear its pointer.
 * @param pointer Owned pointer to release and clear.
 */
template <class T>
static inline void status_delete_owned(T*& pointer)
{
    if (pointer != 0)
    {
        delete pointer;
        pointer = 0;
    }
}

/** @brief Store the inherited window state field. @param value Value to store. */
void FieldClass15AE70::func_slot24(u8 value)
{
    unk0c = value;
}

/** @brief Read the inherited window state field. @return Stored value. */
u8 FieldClass15AE70::func_slot28()
{
    return unk0c;
}

/** @brief Store the inherited window state field. @param value Value to store. */
void FieldClass15AE70::func_slot2c(u8 value)
{
    unk08 = value;
}

/** @brief Read the inherited window state field. @return Stored value. */
u8 FieldClass15AE70::func_slot30()
{
    return unk08;
}

/** @brief Store the inherited window state field. @param value Value to store. */
void FieldClass15AE70::func_slot34(u16 value)
{
    unk0a = value;
}

/** @brief Read the inherited window state field. @return Stored value. */
u16 FieldClass15AE70::func_slot38()
{
    return unk0a;
}

/** @brief Store the inherited window state field. @param value Value to store. */
void FieldClass15AE70::func_slot48(void* value)
{
    unk9c = value;
}

/** @brief Read the inherited window state field. @return Stored value. */
void* FieldClass15AE70::func_slot4c()
{
    return unk9c;
}

/** @brief Store the inherited window state field. @param value Value to store. */
void FieldClass15AE70::func_slot50(u32 value)
{
    unk04 = value;
}

/** @brief Read the inherited window state field. @return Stored value. */
u32 FieldClass15AE70::func_slot54()
{
    return unk04;
}

/** @brief Read the inherited window container. @return Stored value. */
LibObject178660* FieldClass15AE70::func_slot58()
{
    return unk10;
}

/** @brief Default window callback with no action. @param text_key Unused message key. */
void FieldClass15AE70::func_slot60(s32 text_key)
{
}

/** @brief Default window callback with no action. */
void FieldClass15AE70::func_slot64()
{
}

/** @brief Default window callback with no action. */
void FieldClass15AE70::func_slot70()
{
}

/** @brief Default window callback with no action. */
void FieldClass15AE70::func_slot74()
{
}

/** @brief Default window callback with no action. */
void FieldClass15AE70::func_slot78()
{
}

/** @brief Default window callback with no action. */
void FieldClass15AE70::func_slot7c()
{
}

/** @brief Default window callback with no action. */
void FieldClass15AE70::func_slot80()
{
}

/** @brief Default window callback with no action. */
void FieldClass15AE70::func_slot84()
{
}

/** @brief Default window callback with no action. */
void FieldClass15AE70::func_slot88()
{
}

/** @brief Default window callback with no action. */
void FieldClass15AE70::func_slot8c()
{
}

/** @brief Default window callback with no action. */
void FieldClass15AE70::func_slot90()
{
}

/** @brief Default window callback with no action. */
void FieldClass15AE70::func_slot94()
{
}

/** @brief Default window callback with no action. */
void FieldClass15AE70::func_slot98()
{
}

/** @brief Default window callback with no action. */
void FieldClass15AE70::func_slot9c()
{
}

/** @brief Default window callback with no action. */
void FieldClass15AE70::func_slota0()
{
}

/** @brief Default window callback with no action. */
void FieldClass15AE70::func_slota4()
{
}

/** @brief Default window callback with no action. */
void FieldClass15AE70::func_slota8()
{
}

/** @brief Default window callback with no action. */
void FieldClass15AE70::func_slotac()
{
}

/** @brief Default window callback returning zero. @return Zero. */
u8 FieldClass15AE70::func_slotb8()
{
    return 0;
}

/** @brief Default window callback returning zero. @return Zero. */
u8 FieldClass15AE70::func_slotbc()
{
    return 0;
}

/** @brief Default window callback returning zero. @return Zero. */
s32 FieldClass15AE70::func_slotc0()
{
    return 0;
}

/** @brief Default window callback returning zero. @return Zero. */
s32 FieldClass15AE70::func_slotc4()
{
    return 0;
}

/** @brief Default window callback returning zero. @return Zero. */
s32 FieldClass15AE70::func_slotc8()
{
    return 0;
}

/** @brief Default window callback returning zero. @return Zero. */
s32 FieldClass15AE70::func_slotcc()
{
    return 0;
}

/** @brief Default window callback returning zero. @return Zero. */
s32 FieldClass15AE70::func_slotd0()
{
    return 0;
}

/** @brief Default window callback returning zero. @return Zero. */
s32 FieldClass15AE70::func_slotd4()
{
    return 0;
}

/** @brief Default window callback returning zero. @return Zero. */
s32 FieldClass15AE70::func_slotd8()
{
    return 0;
}

/** @brief Default window callback returning zero. @return Zero. */
s32 FieldClass15AE70::func_slotdc()
{
    return 0;
}

/** @brief Default window callback with no action. */
void FieldClass15AE70::func_slote0()
{
}

/** @brief Default window callback with no action. */
void FieldClass15AE70::func_slote4()
{
}

/** @brief Read the inherited window state field. @return Stored value. */
u8 FieldClass15AE70::func_slote8()
{
    return unk0d;
}

/** @brief Store the inherited window state field. @param value Value to store. */
void FieldClass15AE70::func_slotec(u8 value)
{
    unk0d = value;
}

/** @brief Default window callback with no action. */
void FieldClass15AE70::func_slotf0()
{
}

/** @brief Get the active window. @return Stored window pointer. */
void* StatusResourceState::func_00261150()
{
    return unk20;
}

/** @brief Set the active window. @param value Window pointer to store. */
void StatusResourceState::func_00263C70(void* value)
{
    unk20 = value;
}

void status_initialize_name_maps(StatusNameWindow* object)
{
    func_0013A678(object->hiragana_bytes, 0, 90);
    func_0013A678(object->katakana_bytes, 0, 90);
    func_0013A678(object->alphanumeric_bytes, 0, 80);
    StatusGlyphMap90 first = g_status_hiragana_bytes;
    for (s32 i = 0; i < 90; ++i)
    {
        object->hiragana_bytes[i] = first.values[i];
    }
    StatusGlyphMap90 second = g_status_katakana_bytes;
    for (s32 i = 0; i < 90; ++i)
    {
        object->katakana_bytes[i] = second.values[i];
    }
    StatusGlyphMap80 third = g_status_alphanumeric_bytes;
    for (s32 i = 0; i < 80; ++i)
    {
        object->alphanumeric_bytes[i] = third.values[i];
    }
}

void status_append_name_diacritic(StatusNameWindow* object, s16 code)
{
    if (object->grid_mode == STATUS_NAME_HIRAGANA)
    {
        if ((code >= 15 && code <= 24) || (code >= 40 && code <= 44) || (code >= 60 && code <= 64))
        {
            object->name_bytes[object->last_name_byte++] = STATUS_NAME_DAKUTEN;
        }
        if (code >= 25 && code <= 29)
        {
            object->name_bytes[object->last_name_byte++] = STATUS_NAME_HANDAKUTEN;
        }
    }
    else if (object->grid_mode == STATUS_NAME_KATAKANA)
    {
        if ((code >= 15 && code <= 24) || (code >= 40 && code <= 44) || (code >= 60 && code <= 64))
        {
            ++object->last_name_byte;
            object->name_bytes[object->last_name_byte] = STATUS_NAME_DAKUTEN;
        }
        if (code >= 25 && code <= 29)
        {
            ++object->last_name_byte;
            object->name_bytes[object->last_name_byte] = STATUS_NAME_HANDAKUTEN;
        }
        if (code == 75)
        {
            ++object->last_name_byte;
            object->name_bytes[object->last_name_byte] = STATUS_NAME_DAKUTEN;
        }
    }
}

s32 status_remove_last_name_entry(StatusNameWindow* object)
{
    if (object->last_name_byte < 0)
    {
        return 3;
    }
    u8 removed_hiragana_delimiter = 0;
    while (1)
    {
        u8* entry = &object->name_bytes[object->last_name_byte];
        if (*entry == STATUS_NAME_HIRAGANA_DELIMITER)
        {
            *entry = 0;
            removed_hiragana_delimiter = 1;
            object->last_name_byte--;
            continue;
        }
        if (*entry == STATUS_NAME_DAKUTEN)
        {
            *entry = 0;
            object->last_name_byte--;
            continue;
        }
        if (*entry == STATUS_NAME_HANDAKUTEN)
        {
            *entry = 0;
            object->last_name_byte--;
            continue;
        }
        break;
    }
    object->name_bytes[object->last_name_byte] = 0;
    object->last_name_byte--;
    if (removed_hiragana_delimiter == 1)
    {
        if (object->name_bytes[object->last_name_byte] == STATUS_NAME_HIRAGANA_DELIMITER)
        {
            object->name_bytes[object->last_name_byte] = 0;
            object->last_name_byte--;
        }
        else
        {
            object->last_name_byte++;
            object->name_bytes[object->last_name_byte] = STATUS_NAME_HIRAGANA_DELIMITER;
        }
    }
    status_refresh_name_markers(object);
    status_refresh_name_glyphs(object);
    return 2;
}

void status_refresh_name_markers(StatusNameWindow* object)
{
    object->selected_name_glyph = func_004679B0(object->name_text);
    for (s32 i = object->first_name_marker; i < object->first_name_marker + 7; ++i)
    {
        StatusDisplayNode* node = static_cast<StatusDisplayNode*>(status_list_node_at(&object->unk2c, i));
        LibClass178600* marker = node->value;
        marker->unk3f = 0;
        if (i == object->first_name_marker + object->selected_name_glyph)
        {
            marker->unk3f = 1;
        }
    }
    if (object->selected_name_glyph >= 6)
    {
        StatusDisplayNode* node = static_cast<StatusDisplayNode*>(status_list_node_at(&object->unk2c, object->first_name_marker + 6));
        node->value->unk3f = 1;
    }
    if (object->selected_name_glyph <= 0)
    {
        StatusDisplayNode* node = static_cast<StatusDisplayNode*>(status_list_node_at(&object->unk2c, object->first_name_marker));
        node->value->unk3f = 1;
    }
}

void status_refresh_name_glyphs(StatusNameWindow* object)
{
    s32 empty = object->name_bytes[0] == 0;
    if (empty == 0)
    {
        LibObject175140* text = object->name_text;
        text->unkfc = reinterpret_cast<const char*>(object->name_bytes);
        text->unk3c = 1;
        object->name_text->unk3f = 0;
    }
    status_decode_name_glyphs(object);
    for (s32 i = 0; i < 7; ++i)
    {
        object->name_glyph_widgets[i]->unk3f = 0;
    }
    for (s32 i = 0; i < 7; ++i)
    {
        u16 key = object->name_glyph_keys[i];
        if (key != 0)
        {
            u32 source = object->func_slot54();
            lib_text_set_resource(object->name_glyph_widgets[i], source, key, 0);
            object->name_glyph_widgets[i]->unk3f = 1;
        }
        else
        {
            u32 source = object->func_slot54();
            lib_text_set_resource(object->name_glyph_widgets[i], source, STATUS_TEXT_BLANK, 0);
            object->name_glyph_widgets[i]->unk3f = 1;
        }
    }
}

void status_decode_name_glyphs(StatusNameWindow* object)
{
    for (s32 i = 0; i < 7; ++i)
    {
        object->name_glyph_keys[i] = 0;
    }
    u16 position = 0;
    u16 output = 0;
    u8 alternate = 0;
    for (;;)
    {
        if (position >= 24 || output >= 8)
        {
            break;
        }
        u8 value = object->name_bytes[position];
        if (value == 0)
        {
            break;
        }
        if (value == STATUS_NAME_HIRAGANA_DELIMITER)
        {
            alternate = alternate != 1;
            ++position;
            continue;
        }
        if (value == STATUS_NAME_DAKUTEN)
        {
            u16* destination = object->name_glyph_keys + output;
            u16& previous = destination[-1];
            if (previous == 0x15E2)
            {
                previous += 0x49;
            }
            else
            {
                previous += 10;
            }
        }
        else if (value == STATUS_NAME_HANDAKUTEN)
        {
            object->name_glyph_keys[output - 1] += 20;
        }
        else if (value == STATUS_NAME_SPACE)
        {
            object->name_glyph_keys[output++] = STATUS_TEXT_BLANK;
        }
        else if (alternate == 1)
        {
            for (s32 i = 0; i < 90; ++i)
            {
                if (value == object->hiragana_bytes[i])
                {
                    object->name_glyph_keys[output++] = i + STATUS_TEXT_HIRAGANA_GLYPH_BASE;
                    break;
                }
            }
        }
        else
        {
            for (s32 i = 0; i < 90; ++i)
            {
                if (value == object->katakana_bytes[i])
                {
                    object->name_glyph_keys[output++] = i + STATUS_TEXT_KATAKANA_GLYPH_BASE;
                    break;
                }
            }
            for (s32 i = 0; i < 80; ++i)
            {
                if (value == object->alphanumeric_bytes[i])
                {
                    object->name_glyph_keys[output++] = i + STATUS_TEXT_ALPHANUMERIC_GLYPH_BASE;
                    break;
                }
            }
        }
        ++position;
    }
}

void status_append_selected_name_glyph(StatusNameWindow* object, u8 mode)
{
    if (object->last_name_byte < 24)
    {
        u8 full = func_004679B0(object->name_text) >= 7;
        if (full == 1)
        {
            return;
        }
        ++object->last_name_byte;
        s16 code = object->selected_grid_cell % 11 + 10 * (object->selected_grid_cell / 11) - 1;
        if (object->grid_mode == STATUS_NAME_HIRAGANA)
        {
            if (object->last_name_byte > 0 && object->name_bytes[object->last_name_byte - 1] == STATUS_NAME_HIRAGANA_DELIMITER)
            {
                --object->last_name_byte;
                object->name_bytes[object->last_name_byte++] = object->hiragana_bytes[code];
                status_append_name_diacritic(object, code);
                object->name_bytes[object->last_name_byte] = STATUS_NAME_HIRAGANA_DELIMITER;
            }
            else
            {
                object->name_bytes[object->last_name_byte++] = STATUS_NAME_HIRAGANA_DELIMITER;
                object->name_bytes[object->last_name_byte++] = object->hiragana_bytes[code];
                status_append_name_diacritic(object, code);
                object->name_bytes[object->last_name_byte] = STATUS_NAME_HIRAGANA_DELIMITER;
            }
        }
        else if (object->grid_mode == STATUS_NAME_KATAKANA)
        {
            object->name_bytes[object->last_name_byte] = object->katakana_bytes[code];
            status_append_name_diacritic(object, code);
        }
        else
        {
            if (code >= 80)
            {
                object->name_bytes[object->last_name_byte] = STATUS_NAME_SPACE;
            }
            else
            {
                object->name_bytes[object->last_name_byte] = object->alphanumeric_bytes[code];
            }
        }
        status_refresh_name_markers(object);
        status_refresh_name_glyphs(object);
    }
}

extern "C" void status_select_alphanumeric_grid(StatusNameWindow* object, u8 mode)
{
    object->grid_mode = STATUS_NAME_ALPHANUMERIC;
    for (s32 i = 0; i < STATUS_NAME_GRID_LABEL_COUNT; ++i)
    {
        StatusDisplayNode* node = static_cast<StatusDisplayNode*>(status_list_node_at(&object->unk2c, i));
        LibClass178600* display = node->value;
        display->unk3f = 0;
        switch (object->grid_mode)
        {
        case STATUS_NAME_HIRAGANA:
            switch (i)
            {
            case STATUS_NAME_GRID_HIRAGANA_MAIN:
            case STATUS_NAME_GRID_HIRAGANA_TAIL:
            case STATUS_NAME_GRID_HIRAGANA_DIACRITICS:
                display->unk3f = 1;
                break;
            }
            break;
        case STATUS_NAME_KATAKANA:
            switch (i)
            {
            case STATUS_NAME_GRID_KATAKANA_MAIN:
                display->unk3f = 1;
                break;
            case STATUS_NAME_GRID_KATAKANA_TAIL:
            case STATUS_NAME_GRID_KATAKANA_SPACE:
                display->unk3f = 0;
                break;
            }
            break;
        case STATUS_NAME_ALPHANUMERIC:
            switch (i)
            {
            case STATUS_NAME_GRID_DIGITS_LEFT:
            case STATUS_NAME_GRID_DIGITS_RIGHT:
            case STATUS_NAME_GRID_LETTERS_LEFT:
            case STATUS_NAME_GRID_LETTERS_RIGHT:
            case STATUS_NAME_GRID_SYMBOLS_LEFT:
            case STATUS_NAME_GRID_SYMBOLS_RIGHT:
                display->unk3f = 1;
                if (object->alphabet_symbol_grid != 0)
                {
                    object->alphabet_symbol_grid->unk3f = 1;
                }
                break;
            }
            break;
        }
    }
}

void StatusNameWindow::func_slot5c()
{
    FieldClass153E30* receiver = D_001B643C->callbacks->status_receiver;
    if (receiver->func_00261150() == this)
    {
        if (this->selected_name_glyph < 0)
        {
            this->selected_name_glyph = 0;
        }
        if (this->selected_name_glyph >= 6)
        {
            this->selected_name_glyph = 6;
        }
        LibClass178600* name_cursor = this->name_cursor;
        float cursor_x = this->name_x + 36.0f * this->selected_name_glyph;
        float cursor_y = this->name_y;
        name_cursor->unk18.unk00 = cursor_x;
        name_cursor->unk18.unk04 = cursor_y;
        name_cursor->unk3c = 1;
    }
}

void status_move_name_grid_cursor(StatusNameWindow* object, s32 value)
{
    LibClass175030* marker = object->grid_marker;
    LibMovementState& movement = *marker;
    if (movement.unk35 != 0)
    {
        if (value < 0)
        {
            value = 98;
        }
        if (value > 98)
        {
            value = 0;
        }
        s32 row = value / 11;
        s32 column = value % 11;
        float x;
        if (column == 0)
        {
            x = object->command_x - 6.0f;
        }
        else if (column < 6)
        {
            x = (155.0f + 34.0f * column) - 4.0f;
        }
        else
        {
            x = 48.0f + (155.0f + 34.0f * column);
        }
        func_00466E40(&movement, x, 16.0f + (110.0f + 28.0f * row), 1.0f / 15.0f);
        object->selected_grid_cell = value;
        func_002CFE40(D_001B643C->callbacks, 0);
    }
}

void StatusNameWindow::func_slot74()
{
    s32 value = this->selected_grid_cell;
    s32 quotient = value / 11;
    s32 remainder = value % 11;
    if (remainder == 10)
    {
        status_move_name_grid_cursor(this, quotient * 11);
    }
    else
    {
        status_move_name_grid_cursor(this, value + 1);
    }
}

void StatusNameWindow::func_slot70()
{
    s32 value = this->selected_grid_cell;
    s32 quotient = value / 11;
    s32 remainder = value % 11;
    if (remainder == 0)
    {
        status_move_name_grid_cursor(this, quotient * 11 + 10);
    }
    else
    {
        status_move_name_grid_cursor(this, value - 1);
    }
}

void StatusNameWindow::func_slot6c()
{
    s32 value = this->selected_grid_cell;
    if (value / 11 == 8)
    {
        status_move_name_grid_cursor(this, value % 11);
    }
    else
    {
        status_move_name_grid_cursor(this, value + 11);
    }
}

void StatusNameWindow::func_slot68()
{
    s32 value = this->selected_grid_cell;
    if (value / 11 == 0)
    {
        status_move_name_grid_cursor(this, value % 11 + 88);
    }
    else
    {
        status_move_name_grid_cursor(this, value - 11);
    }
}

void StatusNameWindow::func_slote4()
{
    s8* row = this->default_names[this->selection->slots[this->selection->current] - 1];
    for (s32 i = 0; i < 24; ++i)
    {
        this->name_bytes[i] = 0;
    }
    for (s32 i = 0; i < 24; ++i)
    {
        s8 value = row[i];
        if (value == 0)
        {
            break;
        }
        this->name_bytes[i] = value;
    }
    this->last_name_byte = 0;
    s8 last;
    for (;;)
    {
        last = this->last_name_byte;
        if (this->name_bytes[last] == 0)
        {
            break;
        }
        this->last_name_byte = last + 1;
    }
    if (last > 0)
    {
        this->last_name_byte = last - 1;
    }
    status_refresh_name_markers(this);
    status_refresh_name_glyphs(this);
    func_002CFE40(D_001B643C->callbacks, 1);
}

void StatusNameWindow::func_slote0()
{
    status_move_name_grid_cursor(this, STATUS_NAME_COMMAND_CONFIRM);
}

s32 StatusNameWindow::func_slotc4()
{
    return 0;
}

s32 StatusNameWindow::func_slotc0()
{
    return 0;
}

u8 StatusNameWindow::func_slotb4()
{
    status_remove_last_name_entry(this);
    return 2;
}

u8 StatusNameWindow::func_slotb0()
{
    u8 result = 0;
    switch (selected_grid_cell)
    {
    case STATUS_NAME_COMMAND_HIRAGANA:
    case STATUS_NAME_COMMAND_KATAKANA:
    case STATUS_NAME_COMMAND_ALPHANUMERIC:
        return 0;
    case STATUS_NAME_COMMAND_BACKSPACE:
        result = status_remove_last_name_entry(this);
        break;
    case STATUS_NAME_COMMAND_DEFAULT:
    {
        s8* row = default_names[selection->slots[selection->current] - 1];
        for (s32 i = 0; i < 24; ++i)
        {
            name_bytes[i] = 0;
        }
        for (s32 i = 0; i < 24; ++i)
        {
            s8 value = row[i];
            if (value == 0)
            {
                break;
            }
            name_bytes[i] = value;
        }
        last_name_byte = 0;
        s8 last;
        for (;;)
        {
            last = last_name_byte;
            if (name_bytes[last] == 0)
            {
                break;
            }
            last_name_byte = last + 1;
        }
        if (last > 0)
        {
            last_name_byte = last - 1;
        }
        status_refresh_name_markers(this);
        status_refresh_name_glyphs(this);
        break;
    }
    case STATUS_NAME_COMMAND_CANCEL:
        close_status_selection(this);
        return 2;
    case STATUS_NAME_COMMAND_UNUSED_ROW_6:
    case STATUS_NAME_COMMAND_UNUSED_ROW_7:
        return 0;
    case STATUS_NAME_COMMAND_CONFIRM:
    {
        u8 empty = name_bytes[0] == 0;
        if (empty == 1)
        {
            return 3;
        }
        u8 blank = 1;
        for (s32 i = 0; i < 24; ++i)
        {
            u8 value = name_bytes[i];
            if (value != STATUS_NAME_SPACE && value != 0 && value != STATUS_NAME_HIRAGANA_DELIMITER)
            {
                blank = 0;
            }
        }
        if (blank == 0)
        {
            s8* destination = reinterpret_cast<s8*>(static_cast<StatusCharacterEquipment*>(selection->unk04)[selection->current].character_name);
            const s8* source = reinterpret_cast<const s8*>(name_bytes);
            do
            {
            } while ((*destination++ = *source++) != 0);
            StatusNameSection* section = static_cast<StatusNameSection*>(func_101440(func_101290(func_10D8E0()), 4));
            func_0013A4C0(section->names[selection->slots[selection->current] - 1], name_bytes, 24);
            close_status_selection(this);
        }
        else
        {
            return 3;
        }
        break;
    }
    default:
        u8 full = func_004679B0(name_text) >= 7;
        if (full)
        {
            return 3;
        }
        status_append_selected_name_glyph(this, grid_mode);
        break;
    }
    u8 status;
    if (result == 0)
    {
        status = 1;
    }
    else
    {
        status = 2;
    }
    return status;
}

s32 StatusNameWindow::func_slotf4(void* associated)
{
    selection = D_001B643C->callbacks->status_receiver->selected_records();
    selected_character_id = selection->slots[selection->current];
    FieldClass15AE70::func_slot10(reinterpret_cast<u32>(associated), 16.0f, 72.0f, 16);
    LibClass178630* panel = new (0) LibClass178630;
    lib_panel_init_rectangle(panel, 0, 0.0f, 110.0f, 608.0f, 268.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    for (s32 index = 0; index < STATUS_NAME_GRID_LABEL_COUNT; index++)
    {
        LibObject178750* label = new (0) LibObject178750;
        if (label == 0)
        {
            return 0;
        }
        switch (index)
        {
        case STATUS_NAME_GRID_HIRAGANA_MAIN:
            lib_text_init_resource_rectangle(label, reinterpret_cast<s32>(associated), STATUS_TEXT_HIRAGANA_GRID, 0, 184.0f, 118.0f, 0.0f, 0.0f);
            status_set_spacing(label, 10.0f);
            set_label_spacing_y(label, 4.0f);
            break;
        case STATUS_NAME_GRID_HIRAGANA_TAIL:
            lib_text_init_resource_rectangle(label, reinterpret_cast<s32>(associated), STATUS_TEXT_HIRAGANA_GRID_TAIL, 0, 406.0f, 230.0f, 0.0f, 0.0f);
            status_set_spacing(label, 44.0f);
            set_label_spacing_y(label, 32.0f);
            break;
        case STATUS_NAME_GRID_HIRAGANA_DIACRITICS:
            lib_text_init_resource_rectangle(label, reinterpret_cast<s32>(associated), STATUS_TEXT_HIRAGANA_DIACRITICS, 0, 542.0f, 314.0f, 0.0f, 0.0f);
            break;
        case STATUS_NAME_GRID_KATAKANA_MAIN:
            lib_text_init_resource_rectangle(label, reinterpret_cast<s32>(associated), STATUS_TEXT_KATAKANA_GRID, 0, 184.0f, 118.0f, 0.0f, 0.0f);
            status_set_spacing(label, 10.0f);
            set_label_spacing_y(label, 4.0f);
            label->unk3f = 0;
            break;
        case STATUS_NAME_GRID_KATAKANA_TAIL:
            lib_text_init_resource_rectangle(label, reinterpret_cast<s32>(associated), STATUS_TEXT_KATAKANA_GRID_TAIL, 0, 406.0f, 230.0f, 0.0f, 0.0f);
            status_set_spacing(label, 44.0f);
            set_label_spacing_y(label, 32.0f);
            label->unk3f = 0;
            break;
        case STATUS_NAME_GRID_KATAKANA_SPACE:
            lib_text_init_resource_rectangle(label, reinterpret_cast<s32>(associated), STATUS_TEXT_KATAKANA_GRID_SPACE, 0, 406.0f, 314.0f, 0.0f, 0.0f);
            status_set_spacing(label, 112.0f);
            label->unk3f = 0;
            break;
        case STATUS_NAME_GRID_DIGITS_LEFT:
            lib_text_init_resource_rectangle(label, reinterpret_cast<s32>(associated), STATUS_TEXT_DIGIT_GRID_LEFT, 0, 184.0f, 118.0f, 0.0f, 0.0f);
            status_set_spacing(label, 22.0f);
            set_label_spacing_y(label, 4.0f);
            label->unk3f = 0;
            break;
        case STATUS_NAME_GRID_DIGITS_RIGHT:
            lib_text_init_resource_rectangle(label, reinterpret_cast<s32>(associated), STATUS_TEXT_DIGIT_GRID_RIGHT, 0, 406.0f, 118.0f, 0.0f, 0.0f);
            status_set_spacing(label, 22.0f);
            set_label_spacing_y(label, 4.0f);
            label->unk3f = 0;
            break;
        case STATUS_NAME_GRID_LETTERS_LEFT:
            lib_text_init_resource_rectangle(label, reinterpret_cast<s32>(associated), STATUS_TEXT_LETTER_GRID_LEFT, 0, 184.0f, 146.0f, 0.0f, 0.0f);
            status_set_spacing(label, 18.0f);
            set_label_spacing_y(label, 4.0f);
            label->unk3f = 0;
            break;
        case STATUS_NAME_GRID_LETTERS_RIGHT:
            lib_text_init_resource_rectangle(label, reinterpret_cast<s32>(associated), STATUS_TEXT_LETTER_GRID_RIGHT, 0, 406.0f, 146.0f, 0.0f, 0.0f);
            status_set_spacing(label, 18.0f);
            set_label_spacing_y(label, 4.0f);
            label->unk3f = 0;
            break;
        case STATUS_NAME_GRID_SYMBOLS_LEFT:
            lib_text_init_resource_rectangle(label, reinterpret_cast<s32>(associated), STATUS_TEXT_SYMBOL_GRID_LEFT, 0, 184.0f, 230.0f, 0.0f, 0.0f);
            status_set_spacing(label, 26.0f);
            set_label_spacing_y(label, 4.0f);
            label->unk3f = 0;
            break;
        case STATUS_NAME_GRID_SYMBOLS_RIGHT:
            lib_text_init_resource_rectangle(label, reinterpret_cast<s32>(associated), STATUS_TEXT_SYMBOL_GRID_RIGHT, 0, 406.0f, 230.0f, 0.0f, 0.0f);
            status_set_spacing(label, 26.0f);
            set_label_spacing_y(label, 4.0f);
            label->unk3f = 0;
            break;
        }
        lib_container_attach_widget(unk10, label);
        status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&unk2c), label);
        if (0 <= index && index < 6)
        {
            label->unk3d = 0;
        }
        if (8 <= index && index < STATUS_NAME_GRID_LABEL_COUNT)
        {
            label->unk3d = 0;
        }
    }
    alphabet_symbol_grid = new (0) LibObject178750;
    lib_text_init_resource_rectangle(alphabet_symbol_grid, reinterpret_cast<s32>(associated), STATUS_TEXT_ALPHABET_SYMBOL_GRID, 0, 184.0f, 146.0f, 0.0f, 0.0f);
    set_label_spacing_y(alphabet_symbol_grid, 4.0f);
    alphabet_symbol_grid->unk3f = 0;
    lib_container_attach_widget(unk10, alphabet_symbol_grid);
    command_x = 32.0f;
    row_height = 28.0f;
    glyph_scale = 0.86f;
    glyph_width = 24.0f * glyph_scale;
    for (s32 index = 0; index < 6; index++)
    {
        command_labels[index] = new (0) LibObject178750;
        lib_text_init_resource_rectangle(command_labels[index], reinterpret_cast<s32>(associated), index + STATUS_TEXT_HIRAGANA, 1,
                                         command_x, 9.0f + (110.0f + row_height * index), 0.0f, 0.0f);
        LibObject178750* label = command_labels[index];
        label->set_scale(glyph_scale, glyph_scale);
        lib_container_attach_widget(unk10, command_labels[index]);
        status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&unk2c), command_labels[index]);
        if (0 <= index && index < 3)
        {
            command_labels[index]->unk3d = 0;
        }
    }
    command_labels[6] = new (0) LibObject178750;
    lib_text_init_resource_rectangle(command_labels[6], reinterpret_cast<s32>(associated), STATUS_TEXT_CONFIRM, 1, command_x, 334.0f, 0.0f, 0.0f);
    command_labels[6]->set_scale(0.9f, 0.9f);
    lib_container_attach_widget(unk10, command_labels[6]);
    status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&unk2c), command_labels[6]);
    panel = new (0) LibClass178630;
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 608.0f, 110.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    surname_caption = new (0) LibObject178750;
    lib_text_init_resource_rectangle(surname_caption, reinterpret_cast<s32>(associated), selection->slots[selection->current] + STATUS_TEXT_CHARACTER_SURNAME_BASE, 0,
                                     404.0f, 43.0f, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, surname_caption);
    status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&unk2c), surname_caption);
    for (s32 index = 0; index < 7; index++)
    {
        LibObject178750* marker = new (0) LibObject178750;
        lib_text_init_resource_rectangle(marker, reinterpret_cast<s32>(associated), STATUS_TEXT_NAME_UNDERLINE, 0,
                                         (152.0f + 36.0f * index) - 2.0f, 57.0f, 0.0f, 0.0f);
        if (first_name_marker == 0)
        {
            first_name_marker = unk2c.unk04;
        }
        lib_container_attach_widget(unk10, marker);
        status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&unk2c), marker);
        marker->set_color(0x288080);
        marker->set_scale(1.2f, 1.2f);
        marker->unk80 = 3.6f;
        marker->unk3c = 1;
    }
    for (s32 index = 0; index < 7; index++)
    {
        LibObject178750* marker = new (0) LibObject178750;
        lib_text_init_resource_rectangle(marker, reinterpret_cast<s32>(associated), STATUS_TEXT_NAME_SHADOW, 0, 152.0f + 36.0f * index, 59.0f, 0.0f, 0.0f);
        marker->unk80 = 1.8f;
        marker->unk3c = 1;
        lib_container_attach_widget(unk10, marker);
        status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&unk2c), marker);
        marker->set_color(0x505050);
    }
    name_x = 152.0f;
    name_y = 43.0f;
    for (s32 index = 0; index < 7; index++)
    {
        name_glyph_widgets[index] = new (0) LibObject178750;
        lib_text_init_resource_rectangle(name_glyph_widgets[index], reinterpret_cast<s32>(associated), STATUS_TEXT_BLANK, 0, name_x + 36.0f * index, name_y, 0.0f, 0.0f);
        lib_container_attach_widget(unk10, name_glyph_widgets[index]);
        status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&unk2c), name_glyph_widgets[index]);
        name_glyph_widgets[index]->unk3f = 0;
    }
    name_text = new (0) LibObject175140;
    const char* name = static_cast<StatusCharacterEquipment*>(selection->unk04)[selection->current].character_name;
    name_text->func_00467AD0(name_x, name_y, 0.0f, 0.0f, name, 0);
    lib_container_attach_widget(unk10, name_text);
    status_append_name_widget(reinterpret_cast<StatusWidgetList*>(&unk44), name_text);
    status_set_spacing(name_text, 8.0f);
    name_cursor = new (0) ItemCreationClass172600;
    func_0041AD10(static_cast<ItemCreationClass172600*>(name_cursor), name_x + 36.0f * selected_name_glyph, name_y, 24.0f, 24.0f);
    lib_container_attach_widget(unk10, name_cursor);
    portrait_resource_slot = selection->slots[selection->current];
    portrait = new (0) ItemCreationOptionResourceDisplay;
    void* allocation = func_002D3D80(D_001B643C->slots, portrait_resource_slot);
    FieldResourceRecord* resource = static_cast<FieldResourceRecord*>(func_002D3EB0(D_001B643C->slots, portrait_resource_slot));
    portrait->unkcc = allocation;
    portrait->unkd0 = portrait_resource_slot;
    portrait->func_002D6440(resource, 40.0f, 15.0f);
    lib_container_attach_widget(unk10, portrait);
    portrait->unk34 = 3;
    grid_marker = new (0) LibClass175030;
    lib_moving_widget_init_position(grid_marker, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, grid_marker);
    grid_marker->func_00466E40(command_x - 6.0f, 214.0f, 0.1f);
    status_select_alphanumeric_grid(this, grid_mode);
    lib_text_set_resource(surname_caption, func_slot54(), selection->slots[selection->current] + STATUS_TEXT_CHARACTER_SURNAME_BASE, 0);
    const s8* saved = reinterpret_cast<const s8*>(static_cast<StatusCharacterEquipment*>(selection->unk04)[selection->current].character_name);
    for (s32 index = 0; index < 24; index++)
    {
        name_bytes[index] = 0;
    }
    for (s32 index = 0; index < 24; index++)
    {
        s8 value = saved[index];
        if (value == 0)
        {
            break;
        }
        name_bytes[index] = value;
    }
    last_name_byte = 0;
    s8 last;
    for (;;)
    {
        last = last_name_byte;
        if (name_bytes[last] == 0)
        {
            break;
        }
        last_name_byte = last + 1;
    }
    if (last > 0)
    {
        last_name_byte = last - 1;
    }
    status_refresh_name_glyphs(this);
    status_refresh_name_markers(this);
    return 1;
}

ItemCreationClass175110::~ItemCreationClass175110()
{
}

StatusNameWindow::StatusNameWindow()
{
    selection = 0;
    surname_caption = 0;
    name_text = 0;
    name_glyph_widgets[0] = 0;
    name_glyph_widgets[1] = 0;
    name_glyph_widgets[2] = 0;
    name_glyph_widgets[3] = 0;
    name_glyph_widgets[4] = 0;
    name_glyph_widgets[5] = 0;
    name_glyph_widgets[6] = 0;
    first_name_marker = 0;
    selected_name_glyph = 0;
    last_name_byte = 0;
    for (s32 i = 0; i < 24; ++i)
    {
        name_bytes[i] = 0;
    }
    name_glyph_keys[0] = 0;
    name_glyph_keys[1] = 0;
    name_glyph_keys[2] = 0;
    name_glyph_keys[3] = 0;
    name_glyph_keys[4] = 0;
    name_glyph_keys[5] = 0;
    name_glyph_keys[6] = 0;
    status_initialize_name_maps(this);
    name_cursor = 0;
    name_x = 0;
    name_y = 0;
    selected_character_id = 0;
    command_x = 0;
    row_height = 0;
    glyph_scale = 0;
    glyph_width = 0;
    func_0013C948(reinterpret_cast<char*>(default_names[0]), g_status_default_fayt_name);
    func_0013C948(reinterpret_cast<char*>(default_names[1]), g_status_default_sophia_name);
    func_0013C948(reinterpret_cast<char*>(default_names[2]), g_status_default_maria_name);
    func_0013C948(reinterpret_cast<char*>(default_names[3]), g_status_default_cliff_name);
    func_0013C948(reinterpret_cast<char*>(default_names[4]), g_status_default_nel_name);
    func_0013C948(reinterpret_cast<char*>(default_names[5]), g_status_default_albel_name);
    func_0013C948(reinterpret_cast<char*>(default_names[6]), g_status_default_roger_name);
    func_0013C948(reinterpret_cast<char*>(default_names[7]), g_status_default_peppita_name);
    func_0013C948(reinterpret_cast<char*>(default_names[8]), g_status_default_adray_name);
    func_0013C948(reinterpret_cast<char*>(default_names[9]), g_status_default_mirage_name);
    portrait = 0;
    portrait_resource_slot = 0;
    selected_grid_cell = STATUS_NAME_COMMAND_BACKSPACE;
    grid_mode = STATUS_NAME_ALPHANUMERIC;
    alphabet_symbol_grid = 0;
}

void status_update_scroll(StatusCharacterWindow* object)
{
    if (object->scroll_active == 0)
    {
        return;
    }
    if (object->scroll_active == 1)
    {
        move_status_display_list(&object->text_widgets, object);
        move_status_display_list(&object->numeric_widgets, object);
        move_status_display_list(&object->item_widgets, object);
        object->scroll_timer += 1.0f;
        if (object->scroll_timer >= 4.0f)
        {
            object->scroll_active = 0;
        }
        if (object->scroll_delta >= 0.0f)
        {
            object->scroll_position -= object->scroll_extent / 4.0f;
        }
        else
        {
            object->scroll_position += object->scroll_extent / 4.0f;
        }
        LibClass1725D0* marker = object->scroll_marker;
        marker->unk54 = object->scroll_position;
        marker->unk3c = 1;
    }
}

void status_begin_scroll(StatusCharacterWindow* object, u16 scroll_page)
{
    if (object->scroll_active == 0 && (scroll_page != 0 || object->scroll_page != 0) && (scroll_page != 1 || object->scroll_page != 1))
    {
        object->scroll_page++;
        if (object->scroll_page >= 2)
        {
            object->scroll_page = 0;
        }
        if (scroll_page == 0)
        {
            object->scroll_delta = object->scroll_step;
        }
        else if (scroll_page == 1)
        {
            object->scroll_delta = -object->scroll_step;
        }
        if (object->scroll_active == 0)
        {
            object->scroll_active = 1;
            object->scroll_timer = 0.0f;
        }
        func_002CFE40(D_001B643C->callbacks, 0);
    }
}

void StatusCharacterWindow::func_slot6c()
{
    status_begin_scroll(this, 1);
}

void StatusCharacterWindow::func_slot68()
{
    status_begin_scroll(this, 0);
}

/**
 * @brief Refresh the selected character's name, statistics, equipment, and status captions.
 * @param object Status record window.
 */
extern "C" void status_refresh_character_display(StatusCharacterWindow* object)
{
    FieldRecordSelection* selection = object->selection;
    s8 current = selection->current;
    func_003F9890(&reinterpret_cast<StatusCharacterRecord*>(selection->records)[current],
                 &static_cast<StatusCharacterEquipment*>(selection->unk04)[current], 0, -1);
    LibObject175140* record = object->character_name_widget;
    record->unkfc = status_equipment(object->selection)->character_name;
    record->unk3c = 1;
    status_set_numeric(object->hp_value, status_character(object->selection)->get_hp());
    status_set_numeric(object->max_hp_value, status_character(object->selection)->get_max_hp());
    status_set_numeric(object->mp_value, status_character(object->selection)->get_mp());
    status_set_numeric(object->max_mp_value, status_character(object->selection)->get_max_mp());
    status_set_numeric(object->level_value, status_character(object->selection)->get_level());
    status_set_numeric(object->experience_value, status_character(object->selection)->get_experience());
    StatusCharacterRecord* character = &reinterpret_cast<StatusCharacterRecord*>(status_record_table(object->selection))[status_selected_index(object->selection)];
    if (character->get_level() < 255)
    {
        s32 total = 0;
        s32 level = character->get_level();
        StatusExperienceTable* experience = new (0) StatusExperienceTable;
        status_set_numeric(object->next_level_experience_value, func_004028C0(experience, level + 1, character, &total));
        if (experience != 0)
        {
            delete experience;
        }
        object->next_level_experience_value->unk3f = 1;
        object->max_level_caption->unk3f = 0;
    }
    else
    {
        object->next_level_experience_value->unk3f = 0;
        object->max_level_caption->unk3f = 1;
    }
    status_set_numeric(object->attack_value, status_character(object->selection)->get_attack());
    status_set_numeric(object->defense_value, status_character(object->selection)->get_defense());
    status_set_numeric(object->agility_value, status_character(object->selection)->get_agility());
    status_set_numeric(object->hit_value, status_character(object->selection)->get_hit());
    status_set_numeric(object->intelligence_value, status_character(object->selection)->get_intelligence());
    for (s32 index = 0; index < 4; index++)
    {
        s16 identifier = status_equipment(object->selection)->get_allocation_id(index);
        if (identifier == 0)
        {
            object->equipment_values[index]->unk3f = 0;
            object->empty_equipment_captions[index]->unk3f = 1;
        }
        else
        {
            ItemCreationAllocationRecord* allocation = status_allocation(identifier);
            if (allocation == 0)
            {
                object->equipment_values[index]->unk3f = 0;
                object->empty_equipment_captions[index]->unk3f = 1;
            }
            else
            {
                u16 item = allocation->definition_index();
                u8 modification = allocation->modification_number;
                status_set_item(object->equipment_values[index], item + 1, modification);
                object->equipment_values[index]->unk3f = 1;
                object->empty_equipment_captions[index]->unk3f = 0;
            }
        }
    }
    object->selected_slot = object->selection->slots[object->selection->current];
    LibBounds4C69B0* name_bounds = func_00467950(object->character_name_widget);
    LibBounds4C69B0* surname_bounds = lib_text_measure_bounds(object->surname_caption);
    set_status_record_rectangle(object->surname_caption, object->name_x + name_bounds->unk08, object->name_y, surname_bounds->unk08, 24.0f);
    lib_text_set_resource(object->surname_caption, object->func_slot54(), object->selected_slot + STATUS_TEXT_CHARACTER_SURNAME_BASE, 0);
    status_refresh_portrait(object);
    status_refresh_battle_skill_keys(object);
    status_set_numeric(object->sp_value, status_equipment(object->selection)->get_sp());
    status_set_numeric(object->assigned_cp_value, object->assigned_cp);
    status_set_numeric(object->cp_value, status_equipment(object->selection)->get_cp());
    u32 source0 = object->func_slot54();
    lib_text_set_resource(object->short_minor_attack_skill_caption, source0, object->battle_skill_caption_keys[0], 0);
    u32 source1 = object->func_slot54();
    lib_text_set_resource(object->long_minor_attack_skill_caption, source1, object->battle_skill_caption_keys[1], 0);
    u32 source2 = object->func_slot54();
    lib_text_set_resource(object->short_major_attack_skill_caption, source2, object->battle_skill_caption_keys[2], 0);
    u32 source3 = object->func_slot54();
    lib_text_set_resource(object->long_major_attack_skill_caption, source3, object->battle_skill_caption_keys[3], 0);
    u32 source4 = object->func_slot54();
    lib_text_set_resource(object->support_skill_1_caption, source4, object->battle_skill_caption_keys[4], 0);
    u32 source5 = object->func_slot54();
    lib_text_set_resource(object->support_skill_2_caption, source5, object->battle_skill_caption_keys[5], 0);
}

void StatusCharacterWindow::func_slot64()
{
    LibObject175140* character_name_widget = this->character_name_widget;
    character_name_widget->unkfc = static_cast<StatusCharacterEquipment*>(this->selection->unk04)[this->selection->current].character_name;
    character_name_widget->unk3c = 1;
    this->selected_slot = this->selection->slots[this->selection->current];
    LibBounds4C69B0* name_bounds = func_00467950(this->character_name_widget);
    u32 source = this->func_slot54();
    lib_text_set_resource(this->surname_caption, source, this->selected_slot + STATUS_TEXT_CHARACTER_SURNAME_BASE, 0);
    LibBounds4C69B0* surname_bounds = lib_text_measure_bounds(this->surname_caption);
    set_status_record_rectangle(this->surname_caption, this->name_x + name_bounds->unk08,
                                this->name_y, surname_bounds->unk08, 24.0f);
    this->name_entry_hint->unk3f = 1;
    this->name_divider->unk3f = 1;
    this->unk10->unkab = 1;
}

/**
 * @brief Update nested-display cancellation and status-window transitions.
 */
void StatusCharacterWindow::func_slot5c()
{
    if (this->model_cancel_pending != 0 && func_002FD480(this->character_model))
    {
        if (this->character_model != 0)
        {
            this->character_model->func_001DD7B0();
            this->character_model = 0;
        }
        if (this->model_reload_pending != 0)
        {
            status_create_character_model(this);
            this->model_reload_pending = 0;
        }
        else
        {
            this->portrait->unk3f = 1;
            lib_text_set_resource(this->color_setup_hint, this->func_slot54(), STATUS_TEXT_COLOR_SETUP_HINT, 0);
        }
        this->model_cancel_pending = 0;
    }
    FieldClass153E30* receiver = D_001B643C->callbacks->status_receiver;
    if (receiver->func_00261150() != this)
    {
        if (this->character_model != 0)
        {
            field_cancel_model_request(this->character_model);
            this->model_cancel_pending = 1;
        }
        return;
    }
    status_update_scroll(this);
    if (this->character_change_pending == 1 && this->selection->active == 1)
    {
        status_refresh_character_display(this);
        this->character_change_pending = 0;
    }
    if (this->window_transition_pending != 0 && this->character_model == 0)
    {
        this->set_state(1, 0x80);
    }
}

s32 StatusCharacterWindow::func_slotdc()
{
    if (character_change_pending == 1)
    {
        return 0;
    }
    if (selection->count < 2)
    {
        return 0;
    }
    character_change_pending = 1;
    selection->active = 0;
    func_0028E2B0(selection, 1);
    if (character_model != 0)
    {
        field_cancel_model_request(character_model);
        model_cancel_pending = 1;
    }
    return 4;
}

s32 StatusCharacterWindow::func_slotd8()
{
    if (character_change_pending == 1)
    {
        return 0;
    }
    if (selection->count < 2)
    {
        return 0;
    }
    character_change_pending = 1;
    selection->active = 0;
    func_0028E2B0(selection, 0);
    if (character_model != 0)
    {
        field_cancel_model_request(character_model);
        model_cancel_pending = 1;
    }
    return 4;
}

/**
 * @brief Create and attach the nested status display when needed.
 * @param object Status state containing the optional nested display.
 */
void status_create_character_model(StatusCharacterWindow* object)
{
    if (object->character_model == 0)
    {
        object->character_model = new (0) FieldClass15BB90;
        FieldRecordSelection* selection = object->selection;
        u16 identifier = selection->slots[selection->current];
        u16 variant = static_cast<StatusCharacterEquipment*>(selection->unk04)[selection->current].character_resource_variant;
        if (variant >= 4)
        {
            variant = 3;
        }
        field_request_model_resource(object->character_model, 0x290 + 4 * (identifier - 1) + (u16)variant);
        object->character_model->unk5b = 1;
        field_replace_model_camera(object->character_model, D_001B643C->model_camera);
        field_attach_model_display(object->character_model);
        if (static_cast<StatusWindowSection*>(func_101440(func_101290(func_10D8E0()), 1))->enabled != 0)
        {
            func_002FD1B0(reinterpret_cast<FieldFloatState5C*>(object->character_model), 0.5235988f, 750.0f, 0.0f, 140.0f, 115.0f);
        }
        else
        {
            func_002FD1B0(reinterpret_cast<FieldFloatState5C*>(object->character_model), 0.5235988f, 480.0f, 0.0f, 90.0f, 110.0f);
        }
        D_001B6614->append_node(object->character_model, -1);
    }
}

u8 StatusCharacterWindow::func_slotb8()
{
    if (this->color_setup_hint == 0)
    {
        return 0;
    }
    if (this->character_model != 0)
    {
        field_cancel_model_request(this->character_model);
        this->model_cancel_pending = 1;
        FieldRecordSelection* selection = this->selection;
        s32 next = static_cast<StatusCharacterEquipment*>(selection->unk04)[selection->current].character_resource_variant + 1;
        StatusVariantSection* section = static_cast<StatusVariantSection*>(func_101440(func_101290(func_10D8E0()), 1));
        u16 checksum = section->checksum;
        const u8* begin = section->values;
        const u8* end = reinterpret_cast<const u8*>(&section->checksum);
        u8 maximum;
        if (checksum != func_00457470(section->seed, begin, end - begin))
        {
            maximum = 0;
        }
        else
        {
            maximum = section->values[3];
        }
        next %= maximum + 1;
        selection = this->selection;
        static_cast<StatusCharacterEquipment*>(selection->unk04)[selection->current].character_resource_variant = next;
        this->model_reload_pending = 1;
        return 1;
    }
    status_create_character_model(this);
    this->portrait->unk3f = 0;
    lib_text_set_resource(this->color_setup_hint, this->func_slot54(), STATUS_TEXT_COLOR_CHANGE_HINT, 0);
    return 1;
}

u8 StatusCharacterWindow::func_slotb4()
{
    if (D_001B643C->menu_controller == 0)
    {
        return 0;
    }
    if (this->character_model != 0)
    {
        field_cancel_model_request(this->character_model);
        this->model_cancel_pending = 1;
    }
    this->window_transition_pending = 1;
    return 2;
}

u8 StatusCharacterWindow::func_slotb0()
{
    this->unk10->unkab = 0;
    StatusResourceState* target = D_001B643C->callbacks->status_receiver;
    if (target != 0)
    {
        target->requested_window = STATUS_WINDOW_NAME;
        target->transition_phase = STATUS_TRANSITION_START;
        D_001B643C->callbacks->input_enabled = 0;
    }
    if (this->character_model != 0)
    {
        field_cancel_model_request(this->character_model);
        this->model_cancel_pending = 1;
    }
    return 1;
}

void status_refresh_portrait(StatusCharacterWindow* object)
{
    u16 selected = object->selection->slots[object->selection->current];
    for (s32 index = 0; index < 8; index++)
    {
        if (selected == object->resource_slots[index])
        {
            break;
        }
    }
    u16 key;
    if (object->alternate_portrait_group != 0)
    {
        key = selected + 14;
    }
    else if (selected == 1 || selected == 2)
    {
        key = selected + 58;
    }
    else
    {
        key = selected + 14;
    }
    void* allocation = func_002D3D80(D_001B643C->slots, key & 0xFF);
    FieldResourceRecord* record = func_002D3CC0(D_001B643C->slots, 0);
    if (object->portrait != 0)
    {
        set_status_resource_scale(object->portrait, 1.3f, 1.3f);
    }
    LibClass175110* display = object->portrait;
    if (display != 0 && record != 0)
    {
        set_status_widget_position(display, object->portrait_x, object->portrait_y);
        func_002D5CF0(object->portrait, allocation, record, static_cast<u8>(key));
    }
}

void status_refresh_battle_skill_keys(StatusCharacterWindow* object)
{
    s32 skill_id, mastery_points, mastery_level, points_to_next_level;
    s32 minor_mp_cost, minor_hp_cost, cp_cost, minor_fury_cost, major_damage_scale_minus_one;
    if (object->selection != 0)
    {
        object->assigned_cp = 0;
        FieldRecordSelection* selection = object->selection;
        StatusCharacterEquipment* record = &static_cast<StatusCharacterEquipment*>(selection->unk04)[selection->current];
        if (record != 0)
        {
            for (s32 index = 0; index < 6; index++)
            {
                object->battle_skill_caption_keys[index] = STATUS_TEXT_NONE;
                s32 entry = status_battle_skill_index(record, index);
                if (entry > 0)
                {
                    selection = object->selection;
                    func_00408850(&static_cast<StatusCharacterEquipment*>(selection->unk04)[selection->current], selection->slots[selection->current], entry - 1,
                                  &skill_id, &mastery_points, &mastery_level, &points_to_next_level);
                    selection = object->selection;
                    func_004095C0(skill_id, &selection->records[selection->current], &static_cast<StatusCharacterEquipment*>(selection->unk04)[selection->current],
                                  &minor_mp_cost, &minor_hp_cost, &cp_cost, &minor_fury_cost, &major_damage_scale_minus_one, 0, 0, 0);
                    object->assigned_cp += cp_cost;
                    object->battle_skill_caption_keys[index] = skill_id + STATUS_TEXT_BATTLE_SKILL_BASE;
                }
                else
                {
                    object->battle_skill_caption_keys[index] = STATUS_TEXT_NONE;
                }
            }
        }
    }
}

/**
 * @brief Create the selected character's portrait, stat rows, equipment, and scrolling displays.
 * @param associated Full resource source word.
 * @return One on completion, or zero if selection or a stat label is unavailable.
 */
s32 StatusCharacterWindow::func_slotf4(u32 associated)
{
    StatusFlagsSection* flags = static_cast<StatusFlagsSection*>(func_101440(func_101290(func_10D8E0()), 4));
    if (flags != 0)
    {
        alternate_portrait_group = (flags->flags & 0x10) != 0;
    }
    selection = D_001B643C->callbacks->status_receiver->selected_records();
    if (selection == 0)
    {
        return 0;
    }
    selected_slot = selection->slots[selection->current];
    FieldClass15AE70::func_slot10(associated, 16.0f, 72.0f, 14);
    container = new (0) LibObject178660;
    lib_container_init(container, 0, 16.0f, 72.0f, 9, 0.0f, 0x898);
    lib_queue_display_object(D_001B657C, container);
    LibClass178630* panel = new (0) LibClass178630;
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 608.0f, 392.0f, 88.0f);
    lib_container_attach_widget(container, panel);
    name_x = 12.0f;
    name_y = 12.0f;
    character_name_widget = new (0) LibObject175140;
    surname_caption = new (0) LibObject178750;
    name_divider = new (0) ItemCreationClass172870;
    character_name_widget->func_00467AD0(name_x, name_y, 0.0f, 0.0f, status_equipment(selection)->character_name, 0);
    lib_container_attach_widget(unk10, character_name_widget);
    status_append_name_widget(reinterpret_cast<StatusWidgetList*>(&unk44), character_name_widget);
    LibBounds4C69B0* bounds = func_00467950(character_name_widget);
    lib_text_init_resource_rectangle(surname_caption, associated, selected_slot + STATUS_TEXT_CHARACTER_SURNAME_BASE, 0, name_x + bounds->unk08, name_y, 0.0f, 0.0f);
    status_set_spacing(surname_caption, -1.0f);
    lib_container_attach_widget(unk10, surname_caption);
    lib_text_measure_bounds(surname_caption);
    float divider_y = 26.0f + name_y;
    lib_marker_init_rectangle(name_divider, 12.0f, divider_y, 584.0f, 3.0f);
    status_set_marker_color(name_divider, 0x888888);
    lib_container_attach_widget(unk10, name_divider);
    if (selection->count > 1)
    {
        LibObject178750* hint = new (0) LibObject178750;
        hint->init_resource_rectangle(384.0f, name_y, 0.0f, 0.0f, associated, STATUS_TEXT_MEMBER_HINT, 0);
        lib_container_attach_widget(unk10, hint);
    }
    name_entry_hint = new (0) LibObject178750;
    lib_text_init_resource_rectangle(name_entry_hint, associated, STATUS_TEXT_NAME_HINT, 0, 520.0f, name_y, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, name_entry_hint);
    ItemCreationClass1746A0* scissor = new (0) ItemCreationClass1746A0;
    ItemCreationClass1746A0* reset = new (0) ItemCreationClass1746A0;
    lib_scissor_init_rectangle(scissor, 8.0f, 48.0f, 580.0f, 336.0f);
    lib_container_attach_widget(unk10, scissor);
    portrait_x = 316.0f;
    portrait_y = 52.0f;
    portrait = new (0) ItemCreationOptionResourceDisplay;
    u16 resource_key;
    if (alternate_portrait_group)
    {
        resource_key = selected_slot + 14;
    }
    else if (selected_slot == 1 || selected_slot == 2)
    {
        resource_key = selected_slot + 58;
    }
    else
    {
        resource_key = selected_slot + 14;
    }
    portrait->unkcc = func_002D3D80(D_001B643C->slots, resource_key & 0xFF);
    portrait->unkd0 = resource_key;
    portrait->func_002D6440(func_002D3CC0(D_001B643C->slots, 0), portrait_x, portrait_y);
    portrait->unk34 = 3;
    lib_container_attach_widget(unk10, portrait);
    StatusVariantSection* variants = static_cast<StatusVariantSection*>(func_101440(func_101290(func_10D8E0()), 1));
    u8* variant_begin = variants->values;
    u8* variant_end = reinterpret_cast<u8*>(&variants->checksum);
    u8 variant;
    if (variants->checksum != func_00457470(variants->seed, variant_begin, variant_end - variant_begin))
    {
        variant = 0;
    }
    else
    {
        variant = variants->values[3];
    }
    if (variant > 0)
    {
        color_setup_hint = new (0) LibObject178750;
        lib_text_init_resource_rectangle(color_setup_hint, associated, STATUS_TEXT_COLOR_SETUP_HINT, 0, 467.0f, 350.0f, 0.0f, 0.0f);
        lib_container_attach_widget(unk10, color_setup_hint);
    }
    float base_y = portrait_y;
    for (s32 index = 0; index < 8; index++)
    {
        u16 identifier = selection->slots[static_cast<s16>(index)];
        if (identifier != 0)
        {
            resource_slots[index] = identifier;
        }
    }
    hp_value = new (0) LibObject174F20;
    max_hp_value = new (0) LibObject174F20;
    mp_value = new (0) LibObject174F20;
    max_mp_value = new (0) LibObject174F20;
    level_value = new (0) LibObject174F20;
    experience_value = new (0) LibObject174F20;
    next_level_experience_value = new (0) LibObject174F20;
    max_level_caption = new (0) LibObject178750;
    attack_value = new (0) LibObject174F20;
    defense_value = new (0) LibObject174F20;
    agility_value = new (0) LibObject174F20;
    hit_value = new (0) LibObject174F20;
    intelligence_value = new (0) LibObject174F20;
    sp_value = new (0) LibObject174F20;
    assigned_cp_value = new (0) LibObject174F20;
    cp_value = new (0) LibObject174F20;
    skills_label = new (0) LibObject178750;
    sp_label = new (0) LibObject178750;
    cp_label = new (0) LibObject178750;
    cp_separator = new (0) LibObject178750;
    short_minor_attack_button = new (0) LibObject178750;
    short_minor_attack_label = new (0) LibObject178750;
    long_minor_attack_button = new (0) LibObject178750;
    long_minor_attack_label = new (0) LibObject178750;
    short_major_attack_button = new (0) LibObject178750;
    short_major_attack_label = new (0) LibObject178750;
    long_major_attack_button = new (0) LibObject178750;
    long_major_attack_label = new (0) LibObject178750;
    support_skill_1_label = new (0) LibObject178750;
    support_skill_1_caption = new (0) LibObject178750;
    support_skill_2_label = new (0) LibObject178750;
    support_skill_2_caption = new (0) LibObject178750;
    short_minor_attack_skill_caption = new (0) LibObject178750;
    long_minor_attack_skill_caption = new (0) LibObject178750;
    short_major_attack_skill_caption = new (0) LibObject178750;
    long_major_attack_skill_caption = new (0) LibObject178750;
    status_append_numeric_widget(reinterpret_cast<StatusWidgetList*>(&numeric_widgets), hp_value);
    status_append_numeric_widget(reinterpret_cast<StatusWidgetList*>(&numeric_widgets), max_hp_value);
    status_append_numeric_widget(reinterpret_cast<StatusWidgetList*>(&numeric_widgets), mp_value);
    status_append_numeric_widget(reinterpret_cast<StatusWidgetList*>(&numeric_widgets), max_mp_value);
    status_append_numeric_widget(reinterpret_cast<StatusWidgetList*>(&numeric_widgets), level_value);
    status_append_numeric_widget(reinterpret_cast<StatusWidgetList*>(&numeric_widgets), experience_value);
    status_append_numeric_widget(reinterpret_cast<StatusWidgetList*>(&numeric_widgets), next_level_experience_value);
    status_append_numeric_widget(reinterpret_cast<StatusWidgetList*>(&numeric_widgets), attack_value);
    status_append_numeric_widget(reinterpret_cast<StatusWidgetList*>(&numeric_widgets), defense_value);
    status_append_numeric_widget(reinterpret_cast<StatusWidgetList*>(&numeric_widgets), agility_value);
    status_append_numeric_widget(reinterpret_cast<StatusWidgetList*>(&numeric_widgets), hit_value);
    status_append_numeric_widget(reinterpret_cast<StatusWidgetList*>(&numeric_widgets), intelligence_value);
    status_append_numeric_widget(reinterpret_cast<StatusWidgetList*>(&numeric_widgets), sp_value);
    status_append_numeric_widget(reinterpret_cast<StatusWidgetList*>(&numeric_widgets), assigned_cp_value);
    status_append_numeric_widget(reinterpret_cast<StatusWidgetList*>(&numeric_widgets), cp_value);
    status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&text_widgets), skills_label);
    status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&text_widgets), sp_label);
    status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&text_widgets), cp_label);
    status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&text_widgets), cp_separator);
    status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&text_widgets), short_minor_attack_button);
    status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&text_widgets), short_minor_attack_label);
    status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&text_widgets), long_minor_attack_button);
    status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&text_widgets), long_minor_attack_label);
    status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&text_widgets), short_major_attack_button);
    status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&text_widgets), short_major_attack_label);
    status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&text_widgets), long_major_attack_button);
    status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&text_widgets), long_major_attack_label);
    status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&text_widgets), support_skill_1_label);
    status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&text_widgets), support_skill_1_caption);
    status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&text_widgets), support_skill_2_label);
    status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&text_widgets), support_skill_2_caption);
    status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&text_widgets), short_minor_attack_skill_caption);
    status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&text_widgets), long_minor_attack_skill_caption);
    status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&text_widgets), short_major_attack_skill_caption);
    status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&text_widgets), long_major_attack_skill_caption);
    for (s32 index = 0; index <= 4; index++)
    {
        LibObject178750* label = new (0) LibObject178750;
        lib_text_init_resource_rectangle(label, associated, STATUS_TEXT_HP + index, 1, 16.0f, base_y + 24.0f * static_cast<float>(index), 0.0f, 0.0f);
        label->set_color(0x806080);
        label->set_scale(0.85f, 0.85f);
        lib_container_attach_widget(unk10, label);
        status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&text_widgets), label);
    }
    FieldRecordSelection* selected = selection;
    s8 current = selected->current;
    StatusCharacterRecord* character = &reinterpret_cast<StatusCharacterRecord*>(selected->records)[current];
    func_003F9890(character, &static_cast<StatusCharacterEquipment*>(selected->unk04)[current], 0, -1);
    s32 hp = status_character(selection)->get_hp();
    s32 mp = status_character(selection)->get_mp();
    s32 maximum_hp = status_character(selection)->get_max_hp();
    s32 maximum_mp = status_character(selection)->get_max_mp();
    character = &reinterpret_cast<StatusCharacterRecord*>(status_record_table(selection))[status_selected_index(selection)];
    s32 level = character->get_level();
    s32 experience = character->get_experience();
    hp_value->init_numeric_resource_rectangle(58.0f, base_y, 60.0f, 24.0f, hp, 0, 0);
    lib_container_attach_widget(unk10, hp_value);
    hp_value->set_scale(0.9f, 0.9f);
    float mp_y = 24.0f + base_y;
    mp_value->init_numeric_resource_rectangle(58.0f, mp_y, 60.0f, 24.0f, mp, 0, 0);
    lib_container_attach_widget(unk10, mp_value);
    mp_value->set_scale(0.9f, 0.9f);
    max_hp_value->init_numeric_resource_rectangle(142.0f, base_y, 60.0f, 24.0f, maximum_hp, 0, 0);
    lib_container_attach_widget(unk10, max_hp_value);
    max_hp_value->set_scale(0.9f, 0.9f);
    max_mp_value->init_numeric_resource_rectangle(142.0f, mp_y, 60.0f, 24.0f, maximum_mp, 0, 0);
    lib_container_attach_widget(unk10, max_mp_value);
    max_mp_value->set_scale(0.9f, 0.9f);
    level_value->init_numeric_resource_rectangle(142.0f, 48.0f + base_y, 60.0f, 24.0f, level, 0, 0);
    lib_container_attach_widget(unk10, level_value);
    level_value->set_scale(0.9f, 0.9f);
    experience_value->init_numeric_resource_rectangle(142.0f, 72.0f + base_y, 60.0f, 24.0f, experience, 0, 0);
    lib_container_attach_widget(unk10, experience_value);
    experience_value->set_scale(0.9f, 0.9f);
    character = status_character(selection);
    s32 total = 0;
    level = character->get_level();
    StatusExperienceTable* table = new (0) StatusExperienceTable;
    s32 remaining_experience = func_004028C0(table, level + 1, character, &total);
    float next_y = 96.0f + base_y;
    next_level_experience_value->init_numeric_resource_rectangle(142.0f, next_y, 60.0f, 24.0f, remaining_experience, 0, 0);
    lib_container_attach_widget(unk10, next_level_experience_value);
    next_level_experience_value->set_scale(0.9f, 0.9f);
    if (table != 0)
    {
        delete table;
    }
    lib_text_init_resource_rectangle(max_level_caption, associated, STATUS_TEXT_MAX_LEVEL, 0, 158.0f, next_y, 0.0f, 0.0f);
    max_level_caption->set_scale(0.9f, 0.9f);
    max_level_caption->set_color(0x508050);
    lib_container_attach_widget(unk10, max_level_caption);
    status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&text_widgets), max_level_caption);
    for (s32 index = 0; index < 2; index++)
    {
        LibObject178750* separator = new (0) LibObject178750;
        lib_text_init_resource_rectangle(separator, associated, STATUS_TEXT_SLASH, 0, 128.0f, base_y + 24.0f * static_cast<float>(index), 0.0f, 0.0f);
        separator->set_color(0x806080);
        separator->set_scale(0.85f, 0.85f);
        lib_container_attach_widget(unk10, separator);
        status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&text_widgets), separator);
    }
    for (s32 key = STATUS_TEXT_ATTACK; key <= STATUS_TEXT_ACCESSORY_2; key++)
    {
        LibObject178750* label = new (0) LibObject178750;
        if (label == 0)
        {
            return 0;
        }
        switch (key)
        {
        case STATUS_TEXT_ATTACK:
        case STATUS_TEXT_DEFENSE:
        case STATUS_TEXT_AGILITY:
        case STATUS_TEXT_HIT:
        case STATUS_TEXT_INTELLIGENCE:
            lib_text_init_resource_rectangle(label, associated, key, 1, 234.0f, base_y + 24.0f * static_cast<float>(key - STATUS_TEXT_ATTACK), 0.0f, 0.0f);
            label->set_scale(0.85f, 0.85f);
            break;
        case STATUS_TEXT_WEAPON:
        case STATUS_TEXT_ARMOR:
        case STATUS_TEXT_ACCESSORY_1:
        case STATUS_TEXT_ACCESSORY_2:
            lib_text_init_resource_rectangle(label, associated, key, 1, 16.0f, 2.0f + (180.0f + 48.0f * static_cast<float>(key - STATUS_TEXT_WEAPON)), 0.0f, 0.0f);
            label->set_scale(0.75f, 0.75f);
            break;
        }
        label->set_color(0x806080);
        lib_container_attach_widget(unk10, label);
        status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&text_widgets), label);
    }
    attack_value->init_numeric_resource_rectangle(294.0f, base_y, 48.0f, 24.0f, status_character(selection)->get_attack(), 0, 0);
    lib_container_attach_widget(unk10, attack_value);
    attack_value->set_scale(0.9f, 0.9f);
    s32 defense = status_character(selection)->get_defense();
    defense_value->init_numeric_resource_rectangle(294.0f, status_row_y(base_y, 1), 48.0f, 24.0f, defense, 0, 0);
    lib_container_attach_widget(unk10, defense_value);
    defense_value->set_scale(0.9f, 0.9f);
    s32 agility = status_character(selection)->get_agility();
    agility_value->init_numeric_resource_rectangle(294.0f, status_row_y(base_y, 2), 48.0f, 24.0f, agility, 0, 0);
    lib_container_attach_widget(unk10, agility_value);
    agility_value->set_scale(0.9f, 0.9f);
    s32 hit = status_character(selection)->get_hit();
    hit_value->init_numeric_resource_rectangle(294.0f, status_row_y(base_y, 3), 48.0f, 24.0f, hit, 0, 0);
    lib_container_attach_widget(unk10, hit_value);
    hit_value->set_scale(0.9f, 0.9f);
    s32 intelligence = status_character(selection)->get_intelligence();
    intelligence_value->init_numeric_resource_rectangle(294.0f, status_row_y(base_y, 4), 48.0f, 24.0f, intelligence, 0, 0);
    lib_container_attach_widget(unk10, intelligence_value);
    intelligence_value->set_scale(0.9f, 0.9f);
    for (s32 index = 0; index < 4; index++)
    {
        equipment_values[index] = new (0) LibObject172410;
        empty_equipment_captions[index] = new (0) LibObject178750;
        status_append_item_widget(reinterpret_cast<StatusWidgetList*>(&item_widgets), equipment_values[index]);
        status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&text_widgets), empty_equipment_captions[index]);
    }
    for (s32 index = 0; index < 4; index++)
    {
        float item_y = 204.0f + 48.0f * static_cast<float>(index);
        lib_item_code_init_rectangle(equipment_values[index], 32.0f, item_y, 306.000030517578125f, 20.40000152587890625f, 0, 0, 0);
        equipment_values[index]->set_scale(0.85f, 0.85f);
        status_set_item_flag(equipment_values[index], 1);
        lib_container_attach_widget(unk10, equipment_values[index]);
        lib_text_init_resource_rectangle(empty_equipment_captions[index], associated, STATUS_TEXT_NONE, 0, 32.0f, item_y, 0.0f, 0.0f);
        empty_equipment_captions[index]->set_scale(0.85f, 0.85f);
        lib_container_attach_widget(unk10, empty_equipment_captions[index]);
    }
    status_refresh_battle_skill_keys(this);
    float lower_y = 392.0f + base_y;
    lib_text_init_resource_rectangle(skills_label, associated, STATUS_TEXT_SKILLS, 1, 16.0f, lower_y, 0.0f, 0.0f);
    skills_label->set_color(0x806080);
    skills_label->set_scale(0.85f, 0.85f);
    lib_container_attach_widget(unk10, skills_label);
    lib_text_init_resource_rectangle(sp_label, associated, STATUS_TEXT_SP, 1, 16.0f, lower_y + 24.0f, 0.0f, 0.0f);
    sp_label->set_color(0x806080);
    sp_label->set_scale(0.85f, 0.85f);
    lib_container_attach_widget(unk10, sp_label);
    lib_text_init_resource_rectangle(cp_label, associated, STATUS_TEXT_CP, 1, 16.0f, lower_y + 48.0f, 0.0f, 0.0f);
    cp_label->set_color(0x806080);
    cp_label->set_scale(0.85f, 0.85f);
    lib_container_attach_widget(unk10, cp_label);
    sp_value->init_numeric_resource_rectangle(158.0f, lower_y + 24.0f, 48.0f, 24.0f, 8888, 0, 0);
    sp_value->set_scale(0.9f, 0.9f);
    lib_container_attach_widget(unk10, sp_value);
    assigned_cp_value->init_numeric_resource_rectangle(70.0f, lower_y + 48.0f, 48.0f, 24.0f, 8888, 1, 0);
    assigned_cp_value->set_scale(0.9f, 0.9f);
    lib_container_attach_widget(unk10, assigned_cp_value);
    cp_separator->init_resource_rectangle(130.0f, lower_y + 48.0f, 0.0f, 0.0f, associated, STATUS_TEXT_SLASH, 1);
    cp_separator->set_scale(0.85f, 0.85f);
    lib_container_attach_widget(unk10, cp_separator);
    cp_value->init_numeric_resource_rectangle(158.0f, lower_y + 48.0f, 48.0f, 24.0f, status_equipment(selection)->get_cp(), 0, 0);
    cp_value->set_scale(0.9f, 0.9f);
    lib_container_attach_widget(unk10, cp_value);
    lib_text_init_resource_rectangle(short_minor_attack_button, associated, STATUS_TEXT_MINOR_ATTACK_BUTTON, 0, 16.0f, 553.0f, 0.0f, 0.0f);
    lib_text_init_resource_rectangle(short_minor_attack_label, associated, STATUS_TEXT_SHORT_RANGE, 1, 46.0f, 556.0f, 96.0f, 24.0f);
    short_minor_attack_skill_caption->init_resource_rectangle(124.0f, 556.0f, 0.0f, 0.0f, associated, battle_skill_caption_keys[0], 0);
    short_minor_attack_button->set_scale(0.8f, 0.8f);
    lib_container_attach_widget(unk10, short_minor_attack_button);
    short_minor_attack_label->set_scale(0.8f, 0.8f);
    short_minor_attack_label->set_color(0x806080);
    short_minor_attack_label->set_mode(0);
    short_minor_attack_label->set_vertical_alignment(1);
    lib_container_attach_widget(unk10, short_minor_attack_label);
    short_minor_attack_skill_caption->set_scale(0.9f, 0.9f);
    status_set_spacing(short_minor_attack_skill_caption, -1.0f);
    lib_container_attach_widget(unk10, short_minor_attack_skill_caption);
    lib_text_init_resource_rectangle(long_minor_attack_button, associated, STATUS_TEXT_MINOR_ATTACK_BUTTON, 0, 16.0f, 591.0f, 0.0f, 0.0f);
    lib_text_init_resource_rectangle(long_minor_attack_label, associated, STATUS_TEXT_LONG_RANGE, 1, 46.0f, 594.0f, 96.0f, 24.0f);
    long_minor_attack_skill_caption->init_resource_rectangle(124.0f, 594.0f, 0.0f, 0.0f, associated, battle_skill_caption_keys[1], 0);
    long_minor_attack_button->set_scale(0.8f, 0.8f);
    lib_container_attach_widget(unk10, long_minor_attack_button);
    long_minor_attack_label->set_scale(0.8f, 0.8f);
    long_minor_attack_label->set_color(0x806080);
    long_minor_attack_label->set_mode(0);
    long_minor_attack_label->set_vertical_alignment(1);
    lib_container_attach_widget(unk10, long_minor_attack_label);
    long_minor_attack_skill_caption->set_scale(0.9f, 0.9f);
    status_set_spacing(long_minor_attack_skill_caption, -1.0f);
    lib_container_attach_widget(unk10, long_minor_attack_skill_caption);
    lib_text_init_resource_rectangle(short_major_attack_button, associated, STATUS_TEXT_MAJOR_ATTACK_BUTTON, 0, 16.0f, 629.0f, 0.0f, 0.0f);
    lib_text_init_resource_rectangle(short_major_attack_label, associated, STATUS_TEXT_SHORT_RANGE, 1, 46.0f, 632.0f, 96.0f, 24.0f);
    short_major_attack_skill_caption->init_resource_rectangle(124.0f, 632.0f, 0.0f, 0.0f, associated, battle_skill_caption_keys[2], 0);
    short_major_attack_button->set_scale(0.8f, 0.8f);
    lib_container_attach_widget(unk10, short_major_attack_button);
    short_major_attack_label->set_scale(0.8f, 0.8f);
    short_major_attack_label->set_color(0x806080);
    short_major_attack_label->set_mode(0);
    short_major_attack_label->set_vertical_alignment(1);
    lib_container_attach_widget(unk10, short_major_attack_label);
    short_major_attack_skill_caption->set_scale(0.9f, 0.9f);
    status_set_spacing(short_major_attack_skill_caption, -1.0f);
    lib_container_attach_widget(unk10, short_major_attack_skill_caption);
    lib_text_init_resource_rectangle(long_major_attack_button, associated, STATUS_TEXT_MAJOR_ATTACK_BUTTON, 0, 16.0f, 667.0f, 0.0f, 0.0f);
    lib_text_init_resource_rectangle(long_major_attack_label, associated, STATUS_TEXT_LONG_RANGE, 1, 46.0f, 670.0f, 96.0f, 24.0f);
    long_major_attack_skill_caption->init_resource_rectangle(124.0f, 670.0f, 0.0f, 0.0f, associated, battle_skill_caption_keys[3], 0);
    long_major_attack_button->set_scale(0.8f, 0.8f);
    lib_container_attach_widget(unk10, long_major_attack_button);
    long_major_attack_label->set_scale(0.8f, 0.8f);
    long_major_attack_label->set_color(0x806080);
    long_major_attack_label->set_mode(0);
    long_major_attack_label->set_vertical_alignment(1);
    lib_container_attach_widget(unk10, long_major_attack_label);
    long_major_attack_skill_caption->set_scale(0.9f, 0.9f);
    status_set_spacing(long_major_attack_skill_caption, -1.0f);
    lib_container_attach_widget(unk10, long_major_attack_skill_caption);
    lib_text_init_resource_rectangle(support_skill_1_label, associated, STATUS_TEXT_SUPPORT_1, 1, 16.0f, 708.0f, 96.0f, 24.0f);
    support_skill_1_label->set_scale(0.8f, 0.8f);
    support_skill_1_label->set_color(0x806080);
    support_skill_1_label->set_mode(0);
    support_skill_1_label->set_vertical_alignment(1);
    lib_container_attach_widget(unk10, support_skill_1_label);
    support_skill_1_caption->init_resource_rectangle(124.0f, 708.0f, 0.0f, 0.0f, associated, battle_skill_caption_keys[4], 0);
    support_skill_1_caption->set_scale(0.9f, 0.9f);
    lib_container_attach_widget(unk10, support_skill_1_caption);
    lib_text_init_resource_rectangle(support_skill_2_label, associated, STATUS_TEXT_SUPPORT_2, 1, 16.0f, 746.0f, 96.0f, 24.0f);
    support_skill_2_label->set_scale(0.8f, 0.8f);
    support_skill_2_label->set_color(0x806080);
    support_skill_2_label->set_mode(0);
    support_skill_2_label->set_vertical_alignment(1);
    lib_container_attach_widget(unk10, support_skill_2_label);
    support_skill_2_caption->init_resource_rectangle(124.0f, 746.0f, 0.0f, 0.0f, associated, battle_skill_caption_keys[5], 0);
    support_skill_2_caption->set_scale(0.9f, 0.9f);
    lib_container_attach_widget(unk10, support_skill_2_caption);
    lib_scissor_init_reset(reset, 1);
    lib_container_attach_widget(unk10, reset);
    scroll_marker = new (0) ItemCreationClass1725D0;
    lib_list_indicator_init(scroll_marker, 588.0f, 8.0f + divider_y, (392.0f - divider_y) - 16.0f, scroll_extent, scroll_position);
    lib_container_attach_widget(unk10, scroll_marker);
    status_refresh_character_display(this);
    return 1;
}

LibClass178A70::~LibClass178A70()
{
}

void StatusCharacterWindow::func_slot0c()
{
    container->func_003EF740();
    FieldClass15AE70::func_slot0c();
}

/** @brief Release the owned display lists and window base. */
StatusCharacterWindow::~StatusCharacterWindow()
{
}

/** @brief Initialize the character window and its three owned widget lists. */
StatusCharacterWindow::StatusCharacterWindow()
{
    selection = 0;
    character_change_pending = 0;
    character_name_widget = 0;
    hp_value = 0;
    max_hp_value = 0;
    mp_value = 0;
    max_mp_value = 0;
    level_value = 0;
    experience_value = 0;
    next_level_experience_value = 0;
    attack_value = 0;
    defense_value = 0;
    agility_value = 0;
    hit_value = 0;
    intelligence_value = 0;
    skills_label = 0;
    sp_label = 0;
    cp_label = 0;
    sp_value = 0;
    assigned_cp_value = 0;
    cp_separator = 0;
    cp_value = 0;
    short_minor_attack_button = 0;
    short_minor_attack_label = 0;
    long_minor_attack_button = 0;
    long_minor_attack_label = 0;
    short_major_attack_button = 0;
    short_major_attack_label = 0;
    long_major_attack_button = 0;
    long_major_attack_label = 0;
    support_skill_1_label = 0;
    support_skill_1_caption = 0;
    support_skill_2_label = 0;
    support_skill_2_caption = 0;
    short_minor_attack_skill_caption = 0;
    long_minor_attack_skill_caption = 0;
    short_major_attack_skill_caption = 0;
    long_major_attack_skill_caption = 0;
    color_setup_hint = 0;
    battle_skill_caption_keys[0] = STATUS_TEXT_NONE;
    battle_skill_caption_keys[1] = STATUS_TEXT_NONE;
    battle_skill_caption_keys[2] = STATUS_TEXT_NONE;
    battle_skill_caption_keys[3] = STATUS_TEXT_NONE;
    battle_skill_caption_keys[4] = STATUS_TEXT_NONE;
    battle_skill_caption_keys[5] = STATUS_TEXT_NONE;
    assigned_cp = 0;
    surname_caption = 0;
    name_divider = 0;
    selected_slot = 0;
    name_x = 0;
    name_y = 0;
    resource_slots[0] = 0;
    resource_slots[1] = 0;
    resource_slots[2] = 0;
    resource_slots[3] = 0;
    resource_slots[4] = 0;
    resource_slots[5] = 0;
    resource_slots[6] = 0;
    resource_slots[7] = 0;
    portrait_x = 0;
    portrait_y = 0;
    portrait = 0;
    scroll_page = 0;
    scroll_active = 0;
    scroll_marker = 0;
    scroll_extent = 50.0f;
    scroll_position = 0;
    scroll_step = 98.0f;
    alternate_portrait_group = 0;
    character_model = 0;
    model_cancel_pending = 0;
    model_reload_pending = 0;
    window_transition_pending = 0;
    equipment_values[0] = 0;
    empty_equipment_captions[0] = 0;
    equipment_values[1] = 0;
    empty_equipment_captions[1] = 0;
    equipment_values[2] = 0;
    empty_equipment_captions[2] = 0;
    equipment_values[3] = 0;
    empty_equipment_captions[3] = 0;
}

/** @brief Hold the caption until its timer expires, then scroll and wrap it. */
void StatusHelpWindow::func_slot5c()
{
    StatusHelpWindow* object = this;
    LibObject178750* target = object->help_caption;
    float x = target->unk18.unk00;
    float y = target->unk18.unk04;
    float width = target->unk18.unk08;
    float height = target->unk18.unk0c;
    if (object->scroll_active == 0)
    {
        set_status_record_rectangle(target, object->initial_text_x, y, width, height);
        object->hold_timer++;
        if (!((float)object->hold_timer <= 120.0f))
        {
            object->hold_timer = 0;
            object->scroll_active = 1;
        }
        return;
    }
    x -= 108.0f * D_001B6690;
    if (x < object->clip_x - (float)object->scroll_distance)
    {
        x = 2.0f + (object->clip_x + object->clip_width);
    }
    set_status_record_rectangle(target, x, y, width, height);
}

/**
 * @brief Select character or name-entry help and reset the scroll timer.
 * @param key Requested caption key.
 */
void StatusHelpWindow::func_slot60(s32 key)
{
    StatusHelpWindow* object = this;
    if (key >= STATUS_TEXT_CHARACTER_HELP && key < STATUS_TEXT_NAME_HELP + 1)
    {
        object->hold_timer = 0;
        object->scroll_active = 0;
        lib_text_set_resource(object->help_caption, object->func_slot54(), key, 1);
        object->scroll_distance = (s32)lib_text_measure_bounds(object->help_caption)->unk08 + 6;
    }
}

/**
 * @brief Create the captions, scrolling text, and frame geometry.
 * @param associated Full resource source word.
 * @return One when the text and both frames are present, otherwise zero.
 */
s32 StatusHelpWindow::func_slotf4(u32 associated)
{
    StatusHelpWindow* object = this;
    object->FieldClass15AE70::func_slot14(associated, 0, 9, 1400, 16.0f, 16.0f, 0.0f);
    LibObject178750* label = new (0) LibObject178750;
    lib_text_init_resource_rectangle(label, static_cast<s32>(associated), STATUS_TEXT_HEADING, 0, 16.0f, 6.0f, 0.0f, 0.0f);
    lib_container_attach_widget(object->unk10, label);
    status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&object->unk2c), label);
    LibObject178750* caption = new (0) LibObject178750;
    lib_text_init_resource_rectangle(caption, static_cast<s32>(associated), STATUS_TEXT_STATUS, 0, 36.0f, 40.0f, 0.0f, 0.0f);
    caption->set_scale(0.65f, 0.65f);
    lib_container_attach_widget(object->unk10, caption);
    status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&object->unk2c), caption);
    object->help_caption = new (0) LibObject178750;
    LibClass1746A0* frame = new (0) LibClass1746A0;
    LibClass1746A0* background = new (0) LibClass1746A0;
    if (object->help_caption == 0 || frame == 0 || background == 0)
    {
        return 0;
    }
    object->heading_width = lib_text_measure_bounds(label)->unk08;
    object->clip_x = 18.0f + object->heading_width;
    float frame_padding = 32.0f;
    object->clip_width = 640.0f - (16.0f + (object->clip_x + frame_padding));
    object->initial_text_x = 24.0f + object->heading_width;
    lib_scissor_init_rectangle(frame, object->clip_x, 0.0f, object->clip_width, 56.0f);
    lib_container_attach_widget(object->unk10, frame);
    status_append_scissor_widget(reinterpret_cast<StatusWidgetList*>(&object->unk20), frame);
    lib_text_init_resource_rectangle(object->help_caption, static_cast<s32>(associated), STATUS_TEXT_CHARACTER_HELP, 0, object->initial_text_x, 6.0f, 0.0f, 0.0f);
    lib_container_attach_widget(object->unk10, object->help_caption);
    status_append_text_widget(reinterpret_cast<StatusWidgetList*>(&object->unk2c), object->help_caption);
    lib_scissor_init_reset(background, 1);
    lib_container_attach_widget(object->unk10, background);
    status_append_scissor_widget(reinterpret_cast<StatusWidgetList*>(&object->unk20), background);
    object->func_slot60(STATUS_TEXT_CHARACTER_HELP);
    return 1;
}

/** @brief Destroy the caption window base. */
StatusHelpWindow::~StatusHelpWindow()
{
}

/**
 * @brief Create and attach the three status resource displays.
 * @param associated Full resource source word.
 * @return One after the displays are initialized.
 */
s32 StatusBackgroundWindow::func_slotf4(u32 associated)
{
    StatusBackgroundWindow* object = this;
    object->FieldClass15AE70::func_slot14(associated, 0, 9, 1200, 16.0f, 16.0f, 0.0f);
    ItemCreationOptionResourceDisplay* first = new (0) ItemCreationOptionResourceDisplay;
    ItemCreationOptionResourceDisplay* second = new (0) ItemCreationOptionResourceDisplay;
    ItemCreationOptionResourceDisplay* third = new (0) ItemCreationOptionResourceDisplay;
    void* allocation = func_002D3D80(D_001B643C->slots, 11);
    first->unkcc = allocation;
    second->unkcc = allocation;
    third->unkcc = allocation;
    first->unkd0 = 11;
    second->unkd0 = 11;
    third->unkd0 = 11;
    initialize_status_resource(first, func_002D3CC0(D_001B643C->slots, 5), 0.0f, 0.0f);
    initialize_status_resource(second, func_002D3CC0(D_001B643C->slots, 6), 256.0f, 0.0f);
    initialize_status_resource(third, func_002D3CC0(D_001B643C->slots, 7), 512.0f, 0.0f);
    lib_container_attach_widget(object->unk10, first);
    lib_container_attach_widget(object->unk10, second);
    lib_container_attach_widget(object->unk10, third);
    return 1;
}

/** @brief Destroy the background window base. */
StatusBackgroundWindow::~StatusBackgroundWindow()
{
}

/** @brief Release the status resource, queue this receiver, and clear its allocation slots. */
void StatusResourceState::func_slot5c()
{
    StatusResourceState* object = this;
    if (object->resource != 0)
    {
        lib_release_resource_slot(D_001B657C, object->resource);
    }
    lib_object_detach_owner(object);
    object->func_001DD7B0();
    FieldBufferSlots* slots = D_001B643C->slots;
    for (s32 index = 15; index <= 22; index++)
    {
        func_002D3DC0(slots, (u8)index);
    }
    func_002D3DC0(slots, 59);
    func_002D3DC0(slots, 60);
}

/** @brief Submit this receiver to the resident object queue. */
void StatusResourceState::func_001DD7B0()
{
    resident_enqueue_object(D_001B65F4, this);
}

/** @brief Switch between record and name windows through a timed transition. */
void StatusResourceState::func_001DF360()
{
    StatusResourceState* object = this;
    switch (object->transition_phase)
    {
    case STATUS_TRANSITION_IDLE:
        break;
    case STATUS_TRANSITION_START:
    {
        func_0020F230(D_001B6430->context->unk38, 0, 0, 0x80000000, 0, 0, 0, 10.0f, 0.0f, 0.0f);
        StatusTransitionEffect* effect;
        (effect = reinterpret_cast<StatusTransitionOwner*>(D_001B6430->context->unk38)->effect)->value = D_001B6694;
        effect->mode = 10;
        object->transition_phase = STATUS_TRANSITION_SWITCH_WINDOW;
        break;
    }
    case STATUS_TRANSITION_SWITCH_WINDOW:
    {
        if ((u8)func_0022A160(reinterpret_cast<StatusTransitionOwner*>(D_001B6430->context->unk38)->effect) != 0)
        {
            return;
        }
        func_004DCEA0(D_001B6650, 0, 0);
        switch (object->requested_window)
        {
        case STATUS_WINDOW_CHARACTER:
            static_cast<StatusHelpWindow*>(D_001B643C->callbacks->status_receiver->func_00263C90())->func_slot60(STATUS_TEXT_CHARACTER_HELP);
            D_001B643C->callbacks->status_receiver->func_00263C70(object->character_window);
            object->character_window->func_slot64();
            object->character_window->func_slot18(1, 127);
            object->character_window->func_slot20(1);
            break;
        case STATUS_WINDOW_NAME:
        {
            static_cast<StatusHelpWindow*>(D_001B643C->callbacks->status_receiver->func_00263C90())->func_slot60(STATUS_TEXT_NAME_HELP);
            StatusNameWindow* window = new (0) StatusNameWindow;
            window->func_slotf4((void*)object->resource);
            window->func_slot40(object->character_window);
            object->FieldClass153E30::add_child(window);
            D_001B643C->callbacks->status_receiver->func_00263C70(window);
            break;
        }
        }
        func_0020F230(D_001B6430->context->unk38, 0, 0x80000000, 0, 0, 0, 0, 10.0f, 0.0f, 0.0f);
        StatusTransitionEffect* effect;
        (effect = reinterpret_cast<StatusTransitionOwner*>(D_001B6430->context->unk38)->effect)->value = D_001B6694;
        effect->mode = 10;
        object->transition_phase = STATUS_TRANSITION_FINISH;
        func_004DCEA0(D_001B6650, 1, 0);
        break;
    }
    case STATUS_TRANSITION_FINISH:
        if ((u8)func_0022A160(reinterpret_cast<StatusTransitionOwner*>(D_001B6430->context->unk38)->effect) == 0)
        {
            object->transition_phase = STATUS_TRANSITION_IDLE;
            D_001B643C->callbacks->input_enabled = 1;
        }
        break;
    }
}

/** @brief Get the text window. @return Stored text window pointer. */
void* StatusResourceState::func_00263C90()
{
    return unk24;
}

/**
 * @brief Create and attach the status windows and record selection.
 * @return One after setup succeeds, or zero otherwise.
 */
s32 StatusResourceState::func_00263CD0()
{
    StatusResourceState* object = this;
    StatusBackgroundWindow* background = new (0) StatusBackgroundWindow;
    StatusHelpWindow* text = new (0) StatusHelpWindow;
    object->character_window = new (0) StatusCharacterWindow;
    object->selection = new (0) FieldRecordSelection;
    if ((u8)func_0028E3D0(object->selection) == 0)
    {
        return 0;
    }
    object->unk20 = object->character_window;
    background->func_slotf4(object->resource);
    object->FieldClass153E30::add_child(background);
    background->func_slot40(0);
    text->func_slotf4(object->resource);
    object->FieldClass153E30::add_child(text);
    object->unk24 = text;
    text->func_slot40(background);
    object->character_window->func_slotf4(object->resource);
    object->FieldClass153E30::add_child(object->character_window);
    object->setup_complete = 1;
    return 1;
}

/**
 * @brief Load the completed status resource and finish receiver setup.
 * @param buffer Completed resource buffer, or null.
 * @return Zero without a buffer, otherwise the receiver setup result.
 */
s32 StatusResourceState::func_001E1820(void* buffer)
{
    StatusResourceState* object = this;
    if (buffer == 0)
    {
        return 0;
    }
    StatusAlignedResource* aligned = aligned_status_resource(buffer);
    s32 size = aligned->size + 0x80;
    void* saved_heap = resident_get_allocation_heap();
    void* heap = D_001B6430->context->unk70;
    void* memory = resident_heap_allocate(heap, size);
    if (memory != 0)
    {
        resident_heap_release(memory);
        resident_exchange_allocation_heap(heap);
    }
    object->resource = lib_load_resource_slot(D_001B657C, aligned);
    resident_exchange_allocation_heap(saved_heap);
    StatusRuntimeResource* runtime = reinterpret_cast<StatusRuntimeResource*>(D_001B657C);
    runtime->resource = object->resource;
    runtime->code = 0xC351;
    return object->func_00263CD0();
}

/** @brief Report the receiver state. @return One. */
u8 StatusResourceState::func_00264110()
{
    return 1;
}

/** @brief Destroy the owned record selection and the Field receiver base. */
StatusResourceState::~StatusResourceState()
{
    if (selection != 0)
    {
        status_delete_owned(selection);
    }
}

/** @brief Initialize the resource handle, selection, and transition state. */
StatusResourceState::StatusResourceState()
{
    resource = 0;
    setup_complete = 0;
    selection = 0;
    character_window = 0;
    requested_window = STATUS_WINDOW_CHARACTER;
    transition_phase = STATUS_TRANSITION_IDLE;
}

/** @brief Leave the status receiver unchanged. */
void StatusResourceState::func_001DD410()
{
}

void ItemCreationClass185050::func_slot0c()
{
}

StatusNameWindow::~StatusNameWindow()
{
}

/** @brief Leave the base window unchanged. */
void FieldClass15AE70::func_slot68()
{
}

/** @brief Leave the base window unchanged. */
void FieldClass15AE70::func_slot6c()
{
}

/** @brief Report the default window callback result. @return Zero. */
u8 FieldClass15AE70::func_slotb0()
{
    return 0;
}

/** @brief Report the default window callback result. @return Zero. */
u8 FieldClass15AE70::func_slotb4()
{
    return 0;
}

/** @brief Leave the base window unchanged. */
void FieldClass15AE70::func_slot5c()
{
}

/** @brief Report whether window setup finished. @return Setup flag. */
u8 StatusResourceState::func_00261D20()
{
    return setup_complete;
}

/** @brief Get the loaded resource handle. @return Resource handle. */
u32 StatusResourceState::func_00263CC0()
{
    return resource;
}

/** @brief Report the status receiver type. @return Four. */
s32 StatusResourceState::func_001DF3D0()
{
    return 4;
}

/** @brief Get the record selection. @return Owned record selection. */
FieldRecordSelection* StatusResourceState::selected_records()
{
    return selection;
}

/** @brief Set the text window. @param value Window pointer to store. */
void StatusResourceState::func_00263C80(void* value)
{
    unk24 = value;
}

/** @brief Set the receiver byte. @param value Signed byte to store. */
void StatusResourceState::func_00263CA0(s8 value)
{
    unk28 = value;
}

/** @brief Get the receiver byte. @return Stored signed byte. */
s8 StatusResourceState::func_00263CB0()
{
    return unk28;
}

/** @brief Report the default command result. @return Zero. */
s32 StatusResourceState::func_slot60()
{
    return 0;
}

/** @brief Report the default command result. @return Zero. */
s32 StatusResourceState::func_slot64()
{
    return 0;
}

/** @brief Leave the resource state unchanged. */
void StatusResourceState::func_slot68()
{
}

/** @brief Default receiver callback with no action. */
void StatusResourceState::func_slot70()
{
}

/** @brief Default receiver callback with no action. */
void StatusResourceState::func_slot74()
{
}

/** @brief Default receiver callback with no action. */
void StatusResourceState::func_slot78()
{
}

/** @brief Default receiver callback returning zero. @return Zero. */
s32 StatusResourceState::func_slot7c()
{
    return 0;
}

/** @brief Default receiver callback returning zero. @return Zero. */
s32 StatusResourceState::func_slot80()
{
    return 0;
}

/** @brief Default receiver callback returning zero. @return Zero. */
s32 StatusResourceState::func_slot84()
{
    return 0;
}

/** @brief Allocate the sentinel and initialize the empty list. */
StatusItemWidgetList::StatusItemWidgetList()
{
    head = new (0) StatusWidgetNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

/** @brief Release the list nodes and sentinel storage. */
StatusItemWidgetList::~StatusItemWidgetList()
{
    status_clear_item_widgets(reinterpret_cast<StatusWidgetList*>(this));
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

void status_append_item_widget(StatusWidgetList* list, void* value)
{
    StatusWidgetNode* node = (StatusWidgetNode*)func_100AC0(8, 0);
    if (node != 0)
    {
        StatusWidgetNode* tail;
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

void status_clear_item_widgets(StatusWidgetList* list)
{
    StatusWidgetNode* node = list->head->next;
    if (node == 0)
    {
        return;
    }
    while (node != 0)
    {
        StatusWidgetNode* next = node->next;
        delete node;
        node = next;
    }
    list->head->next = 0;
    list->count = 0;
}

void status_append_name_widget(StatusWidgetList* list, void* value)
{
    StatusWidgetNode* node = (StatusWidgetNode*)func_100AC0(8, 0);
    if (node != 0)
    {
        StatusWidgetNode* tail;
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

/** @brief Allocate the sentinel and initialize the empty list. */
StatusNumericWidgetList::StatusNumericWidgetList()
{
    head = new (0) StatusWidgetNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

/** @brief Release the list nodes and sentinel storage. */
StatusNumericWidgetList::~StatusNumericWidgetList()
{
    status_clear_numeric_widgets(reinterpret_cast<StatusWidgetList*>(this));
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

void status_append_numeric_widget(StatusWidgetList* list, void* value)
{
    StatusWidgetNode* node = (StatusWidgetNode*)func_100AC0(8, 0);
    if (node != 0)
    {
        StatusWidgetNode* tail;
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

void status_clear_numeric_widgets(StatusWidgetList* list)
{
    StatusWidgetNode* node = list->head->next;
    if (node == 0)
    {
        return;
    }
    while (node != 0)
    {
        StatusWidgetNode* next = node->next;
        delete node;
        node = next;
    }
    list->head->next = 0;
    list->count = 0;
}

/** @brief Allocate the sentinel and initialize the empty list. */
StatusTextWidgetList::StatusTextWidgetList()
{
    head = new (0) StatusWidgetNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

/** @brief Release the list nodes and sentinel storage. */
StatusTextWidgetList::~StatusTextWidgetList()
{
    status_clear_text_widgets(reinterpret_cast<StatusWidgetList*>(this));
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

void status_append_text_widget(StatusWidgetList* list, void* value)
{
    StatusWidgetNode* node = (StatusWidgetNode*)func_100AC0(8, 0);
    if (node != 0)
    {
        StatusWidgetNode* tail;
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

void status_clear_text_widgets(StatusWidgetList* list)
{
    StatusWidgetNode* node = list->head->next;
    if (node == 0)
    {
        return;
    }
    while (node != 0)
    {
        StatusWidgetNode* next = node->next;
        delete node;
        node = next;
    }
    list->head->next = 0;
    list->count = 0;
}

void* status_list_node_at(void* list, s32 count)
{
    StatusWidgetNode* node = (*(StatusWidgetNode**)list)->next;
    s32 i;

    for (i = 0; i < count; i++)
    {
        if (node == 0)
        {
            return 0;
        }
        node = node->next;
    }
    return node;
}

void status_append_scissor_widget(StatusWidgetList* list, void* value)
{
    StatusWidgetNode* node = (StatusWidgetNode*)func_100AC0(8, 0);
    if (node != 0)
    {
        StatusWidgetNode* tail;
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
