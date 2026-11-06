#ifndef SO3_OVERLAYS_BOOT_TRACKS_H
#define SO3_OVERLAYS_BOOT_TRACKS_H

#include "types.h"
#include "overlays/boot/boot.h"

/** Fixed pool of tracks with a bitmap of used slots. */
template <class T> struct BootTrackPool
{
        /**
         * @brief Allocate the tracks, mark them pooled and clear the used bitmap.
         * @param count Number of tracks.
         * @return One on success, or zero when the tracks could not be allocated.
         */
        s32 init(s32 count)
        {
            s32 index;
            s32 word_count;
            s32 word;
            items = new (0) T[count];

            if (items == 0)
            {
                return 0;
            }

            for (index = 0; index < count; index++)
            {
                items[index].state.pooled = true;
            }

            if (!external)
            {
                delete[] used;
            }

            capacity = count;
            words = (u32)(count + 63) >> 6;
            used = new (0) u64[words];
            external = false;
            this->count = count;
            unk04 = 0;
            word_count = words;

            for (word = 0; word < word_count; word++)
            {
                used[word] = 0;
            }

            return 1;
        }

        /**
         * @brief Mark a track's pool slot as free.
         * @param track Track to release.
         */
        void free(T* track)
        {
            u32 index = ((u32)track - (u32)items) / ((u32)&items[1] - (u32)items);
            used[index >> 6] &= ~((u64)1 << (index & 0x3F));
        }

        /** @brief Release every track in the pool and its storage. */
        void release()
        {
            s32 track_count = count;
            s32 index;

            for (index = 0; index < track_count; index++)
            {
                items[index].state.pooled = false;
            }

            delete[] items;

            if (!external)
            {
                delete[] used;
                used = 0;
            }

            items = 0;
            count = 0;
        }

        s32 count;
        s32 unk04;
        T* items;
        s32 capacity;
        s32 words;
        u64* used;
        bool external;
};

/** How a track evaluates keys outside its first and last keyframes. */
enum BootTrackEndMode
{
    /** Keep the first or last value outside the key span. */
    BOOT_TRACK_END_HOLD,

    /** Wrap the key into the stored span. */
    BOOT_TRACK_END_CYCLE,

    /** Use the first value at the last segment's endpoint. */
    BOOT_TRACK_END_CYCLE_TO_FIRST,

    /** Reflect the key on odd cycles. */
    BOOT_TRACK_END_PING_PONG,

    /** Continue evaluating the first or last segment outside the span. */
    BOOT_TRACK_END_EXTEND_SEGMENT,

    /** Wrap the key and add the endpoint difference for each cycle. */
    BOOT_TRACK_END_OFFSET_CYCLE,

    /** Interpolate from the stored single key before the first array key. */
    BOOT_TRACK_END_USE_PRE_START_KEY
};

/** Bookkeeping every track keeps after its key storage: counts, the cached lookup and how it extends past its ends. */
struct BootSequenceTail
{
    /** Whole key spans the last wrapped key was past the first key; negative before it. */
    s32 cycle_count;

    /** Last key minus first key. */
    float span;

    s16 key_count;
    s16 key_capacity;

    /** Lower key index the last search found; the next search starts there. */
    s16 search_index;

    /** Lower key index the cached segment was built from; -1 after the keys change. */
    s16 segment_lower;

    /** Upper key index the cached segment was built from; -1 after the keys change. */
    s16 segment_upper;

    /** BootTrackEndMode applied before the first key. */
    u8 before_mode : 4;

    /** BootTrackEndMode applied after the last key. */
    u8 after_mode : 4;

    /** Set when either end extends its first or last keyframe segment. */
    u8 extends_segment : 1;

    /** Set when the keys are bound from outside, so the track doesn't free them. */
    u8 external_keys : 1;

    /** Set while the track belongs to a pool. */
    u8 pooled : 1;

    u8 unk13_3_7 : 5;
};

/** Track record with vtable D_171B00 in main data; its data comes before the vptr. */
class BootFloatHistoryBase
{
    public:
        /** @brief Reset the record. */
        BootFloatHistoryBase();

        /** @brief Forget the stored samples. */
        void reset();

        u32 unk00;
        s16 sample_count;
        s16 next_index;
        u32 unk08;
        u32 unk0C;

        /** @brief Slot 8; empty here and in every Lib copy, so its purpose is unknown. */
        virtual void func_slot08();
};

/** BootFloatHistoryBase with vtable D_171B30 in main data. */
class BootFloatHistory : public BootFloatHistoryBase
{
    public:
        /** @brief Reset the record and clear its first word. */
        BootFloatHistory();

        /**
         * @brief Evaluate the record at a key.
         * @param key Evaluation key.
         * @return Evaluated value.
         */
        virtual float sample(float key) const = 0;

        /**
         * @brief Store a value and key in the two-entry history and count it, up to two.
         * @param value Value to store.
         * @param key Key to store.
         */
        virtual void push_sample(const float* value, float key);

        float values[2];
        float keys[2];
};

/** 0x24-byte BootFloatHistory with the Lib vtable D_178200. */
class BootClass178200 : public BootFloatHistory
{
    public:
        /**
         * @brief Evaluate the record at a key.
         * @param key Evaluation key.
         * @return Evaluated value.
         */
        virtual float sample(float key) const;

        /**
         * @brief Add a key and its value to the record.
         * @param key Key.
         * @param value Value at the key.
         */
        virtual void add_sample(float key, float value);
};

/** Vector record with vtable D_171B10 in main data; its data comes before the vptr. */
class BootVectorHistoryBase
{
    public:
        /** @brief Reset the record. */
        BootVectorHistoryBase();

        /** @brief Forget the stored samples. */
        void reset();

        FieldVec4B unk00;
        s16 sample_count;
        s16 next_index;
        u32 unk14;
        u32 unk18;

        /** @brief Slot 8; empty here and in every Lib copy, so its purpose is unknown. */
        virtual void func_slot08();
};

/** BootVectorHistoryBase with vtable D_171B50 in main data. */
class BootVectorHistory : public BootVectorHistoryBase
{
    public:
        /** @brief Reset the record and clear its vector. */
        BootVectorHistory();

        /**
         * @brief Evaluate the record at a key.
         * @param key Evaluation key.
         * @return Evaluated vector.
         */
        virtual FieldVec4B sample(float key) = 0;

        /**
         * @brief Store a value and key in the two-entry history and count it, up to two.
         * @param key Key to store.
         * @param value Value to store.
         */
        virtual void push_sample(float key, const FieldVec4A* value);

        FieldVec4B values[2];
        float keys[2];
};

/** 0x20-byte BootVectorHistory with the Lib vtable D_1781E0. */
class BootClass1781E0 : public BootVectorHistory
{
    public:
        /**
         * @brief Evaluate the record at a key.
         * @param key Evaluation key.
         * @return Evaluated vector.
         */
        virtual FieldVec4B sample(float key);
};

/**
 * Two-sample vector history with vtable D_171B20 in main data; its data comes before the vptr. The same layout as
 * BootVectorHistoryBase; Lib's BootClass1718C0-family sampler resets and fills one.
 */
class BootClass171B20
{
    public:
        /** @brief Reset the record. */
        BootClass171B20();

        /** @brief Forget the stored samples. */
        void reset();

        FieldVec4B unk00;
        s16 sample_count;
        s16 next_index;
        u32 unk14;
        u32 unk18;

        /** @brief Slot 8; empty here and in every Lib copy, so its purpose is unknown. */
        virtual void func_slot08();
};

/** BootClass171B20 with vtable D_171B70 in main data. */
class BootClass171B70 : public BootClass171B20
{
    public:
        /** @brief Reset the record and clear its vector. */
        BootClass171B70();

        // Pure virtual slot 0xC; only its position is known.
        virtual void func_slot0c() = 0;

        /**
         * @brief Store a value and key in the two-entry history and count it, up to two.
         * @param value Value to store.
         * @param key Key to store.
         */
        virtual void push_sample(const FieldVec4A* value, float key);

        FieldVec4B values[2];
        float keys[2];
};

/** 0x20-byte BootClass171B70 with the Lib vtable D_1781C0. */
class BootClass1781C0 : public BootClass171B70
{
    public:
        // Lib implementation of the pure slot; only its position is known.
        virtual void func_slot0c();
};

/** Scalar range with vtable D_171B88 in main data; its data comes before the vptr. */
class BootFloatSegmentBase
{
    public:
        /** @brief Install the vtable; the range is left unset. */
        BootFloatSegmentBase();

        float start_value;
        float end_value;
        float start_tangent;
        float end_tangent;
        float start_key;
        float end_key;
        float key_span;

        /**
         * @brief Evaluate the segment at a key; Lib implements this.
         * @param key Evaluation key.
         * @return Value at the key.
         */
        float interpolate(float key) const;

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

/** 0x20-byte BootFloatSegmentBase with vtable D_171270 in main data. */
class BootFloatSegment : public BootFloatSegmentBase
{
    public:
        /**
         * @brief Evaluate the segment at a key.
         * @param key Evaluation key.
         * @return Value at the key.
         */
        virtual float evaluate(float key) const;
};

/** Root of the keyframe tracks (vtable D_171170 in main data). A track holds keys sorted by time and samples a value between them. */
class BootTrack
{
    public:
        /** @brief Destroy the track. */
        virtual ~BootTrack()
        {
        }
};

/** 8-byte scalar keyframe of BootFloatTrackBase: a key followed by its value. */
struct BootFloatTrackKey
{
    /**
     * @brief Copy the key and value.
     * @param entry Entry to copy.
     * @return This entry.
     */
    BootFloatTrackKey& operator=(const BootFloatTrackKey& entry)
    {
        key = entry.key;
        value = entry.value;
        return *this;
    }

