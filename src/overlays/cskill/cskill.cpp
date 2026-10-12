#include "include_asm.h"
#include "overlays/cskill/text.h"
#include "main/resident_data.h"
#include "main/resident_001001E0.h"
#include "main/resident_0010A0E0.h"
#include "overlays/1067-00/text_0028E240.h"
#include "overlays/1067-00/text_0023B1D0.h"
#include "overlays/1067-00/text_marker.h"
#include "overlays/1067-00/grid_marker.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_001E1590.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/lib/resource_widget_inlines.h"
#include "overlays/lib/text_00419A70.h"
#include "overlays/1067-00/text_002D5260.h"
#include "overlays/lib/text_003F90C0.h"
#include "overlays/1067-00/text_002CEAF0.h"

#include "overlays/1067-00/text_002AE9E0.h"
#include "main/resident_0011EE70.h"

#define SKILL_FLAG_ENCODING_MASK 0x7DE3F7E3

/** Message keys in the skill menu bank (resource 89). */
enum SkillMessageKey
{
    SKILL_MSG_TITLE = 0x1770,
    SKILL_MSG_BATTLE_SETUP_HELP = 0x1771,
    SKILL_MSG_SYMBOLOGY_TARGET_HELP = 0x1774,
    SKILL_MSG_SYMBOLOGY_ENABLE_HELP = 0x1775,
    SKILL_MSG_STATUS = 0x1776,
    SKILL_MSG_BATTLE = 0x1777,
    SKILL_MSG_TACTICAL = 0x1778,
    SKILL_MSG_CP = 0x1787,
    SKILL_MSG_NONE = 0x178A,
    SKILL_MSG_SWITCH_ON_OFF = 0x1791,
    SKILL_MSG_DETAILED_SETUP = 0x1792,
    SKILL_MSG_CONFIRM_END_SETUP = 0x1793,
    SKILL_MSG_SKILL = 0x1794,
    SKILL_MSG_BLANK = 0x1795,
    SKILL_MSG_INITIATE = 0x1797,
    SKILL_MSG_YES = 0x1798,
    SKILL_MSG_NO = 0x1799,
    SKILL_MSG_HP_COST = 0x17C3,
    SKILL_MSG_MP_COST = 0x17C4,
    SKILL_MSG_SYMBOLOGY_TITLE = 0x17C7,
    SKILL_MSG_SYMBOLOGY_LABEL = 0x17C8,
    SKILL_MSG_NAME_BASE = 0x18FF,
    SKILL_MSG_INVALID_DESCRIPTION = 0x1A62,
    SKILL_MSG_STATUS_HELP_BASE = 0x1A91,
    SKILL_MSG_TACTICAL_HELP_BASE = 0x1AA3,
    SKILL_MSG_AURA_NAME_BASE = 0x1AAA,
    SKILL_MSG_AURA_HELP_BASE = 0x1AB0,
    SKILL_MSG_DAMAGE_CONVERSION_NAME_BASE = 0x1AB8,
    SKILL_MSG_DAMAGE_CONVERSION_HELP_BASE = 0x1ABA
};

/** Partial 0xC4-byte character record with checksum-protected flags, HP and MP. */
typedef struct SkillCharacterStats
{
    u8 unk00[8];
    u32 encoded_flags;
    s32 encoded_experience;
    u32 encoded_base_hp;
    u32 encoded_max_hp;
    u32 encoded_hp;
    u32 encoded_base_mp;
    u32 encoded_max_mp;
    u32 encoded_mp;
    u8 unk28[0x60];
    u32 flags_experience_checksum;
    u32 hp_checksum;
    u32 mp_checksum;
    u8 unk94[0x14];
    u32 checksum_salt;
    u8 unkac[0x18];
} SkillCharacterStats;

/** Partial menu resource header; resource buffers begin on a 128-byte boundary. */
struct SkillAlignedResource
{
    u8 unk00[0x40];
    s32 size;
};

/** Four-float position with a zero-initializing default constructor. */
typedef struct SkillVector4
{
    /** @brief Initialize every position component to zero. */
    SkillVector4()
    {
        x = y = z = w = 0.0f;
    }
    /** @brief Initialize a position from its components. @param x_value Horizontal component. @param y_value Vertical component. @param z_value Depth component. @param w_value Fourth component. */
    SkillVector4(float x_value, float y_value, float z_value, float w_value)
    {
        x = x_value;
        y = y_value;
        z = z_value;
        w = w_value;
    }
    float x;
    float y;
    float z;
    float w;
} SkillVector4;

struct SkillCharacterEquipment;

