#include "overlays/ctactics/ctactics.h"
#include "main/resident_data.h"
#include "main/resident_001001E0.h"
#include "main/resident_0010A0E0.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "overlays/1067-00/text_0028E240.h"
#include "overlays/1067-00/text_00212560.h"
#include "overlays/1067-00/text_002607B0.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_002D5260.h"
#include "overlays/1067-00/text_002D3BD0.h"
#include "overlays/1067-00/text_0023B1D0.h"
#include "overlays/1067-00/text_002CEAF0.h"
#include "overlays/1067-00/grid_marker.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_003F90C0.h"
#include "overlays/lib/scalar_indicator_inlines.h"
#include "overlays/lib/resource_widget_inlines.h"
#include "overlays/lib/movement_widget_inlines.h"

#define TACTICS_STAT_WORD_XOR_KEY 0x7DE3F7E3
#define TACTICS_STAT_HALFWORD_XOR_KEY 0x7E93

enum TacticsMessageKey
{
    TACTICS_MSG_TITLE = 0x2710,
    TACTICS_MSG_CHANGE_TACTICS = 0x2711,
    TACTICS_MSG_REPLACE = 0x2712,
    TACTICS_MSG_FORMATION = 0x2713,
    TACTICS_MSG_HELP_FIRST = 0x2714,
    TACTICS_MSG_CHANGE_TACTICS_HELP = 0x2714,
    TACTICS_MSG_REPLACE_HELP = 0x2719,
    TACTICS_MSG_FORMATION_HELP = 0x271A,
    TACTICS_MSG_HELP_END = 0x271C,
    TACTICS_MSG_EMPTY_ROW = 0x2720,
    TACTICS_MSG_LEFT_COLUMN_TITLE = 0x2721,
    TACTICS_MSG_RIGHT_COLUMN_TITLE = 0x2722,
    TACTICS_MSG_TACTICS_MENU = 0x2723,
    TACTICS_MSG_DEFAULT_HINT = 0x2724,
    TACTICS_MSG_LEVEL = 0x2725,
    TACTICS_MSG_HP = 0x2726,
    TACTICS_MSG_MP = 0x2727,
    TACTICS_MSG_VALUE_SEPARATOR = 0x2728,
    TACTICS_MSG_SET_LEADER = 0x2729,
    TACTICS_MSG_SET_LEADER_TITLE = 0x272A,
    TACTICS_MSG_LEADER = 0x272B,
    TACTICS_MSG_STRATEGY_NAME_BASE = 0x2968,
    TACTICS_MSG_ALT_STRATEGY_NAME_BASE = 0x296E,
    TACTICS_MSG_DUMMY = 0x29CC,
    TACTICS_MSG_CONFIRM_EXIT_TACTICS = 0x29CD,
    TACTICS_MSG_CONFIRM_EXIT_REPLACE = 0x29CE,
    TACTICS_MSG_CONFIRM_EXIT_FORMATION = 0x29CF,
    TACTICS_MSG_CONFIRM_EXIT = 0x29D0,
    TACTICS_MSG_STRATEGY_HELP_BASE = 0x29D1,
    TACTICS_MSG_ALT_STRATEGY_HELP_BASE = 0x29D7,
    TACTICS_MSG_STRATEGY_HINT = 0x29DD,
    TACTICS_MSG_REPLACEMENT_HINT = 0x29DE,
    TACTICS_MSG_FORMATION_HINT = 0x29DF,
    TACTICS_MSG_FORMATION_NAME_BASE = 0x2A30,
    TACTICS_MSG_FORMATION_HELP_BASE = 0x2A62,
    TACTICS_MSG_YES = 0x7E8,
    TACTICS_MSG_NO = 0x7E9
};

/** Coordinate selector owning its position list and selected entry. */
class TacticsCoordinateSelector : public LibClass175030
{
public:
    /** @brief Destroy the coordinate list and movement bases. */
    virtual ~TacticsCoordinateSelector();

    /** @brief Initialize the coordinate list and clear its selected entry. */
    TacticsCoordinateSelector()
    {
        selected = -1;
    }

    /** @brief Report the default list kind. @return Three. */
    virtual s32 get_default_list_kind();

    /** @brief Leave the default update hook unchanged. */
    virtual void update();

    /** @brief Leave the default notification hook unchanged. */
    virtual void func_003EEBE0();

    TacticsCoordinatePositionList nodes;

    s32 selected;
};

/**
 * @brief Delete an owned object and clear its pointer.
 * @param object Owned pointer to release, or null.
 */
template <class T>
static inline void delete_owned(T*& object)
{
    if (object != 0)
    {
        delete object;
        object = 0;
    }
}

/**
 * @brief Clear the grid window's selection state and resource keys.
 * @param object Grid window to reset.
 */
static inline void clear_grid_state(TacticsStrategyWindow* object)
{
    object->character_id = 0;
    object->selected_entry = 0;
    object->keys[0] = 0;
    object->keys[1] = 0;
    object->keys[2] = 0;
    object->keys[3] = 0;
    object->keys[4] = 0;
    object->keys[5] = 0;
}

/**
 * @brief Return the text key of a character's first battle strategy.
 * @param character_id Signed character ID.
 * @return First of the character's six consecutive strategy names, or TACTICS_MSG_DUMMY for an unknown character.
 */
static inline s32 first_strategy_text_key(s16 character_id)
{
    s32 first_key;

    switch (character_id)
    {
        case 1:
            first_key = TACTICS_MSG_STRATEGY_NAME_BASE;
            break;
        case 2:
            first_key = TACTICS_MSG_ALT_STRATEGY_NAME_BASE;
            break;
        case 3:
            first_key = TACTICS_MSG_STRATEGY_NAME_BASE;
            break;
        case 4:
            first_key = TACTICS_MSG_STRATEGY_NAME_BASE;
            break;
        case 5:
            first_key = TACTICS_MSG_STRATEGY_NAME_BASE;
            break;
        case 6:
            first_key = TACTICS_MSG_STRATEGY_NAME_BASE;
            break;
        case 7:
            first_key = TACTICS_MSG_STRATEGY_NAME_BASE;
            break;
        case 8:
            first_key = TACTICS_MSG_STRATEGY_NAME_BASE;
            break;
        case 9:
            first_key = TACTICS_MSG_ALT_STRATEGY_NAME_BASE;
            break;
        case 10:
            first_key = TACTICS_MSG_STRATEGY_NAME_BASE;
            break;
        default:
            first_key = TACTICS_MSG_DUMMY;
            break;
    }

    return first_key;
}

/** 0x114-byte character record with the character's name and chosen battle strategy. */
struct TacticsCharacterEquipment
{
    u8 unk00[0x20];

    char character_name[0x18];

    u8 battle_strategy;

    u8 previous_battle_strategy;

    u8 unk3a[0xDA];
};

/** Checksum-protected 0xC4-byte character statistics record with a signed character ID. */
class TacticsCharacterRecord
{
public:
    s16 character_id;

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
                encoded_flags = ((flags ^ TACTICS_STAT_WORD_XOR_KEY) | 1) ^ TACTICS_STAT_WORD_XOR_KEY;
                s32 current_key = checksum_salt;
                flags = encoded_flags;
                s32 current_experience = encoded_experience;
                flags_experience_checksum = current_key ^ (current_experience ^ (flags + current_key));
            }

            return 0;
        }

        return value ^ TACTICS_STAT_WORD_XOR_KEY;
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
                encoded_flags = ((flags ^ TACTICS_STAT_WORD_XOR_KEY) | 1) ^ TACTICS_STAT_WORD_XOR_KEY;
                s32 current_key = checksum_salt;
                flags = encoded_flags;
                s32 current_experience = encoded_experience;
                flags_experience_checksum = current_key ^ (current_experience ^ (flags + current_key));
            }

            return 0;
        }

        return value ^ TACTICS_STAT_WORD_XOR_KEY;
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
                encoded_flags = ((flags ^ TACTICS_STAT_WORD_XOR_KEY) | 1) ^ TACTICS_STAT_WORD_XOR_KEY;
                s32 current_key = checksum_salt;
                flags = encoded_flags;
                s32 current_experience = encoded_experience;
                flags_experience_checksum = current_key ^ (current_experience ^ (flags + current_key));
            }

            return 0;
        }

        return value ^ TACTICS_STAT_WORD_XOR_KEY;
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
                encoded_flags = ((flags ^ TACTICS_STAT_WORD_XOR_KEY) | 1) ^ TACTICS_STAT_WORD_XOR_KEY;
                s32 current_key = checksum_salt;
                flags = encoded_flags;
                s32 current_experience = encoded_experience;
                flags_experience_checksum = current_key ^ (current_experience ^ (flags + current_key));
            }

            return 0;
        }

        return value ^ TACTICS_STAT_WORD_XOR_KEY;
    }

    /** @brief Decode the protected level. @return Level, or one for an invalid checksum. */
    s32 get_level() const
    {
        if (level_checksum != (checksum_salt ^ (encoded_level ^ (encoded_base_level + checksum_salt))))
        {
            return 1;
        }

        return encoded_level ^ TACTICS_STAT_HALFWORD_XOR_KEY;
    }

    /** @brief Decode the protected flags. @return Flags, or five for an invalid checksum. */
    u32 get_flags() const
    {
        u32 experience = encoded_experience;

        if (flags_experience_checksum != (checksum_salt ^ (experience ^ (encoded_flags + checksum_salt))))
        {
            return 5;
        }

        return encoded_flags ^ TACTICS_STAT_WORD_XOR_KEY;
    }
};

/**
 * @brief Return a strategy name display from the strategy window's list.
 * @param object Strategy window containing the list.
 * @param index Node index.
 * @return Display payload stored in the indexed node.
 */
static inline LibObject178750* strategy_display(TacticsStrategyWindow* object, s32 index)
{
    return static_cast<LibObject178750*>(get_text_widget_node(
        &object->unk2c, index)->value);
}

/**
 * @brief Update a widget rectangle and request its refresh.
 * @param object Widget to position.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 */
static inline void set_widget_rectangle(LibClass178600* object, float x, float y,
    float width, float height)
{
    object->unk18.unk00 = x;
    object->unk18.unk04 = y;
    object->unk18.unk08 = width;
    object->unk18.unk0c = height;
    object->unk3c = 1;
}

/**
 * @brief Set both resource-display scales and request a refresh.
 * @param object Resource display to update.
 * @param scale Horizontal and vertical drawing scale.
 */
static inline void set_resource_display_scale(ItemCreationOptionResourceDisplay* object, float scale)
{
    object->unk50.unk34 = scale;
    object->unk50.unk30 = scale;
    object->unk3c = 1;
}

/** Partial aligned resource header with its size at offset 0x40. */
struct TacticsAlignedResource
{
    u8 unk00[0x40];

    s32 size;
};

/**
 * @brief Round the resource buffer to its next 128-byte boundary.
 * @param buffer Completed buffer containing the aligned header.
 * @return Header at the next aligned address, including an already aligned input.
 */
static inline TacticsAlignedResource* aligned_resource(void* buffer)
{
    return reinterpret_cast<TacticsAlignedResource*>((reinterpret_cast<u32>(buffer) + 0x7F) & ~0x7F);
}

/** Coordinate value and next link in an owned list. */
class TacticsCoordinateNode
{
public:
    float x;

    float y;

    TacticsCoordinateNode* next;

    /** @brief Initialize both coordinate components to zero. */
    TacticsCoordinateNode()
    {
        y = 0.0f;
        x = 0.0f;
    }

    /** @brief Finish the coordinate node lifetime. */
    ~TacticsCoordinateNode()
    {
    }
};

/** Partial associated window containing its movement target. */
struct TacticsAssociatedMovementRef
{
    u8 unk00[0xB8];

    LibClass175030* movement;
};

/** Partial resident menu state with the chosen formation and leader. */
typedef struct TacticsSavedFormation
{
    u8 pad_00[0x20];

    u8 formation;

    u8 leader_character_id;
} TacticsSavedFormation;

/** Partial runtime control state with its pending refresh byte. */
struct TacticsRuntimeControl
{
    u8 unk00[0x6E];

    u8 character_state_refresh_pending;
};

/** Partial callback directory containing its active native State. */
struct TacticsRuntimeCallbacks
{
    u8 unk00[0x14];

    FieldClass153E30* state;

    u8 unk18[2];

    u16 tactics_mode_flags;
};

/** Partial resident reference used by the tactics selection callbacks. */
typedef struct TacticsGridSelectionRef
{
    TacticsSavedFormation* state;

    TacticsCharacterRecord* character_records;

    TacticsCharacterEquipment* equipment_records;

    FieldClass153E00* runtime;

    TacticsRuntimeCallbacks* callbacks;

    u8 pad_14[0xC];

    FieldBufferSlots* resources;
} TacticsGridSelectionRef;

extern "C" TacticsGridSelectionRef* D_001B643C;

extern "C" LibWidgetColors4C5590 g_tactics_strategy_title_colors;

extern "C" LibWidgetColors4C5590 g_tactics_leader_title_colors;

extern "C" LibWidgetColors4C5590 g_tactics_exit_confirm_title_colors;

/** "DUMMY", the initial text of the character name labels. */
extern "C" const char g_tactics_dummy_text[];

static inline bool tactics_selection_inactive(TacticsCoordinateSelector* selection);

static inline u8 tactics_grid_empty(FieldObject23CEA0* grid);

static inline void set_display_position(ItemCreationOptionResourceDisplay* display, float x, float y);

static inline void refresh_formation(TacticsFormationWindow* object, s16 selected_entry);

static inline bool resource_code_empty(u8 code);

static inline float shifted_position(const float& origin, float offset);

static inline bool coordinate_records_ready(TacticsChangeWindow* object);

static inline void append_position(TacticsCoordinateSelector* widget, float x, float y);

static inline bool initialize_selector_records(TacticsReplaceWindow* object);

static inline s32 record_character_id(TacticsCharacterRecord* record);

static inline u8 character_record_empty(const TacticsCharacterRecord* record);

/**
 * @brief Report whether the grid's control byte is clear.
 * @param grid Field grid containing the control byte.
 * @return One when the control byte is zero; otherwise zero.
 */
static inline u8 tactics_grid_empty(FieldObject23CEA0* grid)
{
    return !grid->unk35;
}

/**
 * @brief Test whether the selection control byte is clear.
 * @param selection Field coordinate selector.
 * @return True when the control byte is zero.
 */
static inline bool tactics_selection_inactive(TacticsCoordinateSelector* selection)
{
    return !selection->unk35;
}

/**
 * @brief Move a resource display and request its refresh.
 * @param display Resource display to move.
 * @param x Horizontal position.
 * @param y Vertical position.
 */
static inline void set_display_position(ItemCreationOptionResourceDisplay* display, float x, float y)
{
    display->unk18.unk00 = x;
    display->unk18.unk04 = y;
    display->unk3c = 1;
}

/**
 * @brief Color the selected name, dim the others, and move the cursor to the selection.
 * @param window Leader window holding the names and cursor.
 * @param selected_entry Name to highlight.
 */
static inline void highlight_candidate(TacticsLeaderWindow* window, s32 selected_entry)
{
    s32 index = 0;
    FieldListNode* node = window->unk44.head->next;

    while (node != 0)
    {
        LibObject175140* name = static_cast<LibObject175140*>(node->value);

        if (index == selected_entry)
        {
            name->set_color(0x288080);
            func_0023B9B0(window->cursor, selected_entry, func_00467950(name)->unk08);
        }
        else
        {
            name->set_color(0x808080);
        }

        node = node->next;
        index++;
    }
}

/**
 * @brief Return a party name label from the leader window's list.
 * @param object Leader window containing the list.
 * @param index Display index.
 * @return Name label stored in the selected list node.
 */
static inline LibObject175140* candidate_display(TacticsLeaderWindow* object, s32 index)
{
    return static_cast<LibObject175140*>(get_widget_node_at_index(
        &object->unk44, index)->value);
}

/**
 * @brief Test whether a resource slot has no entry code.
 * @param resource Record selection containing the slot codes.
 * @param index Signed resource slot index.
 * @return True when the slot's entry code is zero.
 */
