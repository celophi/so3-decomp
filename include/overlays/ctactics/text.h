#ifndef SO3_OVERLAYS_CTACTICS_TEXT_H
#define SO3_OVERLAYS_CTACTICS_TEXT_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TacticsListNode
{
    void* value;
    struct TacticsListNode* next;
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
