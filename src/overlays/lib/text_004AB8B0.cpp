#include "include_asm.h"
#include "overlays/lib/text_004AB8B0.h"
#include "main/resident_data.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/lib/vector_vu0.h"

extern LibTrackPool<LibPooledSlerpQuaternionTrack>* g_slerp_quaternion_track_pool;
extern LibTrackPool<LibPooledFloatTrack>* g_float_track_pool;
extern LibTrackPool<LibPooledFloatCurveTrack>* g_float_curve_track_pool;
extern LibTrackPool<LibPooledFloatQuaternionTrack>* g_float_quaternion_track_pool;

/**
 * @brief Mark a track's g_slerp_quaternion_track_pool slot as free.
 * @param pool Pool that owns the track.
 * @param track Track to release.
 */
void slerp_quaternion_track_pool_free(LibTrackPool<LibPooledSlerpQuaternionTrack>* pool, LibPooledSlerpQuaternionTrack* track);

/**
 * @brief Mark a track's g_float_track_pool slot as free.
 * @param pool Pool that owns the track.
 * @param track Track to release.
 */
void float_track_pool_free(LibTrackPool<LibPooledFloatTrack>* pool, LibPooledFloatTrack* track);

/**
 * @brief Mark a track's g_float_curve_track_pool slot as free.
 * @param pool Pool that owns the track.
 * @param track Track to release.
 */
void float_curve_track_pool_free(LibTrackPool<LibPooledFloatCurveTrack>* pool, LibPooledFloatCurveTrack* track);

/**
 * @brief Mark a track's g_float_quaternion_track_pool slot as free.
 * @param pool Pool that owns the track.
 * @param track Track to release.
 */
void float_quaternion_track_pool_free(LibTrackPool<LibPooledFloatQuaternionTrack>* pool, LibPooledFloatQuaternionTrack* track);

/** Another animation entry flag, and the kinds an entry without a target may have. */
enum
{
    LIB_ANIMATION_ENTRY_RESTART_ONLY = 0x20,
    LIB_ANIMATION_KIND_UNBOUND_FIRST = 0xE0,
    LIB_ANIMATION_KIND_UNBOUND_END = 0xF0
};

extern "C" {

typedef struct FourWordClearOwnertext_004AB8B0 { u32 words[4]; } FourWordClearOwnertext_004AB8B0;

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AB8B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ABA00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ABA10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ABA20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ABA30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ABA40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ABA50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ABA60);

s32 func_004ABAA0(void* object)
{
    return 99;
}

void func_004ABAB0(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ABAC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ABD10);

void func_004ABD30(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ABD40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ABFF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AC260);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AC320);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AC390);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AC3A0);

/** @brief Forget the stored samples. */
void LibLinearFloatHistory::reset()
{
    sample_count = 0;
    next_index = 0;
    unk08 = 0;
    unk0C = 0;
}

/** @brief Do nothing; the slot's purpose is unknown. */
void LibLinearFloatHistory::func_slot08()
{
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
s32 LibSlerpQuaternionKeyTrack::read_key(s32 index, float* key, void* value, void* first, void* second) const
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
        *static_cast<FieldVec4B*>(value) = key_array[index].value;
    }

    return 1;
}

/**
 * @brief Normalize a key across the cached span and store its signed period count.
 * @param key Key whose period count is representable as a signed 32-bit integer.
 * @return Normalized key, with odd-period reflection selected by the control fields.
 */
