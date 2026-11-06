#ifndef SO3_OVERLAYS_LIB_TRACKS_H
#define SO3_OVERLAYS_LIB_TRACKS_H

#include "types.h"
#include "main/resident_001001E0.h"
#include "overlays/lib/vector.h"
#include "clamp.h"
#include "overlays/lib/text_004BD360.h"

/** Fixed pool of tracks with a bitmap of used slots. */
template <class T> struct LibTrackPool
{
    /**
     * @brief Mark a track's pool slot as free.
     * @param track Track to release.
     */
    void free(T* track)
    {
        u32 index = ((u32)track - (u32)items) / ((u32)&items[1] - (u32)items);
        used[index >> 6] &= ~((u64)1 << (index & 0x3F));
    }

    s32 count;
    s32 unk04;
    T* items;
    s32 capacity;
    s32 words;
    u64* used;
    bool external;
};

class LibClass177EE0;
class LibPooledFloatTrack;
class LibPooledFloatCurveTrack;
class LibPooledFloatQuaternionTrack;

/** 32-byte keyframe of LibClass177B50: a key and a value at offset 0x10. */
struct LibTrackKey177B50
{
    /** @brief Leave the keyframe uninitialized. */
    LibTrackKey177B50();

    float key;
    FieldVec4B value;
};

/**
 * Vector keyframe track with vtable D_177B50 in main data; Lib's copy of Boot's BootClass1718C0. Its keys aren't
 * stored at this level.
 */
class LibClass177B50 : public LibClass173180
{
public:
    /** @brief Release the keyframe storage. */
    virtual ~LibClass177B50();

    virtual void allocate_keys(s32 count);
    virtual void bind_keys(s32 count, void* keys);
    virtual void set_before_mode(u32 mode);
    virtual void set_after_mode(u32 mode);
    virtual s32 get_cycle_count() const;
    virtual s32 append_key(const void* value, const void* in_tangent, const void* out_tangent, float key);
    virtual s32 replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent);
    virtual s32 insert_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent);
    virtual void set_single_key(const void* value, const void* in_tangent, const void* out_tangent, float key);
    virtual s32 has_key(float key) const;
    virtual float wrap_key(float key) const;
    virtual float get_key_span() const;
    virtual void evaluate(float key, void* output);
    virtual s16 get_key_count() const;
    virtual void* get_keys();
    virtual void reset_state();
    virtual s16 get_key_capacity();

    /**
     * @brief Append a keyframe; the base ignores it.
     * @param value Keyframe value.
     * @param key Sort key.
     * @return Nonzero when the keyframe was stored.
     */
    virtual s32 on_append_key(const FieldVec4A* value, float key);

    /**
     * @brief Replace an indexed keyframe; the base ignores it.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @return Nonzero when the keyframe was stored.
     */
    virtual s32 on_replace_key(s32 index, float key, const FieldVec4A* value);

    /**
     * @brief Insert a keyframe at an index; the base ignores it.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @return Nonzero when the keyframe was stored.
     */
    virtual s32 on_insert_key(s32 index, float key, const FieldVec4A* value);

    /**
     * @brief Store a single keyframe; the base ignores it.
     * @param value Keyframe value.
     * @param key Sort key.
     */
    virtual void on_set_single_key(const FieldVec4A* value, float key);

    /**
     * @brief Return a zero vector, the track's value when it has no keys.
     * @return Zero vector.
     */
    virtual FieldVec4A get_zero_value() const;

    /**
     * @brief Return the value of the keyframe at a key.
     * @param key Key to find.
     * @return Keyframe value, or zero when the key is absent.
     */
    virtual FieldVec4A find_key_value(float key);

    /**
     * @brief Sample the track at a key.
     * @param key Key to sample at.
     * @return Value at the key.
     */
    virtual FieldVec4A sample(float key) const = 0;

    /** @brief Free the keys and give the track back to its pool; pooled tracks implement it. */
    virtual void return_to_pool() = 0;

    /** @brief Delete the key storage unless it is external, and clear the key pointer. */
    void free_keys();

    LibTrackKey177B50* key_array;
    u8 unk08[8];

    /** Key of the single cached keyframe, used before an array is allocated. */
    float single_key;

    u8 unk14[0xC];

    /** Value of the single cached keyframe. */
    FieldVec4B single_value;

    LibTrackState state;

    /** @brief Clear the pooled flag and reset the sequence. */
    LibClass177B50();

    /**
     * @brief Wrap a key into the key span and record how many spans it was past the first key.
     * @param key Key to wrap.
     * @return Wrapped key, reflected on odd cycles in ping-pong mode.
     */
    float update_cycle_count(float key);

    /**
     * @brief Find the keys around a key, starting from the cached search index.
     * @param key Key to place.
     * @param lower Receives the lower key index.
     * @param upper Receives the upper key index.
     * @return One when an end mode extends the first or last segment, otherwise zero.
     */
    u8 find_surrounding_keys(float key, s32* lower, s32* upper);
};

/** LibClass177B50 that stores its keys, with vtable D_177AC0 in main data; Lib's copy of Boot's BootClass171320. */
class LibClass177AC0 : public LibClass177B50
{
public:
    /** @brief Destroy the track. */
    virtual ~LibClass177AC0()
    {
    }

