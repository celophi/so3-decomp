#include "include_asm.h"
#include "overlays/lib/text_004AB8B0.h"
#include "main/resident_data.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/lib/vector_vu0.h"

extern LibTrackPool<LibClass177EE0>* g_track_1718C0_pool;
extern LibTrackPool<LibPooledFloatTrack>* g_float_track_pool;
extern LibTrackPool<LibPooledFloatCurveTrack>* g_float_curve_track_pool;
extern LibTrackPool<LibPooledFloatQuaternionTrack>* g_float_quaternion_track_pool;

/**
 * @brief Mark a track's g_track_1718C0_pool slot as free.
 * @param pool Pool that owns the track.
 * @param track Track to release.
 */
void track_1718C0_pool_free(LibTrackPool<LibClass177EE0>* pool, LibClass177EE0* track);

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

typedef struct HalfwordGetterOwnertext_004AB8B0
{
    u8 unk00[0x18];
    s16 unk18;
    s16 unk1a;
    u8 unk1c[0x4];
    s16 unk20;
    s16 unk22;
    u8 unk24[0x14];
    s16 unk38;
    s16 unk3a;
} HalfwordGetterOwnertext_004AB8B0;

typedef struct WordGetterOwnertext_004AB8B0
{
    u8 unk00[0x4];
    u32 unk04;
    u8 unk08[0x8];
    u32 unk10;
    u8 unk14[0x4];
    u32 unk18;
    u8 unk1c[0x14];
    u32 unk30;
} WordGetterOwnertext_004AB8B0;

typedef struct FourWordClearOwnertext_004AB8B0 { u32 words[4]; } FourWordClearOwnertext_004AB8B0;

typedef struct ClearForwardWordOwnertext_004AB8B0
{
    u8 unk00[0x48];
    u32 unk48;
    u32 unk4c;
} ClearForwardWordOwnertext_004AB8B0;

typedef struct PackedModePair
{
    u8 lowMode : 4;
    u8 highMode : 4;
    u8 hasModeFour : 1;
    u8 unk01_1_7 : 7;
} PackedModePair;

typedef struct PackedModesOwner
{
    u8 unk00[0x22];
    PackedModePair at22;
    u8 unk24[0x6];
    PackedModePair at2a;
    u8 unk2c[0x16];
    PackedModePair at42;
} PackedModesOwner;

typedef struct FloatKeyScanEntry_text_004AB8B0_08
{
    float key00;
    u8 unk04[0x4];
} FloatKeyScanEntry_text_004AB8B0_08;

typedef struct FloatKeyScanOwner_text_004AB8B0_08
{
    u8 unk00[0x4];
    FloatKeyScanEntry_text_004AB8B0_08* entries;
    u8 unk08[0x10];
    s16 count18;
    u8 unk1a[0x6];
    s16 count20;
    u8 unk22[0x16];
    s16 count38;
} FloatKeyScanOwner_text_004AB8B0_08;

typedef struct FloatKeyScanEntry_text_004AB8B0_10
{
    float key00;
    u8 unk04[0x8];
    float key0c;
} FloatKeyScanEntry_text_004AB8B0_10;

typedef struct FloatDiffEntry_text_004AB8B0_10
{
    u32 unk00;
    float value;
    u8 unk08[8];
} FloatDiffEntry_text_004AB8B0_10;

typedef struct FloatDiffEntry_text_004AB8B0_08
{
    u32 unk00;
    float value;
} FloatDiffEntry_text_004AB8B0_08;

typedef struct FloatKeyScanOwner_text_004AB8B0_10
{
    u8 unk00[0x4];
    FloatKeyScanEntry_text_004AB8B0_10* entries;
    u8 unk08[0x10];
    s16 count18;
    u8 unk1a[0x6];
    s16 count20;
    u8 unk22[0x16];
    s16 count38;
} FloatKeyScanOwner_text_004AB8B0_10;

typedef struct FloatKeyScanEntry_text_004AB8B0_20
{
    float key00;
    u8 unk04[0x8];
    float key0c;
    u8 unk10[0x10];
} FloatKeyScanEntry_text_004AB8B0_20;

