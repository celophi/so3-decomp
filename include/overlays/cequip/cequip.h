#ifndef SO3_OVERLAYS_CEQUIP_CEQUIP_H
#define SO3_OVERLAYS_CEQUIP_CEQUIP_H

#include "types.h"
#include "overlays/1067-00/text_0028E240.h"
#include "overlays/1067-00/text_002D5260.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_0023B1D0.h"
#include "overlays/1067-00/text_001E1590.h"

#define EQUIP_STAT_WORD_XOR_KEY 0x7DE3F7E3
#define EQUIP_STAT_HALFWORD_XOR_KEY 0x7E93

typedef struct ItemCreationCategoryRecord ItemCreationCategoryRecord;

#ifdef __cplusplus
struct ItemCreationAllocationRecord;
class EquipController;
class EquipItemListWindow;
class EquipItemTypeNode;
class EquipNewItemTypeNode;
class EquipParameterWindow;
class EquipSlotWindow;

/** Item type IDs that include a newly obtained item, behind a sentinel node. */
class EquipNewItemTypeList
{
public:
    EquipNewItemTypeNode* head;

    u32 count;

    /** @brief Allocate the sentinel and initialize the empty list. */
    EquipNewItemTypeList();

    /** @brief Release the value nodes and sentinel storage. */
    virtual ~EquipNewItemTypeList();
};

/** Item type records listed for the selected slot, behind a sentinel node; a null record is the "(None)" row. */
class EquipItemTypeList
{
public:
    EquipItemTypeNode* head;

    u32 count;

    /** @brief Allocate the sentinel and initialize the empty list. */
    EquipItemTypeList();

    /** @brief Release the value nodes and sentinel storage. */
    virtual ~EquipItemTypeList();
};

/** Contextual copies of the recovered list-node base and sentinel. */
typedef LibClass171E80 EquipClass182318;

typedef LibClass171E90 EquipClass182328;

/** Contextual copy of the movement widget's storage base. */
typedef ItemCreationClass185050 EquipClass182340;

/** Contextual tooltip widget with its owned DMA storage and resident table. */
class EquipClass1797B0 : public LibClass178600
{
public:
    /** @brief Initialize the tooltip display and drawing storage. */
    EquipClass1797B0()
    {
        unk38 = 0x12;
    }

    /** @brief Release tooltip drawing storage and the widget base. */
    virtual ~EquipClass1797B0();

    /** @brief Draw the tooltip rectangle and its stored resource. */
    virtual void draw();

    LibStorageBlock0C unk40;

    u8 unk4c[4];
};

/** Resident tooltip container with one tooltip and eight owned text widgets. */
class EquipClass1796F0 : public LibObject178660
{
public:
    /** @brief Initialize the tooltip container and its embedded displays. */
    EquipClass1796F0()
    {
        unk6c = 0x6FF8;
    }

    /** @brief Destroy the text array, tooltip, and container bases. */
    virtual ~EquipClass1796F0();

    /** @brief Update the tooltip text animation. @param first First update flag. @param second Second update flag. @param third Third update flag. */
    virtual void func_00412C40(u32 first, u32 second, u32 third);

    EquipClass1797B0 unkf0;

    LibObject178750 unk140[8];

    u8 unk9e0[0x30];
};

/** Help bar with the "Equipment" title and label and a scrolling help line. */
class EquipHelpWindow : public FieldClass15AE70
{
public:
    /** @brief Initialize the text display, timer, and scrolling bounds. */
    EquipHelpWindow()
    {
        text = 0;
        scroll_span = 0;
        unkb0[0] = 0;
        initial_pause_frames = 0;
        scroll_phase = 0;
        label_right_edge = 0.0f;
        initial_text_x = 0.0f;
        clip_x = 0.0f;
        clip_width = 0.0f;
    }

    /** @brief Destroy the scrolling text window. */
    virtual ~EquipHelpWindow();

    /** @brief Hold the display position until its timer expires, then scroll and wrap it. */
    virtual void func_slot5c();

    /** @brief Reset the text display and recompute its width for the supported key range. @param text_key Text resource key. */
    virtual void func_slot60(s32 text_key);

    /**
     * @brief Create the text, frame and scrolling display.
     * @param associated Full resource source word.
     * @return One when initial displays exist, otherwise zero.
     */
    virtual s32 func_slotf4(u32 associated);