float LibSlerpQuaternionTrackBase::update_cycle_count(float key)
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

        if ((state.before_mode == LIB_TRACK_END_PING_PONG && state.cycle_count < 0) || (state.after_mode == LIB_TRACK_END_PING_PONG && state.cycle_count > 0))
        {
            s32 last_index = state.key_count - 1;
            LibSlerpQuaternionTrackKey* last_entry = key_array + last_index;
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
u8 LibSlerpQuaternionTrackBase::find_surrounding_keys(float key, s32* lower, s32* upper)
{
    s32 index;
    s32 count;
    s32 next;

    if (state.extends_segment)
    {
        if (state.before_mode == LIB_TRACK_END_EXTEND_SEGMENT && state.cycle_count < 0)
        {
            *lower = 0;
            *upper = 1;
            state.search_index = 0;
            return 1;
        }

        if (state.after_mode == LIB_TRACK_END_EXTEND_SEGMENT && state.cycle_count > 0)
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

/** @brief Free the keys. */
LibSlerpQuaternionTrackBase::~LibSlerpQuaternionTrackBase()
{
    free_keys();
}

/** @brief Clear the key storage, counts, modes and cached indices. */
void LibSlerpQuaternionTrackBase::reset_state()
{
    key_array = 0;
    state.before_mode = LIB_TRACK_END_CYCLE;
    state.after_mode = LIB_TRACK_END_CYCLE;
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
 * @brief Bind an external keyframe array and cache its first-to-last key span.
 * @param count Keyframe count.
 * @param keys External keyframe storage.
 */
void LibSlerpQuaternionTrackBase::bind_keys(s32 count, void* keys)
{
    s32 last_index = count - 1;
    LibSlerpQuaternionTrackKey* last;
    state.external_keys = 1;
    key_array = static_cast<LibSlerpQuaternionTrackKey*>(keys);
    state.key_capacity = count;
    state.key_count = count;
    last = key_array + last_index;
    state.span = last->key - key_array[0].key;
}

/**
 * @brief Set the end mode used before the first key, and note whether either end extends its segment.
 * @param mode LIB_TRACK_END_* mode.
 */
void LibSlerpQuaternionTrackBase::set_before_mode(u32 mode)
{
    state.before_mode = mode;
    state.extends_segment = state.before_mode == LIB_TRACK_END_EXTEND_SEGMENT || state.after_mode == LIB_TRACK_END_EXTEND_SEGMENT;
}

/**
 * @brief Set the end mode used after the last key, and note whether either end extends its segment.
 * @param mode LIB_TRACK_END_* mode.
 */
void LibSlerpQuaternionTrackBase::set_after_mode(u32 mode)
{
    state.after_mode = mode;
    state.extends_segment = state.before_mode == LIB_TRACK_END_EXTEND_SEGMENT || state.after_mode == LIB_TRACK_END_EXTEND_SEGMENT;
}

/**
 * @brief Return how many key spans the last wrapped key was past the first key.
 * @return Signed cycle count.
 */
s32 LibSlerpQuaternionTrackBase::get_cycle_count() const
{
    return state.cycle_count;
}

/**
 * @brief Return the number of stored keys.
 * @return Key count.
 */
s16 LibSlerpQuaternionTrackBase::get_key_count() const
{
    return state.key_count;
}

/**
 * @brief Return the number of keys the storage can hold.
 * @return Key capacity.
 */
s16 LibSlerpQuaternionTrackBase::get_key_capacity()
{
    return state.key_capacity;
}

/**
 * @brief Test whether a key is stored exactly.
 * @param key Key to find.
 * @return One when a key equals it, otherwise zero.
 */
s32 LibSlerpQuaternionTrackBase::has_key(float key) const
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
 * @brief Return a zero vector, the track's value when it has no keys.
 * @return Zero vector.
 */
FieldVec4A LibSlerpQuaternionTrackBase::get_zero_value() const
{
    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Return the last key minus the first, or zero below two keys.
 * @return Key span.
 */
float LibSlerpQuaternionTrackBase::get_key_span() const
{
    s32 last_index;
    LibSlerpQuaternionTrackKey* last_entry;

    if (state.key_count < 2)
    {
        return 0.0f;
    }

    last_index = state.key_count - 1;
    last_entry = key_array + last_index;
    return last_entry->key - key_array[0].key;
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the vector.
 */
void LibSlerpQuaternionTrackBase::evaluate(float key, void* output)
{
    *static_cast<FieldVec4B*>(output) = sample(key);
}

/**
 * @brief Move a key into the first key span by whole spans.
 * @param key Key to wrap.
 * @return Key minus the whole spans it lies past the first key, or the key itself.
 */
float LibSlerpQuaternionTrackBase::wrap_key(float key) const
{
    s32 last_index = state.key_count - 1;
    LibSlerpQuaternionTrackKey* keys = key_array;
    LibSlerpQuaternionTrackKey* last = keys + last_index;
    float first = keys[0].key;
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
void* LibSlerpQuaternionTrackBase::get_keys()
{
    return key_array;
}

/** @brief Delete the key storage unless it is external, and clear the key pointer. */
void LibSlerpQuaternionTrackBase::free_keys()
{
    if (!state.external_keys)
    {
        delete[] key_array;
    }

    key_array = 0;
}

/**
 * @brief Return the value of the first keyframe at exactly a key.
 * @param key Key to find.
 * @return Keyframe value, or a zero vector when no key matches.
 */
FieldVec4A LibSlerpQuaternionTrackBase::find_key_value(float key)
{
    s32 index;

    for (index = 0; index < state.key_count; index++)
    {
        if (key == key_array[index].key)
        {
            LibSlerpQuaternionTrackKey* entry = key_array + index;
            return *reinterpret_cast<const FieldVec4A*>(&entry->value);
        }
    }

    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Store a single keyframe through on_set_single_key.
 * @param value Keyframe value.
 * @param in_tangent Unused.
 * @param out_tangent Unused.
 * @param key Sort key.
 */
void LibSlerpQuaternionTrackBase::set_single_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    on_set_single_key(static_cast<const FieldVec4A*>(value), key);
}

/**
 * @brief Store the single key; the base ignores it.
 * @param value Key value.
 * @param key Key position.
 */
void LibSlerpQuaternionTrackBase::on_set_single_key(const FieldVec4A* value, float key)
{
}

/**
 * @brief Insert a keyframe through on_insert_key.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @param in_tangent Unused.
 * @param out_tangent Unused.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibSlerpQuaternionTrackBase::insert_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    return on_insert_key(index, key, static_cast<const FieldVec4A*>(value));
}

/**
 * @brief Insert a key; the base ignores it.
 * @param index Key index.
 * @param key Key position.
 * @param value Key value.
 * @return Zero.
 */
s32 LibSlerpQuaternionTrackBase::on_insert_key(s32 index, float key, const FieldVec4A* value)
{
    return 0;
}

/**
 * @brief Replace a keyframe through on_replace_key.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @param in_tangent Unused.
 * @param out_tangent Unused.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibSlerpQuaternionTrackBase::replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    return on_replace_key(index, key, static_cast<const FieldVec4A*>(value));
}

/**
 * @brief Replace a key; the base ignores it.
 * @param index Key index.
 * @param key Key position.
 * @param value Key value.
 * @return Zero.
 */
s32 LibSlerpQuaternionTrackBase::on_replace_key(s32 index, float key, const FieldVec4A* value)
{
    return 0;
}

/**
 * @brief Append a keyframe through on_append_key.
 * @param value Keyframe value.
 * @param in_tangent Unused.
 * @param out_tangent Unused.
 * @param key Sort key.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibSlerpQuaternionTrackBase::append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    return on_append_key(static_cast<const FieldVec4A*>(value), key);
}

/**
 * @brief Append a key; the base ignores it.
 * @param value Key value.
 * @param key Key position.
 * @return Zero.
 */
s32 LibSlerpQuaternionTrackBase::on_append_key(const FieldVec4A* value, float key)
{
    return 0;
}

/**
 * @brief Allocate storage for a number of keyframes, dropping any keys the track owned.
 * @param count Keyframes to hold.
 */
void LibSlerpQuaternionTrackBase::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] key_array;
    key_array = new (0) LibSlerpQuaternionTrackKey[count];
    state.key_capacity = count;

    if (!key_array)
    {
        state.key_capacity = 0;
    }
}

/** @brief Leave the keyframe uninitialized. */
LibSlerpQuaternionTrackKey::LibSlerpQuaternionTrackKey()
{
}

/**
 * @brief Store a single keyframe in the cached key and value, and use it before the first key.
 * @param value Keyframe value.
 * @param key Sort key.
 */
void LibSlerpQuaternionKeyTrack::on_set_single_key(const FieldVec4A* value, float key)
{
    set_before_mode(LIB_TRACK_END_USE_PRE_START_KEY);
    single_value = *value;
    single_key = key;
}

/**
 * @brief Insert a keyframe at an index.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibSlerpQuaternionKeyTrack::on_insert_key(s32 index, float key, const FieldVec4A* value)
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
s32 LibSlerpQuaternionKeyTrack::on_replace_key(s32 index, float key, const FieldVec4A* value)
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
s32 LibSlerpQuaternionKeyTrack::on_append_key(const FieldVec4A* value, float key)
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

/** @brief Clear the cached sample state and reset the keys' bookkeeping. */
void LibPooledFloatQuaternionTrack::reset_state()
{
    unk58 = 0;
    unk50 = 0;
    LibFloatQuaternionTrackBase::reset_state();
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", append_key__29LibPooledFloatQuaternionTrackFPCvPCvPCvf);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", replace_key__29LibPooledFloatQuaternionTrackFifPCvPCvPCv);

/**
 * @brief Insert a keyframe, with zero for a missing extra value.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe rotation.
 * @param first First extra value, or null for zero.
 * @param second Second extra value, or null for zero.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibPooledFloatQuaternionTrack::insert_key(s32 index, float key, const void* value, const void* first, const void* second)
{
    float second_value = (second == 0) ? 0.0f : *static_cast<const float*>(second);
    float first_value = (first == 0) ? 0.0f : *static_cast<const float*>(first);
    return insert_entry(index, key, static_cast<const FieldVec4A*>(value), first_value, second_value);
}

/**
 * @brief Store a single keyframe, with zero for a missing extra value, and use it before the first key.
 * @param value Keyframe rotation.
 * @param first First extra value, or null for zero.
 * @param second Second extra value, or null for zero.
 * @param key Sort key.
 */
void LibPooledFloatQuaternionTrack::set_single_key(const void* value, const void* first, const void* second, float key)
{
    float second_value = (second == 0) ? 0.0f : *static_cast<const float*>(second);
    float first_value = (first == 0) ? 0.0f : *static_cast<const float*>(first);
    set_before_mode(LIB_TRACK_END_USE_PRE_START_KEY);
    copy_vector(&single_key.value, static_cast<const LibVector4*>(value));
    single_key.first = first_value;
    single_key.second = second_value;
    single_key.key = key;
}

/**
 * @brief Report how fast the sampled value was changing.
 * @param output Receives the rate.
 */
void LibPooledFloatQuaternionTrack::get_value_rate(void* output) const
{
    *static_cast<float*>(output) = value_rate;
}

/** @brief Reset to a single zero keyframe at key zero, then select the cycle end mode. */
void LibPooledFloatQuaternionTrack::reset_keys()
{
    FieldVec4A zero(0.0f, 0.0f, 0.0f, 0.0f);
    set_single_key(&zero, &zero, &zero, 0.0f);
    set_before_mode(LIB_TRACK_END_CYCLE);
}

/** @brief Give the track back to its pool when it came from one, otherwise delete it. */
void LibPooledFloatQuaternionTrack::release()
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

/** @brief Free the keys and give the track back to g_float_quaternion_track_pool. */
void LibPooledFloatQuaternionTrack::return_to_pool()
{
    LibFloatQuaternionTrackBase::free_keys();
    float_quaternion_track_pool_free(g_float_quaternion_track_pool, this);
}

/** @brief Destroy the track. */
LibPooledFloatQuaternionTrack::~LibPooledFloatQuaternionTrack()
{
}

/**
 * @brief Set the end mode used before the first key, and note whether either end extends its segment.
 * @param mode LIB_TRACK_END_* mode.
 */
void LibFloatQuaternionTrackBase::set_before_mode(u32 mode)
{
    state.before_mode = mode;
    state.extends_segment = state.before_mode == LIB_TRACK_END_EXTEND_SEGMENT || state.after_mode == LIB_TRACK_END_EXTEND_SEGMENT;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", get_end_delta__29LibPooledFloatQuaternionTrackCFPv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", insert_entry__29LibPooledFloatQuaternionTrackFifPC10FieldVec4Aff);

/**
 * @brief Read an indexed keyframe.
 * @param index Keyframe index.
 * @param key Receives the sort key.
 * @param value Receives the rotation.
 * @param first Receives the first extra value.
 * @param second Receives the second extra value.
 * @return One when the index is within the capacity, otherwise zero.
 */
s32 LibPooledFloatQuaternionTrack::read_key(s32 index, float* key, void* value, void* first, void* second) const
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
        *static_cast<FieldVec4B*>(value) = key_array[index].value;
    }

    if (first)
    {
        *static_cast<float*>(first) = key_array[index].first;
    }

    if (second)
    {
        *static_cast<float*>(second) = key_array[index].second;
    }

    return 1;
}

/**
 * @brief Copy an unpacked keyframe after the last key and extend the key span to it.
 * @param record LibFloatQuaternionKeyRecord to append.
 */
void LibPooledFloatQuaternionTrack::append_key_record(const void* record)
{
    const LibFloatQuaternionKeyRecord* source = static_cast<const LibFloatQuaternionKeyRecord*>(record);

    if (key_array)
    {
        key_array[state.key_count].value.x = source->value[0];
        key_array[state.key_count].value.y = source->value[1];
        key_array[state.key_count].value.z = source->value[2];
        key_array[state.key_count].value.w = source->value[3];
        key_array[state.key_count].key = source->key;
        key_array[state.key_count].first = source->first;
        key_array[state.key_count].second = source->second;
        state.span = key_array[state.key_count].key - key_array[0].key;
        state.key_count++;
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AD860);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ADC60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AE5A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", sample__29LibPooledFloatQuaternionTrackCFf);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AEFE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AEFF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AF060);

/**
 * @brief Store the single keyframe and its tangents from plain floats.
 * @param key Sort key.
 * @param value Keyframe value.
 * @param in_tangent Incoming tangent.
 * @param out_tangent Outgoing tangent.
 */
void LibPooledFloatCurveTrack::set_single_float_curve_key(float key, float value, float in_tangent, float out_tangent)
{
    LibFloatCurveTrack::set_single_curve_key(&value, &in_tangent, &out_tangent, key);
}

/**
 * @brief Insert a keyframe and its tangents.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @param in_tangent Incoming tangent.
 * @param out_tangent Outgoing tangent.
 */
void LibPooledFloatCurveTrack::insert_float_curve_key(s32 index, float key, float value, float in_tangent, float out_tangent)
{
    LibFloatCurveTrack::insert_curve_key(index, key, &value, &in_tangent, &out_tangent);
}

/**
 * @brief Replace a keyframe and its tangents.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @param in_tangent Incoming tangent.
 * @param out_tangent Outgoing tangent.
 */
void LibPooledFloatCurveTrack::replace_float_curve_key(s32 index, float key, float value, float in_tangent, float out_tangent)
{
    LibFloatCurveTrack::replace_curve_key(index, key, &value, &in_tangent, &out_tangent);
}

/**
 * @brief Append a keyframe and its tangents.
 * @param key Sort key.
 * @param value Keyframe value.
 * @param in_tangent Incoming tangent.
 * @param out_tangent Outgoing tangent.
 */
void LibPooledFloatCurveTrack::append_float_curve_key(float key, float value, float in_tangent, float out_tangent)
{
    LibFloatCurveTrack::append_curve_key(&value, &in_tangent, &out_tangent, key);
}

/** @brief Give the track and its keys back to the pool when it came from one, otherwise delete it. */
void LibPooledFloatCurveTrack::release()
{
    if (this != 0)
    {
        if (state.pooled)
        {
            free_keys();
            float_curve_track_pool_free(g_float_curve_track_pool, this);
        }
        else
        {
            delete this;
        }
    }
}

/** @brief Destroy the track. */
LibPooledFloatCurveTrack::~LibPooledFloatCurveTrack()
{
}

/** @brief Forget the last sampled value and reset the keys' bookkeeping. */
void LibFloatCurveTrack::reset_state()
{
    last_value = 0.0f;
    LibFloatCurveTrackBase::reset_state();
}

/**
 * @brief Evaluate the track with cached interpolation, wrapping and endpoint extrapolation.
 * @param key Sort value.
 * @return Evaluated value; updates the cached value and its scaled change.
 */
float LibFloatCurveTrack::sample(float key)
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

    if (state.key_count == 1 && (!(key < key_array[0].key) || state.before_mode != LIB_TRACK_END_USE_PRE_START_KEY))
    {
        return key_array[0].value;
    }

    extrapolate = 0;

    if (key < key_array[0].key && state.before_mode == LIB_TRACK_END_USE_PRE_START_KEY)
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
            if (state.before_mode == LIB_TRACK_END_HOLD && state.cycle_count < 0)
            {
                return key_array[0].value;
            }

            if (state.after_mode == LIB_TRACK_END_HOLD && state.cycle_count > 0)
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
            LibFloatCurveTrackKey* first = lower >= 0 ? key_array + lower : &single_key;
            s32 last = state.key_count - 1;

            if (upper == last && ((!(key < key_array[0].key) && state.after_mode == LIB_TRACK_END_CYCLE_TO_FIRST) ||
                (key < key_array[0].key && state.before_mode == LIB_TRACK_END_CYCLE_TO_FIRST)))
            {
                LibFloatCurveTrackKey* entries = key_array;
                curve_segment.set_endpoints(&first->value, &first->out_tangent, &entries[0].value, &entries[0].in_tangent, first->key, entries[upper].key);
            }
            else if (lower < upper)
            {
                LibFloatCurveTrackKey* second = key_array + upper;
                curve_segment.set_endpoints(&first->value, &first->out_tangent, &second->value, &second->in_tangent, first->key, second->key);
            }
            else
            {
                LibFloatCurveTrackKey* second = key_array + last;
                curve_segment.set_endpoints(&first->value, &first->out_tangent, &second->value, &second->in_tangent, first->key, second->key);
            }
        }

        result = curve_segment.interpolate(wrapped_key);

        if (state.cycle_count && ((state.before_mode == LIB_TRACK_END_OFFSET_CYCLE && state.cycle_count < 0) ||
            (state.after_mode == LIB_TRACK_END_OFFSET_CYCLE && state.cycle_count > 0)))
        {
            float delta = key_array[state.key_count - 1].value - key_array[0].value;
            result += delta * state.cycle_count;
        }
    }
    else if (wrapped_key < key)
    {
        s32 count = state.key_count;
        LibFloatCurveTrackKey* entries = key_array;
        LibFloatCurveTrackKey* last_entry = entries + (count - 1);
        LibFloatCurveTrackKey* previous_entry = entries + (count - 2);
        float last_key = last_entry->key;
        float previous_key = previous_entry->key;
        float slope = entries[count - 1].in_tangent / (last_key - previous_key);
        result = entries[count - 1].value + slope * (key - last_key);
    }
    else
    {
        LibFloatCurveTrackKey* entries = key_array;
        float first_key = entries[0].key;
        result = entries[0].value + (entries[0].out_tangent / (entries[1].key - first_key)) * (key - first_key);
    }

    value_rate = g_inverse_frame_ticks * (result - last_value);
    last_value = result;
    return result;
}

#define LIB_TRACKS_EMIT_DTOR_FLOAT_CURVE_TRACK

/**
 * @brief Append a keyframe, with zero for a missing tangent.
 * @param value Keyframe value.
 * @param in_tangent Incoming tangent, or null for zero.
 * @param out_tangent Outgoing tangent, or null for zero.
 * @param key Sort key.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibFloatCurveTrack::append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    float in_value;
    float out_value;
    out_value = (out_tangent == 0) ? 0.0f : *static_cast<const float*>(out_tangent);
    out_tangent = &out_value;
    in_value = (in_tangent == 0) ? 0.0f : *static_cast<const float*>(in_tangent);
    in_tangent = &in_value;
    return append_curve_key(static_cast<const float*>(value), static_cast<const float*>(in_tangent), static_cast<const float*>(out_tangent), key);
}

/**
 * @brief Replace a keyframe, with zero for a missing tangent.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @param in_tangent Incoming tangent, or null for zero.
 * @param out_tangent Outgoing tangent, or null for zero.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibFloatCurveTrack::replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    float in_value;
    float out_value;
    out_value = (out_tangent == 0) ? 0.0f : *static_cast<const float*>(out_tangent);
    out_tangent = &out_value;
    in_value = (in_tangent == 0) ? 0.0f : *static_cast<const float*>(in_tangent);
    in_tangent = &in_value;
    return replace_curve_key(index, key, static_cast<const float*>(value), static_cast<const float*>(in_tangent), static_cast<const float*>(out_tangent));
}

/**
 * @brief Insert a keyframe, with zero for a missing tangent.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @param in_tangent Incoming tangent, or null for zero.
 * @param out_tangent Outgoing tangent, or null for zero.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibFloatCurveTrack::insert_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    float in_value;
    float out_value;
    out_value = (out_tangent == 0) ? 0.0f : *static_cast<const float*>(out_tangent);
    out_tangent = &out_value;
    in_value = (in_tangent == 0) ? 0.0f : *static_cast<const float*>(in_tangent);
    in_tangent = &in_value;
    return insert_curve_key(index, key, static_cast<const float*>(value), static_cast<const float*>(in_tangent), static_cast<const float*>(out_tangent));
}

/**
 * @brief Store the single keyframe, with zero for a missing tangent.
 * @param value Keyframe value.
 * @param in_tangent Incoming tangent, or null for zero.
 * @param out_tangent Outgoing tangent, or null for zero.
 * @param key Sort key.
 */
void LibFloatCurveTrack::set_single_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    float in_value;
    float out_value;
    out_value = (out_tangent == 0) ? 0.0f : *static_cast<const float*>(out_tangent);
    out_tangent = &out_value;
    in_value = (in_tangent == 0) ? 0.0f : *static_cast<const float*>(in_tangent);
    in_tangent = &in_value;
    set_single_curve_key(static_cast<const float*>(value), static_cast<const float*>(in_tangent), static_cast<const float*>(out_tangent), key);
}

