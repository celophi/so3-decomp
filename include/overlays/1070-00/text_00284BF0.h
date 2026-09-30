#ifndef SO3_OVERLAYS_1070_00_TEXT_00284BF0_H
#define SO3_OVERLAYS_1070_00_TEXT_00284BF0_H

#include "types.h"

/** Partial list node; the leading bytes and full object extent are unknown. */
typedef struct FieldListNode
{
    u8 unk00[8];
    struct FieldListNode* next;
} FieldListNode;

/** Four adjacent floating-point components observed in vector operations. */
typedef struct FieldVector
{
    float x;
    float y;
    float z;
    float w;
} FieldVector;

/** Partial object reached through context field 0xE4; full extent is unknown. */
typedef struct FieldContextE4
{
    u8 unk00[0xB4];
    u8 unkb4[0x8C];
    char unk140[1];
} FieldContextE4;

/** Partial object reached through context field 0x38. */
typedef struct FieldContext38
{
    u8 unk00[0x5C0];
    void* unk5c0;
    void* unk5c4;
} FieldContext38;

/** Partial object reached through context field 0x18. */
typedef struct FieldContext18
{
    u8 unk00[0x3A0];
    void* unk3a0;
} FieldContext18;

/** Partial object reached through context field 0x58. */
typedef struct FieldContext58
{
    u8 unk00[0x1B4];
    s32 unk1b4;
} FieldContext58;

/** Common prefix used by the observed halfword flag accessors. */
typedef struct FieldObjectFlags
{
    u8 unk00[0x6C];
    u16 unk6c;
    u16 unk6e;
} FieldObjectFlags;

/** Partial state object allocated by the observed callers. */
typedef struct FieldWordState
{
    u8 unk00[0x2C];
    s32 unk2c;
} FieldWordState;

/** Partial embedded byte state; the surrounding object is unresolved. */
typedef struct FieldByteState
{
    u8 unk00[4];
    u8 unk04;
} FieldByteState;

/** Partial link object with an observed receiver pointer at offset 0x18. */
typedef struct FieldLinkedObject
{
    u8 unk00[0x18];
    void* unk18;
} FieldLinkedObject;

/** Partial object whose byte at 0x49 supplies a flag. */
typedef struct FieldFlaggedObject
{
    u8 unk00[0x49];
    u8 unk49;
} FieldFlaggedObject;

/** Partial owner of the object passed to the flag accessor. */
typedef struct FieldFlaggedObjectRef
{
    u8 unk00[0x1C];
    FieldFlaggedObject* unk1c;
} FieldFlaggedObjectRef;

/** Partial Field context; the pointed-to object types and full extent are unknown. */
typedef struct FieldContext
{
    u8 unk00[4];
    void* unk04;
    u8 unk08[12];
    void* unk14;
    FieldContext18* unk18;
    u8 unk1c[16];
    void* unk2c;
    void* unk30;
    u8 unk34[4];
    FieldContext38* unk38;
    void* unk3c;
    void* unk40;
    u8 unk44[8];
    void* unk4c;
    u8 unk50[4];
    void* unk54;
    FieldContext58* unk58;
    u8 unk5c[0x84];
    void* unke0;
    FieldContextE4* unke4;
} FieldContext;

/** Reference to the Field context shared by the observed accessor callers. */
typedef struct FieldContextRef
{
    FieldContext* context;
} FieldContextRef;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Test whether a list traversal has reached its sentinel.
 * @param sentinel List sentinel.
 * @param node Current node.
 * @return 1 if node is the sentinel, otherwise 0.
 */
s32 func_00288650(const void* sentinel, const void* node);

/**
 * @brief Get the next node in a circular list traversal.
 * @param node Current node or list sentinel.
 * @return Next node, which may be the list sentinel.
 */
FieldListNode* func_00288660(const FieldListNode* node);

/**
 * @brief Get the referenced Field context.
 * @param ref Reference to the Field context.
 * @return The context pointer.
 */
FieldContext* func_00288640(const FieldContextRef* ref);

/**
 * @brief Return the supplied object pointer.
 * @param object Object or subobject pointer.
 * @return The same pointer.
 */
void* func_00288670(void* object);

/**
 * @brief Read the Field context pointer at offset 0xE4.
 * @param ref Reference to the Field context.
 * @return The stored object pointer.
 */
void* func_00288690(const FieldContextRef* ref);

/**
 * @brief Return the supplied object pointer.
 * @param object Object or subobject pointer.
 * @return The same pointer.
 */
void* func_00289460(void* object);

/**
 * @brief Return the supplied object pointer.
 * @param object Object or subobject pointer.
 * @return The same pointer.
 */
void* func_002899C0(void* object);

/**
 * @brief Read the Field context pointer at offset 0x58.
 * @param ref Reference to the Field context.
 * @return The stored object pointer.
 */
void* func_00289D00(const FieldContextRef* ref);

/**
 * @brief Read the Field context pointer at offset 0x38.
 * @param ref Reference to the Field context.
 * @return The stored object pointer.
 */
void* func_00289D50(const FieldContextRef* ref);