    float key;
    float value;
};

/** Key storage and bookkeeping for tracks of single float values (vtable D_1717A0 in main data); keys aren't stored at this level. */
class BootFloatTrackBase : public BootTrack
{
    public:
        /** @brief Construct the track. */
        BootFloatTrackBase();

        /** @brief Destroy the track. */
        virtual ~BootFloatTrackBase();

        /**
         * @brief Allocate storage for the requested keyframe count.
         * @param count Requested keyframe count.
         */
        virtual void allocate_keys(s32 count);

        /**
         * @brief Bind an external keyframe array.
         * @param count Keyframe count.
         * @param entries External keyframe storage.
         */
        virtual void bind_keys(s32 count, BootFloatTrackKey* entries);

        /**
         * @brief Set what the track does before its first key.
         * @param value Mode value.
         */
        virtual void set_before_mode(u32 value);

        /**
         * @brief Set what the track does after its last key.
         * @param value Mode value.
         */
        virtual void set_after_mode(u32 value);

        /**
         * @brief Return how many key spans the last wrapped key was past the first key.
         * @return Signed cycle count.
         */
        virtual s32 get_cycle_count() const;

        /**
         * @brief Append a keyframe.
         * @param value Keyframe value.
         * @param key Sort key.
         * @return Append status.
         */
        virtual s32 append_key(const float* value, float key);

        /** @brief Slot 0x24; BootTrack's empty version (track_default_func_slot24) is the only one. */
        virtual void func_slot24();

        /**
         * @brief Replace an indexed keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @return Replacement status.
         */
        virtual s32 replace_key(s32 index, float key, const float* value);

        /**
         * @brief Insert an indexed keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @return Insertion status.
         */
        virtual s32 insert_key(s32 index, float key, const float* value);

        /**
         * @brief Read an indexed keyframe; the base has none.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @return Nonzero when the keyframe is available.
         */
        virtual s32 read_key(s32 index, float* key, float* value, float* first, float* second) const;

        /**
         * @brief Add a keyframe through the track implementation.
         * @param value Keyframe value.
         * @param key Sort key.
         */
        virtual void set_single_key(const float* value, float key);

        /** @brief Run the default update hook. */
        virtual void reset_keys();

        /**
         * @brief Test whether the track contains the supplied key.
         * @param key Key to find.
         * @return Nonzero when the key exists.
         */
        virtual s32 has_key(float key) const;

        /**
         * @brief Return the difference between the last and first key values.
         * @param output Receives the difference.
         */
        virtual void get_end_delta(float* output) const = 0;

        /**
         * @brief Wrap a key into the stored key range.
         * @param key Key to wrap.
         * @return Wrapped key.
         */
        virtual float wrap_key(float key) const;

        /**
         * @brief Return how fast the value changed at the last sample, per second.
         * @param output Receives the rate.
         */
        virtual void get_value_rate(float* output) const = 0;

        /**
         * @brief Return the span between the first and last keys.
         * @return Key span, or zero with fewer than two keys.
         */
        virtual float get_key_span() const;

        /**
         * @brief Evaluate the track at a key.
         * @param key Evaluation key.
         * @param output Receives the evaluated value.
         */
        virtual void evaluate(float key, float* output);

        /**
         * @brief Return the stored keyframe count.
         * @return Keyframe count.
         */
        virtual s16 get_key_count() const;

        /** @brief Return a pooled track to its pool, or delete an ordinary track. */
        virtual void release();

        /**
         * @brief Return the keyframe storage.
         * @return Keyframe storage.
         */
        virtual BootFloatTrackKey* get_keys();

        /** @brief Reset the sequence fields and set both modes to one. */
        virtual void reset_state();

        /**
         * @brief Return the number of keys the storage can hold.
         * @return Key capacity.
         */
        virtual s16 get_key_capacity();

        /**
         * @brief Handle a keyframe with a key; the base implementation ignores it.
         * @param value Key value.
         * @param key Key the keyframe sits at.
         * @return Handler result.
         */
        virtual s32 on_append_key(const float* value, float key);

        /**
         * @brief Handle an indexed keyframe with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @return Handler result.
         */
        virtual s32 on_replace_key(s32 index, float key, const float* value);

        /**
         * @brief Handle an indexed keyframe with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @return Handler result.
         */
        virtual s32 on_insert_key(s32 index, float key, const float* value);

        /**
         * @brief Handle a keyframe with a key; the base implementation ignores it.
         * @param value Key value.
         * @param key Key the keyframe sits at.
         */
        virtual void on_set_single_key(const float* value, float key);

        /**
         * @brief Return zero.
         * @return Zero.
         */
        virtual float get_zero_value() const;

        /**
         * @brief Return the value of the keyframe with the supplied key.
         * @param key Key to find.
         * @return Keyframe value, or zero when the key is absent.
         */
        virtual float find_key_value(float key);

        // Implemented by the derived tracks: sample (slot 0x80) and return_to_pool (slot 0x84).
        virtual float sample(float key) = 0;

        virtual void return_to_pool() = 0;

        /** @brief Delete the key storage unless it is external, and clear the key pointer. */
        void free_keys();

        /**
         * @brief Normalize a key across the cached span and store its signed period count.
         * @param key Key whose period count is representable as a signed 32-bit integer.
         * @return Normalized key, with odd-period reflection selected by the control fields.
         */
        float update_cycle_count(float key);

        /**
         * @brief Find the entries around a key, starting from the cached cursor.
         * @param key Key to place.
         * @param lower Receives the lower entry index.
         * @param upper Receives the upper entry index.
         * @return One when the active end mode extends the first or last segment, otherwise zero.
         */
        u8 find_surrounding_keys(float key, s32* lower, s32* upper);

        BootFloatTrackKey* key_array;

        /** Single cached keyframe, used before an array is allocated. */
        BootFloatTrackKey single_key;

        BootSequenceTail state;
};

/** Float track that stores its keys in the array (vtable D_171560 in main data). */
class BootFloatKeyTrack : public BootFloatTrackBase
{
    public:
        /** @brief Destroy the track. */
        virtual ~BootFloatKeyTrack()
        {
        }

        /**
         * @brief Read an indexed keyframe.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @return One when the index is within the capacity, otherwise zero.
         */
        virtual s32 read_key(s32 index, float* key, float* value, float* first, float* second) const;

        /**
         * @brief Append a keyframe.
         * @param value Keyframe value.
         * @param key Sort key.
         * @return Nonzero when the keyframe was stored.
         */
        virtual s32 on_append_key(const float* value, float key);

        /**
         * @brief Replace an indexed keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @return Nonzero when the keyframe was stored.
         */
        virtual s32 on_replace_key(s32 index, float key, const float* value);

        /**
         * @brief Insert a keyframe at an index.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @return Nonzero when the keyframe was stored.
         */
        virtual s32 on_insert_key(s32 index, float key, const float* value);

        /**
         * @brief Store a single keyframe.
         * @param value Keyframe value.
         * @param key Sort key.
         */
        virtual void on_set_single_key(const float* value, float key);
};

/** Float track that samples its keys and caches the value and its change per frame (vtable D_1715F0 in main data). */
class BootFloatTrack : public BootFloatKeyTrack
{
    public:
        /** @brief Destroy the track. */
        virtual ~BootFloatTrack()
        {
        }

        /** @brief Reset to a single zero keyframe at key zero, then select the cycle end mode. */
        virtual void reset_keys();

        /**
         * @brief Return the difference between the endpoint values.
         * @param output Receives the difference.
         */
        virtual void get_end_delta(float* output) const;

        /**
         * @brief Return how fast the value changed at the last sample, per second.
         * @param output Receives the rate.
         */
        virtual void get_value_rate(float* output) const;

        /** @brief Clear the last sampled value, then reset the key state. */
        virtual void reset_state();

        /**
         * @brief Evaluate the track at a key.
         * @param key Evaluation key.
         * @return Evaluated value.
         */
        virtual float sample(float key);

        BootClass178200 sample_history;
        float last_value;
        float value_rate;
};

/** 0x50-byte float track allocated from a BootTrackPool, with the Lib vtable D_177F70. */
class BootPooledFloatTrack : public BootFloatTrack
{
    public:
        /** @brief Construct the track. */
        BootPooledFloatTrack();

        /** @brief Destroy the track. */
        virtual ~BootPooledFloatTrack();

        /** @brief Free the keys and give the track back to its pool; boot uses the Lib implementation. */
        virtual void return_to_pool();
};

/** 16-byte keyframe of BootVectorTrackBase; the value's fourth component is its key. */
struct BootVectorTrackKey
{
    /** @brief Leave the value uninitialized. */
    BootVectorTrackKey()
    {
    }

    FieldVec4B value;
};

/** Key storage for tracks of xyz vectors whose w holds the key (vtable D_171830 in main data). */
class BootVectorTrackBase : public BootTrack
{
    public:
        /** @brief Construct the track. */
        BootVectorTrackBase();

        /** @brief Destroy the track. */
        virtual ~BootVectorTrackBase();

        /**
         * @brief Allocate storage for the requested keyframe count.
         * @param count Requested keyframe count.
         */
        virtual void allocate_keys(s32 count);

        /**
         * @brief Bind an external keyframe array.
         * @param count Keyframe count.
         * @param entries External keyframe storage.
         */
        virtual void bind_keys(s32 count, BootVectorTrackKey* entries);

