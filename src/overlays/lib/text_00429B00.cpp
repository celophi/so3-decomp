#include "include_asm.h"
#include "vu0.h"
#include "overlays/lib/matrix_vu0.h"
#include "overlays/lib/vector_inlines.h"
#include "clamp.h"
#include "overlays/lib/blend_transform.h"
#include "overlays/lib/model.h"
#include "overlays/lib/scene_objects.h"
#include "main/resident_data.h"
#include "overlays/lib/text_00429B00.h"
#include "overlays/lib/text_0043A920.h"
#include "overlays/lib/tracks.h"
#include "overlays/lib/emission.h"
#include "overlays/lib/text_0049B820.h"
#include "overlays/lib/image_model.h"
#include "overlays/lib/text_0046AE20.h"
#include "overlays/lib/emission_vu0.h"
#include "overlays/lib/light_vu0.h"
#include "overlays/lib/memory_card.h"
#include "overlays/lib/image_capture.h"
#include "overlays/lib/transform_owner_inlines.h"
#include "overlays/lib/transform_inlines.h"
#include "overlays/lib/occluder_vu0.h"
#include "overlays/lib/ripple_vu0.h"
#include "overlays/lib/light_random.h"
#include "sdk/main/libkernl_00121940.h"
#include "ee.h"
#include "overlays/lib/text_004DD440.h"

#include "sdk/main/libmc_0012BB10.h"
#include "overlays/lib/text_004CD3A0.h"
#include "sdk/main/libc_guess_00137290.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "sdk/main/libc_guess_0013CD50.h"
#include "main/sound_set.h"
#include "sdk/main/libc_guess_0013C948.h"
#include "sdk/main/libc_0013C6D0.h"
#include "overlays/lib/text_0044ABE0.h"
#include "main/entry_table.h"
#include "main/system.h"
#include "main/utility.h"
#include "main/resource_queue.h"

/** @brief Leave the element uninitialized. */
inline LibClass173490Entry::LibClass173490Entry()
{
}

/** LibClass173380 that LibClass173380::build_packet creates, with vtable D_173270 in main data. */
class LibClass173270 : public LibClass173380
{
public:
    /** @brief Start with no light and no lifetime. */
    LibClass173270()
    {
        lifetime = 0;
        light_index = -1;
        set_type_id(0x121);
    }

    /** @brief Destroy the model. */
    virtual ~LibClass173270();

    /** @brief Detach from the owner and destroy as a plain transform owner, keeping the child objects. */
    virtual void destroy();

    /** @brief Queue the model's DMA as LibModel does. */
    virtual void render();

    /**
     * @brief Mark the transfer done without finishing the packet.
     * @param channel DMA channel number.
     */
    virtual void complete_dma(u32 channel);

    /**
     * @brief Choose the caster light the shadow is drawn for.
     * @param index Light number in the caster's shadow light list.
     */
    void set_light_index(s8 index)
    {
        light_index = index;
    }

    /**
     * @brief Count the lifetime down.
     * @return Whether it ran out.
     */
    bool expire()
    {
        if (--lifetime == 0)
        {
            return true;
        }

        return false;
    }

    s8 light_index;
    s32 lifetime;
};

/** Sound bank set Lib plays its sounds through. */
extern ResidentSoundBankSet* D_001B6524;

/** Per sound bank slot: the last voice line asked to hold back the next sound of some events. */
extern "C" u8 D_001B6528[RESIDENT_SOUND_BANK_SLOT_COUNT];

/** Sound number tables for func_0042EB50, four numbers each; entries 1 to 10 are used. */
extern s16* D_004ED0EC[];

/** Sound number tables for func_0042F160, two numbers each; entries 1 to 10 are used. */
extern s16* D_004ECCDC[];

/** Sound number tables for func_0042F0D0, four numbers each; entries 1 to 10 are used. */
extern s16* D_004ECD0C[];

/** Sound number tables for func_0042EBE0, two sets of six numbers; entries 1 to 10 are used. */
extern s16* D_004ED0BC[];

/** Sound number tables for func_0042EF30, three bands of ten numbers; entries 1 to 10 are used. */
extern s16* D_004ECFBC[];

/** Sound number tables for func_0042F420, four groups of three numbers; entries 1 to 10 are used. */
extern s16 (*D_004ECB3C[])[3];

/** Sound number tables for func_0042F250, three numbers for each of three levels; entries 1 to 10 are used. */
extern s16* D_004ECCAC[];

extern "C" {

typedef struct WordSetterOwnertext_00429B00
{
    u8 unk00[0x24];
    u32 unk24;
    u8 unk28[0x400];
    u32 unk428;
} WordSetterOwnertext_00429B00;


}

/**
 * @brief Read an indexed keyframe, unpacking its rotation.
 * @param index Keyframe index.
 * @param key Receives the sort key, or null.
 * @param value Receives the rotation, or null; w is rebuilt from x, y and z.
 * @param first Unused.
 * @param second Unused.
 * @return One when the index is within the capacity, otherwise zero.
 */
s32 LibPooledQuaternionTrack::read_key(s32 index, float* key, void* value, void* first, void* second) const
{
    if (index >= state.key_capacity)
    {
        return 0;
    }

    if (key)
    {
        *key = key_array[index].get_key();
    }

    if (value)
    {
        FieldVec4A* rotation = static_cast<FieldVec4A*>(value);
        rotation->x = (1.0f / 32768.0f) * key_array[index].packed_rotation[0];
        rotation->y = (1.0f / 32768.0f) * key_array[index].packed_rotation[1];
        rotation->z = (1.0f / 32768.0f) * key_array[index].packed_rotation[2];
        float y = rotation->y;
        float x = rotation->x;
        float z = rotation->z;
        y *= y;
        x *= x;
        float w_squared = 1.0f - (x + y + z * z);
        rotation->w = __sqrt(w_squared, w_squared);
    }

    return 1;
}

/**
 * @brief Shift the later keyframes up and pack a rotation at an index.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe rotation.
 * @return One when the index is a stored key and there was room, otherwise zero.
 */
s32 LibPooledQuaternionTrack::insert_rotation(s32 index, float key, const FieldVec4A* value)
{
    s32 i;

    if (index >= state.key_count)
    {
        return 0;
    }

    if (state.key_count >= state.key_capacity)
    {
        return 0;
    }

    for (i = state.key_count; i > index; i--)
    {
        key_array[i] = key_array[i - 1];
    }

    s32 x = 32768.0f * value->x;
    s32 y = 32768.0f * value->y;
    s32 z = 32768.0f * value->z;

    if (value->w < 0.0f)
    {
        x = -x;
        y = -y;
        z = -z;
    }

    x = clamp_high(x, 32767);
    y = clamp_high(y, 32767);
    z = clamp_high(z, 32767);
    x = clamp_low(x, -32768);
    y = clamp_low(y, -32768);
    z = clamp_low(z, -32768);
    key_array[index].packed_rotation[0] = x;
    key_array[index].packed_rotation[1] = y;
    key_array[index].packed_rotation[2] = z;
    key_array[index].set_key(key);

    if (index == state.key_count - 1)
    {
        state.span = key - key_array[0].get_key();
    }

    state.key_count++;
    return 1;
}

/**
 * @brief Pack a rotation into an existing keyframe.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe rotation.
 * @return True when the index is within the capacity.
 */
bool LibPooledQuaternionTrack::replace_rotation(s32 index, float key, const FieldVec4A* value)
{
    if (index >= state.key_capacity)
    {
        return false;
    }

    s32 x = 32768.0f * value->x;
    s32 y = 32768.0f * value->y;
    s32 z = 32768.0f * value->z;

    if (value->w < 0.0f)
    {
        x = -x;
        y = -y;
        z = -z;
    }

    x = clamp_high(x, 32767);
    y = clamp_high(y, 32767);
    z = clamp_high(z, 32767);
    x = clamp_low(x, -32768);
    y = clamp_low(y, -32768);
    z = clamp_low(z, -32768);
    key_array[index].packed_rotation[0] = x;
    key_array[index].packed_rotation[1] = y;
    key_array[index].packed_rotation[2] = z;
    key_array[index].set_key(key);

    if (index == state.key_count - 1)
    {
        state.span = key - key_array[0].get_key();
    }

    return true;
}

/**
 * @brief Pack a rotation and append it after the last keyframe.
 * @param value Keyframe rotation.
 * @param key Sort key.
 * @return True when there was room.
 */
bool LibPooledQuaternionTrack::append_rotation(const FieldVec4A* value, float key)
{
    if (state.key_count >= state.key_capacity)
    {
        return false;
    }

    s32 x = 32768.0f * value->x;
    s32 y = 32768.0f * value->y;
    s32 z = 32768.0f * value->z;

    if (value->w < 0.0f)
    {
        x = -x;
        y = -y;
        z = -z;
    }

    x = clamp_high(x, 32767);
    y = clamp_high(y, 32767);
    z = clamp_high(z, 32767);
    x = clamp_low(x, -32768);
    y = clamp_low(y, -32768);
    z = clamp_low(z, -32768);
    key_array[state.key_count].packed_rotation[0] = x;
    key_array[state.key_count].packed_rotation[1] = y;
    key_array[state.key_count].packed_rotation[2] = z;
    key_array[state.key_count].set_key(key);
    state.span = key - key_array[0].get_key();
    state.key_count++;
    return true;
}

/** @brief Reset the cached sampling state. */
void LibPooledQuaternionTrack::reset_state()
{
    LibQuaternionTrackBase::reset_state();
}

/** @brief Free the keys, then destroy the track. */
LibQuaternionTrackBase::~LibQuaternionTrackBase()
{
    free_keys();
}

/** @brief Reset the keys, counts, modes and cached indices. */
void LibQuaternionTrackBase::reset_state()
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
 * @brief Allocate storage for a number of keyframes, dropping any keys the track owned.
 * @param count Keyframes to hold.
 */
void LibQuaternionTrackBase::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] key_array;
    key_array = new (0) LibQuaternionTrackKey[count];
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
void LibQuaternionTrackBase::bind_keys(s32 count, void* keys)
{
    s32 last_index = count - 1;
    LibQuaternionTrackKey* last;
    state.external_keys = 1;
    key_array = static_cast<LibQuaternionTrackKey*>(keys);
    state.key_capacity = count;
    state.key_count = count;
    last = key_array + last_index;
    state.span = (float)last->key - (float)key_array[0].key;
}

/**
 * @brief Set what the track does after its last key, and whether either end extends a segment.
 * @param mode LibTrackEndMode.
 */
void LibQuaternionTrackBase::set_after_mode(u32 mode)
{
    state.after_mode = mode;
    state.extends_segment = state.before_mode == LIB_TRACK_END_EXTEND_SEGMENT || state.after_mode == LIB_TRACK_END_EXTEND_SEGMENT;
}

/**
 * @brief Return how many key spans the last wrapped key was past the first key.
 * @return Signed cycle count.
 */
s32 LibQuaternionTrackBase::get_cycle_count() const
{
    return state.cycle_count;
}

/**
 * @brief Return the number of stored keys.
 * @return Key count.
 */
s16 LibQuaternionTrackBase::get_key_count() const
{
    return state.key_count;
}

/**
 * @brief Return the number of keys the storage can hold.
 * @return Key capacity.
 */
s16 LibQuaternionTrackBase::get_key_capacity()
{
    return state.key_capacity;
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param value Keyframe value.
 * @param first First auxiliary value.
 * @param second Second auxiliary value.
 * @param key Sort key.
 * @return Zero.
 */
bool LibQuaternionTrackBase::on_append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return 0;
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @param first First auxiliary value.
 * @param second Second auxiliary value.
 * @return Zero.
 */
bool LibQuaternionTrackBase::on_replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return 0;
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @param first First auxiliary value.
 * @param second Second auxiliary value.
 * @return Zero.
 */
s32 LibQuaternionTrackBase::on_insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return 0;
}

/**
 * @brief Test whether the track has a keyframe at a key.
 * @param key Key to find.
 * @return One when a keyframe sits at the key, otherwise zero.
 */
s32 LibQuaternionTrackBase::has_key(float key) const
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
 * @brief Return a zero quaternion; the track's value when it has no keys.
 * @return Zero vector.
 */
FieldVec4A LibQuaternionTrackBase::get_zero_value() const
{
    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Return the span between the first and last keys.
 * @return Key span, or zero when fewer than two keys are stored.
 */
float LibQuaternionTrackBase::get_key_span() const
{
    s32 last_index;
    LibQuaternionTrackKey* last;

    if (state.key_count < 2)
    {
        return 0.0f;
    }

    last_index = state.key_count - 1;
    last = key_array + last_index;
    return (float)last->key - (float)key_array[0].key;
}

/**
 * @brief Read the result pointer back after the copy.
 * @param out Result pointer.
 */
static inline void reread_result(FieldVec4A*& out)
{
    // TODO: The game reads the result pointer back through its address after the copy and never uses it. Every
    // non-volatile form I tried gets optimised away, so I'm not sure yet what the original wrote here.
    FieldVec4A* volatile* slot = &out;
    (void)*slot;
}

/**
 * @brief LibQuaternionTrackBase's find_key_value (slot 0x7C): find the keyframe with a key and decode its rotation.
 * @param out Receives the rotation, or zero when the key is absent.
 * @param track Track to search.
 * @param key Key to find.
 */
void quaternion_track_find_key_value(FieldVec4A* out, LibQuaternionTrackBase* track, float key)
{
    s32 index;

    for (index = 0; index < track->state.key_count; index++)
    {
        LibQuaternionTrackKey* entry = track->key_array + index;

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
 * @param output Receives the rotation.
 */
void LibQuaternionTrackBase::evaluate(float key, void* output)
{
    *static_cast<FieldVec4B*>(output) = sample(key);
}

/**
 * @brief Wrap a key by whole spans between the first and last keys.
 * @param key Key position.
 * @return Wrapped key.
 */
float LibQuaternionTrackBase::wrap_key(float key) const
{
    s32 last_index = state.key_count - 1;
    LibQuaternionTrackKey* entries = key_array;
    LibQuaternionTrackKey* last = entries + last_index;
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
void* LibQuaternionTrackBase::get_keys()
{
    return key_array;
}

/** @brief Delete the key storage unless it is external, and clear the key pointer. */
void LibQuaternionTrackBase::free_keys()
{
    if (!state.external_keys)
    {
        delete[] key_array;
    }

    key_array = 0;
}

/**
 * @brief Mark a track's g_quaternion_track_pool slot as free.
 * @param pool Pool that owns the track.
 * @param track Track to release.
 */
void quaternion_track_pool_free(LibTrackPool<LibPooledQuaternionTrack>* pool, LibPooledQuaternionTrack* track)
{
    pool->free(track);
}

/**
 * @brief Ignore the keyframe; the root has no key storage.
 * @param value Keyframe value.
 * @param in_tangent Incoming tangent.
 * @param out_tangent Outgoing tangent.
 * @param key Sort key.
 * @return Zero.
 */
bool LibClass173180::append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    return 0;
}

/**
 * @brief Ignore the keyframe; the root has no key storage.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @param in_tangent Incoming tangent.
 * @param out_tangent Outgoing tangent.
 * @return Zero.
 */
bool LibClass173180::replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    return 0;
}

/**
 * @brief Ignore the keyframe; the root has no key storage.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @param in_tangent Incoming tangent.
 * @param out_tangent Outgoing tangent.
 * @return Zero.
 */
s32 LibClass173180::insert_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    return 0;
}

/**
 * @brief Report that the root has no keyframes to read.
 * @param index Keyframe index.
 * @param key Receives the sort key.
 * @param value Receives the value.
 * @param first Receives the first auxiliary value.
 * @param second Receives the second auxiliary value.
 * @return Zero.
 */
s32 LibClass173180::read_key(s32 index, float* key, void* value, void* first, void* second) const
{
    return 0;
}

/**
 * @brief Ignore the keyframe; the root has no key storage.
 * @param value Keyframe value.
 * @param in_tangent Incoming tangent.
 * @param out_tangent Outgoing tangent.
 * @param key Sort key.
 */
void LibClass173180::set_single_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
}

/** @brief Do nothing; the root caches no sample. */
void LibClass173180::reset_keys()
{
}

/** @brief Delete the track through its virtual destructor. */
void LibClass173180::release()
{
    delete this;
}

/**
 * @brief Append a keyframe through on_append_key.
 * @param value Keyframe value.
 * @param in_tangent First auxiliary value.
 * @param out_tangent Second auxiliary value.
 * @param key Sort key.
 * @return Nonzero when the keyframe was stored.
 */
bool LibQuaternionTrackBase::append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
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
bool LibQuaternionTrackBase::replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
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
s32 LibQuaternionTrackBase::insert_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    return on_insert_key(index, key, static_cast<const FieldVec4A*>(value), static_cast<const FieldVec4A*>(in_tangent), static_cast<const FieldVec4A*>(out_tangent));
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param value Keyframe rotation.
 * @param key Sort key.
 */
void LibQuaternionTrackBase::on_set_single_key(const FieldVec4A* value, float key)
{
}

/**
 * @brief Store a single keyframe through on_set_single_key.
 * @param value Keyframe rotation.
 * @param in_tangent Unused.
 * @param out_tangent Unused.
 * @param key Sort key.
 */
void LibQuaternionTrackBase::set_single_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    on_set_single_key(static_cast<const FieldVec4A*>(value), key);
}

extern "C" {

}

/** @brief Destroy the model. */
LibClass173270::~LibClass173270()
{
}

/** @brief Detach from the owner and destroy as a plain transform owner, keeping the child objects. */
void LibClass173270::destroy()
{
    owner = 0;
    LibTransformOwner::destroy();
}

/**
 * @brief Give no centre for the oriented-box visibility test.
 * @param output Unused.
 * @return Zero.
 */
s32 LibClass173380::get_box_cull_center(void* output)
{
    return 0;
}

/**
 * @brief Slot 0x44 of the second vtable; its purpose is unknown.
 * @return 128.
 */
s32 LibClass173380::func_slot44()
{
    return 128;
}

extern "C" {

/**
 * @brief Recompute the RGBA factor from the stored base and modulation factors.
 * @param object Rendering state whose combined factor is updated.
 */
void lib_update_color_factor(LibTextBufferState* object)
{
    vu0_multiply_xyzw(&object->combined_color_factor, &object->base_color_factor, &object->color_modulation);
}

}

/**
 * @brief Apply the source blend mode and copy its inherited transform state.
 * @param source Blend transform to copy.
 */
void LibBlendTransform::copy_blend_state(const LibBlendTransform* source)
{
    set_blend_mode(source->blend_mode);
    LibTransform::copy_offset_transform_state(source);
}

/**
 * @brief Store the blend mode.
 * @param mode Blend mode to store.
 */
void LibBlendTransform::set_blend_mode(u8 mode)
{
    blend_mode = mode;
}

/**
 * @brief Mark the transfer done without finishing the packet.
 * @param channel DMA channel number.
 */
void LibClass173270::complete_dma(u32 channel)
{
    dma_pending = 0;
    unk62 = 1;
}

/** @brief Queue the model's DMA as LibModel does. */
void LibClass173270::render()
{
    LibModel::render();
}

extern "C" {

/**
 * @brief Store unk820.
 * @param model Model to update.
 * @param value 16-byte aligned value to store.
 */
void func_0042ABE0(LibClass173380* model, const LibVector4* value)
{
    copy_vector(&model->unk820, value);
}

}

/**
 * @brief Return LibModel's bounding sphere with the radius scaled by unk848.
 * @return Bounding sphere (centre in xyz, radius in w).
 */
const LibVector4* LibClass173380::get_bounding_sphere()
{
    LibVector4 sphere;
    copy_vector(&sphere, LibModel::get_bounding_sphere());
    sphere.w *= unk848;
    copy_vector(&bounding_sphere, &sphere);
    return &bounding_sphere;
}

/** @brief Finish the packet, or mark the transfer done when unk838 is set. */
void LibClass173380::func_slot4C()
{
    if (!unk838)
    {
        lib_finish_packet(this);
    }
    else
    {
        dma_pending = 0;
        unk62 = 1;
    }
}

/**
 * @brief Build this model from another one of the same kind and copy its settings.
 * @param links Display list the model draws through, or null.
 * @param source Model to copy.
 * @return Nonzero on success.
 */
s32 LibClass173380::build_from(LibUpdateList* links, LibClass173380* source)
{
    if (!LibModel::build_from(links, source))
    {
        return 0;
    }

    LibModel* shared = source->unk830;
    unk830 = shared;
    shared->unk790++;
    unk836 = source->unk836;
    unk837 = source->unk837;
    unk835 = source->unk835;
    unk834 = source->unk834;
    unk848 = source->unk848;
    copy_vector(&unk820, &source->unk820);
    unk854 = source->unk854;
    unk858 = source->unk858;
    unk838 = source->unk838;
    unk83a = source->unk83a;
    unk839 = source->unk839;
    unk83c = source->unk83c;
    unk84c = source->unk84c;
    unk850 = source->unk850;
    unk844 = source->unk844;
    unk85c = source->unk85c;
    unk83e = source->unk83e;
    built_from_source = 1;
    return 1;
}

// TODO: The game enters this list loop with a jump to its test instead of a guard, which I've only got with loop
// rotation off, so I think the original turned it off around here.
#pragma push
#pragma opt_rotateloops off

/** @brief Update the objects in the model's own list, then the model. */
void LibClass173380::update()
{
    LibListSentinel* node = objects.sentinel.next;

    while (&objects.sentinel != node)
    {
        static_cast<LibListObject*>(node)->update();
        node = node->next;
    }

    LibModel::update();
}

#pragma pop

/** @brief Destroy the child objects, then destroy the model through its base. */
void LibClass173380::destroy()
{
    for (s32 i = 0; i < 3; i++)
    {
        if (children[i])
        {
            children[i]->destroy();
            children[i] = 0;
        }
    }

    LibModelBase::destroy();
}