static inline bool party_slot_empty(FieldRecordSelection* resource, s16 index)
{
    return !static_cast<u8>(resource->slots[index]);
}

/**
 * @brief Fit the indicator to the selected name's position and drawing width.
 * @param object Leader window whose selected name supplies the rectangle.
 */
static inline void position_candidate_indicator(TacticsLeaderWindow* object)
{
    if (candidate_display(object, object->candidate_indices_by_slot[object->selected]) != 0)
    {
        LibUiRect16* position = &candidate_display(object,
            object->candidate_indices_by_slot[object->selected])->unk18;
        LibBounds4C69B0* bounds = func_00467950(candidate_display(object,
            object->candidate_indices_by_slot[object->selected]));
        set_widget_rectangle(object->indicator, position->unk00, position->unk04,
            bounds->unk08, 24.0f);
    }
}

/**
 * @brief Color the selected text entry, dim the others, and move the cursor to the selection.
 * @param window Formation window holding the text list and cursor.
 * @param selected_entry Entry to highlight.
 */
static inline void highlight_text(TacticsFormationWindow* window, s32 selected_entry)
{
    s32 index = 0;
    FieldListNode* node = window->unk2c.head->next;

    while (node != 0)
    {
        LibObject178750* text = static_cast<LibObject178750*>(node->value);

        if (index == selected_entry)
        {
            text->set_color(0x288080);
            func_0023B9B0(window->cursor, selected_entry, lib_text_measure_bounds(text)->unk08);
        }
        else
        {
            text->set_color(0x808080);
        }

        node = node->next;
        index++;
    }
}

/**
 * @brief Show the selected formation's description and highlight its name.
 * @param object Formation window holding the description, text list, and cursor.
 * @param selected_entry Selected grid entry.
 */
static inline void refresh_formation(TacticsFormationWindow* object, s16 selected_entry)
{
    lib_text_set_resource(object->title, object->func_slot54(), selected_entry + TACTICS_MSG_FORMATION_HELP_BASE, 0);
    s32 selected = selected_entry;
    highlight_text(object, selected);
}

/**
 * @brief Test whether a resource code is zero.
 * @param code Resource code.
 * @return True when the code is zero.
 */
static inline bool resource_code_empty(u8 code)
{
    return !code;
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
 * @brief Test that the coordinate window's paired record arrays are present.
 * @param object Coordinate window holding the array links.
 * @return One when both links exist, otherwise zero.
 */
static inline bool coordinate_records_ready(TacticsChangeWindow* object)
{
    if (object->character_records == 0 || object->equipment_records == 0)
    {
        return false;
    }

    return true;
}

/**
 * @brief Append a coordinate pair to the widget's position list.
 * @param widget Coordinate widget owning the list.
 * @param x Horizontal coordinate.
 * @param y Vertical coordinate.
 */
static inline void append_position(TacticsCoordinateSelector* widget, float x, float y)
{
    append_coordinate_pair(&widget->nodes, TacticsPresetPosition(x, y));
}

/**
 * @brief Bind the paired record arrays and allocate cleared swap buffers.
 * @param object Selector window holding the records and buffers.
 * @return True when all four links exist, otherwise false.
 */
static inline bool initialize_selector_records(TacticsReplaceWindow* object)
{
    object->character_records = D_001B643C->character_records;
    object->equipment_records = D_001B643C->equipment_records;
    object->character_record_buffer = new (0) TacticsCharacterRecord;
    object->equipment_record_buffer = new (0) TacticsCharacterEquipment;

    if (object->character_records == 0 || object->equipment_records == 0 || object->character_record_buffer == 0 || object->equipment_record_buffer == 0)
    {
        return false;
    }

    func_0013A678(object->character_record_buffer, 0, sizeof(TacticsCharacterRecord));
    func_0013A678(object->equipment_record_buffer, 0, sizeof(TacticsCharacterEquipment));
    return true;
}

/**
 * @brief Read a character record's character ID.
 * @param record Character record.
 * @return Signed character ID.
 */
static inline s32 record_character_id(TacticsCharacterRecord* record)
{
    return record->character_id;
}

/**
 * @brief Test whether a character slot holds no character.
 * @param record Character record.
 * @return Nonzero when the character ID is zero.
 */
static inline u8 character_record_empty(const TacticsCharacterRecord* record)
{
    return !record->character_id;
}

/** @brief Leave the default update hook unchanged. */
void TacticsCoordinateSelector::update()
{
}

/**
 * @brief Highlight the text display for the selected grid entry.
 * @param selected Entry to highlight.
 */
void TacticsExitConfirmWindow::func_slotf8(s16 selected)
{
    s32 index = 0;
    FieldListNode* node = unk2c.head->next;

    while (node != 0)
    {
        LibObject178750* text = static_cast<LibObject178750*>(node->value);

        if (index == selected)
        {
            text->set_color(0x288080);
        }
        else
        {
            text->set_color(0x808080);
        }

        node = node->next;
        index++;
    }
}

/** @brief Compare the State's active window with this window; neither outcome has further work. */
void TacticsExitConfirmWindow::func_slot5c()
{
    if (D_001B643C->callbacks->state->func_00261150() != this)
    {
        return;
    }
}

/** @brief Return the associated object. @return Stored object. */
void* FieldClass153E30::func_00261150()
{
    return unk20;
}

/** @brief Move to the following grid entry and update its text highlight. */
void TacticsExitConfirmWindow::func_slot6c()
{
    if (grid->process_direction(1) != 1)
    {
        func_slotf8(grid->unk114);
    }
}

/** @brief Move to the preceding grid entry and update its text highlight. */
void TacticsExitConfirmWindow::func_slot68()
{
    if (grid->process_direction(0) != 1)
    {
        func_slotf8(grid->unk114);
    }
}

/**
 * @brief Close the child window and restore the associated window's movement.
 * @return Two after restoring the associated window and queuing removal.
 */
u8 TacticsExitConfirmWindow::func_slotb4()
{
    FieldClass15AE70::func_slot18(0, 0x7F);
    LibClass175030* movement = static_cast<TacticsAssociatedMovementRef*>(func_slot44())->movement;
    movement->unk30 = 128.0f;
    movement->unk3c = 1;
    FieldClass153E30* state = D_001B643C->callbacks->state;
    state->func_00263C70(func_slot44());
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->callbacks), this);
    return 2;
}

/** @brief Store the associated object. @param value Object to store. */
void FieldClass153E30::func_00263C70(void* value)
{
    unk20 = value;
}

/**
 * @brief On Yes, refresh any pending character state and leave the setup; on No, close this window.
 * @return One after Yes; two after No closes the window.
 */