        /**
         * @brief Set what the track does before its first key.
         * @param value Mode value.
         */
        virtual void set_before_mode(u32 value);

        /**
         * @brief Set what the track does after its last key.
         * @param value Mode value.
         */
        virtual void set_after_mode(u32 value);

        /**
         * @brief Return how many key spans the last wrapped key was past the first key.
         * @return Signed cycle count.
         */
        virtual s32 get_cycle_count() const;

        /**
         * @brief Append a vector keyframe.
         * @param value Keyframe value.
         * @param key Sort key.
         * @return Append status.
         */
        virtual s32 append_key(const FieldVec4A* value, float key);

        /** @brief Slot 0x24; BootTrack's empty version (track_default_func_slot24) is the only one. */
        virtual void func_slot24();

        /**
         * @brief Replace an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @return Replacement status.
         */
        virtual s32 replace_key(s32 index, float key, const FieldVec4A* value);

        /**
         * @brief Insert an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @return Insertion status.
         */
        virtual s32 insert_key(s32 index, float key, const FieldVec4A* value);

        /**
         * @brief Read an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Receives the sort key.
         * @param value Receives the value.
         * @param first Receives the first auxiliary vector.
         * @param second Receives the second auxiliary vector.
         * @return Nonzero when the keyframe is available.
         */
        virtual s32 read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        /**
         * @brief Add a vector keyframe through the track implementation.
         * @param value Keyframe value.
         * @param key Sort key.
         */
        virtual void set_single_key(const FieldVec4A* value, float key);

        /** @brief Run the default update hook. */
        virtual void reset_keys();

        /**
         * @brief Test whether the track contains the supplied key.
         * @param key Key to find.
         * @return Nonzero when the key exists.
         */
        virtual s32 has_key(float key) const;

        /**
         * @brief Return the difference between the last and first key values.
         * @param output Receives the difference.
         */
        virtual void get_end_delta(FieldVec4B* output) const = 0;

        /**
         * @brief Wrap a key into the stored key range.
         * @param key Key to wrap.
         * @return Wrapped key.
         */
        virtual float wrap_key(float key) const;

        /**
         * @brief Return how fast the value changed at the last sample, per second.
         * @param output Receives the rate.
         */
        virtual void get_value_rate(FieldVec4B* output) const = 0;

        /**
         * @brief Return the span between the first and last keys.
         * @return Key span, or zero when fewer than two keys are stored.
         */
        virtual float get_key_span() const;

        /**
         * @brief Evaluate the vector track at a key.
         * @param key Evaluation key.
         * @param output Receives the evaluated vector.
         */
        virtual void evaluate(float key, FieldVec4B* output);

        /**
         * @brief Return the stored keyframe count.
         * @return Keyframe count.
         */
        virtual s16 get_key_count() const;

        /** @brief Return a pooled track or delete an ordinary track. */
        virtual void release();

        /**
         * @brief Return the key storage.
         * @return Key array, or null.
         */
        virtual BootVectorTrackKey* get_keys();

        /** @brief Reset the sequence fields and set both modes to one. */
        virtual void reset_state();

        /**
         * @brief Return the number of keys the storage can hold.
         * @return Key capacity.
         */
        virtual s16 get_key_capacity();

        /**
         * @brief Handle a vector set with a key; the base implementation ignores it.
         * @param value Key value.
         * @param key Key the keyframe sits at.
         * @return Handler result.
         */
        virtual s32 on_append_key(const FieldVec4A* value, float key);

        /**
         * @brief Handle an indexed vector set with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @return Handler result.
         */
        virtual s32 on_replace_key(s32 index, float key, const FieldVec4A* value);

        /**
         * @brief Handle an indexed vector set with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @return Handler result.
         */
        virtual s32 on_insert_key(s32 index, float key, const FieldVec4A* value);

        /**
         * @brief Handle a vector set with a key; the base implementation ignores it.
         * @param value Key value.
         * @param key Key the keyframe sits at.
         */
        virtual void on_set_single_key(const FieldVec4A* value, float key);

        /**
         * @brief Return a zero vector.
         * @return Zero vector.
         */
        virtual FieldVec4A get_zero_value() const;

        /**
         * @brief Return the value of the keyframe with the supplied key.
         * @param key Key to find.
         * @return Keyframe value, or zero when the key is absent.
         */
        virtual FieldVec4A find_key_value(float key);

        /**
         * @brief Sample the track at a key and cache the value and its change per second.
         * @param key Key to sample at.
         * @return Value at the key.
         */
        virtual FieldVec4A sample(float key) = 0;

        /** @brief Free the keys and give the track back to its pool; pooled tracks implement it. */
        virtual void return_to_pool() = 0;

        /** @brief Delete the key storage unless it is external, and clear the key pointer. */
        void free_keys();

        /**
         * @brief Normalize a key across the cached span and store its signed period count.
         * @param key Key whose period count is representable as a signed 32-bit integer.
         * @return Normalized key, with odd-period reflection selected by the control fields.
         */
        float update_cycle_count(float key);

        /**
         * @brief Find the entries around a key, starting from the cached cursor.
         * @param key Key to place.
         * @param lower Receives the lower entry index.
         * @param upper Receives the upper entry index.
         * @return One when the active end mode extends the first or last segment, otherwise zero.
         */
        u8 find_surrounding_keys(float key, s32* lower, s32* upper);

        BootVectorTrackKey* key_array;
        u8 unk08[8];

        /** Single cached keyframe, used before an array is allocated. */
        BootVectorTrackKey single_key;

        BootSequenceTail state;
};

/** Vector track that stores its keys in the array (vtable D_1713B0 in main data). */
class BootVectorKeyTrack : public BootVectorTrackBase
{
    public:
        /** @brief Destroy the track. */
        virtual ~BootVectorKeyTrack()
        {
        }

        // Overrides of the base slots of the same names.
        virtual s32 read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        virtual s32 on_append_key(const FieldVec4A* value, float key);
        virtual s32 on_replace_key(s32 index, float key, const FieldVec4A* value);
        virtual s32 on_insert_key(s32 index, float key, const FieldVec4A* value);
        virtual void on_set_single_key(const FieldVec4A* value, float key);
};

/** Vector track that samples its keys and caches the value and its change per frame (vtable D_171440 in main data). */
class BootVectorTrack : public BootVectorKeyTrack
{
    public:
        /** @brief Destroy the track. */
        virtual ~BootVectorTrack()
        {
        }

        // Overrides of the base slots of the same names.
        virtual void reset_keys();

        virtual void get_end_delta(FieldVec4B* output) const;
        virtual void get_value_rate(FieldVec4B* output) const;
        virtual void reset_state();
        virtual FieldVec4A sample(float key);

        BootClass1781E0 sample_history;
        FieldVec4B last_value;
        FieldVec4B value_rate;
};

/** 0xB0-byte vector track allocated from a BootTrackPool (vtable D_1714D0 in main data). */
class BootPooledVectorTrack : public BootVectorTrack
{
    public:
        /** @brief Construct the track. */
        BootPooledVectorTrack();

        /** @brief Destroy the track. */
        virtual ~BootPooledVectorTrack();

        // Overrides of the base slots of the same names.
        virtual void release();

        virtual void return_to_pool();
};

/** 32-byte keyframe of BootClass1718C0: a key and a value at offset 0x10. */
struct BootTrackKey1718C0
{
    /** @brief Leave the keyframe uninitialized. */
    BootTrackKey1718C0();

    float key;
    FieldVec4B value;
};

/**
 * Keyframe track with vtable D_1718C0 in main data; its constructor and destructor are out of line. The values look
 * like rotations: Lib's sampler (0x4B1A50, through D_177EE0) handles the end modes with quaternion inverses and a VU
 * normalize, as BootFloatQuaternionTrackBase's does, but interpolates with plain float maths and a BootClass171B70
 * history instead of slerp.
 */
class BootClass1718C0 : public BootTrack
{
    public:
        /** @brief Construct the track. */
        BootClass1718C0();

        /** @brief Destroy the track. */
        virtual ~BootClass1718C0();

        /**
         * @brief Allocate storage for the requested keyframe count.
         * @param count Requested keyframe count.
         */
        virtual void allocate_keys(s32 count);

        /**
         * @brief Bind an external keyframe array.
         * @param count Keyframe count.
         * @param entries External keyframe storage.
         */
        virtual void bind_keys(s32 count, BootTrackKey1718C0* entries);

        /**
         * @brief Set what the track does before its first key.
         * @param value Mode value.
         */
        virtual void set_before_mode(u32 value);

        /**
         * @brief Set what the track does after its last key.
         * @param value Mode value.
         */
        virtual void set_after_mode(u32 value);

        /**
         * @brief Return how many key spans the last wrapped key was past the first key.
         * @return Signed cycle count.
         */
        virtual s32 get_cycle_count() const;

        /**
         * @brief Append a vector keyframe.
         * @param value Keyframe value.
         * @param key Sort key.
         * @return Append status.
         */
        virtual s32 append_key(const FieldVec4A* value, float key);

        /** @brief Slot 0x24; BootTrack's empty version (track_default_func_slot24) is the only one. */
        virtual void func_slot24();

        /**
         * @brief Replace an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @return Replacement status.
         */
        virtual s32 replace_key(s32 index, float key, const FieldVec4A* value);

        /**
         * @brief Insert an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @return Insertion status.
         */
        virtual s32 insert_key(s32 index, float key, const FieldVec4A* value);

