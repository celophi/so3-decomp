#ifndef SO3_OVERLAYS_3454_00_TEXT_001ED3E0_H
#define SO3_OVERLAYS_3454_00_TEXT_001ED3E0_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DescriptorF2520
{
    u8 unk00[6];
    u16 unk06;
} DescriptorF2520;

typedef struct CachedDescriptorF2520
{
    DescriptorF2520* descriptor;
    u32 unk04;
} CachedDescriptorF2520;

typedef struct RecordF5C
{
    s32 unk00;
    s32 unk04;
    s32 unk08;
    void* unk0C;
} RecordF5C;

typedef struct StateF5E10 StateF5E10;
typedef struct StateF5E60 StateF5E60;

/**
 * @brief Save a descriptor pointer and its halfword field.
 * @param cache Destination for the pointer and cached value.
 * @param descriptor Descriptor to read.
 */
void func_001F2520(CachedDescriptorF2520* cache, DescriptorF2520* descriptor);

/**
 * @brief Store a value in the last field of a record.
 * @param record Record to update.
 * @param value Value to store.
 * @return The input record.
 */
RecordF5C* func_001F5CD0(RecordF5C* record, void* value);

/**
 * @brief Set the first three record fields to -1 and clear the last field.
 * @param record Record to update.
 * @return The input record.
 */
RecordF5C* func_001F5CE0(RecordF5C* record);

/**
 * @brief Store a value in the last field of a record.
 * @param record Record to update.
 * @param value Value to store.
 * @return The input record.
 */
RecordF5C* func_001F5D00(RecordF5C* record, void* value);

/**
 * @brief Set the first three record fields to -1 and clear the last field.
 * @param record Record to update.
 * @return The input record.
 */
RecordF5C* func_001F5D10(RecordF5C* record);

/**
 * @brief Return a record without changing it.
 * @param record Record to return.
 * @return The input record.
 */
RecordF5C* func_001F5D30(RecordF5C* record);

/**
 * @brief Store a value in the last field of a record.
 * @param record Record to update.
 * @param value Value to store.
 * @return The input record.
 */
RecordF5C* func_001F5D40(RecordF5C* record, void* value);

/**
 * @brief Set the first three record fields to -1 and clear the last field.
 * @param record Record to update.
 * @return The input record.
 */
RecordF5C* func_001F5D50(RecordF5C* record);

/**
 * @brief Store a value in the last field of a record.
 * @param record Record to update.
 * @param value Value to store.
 * @return The input record.
 */
RecordF5C* func_001F5D70(RecordF5C* record, void* value);

/**
 * @brief Set the first three record fields to -1 and clear the last field.
 * @param record Record to update.
 * @return The input record.
 */
RecordF5C* func_001F5D80(RecordF5C* record);

/**
 * @brief Store a value in the last field of a record.
 * @param record Record to update.
 * @param value Value to store.
 * @return The input record.
 */
RecordF5C* func_001F5DA0(RecordF5C* record, void* value);

/**
 * @brief Set the first three record fields to -1 and clear the last field.
 * @param record Record to update.
 * @return The input record.
 */
RecordF5C* func_001F5DB0(RecordF5C* record);

/**
 * @brief Return a record without changing it.
 * @param record Record to return.
 * @return The input record.
 */
RecordF5C* func_001F5DD0(RecordF5C* record);

/**
 * @brief Store a value in the last field of a record.
 * @param record Record to update.
 * @param value Value to store.
 * @return The input record.
 */
RecordF5C* func_001F5DE0(RecordF5C* record, void* value);

/**
 * @brief Set the first three record fields to -1 and clear the last field.
 * @param record Record to update.
 * @return The input record.
 */
RecordF5C* func_001F5DF0(RecordF5C* record);

/**
 * @brief Store a value in the last field of a record.
 * @param record Record to update.
 * @param value Value to store.
 * @return The input record.
 */
RecordF5C* func_001F5E30(RecordF5C* record, void* value);

/**
 * @brief Set the first three record fields to -1 and clear the last field.
 * @param record Record to update.
 * @return The input record.
 */
RecordF5C* func_001F5E40(RecordF5C* record);

/**
 * @brief Store a value in the last field of a record.
 * @param record Record to update.
 * @param value Value to store.
 * @return The input record.
 */
RecordF5C* func_001F5E90(RecordF5C* record, void* value);

/**
 * @brief Store a value in the last field of a record.
 * @param record Record to update.
 * @param value Value to store.
 * @return The input record.
 */
RecordF5C* func_001F5EA0(RecordF5C* record, void* value);

/**
 * @brief Set the first three record fields to -1 and clear the last field.
 * @param record Record to update.
 * @return The input record.
 */
RecordF5C* func_001F5EB0(RecordF5C* record);

/**
 * @brief Set the first three record fields to -1 and clear the last field.
 * @param record Record to update.
 * @return The input record.
 */
RecordF5C* func_001F5ED0(RecordF5C* record);

/**
 * @brief Clear the status byte in each of four state entries.
 * @param state Object containing the entries.
 */
void func_001F5E10(StateF5E10* state);

/**
 * @brief Clear several state fields and reset one index to -1.
 * @param state Object containing the fields.
 */
void func_001F5E60(StateF5E60* state);

#ifdef __cplusplus
}
#endif

#endif