u8 TacticsExitConfirmWindow::func_slotb0()
{
    selected = grid->unk114;
    u8 result = 0;

    if (selected == 0)
    {
        if (reinterpret_cast<TacticsRuntimeControl*>(D_001B643C->runtime)->character_state_refresh_pending != 0)
        {
            ResidentContextObject38* context = D_001B6430->context->unk38;
            reinterpret_cast<FieldClass151D40*>(context)->refresh_field_character_state();
            reinterpret_cast<TacticsRuntimeControl*>(D_001B643C->runtime)->character_state_refresh_pending = 0;
        }

        set_state(0xFF, 0x80);
    }
    else
    {
        result = func_slotb4();
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

/**
 * @brief Create the child window's two-entry grid, panels, and text displays.
 * @param associated Full resource source word forwarded to the base and displays.
 * @param x Horizontal window position.
 * @param y Vertical window position.
 * @param code Base window initializer code.
 * @param text_key Text key for the heading display.
 * @return One after initialization, or zero when a required display or grid is absent.
 */
s32 TacticsExitConfirmWindow::func_slotf4(u32 associated, float x, float y,
    s32 code, s32 text_key)
{
    FieldClass15AE70::func_slot10(associated, x, y, code);
    LibWidgetColors4C5590 colors = g_tactics_exit_confirm_title_colors;
    LibClass178630* title_panel = new (0) LibClass178630;
    LibClass178630* panel = new (0) LibClass178630;
    lib_panel_init_rectangle(panel, 1, 0.0f, 0.0f, 290.0f, 208.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    append_panel_widget_node(&unk14, panel);
    lib_panel_init_rectangle(title_panel, 1, 0.0f, 0.0f, 290.0f, 40.0f, 88.0f);
    lib_panel_set_colors(title_panel, &colors);
    lib_container_attach_widget(unk10, title_panel);
    append_panel_widget_node(&unk14, title_panel);
    LibObject178750* first = new (0) LibObject178750;
    LibObject178750* second = new (0) LibObject178750;
    LibObject178750* heading = new (0) LibObject178750;
    LibObject178750* notice = new (0) LibObject178750;
    grid = new (0) FieldObject23CEA0;

    if (first == 0 || second == 0 || heading == 0 || grid == 0)
    {
        return 0;
    }

    lib_text_init_resource_rectangle(first, associated, TACTICS_MSG_YES, 0, 110.0f, 132.0f, 0.0f, 0.0f);
    lib_text_init_resource_rectangle(second, associated, TACTICS_MSG_NO, 0, 110.0f, 168.0f, 0.0f, 0.0f);
    lib_text_init_resource_rectangle(heading, associated, text_key, 0, 24.0f, 64.0f, 0.0f, 0.0f);
    lib_text_init_resource_rectangle(notice, associated, TACTICS_MSG_CONFIRM_EXIT, 0, 0.0f, 8.0f, 290.0f, 40.0f);
    notice->set_mode(1);
    lib_container_attach_widget(unk10, first);
    lib_container_attach_widget(unk10, second);
    lib_container_attach_widget(unk10, heading);
    lib_container_attach_widget(unk10, notice);
    append_text_widget_node(&unk2c, first);
    append_text_widget_node(&unk2c, second);
    append_text_widget_node(&unk2c, heading);
    append_text_widget_node(&unk2c, notice);
    grid->func_0023CE80(1, 2);
    grid->func_0023CE60(0.0f, 36.0f);
    grid->unkF2 = 0;
    grid->func_0023CF50(1, 110.0f + x, 132.0f + y);
    append_grid_widget_node(&unk74, grid);
    func_slotf8(grid->unk114);
    return 1;
}

/** @brief Destroy the child window's base. */
TacticsExitConfirmWindow::~TacticsExitConfirmWindow()
{
}

/** @brief Move to the following grid entry and update the name highlight. */
void TacticsLeaderWindow::func_slot6c()
{
    if (candidate_count != 1)
    {
        if (grid->process_direction(1) != 1)
        {
            highlight_candidate(this, grid->unk114);
        }
    }
}

/** @brief Move to the preceding grid entry and update the name highlight. */
void TacticsLeaderWindow::func_slot68()
{
    if (candidate_count != 1)
    {
        if (grid->process_direction(0) != 1)
        {
            highlight_candidate(this, grid->unk114);
        }
    }
}

/**
 * @brief Restore the saved grid entry, refresh its highlight, and return to the associated window.
 * @return Two after restoring the associated window.
 */
u8 TacticsLeaderWindow::func_slotb4()
{
    FieldObject23CEA0* selected_grid = grid;

    if (selected_grid != 0)
    {
        selected_grid->index = candidate_indices_by_slot[selected];
        func_0023CB30(selected_grid);
        func_0023CEE0(reinterpret_cast<FieldObject23CEB0*>(grid));
        grid->unkad = 0;
    }

    highlight_candidate(this, candidate_indices_by_slot[selected]);

    func_slot20(0);
    FieldClass15AE70* parent = static_cast<FieldClass15AE70*>(func_slot44());
    parent->func_slot64();
    D_001B643C->callbacks->state->func_00263C70(parent);
    return 2;
}

/**
 * @brief Save the chosen character ID and update the parent label.
 * @return One after the selected character ID is applied.
 */
u8 TacticsLeaderWindow::func_slotb0()
{
    for (s32 index = 0; index < 3; index++)
    {
        if (candidate_indices_by_slot[index] == grid->unk114)
        {
            selected = index;
        }
    }

    D_001B643C->state->leader_character_id = character_ids[candidate_indices_by_slot[selected]];

    if (candidate_display(this, candidate_indices_by_slot[selected]) != 0)
    {
        position_candidate_indicator(this);
    }

    set_leader(static_cast<TacticsFormationWindow*>(func_slot44()), character_ids[candidate_indices_by_slot[selected]]);
    return 1;
}

/**
 * @brief Initialize the party names, grid, cursor, and indicator.
 * @param associated Full resource source word forwarded to the base and title.
 * @return Zero when a panel allocation or resource link fails; otherwise one.
 */
s32 TacticsLeaderWindow::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 200.0f, 136.0f, 8);
    LibClass178630* panel = new (0) LibClass178630;

    if (panel == 0)
    {
        return 0;
    }

    lib_panel_init_rectangle(panel, 1, 0.0f, 0.0f, 232.0f, 148.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    append_panel_widget_node(&unk14, panel);
    LibClass178630* title_panel = new (0) LibClass178630;

    if (title_panel == 0)
    {
        return 0;
    }

    lib_panel_init_rectangle(title_panel, 1, 0.0f, 0.0f, 232.0f, 40.0f, 88.0f);
    LibWidgetColors4C5590 colors = g_tactics_leader_title_colors;
    lib_panel_set_colors(title_panel, &colors);
    lib_container_attach_widget(unk10, title_panel);
    append_panel_widget_node(&unk14, title_panel);
    LibObject178750* title = new (0) LibObject178750;
    lib_text_init_resource_rectangle(title, associated, TACTICS_MSG_SET_LEADER_TITLE, 1, 42.0f, 8.0f, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, title);

    if (record_selection == 0)
    {
        return 0;
    }

    selected = -1;
    u8 character_id;
    s32 icon_index = 0;
    u8 saved_character_id = D_001B643C->state->leader_character_id;
    candidate_count = 0;

    for (s32 index = 0; index < 3; index++)
    {
        candidate_indices_by_slot[index] = 0;
        character_id = static_cast<u8>(record_selection->slots[static_cast<s16>(index)]);

        if (character_id != 0)
        {
            LibObject175140* name = new (0) LibObject175140;
            float y = 48.0f + 28.0f * candidate_count;
            name->func_00467AD0(24.0f, y, 0.0f, 0.0f,
                reinterpret_cast<const char*>(&static_cast<TacticsCharacterEquipment*>(
                    record_selection->unk04)[static_cast<s16>(index)]) + 0x20, 0);
            lib_container_attach_widget(unk10, name);
            append_icon_widget_node(&unk44, name);
            candidate_indices_by_slot[index] = icon_index;
            icon_index++;
            character_ids[candidate_count++] = character_id;

            if (saved_character_id == character_id)
            {
                selected = index;
            }
        }
    }

    if (selected == -1)
    {
        for (s32 index = 0; index < 3; index++)
        {
            if (party_slot_empty(record_selection, index))
            {
                continue;
            }

            selected = index;
            break;
        }
    }

    if (selected == -1)
    {
        selected = 0;
    }

    base_x = 224.0f;
    base_y = 184.0f;
    grid = new (0) FieldObject23CEA0;
    grid->func_0023CE80(1, candidate_count);
    grid->func_0023CE60(0.0f, 28.0f);
    grid->unkF2 = 0;
    grid->func_0023CF50(0, base_x, base_y);
    FieldObject23CEA0* selected_grid = grid;
    selected_grid->index = candidate_indices_by_slot[selected];
    func_0023CB30(selected_grid);
    func_0023CEE0(reinterpret_cast<FieldObject23CEB0*>(grid));
    append_grid_widget_node(&unk74, grid);
    cursor = new (0) FieldObject23BE00;
    cursor->func_0023BB20(24.0f, 48.0f, 120.0f, 1.0f, grid, 0x288080);
    lib_container_attach_widget(unk10, cursor);
    append_cursor_widget_node(&unk8c, cursor);
    indicator = new (0) ItemCreationClass172600;
    func_0041AD10(indicator, base_x, base_y, 144.0f, 24.0f);
    lib_container_attach_widget(unk10, indicator);
    highlight_candidate(this, candidate_indices_by_slot[selected]);

    if (candidate_display(this, candidate_indices_by_slot[selected]) != 0)
    {
        position_candidate_indicator(this);
    }

    return 1;
}

/** @brief Destroy the leader window's base. */
TacticsLeaderWindow::~TacticsLeaderWindow()
{
}

/**
 * @brief Restore the leader window's grid and highlight, then activate it.
 * @return One after activating the leader window.
 */
u8 TacticsFormationWindow::func_slotb8()
{
    ItemCreationClass174C40* widget = resource_widget;

    if (widget != 0)
    {
        widget->unkd0 = 0x32;
        widget->unk3c = 1;
    }

    FieldObject23CEA0* parent_grid = grid;

    if (parent_grid != 0)
    {
        parent_grid->FieldClass151C50::unk30 = 64.0f;
        parent_grid->unkae = 1;
    }

    TacticsLeaderWindow* child = static_cast<TacticsLeaderWindow*>(func_slot4c());
    FieldObject23CEA0* selected_grid = child->grid;

    if (selected_grid != 0)
    {
        selected_grid->index = child->candidate_indices_by_slot[child->selected];
        func_0023CB30(selected_grid);
        func_0023CEE0(reinterpret_cast<FieldObject23CEB0*>(child->grid));
        child->grid->unkad = 1;
    }

    highlight_candidate(child, child->candidate_indices_by_slot[child->selected]);

    child->func_slot20(1);
    D_001B643C->callbacks->state->func_00263C70(child);
    return 1;
}

/** @brief Return the alternate associated window. @return Stored window pointer. */
void* FieldClass15AE70::func_slot4c()
{
    return unk9c;
}

/**
 * @brief Open the selection child for an enabled grid, or update the control-mode flags.
 * @return Two after the action, or zero for a disabled grid or an absent runtime or child.
 */
u8 TacticsFormationWindow::func_slotb4()
{
    if (tactics_grid_empty(grid) == 1)
    {
        return 0;
    }

    FieldClass153E00* runtime = D_001B643C->runtime;

    if (!runtime)
    {
        return 0;
    }

    u8 control_mode = runtime->unk2d != 0;

    if (control_mode == 1)
    {
        set_state(1, 0x80);
    }
    else
    {
        TacticsExitConfirmWindow* child = new (0) TacticsExitConfirmWindow;

        if (!child)
        {
            return 0;
        }

        child->func_slotf4(func_slot54(), 175.0f, 160.0f, 5, TACTICS_MSG_CONFIRM_EXIT_FORMATION);
        child->func_slot40(this);
        D_001B643C->callbacks->state->add_child(child);
        D_001B643C->callbacks->state->func_00263C70(child);
    }

    return 2;
}

/** @brief Return the stored resource source word. @return Stored word. */
u32 FieldClass15AE70::func_slot54()
{
    return unk04;
}

/**
 * @brief Save the enabled grid selection and fit the indicator to its text.
 * @return Zero when the grid's control byte is clear; otherwise one.
 */
u8 TacticsFormationWindow::func_slotb0()
{
    if (tactics_grid_empty(grid) == 1)
    {
        return 0;
    }

    selected = grid->unk114;
    D_001B643C->state->formation = selected;
    LibUiRect16* position = &static_cast<LibObject178750*>(get_text_widget_node(
        &unk2c, selected)->value)->unk18;
    LibBounds4C69B0* bounds = lib_text_measure_bounds(static_cast<LibObject178750*>(get_text_widget_node(
        &unk2c, selected)->value));
    set_widget_rectangle(indicator, position->unk00, position->unk04, bounds->unk08, 24.0f);
    return 1;
}

/** @brief Move to the following formation and update its description, cursor, and character positions. */
void TacticsFormationWindow::func_slot6c()
{
    if (grid->process_direction(1) != 1)
    {
        position_formation_characters(this);

        if (grid != 0)
        {
            s32 selected_entry = grid->unk114;
            refresh_formation(this, selected_entry);
        }
    }
}

/** @brief Move to the preceding formation and update its description, cursor, and character positions. */
void TacticsFormationWindow::func_slot68()
{
    if (grid->process_direction(0) != 1)
    {
        position_formation_characters(this);

        if (grid != 0)
        {
            s32 selected_entry = grid->unk114;
            refresh_formation(this, selected_entry);
        }
    }
}

/** @brief Restore the grid and resource widget movement flags. */
void TacticsFormationWindow::func_slot64()
{
    FieldObject23CEA0* parent_grid = grid;

    if (parent_grid != 0)
    {
        parent_grid->FieldClass151C50::unk30 = 128.0f;
        parent_grid->unkae = 1;
    }

    ItemCreationClass174C40* widget = resource_widget;

    if (widget != 0)
    {
        widget->unkd0 = 0x22;
        widget->unk3c = 1;
    }
}

/**
 * @brief Place the party's character displays at the selected formation's positions.
 * @param object Formation window holding the grid, character displays, and base coordinates.
 */
void position_formation_characters(TacticsFormationWindow* object)
{
    if (object->grid != 0)
    {
        float first = 0.0f;
        float second = 0.0f;
        s16 index = object->grid->unk114;

        if (object->character_displays[0] != 0)
        {
            func_00408600(index, 0, &first, &second);
            first /= 42.0f;
            second /= 42.0f;
            first -= 10.0f + 0.2f * (250.0f - second);
            set_display_position(object->character_displays[0], -14.400001f + (object->base_x + first),
                -16.0f + (object->base_y + second));
        }

        if (object->character_displays[1] != 0)
        {
            func_00408600(index, 1, &first, &second);
            first /= 42.0f;
            second /= 42.0f;
            first -= 10.0f + 0.2f * (250.0f - second);
            set_display_position(object->character_displays[1], -14.400001f + (object->base_x + first),
                -16.0f + (object->base_y + second));
        }

        if (object->character_displays[2] != 0)
        {
            func_00408600(index, 2, &first, &second);
            first /= 42.0f;
            second /= 42.0f;
            first -= 10.0f + 0.2f * (250.0f - second);
            set_display_position(object->character_displays[2], -14.400001f + (object->base_x + first),
                -16.0f + (object->base_y + second));
        }
    }
}

/**
 * @brief Select the character ID in the parent and point its label at the matching record's text.
 * @param object Formation window.
 * @param character_id Full character code; zero selects code 1.
 */
void set_leader(TacticsFormationWindow* object, u32 character_id)
{
    s32 code = static_cast<u8>(character_id ? character_id : 1);
    u8 selected = 0;
    s32 index;

    for (index = 0; index < 3; index++)
    {
        if (object->character_ids[index] == code)
        {
            selected = index;
        }
    }

    if (selected == 0)
    {
        for (index = 0; index < 3; index++)
        {
            u8 slot_code = object->character_ids[index];

            if (!resource_code_empty(slot_code))
            {
                selected = index;
                D_001B643C->state->leader_character_id = slot_code;
                break;
            }
        }
    }

    LibObject175140* label = object->label;
    label->unkfc =
        static_cast<TacticsCharacterEquipment*>(object->record_selection->unk04)[static_cast<s16>(selected)].character_name;
    label->unk3c = 1;
}

/**
 * @brief Update the formation window's character positions, description, highlight, and indicator.
 * @param object Formation window to refresh.
 */
void refresh_formation_display(TacticsFormationWindow* object)
{
    position_formation_characters(object);

    if (object->grid != 0)
    {
        s32 selected_entry = object->grid->unk114;
        refresh_formation(object, selected_entry);
    }

    LibUiRect16* position = &static_cast<LibObject178750*>(get_text_widget_node(
        &object->unk2c, object->selected)->value)->unk18;
    LibBounds4C69B0* bounds = lib_text_measure_bounds(static_cast<LibObject178750*>(get_text_widget_node(
        &object->unk2c, object->selected)->value));
    set_widget_rectangle(object->indicator, position->unk00, position->unk04, bounds->unk08, 24.0f);
}

/**
 * @brief Create the formation window's grid, character displays, and leader label.
 * @param associated Full resource source word forwarded to the base and text widgets.
 * @return One after initialization, or zero when the resource selection or a panel is absent.
 */
s32 TacticsFormationWindow::func_slotf4(u32 associated)
{
    if (record_selection == 0)
    {
        return 0;
    }

    FieldClass15AE70::func_slot10(associated, 16.0f, 72.0f, 9);
    LibClass178630* panel = new (0) LibClass178630;

    if (panel == 0)
    {
        return 0;
    }

    lib_panel_init_rectangle(panel, 1, 0.0f, 0.0f, 288.0f, 392.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    append_panel_widget_node(&unk14, panel);
    LibClass178630* resource_panel = new (0) LibClass178630;

    if (resource_panel == 0)
    {
        return 0;
    }

    lib_panel_init_rectangle(resource_panel, 1, 240.0f, 0.0f, 368.0f, 108.0f, 88.0f);
    lib_container_attach_widget(unk10, resource_panel);
    append_panel_widget_node(&unk14, resource_panel);

    for (s32 index = 0; index < 10; index++)
    {
        LibObject178750* display = new (0) LibObject178750;
        lib_text_init_resource_rectangle(display, associated, TACTICS_MSG_FORMATION_NAME_BASE + index, 0,
            24.0f, 24.0f + 28.0f * index, 0.0f, 0.0f);
        lib_container_attach_widget(unk10, display);
        append_text_widget_node(&unk2c, display);
    }

    title = new (0) LibObject178750;
    lib_text_init_resource_rectangle(title, associated, TACTICS_MSG_FORMATION_HELP_BASE, 0, 256.0f, 16.0f, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, title);
    grid = new (0) FieldObject23CEA0;
    grid->func_0023CE80(1, 10);
    grid->func_0023CE60(0.0f, 28.0f);
    grid->unkF2 = 0;
    grid->func_0023CF50(selected, 32.0f, 96.0f);
    FieldObject23CEA0* selection = grid;
    selection->index = selected;
    func_0023CB30(selection);
    func_0023CEE0(reinterpret_cast<FieldObject23CEB0*>(grid));
    append_grid_widget_node(&unk74, grid);
    cursor = new (0) FieldObject23BE00;
    cursor->func_0023BB20(24.0f, 24.0f, 120.0f, 1.0f, grid, 0x288080);
    lib_container_attach_widget(unk10, cursor);
    append_cursor_widget_node(&unk8c, cursor);
    indicator = new (0) ItemCreationClass172600;
    func_0041AD10(indicator, 24.0f, 24.0f, 144.0f, 24.0f);
    lib_container_attach_widget(unk10, indicator);
    resource_widget = new (0) ItemCreationClass174C40;
    lib_indexed_resource_init(resource_widget, 0x22, 32.0f, 348.0f);
    lib_container_attach_widget(unk10, resource_widget);
    LibObject178750* resource_heading = new (0) LibObject178750;
    lib_text_init_resource_rectangle(resource_heading, associated, TACTICS_MSG_SET_LEADER, 0, 72.0f, 352.0f, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, resource_heading);
    u8 saved_entry = D_001B643C->state->leader_character_id;
    u16 resource_index = 0;
    func_0013A678(character_ids, 0, 3);

    for (s32 index = 0; index < 3; index++)
    {
        character_ids[index] = record_selection->slots[static_cast<s16>(index)];

        if (character_ids[index] == saved_entry)
        {
            resource_index = index;
        }
    }

    base_x = 320.0f;
    base_y = 132.0f;
    float heading_y = base_y - 24.0f;
    LibObject178750* selected_heading = new (0) LibObject178750;
    selected_heading->init_resource_rectangle(322.0f, heading_y, 0.0f, 0.0f, associated, TACTICS_MSG_LEADER, 1);
    selected_heading->set_color(0x288080);
    lib_container_attach_widget(unk10, selected_heading);
    label = new (0) LibObject175140;
    label->func_00467AD0(434.0f, heading_y, 0.0f, 0.0f,
        static_cast<TacticsCharacterEquipment*>(record_selection->unk04)[static_cast<s16>(resource_index)].character_name, 0);
    lib_container_attach_widget(unk10, label);
    ItemCreationOptionResourceDisplay* display = new (0) ItemCreationOptionResourceDisplay;
    void* allocation = field_get_aligned_allocation(D_001B643C->resources, 0);
    FieldResourceRecord* record = field_find_resource_record(D_001B643C->resources, 8);
    display->unkcc = allocation;
    display->unkd0 = 0;
    func_002D6440(display, record, base_x, base_y);
    set_resource_display_scale(display, 2.5f);
    lib_container_attach_widget(unk10, display);

    if (character_ids[0] != 0)
    {
        character_displays[0] = new (0) ItemCreationOptionResourceDisplay;
    }

    if (character_ids[1] != 0)
    {
        character_displays[1] = new (0) ItemCreationOptionResourceDisplay;
    }

    if (character_ids[2] != 0)
    {
        character_displays[2] = new (0) ItemCreationOptionResourceDisplay;
    }

    FieldResourceRecord* default_record = static_cast<FieldResourceRecord*>(field_get_builtin_resource_data(D_001B643C->resources, 0));

    if (character_displays[2] != 0)
    {
        character_displays[2]->unkcc = field_get_aligned_allocation(D_001B643C->resources, character_ids[2]);
        character_displays[2]->unkd0 = character_ids[2];
        func_002D6440(character_displays[2], default_record, base_x, base_y);
        set_resource_display_scale(character_displays[2], 0.4f);
        lib_container_attach_widget(unk10, character_displays[2]);
    }

    if (character_displays[1] != 0)
    {
        character_displays[1]->unkcc = field_get_aligned_allocation(D_001B643C->resources, character_ids[1]);
        character_displays[1]->unkd0 = character_ids[1];
        func_002D6440(character_displays[1], default_record, base_x, base_y);
        set_resource_display_scale(character_displays[1], 0.4f);
        lib_container_attach_widget(unk10, character_displays[1]);
    }

    if (character_displays[0] != 0)
    {
        character_displays[0]->unkcc = field_get_aligned_allocation(D_001B643C->resources, character_ids[0]);
        character_displays[0]->unkd0 = character_ids[0];
        func_002D6440(character_displays[0], default_record, base_x, base_y);
        set_resource_display_scale(character_displays[0], 0.4f);
        lib_container_attach_widget(unk10, character_displays[0]);
    }

    highlight_text(this, selected);

    refresh_formation_display(this);
    return 1;
}

/** @brief Leave the base destructor unchanged. */
ItemCreationClass175110::~ItemCreationClass175110()
{
}

/** @brief Destroy the formation window base. */
TacticsFormationWindow::~TacticsFormationWindow()
{
}

/** @brief Clear the displays and restore the resident grid selection. */
TacticsFormationWindow::TacticsFormationWindow()
{
    title = 0;
    grid = 0;
    cursor = 0;
    indicator = 0;
    resource_widget = 0;
    record_selection = 0;
    character_displays[0] = 0;
    character_displays[1] = 0;
    character_displays[2] = 0;
    func_0013A678(character_ids, 0, 3);
    selected = D_001B643C->state->formation;
    base_x = 0.0f;
    base_y = 0.0f;
    label = 0;
}

/**
 * @brief Advance the chosen selector one entry, wrapping after its eighth entry.
 */
void TacticsReplaceWindow::func_slot6c()
{
    TacticsCoordinateSelector* selection;

    if (use_second)
    {
        selection = second_selector;
    }
    else
    {
        selection = first_selector;
    }

    if (tactics_selection_inactive(selection))
    {
        return;
    }

    s32 index = selection->selected + 1;

    if (index >= 8)
    {
        index = 0;
    }

    func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(selection), index, 0);
}

/**
 * @brief Move the chosen selector back one entry, wrapping to its eighth entry.
 */
void TacticsReplaceWindow::func_slot68()
{
    TacticsCoordinateSelector* selection;

    if (use_second)
    {
        selection = second_selector;
    }
    else
    {
        selection = first_selector;
    }

    if (tactics_selection_inactive(selection))
    {
        return;
    }

    s32 index = selection->selected - 1;

    if (index < 0)
    {
        index = 7;
    }

    func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(selection), index, 0);
}

/**
 * @brief Map the chosen selector's first three entries to entries three, five, and six.
 */
void TacticsReplaceWindow::func_slot74()
{
    TacticsCoordinateSelector* selection;

    if (use_second)
    {
        selection = second_selector;
    }
    else
    {
        selection = first_selector;
    }

    if (tactics_selection_inactive(selection))
    {
        return;
    }

    s32 index = selection->selected;

    switch (index)
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

    func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(selection), index, 0);
}