/**
 * @brief Read an indexed keyframe.
 * @param index Keyframe index.
 * @param key Receives the sort key.
 * @param value Receives the value.
 * @param first Receives the incoming tangent.
 * @param second Receives the outgoing tangent.
 * @return One when the index is within the capacity, otherwise zero.
 */
s32 LibFloatCurveTrack::read_key(s32 index, float* key, void* value, void* first, void* second) const
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
        *static_cast<float*>(value) = key_array[index].value;
    }

    if (first)
    {
        *static_cast<float*>(first) = key_array[index].in_tangent;
    }

    if (second)
    {
        *static_cast<float*>(second) = key_array[index].out_tangent;
    }

    return 1;
}

/** @brief Reset to a single zero keyframe at key zero. */
void LibFloatCurveTrack::reset_keys()
{
    float zero = 0.0f;
    set_single_key(&zero, &zero, &zero, 0.0f);
}

/**
 * @brief Report how fast the sampled value was changing.
 * @param output Receives the rate.
 */
void LibFloatCurveTrack::get_value_rate(void* output) const
{
    *static_cast<float*>(output) = value_rate;
}

/**
 * @brief Report the last key's value minus the first's.
 * @param output Receives the difference; left alone when there are no keys.
 */
void LibFloatCurveTrack::get_end_delta(void* output) const
{
    if (key_array != 0)
    {
        *static_cast<float*>(output) = key_array[state.key_count - 1].value - key_array[0].value;
    }
}

/**
 * @brief Normalize a key across the cached span and store its signed period count.
 * @param key Key whose period count is representable as a signed 32-bit integer.
 * @return Normalized key, with odd-period reflection selected by the control fields.
 */