/** @brief Use the draw bucket stored at unk83c. */
void LibClass173380::set_default_draw_bucket()
{
    draw_bucket = unk83c;
}

extern "C" void func_0042B000(LibModel* model);

/** @brief Build LibModel's packets, then this model's own unless it was built from another one. */
void LibClass173380::build_packets()
{
    LibModel::build_packets();

    if (!built_from_source)
    {
        func_0042B000(this);
    }
}

/**
 * @brief Return the part a mesh record draws with: its slot in the model's part table, or the record's own copy.
 * @param model Model.
 * @param record Mesh part record.
 * @return The part.
 */
static inline LibModelPart* lib_model_record_part(LibModel* model, LibMeshPartRecord* record)
{
    LibModelPart* part = &record->part;

    if (record->part.slot != 0)
    {
        part = &static_cast<LibModelPart*>(model->parts)[record->part.slot - 1];
    }

    return part;
}

extern "C" {

/**
 * @brief Make the model's flagged parts draw textured triangle strips with three registers, blended and fogged as
 *        the model is.
 * @param model Model.
 */
void func_0042AEC0(LibModel* model)
{
    func_004D5C10(model->resource);
    LibMeshHeader* mesh = reinterpret_cast<LibMeshHeader*>(lib_resource_active_payload(model->resource));
    s32 count = mesh->part_count;
    u32 primitive = (model->fog_enabled ? GS_PRIM_FGE : 0) | 0x4C;

    for (s32 i = 0; i < count; i++)
    {
        LibMeshPartRecord* record = static_cast<LibMeshPartRecord*>(func_004D5AC0(model->resource));

        if (record->unk14 & 1)
        {
            LibModelPart* part = lib_model_record_part(model, record);
            part->first_tag_high = (primitive << 15) | (u32)((GIF_TAG_NREG(3) | GIF_TAG_PRE) >> 32);
            part->first_registers = 0x412;
        }
    }

    FlushCache(0);
}

/**
 * @brief Make the model's flagged parts draw textured triangle strips with four registers.
 * @param model Model.
 */
void func_0042B000(LibModel* model)
{
    func_004D5C10(model->resource);
    LibMeshHeader* mesh = reinterpret_cast<LibMeshHeader*>(lib_resource_active_payload(model->resource));
    s32 count = mesh->part_count;

    for (s32 i = 0; i < count; i++)
    {
        LibMeshPartRecord* record = static_cast<LibMeshPartRecord*>(func_004D5AC0(model->resource));

        if (record->unk14 & 1)
        {
            LibModelPart* part = lib_model_record_part(model, record);
            part->first_tag_high = (u32)((GIF_TAG_NREG(4) | GIF_TAG_PRIM(0x14) | GIF_TAG_PRE) >> 32);
            part->first_registers = 0x42EE;
        }
    }

    FlushCache(0);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042B110);

// TODO: These list loops are entered with a jump to their test like update()'s, and the two child offsets only land
// in the game's registers with loop invariants left in place, so I think the original had both turned off here.
#pragma push
#pragma opt_rotateloops off
#pragma opt_loop_invariants off

/**
 * @brief Render the children slot by slot (each attached model's child in that slot, then this model's own), then
 *        the attached models, then this model.
 */
void LibClass173380::render()
{
    if (unk838)
    {
        LibModel::render();
    }
    else
    {
        s32 i = 2;

        do
        {
            if (children[i])
            {
                LibListSentinel* node = objects.sentinel.next;

                while (&objects.sentinel != node)
                {
                    LibTransformOwner* child = static_cast<LibClass173380*>(node)->children[i];

                    if (child && child->unk63)
                    {
                        child->render();
                    }

                    node = node->next;
                }

                if (children[i]->unk63)
                {
                    children[i]->render();
                }
            }
        } while (--i >= 0);

        LibListSentinel* node = objects.sentinel.next;

        while (&objects.sentinel != node)
        {
            LibTransformOwner* object = static_cast<LibTransformOwner*>(node);

            if (object->unk63)
            {
                object->render();
            }

            node = node->next;
        }

        if (unk83d)
        {
            LibModel::complete_dma(0);
        }
        else
        {
            LibModel::render();
        }
    }
}

#pragma pop

}

/**
 * @brief Extra quadwords to reserve in the draw packet.
 * @return 256.
 */
s32 LibClass173380::get_extra_packet_size()
{
    return 256;
}

extern "C" {

/** Ground the shadows fall on, or null for none. */
extern "C" LibShadowGround* D_001B651C;

/**
 * @brief Build the shadow model's packet for one of the caster's lights: the light's shadow matrix times the model's
 *        transform, the screen scale, and the caster's texture.
 * @param model Shadow model.
 * @param index Light number in the caster's shadow light list.
 * @param matrix Camera.
 * @param context Packet building context; unused.
 */
void func_0042CC80(LibClass173380* model, s32 index, const void* matrix, void* context);


/**
 * @brief Set the shadow model up for one of the caster's lights: the shadow plane (a plane under the caster when the
 *        light is steep, otherwise the ground), the shadow's fade, then the packet.
 * @param model Shadow model.
 * @param index Light number in the caster's shadow light list.
 * @param matrix Camera.
 * @param context Packet building context.
 * @param weight Light weight.
 */
void func_0042C5C0(LibClass173380* model, s32 index, const void* matrix, void* context, float weight)
{
    LibModel* caster = model->unk830;
    LibShadowLightList* lights = &caster->shadow_lights;

    if (index >= caster->shadow_lights.count)
    {
        return;
    }

    if (model->unk834 > 0 && D_001B651C)
    {
        FieldVec4B origin;
        FieldVec4B projected;
        FieldVec4B direction;
        FieldVec4B eye;
        FieldVec4B right;
        FieldVec4B forward;
        LibMatrix44Value view;
        FieldVec4B zero;
        LibMatrix44Value shadow;
        float height = 0.0f;
        origin.x = caster->transform.m[0][3];
        origin.y = caster->transform.m[1][3];
        origin.z = caster->transform.m[2][3];
        origin.w = 1.0f;
        LibLight* light = lights->lights[index];
        const FieldVec4B* position = reinterpret_cast<const FieldVec4B*>(&light->position);

        if (model->resource)
        {
            height = reinterpret_cast<LibMeshHeader*>(lib_resource_payload(model->resource))->sphere_radius;
        }

        if (light->kind & 3)
        {
            direction = origin - *position;
            lib_normalize_vector3(&direction.x);
        }
        else
        {
            direction.set(*reinterpret_cast<const FieldVec4B*>(&light->direction));
        }

        if (direction.y < model->unk84c)
        {
            // TODO: Only the parent update is wanted here; keeping the unused matrix keeps the game's branch shape.
            const LibMatrix44Value* parent = lib_get_parent_matrix(model);
            float distance = (model->unk850 * model->unk70.z) / static_cast<const LibCamera*>(matrix)->projection_distance;
            *reinterpret_cast<unsigned __int128*>(&zero) = 0;
            eye.x = origin.x + direction.x * distance;
            eye.y = origin.y + direction.y * distance;
            eye.z = origin.z + direction.z * distance;
            lib_matrix_look_at(&view, &zero, &direction, 0.0f);
            right.x = 1.0f;
            right.y = 0.0f;
            right.z = 0.0f;
            right.w = 1.0f;
            forward.x = 0.0f;
            forward.y = 1.0f;
            forward.z = 0.0f;
            forward.w = 1.0f;
            vu0_dot_matrix_rows(&view, &right, &right);
            vu0_dot_matrix_rows(&view, &forward, &forward);
            right.x += eye.x;
            right.y += eye.y;
            right.z += eye.z;
            forward.x += eye.x;
            forward.y += eye.y;
            forward.z += eye.z;
            func_004CC7A0(&model->unk820.x, &eye.x, &right.x, &forward.x);
        }
        else
        {
            origin.y -= height;
            model->unk820.x = 0.0f;
            model->unk820.y = -1.0f;
            model->unk820.z = 0.0f;
            model->unk820.w = D_001B651C->get_height(&origin, model);

            if (light->kind & 3)
            {
                lib_build_projective_shadow_matrix(&shadow, (const FieldVec4A*)position, (const FieldVec4A*)&model->unk820);
            }
            else
            {
                lib_build_directional_shadow_matrix(&shadow, (const FieldVec4A*)&direction, (const FieldVec4A*)&model->unk820);
            }

            vu0_dot_matrix_rows(&shadow, &origin, &projected);
            // TODO: The game divides by w here and never uses the result.
            float inverse = 1.0f / projected.w;
            vu0_divide_by_w(&projected, &projected);
            float ground = D_001B651C->get_height(&projected, model);

            if (ground < model->unk820.w)
            {
                ground = model->unk820.w;
            }

            model->unk820.w = ground + model->unk844;
        }
    }

    if (model->unk836 || model->unk837)
    {
        LibVector4 color;
        *reinterpret_cast<unsigned __int128*>(&color) = *reinterpret_cast<const unsigned __int128*>(&model->base_color_factor);
        float alpha = 1.0f;

        if (model->unk836)
        {
            alpha = 0.01f * (model->unk854 * (lights->weights[index] * weight));

            if (alpha <= 0.0f)
            {
                return;
            }
        }

        if (model->unk837)
        {
            FieldVec4B position;
            position.x = matrix_row(&model->transform, 0)->w;
            position.y = matrix_row(&model->transform, 1)->w;
            position.z = matrix_row(&model->transform, 2)->w;
            position.w = 1.0f;
            // TODO: The game multiplies by the squared length here, not one over the length; harmless for a unit normal.
            float fade = model->unk820.w + (model->unk820.x * position.x + model->unk820.y * position.y + model->unk820.z * position.z);
            fade = 0.001f * (model->unk858 * (-fade * ee_rsqrt_in_place(model->unk820.x * model->unk820.x + model->unk820.y * model->unk820.y + model->unk820.z * model->unk820.z, 1.0f)));

            if (!(fade <= 1.0f))
            {
                alpha /= fade;
            }
        }

        if (alpha <= 0.001f)
        {
            return;
        }

        color.w = ee_min(alpha, 1.0f);
        *reinterpret_cast<unsigned __int128*>(&model->base_color_factor) = *reinterpret_cast<const unsigned __int128*>(&color);
        model->update_combined_color_factor();
    }

    func_0042CC80(model, index, matrix, context);
    model->unk83d = 0;
    model->unk66 = 1;
}

/** Partial view of the shadow model's draw packet. */
typedef struct LibShadowPacketHeader
{
    u8 unk00[0x60];
    unsigned __int128 shadow[4];
    unsigned __int128 transform[4];
    u8 unke0[0x1C];
    s32 projective;
    u8 unk100[0x50];
    unsigned __int128 light_position;
    u8 unk160[0x100];
    unsigned __int128 light_direction;
    unsigned __int128 scale;
    unsigned __int128 offset;
    u64 tex0_1;
    s32 tex0_1_register;
    u8 unk29c[4];
    u64 tex0_2;
    s32 tex0_2_register;
} LibShadowPacketHeader;

/**
 * @brief Build the rest of the shadow model's packet.
 * @param model Shadow model.
 * @param matrix Camera.
 */
void func_0042B110(LibClass173380* model, const void* matrix);

/**
 * @brief Build the shadow model's packet for one of the caster's lights: the light's shadow matrix times the model's
 *        transform, the screen scale, and the caster's texture.
 * @param model Shadow model.
 * @param index Light number in the caster's shadow light list.
 * @param matrix Camera.
 * @param context Packet building context; unused.
 */
void func_0042CC80(LibClass173380* model, s32 index, const void* matrix, void* context)
{
    LibShadowPacketHeader* header = (LibShadowPacketHeader*)((u32)&model->draw_packet | EE_UNCACHED_ACCELERATED);
    LibModel* caster = model->unk830;
    LibShadowLightList* lights = &caster->shadow_lights;

    if (index >= caster->shadow_lights.count)
    {
        return;
    }

    if (model->source != 0)
    {
        void* payload_override = model->resource->payload_override;
        model->select_payload(payload_override, model->source->get_packet_set());
    }

    LibVector4 scale;
    scale.x = 0.0009765625f;
    scale.y = 0.0009765625f;
    float half = 0.5f;
    LibDisplayArea& area = D_001B6520->display_area;
    header->scale = *(unsigned __int128*)&scale;
    LibCameraContext* display = D_001B6520;
    scale.x *= 2047.5f - half * area.width;
    half = display->unk3E4C ? half : 0.0f;
    scale.y *= 2047.5f - 0.5f * area.height + half;
    header->offset = *(unsigned __int128*)&scale;
    LibLight* light = lights->lights[index];
    LibMatrix44Value shadow;

    if (!(light->kind & 3))
    {
        LibVector4 direction;
        header->projective = 0;
        direction.x = light->transform.m[0][1];
        direction.y = light->transform.m[1][1];
        direction.z = light->transform.m[2][1];
        direction.w = 1.0f;
        header->light_direction = *(unsigned __int128*)&direction;
        const FieldVec4A* light_direction = (const FieldVec4A*)&light->direction;
        lib_build_directional_shadow_matrix(&shadow, light_direction, (const FieldVec4A*)&model->unk820);
    }
    else
    {
        LibVector4 position;
        header->projective = 1;
        position.x = light->transform.m[0][3];
        position.y = light->transform.m[1][3];
        position.z = light->transform.m[2][3];
        position.w = 1.0f;
        header->light_position = *(unsigned __int128*)&position;
        const FieldVec4A* light_position = (const FieldVec4A*)&light->position;
        lib_build_projective_shadow_matrix(&shadow, light_position, (const FieldVec4A*)&model->unk820);
    }

    vu0_multiply_matrix(&shadow, &shadow, &model->transform);
    header->shadow[0] = *(unsigned __int128*)&shadow.m[0];
    header->shadow[1] = *(unsigned __int128*)&shadow.m[1];
    header->shadow[2] = *(unsigned __int128*)&shadow.m[2];
    header->shadow[3] = *(unsigned __int128*)&shadow.m[3];
    const unsigned __int128* from = reinterpret_cast<const unsigned __int128*>(&model->transform);

    if (model->unk5a1)
    {
        model->unk5a1 = 0;
    }
    else
    {
        unsigned __int128* to = header->transform;

        *to++ = *from++;
        *to++ = *from++;
        *to++ = *from++;
        *to++ = *from++;
    }

    LibMeshHeader* mesh = reinterpret_cast<LibMeshHeader*>(lib_resource_payload(model->resource));

    // TODO: Like LibModel::build_packet, the game keeps a jump at the end of this arm for a flag that's never read;
    // the flag is a guess.
    bool rebuilt = false;

    if (model->packet == 0)
    {
        model->build_packets();
        model->unk791 = 1;

        if (model->packet == 0)
        {
            model->unk63 = 0;
            return;
        }

        rebuilt = true;
    }
    else
    {
        s32 parts = mesh->part_count;

        if (model->unk77c != parts)
        {
            model->build_packets();

            if (model->packet == 0)
            {
                model->unk63 = 0;
                return;
            }
        }
    }

    model->payload = reinterpret_cast<u8*>(mesh);

    if (model->unk59d_0)
    {
        func_004A7AC0(model, static_cast<const LibCamera*>(matrix));
    }

    u64 tex0 = ((u64)((g_vram_allocator->allocations[30] >> 5) & 0x3FFF) << 37) | 0x2C00000;
    header->tex0_1 = tex0;
    header->tex0_1_register = GS_REGISTER_TEX2_1;
    header->tex0_2 = tex0 | ((u64)1 << 56);
    header->tex0_2_register = GS_REGISTER_TEX2_1;
    func_0042B110(model, matrix);
    ee_sync();
    model->unk63 = 1;
}

/** Most lights a shadow model draws shadows for. */
extern "C" u8 D_001B61BC;

/** Frames a shadow model's extra child lives without being chosen again. */
extern "C" s32 D_001B61B8;


/**
 * @brief Pick the caster's strongest lights (up to unk835), keep one child shadow model per extra light, and build
 *        the shadows of this model, its children and the models in its own list.
 * @param matrix Camera.
 * @param context Packet building context.
 */
void LibClass173380::build_packet(const void* matrix, void* context)
{
    if (resource == 0)
    {
        return;
    }

    if (unk830 == 0)
    {
        return;
    }

    if (!unk830->unk63)
    {
        func_004A59D0(unk830, context);
    }

    LibModel* caster = unk830;
    s32 count = caster->shadow_lights.count;
    LibShadowLightList* lights = &caster->shadow_lights;

    if (count == 0)
    {
        return;
    }

    s32 limit = unk835;

    if (D_001B61BC < limit)
    {
        limit = D_001B61BC;
    }

    s32 visible = 0;
    float total = unk840;
    s8 order[4];

    for (s32 i = 0; i < count; i++)
    {
        if (!lights->unk04[i])
        {
            continue;
        }

        if (lights->lights[i]->unk291)
        {
            FieldVec4B position;
            position.x = transform.m[0][3];
            position.y = transform.m[1][3];
            position.z = transform.m[2][3];
            position.w = 1.0f;

            if (!(lights->lights[i]->position.y <= position.y))
            {
                continue;
            }
        }

        float weight = lights->weights[i];

        if (!(weight <= 0.0f))
        {
            order[visible++] = i;
        }

        if (weight < 0.0f)
        {
            total += weight;
            total = ee_max(0.0f, total);
        }
    }

    if (visible == 0)
    {
        return;
    }

    if (total == 0.0f)
    {
        return;
    }

    for (s32 i = 0; i < 3; i++)
    {
        if (children[i])
        {
            static_cast<LibClass173270*>(children[i])->light_index = -1;

            if (static_cast<LibClass173270*>(children[i])->expire())
            {
                LibClass173380* child = static_cast<LibClass173380*>(children[i]);

                if (child->unk830)
                {
                    if (child->unk830->unk790)
                    {
                        child->unk830->unk790--;
                    }

                    child->unk830 = 0;
                }

                children[i]->destroy();
                children[i] = 0;
            }
        }
    }

    if (1 < visible)
    {
        for (s32 i = 0; i < visible; i++)
        {
            for (s32 j = i + 1; j < visible; j++)
            {
                if (lights->weights[order[i]] < lights->weights[order[j]])
                {
                    s8 swap = order[i];
                    order[i] = order[j];
                    order[j] = swap;
                }
            }
        }

        if (limit < visible)
        {
            visible = limit;
        }

        for (s32 i = 1; i < visible; i++)
        {
            if (children[i - 1] == 0)
            {
                LibClass173270* child = new (0) LibClass173270;

                if (child)
                {
                    if (child->build_from(0, this))
                    {
                        children[i - 1] = child;
                        child->owner = owner;
                    }
                    else
                    {
                        child->destroy();
                    }
                }
            }

            if (children[i - 1])
            {
                static_cast<LibClass173270*>(children[i - 1])->lifetime = D_001B61B8;
                static_cast<LibClass173270*>(children[i - 1])->set_light_index(order[i]);
            }
        }
    }

    unk83b = order[0];

    if (unk838)
    {
        return;
    }

    bool drawn = false;

    for (LibListSentinel* node = objects.sentinel.next; !at_list_end(&objects.sentinel, node); node = node->next)
    {
        LibClass173380* object = static_cast<LibClass173380*>(node);
        object->unk63 = 0;
        object->build_packet(matrix, context);
    }

    for (s32 i = 2; i >= 0; i--)
    {
        if (children[i] == 0)
        {
            continue;
        }

        s32 index = static_cast<LibClass173270*>(children[i])->light_index;
        children[i]->unk63 = 0;

        if (index >= 0)
        {
            for (LibListSentinel* node = objects.sentinel.next; !at_list_end(&objects.sentinel, node); node = node->next)
            {
                LibClass173380* object = static_cast<LibClass173380*>(node);

                if (object->children[i])
                {
                    object->children[i]->unk63 = 0;

                    if (static_cast<LibClass173380*>(object->children[i])->unk830->shadow_lights.count)
                    {
                        s32 object_index = static_cast<LibClass173270*>(object->children[i])->light_index;

                        if (object_index >= 0)
                        {
                            object->children[i]->unk62 = 0;
                            object->children[i]->update_transform_matrix();
                            func_0042C5C0(static_cast<LibClass173380*>(object->children[i]), object_index, matrix, context, total);

                            if (object->children[i]->unk63)
                            {
                                drawn = true;
                            }
                        }
                    }
                }
            }

            children[i]->unk62 = 0;
            children[i]->update_transform_matrix();
            func_0042C5C0(static_cast<LibClass173380*>(children[i]), index, matrix, context, total);

            if (children[i]->unk63)
            {
                drawn = true;
            }
        }
        else
        {
            for (LibListSentinel* node = objects.sentinel.next; !at_list_end(&objects.sentinel, node); node = node->next)
            {
                LibClass173380* object = static_cast<LibClass173380*>(node);

                if (object->children[i])
                {
                    object->children[i]->unk63 = 0;
                }
            }
        }
    }

    for (LibListSentinel* node = objects.sentinel.next; !at_list_end(&objects.sentinel, node); node = node->next)
    {
        LibClass173380* object = static_cast<LibClass173380*>(node);
        object->unk63 = 0;
        object->unk62 = 0;
        object->update_transform_matrix();
        func_0042C5C0(object, object->unk83b, matrix, context, total);

        if (!drawn && object->unk63)
        {
            drawn = true;
        }
    }

    func_0042C5C0(this, order[0], matrix, context, total);

    if (drawn && !unk63)
    {
        unk63 = 1;
        unk83d = 1;
    }
}

}