    LibObject178750* text;

    s32 scroll_span;

    u8 unkb0[2];

    s16 initial_pause_frames;

    u8 scroll_phase;

    u8 unkb5[3];

    float label_right_edge;

    float initial_text_x;

    float clip_x;

    float clip_width;
};

/** Yes/No window that asks "Finish equipping characters?" before leaving the menu. */
class EquipExitConfirmWindow : public FieldClass15AE70
{
public:
    /** @brief Initialize the selection grid pointer and signed selection index. */
    EquipExitConfirmWindow()
    {
        grid = 0;
        selected = -1;
    }

    /** @brief Destroy the initial equipment window. */
    virtual ~EquipExitConfirmWindow();

    /**
     * @brief Create the panel, text labels and selection grid.
     * @param associated Full resource source word.
     * @param x Window horizontal position.
     * @param y Window vertical position.
     * @param code Nested display initializer code.
     * @return One when all displays exist, otherwise zero.
     */
    virtual s32 func_slot10(u32 associated, float x, float y, s32 code);

    /** @brief Refresh icon colors while this window is selected. */
    virtual void func_slot5c();

    /** @brief Activate the selected icon or set the empty-selection state. @return One to stay, or two after cancellation. */
    virtual u8 func_slotb0();

    /** @brief Hide this window and restore the associated State window. @return Two. */
    virtual u8 func_slotb4();

    /** @brief Forward direction zero to the selection grid and test its result. */
    virtual void func_slot68();

    /** @brief Forward direction one to the selection grid and test its result. */
    virtual void func_slot6c();

    /** @brief Color each active icon according to its selection index. @param selected Selected icon index. */
    virtual void func_slotf4(s16 selected);

    FieldObject23CEA0* grid;

    s16 selected;
};

/** Selected character panel: name, level, portrait, Optimize/Switch prompts, and arrows when there are several characters. */
class EquipCharacterWindow : public FieldClass15AE70
{
public:
    /** @brief Initialize the window displays and acquire the active record selection. */
    EquipCharacterWindow();

    /** @brief Show the portrait of the selected character and hide the others. */
    void show_current_portrait();

    /** @brief Destroy the equipment window. */
    virtual ~EquipCharacterWindow();

    /** @brief Enable the display widget while its State window is selected. */
    virtual void func_slot5c();

    /** @brief Create the window displays. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);

    s16 character_slot;

    u8 unkaa[2];

    FieldRecordSelection* selection;

    LibObject175140* name_text;

    LibObject178750* level_label;

    LibObject174F20* level_value;

    ItemCreationClass174C40* left_indicator;

    ItemCreationClass174C40* right_indicator;

    ItemCreationOptionResourceDisplay* portraits[8];

    u8 portrait_slots[8];

    LibObject178750* optimize_prompt;

    LibObject178750* switch_prompt;
};

/** Background window owning three displays of resource 11. */
class EquipResourceWindow : public FieldClass15AE70
{
public:
    /** @brief Initialize the three option display pointers. */
    EquipResourceWindow()
    {
        left_tile = 0;
        middle_tile = 0;
        right_tile = 0;
    }

    /** @brief Destroy the option window. */
    virtual ~EquipResourceWindow();

    /** @brief Create and attach the three option displays. @param associated Full resource source word. @return One. */
    virtual s32 func_slotf4(u32 associated);

    ItemCreationOptionResourceDisplay* left_tile;

    ItemCreationOptionResourceDisplay* middle_tile;

    ItemCreationOptionResourceDisplay* right_tile;
};

/** Background panel behind the item lists. */
class EquipItemListPanel : public FieldClass15AE70
{
public:
    /** @brief Initialize the panel's Field base. */
    EquipItemListPanel()
    {
    }

    /** @brief Destroy the panel window. */
    virtual ~EquipItemListPanel();

