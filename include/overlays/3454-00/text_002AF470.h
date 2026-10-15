#ifndef SO3_OVERLAYS_3454_00_TEXT_002AF470_H
#define SO3_OVERLAYS_3454_00_TEXT_002AF470_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
void func_002B3BE0(u8* object, void* context);
void func_002B0EF0(u8* receiver, void* value1, void* value2, void* value3);
/** Set the output values when the input float is positive. */
s32 func_002B0AF0(void* object, const void* value, float* zero_output, float* small_output);
#endif

/** Call the object cleanup helper, then clear the byte at receiver offset 0x570. */
void func_002B3D20(void* receiver);
/** Initialize the object and store the resolved field value at offset 0x2F0C. */
void func_002B5490(void* receiver);
/** Initialize the object and store the resolved field value at offset 0x2F24. */
void func_002BAB10(void* receiver);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B0880(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_002B0890(void* object);

/**
 * @brief Pass the pointer at offset 4 to the field counter.
 * @param receiver Object containing the pointer.
 */
void func_002B08A0(void* receiver);

/**
 * @brief Pass the pointer at offset 4 to the field validator.
 * @param receiver Object containing the pointer.
 */
void func_002B08C0(void* receiver);

/**
 * @brief Count the set entries for the supplied object.
 * @param object Input object.
 * @return Number of set entries.
 */
s32 func_002B1380(void* object);

/**
 * @brief Validate the supplied field object.
 * @param object Input object.
 * @return Validation result.
 */
s32 func_002B1300(void* object);

/**
 * @brief Resolve the nested word value and store the result.
 * @param object Object containing the input and result fields.
 */
void func_002BDF20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B08E0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002B0920(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B0940(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_002B0AD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B0AE0(void* object);

/**
 * @brief Return the fixed value 14.
 * @param object Receiver or first argument; unused.
 * @return Always 14.
 */
s32 func_002B0BC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B1090(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B1110(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B1120(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B1130(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B1140(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B1150(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B1160(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B11A0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B11B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B11C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B11D0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B11E0(void* object);

/** Return the word at receiver offset 0xD30. */
u32 func_002B10A0(const void* object);
/** Return the word at receiver offset 0xD34. */
u32 func_002B10B0(const void* object);
/** Return the word at receiver offset 0xD38. */
u32 func_002B10C0(const void* object);


/** Return the unsigned byte at receiver offset 0xCDF. */
u8 func_002B10D0(const void* object);

/** Return the unsigned byte at receiver offset 0xCDA. */
u8 func_002B10E0(const void* object);

/** Return the unsigned byte at receiver offset 0xCD1. */
u8 func_002B10F0(const void* object);

/** Return the unsigned byte at receiver offset 0xCE7. */
u8 func_002B1100(const void* object);

/** Return the unsigned byte at receiver offset 0xF16. */
u8 func_002B1170(const void* object);


/** Return the signed halfword at receiver offset 0x18. */
s16 func_002B1080(const void* object);


/** Store the byte constant at receiver offset 0x10D. */
void func_002B08F0(void* object);

/** Store the byte constant at receiver offset 0x10D. */
void func_002B0900(void* object);

/** Store the byte constant at receiver offset 0x10D. */
void func_002B0910(void* object);

/** Store the byte constant at receiver offset 0x60. */
void func_002B0E10(void* object);

/** Store the byte constant at receiver offset 0x60. */
void func_002B0F30(void* object);

/** Store the byte constant at receiver offset 0x4A3. */
void func_002B0F40(void* object);

/** Store the byte constant at receiver offset 0x4. */
void func_002B0FE0(void* object);

#ifdef __cplusplus
}
#endif

#endif