/**
 * @brief Map the chosen selector's last five entries back to its first three.
 */
void TacticsReplaceWindow::func_slot70()
{
    TacticsCoordinateSelector* selection;

    if (use_second)
    {
        selection = second_selector;
    }
    else
    {
        selection = first_selector;
    }

    if (tactics_selection_inactive(selection))
    {
        return;
    }

    s32 index = selection->selected;

    switch (index)
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

    func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(selection), index, 0);
}

/**
 * @brief Return to the first selector, update control-mode flags, or open its child window.
 * @return Two after the action, or zero when the runtime or child allocation is absent.
 */
u8 TacticsReplaceWindow::func_slotb4()
{
    if (use_second == 1)
    {
        LibClass175030* second_target = second_selector;
        second_target->unk10 = -128.0f;
        second_target->unk14 = -128.0f;
        second_target->unk35 = 1;
        second_target->unk3c = 1;
        second_selector->unk3f = 0;
        LibClass175030* first_target = first_selector;
        first_target->unk30 = 128.0f;
        first_target->unk3c = 1;
        use_second = 0;
        source_record_index = -1;
        destination_record_index = -1;
        return 2;
    }

    FieldClass153E00* runtime = D_001B643C->runtime;

    if (!runtime)
    {
        return 0;
    }

    u8 control_mode = runtime->unk2d != 0;

    if (control_mode == 1)
    {
        set_state(1, 0x80);
    }
    else
    {
        TacticsExitConfirmWindow* child = new (0) TacticsExitConfirmWindow;

        if (!child)
        {
            return 0;
        }

        child->func_slotf4(func_slot54(), 175.0f, 160.0f, 5, TACTICS_MSG_CONFIRM_EXIT_REPLACE);
        child->func_slot40(this);
        LibClass175030* first_target = first_selector;
        first_target->unk30 = 64.0f;
        first_target->unk3c = 1;
        D_001B643C->callbacks->state->add_child(child);
        D_001B643C->callbacks->state->func_00263C70(child);
    }

    return 2;
}

/**
 * @brief Confirm a swap between the two selected character slots, or start choosing the second slot.
 * @return One when the selection continues, three when the swap is refused or rolled back.
 */
u8 TacticsReplaceWindow::func_slotb0()
{
    u8 result = 1;

    if (use_second == 1)
    {
        u8 allowed = 0;
        s16 remaining = 0;
        destination_record_index = second_selector->selected;
        s16 source = source_record_index;

        for (s32 i = 0; i < 4; i++)
        {
            if (i != source && i != destination_record_index)
            {
                TacticsCharacterRecord* record = &character_records[i];
                s32 character_id = record->character_id;
                s32 stat_limit_type = record->stat_limit_type;

                if (stat_limit_type == 0 && character_id != 0)
                {
                    remaining++;
                }
            }
        }

        if (remaining)
        {
            allowed = 1;
        }
        else
        {
            if (source < 4 && destination_record_index < 4)
            {
                allowed = 1;
            }

            TacticsCharacterRecord* records = character_records;
            TacticsCharacterRecord* first_record = &records[source_record_index];
            TacticsCharacterRecord* second_record = &records[destination_record_index];
            s32 first_stat_limit_type = first_record->stat_limit_type;
            s32 first_character_id = first_record->character_id;
            s32 second_stat_limit_type = second_record->stat_limit_type;
            s32 second_character_id = second_record->character_id;

            if (first_stat_limit_type == 0 && first_character_id != 0 && second_stat_limit_type == 0 && second_character_id != 0)
            {
                allowed = 1;
            }
        }

        if (allowed == 1)
        {
            if (source != destination_record_index)
            {
                func_0013A678(character_record_buffer, 0, sizeof(TacticsCharacterRecord));
                func_0013A678(equipment_record_buffer, 0, sizeof(TacticsCharacterEquipment));
                func_0013A4C0(character_record_buffer, &character_records[source_record_index], sizeof(TacticsCharacterRecord));
                func_0013A4C0(equipment_record_buffer, &equipment_records[source_record_index], sizeof(TacticsCharacterEquipment));
                func_0013A4C0(&character_records[source_record_index], &character_records[destination_record_index], sizeof(TacticsCharacterRecord));
                func_0013A4C0(&equipment_records[source_record_index], &equipment_records[destination_record_index], sizeof(TacticsCharacterEquipment));
                func_0013A4C0(&character_records[destination_record_index], character_record_buffer, sizeof(TacticsCharacterRecord));
                func_0013A4C0(&equipment_records[destination_record_index], equipment_record_buffer, sizeof(TacticsCharacterEquipment));
                u8 rejected = 0;
                u8 invalid[4] = {0};

                for (s32 i = 0; i < 4; i++)
                {
                    s32 stat_limit_type = character_records[i].stat_limit_type;
                    s32 character_id = character_records[i].character_id;

                    if (stat_limit_type == 0 && character_id != 0)
                    {
                        u32 flags = character_records[i].get_flags();

                        if (flags & 5)
                        {
                            invalid[i] = 1;
                        }
                        else
                        {
                            invalid[i] = 0;
                        }
                    }
                    else
                    {
                        invalid[i] = 1;
                    }
                }

                if (invalid[0] == 1 && invalid[1] == 1 && invalid[2] == 1)
                {
                    rejected = 1;
                }

                if (rejected)
                {
                    func_0013A678(character_record_buffer, 0, sizeof(TacticsCharacterRecord));
                    func_0013A678(equipment_record_buffer, 0, sizeof(TacticsCharacterEquipment));
                    func_0013A4C0(character_record_buffer, &character_records[source_record_index], sizeof(TacticsCharacterRecord));
                    func_0013A4C0(equipment_record_buffer, &equipment_records[source_record_index], sizeof(TacticsCharacterEquipment));
                    func_0013A4C0(&character_records[source_record_index], &character_records[destination_record_index], sizeof(TacticsCharacterRecord));
                    func_0013A4C0(&equipment_records[source_record_index], &equipment_records[destination_record_index], sizeof(TacticsCharacterEquipment));
                    func_0013A4C0(&character_records[destination_record_index], character_record_buffer, sizeof(TacticsCharacterRecord));
                    func_0013A4C0(&equipment_records[destination_record_index], equipment_record_buffer, sizeof(TacticsCharacterEquipment));
                    result = 3;
                }
                else
                {
                    reinterpret_cast<TacticsRuntimeControl*>(D_001B643C->runtime)->character_state_refresh_pending = 1;
                    refresh_pending = 1;
                }

                s32 i;
                TacticsSavedFormation* saved = D_001B643C->state;

                for (i = 0; i < 3; i++)
                {
                    if (saved->leader_character_id == character_records[i].character_id)
                    {
                        break;
                    }
                }

                if (i == 3)
                {
                    for (s32 j = 0; j < 3; j++)
                    {
                        if (!character_record_empty(&character_records[j]))
                        {
                            D_001B643C->state->leader_character_id = character_records[j].character_id;
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            result = 3;
        }

        LibClass175030* second_target = second_selector;
        second_target->unk10 = -128.0f;
        second_target->unk14 = -128.0f;
        second_target->unk35 = 1;
        second_target->unk3c = 1;
        second_selector->unk3f = 0;
        LibClass175030* first_target = first_selector;
        first_target->unk30 = 128.0f;
        first_target->unk3c = 1;
        use_second = 0;
        source_record_index = -1;
        destination_record_index = -1;
    }
    else
    {
        LibClass175030* second_target = second_selector;
        LibClass175030* first_target = first_selector;
        const float& x = first_target->unk10;
        float y = first_target->unk14;
        second_target->unk10 = x;
        second_target->unk14 = y;
        second_target->unk35 = 1;
        second_target->unk3c = 1;
        s32 index = (s32)(24.0f + x);
        s32 direct = 1;

        if (!first_target->unk14)
        {
            direct = 0;
        }

        func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(second_selector), index, direct);
        second_selector->unk3f = 1;
        source_record_index = first_selector->selected;
        func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(second_selector), source_record_index, 1);
        first_target = first_selector;
        first_target->unk30 = 64.0f;
        first_target->unk3c = 1;
        use_second = 1;
    }

    return result;
}

/** @brief Refresh the eight resource rows after a record change while this window is active. */
void TacticsReplaceWindow::func_slot5c()
{
    if (static_cast<FieldClass15AE70*>(D_001B643C->callbacks->state->func_00261150()) == this && refresh_pending == 1)
    {
        row_character_ids[0] = 0;
        row_character_ids[1] = 0;
        row_character_ids[2] = 0;
        row_character_ids[3] = 0;
        row_character_ids[4] = 0;
        row_character_ids[5] = 0;
        row_character_ids[6] = 0;
        row_character_ids[7] = 0;

        for (s32 i = 0; i < 8; i++)
        {
            LibObject175140* character_name = static_cast<LibObject175140*>(get_widget_node_at_index(
                &unk44, i)->value);
            LibObject178750* empty_marker = static_cast<LibObject178750*>(get_text_widget_node(
                &unk2c, i)->value);
            LibObject178750* level_label = static_cast<LibObject178750*>(get_text_widget_node(
                &level_label_list, i)->value);
            LibObject174F20* level_value = static_cast<LibObject174F20*>(get_stat_value_node(
                &level_value_list, i)->value);
            LibObject178750* hp_label = static_cast<LibObject178750*>(get_text_widget_node(
                &hp_label_list, i)->value);
            LibObject178750* mp_label = static_cast<LibObject178750*>(get_text_widget_node(
                &mp_label_list, i)->value);
            LibObject174F20* current_hp_value = static_cast<LibObject174F20*>(get_stat_value_node(
                &hp_value_list, i)->value);
            LibObject178750* hp_separator = static_cast<LibObject178750*>(get_text_widget_node(
                &hp_separator_text_list, i)->value);
            LibObject174F20* max_hp_value = static_cast<LibObject174F20*>(get_stat_value_node(
                &max_hp_value_list, i)->value);
            LibObject174F20* current_mp_value = static_cast<LibObject174F20*>(get_stat_value_node(
                &mp_value_list, i)->value);
            LibObject178750* mp_separator = static_cast<LibObject178750*>(get_text_widget_node(
                &mp_separator_text_list, i)->value);
            LibObject174F20* max_mp_value = static_cast<LibObject174F20*>(get_stat_value_node(
                &max_mp_value_list, i)->value);
            s32 character_id = character_records[i].character_id;

            if (character_records[i].stat_limit_type == 0 && character_id != 0)
            {
                character_name->unkfc = equipment_records[i].character_name;
                character_name->unk3c = 1;
                character_name->unk3f = 1;
                empty_marker->unk3f = 0;
                level_label->unk3f = 1;
                level_value->numeric_value = character_records[i].get_level();
                level_value->unk3c = 1;
                level_value->unk3f = 1;
                hp_label->unk3f = 1;
                mp_label->unk3f = 1;
                current_hp_value->numeric_value = character_records[i].get_hp();
                current_hp_value->unk3c = 1;
                current_hp_value->unk3f = 1;
                hp_separator->unk3f = 1;
                max_hp_value->numeric_value = character_records[i].get_max_hp();
                max_hp_value->unk3c = 1;
                max_hp_value->unk3f = 1;
                current_mp_value->numeric_value = character_records[i].get_mp();
                current_mp_value->unk3c = 1;
                current_mp_value->unk3f = 1;
                mp_separator->unk3f = 1;
                max_mp_value->numeric_value = character_records[i].get_max_mp();
                max_mp_value->unk3c = 1;
                max_mp_value->unk3f = 1;
                void* allocation;
                FieldResourceRecord* record;

                if (character_records[i].get_flags() & 5)
                {
                    allocation = field_get_aligned_allocation(D_001B643C->resources, static_cast<u8>(character_id + 0x30));
                    record = field_find_resource_record(D_001B643C->resources, 4);
                    character_name->set_color(0x505080);
                }
                else
                {
                    allocation = field_get_aligned_allocation(D_001B643C->resources, static_cast<u8>(character_id));
                    record = field_find_resource_record(D_001B643C->resources, 4);
                    character_name->set_color(0x808080);
                }

                func_002D5CF0(resource_displays[i], allocation, record, static_cast<u8>(character_id));
                resource_displays[i]->unk3f = 1;
                row_character_ids[i] = character_id;
            }
            else
            {
                character_name->unk3f = 0;
                empty_marker->unk3f = 1;
                level_label->unk3f = 0;
                level_value->unk3f = 0;
                hp_label->unk3f = 0;
                mp_label->unk3f = 0;
                current_hp_value->unk3f = 0;
                hp_separator->unk3f = 0;
                max_hp_value->unk3f = 0;
                current_mp_value->unk3f = 0;
                mp_separator->unk3f = 0;
                max_mp_value->unk3f = 0;
                resource_displays[i]->unk3f = 0;
                row_character_ids[i] = 0;
            }

            if (i >= 3)
            {
                hp_separator->unk3f = 0;
                max_hp_value->unk3f = 0;
                mp_separator->unk3f = 0;
                max_mp_value->unk3f = 0;
            }
        }

        refresh_pending = 0;
    }
}

/**
 * @brief Initialize the paired selectors and their eight resource rows.
 * @param associated Resource source word forwarded to the base and text displays.
 * @return One on success, otherwise zero when records or required displays are absent.
 */
s32 TacticsReplaceWindow::func_slotf4(u32 associated)
{
    s32 source = associated;

    if (initialize_selector_records(this) == false)
    {
        return 0;
    }

    FieldClass15AE70::func_slot10(source, 16.0f, 96.0f, 8);
    first_selector = new (0) TacticsCoordinateSelector;
    second_selector = new (0) TacticsCoordinateSelector;
    lib_moving_widget_init_position(first_selector, 0.0f, 0.0f);
    lib_moving_widget_init_position(second_selector, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, first_selector);
    lib_container_attach_widget(unk10, second_selector);

    for (s32 index = 0; index < 8; index++)
    {
        LibClass178630* panel = new (0) LibClass178630;

        if (panel == 0)
        {
            return 0;
        }

        float height;
        float label_y;
        float column_x;
        float label_x;
        float empty_y;
        float first_x;
        float first_y;
        float second_x;
        float second_y;
        float third_x;
        float third_y;
        float numeric_offset;
        float width;

        if (index < 3)
        {
            height = 120.0f;
            width = 304.0f;
            lib_panel_init_rectangle(panel, 1, 0.0f, 120.0f * index, width, 120.0f, 88.0f);
        }
        else
        {
            height = 72.0f;
            width = 304.0f;
            lib_panel_init_rectangle(panel, 1, width, 72.0f * (index - 3), width, 72.0f, 88.0f);
        }

        append_panel_widget_node(&unk14, panel);
        lib_container_attach_widget(unk10, panel);
        LibObject175140* character_name_label = new (0) LibObject175140;
        LibObject178750* empty_marker = new (0) LibObject178750;
        LibObject178750* level_label = new (0) LibObject178750;
        LibObject174F20* level_value = new (0) LibObject174F20;
        LibObject178750* hp_label = new (0) LibObject178750;
        LibObject178750* mp_label = new (0) LibObject178750;
        LibObject174F20* current_hp_value = new (0) LibObject174F20;
        LibObject178750* hp_separator = new (0) LibObject178750;
        LibObject174F20* max_hp_value = new (0) LibObject174F20;
        LibObject174F20* current_mp_value = new (0) LibObject174F20;
        LibObject178750* mp_separator = new (0) LibObject178750;
        LibObject174F20* max_mp_value = new (0) LibObject174F20;
        resource_displays[index] = new (0) ItemCreationOptionResourceDisplay;

        if (character_name_label == 0 || empty_marker == 0)
        {
            return 0;
        }

        empty_marker->init_resource_rectangle(16.0f, 16.0f, 0.0f, 0.0f, source, TACTICS_MSG_EMPTY_ROW, 0);
        s32 row;

        if (index < 3)
        {
            column_x = 0.0f;
            row = index;
        }
        else
        {
            row = index - 3;
            column_x = width;
        }

        if (index < 3)
        {
            label_x = 108.0f + column_x;
            float row_y = height * row;
            label_y = 14.0f + row_y;
            empty_y = (height / 2.0f + row_y) - 19.2f;
            first_x = 208.0f + column_x;
            numeric_offset = 36.0f;
            first_y = numeric_offset + row_y;
            second_x = 120.0f + column_x;
            second_y = 48.0f + label_y;
            third_x = second_x;
            third_y = 24.0f + second_y;
        }
        else
        {
            float row_y;
            label_x = 78.0f + column_x;
            row_y = height * row;
            label_y = 14.0f + row_y;
            empty_y = 8.0f + ((height / 2.0f + row_y) - 19.2f * 0.8f);
            first_x = 70.0f + column_x;
            numeric_offset = 36.0f;
            first_y = 3.0f + (numeric_offset + row_y);
            second_x = 134.0f + column_x;
            third_x = 215.0f + column_x;
            second_y = first_y;
            third_y = first_y;
            empty_marker->set_scale(0.8f, 0.8f);
        }

        character_name_label->func_00467AD0(label_x, label_y, 0.0f, 0.0f, g_tactics_dummy_text, 0);
        character_name_label->set_scale(0.8f, 0.8f);
        set_widget_rectangle(empty_marker, column_x, empty_y, width, 24.0f);
        empty_marker->set_mode(1);
        level_label->init_resource_rectangle(first_x, first_y, 0.0f, 0.0f, source, TACTICS_MSG_LEVEL, 0);
        level_label->set_scale(0.8f, 0.8f);
        level_label->set_color(0x806080);

        if (index < 3)
        {
            level_value->init_numeric_resource_rectangle(32.0f + first_x, first_y, 42.0f, 24.0f, 0, 0, 0);
        }
        else
        {
            level_value->init_numeric_resource_rectangle(17.0f + first_x, first_y, 42.0f, 24.0f, 0, 0, 0);
        }

        level_value->set_scale(0.8f, 0.8f);
        hp_label->init_resource_rectangle(second_x, second_y, 0.0f, 0.0f, source, TACTICS_MSG_HP, 0);
        hp_label->set_scale(0.8f, 0.8f);
        hp_label->set_color(0x806080);
        float value_width;

        if (index < 3)
        {
            value_width = 56.0f;
            current_hp_value->init_numeric_resource_rectangle(numeric_offset + second_x, second_y, value_width, 24.0f, 0, 0, 0);
        }
        else
        {
            value_width = 56.0f;
            current_hp_value->init_numeric_resource_rectangle(19.0f + second_x, second_y, value_width, 24.0f, 0, 0, 0);
        }

        current_hp_value->set_scale(0.8f, 0.8f);
        hp_separator->init_resource_rectangle(98.0f + second_x, second_y, 0.0f, 0.0f, source, TACTICS_MSG_VALUE_SEPARATOR, 0);
        hp_separator->set_scale(0.8f, 0.8f);
        max_hp_value->init_numeric_resource_rectangle(106.0f + second_x, second_y, value_width, 24.0f, 0, 0, 0);
        max_hp_value->set_scale(0.8f, 0.8f);
        mp_label->init_resource_rectangle(third_x, third_y, 0.0f, 0.0f, source, TACTICS_MSG_MP, 0);
        mp_label->set_scale(0.8f, 0.8f);
        mp_label->set_color(0x806080);

        if (index < 3)
        {
            current_mp_value->init_numeric_resource_rectangle(numeric_offset + third_x, third_y, value_width, 24.0f, 0, 0, 0);
        }
        else
        {
            current_mp_value->init_numeric_resource_rectangle(20.0f + third_x, third_y, value_width, 24.0f, 0, 0, 0);
        }

        current_mp_value->set_scale(0.8f, 0.8f);
        mp_separator->init_resource_rectangle(98.0f + third_x, third_y, 0.0f, 0.0f, source, TACTICS_MSG_VALUE_SEPARATOR, 0);
        mp_separator->set_scale(0.8f, 0.8f);
        max_mp_value->init_numeric_resource_rectangle(106.0f + third_x, third_y, value_width, 24.0f, 0, 0, 0);
        max_mp_value->set_scale(0.8f, 0.8f);
        s32 character_id = record_character_id(&character_records[index]);

        if (character_records[index].stat_limit_type == 0 && character_id != 0)
        {
            character_name_label->unkfc = equipment_records[index].character_name;
            character_name_label->unk3c = 1;
            character_name_label->unk3f = 1;
            empty_marker->unk3f = 0;
            level_label->unk3f = 1;
            level_value->numeric_value = character_records[index].get_level();
            level_value->unk3c = 1;
            level_value->unk3f = 1;
            hp_label->unk3f = 1;
            mp_label->unk3f = 1;
            current_hp_value->numeric_value = character_records[index].get_hp();
            current_hp_value->unk3c = 1;
            current_hp_value->unk3f = 1;
            hp_separator->unk3f = 1;
            max_hp_value->numeric_value = character_records[index].get_max_hp();
            max_hp_value->unk3c = 1;
            max_hp_value->unk3f = 1;
            current_mp_value->numeric_value = character_records[index].get_mp();
            current_mp_value->unk3c = 1;
            current_mp_value->unk3f = 1;
            mp_separator->unk3f = 1;
            max_mp_value->numeric_value = character_records[index].get_max_mp();
            max_mp_value->unk3c = 1;
            max_mp_value->unk3f = 1;
            void* allocation;
            FieldResourceRecord* record;

            if (character_records[index].get_flags() & 5)
            {
                allocation = field_get_aligned_allocation(D_001B643C->resources, static_cast<u8>(character_id + 0x30));
                record = field_find_resource_record(D_001B643C->resources, 4);
                character_name_label->set_color(0x505080);
            }
            else
            {
                allocation = field_get_aligned_allocation(D_001B643C->resources, static_cast<u8>(character_id));
                record = static_cast<FieldResourceRecord*>(field_get_builtin_resource_data(D_001B643C->resources, 0));
                character_name_label->set_color(0x808080);
            }

            resource_displays[index]->unkcc = allocation;
            resource_displays[index]->unkd0 = character_id;

            if (index < 3)
            {
                func_002D6440(resource_displays[index], record, 20.0f + column_x, 8.0f + label_y);
            }
            else
            {
                func_002D6440(resource_displays[index], record, 15.0f + column_x, label_y - 5.0f);
                set_resource_display_scale(resource_displays[index], 0.68f);
            }

            row_character_ids[index] = character_id;
        }
        else
        {
            character_name_label->unk3f = 0;
            empty_marker->unk3f = 1;
            level_label->unk3f = 0;
            level_value->unk3f = 0;
            hp_label->unk3f = 0;
            mp_label->unk3f = 0;
            current_hp_value->unk3f = 0;
            hp_separator->unk3f = 0;
            max_hp_value->unk3f = 0;
            current_mp_value->unk3f = 0;
            mp_separator->unk3f = 0;
            max_mp_value->unk3f = 0;
            void* allocation = field_get_aligned_allocation(D_001B643C->resources, 1);
            FieldResourceRecord* record = static_cast<FieldResourceRecord*>(field_get_builtin_resource_data(D_001B643C->resources, 0));
            resource_displays[index]->unkcc = allocation;
            resource_displays[index]->unkd0 = character_id;

            if (index < 3)
            {
                func_002D6440(resource_displays[index], record, 20.0f + column_x, 8.0f + label_y);
            }
            else
            {
                func_002D6440(resource_displays[index], record, 15.0f + column_x, label_y - 5.0f);
                set_resource_display_scale(resource_displays[index], 0.68f);
            }

            resource_displays[index]->unk3f = 0;
        }

        if (index < 3)
        {
            append_position(first_selector, 20.0f + column_x, 38.0f + label_y);
            append_position(second_selector, 20.0f + column_x, 38.0f + label_y);
        }
        else
        {
            hp_separator->unk3f = 0;
            max_hp_value->unk3f = 0;
            mp_separator->unk3f = 0;
            max_mp_value->unk3f = 0;
            append_position(first_selector, 20.0f + column_x, 18.0f + label_y);
            append_position(second_selector, 20.0f + column_x, 18.0f + label_y);
        }

        lib_container_attach_widget(unk10, character_name_label);
        append_icon_widget_node(&unk44, character_name_label);
        lib_container_attach_widget(unk10, empty_marker);
        append_text_widget_node(&unk2c, empty_marker);
        lib_container_attach_widget(unk10, level_label);
        append_text_widget_node(&level_label_list, level_label);
        lib_container_attach_widget(unk10, level_value);
        append_stat_value_node(&level_value_list, level_value);
        lib_container_attach_widget(unk10, hp_label);
        append_text_widget_node(&hp_label_list, hp_label);
        lib_container_attach_widget(unk10, mp_label);
        append_text_widget_node(&mp_label_list, mp_label);
        lib_container_attach_widget(unk10, current_hp_value);
        append_stat_value_node(&hp_value_list, current_hp_value);
        lib_container_attach_widget(unk10, hp_separator);
        append_text_widget_node(&hp_separator_text_list, hp_separator);
        lib_container_attach_widget(unk10, max_hp_value);
        append_stat_value_node(&max_hp_value_list, max_hp_value);
        lib_container_attach_widget(unk10, current_mp_value);
        append_stat_value_node(&mp_value_list, current_mp_value);
        lib_container_attach_widget(unk10, mp_separator);
        append_text_widget_node(&mp_separator_text_list, mp_separator);
        lib_container_attach_widget(unk10, max_mp_value);
        append_stat_value_node(&max_mp_value_list, max_mp_value);
        lib_container_attach_widget(unk10, resource_displays[index]);
    }

    LibObject178750* first_title = new (0) LibObject178750;
    LibObject178750* second_title = new (0) LibObject178750;

    if (first_title == 0 || second_title == 0)
    {
        return 0;
    }

    first_title->init_resource_rectangle(16.0f, 16.0f, 0.0f, 0.0f, source, TACTICS_MSG_LEFT_COLUMN_TITLE, 1);
    set_widget_rectangle(first_title, 16.0f, -20.0f, 304.0f, 16.0f);
    first_title->set_mode(0);
    first_title->set_color(0x288080);
    second_title->init_resource_rectangle(16.0f, 16.0f, 0.0f, 0.0f, source, TACTICS_MSG_RIGHT_COLUMN_TITLE, 1);
    set_widget_rectangle(second_title, 320.0f, -20.0f, 304.0f, 16.0f);
    second_title->set_mode(0);
    second_title->set_color(0x288080);
    lib_container_attach_widget(unk10, first_title);
    lib_container_attach_widget(unk10, second_title);
    append_text_widget_node(&unk2c, first_title);
    append_text_widget_node(&unk2c, second_title);
    func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(first_selector), 0, 1);
    func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(second_selector), 0, 1);
    second_selector->unk3f = 0;
    return 1;
}

