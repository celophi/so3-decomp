#ifndef SO3_OVERLAYS_1067_00_TEXT_002CD390_H
#define SO3_OVERLAYS_1067_00_TEXT_002CD390_H

#include "types.h"
#ifdef __cplusplus
#include "overlays/1067-00/text_002CABC0.h"
#else
typedef struct FieldBytePtr10 FieldBytePtr10;
#endif

typedef struct FieldStateCD390 FieldStateCD390;
/** Field list parameters preceding the callback base. */
typedef struct FieldStateCE420
{
    struct LibClass178600* unk00;
    struct LibClass178600* unk04;
    float unk08;
    float unk0c;
    u8 pad10[0xA];
    u16 unk1a;
    u16 unk1c;
    u8 pad1e[4];
    u16 unk22;
    s16 unk24;
    u8 unk26;
    u8 unk27;
    u8 unk28;
    u8 pad29[2];
    u8 unk2b;
    u32 unk2c;
    u8 pad30[4];
    float unk34;
    float unk38;
    u8 unk3c;
    u8 unk3d[3];
} FieldStateCE420;
typedef struct FieldObjectCE8D0 FieldObjectCE8D0;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set the float at offset 0x14 to one when the state bit is set.
 * @param object Receiver containing the float and state bit.
 * @return Zero when the bit was set; one otherwise.
 */
s32 func_002CD390(FieldStateCD390* object);

/** @brief Perform no action. @param object Receiver; unused. */
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
 * @param second Value whose low byte is stored.
 * @param third First halfword value.
 * @param fourth Second halfword value.
 */
void func_002CE420(FieldStateCE420* object, u8 first, u32 second, u16 third, u16 fourth);

/**
 * @brief Return the fixed value one.
 * @param object Receiver of the call.
 * @return One.
 */
int func_002CD9E0(void* object);

/**
 * @brief Store a byte in the selected object when present.
 * @param object Receiver containing the selected object.
 * @param value Value whose low byte is stored.
 */
void func_002CE510(FieldBytePtr10* object, u32 value);

/**
 * @brief Create a nested display and initialize it with the associated object and coordinates.
 * @param object Receiver that owns the nested display.
 * @param associated Associated object forwarded to the receiver's handler.
 * @param x Horizontal coordinate.
 * @param y Vertical coordinate.
 * @param code Value forwarded to the nested display initializer.
 * @return One when the nested display and associated object are present, or zero otherwise.
 */
s32 func_002CE8D0(FieldObjectCE8D0* object, void* associated, float x, float y, s32 code);

#ifdef __cplusplus
}
#endif

#endif
