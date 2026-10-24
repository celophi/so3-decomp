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
#include "overlays/lib/resource_widget_inlines.h"
#include "overlays/lib/list_indicator_inlines.h"
#include "overlays/lib/movement_widget_inlines.h"
#include "overlays/lib/text_00419A70.h"
#include "overlays/lib/marker_widget_inlines.h"

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
};

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

struct DisplayRecord
{
    void* methods;
    u8 unk04[0x5C];
    u8 unk60;
    u8 unk61[0x47];
    u8 unka8;
};

struct Record00349190
{
    u8 unk00[0x20];
    u32 unk20;
    u32 unk24;
    u32 unk28;
    float unk2c;
    u8 unk30[0x3C];
    u16 unk6c;
    u8 unk6e[0x46];
    u32 unkb4;
    u32 unkb8;
};

/** Partial transform receiver with MAIN table D_184400, a packet, and a release flag. */
struct Record00349250
{
    void* methods;
    u8 unk04[0x60];
    u8 dma_pending;
    u8 unk65[0x2B];
    void* notification_table;
    u8 unk94[0x34];
    ResidentPacket* packet;
    u8 unkcc[0x38];
    u8 release_pending;
};

struct Record00349BF0
{
    u8 unk00[0x2C];
    void* unk2c;
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






struct TransformRecord
{
    u8 unk00[0x20];
    Vector4 unk20;
    Vector4 unk30;
    Vector4 unk40;
    u8 unk50;
};

struct ScreenRecord
{
    u8 unk00[0x3C];
    u8 unk3c;
    u8 unk3d[0x33];
    float unk70;
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

        virtual void func_slot11c(s32 first, s32 second);

        LibClass178600* second[14];
        LibClass178600* third[14];
        ItemController* controller;
        ItemList184EC8 entries;
        u32 unk1b8[24];
        u8 sort_enabled;
};

struct Record00353A50
{
    void* methods;
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

        virtual void func_slot5c();

        /** @brief Restore the linked panel height and mark it for update. */
        virtual void func_slot64();

        virtual void func_slot68();

        virtual void func_slot6c();

        virtual u8 func_slotb0();

        /** @brief Set the window state and flags. @return Two after updating the state. */
        virtual u8 func_slotb4();

        virtual s32 func_slotf4(u32 associated);

        ScreenRecord* unka8;
        void* unkac;
        FieldClass15AE70* unkb0;
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
            unkb4 = 0.0f;
            start_x = 0.0f;
            left_edge = 0.0f;
            visible_width = 0.0f;
        }

        /** @brief Destroy the window and its Field base. */
        virtual ~ItemWindow184BF0();

        /** @brief Delay, scroll and wrap the text within its horizontal bounds. */
        virtual void func_slot5c();

        virtual void func_slot60(s32 text_key);

        virtual s32 func_slotf4(u32 associated);

        CitemTextDisplay* text_display;
        s32 scroll_extent;
        s16 delay_frames;
        u8 scrolling;
        u8 unkb3;
        float unkb4;
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

/** Prefix of native D_153D40 runtime storage produced by Field002630F0. */
typedef struct CitemRuntime643C
{
    u8 unk00[0x10];
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
            unka8 = 0;
            selection = 0;
            unkb0 = 0.0f;
            unkb4 = 0.0f;
            unkb8 = 0.0f;
            unkbc = 0.0f;
            unkc0 = 1;
            unkc4 = 2;
            message_changed = 0;
        }

        /** @brief Restore the controller message and destroy the window base. */
        virtual ~ItemWindow1845B0();

        virtual void func_slot5c();
        /** @brief Move the selector from its second coordinate row to its first row. */
        virtual void func_slot68();
        /** @brief Move the selector from its first coordinate row to its second row. */
        virtual void func_slot6c();
        /** @brief Move the selector back one entry, wrapping to its eighth entry. */
        virtual void func_slot70();
        /** @brief Advance the selector one entry, wrapping after its eighth entry. */
        virtual void func_slot74();
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
        virtual s32 func_slotf4(u32 associated);

