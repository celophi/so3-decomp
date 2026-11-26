#include "include_asm.h"
#include "main/dma_queue.h"
#include "overlays/lib/text_004ABA60.h"
#include "main/resident_data.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/model.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/lib/vector_vu0.h"
#include "overlays/lib/quaternion_vu0.h"
#include "overlays/lib/skin_vu0.h"
#include "ee.h"
#include "overlays/lib/text_0046AE20.h"
#include "overlays/lib/text_004DD440.h"
#include "overlays/lib/image_model.h"
#include "overlays/lib/particle_grid.h"
#include "overlays/lib/scene_objects.h"
#include "overlays/lib/emission.h"

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

extern "C" {

/** @brief Start unattached, with no data. */
LibClass1734B0::LibClass1734B0()
{
    unk0e = 0;
}

/**
 * @brief Return the entry's type code.
 * @return 99.
 */
s32 LibClass177A80::func_slot14()
{
    return 99;
}

/**
 * @brief Nothing to finish.
 * @param channel DMA channel; unused.
 */
void LibClass177A80::complete_dma(u32 channel)
{
}

/**
 * @brief Build the bone matrices into the next of the two uncached matrix buffers: each bone's matrix times its bind
 *        matrix, relative to the root, through the VU0 microprogram at 0x898.
 * @param object Skin entry.
 * @param root Model transform the bones are relative to.
 */
extern "C" void func_004ABAC0(LibClass177A80* object, LibTransform* root)
{
    if (object->second_matrices == 0)
    {
        return;
    }

    object->unk50 ^= 1;
    LibMatrix44Value* output;
    s32 count = object->header->matrix_count;
    LibClass177A20* list = object->list;
    output = (LibMatrix44Value*)((u32)(object->second_matrices + count * object->unk50 + 1) | EE_UNCACHED_ACCELERATED);
    LibTransform** bones = (LibTransform**)object->unk3c;

    if (list->unk8d_3)
    {
        root->transform_dirty = 1;
        root->matrix_ready = 0;
        root->unk51 = 0;

        for (s32 i = 0; i < count; i++)
        {
            LibTransform* bone = bones[i];
            bone->transform_dirty = 1;
            bone->matrix_ready = 0;
            bone->unk51 = 0;
        }
    }

    object->cursor = object->records;

    if (!root->matrix_ready)
    {
        root->update_transform_matrix();
    }

    LibMatrix44Value inverse = func_004CF0B0(root->transform);

    for (s32 i = 0; i < count; i++)
    {
        if (!bones[i]->matrix_ready)
        {
            bones[i]->update_transform_matrix();
        }
    }

    const LibMatrix44Value* first = &bones[0]->transform;
    vu0_skin_load_root(&inverse);
    vu0_skin_load_bone(first, &object->matrices[0]);
    vu0_skin_start();
    s32 total = object->header->matrix_count;

    if (total > 0)
    {
        for (s32 i = 1; i < total; i++)
        {
            const LibMatrix44Value* bone = &bones[i]->transform;
            LibMatrix44Value* bind = &object->matrices[i];
            ee_prefetch(bind);
            vu0_skin_load_bone(bone, bind);
            vu0_skin_store_previous(output);
            vu0_skin_start();
            output++;
        }
    }

    vu0_skin_store_last(output);
}

/**
 * @brief Return the record at the cursor and move past it; each record starts with its size as a halfword.
 * @param index Bit index; unused.
 * @param size Receives the record's size.
 * @return Record.
 */
u8* LibClass177A80::read_record(u32 index, u32* size)
{
    *size = *reinterpret_cast<u16*>(cursor);
    u8* record = cursor;
    cursor = record + *reinterpret_cast<u16*>(record);
    return record;
}

/**
 * @brief Nothing to send.
 * @param channel DMA channel; unused.
 */
void LibClass177A80::submit_dma(u32 channel)
{
}

/** DMA queue of the VIF0 channel. */
extern "C" ResidentDmaQueue* D_001B660C;

/**
 * @brief Build the bone matrices in the scratchpad, behind a VIF UNPACK to VU0 memory 0x10, and send them over VIF0.
 * @param root Model transform the bones are relative to.
 * @return One when the matrices were sent, zero without bones.
 */
s32 LibClass177A80::func_slot1C(LibTransform* root)
{
    s32 count;
    LibTransform** bones = (LibTransform**)unk3c;

    if (bones == 0)
    {
        return 0;
    }

    count = header->matrix_count;
    LibClass177A20* owner = list;

    if (owner->unk8d_3)
    {
        root->transform_dirty = 1;
        root->matrix_ready = 0;
        root->unk51 = 0;

        for (s32 i = 0; i < count; i++)
        {
            LibTransform* bone = bones[i];
            bone->transform_dirty = 1;
            bone->matrix_ready = 0;
            bone->unk51 = 0;
        }
    }

    cursor = records;
    LibMatrix44Value* output = (LibMatrix44Value*)(EE_SCRATCHPAD + 0x10);

    if (!root->matrix_ready)
    {
        root->update_transform_matrix();
    }

    LibMatrix44Value inverse = func_004CF0B0(root->transform);

    for (s32 i = 0; i < count; i++)
    {
        if (!bones[i]->matrix_ready)
        {
            bones[i]->update_transform_matrix();
        }
    }

    const LibMatrix44Value* first = &bones[0]->transform;
    vu0_skin_load_root(&inverse);
    vu0_skin_load_bone(first, &matrices[0]);
    vu0_skin_start();
    s32 total = header->matrix_count;

    if (total > 0)
    {
        for (s32 i = 1; i < total; i++)
        {
            const LibMatrix44Value* bone = &bones[i]->transform;
            LibMatrix44Value* bind = &matrices[i];
            ee_prefetch(bind);
            vu0_skin_load_bone(bone, bind);
            vu0_skin_store_previous(output);
            vu0_skin_start();
            output++;
        }
    }

    s32 quadwords = header->matrix_count * 4;
    u32* tag = (u32*)EE_SCRATCHPAD;
    *(unsigned __int128*)tag = 0;
    tag[3] = (quadwords << 16) | 0x6C000010;
    s32 transfer = quadwords + 1;
    ResidentDmaQueue* queue = D_001B660C;
    queue->current = 0;
    queue->busy = 1;
    *D0_QWC = transfer;
    // TODO: The address only shares the tag's register when it's put back in tag first, so I think the game did that.
    tag = (u32*)(0x80000000 | EE_SCRATCHPAD);
    *D0_MADR = (u32)tag;
    *D_STAT = 1;
    vu0_skin_store_last(output);
    ee_sync();
    *D0_CHCR = 0x101;
    return 1;
}

/**
 * @brief Use borrowed data and build the matrix arrays from it.
 * @param value Borrowed data.
 */
void LibClass177A80::set_borrowed_data(void* value)
{
    data = value;
    data_is_borrowed = 1;
    header = reinterpret_cast<LibClass177A80Header*>(static_cast<u8*>(value) + 0x10);
    unk38 = reinterpret_cast<u8*>(header + 1);
    matrices = new (0) LibMatrix44Value[header->matrix_count];

    if (matrices == 0)
    {
        return;
    }

    unk3c = new (0) u32[header->matrix_count];

    if (unk3c == 0)
    {
        delete matrices;
        matrices = 0;
        return;
    }

    const float* source = reinterpret_cast<const float*>(unk38 + header->matrix_count * 4);
    s32 count = header->matrix_count;

    for (s32 i = 0; i < count; i++)
    {
        matrices[i].set_identity();
        matrices[i].m[0][0] = source[0];
        matrices[i].m[1][0] = source[1];
        matrices[i].m[2][0] = source[2];
        matrices[i].m[0][1] = source[3];
        matrices[i].m[1][1] = source[4];
        matrices[i].m[2][1] = source[5];
        matrices[i].m[0][2] = source[6];
        matrices[i].m[1][2] = source[7];
        matrices[i].m[2][2] = source[8];
        matrices[i].m[0][3] = source[9];
        matrices[i].m[1][3] = source[10];
        matrices[i].m[2][3] = source[11];
        source += 12;
    }

    records = reinterpret_cast<u8*>(header) + header->records_offset;

    if (header->has_second_set)
    {
        second_matrices = new (0) LibMatrix44Value[header->matrix_count * 2 + 2];

        if (second_matrices == 0)
        {
            delete unk3c;
            unk3c = 0;
            delete matrices;
            matrices = 0;
            return;
        }

        FlushCache(0);
    }
}

/** @brief Free the matrix and index arrays. */
LibClass177A80::~LibClass177A80()
{
    delete[] matrices;
    delete[] second_matrices;
    delete[] unk3c;
}

/** @brief Start with no arrays. */
LibClass177A80::LibClass177A80()
{
    unk3c = 0;
    matrices = 0;
    second_matrices = 0;
    unk50 = 0;
    unk19 = 1;
    unk0f = 1;
}

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
bool LibSlerpQuaternionTrackBase::replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
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
bool LibSlerpQuaternionTrackBase::on_replace_key(s32 index, float key, const FieldVec4A* value)
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
bool LibSlerpQuaternionTrackBase::append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    return on_append_key(static_cast<const FieldVec4A*>(value), key);
}

/**
 * @brief Append a key; the base ignores it.
 * @param value Key value.
 * @param key Key position.
 * @return Zero.
 */
bool LibSlerpQuaternionTrackBase::on_append_key(const FieldVec4A* value, float key)
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
bool LibSlerpQuaternionKeyTrack::on_replace_key(s32 index, float key, const FieldVec4A* value)
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
bool LibSlerpQuaternionKeyTrack::on_append_key(const FieldVec4A* value, float key)
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
    offset_cycle = 0;
    last_fraction = 0;
    LibFloatQuaternionTrackBase::reset_state();
}

/**
 * @brief Store a keyframe after the last one and update the span.
 * @param track Track with room for another key.
 * @param value Keyframe rotation.
 * @param first First extra value.
 * @param second Second extra value.
 * @param key Sort key.
 * @return False when the track has no keys allocated or is full.
 */
static inline bool lib_float_quaternion_append(LibPooledFloatQuaternionTrack* track, const FieldVec4A* value, float first,
                                               float second, float key)
{
    if (track->key_array == 0)
    {
        return false;
    }

    if (track->state.key_count >= track->state.key_capacity)
    {
        return false;
    }

    track->key_array[track->state.key_count].value = *value;
    track->key_array[track->state.key_count].first = first;
    track->key_array[track->state.key_count].second = second;
    track->key_array[track->state.key_count].key = key;
    track->state.span = key - track->key_array[0].key;
    track->state.key_count++;
    return true;
}

/**
 * @brief Append a keyframe, with zero for a missing extra value.
 * @param value Keyframe rotation.
 * @param first First extra value, or null for zero.
 * @param second Second extra value, or null for zero.
 * @param key Sort key.
 * @return Whether the keyframe was stored.
 */
bool LibPooledFloatQuaternionTrack::append_key(const void* value, const void* first, const void* second, float key)
{
    float first_value = (first == 0) ? 0.0f : *static_cast<const float*>(first);
    float second_value = (second == 0) ? 0.0f : *static_cast<const float*>(second);
    return lib_float_quaternion_append(this, static_cast<const FieldVec4A*>(value), first_value, second_value, key);
}

