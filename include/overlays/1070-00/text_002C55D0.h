#ifndef SO3_OVERLAYS_1070_00_TEXT_002C55D0_H
#define SO3_OVERLAYS_1070_00_TEXT_002C55D0_H

#include "overlays/1070-00/text_00202FB0.h"

/** Partial receiver storing a linked object and an additional word value. */
typedef struct FieldLinkedState
{
    u8 unk00[0x24];
    void* unk24;
    u32 unk28;
} FieldLinkedState;

/** Partial receiver describing a bit limit and its packed 64-bit words. */
typedef struct FieldBitCountState
{
    s32 unk00;
    u8 unk04[0x10];
    u64* unk14;
} FieldBitCountState;

/** Partial receiver with four vector fields and a state byte. */
typedef struct FieldVectorSlots880
{
    u8 unk00[0x20];
    unsigned __int128 unk20;
    unsigned __int128 unk30;
    u8 unk40[0x10];
    u8 unk50;
    u8 unk51[0x82F];
    unsigned __int128 unk880;
    unsigned __int128 unk890;
} FieldVectorSlots880;

/** Vector storage that can be cleared as a single 128-bit value. */
typedef union FieldVectorBits
{
    FieldVector vector;
    unsigned __int128 bits;
} FieldVectorBits;

/** Partial receiver with a floating-point value at offset 0x4C. */
typedef struct FieldFloat4C
{
    u8 unk00[0x4C];
    float unk4c;
} FieldFloat4C;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize and append a record while the next index is below the limit.
 * @param object Queue containing the record array and next index.
 * @param value Word value to store in the record.
 * @param kind Byte value to store in field 0x15.
 * @param flag Value whose low bit sets field 0x16 bit 1.
 */
void func_002D1C70(FieldRecordQueue* object, u32 value, u8 kind, u8 flag);

/**
 * @brief Copy a vector into fields 0x890 and 0x20, and set the state byte.
 * @param object Receiver to update.
 * @param value Vector to copy.
 */
void func_002CC6B0(FieldVectorSlots880* object, const unsigned __int128* value);

/**
 * @brief Copy one vector into two destinations.
 * @param first First destination.
 * @param second Second destination.
 * @param source Vector to copy.
 */
void func_002CC6E0(unsigned __int128* first, unsigned __int128* second, const unsigned __int128* source);

/**
 * @brief Clear a vector and set its final component to one.
 * @param value Vector to reset.
 */
void func_002CCB50(FieldVectorBits* value);

/**
 * @brief Copy a vector into fields 0x880 and 0x30, and set the state byte.
 * @param object Receiver to update.
 * @param value Vector to copy.
 */
void func_002CD950(FieldVectorSlots880* object, const unsigned __int128* value);

/**
 * @brief Copy a vector into fields 0x880 and 0x30, and set the state byte.
 * @param object Receiver to update.
 * @param value Vector to copy.
 */
void func_002CD970(FieldVectorSlots880* object, const unsigned __int128* value);

/**
 * @brief Copy a vector into fields 0x890 and 0x20, and set the state byte.
 * @param object Receiver to update.
 * @param value Vector to copy.
 */
void func_002CD990(FieldVectorSlots880* object, const unsigned __int128* value);

/**
 * @brief Copy the receiver's floating-point value into an output location.
 * @param object Receiver containing the value.
 * @param result Output location.
 */
void func_002D5570(const FieldFloat4C* object, float* result);

/**
 * @brief Set all four vector components to one value.
 * @param vector Destination vector.
 * @param value Component value.
 * @return The destination vector.
 */
FieldVector* func_002CC6F0(FieldVector* vector, float value);

/**
 * @brief Set the linked receiver pointer and adjacent word value.
 * @param object Receiver to update.
 * @param receiver Object pointer to store.
 * @param value Word to store.
 */
void func_002CB980(FieldLinkedState* object, void* receiver, u32 value);

/**
 * @brief Count the set bits below the stored signed bit limit.
 * @param object Receiver containing the bit limit and packed words.
 * @return The number of set bits, or zero for a nonpositive limit.
 */
s32 func_002D1DE0(const FieldBitCountState* object);

/**
 * @brief Count the set bits below the stored signed bit limit.
 * @param object Receiver containing the bit limit and packed words.
 * @return The number of set bits, or zero for a nonpositive limit.
 */
s32 func_002D2490(const FieldBitCountState* object);

/**
 * @brief Count the set bits below the stored signed bit limit.
 * @param object Receiver containing the bit limit and packed words.
 * @return The number of set bits, or zero for a nonpositive limit.
 */
s32 func_002D2B50(const FieldBitCountState* object);

/**
 * @brief Count the set bits below the stored signed bit limit.
 * @param object Receiver containing the bit limit and packed words.
 * @return The number of set bits, or zero for a nonpositive limit.
 */
s32 func_002D3180(const FieldBitCountState* object);

/**
 * @brief Count the set bits below the stored signed bit limit.
 * @param object Receiver containing the bit limit and packed words.
 * @return The number of set bits, or zero for a nonpositive limit.
 */
s32 func_002D36F0(const FieldBitCountState* object);

/**
 * @brief Count the set bits below the stored signed bit limit.
 * @param object Receiver containing the bit limit and packed words.
 * @return The number of set bits, or zero for a nonpositive limit.
 */
s32 func_002D3D30(const FieldBitCountState* object);

/**
 * @brief Count the set bits below the stored signed bit limit.
 * @param object Receiver containing the bit limit and packed words.
 * @return The number of set bits, or zero for a nonpositive limit.
 */
s32 func_002D42B0(const FieldBitCountState* object);

/**
 * @brief Count the set bits below the stored signed bit limit.
 * @param object Receiver containing the bit limit and packed words.
 * @return The number of set bits, or zero for a nonpositive limit.
 */
s32 func_002D4850(const FieldBitCountState* object);

/**
 * @brief Return the fixed value 2.
 * @param object Receiver or first argument; unused.
 * @return Always 2.
 */
s32 func_002CAF30(void* object);

/**
 * @brief Return the fixed value 2.
 * @param object Receiver or first argument; unused.
 * @return Always 2.
 */
s32 func_002CD940(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_002CD9B0(void* object);

/**
 * @brief Return the fixed value 9.
 * @param object Receiver or first argument; unused.
 * @return Always 9.
 */
s32 func_002CDA70(void* object);

/**
 * @brief Return the fixed value 14.
 * @param object Receiver or first argument; unused.
 * @return Always 14.
 */
s32 func_002D1C40(void* object);

/**
 * @brief Clear a 128-bit vector value.
 * @param vector Value to clear.
 */
void func_002CC6D0(unsigned __int128* vector);

/**
 * @brief Write the difference between selected floats in an eight-byte record array.
 * @param object Object containing the array pointer and count.
 * @param result Destination for the difference; unchanged if the array is absent.
 */
void func_002D5540(void* object, float* result);

#ifdef __cplusplus
}
#endif

#endif
