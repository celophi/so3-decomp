#ifndef SO3_OVERLAYS_CEQUIP_CEQUIP_H
#define SO3_OVERLAYS_CEQUIP_CEQUIP_H

#include "types.h"
#include "overlays/1067-00/text_0028E240.h"
#include "overlays/1067-00/text_002D5260.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_0023B1D0.h"
#include "overlays/1067-00/text_001E1590.h"

typedef struct EquipLinkedList EquipLinkedList;
typedef struct EquipWordList EquipWordList;
typedef struct ItemCreationCategoryRecord ItemCreationCategoryRecord;
typedef struct EquipListState EquipListState;

#ifdef __cplusplus
/** Equipment list with a sentinel node, element count, and virtual destructor. */
struct EquipLinkedList
{
    struct EquipLinkedNode* head;
    u32 count;
    /** @brief Allocate the sentinel and initialize the empty list. */
    EquipLinkedList();
    /** @brief Release the value nodes and sentinel storage. */
    virtual ~EquipLinkedList();
};

/** Equipment list with a sentinel node, element count, and virtual destructor. */
struct EquipWordList
{
    struct EquipWordNode* head;
    u32 count;
    /** @brief Allocate the sentinel and initialize the empty list. */
    EquipWordList();
    /** @brief Release the value nodes and sentinel storage. */
    virtual ~EquipWordList();
};

/** Contextual copies of the recovered list-node base and sentinel. */
typedef LibClass171E80 EquipClass182318;
typedef LibClass171E90 EquipClass182328;

/** Contextual copy of the movement widget's storage base. */
typedef ItemCreationClass185050 EquipClass182340;

/** Contextual tooltip widget with its owned DMA storage and resident table. */
struct EquipClass1797B0 : public LibClass178600
{
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
struct EquipClass1796F0 : public LibObject178660
{
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

struct FieldRecordSelection;
/** Partial scrolling text window with its display bounds and timer. */
struct EquipClass182350 : public FieldClass15AE70
{
    /** @brief Initialize the text display, timer, and scrolling bounds. */
    EquipClass182350()
    {
        unka8 = 0;
        unkac = 0;
        unkb0[0] = 0;
        unkb2 = 0;
        unkb4 = 0;
        unkb8 = 0.0f;
        unkbc = 0.0f;
        unkc0 = 0.0f;
        unkc4 = 0.0f;
    }

    /** @brief Destroy the scrolling text window. */
    virtual ~EquipClass182350();
    /** @brief Hold the display position until its timer expires, then scroll and wrap it. */
    virtual void func_slot5c();
    /** @brief Reset the text display and recompute its width for the supported key range. @param text_key Text resource key. */
    virtual void func_slot60(s32 text_key);
    /** @brief Create the text, frame and scrolling display. @param associated Full resource source word. @return One when initial displays exist, otherwise zero. */
    virtual s32 func_slotf4(u32 associated);
    LibObject178750* unka8;
    s32 unkac;
    u8 unkb0[2];
    s16 unkb2;
    u8 unkb4;
    u8 unkb5[3];
    float unkb8;
    float unkbc;
    float unkc0;
    float unkc4;
};

/** Partial initial equipment window with its selected icon index. */
struct EquipClass182220 : public FieldClass15AE70
{
    /** @brief Initialize the selection grid pointer and signed selection index. */
    EquipClass182220()
    {
        unka8 = 0;
        unkac = -1;
    }

    /** @brief Destroy the initial equipment window. */
    virtual ~EquipClass182220();
    /** @brief Create the panel, text labels and selection grid. @param associated Full resource source word. @param x Window horizontal position. @param y Window vertical position. @param code Nested display initializer code. @return One when all displays exist, otherwise zero. */
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
    FieldObject23CEA0* unka8;
    s16 unkac;
};

/** Partial equipment window with a display widget at offset 0xEC. */
struct EquipClass182C90 : public FieldClass15AE70
{
    /** @brief Initialize the window displays and acquire the active record selection. */
    EquipClass182C90();
    /** @brief Mark the option display corresponding to the current equipment slot. */
    void refresh_slot_marker();
    /** @brief Destroy the equipment window. */
    virtual ~EquipClass182C90();
    /** @brief Enable the display widget while its State window is selected. */
    virtual void func_slot5c();
    /** @brief Create the window displays. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
    s16 unka8;
    u8 unkaa[2];
    FieldRecordSelection* unkac;
    LibObject175140* unkb0;
    LibObject178750* unkb4;
    LibObject174F20* unkb8;
    ItemCreationClass174C40* unkbc;
    ItemCreationClass174C40* unkc0;
    ItemCreationOptionResourceDisplay* unkc4[8];
    u8 unke4[8];
    LibObject178750* unkec;
    LibObject178750* unkf0;
};

/** Window containing three resource-backed option displays. */
struct EquipClass182450 : public FieldClass15AE70
{
    /** @brief Initialize the three option display pointers. */
    EquipClass182450()
    {
        unka8 = 0;
        unkac = 0;
        unkb0 = 0;
    }