typedef struct FloatKeyScanOwner_text_004AB8B0_20
{
    u8 unk00[0x4];
    FloatKeyScanEntry_text_004AB8B0_20* entries;
    u8 unk08[0x10];
    s16 count18;
    u8 unk1a[0x6];
    s16 count20;
    u8 unk22[0x16];
    s16 count38;
} FloatKeyScanOwner_text_004AB8B0_20;

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
void LibClass178200::reset()
{
    sample_count = 0;
    next_index = 0;
    unk08 = 0;
    unk0C = 0;
}

/** @brief Do nothing; the slot's purpose is unknown. */
void LibClass178200::func_slot08()
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
s32 LibClass177AC0::read_key(s32 index, float* key, void* value, void* first, void* second) const
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
float LibClass177B50::update_cycle_count(float key)
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
            LibTrackKey177B50* last_entry = key_array + last_index;
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
u8 LibClass177B50::find_surrounding_keys(float key, s32* lower, s32* upper)
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", __dt__14LibClass177B50Fv);

/** @brief Clear the key storage, counts, modes and cached indices. */
void LibClass177B50::reset_state()
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
void LibClass177B50::bind_keys(s32 count, void* keys)
{
    s32 last_index = count - 1;
    LibTrackKey177B50* last;
    state.external_keys = 1;
    key_array = static_cast<LibTrackKey177B50*>(keys);
    state.key_capacity = count;
    state.key_count = count;
    last = key_array + last_index;
    state.span = last->key - key_array[0].key;
}

/** Set the low packed mode at 0x42 and record whether either mode equals four. */
void func_004AC850(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at42.lowMode = mode;
    receiver->at42.hasModeFour = receiver->at42.lowMode == 4 || receiver->at42.highMode == 4;
}

/** Set the high packed mode at 0x42 and record whether either mode equals four. */
void func_004AC8B0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at42.highMode = mode;
    receiver->at42.hasModeFour = receiver->at42.lowMode == 4 || receiver->at42.highMode == 4;
}

/** Return the word at receiver offset 0x30. */
u32 func_004AC910(const void* object)
{
    const WordGetterOwnertext_004AB8B0* receiver = (const WordGetterOwnertext_004AB8B0*)object;
    return receiver->unk30;
}

/** Return the signed halfword at receiver offset 0x38. */
s16 func_004AC920(const void* object)
{
    const HalfwordGetterOwnertext_004AB8B0* receiver = (const HalfwordGetterOwnertext_004AB8B0*)object;
    return receiver->unk38;
}