    /** @brief Create and attach the panel display. @param associated Full resource source word. @return One. */
    virtual s32 func_slotf4(u32 associated);
};

/** Indices into EquipCharacterRecord::checksums. */
enum EquipCharacterCheck
{
    EQUIP_CHECK_LEVEL = 0,
    EQUIP_CHECK_FLAGS_EXPERIENCE = 1,
    EQUIP_CHECK_HP = 2,
    EQUIP_CHECK_MP = 3,
    EQUIP_CHECK_ATTACK = 4,
    EQUIP_CHECK_DEFENSE = 5,
    EQUIP_CHECK_AGILITY = 6,
    EQUIP_CHECK_HIT = 7,
    EQUIP_CHECK_KNOCKBACK_POWER = 8,
    EQUIP_CHECK_SALT = 9,
    EQUIP_CHECK_CRITICAL_RATE = 10,
    EQUIP_CHECK_KNOCKBACK_RESISTANCE = 11
};

/** Checksum-protected 0xC4-byte character record: level, experience, HP, MP, fury, and statistics. */
class EquipCharacterRecord
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

    /** Intelligence is validated through the HIT checksum. */
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

    /** Indexed by EquipCharacterCheck; the last three entries are unidentified. */
    s32 checksums[15];

    s32 unkc0;

    /**
     * @brief Decode a protected statistic's current value after validating its checksum.
     * @param base Encoded base value.
     * @param effective Encoded effective value.
     * @param value Encoded current value.
     * @param check Stored checksum.
     * @param salt Record checksum salt.
     * @return Current value, or zero for an invalid checksum.
     */
    static s32 decode_statistic(s32 base, s32 effective, s32 value, s32 check, s32 salt)
    {
        if (check != (salt ^ (value ^ (base + effective))))
        {
            return 0;
        }

        return value ^ EQUIP_STAT_WORD_XOR_KEY;
    }

    /** @brief Decode the level. @return Level, or one for an invalid checksum. */
    s32 get_level() const
    {
        if (checksums[EQUIP_CHECK_LEVEL] != (checksums[EQUIP_CHECK_SALT] ^ (encoded_level ^ (encoded_base_level + checksums[EQUIP_CHECK_SALT]))))
        {
            return 1;
        }

        return encoded_level ^ EQUIP_STAT_HALFWORD_XOR_KEY;
    }

    /** @brief Decode the current attack. @return Attack, or zero for an invalid checksum. */
    s32 get_attack() const
    {
        return decode_statistic(encoded_base_attack, encoded_effective_attack, encoded_attack, checksums[EQUIP_CHECK_ATTACK], checksums[EQUIP_CHECK_SALT]);
    }

    /** @brief Decode the current defense. @return Defense, or zero for an invalid checksum. */
    s32 get_defense() const
    {
        return decode_statistic(encoded_base_defense, encoded_effective_defense, encoded_defense, checksums[EQUIP_CHECK_DEFENSE], checksums[EQUIP_CHECK_SALT]);
    }

    /** @brief Decode the effective attack. @return Effective attack, or zero for an invalid checksum. */
    u32 get_effective_attack() const
    {
        if (checksums[EQUIP_CHECK_ATTACK] != (checksums[EQUIP_CHECK_SALT] ^ (encoded_attack ^ (encoded_base_attack + encoded_effective_attack))))
        {
            return 0;
        }

        return encoded_effective_attack ^ EQUIP_STAT_WORD_XOR_KEY;
    }

    /** @brief Decode the effective defense. @return Effective defense, or zero for an invalid checksum. */
    u32 get_effective_defense() const
    {
        if (checksums[EQUIP_CHECK_DEFENSE] != (checksums[EQUIP_CHECK_SALT] ^ (encoded_defense ^ (encoded_base_defense + encoded_effective_defense))))
        {
            return 0;
        }

        return encoded_effective_defense ^ EQUIP_STAT_WORD_XOR_KEY;
    }

    /** @brief Decode the effective agility. @return Effective agility, or zero for an invalid checksum. */
    u32 get_effective_agility() const
    {
        if (checksums[EQUIP_CHECK_AGILITY] != (checksums[EQUIP_CHECK_SALT] ^ (encoded_agility ^ (encoded_base_agility + encoded_effective_agility))))
        {
            return 0;
        }

        return encoded_effective_agility ^ EQUIP_STAT_WORD_XOR_KEY;
    }

    /** @brief Decode the effective hit. @return Effective hit, or zero for an invalid checksum. */
    u32 get_effective_hit() const
    {
        if (checksums[EQUIP_CHECK_HIT] != (checksums[EQUIP_CHECK_SALT] ^ (encoded_hit ^ (encoded_base_hit + encoded_effective_hit))))
        {
            return 0;
        }

        return encoded_effective_hit ^ EQUIP_STAT_WORD_XOR_KEY;
    }