    /** @brief Destroy the option window. */
    virtual ~EquipClass182450();
    /** @brief Create and attach the three option displays. @param associated Full resource source word. @return One. */
    virtual s32 func_slotf4(u32 associated);
    ItemCreationOptionResourceDisplay* unka8;
    ItemCreationOptionResourceDisplay* unkac;
    ItemCreationOptionResourceDisplay* unkb0;
};

/** Partial equipment panel window with a resident rectangle widget. */
struct EquipClass182790 : public FieldClass15AE70
{
    /** @brief Initialize the panel's Field base. */
    EquipClass182790()
    {
    }

    /** @brief Destroy the panel window. */
    virtual ~EquipClass182790();
    /** @brief Create and attach the panel display. @param associated Full resource source word. @return One. */
    virtual s32 func_slotf4(u32 associated);
};

struct EquipListState;
/** Partial view of a 0x114-byte resource record with its protected equipment entries. */
struct EquipResourceEquipment
{
    u8 unk00[0xC];
    s16 unk0c;
    s16 unk0e;
    s16 unk10[4];
    u8 unk18[0xD8];
    s32 unkf0;
    u8 unkf4[0x18];
    s32 unk10c;
    u8 unk110[4];
};
/** Partial item-details window with one header and five statistic rows. */
struct EquipClass182890 : public FieldClass15AE70
{
    /** @brief Initialize item comparison records and display pointers. @param state Owning equipment State. */
    EquipClass182890(EquipListState* state);
    /** @brief Refresh the selected item icon and both statistic columns. @param category Selected category. @param selected Selected item record index. */
    void refresh_item_details(u8 category, s16 selected);
    /** @brief Destroy the item-details window. */
    virtual ~EquipClass182890();
    /** @brief Create and attach the item-details displays. @param associated Full resource source word. @return One. */
    virtual s32 func_slotf4(u32 associated);
    EquipListState* unka8;
    u8 unkac;
    u8 unkad;
    s16 unkae;
    s16 unkb0;
    u8 unkb2;
    u8 unkb3;
    FieldRecord unkb4;
    /** Encoded resource record used for the comparison. */
    EquipResourceEquipment unk178;
    LibObject178750* unk28c;
    LibObject172410* unk290;
    LibObject178750* unk294[5];
    LibObject178750* unk2a8[5];
    LibObject178750* unk2bc[5];
    LibObject174F20* unk2d0[5];
    LibObject174F20* unk2e4[5];
};

/** Partial category panel window using a resident rectangle widget. */
struct EquipClass182A90 : public FieldClass15AE70
{
    /** @brief Initialize the category panel's Field base. */
    EquipClass182A90()
    {
    }

