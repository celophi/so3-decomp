#ifndef SO3_OVERLAYS_BOOT_TEXT_001ED4E0_H
#define SO3_OVERLAYS_BOOT_TEXT_001ED4E0_H

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
    float second;
    float third;
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

/** Settings record initialized before calls to the resident rendering interface. */
typedef struct BootDrawSettings
{
    u16 unk00;
    u8 unk02;
    u8 unk03;
    u8 unk04;
    u8 unk05;
    u8 unk06;
    u8 unk07;
    float unk08;
    float unk0C;
    float unk10;
    float unk14;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
} BootDrawSettings;

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
    float unk00;
    float unk04;
    float unk08;
    float unk0C;
    float unk10;
    float unk14;
    float unk18;
} BootFloatSegmentState;

#ifdef __cplusplus
/** GIF tag: the tag word and the register list, four bits per register. */
struct BootGifTag
{
    u64 tag;

    union
    {
        u64 registers;

        struct
        {
            u64 register0 : 4;
            u64 register1 : 4;
            u64 register2 : 4;
            u64 register3 : 4;
            u64 unused : 48;
        } fields;
    };
};

/** One fade strip's packet: upload the strip's image to VRAM, then draw it as a textured sprite. */
struct BootFadeStripPacket
{
    u64 transfer_dma;
    u64 unk08;
    BootGifTag transfer_tag;
    u64 bitbltbuf;
    u64 bitbltbuf_register;
    u64 trxpos;
    u64 trxpos_register;
    u64 trxreg;
    u64 trxreg_register;
    u64 trxdir;
    u64 trxdir_register;
    u64 image_tag;
    u64 unk68;
    u64 image_dma;
    u64 unk78;
    u64 draw_dma;
    u64 unk88;
    BootGifTag draw_tag;
    u64 texflush;
    u64 texflush_register;
    u64 tex0;
    u64 tex0_register;
    u64 prim;
    u64 prim_register;
    u64 rgbaq;
    u64 rgbaq_register;
    BootGifTag sprite_tag;
    u64 uv0;
    u64 xyz0;
    u64 uv1;
    u64 xyz1;
};

/** VRAM area request passed to func_4D93A0. */
struct BootVramRequest
{
    s16 width;
    s16 height;
    s32 size;
    u8 unk08[4];
    s16 unk0c;
    u8 unk0e;
    u8 unk0f;
};

class FieldVec4A;
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
 * @param object Record-array receiver.
 * @param index Nonnegative entry index, checked against capacity.
 * @param key Optional output for the entry key.
 * @param first Optional output for the first value.
 * @param second Optional output for the second value.
 * @param third Optional output for the third value.
 * @return One if read, or zero if storage is absent or the index is outside capacity.
 */
s32 float_curve_track_read_entry(BootFloatCurveTrackState* object, s32 index, float* key, float* first, float* second, float* third);

/**
 * @brief Insert three values and their key before an existing entry.
 * @param object Record-array receiver with a nonnegative entry count.
 * @param index Nonnegative insertion index, less than the current entry count.
 * @param first First value to copy after moving existing entries.
 * @param second Second value to copy after moving existing entries.
 * @param third Third value to copy after moving existing entries.
 * @param key Key associated with the inserted entry.
 * @return One if inserted, or zero if storage, index, or remaining capacity is invalid.
 */
s32 float_curve_track_insert_curve_key(BootFloatCurveTrackState* object, s32 index, const float* first, const float* second, const float* third, float key);

/**
 * @brief Replace an indexed three-value entry and update the span for the last entry.
 * @param object Record-array receiver.
 * @param index Nonnegative entry index, checked against capacity.
 * @param first First value to copy.
 * @param second Second value to copy.
 * @param third Third value to copy.
 * @param key Key associated with the entry.
 * @return One if stored, or zero if storage is absent or the index is outside capacity.
 */
s32 float_curve_track_replace_curve_key(BootFloatCurveTrackState* object, s32 index, const float* first, const float* second, const float* third, float key);

/**
 * @brief Append three values and their key, updating the span and entry count.
 * @param object Record-array receiver with a nonnegative entry count.
 * @param first First value to copy.
 * @param second Second value to copy.
 * @param third Third value to copy.
 * @param key Key associated with the new entry.
 * @return One if appended, or zero if storage is absent or capacity is exhausted.
 */
s32 float_curve_track_append_entry(BootFloatCurveTrackState* object, const float* first, const float* second, const float* third, float key);

