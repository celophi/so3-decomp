#ifndef SO3_OVERLAYS_1070_00_TEXT_002B4F20_H
#define SO3_OVERLAYS_1070_00_TEXT_002B4F20_H

#include "types.h"
#include "overlays/1070-00/text_00284BF0.h"

/** Partial receiver containing the adjacent floating-point fields at 0x30 and 0x34. */
typedef struct FieldFloatPair30
{
    u8 unk00[0x30];
    float unk30;
    float unk34;
} FieldFloatPair30;

/** Partial receiver with an active byte and four signed values. */
typedef struct FieldFourValueState48
{
    u8 unk00[0x44];
    u8 unk44;
    u8 unk45[3];
    s32 unk48;
    s32 unk4c;
    s32 unk50;
    s32 unk54;
} FieldFourValueState48;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set the adjacent floating-point values at offsets 0x30 and 0x34.
 * @param object Receiver to update.
 * @param first Value for offset 0x30.
 * @param second Value for offset 0x34.
 */
void func_002B6BC0(FieldFloatPair30* object, float first, float second);

/**
 * @brief Set the active byte and four adjacent signed values.
 * @param object Receiver to update.
 * @param first Value for offset 0x48.
 * @param second Value for offset 0x4C.
 * @param third Value for offset 0x50.
 * @param fourth Value for offset 0x54.
 */
void func_002B5CB0(FieldFourValueState48* object, s32 first, s32 second, s32 third, s32 fourth);

/**
 * @brief Return the fixed value 9.
 * @param object Receiver or first argument; unused.
 * @return Always 9.
 */
s32 func_002B5150(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_002B6DE0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002B6E20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B7070(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B8090(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B80B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B80C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B80D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B80E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B80F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B8110(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B8120(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B8130(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B8140(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B8150(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B8160(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B8170(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B8180(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B8190(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B81A0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B81B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B81C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B81D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B81E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B8200(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B8210(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B8220(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B8230(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B8240(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B8250(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B8270(void* object);

/**
 * @brief Return the fixed value 32.
 * @param object Receiver or first argument; unused.
 * @return Always 32.
 */
s32 func_002B8350(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_002B91D0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002B9200(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B9FF0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002BA1F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BA200(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BA220(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BA230(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BA240(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BA250(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BA260(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BA270(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002BA280(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BA290(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BA2A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BA2B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002BA2C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BA2D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BA2E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BA2F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BA300(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BA310(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002BA320(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BA330(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002BA340(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BA350(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BA370(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BA380(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002BA390(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BA3A0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002BA3B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BA3C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BA3E0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002BA480(void* object);

/**
 * @brief Return the fixed value 2.
 * @param object Receiver or first argument; unused.
 * @return Always 2.
 */
s32 func_002BEEE0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BEF10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BEF20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BEF30(void* object);


/**
 * @brief Clear the word at offset 0x28.
 * @param object Receiver to update.
 */
void func_002B6DF0(void* object);

/**
 * @brief Return the fixed float value 2500.0.
 * @param object Receiver or first argument; unused.
 * @return The fixed value.
 */
float func_002B6E00(void* object);

/**
 * @brief Return the fixed float value 100.0.
 * @param object Receiver or first argument; unused.
 * @return The fixed value.
 */
float func_002B80A0(void* object);

/**
 * @brief Return the word at offset 0x1C.
 * @param object Receiver containing the field.
 * @return The selected value.
 */
u32 func_002B8320(void* object);

/**
 * @brief Return the word at offset 0xC.
 * @param object Receiver containing the field.
 * @return The selected value.
 */
u32 func_002B8330(void* object);

/**
 * @brief Return the word at offset 0x10.
 * @param object Receiver containing the field.
 * @return The selected value.
 */
u32 func_002B8340(void* object);

/**
 * @brief Test whether the word at offset 0x14 is nonzero.
 * @param object Receiver containing the field.
 * @return The selected value.
 */
s32 func_002B8360(void* object);

/**
 * @brief Return the fixed float value 1.0.
 * @param object Receiver or first argument; unused.
 * @return The fixed value.
 */
float func_002B8AC0(void* object);

/**
 * @brief Clear the word at offset 0x28.
 * @param object Receiver to update.
 */
void func_002B91E0(void* object);

/**
 * @brief Return the float at offset 0x2C.
 * @param object Receiver containing the field.
 * @return The selected value.
 */
float func_002B91F0(void* object);

/**
 * @brief Set the byte at offset 0x60 to 10.
 * @param object Receiver to update.
 */
void func_002BEEF0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return The fixed value.
 */
s32 func_002B8080(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B8100(void* object);

/**
 * @brief Return the fixed float value 0.0.
 * @param object Receiver or first argument; unused.
 * @return The fixed value.
 */
float func_002B81F0(void* object);

/**
 * @brief Return the fixed float value 0.0.
 * @param object Receiver or first argument; unused.
 * @return The fixed value.
 */
float func_002B8260(void* object);

/**
 * @brief Return the fixed float value 100.0.
 * @param object Receiver or first argument; unused.
 * @return The fixed value.
 */
float func_002BA210(void* object);

/**
 * @brief Return the fixed float value 0.0.
 * @param object Receiver or first argument; unused.
 * @return The fixed value.
 */
float func_002BA360(void* object);

/**
 * @brief Return the fixed float value 0.0.
 * @param object Receiver or first argument; unused.
 * @return The fixed value.
 */
float func_002BA3D0(void* object);

/**
 * @brief Return the word at offset 0x1C.
 * @param object Receiver containing the field.
 * @return The selected value.
 */
u32 func_002BA450(void* object);

/**
 * @brief Return the word at offset 0xC.
 * @param object Receiver containing the field.
 * @return The selected value.
 */
u32 func_002BA460(void* object);

/**
 * @brief Return the word at offset 0x10.
 * @param object Receiver containing the field.
 * @return The selected value.
 */
u32 func_002BA470(void* object);

/**
 * @brief Test whether the word at offset 0x14 is nonzero.
 * @param object Receiver containing the field.
 * @return The selected value.
 */
s32 func_002BA490(void* object);

/**
 * @brief Return the fixed float value 1.0.
 * @param object Receiver or first argument; unused.
 * @return The fixed value.
 */
float func_002BABF0(void* object);

/**
 * @brief Return the signed halfword at offset 0x14.
 * @param object Receiver containing the field.
 * @return The selected value.
 */
s16 func_002BACC0(void* object);

/**
 * @brief Clear the notification entry identified by its token.
 * @param object Receiver containing eight notification slots.
 * @param token Token to find in the slots.
 */
void func_002BAF30(FieldContextE4* object, s32 token);

/**
 * @brief Register a byte-state notification in an available slot.
 * @param object Receiver containing eight notification slots.
 * @param name Name copied into the slot's 16-byte label.
 * @param state Byte state passed to the notification binding.
 * @param value Signed byte passed to the notification binding.
 * @return Slot token, or -1 when every slot is occupied.
 */
s32 func_002BAFB0(FieldContextE4* object, const char* name, u8* state, s8 value);

#ifdef __cplusplus
}
#endif

#endif