        /**
         * @brief Read an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Receives the sort key.
         * @param value Receives the value.
         * @param first Receives the first auxiliary vector.
         * @param second Receives the second auxiliary vector.
         * @return Nonzero when the keyframe is available.
         */
        virtual s32 read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        /**
         * @brief Add a vector keyframe through the track implementation.
         * @param value Keyframe value.
         * @param key Sort key.
         */
        virtual void set_single_key(const FieldVec4A* value, float key);

        /** @brief Run the default update hook. */
        virtual void reset_keys();

        /**
         * @brief Test whether the track contains the supplied key.
         * @param key Key to find.
         * @return Nonzero when the key exists.
         */
        virtual s32 has_key(float key) const;

        /**
         * @brief Return the difference between the last and first key values.
         * @param output Receives the difference.
         */
        virtual void get_end_delta(FieldVec4B* output) const = 0;

        /**
         * @brief Wrap a key into the stored key range.
         * @param key Key to wrap.
         * @return Wrapped key.
         */
        virtual float wrap_key(float key) const;

        /**
         * @brief Return how fast the value changed at the last sample, per second.
         * @param output Receives the rate.
         */
        virtual void get_value_rate(FieldVec4B* output) const = 0;

        /**
         * @brief Return the span between the first and last keys.
         * @return Key span, or zero when fewer than two keys are stored.
         */
        virtual float get_key_span() const;

        /**
         * @brief Evaluate the vector track at a key.
         * @param key Evaluation key.
         * @param output Receives the evaluated vector.
         */
        virtual void evaluate(float key, FieldVec4B* output) const;

        /**
         * @brief Return the stored keyframe count.
         * @return Keyframe count.
         */
        virtual s16 get_key_count() const;

        /** @brief Return a pooled track or delete an ordinary track. */
        virtual void release();

        /**
         * @brief Return the key storage.
         * @return Key array, or null.
         */
        virtual BootTrackKey1718C0* get_keys();

        /** @brief Clear the key storage, counts, modes and cached indices. */
        virtual void reset_state();

        /**
         * @brief Return the number of keys the storage can hold.
         * @return Key capacity.
         */
        virtual s16 get_key_capacity();

        /**
         * @brief Handle a vector set with a key; the base implementation ignores it.
         * @param value Key value.
         * @param key Key the keyframe sits at.
         * @return Handler result.
         */
        virtual s32 on_append_key(const FieldVec4A* value, float key);

        /**
         * @brief Handle an indexed vector set with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @return Handler result.
         */
        virtual s32 on_replace_key(s32 index, float key, const FieldVec4A* value);

        /**
         * @brief Handle an indexed vector set with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @return Handler result.
         */
        virtual s32 on_insert_key(s32 index, float key, const FieldVec4A* value);

        /**
         * @brief Handle a vector set with a key; the base implementation ignores it.
         * @param value Key value.
         * @param key Key the keyframe sits at.
         */
        virtual void on_set_single_key(const FieldVec4A* value, float key);

        /**
         * @brief Return a zero vector.
         * @return Zero vector.
         */
        virtual FieldVec4A get_zero_value() const;

        /**
         * @brief Return the value of the keyframe with the supplied key.
         * @param key Key to find.
         * @return Keyframe value, or zero when the key is absent.
         */
        virtual FieldVec4A find_key_value(float key);

        /**
         * @brief Sample the track at a key and cache the value and its change per second.
         * @param key Key to sample at.
         * @return Value at the key.
         */
        virtual FieldVec4A sample(float key) const = 0;

        /** @brief Free the keys and give the track back to its pool; pooled tracks implement it. */
        virtual void return_to_pool() = 0;

        /** @brief Delete the key storage unless it is external, and clear the key pointer. */
        void free_keys();

        BootTrackKey1718C0* key_array;
        u8 unk08[8];

        /** Key of the single cached keyframe, used before an array is allocated. */
        float single_key;

        u8 unk14[0xC];

        /** Value of the single cached keyframe. */
        FieldVec4B single_value;

        BootSequenceTail state;
};

/** Partial BootClass1718C0 with vtable D_171320 in main data. */
class BootClass171320 : public BootClass1718C0
{
    public:
        /** @brief Destroy the track. */
        virtual ~BootClass171320()
        {
        }

        // Overrides of the base slots of the same names.
        virtual s32 read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        virtual s32 on_append_key(const FieldVec4A* value, float key);
        virtual s32 on_replace_key(s32 index, float key, const FieldVec4A* value);
        virtual s32 on_insert_key(s32 index, float key, const FieldVec4A* value);
        virtual void on_set_single_key(const FieldVec4A* value, float key);
};

/** 0xC0-byte pooled track with the Lib vtable D_177EE0. */
class BootClass177EE0 : public BootClass171320
{
    public:
        /** @brief Construct the track. */
        BootClass177EE0();

        /** @brief Destroy the track. */
        virtual ~BootClass177EE0();

        // Boot uses the Lib implementations of these.
        virtual void get_end_delta(FieldVec4B* output) const;

        virtual void get_value_rate(FieldVec4B* output) const;
        virtual FieldVec4A sample(float key) const;
        virtual void return_to_pool();

        BootClass1781C0 unk50;
        u8 unkA0[0x20];
};

/** 16-byte keyframe of BootFloatCurveTrackBase: a key and three values. */
struct BootFloatCurveTrackKey
{
    /**
     * @brief Copy the key and three values.
     * @param entry Entry to copy.
     * @return This entry.
     */
    BootFloatCurveTrackKey& operator=(const BootFloatCurveTrackKey& entry)
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

/** Key storage for float tracks whose keys carry a value and two tangents (vtable D_171950 in main data). */
class BootFloatCurveTrackBase : public BootTrack
{
    public:
        /** @brief Construct the track. */
        BootFloatCurveTrackBase();

        /** @brief Destroy the track. */
        virtual ~BootFloatCurveTrackBase();

        /**
         * @brief Replace the entry array with count new entries.
         * @param count Number of entries.
         */
        virtual void allocate_keys(s32 count);

        /**
         * @brief Install an entry array, set both counts, mark the array as installed and cache its span.
         * @param count Number of entries; must be at least one.
         * @param entries Entry array to install.
         */
        virtual void bind_keys(s32 count, BootFloatCurveTrackKey* entries);

        /**
         * @brief Set what the track does before its first key, and whether it extends an end segment.
         * @param value Value whose low four bits are stored.
         */
        virtual void set_before_mode(u32 value);

        /**
         * @brief Set what the track does after its last key, and whether it extends an end segment.
         * @param value Value whose low four bits are stored.
         */
        virtual void set_after_mode(u32 value);

        /**
         * @brief Return how many key spans the last wrapped key was past the first key.
         * @return Signed cycle count.
         */
        virtual s32 get_cycle_count() const;

        /**
         * @brief Append an entry through slot 24.
         * @param value Key value, or null.
         * @param in_tangent Tangent arriving at the key, or null.
         * @param out_tangent Tangent leaving the key, or null.
         * @param key Sort value.
         * @return The result of slot 24.
         */
        virtual s32 append_key(const float* value, const float* in_tangent, const float* out_tangent, float key);

        /** @brief Default virtual handler that performs no work. */
        virtual void func_slot24();

        /**
         * @brief Set an entry through slot 25.
         * @param index Entry index.
         * @param key Sort value.
         * @param value Key value, or null.
         * @param in_tangent Tangent arriving at the key, or null.
         * @param out_tangent Tangent leaving the key, or null.
         * @return The result of slot 25.
         */
        virtual s32 replace_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent);

        /**
         * @brief Insert an entry through slot 26.
         * @param index Entry index.
         * @param key Sort value.
         * @param value Key value, or null.
         * @param in_tangent Tangent arriving at the key, or null.
         * @param out_tangent Tangent leaving the key, or null.
         * @return The result of slot 26.
         */
        virtual s32 insert_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent);

        /**
         * @brief Default entry reader that returns zero.
         * @param index Entry index.
         * @param key Receives the sort value, or null.
         * @param value Receives the key value, or null.
         * @param in_tangent Receives the arriving tangent, or null.
         * @param out_tangent Receives the leaving tangent, or null.
         * @return Always 0.
         */
        virtual s32 read_key(s32 index, float* key, float* value, float* in_tangent, float* out_tangent) const;

        /**
         * @brief Add an entry through slot 27.
         * @param value Key value, or null.
         * @param in_tangent Tangent arriving at the key, or null.
         * @param out_tangent Tangent leaving the key, or null.
         * @param key Sort value.
         */
        virtual void set_single_key(const float* value, const float* in_tangent, const float* out_tangent, float key);

        /** @brief Default virtual handler that performs no work. */
        virtual void reset_keys();

        /**
         * @brief Test whether an entry has exactly the given sort value.
         * @param key Sort value to find.
         * @return 1 when a matching entry exists, otherwise 0.
         */
        virtual s32 has_key(float key) const;

        /**
         * @brief Return the difference between the last and first key values.
         * @param output Receives the difference.
         */
        virtual void get_end_delta(float* output) const = 0;

        /**
         * @brief Wrap a value into the span between the first and last entry sort values.
         * @param key Value to wrap.
         * @return value reduced by a whole number of spans, or value unchanged when that number is zero.
         */
        virtual float wrap_key(float key) const;

        /**
         * @brief Return how fast the value changed at the last sample, per second.
         * @param output Receives the rate.
         */
        virtual void get_value_rate(float* output) const = 0;

        /**
         * @brief Compute the span between the first and last entry sort values.
         * @return The span, or 0.0f when fewer than two entries exist.
         */
        virtual float get_key_span() const;

        /**
         * @brief Store slot 30's value for a sort value.
         * @param key Sort value.
         * @param output Receives the value.
         */
        virtual void evaluate(float key, float* output);

