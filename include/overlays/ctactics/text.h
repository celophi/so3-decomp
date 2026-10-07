#ifndef SO3_OVERLAYS_CTACTICS_TEXT_H
#define SO3_OVERLAYS_CTACTICS_TEXT_H

#include "types.h"

typedef struct TacticsPositionOwner TacticsPositionOwner;
typedef struct TacticsGridOwner TacticsGridOwner;
typedef struct TacticsHighlightOwner TacticsHighlightOwner;
typedef struct TacticsPresetOwner TacticsPresetOwner;
typedef struct TacticsSelectionOwner TacticsSelectionOwner;
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
#endif

#ifdef __cplusplus
extern "C" {
#endif

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
void func_0034DD10(TacticsHighlightOwner* object);

/**
 * @brief Place the present indicators using the selected grid row's coordinate pairs.
 * @param object Tactics receiver holding the grid, indicators, and base coordinates.
 */
void func_00349EB0(TacticsGridOwner* object);

/**
 * @brief Advance the enabled coordinate selector, wrapping after its eighth entry.
 * @param object Tactics receiver holding the coordinate selector.
 */
void func_0034EC80(TacticsSelectionOwner* object);

/**
 * @brief Move the enabled coordinate selector back, wrapping to its eighth entry.
 * @param object Tactics receiver holding the coordinate selector.
 */
void func_0034ECD0(TacticsSelectionOwner* object);

/**
 * @brief Map the first three selector entries to entries three, five, and six.
 * @param object Tactics receiver holding the enabled coordinate selector.
 */
void func_0034ED20(TacticsSelectionOwner* object);

/**
 * @brief Map the last five selector entries back to the first three.
 * @param object Tactics receiver holding the enabled coordinate selector.
 */
void func_0034EDA0(TacticsSelectionOwner* object);

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
 * @brief Hold the display position until its timer expires, then scroll and wrap it.
 * @param object Tactics state containing the display receiver and movement bounds.
 */
void func_0034FD60(TacticsPositionOwner* object);

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
 * @brief Return the field at byte offset 0x98.
 * @param object Object containing the field.
 * @return The field value.
 */
u32 func_00348640(void* object);

/**
 * @brief Return the field at byte offset 0x9C.
 * @param object Object containing the field.
 * @return The field value.
 */
u32 func_003499A0(void* object);

/**
 * @brief Store the field at byte offset 0x98.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_00349B20(void* object, u32 value);

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
 * @brief Update a linked object according to the signed state field.
 * @param object Object containing the linked fields.
 */
void func_0034EC30(void* object);

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
