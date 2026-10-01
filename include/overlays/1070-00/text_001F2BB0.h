#ifndef SO3_OVERLAYS_1070_00_TEXT_001F2BB0_H
#define SO3_OVERLAYS_1070_00_TEXT_001F2BB0_H

#include "types.h"
/** Common node prefix used by the indexed lists; full extent is unknown. */
typedef struct FieldIndexedListNode
{
    void* value;
    struct FieldIndexedListNode* next;
} FieldIndexedListNode;
/** Partial indexed list with a stored head node. */
typedef struct FieldIndexedList
{
    FieldIndexedListNode* head;
} FieldIndexedList;

/** Partial owner containing the starting value for a float transition. */
typedef struct FieldFloatOwner544
{
    u8 unk00[0x544];
    float unk544;
} FieldFloatOwner544;

/** Partial receiver containing float transitions and their word flags. */
typedef struct FieldFloatTransitions70
{
    FieldFloatOwner544* owner;
    u8 unk04[0x6C];
    u32 unk70;
    float unk74;
    float unk78;
    float unk7c;
    u8 unk80[0x30];
    float unkb0;
    float unkb4;
    u8 unkb8[4];
    float unkbc;
    float unkc0;
    float unkc4;
    u8 unkc8[0x18];
    float unke0;
    float unke4;
    float unke8;
    float unkec;
    u8 unkf0[4];
    float unkf4;
    float unkf8;
    u8 unkfc[8];
    float unk104;
    float unk108;
    u8 unk10c[4];
    float unk110;
    float unk114;
    float unk118;
} FieldFloatTransitions70;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Return the supplied object pointer.
 * @param object Object or subobject pointer.
 * @return The same pointer.
 */
void* func_001FAD90(void* object);

/**
 * @brief Find a node by advancing from the first list element.
 * @param list List with a non-null head node.
 * @param index Number of links to advance; nonpositive values select the first node.
 * @return The selected node, or null if the chain ends first.
 */
FieldIndexedListNode* func_001FA7A0(const FieldIndexedList* list, s32 index);

/**
 * @brief Find a node by advancing from the first list element.
 * @param list List with a non-null head node.
 * @param index Number of links to advance; nonpositive values select the first node.
 * @return The selected node, or null if the chain ends first.
 */
FieldIndexedListNode* func_001FA8A0(const FieldIndexedList* list, s32 index);

/**
 * @brief Initialize a float transition from its owner value.
 * @param object Receiver containing the transition state.
 * @param target Requested endpoint.
 * @param duration Transition duration; nonpositive values use the unscaled difference.
 */
void func_001FE6D0(FieldFloatTransitions70* object, float target, float duration);

/**
 * @brief Initialize a float transition from the value at offset 0xF8.
 * @param object Receiver containing the transition state.
 * @param target Requested endpoint; the 0x7F7FFFFF float sentinel selects the saved endpoint.
 * @param duration Transition duration; zero leaves the difference unscaled.
 */
void func_001FEB00(FieldFloatTransitions70* object, float target, float duration);

/**
 * @brief Initialize a float transition from the value at offset 0xF4.
 * @param object Receiver containing the transition state.
 * @param target Requested endpoint; the 0x7F7FFFFF float sentinel selects the saved endpoint.
 * @param duration Transition duration; zero leaves the difference unscaled.
 */
void func_001FEB70(FieldFloatTransitions70* object, float target, float duration);

/**
 * @brief Initialize a float transition or apply its endpoint immediately.
 * @param object Receiver containing the transition state.
 * @param target Requested endpoint.
 * @param duration Transition duration; zero applies the endpoint immediately.
 */
void func_001FEBE0(FieldFloatTransitions70* object, float target, float duration);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001F9E40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001F9E50(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001F9E60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001F9E70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001F9E80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001F9E90(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001F9EA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001F9EB0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F9EC0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F9ED0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001FAFC0(void* object);

/**
 * @brief Return the fixed value 14.
 * @param object Receiver or first argument; unused.
 * @return Always 14.
 */
s32 func_001FBDF0(void* object);

/**
 * @brief Return the fixed value 5.
 * @param object Receiver or first argument; unused.
 * @return Always 5.
 */
s32 func_001FE2D0(void* object);

/**
 * @brief Return the fixed value 14.
 * @param object Receiver or first argument; unused.
 * @return Always 14.
 */
s32 func_001FE370(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002010C0(void* object);

#ifdef __cplusplus
}
#endif

#endif