/** @brief Construct the model with its default settings. */
LibClass173380::LibClass173380()
{
    set_type_id(0x120);
    unk83d = 0;
    unk830 = 0;
    unk844 = 10.0f;
    unk820.x = 0.0f;
    unk820.y = 1.0f;
    unk820.z = 0.0f;
    unk820.w = -3.0f;
    unk835 = 4;
    built_from_source = 0;
    unk836 = 0;
    unk837 = 1;
    unk854 = 100.0f;
    unk858 = 50.0f;
    unk83b = 0;
    unk848 = 2.0f;
    children[0] = 0;
    children[1] = 0;
    children[2] = 0;
    unk860[0] = 0;
    unk860[1] = 0;
    unk868[0] = 0;
    unk868[1] = 0;
    unk870[0] = 0;
    unk870[1] = 0;
    unk85c = 0;
    unk838 = 0;
    unk83a = 1;
    unk840 = 1.0f;
    unk67 = 0;
    unk84c = 0.2f;
    unk850 = 480.0f;
    unk83c = 4;
    unk83e = 0;
    unk839 = 0;
}

extern "C" {

/** @brief Upload the palette image at D_004EC600. */
void lib_upload_default_palette(void)
{
    func_004D8C20(D_004EC600, 30);
}

}

/**
 * @brief Return the entry's type code.
 * @return 34.
 */
s32 LibClass173490::func_slot14()
{
    return 34;
}

extern "C" {

s32 func_0042DCE0(LibClass173490* entry, const LibVector4* position, s32* cell, float* x, float* y);

/**
 * @brief Multiply the first three components of a vector by another vector's.
 * @param vector Vector to scale.
 * @param scale Per-component factors; w is unused.
 * @return The scaled vector.
 */
static inline FieldVec4B scale_components(const FieldVec4B& vector, const LibVector4& scale)
{
    FieldVec4B result = vector;
    result.x *= scale.x;
    result.y *= scale.y;
    result.z *= scale.z;
    return result;
}

/**
 * @brief Add a vector at a position, spread bilinearly over the four cells around it.
 * @param entry Grid entry.
 * @param position Position to add at.
 * @param amount Vector to add.
 */
void func_0042D9B0(LibClass173490* entry, const LibVector4* position, const LibVector4* amount)
{
    s32 stride = entry->unk30[0] + 2;
    s32 cell;
    float x;
    float y;

    if (func_0042DCE0(entry, position, &cell, &x, &y))
    {
        // TODO: The second cell array holds vectors here; LibClass173490Entry may really be a FieldVec4B.
        FieldVec4B* cells = reinterpret_cast<FieldVec4B*>(entry->unk44);
        float weight;

        weight = (1.0f - x) * (1.0f - y);
        cells[cell] += scale_components(FieldVec4B(weight, weight, weight, weight), *amount);
        weight = x * (1.0f - y);
        cells[cell + 1] += scale_components(FieldVec4B(weight, weight, weight, weight), *amount);
        weight = (1.0f - x) * y;
        cells[cell + stride] += scale_components(FieldVec4B(weight, weight, weight, weight), *amount);
        weight = x * y;
        cells[cell + stride + 1] += scale_components(FieldVec4B(weight, weight, weight, weight), *amount);
    }
}

/**
 * @brief Find the grid cell a position falls in, in the space of the entry's transform, and where in the cell.
 * @param entry Grid entry.
 * @param position Position to look up.
 * @param cell Receives the cell index (one cell of border on every side).
 * @param x Receives the position across the cell, from 0 to 1.
 * @param y Receives the position down the cell, from 0 to 1.
 * @return One when the position is over the grid, otherwise zero.
 */
s32 func_0042DCE0(LibClass173490* entry, const LibVector4* position, s32* cell, float* x, float* y)
{
    LibVector4 local;

    if (entry->unk3c == 0)
    {
        return 0;
    }

    if (!entry->unk3c->matrix_ready)
    {
        entry->unk3c->update_transform_matrix();
        mark_transpose_current(entry->unk3c);
        func_004D9E70(entry->unk3c);
    }
    else if (!entry->unk3c->unk20e_0)
    {
        transpose_transform(entry->unk3c);
        func_004D9E70(entry->unk3c);
    }
    else if (!entry->unk3c->unk20e_2)
    {
        func_004D9E70(entry->unk3c);
    }

    entry->unk3c->to_local(position, &local);
    s32 width = entry->unk30[0];
    s32 height = entry->unk30[1];
    float size = *(float*)&entry->unk30[4];
    float left = *(float*)&entry->unk30[2];
    float top = *(float*)&entry->unk30[3];
    float right = left + size * (width - 1);
    float bottom = top + size * (height - 1);

    if (local.x < left || !(local.x <= right) || local.z < top || !(local.z <= bottom))
    {
        return 0;
    }

    s32 column = (local.x - left) / size;
    s32 row = (local.z - top) / size;
    width += 2;
    *x = (local.x - column * size - left) / size;
    *y = (local.z - row * size - top) / size;
    *cell = (column + 1) + (row + 1) * width;
    return 1;
}

/**
 * @brief Copy each vertex's cell element into the output, or, when unk4c is clear, the output's values back into
 *        the cells and set unk4d.
 * @param output Output to fill or read.
 * @param index Bit index, which picks the record of cell indices.
 */
void LibClass173490::func_slot10(LibEntryOutput* output, s32 index)
{
    LibClass173490Entry* values = output->values;
    u16* cells = static_cast<u16*>(output->records[index]);
    s32 count = output->count;
    LibClass173490Entry* entries = unk40;

    if (unk4c)
    {
        for (s32 i = 0; i < count; i++)
        {
            *values = entries[*cells];
            cells++;
            values++;
        }
    }
    else
    {
        unk4d = 1;

        for (s32 i = 0; i < count; i++)
        {
            entries[*cells] = *values;
            cells++;
            values++;
        }
    }
}

/**
 * @brief Run one step of the ripple grid on VU0: drop a random ripple when enabled, spread the heights into the
 *        velocities (only on masked cells unless the grid is unmasked), then move the masked heights. Rewind the
 *        records; while the grid is idle only rewind them.
 * @param root Model transform the grid belongs to.
 * @return One.
 */
s32 LibClass173490::func_slot1C(LibTransform* root)
{
    if (unk4d)
    {
        unk4c = 1;
    }

    if (!unk4c)
    {
        unk38 = reinterpret_cast<u32>(unk34);
        return 1;
    }

    unk3c = root;
    LibClass174C20Header* header = reinterpret_cast<LibClass174C20Header*>(unk30);
    s32 depth = header->rows + 2;
    s32 width = header->columns + 2;
    LibClass173490Entry* heights = unk40;
    LibClass173490Entry* velocities = unk44;

    if (header->random_drops)
    {
        s32 x = resident_random_below(width - 2) + 1;
        s32 y = resident_random_below(depth - 2) + 1;
        float* v = reinterpret_cast<float*>(velocities);
        v[(x + y * width) * 4 + 0] += reinterpret_cast<LibClass174C20Header*>(unk30)->drop_strength * (0.02f * (resident_random_fraction() - 0.5f));
        v[(x + y * width) * 4 + 1] += reinterpret_cast<LibClass174C20Header*>(unk30)->drop_strength * (0.02f * (resident_random_fraction() - 0.5f));
        v[(x + y * width) * 4 + 2] += reinterpret_cast<LibClass174C20Header*>(unk30)->drop_strength * (0.02f * (resident_random_fraction() - 0.5f));
    }

    float step = reinterpret_cast<LibClass174C20Header*>(unk30)->speed * g_frame_seconds;
    u32* mask = unk48;

    if (reinterpret_cast<LibClass174C20Header*>(unk30)->unmasked)
    {
        vu0_ripple_set_steps(step, 4.0f * step);

        if (2 < width)
        {
            for (s32 y = 1; y < depth - 1; y++)
            {
                s32 cell = y * width + 1;
                LibClass173490Entry* left = &heights[cell - 1];
                LibClass173490Entry* velocity = &velocities[cell];
                u32* weights = &mask[cell];
                vu0_ripple_load_row(left);
                s32 count = width - 2;
                left++;

                do
                {
                    vu0_ripple_rotate(left);
                    LibClass173490Entry* out = velocity;
                    vu0_ripple_spread(out, left - width, left + width);
                    count--;
                    left++;
                    velocity++;
                    s32 done = ee_movz(0, 1, count);
                    vu0_ripple_store_velocity(out);

                    if (done)
                    {
                        break;
                    }
                } while (true);
            }
        }
    }
    else
    {
        vu0_ripple_set_steps(step, 4.0f * step);

        if (2 < width)
        {
            for (s32 y = 1; y < depth - 1; y++)
            {
                s32 cell = y * width + 1;
                LibClass173490Entry* left = &heights[cell - 1];
                LibClass173490Entry* velocity = &velocities[cell];
                u32* weights = &mask[cell];
                vu0_ripple_load_row(left);
                s32 count = width - 2;
                left++;

                for (;;)
                {
                    vu0_ripple_rotate(left);
                    u32 weight = *weights++;

                    if (weight == 0)
                    {
                        count--;
                        left++;
                        velocity++;

                        if (count == 0)
                        {
                            break;
                        }

                        continue;
                    }

                    LibClass173490Entry* out = velocity;
                    vu0_ripple_spread_masked(out, left - width, left + width, weight);
                    left++;
                    velocity++;
                    vu0_ripple_weight_spread();
                    count--;
                    s32 done = ee_movz(0, 1, count);
                    vu0_ripple_store_velocity(out);

                    if (done)
                    {
                        break;
                    }
                }
            }
        }
    }

    vu0_ripple_set_frame(g_frame_seconds);

    if (width != 0)
    {
        for (s32 y = 0; y < depth; y++)
        {
            s32 count = width;
            s32 row = y * width;
            u32* weights = &mask[row];
            LibClass173490Entry* height = &heights[row];
            LibClass173490Entry* velocity = &velocities[row];

            for (;;)
            {
                u32 weight = *weights++;

                if (weight == 0)
                {
                    count--;
                    height++;
                    velocity++;

                    if (count == 0)
                    {
                        break;
                    }

                    continue;
                }

                vu0_ripple_load_cell(height, velocity);
                count--;
                velocity++;
                vu0_ripple_integrate();
                s32 done = ee_movz(0, 1, count);
                vu0_ripple_store_height(height);
                height++;

                if (done)
                {
                    break;
                }
            }
        }
    }

    unk38 = reinterpret_cast<u32>(unk34);
    return 1;
}

/**
 * @brief Return the record at the cursor and move past it; the size is given in halfwords and rounded up to 16 bytes.
 * @param index Bit index; unused.
 * @param size Size in halfwords; receives the size in bytes.
 * @return Record.
 */
u8* LibClass173490::read_record(u32 index, u32* size)
{
    *size = (*size * 2 + 15) & ~15;
    u8* record = reinterpret_cast<u8*>(unk38);
    unk38 += *size;
    return record;
}

/** @brief Clear both element arrays and the two flags. */
void LibClass173490::clear_entries()
{
    if (!unk40)
    {
        return;
    }

    s32 rows = unk30[1] + 2;
    s32 columns = unk30[0] + 2;
    LibClass173490Entry zero;
    zero.x = 0.0f;
    zero.y = 0.0f;
    zero.z = 0.0f;
    zero.w = 0.0f;
    LibClass173490Entry* first = unk40;
    LibClass173490Entry* second = unk44;

    for (s32 y = 0; y < rows; y++)
    {
        for (s32 x = 0; x < columns; x++)
        {
            *first = zero;
            *second = zero;
            first++;
            second++;
        }
    }

    unk4c = 0;
    unk4d = 0;
}

/**
 * @brief Use borrowed grid data: find its header, row words and records, and allocate and clear both element arrays.
 * @param value Borrowed data.
 */
void LibClass173490::set_borrowed_data(void* value)
{
    data = value;
    data_is_borrowed = 1;
    unk30 = reinterpret_cast<u32*>(static_cast<u8*>(value) + 0x10);
    u32* header = unk30;
    s32 columns = header[0] + 2;
    s32 rows = header[1] + 2;
    unk48 = reinterpret_cast<u32*>(reinterpret_cast<u8*>(header) + 0x20);
    s32 count = columns * rows + 1;
    unk34 = unk48 + ((count + 2) & ~3);
    unk44 = new (0) LibClass173490Entry[count];
    unk40 = new (0) LibClass173490Entry[count];

    if (!unk40 || !unk44)
    {
        delete[] unk40;
        delete[] unk44;
        unk40 = 0;
        unk44 = 0;
    }

    clear_entries();
}

}

/** @brief Free both entry arrays, then destroy the entry. */
LibClass173490::~LibClass173490()
{
    delete[] unk40;
    delete[] unk44;
}

/** @brief Start with no entry arrays. */
LibClass173490::LibClass173490()
{
    unk19 = 1;
    unk0f = 8;
    unk40 = 0;
    unk44 = 0;
    unk3c = 0;
    unk4c = 0;
    unk4d = 0;
}

extern "C" {

}

/**
 * @brief Return the entry's type code.
 * @return Three.
 */
s32 LibClass1734B0::func_slot14()
{
    return 3;
}

/**
 * @brief Use data the entry doesn't own.
 * @param value Borrowed data.
 */
void LibClass1779F0::set_borrowed_data(void* value)
{
    data = value;
    data_is_borrowed = 1;
}

/**
 * @brief Return the next record when the entry has one for a bit; the base entry has none.
 * @param index Bit index.
 * @param size Receives the record's size.
 * @return Record, or null.
 */
u8* LibClass1779F0::read_record(u32 index, u32* size)
{
    return 0;
}

