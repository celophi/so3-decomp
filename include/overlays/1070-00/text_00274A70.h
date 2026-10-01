#ifndef SO3_OVERLAYS_1070_00_TEXT_00274A70_H
#define SO3_OVERLAYS_1070_00_TEXT_00274A70_H

#include "types.h"

/** Partial receiver whose word value is at offset 0x18. */
typedef struct FieldWordState18
{
    u8 unk00[0x18];
    u32 unk18;
} FieldWordState18;

/** Partial target whose float value is at offset 0x90. */
typedef struct FieldFloatTarget90
{
    u8 unk00[0x90];
    float unk90;
} FieldFloatTarget90;

/** Partial receiver owning a float value and an optional linked target. */
typedef struct FieldFloatOwner540
{
    u8 unk00[0x144];
    FieldFloatTarget90* unk144;
    u8 unk148[0x3F8];
    float unk540;
} FieldFloatOwner540;

/** Partial linked record containing an object pointer. */
typedef struct FieldPointerState48
{
    u8 unk00[0x48];
    void* unk48;
} FieldPointerState48;

/** Partial receiver containing an optional linked record. */
typedef struct FieldPointerOwner588
{
    u8 unk00[0x588];
    FieldPointerState48* unk588;
} FieldPointerOwner588;

/** Partial receiver for the observed conditional state update. */
typedef struct FieldCappedByte4A4
{
    u8 unk00[0x4A4];
    s8 unk4a4;
    u8 unk4a5_0 : 1;
    u8 unk4a5_1_7 : 7;
} FieldCappedByte4A4;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set the word value at offset 0x18.
 * @param object Receiver to update.
 * @param value Word to store.
 */
void func_00281CE0(FieldWordState18* object, u32 value);

/**
 * @brief Set the receiver float and mirror it to the linked target when present.
 * @param object Receiver to update.
 * @param value Float value to store.
 */
void func_00276D80(FieldFloatOwner540* object, float value);

/**
 * @brief Read the object pointer through the optional linked record.
 * @param object Receiver to inspect.
 * @return The stored object pointer, or null when the linked record is absent.
 */
void* func_00277690(const FieldPointerOwner588* object);

/**
 * @brief Cap the signed byte at four and set its update flag.
 * @param object Receiver containing the value and flag.
 * @param value Signed value to store; values above four are capped.
 */
void func_00276FE0(FieldCappedByte4A4* object, s8 value);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00275390(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_002754F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00275500(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00275510(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00275530(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00275540(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00275550(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00275560(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00275570(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00275580(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00275590(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002755A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002755B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002755C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002755D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002755E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002755F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00275600(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00275610(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00275620(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00275630(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00275640(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00275650(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00275660(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00275680(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00275690(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002756A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002756B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002756C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002756D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002756F0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002757D0(void* object);

/**
 * @brief Return the fixed value 9.
 * @param object Receiver or first argument; unused.
 * @return Always 9.
 */
s32 func_00276020(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0027D2F0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_0027EA60(void* object);

#ifdef __cplusplus
}
#endif

#endif