/** Return the signed halfword at receiver offset 0x3A. */
s16 func_004AC930(const void* object)
{
    const HalfwordGetterOwnertext_004AB8B0* receiver = (const HalfwordGetterOwnertext_004AB8B0*)object;
    return receiver->unk3a;
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_004AC940(void* object, float key)
{
    FloatKeyScanOwner_text_004AB8B0_20* receiver = static_cast<FloatKeyScanOwner_text_004AB8B0_20*>(object);
    s16 count = receiver->count38;
    s32 index;

    for (index = 0; index < count; index++)
    {
        if (key == receiver->entries[index].key00)
        {
            return 1;
        }
    }

    return 0;
}

void func_004AC990(void* object)
{
    FourWordClearOwnertext_004AB8B0* receiver = (FourWordClearOwnertext_004AB8B0*)object;
    receiver->words[0] = 0;
    receiver->words[1] = 0;
    receiver->words[2] = 0;
    receiver->words[3] = 0;
}

/** Return the key span between the first and last entries. */
float func_004AC9B0(void* object)
{
    const FloatKeyScanOwner_text_004AB8B0_20* receiver = static_cast<const FloatKeyScanOwner_text_004AB8B0_20*>(object);
    s32 count = receiver->count38;

    if (count < 2)
    {
        return 0.0f;
    }

    const FloatKeyScanEntry_text_004AB8B0_20* entries = receiver->entries;
    const FloatKeyScanEntry_text_004AB8B0_20* lastEntry = entries + --count;
    float first = entries[0].key00;
    float last = lastEntry->key00;
    return last - first;
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the vector.
 */
void LibClass177B50::evaluate(float key, void* output)
{
    *static_cast<FieldVec4B*>(output) = sample(key);
}

/**
 * @brief Move a key into the first key span by whole spans.
 * @param key Key to wrap.
 * @return Key minus the whole spans it lies past the first key, or the key itself.
 */
float LibClass177B50::wrap_key(float key) const
{
    s32 last_index = state.key_count - 1;
    LibTrackKey177B50* keys = key_array;
    LibTrackKey177B50* last = keys + last_index;
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

/** Return the word at receiver offset 0x4. */
u32 func_004ACAE0(const void* object)
{
    const WordGetterOwnertext_004AB8B0* receiver = (const WordGetterOwnertext_004AB8B0*)object;
    return receiver->unk04;
}

/** @brief Delete the key storage unless it is external, and clear the key pointer. */
void LibClass177B50::free_keys()
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
FieldVec4A LibClass177B50::find_key_value(float key)
{
    s32 index;

    for (index = 0; index < state.key_count; index++)
    {
        if (key == key_array[index].key)
        {
            LibTrackKey177B50* entry = key_array + index;
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
void LibClass177B50::set_single_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    on_set_single_key(static_cast<const FieldVec4A*>(value), key);
}

void func_004ACBD0(void* object)
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
s32 LibClass177B50::insert_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    return on_insert_key(index, key, static_cast<const FieldVec4A*>(value));
}

s32 func_004ACC10(void* object)
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
s32 LibClass177B50::replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    return on_replace_key(index, key, static_cast<const FieldVec4A*>(value));
}

s32 func_004ACC50(void* object)
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
s32 LibClass177B50::append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    return on_append_key(static_cast<const FieldVec4A*>(value), key);
}

s32 func_004ACC90(void* object)
{
    return 0;
}

/**
 * @brief Allocate storage for a number of keyframes, dropping any keys the track owned.
 * @param count Keyframes to hold.
 */
void LibClass177B50::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] key_array;
    key_array = new (0) LibTrackKey177B50[count];
    state.key_capacity = count;

    if (!key_array)
    {
        state.key_capacity = 0;
    }
}

/** @brief Leave the keyframe uninitialized. */
LibTrackKey177B50::LibTrackKey177B50()
{
}

/**
 * @brief Store a single keyframe in the cached key and value, and use it before the first key.
 * @param value Keyframe value.
 * @param key Sort key.
 */
void LibClass177AC0::on_set_single_key(const FieldVec4A* value, float key)
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
s32 LibClass177AC0::on_insert_key(s32 index, float key, const FieldVec4A* value)
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
s32 LibClass177AC0::on_replace_key(s32 index, float key, const FieldVec4A* value)
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
s32 LibClass177AC0::on_append_key(const FieldVec4A* value, float key)
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

typedef struct LibResetWrapperState004ACFF0
{
    u8 unk00[0x50];
    u32 unk50;
    u8 unk54[4];
    u32 unk58;
} LibResetWrapperState004ACFF0;

void func_004ACFF0(void* object)
{
    LibResetWrapperState004ACFF0* receiver = (LibResetWrapperState004ACFF0*)object;
    receiver->unk58 = 0;
    receiver->unk50 = 0;
    static_cast<LibFloatQuaternionTrackBase*>(object)->LibFloatQuaternionTrackBase::reset_state();
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AD010);

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

void func_004AD2B0(const void* object, float* value)
{
    *value = *(const float*)((const u8*)object + 0x54);
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

void func_004AD380(void* object)
{
    static_cast<LibFloatQuaternionTrackBase*>(object)->free_keys();
    float_quaternion_track_pool_free(g_float_quaternion_track_pool, static_cast<LibPooledFloatQuaternionTrack*>(object));
}

/** @brief Destroy the track. */
LibPooledFloatQuaternionTrack::~LibPooledFloatQuaternionTrack()
{
}

/** Set the low packed mode at 0x42 and record whether either mode equals four. */
void func_004AD410(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at42.lowMode = mode;
    receiver->at42.hasModeFour = receiver->at42.lowMode == 4 || receiver->at42.highMode == 4;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AD470);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AD770);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AD860);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ADC60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AE5A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AE7E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AEFE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AEFF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AF060);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AF6A0);

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

