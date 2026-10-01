#ifndef SO3_OVERLAYS_1067_00_TEXT_0023DC90_H
#define SO3_OVERLAYS_1067_00_TEXT_0023DC90_H

#include "types.h"
#include "boot/resident_data.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Select the target word, retaining it for sentinel -2.
 * @param object Target receiver.
 * @param value Word to select.
 */
void func_00249AB0(void* object, s32 value);

/**
 * @brief Add one entry when the resident entry owner exists.
 * @param object Calling object; unused here.
 * @param value Value passed to the entry lookup.
 * @param strength Float setting for the new entry.
 */
void func_0024A030(void* object, void* value, float strength);


typedef struct FieldObject1533E0 FieldObject1533E0;
typedef struct FieldObject24B6B0 FieldObject24B6B0;
typedef struct FieldObject24C300 FieldObject24C300;

/** Partial target containing two signed bytes at offsets 8 and 9. */
typedef struct FieldPairAt08
{
    u8 unk00[8];
    s8 unk08;
    s8 unk09;
} FieldPairAt08;

/**
 * @brief Copy two signed bytes to a target when it exists.
 * @param owner Calling object; unused here.
 * @param target Target containing the byte pair.
 * @param first First byte.
 * @param second Second byte.
 */
void func_0024A8A0(void* owner, FieldPairAt08* target, s8 first, s8 second);

/**
 * @brief Return the current field context's attached object at offset 8.
 * @param ref Holder of the current field context.
 * @return The pointer held at context offset 8.
 */
ResidentContext08* func_0024B4B0(ResidentContextRef* ref);

/**
 * @brief Update the receiver value and notify its target when present.
 * @param object Receiver to update.
 * @param value New value, or -1 to keep the current value.
 */
void func_0024B6B0(FieldObject24B6B0* object, s32 value);

/**
 * @brief Handle the receiver's target.
 * @param object Receiver whose value is used by the handler.
 * @param target Target to handle.
 */
void func_0024B4D0(FieldObject24B6B0* object, void* target);

/**
 * @brief Run the first update when both receiver state bits are clear.
 * @param object Receiver to update.
 */
void func_0024C300(FieldObject24C300* object);

/**
 * @brief Run the second update when both receiver state bits are clear.
 * @param object Receiver to update.
 */
void func_0024C340(FieldObject24C300* object);

void func_00246960(FieldObject24C300* object);
void func_002468A0(FieldObject24C300* object);

/**
 * @brief Report the fixed category for this object.
 * @param object Receiver.
 * @return Always 2.
 */
s32 func_00249280(FieldObject1533E0* object);

#ifdef __cplusplus
}
#endif

#endif