/**
 * @brief Normalize a key across the cached span and store its signed period count.
 * @param object Receiver with 48-byte records and a nonzero cached key span.
 * @param key Key whose period count is representable as a signed 32-bit integer.
 * @return Normalized key, with odd-period reflection selected by the control fields.
 */
float vector_curve_track_update_cycle_count(BootVectorCurveTrackState* object, float key);

/**
 * @brief Normalize a key across the cached span and store its signed period count.
 * @param object Receiver with vector-key records and a nonzero cached key span.
 * @param key Key whose period count is representable as a signed 32-bit integer.
 * @return Normalized key, with odd-period reflection selected by the control fields.
 */
float vector_track_update_cycle_count(BootVectorTrackState* object, float key);

/**
 * @brief Normalize a key across the cached span and store its signed period count.
 * @param object Receiver with float-key entries and a nonzero cached key span.
 * @param key Key whose period count is representable as a signed 32-bit integer.
 * @return Normalized key, with odd-period reflection selected by the control fields.
 */
float float_track_update_cycle_count(BootFloatTrackState* object, float key);

/**
 * @brief Normalize a key across the cached span and store its signed period count.
 * @param object Receiver with record storage and a nonzero cached key span.
 * @param key Key whose period count is representable as a signed 32-bit integer.
 * @return Normalized key, with odd-period reflection selected by the control fields.
 */
float float_curve_track_update_cycle_count(BootFloatCurveTrackState* object, float key);

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
 * @param object Receiver to reset without releasing its current storage.
 */
void vector_curve_track_reset_state(BootVectorCurveTrackState* object);

/**
 * @brief Bind external 48-byte records and cache their first-to-last key span.
 * @param object Array receiver.
 * @param count Positive entry count representable in the receiver count fields.
 * @param entries External storage containing the specified number of entries.
 */
void vector_curve_track_bind_keys(BootVectorCurveTrackState* object, s32 count, BootVectorCurveStateKey* entries);

/**
 * @brief Adjust a scalar key by whole spans determined from the endpoint records.
 * @param object Receiver with positive count, valid storage, and distinct endpoint keys.
 * @param key Scalar key whose normalized span quotient must fit in a signed word.
 * @return Key minus the computed number of endpoint spans, or the key for zero spans.
 */
float vector_curve_track_wrap_key(BootVectorCurveTrackState* object, float key);

/**
 * @brief Release owned record-array storage and clear the array pointer.
 * @param object Receiver whose packed ownership flag distinguishes external storage.
 */
void vector_curve_track_free_keys(BootVectorCurveTrackBase* track);
void func_001EEDF0(BootPooledVectorCurveTrack* track);

/**
 * @brief Release owned record-array storage and clear the array pointer.
 * @param object Receiver whose packed ownership flag distinguishes external storage.
 */
void func_001F0960(BootClass171A70* track);

/**
 * @brief Release owned record-array storage and clear the array pointer.
 * @param object Receiver whose packed ownership flag distinguishes external storage.
 */
void quaternion_track_free_keys(BootQuaternionTrackBase* track);

/**
 * @brief Release owned record-array storage and clear the array pointer.
 * @param object Receiver whose packed ownership flag distinguishes external storage.
 */
void func_001F2280(BootClass171680* track);

/**
 * @brief Reset array storage, counts, packed controls, and cached indices.
 * @param object Receiver to reset without releasing its current storage.
 */
void float_curve_track_reset_state(BootFloatCurveTrackState* object);

/**
 * @brief Reset array storage, counts, packed controls, and cached indices.
 * @param object Receiver to reset without releasing its current storage.
 */
void func_001F14F0(BootState1F1580* object);

/**
 * @brief Release owned array storage and clear the array pointer.
 * @param object Receiver whose packed ownership flag distinguishes external storage.
 */
void float_curve_track_free_keys(BootFloatCurveTrackBase* track);

/**
 * @brief Release owned array storage and clear the array pointer.
 * @param object Receiver whose packed ownership flag distinguishes external storage.
 */
void func_001F16F0(BootClass1718C0* track);

/**
 * @brief Release owned array storage and clear the array pointer.
 * @param object Receiver whose packed ownership flag distinguishes external storage.
 */
void vector_track_free_keys(BootVectorTrackBase* track);
void func_001EEEA0(BootPooledVectorTrack* track);