extern "C" {

/**
 * @brief Play one of four sounds from a table at random, following an emitter.
 * @param emitter Object the sound follows.
 * @param table Table index, 1 to 10.
 * @return Slot identifier of the sound, or 0 for a bad index.
 */
s32 func_0042EB50(ResidentSoundEmitter* emitter, s32 table)
{
    s16* numbers;

    if (table <= 0 || table > 10)
    {
        return 0;
    }

    numbers = D_004ED0EC[table];
    return resident_sound_bank_set_play_voice(D_001B6524, numbers[resident_random_below(4)], emitter, 0, 0x7F, 0);
}

/**
 * @brief Play a voice line from one of two sets by level.
 * @param emitter Object the sound follows.
 * @param numbers Sound number table.
 * @param first Index of the first number to pick from; one of it and the next is picked at random.
 * @return Slot identifier of the sound.
 */
static inline s32 lib_play_level_voice(ResidentSoundEmitter* emitter, const s16* numbers, s32 first)
{
    return resident_sound_bank_set_play_voice(D_001B6524, numbers[first + resident_random_below(2)], emitter, 0, 0x7F, 0);
}

/**
 * @brief Sometimes play a voice line chosen by a value from the system settings grid: never below 10, more often and
 *        at a higher level (one per 8 above 10, up to 4) as it grows; some entries use the second set.
 * @param emitter Object the sound follows.
 * @param table Table index and grid column, 1 to 10.
 * @param entry Grid row, 1 to 10.
 * @return Slot identifier of the sound, or 0 when nothing plays.
 */
s32 func_0042EBE0(ResidentSoundEmitter* emitter, s32 table, s32 entry)
{
    if (table <= 0 || table > 10)
    {
        return 0;
    }

    if (entry <= 0 || entry > 10)
    {
        return 0;
    }

    if (!resident_poll_resource_queue(g_resource_queue))
    {
        return 0;
    }

    LibSystemSettings* settings =
        reinterpret_cast<LibSystemSettings*>(resident_find_entry(resident_get_entry_table(resident_get_system()), 1));
    s32 value = func_00457980(settings, entry, table);

    if (value < 10)
    {
        return 0;
    }

    if (resident_rand() > (u32)(value * 90))
    {
        return 0;
    }

    s32 level = (value - 10) / 8;

    if (level > 4)
    {
        level = 4;
    }

    s16* numbers = D_004ED0BC[table];

    switch (table)
    {
    case 1:
        if (entry == 5)
        {
            return lib_play_level_voice(emitter, numbers, level + 6);
        }

        return lib_play_level_voice(emitter, numbers, level);
    case 2:
        if (entry != 1 && entry != 8 && entry != 7)
        {
            return lib_play_level_voice(emitter, numbers, level + 6);
        }

        return lib_play_level_voice(emitter, numbers, level);
    case 4:
        if (entry == 2 || entry == 3 || entry == 5 || entry == 8)
        {
            return lib_play_level_voice(emitter, numbers, level + 6);
        }

        return lib_play_level_voice(emitter, numbers, level);
    default:
        return lib_play_level_voice(emitter, numbers, level);
    }
}

/**
 * @brief Sometimes play a voice line chosen by a value from the system settings grid: never below 10, more often and
 *        from a higher band as the value grows (bands from 30 and 45).
 * @param emitter Object the sound follows.
 * @param table Table index and grid column, 1 to 10.
 * @param entry Number in the band and grid row, 1 to 10.
 * @return Slot identifier of the sound, or 0 when nothing plays.
 */
s32 func_0042EF30(ResidentSoundEmitter* emitter, s32 table, s32 entry)
{
    if (table <= 0 || table > 10)
    {
        return 0;
    }

    if (entry <= 0 || entry > 10)
    {
        return 0;
    }

    if (!resident_poll_resource_queue(g_resource_queue))
    {
        return 0;
    }

    LibSystemSettings* settings =
        reinterpret_cast<LibSystemSettings*>(resident_find_entry(resident_get_entry_table(resident_get_system()), 1));
    s32 value = func_00457980(settings, entry, table);

    if (value < 10)
    {
        return 0;
    }

    if (resident_rand() > (u32)(value * 80))
    {
        return 0;
    }

    s16* numbers = D_004ECFBC[table];

    if (value < 30)
    {
        return resident_sound_bank_set_play_voice(D_001B6524, numbers[entry - 1], emitter, 0, 0x7F, 0);
    }

    if (value < 45)
    {
        return resident_sound_bank_set_play_voice(D_001B6524, numbers[entry + 9], emitter, 0, 0x7F, 0);
    }

    return resident_sound_bank_set_play_voice(D_001B6524, numbers[entry + 19], emitter, 0, 0x7F, 0);
}

/**
 * @brief Play one of four sounds from a second set of tables at random, following an emitter.
 * @param emitter Object the sound follows.
 * @param table Table index, 1 to 10.
 * @return Slot identifier of the sound, or 0 for a bad index.
 */
s32 func_0042F0D0(ResidentSoundEmitter* emitter, s32 table)
{
    s16* numbers;

    if (table <= 0 || table > 10)
    {
        return 0;
    }

    numbers = D_004ECD0C[table];
    return resident_sound_bank_set_play_voice(D_001B6524, numbers[resident_random_below(4)], emitter, 0, 0x7F, 0);
}

/**
 * @brief Play one of two sounds from a table, the first most of the time, following an emitter.
 * @param emitter Object the sound follows.
 * @param table Table index, 1 to 10.
 * @return Slot identifier of the sound, or 0 for a bad index.
 */
s32 func_0042F160(ResidentSoundEmitter* emitter, s32 table)
{
    s16* numbers;

    if (table <= 0 || table > 10)
    {
        return 0;
    }

    numbers = D_004ECCDC[table];

    if (resident_rand() < 24000)
    {
        return resident_sound_bank_set_play_voice(D_001B6524, numbers[0], emitter, 0, 0x7F, 0);
    }

    return resident_sound_bank_set_play_voice(D_001B6524, numbers[1], emitter, 0, 0x7F, 0);
}

/**
 * @brief Play sound data following an emitter, when the sound bank set is up.
 * @param emitter Object the sound follows.
 * @param buffer Sound data to play.
 * @param owns_buffer Nonzero to free the buffer when the sound ends.
 * @return Slot identifier of the sound, or 0 without a sound bank set.
 */
s32 func_0042F210(ResidentSoundEmitter* emitter, u8* buffer, s32 owns_buffer)
{
    if (D_001B6524 == 0)
    {
        return 0;
    }

    return resident_sound_bank_set_play_data(D_001B6524, buffer, emitter, 0, 0x7F, 0, owns_buffer);
}

/**
 * @brief Test whether exactly one of the sound bank set's banks is loaded.
 * @return Nonzero when exactly one is.
 */
static inline u8 lib_one_sound_bank_loaded()
{
    ResidentSoundBankSet* set = D_001B6524;
    s32 loaded = 0;

    for (s32 i = 0; i < RESIDENT_SOUND_BANK_SLOT_COUNT; i++)
    {
        if (set->banks[i])
        {
            loaded++;
        }
    }

    if (loaded == 1)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief Pick a sound number from a table by level: each of six conditions adds a half level, up to level two.
 * @param table Table index, 1 to 10.
 * @param amount Adds a half level from 7200 and another from 28800.
 * @param value Adds a half level above limit, and another above four times limit.
 * @param limit See value.
 * @param count Adds a half level above zero and another from four.
 * @return Sound number, or 0 for a bad index.
 */
extern "C" s32 func_0042F250(s32 table, s32 amount, s32 value, s32 limit, s32 count)
{
    if (table <= 0 || table > 10)
    {
        return 0;
    }

    s32 level = 0;

    if (amount >= 7200)
    {
        level++;
    }

    if (amount >= 28800)
    {
        level++;
    }

    if (limit < value)
    {
        level++;
    }

    if (limit * 4 < value)
    {
        level++;
    }

    if (count > 0)
    {
        level++;
    }

    if (count > 3)
    {
        level++;
    }

    level = clamp_high(level >> 1, 2);
    s16* numbers = D_004ECCAC[table];

    if (table == 1 && level == 1)
    {
        if (lib_one_sound_bank_loaded())
        {
            s32 pick = resident_random_below(3);

            if (pick == 0)
            {
                return 0x13CC;
            }

            return numbers[3 + pick];
        }
    }

    return numbers[level * 3 + resident_random_below(3)];
}

/**
 * @brief Play sound data following an emitter, when the sound bank set is up.
 * @param emitter Object the sound follows.
 * @param buffer Sound data to play.
 * @param owns_buffer Nonzero to free the buffer when the sound ends.
 * @return Slot identifier of the sound, or 0 without a sound bank set.
 */
s32 func_0042F3E0(ResidentSoundEmitter* emitter, u8* buffer, s32 owns_buffer)
{
    if (D_001B6524 == 0)
    {
        return 0;
    }

    return resident_sound_bank_set_play_data(D_001B6524, buffer, emitter, 0, 0x7F, 0, owns_buffer);
}

/**
 * @brief Pick a sound number from a group: the first, or one of the other two at random.
 * @param group Group of three sound numbers.
 * @param random Nonzero to pick one of the other two at random.
 * @return Sound number.
 */
static inline s32 lib_pick_sound_number(const s16* group, s32 random)
{
    if (random == 0)
    {
        return group[0];
    }

    const s16* alternatives = &group[1];

    return alternatives[resident_random_below(2)];
}

/**
 * @brief Pick a sound number from a table by comparing two values.
 * @param table Table index, 1 to 10.
 * @param first First value.
 * @param second Second value.
 * @param random Nonzero to pick one of a group's other two numbers at random.
 * @param special Nonzero to use the fourth group regardless of the values.
 * @return Sound number, or 0 for a bad index.
 */
extern "C" s32 func_0042F420(s32 table, s32 first, s32 second, s32 random, s32 special)
{
    if (table <= 0 || table > 10)
    {
        return 0;
    }

    s16 (*groups)[3] = D_004ECB3C[table];

    if (special)
    {
        return lib_pick_sound_number(groups[3], random);
    }

    if (second + 10 < first)
    {
        return lib_pick_sound_number(groups[0], random);
    }

    if (first + 10 < second)
    {
        return lib_pick_sound_number(groups[2], random);
    }

    return lib_pick_sound_number(groups[1], random);
}

/**
 * @brief Play a sound bank slot's sound for an event, or now and then one of the slot character's voice lines for it.
 *
 * Each slot remembers whether its last voice line asked to hold back the next sound of some events.
 * @param emitter Object the sound follows.
 * @param slot Sound bank slot.
 * @param event Event the sound is for.
 * @param voice Nonzero to allow a voice line instead of the slot's sound.
 * @return Slot identifier of the sound, or 0 when nothing plays.
 */
extern "C" s32 func_0042F550(ResidentSoundEmitter* emitter, s32 slot, s32 event, s32 voice)
{
    if (D_001B6524 == 0)
    {
        return 0;
    }

    if (D_001B6524->loading != 0)
    {
        return 0;
    }

    if (voice == 0 || !resident_poll_resource_queue(g_resource_queue) || resident_rand() < 30000)
    {
        u8* held = &D_001B6528[slot];

        if (*held)
        {
            *held = 0;

            switch (D_001B6524->banks[slot])
            {
            case 1:
                switch (event)
                {
                case 0xB:
                case 0xD:
                case 0x10:
                case 0x12:
                case 0x15:
                case 0x17:
                case 0x19:
                case 0x1B:
                case 0x1D:
                    return 0;
                }

                break;
            case 5:
                switch (event)
                {
                case 0x13:
                case 0x15:
                    return 0;
                }

                break;
            }
        }

        *held = 0;
        return resident_sound_bank_set_play(D_001B6524, slot, event, emitter, 0, 0x7F, 0);
    }

    switch (D_001B6524->banks[slot])
    {
    case 1:
        switch (event)
        {
        case 0xA:
            D_001B6528[slot] = 1;
            return resident_sound_play_voice(g_sound, 0x1357, emitter, 0, 0x7F, 0);
        case 0xC:
            D_001B6528[slot] = 1;
            return resident_sound_play_voice(g_sound, 0x1358, emitter, 0, 0x7F, 0);
        case 0xE:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1359, emitter, 0, 0x7F, 0);
        case 0xF:
            D_001B6528[slot] = 1;
            return resident_sound_play_voice(g_sound, 0x135A, emitter, 0, 0x7F, 0);
        case 0x11:
            D_001B6528[slot] = 1;
            return resident_sound_play_voice(g_sound, 0x135B, emitter, 0, 0x7F, 0);
        case 0x13:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x135C, emitter, 0, 0x7F, 0);
        case 0x14:
            D_001B6528[slot] = 1;
            return resident_sound_play_voice(g_sound, 0x135D, emitter, 0, 0x7F, 0);
        case 0x16:
            D_001B6528[slot] = 1;
            return resident_sound_play_voice(g_sound, 0x135E, emitter, 0, 0x7F, 0);
        case 0x18:
            D_001B6528[slot] = 1;
            return resident_sound_play_voice(g_sound, 0x135F, emitter, 0, 0x7F, 0);
        case 0x1A:
            D_001B6528[slot] = 1;
            return resident_sound_play_voice(g_sound, 0x1360, emitter, 0, 0x7F, 0);
        case 0x1C:
            D_001B6528[slot] = 1;
            return resident_sound_play_voice(g_sound, 0x1361, emitter, 0, 0x7F, 0);
        case 0xB:
        case 0xD:
        case 0x10:
        case 0x12:
        case 0x15:
        case 0x17:
        case 0x19:
        case 0x1B:
        case 0x1D:
            D_001B6528[slot] = 0;
            return 0;
        }

        break;
    case 3:
        switch (event)
        {
        case 0xA:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1362, emitter, 0, 0x7F, 0);
        case 0xB:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1363, emitter, 0, 0x7F, 0);
        case 0xC:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1364, emitter, 0, 0x7F, 0);
        case 0xD:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1365, emitter, 0, 0x7F, 0);
        case 0xE:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1366, emitter, 0, 0x7F, 0);
        case 0xF:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1367, emitter, 0, 0x7F, 0);
        case 0x10:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1368, emitter, 0, 0x7F, 0);
        case 0x11:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1369, emitter, 0, 0x7F, 0);
        case 0x12:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x136A, emitter, 0, 0x7F, 0);
        case 0x13:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x136B, emitter, 0, 0x7F, 0);
        case 0x14:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x136C, emitter, 0, 0x7F, 0);
        }

        break;
    case 4:
        switch (event)
        {
        case 0xA:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x136D, emitter, 0, 0x7F, 0);
        case 0xB:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x136E, emitter, 0, 0x7F, 0);
        case 0xC:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x136F, emitter, 0, 0x7F, 0);
        case 0xD:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1370, emitter, 0, 0x7F, 0);
        case 0xE:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1371, emitter, 0, 0x7F, 0);
        case 0xF:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1372, emitter, 0, 0x7F, 0);
        case 0x10:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1373, emitter, 0, 0x7F, 0);
        case 0x11:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1374, emitter, 0, 0x7F, 0);
        case 0x12:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1375, emitter, 0, 0x7F, 0);
        case 0x13:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1376, emitter, 0, 0x7F, 0);
        case 0x14:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1377, emitter, 0, 0x7F, 0);
        }

        break;
    case 5:
        switch (event)
        {
        case 0xA:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1378, emitter, 0, 0x7F, 0);
        case 0xB:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1379, emitter, 0, 0x7F, 0);
        case 0xC:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x137A, emitter, 0, 0x7F, 0);
        case 0xD:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x137B, emitter, 0, 0x7F, 0);
        case 0xE:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x137C, emitter, 0, 0x7F, 0);
        case 0xF:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x137D, emitter, 0, 0x7F, 0);
        case 0x10:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x137E, emitter, 0, 0x7F, 0);
        case 0x11:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x137F, emitter, 0, 0x7F, 0);
        case 0x12:
            D_001B6528[slot] = 1;
            return resident_sound_play_voice(g_sound, 0x1380, emitter, 0, 0x7F, 0);
        case 0x14:
            D_001B6528[slot] = 1;
            return resident_sound_play_voice(g_sound, 0x1381, emitter, 0, 0x7F, 0);
        case 0x16:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1382, emitter, 0, 0x7F, 0);
        case 0x13:
        case 0x15:
            D_001B6528[slot] = 0;
            return 0;
        }

        break;
    case 6:
        switch (event)
        {
        case 0xA:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1383, emitter, 0, 0x7F, 0);
        case 0xB:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1384, emitter, 0, 0x7F, 0);
        case 0xC:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1385, emitter, 0, 0x7F, 0);
        case 0xD:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1386, emitter, 0, 0x7F, 0);
        case 0xE:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1387, emitter, 0, 0x7F, 0);
        case 0xF:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1388, emitter, 0, 0x7F, 0);
        case 0x10:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1389, emitter, 0, 0x7F, 0);
        case 0x11:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x138A, emitter, 0, 0x7F, 0);
        case 0x12:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x138B, emitter, 0, 0x7F, 0);
        case 0x13:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x138C, emitter, 0, 0x7F, 0);
        case 0x14:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x138D, emitter, 0, 0x7F, 0);
        }

        break;
    case 7:
        switch (event)
        {
        case 0xA:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x138E, emitter, 0, 0x7F, 0);
        case 0xB:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x138F, emitter, 0, 0x7F, 0);
        case 0xC:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1390, emitter, 0, 0x7F, 0);
        case 0xD:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1391, emitter, 0, 0x7F, 0);
        case 0xE:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1392, emitter, 0, 0x7F, 0);
        case 0xF:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1393, emitter, 0, 0x7F, 0);
        case 0x10:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1394, emitter, 0, 0x7F, 0);
        case 0x11:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1395, emitter, 0, 0x7F, 0);
        case 0x12:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1396, emitter, 0, 0x7F, 0);
        case 0x13:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1397, emitter, 0, 0x7F, 0);
        case 0x14:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1398, emitter, 0, 0x7F, 0);
        }

        break;
    case 8:
        switch (event)
        {
        case 0xA:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x1399, emitter, 0, 0x7F, 0);
        case 0xB:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x139A, emitter, 0, 0x7F, 0);
        case 0xC:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x139B, emitter, 0, 0x7F, 0);
        case 0xD:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x139C, emitter, 0, 0x7F, 0);
        case 0xE:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x139D, emitter, 0, 0x7F, 0);
        case 0xF:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x139E, emitter, 0, 0x7F, 0);
        case 0x10:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x139F, emitter, 0, 0x7F, 0);
        case 0x11:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x13A0, emitter, 0, 0x7F, 0);
        case 0x12:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x13A1, emitter, 0, 0x7F, 0);
        case 0x13:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x13A2, emitter, 0, 0x7F, 0);
        case 0x14:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x13A3, emitter, 0, 0x7F, 0);
        }

        break;
    case 9:
        switch (event)
        {
        case 0xA:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x13A4, emitter, 0, 0x7F, 0);
        case 0xB:
            D_001B6528[slot] = 1;
            return resident_sound_play_voice(g_sound, 0x13A5, emitter, 0, 0x7F, 0);
        case 0xD:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x13A6, emitter, 0, 0x7F, 0);
        case 0xE:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x13A7, emitter, 0, 0x7F, 0);
        case 0xF:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x13A8, emitter, 0, 0x7F, 0);
        default:
            break;
        }

        break;
    case 10:
        switch (event)
        {
        case 0xA:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x13A9, emitter, 0, 0x7F, 0);
        case 0xB:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x13AA, emitter, 0, 0x7F, 0);
        case 0xC:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x13AB, emitter, 0, 0x7F, 0);
        case 0xD:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x13AC, emitter, 0, 0x7F, 0);
        case 0xE:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x13AD, emitter, 0, 0x7F, 0);
        case 0xF:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x13AE, emitter, 0, 0x7F, 0);
        case 0x10:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x13AF, emitter, 0, 0x7F, 0);
        case 0x11:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x13B0, emitter, 0, 0x7F, 0);
        case 0x12:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x13B1, emitter, 0, 0x7F, 0);
        case 0x13:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x13B2, emitter, 0, 0x7F, 0);
        case 0x14:
            D_001B6528[slot] = 0;
            return resident_sound_play_voice(g_sound, 0x13B3, emitter, 0, 0x7F, 0);
        }

        break;
    }

    return 0;
}

/**
 * @brief Play sound 9 of a sound bank slot following an emitter, unless banks are still loading.
 * @param emitter Object the sound follows.
 * @param slot Sound bank slot.
 * @return Slot identifier of the sound, or 0 without a sound bank set or while it loads.
 */
s32 func_00430AA0(ResidentSoundEmitter* emitter, s32 slot)
{
    if (D_001B6524 == 0)
    {
        return 0;
    }

    if (D_001B6524->loading != 0)
    {
        return 0;
    }

    return resident_sound_bank_set_play(D_001B6524, slot, 9, emitter, 0, 0x7F, 0);
}

/**
 * @brief Play a sound slot for a drop from one value to another, picked by how far it fell against a maximum.
 * @param emitter Object the sound follows.
 * @param bank Bank argument passed on to the sound bank set.
 * @param current Value after the drop.
 * @param previous Value before the drop; a rise plays nothing.
 * @param maximum Maximum the drop is measured against.
 * @return Slot identifier of the sound, or 0 when nothing plays.
 */
s32 func_00430B00(ResidentSoundEmitter* emitter, s32 bank, s32 current, s32 previous, s32 maximum)
{
    if (D_001B6524 == 0)
    {
        return 0;
    }

    if (D_001B6524->loading != 0)
    {
        return 0;
    }

    s32 drop = previous - current;

    if (drop < 0)
    {
        return 0;
    }

    if ((previous >= maximum >> 2 && drop < maximum >> 2) || (previous >= maximum >> 3 && drop < maximum >> 3))
    {
        return resident_sound_bank_set_play(D_001B6524, bank, 8, emitter, 0, 0x7F, 0);
    }

    if (current > maximum >> 4)
    {
        if (resident_rand() < 20000)
        {
            return resident_sound_bank_set_play(D_001B6524, bank, 7, emitter, 0, 0x7F, 0);
        }

        return resident_sound_bank_set_play(D_001B6524, bank, 6, emitter, 0, 0x7F, 0);
    }

    if (resident_rand() < 10000)
    {
        return resident_sound_bank_set_play(D_001B6524, bank, 6, emitter, 0, 0x7F, 0);
    }

    return resident_sound_bank_set_play(D_001B6524, bank, 5, emitter, 0, 0x7F, 0);
}

/**
 * @brief Play a sound slot by kind: kinds 0 and 1 pick one of two slots at random, any other kind slot 4.
 * @param emitter Object the sound follows.
 * @param bank Bank argument passed on to the sound bank set.
 * @param kind Sound kind.
 * @return Slot identifier of the sound, or 0 when nothing plays.
 */
s32 func_00430CA0(ResidentSoundEmitter* emitter, s32 bank, s32 kind)
{
    if (D_001B6524 == 0)
    {
        return 0;
    }

    if (D_001B6524->loading != 0)
    {
        return 0;
    }

    switch (kind)
    {
    case 0:
        if (resident_rand() < 0x2000)
        {
            return resident_sound_bank_set_play(D_001B6524, bank, 1, emitter, 0, 0x7F, 0);
        }

        return resident_sound_bank_set_play(D_001B6524, bank, 0, emitter, 0, 0x7F, 0);
    case 1:
        if (resident_rand() < 0x2000)
        {
            return resident_sound_bank_set_play(D_001B6524, bank, 3, emitter, 0, 0x7F, 0);
        }

        return resident_sound_bank_set_play(D_001B6524, bank, 2, emitter, 0, 0x7F, 0);
    default:
        return resident_sound_bank_set_play(D_001B6524, bank, 4, emitter, 0, 0x7F, 0);
    }
}

/** Half the camera's screen width, for the occluder upload. */
extern "C" float D_001B652C;

/** Half the camera's screen height, for the occluder upload. */
extern "C" float D_001B6530;

/** Camera near depth, for the occluder upload. */
extern "C" float D_001B6534;

/** Camera far depth, for the occluder upload. */
extern "C" float D_001B6538;

/**
 * @brief Collect up to 128 occluders, upload the ones in view to VU0 (nine qwords each from qword 8) and note the
 *        nearest one's depth.
 * @param list Occluder list.
 * @param camera Camera to test against.
 * @param matrix Depth-scaled view matrix.
 * @return Number of occluders uploaded.
 */
extern "C" s32 func_00430E00(LibClass178B30* list, LibCamera* camera, const LibMatrix44Value* matrix)
{
    s32 count = 0;
    LibOccluder** nodes = list->nodes;
    LibListSentinel* node = &list->sentinel;

    for (;;)
    {
        node = node->next;

        if (at_list_end(&list->sentinel, node))
        {
            break;
        }

        nodes[count++] = reinterpret_cast<LibOccluder*>(node);

        if (count >= 128)
        {
            return 0;
        }

        static_cast<LibTransformOwner*>(static_cast<LibListObject*>(node))->update_transform_matrix();
    }

    if (count == 0)
    {
        return 0;
    }

    LibVector4 position;
    position.x = camera->transform.m[0][3];
    position.y = camera->transform.m[1][3];
    position.z = camera->transform.m[2][3];
    position.w = 1.0f;
    float nearest = 1e30f;
    vu0_load_vf24_vf27(matrix);
    count = 0;
    float near;
    float far;
    float half_width = 0.5f * (camera->screen_max.x - camera->screen_min.x);
    float half_height = 0.5f * (camera->screen_max.y - camera->screen_min.y);
    far = camera->screen_max.z;
    near = camera->screen_min.z;
    D_001B6534 = near;
    D_001B6538 = far;
    D_001B652C = half_width;
    D_001B6530 = half_height;
    s32 slot = 8;
    s32 total = list->node_count;

    for (s32 i = 0; i < total; i++)
    {
        LibOccluder* occluder = nodes[i];

        if (func_00431090(occluder, &position, slot) && !(occluder->depth < camera->screen_min.z))
        {
            slot += 9;
            nodes[count++] = occluder;

            if (occluder->depth < nearest)
            {
                nearest = occluder->depth;
            }
        }

        if (count >= 26)
        {
            break;
        }
    }

    if (count == 0)
    {
        return 0;
    }

    list->nearest_depth = nearest;
    return count;
}

/**
 * @brief Work out the four corners of the rectangle from its half extents, in the xz plane at y zero.
 * @param object Rectangle; the corners' w is left alone.
 */
extern "C" void func_00431020(LibOccluder* object)
{
    object->corners[0].x = -object->half_width;
    object->corners[0].y = 0.0f;
    object->corners[0].z = -object->half_depth;
    object->corners[1].x = object->half_width;
    object->corners[1].y = 0.0f;
    object->corners[1].z = -object->half_depth;
    object->corners[2].x = object->half_width;
    object->corners[2].y = 0.0f;
    object->corners[2].z = object->half_depth;
    object->corners[3].x = -object->half_width;
    object->corners[3].y = 0.0f;
    object->corners[3].z = object->half_depth;
}

/**
 * @brief Add a projected corner's outcode bits: 1/2 right/left of the half width, 4/8 below/above the half height,
 *        0x10/0x20 nearer/farther than the depth range.
 * @param point Projected corner.
 * @param code Outcode to add to.
 */
static inline void occluder_outcode(const LibVector4* point, s32& code)
{
    if (!(point->x <= D_001B652C))
    {
        code |= 1;
    }
    else if (point->x < -D_001B652C)
    {
        code |= 2;
    }

    if (!(point->y <= D_001B6530))
    {
        code |= 4;
    }
    else if (point->y < -D_001B6530)
    {
        code |= 8;
    }

    if (point->z < D_001B6534)
    {
        code |= 0x10;
    }
    else if (!(point->z <= D_001B6538))
    {
        code |= 0x20;
    }
}

/**
 * @brief Upload an occluder's corners and edge normals to VU0 and tell whether it can hide anything.
 * @param occluder Occluder.
 * @param position Viewer position.
 * @param slot VU0 data slot (quadword) the corners and normals go to.
 * @return Zero when the occluder faces away (one-sided) or all four corners are off the same side of the view, else one.
 */
extern "C" s32 func_00431090(LibOccluder* occluder, const LibVector4* position, s32 slot)
{
    LibVector4 points[5];
    vu0_occluder_load_matrix(reinterpret_cast<u8*>(occluder) + 0x90, slot);
    vu0_occluder_build_faces(occluder->corners, position);
    vu0_occluder_store_first_corners(points);
    vu0_occluder_store_last_corners(points);
    float depth = 1e30f;
    depth = ee_min(points[0].z, depth);
    depth = ee_min(points[1].z, depth);
    depth = ee_min(points[2].z, depth);
    vu0_occluder_normalize_fourth();
    depth = ee_min(points[3].z, depth);
    occluder->depth = depth;
    vu0_occluder_normalize_fifth();

    if (!(points[4].z <= 0.0f))
    {
        vu0_occluder_flip_normals();

        if (occluder->unk21c)
        {
            return 0;
        }
    }

    vu0_occluder_store_normals();
    s32 first = 0;
    s32 second = 0;
    s32 third = 0;
    s32 fourth = 0;
    vu0_occluder_project_first(points);
    occluder_outcode(points, first);

    if (first == 0)
    {
        return 1;
    }

    vu0_occluder_project_second(points);
    occluder_outcode(points, second);

    if (second == 0)
    {
        return 1;
    }

    vu0_occluder_project_third(points);
    occluder_outcode(points, third);

    if (third == 0)
    {
        return 1;
    }

    vu0_occluder_project_fourth(points);
    occluder_outcode(points, fourth);

    if (fourth == 0)
    {
        return 1;
    }

    if (first & second & third & fourth)
    {
        return 0;
    }

    return 1;
}

/** @brief Construct the transform. */
LibClass1734D0::LibClass1734D0()
{
    set_type_id(0x1100);
}

/**
 * @brief Virtual slot 0x1C, first after LibListObject's.
 * @return Always four.
 */
s32 LibMemoryCard::func_slot1C()
{
    return 4;
}

/**
 * @brief Set unk54 and every unk2c entry to -1.
 * @param card Memory card object.
 */
void func_00431730(LibMemoryCard* card)
{
    card->unk54 = -1;

    for (s32 i = 0; i < 10; i++)
    {
        card->unk2c[i] = -1;
    }
}