/** @brief Destroy the movement storage and widget base. */
inline ItemCreationClass175030::~ItemCreationClass175030()
{
}

/** @brief Release both binary buffers, then destroy the lists and base window. */
TacticsReplaceWindow::~TacticsReplaceWindow()
{
    if (character_record_buffer != 0)
    {
        delete_owned(character_record_buffer);
    }

    if (equipment_record_buffer != 0)
    {
        delete_owned(equipment_record_buffer);
    }
}

/** @brief Construct the owned lists and clear the window control fields. */
TacticsReplaceWindow::TacticsReplaceWindow()
{
    character_records = 0;
    equipment_records = 0;
    character_record_buffer = 0;
    equipment_record_buffer = 0;
    second_selector = 0;
    first_selector = 0;
    use_second = 0;
    source_record_index = -1;
    destination_record_index = -1;
    refresh_pending = 0;
    row_character_ids[0] = 0;
    row_character_ids[1] = 0;
    row_character_ids[2] = 0;
    row_character_ids[3] = 0;
    row_character_ids[4] = 0;
    row_character_ids[5] = 0;
    row_character_ids[6] = 0;
    row_character_ids[7] = 0;
}

/** @brief Refresh the associated text when the active grid selection changes. */
void TacticsStrategyWindow::func_slot5c()
{
    if (D_001B643C->callbacks->state->func_00261150() != this)
    {
        return;
    }

    s16 index = grid->unk114;

    if (index == selected)
    {
        return;
    }

    if (character_id == 2 || character_id == 9)
    {
        static_cast<FieldClass15AE70*>(D_001B643C->callbacks->state->func_00263C90())->func_slot60(index + TACTICS_MSG_ALT_STRATEGY_HELP_BASE);
    }
    else
    {
        static_cast<FieldClass15AE70*>(D_001B643C->callbacks->state->func_00263C90())->func_slot60(index + TACTICS_MSG_STRATEGY_HELP_BASE);
    }

    selected = index;
}

/** @brief Set the window message by signed text key. @param text_key Message key or relative index. */
void FieldClass15AE70::func_slot60(s32 text_key)
{
}

/** @brief Return the alternate associated object. @return Stored object. */
void* FieldClass153E30::func_00263C90()
{
    return unk24;
}

/**
 * @brief Color up to six strategy names and place the cursor on the selected one.
 * @param object Strategy window holding the names, grid, and cursor.
 */
void highlight_strategy(TacticsStrategyWindow* object)
{
    s16 selected = object->grid->unk114;
    s32 index = 0;
    FieldListNode* node = object->unk2c.head->next;

    while (node != 0)
    {
        if (index >= 6)
        {
            break;
        }

        LibObject178750* display = static_cast<LibObject178750*>(node->value);

        if (index == selected)
        {
            display->set_color(0x288080);
            func_0023B9B0(object->cursor, index,
                lib_text_measure_bounds(display)->unk08);
        }
        else
        {
            display->set_color(0x808080);
        }

        node = node->next;
        index++;
    }
}

/** @brief Move to the following grid entry and refresh its highlight. */
void TacticsStrategyWindow::func_slot6c()
{
    if (static_cast<s16>(grid->process_direction(1)) == 1)
    {
        return;
    }

    highlight_strategy(this);
}

/** @brief Move to the preceding grid entry and refresh its highlight. */
void TacticsStrategyWindow::func_slot68()
{
    if (static_cast<s16>(grid->process_direction(0)) == 1)
    {
        return;
    }

    highlight_strategy(this);
}

/**
 * @brief Close the grid window, restore its parent, and reset the associated text.
 * @return Two after closing.
 */
u8 TacticsStrategyWindow::func_slotb4()
{
    cursor->unk3f = 0;
    selection_indicator->unk3f = 0;
    FieldClass15AE70::func_slot18(0, 0x7F);
    static_cast<FieldClass15AE70*>(func_slot44())->func_slot64();
    FieldClass153E30* state = D_001B643C->callbacks->state;
    state->func_00263C70(func_slot44());
    static_cast<FieldClass15AE70*>(D_001B643C->callbacks->state->func_00263C90())->func_slot60(TACTICS_MSG_CHANGE_TACTICS_HELP);
    return 2;
}

/**
 * @brief Save the chosen strategy, update the character's row, and return to the Change Tactics window.
 * @return One after the selected entry is applied.
 */
u8 TacticsStrategyWindow::func_slotb0()
{
    TacticsChangeWindow* parent = static_cast<TacticsChangeWindow*>(func_slot44());
    TacticsCharacterEquipment* record = &parent->equipment_records[parent->selected];
    record->battle_strategy = grid->unk114;
    LibObject178750* display = static_cast<LibObject178750*>(get_text_widget_node(
        &parent->unk2c, parent->selected)->value);
    TacticsCharacterRecord* records = parent->character_records;
    s16 record_index = parent->selected;
    s16 character_id;

    if (records)
    {
        character_id = records[record_index].character_id;
    }
    else
    {
        character_id = 0;
    }

    u32 key = parent->get_strategy_text_key(character_id, record_index);
    lib_text_set_resource(display, parent->func_slot54(), key, 0);
    cursor->unk3f = 0;
    selection_indicator->unk3f = 0;
    FieldClass15AE70::func_slot18(0, 0x7F);
    static_cast<FieldClass15AE70*>(func_slot44())->func_slot64();
    FieldClass153E30* state = D_001B643C->callbacks->state;
    state->func_00263C70(func_slot44());
    static_cast<FieldClass15AE70*>(D_001B643C->callbacks->state->func_00263C90())->func_slot60(TACTICS_MSG_CHANGE_TACTICS_HELP);
    return 1;
}