/**
 * @brief Release owned array storage and clear the array pointer.
 * @param object Receiver whose packed ownership flag distinguishes external storage.
 */
void float_track_free_keys(BootFloatTrackBase* track);

/**
 * @brief Adjust a scalar key by whole spans determined from the endpoint records.
 * @param object Receiver with positive count, valid storage, and distinct endpoint keys.
 * @param key Scalar key whose normalized span quotient must fit in a signed word.
 * @return Key minus the computed number of endpoint spans, or the key for zero spans.
 */
float func_001F29D0(BootState1F1580* object, float key);

/**
 * @brief Return the last-to-first key difference, or zero below two records.
 * @param object Receiver with valid storage when its count is at least two.
 * @return Difference between the last and first scalar keys, or zero.
 */
float func_001F2AC0(BootState1F1580* object);

/**
 * @brief Test whether the 32-byte record array contains an exactly equal key.
 * @param object Receiver with valid storage when its count is positive.
 * @param key Scalar key to find.
 * @return One for an equal key, or zero when none is present.
 */
s32 func_001F2B10(BootState1F1580* object, float key);

/**
 * @brief Bind external 32-byte records and cache their first-to-last key span.
 * @param object Array receiver.
 * @param count Positive entry count representable in the receiver count fields.
 * @param entries External storage containing the specified number of entries.
 */
void func_001F2C60(BootState1F1580* object, s32 count, BootKeyEntry32* entries);

/**
 * @brief Adjust a scalar key by whole spans determined from the endpoint records.
 * @param object Receiver with positive count, valid storage, and distinct endpoint keys.
 * @param key Scalar key whose normalized span quotient must fit in a signed word.
 * @return Key minus the computed number of endpoint spans, or the key for zero spans.
 */
float float_curve_track_wrap_key(BootFloatCurveTrackState* object, float key);

/**
 * @brief Find the value stored with the first exactly equal scalar key.
 * @param object Receiver with valid storage when its count is positive.
 * @param key Scalar key to find.
 * @return The first matching value, or zero when the key is absent.
 */
float float_curve_track_find_key_value(BootFloatCurveTrackState* object, float key);

/**
 * @brief Return the last-to-first key difference, or zero below two records.
 * @param object Receiver with valid storage when its count is at least two.
 * @return Difference between the last and first scalar keys, or zero.
 */
float float_curve_track_get_key_span(BootFloatCurveTrackState* object);

/**
 * @brief Test whether the 16-byte record array contains an exactly equal key.
 * @param object Receiver with valid storage when its count is positive.
 * @param key Scalar key to find.
 * @return One for an equal key, or zero when none is present.
 */
s32 float_curve_track_has_key(BootFloatCurveTrackState* object, float key);

/**
 * @brief Bind external 16-byte records and cache their first-to-last key span.
 * @param object Array receiver.
 * @param count Positive entry count representable in the receiver count fields.
 * @param entries External storage containing the specified number of entries.
 */
void float_curve_track_bind_keys(BootFloatCurveTrackState* object, s32 count, BootFloatCurveStateKey* entries);

/**
 * @brief Adjust a scalar key by whole spans determined from the endpoint records.
 * @param object Receiver with positive count, valid storage, and distinct endpoint keys.
 * @param key Scalar key whose normalized span quotient must fit in a signed word.
 * @return Key minus the computed number of endpoint spans, or the key for zero spans.
 */
float func_001F5E20(BootState1F47F0* object, float key);

/**
 * @brief Return the last-to-first key difference, or zero below two records.
 * @param object Receiver with valid storage when its count is at least two.
 * @return Difference between the last and first scalar keys, or zero.
 */
float func_001F5F10(BootState1F47F0* object);

/**
 * @brief Test whether the 32-byte record array contains an exactly equal key.
 * @param object Receiver with valid storage when its count is positive.
 * @param key Scalar key to find.
 * @return One for an equal key, or zero when none is present.
 */
s32 func_001F5F60(BootState1F47F0* object, float key);

/**
 * @brief Return the last-to-first key difference, or zero below two records.
 * @param object Receiver with valid storage when its count is at least two.
 * @return Difference between the last and first scalar keys, or zero.
 */
float func_001F5C50(BootState1F4730* object);

/**
 * @brief Test whether the 48-byte record array contains an exactly equal key.
 * @param object Receiver with valid storage when its count is positive.
 * @param key Scalar key to find.
 * @return One for an equal key, or zero when none is present.
 */
s32 func_001F5BE0(BootState1F4730* object, float key);