        void* unka8;
        FieldObject23B1D0* selection;
        float unkb0;
        float unkb4;
        float unkb8;
        float unkbc;
        s32 unkc0;
        s32 unkc4;
        u8 message_changed;
        u8 unkc9[0x83];
};

/** Item action window owning a selector and a list of display widgets. */
class ItemWindow1846B0 : public FieldClass15AE70
{
    public:
        /** @brief Initialize the selector links, display list, and action state. */
        ItemWindow1846B0()
        {
            unka8 = 0;
            selection = 0;
            unkb0 = 0.0f;
            unkb4 = 0.0f;
            unkb8 = 0.0f;
            message_changed = 0;
        }

        /** @brief Restore the controller message and destroy the display list and window base. */
        virtual ~ItemWindow1846B0();
        /** @brief Release the list's display objects and the window's base displays. */
        virtual void func_slot0c();
        virtual void func_slot5c();
        /** @brief Move the selector from its second coordinate row to its first row. */
        virtual void func_slot68();
        /** @brief Move the selector from its first coordinate row to its second row. */
        virtual void func_slot6c();
        /** @brief Move the selector back one entry, wrapping to its eighth entry. */
        virtual void func_slot70();
        /** @brief Advance the selector one entry, wrapping after its eighth entry. */
        virtual void func_slot74();
        virtual u8 func_slotb0();
        /** @brief Close the action window and restore its parent. @return Two after closing the window. */
        virtual u8 func_slotb4();
        virtual s32 func_slotf4(u32 associated);

        void* unka8;
        FieldObject23B1D0* selection;
        float unkb0;
        float unkb4;
        float unkb8;
        ItemList184ED8 displays;
        u8 unkc8[0x140];
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
extern u8 D_184390[];
extern u8 D_1844A0[];
extern u8 __vt__23ItemCreationClass175110[];
extern u8 D_50CD30[];
extern LibWidgetColors4C5590 D_354C40;
extern void func_2CEAF0(void* object, s32 flags);
extern void func_100B40(void* object);
extern void func_4CE4C0(Vector4* destination, const Vector4* source);
extern void func_2BC410(Record00349BF0* record, s32 flag);
extern void func_4618F0(void* record, s32 flag);
extern void func_4C48B0(void* record, s32 flag);
extern void func_2CD9F0(void* record, s32 flag);
extern void func_44B110(void* object, s32 arg1, s32 arg2, void* arg3, float value, s32 flag);

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
 * @brief View the transform receiver through its native secondary DMA interface.
 * @param object Complete transform receiver.
 * @return Interface at offset 0x90, or null for a null receiver.
 */
static inline struct LibClass171FF0* transform_notification(Record00349250* object)
{
    void* notification = object;

    if (object != 0)
    {
        notification = (u8*)notification + 0x90;
    }
    return (struct LibClass171FF0*)notification;
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
static inline void set_text_bounds(struct CitemTextDisplay* display, float x, float y, float width, float height)
{
    display->rectangle.unk00 = x;
    display->rectangle.unk04 = y;
    display->rectangle.unk08 = width;
    display->rectangle.unk0c = height;
    display->unk3c = 1;
}

/** @brief Read the catalog entry's unsellable flag. @param definition Catalog entry. @return Flag as a byte. */
static inline u8 item_definition_unsellable(const ItemCreationCategoryDefinition* definition)
{
    return definition->unsellable;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003483C0);

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

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003490F0);

s32 func_00349190(Record00349190* record, s32 arg1, s32 arg2, void* arg3, float first, float second, float third)
{
    record->unk6c = 0x6006;
    record->unk20 = 0;
    record->unk24 = 0;
    record->unk28 = 0;
    record->unk2c = 1.0f;
    func_44B110(record, arg1, arg2, arg3, third, 0);
    record->unkb4 = 0;
    record->unkb8 = 0;
    return 1;
}

void func_003491F0(void* object)
{
    func_4D00B0(object);
}

void item_submit_transform_packet(Record00349250* object)
{
    object->dma_pending = 1;
    if (object->packet != 0)
    {
        func_0011F770(object->packet, transform_notification(object));
    }
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00349250);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003492F0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00349B90);

