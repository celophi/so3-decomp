#include "overlays/citem/item_controller.h"
#include "include_asm.h"
#include "overlays/citem/text.h"
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

extern "C"
{
void func_4D00B0(void* object);
FieldRecordSelection* func_0028E4D0(FieldRecordSelection* selection);
}

#include "overlays/lib/text_004095C0.h"
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

#define ANGLE_STEP_RADIANS 0.008726646f
#define ANGLE_LIMIT_RADIANS 0.5235988f

enum CitemMessageKey
{
    CITEM_MSG_ITEM_NAMES = 50000
};

/** Partial loaded-resource header containing the block's byte count. */
struct CitemAlignedResource
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

#define ITEM_STAT_WORD_XOR_KEY 0x7DE3F7E3
#define ITEM_STAT_HALFWORD_XOR_KEY 0x7E93

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
class CitemFlagBlock
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

struct ItemListOwner
{
    ItemListNode* head;
    u32 count;
};

/** Item choice window containing a two-column grid and text displays. */
class ItemChoiceWindow184280 : public FieldClass15AE70
{
    public:
        /** @brief Initialize the grid and text links. */
        ItemChoiceWindow184280()
        {
            grid = 0;
            first_text = 0;
            second_text = 0;
        }

        /** @brief Destroy the choice window and its Field base. */
        virtual ~ItemChoiceWindow184280();

        /** @brief Enable grid input when this is the active window. */
        virtual void func_slot5c();

        /** @brief Move the grid selection and update the choice colors. */
        virtual void func_slot70();

        /** @brief Move the grid selection and update the choice colors. */
        virtual void func_slot74();

        /**
         * @brief Apply the selected choice and restore the remaining allocation or item list.
         * @return Zero when input is blocked, the back result for the second choice, otherwise one.
         */
        virtual u8 func_slotb0();

        /**
         * @brief Close the choice window and restore the allocation window.
         * @return Zero when input is blocked, otherwise two.
         */
        virtual u8 func_slotb4();

        /**
         * @brief Create the panels, text displays, and two-column choice grid.
         * @param associated Resource source word.
         * @return One after initialization.
         */
        virtual s32 func_slotf4(u32 associated);

        FieldObject23CEA0* grid;
        LibObject178750* first_text;
        LibObject178750* second_text;
};

/** Observed prefix used by the remaining C window entry points. */
struct ItemRecord
{
    void* methods;
    u32 unk04;
    u8 unk08;
    u8 unk09;
    u16 unk0a;
    u8 unk0c;
    u8 unk0d;
    u8 unk0e[2];
    u32 unk10;
    ItemListOwner panels;
    u8 unk1c[4];
    u32 unk20;
    u8 unk24[0x50];
    ItemListOwner grids;
    u8 unk7c[0x1C];
    u32 unk98;
    u32 unk9c;
    u8 unka0[8];
};

struct StatusRecord
{
    u8 unk00[0x24];
    u32 unk24;
    s8 unk28;
    u8 unk29[0x13];
    u8 unk3c;
};


struct Record0034C6A0
{
    void* methods;
    u8 unk04[0x3C];
    u8 unk40;
};

/** Coordinate-list link owned by the item menu. */
class CitemCoordinateNode
{
    public:
        float x;
        float y;
        CitemCoordinateNode* next;

        /** @brief Initialize the coordinate pair to zero. */
        CitemCoordinateNode()
        {
            x = y = 0.0f;
        }

        /** @brief Destroy a coordinate link. */
        ~CitemCoordinateNode()
        {
        }
};






/** Draw the paired HP and MP gauges for one character. */
/** Gauge origin, zeroed on construction. */
struct ItemGaugeOrigin
{
    /** @brief Start at the origin. */
    ItemGaugeOrigin()
    {
        x = y = 0.0f;
    }

    float x;
    float y;
};

class ItemHpMpGaugeDrawer : public FieldClass159A70
{
    public:
        /** @brief Clear the origin, spacing and character link. */
        ItemHpMpGaugeDrawer()
        {
            origin.x = 0.0f;
            origin.y = 0.0f;
            row_spacing = 0.0f;
            character_id = 0;
            characters = 0;
        }

        /** @brief Release the drawing packet and base. */
        virtual ~ItemHpMpGaugeDrawer();

        /** @brief Rebuild the drawing packet. @param first Unused draw flag. @param depth Unused drawing depth. @param value Unused drawing value. */
        virtual void func_002BC4F0(u32 first, u32 depth, float value);

        ItemGaugeOrigin origin;
        float row_spacing;
        s16 character_id;
        u8 unk3e[2];
        ItemCharacterStats* characters;
};

/** HP and MP gauge transform with drawing and DMA notification interfaces. */
class ItemHpMpGauge : public FieldClass1599E0, public ItemHpMpGaugeDrawer
{
    public:
        /** @brief Initialize the gauge bases with release not yet queued. */
        ItemHpMpGauge()
        {
            queued_for_release = 0;
        }

        /** @brief Release the drawing and transform bases. */
        virtual ~ItemHpMpGauge();

        /** @brief Submit the drawing packet for DMA notification. */
        virtual void func_003EEBE0();

        /** @brief Leave the default update state unchanged. */
        virtual void update();

        /** @brief Report the transform kind. @return Fourteen. */
        virtual s32 get_default_list_kind();

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

/** Moving selector with its coordinate list and selected entry. */
class ItemCoordinateSelector : public LibClass175030
{
    public:
        /** @brief Initialize an empty coordinate list with no selected entry. */
        ItemCoordinateSelector()
        {
            selected = -1;
        }

        /** @brief Destroy the coordinate list and movement bases. */
        virtual ~ItemCoordinateSelector();

        /** @brief Report the intrusive object kind. @return Three. */
        virtual s32 get_default_list_kind();

        /** @brief Leave the default update hook unchanged. */
        virtual void update();

        /** @brief Leave the default notification hook unchanged. */
        virtual void func_003EEBE0();

        ItemList184EB8 nodes;
        s32 selected;
};

/** Item panel window built on the Field window base. */
class ItemWindow1849F0 : public FieldClass15AE70
{
    public:
        /** @brief Initialize the window and its display links. */
        ItemWindow1849F0()
        {
        }

        /** @brief Destroy the window and its Field base. */
        virtual ~ItemWindow1849F0();

        /**
         * @brief Initialize the window displays from a resource source.
         * @param associated Resource source word.
         * @return One after initialization.
         */
        virtual s32 func_slotf4(u32 associated);
};

/** Item list window with fourteen rows and an owned allocation list. */
class ItemListWindow1848D0 : public FieldClass15AD40
{
    public:
        /** @brief Initialize the row pointers and controller link. @param owner Parent item controller. */
        ItemListWindow1848D0(ItemController* owner);

        /** @brief Destroy the owned allocation list and Field window base. */
        virtual ~ItemListWindow1848D0();

        /** @brief Update the selected identifier and the selection marker. */
        virtual void func_slot5c();

        virtual u8 func_slotb0();

        /** @brief Hide the rows and restore the associated window. @return Two after restoring the window. */
        virtual u8 func_slotb4();

        /** @brief Toggle sorting and refresh the current rows. @return Zero for category seven, otherwise one. */
        virtual u8 func_slotbc();

        /**
         * @brief Create the row displays, clipping widgets, and selection controls.
         * @param associated Resource source word.
         * @return One after initialization.
         */
        virtual s32 func_slot104(u32 associated);

        /**
         * @brief Set the attached display flag and height.
         * @param value Unused first flag.
         * @param alternate Value stored as a byte; its full value selects the height.
         */
        virtual void func_slot10c(u32 value, u32 alternate);

        /** @brief Populate the visible rows and update their colors. @param start First record index. */
        virtual void refresh_rows(s32 start);

        /** @brief Position the row displays. @param start Base vertical coordinate. */
        virtual void set_scroll_position(float start);

        /**
         * @brief Rebuild the item-type list for a category and reset the visible rows and selection.
         * @param reset Nonzero to move the selection back to the first row.
         * @param category Category to list, or -1 for the controller's current category.
         */
        virtual void func_slot11c(s32 reset, s32 category);

        LibClass178600* second[14];
        LibClass178600* third[14];
        ItemController* controller;
        ItemList184EC8 entries;
        u32 unk1b8[24];
        u8 sort_enabled;
};

/** Item window linked to its controller and alternate list. */
class ItemWindow184AF0 : public FieldClass15AE70
{
    public:
        /** @brief Initialize the controller link and window fields. @param owner Parent item controller. */
        ItemWindow184AF0(ItemController* owner)
        {
            unka8 = 0;
            unkac = 0;
            unkb0 = 0;
            controller = owner;
            unkb8 = 0;
            unkbc = 0;
            FieldClass15AE70();
        }

        /** @brief Destroy the window and its Field base. */
        virtual ~ItemWindow184AF0();

        /** @brief Update the active selection and hide the linked message display. */
        virtual void func_slot5c();

        /** @brief Restore the linked panel height and mark it for update. */
        virtual void func_slot64();

        /** @brief Move the selector back and highlight, describe and show the newly selected entry. */
        virtual void func_slot68();

        /** @brief Move the selector forward and highlight, describe and show the newly selected entry. */
        virtual void func_slot6c();

        /**
         * @brief Confirm the selected entry: lower the selector, focus the list and describe the choice.
         * @return Zero while the selector is missing or idle, otherwise one.
         */
        virtual u8 func_slotb0();

        /** @brief Set the window state and flags. @return Two after updating the state. */
        virtual u8 func_slotb4();

        /**
         * @brief Create the panel, the ten category labels and icons, the selector and its highlight, then highlight the first label.
         * @param associated Resource source word.
         * @return Zero when the list window is missing, otherwise one.
         */
        virtual s32 func_slotf4(u32 associated);

        FieldClass153130* unka8;
        FieldClass153170* unkac;
        ItemListWindow1848D0* unkb0;
        ItemController* controller;
        u16 unkb8;
        u8 unkba[2];
        void* unkbc;
};

/** Observed C prefix of the native 0x114-byte LibObject178750 text widget. */
struct CitemTextDisplay
{
    void* methods;
    u8 unk04[0x14];
    LibUiRect16 rectangle;
    u8 unk28[0x10];
    u8 unk38;
    u8 unk39[3];
    u8 unk3c;
    u8 unk3d[2];
    u8 unk3f;
    u8 unk40[0x40];
    float scale_x;
    float scale_y;
    u8 unk88[0xC];
    u32 color;
    u8 unk98[4];
    u32 mode;
};

/** Item message window containing three text displays. */
class ItemWindow1844B0 : public FieldClass15AE70
{
    public:
        /** @brief Initialize the window and its display links. */
        ItemWindow1844B0()
        {
            text[0] = 0;
            text[1] = 0;
            text[2] = 0;
            width = 0.0f;
            height = 0.0f;
            scale = 0.0f;
            unkc0 = 0.0f;
            row_spacing = 0.0f;
            text_x = 0.0f;
            text_y = 0.0f;
            unkd0 = 0.0f;
        }

        /** @brief Destroy the window and its Field base. */
        virtual ~ItemWindow1844B0();

        /**
         * @brief Initialize the window displays from a resource source.
         * @param associated Resource source word.
         * @return One after initialization.
         */
        virtual s32 func_slotf4(u32 associated);

        LibObject178750* text[3];
        float width;
        float height;
        float scale;
        float unkc0;
        float row_spacing;
        float text_x;
        float text_y;
        float unkd0;
};

/** Item text window with delayed horizontal scrolling. */
class ItemWindow184BF0 : public FieldClass15AE70
{
    public:
        /** @brief Initialize the window and its display links. */
        ItemWindow184BF0()
        {
            text_display = 0;
            scroll_extent = 0;
            scrolling = 0;
            delay_frames = 0;
            label_width = 0.0f;
            start_x = 0.0f;
            left_edge = 0.0f;
            visible_width = 0.0f;
        }

        /** @brief Destroy the window and its Field base. */
        virtual ~ItemWindow184BF0();

        /** @brief Delay, scroll and wrap the text within its horizontal bounds. */
        virtual void func_slot5c();

        /**
         * @brief Set the scrolling message and restart its delay when the key is in range.
         * @param text_key Message key; only keys 7020 through 7034 are accepted.
         */
        virtual void func_slot60(s32 text_key);

        /**
         * @brief Create the label, hint and clipped scrolling message, then show the first message.
         * @param associated Resource source word.
         * @return Zero when a display could not be allocated, otherwise one.
         */
        virtual s32 func_slotf4(u32 associated);

        LibObject178750* text_display;
        s32 scroll_extent;
        s16 delay_frames;
        u8 scrolling;
        u8 unkb3;
        float label_width;
        float start_x;
        float left_edge;
        float visible_width;
};

/** Item window containing three resource display widgets. */
class ItemWindow184CF0 : public FieldClass15AE70
{
    public:
        /** @brief Initialize the window and its display links. */
        ItemWindow184CF0()
        {
            unka8 = 0;
            unkac = 0;
            unkb0 = 0;
        }

        /** @brief Destroy the window and its Field base. */
        virtual ~ItemWindow184CF0();

        /**
         * @brief Create the window container and its three resource displays.
         * @param associated Resource source word.
         * @return One after initialization.
         */
        virtual s32 func_slotf4(u32 associated);

        ItemCreationOptionResourceDisplay* unka8;
        ItemCreationOptionResourceDisplay* unkac;
        ItemCreationOptionResourceDisplay* unkb0;
        u8 unkb4[4];
};

/** Payload-list link owned by the item menu. */
class ItemListNode
{
    public:
        void* value;
        ItemListNode* next;

        /** @brief Destroy the link without releasing its payload. */
        ~ItemListNode()
        {
        }
};

typedef struct ItemSortRecord
{
    u8 unk00[2];
    u16 table_index;
    u8 unk04[4];
    u8 unk08;
} ItemSortRecord;

typedef ItemCreationCategoryDefinition ItemSortDefinition;


struct ControlScreen
{
    u8 unk00[0x1C];
    float y;
    u8 unk20[0x1C];
    u8 unk3c;
    u8 unk3d[2];
    u8 unk3f;
    u8 unk40[0x30];
    float unk70;
};


/** Partial display settings used to frame the allocation model preview. */
struct CitemDisplaySettings
{
    u8 unk00[0x18C];
    u8 widescreen;
};

/** Prefix of Field's menu manager (vtable D_15B020); offset 0x14 is the active menu controller. */
typedef struct CitemWindowController
{
    u8 unk00[0x14];
    struct FieldClass153E30* selected;
} CitemWindowController;

/** Partial runtime state reached through D_001B643C. */
typedef struct CitemRuntimeState
{
    u8 unk00[0x9A];
    u8 unk9a;
} CitemRuntimeState;

/** Prefix of native D_153D40 runtime storage produced by Field002630F0. */
typedef struct CitemRuntime643C
{
    u8 unk00[4];
    ItemCharacterStats* characters;
    u8 unk08[4];
    CitemRuntimeState* state;
    CitemWindowController* controller;
    u8 unk14[8];
    void* field_camera;
    FieldBufferSlots* buffers;
} CitemRuntime643C;

/** The allocation helper receives this resident storage opaquely. */
extern "C" ResidentObject1B64F8* D_001B64F8;

extern "C" u16 D_354CE0[];

extern "C" CitemRuntime643C* D_001B643C;

/** Item action window with an eight-position coordinate selector. */
class ItemWindow1845B0 : public FieldClass15AE70
{
    public:
        /** @brief Initialize the selector links and action state. */
        ItemWindow1845B0()
        {
            records = 0;
            selection = 0;
            x = 0.0f;
            y = 0.0f;
            row_height = 0.0f;
            pulse_level = 0;
            pulse_step = 1;
            unkc4 = 2;
            message_changed = 0;
        }