/**
 * @brief Bind external 48-byte records and cache their first-to-last key span.
 * @param object Array receiver.
 * @param count Positive entry count representable in the receiver count fields.
 * @param entries External storage containing the specified number of entries.
 */
void func_001F5A00(BootState1F4730* object, s32 count, BootKeyEntry48* entries);

/**
 * @brief Test whether the 48-byte record array contains an exactly equal key.
 * @param object Receiver with valid storage when its count is positive.
 * @param key Scalar key to find.
 * @return One for an equal key, or zero when none is present.
 */
s32 vector_curve_track_has_key(BootVectorCurveTrackState* object, float key);

/**
 * @brief Return the last-to-first key difference, or zero below two records.
 * @param object Receiver with valid storage when its count is at least two.
 * @return Difference between the last and first scalar keys, or zero.
 */
float vector_curve_track_get_key_span(BootVectorCurveTrackState* object);

/**
 * @brief Store four scalar inputs and an endpoint span, substituting one for zero.
 * @param object Receiver of the inputs, endpoints, and span.
 * @param first Input stored at offset 0x00.
 * @param second Input stored at offset 0x08.
 * @param third Input stored at offset 0x04.
 * @param fourth Input stored at offset 0x0C.
 * @param start First endpoint.
 * @param end Second endpoint.
 */
void float_segment_set_endpoints(BootFloatSegmentState* object, const float* first, const float* second, const float* third, const float* fourth, float start, float end);

/**
 * @brief Reset vector-key storage, counts, control fields, and cached indices.
 * @param object Array receiver to reset without releasing its current storage.
 */
void vector_track_reset_state(BootVectorTrackState* object);

/**
 * @brief Bind external vector-key storage and cache its first-to-last key span.
 * @param object Array receiver.
 * @param count Positive entry count representable in the receiver count fields.
 * @param entries External storage containing the specified number of entries.
 */
void vector_track_bind_keys(BootVectorTrackState* object, s32 count, BootVectorStateKey* entries);

/**
 * @brief Test whether the vector-key array contains an exactly equal key.
 * @param object Receiver with valid storage when its count is positive.
 * @param key Key to find.
 * @return One if a key matches, or zero otherwise.
 */
s32 vector_track_has_key(BootVectorTrackState* object, float key);

/**
 * @brief Compute the span between the last and first vector-entry keys.
 * @param object Receiver with valid storage when it has at least two entries.
 * @return Key span, or zero when fewer than two entries exist.
 */
float vector_track_get_key_span(BootVectorTrackState* object);

/**
 * @brief Wrap a key by the first-to-last vector-entry key span.
 * @param object Receiver with valid nonempty storage and a nonzero key span.
 * @param key Key to wrap using truncation after adjusting negative positions.
 * @return Key with the computed whole spans subtracted.
 */
float vector_track_wrap_key(BootVectorTrackState* object, float key);

/**
 * @brief Read either or both members of an indexed float entry.
 * @param object Array receiver.
 * @param index Nonnegative entry index, checked against capacity.
 * @param key Optional destination for the entry key.
 * @param value Optional destination for the entry value.
 * @return One for an available slot, or zero if storage is absent or the index is too large.
 */
s32 float_track_read_entry(BootFloatTrackState* object, s32 index, float* key, float* value);

/**
 * @brief Test whether the float-entry array contains an exactly equal key.
 * @param object Receiver with valid storage when its count is positive.
 * @param key Key to find.
 * @return One if a matching key exists, or zero otherwise.
 */
s32 float_track_has_key(BootFloatTrackState* object, float key);

/**
 * @brief Reset float-entry storage, counts, control fields, and cached indices.
 * @param object Array receiver to reset without releasing its current storage.
 */
void float_track_reset_state(BootFloatTrackState* object);

/**
 * @brief Bind external entry storage and cache its first-to-last key span.
 * @param object Array receiver.
 * @param count Positive entry count representable in the receiver count fields.
 * @param entries External storage containing the specified number of entries.
 */
void float_track_bind_keys(BootFloatTrackState* object, s32 count, BootFloatStateKey* entries);

/**
 * @brief Wrap a key by the span between the first and last entries.
 * @param object Receiver with valid nonempty storage and a nonzero key span.
 * @param key Key to wrap using truncation after adjusting negative positions.
 * @return Key with the computed whole spans subtracted.
 */
float float_track_wrap_key(BootFloatTrackState* object, float key);