/**
 * @brief Read the Field context pointer at offset 0x30.
 * @param ref Reference to the Field context.
 * @return The stored object pointer.
 */
void* func_0028A810(const FieldContextRef* ref);

/**
 * @brief Read the Field context pointer at offset 0x40.
 * @param ref Reference to the Field context.
 * @return The stored object pointer.
 */
void* func_0028A820(const FieldContextRef* ref);

/**
 * @brief Read the Field context pointer at offset 0x2C.
 * @param ref Reference to the Field context.
 * @return The stored object pointer.
 */
void* func_0028A830(const FieldContextRef* ref);

/**
 * @brief Read the Field context pointer at offset 0x18.
 * @param ref Reference to the Field context.
 * @return The stored object pointer.
 */
void* func_0028A8C0(const FieldContextRef* ref);

/**
 * @brief Read the Field context pointer at offset 0x3C.
 * @param ref Reference to the Field context.
 * @return The stored object pointer.
 */
void* func_0028B1A0(const FieldContextRef* ref);

/**
 * @brief Read the Field context pointer at offset 0x14.
 * @param ref Reference to the Field context.
 * @return The stored object pointer.
 */
void* func_0028B1B0(const FieldContextRef* ref);

/**
 * @brief Read the Field context pointer at offset 0x54.
 * @param ref Reference to the Field context.
 * @return The stored object pointer.
 */
void* func_0028B1D0(const FieldContextRef* ref);

/**
 * @brief Read the Field context pointer at offset 0x04.
 * @param ref Reference to the Field context.
 * @return The stored object pointer.
 */
void* func_0028B1E0(const FieldContextRef* ref);

/**
 * @brief Read the Field context pointer at offset 0x4C.
 * @param ref Reference to the Field context.
 * @return The stored object pointer.
 */
void* func_0028B1F0(const FieldContextRef* ref);

/**
 * @brief Set all four vector components to one value.
 * @param vector Destination vector.
 * @param value Component value.
 * @return The destination vector.
 */
FieldVector* func_00286060(FieldVector* vector, float value);

/**
 * @brief Get the embedded character data at offset 0x140.
 * @param object Object reached through context field 0xE4.
 * @return Start of the character data; its full extent is unknown.
 */
char* func_00288680(FieldContextE4* object);

/**
 * @brief Set the context object pointer at offset 0xE0.
 * @param ref Reference to the Field context.
 * @param object Object pointer to store.
 */
void func_002886B0(const FieldContextRef* ref, void* object);

/**
 * @brief Get an indexed four-component vector.
 * @param vectors Contiguous vector elements.
 * @param index Element index.
 * @return The selected vector.
 */
FieldVector* func_00289830(FieldVector* vectors, s32 index);

/**
 * @brief Mask the halfword flags at offset 0x6C.
 * @param object Object containing the flags.
 * @param mask Bits to retain.
 */
void func_002899A0(FieldObjectFlags* object, u16 mask);

/**
 * @brief Set the halfword value at offset 0x6E.
 * @param object Object containing the halfword.
 * @param value Value whose low 16 bits are stored.
 */
void func_002899B0(FieldObjectFlags* object, s32 value);

/**
 * @brief Clear the object pointer at offset 0x5C4.
 * @param object Object reached through context field 0x38.
 */
void func_00289D40(FieldContext38* object);

/**
 * @brief Set the state word at offset 0x2C.
 * @param object State object.
 * @param value State value to store.
 */
void func_0028A290(FieldWordState* object, s32 value);

/**
 * @brief Read the embedded state byte at offset 0x04.
 * @param object Embedded byte state.
 * @return The stored byte.
 */
u8 func_0028A800(const FieldByteState* object);

/**
 * @brief Read the object pointer at offset 0x3A0.
 * @param object Object reached through context field 0x18.
 * @return The stored object pointer.
 */
void* func_0028A8B0(const FieldContext18* object);

/**
 * @brief Get the embedded receiver at offset 0xB4.
 * @param object Object reached through context field 0xE4.
 * @return The embedded receiver.
 */
void* func_0028A8D0(FieldContextE4* object);

/**
 * @brief Test whether the state word equals the -2 sentinel.
 * @param object Object reached through context field 0x58.
 * @return One when the state is -2, otherwise zero.
 */
s32 func_0028B150(const FieldContext58* object);

/**
 * @brief Set the linked receiver pointer.
 * @param object Link object.
 * @param receiver Receiver pointer to store.
 */
void func_0028B1C0(FieldLinkedObject* object, void* receiver);

/**
 * @brief Read bit zero of the byte at offset 0x49.
 * @param object Object containing the flag byte.
 * @return The flag as zero or one.
 */
s32 func_0028B200(const FieldFlaggedObject* object);

/**
 * @brief Get the referenced object containing the flag byte.
 * @param object Reference owner.
 * @return The stored object pointer.
 */
FieldFlaggedObject* func_0028B210(const FieldFlaggedObjectRef* object);

/**
 * @brief Clear the object pointer at offset 0x5C0.
 * @param object Object reached through context field 0x38.
 */
void func_0028B240(FieldContext38* object);

#ifdef __cplusplus
}
#endif

#endif