    virtual s32 read_key(s32 index, float* key, void* value, void* first, void* second) const;
    virtual s32 on_append_key(const FieldVec4A* value, float key);
    virtual s32 on_replace_key(s32 index, float key, const FieldVec4A* value);
    virtual s32 on_insert_key(s32 index, float key, const FieldVec4A* value);
    virtual void on_set_single_key(const FieldVec4A* value, float key);
};

/** 0xC0-byte pooled LibClass177AC0 with vtable D_177EE0 in main data, allocated from g_track_1718C0_pool. */
class LibClass177EE0 : public LibClass177AC0
{
public:
    /** @brief Destroy the track. */
    virtual ~LibClass177EE0();

    virtual void get_end_delta(void* output) const;
    virtual void get_value_rate(void* output) const;
    virtual void release();
    virtual void reset_state();
    virtual FieldVec4A sample(float key) const;
    virtual void return_to_pool();

    u8 unk50[0x70];
};

/** 8-byte keyframe of LibFloatTrackBase: a key followed by its value. */
struct LibFloatTrackKey
{
    /**
     * @brief Copy the key and value.
     * @param entry Entry to copy.
     * @return This entry.
     */
    LibFloatTrackKey& operator=(const LibFloatTrackKey& entry)
    {
        key = entry.key;
        value = entry.value;
        return *this;
    }

    float key;
    float value;
};

/** Key storage for tracks of single float values, with vtable D_178130 in main data; keys aren't stored at this level. */
class LibFloatTrackBase : public LibClass173180
{
public:
    /** @brief Clear the pooled flag and reset the sequence. */
    LibFloatTrackBase();

    /** @brief Release the keyframe storage. */
    virtual ~LibFloatTrackBase();

    virtual void allocate_keys(s32 count);
    virtual void bind_keys(s32 count, void* keys);
    virtual void set_before_mode(u32 mode);
    virtual void set_after_mode(u32 mode);
    virtual s32 get_cycle_count() const;
    virtual s32 append_key(const void* value, const void* in_tangent, const void* out_tangent, float key);
    virtual s32 replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent);
    virtual s32 insert_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent);
    virtual void set_single_key(const void* value, const void* in_tangent, const void* out_tangent, float key);
    virtual s32 has_key(float key) const;
    virtual float wrap_key(float key) const;
    virtual float get_key_span() const;
    virtual void evaluate(float key, void* output);
    virtual s16 get_key_count() const;
    virtual void* get_keys();
    virtual void reset_state();
    virtual s16 get_key_capacity();

    /**
     * @brief Append a keyframe; the base ignores it.
     * @param value Keyframe value.
     * @param key Sort key.
     * @return Nonzero when the keyframe was stored.
     */
    virtual s32 on_append_key(const float* value, float key);

    /**
     * @brief Replace an indexed keyframe; the base ignores it.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @return Nonzero when the keyframe was stored.
     */
    virtual s32 on_replace_key(s32 index, float key, const float* value);

    /**
     * @brief Insert a keyframe at an index; the base ignores it.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @return Nonzero when the keyframe was stored.
     */
    virtual s32 on_insert_key(s32 index, float key, const float* value);

    /**
     * @brief Store a single keyframe; the base ignores it.
     * @param value Keyframe value.
     * @param key Sort key.
     */
    virtual void on_set_single_key(const float* value, float key);

    /**
     * @brief Return zero, the track's value when it has no keys.
     * @return Zero.
     */
    virtual float get_zero_value() const;

    /**
     * @brief Return the value of the keyframe at a key.
     * @param key Key to find.
     * @return Keyframe value, or zero when the key is absent.
     */
    virtual float find_key_value(float key);

    /**
     * @brief Sample the track at a key.
     * @param key Key to sample at.
     * @return Value at the key.
     */
    virtual float sample(float key) = 0;

    /** @brief Delete the key storage unless it is external, and clear the key pointer. */
    void free_keys();

    /**
     * @brief Wrap a key into the key span and record how many spans it was past the first key.
     * @param key Key to wrap.
     * @return Wrapped key, reflected on odd cycles in ping-pong mode.
     */
    float update_cycle_count(float key);

    /**
     * @brief Find the keys around a key, starting from the cached search index.
     * @param key Key to place.
     * @param lower Receives the lower key index.
     * @param upper Receives the upper key index.
     * @return One when an end mode extends the first or last segment, otherwise zero.
     */
    u8 find_surrounding_keys(float key, s32* lower, s32* upper);

    LibFloatTrackKey* key_array;

    /** Single cached keyframe, used before the first array key. */
    LibFloatTrackKey single_key;

    LibTrackState state;
};

/** Float track that stores its keys in the array, with vtable D_178010 in main data. */
class LibFloatKeyTrack : public LibFloatTrackBase
{
public:
    /** @brief Destroy the track. */
    virtual ~LibFloatKeyTrack()
    {
    }

    virtual s32 read_key(s32 index, float* key, void* value, void* first, void* second) const;
    virtual s32 on_append_key(const float* value, float key);
    virtual s32 on_replace_key(s32 index, float key, const float* value);
    virtual s32 on_insert_key(s32 index, float key, const float* value);
    virtual void on_set_single_key(const float* value, float key);
};

/**
 * Two-sample float history a float track samples through, with vtable D_178200 in main data; its data comes before
 * the vptr. Boot splits the same layout into a base, a history and BootClass178200, but Lib has no vtables for
 * the first two, so here it is one class.
 */
class LibClass178200
{
public:
    u32 unk00;
    s16 sample_count;
    s16 next_index;
    u32 unk08;
    u32 unk0C;