        /** @brief Restore the controller message and destroy the window base. */
        virtual ~ItemWindow1845B0();

        /** @brief Pulse the comparison colours and refresh each party member's ATK, DEF and INT change for the selected item. */
        virtual void func_slot5c();
        /** @brief Move the selector from its second coordinate row to its first row. */
        virtual void func_slot68();
        /** @brief Move the selector from its first coordinate row to its second row. */
        virtual void func_slot6c();
        /** @brief Move the selector back one entry, wrapping to its eighth entry. */
        virtual void func_slot70();
        /** @brief Advance the selector one entry, wrapping after its eighth entry. */
        virtual void func_slot74();
        /**
         * @brief Equip the selected allocation on the selected character and refresh their statistics.
         * @return Three when nobody or no eligible allocation is selected, otherwise zero.
         */
        virtual u8 func_slotb0();
        /** @brief Close the action window and restore its parent. @return Two after closing the window. */
        virtual u8 func_slotb4();
        /**
         * @brief Toggle the action mode and message for category two.
         * @return One when the selected allocation belongs to category two, otherwise zero.
         */
        virtual s32 func_slotc0();
        /** @brief Forward to the slot 0xC0 handler. @return The handler's result. */
        virtual s32 func_slotc4();
        /**
         * @brief Create the party panels with names, portraits and stat-comparison labels, then show the item category hint.
         * @param associated Resource source word.
         * @return Zero when the selector could not be allocated, otherwise one.
         */
        virtual s32 func_slotf4(u32 associated);

        FieldRecordSelection* records;
        ItemCoordinateSelector* selection;
        float x;
        float y;

        /** Height of each character panel. */
        float row_height;

        s32 pulse_level;
        s32 pulse_step;
        s32 unkc4;
        u8 message_changed;
        u8 unkc9[3];
        ItemCreationOptionResourceDisplay* indicators[8];
        LibObject178750* stat_values[8][3];
};

/** Item action window owning a selector and a list of display widgets. */
class ItemWindow1846B0 : public FieldClass15AE70
{
    public:
        /** @brief Initialize the selector links, display list, and action state. */
        ItemWindow1846B0()
        {
            records = 0;
            selection = 0;
            x = 0.0f;
            y = 0.0f;
            row_height = 0.0f;
            message_changed = 0;
        }

        /** @brief Restore the controller message and destroy the display list and window base. */
        virtual ~ItemWindow1846B0();
        /** @brief Release the list's display objects and the window's base displays. */
        virtual void func_slot0c();
        /** @brief Update the gauges and refresh each party member's HP, MP, status badges and name color. */
        virtual void func_slot5c();
        /** @brief Move the selector from its second coordinate row to its first row. */
        virtual void func_slot68();
        /** @brief Move the selector from its first coordinate row to its second row. */
        virtual void func_slot6c();
        /** @brief Move the selector back one entry, wrapping to its eighth entry. */
        virtual void func_slot70();
        /** @brief Advance the selector one entry, wrapping after its eighth entry. */
        virtual void func_slot74();
        /** @brief Use the selected item on the selected party member. @return Three when it can't be used, otherwise zero. */
        virtual u8 func_slotb0();
        /** @brief Close the action window and restore its parent. @return Two after closing the window. */
        virtual u8 func_slotb4();
        /**
         * @brief Create the party panels with names, HP and MP values, portraits, status badges, gauges and selector positions.
         * @param associated Resource source word.
         * @return Zero when the selector could not be allocated, otherwise one.
         */
        virtual s32 func_slotf4(u32 associated);

        FieldRecordSelection* records;
        ItemCoordinateSelector* selection;
        float x;
        float y;

        /** Height of each character panel. */
        float row_height;
        ItemList184ED8 displays;
        LibObject174F20* hp_values[8];
        LibObject174F20* mp_values[8];
        LibObject174F20* max_hp_values[8];
        LibObject174F20* max_mp_values[8];
        LibObject175140* labels[8];
        ItemCreationOptionResourceDisplay* indicators[8];
        ItemCreationOptionResourceDisplay* badges[8][4];
        u8 message_changed;
        u8 unk209[3];
};

/**
 * @brief Update the controller's text window when it is present.
 * @param window Text window to update.
 * @param key Signed message key.
 */
static inline void set_item_window_message(ItemWindow184BF0* window, s16 key)
{
    if (window != 0)
    {
        window->func_slot60(key);
    }
}

/** Allocation-detail window with six item-code and resource-display rows. */
class ItemAllocationWindow1847B0 : public FieldClass15AD40
{
    public:
        /** @brief Initialize row pointers, angle state, and the Field base. */
        ItemAllocationWindow1847B0()
        {
            for (s32 index = 0; index < 6; index++)
            {
                first[index] = 0;
            }
            unk1b0 = 0;
            unk1b8 = 0;
            unk1bc = 0;
            FieldClass15AD40();
        }

        /** @brief Detach the panel and destroy the Field window base. */
        virtual ~ItemAllocationWindow1847B0();

        /** @brief Release the nested container and the base display lists. */
        virtual void func_slot0c();

        /** @brief Update the list input, the selected allocation's detail codes and marker, and the model preview state. */
        virtual void func_slot5c();

        /** @brief Increase the active display angle up to its limit. */
        virtual void func_slot68();

        /** @brief Decrease the active display angle down to zero. */
        virtual void func_slot6c();

        /**
         * @brief Open the category-specific action window for the selected allocation.
         * @return Zero during preview, three for an unavailable action, otherwise one.
         */
        virtual u8 func_slotb0();

        /**
         * @brief Cancel the active preview or restore the associated item list.
         * @return Two after handling the back action.
         */
        virtual u8 func_slotb4();

        /**
         * @brief Toggle the selected allocation's model preview.
         * @return Zero after handling or ignoring the preview request.
         */
        virtual u8 func_slotb8();

        /**
         * @brief Open the choice window for the selected allocation when permitted.
         * @return Zero during a preview, three for an unsellable entry, otherwise one.
         */
        virtual u8 func_slotbc();

        /**
         * @brief Build the allocation rows, detail widgets, preview labels, and selection controls.
         * @param associated Loaded resource slot.
         * @return One after initialization.
         */
        virtual s32 func_slot104(u32 associated);

        /**
         * @brief Set row flags and update the selection control height.
         * @param value Flag stored in each item-code and resource row.
         * @param alternate Control flag; its full value selects the height.
         */
        virtual void func_slot10c(u32 value, u32 alternate);

        /** @brief Populate the visible allocation rows. @param start First allocation index. */
        virtual void refresh_rows(s32 start);

        /** @brief Position the allocation rows. @param start Vertical offset. */
        virtual void set_scroll_position(float start);

        /**
         * @brief Refresh the allocation selection or its model preview.
         * @param reset Nonzero to reset the selection position.
         */
        void func_0034FB80(s32 reset);

        LibObject172410* first[6];
        LibObject172440* details[8];
        ItemCreationClass172870* display170;
        LibClass178630* panel;
        LibObject178750* text178;
        LibObject178750* text17c;
        ItemCreationOptionResourceDisplay* second[6];
        LibObject178660* container;
        LibObject178750* text19c;
        u8 unk1a0[4];
        LibObject178750* text1a4;
        LibObject178750* text1a8;
        LibObject172410* selected_code;
        u8 unk1b0;
        u8 unk1b1[7];
        FieldClass15BB90* unk1b8;
        u8 unk1bc;
};


extern "C"
{
extern u8 __vt__23ItemCreationClass175110[];
extern LibVector4 D_50CD30;
extern u64 D_004ED330[];
extern LibWidgetColors4C5590 D_354C40;
extern void func_2CEAF0(void* object, s32 flags);
extern void func_100B40(void* object);
extern void func_4CE4C0(LibVector4* destination, const LibVector4* source);
extern void func_4618F0(void* record, s32 flag);
extern void func_4C48B0(void* record, s32 flag);
extern void func_2CD9F0(void* record, s32 flag);
extern void func_44B110(void* object, s32 code, s32 first, void* source, float z, s32 flag);
extern s32 func_2E19D0(ItemCreationAllocationRecord* record, s32 character);
extern u16 func_2CDFB0(FieldStateCE420* object);
extern const char D_354C80[];
extern LibCameraContext* D_001B6650;
extern s32 func_40C7E0(ResidentObject1B64F8* inventory, s16 identifier, s32 owner);
extern void func_3F9890(ItemCharacterStats* record, ItemCharacterEquipment* equipment, const ItemCreationAllocationRecord* candidate, s32 index);

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

/** @brief Apply the window scale to one text widget. @param object Text window. @param index Text-widget index. */
static inline void scale_window_text(ItemWindow1844B0* object, u32 index)
{
    struct CitemTextDisplay* text = (struct CitemTextDisplay*)object->text[index];
    float scale = object->scale;
    text->scale_y = scale;
    text->scale_x = scale;
    text->unk3c = 1;
}

/**
 * @brief Return the 128-byte-aligned resource header.
 * @param buffer Completed resource buffer.
 * @return Aligned resource header.
 */
static inline CitemAlignedResource* aligned_item_resource(void* buffer)
{
    return reinterpret_cast<CitemAlignedResource*>((reinterpret_cast<u32>(buffer) + 0x7F) & ~0x7F);
}

/** @brief Delete an owned record selection and clear its pointer. @param selection Owned selection. */
static inline void release_record_selection(FieldRecordSelection*& selection)
{
    if (selection != 0)
    {
        delete selection;
        selection = 0;
    }
}

/**
 * @brief Allocate and populate a missing record selection.
 * @param object Receiver that owns the selection.
 * @return One after successful population, or zero if already present or initialization fails.
 */
static inline u8 create_record_selection(ItemController* object)
{
    FieldRecordSelection* selection;
    if (object->selection != 0)
    {
        return 0;
    }
    selection = (FieldRecordSelection*)func_00100AC0(sizeof(FieldRecordSelection), 0);
    if (selection != 0)
    {
        selection = func_0028E4D0(selection);
    }
    object->selection = selection;
    if (object->selection == 0)
    {
        return 0;
    }
    if ((u8)func_0028E3D0(object->selection) == 0)
    {
        return 0;
    }
    return 1;
}

/**
 * @brief Allocate a coordinate node with its scalar values initially clear.
 * @return Allocated node, or null.
 */
static inline CitemCoordinateNode* allocate_coordinate_node(void)
{
    CitemCoordinateNode* node = new (0) CitemCoordinateNode;
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
 * @return Category record, or null outside one through 750.
 */
static inline ItemCreationCategoryRecord* item_category_record(s32 value)
{
    ResidentObject1B64F8* base = D_001B64F8;
    u16 index = value;
    bool valid = false;

    if (index > 0 && index <= 750)
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
    item_append_selector_coordinate(&selector->nodes, CitemCoordinate2(x, y));
}

/**
 * @brief Set a numeric widget's value and mark it for update.
 * @param image Numeric widget.
 * @param value Value to show.
 */
static inline void set_cost_value(LibObject174F20* image, s32 value)
{
    image->numeric_value = value;
    image->unk3c = 1;
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
 * @brief Set a selector's panel height and mark it for update.
 * @param selector Selector, or null.
 * @param height Panel height.
 */
static inline void set_selector_height(FieldClass153130* selector, float height)
{
    if (selector != 0)
    {
        selector->ItemCreationClass185050::unk30 = height;
        selector->unk3c = 1;
    }
}

/** @brief Read the catalog entry's unsellable flag. @param definition Catalog entry. @return Flag as a byte. */
static inline u8 item_definition_unsellable(const ItemCreationCategoryDefinition* definition)
{
    return definition->unsellable;
}

void func_00348460(ItemRecord* item, u8 value)
{
    item->unk0c = value;
}

u8 func_00348470(ItemRecord* item)
{
    return item->unk0c;
}

void func_00348480(ItemRecord* item, u8 value)
{
    item->unk08 = value;
}

u8 func_00348490(ItemRecord* item)
{
    return item->unk08;
}

void func_003484A0(ItemRecord* item, u16 value)
{
    item->unk0a = value;
}

u16 func_003484B0(ItemRecord* item)
{
    return item->unk0a;
}


void func_003484E0(ItemRecord* item, u32 value)
{
    item->unk9c = value;
}

u32 func_003484F0(ItemRecord* item)
{
    return item->unk9c;
}

void func_00348500(ItemRecord* item, u32 value)
{
    item->unk04 = value;
}

u32 func_00348510(ItemRecord* item)
{
    return item->unk04;
}

u32 func_00348520(ItemRecord* item)
{
    return item->unk10;
}

void func_00348530(void* object)
{
}

void func_00348540(void* object)
{
}

void func_00348550(void* object)
{
}

void func_00348560(void* object)
{
}

void func_00348570(void* object)
{
}

void func_00348580(void* object)
{
}

void func_00348590(void* object)
{
}

void func_003485A0(void* object)
{
}

void func_003485B0(void* object)
{
}

void func_003485C0(void* object)
{
}

void func_003485D0(void* object)
{
}

void func_003485E0(void* object)
{
}

void func_003485F0(void* object)
{
}

void func_00348600(void* object)
{
}

void func_00348610(void* object)
{
}

void func_00348620(void* object)
{
}

void func_00348630(void* object)
{
}

void func_00348640(void* object)
{
}

s32 func_00348650(void* object)
{
    return 0;
}

s32 func_00348660(void* object)
{
    return 0;
}

s32 func_00348670(void* object)
{
    return 0;
}

s32 func_00348680(void* object)
{
    return 0;
}

s32 func_00348690(void* object)
{
    return 0;
}

s32 func_003486A0(void* object)
{
    return 0;
}

s32 func_003486B0(void* object)
{
    return 0;
}

s32 func_003486C0(void* object)
{
    return 0;
}

s32 func_003486D0(void* object)
{
    return 0;
}

s32 func_003486E0(void* object)
{
    return 0;
}

void func_003486F0(void* object)
{
}

void func_00348700(void* object)
{
}

u8 func_00348710(ItemRecord* item)
{
    return item->unk0d;
}

void func_00348720(ItemRecord* item, u8 value)
{
    item->unk0d = value;
}

void func_00348730(void* object)
{
}

u32 func_003487B0(ItemRecord* item)
{
    return item->unk20;
}

void ItemChoiceWindow184280::func_slot74()
{
    if (!func_slot28())
    {
        if (grid->process_direction(2) != 1)
        {
            if (grid->unk114 != 0)
            {
                first_text->set_color(0x808080);
                second_text->set_color(0x288080);
            }
            else
            {
                first_text->set_color(0x288080);
                second_text->set_color(0x808080);
            }
        }
    }
}

void ItemChoiceWindow184280::func_slot70()
{
    if (!func_slot28())
    {
        if (grid->process_direction(3) != 1)
        {
            if (grid->unk114 != 0)
            {
                first_text->set_color(0x808080);
                second_text->set_color(0x288080);
            }
            else
            {
                first_text->set_color(0x288080);
                second_text->set_color(0x808080);
            }
        }
    }
}

void func_003489F0(ItemRecord* item, u32 value)
{
    item->unk20 = value;
}

}

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

s32 ItemHpMpGauge::initialize(s32 code, s32 first, void* source, float x, float y, float z)
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

void ItemHpMpGauge::func_003F4410(u32 value)
{
    func_4D00B0(this);
}

void ItemHpMpGauge::func_003EEBE0()
{
    dma_pending = 1;
    if (unk08 != 0)
    {
        func_0011F770(unk08, this);
    }
}

inline ItemHpMpGaugeDrawer::~ItemHpMpGaugeDrawer()
{
}

ItemHpMpGauge::~ItemHpMpGauge()
{
}

extern "C"
{

/** @brief Build the paired HP and MP gauge drawing packet. @param drawer Gauge drawer. */
void func_003492F0(ItemHpMpGaugeDrawer* drawer);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/citem", func_003492F0);

}

void ItemHpMpGaugeDrawer::func_002BC4F0(u32 first, u32 depth, float value)
{
    ResidentPacket* packet = unk08;
    if (packet != 0)
    {
        packet->unk08 = packet->unk00 + 64;
        packet->unk0c = packet->unk08;
        packet->unk15 = 0;
        func_0011F140(packet, D_004ED330[0]);
        func_003492F0(this);
    }
}

u32 ItemController::get_resource_slot()
{
    return resource_slot;
}

extern "C"
{

/**
 * @brief Initialize a panel with three positioned and scaled text widgets.
 * @param object Text-window receiver.
 * @param associated Associated resource source word.
 * @return One after initialization.
 */
}

s32 ItemWindow1844B0::func_slotf4(u32 associated)
{
    LibClass178630* panel;
    this->width = 192.0f;
    this->height = 104.0f;
    func_002CE760(this, associated, 0, 9, 0x578, 16.0f, 360.0f, 0.0f);
    panel = allocate_panel();
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, this->width, this->height, 88.0f);
    lib_container_attach_widget(this->unk10, (LibClass178600*)panel);
    this->text[0] = allocate_text_widget();
    this->text[1] = allocate_text_widget();
    this->text[2] = allocate_text_widget();
    this->scale = 0.85f;
    this->unkc0 = 14.0f;
    this->row_spacing = 28.0f;
    this->text_x = 16.0f;
    this->text_y = this->height / 3.0f - this->row_spacing / 2.0f;
    this->unkd0 = 3.0f;
    this->text[0]->init_resource_rectangle(this->text_x, this->text_y, 0.0f, 0.0f, associated, 0x1B80, 0);
    this->text[1]->init_resource_rectangle(this->text_x, this->text_y + this->row_spacing, 0.0f, 0.0f, associated, 0x1B7D, 0);
    this->text[2]->init_resource_rectangle(80.0f + this->text_x, this->text_y + this->row_spacing, 0.0f, 0.0f, associated, 0x1B7E, 0);
    scale_window_text(this, 0);
    scale_window_text(this, 1);
    scale_window_text(this, 2);
    lib_container_attach_widget(this->unk10, (LibClass178600*)this->text[0]);
    lib_container_attach_widget(this->unk10, (LibClass178600*)this->text[1]);
    lib_container_attach_widget(this->unk10, (LibClass178600*)this->text[2]);
    ((struct CitemTextDisplay*)this->text[0])->unk3f = 0;
    return 1;
}

/** @brief Pulse the comparison colours and refresh each party member's ATK, DEF and INT change for the selected item. */
void ItemWindow1845B0::func_slot5c()
{
    ItemController* owner = static_cast<ItemController*>(D_001B643C->controller->selected);

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
        s8 slot = records->slots[index];

        if (slot <= 0)
        {
            continue;
        }

        indicators[row]->unk3f = 1;
        stat_values[row][0]->unk3f = 1;
        stat_values[row][1]->unk3f = 1;
        stat_values[row][2]->unk3f = 1;
        ItemCreationAllocationRecord* allocation = owner->unkbc;

        if (allocation == 0)
        {
            set_display_brightness(indicators[row], 50.0f);
            lib_text_set_resource(stat_values[row][0], owner->get_resource_slot(), 0x1B9C, 0);
            lib_text_set_resource(stat_values[row][1], owner->get_resource_slot(), 0x1B9C, 0);
            lib_text_set_resource(stat_values[row][2], owner->get_resource_slot(), 0x1B9C, 0);
            continue;
        }

        u16 equipment_mask = D_001B64F0[item_allocation_value(allocation)].equipment_mask;

        if (equipment_mask & (1 << (slot - 1)))
        {
            set_display_brightness(indicators[row], 128.0f);
        }
        else
        {
            set_display_brightness(indicators[row], 50.0f);
            lib_text_set_resource(stat_values[row][0], owner->get_resource_slot(), 0x1B9C, 0);
            lib_text_set_resource(stat_values[row][1], owner->get_resource_slot(), 0x1B9C, 0);
            lib_text_set_resource(stat_values[row][2], owner->get_resource_slot(), 0x1B9C, 0);
            continue;
        }

        ItemCharacterStats* character = &reinterpret_cast<ItemCharacterStats*>(records->records)[index];
        ItemCharacterEquipment* equipment = &static_cast<ItemCharacterEquipment*>(records->unk04)[index];
        ItemCharacterStats character_copy = *character;
        ItemCharacterEquipment equipment_copy = *equipment;

        switch (static_cast<u8>(D_001B64F0[item_allocation_value(allocation)].category))
        {
        case 0:
            equipment_copy.set_equipment_id(0, lib_allocation_get_identifier(allocation));
            break;
        case 1:
            equipment_copy.set_equipment_id(1, lib_allocation_get_identifier(allocation));
            break;
        case 2:
            equipment_copy.set_equipment_id(unkc4, lib_allocation_get_identifier(allocation));
            break;
        }

        func_3F9890(&character_copy, &equipment_copy, 0, -1);

        if (character_attack(character_copy) > character_attack(*character))
        {
            lib_text_set_resource(stat_values[row][0], owner->get_resource_slot(), 0x1B99, 0);
            stat_values[row][0]->set_color(static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) |
                                          (static_cast<u64>(static_cast<u8>(static_cast<s32>(80.0f + 2.6666667f * pulse_level))) << 8) |
                                          (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) << 16));
        }
        else if (character_attack(character_copy) == character_attack(*character))
        {
            lib_text_set_resource(stat_values[row][0], owner->get_resource_slot(), 0x1B9B, 0);
        }
        else
        {
            lib_text_set_resource(stat_values[row][0], owner->get_resource_slot(), 0x1B9A, 0);
            stat_values[row][0]->set_color(static_cast<u64>(static_cast<u8>(static_cast<s32>(80.0f + 2.6666667f * pulse_level))) |
                                          (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) << 8) |
                                          (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) << 16));
        }

        if (character_defense(character_copy) > character_defense(*character))
        {
            lib_text_set_resource(stat_values[row][1], owner->get_resource_slot(), 0x1B99, 0);
            stat_values[row][1]->set_color(static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) |
                                          (static_cast<u64>(static_cast<u8>(static_cast<s32>(80.0f + 2.6666667f * pulse_level))) << 8) |
                                          (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) << 16));
        }
        else if (character_defense(character_copy) == character_defense(*character))
        {
            lib_text_set_resource(stat_values[row][1], owner->get_resource_slot(), 0x1B9B, 0);
        }
        else
        {
            lib_text_set_resource(stat_values[row][1], owner->get_resource_slot(), 0x1B9A, 0);
            stat_values[row][1]->set_color(static_cast<u64>(static_cast<u8>(static_cast<s32>(80.0f + 2.6666667f * pulse_level))) |
                                          (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) << 8) |
                                          (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) << 16));
        }

        if (character_intelligence(character_copy) > character_intelligence(*character))
        {
            lib_text_set_resource(stat_values[row][2], owner->get_resource_slot(), 0x1B99, 0);
            stat_values[row][2]->set_color(static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) |
                                          (static_cast<u64>(static_cast<u8>(static_cast<s32>(80.0f + 2.6666667f * pulse_level))) << 8) |
                                          (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) << 16));
        }
        else if (character_intelligence(character_copy) == character_intelligence(*character))
        {
            lib_text_set_resource(stat_values[row][2], owner->get_resource_slot(), 0x1B9B, 0);
        }
        else
        {
            lib_text_set_resource(stat_values[row][2], owner->get_resource_slot(), 0x1B9A, 0);
            stat_values[row][2]->set_color(static_cast<u64>(static_cast<u8>(static_cast<s32>(80.0f + 2.6666667f * pulse_level))) |
                                          (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) << 8) |
                                          (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) << 16));
        }
    }
}

