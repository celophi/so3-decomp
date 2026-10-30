#include "include_asm.h"
#include "clamp.h"
#include "vu0.h"
#include "overlays/lib/vector.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/boot/text_001EEC80.h"
#include "overlays/boot/resident.h"

extern "C" {

FieldVec4B func_4B1640(const BootVectorSegmentBase* range, float key);
extern BootTrackPool<BootPooledVectorCurveTrack>* g_vector_curve_track_pool;
float func_4B16C0(void* segment, float key);
extern BootTrackPool<BootPooledVectorTrack>* g_vector_track_pool;
extern float D_001B668C;
}

typedef struct FieldF32At050
{
    u8 pad[0x50];
    float value;
} FieldF32At050;

typedef struct FieldF32At04C
{
    u8 pad[0x4C];
    float value;
} FieldF32At04C;

/**
 * @brief Evaluate a vector range at a key.
 * @param range Range to evaluate.
 * @param key Evaluation key.
 * @return Evaluated vector.
 */
FieldVec4B vector_segment_evaluate(const BootVectorSegmentBase* range, float key)
{
    return func_4B1640(range, key);
}

/**
 * @brief Run the default track hook.
 * @param object Object to use.
 */
void func_001EECA0(void* object)
{
}

/** @brief Delete the track; pooled tracks override this to return to their pool. */
void BootFloatCurveTrackBase::release()
{
    delete this;
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EED30(void* track)
{
    return 0;
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EED40(void* track)
{
    return 0;
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EED50(void* track)
{
    return 0;
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EED60(void* track)
{
    return 0;
}

/**
 * @brief Perform no work.
 * @param track Receiver or first argument; unused.
 */
void func_001EED70(void* track)
{
}

/**
 * @brief Perform no work.
 * @param track Receiver or first argument; unused.
 */
void func_001EED80(void* track)
{
}

/** @brief Return a pooled track to its pool, or delete an ordinary track. */
void BootPooledVectorCurveTrack::release()
{
    if (this != 0)
    {
        if (state.pooled)
        {
            return_to_pool();
        }
        else
        {
            delete this;
        }
    }
}

/**
 * @brief Free a pooled track's keys and give the track back to its pool.
 * @param track Pooled track.
 */
void vector_curve_track_return_to_pool(BootPooledVectorCurveTrack* track)
{
    vector_curve_track_free_keys(track);
    vector_curve_track_pool_free(g_vector_curve_track_pool, track);
}

/**
 * @brief Evaluate a float curve segment at a key.
 * @param segment Segment to evaluate.
 * @param key Key to evaluate at.
 * @return Value at the key.
 */
float float_segment_evaluate(void* segment, float key)
{
    return func_4B16C0(segment, key);
}

/** @brief Return a pooled track to its pool, or delete an ordinary track. */
void BootPooledVectorTrack::release()
{
    if (this != 0)
    {
        if (state.pooled)
        {
            return_to_pool();
        }
        else
        {
            delete this;
        }
    }
}

/**
 * @brief Free a pooled track's keys and give the track back to its pool.
 * @param track Pooled track.
 */
void vector_track_return_to_pool(BootPooledVectorTrack* track)
{
    vector_track_free_keys(track);
    vector_track_pool_free(g_vector_track_pool, track);
}

struct ResetVectorB0_001ED4E0
{
    u8 pad[0xB0];
    FieldVec4B value;
};

/** Clear the last sampled value, then reset the key state. */
void vector_curve_track_reset_sampling(void* track)
{
    ((ResetVectorB0_001ED4E0*)track)->value = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    vector_curve_track_reset_state((BootVectorCurveTrackState*)track);
}

/**
 * @brief Subtract the first three components of one vector from another.
 * @param left Vector to subtract from.
 * @param right Vector to subtract.
 * @return left minus right, keeping left's fourth component.
 */
static inline FieldVec4B difference(const FieldVec4B& left, const FieldVec4B& right)
{
    FieldVec4B value(left);
    value.x -= right.x;
    value.y -= right.y;
    value.z -= right.z;
    return value;
}

/**
 * @brief Scale all four components of a vector.
 * @param scale Factor to multiply by.
 * @param vector Vector to scale.
 * @return The scaled vector.
 */
static inline FieldVec4B scaled(float scale, const FieldVec4B& vector)
{
    FieldVec4B value(vector);
    return value *= scale;
}

/**
 * @brief Add the first three components of two vectors.
 * @param left First vector.
 * @param right Vector to add.
 * @return left plus right, keeping left's fourth component.
 */
static inline FieldVec4B sum(const FieldVec4B& left, const FieldVec4B& right)
{
    FieldVec4B value(left);
    value.x += right.x;
    value.y += right.y;
    value.z += right.z;
    return value;
}

/**
 * @brief Return a vector track's last keyframe.
 * @param track Track with at least one keyframe.
 * @return The last keyframe.
 */
static inline BootVectorCurveTrackKey& last_entry(BootVectorCurveTrackBase* track)
{
    return static_cast<BootVectorCurveTrackKey*>(track->key_array)[track->state.key_count - 1];
}

/**
 * @brief Return a keyframe's key.
 * @param entry Keyframe.
 * @return The key, stored in the value's fourth component.
 */
static inline float key_of(const BootVectorCurveTrackKey* entry)
{
    return entry->value.w;
}

/**
 * @brief Evaluate the track at a key, extrapolating past either end, and cache the value and its change per frame.
 * @param key Evaluation key.
 * @return Evaluated vector.
 */
FieldVec4A BootVectorCurveTrack::sample(float key)
{
    s32 lower;
    s32 upper;
    float wrapped_key;
    u8 extrapolate;
    FieldVec4B result;

    if (!key_array || !state.key_count)
    {
        return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    }

    if (state.unk0c >= state.key_capacity)
    {
        state.unk0c = 0;
    }

    if (state.key_count == 1 && (!(key < static_cast<BootVectorCurveTrackKey*>(key_array)[0].value.w) || state.before_mode != 6))
    {
        return *reinterpret_cast<FieldVec4A*>(&static_cast<BootVectorCurveTrackKey*>(key_array)[0].value);
    }

    extrapolate = 0;

    if (key < static_cast<BootVectorCurveTrackKey*>(key_array)[0].value.w && state.before_mode == 6)
    {
        upper = 0;
        wrapped_key = key;
        lower = -1;
    }
    else
    {
        wrapped_key = vector_curve_track_update_cycle_count(reinterpret_cast<BootVectorCurveTrackState*>(this), key);

        if (state.cycle_count)
        {
            if (state.before_mode == 0 && state.cycle_count < 0)
            {
                return *reinterpret_cast<FieldVec4A*>(&static_cast<BootVectorCurveTrackKey*>(key_array)[0].value);
            }

            if (state.after_mode == 0 && state.cycle_count > 0)
            {
                return *reinterpret_cast<FieldVec4A*>(&static_cast<BootVectorCurveTrackKey*>(key_array)[state.key_count - 1].value);
            }
        }

        extrapolate = vector_curve_track_find_surrounding_keys(this, wrapped_key, &lower, &upper);

        if (extrapolate)
        {
            wrapped_key = key;
        }
    }

    if (!extrapolate)
    {
        if (state.unk0e != lower || state.cached_index != upper)
        {
            state.unk0e = lower;
            state.cached_index = upper;
            BootVectorCurveTrackKey* first =
                lower >= 0 ? static_cast<BootVectorCurveTrackKey*>(key_array) + lower : reinterpret_cast<BootVectorCurveTrackKey*>(&unk10);
            s32 last = state.key_count - 1;

            if (upper == last && ((!(key < static_cast<BootVectorCurveTrackKey*>(key_array)[0].value.w) && state.after_mode == 2) ||
                                  (key < static_cast<BootVectorCurveTrackKey*>(key_array)[0].value.w && state.before_mode == 2)))
            {
                BootVectorCurveTrackKey* entries = static_cast<BootVectorCurveTrackKey*>(key_array);
                BootVectorCurveTrackKey* second = entries + upper;
                curve_segment.set_endpoints(first->value.w, second->value.w, reinterpret_cast<const FieldVec4A*>(&first->value),
                                            reinterpret_cast<const FieldVec4A*>(&first->out_tangent), reinterpret_cast<const FieldVec4A*>(&entries[0].value),
                                            reinterpret_cast<const FieldVec4A*>(&entries[0].in_tangent));
            }
            else if (lower < upper)
            {
                BootVectorCurveTrackKey* second = static_cast<BootVectorCurveTrackKey*>(key_array) + upper;
                curve_segment.set_endpoints(first->value.w, second->value.w, reinterpret_cast<const FieldVec4A*>(&first->value),
                                            reinterpret_cast<const FieldVec4A*>(&first->out_tangent), reinterpret_cast<const FieldVec4A*>(&second->value),
                                            reinterpret_cast<const FieldVec4A*>(&second->in_tangent));
            }
            else
            {
                BootVectorCurveTrackKey* second = static_cast<BootVectorCurveTrackKey*>(key_array) + last;
                curve_segment.set_endpoints(first->value.w, second->value.w, reinterpret_cast<const FieldVec4A*>(&first->value),
                                            reinterpret_cast<const FieldVec4A*>(&first->out_tangent), reinterpret_cast<const FieldVec4A*>(&second->value),
                                            reinterpret_cast<const FieldVec4A*>(&second->in_tangent));
            }
        }

        result = func_4B1640(&curve_segment, wrapped_key);

        if (state.cycle_count && ((state.before_mode == 5 && state.cycle_count < 0) || (state.after_mode == 5 && state.cycle_count > 0)))
        {
            FieldVec4B delta = difference(static_cast<BootVectorCurveTrackKey*>(key_array)[state.key_count - 1].value,
                                          static_cast<BootVectorCurveTrackKey*>(key_array)[0].value);
            result += scaled((float)state.cycle_count, delta);
        }
    }
    else
    {
        FieldVec4B slope;

        if (wrapped_key < key)
        {
            slope = scaled(1.0f / (last_entry(this).value.w - key_of(static_cast<BootVectorCurveTrackKey*>(key_array) + (state.key_count - 2))),
                           static_cast<BootVectorCurveTrackKey*>(key_array)[state.key_count - 1].in_tangent);
            result = sum(static_cast<BootVectorCurveTrackKey*>(key_array)[state.key_count - 1].value, scaled(key - last_entry(this).value.w, slope));
        }
        else
        {
            slope = scaled(1.0f / (key_of(static_cast<BootVectorCurveTrackKey*>(key_array) + 1) - key_of(static_cast<BootVectorCurveTrackKey*>(key_array))),
                           static_cast<BootVectorCurveTrackKey*>(key_array)[0].out_tangent);
            result = sum(static_cast<BootVectorCurveTrackKey*>(key_array)[0].value,
                         scaled(key - static_cast<BootVectorCurveTrackKey*>(key_array)[0].value.w, slope));
        }
    }

    value_rate = scaled(D_001B668C, difference(result, last_value));
    last_value = result;
    return *reinterpret_cast<FieldVec4A*>(&result);
}

/**
 * @brief Append a keyframe.
 * @param value Keyframe value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Sort key.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootVectorCurveTrack::append_curve_key(const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent, float key)
{
    if (key_array == 0)
    {
        return 0;
    }

    if (state.key_count >= state.key_capacity)
    {
        return 0;
    }

    static_cast<BootVectorCurveTrackKey*>(key_array)[state.key_count].value = *value;
    static_cast<BootVectorCurveTrackKey*>(key_array)[state.key_count].in_tangent = *in_tangent;
    static_cast<BootVectorCurveTrackKey*>(key_array)[state.key_count].out_tangent = *out_tangent;
    static_cast<BootVectorCurveTrackKey*>(key_array)[state.key_count].value.w = key;
    state.span = key - static_cast<BootVectorCurveTrackKey*>(key_array)[0].value.w;
    state.key_count++;
    return 1;
}

/**
 * @brief Subtract the first three components.
 * @param left Vector to subtract from.
 * @param right Vector to subtract.
 * @return Difference, keeping the left vector's fourth component.
 */
static inline FieldVec4A sequence_difference(const FieldVec4B& left, const FieldVec4B& right)
{
    FieldVec4A value;
    *(unsigned __int128*)&value = *(const unsigned __int128*)&left;
    value.x -= right.x;
    value.y -= right.y;
    value.z -= right.z;
    return value;
}

/**
 * @brief Return a vector, or a zeroed fallback when it is missing.
 * @param vector Optional vector.
 * @param zero Storage for the zero vector.
 * @return The vector, or zero after clearing it.
 */
static inline const FieldVec4A* track_vector(const FieldVec4A* vector, FieldVec4A* zero)
{
    if (!vector)
    {
        zero->x = 0.0f;
        zero->y = 0.0f;
        zero->z = 0.0f;
        zero->w = 0.0f;
        return zero;
    }

    return vector;
}

/**
 * @brief Append a keyframe, using zero vectors for missing auxiliary vectors.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootVectorCurveTrack::append_key(const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent, float key)
{
    FieldVec4A zero_first;
    FieldVec4A zero_second;
    out_tangent = track_vector(out_tangent, &zero_second);
    in_tangent = track_vector(in_tangent, &zero_first);
    return append_curve_key(value, in_tangent, out_tangent, key);
}

/**
 * @brief Replace an indexed keyframe.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootVectorCurveTrack::replace_curve_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent)
{
    if (key_array == 0)
    {
        return 0;
    }

    if (index >= state.key_capacity)
    {
        return 0;
    }

    static_cast<BootVectorCurveTrackKey*>(key_array)[index].value = *value;
    static_cast<BootVectorCurveTrackKey*>(key_array)[index].in_tangent = *in_tangent;
    static_cast<BootVectorCurveTrackKey*>(key_array)[index].out_tangent = *out_tangent;
    static_cast<BootVectorCurveTrackKey*>(key_array)[index].value.w = key;

    if (index == state.key_count - 1)
    {
        state.span = key - static_cast<BootVectorCurveTrackKey*>(key_array)[0].value.w;
    }

    return 1;
}

/**
 * @brief Replace an indexed keyframe, using zero vectors for missing auxiliary vectors.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootVectorCurveTrack::replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent)
{
    FieldVec4A zero_first;
    FieldVec4A zero_second;
    out_tangent = track_vector(out_tangent, &zero_second);
    in_tangent = track_vector(in_tangent, &zero_first);
    return replace_curve_key(index, key, value, in_tangent, out_tangent);
}

/**
 * @brief Insert a keyframe, using zero vectors for missing auxiliary vectors.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootVectorCurveTrack::insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent)
{
    FieldVec4A zero_first;
    FieldVec4A zero_second;
    out_tangent = track_vector(out_tangent, &zero_second);
    in_tangent = track_vector(in_tangent, &zero_first);
    return insert_curve_key(index, key, value, in_tangent, out_tangent);
}

/**
 * @brief Store a single keyframe, using zero vectors for missing auxiliary vectors.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key the keyframe sits at.
 */
void BootVectorCurveTrack::set_single_key(const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent, float key)
{
    FieldVec4A zero_first;
    FieldVec4A zero_second;
    out_tangent = track_vector(out_tangent, &zero_second);
    in_tangent = track_vector(in_tangent, &zero_first);
    set_single_curve_key(value, in_tangent, out_tangent, key);
}

/**
 * @brief Read an indexed keyframe.
 * @param index Keyframe index.
 * @param key Receives the sort key.
 * @param value Receives the value.
 * @param first Receives the first auxiliary vector.
 * @param second Receives the second auxiliary vector.
 * @return One when the index is within the capacity, otherwise zero.
 */
s32 BootVectorCurveTrack::read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const
{
    if (key_array == 0)
    {
        return 0;
    }

    if (index >= state.key_capacity)
    {
        return 0;
    }

    if (key)
    {
        *key = static_cast<const BootVectorCurveTrackKey*>(key_array)[index].value.w;
    }

    if (value)
    {
        *value = static_cast<const BootVectorCurveTrackKey*>(key_array)[index].value;
    }

    if (first)
    {
        *first = static_cast<const BootVectorCurveTrackKey*>(key_array)[index].in_tangent;
    }

    if (second)
    {
        *second = static_cast<const BootVectorCurveTrackKey*>(key_array)[index].out_tangent;
    }

    return 1;
}

/** @brief Reset to a single zero keyframe at key zero. */
void BootVectorCurveTrack::reset_keys()
{
    FieldVec4A zero(0.0f, 0.0f, 0.0f, 0.0f);
    set_single_key(&zero, &zero, &zero, 0.0f);
}

/**
 * @brief Return how fast the value changed at the last sample, per second.
 * @param track Track to read.
 * @param output Receives the rate.
 */
void vector_curve_track_get_value_rate(const BootVectorCurveTrack* track, FieldVec4B* output)
{
    *output = *reinterpret_cast<const FieldVec4A*>(&track->value_rate);
}

/**
 * @brief Return the difference between the endpoint vectors.
 * @param output Receives the difference.
 */
void BootVectorCurveTrack::get_end_delta(FieldVec4B* output) const
{
    if (key_array != 0)
    {
        *output = sequence_difference(static_cast<const BootVectorCurveTrackKey*>(key_array)[state.key_count - 1].value,
                                      static_cast<const BootVectorCurveTrackKey*>(key_array)[0].value);
    }
}

/**
 * @brief Clear the last sampled value, then reset the key state.
 * @param track Track to reset.
 */
void float_curve_track_reset_sampling(BootFloatCurveTrack* track)
{
    track->last_value = 0.0f;
    float_curve_track_reset_state(reinterpret_cast<BootFloatCurveTrackState*>(track));
}

/**
 * @brief Append an entry, using zero for missing components.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootFloatCurveTrack::append_key(const float* value, const float* in_tangent, const float* out_tangent, float key)
{
    float y_value;
    float z_value;
    z_value = (out_tangent == 0) ? 0.0f : *out_tangent;
    out_tangent = &z_value;
    y_value = (in_tangent == 0) ? 0.0f : *in_tangent;
    in_tangent = &y_value;
    return append_curve_key(value, in_tangent, out_tangent, key);
}

/**
 * @brief Replace an indexed entry, using zero for missing components.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootFloatCurveTrack::replace_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent)
{
    float y_value;
    float z_value;
    z_value = (out_tangent == 0) ? 0.0f : *out_tangent;
    out_tangent = &z_value;
    y_value = (in_tangent == 0) ? 0.0f : *in_tangent;
    in_tangent = &y_value;
    return replace_curve_key(index, key, value, in_tangent, out_tangent);
}

/**
 * @brief Insert an entry, using zero for missing components.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootFloatCurveTrack::insert_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent)
{
    float y_value;
    float z_value;
    z_value = (out_tangent == 0) ? 0.0f : *out_tangent;
    out_tangent = &z_value;
    y_value = (in_tangent == 0) ? 0.0f : *in_tangent;
    in_tangent = &y_value;
    return insert_curve_key(index, key, value, in_tangent, out_tangent);
}

/**
 * @brief Store a single entry, using zero for missing components.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key the keyframe sits at.
 */
void BootFloatCurveTrack::set_single_key(const float* value, const float* in_tangent, const float* out_tangent, float key)
{
    float y_value;
    float z_value;
    z_value = (out_tangent == 0) ? 0.0f : *out_tangent;
    out_tangent = &z_value;
    y_value = (in_tangent == 0) ? 0.0f : *in_tangent;
    in_tangent = &y_value;
    set_single_curve_key(value, in_tangent, out_tangent, key);
}

/** @brief Reset to a single zero keyframe at key zero. */
void BootFloatCurveTrack::reset_keys()
{
    float zero = 0.0f;
    set_single_key(&zero, &zero, &zero, 0.0f);
}

/**
 * @brief Return how fast the value changed at the last sample, per second.
 * @param track Track to read.
 * @param value Receives the rate.
 */
void float_curve_track_get_value_rate(void* track, float* value)
{
    *value = ((FieldF32At050*)track)->value;
}

/**
 * @brief Write the difference between the last and first float values in a sixteen-byte record array.
 * @param track Object containing the array pointer and count.
 * @param result Destination for the difference; unchanged if the array is absent.
 */
void float_curve_track_get_end_delta(void* track, float* result)
{
    float* values = *(float**)((u8*)track + 4);

    if (values != 0)
    {
        s16 count = *(s16*)((u8*)track + 0x20);
        *result = values[count * 4 - 3] - values[1];
    }
}

/** @brief Install the vtable; the range is left unset. */
BootVectorSegmentBase::BootVectorSegmentBase()
{
}

/**
 * @brief Set the segment from the keys, values and tangents at its two ends.
 * @param from_key Key the segment starts at.
 * @param to_key Key the segment ends at.
 * @param from_value Value at the start key.
 * @param from_tangent Tangent at the start key.
 * @param to_value Value at the end key.
 * @param to_tangent Tangent at the end key.
 */
void BootVectorSegmentBase::set_endpoints(float from_key, float to_key, const FieldVec4A* from_value, const FieldVec4A* from_tangent,
                                          const FieldVec4A* to_value, const FieldVec4A* to_tangent)
{
    start_value = *from_value;
    start_key = from_key;
    start_tangent = *from_tangent;
    end_value = *to_value;
    end_key = to_key;
    end_tangent = *to_tangent;
    key_span = to_key - from_key;

    if (key_span == 0.0f)
    {
        key_span = 1.0f;
    }
}

/** @brief Install the vtable; the range is left unset. */
BootFloatSegmentBase::BootFloatSegmentBase()
{
}

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
                                 const float* end_tangent, float start_key, float end_key)
{
    segment->start_value = *start_value;
    segment->start_key = start_key;
    segment->start_tangent = *start_tangent;
    segment->end_value = *end_value;
    segment->end_key = end_key;
    segment->end_tangent = *end_tangent;
    segment->key_span = end_key - start_key;

    if (segment->key_span == 0.0f)
    {
        segment->key_span = 1.0f;
    }
}

struct ResetVector90_001ED4E0
{
    u8 pad[0x90];
    FieldVec4B value;
};

/** Clear the last sampled value, then reset the key state. */
void vector_track_reset_sampling(void* track)
{
    ((ResetVector90_001ED4E0*)track)->value = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    vector_track_reset_state((BootVectorTrackState*)track);
}

/**
 * @brief Evaluate the track at a key and cache the value and its change per frame.
 * @param key Evaluation key.
 * @return Evaluated vector.
 */
FieldVec4A BootVectorTrack::sample(float key)
{
    s32 lower;
    s32 upper;
    float wrapped_key;
    u8 extrapolate;

    if (!key_array || !state.key_count)
    {
        return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    }

    if (state.unk0c >= state.key_capacity)
    {
        state.unk0c = 0;
    }

    if (state.key_count == 1 && (!(key < key_array[0].value.w) || state.before_mode != 6))
    {
        return *reinterpret_cast<FieldVec4A*>(&key_array[0].value);
    }

    if (key < key_array[0].value.w && state.before_mode == 6)
    {
        upper = 0;
        wrapped_key = key;
        lower = -1;
    }
    else
    {
        wrapped_key = vector_track_update_cycle_count(reinterpret_cast<BootVectorTrackState*>(this), key);

        if (state.before_mode == 0 && state.cycle_count < 0)
        {
            return *reinterpret_cast<FieldVec4A*>(&key_array[0].value);
        }

        if (state.after_mode == 0 && state.cycle_count > 0)
        {
            return *reinterpret_cast<FieldVec4A*>(&key_array[state.key_count - 1].value);
        }

        extrapolate = vector_track_find_surrounding_keys(this, wrapped_key, &lower, &upper);

        if (extrapolate)
        {
            wrapped_key = key;
        }
    }

    if (state.unk0e != lower || state.cached_index != upper)
    {
        state.unk0e = lower;
        state.cached_index = upper;
        BootVectorTrackKey* first = lower >= 0 ? key_array + lower : reinterpret_cast<BootVectorTrackKey*>(&unk10);
        vector_history_reset(&sample_history);
        sample_history.push_sample(first->value.w, reinterpret_cast<const FieldVec4A*>(&first->value));
        s32 last = state.key_count - 1;
        // TODO: My guess; copying upper into its own local is the only way I found that matches.
        s32 upper_index = upper;

        if (upper_index == last && ((!(key < key_array[0].value.w) && state.after_mode == 2) || (key < key_array[0].value.w && state.before_mode == 2)))
        {
            BootVectorTrackKey* entries = key_array;
            BootVectorTrackKey* second = entries + upper_index;
            sample_history.push_sample(second->value.w, reinterpret_cast<const FieldVec4A*>(&entries[0].value));
        }
        else if (lower < upper_index)
        {
            BootVectorTrackKey* second = key_array + upper_index;
            sample_history.push_sample(second->value.w, reinterpret_cast<const FieldVec4A*>(&second->value));
        }
        else
        {
            BootVectorTrackKey* second = key_array + last;
            sample_history.push_sample(second->value.w, reinterpret_cast<const FieldVec4A*>(&key_array[upper_index].value));
        }
    }

    FieldVec4B result = sample_history.sample(wrapped_key);

    if ((state.before_mode == 5 && state.cycle_count < 0) || (state.after_mode == 5 && state.cycle_count > 0))
    {
        FieldVec4B delta = difference(key_array[state.key_count - 1].value, key_array[0].value);
        result += scaled((float)state.cycle_count, delta);
    }

    value_rate = scaled(1.0f / D_001B6688, difference(result, last_value));
    last_value = result;
    return *reinterpret_cast<FieldVec4A*>(&result);
}

/**
 * @brief Return the difference between the endpoint values.
 * @param output Receives the difference.
 */
void BootVectorTrack::get_end_delta(FieldVec4B* output) const
{
    if (key_array != 0)
    {
        *output = sequence_difference(static_cast<const BootVectorTrackKey*>(key_array)[state.key_count - 1].value,
                                      static_cast<const BootVectorTrackKey*>(key_array)[0].value);
    }
}

/**
 * @brief Return how fast the value changed at the last sample, per second.
 * @param track Track to read.
 * @param output Receives the rate.
 */
void vector_track_get_value_rate(const BootVectorTrack* track, FieldVec4B* output)
{
    *output = *reinterpret_cast<const FieldVec4A*>(&track->value_rate);
}

/** @brief Clear the last sampled value, then reset the key state. */
void BootFloatTrack::reset_state()
{
    last_value = 0.0f;
    BootFloatTrackBase::reset_state();
}

/**
 * @brief Write the difference between the last and first float values in an eight-byte record array.
 * @param track Object containing the array pointer and count.
 * @param result Destination for the difference; unchanged if the array is absent.
 */
void float_track_get_end_delta(void* track, float* result)
{
    float* values = *(float**)((u8*)track + 4);

    if (values != 0)
    {
        s16 count = *(s16*)((u8*)track + 0x18);
        *result = values[count * 2 - 1] - values[1];
    }
}

/**
 * @brief Return how fast the value changed at the last sample, per second.
 * @param track Track to read.
 * @param value Receives the rate.
 */
void float_track_get_value_rate(void* track, float* value)
{
    *value = ((FieldF32At04C*)track)->value;
}

/** @brief Reset the record and clear its vector. */
BootClass171B70::BootClass171B70()
{
    unk00 = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/** @brief Reset the record and clear its vector. */
BootVectorHistory::BootVectorHistory()
{
    unk00 = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Store a value and key in the two-entry history and count it, up to two.
 * @param key Key to store.
 * @param value Value to store.
 */
void BootVectorHistory::push_sample(float key, const FieldVec4A* value)
{
    unk20[next_index] = *value;
    unk40[next_index] = key;

    if (++next_index >= 2)
    {
        next_index = 0;
    }

    if (++sample_count > 2)
    {
        sample_count = 2;
    }
}

/** @brief Reset the record and clear its first word. */
BootFloatHistory::BootFloatHistory()
{
    unk00 = 0;
}

/** @brief Reset the record. */
BootClass171B20::BootClass171B20()
{
    history_171B20_reset(this);
}

/**
 * @brief Forget the stored samples.
 * @param history History to clear.
 */
void history_171B20_reset(BootClass171B20* history)
{
    history->sample_count = 0;
    history->next_index = 0;
    history->unk14 = 0;
    history->unk18 = 0;
}

/** @brief Reset the record. */
BootVectorHistoryBase::BootVectorHistoryBase()
{
    vector_history_reset(this);
}

/**
 * @brief Forget the stored samples.
 * @param history History to clear.
 */
void vector_history_reset(BootVectorHistoryBase* history)
{
    history->sample_count = 0;
    history->next_index = 0;
    history->unk14 = 0;
    history->unk18 = 0;
}

/** @brief Reset the record. */
BootFloatHistoryBase::BootFloatHistoryBase()
{
    float_history_reset(this);
}

/**
 * @brief Forget the stored samples.
 * @param history History to clear.
 */
void float_history_reset(BootFloatHistoryBase* history)
{
    history->sample_count = 0;
    history->next_index = 0;
    history->unk08 = 0;
    history->unk0C = 0;
}

/**
 * @brief Append a keyframe.
 * @param value Keyframe value.
 * @param key Sort key.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootVectorKeyTrack::on_append_key(const FieldVec4A* value, float key)
{
    if (key_array == 0)
    {
        return 0;
    }

    if (state.key_count >= state.key_capacity)
    {
        return 0;
    }

    static_cast<BootVectorTrackKey*>(key_array)[state.key_count].value = *value;
    static_cast<BootVectorTrackKey*>(key_array)[state.key_count].value.w = key;
    state.span = key - static_cast<BootVectorTrackKey*>(key_array)[0].value.w;
    state.unk0e = -1;
    state.cached_index = -1;
    state.key_count++;
    return 1;
}

/**
 * @brief Replace an indexed keyframe.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootVectorKeyTrack::on_replace_key(s32 index, float key, const FieldVec4A* value)
{
    if (key_array == 0)
    {
        return 0;
    }

    if (index >= state.key_capacity)
    {
        return 0;
    }

    static_cast<BootVectorTrackKey*>(key_array)[index].value = *value;
    static_cast<BootVectorTrackKey*>(key_array)[index].value.w = key;

    if (index == state.key_count - 1)
    {
        state.span = key - static_cast<BootVectorTrackKey*>(key_array)[0].value.w;
    }

    state.unk0e = -1;
    state.cached_index = -1;
    return 1;
}

/**
 * @brief Read an indexed keyframe.
 * @param index Keyframe index.
 * @param key Receives the sort key.
 * @param value Receives the value.
 * @param first Unused; this track has no auxiliary vectors.
 * @param second Unused; this track has no auxiliary vectors.
 * @return One when the index is within the capacity, otherwise zero.
 */
s32 BootVectorKeyTrack::read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const
{
    if (key_array == 0)
    {
        return 0;
    }

    if (index >= state.key_capacity)
    {
        return 0;
    }

    if (key)
    {
        *key = static_cast<const BootVectorTrackKey*>(key_array)[index].value.w;
    }

    if (value)
    {
        *value = static_cast<const BootVectorTrackKey*>(key_array)[index].value;
    }

    return 1;
}

/** @brief Release the keyframe storage. */
BootClass171A70::~BootClass171A70()
{
    track_171A70_free_keys(this);
}

/**
 * @brief Release owned record-array storage and clear the array pointer.
 * @param track Receiver whose packed ownership flag distinguishes external storage.
 */
void track_171A70_free_keys(BootClass171A70* track)
{
    if (!track->state.external_keys)
    {
        delete[] track->key_array;
    }

    track->key_array = 0;
}

/**
 * @brief Normalize a key across the cached span and store its signed period count.
 * @param track Receiver with 48-byte records and a nonzero cached key span.
 * @param key Key whose period count is representable as a signed 32-bit integer.
 * @return Normalized key, with odd-period reflection selected by the control fields.
 */
float vector_curve_track_update_cycle_count(BootVectorCurveTrackState* track, float key)
{
    float first = track->entries[0].key;
    float quotient = (key - first) / track->span;

    if (key < first)
    {
        quotient -= 1.0f;
    }

    track->cycle_count = quotient;

    if (track->cycle_count)
    {
        float result = key - (float)track->cycle_count * track->span;

        if ((track->before_mode == 3 && track->cycle_count < 0) || (track->after_mode == 3 && track->cycle_count > 0))
        {
            s32 last_index = track->count - 1;
            BootVectorCurveStateKey* last_entry = track->entries + last_index;
            float last = last_entry->key;

            if (track->cycle_count & 1)
            {
                result = first + (last - result);
            }
        }

        return result;
    }

    return key;
}

/**
 * @brief Find the entries around a key, starting from the cached cursor.
 * @param track Track to search.
 * @param key Key to place.
 * @param lower Receives the lower entry index.
 * @param upper Receives the upper entry index.
 * @return One when a reflecting end mode extends the first or last segment, otherwise zero.
 */
u8 vector_curve_track_find_surrounding_keys(BootVectorCurveTrackBase* track, float key, s32* lower, s32* upper)
{
    s32 index;
    s32 count;
    s32 next;

    if (track->state.repeats)
    {
        if (track->state.before_mode == 4 && track->state.cycle_count < 0)
        {
            *lower = 0;
            *upper = 1;
            track->state.unk0c = 0;
            return 1;
        }

        if (track->state.after_mode == 4 && track->state.cycle_count > 0)
        {
            *lower = track->state.key_count - 2;
            *upper = track->state.key_count - 1;
            track->state.unk0c = track->state.key_count - 2;
            return 1;
        }
    }

    index = track->state.unk0c;
    count = track->state.key_count;

    while (index > 0 && key < static_cast<BootVectorCurveTrackKey*>(track->key_array)[index].value.w)
    {
        index--;
    }

    index = clamp_low(index, 0);

    while ((next = index + 1) < count && !(key < static_cast<BootVectorCurveTrackKey*>(track->key_array)[next].value.w))
    {
        index++;
    }

    if (index >= count - 1)
    {
        *lower = count - 2;
        *upper = count - 1;
    }
    else
    {
        *lower = index;
        *upper = index + 1;
    }

    track->state.unk0c = index;
    return 0;
}
/** @brief Release the keyframe storage. */
BootVectorCurveTrackBase::~BootVectorCurveTrackBase()
{
    vector_curve_track_free_keys(this);
}

/**
 * @brief Reset 48-byte record storage, counts, packed controls, and cached indices.
 * @param track Receiver to reset without releasing its current storage.
 */
void vector_curve_track_reset_state(BootVectorCurveTrackState* track)
{
    track->entries = 0;
    track->before_mode = 1;
    track->after_mode = 1;
    track->capacity = 0;
    track->count = 0;
    track->unk4C = -1;
    track->cycle_count = 0;
    track->unk4E = -1;
    track->cached_index = -1;
    track->repeats = 0;
    track->external_keys = 0;
}

/**
 * @brief Bind external 48-byte records and cache their first-to-last key span.
 * @param track Array receiver.
 * @param count Positive entry count representable in the receiver count fields.
 * @param entries External storage containing the specified number of entries.
 */
void vector_curve_track_bind_keys(BootVectorCurveTrackState* track, s32 count, BootVectorCurveStateKey* entries)
{
    s32 last_index = count - 1;
    BootVectorCurveStateKey* last;
    track->external_keys = 1;
    track->entries = entries;
    track->capacity = count;
    track->count = count;
    last = track->entries + last_index;
    track->span = last->key - track->entries[0].key;
}

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param value Value to store, truncated to four bits.
 */
void BootVectorCurveTrackBase::set_before_mode(u32 value)
{
    state.before_mode = value;
    state.repeats = state.before_mode == 4 || state.after_mode == 4;
}

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param value Value to store, truncated to four bits.
 */
void BootVectorCurveTrackBase::set_after_mode(u32 value)
{
    state.after_mode = value;
    state.repeats = state.before_mode == 4 || state.after_mode == 4;
}

/**
 * @brief Return how many key spans the last wrapped key was past the first key.
 * @return Signed cycle count.
 */
s32 BootVectorCurveTrackBase::get_cycle_count() const
{
    return state.cycle_count;
}

/**
 * @brief Return the number of stored keys.
 * @return Key count.
 */
s16 BootVectorCurveTrackBase::get_key_count() const
{
    return state.key_count;
}

/**
 * @brief Return the number of keys the storage can hold.
 * @return Key capacity.
 */
s16 BootVectorCurveTrackBase::get_key_capacity()
{
    return state.key_capacity;
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 vector_curve_track_on_append_key(void* track)
{
    return 0;
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 vector_curve_track_on_replace_key(void* track)
{
    return 0;
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 vector_curve_track_on_insert_key(void* track)
{
    return 0;
}

/**
 * @brief Perform no work.
 * @param track Receiver or first argument; unused.
 */
void vector_curve_track_on_set_single_key(void* track)
{
}

/**
 * @brief Test whether the 48-byte record array contains an exactly equal key.
 * @param track Receiver with valid storage when its count is positive.
 * @param key Scalar key to find.
 * @return One for an equal key, or zero when none is present.
 */
s32 vector_curve_track_has_key(BootVectorCurveTrackState* track, float key)
{
    s32 index;

    for (index = 0; index < track->count; index++)
    {
        if (key == track->entries[index].key)
        {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Write a zero value; the track's value when it has no keys.
 * @param result Receives the zero value.
 */
void vector_curve_track_get_zero_value(u32* result)
{
    result[0] = 0;
    result[1] = 0;
    result[2] = 0;
    result[3] = 0;
}

/**
 * @brief Return the last-to-first key difference, or zero below two records.
 * @param track Receiver with valid storage when its count is at least two.
 * @return Difference between the last and first scalar keys, or zero.
 */
float vector_curve_track_get_key_span(BootVectorCurveTrackState* track)
{
    s32 last_index;
    BootVectorCurveStateKey* last_entry;

    if (track->count < 2)
    {
        return 0.0f;
    }

    last_index = track->count - 1;
    last_entry = track->entries + last_index;
    return last_entry->key - track->entries[0].key;
}

/**
 * @brief Read the vector value associated with the first exactly equal key.
 * @param track Receiver with 48-byte records, valid when its count is positive.
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A vector_curve_track_find_key_value(BootVectorCurveTrackState* track, float key)
{
    s32 index;

    for (index = 0; index < track->count; index++)
    {
        if (key == track->entries[index].key)
        {
            BootVectorCurveStateKey* entry = track->entries + index;
            return *reinterpret_cast<const FieldVec4A*>(entry->value);
        }
    }

    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void BootVectorCurveTrackBase::evaluate(float key, FieldVec4B* output)
{
    *output = sample(key);
}

/**
 * @brief Adjust a scalar key by whole spans determined from the endpoint records.
 * @param track Receiver with positive count, valid storage, and distinct endpoint keys.
 * @param key Scalar key whose normalized span quotient must fit in a signed word.
 * @return Key minus the computed number of endpoint spans, or the key for zero spans.
 */
float vector_curve_track_wrap_key(BootVectorCurveTrackState* track, float key)
{
    s32 last_index = track->count - 1;
    BootVectorCurveStateKey* entries = track->entries;
    BootVectorCurveStateKey* last = entries + last_index;
    float first = entries[0].key;
    float span = last->key - first;
    float quotient = (key - first) / span;
    s32 periods;

    if (quotient < 0.0f)
    {
        quotient -= 1.0f;
    }

    periods = quotient;

    if (periods != 0)
    {
        return key - (float)periods * span;
    }

    return key;
}

/**
 * @brief Return the key storage.
 * @param track Track to read.
 * @return Key array, or null.
 */
BootVectorCurveStateKey* vector_curve_track_get_keys(const BootVectorCurveTrackState* track)
{
    return track->entries;
}

/**
 * @brief Release owned record-array storage and clear the array pointer.
 * @param track Receiver whose packed ownership flag distinguishes external storage.
 */
void vector_curve_track_free_keys(BootVectorCurveTrackBase* track)
{
    if (!track->state.external_keys)
    {
        delete[] static_cast<BootVectorCurveTrackKey*>(track->key_array);
    }

    track->key_array = 0;
}

/** @brief Release the keyframe storage. */
BootFloatCurveTrackBase::~BootFloatCurveTrackBase()
{
    float_curve_track_free_keys(this);
}

/**
 * @brief Reset array storage, counts, packed controls, and cached indices.
 * @param track Receiver to reset without releasing its current storage.
 */
void float_curve_track_reset_state(BootFloatCurveTrackState* track)
{
    track->entries = 0;
    track->before_mode = 1;
    track->after_mode = 1;
    track->capacity = 0;
    track->count = 0;
    track->unk24 = -1;
    track->cycle_count = 0;
    track->unk26 = -1;
    track->cached_index = -1;
    track->repeats = 0;
    track->external_keys = 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param count Requested keyframe count.
 */
void BootFloatCurveTrackBase::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] key_array;
    key_array = new (0) BootFloatCurveTrackKey[count];
    state.key_capacity = count;

    if (!key_array)
    {
        state.key_capacity = 0;
    }
}

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param value Value to store, truncated to four bits.
 */
void BootFloatCurveTrackBase::set_before_mode(u32 value)
{
    state.before_mode = value;
    state.repeats = state.before_mode == 4 || state.after_mode == 4;
}

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param value Value to store, truncated to four bits.
 */
void BootFloatCurveTrackBase::set_after_mode(u32 value)
{
    state.after_mode = value;
    state.repeats = state.before_mode == 4 || state.after_mode == 4;
}

/**
 * @brief Return how many key spans the last wrapped key was past the first key.
 * @return Signed cycle count.
 */
s32 BootFloatCurveTrackBase::get_cycle_count() const
{
    return state.cycle_count;
}

/**
 * @brief Return the number of stored keys.
 * @return Key count.
 */
s16 BootFloatCurveTrackBase::get_key_count() const
{
    return state.key_count;
}

/**
 * @brief Return the number of keys the storage can hold.
 * @return Key capacity.
 */
s16 BootFloatCurveTrackBase::get_key_capacity() const
{
    return state.key_capacity;
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 float_curve_track_on_append_key(void* track)
{
    return 0;
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 float_curve_track_on_replace_key(void* track)
{
    return 0;
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 float_curve_track_on_insert_key(void* track)
{
    return 0;
}

/**
 * @brief Perform no work.
 * @param track Receiver or first argument; unused.
 */
void float_curve_track_on_set_single_key(void* track)
{
}

/**
 * @brief Write a zero value; the track's value when it has no keys.
 * @param track Receives the zero value.
 * @return Zero.
 */
float float_curve_track_get_zero_value(void* track)
{
    return 0.0f;
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void BootFloatCurveTrackBase::evaluate(float key, float* output)
{
    *output = sample(key);
}

/**
 * @brief Return the key storage.
 * @return Key array, or null.
 */
BootFloatCurveTrackKey* BootFloatCurveTrackBase::get_keys() const
{
    return key_array;
}

/**
 * @brief Release owned array storage and clear the array pointer.
 * @param track Receiver whose packed ownership flag distinguishes external storage.
 */
void float_curve_track_free_keys(BootFloatCurveTrackBase* track)
{
    if (!track->state.external_keys)
    {
        delete[] track->key_array;
    }

    track->key_array = 0;
}

/** @brief Release the keyframe storage. */
BootClass1718C0::~BootClass1718C0()
{
    track_1718C0_free_keys(this);
}

/**
 * @brief Reset array storage, counts, packed controls, and cached indices.
 * @param track Receiver to reset without releasing its current storage.
 */
void track_1718C0_reset_state(BootState1F1580* track)
{
    track->entries = 0;
    track->before_mode = 1;
    track->after_mode = 1;
    track->capacity = 0;
    track->count = 0;
    track->unk3C = -1;
    track->cycle_count = 0;
    track->unk3E = -1;
    track->cached_index = -1;
    track->repeats = 0;
    track->external_keys = 0;
}

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param value Value to store, truncated to four bits.
 */
void BootClass1718C0::set_before_mode(u32 value)
{
    state.before_mode = value;
    state.repeats = state.before_mode == 4 || state.after_mode == 4;
}

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param value Value to store, truncated to four bits.
 */
void BootClass1718C0::set_after_mode(u32 value)
{
    state.after_mode = value;
    state.repeats = state.before_mode == 4 || state.after_mode == 4;
}

/**
 * @brief Return how many key spans the last wrapped key was past the first key.
 * @return Signed cycle count.
 */
s32 BootClass1718C0::get_cycle_count() const
{
    return state.cycle_count;
}

/**
 * @brief Return the number of stored keys.
 * @return Key count.
 */
s16 BootClass1718C0::get_key_count() const
{
    return state.key_count;
}

/**
 * @brief Return the number of keys the storage can hold.
 * @return Key capacity.
 */
s16 BootClass1718C0::get_key_capacity()
{
    return state.key_capacity;
}

/**
 * @brief Write a zero value; the track's value when it has no keys.
 * @param result Receives the zero value.
 */
void track_1718C0_get_zero_value(u32* result)
{
    result[0] = 0;
    result[1] = 0;
    result[2] = 0;
    result[3] = 0;
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void BootClass1718C0::evaluate(float key, FieldVec4B* output) const
{
    *output = sample(key);
}

/**
 * @brief Return the key storage.
 * @param track Track to read.
 * @return Key array, or null.
 */
BootKeyEntry32* track_1718C0_get_keys(const BootState1F1580* track)
{
    return track->entries;
}

/**
 * @brief Release owned array storage and clear the array pointer.
 * @param track Receiver whose packed ownership flag distinguishes external storage.
 */
void track_1718C0_free_keys(BootClass1718C0* track)
{
    if (!track->state.external_keys)
    {
        delete[] track->key_array;
    }

    track->key_array = 0;
}

/**
 * @brief Normalize a key across the cached span and store its signed period count.
 * @param track Receiver with vector-key records and a nonzero cached key span.
 * @param key Key whose period count is representable as a signed 32-bit integer.
 * @return Normalized key, with odd-period reflection selected by the control fields.
 */
float vector_track_update_cycle_count(BootVectorTrackState* track, float key)
{
    float first = track->entries[0].key;
    float quotient = (key - first) / track->span;

    if (key < first)
    {
        quotient -= 1.0f;
    }

    track->cycle_count = quotient;

    if (track->cycle_count)
    {
        float result = key - (float)track->cycle_count * track->span;

        if ((track->before_mode == 3 && track->cycle_count < 0) || (track->after_mode == 3 && track->cycle_count > 0))
        {
            s32 last_index = track->count - 1;
            BootVectorStateKey* last_entry = track->entries + last_index;
            float last = last_entry->key;

            if (track->cycle_count & 1)
            {
                result = first + (last - result);
            }
        }

        return result;
    }

    return key;
}

/**
 * @brief Find the entries around a key, starting from the cached cursor.
 * @param track Track to search.
 * @param key Key to place.
 * @param lower Receives the lower entry index.
 * @param upper Receives the upper entry index.
 * @return One when a reflecting end mode extends the first or last segment, otherwise zero.
 */
u8 vector_track_find_surrounding_keys(BootVectorTrackBase* track, float key, s32* lower, s32* upper)
{
    s32 index;
    s32 count;
    s32 next;

    if (track->state.repeats)
    {
        if (track->state.before_mode == 4 && track->state.cycle_count < 0)
        {
            *lower = 0;
            *upper = 1;
            track->state.unk0c = 0;
            return 1;
        }

        if (track->state.after_mode == 4 && track->state.cycle_count > 0)
        {
            *lower = track->state.key_count - 2;
            *upper = track->state.key_count - 1;
            track->state.unk0c = track->state.key_count - 2;
            return 1;
        }
    }

    index = track->state.unk0c;
    count = track->state.key_count;

    while (index > 0 && key < static_cast<BootVectorTrackKey*>(track->key_array)[index].value.w)
    {
        index--;
    }

    index = clamp_low(index, 0);

    while ((next = index + 1) < count && !(key < static_cast<BootVectorTrackKey*>(track->key_array)[next].value.w))
    {
        index++;
    }

    if (index >= count - 1)
    {
        *lower = count - 2;
        *upper = count - 1;
    }
    else
    {
        *lower = index;
        *upper = index + 1;
    }

    track->state.unk0c = index;
    return 0;
}
/** @brief Release the keyframe storage. */
BootVectorTrackBase::~BootVectorTrackBase()
{
    vector_track_free_keys(this);
}

/**
 * @brief Reset vector-key storage, counts, control fields, and cached indices.
 * @param track Array receiver to reset without releasing its current storage.
 */
void vector_track_reset_state(BootVectorTrackState* track)
{
    track->entries = 0;
    track->before_mode = 1;
    track->after_mode = 1;
    track->capacity = 0;
    track->count = 0;
    track->unk2C = -1;
    track->cycle_count = 0;
    track->unk2E = -1;
    track->cached_index = -1;
    track->repeats = 0;
    track->external_keys = 0;
}

/**
 * @brief Bind external vector-key storage and cache its first-to-last key span.
 * @param track Array receiver.
 * @param count Positive entry count representable in the receiver count fields.
 * @param entries External storage containing the specified number of entries.
 */
void vector_track_bind_keys(BootVectorTrackState* track, s32 count, BootVectorStateKey* entries)
{
    s32 last_index = count - 1;
    BootVectorStateKey* last;
    track->external_keys = 1;
    track->entries = entries;
    track->capacity = count;
    track->count = count;
    last = track->entries + last_index;
    track->span = last->key - track->entries[0].key;
}

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param value Value to store, truncated to four bits.
 */
void BootVectorTrackBase::set_before_mode(u32 value)
{
    state.before_mode = value;
    state.repeats = state.before_mode == 4 || state.after_mode == 4;
}

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param value Value to store, truncated to four bits.
 */
void BootVectorTrackBase::set_after_mode(u32 value)
{
    state.after_mode = value;
    state.repeats = state.before_mode == 4 || state.after_mode == 4;
}

/**
 * @brief Return how many key spans the last wrapped key was past the first key.
 * @return Signed cycle count.
 */
s32 BootVectorTrackBase::get_cycle_count() const
{
    return state.cycle_count;
}

/**
 * @brief Return the number of stored keys.
 * @return Key count.
 */
s16 BootVectorTrackBase::get_key_count() const
{
    return state.key_count;
}

/**
 * @brief Return the number of keys the storage can hold.
 * @return Key capacity.
 */
s16 BootVectorTrackBase::get_key_capacity()
{
    return state.key_capacity;
}

/**
 * @brief Test whether the vector-key array contains an exactly equal key.
 * @param track Receiver with valid storage when its count is positive.
 * @param key Key to find.
 * @return One if a key matches, or zero otherwise.
 */
s32 vector_track_has_key(BootVectorTrackState* track, float key)
{
    s32 index;

    for (index = 0; index < track->count; index++)
    {
        if (key == track->entries[index].key)
        {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Write a zero value; the track's value when it has no keys.
 * @param result Receives the zero value.
 */
void vector_track_get_zero_value(u32* result)
{
    result[0] = 0;
    result[1] = 0;
    result[2] = 0;
    result[3] = 0;
}

/**
 * @brief Compute the span between the last and first vector-entry keys.
 * @param track Receiver with valid storage when it has at least two entries.
 * @return Key span, or zero when fewer than two entries exist.
 */
float vector_track_get_key_span(BootVectorTrackState* track)
{
    BootVectorStateKey* last;

    if (track->count < 2)
    {
        return 0.0f;
    }

    last = track->entries + (track->count - 1);
    return last->key - track->entries[0].key;
}

/**
 * @brief Read the vector value associated with the first exactly equal key.
 * @param track Receiver with vector-key entries, valid when its count is positive.
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A vector_track_find_key_value(BootVectorTrackState* track, float key)
{
    s32 index;

    for (index = 0; index < track->count; index++)
    {
        if (key == track->entries[index].key)
        {
            BootVectorStateKey* entry = track->entries + index;
            return *reinterpret_cast<const FieldVec4A*>(entry);
        }
    }

    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void BootVectorTrackBase::evaluate(float key, FieldVec4B* output)
{
    *output = sample(key);
}

/**
 * @brief Wrap a key by the first-to-last vector-entry key span.
 * @param track Receiver with valid nonempty storage and a nonzero key span.
 * @param key Key to wrap using truncation after adjusting negative positions.
 * @return Key with the computed whole spans subtracted.
 */
float vector_track_wrap_key(BootVectorTrackState* track, float key)
{
    BootVectorStateKey* last = track->entries + (track->count - 1);
    float first = track->entries[0].key;
    float span = last->key - first;
    float position = (key - first) / span;
    s32 cycles;

    if (position < 0.0f)
    {
        position -= 1.0f;
    }

    cycles = (s32)position;

    if (cycles != 0)
    {
        return key - cycles * span;
    }

    return key;
}

/**
 * @brief Return the key storage.
 * @param track Track to read.
 * @return Key array, or null.
 */
BootVectorStateKey* vector_track_get_keys(const BootVectorTrackState* track)
{
    return track->entries;
}

/**
 * @brief Release owned array storage and clear the array pointer.
 * @param track Receiver whose packed ownership flag distinguishes external storage.
 */
void vector_track_free_keys(BootVectorTrackBase* track)
{
    if (!track->state.external_keys)
    {
        delete[] track->key_array;
    }

    track->key_array = 0;
}

/** @brief Release the keyframe storage. */
BootFloatTrackBase::~BootFloatTrackBase()
{
    float_track_free_keys(this);
}

/**
 * @brief Reset float-entry storage, counts, control fields, and cached indices.
 */
void BootFloatTrackBase::reset_state()
{
    key_array = 0;
    state.before_mode = 1;
    state.after_mode = 1;
    state.key_capacity = 0;
    state.key_count = 0;
    state.unk0c = -1;
    state.cycle_count = 0;
    state.unk0e = -1;
    state.cached_index = -1;
    state.repeats = 0;
    state.external_keys = 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param count Requested keyframe count.
 */
void BootFloatTrackBase::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] key_array;
    key_array = new (0) BootFloatTrackKey[count];
    state.key_capacity = count;

    if (!key_array)
    {
        state.key_capacity = 0;
    }
}

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param value Value to store, truncated to four bits.
 */
void BootFloatTrackBase::set_before_mode(u32 value)
{
    state.before_mode = value;
    state.repeats = state.before_mode == 4 || state.after_mode == 4;
}

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param value Value to store, truncated to four bits.
 */
void BootFloatTrackBase::set_after_mode(u32 value)
{
    state.after_mode = value;
    state.repeats = state.before_mode == 4 || state.after_mode == 4;
}

/**
 * @brief Return how many key spans the last wrapped key was past the first key.
 * @return Signed cycle count.
 */
s32 BootFloatTrackBase::get_cycle_count() const
{
    return state.cycle_count;
}

/**
 * @brief Return the number of stored keys.
 * @return Key count.
 */
s16 BootFloatTrackBase::get_key_count() const
{
    return state.key_count;
}

/**
 * @brief Return the number of keys the storage can hold.
 * @return Key capacity.
 */
s16 BootFloatTrackBase::get_key_capacity()
{
    return state.key_capacity;
}

/**
 * @brief Write a zero value; the track's value when it has no keys.
 * @param object Receives the zero value.
 * @return Zero.
 */
float float_track_get_zero_value(void* object)
{
    return 0.0f;
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void BootFloatTrackBase::evaluate(float key, float* output)
{
    *output = sample(key);
}

/**
 * @brief Return the key storage.
 * @return Key array, or null.
 */
BootFloatTrackKey* BootFloatTrackBase::get_keys()
{
    return key_array;
}

/**
 * @brief Release owned array storage and clear the array pointer.
 * @param track Receiver whose packed ownership flag distinguishes external storage.
 */
void float_track_free_keys(BootFloatTrackBase* track)
{
    if (!track->state.external_keys)
    {
        delete[] track->key_array;
    }

    track->key_array = 0;
}

/** @brief Release the keyframe storage. */
BootQuaternionTrackBase::~BootQuaternionTrackBase()
{
    quaternion_track_free_keys(this);
}

/**
 * @brief Release owned record-array storage and clear the array pointer.
 * @param track Receiver whose packed ownership flag distinguishes external storage.
 */
void quaternion_track_free_keys(BootQuaternionTrackBase* track)
{
    if (!track->state.external_keys)
    {
        delete[] track->key_array;
    }

    track->key_array = 0;
}

/** @brief Release the keyframe storage. */
BootClass171680::~BootClass171680()
{
    track_171680_free_keys(this);
}

/**
 * @brief Release owned record-array storage and clear the array pointer.
 * @param track Receiver whose packed ownership flag distinguishes external storage.
 */
void track_171680_free_keys(BootClass171680* track)
{
    if (!track->state.external_keys)
    {
        delete[] track->key_array;
    }

    track->key_array = 0;
}

/**
 * @brief Mark a track's pool slot as free.
 * @param pool Pool that owns the track.
 * @param track Track to release.
 */
void vector_track_pool_free(BootTrackPool<BootPooledVectorTrack>* pool, BootPooledVectorTrack* track)
{
    pool->free(track);
}

/**
 * @brief Mark a track's pool slot as free.
 * @param pool Pool that owns the track.
 * @param track Track to release.
 */
void vector_curve_track_pool_free(BootTrackPool<BootPooledVectorCurveTrack>* pool, BootPooledVectorCurveTrack* track)
{
    pool->free(track);
}

/** @brief Clear the pooled flag and reset the sequence. */
BootClass171680::BootClass171680()
{
    state.pooled = false;
    reset_state();
}

/** @brief Clear the pooled flag and reset the sequence. */
BootQuaternionTrackBase::BootQuaternionTrackBase()
{
    state.pooled = false;
    reset_state();
}

/**
 * @brief Wrap a key by the span between the first and last entries.
 * @param key Key to wrap using truncation after adjusting negative positions.
 * @return Key with the computed whole spans subtracted.
 */
float BootFloatTrackBase::wrap_key(float key) const
{
    s32 last_index = state.key_count - 1;
    float first = key_array[0].key;
    float span = key_array[last_index].key - first;
    float position = (key - first) / span;
    s32 cycles;

    if (position < 0.0f)
    {
        position -= 1.0f;
    }

    cycles = (s32)position;

    if (cycles != 0)
    {
        return key - cycles * span;
    }

    return key;
}

/**
 * @brief Read the value associated with the first exactly equal key.
 * @param track Receiver with valid storage when its count is positive.
 * @param key Key to find.
 * @return Associated value, or zero when no key matches.
 */
float float_track_find_key_value(BootFloatTrackState* track, float key)
{
    s32 index;

    for (index = 0; index < track->count; index++)
    {
        if (key == track->entries[index].key)
        {
            BootFloatStateKey* entry = track->entries + index;
            return entry->value;
        }
    }

    return 0.0f;
}

/**
 * @brief Compute the difference between the last and first entry keys.
 * @return Key span, or zero when fewer than two entries exist.
 */
float BootFloatTrackBase::get_key_span() const
{
    s32 last_index;

    if (state.key_count < 2)
    {
        return 0.0f;
    }

    last_index = state.key_count - 1;
    return key_array[last_index].key - key_array[0].key;
}

/**
 * @brief Test whether the float-entry array contains an exactly equal key.
 * @param key Key to find.
 * @return One if a matching key exists, or zero otherwise.
 */
s32 BootFloatTrackBase::has_key(float key) const
{
    s16 count = state.key_count;
    s32 index;

    for (index = 0; index < count; index++)
    {
        if (key == key_array[index].key)
        {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Forward a keyframe with a key to slot 0x74.
 * @param track Track to use.
 * @param value Key value.
 * @param key Key the keyframe sits at.
 */
void float_track_set_single_key(BootFloatTrackBase* track, const float* value, float key)
{
    track->on_set_single_key(value, key);
}

/**
 * @brief Perform no work.
 * @param track Receiver or first argument; unused.
 */
void float_track_on_set_single_key(void* track)
{
}

/**
 * @brief Forward an indexed keyframe with a key to slot 0x70.
 * @param track Track to use.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @return Nonzero when the keyframe was stored.
 */
s32 float_track_insert_key(BootFloatTrackBase* track, s32 index, float key, const float* value)
{
    return track->on_insert_key(index, key, value);
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 float_track_on_insert_key(void* track)
{
    return 0;
}

/**
 * @brief Forward an indexed keyframe with a key to slot 0x6C.
 * @param track Track to use.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @return Nonzero when the keyframe was stored.
 */
s32 float_track_replace_key(BootFloatTrackBase* track, s32 index, float key, const float* value)
{
    return track->on_replace_key(index, key, value);
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 float_track_on_replace_key(void* track)
{
    return 0;
}

/**
 * @brief Forward a keyframe with a key to slot 0x68.
 * @param track Track to use.
 * @param value Key value.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 float_track_append_key(BootFloatTrackBase* track, const float* value, float key)
{
    return track->on_append_key(value, key);
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 float_track_on_append_key(void* track)
{
    return 0;
}

/**
 * @brief Bind external entry storage and cache its first-to-last key span.
 * @param count Positive entry count representable in the receiver count fields.
 * @param entries External storage containing the specified number of entries.
 */
void BootFloatTrackBase::bind_keys(s32 count, BootFloatTrackKey* entries)
{
    s32 last_index = count - 1;
    state.external_keys = 1;
    key_array = entries;
    state.key_capacity = count;
    state.key_count = count;
    state.span = key_array[last_index].key - key_array[0].key;
}

/** @brief Clear the pooled flag and reset the sequence. */
BootFloatTrackBase::BootFloatTrackBase()
{
    state.pooled = false;
    reset_state();
}

/**
 * @brief Forward to slot 0x74.
 * @param track Track to use.
 * @param value Key value.
 * @param key Key the keyframe sits at.
 */
void vector_track_set_single_key(BootVectorTrackBase* track, const FieldVec4A* value, float key)
{
    track->on_set_single_key(value, key);
}

/**
 * @brief Perform no work.
 * @param track Receiver or first argument; unused.
 */
void vector_track_on_set_single_key(void* track)
{
}

/**
 * @brief Forward to slot 0x70.
 * @param track Track to use.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @return Nonzero when the keyframe was stored.
 */
s32 vector_track_insert_key(BootVectorTrackBase* track, s32 index, float key, const FieldVec4A* value)
{
    return track->on_insert_key(index, key, value);
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 vector_track_on_insert_key(void* track)
{
    return 0;
}

/**
 * @brief Forward to slot 0x6C.
 * @param track Track to use.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @return Nonzero when the keyframe was stored.
 */
s32 vector_track_replace_key(BootVectorTrackBase* track, s32 index, float key, const FieldVec4A* value)
{
    return track->on_replace_key(index, key, value);
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 vector_track_on_replace_key(void* track)
{
    return 0;
}

/**
 * @brief Forward to slot 0x68.
 * @param track Track to use.
 * @param value Key value.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 vector_track_append_key(BootVectorTrackBase* track, const FieldVec4A* value, float key)
{
    return track->on_append_key(value, key);
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 vector_track_on_append_key(void* track)
{
    return 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param count Requested keyframe count.
 */
void BootVectorTrackBase::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] static_cast<BootVectorTrackKey*>(key_array);
    key_array = new (0) BootVectorTrackKey[count];
    state.key_capacity = count;

    if (!key_array)
    {
        state.key_capacity = 0;
    }
}

/** @brief Clear the pooled flag and reset the sequence. */
BootVectorTrackBase::BootVectorTrackBase()
{
    state.pooled = false;
    reset_state();
}

/**
 * @brief Adjust a scalar key by whole spans determined from the endpoint records.
 * @param track Receiver with positive count, valid storage, and distinct endpoint keys.
 * @param key Scalar key whose normalized span quotient must fit in a signed word.
 * @return Key minus the computed number of endpoint spans, or the key for zero spans.
 */
float track_1718C0_wrap_key(BootState1F1580* track, float key)
{
    s32 last_index = track->count - 1;
    BootKeyEntry32* entries = track->entries;
    BootKeyEntry32* last = entries + last_index;
    float first = entries[0].key;
    float span = last->key - first;
    float quotient = (key - first) / span;
    s32 periods;

    if (quotient < 0.0f)
    {
        quotient -= 1.0f;
    }

    periods = quotient;

    if (periods != 0)
    {
        return key - (float)periods * span;
    }

    return key;
}

/**
 * @brief Read the vector value associated with the first exactly equal key.
 * @param track Receiver with 32-byte records, valid when its count is positive.
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A track_1718C0_find_key_value(BootState1F1580* track, float key)
{
    s32 index;

    for (index = 0; index < track->count; index++)
    {
        if (key == track->entries[index].key)
        {
            BootKeyEntry32* entry = track->entries + index;
            return *reinterpret_cast<const FieldVec4A*>(entry->value);
        }
    }

    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Return the last-to-first key difference, or zero below two records.
 * @param track Receiver with valid storage when its count is at least two.
 * @return Difference between the last and first scalar keys, or zero.
 */
float track_1718C0_get_key_span(BootState1F1580* track)
{
    s32 last_index;
    BootKeyEntry32* last_entry;

    if (track->count < 2)
    {
        return 0.0f;
    }

    last_index = track->count - 1;
    last_entry = track->entries + last_index;
    return last_entry->key - track->entries[0].key;
}

/**
 * @brief Test whether the 32-byte record array contains an exactly equal key.
 * @param track Receiver with valid storage when its count is positive.
 * @param key Scalar key to find.
 * @return One for an equal key, or zero when none is present.
 */
s32 track_1718C0_has_key(BootState1F1580* track, float key)
{
    s32 index;

    for (index = 0; index < track->count; index++)
    {
        if (key == track->entries[index].key)
        {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Forward to slot 0x74.
 * @param track Track to use.
 * @param value Key value.
 * @param key Key the keyframe sits at.
 */
void track_1718C0_set_single_key(BootClass1718C0* track, const FieldVec4A* value, float key)
{
    track->on_set_single_key(value, key);
}

/**
 * @brief Perform no work.
 * @param track Receiver or first argument; unused.
 */
void track_1718C0_on_set_single_key(void* track)
{
}

/**
 * @brief Forward to slot 0x70.
 * @param track Track to use.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @return Nonzero when the keyframe was stored.
 */
s32 track_1718C0_insert_key(BootClass1718C0* track, s32 index, float key, const FieldVec4A* value)
{
    return track->on_insert_key(index, key, value);
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 track_1718C0_on_insert_key(void* track)
{
    return 0;
}

/**
 * @brief Forward to slot 0x6C.
 * @param track Track to use.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @return Nonzero when the keyframe was stored.
 */
s32 track_1718C0_replace_key(BootClass1718C0* track, s32 index, float key, const FieldVec4A* value)
{
    return track->on_replace_key(index, key, value);
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 track_1718C0_on_replace_key(void* track)
{
    return 0;
}

/**
 * @brief Forward to slot 0x68.
 * @param track Track to use.
 * @param value Key value.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 track_1718C0_append_key(BootClass1718C0* track, const FieldVec4A* value, float key)
{
    return track->on_append_key(value, key);
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 track_1718C0_on_append_key(void* track)
{
    return 0;
}

/**
 * @brief Bind external 32-byte records and cache their first-to-last key span.
 * @param track Array receiver.
 * @param count Positive entry count representable in the receiver count fields.
 * @param entries External storage containing the specified number of entries.
 */
void track_1718C0_bind_keys(BootState1F1580* track, s32 count, BootKeyEntry32* entries)
{
    s32 last_index = count - 1;
    BootKeyEntry32* last;
    track->external_keys = 1;
    track->entries = entries;
    track->capacity = count;
    track->count = count;
    last = track->entries + last_index;
    track->span = last->key - track->entries[0].key;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param count Requested keyframe count.
 */
void BootClass1718C0::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] key_array;
    key_array = new (0) BootTrackKey1718C0[count];
    state.key_capacity = count;

    if (!key_array)
    {
        state.key_capacity = 0;
    }
}

/** @brief Leave the keyframe uninitialized. */
BootTrackKey1718C0::BootTrackKey1718C0()
{
}

/** @brief Clear the pooled flag and reset the sequence. */
BootClass1718C0::BootClass1718C0()
{
    state.pooled = false;
    reset_state();
}

/**
 * @brief Adjust a scalar key by whole spans determined from the endpoint records.
 * @param key Scalar key whose normalized span quotient must fit in a signed word.
 * @return Key minus the computed number of endpoint spans, or the key for zero spans.
 */
float BootFloatCurveTrackBase::wrap_key(float key) const
{
    s32 last_index = state.key_count - 1;
    BootFloatCurveTrackKey* entries = key_array;
    BootFloatCurveTrackKey* last = entries + last_index;
    float first = entries[0].key;
    float span = last->key - first;
    float quotient = (key - first) / span;
    s32 periods;

    if (quotient < 0.0f)
    {
        quotient -= 1.0f;
    }

    periods = quotient;

    if (periods != 0)
    {
        return key - (float)periods * span;
    }

    return key;
}

/**
 * @brief Find the value stored with the first exactly equal scalar key.
 * @param key Scalar key to find.
 * @return The first matching value, or zero when the key is absent.
 */
float BootFloatCurveTrackBase::find_key_value(float key)
{
    s32 index;

    for (index = 0; index < state.key_count; index++)
    {
        if (key == key_array[index].key)
        {
            BootFloatCurveTrackKey* entry = key_array + index;
            return entry->value;
        }
    }

    return 0.0f;
}

/**
 * @brief Return the last-to-first key difference, or zero below two records.
 * @return Difference between the last and first scalar keys, or zero.
 */
float BootFloatCurveTrackBase::get_key_span() const
{
    s32 last_index;
    BootFloatCurveTrackKey* last_entry;

    if (state.key_count < 2)
    {
        return 0.0f;
    }

    last_index = state.key_count - 1;
    last_entry = key_array + last_index;
    return last_entry->key - key_array[0].key;
}

/**
 * @brief Test whether the 16-byte record array contains an exactly equal key.
 * @param key Scalar key to find.
 * @return One for an equal key, or zero when none is present.
 */
s32 BootFloatCurveTrackBase::has_key(float key) const
{
    s16 count = state.key_count;
    s32 index;

    for (index = 0; index < count; index++)
    {
        if (key == key_array[index].key)
        {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Bind external 16-byte records and cache their first-to-last key span.
 * @param count Positive entry count representable in the receiver count fields.
 * @param entries External storage containing the specified number of entries.
 */
void BootFloatCurveTrackBase::bind_keys(s32 count, BootFloatCurveTrackKey* entries)
{
    s32 last_index = count - 1;
    BootFloatCurveTrackKey* last;
    state.external_keys = 1;
    key_array = entries;
    state.key_capacity = count;
    state.key_count = count;
    last = key_array + last_index;
    state.span = last->key - key_array[0].key;
}

/** @brief Clear the pooled flag and reset the sequence. */
BootFloatCurveTrackBase::BootFloatCurveTrackBase()
{
    state.pooled = false;
    reset_state();
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param count Requested keyframe count.
 */
void BootVectorCurveTrackBase::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] static_cast<BootVectorCurveTrackKey*>(key_array);
    key_array = new (0) BootVectorCurveTrackKey[count];
    state.key_capacity = count;

    if (!key_array)
    {
        state.key_capacity = 0;
    }
}

/** @brief Clear the pooled flag and reset the sequence. */
BootVectorCurveTrackBase::BootVectorCurveTrackBase()
{
    state.pooled = false;
    reset_state();
}

/** @brief Clear the pooled flag and reset the sequence. */
BootClass171A70::BootClass171A70()
{
    state.pooled = false;
    reset_state();
}

/**
 * @brief Store a single keyframe in the cached key and value.
 * @param value Keyframe value.
 * @param key Sort key.
 */
void BootFloatKeyTrack::on_set_single_key(const float* value, float key)
{
    set_before_mode(6);
    single_key.value = *value;
    single_key.key = key;
}

/**
 * @brief Read either or both members of an indexed float entry.
 * @param track Array receiver.
 * @param index Nonnegative entry index, checked against capacity.
 * @param key Optional destination for the entry key.
 * @param value Optional destination for the entry value.
 * @return One for an available slot, or zero if storage is absent or the index is too large.
 */
s32 float_track_read_entry(BootFloatTrackState* track, s32 index, float* key, float* value)
{
    if (track->entries == 0)
    {
        return 0;
    }

    if (index >= track->capacity)
    {
        return 0;
    }

    if (key != 0)
    {
        *key = track->entries[index].key;
    }

    if (value != 0)
    {
        *value = track->entries[index].value;
    }

    return 1;
}

/**
 * @brief Insert a float entry before an existing index and shift following entries.
 * @param track Array receiver with spare capacity.
 * @param index Nonnegative index less than the current count.
 * @param value Entry value to copy.
 * @param key Key associated with the entry.
 * @return One if inserted, or zero if storage is absent, full, or the index is too large.
 */
s32 float_track_insert_entry(BootFloatTrackState* track, s32 index, const float* value, float key)
{
    s32 cursor;

    if (track->entries == 0)
    {
        return 0;
    }

    if (index >= track->count)
    {
        return 0;
    }

    if (track->count >= track->capacity)
    {
        return 0;
    }

    for (cursor = track->count; cursor > index; cursor--)
    {
        BootFloatStateKey* destination = &track->entries[cursor];
        BootFloatStateKey* source = &track->entries[cursor - 1];
        destination->key = source->key;
        destination->value = source->value;
    }

    track->entries[index].value = *value;
    track->entries[index].key = key;

    if (index == track->count - 1)
    {
        track->span = key - track->entries[0].key;
    }

    track->unk1E = -1;
    track->cached_index = -1;
    track->count++;
    return 1;
}

/**
 * @brief Replace an indexed float entry and update the span when it is the last entry.
 * @param track Array receiver.
 * @param index Nonnegative entry index, checked against capacity.
 * @param value Entry value to copy.
 * @param key Key associated with the entry.
 * @return One if stored, or zero if storage is absent or the index is outside capacity.
 */
s32 float_track_replace_entry(BootFloatTrackState* track, s32 index, const float* value, float key)
{
    if (track->entries == 0)
    {
        return 0;
    }

    if (index >= track->capacity)
    {
        return 0;
    }

    track->entries[index].value = *value;
    track->entries[index].key = key;

    if (index == track->count - 1)
    {
        track->span = key - track->entries[0].key;
    }

    track->unk1E = -1;
    track->cached_index = -1;
    return 1;
}

/**
 * @brief Append a float entry and update the cached key span.
 * @param track Array receiver.
 * @param value Entry value to copy.
 * @param key Key associated with the entry.
 * @return One if appended, or zero if storage is absent or full.
 */
s32 float_track_append_entry(BootFloatTrackState* track, const float* value, float key)
{
    if (track->entries == 0)
    {
        return 0;
    }

    if (track->count >= track->capacity)
    {
        return 0;
    }

    track->entries[track->count].value = *value;
    track->entries[track->count].key = key;
    track->span = key - track->entries[0].key;
    track->unk1E = -1;
    track->cached_index = -1;
    track->count++;
    return 1;
}

/**
 * @brief Store a single keyframe in the cached value.
 * @param value Keyframe value.
 * @param key Key, stored in the value's fourth component.
 */
void BootVectorKeyTrack::on_set_single_key(const FieldVec4A* value, float key)
{
    set_before_mode(6);
    unk10 = *value;
    unk10.w = key;
}

/**
 * @brief Insert a keyframe at an index.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootVectorKeyTrack::on_insert_key(s32 index, float key, const FieldVec4A* value)
{
    s32 count;
    s32 i;

    if (key_array == 0)
    {
        return 0;
    }

    count = state.key_count;

    if (index >= count)
    {
        return 0;
    }

    if (count >= state.key_capacity)
    {
        return 0;
    }

    for (i = count; i > index; i--)
    {
        static_cast<BootVectorTrackKey*>(key_array)[i] = static_cast<BootVectorTrackKey*>(key_array)[i - 1];
    }

    static_cast<BootVectorTrackKey*>(key_array)[index].value = *value;
    static_cast<BootVectorTrackKey*>(key_array)[index].value.w = key;

    if (index == state.key_count - 1)
    {
        state.span = key - static_cast<BootVectorTrackKey*>(key_array)[0].value.w;
    }

    state.unk0e = -1;
    state.cached_index = -1;
    state.key_count++;
    return 1;
}

/**
 * @brief Store a single keyframe in the cached key and value.
 * @param value Keyframe value.
 * @param key Sort key.
 */
void BootClass171320::on_set_single_key(const FieldVec4A* value, float key)
{
    set_before_mode(6);
    unk20 = *value;
    unk10 = key;
}

/**
 * @brief Read an indexed keyframe.
 * @param index Keyframe index.
 * @param key Receives the sort key.
 * @param value Receives the value.
 * @param first Unused; this track has no auxiliary vectors.
 * @param second Unused; this track has no auxiliary vectors.
 * @return One when the index is within the capacity, otherwise zero.
 */
s32 BootClass171320::read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const
{
    if (key_array == 0)
    {
        return 0;
    }

    if (index >= state.key_capacity)
    {
        return 0;
    }

    if (key)
    {
        *key = key_array[index].key;
    }

    if (value)
    {
        *value = key_array[index].value;
    }

    return 1;
}

/**
 * @brief Insert a keyframe at an index.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootClass171320::on_insert_key(s32 index, float key, const FieldVec4A* value)
{
    s32 count;
    s32 i;

    if (key_array == 0)
    {
        return 0;
    }

    count = state.key_count;

    if (index >= count)
    {
        return 0;
    }

    if (count >= state.key_capacity)
    {
        return 0;
    }

    for (i = count; i > index; i--)
    {
        key_array[i] = key_array[i - 1];
    }

    key_array[index].value = *value;
    key_array[index].key = key;

    if (index == state.key_count - 1)
    {
        state.span = key - key_array[0].key;
    }

    state.unk0e = -1;
    state.cached_index = -1;
    state.key_count++;
    return 1;
}

/**
 * @brief Replace an indexed keyframe.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootClass171320::on_replace_key(s32 index, float key, const FieldVec4A* value)
{
    if (key_array == 0)
    {
        return 0;
    }

    if (index >= state.key_capacity)
    {
        return 0;
    }

    key_array[index].value = *value;
    key_array[index].key = key;

    if (index == state.key_count - 1)
    {
        state.span = key - key_array[0].key;
    }

    state.unk0e = -1;
    state.cached_index = -1;
    return 1;
}

/**
 * @brief Append a keyframe.
 * @param value Keyframe value.
 * @param key Sort key.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootClass171320::on_append_key(const FieldVec4A* value, float key)
{
    if (key_array == 0)
    {
        return 0;
    }

    if (state.key_count >= state.key_capacity)
    {
        return 0;
    }

    key_array[state.key_count].value = *value;
    key_array[state.key_count].key = key;
    state.span = key - key_array[0].key;
    state.unk0e = -1;
    state.cached_index = -1;
    state.key_count++;
    return 1;
}

/** @brief Reset to a single zero keyframe at key zero, then set before_mode to one. */
void BootFloatTrack::reset_keys()
{
    float zero = 0.0f;
    on_set_single_key(&zero, 0.0f);
    set_before_mode(1);
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @return Evaluated value.
 */
float BootFloatTrack::sample(float key)
{
    s32 lower;
    s32 upper;
    float wrapped_key;
    float result;
    u8 extrapolate;

    if (!key_array || !state.key_count)
    {
        return 0.0f;
    }

    if (state.unk0c >= state.key_capacity)
    {
        state.unk0c = 0;
    }

    if (state.key_count == 1 && (!(key < key_array[0].key) || state.before_mode != 6))
    {
        return key_array[0].value;
    }

    if (key < key_array[0].key && state.before_mode == 6)
    {
        upper = 0;
        wrapped_key = key;
        lower = -1;
    }
    else
    {
        wrapped_key = float_track_update_cycle_count(reinterpret_cast<BootFloatTrackState*>(this), key);

        if (state.before_mode == 0 && state.cycle_count < 0)
        {
            return key_array[0].value;
        }

        if (state.after_mode == 0 && state.cycle_count > 0)
        {
            return key_array[state.key_count - 1].value;
        }

        extrapolate = float_track_find_surrounding_keys(this, wrapped_key, &lower, &upper);

        if (extrapolate)
        {
            wrapped_key = key;
        }
    }

    if (state.unk0e != lower || state.cached_index != upper)
    {
        state.unk0e = lower;
        state.cached_index = upper;
        BootFloatTrackKey* first = lower >= 0 ? key_array + lower : &single_key;
        sample_history.sample_count = 0;
        sample_history.next_index = 0;
        sample_history.unk08 = 0;
        sample_history.unk0C = 0;
        sample_history.add_sample(first->key, first->value);
        s32 last = state.key_count - 1;
        // TODO: My guess; copying upper into its own local is the only way I found that matches.
        s32 upper_index = upper;

        if (upper_index == last && ((!(key < key_array[0].key) && state.after_mode == 2) || (key < key_array[0].key && state.before_mode == 2)))
        {
            BootFloatTrackKey* entries = key_array;
            sample_history.add_sample(entries[upper_index].key, entries[0].value);
        }
        else if (lower < upper_index)
        {
            BootFloatTrackKey* second = key_array + upper_index;
            sample_history.add_sample(second->key, second->value);
        }
        else
        {
            sample_history.add_sample(key_array[last].key, key_array[upper_index].value);
        }
    }

    result = sample_history.sample(wrapped_key);

    if ((state.before_mode == 5 && state.cycle_count < 0) || (state.after_mode == 5 && state.cycle_count > 0))
    {
        float delta = key_array[state.key_count - 1].value - key_array[0].value;
        result += delta * state.cycle_count;
    }

    value_rate = (result - last_value) / D_001B6688;
    last_value = result;
    return result;
}

/** @brief Reset to a single zero keyframe at key zero, then set before_mode to one. */
void BootVectorTrack::reset_keys()
{
    FieldVec4A zero(0.0f, 0.0f, 0.0f, 0.0f);
    on_set_single_key(&zero, 0.0f);
    set_before_mode(1);
}

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
s32 float_curve_track_read_entry(BootFloatCurveTrackState* track, s32 index, float* key, float* value, float* in_tangent, float* out_tangent)
{
    if (!track->entries)
    {
        return 0;
    }

    if (index >= track->capacity)
    {
        return 0;
    }

    if (key)
    {
        *key = track->entries[index].key;
    }

    if (value)
    {
        *value = track->entries[index].value;
    }

    if (in_tangent)
    {
        *in_tangent = track->entries[index].in_tangent;
    }

    if (out_tangent)
    {
        *out_tangent = track->entries[index].out_tangent;
    }

    return 1;
}

/**
 * @brief Store a single entry in the cached entry.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Sort value.
 */
void BootFloatCurveTrack::set_single_curve_key(const float* value, const float* in_tangent, const float* out_tangent, float key)
{
    set_before_mode(6);
    single_key.value = *value;
    single_key.in_tangent = *in_tangent;
    single_key.out_tangent = *out_tangent;
    single_key.key = key;
}

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
                                       float key)
{
    s32 cursor;

    if (!track->entries)
    {
        return 0;
    }

    if (index >= track->count)
    {
        return 0;
    }

    if (track->count >= track->capacity)
    {
        return 0;
    }

    for (cursor = track->count; cursor > index; cursor--)
    {
        BootFloatCurveStateKey* destination = &track->entries[cursor];
        BootFloatCurveStateKey* source = &track->entries[cursor - 1];
        destination->key = source->key;
        destination->value = source->value;
        destination->in_tangent = source->in_tangent;
        destination->out_tangent = source->out_tangent;
    }

    track->entries[index].value = *value;
    track->entries[index].in_tangent = *in_tangent;
    track->entries[index].out_tangent = *out_tangent;
    track->entries[index].key = key;

    if (index == track->count - 1)
    {
        track->span = key - track->entries[0].key;
    }

    track->count++;
    return 1;
}

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
                                        float key)
{
    if (!track->entries)
    {
        return 0;
    }

    if (index >= track->capacity)
    {
        return 0;
    }

    track->entries[index].value = *value;
    track->entries[index].in_tangent = *in_tangent;
    track->entries[index].out_tangent = *out_tangent;
    track->entries[index].key = key;

    if (index == track->count - 1)
    {
        track->span = key - track->entries[0].key;
    }

    return 1;
}

/**
 * @brief Append three values and their key, updating the span and entry count.
 * @param track Record-array receiver with a nonnegative entry count.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key associated with the new entry.
 * @return One if appended, or zero if storage is absent or capacity is exhausted.
 */
s32 float_curve_track_append_entry(BootFloatCurveTrackState* track, const float* value, const float* in_tangent, const float* out_tangent, float key)
{
    if (!track->entries)
    {
        return 0;
    }

    if (track->count >= track->capacity)
    {
        return 0;
    }

    track->entries[track->count].value = *value;
    track->entries[track->count].in_tangent = *in_tangent;
    track->entries[track->count].out_tangent = *out_tangent;
    track->entries[track->count].key = key;
    track->span = key - track->entries[0].key;
    track->count++;
    return 1;
}

/**
 * @brief Evaluate the track with cached interpolation, wrapping and endpoint extrapolation.
 * @param key Sort value.
 * @return Evaluated value; updates the cached value and its scaled change.
 */
float BootFloatCurveTrack::sample(float key)
{
    s32 lower;
    s32 upper;
    float wrapped_key;
    u8 extrapolate;
    float result;

    if (!key_array || !state.key_count)
    {
        return 0.0f;
    }

    if (state.unk0c >= state.key_capacity)
    {
        state.unk0c = 0;
    }

    if (state.key_count == 1 && (!(key < key_array[0].key) || state.before_mode != 6))
    {
        return key_array[0].value;
    }

    extrapolate = 0;

    if (key < key_array[0].key && state.before_mode == 6)
    {
        upper = 0;
        wrapped_key = key;
        lower = -1;
    }
    else
    {
        wrapped_key = float_curve_track_update_cycle_count(reinterpret_cast<BootFloatCurveTrackState*>(this), key);

        if (state.cycle_count)
        {
            if (state.before_mode == 0 && state.cycle_count < 0)
            {
                return key_array[0].value;
            }

            if (state.after_mode == 0 && state.cycle_count > 0)
            {
                return key_array[state.key_count - 1].value;
            }
        }

        extrapolate = float_curve_track_find_surrounding_keys(this, wrapped_key, &lower, &upper);

        if (extrapolate)
        {
            wrapped_key = key;
        }
    }

    if (!extrapolate)
    {
        if (state.unk0e != lower || state.cached_index != upper)
        {
            state.unk0e = lower;
            state.cached_index = upper;
            BootFloatCurveTrackKey* first = lower >= 0 ? key_array + lower : &single_key;
            s32 last = state.key_count - 1;

            if (upper == last && ((!(key < key_array[0].key) && state.after_mode == 2) || (key < key_array[0].key && state.before_mode == 2)))
            {
                BootFloatCurveTrackKey* entries = key_array;
                curve_segment.set_endpoints(&first->value, &first->out_tangent, &entries[0].value, &entries[0].in_tangent, first->key, entries[upper].key);
            }
            else if (lower < upper)
            {
                BootFloatCurveTrackKey* second = key_array + upper;
                curve_segment.set_endpoints(&first->value, &first->out_tangent, &second->value, &second->in_tangent, first->key, second->key);
            }
            else
            {
                BootFloatCurveTrackKey* second = key_array + last;
                curve_segment.set_endpoints(&first->value, &first->out_tangent, &second->value, &second->in_tangent, first->key, second->key);
            }
        }

        result = func_4B16C0(&curve_segment, wrapped_key);

        if (state.cycle_count && ((state.before_mode == 5 && state.cycle_count < 0) || (state.after_mode == 5 && state.cycle_count > 0)))
        {
            float delta = key_array[state.key_count - 1].value - key_array[0].value;
            result += delta * state.cycle_count;
        }
    }
    else if (wrapped_key < key)
    {
        s32 count = state.key_count;
        BootFloatCurveTrackKey* entries = key_array;
        BootFloatCurveTrackKey* last_entry = entries + (count - 1);
        BootFloatCurveTrackKey* previous_entry = entries + (count - 2);
        float last_key = last_entry->key;
        float previous_key = previous_entry->key;
        float slope = entries[count - 1].in_tangent / (last_key - previous_key);
        result = entries[count - 1].value + slope * (key - last_key);
    }
    else
    {
        BootFloatCurveTrackKey* entries = key_array;
        float first_key = entries[0].key;
        result = entries[0].value + (entries[0].out_tangent / (entries[1].key - first_key)) * (key - first_key);
    }

    value_rate = D_001B668C * (result - last_value);
    last_value = result;
    return result;
}

/**
 * @brief Store a single keyframe in the cached vectors.
 * @param value Keyframe value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key, stored in the value's fourth component.
 */
void BootVectorCurveTrack::set_single_curve_key(const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent, float key)
{
    set_before_mode(6);
    unk10 = *value;
    unk20 = *in_tangent;
    unk30 = *out_tangent;
    unk10.w = key;
}

/**
 * @brief Insert a keyframe at an index.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootVectorCurveTrack::insert_curve_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent)
{
    s32 count;
    s32 i;

    if (key_array == 0)
    {
        return 0;
    }

    count = state.key_count;

    if (index >= count)
    {
        return 0;
    }

    if (count >= state.key_capacity)
    {
        return 0;
    }

    for (i = count; i > index; i--)
    {
        static_cast<BootVectorCurveTrackKey*>(key_array)[i] = static_cast<BootVectorCurveTrackKey*>(key_array)[i - 1];
    }

    static_cast<BootVectorCurveTrackKey*>(key_array)[index].value = *value;
    static_cast<BootVectorCurveTrackKey*>(key_array)[index].in_tangent = *in_tangent;
    static_cast<BootVectorCurveTrackKey*>(key_array)[index].out_tangent = *out_tangent;
    static_cast<BootVectorCurveTrackKey*>(key_array)[index].value.w = key;

    if (index == state.key_count - 1)
    {
        state.span = key - static_cast<BootVectorCurveTrackKey*>(key_array)[0].value.w;
    }

    state.key_count++;
    return 1;
}

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param value Value to store, truncated to four bits.
 */
void BootClass171680::set_before_mode(u32 value)
{
    state.before_mode = value;
    state.repeats = state.before_mode == 4 || state.after_mode == 4;
}

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param value Value to store, truncated to four bits.
 */
void BootQuaternionTrackBase::set_before_mode(u32 value)
{
    state.before_mode = value;
    state.repeats = state.before_mode == 4 || state.after_mode == 4;
}

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param value Value to store, truncated to four bits.
 */
void BootClass171A70::set_before_mode(u32 value)
{
    state.before_mode = value;
    state.repeats = state.before_mode == 4 || state.after_mode == 4;
}

/**
 * @brief Store a value and key in the two-entry history and count it, up to two.
 * @param value Value to store.
 * @param key Key to store.
 */
void BootClass171B70::push_sample(const FieldVec4A* value, float key)
{
    unk20[next_index] = *value;
    unk40[next_index] = key;

    if (++next_index >= 2)
    {
        next_index = 0;
    }

    if (++sample_count > 2)
    {
        sample_count = 2;
    }
}

/**
 * @brief Store paired float values in the next slot of a two-entry history.
 * @param history History whose write index wraps and count saturates at two.
 * @param value First float value to copy.
 * @param associated Second float value to store.
 */
void float_history_push(BootFloatHistoryState* history, const float* value, float associated)
{
    history->values[history->next_index] = *value;
    history->unk1C[history->next_index] = associated;

    if (++history->next_index >= 2)
    {
        history->next_index = 0;
    }

    if (++history->count > 2)
    {
        history->count = 2;
    }
}

/**
 * @brief Perform no work.
 * @param history Receiver or first argument; unused.
 */
void func_001F4950(void* history)
{
}

/**
 * @brief Perform no work.
 * @param history Receiver or first argument; unused.
 */
void func_001F4960(void* history)
{
}

/**
 * @brief Perform no work.
 * @param history Receiver or first argument; unused.
 */
void func_001F4970(void* history)
{
}

/**
 * @brief Reset array storage, counts, packed controls, and cached indices.
 */
void BootClass171A70::reset_state()
{
    key_array = 0;
    state.before_mode = 1;
    state.after_mode = 1;
    state.key_capacity = 0;
    state.key_count = 0;
    state.unk0c = -1;
    state.cycle_count = 0;
    state.unk0e = -1;
    state.cached_index = -1;
    state.repeats = 0;
    state.external_keys = 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param count Requested keyframe count.
 */
void BootClass171A70::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] key_array;
    key_array = new (0) BootTrackKey171A70[count];
    state.key_capacity = count;

    if (!key_array)
    {
        state.key_capacity = 0;
    }
}

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param value Value to store, truncated to four bits.
 */
void BootClass171A70::set_after_mode(u32 value)
{
    state.after_mode = value;
    state.repeats = state.before_mode == 4 || state.after_mode == 4;
}

/**
 * @brief Return how many key spans the last wrapped key was past the first key.
 * @return Signed cycle count.
 */
s32 BootClass171A70::get_cycle_count() const
{
    return state.cycle_count;
}

/**
 * @brief Return the number of stored keys.
 * @return Key count.
 */
s16 BootClass171A70::get_key_count() const
{
    return state.key_count;
}

/**
 * @brief Return the number of keys the storage can hold.
 * @return Key capacity.
 */
s16 BootClass171A70::get_key_capacity()
{
    return state.key_capacity;
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 track_171A70_on_append_key(void* track)
{
    return 0;
}

/**
 * @brief Forward to slot 0x68.
 * @param track Track to use.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 track_171A70_append_key(BootClass171A70* track, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return track->on_append_key(value, first, second, key);
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 track_171A70_on_replace_key(void* track)
{
    return 0;
}

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
s32 track_171A70_replace_key(BootClass171A70* track, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return track->on_replace_key(index, key, value, first, second);
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 track_171A70_on_insert_key(void* track)
{
    return 0;
}

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
s32 track_171A70_insert_key(BootClass171A70* track, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return track->on_insert_key(index, key, value, first, second);
}

/**
 * @brief Perform no work.
 * @param track Receiver or first argument; unused.
 */
void track_171A70_on_set_single_key(void* track)
{
}

/**
 * @brief Forward to slot 0x74.
 * @param track Track to use.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 */
void track_171A70_set_single_key(BootClass171A70* track, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    track->on_set_single_key(value, first, second, key);
}

/**
 * @brief Write a zero value; the track's value when it has no keys.
 * @param result Receives the zero value.
 */
void track_171A70_get_zero_value(u32* result)
{
    result[0] = 0;
    result[1] = 0;
    result[2] = 0;
    result[3] = 0;
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void BootClass171A70::evaluate(float key, FieldVec4B* output) const
{
    *output = sample(key);
}

/**
 * @brief Return the key storage.
 * @return Key array, or null.
 */
BootTrackKey171A70* BootClass171A70::get_keys()
{
    return key_array;
}

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
                                  float key)
{
    return track->on_append_key(value, in_tangent, out_tangent, key);
}

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
                                   const FieldVec4A* out_tangent)
{
    return track->on_replace_key(index, key, value, in_tangent, out_tangent);
}

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
                                  const FieldVec4A* out_tangent)
{
    return track->on_insert_key(index, key, value, in_tangent, out_tangent);
}

/**
 * @brief Forward to slot 0x74.
 * @param track Track to use.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key the keyframe sits at.
 */
void vector_curve_track_set_single_key(BootVectorCurveTrackBase* track, const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent,
                                       float key)
{
    track->on_set_single_key(value, in_tangent, out_tangent, key);
}

/**
 * @brief Normalize a key across the cached span and store its signed period count.
 * @param track Receiver with record storage and a nonzero cached key span.
 * @param key Key whose period count is representable as a signed 32-bit integer.
 * @return Normalized key, with odd-period reflection selected by the control fields.
 */
float float_curve_track_update_cycle_count(BootFloatCurveTrackState* track, float key)
{
    float first = track->entries[0].key;
    float quotient = (key - first) / track->span;

    if (key < first)
    {
        quotient -= 1.0f;
    }

    track->cycle_count = quotient;

    if (track->cycle_count)
    {
        float result = key - (float)track->cycle_count * track->span;

        if ((track->before_mode == 3 && track->cycle_count < 0) || (track->after_mode == 3 && track->cycle_count > 0))
        {
            s32 last_index = track->count - 1;
            BootFloatCurveStateKey* last_entry = track->entries + last_index;
            float last = last_entry->key;

            if (track->cycle_count & 1)
            {
                result = first + (last - result);
            }
        }

        return result;
    }

    return key;
}

/**
 * @brief Find the entries around a key, starting from the cached cursor.
 * @param track Track to search.
 * @param key Key to place.
 * @param lower Receives the lower entry index.
 * @param upper Receives the upper entry index.
 * @return One when a reflecting end mode extends the first or last segment, otherwise zero.
 */
u8 float_curve_track_find_surrounding_keys(BootFloatCurveTrackBase* track, float key, s32* lower, s32* upper)
{
    s32 index;
    s32 count;
    s32 next;

    if (track->state.repeats)
    {
        if (track->state.before_mode == 4 && track->state.cycle_count < 0)
        {
            *lower = 0;
            *upper = 1;
            track->state.unk0c = 0;
            return 1;
        }

        if (track->state.after_mode == 4 && track->state.cycle_count > 0)
        {
            *lower = track->state.key_count - 2;
            *upper = track->state.key_count - 1;
            track->state.unk0c = track->state.key_count - 2;
            return 1;
        }
    }

    index = track->state.unk0c;
    count = track->state.key_count;

    while (index > 0 && key < track->key_array[index].key)
    {
        index--;
    }

    index = clamp_low(index, 0);

    while ((next = index + 1) < count && !(key < track->key_array[next].key))
    {
        index++;
    }

    if (index >= count - 1)
    {
        *lower = count - 2;
        *upper = count - 1;
    }
    else
    {
        *lower = index;
        *upper = index + 1;
    }

    track->state.unk0c = index;
    return 0;
}
/**
 * @brief Forward to slot 0x68.
 * @param track Track to use.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 float_curve_track_append_key(BootFloatCurveTrackBase* track, const float* value, const float* in_tangent, const float* out_tangent, float key)
{
    return track->on_append_key(value, in_tangent, out_tangent, key);
}

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
s32 float_curve_track_replace_key(BootFloatCurveTrackBase* track, s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent)
{
    return track->on_replace_key(index, key, value, in_tangent, out_tangent);
}

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
s32 float_curve_track_insert_key(BootFloatCurveTrackBase* track, s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent)
{
    return track->on_insert_key(index, key, value, in_tangent, out_tangent);
}

/**
 * @brief Forward to slot 0x74.
 * @param track Track to use.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key the keyframe sits at.
 */
void float_curve_track_set_single_key(BootFloatCurveTrackBase* track, const float* value, const float* in_tangent, const float* out_tangent, float key)
{
    track->on_set_single_key(value, in_tangent, out_tangent, key);
}

/**
 * @brief Normalize a key across the cached span and store its signed period count.
 * @param track Receiver with float-key entries and a nonzero cached key span.
 * @param key Key whose period count is representable as a signed 32-bit integer.
 * @return Normalized key, with odd-period reflection selected by the control fields.
 */
float float_track_update_cycle_count(BootFloatTrackState* track, float key)
{
    float first = track->entries[0].key;
    float quotient = (key - first) / track->span;

    if (key < first)
    {
        quotient -= 1.0f;
    }

    track->cycle_count = quotient;

    if (track->cycle_count)
    {
        float result = key - (float)track->cycle_count * track->span;

        if ((track->before_mode == 3 && track->cycle_count < 0) || (track->after_mode == 3 && track->cycle_count > 0))
        {
            s32 last_index = track->count - 1;
            BootFloatStateKey* last_entry = track->entries + last_index;
            float last = last_entry->key;

            if (track->cycle_count & 1)
            {
                result = first + (last - result);
            }
        }

        return result;
    }

    return key;
}

/**
 * @brief Find the entries around a key, starting from the cached cursor.
 * @param track Track to search.
 * @param key Key to place.
 * @param lower Receives the lower entry index.
 * @param upper Receives the upper entry index.
 * @return One when a reflecting end mode extends the first or last segment, otherwise zero.
 */
u8 float_track_find_surrounding_keys(BootFloatTrackBase* track, float key, s32* lower, s32* upper)
{
    s32 index;
    s32 count;
    s32 next;

    if (track->state.repeats)
    {
        if (track->state.before_mode == 4 && track->state.cycle_count < 0)
        {
            *lower = 0;
            *upper = 1;
            track->state.unk0c = 0;
            return 1;
        }

        if (track->state.after_mode == 4 && track->state.cycle_count > 0)
        {
            *lower = track->state.key_count - 2;
            *upper = track->state.key_count - 1;
            track->state.unk0c = track->state.key_count - 2;
            return 1;
        }
    }

    index = track->state.unk0c;
    count = track->state.key_count;

    while (index > 0 && key < track->key_array[index].key)
    {
        index--;
    }

    index = clamp_low(index, 0);

    while ((next = index + 1) < count && !(key < track->key_array[next].key))
    {
        index++;
    }

    if (index >= count - 1)
    {
        *lower = count - 2;
        *upper = count - 1;
    }
    else
    {
        *lower = index;
        *upper = index + 1;
    }

    track->state.unk0c = index;
    return 0;
}
/**
 * @brief Reset signed-key entry storage, counts, control fields, and cached indices.
 */
void BootQuaternionTrackBase::reset_state()
{
    key_array = 0;
    state.before_mode = 1;
    state.after_mode = 1;
    state.key_capacity = 0;
    state.key_count = 0;
    state.unk0c = -1;
    state.cycle_count = 0;
    state.unk0e = -1;
    state.cached_index = -1;
    state.repeats = 0;
    state.external_keys = 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param count Requested keyframe count.
 */
void BootQuaternionTrackBase::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] key_array;
    key_array = new (0) BootQuaternionTrackKey[count];
    state.key_capacity = count;

    if (!key_array)
    {
        state.key_capacity = 0;
    }
}

/**
 * @brief Bind external entry storage and cache its first-to-last key span.
 * @param count Positive entry count representable in the receiver count fields.
 * @param entries External storage containing the specified number of entries.
 */
void BootQuaternionTrackBase::bind_keys(s32 count, BootQuaternionTrackKey* entries)
{
    s32 last_index = count - 1;
    BootQuaternionTrackKey* last;
    state.external_keys = 1;
    key_array = entries;
    state.key_capacity = count;
    state.key_count = count;
    last = key_array + last_index;
    state.span = (float)last->key - (float)key_array[0].key;
}

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param value Value to store, truncated to four bits.
 */
void BootQuaternionTrackBase::set_after_mode(u32 value)
{
    state.after_mode = value;
    state.repeats = state.before_mode == 4 || state.after_mode == 4;
}

/**
 * @brief Return how many key spans the last wrapped key was past the first key.
 * @return Signed cycle count.
 */
s32 BootQuaternionTrackBase::get_cycle_count() const
{
    return state.cycle_count;
}

/**
 * @brief Return the number of stored keys.
 * @return Key count.
 */
s16 BootQuaternionTrackBase::get_key_count() const
{
    return state.key_count;
}

/**
 * @brief Return the number of keys the storage can hold.
 * @return Key capacity.
 */
s16 BootQuaternionTrackBase::get_key_capacity()
{
    return state.key_capacity;
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 quaternion_track_on_append_key(void* track)
{
    return 0;
}

/**
 * @brief Forward to slot 0x68.
 * @param track Track to use.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 quaternion_track_append_key(BootQuaternionTrackBase* track, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return track->on_append_key(value, first, second, key);
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 quaternion_track_on_replace_key(void* track)
{
    return 0;
}

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
                                 const FieldVec4A* second)
{
    return track->on_replace_key(index, key, value, first, second);
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 quaternion_track_on_insert_key(void* track)
{
    return 0;
}

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
                                const FieldVec4A* second)
{
    return track->on_insert_key(index, key, value, first, second);
}

/**
 * @brief Perform no work.
 * @param track Receiver or first argument; unused.
 */
void quaternion_track_on_set_single_key(void* track)
{
}

/**
 * @brief Forward to slot 0x74.
 * @param track Track to use.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 */
void quaternion_track_set_single_key(BootQuaternionTrackBase* track, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    track->on_set_single_key(value, first, second, key);
}

/**
 * @brief Test whether the array contains a signed entry key equal to the given float.
 * @param key Key to find.
 * @return One if a matching key exists, or zero otherwise.
 */
s32 BootQuaternionTrackBase::has_key(float key) const
{
    s16 count = state.key_count;
    s32 index;

    for (index = 0; index < count; index++)
    {
        if (key == key_array[index].key)
        {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Write a zero value; the track's value when it has no keys.
 * @param result Receives the zero value.
 */
void quaternion_track_get_zero_value(u32* result)
{
    result[0] = 0;
    result[1] = 0;
    result[2] = 0;
    result[3] = 0;
}

/**
 * @brief Compute the difference between the last and first entry keys.
 * @return Key span, or zero when fewer than two entries exist.
 */
float BootQuaternionTrackBase::get_key_span() const
{
    s32 last_index;
    BootQuaternionTrackKey* last_entry;

    if (state.key_count < 2)
    {
        return 0.0f;
    }

    last_index = state.key_count - 1;
    last_entry = key_array + last_index;
    return (float)last_entry->key - (float)key_array[0].key;
}

/**
 * @brief Read the result pointer back through its address.
 * @param out Result pointer.
 */
static inline void reread_result(FieldVec4A*& out)
{
    // TODO: The original reads the result pointer again after the copy; a volatile read is the only way I found that matches.
    FieldVec4A* volatile* slot = &out;
    (void)*slot;
}

/**
 * @brief Find the keyframe with a key and decode its rotation.
 * @param out Receives the rotation, or zero when the key is absent.
 * @param track Keyframe array.
 * @param key Key to find.
 */
void quaternion_track_find_key_value(FieldVec4A* out, BootQuaternionTrackState* track, float key)
{
    s32 index;

    for (index = 0; index < track->count; index++)
    {
        BootQuaternionStateKey* entry = track->entries + index;

        if (key == entry->key)
        {
            FieldVec4A value;
            vu0_decode_short_quaternion(entry);
            vu0_store_decoded_quaternion(&value);
            *out = value;
            reread_result(out);
            return;
        }
    }

    FieldVec4A* result = out;
    result->x = 0.0f;
    result->y = 0.0f;
    result->z = 0.0f;
    result->w = 0.0f;
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void BootQuaternionTrackBase::evaluate(float key, FieldVec4B* output) const
{
    *output = sample(key);
}

/**
 * @brief Wrap a key by the span between the first and last entries.
 * @param key Key whose normalized span quotient must fit in a signed word.
 * @return Key with the computed whole spans subtracted.
 */
float BootQuaternionTrackBase::wrap_key(float key) const
{
    s32 last_index = state.key_count - 1;
    BootQuaternionTrackKey* entries = key_array;
    BootQuaternionTrackKey* last = entries + last_index;
    float first = entries[0].key;
    float span = last->key - first;
    float position = (key - first) / span;
    s32 cycles;

    if (position < 0.0f)
    {
        position -= 1.0f;
    }

    cycles = (s32)position;

    if (cycles != 0)
    {
        return key - cycles * span;
    }

    return key;
}

/**
 * @brief Return the key storage.
 * @return Key array, or null.
 */
BootQuaternionTrackKey* BootQuaternionTrackBase::get_keys()
{
    return key_array;
}

/**
 * @brief Reset 48-byte record storage, counts, packed controls, and cached indices.
 */
void BootClass171680::reset_state()
{
    key_array = 0;
    state.before_mode = 1;
    state.after_mode = 1;
    state.key_capacity = 0;
    state.key_count = 0;
    state.unk0c = -1;
    state.cycle_count = 0;
    state.unk0e = -1;
    state.cached_index = -1;
    state.repeats = 0;
    state.external_keys = 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param count Requested keyframe count.
 */
void BootClass171680::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] key_array;
    key_array = new (0) BootTrackKey171680[count];
    state.key_capacity = count;

    if (!key_array)
    {
        state.key_capacity = 0;
    }
}

/**
 * @brief Bind external 48-byte records and cache their first-to-last key span.
 * @param count Positive entry count representable in the receiver count fields.
 * @param entries External storage containing the specified number of entries.
 */
void BootClass171680::bind_keys(s32 count, BootTrackKey171680* entries)
{
    s32 last_index = count - 1;
    BootTrackKey171680* last;
    state.external_keys = 1;
    key_array = entries;
    state.key_capacity = count;
    state.key_count = count;
    last = key_array + last_index;
    state.span = last->key - key_array[0].key;
}

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param value Value to store, truncated to four bits.
 */
void BootClass171680::set_after_mode(u32 value)
{
    state.after_mode = value;
    state.repeats = state.before_mode == 4 || state.after_mode == 4;
}

/**
 * @brief Return how many key spans the last wrapped key was past the first key.
 * @return Signed cycle count.
 */
s32 BootClass171680::get_cycle_count() const
{
    return state.cycle_count;
}

/**
 * @brief Return the number of stored keys.
 * @return Key count.
 */
s16 BootClass171680::get_key_count() const
{
    return state.key_count;
}

/**
 * @brief Return the number of keys the storage can hold.
 * @return Key capacity.
 */
s16 BootClass171680::get_key_capacity()
{
    return state.key_capacity;
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 track_171680_on_append_key(void* track)
{
    return 0;
}

/**
 * @brief Forward to slot 0x68.
 * @param track Track to use.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 track_171680_append_key(BootClass171680* track, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return track->on_append_key(value, first, second, key);
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 track_171680_on_replace_key(void* track)
{
    return 0;
}

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
s32 track_171680_replace_key(BootClass171680* track, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return track->on_replace_key(index, key, value, first, second);
}

/**
 * @brief Return the fixed value 0.
 * @param track Receiver or first argument; unused.
 * @return Always 0.
 */
s32 track_171680_on_insert_key(void* track)
{
    return 0;
}

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
s32 track_171680_insert_key(BootClass171680* track, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return track->on_insert_key(index, key, value, first, second);
}

/**
 * @brief Perform no work.
 * @param track Receiver or first argument; unused.
 */
void track_171680_on_set_single_key(void* track)
{
}

/**
 * @brief Forward to slot 0x74.
 * @param track Track to use.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 */
void track_171680_set_single_key(BootClass171680* track, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    track->on_set_single_key(value, first, second, key);
}

/**
 * @brief Test whether the 48-byte record array contains an exactly equal key.
 * @param key Scalar key to find.
 * @return One for an equal key, or zero when none is present.
 */
s32 BootClass171680::has_key(float key) const
{
    s16 count = state.key_count;
    s32 index;

    for (index = 0; index < count; index++)
    {
        if (key == key_array[index].key)
        {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Write a zero value; the track's value when it has no keys.
 * @param result Receives the zero value.
 */
void track_171680_get_zero_value(u32* result)
{
    result[0] = 0;
    result[1] = 0;
    result[2] = 0;
    result[3] = 0;
}

/**
 * @brief Return the last-to-first key difference, or zero below two records.
 * @return Difference between the last and first scalar keys, or zero.
 */
float BootClass171680::get_key_span() const
{
    s32 last_index;
    BootTrackKey171680* last_entry;

    if (state.key_count < 2)
    {
        return 0.0f;
    }

    last_index = state.key_count - 1;
    last_entry = key_array + last_index;
    return last_entry->key - key_array[0].key;
}

/**
 * @brief Read the vector value associated with the first exactly equal key.
 * @param track Receiver with 48-byte records, valid when its count is positive.
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A track_171680_find_key_value(BootState1F4730* track, float key)
{
    s32 index;

    for (index = 0; index < track->count; index++)
    {
        if (key == track->entries[index].key)
        {
            BootKeyEntry48* entry = track->entries + index;
            return *reinterpret_cast<const FieldVec4A*>(entry->value);
        }
    }

    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void BootClass171680::evaluate(float key, FieldVec4B* output) const
{
    *output = sample(key);
}

/**
 * @brief Adjust a scalar key by whole spans determined from the endpoint records.
 * @param key Scalar key whose normalized span quotient must fit in a signed word.
 * @return Key minus the computed number of endpoint spans, or the key for zero spans.
 */
float BootClass171680::wrap_key(float key) const
{
    s32 last_index = state.key_count - 1;
    BootTrackKey171680* entries = key_array;
    BootTrackKey171680* last = entries + last_index;
    float first = entries[0].key;
    float span = last->key - first;
    float quotient = (key - first) / span;
    s32 periods;

    if (quotient < 0.0f)
    {
        quotient -= 1.0f;
    }

    periods = quotient;

    if (periods != 0)
    {
        return key - (float)periods * span;
    }

    return key;
}

/**
 * @brief Return the key storage.
 * @return Key array, or null.
 */
BootTrackKey171680* BootClass171680::get_keys()
{
    return key_array;
}

/** @brief Leave the keyframe uninitialized. */
BootTrackKey171680::BootTrackKey171680()
{
}

/**
 * @brief Adjust a scalar key by whole spans determined from the endpoint records.
 * @param key Scalar key whose normalized span quotient must fit in a signed word.
 * @return Key minus the computed number of endpoint spans, or the key for zero spans.
 */
float BootClass171A70::wrap_key(float key) const
{
    s32 last_index = state.key_count - 1;
    BootTrackKey171A70* entries = key_array;
    BootTrackKey171A70* last = entries + last_index;
    float first = entries[0].key;
    float span = last->key - first;
    float quotient = (key - first) / span;
    s32 periods;

    if (quotient < 0.0f)
    {
        quotient -= 1.0f;
    }

    periods = quotient;

    if (periods != 0)
    {
        return key - (float)periods * span;
    }

    return key;
}

/**
 * @brief Read the vector value associated with the first exactly equal key.
 * @param track Receiver with 32-byte records, valid when its count is positive.
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A track_171A70_find_key_value(BootState1F47F0* track, float key)
{
    s32 index;

    for (index = 0; index < track->count; index++)
    {
        if (key == track->entries[index].key)
        {
            BootKeyEntry32* entry = track->entries + index;
            return *reinterpret_cast<const FieldVec4A*>(entry->value);
        }
    }

    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Return the last-to-first key difference, or zero below two records.
 * @return Difference between the last and first scalar keys, or zero.
 */
float BootClass171A70::get_key_span() const
{
    s32 last_index;
    BootTrackKey171A70* last_entry;

    if (state.key_count < 2)
    {
        return 0.0f;
    }

    last_index = state.key_count - 1;
    last_entry = key_array + last_index;
    return last_entry->key - key_array[0].key;
}

/**
 * @brief Test whether the 32-byte record array contains an exactly equal key.
 * @param key Scalar key to find.
 * @return One for an equal key, or zero when none is present.
 */
s32 BootClass171A70::has_key(float key) const
{
    s16 count = state.key_count;
    s32 index;

    for (index = 0; index < count; index++)
    {
        if (key == key_array[index].key)
        {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Bind external 32-byte records and cache their first-to-last key span.
 * @param count Positive entry count representable in the receiver count fields.
 * @param entries External storage containing the specified number of entries.
 */
void BootClass171A70::bind_keys(s32 count, BootTrackKey171A70* entries)
{
    s32 last_index = count - 1;
    BootTrackKey171A70* last;
    state.external_keys = 1;
    key_array = entries;
    state.key_capacity = count;
    state.key_count = count;
    last = key_array + last_index;
    state.span = last->key - key_array[0].key;
}

/** @brief Leave the keyframe uninitialized. */
BootTrackKey171A70::BootTrackKey171A70()
{
}