    /** @brief Forget the stored samples. */
    void reset();

    /**
     * @brief Find the two stored samples and how far a key lies between them.
     * @param key Key to place.
     * @param lower Receives the index of the older sample.
     * @param upper Receives the index of the newer sample.
     * @return Blend factor from the older sample to the newer one; zero until both samples are stored.
     */
    float find_blend(float key, s32* lower, s32* upper) const;

    /** @brief Slot 8; empty in every copy, so its purpose is unknown. */
    virtual void func_slot08();

    /**
     * @brief Blend the two stored values linearly at a key.
     * @param key Evaluation key.
     * @return Blended value, or zero when the history is empty.
     */
    virtual float sample(float key) const;

    /**
     * @brief Store a value and key in the two-entry history and count it, up to two.
     * @param value Value to store.
     * @param key Key to store.
     */
    virtual void push_sample(const float* value, float key);

    /**
     * @brief Add a key and its value to the record.
     * @param key Key.
     * @param value Value at the key.
     */
    virtual void add_sample(float key, float value);

    float values[2];
    float keys[2];
};

/** Two-sample vector history that blends xyz linearly, with vtable D_1781E0 in main data; its data comes before the vptr. */
class LibLinearVectorHistory
{
public:
    FieldVec4B unk00;
    s16 sample_count;
    s16 next_index;
    u32 unk14;
    u32 unk18;

    /**
     * @brief Find the two stored samples and how far a key lies between them.
     * @param key Key to place.
     * @param lower Receives the index of the older sample.
     * @param upper Receives the index of the newer sample.
     * @return Blend factor from the older sample to the newer one; zero until both samples are stored.
     */
    float find_blend(float key, s32* lower, s32* upper) const;

    /** @brief Slot 8; empty in every copy, so its purpose is unknown. */
    virtual void func_slot08();

    /**
     * @brief Blend the two stored vectors' xyz linearly at a key.
     * @param key Evaluation key.
     * @return Blended vector; w is the newer sample's w minus the older one's, scaled by the blend.
     */
    virtual FieldVec4B sample(float key);

    /**
     * @brief Store a value and key in the two-entry history and count it, up to two.
     * @param key Key to store.
     * @param value Value to store.
     */
    virtual void push_sample(float key, const FieldVec4A* value);

    FieldVec4B values[2];
    float keys[2];
};

/** Two-sample quaternion history that slerps, with vtable D_1781C0 in main data; its data comes before the vptr. */
class LibSlerpQuaternionHistory
{
public:
    FieldVec4B unk00;
    s16 sample_count;
    s16 next_index;
    u32 unk14;
    u32 unk18;

    /** @brief Forget the stored samples. */
    void reset();

    /**
     * @brief Find the two stored samples and how far a key lies between them.
     * @param key Key to place.
     * @param lower Receives the index of the older sample.
     * @param upper Receives the index of the newer sample.
     * @return Blend factor from the older sample to the newer one; zero until both samples are stored.
     */
    float find_blend(float key, s32* lower, s32* upper) const;

    /** @brief Slot 8; empty in every copy, so its purpose is unknown. */
    virtual void func_slot08();

    /**
     * @brief Slerp the two stored quaternions at a key.
     * @param key Evaluation key.
     * @return Interpolated quaternion.
     */
    virtual FieldVec4B sample(float key);

    /**
     * @brief Store a value and key in the two-entry history and count it, up to two.
     * @param value Value to store.
     * @param key Key to store.
     */
    virtual void push_sample(const FieldVec4A* value, float key);

    /**
     * @brief Slerp the two stored quaternions at a key and report the blend.
     * @param key Evaluation key.
     * @param blend Receives the blend factor when not null.
     * @return Interpolated quaternion.
     */
    virtual FieldVec4B sample_with_blend(float key, float* blend);

    FieldVec4B values[2];
    float keys[2];
};

/** Float track that samples its keys and caches the value and its rate, with vtable D_1780A0 in main data. */
class LibFloatTrack : public LibFloatKeyTrack
{
public:
    /** @brief Destroy the track. */
    virtual ~LibFloatTrack()
    {
    }

    virtual void reset_keys();
    virtual void get_end_delta(void* output) const;
    virtual void get_value_rate(void* output) const;
    virtual void reset_state();
    virtual float sample(float key);

    /** Two-sample history the sampler fills; a Lib history object with vtable D_178200. */
    LibClass178200 sample_history;

    float last_value;
    float value_rate;
};

/** 0x50-byte float track allocated from g_float_track_pool, with vtable D_177F70 in main data. */
class LibPooledFloatTrack : public LibFloatTrack
{
public:
    /** @brief Destroy the track. */
    virtual ~LibPooledFloatTrack();

    virtual void release();

    /**
     * @brief Append a keyframe from plain floats.
     * @param key Sort key.
     * @param value Keyframe value.
     */
    virtual void append_float_key(float key, float value);

    /**
     * @brief Replace an indexed keyframe from plain floats.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     */
    virtual void replace_float_key(s32 index, float key, float value);

    /**
     * @brief Insert a keyframe from plain floats.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     */
    virtual void insert_float_key(s32 index, float key, float value);

    /**
     * @brief Store the single keyframe from plain floats.
     * @param key Sort key.
     * @param value Keyframe value.
     */
    virtual void set_single_float_key(float key, float value);

    /** @brief Free the keys and give the track back to g_float_track_pool. */
    virtual void return_to_pool();
};