/** Selected spell description, mastery, and MP expenditure. */
struct SkillSymbologyHelpWindow : public FieldClass15AE70
{
    /** @brief Initialize the window links and display state. */
    SkillSymbologyHelpWindow();
    /** @brief Release the window base and its display lists. */
    virtual ~SkillSymbologyHelpWindow();
    /** @brief Initialize the window displays. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
    FieldRecordSelection* selection;
    LibObject174D90* description;
    LibObject178750* mastery_label;
    LibObject174F20* mastery_value;
    LibObject178750* mp_cost_label;
    LibObject174F20* mp_cost_value;
};

/** Partial symbology character display with name, MP, and character navigation. */
struct SkillSymbologyCharacterWindow : public FieldClass15AE70
{
    /** @brief Initialize the window links and display state. */
    SkillSymbologyCharacterWindow();
    /** @brief Release the window base and its display lists. */
    virtual ~SkillSymbologyCharacterWindow();
    /**
     * @brief Refresh the selected character's MP display.
     */
    virtual void func_slot5c();
    /** @brief Initialize the window displays. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
    FieldRecordSelection* selection;
    LibObject175140* character_name;
    LibObject178750* mp_label;
    LibObject174F20* mp_value;
    LibObject178750* symbology_level_label;
    LibObject174F20* symbology_level_value;
    LibClass178600* first;
    LibClass178600* second;
    LibClass178600* condition_markers[3];
    struct CharacterMarkerPair
    {
        LibClass178600* available;
        LibClass178600* unavailable;
    } character_markers[8];
    u8 character_slots[8];
    u8 show_party;
};

/** Resource window owning the paired resource displays. */
struct SkillResourceWindow : FieldClass15AE70
{
    /** @brief Initialize the window and clear its initial state. */
    SkillResourceWindow()
    {
        unka8 = 0;
    }
    /** @brief Destroy the window base and its display lists. */
    virtual ~SkillResourceWindow();
    /** @brief Leave the resource-window drawing state unchanged. */
    virtual void func_slot5c();
    /** @brief Initialize the display widgets. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
    u32 unka8;
};

/** Message window associated with the status display. */
struct SkillStatusMessageWindow : FieldClass15AE70
{
    /** @brief Initialize the window and clear its initial state. */
    SkillStatusMessageWindow()
    {
    }
    /** @brief Destroy the window base and its display lists. */
    virtual ~SkillStatusMessageWindow();
    /** @brief Handle a window message key. @param key Signed message key. */
    virtual void func_slot60(s32 key);
    /** @brief Initialize the display widgets. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
};

/** Message window associated with the mode display. */
struct SkillModeMessageWindow : FieldClass15AE70
{
    /** @brief Initialize the window and clear its initial state. */
    SkillModeMessageWindow()
    {
    }
    /** @brief Destroy the window base and its display lists. */
    virtual ~SkillModeMessageWindow();
    /** @brief Handle a window message key. @param key Signed message key. */
    virtual void func_slot60(s32 key);
    /** @brief Initialize the display widgets. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
};

/** Menu controller with DMA notification and Field callback interfaces. */
struct SkillController : public LibClass171FF0, public FieldClass153E30
{
    /** @brief Initialize the controller and clear its window links. */
    SkillController();
    /** @brief Delete the owned record selection and destroy the Field receiver base. */
    virtual ~SkillController();
    /** @brief Report whether window setup finished. @return Setup flag. */
    virtual u8 func_00261D20();
    /** @brief Get the loaded resource handle. @return Resource handle. */
    virtual u32 func_00263CC0();
    /** @brief Report the controller kind. @return Four. */
    virtual s32 func_001DF3D0();
    /** @brief Submit the Field receiver to the resident object queue. */
    virtual void func_001DD7B0();
    /** @brief Allocate and initialize the character record selection. @return One on success, or zero on failure. */
    virtual u8 func_00264110();
    /** @brief Load a completed menu resource and create the windows. @param buffer Completed resource buffer. @return Setup result, or zero without a buffer. */
    virtual s32 func_001E1820(void* buffer);
    /** @brief Create the skill or symbology windows and attach their navigation links. @return One. */
    virtual s32 func_00263CD0();
    /** @brief Release the menu resource and queue the controller for removal. */
    virtual void func_slot5c();
    /** @brief Get the character record selection. @return Owned record selection. */
    virtual FieldRecordSelection* selected_records();
    u8 menu_kind;
    u8 unk39[3];
    u32 resource_slot;
    u8 windows_initialized;
    u8 unk41[3];
    FieldRecordSelection* record_selection;
    u16 selected;
    u8 unk4a[2];
    FieldClass15AE70* window;
    SkillCharacterWindow* status;
    SkillStatusMessageWindow* status_message;
    SkillFourRowSelection* four_rows;
    SkillBattleSetupWindow* status_rows;
    SkillTacticalWindow* mode_query;
    SkillModeMessageWindow* mode_message;
    SkillModeSelection* mode_window;
    SkillDualSelection* paired;
    SkillTextReceiver* text_window;
    SkillSymbologyCharacterWindow* symbology_character;
    SkillSymbologyHelpWindow* symbology_help;
    SkillSymbologyWindow* symbology_spells;
    SkillOptionsWindow* options;
    void* unk84;
    u8 unk88;
    u8 unk89[3];
    FieldRecord* entry;
    SkillCharacterEquipment* detail;
    u8 code;
    u8 unk95[3];
    s32 message;
    u8 row_mode;
    u8 unk9d[3];
    SkillSecondarySelection* secondary;
    u8 unka4[4];
    u16 state;
};

struct SkillDualSelection : public FieldClass15AE70
{
    /** @brief Initialize both grids, the paired display list and empty selection state. */
    SkillDualSelection();
    /** @brief Release the paired display list and destroy the window base. */
    virtual ~SkillDualSelection();
    /** @brief Move the active grid in direction zero. */
    virtual void func_slot68();
    /** @brief Move the active grid in direction one. */
    virtual void func_slot6c();
    /** @brief Cancel the active grid. */
    virtual void func_slot70();
    /** @brief Process the active grid selection. @return Selection event code. */
    virtual s32 func_slotb0();
    /** @brief Restore the associated window. @return Two after restoring the window, or three when absent. */
    virtual s32 func_slotb4();
    /** @brief Leave the grid selection unchanged. @return Zero. */
    virtual s32 func_slotd8();
    /** @brief Leave the grid selection unchanged. @return Zero. */
    virtual s32 func_slotdc();
    /** @brief Initialize both grids. @param associated Full resource source word. @return One on success; zero on allocation failure. */
    virtual s32 func_slotf4(u32 associated);
    FieldObject23CEA0* first;
    FieldObject23CEA0* second;
    FieldObject23BE00* first_display;
    FieldObject23BE00* second_display;
    s16 mode;
    u8 unkba[2];
    FieldRecordSelection* records;
    float first_spacing;
    float second_spacing;
    SkillList183C38 list;
    u8 values[7];
    u8 enabled[2];
    u8 unkdd[3];
    LibClass172600* first_marker;
    LibClass172600* second_marker;
    float first_x;
    float first_y;
    float second_x;
    float second_y;
    u8 count;
    u8 unkf9[3];
    SkillController* owner;
};

/** Mode window with its selection, positions, display lists, and row values. */
struct SkillModeSelection : public FieldClass15AE70
{
    /** @brief Initialize the mode rows, owned list, and controller link. @param owner Window controller. */
    SkillModeSelection(SkillController* owner);
    /** @brief Destroy the mode list and base display lists. */
    virtual ~SkillModeSelection();
    /** @brief Update the active mode window and its list indicator. */
    virtual void func_slot5c();
    /** @brief Ignore the supplied message key. @param key Unused signed message key. */
    virtual void func_slot60(s32 key);
    /** @brief Move the mode selection in direction zero. */
    virtual void func_slot68();
    /** @brief Move the mode selection in direction one. */
    virtual void func_slot6c();
    /** @brief Process the selected mode entry. @return Mode selection event code. */
    virtual s32 func_slotb0();
    /** @brief Restore the associated mode window. @return Mode selection event code. */
    virtual s32 func_slotb4();
    /** @brief Move to the preceding page of mode entries. @return Zero after processing. */
    virtual s32 func_slotd0();
    /** @brief Move to the following page of mode entries. @return Zero after processing. */
    virtual s32 func_slotd4();
    /** @brief Leave the mode window unchanged. @return Zero. */
    virtual s32 func_slotd8();
    /** @brief Leave the mode window unchanged. @return Zero. */
    virtual s32 func_slotdc();
    /** @brief Initialize the window displays. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
    u8 state;
    u8 animation_mode;
    u8 unkaa[2];
    float step;
    float remaining;
    FieldObject23CEA0* selection;
    SkillVector4 first_position;
    SkillVector4 second_position;
    FieldObject23B950* recipient;
    FieldRecordSelection* record_selection;
    u32 unke0;
    s16 mode;
    u8 unke6[2];
    s32 values[42];
    u8 unk190[42];
    u8 unk1ba[42];
    u8 colors[42];
    u8 unk20e[2];
    SkillList183C48 second;
    float spacing;
    float offset;
    float row_height;
    LibClass1725D0* marker;
    float track_size;
    u32 unk230[42];
    s32 item_count;
    s32 count;
    LibObject178750* display;
    u8 flag;
    u8 unk2e5[3];
    SkillController* owner;
};
/** Partial window with a grid-choice callback after its Field virtual interface. */
struct SkillGridChoice : public FieldClass15AE70
{
    /** @brief Initialize an empty grid choice with no selected entry. */
    SkillGridChoice();
    /** @brief Release the window base and optionally its storage. */
    virtual ~SkillGridChoice();
    /**
     * @brief Create the choice panel, text widgets, and two-entry grid.
     * @param associated Full resource source word.
     * @param x Horizontal coordinate.
     * @param y Vertical coordinate.
     * @param code Base display code.
     * @return One after setup, or zero when an allocation fails.
     */
    virtual s32 func_slot10(u32 associated, float x, float y, s32 code);
    /** @brief Refresh the current grid choice. */
    virtual void func_slot5c();
    /** @brief Leave the current choice message unchanged. @param text_key Unused message key. */
    virtual void func_slot60(s32 text_key);
    /** @brief Move the choice grid in direction zero. */
    virtual void func_slot68();
    /** @brief Move the choice grid in direction one. */
    virtual void func_slot6c();
    /** @brief Process the current choice. @return Choice event code. */
    virtual s32 func_slotb0();
    /** @brief Cancel the choice window. @return Two after queuing cancellation. */
    virtual s32 func_slotb4();
    /** @brief Handle the current grid choice. @param selected Selected grid index. */
    virtual void func_slotf4(s16 selected);
    FieldObject23CEA0* selection;
    s16 selected;
};

struct SkillSecondarySelection : FieldClass15AE70
{
    /** @brief Initialize the window and clear its initial state. */
    SkillSecondarySelection()
    {
        owner = 0;
        selection = 0;
        previous = 0;
        code = 0;
        state = 0;
        status = 0;
        four_rows = 0;
        status_rows = 0;
        mode_query = 0;
        cursor = 0;
    }
    /** @brief Destroy the window base and its display lists. */
    virtual ~SkillSecondarySelection();
    /** @brief Refresh the visible window state. */
    virtual void func_slot5c();
    /** @brief Handle a window message key. @param key Signed message key. */
    virtual void func_slot60(s32 key);
    /** @brief Refresh the associated owner and reset the selection state. */
    virtual void func_slot64();
    /** @brief Move the selection in direction zero. */
    virtual void func_slot68();
    /** @brief Move the selection in direction one. */
    virtual void func_slot6c();
    /** @brief Process the selected window. @return Selection event code. */
    virtual s32 func_slotb0();
    /** @brief Open the grid choice. @return Selection event code. */
    virtual s32 func_slotb4();
    /** @brief Cycle the status record in direction zero. @return Selection event code. */
    virtual s32 func_slotd8();
    /** @brief Cycle the status record in direction one. @return Selection event code. */
    virtual s32 func_slotdc();
    /** @brief Initialize the display widgets. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
    SkillController* owner;
    FieldObject23CEA0* selection;
    s16 code;
    s16 previous;
    s16 direction;
    u8 state;
    u8 unkb7;
    SkillCharacterWindow* status;
    FieldObject23BE00* cursor;
    SkillFourRowSelection* four_rows;
    SkillBattleSetupWindow* status_rows;
    SkillTacticalWindow* mode_query;
};

/** Partial four-row window with its record selection, grid, and cursor display. */
struct SkillFourRowSelection : public FieldClass15AE70
{
    /** @brief Initialize the window links and display state. */
    SkillFourRowSelection();
    /** @brief Release the window base and its display lists. */
    virtual ~SkillFourRowSelection();
    /** @brief Refresh the window displays. */
    virtual void func_slot5c();
    /**
     * @brief Move the four-row grid in direction zero and update its row colors and cursor.
     */
    virtual void func_slot68();
    /**
     * @brief Move the four-row grid in direction one and update its row colors and cursor.
     */
    virtual void func_slot6c();
    /** @brief Process the selected entry. */
    virtual s32 func_slotb0();
    /**
     * @brief Reset the four row colors and return to the associated window.
     * @return Two after switching windows, or zero while the grid is inactive.
     */
    virtual s32 func_slotb4();
    /** @brief Retreat the selected record through the active controller. @return Byte event code zero or four. */
    virtual s32 func_slotd8();
    /** @brief Advance the selected record through the active controller. @return Byte event code zero or four. */
    virtual s32 func_slotdc();
    /** @brief Initialize the window displays. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
    FieldRecordSelection* records;
    FieldObject23CEA0* selection;
    FieldClass15AE70* message;
    SkillCharacterWindow* status;
    float row_spacing;
    float first_row_y;
    LibObject178750* first_display;
    LibObject178750* second_display;
    LibClass172870* third_display;
    FieldObject23BE00* cursor;
    LibObject174F20* first_rows[4];
    LibObject174F20* second_rows[4];
    LibObject178750* third_rows[4];
    u8 flag;
};

/** Runtime callback state containing the active controller interface. */
struct SkillRuntimeCallbacks
{
    u8 unk00[0x14];
    FieldClass153E30* controller;
    u8 unk18[2];
    u16 menu_kind;
};

/** Partial resident runtime view. */
struct SkillRuntime
{
    u8 unk00[0xC];
    FieldSlotRecordOwner1C* loader;
    SkillRuntimeCallbacks* callbacks;
    u8 unk14[0xC];
    FieldBufferSlots* resources;
};

/** Linked node containing a pair of float values. */
typedef struct SkillPairListNode
{
    float first;
    float second;
    struct SkillPairListNode* next;

    /** @brief Initialize both stored values to zero. */
    SkillPairListNode()
    {
        second = 0.0f;
        first = 0.0f;
    }

    /** @brief Destroy a paired-value node. */
    ~SkillPairListNode()
    {
    }
} SkillPairListNode;

typedef struct SkillCharacterWindow : public FieldClass15AE70
{
    /** @brief Initialize the status display and controller link. @param owner Window controller. */
    SkillCharacterWindow(SkillController* owner);
    /** @brief Destroy the status window and its base display lists. */
    virtual ~SkillCharacterWindow();
    /** @brief Refresh the active status message. */
    virtual void func_slot5c();
    /** @brief Ignore the supplied message key. @param key Unused signed message key. */
    virtual void func_slot60(s32 key);
    /** @brief Initialize the window displays. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
    FieldRecordSelection* selection;
    LibObject175140* character_name;
    LibObject178750* sp_label;
    LibObject178750* level_label;
    LibObject178750* mastery_label;
    LibObject178750* next_level_label;
    LibObject178750* cp_label;
    LibObject174F20* assigned_cp_value;
    LibObject178750* cp_separator;
    LibObject174F20* available_cp_value;
    LibObject174F20* sp_value;
    LibObject174F20* mastery_values[3];
    LibObject178750* max_level_label;
    u32 unke4[3];
    u8 unkf0[4];
    u8 changed;
    u8 unkf5[3];
    SkillFourRowSelection* four_rows;
    SkillBattleSetupWindow* status_rows;
    SkillTacticalWindow* mode_query;
    SkillModeSelection* mode_window;
    SkillDualSelection* paired;
    LibClass178600* first_display;
    LibClass178600* second_display;
    LibClass178600* icons[8];
    u8 codes[8];
    u8 active;
    u8 unk13d[3];
    SkillController* owner;
} SkillCharacterWindow;

/** Character name, equipment and protected skill setup in the 0x114-byte save record. */
struct SkillCharacterEquipment
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
};

/** Coordinate selector with an owned pair list after its movement state. */
struct SkillCoordinateSelector : public LibClass175030
{
    /** @brief Destroy the coordinate list and movement bases. */
    virtual ~SkillCoordinateSelector();
    /** @brief Report the intrusive object kind. @return Three. */
    virtual s32 func_003EEBC0();
    /** @brief Leave the default update hook unchanged. */
    virtual void func_003EEBD0();
    /** @brief Leave the default notification hook unchanged. */
    virtual void func_003EEBE0();
    SkillPairList184258 nodes;
    s32 selected;
};

/** Options window with a selector and its owned display list. */
struct SkillOptionsWindow : public FieldClass15AE70
{
    /** @brief Initialize an empty options window and its display list. */
    SkillOptionsWindow();
    /** @brief Release the display list and window base. */
    virtual ~SkillOptionsWindow();
    /** @brief Release the listed displays and window attachments. */
    virtual void func_slot0c();
    /** @brief Refresh option display values. */
    virtual void func_slot5c();
    /** @brief Handle an unused message key. @param key Message key. */
    virtual void func_slot60(s32 key);
    /** @brief Move the selector to the preceding row. */
    virtual void func_slot68();
    /** @brief Move the selector to the following row. */
    virtual void func_slot6c();
    /** @brief Move the selector to the preceding entry. */
    virtual void func_slot70();
    /** @brief Move the selector to the following entry. */
    virtual void func_slot74();
    /** @brief Apply the selected options. @return Action status. */
    virtual s32 func_slotb0();
    /** @brief Restore the associated window. @return Two after cancellation. */
    virtual s32 func_slotb4();
    /** @brief Create the option displays. @param associated Full resource source word. @return Setup status. */
    virtual s32 func_slotf4(u32 associated);
    FieldRecordSelection* records;
    SkillCoordinateSelector* child;
    float x;
    float y;
    void* unkb8;
    SkillList184268 nested;
    LibObject174F20* hp_values[8];
    LibObject174F20* mp_values[8];
    LibObject174F20* max_hp_values[8];
    LibObject174F20* max_mp_values[8];
    LibObject175140* labels[8];
    ItemCreationOptionResourceDisplay* indicators[8];
    ItemCreationOptionResourceDisplay* badges[8][4];
    s32 selected_kind;
    s32 selected_index;
};

/** Draw the paired HP and MP gauges for one character. */
struct SkillHpMpGaugeDrawer : public FieldClass159A70
{
    /** @brief Release the drawing packet and base. */
    virtual ~SkillHpMpGaugeDrawer();
    /** @brief Rebuild the drawing packet. @param first Unused draw flag. @param depth Unused drawing depth. @param value Unused drawing value. */
    virtual void func_002BC4F0(u32 first, u32 depth, float value);
    float x;
    float y;
    float row_spacing;
    s16 character_id;
    u8 unk3e[2];
    SkillCharacterStats* characters;
};

/** Tactical skill selection with character links, row modes, and saved character rows. */
typedef struct SkillTacticalWindow : public FieldClass15AE70
{
    /** @brief Initialize tactical row positions, character links, and selection state. */
    SkillTacticalWindow();
    /** @brief Release the window base and its display lists. */
    virtual ~SkillTacticalWindow();
    /**
     * @brief Refresh the selection rows and clear the associated active window's grid-list flags.
     */
    virtual void func_slot5c();
    /**
     * @brief Enable the selection display and show the current row's mode description.
     */
    virtual void func_slot64();
    /**
     * @brief Dispatch direction zero and refresh when the grid reports a change.
     */
    virtual void func_slot68();
    /**
     * @brief Dispatch direction one and refresh when the grid reports a change.
     */
    virtual void func_slot6c();
    /**
     * @brief Apply an eligible selected mode and hide its status displays.
     * @return Zero when inactive or ineligible, three when unavailable, or one after applying the mode.
     */
    virtual s32 func_slotb0();
    /** @brief Save the mode-query choice, clear its pending state, and restore the associated window. @return Zero while inactive, or two after completing the transition. */
    virtual s32 func_slotb4();
    /**
     * @brief Store the cursor for the selected slot and apply its mode.
     * @return Zero when inactive or empty, three when the mode reports three, or one otherwise.
     */
    virtual s32 func_slotbc();
    /** @brief Save the mode-query choice and retreat to the preceding record. @return Event code zero or four. */
    virtual s32 func_slotd8();
    /** @brief Save the mode-query choice and advance the selected record. @return Event code zero or four. */
    virtual s32 func_slotdc();
    /** @brief Initialize the window displays. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
    FieldObject23CEA0* selection;
    s16 unkac[5];
    s16 unkb6;
    float row_x;
    float row_y;
    float row_spacing;
    FieldRecordSelection* records;
    FieldClass15AE70* attachment;
    FieldObject23BE00* cursor;
    u8 active;
    u8 unkd1[3];
    s32 character_rows[12];
    s32 row_count;
    s16 row_modes[6];
    SkillController* parent;
} SkillTacticalWindow;

/** HP and MP gauge transform with drawing and DMA notification interfaces. */
struct SkillHpMpGauge : public FieldClass1599E0, public SkillHpMpGaugeDrawer
{
    /** @brief Release the drawing and transform bases. */
    virtual ~SkillHpMpGauge();
    /** @brief Submit the drawing packet for DMA notification. */
    virtual void func_003EEBE0();
    /** @brief Leave the default update state unchanged. */
    virtual void func_003EEBD0();
    /** @brief Report the transform kind. @return Fourteen. */
    virtual s32 func_003EEBC0();
    /** @brief Detach and queue the gauge for release. */
    virtual void func_003EF740();
    /** @brief Restore the saved transform state. */
    virtual void func_003F4420();
    /** @brief Update gauge visibility and rebuild changed packets. @param first Update enabled. @param second Mark the packet changed. @param third Allow drawing. */
    virtual void func_0044B100(u32 first, u32 second, u32 third);
    /** @brief Complete DMA notification processing. @param value Unused notification value. */
    virtual void func_003F4410(u32 value);
    /** @brief Initialize the gauge transform. @param code Transform code. @param first First transform flag. @param source Transform source. @param x Unused first coordinate. @param y Unused second coordinate. @param z Third coordinate. @return One. */
    virtual s32 initialize(s32 code, s32 first, void* source, float x, float y, float z);
    u8 queued_for_release;
};

typedef struct ListItem0035CCE0
{
    u8 unk00[0x18];
    SkillVector4 position;
    u8 unk28[0x14];
    u8 unk3c;
    u8 unk3d[2];
    u8 unk3f;
    u8 unk40[0x54];
    u32 unk94;
} ListItem0035CCE0;

/** Spell selection grid with two columns and 30 scrolling spell entries. */
typedef struct SkillSymbologyWindow : public FieldClass15AE70
{
    /** @brief Initialize the window links and display state. */
    SkillSymbologyWindow();
    /** @brief Release the window base and its display lists. */
    virtual ~SkillSymbologyWindow();
    /** @brief Refresh the window displays. */
    virtual void func_slot5c();
    /**
     * @brief Set the selected display object's status to one.
     */
    virtual void func_slot64();
    /** @brief Move back two grid entries, scrolling the paired rows at the top edge. */
    virtual void func_slot68();
    /** @brief Advance two grid entries, scrolling the paired rows at the bottom edge. */
    virtual void func_slot6c();
    /** @brief Move back one grid entry, scrolling the paired rows at the top edge. */
    virtual void func_slot70();
    /** @brief Advance one grid entry, scrolling the paired rows at the bottom edge. */
    virtual void func_slot74();
    /**
     * @brief Validate the selected entry and open its options window.
     * @return Zero while inactive, three for a rejected entry, or one after opening its options.
     */
    virtual s32 func_slotb0();
    /**
     * @brief Open a grid-choice window or mark the receiver when its source is busy.
     * @return Two after opening or marking the source, otherwise zero without a loader or allocation.
     */
    virtual s32 func_slotb4();
    /** @brief Refresh the selection display. */
    virtual s32 func_slotbc();
    /**
     * @brief Move the paired display lists toward scroll position zero.
     * @return Zero.
     */
    virtual s32 func_slotc0();
    /**
     * @brief Advance the paired display lists toward scroll position 16.
     * @return Zero.
     */
    virtual s32 func_slotc4();
    /**
     * @brief Move to the previous symbology character when the spell grid is enabled.
     * @return Character change event, or zero when navigation is unavailable.
     */
    virtual s32 func_slotd8();
    /**
     * @brief Advance to the next symbology character when the spell grid is enabled.
     * @return Character change event, or zero when navigation is unavailable.
     */
    virtual s32 func_slotdc();
    /** @brief Initialize the window displays. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
    SkillSymbologyCharacterWindow* character_window;
    FieldRecordSelection* records;
    FieldObject23CEA0* selection;
    u8 unkb4[4];
    ListItem0035CCE0* first[30];
    ListItem0035CCE0* second[30];
    FieldClass153170* cursor;
    s32 selected;
    s32 position;
    s32 shift;
} SkillSymbologyWindow;

typedef struct ListNode0035CCE0
{
    ListItem0035CCE0* value;
    struct ListNode0035CCE0* next;
} ListNode0035CCE0;

/** Partial status attachment exposing its activity byte. */
struct SkillStatusAttachment
{
    u8 unk00[0xCB];
    u8 active;
};

/** Partial six-row Field window with native display lists and value tables. */
typedef struct SkillBattleSetupWindow : public FieldClass15AE70
{
    /** @brief Initialize both display lists, the value tables and controller link. @param owner Window controller. */
    SkillBattleSetupWindow(SkillController* owner);
    /** @brief Release both owned display lists and the window base. */
    virtual ~SkillBattleSetupWindow();
    /** @brief Refresh the active row message. */
    virtual void func_slot5c();
    /** @brief Ignore the supplied message key. @param key Unused signed message key. */
    virtual void func_slot60(s32 key);
    /** @brief Refresh the row positions and selected cursor. */
    virtual void func_slot64();
    /** @brief Move the row selection in direction zero. */
    virtual void func_slot68();
    /** @brief Move the row selection in direction one. */
    virtual void func_slot6c();
    /** @brief Process the selected row. @return Selection event code. */
    virtual s32 func_slotb0();
    /** @brief Restore the associated window. @return Two after restoring the window. */
    virtual s32 func_slotb4();
    /** @brief Cycle the status record in direction zero. @return Record-change event code. */
    virtual s32 func_slotd8();
    /** @brief Cycle the status record in direction one. @return Record-change event code. */
    virtual s32 func_slotdc();
    /** @brief Initialize the window displays. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
    SkillStatusAttachment* attachment;
    FieldObject23CEA0* selection;
    FieldObject23BAB0* display;
    float row_x;
    float row_y;
    float row_spacing;
    float x;
    float y;
    float spacing;
    u8 unkcc[8];
    FieldRecordSelection* record_selection;
    SkillList183C38 second;
    SkillList183C38 third;
    s32 keys[6];
    LibObject174F20* cp_values[7];
    float unk124;
    s32 cp_costs[6];
    s32 first_values[6];
    s32 second_values[6];
    s32 third_values[6];
    u8 flag;
    u8 active;
    u8 unk18a[2];
    SkillController* owner;
} SkillBattleSetupWindow;

/** Menu heading and help text with a delayed horizontal scroll. */
typedef struct SkillHelpWindow : public FieldClass15AE70
{
    /** @brief Initialize the window links and help_text state. */
    SkillHelpWindow();
    /** @brief Release the window base and its help_text lists. */
    virtual ~SkillHelpWindow();
    /**
     * @brief Scroll the help text horizontally after the initial delay.
     */
    virtual void func_slot5c();
    /**
     * @brief Set the menu help text and measure its scrolling width.
     * @param key Text resource key.
     */
    virtual void func_slot60(s32 key);
    /** @brief Initialize the window displays. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
    LibObject178750* help_text;
    s32 text_width;
    u8 unkb0;
    u8 unkb1;
    s16 scroll_delay_frames;
    u8 scrolling;
    u8 unkb5[3];
    float unkb8;
    u32 unkbc;
    u32 unkc0;
    float title_width;
    float text_start_x;
    float clip_left;
    float clip_width;
    s32 menu_kind;
} SkillHelpWindow;

/** Partial storage widget embedded in the battle setup display. */
class FieldClass159FE0 : public LibClass178600
{
public:
    /** @brief Release the widget storage and destroy its base. */
    virtual ~FieldClass159FE0();
    /** @brief Report the intrusive widget kind. @return Three. */
    virtual s32 func_003EEBC0();
    /** @brief Leave the default update hook unchanged. */
    virtual void func_003EEBD0();
    /** @brief Leave the default notification hook unchanged. */
    virtual void func_003EEBE0();
    /** @brief Update the widget drawing state. */
    virtual void func_00413D20();
    /** @brief Draw the widget. */
    virtual void func_00462310();
    LibStorageBlock0C storage;
};

/** Skill CP, Fury and HP/MP costs, with the attack damage multiplier. */
struct SkillCostWindow : FieldClass15AE70
{
    /** @brief Initialize the skill cost displays and controller link. @param owner Window controller. */
    SkillCostWindow(SkillController* owner);
    /** @brief Destroy the skill cost window and its base display lists. */
    virtual ~SkillCostWindow();
    /** @brief Set the skill cost title key. @param key Signed message key. */
    virtual void func_slot60(s32 key);
    /** @brief Initialize the window displays. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
    LibObject178750* title;
    u32 unkac;
    LibObject178750* multiplier_label;
    LibObject178750* damage_label;
    LibObject178750* decimal_point;
    LibObject174F20* multiplier_units;
    LibObject174F20* multiplier_tenths;
    LibObject174F20* multiplier_hundredths;
    LibObject178750* cp_label;
    LibObject174F20* cp_value;
    LibObject178750* fury_label;
    LibObject174F20* fury_value;
    LibObject178750* hp_mp_label;
    LibObject174F20* hp_mp_value;
    SkillController* owner;
};

/** Window containing paired text choices, icons, and values. */
struct SkillTextReceiver : FieldClass15AE70
{
    /** @brief Initialize the window and clear its initial state. */
    SkillTextReceiver()
    {
        display = 0;
        first_choice = 0;
        second_choice = 0;
        first_icon = 0;
        first_value = 0;
        second_icon = 0;
        second_value = 0;
    }
    /** @brief Destroy the window base and its display lists. */
    virtual ~SkillTextReceiver();
    /** @brief Handle a window message key. @param key Signed message key. */
    virtual void func_slot60(s32 key);
    /** @brief Initialize the display widgets. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
    LibObject178750* display;
    LibObject178750* first_choice;
    LibObject178750* second_choice;
    ItemCreationClass174C40* first_icon;
    LibObject178750* first_value;
    ItemCreationClass174C40* second_icon;
    LibObject178750* second_value;
};

extern "C" SkillRuntime* D_001B643C;

/** @brief Set display flags for the selected window lists. @param object Window base. @param flag Flag value. @param lists List-selection bit mask. */
extern "C" void func_002CE530(FieldClass15AE70* object, u32 flag, u32 lists);

extern "C" u64 D_4ED330[];

extern "C" LibVector4 D_50CD30;

extern "C" void func_2CEAF0(void* object, s32 flag);

extern "C" void* func_2BC410(void* object, s16 flag);

extern "C" void* func_002BC280(void* object, s16 flag);

extern "C" void func_44B210(void* record);

extern "C" void* func_4618F0(void* record, s16 flag);

extern "C" void* func_4C48B0(void* record, s16 flag);

extern "C" void func_44B110(void* object, s32 arg1, s32 arg2, void* arg3, float value, s32 flag);

extern "C" void func_2CEBE0(void* object);

extern "C" void func_4CE4C0(void* destination, const void* source);

extern "C" void func_4D00B0(void* object);

extern "C" void func_420D20(FieldObject23B850* object, u32 color);

extern "C" void func_0034BD30(SkillModeSelection* record, s32 index);

extern "C" s32 func_4C6A40(void* item);

/**
 * @brief Read skill costs and the encoded major-attack damage scale.
 * @param code Global skill ID (1-154).
 * @param entry Character stats used to calculate percentage costs.
 * @param detail Character equipment and skill setup.
 * @param minor_mp_cost Minor attack MP cost.
 * @param minor_hp_cost Minor attack HP cost.
 * @param cp_cost CP required to equip the skill.
 * @param minor_fury_cost Minor attack Fury cost.
 * @param major_damage_scale Major damage multiplier times 1024, minus one.
 * @param major_fury_cost Major attack Fury cost.
 * @param major_mp_cost Major attack MP cost.
 * @param major_hp_cost Major attack HP cost.
 * @return Nonzero for a valid skill ID.
 */
extern "C" u8 func_4095C0(s32 code, FieldRecord* entry, SkillCharacterEquipment* detail, s32* minor_mp_cost, s32* minor_hp_cost,
                         s32* cp_cost, s32* minor_fury_cost, s32* major_damage_scale, s32* major_fury_cost,
                         s32* major_mp_cost, s32* major_hp_cost);

/** @brief Locate the aligned resource header. @param buffer Completed resource buffer. @return Aligned header. */
static inline SkillAlignedResource* aligned_skill_resource(void* buffer)
{
    return reinterpret_cast<SkillAlignedResource*>((reinterpret_cast<u32>(buffer) + 0x7F) & ~0x7F);
}

/** @brief Delete an owned object and clear its stored pointer. @param pointer Owned pointer. */
template <class T>
static inline void skill_delete_owned(T*& pointer)
{
    if (pointer != 0)
    {
        delete pointer;
        pointer = 0;
    }
}

/** @brief Refresh the owner message window when its kind requires it. @param owner Controller owner. */
static inline void refresh_owner_message(SkillController* owner)
{
    if (owner->menu_kind == 2)
    {
        FieldClass15AE70* window = owner->window;
        if (window != 0)
        {
            skill_refresh_costs(window);
        }
    }
}

/** @brief Convert an entry resource key to its message index. @param key Entry resource key. @return Message index, or zero for the special entry. */
static inline s32 message_from_key(s32 key)
{
    s32 message;
    s32 index = key - SKILL_MSG_NONE;
    if (index == 0)
    {
        message = 0;
    }
    else
    {
        message = key - SKILL_MSG_NAME_BASE;
    }
    return message;
}

/** @brief Update the optional controller owner's row message. @param owner Optional controller owner. @param row Selected row. @param key Selected entry resource key. */
static inline void set_row_message(SkillController* owner, s16 row, s32 key)
{
    if (owner != 0)
    {
        if (row == 2 || row == 3)
        {
            owner->row_mode = 1;
        }
        else
        {
            owner->row_mode = 0;
        }
        s32 message = key - SKILL_MSG_NAME_BASE;
        if (message < 0)
        {
            message = 0;
        }
        owner->message = message;
        refresh_owner_message(owner);
    }
}

/**
 * @brief Show the selected grid entry's message through the controller's owning window.
 * @param controller Active Field controller interface.
 * @param selection Grid containing the current entry index.
 * @param first_key Resource key for entry zero.
 */
static inline void show_grid_message(FieldClass153E30* controller, FieldObject23CEA0* selection, s32 first_key)
{
    SkillController* owner = static_cast<SkillController*>(controller);
    owner->window->func_slot60(selection->unk114 + first_key);
}

/**
 * @brief Dispatch a movement direction when the grid is active.
 * @param selection Grid receiver.
 * @param direction Signed direction code.
 */
static inline void move_active_grid(FieldObject23CEA0* selection, s16 direction)
{
    u8 inactive = !selection->unk35;
    if (inactive != 1)
    {
        selection->process_direction(direction);
    }
}

/** @brief Advance or retreat the record selection and refresh its linked windows. @param status Status window. @param forward Nonzero to advance. @return Byte event code zero or four. */
static inline s32 cycle_status_record(SkillCharacterWindow* status, s32 forward)
{
    if (status->changed == 1)
    {
        return 0;
    }
    status->selection->active = 0;
    status->changed = 1;
    func_0028E2B0(status->selection, forward);
    if (status->active != 0)
    {
        func_00358310(status);
    }
    if (status->four_rows != 0)
    {
        func_003559F0(status->four_rows);
    }
    if (status->status_rows != 0)
    {
        func_00354190(status->status_rows);
    }
    if (status->mode_query != 0)
    {
        func_00352C00(status->mode_query);
    }
    if (status->mode_window != 0)
    {
        func_00350890(status->mode_window, status->mode_window->mode);
    }
    if (status->paired != 0)
    {
        func_0034B3F0(status->paired);
    }
    return (u8)(status->selection->count == 1 ? 0 : 4);
}

/**
 * @brief Read the salt shared by the character's protected checksums.
 * @param record Protected record.
 * @return Checksum salt.
 */
static inline u32 character_checksum_salt(SkillCharacterStats* record)
{
    return record->checksum_salt;
}

/**
 * @brief Set the skill cost labels visibility.
 * @param object Skill cost window.
 * @param visible Display visibility byte.
 */
static inline void cost_labels(SkillCostWindow* object, u8 visible)
{
    object->multiplier_label->unk3f = visible;
    object->damage_label->unk3f = visible;
    object->cp_label->unk3f = visible;
    object->fury_label->unk3f = visible;
    object->hp_mp_label->unk3f = visible;
}

/**
 * @brief Set the skill cost values visibility.
 * @param object Skill cost window.
 * @param visible Display visibility byte.
 */
static inline void cost_values(SkillCostWindow* object, u8 visible)
{
    object->multiplier_label->unk3f = visible;
    object->multiplier_units->unk3f = visible;
    object->decimal_point->unk3f = visible;
    object->multiplier_tenths->unk3f = visible;
    object->multiplier_hundredths->unk3f = visible;
    object->cp_value->unk3f = visible;
    object->fury_value->unk3f = visible;
    object->hp_mp_value->unk3f = visible;
}

/**
 * @brief Set the skill cost values color.
 * @param object Skill cost window.
 * @param color Packed display color.
 */
static inline void cost_colors(SkillCostWindow* object, u32 color)
{
    object->multiplier_label->set_color(color);
    object->multiplier_units->set_color(color);
    object->decimal_point->set_color(color);
    object->multiplier_tenths->set_color(color);
    object->multiplier_hundredths->set_color(color);
    object->cp_value->set_color(color);
    object->fury_value->set_color(color);
    object->hp_mp_value->set_color(color);
}

/**
 * @brief Hide the attack damage multiplier and label.
 * @param object Skill cost window.
 */
static inline void hide_damage_multiplier(SkillCostWindow* object)
{
    object->damage_label->unk3f = 0;
    object->multiplier_label->unk3f = 0;
    object->multiplier_units->unk3f = 0;
    object->decimal_point->unk3f = 0;
    object->multiplier_tenths->unk3f = 0;
    object->multiplier_hundredths->unk3f = 0;
}

/**
 * @brief Update a numeric image and mark it changed.
 * @param image Numeric image.
 * @param value Image value.
 */
static inline void set_cost_value(LibObject174F20* image, s32 value)
{
    image->numeric_value = value;
    image->unk3c = 1;
}

/**
 * @brief Refresh the optional controller owner's message for the selected mode entry.
 * @param object Mode selection window.
 */
static inline void refresh_mode_message(SkillModeSelection* object)
{
    s16 selected = object->selection->unk114;
    SkillController* owner = static_cast<SkillController*>(D_001B643C->callbacks->controller);
    if (owner != 0)
    {
        s32 message = object->values[selected] - SKILL_MSG_NAME_BASE;
        if (message < 0)
        {
            message = 0;
        }
        owner->message = message;
        refresh_owner_message(owner);
    }
}

/**
 * @brief Set the low byte of each linked display flag.
 * @param list Display list.
 * @param flag Full flag word.
 */
static inline void set_list_display_flags(SkillList183C38* list, u32 flag)
{
    for (SkillListNode* node = list->head->next; node != 0; node = node->next)
    {
        static_cast<LibClass178600*>(node->value)->unk3f = flag & 0xFF;
    }
}

/** @brief Decode current MP, marking valid flags when its checksum fails. */
static inline u32 character_mp(SkillCharacterStats* record)
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
            record->encoded_flags = ((flags ^ SKILL_FLAG_ENCODING_MASK) | 1) ^ SKILL_FLAG_ENCODING_MASK;
            s32 current_salt = record->encoded_experience;
            record->flags_experience_checksum = ((record->encoded_flags + record->checksum_salt) ^ current_salt) ^ record->checksum_salt;
        }
        return 0;
    }
    return encoded ^ SKILL_FLAG_ENCODING_MASK;
}

/** @brief Decode current HP, marking valid flags when its checksum fails. @param record Character stats. @return HP, or zero after corruption. */
static inline u32 character_hp(SkillCharacterStats* record)
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
            record->encoded_flags = ((flags ^ SKILL_FLAG_ENCODING_MASK) | 1) ^ SKILL_FLAG_ENCODING_MASK;
            s32 current_salt = record->encoded_experience;
            record->flags_experience_checksum = ((record->encoded_flags + record->checksum_salt) ^ current_salt) ^ record->checksum_salt;
        }
        return 0;
    }
    return encoded ^ SKILL_FLAG_ENCODING_MASK;
}

/** @brief Clear tactical choice state and its available row count. @param window Tactical selection window. */
static inline void clear_tactical_choices(SkillTacticalWindow* window)
{
    for (s32 i = 0; i < 5; i++)
    {
        window->unkac[i] = 0;
    }
    window->row_count = 0;
}

/**
 * @brief Refresh the mode-query cursor opacity for the active window.
 * @param object Mode-query window.
 */
static inline void refresh_query_cursor(SkillTacticalWindow* object)
{
    if (D_001B643C->callbacks->controller->func_00261150() == object)
    {
        s32 opacity = object->row_count ? 128 : 0;
        LibClass178600* cursor = object->cursor;
        cursor->unk28 = (float)opacity;
        cursor->unk3c = 1;
    }
    else
    {
        LibClass178600* cursor = object->cursor;
        cursor->unk28 = 0.0f;
        cursor->unk3c = 1;
    }
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
 * @brief Set the primary status label and value visibility.
 * @param object Status window.
 * @param visible Display visibility byte.
 */
static inline void status_primary_group(SkillCharacterWindow* object, u8 visible)
{
    object->sp_label->unk3f = visible;
    object->sp_value->unk3f = visible;
}

/**
 * @brief Set detailed status visibility and hide its fallback label.
 * @param object Status window.
 * @param visible Display visibility byte.
 */
static inline void status_detail_group(SkillCharacterWindow* object, u8 visible)
{
    object->level_label->unk3f = visible;
    object->mastery_label->unk3f = visible;
    object->next_level_label->unk3f = visible;
    object->mastery_values[0]->unk3f = visible;
    object->mastery_values[1]->unk3f = visible;
    object->mastery_values[2]->unk3f = visible;
    object->max_level_label->unk3f = 0;
    object->cp_label->unk3f = visible;
    object->assigned_cp_value->unk3f = visible;
    object->cp_separator->unk3f = visible;
    object->available_cp_value->unk3f = visible;
}

/** @brief Decode maximum HP after validating its checksum. @param record Character stats. @return Maximum HP, or zero after corruption. */
static inline u32 character_max_hp(SkillCharacterStats* record)
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
            record->encoded_flags = ((flags ^ SKILL_FLAG_ENCODING_MASK) | 1) ^ SKILL_FLAG_ENCODING_MASK;
            s32 current_salt = record->encoded_experience;
            record->flags_experience_checksum = ((record->encoded_flags + record->checksum_salt) ^ current_salt) ^ record->checksum_salt;
        }
        return 0;
    }
    return salt ^ SKILL_FLAG_ENCODING_MASK;
}

/** @brief Decode maximum MP after validating its checksum. @param record Character stats. @return Maximum MP, or zero after corruption. */
static inline u32 character_max_mp(SkillCharacterStats* record)
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
            record->encoded_flags = ((flags ^ SKILL_FLAG_ENCODING_MASK) | 1) ^ SKILL_FLAG_ENCODING_MASK;
            s32 current_salt = record->encoded_experience;
            record->flags_experience_checksum = ((record->encoded_flags + record->checksum_salt) ^ current_salt) ^ record->checksum_salt;
        }
        return 0;
    }
    return salt ^ SKILL_FLAG_ENCODING_MASK;
}

/**
 * @brief Decode the record flag word after validating its check word.
 * @param record Protected entry record.
 * @return Decoded flags, or five when the check word is invalid.
 */
static inline u32 character_flags(SkillCharacterStats* record)
{
    u32 key = record->checksum_salt;
    u32 value = record->encoded_flags;
    s32 salt = record->encoded_experience;
    if (record->flags_experience_checksum != ((value + key) ^ salt ^ key))
    {
        return 5;
    }
    return value ^ SKILL_FLAG_ENCODING_MASK;
}

/**
 * @brief Write the 8-bit field at offset 0xC.
 * @param value Value to store.
 */
void FieldClass15AE70::func_slot24(u8 value)
{
    unk0c = value;
}

/**
 * @brief Read the 8-bit field at offset 0xC.
 * @return Field value.
 */
u8 FieldClass15AE70::func_slot28()
{
    return unk0c;
}

/**
 * @brief Write the 8-bit field at offset 0x8.
 * @param value Value to store.
 */
void FieldClass15AE70::func_slot2c(u8 value)
{
    unk08 = value;
}

/**
 * @brief Read the 8-bit field at offset 0x8.
 * @return Field value.
 */
u8 FieldClass15AE70::func_slot30()
{
    return unk08;
}

/**
 * @brief Write the 16-bit field at offset 0xA.
 * @param value Value to store.
 */
void FieldClass15AE70::func_slot34(u16 value)
{
    unk0a = value;
}

/**
 * @brief Read the 16-bit field at offset 0xA.
 * @return Field value.
 */
u16 FieldClass15AE70::func_slot38()
{
    return unk0a;
}

/**
 * @brief Store the alternate associated pointer.
 * @param value Pointer to store.
 */
void FieldClass15AE70::func_slot48(void* value)
{
    unk9c = value;
}

/**
 * @brief Return the alternate associated pointer.
 * @return Stored pointer.
 */
void* FieldClass15AE70::func_slot4c()
{
    return unk9c;
}

/**
 * @brief Write the 32-bit field at offset 0x4.
 * @param value Value to store.
 */
void FieldClass15AE70::func_slot50(u32 value)
{
    unk04 = value;
}

/**
 * @brief Read the 32-bit field at offset 0x4.
 * @return Field value.
 */
u32 FieldClass15AE70::func_slot54()
{
    return unk04;
}

/**
 * @brief Return the nested display container.
 * @return Stored container pointer.
 */
LibObject178660* FieldClass15AE70::func_slot58()
{
    return unk10;
}

/** @brief Leave the default window callback unhandled. */
void FieldClass15AE70::func_slot5c()
{
}

/** @brief Leave the default window callback unhandled. */
void FieldClass15AE70::func_slot64()
{
}

/** @brief Leave the default window callback unhandled. */
void FieldClass15AE70::func_slot68()
{
}

/** @brief Leave the default window callback unhandled. */
void FieldClass15AE70::func_slot6c()
{
}

/** @brief Leave the default window callback unhandled. */
void FieldClass15AE70::func_slot70()
{
}

/** @brief Leave the default window callback unhandled. */
void FieldClass15AE70::func_slot74()
{
}

/** @brief Leave the default window callback unhandled. */
void FieldClass15AE70::func_slot78()
{
}

/** @brief Leave the default window callback unhandled. */
void FieldClass15AE70::func_slot7c()
{
}

/** @brief Leave the default window callback unhandled. */
void FieldClass15AE70::func_slot80()
{
}

/** @brief Leave the default window callback unhandled. */
void FieldClass15AE70::func_slot84()
{
}

/** @brief Leave the default window callback unhandled. */
void FieldClass15AE70::func_slot88()
{
}

/** @brief Leave the default window callback unhandled. */
void FieldClass15AE70::func_slot8c()
{
}

/** @brief Leave the default window callback unhandled. */
void FieldClass15AE70::func_slot90()
{
}

/** @brief Leave the default window callback unhandled. */
void FieldClass15AE70::func_slot94()
{
}

/** @brief Leave the default window callback unhandled. */
void FieldClass15AE70::func_slot98()
{
}

/** @brief Leave the default window callback unhandled. */
void FieldClass15AE70::func_slot9c()
{
}

/** @brief Leave the default window callback unhandled. */
void FieldClass15AE70::func_slota0()
{
}

/** @brief Leave the default window callback unhandled. */
void FieldClass15AE70::func_slota4()
{
}

/** @brief Leave the default window callback unhandled. */
void FieldClass15AE70::func_slota8()
{
}

/** @brief Leave the default window callback unhandled. */
void FieldClass15AE70::func_slotac()
{
}

/** @brief Return the default window action result. @return Zero. */
s32 FieldClass15AE70::func_slotb0()
{
    return 0;
}

/** @brief Return the default window action result. @return Zero. */
s32 FieldClass15AE70::func_slotb4()
{
    return 0;
}

/** @brief Return the default window action result. @return Zero. */
s32 FieldClass15AE70::func_slotb8()
{
    return 0;
}

/** @brief Return the default window action result. @return Zero. */
s32 FieldClass15AE70::func_slotbc()
{
    return 0;
}

/** @brief Return the default window action result. @return Zero. */
s32 FieldClass15AE70::func_slotc0()
{
    return 0;
}

/** @brief Return the default window action result. @return Zero. */
s32 FieldClass15AE70::func_slotc4()
{
    return 0;
}

/** @brief Return the default window action result. @return Zero. */
s32 FieldClass15AE70::func_slotc8()
{
    return 0;
}

/** @brief Return the default window action result. @return Zero. */
s32 FieldClass15AE70::func_slotcc()
{
    return 0;
}

/** @brief Return the default window action result. @return Zero. */
s32 FieldClass15AE70::func_slotd0()
{
    return 0;
}

/** @brief Return the default window action result. @return Zero. */
s32 FieldClass15AE70::func_slotd4()
{
    return 0;
}

/** @brief Return the default window action result. @return Zero. */
s32 FieldClass15AE70::func_slotd8()
{
    return 0;
}

/** @brief Return the default window action result. @return Zero. */
s32 FieldClass15AE70::func_slotdc()
{
    return 0;
}

/** @brief Leave the default window callback unhandled. */
void FieldClass15AE70::func_slote0()
{
}

/** @brief Leave the default window callback unhandled. */
void FieldClass15AE70::func_slote4()
{
}

/**
 * @brief Read the 8-bit field at offset 0xD.
 * @return Field value.
 */
u8 FieldClass15AE70::func_slote8()
{
    return unk0d;
}

/**
 * @brief Write the 8-bit field at offset 0xD.
 * @param value Value to store.
 */
void FieldClass15AE70::func_slotec(u8 value)
{
    unk0d = value;
}

/** @brief Leave the default window callback unhandled. */
void FieldClass15AE70::func_slotf0()
{
}

void skill_refresh_costs(FieldClass15AE70* receiver)
{
    SkillCostWindow* object = static_cast<SkillCostWindow*>(receiver);
    if (object->owner == 0)
    {
        return;
    }
    s32 minor_mp_cost = -1, minor_hp_cost = -1, cp_cost = -1, minor_fury_cost = -1, major_damage_scale = -1, major_fury_cost = -1, major_mp_cost = -1,
        major_hp_cost = -1;
    s32 code = object->owner->message;
    FieldRecord* entry = object->owner->entry;
    SkillCharacterEquipment* detail = object->owner->detail;
    s32 mode = object->owner->row_mode;
    if (code == 0)
    {
        cost_labels(object, 0);
        cost_values(object, 0);
        return;
    }
    cost_labels(object, 1);
    if (func_4095C0(code, entry, detail, &minor_mp_cost, &minor_hp_cost, &cp_cost, &minor_fury_cost, &major_damage_scale, &major_fury_cost, &major_mp_cost,
                    &major_hp_cost) != 0)
    {
        major_damage_scale++;
        float scaled = (float)major_damage_scale / 1024.0f;
        scaled *= 100.0f;
        s32 percent = (s32)scaled;
        s32 units = percent / 100;
        s32 tenths = (percent % 100) / 10;
        s32 hundredths = percent % 10;
        s32 value;
        if (mode != 0)
        {
            if (major_mp_cost == 0)
            {
                lib_text_set_resource(object->hp_mp_label, object->func_slot54(), SKILL_MSG_HP_COST, 0);
                value = major_hp_cost;
            }
            else
            {
                lib_text_set_resource(object->hp_mp_label, object->func_slot54(), SKILL_MSG_MP_COST, 0);
                value = major_mp_cost;
            }
            set_cost_value(object->multiplier_units, units);
            set_cost_value(object->multiplier_tenths, tenths);
            set_cost_value(object->multiplier_hundredths, hundredths);
            set_cost_value(object->cp_value, cp_cost);
            set_cost_value(object->fury_value, major_fury_cost);
            set_cost_value(object->hp_mp_value, value);
            cost_colors(object, 0x508050);
        }
        else
        {
            if (minor_mp_cost == 0)
            {
                lib_text_set_resource(object->hp_mp_label, object->func_slot54(), SKILL_MSG_HP_COST, 0);
                value = minor_hp_cost;
            }
            else
            {
                lib_text_set_resource(object->hp_mp_label, object->func_slot54(), SKILL_MSG_MP_COST, 0);
                value = minor_mp_cost;
            }
            set_cost_value(object->multiplier_units, 1);
            set_cost_value(object->multiplier_tenths, 0);
            set_cost_value(object->multiplier_hundredths, 0);
            set_cost_value(object->cp_value, cp_cost);
            set_cost_value(object->fury_value, minor_fury_cost);
            set_cost_value(object->hp_mp_value, value);
            cost_colors(object, 0x288080);
        }
        cost_values(object, 1);
    }
    else
    {
        cost_values(object, 0);
    }
    if (code == 97 || code == 98 || code == 100 || code == 99)
    {
        hide_damage_multiplier(object);
    }
    if (code >= 131 && code < 155)
    {
        hide_damage_multiplier(object);
        object->fury_label->unk3f = 0;
        object->fury_value->unk3f = 0;
        object->hp_mp_label->unk3f = 0;
        object->hp_mp_value->unk3f = 0;
    }
}

void SkillCostWindow::func_slot60(s32 key)
{
    if (this->title != 0)
    {
        u32 source = this->func_slot54();
        lib_text_set_resource(this->title, source, key, 0);
    }
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_00348D10);

SkillCostWindow::~SkillCostWindow()
{
}
SkillCostWindow::SkillCostWindow(SkillController* controller)
{
    title = 0;
    unkac = 0;
    cp_label = 0;
    cp_value = 0;
    multiplier_label = 0;
    damage_label = 0;
    multiplier_units = 0;
    decimal_point = 0;
    multiplier_tenths = 0;
    multiplier_hundredths = 0;
    fury_label = 0;
    fury_value = 0;
    hp_mp_label = 0;
    hp_mp_value = 0;
    owner = 0;
    owner = controller;
}

void func_00349920(u8* object, s32 mode)
{
    if (mode == 0)
    {
        (*(u8**)(object + 0xA8))[0x3F] = 0;
        (*(u8**)(object + 0xB8))[0x3F] = 0;
        (*(u8**)(object + 0xC0))[0x3F] = 0;
        (*(u8**)(object + 0xAC))[0x3F] = 0;
        (*(u8**)(object + 0xB0))[0x3F] = 0;
        (*(u8**)(object + 0xB4))[0x3F] = 0;
        (*(u8**)(object + 0xBC))[0x3F] = 0;
    }
    else if (mode > 0)
    {
        (*(u8**)(object + 0xAC))[0x3F] = 1;
        (*(u8**)(object + 0xB0))[0x3F] = 0;
    }
    else
    {
        (*(u8**)(object + 0xAC))[0x3F] = 0;
        (*(u8**)(object + 0xB0))[0x3F] = 1;
    }
}

s32 SkillTextReceiver::func_slotf4(u32 associated)
{
    this->FieldClass15AE70::func_slot10(associated, 320.0f, 176.0f, 15);
    this->display = new (0) LibObject178750;
    this->first_choice = new (0) LibObject178750;
    this->second_choice = new (0) LibObject178750;
    this->first_icon = new (0) ItemCreationClass174C40;
    this->first_value = new (0) LibObject178750;
    this->second_icon = new (0) ItemCreationClass174C40;
    this->second_value = new (0) LibObject178750;
    this->display->init_resource_rectangle(64.0f, 38.0f, 0.0f, 0.0f, (s32)associated, SKILL_MSG_INITIATE, 0);
    this->first_choice->init_resource_rectangle(140.0f, 38.0f, 0.0f, 0.0f, (s32)associated, SKILL_MSG_YES, 0);
    this->second_choice->init_resource_rectangle(140.0f, 38.0f, 0.0f, 0.0f, (s32)associated, SKILL_MSG_NO, 0);
    this->first_choice->unk3f = 0;
    this->second_choice->unk3f = 0;
    lib_indexed_resource_init(this->first_icon, 35, 64.0f, 86.0f);
    this->first_value->init_resource_rectangle(100.0f, 90.0f, 0.0f, 0.0f, (s32)associated, SKILL_MSG_SWITCH_ON_OFF, 0);
    lib_indexed_resource_init(this->second_icon, 32, 64.0f, 122.0f);
    this->second_value->init_resource_rectangle(100.0f, 126.0f, 0.0f, 0.0f, (s32)associated, SKILL_MSG_DETAILED_SETUP, 0);
    lib_container_attach_widget(this->unk10, this->display);
    lib_container_attach_widget(this->unk10, this->first_choice);
    lib_container_attach_widget(this->unk10, this->second_choice);
    lib_container_attach_widget(this->unk10, this->first_icon);
    lib_container_attach_widget(this->unk10, this->first_value);
    lib_container_attach_widget(this->unk10, this->second_icon);
    lib_container_attach_widget(this->unk10, this->second_value);
    return 1;
}

/** @brief Release the resource widget's storage and destroy its base. */
ItemCreationClass175110::~ItemCreationClass175110()
{
}

SkillTextReceiver::~SkillTextReceiver()
{
}

void func_00349E80(SkillDualSelection* object)
{
    if (object->mode == 0)
    {
        FieldObject23CEA0* selection = object->first;
        SkillController* owner = static_cast<SkillController*>(D_001B643C->callbacks->controller);
        owner->window->func_slot60(object->values[selection->unk114] + SKILL_MSG_AURA_HELP_BASE);
    }
    else if (object->mode == 1)
    {
        show_grid_message(D_001B643C->callbacks->controller, object->second, SKILL_MSG_DAMAGE_CONVERSION_HELP_BASE);
    }
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_00349F30);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_0034A130);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_0034A2B0);

s32 SkillDualSelection::func_slotdc()
{
    return 0;
}

s32 SkillDualSelection::func_slotd8()
{
    return 0;
}

s32 SkillDualSelection::func_slotb4()
{
    FieldClass15AE70* window = static_cast<FieldClass15AE70*>(this->func_slot44());
    if (window == 0)
    {
        return 3;
    }
    LibClass178600* first = this->owner->status->first_display;
    if (first != 0)
    {
        first->unk3f = 1;
    }
    LibClass178600* second = this->owner->status->second_display;
    if (second != 0)
    {
        second->unk3f = 1;
    }
    func_00349F30(this, 2);
    window->func_slot64();
    D_001B643C->callbacks->controller->func_00263C70(window);
    return 2;
}

/** @brief Store the associated object. @param value Object to store. */
void FieldClass153E30::func_00263C70(void* value)
{
    unk20 = value;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_0034A650);

void SkillDualSelection::func_slot70()
{
    if (this->mode == 0)
    {
        u8 inactive = !this->first->unk35;
        if (inactive == 1)
        {
            return;
        }
    }
    else if (this->mode == 1)
    {
        u8 inactive = !this->second->unk35;
        if (inactive == 1)
        {
            return;
        }
    }
    this->func_slotb4();
}

void SkillDualSelection::func_slot6c()
{
    if (this->mode == 0)
    {
        if (this->count <= 1)
        {
            return;
        }
        FieldObject23CEA0* selection = this->first;
        u8 inactive = !selection->unk35;
        if (inactive == 1)
        {
            return;
        }
        if (selection->process_direction(1) != 1)
        {
            func_0034A2B0(this, 0);
            func_00349E80(this);
        }
    }
    else if (this->mode == 1)
    {
        FieldObject23CEA0* selection = this->second;
        u8 inactive = !selection->unk35;
        if (inactive == 1)
        {
            return;
        }
        if (selection->process_direction(1) != 1)
        {
            func_0034A130(this, 0);
            func_00349E80(this);
        }
    }
}

void SkillDualSelection::func_slot68()
{
    if (this->mode == 0)
    {
        if (this->count <= 1)
        {
            return;
        }
        FieldObject23CEA0* selection = this->first;
        u8 inactive = !selection->unk35;
        if (inactive == 1)
        {
            return;
        }
        if (selection->process_direction(0) != 1)
        {
            func_0034A2B0(this, 0);
            func_00349E80(this);
        }
    }
    else if (this->mode == 1)
    {
        FieldObject23CEA0* selection = this->second;
        u8 inactive = !selection->unk35;
        if (inactive == 1)
        {
            return;
        }
        if (selection->process_direction(0) != 1)
        {
            func_0034A130(this, 0);
            func_00349E80(this);
        }
    }
}

/**
 * @brief Configure the second grid and register its newly allocated display object.
 * @param record Receiver containing the second grid and display owner.
 * @return One after setup, otherwise zero without the second grid.
 */
s32 func_0034B190(SkillDualSelection* record)
{
    float x;
    float y;
    if (record->second == 0)
    {
        return 0;
    }
    x = record->unk10->unk20.components[0] + record->second_x;
    y = record->unk10->unk20.components[1] + record->second_y;
    record->second_display = new (0) FieldObject23BE00;
    func_0023BB20(record->second_display, reinterpret_cast<FieldObject23CEB0*>(record->second), 0x808080, record->second_x, record->second_y, 96.0f, 1.0f);
    lib_container_attach_widget(record->unk10, reinterpret_cast<LibClass178600*>(record->second_display));
    func_0035C440(reinterpret_cast<SkillList*>(&record->unk8c), record->second_display);
    func_0023CE80((FieldObject23CE80*)record->second, 1, 2);
    func_0023CE60((FieldObject23CE80*)record->second, 0.0f, record->second_spacing);
    record->second->unkF2 = 0;
    record->second->unk119 = 1;
    func_0023CF50(reinterpret_cast<FieldObject23CEB0*>(record->second), 0, x, y);
    func_0023CEA0(record->second, 0);
    func_0035C4D0(reinterpret_cast<SkillList*>(&record->unk74), record->second);
    return 1;
}

/**
 * @brief Configure the first grid and register its newly allocated display object.
 * @param record Receiver containing the first grid and display owner.
 * @return One after setup, otherwise zero without the first grid.
 */
s32 func_0034B2C0(SkillDualSelection* record)
{
    float x;
    float y;
    if (record->first == 0)
    {
        return 0;
    }
    x = record->unk10->unk20.components[0] + record->first_x;
    y = record->unk10->unk20.components[1] + record->first_y;
    record->first_display = new (0) FieldObject23BE00;
    func_0023BB20(record->first_display, reinterpret_cast<FieldObject23CEB0*>(record->first), 0x808080, record->first_x, record->first_y, 48.0f, 1.0f);
    lib_container_attach_widget(record->unk10, reinterpret_cast<LibClass178600*>(record->first_display));
    func_0035C440(reinterpret_cast<SkillList*>(&record->unk8c), record->first_display);
    func_0023CE80((FieldObject23CE80*)record->first, 1, 7);
    func_0023CE60((FieldObject23CE80*)record->first, 0.0f, record->first_spacing);
    record->first->unkF2 = 0;
    record->first->unk119 = 1;
    func_0023CF50(reinterpret_cast<FieldObject23CEB0*>(record->first), 0, x, y);
    func_0023CEA0(record->first, 0);
    func_0035C4D0(reinterpret_cast<SkillList*>(&record->unk74), record->first);
    return 1;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_0034B3F0);

/** @brief Initialize the scalar indicator storage and select kind five. */
inline ItemCreationClass172600::ItemCreationClass172600()
{
    unk38 = 5;
}

u8 func_0034B720(SkillDualSelection* object)
{
    object->first_spacing = 26.0f;
    object->first_x = 64.0f;
    object->first_y = 14.0f;
    for (s32 index = 0; index < 7; index++)
    {
        LibObject178750* item = new (0) LibObject178750;
        if (item == 0)
        {
            return 0;
        }
        s32 slot = static_cast<s32>(object->func_slot54());
        lib_text_init_resource_rectangle(item, slot, index + SKILL_MSG_AURA_NAME_BASE, 0, object->first_x, object->first_y + object->first_spacing * (float)index, 0.0f, 0.0f);
        item->unk88 = -1.0f;
        item->unk3c = 1;
        lib_container_attach_widget(object->unk10, item);
        func_0035C9D0(reinterpret_cast<SkillList*>(&object->unk2c), item);
    }
    object->first_marker = new (0) LibClass172600;
    func_0041AD10(object->first_marker, object->first_x, object->first_y, 72.0f, 24.0f);
    object->first_marker->unk3d = 0;
    lib_container_attach_widget(object->unk10, object->first_marker);
    object->second_spacing = 48.0f;
    object->second_x = 116.0f;
    object->second_y = 8.0f + (104.0f - object->second_spacing);
    for (s32 index = 0; index < 2; index++)
    {
        LibObject178750* item = new (0) LibObject178750;
        if (item == 0)
        {
            return 0;
        }
        s32 slot = static_cast<s32>(object->func_slot54());
        lib_text_init_resource_rectangle(item, slot, index + SKILL_MSG_DAMAGE_CONVERSION_NAME_BASE, 0, object->second_x, object->second_y + object->second_spacing * (float)index, 0.0f, 0.0f);
        item->unk88 = -1.0f;
        item->unk3c = 1;
        lib_container_attach_widget(object->unk10, item);
        func_0035C9D0(reinterpret_cast<SkillList*>(&object->list), item);
    }
    object->second_marker = new (0) LibClass172600;
    func_0041AD10(object->second_marker, object->second_x, object->second_y, 96.0f, 24.0f);
    object->second_marker->unk3d = 0;
    lib_container_attach_widget(object->unk10, object->second_marker);
    return 1;
}

s32 SkillDualSelection::func_slotf4(u32 associated)
{
    this->FieldClass15AE70::func_slot10(associated, 320.0f, 176.0f, 15);
    LibClass1746A0* first = new (0) LibClass1746A0;
    LibClass1746A0* second = new (0) LibClass1746A0;
    this->first = new (0) FieldObject23CEA0;
    this->second = new (0) FieldObject23CEA0;
    if (first == 0 || second == 0 || this->first == 0 || this->second == 0)
    {
        return 0;
    }
    lib_scissor_init_rectangle(first, 14.0f, 14.0f, 278.0f, 182.0f);
    lib_container_attach_widget(this->unk10, first);
    func_0035CB20(reinterpret_cast<SkillList*>(&this->unk20), first);
    if ((u8)func_0034B720(this) == 0)
    {
        return 0;
    }
    lib_scissor_init_reset(second, 1);
    lib_container_attach_widget(this->unk10, second);
    func_0035CB20(reinterpret_cast<SkillList*>(&this->unk20), second);
    if ((u8)func_0034B2C0(this) == 0 ||
        (u8)func_0034B190(this) == 0)
    {
        return 0;
    }
    func_0034B3F0(this);
    func_0034A2B0(this, 1);
    func_0034A130(this, 1);
    func_00349F30(this, 2);
    return 1;
}

SkillDualSelection::~SkillDualSelection()
{
}

SkillDualSelection::SkillDualSelection()
{
    first = 0;
    first_display = 0;
    first_spacing = 0.0f;
    second = 0;
    second_display = 0;
    second_spacing = 0.0f;
    mode = -1;
    records = 0;
    first_x = 0.0f;
    first_y = 0.0f;
    second_x = 0.0f;
    second_y = 0.0f;
    first_marker = 0;
    second_marker = 0;
    count = 0;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_0034BD30);

void func_0034BEE0(SkillModeSelection* record)
{
    s32 index;
    for (index = 0; index < 42; index++)
    {
        ListItem0035CCE0* first = (ListItem0035CCE0*)func_0035CAE0(reinterpret_cast<SkillList*>(&record->unk2c), index)->value;
        ListItem0035CCE0* second = (ListItem0035CCE0*)func_0035C890(reinterpret_cast<SkillList*>(&record->second), index)->value;
        if (record->values[index] == 0 && index > 0)
        {
            first->unk3f = 0;
            second->unk3f = 0;
        }
        else if (index == record->selection->unk114)
        {
            if (record->colors[index] != 0)
            {
                first->unk94 = 0x288080;
                first->unk3c = 1;
                second->unk94 = 0x288080;
                second->unk3c = 1;
            }
            else
            {
                first->unk94 = 0x505050;
                first->unk3c = 1;
                second->unk94 = 0x505050;
                second->unk3c = 1;
            }
            func_0034BD30(record, index);
            lib_text_measure_bounds(reinterpret_cast<LibObject178750*>(first));
            func_4C6A40(first);
        }
        else if (record->colors[index] != 0)
        {
            first->unk94 = 0x808080;
            first->unk3c = 1;
            second->unk94 = 0x288080;
            second->unk3c = 1;
        }
        else
        {
            first->unk94 = 0x505050;
            first->unk3c = 1;
            second->unk94 = 0x505050;
            second->unk3c = 1;
        }
    }
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_0034C060);

void func_0034C110(SkillModeSelection* record, float offset)
{
    s32 index = 0;
    ListNode0035CCE0* first = reinterpret_cast<ListNode0035CCE0*>(record->unk2c.unk00)->next;
    ListNode0035CCE0* second = reinterpret_cast<ListNode0035CCE0*>(record->second.head)->next;
    while (first != 0)
    {
        ListItem0035CCE0* item = first->value;
        float z;
        float w;
        float second_z;
        float second_w;
        float row;
        float x;
        float y;
        float second_x;
        float second_y;
        row = (float)index;
        x = record->first_position.x;
        y = record->first_position.y;
        z = record->first_position.z;
        w = record->first_position.w;
        y -= offset;
        y += record->spacing * row;
        item->position.x = x;
        item->position.y = y;
        item->position.z = z;
        item->position.w = w;
        item->unk3c = 1;
        item = first->value;
        item->unk94 = 0x808080;
        item->unk3c = 1;
        first = first->next;
        if (second != 0)
        {
            second_x = record->second_position.x;
            second_y = record->second_position.y;
            second_z = record->second_position.z;
            second_w = record->second_position.w;
            second_y -= offset;
            second_y += record->spacing * row;
            item = second->value;
            item->position.x = second_x;
            item->position.y = second_y;
            item->position.z = second_z;
            item->position.w = second_w;
            item->unk3c = 1;
            item = second->value;
            item->unk94 = 0x288080;
            item->unk3c = 1;
            second = second->next;
        }
        index++;
    }
}

/**
 * @brief Refresh the selected item's display receiver and color.
 * @param record Receiver containing the item list and selection state.
 */
void func_0034C1F0(SkillModeSelection* record)
{
    SkillListNode* node = func_0035CAE0(reinterpret_cast<SkillList*>(&record->unk2c), record->selection->unk114);
    if (record->recipient != 0)
    {
        if (record->state != 0 && record->animation_mode == 2)
        {
            record->recipient->flag3F = 0;
        }
        else
        {
            record->recipient->flag3F = 1;
        }
    }
    if (node != 0)
    {
        if (record->recipient == 0)
        {
            record->recipient = (FieldObject23B950*)new (0) FieldClass153170;
            func_0023B850((FieldObject23B850*)record->recipient, (FieldTarget23B850*)node->value, 0x288080);
            lib_container_attach_widget(record->unk10, reinterpret_cast<LibClass178600*>(record->recipient));
        }
        func_0023B7E0(record->recipient, (FieldTarget23B850*)node->value);
        if (record->colors[record->selection->unk114] != 0)
        {
            func_420D20((FieldObject23B850*)record->recipient, 0x288080);
        }
        else
        {
            func_420D20((FieldObject23B850*)record->recipient, 0x505050);
        }
        func_0023B780(record->recipient);
    }
}

/**
 * @brief Update the active mode window and its list indicator.
 */
void SkillModeSelection::func_slot5c()
{
    if (D_001B643C->callbacks->controller->func_00261150() != this)
    {
        return;
    }
    switch (this->state)
    {
    case 0:
    {
        s32 key = this->values[this->selection->unk114];
        if (key == 0)
        {
            return;
        }
        s32 message = message_from_key(key);
        SkillController* owner = static_cast<SkillController*>(D_001B643C->callbacks->controller);
        if (owner != 0)
        {
            if (message < 0)
            {
                message = 0;
            }
            owner->message = message;
            refresh_owner_message(owner);
        }
        break;
    }
    case 1:
        if (this->animation_mode == 2)
        {
            this->step *= -1.0f;
        }
        this->state = 2;
    case 2:
        func_0034C060(this);
        if (this->remaining <= 0.0f)
        {
            this->state = 3;
        }
        else
        {
            break;
        }
    case 3:
        this->animation_mode = 0;
        this->step = 0.0f;
        this->remaining = 0.0f;
        this->state = 0;
        break;
    }
    if (this->count > 0)
    {
        this->marker->unk3f = 1;
        LibClass1725D0* marker = this->marker;
        marker->unk50 = 100.0f * (6.0f / this->track_size);
        marker->unk3c = 1;
        marker = this->marker;
        marker->unk54 = 100.0f * ((float)this->selection->row_count / this->track_size);
        marker->unk3c = 1;
    }
    else
    {
        this->marker->unk3f = 0;
    }
    func_0034C1F0(this);
}

/** @brief Return the associated object. @return Stored object. */
void* FieldClass153E30::func_00261150()
{
    return unk20;
}

s32 SkillModeSelection::func_slotdc()
{
    return 0;
}

s32 SkillModeSelection::func_slotd8()
{
    return 0;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_0034C550);

/** @brief Return the character record selection. @return Owned record selection. */
FieldRecordSelection* SkillController::selected_records()
{
    return record_selection;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_0034C7D0);

s32 SkillModeSelection::func_slotd4()
{
    FieldObject23CEA0* selection = this->selection;
    u8 inactive = !selection->FieldClass151C50::unk35;
    if (inactive == 1)
    {
        return 0;
    }
    if ((s32)this->state > 0)
    {
        return 0;
    }
    s16 first = selection->row_count;
    s16 selected = selection->unk114;
    s32 count = this->item_count;
    s32 first_index;
    s32 last_index = count - 1;
    if (selected >= last_index)
    {
        return 0;
    }
    if (count < 2)
    {
        return 0;
    }
    s32 visible_index;
    if (count < 6)
    {
        visible_index = last_index;
        first_index = 0;
    }
    else
    {
        visible_index = selected - first;
        first_index = first + 6;
        s32 end = first_index + 6;
        if (end >= count)
        {
            visible_index += end - count;
            first_index = count - 6;
            if (visible_index >= 6)
            {
                visible_index = 5;
            }
        }
    }
    this->step = -this->spacing * (float)(first_index - first);
    this->animation_mode = 2;
    func_0034C060(this);
    this->selection->row_count = first_index;
    selection = this->selection;
    selection->index = visible_index;
    func_0023CB30(selection);
    func_0023CEE0(reinterpret_cast<FieldObject23CEB0*>(this->selection));
    func_0034BEE0(this);
    func_0034C1F0(this);
    refresh_mode_message(this);
    refresh_mode_message(this);
    func_0034C1F0(this);
    resident_allocate_request(D_001B65F8, 0, 0, 0, 127, 64, 0);
    return 0;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_0034DCE0);

void SkillModeSelection::func_slot6c()
{
    FieldObject23CEA0* selection = this->selection;
    u8 inactive = !selection->FieldClass151C50::unk35;
    if (inactive == 1)
    {
        return;
    }
    if (this->state > 0)
    {
        return;
    }
    if (selection->unk114 + 1 >= this->item_count)
    {
        return;
    }
    u8 result = selection->process_direction(1);
    if (result == 1)
    {
        return;
    }
    if (result == 3)
    {
        this->state = 1;
        this->step = this->spacing / 4.0f;
        this->remaining = 4.0f;
        this->animation_mode = 2;
    }
    func_0034BEE0(this);
    func_0034C1F0(this);
    refresh_mode_message(this);
    refresh_mode_message(this);
}

void SkillModeSelection::func_slot68()
{
    FieldObject23CEA0* selection = this->selection;
    u8 inactive = !selection->FieldClass151C50::unk35;
    if (inactive == 1)
    {
        return;
    }
    if (this->state > 0)
    {
        return;
    }
    s16 selected = selection->unk114;
    if (selection->row_count == 0 && selected == 0)
    {
        return;
    }
    u8 result = selection->process_direction(0);
    if (result == 1)
    {
        return;
    }
    if (result == 2)
    {
        this->state = 1;
        this->step = this->spacing / 4.0f;
        this->remaining = 4.0f;
        this->animation_mode = 1;
    }
    func_0034BEE0(this);
    func_0034C1F0(this);
    refresh_mode_message(this);
    refresh_mode_message(this);
}

/**
 * @brief Configure the selection grid position and register its display state.
 * @param record Receiver with the display owner and selection grid.
 * @param row_count Number of grid rows; zero leaves the grid unchanged.
 * @return One for zero rows or completed setup, otherwise zero without a display owner.
 */
s32 func_0034E260(SkillModeSelection* record, s16 row_count)
{
    float first;
    float second;
    if (row_count == 0)
    {
        return 1;
    }
    if (record->unk10 == 0)
    {
        return 0;
    }
    first = record->unk10->unk20.components[0] + record->offset;
    second = 16.0f + record->unk10->unk20.components[1];
    func_0023CE80((FieldObject23CE80*)record->selection, 1, row_count);
    func_0023CE60((FieldObject23CE80*)record->selection, 0.0f, record->spacing);
    record->selection->unkF2 = 0;
    record->selection->unk119 = 0;
    reinterpret_cast<FieldObject23CEB0*>(record->selection)->unk116 = 36;
    func_0023CF50(reinterpret_cast<FieldObject23CEB0*>(record->selection), 0, first, second);
    func_0035C4D0(reinterpret_cast<SkillList*>(&record->unk74), record->selection);
    if (record->selection != 0)
    {
        FieldObject23B950* recipient = record->recipient;
        if (recipient != 0)
        {
            recipient->unk28 = 0;
            recipient->flag3C = 1;
        }
        func_0023CEA0((FieldObject23CEA0*)record->selection, 0);
    }
    return 1;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_0034E380);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_0034F1A0);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_0034FB40);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_0034FC30);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_003505C0);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_003506B0);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_00350890);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_00351090);