Record00349BF0* func_00349BF0(Record00349BF0* record, s16 flag)
{
    if (record != 0)
    {
        record->unk2c = D_1844A0;
        func_2BC410(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
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

extern "C"
{


INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_slot5c__16ItemWindow1845B0Fv);

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
static inline s32 item_selection_control_is_clear(FieldObject23B1D0* selection)
{
    return ((u32)selection->flag75 > 0) ^ 1;
}

}

void ItemWindow1845B0::func_slot70()
{
    FieldObject23B1D0* selection = this->selection;
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
    func_0023B1D0(selection, index, 0);
}

extern "C"
{

}

void ItemWindow1845B0::func_slot74()
{
    FieldObject23B1D0* selection = this->selection;
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
    func_0023B1D0(selection, index, 0);
}

extern "C"
{

}

void ItemWindow1845B0::func_slot6c()
{
    FieldObject23B1D0* selection = this->selection;
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
    func_0023B1D0(selection, index, 0);
}

extern "C"
{

}

void ItemWindow1845B0::func_slot68()
{
    FieldObject23B1D0* selection = this->selection;
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
    func_0023B1D0(selection, index, 0);
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

extern "C"
{

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_slotb0__16ItemWindow1845B0Fv);

}

ItemWindow1845B0::~ItemWindow1845B0()
{
    if (message_changed != 0)
    {
        ItemController* controller = static_cast<ItemController*>(D_001B643C->controller->selected);
        set_item_window_message(controller->unk48, controller->unkb4 + 0x1B6C);
    }
}

extern "C"
{

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_slotf4__16ItemWindow1845B0FUi);

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

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034C710);

}

FieldRecordSelection* ItemController::selected_records()
{
    return selection;
}

extern "C"
{

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_slot5c__16ItemWindow1846B0Fv);

}

void ItemWindow1846B0::func_slot70()
{
    FieldObject23B1D0* selection = this->selection;
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
    func_0023B1D0(selection, index, 0);
}

extern "C"
{

}

void ItemWindow1846B0::func_slot74()
{
    FieldObject23B1D0* selection = this->selection;
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
    func_0023B1D0(selection, index, 0);
}

extern "C"
{

}

void ItemWindow1846B0::func_slot6c()
{
    FieldObject23B1D0* selection = this->selection;
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
    func_0023B1D0(selection, index, 0);
}

extern "C"
{

}

void ItemWindow1846B0::func_slot68()
{
    FieldObject23B1D0* selection = this->selection;
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
    func_0023B1D0(selection, index, 0);
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

extern "C"
{

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_slotb0__16ItemWindow1846B0Fv);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_slotf4__16ItemWindow1846B0FUi);

}

void ItemWindow1846B0::func_slot0c()
{
    for (ItemListNode* node = this->displays.head->next; node != 0; node = node->next)
    {
        static_cast<LibClass171EA0*>(node->value)->func_003EF740();
    }

    FieldClass15AE70::func_slot0c();
}

extern "C"
{

void item_queue_transform_release(Record00349250* object)
{
    object->release_pending = 1;
    func_0044B210((LibClass174610*)object);
    resident_enqueue_object(D_001B65F4, object);
}

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
            reinterpret_cast<LibClass178600*>(window->selection)->unk3f = 1;
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
            reinterpret_cast<LibClass178600*>(window->selection)->unk3f = 1;
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

extern "C"
{

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_slot5c__26ItemAllocationWindow1847B0Fv);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00350B60);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_slot11c__20ItemListWindow1848D0Fii);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", __ct__20ItemListWindow1848D0FP14ItemController);

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
    struct ScreenRecord* screen = this->unka8;

    if (screen != 0)
    {
        screen->unk70 = 128.0f;
        screen->unk3c = 1;
    }
}

u8 ItemWindow184AF0::func_slotb4()
{
    this->set_state(1, 0x80);
    return 2;
}