    /** @brief Decode the effective intelligence, which shares the HIT checksum. @return Effective intelligence, or zero for an invalid checksum. */
    u32 get_effective_intelligence() const
    {
        if (checksums[EQUIP_CHECK_HIT] != (checksums[EQUIP_CHECK_SALT] ^ (encoded_hit ^ (encoded_base_hit + encoded_effective_hit))))
        {
            return 0;
        }

        return encoded_effective_intelligence ^ EQUIP_STAT_WORD_XOR_KEY;
    }
};

/** Checksums protecting EquipCharacterEquipment, each mixed with the salt. */
struct EquipEquipmentChecksums
{
    u32 luck;

    u32 stamina;

    u32 equipment;

    u32 sp_cp;

    u32 symbology_mastery;

    u32 battle_skill_mastery;

    u32 tactical_skill_states;

    u32 battle_skill_indices;

    u32 status_skill_levels;

    u32 salt;
};

/** Checksum-protected 0x114-byte character equipment and skill record. */
class EquipCharacterEquipment
{
public:
    s16 encoded_base_luck;

    s16 encoded_effective_luck;

    s16 encoded_luck;

    s16 encoded_base_stamina;

    s16 encoded_effective_stamina;

    s16 encoded_stamina;

    s16 encoded_equipment_slot_count;

    /** Highest valid index into encoded_equipment_ids. */
    s16 encoded_slot_limit;

    s16 encoded_equipment_ids[4];

    s16 encoded_sp;

    s16 encoded_cp;

    s32 unk1c;

    char character_name[24];

    u8 battle_strategy;

    u8 previous_battle_strategy;

    u8 unk3a;

    u8 encoded_anti_attack_aura_mask;

    s8 encoded_status_skill_levels[5];

    u8 encoded_battle_skill_indices[6];

    s8 encoded_tactical_skill_states[7];

    s16 encoded_symbology_mastery[32];

    s16 encoded_battle_skill_mastery[42];

    /** Damage responses in earth, water, fire, wind order. */
    u8 elemental_damage_responses[4];

    u8 attack_element_mask;

    u8 character_resource_variant;

    EquipEquipmentChecksums checksums;

    u32 unk110;

    /** @brief Compute the equipment checksum from the encoded IDs and the salt. @return Equipment checksum. */
    s32 compute_equipment_checksum() const
    {
        return checksums.salt ^ ((encoded_equipment_ids[1] + encoded_equipment_ids[2]) ^ (encoded_equipment_ids[3] + encoded_equipment_ids[0]));
    }

    /** @brief Test the stored equipment checksum. @return True when it agrees with the encoded IDs and the salt. */
    bool equipment_valid() const
    {
        return checksums.equipment ==
               (checksums.salt ^ ((encoded_equipment_ids[1] + encoded_equipment_ids[2]) ^ (encoded_equipment_ids[3] + encoded_equipment_ids[0])));
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

        if ((encoded_slot_limit ^ EQUIP_STAT_HALFWORD_XOR_KEY) < index)
        {
            return 0;
        }

        return encoded_equipment_ids[index] ^ EQUIP_STAT_HALFWORD_XOR_KEY;
    }

    /**
     * @brief Equip an item in a slot and update the equipment checksum, when the record and slot are valid.
     * @param index Equipment slot.
     * @param value Item ID.
     */
    void set_equipment_id(s32 index, s16 value)
    {
        if (equipment_valid() && index >= 0 && index <= (encoded_slot_limit ^ EQUIP_STAT_HALFWORD_XOR_KEY))
        {
            encoded_equipment_ids[index] = value ^ EQUIP_STAT_HALFWORD_XOR_KEY;
            checksums.equipment = compute_equipment_checksum();
        }
    }
};

/** Slot name, item icon, and ATK/DEF/AGL/HIT/INT rows comparing the current value with the selected item's. */
class EquipStatComparisonWindow : public FieldClass15AE70
{
public:
    /** @brief Initialize item comparison records and display pointers. @param state Owning equipment State. */
    EquipStatComparisonWindow(EquipController* state);

    /** @brief Refresh the selected item icon and both statistic columns. @param category Selected category. @param selected Selected item record index. */
    void refresh_item_details(u8 category, s16 selected);

    /** @brief Destroy the item-details window. */
    virtual ~EquipStatComparisonWindow();