/** Cubic Hermite segment between two float keys. */
class LibFloatSegment
{
public:
    /**
     * @brief Compute the Hermite basis weights at a key.
     * @param key Evaluation key.
     * @param weights Receives the start value, end value, start tangent and end tangent weights.
     */
    void get_weights(float key, float* weights) const;

    /**
     * @brief Evaluate the segment at a key.
     * @param key Evaluation key.
     * @return Value at the key.
     */
    float interpolate(float key) const;

    float start_value;
    float end_value;
    float start_tangent;
    float end_tangent;
    float start_key;
    float end_key;
    float key_span;

    /**
     * @brief Set the segment from the values, tangents and keys at its two ends.
     * @param from_value Value at the start key.
     * @param from_tangent Tangent at the start key.
     * @param to_value Value at the end key.
     * @param to_tangent Tangent at the end key.
     * @param from_key Key the segment starts at.
     * @param to_key Key the segment ends at.
     */
    virtual void set_endpoints(const float* from_value, const float* from_tangent, const float* to_value, const float* to_tangent, float from_key,
                               float to_key);
};

/** Cubic Hermite segment between two vector keys. */
class LibVectorSegment
{
public:
    /**
     * @brief Compute the Hermite basis weights at a key.
     * @param key Evaluation key.
     * @param weights Receives the start value, end value, start tangent and end tangent weights.
     */
    void get_weights(float key, float* weights) const;

    /**
     * @brief Evaluate the segment at a key.
     * @param key Evaluation key.
     * @return Value at the key.
     */
    FieldVec4B interpolate(float key) const;

    FieldVec4B start_value;
    FieldVec4B end_value;
    FieldVec4B start_tangent;
    FieldVec4B end_tangent;
    float start_key;
    float end_key;
    float key_span;

    /**
     * @brief Set the segment from the keys, values and tangents at its two ends.
     * @param from_key Key the segment starts at.
     * @param to_key Key the segment ends at.
     * @param from_value Value at the start key.
     * @param from_tangent Tangent at the start key.
     * @param to_value Value at the end key.
     * @param to_tangent Tangent at the end key.
     */
    virtual void set_endpoints(float from_key, float to_key, const FieldVec4A* from_value, const FieldVec4A* from_tangent, const FieldVec4A* to_value,
                               const FieldVec4A* to_tangent);
};

/** Basis weights of the last vector segment evaluated, kept where VU0 can load them. */
extern float g_vector_segment_weights[4];

/** 16-byte vector keyframe: a value whose w is the key. */
struct LibVectorTrackKey
{
    /** @brief Leave the key unset. */
    LibVectorTrackKey()
    {
    }

    FieldVec4B value;
};

/** 48-byte keyframe of LibVectorCurveTrackBase: a LibVectorTrackKey and two tangents. */
struct LibVectorCurveTrackKey : public LibVectorTrackKey
{
    /** @brief Leave the key unset. */
    LibVectorCurveTrackKey()
    {
    }

    FieldVec4B in_tangent;
    FieldVec4B out_tangent;
};

/** Key storage for vector tracks whose keys carry two tangents. */
class LibVectorCurveTrackBase : public LibClass173180
{
public:
    /** @brief Release the keyframe storage. */
    virtual ~LibVectorCurveTrackBase();

    virtual void allocate_keys(s32 count);
    virtual void bind_keys(s32 count, void* keys);
    virtual void set_before_mode(u32 mode);
    virtual void set_after_mode(u32 mode);
    virtual s32 get_cycle_count() const;
    virtual s32 append_key(const void* value, const void* in_tangent, const void* out_tangent, float key);
    virtual s32 replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent);
    virtual s32 insert_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent);
    virtual void set_single_key(const void* value, const void* in_tangent, const void* out_tangent, float key);
    virtual s32 has_key(float key) const;
    virtual float wrap_key(float key) const;
    virtual float get_key_span() const;
    virtual void evaluate(float key, void* output);
    virtual s16 get_key_count() const;
    virtual void* get_keys();
    virtual void reset_state();
    virtual s16 get_key_capacity();

    /**
     * @brief Append a keyframe; the base ignores it.
     * @param value Keyframe value.
     * @param in_tangent Incoming tangent.
     * @param out_tangent Outgoing tangent.
     * @param key Sort key.
     * @return Nonzero when the keyframe was stored.
     */
    virtual s32 on_append_key(const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent, float key);

    /**
     * @brief Replace an indexed keyframe; the base ignores it.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @param in_tangent Incoming tangent.
     * @param out_tangent Outgoing tangent.
     * @return Nonzero when the keyframe was stored.
     */
    virtual s32 on_replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent);

    /**
     * @brief Insert a keyframe at an index; the base ignores it.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @param in_tangent Incoming tangent.
     * @param out_tangent Outgoing tangent.
     * @return Nonzero when the keyframe was stored.
     */
    virtual s32 on_insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent);

    /**
     * @brief Store a single keyframe; the base ignores it.
     * @param value Keyframe value.
     * @param in_tangent Incoming tangent.
     * @param out_tangent Outgoing tangent.
     * @param key Sort key.
     */
    virtual void on_set_single_key(const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent, float key);

    /**
     * @brief Return the zero vector, the track's value when it has no keys.
     * @return Zero vector.
     */
    virtual FieldVec4A get_zero_value() const;

    /**
     * @brief Return the value of the keyframe at a key.
     * @param key Key to find.
     * @return Keyframe value, or zero when the key is absent.
     */
    virtual FieldVec4A find_key_value(float key);

    /**
     * @brief Sample the track at a key.
     * @param key Key to sample at.
     * @return Value at the key.
     */
    virtual FieldVec4A sample(float key) = 0;

    /**
     * @brief Append a keyframe with both tangents.
     * @param value Keyframe value.
     * @param in_tangent Incoming tangent.
     * @param out_tangent Outgoing tangent.
     * @param key Sort key.
     * @return Nonzero when the keyframe was stored.
     */
    virtual s32 append_curve_key(const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent, float key) = 0;

    /** @brief Delete the key storage unless it is external, and clear the key pointer. */
    void free_keys();

    /**
     * @brief Wrap a key into the key span and record how many spans it was past the first key.
     * @param key Key to wrap.
     * @return Wrapped key, reflected on odd cycles in ping-pong mode.
     */
    float update_cycle_count(float key);

    /**
     * @brief Find the keys around a key, starting from the cached search index.
     * @param key Key to place.
     * @param lower Receives the lower key index.
     * @param upper Receives the upper key index.
     * @return One when an end mode extends the first or last segment, otherwise zero.
     */
    u8 find_surrounding_keys(float key, s32* lower, s32* upper);

    LibVectorCurveTrackKey* key_array;
    u8 unk08[8];

    /** Single cached keyframe, used before the first array key. */
    LibVectorCurveTrackKey single_key;

    LibTrackState state;
    u8 unk54[0xC];
};

