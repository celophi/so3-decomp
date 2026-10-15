#ifndef SO3_OVERLAYS_LIB_TEXT_0043A920_H
#define SO3_OVERLAYS_LIB_TEXT_0043A920_H

#include "types.h"

void func_00441BE0(void* object, void* cell, void* row, s32 index, void* extra4, void* extra5, void* extra6, void* extra7, void* extra8);

/** Return the mapped array entry after its 0x30-byte prefix, or null. */
void* func_0043D240(const void* object, s32 index);
/** Clear four state bytes before updating the row through the owner. */
#ifdef __cplusplus
extern "C" {
#endif
void func_00441C10(void* object, u8* state, void* row);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
void* func_0043DF70(void* receiver);
#endif

/** Build and return a pointer to the four-word stack value. */
void* func_0044A410(void);

/**
 * @brief Process the supplied object with two additional values.
 * @param object Input object.
 * @param arg1 First additional value.
 * @param arg2 Second additional value.
 * @return Processing result.
 */
void* func_00448A10(void* object, u32 arg1, u32 arg2);

/** Copy the vector at receiver offset 0x80 to the result. */
void func_00448CD0(const void* object, void* result);

/**
 * @brief Store the value at receiver offset 0x28.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0043D770(void* object, float value);

/**
 * @brief Store the value at receiver offset 0x30.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0043D780(void* object, float value);

/**
 * @brief Store the value at receiver offset 0x34.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0043D7C0(void* object, float value);

/**
 * @brief Store the value at receiver offset 0x44.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0043D7F0(void* object, float value);

/**
 * @brief Store the value at receiver offset 0x3C.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0043D890(void* object, float value);

/**
 * @brief Store the value at receiver offset 0x40.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0043D8B0(void* object, float value);

/**
 * @brief Store the value at receiver offset 0x38.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0043D930(void* object, float value);

/**
 * @brief Store the value at receiver offset 0x28.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_00444CF0(void* object, float value);

/**
 * @brief Store the value at receiver offset 0x30.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_00444D00(void* object, float value);

/**
 * @brief Store the value at receiver offset 0x34.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_00444D40(void* object, float value);

/**
 * @brief Store the value at receiver offset 0x44.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_00444D70(void* object, float value);

/**
 * @brief Store the value at receiver offset 0x3C.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_00444E10(void* object, float value);

/**
 * @brief Store the value at receiver offset 0x40.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_00444E30(void* object, float value);

/**
 * @brief Store the value at receiver offset 0x38.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_00444EB0(void* object, float value);


/** Return the float member at receiver offset 0x30. */
float func_0043D790(void* object);

/** Return the float member at receiver offset 0x44. */
float func_0043D800(void* object);

/** Return the float member at receiver offset 0x28. */
float func_0043D810(void* object);

/** Return the float member at receiver offset 0x30. */
float func_00444D10(void* object);

/** Return the float member at receiver offset 0x44. */
float func_00444D80(void* object);

/** Return the float member at receiver offset 0x28. */
float func_00444D90(void* object);

/** Return the word at receiver offset 0x48. */
u32 func_0043D830(const void* object);
/** Return the word at receiver offset 0x50. */
u32 func_0043D870(const void* object);
/** Return the word at receiver offset 0x1C. */
u32 func_0043D9C0(const void* object);
/** Return the word at receiver offset 0xC. */
u32 func_0043D9D0(const void* object);
/** Return the word at receiver offset 0x10. */
u32 func_0043D9E0(const void* object);
/** Return the word at receiver offset 0xB8. */
u32 func_00441BB0(const void* object);
/** Return the word at receiver offset 0xBC. */
u32 func_00441BD0(const void* object);
/** Return the word at receiver offset 0x48. */
u32 func_00444DB0(const void* object);
/** Return the word at receiver offset 0x50. */
u32 func_00444DF0(const void* object);
/** Return the word at receiver offset 0x1C. */
u32 func_00444F00(const void* object);
/** Return the word at receiver offset 0xC. */
u32 func_00444F10(const void* object);
/** Return the word at receiver offset 0x10. */
u32 func_00444F20(const void* object);
/** Return the word at receiver offset 0x40. */
u32 func_00449F40(const void* object);
/** Return the word at receiver offset 0x4. */
u32 func_0044A160(const void* object);


/** Store the word at receiver offset 0x48. */
void func_0043D820(void* object, u32 value);

/** Store the word at receiver offset 0x50. */
void func_0043D860(void* object, u32 value);

/** Store the word at receiver offset 0xB8. */
void func_00441BA0(void* object, u32 value);

/** Store the word at receiver offset 0xBC. */
void func_00441BC0(void* object, u32 value);

/** Store the word at receiver offset 0x48. */
void func_00444DA0(void* object, u32 value);

/** Store the word at receiver offset 0x50. */
void func_00444DE0(void* object, u32 value);


/** Store the byte at receiver offset 0x4D. */
void func_0043D7A0(void* object, u8 value);

/** Store the byte at receiver offset 0x56. */
void func_0043D7D0(void* object, u8 value);

/** Store the byte at receiver offset 0x4F. */
void func_0043D840(void* object, u8 value);

/** Store the byte at receiver offset 0x4E. */
void func_0043D850(void* object, u8 value);

/** Store the byte at receiver offset 0x55. */
void func_0043D880(void* object, u8 value);

/** Store the byte at receiver offset 0x54. */
void func_0043D8A0(void* object, u8 value);

/** Store the byte at receiver offset 0x4D. */
void func_00444D20(void* object, u8 value);

/** Store the byte at receiver offset 0x56. */
void func_00444D50(void* object, u8 value);

/** Store the byte at receiver offset 0x4F. */
void func_00444DC0(void* object, u8 value);

/** Store the byte at receiver offset 0x4E. */
void func_00444DD0(void* object, u8 value);

/** Store the byte at receiver offset 0x55. */
void func_00444E00(void* object, u8 value);

/** Store the byte at receiver offset 0x54. */
void func_00444E20(void* object, u8 value);


/** Return the unsigned byte at receiver offset 0x4D. */
u8 func_0043D7B0(const void* object);

/** Return the unsigned byte at receiver offset 0x56. */
u8 func_0043D7E0(const void* object);

/** Return the unsigned byte at receiver offset 0x4D. */
u8 func_00444D30(const void* object);

/** Return the unsigned byte at receiver offset 0x56. */
u8 func_00444D60(const void* object);


/** Return the signed halfword at receiver offset 0x48. */
s16 func_00449F50(const void* object);

/** Return the signed halfword at receiver offset 0x4A. */
s16 func_00449F60(const void* object);


/** Store the byte constant at receiver offset 0x60. */
void func_0044A400(void* object);

/** Clear the byte at receiver offset 0x480. */
void func_0043AFC0(void* object);

/** Return whether the receiver's word at offset 0x14 is nonzero. */
s32 func_0043DA00(void* receiver);

/** Return whether the receiver's word at offset 0x14 is nonzero. */
s32 func_00444F40(void* receiver);

/** Return the floating-point value 1.0f. */
float func_00441520(void* object);

/** Return the floating-point value 1.0f. */
float func_00447DC0(void* object);

/** Return the fixed integer value -1. */
s32 func_0043A920(void* object);

/** Return the fixed integer value 1. */
s32 func_0043D230(void* object);

/** Return the fixed integer value 1. */
s32 func_0043D9F0(void* object);

/** Return the fixed integer value 1. */
s32 func_00441B90(void* object);

/** Return the fixed integer value 63. */
s32 func_00444F30(void* object);

/** Return the fixed integer value 1. */
s32 func_004471A0(void* object);

/** Return the fixed integer value 14. */
s32 func_0044A5E0(void* object);

/** Return the fixed value 0. */
s32 func_0043D0B0(void* object);

/** Return the fixed value 0. */
s32 func_0043D0C0(void* object);

/** Return the fixed value 0. */
s32 func_0043D950(void* object);

/** Return the fixed value 0. */
s32 func_0043D970(void* object);

/** Return the fixed value 0. */
s32 func_00447C70(void* object);

/** Return the fixed value 0. */
s32 func_00447C90(void* object);

/** Return the fixed value 0. */
s32 func_00448900(void* object);

/** Return the fixed value 0. */
s32 func_00449F70(void* object);

/** Return the fixed value 0. */
s32 func_00449F80(void* object);

/** Return the fixed value 0. */
s32 func_00449F90(void* object);

void func_0043BCD0(void* object);
void func_0043BCE0(void* object);
void func_0043D220(void* object);
void func_0043D940(void* object);
void func_0043D960(void* object);
void func_00441B80(void* object);
void func_00447190(void* object);
void func_00447C60(void* object);
void func_00447C80(void* object);
void func_00449FA0(void* object);

/** Return the first pointer argument unchanged. */
void* func_00448690(void* value);
/** Return the first pointer argument unchanged. */
void* func_0044A330(void* value);

/** Set the ready flag and copy a 128-bit value into the receiver. */
void func_0043ABE0(void* object, const unsigned __int128* value);

/** Set the ready flag and copy a 128-bit value into the receiver. */
void func_0043ACB0(void* object, const unsigned __int128* value);

/** Set the ready flag and copy a 128-bit value into the receiver. */
void func_0043AD20(void* object, const unsigned __int128* value);

/** Set the ready flag and copy a 128-bit value into the receiver. */
void func_0043ADA0(void* object, const unsigned __int128* value);


/** Clear four consecutive words at the start of the receiver. */
void func_0044A000(void* object);


#ifdef __cplusplus
/** Set the receiver flag and store four float values. */
void func_0043AAF0(void* object, float x, float y, float z, float w);

/** Set the receiver flag and store four float values. */
void func_0043AB50(void* object, float x, float y, float z, float w);

/** Set the receiver flag and store four float values. */
void func_0043ABB0(void* object, float x, float y, float z, float w);

/** Set a receiver flag and store three float values. */
void func_0043AD60(void* object, float x, float y, float z);

/** Set a receiver flag and store three float values. */
void func_0043AF40(void* object, float x, float y, float z);


/** Clear the receiver flag and copy one 128-bit value to offset 0x3A0. */
void func_0043AA00(void* object, const unsigned __int128* value);

/** Clear the receiver flag and copy one 128-bit value to offset 0x380. */
void func_0043AA50(void* object, const unsigned __int128* value);

/** Clear the receiver flag and copy one 128-bit value to offset 0x360. */
void func_0043AAE0(void* object, const unsigned __int128* value);

/** Clear the receiver flag and copy one 128-bit value to offset 0x320. */
void func_0043AB40(void* object, const unsigned __int128* value);

/** Clear the receiver flag and copy one 128-bit value to offset 0x2E0. */
void func_0043ABA0(void* object, const unsigned __int128* value);

/** Clear the receiver flag and copy one 128-bit value to offset 0x2B0. */
void func_0043AC00(void* object, const unsigned __int128* value);

/** Clear the receiver flag and copy one 128-bit value to offset 0x290. */
void func_0043AC50(void* object, const unsigned __int128* value);

/** Clear the receiver flag and copy one 128-bit value to offset 0x270. */
void func_0043ACA0(void* object, const unsigned __int128* value);

/** Clear the receiver flag and copy one 128-bit value to offset 0x250. */
void func_0043ACF0(void* object, const unsigned __int128* value);

/** Clear the receiver flag and copy one 128-bit value to offset 0x230. */
void func_0043ADE0(void* object, const unsigned __int128* value);


/** Set the receiver flag and copy two 128-bit values to offsets 0x3A0 and 0x3B0. */
void func_0043A9C0(void* object, const unsigned __int128* first, const unsigned __int128* second);

#ifdef __cplusplus
extern "C" {
#endif
/** @brief Set byte 0x490 and store a float at receiver offset 0x43C. @param object Receiver to update. @param value Float value to store. */
void func_0043A9B0(void* object, float value);
#ifdef __cplusplus
}
#endif

/** Set the receiver flag and copy two 128-bit values to offsets 0x3A0 and 0x3B0. */
void func_0043A9E0(void* object, const unsigned __int128* first, const unsigned __int128* second);

/** Set the receiver flag and copy two 128-bit values to offsets 0x380 and 0x390. */
void func_0043AA10(void* object, const unsigned __int128* first, const unsigned __int128* second);

/** Set the receiver flag and copy two 128-bit values to offsets 0x380 and 0x390. */
void func_0043AA30(void* object, const unsigned __int128* first, const unsigned __int128* second);

/** Set the receiver flag and copy two 128-bit values to offsets 0x360 and 0x370. */
void func_0043AAC0(void* object, const unsigned __int128* first, const unsigned __int128* second);

/** Set the receiver flag and copy two 128-bit values to offsets 0x320 and 0x330. */
void func_0043AB20(void* object, const unsigned __int128* first, const unsigned __int128* second);

/** Set the receiver flag and copy two 128-bit values to offsets 0x2E0 and 0x2F0. */
void func_0043AB80(void* object, const unsigned __int128* first, const unsigned __int128* second);

/** Set the receiver flag and copy two 128-bit values to offsets 0x290 and 0x2A0. */
void func_0043AC10(void* object, const unsigned __int128* first, const unsigned __int128* second);

/** Set the receiver flag and copy two 128-bit values to offsets 0x290 and 0x2A0. */
void func_0043AC30(void* object, const unsigned __int128* first, const unsigned __int128* second);

/** Set the receiver flag and copy two 128-bit values to offsets 0x270 and 0x280. */
void func_0043AC60(void* object, const unsigned __int128* first, const unsigned __int128* second);

/** Set the receiver flag and copy two 128-bit values to offsets 0x270 and 0x280. */
void func_0043AC80(void* object, const unsigned __int128* first, const unsigned __int128* second);

/** Set the receiver flag and copy two 128-bit values to offsets 0x250 and 0x260. */
void func_0043ACD0(void* object, const unsigned __int128* first, const unsigned __int128* second);

/** Set the receiver flag and copy two 128-bit values to offsets 0x230 and 0x240. */
void func_0043ADC0(void* object, const unsigned __int128* first, const unsigned __int128* second);


/** Store the byte source and value, then set state 0x57 from the source byte. */
void func_0043D8C0(void* object, const u8* source, u32 value);

/** Store a byte source and word, then set state 0x57 from the source byte. */
void func_00444E40(void* object, const u8* source, u32 value);

/** Clear two pointer fields and set the byte at receiver offset 0x57 from enabled. */
void func_0043D900(void* object, s32 enabled);

/** Clear two pointer fields and set the byte at receiver offset 0x57 from enabled. */
void func_00444E80(void* object, s32 enabled);

/** Clear the word at receiver offset 0x2C and copy four aligned values from the source. */
void func_0043D1F0(void* object, const void* source);

/** Clear the word at receiver offset 0x2C and copy four aligned values from the source. */
void func_00447160(void* object, const void* source);

/** Return the 64-byte table entry at row * (count - 1) + column. */
void* func_0043D9A0(void* object, s32 row, s32 column);

/** Return the 64-byte table entry at row * (count - 1) + column. */
void* func_00444EE0(void* object, s32 row, s32 column);

/** Return the table address at base + index * 48. */
void* func_0043D980(void* object, s32 index);

/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_00448E20(void* object, u8 mode);


/** Set the high packed mode at its target field and record whether either mode equals four. */
void func_00449EE0(void* object, u8 mode);


/** Clear the vector at offset 0x70 and update the associated state. */
void func_00449AF0(void* object);
s32 func_00449FB0(void* object, float key);


}
#endif

#endif