extern "C"
{


INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_slotb0__16ItemWindow184AF0Fv);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_slot6c__16ItemWindow184AF0Fv);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_slot68__16ItemWindow184AF0Fv);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_slot5c__16ItemWindow184AF0Fv);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_slotf4__16ItemWindow184AF0FUi);

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
    struct CitemTextDisplay* display = this->text_display;
    float x = display->rectangle.unk00;
    float y = display->rectangle.unk04;
    float width = display->rectangle.unk08;
    float height = display->rectangle.unk0c;

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

extern "C"
{


INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_slot60__16ItemWindow184BF0Fi);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_slotf4__16ItemWindow184BF0FUi);

}

ItemWindow184BF0::~ItemWindow184BF0()
{
}

extern "C"
{


INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_slotf4__16ItemWindow184CF0FUi);

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

extern "C"
{

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", __ct__14ItemControllerFv);

}

void ItemClass184380::func_00353A30()
{
}

void ItemClass184380::func_00353A40()
{
}

extern "C"
{

Record00353A50* func_00353A50(Record00353A50* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_184390;
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00353AA0);

s32 func_00353B00(void* object)
{
    return 3;
}

void func_00353B10(void* object)
{
}

void func_00353B20(void* object)
{
}

void func_00353B30(TransformRecord* record, const Vector4* value)
{
    record->unk50 = 1;
    record->unk20 = *value;
}

void func_00353B50(TransformRecord* record, const Vector4* value)
{
    record->unk50 = 1;
    record->unk20 = *value;
}

void func_00353B70(TransformRecord* record, float x, float y, float z)
{
    record->unk50 = 1;
    record->unk20.x = x;
    record->unk20.y = y;
    record->unk20.z = z;
    record->unk20.w = 1.0f;
}

void func_00353B90(TransformRecord* record, float x, float y, float z, float w)
{
    record->unk50 = 1;
    record->unk30.x = x;
    record->unk30.y = y;
    record->unk30.z = z;
    record->unk30.w = w;
}

void func_00353BB0(TransformRecord* record, const Vector4* value)
{
    record->unk50 = 1;
    record->unk30 = *value;
}

void func_00353BD0(TransformRecord* record, const Vector4* value)
{
    record->unk50 = 1;
    record->unk30 = *value;
}

void func_00353BF0(TransformRecord* record, const Vector4* input)
{
    record->unk50 = 1;
    func_4CE4C0(&record->unk30, input);
}

void func_00353C20(TransformRecord* record, const Vector4* input)
{
    record->unk50 = 1;
    func_4CE4C0(&record->unk30, input);
}

void func_00353C50(TransformRecord* record, float x, float y, float z)
{
    Vector4 value;
    record->unk50 = 1;
    value.x = x;
    value.y = y;
    value.z = z;
    value.w = 1.0f;
    func_4CE4C0(&record->unk30, &value);
}

void func_00353C90(TransformRecord* record, const Vector4* value)
{
    record->unk50 = 1;
    record->unk40 = *value;
}

void func_00353CB0(TransformRecord* record, const Vector4* value)
{
    record->unk50 = 1;
    record->unk40 = *value;
}

void func_00353CD0(TransformRecord* record, float x, float y, float z)
{
    record->unk50 = 1;
    record->unk40.x = x;
    record->unk40.y = y;
    record->unk40.z = z;
}

s32 func_00353CF0(void* object)
{
    return 0;
}

s32 func_00353D00(float value)
{
    s32 result = 1;
    if (!(value < 0.0f))
    {
        result = 0;
    }
    return result;
}

u8* func_00353D20(void)
{
    return D_50CD30;
}

s32 func_00353D30(void* object)
{
    return 0;
}

void func_00353D40(void* object)
{
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00353D50);

s32 func_00353E20(void* object)
{
    return 14;
}

void func_00353E30(DisplayRecord* display)
{
    display->unk60 = display->unka8;
}

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

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354B80);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354B90);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354BA0);

}
