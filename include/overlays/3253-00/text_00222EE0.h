#ifndef SO3_OVERLAYS_3253_00_TEXT_00222EE0_H
#define SO3_OVERLAYS_3253_00_TEXT_00222EE0_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Forward the receiver to func_4EABF0. */
void func_0022F760(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002231D0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00223210(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00223250(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00223290(void* object);

/**
 * @brief Clear the first four words of the receiver.
 * @param object Receiver whose words at offsets 0 through 0x0C are cleared.
 */
void func_00223320(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00223920(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00223960(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002239A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002239E0(void* object);

/**
 * @brief Return the fixed value 2.
 * @param object Receiver or first argument; unused.
 * @return Always 2.
 */
s32 func_00224140(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002246A0(void* object);

/** Return the word at receiver offset 0x4. */
u32 func_00222F80(const void* object);
/** Return the word at receiver offset 0x40. */
u32 func_002231B0(const void* object);
/** Return the word at receiver offset 0x4. */
u32 func_002234F0(const void* object);
/** Return the word at receiver offset 0x30. */
u32 func_00223900(const void* object);
/** Return the word at receiver offset 0x4. */
u32 func_00223A90(const void* object);


/** Store the byte at receiver offset 0x41. */
void func_0022E000(void* object, u8 value);


/** Return the signed halfword at receiver offset 0x48. */
s16 func_002231C0(const void* object);

/** Return the signed halfword at receiver offset 0x38. */
s16 func_00223910(const void* object);

/** Return the first pointer argument unchanged. */
void* func_00224040(void* value);
/** Return the first pointer argument unchanged. */
void* func_00224050(void* value);

/** Return the receiver address at byte offset 0x20. */
const float* func_0022E030(const void* object);

/** Clear four consecutive words at the start of the receiver. */
void func_00223A20(void* object);


#ifdef __cplusplus
/** Set the high packed mode at its target field and record whether either mode equals four. */
void func_00223150(void* object, u8 mode);

/** Set the high packed mode at its target field and record whether either mode equals four. */
void func_002238A0(void* object, u8 mode);


/** Find a key in the receiver's fixed-size entry array. */
s32 func_002232D0(void* object, float key);

/** Return the key span between the first and last entries. */
float func_00223F50(void* object);

/** Find a key in the receiver's fixed-size entry array. */
s32 func_00223FA0(void* object, float key);


}
#endif

#endif