void func_00351360(SkillModeSelection* object, u32 flag, s32 active)
{
    object->flag = flag;
    object->func_slot18(flag, 2);
    if (object->selection != 0)
    {
        LibClass178600* recipient = reinterpret_cast<LibClass178600*>(object->recipient);
        if (recipient != 0)
        {
            if (active != 0)
            {
                recipient->unk28 = 128.0f;
                recipient->unk3c = 1;
            }
            else
            {
                recipient->unk28 = 0.0f;
                recipient->unk3c = 1;
            }
        }
        func_0023CEA0(object->selection, active);
    }
    SkillListNode* node = object->second.head->next;
    s32 index = 0;
    for (; node != 0; node = node->next, index++)
    {
        if (index == 0)
        {
            static_cast<LibClass178600*>(node->value)->unk3f = 0;
        }
        else
        {
            static_cast<LibClass178600*>(node->value)->unk3f = flag & 0xFF;
        }
    }
    object->display->unk3f = flag;
    if ((u8)flag == 1 && (u8)active == 1)
    {
        func_0034BEE0(object);
    }
    if ((u8)flag == 0)
    {
        object->marker->unk3f = 0;
    }
}

#include "overlays/lib/list_indicator_inlines.h"

s32 SkillModeSelection::func_slotf4(u32 associated)
{
    this->FieldClass15AE70::func_slot10(associated, 320.0f, 176.0f, 15);
    this->display = new (0) LibObject178750;
    this->display->init_resource_rectangle(248.0f, 9.0f, 0.0f, 0.0f, static_cast<s32>(associated), SKILL_MSG_CP, 1);
    lib_container_attach_widget(this->unk10, this->display);
    this->display->set_color(0x288CFF);
    this->display->set_scale(0.6f, 0.6f);
    {
        LibObject178750* display = this->display;
        display->unk88 = 2.0f;
        display->unk3c = 1;
    }
    this->display->unk3f = 0;
    LibClass1746A0* first = new (0) LibClass1746A0;
    LibClass1746A0* second = new (0) LibClass1746A0;
    this->selection = new (0) FieldObject23CEA0;
    if (first == 0 || second == 0 || this->selection == 0)
    {
        return 0;
    }
    lib_scissor_init_rectangle(first, 14.0f, 20.0f, 278.0f, 176.0f);
    lib_container_attach_widget(this->unk10, first);
    func_0035CB20(reinterpret_cast<SkillList*>(&this->unk20), first);
    if ((u8)func_00351090(this) == 0)
    {
        return 0;
    }
    this->marker = new (0) LibClass1725D0;
    lib_list_indicator_init(this->marker, 280.0f, 18.0f, 178.0f, 100.0f, 0.0f);
    lib_container_attach_widget(this->unk10, this->marker);
    this->marker->unk3f = 0;
    lib_scissor_init_reset(second, 1);
    lib_container_attach_widget(this->unk10, second);
    func_0035CB20(reinterpret_cast<SkillList*>(&this->unk20), second);
    if ((u8)func_0034E260(this, 6) == 0)
    {
        return 0;
    }
    return 1;
}