    /** @brief Create and attach the item-details displays. @param associated Full resource source word. @return One. */
    virtual s32 func_slotf4(u32 associated);

    EquipController* controller;

    u8 slot;

    u8 unkad;

    s16 item;

    s16 preview_item;

    u8 unkb2;

    u8 unkb3;

    EquipCharacterRecord preview_record;

    /** Encoded resource record used for the comparison. */
    EquipCharacterEquipment preview_equipment;

    LibObject178750* slot_label;

    LibObject172410* item_icon;

    LibObject178750* stat_labels[5];

    LibObject178750* separators[5];

    LibObject178750* arrows[5];

    LibObject174F20* current_values[5];

    LibObject174F20* preview_values[5];
};

/** Background panel behind the equipment slot window. */
class EquipSlotPanel : public FieldClass15AE70
{
public:
    /** @brief Initialize the category panel's Field base. */
    EquipSlotPanel()
    {
    }

    /** @brief Destroy the category panel window. */
    virtual ~EquipSlotPanel();

    /** @brief Create and attach the category panel display. @param associated Full resource source word. @return One. */
    virtual s32 func_slotf4(u32 associated);
};

/** Equipment menu controller: loads the menu resource and builds its windows. */
class EquipController : public FieldClass153E30
{
public:
    /** @brief Initialize the equipment State and its resource table entries. */
    EquipController();

    /** @brief Destroy the equipment State. */
    virtual ~EquipController();

    /** @brief Create and connect the equipment State displays. @return One after display setup. */
    virtual s32 init_windows();

    /**
     * @brief Load an aligned resource and create the State displays.
     * @param buffer Resource buffer.
     * @return Display creation result, or zero for a null buffer.
     */
    virtual s32 on_resource_loaded(void* buffer);

    /** @brief Report this object's default list kind. @return Four. */
    virtual s32 get_default_list_kind();

    /** @brief Submit the State to the resident object queue. */
    virtual void func_001DD7B0();

    /**
     * @brief Allocate and initialize the State's record selection.
     * @return One when a selection exists and initialization succeeds; otherwise zero.
     */
    virtual u8 func_00264110();

    /** @brief Return the loaded resource slot. @return Resource slot. */
    virtual u32 get_resource_slot();

    /** @brief Report whether window setup finished. @return Setup flag. */
    virtual u8 windows_ready();

    /** @brief Release the State resources and queue its receiver. */
    virtual void func_slot5c();

    /** @brief Return the record selection. @return Current record selection. */
    virtual FieldRecordSelection* selected_records();

    s32 resource_slot;

    FieldRecordSelection* selection;

    u8 windows_initialized : 1;

    u8 unk3c_1_7 : 7;

    u8 unk3d[3];

    EquipCharacterWindow* character_window;

    EquipSlotWindow* slot_window;

    EquipStatComparisonWindow* comparison_window;

    EquipItemListPanel* item_list_panel;

    EquipItemListWindow* item_list_window;

    EquipParameterWindow* parameter_window;

    u32 unk58;

    u32 unk5c;

    u16 selected_slot;

    u8 unk62[2];

    s32 selected_item_type;

    void* tooltip;
};

/** Selected item's description, or its "Parameter Changes" (ATK, HIT, DEF, AGL, INT bonuses) while toggled on. */
class EquipParameterWindow : public FieldClass15AE70
{
public:
    /** @brief Initialize the category detail state, labels, and numeric displays. */
    EquipParameterWindow()
    {
        description_key = 0;
        show_parameters = 0;

        for (s32 i = 0; i < 5; i++)
        {
            parameter_labels[i] = 0;
            parameter_values[i] = 0;
        }
    }

    /** @brief Destroy the category detail window. */
    virtual ~EquipParameterWindow();

    /** @brief Refresh the selected category detail displays. */
    virtual void func_slot5c();

    /** @brief Create the multiline and comparison displays. @param associated Full resource source word. @return One, or zero without an associated object. */
    virtual s32 func_slotf4(u32 associated);

    LibObject174D90* description;

    LibObject178750* title;

    LibObject178750* parameter_labels[5];

    LibObject178750* separators[5];

    LibObject174F20* parameter_values[5];

    s32 description_key;

    u8 show_parameters;
};