/**
 * @brief Read an unk2c entry.
 * @param card Memory card object.
 * @param index Entry index; the check lets 10 through, which reads unk54.
 * @return The entry, or -1 when the index is out of range.
 */
s32 func_00431770(LibMemoryCard* card, s32 index)
{
    if (index < 0)
    {
        return -1;
    }

    if (index > 10)
    {
        return -1;
    }

    return card->unk2c[index];
}

/**
 * @brief Store a value from 0 to 10 in unk54.
 * @param card Memory card object.
 * @param value Value to store.
 * @return 1 once stored, 0 when the value is out of range.
 */
s32 func_004317B0(LibMemoryCard* card, s32 value)
{
    if (value < 0)
    {
        return 0;
    }

    if (value > 10)
    {
        return 0;
    }

    card->unk54 = value;
    return 1;
}

/** Separator between a card directory and a file name. */
extern "C" char D_00505930[];

/**
 * @brief Move a slot to its next step when its card command succeeded, or to status 0x10 when it failed.
 * @param record Slot record.
 */
static inline void lib_card_step(LibMemoryCardSlot* record)
{
    if (record->result >= 0)
    {
        record->status++;
    }
    else
    {
        record->status = 0x10;
    }
}

/**
 * @brief Advance a slot's file read: open, seek, read, close, then the next file of the request.
 * @param card Memory card object; a pending result index (unk54) receives the read size.
 * @param record Slot record to advance.
 */
extern "C" void func_004317F0(LibMemoryCard* card, LibMemoryCardSlot* record)
{
    LibCardFileBuffer* file = &record->request->files[record->unk44];
    s32 config = record->config;
    s32 slot = config & 0xF;

    switch (record->status & 0xF)
    {
    case 0:
        memset_guess(record->name, 0, sizeof(record->name));
        strcpy_guess(record->name, record->request->directory);
        strcat(record->name, D_00505930);
        strcat(record->name, file->name);
        record->result = sceMcOpen(config >> 4, slot, record->name, 1);
        lib_card_step(record);
        break;
    case 1:
        if (sceMcSync(1, 0, &record->result))
        {
            if (record->result >= 0)
            {
                record->fd = record->result;
                record->result = sceMcSeek(record->fd, file->offset, 0);
            }

            lib_card_step(record);
        }

        break;
    case 2:
        if (sceMcSync(1, 0, &record->result))
        {
            if (record->result >= 0)
            {
                record->result = sceMcRead(record->fd, file->data, file->size);
            }

            lib_card_step(record);
        }

        break;
    case 3:
        if (sceMcSync(1, 0, &record->result))
        {
            if (record->result >= 0)
            {
                if (card->unk54 > 0)
                {
                    card->unk2c[card->unk54] = record->result;
                    card->unk54 = 0;
                }

                record->result = sceMcClose(record->fd);
            }

            lib_card_step(record);
        }

        break;
    case 4:
        if (sceMcSync(1, 0, &record->result))
        {
            if (record->unk44 == record->request->file_count - 1)
            {
                record->status = 0x18;
            }
            else
            {
                record->unk44++;
                record->status = 0x30;
            }
        }

        break;
    }
}

/**
 * @brief Advance a slot's file write: enter (or make) the request's directory, then open, seek, write, close each
 *        file; a file without data only has its size reserved by seeking.
 * @param card Memory card object; unk24 is the open mode, unk28 is set when the request finishes.
 * @param record Slot record to advance.
 */
extern "C" void func_00431AB0(LibMemoryCard* card, LibMemoryCardSlot* record)
{
    LibCardFileBuffer* file = &record->request->files[record->unk44];
    s32 config = record->config;
    s32 slot = config & 0xF;

    switch (record->status & 0xF)
    {
    case 0:
        if (sceMcChdir(config >> 4, slot, record->request->directory, 0) == 0)
        {
            record->status++;
        }

        break;
    case 1:
        if (sceMcSync(1, 0, &record->result))
        {
            if (record->result >= 0)
            {
                record->result = sceMcChdir(config >> 4, slot, D_00505930, 0);
            }
            else if (record->result == -4)
            {
                record->result = sceMcMkdir(config >> 4, slot, record->request->directory);
            }

            lib_card_step(record);
        }

        break;
    case 2:
        if (sceMcSync(1, 0, &record->result))
        {
            if (record->result >= 0)
            {
                memset_guess(record->name, 0, sizeof(record->name));
                strcpy_guess(record->name, record->request->directory);
                strcat(record->name, D_00505930);
                strcat(record->name, file->name);
                record->result = sceMcOpen(config >> 4, slot, record->name, card->unk24);
            }

            lib_card_step(record);
        }

        break;
    case 3:
        if (sceMcSync(1, 0, &record->result))
        {
            if (record->result >= 0)
            {
                record->fd = record->result;
                record->result = sceMcSeek(record->result, file->offset, 0);
            }

            lib_card_step(record);
        }

        break;
    case 4:
        if (sceMcSync(1, 0, &record->result))
        {
            if (record->result >= 0)
            {
                if (file->data == 0)
                {
                    record->result = sceMcSeek(record->fd, file->size, 0);
                }
                else
                {
                    record->result = sceMcWrite(record->fd, file->data, file->size);
                }
            }

            lib_card_step(record);
        }

        break;
    case 5:
        if (sceMcSync(1, 0, &record->result))
        {
            if (record->result >= 0)
            {
                record->result = sceMcClose(record->fd);
            }

            lib_card_step(record);
        }

        break;
    case 6:
        if (sceMcSync(1, 0, &record->result))
        {
            if (record->unk44 == record->request->file_count - 1)
            {
                record->status = 0x18;
                card->unk28 = 1;
            }
            else
            {
                record->unk44++;
                record->status = 0x42;
            }
        }

        break;
    }
}

/**
 * @brief Advance a slot's file read.
 * @param card Memory card object.
 * @param record Slot record to advance.
 */
extern "C" void func_004317F0(LibMemoryCard* card, LibMemoryCardSlot* record);

/**
 * @brief Advance a slot's card check.
 * @param card Memory card object.
 * @param record Slot record to advance.
 */
extern "C" void func_00432090(LibMemoryCard* card, LibMemoryCardSlot* record);

/** @brief Advance the current slot's command; a card command that fails to start sets the slot's status to 0x18. */
void LibMemoryCard::update()
{
    LibMemoryCardSlot* record = &slots[unk1e];
    s32 slot = record->config & 0xF;

    switch (record->status & ~0xF)
    {
    case 0x10:
        func_00432090(this, record);
        break;
    case 0x20:
        if (sceMcFormat(record->config >> 4, slot) == 0)
        {
            record->status = 0x18;
        }

        break;
    case 0x30:
        func_004317F0(this, record);
        break;
    case 0x40:
        func_00431AB0(this, record);
        break;
    case 0x60:
        if (sceMcGetDir(record->config >> 4, slot, record->name, record->unk7C, record->unk78,
                        reinterpret_cast<void*>((reinterpret_cast<u32>(record->buffer) + 0x3F) & ~0x3F)) == 0)
        {
            record->status = 0x18;
        }

        break;
    case 0xC0:
        if (sceMcSetFileInfo(record->config >> 4, slot, record->name, record->buffer, record->unk78) == 0)
        {
            record->status = 0x18;
        }

        break;
    }
}

/**
 * @brief Find a slot that can start a file operation: the card library is set up, the slot is open, its card is
 *        ready and its last operation finished.
 * @param card Memory card object.
 * @param slot Slot index.
 * @return The slot's record, or null.
 */
static inline LibMemoryCardSlot* lib_memory_card_idle_slot(LibMemoryCard* card, u32 slot)
{
    LibMemoryCardSlot* record;

    if (!card->initialized || slot >= LIB_MEMORY_CARD_SLOT_COUNT)
    {
        return 0;
    }

    record = &card->slots[slot];

    if (record->card_state != LIB_MEMORY_CARD_STATE_READY)
    {
        return 0;
    }

    if ((record->status & LIB_MEMORY_CARD_STATUS_GROUP_MASK) != LIB_MEMORY_CARD_STATUS_DONE)
    {
        return 0;
    }

    if (!(record->state_flags & LIB_MEMORY_CARD_SLOT_OPEN))
    {
        return 0;
    }

    return record;
}

/**
 * @brief Start an operation: an idle slot takes it as its status, a running one queues it in the busy byte.
 * @param record Slot record.
 * @param operation Operation code.
 */
static inline void lib_memory_card_start_operation(LibMemoryCardSlot* record, u8 operation)
{
    if (record->status == LIB_MEMORY_CARD_STATUS_DONE)
    {
        record->status = operation;
    }
    else
    {
        record->busy = operation;
    }
}

/**
 * @brief Start looking for a file on the card in a slot.
 * @param card Memory card object.
 * @param slot Slot index.
 * @param name File to look for.
 * @param unk7C Stored in the slot at 0x7C.
 * @param unk78 Stored in the slot at 0x78.
 * @param buffer Buffer the probe reads into; it is aligned to 64 bytes first.
 * @return 0 once started, -1 when the slot can't start an operation.
 */
s32 lib_memory_card_probe_file(LibMemoryCard* card, u32 slot, const char* name, s32 unk7C, s32 unk78, u8* buffer)
{
    LibMemoryCardSlot* record = lib_memory_card_idle_slot(card, slot);

    if (!record)
    {
        return -1;
    }

    lib_memory_card_start_operation(record, LIB_MEMORY_CARD_OP_PROBE_FILE);
    record->result = 0;
    record->buffer = reinterpret_cast<u8*>((reinterpret_cast<u32>(buffer) + 63) & ~63);
    record->unk78 = unk78;
    record->unk7C = unk7C;
    strncpy_guess(record->name, name, sizeof(record->name));
    return 0;
}

/**
 * @brief Advance a slot's card check: start reading the card info, wait for it, or wait for the running command.
 * @param card Memory card object.
 * @param record Slot record to advance.
 */
void func_00432090(LibMemoryCard* card, LibMemoryCardSlot* record)
{
    s32 result = -1;
    s32 config = record->config;
    s32 port = config & 0xF;

    switch (record->status & 0xF)
    {
        case 0:
            if (!(record->state_flags & 1))
            {
                if (!(record->state_flags & 4))
                {
                    if (sceMcGetInfo(config >> 4, port, &record->card_state, &record->free_space, &record->formatted) == 0)
                    {
                        record->status++;
                    }
                }
                else if (sceMcGetInfo(config >> 4, port, &record->card_state, 0, 0) == 0)
                {
                    record->status++;
                }
            }
            else
            {
                memset_guess(record, 0, sizeof(LibMemoryCardSlot));
            }

            break;

        case 1:
            if (sceMcSync(1, 0, &result))
            {
                if (result == 0)
                {
                    record->state_flags |= 4;
                }
                else
                {
                    record->state_flags &= ~4;
                }

                if (!record->busy)
                {
                    record->status--;
                }
                else
                {
                    record->status = record->busy;
                    record->busy = 0;
                }

                if (card->unk1e == 1 && !card->ready)
                {
                    card->ready = 1;
                }

                card->unk1e++;

                if (card->unk1e >= 2)
                {
                    card->unk1e = 0;
                }
            }

            break;

        case 8:
            if (sceMcSync(1, 0, &record->result))
            {
                record->state_flags &= ~4;
                record->status = LIB_MEMORY_CARD_STATUS_DONE;
            }

            break;
    }
}

/**
 * @brief Read the result of a slot's last operation.
 * @param card Memory card object.
 * @param slot Slot index.
 * @param result Receives the result when one is ready; cleared first. May be null.
 * @return 1 with a result, 0 while the slot is busy or its status has no result, -1 when the card library isn't set
 *         up or the slot doesn't exist.
 */
s32 lib_memory_card_get_result(LibMemoryCard* card, s32 slot, s32* result)
{
    if (result)
    {
        *result = 0;
    }

    if (!card->initialized || slot >= LIB_MEMORY_CARD_SLOT_COUNT)
    {
        return -1;
    }

    if (card->slots[slot].busy)
    {
        return 0;
    }

    u8 status = card->slots[slot].status;

    if (status != 0 && (status & LIB_MEMORY_CARD_STATUS_GROUP_MASK) != LIB_MEMORY_CARD_STATUS_DONE)
    {
        return 0;
    }

    if (result)
    {
        *result = card->slots[slot].result;
    }

    return 1;
}

/**
 * @brief Start a file transfer on the card in a slot.
 * @param card Memory card object.
 * @param slot Slot index.
 * @param request Files to transfer; the slot keeps the pointer until it finishes.
 * @return 0 once started, -1 when the slot can't start an operation.
 */
s32 lib_memory_card_start_transfer(LibMemoryCard* card, u32 slot, LibCardFileRequest* request)
{
    LibMemoryCardSlot* record = lib_memory_card_idle_slot(card, slot);

    if (!record)
    {
        return -1;
    }

    lib_memory_card_start_operation(record, LIB_MEMORY_CARD_OP_TRANSFER);
    record->result = 0;
    record->unk44 = 0;
    record->request = request;
    return 0;
}

/**
 * @brief Start operation 0xC0 on the card in a slot for a named file.
 * @param card Memory card object.
 * @param slot Slot index.
 * @param name File name, copied into the slot.
 * @param unk78 Stored in the slot at 0x78.
 * @param buffer Stored as the slot's buffer, without aligning it.
 * @return 0 once started, -1 when the slot can't start an operation.
 */
s32 func_004323E0(LibMemoryCard* card, u32 slot, const char* name, s32 unk78, u8* buffer)
{
    LibMemoryCardSlot* record = lib_memory_card_idle_slot(card, slot);

    if (!record)
    {
        return -1;
    }

    lib_memory_card_start_operation(record, LIB_MEMORY_CARD_OP_C0);
    record->result = 0;
    record->buffer = buffer;
    record->unk78 = unk78;
    strncpy_guess(record->name, name, sizeof(record->name));
    return 0;
}

/**
 * @brief Start operation 0x40 on the card in a slot for a file request.
 * @param card Memory card object.
 * @param slot Slot index.
 * @param request Files to work on; the slot keeps the pointer until it finishes.
 * @return 0 once started, -1 when the slot can't start an operation.
 */
s32 func_004324D0(LibMemoryCard* card, u32 slot, LibCardFileRequest* request)
{
    LibMemoryCardSlot* record = lib_memory_card_idle_slot(card, slot);

    if (!record)
    {
        return -1;
    }

    lib_memory_card_start_operation(record, LIB_MEMORY_CARD_OP_40);
    record->result = 0;
    record->unk44 = 0;
    record->request = request;
    return 0;
}

/**
 * @brief Start operation 0x20 on the card in a slot.
 * @param card Memory card object.
 * @param slot Slot index.
 * @return 0 once started, -1 when the slot can't start an operation.
 */
s32 func_004325A0(LibMemoryCard* card, u32 slot)
{
    LibMemoryCardSlot* record = lib_memory_card_idle_slot(card, slot);

    if (!record)
    {
        return -1;
    }

    lib_memory_card_start_operation(record, LIB_MEMORY_CARD_OP_20);
    record->result = 0;
    return 0;
}

/**
 * @brief Open a slot that isn't running anything: clear its record and mark it open.
 * @param card Memory card object.
 * @param slot Slot index.
 * @param enabled Low bit goes to bit 4 of the slot's config.
 * @param flags Low two bits go to bits 0-1 of the slot's config.
 */
void lib_memory_card_open_slot(LibMemoryCard* card, s32 slot, u32 enabled, u32 flags)
{
    LibMemoryCardSlot* record;

    if (!card->initialized || slot < 0 || slot >= LIB_MEMORY_CARD_SLOT_COUNT)
    {
        return;
    }

    record = &card->slots[slot];

    if (record->status)
    {
        return;
    }

    memset_guess(record, 0, sizeof(LibMemoryCardSlot));
    record->config = ((enabled & 1) << 4) | (flags & 3);
    record->status = LIB_MEMORY_CARD_STATUS_DONE;
    record->state_flags = LIB_MEMORY_CARD_SLOT_OPEN;
}

/** Store the word at receiver offset 0x24. */
void func_00432710(void* object, u32 value)
{
    WordSetterOwnertext_00429B00* receiver = (WordSetterOwnertext_00429B00*)object;
    receiver->unk24 = value;
}

/** Static storage the card's slot records are carved from: both records plus room to align them. */
extern "C" u8 lib_memory_card_slot_storage[];

/**
 * @brief Set up the card library and the slot records, then add the card to an update list.
 * @param card Memory card object.
 * @param list List to add the card to, or null.
 * @return 1 once set up, 0 when it already was or the card library failed to start.
 */
s32 lib_memory_card_init(LibMemoryCard* card, LibUpdateList* list)
{
    if (card->initialized || sceMcInit() != 0)
    {
        return 0;
    }

    card->slot_storage = lib_memory_card_slot_storage;

    if (!card->slot_storage)
    {
        return 0;
    }

    memset_guess(card->slot_storage, 0, LIB_MEMORY_CARD_SLOT_COUNT * sizeof(LibMemoryCardSlot) + 64);
    card->slots = reinterpret_cast<LibMemoryCardSlot*>((reinterpret_cast<u32>(card->slot_storage) + 63) & ~63);
    card->initialized = 1;
    card->unk1e = 0;

    if (list)
    {
        list->append_node(card, -1);
    }

    return 1;
}

/** @brief Wait for the card command in progress, then detach and queue the object once the library is set up. */
void LibMemoryCard::destroy()
{
    s32 command;
    s32 result;

    if (!sceMcSync(1, &command, &result))
    {
        sceMcSync(0, &command, &result);
    }

    if (initialized)
    {
        lib_object_detach_owner(this);
        resident_enqueue_object(g_resident_release_queues, this);
    }
}

/** @brief Destroy the memory card object. */
LibMemoryCard::~LibMemoryCard()
{
}

/** @brief Initialize the memory card object. */
LibMemoryCard::LibMemoryCard()
{
    slots = 0;
    slot_storage = 0;
    initialized = 0;
    unk1e = 0;
    ready = 0;
    unk24 = 0x202;
    unk28 = 0;
    unk54 = -1;

    for (s32 i = 0; i < 10; i++)
    {
        unk2c[i] = -1;
    }
}

/** @brief Delete the semaphore, then the thread. */
LibClass173580::~LibClass173580()
{
}

/** @brief Mark the packet being stored as done and finish the capture. */
void LibImageCapture::on_store_complete()
{
    stored[storing] = 1;
    lib_finish_packet(this);
}

extern "C" const char D_00505960[];
extern "C" const char D_00505990[];
extern "C" unsigned __int128 D_004ED120;

/**
 * @brief Turn a pointer into a DMA source or destination: the physical address, with the scratchpad flag for
 *        scratchpad memory.
 * @param address Pointer.
 * @return DMA address.
 */
static inline void lib_dma_set_address(volatile u32* madr, const void* address)
{
    if (((u32)address & EE_SCRATCHPAD) == EE_SCRATCHPAD)
    {
        *madr = ((u32)address & 0x0FFFFFFF) | DMA_ADDRESS_SCRATCHPAD;
    }
    else
    {
        *madr = (u32)address & 0x0FFFFFFF;
    }
}

/**
 * @brief Thread body: store each packet a capture hands over, then finish the capture.
 *
 * The store is Sony's sceGsExecStoreImage with the DMA waits on the thread's semaphore: the packet goes to the GS
 * over VIF1, the rectangle comes back through the VIF1 FIFO, whole blocks of eight quadwords by DMA and the rest
 * read by hand.
 */