/**
 * @brief Show a character's six strategies and highlight the current one.
 * @param record_index Signed record index in the resident record table.
 * @param initial_entry Strategy to highlight.
 * @return Marker position status.
 */
s32 TacticsStrategyWindow::set_character(s16 record_index, u8 initial_entry)
{
    clear_grid_state(this);
    character_id = character_records[record_index].character_id;
    selected_entry = initial_entry;
    s32 first_key = first_strategy_text_key(character_id);

    if (first_key == TACTICS_MSG_DUMMY)
    {
        keys[0] = TACTICS_MSG_DUMMY;
        keys[1] = TACTICS_MSG_DUMMY;
        keys[2] = TACTICS_MSG_DUMMY;
        keys[3] = TACTICS_MSG_DUMMY;
        keys[4] = TACTICS_MSG_DUMMY;
        keys[5] = TACTICS_MSG_DUMMY;
    }
    else
    {
        for (s32 index = 0; index < 6; index++)
        {
            keys[index] = first_key + index;
            LibObject178750* display = strategy_display(this, index);
            lib_text_set_resource(display, func_slot54(), keys[index], 0);
        }
    }

    for (s32 index = 0; index < 6; index++)
    {
        LibObject178750* display = strategy_display(this, index);
        display->set_color(0x808080);
    }

    LibUiRect16* rectangle = &strategy_display(this, selected_entry)->unk18;
    LibBounds4C69B0* bounds = lib_text_measure_bounds(strategy_display(this, selected_entry));
    FieldObject23CEA0* selection = grid;
    selection->index = selected_entry;
    func_0023CB30(selection);
    func_0023CEE0(reinterpret_cast<FieldObject23CEB0*>(grid));
    set_widget_rectangle(selection_indicator, rectangle->unk00, rectangle->unk04,
        bounds->unk08, bounds->unk0c);
    LibObject178750* selected = strategy_display(this, selected_entry);
    selected->set_color(0x288080);
    return func_0023B9B0(cursor, selected_entry, bounds->unk08);
}

/**
 * @brief Create the strategy window's text, panels, selector, and indicators.
 * @param associated Full resource source word forwarded to the base window and text widgets.
 * @return Zero when required resources or displays are missing; otherwise one.
 */
s32 TacticsStrategyWindow::func_slotf4(u32 associated)
{
    character_records = D_001B643C->character_records;
    equipment_records = D_001B643C->equipment_records;

    if (character_records == 0 || equipment_records == 0)
    {
        return 0;
    }

    FieldClass15AE70::func_slot10(associated, 138.0f, 148.0f, 7);
    LibClass178630* panel = new (0) LibClass178630;
    text[0] = new (0) LibObject178750;
    text[1] = new (0) LibObject178750;
    text[2] = new (0) LibObject178750;
    text[3] = new (0) LibObject178750;
    text[4] = new (0) LibObject178750;
    text[5] = new (0) LibObject178750;
    grid = new (0) FieldObject23CEA0;
    LibClass178630* title_panel = new (0) LibClass178630;
    LibObject178750* title = new (0) LibObject178750;
    selection_indicator = new (0) ItemCreationClass172600;
    cursor = new (0) FieldObject23BE00;

    if (panel == 0 || text[0] == 0 || text[1] == 0 || text[2] == 0 ||
        text[3] == 0 || text[4] == 0 || text[5] == 0 || grid == 0)
    {
        return 0;
    }

    LibWidgetColors4C5590 colors = g_tactics_strategy_title_colors;
    lib_panel_init_rectangle(panel, 1, 0.0f, 0.0f, 364.0f, 256.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    append_panel_widget_node(&unk14, panel);
    lib_panel_init_rectangle(title_panel, 1, 0.0f, 0.0f, 364.0f, 48.0f, 88.0f);
    lib_panel_set_colors(title_panel, &colors);
    lib_container_attach_widget(unk10, title_panel);
    append_panel_widget_node(&unk14, title_panel);
    clear_grid_state(this);
    keys[0] = TACTICS_MSG_DUMMY;
    keys[1] = TACTICS_MSG_DUMMY;
    keys[2] = TACTICS_MSG_DUMMY;
    keys[3] = TACTICS_MSG_DUMMY;
    keys[4] = TACTICS_MSG_DUMMY;
    keys[5] = TACTICS_MSG_DUMMY;
    lib_text_init_resource_rectangle(text[0], associated, keys[0], 0, 28.0f, 60.0f, 0.0f, 0.0f);
    lib_text_init_resource_rectangle(text[1], associated, keys[1], 0, 28.0f, 90.0f, 0.0f, 0.0f);
    lib_text_init_resource_rectangle(text[2], associated, keys[2], 0, 28.0f, 120.0f, 0.0f, 0.0f);
    lib_text_init_resource_rectangle(text[3], associated, keys[3], 0, 28.0f, 150.0f, 0.0f, 0.0f);
    lib_text_init_resource_rectangle(text[4], associated, keys[4], 0, 28.0f, 180.0f, 0.0f, 0.0f);
    lib_text_init_resource_rectangle(text[5], associated, keys[5], 0, 28.0f, 210.0f, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, text[0]);
    lib_container_attach_widget(unk10, text[1]);
    lib_container_attach_widget(unk10, text[2]);
    lib_container_attach_widget(unk10, text[3]);
    lib_container_attach_widget(unk10, text[4]);
    lib_container_attach_widget(unk10, text[5]);
    append_text_widget_node(&unk2c, text[0]);
    append_text_widget_node(&unk2c, text[1]);
    append_text_widget_node(&unk2c, text[2]);
    append_text_widget_node(&unk2c, text[3]);
    append_text_widget_node(&unk2c, text[4]);
    append_text_widget_node(&unk2c, text[5]);
    lib_text_init_resource_rectangle(title, associated, TACTICS_MSG_TACTICS_MENU, 1, 0.0f, 12.0f, 364.0f, 48.0f);
    title->unk9c = 1;
    title->unk3c = 1;
    lib_container_attach_widget(unk10, title);
    append_text_widget_node(&unk2c, title);
    LibBounds4C69B0* bounds = lib_text_measure_bounds(text[0]);
    func_0041AD10(selection_indicator, bounds->unk00, bounds->unk04, bounds->unk08, 24.0f);
    lib_container_attach_widget(unk10, selection_indicator);
    grid->func_0023CE80(1, 6);
    grid->func_0023CE60(0.0f, 30.0f);
    grid->unkF2 = 0;
    grid->func_0023CF50(0, 166.0f, 208.0f);
    FieldObject23CEA0* selection = grid;
    selection->index = selected_entry;
    func_0023CB30(selection);
    func_0023CEE0(reinterpret_cast<FieldObject23CEB0*>(grid));
    append_grid_widget_node(&unk74, grid);
    cursor->func_0023BB20(28.0f, 60.0f, 192.0f, 1.0f, grid, 0x288080);
    lib_container_attach_widget(unk10, cursor);
    cursor->unk3f = 0;
    selection_indicator->unk3f = 0;
    FieldClass15AE70::func_slot18(0, 0x7F);
    return 1;
}

/** @brief Destroy the grid window. */
TacticsStrategyWindow::~TacticsStrategyWindow()
{
}

/** @brief Initialize the grid window's pointers and control fields. */
TacticsStrategyWindow::TacticsStrategyWindow()
{
    character_records = 0;
    equipment_records = 0;
    grid = 0;
    selected = -1;
    text[0] = 0;
    text[1] = 0;
    text[2] = 0;
    text[3] = 0;
    text[4] = 0;
    text[5] = 0;
    selection_indicator = 0;
    cursor = 0;
    character_id = 0;
    selected_entry = 0;
}

/** @brief Restore the selector movement or visibility state. */
void TacticsChangeWindow::func_slot64()
{
    s16 state = selected;
    LibClass175030* target;

    if (state == 3 || state == 4)
    {
        selection->unk3f = 1;
    }
    else
    {
        target = selection;
        target->unk30 = 128.0f;
        target->unk3c = 1;
    }
}

/** @brief Move to the following coordinate, wrapping after the eighth. */
void TacticsChangeWindow::func_slot6c()
{
    TacticsCoordinateSelector* selection = this->selection;

    if (tactics_selection_inactive(selection))
    {
        return;
    }

    s32 index = selection->selected + 1;

    if (index >= 8)
    {
        index = 0;
    }

    func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(selection), index, 0);
}

/** @brief Move to the preceding coordinate, wrapping before the first. */
void TacticsChangeWindow::func_slot68()
{
    TacticsCoordinateSelector* selection = this->selection;

    if (tactics_selection_inactive(selection))
    {
        return;
    }

    s32 index = selection->selected - 1;

    if (index < 0)
    {
        index = 7;
    }

    func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(selection), index, 0);
}

/** @brief Map the first three coordinate entries to entries three, five, and six. */
void TacticsChangeWindow::func_slot74()
{
    TacticsCoordinateSelector* selection = this->selection;

    if (tactics_selection_inactive(selection))
    {
        return;
    }

    s32 index = selection->selected;

    switch (index)
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

    func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(selection), index, 0);
}

/** @brief Map the last five coordinate entries to the first three. */
void TacticsChangeWindow::func_slot70()
{
    TacticsCoordinateSelector* selection = this->selection;

    if (tactics_selection_inactive(selection))
    {
        return;
    }

    s32 index = selection->selected;

    switch (index)
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

    func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(selection), index, 0);
}

/**
 * @brief Open a child window, or update the window flags for the resident control mode.
 * @return Two after the action, or zero when the runtime or child allocation is absent.
 */
u8 TacticsChangeWindow::func_slotb4()
{
    FieldClass153E00* runtime = D_001B643C->runtime;

    if (!runtime)
    {
        return 0;
    }

    u8 control_mode = runtime->unk2d != 0;

    if (control_mode == 1)
    {
        set_state(1, 0x80);
    }
    else
    {
        TacticsExitConfirmWindow* child = new (0) TacticsExitConfirmWindow;

        if (!child)
        {
            return 0;
        }

        child->func_slotf4(func_slot54(), 175.0f, 160.0f, 5, TACTICS_MSG_CONFIRM_EXIT_TACTICS);
        child->func_slot40(this);
        D_001B643C->callbacks->state->add_child(child);
        D_001B643C->callbacks->state->func_00263C70(child);
    }

    return 2;
}

/**
 * @brief Open the grid window for the selected enabled record and remember its current entry.
 * @return One after opening the grid window, or three for a disabled record.
 */
u8 TacticsChangeWindow::func_slotb0()
{
    selected = selection->selected;

    if (record_enabled[selected])
    {
        TacticsCharacterEquipment* record = &equipment_records[selected];
        u8 initial_entry = record->battle_strategy;
        record->previous_battle_strategy = initial_entry;

        if (selected == 3 || selected == 4)
        {
            selection->unk3f = 0;
        }
        else
        {
            LibClass175030* target = selection;
            target->unk30 = 64.0f;
            target->unk3c = 1;
        }

        TacticsStrategyWindow* child = static_cast<TacticsStrategyWindow*>(func_slot44());
        child->set_character(selected, initial_entry);
        child->cursor->unk3f = 1;
        child->selection_indicator->unk3f = 1;
        child->FieldClass15AE70::func_slot18(1, 0x7F);
        FieldClass153E30* state = D_001B643C->callbacks->state;
        state->func_00263C70(func_slot44());
    }
    else
    {
        return 3;
    }

    return 1;
}

/**
 * @brief Return the text key of a character's chosen battle strategy.
 * @param character_id Signed character ID selecting the key range.
 * @param record_index Record index in the resident entry table.
 * @return Text key of the chosen strategy's name.
 */
u32 TacticsChangeWindow::get_strategy_text_key(s16 character_id, s32 record_index)
{
    u32 first_key = first_strategy_text_key(character_id);

    TacticsCharacterEquipment* record = &equipment_records[record_index];
    return first_key + record->battle_strategy;
}

/**
 * @brief Select the position of a row's strategy text, clearing it for an invalid row.
 * @param object Change Tactics window holding the position pair.
 * @param index Zero-based row index.
 * @return The receiver's updated position pair.
 */
TacticsPresetPosition* set_strategy_text_position(TacticsChangeWindow* object, s32 index)
{
    switch (index)
    {
    case 0:
        object->preset_position.x = 96.0f;
        object->preset_position.y = 68.0f;
        break;
    case 1:
        object->preset_position.x = 96.0f;
        object->preset_position.y = 188.0f;
        break;
    case 2:
        object->preset_position.x = 96.0f;
        object->preset_position.y = 308.0f;
        break;
    case 3:
        object->preset_position.x = 390.0f;
        object->preset_position.y = 38.0f;
        break;
    case 4:
        object->preset_position.x = 390.0f;
        object->preset_position.y = 110.0f;
        break;
    case 5:
        object->preset_position.x = 390.0f;
        object->preset_position.y = 182.0f;
        break;
    case 6:
        object->preset_position.x = 390.0f;
        object->preset_position.y = 254.0f;
        break;
    case 7:
        object->preset_position.x = 390.0f;
        object->preset_position.y = 326.0f;
        break;
    default:
        object->preset_position.x = 0.0f;
        object->preset_position.y = 0.0f;
        break;
    }

    return &object->preset_position;
}

/**
 * @brief Initialize the coordinate selector, row displays, and resource bindings.
 * @param associated Resource source word forwarded to the base and text displays.
 * @return One on success, or zero when records or required displays are absent.
 */