    /** @brief Destroy the category panel window. */
    virtual ~EquipClass182A90();
    /** @brief Create and attach the category panel display. @param associated Full resource source word. @return One. */
    virtual s32 func_slotf4(u32 associated);
};

struct EquipClass182B90;
struct EquipClass182990;
struct EquipPackedRecord;
struct EquipClass182670;
/** Partial equipment State with its selection, resource keys, and owned windows. */
struct EquipListState : public FieldClass153E30
{
    /** @brief Initialize the equipment State and its resource table entries. */
    EquipListState();
    /** @brief Destroy the equipment State. */
    virtual ~EquipListState();
    /** @brief Create and connect the equipment State displays. @return One after display setup. */
    virtual s32 init_windows();
    /** @brief Load an aligned resource and create the State displays. @param buffer Resource buffer. @return Display creation result, or zero for a null buffer. */
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
    s32 unk34;
    FieldRecordSelection* unk38;
    u8 unk3c_active : 1;
    u8 unk3c_other : 7;
    u8 unk3d[3];
    EquipClass182C90* unk40;
    EquipClass182990* unk44;
    EquipClass182890* unk48;
    EquipClass182790* unk4c;
    EquipClass182670* unk50;
    EquipClass182B90* unk54;
    u32 unk58;
    u32 unk5c;
    u16 unk60;
    u8 unk62[2];
    s32 unk64;
    void* unk68;
};

struct FieldState23B3A0;
/** Partial category detail window with multiline, label, and numeric displays. */
struct EquipClass182B90 : public FieldClass15AE70
{
    /** @brief Initialize the category detail state, labels, and numeric displays. */
    EquipClass182B90()
    {
        unkec = 0;
        unkf0 = 0;
        for (s32 i = 0; i < 5; i++)
        {
            unkb0[i] = 0;
            unkd8[i] = 0;
        }
    }

