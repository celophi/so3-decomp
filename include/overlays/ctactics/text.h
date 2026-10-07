#ifndef SO3_OVERLAYS_CTACTICS_TEXT_H
#define SO3_OVERLAYS_CTACTICS_TEXT_H

#include "types.h"
#ifdef __cplusplus
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_001E1590.h"
struct FieldRecordSelection;
struct LibObject178750;
#endif

typedef struct FieldCountedList FieldCountedList;

typedef struct TacticsGridOwner TacticsGridOwner;
typedef struct TacticsPresetOwner TacticsPresetOwner;
typedef struct TacticsDualSelectionOwner TacticsDualSelectionOwner;

typedef struct TacticsPresetPosition
{
    float x;
    float y;
} TacticsPresetPosition;

typedef struct TacticsList18B8E0 TacticsList18B8E0;
typedef struct TacticsList18B8D0 TacticsList18B8D0;
typedef struct TacticsList18B8C0 TacticsList18B8C0;
typedef struct TacticsList18B8B0 TacticsList18B8B0;

#ifdef __cplusplus
/** Known native State prefix through its owned selection pointer at offset 3C. */
struct TacticsState18B820 : public FieldClass153E30
{
    /** @brief Destroy the State; its complete virtual tail remains unresolved. */
    virtual ~TacticsState18B820();
    /**
     * @brief Allocate and initialize the State's record selection.
     * @return One when a selection exists and initialization succeeds; otherwise zero.
     */
    virtual u8 func_00264110();
    /**
     * @brief Load the completed aligned resource using the State's heap context.
     * @param buffer Completed resource buffer, or null to report failure.
     * @return Zero for a null buffer; otherwise the virtual completion result.
     */
    virtual s32 func_001E1820(void* buffer);

    /** @brief Release the loaded resource, detach the State, and dispatch its release handler. */
    virtual void func_00263D80();

    s32 unk34;
    u8 unk38_0 : 1;
    u8 unk38_1_7 : 7;
    u8 unk39[3];
    FieldRecordSelection* selection;
};

/** Known native window interface used to initialize its resource displays. */
struct TacticsWindow18B720 : public FieldClass15AE70
{
    /** @brief Destroy the resource window. */
    virtual ~TacticsWindow18B720();
    /**
     * @brief Initialize the window and attach three resource displays.
     * @param associated Associated window context forwarded to the base initializer.
     * @return One after the displays are attached.
     */
    virtual s32 func_slotf4(void* associated);
};

/** Native 0xC4-byte scrolling window with its text widget and movement bounds. */
struct TacticsWindow18B620 : public FieldClass15AE70
{
    /** @brief Destroy the scrolling window. */
    virtual ~TacticsWindow18B620();
    /** @brief Hold the text position, then scroll and wrap it after the timer expires. */
    virtual void func_slot5c();
    /**
     * @brief Replace the text for supported keys and reset its scrolling state.
     * @param text_key Text key in the supported 2714..271B range.
     */
    virtual void func_slot60(s32 text_key);

    /**
     * @brief Initialize the scrolling window and its text displays.
     * @param associated Associated context forwarded to the base initializer.
     * @return One after initialization succeeds; otherwise zero.
     */
    virtual s32 func_slotf4(void* associated);

    LibObject178750* text;
    s32 distance;
    s16 timer;
    u8 state;
    float unkb4;
    float initial_x;
    float base_x;
    float width;
};

/** Native 0xC8-byte tactics window containing the coordinate selector. */
struct TacticsWindow18B520 : public FieldClass15AE70
{
    /** @brief Destroy the coordinate-selection window. */
    virtual ~TacticsWindow18B520();
    /** @brief Restore the selection movement or visibility state. */
    virtual void func_slot64();
    /** @brief Move to the preceding coordinate, wrapping after the first. */
    virtual void func_slot68();
    /** @brief Move to the following coordinate, wrapping after the eighth. */
    virtual void func_slot6c();
    /** @brief Map the last five coordinate entries to the first three. */
    virtual void func_slot70();
    /** @brief Map the first three coordinate entries to entries three, five, and six. */
    virtual void func_slot74();
    /** @brief Apply the selected coordinate. @return Selection action status. */
    virtual s32 func_slotb0();
    /** @brief Open the coordinate-selection child window. @return Window action status. */
    virtual s32 func_slotb4();
    /**
     * @brief Initialize the coordinate window and its resource displays.
     * @param associated Associated context forwarded to the base initializer.
     * @return One on success; otherwise zero.
     */
    virtual s32 func_slotf4(void* associated);

    void* unka8;
    void* unkac;
    struct FieldObject23B1D0* selection;
    s16 selected;
    u8 enabled[8];
    u8 unkbe[0xA];
};