s32 TacticsChangeWindow::func_slotf4(u32 associated)
{
    character_records = D_001B643C->character_records;
    equipment_records = D_001B643C->equipment_records;

    if (coordinate_records_ready(this) == false)
    {
        return 0;
    }

    u32 source = associated;
    FieldClass15AE70::func_slot10(source, 16.0f, 96.0f, 8);
    selection = new (0) TacticsCoordinateSelector;
    lib_moving_widget_init_position(selection, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, selection);

    for (s32 index = 0; index < 8; index++)
    {
        LibObject178750* text = new (0) LibObject178750;
        lib_container_attach_widget(unk10, text);
        append_text_widget_node(&unk2c, text);
    }

    for (s32 index = 0; index < 8; index++)
    {
        LibClass178630* panel = new (0) LibClass178630;

        if (panel == 0)
        {
            return 0;
        }

        float height;
        float column_x;
        float row_y;
        float width;

        if (index < 3)
        {
            height = 120.0f;
            width = 304.0f;
            lib_panel_init_rectangle(panel, 1, 0.0f, 120.0f * index, width, 120.0f, 88.0f);
        }
        else
        {
            height = 72.0f;
            width = 304.0f;
            lib_panel_init_rectangle(panel, 1, width, 72.0f * (index - 3), width, 72.0f, 88.0f);
        }

        append_panel_widget_node(&unk14, panel);
        lib_container_attach_widget(unk10, panel);
        LibObject175140* label = new (0) LibObject175140;
        LibObject178750* empty = new (0) LibObject178750;

        if (label == 0 || empty == 0)
        {
            return 0;
        }

        lib_text_init_resource_rectangle(empty, source, TACTICS_MSG_EMPTY_ROW, 0, 16.0f, 16.0f, 0.0f, 0.0f);

        if (index < 3)
        {
            row_y = height * index;
            label->func_00467AD0(108.0f, 24.0f + row_y, 0.0f, 0.0f, g_tactics_dummy_text, 0);
            set_widget_rectangle(empty, 0.0f, (height / 2.0f + row_y) - 19.2f, width, 24.0f);
            column_x = 0.0f;
        }
        else
        {
            row_y = height * (index - 3);
            label->func_00467AD0(412.0f, 14.0f + row_y, 0.0f, 0.0f, g_tactics_dummy_text, 0);
            set_widget_rectangle(empty, 304.0f, 8.0f + ((height / 2.0f + row_y) - 19.2f * 0.8f), 304.0f, 24.0f);
            column_x = 304.0f;
            empty->set_scale(0.8f, 0.8f);
        }

        empty->set_mode(1);
        label->set_scale(0.82f, 0.82f);
        LibObject178750* text = static_cast<LibObject178750*>(get_text_widget_node(&unk2c, index)->value);
        s32 character_id = character_records[index].character_id;

        if (character_records[index].stat_limit_type == 0 && character_id != 0)
        {
            label->unkfc = equipment_records[index].character_name;
            label->unk3c = 1;
            label->unk3f = 1;
            empty->unk3f = 0;
            record_enabled[index] = 1;
            ItemCreationOptionResourceDisplay* display = new (0) ItemCreationOptionResourceDisplay;
            void* allocation = field_get_aligned_allocation(D_001B643C->resources, static_cast<u8>(character_id));
            FieldResourceRecord* record = static_cast<FieldResourceRecord*>(field_get_builtin_resource_data(D_001B643C->resources, 0));
            display->unkcc = allocation;
            display->unkd0 = character_id;

            if (index < 3)
            {
                func_002D6440(display, record, 18.0f + column_x, 16.0f + row_y);
            }
            else
            {
                func_002D6440(display, record, 18.0f + column_x, 10.0f + row_y);
                set_resource_display_scale(display, 0.68f);
            }

            lib_container_attach_widget(unk10, display);
            u32 text_key = get_strategy_text_key(character_id, index);
            TacticsPresetPosition* preset = set_strategy_text_position(this, index);
            lib_text_init_resource_rectangle(text, source, text_key, 0, preset->x, preset->y, 0.0f, 0.0f);
            text->unk88 = -1.0f;
            text->unk3c = 1;
            text->set_scale(0.7f, 0.7f);
        }
        else
        {
            lib_text_init_resource_rectangle(text, source, TACTICS_MSG_DUMMY, 0, 0.0f, 0.0f, 0.0f, 0.0f);
            text->unk3f = 0;
            label->unk3f = 0;
            empty->unk3f = 1;
        }

        if (index < 3)
        {
            append_position(selection, 18.0f + column_x, 52.0f + row_y);
        }
        else
        {
            append_position(selection, 18.0f + column_x, 36.0f + row_y);
        }

        append_icon_widget_node(&unk44, label);
        lib_container_attach_widget(unk10, label);
        append_text_widget_node(&unk2c, empty);
        lib_container_attach_widget(unk10, empty);
    }

    LibObject178750* first_title = new (0) LibObject178750;
    LibObject178750* second_title = new (0) LibObject178750;

    if (first_title == 0 || second_title == 0)
    {
        return 0;
    }

    lib_text_init_resource_rectangle(first_title, source, TACTICS_MSG_LEFT_COLUMN_TITLE, 1, 16.0f, 16.0f, 0.0f, 0.0f);
    set_widget_rectangle(first_title, 16.0f, -20.0f, 304.0f, 16.0f);
    first_title->set_mode(0);
    first_title->set_color(0x288080);
    lib_text_init_resource_rectangle(second_title, source, TACTICS_MSG_RIGHT_COLUMN_TITLE, 1, 16.0f, 16.0f, 0.0f, 0.0f);
    set_widget_rectangle(second_title, 320.0f, -20.0f, 304.0f, 16.0f);
    second_title->set_mode(0);
    second_title->set_color(0x288080);
    func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(selection), 0, 1);
    lib_container_attach_widget(unk10, first_title);
    lib_container_attach_widget(unk10, second_title);
    append_text_widget_node(&unk2c, first_title);
    append_text_widget_node(&unk2c, second_title);
    return 1;
}

/** @brief Destroy the coordinate-selection window. */
TacticsChangeWindow::~TacticsChangeWindow()
{
}

/**
 * @brief Replace the text for supported keys and reset its scrolling state.
 * @param text_key Help line key, from TACTICS_MSG_HELP_FIRST up to TACTICS_MSG_HELP_END.
 */
void TacticsHelpWindow::func_slot60(s32 text_key)
{
    if (text_key >= TACTICS_MSG_HELP_FIRST && text_key < TACTICS_MSG_HELP_END)
    {
        scroll_phase = 0;
        initial_pause_frames = 0;
        lib_text_set_resource(text, func_slot54(), text_key, 1);
        scroll_span = static_cast<s32>(lib_text_measure_bounds(text)->unk08) + 6;
    }
}

/** @brief Hold the text position, then scroll and wrap it after the timer expires. */
void TacticsHelpWindow::func_slot5c()
{
    LibObject178750* target = text;
    float x = target->unk18.unk00;
    float y = target->unk18.unk04;
    float z = target->unk18.unk08;
    float w = target->unk18.unk0c;

    if (scroll_phase == 0)
    {
        set_widget_rectangle(target, initial_text_x, y, z, w);
        initial_pause_frames++;

        if (!((float)initial_pause_frames <= 120.0f))
        {
            initial_pause_frames = 0;
            scroll_phase = 1;
        }

        return;
    }

    x -= 108.0f * D_001B6690;

    if (x < clip_x - (float)scroll_span)
    {
        x = 2.0f + (clip_x + clip_width);
    }

    set_widget_rectangle(target, x, y, z, w);
}

/**
 * @brief Initialize the scrolling window and its text displays.
 * @param associated Resource source word forwarded to the base and text displays.
 * @return One after initialization succeeds; otherwise zero.
 */
s32 TacticsHelpWindow::func_slotf4(u32 associated)
{
    u32 resource_source = associated;
    FieldClass15AE70::func_slot10(resource_source, 16.0f, 16.0f, 19);
    LibObject178750* heading = new (0) LibObject178750;
    LibObject178750* label = new (0) LibObject178750;
    LibObject178750* hint = new (0) LibObject178750;
    lib_text_init_resource_rectangle(heading, resource_source, TACTICS_MSG_TITLE, 0, 16.0f, 10.0f, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, heading);
    append_text_widget_node(&unk2c, heading);

    switch (D_001B643C->callbacks->tactics_mode_flags & 0xF)
    {
    case 1:
        lib_text_init_resource_rectangle(label, resource_source, TACTICS_MSG_CHANGE_TACTICS, 0, 80.0f, 6.0f, 0.0f, 0.0f);
        lib_text_init_resource_rectangle(hint, resource_source, TACTICS_MSG_STRATEGY_HINT, 0, 36.0f, 40.0f, 0.0f, 0.0f);
        break;
    case 2:
        lib_text_init_resource_rectangle(label, resource_source, TACTICS_MSG_REPLACE, 0, 80.0f, 6.0f, 0.0f, 0.0f);
        lib_text_init_resource_rectangle(hint, resource_source, TACTICS_MSG_REPLACEMENT_HINT, 0, 36.0f, 40.0f, 0.0f, 0.0f);
        break;
    case 4:
        lib_text_init_resource_rectangle(label, resource_source, TACTICS_MSG_FORMATION, 0, 80.0f, 6.0f, 0.0f, 0.0f);
        lib_text_init_resource_rectangle(hint, resource_source, TACTICS_MSG_FORMATION_HINT, 0, 36.0f, 40.0f, 0.0f, 0.0f);
        break;
    default:
        lib_text_init_resource_rectangle(hint, resource_source, TACTICS_MSG_DEFAULT_HINT, 0, 36.0f, 40.0f, 0.0f, 0.0f);
        break;
    }

    lib_container_attach_widget(unk10, label);
    append_text_widget_node(&unk2c, label);
    hint->set_scale(0.65f, 0.65f);
    lib_container_attach_widget(unk10, hint);
    append_text_widget_node(&unk2c, hint);
    text = new (0) LibObject178750;
    ItemCreationClass1746A0* clip = new (0) ItemCreationClass1746A0;
    ItemCreationClass1746A0* reset_clip = new (0) ItemCreationClass1746A0;

    if (text == 0 || clip == 0 || reset_clip == 0)
    {
        return 0;
    }

    label_right_edge = 80.0f + lib_text_measure_bounds(label)->unk08;
    clip_x = 18.0f + label_right_edge;
    clip_width = 640.0f - (16.0f + shifted_position(clip_x, 32.0f));
    initial_text_x = 24.0f + label_right_edge;
    lib_scissor_init_rectangle(clip, clip_x, 0.0f, clip_width, 56.0f);
    lib_container_attach_widget(unk10, clip);
    append_clip_widget_node(&unk20, clip);
    lib_text_init_resource_rectangle(text, resource_source, TACTICS_MSG_CHANGE_TACTICS_HELP, 0, initial_text_x, 6.0f, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, text);
    append_text_widget_node(&unk2c, text);
    lib_scissor_init_reset(reset_clip, 1);
    lib_container_attach_widget(unk10, reset_clip);
    append_clip_widget_node(&unk20, reset_clip);

    switch (D_001B643C->callbacks->tactics_mode_flags & 0xF)
    {
    case 1:
        func_slot60(TACTICS_MSG_CHANGE_TACTICS_HELP);
        break;
    case 2:
        func_slot60(TACTICS_MSG_REPLACE_HELP);
        break;
    case 4:
        func_slot60(TACTICS_MSG_FORMATION_HELP);
        break;
    }

    return 1;
}

/** @brief Destroy the scrolling window. */
TacticsHelpWindow::~TacticsHelpWindow()
{
}

/**
 * @brief Initialize the resource window and attach its three displays.
 * @param associated Resource source word forwarded to the base initializer.
 * @return One after the displays are attached.
 */
s32 TacticsResourceWindow::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 16.0f, 16.0f, 20);
    ItemCreationOptionResourceDisplay* first = new (0) ItemCreationOptionResourceDisplay;
    ItemCreationOptionResourceDisplay* second = new (0) ItemCreationOptionResourceDisplay;
    ItemCreationOptionResourceDisplay* third = new (0) ItemCreationOptionResourceDisplay;
    void* allocation = field_get_aligned_allocation(D_001B643C->resources, 11);
    first->unkcc = allocation;
    second->unkcc = allocation;
    third->unkcc = allocation;
    first->unkd0 = 11;
    second->unkd0 = 11;
    third->unkd0 = 11;
    func_002D6440(first, field_find_resource_record(D_001B643C->resources, 5), 0.0f, 0.0f);
    func_002D6440(second, field_find_resource_record(D_001B643C->resources, 6), 256.0f, 0.0f);
    func_002D6440(third, field_find_resource_record(D_001B643C->resources, 7), 512.0f, 0.0f);
    lib_container_attach_widget(unk10, first);
    lib_container_attach_widget(unk10, second);
    lib_container_attach_widget(unk10, third);
    return 1;
}

/** @brief Destroy the resource window. */
TacticsResourceWindow::~TacticsResourceWindow()
{
}

/** @brief Release the loaded resource, detach the State, and dispatch its release handler. */
void TacticsController::func_slot5c()
{
    if (resource_slot != 0)
    {
        lib_release_resource_slot(D_001B657C, resource_slot);
    }

    lib_object_detach_owner(this);
    func_001DD7B0();
}

/** @brief Submit the State to the resident object queue. */
void TacticsController::func_001DD7B0()
{
    resident_enqueue_object(D_001B65F4, this);
}

/** @brief Default update handler that performs no work. */
void FieldListObject::update()
{
}

/**
 * @brief Initialize the State's windows and their resource-mode associations.
 * @return One after setup, or zero when a required window allocation fails.
 */
s32 TacticsController::init_windows()
{
    TacticsResourceWindow* background = new (0) TacticsResourceWindow;
    TacticsHelpWindow* scrolling = new (0) TacticsHelpWindow;

    if (background == 0 || scrolling == 0)
    {
        return 0;
    }

    background->func_slotf4(resource_slot);
    FieldClass153E30::add_child(background);
    background->func_slot40(0);
    scrolling->func_slotf4(resource_slot);
    FieldClass153E30::add_child(scrolling);
    unk24 = scrolling;
    scrolling->func_slot40(background);

    switch (D_001B643C->callbacks->tactics_mode_flags & 0xF)
    {
    case 1:
    {
        TacticsChangeWindow* coordinate = new (0) TacticsChangeWindow;
        TacticsStrategyWindow* child = new (0) TacticsStrategyWindow;

        if (coordinate == 0 || child == 0)
        {
            return 0;
        }

        unk20 = coordinate;
        coordinate->func_slotf4(resource_slot);
        FieldClass153E30::add_child(coordinate);
        coordinate->func_slot40(child);
        child->func_slotf4(resource_slot);
        FieldClass153E30::add_child(child);
        child->func_slot40(coordinate);
        child->func_slot18(0, 0x7F);
        break;
    }
    case 2:
    {
        TacticsReplaceWindow* window = new (0) TacticsReplaceWindow;

        if (window == 0)
        {
            return 0;
        }

        unk20 = window;
        window->func_slotf4(resource_slot);
        FieldClass153E30::add_child(window);
        window->func_slot40(scrolling);
        break;
    }
    case 4:
    {
        TacticsFormationWindow* window = new (0) TacticsFormationWindow;
        TacticsLeaderWindow* child = new (0) TacticsLeaderWindow;

        if (window == 0 || child == 0)
        {
            return 0;
        }

        window->record_selection = selection;
        window->func_slotf4(resource_slot);
        FieldClass153E30::add_child(window);
        window->func_slot40(scrolling);
        window->func_slot48(child);
        child->record_selection = selection;
        child->func_slotf4(resource_slot);
        FieldClass153E30::add_child(child);
        child->func_slot40(window);
        FieldObject23CEA0* grid = child->grid;

        if (grid != 0)
        {
            grid->index = child->candidate_indices_by_slot[child->selected];
            func_0023CB30(grid);
            func_0023CEE0(reinterpret_cast<FieldObject23CEB0*>(child->grid));
            child->grid->unkad = 0;
        }

        highlight_candidate(child, child->candidate_indices_by_slot[child->selected]);

        child->func_slot20(0);
        unk20 = window;
        break;
    }
    }

    windows_initialized = 1;
    return 1;
}

/** @brief Store the alternate window pointer. @param associated Pointer to store. */
void FieldClass15AE70::func_slot48(void* associated)
{
    unk9c = associated;
}

/**
 * @brief Load the completed aligned resource using the State's heap context.
 * @param buffer Completed resource buffer, or null to report failure.
 * @return Zero for a null buffer; otherwise the window initialization result.
 */
s32 TacticsController::on_resource_loaded(void* buffer)
{
    if (buffer == 0)
    {
        return 0;
    }

    TacticsAlignedResource* aligned = aligned_resource(buffer);
    s32 size = aligned->size + 0x80;
    void* saved_heap = resident_get_allocation_heap();
    void* heap = D_001B6430->context->unk70;
    void* memory = resident_heap_allocate(heap, size);

    if (memory != 0)
    {
        resident_heap_release(memory);
        resident_exchange_allocation_heap(heap);
    }

    resource_slot = lib_load_resource_slot(D_001B657C, aligned);
    resident_exchange_allocation_heap(saved_heap);
    return init_windows();
}

/**
 * @brief Allocate and initialize the State's record selection.
 * @return One when a selection exists and initialization succeeds; otherwise zero.
 */
u8 TacticsController::func_00264110()
{
    selection = new (0) FieldRecordSelection;
    u8 result = func_0028E3D0(selection);

    if (selection == 0 || result == 0)
    {
        return 0;
    }

    return 1;
}

/** @brief Release the owned record selection and destroy the State base. */
TacticsController::~TacticsController()
{
    if (selection != 0)
    {
        delete_owned(selection);
    }
}

/** @brief Clear the resource slot, window initialization flag, and selection pointer. */
TacticsController::TacticsController()
{
    resource_slot = 0;
    windows_initialized = 0;
    selection = 0;
}

/** @brief Destroy the coordinate list and movement bases. */
TacticsCoordinateSelector::~TacticsCoordinateSelector()
{
}

/** @brief Perform no work. */
void ItemCreationClass185050::func_slot0c()
{
}

/** @brief Report the default list kind. @return Three. */
s32 TacticsCoordinateSelector::get_default_list_kind()
{
    return 3;
}

/** @brief Leave the default notification hook unchanged. */
void TacticsCoordinateSelector::func_003EEBE0()
{
}

/** @brief Store the window control byte. @param value Control value. */
void FieldClass15AE70::func_slot24(u8 value)
{
    unk0c = value;
}

/** @brief Read the window control byte. @return Stored control value. */
u8 FieldClass15AE70::func_slot28()
{
    return unk0c;
}

/** @brief Store the byte state code. @param value State code. */
void FieldClass15AE70::func_slot2c(u8 value)
{
    unk08 = value;
}