/**
 * @brief Store a keyframe over an existing one; replacing the last keyframe updates the span.
 * @param track Track.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe rotation.
 * @param first First extra value.
 * @param second Second extra value.
 * @return False when the track has no keys allocated or the index is past its capacity.
 */
static inline bool lib_float_quaternion_replace(LibPooledFloatQuaternionTrack* track, s32 index, float key,
                                                const FieldVec4A* value, float first, float second)
{
    if (track->key_array == 0)
    {
        return false;
    }

    if (index >= track->state.key_capacity)
    {
        return false;
    }

    track->key_array[index].value = *value;
    track->key_array[index].first = first;
    track->key_array[index].second = second;
    track->key_array[index].key = key;

    if (index == track->state.key_count - 1)
    {
        track->state.span = key - track->key_array[0].key;
    }

    return true;
}

/**
 * @brief Replace a keyframe, with zero for a missing extra value; replacing the last keyframe updates the span.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe rotation.
 * @param first First extra value, or null for zero.
 * @param second Second extra value, or null for zero.
 * @return Whether the keyframe was stored.
 */
bool LibPooledFloatQuaternionTrack::replace_key(s32 index, float key, const void* value, const void* first, const void* second)
{
    float first_value = (first == 0) ? 0.0f : *static_cast<const float*>(first);
    float second_value = (second == 0) ? 0.0f : *static_cast<const float*>(second);
    return lib_float_quaternion_replace(this, index, key, static_cast<const FieldVec4A*>(value), first_value, second_value);
}

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

/**
 * @brief Multiply two quaternions.
 * @param first Left quaternion.
 * @param second Right quaternion.
 * @return first times second.
 */
static inline FieldVec4B lib_quaternion_product(const FieldVec4B& first, const FieldVec4B& second)
{
    FieldVec4B result;
    result.x = first.w * second.x + second.w * first.x + first.y * second.z - first.z * second.y;
    result.y = first.w * second.y + second.w * first.y + first.z * second.x - first.x * second.z;
    result.z = first.w * second.z + second.w * first.z + first.x * second.y - first.y * second.x;
    result.w = first.w * second.w - first.x * second.x - first.y * second.y - first.z * second.z;
    return result;
}

/**
 * @brief Report the rotation from the first key to the last one.
 * @param output Receives the rotation.
 */
void LibPooledFloatQuaternionTrack::get_end_delta(void* output) const
{
    if (key_array == 0)
    {
        return;
    }

    const FieldVec4B* end = &key_array[state.key_count - 1].value;
    FieldVec4B* delta = static_cast<FieldVec4B*>(output);
    FieldVec4B inverse = lib_quaternion_inverse(key_array[0].value);
    *delta = lib_quaternion_product(*end, inverse);
}

/**
 * @brief Insert a keyframe, moving the later keys up.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe rotation.
 * @param first First extra value.
 * @param second Second extra value.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibPooledFloatQuaternionTrack::insert_entry(s32 index, float key, const FieldVec4A* value, float first, float second)
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
    key_array[index].first = first;
    key_array[index].second = second;
    key_array[index].key = key;

    if (index == state.key_count - 1)
    {
        state.span = key - key_array[0].key;
    }

    state.key_count++;
    return 1;
}

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004ABA60", sample_once__24LibPooledQuaternionTrackFf);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004ABA60", pooled_quaternion_track_sample);

/**
 * @brief Evaluate the track at a key without wrapping or extrapolating, and cache the rotation and its change per frame.
 *
 * At or past the last key it returns the last key's rotation and sets the cycle count to one.
 * @param key Evaluation key.
 * @return Evaluated rotation.
 */
FieldVec4A LibPooledFloatQuaternionTrack::sample_once(float key)
{
    FieldVec4B result;

    if (!key_array)
    {
        return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    }

    if (state.key_count == 1)
    {
        return *reinterpret_cast<FieldVec4A*>(&key_array[0].value);
    }

    if (!(key < key_at(state.key_count - 1)))
    {
        state.cycle_count = 1;
        state.search_index = 0;
        return *reinterpret_cast<FieldVec4A*>(&key_array[state.key_count - 1].value);
    }

    state.cycle_count = 0;

    while (state.search_index > 0 && key < key_at(state.search_index))
    {
        state.search_index--;
    }

    if (state.search_index < 0)
    {
        state.search_index = 0;
    }

    while (state.search_index + 1 < state.key_count && !(key < key_at(state.search_index + 1)))
    {
        state.search_index++;
    }

    if (state.search_index >= state.key_count - 1)
    {
        state.search_index = state.key_count - 2;
    }

    if (state.segment_lower != state.search_index)
    {
        state.segment_lower = state.search_index;
        lower_key = &key_array[state.search_index];
        upper_key = &key_array[state.search_index + 1];
    }

    LibFloatQuaternionTrackKey* lower = lower_key;
    LibFloatQuaternionTrackKey* upper = upper_key;
    float t = (key - lower->key) / (upper->key - lower->key);
    float fall = 3.0f - 2.0f * t;
    float before_squared = (1.0f - t) * (1.0f - t);
    float after = t - 1.0f;
    float squared = t * t;
    float end_weight = squared * fall;
    float start_tangent_weight = before_squared * t;
    float end_tangent_weight = after * squared;
    float fraction = end_weight + start_tangent_weight * lower->second + end_tangent_weight * upper->first;

    lib_quaternion_slerp_async(&result, &lower->value, &upper->value, fraction);
    value_rate = g_inverse_frame_ticks * (fraction - last_fraction);
    last_fraction = fraction;
    return *reinterpret_cast<FieldVec4A*>(&result);
}

/**
 * @brief Interpolate the track at a key and cache the blend fraction and its change per frame.
 * @param key Evaluation key.
 * @return Rotation at the key.
 */
FieldVec4A LibPooledFloatQuaternionTrack::sample(float key) const
{
    LibPooledFloatQuaternionTrack* self = const_cast<LibPooledFloatQuaternionTrack*>(this);
    s32 lower;
    s32 upper;
    float wrapped_key;
    float fraction;
    u8 extrapolate;
    FieldVec4B result;

    s16 count;

    if (!key_array || !(count = state.key_count))
    {
        return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    }

    if (state.key_count == 1 && (!(key < key_array[0].key) || state.before_mode != LIB_TRACK_END_USE_PRE_START_KEY))
    {
        return *reinterpret_cast<FieldVec4A*>(&key_array[0].value);
    }

    if (state.search_index >= state.key_capacity)
    {
        self->state.search_index = 0;
    }

    extrapolate = 0;

    if (state.before_mode == LIB_TRACK_END_USE_PRE_START_KEY && key < key_array[0].key)
    {
        upper = 0;
        wrapped_key = key;
        lower = -1;
    }
    else
    {
        wrapped_key = self->update_cycle_count(key);

        if (state.cycle_count != 0)
        {
            if (state.before_mode == LIB_TRACK_END_HOLD && state.cycle_count < 0)
            {
                return *reinterpret_cast<FieldVec4A*>(&key_array[0].value);
            }

            if (state.after_mode == LIB_TRACK_END_HOLD && state.cycle_count > 0)
            {
                return *reinterpret_cast<FieldVec4A*>(&key_array[state.key_count - 1].value);
            }
        }

        extrapolate = self->find_surrounding_keys(wrapped_key, &lower, &upper);

        if (extrapolate)
        {
            wrapped_key = key;
        }
    }

    if (!extrapolate)
    {
        if (state.segment_lower != lower || state.segment_upper != upper)
        {
            self->state.segment_lower = lower;
            self->state.segment_upper = upper;

            if (lower >= 0)
            {
                self->lower_key = key_array + lower;
            }
            else
            {
                self->lower_key = &self->single_key;
            }

            if (upper == state.key_count - 1 && ((!(key < key_array[0].key) && state.after_mode == LIB_TRACK_END_CYCLE_TO_FIRST) ||
                (key < key_array[0].key && state.before_mode == LIB_TRACK_END_CYCLE_TO_FIRST)))
            {
                self->upper_key = key_array;
            }
            else if (lower < upper)
            {
                self->upper_key = key_array + upper;
            }
            else
            {
                self->upper_key = key_array + (state.key_count - 1);
            }
        }

        LibFloatQuaternionTrackKey* second;
        LibFloatQuaternionTrackKey* first = lower_key;
        second = upper_key;
        float t = (wrapped_key - first->key) / (second->key - first->key);
        float after = t - 1.0f;
        float before_squared = (1.0f - t) * (1.0f - t);
        float squared = t * t;
        float end_weight = squared * (3.0f - 2.0f * t);
        float start_tangent_weight = before_squared * t;
        float end_tangent_weight = after * squared;
        t = end_weight + start_tangent_weight * first->second + end_tangent_weight * second->first;

        lib_quaternion_slerp_async(&result, &first->value, &second->value, t);

        if ((state.before_mode == LIB_TRACK_END_OFFSET_CYCLE && state.cycle_count < 0) ||
            (state.after_mode == LIB_TRACK_END_OFFSET_CYCLE && state.cycle_count > 0))
        {
            if (offset_cycle != state.cycle_count)
            {
                const FieldVec4B* end = &key_array[state.key_count - 1].value;
                FieldVec4B delta = lib_quaternion_inverse(key_array[0].value);
                s32 cycle;

                delta = lib_quaternion_product(*end, delta);

                if (state.cycle_count < 0)
                {
                    delta = lib_quaternion_inverse(delta);

                    if (offset_cycle < 0 && state.cycle_count < offset_cycle)
                    {
                        delta = cycle_offset;

                        for (cycle = offset_cycle; cycle > state.cycle_count; cycle--)
                        {
                            vu0_quaternion_multiply_assign_first_in_vf1(&delta, &delta);
                        }
                    }
                    else
                    {
                        for (cycle = 0; cycle > state.cycle_count; cycle--)
                        {
                            vu0_quaternion_multiply_assign_first_in_vf1(&delta, &delta);
                        }
                    }
                }
                else if (offset_cycle > 0 && offset_cycle < state.cycle_count)
                {
                    delta = cycle_offset;

                    for (cycle = offset_cycle; cycle < state.cycle_count; cycle++)
                    {
                        vu0_quaternion_multiply_assign_first_in_vf1(&delta, &delta);
                    }
                }
                else
                {
                    for (cycle = 0; cycle < state.cycle_count; cycle++)
                    {
                        vu0_quaternion_multiply_assign_first_in_vf1(&delta, &delta);
                    }
                }

                self->cycle_offset = delta;
                vu0_quaternion_multiply_assign_first_in_vf1(&result, &delta);
                lib_normalize_quaternion(&result);
                self->offset_cycle = state.cycle_count;
            }
            else
            {
                vu0_quaternion_multiply_assign_first_in_vf1(&result, &cycle_offset);
                lib_normalize_quaternion(&result);
            }
        }
    }
    else if (wrapped_key < key)
    {
        LibFloatQuaternionTrackKey* previous_entry = key_array + (state.key_count - 2);
        LibFloatQuaternionTrackKey* last_entry = key_array + (state.key_count - 1);
        float previous_key = previous_entry->key;
        float last_key = last_entry->key;
        float slope = key_array[state.key_count - 1].first / (last_key - previous_key);
        fraction = 1.0f + slope * (key - last_key);
        lib_quaternion_slerp_async(&result, &previous_entry->value, &last_entry->value, fraction);
    }
    else
    {
        LibFloatQuaternionTrackKey* entries = key_array;
        float first_key = entries[0].key;
        fraction = 1.0f + (entries[0].second / (entries[1].key - first_key)) * (first_key - key);
        lib_quaternion_slerp_async(&result, &entries[1].value, &entries[0].value, fraction);
    }

    self->value_rate = g_inverse_frame_ticks * (fraction - last_fraction);
    self->last_fraction = fraction;
    return *reinterpret_cast<FieldVec4A*>(&result);
}

