#ifndef SO3_OVERLAYS_BOOT_TEXT_001EEC80_H
#define SO3_OVERLAYS_BOOT_TEXT_001EEC80_H

#include "types.h"
#include "overlays/boot/text_001DD3C0.h"

/** @brief A 48-byte record whose leading four-float value carries its scalar key as the fourth component. */
typedef struct BootVectorCurveStateKey
{
    float value[3];
    float key;
    u8 unk10[0x20];
} BootVectorCurveStateKey;

/** @brief Partial record-array receiver with counts, span, and packed controls. */
typedef struct BootVectorCurveTrackState
{
    u8 unk00[4];
    BootVectorCurveStateKey* entries;
    u8 unk08[0x38];
    s32 cycle_count;
    float span;
    s16 count;
    s16 capacity;
    s16 unk4C;
    s16 unk4E;
    s16 cached_index;
    u8 before_mode : 4;
    u8 after_mode : 4;
    u8 repeats : 1;
    u8 external_keys : 1;
    u8 unk53_other : 6;
} BootVectorCurveTrackState;

/** @brief A scalar key followed by three independent float values. */
typedef struct BootFloatCurveStateKey
{
    float key;
    float value;
    float in_tangent;
    float out_tangent;
} BootFloatCurveStateKey;

/** @brief Partial array receiver with counts, storage, and packed controls. */
typedef struct BootFloatCurveTrackState
{
    u8 unk00[4];
    BootFloatCurveStateKey* entries;
    u8 unk08[0x10];
    s32 cycle_count;
    float span;
    s16 count;
    s16 capacity;
    s16 unk24;
    s16 unk26;
    s16 cached_index;
    u8 before_mode : 4;
    u8 after_mode : 4;
    u8 repeats : 1;
    u8 external_keys : 1;
    u8 unk2B_other : 6;
} BootFloatCurveTrackState;

/** @brief A 32-byte record with a scalar key and an aligned four-float value. */
typedef struct BootKeyEntry32
{
    float key;
    u8 unk04[0xC];
    float value[4];
} __attribute__((aligned(16))) BootKeyEntry32;

/** @brief Partial array receiver with counts, storage, and packed controls. */
typedef struct BootState1F1580
{
    u8 unk00[4];
    BootKeyEntry32* entries;
    u8 unk08[0x28];
    u32 cycle_count;
    float span;
    s16 count;
    s16 capacity;
    s16 unk3C;
    s16 unk3E;
    s16 cached_index;
    u8 before_mode : 4;
    u8 after_mode : 4;
    u8 repeats : 1;
    u8 external_keys : 1;
    u8 unk43_other : 6;
} BootState1F1580;

/** Three float components followed by their scalar key. */
typedef struct BootVectorStateKey
{
    float values[3];
    float key;
} __attribute__((aligned(16))) BootVectorStateKey;

/** Partial vector-key array receiver with packed control fields. */
typedef struct BootVectorTrackState
{
    u8 unk00[4];
    BootVectorStateKey* entries;
    u8 unk08[0x18];
    s32 cycle_count;
    float span;
    s16 count;
    s16 capacity;
    s16 unk2C;
    s16 unk2E;
    s16 cached_index;
    u8 before_mode : 4;
    u8 after_mode : 4;
    u8 repeats : 1;
    u8 external_keys : 1;
    u8 unk33_other : 6;
} BootVectorTrackState;

/** Float key and value stored in the indexed array. */
typedef struct BootFloatStateKey
{
    float key;
    float value;
} BootFloatStateKey;

/** Partial float-entry array with counts, cached span, and packed control fields. */
typedef struct BootFloatTrackState
{
    u8 unk00[4];
    BootFloatStateKey* entries;
    u8 unk08[8];
    s32 cycle_count;
    float span;
    s16 count;
    s16 capacity;
    s16 unk1C;
    s16 unk1E;
    s16 cached_index;
    u8 before_mode : 4;
    u8 after_mode : 4;
    u8 repeats : 1;
    u8 external_keys : 1;
    u8 unk23_other : 6;
} BootFloatTrackState;

/** @brief A 48-byte record with a scalar key, an aligned four-float value and a further payload. */
typedef struct BootKeyEntry48
{
    float key;
    u8 unk04[0xC];
    float value[4];
    u8 unk20[0x10];
} __attribute__((aligned(16))) BootKeyEntry48;

/** @brief Partial 48-byte record-array receiver with packed control fields. */
typedef struct BootState1F4730
{
    u8 unk00[4];
    BootKeyEntry48* entries;
    u8 unk08[0x38];
    u32 cycle_count;
    float span;
    s16 count;
    s16 capacity;
    s16 unk4C;
    s16 unk4E;
    s16 cached_index;
    u8 before_mode : 4;
    u8 after_mode : 4;
    u8 repeats : 1;
    u8 external_keys : 1;
    u8 unk53_other : 6;
} BootState1F4730;