        /**
         * @brief Return the stored keyframe count.
         * @return Keyframe count.
         */
        virtual s16 get_key_count() const;

        /** @brief Delete the object through its virtual destructor. */
        virtual void release();

        /**
         * @brief Return the key storage.
         * @return Key array, or null.
         */
        virtual BootFloatCurveTrackKey* get_keys() const;

        /** @brief Reset the entry array pointer, counters, indices, nibbles and ownership flags. */
        virtual void reset_state();

        /**
         * @brief Return the number of keys the storage can hold.
         * @return Key capacity.
         */
        virtual s16 get_key_capacity() const;

        /**
         * @brief Default append handler.
         * @param value Key value, or null.
         * @param in_tangent Tangent arriving at the key, or null.
         * @param out_tangent Tangent leaving the key, or null.
         * @param key Sort value.
         * @return Always 0.
         */
        virtual s32 on_append_key(const float* value, const float* in_tangent, const float* out_tangent, float key);

        /**
         * @brief Default set handler.
         * @param index Entry index.
         * @param key Sort value.
         * @param value Key value, or null.
         * @param in_tangent Tangent arriving at the key, or null.
         * @param out_tangent Tangent leaving the key, or null.
         * @return Always 0.
         */
        virtual s32 on_replace_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent);

        /**
         * @brief Default insert handler.
         * @param index Entry index.
         * @param key Sort value.
         * @param value Key value, or null.
         * @param in_tangent Tangent arriving at the key, or null.
         * @param out_tangent Tangent leaving the key, or null.
         * @return Always 0.
         */
        virtual s32 on_insert_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent);

        /**
         * @brief Default add handler.
         * @param value Key value, or null.
         * @param in_tangent Tangent arriving at the key, or null.
         * @param out_tangent Tangent leaving the key, or null.
         * @param key Sort value.
         */
        virtual void on_set_single_key(const float* value, const float* in_tangent, const float* out_tangent, float key);

        /**
         * @brief Report a fixed zero value for this receiver class.
         * @return Always 0.0f.
         */
        virtual float get_zero_value() const;

        /**
         * @brief Find the first entry with the requested sort value.
         * @param key Sort value to find.
         * @return The entry's first component, or zero when no entry matches.
         */
        virtual float find_key_value(float key);

        /**
         * @brief Sample the track at a key and cache the value and its change per second.
         * @param key Key to sample at.
         * @return Value at the key.
         */
        virtual float sample(float key) = 0;

        /**
         * @brief Append a key with its tangents.
         * @param value Key value.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         * @param key Key.
         * @return Nonzero when the key was stored.
         */
        virtual s32 append_curve_key(const float* value, const float* in_tangent, const float* out_tangent, float key) = 0;

        /** @brief Delete the key storage unless it is external, and clear the key pointer. */
        void free_keys();

        /**
         * @brief Normalize a key across the cached span and store its signed period count.
         * @param key Key whose period count is representable as a signed 32-bit integer.
         * @return Normalized key, with odd-period reflection selected by the control fields.
         */
        float update_cycle_count(float key);

        /**
         * @brief Find the entries around a key, starting from the cached cursor.
         * @param key Key to place.
         * @param lower Receives the lower entry index.
         * @param upper Receives the upper entry index.
         * @return One when the active end mode extends the first or last segment, otherwise zero.
         */
        u8 find_surrounding_keys(float key, s32* lower, s32* upper);

        BootFloatCurveTrackKey* key_array;
        BootFloatCurveTrackKey single_key;
        BootSequenceTail state;
};

/** Float curve track that stores and samples its keys (vtable D_171280 in main data). */
class BootFloatCurveTrack : public BootFloatCurveTrackBase
{
    public:
        /** @brief Destroy the track. */
        virtual ~BootFloatCurveTrack()
        {
        }

        // Overrides of the base slots of the same names.
        virtual s32 append_key(const float* value, const float* in_tangent, const float* out_tangent, float key);

        virtual s32 replace_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent);
        virtual s32 insert_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent);
        virtual s32 read_key(s32 index, float* key, float* value, float* in_tangent, float* out_tangent) const;
        virtual void set_single_key(const float* value, const float* in_tangent, const float* out_tangent, float key);
        virtual void reset_keys();
        virtual void get_end_delta(float* output) const;
        virtual void get_value_rate(float* output) const;
        virtual void reset_state();
        virtual float sample(float key);
        virtual s32 append_curve_key(const float* value, const float* in_tangent, const float* out_tangent, float key);

        /**
         * @brief Replace an indexed entry.
         * @param index Entry index.
         * @param key Sort value.
         * @param value Key value.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         * @return One when the entry was stored.
         */
        virtual s32 replace_curve_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent);

        /**
         * @brief Insert an entry at an index.
         * @param index Entry index.
         * @param key Sort value.
         * @param value Key value.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         * @return One when the entry was stored.
         */
        virtual s32 insert_curve_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent);

        /**
         * @brief Store a single entry in the cached entry.
         * @param value Key value.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         * @param key Sort value.
         */
        virtual void set_single_curve_key(const float* value, const float* in_tangent, const float* out_tangent, float key);

        BootFloatSegment curve_segment;
        float last_value;
        float value_rate;
};

/** 0x54-byte float curve track allocated from a BootTrackPool, with the Lib vtable D_177C70. */
class BootPooledFloatCurveTrack : public BootFloatCurveTrack
{
    public:
        /** @brief Construct the track. */
        BootPooledFloatCurveTrack();

        /** @brief Destroy the track. */
        virtual ~BootPooledFloatCurveTrack();
};

/** Vector range with vtable D_171B98 in main data; its data comes before the vptr. */
class BootVectorSegmentBase
{
    public:
        /** @brief Install the vtable; the range is left unset. */
        BootVectorSegmentBase();

        FieldVec4B start_value;
        FieldVec4B end_value;
        FieldVec4B start_tangent;
        FieldVec4B end_tangent;
        float start_key;
        float end_key;
        float key_span;

        /**
         * @brief Evaluate the segment at a key; Lib implements this.
         * @param key Evaluation key.
         * @return Value at the key.
         */
        FieldVec4B interpolate(float key) const;

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

/** 0x50-byte BootVectorSegmentBase with vtable D_1710C0 in main data. */
class BootVectorSegment : public BootVectorSegmentBase
{
    public:
        /**
         * @brief Evaluate the segment at a key.
         * @param key Evaluation key.
         * @return Value at the key.
         */
        virtual FieldVec4B evaluate(float key) const;
};

/** 48-byte vector keyframe of BootVectorCurveTrackBase: a BootVectorTrackBase keyframe and two auxiliary vectors. */
struct BootVectorCurveTrackKey : public BootVectorTrackKey
{
    /** @brief Leave the vectors uninitialized. */
    BootVectorCurveTrackKey()
    {
    }

    FieldVec4B in_tangent;
    FieldVec4B out_tangent;
};

/** Key storage for vector tracks whose keys carry a value and two tangent vectors (vtable D_1719E0 in main data). */
class BootVectorCurveTrackBase : public BootTrack
{
    public:
        /** @brief Construct the track. */
        BootVectorCurveTrackBase();

        /** @brief Destroy the track. */
        virtual ~BootVectorCurveTrackBase();

        /**
         * @brief Allocate storage for the requested keyframe count.
         * @param count Requested keyframe count.
         */
        virtual void allocate_keys(s32 count);

        /**
         * @brief Bind an external keyframe array.
         * @param count Keyframe count.
         * @param entries External keyframe storage.
         */
        virtual void bind_keys(s32 count, BootVectorCurveTrackKey* entries);

        /**
         * @brief Set what the track does before its first key.
         * @param value Mode value.
         */
        virtual void set_before_mode(u32 value);

        /**
         * @brief Set what the track does after its last key.
         * @param value Mode value.
         */
        virtual void set_after_mode(u32 value);

        /**
         * @brief Return how many key spans the last wrapped key was past the first key.
         * @return Signed cycle count.
         */
        virtual s32 get_cycle_count() const;

        /**
         * @brief Append a vector keyframe.
         * @param value Keyframe value.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         * @param key Sort key.
         * @return Append status.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         */
        virtual s32 append_key(const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent, float key);

        /** @brief Slot 0x24; BootTrack's empty version (track_default_func_slot24) is the only one. */
        virtual void func_slot24();

        /**
         * @brief Replace an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         * @return Replacement status.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         */
        virtual s32 replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent);