float LibQuaternionTrackBase::update_cycle_count(float key)
{
    float first = key_array[0].get_key();
    float quotient = (key - first) / state.span;

    if (key < first)
    {
        quotient -= 1.0f;
    }

    state.cycle_count = quotient;

    if (state.cycle_count)
    {
        float result = key - (float)state.cycle_count * state.span;

        if ((state.before_mode == LIB_TRACK_END_PING_PONG && state.cycle_count < 0) || (state.after_mode == LIB_TRACK_END_PING_PONG && state.cycle_count > 0))
        {
            s32 last_index = state.key_count - 1;
            LibQuaternionTrackKey* last_entry = key_array + last_index;
            float last = last_entry->get_key();

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
u8 LibQuaternionTrackBase::find_surrounding_keys(float key, s32* lower, s32* upper)
{
    s32 index;
    s32 count;
    s32 next;

    if (state.extends_segment)
    {
        if (state.before_mode == LIB_TRACK_END_EXTEND_SEGMENT && state.cycle_count < 0)
        {
            *lower = 0;
            *upper = 1;
            state.search_index = 0;
            return 1;
        }

        if (state.after_mode == LIB_TRACK_END_EXTEND_SEGMENT && state.cycle_count > 0)
        {
            *lower = state.key_count - 2;
            *upper = state.key_count - 1;
            state.search_index = state.key_count - 2;
            return 1;
        }
    }

    index = state.search_index;
    count = state.key_count;

    while (index > 0 && key < key_array[index].get_key())
    {
        index--;
    }

    index = clamp_low(index, 0);

    while ((next = index + 1) < count && !(key < key_array[next].get_key()))
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
 * @brief Normalize a key across the cached span and store its signed period count.
 * @param key Key whose period count is representable as a signed 32-bit integer.
 * @return Normalized key, with odd-period reflection selected by the control fields.
 */
float LibFloatQuaternionTrackBase::update_cycle_count(float key)
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

        if ((state.before_mode == LIB_TRACK_END_PING_PONG && state.cycle_count < 0) || (state.after_mode == LIB_TRACK_END_PING_PONG && state.cycle_count > 0))
        {
            s32 last_index = state.key_count - 1;
            LibFloatQuaternionTrackKey* last_entry = key_array + last_index;
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
u8 LibFloatQuaternionTrackBase::find_surrounding_keys(float key, s32* lower, s32* upper)
{
    s32 index;
    s32 count;
    s32 next;

    if (state.extends_segment)
    {
        if (state.before_mode == LIB_TRACK_END_EXTEND_SEGMENT && state.cycle_count < 0)
        {
            *lower = 0;
            *upper = 1;
            state.search_index = 0;
            return 1;
        }

        if (state.after_mode == LIB_TRACK_END_EXTEND_SEGMENT && state.cycle_count > 0)
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

/** @brief Free the keys, then destroy the track. */
LibFloatQuaternionTrackBase::~LibFloatQuaternionTrackBase()
{
    free_keys();
}

/**
 * @brief Reset array storage, counts, packed controls, and cached indices.
 */
void LibFloatQuaternionTrackBase::reset_state()
{
    key_array = 0;
    state.before_mode = LIB_TRACK_END_CYCLE;
    state.after_mode = LIB_TRACK_END_CYCLE;
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
 * @brief Bind an external keyframe array and cache its first-to-last key span.
 * @param count Keyframe count.
 * @param keys External keyframe storage.
 */
void LibFloatQuaternionTrackBase::bind_keys(s32 count, void* keys)
{
    s32 last_index = count - 1;
    LibFloatQuaternionTrackKey* last;
    state.external_keys = 1;
    key_array = static_cast<LibFloatQuaternionTrackKey*>(keys);
    state.key_capacity = count;
    state.key_count = count;
    last = key_array + last_index;
    state.span = last->key - key_array[0].key;
}

/**
 * @brief Set the end mode used after the last key, and note whether either end extends its segment.
 * @param mode LIB_TRACK_END_* mode.
 */
void LibFloatQuaternionTrackBase::set_after_mode(u32 mode)
{
    state.after_mode = mode;
    state.extends_segment = state.before_mode == LIB_TRACK_END_EXTEND_SEGMENT || state.after_mode == LIB_TRACK_END_EXTEND_SEGMENT;
}

/**
 * @brief Return how many key spans the last wrapped key was past the first key.
 * @return Signed cycle count.
 */
s32 LibFloatQuaternionTrackBase::get_cycle_count() const
{
    return state.cycle_count;
}

/**
 * @brief Return the number of stored keys.
 * @return Key count.
 */
s16 LibFloatQuaternionTrackBase::get_key_count() const
{
    return state.key_count;
}

/**
 * @brief Return the number of keys the storage can hold.
 * @return Key capacity.
 */
s16 LibFloatQuaternionTrackBase::get_key_capacity()
{
    return state.key_capacity;
}

/**
 * @brief Store a keyframe; the base ignores it.
 */
s32 LibFloatQuaternionTrackBase::on_append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return 0;
}

/**
 * @brief Store a keyframe; the base ignores it.
 */
s32 LibFloatQuaternionTrackBase::on_replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return 0;
}

/**
 * @brief Store a keyframe; the base ignores it.
 */
s32 LibFloatQuaternionTrackBase::on_insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return 0;
}

/**
 * @brief Store a keyframe; the base ignores it.
 */
void LibFloatQuaternionTrackBase::on_set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
}

/**
 * @brief Test whether a key is stored exactly.
 * @param key Key to find.
 * @return One when a key equals it, otherwise zero.
 */
s32 LibFloatQuaternionTrackBase::has_key(float key) const
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
 * @brief Return a zero vector, the track's value when it has no keys.
 * @return Zero vector.
 */
FieldVec4A LibFloatQuaternionTrackBase::get_zero_value() const
{
    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Return the last key minus the first, or zero below two keys.
 * @return Key span.
 */
float LibFloatQuaternionTrackBase::get_key_span() const
{
    s32 last_index;
    LibFloatQuaternionTrackKey* last_entry;

    if (state.key_count < 2)
    {
        return 0.0f;
    }

    last_index = state.key_count - 1;
    last_entry = key_array + last_index;
    return last_entry->key - key_array[0].key;
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the value.
 */
void LibFloatQuaternionTrackBase::evaluate(float key, void* output)
{
    *static_cast<FieldVec4B*>(output) = sample(key);
}

/**
 * @brief Adjust a scalar key by whole spans determined from the endpoint records.
 * @param key Scalar key whose normalized span quotient must fit in a signed word.
 * @return Key minus the computed number of endpoint spans, or the key for zero spans.
 */
float LibFloatQuaternionTrackBase::wrap_key(float key) const
{
    s32 last_index = state.key_count - 1;
    LibFloatQuaternionTrackKey* entries = key_array;
    LibFloatQuaternionTrackKey* last = entries + last_index;
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
void* LibFloatQuaternionTrackBase::get_keys()
{
    return key_array;
}

/** @brief Delete the key storage unless it is external, and clear the key pointer. */
void LibFloatQuaternionTrackBase::free_keys()
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
float LibFloatCurveTrackBase::update_cycle_count(float key)
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

        if ((state.before_mode == LIB_TRACK_END_PING_PONG && state.cycle_count < 0) || (state.after_mode == LIB_TRACK_END_PING_PONG && state.cycle_count > 0))
        {
            s32 last_index = state.key_count - 1;
            LibFloatCurveTrackKey* last_entry = key_array + last_index;
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
u8 LibFloatCurveTrackBase::find_surrounding_keys(float key, s32* lower, s32* upper)
{
    s32 index;
    s32 count;
    s32 next;

    if (state.extends_segment)
    {
        if (state.before_mode == LIB_TRACK_END_EXTEND_SEGMENT && state.cycle_count < 0)
        {
            *lower = 0;
            *upper = 1;
            state.search_index = 0;
            return 1;
        }

        if (state.after_mode == LIB_TRACK_END_EXTEND_SEGMENT && state.cycle_count > 0)
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

/** @brief Free the keys. */
LibFloatCurveTrackBase::~LibFloatCurveTrackBase()
{
    free_keys();
}

/**
 * @brief Reset array storage, counts, packed controls, and cached indices.
 */
void LibFloatCurveTrackBase::reset_state()
{
    key_array = 0;
    state.before_mode = LIB_TRACK_END_CYCLE;
    state.after_mode = LIB_TRACK_END_CYCLE;
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
void LibFloatCurveTrackBase::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] key_array;
    key_array = new (0) LibFloatCurveTrackKey[count];
    state.key_capacity = count;

    if (!key_array)
    {
        state.key_capacity = 0;
    }
}

/**
 * @brief Bind an external keyframe array and cache its first-to-last key span.
 * @param count Keyframe count.
 * @param keys External keyframe storage.
 */
void LibFloatCurveTrackBase::bind_keys(s32 count, void* keys)
{
    s32 last_index = count - 1;
    LibFloatCurveTrackKey* last;
    state.external_keys = 1;
    key_array = static_cast<LibFloatCurveTrackKey*>(keys);
    state.key_capacity = count;
    state.key_count = count;
    last = key_array + last_index;
    state.span = last->key - key_array[0].key;
}

/**
 * @brief Set the end mode used before the first key, and note whether either end extends its segment.
 * @param mode LIB_TRACK_END_* mode.
 */
void LibFloatCurveTrackBase::set_before_mode(u32 mode)
{
    state.before_mode = mode;
    state.extends_segment = state.before_mode == LIB_TRACK_END_EXTEND_SEGMENT || state.after_mode == LIB_TRACK_END_EXTEND_SEGMENT;
}

/**
 * @brief Set the end mode used after the last key, and note whether either end extends its segment.
 * @param mode LIB_TRACK_END_* mode.
 */
void LibFloatCurveTrackBase::set_after_mode(u32 mode)
{
    state.after_mode = mode;
    state.extends_segment = state.before_mode == LIB_TRACK_END_EXTEND_SEGMENT || state.after_mode == LIB_TRACK_END_EXTEND_SEGMENT;
}

/**
 * @brief Return how many key spans the last wrapped key was past the first key.
 * @return Signed cycle count.
 */
s32 LibFloatCurveTrackBase::get_cycle_count() const
{
    return state.cycle_count;
}

/**
 * @brief Return the number of stored keys.
 * @return Key count.
 */
s16 LibFloatCurveTrackBase::get_key_count() const
{
    return state.key_count;
}

/**
 * @brief Return the number of keys the storage can hold.
 * @return Key capacity.
 */
s16 LibFloatCurveTrackBase::get_key_capacity()
{
    return state.key_capacity;
}

/**
 * @brief Store a keyframe; the base ignores it.
 */
s32 LibFloatCurveTrackBase::on_append_key(const float* value, const float* in_tangent, const float* out_tangent, float key)
{
    return 0;
}

/**
 * @brief Store a keyframe; the base ignores it.
 */
s32 LibFloatCurveTrackBase::on_replace_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent)
{
    return 0;
}

/**
 * @brief Store a keyframe; the base ignores it.
 */
s32 LibFloatCurveTrackBase::on_insert_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent)
{
    return 0;
}

/**
 * @brief Store a keyframe; the base ignores it.
 */
void LibFloatCurveTrackBase::on_set_single_key(const float* value, const float* in_tangent, const float* out_tangent, float key)
{
}

/**
 * @brief Test whether a key is stored exactly.
 * @param key Key to find.
 * @return One when a key equals it, otherwise zero.
 */
s32 LibFloatCurveTrackBase::has_key(float key) const
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
 * @brief Return the floating-point value 0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
/**
 * @brief Return zero, the track's value when it has no keys.
 * @return Zero.
 */
float LibFloatCurveTrackBase::get_zero_value() const
{
    return 0.0f;
}

/**
 * @brief Return the last key minus the first, or zero below two keys.
 * @return Key span.
 */
float LibFloatCurveTrackBase::get_key_span() const
{
    s32 last_index;
    LibFloatCurveTrackKey* last_entry;

    if (state.key_count < 2)
    {
        return 0.0f;
    }

    last_index = state.key_count - 1;
    last_entry = key_array + last_index;
    return last_entry->key - key_array[0].key;
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the value.
 */
void LibFloatCurveTrackBase::evaluate(float key, void* output)
{
    *static_cast<float*>(output) = sample(key);
}

/**
 * @brief Adjust a scalar key by whole spans determined from the endpoint records.
 * @param key Scalar key whose normalized span quotient must fit in a signed word.
 * @return Key minus the computed number of endpoint spans, or the key for zero spans.
 */
float LibFloatCurveTrackBase::wrap_key(float key) const
{
    s32 last_index = state.key_count - 1;
    LibFloatCurveTrackKey* entries = key_array;
    LibFloatCurveTrackKey* last = entries + last_index;
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
void* LibFloatCurveTrackBase::get_keys()
{
    return key_array;
}

/** @brief Delete the key storage unless it is external, and clear the key pointer. */
void LibFloatCurveTrackBase::free_keys()
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
void float_curve_track_pool_free(LibTrackPool<LibPooledFloatCurveTrack>* pool, LibPooledFloatCurveTrack* track)
{
    pool->free(track);
}

/**
 * @brief Mark a track's pool slot as free.
 * @param pool Pool that owns the track.
 * @param track Track to release.
 */
void float_quaternion_track_pool_free(LibTrackPool<LibPooledFloatQuaternionTrack>* pool, LibPooledFloatQuaternionTrack* track)
{
    pool->free(track);
}

/**
 * @brief Find the value stored with the first exactly equal scalar key.
 * @param key Scalar key to find.
 * @return The first matching value, or zero when the key is absent.
 */
float LibFloatCurveTrackBase::find_key_value(float key)
{
    s32 index;

    for (index = 0; index < state.key_count; index++)
    {
        if (key == key_array[index].key)
        {
            LibFloatCurveTrackKey* entry = key_array + index;
            return entry->value;
        }
    }

    return 0.0f;
}

/**
 * @brief Read the vector value associated with the first exactly equal key.
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A LibFloatQuaternionTrackBase::find_key_value(float key)
{
    s32 index;

    for (index = 0; index < state.key_count; index++)
    {
        if (key == key_array[index].key)
        {
            LibFloatQuaternionTrackKey* entry = key_array + index;
            return *reinterpret_cast<const FieldVec4A*>(&entry->value);
        }
    }

    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Allocate storage for a number of keyframes, dropping any keys the track owned.
 * @param count Keyframes to hold.
 */
void LibFloatQuaternionTrackBase::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] key_array;
    key_array = new (0) LibFloatQuaternionTrackKey[count];
    state.key_capacity = count;

    if (!key_array)
    {
        state.key_capacity = 0;
    }
}

/** @brief Leave the keyframe uninitialized. */
LibFloatQuaternionTrackKey::LibFloatQuaternionTrackKey()
{
}

/**
 * @brief Store a single entry in the cached entry.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Sort value.
 */
void LibFloatCurveTrack::set_single_curve_key(const float* value, const float* in_tangent, const float* out_tangent, float key)
{
    set_before_mode(LIB_TRACK_END_USE_PRE_START_KEY);
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
s32 LibFloatCurveTrack::insert_curve_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent)
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
        LibFloatCurveTrackKey* destination = &key_array[cursor];
        LibFloatCurveTrackKey* source = &key_array[cursor - 1];
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
s32 LibFloatCurveTrack::replace_curve_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent)
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
s32 LibFloatCurveTrack::append_curve_key(const float* value, const float* in_tangent, const float* out_tangent, float key)
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
 * @brief Append a keyframe through on_append_key.
 * @param value Keyframe value.
 * @param in_tangent First auxiliary value.
 * @param out_tangent Second auxiliary value.
 * @param key Sort key.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibFloatQuaternionTrackBase::append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    return on_append_key(static_cast<const FieldVec4A*>(value), static_cast<const FieldVec4A*>(in_tangent), static_cast<const FieldVec4A*>(out_tangent), key);
}

/**
 * @brief Replace a keyframe through on_replace_key.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @param in_tangent First auxiliary value.
 * @param out_tangent Second auxiliary value.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibFloatQuaternionTrackBase::replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    return on_replace_key(index, key, static_cast<const FieldVec4A*>(value), static_cast<const FieldVec4A*>(in_tangent), static_cast<const FieldVec4A*>(out_tangent));
}

/**
 * @brief Insert a keyframe through on_insert_key.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @param in_tangent First auxiliary value.
 * @param out_tangent Second auxiliary value.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibFloatQuaternionTrackBase::insert_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    return on_insert_key(index, key, static_cast<const FieldVec4A*>(value), static_cast<const FieldVec4A*>(in_tangent), static_cast<const FieldVec4A*>(out_tangent));
}

/**
 * @brief Store a single keyframe through on_set_single_key.
 * @param value Keyframe value.
 * @param in_tangent First auxiliary value.
 * @param out_tangent Second auxiliary value.
 * @param key Sort key.
 */
void LibFloatQuaternionTrackBase::set_single_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    on_set_single_key(static_cast<const FieldVec4A*>(value), static_cast<const FieldVec4A*>(in_tangent), static_cast<const FieldVec4A*>(out_tangent), key);
}

/**
 * @brief Append a keyframe through on_append_key.
 * @param value Keyframe value.
 * @param in_tangent Incoming tangent.
 * @param out_tangent Outgoing tangent.
 * @param key Sort key.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibFloatCurveTrackBase::append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    return on_append_key(static_cast<const float*>(value), static_cast<const float*>(in_tangent), static_cast<const float*>(out_tangent), key);
}

/**
 * @brief Replace a keyframe through on_replace_key.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @param in_tangent Incoming tangent.
 * @param out_tangent Outgoing tangent.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibFloatCurveTrackBase::replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    return on_replace_key(index, key, static_cast<const float*>(value), static_cast<const float*>(in_tangent), static_cast<const float*>(out_tangent));
}

/**
 * @brief Insert a keyframe through on_insert_key.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @param in_tangent Incoming tangent.
 * @param out_tangent Outgoing tangent.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibFloatCurveTrackBase::insert_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    return on_insert_key(index, key, static_cast<const float*>(value), static_cast<const float*>(in_tangent), static_cast<const float*>(out_tangent));
}

/**
 * @brief Store a single keyframe through on_set_single_key.
 * @param value Keyframe value.
 * @param in_tangent Incoming tangent.
 * @param out_tangent Outgoing tangent.
 * @param key Sort key.
 */
void LibFloatCurveTrackBase::set_single_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    on_set_single_key(static_cast<const float*>(value), static_cast<const float*>(in_tangent), static_cast<const float*>(out_tangent), key);
}

/**
 * @brief Evaluate the segment at a key.
 * @param key Evaluation key.
 * @return Value at the key.
 */
FieldVec4B LibVectorSegment::interpolate(float key) const
{
    FieldVec4B result;

    get_weights(key, g_vector_segment_weights);
    vu0_blend_four(g_vector_segment_weights, &start_value, &start_tangent);
    vu0_store_vf12(&result);
    return result;
}

/**
 * @brief Evaluate the segment at a key.
 * @param key Evaluation key.
 * @return Value at the key.
 */
float LibFloatSegment::interpolate(float key) const
{
    float weights[4];

    get_weights(key, weights);
    return weights[0] * start_value + weights[1] * end_value + weights[2] * start_tangent + weights[3] * end_tangent;
}

/**
 * @brief Compute the Hermite basis weights at a key.
 * @param key Evaluation key.
 * @param weights Receives the start value, end value, start tangent and end tangent weights.
 */
void LibVectorSegment::get_weights(float key, float* weights) const
{
    float t = (key - start_key) / key_span;
    float rise = 1.0f + 2.0f * t;
    float fall = 3.0f - 2.0f * t;
    float before_squared = (1.0f - t) * (1.0f - t);
    float after = t - 1.0f;
    float after_squared = after * after;
    float squared = t * t;

    weights[0] = after_squared * rise;
    weights[1] = squared * fall;
    weights[2] = before_squared * t;
    weights[3] = after * squared;
}

/**
 * @brief Compute the Hermite basis weights at a key.
 * @param key Evaluation key.
 * @param weights Receives the start value, end value, start tangent and end tangent weights.
 */
void LibFloatSegment::get_weights(float key, float* weights) const
{
    float t = (key - start_key) / key_span;
    float rise = 1.0f + 2.0f * t;
    float fall = 3.0f - 2.0f * t;
    float before_squared = (1.0f - t) * (1.0f - t);
    float after = t - 1.0f;
    float after_squared = after * after;
    float squared = t * t;

    weights[0] = after_squared * rise;
    weights[1] = squared * fall;
    weights[2] = before_squared * t;
    weights[3] = after * squared;
}

/** @brief Clear the cached sample state and reset the keys' bookkeeping. */
void LibPooledSlerpQuaternionTrack::reset_state()
{
    unkB0 = 0;
    unkB4 = 0;
    LibSlerpQuaternionTrackBase::reset_state();
}

/**
 * @brief Report how fast the sampled value was changing.
 * @param output Receives the rate.
 */
void LibPooledSlerpQuaternionTrack::get_value_rate(void* output) const
{
    *static_cast<float*>(output) = value_rate;
}

/** @brief Give the track back to its pool when it came from one, otherwise delete it. */
void LibPooledSlerpQuaternionTrack::release()
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

/** @brief Free the keys and give the track back to g_slerp_quaternion_track_pool. */
void LibPooledSlerpQuaternionTrack::return_to_pool()
{
    LibSlerpQuaternionTrackBase::free_keys();
    slerp_quaternion_track_pool_free(g_slerp_quaternion_track_pool, this);
}

/** @brief Destroy the track. */
LibPooledSlerpQuaternionTrack::~LibPooledSlerpQuaternionTrack()
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", get_end_delta__29LibPooledSlerpQuaternionTrackCFPv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", sample__29LibPooledSlerpQuaternionTrackCFf);

/**
 * @brief Store the single keyframe from plain floats.
 * @param key Sort key.
 * @param value Keyframe value.
 */
void LibPooledFloatTrack::set_single_float_key(float key, float value)
{
    LibFloatKeyTrack::on_set_single_key(&value, key);
}

/**
 * @brief Insert a keyframe.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 */
void LibPooledFloatTrack::insert_float_key(s32 index, float key, float value)
{
    LibFloatKeyTrack::on_insert_key(index, key, &value);
}

/**
 * @brief Replace a keyframe.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 */
void LibPooledFloatTrack::replace_float_key(s32 index, float key, float value)
{
    LibFloatKeyTrack::on_replace_key(index, key, &value);
}

/**
 * @brief Append a keyframe from plain floats.
 * @param key Sort key.
 * @param value Keyframe value.
 */
void LibPooledFloatTrack::append_float_key(float key, float value)
{
    LibFloatKeyTrack::on_append_key(&value, key);
}

/** @brief Give the track back to its pool when it came from one, otherwise delete it. */
void LibPooledFloatTrack::release()
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

/** @brief Free the keys and give the track back to g_float_track_pool. */
void LibPooledFloatTrack::return_to_pool()
{
    LibFloatTrackBase::free_keys();
    float_track_pool_free(g_float_track_pool, this);
}

/** @brief Destroy the track. */
LibPooledFloatTrack::~LibPooledFloatTrack()
{
}

/** @brief Forget the last sampled value and reset the keys' bookkeeping. */
void LibFloatTrack::reset_state()
{
    last_value = 0.0f;
    LibFloatTrackBase::reset_state();
}

/**
 * @brief Report the last key's value minus the first's.
 * @param output Receives the difference; left alone when there are no keys.
 */
void LibFloatTrack::get_end_delta(void* output) const
{
    if (key_array != 0)
    {
        *static_cast<float*>(output) = key_array[state.key_count - 1].value - key_array[0].value;
    }
}

/**
 * @brief Report how fast the sampled value was changing.
 * @param output Receives the rate.
 */
void LibFloatTrack::get_value_rate(void* output) const
{
    *static_cast<float*>(output) = value_rate;
}

/**
 * @brief Store a value and key in the two-entry history and count it, up to two.
 * @param value Value to store.
 * @param key Key to store.
 */
void LibSlerpQuaternionHistory::push_sample(const FieldVec4A* value, float key)
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

/** @brief Forget the stored samples. */
void LibSlerpQuaternionHistory::reset()
{
    sample_count = 0;
    next_index = 0;
    unk14 = 0;
    unk18 = 0;
}

/** @brief Free the keys. */
LibFloatTrackBase::~LibFloatTrackBase()
{
    free_keys();
}

/**
 * @brief Reset float-entry storage, counts, control fields, and cached indices.
 */
void LibFloatTrackBase::reset_state()
{
    key_array = 0;
    state.before_mode = LIB_TRACK_END_CYCLE;
    state.after_mode = LIB_TRACK_END_CYCLE;
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
void LibFloatTrackBase::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] key_array;
    key_array = new (0) LibFloatTrackKey[count];
    state.key_capacity = count;

    if (!key_array)
    {
        state.key_capacity = 0;
    }
}

/**
 * @brief Set the end mode used before the first key, and note whether either end extends its segment.
 * @param mode LIB_TRACK_END_* mode.
 */
void LibFloatTrackBase::set_before_mode(u32 mode)
{
    state.before_mode = mode;
    state.extends_segment = state.before_mode == LIB_TRACK_END_EXTEND_SEGMENT || state.after_mode == LIB_TRACK_END_EXTEND_SEGMENT;
}

/**
 * @brief Set the end mode used after the last key, and note whether either end extends its segment.
 * @param mode LIB_TRACK_END_* mode.
 */
void LibFloatTrackBase::set_after_mode(u32 mode)
{
    state.after_mode = mode;
    state.extends_segment = state.before_mode == LIB_TRACK_END_EXTEND_SEGMENT || state.after_mode == LIB_TRACK_END_EXTEND_SEGMENT;
}

/**
 * @brief Return how many key spans the last wrapped key was past the first key.
 * @return Signed cycle count.
 */
s32 LibFloatTrackBase::get_cycle_count() const
{
    return state.cycle_count;
}

/**
 * @brief Return the number of stored keys.
 * @return Key count.
 */
s16 LibFloatTrackBase::get_key_count() const
{
    return state.key_count;
}

/**
 * @brief Return the number of keys the storage can hold.
 * @return Key capacity.
 */
s16 LibFloatTrackBase::get_key_capacity()
{
    return state.key_capacity;
}

/**
 * @brief Return the floating-point value 0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
/**
 * @brief Return zero, the track's value when it has no keys.
 * @return Zero.
 */
float LibFloatTrackBase::get_zero_value() const
{
    return 0.0f;
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the value.
 */
void LibFloatTrackBase::evaluate(float key, void* output)
{
    *static_cast<float*>(output) = sample(key);
}

/**
 * @brief Return the key storage.
 * @return Key array, or null.
 */
void* LibFloatTrackBase::get_keys()
{
    return key_array;
}

/** @brief Delete the key storage unless it is external, and clear the key pointer. */
void LibFloatTrackBase::free_keys()
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
void float_track_pool_free(LibTrackPool<LibPooledFloatTrack>* pool, LibPooledFloatTrack* track)
{
    pool->free(track);
}

/**
 * @brief Mark a track's pool slot as free.
 * @param pool Pool that owns the track.
 * @param track Track to release.
 */
void slerp_quaternion_track_pool_free(LibTrackPool<LibPooledSlerpQuaternionTrack>* pool, LibPooledSlerpQuaternionTrack* track)
{
    pool->free(track);
}

/**
 * @brief Wrap a key by the span between the first and last entries.
 * @param key Key to wrap using truncation after adjusting negative positions.
 * @return Key with the computed whole spans subtracted.
 */
float LibFloatTrackBase::wrap_key(float key) const
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
float LibFloatTrackBase::find_key_value(float key)
{
    s32 index;

    for (index = 0; index < state.key_count; index++)
    {
        if (key == key_array[index].key)
        {
            LibFloatTrackKey* entry = key_array + index;
            return entry->value;
        }
    }

    return 0.0f;
}

/**
 * @brief Return the last key minus the first, or zero below two keys.
 * @return Key span.
 */
float LibFloatTrackBase::get_key_span() const
{
    s32 last_index;
    LibFloatTrackKey* last_entry;

    if (state.key_count < 2)
    {
        return 0.0f;
    }

    last_index = state.key_count - 1;
    last_entry = key_array + last_index;
    return last_entry->key - key_array[0].key;
}

/**
 * @brief Test whether a key is stored exactly.
 * @param key Key to find.
 * @return One when a key equals it, otherwise zero.
 */
s32 LibFloatTrackBase::has_key(float key) const
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
 * @brief Store a single keyframe through on_set_single_key.
 * @param value Keyframe value.
 * @param in_tangent Unused.
 * @param out_tangent Unused.
 * @param key Sort key.
 */
void LibFloatTrackBase::set_single_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    on_set_single_key(static_cast<const float*>(value), key);
}

/**
 * @brief Store the single key; the base ignores it.
 * @param value Key value.
 * @param key Key position.
 */
void LibFloatTrackBase::on_set_single_key(const float* value, float key)
{
}

/**
 * @brief Insert a keyframe through on_insert_key.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @param in_tangent Unused.
 * @param out_tangent Unused.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibFloatTrackBase::insert_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    return on_insert_key(index, key, static_cast<const float*>(value));
}

/**
 * @brief Insert a key; the base ignores it.
 * @param index Key index.
 * @param key Key position.
 * @param value Key value.
 * @return Zero.
 */
s32 LibFloatTrackBase::on_insert_key(s32 index, float key, const float* value)
{
    return 0;
}

/**
 * @brief Replace a keyframe through on_replace_key.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @param in_tangent Unused.
 * @param out_tangent Unused.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibFloatTrackBase::replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    return on_replace_key(index, key, static_cast<const float*>(value));
}

/**
 * @brief Replace a key; the base ignores it.
 * @param index Key index.
 * @param key Key position.
 * @param value Key value.
 * @return Zero.
 */
s32 LibFloatTrackBase::on_replace_key(s32 index, float key, const float* value)
{
    return 0;
}

/**
 * @brief Append a keyframe through on_append_key.
 * @param value Keyframe value.
 * @param in_tangent Unused.
 * @param out_tangent Unused.
 * @param key Sort key.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibFloatTrackBase::append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    return on_append_key(static_cast<const float*>(value), key);
}

/**
 * @brief Append a key; the base ignores it.
 * @param value Key value.
 * @param key Key position.
 * @return Zero.
 */
s32 LibFloatTrackBase::on_append_key(const float* value, float key)
{
    return 0;
}

/**
 * @brief Bind an external keyframe array and cache its first-to-last key span.
 * @param count Keyframe count.
 * @param keys External keyframe storage.
 */
void LibFloatTrackBase::bind_keys(s32 count, void* keys)
{
    s32 last_index = count - 1;
    state.external_keys = 1;
    key_array = static_cast<LibFloatTrackKey*>(keys);
    state.key_capacity = count;
    state.key_count = count;
    state.span = key_array[last_index].key - key_array[0].key;
}

#define LIB_TRACKS_EMIT_DTOR_FLOAT_KEY_TRACK

/**
 * @brief Store a single keyframe in the cached key and value.
 * @param value Keyframe value.
 * @param key Sort key.
 */
void LibFloatKeyTrack::on_set_single_key(const float* value, float key)
{
    set_before_mode(LIB_TRACK_END_USE_PRE_START_KEY);
    single_key.value = *value;
    single_key.key = key;
}

#define LIB_TRACKS_EMIT_DTOR_FLOAT_KEY_TRACK

/**
 * @brief Read an indexed keyframe.
 * @param index Keyframe index.
 * @param key Receives the sort key.
 * @param value Receives the value.
 * @param first Unused; float keys have no auxiliary values.
 * @param second Unused; float keys have no auxiliary values.
 * @return One when the index is within the capacity, otherwise zero.
 */
s32 LibFloatKeyTrack::read_key(s32 index, float* key, void* value, void* first, void* second) const
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
        *static_cast<float*>(value) = key_array[index].value;
    }

    return 1;
}