s32 ItemWindow1845B0::func_slotc0()
{
    ItemController* controller = static_cast<ItemController*>(D_001B643C->controller->selected);
    ItemCreationAllocationRecord* allocation = controller->unkbc;
    if (allocation != 0)
    {
        u16 identifier = allocation->definition_index();
        if ((u8)D_001B64F0[identifier].category == 2)
        {
            unkc4 = unkc4 == 2 ? 3 : 2;
            if (unkc4 == 2)
            {
                set_item_window_message(controller->unk48, 0x1B78);
            }
            if (unkc4 == 3)
            {
                set_item_window_message(controller->unk48, 0x1B79);
            }
            return 1;
        }
    }
    return 0;
}

extern "C"
{

}

s32 ItemWindow1845B0::func_slotc4()
{
    return this->func_slotc0();
}

extern "C"
{

/**
 * @brief Test whether the coordinate selector's control byte is clear.
 * @param selection Coordinate selector to inspect.
 * @return One when the control byte is zero, otherwise zero.
 */
static inline s32 item_selection_control_is_clear(ItemCoordinateSelector* selection)
{
    return ((u32)selection->ItemCreationClass185050::unk35 > 0) ^ 1;
}

}

void ItemWindow1845B0::func_slot70()
{
    ItemCoordinateSelector* selection = this->selection;
    s32 index;
    if (item_selection_control_is_clear(selection) != 0)
    {
        return;
    }
    index = selection->selected - 1;
    if (index < 0)
    {
        index = 7;
    }
    func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(selection), index, 0);
}

extern "C"
{

}

void ItemWindow1845B0::func_slot74()
{
    ItemCoordinateSelector* selection = this->selection;
    s32 index;
    if (item_selection_control_is_clear(selection) != 0)
    {
        return;
    }
    index = selection->selected + 1;
    if (index >= 8)
    {
        index = 0;
    }
    func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(selection), index, 0);
}

extern "C"
{

}

void ItemWindow1845B0::func_slot6c()
{
    ItemCoordinateSelector* selection = this->selection;
    s32 index;
    if (item_selection_control_is_clear(selection) != 0)
    {
        return;
    }
    switch (selection->selected)
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

extern "C"
{

}

void ItemWindow1845B0::func_slot68()
{
    ItemCoordinateSelector* selection = this->selection;
    s32 index;
    if (item_selection_control_is_clear(selection) != 0)
    {
        return;
    }
    switch (selection->selected)
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

extern "C"
{

}

u8 ItemWindow1845B0::func_slotb4()
{
    ItemCreationAllocationRecord* records[100];
    ItemController* controller = static_cast<ItemController*>(D_001B643C->controller->selected);
    if (lib_collect_unequipped_allocations(D_001B64F8, records, controller->category) == 0)
    {
        controller->remove_child(this);
        controller->remove_child(this->func_slot44());
        FieldClass15AE70* associated = (FieldClass15AE70*)this->func_slot44();
        ItemListWindow1848D0* list = static_cast<ItemListWindow1848D0*>(associated->func_slot44());
        list->func_slot11c(0, -1);
        list->func_slot10c(1, 1);
        D_001B643C->controller->selected->func_00263C70(list);
    }
    else
    {
        controller->remove_child(this);
        ItemAllocationWindow1847B0* associated = static_cast<ItemAllocationWindow1847B0*>(this->func_slot44());
        associated->container->unkab = 1;
        controller->func_00263C70(associated);
    }
    return 2;
}

/**
 * @brief Equip the selected allocation on the selected character and refresh their statistics.
 * @return Three when nobody or no eligible allocation is selected, otherwise zero.
 */
u8 ItemWindow1845B0::func_slotb0()
{
    ItemController* owner = static_cast<ItemController*>(D_001B643C->controller->selected);
    s8 slot;
    ItemCharacterStats* character;
    ItemCharacterEquipment* equipment;
    ItemCreationAllocationRecord* allocation = owner->unkbc;
    FieldRecordSelection* records = this->records;
    s16 index = selection->selected;
    slot = records->slots[index];

    if (allocation != 0 && slot > 0)
    {
        character = &reinterpret_cast<ItemCharacterStats*>(records->records)[index];
        equipment = &static_cast<ItemCharacterEquipment*>(records->unk04)[index];

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
        case 0:
            func_40C7E0(D_001B64F8, equipment->get_equipment_id(0), 0);
            func_40C7E0(D_001B64F8, lib_allocation_get_identifier(allocation), slot);
            equipment->set_equipment_id(0, lib_allocation_get_identifier(allocation));
            break;
        case 1:
            func_40C7E0(D_001B64F8, equipment->get_equipment_id(1), 0);
            func_40C7E0(D_001B64F8, lib_allocation_get_identifier(allocation), slot);
            equipment->set_equipment_id(1, lib_allocation_get_identifier(allocation));
            break;
        case 2:
            func_40C7E0(D_001B64F8, equipment->get_equipment_id(unkc4), 0);
            func_40C7E0(D_001B64F8, lib_allocation_get_identifier(allocation), slot);
            equipment->set_equipment_id(unkc4, lib_allocation_get_identifier(allocation));
            break;
        }

        func_3F9890(character, equipment, 0, -1);
        resident_allocate_request(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
    }
    else
    {
        return 3;
    }

    static_cast<ItemAllocationWindow1847B0*>(func_slot44())->func_0034FB80(0);
    return 0;
}

ItemWindow1845B0::~ItemWindow1845B0()
{
    if (message_changed != 0)
    {
        ItemController* controller = static_cast<ItemController*>(D_001B643C->controller->selected);
        set_item_window_message(controller->unk48, controller->unkb4 + 0x1B6C);
    }
}

/**
 * @brief Create the party panels with names, portraits and stat-comparison labels, then show the item category hint.
 * @param associated Resource source word.
 * @return Zero when the selector could not be allocated, otherwise one.
 */
s32 ItemWindow1845B0::func_slotf4(u32 associated)
{
    s32 source = associated;
    ItemController* owner = static_cast<ItemController*>(D_001B643C->controller->selected);
    this->records = owner->selected_records();
    this->x = 12.0f;
    this->y = 216.0f;
    FieldClass15AE70::func_slot10(source, this->x, this->y, 15);
    this->selection = new (0) ItemCoordinateSelector;
    if (this->selection == 0)
    {
        return 0;
    }
    lib_moving_widget_init_position(this->selection, 0.0f, 0.0f);
    lib_container_attach_widget(this->unk10, this->selection);
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
        s8 slot = this->records->slots[index];
        if (slot > 0)
        {
            if (row < 3)
            {
                LibObject175140* label = new (0) LibObject175140;
                label->func_00467AD0(16.0f + panel_x, 10.0f + panel_y, 0.0f, 0.0f,
                    static_cast<ItemCharacterEquipment*>(this->records->unk04)[index].character_name, 0);
                lib_container_attach_widget(this->unk10, label);
                label->set_scale(0.8f, 0.8f);
            }
            this->indicators[row] = new (0) ItemCreationOptionResourceDisplay;
            u8 character = slot;
            void* resource = field_get_aligned_allocation(D_001B643C->buffers, character);
            FieldResourceRecord* record = field_find_resource_record(D_001B643C->buffers, 4);
            this->indicators[row]->unkcc = resource;
            this->indicators[row]->unkd0 = character;
            if (row < 3)
            {
                this->indicators[row]->func_002D6440(14.0f + panel_x, 48.0f + panel_y, record);
                ItemCreationOptionResourceDisplay* indicator = this->indicators[row];
                indicator->unk50.unk34 = 0.8f;
                indicator->unk50.unk30 = 0.8f;
                indicator->unk3c = 1;
            }
            else
            {
                this->indicators[row]->func_002D6440(14.0f + panel_x, 12.0f + panel_y, record);
                ItemCreationOptionResourceDisplay* indicator = this->indicators[row];
                indicator->unk50.unk34 = 0.65f;
                indicator->unk50.unk30 = 0.65f;
                indicator->unk3c = 1;
            }
            this->indicators[row]->unk34 = 3;
            this->indicators[row]->unk3f = 0;
            lib_container_attach_widget(this->unk10, this->indicators[row]);
            LibObject178750* first_label = new (0) LibObject178750;
            LibObject178750* second_label = new (0) LibObject178750;
            LibObject178750* third_label = new (0) LibObject178750;
            this->stat_values[row][0] = new (0) LibObject178750;
            this->stat_values[row][1] = new (0) LibObject178750;
            this->stat_values[row][2] = new (0) LibObject178750;
            if (row < 3)
            {
                first_label->init_resource_rectangle(text_x, text_y, 0.0f, 0.0f, source, 0x1B94, 0);
                second_label->init_resource_rectangle(text_x, 26.0f + text_y, 0.0f, 0.0f, source, 0x1B96, 0);
                third_label->init_resource_rectangle(text_x, 52.0f + text_y, 0.0f, 0.0f, source, 0x1B98, 0);
                first_label->set_scale(0.8f, 0.8f);
                second_label->set_scale(0.8f, 0.8f);
                third_label->set_scale(0.8f, 0.8f);
                this->stat_values[row][0]->init_resource_rectangle(45.0f + text_x, 1.0f + (text_y - 3.0f), 0.0f, 0.0f, source, 0x1B99, 0);
                this->stat_values[row][1]->init_resource_rectangle(45.0f + text_x, 2.0f + ((26.0f + text_y) - 3.0f), 0.0f, 0.0f, source, 0x1B9A, 0);
                this->stat_values[row][2]->init_resource_rectangle(45.0f + text_x, 4.0f + ((50.0f + text_y) - 3.0f), 0.0f, 0.0f, source, 0x1B9B, 0);
            }
            else
            {
                first_label->init_resource_rectangle(text_x, text_y, 0.0f, 0.0f, source, 0x1B94, 0);
                second_label->init_resource_rectangle(text_x, 19.0f + text_y, 0.0f, 0.0f, source, 0x1B96, 0);
                third_label->init_resource_rectangle(text_x, 38.0f + text_y, 0.0f, 0.0f, source, 0x1B98, 0);
                first_label->set_scale(0.68f, 0.68f);
                second_label->set_scale(0.68f, 0.68f);
                third_label->set_scale(0.68f, 0.68f);
                this->stat_values[row][0]->init_resource_rectangle(41.0f + text_x, text_y - 3.0f, 0.0f, 0.0f, source, 0x1B99, 0);
                this->stat_values[row][1]->init_resource_rectangle(41.0f + text_x, (19.0f + text_y) - 3.0f, 0.0f, 0.0f, source, 0x1B9A, 0);
                this->stat_values[row][2]->init_resource_rectangle(41.0f + text_x, (38.0f + text_y) - 3.0f, 0.0f, 0.0f, source, 0x1B9B, 0);
                this->stat_values[row][0]->set_scale(0.9f, 0.9f);
                this->stat_values[row][1]->set_scale(0.9f, 0.9f);
                this->stat_values[row][2]->set_scale(0.9f, 0.9f);
            }
            this->stat_values[row][0]->unk3f = 0;
            this->stat_values[row][1]->unk3f = 0;
            this->stat_values[row][2]->unk3f = 0;
            lib_container_attach_widget(this->unk10, first_label);
            lib_container_attach_widget(this->unk10, second_label);
            lib_container_attach_widget(this->unk10, third_label);
            lib_container_attach_widget(this->unk10, this->stat_values[row][0]);
            lib_container_attach_widget(this->unk10, this->stat_values[row][1]);
            lib_container_attach_widget(this->unk10, this->stat_values[row][2]);
        }
        else
        {
            LibObject178750* empty = new (0) LibObject178750;
            empty->init_resource_rectangle(16.0f + panel_x, 10.0f + panel_y, 0.0f, 0.0f, source, 0x1B8F, 0);
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
            append_selector_position(this->selection, 14.0f + panel_x, 88.0f + panel_y);
        }
        else
        {
            append_selector_position(this->selection, 14.0f + panel_x, 47.0f + panel_y);
        }
    }
    func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(this->selection), 0, 1);
    this->selection->unk3f = 0;
    this->unk10->LibClass174610::unkab = 0;
    ItemCreationAllocationRecord* allocation = owner->unkbc;
    if (allocation != 0)
    {
        if (static_cast<u8>(D_001B64F0[item_allocation_value(allocation)].category) == 0)
        {
            set_item_window_message(owner->unk48, 0x1B76);
            this->message_changed = 1;
        }
        if (static_cast<u8>(D_001B64F0[item_allocation_value(allocation)].category) == 1)
        {
            set_item_window_message(owner->unk48, 0x1B77);
            this->message_changed = 1;
        }
        if (static_cast<u8>(D_001B64F0[item_allocation_value(allocation)].category) == 2)
        {
            set_item_window_message(owner->unk48, 0x1B78);
            this->message_changed = 1;
        }
    }
    return 1;
}