/** Vector curve track that stores and samples its keys, with vtable D_179280 in main data. */
class LibVectorCurveTrack : public LibVectorCurveTrackBase
{
public:
    /** @brief Destroy the track. */
    virtual ~LibVectorCurveTrack()
    {
    }

    virtual s32 append_key(const void* value, const void* in_tangent, const void* out_tangent, float key);
    virtual s32 replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent);
    virtual s32 insert_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent);
    virtual s32 read_key(s32 index, float* key, void* value, void* first, void* second) const;
    virtual void set_single_key(const void* value, const void* in_tangent, const void* out_tangent, float key);
    virtual void reset_keys();
    virtual void get_end_delta(void* output) const;
    virtual void get_value_rate(void* output) const;
    virtual void reset_state();
    virtual FieldVec4A sample(float key);
    virtual s32 append_curve_key(const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent, float key);

    /**
     * @brief Replace an indexed keyframe with both tangents.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @param in_tangent Incoming tangent.
     * @param out_tangent Outgoing tangent.
     * @return Nonzero when the keyframe was stored.
     */
    virtual s32 replace_curve_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent);

    /**
     * @brief Insert a keyframe with both tangents.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @param in_tangent Incoming tangent.
     * @param out_tangent Outgoing tangent.
     * @return Nonzero when the keyframe was stored.
     */
    virtual s32 insert_curve_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent);

    /**
     * @brief Store the single keyframe with both tangents, and use it before the first key.
     * @param value Keyframe value.
     * @param in_tangent Incoming tangent.
     * @param out_tangent Outgoing tangent.
     * @param key Sort key.
     */
    virtual void set_single_curve_key(const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent, float key);

    /** Hermite segment between the keys around the last sample. */
    LibVectorSegment curve_segment;

    FieldVec4B last_value;
    FieldVec4B value_rate;
};

/** 0xD0-byte vector curve track allocated from g_vector_curve_track_pool, with vtable D_179320 in main data. */
class LibPooledVectorCurveTrack : public LibVectorCurveTrack
{
public:
    /** @brief Destroy the track. */
    virtual ~LibPooledVectorCurveTrack();

    virtual void release();

    /** @brief Free the keys and give the track back to g_vector_curve_track_pool. */
    virtual void return_to_pool();
};

/** 16-byte keyframe of LibFloatCurveTrackBase: a key, a value and two tangents. */
struct LibFloatCurveTrackKey
{
    /**
     * @brief Copy the key, value and tangents.
     * @param entry Entry to copy.
     * @return This entry.
     */
    LibFloatCurveTrackKey& operator=(const LibFloatCurveTrackKey& entry)
    {
        key = entry.key;
        value = entry.value;
        in_tangent = entry.in_tangent;
        out_tangent = entry.out_tangent;
        return *this;
    }

    float key;
    float value;
    float in_tangent;
    float out_tangent;
};

/** Key storage for float tracks whose keys carry a value and two tangents, with vtable D_177DC0 in main data. */
class LibFloatCurveTrackBase : public LibClass173180
{
public:
    /** @brief Clear the pooled flag and reset the sequence. */
    LibFloatCurveTrackBase();

    /** @brief Release the keyframe storage. */
    virtual ~LibFloatCurveTrackBase();