#define LIB_TRACKS_EMIT_DTOR_FLOAT_KEY_TRACK

/**
 * @brief Insert a float entry before an existing index and shift following entries.
 * @param index Nonnegative index less than the current count.
 * @param key Key associated with the entry.
 * @param value Entry value to copy.
 * @return One if inserted, or zero if storage is absent, full, or the index is too large.
 */
s32 LibFloatKeyTrack::on_insert_key(s32 index, float key, const float* value)
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
        LibFloatTrackKey* destination = &key_array[cursor];
        LibFloatTrackKey* source = &key_array[cursor - 1];
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

#define LIB_TRACKS_EMIT_DTOR_FLOAT_KEY_TRACK

/**
 * @brief Replace an indexed float entry and update the span when it is the last entry.
 * @param index Nonnegative entry index, checked against capacity.
 * @param key Key associated with the entry.
 * @param value Entry value to copy.
 * @return One if stored, or zero if storage is absent or the index is outside capacity.
 */
s32 LibFloatKeyTrack::on_replace_key(s32 index, float key, const float* value)
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

#define LIB_TRACKS_EMIT_DTOR_FLOAT_KEY_TRACK

/**
 * @brief Append a float entry and update the cached key span.
 * @param value Entry value to copy.
 * @param key Key associated with the entry.
 * @return One if appended, or zero if storage is absent or full.
 */