SkillModeSelection::~SkillModeSelection()
{
}
SkillModeSelection::SkillModeSelection(SkillController* controller)
{
    selection = 0;
    spacing = 29.0f;
    offset = 20.0f;
    row_height = 24.0f;
    record_selection = 0;
    state = 0;
    step = 0;
    remaining = 0;
    unke0 = 0;
    recipient = 0;
    mode = -1;
    for (s32 i = 0; i < 42; i++)
    {
        values[i] = 0;
        unk190[i] = 0;
        unk1ba[i] = 0;
        unk230[i] = 0;
        item_count = 0;
    }
    state = 0;
    if (selection != 0)
    {
        func_0023C710(selection);
    }
    marker = 0;
    track_size = 0;
    owner = 0;
    owner = controller;
    flag = 0;
    display = 0;
}

s32 SkillModeMessageWindow::func_slotf4(u32 associated)
{
    func_002CE8D0(reinterpret_cast<FieldObjectCE8D0*>(this), associated, 320.0f, 176.0f, 0xF);
    LibClass178630* widget = new (0) LibClass178630;
    if (widget == 0)
    {
        return 0;
    }
    lib_panel_init_rectangle(widget, 0, 0.0f, 0.0f, 304.0f, 208.0f, 88.0f);
    lib_container_attach_widget(this->unk10, widget);
    return 1;
}

SkillModeMessageWindow::~SkillModeMessageWindow()
{
}