void LibClass173580::run()
{
    for (;;)
    {
        if (wake_failed)
        {
            wake_failed = 0;
        }
        else
        {
            resident_thread_sleep();
        }

        u32 timeout = 0;
        s32 blocks = 0;
        s32 drain = 0;
        s32 rest = 0;
        s32 rest_bytes = 0;
        GsStoreImage* image = packet;
        s32 format = image->bitbltbuf.source_format;
        s32 width = image->trxreg.width;
        s32 height = image->trxreg.height;
        s32 rounded_height = 0;
        s32 bytes;
        s32 quadwords;
        s32 i;
        unsigned __int128 last;

        switch (format)
        {
            case GS_PSMCT32:
            case GS_PSMZ32:
                bytes = width * height * 4;
                rest_bytes = bytes & 0xF;
                quadwords = bytes >> 4;
                blocks = quadwords & ~7;
                rest = quadwords & 7;

                if (rest_bytes == 0)
                {
                    rounded_height = height;
                    drain = 0;
                }
                else
                {
                    rounded_height = (height + 3) & ~3;
                    drain = (width * rounded_height >> 2) - blocks - rest - 1;
                }

                break;
            case GS_PSMCT24:
            case GS_PSMZ24:
                bytes = width * height * 3;
                rest_bytes = bytes & 0xF;
                quadwords = bytes >> 4;
                blocks = quadwords & ~7;
                rest = quadwords & 7;

                if (rest_bytes == 0)
                {
                    rounded_height = height;
                    drain = 0;
                }
                else
                {
                    rounded_height = (height + 15) & ~15;
                    drain = (width * rounded_height * 3 >> 4) - blocks - rest - 1;
                }

                break;
            case GS_PSMCT16:
            case GS_PSMCT16S:
            case GS_PSMZ16:
            case GS_PSMZ16S:
                bytes = width * height * 2;
                rest_bytes = bytes & 0xF;
                quadwords = bytes >> 4;
                rest = quadwords & 7;
                blocks = quadwords & ~7;

                if (rest_bytes == 0)
                {
                    rounded_height = height;
                    drain = 0;
                }
                else
                {
                    rounded_height = (height + 7) & ~7;
                    drain = (width * rounded_height >> 3) - blocks - rest - 1;
                }

                break;
            case GS_PSMT8:
            case GS_PSMT8H:
                bytes = width * height;
                rest_bytes = bytes & 0xF;
                quadwords = bytes >> 4;
                rest = quadwords & 7;
                blocks = quadwords & ~7;

                if (rest_bytes == 0)
                {
                    rounded_height = height;
                    drain = 0;
                }
                else
                {
                    rounded_height = (height + 7) & ~7;
                    drain = (width * rounded_height >> 4) - blocks - rest - 1;
                }

                break;
            case GS_PSMT4:
            case GS_PSMT4HL:
            case GS_PSMT4HH:
                bytes = width * height >> 1;
                rest_bytes = bytes & 0xF;
                quadwords = bytes >> 4;
                rest = quadwords & 7;
                blocks = quadwords & ~7;

                if (rest_bytes == 0)
                {
                    rounded_height = height;
                    drain = 0;
                }
                else
                {
                    rounded_height = (height + 7) & ~7;
                    drain = (width * rounded_height >> 5) - blocks - rest - 1;
                }

                break;
        }

        if (rest_bytes != 0)
        {
            *reinterpret_cast<u64*>(reinterpret_cast<u32>(&packet->trxreg) | UNCACHED_SEGMENT) =
                (u64)(u16)width | ((u64)rounded_height << 32);
        }

        u64 mask = GsPutIMR(GsGetIMR() | 0x200);
        GS_CSR = GS_CSR_FINISH;
        *D1_QWC = 7;
        lib_dma_set_address(D1_MADR, packet);
        *D1_CHCR = DMA_CHCR_START | DMA_CHCR_DIR_FROM_MEMORY;
        semaphore.wait();

        while ((GS_CSR & GS_CSR_FINISH) == 0)
        {
            if (timeout++ > 0x1000000)
            {
                scePrintf(D_00505960);
                VIF1_FIFO = D_004ED120;
                goto done;
            }
        }

        VIF1_STAT = VIF1_STAT_FDR;
        GS_BUSDIR = GS_BUSDIR_LOCAL_TO_HOST;

        if (blocks != 0)
        {
            DmaSubmission* submission = capture;
            ResidentDmaQueue* queue = g_vif1_dma_queue;
            queue->current = submission;
            queue->busy = 1;
            *D1_QWC = blocks;
            lib_dma_set_address(D1_MADR, destination);
            *D1_CHCR = DMA_CHCR_START;
            semaphore.wait();
        }

        for (i = 0; i < rest; i++)
        {
            while ((VIF1_STAT & VIF1_STAT_FQC) == 0)
            {
                if (timeout++ > 0x1000000)
                {
                    scePrintf(D_00505990);
                    GS_CSR = GS_CSR_RESET;
                    GS_BUSDIR = 0;
                    GIF_CTRL = GIF_CTRL_RESET;
                    VIF1_FBRST = VIF1_FBRST_RESET;
                    goto done;
                }
            }

            static_cast<unsigned __int128*>(destination)[blocks + i] = VIF1_FIFO;
        }

        if (rest_bytes != 0)
        {
            while ((VIF1_STAT & VIF1_STAT_FQC) == 0)
            {
                if (timeout++ > 0x1000000)
                {
                    scePrintf(D_00505990);
                    GS_CSR = GS_CSR_RESET;
                    GS_BUSDIR = 0;
                    GIF_CTRL = GIF_CTRL_RESET;
                    VIF1_FBRST = VIF1_FBRST_RESET;
                    goto done;
                }
            }

            last = VIF1_FIFO;

            for (i = 0; i < rest_bytes; i++)
            {
                reinterpret_cast<u8*>(static_cast<unsigned __int128*>(destination) + (blocks + rest))[i] =
                    reinterpret_cast<u8*>(&last)[i];
            }

            for (i = 0; i < drain; i++)
            {
                while ((VIF1_STAT & VIF1_STAT_FQC) == 0)
                {
                    if (timeout++ > 0x1000000)
                    {
                        scePrintf(D_00505990);
                        GS_CSR = GS_CSR_RESET;
                        GS_BUSDIR = 0;
                        GIF_CTRL = GIF_CTRL_RESET;
                        VIF1_FBRST = VIF1_FBRST_RESET;
                        goto done;
                    }
                }

                last = VIF1_FIFO;
            }
        }

        VIF1_STAT = 0;
        GS_BUSDIR = 0;
        GsPutIMR(mask);
        GS_CSR = GS_CSR_FINISH;
        VIF1_FIFO = D_004ED120;

    done:
        resident_sync_gs_path(g_input_system, 0, 0);
        capture->on_store_complete();
        resident_dma_queue_resume(g_vif1_dma_queue);

        if (capture->unk65 == 1)
        {
            func_004DC420(g_packet_queue, 1);
        }
    }
}

/**
 * @brief Let the store thread know the store packet's transfer is over.
 * @param channel DMA channel number.
 */
void LibImageCapture::complete_dma(u32 channel)
{
    resident_dma_queue_pause(g_vif1_dma_queue);
    iSignalSema(D_005081D0.semaphore.id);
}

/**
 * @brief Hand the packet being stored to the store thread and wake it.
 * @param channel DMA channel number.
 */
void LibImageCapture::submit_dma(u32 channel)
{
    dma_pending = 1;
    u8 index = storing;
    void* destination = destinations[index];
    D_005081D0.packet = reinterpret_cast<GsStoreImage*>(reinterpret_cast<u32>(&packets[index]) | UNCACHED_SEGMENT);
    D_005081D0.destination = destination;
    D_005081D0.capture = this;

    if (!resident_thread_wakeup(&D_005081D0))
    {
        D_005081D0.wake_failed = 1;
    }
}

/**
 * @brief Packet-queue handler for a capture that render handed over: let queued packets start, then queue the
 *        capture's DMA.
 * @param capture Capture object.
 */
void func_004332F0(LibImageCapture* capture)
{
    func_004DC420(g_packet_queue, 0);
    resident_dma_queue_push(g_vif1_dma_queue, capture);
}

/** @brief Queue the capture's DMA, or hand it to the packet queue when unk65 is set. */
void LibImageCapture::render()
{
    if (!unk65)
    {
        resident_dma_queue_push(g_vif1_dma_queue, this);
    }
    else
    {
        func_004DC4F0(g_packet_queue, 6, 0, this, 0, 0);
    }
}

/**
 * @brief Queue a copy of a VRAM rectangle into memory, in the next of the capture's two store packets.
 * @param capture Capture object.
 * @param destination Memory the pixels are copied to.
 * @param base_pointer Source buffer address in 64-word blocks.
 * @param buffer_width Source buffer width in 64-pixel units.
 * @param pixel_format Source pixel format.
 * @param x Left edge of the rectangle.
 * @param y Top edge of the rectangle.
 * @param width Rectangle width.
 * @param height Rectangle height.
 */
void lib_image_capture_store(LibImageCapture* capture, void* destination, s16 base_pointer, s16 buffer_width,
                             s16 pixel_format, s16 x, s16 y, s16 width, s16 height)
{
    capture->current ^= 1;
    sceGsSetDefStoreImage(reinterpret_cast<GsStoreImage*>(reinterpret_cast<u32>(&capture->packets[capture->current]) | UNCACHED_SEGMENT),
                          base_pointer, buffer_width, pixel_format, x, y, width, height);
    capture->destinations[capture->current] = destination;
    capture->stored[capture->current] = 0;
    capture->pending = 1;
}

/**
 * @brief Pick the waiting packet to store, if there is one.
 * @param matrix Matrix supplied by the caller; unused.
 * @param context Opaque caller context; unused.
 */
void LibImageCapture::build_packet(const void* matrix, void* context)
{
    if (!pending)
    {
        unk63 = 0;
        return;
    }

    storing = current;
    unk63 = 1;
    pending = 0;
}

/** @brief Destroy the capture. */
LibImageCapture::~LibImageCapture()
{
}

/** @brief Construct the capture. */
LibImageCapture::LibImageCapture()
{
    set_type_id(0x1200);
    default_draw_bucket = 9;
    current = 0;
    pending = 0;
    unk65 = 0;
    set_draw_flags(draw_flags | LIB_DRAW_FLAG_0400);
    FlushCache(0);
}

/** @brief Use the capture's own draw bucket. */
void LibImageCapture::set_default_draw_bucket()
{
    draw_bucket = default_draw_bucket;
}

/** @brief Free the shared font (archive resources 8 and 9) and remove it from the entry table. */
void lib_release_shared_font(void)
{
    ResidentEntryTable* table = resident_get_entry_table(resident_get_system());
    void* font = (void*)resident_find_entry(table, LIB_ENTRY_SHARED_FONT);
    resident_remove_entry(table, LIB_ENTRY_SHARED_FONT);
    free_guess(font);
}

/**
 * @brief Multiply a vector by the 4x4 matrix whose rows are already loaded in vf1-vf4.
 * @param vector 16-byte aligned source vector.
 * @param result 16-byte aligned destination; may equal vector.
 */
void func_004336E0(const void* vector, void* result)
{
    vu0_load_vf15(vector);
    vu0_dot_rows_vf15(result);
}

/**
 * @brief Load a 4x4 matrix into vf1-vf4, then multiply a vector by it as func_004336E0 does.
 * @param matrix 16-byte aligned matrix of four rows.
 * @param vector 16-byte aligned source vector.
 * @param result 16-byte aligned destination.
 */
void func_00433730(const void* matrix, const void* vector, void* result)
{
    vu0_load_vf15(vector);
    vu0_load_matrix(matrix);
    vu0_dot_rows_vf15(result);
}

/**
 * @brief Free a C library allocation when there is one.
 * @param block Allocation, or null.
 */
static inline void lib_free_block(void* block)
{
    if (block)
    {
        free_guess(block);
    }
}

/**
 * @brief Allocate the largest block the C library heap can give, leaving room for a reserve.
 *
 * Halves in on the largest allocation size first. Room is also left after the block below 0x1EFD001; when the block
 * would end past that, it is allocated again 0x1400 bytes smaller.
 * @param reserve Bytes to leave free, besides 0x20.
 * @return The block, or null when the reserve doesn't fit.
 */
extern "C" void* func_00433790(s32 reserve)
{
    s32 step = 0x2000000;
    s32 size = step;

    do
    {
        void* block = malloc_guess(size);

        if (block == 0)
        {
            step /= 2;
            size -= step;
        }
        else
        {
            lib_free_block(block);
            step /= 2;
            size += step;
        }
    } while (step > 2);

    size -= reserve + 0x20;

    if (size < 0)
    {
        return 0;
    }

    void* block = malloc_guess(size);

    if ((u32)(reserve + ((u32)block + size)) > 0x1EFD000)
    {
        lib_free_block(block);
        block = malloc_guess(size - 0x1400);
    }

    return block;
}

/**
 * @brief Allocate an aligned buffer: take as many aligned blocks as fit, keep the highest one and free the rest.
 * @param size Requested buffer size in bytes.
 * @param alignment Buffer alignment in bytes.
 * @return The buffer, or null when allocation fails.
 */
void* func_00433880(u32 size, u32 alignment)
{
    void* blocks[0x400];

    blocks[0] = func_00433790(size + alignment * 2);

    if (blocks[0] == 0)
    {
        return 0;
    }

    s32 count = 1;
    s32 i = count;

    for (; count < 0x400; count++)
    {
        blocks[count] = memalign(alignment, size);

        if (blocks[count] == 0)
        {
            break;
        }
    }

    u32 highest = 0;
    s32 best = -1;

    for (; i < count; i++)
    {
        if (highest < (u32)blocks[i])
        {
            highest = (u32)blocks[i];
            best = i;
        }
    }

    void* result = 0;

    if (best != -1)
    {
        result = blocks[best];
    }

    for (i = 0; i < count; i++)
    {
        if (i != best)
        {
            lib_free_block(blocks[i]);
        }
    }

    blocks[0] = malloc_guess(0x1400);
    lib_free_block(blocks[0]);
    return result;
}

/**
 * @brief Find, to within a few bytes, the largest block the heap can hand out below 0x1FE0000.
 * @return Block size.
 */
extern "C" s32 func_004339F0(void)
{
    s32 step = 0x1000000;
    s32 size = step;

    do
    {
        void* block = malloc_guess(size);

        if (block == 0 || (u32)block >= 0x1FE0000)
        {
            if (block)
            {
                free_guess(block);
            }

            step /= 2;
            size -= step;
        }
        else
        {
            if (block)
            {
                free_guess(block);
            }

            step /= 2;
            size += step;
        }
    } while (step >= 3);

    return size;
}

/**
 * @brief Allocate blocks from the C library heap, halving the size whenever one fails, then free them all, the
 *        highest one last.
 */
void func_00433AA0(void)
{
    void* blocks[0x100];
    s32 count;
    s32 size = 0x2000000;

    for (count = 0; count < 0x100; count++)
    {
        blocks[count] = malloc_guess(size);

        if (blocks[count] == 0)
        {
            size /= 2;

            if (size < 4)
            {
                break;
            }
        }
    }

    s32 i;
    u32 highest = 0;
    s32 best;

    for (i = 0; i < count; i++)
    {
        if (highest < (u32)blocks[i])
        {
            highest = (u32)blocks[i];
            best = i;
        }
    }

    for (i = 0; i < count; i++)
    {
        if (i != best)
        {
            lib_free_block(blocks[i]);
        }
    }

    lib_free_block(blocks[best]);
}

void* func_00433BE0(u32 alignment, u32 size) { return memalign(alignment, size); }

/** @brief Destroy the light. */
LibClass173630::~LibClass173630()
{
}

/**
 * @brief Pick a random point in the light's box when the point is in front of the light and over its disc.
 * @param point Point being lit.
 * @param normal Unused.
 * @return The picked point (unk290), or zero when the point is behind the light or outside the disc.
 */
const LibVector4* LibClass173630::func_slot88(const LibVector4* point, const LibVector4* normal)
{
    LibVector4 measure;

    vu0_light_load_point(point, &view_position, &axis);
    vu0_disc_light_offset();
    *(unsigned __int128*)&unk290 = 0;
    vu0_disc_light_project(&measure);

    if (measure.x < 0.0f)
    {
        return &unk290;
    }

    vu0_disc_light_radial();
    float x = lib_light_random_fraction();
    vu0_disc_light_square();
    float y = lib_light_random_fraction();
    vu0_disc_light_sum();
    float z = lib_light_random_fraction();
    vu0_disc_light_subtract_radius();
    x *= unk270.x;
    y *= unk270.y;
    z *= unk270.z;
    vu0_disc_light_store_distance(&measure);

    if (!(measure.x <= 0.0f))
    {
        return &unk290;
    }

    unk290.x = unk280.x + (unk240.x + x);
    unk290.y = unk280.y + (unk240.y + y);
    unk290.z = unk280.z + (unk240.z + z);
    return &unk290;
}


/**
 * @brief Bring the position and both directions into the view's space.
 * @param matrix View matrix.
 * @param rotation View matrix with its rows normalised.
 */
void LibClass173630::func_slot84(const LibMatrix44Value* matrix, const LibMatrix44Value* rotation)
{
    LibVector4 direction;

    if (!matrix_ready)
    {
        update_transform_matrix();
    }

    LibMatrix44Value world(*get_transposed_transform(this));
    vu0_normalize_rows_xyz(&world);
    LibVector4 position;
    position.x = matrix_row(&transform, 0)->w;
    position.y = matrix_row(&transform, 1)->w;
    position.z = matrix_row(&transform, 2)->w;
    position.w = 1.0f;
    vu0_transform_emission_point(matrix, &position, &view_position);
    vu0_light_transform_direction(&world, &unk230, &direction);
    vu0_light_transform_direction(rotation, &direction, &unk240);
    vu0_light_transform_direction(&world, &unk260, &direction);
    vu0_light_transform_direction(rotation, &direction, &unk270);
    vu0_load_vf1(&unk240);
    unk280.x = 0.5f * unk270.x;
    unk280.y = 0.5f * unk270.y;
    unk280.z = 0.5f * unk270.z;
    vu0_light_start_normalize_vf1();
    view_position.w = radius * radius;
    vu0_light_store_normalized_vf1(&axis);
}

}

/**
 * @brief Work out the vector from a point to the light, falling off with distance.
 * @param point Point being lit.
 * @param normal Unused.
 * @return Light vector at unk220.
 */
const LibVector4* LibClass173750::func_slot88(const LibVector4* point, const LibVector4* normal)
{
    vu0_light_load_point(point, &view_position, &unk230);
    vu0_light_point_vector(&unk220);
    return &unk220;
}

/**
 * @brief Transform the light's position into the view's space.
 * @param matrix View matrix.
 * @param rotation Unused.
 */
void LibClass173750::func_slot84(const LibMatrix44Value* matrix, const LibMatrix44Value* rotation)
{
    LibVector4 position;

    if (!matrix_ready)
    {
        update_transform_matrix();
    }

    position.x = transform.m[0][3];
    position.y = transform.m[1][3];
    position.z = transform.m[2][3];
    position.w = 1.0f;
    vu0_transform_emission_point(matrix, &position, &view_position);
    unk230.w = 25.0f;
}

/**
 * @brief Scale a normal by the light's factors.
 * @param point Unused.
 * @param normal Normal at the point.
 * @return Light vector at unk220.
 */
const LibVector4* LibClass1737E0::func_slot88(const LibVector4* point, const LibVector4* normal)
{
    vu0_light_load_normal(normal, &unk230);
    vu0_light_scale_normal(&unk220);
    return &unk220;
}

extern "C" {

/**
 * @brief Pick a random point: unk260 plus unk230 plus a random fraction of axis, per component.
 * @param light Light whose unk270 receives the point.
 * @return The point (unk270).
 */
extern "C" LibVector4* func_00434330(LibClass173630* light)
{
    light->unk270.x = light->unk260.x + (light->unk230.x + light->axis.x * lib_light_random_fraction());
    light->unk270.y = light->unk260.y + (light->unk230.y + light->axis.y * lib_light_random_fraction());
    light->unk270.z = light->unk260.z + (light->unk230.z + light->axis.z * lib_light_random_fraction());
    return &light->unk270;
}

}

/**
 * @brief Turn both directions into the view's space and halve the second.
 * @param matrix Unused.
 * @param rotation View matrix with its rows normalised.
 */
void LibClass173870::func_slot84(const LibMatrix44Value* matrix, const LibMatrix44Value* rotation)
{
    LibVector4 direction;

    if (!matrix_ready)
    {
        update_transform_matrix();
    }

    LibMatrix44Value world(*get_transposed_transform(this));
    vu0_normalize_rows_xyz(&world);
    vu0_light_transform_direction(&world, &unk220, &direction);
    vu0_light_transform_direction(rotation, &direction, &unk230);
    vu0_light_transform_direction(&world, &unk240, &direction);
    vu0_light_transform_direction(rotation, &direction, &unk250);
    unk260.x = 0.5f * unk250.x;
    unk260.y = 0.5f * unk250.y;
    unk260.z = 0.5f * unk250.z;
}

/**
 * @brief Turn the direction into the view's space.
 * @param matrix Unused.
 * @param rotation View matrix with its rows normalised.
 */
void LibClass173900::func_slot84(const LibMatrix44Value* matrix, const LibMatrix44Value* rotation)
{
    LibVector4 direction;

    if (!matrix_ready)
    {
        update_transform_matrix();
    }

    LibMatrix44Value world(*get_transposed_transform(this));
    vu0_normalize_rows_xyz(&world);
    vu0_light_transform_direction(&world, &unk220, &direction);
    vu0_light_transform_direction(rotation, &direction, &unk230);
}