        /**
         * @brief Insert an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         * @return Insertion status.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         */
        virtual s32 insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent);

        /**
         * @brief Read an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Receives the sort key.
         * @param value Receives the value.
         * @param first Receives the first auxiliary vector.
         * @param second Receives the second auxiliary vector.
         * @return Nonzero when the keyframe is available.
         */
        virtual s32 read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        /**
         * @brief Add a vector keyframe through the track implementation.
         * @param value Keyframe value.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         * @param key Sort key.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         */
        virtual void set_single_key(const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent, float key);

        /** @brief Run the default update hook. */
        virtual void reset_keys();

        /**
         * @brief Test whether the track contains the supplied key.
         * @param key Key to find.
         * @return Nonzero when the key exists.
         */
        virtual s32 has_key(float key) const;

        /**
         * @brief Return the difference between the last and first key values.
         * @param output Receives the difference.
         */
        virtual void get_end_delta(FieldVec4B* output) const = 0;

        /**
         * @brief Wrap a key into the stored key range.
         * @param key Key to wrap.
         * @return Wrapped key.
         */
        virtual float wrap_key(float key) const;

        /**
         * @brief Return how fast the value changed at the last sample, per second.
         * @param output Receives the rate.
         */
        virtual void get_value_rate(FieldVec4B* output) const = 0;

        /**
         * @brief Return the span between the first and last keys.
         * @return Key span, or zero when fewer than two keys are stored.
         */
        virtual float get_key_span() const;

        /**
         * @brief Evaluate the vector track at a key.
         * @param key Evaluation key.
         * @param output Receives the evaluated vector.
         */
        virtual void evaluate(float key, FieldVec4B* output);

        /**
         * @brief Return the stored keyframe count.
         * @return Keyframe count.
         */
        virtual s16 get_key_count() const;

        /** @brief Return a pooled track or delete an ordinary track. */
        virtual void release();

        /**
         * @brief Return the key storage.
         * @return Key array, or null.
         */
        virtual BootVectorCurveTrackKey* get_keys();

        /** @brief Reset the sequence fields and set both modes to one. */
        virtual void reset_state();

        /**
         * @brief Return the number of keys the storage can hold.
         * @return Key capacity.
         */
        virtual s16 get_key_capacity();

        /**
         * @brief Handle a vector set with a key; the base implementation ignores it.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @param key Key the keyframe sits at.
         * @return Handler result.
         */
        virtual s32 on_append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /**
         * @brief Handle an indexed vector set with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @return Handler result.
         */
        virtual s32 on_replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Handle an indexed vector set with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @return Handler result.
         */
        virtual s32 on_insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Handle a vector set with a key; the base implementation ignores it.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @param key Key the keyframe sits at.
         */
        virtual void on_set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /**
         * @brief Return a zero vector.
         * @return Zero vector.
         */
        virtual FieldVec4A get_zero_value() const;

        /**
         * @brief Return the value of the keyframe with the supplied key.
         * @param key Key to find.
         * @return Keyframe value, or zero when the key is absent.
         */
        virtual FieldVec4A find_key_value(float key);

        /**
         * @brief Sample the track at a key and cache the value and its change per second.
         * @param key Key to sample at.
         * @return Value at the key.
         */
        virtual FieldVec4A sample(float key) = 0;

        /**
         * @brief Append a key with its tangents.
         * @param value Key value.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         * @param key Key.
         * @return Nonzero when the key was stored.
         */
        virtual s32 append_curve_key(const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent, float key) = 0;

        /** @brief Delete the key storage unless it is external, and clear the key pointer. */
        void free_keys();

        /**
         * @brief Normalize a key across the cached span and store its signed period count.
         * @param key Key whose period count is representable as a signed 32-bit integer.
         * @return Normalized key, with odd-period reflection selected by the control fields.
         */
        float update_cycle_count(float key);

        /**
         * @brief Find the entries around a key, starting from the cached cursor.
         * @param key Key to place.
         * @param lower Receives the lower entry index.
         * @param upper Receives the upper entry index.
         * @return One when the active end mode extends the first or last segment, otherwise zero.
         */
        u8 find_surrounding_keys(float key, s32* lower, s32* upper);

        void* key_array;
        u8 unk08[8];

        /** Single cached keyframe, used before an array is allocated. */
        BootVectorCurveTrackKey single_key;

        BootSequenceTail state;
        u8 unk54[0xC];
};

/** Vector curve track that stores and samples its keys (vtable D_1710D0 in main data). */
class BootVectorCurveTrack : public BootVectorCurveTrackBase
{
    public:
        /** @brief Destroy the track. */
        virtual ~BootVectorCurveTrack()
        {
        }

        // Overrides of the base slots of the same names.
        virtual s32 append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        virtual s32 replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
        virtual s32 insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
        virtual s32 read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;
        virtual void set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);
        virtual void reset_keys();
        virtual void get_end_delta(FieldVec4B* output) const;
        virtual void get_value_rate(FieldVec4B* output) const;
        virtual void reset_state();
        virtual FieldVec4A sample(float key);
        virtual s32 append_curve_key(const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent, float key);

        /**
         * @brief Replace an indexed keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         * @return Nonzero when the keyframe was stored.
         */
        virtual s32 replace_curve_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent);

        /**
         * @brief Insert a keyframe at an index.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         * @return Nonzero when the keyframe was stored.
         */
        virtual s32 insert_curve_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent);

        /**
         * @brief Store a single keyframe in the cached vectors.
         * @param value Keyframe value.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key. auxiliary vector.
         * @param key Key.
         */
        virtual void set_single_curve_key(const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent, float key);

        BootVectorSegment curve_segment;
        FieldVec4B last_value;
        FieldVec4B value_rate;
};

/** 0xD0-byte vector curve track allocated from a BootTrackPool (vtable D_1711D0 in main data). */
class BootPooledVectorCurveTrack : public BootVectorCurveTrack
{
    public:
        /** @brief Construct the track. */
        BootPooledVectorCurveTrack();

        /** @brief Destroy the track. */
        virtual ~BootPooledVectorCurveTrack();

        // Overrides of the base slots of the same names.
        virtual void release();

        /** @brief Free the keys and give the track back to its pool. */
        virtual void return_to_pool();
};

/** 32-byte keyframe of BootFloatQuaternionTrackBase: a key and a rotation quaternion at offset 0x10. */
struct BootFloatQuaternionTrackKey
{
    /** @brief Leave the keyframe uninitialized. */
    BootFloatQuaternionTrackKey();

    float key;
    u8 unk04[0xC];

    /** Rotation quaternion (x, y, z, w). */
    float value[4];
};

/**
 * Key storage for rotation tracks with full float quaternions (vtable D_171A70 in main data); its constructor and
 * destructor are out of line. Lib's sampler slerps between neighbouring keys.
 */
class BootFloatQuaternionTrackBase : public BootTrack
{
    public:
        /** @brief Construct the track. */
        BootFloatQuaternionTrackBase();

        /** @brief Destroy the track. */
        virtual ~BootFloatQuaternionTrackBase();

        /**
         * @brief Allocate storage for the requested keyframe count.
         * @param count Requested keyframe count.
         */
        virtual void allocate_keys(s32 count);

        /**
         * @brief Bind an external keyframe array.
         * @param count Keyframe count.
         * @param entries External keyframe storage.
         */
        virtual void bind_keys(s32 count, BootFloatQuaternionTrackKey* entries);

        /**
         * @brief Set what the track does before its first key.
         * @param value Mode value.
         */
        virtual void set_before_mode(u32 value);

        /**
         * @brief Set what the track does after its last key.
         * @param value Mode value.
         */
        virtual void set_after_mode(u32 value);

        /**
         * @brief Return how many key spans the last wrapped key was past the first key.
         * @return Signed cycle count.
         */
        virtual s32 get_cycle_count() const;

        /**
         * @brief Append a vector keyframe.
         * @param value Keyframe value.
         * @param first Optional first auxiliary vector.
         * @param second Optional second auxiliary vector.
         * @param key Sort key.
         * @return Append status.
         */
        virtual s32 append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Slot 0x24; BootTrack's empty version (track_default_func_slot24) is the only one. */
        virtual void func_slot24();

        /**
         * @brief Replace an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @param first Optional first auxiliary vector.
         * @param second Optional second auxiliary vector.
         * @return Replacement status.
         */
        virtual s32 replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Insert an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @param first Optional first auxiliary vector.
         * @param second Optional second auxiliary vector.
         * @return Insertion status.
         */
        virtual s32 insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Read an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Receives the sort key.
         * @param value Receives the value.
         * @param first Receives the first auxiliary vector.
         * @param second Receives the second auxiliary vector.
         * @return Nonzero when the keyframe is available.
         */
        virtual s32 read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        /**
         * @brief Add a vector keyframe through the track implementation.
         * @param value Keyframe value.
         * @param first Optional first auxiliary vector.
         * @param second Optional second auxiliary vector.
         * @param key Sort key.
         * @param second Second auxiliary vector.
         */
        virtual void set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Run the default update hook. */
        virtual void reset_keys();

        /**
         * @brief Test whether the track contains the supplied key.
         * @param key Key to find.
         * @return Nonzero when the key exists.
         */
        virtual s32 has_key(float key) const;

        /**
         * @brief Return the difference between the last and first key values.
         * @param output Receives the difference.
         */
        virtual void get_end_delta(FieldVec4B* output) const = 0;

        /**
         * @brief Wrap a key into the stored key range.
         * @param key Key to wrap.
         * @return Wrapped key.
         */
        virtual float wrap_key(float key) const;

        /**
         * @brief Return how fast the value changed at the last sample, per second.
         * @param output Receives the rate.
         */
        virtual void get_value_rate(FieldVec4B* output) const = 0;

        /**
         * @brief Return the span between the first and last keys.
         * @return Key span, or zero when fewer than two keys are stored.
         */
        virtual float get_key_span() const;

        /**
         * @brief Evaluate the vector track at a key.
         * @param key Evaluation key.
         * @param output Receives the evaluated vector.
         */
        virtual void evaluate(float key, FieldVec4B* output) const;

        /**
         * @brief Return the stored keyframe count.
         * @return Keyframe count.
         */
        virtual s16 get_key_count() const;

        /** @brief Return a pooled track or delete an ordinary track. */
        virtual void release();

        /**
         * @brief Return the key storage.
         * @return Key array, or null.
         */
        virtual BootFloatQuaternionTrackKey* get_keys();

        /** @brief Clear the key storage, counts, modes and cached indices. */
        virtual void reset_state();

        /**
         * @brief Return the number of keys the storage can hold.
         * @return Key capacity.
         */
        virtual s16 get_key_capacity();