extern "C"
{

Record0034C6A0* func_0034C6A0(Record0034C6A0* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = __vt__23ItemCreationClass175110;
        func_4618F0(&record->unk40, -1);
        func_4C48B0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

}

/** @brief Destroy the movement storage and intrusive widget base. */
inline ItemCreationClass175030::~ItemCreationClass175030()
{
}

FieldRecordSelection* ItemController::selected_records()
{
    return selection;
}

/** @brief Update the gauges and refresh each party member's HP, MP, status badges and name color. */
void ItemWindow1846B0::func_slot5c()
{
    for (ItemListNode* node = displays.head->next; node != 0; node = node->next)
    {
        static_cast<ItemHpMpGauge*>(node->value)->func_0044B100(1, 1, 1);
    }

    for (s32 row = 0; row < 8; ++row)
    {
        s16 index = row;
        if (records->slots[index] > 0)
        {
            ItemCharacterStats* entry = &reinterpret_cast<ItemCharacterStats*>(records->records)[index];
            func_3F9890(entry, &static_cast<ItemCharacterEquipment*>(records->unk04)[index], 0, -1);
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

void ItemWindow1846B0::func_slot70()
{
    ItemCoordinateSelector* selection = this->selection;
    s32 index;
    if (item_selection_control_is_clear(selection) != 0)
    {
        return;
    }
    index = selection->selected - 1;
    if (index < 0)
    {
        index = 7;
    }
    func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(selection), index, 0);
}

extern "C"
{

}

void ItemWindow1846B0::func_slot74()
{
    ItemCoordinateSelector* selection = this->selection;
    s32 index;
    if (item_selection_control_is_clear(selection) != 0)
    {
        return;
    }
    index = selection->selected + 1;
    if (index >= 8)
    {
        index = 0;
    }
    func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(selection), index, 0);
}

extern "C"
{

}

void ItemWindow1846B0::func_slot6c()
{
    ItemCoordinateSelector* selection = this->selection;
    s32 index;
    if (item_selection_control_is_clear(selection) != 0)
    {
        return;
    }
    switch (selection->selected)
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

extern "C"
{

}

void ItemWindow1846B0::func_slot68()
{
    ItemCoordinateSelector* selection = this->selection;
    s32 index;
    if (item_selection_control_is_clear(selection) != 0)
    {
        return;
    }
    switch (selection->selected)
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

extern "C"
{

}

u8 ItemWindow1846B0::func_slotb4()
{
    ItemCreationAllocationRecord* records[100];
    ItemController* controller = static_cast<ItemController*>(D_001B643C->controller->selected);
    if (lib_collect_unequipped_allocations(D_001B64F8, records, controller->category) == 0)
    {
        controller->remove_child(this);
        controller->remove_child(func_slot44());
        FieldClass15AE70* associated = static_cast<FieldClass15AE70*>(func_slot44());
        ItemListWindow1848D0* list = static_cast<ItemListWindow1848D0*>(associated->func_slot44());
        list->func_slot11c(0, -1);
        list->func_slot10c(1, 1);
        D_001B643C->controller->selected->func_00263C70(list);
    }
    else
    {
        controller->remove_child(this);
        ItemAllocationWindow1847B0* associated = static_cast<ItemAllocationWindow1847B0*>(func_slot44());
        associated->container->unkab = 1;
        controller->func_00263C70(associated);
    }
    return 2;
}

/**
 * @brief Use the selected item on the selected party member.
 * @return Three when nobody is selected or the item can't be used, otherwise zero.
 */
u8 ItemWindow1846B0::func_slotb0()
{
    ItemController* owner = static_cast<ItemController*>(D_001B643C->controller->selected);
    s32 selected = selection->selected;
    s8 slot = records->slots[static_cast<s16>(selected)];

    if (owner->unkbc != 0 && slot > 0)
    {
        switch (func_2E19D0(owner->unkbc, selected))
        {
        case -1:
        case 0:
            return 3;
        case 1:
            func_0040C9F0(D_001B64F8, lib_allocation_get_identifier(owner->unkbc));
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

    static_cast<ItemAllocationWindow1847B0*>(func_slot44())->func_0034FB80(0);
    return 0;
}

/**
 * @brief Create the party panels with names, HP and MP values, portraits, status badges, gauges and selector positions.
 * @param associated Resource source word.
 * @return Zero when the selector could not be allocated, otherwise one.
 */
s32 ItemWindow1846B0::func_slotf4(u32 associated)
{
    s32 source = associated;
    ItemController* owner = static_cast<ItemController*>(D_001B643C->controller->selected);
    this->records = owner->selected_records();
    this->x = 12.0f;
    this->y = 216.0f;
    FieldClass15AE70::func_slot10(source, this->x, this->y, 15);
    this->selection = new (0) ItemCoordinateSelector;
    if (this->selection == 0)
    {
        return 0;
    }
    lib_moving_widget_init_position(this->selection, 0.0f, 0.0f);
    lib_container_attach_widget(this->unk10, this->selection);
    this->row_height = 128.0f;
    for (s32 row = 0; row < 8; row++)
    {
        float indicator_x;
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
        s8 slot = this->records->slots[index];
        if (slot > 0)
        {
            if (row < 3)
            {
                this->labels[row] = new (0) LibObject175140;
                this->labels[row]->func_00467AD0(16.0f + panel_x, 10.0f + panel_y, 0.0f, 0.0f,
                    slot > 0 ? static_cast<ItemCharacterEquipment*>(this->records->unk04)[index].character_name : D_354C80, 0);
                lib_container_attach_widget(this->unk10, this->labels[row]);
                this->labels[row]->set_scale(0.8f, 0.8f);
                if (reinterpret_cast<ItemCharacterStats*>(this->records->records)[index].get_flags() & 5)
                {
                    this->labels[row]->set_color(0x505080);
                }
                else
                {
                    this->labels[row]->set_color(0x808080);
                }
            }
            this->hp_values[row] = new (0) LibObject174F20;
            if (row < 3)
            {
                // The original reuses the column width for the HP and MP row offsets.
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
            set_cost_value(this->hp_values[row], character_hp(&reinterpret_cast<ItemCharacterStats*>(this->records->records)[index]));
            lib_container_attach_widget(this->unk10, this->hp_values[row]);
            if (row < 3)
            {
                LibObject178750* separator = new (0) LibObject178750;
                separator->init_resource_rectangle(60.0f + value_x, hp_y, 0.0f, 0.0f, source, 0x1B93, 0);
                separator->set_scale(0.8f, 0.8f);
                lib_container_attach_widget(this->unk10, separator);
                this->max_hp_values[row] = new (0) LibObject174F20;
                lib_numeric_widget_init_rectangle(this->max_hp_values[row], 0, 1, 0, 61.0f + value_x, hp_y, value_width, value_height);
                this->max_hp_values[row]->set_scale(0.8f, 0.8f);
                set_cost_value(this->max_hp_values[row], character_max_hp(&reinterpret_cast<ItemCharacterStats*>(this->records->records)[index]));
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
            set_cost_value(this->mp_values[row], character_mp(&reinterpret_cast<ItemCharacterStats*>(this->records->records)[index]));
            lib_container_attach_widget(this->unk10, this->mp_values[row]);
            if (row < 3)
            {
                LibObject178750* separator = new (0) LibObject178750;
                separator->init_resource_rectangle(60.0f + value_x, column_width, 0.0f, 0.0f, source, 0x1B93, 0);
                separator->set_scale(0.8f, 0.8f);
                lib_container_attach_widget(this->unk10, separator);
                this->max_mp_values[row] = new (0) LibObject174F20;
                lib_numeric_widget_init_rectangle(this->max_mp_values[row], 1, 0, 0, 61.0f + value_x, column_width, value_width, 0.0f);
                this->max_mp_values[row]->set_scale(0.8f, 0.8f);
                set_cost_value(this->max_mp_values[row], character_max_mp(&reinterpret_cast<ItemCharacterStats*>(this->records->records)[index]));
                lib_container_attach_widget(this->unk10, this->max_mp_values[row]);
            }
            this->indicators[row] = new (0) ItemCreationOptionResourceDisplay;
            u8 character = slot;
            void* resource = field_get_aligned_allocation(D_001B643C->buffers, character);
            FieldResourceRecord* record = field_find_resource_record(D_001B643C->buffers, 4);
            this->indicators[row]->unkcc = resource;
            this->indicators[row]->unkd0 = character;
            if (row < 3)
            {
                indicator_x = 14.0f + panel_x;
                this->indicators[row]->func_002D6440(indicator_x, 48.0f + panel_y, record);
                ItemCreationOptionResourceDisplay* indicator = this->indicators[row];
                indicator->unk50.unk34 = 0.8f;
                indicator->unk50.unk30 = 0.8f;
                indicator->unk3c = 1;
            }
            else
            {
                indicator_x = 14.0f + panel_x;
                this->indicators[row]->func_002D6440(indicator_x, 12.0f + panel_y, record);
                ItemCreationOptionResourceDisplay* indicator = this->indicators[row];
                indicator->unk50.unk34 = 0.65f;
                indicator->unk50.unk30 = 0.65f;
                indicator->unk3c = 1;
            }
            lib_container_attach_widget(this->unk10, this->indicators[row]);
            resource = field_get_aligned_allocation(D_001B643C->buffers, 0);
            record = field_find_resource_record(D_001B643C->buffers, 40);
            this->badges[row][0] = new (0) ItemCreationOptionResourceDisplay;
            this->badges[row][0]->unkcc = resource;
            this->badges[row][0]->unkd0 = 0;
            ItemCreationOptionResourceDisplay* badge = this->badges[row][0];
            badge->unk50.unk34 = 0.8f;
            badge->unk50.unk30 = 0.8f;
            badge->unk3c = 1;
            this->badges[row][0]->func_002D6440(badge_x, badge_y, record);
            this->badges[row][0]->unk3f = 0;
            lib_container_attach_widget(this->unk10, this->badges[row][0]);
            record = field_find_resource_record(D_001B643C->buffers, 39);
            this->badges[row][1] = new (0) ItemCreationOptionResourceDisplay;
            this->badges[row][1]->unkcc = resource;
            this->badges[row][1]->unkd0 = 0;
            badge = this->badges[row][1];
            badge->unk50.unk34 = 0.8f;
            badge->unk50.unk30 = 0.8f;
            badge->unk3c = 1;
            if (row < 3)
            {
                this->badges[row][1]->func_002D6440(35.0f + badge_x, badge_y, record);
            }
            else
            {
                this->badges[row][1]->func_002D6440(25.0f + badge_x, badge_y, record);
            }
            this->badges[row][1]->unk3f = 0;
            lib_container_attach_widget(this->unk10, this->badges[row][1]);
            record = field_find_resource_record(D_001B643C->buffers, 38);
            this->badges[row][2] = new (0) ItemCreationOptionResourceDisplay;
            this->badges[row][2]->unkcc = resource;
            this->badges[row][2]->unkd0 = 0;
            badge = this->badges[row][2];
            badge->unk50.unk34 = 0.8f;
            badge->unk50.unk30 = 0.8f;
            badge->unk3c = 1;
            if (row < 3)
            {
                this->badges[row][2]->func_002D6440(70.0f + badge_x, badge_y, record);
            }
            else
            {
                this->badges[row][2]->func_002D6440(25.0f + badge_x, 30.0f + badge_y, record);
            }
            this->badges[row][2]->unk3f = 0;
            lib_container_attach_widget(this->unk10, this->badges[row][2]);
            resource = field_get_aligned_allocation(D_001B643C->buffers, (u8)(slot + 0x30));
            record = field_find_resource_record(D_001B643C->buffers, 4);
            this->badges[row][3] = new (0) ItemCreationOptionResourceDisplay;
            this->badges[row][3]->unkcc = resource;
            this->badges[row][3]->unkd0 = 0;
            if (row < 3)
            {
                this->badges[row][3]->func_002D6440(indicator_x, 48.0f + panel_y, record);
                badge = this->badges[row][3];
                badge->unk50.unk34 = 0.8f;
                badge->unk50.unk30 = 0.8f;
                badge->unk3c = 1;
            }
            else
            {
                this->badges[row][3]->func_002D6440(indicator_x, 12.0f + panel_y, record);
                badge = this->badges[row][3];
                badge->unk50.unk34 = 0.65f;
                badge->unk50.unk30 = 0.65f;
                badge->unk3c = 1;
            }
            this->badges[row][3]->unk3f = reinterpret_cast<ItemCharacterStats*>(this->records->records)[index].get_flags() & 5;
            lib_container_attach_widget(this->unk10, this->badges[row][3]);
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
            item_append_list_value(&this->displays, gauge);
            gauge->LibClass174610::unkab = 0;
        }
        else
        {
            LibObject178750* empty = new (0) LibObject178750;
            empty->init_resource_rectangle(16.0f + panel_x, 10.0f + panel_y, 0.0f, 0.0f, source, 0x1B8F, 0);
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
            append_selector_position(this->selection, 14.0f + panel_x, 88.0f + panel_y);
        }
        else
        {
            append_selector_position(this->selection, 14.0f + panel_x, 47.0f + panel_y);
        }
    }
    func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(this->selection), 0, 1);
    this->selection->unk3f = 0;
    this->unk10->LibClass174610::unkab = 0;
    for (ItemListNode* node = this->displays.head->next; node != 0; node = node->next)
    {
        static_cast<LibClass174610*>(node->value)->unkab = 0;
    }
    if (owner->unkbc != 0)
    {
        set_item_window_message(owner->unk48, 0x1B7A);
        this->message_changed = 1;
    }
    return 1;
}

void ItemWindow1846B0::func_slot0c()
{
    for (ItemListNode* node = this->displays.head->next; node != 0; node = node->next)
    {
        static_cast<LibClass171EA0*>(node->value)->func_003EF740();
    }

    FieldClass15AE70::func_slot0c();
}

void ItemHpMpGauge::func_003EF740()
{
    queued_for_release = 1;
    func_0044B210(this);
    resident_enqueue_object(D_001B65F4, this);
}

ItemWindow1846B0::~ItemWindow1846B0()
{
    if (message_changed != 0)
    {
        ItemController* controller = static_cast<ItemController*>(D_001B643C->controller->selected);
        set_item_window_message(controller->unk48, controller->unkb4 + 0x1B6C);
    }
}

extern "C"
{

}

u8 ItemAllocationWindow1847B0::func_slotb0()
{
    if (unk1b0 != 0)
    {
        return 0;
    }

    ItemCreationAllocationRecord* records[99];
    ItemController* owner = static_cast<ItemController*>(D_001B643C->controller->selected);
    s32 count = lib_collect_unequipped_allocations(D_001B64F8, records, (u16)owner->category);
    s32 selected = unk24;
    if (count != 0 && selected >= 0)
    {
        u16 identifier = records[0]->definition_index();
        switch ((u8)D_001B64F0[identifier].category)
        {
        case 0:
        case 1:
        case 2:
        {
            ItemWindow1845B0* window = new (0) ItemWindow1845B0;
            window->func_slotf4(owner->get_resource_slot());
            window->func_slot40(this);
            window->selection->unk3f = 1;
            window->unk10->unkab = 1;
            owner->add_child(window);
            owner->func_00263C70(window);
            container->unkab = 0;
            break;
        }
        case 3:
        case 4:
        case 5:
        case 6:
        {
            u16 identifier = records[selected]->definition_index();
            if (((u8)D_001B64F0[identifier].unk13_high & 1) == 0)
            {
                return 3;
            }
            ItemWindow1846B0* window = new (0) ItemWindow1846B0;
            window->func_slotf4(owner->get_resource_slot());
            window->func_slot40(this);
            window->selection->unk3f = 1;
            window->unk10->unkab = 1;
            for (ItemListNode* node = window->displays.head->next; node != 0; node = node->next)
            {
                static_cast<LibClass174610*>(node->value)->unkab = 1;
            }
            owner->add_child(window);
            owner->func_00263C70(window);
            container->unkab = 0;
            break;
        }
        }
    }
    return 1;
}

/** @brief Update the list input, the selected allocation's detail codes and marker, and the model preview state. */
void ItemAllocationWindow1847B0::func_slot5c()
{
    if (D_001B643C->controller->selected->func_00261150() == this && unk1b0 == 0)
    {
        FieldClass15AD40::func_slot5c();
    }
    else if (unk1b0 == 0)
    {
        func_2CDFB0(&static_cast<FieldStateCE420&>(*this));
    }

    if (D_001B643C->controller->selected->func_00261150() == this)
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

    ItemController* owner = static_cast<ItemController*>(D_001B643C->controller->selected);
    ItemCreationAllocationRecord* records[99];

    u32 category = owner->category;

    if (owner->unkb4 != 7)
    {
        s32 count = lib_collect_unequipped_allocations(D_001B64F8, records, static_cast<u16>(category));
        s32 selected = unk24;

        if (count != 0 && selected >= 0)
        {
            s32 shown = 0;

            for (s32 index = 0; index < 8; index++)
            {
                u16 value = func_0040D930(records[selected], index);

                if (value != 0 && value != 700)
                {
                    LibObject172440* detail = details[shown];
                    detail->unkfc = value;
                    detail->unk3c = 1;
                    details[shown]->unk3f = 1;
                    shown++;
                }
            }

            for (; shown < 8; shown++)
            {
                details[shown]->unk3f = 0;
            }

            LibObject172410* marked = first[unk28];
            set_selection_marker(marked, marked->unk94);
            u8 modification;
            ItemCreationAllocationRecord* record = records[selected];
            modification = record->modification_number;
            u16 identifier = record->definition_index();
            LibObject172410* code = selected_code;
            code->unkfc = identifier + 1;
            code->unkfe = modification;
            code->unk3c = 1;
            owner->unkbc = records[selected];
        }
        else
        {
            for (s32 index = 0; index < 8; index++)
            {
                details[index]->unk3f = 0;
            }

            set_selection_marker(0, 0x808080);
            owner->unkbc = 0;
        }
    }
    else
    {
        owner->unkbc = 0;
    }

    for (s32 index = 0; index < 6; index++)
    {
        first[index]->unk3f = 0;
        second[index]->unk3f = 0;
    }

    if (unk1b0 != 0)
    {
        text19c->unk3f = 1;
        selected_code->unk3f = 1;
        text1a4->unk3f = 1;
        text1a8->unk3f = 1;

        if (owner->unkb4 == 7)
        {
            selected_code->unk3f = 0;
        }

        FieldStateCE420::unk04->unk3f = 0;
        FieldStateCE420::unk00->unk3f = 0;
        ItemCreationClass172870* marker = display170;
        marker->unk18.unk04 = 66.0f;
        marker->unk3c = 1;
        set_selection_marker(0, 0x808080);

        if (unk1bc != 0 && func_002FD480(unk1b8) != 0)
        {
            unk1b0 = 0;
            unk1bc = 0;
            text178->unk3f = 1;
            lib_text_set_resource(text178, owner->get_resource_slot(), 0x1B9D, 0);
            LibObject178750* text = text17c;
            text->unk18.unk00 = 448.0f;
            text->unk18.unk04 = 330.0f;
            text->unk3c = 1;
            lib_text_set_resource(text17c, owner->get_resource_slot(), 0x1B9E, 0);

            if (unk1b8 != 0)
            {
                unk1b8->func_001DD7B0();
                unk1b8 = 0;
            }

            if (owner->unkb4 == 7)
            {
                field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->controller), this);
                ItemListWindow1848D0* list = static_cast<ItemListWindow1848D0*>(func_slot44());
                list->func_slot11c(0, -1);
                list->func_slot10c(1, 1);
                D_001B643C->controller->selected->func_00263C70(list);
                unk1b0 = 1;
            }
        }
    }
    else
    {
        text19c->unk3f = 0;
        selected_code->unk3f = 0;
        text1a4->unk3f = 0;
        text1a8->unk3f = 0;

        for (s32 index = 0; index < 6; index++)
        {
            first[index]->unk3f = 1;
            second[index]->unk3f = 1;
        }

        FieldStateCE420::unk04->unk3f = 1;
        FieldStateCE420::unk00->unk3f = 1;
        ItemCreationClass172870* marker = display170;
        marker->unk18.unk04 = 160.0f;
        marker->unk3c = 1;
    }
}

/** @brief Destroy the list receiver and its head node. */
LibClass178A70::~LibClass178A70()
{
}

/**
 * @brief Rebuild the item-type list for a category and reset the visible rows and selection.
 * @param reset Nonzero to move the selection back to the first row.
 * @param category Category to list, or -1 for the controller's current category.
 */
void ItemListWindow1848D0::func_slot11c(s32 reset, s32 category)
{
    func_00354400(&entries);

    for (s32 index = 0; index < 24; index++)
    {
        unk1b8[index] = 0;
    }

    unk88 = 0;

    category = category == -1 ? controller->unkb4 : category;

    FieldClass15AE60::unk8c = category;

    switch (category)
    {
    case 7:
        unk88 = controller->entry_count;
        break;
    case 8:
        ItemCreationCategoryRecord* entry = D_001B64F8->item_types;

        for (s32 index = 0; index < 750; index++, entry++)
        {

            if ((static_cast<u8>(D_001B64F0[entry->catalog_index].unk13_high) & 2) && entry->inventory_count > 0)
            {
                func_00354370(reinterpret_cast<ItemListOwner*>(&entries), entry);
                unk88++;
            }
        }
        break;
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        for (s32 index = 1; index <= 750; index++)
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
                        unk1b8[identifier / 32] |= 1 << (identifier % 32);
                        break;
                    }
                }

                func_00354370(reinterpret_cast<ItemListOwner*>(&entries), entry);
                unk88++;
            }
        }
        break;
    case 9:
        for (s32 index = 1; index <= 750; index++)
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
                    unk1b8[identifier / 32] |= 1 << (identifier % 32);
                    func_00354370(reinterpret_cast<ItemListOwner*>(&entries), entry);
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
        func_00354980(&entries, func_00351E40, 0, 1);
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

/** @brief Initialize the row pointers and controller link. @param owner Parent item controller. */
ItemListWindow1848D0::ItemListWindow1848D0(ItemController* owner)
{
    for (s32 index = 0; index < 14; index++)
    {
        unk48[index] = 0;
        second[index] = 0;
        third[index] = 0;
    }

    // TODO: The only way I found to get the original's two stores is to clear the link before setting it.
    controller = 0;
    controller = owner;
    sort_enabled = 0;
    FieldClass15AD40();
}

extern "C"
{

s32 func_00351E40(const ItemListNode* left, const ItemListNode* right, u32 comparison_arg)
{
    const ItemSortRecord* first = (const ItemSortRecord*)left->value;
    const ItemSortRecord* second = (const ItemSortRecord*)right->value;
    const ItemSortDefinition* first_definition = &D_001B64F0[first->table_index];
    const ItemSortDefinition* second_definition = &D_001B64F0[second->table_index];
    return first_definition->sort_order - second_definition->sort_order;
}

}

s32 ItemAllocationWindow1847B0::func_slot104(u32 associated)
{
    FieldClass15AE70::func_slot14(associated, 0, 9, 2400, 20.0f, 83.0f, 0.0f);
    FieldClass15AE60::unk3c = 1;
    container = new (0) LibObject178660;
    lib_container_init(container, 14, 20.0f, 83.0f, 0, 0.0f, 0);
    lib_queue_display_object(D_001B657C, container);
    LibClass1746A0* clip = new (0) LibClass1746A0;
    LibClass1746A0* reset = new (0) LibClass1746A0;
    panel = new (0) LibClass178630;
    lib_panel_init_rectangle(panel, 1, 0.0f, 0.0f, 590.0f, 370.0f, 88.0f);
    lib_container_attach_widget(FieldClass15AE70::unk10, panel);
    lib_panel_init_transform(panel, 1500.0f);
    lib_scissor_init_rectangle(clip, 16.0f, 16.0f, 600.0f, 140.0f);
    lib_container_attach_widget(FieldClass15AE70::unk10, clip);
    void* allocation = field_get_aligned_allocation(D_001B643C->buffers, 14);

    for (s32 index = 0; index < 6; index++)
    {
        FieldResourceRecord* record = field_find_resource_record(D_001B643C->buffers, 60);
        second[index] = new (0) ItemCreationOptionResourceDisplay;
        second[index]->unkcc = allocation;
        second[index]->unkd0 = 14;
        float y = 16.0f + 28.0f * static_cast<float>(index);
        second[index]->func_002D6440(30.0f, y, record);
        ItemCreationOptionResourceDisplay* resource = second[index];
        resource->unk50.unk34 = 0.95f;
        resource->unk50.unk30 = 0.95f;
        resource->unk3c = 1;
        second[index]->unk3d = 0;
        lib_container_attach_widget(FieldClass15AE70::unk10, second[index]);
        first[index] = new (0) LibObject172410;
        lib_item_code_init_rectangle(first[index], 60.0f, y, 323.99997f, 21.599998f, 100, 0, 0);
        first[index]->set_scale(0.9f, 0.9f);
        LibObject172410* text = first[index];
        text->unkfa = 1;
        text->unk3c = 1;
        text = first[index];
        text->unk88 = -1.0f;
        text->unk3c = 1;
        first[index]->unk3d = 0;
        lib_container_attach_widget(FieldClass15AE70::unk10, first[index]);
    }

    lib_scissor_init_reset(reset, 1);
    lib_container_attach_widget(FieldClass15AE70::unk10, reset);
    display170 = new (0) ItemCreationClass172870;
    lib_marker_init_rectangle(display170, 24.0f, 160.0f, 550.0f, 4.0f);
    ItemCreationClass172870* marker = display170;
    marker->unk50 = 0xDC6464;
    marker->unk3c = 1;
    lib_container_attach_widget(FieldClass15AE70::unk10, display170);
    FieldRuntime* runtime = D_001B657C;
    runtime->detail_resource_slot = associated;
    runtime->detail_base_key = 70001;
    s32 index;

    for (index = 0; index < 8; index++)
    {
        details[index] = new (0) LibObject172440;
        lib_detail_code_init_rectangle(details[index], 0, 1, 0, 24.0f, static_cast<float>(175 + 22 * index), 0.0f, 0.0f);
        LibObject172440* text = details[index];
        text->unk80 = 0.8f;
        text->unk84 = 0.8f;
        text->unk3c = 1;
        details[index]->unk3f = 0;
        lib_container_attach_widget(container, details[index]);
    }

    ItemController* owner = static_cast<ItemController*>(D_001B643C->controller->selected);
    text19c = new (0) LibObject178750;
    text19c->init_resource_rectangle(16.0f, 12.0f, 0.0f, 0.0f, associated, owner->unkb4 + 0x1B62, 0);
    LibObject178750* text = text19c;
    text->unk88 = -1.0f;
    text->unk3c = 1;
    text19c->set_scale(0.8f, 0.8f);
    text19c->set_color(0x805050);
    text19c->unk3f = 0;
    lib_container_attach_widget(FieldClass15AE70::unk10, text19c);
    selected_code = new (0) LibObject172410;
    lib_item_code_init_rectangle(selected_code, 24.0f, 34.0f, 561.6f, 31.199999f, 0, 0, 0);
    LibObject172410* code = selected_code;
    code->unkfc = owner->category;
    code->unkfe = 0;
    code->unk3c = 1;
    selected_code->set_scale(1.3f, 1.3f);
    selected_code->unk3f = 0;
    lib_container_attach_widget(FieldClass15AE70::unk10, selected_code);

    if (owner->unkb4 == 7)
    {
        LibObject178750* name = new (0) LibObject178750;
        name->init_resource_rectangle(24.0f, 34.0f, 0.0f, 0.0f, associated, owner->category + 75001, 0);
        name->set_scale(1.3f, 1.3f);
        lib_container_attach_widget(FieldClass15AE70::unk10, name);
        text1a4 = new (0) LibObject178750;
        text1a4->init_resource_rectangle(24.0f, 78.0f, 534.0f, 66.0f, associated, owner->category + 76001, 0);
    }
    else
    {
        text1a4 = new (0) LibObject178750;
        text1a4->init_resource_rectangle(24.0f, 78.0f, 534.0f, 66.0f, associated, owner->category + 55000, 0);
    }

    text1a4->set_mode(0);
    text1a4->set_vertical_alignment(1);
    text = text1a4;
    text->unk88 = -1.0f;
    text->unk3c = 1;
    text1a4->set_scale(0.9f, 0.9f);
    text1a4->unk3f = 0;
    lib_container_attach_widget(container, text1a4);
    text1a8 = new (0) LibObject178750;
    text1a8->init_resource_rectangle(16.0f, 150.0f, 0.0f, 0.0f, associated, 0x1B8C, 0);
    text1a8->set_scale(0.8f, 0.8f);
    text1a8->set_color(0x805050);
    text = text1a8;
    text->unk88 = -1.0f;
    text->unk3c = 1;
    text1a8->unk3f = 0;
    lib_container_attach_widget(FieldClass15AE70::unk10, text1a8);
    text178 = new (0) LibObject178750;
    text178->init_resource_rectangle(400.0f, 295.0f, 0.0f, 0.0f, associated, 0x1B9D, 1);
    lib_container_attach_widget(container, text178);
    text17c = new (0) LibObject178750;
    text17c->init_resource_rectangle(448.0f, 330.0f, 0.0f, 0.0f, associated, 0x1B9E, 1);
    lib_container_attach_widget(container, text17c);
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
    func_0034FB80(1);
    return 1;
}

void ItemAllocationWindow1847B0::func_0034FB80(s32 reset)
{
    unk88 = 0;
    ItemController* owner = static_cast<ItemController*>(D_001B643C->controller->selected);

    u32 category = owner->category;

    if (owner->unkb4 == 7)
    {
        s32 key = D_354CE0[static_cast<u16>(category)] + 0x88;

        if (unk1b8 == 0)
        {
            unk1b8 = new (0) FieldClass15BB90;
            field_request_model_resource(unk1b8, key);
            unk1b8->unk5b = 1;
            field_replace_model_camera(unk1b8, D_001B643C->field_camera);
            field_attach_model_display(unk1b8);

            if (reinterpret_cast<CitemDisplaySettings*>(resident_find_entry(resident_get_entry_table(resident_get_runtime_owner()), 1))->widescreen != 0)
            {
                func_002FD1B0(reinterpret_cast<FieldFloatState5C*>(unk1b8), 0.5235988f, 600.0f, 0.34906584f, 120.0f, 35.0f);
            }
            else
            {
                func_002FD1B0(reinterpret_cast<FieldFloatState5C*>(unk1b8), 0.5235988f, 500.0f, 0.34906584f, 90.0f, 50.0f);
            }

            D_001B6614->append_node(unk1b8, -1);
        }

        unk1b0 = 1;
        text178->unk3f = 0;
        lib_text_set_resource(text178, owner->get_resource_slot(), 0x1B9D, 0);
        LibObject178750* display = text17c;
        display->unk18.unk00 = 518.0f;
        display->unk3c = 1;
        lib_text_set_resource(text17c, owner->get_resource_slot(), 0x1BA0, 0);
        selected_code->unk3f = 0;
        FieldStateCE420::unk04->unk3d = 0;
        FieldStateCE420::unk00->unk3d = 0;
        LibClass178600* marker = display170;
        marker->unk18.unk04 = 66.0f;
        marker->unk3c = 1;
    }
    else
    {
        ItemCreationAllocationRecord* records[99];
        unk88 = lib_collect_unequipped_allocations(D_001B64F8, records, static_cast<u16>(category));
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

u8 ItemChoiceWindow184280::func_slotb4()
{
    if (func_slot28())
    {
        return 0;
    }

    ItemController* owner = static_cast<ItemController*>(D_001B643C->controller->selected);
    owner->remove_child(this);
    ItemAllocationWindow1847B0* window = static_cast<ItemAllocationWindow1847B0*>(func_slot44());
    window->container->unkab = 1;
    owner->func_00263C70(window);
    return 2;
}

u8 ItemChoiceWindow184280::func_slotb0()
{
    if (func_slot28())
    {
        return 0;
    }

    if (grid != 0 && grid->unk114 != 0)
    {
        return func_slotb4();
    }

    ItemController* owner = static_cast<ItemController*>(D_001B643C->controller->selected);
    func_0040C9F0(D_001B64F8, lib_allocation_get_identifier(owner->unkbc));
    ItemCreationAllocationRecord* records[99];
    u16 identifier = owner->unkbc->definition_index();

    if (lib_collect_unequipped_allocations(D_001B64F8, records, identifier + 1) == 0)
    {
        owner->remove_child(this);
        owner->remove_child(func_slot44());
        ItemListWindow1848D0* list = static_cast<ItemListWindow1848D0*>(static_cast<ItemAllocationWindow1847B0*>(func_slot44())->func_slot44());
        list->func_slot11c(0, -1);
        list->func_slot10c(1, 1);
        D_001B643C->controller->selected->func_00263C70(list);
    }
    else
    {
        owner->remove_child(this);
        ItemAllocationWindow1847B0* window = static_cast<ItemAllocationWindow1847B0*>(func_slot44());
        window->container->unkab = 1;
        window->func_0034FB80(0);
        owner->func_00263C70(window);
    }

    return 1;
}

ItemChoiceWindow184280::~ItemChoiceWindow184280()
{
}

void ItemChoiceWindow184280::func_slot5c()
{
    void* active = D_001B643C->controller->selected->func_00261150();
    func_0023CEA0(this->grid, active == this);
    D_001B643C->controller->selected->func_00261150();
}

s32 ItemChoiceWindow184280::func_slotf4(u32 associated)
{
    LibClass178630* panel;
    LibObject178750* text;
    FieldObject23CEA0* grid;
    LibWidgetColors4C5590 colors;
    FieldClass15AE70::func_slot10(associated, 145.0f, 170.0f, 13);
    panel = allocate_panel();
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 350.0f, 176.0f, 88.0f);
    lib_container_attach_widget((LibObject178660*)this->unk10, (LibClass178600*)panel);
    func_003546B0(reinterpret_cast<ItemListOwner*>(&unk14), panel);
    panel = allocate_panel();
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 350.0f, 48.0f, 88.0f);
    lib_container_attach_widget((LibObject178660*)this->unk10, (LibClass178600*)panel);
    colors = D_354C40;
    lib_panel_set_colors(panel, &colors);
    func_003546B0(reinterpret_cast<ItemListOwner*>(&unk14), panel);
    text = allocate_text_widget();
    text->init_resource_rectangle(0.0f, 12.0f, 350.0f, 48.0f, associated, 0x1BA1, 0);
    set_text_mode(text, 1);
    lib_container_attach_widget((LibObject178660*)this->unk10, (LibClass178600*)text);
    text = allocate_text_widget();
    text->init_resource_rectangle(0.0f, 64.0f, 350.0f, 64.0f, associated, 0x1BA2, 0);
    set_text_mode(text, 1);
    lib_container_attach_widget((LibObject178660*)this->unk10, (LibClass178600*)text);
    this->first_text = allocate_text_widget();
    this->second_text = allocate_text_widget();
    this->first_text->init_resource_rectangle(122.0f, 132.0f, 0.0f, 0.0f, associated, 0x1BA3, 0);
    lib_container_attach_widget((LibObject178660*)this->unk10, (LibClass178600*)this->first_text);
    this->second_text->init_resource_rectangle(212.0f, 132.0f, 0.0f, 0.0f, associated, 0x1BA4, 0);
    lib_container_attach_widget((LibObject178660*)this->unk10, (LibClass178600*)this->second_text);
    grid = new (0) FieldObject23CEA0;
    this->grid = grid;
    func_0023CE80((FieldObject23CE80*)this->grid, 2, 1);
    func_0023CE60((FieldObject23CE80*)this->grid, 80.0f, 0.0f);
    this->grid->unkF2 = 0;
    func_0023CF50((FieldObject23CEB0*)this->grid, 1, 265.0f, 302.0f);
    this->grid->unkad = 0;
    func_003544C0(reinterpret_cast<ItemListOwner*>(&unk74), this->grid);

    if (this->grid->unk114 != 0)
    {
        set_text_color(this->first_text, 0x808080);
        set_text_color(this->second_text, 0x288080);
    }
    else
    {
        set_text_color(this->first_text, 0x288080);
        set_text_color(this->second_text, 0x808080);
    }

    return 1;
}

u8 ItemAllocationWindow1847B0::func_slotbc()
{
    if (unk1b0 != 0)
    {
        return 0;
    }

    ItemCreationAllocationRecord* records[99];
    ItemController* owner = static_cast<ItemController*>(D_001B643C->controller->selected);
    s32 count = lib_collect_unequipped_allocations(D_001B64F8, records, (u16)owner->category);
    s32 selected = unk24;

    if (count != 0 && selected >= 0)
    {
        ItemCreationAllocationRecord* allocation = records[selected];
        u16 identifier = allocation->definition_index();

        if (item_definition_unsellable(&D_001B64F0[identifier]) == 0)
        {
            ItemChoiceWindow184280* window = new (0) ItemChoiceWindow184280;
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

ItemAllocationWindow1847B0::~ItemAllocationWindow1847B0()
{
    if (panel != 0)
    {
        lib_panel_detach(panel);
    }
}

void ItemAllocationWindow1847B0::func_slot0c()
{
    container->func_003EF740();
    FieldClass15AE70::func_slot0c();
}

void ItemAllocationWindow1847B0::func_slot6c()
{
    if (this->unk1b0 != 0)
    {
        FieldClass15BB90* angle = this->unk1b8;
        if (angle != 0)
        {
            float value = angle->values[2];
            value -= ANGLE_STEP_RADIANS;
            if (value < 0.0f)
            {
                value = 0.0f;
            }
            angle->values[2] = value;
        }
    }
}

void ItemAllocationWindow1847B0::func_slot68()
{
    if (this->unk1b0 != 0)
    {
        FieldClass15BB90* angle = this->unk1b8;
        if (angle != 0)
        {
            float value = angle->values[2];
            value += ANGLE_STEP_RADIANS;
            if (value > ANGLE_LIMIT_RADIANS)
            {
                value = ANGLE_LIMIT_RADIANS;
            }
            angle->values[2] = value;
        }
    }
}

void ItemAllocationWindow1847B0::func_slot10c(u32 value, u32 alternate)
{
    first[0]->unk3f = value;
    second[0]->unk3f = value;
    first[1]->unk3f = value;
    second[1]->unk3f = value;
    first[2]->unk3f = value;
    second[2]->unk3f = value;
    first[3]->unk3f = value;
    second[3]->unk3f = value;
    first[4]->unk3f = value;
    second[4]->unk3f = value;
    first[5]->unk3f = value;
    second[5]->unk3f = value;
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

void ItemAllocationWindow1847B0::set_scroll_position(float offset)
{
    ItemController* controller = static_cast<ItemController*>(D_001B643C->controller->selected);

    if (controller->unkb4 != 7)
    {
        float y = 16.0f + offset;

        s32 row = 0;

        do
        {
            LibClass178600* screen = first[row];
            screen->unk18.unk04 = y;
            screen->unk3c = 1;
            screen = second[row];
            screen->unk18.unk04 = y;
            screen->unk3c = 1;
            y += 28.0f;
            row++;
        } while (row < 6);
    }
}

void ItemAllocationWindow1847B0::refresh_rows(s32 first_index)
{
    ItemCreationAllocationRecord* records[99];
    ItemController* selected = static_cast<ItemController*>(D_001B643C->controller->selected);
    if (selected->unkb4 != 7)
    {
        u32 category = selected->category;
        s32 index;
        func_0013A678(records, 0, sizeof(records));
        unk88 = lib_collect_unequipped_allocations(D_001B64F8, records, (u16)category);
        for (index = 0; index < 6; index++)
        {
            if (records[first_index + index] != 0)
            {
                LibObject172410* display = first[index];
                u8 value_byte = records[first_index + index]->modification_number;
                s32 count = 0;
                s32 detail;
                void* allocation;
                FieldResourceRecord* record;
                display->unkfc = category;
                display->unkfe = value_byte;
                display->unk3c = 1;
                for (detail = 0; detail < 8; detail++)
                {
                    u16 value = func_0040D930(records[first_index + index], detail);
                    if (value != 0 && value != 700)
                    {
                        count++;
                    }
                }
                allocation = field_get_aligned_allocation(D_001B643C->buffers, 14);
                record = field_find_resource_record(D_001B643C->buffers, count + 60);
                func_002D5CF0((ItemCreationOptionResourceDisplay*)second[index], allocation, record, 14);
                first[index]->unk3d = 1;
                second[index]->unk3d = 1;
            }
            else
            {
                first[index]->unk3d = 0;
                second[index]->unk3d = 0;
            }
        }
    }
}

u8 ItemAllocationWindow1847B0::func_slotb8()
{
    ItemController* owner = static_cast<ItemController*>(D_001B643C->controller->selected);

    if (owner->unkb4 == 7)
    {
        return 0;
    }

    if (unk1b0 != 0)
    {
        field_cancel_model_request(unk1b8);
        unk1bc = 1;
        resident_allocate_request(D_001B65F8, 2, 0, 0, 0x7F, 0x40, 0);
    }
    else
    {
        ItemCreationAllocationRecord* records[99];
        s32 count = lib_collect_unequipped_allocations(D_001B64F8, records, (u16)owner->category);
        s32 selected = unk24;

        if (count != 0 && selected >= 0)
        {
            u16 identifier = records[selected]->definition_index();
            s32 key = (u16)D_001B64F0[identifier].model_index + 0x88;

            if (unk1b8 == 0)
            {
                unk1b8 = new (0) FieldClass15BB90;
                field_request_model_resource(unk1b8, key);
                unk1b8->unk5b = 1;
                field_replace_model_camera(unk1b8, D_001B643C->field_camera);
                field_attach_model_display(unk1b8);

                if (reinterpret_cast<CitemDisplaySettings*>(resident_find_entry(resident_get_entry_table(resident_get_runtime_owner()), 1))->widescreen != 0)
                {
                    func_002FD1B0(reinterpret_cast<FieldFloatState5C*>(unk1b8), 0.5235988f, 600.0f, 0.34906584f, 120.0f, 35.0f);
                }
                else
                {
                    func_002FD1B0(reinterpret_cast<FieldFloatState5C*>(unk1b8), 0.5235988f, 500.0f, 0.34906584f, 90.0f, 50.0f);
                }

                D_001B6614->append_node(unk1b8, -1);
            }

            unk1b0 = 1;
            text178->unk3f = 0;
            lib_text_set_resource(text178, owner->get_resource_slot(), 0x1B9D, 0);
            LibObject178750* text = text17c;
            text->unk18.unk00 = 425.0f;
            text->unk18.unk04 = 337.0f;
            text->unk3c = 1;
            lib_text_set_resource(text17c, owner->get_resource_slot(), 0x1B9F, 0);
            resident_allocate_request(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
        }
    }

    return 0;
}

u8 ItemAllocationWindow1847B0::func_slotb4()
{
    if (unk1b0 != 0)
    {
        if (unk1b8 != 0)
        {
            field_cancel_model_request(unk1b8);
            unk1bc = 1;
        }
        return 2;
    }
    ItemController* owner = static_cast<ItemController*>(D_001B643C->controller->selected);
    owner->remove_child(this);
    ItemListWindow1848D0* list = static_cast<ItemListWindow1848D0*>(func_slot44());
    list->func_slot11c(0, -1);
    list->func_slot10c(1, 1);
    D_001B643C->controller->selected->func_00263C70(list);
    return 2;
}

u8 ItemListWindow1848D0::func_slotb0()
{
    if (unk88 == 0)
    {
        return 3;
    }
    if (controller == 0)
    {
        return 0;
    }
    ItemAllocationWindow1847B0* window = new (0) ItemAllocationWindow1847B0;
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
    if (controller->unkb4 == 7)
    {
        resident_allocate_request(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
        return 0;
    }
    return 1;
}

s32 ItemListWindow1848D0::func_slot104(u32 associated)
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
        second[index] = new (0) LibObject178750;
        third[index] = new (0) LibObject174F20;
        float y = 16.0f + 28.0f * (float)index;
        reinterpret_cast<LibObject178750*>(unk48[index])->init_resource_rectangle(22.0f, y, 0.0f, 0.0f, associated, CITEM_MSG_ITEM_NAMES, 0);
        reinterpret_cast<LibObject178750*>(second[index])->init_resource_rectangle(326.0f, y - 4.0f, 0.0f, 0.0f, associated, 0x7E4, 1);
        lib_numeric_widget_init_rectangle(static_cast<LibObject174F20*>(third[index]), index, associated, 1, 334.0f, y, 28.0f, 24.0f);
        {
            LibClass174EF0* text = static_cast<LibClass174EF0*>(unk48[index]);
            text->unk88 = -1.0f;
            text->unk3c = 1;
        }
        static_cast<LibClass174EF0*>(unk48[index])->set_scale(0.9f, 0.9f);
        lib_container_attach_widget(FieldClass15AE70::unk10, unk48[index]);
        lib_container_attach_widget(FieldClass15AE70::unk10, second[index]);
        lib_container_attach_widget(FieldClass15AE70::unk10, third[index]);
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
    func_slot11c(1, 0);
    return 1;
}

void ItemCreationClass185050::func_slot0c()
{
}

void ItemListWindow1848D0::func_slot5c()
{
    if (D_001B643C->controller->selected->func_00261150() == this)
    {
        FieldClass15AD40::func_slot5c();
        if (FieldClass15AE60::unk8c == 7)
        {
            s16 selected = unk24;
            if (selected >= 0)
            {
                ItemController* owner = controller;
                s32 entry;
                if (selected >= owner->entry_count)
                {
                    entry = -1;
                }
                else
                {
                    entry = owner->entries[selected];
                }
                owner->category = entry;
            }
        }
        else
        {
            ItemListNode* node = func_00354480(reinterpret_cast<ItemListOwner*>(&entries), unk24);
            if (node != 0)
            {
                ItemSortRecord* record = static_cast<ItemSortRecord*>(node->value);
                controller->category = (u16)(record->table_index + 1);
            }
        }
        if (unk24 >= 0 && unk88 != 0)
        {
            LibClass174EF0* display = static_cast<LibClass174EF0*>(unk48[unk28]);
            set_selection_marker(display, display->unk94);
        }
        else
        {
            set_selection_marker(0, 0x808080);
        }
    }
    else
    {
        set_selection_marker(0, 0x808080);
    }
}

void ItemListWindow1848D0::refresh_rows(s32 start)
{
    if (controller != 0)
    {
        if (FieldClass15AE60::unk8c == 7)
        {
            for (s32 index = 0; index < 14; index++)
            {
                s32 entry;
                if (index + start >= controller->entry_count)
                {
                    entry = -1;
                }
                else
                {
                    entry = controller->entries[start + index];
                }
                if (entry >= 0)
                {
                    lib_text_set_resource(reinterpret_cast<LibObject178750*>(unk48[index]), func_slot54(), entry + 0x124F9, 0);
                    static_cast<LibClass174EF0*>(unk48[index])->set_color(0x808080);
                    LibObject174F20* numeric = static_cast<LibObject174F20*>(third[index]);
                    numeric->numeric_value = 1;
                    numeric->unk3c = 1;
                    unk48[index]->unk3d = 1;
                    third[index]->unk3d = 1;
                    second[index]->unk3d = 1;
                }
                else
                {
                    unk48[index]->unk3d = 0;
                    third[index]->unk3d = 0;
                    second[index]->unk3d = 0;
                }
            }
        }
        else
        {
            ItemListNode* node = func_00354480(reinterpret_cast<ItemListOwner*>(&entries), start);
            for (s32 index = 0; index < 14; index++)
            {
                if (node != 0)
                {
                    s32 text_key;
                    ItemSortRecord* record = static_cast<ItemSortRecord*>(node->value);
                    if (record != 0)
                    {
                        s32 identifier = (u16)(record->table_index + 1);
                        text_key = identifier + CITEM_MSG_ITEM_NAMES;
                        if ((unk1b8[identifier / 32] & (1 << (identifier % 32))) != 0)
                        {
                            static_cast<LibClass174EF0*>(unk48[index])->set_color(0x508050);
                        }
                        else
                        {
                            static_cast<LibClass174EF0*>(unk48[index])->set_color(0x808080);
                        }
                        lib_text_set_resource(reinterpret_cast<LibObject178750*>(unk48[index]), func_slot54(), text_key, 0);
                        LibObject174F20* numeric = static_cast<LibObject174F20*>(third[index]);
                        numeric->numeric_value = record->unk08;
                        numeric->unk3c = 1;
                        unk48[index]->unk3d = 1;
                        third[index]->unk3d = 1;
                        second[index]->unk3d = 1;
                    }
                    node = node->next;
                }
                else
                {
                    unk48[index]->unk3d = 0;
                    third[index]->unk3d = 0;
                    second[index]->unk3d = 0;
                }
            }
        }
    }
}

ItemListWindow1848D0::~ItemListWindow1848D0()
{
}

void FieldClass15AD40::func_slot110(u8 value)
{
    unk84 = value;
}

u8 ItemListWindow1848D0::func_slotbc()
{
    if (this->FieldClass15AE60::unk8c == 7)
    {
        return 0;
    }

    this->sort_enabled = !this->sort_enabled;

    if (this->sort_enabled != 0)
    {
        func_00354980(&this->entries, func_00351E40, 0, 1);
    }
    else
    {
        this->func_slot11c(0, -1);
    }

    this->refresh_rows(this->unk22);
    return 1;
}

u8 ItemListWindow1848D0::func_slotb4()
{
    this->func_slot10c(0, 0);
    FieldClass15AE70* associated = static_cast<FieldClass15AE70*>(this->func_slot44());
    associated->func_slot64();
    D_001B643C->controller->selected->func_00263C70(associated);
    return 2;
}

void ItemListWindow1848D0::func_slot10c(u32 value, u32 alternate)
{
    if (reinterpret_cast<ControlScreen*>(FieldClass15AE60::unk04) != 0)
    {
        reinterpret_cast<ControlScreen*>(FieldClass15AE60::unk04)->unk3f = alternate;
        if (alternate != 0)
        {
            struct ControlScreen* screen = reinterpret_cast<ControlScreen*>(FieldClass15AE60::unk04);
            screen->unk70 = 128.0f;
            screen->unk3c = 1;
        }
        else
        {
            struct ControlScreen* screen = reinterpret_cast<ControlScreen*>(FieldClass15AE60::unk04);
            screen->unk70 = 64.0f;
            screen->unk3c = 1;
        }
    }
}

void ItemListWindow1848D0::set_scroll_position(float start)
{
    s32 index;
    float value = start + 16.0f;
    for (index = 0; index < 14; index++)
    {
        LibClass178600* slot = unk48[index];
        slot->unk18.unk00 = 24.0f;
        slot->unk18.unk04 = value;
        slot->unk3c = 1;
        slot = second[index];
        slot->unk18.unk00 = 326.0f;
        slot->unk18.unk04 = value;
        slot->unk3c = 1;
        slot = third[index];
        slot->unk18.unk00 = 334.0f;
        slot->unk18.unk04 = value;
        slot->unk3c = 1;
        value += 28.0f;
    }
}

s32 ItemWindow1849F0::func_slotf4(u32 associated)
{
    LibClass178630* panel;
    func_002CE760(this, associated, 0, 9, 0x578, 204.0f, 72.0f, 0.0f);
    panel = allocate_panel();
    lib_panel_init_rectangle(panel, 1, 0.0f, 0.0f, 412.0f, 396.0f, 88.0f);
    lib_container_attach_widget(this->unk10, (LibClass178600*)panel);
    return 1;
}

ItemWindow1849F0::~ItemWindow1849F0()
{
}

void ItemWindow184AF0::func_slot64()
{
    set_selector_height(unka8, 128.0f);
}

u8 ItemWindow184AF0::func_slotb4()
{
    this->set_state(1, 0x80);
    return 2;
}

/**
 * @brief Confirm the selected entry: lower the selector, focus the list and describe the choice.
 * @return Zero while the selector is missing or idle, otherwise one.
 */
u8 ItemWindow184AF0::func_slotb0()
{
    if (unka8 == 0)
    {
        return 0;
    }

    bool idle = !unka8->ItemCreationClass185050::unk35;
    if (idle)
    {
        return 0;
    }

    set_selector_height(unka8, 64.0f);

    u16 selected = unka8->func_0023B3A0();
    unkb0->func_slot10c(1, 1);
    unkb0->func_slot110(1);

    if (selected == 7)
    {
        if (controller->unk54 != 0)
        {
            controller->unk54->text[0]->unk3f = 0;
        }
    }
    else
    {
        ItemController* owner;
        ItemWindow1844B0* message = controller->unk54;
        if (message != 0)
        {
            owner = static_cast<ItemController*>(D_001B643C->controller->selected);
            lib_text_set_resource(message->text[0], owner->get_resource_slot(), 0x1B80, 0);
            lib_text_set_resource(message->text[1], owner->get_resource_slot(), 0x1B7D, 0);
            lib_text_set_resource(message->text[2], owner->get_resource_slot(), 0x1B7E, 0);
            message->text[0]->unk3f = 1;
        }
    }

    if (D_001B643C->state != 0)
    {
        D_001B643C->state->unk9a = 1;
    }

    D_001B643C->controller->selected->func_00263C70(unkb0);
    return 1;
}

/** @brief Move the selector forward and highlight, describe and show the newly selected entry. */
void ItemWindow184AF0::func_slot6c()
{
    if (unka8 != 0 && unka8->func_0023B3B0(1) != 1)
    {
        u16 selected = unka8->func_0023B3A0();
        s16 row = selected;

        if (unka8 != 0)
        {
            for (s32 index = 0; index < unkb8; index++)
            {
                LibObject178750* text = static_cast<LibObject178750*>(func_003545E0(reinterpret_cast<ItemListOwner*>(&unk2c), index)->value);

                if (index == row)
                {
                    set_text_color(text, 0x288080);
                    unkac->func_0023B7E0(text);
                }
                else
                {
                    set_text_color(text, 0x808080);
                }
            }
        }

        s16 key = selected + 0x1B6C;
        set_item_window_message(controller->unk48, key);
        unkb0->func_slot11c(1, unka8->func_0023B3A0());
        unkb0->func_slot10c(1, 0);
    }
}

/** @brief Move the selector back and highlight, describe and show the newly selected entry. */
void ItemWindow184AF0::func_slot68()
{
    if (unka8 != 0 && unka8->func_0023B3B0(0) != 1)
    {
        u16 selected = unka8->func_0023B3A0();
        s16 row = selected;

        if (unka8 != 0)
        {
            for (s32 index = 0; index < unkb8; index++)
            {
                LibObject178750* text = static_cast<LibObject178750*>(func_003545E0(reinterpret_cast<ItemListOwner*>(&unk2c), index)->value);

                if (index == row)
                {
                    set_text_color(text, 0x288080);
                    unkac->func_0023B7E0(text);
                }
                else
                {
                    set_text_color(text, 0x808080);
                }
            }
        }

        s16 key = selected + 0x1B6C;
        set_item_window_message(controller->unk48, key);
        unkb0->func_slot11c(1, unka8->func_0023B3A0());
        unkb0->func_slot10c(1, 0);
    }
}

void ItemWindow184AF0::func_slot5c()
{
    if (D_001B643C->controller->selected->func_00261150() == this)
    {
        ItemController* owner = static_cast<ItemController*>(D_001B643C->controller->selected);
        owner->unkb4 = unka8->func_0023B3A0();

        if (owner->unk54 != 0)
        {
            owner->unk54->text[0]->unk3f = 0;
        }
    }
}

// Sized like the u8 column parameter it feeds.
#pragma enumsalwaysint off
/** Column count of a selection widget. */
enum SelectorColumns
{
    SELECTOR_SINGLE_COLUMN = 1
};
#pragma enumsalwaysint reset

/**
 * @brief Create the panel, the ten category labels and icons, the selector and its highlight, then highlight the first label.
 * @param associated Resource source word.
 * @return Zero when the list window is missing, otherwise one.
 */
s32 ItemWindow184AF0::func_slotf4(u32 associated)
{
    unkb0 = static_cast<ItemListWindow1848D0*>(func_slot4c());

    if (unkb0 == 0)
    {
        return 0;
    }

    FieldClass15AE70::func_slot14(associated, 0, 9, 0x708, 16.0f, 72.0f, 0.0f);
    LibClass178630* panel = allocate_panel();
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 192.0f, 288.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    unkb8 = 10;

    for (s32 index = 0; index < unkb8; index++)
    {
        LibObject178750* text = allocate_text_widget();
        float y = 16.0f + 26.0f * static_cast<float>(index);
        text->init_resource_rectangle(42.0f, y, 0.0f, 0.0f, associated, index + 0x1B62, 0);
        text->unk88 = -1.0f;
        text->unk3c = 1;
        text->set_scale(0.9f, 0.9f);
        lib_container_attach_widget(unk10, text);
        func_00354550(reinterpret_cast<ItemListOwner*>(&unk2c), text);

        ItemCreationOptionResourceDisplay* icon = new (0) ItemCreationOptionResourceDisplay;
        void* allocation = field_get_aligned_allocation(D_001B643C->buffers, 14);
        FieldResourceRecord* record = field_find_resource_record(D_001B643C->buffers, index + 50);
        icon->unkcc = allocation;
        icon->unkd0 = 14;
        icon->func_002D6440(16.0f, y, record);
        lib_container_attach_widget(unk10, icon);
    }

    unka8 = new (0) FieldClass153130;
    // TODO: Binding the row top through a reference is the only way I found to get the original's constant order.
    const float& top = 28.0f;
    SelectorColumns columns = SELECTOR_SINGLE_COLUMN;
    unka8->func_0023B530(columns, unkb8, 1, 0, 1, 20.0f, top, 0.0f, 26.0f);
    lib_container_attach_widget(unk10, unka8);

    LibObject178750* first = static_cast<LibObject178750*>(func_003545E0(reinterpret_cast<ItemListOwner*>(&unk2c), 0)->value);
    unkac = new (0) FieldClass153170;
    unkac->func_0023B850(first, 0x288080);
    lib_container_attach_widget(unk10, unkac);

    if (unka8 != 0)
    {
        for (s32 index = 0; index < unkb8; index++)
        {
            LibObject178750* text = static_cast<LibObject178750*>(func_003545E0(reinterpret_cast<ItemListOwner*>(&unk2c), index)->value);

            if (index == 0)
            {
                set_text_color(text, 0x288080);
                unkac->func_0023B7E0(text);
            }
            else
            {
                set_text_color(text, 0x808080);
            }
        }
    }

    return 1;
}

ItemWindow184AF0::~ItemWindow184AF0()
{
}

extern "C"
{


/**
 * @brief Hold the text at its starting position, then scroll and wrap it horizontally.
 * @param record Window storing the display, delay and scrolling bounds.
 */
}

void ItemWindow184BF0::func_slot5c()
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

    {
        float left = this->left_edge;
        x -= 108.0f * D_001B6690;

        if (x < left - (float)this->scroll_extent)
        {
            x = 2.0f + (left + this->visible_width);
        }

        set_text_bounds(display, x, y, width, height);
    }
}

void ItemWindow184BF0::func_slot60(s32 text_key)
{
    if (text_key >= 7020 && text_key < 7035)
    {
        scrolling = 0;
        delay_frames = 0;
        lib_text_set_resource(text_display, func_slot54(), text_key, 1);
        scroll_extent = (s32)lib_text_measure_bounds(text_display)->unk08 + 6;
    }
}

/**
 * @brief Create the label, hint and clipped scrolling message, then show the first message.
 * @param associated Resource source word.
 * @return Zero when a display could not be allocated, otherwise one.
 */
s32 ItemWindow184BF0::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot14(associated, 0, 9, 0x578, 16.0f, 16.0f, 0.0f);

    LibObject178750* label = new (0) LibObject178750;
    label->init_resource_rectangle(16.0f, 6.0f, 0.0f, 0.0f, associated, 0x1B58, 0);
    lib_container_attach_widget(unk10, label);
    func_00354550(reinterpret_cast<ItemListOwner*>(&unk2c), label);

    LibObject178750* caption = new (0) LibObject178750;
    caption->init_resource_rectangle(36.0f, 40.0f, 0.0f, 0.0f, associated, 0x1B8E, 0);
    caption->set_scale(0.65f, 0.65f);
    lib_container_attach_widget(unk10, caption);
    func_00354550(reinterpret_cast<ItemListOwner*>(&unk2c), caption);

    text_display = new (0) LibObject178750;
    LibClass1746A0* clip = new (0) LibClass1746A0;
    LibClass1746A0* reset = new (0) LibClass1746A0;

    if (text_display == 0 || clip == 0 || reset == 0)
    {
        return 0;
    }

    label_width = lib_text_measure_bounds(label)->unk08;
    left_edge = 18.0f + label_width;
    visible_width = 640.0f - (16.0f + shifted_position(left_edge, 32.0f));
    start_x = 24.0f + label_width;
    lib_scissor_init_rectangle(clip, left_edge, 0.0f, visible_width, 56.0f);
    lib_container_attach_widget(unk10, clip);
    func_00354620(reinterpret_cast<ItemListOwner*>(&unk20), clip);

    text_display->init_resource_rectangle(start_x, 6.0f, 0.0f, 0.0f, associated, 0x1B6C, 0);
    lib_container_attach_widget(unk10, text_display);
    func_00354550(reinterpret_cast<ItemListOwner*>(&unk2c), text_display);

    lib_scissor_init_reset(reset, 1);
    lib_container_attach_widget(unk10, reset);
    func_00354620(reinterpret_cast<ItemListOwner*>(&unk20), reset);

    func_slot60(0x1B6C);
    return 1;
}

ItemWindow184BF0::~ItemWindow184BF0()
{
}

/**
 * @brief Create the window container and its three resource displays.
 * @param associated Resource source word.
 * @return One after initialization.
 */
s32 ItemWindow184CF0::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot14(associated, 0, 9, 0x4B0, 16.0f, 16.0f, 0.0f);
    unka8 = new (0) ItemCreationOptionResourceDisplay;
    unkac = new (0) ItemCreationOptionResourceDisplay;
    unkb0 = new (0) ItemCreationOptionResourceDisplay;

    void* allocation = field_get_aligned_allocation(D_001B643C->buffers, 11);
    unka8->unkcc = allocation;
    unkac->unkcc = allocation;
    unkb0->unkcc = allocation;
    unka8->unkd0 = 11;
    unkac->unkd0 = 11;
    unkb0->unkd0 = 11;

    unka8->func_002D6440(0.0f, 0.0f, field_find_resource_record(D_001B643C->buffers, 5));
    unkac->func_002D6440(256.0f, 0.0f, field_find_resource_record(D_001B643C->buffers, 6));
    unkb0->func_002D6440(512.0f, 0.0f, field_find_resource_record(D_001B643C->buffers, 7));

    lib_container_attach_widget(unk10, unka8);
    lib_container_attach_widget(unk10, unkac);
    lib_container_attach_widget(unk10, unkb0);
    return 1;
}

ItemWindow184CF0::~ItemWindow184CF0()
{
}

void ItemController::func_slot5c()
{
    if (resource_slot != 0)
    {
        lib_release_resource_slot(D_001B657C, resource_slot);
    }

    lib_object_detach_owner(&static_cast<FieldClass153E30&>(*this));
    func_001DD7B0();
    field_queue_allocation_release(D_001B643C->buffers, 14);
}

s32 ItemController::init_windows()
{
    CitemFlagBlock* flag_block = reinterpret_cast<CitemFlagBlock*>(resident_find_entry(resident_get_entry_table(resident_get_runtime_owner()), 4));

    if (flag_block != 0)
    {
        entry_count = 0;

        for (s32 index = 0; index < 68; index++)
        {
            bool enabled = flag_block->is_set(index + 0x76C);

            if (enabled == true)
            {
                entries[entry_count++] = index;
            }
        }
    }

    if (unk5c != 1)
    {
        unk44 = new (0) ItemWindow184CF0;
        unk48 = new (0) ItemWindow184BF0;
        unk4c = new (0) ItemWindow184AF0(this);
        unk50 = new (0) ItemListWindow1848D0(this);
        unk54 = new (0) ItemWindow1844B0;
        unk58 = new (0) ItemWindow1849F0;
        unk44->func_slotf4(resource_slot);
        FieldClass153E30::add_child(unk44);
        unk44->func_slot40(0);
        unk48->func_slotf4(resource_slot);
        FieldClass153E30::add_child(unk48);
        unk24 = unk48;
        unk48->func_slot40(unk44);
        unk4c->func_slot48(unk50);
        unk4c->func_slotf4(resource_slot);
        FieldClass153E30::add_child(unk4c);
        unk58->func_slotf4(resource_slot);
        FieldClass153E30::add_child(unk58);
        unk50->func_slot40(unk4c);
        unk50->func_slot104(resource_slot);
        FieldClass153E30::add_child(unk50);
        unk54->func_slotf4(resource_slot);
        FieldClass153E30::add_child(unk54);
        unk20 = unk4c;
    }

    windows_initialized = 1;
    return 1;
}

s32 ItemController::on_resource_loaded(void* buffer)
{
    if (buffer == 0)
    {
        return 0;
    }

    CitemAlignedResource* resource = aligned_item_resource(buffer);
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
    runtime->item_name_base_key = CITEM_MSG_ITEM_NAMES + 1;
    return init_windows();
}

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

void ItemController::func_001DD7B0()
{
    if (selection != 0)
    {
        release_record_selection(selection);
    }

    FieldClass153E30* receiver = this;
    resident_enqueue_object(D_001B65F4, receiver);
}

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
    selection = 0;
    unk44 = 0;
    unk48 = 0;
    unk4c = 0;
    unk50 = 0;
    unk54 = 0;
    unk58 = 0;
    unkbc = 0;
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

    for (s32 index = 0; index < 68; index++)
    {
        entries[index] = 0;
    }
}

/** @brief Leave the default DMA notification hook unchanged. @param value Unused notification value. */
void LibClass171FF0::func_003EFA90(u32 value)
{
}

void LibClass171FF0::func_003F4410(u32 value)
{
}

s32 ItemCoordinateSelector::get_default_list_kind()
{
    return 3;
}

void ItemCoordinateSelector::update()
{
}

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
    func_4CE4C0(&unk30, value);
}

/** @brief Update the rotation state and mark the transform dirty. @param value Rotation components. */
void LibClass171EF0::func_003EEF60(const LibVector4* value)
{
    transform_dirty = 1;
    func_4CE4C0(&unk30, value);
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
    func_4CE4C0(&unk30, &value);
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

ItemCoordinateSelector::~ItemCoordinateSelector()
{
}

s32 ItemHpMpGauge::get_default_list_kind()
{
    return 14;
}

void ItemHpMpGauge::func_003F4420()
{
    unk60 = unka8;
}

ItemWindow1844B0::~ItemWindow1844B0()
{
}

extern "C"
{


void func_00353EA0(void* object)
{
}

void func_00353EB0(void* object)
{
}

void func_00353EC0(void* object)
{
}

s32 func_00353ED0(void* object)
{
    return 0;
}

s32 func_00353EE0(void* object)
{
    return 0;
}

void func_00353F70(StatusRecord* state, u32 value)
{
    state->unk24 = value;
}

u32 func_00353F80(StatusRecord* state)
{
    return state->unk24;
}

void func_00353F90(StatusRecord* state, s8 value)
{
    state->unk28 = value;
}

s8 func_00353FA0(StatusRecord* state)
{
    return state->unk28;
}

s32 func_00353FB0(void* object)
{
    return 0;
}

s32 func_00353FC0(void* object)
{
    return 0;
}

void func_00353FD0(void* object)
{
}

void func_00353FE0(void* object)
{
}

void func_00353FF0(void* object)
{
}

void func_00354000(void* object)
{
}

s32 func_00354010(void* object)
{
    return 0;
}

s32 func_00354020(void* object)
{
    return 0;
}

s32 func_00354030(void* object)
{
    return 0;
}

}

s32 ItemController::get_default_list_kind()
{
    return 4;
}

u8 ItemController::windows_ready()
{
    return windows_initialized;
}

ItemList184ED8::ItemList184ED8()
{
    head = new (0) ItemListNode;

    if (head == 0)
    {
        throw;
    }

    head->next = 0;
    count = 0;
}

ItemList184ED8::~ItemList184ED8()
{
    func_003541F0(this);

    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

extern "C"
{

void item_append_list_value(Record003540E0* owner, void* value)
{
    ItemListNode* node = (ItemListNode*)func_00100AC0(sizeof(ItemListNode), 0);
    if (node != 0)
    {
        ItemListNode* tail;
        node->value = value;
        node->next = 0;
        tail = owner->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        owner->count++;
    }
}

void func_003541F0(Record003540E0* owner)
{
    ItemListNode* node = owner->head->next;

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

    owner->head->next = 0;
    owner->count = 0;
}

}

ItemList184EC8::ItemList184EC8()
{
    head = new (0) ItemListNode;

    if (head == 0)
    {
        throw;
    }

    head->next = 0;
    count = 0;
}

ItemList184EC8::~ItemList184EC8()
{
    func_00354400(this);

    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

extern "C"
{

void func_00354370(ItemListOwner* owner, void* value)
{
    ItemListNode* node = (ItemListNode*)func_00100AC0(sizeof(ItemListNode), 0);
    if (node != 0)
    {
        ItemListNode* tail;
        node->value = value;
        node->next = 0;
        tail = owner->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        owner->count++;
    }
}

void func_00354400(Record003542F0* owner)
{
    ItemListNode* node = owner->head->next;

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

    owner->head->next = 0;
    owner->count = 0;
}

ItemListNode* func_00354480(ItemListOwner* owner, s32 index)
{
    ItemListNode* node = owner->head->next;
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

void func_003544C0(ItemListOwner* owner, void* value)
{
    ItemListNode* node = (ItemListNode*)func_00100AC0(sizeof(ItemListNode), 0);
    if (node != 0)
    {
        ItemListNode* tail;
        node->value = value;
        node->next = 0;
        tail = owner->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        owner->count++;
    }
}

void func_00354550(ItemListOwner* owner, void* value)
{
    ItemListNode* node = (ItemListNode*)func_00100AC0(sizeof(ItemListNode), 0);
    if (node != 0)
    {
        ItemListNode* tail;
        node->value = value;
        node->next = 0;
        tail = owner->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        owner->count++;
    }
}

ItemListNode* func_003545E0(ItemListOwner* owner, s32 index)
{
    ItemListNode* node = owner->head->next;
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

void func_00354620(ItemListOwner* owner, void* value)
{
    ItemListNode* node = (ItemListNode*)func_00100AC0(sizeof(ItemListNode), 0);
    if (node != 0)
    {
        ItemListNode* tail;
        node->value = value;
        node->next = 0;
        tail = owner->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        owner->count++;
    }
}

void func_003546B0(ItemListOwner* owner, void* value)
{
    ItemListNode* node = (ItemListNode*)func_00100AC0(sizeof(ItemListNode), 0);
    if (node != 0)
    {
        ItemListNode* tail;
        node->value = value;
        node->next = 0;
        tail = owner->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        owner->count++;
    }
}

}

ItemList184EB8::~ItemList184EB8()
{
    func_003547C0(this);

    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

extern "C"
{

void func_003547C0(Record00354740* owner)
{
    CitemCoordinateNode* node = owner->head->next;

    if (node == 0)
    {
        return;
    }

    while (node != 0)
    {
        CitemCoordinateNode* next = node->next;
        delete node;
        node = next;
    }

    owner->head->next = 0;
    owner->count = 0;
}

void item_append_selector_coordinate(Record00354740* owner, CitemCoordinate2 value)
{
    CitemCoordinateNode* node = allocate_coordinate_node();

    if (node != 0)
    {
        CitemCoordinateNode* tail;

        node->x = value.x;
        node->y = value.y;
        node->next = 0;
        tail = owner->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        owner->count++;
    }
}

}

ItemList184EB8::ItemList184EB8()
{
    head = new (0) CitemCoordinateNode;

    if (head == 0)
    {
        throw;
    }

    head->next = 0;
    count = 0;
}

extern "C"
{

void func_00354980(ItemList184EC8* owner, ItemListComparator compare, u32 comparison_arg, s32 ascending)
{
    ItemListNode* position = owner->head;
    ItemListNode* previous;
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

}
