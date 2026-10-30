#include "include_asm.h"
#include "clamp.h"
#include "vu0.h"
#include "overlays/lib/vector.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/boot/text_001EEC80.h"
#include "overlays/boot/resident.h"

extern "C" {

extern BootTrackPool<BootPooledVectorCurveTrack>* g_vector_curve_track_pool;
extern BootTrackPool<BootPooledVectorTrack>* g_vector_track_pool;
extern float D_001B668C;
}

/**
 * @brief Evaluate the segment at a key.
 * @param key Evaluation key.
 * @return Value at the key.
 */
FieldVec4B BootVectorSegment::evaluate(float key) const
{
    return interpolate(key);
}

/**
 * @brief BootTrack's slot 0x24, between append_key and replace_key; every family inherits it and none overrides it, so
 * its purpose is unknown. It does nothing, as Lib's copy (0x429850) does.
 * @param track Track; unused.
 */
void track_default_func_slot24(void* track)
{
}

/** @brief Delete the track; pooled tracks override this to return to their pool. */
void BootFloatCurveTrackBase::release()
{
    delete this;
}

/**
 * @brief BootTrack's append_key (slot 0x20), which the families' base classes inherit; it does nothing.
 * @param track Track; unused.
 * @return Zero.
 */
s32 track_default_append_key(void* track)
{
    return 0;
}

/**
 * @brief BootTrack's replace_key (slot 0x28), which the families' base classes inherit; it does nothing.
 * @param track Track; unused.
 * @return Zero.
 */
s32 track_default_replace_key(void* track)
{
    return 0;
}

/**
 * @brief BootTrack's insert_key (slot 0x2C), which the families' base classes inherit; it does nothing.
 * @param track Track; unused.
 * @return Zero.
 */
s32 track_default_insert_key(void* track)
{
    return 0;
}

/**
 * @brief BootTrack's read_key (slot 0x30), which the families' base classes inherit; it does nothing.
 * @param track Track; unused.
 * @return Zero.
 */
s32 track_default_read_key(void* track)
{
    return 0;
}

/**
 * @brief BootTrack's set_single_key (slot 0x34), which the families' base classes inherit; it does nothing.
 * @param track Track; unused.
 */
void track_default_set_single_key(void* track)
{
}

/**
 * @brief BootTrack's reset_keys (slot 0x38), which the families' base classes inherit; it does nothing.
 * @param track Track; unused.
 */
void track_default_reset_keys(void* track)
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
 */
void BootPooledVectorCurveTrack::return_to_pool()
{
    free_keys();
    vector_curve_track_pool_free(g_vector_curve_track_pool, this);
}

/**
 * @brief Evaluate the segment at a key.
 * @param key Evaluation key.
 * @return Value at the key.
 */
