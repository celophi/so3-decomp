#ifndef SO3_OVERLAYS_0002_00_TEXT_001DD3C0_H
#define SO3_OVERLAYS_0002_00_TEXT_001DD3C0_H

#include "types.h"

typedef struct Record001E94E0 Record001E94E0;

/** @brief Partial state layout for the two selectable reset modes. */
typedef struct BootState1E1A40
{
    u8 unk00[0x18];
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    u8 unk1E;
    u8 unk1F[9];
    u8 unk28;
    u8 unk29;
    u8 unk2A;
    u8 unk2B;
    u8 unk2C;
    u8 unk2D;
    u8 unk2E[0xD06];
    u8 unkD34;
    u8 unkD35[2];
    u8 unkD37[2];
    u8 unkD39[0xC3];
    s32 unkDFC[2];
    s32 unkE04[2];
} BootState1E1A40;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Reset the shared state and the fields selected by mode 0 or 1.
 * @param object State receiving the reset.
 * @param mode Mode to store and reset; other values reset only shared fields.
 */
void func_001E1A40(BootState1E1A40* object, s16 mode);

/**
 * @brief Store mode 1 or 2 and reset the state for selector 0.
 * @param object State receiving the mode and reset.
 * @param mode Mode to store; values other than 1 or 2 have no effect.
 */
void func_001E0DE0(BootState1E1A40* object, u8 mode);

/**
 * @brief Query a mode's byte and reset selector 0 when the reset flag is set.
 * @param object State containing the mode bytes and reset flag.
 * @param mode Mode 0 or 1 to query; other values return zero without a reset.
 * @param kind Select guarded values with 1, or the direct mode byte otherwise.
 * @return The selected byte before any reset.
 */
