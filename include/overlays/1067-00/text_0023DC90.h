#ifndef SO3_OVERLAYS_1067_00_TEXT_0023DC90_H
#define SO3_OVERLAYS_1067_00_TEXT_0023DC90_H

#include "types.h"
#include "boot/resident_data.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Partial object passed to func_00249880, with a target at offset 0x80 and state flags at offset 0x590. */
typedef struct FieldObject24B6B0
{
    u8 unk00[0x80];
    void* target;
    u32 unk84;
    s32 value;
    u8 unk8c[0x504];
    u8 unk590_0 : 1;
    u8 unk590_1 : 1;
    u8 unk590_2 : 1;
    u8 unk590_3 : 1;
    u8 unk590_4_7 : 4;
} FieldObject24B6B0;
typedef struct FieldObject24B4C0 FieldObject24B4C0;
typedef struct FieldObject24B490 FieldObject24B490;
typedef struct FieldObject24C380 FieldObject24C380;

/**
 * @brief Process the receiver when it has a target and an active resident entry.
 * @param object Receiver to process.
 * @param value Value passed to the field helper.
 */
void func_00249880(FieldObject24B6B0* object, const void* value);

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

typedef struct FieldObject24A410 FieldObject24A410;

/**
 * @brief Clear the receiver state and detach its linked object when present.
 * @param object Receiver to reset.
 */
void func_0024A410(FieldObject24A410* object);

typedef struct FieldObject1533E0 FieldObject1533E0;
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
 * @brief Read the linked pointer at receiver offset 0x7C.
 * @param object Receiver containing the pointer.
 * @return The linked pointer.
 */
void* func_0024B490(const FieldObject24B490* object);

/**
 * @brief Read the pointer at offset 0xDC of a resident context.
 * @param context Context containing the pointer.
 * @return The context pointer at offset 0xDC.
 */
void* func_0024B4A0(const ResidentContext08* context);

/**
 * @brief Read the receiver's halfword at offset 0x6C.
 * @param object Receiver containing the halfword.
 * @return The unsigned halfword value.
 */
u16 func_0024B4C0(const FieldObject24B4C0* object);

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

/**
 * @brief Get the address of the receiver field at offset 0x120.
 * @param object Receiver containing the field.
 * @return Address of the field.
 */
void* func_0024C380(FieldObject24C380* object);

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