extern "C" {

/** Partial pointer list of lights; its data comes before the vptr. */
typedef struct LibLightPointerList
{
    s16 capacity;
    s16 count;
    LibClass1736C0** lights;
    u8 unk08[8];
    LibVector4 ambient;
    u8 has_positional;
} LibLightPointerList;

/**
 * @brief Add up the light vectors the list's switched-on lights give at a point.
 * @param list Lights.
 * @param point Point being lit.
 * @param normal Normal at the point.
 * @param result Receives the sum.
 */
void func_004348E0(LibLightPointerList* list, const LibVector4* point, const LibVector4* normal, LibVector4* result)
{
    clear_vector(result);
    s32 count = list->count;

    for (s32 i = 0; i < count; i++)
    {
        LibClass1736C0* light = list->lights[i];

        if (light->kind)
        {
            const LibVector4* vector = light->func_slot88(point, normal);
            result->x += vector->x;
            result->y += vector->y;
            result->z += vector->z;
        }
    }
}

/**
 * @brief Bring a transform's matrices up to date, put every light in the list into its space, and sum the lights of
 *        kind zero, which don't depend on the point, into the list's ambient vector.
 * @param list Lights.
 * @param source Transform the lights are brought into.
 */
void func_004349D0(LibLightPointerList* list, LibTransform* source)
{
    if (!source->matrix_ready)
    {
        source->update_transform_matrix();
        source->unk20e_0 = true;
        source->unk20e_1 = 0;
        ee_transpose_matrix(&source->transposed_transform, &source->transform);
        func_004D9E70(source);
    }
    else if (!source->unk20e_0)
    {
        source->unk20e_0 = 1;
        source->unk20e_1 = 0;
        ee_transpose_matrix(&source->transposed_transform, &source->transform);
        func_004D9E70(source);
    }
    else if (!source->unk20e_2)
    {
        func_004D9E70(source);
    }

    const LibMatrix44Value* inverse = &source->inverse_transform;
    LibMatrix44Value normalized = *inverse;
    vu0_normalize_rows_xyz(&normalized);
    const FieldVec4A& zero = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    copy_vector(&list->ambient, (const LibVector4*)&zero);
    list->has_positional = 0;
    s32 count = list->count;

    for (s32 i = 0; i < count; i++)
    {
        LibClass1736C0* light = list->lights[i];
        light->func_slot84(inverse, &normalized);

        if (!light->kind)
        {
            const LibVector4* vector = light->func_slot88(0, 0);
            list->ambient.x += vector->x;
            list->ambient.y += vector->y;
            list->ambient.z += vector->z;
        }
        else
        {
            list->has_positional = 1;
        }
    }
}

s32 func_00434F20(void* object)
{
    return 6;
}

/** @brief Let go of the source, destroying it when this was its last emitter, then destroy the emitter. */
void LibClass173990::destroy()
{
    LibObject1751A0* held = source;

    if (held && held->user_count > 0 && --held->user_count == 0)
    {
        held->destroy();
    }

    source = 0;
    LibTransformOwner::destroy();
}

/** @brief Release the textures, then detach and queue the model. */
void LibObject1751A0::destroy()
{
    release_textures();
    LibColorModel::destroy();
}

// TODO: The emitter and grid destructors later in this file inline these operators while the next file calls
// them, so I think this file was built with auto-inlining. Until the flags are settled, this scoped pragma stands in
// for it here.
#pragma push
#pragma auto_inline on

/**
 * @brief Free an array whose construction failed, the same way as operator delete[](void*).
 * @param object Array storage, or null.
 * @param heap Heap selector the array was allocated with.
 */
void LibClass173A28::operator delete[](void* object, s32 heap)
{
    if (g_field_allocation_heap)
    {
        if (object)
        {
            resident_heap_release(object);
        }
    }
    else
    {
        ::operator delete(object);
    }
}

/**
 * @brief Free an array through the heap at g_field_allocation_heap when one is set, otherwise through operator delete.
 * @param object Array storage, or null.
 */
void LibClass173A28::operator delete[](void* object)
{
    if (g_field_allocation_heap)
    {
        if (object)
        {
            resident_heap_release(object);
        }
    }
    else
    {
        ::operator delete(object);
    }
}

/**
 * @brief Free an object whose construction failed, the same way as operator delete(void*).
 * @param object Object storage, or null.
 * @param heap Heap selector the object was allocated with.
 */
void LibClass173A28::operator delete(void* object, s32 heap)
{
    if (g_field_allocation_heap)
    {
        if (object)
        {
            resident_heap_release(object);
        }
    }
    else
    {
        ::operator delete(object);
    }
}

/**
 * @brief Free an object through the heap at g_field_allocation_heap when one is set, otherwise through operator delete.
 * @param object Object storage, or null.
 */
void LibClass173A28::operator delete(void* object)
{
    if (g_field_allocation_heap)
    {
        if (object)
        {
            resident_heap_release(object);
        }
    }
    else
    {
        ::operator delete(object);
    }
}

#pragma pop

/**
 * @brief Allocate an array from the heap at g_field_allocation_heap when one is set, otherwise through operator new.
 * @param size Size in bytes.
 * @param heap Heap selector passed on to operator new.
 * @return The allocation.
 */
void* LibClass173A28::operator new[](u32 size, s32 heap)
{
    if (g_field_allocation_heap)
    {
        return resident_heap_allocate(g_field_allocation_heap, size);
    }

    return ::operator new(size, heap);
}

/**
 * @brief Allocate an object from the heap at g_field_allocation_heap when one is set, otherwise through operator new.
 * @param size Size in bytes.
 * @param heap Heap selector passed on to operator new.
 * @return The allocation.
 */
void* LibClass173A28::operator new(u32 size, s32 heap)
{
    if (g_field_allocation_heap)
    {
        return resident_heap_allocate(g_field_allocation_heap, size);
    }

    return ::operator new(size, heap);
}

/**
 * @brief Store unk428.
 * @param emitter Emitter to update.
 * @param value Word to store.
 */
void func_00435190(LibClass173990* emitter, u32 value)
{
    emitter->unk428 = value;
}

/**
 * @brief Store unk49c bit 2 and the bytes unk492 and unk493.
 * @param emitter Emitter to update.
 * @param flag Low bit goes to unk49c bit 2.
 * @param first Stored in unk492.
 * @param second Stored in unk493.
 */
void func_004351A0(LibClass173990* emitter, u32 flag, u8 first, u8 second)
{
    emitter->unk49c_2 = flag;
    emitter->unk492 = first;
    emitter->unk493 = second;
}

/**
 * @brief Store unk49c bit 1 and two angles, and cache the squared cosines of their halves.
 * @param emitter Emitter to update.
 * @param flag Low bit goes to unk49c bit 1.
 * @param first Angle stored in unk410.
 * @param second Angle stored in unk414.
 */
void func_004351D0(LibClass173990* emitter, u32 flag, float first, float second)
{
    float first_cosine;
    float second_cosine;

    emitter->unk49c_1 = flag;
    emitter->unk410 = first;
    emitter->unk414 = second;
    first_cosine = lib_cosine_degree9(0.5f * first);
    second_cosine = lib_cosine_degree9(0.5f * second);
    first_cosine *= first_cosine;
    second_cosine *= second_cosine;
    emitter->unk418 = second_cosine;
    emitter->unk41c = 1.0f / (first_cosine - second_cosine);
}

/**
 * @brief Store unk49b bit 7, unk49c bit 0, unk491 and unk40c.
 * @param emitter Emitter to update.
 * @param first_flag Low bit goes to unk49b bit 7.
 * @param second_flag Low bit goes to unk49c bit 0.
 * @param value Stored in unk491.
 * @param factor Stored in unk40c.
 */
void func_00435270(LibClass173990* emitter, bool first_flag, bool second_flag, u8 value, float factor)
{
    emitter->unk49b_7 = first_flag;
    emitter->unk49c_0 = second_flag;
    emitter->unk491 = value;
    emitter->unk40c = factor;
}

/**
 * @brief Store unk49b bit 6 and the floats unk404 and unk408.
 * @param emitter Emitter to update.
 * @param flag Low bit goes to unk49b bit 6.
 * @param first Stored in unk404.
 * @param second Stored in unk408.
 */
void func_004352B0(LibClass173990* emitter, u32 flag, float first, float second)
{
    emitter->unk49b_6 = flag;
    emitter->unk404 = first;
    emitter->unk408 = second;
}

/**
 * @brief Copy another emitter's settings, entries and offset transform.
 * @param other Emitter to copy.
 */
void LibClass173990::copy_state(const LibClass173990* other)
{
    unk220 = other->unk220;
    unk230 = other->unk230;
    unk240 = other->unk220;
    unk250 = other->unk250;
    unk260 = other->unk260;
    unk270 = other->unk270;
    unk240 = other->unk240;
    unk290 = other->unk290;
    unk2a0 = other->unk2a0;
    unk2b0 = other->unk2b0;
    unk2c0 = other->unk2c0;
    unk2d0 = other->unk2d0;
    unk2e0 = other->unk2e0;
    unk2f0 = other->unk2f0;
    unk300 = other->unk2c0;
    unk310 = other->unk2d0;
    unk320 = other->unk2e0;
    unk330 = other->unk2f0;
    unk340 = other->unk2c0;
    unk350 = other->unk2d0;
    unk360 = other->unk2e0;
    unk370 = other->unk2f0;
    unk380 = other->unk380;
    unk390 = other->unk390;
    unk3a0 = other->unk3a0;
    unk3b0 = other->unk3b0;
    unk3c0[0] = other->unk3c0[0];
    unk3c0[1] = other->unk3c0[1];
    unk3c0[2] = other->unk3c0[2];
    unk3c0[3] = other->unk3c0[3];
    source = other->source;
    unk42c = other->unk42c;
    unk499_0 = 1;
    unk3ec = other->unk3ec;
    unk3f0 = other->unk3f0;
    unk3f4 = other->unk3f4;
    unk3f8 = other->unk3f8;
    unk420 = other->unk420;
    unk49a = other->unk49a;
    unk499_1 = other->unk499_1;
    unk49b_0 = other->unk49b_0;
    unk49b_1 = other->unk49b_1;
    unk49b_2 = other->unk49b_2;
    unk49b_3 = other->unk49b_3;
    unk49b_4 = other->unk49b_4;
    unk49b_6 = other->unk49b_6;
    unk49b_7 = other->unk49b_7;
    unk49c_0 = other->unk49c_0;
    unk49c_1 = other->unk49c_1;
    unk49c_5 = other->unk49c_5;
    unk3fc = other->unk3fc;
    unk404 = other->unk404;
    unk408 = other->unk408;
    unk40c = other->unk40c;
    unk410 = other->unk410;
    unk414 = other->unk414;
    unk491 = other->unk491;
    unk418 = other->unk418;
    unk41c = other->unk41c;
    unk49c_2 = other->unk49c_2;
    unk492 = other->unk492;
    unk493 = other->unk493;
    unk428 = other->unk428;
    unk434 = other->unk434;
    unk438 = other->unk438;

    for (s32 i = 0; i < 8; i++)
    {
        unk480[i] = other->unk480[i];
    }

    for (s32 i = 0; i < 8; i++)
    {
        unk488[i] = other->unk488[i];
    }

    unk49c_3 = other->unk49c_3;
    unk49c_6 = other->unk49c_6;
    s32 count = other->entry_count;

    if (count != 0)
    {
        delete[] entries;
        entries = new (0) LibClass173490Entry[count];

        if (entries != 0)
        {
            entry_count = count;
        }
        else
        {
            entry_count = 0;
        }

        for (s32 i = 0; i < other->entry_count; i++)
        {
            const LibClass173490Entry& entry = other->entries[i];

            if (entries != 0)
            {
                entries[i] = entry;
            }
        }
    }
    else
    {
        entry_count = 0;
        delete[] entries;
        entries = 0;
    }

    LibTransform::copy_offset_transform_state(other);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00435840);

}