        /**
         * @brief Handle a vector set with a key; the base implementation ignores it.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @param key Key the keyframe sits at.
         * @return Handler result.
         */
        virtual s32 on_append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /**
         * @brief Handle an indexed vector set with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @return Handler result.
         */
        virtual s32 on_replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Handle an indexed vector set with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @return Handler result.
         */
        virtual s32 on_insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Handle a vector set with a key; the base implementation ignores it.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @param key Key the keyframe sits at.
         */
        virtual void on_set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /**
         * @brief Return a zero vector.
         * @return Zero vector.
         */
        virtual FieldVec4A get_zero_value() const;

        /**
         * @brief Return the value of the keyframe with the supplied key.
         * @param key Key to find.
         * @return Keyframe value, or zero when the key is absent.
         */
        virtual FieldVec4A find_key_value(float key);

        /**
         * @brief Sample the track at a key and cache the value and its change per second.
         * @param key Key to sample at.
         * @return Value at the key.
         */
        virtual FieldVec4A sample(float key) const = 0;

        /** @brief Free the keys and give the track back to its pool; pooled tracks implement it. */
        virtual void return_to_pool() = 0;

        /** @brief Delete the key storage unless it is external, and clear the key pointer. */
        void free_keys();

        BootFloatQuaternionTrackKey* key_array;
        u8 unk08[0x28];
        BootSequenceTail state;
};

/** 0x80-byte float quaternion track allocated from a BootTrackPool, with the Lib vtable D_177BE0. */
class BootPooledFloatQuaternionTrack : public BootFloatQuaternionTrackBase
{
    public:
        /** @brief Construct the track. */
        BootPooledFloatQuaternionTrack();

        /** @brief Destroy the track. */
        virtual ~BootPooledFloatQuaternionTrack();

        // Boot uses the Lib implementations of these.
        virtual void get_end_delta(FieldVec4B* output) const;

        virtual void get_value_rate(FieldVec4B* output) const;
        virtual FieldVec4A sample(float key) const;
        virtual void return_to_pool();

        u8 unk44[0x3C];
};

/** 48-byte keyframe of BootQuaternionCurveTrackBase: a key, a rotation quaternion and its squad control quaternion. */
struct BootQuaternionCurveTrackKey
{
    /** @brief Leave the keyframe uninitialized. */
    BootQuaternionCurveTrackKey();

    float key;
    u8 unk04[0xC];

    /** Rotation quaternion (x, y, z, w). */
    float value[4];

    /** Inner control quaternion that squad blends through between this key and the next. */
    float control[4];
};

/**
 * Key storage for smooth rotation tracks (vtable D_171680 in main data); its constructor and destructor are out
 * of line. Each key carries a control quaternion, and Lib's sampler interpolates with squad.
 */
class BootQuaternionCurveTrackBase : public BootTrack
{
    public:
        /** @brief Construct the track. */
        BootQuaternionCurveTrackBase();

        /** @brief Destroy the track. */
        virtual ~BootQuaternionCurveTrackBase();

        /**
         * @brief Allocate storage for the requested keyframe count.
         * @param count Requested keyframe count.
         */
        virtual void allocate_keys(s32 count);

        /**
         * @brief Bind an external keyframe array.
         * @param count Keyframe count.
         * @param entries External keyframe storage.
         */
        virtual void bind_keys(s32 count, BootQuaternionCurveTrackKey* entries);

        /**
         * @brief Set what the track does before its first key.
         * @param value Mode value.
         */
        virtual void set_before_mode(u32 value);

        /**
         * @brief Set what the track does after its last key.
         * @param value Mode value.
         */
        virtual void set_after_mode(u32 value);

        /**
         * @brief Return how many key spans the last wrapped key was past the first key.
         * @return Signed cycle count.
         */
        virtual s32 get_cycle_count() const;

        /**
         * @brief Append a vector keyframe.
         * @param value Keyframe value.
         * @param first Optional first auxiliary vector.
         * @param second Optional second auxiliary vector.
         * @param key Sort key.
         * @return Append status.
         */
        virtual s32 append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Slot 0x24; BootTrack's empty version (track_default_func_slot24) is the only one. */
        virtual void func_slot24();

        /**
         * @brief Replace an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @param first Optional first auxiliary vector.
         * @param second Optional second auxiliary vector.
         * @return Replacement status.
         */
        virtual s32 replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Insert an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @param first Optional first auxiliary vector.
         * @param second Optional second auxiliary vector.
         * @return Insertion status.
         */
        virtual s32 insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Read an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Receives the sort key.
         * @param value Receives the value.
         * @param first Receives the first auxiliary vector.
         * @param second Receives the second auxiliary vector.
         * @return Nonzero when the keyframe is available.
         */
        virtual s32 read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        /**
         * @brief Add a vector keyframe through the track implementation.
         * @param value Keyframe value.
         * @param first Optional first auxiliary vector.
         * @param second Optional second auxiliary vector.
         * @param key Sort key.
         * @param second Second auxiliary vector.
         */
        virtual void set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Run the default update hook. */
        virtual void reset_keys();

        /**
         * @brief Test whether the track contains the supplied key.
         * @param key Key to find.
         * @return Nonzero when the key exists.
         */
        virtual s32 has_key(float key) const;

        /**
         * @brief Return the difference between the last and first key values.
         * @param output Receives the difference.
         */
        virtual void get_end_delta(FieldVec4B* output) const = 0;

        /**
         * @brief Wrap a key into the stored key range.
         * @param key Key to wrap.
         * @return Wrapped key.
         */
        virtual float wrap_key(float key) const;

        /**
         * @brief Return how fast the value changed at the last sample, per second.
         * @param output Receives the rate.
         */
        virtual void get_value_rate(FieldVec4B* output) const = 0;

        /**
         * @brief Return the span between the first and last keys.
         * @return Key span, or zero when fewer than two keys are stored.
         */
        virtual float get_key_span() const;

        /**
         * @brief Evaluate the vector track at a key.
         * @param key Evaluation key.
         * @param output Receives the evaluated vector.
         */
        virtual void evaluate(float key, FieldVec4B* output) const;

        /**
         * @brief Return the stored keyframe count.
         * @return Keyframe count.
         */
        virtual s16 get_key_count() const;

        /** @brief Return a pooled track or delete an ordinary track. */
        virtual void release();

        /**
         * @brief Return the key storage.
         * @return Key array, or null.
         */
        virtual BootQuaternionCurveTrackKey* get_keys();

        /** @brief Clear the key storage, counts, modes and cached indices. */
        virtual void reset_state();

        /**
         * @brief Return the number of keys the storage can hold.
         * @return Key capacity.
         */
        virtual s16 get_key_capacity();

        /**
         * @brief Handle a vector set with a key; the base implementation ignores it.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @param key Key the keyframe sits at.
         * @return Handler result.
         */
        virtual s32 on_append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /**
         * @brief Handle an indexed vector set with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @return Handler result.
         */
        virtual s32 on_replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Handle an indexed vector set with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @return Handler result.
         */
        virtual s32 on_insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Handle a vector set with a key; the base implementation ignores it.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @param key Key the keyframe sits at.
         */
        virtual void on_set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /**
         * @brief Return a zero vector.
         * @return Zero vector.
         */
        virtual FieldVec4A get_zero_value() const;

        /**
         * @brief Return the value of the keyframe with the supplied key.
         * @param key Key to find.
         * @return Keyframe value, or zero when the key is absent.
         */
        virtual FieldVec4A find_key_value(float key);

        /**
         * @brief Sample the track at a key and cache the value and its change per second.
         * @param key Key to sample at.
         * @return Value at the key.
         */
        virtual FieldVec4A sample(float key) const = 0;

        /** @brief Free the keys and give the track back to its pool; pooled tracks implement it. */
        virtual void return_to_pool() = 0;

        /** @brief Delete the key storage unless it is external, and clear the key pointer. */
        void free_keys();

        BootQuaternionCurveTrackKey* key_array;
        u8 unk08[0x38];
        BootSequenceTail state;
};

/** 0x90-byte quaternion curve track allocated from a BootTrackPool, with the Lib vtable D_174440. */
class BootPooledQuaternionCurveTrack : public BootQuaternionCurveTrackBase
{
    public:
        /** @brief Construct the track. */
        BootPooledQuaternionCurveTrack();

        /** @brief Destroy the track. */
        virtual ~BootPooledQuaternionCurveTrack();

        // Boot uses the Lib implementations of these.
        virtual void get_end_delta(FieldVec4B* output) const;

        virtual void get_value_rate(FieldVec4B* output) const;
        virtual FieldVec4A sample(float key) const;
        virtual void return_to_pool();

        u8 unk54[0x3C];
};

/** 8-byte packed keyframe of BootQuaternionTrackBase: three halfword values and a halfword key. */
struct BootQuaternionTrackKey
{
    /**
     * @brief Copy the values and key.
     * @param entry Entry to copy.
     * @return This entry.
     */
    BootQuaternionTrackKey& operator=(const BootQuaternionTrackKey& entry)
    {
        packed_rotation[0] = entry.packed_rotation[0];
        packed_rotation[1] = entry.packed_rotation[1];
        packed_rotation[2] = entry.packed_rotation[2];
        key = entry.key;
        return *this;
    }

    /** Rotation as the quaternion's x, y and z in 1.15 fixed point; w is rebuilt from them. */
    s16 packed_rotation[3];

    s16 key;
};

/** Key storage for rotation tracks with quaternions packed as three halfwords (vtable D_171710 in main data). */
class BootQuaternionTrackBase : public BootTrack
{
    public:
        /** @brief Construct the track. */
        BootQuaternionTrackBase();