void SkillTacticalWindow::func_slot5c()
{
    func_00351BE0(this);
    if (D_001B643C->callbacks->controller->func_00261150() == this)
    {
        FieldClass15AE70* window = static_cast<FieldClass15AE70*>(this->func_slot4c());
        window->func_slot18(0, 4);
    }
}

void SkillTacticalWindow::func_slot64()
{
    FieldObject23CEA0* selection = this->selection;
    selection->FieldClass151C50::unk30 = 128.0f;
    selection->unkae = 1;
    LibObject178660* display = this->attachment->unk10;
    if (display != 0)
    {
        display->unkab = 1;
    }
    SkillController* owner = static_cast<SkillController*>(D_001B643C->callbacks->controller);
    FieldClass15AE70* window = owner->window;
    if (this->row_count > 0)
    {
        window->func_slot60(this->row_modes[this->selection->unk114] + SKILL_MSG_TACTICAL_HELP_BASE);
    }
    else
    {
        window->func_slot60(SKILL_MSG_BLANK);
    }
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_00351BE0);

void SkillTacticalWindow::func_slot6c()
{
    FieldObject23CEA0* selection = this->selection;
    u8 inactive = !selection->unk35;
    if (inactive == 1)
    {
        return;
    }
    if (this->row_count < 2)
    {
        return;
    }
    if (selection->process_direction(1) != 1)
    {
        func_00351BE0(this);
    }
}

void SkillTacticalWindow::func_slot68()
{
    FieldObject23CEA0* selection = this->selection;
    u8 inactive = !selection->unk35;
    if (inactive == 1)
    {
        return;
    }
    if (this->row_count < 2)
    {
        return;
    }
    if (selection->process_direction(0) != 1)
    {
        func_00351BE0(this);
    }
}

void func_003522C0(SkillTacticalWindow* object)
{
    u8 mode;
    switch (object->row_modes[object->selection->unk114])
    {
    case 4:
        mode = 0;
        break;
    case 5:
        mode = 1;
        break;
    default:
        return;
    }
    SkillDualSelection* window = static_cast<SkillDualSelection*>(object->func_slot4c());
    func_00349F30(window, mode);
    FieldObject23CEA0* selection = object->selection;
    selection->FieldClass151C50::unk30 = 64.0f;
    selection->unkae = 1;
    LibObject178660* display = object->attachment->unk10;
    if (display != 0)
    {
        display->unkab = 0;
    }
    D_001B643C->callbacks->controller->func_00263C70(window);
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_003523A0);

s32 SkillTacticalWindow::func_slotdc()
{
    FieldObject23CEA0* selection = this->selection;
    u8 inactive = !selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    SkillController* owner = static_cast<SkillController*>(D_001B643C->callbacks->controller);
    SkillCharacterWindow* status = owner->status;
    if (owner == 0 || status == 0)
    {
        return 0;
    }
    this->character_rows[(u8)this->records->slots[this->records->current]] = selection->index;
    return cycle_status_record(status, 1);
}

s32 SkillTacticalWindow::func_slotd8()
{
    FieldObject23CEA0* selection = this->selection;
    u8 inactive = !selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    SkillController* owner = static_cast<SkillController*>(D_001B643C->callbacks->controller);
    SkillCharacterWindow* status = owner->status;
    if (owner == 0 || status == 0)
    {
        return 0;
    }
    this->character_rows[(u8)this->records->slots[this->records->current]] = selection->index;
    return cycle_status_record(status, 0);
}

s32 SkillTacticalWindow::func_slotb4()
{
    u8 inactive = !this->selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    this->character_rows[(u8)this->records->slots[this->records->current]] = this->selection->index;
    clear_tactical_choices(this);
    LibObject178660* display = this->attachment->unk10;
    if (display != 0)
    {
        display->unkab = 0;
    }
    FieldClass15AE70* associated = static_cast<FieldClass15AE70*>(this->func_slot44());
    associated->func_slot64();
    D_001B643C->callbacks->controller->func_00263C70(associated);
    this->active = 1;
    func_00351BE0(this);
    if (D_001B643C->callbacks->controller->func_00261150() == this)
    {
        s32 opacity = this->row_count ? 128 : 0;
        LibClass178600* cursor = this->cursor;
        cursor->unk28 = (float)opacity;
        cursor->unk3c = 1;
    }
    else
    {
        LibClass178600* cursor = this->cursor;
        cursor->unk28 = 0.0f;
        cursor->unk3c = 1;
    }
    func_0023CEA0(this->selection, 0);
    return 2;
}

s32 SkillTacticalWindow::func_slotbc()
{
    FieldObject23CEA0* selection = this->selection;
    u8 inactive = !selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    if (this->row_count == 0)
    {
        return 0;
    }
    this->character_rows[(u8)this->records->slots[this->records->current]] = selection->index;
    if (func_003523A0(this) == 3)
    {
        return 3;
    }
    return 1;
}

s32 SkillTacticalWindow::func_slotb0()
{
    FieldObject23CEA0* selection = this->selection;
    u8 inactive = !selection->unk35;
    s16 index;
    s16 mode;
    LibClass178600* display;

    if (inactive == 1)
    {
        return 0;
    }
    index = selection->unk114;
    if (this->row_count == 0)
    {
        return 3;
    }
    mode = this->row_modes[index];
    if (mode == 4 || mode == 5)
    {
        func_003522C0(this);
        display = this->parent->status->first_display;
        if (display != 0)
        {
            display->unk3f = 0;
        }
        display = this->parent->status->second_display;
        if (display != 0)
        {
            display->unk3f = 0;
        }
        return 1;
    }
    return 0;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_00352C00);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_slotf4__19SkillTacticalWindowFUi);

SkillTacticalWindow::~SkillTacticalWindow()
{
}

/** @brief Initialize tactical row positions, character links, and selection state. */
SkillTacticalWindow::SkillTacticalWindow()
{
    selection = 0;
    attachment = 0;
    cursor = 0;
    row_x = 32.0f;
    row_y = 20.0f;
    row_spacing = 36.0f;
    unkb6 = 0;
    row_count = 0;
    records = D_001B643C->callbacks->controller->selected_records();
    clear_tactical_choices(this);
    for (s32 i = 0; i < 5; i++)
    {
        row_modes[i] = 0;
    }
    for (s32 i = 0; i < 12; i++)
    {
        character_rows[i] = 0;
    }
    active = 0;
}

s32 func_003534C0(SkillBattleSetupWindow* owner, s32 mode)
{
    s32 sum = 0;
    s32 i;
    owner->cp_values[0]->unk3f = mode;
    if (mode != 0)
    {
        for (i = 0; i < 6; i++)
        {
            s32 value = owner->cp_costs[i];
            LibObject174F20* item = owner->cp_values[i + 1];
            item->numeric_value = value;
            item->unk3c = 1;
            if (value == -1)
            {
                owner->cp_values[i + 1]->unk3f = 0;
                value = 0;
            }
            else
            {
                owner->cp_values[i + 1]->unk3f = 1;
            }
            sum += value;
        }
    }
    else
    {
        for (i = 0; i < 6; i++)
        {
            owner->cp_values[i + 1]->unk3f = 0;
        }
    }
    return sum;
}

void func_00353570(SkillBattleSetupWindow* object, u32 flag, s32 active)
{
    object->flag = flag;
    object->active = active;
    object->func_slot18(flag, 0x42);
    set_list_display_flags(&object->second, flag);
    set_list_display_flags(&object->third, flag);
    if (active != 0)
    {
        LibClass178600* display = reinterpret_cast<LibClass178600*>(object->display);
        display->unk28 = 128.0f;
        display->unk3c = 1;
    }
    else
    {
        LibClass178600* display = reinterpret_cast<LibClass178600*>(object->display);
        display->unk28 = 0.0f;
        display->unk3c = 1;
    }
    func_0023CEA0(object->selection, active);
    func_003534C0(object, flag);
}

void SkillBattleSetupWindow::func_slot64()
{
    FieldObject23CEA0* selection = this->selection;
    selection->FieldClass151C50::unk30 = 128.0f;
    selection->unkae = 1;
    func_003538F0(this);
    SkillController* owner = static_cast<SkillController*>(D_001B643C->callbacks->controller);
    SkillCharacterWindow* status = owner->status;
    if (owner != 0 && status != 0)
    {
        s32 index = this->selection->unk114;
        if (this->keys[index] == SKILL_MSG_NONE)
        {
            func_003580D0(status, -1, -1, -1);
        }
        else
        {
            func_003580D0(status, this->first_values[index], this->second_values[index], this->third_values[index]);
        }
    }
}

void func_00353720(void* receiver)
{
    SkillBattleSetupWindow* object = static_cast<SkillBattleSetupWindow*>(receiver);
    SkillController* owner = static_cast<SkillController*>(D_001B643C->callbacks->controller);
    FieldObject23CEA0* selection = object->selection;
    FieldClass15AE70* window = owner->window;
    if (selection == 0 || owner == 0 || window == 0)
    {
        return;
    }
    s16 row = selection->unk114;
    s32 key = object->keys[row];
    if (key == SKILL_MSG_NONE)
    {
        owner->message = 0;
        refresh_owner_message(owner);
        window->func_slot60(SKILL_MSG_BLANK);
    }
    else
    {
        set_row_message(owner, row, key);
        s32 text = key + 0xC8;
        if (text >= SKILL_MSG_INVALID_DESCRIPTION)
        {
            window->func_slot60(SKILL_MSG_INVALID_DESCRIPTION);
        }
        else
        {
            window->func_slot60(text);
        }
    }
}

void SkillBattleSetupWindow::func_slot5c()
{
    if (D_001B643C->callbacks->controller->func_00261150() == this)
    {
        func_00353720(this);
    }
}

void func_003538F0(SkillBattleSetupWindow* record)
{
    s32 index;
    for (index = 0; index < 6; index++)
    {
        ListItem0035CCE0* first = (ListItem0035CCE0*)func_0035CAE0(reinterpret_cast<SkillList*>(&record->unk2c), index)->value;
        ListItem0035CCE0* second = (ListItem0035CCE0*)func_0035CAE0(reinterpret_cast<SkillList*>(&record->second), index)->value;
        if (index == record->selection->unk114)
        {
            LibBounds4C69B0* metrics;
            first->unk94 = 0x288080;
            first->unk3c = 1;
            second->unk94 = 0x288080;
            second->unk3c = 1;
            metrics = lib_text_measure_bounds(reinterpret_cast<LibObject178750*>(first));
            func_0023BAB0(record->display, first->position.x,
                         1.0f + (24.0f + first->position.y), 16.0f + metrics->unk08);
        }
        else
        {
            first->unk94 = 0x808080;
            first->unk3c = 1;
            second->unk94 = 0x808080;
            second->unk3c = 1;
        }
    }
}

s32 SkillBattleSetupWindow::func_slotdc()
{
    u8 inactive = !this->selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    SkillController* owner = static_cast<SkillController*>(D_001B643C->callbacks->controller);
    SkillCharacterWindow* status = owner->status;
    if (owner == 0 || status == 0)
    {
        return 0;
    }
    return cycle_status_record(status, 1);
}

s32 SkillBattleSetupWindow::func_slotd8()
{
    u8 inactive = !this->selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    SkillController* owner = static_cast<SkillController*>(D_001B643C->callbacks->controller);
    SkillCharacterWindow* status = owner->status;
    if (owner == 0 || status == 0)
    {
        return 0;
    }
    return cycle_status_record(status, 0);
}

void SkillBattleSetupWindow::func_slot6c()
{
    FieldObject23CEA0* selection = this->selection;
    u8 inactive = !selection->unk35;
    if (inactive == 1)
    {
        return;
    }
    if (selection != 0 && selection->unk114 == 3)
    {
        func_0023CE70(reinterpret_cast<FieldObject23CEB0*>(selection), this->x, this->y + this->spacing);
    }
    if (this->selection->process_direction(1) == 1)
    {
        return;
    }
    if (this->attachment != 0)
    {
        this->attachment->active = 0;
    }
    func_003538F0(this);
    SkillController* owner = static_cast<SkillController*>(D_001B643C->callbacks->controller);
    SkillCharacterWindow* status = owner->status;
    if (owner != 0)
    {
        if (status != 0)
        {
            s32 index = this->selection->unk114;
            if (this->keys[index] == SKILL_MSG_NONE)
            {
                func_003580D0(status, -1, -1, -1);
            }
            else
            {
                func_003580D0(status, this->first_values[index], this->second_values[index], this->third_values[index]);
            }
        }
    }
}

void SkillBattleSetupWindow::func_slot68()
{
    FieldObject23CEA0* selection = this->selection;
    u8 inactive = !selection->unk35;
    if (inactive == 1)
    {
        return;
    }
    if (selection != 0 && selection->unk114 == 4)
    {
        func_0023CE70(reinterpret_cast<FieldObject23CEB0*>(selection), this->x, this->y);
    }
    if (this->selection->process_direction(0) == 1)
    {
        return;
    }
    if (this->attachment != 0)
    {
        this->attachment->active = 0;
    }
    func_003538F0(this);
    SkillController* owner = static_cast<SkillController*>(D_001B643C->callbacks->controller);
    SkillCharacterWindow* status = owner->status;
    if (owner != 0)
    {
        if (status != 0)
        {
            s32 index = this->selection->unk114;
            if (this->keys[index] == SKILL_MSG_NONE)
            {
                func_003580D0(status, -1, -1, -1);
            }
            else
            {
                func_003580D0(status, this->first_values[index], this->second_values[index], this->third_values[index]);
            }
        }
    }
}

s32 SkillBattleSetupWindow::func_slotb4()
{
    u8 inactive = !this->selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    SkillController* owner = this->owner;
    if (owner != 0)
    {
        owner->message = 0;
        refresh_owner_message(owner);
    }
    for (s32 index = 0; index < 6; index++)
    {
        ListItem0035CCE0* first = static_cast<ListItem0035CCE0*>(func_0035CAE0(reinterpret_cast<SkillList*>(&this->unk2c), index)->value);
        if (first != 0)
        {
            first->unk94 = 0x808080;
            first->unk3c = 1;
        }
        ListItem0035CCE0* second = static_cast<ListItem0035CCE0*>(func_0035CAE0(reinterpret_cast<SkillList*>(&this->second), index)->value);
        if (second != 0)
        {
            second->unk94 = 0x808080;
            second->unk3c = 1;
        }
    }
    SkillModeSelection* mode = static_cast<SkillModeSelection*>(this->func_slot4c());
    if (mode != 0 && this->selection != 0)
    {
        func_00351360(mode, 0, 0);
    }
    func_00353570(this, 1, 0);
    FieldClass15AE70* associated = static_cast<FieldClass15AE70*>(this->func_slot44());
    associated->func_slot64();
    D_001B643C->callbacks->controller->func_00263C70(associated);
    return 2;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_00354060);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_00354190);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_003547C0);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_00354D80);

FieldClass159FE0::~FieldClass159FE0()
{
}

/** @brief Destroy the embedded intrusive links. */
LibClass178A70::~LibClass178A70()
{
}

SkillBattleSetupWindow::~SkillBattleSetupWindow()
{
}
SkillBattleSetupWindow::SkillBattleSetupWindow(SkillController* controller)
{
    attachment = 0;
    selection = 0;
    row_x = 0.0f;
    row_y = 0.0f;
    row_spacing = 0.0f;
    x = 0.0f;
    y = 0.0f;
    spacing = 0.0f;
    record_selection = 0;
    display = 0;
    cp_values[0] = 0;
    unk124 = 258.0f;
    for (s32 index = 0; index < 6; index++)
    {
        keys[index] = 0;
        cp_costs[index] = -1;
        cp_values[index + 1] = 0;
        first_values[index] = -1;
        second_values[index] = -1;
        third_values[index] = -1;
    }
    flag = 0;
    active = 0;
    owner = 0;
    owner = controller;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_slot5c__21SkillFourRowSelectionFv);

void func_003558B0(SkillFourRowSelection* object, u32 flag, s32 active)
{
    object->flag = flag;
    object->func_slot18(flag, 10);
    object->first_display->unk3f = flag;
    object->second_display->unk3f = flag;
    object->third_display->unk3f = flag;
    object->cursor->unk3f = flag;
    if (active != 0)
    {
        LibClass178600* cursor = object->cursor;
        cursor->unk28 = 128.0f;
        cursor->unk3c = 1;
    }
    else
    {
        LibClass178600* cursor = object->cursor;
        cursor->unk28 = 0.0f;
        cursor->unk3c = 1;
    }
    func_0023CEA0(object->selection, active);
    if (active != 0)
    {
        object->message->func_slot60(SKILL_MSG_STATUS_HELP_BASE + object->selection->unk114);
    }
    if ((u8)flag == 0)
    {
        for (s32 index = 0; index < 4; index++)
        {
            object->first_rows[index]->unk3f = 0;
            object->second_rows[index]->unk3f = 0;
            object->third_rows[index]->unk3f = 0;
        }
    }
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_003559F0);

void SkillFourRowSelection::func_slot6c()
{
    FieldObject23CEA0* selection = this->selection;
    u8 inactive = !selection->unk35;
    if (inactive == 1)
    {
        return;
    }
    if (selection->process_direction(1) == 1)
    {
        return;
    }
    for (s32 index = 0; index < 4; index++)
    {
        LibObject178750* item = static_cast<LibObject178750*>(func_0035CAE0(reinterpret_cast<SkillList*>(&this->unk2c), index)->value);
        if (index == this->selection->unk114)
        {
            item->unk94 = 0x288080;
            item->unk3c = 1;
            LibBounds4C69B0* metrics = lib_text_measure_bounds(item);
            func_0023B9B0(this->cursor, (s16)index, metrics->unk08);
        }
        else
        {
            item->unk94 = 0x808080;
            item->unk3c = 1;
        }
    }
}

void SkillFourRowSelection::func_slot68()
{
    FieldObject23CEA0* selection = this->selection;
    u8 inactive = !selection->unk35;
    if (inactive == 1)
    {
        return;
    }
    if (selection->process_direction(0) == 1)
    {
        return;
    }
    for (s32 index = 0; index < 4; index++)
    {
        LibObject178750* item = static_cast<LibObject178750*>(func_0035CAE0(reinterpret_cast<SkillList*>(&this->unk2c), index)->value);
        if (index == this->selection->unk114)
        {
            item->unk94 = 0x288080;
            item->unk3c = 1;
            LibBounds4C69B0* metrics = lib_text_measure_bounds(item);
            func_0023B9B0(this->cursor, (s16)index, metrics->unk08);
        }
        else
        {
            item->unk94 = 0x808080;
            item->unk3c = 1;
        }
    }
}

s32 SkillFourRowSelection::func_slotdc()
{
    u8 inactive = !this->selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    SkillController* owner = static_cast<SkillController*>(D_001B643C->callbacks->controller);
    SkillCharacterWindow* status = owner->status;
    if (owner == 0 || status == 0)
    {
        return 0;
    }
    return cycle_status_record(status, 1);
}

s32 SkillFourRowSelection::func_slotd8()
{
    u8 inactive = !this->selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    SkillController* owner = static_cast<SkillController*>(D_001B643C->callbacks->controller);
    SkillCharacterWindow* status = owner->status;
    if (owner == 0 || status == 0)
    {
        return 0;
    }
    return cycle_status_record(status, 0);
}

s32 SkillFourRowSelection::func_slotb4()
{
    u8 inactive = !this->selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    for (s32 index = 0; index < 4; index++)
    {
        LibObject178750* item = static_cast<LibObject178750*>(func_0035CAE0(reinterpret_cast<SkillList*>(&this->unk2c), index)->value);
        item->unk94 = 0x808080;
        item->unk3c = 1;
    }
    func_003558B0(this, 1, 0);
    static_cast<FieldClass15AE70*>(this->func_slot44())->func_slot64();
    FieldClass153E30* controller = D_001B643C->callbacks->controller;
    controller->func_00263C70(this->func_slot44());
    return 2;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_slotb0__21SkillFourRowSelectionFv);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_00356CB0);

u32 skill_character_mp(SkillCharacterStats* record)
{
    return character_mp(record);
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_00356F80);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_00357000);

u32 skill_character_hp(SkillCharacterStats* record)
{
    return character_hp(record);
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_003572D0);

u32 skill_add_character_flags(SkillCharacterStats* record, u32 flags)
{
    u32 key = record->checksum_salt;
    u32 value = record->encoded_flags;
    s32 salt = record->encoded_experience;
    u32 checksum = record->flags_experience_checksum;
    if (checksum != ((value + key) ^ salt ^ key))
    {
        return 5;
    }
    record->encoded_flags = ((value ^ SKILL_FLAG_ENCODING_MASK) | flags) ^ SKILL_FLAG_ENCODING_MASK;
    s32 current_salt = record->encoded_experience;
    record->flags_experience_checksum = ((record->encoded_flags + record->checksum_salt) ^ current_salt) ^ record->checksum_salt;
    return record->encoded_flags ^ SKILL_FLAG_ENCODING_MASK;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_003573D0);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_003575A0);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_slotf4__21SkillFourRowSelectionFUi);

SkillFourRowSelection::~SkillFourRowSelection()
{
}

SkillFourRowSelection::SkillFourRowSelection()
{
    records = 0;
    selection = 0;
    message = 0;
    status = 0;
    row_spacing = 32.0f;
    first_row_y = 62.0f;
    first_display = 0;
    second_display = 0;
    third_display = 0;
    cursor = 0;
    flag = 0;
    for (s32 i = 0; i < 4; i++)
    {
        first_rows[i] = 0;
        second_rows[i] = 0;
        third_rows[i] = 0;
    }
}

s32 SkillStatusMessageWindow::func_slotf4(u32 associated)
{
    func_002CE8D0(reinterpret_cast<FieldObjectCE8D0*>(this), associated, 16.0f, 176.0f, 0x11);
    LibClass178630* widget = new (0) LibClass178630;
    if (widget == 0)
    {
        return 0;
    }
    lib_panel_init_rectangle(widget, 0, 0.0f, 0.0f, 304.0f, 208.0f, 88.0f);
    func_0035CBB0(reinterpret_cast<SkillList*>(&this->unk14), widget);
    lib_container_attach_widget(this->unk10, widget);
    return 1;
}