    /** @brief Destroy the category detail window. */
    virtual ~EquipClass182B90();
    /** @brief Refresh the selected category detail displays. */
    virtual void func_slot5c();
    /** @brief Create the multiline and comparison displays. @param associated Full resource source word. @return One, or zero without an associated object. */
    virtual s32 func_slotf4(u32 associated);
    LibObject174D90* unka8;
    LibObject178750* unkac;
    LibObject178750* unkb0[5];
    LibObject178750* unkc4[5];
    LibObject174F20* unkd8[5];
    s32 unkec;
    u8 unkf0;
};
/** Partial category window with its selector and associated list window. */
struct EquipClass182990 : public FieldClass15AE70
{
    /** @brief Initialize the category widgets and attach the State selection. @param state Owning equipment State. */
    EquipClass182990(EquipListState* state);
    /** @brief Destroy the category window. */
    virtual ~EquipClass182990();
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
    /** @brief Toggle the owning State display flag. @return One. */
    virtual u8 func_slotbc();
    /** @brief Cycle to the previous record and rebuild its displays. @return Four after cycling, or zero when unavailable. */
    virtual s32 func_slotd8();
    /** @brief Cycle to the next record and rebuild its displays. @return Four after cycling, or zero when unavailable. */
    virtual s32 func_slotdc();
    /** @brief Create category widgets. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
    EquipListState* unka8;
    FieldRecordSelection* unkac;
    float unkb0;
    EquipPackedRecord* unkb4;
    s16 unkb8[4];
    u8 unkc0;
    u8 unkc1[3];
    LibClass174EF0* unkc4[4];
    LibObject172410* unkd4[4];
    LibClass174EF0* unke4[4];
    void* unkf4;
    void* unkf8;
    FieldState23B3A0* equipment_slot_selector;
    FieldClass15AE70* unk100;
    FieldClass15AD40* unk104;
    u16 unk108;
};

/** Equipment list window using Field callbacks at offset 0xA8. */
struct EquipClass182550 : public FieldClass15AD40
{
    /** @brief Initialize list display pointers and attach the option State. @param state Owning equipment State. */
    EquipClass182550(EquipListState* state);
    /** @brief Destroy the Field list window. */
    virtual ~EquipClass182550();
    /** @brief Run the equipment list update hook. */
    virtual void func_slot5c();
    /** @brief Activate the selected record and restore the category window. @return One on success, or three when no record is selectable. */
    virtual u8 func_slotb0();
    /** @brief Restore the associated window and clear the detail display. @return Two. */
    virtual u8 func_slotb4();
    /** @brief Return the empty equipment selection result. @return Zero. */
    virtual u8 func_slotb8();
    /** @brief Toggle the linked display flag. @return One. */
    virtual u8 func_slotbc();
    /** @brief Refresh the visible equipment rows. @param start First record index. */
    virtual void refresh_rows(s32 start);
    /** @brief Set the visible equipment row positions. @param start Base row position. */
    virtual void set_scroll_position(float start);
    /** @brief Create the equipment list displays. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slot104(u32 associated);
    /** @brief Set the paired display flags. @param first First flag. @param second Second flag. */
    virtual void func_slot10c(u32 first, u32 second);
    /** @brief Recount the category records and clamp the visible selection. */
    void func_00349D50();
    ItemCreationOptionResourceDisplay* unk138[9];
    LibObject172410* unk15c[9];
    LibClass178630* unk180;
    void* unk184;
    EquipListState* unk188;
    void* unk18c;
    s16 unk190;
};

/** Equipment list window owning two counted lists. */
struct EquipClass182670 : public FieldClass15AD40
{
    /** @brief Initialize the display pointers and owned lists. @param state Owning equipment State. */
    EquipClass182670(EquipListState* state);
    /** @brief Destroy the owned lists and the Field window. */
    virtual ~EquipClass182670();
    /** @brief Update the selected category, row highlight, and detail window. */
    virtual void func_slot5c();
    /** @brief Activate the category list or create the selected record window. @return Selection result. */
    virtual u8 func_slotb0();
    /** @brief Restore the associated window and hide the alternate window. @return Two. */
    virtual u8 func_slotb4();
    virtual u8 func_slotbc();
    /** @brief Refresh category names, availability counts, and selection colors. @param start First category row. */
    virtual void refresh_rows(s32 start);
    /** @brief Position all three displays in each row. @param start Base row position. */
    virtual void set_scroll_position(float start);
    /** @brief Create the category names, counts, and selection displays. @param associated Full resource source word. @return One. */
    virtual s32 func_slot104(u32 associated);
    /** @brief Rebuild the list for the selected category. @param category Category index, clamped to two. */
    virtual void func_slot108(u8 category);
    virtual void func_slot10c(u32 first, u32 second);
    LibObject178750* unk138[9];
    LibObject174F20* unk15c[9];
    EquipListState* unk180;
    void* unk184;
    EquipWordList unk188;
    s16 unk194;
    EquipLinkedList unk198;
    FieldClass15AE70* unk1a4;
};

extern "C" {
#endif

/**
 * @brief Append a value to the linked list.
 * @param list List to update.
 * @param value Value to append.
 */
void func_003517D0(EquipLinkedList* list, u16 value);

/**
 * @brief Append a category-record pointer to the list.
 * @param list List to update.
 * @param value Category-record pointer, which may be null.
 */
void func_00351A20(EquipWordList* list, ItemCreationCategoryRecord* value);

/**
 * @brief Append a word value to the linked list.
 * @param list List to update.
 * @param value Value to append.
 */
void func_00351B70(FieldCountedList* list, void* value);

/**
 * @brief Append a word value to the linked list.
 * @param list List to update.
 * @param value Value to append.
 */
void func_00351C00(FieldCountedList* list, void* value);

/**
 * @brief Append a word value to the linked list.
 * @param list List to update.
 * @param value Value to append.
 */
void func_00351C90(FieldCountedList* list, void* value);

/**
 * @brief Append a word value to the linked list.
 * @param list List to update.
 * @param value Value to append.
 */
void func_00351D20(FieldCountedList* list, void* value);

/**
 * @brief Append a word value to the linked list.
 * @param list List to update.
 * @param value Value to append.
 */
void func_00351DB0(FieldCountedList* list, void* value);

/**
 * @brief Append a word value to the linked list.
 * @param list List to update.
 * @param value Value to append.
 */
void func_00351E40(FieldCountedList* list, void* value);

/**
 * @brief Advance from the first linked node by a number of steps.
 * @param object Holder of the linked list.
 * @param count Number of links to follow.
 * @return Reached node, or null if the chain ends early.
 */
void* func_003518E0(void* object, s32 count);

/**
 * @brief Advance from the first linked node by a number of steps.
 * @param object Holder of the linked list.
 * @param count Number of links to follow.
 * @return Reached node, or null if the chain ends early.
 */
void* func_00351B30(void* object, s32 count);

/**
 * @brief Delete the list nodes after the sentinel and reset the list count.
 * @param list List whose nodes should be released.
 */
void func_00351860(EquipLinkedList* list);

/**
 * @brief Delete the list nodes after the sentinel and reset the list count.
 * @param list List whose nodes should be released.
 */
void func_00351AB0(EquipWordList* list);

#ifdef __cplusplus
}
#endif

#endif