/** One row of the quadratic fit's system: three coefficients and the right-hand side. */
struct LibFitRow
{
    float value[4];
};

/** The quadratic fit's 3x4 system. */
struct LibMatrix34
{
    LibFitRow rows[3];
};

/**
 * @brief Find one row of a 3x4 system.
 * @param rows Rows.
 * @param index Row.
 * @return The row.
 */
LibFitRow* func_004AEFE0(LibFitRow* rows, s32 index)
{
    return &rows[index];
}

/**
 * @brief Copy a 3x4 system.
 * @param destination Copy.
 * @param source System copied.
 * @return The copy.
 */
LibMatrix34* func_004AEFF0(LibMatrix34* destination, const LibMatrix34* source)
{
    *destination = *source;
    return destination;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004ABA60", compute_tangents__23LibVectorCurveTrackBaseFv);

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
bool LibFloatCurveTrack::append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
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
bool LibFloatCurveTrack::replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
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
bool LibFloatQuaternionTrackBase::on_append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return 0;
}

/**
 * @brief Store a keyframe; the base ignores it.
 */
bool LibFloatQuaternionTrackBase::on_replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
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
bool LibFloatCurveTrackBase::on_append_key(const float* value, const float* in_tangent, const float* out_tangent, float key)
{
    return 0;
}

/**
 * @brief Store a keyframe; the base ignores it.
 */
bool LibFloatCurveTrackBase::on_replace_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent)
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
bool LibFloatCurveTrack::replace_curve_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent)
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
bool LibFloatCurveTrack::append_curve_key(const float* value, const float* in_tangent, const float* out_tangent, float key)
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
bool LibFloatQuaternionTrackBase::append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
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
bool LibFloatQuaternionTrackBase::replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
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
bool LibFloatCurveTrackBase::append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
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
bool LibFloatCurveTrackBase::replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
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
    offset_cycle = 0;
    last_blend = 0;
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

/**
 * @brief Report the rotation from the first key to the last one.
 * @param output Receives the rotation.
 */
void LibPooledSlerpQuaternionTrack::get_end_delta(void* output) const
{
    if (key_array == 0)
    {
        return;
    }

    const FieldVec4B* end = &key_array[state.key_count - 1].value;
    FieldVec4B* delta = static_cast<FieldVec4B*>(output);
    FieldVec4B inverse = lib_quaternion_inverse(key_array[0].value);
    *delta = lib_quaternion_product(*end, inverse);
}

/**
 * @brief Slerp the track at a key through the two-sample history and cache the blend's change per frame.
 * @param key Evaluation key.
 * @return Rotation at the key.
 */
FieldVec4A LibPooledSlerpQuaternionTrack::sample(float key) const
{
    LibPooledSlerpQuaternionTrack* self = const_cast<LibPooledSlerpQuaternionTrack*>(this);
    s32 lower;
    s32 upper;
    float wrapped_key;
    float blend;
    u8 extrapolate;

    if (!key_array || !state.key_count)
    {
        return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    }

    if (state.search_index >= state.key_capacity)
    {
        self->state.search_index = 0;
    }

    if (state.key_count == 1 && (!(key < key_array[0].key) || state.before_mode != LIB_TRACK_END_USE_PRE_START_KEY))
    {
        return *reinterpret_cast<FieldVec4A*>(&key_array[0].value);
    }

    if (key < key_array[0].key && state.before_mode == LIB_TRACK_END_USE_PRE_START_KEY)
    {
        upper = 0;
        wrapped_key = key;
        lower = -1;
    }
    else
    {
        wrapped_key = self->update_cycle_count(key);

        if (state.before_mode == LIB_TRACK_END_HOLD && state.cycle_count < 0)
        {
            return *reinterpret_cast<FieldVec4A*>(&key_array[0].value);
        }

        if (state.after_mode == LIB_TRACK_END_HOLD && state.cycle_count > 0)
        {
            return *reinterpret_cast<FieldVec4A*>(&key_array[state.key_count - 1].value);
        }

        extrapolate = self->find_surrounding_keys(wrapped_key, &lower, &upper);

        if (extrapolate)
        {
            wrapped_key = key;
        }
    }

    if (state.segment_lower != lower || state.segment_upper != upper)
    {
        LibSlerpQuaternionTrackKey* first;

        self->state.segment_lower = lower;
        self->state.segment_upper = upper;

        if (lower >= 0)
        {
            first = key_array + lower;
        }
        else
        {
            first = reinterpret_cast<LibSlerpQuaternionTrackKey*>(&self->single_key);
        }

        self->sample_history.reset();
        self->sample_history.push_sample(first->key, reinterpret_cast<FieldVec4A*>(&first->value));

        s32 last = state.key_count - 1;

        if (upper == last && ((!(key < key_array[0].key) && state.after_mode == LIB_TRACK_END_CYCLE_TO_FIRST) ||
            (key < key_array[0].key && state.before_mode == LIB_TRACK_END_CYCLE_TO_FIRST)))
        {
            self->sample_history.push_sample(key_array[upper].key, reinterpret_cast<FieldVec4A*>(&key_array[0].value));
        }
        else if (lower < upper)
        {
            self->sample_history.push_sample(key_array[upper].key, reinterpret_cast<FieldVec4A*>(&key_array[upper].value));
        }
        else
        {
            self->sample_history.push_sample(key_array[last].key, reinterpret_cast<FieldVec4A*>(&key_array[upper].value));
        }
    }

    FieldVec4B result = self->sample_history.sample_with_blend(wrapped_key, &blend);

    if ((state.before_mode == LIB_TRACK_END_OFFSET_CYCLE && state.cycle_count < 0) ||
        (state.after_mode == LIB_TRACK_END_OFFSET_CYCLE && state.cycle_count > 0))
    {
        if (offset_cycle != state.cycle_count)
        {
            const FieldVec4B* end = &key_array[state.key_count - 1].value;
            FieldVec4B delta = lib_quaternion_inverse(key_array[0].value);

            delta = lib_quaternion_product(*end, delta);

            if (state.cycle_count < 0)
            {
                delta = lib_quaternion_inverse(delta);

                if (offset_cycle < 0 && state.cycle_count < offset_cycle)
                {
                    delta = cycle_offset;

                    for (s32 cycle = offset_cycle; cycle > state.cycle_count; cycle--)
                    {
                        delta = lib_quaternion_product(delta, delta);
                    }
                }
                else
                {
                    for (s32 cycle = 0; cycle > state.cycle_count; cycle--)
                    {
                        delta = lib_quaternion_product(delta, delta);
                    }
                }
            }
            else if (offset_cycle > 0 && offset_cycle < state.cycle_count)
            {
                delta = cycle_offset;

                for (s32 cycle = offset_cycle; cycle < state.cycle_count; cycle++)
                {
                    delta = lib_quaternion_product(delta, delta);
                }
            }
            else
            {
                for (s32 cycle = 0; cycle < state.cycle_count; cycle++)
                {
                    delta = lib_quaternion_product(delta, delta);
                }
            }

            self->cycle_offset = delta;
            result = lib_quaternion_product(result, delta);
            lib_normalize_quaternion(&result);
            self->offset_cycle = state.cycle_count;
        }
        else
        {
            result = lib_quaternion_product(result, cycle_offset);
            lib_normalize_quaternion(&result);
        }
    }

    self->value_rate = (blend - last_blend) / g_frame_ticks;
    self->last_blend = blend;
    return *reinterpret_cast<FieldVec4A*>(&result);
}

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
 * @param key Key to store.
 * @param value Value to store.
 */
void LibSlerpQuaternionHistory::push_sample(float key, const FieldVec4A* value)
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
bool LibFloatTrackBase::replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
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
bool LibFloatTrackBase::on_replace_key(s32 index, float key, const float* value)
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
bool LibFloatTrackBase::append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    return on_append_key(static_cast<const float*>(value), key);
}

/**
 * @brief Append a key; the base ignores it.
 * @param value Key value.
 * @param key Key position.
 * @return Zero.
 */
bool LibFloatTrackBase::on_append_key(const float* value, float key)
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
bool LibFloatKeyTrack::on_replace_key(s32 index, float key, const float* value)
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
bool LibFloatKeyTrack::on_append_key(const float* value, float key)
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

// TODO: this one only matches at level 3 while the rest of the file is level 4. The registers of `upper` and
// the key array swap at level 4, so my source shape is probably off somewhere.
#pragma push
#pragma optimization_level 3

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

#pragma pop

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

/**
 * @brief Interpolate the recorded values linearly at a key.
 * @param key Sample key.
 * @return The value at the key, or zero with nothing recorded.
 */
FieldVec4B LibLinearVectorHistory::sample(float key)
{
    if (sample_count == 0)
    {
        return FieldVec4B(0.0f, 0.0f, 0.0f, 0.0f);
    }

    s32 lower;
    s32 upper;
    float blend = find_blend(key, &lower, &upper);
    FieldVec4B result = (values[upper] - values[lower]) * blend + values[lower];
    return result;
}

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

/**
 * @brief Clear the populated entries bound to a target, when the animation has entries.
 * @param object Animation object.
 * @param target Bound target to remove.
 */
extern "C" void func_004B3D80(LibAnimation* object, const void* target)
{
    if (object->entries)
    {
        s32 count = object->entry_count;

        for (s32 index = 0; index < count; index++)
        {
            LibAnimationEntry14* entry = &object->entries[index];

            if (entry->channel && entry->target == target)
            {
                entry->target = 0;
            }
        }
    }
}

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

/**
 * @brief Apply one animation entry at a frame (func_004B4840's counterpart for func_004B43C0).
 * @param object Animation object.
 * @param entry Entry to apply.
 * @param frame Frame.
 * @param mode Mode passed through.
 * @param status Status so far.
 * @return The entry's status.
 */
extern "C" s32 func_004BD4F0(LibAnimation* object, LibAnimationEntry14* entry, float frame, s32 mode, s32 status);

/**
 * @brief Apply every eligible animation entry at a frame through func_004BD4F0.
 * @param object Animation object.
 * @param frame Requested frame; a negative frame leaves the animation marked as restarting.
 * @param mode Nonzero to stop at the first entry that returns a nonzero status.
 * @return Status of the last applied entry, or 0 when the animation has no entries.
 */