SkillStatusMessageWindow::~SkillStatusMessageWindow()
{
}

void func_003580D0(SkillCharacterWindow* owner, s32 first, s32 second, s32 third)
{
    if (second == -1)
    {
        owner->mastery_values[1]->unk3f = 0;
    }
    else
    {
        LibObject174F20* item = owner->mastery_values[1];
        item->numeric_value = second - 1;
        item->unk3c = 1;
        owner->mastery_values[1]->unk3f = 1;
    }
    if (first == -1)
    {
        owner->mastery_values[0]->unk3f = 0;
    }
    else
    {
        LibObject174F20* item = owner->mastery_values[0];
        item->numeric_value = first;
        item->unk3c = 1;
        owner->mastery_values[0]->unk3f = 1;
    }
    if (third == -1)
    {
        owner->mastery_values[2]->unk3f = 0;
        owner->max_level_label->unk3f = 0;
    }
    else if (first == 10)
    {
        owner->mastery_values[2]->unk3f = 0;
        owner->max_level_label->unk3f = 1;
    }
    else
    {
        LibObject174F20* item = owner->mastery_values[2];
        item->numeric_value = third;
        item->unk3c = 1;
        owner->mastery_values[2]->unk3f = 1;
        owner->max_level_label->unk3f = 0;
    }
}

void SkillCharacterWindow::func_slot5c()
{
    SkillCharacterWindow* record = this;
    if (record->changed == 1)
    {
        if (record->selection->active == 1)
        {
            func_00358200(record);
            record->changed = 0;
        }
    }
}

void func_00358200(SkillCharacterWindow* record)
{
    SkillCharacterEquipment* detail;
    u32 key;
    s32 value;
    LibObject175140* name_display;
    LibObject174F20* item;

    name_display = record->character_name;
    name_display->unkfc = static_cast<SkillCharacterEquipment*>(record->selection->unk04)[record->selection->current].character_name;
    name_display->unk3c = 1;
    detail = &static_cast<SkillCharacterEquipment*>(record->selection->unk04)[record->selection->current];
    key = detail->checksum_salt;
    value = (detail->sp_cp_checksum != (((detail->encoded_cp + key) ^ detail->encoded_sp) ^ key)) ? 0 : (detail->encoded_sp ^ 0x7E93);
    item = record->sp_value;
    item->numeric_value = value;
    item->unk3c = 1;
    if (record->selection != 0)
    {
        detail = &static_cast<SkillCharacterEquipment*>(record->selection->unk04)[record->selection->current];
        if (detail != 0)
        {
            key = detail->checksum_salt;
            value = (detail->sp_cp_checksum != (((detail->encoded_cp + key) ^ detail->encoded_sp) ^ key)) ? 0 : (detail->encoded_cp ^ 0x7E93);
            item = record->available_cp_value;
            item->numeric_value = value;
            item->unk3c = 1;
        }
    }
}

void func_00358310(SkillCharacterWindow* object)
{
    if (object->active != 0 && object->selection != 0)
    {
        u16 code = object->selection->slots[object->selection->current];
        s32 selected = 0;
        for (s32 i = 0; i < 8; i++)
        {
            LibClass178600* icon = object->icons[i];
            if (icon != 0)
            {
                icon->unk3f = 0;
            }
        }
        for (s32 i = 0; i < 8; i++)
        {
            if (code == object->codes[i])
            {
                break;
            }
            selected++;
        }
        LibClass178600* icon = object->icons[selected];
        if (icon != 0)
        {
            icon->unk3f = 1;
        }
        SkillController* record = object->owner;
        if (record != 0)
        {
            FieldRecordSelection* selection = object->selection;
            s8 index = selection->current;
            SkillCharacterEquipment* detail = &static_cast<SkillCharacterEquipment*>(selection->unk04)[index];
            FieldRecord* entry = &selection->records[index];
            record->entry = entry;
            record->detail = detail;
            record->code = code;
        }
    }
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_00358410);

SkillCharacterWindow::~SkillCharacterWindow()
{
}
SkillCharacterWindow::SkillCharacterWindow(SkillController* controller)
{
    selection = 0;
    character_name = 0;
    sp_value = 0;
    mastery_values[0] = 0;
    mastery_values[1] = 0;
    mastery_values[2] = 0;
    unke4[0] = 0;
    unke4[1] = 0;
    unke4[2] = 0;
    four_rows = 0;
    status_rows = 0;
    mode_query = 0;
    mode_window = 0;
    paired = 0;
    changed = 0;
    cp_label = 0;
    assigned_cp_value = 0;
    cp_separator = 0;
    available_cp_value = 0;
    for (s32 index = 0; index < 8; index++)
    {
        icons[index] = 0;
        codes[index] = 0;
    }
    active = 0;
    first_display = 0;
    second_display = 0;
    owner = 0;
    owner = controller;
}

/** Partial secondary selection control and its state byte. */
void SkillSecondarySelection::func_slot64()
{
    FieldObject23CEA0* selection = this->selection;
    selection->FieldClass151C50::unk30 = 128.0f;
    selection->unkae = 1;
    SkillController* owner = static_cast<SkillController*>(D_001B643C->callbacks->controller);
    func_0035AF00(owner, this->code, 1);
    this->state = 0;
}

void SkillSecondarySelection::func_slot5c()
{
    if (D_001B643C->callbacks->controller->func_00261150() != this)
    {
        return;
    }
    u8 inactive = !this->selection->unk35;
    if (inactive == 1)
    {
        return;
    }
    if (this->state != 1)
    {
        return;
    }
    s32 key = this->code + SKILL_MSG_BATTLE_SETUP_HELP;
    FieldClass15AE70* window = static_cast<FieldClass15AE70*>(D_001B643C->callbacks->controller->func_00263C90());
    window->func_slot60(key);
    s16 selected = this->code;
    for (s32 index = 0; index <= 2; index++)
    {
        ListItem0035CCE0* item = static_cast<ListItem0035CCE0*>(func_0035CAE0(reinterpret_cast<SkillList*>(&this->unk2c), index)->value);
        if (index == selected)
        {
            item->unk94 = 0x288080;
            item->unk3c = 1;
            LibBounds4C69B0* metrics = lib_text_measure_bounds(reinterpret_cast<LibObject178750*>(item));
            func_0023B9B0(this->cursor, (s16)index, metrics->unk08);
        }
        else
        {
            item->unk94 = 0x808080;
            item->unk3c = 1;
        }
    }
    this->state = 0;
}

void FieldClass15AE70::func_slot60(s32 key)
{
}

/** @brief Return the alternate associated object. @return Stored object. */
void* FieldClass153E30::func_00263C90()
{
    return unk24;
}

s32 SkillSecondarySelection::func_slotdc()
{
    if (this->func_slot28())
    {
        return 0;
    }
    u8 inactive = !this->selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    return cycle_status_record(this->status, 1);
}

s32 SkillSecondarySelection::func_slotd8()
{
    if (this->func_slot28())
    {
        return 0;
    }
    u8 inactive = !this->selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    return cycle_status_record(this->status, 0);
}

s32 SkillSecondarySelection::func_slotb4()
{
    FieldSlotRecordOwner1C* loader = D_001B643C->loader;
    if (loader == 0)
    {
        return 0;
    }
    u8 ready = loader->unk2d != 0;
    if (ready == 1)
    {
        this->set_state(1, 0x80);
    }
    else
    {
        SkillGridChoice* choice = new (0) SkillGridChoice;
        if (choice == 0)
        {
            return 0;
        }
        choice->func_slot10(this->func_slot54(), 192.0f, 160.0f, 5);
        choice->func_slot40(this);
        D_001B643C->callbacks->controller->add_child(choice);
        D_001B643C->callbacks->controller->func_00263C70(choice);
    }
    return 2;
}

s32 SkillSecondarySelection::func_slotb0()
{
    u8 inactive = !this->selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    u16 code = this->selection->unk114;
    SkillController* selected_owner = this->owner;
    selected_owner->selected = code;
    func_0035AF00(selected_owner, selected_owner->selected, 1);
    switch (code)
    {
    case 1:
    {
        func_003559F0(this->four_rows);
        SkillFourRowSelection* window = this->four_rows;
        for (s32 index = 0; index < 4; index++)
        {
            LibClass174EF0* item = static_cast<LibClass174EF0*>(func_0035CAE0(reinterpret_cast<SkillList*>(&window->unk2c), index)->value);
            if (index == window->selection->unk114)
            {
                item->unk94 = 0x288080;
                item->unk3c = 1;
                LibBounds4C69B0* metrics = lib_text_measure_bounds(reinterpret_cast<LibObject178750*>(item));
                func_0023B9B0(window->cursor, (s16)index, metrics->unk08);
            }
            else
            {
                item->unk94 = 0x808080;
                item->unk3c = 1;
            }
        }
        func_003558B0(this->four_rows, 1, 1);
        func_00353570(this->status_rows, 0, 0);
        SkillTacticalWindow* query = this->mode_query;
        query->active = 0;
        query->func_slot18(0, 2);
        func_00349920(reinterpret_cast<u8*>(query->attachment), 0);
        refresh_query_cursor(query);
        func_0023CEA0(query->selection, 0);
        this->owner->func_00263C70(this->four_rows);
        break;
    }
    case 0:
    {
        func_00354190(this->status_rows);
        func_003538F0(this->status_rows);
        func_00353720(this->status_rows);
        FieldClass153E30* controller = D_001B643C->callbacks->controller;
        SkillBattleSetupWindow* window = this->status_rows;
        SkillController* owner = static_cast<SkillController*>(controller);
        SkillCharacterWindow* status = owner->status;
        if (owner != 0 && status != 0)
        {
            s32 index = window->selection->unk114;
            if (window->keys[index] == SKILL_MSG_NONE)
            {
                func_003580D0(status, -1, -1, -1);
            }
            else
            {
                func_003580D0(status, window->first_values[index], window->second_values[index], window->third_values[index]);
            }
        }
        func_00353570(this->status_rows, 1, 1);
        func_003558B0(this->four_rows, 0, 0);
        SkillTacticalWindow* query = this->mode_query;
        query->active = 0;
        query->func_slot18(0, 2);
        func_00349920(reinterpret_cast<u8*>(query->attachment), 0);
        refresh_query_cursor(query);
        func_0023CEA0(query->selection, 0);
        this->owner->func_00263C70(this->status_rows);
        break;
    }
    case 2:
    {
        this->owner->func_00263C70(this->mode_query);
        func_00352C00(this->mode_query);
        if (this->owner->paired != 0)
        {
            func_0034B3F0(this->owner->paired);
        }
        func_00351BE0(this->mode_query);
        SkillTacticalWindow* query = this->mode_query;
        if (query->attachment != 0)
        {
            if (query->row_count != 0)
            {
                LibObject178660* display = query->attachment->unk10;
                if (display != 0)
                {
                    display->unkab = 1;
                }
            }
            else
            {
                LibObject178660* display = query->attachment->unk10;
                if (display != 0)
                {
                    display->unkab = 0;
                }
            }
        }
        query = this->mode_query;
        query->active = 1;
        func_00351BE0(query);
        refresh_query_cursor(query);
        func_0023CEA0(query->selection, 1);
        func_00353570(this->status_rows, 0, 0);
        func_003558B0(this->four_rows, 0, 0);
        FieldClass153E30* controller = D_001B643C->callbacks->controller;
        query = this->mode_query;
        SkillController* owner = static_cast<SkillController*>(controller);
        FieldClass15AE70* window = owner->window;
        if (query->row_count > 0)
        {
            window->func_slot60(query->row_modes[query->selection->unk114] + SKILL_MSG_TACTICAL_HELP_BASE);
        }
        else
        {
            window->func_slot60(SKILL_MSG_BLANK);
        }
        break;
    }
    }
    FieldObject23CE80* selection = reinterpret_cast<FieldObject23CE80*>(this->selection);
    selection->unkE0 = 64.0f;
    selection->unkAE = 1;
    return 1;
}

void SkillSecondarySelection::func_slot6c()
{
    if (this->func_slot28())
    {
        return;
    }
    if (this->selection->process_direction(1) == 1)
    {
        return;
    }
    this->previous = this->code;
    this->code = this->selection->unk114;
    if (this->previous == this->code)
    {
        return;
    }
    this->direction = 1;
    this->state = 1;
    SkillController* owner = static_cast<SkillController*>(D_001B643C->callbacks->controller);
    func_0035AF00(owner, this->code, 1);
}

void SkillSecondarySelection::func_slot68()
{
    if (this->func_slot28())
    {
        return;
    }
    if (this->selection->process_direction(0) == 1)
    {
        return;
    }
    this->previous = this->code;
    this->code = this->selection->unk114;
    if (this->previous == this->code)
    {
        return;
    }
    this->direction = 0;
    this->state = 1;
    SkillController* owner = static_cast<SkillController*>(D_001B643C->callbacks->controller);
    func_0035AF00(owner, this->code, 1);
}

s32 SkillSecondarySelection::func_slotf4(u32 associated)
{
    this->FieldClass15AE70::func_slot10(associated, 16.0f, 72.0f, 8);
    this->owner = static_cast<SkillController*>(D_001B643C->callbacks->controller);
    LibClass178630* panel = new (0) LibClass178630;
    LibObject178750* first = new (0) LibObject178750;
    LibObject178750* second = new (0) LibObject178750;
    LibObject178750* third = new (0) LibObject178750;
    this->selection = new (0) FieldObject23CEA0;
    if (this->owner == 0 || panel == 0 || first == 0 || second == 0 || third == 0 || this->selection == 0)
    {
        return 0;
    }
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 200.0f, 104.0f, 88.0f);
    func_0035CBB0(reinterpret_cast<SkillList*>(&this->unk14), panel);
    lib_container_attach_widget(this->unk10, panel);
    second->init_resource_rectangle(70.0f, 13.0f, 0.0f, 0.0f, (s32)associated, SKILL_MSG_BATTLE, 0);
    first->init_resource_rectangle(70.0f, 40.0f, 0.0f, 0.0f, (s32)associated, SKILL_MSG_STATUS, 0);
    third->init_resource_rectangle(70.0f, 67.0f, 0.0f, 0.0f, (s32)associated, SKILL_MSG_TACTICAL, 0);
    lib_container_attach_widget(this->unk10, second);
    func_0035C9D0(reinterpret_cast<SkillList*>(&this->unk2c), second);
    lib_container_attach_widget(this->unk10, first);
    func_0035C9D0(reinterpret_cast<SkillList*>(&this->unk2c), first);
    lib_container_attach_widget(this->unk10, third);
    func_0035C9D0(reinterpret_cast<SkillList*>(&this->unk2c), third);
    second->unk94 = 0x288080;
    second->unk3c = 1;
    ItemCreationOptionResourceDisplay* icon_first = new (0) ItemCreationOptionResourceDisplay;
    ItemCreationOptionResourceDisplay* icon_second = new (0) ItemCreationOptionResourceDisplay;
    ItemCreationOptionResourceDisplay* icon_third = new (0) ItemCreationOptionResourceDisplay;
    void* resource = func_002D3D80(D_001B643C->resources, 0);
    icon_first->unkcc = resource;
    icon_second->unkcc = resource;
    icon_third->unkcc = resource;
    icon_first->unkd0 = 0;
    icon_second->unkd0 = 0;
    icon_third->unkd0 = 0;
    icon_second->func_002D6440(func_002D3CC0(D_001B643C->resources, 0x12), 32.0f, 11.0f);
    icon_first->func_002D6440(func_002D3CC0(D_001B643C->resources, 0x14), 32.0f, 38.0f);
    icon_third->func_002D6440(func_002D3CC0(D_001B643C->resources, 0x15), 32.0f, 65.0f);
    lib_container_attach_widget(this->unk10, icon_first);
    lib_container_attach_widget(this->unk10, icon_second);
    lib_container_attach_widget(this->unk10, icon_third);
    LibBounds4C69B0* metrics = lib_text_measure_bounds(first);
    this->cursor = new (0) FieldObject23BE00;
    this->cursor->func_0023BB20(70.0f, 13.0f, metrics->unk08, 1.0f, this->selection, 0x288080);
    lib_container_attach_widget(this->unk10, this->cursor);
    func_0035C440(reinterpret_cast<SkillList*>(&this->unk8c), this->cursor);
    this->selection->func_0023CE80(1, 3);
    this->selection->func_0023CE60(0.0f, 27.0f);
    this->selection->unkF2 = 0;
    this->selection->unk119 = 1;
    this->selection->func_0023CF50(0, 56.0f, 85.0f);
    func_0035C4D0(reinterpret_cast<SkillList*>(&this->unk74), this->selection);
    return 1;
}

SkillSecondarySelection::~SkillSecondarySelection()
{
}

void SkillHelpWindow::func_slot5c()
{
    LibObject178750* help_text = this->help_text;
    float x = help_text->unk18.unk00;
    float y = help_text->unk18.unk04;
    float z = help_text->unk18.unk08;
    float w = help_text->unk18.unk0c;
    if (this->scrolling == 0)
    {
        help_text->unk18.unk00 = this->text_start_x;
        help_text->unk18.unk04 = y;
        help_text->unk18.unk08 = z;
        help_text->unk18.unk0c = w;
        help_text->unk3c = 1;
        this->scroll_delay_frames++;
        if (!((float)this->scroll_delay_frames <= 120.0f))
        {
            this->scroll_delay_frames = 0;
            this->scrolling = 1;
        }
        return;
    }
    {
        float clip_left = this->clip_left;
        x -= 108.0f * D_001B6690;
        if (x < clip_left - (float)this->text_width)
        {
            x = 2.0f + (clip_left + this->clip_width);
        }
        help_text->unk18.unk00 = x;
        help_text->unk18.unk04 = y;
        help_text->unk18.unk08 = z;
        help_text->unk18.unk0c = w;
        help_text->unk3c = 1;
    }
}

void SkillHelpWindow::func_slot60(s32 key)
{
    if (key >= SKILL_MSG_BATTLE_SETUP_HELP && key <= SKILL_MSG_SYMBOLOGY_ENABLE_HELP)
    {
        this->scrolling = 0;
        this->scroll_delay_frames = 0;
        u32 source = this->func_slot54();
        lib_text_set_resource(this->help_text, source, key, 0);
        LibBounds4C69B0* bounds = lib_text_measure_bounds(this->help_text);
        this->text_width = (s32)bounds->unk08 + 6;
    }
}

s32 SkillHelpWindow::func_slotf4(u32 associated)
{
    this->FieldClass15AE70::func_slot10(associated, 16.0f, 16.0f, 19);
    LibObject178750* first = new (0) LibObject178750;
    LibObject178750* second = new (0) LibObject178750;
    s32 menu_kind = this->menu_kind;
    if (menu_kind == 1)
    {
        first->init_resource_rectangle(16.0f, 5.0f, 0.0f, 0.0f, (s32)associated, SKILL_MSG_SYMBOLOGY_TITLE, 0);
        second->init_resource_rectangle(36.0f, 40.0f, 0.0f, 0.0f, (s32)associated, SKILL_MSG_SYMBOLOGY_LABEL, 0);
    }
    else if (menu_kind == 2)
    {
        first->init_resource_rectangle(16.0f, 5.0f, 0.0f, 0.0f, (s32)associated, SKILL_MSG_TITLE, 0);
        second->init_resource_rectangle(36.0f, 40.0f, 0.0f, 0.0f, (s32)associated, SKILL_MSG_SKILL, 0);
        first->set_scale(1.1f, 1.1f);
    }
    else
    {
        first->init_resource_rectangle(16.0f, 5.0f, 0.0f, 0.0f, (s32)associated, SKILL_MSG_TITLE, 0);
        second->init_resource_rectangle(36.0f, 40.0f, 0.0f, 0.0f, (s32)associated, SKILL_MSG_SKILL, 0);
    }
    lib_container_attach_widget(this->unk10, first);
    func_0035C9D0(reinterpret_cast<SkillList*>(&this->unk2c), first);
    second->set_scale(0.65f, 0.65f);
    lib_container_attach_widget(this->unk10, second);
    func_0035C9D0(reinterpret_cast<SkillList*>(&this->unk2c), second);
    this->help_text = new (0) LibObject178750;
    ItemCreationClass1746A0* first_frame = new (0) ItemCreationClass1746A0;
    ItemCreationClass1746A0* second_frame = new (0) ItemCreationClass1746A0;
    if (this->help_text == 0 || first_frame == 0 || second_frame == 0)
    {
        return 0;
    }
    this->title_width = lib_text_measure_bounds(first)->unk08;
    this->clip_left = 18.0f + this->title_width;
    this->clip_width = 640.0f - (16.0f + shifted_position(this->clip_left, 32.0f));
    this->text_start_x = 24.0f + this->title_width;
    lib_scissor_init_rectangle(first_frame, this->clip_left, 0.0f, this->clip_width, 56.0f);
    lib_container_attach_widget(this->unk10, first_frame);
    func_0035CB20(reinterpret_cast<SkillList*>(&this->unk20), first_frame);
    this->help_text->init_resource_rectangle(this->text_start_x, 6.0f, 0.0f, 0.0f, (s32)associated, SKILL_MSG_BATTLE_SETUP_HELP, 0);
    lib_container_attach_widget(this->unk10, this->help_text);
    func_0035C9D0(reinterpret_cast<SkillList*>(&this->unk2c), this->help_text);
    lib_scissor_init_reset(second_frame, 1);
    lib_container_attach_widget(this->unk10, second_frame);
    func_0035CB20(reinterpret_cast<SkillList*>(&this->unk20), second_frame);
    this->func_slot60(SKILL_MSG_BATTLE_SETUP_HELP);
    return 1;
}

SkillHelpWindow::~SkillHelpWindow()
{
}

SkillHelpWindow::SkillHelpWindow()
{
    help_text = 0;
    text_width = 0;
    unkb0 = 0xFF;
    scrolling = 0;
    scroll_delay_frames = 0;
    unkb8 = -96.0f;
    unkbc = 0;
    unkc0 = 0;
    title_width = 0;
    text_start_x = 0;
    clip_left = 0;
    clip_width = 0;
    menu_kind = 1;
}

