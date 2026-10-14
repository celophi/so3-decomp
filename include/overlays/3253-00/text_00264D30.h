#ifndef SO3_OVERLAYS_3253_00_TEXT_00264D30_H
#define SO3_OVERLAYS_3253_00_TEXT_00264D30_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_00267670(void* object);

/**
 * @brief Store a word at offset 0x14 and set the byte at offset 0x0C to one.
 * @param object Receiver.
 * @param value Word to store.
 */
void func_00267680(void* object, u32 value);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00267690(void* object);

/**
 * @brief Return the fixed value 5.
 * @param object Receiver or first argument; unused.
 * @return Always 5.
 */
s32 func_002677A0(void* object);

/**
 * @brief Return the fixed value 7.
 * @param object Receiver or first argument; unused.
 * @return Always 7.
 */
s32 func_00267890(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002678A0(void* object);

/**
 * @brief Return the receiver address at offset 0x90.
 * @param object Receiver.
 * @return Address of the field at offset 0x90.
 */
void* func_00267920(void* object);

/**
 * @brief Return the receiver address at offset 0x1D0.
 * @param object Receiver.
 * @return Address of the field at offset 0x1D0.
 */
void* func_00267930(void* object);

/**
 * @brief Return the receiver address at offset 0x1E0.
 * @param object Receiver.
 * @return Address of the field at offset 0x1E0.
 */
void* func_00267940(void* object);

/**
 * @brief Return the receiver address at offset 0x1F0.
 * @param object Receiver.
 * @return Address of the field at offset 0x1F0.
 */
void* func_00267950(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00267960(void* object);

/**
 * @brief Return the field at offset 0x620 when the receiver's word at 0x618 is nonzero.
 * @param object Receiver.
 * @return Address of the field, or null when it is absent.
 */
void* func_00267970(void* object);

/**
 * @brief Return the fixed value 6.
 * @param object Receiver or first argument; unused.
 * @return Always 6.
 */
s32 func_00267B20(void* object);

/**
 * @brief Perform the receiver's two cleanup operations.
 * @param object Receiver to clean up.
 */
void func_00267B30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00267C70(void* object);

/**
 * @brief Copy the receiver's byte at offset 0xA8 to offset 0x60.
 * @param object Receiver.
 */
void func_00267C80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00267D30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00267D40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00267D50(void* object);

/**
 * @brief Return the floating-point value 0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_00267D60(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00267D70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00267D80(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00268380(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002685D0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002685E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002685F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00268600(void* object);

/**
 * @brief Test whether the receiver's word at offset 0x704 is nonzero.
 * @param object Receiver.
 * @return One when the word is nonzero; otherwise zero.
 */
s32 func_00268610(const void* object);

/**
 * @brief Return the receiver address at offset 0x79C.
 * @param object Receiver.
 * @return Address at offset 0x79C.
 */
void* func_00268620(void* object);

/**
 * @brief Read the receiver's byte at offset 0x794.
 * @param object Receiver.
 * @return The byte value.
 */
u8 func_00268630(const void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00268640(void* object);

/**
 * @brief Return the supplied second argument.
 * @param object First argument, unused.
 * @param value Value to return.
 * @return The supplied value.
 */
void* func_002686C0(void* object, void* value);

/**
 * @brief Return the supplied second argument.
 * @param object First argument, unused.
 * @param value Value to return.
 * @return The supplied value.
 */
void* func_002686D0(void* object, void* value);

/**
 * @brief Set the receiver's byte at offset 0x60 to six.
 * @param object Receiver.
 */
void func_00268770(void* object);

/**
 * @brief Set the receiver's byte at offset 0x60 to ten.
 * @param object Receiver.
 */
void func_00268780(void* object);

/**
 * @brief Set the receiver's byte at offset 0x60 to nine.
 * @param object Receiver.
 */
void func_00268820(void* object);

/**
 * @brief Copy the receiver's byte at offset 0x125 to offset 0x60.
 * @param object Receiver.
 */
void func_00268940(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00268950(void* object);

/**
 * @brief Set the receiver's byte at offset 0x60 to six.
 * @param object Receiver.
 */
void func_002689F0(void* object);

/**
 * @brief Return the fixed value 12.
 * @param object Receiver or first argument; unused.
 * @return Always 12.
 */
s32 func_00268A90(void* object);

/**
 * @brief Return the fixed value 5.
 * @param object Receiver or first argument; unused.
 * @return Always 5.
 */
s32 func_00268B30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00268B40(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00268B50(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00268B60(void* object);

/**
 * @brief Return the fixed value 5.
 * @param object Receiver or first argument; unused.
 * @return Always 5.
 */
s32 func_00268B70(void* object);

/**
 * @brief Set the receiver's byte at offset 0x60 to nine.
 * @param object Receiver.
 */
void func_00268C10(void* object);

/**
 * @brief Set the receiver's byte at offset 0x60 to six.
 * @param object Receiver.
 */
void func_00268CB0(void* object);

/**
 * @brief Set the receiver's byte at offset 0x60 to nine.
 * @param object Receiver.
 */
void func_00268D50(void* object);

/**
 * @brief Set the receiver's byte at offset 0x60 to seven.
 * @param object Receiver.
 */
void func_00268D60(void* object);


/**
 * @brief Clear and reset the receiver fields at offsets 0x40 and 0x48 through 0x50.
 * @param object Receiver.
 */
void func_00269020(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269D50(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026A3F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026A8F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026A970(void* object);

/**
 * @brief Test whether the byte at receiver offset 0xA4 plus index equals four.
 * @param object Receiver.
 * @param index Byte offset added to 0xA4.
 * @return One when the selected byte equals four; otherwise zero.
 */
s32 func_0026B020(const void* object, s32 index);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_0026FEB0(void* object);

/**
 * @brief Forward the receiver to func_0026C550.
 * @param object Receiver.
 */
void func_0026FFF0(void* object);

/**
 * @brief Forward the receiver to func_4EABF0.
 * @param object Receiver.
 */
void func_002705C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00272980(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00273A70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00273A80(void* object);

/**
 * @brief Forward the receiver to func_4EABF0.
 * @param object Receiver.
 */
void func_00274AC0(void* object);

#ifdef __cplusplus
}
#endif

#endif