/**
 * @brief Read the value associated with the first exactly equal key.
 * @param object Receiver with valid storage when its count is positive.
 * @param key Key to find.
 * @return Associated value, or zero when no key matches.
 */
float float_track_find_key_value(BootFloatTrackState* object, float key);

/**
 * @brief Read the vector value associated with the first exactly equal key.
 * @param object Receiver with 48-byte records, valid when its count is positive.
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A vector_curve_track_find_key_value(BootVectorCurveTrackState* object, float key);

/**
 * @brief Read the vector value associated with the first exactly equal key.
 * @param object Receiver with vector-key entries, valid when its count is positive.
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A vector_track_find_key_value(BootVectorTrackState* object, float key);

/**
 * @brief Read the vector value associated with the first exactly equal key.
 * @param object Receiver with 32-byte records, valid when its count is positive.
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A func_001F2A60(BootState1F1580* object, float key);

/**
 * @brief Read the vector value associated with the first exactly equal key.
 * @param object Receiver with 48-byte records, valid when its count is positive.
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A func_001F5CA0(BootState1F4730* object, float key);

/**
 * @brief Read the vector value associated with the first exactly equal key.
 * @param object Receiver with 32-byte records, valid when its count is positive.
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A func_001F5EB0(BootState1F47F0* object, float key);

/**
 * @brief Compute the difference between the last and first entry keys.
 * @param object Receiver with valid storage when it has at least two entries.
 * @return Key span, or zero when fewer than two entries exist.
 */
float float_track_get_key_span(BootFloatTrackState* object);

/**
 * @brief Store paired float values in the next slot of a two-entry history.
 * @param history History whose write index wraps and count saturates at two.
 * @param value First float value to copy.
 * @param associated Second float value to store.
 */
void float_history_push(BootFloatHistoryState* history, const float* value, float associated);

/**
 * @brief Insert a float entry before an existing index and shift following entries.
 * @param object Array receiver with spare capacity.
 * @param index Nonnegative index less than the current count.
 * @param value Entry value to copy.
 * @param key Key associated with the entry.
 * @return One if inserted, or zero if storage is absent, full, or the index is too large.
 */
s32 float_track_insert_entry(BootFloatTrackState* object, s32 index, const float* value, float key);

/**
 * @brief Replace an indexed float entry and update the span when it is the last entry.
 * @param object Array receiver.
 * @param index Nonnegative entry index, checked against capacity.
 * @param value Entry value to copy.
 * @param key Key associated with the entry.
 * @return One if stored, or zero if storage is absent or the index is outside capacity.
 */
s32 float_track_replace_entry(BootFloatTrackState* object, s32 index, const float* value, float key);

/**
 * @brief Append a float entry and update the cached key span.
 * @param object Array receiver.
 * @param value Entry value to copy.
 * @param key Key associated with the entry.
 * @return One if appended, or zero if storage is absent or full.
 */
s32 float_track_append_entry(BootFloatTrackState* object, const float* value, float key);

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void vector_curve_track_set_before_mode(BootVectorCurveTrackState* state, u32 value);

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void vector_curve_track_set_after_mode(BootVectorCurveTrackState* state, u32 value);

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void float_curve_track_set_before_mode(BootFloatCurveTrackState* state, u32 value);

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void float_curve_track_set_after_mode(BootFloatCurveTrackState* state, u32 value);

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void func_001F1580(BootState1F1580* state, u32 value);

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void func_001F15E0(BootState1F1580* state, u32 value);

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void vector_track_set_before_mode(BootVectorTrackState* state, u32 value);

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void vector_track_set_after_mode(BootVectorTrackState* state, u32 value);

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void float_track_set_before_mode(BootFloatTrackState* state, u32 value);

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void float_track_set_after_mode(BootFloatTrackState* state, u32 value);

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void func_001F4730(BootState1F4730* state, u32 value);

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void quaternion_track_set_before_mode(BootQuaternionTrackState* state, u32 value);

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void func_001F47F0(BootState1F47F0* state, u32 value);

/**
 * @brief Reset array storage, counts, packed controls, and cached indices.
 * @param object Receiver to reset without releasing its current storage.
 */
void func_001F4980(BootState1F47F0* object);

/**
 * @brief Bind external 32-byte records and cache their first-to-last key span.
 * @param object Array receiver.
 * @param count Positive entry count representable in the receiver count fields.
 * @param entries External storage containing the specified number of entries.
 */