/** @brief An eight-byte record with an observed signed scalar key. */
typedef struct BootQuaternionStateKey
{
    u8 unk00[6];
    s16 key;
} BootQuaternionStateKey;

/** @brief Partial record-array receiver with counts, span, and packed controls. */
typedef struct BootQuaternionTrackState
{
    u8 unk00[4];
    BootQuaternionStateKey* entries;
    u8 unk08[8];
    u32 cycle_count;
    float span;
    s16 count;
    s16 capacity;
    s16 unk1C;
    s16 unk1E;
    s16 cached_index;
    u8 before_mode : 4;
    u8 after_mode : 4;
    u8 repeats : 1;
    u8 external_keys : 1;
    u8 unk23_other : 6;
} BootQuaternionTrackState;

/** @brief Partial 32-byte record-array receiver with packed control fields. */
typedef struct BootState1F47F0
{
    u8 unk00[4];
    BootKeyEntry32* entries;
    u8 unk08[0x28];
    u32 cycle_count;
    float span;
    s16 count;
    s16 capacity;
    s16 unk3C;
    s16 unk3E;
    s16 cached_index;
    u8 before_mode : 4;
    u8 after_mode : 4;
    u8 repeats : 1;
    u8 external_keys : 1;
    u8 unk43_other : 6;
} BootState1F47F0;

/** Partial two-entry history of paired float values. */
typedef struct BootFloatHistoryState
{
    u8 unk00[4];
    s16 count;
    s16 next_index;
    u8 unk08[12];
    float values[2];
    float unk1C[2];
} BootFloatHistoryState;

/** @brief Partial scalar record containing four inputs and its endpoint range. */
typedef struct BootFloatSegmentState
{
    float start_value;
    float end_value;
    float start_tangent;
    float end_tangent;
    float start_key;
    float end_key;
    float key_span;
} BootFloatSegmentState;