void SkillResourceWindow::func_slot5c()
{
}

s32 SkillResourceWindow::func_slotf4(u32 associated)
{
    this->FieldClass15AE70::func_slot10(associated, 16.0f, 16.0f, 20);
    ItemCreationOptionResourceDisplay* first = new (0) ItemCreationOptionResourceDisplay;
    ItemCreationOptionResourceDisplay* second = new (0) ItemCreationOptionResourceDisplay;
    ItemCreationOptionResourceDisplay* third = new (0) ItemCreationOptionResourceDisplay;
    void* resource = func_002D3D80(D_001B643C->resources, 11);
    first->unkcc = resource;
    second->unkcc = resource;
    third->unkcc = resource;
    first->unkd0 = 11;
    second->unkd0 = 11;
    third->unkd0 = 11;
    first->func_002D6440(func_002D3CC0(D_001B643C->resources, 5), 0.0f, 0.0f);
    second->func_002D6440(func_002D3CC0(D_001B643C->resources, 6), 256.0f, 0.0f);
    third->func_002D6440(func_002D3CC0(D_001B643C->resources, 7), 512.0f, 0.0f);
    lib_container_attach_widget(this->unk10, first);
    lib_container_attach_widget(this->unk10, second);
    lib_container_attach_widget(this->unk10, third);
    return 1;
}

SkillResourceWindow::~SkillResourceWindow()
{
}

void func_0035AF00(SkillController* owner, s32 code, u8 enabled)
{
    switch (code)
    {
    case 1:
    {
        SkillCharacterWindow* status = owner->status;
        status_primary_group(status, 1);
        FieldRecordSelection* selection = status->selection;
        SkillCharacterEquipment* detail = &static_cast<SkillCharacterEquipment*>(selection->unk04)[selection->current];
        u32 key = detail->checksum_salt;
        s32 value = (detail->sp_cp_checksum != (((detail->encoded_cp + key) ^ detail->encoded_sp) ^ key)) ? 0 : (detail->encoded_sp ^ 0x7E93);
        LibObject174F20* item = status->sp_value;
        item->numeric_value = value;
        item->unk3c = 1;
        status_detail_group(owner->status, 0);
        SkillTacticalWindow* query = owner->mode_query;
        query->active = 0;
        query->func_slot18(0, 2);
        func_00349920(reinterpret_cast<u8*>(query->attachment), 0);
        refresh_query_cursor(query);
        func_0023CEA0(query->selection, 0);
        func_00353570(owner->status_rows, 0, 0);
        func_003558B0(owner->four_rows, 1, 0);
        func_003559F0(owner->four_rows);
        break;
    }
    case 0:
    {
        s32 value = func_003534C0(owner->status_rows, 1);
        SkillCharacterWindow* status = owner->status;
        LibObject174F20* item = status->assigned_cp_value;
        if (item != 0)
        {
            if (value < 0)
            {
                value = 0;
            }
            item->numeric_value = value;
            item->unk3c = 1;
        }
        FieldRecordSelection* selection = status->selection;
        if (selection != 0)
        {
            SkillCharacterEquipment* detail = &static_cast<SkillCharacterEquipment*>(selection->unk04)[selection->current];
            if (detail != 0)
            {
                u32 key = detail->checksum_salt;
                s32 value;
                if (detail->sp_cp_checksum != (((detail->encoded_cp + key) ^ detail->encoded_sp) ^ key))
                {
                    value = 0;
                }
                else
                {
                    value = detail->encoded_cp ^ 0x7E93;
                }
                LibObject174F20* item = status->available_cp_value;
                item->numeric_value = value;
                item->unk3c = 1;
            }
        }
        status_primary_group(owner->status, 0);
        status_detail_group(owner->status, 1);
        SkillTacticalWindow* query = owner->mode_query;
        query->active = 0;
        query->func_slot18(0, 2);
        func_00349920(reinterpret_cast<u8*>(query->attachment), 0);
        refresh_query_cursor(query);
        func_0023CEA0(query->selection, 0);
        func_003558B0(owner->four_rows, 0, 0);
        func_00353570(owner->status_rows, 1, 0);
        break;
    }
    case 2:
    {
        status_detail_group(owner->status, 0);
        status_primary_group(owner->status, 0);
        func_00353570(owner->status_rows, 0, 0);
        func_003558B0(owner->four_rows, 0, 0);
        SkillTacticalWindow* query = owner->mode_query;
        query->active = 1;
        func_00351BE0(query);
        refresh_query_cursor(query);
        func_0023CEA0(query->selection, 0);
        func_00352C00(owner->mode_query);
        break;
    }
    }
    if (enabled == 1)
    {
        FieldClass15AE70* window = owner->window;
        if (window != 0)
        {
            window->func_slot60(SKILL_MSG_BLANK);
        }
    }
    func_003580D0(owner->status, -1, -1, -1);
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_slot5c__15SkillControllerFv);

/** @brief Submit the Field receiver to the resident object queue. */
void SkillController::func_001DD7B0()
{
    FieldClass153E30* entry = this;
    resident_enqueue_object(D_001B65F4, entry);
}

/** @brief Create the skill or symbology windows and attach their navigation links. @return One. */
s32 SkillController::func_00263CD0()
{
    SkillResourceWindow* resource = new (0) SkillResourceWindow;
    SkillHelpWindow* message = new (0) SkillHelpWindow;
    resource->func_slotf4(resource_slot);
    FieldClass153E30::add_child(resource);
    resource->func_slot40(0);
    message->menu_kind = menu_kind;
    message->func_slotf4(resource_slot);
    FieldClass153E30::add_child(message);
    unk24 = message;
    message->func_slot40(resource);
    if (menu_kind == 1)
    {
        SkillSymbologyCharacterWindow* list = new (0) SkillSymbologyCharacterWindow;
        symbology_character = list;
        SkillSymbologyHelpWindow* primary = new (0) SkillSymbologyHelpWindow;
        symbology_help = primary;
        SkillSymbologyWindow* rows = new (0) SkillSymbologyWindow;
        symbology_spells = rows;
        options = new (0) SkillOptionsWindow;
        symbology_character->func_slotf4(resource_slot);
        FieldClass153E30::add_child(symbology_character);
        symbology_character->func_slot40(symbology_help);
        symbology_help->func_slotf4(resource_slot);
        FieldClass153E30::add_child(symbology_help);
        symbology_help->func_slot40(symbology_spells);
        symbology_spells->func_slot40(symbology_character);
        symbology_spells->func_slot48(options);
        symbology_spells->func_slotf4(resource_slot);
        FieldClass153E30::add_child(symbology_spells);
        options->func_slotf4(resource_slot);
        FieldClass153E30::add_child(options);
        options->func_slot40(symbology_spells);
        message->func_slot60(SKILL_MSG_SYMBOLOGY_ENABLE_HELP);
        unk20 = symbology_spells;
    }
    else if (menu_kind == 2)
    {
        secondary = new (0) SkillSecondarySelection;
        status = new (0) SkillCharacterWindow(this);
        status_message = new (0) SkillStatusMessageWindow;
        SkillFourRowSelection* four = new (0) SkillFourRowSelection;
        four_rows = four;
        status_rows = new (0) SkillBattleSetupWindow(this);
        mode_query = new (0) SkillTacticalWindow;
        mode_message = new (0) SkillModeMessageWindow;
        mode_window = new (0) SkillModeSelection(this);
        paired = new (0) SkillDualSelection;
        text_window = new (0) SkillTextReceiver;
        window = new (0) SkillCostWindow(this);
        mode_query->parent = this;
        paired->owner = this;
        secondary->func_slotf4(resource_slot);
        FieldClass153E30::add_child(secondary);
        secondary->func_slot40(message);
        secondary->status = status;
        secondary->four_rows = four_rows;
        secondary->status_rows = status_rows;
        secondary->mode_query = mode_query;
        status->func_slotf4(resource_slot);
        FieldClass153E30::add_child(status);
        status->func_slot40(secondary);
        status->four_rows = four_rows;
        status->status_rows = status_rows;
        status->mode_query = mode_query;
        status->mode_window = mode_window;
        status->paired = paired;
        four_rows->func_slotf4(resource_slot);
        FieldClass153E30::add_child(four_rows);
        four_rows->func_slot40(secondary);
        four_rows->message = window;
        four_rows->status = status;
        status_rows->record_selection = record_selection;
        status_rows->func_slotf4(resource_slot);
        FieldClass153E30::add_child(status_rows);
        status_rows->func_slot40(secondary);
        status_rows->func_slot48(mode_window);
        reinterpret_cast<SkillCostWindow*>(window)->func_slotf4(resource_slot);
        FieldClass153E30::add_child(window);
        window->func_slot40(status_message);
        text_window->func_slotf4(resource_slot);
        FieldClass153E30::add_child(text_window);
        text_window->func_slot40(mode_query);
        LibObject178660* attachment = text_window->unk10;
        if (attachment != 0)
        {
            attachment->LibClass174610::unkab = 0;
        }
        mode_query->func_slot40(secondary);
        mode_query->func_slot48(paired);
        mode_query->attachment = text_window;
        mode_query->func_slotf4(resource_slot);
        FieldClass153E30::add_child(mode_query);
        status_message->func_slotf4(resource_slot);
        FieldClass153E30::add_child(status_message);
        status_message->func_slot40(status);
        mode_message->func_slotf4(resource_slot);
        FieldClass153E30::add_child(mode_message);
        mode_message->func_slot40(mode_window);
        mode_window->record_selection = record_selection;
        mode_window->func_slotf4(resource_slot);
        FieldClass153E30::add_child(mode_window);
        mode_window->func_slot40(status_rows);
        mode_window->func_slot48(status);
        paired->func_slotf4(resource_slot);
        FieldClass153E30::add_child(paired);
        paired->func_slot40(mode_query);
        func_00353570(status_rows, 1, 0);
        func_00354190(status_rows);
        SkillTacticalWindow* query_window = mode_query;
        query_window->active = 0;
        query_window->func_slot18(0, 2);
        func_00349920(reinterpret_cast<u8*>(query_window->attachment), 0);
        refresh_query_cursor(query_window);
        func_0023CEA0(query_window->selection, 0);
        func_003558B0(four_rows, 0, 0);
        func_00351360(mode_window, 0, 0);
        func_00349F30(paired, 2);
        unk20 = secondary;
    }
    state = 6;
    windows_initialized = 1;
    return 1;
}

/** @brief Load a completed menu resource and create its windows. @param buffer Completed resource buffer. @return Setup result, or zero without a buffer. */
s32 SkillController::func_001E1820(void* buffer)
{
    if (buffer == 0)
    {
        return 0;
    }
    SkillAlignedResource* aligned = aligned_skill_resource(buffer);
    s32 size = aligned->size + 128;
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
    return func_00263CD0();
}

/** @brief Allocate and initialize the character record selection. @return One on success, or zero on failure. */
u8 SkillController::func_00264110()
{
    FieldRecordSelection* selection = new (0) FieldRecordSelection;
    this->record_selection = selection;
    if (this->record_selection == 0)
    {
        return 0;
    }
    return (u8)func_0028E3D0(this->record_selection) != 0;
}

/** @brief Delete the owned record selection and destroy the Field receiver base. */
SkillController::~SkillController()
{
    if (record_selection != 0)
    {
        skill_delete_owned(record_selection);
    }
}

/** @brief Initialize the controller and clear its window links. */
SkillController::SkillController()
{
    menu_kind = D_001B643C->callbacks->menu_kind;
    resource_slot = 0;
    windows_initialized = 0;
    record_selection = 0;
    selected = 0;
    window = 0;
    status = 0;
    status_message = 0;
    four_rows = 0;
    status_rows = 0;
    mode_query = 0;
    mode_message = 0;
    mode_window = 0;
    paired = 0;
    text_window = 0;
    symbology_character = 0;
    symbology_help = 0;
    symbology_spells = 0;
    options = 0;
    unk84 = 0;
    entry = 0;
    detail = 0;
    code = 0;
    unk88 = 0;
    message = 0;
}

/** @brief Leave the default DMA notification hook unchanged. @param value Unused notification value. */
void LibClass171FF0::func_003EFA90(u32 value)
{
}

void LibClass171FF0::func_003F4410(u32 value)
{
}

s32 SkillCoordinateSelector::func_003EEBC0()
{
    return 3;
}

void SkillCoordinateSelector::func_003EEBD0()
{
}

void SkillCoordinateSelector::func_003EEBE0()
{
}

/** @brief Copy the translation vector and mark the transform dirty. @param value Translation vector. */
void LibClass178A90::func_003EF770(const LibVector4* value)
{
    unk50 = 1;
    unk20.packed = value->packed;
}

/** @brief Copy the translation vector and mark the transform dirty. @param value Translation vector. */
void LibClass178A90::func_003EF780(const LibVector4* value)
{
    unk50 = 1;
    unk20.packed = value->packed;
}

/** @brief Set the translation coordinates and mark the transform dirty. @param x Horizontal translation. @param y Vertical translation. @param z Third translation component. */
void LibClass178A90::func_003EF790(float x, float y, float z)
{
    unk50 = 1;
    unk20.components[0] = x;
    unk20.components[1] = y;
    unk20.components[2] = z;
    unk20.components[3] = 1.0f;
}

/** @brief Set all quaternion components and mark the transform dirty. @param x First component. @param y Second component. @param z Third component. @param w Fourth component. */
void LibClass171EF0::func_003EEED0(float x, float y, float z, float w)
{
    unk50 = 1;
    unk30.components[0] = x;
    unk30.components[1] = y;
    unk30.components[2] = z;
    unk30.components[3] = w;
}

/** @brief Copy the quaternion and mark the transform dirty. @param value Quaternion components. */
void LibClass171EF0::func_003EEEF0(const LibVector4* value)
{
    unk50 = 1;
    unk30.packed = value->packed;
}

/** @brief Copy the quaternion and mark the transform dirty. @param value Quaternion components. */
void LibClass171EF0::func_003EEF10(const LibVector4* value)
{
    unk50 = 1;
    unk30.packed = value->packed;
}

/** @brief Update the rotation state and mark the transform dirty. @param value Rotation components. */
void LibClass171EF0::func_003EEF30(const LibVector4* value)
{
    unk50 = 1;
    func_4CE4C0(&unk30, value);
}

/** @brief Update the rotation state and mark the transform dirty. @param value Rotation components. */
void LibClass171EF0::func_003EEF60(const LibVector4* value)
{
    unk50 = 1;
    func_4CE4C0(&unk30, value);
}

/** @brief Set the rotation components and mark the transform dirty. @param x First component. @param y Second component. @param z Third component. */
void LibClass171EF0::func_003EEF90(float x, float y, float z)
{
    unk50 = 1;
    LibVector4 value;
    value.components[0] = x;
    value.components[1] = y;
    value.components[2] = z;
    value.components[3] = 1.0f;
    func_4CE4C0(&unk30, &value);
}

/** @brief Copy the scale vector and mark the transform dirty. @param value Scale vector. */
void LibClass171EF0::func_003EEFD0(const LibVector4* value)
{
    unk50 = 1;
    unk40.packed = value->packed;
}

/** @brief Copy the scale vector and mark the transform dirty. @param value Scale vector. */
void LibClass171EF0::func_003EEFF0(const LibVector4* value)
{
    unk50 = 1;
    unk40.packed = value->packed;
}