void func_004AF8A0(void* object)
{
    ((ClearForwardWordOwnertext_004AB8B0*)object)->unk4c = 0;
    static_cast<LibFloatCurveTrackBase*>(object)->LibFloatCurveTrackBase::reset_state();
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

void func_004AFF60(const void* object, float* value)
{
    *value = *(const float*)((const u8*)object + 0x50);
}

void func_004AFF70(const void* object, float* output)
{
    const FloatKeyScanOwner_text_004AB8B0_10* receiver = (const FloatKeyScanOwner_text_004AB8B0_10*)object;
    FloatDiffEntry_text_004AB8B0_10* entries = (FloatDiffEntry_text_004AB8B0_10*)receiver->entries;

    if (entries != 0)
    {
        *output = entries[receiver->count20 - 1].value - entries[0].value;
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

/** Set the high packed mode at 0x42 and record whether either mode equals four. */
void func_004B05A0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at42.highMode = mode;
    receiver->at42.hasModeFour = receiver->at42.lowMode == 4 || receiver->at42.highMode == 4;
}

/** Return the word at receiver offset 0x30. */
u32 func_004B0600(const void* object)
{
    const WordGetterOwnertext_004AB8B0* receiver = (const WordGetterOwnertext_004AB8B0*)object;
    return receiver->unk30;
}

/** Return the signed halfword at receiver offset 0x38. */
s16 func_004B0610(const void* object)
{
    const HalfwordGetterOwnertext_004AB8B0* receiver = (const HalfwordGetterOwnertext_004AB8B0*)object;
    return receiver->unk38;
}

/** Return the signed halfword at receiver offset 0x3A. */
s16 func_004B0620(const void* object)
{
    const HalfwordGetterOwnertext_004AB8B0* receiver = (const HalfwordGetterOwnertext_004AB8B0*)object;
    return receiver->unk3a;
}

s32 func_004B0630(void* object)
{
    return 0;
}

s32 func_004B0640(void* object)
{
    return 0;
}

s32 func_004B0650(void* object)
{
    return 0;
}

void func_004B0660(void* object)
{
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_004B0670(void* object, float key)
{
    FloatKeyScanOwner_text_004AB8B0_20* receiver = static_cast<FloatKeyScanOwner_text_004AB8B0_20*>(object);
    s16 count = receiver->count38;
    s32 index;

    for (index = 0; index < count; index++)
    {
        if (key == receiver->entries[index].key00)
        {
            return 1;
        }
    }

    return 0;
}

void func_004B06C0(void* object)
{
    FourWordClearOwnertext_004AB8B0* receiver = (FourWordClearOwnertext_004AB8B0*)object;
    receiver->words[0] = 0;
    receiver->words[1] = 0;
    receiver->words[2] = 0;
    receiver->words[3] = 0;
}

/** Return the key span between the first and last entries. */
float func_004B06E0(void* object)
{
    const FloatKeyScanOwner_text_004AB8B0_20* receiver = static_cast<const FloatKeyScanOwner_text_004AB8B0_20*>(object);
    s32 count = receiver->count38;

    if (count < 2)
    {
        return 0.0f;
    }

    const FloatKeyScanEntry_text_004AB8B0_20* entries = receiver->entries;
    const FloatKeyScanEntry_text_004AB8B0_20* lastEntry = entries + --count;
    float first = entries[0].key00;
    float last = lastEntry->key00;
    return last - first;
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

/** Return the word at receiver offset 0x4. */
u32 func_004B0810(const void* object)
{
    const WordGetterOwnertext_004AB8B0* receiver = (const WordGetterOwnertext_004AB8B0*)object;
    return receiver->unk04;
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", __dt__22LibFloatCurveTrackBaseFv);

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

/** Set the low packed mode at 0x2A and record whether either mode equals four. */
void func_004B0CA0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at2a.lowMode = mode;
    receiver->at2a.hasModeFour = receiver->at2a.lowMode == 4 || receiver->at2a.highMode == 4;
}

/** Set the high packed mode at 0x2A and record whether either mode equals four. */
void func_004B0D00(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at2a.highMode = mode;
    receiver->at2a.hasModeFour = receiver->at2a.lowMode == 4 || receiver->at2a.highMode == 4;
}

/** Return the word at receiver offset 0x18. */
u32 func_004B0D60(const void* object)
{
    const WordGetterOwnertext_004AB8B0* receiver = (const WordGetterOwnertext_004AB8B0*)object;
    return receiver->unk18;
}

/** Return the signed halfword at receiver offset 0x20. */
s16 func_004B0D70(const void* object)
{
    const HalfwordGetterOwnertext_004AB8B0* receiver = (const HalfwordGetterOwnertext_004AB8B0*)object;
    return receiver->unk20;
}

/** Return the signed halfword at receiver offset 0x22. */
s16 func_004B0D80(const void* object)
{
    const HalfwordGetterOwnertext_004AB8B0* receiver = (const HalfwordGetterOwnertext_004AB8B0*)object;
    return receiver->unk22;
}

s32 func_004B0D90(void* object)
{
    return 0;
}

s32 func_004B0DA0(void* object)
{
    return 0;
}

s32 func_004B0DB0(void* object)
{
    return 0;
}

void func_004B0DC0(void* object)
{
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_004B0DD0(void* object, float key)
{
    FloatKeyScanOwner_text_004AB8B0_10* receiver = static_cast<FloatKeyScanOwner_text_004AB8B0_10*>(object);
    s16 count = receiver->count20;
    s32 index;

    for (index = 0; index < count; index++)
    {
        if (key == receiver->entries[index].key00)
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
float func_004B0E20(void* object)
{
    return 0.0f;
}

/** Return the key span between the first and last entries. */
float func_004B0E30(void* object)
{
    const FloatKeyScanOwner_text_004AB8B0_10* receiver = static_cast<const FloatKeyScanOwner_text_004AB8B0_10*>(object);
    s32 count = receiver->count20;

    if (count < 2)
    {
        return 0.0f;
    }

    const FloatKeyScanEntry_text_004AB8B0_10* entries = receiver->entries;
    const FloatKeyScanEntry_text_004AB8B0_10* lastEntry = entries + --count;
    float first = entries[0].key00;
    float last = lastEntry->key00;
    return last - first;
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

/** Return the word at receiver offset 0x4. */
u32 func_004B0F40(const void* object)
{
    const WordGetterOwnertext_004AB8B0* receiver = (const WordGetterOwnertext_004AB8B0*)object;
    return receiver->unk04;
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

typedef struct LibResetWrapperState004B1800
{
    u8 unk00[0xB0];
    u32 unkB0;
    u32 unkB4;
} LibResetWrapperState004B1800;

void func_004B1800(void* object)
{
    LibResetWrapperState004B1800* receiver = (LibResetWrapperState004B1800*)object;
    receiver->unkB0 = 0;
    receiver->unkB4 = 0;
    static_cast<LibClass177B50*>(object)->LibClass177B50::reset_state();
}

void func_004B1820(const void* object, float* value)
{
    *value = *(const float*)((const u8*)object + 0xB8);
}

/** @brief Give the track back to its pool when it came from one, otherwise delete it. */
void LibClass177EE0::release()
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

void func_004B1890(void* object)
{
    static_cast<LibClass177B50*>(object)->free_keys();
    track_1718C0_pool_free(g_track_1718C0_pool, static_cast<LibClass177EE0*>(object));
}

/** @brief Destroy the track. */
LibClass177EE0::~LibClass177EE0()
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B1930);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B1A50);

void func_004B24A0(void* object, float value1, float value2)
{
    static_cast<LibFloatKeyTrack*>(object)->LibFloatKeyTrack::on_set_single_key(&value2, value1);
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

void func_004B2500(void* object, float value1, float value2)
{
    static_cast<LibFloatKeyTrack*>(object)->LibFloatKeyTrack::on_append_key(&value2, value1);
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

void func_004B2580(void* object)
{
    static_cast<LibFloatTrackBase*>(object)->free_keys();
    float_track_pool_free(g_float_track_pool, static_cast<LibPooledFloatTrack*>(object));
}

/** @brief Destroy the track. */
LibPooledFloatTrack::~LibPooledFloatTrack()
{
}

void func_004B2700(void* object)
{
    ((ClearForwardWordOwnertext_004AB8B0*)object)->unk48 = 0;
    static_cast<LibFloatTrackBase*>(object)->LibFloatTrackBase::reset_state();
}

void func_004B2720(const void* object, float* output)
{
    const FloatKeyScanOwner_text_004AB8B0_10* receiver = (const FloatKeyScanOwner_text_004AB8B0_10*)object;
    FloatDiffEntry_text_004AB8B0_08* entries = (FloatDiffEntry_text_004AB8B0_08*)receiver->entries;

    if (entries != 0)
    {
        *output = entries[receiver->count18 - 1].value - entries[0].value;
    }
}

void func_004B2750(const void* object, float* value)
{
    *value = *(const float*)((const u8*)object + 0x4C);
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", __dt__17LibFloatTrackBaseFv);

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

/** Set the low packed mode at 0x22 and record whether either mode equals four. */
void func_004B29A0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at22.lowMode = mode;
    receiver->at22.hasModeFour = receiver->at22.lowMode == 4 || receiver->at22.highMode == 4;
}

/** Set the high packed mode at 0x22 and record whether either mode equals four. */
void func_004B2A00(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at22.highMode = mode;
    receiver->at22.hasModeFour = receiver->at22.lowMode == 4 || receiver->at22.highMode == 4;
}

/** Return the word at receiver offset 0x10. */
u32 func_004B2A60(const void* object)
{
    const WordGetterOwnertext_004AB8B0* receiver = (const WordGetterOwnertext_004AB8B0*)object;
    return receiver->unk10;
}

/** Return the signed halfword at receiver offset 0x18. */
s16 func_004B2A70(const void* object)
{
    const HalfwordGetterOwnertext_004AB8B0* receiver = (const HalfwordGetterOwnertext_004AB8B0*)object;
    return receiver->unk18;
}

/** Return the signed halfword at receiver offset 0x1A. */
s16 func_004B2A80(const void* object)
{
    const HalfwordGetterOwnertext_004AB8B0* receiver = (const HalfwordGetterOwnertext_004AB8B0*)object;
    return receiver->unk1a;
}

/**
 * @brief Return the floating-point value 0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_004B2A90(void* object)
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

/** Return the word at receiver offset 0x4. */
u32 func_004B2AD0(const void* object)
{
    const WordGetterOwnertext_004AB8B0* receiver = (const WordGetterOwnertext_004AB8B0*)object;
    return receiver->unk04;
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
void track_1718C0_pool_free(LibTrackPool<LibClass177EE0>* pool, LibClass177EE0* track)
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

/** Return the key span between the first and last entries. */
float func_004B2CC0(void* object)
{
    const FloatKeyScanOwner_text_004AB8B0_08* receiver = static_cast<const FloatKeyScanOwner_text_004AB8B0_08*>(object);
    s32 count = receiver->count18;

    if (count < 2)
    {
        return 0.0f;
    }

    const FloatKeyScanEntry_text_004AB8B0_08* entries = receiver->entries;
    const FloatKeyScanEntry_text_004AB8B0_08* lastEntry = entries + --count;
    float first = entries[0].key00;
    float last = lastEntry->key00;
    return last - first;
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_004B2D10(void* object, float key)
{
    FloatKeyScanOwner_text_004AB8B0_08* receiver = static_cast<FloatKeyScanOwner_text_004AB8B0_08*>(object);
    s16 count = receiver->count18;
    s32 index;

    for (index = 0; index < count; index++)
    {
        if (key == receiver->entries[index].key00)
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

void func_004B2D90(void* object)
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

s32 func_004B2DD0(void* object)
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

s32 func_004B2E10(void* object)
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

s32 func_004B2E50(void* object)
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
float LibClass178200::sample(float key) const
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
void LibClass178200::add_sample(float key, float value)
{
    LibClass178200::push_sample(&value, key);
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
void LibClass178200::push_sample(const float* value, float key)
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
float LibClass178200::find_blend(float key, s32* lower, s32* upper) const
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