    virtual void allocate_keys(s32 count);
    virtual void bind_keys(s32 count, void* keys);
    virtual void set_before_mode(u32 mode);
    virtual void set_after_mode(u32 mode);
    virtual s32 get_cycle_count() const;
    virtual s32 append_key(const void* value, const void* in_tangent, const void* out_tangent, float key);
    virtual s32 replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent);
    virtual s32 insert_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent);
    virtual void set_single_key(const void* value, const void* in_tangent, const void* out_tangent, float key);
    virtual s32 has_key(float key) const;
    virtual float wrap_key(float key) const;
    virtual float get_key_span() const;
    virtual void evaluate(float key, void* output);
    virtual s16 get_key_count() const;
    virtual void* get_keys();
    virtual void reset_state();
    virtual s16 get_key_capacity();

    /**
     * @brief Append a keyframe; the base ignores it.
     * @param value Keyframe value.
     * @param in_tangent Incoming tangent.
     * @param out_tangent Outgoing tangent.
     * @param key Sort key.
     * @return Nonzero when the keyframe was stored.
     */
    virtual s32 on_append_key(const float* value, const float* in_tangent, const float* out_tangent, float key);

    /**
     * @brief Replace an indexed keyframe; the base ignores it.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @param in_tangent Incoming tangent.
     * @param out_tangent Outgoing tangent.
     * @return Nonzero when the keyframe was stored.
     */
    virtual s32 on_replace_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent);

    /**
     * @brief Insert a keyframe at an index; the base ignores it.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @param in_tangent Incoming tangent.
     * @param out_tangent Outgoing tangent.
     * @return Nonzero when the keyframe was stored.
     */
    virtual s32 on_insert_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent);

    /**
     * @brief Store a single keyframe; the base ignores it.
     * @param value Keyframe value.
     * @param in_tangent Incoming tangent.
     * @param out_tangent Outgoing tangent.
     * @param key Sort key.
     */
    virtual void on_set_single_key(const float* value, const float* in_tangent, const float* out_tangent, float key);

    /**
     * @brief Return zero, the track's value when it has no keys.
     * @return Zero.
     */
    virtual float get_zero_value() const;

    /**
     * @brief Return the value of the keyframe at a key.
     * @param key Key to find.
     * @return Keyframe value, or zero when the key is absent.
     */
    virtual float find_key_value(float key);

    /**
     * @brief Sample the track at a key.
     * @param key Key to sample at.
     * @return Value at the key.
     */
    virtual float sample(float key) = 0;

    /**
     * @brief Append a keyframe with both tangents.
     * @param value Keyframe value.
     * @param in_tangent Incoming tangent.
     * @param out_tangent Outgoing tangent.
     * @param key Sort key.
     * @return Nonzero when the keyframe was stored.
     */
    virtual s32 append_curve_key(const float* value, const float* in_tangent, const float* out_tangent, float key) = 0;

    /** @brief Delete the key storage unless it is external, and clear the key pointer. */
    void free_keys();

    /**
     * @brief Wrap a key into the key span and record how many spans it was past the first key.
     * @param key Key to wrap.
     * @return Wrapped key, reflected on odd cycles in ping-pong mode.
     */
    float update_cycle_count(float key);

    /**
     * @brief Find the keys around a key, starting from the cached search index.
     * @param key Key to place.
     * @param lower Receives the lower key index.
     * @param upper Receives the upper key index.
     * @return One when an end mode extends the first or last segment, otherwise zero.
     */
    u8 find_surrounding_keys(float key, s32* lower, s32* upper);

    LibFloatCurveTrackKey* key_array;

    /** Single cached keyframe, used before the first array key. */
    LibFloatCurveTrackKey single_key;

    LibTrackState state;
};

/** Float curve track that stores and samples its keys, with vtable D_177D20 in main data. */
class LibFloatCurveTrack : public LibFloatCurveTrackBase
{
public:
    /** @brief Destroy the track. */
    virtual ~LibFloatCurveTrack()
    {
    }

    virtual s32 append_key(const void* value, const void* in_tangent, const void* out_tangent, float key);
    virtual s32 replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent);
    virtual s32 insert_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent);
    virtual s32 read_key(s32 index, float* key, void* value, void* first, void* second) const;
    virtual void set_single_key(const void* value, const void* in_tangent, const void* out_tangent, float key);
    virtual void reset_keys();
    virtual void get_end_delta(void* output) const;
    virtual void get_value_rate(void* output) const;
    virtual void reset_state();
    virtual float sample(float key);
    virtual s32 append_curve_key(const float* value, const float* in_tangent, const float* out_tangent, float key);

    /**
     * @brief Replace an indexed keyframe with both tangents.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @param in_tangent Incoming tangent.
     * @param out_tangent Outgoing tangent.
     * @return Nonzero when the keyframe was stored.
     */
    virtual s32 replace_curve_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent);

    /**
     * @brief Insert a keyframe with both tangents.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @param in_tangent Incoming tangent.
     * @param out_tangent Outgoing tangent.
     * @return Nonzero when the keyframe was stored.
     */
    virtual s32 insert_curve_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent);

    /**
     * @brief Store the single keyframe with both tangents, and use it before the first key.
     * @param value Keyframe value.
     * @param in_tangent Incoming tangent.
     * @param out_tangent Outgoing tangent.
     * @param key Sort key.
     */
    virtual void set_single_curve_key(const float* value, const float* in_tangent, const float* out_tangent, float key);

    /** Hermite segment between the keys around the last sample. */
    LibFloatSegment curve_segment;

    float last_value;
    float value_rate;
};

/** 0x54-byte float curve track allocated from g_float_curve_track_pool, with vtable D_177C70 in main data. */
class LibPooledFloatCurveTrack : public LibFloatCurveTrack
{
public:
    /** @brief Destroy the track. */
    virtual ~LibPooledFloatCurveTrack();

    virtual void release();

    /**
     * @brief Append a keyframe from plain floats.
     * @param key Sort key.
     * @param value Keyframe value.
     * @param in_tangent Incoming tangent.
     * @param out_tangent Outgoing tangent.
     */
    virtual void append_float_curve_key(float key, float value, float in_tangent, float out_tangent);