/** @brief Read the byte state code. @return Stored state code. */
u8 FieldClass15AE70::func_slot30()
{
    return unk08;
}

/** @brief Store the halfword state flags. @param value State flags. */
void FieldClass15AE70::func_slot34(u16 value)
{
    unk0a = value;
}

/** @brief Read the halfword state flags. @return Stored state flags. */
u16 FieldClass15AE70::func_slot38()
{
    return unk0a;
}

/** @brief Store the opaque resource source word. @param value Word to store. */
void FieldClass15AE70::func_slot50(u32 value)
{
    unk04 = value;
}

/** @brief Return the nested display container. @return Stored container. */
LibObject178660* FieldClass15AE70::func_slot58()
{
    return unk10;
}

/** @brief Leave the default virtual hook unchanged. */
void FieldClass15AE70::func_slot64()
{
}

/** @brief Leave the default virtual hook unchanged. */
void FieldClass15AE70::func_slot70()
{
}

/** @brief Leave the default virtual hook unchanged. */
void FieldClass15AE70::func_slot74()
{
}

/** @brief Leave the default virtual hook unchanged. */
void FieldClass15AE70::func_slot78()
{
}

/** @brief Leave the default virtual hook unchanged. */
void FieldClass15AE70::func_slot7c()
{
}

/** @brief Leave the default virtual hook unchanged. */
void FieldClass15AE70::func_slot80()
{
}

/** @brief Leave the default virtual hook unchanged. */
void FieldClass15AE70::func_slot84()
{
}

/** @brief Leave the default virtual hook unchanged. */
void FieldClass15AE70::func_slot88()
{
}

/** @brief Leave the default virtual hook unchanged. */
void FieldClass15AE70::func_slot8c()
{
}

/** @brief Leave the default virtual hook unchanged. */
void FieldClass15AE70::func_slot90()
{
}

/** @brief Leave the default virtual hook unchanged. */
void FieldClass15AE70::func_slot94()
{
}

/** @brief Leave the default virtual hook unchanged. */
void FieldClass15AE70::func_slot98()
{
}

/** @brief Leave the default virtual hook unchanged. */
void FieldClass15AE70::func_slot9c()
{
}

/** @brief Leave the default virtual hook unchanged. */
void FieldClass15AE70::func_slota0()
{
}

/** @brief Leave the default virtual hook unchanged. */
void FieldClass15AE70::func_slota4()
{
}

/** @brief Leave the default virtual hook unchanged. */
void FieldClass15AE70::func_slota8()
{
}

/** @brief Leave the default virtual hook unchanged. */
void FieldClass15AE70::func_slotac()
{
}

/** @brief Return the default byte result. @return Zero. */
u8 FieldClass15AE70::func_slotb8()
{
    return 0;
}

/** @brief Return the default byte result. @return Zero. */
u8 FieldClass15AE70::func_slotbc()
{
    return 0;
}

/** @brief Return the default status. @return Zero. */
s32 FieldClass15AE70::func_slotc0()
{
    return 0;
}

/** @brief Return the default status. @return Zero. */
s32 FieldClass15AE70::func_slotc4()
{
    return 0;
}

/** @brief Return the default status. @return Zero. */
s32 FieldClass15AE70::func_slotc8()
{
    return 0;
}

/** @brief Return the default status. @return Zero. */
s32 FieldClass15AE70::func_slotcc()
{
    return 0;
}

/** @brief Return the default status. @return Zero. */
s32 FieldClass15AE70::func_slotd0()
{
    return 0;
}

/** @brief Return the default status. @return Zero. */
s32 FieldClass15AE70::func_slotd4()
{
    return 0;
}

/** @brief Return the default status. @return Zero. */
s32 FieldClass15AE70::func_slotd8()
{
    return 0;
}

/** @brief Return the default status. @return Zero. */
s32 FieldClass15AE70::func_slotdc()
{
    return 0;
}

/** @brief Leave the default virtual hook unchanged. */
void FieldClass15AE70::func_slote0()
{
}

/** @brief Leave the default virtual hook unchanged. */
void FieldClass15AE70::func_slote4()
{
}

/** @brief Read the nested display byte flag. @return Stored flag. */
u8 FieldClass15AE70::func_slote8()
{
    return unk0d;
}

/** @brief Set the nested display byte flag. @param value Flag value. */
void FieldClass15AE70::func_slotec(u8 value)
{
    unk0d = value;
}

/** @brief Leave the default virtual hook unchanged. */
void FieldClass15AE70::func_slotf0()
{
}

/** @brief Leave the default virtual update hook unchanged. */
void FieldClass15AE70::func_slot5c()
{
}

/** @brief Leave the default virtual navigation hook unchanged. */
void FieldClass15AE70::func_slot68()
{
}

/** @brief Leave the default virtual navigation hook unchanged. */
void FieldClass15AE70::func_slot6c()
{
}

/** @brief Return the default window action status. @return Zero. */
u8 FieldClass15AE70::func_slotb0()
{
    return 0;
}

/** @brief Return the default window action status. @return Zero. */
u8 FieldClass15AE70::func_slotb4()
{
    return 0;
}

/** @brief Report whether window setup finished. @return Setup flag. */
u8 TacticsController::windows_ready()
{
    return windows_initialized;
}

/** @brief Return the loaded resource slot. @return Resource slot. */
u32 TacticsController::get_resource_slot()
{
    return resource_slot;
}

/** @brief Report this object's default list kind. @return Four. */
s32 TacticsController::get_default_list_kind()
{
    return 4;
}

/** @brief Store the alternate associated object. @param value Object to store. */
void FieldClass153E30::func_00263C80(void* value)
{
    unk24 = value;
}

/** @brief Store the receiver state byte. @param value State byte. */
void FieldClass153E30::func_00263CA0(s8 value)
{
    unk28 = value;
}

/** @brief Return the receiver state byte. @return State byte. */
s8 FieldClass153E30::func_00263CB0()
{
    return unk28;
}

/** @brief Return the default receiver result. @return Zero. */
s32 FieldClass153E30::func_slot60()
{
    return 0;
}

/** @brief Return the default receiver result. @return Zero. */
s32 FieldClass153E30::func_slot64()
{
    return 0;
}

/** @brief Run the empty receiver hook. */
void FieldClass153E30::func_slot68()
{
}

/** @brief Return the receiver's selection object. @return Null in the base implementation. */
FieldRecordSelection* FieldClass153E30::selected_records()
{
    return 0;
}

/** @brief Run the empty receiver hook. */
void FieldClass153E30::func_slot70()
{
}

/** @brief Run the empty receiver hook. */
void FieldClass153E30::func_slot74()
{
}

/** @brief Run the empty receiver hook. */
void FieldClass153E30::func_slot78()
{
}

/** @brief Return the default receiver result. @return Zero. */
s32 FieldClass153E30::func_slot7c()
{
    return 0;
}

/** @brief Return the default receiver result. @return Zero. */
s32 FieldClass153E30::func_slot80()
{
    return 0;
}

/** @brief Return the default receiver result. @return Zero. */
s32 FieldClass153E30::func_slot84()
{
    return 0;
}

/** @brief Create the head node and start with an empty list. */
TacticsCharacterNameWidgetList::TacticsCharacterNameWidgetList()
{
    head = new (0) FieldListNode;

    if (head == 0)
    {
        throw;
    }

    head->next = 0;
    count = 0;
}

/** @brief Delete the value nodes and the head node. */
TacticsCharacterNameWidgetList::~TacticsCharacterNameWidgetList()
{
    clear_character_name_widget_list(this);

    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

/**
 * @brief Delete every node after the head node and set the count to zero.
 * @param list List to clear. The head node stays allocated.
 */
void clear_character_name_widget_list(TacticsCharacterNameWidgetList* list)
{
    FieldListNode* node = list->head->next;

    if (node == 0)
    {
        return;
    }

    while (node != 0)
    {
        FieldListNode* next = node->next;
        delete node;
        node = next;
    }

    list->head->next = 0;
    list->count = 0;
}

/**
 * @brief Add a node holding `value` to the end of the list.
 * @param list List to append to.
 * @param value Pointer stored in the node. The caller owns it.
 */
void append_cursor_widget_node(FieldCountedList* list, void* value)
{
    FieldListNode* node = new (0) FieldListNode;

    if (node == 0)
    {
        return;
    }

    node->value = value;
    node->next = 0;
    FieldListNode* cursor = list->head;

    while (cursor->next != 0)
    {
        cursor = cursor->next;
    }

    cursor->next = node;
    list->count++;
}

/**
 * @brief Add a node holding `value` to the end of the list.
 * @param list List to append to.
 * @param value Pointer stored in the node. The caller owns it.
 */
void append_grid_widget_node(FieldCountedList* list, void* value)
{
    FieldListNode* node = new (0) FieldListNode;

    if (node == 0)
    {
        return;
    }

    node->value = value;
    node->next = 0;
    FieldListNode* cursor = list->head;

    while (cursor->next != 0)
    {
        cursor = cursor->next;
    }

    cursor->next = node;
    list->count++;
}

/**
 * @brief Add a node holding `value` to the end of the list.
 * @param list List to append to.
 * @param value Pointer stored in the node. The caller owns it.
 */
void append_icon_widget_node(FieldCountedList* list, void* value)
{
    FieldListNode* node = new (0) FieldListNode;

    if (node == 0)
    {
        return;
    }

    node->value = value;
    node->next = 0;
    FieldListNode* cursor = list->head;

    while (cursor->next != 0)
    {
        cursor = cursor->next;
    }

    cursor->next = node;
    list->count++;
}

/**
 * @brief Return the node at `index`. Index zero is the first node after the head node.
 * @param list List to search.
 * @param index Zero-based index among the value nodes.
 * @return The node at that index, or null if the list ends first.
 */
FieldListNode* get_widget_node_at_index(FieldCountedList* list, s32 index)
{
    FieldListNode* node = list->head->next;
    s32 i;

    for (i = 0; i < index; i++)
    {
        if (node == 0)
        {
            return 0;
        }

        node = node->next;
    }

    return node;
}

/** @brief Create the head node and start with an empty list. */
TacticsStatValueWidgetList::TacticsStatValueWidgetList()
{
    head = new (0) FieldListNode;

    if (head == 0)
    {
        throw;
    }

    head->next = 0;
    count = 0;
}

/** @brief Release the stat-value nodes and the head node. */
TacticsStatValueWidgetList::~TacticsStatValueWidgetList()
{
    clear_stat_value_list(this);

    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

/**
 * @brief Add a node holding `value` to the end of the list.
 * @param list List to append to.
 * @param value Pointer stored in the node. The caller owns it.
 */
void append_stat_value_node(FieldCountedList* list, void* value)
{
    FieldListNode* node = new (0) FieldListNode;

    if (node == 0)
    {
        return;
    }

    node->value = value;
    node->next = 0;
    FieldListNode* cursor = list->head;

    while (cursor->next != 0)
    {
        cursor = cursor->next;
    }

    cursor->next = node;
    list->count++;
}

/**
 * @brief Delete every node after the head node and set the count to zero.
 * @param list List to clear. The head node stays allocated.
 */
void clear_stat_value_list(TacticsStatValueWidgetList* list)
{
    FieldListNode* node = list->head->next;

    if (node == 0)
    {
        return;
    }

    while (node != 0)
    {
        FieldListNode* next = node->next;
        delete node;
        node = next;
    }

    list->head->next = 0;
    list->count = 0;
}

/**
 * @brief Return the node at `index`. Index zero is the first node after the head node.
 * @param list List to search.
 * @param index Zero-based index among the value nodes.
 * @return The node at that index, or null if the list ends first.
 */
FieldListNode* get_stat_value_node(FieldCountedList* list, s32 index)
{
    FieldListNode* node = list->head->next;
    s32 i;

    for (i = 0; i < index; i++)
    {
        if (node == 0)
        {
            return 0;
        }

        node = node->next;
    }

    return node;
}

/** @brief Create the head node and start with an empty list. */
TacticsTextWidgetList::TacticsTextWidgetList()
{
    head = new (0) FieldListNode;

    if (head == 0)
    {
        throw;
    }

    head->next = 0;
    count = 0;
}

/** @brief Release the text-widget nodes and the head node. */
TacticsTextWidgetList::~TacticsTextWidgetList()
{
    clear_text_widget_list(this);

    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

/**
 * @brief Add a node holding `value` to the end of the list.
 * @param list List to append to.
 * @param value Pointer stored in the node. The caller owns it.
 */
void append_text_widget_node(FieldCountedList* list, void* value)
{
    FieldListNode* node = new (0) FieldListNode;

    if (node == 0)
    {
        return;
    }

    node->value = value;
    node->next = 0;
    FieldListNode* cursor = list->head;

    while (cursor->next != 0)
    {
        cursor = cursor->next;
    }

    cursor->next = node;
    list->count++;
}

/**
 * @brief Delete every node after the head node and set the count to zero.
 * @param list List to clear. The head node stays allocated.
 */
void clear_text_widget_list(TacticsTextWidgetList* list)
{
    FieldListNode* node = list->head->next;

    if (node == 0)
    {
        return;
    }

    while (node != 0)
    {
        FieldListNode* next = node->next;
        delete node;
        node = next;
    }

    list->head->next = 0;
    list->count = 0;
}

/**
 * @brief Return the node at `index`. Index zero is the first node after the head node.
 * @param list List to search.
 * @param index Zero-based index among the value nodes.
 * @return The node at that index, or null if the list ends first.
 */
FieldListNode* get_text_widget_node(FieldCountedList* list, s32 index)
{
    FieldListNode* node = list->head->next;
    s32 i;

    for (i = 0; i < index; i++)
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
 * @param list List to append to.
 * @param value Pointer stored in the node. The caller owns it.
 */
void append_clip_widget_node(FieldCountedList* list, void* value)
{
    FieldListNode* node = new (0) FieldListNode;

    if (node == 0)
    {
        return;
    }

    node->value = value;
    node->next = 0;
    FieldListNode* cursor = list->head;

    while (cursor->next != 0)
    {
        cursor = cursor->next;
    }

    cursor->next = node;
    list->count++;
}

/**
 * @brief Add a node holding `value` to the end of the list.
 * @param list List to append to.
 * @param value Pointer stored in the node. The caller owns it.
 */
void append_panel_widget_node(FieldCountedList* list, void* value)
{
    FieldListNode* node = new (0) FieldListNode;

    if (node == 0)
    {
        return;
    }

    node->value = value;
    node->next = 0;
    FieldListNode* cursor = list->head;

    while (cursor->next != 0)
    {
        cursor = cursor->next;
    }

    cursor->next = node;
    list->count++;
}

/** @brief Release the coordinate nodes and the head node. */
TacticsCoordinatePositionList::~TacticsCoordinatePositionList()
{
    clear_coordinate_widget_list(this);

    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

/**
 * @brief Delete every coordinate node after the head node and set the count to zero.
 * @param list List to clear. The head node stays allocated.
 */
void clear_coordinate_widget_list(TacticsCoordinatePositionList* list)
{
    TacticsCoordinateNode* node = list->head->next;

    if (node == 0)
    {
        return;
    }

    while (node != 0)
    {
        TacticsCoordinateNode* next = node->next;
        delete node;
        node = next;
    }

    list->head->next = 0;
    list->count = 0;
}

/**
 * @brief Copy `value.x` and `value.y` into a new node at the end of the list.
 * @param list List to append to.
 * @param value Coordinate pair to copy.
 */
void append_coordinate_pair(TacticsCoordinatePositionList* list, TacticsPresetPosition value)
{
    TacticsCoordinateNode* node = new (0) TacticsCoordinateNode;

    if (node == 0)
    {
        return;
    }

    node->x = value.x;
    node->y = value.y;
    node->next = 0;
    TacticsCoordinateNode* cursor = list->head;

    while (cursor->next != 0)
    {
        cursor = cursor->next;
    }

    cursor->next = node;
    list->count++;
}

/** @brief Create the head node and start with an empty list. */
TacticsCoordinatePositionList::TacticsCoordinatePositionList()
{
    head = new (0) TacticsCoordinateNode;

    if (head == 0)
    {
        throw;
    }

    head->next = 0;
    count = 0;
}