void func_001F5FB0(BootState1F47F0* object, s32 count, BootKeyEntry32* entries);

/**
 * @brief Reset signed-key entry storage, counts, control fields, and cached indices.
 * @param object Array receiver to reset without releasing its current storage.
 */
void quaternion_track_reset_state(BootQuaternionTrackState* object);

/**
 * @brief Bind external entry storage and cache its first-to-last key span.
 * @param object Array receiver.
 * @param count Positive entry count representable in the receiver count fields.
 * @param entries External storage containing the specified number of entries.
 */
void quaternion_track_bind_keys(BootQuaternionTrackState* object, s32 count, BootQuaternionStateKey* entries);

/**
 * @brief Test whether the array contains a signed entry key equal to the given float.
 * @param object Receiver with valid storage when its count is positive.
 * @param key Key to find.
 * @return One if a matching key exists, or zero otherwise.
 */
s32 quaternion_track_has_key(BootQuaternionTrackState* object, float key);

/**
 * @brief Compute the difference between the last and first entry keys.
 * @param object Receiver with valid storage when it has at least two entries.
 * @return Key span, or zero when fewer than two entries exist.
 */
float quaternion_track_get_key_span(BootQuaternionTrackState* object);

/**
 * @brief Wrap a key by the span between the first and last entries.
 * @param object Receiver with valid nonempty storage and a nonzero key span.
 * @param key Key whose normalized span quotient must fit in a signed word.
 * @return Key with the computed whole spans subtracted.
 */
float quaternion_track_wrap_key(BootQuaternionTrackState* object, float key);

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void func_001F4AC0(BootState1F47F0* state, u32 value);

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void quaternion_track_set_after_mode(BootQuaternionTrackState* state, u32 value);

/**
 * @brief Reset 48-byte record storage, counts, packed controls, and cached indices.
 * @param object Receiver to reset without releasing its current storage.
 */
void func_001F58C0(BootState1F4730* object);

/**
 * @brief Adjust a scalar key by whole spans determined from the endpoint records.
 * @param object Receiver with positive count, valid storage, and distinct endpoint keys.
 * @param key Scalar key whose normalized span quotient must fit in a signed word.
 * @return Key minus the computed number of endpoint spans, or the key for zero spans.
 */
float func_001F5D60(BootState1F4730* object, float key);

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void func_001F5A50(BootState1F4730* state, u32 value);

/**
 * @brief Initialize the settings record to its default values.
 * @param settings Settings record to initialize.
 */