    /**
     * @brief Replace an indexed keyframe from plain floats.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @param in_tangent Incoming tangent.
     * @param out_tangent Outgoing tangent.
     */
    virtual void replace_float_curve_key(s32 index, float key, float value, float in_tangent, float out_tangent);

    /**
     * @brief Insert a keyframe from plain floats.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @param in_tangent Incoming tangent.
     * @param out_tangent Outgoing tangent.
     */
    virtual void insert_float_curve_key(s32 index, float key, float value, float in_tangent, float out_tangent);

    /**
     * @brief Store the single keyframe from plain floats.
     * @param key Sort key.
     * @param value Keyframe value.
     * @param in_tangent Incoming tangent.
     * @param out_tangent Outgoing tangent.
     */
    virtual void set_single_float_curve_key(float key, float value, float in_tangent, float out_tangent);
};

/** 32-byte keyframe of LibFloatQuaternionTrackBase: a key and a rotation quaternion at offset 0x10. */
struct LibFloatQuaternionTrackKey
{
    /** @brief Leave the keyframe uninitialized. */
    LibFloatQuaternionTrackKey();

    float key;

    /** Extra values the pooled track stores with each key; their meaning is unknown. */
    float first;
    float second;

    u8 unk0c[4];

    /** Rotation quaternion (x, y, z, w). */
    FieldVec4B value;
};

/** Key storage for rotation tracks with full float quaternions, with vtable D_177E50 in main data. */
class LibFloatQuaternionTrackBase : public LibClass173180
{
public:
    /** @brief Clear the pooled flag and reset the sequence. */
    LibFloatQuaternionTrackBase();

    /** @brief Release the keyframe storage. */
    virtual ~LibFloatQuaternionTrackBase();

    virtual void allocate_keys(s32 count);
    virtual void bind_keys(s32 count, void* keys);
    virtual void set_before_mode(u32 mode);
    virtual void set_after_mode(u32 mode);
    virtual s32 get_cycle_count() const;
    virtual s32 append_key(const void* value, const void* in_tangent, const void* out_tangent, float key);
    virtual s32 replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent);
    virtual s32 insert_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent);
    virtual void set_single_key(const void* value, const void* in_tangent, const void* out_tangent, float key);
    virtual s32 has_key(float key) const;
    virtual float wrap_key(float key) const;
    virtual float get_key_span() const;
    virtual void evaluate(float key, void* output);
    virtual s16 get_key_count() const;
    virtual void* get_keys();
    virtual void reset_state();
    virtual s16 get_key_capacity();

    /**
     * @brief Append a keyframe; the base ignores it.
     * @param value Keyframe value.
     * @param first First auxiliary value.
     * @param second Second auxiliary value.
     * @param key Sort key.
     * @return Nonzero when the keyframe was stored.
     */
    virtual s32 on_append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

    /**
     * @brief Replace an indexed keyframe; the base ignores it.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @param first First auxiliary value.
     * @param second Second auxiliary value.
     * @return Nonzero when the keyframe was stored.
     */
    virtual s32 on_replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

    /**
     * @brief Insert a keyframe at an index; the base ignores it.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @param first First auxiliary value.
     * @param second Second auxiliary value.
     * @return Nonzero when the keyframe was stored.
     */
    virtual s32 on_insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

    /**
     * @brief Store a single keyframe; the base ignores it.
     * @param value Keyframe value.
     * @param first First auxiliary value.
     * @param second Second auxiliary value.
     * @param key Sort key.
     */
    virtual void on_set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

    /**
     * @brief Return a zero quaternion, the track's value when it has no keys.
     * @return Zero vector.
     */
    virtual FieldVec4A get_zero_value() const;

    /**
     * @brief Return the rotation of the keyframe at a key.
     * @param key Key to find.
     * @return Keyframe rotation, or zero when the key is absent.
     */
    virtual FieldVec4A find_key_value(float key);

    /**
     * @brief Sample the track at a key.
     * @param key Key to sample at.
     * @return Rotation at the key.
     */
    virtual FieldVec4A sample(float key) const = 0;

    /** @brief Free the keys and give the track back to its pool; pooled tracks implement it. */
    virtual void return_to_pool() = 0;

    /** @brief Delete the key storage unless it is external, and clear the key pointer. */
    void free_keys();

    /**
     * @brief Wrap a key into the key span and record how many spans it was past the first key.
     * @param key Key to wrap.
     * @return Wrapped key, reflected on odd cycles in ping-pong mode.
     */
    float update_cycle_count(float key);

    /**
     * @brief Find the keys around a key, starting from the cached search index.
     * @param key Key to place.
     * @param lower Receives the lower key index.
     * @param upper Receives the upper key index.
     * @return One when an end mode extends the first or last segment, otherwise zero.
     */
    u8 find_surrounding_keys(float key, s32* lower, s32* upper);

    LibFloatQuaternionTrackKey* key_array;
    u8 unk08[8];

    /** Single cached keyframe, used before the first array key. */
    LibFloatQuaternionTrackKey single_key;

    LibTrackState state;
};

/** 0x80-byte float quaternion track allocated from g_float_quaternion_track_pool, with vtable D_177BE0 in main data. */
class LibPooledFloatQuaternionTrack : public LibFloatQuaternionTrackBase
{
public:
    /** @brief Destroy the track. */
    virtual ~LibPooledFloatQuaternionTrack();

