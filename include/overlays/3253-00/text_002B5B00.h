#ifndef SO3_OVERLAYS_3253_00_TEXT_002B5B00_H
#define SO3_OVERLAYS_3253_00_TEXT_002B5B00_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
void func_002B60A0(u8* receiver, void* value1, void* value2, void* value3);
#endif

/**
 * @brief Count the set entries for the supplied object.
 * @param object Input object.
 * @return Number of set entries.
 */
s32 func_002B6600(void* object);

/**
 * @brief Return one when the receiver's virtual list contains a non-null entry.
 * @param object Receiver with a virtual list getter.
 * @return One if a list entry is non-null; otherwise zero.
 */
s32 func_002B6580(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_002B5C80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B5C90(void* object);

/**
 * @brief Initialize a non-null receiver's vtable chain and activate it for a positive value.
 * @param receiver Object to initialize.
 * @param value Signed value controlling activation.
 * @return The receiver pointer.
 */
void* func_002B5CE0(void* receiver, s16 value);

/**
 * @brief Initialize a non-null receiver's vtable chain and activate it for a positive value.
 * @param receiver Object to initialize.
 * @param value Signed value controlling activation.
 * @return The receiver pointer.
 */
void* func_002B5D80(void* receiver, s16 value);

/**
 * @brief Initialize a non-null receiver's vtable chain and activate it for a positive value.
 * @param receiver Object to initialize.
 * @param value Signed value controlling activation.
 * @return The receiver pointer.
 */
void* func_002B6100(void* receiver, s16 value);

/**
 * @brief Initialize a non-null receiver's vtable chain and activate it for a positive value.
 * @param receiver Object to initialize.
 * @param value Signed value controlling activation.
 * @return The receiver pointer.
 */
void* func_002B6270(void* receiver, s16 value);

/**
 * @brief Set two output values when the input field at offset 4 is positive.
 * @param object Unused first argument.
 * @param value Object containing the input float.
 * @param result0 First output float.
 * @param result1 Second output float.
 * @return One when outputs are set; otherwise zero.
 */
s32 func_002B5CA0(void* object, const void* value, float* result0, float* result1);

/**
 * @brief Return the fixed value 14.
 * @param object Receiver or first argument; unused.
 * @return Always 14.
 */
s32 func_002B5D70(void* object);

/**
 * @brief Return the helper result for the child at receiver offset 0x194.
 * @param receiver Object containing the child pointer.
 * @return Zero when the child pointer is null; otherwise the helper result.
 */
float func_002B5E10(void* receiver);

/**
 * @brief Copy the receiver word at offset 0x338 to offset 0x14.
 * @param receiver Object containing both words.
 */
void func_002B5F20(void* receiver);

/**
 * @brief Initialize the receiver's vtable chain and activate it when the signed value is positive.
 * @param receiver Object to initialize.
 * @param value Signed value controlling activation.
 * @return The receiver pointer.
 */
void* func_002B5F30(void* receiver, s16 value);

/**
 * @brief Set the receiver byte at offset 0x60 to eight.
 * @param receiver Object containing the byte.
 */
void func_002B5FC0(void* receiver);

/**
 * @brief Set the receiver byte at offset 0x60 to eight.
 * @param receiver Object containing the byte.
 */
void func_002B60E0(void* receiver);

/**
 * @brief Set the receiver byte at offset 0x493 to one.
 * @param receiver Object containing the byte.
 */
void func_002B60F0(void* receiver);

/**
 * @brief Return the fixed value 14.
 * @param object Receiver or first argument; unused.
 * @return Always 14.
 */
s32 func_002B6250(void* object);

/**
 * @brief Set the receiver byte at offset 4 to one.
 * @param receiver Object containing the byte.
 */
void func_002B6260(void* receiver);

/**
 * @brief Return the signed halfword at receiver offset 0x18.
 * @param receiver Object containing the halfword.
 * @return The halfword value.
 */
s32 func_002B6300(void* receiver);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B6310(void* object);

/**
 * @brief Return the word at receiver offset 0xD3C.
 * @param receiver Object containing the word.
 * @return The word value.
 */
u32 func_002B6320(void* receiver);

/**
 * @brief Return the word at receiver offset 0xD40.
 * @param receiver Object containing the word.
 * @return The word value.
 */
u32 func_002B6330(void* receiver);

/**
 * @brief Return the word at receiver offset 0xD44.
 * @param receiver Object containing the word.
 * @return The word value.
 */
u32 func_002B6340(void* receiver);

/**
 * @brief Return the byte at receiver offset 0xCEE.
 * @param receiver Object containing the byte.
 * @return The byte value.
 */
u8 func_002B6350(void* receiver);

/**
 * @brief Return the byte at receiver offset 0xCEA.
 * @param receiver Object containing the byte.
 * @return The byte value.
 */
u8 func_002B6360(void* receiver);

/**
 * @brief Return the byte at receiver offset 0xCE1.
 * @param receiver Object containing the byte.
 * @return The byte value.
 */
u8 func_002B6370(void* receiver);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B6380(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B6390(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B63A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B63B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B63C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B63D0(void* object);

/**
 * @brief Return the byte at receiver offset 0xF26.
 * @param receiver Object containing the byte.
 * @return The byte value.
 */
u8 func_002B63E0(void* receiver);

/**
 * @brief XOR the word at offset 0xD24 with the masked word at 0xCD8.
 * @param receiver Object containing both words.
 * @return The combined word.
 */
u32 func_002B63F0(void* receiver);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B6410(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B6420(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B6430(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B6440(void* object);

/**
 * @brief Set the receiver halfword at offset 0x2F28 when the value's low byte is eight, then run a helper.
 * @param receiver Object containing the halfword.
 * @param value Value whose low byte is checked.
 */
void func_002B9CB0(void* receiver, s32 value);

/**
 * @brief Run the receiver helper when bytes 0xCE1 and 0xCEE contain the expected state and value.
 * @param receiver Object containing both bytes.
 * @param value Value forwarded to the helper.
 */
void func_002B9CF0(void* receiver, s32 value);

/**
 * @brief Call the helper on the receiver, then clear its byte at offset 0x579.
 * @param receiver Object to process.
 */
void func_002B9E30(void* receiver);

/**
 * @brief Clear receiver byte 0x448, then conditionally mark the child at +0x1F0.
 * @param receiver Object containing the state and child pointer.
 * @return One when the helper permits the child update; otherwise zero.
 */
s32 func_002B8CD0(void* receiver);

/**
 * @brief Initialize the receiver and resolve its word at offset 0x50 into offset 0x2EEC.
 * @param receiver Object containing the input and result words.
 */
void func_002BB740(void* receiver);

/**
 * @brief Initialize a non-null receiver, then initialize and activate it according to a signed value.
 * @param receiver Object to initialize.
 * @param value Signed value controlling activation.
 * @return The receiver pointer.
 */
void* func_002BB780(void* receiver, s16 value);

/** Initialize the receiver's fields to their default sentinel values. */
void* func_002BB7E0(void* receiver);

/**
 * @brief Initialize three receiver fields using resource data from its word at offset 0x50.
 * @param receiver Object containing the resource word and result fields.
 */
void func_002BCCB0(void* receiver);

/**
 * @brief Reset the receiver through a helper and set byte 0x5BE to one.
 * @param receiver Object to reset.
 */
void func_002C40A0(void* receiver);

/**
 * @brief Reset the receiver through a helper and set byte 0x5BE to one.
 * @param receiver Object to reset.
 */
void func_002C40D0(void* receiver);

/**
 * @brief When the helper accepts the receiver, set bytes 0x38E and 0x5BC.
 * @param receiver Object containing the bytes.
 * @return One when the helper accepts the receiver; otherwise zero.
 */
s32 func_002C42B0(void* receiver);

/**
 * @brief Initialize the receiver and resolve its word at offset 0x50 into offset 0x2F04.
 * @param receiver Object containing the input and result words.
 */
void func_002C2030(void* receiver);

/**
 * @brief Update the receiver's embedded float state when the global helper allows it.
 * @param receiver Object containing the embedded state.
 * @return One when the helper allows the update; otherwise zero.
 */
s32 func_002C0A40(void* receiver);

/**
 * @brief Initialize the receiver's vtable chain and clear or release its embedded object.
 * @param receiver Object to initialize.
 * @param value Signed value controlling activation.
 * @return The receiver pointer.
 */
void* func_002C0AE0(void* receiver, s16 value);

/**
 * @brief Initialize the receiver and its embedded object, then activate it for a positive value.
 * @param receiver Object to initialize.
 * @param value Signed value controlling activation.
 * @return The receiver pointer.
 */
void* func_002BC470(void* receiver, s16 value);

/**
 * @brief Initialize the receiver and its embedded object, then activate it for a positive value.
 * @param receiver Object to initialize.
 * @param value Signed value controlling activation.
 * @return The receiver pointer.
 */
void* func_002BDF20(void* receiver, s16 value);

/**
 * @brief Initialize the receiver and its embedded object, then activate it for a positive value.
 * @param receiver Object to initialize.
 * @param value Signed value controlling activation.
 * @return The receiver pointer.
 */
void* func_002B68C0(void* receiver, s16 value);

/**
 * @brief Initialize the receiver's vtable and selected fields.
 * @param receiver Object whose fields are initialized.
 * @return The receiver pointer.
 */
void* func_002BFCD0(void* receiver);

/**
 * @brief Initialize the receiver's vtable chain and activate it for a positive signed value.
 * @param receiver Object to initialize.
 * @param value Signed value controlling activation.
 * @return The receiver pointer.
 */
void* func_002C3FE0(void* receiver, s16 value);

/**
 * @brief Initialize the receiver's vtable chain, release its embedded object, and activate it when requested.
 * @param receiver Object to initialize.
 * @param value Signed value controlling activation.
 * @return The receiver pointer.
 */
void* func_002B5FD0(void* receiver, s16 value);

/** Initialize a non-null receiver and activate it when the signed value is positive. */
void* func_002C2070(void* receiver, s16 value);

/**
 * @brief Set the receiver's vtable and initialize its sentinel fields.
 * @param receiver Object to initialize.
 * @return The receiver pointer.
 */
void* func_002C20D0(void* receiver);

/**
 * @brief Resolve the receiver word at offset 0x50 with a global data object and store the result at 0x450.
 * @param receiver Object containing the input and result words.
 */
void func_002C4540(void* receiver);

/**
 * @brief Resolve the receiver word at offset 0x50 with a global data object and store the result at 0x45C.
 * @param receiver Object containing the input and result words.
 */
void func_002C5800(void* receiver);

#ifdef __cplusplus
}
#endif

#endif