s32 LibFloatKeyTrack::on_append_key(const float* value, float key)
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

#define LIB_TRACKS_EMIT_DTOR_FLOAT_TRACK
#define LIB_TRACKS_EMIT_DTOR_FLOAT_KEY_TRACK

/** @brief Reset to a single zero keyframe at key zero, then select the cycle end mode. */
void LibFloatTrack::reset_keys()
{
    float zero = 0.0f;
    on_set_single_key(&zero, 0.0f);
    set_before_mode(LIB_TRACK_END_CYCLE);
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @return Evaluated value.
 */
float LibFloatTrack::sample(float key)
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

    if (state.key_count == 1 && (!(key < key_array[0].key) || state.before_mode != LIB_TRACK_END_USE_PRE_START_KEY))
    {
        return key_array[0].value;
    }

    if (key < key_array[0].key && state.before_mode == LIB_TRACK_END_USE_PRE_START_KEY)
    {
        upper = 0;
        wrapped_key = key;
        lower = -1;
    }
    else
    {
        wrapped_key = update_cycle_count(key);

        if (state.before_mode == LIB_TRACK_END_HOLD && state.cycle_count < 0)
        {
            return key_array[0].value;
        }

        if (state.after_mode == LIB_TRACK_END_HOLD && state.cycle_count > 0)
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
        LibFloatTrackKey* first = lower >= 0 ? key_array + lower : &single_key;
        sample_history.reset();
        sample_history.add_sample(first->key, first->value);
        s32 last = state.key_count - 1;
        // Keep a separate index for the upper key to preserve register allocation.
        s32 upper_index = upper;

        if (upper_index == last && ((!(key < key_array[0].key) && state.after_mode == LIB_TRACK_END_CYCLE_TO_FIRST) ||
            (key < key_array[0].key && state.before_mode == LIB_TRACK_END_CYCLE_TO_FIRST)))
        {
            LibFloatTrackKey* entries = key_array;
            sample_history.add_sample(entries[upper_index].key, entries[0].value);
        }
        else if (lower < upper_index)
        {
            LibFloatTrackKey* second = key_array + upper_index;
            sample_history.add_sample(second->key, second->value);
        }
        else
        {
            sample_history.add_sample(key_array[last].key, key_array[upper_index].value);
        }
    }

    result = sample_history.sample(wrapped_key);

    if ((state.before_mode == LIB_TRACK_END_OFFSET_CYCLE && state.cycle_count < 0) ||
        (state.after_mode == LIB_TRACK_END_OFFSET_CYCLE && state.cycle_count > 0))
    {
        float delta = key_array[state.key_count - 1].value - key_array[0].value;
        result += delta * state.cycle_count;
    }

    value_rate = (result - last_value) / g_frame_ticks;
    last_value = result;
    return result;
}

