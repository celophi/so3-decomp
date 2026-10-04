#ifndef SO3_OVERLAYS_1067_00_TEXT_002934A0_H
#define SO3_OVERLAYS_1067_00_TEXT_002934A0_H

#include "types.h"
#include "overlays/1067-00/curve.h"

typedef struct FieldObject1573D0 FieldObject1573D0;

/** Partial curve owner with transition values and state bits. */
struct FieldObject1573D0
{
    u8 pad[0x14];
    FieldClass1514F8 unk14;
    float unk20;
    float unk24;
    float unk28;
    float unk2c;
    float unk30;
    float unk34;
    u8 unk38_0 : 1;
    u8 unk38_1 : 1;
    u8 unk38_2_7 : 6;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Report the fixed type value for this receiver.
 * @param object Receiver to inspect.
 * @return Always 4.
 */
s32 func_002934D0(FieldObject1573D0* object);

/**
 * @brief Initialize the object's float values and two state bits.
 * @param object Object to initialize.
 * @param first_value Value stored at offset 0x24.
 * @param second_value Value stored at offset 0x20.
 * @param third_value Value stored at offset 0x2C.
 */
void func_002934E0(FieldObject1573D0* object, float first_value, float second_value, float third_value);

/**
 * @brief Advance the object's float transition while its active bit is set.
 * @param object Object with the transition state and embedded curve.
 */
void func_00293540(FieldObject1573D0* object);

#ifdef __cplusplus
}
#endif

#endif