    virtual s32 append_key(const void* value, const void* first, const void* second, float key);
    virtual void func_slot24();
    virtual s32 replace_key(s32 index, float key, const void* value, const void* first, const void* second);
    virtual s32 insert_key(s32 index, float key, const void* value, const void* first, const void* second);
    virtual s32 read_key(s32 index, float* key, void* value, void* first, void* second) const;
    virtual void set_single_key(const void* value, const void* first, const void* second, float key);
    virtual void reset_keys();
    virtual void get_end_delta(void* output) const;
    virtual void get_value_rate(void* output) const;
    virtual void release();
    virtual void reset_state();
    virtual FieldVec4A sample(float key) const;
    virtual void return_to_pool();

    /**
     * @brief Insert a keyframe at an index.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe rotation.
     * @param first First extra value.
     * @param second Second extra value.
     * @return Nonzero when the keyframe was stored.
     */
    s32 insert_entry(s32 index, float key, const FieldVec4A* value, float first, float second);

    u8 unk50[0x30];
};


/** 8-byte packed keyframe of LibQuaternionTrackBase: three halfword values and a halfword key. */
struct LibQuaternionTrackKey
{
    /**
     * @brief Copy the values and key.
     * @param entry Keyframe to copy.
     * @return This keyframe.
     */
    LibQuaternionTrackKey& operator=(const LibQuaternionTrackKey& entry)
    {
        packed_rotation[0] = entry.packed_rotation[0];
        packed_rotation[1] = entry.packed_rotation[1];
        packed_rotation[2] = entry.packed_rotation[2];
        key = entry.key;
        return *this;
    }

    /**
     * @brief Return the key as a float.
     * @return Key.
     */
    float get_key() const
    {
        return key;
    }

    /** Rotation as the quaternion's x, y and z in 1.15 fixed point; w is rebuilt from them. */
    s16 packed_rotation[3];

    s16 key;
};

/** Key storage for rotation tracks with quaternions packed as three halfwords, with vtable D_1731E0 in main data. */
class LibQuaternionTrackBase : public LibClass173180
{
public:
    /** @brief Release the keyframe storage. */
    virtual ~LibQuaternionTrackBase();

    virtual void allocate_keys(s32 count);
    virtual void bind_keys(s32 count, void* keys);
    virtual void set_before_mode(u32 mode);
    virtual void set_after_mode(u32 mode);
    virtual s32 get_cycle_count() const;
    virtual s32 append_key(const void* value, const void* in_tangent, const void* out_tangent, float key);
    virtual s32 replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent);
    virtual s32 insert_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent);
    virtual void set_single_key(const void* value, const void* in_tangent, const void* out_tangent, float key);
    virtual s32 has_key(float key) const;
    virtual float wrap_key(float key) const;
    virtual float get_key_span() const;
    virtual void evaluate(float key, void* output);
    virtual s16 get_key_count() const;
    virtual void* get_keys();
    virtual void reset_state();
    virtual s16 get_key_capacity();

    /**
     * @brief Append a keyframe; the base ignores it.
     * @param value Keyframe value.
     * @param first First auxiliary value.
     * @param second Second auxiliary value.
     * @param key Sort key.
     * @return Nonzero when the keyframe was stored.
     */
    virtual s32 on_append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

    /**
     * @brief Replace an indexed keyframe; the base ignores it.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @param first First auxiliary value.
     * @param second Second auxiliary value.
     * @return Nonzero when the keyframe was stored.
     */
    virtual s32 on_replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

    /**
     * @brief Insert a keyframe at an index; the base ignores it.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @param first First auxiliary value.
     * @param second Second auxiliary value.
     * @return Nonzero when the keyframe was stored.
     */
    virtual s32 on_insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

    /**
     * @brief Store a single keyframe; the base ignores it.
     * @param value Keyframe value.
     * @param first First auxiliary value.
     * @param second Second auxiliary value.
     * @param key Sort key.
     */
    virtual void on_set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

    /**
     * @brief Return a zero quaternion, the track's value when it has no keys.
     * @return Zero vector.
     */
    virtual FieldVec4A get_zero_value() const;

    /**
     * @brief Return the decoded rotation of the keyframe at a key.
     * @param key Key to find.
     * @return Keyframe rotation, or zero when the key is absent.
     */
    virtual FieldVec4A find_key_value(float key);

    /**
     * @brief Sample the track at a key.
     * @param key Key to sample at.
     * @return Rotation at the key.
     */
    virtual FieldVec4A sample(float key) const = 0;

    /** @brief Free the keys and give the track back to its pool; pooled tracks implement it. */
    virtual void return_to_pool() = 0;

    /** @brief Delete the key storage unless it is external, and clear the key pointer. */
    void free_keys();

    /**
     * @brief Wrap a key into the key span and record how many spans it was past the first key.
     * @param key Key to wrap.
     * @return Wrapped key, reflected on odd cycles in ping-pong mode.
     */
    float update_cycle_count(float key);

    /**
     * @brief Find the keys around a key, starting from the cached search index.
     * @param key Key to place.
     * @param lower Receives the lower key index.
     * @param upper Receives the upper key index.
     * @return One when an end mode extends the first or last segment, otherwise zero.
     */
    u8 find_surrounding_keys(float key, s32* lower, s32* upper);

    LibQuaternionTrackKey* key_array;

    /** Single cached keyframe, used before the first array key. */
    LibQuaternionTrackKey single_key;

    LibTrackState state;
};

#endif