        /** @brief Destroy the track. */
        virtual ~BootQuaternionTrackBase();

        /**
         * @brief Allocate storage for the requested keyframe count.
         * @param count Requested keyframe count.
         */
        virtual void allocate_keys(s32 count);

        /**
         * @brief Bind an external keyframe array.
         * @param count Keyframe count.
         * @param entries External keyframe storage.
         */
        virtual void bind_keys(s32 count, BootQuaternionTrackKey* entries);

        /**
         * @brief Set what the track does before its first key.
         * @param value Mode value.
         */
        virtual void set_before_mode(u32 value);

        /**
         * @brief Set what the track does after its last key.
         * @param value Mode value.
         */
        virtual void set_after_mode(u32 value);

        /**
         * @brief Return how many key spans the last wrapped key was past the first key.
         * @return Signed cycle count.
         */
        virtual s32 get_cycle_count() const;

        /**
         * @brief Append a vector keyframe.
         * @param value Keyframe value.
         * @param first Optional first auxiliary vector.
         * @param second Optional second auxiliary vector.
         * @param key Sort key.
         * @return Append status.
         */
        virtual s32 append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Slot 0x24; BootTrack's empty version (track_default_func_slot24) is the only one. */
        virtual void func_slot24();

        /**
         * @brief Replace an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @param first Optional first auxiliary vector.
         * @param second Optional second auxiliary vector.
         * @return Replacement status.
         */
        virtual s32 replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Insert an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @param first Optional first auxiliary vector.
         * @param second Optional second auxiliary vector.
         * @return Insertion status.
         */
        virtual s32 insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Read an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Receives the sort key.
         * @param value Receives the value.
         * @param first Receives the first auxiliary vector.
         * @param second Receives the second auxiliary vector.
         * @return Nonzero when the keyframe is available.
         */
        virtual s32 read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        /**
         * @brief Add a vector keyframe through the track implementation.
         * @param value Keyframe value.
         * @param first Optional first auxiliary vector.
         * @param second Optional second auxiliary vector.
         * @param key Sort key.
         * @param second Second auxiliary vector.
         */
        virtual void set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Run the default update hook. */
        virtual void reset_keys();

        /**
         * @brief Test whether the track contains the supplied key.
         * @param key Key to find.
         * @return Nonzero when the key exists.
         */
        virtual s32 has_key(float key) const;

        /**
         * @brief Return the difference between the last and first key values.
         * @param output Receives the difference.
         */
        virtual void get_end_delta(FieldVec4B* output) const = 0;

        /**
         * @brief Wrap a key into the stored key range.
         * @param key Key to wrap.
         * @return Wrapped key.
         */
        virtual float wrap_key(float key) const;

        /**
         * @brief Return how fast the value changed at the last sample, per second.
         * @param output Receives the rate.
         */
        virtual void get_value_rate(FieldVec4B* output) const = 0;

        /**
         * @brief Return the span between the first and last keys.
         * @return Key span, or zero when fewer than two keys are stored.
         */
        virtual float get_key_span() const;

        /**
         * @brief Evaluate the vector track at a key.
         * @param key Evaluation key.
         * @param output Receives the evaluated vector.
         */
        virtual void evaluate(float key, FieldVec4B* output) const;

        /**
         * @brief Return the stored keyframe count.
         * @return Keyframe count.
         */
        virtual s16 get_key_count() const;

        /** @brief Return a pooled track or delete an ordinary track. */
        virtual void release();

        /**
         * @brief Return the key storage.
         * @return Key array, or null.
         */
        virtual BootQuaternionTrackKey* get_keys();

        /** @brief Clear the key storage, counts, modes and cached indices. */
        virtual void reset_state();

        /**
         * @brief Return the number of keys the storage can hold.
         * @return Key capacity.
         */
        virtual s16 get_key_capacity();

        /**
         * @brief Handle a vector set with a key; the base implementation ignores it.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @param key Key the keyframe sits at.
         * @return Handler result.
         */
        virtual s32 on_append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /**
         * @brief Handle an indexed vector set with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @return Handler result.
         */
        virtual s32 on_replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Handle an indexed vector set with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @return Handler result.
         */
        virtual s32 on_insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Handle a vector set with a key; the base implementation ignores it.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @param key Key the keyframe sits at.
         */
        virtual void on_set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /**
         * @brief Return a zero vector.
         * @return Zero vector.
         */
        virtual FieldVec4A get_zero_value() const;

        /**
         * @brief Return the value of the keyframe with the supplied key.
         * @param key Key to find.
         * @return Keyframe value, or zero when the key is absent.
         */
        virtual FieldVec4A find_key_value(float key) const;

        /**
         * @brief Sample the track at a key and cache the value and its change per second.
         * @param key Key to sample at.
         * @return Value at the key.
         */
        virtual FieldVec4A sample(float key) const = 0;

        /** @brief Free the keys and give the track back to its pool; pooled tracks implement it. */
        virtual void return_to_pool() = 0;

        /** @brief Delete the key storage unless it is external, and clear the key pointer. */
        void free_keys();

        BootQuaternionTrackKey* key_array;
        u8 unk08[8];
        BootSequenceTail state;
};

/** 0x2C-byte quaternion track allocated from a BootTrackPool, with the Lib vtable D_1730F0. */
class BootPooledQuaternionTrack : public BootQuaternionTrackBase
{
    public:
        /** @brief Construct the track. */
        BootPooledQuaternionTrack();

        /** @brief Destroy the track. */
        virtual ~BootPooledQuaternionTrack();

        // Boot uses the Lib implementations of these.
        virtual void get_end_delta(FieldVec4B* output) const;

        virtual void get_value_rate(FieldVec4B* output) const;
        virtual FieldVec4A sample(float key) const;
        virtual void return_to_pool();

        u8 unk24[8];
};

s32 float_track_pool_allocate(BootTrackPool<BootPooledFloatTrack>* pool, s32 count);

void float_track_pool_release(BootTrackPool<BootPooledFloatTrack>* pool);

s32 vector_track_pool_allocate(BootTrackPool<BootPooledVectorTrack>* pool, s32 count);

void vector_track_pool_release(BootTrackPool<BootPooledVectorTrack>* pool);

s32 track_1718C0_pool_allocate(BootTrackPool<BootClass177EE0>* pool, s32 count);

void track_1718C0_pool_release(BootTrackPool<BootClass177EE0>* pool);

s32 float_curve_track_pool_allocate(BootTrackPool<BootPooledFloatCurveTrack>* pool, s32 count);

void float_curve_track_pool_release(BootTrackPool<BootPooledFloatCurveTrack>* pool);

s32 vector_curve_track_pool_allocate(BootTrackPool<BootPooledVectorCurveTrack>* pool, s32 count);

void vector_curve_track_pool_release(BootTrackPool<BootPooledVectorCurveTrack>* pool);

s32 float_quaternion_track_pool_allocate(BootTrackPool<BootPooledFloatQuaternionTrack>* pool, s32 count);

void float_quaternion_track_pool_release(BootTrackPool<BootPooledFloatQuaternionTrack>* pool);

s32 quaternion_curve_track_pool_allocate(BootTrackPool<BootPooledQuaternionCurveTrack>* pool, s32 count);

void quaternion_curve_track_pool_release(BootTrackPool<BootPooledQuaternionCurveTrack>* pool);

s32 quaternion_track_pool_allocate(BootTrackPool<BootPooledQuaternionTrack>* pool, s32 count);

void quaternion_track_pool_release(BootTrackPool<BootPooledQuaternionTrack>* pool);

class FieldVec4A;
class BootPooledVectorTrack;
class BootPooledVectorCurveTrack;
class BootQuaternionTrackBase;

/**
 * @brief BootTrack's slot 0x24, between append_key and replace_key; every family inherits it and none overrides it, so
 * its purpose is unknown. It does nothing, as Lib's copy (0x429850) does.
 * @param track Track; unused.
 */
void track_default_func_slot24(void* track);

/**
 * @brief BootTrack's append_key (slot 0x20), which the families' base classes inherit; it does nothing.
 * @param track Track; unused.
 * @return Zero.
 */
s32 track_default_append_key(void* track);

/**
 * @brief BootTrack's replace_key (slot 0x28), which the families' base classes inherit; it does nothing.
 * @param track Track; unused.
 * @return Zero.
 */
s32 track_default_replace_key(void* track);

/**
 * @brief BootTrack's insert_key (slot 0x2C), which the families' base classes inherit; it does nothing.
 * @param track Track; unused.
 * @return Zero.
 */
s32 track_default_insert_key(void* track);

/**
 * @brief BootTrack's read_key (slot 0x30), which the families' base classes inherit; it does nothing.
 * @param track Track; unused.
 * @return Zero.
 */
s32 track_default_read_key(void* track);

/**
 * @brief BootTrack's set_single_key (slot 0x34), which the families' base classes inherit; it does nothing.
 * @param track Track; unused.
 */
void track_default_set_single_key(void* track);

/**
 * @brief BootTrack's reset_keys (slot 0x38), which the families' base classes inherit; it does nothing.
 * @param track Track; unused.
 */
void track_default_reset_keys(void* track);

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
 * @brief BootQuaternionTrackBase's find_key_value (slot 0x7C): find the keyframe with a key and decode its rotation.
 * @param out Receives the rotation, or zero when the key is absent.
 * @param track Track to search.
 * @param key Key to find.
 */
void quaternion_track_find_key_value(FieldVec4A* out, BootQuaternionTrackBase* track, float key);

#endif