/** Native 0xF8-byte tactics grid window with its text displays and cursor. */
struct TacticsWindow18B420 : public FieldClass15AE70
{
    /** @brief Initialize the grid window's pointers and control fields. */
    TacticsWindow18B420();
    /** @brief Destroy the grid window. */
    virtual ~TacticsWindow18B420();
    /** @brief Refresh the associated text when the grid selection changes. */
    virtual void func_slot5c();
    /** @brief Move to the preceding grid entry and refresh its highlight. */
    virtual void func_slot68();
    /** @brief Move to the following grid entry and refresh its highlight. */
    virtual void func_slot6c();
    /** @brief Apply the grid selection. @return Grid action status. */
    virtual s32 func_slotb0();
    /** @brief Close the grid window. @return Window action status. */
    virtual s32 func_slotb4();
    /**
     * @brief Initialize the grid and its resource displays.
     * @param associated Associated context forwarded to the base initializer.
     * @return One on success; otherwise zero.
     */
    virtual s32 func_slotf4(void* associated);

    void* unka8;
    void* unkac;
    struct FieldObject23CEA0* grid;
    s16 selected;
    u8 unkb6[2];
    LibObject178750* text[6];
    u8 unkd0[4];
    struct ItemCreationClass172600* unkd4;
    struct FieldObject23BE00* cursor;
    s32 keys[6];
    s16 unkf4;
    u8 unkf6;
};

/** Sentinel list owning its nodes and recording their count. */
struct TacticsList18B8E0
{
    struct TacticsListNode* head;
    u32 count;
    /** @brief Initialize an empty list and allocate its sentinel. */
    TacticsList18B8E0();
    /** @brief Release list nodes and the sentinel. */
    virtual ~TacticsList18B8E0();
};
/** Sentinel list owning its nodes and recording their count. */
struct TacticsList18B8D0
{
    struct TacticsListNode* head;
    u32 count;
    /** @brief Initialize an empty list and allocate its sentinel. */
    TacticsList18B8D0();
    /** @brief Release list nodes and the sentinel. */
    virtual ~TacticsList18B8D0();
};
/** Sentinel list owning its nodes and recording their count. */
struct TacticsList18B8C0
{
    struct TacticsListNode* head;
    u32 count;
    /** @brief Initialize an empty list and allocate its sentinel. */
    TacticsList18B8C0();
    /** @brief Release list nodes and the sentinel. */
    virtual ~TacticsList18B8C0();
};
/** Sentinel list owning its nodes and recording their count. */
struct TacticsList18B8B0
{
    struct TacticsCoordinateNode* head;
    u32 count;
    /** @brief Initialize an empty list and allocate its sentinel. */
    TacticsList18B8B0();
    /** @brief Release list nodes and the sentinel. */
    virtual ~TacticsList18B8B0();
};
/** Native 0x17C-byte tactics window owning two binary buffers and eleven lists. */
struct TacticsWindow18B320 : public FieldClass15AE70
{
    /** @brief Construct the owned lists and clear the window control fields. */
    TacticsWindow18B320();
    /** @brief Release both binary buffers, then destroy the lists and base window. */
    virtual ~TacticsWindow18B320();
    /** @brief Refresh the active selector and associated text. */
    virtual void func_slot5c();
    /** @brief Move the chosen selector to its preceding entry. */
    virtual void func_slot68();
    /** @brief Move the chosen selector to its following entry. */
    virtual void func_slot6c();
    /** @brief Map the chosen selector's last five entries to its first three. */
    virtual void func_slot70();
    /** @brief Map the chosen selector's first three entries to entries three, five, and six. */
    virtual void func_slot74();
    /** @brief Apply the chosen selector's entry. @return Selection action status. */
    virtual s32 func_slotb0();
    /** @brief Open the chosen selector's child window. @return Window action status. */
    virtual s32 func_slotb4();
    /**
     * @brief Initialize the selectors, their buffers, and the resource displays.
     * @param associated Associated context forwarded to the base initializer.
     * @return One on success; otherwise zero.
     */
    virtual s32 func_slotf4(void* associated);