#ifdef __cplusplus
class FieldVec4A;
class FieldVec4B;
template <class T> struct BootTrackPool;
class BootVectorSegmentBase;
class BootFloatTrack;
class BootFloatCurveTrack;
class BootVectorTrack;
class BootClass171B20;
class BootVectorHistoryBase;
class BootFloatHistoryBase;
class BootVectorCurveTrack;
class BootFloatTrackBase;
class BootVectorTrackBase;
class BootClass1718C0;
class BootFloatCurveTrackBase;
class BootClass171A70;
class BootVectorCurveTrackBase;
class BootClass171680;
class BootQuaternionTrackBase;
class BootPooledVectorCurveTrack;
class BootPooledVectorTrack;
extern "C" {
#endif

/**
 * @brief Copy an indexed entry's key and values to the requested outputs.
 * @param track Record-array receiver.
 * @param index Nonnegative entry index, checked against capacity.
 * @param key Optional output for the entry key.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @return One if read, or zero if storage is absent or the index is outside capacity.
 */
s32 float_curve_track_read_entry(BootFloatCurveTrackState* track, s32 index, float* key, float* value, float* in_tangent, float* out_tangent);

/**
 * @brief Insert three values and their key before an existing entry.
 * @param track Record-array receiver with a nonnegative entry count.
 * @param index Nonnegative insertion index, less than the current entry count.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key associated with the inserted entry.
 * @return One if inserted, or zero if storage, index, or remaining capacity is invalid.
 */
s32 float_curve_track_insert_curve_key(BootFloatCurveTrackState* track, s32 index, const float* value, const float* in_tangent, const float* out_tangent,
                                       float key);

/**
 * @brief Replace an indexed three-value entry and update the span for the last entry.
 * @param track Record-array receiver.
 * @param index Nonnegative entry index, checked against capacity.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key associated with the entry.
 * @return One if stored, or zero if storage is absent or the index is outside capacity.
 */
s32 float_curve_track_replace_curve_key(BootFloatCurveTrackState* track, s32 index, const float* value, const float* in_tangent, const float* out_tangent,
                                        float key);

/**
 * @brief Append three values and their key, updating the span and entry count.
 * @param track Record-array receiver with a nonnegative entry count.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key associated with the new entry.
 * @return One if appended, or zero if storage is absent or capacity is exhausted.
 */
s32 float_curve_track_append_entry(BootFloatCurveTrackState* track, const float* value, const float* in_tangent, const float* out_tangent, float key);

/**
 * @brief Normalize a key across the cached span and store its signed period count.
 * @param track Receiver with 48-byte records and a nonzero cached key span.
 * @param key Key whose period count is representable as a signed 32-bit integer.
 * @return Normalized key, with odd-period reflection selected by the control fields.
 */
float vector_curve_track_update_cycle_count(BootVectorCurveTrackState* track, float key);

/**
 * @brief Normalize a key across the cached span and store its signed period count.
 * @param track Receiver with vector-key records and a nonzero cached key span.
 * @param key Key whose period count is representable as a signed 32-bit integer.
 * @return Normalized key, with odd-period reflection selected by the control fields.
 */
float vector_track_update_cycle_count(BootVectorTrackState* track, float key);

/**
 * @brief Normalize a key across the cached span and store its signed period count.
 * @param track Receiver with float-key entries and a nonzero cached key span.
 * @param key Key whose period count is representable as a signed 32-bit integer.
 * @return Normalized key, with odd-period reflection selected by the control fields.
 */
float float_track_update_cycle_count(BootFloatTrackState* track, float key);

/**
 * @brief Normalize a key across the cached span and store its signed period count.
 * @param track Receiver with record storage and a nonzero cached key span.
 * @param key Key whose period count is representable as a signed 32-bit integer.
 * @return Normalized key, with odd-period reflection selected by the control fields.
 */
float float_curve_track_update_cycle_count(BootFloatCurveTrackState* track, float key);

/**
 * @brief Find the entries around a key, starting from the cached cursor.
 * @param track Track to search.
 * @param key Key to place.
 * @param lower Receives the lower entry index.
 * @param upper Receives the upper entry index.
 * @return One when a reflecting end mode extends the first or last segment, otherwise zero.
 */
u8 vector_curve_track_find_surrounding_keys(BootVectorCurveTrackBase* track, float key, s32* lower, s32* upper);

/**
 * @brief Find the entries around a key, starting from the cached cursor.
 * @param track Track to search.
 * @param key Key to place.
 * @param lower Receives the lower entry index.
 * @param upper Receives the upper entry index.
 * @return One when a reflecting end mode extends the first or last segment, otherwise zero.
 */
u8 vector_track_find_surrounding_keys(BootVectorTrackBase* track, float key, s32* lower, s32* upper);

/**
 * @brief Find the entries around a key, starting from the cached cursor.
 * @param track Track to search.
 * @param key Key to place.
 * @param lower Receives the lower entry index.
 * @param upper Receives the upper entry index.
 * @return One when a reflecting end mode extends the first or last segment, otherwise zero.
 */
u8 float_curve_track_find_surrounding_keys(BootFloatCurveTrackBase* track, float key, s32* lower, s32* upper);

/**
 * @brief Find the entries around a key, starting from the cached cursor.
 * @param track Track to search.
 * @param key Key to place.
 * @param lower Receives the lower entry index.
 * @param upper Receives the upper entry index.
 * @return One when a reflecting end mode extends the first or last segment, otherwise zero.
 */
u8 float_track_find_surrounding_keys(BootFloatTrackBase* track, float key, s32* lower, s32* upper);

/**
 * @brief Reset 48-byte record storage, counts, packed controls, and cached indices.
 * @param track Receiver to reset without releasing its current storage.
 */
void vector_curve_track_reset_state(BootVectorCurveTrackState* track);

/**
 * @brief Bind external 48-byte records and cache their first-to-last key span.
 * @param track Array receiver.
 * @param count Positive entry count representable in the receiver count fields.
 * @param entries External storage containing the specified number of entries.
 */
void vector_curve_track_bind_keys(BootVectorCurveTrackState* track, s32 count, BootVectorCurveStateKey* entries);

/**
 * @brief Adjust a scalar key by whole spans determined from the endpoint records.
 * @param track Receiver with positive count, valid storage, and distinct endpoint keys.
 * @param key Scalar key whose normalized span quotient must fit in a signed word.
 * @return Key minus the computed number of endpoint spans, or the key for zero spans.
 */
float vector_curve_track_wrap_key(BootVectorCurveTrackState* track, float key);

/**
 * @brief Release owned record-array storage and clear the array pointer.
 * @param track Receiver whose packed ownership flag distinguishes external storage.
 */
void vector_curve_track_free_keys(BootVectorCurveTrackBase* track);
/**
 * @brief Free a pooled track's keys and give the track back to its pool.
 * @param track Pooled track.
 */
void vector_curve_track_return_to_pool(BootPooledVectorCurveTrack* track);

/**
 * @brief Release owned record-array storage and clear the array pointer.
 * @param track Receiver whose packed ownership flag distinguishes external storage.
 */
void track_171A70_free_keys(BootClass171A70* track);

/**
 * @brief Release owned record-array storage and clear the array pointer.
 * @param track Receiver whose packed ownership flag distinguishes external storage.
 */
void quaternion_track_free_keys(BootQuaternionTrackBase* track);

/**
 * @brief Release owned record-array storage and clear the array pointer.
 * @param track Receiver whose packed ownership flag distinguishes external storage.
 */
void track_171680_free_keys(BootClass171680* track);

/**
 * @brief Reset array storage, counts, packed controls, and cached indices.
 * @param track Receiver to reset without releasing its current storage.
 */
void float_curve_track_reset_state(BootFloatCurveTrackState* track);

/**
 * @brief Reset array storage, counts, packed controls, and cached indices.
 * @param track Receiver to reset without releasing its current storage.
 */
void track_1718C0_reset_state(BootState1F1580* track);

/**
 * @brief Release owned array storage and clear the array pointer.
 * @param track Receiver whose packed ownership flag distinguishes external storage.
 */
void float_curve_track_free_keys(BootFloatCurveTrackBase* track);

/**
 * @brief Release owned array storage and clear the array pointer.
 * @param track Receiver whose packed ownership flag distinguishes external storage.
 */
void track_1718C0_free_keys(BootClass1718C0* track);

/**
 * @brief Release owned array storage and clear the array pointer.
 * @param track Receiver whose packed ownership flag distinguishes external storage.
 */
void vector_track_free_keys(BootVectorTrackBase* track);
/**
 * @brief Free a pooled track's keys and give the track back to its pool.
 * @param track Pooled track.
 */
void vector_track_return_to_pool(BootPooledVectorTrack* track);

/**
 * @brief Release owned array storage and clear the array pointer.
 * @param track Receiver whose packed ownership flag distinguishes external storage.
 */
void float_track_free_keys(BootFloatTrackBase* track);

/**
 * @brief Adjust a scalar key by whole spans determined from the endpoint records.
 * @param track Receiver with positive count, valid storage, and distinct endpoint keys.
 * @param key Scalar key whose normalized span quotient must fit in a signed word.
 * @return Key minus the computed number of endpoint spans, or the key for zero spans.
 */
float track_1718C0_wrap_key(BootState1F1580* track, float key);

/**
 * @brief Return the last-to-first key difference, or zero below two records.
 * @param track Receiver with valid storage when its count is at least two.
 * @return Difference between the last and first scalar keys, or zero.
 */
float track_1718C0_get_key_span(BootState1F1580* track);

/**
 * @brief Test whether the 32-byte record array contains an exactly equal key.
 * @param track Receiver with valid storage when its count is positive.
 * @param key Scalar key to find.
 * @return One for an equal key, or zero when none is present.
 */
s32 track_1718C0_has_key(BootState1F1580* track, float key);

/**
 * @brief Bind external 32-byte records and cache their first-to-last key span.
 * @param track Array receiver.
 * @param count Positive entry count representable in the receiver count fields.
 * @param entries External storage containing the specified number of entries.
 */
void track_1718C0_bind_keys(BootState1F1580* track, s32 count, BootKeyEntry32* entries);

/**
 * @brief Test whether the 48-byte record array contains an exactly equal key.
 * @param track Receiver with valid storage when its count is positive.
 * @param key Scalar key to find.
 * @return One for an equal key, or zero when none is present.
 */
s32 vector_curve_track_has_key(BootVectorCurveTrackState* track, float key);

/**
 * @brief Return the last-to-first key difference, or zero below two records.
 * @param track Receiver with valid storage when its count is at least two.
 * @return Difference between the last and first scalar keys, or zero.
 */
float vector_curve_track_get_key_span(BootVectorCurveTrackState* track);

/**
 * @brief Store four scalar inputs and an endpoint span, substituting one for zero.
 * @param segment Receiver of the inputs, endpoints, and span.
 * @param start_value Value at the start_key key.
 * @param start_tangent Tangent at the start_key key.
 * @param end_value Value at the end_key key.
 * @param end_tangent Tangent at the end_key key.
 * @param start_key Key the segment starts at.
 * @param end_key Key the segment ends at.
 */
void float_segment_set_endpoints(BootFloatSegmentState* segment, const float* start_value, const float* start_tangent, const float* end_value,
                                 const float* end_tangent, float start_key, float end_key);

/**
 * @brief Reset vector-key storage, counts, control fields, and cached indices.
 * @param track Array receiver to reset without releasing its current storage.
 */
void vector_track_reset_state(BootVectorTrackState* track);

/**
 * @brief Bind external vector-key storage and cache its first-to-last key span.
 * @param track Array receiver.
 * @param count Positive entry count representable in the receiver count fields.
 * @param entries External storage containing the specified number of entries.
 */
void vector_track_bind_keys(BootVectorTrackState* track, s32 count, BootVectorStateKey* entries);

/**
 * @brief Test whether the vector-key array contains an exactly equal key.
 * @param track Receiver with valid storage when its count is positive.
 * @param key Key to find.
 * @return One if a key matches, or zero otherwise.
 */
s32 vector_track_has_key(BootVectorTrackState* track, float key);

/**
 * @brief Compute the span between the last and first vector-entry keys.
 * @param track Receiver with valid storage when it has at least two entries.
 * @return Key span, or zero when fewer than two entries exist.
 */
float vector_track_get_key_span(BootVectorTrackState* track);

/**
 * @brief Wrap a key by the first-to-last vector-entry key span.
 * @param track Receiver with valid nonempty storage and a nonzero key span.
 * @param key Key to wrap using truncation after adjusting negative positions.
 * @return Key with the computed whole spans subtracted.
 */
float vector_track_wrap_key(BootVectorTrackState* track, float key);

/**
 * @brief Read either or both members of an indexed float entry.
 * @param track Array receiver.
 * @param index Nonnegative entry index, checked against capacity.
 * @param key Optional destination for the entry key.
 * @param value Optional destination for the entry value.
 * @return One for an available slot, or zero if storage is absent or the index is too large.
 */
s32 float_track_read_entry(BootFloatTrackState* track, s32 index, float* key, float* value);

/**
 * @brief Read the vector value associated with the first exactly equal key.
 * @param track Receiver with 48-byte records, valid when its count is positive.
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A vector_curve_track_find_key_value(BootVectorCurveTrackState* track, float key);

/**
 * @brief Read the vector value associated with the first exactly equal key.
 * @param track Receiver with vector-key entries, valid when its count is positive.
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A vector_track_find_key_value(BootVectorTrackState* track, float key);

/**
 * @brief Read the vector value associated with the first exactly equal key.
 * @param track Receiver with 32-byte records, valid when its count is positive.
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A track_1718C0_find_key_value(BootState1F1580* track, float key);

/**
 * @brief Store paired float values in the next slot of a two-entry history.
 * @param history History whose write index wraps and count saturates at two.
 * @param value First float value to copy.
 * @param associated Second float value to store.
 */
void float_history_push(BootFloatHistoryState* history, const float* value, float associated);

/**
 * @brief Insert a float entry before an existing index and shift following entries.
 * @param track Array receiver with spare capacity.
 * @param index Nonnegative index less than the current count.
 * @param value Entry value to copy.
 * @param key Key associated with the entry.
 * @return One if inserted, or zero if storage is absent, full, or the index is too large.
 */
s32 float_track_insert_entry(BootFloatTrackState* track, s32 index, const float* value, float key);

/**
 * @brief Replace an indexed float entry and update the span when it is the last entry.
 * @param track Array receiver.
 * @param index Nonnegative entry index, checked against capacity.
 * @param value Entry value to copy.
 * @param key Key associated with the entry.
 * @return One if stored, or zero if storage is absent or the index is outside capacity.
 */
s32 float_track_replace_entry(BootFloatTrackState* track, s32 index, const float* value, float key);

/**
 * @brief Append a float entry and update the cached key span.
 * @param track Array receiver.
 * @param value Entry value to copy.
 * @param key Key associated with the entry.
 * @return One if appended, or zero if storage is absent or full.
 */
s32 float_track_append_entry(BootFloatTrackState* track, const float* value, float key);

/**
 * @brief Perform no work.
 * @param track Receiver or first argument; unused.
 */
void func_001EECA0(void* track);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EED30(void* track);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EED40(void* track);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EED50(void* track);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EED60(void* track);

/**
 * @brief Perform no work.
 * @param track Receiver or first argument; unused.
 */
void func_001EED70(void* track);

/**
 * @brief Perform no work.
 * @param track Receiver or first argument; unused.
 */
void func_001EED80(void* track);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 vector_curve_track_on_append_key(void* track);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 vector_curve_track_on_replace_key(void* track);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 vector_curve_track_on_insert_key(void* track);

/**
 * @brief Perform no work.
 * @param track Receiver or first argument; unused.
 */
void vector_curve_track_on_set_single_key(void* track);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 float_curve_track_on_append_key(void* track);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 float_curve_track_on_replace_key(void* track);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 float_curve_track_on_insert_key(void* track);

/**
 * @brief Perform no work.
 * @param track Receiver or first argument; unused.
 */
void float_curve_track_on_set_single_key(void* track);

/**
 * @brief Perform no work.
 * @param track Receiver or first argument; unused.
 */
void float_track_on_set_single_key(void* track);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 float_track_on_insert_key(void* track);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 float_track_on_replace_key(void* track);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 float_track_on_append_key(void* track);

/**
 * @brief Perform no work.
 * @param track Receiver or first argument; unused.
 */
void vector_track_on_set_single_key(void* track);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 vector_track_on_insert_key(void* track);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 vector_track_on_replace_key(void* track);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 vector_track_on_append_key(void* track);

/**
 * @brief Perform no work.
 * @param track Receiver or first argument; unused.
 */
void track_1718C0_on_set_single_key(void* track);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 track_1718C0_on_insert_key(void* track);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 track_1718C0_on_replace_key(void* track);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 track_1718C0_on_append_key(void* track);

/**
 * @brief Perform no work.
 * @param history Receiver or first argument; unused.
 */
void func_001F4950(void* history);

/**
 * @brief Perform no work.
 * @param history Receiver or first argument; unused.
 */
void func_001F4960(void* history);

/**
 * @brief Perform no work.
 * @param history Receiver or first argument; unused.
 */
void func_001F4970(void* history);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 track_171A70_on_append_key(void* track);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 track_171A70_on_replace_key(void* track);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 track_171A70_on_insert_key(void* track);

/**
 * @brief Perform no work.
 * @param track Receiver or first argument; unused.
 */
void track_171A70_on_set_single_key(void* track);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 quaternion_track_on_append_key(void* track);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 quaternion_track_on_replace_key(void* track);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 quaternion_track_on_insert_key(void* track);

/**
 * @brief Perform no work.
 * @param track Receiver or first argument; unused.
 */
void quaternion_track_on_set_single_key(void* track);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 track_171680_on_append_key(void* track);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 track_171680_on_replace_key(void* track);

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 track_171680_on_insert_key(void* track);

/**
 * @brief Perform no work.
 * @param track Receiver or first argument; unused.
 */
void track_171680_on_set_single_key(void* track);

/**
 * @brief Return the key storage.
 * @param track Track to read.
 * @return Key array, or null.
 */
BootVectorCurveStateKey* vector_curve_track_get_keys(const BootVectorCurveTrackState* track);

/**
 * @brief Return the key storage.
 * @param track Track to read.
 * @return Key array, or null.
 */
BootKeyEntry32* track_1718C0_get_keys(const BootState1F1580* track);

/**
 * @brief Return the key storage.
 * @param track Track to read.
 * @return Key array, or null.
 */
BootVectorStateKey* vector_track_get_keys(const BootVectorTrackState* track);

/**
 * @brief Write a zero value; the track's value when it has no keys.
 * @param track Receives the zero value.
 * @return Zero.
 */
float float_curve_track_get_zero_value(void* track);

/**
 * @brief Write a zero value; the track's value when it has no keys.
 * @param track Receives the zero value.
 * @return Zero.
 */
float float_track_get_zero_value(void* track);

/**
 * @brief Return how fast the value changed at the last sample, per second.
 * @param track Track to read.
 * @param value Receives the rate.
 */
void float_curve_track_get_value_rate(void* track, float* value);

/**
 * @brief Return how fast the value changed at the last sample, per second.
 * @param track Track to read.
 * @param value Receives the rate.
 */
void float_track_get_value_rate(void* track, float* value);

/**
 * @brief Forget the stored samples.
 * @param history History to clear.
 */
void history_171B20_reset(BootClass171B20* history);

/**
 * @brief Forget the stored samples.
 * @param history History to clear.
 */
void vector_history_reset(BootVectorHistoryBase* history);

/**
 * @brief Forget the stored samples.
 * @param history History to clear.
 */
void float_history_reset(BootFloatHistoryBase* history);

/**
 * @brief Write a zero value; the track's value when it has no keys.
 * @param result Receives the zero value.
 */
void track_1718C0_get_zero_value(u32* result);

/**
 * @brief Write a zero value; the track's value when it has no keys.
 * @param result Receives the zero value.
 */
void vector_track_get_zero_value(u32* result);

/**
 * @brief Write a zero value; the track's value when it has no keys.
 * @param result Receives the zero value.
 */
void track_171A70_get_zero_value(u32* result);

/**
 * @brief Write a zero value; the track's value when it has no keys.
 * @param result Receives the zero value.
 */
void quaternion_track_get_zero_value(u32* result);

/**
 * @brief Write a zero value; the track's value when it has no keys.
 * @param result Receives the zero value.
 */
void track_171680_get_zero_value(u32* result);

/**
 * @brief Write a zero value; the track's value when it has no keys.
 * @param result Receives the zero value.
 */
void vector_curve_track_get_zero_value(u32* result);

/**
 * @brief Write the difference between the last and first float values in an eight-byte record array.
 * @param track Object containing the array pointer and count.
 * @param result Destination for the difference; unchanged if the array is absent.
 */
void float_track_get_end_delta(void* track, float* result);

/**
 * @brief Write the difference between the last and first float values in a sixteen-byte record array.
 * @param track Object containing the array pointer and count.
 * @param result Destination for the difference; unchanged if the array is absent.
 */
void float_curve_track_get_end_delta(void* track, float* result);

/** Clear the last sampled value, then reset the key state. */
void vector_curve_track_reset_sampling(void* track);
/** Clear the last sampled value, then reset the key state. */
void vector_track_reset_sampling(void* track);

/**
 * @brief Evaluate a vector range at a key.
 * @param range Range to evaluate.
 * @param key Evaluation key.
 * @return Evaluated vector.
 */
FieldVec4B vector_segment_evaluate(const BootVectorSegmentBase* range, float key);

/**
 * @brief Mark a track's pool slot as free.
 * @param pool Pool that owns the track.
 * @param track Track to release.
 */
void vector_curve_track_pool_free(BootTrackPool<BootPooledVectorCurveTrack>* pool, BootPooledVectorCurveTrack* track);

/**
 * @brief Mark a track's pool slot as free.
 * @param pool Pool that owns the track.
 * @param track Track to release.
 */
void vector_track_pool_free(BootTrackPool<BootPooledVectorTrack>* pool, BootPooledVectorTrack* track);

/**
 * @brief Return how fast the value changed at the last sample, per second.
 * @param track Track to read.
 * @param output Receives the rate.
 */
void vector_curve_track_get_value_rate(const BootVectorCurveTrack* track, FieldVec4B* output);

/**
 * @brief Clear the last sampled value, then reset the key state.
 * @param track Track to reset.
 */
void float_curve_track_reset_sampling(BootFloatCurveTrack* track);

/**
 * @brief Return how fast the value changed at the last sample, per second.
 * @param track Track to read.
 * @param output Receives the rate.
 */
void vector_track_get_value_rate(const BootVectorTrack* track, FieldVec4B* output);

/**
 * @brief Forward a keyframe with a key to slot 0x74.
 * @param track Track to use.
 * @param value Key value.
 * @param key Key the keyframe sits at.
 */
void float_track_set_single_key(BootFloatTrackBase* track, const float* value, float key);

/**
 * @brief Forward an indexed keyframe with a key to slot 0x70.
 * @param track Track to use.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @return Nonzero when the keyframe was stored.
 */
s32 float_track_insert_key(BootFloatTrackBase* track, s32 index, float key, const float* value);

/**
 * @brief Forward an indexed keyframe with a key to slot 0x6C.
 * @param track Track to use.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @return Nonzero when the keyframe was stored.
 */
s32 float_track_replace_key(BootFloatTrackBase* track, s32 index, float key, const float* value);

/**
 * @brief Forward a keyframe with a key to slot 0x68.
 * @param track Track to use.
 * @param value Key value.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 float_track_append_key(BootFloatTrackBase* track, const float* value, float key);

/**
 * @brief Forward to slot 0x74.
 * @param track Track to use.
 * @param value Key value.
 * @param key Key the keyframe sits at.
 */
void vector_track_set_single_key(BootVectorTrackBase* track, const FieldVec4A* value, float key);

/**
 * @brief Forward to slot 0x70.
 * @param track Track to use.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @return Nonzero when the keyframe was stored.
 */
s32 vector_track_insert_key(BootVectorTrackBase* track, s32 index, float key, const FieldVec4A* value);

/**
 * @brief Forward to slot 0x6C.
 * @param track Track to use.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @return Nonzero when the keyframe was stored.
 */
s32 vector_track_replace_key(BootVectorTrackBase* track, s32 index, float key, const FieldVec4A* value);

/**
 * @brief Forward to slot 0x68.
 * @param track Track to use.
 * @param value Key value.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 vector_track_append_key(BootVectorTrackBase* track, const FieldVec4A* value, float key);

/**
 * @brief Forward to slot 0x74.
 * @param track Track to use.
 * @param value Key value.
 * @param key Key the keyframe sits at.
 */
void track_1718C0_set_single_key(BootClass1718C0* track, const FieldVec4A* value, float key);

/**
 * @brief Forward to slot 0x70.
 * @param track Track to use.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @return Nonzero when the keyframe was stored.
 */
s32 track_1718C0_insert_key(BootClass1718C0* track, s32 index, float key, const FieldVec4A* value);

/**
 * @brief Forward to slot 0x6C.
 * @param track Track to use.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @return Nonzero when the keyframe was stored.
 */
s32 track_1718C0_replace_key(BootClass1718C0* track, s32 index, float key, const FieldVec4A* value);

/**
 * @brief Forward to slot 0x68.
 * @param track Track to use.
 * @param value Key value.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 track_1718C0_append_key(BootClass1718C0* track, const FieldVec4A* value, float key);

/**
 * @brief Forward to slot 0x68.
 * @param track Track to use.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 track_171A70_append_key(BootClass171A70* track, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

/**
 * @brief Forward to slot 0x6C.
 * @param track Track to use.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @return Nonzero when the keyframe was stored.
 */
s32 track_171A70_replace_key(BootClass171A70* track, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

/**
 * @brief Forward to slot 0x70.
 * @param track Track to use.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @return Nonzero when the keyframe was stored.
 */
s32 track_171A70_insert_key(BootClass171A70* track, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

/**
 * @brief Forward to slot 0x74.
 * @param track Track to use.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 */
void track_171A70_set_single_key(BootClass171A70* track, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

/**
 * @brief Forward to slot 0x68.
 * @param track Track to use.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 vector_curve_track_append_key(BootVectorCurveTrackBase* track, const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent,
                                  float key);

/**
 * @brief Forward to slot 0x6C.
 * @param track Track to use.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @return Nonzero when the keyframe was stored.
 */
s32 vector_curve_track_replace_key(BootVectorCurveTrackBase* track, s32 index, float key, const FieldVec4A* value, const FieldVec4A* in_tangent,
                                   const FieldVec4A* out_tangent);

/**
 * @brief Forward to slot 0x70.
 * @param track Track to use.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @return Nonzero when the keyframe was stored.
 */
s32 vector_curve_track_insert_key(BootVectorCurveTrackBase* track, s32 index, float key, const FieldVec4A* value, const FieldVec4A* in_tangent,
                                  const FieldVec4A* out_tangent);

/**
 * @brief Forward to slot 0x74.
 * @param track Track to use.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key the keyframe sits at.
 */
void vector_curve_track_set_single_key(BootVectorCurveTrackBase* track, const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent,
                                       float key);

/**
 * @brief Forward to slot 0x68.
 * @param track Track to use.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 float_curve_track_append_key(BootFloatCurveTrackBase* track, const float* value, const float* in_tangent, const float* out_tangent, float key);

/**
 * @brief Forward to slot 0x6C.
 * @param track Track to use.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @return Nonzero when the keyframe was stored.
 */
s32 float_curve_track_replace_key(BootFloatCurveTrackBase* track, s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent);

/**
 * @brief Forward to slot 0x70.
 * @param track Track to use.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @return Nonzero when the keyframe was stored.
 */
s32 float_curve_track_insert_key(BootFloatCurveTrackBase* track, s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent);

/**
 * @brief Forward to slot 0x74.
 * @param track Track to use.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key the keyframe sits at.
 */
void float_curve_track_set_single_key(BootFloatCurveTrackBase* track, const float* value, const float* in_tangent, const float* out_tangent, float key);

/**
 * @brief Forward to slot 0x68.
 * @param track Track to use.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 quaternion_track_append_key(BootQuaternionTrackBase* track, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

/**
 * @brief Forward to slot 0x6C.
 * @param track Track to use.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @return Nonzero when the keyframe was stored.
 */
s32 quaternion_track_replace_key(BootQuaternionTrackBase* track, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first,
                                 const FieldVec4A* second);

/**
 * @brief Forward to slot 0x70.
 * @param track Track to use.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @return Nonzero when the keyframe was stored.
 */
s32 quaternion_track_insert_key(BootQuaternionTrackBase* track, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first,
                                const FieldVec4A* second);

/**
 * @brief Forward to slot 0x74.
 * @param track Track to use.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 */
void quaternion_track_set_single_key(BootQuaternionTrackBase* track, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

/**
 * @brief Find the keyframe with a key and decode its rotation.
 * @param out Receives the rotation, or zero when the key is absent.
 * @param track Keyframe array.
 * @param key Key to find.
 */
void quaternion_track_find_key_value(FieldVec4A* out, BootQuaternionTrackState* track, float key);

/**
 * @brief Forward to slot 0x68.
 * @param track Track to use.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 track_171680_append_key(BootClass171680* track, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

/**
 * @brief Forward to slot 0x6C.
 * @param track Track to use.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @return Nonzero when the keyframe was stored.
 */
s32 track_171680_replace_key(BootClass171680* track, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

/**
 * @brief Forward to slot 0x70.
 * @param track Track to use.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @return Nonzero when the keyframe was stored.
 */
s32 track_171680_insert_key(BootClass171680* track, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

/**
 * @brief Forward to slot 0x74.
 * @param track Track to use.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 */
void track_171680_set_single_key(BootClass171680* track, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

/**
 * @brief Evaluate a float curve segment at a key.
 * @param segment Segment to evaluate.
 * @param key Key to evaluate at.
 * @return Value at the key.
 */
float float_segment_evaluate(void* segment, float key);

/**
 * @brief Read the value associated with the first exactly equal key.
 * @param track Receiver with valid storage when its count is positive.
 * @param key Key to find.
 * @return Associated value, or zero when no key matches.
 */
float float_track_find_key_value(BootFloatTrackState* track, float key);

/**
 * @brief Read the vector value associated with the first exactly equal key.
 * @param track Receiver with 32-byte records, valid when its count is positive.
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A track_171A70_find_key_value(BootState1F47F0* track, float key);

/**
 * @brief Read the vector value associated with the first exactly equal key.
 * @param track Receiver with 48-byte records, valid when its count is positive.
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A track_171680_find_key_value(BootState1F4730* track, float key);

#ifdef __cplusplus
}
#endif

#endif
