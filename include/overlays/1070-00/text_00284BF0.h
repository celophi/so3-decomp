#ifndef SO3_OVERLAYS_1070_00_TEXT_00284BF0_H
#define SO3_OVERLAYS_1070_00_TEXT_00284BF0_H

#include "types.h"

/** Partial list node; the leading bytes and full object extent are unknown. */
typedef struct FieldListNode
{
    u8 unk00[8];
    struct FieldListNode* next;
} FieldListNode;

/** Partial Field context; the pointed-to object types and full extent are unknown. */
typedef struct FieldContext
{
    u8 unk00[4];
    void* unk04;
    u8 unk08[12];
    void* unk14;
    void* unk18;
    u8 unk1c[16];
    void* unk2c;
    void* unk30;
    u8 unk34[4];
    void* unk38;
    void* unk3c;
    void* unk40;
    u8 unk44[8];
    void* unk4c;
    u8 unk50[4];
    void* unk54;
    void* unk58;
    u8 unk5c[136];
    void* unke4;
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

#ifdef __cplusplus
}
#endif

#endif