    void* unka8;
    void* unkac;
    u8* bufferc4;
    u8* buffer114;
    struct FieldObject23B1D0* first;
    struct FieldObject23B1D0* second;
    u8 use_second;
    u8 unkc1;
    s16 unkc2;
    s16 unkc4;
    u8 unkc6[2];
    TacticsList18B8C0 unkc8;
    TacticsList18B8D0 unkd4;
    TacticsList18B8C0 unke0;
    TacticsList18B8C0 unkec;
    TacticsList18B8D0 unkf8;
    TacticsList18B8C0 unk104;
    TacticsList18B8D0 unk110;
    TacticsList18B8D0 unk11c;
    TacticsList18B8C0 unk128;
    TacticsList18B8D0 unk134;
    TacticsList18B8E0 unk140;
    s16 unk14c[8];
    u8 unk15c[0x20];
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Append an unowned value pointer to the counted list.
 * @param list Sentinel list receiving the new node.
 * @param value Value pointer stored without transferring ownership.
 */
void func_003515A0(FieldCountedList* list, void* value);

/**
 * @brief Append an unowned value pointer to the counted list.
 * @param list Sentinel list receiving the new node.
 * @param value Value pointer stored without transferring ownership.
 */
void func_00351630(FieldCountedList* list, void* value);

/**
 * @brief Append an unowned value pointer to the counted list.
 * @param list Sentinel list receiving the new node.
 * @param value Value pointer stored without transferring ownership.
 */
void func_003516C0(FieldCountedList* list, void* value);

/**
 * @brief Append an unowned value pointer to the counted list.
 * @param list Sentinel list receiving the new node.
 * @param value Value pointer stored without transferring ownership.
 */
void func_00351890(FieldCountedList* list, void* value);

/**
 * @brief Append an unowned value pointer to the counted list.
 * @param list Sentinel list receiving the new node.
 * @param value Value pointer stored without transferring ownership.
 */
void func_00351AE0(FieldCountedList* list, void* value);

/**
 * @brief Append an unowned value pointer to the counted list.
 * @param list Sentinel list receiving the new node.
 * @param value Value pointer stored without transferring ownership.
 */
void func_00351C30(FieldCountedList* list, void* value);

/**
 * @brief Append an unowned value pointer to the counted list.
 * @param list Sentinel list receiving the new node.
 * @param value Value pointer stored without transferring ownership.
 */
void func_00351CC0(FieldCountedList* list, void* value);

/**
 * @brief Append a coordinate pair to the owned list.
 * @param list Sentinel list receiving the new node.
 * @param value Coordinate pair copied into the new node.
 */
void func_00351E50(TacticsList18B8B0* list, TacticsPresetPosition value);

/**
 * @brief Release all value nodes, preserving the sentinel.
 * @param list List whose nodes and element count are cleared.
 */
void func_00351520(TacticsList18B8E0* list);

/**
 * @brief Release all value nodes, preserving the sentinel.
 * @param list List whose nodes and element count are cleared.
 */
void func_00351920(TacticsList18B8D0* list);

/**
 * @brief Release all value nodes, preserving the sentinel.
 * @param list List whose nodes and element count are cleared.
 */
void func_00351B70(TacticsList18B8C0* list);

/**
 * @brief Release all value nodes, preserving the sentinel.
 * @param list List whose nodes and element count are cleared.
 */
void func_00351DD0(TacticsList18B8B0* list);

/**
 * @brief Save the enabled grid selection and copy its node position to the display.
 * @param object Tactics receiver holding the grid, node list, and display target.
 * @return Zero when the grid's control byte is clear; otherwise one.
 */
u8 func_00349B40(TacticsGridOwner* object);

/**
 * @brief Color up to six list displays and place the cursor for the selected grid entry.
 * @param object Tactics receiver holding the display list, grid, and cursor.
 */
void func_0034DD10(TacticsWindow18B420* object);

/**
 * @brief Place the present indicators using the selected grid row's coordinate pairs.
 * @param object Tactics receiver holding the grid, indicators, and base coordinates.
 */
void func_00349EB0(TacticsGridOwner* object);

/**
 * @brief Advance the chosen selector one entry, wrapping after its eighth entry.
 * @param object Tactics receiver containing two selectors and the selector choice byte.
 */
void func_0034AFB0(TacticsDualSelectionOwner* object);

/**
 * @brief Move the chosen selector back one entry, wrapping to its eighth entry.
 * @param object Tactics receiver containing two selectors and the selector choice byte.
 */
void func_0034B020(TacticsDualSelectionOwner* object);

/**
 * @brief Map the chosen selector's first three entries to entries three, five, and six.
 * @param object Tactics receiver containing two selectors and the selector choice byte.
 */
void func_0034B080(TacticsDualSelectionOwner* object);

/**
 * @brief Map the chosen selector's last five entries back to its first three.
 * @param object Tactics receiver containing two selectors and the selector choice byte.
 */
void func_0034B120(TacticsDualSelectionOwner* object);

/**
 * @brief Enqueue the receiver for deferred processing.
 * @param object Receiver to append to the resident object queue.
 */
void func_00350790(void* object);

/**
 * @brief Select a preset display position, clearing it for an invalid index.
 * @param object Receiver holding the position pair.
 * @param index Zero-based preset index.
 * @return The receiver's updated position pair.
 */
TacticsPresetPosition* func_0034F190(TacticsPresetOwner* object, s32 index);

typedef struct TacticsListNode
{
    void* value;
    struct TacticsListNode* next;
#ifdef __cplusplus
    /** @brief Finish the node lifetime; the stored value is not owned. */
    ~TacticsListNode() {}
#endif
} TacticsListNode;

typedef struct TacticsList
{
    TacticsListNode* head;
} TacticsList;

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348400(void* object);

/**
 * @brief Mark each icon active and color the selected one differently.
 * @param object Holder of the icon list.
 * @param selected Index of the icon to color differently.
 */
void func_00348410(void* object, s16 selected);

/**
 * @brief Return the field at byte offset 0x20.
 * @param object Object containing the field.
 * @return The field value.
 */
u32 func_003484C0(void* object);

/**
 * @brief Store the field at byte offset 0x20.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_00348630(void* object, u32 value);

/**
 * @brief Return the field at byte offset 0x9C.
 * @param object Object containing the field.
 * @return The field value.
 */
u32 func_003499A0(void* object);

/**
 * @brief Return the field at byte offset 0x4.
 * @param object Object containing the field.
 * @return The field value.
 */
u32 func_00349B30(void* object);

/**
 * @brief Set the fields of two optional linked objects.
 * @param object Object containing the linked fields.
 */
void func_00349E70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0034DCF0(void* object);

/**
 * @brief Return the field at byte offset 0x24.
 * @param object Object containing the field.
 * @return The field value.
 */
u32 func_0034DD00(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003507B0(void* object);

/**
 * @brief Store the field at byte offset 0x9C.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_00350D10(void* object, u32 value);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00351020(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_00351030(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00351040(void* object);

/**
 * @brief Store the field at byte offset 0xC.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_00351050(void* object, u8 value);

/**
 * @brief Return the field at byte offset 0xC.
 * @param object Object containing the field.
 * @return The field value.
 */
u8 func_00351060(void* object);

/**
 * @brief Store the field at byte offset 0x8.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_00351070(void* object, u8 value);

/**
 * @brief Return the field at byte offset 0x8.
 * @param object Object containing the field.
 * @return The field value.
 */
u8 func_00351080(void* object);

/**
 * @brief Store the field at byte offset 0xA.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_00351090(void* object, u16 value);

/**
 * @brief Return the field at byte offset 0xA.
 * @param object Object containing the field.
 * @return The field value.
 */
u16 func_003510A0(void* object);

/**
 * @brief Store the field at byte offset 0x4.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_003510B0(void* object, u32 value);

/**
 * @brief Return the field at byte offset 0x10.
 * @param object Object containing the field.
 * @return The field value.
 */
u32 func_003510C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003510D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003510E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003510F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00351100(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00351110(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00351120(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00351130(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00351140(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00351150(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00351160(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00351170(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00351180(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00351190(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003511A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003511B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003511C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003511D0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003511E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003511F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00351200(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00351210(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00351220(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00351230(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00351240(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00351250(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00351260(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00351270(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00351280(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00351290(void* object);

/**
 * @brief Return the field at byte offset 0xD.
 * @param object Object containing the field.
 * @return The field value.
 */
u8 func_003512A0(void* object);

/**
 * @brief Store the field at byte offset 0xD.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_003512B0(void* object, u8 value);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003512C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003512D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003512E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003512F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00351300(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00351310(void* object);

/**
 * @brief Return bit zero of the byte at offset 0x38.
 * @param object Object containing the field.
 * @return The field value.
 */
u32 func_00351320(void* object);

/**
 * @brief Return the field at byte offset 0x34.
 * @param object Object containing the field.
 * @return The field value.
 */
u32 func_00351330(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00351340(void* object);

/**
 * @brief Store the field at byte offset 0x24.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_00351350(void* object, u32 value);

/**
 * @brief Store the field at byte offset 0x28.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_00351360(void* object, u8 value);

/**
 * @brief Return the field at byte offset 0x28.
 * @param object Object containing the field.
 * @return The field value.
 */
s8 func_00351370(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00351380(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00351390(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003513A0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003513B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003513C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003513D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003513E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003513F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00351400(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00351410(void* object);

/**
 * @brief Return the node at an index in a linked list.
 * @param list List containing the nodes.
 * @param index Zero-based node index.
 * @return The node, or null if the list ends before the index.
 */
TacticsListNode* func_00351750(TacticsList* list, s32 index);

/**
 * @brief Return the node at an index in a linked list.
 * @param list List containing the nodes.
 * @param index Zero-based node index.
 * @return The node, or null if the list ends before the index.
 */
TacticsListNode* func_003519A0(TacticsList* list, s32 index);

/**
 * @brief Return the node at an index in a linked list.
 * @param list List containing the nodes.
 * @param index Zero-based node index.
 * @return The node, or null if the list ends before the index.
 */
TacticsListNode* func_00351BF0(TacticsList* list, s32 index);

#ifdef __cplusplus
}
#endif

#endif