/**
 * @brief Normalize a key across the cached span and store its signed period count.
 * @param key Key whose period count is representable as a signed 32-bit integer.
 * @return Normalized key, with odd-period reflection selected by the control fields.
 */
float LibFloatTrackBase::update_cycle_count(float key)
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

        if ((state.before_mode == LIB_TRACK_END_PING_PONG && state.cycle_count < 0) || (state.after_mode == LIB_TRACK_END_PING_PONG && state.cycle_count > 0))
        {
            s32 last_index = state.key_count - 1;
            LibFloatTrackKey* last_entry = key_array + last_index;
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
u8 LibFloatTrackBase::find_surrounding_keys(float key, s32* lower, s32* upper)
{
    s32 index;
    s32 count;
    s32 next;

    if (state.extends_segment)
    {
        if (state.before_mode == LIB_TRACK_END_EXTEND_SEGMENT && state.cycle_count < 0)
        {
            *lower = 0;
            *upper = 1;
            state.search_index = 0;
            return 1;
        }

        if (state.after_mode == LIB_TRACK_END_EXTEND_SEGMENT && state.cycle_count > 0)
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
 * @brief Slerp the two stored quaternions at a key and report the blend.
 * @param key Evaluation key.
 * @param blend Receives the blend factor when not null.
 * @return Interpolated quaternion.
 */
FieldVec4B LibSlerpQuaternionHistory::sample_with_blend(float key, float* blend)
{
    if (!sample_count)
    {
        return FieldVec4B(0.0f, 0.0f, 0.0f, 0.0f);
    }

    s32 lower;
    s32 upper;
    float fraction = find_blend(key, &lower, &upper);

    if (blend)
    {
        *blend = fraction;
    }

    FieldVec4B result;
    lib_quaternion_slerp_async(&result, &values[lower], &values[upper], fraction);
    return result;
}

/**
 * @brief Slerp the two stored quaternions at a key.
 * @param key Evaluation key.
 * @return Interpolated quaternion.
 */
FieldVec4B LibSlerpQuaternionHistory::sample(float key)
{
    return sample_with_blend(key, 0);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", sample__22LibLinearVectorHistoryFf);

/**
 * @brief Evaluate the history at a key, blending linearly between its two samples.
 * @param key Evaluation key.
 * @return Interpolated value, or zero before any sample.
 */
float LibLinearFloatHistory::sample(float key) const
{
    if (!sample_count)
    {
        return 0.0f;
    }

    s32 lower;
    s32 upper;
    float blend = find_blend(key, &lower, &upper);
    return values[lower] + blend * (values[upper] - values[lower]);
}

/**
 * @brief Add a key and its value to the record.
 * @param key Key.
 * @param value Value at the key.
 */
void LibLinearFloatHistory::add_sample(float key, float value)
{
    LibLinearFloatHistory::push_sample(&value, key);
}

/**
 * @brief Find the two stored samples and how far a key lies between them.
 * @param key Key to place.
 * @param lower Receives the index of the older sample.
 * @param upper Receives the index of the newer sample.
 * @return Blend factor from the older sample to the newer one; zero until both samples are stored.
 */
float LibSlerpQuaternionHistory::find_blend(float key, s32* lower, s32* upper) const
{
    if (sample_count != 2)
    {
        return 0.0f;
    }

    *lower = next_index;
    *upper = *lower ^ 1;
    float span = keys[*upper] - keys[*lower];

    if (span == 0.0f)
    {
        return 0.0f;
    }

    return (key - keys[*lower]) / span;
}

/**
 * @brief Store a value and key in the two-entry history and count it, up to two.
 * @param key Key to store.
 * @param value Value to store.
 */
void LibLinearVectorHistory::push_sample(float key, const FieldVec4A* value)
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
 * @brief Find the two stored samples and how far a key lies between them.
 * @param key Key to place.
 * @param lower Receives the index of the older sample.
 * @param upper Receives the index of the newer sample.
 * @return Blend factor from the older sample to the newer one; zero until both samples are stored.
 */
float LibLinearVectorHistory::find_blend(float key, s32* lower, s32* upper) const
{
    if (sample_count != 2)
    {
        return 0.0f;
    }

    *lower = next_index;
    *upper = *lower ^ 1;
    float span = keys[*upper] - keys[*lower];

    if (span == 0.0f)
    {
        return 0.0f;
    }

    return (key - keys[*lower]) / span;
}

/**
 * @brief Store a value and key in the two-entry history and count it, up to two.
 * @param value Value to store.
 * @param key Key to store.
 */
void LibLinearFloatHistory::push_sample(const float* value, float key)
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
 * @brief Find the two stored samples and how far a key lies between them.
 * @param key Key to place.
 * @param lower Receives the index of the older sample.
 * @param upper Receives the index of the newer sample.
 * @return Blend factor from the older sample to the newer one; zero until both samples are stored.
 */
float LibLinearFloatHistory::find_blend(float key, s32* lower, s32* upper) const
{
    if (sample_count != 2)
    {
        return 0.0f;
    }

    *lower = next_index;
    *upper = *lower ^ 1;
    float span = keys[*upper] - keys[*lower];

    if (span == 0.0f)
    {
        return 0.0f;
    }

    return (key - keys[*lower]) / span;
}

/** @brief Do nothing; the slot's purpose is unknown. */
void LibSlerpQuaternionHistory::func_slot08()
{
}

/** @brief Do nothing; the slot's purpose is unknown. */
void LibLinearVectorHistory::func_slot08()
{
}

s32 func_004B3D60(void* object)
{
    return 0;
}

s32 func_004B3D70(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B3D80);

/**
 * @brief Read a target's translation, rotation and scale from its animation channels.
 *
 * A whole-vector channel wins; otherwise up to three per-axis channels fill the components in order, and
 * per-axis rotation angles are converted to a quaternion.
 * @param object Animation object.
 * @param target Bound target to update.
 */
extern "C" void lib_animation_read_channel_pose(LibAnimation* object, LibAnimationTarget* target)
{
    LibClass173180* channel = lib_animation_find_channel_inline(object, target, LIB_ANIMATION_KIND_TRANSLATION, 0);

    if (channel)
    {
        LibVector4 value;
        channel->get_end_delta(&value);
        copy_vector(&target->channel_translation, &value);
    }
    else
    {
        LibVector4 value;
        value.x = 0.0f;
        value.y = 0.0f;
        value.z = 0.0f;
        value.w = 0.0f;
        u8 found = 0;

        for (s32 i = 0; i < LIB_ANIMATION_AXIS_COUNT; i++)
        {
            channel = lib_animation_find_channel_inline(object, target, LIB_ANIMATION_KIND_TRANSLATION_AXIS, i);

            if (!channel)
            {
                break;
            }

            float component;
            channel->get_end_delta(&component);
            (&value.x)[i] = component;
            found = 1;
        }

        if (found)
        {
            copy_vector(&target->channel_translation, &value);
        }
    }

    channel = lib_animation_find_channel_inline(object, target, LIB_ANIMATION_KIND_ROTATION, 0);

    if (channel)
    {
        LibVector4 value;
        channel->get_end_delta(&value);
        copy_vector(&target->channel_rotation, &value);
    }
    else
    {
        LibVector4 angles;
        angles.x = 0.0f;
        angles.y = 0.0f;
        angles.z = 0.0f;
        angles.w = 0.0f;
        u8 found = 0;

        for (s32 i = 0; i < LIB_ANIMATION_AXIS_COUNT; i++)
        {
            channel = lib_animation_find_channel_inline(object, target, LIB_ANIMATION_KIND_ROTATION_AXIS, i);

            if (!channel)
            {
                break;
            }

            float angle;
            channel->get_end_delta(&angle);
            (&angles.x)[i] = angle;
            found = 1;
        }

        if (found)
        {
            LibVector4 rotation;
            func_004CE040(&rotation, &angles);
            copy_vector(&target->channel_rotation, &rotation);
        }
    }

    channel = lib_animation_find_channel_inline(object, target, LIB_ANIMATION_KIND_SCALE, 0);

    if (channel)
    {
        LibVector4 value;
        channel->get_end_delta(&value);
        copy_vector(&target->channel_scale, &value);
    }
    else
    {
        LibVector4 value;
        value.x = 0.0f;
        value.y = 0.0f;
        value.z = 0.0f;
        value.w = 0.0f;
        u8 found = 0;

        for (s32 i = 0; i < LIB_ANIMATION_AXIS_COUNT; i++)
        {
            channel = lib_animation_find_channel_inline(object, target, LIB_ANIMATION_KIND_SCALE_AXIS, i);

            if (!channel)
            {
                break;
            }

            float component;
            channel->get_end_delta(&component);
            (&value.x)[i] = component;
            found = 1;
        }

        if (found)
        {
            copy_vector(&target->channel_scale, &value);
        }
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B43C0);

/**
 * @brief Apply every eligible animation entry at a frame.
 * @param object Animation object.
 * @param frame Requested frame; a negative frame leaves the animation marked as restarting.
 * @param mode Nonzero to stop at the first entry that returns a nonzero status.
 * @return Status of the last applied entry, or 0 when the animation has no entries.
 */
s32 lib_animation_apply_frame(LibAnimation* object, float frame, s32 mode)
{
    s32 status;
    s32 count;
    u8 restarting;
    s32 index;

    if (object->entries == 0)
    {
        return 0;
    }

    object->unk60 = 0;
    object->unk48 = 0;
    status = 0;
    restarting = !object->started;
    count = object->entry_count;

    for (index = 0; index < count; index++)
    {
        LibAnimationEntry14* entry = &object->entries[index];

        if (entry->channel != 0)
        {
            if (entry->target != 0 || (entry->kind >= LIB_ANIMATION_KIND_UNBOUND_FIRST && entry->kind < LIB_ANIMATION_KIND_UNBOUND_END))
            {
                if (entry->flags & LIB_ANIMATION_ENTRY_SKIP)
                {
                    continue;
                }

                if (!(entry->flags & LIB_ANIMATION_ENTRY_RESTART_ONLY) || restarting)
                {
                    if (object->unk60 == entry->target)
                    {
                        status = func_004B4840(object, entry, (float)(s32)frame, mode, status);
                    }
                    else
                    {
                        object->unk60 = 0;
                        status = func_004B4840(object, entry, frame, mode, status);
                    }
                }
            }
        }

        if (mode != 0 && status != 0)
        {
            break;
        }
    }

    if (!(frame < 0.0f))
    {
        object->started = 1;
    }

    return status;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B46E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B4840);

}