/** Weapon, Armor, and Accessory slots with the equipped item or "(None)" in each, and the slot cursor. */
class EquipSlotWindow : public FieldClass15AE70
{
public:
    /** @brief Initialize the category widgets and attach the State selection. @param state Owning equipment State. */
    EquipSlotWindow(EquipController* state);

    /** @brief Destroy the category window. */
    virtual ~EquipSlotWindow();

    /** @brief Update the selected category tooltip. */
    virtual void func_slot5c();

    /** @brief Restore the associated record displays and start the selector animation. */
    virtual void func_slot64();

    /** @brief Cycle the selector backward and rebuild the associated category list. */
    virtual void func_slot68();

    /** @brief Cycle the selector forward and rebuild the associated category list. */
    virtual void func_slot6c();

    /** @brief Activate a supported category and restore its associated list window. @return One on activation, or three for an unsupported category. */
    virtual u8 func_slotb0();

    /** @brief Activate the alternate selection window. @return Selection result. */
    virtual u8 func_slotb4();

    /** @brief Apply the selected record action and refresh category displays. @return One. */
    virtual u8 func_slotb8();

    /** @brief Switch the parameter window between the item description and its parameter changes. @return One. */
    virtual u8 func_slotbc();

    /** @brief Cycle to the previous record and rebuild its displays. @return Four after cycling, or zero when unavailable. */
    virtual s32 func_slotd8();

    /** @brief Cycle to the next record and rebuild its displays. @return Four after cycling, or zero when unavailable. */
    virtual s32 func_slotdc();

    /** @brief Create category widgets. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);

    EquipController* controller;

    FieldRecordSelection* selection;

    float row_spacing;

    ItemCreationAllocationRecord* current_item;

    s16 equipped_items[4];

    u8 usable_slot_count;

    u8 unkc1[3];

    LibClass174EF0* slot_labels[4];

    LibObject172410* item_icons[4];

    LibClass174EF0* empty_labels[4];

    void* unkf4;

    void* parameter_window;

    FieldClass153130* equipment_slot_selector;

    FieldClass15AE70* comparison_window;

    FieldClass15AD40* item_list;

    u16 active_slot;
};

/** List of the unequipped items of the selected type, with their icons and modification marks. */
class EquipItemInstanceListWindow : public FieldClass15AD40
{
public:
    /** @brief Initialize list display pointers and attach the option State. @param state Owning equipment State. */
    EquipItemInstanceListWindow(EquipController* state);

    /** @brief Destroy the Field list window. */
    virtual ~EquipItemInstanceListWindow();

    /** @brief Run the equipment list update hook. */
    virtual void func_slot5c();

    /** @brief Activate the selected record and restore the category window. @return One on success, or three when no record is selectable. */
    virtual u8 func_slotb0();

    /** @brief Restore the associated window and clear the detail display. @return Two. */
    virtual u8 func_slotb4();

    /** @brief Return the empty equipment selection result. @return Zero. */
    virtual u8 func_slotb8();

    /** @brief Switch the parameter window between the item description and its parameter changes. @return One. */
    virtual u8 func_slotbc();

    /** @brief Refresh the visible equipment rows. @param start First record index. */
    virtual void refresh_rows(s32 start);

    /** @brief Set the visible equipment row positions. @param start Base row position. */
    virtual void set_scroll_position(float start);

    /** @brief Create the equipment list displays. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slot104(u32 associated);

    /**
     * @brief Show or hide the rows and the list cursor.
     * @param rows Nonzero shows the item icons, factor marks and panel.
     * @param cursor Nonzero shows the cursor and indicator at full brightness; zero hides them and dims the cursor.
     */
    virtual void func_slot10c(u32 rows, u32 cursor);

    /** @brief Recount the category records and clamp the visible selection. */
    void recount_rows();

    ItemCreationOptionResourceDisplay* factor_marks[9];

    LibObject172410* item_icons[9];

    LibClass178630* panel;

    void* mark_allocation;

    EquipController* controller;

    void* tooltip;

    s16 tooltip_item;
};

/** Item types that fit the selected slot, with how many of each are available; types holding a new item are tinted green. */
class EquipItemListWindow : public FieldClass15AD40
{
public:
    /** @brief Initialize the display pointers and owned lists. @param state Owning equipment State. */
    EquipItemListWindow(EquipController* state);

    /** @brief Destroy the owned lists and the Field window. */
    virtual ~EquipItemListWindow();