float BootFloatSegment::evaluate(float key) const
{
    return interpolate(key);
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
 */
void BootPooledVectorTrack::return_to_pool()
{
    free_keys();
    vector_track_pool_free(g_vector_track_pool, this);
}

/** @brief Clear the last sampled value, then reset the key state. */
void BootVectorCurveTrack::reset_state()
{
    last_value = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    BootVectorCurveTrackBase::reset_state();
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

    if (state.search_index >= state.key_capacity)
    {
        state.search_index = 0;
    }

    if (state.key_count == 1 && (!(key < static_cast<BootVectorCurveTrackKey*>(key_array)[0].value.w) || state.before_mode != BOOT_TRACK_END_USE_PRE_START_KEY))
    {
        return *reinterpret_cast<FieldVec4A*>(&static_cast<BootVectorCurveTrackKey*>(key_array)[0].value);
    }

    extrapolate = 0;

    if (key < static_cast<BootVectorCurveTrackKey*>(key_array)[0].value.w && state.before_mode == BOOT_TRACK_END_USE_PRE_START_KEY)
    {
        upper = 0;
        wrapped_key = key;
        lower = -1;
    }
    else
    {
        wrapped_key = update_cycle_count(key);

        if (state.cycle_count)
        {
            if (state.before_mode == BOOT_TRACK_END_HOLD && state.cycle_count < 0)
            {
                return *reinterpret_cast<FieldVec4A*>(&static_cast<BootVectorCurveTrackKey*>(key_array)[0].value);
            }

            if (state.after_mode == BOOT_TRACK_END_HOLD && state.cycle_count > 0)
            {
                return *reinterpret_cast<FieldVec4A*>(&static_cast<BootVectorCurveTrackKey*>(key_array)[state.key_count - 1].value);
            }
        }

        extrapolate = find_surrounding_keys(wrapped_key, &lower, &upper);

        if (extrapolate)
        {
            wrapped_key = key;
        }
    }

    if (!extrapolate)
    {
        if (state.segment_lower != lower || state.segment_upper != upper)
        {
            state.segment_lower = lower;
            state.segment_upper = upper;
            BootVectorCurveTrackKey* first = lower >= 0 ? static_cast<BootVectorCurveTrackKey*>(key_array) + lower : &single_key;
            s32 last = state.key_count - 1;

            if (upper == last && ((!(key < static_cast<BootVectorCurveTrackKey*>(key_array)[0].value.w) && state.after_mode == BOOT_TRACK_END_CYCLE_TO_FIRST) ||
                                  (key < static_cast<BootVectorCurveTrackKey*>(key_array)[0].value.w && state.before_mode == BOOT_TRACK_END_CYCLE_TO_FIRST)))
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

        result = curve_segment.interpolate(wrapped_key);

        if (state.cycle_count && ((state.before_mode == BOOT_TRACK_END_OFFSET_CYCLE && state.cycle_count < 0) ||
            (state.after_mode == BOOT_TRACK_END_OFFSET_CYCLE && state.cycle_count > 0)))
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
 * @param output Receives the rate.
 */
void BootVectorCurveTrack::get_value_rate(FieldVec4B* output) const
{
    *output = *reinterpret_cast<const FieldVec4A*>(&value_rate);
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

/** @brief Clear the last sampled value, then reset the key state. */
void BootFloatCurveTrack::reset_state()
{
    last_value = 0.0f;
    BootFloatCurveTrackBase::reset_state();
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
 * @param output Receives the rate.
 */
void BootFloatCurveTrack::get_value_rate(float* output) const
{
    *output = value_rate;
}

/**
 * @brief Return the difference between the last and first key values.
 * @param output Receives the difference; left alone when there are no keys.
 */
void BootFloatCurveTrack::get_end_delta(float* output) const
{
    if (key_array != 0)
    {
        *output = key_array[state.key_count - 1].value - key_array[0].value;
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
 * @brief Set the segment from the values, tangents and keys at its two ends.
 * @param from_value Value at the start key.
 * @param from_tangent Tangent at the start key.
 * @param to_value Value at the end key.
 * @param to_tangent Tangent at the end key.
 * @param from_key Key the segment starts at.
 * @param to_key Key the segment ends at.
 */
void BootFloatSegmentBase::set_endpoints(const float* from_value, const float* from_tangent, const float* to_value, const float* to_tangent, float from_key,
                                         float to_key)
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

/** @brief Clear the last sampled value, then reset the key state. */
void BootVectorTrack::reset_state()
{
    last_value = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    BootVectorTrackBase::reset_state();
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

    if (state.search_index >= state.key_capacity)
    {
        state.search_index = 0;
    }

    if (state.key_count == 1 && (!(key < key_array[0].value.w) || state.before_mode != BOOT_TRACK_END_USE_PRE_START_KEY))
    {
        return *reinterpret_cast<FieldVec4A*>(&key_array[0].value);
    }

    if (key < key_array[0].value.w && state.before_mode == BOOT_TRACK_END_USE_PRE_START_KEY)
    {
        upper = 0;
        wrapped_key = key;
        lower = -1;
    }
    else
    {
        wrapped_key = update_cycle_count(key);

        if (state.before_mode == BOOT_TRACK_END_HOLD && state.cycle_count < 0)
        {
            return *reinterpret_cast<FieldVec4A*>(&key_array[0].value);
        }

        if (state.after_mode == BOOT_TRACK_END_HOLD && state.cycle_count > 0)
        {
            return *reinterpret_cast<FieldVec4A*>(&key_array[state.key_count - 1].value);
        }

        extrapolate = find_surrounding_keys(wrapped_key, &lower, &upper);

        if (extrapolate)
        {
            wrapped_key = key;
        }
    }

    if (state.segment_lower != lower || state.segment_upper != upper)
    {
        state.segment_lower = lower;
        state.segment_upper = upper;
        BootVectorTrackKey* first = lower >= 0 ? key_array + lower : &single_key;
        sample_history.reset();
        sample_history.push_sample(first->value.w, reinterpret_cast<const FieldVec4A*>(&first->value));
        s32 last = state.key_count - 1;
        // Keep a separate index for the upper key to preserve register allocation.
        s32 upper_index = upper;

        if (upper_index == last && ((!(key < key_array[0].value.w) && state.after_mode == BOOT_TRACK_END_CYCLE_TO_FIRST) ||
            (key < key_array[0].value.w && state.before_mode == BOOT_TRACK_END_CYCLE_TO_FIRST)))
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

    if ((state.before_mode == BOOT_TRACK_END_OFFSET_CYCLE && state.cycle_count < 0) ||
        (state.after_mode == BOOT_TRACK_END_OFFSET_CYCLE && state.cycle_count > 0))
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
 * @param output Receives the rate.
 */
void BootVectorTrack::get_value_rate(FieldVec4B* output) const
{
    *output = *reinterpret_cast<const FieldVec4A*>(&value_rate);
}

/** @brief Clear the last sampled value, then reset the key state. */
void BootFloatTrack::reset_state()
{
    last_value = 0.0f;
    BootFloatTrackBase::reset_state();
}

/**
 * @brief Return the difference between the last and first key values.
 * @param output Receives the difference; left alone when there are no keys.
 */
void BootFloatTrack::get_end_delta(float* output) const
{
    if (key_array != 0)
    {
        *output = key_array[state.key_count - 1].value - key_array[0].value;
    }
}

/**
 * @brief Return how fast the value changed at the last sample, per second.
 * @param output Receives the rate.
 */
void BootFloatTrack::get_value_rate(float* output) const
{
    *output = value_rate;
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
    values[next_index] = *value;
    keys[next_index] = key;

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
    reset();
}

/** @brief Forget the stored samples. */
void BootClass171B20::reset()
{
    sample_count = 0;
    next_index = 0;
    unk14 = 0;
    unk18 = 0;
}

/** @brief Reset the record. */
BootVectorHistoryBase::BootVectorHistoryBase()
{
    reset();
}

/** @brief Forget the stored samples. */
void BootVectorHistoryBase::reset()
{
    sample_count = 0;
    next_index = 0;
    unk14 = 0;
    unk18 = 0;
}

/** @brief Reset the record. */
BootFloatHistoryBase::BootFloatHistoryBase()
{
    reset();
}

/** @brief Forget the stored samples. */
void BootFloatHistoryBase::reset()
{
    sample_count = 0;
    next_index = 0;
    unk08 = 0;
    unk0C = 0;
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
    state.segment_lower = -1;
    state.segment_upper = -1;
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

    state.segment_lower = -1;
    state.segment_upper = -1;
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
BootFloatQuaternionTrackBase::~BootFloatQuaternionTrackBase()
{
    free_keys();
}

/** @brief Delete the key storage unless it is external, and clear the key pointer. */
void BootFloatQuaternionTrackBase::free_keys()
{
    if (!state.external_keys)
    {
        delete[] key_array;
    }

    key_array = 0;
}

/**
 * @brief Normalize a key across the cached span and store its signed period count.
 * @param key Key whose period count is representable as a signed 32-bit integer.
 * @return Normalized key, with odd-period reflection selected by the control fields.
 */
float BootVectorCurveTrackBase::update_cycle_count(float key)
{
    float first = static_cast<BootVectorCurveTrackKey*>(key_array)[0].value.w;
    float quotient = (key - first) / state.span;

    if (key < first)
    {
        quotient -= 1.0f;
    }

    state.cycle_count = quotient;

    if (state.cycle_count)
    {
        float result = key - (float)state.cycle_count * state.span;

        if ((state.before_mode == BOOT_TRACK_END_PING_PONG && state.cycle_count < 0) || (state.after_mode == BOOT_TRACK_END_PING_PONG && state.cycle_count > 0))
        {
            s32 last_index = state.key_count - 1;
            BootVectorCurveTrackKey* last_entry = static_cast<BootVectorCurveTrackKey*>(key_array) + last_index;
            float last = last_entry->value.w;

            if (state.cycle_count & 1)
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
 * @param key Key to place.
 * @param lower Receives the lower entry index.
 * @param upper Receives the upper entry index.
 * @return One when the active end mode extends the first or last segment, otherwise zero.
 */
u8 BootVectorCurveTrackBase::find_surrounding_keys(float key, s32* lower, s32* upper)
{
    s32 index;
    s32 count;
    s32 next;

    if (state.extends_segment)
    {
        if (state.before_mode == BOOT_TRACK_END_EXTEND_SEGMENT && state.cycle_count < 0)
        {
            *lower = 0;
            *upper = 1;
            state.search_index = 0;
            return 1;
        }

        if (state.after_mode == BOOT_TRACK_END_EXTEND_SEGMENT && state.cycle_count > 0)
        {
            *lower = state.key_count - 2;
            *upper = state.key_count - 1;
            state.search_index = state.key_count - 2;
            return 1;
        }
    }

    index = state.search_index;
    count = state.key_count;

    while (index > 0 && key < static_cast<BootVectorCurveTrackKey*>(key_array)[index].value.w)
    {
        index--;
    }

    index = clamp_low(index, 0);

    while ((next = index + 1) < count && !(key < static_cast<BootVectorCurveTrackKey*>(key_array)[next].value.w))
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

    state.search_index = index;
    return 0;
}
/** @brief Release the keyframe storage. */
BootVectorCurveTrackBase::~BootVectorCurveTrackBase()
{
    free_keys();
}

/**
 * @brief Reset 48-byte record storage, counts, packed controls, and cached indices.
 */
void BootVectorCurveTrackBase::reset_state()
{
    static_cast<BootVectorCurveTrackKey*>(key_array) = 0;
    state.before_mode = BOOT_TRACK_END_CYCLE;
    state.after_mode = BOOT_TRACK_END_CYCLE;
    state.key_capacity = 0;
    state.key_count = 0;
    state.search_index = -1;
    state.cycle_count = 0;
    state.segment_lower = -1;
    state.segment_upper = -1;
    state.extends_segment = 0;
    state.external_keys = 0;
}

/**
 * @brief Bind external 48-byte records and cache their first-to-last key span.
 * @param count Positive entry count representable in the receiver count fields.
 * @param entries External storage containing the specified number of entries.
 */
void BootVectorCurveTrackBase::bind_keys(s32 count, BootVectorCurveTrackKey* entries)
{
    s32 last_index = count - 1;
    BootVectorCurveTrackKey* last;
    state.external_keys = 1;
    static_cast<BootVectorCurveTrackKey*>(key_array) = entries;
    state.key_capacity = count;
    state.key_count = count;
    last = static_cast<BootVectorCurveTrackKey*>(key_array) + last_index;
    state.span = last->value.w - static_cast<BootVectorCurveTrackKey*>(key_array)[0].value.w;
}

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param value Value to store, truncated to four bits.
 */
void BootVectorCurveTrackBase::set_before_mode(u32 value)
{
    state.before_mode = value;
    state.extends_segment = state.before_mode == BOOT_TRACK_END_EXTEND_SEGMENT || state.after_mode == BOOT_TRACK_END_EXTEND_SEGMENT;
}

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param value Value to store, truncated to four bits.
 */
void BootVectorCurveTrackBase::set_after_mode(u32 value)
{
    state.after_mode = value;
    state.extends_segment = state.before_mode == BOOT_TRACK_END_EXTEND_SEGMENT || state.after_mode == BOOT_TRACK_END_EXTEND_SEGMENT;
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
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 * @return Zero.
 */
s32 BootVectorCurveTrackBase::on_append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return 0;
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @return Zero.
 */
s32 BootVectorCurveTrackBase::on_replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return 0;
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @return Zero.
 */
s32 BootVectorCurveTrackBase::on_insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return 0;
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 */
void BootVectorCurveTrackBase::on_set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
}

/**
 * @brief Test whether the 48-byte record array contains an exactly equal key.
 * @param key Scalar key to find.
 * @return One for an equal key, or zero when none is present.
 */
s32 BootVectorCurveTrackBase::has_key(float key) const
{
    s16 count = state.key_count;
    s32 index;

    for (index = 0; index < count; index++)
    {
        if (key == static_cast<BootVectorCurveTrackKey*>(key_array)[index].value.w)
        {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Return a zero vector; the track's value when it has no keys.
 * @return Zero vector.
 */
FieldVec4A BootVectorCurveTrackBase::get_zero_value() const
{
    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Return the last-to-first key difference, or zero below two records.
 * @return Difference between the last and first scalar keys, or zero.
 */
float BootVectorCurveTrackBase::get_key_span() const
{
    s32 last_index;
    BootVectorCurveTrackKey* last_entry;

    if (state.key_count < 2)
    {
        return 0.0f;
    }

    last_index = state.key_count - 1;
    last_entry = static_cast<BootVectorCurveTrackKey*>(key_array) + last_index;
    return last_entry->value.w - static_cast<BootVectorCurveTrackKey*>(key_array)[0].value.w;
}

/**
 * @brief Read the vector value associated with the first exactly equal key.
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A BootVectorCurveTrackBase::find_key_value(float key)
{
    s32 index;

    for (index = 0; index < state.key_count; index++)
    {
        if (key == static_cast<BootVectorCurveTrackKey*>(key_array)[index].value.w)
        {
            BootVectorCurveTrackKey* entry = static_cast<BootVectorCurveTrackKey*>(key_array) + index;
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
void BootVectorCurveTrackBase::evaluate(float key, FieldVec4B* output)
{
    *output = sample(key);
}

/**
 * @brief Adjust a scalar key by whole spans determined from the endpoint records.
 * @param key Scalar key whose normalized span quotient must fit in a signed word.
 * @return Key minus the computed number of endpoint spans, or the key for zero spans.
 */
float BootVectorCurveTrackBase::wrap_key(float key) const
{
    s32 last_index = state.key_count - 1;
    BootVectorCurveTrackKey* entries = static_cast<BootVectorCurveTrackKey*>(key_array);
    BootVectorCurveTrackKey* last = entries + last_index;
    float first = entries[0].value.w;
    float span = last->value.w - first;
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
BootVectorCurveTrackKey* BootVectorCurveTrackBase::get_keys()
{
    return static_cast<BootVectorCurveTrackKey*>(key_array);
}

/** @brief Delete the key storage unless it is external, and clear the key pointer. */
void BootVectorCurveTrackBase::free_keys()
{
    if (!state.external_keys)
    {
        delete[] static_cast<BootVectorCurveTrackKey*>(key_array);
    }

    key_array = 0;
}

/** @brief Release the keyframe storage. */
BootFloatCurveTrackBase::~BootFloatCurveTrackBase()
{
    free_keys();
}

/**
 * @brief Reset array storage, counts, packed controls, and cached indices.
 */
void BootFloatCurveTrackBase::reset_state()
{
    key_array = 0;
    state.before_mode = BOOT_TRACK_END_CYCLE;
    state.after_mode = BOOT_TRACK_END_CYCLE;
    state.key_capacity = 0;
    state.key_count = 0;
    state.search_index = -1;
    state.cycle_count = 0;
    state.segment_lower = -1;
    state.segment_upper = -1;
    state.extends_segment = 0;
    state.external_keys = 0;
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
    state.extends_segment = state.before_mode == BOOT_TRACK_END_EXTEND_SEGMENT || state.after_mode == BOOT_TRACK_END_EXTEND_SEGMENT;
}

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param value Value to store, truncated to four bits.
 */
void BootFloatCurveTrackBase::set_after_mode(u32 value)
{
    state.after_mode = value;
    state.extends_segment = state.before_mode == BOOT_TRACK_END_EXTEND_SEGMENT || state.after_mode == BOOT_TRACK_END_EXTEND_SEGMENT;
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
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key the keyframe sits at.
 * @return Zero.
 */
s32 BootFloatCurveTrackBase::on_append_key(const float* value, const float* in_tangent, const float* out_tangent, float key)
{
    return 0;
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @return Zero.
 */
s32 BootFloatCurveTrackBase::on_replace_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent)
{
    return 0;
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @return Zero.
 */
s32 BootFloatCurveTrackBase::on_insert_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent)
{
    return 0;
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key the keyframe sits at.
 */
void BootFloatCurveTrackBase::on_set_single_key(const float* value, const float* in_tangent, const float* out_tangent, float key)
{
}

/**
 * @brief Write a zero value; the track's value when it has no keys.
 * @return Zero.
 */
float BootFloatCurveTrackBase::get_zero_value() const
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

/** @brief Delete the key storage unless it is external, and clear the key pointer. */
void BootFloatCurveTrackBase::free_keys()
{
    if (!state.external_keys)
    {
        delete[] key_array;
    }

    key_array = 0;
}

/** @brief Release the keyframe storage. */
BootClass1718C0::~BootClass1718C0()
{
    free_keys();
}

/**
 * @brief Reset array storage, counts, packed controls, and cached indices.
 */
void BootClass1718C0::reset_state()
{
    key_array = 0;
    state.before_mode = BOOT_TRACK_END_CYCLE;
    state.after_mode = BOOT_TRACK_END_CYCLE;
    state.key_capacity = 0;
    state.key_count = 0;
    state.search_index = -1;
    state.cycle_count = 0;
    state.segment_lower = -1;
    state.segment_upper = -1;
    state.extends_segment = 0;
    state.external_keys = 0;
}

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param value Value to store, truncated to four bits.
 */
void BootClass1718C0::set_before_mode(u32 value)
{
    state.before_mode = value;
    state.extends_segment = state.before_mode == BOOT_TRACK_END_EXTEND_SEGMENT || state.after_mode == BOOT_TRACK_END_EXTEND_SEGMENT;
}

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param value Value to store, truncated to four bits.
 */
void BootClass1718C0::set_after_mode(u32 value)
{
    state.after_mode = value;
    state.extends_segment = state.before_mode == BOOT_TRACK_END_EXTEND_SEGMENT || state.after_mode == BOOT_TRACK_END_EXTEND_SEGMENT;
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
 * @brief Return a zero vector; the track's value when it has no keys.
 * @return Zero vector.
 */
FieldVec4A BootClass1718C0::get_zero_value() const
{
    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
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
 * @return Key array, or null.
 */
BootTrackKey1718C0* BootClass1718C0::get_keys()
{
    return key_array;
}

/** @brief Delete the key storage unless it is external, and clear the key pointer. */
void BootClass1718C0::free_keys()
{
    if (!state.external_keys)
    {
        delete[] key_array;
    }

    key_array = 0;
}

/**
 * @brief Normalize a key across the cached span and store its signed period count.
 * @param key Key whose period count is representable as a signed 32-bit integer.
 * @return Normalized key, with odd-period reflection selected by the control fields.
 */
float BootVectorTrackBase::update_cycle_count(float key)
{
    float first = key_array[0].value.w;
    float quotient = (key - first) / state.span;

    if (key < first)
    {
        quotient -= 1.0f;
    }

    state.cycle_count = quotient;

    if (state.cycle_count)
    {
        float result = key - (float)state.cycle_count * state.span;

        if ((state.before_mode == BOOT_TRACK_END_PING_PONG && state.cycle_count < 0) || (state.after_mode == BOOT_TRACK_END_PING_PONG && state.cycle_count > 0))
        {
            s32 last_index = state.key_count - 1;
            BootVectorTrackKey* last_entry = key_array + last_index;
            float last = last_entry->value.w;

            if (state.cycle_count & 1)
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
 * @param key Key to place.
 * @param lower Receives the lower entry index.
 * @param upper Receives the upper entry index.
 * @return One when the active end mode extends the first or last segment, otherwise zero.
 */
u8 BootVectorTrackBase::find_surrounding_keys(float key, s32* lower, s32* upper)
{
    s32 index;
    s32 count;
    s32 next;

    if (state.extends_segment)
    {
        if (state.before_mode == BOOT_TRACK_END_EXTEND_SEGMENT && state.cycle_count < 0)
        {
            *lower = 0;
            *upper = 1;
            state.search_index = 0;
            return 1;
        }

        if (state.after_mode == BOOT_TRACK_END_EXTEND_SEGMENT && state.cycle_count > 0)
        {
            *lower = state.key_count - 2;
            *upper = state.key_count - 1;
            state.search_index = state.key_count - 2;
            return 1;
        }
    }

    index = state.search_index;
    count = state.key_count;

    while (index > 0 && key < static_cast<BootVectorTrackKey*>(key_array)[index].value.w)
    {
        index--;
    }

    index = clamp_low(index, 0);

    while ((next = index + 1) < count && !(key < static_cast<BootVectorTrackKey*>(key_array)[next].value.w))
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

    state.search_index = index;
    return 0;
}
/** @brief Release the keyframe storage. */
BootVectorTrackBase::~BootVectorTrackBase()
{
    free_keys();
}

/**
 * @brief Reset vector-key storage, counts, control fields, and cached indices.
 */
void BootVectorTrackBase::reset_state()
{
    key_array = 0;
    state.before_mode = BOOT_TRACK_END_CYCLE;
    state.after_mode = BOOT_TRACK_END_CYCLE;
    state.key_capacity = 0;
    state.key_count = 0;
    state.search_index = -1;
    state.cycle_count = 0;
    state.segment_lower = -1;
    state.segment_upper = -1;
    state.extends_segment = 0;
    state.external_keys = 0;
}

/**
 * @brief Bind external vector-key storage and cache its first-to-last key span.
 * @param count Positive entry count representable in the receiver count fields.
 * @param entries External storage containing the specified number of entries.
 */
void BootVectorTrackBase::bind_keys(s32 count, BootVectorTrackKey* entries)
{
    s32 last_index = count - 1;
    BootVectorTrackKey* last;
    state.external_keys = 1;
    key_array = entries;
    state.key_capacity = count;
    state.key_count = count;
    last = key_array + last_index;
    state.span = last->value.w - key_array[0].value.w;
}

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param value Value to store, truncated to four bits.
 */
void BootVectorTrackBase::set_before_mode(u32 value)
{
    state.before_mode = value;
    state.extends_segment = state.before_mode == BOOT_TRACK_END_EXTEND_SEGMENT || state.after_mode == BOOT_TRACK_END_EXTEND_SEGMENT;
}

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param value Value to store, truncated to four bits.
 */
void BootVectorTrackBase::set_after_mode(u32 value)
{
    state.after_mode = value;
    state.extends_segment = state.before_mode == BOOT_TRACK_END_EXTEND_SEGMENT || state.after_mode == BOOT_TRACK_END_EXTEND_SEGMENT;
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
 * @param key Key to find.
 * @return One if a key matches, or zero otherwise.
 */
s32 BootVectorTrackBase::has_key(float key) const
{
    s16 count = state.key_count;
    s32 index;

    for (index = 0; index < count; index++)
    {
        if (key == key_array[index].value.w)
        {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Return a zero vector; the track's value when it has no keys.
 * @return Zero vector.
 */
FieldVec4A BootVectorTrackBase::get_zero_value() const
{
    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Compute the span between the last and first vector-entry keys.
 * @return Key span, or zero when fewer than two entries exist.
 */
float BootVectorTrackBase::get_key_span() const
{
    BootVectorTrackKey* last;

    if (state.key_count < 2)
    {
        return 0.0f;
    }

    last = key_array + (state.key_count - 1);
    return last->value.w - key_array[0].value.w;
}

/**
 * @brief Read the vector value associated with the first exactly equal key.
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A BootVectorTrackBase::find_key_value(float key)
{
    s32 index;

    for (index = 0; index < state.key_count; index++)
    {
        if (key == key_array[index].value.w)
        {
            BootVectorTrackKey* entry = key_array + index;
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
 * @param key Key to wrap using truncation after adjusting negative positions.
 * @return Key with the computed whole spans subtracted.
 */
float BootVectorTrackBase::wrap_key(float key) const
{
    BootVectorTrackKey* last = key_array + (state.key_count - 1);
    float first = key_array[0].value.w;
    float span = last->value.w - first;
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
BootVectorTrackKey* BootVectorTrackBase::get_keys()
{
    return key_array;
}

/** @brief Delete the key storage unless it is external, and clear the key pointer. */
void BootVectorTrackBase::free_keys()
{
    if (!state.external_keys)
    {
        delete[] key_array;
    }

    key_array = 0;
}

/** @brief Release the keyframe storage. */
BootFloatTrackBase::~BootFloatTrackBase()
{
    free_keys();
}

/**
 * @brief Reset float-entry storage, counts, control fields, and cached indices.
 */
void BootFloatTrackBase::reset_state()
{
    key_array = 0;
    state.before_mode = BOOT_TRACK_END_CYCLE;
    state.after_mode = BOOT_TRACK_END_CYCLE;
    state.key_capacity = 0;
    state.key_count = 0;
    state.search_index = -1;
    state.cycle_count = 0;
    state.segment_lower = -1;
    state.segment_upper = -1;
    state.extends_segment = 0;
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
    state.extends_segment = state.before_mode == BOOT_TRACK_END_EXTEND_SEGMENT || state.after_mode == BOOT_TRACK_END_EXTEND_SEGMENT;
}

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param value Value to store, truncated to four bits.
 */
void BootFloatTrackBase::set_after_mode(u32 value)
{
    state.after_mode = value;
    state.extends_segment = state.before_mode == BOOT_TRACK_END_EXTEND_SEGMENT || state.after_mode == BOOT_TRACK_END_EXTEND_SEGMENT;
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
 * @return Zero.
 */
float BootFloatTrackBase::get_zero_value() const
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

/** @brief Delete the key storage unless it is external, and clear the key pointer. */
void BootFloatTrackBase::free_keys()
{
    if (!state.external_keys)
    {
        delete[] key_array;
    }

    key_array = 0;
}

/** @brief Release the keyframe storage. */
BootQuaternionTrackBase::~BootQuaternionTrackBase()
{
    free_keys();
}

/** @brief Delete the key storage unless it is external, and clear the key pointer. */
void BootQuaternionTrackBase::free_keys()
{
    if (!state.external_keys)
    {
        delete[] key_array;
    }

    key_array = 0;
}

/** @brief Release the keyframe storage. */
BootQuaternionCurveTrackBase::~BootQuaternionCurveTrackBase()
{
    free_keys();
}

/** @brief Delete the key storage unless it is external, and clear the key pointer. */
void BootQuaternionCurveTrackBase::free_keys()
{
    if (!state.external_keys)
    {
        delete[] key_array;
    }

    key_array = 0;
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
BootQuaternionCurveTrackBase::BootQuaternionCurveTrackBase()
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
 * @param key Key to find.
 * @return Associated value, or zero when no key matches.
 */
float BootFloatTrackBase::find_key_value(float key)
{
    s32 index;

    for (index = 0; index < state.key_count; index++)
    {
        if (key == key_array[index].key)
        {
            BootFloatTrackKey* entry = key_array + index;
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
 * @param value Key value.
 * @param key Key the keyframe sits at.
 */
void BootFloatTrackBase::set_single_key(const float* value, float key)
{
    on_set_single_key(value, key);
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param value Key value.
 * @param key Key the keyframe sits at.
 */
void BootFloatTrackBase::on_set_single_key(const float* value, float key)
{
}

/**
 * @brief Forward an indexed keyframe with a key to slot 0x70.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootFloatTrackBase::insert_key(s32 index, float key, const float* value)
{
    return on_insert_key(index, key, value);
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @return Zero.
 */
s32 BootFloatTrackBase::on_insert_key(s32 index, float key, const float* value)
{
    return 0;
}

/**
 * @brief Forward an indexed keyframe with a key to slot 0x6C.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootFloatTrackBase::replace_key(s32 index, float key, const float* value)
{
    return on_replace_key(index, key, value);
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @return Zero.
 */
s32 BootFloatTrackBase::on_replace_key(s32 index, float key, const float* value)
{
    return 0;
}

/**
 * @brief Forward a keyframe with a key to slot 0x68.
 * @param value Key value.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootFloatTrackBase::append_key(const float* value, float key)
{
    return on_append_key(value, key);
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param value Key value.
 * @param key Key the keyframe sits at.
 * @return Zero.
 */
s32 BootFloatTrackBase::on_append_key(const float* value, float key)
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
 * @param value Key value.
 * @param key Key the keyframe sits at.
 */
void BootVectorTrackBase::set_single_key(const FieldVec4A* value, float key)
{
    on_set_single_key(value, key);
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param value Key value.
 * @param key Key the keyframe sits at.
 */
void BootVectorTrackBase::on_set_single_key(const FieldVec4A* value, float key)
{
}

/**
 * @brief Forward to slot 0x70.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootVectorTrackBase::insert_key(s32 index, float key, const FieldVec4A* value)
{
    return on_insert_key(index, key, value);
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @return Zero.
 */
s32 BootVectorTrackBase::on_insert_key(s32 index, float key, const FieldVec4A* value)
{
    return 0;
}

/**
 * @brief Forward to slot 0x6C.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootVectorTrackBase::replace_key(s32 index, float key, const FieldVec4A* value)
{
    return on_replace_key(index, key, value);
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @return Zero.
 */
s32 BootVectorTrackBase::on_replace_key(s32 index, float key, const FieldVec4A* value)
{
    return 0;
}

/**
 * @brief Forward to slot 0x68.
 * @param value Key value.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootVectorTrackBase::append_key(const FieldVec4A* value, float key)
{
    return on_append_key(value, key);
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param value Key value.
 * @param key Key the keyframe sits at.
 * @return Zero.
 */
s32 BootVectorTrackBase::on_append_key(const FieldVec4A* value, float key)
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
    delete[] key_array;
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
 * @param key Scalar key whose normalized span quotient must fit in a signed word.
 * @return Key minus the computed number of endpoint spans, or the key for zero spans.
 */
float BootClass1718C0::wrap_key(float key) const
{
    s32 last_index = state.key_count - 1;
    BootTrackKey1718C0* entries = key_array;
    BootTrackKey1718C0* last = entries + last_index;
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
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A BootClass1718C0::find_key_value(float key)
{
    s32 index;

    for (index = 0; index < state.key_count; index++)
    {
        if (key == key_array[index].key)
        {
            BootTrackKey1718C0* entry = key_array + index;
            return *reinterpret_cast<const FieldVec4A*>(&entry->value);
        }
    }

    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Return the last-to-first key difference, or zero below two records.
 * @return Difference between the last and first scalar keys, or zero.
 */
float BootClass1718C0::get_key_span() const
{
    s32 last_index;
    BootTrackKey1718C0* last_entry;

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
s32 BootClass1718C0::has_key(float key) const
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
 * @brief Forward to slot 0x74.
 * @param value Key value.
 * @param key Key the keyframe sits at.
 */
void BootClass1718C0::set_single_key(const FieldVec4A* value, float key)
{
    on_set_single_key(value, key);
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param value Key value.
 * @param key Key the keyframe sits at.
 */
void BootClass1718C0::on_set_single_key(const FieldVec4A* value, float key)
{
}

/**
 * @brief Forward to slot 0x70.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootClass1718C0::insert_key(s32 index, float key, const FieldVec4A* value)
{
    return on_insert_key(index, key, value);
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @return Zero.
 */
s32 BootClass1718C0::on_insert_key(s32 index, float key, const FieldVec4A* value)
{
    return 0;
}

/**
 * @brief Forward to slot 0x6C.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootClass1718C0::replace_key(s32 index, float key, const FieldVec4A* value)
{
    return on_replace_key(index, key, value);
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @return Zero.
 */
s32 BootClass1718C0::on_replace_key(s32 index, float key, const FieldVec4A* value)
{
    return 0;
}

/**
 * @brief Forward to slot 0x68.
 * @param value Key value.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootClass1718C0::append_key(const FieldVec4A* value, float key)
{
    return on_append_key(value, key);
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param value Key value.
 * @param key Key the keyframe sits at.
 * @return Zero.
 */
s32 BootClass1718C0::on_append_key(const FieldVec4A* value, float key)
{
    return 0;
}

/**
 * @brief Bind external 32-byte records and cache their first-to-last key span.
 * @param count Positive entry count representable in the receiver count fields.
 * @param entries External storage containing the specified number of entries.
 */
void BootClass1718C0::bind_keys(s32 count, BootTrackKey1718C0* entries)
{
    s32 last_index = count - 1;
    BootTrackKey1718C0* last;
    state.external_keys = 1;
    key_array = entries;
    state.key_capacity = count;
    state.key_count = count;
    last = key_array + last_index;
    state.span = last->key - key_array[0].key;
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
BootFloatQuaternionTrackBase::BootFloatQuaternionTrackBase()
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
    set_before_mode(BOOT_TRACK_END_USE_PRE_START_KEY);
    single_key.value = *value;
    single_key.key = key;
}

/**
 * @brief Read either or both members of an indexed float entry.
 * @param index Nonnegative entry index, checked against capacity.
 * @param key Optional destination for the entry key.
 * @param value Optional destination for the entry value.
 * @param first Unused; float keys have no tangents.
 * @param second Unused; float keys have no tangents.
 * @return One for an available slot, or zero if storage is absent or the index is too large.
 */
s32 BootFloatKeyTrack::read_key(s32 index, float* key, float* value, float* first, float* second) const
{
    if (key_array == 0)
    {
        return 0;
    }

    if (index >= state.key_capacity)
    {
        return 0;
    }

    if (key != 0)
    {
        *key = key_array[index].key;
    }

    if (value != 0)
    {
        *value = key_array[index].value;
    }

    return 1;
}

/**
 * @brief Insert a float entry before an existing index and shift following entries.
 * @param index Nonnegative index less than the current count.
 * @param key Key associated with the entry.
 * @param value Entry value to copy.
 * @return One if inserted, or zero if storage is absent, full, or the index is too large.
 */
s32 BootFloatKeyTrack::on_insert_key(s32 index, float key, const float* value)
{
    s32 cursor;

    if (key_array == 0)
    {
        return 0;
    }

    if (index >= state.key_count)
    {
        return 0;
    }

    if (state.key_count >= state.key_capacity)
    {
        return 0;
    }

    for (cursor = state.key_count; cursor > index; cursor--)
    {
        BootFloatTrackKey* destination = &key_array[cursor];
        BootFloatTrackKey* source = &key_array[cursor - 1];
        destination->key = source->key;
        destination->value = source->value;
    }

    key_array[index].value = *value;
    key_array[index].key = key;

    if (index == state.key_count - 1)
    {
        state.span = key - key_array[0].key;
    }

    state.segment_lower = -1;
    state.segment_upper = -1;
    state.key_count++;
    return 1;
}

/**
 * @brief Replace an indexed float entry and update the span when it is the last entry.
 * @param index Nonnegative entry index, checked against capacity.
 * @param key Key associated with the entry.
 * @param value Entry value to copy.
 * @return One if stored, or zero if storage is absent or the index is outside capacity.
 */
s32 BootFloatKeyTrack::on_replace_key(s32 index, float key, const float* value)
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

    state.segment_lower = -1;
    state.segment_upper = -1;
    return 1;
}

/**
 * @brief Append a float entry and update the cached key span.
 * @param value Entry value to copy.
 * @param key Key associated with the entry.
 * @return One if appended, or zero if storage is absent or full.
 */
s32 BootFloatKeyTrack::on_append_key(const float* value, float key)
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
    state.segment_lower = -1;
    state.segment_upper = -1;
    state.key_count++;
    return 1;
}

/**
 * @brief Store a single keyframe in the cached value.
 * @param value Keyframe value.
 * @param key Key, stored in the value's fourth component.
 */
void BootVectorKeyTrack::on_set_single_key(const FieldVec4A* value, float key)
{
    set_before_mode(BOOT_TRACK_END_USE_PRE_START_KEY);
    single_key.value = *value;
    single_key.value.w = key;
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

    state.segment_lower = -1;
    state.segment_upper = -1;
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
    set_before_mode(BOOT_TRACK_END_USE_PRE_START_KEY);
    single_value = *value;
    single_key = key;
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

    state.segment_lower = -1;
    state.segment_upper = -1;
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

    state.segment_lower = -1;
    state.segment_upper = -1;
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
    state.segment_lower = -1;
    state.segment_upper = -1;
    state.key_count++;
    return 1;
}

/** @brief Reset to a single zero keyframe at key zero, then select the cycle end mode. */
void BootFloatTrack::reset_keys()
{
    float zero = 0.0f;
    on_set_single_key(&zero, 0.0f);
    set_before_mode(BOOT_TRACK_END_CYCLE);
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

    if (state.search_index >= state.key_capacity)
    {
        state.search_index = 0;
    }

    if (state.key_count == 1 && (!(key < key_array[0].key) || state.before_mode != BOOT_TRACK_END_USE_PRE_START_KEY))
    {
        return key_array[0].value;
    }

    if (key < key_array[0].key && state.before_mode == BOOT_TRACK_END_USE_PRE_START_KEY)
    {
        upper = 0;
        wrapped_key = key;
        lower = -1;
    }
    else
    {
        wrapped_key = update_cycle_count(key);

        if (state.before_mode == BOOT_TRACK_END_HOLD && state.cycle_count < 0)
        {
            return key_array[0].value;
        }

        if (state.after_mode == BOOT_TRACK_END_HOLD && state.cycle_count > 0)
        {
            return key_array[state.key_count - 1].value;
        }

        extrapolate = find_surrounding_keys(wrapped_key, &lower, &upper);

        if (extrapolate)
        {
            wrapped_key = key;
        }
    }

    if (state.segment_lower != lower || state.segment_upper != upper)
    {
        state.segment_lower = lower;
        state.segment_upper = upper;
        BootFloatTrackKey* first = lower >= 0 ? key_array + lower : &single_key;
        sample_history.sample_count = 0;
        sample_history.next_index = 0;
        sample_history.unk08 = 0;
        sample_history.unk0C = 0;
        sample_history.add_sample(first->key, first->value);
        s32 last = state.key_count - 1;
        // Keep a separate index for the upper key to preserve register allocation.
        s32 upper_index = upper;

        if (upper_index == last && ((!(key < key_array[0].key) && state.after_mode == BOOT_TRACK_END_CYCLE_TO_FIRST) ||
            (key < key_array[0].key && state.before_mode == BOOT_TRACK_END_CYCLE_TO_FIRST)))
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

    if ((state.before_mode == BOOT_TRACK_END_OFFSET_CYCLE && state.cycle_count < 0) ||
        (state.after_mode == BOOT_TRACK_END_OFFSET_CYCLE && state.cycle_count > 0))
    {
        float delta = key_array[state.key_count - 1].value - key_array[0].value;
        result += delta * state.cycle_count;
    }

    value_rate = (result - last_value) / D_001B6688;
    last_value = result;
    return result;
}

/** @brief Reset to a single zero keyframe at key zero, then select the cycle end mode. */
void BootVectorTrack::reset_keys()
{
    FieldVec4A zero(0.0f, 0.0f, 0.0f, 0.0f);
    on_set_single_key(&zero, 0.0f);
    set_before_mode(BOOT_TRACK_END_CYCLE);
}

/**
 * @brief Copy an indexed entry's key and values to the requested outputs.
 * @param index Nonnegative entry index, checked against capacity.
 * @param key Optional output for the entry key.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @return One if read, or zero if storage is absent or the index is outside capacity.
 */
s32 BootFloatCurveTrack::read_key(s32 index, float* key, float* value, float* in_tangent, float* out_tangent) const
{
    if (!key_array)
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

    if (in_tangent)
    {
        *in_tangent = key_array[index].in_tangent;
    }

    if (out_tangent)
    {
        *out_tangent = key_array[index].out_tangent;
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
    set_before_mode(BOOT_TRACK_END_USE_PRE_START_KEY);
    single_key.value = *value;
    single_key.in_tangent = *in_tangent;
    single_key.out_tangent = *out_tangent;
    single_key.key = key;
}

/**
 * @brief Insert three values and their key before an existing entry.
 * @param index Nonnegative insertion index, less than the current entry count.
 * @param key Key associated with the inserted entry.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @return One if inserted, or zero if storage, index, or remaining capacity is invalid.
 */
s32 BootFloatCurveTrack::insert_curve_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent)
{
    s32 cursor;

    if (!key_array)
    {
        return 0;
    }

    if (index >= state.key_count)
    {
        return 0;
    }

    if (state.key_count >= state.key_capacity)
    {
        return 0;
    }

    for (cursor = state.key_count; cursor > index; cursor--)
    {
        BootFloatCurveTrackKey* destination = &key_array[cursor];
        BootFloatCurveTrackKey* source = &key_array[cursor - 1];
        destination->key = source->key;
        destination->value = source->value;
        destination->in_tangent = source->in_tangent;
        destination->out_tangent = source->out_tangent;
    }

    key_array[index].value = *value;
    key_array[index].in_tangent = *in_tangent;
    key_array[index].out_tangent = *out_tangent;
    key_array[index].key = key;

    if (index == state.key_count - 1)
    {
        state.span = key - key_array[0].key;
    }

    state.key_count++;
    return 1;
}

/**
 * @brief Replace an indexed three-value entry and update the span for the last entry.
 * @param index Nonnegative entry index, checked against capacity.
 * @param key Key associated with the entry.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @return One if stored, or zero if storage is absent or the index is outside capacity.
 */
s32 BootFloatCurveTrack::replace_curve_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent)
{
    if (!key_array)
    {
        return 0;
    }

    if (index >= state.key_capacity)
    {
        return 0;
    }

    key_array[index].value = *value;
    key_array[index].in_tangent = *in_tangent;
    key_array[index].out_tangent = *out_tangent;
    key_array[index].key = key;

    if (index == state.key_count - 1)
    {
        state.span = key - key_array[0].key;
    }

    return 1;
}

/**
 * @brief Append three values and their key, updating the span and entry count.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key associated with the new entry.
 * @return One if appended, or zero if storage is absent or capacity is exhausted.
 */
s32 BootFloatCurveTrack::append_curve_key(const float* value, const float* in_tangent, const float* out_tangent, float key)
{
    if (!key_array)
    {
        return 0;
    }

    if (state.key_count >= state.key_capacity)
    {
        return 0;
    }

    key_array[state.key_count].value = *value;
    key_array[state.key_count].in_tangent = *in_tangent;
    key_array[state.key_count].out_tangent = *out_tangent;
    key_array[state.key_count].key = key;
    state.span = key - key_array[0].key;
    state.key_count++;
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

    if (state.search_index >= state.key_capacity)
    {
        state.search_index = 0;
    }

    if (state.key_count == 1 && (!(key < key_array[0].key) || state.before_mode != BOOT_TRACK_END_USE_PRE_START_KEY))
    {
        return key_array[0].value;
    }

    extrapolate = 0;

    if (key < key_array[0].key && state.before_mode == BOOT_TRACK_END_USE_PRE_START_KEY)
    {
        upper = 0;
        wrapped_key = key;
        lower = -1;
    }
    else
    {
        wrapped_key = update_cycle_count(key);

        if (state.cycle_count)
        {
            if (state.before_mode == BOOT_TRACK_END_HOLD && state.cycle_count < 0)
            {
                return key_array[0].value;
            }

            if (state.after_mode == BOOT_TRACK_END_HOLD && state.cycle_count > 0)
            {
                return key_array[state.key_count - 1].value;
            }
        }

        extrapolate = find_surrounding_keys(wrapped_key, &lower, &upper);

        if (extrapolate)
        {
            wrapped_key = key;
        }
    }

    if (!extrapolate)
    {
        if (state.segment_lower != lower || state.segment_upper != upper)
        {
            state.segment_lower = lower;
            state.segment_upper = upper;
            BootFloatCurveTrackKey* first = lower >= 0 ? key_array + lower : &single_key;
            s32 last = state.key_count - 1;

            if (upper == last && ((!(key < key_array[0].key) && state.after_mode == BOOT_TRACK_END_CYCLE_TO_FIRST) ||
                (key < key_array[0].key && state.before_mode == BOOT_TRACK_END_CYCLE_TO_FIRST)))
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

        result = curve_segment.interpolate(wrapped_key);

        if (state.cycle_count && ((state.before_mode == BOOT_TRACK_END_OFFSET_CYCLE && state.cycle_count < 0) ||
            (state.after_mode == BOOT_TRACK_END_OFFSET_CYCLE && state.cycle_count > 0)))
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
    set_before_mode(BOOT_TRACK_END_USE_PRE_START_KEY);
    single_key.value = *value;
    single_key.in_tangent = *in_tangent;
    single_key.out_tangent = *out_tangent;
    single_key.value.w = key;
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
void BootQuaternionCurveTrackBase::set_before_mode(u32 value)
{
    state.before_mode = value;
    state.extends_segment = state.before_mode == BOOT_TRACK_END_EXTEND_SEGMENT || state.after_mode == BOOT_TRACK_END_EXTEND_SEGMENT;
}

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param value Value to store, truncated to four bits.
 */
void BootQuaternionTrackBase::set_before_mode(u32 value)
{
    state.before_mode = value;
    state.extends_segment = state.before_mode == BOOT_TRACK_END_EXTEND_SEGMENT || state.after_mode == BOOT_TRACK_END_EXTEND_SEGMENT;
}

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param value Value to store, truncated to four bits.
 */
void BootFloatQuaternionTrackBase::set_before_mode(u32 value)
{
    state.before_mode = value;
    state.extends_segment = state.before_mode == BOOT_TRACK_END_EXTEND_SEGMENT || state.after_mode == BOOT_TRACK_END_EXTEND_SEGMENT;
}

/**
 * @brief Store a value and key in the two-entry history and count it, up to two.
 * @param value Value to store.
 * @param key Key to store.
 */
void BootClass171B70::push_sample(const FieldVec4A* value, float key)
{
    values[next_index] = *value;
    keys[next_index] = key;

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
 * @brief Store a value and key in the two-entry history and count it, up to two.
 * @param value Value to store.
 * @param key Key to store.
 */
void BootFloatHistory::push_sample(const float* value, float key)
{
    values[next_index] = *value;
    keys[next_index] = key;

    if (++next_index >= 2)
    {
        next_index = 0;
    }

    if (++sample_count > 2)
    {
        sample_count = 2;
    }
}

/** @brief Do nothing; the slot's purpose is unknown, and Lib's versions are empty too. */
void BootClass171B20::func_slot08()
{
}

/** @brief Do nothing; the slot's purpose is unknown, and Lib's versions are empty too. */
void BootVectorHistoryBase::func_slot08()
{
}

/** @brief Do nothing; the slot's purpose is unknown, and Lib's versions are empty too. */
void BootFloatHistoryBase::func_slot08()
{
}

/**
 * @brief Reset array storage, counts, packed controls, and cached indices.
 */
void BootFloatQuaternionTrackBase::reset_state()
{
    key_array = 0;
    state.before_mode = BOOT_TRACK_END_CYCLE;
    state.after_mode = BOOT_TRACK_END_CYCLE;
    state.key_capacity = 0;
    state.key_count = 0;
    state.search_index = -1;
    state.cycle_count = 0;
    state.segment_lower = -1;
    state.segment_upper = -1;
    state.extends_segment = 0;
    state.external_keys = 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param count Requested keyframe count.
 */
void BootFloatQuaternionTrackBase::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] key_array;
    key_array = new (0) BootFloatQuaternionTrackKey[count];
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
void BootFloatQuaternionTrackBase::set_after_mode(u32 value)
{
    state.after_mode = value;
    state.extends_segment = state.before_mode == BOOT_TRACK_END_EXTEND_SEGMENT || state.after_mode == BOOT_TRACK_END_EXTEND_SEGMENT;
}

/**
 * @brief Return how many key spans the last wrapped key was past the first key.
 * @return Signed cycle count.
 */
s32 BootFloatQuaternionTrackBase::get_cycle_count() const
{
    return state.cycle_count;
}

/**
 * @brief Return the number of stored keys.
 * @return Key count.
 */
s16 BootFloatQuaternionTrackBase::get_key_count() const
{
    return state.key_count;
}

/**
 * @brief Return the number of keys the storage can hold.
 * @return Key capacity.
 */
s16 BootFloatQuaternionTrackBase::get_key_capacity()
{
    return state.key_capacity;
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 * @return Zero.
 */
s32 BootFloatQuaternionTrackBase::on_append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return 0;
}

/**
 * @brief Forward to slot 0x68.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootFloatQuaternionTrackBase::append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return on_append_key(value, first, second, key);
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @return Zero.
 */
s32 BootFloatQuaternionTrackBase::on_replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return 0;
}

/**
 * @brief Forward to slot 0x6C.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootFloatQuaternionTrackBase::replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return on_replace_key(index, key, value, first, second);
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @return Zero.
 */
s32 BootFloatQuaternionTrackBase::on_insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return 0;
}

/**
 * @brief Forward to slot 0x70.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootFloatQuaternionTrackBase::insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return on_insert_key(index, key, value, first, second);
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 */
void BootFloatQuaternionTrackBase::on_set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
}

/**
 * @brief Forward to slot 0x74.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 */
void BootFloatQuaternionTrackBase::set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    on_set_single_key(value, first, second, key);
}

/**
 * @brief Return a zero vector; the track's value when it has no keys.
 * @return Zero vector.
 */
FieldVec4A BootFloatQuaternionTrackBase::get_zero_value() const
{
    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void BootFloatQuaternionTrackBase::evaluate(float key, FieldVec4B* output) const
{
    *output = sample(key);
}

/**
 * @brief Return the key storage.
 * @return Key array, or null.
 */
BootFloatQuaternionTrackKey* BootFloatQuaternionTrackBase::get_keys()
{
    return key_array;
}

/**
 * @brief Forward to slot 0x68.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootVectorCurveTrackBase::append_key(const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent, float key)
{
    return on_append_key(value, in_tangent, out_tangent, key);
}

/**
 * @brief Forward to slot 0x6C.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootVectorCurveTrackBase::replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent)
{
    return on_replace_key(index, key, value, in_tangent, out_tangent);
}

/**
 * @brief Forward to slot 0x70.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootVectorCurveTrackBase::insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent)
{
    return on_insert_key(index, key, value, in_tangent, out_tangent);
}

/**
 * @brief Forward to slot 0x74.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key the keyframe sits at.
 */
void BootVectorCurveTrackBase::set_single_key(const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent, float key)
{
    on_set_single_key(value, in_tangent, out_tangent, key);
}

/**
 * @brief Normalize a key across the cached span and store its signed period count.
 * @param key Key whose period count is representable as a signed 32-bit integer.
 * @return Normalized key, with odd-period reflection selected by the control fields.
 */
float BootFloatCurveTrackBase::update_cycle_count(float key)
{
    float first = key_array[0].key;
    float quotient = (key - first) / state.span;

    if (key < first)
    {
        quotient -= 1.0f;
    }

    state.cycle_count = quotient;

    if (state.cycle_count)
    {
        float result = key - (float)state.cycle_count * state.span;

        if ((state.before_mode == BOOT_TRACK_END_PING_PONG && state.cycle_count < 0) || (state.after_mode == BOOT_TRACK_END_PING_PONG && state.cycle_count > 0))
        {
            s32 last_index = state.key_count - 1;
            BootFloatCurveTrackKey* last_entry = key_array + last_index;
            float last = last_entry->key;

            if (state.cycle_count & 1)
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
 * @param key Key to place.
 * @param lower Receives the lower entry index.
 * @param upper Receives the upper entry index.
 * @return One when the active end mode extends the first or last segment, otherwise zero.
 */
u8 BootFloatCurveTrackBase::find_surrounding_keys(float key, s32* lower, s32* upper)
{
    s32 index;
    s32 count;
    s32 next;

    if (state.extends_segment)
    {
        if (state.before_mode == BOOT_TRACK_END_EXTEND_SEGMENT && state.cycle_count < 0)
        {
            *lower = 0;
            *upper = 1;
            state.search_index = 0;
            return 1;
        }

        if (state.after_mode == BOOT_TRACK_END_EXTEND_SEGMENT && state.cycle_count > 0)
        {
            *lower = state.key_count - 2;
            *upper = state.key_count - 1;
            state.search_index = state.key_count - 2;
            return 1;
        }
    }

    index = state.search_index;
    count = state.key_count;

    while (index > 0 && key < key_array[index].key)
    {
        index--;
    }

    index = clamp_low(index, 0);

    while ((next = index + 1) < count && !(key < key_array[next].key))
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

    state.search_index = index;
    return 0;
}
/**
 * @brief Forward to slot 0x68.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootFloatCurveTrackBase::append_key(const float* value, const float* in_tangent, const float* out_tangent, float key)
{
    return on_append_key(value, in_tangent, out_tangent, key);
}

/**
 * @brief Forward to slot 0x6C.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootFloatCurveTrackBase::replace_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent)
{
    return on_replace_key(index, key, value, in_tangent, out_tangent);
}

/**
 * @brief Forward to slot 0x70.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootFloatCurveTrackBase::insert_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent)
{
    return on_insert_key(index, key, value, in_tangent, out_tangent);
}

/**
 * @brief Forward to slot 0x74.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key the keyframe sits at.
 */
void BootFloatCurveTrackBase::set_single_key(const float* value, const float* in_tangent, const float* out_tangent, float key)
{
    on_set_single_key(value, in_tangent, out_tangent, key);
}

/**
 * @brief Normalize a key across the cached span and store its signed period count.
 * @param key Key whose period count is representable as a signed 32-bit integer.
 * @return Normalized key, with odd-period reflection selected by the control fields.
 */
float BootFloatTrackBase::update_cycle_count(float key)
{
    float first = key_array[0].key;
    float quotient = (key - first) / state.span;

    if (key < first)
    {
        quotient -= 1.0f;
    }

    state.cycle_count = quotient;

    if (state.cycle_count)
    {
        float result = key - (float)state.cycle_count * state.span;

        if ((state.before_mode == BOOT_TRACK_END_PING_PONG && state.cycle_count < 0) || (state.after_mode == BOOT_TRACK_END_PING_PONG && state.cycle_count > 0))
        {
            s32 last_index = state.key_count - 1;
            BootFloatTrackKey* last_entry = key_array + last_index;
            float last = last_entry->key;

            if (state.cycle_count & 1)
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
 * @param key Key to place.
 * @param lower Receives the lower entry index.
 * @param upper Receives the upper entry index.
 * @return One when the active end mode extends the first or last segment, otherwise zero.
 */
u8 BootFloatTrackBase::find_surrounding_keys(float key, s32* lower, s32* upper)
{
    s32 index;
    s32 count;
    s32 next;

    if (state.extends_segment)
    {
        if (state.before_mode == BOOT_TRACK_END_EXTEND_SEGMENT && state.cycle_count < 0)
        {
            *lower = 0;
            *upper = 1;
            state.search_index = 0;
            return 1;
        }

        if (state.after_mode == BOOT_TRACK_END_EXTEND_SEGMENT && state.cycle_count > 0)
        {
            *lower = state.key_count - 2;
            *upper = state.key_count - 1;
            state.search_index = state.key_count - 2;
            return 1;
        }
    }

    index = state.search_index;
    count = state.key_count;

    while (index > 0 && key < key_array[index].key)
    {
        index--;
    }

    index = clamp_low(index, 0);

    while ((next = index + 1) < count && !(key < key_array[next].key))
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

    state.search_index = index;
    return 0;
}
/**
 * @brief Reset signed-key entry storage, counts, control fields, and cached indices.
 */
void BootQuaternionTrackBase::reset_state()
{
    key_array = 0;
    state.before_mode = BOOT_TRACK_END_CYCLE;
    state.after_mode = BOOT_TRACK_END_CYCLE;
    state.key_capacity = 0;
    state.key_count = 0;
    state.search_index = -1;
    state.cycle_count = 0;
    state.segment_lower = -1;
    state.segment_upper = -1;
    state.extends_segment = 0;
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
    state.extends_segment = state.before_mode == BOOT_TRACK_END_EXTEND_SEGMENT || state.after_mode == BOOT_TRACK_END_EXTEND_SEGMENT;
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
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 * @return Zero.
 */
s32 BootQuaternionTrackBase::on_append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return 0;
}

/**
 * @brief Forward to slot 0x68.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootQuaternionTrackBase::append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return on_append_key(value, first, second, key);
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @return Zero.
 */
s32 BootQuaternionTrackBase::on_replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return 0;
}

/**
 * @brief Forward to slot 0x6C.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootQuaternionTrackBase::replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return on_replace_key(index, key, value, first, second);
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @return Zero.
 */
s32 BootQuaternionTrackBase::on_insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return 0;
}

/**
 * @brief Forward to slot 0x70.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootQuaternionTrackBase::insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return on_insert_key(index, key, value, first, second);
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 */
void BootQuaternionTrackBase::on_set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
}

/**
 * @brief Forward to slot 0x74.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 */
void BootQuaternionTrackBase::set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    on_set_single_key(value, first, second, key);
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
 * @brief Return a zero vector; the track's value when it has no keys.
 * @return Zero vector.
 */
FieldVec4A BootQuaternionTrackBase::get_zero_value() const
{
    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
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
    // Preserve the read of the result pointer after the copy.
    FieldVec4A* volatile* slot = &out;
    (void)*slot;
}

/**
 * @brief BootQuaternionTrackBase's find_key_value (slot 0x7C): find the keyframe with a key and decode its rotation.
 * @param out Receives the rotation, or zero when the key is absent.
 * @param track Track to search.
 * @param key Key to find.
 */
void quaternion_track_find_key_value(FieldVec4A* out, BootQuaternionTrackBase* track, float key)
{
    s32 index;

    for (index = 0; index < track->state.key_count; index++)
    {
        BootQuaternionTrackKey* entry = track->key_array + index;

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
void BootQuaternionCurveTrackBase::reset_state()
{
    key_array = 0;
    state.before_mode = BOOT_TRACK_END_CYCLE;
    state.after_mode = BOOT_TRACK_END_CYCLE;
    state.key_capacity = 0;
    state.key_count = 0;
    state.search_index = -1;
    state.cycle_count = 0;
    state.segment_lower = -1;
    state.segment_upper = -1;
    state.extends_segment = 0;
    state.external_keys = 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param count Requested keyframe count.
 */
void BootQuaternionCurveTrackBase::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] key_array;
    key_array = new (0) BootQuaternionCurveTrackKey[count];
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
void BootQuaternionCurveTrackBase::bind_keys(s32 count, BootQuaternionCurveTrackKey* entries)
{
    s32 last_index = count - 1;
    BootQuaternionCurveTrackKey* last;
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
void BootQuaternionCurveTrackBase::set_after_mode(u32 value)
{
    state.after_mode = value;
    state.extends_segment = state.before_mode == BOOT_TRACK_END_EXTEND_SEGMENT || state.after_mode == BOOT_TRACK_END_EXTEND_SEGMENT;
}

/**
 * @brief Return how many key spans the last wrapped key was past the first key.
 * @return Signed cycle count.
 */
s32 BootQuaternionCurveTrackBase::get_cycle_count() const
{
    return state.cycle_count;
}

/**
 * @brief Return the number of stored keys.
 * @return Key count.
 */
s16 BootQuaternionCurveTrackBase::get_key_count() const
{
    return state.key_count;
}

/**
 * @brief Return the number of keys the storage can hold.
 * @return Key capacity.
 */
s16 BootQuaternionCurveTrackBase::get_key_capacity()
{
    return state.key_capacity;
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 * @return Zero.
 */
s32 BootQuaternionCurveTrackBase::on_append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return 0;
}

/**
 * @brief Forward to slot 0x68.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootQuaternionCurveTrackBase::append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return on_append_key(value, first, second, key);
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @return Zero.
 */
s32 BootQuaternionCurveTrackBase::on_replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return 0;
}

/**
 * @brief Forward to slot 0x6C.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootQuaternionCurveTrackBase::replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return on_replace_key(index, key, value, first, second);
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @return Zero.
 */
s32 BootQuaternionCurveTrackBase::on_insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return 0;
}

/**
 * @brief Forward to slot 0x70.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootQuaternionCurveTrackBase::insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return on_insert_key(index, key, value, first, second);
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 */
void BootQuaternionCurveTrackBase::on_set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
}

/**
 * @brief Forward to slot 0x74.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 */
void BootQuaternionCurveTrackBase::set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    on_set_single_key(value, first, second, key);
}

/**
 * @brief Test whether the 48-byte record array contains an exactly equal key.
 * @param key Scalar key to find.
 * @return One for an equal key, or zero when none is present.
 */
s32 BootQuaternionCurveTrackBase::has_key(float key) const
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
 * @brief Return a zero vector; the track's value when it has no keys.
 * @return Zero vector.
 */
FieldVec4A BootQuaternionCurveTrackBase::get_zero_value() const
{
    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Return the last-to-first key difference, or zero below two records.
 * @return Difference between the last and first scalar keys, or zero.
 */
float BootQuaternionCurveTrackBase::get_key_span() const
{
    s32 last_index;
    BootQuaternionCurveTrackKey* last_entry;

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
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A BootQuaternionCurveTrackBase::find_key_value(float key)
{
    s32 index;

    for (index = 0; index < state.key_count; index++)
    {
        if (key == key_array[index].key)
        {
            BootQuaternionCurveTrackKey* entry = key_array + index;
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
void BootQuaternionCurveTrackBase::evaluate(float key, FieldVec4B* output) const
{
    *output = sample(key);
}

/**
 * @brief Adjust a scalar key by whole spans determined from the endpoint records.
 * @param key Scalar key whose normalized span quotient must fit in a signed word.
 * @return Key minus the computed number of endpoint spans, or the key for zero spans.
 */
float BootQuaternionCurveTrackBase::wrap_key(float key) const
{
    s32 last_index = state.key_count - 1;
    BootQuaternionCurveTrackKey* entries = key_array;
    BootQuaternionCurveTrackKey* last = entries + last_index;
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
BootQuaternionCurveTrackKey* BootQuaternionCurveTrackBase::get_keys()
{
    return key_array;
}

/** @brief Leave the keyframe uninitialized. */
BootQuaternionCurveTrackKey::BootQuaternionCurveTrackKey()
{
}

/**
 * @brief Adjust a scalar key by whole spans determined from the endpoint records.
 * @param key Scalar key whose normalized span quotient must fit in a signed word.
 * @return Key minus the computed number of endpoint spans, or the key for zero spans.
 */
float BootFloatQuaternionTrackBase::wrap_key(float key) const
{
    s32 last_index = state.key_count - 1;
    BootFloatQuaternionTrackKey* entries = key_array;
    BootFloatQuaternionTrackKey* last = entries + last_index;
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
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A BootFloatQuaternionTrackBase::find_key_value(float key)
{
    s32 index;

    for (index = 0; index < state.key_count; index++)
    {
        if (key == key_array[index].key)
        {
            BootFloatQuaternionTrackKey* entry = key_array + index;
            return *reinterpret_cast<const FieldVec4A*>(entry->value);
        }
    }

    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Return the last-to-first key difference, or zero below two records.
 * @return Difference between the last and first scalar keys, or zero.
 */
float BootFloatQuaternionTrackBase::get_key_span() const
{
    s32 last_index;
    BootFloatQuaternionTrackKey* last_entry;

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
s32 BootFloatQuaternionTrackBase::has_key(float key) const
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
void BootFloatQuaternionTrackBase::bind_keys(s32 count, BootFloatQuaternionTrackKey* entries)
{
    s32 last_index = count - 1;
    BootFloatQuaternionTrackKey* last;
    state.external_keys = 1;
    key_array = entries;
    state.key_capacity = count;
    state.key_count = count;
    last = key_array + last_index;
    state.span = last->key - key_array[0].key;
}

/** @brief Leave the keyframe uninitialized. */
BootFloatQuaternionTrackKey::BootFloatQuaternionTrackKey()
{
}
