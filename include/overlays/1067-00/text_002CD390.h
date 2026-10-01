#ifndef SO3_OVERLAYS_1067_00_TEXT_002CD390_H
#define SO3_OVERLAYS_1067_00_TEXT_002CD390_H

#include "types.h"
#include "overlays/1067-00/text_002CABC0.h"

typedef struct FieldStateCD390 FieldStateCD390;
typedef struct FieldStateCE420 FieldStateCE420;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
/**
 * @brief Set the float at offset 0x14 to one when the state bit is set.
 * @param object Receiver containing the float and state bit.
 * @return Zero when the bit was set; one otherwise.
 */
s32 func_002CD390(FieldStateCD390* object);

void func_002CD780(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CD790(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CD7A0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CD7B0(void* object);

/**
 * @brief Store two byte values and two halfwords, copy the current floats, and clear related state.
 * @param object Receiver to update.
 * @param first First byte value.
 * @param second Second byte value.
 * @param third First halfword value.
 * @param fourth Second halfword value.
 */
void func_002CE420(FieldStateCE420* object, u8 first, u8 second, u16 third, u16 fourth);

/**
 * @brief Return the fixed value one.
 * @param object Receiver of the call.
 * @return One.
 */
int func_002CD9E0(void* object);

/**
 * @brief Store a byte in the selected object when present.
 * @param object Receiver containing the selected object.
 * @param value Byte to store.
 */
void func_002CE510(FieldBytePtr10* object, u8 value);

#ifdef __cplusplus
}
#endif

#endif