extern "C" s32 func_004B43C0(LibAnimation* object, float frame, s32 mode)
{
    s32 status;
    u8 restarting;
    s32 count;
    s32 index;

    if (object->entries == 0)
    {
        return 0;
    }

    object->longest_channel = 0;
    object->unk60 = 0;
    status = 0;
    restarting = !object->started;
    count = object->entry_count;

    for (index = 0; index < count; index++)
    {
        LibAnimationEntry14* entry = &object->entries[index];

        if (entry->channel != 0)
        {
            if (entry->target != 0 || (entry->kind >= LIB_ANIMATION_KIND_UNBOUND_FIRST && entry->kind < LIB_ANIMATION_KIND_SLOT))
            {
                if (entry->flags & LIB_ANIMATION_ENTRY_SKIP)
                {
                    continue;
                }

                if (!(entry->flags & LIB_ANIMATION_ENTRY_RESTART_ONLY) || restarting)
                {
                    if (object->unk60 == entry->target)
                    {
                        status = func_004BD4F0(object, entry, (float)(s32)frame, mode, status);
                    }
                    else
                    {
                        object->unk60 = 0;
                        status = func_004BD4F0(object, entry, frame, mode, status);
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
    object->longest_channel = 0;
    status = 0;
    restarting = !object->started;
    count = object->entry_count;

    for (index = 0; index < count; index++)
    {
        LibAnimationEntry14* entry = &object->entries[index];

        if (entry->channel != 0)
        {
            if (entry->target != 0 || (entry->kind >= LIB_ANIMATION_KIND_UNBOUND_FIRST && entry->kind < LIB_ANIMATION_KIND_SLOT))
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

/** Partial view of the object at D_001B664C: the scene number animations can be tied to. */
struct LibAnimationScene
{
    u8 unk00[0x14];
    s32 scene;
};

extern "C" LibAnimationScene* D_001B664C;

/**
 * @brief Apply every entry of one target at a frame, when the animation belongs to the current scene.
 * @param object Animation object.
 * @param target Target whose entries to apply.
 * @param frame Requested frame; a negative frame leaves the animation marked as restarting.
 * @param mode Nonzero to stop at the first entry that returns a nonzero status.
 * @return Status of the last applied entry, or 0 when nothing was applied.
 */
extern "C" s32 func_004B46E0(LibAnimation* object, LibAnimationTarget* target, float frame, s32 mode)
{
    if (object->entries == 0)
    {
        return 0;
    }

    if (object->unk6b && object->unk6b - 1 != D_001B664C->scene)
    {
        return 0;
    }

    object->longest_channel = 0;
    s32 status = 0;
    s32 count = object->entry_count;

    for (s32 index = 0; index < count; index++)
    {
        LibAnimationEntry14* entry = &object->entries[index];

        if (entry->target == target)
        {
            if (entry->channel != 0 && entry->target != 0)
            {
                if (!(entry->flags & LIB_ANIMATION_ENTRY_RESTART_ONLY) || !object->started)
                {
                    status = func_004B4840(object, entry, frame, mode, status);
                }
            }

            if (mode != 0 && status != 0)
            {
                break;
            }
        }
    }

    if (!(frame < 0.0f))
    {
        object->started = 1;
    }

    return status;
}

// TODO: These two are the out-of-line copies of FieldVec4B's and LibMatrix44Value's copy constructors that the
// inline assignment operators call here for their returned copies; the copies are plain functions in
// text_004BD360.cpp, so the calls are written out with a by-value return to get the same temporaries.
extern "C" FieldVec4B func_004BD4C0(const FieldVec4B* value);

extern "C" LibMatrix44Value func_004BD3F0(const LibMatrix44Value* source);

/**
 * @brief Assign a vector the way the inlined FieldVec4B operator= does here, with its returned copy.
 * @param value Vector to set.
 * @param other Value to copy.
 * @return The returned copy.
 */
static inline FieldVec4B lib_assign_vector(FieldVec4B* value, const FieldVec4A& other)
{
    value->set(other);
    return func_004BD4C0(value);
}

/**
 * @brief Assign a matrix the way the inlined LibMatrix44Value operator= does here, with its returned copy.
 * @param matrix Matrix to set.
 * @param source Matrix to copy.
 * @return The returned copy.
 */
static inline LibMatrix44Value lib_assign_matrix(LibMatrix44Value* matrix, const LibMatrix44Value* source)
{
    reinterpret_cast<unsigned __int128*>(matrix)[0] = reinterpret_cast<const unsigned __int128*>(source)[0];
    reinterpret_cast<unsigned __int128*>(matrix)[1] = reinterpret_cast<const unsigned __int128*>(source)[1];
    reinterpret_cast<unsigned __int128*>(matrix)[2] = reinterpret_cast<const unsigned __int128*>(source)[2];
    reinterpret_cast<unsigned __int128*>(matrix)[3] = reinterpret_cast<const unsigned __int128*>(source)[3];
    return func_004BD3F0(matrix);
}

/**
 * @brief Copy a rotation into a transform.
 * @param transform Transform.
 * @param value Rotation quaternion.
 */
static inline void lib_copy_orientation(LibOrientedTransform* transform, const FieldVec4A& value)
{
    transform->copy_orientation(reinterpret_cast<const LibVector4*>(&value));
}

/**
 * @brief Set three consecutive floats.
 * @param output First float.
 * @param x First value.
 * @param y Second value.
 * @param z Third value.
 */
static inline void lib_set_float3(float* output, float x, float y, float z)
{
    output[0] = x;
    output[1] = y;
    output[2] = z;
}

/**
 * @brief Change the y of the vector an object keeps at 0x10, through its out-of-line getter and setter.
 * @param object Object holding the vector.
 * @param y New y.
 */
static inline void lib_set_entry_y(void* object, float y)
{
    LibClass173490Entry vector;
    func_00479090(&vector, func_004BD370(object));
    vector.y = y;
    func_004BD360(object, reinterpret_cast<const unsigned __int128*>(&vector));
}

/**
 * @brief Set one channel of a light list's ambient colour, clamping a negative value to zero.
 * @param lights Light list.
 * @param channel Channel, 0 to 2.
 * @param value New value.
 */
static inline void lib_light_list_set_ambient_channel(LibLightList* lights, s32 channel, float value)
{
    if (value < 0.0f)
    {
        value = 0.0f;
    }

    func_004BD3C0(&lights->unk310.x, channel, value);
}

/**
 * @brief Set a camera's fog colour from three channels, each limited to 0 through 1.
 * @param camera Camera.
 * @param red Red.
 * @param green Green.
 * @param blue Blue.
 */
static inline void lib_camera_set_fog_color(LibCamera* camera, float red, float green, float blue)
{
    if (red < 0.0f)
    {
        red = 0.0f;
    }

    if (green < 0.0f)
    {
        green = 0.0f;
    }

    if (blue < 0.0f)
    {
        blue = 0.0f;
    }

    if (!(red <= 1.0f))
    {
        red = 1.0f;
    }

    if (!(green <= 1.0f))
    {
        green = 1.0f;
    }

    if (!(blue <= 1.0f))
    {
        blue = 1.0f;
    }

    red *= 255.0f;
    green *= 255.0f;
    blue *= 255.0f;
    camera->fog_color = (s32)red | ((s32)green << 8) | ((s32)blue << 16);
}

/**
 * @brief Apply one animation entry at a frame: sample its channel and write the value to the entry's target (or
 *        sub-target) the way the entry type says, keeping the channel with the most cycles as the longest.
 * @param object Animation object.
 * @param entry Entry to apply.
 * @param frame Frame.
 * @param mode Nonzero to stop once a channel has more cycles than the status so far; 2 skips the cycle check.
 * @param status Status so far (the most cycles seen).
 * @return The new status.
 */
extern "C" s32 func_004B4840(LibAnimation* object, LibAnimationEntry14* entry, float frame, s32 mode, s32 status)
{
    void* target = entry->target;

    switch (entry->type)
    {
    case 0:
    {
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        value.w = 1.0f;
        static_cast<LibOrientedTransform*>(target)->set_translation_vector(reinterpret_cast<const LibVector4*>(&value));
        break;
    }
    case 1:
    {
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        value.w = 1.0f;
        static_cast<LibOrientedTransform*>(target)->set_translation_vector(reinterpret_cast<const LibVector4*>(&value));
        break;
    }
    case 2:
    {
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        value.w = 1.0f;
        static_cast<LibOrientedTransform*>(target)->set_translation_vector(reinterpret_cast<const LibVector4*>(&value));
        break;
    }
    case 7:
    {
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        value.w = 1.0f;
        static_cast<LibOrientedTransform*>(target)->set_scale_vector(reinterpret_cast<const LibVector4*>(&value));
        break;
    }
    case 8:
    {
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        value.w = 1.0f;
        static_cast<LibOrientedTransform*>(target)->set_scale_vector(reinterpret_cast<const LibVector4*>(&value));
        break;
    }
    case 9:
    {
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        value.w = 1.0f;
        static_cast<LibOrientedTransform*>(target)->set_scale_vector(reinterpret_cast<const LibVector4*>(&value));
        break;
    }
    case 3:
    {
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        lib_copy_orientation(static_cast<LibOrientedTransform*>(target), track->sample(frame));
        break;
    }
    case 4:
    {
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4B value;
        lib_assign_vector(&value, track->sample(frame));
        s32 cycles = track->get_cycle_count();

        if (status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        static_cast<LibOrientedTransform*>(target)->set_orientation(reinterpret_cast<const LibVector4*>(&value));
        break;
    }
    case 5:
    {
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        static_cast<LibOrientedTransform*>(target)->set_orientation(reinterpret_cast<const LibVector4*>(&value));
        break;
    }
    case 6:
    {
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        static_cast<LibOrientedTransform*>(target)->set_orientation(reinterpret_cast<const LibVector4*>(&value));
        break;
    }
    case 10:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        FieldVec4A vector = *static_cast<const FieldVec4A*>(func_004BD4B0(target));
        (&vector.x)[entry->flags & 0xF] = value;
        static_cast<LibOrientedTransform*>(target)->set_translation_vector(reinterpret_cast<const LibVector4*>(&vector));
        break;
    }
    case 11:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        FieldVec4A vector = *static_cast<const FieldVec4A*>(func_004BD4B0(target));
        (&vector.x)[entry->flags & 0xF] = value;
        static_cast<LibOrientedTransform*>(target)->set_translation_vector(reinterpret_cast<const LibVector4*>(&vector));
        break;
    }
    case 12:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        object->unk20[entry->flags & 0xF] = value;

        if ((entry->flags & 0xF) == 2)
        {
            LibVector4 orientation;
            func_004CE040(&orientation, reinterpret_cast<const LibVector4*>(object->unk20));
            static_cast<LibOrientedTransform*>(target)->set_orientation(&orientation);
        }

        break;
    }
    case 13:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        object->unk20[entry->flags & 0xF] = value;

        if ((entry->flags & 0xF) == 2)
        {
            LibVector4 orientation;
            func_004CE040(&orientation, reinterpret_cast<const LibVector4*>(object->unk20));
            static_cast<LibOrientedTransform*>(target)->set_orientation(&orientation);
        }

        break;
    }
    case 14:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        FieldVec4A vector = *static_cast<const FieldVec4A*>(func_004BD4A0(target));
        (&vector.x)[entry->flags & 0xF] = value;
        static_cast<LibOrientedTransform*>(target)->set_scale_vector(reinterpret_cast<const LibVector4*>(&vector));
        break;
    }
    case 15:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        FieldVec4A vector = *static_cast<const FieldVec4A*>(func_004BD4A0(target));
        (&vector.x)[entry->flags & 0xF] = value;
        static_cast<LibOrientedTransform*>(target)->set_scale_vector(reinterpret_cast<const LibVector4*>(&vector));
        break;
    }
    case 16:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        bound->unk214 = value;
        break;
    }
    case 17:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk214 = value;
        break;
    }
    case 18:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk214 = value;
        break;
    }
    case 19:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        object->unk4c = value;
        break;
    }
    case 20:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        object->unk4c = value;
        break;
    }
    case 21:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        object->unk4c = value;
        break;
    }
    case 22:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        func_004DA050(static_cast<LibTransform*>(target), value);
        break;
    }
    case 23:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_004DA050(static_cast<LibTransform*>(target), value);
        break;
    }
    case 24:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_004DA050(static_cast<LibTransform*>(target), value);
        break;
    }
    case 25:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibWordTrackBase* track = static_cast<LibWordTrackBase*>(entry->channel);
        u32 value = track->sample(frame);

        if (value)
        {
            bound->unk208 = value;
        }

        break;
    }
    case 26:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibWordTrackBase* track = static_cast<LibWordTrackBase*>(entry->channel);
        u32 value = track->sample(frame);
        u32 next = track->sample(1.0f + frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        if (bound->unk208 != next)
        {
            object->unk60 = target;
        }

        if (value)
        {
            bound->unk208 = value;
        }

        break;
    }
    case 27:
    {
        LibClass173180* channel = entry->channel;
        LibAimRecord* record = reinterpret_cast<LibAimRecord*>(channel);

        if (!record->target)
        {
            break;
        }

        LibMatrix44Value matrix;

        if (static_cast<LibTransform*>(target)->parent_transform)
        {
            lib_assign_matrix(&matrix, func_004BD420(static_cast<LibTransform*>(target)));
        }
        else
        {
            matrix.set_identity();
        }

        const FieldVec4B* origin = reinterpret_cast<const FieldVec4B*>(&static_cast<LibTransform*>(target)->translation);
        record->roll = object->unk4c;
        FieldVec4B orientation = func_004C3590(record, frame, &matrix, origin);
        s32 cycles = channel->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            status = cycles;
            object->longest_channel = channel;

            if (mode == 1)
            {
                break;
            }
        }

        static_cast<LibOrientedTransform*>(target)->set_orientation(reinterpret_cast<const LibVector4*>(&orientation));
        break;
    }
    case 30:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 rounded = value >= 0.0f ? (s32)(0.5f + value) : (s32)(value - 0.5f);
        LibBlendSubTarget* sub = static_cast<LibBlendSubTarget*>(entry->sub_target);

        if (!sub)
        {
            break;
        }

        if ((entry->flags & 0xF) == 0)
        {
            sub->unk2f0 = rounded;
            break;
        }

        sub->unk2f4 = rounded;
        break;
    }
    case 31:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 rounded = value >= 0.0f ? (s32)(0.5f + value) : (s32)(value - 0.5f);

        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        LibBlendSubTarget* sub = static_cast<LibBlendSubTarget*>(entry->sub_target);

        if (!sub)
        {
            break;
        }

        if ((entry->flags & 0xF) == 0)
        {
            sub->unk2f0 = rounded;
            break;
        }

        sub->unk2f4 = rounded;
        break;
    }
    case 32:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 rounded = value >= 0.0f ? (s32)(0.5f + value) : (s32)(value - 0.5f);

        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        LibBlendSubTarget* sub = static_cast<LibBlendSubTarget*>(entry->sub_target);

        if (!sub)
        {
            break;
        }

        if ((entry->flags & 0xF) == 0)
        {
            sub->unk2f0 = rounded;
            break;
        }

        sub->unk2f4 = rounded;
        break;
    }
    case 33:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 rounded = value >= 0.0f ? (s32)(0.5f + value) : (s32)(value - 0.5f);
        LibBlendSubTarget* sub = static_cast<LibBlendSubTarget*>(entry->sub_target);

        if (sub)
        {
            sub->unk48 = rounded;
        }

        break;
    }
    case 34:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 rounded = value >= 0.0f ? (s32)(0.5f + value) : (s32)(value - 0.5f);

        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        LibBlendSubTarget* sub = static_cast<LibBlendSubTarget*>(entry->sub_target);

        if (sub)
        {
            sub->unk48 = rounded;
        }

        break;
    }
    case 35:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 rounded = value >= 0.0f ? (s32)(0.5f + value) : (s32)(value - 0.5f);

        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        LibBlendSubTarget* sub = static_cast<LibBlendSubTarget*>(entry->sub_target);

        if (sub)
        {
            sub->unk48 = rounded;
        }

        break;
    }
    case 36:
    {
        LibBlendSubTarget* sub = static_cast<LibBlendSubTarget*>(entry->sub_target);

        if (sub)
        {
            sub->unk48 = (s32)frame;
        }

        break;
    }
    case 37:
    {
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);

        if (static_cast<LibTransform*>(target)->type_id == 0x500)
        {
            LibColorModel* model = static_cast<LibClass173990*>(target)->source;
            value.w = model->color_modulation.w;
            func_00479090(&model->color_modulation, &value);
            model->update_combined_color_factor();
            break;
        }

        {
            LibColorModel* model = static_cast<LibColorModel*>(target);
            value.w = model->color_modulation.w;
            func_00479090(&model->color_modulation, &value);
            model->update_combined_color_factor();
        }

        break;
    }
    case 38:
    {
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        if (static_cast<LibTransform*>(target)->type_id == 0x500)
        {
            LibColorModel* model = static_cast<LibClass173990*>(target)->source;
            value.w = model->color_modulation.w;
            func_00479090(&model->color_modulation, &value);
            model->update_combined_color_factor();
            break;
        }

        {
            LibColorModel* model = static_cast<LibColorModel*>(target);
            value.w = model->color_modulation.w;
            func_00479090(&model->color_modulation, &value);
            model->update_combined_color_factor();
        }

        break;
    }
    case 39:
    {
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        if (static_cast<LibTransform*>(target)->type_id == 0x500)
        {
            LibColorModel* model = static_cast<LibClass173990*>(target)->source;
            value.w = model->color_modulation.w;
            func_00479090(&model->color_modulation, &value);
            model->update_combined_color_factor();
            break;
        }

        {
            LibColorModel* model = static_cast<LibColorModel*>(target);
            value.w = model->color_modulation.w;
            func_00479090(&model->color_modulation, &value);
            model->update_combined_color_factor();
        }

        break;
    }
    case 40:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        FieldVec4A color;

        if (static_cast<LibTransform*>(target)->type_id == 0x500)
        {
            LibColorModel* model = static_cast<LibClass173990*>(target)->source;
            color = *static_cast<const FieldVec4A*>(func_004BD3D0(model));
            (&color.x)[entry->flags & 0xF] = value;
            func_00479090(&model->color_modulation, &color);
            model->update_combined_color_factor();
            break;
        }

        {
            LibColorModel* model = static_cast<LibColorModel*>(target);
            color = *static_cast<const FieldVec4A*>(func_004BD3D0(model));
            (&color.x)[entry->flags & 0xF] = value;
            func_00479090(&model->color_modulation, &color);
            model->update_combined_color_factor();
        }

        break;
    }
    case 41:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        FieldVec4A color;

        if (static_cast<LibTransform*>(target)->type_id == 0x500)
        {
            LibColorModel* model = static_cast<LibClass173990*>(target)->source;
            color = *static_cast<const FieldVec4A*>(func_004BD3D0(model));
            (&color.x)[entry->flags & 0xF] = value;
            func_00479090(&model->color_modulation, &color);
            model->update_combined_color_factor();
            break;
        }

        {
            LibColorModel* model = static_cast<LibColorModel*>(target);
            color = *static_cast<const FieldVec4A*>(func_004BD3D0(model));
            (&color.x)[entry->flags & 0xF] = value;
            func_00479090(&model->color_modulation, &color);
            model->update_combined_color_factor();
        }

        break;
    }
    case 42:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        FieldVec4A color;

        if (static_cast<LibTransform*>(target)->type_id == 0x500)
        {
            LibColorModel* model = static_cast<LibClass173990*>(target)->source;
            color = *static_cast<const FieldVec4A*>(func_004BD3D0(model));
            color.w = value;
            func_00479090(&model->color_modulation, &color);
            model->update_combined_color_factor();
            break;
        }

        {
            LibColorModel* model = static_cast<LibColorModel*>(target);
            color = *static_cast<const FieldVec4A*>(func_004BD3D0(model));
            color.w = value;
            func_00479090(&model->color_modulation, &color);
            model->update_combined_color_factor();
        }

        break;
    }
    case 43:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        FieldVec4A color;

        if (static_cast<LibTransform*>(target)->type_id == 0x500)
        {
            LibColorModel* model = static_cast<LibClass173990*>(target)->source;
            color = *static_cast<const FieldVec4A*>(func_004BD3D0(model));
            color.w = value;
            func_00479090(&model->color_modulation, &color);
            model->update_combined_color_factor();
            break;
        }

        {
            LibColorModel* model = static_cast<LibColorModel*>(target);
            color = *static_cast<const FieldVec4A*>(func_004BD3D0(model));
            color.w = value;
            func_00479090(&model->color_modulation, &color);
            model->update_combined_color_factor();
        }

        break;
    }
    case 44:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        FieldVec4A color;

        if (static_cast<LibTransform*>(target)->type_id == 0x500)
        {
            LibColorModel* model = static_cast<LibClass173990*>(target)->source;
            color = *static_cast<const FieldVec4A*>(func_004BD3D0(model));
            color.w = value;
            func_00479090(&model->color_modulation, &color);
            model->update_combined_color_factor();
            break;
        }

        {
            LibColorModel* model = static_cast<LibColorModel*>(target);
            color = *static_cast<const FieldVec4A*>(func_004BD3D0(model));
            color.w = value;
            func_00479090(&model->color_modulation, &color);
            model->update_combined_color_factor();
        }

        break;
    }
    case 79:
    {
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        lib_light_list_set_ambient(g_light_list, value.x, value.y, value.z);
        break;
    }
    case 80:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        lib_light_list_set_ambient_channel(g_light_list, entry->flags & 0xF, value);
        break;
    }
    case 81:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        lib_light_list_set_ambient_channel(g_light_list, entry->flags & 0xF, value);
        break;
    }
    case 82:
    {
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        LibCamera* camera = static_cast<LibCamera*>(g_display_manager->current_display);

        if (camera)
        {
            lib_camera_set_fog_color(camera, value.x, value.y, value.z);
        }

        break;
    }
    case 83:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        LibCamera* camera = static_cast<LibCamera*>(g_display_manager->current_display);

        if (!camera)
        {
            break;
        }

        u32 axis = entry->flags & 0xF;

        if (value < 0.0f)
        {
            value = 0.0f;
        }

        if (!(value <= 1.0f))
        {
            value = 1.0f;
        }

        value *= 255.0f;

        switch (axis)
        {
        case 0:
            camera->fog_color = (camera->fog_color & 0xFFFF00) | (s32)value;
            break;
        case 1:
            camera->fog_color = (camera->fog_color & 0xFF00FF) | ((s32)value << 8);
            break;
        case 2:
            camera->fog_color = (camera->fog_color & 0xFFFF) | ((s32)value << 16);
            break;
        }

        break;
    }
    case 84:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        LibCamera* camera = static_cast<LibCamera*>(g_display_manager->current_display);

        if (!camera)
        {
            break;
        }

        u32 axis = entry->flags & 0xF;

        if (value < 0.0f)
        {
            value = 0.0f;
        }

        if (!(value <= 1.0f))
        {
            value = 1.0f;
        }

        value *= 255.0f;

        switch (axis)
        {
        case 0:
            camera->fog_color = (camera->fog_color & 0xFFFF00) | (s32)value;
            break;
        case 1:
            camera->fog_color = (camera->fog_color & 0xFF00FF) | ((s32)value << 8);
            break;
        case 2:
            camera->fog_color = (camera->fog_color & 0xFFFF) | ((s32)value << 16);
            break;
        }

        break;
    }
    case 85:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        LibCamera* camera = static_cast<LibCamera*>(g_display_manager->current_display);

        if (camera)
        {
            camera->set_far_fog_fraction(value);
        }

        break;
    }
    case 86:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        LibCamera* camera = static_cast<LibCamera*>(g_display_manager->current_display);

        if (camera)
        {
            camera->set_far_fog_fraction(value);
        }

        break;
    }
    case 87:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        LibCamera* camera = static_cast<LibCamera*>(g_display_manager->current_display);

        if (camera)
        {
            camera->set_near_fog_fraction(value);
        }

        break;
    }
    case 88:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        LibCamera* camera = static_cast<LibCamera*>(g_display_manager->current_display);

        if (camera)
        {
            camera->set_near_fog_fraction(value);
        }

        break;
    }
    case 45:
    {
        LibLight* light = static_cast<LibLight*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        light->direction.w = value;
        break;
    }
    case 46:
    {
        LibLight* light = static_cast<LibLight*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        light->direction.w = value;
        break;
    }
    case 47:
    {
        LibLight* light = static_cast<LibLight*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        light->direction.w = value;
        break;
    }
    case 48:
    {
        LibLight* light = static_cast<LibLight*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        light->color.w = value;
        break;
    }
    case 49:
    {
        LibLight* light = static_cast<LibLight*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        light->color.w = value;
        break;
    }
    case 50:
    {
        LibLight* light = static_cast<LibLight*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        light->color.w = value;
        break;
    }
    case 51:
    {
        LibLight* light = static_cast<LibLight*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        lib_set_float3(&light->color.x, value.x, value.y, value.z);
        break;
    }
    case 52:
    {
        LibLight* light = static_cast<LibLight*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        lib_set_float3(&light->color.x, value.x, value.y, value.z);
        break;
    }
    case 53:
    {
        LibLight* light = static_cast<LibLight*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        lib_set_float3(&light->color.x, value.x, value.y, value.z);
        break;
    }
    case 54:
    {
        LibLight* light = static_cast<LibLight*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_004BD3C0(&light->color.x, entry->flags & 0xF, value);
        break;
    }
    case 55:
    {
        LibLight* light = static_cast<LibLight*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_004BD3C0(&light->color.x, entry->flags & 0xF, value);
        break;
    }
    case 56:
    {
        LibLight* light = static_cast<LibLight*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        light->cone_angle = value;
        func_004C9BA0(light);
        break;
    }
    case 57:
    {
        LibLight* light = static_cast<LibLight*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        light->cone_angle = value;
        func_004C9BA0(light);
        break;
    }
    case 58:
    {
        LibLight* light = static_cast<LibLight*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        light->cone_angle = value;
        func_004C9BA0(light);
        break;
    }
    case 59:
    {
        LibLight* light = static_cast<LibLight*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        light->unk278 = value;
        func_004C9BA0(light);
        break;
    }
    case 60:
    {
        LibLight* light = static_cast<LibLight*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        light->unk278 = value;
        func_004C9BA0(light);
        break;
    }
    case 61:
    {
        LibLight* light = static_cast<LibLight*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        light->unk278 = value;
        func_004C9BA0(light);
        break;
    }
    case 62:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        LibMorphTarget* morph = static_cast<LibMorphTarget*>(entry->sub_target);

        if (morph)
        {
            lib_morph_target_set_weight(morph, value);
        }

        break;
    }
    case 63:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        LibMorphTarget* morph = static_cast<LibMorphTarget*>(entry->sub_target);

        if (morph)
        {
            lib_morph_target_set_weight(morph, value);
        }

        break;
    }
    case 64:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        LibMorphTarget* morph = static_cast<LibMorphTarget*>(entry->sub_target);

        if (morph)
        {
            lib_morph_target_set_weight(morph, value);
        }

        break;
    }
    case 65:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        LibBlendChannelWeights* sub = static_cast<LibBlendChannelWeights*>(entry->sub_target);

        if (!sub)
        {
            break;
        }

        func_004BD3C0(&sub->weights.x, entry->flags & 0xF, value);

        if (sub->weights.x != 0.0f || sub->weights.y != 0.0f)
        {
            if (!sub->state)
            {
                func_004BD380(reinterpret_cast<LibClass1779F0*>(sub), 1);
                sub->state = 0;
            }
        }
        else if (sub->unk18)
        {
            sub->state = 2;
        }

        break;
    }
    case 66:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        LibBlendChannelWeights* sub = static_cast<LibBlendChannelWeights*>(entry->sub_target);

        if (!sub)
        {
            break;
        }

        func_004BD3C0(&sub->weights.x, entry->flags & 0xF, value);

        if (sub->weights.x != 0.0f || sub->weights.y != 0.0f)
        {
            if (!sub->state)
            {
                func_004BD380(reinterpret_cast<LibClass1779F0*>(sub), 1);
                sub->state = 0;
            }
        }
        else if (sub->unk18)
        {
            sub->state = 2;
        }

        break;
    }
    case 67:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        LibBlendChannelWeights* sub = static_cast<LibBlendChannelWeights*>(entry->sub_target);

        if (!sub)
        {
            break;
        }

        func_004BD3C0(&sub->weights.x, entry->flags & 0xF, value);

        if (sub->weights.x != 0.0f || sub->weights.y != 0.0f)
        {
            if (!sub->state)
            {
                func_004BD380(reinterpret_cast<LibClass1779F0*>(sub), 1);
                sub->state = 0;
            }
        }
        else if (sub->unk18)
        {
            sub->state = 2;
        }

        break;
    }
    case 68:
    {
        if (!entry->sub_target)
        {
            break;
        }

        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        value.w = static_cast<LibBlendChannelWeights*>(entry->sub_target)->weights.w;
        LibBlendChannelWeights* sub = static_cast<LibBlendChannelWeights*>(entry->sub_target);
        func_004790D0(reinterpret_cast<LibQuadword*>(&sub->weights), reinterpret_cast<const LibQuadword*>(&value));

        if (sub->weights.x != 1.0f || sub->weights.y != 1.0f || sub->weights.z != 1.0f ||
            sub->weights.w != 1.0f)
        {
            func_004BD380(reinterpret_cast<LibClass1779F0*>(sub), 1);
            sub->state = 0;
        }
        else
        {
            sub->state = 2;
        }

        break;
    }
    case 69:
    {
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        if (!entry->sub_target)
        {
            break;
        }

        value.w = static_cast<LibBlendChannelWeights*>(entry->sub_target)->weights.w;
        LibBlendChannelWeights* sub = static_cast<LibBlendChannelWeights*>(entry->sub_target);
        func_004790D0(reinterpret_cast<LibQuadword*>(&sub->weights), reinterpret_cast<const LibQuadword*>(&value));

        if (sub->weights.x != 1.0f || sub->weights.y != 1.0f || sub->weights.z != 1.0f ||
            sub->weights.w != 1.0f)
        {
            func_004BD380(reinterpret_cast<LibClass1779F0*>(sub), 1);
            sub->state = 0;
        }
        else
        {
            sub->state = 2;
        }

        break;
    }
    case 70:
    {
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        if (!entry->sub_target)
        {
            break;
        }

        value.w = static_cast<LibBlendChannelWeights*>(entry->sub_target)->weights.w;
        LibBlendChannelWeights* sub = static_cast<LibBlendChannelWeights*>(entry->sub_target);
        func_004790D0(reinterpret_cast<LibQuadword*>(&sub->weights), reinterpret_cast<const LibQuadword*>(&value));

        if (sub->weights.x != 1.0f || sub->weights.y != 1.0f || sub->weights.z != 1.0f ||
            sub->weights.w != 1.0f)
        {
            func_004BD380(reinterpret_cast<LibClass1779F0*>(sub), 1);
            sub->state = 0;
        }
        else
        {
            sub->state = 2;
        }

        break;
    }
    case 71:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        if (!entry->sub_target)
        {
            break;
        }

        FieldVec4A weights = static_cast<LibBlendChannelWeights*>(entry->sub_target)->weights;
        (&weights.x)[entry->flags & 0xF] = value;
        LibBlendChannelWeights* sub = static_cast<LibBlendChannelWeights*>(entry->sub_target);
        func_004790D0(reinterpret_cast<LibQuadword*>(&sub->weights), reinterpret_cast<const LibQuadword*>(&weights));

        if (sub->weights.x != 1.0f || sub->weights.y != 1.0f || sub->weights.z != 1.0f ||
            sub->weights.w != 1.0f)
        {
            func_004BD380(reinterpret_cast<LibClass1779F0*>(sub), 1);
            sub->state = 0;
        }
        else
        {
            sub->state = 2;
        }

        break;
    }
    case 72:
    {
        if (!entry->sub_target)
        {
            break;
        }

        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        FieldVec4A weights = static_cast<LibBlendChannelWeights*>(entry->sub_target)->weights;
        (&weights.x)[entry->flags & 0xF] = value;
        LibBlendChannelWeights* sub = static_cast<LibBlendChannelWeights*>(entry->sub_target);
        func_004790D0(reinterpret_cast<LibQuadword*>(&sub->weights), reinterpret_cast<const LibQuadword*>(&weights));

        if (sub->weights.x != 1.0f || sub->weights.y != 1.0f || sub->weights.z != 1.0f ||
            sub->weights.w != 1.0f)
        {
            func_004BD380(reinterpret_cast<LibClass1779F0*>(sub), 1);
            sub->state = 0;
        }
        else
        {
            sub->state = 2;
        }

        break;
    }
    case 73:
    {
        if (!entry->sub_target)
        {
            break;
        }

        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        FieldVec4A weights = static_cast<LibBlendChannelWeights*>(entry->sub_target)->weights;
        weights.w = value;
        LibBlendChannelWeights* sub = static_cast<LibBlendChannelWeights*>(entry->sub_target);
        func_004790D0(reinterpret_cast<LibQuadword*>(&sub->weights), reinterpret_cast<const LibQuadword*>(&weights));

        if (sub->weights.x != 1.0f || sub->weights.y != 1.0f || sub->weights.z != 1.0f ||
            sub->weights.w != 1.0f)
        {
            func_004BD380(reinterpret_cast<LibClass1779F0*>(sub), 1);
            sub->state = 0;
        }
        else
        {
            sub->state = 2;
        }

        break;
    }
    case 74:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        if (!entry->sub_target)
        {
            break;
        }

        FieldVec4A weights = static_cast<LibBlendChannelWeights*>(entry->sub_target)->weights;
        weights.w = value;
        LibBlendChannelWeights* sub = static_cast<LibBlendChannelWeights*>(entry->sub_target);
        func_004790D0(reinterpret_cast<LibQuadword*>(&sub->weights), reinterpret_cast<const LibQuadword*>(&weights));

        if (sub->weights.x != 1.0f || sub->weights.y != 1.0f || sub->weights.z != 1.0f ||
            sub->weights.w != 1.0f)
        {
            func_004BD380(reinterpret_cast<LibClass1779F0*>(sub), 1);
            sub->state = 0;
        }
        else
        {
            sub->state = 2;
        }

        break;
    }
    case 75:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        if (!entry->sub_target)
        {
            break;
        }

        FieldVec4A weights = static_cast<LibBlendChannelWeights*>(entry->sub_target)->weights;
        weights.w = value;
        LibBlendChannelWeights* sub = static_cast<LibBlendChannelWeights*>(entry->sub_target);
        func_004790D0(reinterpret_cast<LibQuadword*>(&sub->weights), reinterpret_cast<const LibQuadword*>(&weights));

        if (sub->weights.x != 1.0f || sub->weights.y != 1.0f || sub->weights.z != 1.0f ||
            sub->weights.w != 1.0f)
        {
            func_004BD380(reinterpret_cast<LibClass1779F0*>(sub), 1);
            sub->state = 0;
        }
        else
        {
            sub->state = 2;
        }

        break;
    }
    case 76:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        LibBlendSubTarget* sub = static_cast<LibBlendSubTarget*>(entry->sub_target);

        if (sub)
        {
            sub->unk5c = 0.01f * value;
        }

        break;
    }
    case 77:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        LibBlendSubTarget* sub = static_cast<LibBlendSubTarget*>(entry->sub_target);

        if (sub)
        {
            sub->unk5c = 0.01f * value;
        }

        break;
    }
    case 78:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        LibBlendSubTarget* sub = static_cast<LibBlendSubTarget*>(entry->sub_target);

        if (sub)
        {
            sub->unk5c = 0.01f * value;
        }

        break;
    }
    case 89:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        LibGridBase* reference = static_cast<LibClass173990*>(target)->source->reference;

        if (reference)
        {
            reference->func_slotb8(value);
        }

        break;
    }
    case 90:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        LibGridBase* reference = static_cast<LibClass173990*>(target)->source->reference;

        if (reference)
        {
            reference->func_slotb8(value);
        }

        break;
    }
    case 91:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3e0.w = value;
        break;
    }
    case 92:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3e0.w = value;
        break;
    }
    case 93:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3f0.x = value;
        break;
    }
    case 94:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3f0.x = value;
        break;
    }
    case 95:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk220, &value);
        break;
    }
    case 96:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk220, &value);
        break;
    }
    case 97:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3f0.z = value;
        break;
    }
    case 98:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3f0.z = value;
        break;
    }
    case 99:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk2c0.x = value;
        break;
    }
    case 100:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk2c0.x = value;
        break;
    }
    case 101:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk2c0.y = value;
        break;
    }
    case 102:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk2c0.y = value;
        break;
    }
    case 103:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk2d0.x = value;
        break;
    }
    case 104:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk2d0.x = value;
        break;
    }
    case 105:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk2d0.y = value;
        break;
    }
    case 106:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk2d0.y = value;
        break;
    }
    case 107:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk2e0, &value);
        break;
    }
    case 108:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk2e0, &value);
        break;
    }
    case 109:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk2f0, &value);
        break;
    }
    case 110:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk2f0, &value);
        break;
    }
    case 111:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        if (bound->unk481 == 7)
        {
            bound->unk230.y = value.y;
            break;
        }

        func_00479090(&bound->unk230, &value);
        break;
    }
    case 112:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        if (bound->unk481 == 7)
        {
            bound->unk230.y = value.y;
            break;
        }

        func_00479090(&bound->unk230, &value);
        break;
    }
    case 113:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        if (bound->unk481 == 7)
        {
            bound->unk240.y = value.y;
            break;
        }

        func_00479090(&bound->unk240, &value);
        break;
    }
    case 114:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        if (bound->unk481 == 7)
        {
            bound->unk240.y = value.y;
            break;
        }

        func_00479090(&bound->unk240, &value);
        break;
    }
    case 115:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk230.x = value;
        break;
    }
    case 116:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk230.x = value;
        break;
    }
    case 117:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk240.x = value;
        break;
    }
    case 118:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk240.x = value;
        break;
    }
    case 119:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk230.z = value;
        break;
    }
    case 120:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk230.z = value;
        break;
    }
    case 121:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk300.x = value;
        break;
    }
    case 122:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk300.x = value;
        break;
    }
    case 123:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk300.y = value;
        break;
    }
    case 124:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk300.y = value;
        break;
    }
    case 125:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk310.x = value;
        break;
    }
    case 126:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk310.x = value;
        break;
    }
    case 127:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk310.y = value;
        break;
    }
    case 128:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk310.y = value;
        break;
    }
    case 129:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk320, &value);
        break;
    }
    case 130:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk320, &value);
        break;
    }
    case 131:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk330, &value);
        break;
    }
    case 132:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk330, &value);
        break;
    }
    case 133:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3f0.w = value;
        break;
    }
    case 134:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3f0.w = value;
        break;
    }
    case 135:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk250, &value);
        break;
    }
    case 136:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk250, &value);
        break;
    }
    case 137:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk260, &value);
        break;
    }
    case 138:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk260, &value);
        break;
    }
    case 139:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk250.x = value;
        bound->unk250.y = value;
        bound->unk250.z = value;
        break;
    }
    case 140:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk250.x = value;
        bound->unk250.y = value;
        bound->unk250.z = value;
        break;
    }
    case 141:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk340.x = value;
        break;
    }
    case 142:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk340.x = value;
        break;
    }
    case 143:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk340.y = value;
        break;
    }
    case 144:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk340.y = value;
        break;
    }
    case 145:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk350.x = value;
        break;
    }
    case 146:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk350.x = value;
        break;
    }
    case 147:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk350.y = value;
        break;
    }
    case 148:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk350.y = value;
        break;
    }
    case 149:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk360, &value);
        break;
    }
    case 150:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk360, &value);
        break;
    }
    case 151:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk370, &value);
        break;
    }
    case 152:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk370, &value);
        break;
    }
    case 153:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        value.w = bound->unk270.w;
        func_00479090(&bound->unk270, &value);
        break;
    }
    case 154:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        value.w = bound->unk270.w;
        func_00479090(&bound->unk270, &value);
        break;
    }
    case 155:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk270.w = value;
        break;
    }
    case 156:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk270.w = value;
        break;
    }
    case 157:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        value.w = bound->unk270.w;
        func_00479090(&bound->unk280, &value);
        break;
    }
    case 158:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        value.w = bound->unk270.w;
        func_00479090(&bound->unk280, &value);
        break;
    }
    case 159:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk280.w = value;
        break;
    }
    case 160:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk280.w = value;
        break;
    }
    case 161:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3c0.x = value;
        break;
    }
    case 162:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3c0.x = value;
        break;
    }
    case 163:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3c0.y = value;
        break;
    }
    case 164:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3c0.y = value;
        break;
    }
    case 165:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3c0.z = value;
        break;
    }
    case 166:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3c0.z = value;
        break;
    }
    case 167:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3c0.w = value;
        break;
    }
    case 168:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3c0.w = value;
        break;
    }
    case 169:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk380.x = value;
        bound->unk380.y = value;
        break;
    }
    case 170:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk380.x = value;
        bound->unk380.y = value;
        break;
    }
    case 171:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk390.x = value;
        bound->unk390.y = value;
        break;
    }
    case 172:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk390.x = value;
        bound->unk390.y = value;
        break;
    }
    case 173:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3a0.x = value;
        bound->unk3a0.y = value;
        break;
    }
    case 174:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3a0.x = value;
        bound->unk3a0.y = value;
        break;
    }
    case 175:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3b0.x = value;
        bound->unk3b0.y = value;
        break;
    }
    case 176:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3b0.x = value;
        bound->unk3b0.y = value;
        break;
    }
    case 177:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        value.w = bound->unk290.w;
        func_00479090(&bound->unk290, &value);
        break;
    }
    case 178:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        value.w = bound->unk290.w;
        func_00479090(&bound->unk290, &value);
        break;
    }
    case 179:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk290.w = value;
        break;
    }
    case 180:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk290.w = value;
        break;
    }
    case 181:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        value.w = bound->unk2a0.w;
        func_00479090(&bound->unk2a0, &value);
        break;
    }
    case 182:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        value.w = bound->unk2a0.w;
        func_00479090(&bound->unk2a0, &value);
        break;
    }
    case 183:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk2a0.w = value;
        break;
    }
    case 184:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk2a0.w = value;
        break;
    }
    case 185:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        value.w = bound->unk2b0.w;
        func_00479090(&bound->unk2b0, &value);
        break;
    }
    case 186:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        value.w = bound->unk2b0.w;
        func_00479090(&bound->unk2b0, &value);
        break;
    }
    case 187:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk2b0.w = value;
        break;
    }
    case 188:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk2b0.w = value;
        break;
    }
    case 189:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        FieldVec4A value;
        value.x = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        value.z = bound->unk230.z;
        func_00479090(&bound->unk230, &value);
        break;
    }
    case 190:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        FieldVec4A value;
        value.x = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        value.z = bound->unk230.z;
        func_00479090(&bound->unk230, &value);
        break;
    }
    case 191:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        FieldVec4A value;
        value.z = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        value.x = bound->unk230.z;
        func_00479090(&bound->unk230, &value);
        break;
    }
    case 192:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        FieldVec4A value;
        value.z = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        value.x = bound->unk230.z;
        func_00479090(&bound->unk230, &value);
        break;
    }
    case 193:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk214 = value;
        break;
    }
    case 194:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk214 = value;
        break;
    }
    case 195:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk210 = value;
        break;
    }
    case 196:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk210 = value;
        break;
    }
    case 197:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk220.y = value;
        break;
    }
    case 198:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk220.y = value;
        break;
    }
    case 199:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk230.x = value;
        break;
    }
    case 200:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk230.x = value;
        break;
    }
    case 201:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk230.y = value;
        break;
    }
    case 202:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk230.y = value;
        break;
    }
    case 203:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk230.x = 6.6725903e-07f * value;
        break;
    }
    case 204:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk230.x = 6.6725903e-07f * value;
        break;
    }
    case 205:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk220, &value);
        break;
    }
    case 206:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk220, &value);
        break;
    }
    case 207:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk220, &value);
        break;
    }
    case 208:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk220, &value);
        break;
    }
    case 209:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk240, &value);
        break;
    }
    case 210:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk240, &value);
        break;
    }
    case 211:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk230, &value);
        break;
    }
    case 212:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk230, &value);
        break;
    }
    case 213:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk260, &value);
        break;
    }
    case 214:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk260, &value);
        break;
    }
    case 215:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk2a0.x = value;
        break;
    }
    case 216:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk2a0.x = value;
        break;
    }
    case 217:
    {
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        static_cast<LibGridBase*>(target)->func_slota0(&value);
        break;
    }
    case 218:
    {
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        static_cast<LibGridBase*>(target)->func_slota0(&value);
        break;
    }
    case 219:
    {
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        static_cast<LibGridBase*>(target)->func_slota4(&value);
        break;
    }
    case 220:
    {
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        static_cast<LibGridBase*>(target)->func_slota4(&value);
        break;
    }
    case 221:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk280.y = value;
        break;
    }
    case 222:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk280.y = value;
        break;
    }
    case 223:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk280.z = value;
        bound->unk240.z = value;
        break;
    }
    case 224:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk280.z = value;
        bound->unk240.z = value;
        break;
    }
    case 225:
    {
        LibBlendColorTarget* bound = static_cast<LibBlendColorTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk28c = (bound->unk28c & 0xFF000000) |
            ((s32)(128.0f * value.x) | ((s32)(128.0f * value.y) << 8) | ((s32)(128.0f * value.z) << 16));
        break;
    }
    case 226:
    {
        LibBlendColorTarget* bound = static_cast<LibBlendColorTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk28c = (bound->unk28c & 0xFF000000) |
            ((s32)(128.0f * value.x) | ((s32)(128.0f * value.y) << 8) | ((s32)(128.0f * value.z) << 16));
        break;
    }
    case 227:
    {
        LibBlendColorTarget* bound = static_cast<LibBlendColorTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        s32 alpha = (s32)(128.0f * value) << 24;
        bound->unk28c = (bound->unk28c & 0xFFFFFF) | alpha;
        break;
    }
    case 228:
    {
        LibBlendColorTarget* bound = static_cast<LibBlendColorTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        s32 alpha = (s32)(128.0f * value) << 24;
        bound->unk28c = (bound->unk28c & 0xFFFFFF) | alpha;
        break;
    }
    case 229:
    {
        LibBlendColorTarget* bound = static_cast<LibBlendColorTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk290 = (bound->unk290 & 0xFF000000) |
            ((s32)(128.0f * value.x) | ((s32)(128.0f * value.y) << 8) | ((s32)(128.0f * value.z) << 16));
        break;
    }
    case 230:
    {
        LibBlendColorTarget* bound = static_cast<LibBlendColorTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk290 = (bound->unk290 & 0xFF000000) |
            ((s32)(128.0f * value.x) | ((s32)(128.0f * value.y) << 8) | ((s32)(128.0f * value.z) << 16));
        break;
    }
    case 231:
    {
        LibBlendColorTarget* bound = static_cast<LibBlendColorTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        s32 alpha = (s32)(128.0f * value) << 24;
        bound->unk290 = (bound->unk290 & 0xFFFFFF) | alpha;
        break;
    }
    case 232:
    {
        LibBlendColorTarget* bound = static_cast<LibBlendColorTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        s32 alpha = (s32)(128.0f * value) << 24;
        bound->unk290 = (bound->unk290 & 0xFFFFFF) | alpha;
        break;
    }
    case 233:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk260.x = value.x;
        bound->unk260.y = value.y;
        bound->unk260.z = 3.1415927f * (2.0f * value.z);
        break;
    }
    case 234:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk260.x = value.x;
        bound->unk260.y = value.y;
        bound->unk260.z = 3.1415927f * (2.0f * value.z);
        break;
    }
    case 235:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk270.x = value.x;
        bound->unk270.y = value.y;
        bound->unk270.z = 3.1415927f * (2.0f * value.z);
        break;
    }
    case 236:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk270.x = value.x;
        bound->unk270.y = value.y;
        bound->unk270.z = 3.1415927f * (2.0f * value.z);
        break;
    }
    case 237:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk280.z = -value;
        float width = 2.0f * value;
        bound->unk290.x = width;
        float height = bound->unk290.y;
        bound->unk240.z = 1.1f * ee_sqrt_in_place(width * width + height * height);
        break;
    }
    case 238:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk280.z = -value;
        bound->unk290.x = 2.0f * value;
        bound->unk240.z = 1.1f * ee_sqrt_in_place(bound->unk290.x * bound->unk290.x + bound->unk290.y * bound->unk290.y);
        break;
    }
    case 239:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk280.w = -value;
        bound->unk290.y = 2.0f * value;
        bound->unk240.z = 1.1f * ee_sqrt_in_place(bound->unk290.x * bound->unk290.x + bound->unk290.y * bound->unk290.y);
        break;
    }
    case 240:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk280.w = -value;
        bound->unk290.y = 2.0f * value;
        bound->unk240.z = 1.1f * ee_sqrt_in_place(bound->unk290.x * bound->unk290.x + bound->unk290.y * bound->unk290.y);
        break;
    }
    case 241:
    {
        LibBlendColorTarget* bound = static_cast<LibBlendColorTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk298 = (bound->unk298 & 0xFF000000) |
            ((s32)(128.0f * value.x) | ((s32)(128.0f * value.y) << 8) | ((s32)(128.0f * value.z) << 16));
        break;
    }
    case 242:
    {
        LibBlendColorTarget* bound = static_cast<LibBlendColorTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk298 = (bound->unk298 & 0xFF000000) |
            ((s32)(128.0f * value.x) | ((s32)(128.0f * value.y) << 8) | ((s32)(128.0f * value.z) << 16));
        break;
    }
    case 243:
    {
        LibBlendColorTarget* bound = static_cast<LibBlendColorTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        s32 alpha = (s32)(128.0f * value) << 24;
        bound->unk298 = (bound->unk298 & 0xFFFFFF) | alpha;
        break;
    }
    case 244:
    {
        LibBlendColorTarget* bound = static_cast<LibBlendColorTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        s32 alpha = (s32)(128.0f * value) << 24;
        bound->unk298 = (bound->unk298 & 0xFFFFFF) | alpha;
        break;
    }
    case 245:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk220.x = 0.5f + value;
        lib_transform_set_dirty(target, 1);
        break;
    }
    case 246:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk220.x = 0.5f + value;
        lib_transform_set_dirty(target, 1);
        break;
    }
    case 247:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk220.y = 0.5f + value;
        lib_transform_set_dirty(target, 1);
        break;
    }
    case 248:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk220.y = 0.5f + value;
        lib_transform_set_dirty(target, 1);
        break;
    }
    case 249:
    case 250:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk7d0.x = value;
        break;
    }
    case 251:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk7d0.x = value;
        break;
    }
    case 252:
    case 253:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk7d0.y = value;
        break;
    }
    case 254:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk7d0.y = value;
        break;
    }
    case 255:
    case 256:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk7d0.z = value;
        break;
    }
    case 257:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk7d0.z = value;
        break;
    }
    case 258:
    case 259:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk7d0.w = value;
        break;
    }
    case 260:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk7d0.w = value;
        break;
    }
    case 261:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk430.w = value;
        break;
    }
    case 262:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk430.w = value;
        break;
    }
    case 263:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk440.x = value;
        break;
    }
    case 264:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk440.x = value;
    }
    case 265:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk494 = (s32)(0.5f + value);
        break;
    }
    case 266:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk494 = (s32)(0.5f + value);
        break;
    }
    case 267:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk495 = (s32)(0.5f + value);
        break;
    }
    case 268:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk495 = (s32)(0.5f + value);
        break;
    }
    case 269:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk496 = (s32)(0.5f + value);
        break;
    }
    case 270:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk496 = (s32)(0.5f + value);
        break;
    }
    case 271:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3d0.x = value;
        break;
    }
    case 272:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3d0.x = value;
        break;
    }
    case 273:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3d0.y = value;
        break;
    }
    case 274:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3d0.y = value;
        break;
    }
    case 275:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3d0.z = value;
        break;
    }
    case 276:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3d0.z = value;
        break;
    }
    case 277:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3d0.w = value;
        break;
    }
    case 278:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk3d0.w = value;
        break;
    }
    case 279:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->translation.x = value;
        break;
    }
    case 280:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->translation.x = value;
        break;
    }
    case 281:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk220.x = value;
        break;
    }
    case 282:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk220.x = value;
        break;
    }
    case 283:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        lib_set_entry_y(&bound->unk230, value);
        lib_transform_set_dirty(target, 1);
        break;
    }
    case 284:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        lib_set_entry_y(&bound->unk230, value);
        lib_transform_set_dirty(target, 1);
        break;
    }
    case 285:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk214 = value;
        break;
    }
    case 286:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk214 = value;
        break;
    }
    case 287:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk220.x = value;
        break;
    }
    case 288:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk220.x = value;
        break;
    }
    case 289:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk214 = value;
        break;
    }
    case 290:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk214 = value;
        break;
    }
    case 291:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk270.x = value;
        break;
    }
    case 292:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk270.x = value;
        break;
    }
    case 293:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk270.y = value;
        break;
    }
    case 294:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk270.y = value;
        break;
    }
    case 295:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk270.z = value;
        break;
    }
    case 296:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk270.z = value;
        break;
    }
    case 297:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk220.x = value;
        break;
    }
    case 298:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk220.x = value;
        break;
    }
    case 299:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk220.y = value;
        break;
    }
    case 300:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk220.y = value;
        break;
    }
    case 301:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk220.x = value;
        break;
    }
    case 302:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk220.x = value;
        break;
    }
    case 303:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk220.y = value;
        break;
    }
    case 304:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk220.y = value;
        break;
    }
    case 305:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        float y = value.y;
        value.x *= 0.5f;
        value.y = 0.5f * value.z;
        value.z = 0.5f * y;
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk220, &value);
        break;
    }
    case 306:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        float y = value.y;
        value.x *= 0.5f;
        value.y = 0.5f * value.z;
        value.z = 0.5f * y;
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->unk220, &value);
        break;
    }
    case 307:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->scale, &value);
        break;
    }
    case 308:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        func_00479090(&bound->scale, &value);
        break;
    }
    case 309:
    {
        LibVectorTrackBase* track = static_cast<LibVectorTrackBase*>(entry->channel);
        FieldVec4A value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        static_cast<LibOrientedTransform*>(target)->set_orientation(reinterpret_cast<const LibVector4*>(&value));
        break;
    }
    case 310:
    {
        LibClass1734D0* occluder = static_cast<LibClass1734D0*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        occluder->half_width = value;
        func_00431020(occluder);
        break;
    }
    case 311:
    {
        LibClass1734D0* occluder = static_cast<LibClass1734D0*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        occluder->half_width = value;
        func_00431020(occluder);
        break;
    }
    case 312:
    {
        LibClass1734D0* occluder = static_cast<LibClass1734D0*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        occluder->half_depth = value;
        func_00431020(occluder);
        break;
    }
    case 313:
    {
        LibClass1734D0* occluder = static_cast<LibClass1734D0*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        occluder->half_depth = value;
        func_00431020(occluder);
        break;
    }
    case 314:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk214 = value;
        break;
    }
    case 315:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk214 = value;
        break;
    }
    case 316:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk214 = value;
        break;
    }
    case 317:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk214 = value;
        break;
    }
    case 318:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk240.x = value;
        break;
    }
    case 319:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk240.x = value;
        break;
    }
    case 320:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk240.y = value;
        break;
    }
    case 321:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk240.y = value;
        break;
    }
    case 322:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk214 = value;
        break;
    }
    case 323:
    {
        LibBlendTarget* bound = static_cast<LibBlendTarget*>(target);
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        bound->unk214 = value;
        break;
    }
    case 324:
    case 326:
    case 328:
    case 330:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        *static_cast<float*>(target) = value;
        break;
    }
    case 325:
    case 327:
    case 329:
    case 331:
    {
        LibFloatTrackBase* track = static_cast<LibFloatTrackBase*>(entry->channel);
        float value = track->sample(frame);
        s32 cycles = track->get_cycle_count();

        if (mode != 2 && status < cycles)
        {
            object->longest_channel = track;
            status = cycles;

            if (mode)
            {
                break;
            }
        }

        *static_cast<float*>(target) = value;
        break;
    }
    }

    return status;
}

}