void init_draw_settings(BootDrawSettings* settings);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EECA0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EED30(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EED40(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EED50(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EED60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EED70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EED80(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 vector_curve_track_on_append_key(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 vector_curve_track_on_replace_key(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 vector_curve_track_on_insert_key(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void vector_curve_track_on_set_single_key(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 float_curve_track_on_append_key(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 float_curve_track_on_replace_key(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 float_curve_track_on_insert_key(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void float_curve_track_on_set_single_key(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void float_track_on_set_single_key(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 float_track_on_insert_key(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 float_track_on_replace_key(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 float_track_on_append_key(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void vector_track_on_set_single_key(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 vector_track_on_insert_key(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 vector_track_on_replace_key(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 vector_track_on_append_key(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001F2B90(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F2BD0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F2C10(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F2C50(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001F4950(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001F4960(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001F4970(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F4B50(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F4B90(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F4BD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001F4C10(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 quaternion_track_on_append_key(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 quaternion_track_on_replace_key(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 quaternion_track_on_insert_key(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void quaternion_track_on_set_single_key(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F5AE0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F5B20(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F5B60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001F5BA0(void* object);

/**
 * @brief Return the 32-bit word at offset 0x40.
 * @param object Object containing the value.
 * @return The stored value.
 */
s32 vector_curve_track_get_cycle_count(const BootVectorCurveTrackState* object);

/**
 * @brief Return the signed 16-bit value at offset 0x48.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 vector_curve_track_get_key_count(const BootVectorCurveTrackState* object);

/**
 * @brief Return the signed 16-bit value at offset 0x4A.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 vector_curve_track_get_key_capacity(const BootVectorCurveTrackState* object);

/**
 * @brief Return the 32-bit word at offset 0x4.
 * @param object Object containing the value.
 * @return The stored value.
 */
BootVectorCurveStateKey* vector_curve_track_get_keys(const BootVectorCurveTrackState* object);

/**
 * @brief Return the 32-bit word at offset 0x18.
 * @param object Object containing the value.
 * @return The stored value.
 */
s32 float_curve_track_get_cycle_count(const BootFloatCurveTrackState* object);

/**
 * @brief Return the signed 16-bit value at offset 0x20.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 float_curve_track_get_key_count(const BootFloatCurveTrackState* object);

/**
 * @brief Return the signed 16-bit value at offset 0x22.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 float_curve_track_get_key_capacity(const BootFloatCurveTrackState* object);

/**
 * @brief Return the 32-bit word at offset 0x4.
 * @param object Object containing the value.
 * @return The stored value.
 */
BootFloatCurveStateKey* float_curve_track_get_keys(const BootFloatCurveTrackState* object);

/**
 * @brief Return the 32-bit word at offset 0x30.
 * @param object Object containing the value.
 * @return The stored value.
 */
s32 func_001F1640(const BootState1F1580* object);

/**
 * @brief Return the signed 16-bit value at offset 0x38.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 func_001F1650(const BootState1F1580* object);

/**
 * @brief Return the signed 16-bit value at offset 0x3A.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 func_001F1660(const BootState1F1580* object);

/**
 * @brief Return the 32-bit word at offset 0x4.
 * @param object Object containing the value.
 * @return The stored value.
 */
BootKeyEntry32* func_001F16E0(const BootState1F1580* object);

/**
 * @brief Return the 32-bit word at offset 0x20.
 * @param object Object containing the value.
 * @return The stored value.
 */
s32 vector_track_get_cycle_count(const BootVectorTrackState* object);

/**
 * @brief Return the vector-key array count.
 * @param object Array receiver.
 * @return Stored entry count.
 */
s16 vector_track_get_key_count(BootVectorTrackState* object);

/**
 * @brief Return the vector-key array capacity.
 * @param object Array receiver.
 * @return Stored entry capacity.
 */
s16 vector_track_get_key_capacity(BootVectorTrackState* object);

/**
 * @brief Return the 32-bit word at offset 0x4.
 * @param object Object containing the value.
 * @return The stored value.
 */
BootVectorStateKey* vector_track_get_keys(const BootVectorTrackState* object);

/**
 * @brief Return the 32-bit word at offset 0x10.
 * @param object Object containing the value.
 * @return The stored value.
 */
s32 float_track_get_cycle_count(const BootFloatTrackState* object);

/**
 * @brief Return the signed 16-bit value at offset 0x18.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 float_track_get_key_count(const BootFloatTrackState* object);

/**
 * @brief Return the signed 16-bit value at offset 0x1A.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 float_track_get_key_capacity(const BootFloatTrackState* object);

/**
 * @brief Return the 32-bit word at offset 0x4.
 * @param object Object containing the value.
 * @return The stored value.
 */
BootFloatStateKey* float_track_get_keys(const BootFloatTrackState* object);

/**
 * @brief Return the 32-bit word at offset 0x30.
 * @param object Object containing the value.
 * @return The stored value.
 */
s32 func_001F4B20(const BootState1F47F0* object);

/**
 * @brief Return the signed 16-bit value at offset 0x38.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 func_001F4B30(const BootState1F47F0* object);

/**
 * @brief Return the signed 16-bit value at offset 0x3A.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 func_001F4B40(const BootState1F47F0* object);

/**
 * @brief Return the 32-bit word at offset 0x4.
 * @param object Object containing the value.
 * @return The stored value.
 */
BootKeyEntry32* func_001F4CC0(const BootState1F47F0* object);

/**
 * @brief Return the 32-bit word at offset 0x10.
 * @param object Object containing the value.
 * @return The stored value.
 */
s32 quaternion_track_get_cycle_count(const BootQuaternionTrackState* object);

/**
 * @brief Return the signed 16-bit value at offset 0x18.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 quaternion_track_get_key_count(const BootQuaternionTrackState* object);

/**
 * @brief Return the signed 16-bit value at offset 0x1A.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 quaternion_track_get_key_capacity(const BootQuaternionTrackState* object);

/**
 * @brief Return the 32-bit word at offset 0x4.
 * @param object Object containing the value.
 * @return The stored value.
 */
BootQuaternionStateKey* quaternion_track_get_keys(const BootQuaternionTrackState* object);

/**
 * @brief Return the 32-bit word at offset 0x40.
 * @param object Object containing the value.
 * @return The stored value.
 */
s32 func_001F5AB0(const BootState1F4730* object);

/**
 * @brief Return the signed 16-bit value at offset 0x48.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 func_001F5AC0(const BootState1F4730* object);

/**
 * @brief Return the signed 16-bit value at offset 0x4A.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 func_001F5AD0(const BootState1F4730* object);

/**
 * @brief Return the 32-bit word at offset 0x4.
 * @param object Object containing the value.
 * @return The stored value.
 */
BootKeyEntry48* func_001F5E00(const BootState1F4730* object);

/**
 * @brief Return zero as a float.
 * @param object Receiver or first argument; unused.
 * @return Always 0.0f.
 */
float float_curve_track_get_zero_value(void* object);

/**
 * @brief Return zero as a float.
 * @param object Receiver or first argument; unused.
 * @return Always 0.0f.
 */
float float_track_get_zero_value(void* object);

/**
 * @brief Copy the float at offset 0x50.
 * @param object Object containing the value.
 * @param value Destination for the value.
 */
void func_001EFD70(void* object, float* value);

/**
 * @brief Copy the float at offset 0x4C.
 * @param object Object containing the value.
 * @param value Destination for the value.
 */
void func_001F04B0(void* object, float* value);

/**
 * @brief Clear the fields at offsets 0x10 through 0x18.
 * @param object Object to clear.
 */
void func_001F0660(void* object);

/**
 * @brief Clear the fields at offsets 0x10 through 0x18.
 * @param object Object to clear.
 */
void func_001F06C0(void* object);

/**
 * @brief Clear the fields at offsets 0x4 through 0xC.
 * @param object Object to clear.
 */
void func_001F0720(void* object);

/**
 * @brief Clear four words starting at offset 0.
 * @param object Object to clear.
 */
void func_001F1670(void* object);

/**
 * @brief Clear four words starting at offset 0.
 * @param object Object to clear.
 */
void vector_track_get_zero_value(void* object);

/**
 * @brief Clear four words starting at offset 0.
 * @param object Object to clear.
 */
void func_001F4C50(void* object);

/**
 * @brief Clear four words starting at offset 0.
 * @param object Object to clear.
 */
void quaternion_track_get_zero_value(void* object);

/**
 * @brief Clear four words starting at offset 0.
 * @param object Object to clear.
 */
void func_001F5C30(void* object);

/**
 * @brief Forward to the cleanup routine for the containing object.
 * @param object Embedded object at offset 0x90.
 */
void func_001FA890(void* object);

/**
 * @brief Clear four words starting at offset 0.
 * @param object Object to clear.
 */
void vector_curve_track_get_zero_value(void* object);

/**
 * @brief Write the difference between the last and first float values in an eight-byte record array.
 * @param object Object containing the array pointer and count.
 * @param result Destination for the difference; unchanged if the array is absent.
 */
void func_001F0480(void* object, float* result);

/**
 * @brief Write the difference between the last and first float values in a sixteen-byte record array.
 * @param object Object containing the array pointer and count.
 * @param result Destination for the difference; unchanged if the array is absent.
 */
void func_001EFD80(void* object, float* result);

/** Clear the vector at offset 0xB0 and update the associated state. */
void func_001EEED0(void* object);
/** Clear the vector at offset 0x90 and update the associated state. */
void func_001EFEA0(void* object);

/**
 * @brief Build an image's quad from a rectangle of its texture and a rectangle of its palette, and queue the
 * model for drawing.
 * @param image Image to build.
 * @param x Left edge of the texture rectangle, in texels.
 * @param y Top edge of the texture rectangle.
 * @param width Rectangle width, which is also the quad's width.
 * @param height Rectangle height, which is also the quad's height.
 * @param palette_x Left edge of the palette rectangle.
 * @param palette_y Top edge of the palette rectangle.
 * @param palette_width Palette rectangle width.
 * @param palette_height Palette rectangle height.
 * @param color Vertex color.
 * @param depth Z position of the quad.
 */
void image_set_rectangle_with_palette(BootImage* image, s32 x, s32 y, s32 width, s32 height, s32 palette_x, s32 palette_y, s32 palette_width,
                                      s32 palette_height, u32 color, s32 depth);

/**
 * @brief Encode a saved record and seal it with a fresh checksum; a damaged record is wiped instead.
 * @param record Record to seal; an already sealed record is left alone.
 */
void seal_record(BootSealedRecord* record);

#ifdef __cplusplus
}
#endif

#endif
