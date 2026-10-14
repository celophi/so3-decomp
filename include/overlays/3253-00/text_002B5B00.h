#ifndef SO3_OVERLAYS_3253_00_TEXT_002B5B00_H
#define SO3_OVERLAYS_3253_00_TEXT_002B5B00_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

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