    /** @brief Update the selected category, row highlight, and detail window. */
    virtual void func_slot5c();

    /** @brief Activate the category list or create the selected record window. @return Selection result. */
    virtual u8 func_slotb0();

    /** @brief Restore the associated window and hide the alternate window. @return Two. */
    virtual u8 func_slotb4();

    /** @brief Switch the parameter window between the item description and its parameter changes. @return One. */
    virtual u8 func_slotbc();

    /** @brief Refresh category names, availability counts, and selection colors. @param start First category row. */
    virtual void refresh_rows(s32 start);

    /** @brief Position all three displays in each row. @param start Base row position. */
    virtual void set_scroll_position(float start);

    /** @brief Create the category names, counts, and selection displays. @param associated Full resource source word. @return One. */
    virtual s32 func_slot104(u32 associated);

    /** @brief Rebuild the list for the selected category. @param category Category index, clamped to two. */
    virtual void func_slot108(u8 category);

    /**
     * @brief Show or hide the list cursor.
     * @param unused Unused.
     * @param cursor Nonzero shows the cursor at full brightness; zero hides it and dims it.
     */
    virtual void func_slot10c(u32 unused, u32 cursor);

    LibObject178750* separators[9];

    LibObject174F20* counts[9];

    EquipController* controller;

    void* unk184;

    EquipItemTypeList item_types;

    s16 unk194;

    EquipNewItemTypeList new_item_types;

    FieldClass15AE70* comparison_window;
};

extern "C" {
#endif

/**
 * @brief Add an item type ID to the end of the list.
 * @param list List to append to.
 * @param value One-based item type ID.
 */
void append_new_item_type(EquipNewItemTypeList* list, u16 value);

/**
 * @brief Add an item type record to the end of the list.
 * @param list List to append to.
 * @param value Item type record, or null for the "(None)" row.
 */
void append_item_type(EquipItemTypeList* list, ItemCreationCategoryRecord* value);

/**
 * @brief Add a node holding `value` to the end of the list.
 * @param list List to append to.
 * @param value Pointer stored in the node. The caller owns it.
 */
void append_grid_widget_node(FieldCountedList* list, void* value);

/**
 * @brief Add a node holding `value` to the end of the list.
 * @param list List to append to.
 * @param value Pointer stored in the node. The caller owns it.
 */
void append_icon_widget_node(FieldCountedList* list, void* value);

/**
 * @brief Add a node holding `value` to the end of the list.
 * @param list List to append to.
 * @param value Pointer stored in the node. The caller owns it.
 */
void append_stat_value_node(FieldCountedList* list, void* value);

/**
 * @brief Add a node holding `value` to the end of the list.
 * @param list List to append to.
 * @param value Pointer stored in the node. The caller owns it.
 */
void append_text_widget_node(FieldCountedList* list, void* value);

/**
 * @brief Add a node holding `value` to the end of the list.
 * @param list List to append to.
 * @param value Pointer stored in the node. The caller owns it.
 */
void append_clip_widget_node(FieldCountedList* list, void* value);

/**
 * @brief Add a node holding `value` to the end of the list.
 * @param list List to append to.
 * @param value Pointer stored in the node. The caller owns it.
 */
void append_panel_widget_node(FieldCountedList* list, void* value);

/**
 * @brief Return the node at `count`. Index zero is the first node after the sentinel.
 * @param list New item type list.
 * @param count Zero-based index among the value nodes.
 * @return The node at that index, or null if the list ends first.
 */
EquipNewItemTypeNode* get_new_item_type_node(EquipNewItemTypeList* list, s32 count);

/**
 * @brief Return the node at `count`. Index zero is the first node after the sentinel.
 * @param list Item type list.
 * @param count Zero-based index among the value nodes.
 * @return The node at that index, or null if the list ends first.
 */
EquipItemTypeNode* get_item_type_node(EquipItemTypeList* list, s32 count);

/**
 * @brief Delete the list nodes after the sentinel and reset the list count.
 * @param list List whose nodes should be released.
 */
void clear_new_item_types(EquipNewItemTypeList* list);

/**
 * @brief Delete the list nodes after the sentinel and reset the list count.
 * @param list List whose nodes should be released.
 */
void clear_item_types(EquipItemTypeList* list);

#ifdef __cplusplus
}
#endif

#endif