/** @brief Set the scale coordinates and mark the transform dirty. @param x First scale component. @param y Second scale component. @param z Third scale component. */
void LibClass171EF0::func_003EF010(float x, float y, float z)
{
    unk50 = 1;
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

/** @brief Report the controller object kind. @return Four. */
s32 SkillController::func_001DF3D0()
{
    return 4;
}

/** @brief Report whether window setup finished. @return Setup flag. */
u8 SkillController::func_00261D20()
{
    return windows_initialized;
}

/** @brief Return the loaded resource slot. @return Resource slot. */
u32 SkillController::func_00263CC0()
{
    return resource_slot;
}

void func_0035C440(SkillList* list, void* value)
{
    SkillListNode* node = new (0) SkillListNode;
    if (node != 0)
    {
        node->value = value;
        node->next = 0;
        SkillListNode* tail = list->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        list->count++;
    }
}

void func_0035C4D0(SkillList* list, void* value)
{
    SkillListNode* node = new (0) SkillListNode;
    if (node != 0)
    {
        SkillListNode* current;
        SkillListNode* next;
        node->value = value;
        node->next = 0;
        current = list->head;
        next = current->next;
        while (next != 0)
        {
            current = next;
            next = next->next;
        }
        current->next = node;
        list->count++;
    }
}

void func_0035C560(SkillList* list, void* value)
{
    SkillListNode* node = new (0) SkillListNode;
    if (node != 0)
    {
        SkillListNode* current;
        SkillListNode* next;
        node->value = value;
        node->next = 0;
        current = list->head;
        next = current->next;
        while (next != 0)
        {
            current = next;
            next = next->next;
        }
        current->next = node;
        list->count++;
    }
}

void func_0035C5F0(SkillList* list, void* value)
{
    SkillListNode* node = new (0) SkillListNode;
    if (node != 0)
    {
        SkillListNode* current;
        SkillListNode* next;
        node->value = value;
        node->next = 0;
        current = list->head;
        next = current->next;
        while (next != 0)
        {
            current = next;
            next = next->next;
        }
        current->next = node;
        list->count++;
    }
}

SkillList183C48::SkillList183C48()
{
    head = new (0) SkillListNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

SkillList183C48::~SkillList183C48()
{
    func_0035C810(this);
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

void func_0035C780(SkillList* list, void* value)
{
    SkillListNode* node = new (0) SkillListNode;
    if (node != 0)
    {
        SkillListNode* current;
        SkillListNode* next;
        node->value = value;
        node->next = 0;
        current = list->head;
        next = current->next;
        while (next != 0)
        {
            current = next;
            next = next->next;
        }
        current->next = node;
        list->count++;
    }
}

void func_0035C810(SkillList183C48* record)
{
    SkillListNode* node = record->head->next;
    if (node == 0)
    {
        return;
    }
    while (node != 0)
    {
        SkillListNode* next = node->next;
        delete node;
        node = next;
    }
    record->head->next = 0;
    record->count = 0;
}

SkillListNode* func_0035C890(SkillList* list, s32 index)
{
    SkillListNode* node = list->head->next;
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

SkillList183C38::SkillList183C38()
{
    head = new (0) SkillListNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

SkillList183C38::~SkillList183C38()
{
    func_0035CA60(this);
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

void func_0035C9D0(SkillList* list, void* value)
{
    SkillListNode* node = new (0) SkillListNode;
    if (node != 0)
    {
        SkillListNode* current;
        SkillListNode* next;
        node->value = value;
        node->next = 0;
        current = list->head;
        next = current->next;
        while (next != 0)
        {
            current = next;
            next = next->next;
        }
        current->next = node;
        list->count++;
    }
}

void func_0035CA60(SkillList183C38* record)
{
    SkillListNode* node = record->head->next;
    if (node == 0)
    {
        return;
    }
    while (node != 0)
    {
        SkillListNode* next = node->next;
        delete node;
        node = next;
    }
    record->head->next = 0;
    record->count = 0;
}

SkillListNode* func_0035CAE0(SkillList* list, s32 index)
{
    SkillListNode* node = list->head->next;
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

void func_0035CB20(SkillList* list, void* value)
{
    SkillListNode* node = new (0) SkillListNode;
    if (node != 0)
    {
        SkillListNode* current;
        SkillListNode* next;
        node->value = value;
        node->next = 0;
        current = list->head;
        next = current->next;
        while (next != 0)
        {
            current = next;
            next = next->next;
        }
        current->next = node;
        list->count++;
    }
}

void func_0035CBB0(SkillList* list, void* value)
{
    SkillListNode* node = new (0) SkillListNode;
    if (node != 0)
    {
        SkillListNode* current;
        SkillListNode* next;
        node->value = value;
        node->next = 0;
        current = list->head;
        next = current->next;
        while (next != 0)
        {
            current = next;
            next = next->next;
        }
        current->next = node;
        list->count++;
    }
}











/** @brief Color the choice text entries for the selected index. @param selected Selected grid index. */
void SkillGridChoice::func_slotf4(s16 selected)
{
    s32 index = 0;
    SkillListNode* node = reinterpret_cast<SkillListNode*>(unk2c.unk00->unk04);
    while (node != 0)
    {
        LibObject178750* item = static_cast<LibObject178750*>(node->value);
        if (index == selected)
        {
            item->unk94 = 0x288080;
            item->unk3c = 1;
        }
        else
        {
            item->unk94 = 0x808080;
            item->unk3c = 1;
        }
        node = node->next;
        index++;
    }
}

void func_0035CD50(SkillGridChoice* object)
{
    if (D_001B643C->callbacks->controller->func_00261150() == object)
    {
        object->func_slotf4(object->selection->unk114);
    }
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_0035CDB0);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_0035CDF0);

s32 func_0035CE30(FieldClass15AE70* object)
{
    func_002CE530(object, 0, 0x7F);
    FieldClass153E30* controller = D_001B643C->callbacks->controller;
    controller->func_00263C70(object->func_slot44());
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->callbacks), object);
    return 2;
}

s32 func_0035CEB0(SkillGridChoice* object)
{
    u8 result = 0;
    object->selected = object->selection->unk114;
    if (object->selected == 0)
    {
        object->set_state(0xFF, 0x80);
    }
    else
    {
        result = object->func_slotb4();
    }
    return result == 0 ? 1 : 2;
}

s32 SkillGridChoice::func_slot10(u32 associated, float x, float y, s32 code)
{
    FieldClass15AE70::func_slot10(associated, x, y, code);
    LibClass178630* panel = new (0) LibClass178630;
    if (panel == 0)
    {
        return 0;
    }
    lib_panel_init_rectangle(panel, 1, 0.0f, 0.0f, 256.0f, 160.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    func_0035CBB0(reinterpret_cast<SkillList*>(&unk14), panel);
    LibObject178750* first = new (0) LibObject178750;
    LibObject178750* second = new (0) LibObject178750;
    LibObject178750* title = new (0) LibObject178750;
    if (first == 0 || second == 0 || title == 0)
    {
        return 0;
    }
    lib_text_init_resource_rectangle(first, static_cast<s32>(associated), 0x7E8, 0, 92.0f, 84.0f, 0.0f, 0.0f);
    lib_text_init_resource_rectangle(second, static_cast<s32>(associated), 0x7E9, 0, 92.0f, 120.0f, 0.0f, 0.0f);
    lib_text_init_resource_rectangle(title, static_cast<s32>(associated), SKILL_MSG_CONFIRM_END_SETUP, 0, 16.0f, 16.0f, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, first);
    lib_container_attach_widget(unk10, second);
    lib_container_attach_widget(unk10, title);
    func_0035C9D0(reinterpret_cast<SkillList*>(&unk2c), first);
    func_0035C9D0(reinterpret_cast<SkillList*>(&unk2c), second);
    func_0035C9D0(reinterpret_cast<SkillList*>(&unk2c), title);
    selection = new (0) FieldObject23CEA0;
    if (selection == 0)
    {
        return 0;
    }
    selection->func_0023CE80(1, 2);
    selection->func_0023CE60(0.0f, 36.0f);
    selection->unkF2 = 0;
    selection->func_0023CF50(1, x + 92.0f, 16.0f + (y + 84.0f));
    func_0035C4D0(reinterpret_cast<SkillList*>(&unk74), selection);
    return 1;
}

SkillGridChoice::~SkillGridChoice()
{
}

inline SkillGridChoice::SkillGridChoice()
{
    selection = 0;
    selected = -1;
}

void SkillHpMpGauge::func_0044B100(u32 first, u32 second, u32 third)
{
    if (queued_for_release != 0)
    {
        return;
    }
    unk62[1] = 0;
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
        SkillHpMpGaugeDrawer::unk00 = 0xFFFFFE - (SkillHpMpGaugeDrawer::unk04->unka0 << 4);
        func_002BC4F0(0, SkillHpMpGaugeDrawer::unk00, 128.0f);
    }
    unk62[1] = 1;
}

s32 SkillHpMpGauge::initialize(s32 code, s32 first, void* source, float x, float y, float z)
{
    unk6c = 0x6006;
    LibClass171EC0::unk20.components[0] = 0.0f;
    LibClass171EC0::unk20.components[1] = 0.0f;
    LibClass171EC0::unk20.components[2] = 0.0f;
    LibClass171EC0::unk20.components[3] = 1.0f;
    func_44B110(this, code, first, source, z, 0);
    unkb4 = 0;
    unkb8 = 0;
    return 1;
}

void SkillHpMpGauge::func_003F4410(u32 value)
{
    func_4D00B0(this);
}

void SkillHpMpGauge::func_003EEBE0()
{
    dma_pending = 1;
    if (unk08 != 0)
    {
        func_0011F770(unk08, this);
    }
}

inline SkillHpMpGaugeDrawer::~SkillHpMpGaugeDrawer()
{
}

SkillHpMpGauge::~SkillHpMpGauge()
{
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", skill_build_hp_mp_gauge_packet);

void SkillHpMpGaugeDrawer::func_002BC4F0(u32 first, u32 depth, float value)
{
    ResidentPacket* packet = unk08;
    if (packet != 0)
    {
        packet->unk08 = packet->unk00 + 64;
        packet->unk0c = packet->unk08;
        packet->unk15 = 0;
        func_0011F140(packet, D_4ED330[0]);
        skill_build_hp_mp_gauge_packet(this);
    }
}

void SkillOptionsWindow::func_slot5c()
{
    for (s32 row = 0; row < 8; ++row)
    {
        s16 index = row;
        if (records->slots[index] > 0)
        {
            SkillCharacterStats* entry = &reinterpret_cast<SkillCharacterStats*>(records->records)[index];
            u32 hp = character_hp(entry);
            LibObject174F20* hp_display = hp_values[row];
            hp_display->numeric_value = hp;
            hp_display->unk3c = 1;
            u32 mp = character_mp(entry);
            LibObject174F20* mp_display = mp_values[row];
            mp_display->numeric_value = mp;
            mp_display->unk3c = 1;
            if (row < 3)
            {
                u32 max_hp = character_max_hp(entry);
                LibObject174F20* max_hp_display = max_hp_values[row];
                max_hp_display->numeric_value = max_hp;
                max_hp_display->unk3c = 1;
                u32 max_mp = character_max_mp(entry);
                LibObject174F20* max_mp_display = max_mp_values[row];
                max_mp_display->numeric_value = max_mp;
                max_mp_display->unk3c = 1;
            }
            badges[row][0]->unk3f = character_flags(entry) & 2;
            badges[row][1]->unk3f = character_flags(entry) & 8;
            badges[row][2]->unk3f = character_flags(entry) & 4;
            if (character_flags(entry) & 5)
            {
                indicators[row]->unk3f = 0;
                badges[row][3]->unk3f = 1;
                if (row < 3)
                {
                    LibObject175140* label = labels[row];
                    label->unk94 = 0x505080;
                    label->unk3c = 1;
                }
            }
            else
            {
                indicators[row]->unk3f = 1;
                badges[row][3]->unk3f = 0;
                if (row < 3)
                {
                    LibObject175140* label = labels[row];
                    label->unk94 = 0x808080;
                    label->unk3c = 1;
                }
            }
        }
    }
}

void SkillOptionsWindow::func_slot70()
{
    SkillCoordinateSelector* child = this->child;
    bool inactive = !child->LibMovementState::unk35;
    if (!inactive)
    {
        s32 index = child->selected - 1;
        if (index < 0)
        {
            index = 7;
        }
        func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(child), index, 0);
    }
}

void SkillOptionsWindow::func_slot74()
{
    SkillCoordinateSelector* child = this->child;
    bool inactive = !child->LibMovementState::unk35;
    if (!inactive)
    {
        s32 index = child->selected + 1;
        if (index >= 8)
        {
            index = 0;
        }
        func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(child), index, 0);
    }
}

void SkillOptionsWindow::func_slot6c()
{
    SkillCoordinateSelector* child = this->child;
    bool inactive = !child->LibMovementState::unk35;
    if (!inactive)
    {
        s32 index = child->selected;
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
        func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(child), index, 0);
    }
}

void SkillOptionsWindow::func_slot68()
{
    SkillCoordinateSelector* child = this->child;
    bool inactive = !child->LibMovementState::unk35;
    if (!inactive)
    {
        s32 index = child->selected;
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
        func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(child), index, 0);
    }
}

/**
 * @brief Cancel the options window and restore its associated window.
 * @return Two after restoring the prior window.
 */
s32 SkillOptionsWindow::func_slotb4()
{
    this->child->unk3f = 0;
    this->unk10->LibClass174610::unkab = 0;
    SkillListNode* node = this->nested.head->next;
    while (node != 0)
    {
        static_cast<LibClass174610*>(node->value)->unkab = 0;
        node = node->next;
    }
    node = this->nested.head->next;
    while (node != 0)
    {
        static_cast<LibClass174610*>(node->value)->func_0044B100(1, 1, 1);
        node = node->next;
    }
    FieldClass15AE70* window = static_cast<FieldClass15AE70*>(this->func_slot44());
    window->func_slot64();
    D_001B643C->callbacks->controller->func_00263C70(window);
    SkillSymbologyCharacterWindow* symbology_character = static_cast<SkillController*>(D_001B643C->callbacks->controller)->symbology_character;
    if (symbology_character->first != 0)
    {
        symbology_character->first->unk3f = 1;
    }
    if (symbology_character->second != 0)
    {
        symbology_character->second->unk3f = 1;
    }
    static_cast<FieldClass15AE70*>(D_001B643C->callbacks->controller->func_00263C90())->func_slot60(SKILL_MSG_SYMBOLOGY_ENABLE_HELP);
    return 2;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_0035E5C0);

u32 skill_mask_character_flags(SkillCharacterStats* record, u32 flags)
{
    u32 key = record->checksum_salt;
    u32 value = record->encoded_flags;
    s32 salt = record->encoded_experience;
    u32 checksum = record->flags_experience_checksum;
    if (checksum != ((value + key) ^ salt ^ key))
    {
        return 5;
    }
    record->encoded_flags = ((value ^ SKILL_FLAG_ENCODING_MASK) & flags) ^ SKILL_FLAG_ENCODING_MASK;
    s32 current_salt = record->encoded_experience;
    record->flags_experience_checksum = ((record->encoded_flags + record->checksum_salt) ^ current_salt) ^ record->checksum_salt;
    return record->encoded_flags ^ SKILL_FLAG_ENCODING_MASK;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_0035FAA0);

/** @brief Destroy the movement storage and intrusive widget base. */
inline ItemCreationClass175030::~ItemCreationClass175030()
{
}

void SkillOptionsWindow::func_slot0c()
{
    SkillListNode* node = this->nested.head->next;
    while (node != 0)
    {
        LibClass171EA0* display = (LibClass171EA0*)node->value;
        display->func_003EF740();
        node = node->next;
    }
    this->FieldClass15AE70::func_slot0c();
}

void SkillHpMpGauge::func_003EF740()
{
    queued_for_release = 1;
    func_44B210(this);
    resident_enqueue_object(D_001B65F4, this);
}

SkillOptionsWindow::SkillOptionsWindow()
{
    records = 0;
    child = 0;
    x = 0.0f;
    y = 0.0f;
    unkb8 = 0;
    selected_kind = 0;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_slot5c__20SkillSymbologyWindowFv);

/**
 * @brief Advance the paired display lists toward scroll position 16.
 * @return Zero.
 */
s32 SkillSymbologyWindow::func_slotc4()
{
    u8 inactive = !this->selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    if (this->shift == 0)
    {
        s32 old_position = this->position;
        if (old_position < 16)
        {
            s32 offset;
            s32 i;
            this->position += 14;
            if (this->position > 16)
            {
                this->position = 16;
            }
            offset = ((this->position - old_position) / 2) * 33;
            for (i = 0; i < 30; i++)
            {
                ListItem0035CCE0* item = this->second[i];
                float y = (float)(s32)(item->position.y - (float)offset);
                item->position.y = y;
                item->unk3c = 1;
                item = this->first[i];
                item->position.y = y;
                item->unk3c = 1;
            }
        }
    }
    resident_allocate_request(D_001B65F8, 0, 0, 0, 127, 64, 0);
    return 0;
}

/**
 * @brief Move the paired display lists toward scroll position zero.
 * @return Zero.
 */
s32 SkillSymbologyWindow::func_slotc0()
{
    u8 inactive = !this->selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    if (this->shift == 0)
    {
        s32 old_position = this->position;
        if (old_position > 0)
        {
            s32 offset;
            s32 i;
            this->position -= 14;
            if (this->position < 0)
            {
                this->position = 0;
            }
            offset = ((this->position - old_position) / 2) * 33;
            for (i = 0; i < 30; i++)
            {
                ListItem0035CCE0* item = this->second[i];
                float y = (float)(s32)(item->position.y - (float)offset);
                item->position.y = y;
                item->unk3c = 1;
                item = this->first[i];
                item->position.y = y;
                item->unk3c = 1;
            }
        }
    }
    resident_allocate_request(D_001B65F8, 0, 0, 0, 127, 64, 0);
    return 0;
}

void SkillSymbologyWindow::func_slot74()
{
    u8 inactive = !this->selection->unk35;
    if (inactive == 1)
    {
        return;
    }
    if (this->selected == 13)
    {
        if (this->position == 16)
        {
            return;
        }
        if (this->shift != 0)
        {
            return;
        }
        this->shift = -33;
        this->position += 2;
        this->selected = 12;
        move_active_grid(this->selection, 3);
    }
    else
    {
        this->selected++;
        move_active_grid(this->selection, 2);
    }
}

void SkillSymbologyWindow::func_slot70()
{
    u8 inactive = !this->selection->unk35;
    if (inactive == 1)
    {
        return;
    }
    if (this->selected == 0)
    {
        if (this->position == 0)
        {
            return;
        }
        if (this->shift != 0)
        {
            return;
        }
        this->shift = 33;
        this->position -= 2;
        this->selected = 1;
        move_active_grid(this->selection, 2);
    }
    else
    {
        this->selected--;
        move_active_grid(this->selection, 3);
    }
}

void SkillSymbologyWindow::func_slot6c()
{
    FieldObject23CEA0* selection = this->selection;
    u8 inactive = !selection->unk35;
    if (inactive == 1)
    {
        return;
    }
    if (this->selected == 12 || this->selected == 13)
    {
        if (this->shift != 0)
        {
            return;
        }
        if (this->position == 16)
        {
            return;
        }
        this->shift = -33;
        this->position += 2;
        resident_allocate_request(D_001B65F8, 0, 0, 0, 127, 64, 0);
    }
    else
    {
        move_active_grid(selection, 1);
        this->selected += 2;
    }
}

void SkillSymbologyWindow::func_slot68()
{
    FieldObject23CEA0* selection = this->selection;
    u8 inactive = !selection->unk35;
    if (inactive == 1)
    {
        return;
    }
    if (this->selected == 0 || this->selected == 1)
    {
        if (this->shift != 0)
        {
            return;
        }
        if (this->position == 0)
        {
            return;
        }
        this->shift = 33;
        this->position -= 2;
        resident_allocate_request(D_001B65F8, 0, 0, 0, 127, 64, 0);
    }
    else
    {
        move_active_grid(selection, 0);
        this->selected -= 2;
    }
}

s32 SkillSymbologyWindow::func_slotdc()
{
    u8 inactive = !this->selection->unk35;
    SkillSymbologyCharacterWindow* character_window;
    if (inactive == 1)
    {
        return 0;
    }
    character_window = this->character_window;
    if (character_window == 0)
    {
        return 0;
    }
    if (this->records->count < 2)
    {
        return 0;
    }
    return skill_cycle_symbology_character(character_window, 1);
}

s32 SkillSymbologyWindow::func_slotd8()
{
    u8 inactive = !this->selection->unk35;
    SkillSymbologyCharacterWindow* character_window;
    if (inactive == 1)
    {
        return 0;
    }
    character_window = this->character_window;
    if (character_window == 0)
    {
        return 0;
    }
    if (this->records->count < 2)
    {
        return 0;
    }
    return skill_cycle_symbology_character(character_window, 0);
}

/**
 * @brief Set the row grid state to one.
 */
void SkillSymbologyWindow::func_slot64()
{
    func_0023CEA0(this->selection, 1);
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_slotbc__20SkillSymbologyWindowFv);

s32 SkillSymbologyWindow::func_slotb4()
{
    FieldSlotRecordOwner1C* loader = D_001B643C->loader;
    if (loader == 0)
    {
        return 0;
    }
    u8 ready = loader->unk2d != 0;
    if (ready == 1)
    {
        this->set_state(1, 0x80);
    }
    else
    {
        SkillGridChoice* choice = new (0) SkillGridChoice;
        if (choice == 0)
        {
            return 0;
        }
        choice->func_slot10(this->func_slot54(), 192.0f, 160.0f, 5);
        choice->func_slot40(this);
        D_001B643C->callbacks->controller->add_child(choice);
        D_001B643C->callbacks->controller->func_00263C70(choice);
    }
    return 2;
}

s32 SkillSymbologyWindow::func_slotb0()
{
    u8 inactive = !this->selection->FieldClass151C50::unk35;
    if (inactive == 1)
    {
        return 0;
    }
    s32 kind, value, result_index, unused;
    FieldRecordSelection* records = this->records;
    s32 current = records->current;
    s32 selected = this->position + this->selected;
    SkillCharacterStats* entry = &reinterpret_cast<SkillCharacterStats*>(records->records)[current];
    SkillCharacterEquipment* detail = &static_cast<SkillCharacterEquipment*>(records->unk04)[current];
    if (func_408EA0(detail, records->slots[records->current], selected, &kind, &value, &result_index, &unused, 1) == 0 || selected == 29)
    {
        return 3;
    }
    if (kind != 3 && kind != 18 && kind != 19 && kind != 20 && kind != 27)
    {
        return 3;
    }
    if (character_flags(entry) & 7)
    {
        return 3;
    }
    s32 required = 0;
    func_4095C0(kind, reinterpret_cast<FieldRecord*>(entry), detail, &required, 0, 0, 0, 0, 0, 0, 0);
    s32 available = (s32)character_mp(entry);
    if (available <= required)
    {
        return 3;
    }
    func_0023CEA0(this->selection, 0);
    SkillSymbologyCharacterWindow* symbology_character = static_cast<SkillController*>(D_001B643C->callbacks->controller)->symbology_character;
    if (symbology_character->first != 0)
    {
        symbology_character->first->unk3f = 0;
    }
    if (symbology_character->second != 0)
    {
        symbology_character->second->unk3f = 0;
    }
    SkillOptionsWindow* options = static_cast<SkillOptionsWindow*>(this->func_slot4c());
    options->child->unk3f = 1;
    options->unk10->LibClass174610::unkab = 1;
    SkillListNode* node = options->nested.head->next;
    while (node != 0)
    {
        static_cast<LibClass174610*>(node->value)->unkab = 1;
        node = node->next;
    }
    node = options->nested.head->next;
    while (node != 0)
    {
        static_cast<LibClass174610*>(node->value)->func_0044B100(1, 1, 1);
        node = node->next;
    }
    s32 option_index = result_index;
    options->selected_kind = kind;
    options->selected_index = option_index;
    D_001B643C->callbacks->controller->func_00263C70(options);
    static_cast<FieldClass15AE70*>(D_001B643C->callbacks->controller->func_00263C90())->func_slot60(SKILL_MSG_SYMBOLOGY_TARGET_HELP);
    return 1;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_slotf4__20SkillSymbologyWindowFUi);

SkillSymbologyWindow::SkillSymbologyWindow()
{
    records = 0;
    selection = 0;
    character_window = 0;
    cursor = 0;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_00362FC0);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_slotf4__24SkillSymbologyHelpWindowFUi);

SkillSymbologyHelpWindow::~SkillSymbologyHelpWindow()
{
}

SkillSymbologyHelpWindow::SkillSymbologyHelpWindow()
{
    selection = 0;
    description = 0;
    mastery_label = 0;
    mastery_value = 0;
    mp_cost_label = 0;
    mp_cost_value = 0;
}

void SkillSymbologyCharacterWindow::func_slot5c()
{
    SkillCharacterStats* record = &((SkillCharacterStats*)this->selection->records)[this->selection->current];
    u32 value = character_mp(record);
    LibObject174F20* display = this->mp_value;
    display->numeric_value = value;
    display->unk3c = 1;
    this->mp_value->unk3f = 1;
}

s32 skill_cycle_symbology_character(SkillSymbologyCharacterWindow* object, s32 forward)
{
    if (object->selection == 0)
    {
        return 0;
    }
    object->selection->active = 0;
    func_0028E2B0(object->selection, forward);
    LibObject175140* text = object->character_name;
    text->unkfc = static_cast<SkillCharacterEquipment*>(object->selection->unk04)[object->selection->current].character_name;
    text->unk3c = 1;
    SkillCharacterStats* record = &reinterpret_cast<SkillCharacterStats*>(object->selection->records)[object->selection->current];
    u32 value = character_mp(record);
    LibObject174F20* display = object->mp_value;
    display->numeric_value = value;
    display->unk3c = 1;
    func_00363890(object);
    return 4;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_00363890);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/cskill", func_slotf4__29SkillSymbologyCharacterWindowFUi);

SkillSymbologyCharacterWindow::~SkillSymbologyCharacterWindow()
{
}

SkillSymbologyCharacterWindow::SkillSymbologyCharacterWindow()
{
    selection = 0;
    character_name = 0;
    mp_label = 0;
    mp_value = 0;
    second = 0;
    first = 0;
    for (s32 i = 0; i < 8; i++)
    {
        character_markers[i].available = 0;
        character_markers[i].unavailable = 0;
        character_slots[i] = 0;
    }
    show_party = 0;
}

SkillCoordinateSelector::~SkillCoordinateSelector()
{
}

void ItemCreationClass185050::func_slot0c()
{
}

s32 SkillHpMpGauge::func_003EEBC0()
{
    return 14;
}

void SkillHpMpGauge::func_003F4420()
{
    unk60 = unka8;
}

SkillOptionsWindow::~SkillOptionsWindow()
{
}

SkillSymbologyWindow::~SkillSymbologyWindow()
{
}

SkillList184268::SkillList184268()
{
    head = new (0) SkillListNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

SkillList184268::~SkillList184268()
{
    func_00364A70(this);
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

void func_003649E0(SkillList* list, void* value)
{
    SkillListNode* node = new (0) SkillListNode;
    if (node != 0)
    {
        SkillListNode* current;
        SkillListNode* next;
        node->value = value;
        node->next = 0;
        current = list->head;
        next = current->next;
        while (next != 0)
        {
            current = next;
            next = next->next;
        }
        current->next = node;
        list->count++;
    }
}

void func_00364A70(SkillList184268* record)
{
    SkillListNode* node = record->head->next;
    if (node == 0)
    {
        return;
    }
    while (node != 0)
    {
        SkillListNode* next = node->next;
        delete node;
        node = next;
    }
    record->head->next = 0;
    record->count = 0;
}

SkillPairList184258::~SkillPairList184258()
{
    func_00364B70(this);
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

void func_00364B70(SkillPairList184258* record)
{
    SkillPairListNode* node = record->head->next;
    if (node == 0)
    {
        return;
    }
    while (node != 0)
    {
        SkillPairListNode* next = node->next;
        delete node;
        node = next;
    }
    record->head->next = 0;
    record->count = 0;
}

void func_00364BF0(SkillPairList184258* list, SkillPairValue value)
{
    SkillPairListNode* node = new (0) SkillPairListNode;
    if (node != 0)
    {
        node->first = value.first;
        node->second = value.second;
        node->next = 0;
        SkillPairListNode* tail = list->head;
        SkillPairListNode* next = tail->next;
        while (next != 0)
        {
            tail = next;
            next = tail->next;
        }
        tail->next = node;
        list->count++;
    }
}

SkillPairList184258::SkillPairList184258()
{
    head = new (0) SkillPairListNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}