extern "C" {

typedef struct ByteClearOwnertext_0043A920
{
    u8 unk00[0x480];
    u8 unk480;
} ByteClearOwnertext_0043A920;

/**
 * @brief Report no selected cell.
 * @return -1.
 */
s32 LibClass173A40::func_slot3C()
{
    return -1;
}

typedef struct QuadwordSetter230Ownertext_0043A920 { u8 unk00[0x230]; unsigned __int128 value230; u8 unk240[0x241]; u8 flag481; } QuadwordSetter230Ownertext_0043A920;
typedef struct QuadwordSetter250Ownertext_0043A920 { u8 unk00[0x250]; unsigned __int128 value250; u8 unk260[0x222]; u8 flag482; } QuadwordSetter250Ownertext_0043A920;
typedef struct QuadwordSetter2B0Ownertext_0043A920 { u8 unk00[0x2B0]; unsigned __int128 value2B0; u8 unk2C0[0x1C5]; u8 flag485; } QuadwordSetter2B0Ownertext_0043A920;

typedef struct FlagFloat340Ownertext_0043A920 { u8 pad00[0x340]; float xy[2]; u8 pad348[0x8]; float zw[2]; u8 pad358[0x132]; u8 flag48A; } FlagFloat340Ownertext_0043A920;
typedef struct FlagFloat300Ownertext_0043A920 { u8 pad00[0x300]; float xy[2]; u8 pad308[0x8]; float zw[2]; u8 pad318[0x170]; u8 flag488; } FlagFloat300Ownertext_0043A920;
typedef struct FlagFloat2C0Ownertext_0043A920 { u8 pad00[0x2C0]; float xy[2]; u8 pad2C8[0x8]; float zw[2]; u8 pad2D8[0x1AE]; u8 flag486; } FlagFloat2C0Ownertext_0043A920;

typedef struct FlagFloat230Receivertext_0043A920 { u8 pad00[0x230]; float x230; u8 pad234[4]; float z238; u8 pad23C[4]; float y240; u8 pad244[0x23D]; u8 flag481; } FlagFloat230Receivertext_0043A920;
typedef struct FlagFloat220Receivertext_0043A920 { u8 pad00[0x220]; float x220; float y224; u8 pad228[0x1D0]; float z3F8; u8 pad3FC[0x84]; u8 flag480; } FlagFloat220Receivertext_0043A920;

typedef struct ClearFlagQuadwordOwnertext_0043A920 { u8 pad00[0x3A0]; unsigned __int128 value3A0; u8 pad3B0[0xDF]; u8 flag48F; } ClearFlagQuadwordOwnertext_0043A920;

typedef struct ClearFlagSlot380Ownertext_0043A920 { u8 pad00[0x380]; unsigned __int128 value380; u8 pad390[0xFE]; u8 flag48E; } ClearFlagSlot380Ownertext_0043A920;
typedef struct ClearFlagSlot360Ownertext_0043A920 { u8 pad00[0x360]; unsigned __int128 value360; u8 pad370[0x11B]; u8 flag48B; } ClearFlagSlot360Ownertext_0043A920;
typedef struct ClearFlagSlot320Ownertext_0043A920 { u8 pad00[0x320]; unsigned __int128 value320; u8 pad330[0x159]; u8 flag489; } ClearFlagSlot320Ownertext_0043A920;
typedef struct ClearFlagSlot2E0Ownertext_0043A920 { u8 pad00[0x2E0]; unsigned __int128 value2E0; u8 pad2F0[0x197]; u8 flag487; } ClearFlagSlot2E0Ownertext_0043A920;
typedef struct ClearFlagSlot2B0Ownertext_0043A920 { u8 pad00[0x2B0]; unsigned __int128 value2B0; u8 pad2C0[0x1C5]; u8 flag485; } ClearFlagSlot2B0Ownertext_0043A920;
typedef struct ClearFlagSlot290Ownertext_0043A920 { u8 pad00[0x290]; unsigned __int128 value290; u8 pad2A0[0x1E4]; u8 flag484; } ClearFlagSlot290Ownertext_0043A920;
typedef struct ClearFlagSlot270Ownertext_0043A920 { u8 pad00[0x270]; unsigned __int128 value270; u8 pad280[0x203]; u8 flag483; } ClearFlagSlot270Ownertext_0043A920;
typedef struct ClearFlagSlot250Ownertext_0043A920 { u8 pad00[0x250]; unsigned __int128 value250; u8 pad260[0x222]; u8 flag482; } ClearFlagSlot250Ownertext_0043A920;
typedef struct ClearFlagSlot230Ownertext_0043A920 { u8 pad00[0x230]; unsigned __int128 value230; u8 pad240[0x241]; u8 flag481; } ClearFlagSlot230Ownertext_0043A920;

typedef struct FlagFloat230Fivetext_0043A920
{
    u8 pad00[0x230];
    float first230;
    float fourth234;
    float third238;
    u8 pad23C[4];
    float second240;
    float fifth244;
    u8 pad248[0x239];
    u8 flag481;
} FlagFloat230Fivetext_0043A920;

typedef struct Word42CFlag49Ctext_0043A920
{
    u8 pad00[0x42C];
    s32 value42C;
    u8 pad430[0x6C];
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 bit2 : 1;
    u8 bit3 : 1;
    u8 bit4 : 1;
} Word42CFlag49Ctext_0043A920;

typedef struct TwoQuadwordFlag3A0Ownertext_0043A920 { u8 pad00[0x3A0]; unsigned __int128 values[2]; u8 pad3C0[0xCF]; u8 flag48F; } TwoQuadwordFlag3A0Ownertext_0043A920;

typedef struct TwoQuadwordFlag380Ownertext_0043A920 { u8 pad00[0x380]; unsigned __int128 values[2]; u8 pad3A0[0xEE]; u8 flag48E; } TwoQuadwordFlag380Ownertext_0043A920;
typedef struct TwoQuadwordFlag360Ownertext_0043A920 { u8 pad00[0x360]; unsigned __int128 values[2]; u8 pad380[0x10B]; u8 flag48B; } TwoQuadwordFlag360Ownertext_0043A920;
typedef struct TwoQuadwordFlag320Ownertext_0043A920 { u8 pad00[0x320]; unsigned __int128 values[2]; u8 pad340[0x149]; u8 flag489; } TwoQuadwordFlag320Ownertext_0043A920;
typedef struct TwoQuadwordFlag2E0Ownertext_0043A920 { u8 pad00[0x2E0]; unsigned __int128 values[2]; u8 pad300[0x187]; u8 flag487; } TwoQuadwordFlag2E0Ownertext_0043A920;
typedef struct TwoQuadwordFlag290Ownertext_0043A920 { u8 pad00[0x290]; unsigned __int128 values[2]; u8 pad2B0[0x1D4]; u8 flag484; } TwoQuadwordFlag290Ownertext_0043A920;
typedef struct TwoQuadwordFlag270Ownertext_0043A920 { u8 pad00[0x270]; unsigned __int128 values[2]; u8 pad290[0x1F3]; u8 flag483; } TwoQuadwordFlag270Ownertext_0043A920;
typedef struct TwoQuadwordFlag250Ownertext_0043A920 { u8 pad00[0x250]; unsigned __int128 values[2]; u8 pad270[0x212]; u8 flag482; } TwoQuadwordFlag250Ownertext_0043A920;
typedef struct TwoQuadwordFlag230Ownertext_0043A920 { u8 pad00[0x230]; unsigned __int128 values[2]; u8 pad250[0x231]; u8 flag481; } TwoQuadwordFlag230Ownertext_0043A920;

void func_0043A930(void* object, float first, float second)
{
    u8* bytes = (u8*)object;
    bytes[0x498] = 1;
    *(float*)(bytes + 0x3D8) = first;
    *(float*)(bytes + 0x3D8) = second;
}

void func_0043A950(void* object, float value)
{
    u8* bytes = (u8*)object;
    bytes[0x498] = 0;
    *(float*)(bytes + 0x3D8) = value;
}

void func_0043A960(void* object, float first, float second)
{
    u8* bytes = (u8*)object;
    bytes[0x497] = 1;
    *(float*)(bytes + 0x3D0) = first;
    *(float*)(bytes + 0x3D0) = second;
}

void func_0043A980(void* object, float value)
{
    u8* bytes = (u8*)object;
    bytes[0x497] = 0;
    *(float*)(bytes + 0x3D0) = value;
}

void func_0043A990(void* object, float first, float second)
{
    u8* bytes = (u8*)object;
    bytes[0x490] = 2;
    *(float*)(bytes + 0x43C) = first;
    *(float*)(bytes + 0x440) = second;
}

typedef struct LibFloat43CByte490
{
    u8 unk00[0x43C];
    float unk43C;
    u8 unk440[0x50];
    u8 unk490;
} LibFloat43CByte490;

/** Set the byte at receiver offset 0x490 and store the float at offset 0x43C. */
void func_0043A9B0(void* object, float value)
{
    LibFloat43CByte490* receiver = (LibFloat43CByte490*)object;
    receiver->unk490 = 1;
    receiver->unk43C = value;
}

void func_0043A9C0(void* object, const unsigned __int128* first, const unsigned __int128* second)
{
    TwoQuadwordFlag3A0Ownertext_0043A920* receiver = (TwoQuadwordFlag3A0Ownertext_0043A920*)object;
    receiver->flag48F = 2;
    receiver->values[0] = *first;
    receiver->values[1] = *second;
}

void func_0043A9E0(void* object, const unsigned __int128* first, const unsigned __int128* second)
{
    TwoQuadwordFlag3A0Ownertext_0043A920* receiver = (TwoQuadwordFlag3A0Ownertext_0043A920*)object;
    receiver->flag48F = 1;
    receiver->values[0] = *first;
    receiver->values[1] = *second;
}

void func_0043AA00(void* object, const unsigned __int128* value)
{
    ClearFlagQuadwordOwnertext_0043A920* receiver = (ClearFlagQuadwordOwnertext_0043A920*)object;
    receiver->flag48F = 0;
    receiver->value3A0 = *value;
}

void func_0043AA10(void* object, const unsigned __int128* first, const unsigned __int128* second)
{
    TwoQuadwordFlag380Ownertext_0043A920* receiver = (TwoQuadwordFlag380Ownertext_0043A920*)object;
    receiver->flag48E = 2;
    receiver->values[0] = *first;
    receiver->values[1] = *second;
}

void func_0043AA30(void* object, const unsigned __int128* first, const unsigned __int128* second)
{
    TwoQuadwordFlag380Ownertext_0043A920* receiver = (TwoQuadwordFlag380Ownertext_0043A920*)object;
    receiver->flag48E = 1;
    receiver->values[0] = *first;
    receiver->values[1] = *second;
}

void func_0043AA50(void* object, const unsigned __int128* value)
{
    ClearFlagSlot380Ownertext_0043A920* receiver = (ClearFlagSlot380Ownertext_0043A920*)object;
    receiver->flag48E = 0;
    receiver->value380 = *value;
}

void func_0043AA60(void* object, float first, float second)
{
    u8* bytes = (u8*)object;
    bytes[0x48D] = 1;
    *(float*)(bytes + 0x3C8) = first;
    *(float*)(bytes + 0x3CC) = second;
}

void func_0043AA80(void* object, float value)
{
    u8* bytes = (u8*)object;
    bytes[0x48D] = 0;
    *(float*)(bytes + 0x3C8) = value;
}

void func_0043AA90(void* object, float first, float second)
{
    u8* bytes = (u8*)object;
    bytes[0x48C] = 1;
    *(float*)(bytes + 0x3C0) = first;
    *(float*)(bytes + 0x3C4) = second;
}

void func_0043AAB0(void* object, float value)
{
    u8* bytes = (u8*)object;
    bytes[0x48C] = 0;
    *(float*)(bytes + 0x3C0) = value;
}

void func_0043AAC0(void* object, const unsigned __int128* first, const unsigned __int128* second)
{
    TwoQuadwordFlag360Ownertext_0043A920* receiver = (TwoQuadwordFlag360Ownertext_0043A920*)object;
    receiver->flag48B = 1;
    receiver->values[0] = *first;
    receiver->values[1] = *second;
}

void func_0043AAE0(void* object, const unsigned __int128* value)
{
    ClearFlagSlot360Ownertext_0043A920* receiver = (ClearFlagSlot360Ownertext_0043A920*)object;
    receiver->flag48B = 0;
    receiver->value360 = *value;
}

void func_0043AAF0(void* object, float x, float y, float z, float w)
{
    FlagFloat340Ownertext_0043A920* receiver = (FlagFloat340Ownertext_0043A920*)object;
    receiver->flag48A = 1;
    receiver->xy[0] = x;
    receiver->xy[1] = y;
    receiver->zw[0] = z;
    receiver->zw[1] = w;
}

void func_0043AB10(void* object, float first, float second)
{
    u8* bytes = (u8*)object;
    bytes[0x48A] = 0;
    *(float*)(bytes + 0x340) = first;
    *(float*)(bytes + 0x344) = second;
}

void func_0043AB20(void* object, const unsigned __int128* first, const unsigned __int128* second)
{
    TwoQuadwordFlag320Ownertext_0043A920* receiver = (TwoQuadwordFlag320Ownertext_0043A920*)object;
    receiver->flag489 = 1;
    receiver->values[0] = *first;
    receiver->values[1] = *second;
}

void func_0043AB40(void* object, const unsigned __int128* value)
{
    ClearFlagSlot320Ownertext_0043A920* receiver = (ClearFlagSlot320Ownertext_0043A920*)object;
    receiver->flag489 = 0;
    receiver->value320 = *value;
}

void func_0043AB50(void* object, float x, float y, float z, float w)
{
    FlagFloat300Ownertext_0043A920* receiver = (FlagFloat300Ownertext_0043A920*)object;
    receiver->flag488 = 1;
    receiver->xy[0] = x;
    receiver->xy[1] = y;
    receiver->zw[0] = z;
    receiver->zw[1] = w;
}

void func_0043AB70(void* object, float first, float second)
{
    u8* bytes = (u8*)object;
    bytes[0x488] = 0;
    *(float*)(bytes + 0x300) = first;
    *(float*)(bytes + 0x304) = second;
}

void func_0043AB80(void* object, const unsigned __int128* first, const unsigned __int128* second)
{
    TwoQuadwordFlag2E0Ownertext_0043A920* receiver = (TwoQuadwordFlag2E0Ownertext_0043A920*)object;
    receiver->flag487 = 1;
    receiver->values[0] = *first;
    receiver->values[1] = *second;
}

void func_0043ABA0(void* object, const unsigned __int128* value)
{
    ClearFlagSlot2E0Ownertext_0043A920* receiver = (ClearFlagSlot2E0Ownertext_0043A920*)object;
    receiver->flag487 = 0;
    receiver->value2E0 = *value;
}

void func_0043ABB0(void* object, float x, float y, float z, float w)
{
    FlagFloat2C0Ownertext_0043A920* receiver = (FlagFloat2C0Ownertext_0043A920*)object;
    receiver->flag486 = 1;
    receiver->xy[0] = x;
    receiver->xy[1] = y;
    receiver->zw[0] = z;
    receiver->zw[1] = w;
}

void func_0043ABD0(void* object, float first, float second)
{
    u8* bytes = (u8*)object;
    bytes[0x486] = 0;
    *(float*)(bytes + 0x2C0) = first;
    *(float*)(bytes + 0x2C4) = second;
}

void func_0043ABE0(void* object, const unsigned __int128* value)
{
    QuadwordSetter2B0Ownertext_0043A920* receiver = (QuadwordSetter2B0Ownertext_0043A920*)object;
    receiver->flag485 = 1;
    receiver->value2B0 = *value;
}

void func_0043AC00(void* object, const unsigned __int128* value)
{
    ClearFlagSlot2B0Ownertext_0043A920* receiver = (ClearFlagSlot2B0Ownertext_0043A920*)object;
    receiver->flag485 = 0;
    receiver->value2B0 = *value;
}

void func_0043AC10(void* object, const unsigned __int128* first, const unsigned __int128* second)
{
    TwoQuadwordFlag290Ownertext_0043A920* receiver = (TwoQuadwordFlag290Ownertext_0043A920*)object;
    receiver->flag484 = 2;
    receiver->values[0] = *first;
    receiver->values[1] = *second;
}

void func_0043AC30(void* object, const unsigned __int128* first, const unsigned __int128* second)
{
    TwoQuadwordFlag290Ownertext_0043A920* receiver = (TwoQuadwordFlag290Ownertext_0043A920*)object;
    receiver->flag484 = 1;
    receiver->values[0] = *first;
    receiver->values[1] = *second;
}

void func_0043AC50(void* object, const unsigned __int128* value)
{
    ClearFlagSlot290Ownertext_0043A920* receiver = (ClearFlagSlot290Ownertext_0043A920*)object;
    receiver->flag484 = 0;
    receiver->value290 = *value;
}

void func_0043AC60(void* object, const unsigned __int128* first, const unsigned __int128* second)
{
    TwoQuadwordFlag270Ownertext_0043A920* receiver = (TwoQuadwordFlag270Ownertext_0043A920*)object;
    receiver->flag483 = 2;
    receiver->values[0] = *first;
    receiver->values[1] = *second;
}

void func_0043AC80(void* object, const unsigned __int128* first, const unsigned __int128* second)
{
    TwoQuadwordFlag270Ownertext_0043A920* receiver = (TwoQuadwordFlag270Ownertext_0043A920*)object;
    receiver->flag483 = 1;
    receiver->values[0] = *first;
    receiver->values[1] = *second;
}

void func_0043ACA0(void* object, const unsigned __int128* value)
{
    ClearFlagSlot270Ownertext_0043A920* receiver = (ClearFlagSlot270Ownertext_0043A920*)object;
    receiver->flag483 = 0;
    receiver->value270 = *value;
}

void func_0043ACB0(void* object, const unsigned __int128* value)
{
    QuadwordSetter250Ownertext_0043A920* receiver = (QuadwordSetter250Ownertext_0043A920*)object;
    receiver->flag482 = 2;
    receiver->value250 = *value;
}

void func_0043ACD0(void* object, const unsigned __int128* first, const unsigned __int128* second)
{
    TwoQuadwordFlag250Ownertext_0043A920* receiver = (TwoQuadwordFlag250Ownertext_0043A920*)object;
    receiver->flag482 = 1;
    receiver->values[0] = *first;
    receiver->values[1] = *second;
}

void func_0043ACF0(void* object, const unsigned __int128* value)
{
    ClearFlagSlot250Ownertext_0043A920* receiver = (ClearFlagSlot250Ownertext_0043A920*)object;
    receiver->flag482 = 0;
    receiver->value250 = *value;
}

void func_0043AD00(void* object, float first, float second, float third, float fourth, float fifth)
{
    FlagFloat230Fivetext_0043A920* receiver = (FlagFloat230Fivetext_0043A920*)object;
    receiver->flag481 = 7;
    receiver->first230 = first;
    receiver->fourth234 = fourth;
    receiver->third238 = third;
    receiver->second240 = second;
    receiver->fifth244 = fifth;
}

void func_0043AD20(void* object, const unsigned __int128* value)
{
    QuadwordSetter230Ownertext_0043A920* receiver = (QuadwordSetter230Ownertext_0043A920*)object;
    receiver->flag481 = 6;
    receiver->value230 = *value;
}

void func_0043AD40(void* object, float first, float second)
{
    u8* bytes = (u8*)object;
    bytes[0x481] = 5;
    *(float*)(bytes + 0x230) = first;
    *(float*)(bytes + 0x240) = second;
}

void func_0043AD60(void* object, float x, float y, float z)
{
    FlagFloat230Receivertext_0043A920* receiver = (FlagFloat230Receivertext_0043A920*)object;
    receiver->flag481 = 4;
    receiver->x230 = x;
    receiver->y240 = y;
    receiver->z238 = z;
}

void func_0043AD80(void* object, float first, float second)
{
    u8* bytes = (u8*)object;
    bytes[0x481] = 3;
    *(float*)(bytes + 0x230) = first;
    *(float*)(bytes + 0x240) = second;
}

void func_0043ADA0(void* object, const unsigned __int128* value)
{
    QuadwordSetter230Ownertext_0043A920* receiver = (QuadwordSetter230Ownertext_0043A920*)object;
    receiver->flag481 = 2;
    receiver->value230 = *value;
}

void func_0043ADC0(void* object, const unsigned __int128* first, const unsigned __int128* second)
{
    TwoQuadwordFlag230Ownertext_0043A920* receiver = (TwoQuadwordFlag230Ownertext_0043A920*)object;
    receiver->flag481 = 1;
    receiver->values[0] = *first;
    receiver->values[1] = *second;
}

void func_0043ADE0(void* object, const unsigned __int128* value)
{
    ClearFlagSlot230Ownertext_0043A920* receiver = (ClearFlagSlot230Ownertext_0043A920*)object;
    receiver->flag481 = 0;
    receiver->value230 = *value;
}

void func_0043ADF0(void* object, s32 value)
{
    Word42CFlag49Ctext_0043A920* receiver = (Word42CFlag49Ctext_0043A920*)object;
    receiver->value42C = value;
    receiver->bit4 = 0;
}

typedef struct EmitterSettings43AE20
{
    u8 pad00[0x220];
    unsigned __int128 value220;
    u8 pad230[0x1C8];
    float value3F8;
    u8 pad3FC[0x24];
    float value420;
    u8 pad424[8];
    s32 value42C;
    u8 pad430[0x50];
    u8 value480;
    u8 pad481[0x1B];
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 bit2 : 1;
    u8 bit3 : 1;
    u8 bit4 : 1;
} EmitterSettings43AE20;

/**
 * @brief Set the emitter's mode to 11 with a vector, two values, a word and flag bit 3; clear flag bit 4.
 * @param object Emitter.
 * @param value Vector stored at 0x220.
 * @param word Word stored at 0x42C.
 * @param flag Flag bit 3.
 * @param first Value stored at 0x420.
 * @param second Value stored at 0x3F8.
 */
void func_0043AE20(void* object, const unsigned __int128* value, s32 word, s32 flag, float first, float second)
{
    EmitterSettings43AE20* receiver = (EmitterSettings43AE20*)object;
    receiver->value480 = 0xB;
    receiver->value220 = *value;
    receiver->value420 = first;
    receiver->value3F8 = second;
    receiver->bit3 = flag;
    receiver->value42C = word;
    receiver->bit4 = 0;
}

void func_0043AE80(void* object, const unsigned __int128* vector, float amount)
{
    u8* bytes = (u8*)object;
    bytes[0x480] = 10;
    *(unsigned __int128*)(bytes + 0x220) = *vector;
    *(float*)(bytes + 0x3F8) = amount;
}

void func_0043AEA0(void* object, const unsigned __int128* vector, float amount)
{
    u8* bytes = (u8*)object;
    bytes[0x480] = 9;
    *(unsigned __int128*)(bytes + 0x220) = *vector;
    *(float*)(bytes + 0x3F8) = amount;
}

void func_0043AEC0(void* object, const unsigned __int128* vector, float amount)
{
    u8* bytes = (u8*)object;
    bytes[0x480] = 8;
    *(unsigned __int128*)(bytes + 0x220) = *vector;
    *(float*)(bytes + 0x3F8) = amount;
}

void func_0043AEE0(void* object, const unsigned __int128* vector, float amount)
{
    u8* bytes = (u8*)object;
    bytes[0x480] = 7;
    *(unsigned __int128*)(bytes + 0x220) = *vector;
    *(float*)(bytes + 0x3F8) = amount;
}

void func_0043AF00(void* object, const unsigned __int128* vector, float amount)
{
    u8* bytes = (u8*)object;
    bytes[0x480] = 6;
    *(unsigned __int128*)(bytes + 0x220) = *vector;
    *(float*)(bytes + 0x3F8) = amount;
}

void func_0043AF20(void* object, const unsigned __int128* vector, float amount)
{
    u8* bytes = (u8*)object;
    bytes[0x480] = 5;
    *(unsigned __int128*)(bytes + 0x220) = *vector;
    *(float*)(bytes + 0x3F8) = amount;
}

void func_0043AF40(void* object, float x, float y, float z)
{
    FlagFloat220Receivertext_0043A920* receiver = (FlagFloat220Receivertext_0043A920*)object;
    receiver->flag480 = 4;
    receiver->x220 = x;
    receiver->y224 = y;
    receiver->z3F8 = z;
}

void func_0043AF60(void* object, const unsigned __int128* vector, float amount)
{
    u8* bytes = (u8*)object;
    bytes[0x480] = 3;
    *(unsigned __int128*)(bytes + 0x220) = *vector;
    *(float*)(bytes + 0x3F8) = amount;
}

void func_0043AF80(void* object, const unsigned __int128* vector, float amount)
{
    u8* bytes = (u8*)object;
    bytes[0x480] = 2;
    *(unsigned __int128*)(bytes + 0x220) = *vector;
    *(float*)(bytes + 0x3F8) = amount;
}

void func_0043AFA0(void* object, const unsigned __int128* vector, float amount)
{
    u8* bytes = (u8*)object;
    bytes[0x480] = 1;
    *(unsigned __int128*)(bytes + 0x220) = *vector;
    *(float*)(bytes + 0x3F8) = amount;
}

void func_0043AFC0(void* object)
{
    ByteClearOwnertext_0043A920* receiver = (ByteClearOwnertext_0043A920*)object;
    receiver->unk480 = 0;
}

/**
 * @brief Test whether an image model is active: flagged with unkadf and either without an unkabc period or with its
 * phase running.
 * @param image Image model.
 * @return Whether it is active.
 */
static inline bool lib_image_model_active(const LibObject1751A0* image)
{
    if (image->unkadf)
    {
        if (image->unkabc == 0.0f)
        {
            return true;
        }

        if (image->phase_period && image->phase)
        {
            return true;
        }
    }

    return false;
}

/**
 * @brief Update the emitter while it has an image model: follow and face the camera as flagged, pass the transform to
 * the image model, end the emitter once its lifetime is over, track its velocity and emit whole entries at its rate.
 */
void LibClass173990::update()
{
    if (source == 0)
    {
        return;
    }

    if (draw_flags & LIB_DRAW_FOLLOW_CAMERA)
    {
        LibCamera* camera;

        if (display_manager != 0)
        {
            camera = static_cast<LibCamera*>(display_manager->current_display);
        }
        else
        {
            camera = static_cast<LibCamera*>(g_display_manager->current_display);
        }

        if (camera != 0)
        {
            if (camera->matrix_ready == 0)
            {
                camera->update_transform_matrix();
            }

            const LibMatrix44Value* matrix = camera->get_transform_matrix();
            set_translation(matrix->m[0][3], translation.y, matrix->m[2][3]);
        }
    }

    if (draw_flags & (LIB_DRAW_FACE_CAMERA_X | LIB_DRAW_FACE_CAMERA_Y | LIB_DRAW_FACE_CAMERA_Z))
    {
        LibCamera* camera;

        if (display_manager != 0)
        {
            camera = static_cast<LibCamera*>(display_manager->current_display);
        }
        else
        {
            camera = static_cast<LibCamera*>(g_display_manager->current_display);
        }

        if (camera != 0)
        {
            if (camera->matrix_ready == 0)
            {
                camera->update_transform_matrix();
            }

            LibVector4 angles;
            const float* camera_angles = camera->rotation_angles;
            func_004CDA40(&angles, &orientation);

            if (draw_flags & LIB_DRAW_FACE_CAMERA_X)
            {
                angles.x = -camera_angles[0];
            }

            if (draw_flags & LIB_DRAW_FACE_CAMERA_Y)
            {
                angles.y = camera_angles[1];
            }

            if (draw_flags & LIB_DRAW_FACE_CAMERA_Z)
            {
                angles.z = -camera_angles[2];
            }

            angles.y += 3.1415927f;
            set_rotation_vector(&angles);
            matrix_ready = 0;
        }
    }

    if (unk499_1 && source != 0)
    {
        source->set_translation_vector(&translation);
        source->set_orientation(&orientation);
        source->set_scale_vector(&scale);
    }

    unk400 += g_frame_seconds;

    if (unk49b_6 && !(unk400 < unk404))
    {
        if (!(unk400 < unk408) || source->unkaac == 0.0f)
        {
            if (unk3e8 != 0)
            {
                func_0046C090(reinterpret_cast<LibEntryManager*>(unk3e8), this);
            }

            LibObject1751A0* held = source;
            s32 users;

            if (held->user_count > 0)
            {
                users = --held->user_count;
            }
            else
            {
                users = 0;
            }

            if (users == 0)
            {
                LibGridBase* grid = source->reference;
                func_0046B3F0(source);

                if (grid->user_count == 0)
                {
                    delete grid;
                }

                source->destroy();
            }

            destroy();
        }

        return;
    }

    if (unk49b_4 || unk49c_5 || unk49c_6)
    {
        if (!unk49b_5)
        {
            if (matrix_ready == 0)
            {
                update_transform_matrix();
            }

            unk49b_5 = 1;
            *reinterpret_cast<unsigned __int128*>(&velocity) = 0;
            *reinterpret_cast<unsigned __int128*>(&position_delta) = 0;
            previous_position.x = transform.m[0][3];
            previous_position.y = transform.m[1][3];
            previous_position.z = transform.m[2][3];
            previous_position.w = 1.0f;
        }
        else
        {
            if (matrix_ready == 0)
            {
                update_transform_matrix();
            }

            FieldVec4A position;
            position.x = transform.m[0][3];
            position.y = transform.m[1][3];
            position.z = transform.m[2][3];
            position.w = 1.0f;
            float scale = 60.0f * (1.0f / g_frame_ticks);
            position_delta.x = previous_position.x - position.x;
            position_delta.y = previous_position.y - position.y;
            position_delta.z = previous_position.z - position.z;
            velocity.x = scale * (position.x - previous_position.x);
            velocity.y = scale * (position.y - previous_position.y);
            velocity.z = scale * (position.z - previous_position.z);
            previous_position = position;
        }
    }

    if (lib_image_model_active(source) && (source->draw_flags & 0x10))
    {
        return;
    }

    float chance = unk3f0;

    if (chance >= 100.0f)
    {
        unk3f4 += unk3ec * g_frame_seconds;
    }
    else
    {
        float random = resident_random_below(10000);
        float spread = 0.01f * (100.0f - chance) * random;
        unk3f4 += unk3ec * g_frame_seconds * (0.0001f * spread + 0.01f * unk3f0);
    }

    if (!(unk3f4 < 1.0f))
    {
        s32 count = unk3f4;
        unk3f4 -= count;
        emit_entries(count, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    }
}

// TODO: The destructor inlines this too; see the operator delete note above.
#pragma push
#pragma auto_inline on

/** @brief Stop using the source image model, destroying it when this was its last user. */
void LibClass173990::release_source()
{
    LibObject1751A0* held = source;

    if (held != 0 && held->user_count > 0)
    {
        if (--held->user_count == 0)
        {
            held->destroy();
        }
    }

    source = 0;
}

#pragma pop

typedef struct EmitterSource43B700
{
    u8 pad00[0xAD0];
    s32 user_count;
} EmitterSource43B700;

typedef struct EmitterSourceOwner43B700
{
    u8 pad00[0x3E4];
    EmitterSource43B700* source;
    u8 pad3E8[0xC];
    u32 value3F4;
    u8 pad3F8[0xA1];
    u8 bit0 : 1;
} EmitterSourceOwner43B700;

/**
 * @brief Attach a source to the emitter, set flag bit 0 of 0x499, clear 0x3F4 and count the emitter as a user.
 * @param object Emitter.
 * @param source Image model to draw from.
 */
void func_0043B700(void* object, EmitterSource43B700* source)
{
    EmitterSourceOwner43B700* receiver = (EmitterSourceOwner43B700*)object;
    receiver->bit0 = 1;
    receiver->source = source;
    receiver->value3F4 = 0;
    source->user_count++;
}

/** @brief Release the emitter's source and entries. */
LibClass173990::~LibClass173990()
{
    release_source();
    delete[] entries;
}

/** @brief Initialize the emitter with no source or entries, its flags cleared and its vectors reset. */
LibClass173990::LibClass173990()
{
    set_type_id(0x500);
    unk499_0 = 0;
    source = 0;
    entries = 0;
    unk49a = 0;
    unk499_1 = 0;
    unk49b_0 = 0;
    unk49b_1 = 0;
    unk49b_2 = 0;
    unk49b_3 = 0;
    unk49b_4 = 0;
    unk49b_5 = 0;
    unk49b_6 = 0;
    unk49c_2 = 0;
    unk49b_7 = 0;
    unk49c_0 = 0;
    unk49c_1 = 0;
    unk49c_5 = 0;
    unk49c_6 = 0;
    unk3fc = 1.0f;
    unk400 = 0;
    unk3f4 = 0;
    unk3ec = 0;
    unk3f0 = 0;
    unk230 = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    unk250 = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    unk260 = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    unk270 = FieldVec4A(128.0f, 128.0f, 128.0f, 128.0f);
    unk290 = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    unk2b0 = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    unk2c0 = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    unk2e0 = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    unk300 = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    unk320 = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    unk340 = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    unk360 = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    unk380 = FieldVec4A(1.0f, 1.0f, 1.0f, 1.0f);
    unk390 = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    unk3a0 = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    unk3b0 = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);

    for (s32 i = 0; i < 8; i++)
    {
        unk3c0[i] = 0;
    }

    unk420 = 0;
    entry_count = 0;

    for (s32 i = 0; i < 8; i++)
    {
        unk480[i] = 0;
    }

    for (s32 i = 0; i < 8; i++)
    {
        unk488[i] = 0;
    }

    unk497 = 0;
    unk498 = 0;
    unk49c_4 = 0;
    unk490 = 0;
    unk494 = 0;
    unk495 = 0;
    unk496 = 1;
    unk3e8 = 0;
    unk428 = 0;
}

/** @brief Do nothing (shared by every grid). */
void LibClass173A40::func_slot10()
{
}

/** @brief Do nothing (shared by every grid). */
void LibClass173A40::func_slot14()
{
}

}