u8 func_001E1410(BootState1E1A40* object, u16 mode, u16 kind);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001DD4C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001E04E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001E04F0(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_001E05D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001E05E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001E0870(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001E0880(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001E08C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001E08D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001E08E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001E08F0(void* object);

/**
 * @brief Return the fixed value 2.
 * @param object Receiver or first argument; unused.
 * @return Always 2.
 */
s32 func_001E0900(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_001E3FE0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001E9400(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001E9410(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001E9440(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001E9450(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001E9490(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001E9640(void* object);

/**
 * @brief Return the 32-bit word at offset 0xDD0.
 * @param object Object containing the value.
 * @return The stored value.
 */
u32 func_001E0AD0(void* object);

/**
 * @brief Return the signed 16-bit value at offset 0xDCE.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 func_001E0AE0(void* object);

/**
 * @brief Return the 8-bit value at offset 0x794.
 * @param object Object containing the value.
 * @return The stored value.
 */
u8 func_001E9480(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_001DD400(void* object);

/**
 * @brief Store the value at offset 0x6A.
 * @param object Object receiving the value.
 * @param value Value to store.
 */
void func_001DFE30(void* object, u16 value);

/**
 * @brief Store the value at offset 0x6C.
 * @param object Object receiving the value.
 * @param value Value to store.
 */
void func_001DFE40(void* object, u16 value);

/**
 * @brief Store the value at offset 0x18.
 * @param object Object receiving the value.
 * @param value Value to store.
 */
void func_001E0250(void* object, u8 value);

/**
 * @brief Clear the byte at offset 0x60.
 * @param object Object containing the byte.
 */
void func_001E0860(void* object);

/**
 * @brief Return the supplied value.
 * @param object Receiver or first argument; unused.
 * @param value Value to return.
 * @return The supplied value.
 */
s32 func_001E9420(void* object, s32 value);

/**
 * @brief Return the supplied value.
 * @param object Receiver or first argument; unused.
 * @param value Value to return.
 * @return The supplied value.
 */
s32 func_001E9430(void* object, s32 value);

/**
 * @brief Return the address of the field at offset 0x79C.
 * @param object Object containing the field.
 * @return Pointer to the field.
 */
u8* func_001E9470(void* object);

/**
 * @brief Return the address of the field at offset 0x570.
 * @param object Object containing the field.
 * @return Pointer to the field.
 */
u8* func_001E94D0(void* object);

/**
 * @brief Return the address of the field at offset 0x90.
 * @param object Object containing the field.
 * @return Pointer to the field.
 */
u8* func_001E9550(void* object);

/**
 * @brief Return the address of the field at offset 0x1D0.
 * @param object Object containing the field.
 * @return Pointer to the field.
 */
u8* func_001E9560(void* object);

/**
 * @brief Return the address of the field at offset 0x1E0.
 * @param object Object containing the field.
 * @return Pointer to the field.
 */
u8* func_001E9570(void* object);

/**
 * @brief Return the address of the field at offset 0x1F0.
 * @param object Object containing the field.
 * @return Pointer to the field.
 */
u8* func_001E9580(void* object);

/**
 * @brief Return zero as a float.
 * @param object Receiver or first argument; unused.
 * @return Always 0.0f.
 */
float func_001E9380(void* object);

/**
 * @brief Check whether the word at offset 0x704 is nonzero.
 * @param object Object containing the word.
 * @return One if nonzero, otherwise zero.
 */
s32 func_001E9460(void* object);

/**
 * @brief Mark a record active and set its float values.
 * @param object Record to update.
 * @param first First float value.
 * @param second Second float value.
 * @param third Third float value.
 */
void func_001DD620(u8* object, float first, float second, float third);

/**
 * @brief Mark a record active and set three float values.
 * @param object Record to update.
 * @param first First float value.
 * @param second Second float value.
 * @param third Third float value.
 */
void func_001DDED0(u8* object, float first, float second, float third);

/**
 * @brief Set three float values and a final value of 1.0f.
 * @param object Record to update.
 * @param first First float value.
 * @param second Second float value.
 * @param third Third float value.
 */
void func_001E0520(u8* object, float first, float second, float third);

/**
 * @brief Mark a record active and set four float values.
 * @param object Record to update.
 * @param first First float value.
 * @param second Second float value.
 * @param third Third float value.
 * @param fourth Fourth float value.
 */
void func_001E0630(u8* object, float first, float second, float third, float fourth);

/**
 * @brief Clear the first four words of a record.
 * @param object Record to clear.
 * @return The record pointer.
 */
void* func_001DFE50(u32* object);

/**
 * @brief Initialize a record pointer to the fixed table.
 * @param object Pointer field to initialize.
 * @return The record pointer.
 */
void* func_001DFE70(void** object);

/**
 * @brief Check whether a float is negative.
 * @param object Receiver or first argument; unused.
 * @param value Float to test.
 * @return One if negative, otherwise zero.
 */
s32 func_001E0890(void* object, float value);

/**
 * @brief Return the fixed table address.
 * @param object Receiver or first argument; unused.
 * @return Address of the fixed table.
 */
void* func_001E08B0(void* object);

/**
 * @brief Clear six consecutive words starting at offset 0x20.
 * @param object Record to clear.
 */
void func_001E9650(u32* object);

/**
 * @brief Copy 16 bytes to offset 0x20.
 * @param object Destination record.
 * @param value 16-byte value to copy.
 */
void func_001E0500(u8* object, const unsigned __int128* value);

/**
 * @brief Copy 16 bytes to offset 0x20.
 * @param object Destination record.
 * @param value 16-byte value to copy.
 */
void func_001E0510(u8* object, const unsigned __int128* value);

/**
 * @brief Mark a record active and copy 16 bytes to offset 0x20.
 * @param object Destination record.
 * @param value 16-byte value to copy.
 */
void func_001E05F0(u8* object, const unsigned __int128* value);

/**
 * @brief Mark a record active and copy 16 bytes to offset 0x20.
 * @param object Destination record.
 * @param value 16-byte value to copy.
 */
void func_001E0610(u8* object, const unsigned __int128* value);

/**
 * @brief Mark a record active and copy 16 bytes to offset 0x30.
 * @param object Destination record.
 * @param value 16-byte value to copy.
 */
void func_001E0650(u8* object, const unsigned __int128* value);

/**
 * @brief Mark a record active and copy 16 bytes to offset 0x30.
 * @param object Destination record.
 * @param value 16-byte value to copy.
 */
void func_001E0670(u8* object, const unsigned __int128* value);

/**
 * @brief Mark a record active and copy 16 bytes to offset 0x40.
 * @param object Destination record.
 * @param value 16-byte value to copy.
 */
void func_001E0730(u8* object, const unsigned __int128* value);

/**
 * @brief Mark a record active and copy 16 bytes to offset 0x40.
 * @param object Destination record.
 * @param value 16-byte value to copy.
 */
void func_001E0750(u8* object, const unsigned __int128* value);

/**
 * @brief Forward to the owner 0x640 bytes before the embedded object.
 * @param object Pointer to the embedded object.
 */
void func_001E9590(u8* object);

/**
 * @brief Forward to the owner 0x640 bytes before the embedded object.
 * @param object Pointer to the embedded object.
 */
void func_001E95A0(u8* object);

/**
 * @brief Set the value byte and active flag.
 * @param object Record to update.
 * @param value Byte to store.
 */
void func_001E94E0(Record001E94E0* object, u8 value);

/**
 * @brief Mark a record active and copy a four-float value into it.
 * @param object Record to update.
 * @param first First float value.
 * @param second Second float value.
 * @param third Third float value.
 */
void func_001E06F0(u8* object, float first, float second, float third);

#ifdef __cplusplus
}
#endif

#endif
