#include "ee.h"
#include "gs.h"
#include "include_asm.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/vector.h"
#include "overlays/lib/text_0046AE20.h"
#include "overlays/lib/text_0049B820.h"
#include "overlays/lib/trig_vu0.h"
#include "overlays/lib/vector_vu0.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/text_00429B00.h"
#include "main/resident_data.h"
#include "main/resident_001001E0.h"
#include "main/resident_00101260.h"
#include "main/resident_00101550.h"
#include "sdk/main/libgraph_0012EAC8.h"
#include "sdk/main/libc_guess_00137290.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "sdk/main/libkernl_00121940.h"
#include "overlays/lib/text_004AB8B0.h"
#include "main/resident_0010A0E0.h"
#include "clamp.h"
#include "overlays/lib/text_0044ABE0.h"
#include "overlays/lib/vector_inlines.h"

/**
 * @brief Subtract the first three components of one vector from another.
 * @param left Vector to subtract from.
 * @param right Vector to subtract.
 * @return left minus right, keeping left's fourth component.
 */
static inline FieldVec4B vector_difference(const FieldVec4B& left, const FieldVec4B& right)
{
    FieldVec4B value(left);
    value.x -= right.x;
    value.y -= right.y;
    value.z -= right.z;
    return value;
}

/**
 * @brief Add the first three components of two vectors.
 * @param left First vector.
 * @param right Vector to add.
 * @return left plus right, keeping left's fourth component.
 */
static inline FieldVec4B vector_sum(const FieldVec4B& left, const FieldVec4B& right)
{
    FieldVec4B value(left);
    value.x += right.x;
    value.y += right.y;
    value.z += right.z;
    return value;
}

/**
 * @brief Return a vector curve track's last keyframe.
 * @param track Track with at least one keyframe.
 * @return The last keyframe.
 */
static inline LibVectorCurveTrackKey& last_entry(LibVectorCurveTrackBase* track)
{
    return static_cast<LibVectorCurveTrackKey*>(track->key_array)[track->state.key_count - 1];
}

/**
 * @brief Return a keyframe's key.
 * @param entry Keyframe.
 * @return The key, stored in the value's fourth component.
 */
static inline float key_of(const LibVectorCurveTrackKey* entry)
{
    return entry->value.w;
}

/**
 * @brief Scale all four components of a vector.
 * @param scale Factor to multiply by.
 * @param vector Vector to scale.
 * @return The scaled vector.
 */
static inline FieldVec4B vector_scaled(float scale, const FieldVec4B& vector)
{
    FieldVec4B value(vector);
    return value *= scale;
}

extern "C" u8 D_00174C90[];
extern "C" void func_004A8F10(void* object);
extern "C" void func_004C2BB0(void* object);
extern "C" void func_00461830(void* embedded, void* adjusted);

struct LibVectorField10View
{
    u8 pad00[0x10];
    LibVector4 value10;
};

struct LibVectorField850View
{
    u8 pad00[0x850];
    LibVector4 value850;
};

struct LibStateBytes62View
{
    u8 pad00[0x62];
    u8 value62;
    u8 value63;
    u8 value64;
};

/** Packed sine-series coefficients, reduction constants, and shared sign scratch. */
struct LibTrigTable
{
    float pi;
    float inverse_pi;
    float coefficient_3;
    float coefficient_5;
    float coefficient_7;
    float coefficient_9;
    float sign;
    union
    {
        float angle;
        float sine_sign;
        float result;
    } phase;
    float half_pi;
    float inverse_half_pi;
    float cosine_offset;
    float scalar_cosine_offset;
    float coefficient_11;
    float coefficient_13;
    float unk38;
    float unk3c;
} __attribute__((aligned(16)));

/** Packed quotient lanes written by VU0 range reduction. */
struct LibTrigQuotients
{
    s32 unk00;
    s32 unk04;
    s32 cosine_half_turns;
    s32 sine_half_turns;
} __attribute__((aligned(16)));

/** Partial widget view with its retained container owner. */
struct LibWidgetContainerLink
{
    u8 unk00[0x14];
    LibContainer* container;
};

extern "C" LibTrigTable D_0050CC80;
extern "C" LibTrigQuotients D_0050CD10;
extern "C" LibTrigQuotients D_0050CD00;

/** Packed scalar quotient lane written by VU0 range reduction. */
struct LibScalarTrigQuotient
{
    u32 unk00[3];
    s32 half_turns;
} __attribute__((aligned(16)));
extern "C" LibScalarTrigQuotient D_0050CCF0;
extern "C" LibScalarTrigQuotient D_0050CCD0;
extern "C" LibScalarTrigQuotient D_0050CCE0;
extern "C" LibScalarTrigQuotient D_0050CCC0;

/** @brief View an aligned matrix row as a vector. @param matrix Destination matrix. @param row Row index. @return Writable row vector. */
static inline FieldVec4A& matrix_row_vector(LibMatrix44Value& matrix, s32 row)
{
    return *(FieldVec4A*)matrix.m[row];
}

/** @brief Unlink a container child. @param object Container. @param child Widget to unlink. */
extern "C" void func_004C6120(LibContainer* object, LibWidget* child);

/** Partial text resource fields and the inherited redraw flag. */
typedef struct LibTextResourceState
{
    u8 pad00[0x3C];
    u8 redraw;
    u8 pad3d[0xCB];
    u32 source;
    u32 key;
    u8 flag;
    u8 pending;
} LibTextResourceState;

typedef struct LibPanelAssociation
{
    u8 pad00[0x9C];
    LibPanel* panel;
} LibPanelAssociation;

typedef struct LibPanelAssociationState
{
    u8 pad00[0x60];
    LibPanelAssociation* association;
} LibPanelAssociationState;

extern "C" void func_004BD360(void* object, const unsigned __int128* value)
{
    LibVectorField10View* state = (LibVectorField10View*)object;
    copy_vector(&state->value10, (const LibVector4*)value);
}

const void* func_004BD370(const void* object)
{
    return (const u8*)object + 0x10;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD380);

/** @brief Store a float in an indexed array slot. @param values Float array. @param index Slot index. @param value Value to store. */
extern "C" void func_004BD3C0(float* values, s32 index, float value)
{
    values[index] = value;
}

const void* func_004BD3D0(const void* object)
{
    return (const u8*)object + 0x570;
}

/**
 * @brief Return how many key spans the last wrapped key was past the first key.
 * @return Signed cycle count.
 */
s32 LibClass1784E0::get_cycle_count() const
{
    return state.cycle_count;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD3F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD420);

/**
 * @brief Return how many key spans the last wrapped key was past the first key.
 * @return Signed cycle count.
 */
s32 LibWordTrackBase::get_cycle_count() const
{
    return state.cycle_count;
}

const void* func_004BD4A0(const void* object)
{
    return (const u8*)object + 0x40;
}

const void* func_004BD4B0(const void* object)
{
    return (const u8*)object + 0x20;
}

extern "C" void* func_004BD4C0(void* object, const unsigned __int128* value)
{
    LibVector4* vector = (LibVector4*)object;
    copy_vector(vector, (const LibVector4*)value);
    return object;
}

/**
 * @brief Return how many key spans the last wrapped key was past the first key.
 * @return Signed cycle count.
 */
s32 LibVectorCurveTrackBase::get_cycle_count() const
{
    return state.cycle_count;
}

/**
 * @brief Return how many key spans the last wrapped key was past the first key.
 * @return Signed cycle count.
 */
s32 LibVectorTrackBase::get_cycle_count() const
{
    return state.cycle_count;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD4F0);

/** @brief Apply the frame the animation follows, once a frame has elapsed. */
void LibAnimation::update()
{
    if (g_frame_seconds != 0.0f && frame)
    {
        unk6c = lib_animation_apply_frame(this, *frame, 0) != 0;
    }
}

/**
 * @brief Mark or clear the skip flag of every populated entry bound to a target.
 * @param target Bound target to match.
 * @param skip Nonzero to skip the target's entries, zero to apply them again.
 */
void LibAnimation::set_target_skipped(const void* target, s32 skip)
{
    s32 count = entry_count;

    for (s32 i = 0; i < count; i++)
    {
        if (entries[i].channel && entries[i].target == target)
        {
            if (skip)
            {
                entries[i].flags |= LIB_ANIMATION_ENTRY_SKIP;
            }
            else
            {
                entries[i].flags &= ~LIB_ANIMATION_ENTRY_SKIP;
            }
        }
    }
}

/** @brief Stop following a frame and leave the update list. */
void LibAnimation::stop()
{
    playing = 0;
    frame = 0;
    lib_object_detach_owner(this);
}

/**
 * @brief Follow a frame and join an update list.
 * @param list Update list to join.
 * @param frame Frame to apply on each update.
 */
void LibAnimation::play(LibUpdateList* list, float* frame)
{
    playing = 1;
    this->frame = frame;
    list->append_node(this, LibUpdateList::DEFAULT_NODE_KIND);
}

/**
 * @brief Replace an animation entry's channel and descriptor when its index is below the entry count.
 * @param object Animation object.
 * @param index Entry index; only the upper bound is checked.
 * @param channel Replacement channel.
 * @param kind Entry kind.
 * @param type Entry type.
 * @param flags Entry flags.
 */
extern "C" void lib_animation_set_entry_channel(LibAnimation* object, s32 index, LibClass173180* channel, u8 kind, s16 type, u8 flags)
{
    if (index < object->entry_count)
    {
        object->entries[index].channel = channel;
        object->entries[index].kind = kind;
        object->entries[index].type = type;
        object->entries[index].flags = flags;
    }
}

/**
 * @brief Read and cache an indexed animation channel matching the entry's low flag nibble.
 * @param object Animation object.
 * @param index Entry index; the caller supplies a valid array index.
 * @param nibble Flag value to match against the entry's low nibble.
 * @return Matching channel, or null.
 */
extern "C" LibClass173180* lib_animation_channel_at(LibAnimation* object, s32 index, u8 nibble)
{
    if (!object->entries)
    {
        return 0;
    }
    if (object->entries[index].channel && nibble == (object->entries[index].flags & 0xF))
    {
        object->cached_entry = &object->entries[index];
        return object->cached_entry->channel;
    }
    object->cached_entry = 0;
    return 0;
}

/**
 * @brief Find the channel bound to a target with the requested kind and axis, and cache its entry.
 * @param object Animation object.
 * @param target Bound target to match.
 * @param kind Entry kind.
 * @param axis Axis to match against the entry flags' low nibble.
 * @return Matching channel, or null.
 */
extern "C" LibClass173180* lib_animation_find_channel(LibAnimation* object, const void* target, u8 kind, u8 axis)
{
    return lib_animation_find_channel_inline(object, target, kind, axis);
}

/**
 * @brief Bind populated animation entries whose state names match over up to sixteen characters.
 * @param object Animation object.
 * @param target Vector state to bind.
 * @param name State name to match.
 */
extern "C" void lib_animation_bind_state(LibAnimation* object, LibAnimationTarget* target, const char* name)
{
    s32 count = object->entry_count;
    for (s32 index = 0; index < count; index++)
    {
        LibAnimationEntry14* entry = &object->entries[index];
        if (entry->channel && lib_compare_bounded_strings(entry->state_name, name, 16) == 0)
        {
            object->entries[index].target = target;
        }
    }
}

/**
 * @brief Clear populated animation entries' targets and mark their bindings incomplete.
 * @param object Animation object.
 */
extern "C" void lib_animation_clear_targets(LibAnimation* object)
{
    s32 count = object->entry_count;
    for (s32 index = 0; index < count; index++)
    {
        if (object->entries[index].channel)
        {
            object->entries[index].target = 0;
        }
    }
    object->targets_bound = 0;
}

/**
 * @brief Clear targets for populated animation entries of the requested kind.
 * @param object Animation object.
 * @param kind Entry kind to clear.
 */
extern "C" void lib_animation_clear_targets_by_kind(LibAnimation* object, u8 kind)
{
    s32 count = object->entry_count;
    for (s32 index = 0; index < count; index++)
    {
        if (object->entries[index].channel && kind == object->entries[index].kind)
        {
            object->entries[index].target = 0;
        }
    }
}

/**
 * @brief Clear populated animation entries referencing a particular target.
 * @param object Animation object.
 * @param target Bound target to remove.
 */
extern "C" void lib_animation_clear_matching_target(LibAnimation* object, const void* target)
{
    s32 count = object->entry_count;
    for (s32 index = 0; index < count; index++)
    {
        if (object->entries[index].channel && object->entries[index].target == target)
        {
            object->entries[index].target = 0;
        }
    }
}

/**
 * @brief Delete populated channels and unregister their binding-owner links.
 * @param object Animation object.
 */
extern "C" void lib_animation_release_channels(LibAnimation* object)
{
    if (object->entries)
    {
        s32 count = object->entry_count;
        for (s32 index = 0; index < count; index++)
        {
            if (object->entries[index].channel)
            {
                object->entries[index].channel->release();
                object->entries[index].channel = 0;
            }
        }
        if (object->primary_binding_owner)
        {
            lib_animation_register_binding(object->primary_binding_owner, 0, 0);
            object->primary_binding_owner = 0;
        }
        s32 slot;
        LibAnimationBindingOwner* owner = object->secondary_binding_owner;
        if (owner)
        {
            for (slot = 0; slot < LIB_ANIMATION_BINDING_CAPACITY; slot++)
            {
                if (owner->animation_slots[slot] == object)
                {
                    owner->animation_slots[slot] = 0;
                }
            }
            object->secondary_binding_owner = 0;
        }
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BDE00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", lib_animation_bind_channels);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BFE10);

/**
 * @brief Replace the animation data with a decoded resource buffer.
 * @param object Animation object.
 * @param source Resource header to decode.
 */
extern "C" void lib_animation_load_resource(LibAnimation* object, ResidentResourceHeader* source)
{
    if (object->entries)
    {
        lib_animation_release_channels(object);
        delete[] object->entries;
    }
    if (!object->resource_is_borrowed)
    {
        delete (u8*)object->resource_data;
    }
    object->targets_bound = 0;
    object->resource_is_borrowed = 0;
    u8* data = resident_allocate_decode_buffer(g_resident_resource_decoder, source, 0, 0);
    if (data)
    {
        resident_decode_resource_block(g_resident_resource_decoder, source, data, 0);
        object->resource_data = data;
    }
}

/** @brief Leave the update list, free an owned resource, and release the channels and bindings. */
LibAnimation::~LibAnimation()
{
    if (playing)
    {
        lib_object_detach_owner(this);
    }

    if (!resource_is_borrowed)
    {
        operator delete(resource_data);
    }

    if (entries && !unk6d)
    {
        lib_animation_release_channels(this);
    }

    delete[] entries;
    entries = 0;

    if (primary_binding_owner)
    {
        lib_animation_register_binding(primary_binding_owner, 0, 0);
    }

    s32 slot;
    LibAnimationBindingOwner* owner = secondary_binding_owner;

    if (owner)
    {
        for (slot = 0; slot < LIB_ANIMATION_BINDING_CAPACITY; slot++)
        {
            if (owner->animation_slots[slot] == this)
            {
                owner->animation_slots[slot] = 0;
            }
        }
    }
}

/** @brief Start with no resource, entries or bindings. */
LibAnimation::LibAnimation()
{
    resource_data = 0;
    resource_is_borrowed = 0;
    playing = 0;
    entries = 0;
    frame = 0;
    unk48 = 0;
    started = 0;
    unk6d = 0;
    unk6b = 0;
    cached_entry = 0;
    targets_bound = 0;
    primary_binding_owner = 0;
    secondary_binding_owner = 0;
    object_kind |= LIB_OBJECT_KIND_ANIMATION;
}

/**
 * @brief Evaluate the track at a key, extrapolating past either end, and cache the value and its change per frame.
 * @param key Evaluation key.
 * @return Evaluated vector.
 */
FieldVec4A LibVectorCurveTrack::sample(float key)
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

    if (state.key_count == 1 && (!(key < static_cast<LibVectorCurveTrackKey*>(key_array)[0].value.w) || state.before_mode != LIB_TRACK_END_USE_PRE_START_KEY))
    {
        return *reinterpret_cast<FieldVec4A*>(&static_cast<LibVectorCurveTrackKey*>(key_array)[0].value);
    }

    extrapolate = 0;

    if (key < static_cast<LibVectorCurveTrackKey*>(key_array)[0].value.w && state.before_mode == LIB_TRACK_END_USE_PRE_START_KEY)
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
                return *reinterpret_cast<FieldVec4A*>(&static_cast<LibVectorCurveTrackKey*>(key_array)[0].value);
            }

            if (state.after_mode == LIB_TRACK_END_HOLD && state.cycle_count > 0)
            {
                return *reinterpret_cast<FieldVec4A*>(&static_cast<LibVectorCurveTrackKey*>(key_array)[state.key_count - 1].value);
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
            LibVectorCurveTrackKey* first = lower >= 0 ? static_cast<LibVectorCurveTrackKey*>(key_array) + lower : &single_key;
            s32 last = state.key_count - 1;

            if (upper == last && ((!(key < static_cast<LibVectorCurveTrackKey*>(key_array)[0].value.w) && state.after_mode == LIB_TRACK_END_CYCLE_TO_FIRST) ||
                                  (key < static_cast<LibVectorCurveTrackKey*>(key_array)[0].value.w && state.before_mode == LIB_TRACK_END_CYCLE_TO_FIRST)))
            {
                LibVectorCurveTrackKey* entries = static_cast<LibVectorCurveTrackKey*>(key_array);
                LibVectorCurveTrackKey* second = entries + upper;
                curve_segment.set_endpoints(first->value.w, second->value.w, reinterpret_cast<const FieldVec4A*>(&first->value),
                                            reinterpret_cast<const FieldVec4A*>(&first->out_tangent), reinterpret_cast<const FieldVec4A*>(&entries[0].value),
                                            reinterpret_cast<const FieldVec4A*>(&entries[0].in_tangent));
            }
            else if (lower < upper)
            {
                LibVectorCurveTrackKey* second = static_cast<LibVectorCurveTrackKey*>(key_array) + upper;
                curve_segment.set_endpoints(first->value.w, second->value.w, reinterpret_cast<const FieldVec4A*>(&first->value),
                                            reinterpret_cast<const FieldVec4A*>(&first->out_tangent), reinterpret_cast<const FieldVec4A*>(&second->value),
                                            reinterpret_cast<const FieldVec4A*>(&second->in_tangent));
            }
            else
            {
                LibVectorCurveTrackKey* second = static_cast<LibVectorCurveTrackKey*>(key_array) + last;
                curve_segment.set_endpoints(first->value.w, second->value.w, reinterpret_cast<const FieldVec4A*>(&first->value),
                                            reinterpret_cast<const FieldVec4A*>(&first->out_tangent), reinterpret_cast<const FieldVec4A*>(&second->value),
                                            reinterpret_cast<const FieldVec4A*>(&second->in_tangent));
            }
        }

        result = curve_segment.interpolate(wrapped_key);

        if (state.cycle_count && ((state.before_mode == LIB_TRACK_END_OFFSET_CYCLE && state.cycle_count < 0) ||
            (state.after_mode == LIB_TRACK_END_OFFSET_CYCLE && state.cycle_count > 0)))
        {
            FieldVec4B delta = vector_difference(static_cast<LibVectorCurveTrackKey*>(key_array)[state.key_count - 1].value,
                                          static_cast<LibVectorCurveTrackKey*>(key_array)[0].value);
            result += vector_scaled((float)state.cycle_count, delta);
        }
    }
    else
    {
        FieldVec4B slope;

        if (wrapped_key < key)
        {
            slope = vector_scaled(1.0f / (last_entry(this).value.w - key_of(static_cast<LibVectorCurveTrackKey*>(key_array) + (state.key_count - 2))),
                           static_cast<LibVectorCurveTrackKey*>(key_array)[state.key_count - 1].in_tangent);
            result = vector_sum(static_cast<LibVectorCurveTrackKey*>(key_array)[state.key_count - 1].value, vector_scaled(key - last_entry(this).value.w, slope));
        }
        else
        {
            slope = vector_scaled(1.0f / (key_of(static_cast<LibVectorCurveTrackKey*>(key_array) + 1) - key_of(static_cast<LibVectorCurveTrackKey*>(key_array))),
                           static_cast<LibVectorCurveTrackKey*>(key_array)[0].out_tangent);
            result = vector_sum(static_cast<LibVectorCurveTrackKey*>(key_array)[0].value,
                         vector_scaled(key - static_cast<LibVectorCurveTrackKey*>(key_array)[0].value.w, slope));
        }
    }

    value_rate = vector_scaled(g_inverse_frame_ticks, vector_difference(result, last_value));
    last_value = result;
    return *reinterpret_cast<FieldVec4A*>(&result);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C0CA0);

/**
 * @brief Evaluate the track at a key and cache the value and its change per second.
 * @param key Evaluation key.
 * @return Evaluated vector.
 */
FieldVec4A LibVectorTrack::sample(float key)
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

    if (state.key_count == 1 && (!(key < key_array[0].value.w) || state.before_mode != LIB_TRACK_END_USE_PRE_START_KEY))
    {
        return *reinterpret_cast<FieldVec4A*>(&key_array[0].value);
    }

    if (key < key_array[0].value.w && state.before_mode == LIB_TRACK_END_USE_PRE_START_KEY)
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
            return *reinterpret_cast<FieldVec4A*>(&key_array[0].value);
        }

        if (state.after_mode == LIB_TRACK_END_HOLD && state.cycle_count > 0)
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
        LibVectorTrackKey* first = lower >= 0 ? key_array + lower : &single_key;
        sample_history.reset();
        sample_history.push_sample(first->value.w, reinterpret_cast<const FieldVec4A*>(&first->value));
        s32 last = state.key_count - 1;
        s32 upper_index = upper;

        if (upper_index == last && ((!(key < key_array[0].value.w) && state.after_mode == LIB_TRACK_END_CYCLE_TO_FIRST) ||
            (key < key_array[0].value.w && state.before_mode == LIB_TRACK_END_CYCLE_TO_FIRST)))
        {
            LibVectorTrackKey* entries = key_array;
            LibVectorTrackKey* second = entries + upper_index;
            sample_history.push_sample(second->value.w, reinterpret_cast<const FieldVec4A*>(&entries[0].value));
        }
        else if (lower < upper_index)
        {
            LibVectorTrackKey* second = key_array + upper_index;
            sample_history.push_sample(second->value.w, reinterpret_cast<const FieldVec4A*>(&second->value));
        }
        else
        {
            LibVectorTrackKey* second = key_array + last;
            sample_history.push_sample(second->value.w, reinterpret_cast<const FieldVec4A*>(&key_array[upper_index].value));
        }
    }

    FieldVec4B result = sample_history.sample(wrapped_key);

    if ((state.before_mode == LIB_TRACK_END_OFFSET_CYCLE && state.cycle_count < 0) ||
        (state.after_mode == LIB_TRACK_END_OFFSET_CYCLE && state.cycle_count > 0))
    {
        FieldVec4B delta = vector_difference(key_array[state.key_count - 1].value, key_array[0].value);
        result += vector_scaled((float)state.cycle_count, delta);
    }

    value_rate = vector_scaled(1.0f / g_frame_ticks, vector_difference(result, last_value));
    last_value = result;
    return *reinterpret_cast<FieldVec4A*>(&result);
}

/** @brief Forget the stored samples. */
void LibLinearVectorHistory::reset()
{
    sample_count = 0;
    next_index = 0;
    unk14 = 0;
    unk18 = 0;
}

/** @brief Free the keys. */
LibWordTrackBase::~LibWordTrackBase()
{
    free_keys();
}

/** @brief Reset the keys, counts, modes and cached indices. */
void LibWordTrackBase::reset_state()
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
 * @brief Allocate key storage.
 * @param count Key count.
 */
void LibWordTrackBase::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] key_array;
    key_array = new (0) LibWordTrackKey[count];
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
void LibWordTrackBase::set_before_mode(u32 mode)
{
    state.before_mode = mode;
    state.extends_segment = state.before_mode == LIB_TRACK_END_EXTEND_SEGMENT || state.after_mode == LIB_TRACK_END_EXTEND_SEGMENT;
}

/**
 * @brief Set the end mode used after the last key, and note whether either end extends its segment.
 * @param mode LIB_TRACK_END_* mode.
 */
void LibWordTrackBase::set_after_mode(u32 mode)
{
    state.after_mode = mode;
    state.extends_segment = state.before_mode == LIB_TRACK_END_EXTEND_SEGMENT || state.after_mode == LIB_TRACK_END_EXTEND_SEGMENT;
}

/**
 * @brief Return the number of stored keys.
 * @return Key count.
 */
s16 LibWordTrackBase::get_key_count() const
{
    return state.key_count;
}

/**
 * @brief Return the number of keys the storage can hold.
 * @return Key capacity.
 */
s16 LibWordTrackBase::get_key_capacity()
{
    return state.key_capacity;
}

/**
 * @brief Return the last sampled value; the base has none.
 * @return Zero.
 */
u32 LibWordTrackBase::get_last_value()
{
    return 0;
}

/**
 * @brief Evaluate the track.
 * @param key Key position.
 * @param output Receives the word.
 */
void LibWordTrackBase::evaluate(float key, void* output)
{
    *(u32*)output = sample(key);
}

/**
 * @brief Return the key storage.
 * @return Key array, or null.
 */
void* LibWordTrackBase::get_keys()
{
    return key_array;
}

/** @brief Delete the key storage unless it is external, and clear the key pointer. */
void LibWordTrackBase::free_keys()
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
float LibVectorCurveTrackBase::update_cycle_count(float key)
{
    float first = static_cast<LibVectorCurveTrackKey*>(key_array)[0].value.w;
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
            LibVectorCurveTrackKey* last_entry = static_cast<LibVectorCurveTrackKey*>(key_array) + last_index;
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
u8 LibVectorCurveTrackBase::find_surrounding_keys(float key, s32* lower, s32* upper)
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

    while (index > 0 && key < static_cast<LibVectorCurveTrackKey*>(key_array)[index].value.w)
    {
        index--;
    }

    index = clamp_low(index, 0);

    while ((next = index + 1) < count && !(key < static_cast<LibVectorCurveTrackKey*>(key_array)[next].value.w))
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
 * @brief Wrap a key into the key span and record how many spans it was past the first key.
 * @param key Key to wrap.
 * @return Wrapped key, reflected on odd cycles in ping-pong mode.
 */
float LibVectorTrackBase::update_cycle_count(float key)
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

        if ((state.before_mode == LIB_TRACK_END_PING_PONG && state.cycle_count < 0) || (state.after_mode == LIB_TRACK_END_PING_PONG && state.cycle_count > 0))
        {
            s32 last_index = state.key_count - 1;
            LibVectorTrackKey* last_entry = key_array + last_index;
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
 * @brief Find the keys around a key, starting from the cached search index.
 * @param key Key to place.
 * @param lower Receives the lower key index.
 * @param upper Receives the upper key index.
 * @return One when an end mode extends the first or last segment, otherwise zero.
 */
u8 LibVectorTrackBase::find_surrounding_keys(float key, s32* lower, s32* upper)
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

    while (index > 0 && key < static_cast<LibVectorTrackKey*>(key_array)[index].value.w)
    {
        index--;
    }

    index = clamp_low(index, 0);

    while ((next = index + 1) < count && !(key < static_cast<LibVectorTrackKey*>(key_array)[next].value.w))
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1C20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1D30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1E50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1F60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2080);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C21A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C22B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C23C0);

/**
 * @brief Wrap a key by whole spans between the first and last keys.
 * @param key Key position.
 * @return Wrapped key.
 */
float LibWordTrackBase::wrap_key(float key) const
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
 * @brief Return the value of the key at a position.
 * @param key Key position.
 * @return Key value, or zero when no key is there.
 */
u32 LibWordTrackBase::find_key_value(float key)
{
    s32 index;

    for (index = 0; index < state.key_count; index++)
    {
        if (key == key_array[index].key)
        {
            LibWordTrackKey* entry = key_array + index;
            return entry->value;
        }
    }

    return 0;
}

/**
 * @brief Return the last key minus the first, or zero below two keys.
 * @return Key span.
 */
float LibWordTrackBase::get_key_span() const
{
    s32 last_index;
    LibWordTrackKey* last_entry;

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
s32 LibWordTrackBase::has_key(float key) const
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
 * @brief Store the single key used before key storage exists.
 * @param value Key value.
 * @param key Key position.
 */
void LibWordTrackBase::set_single_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    on_set_single_key(value, key);
}

/**
 * @brief Store the single key; the base ignores it.
 * @param value Key value.
 * @param key Key position.
 */
void LibWordTrackBase::on_set_single_key(const void* value, float key)
{
}

/**
 * @brief Insert a key before an index.
 * @param index Key index.
 * @param key Key position.
 * @param value Key value.
 * @return Nonzero when the key was stored.
 */
s32 LibWordTrackBase::insert_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    return on_insert_key(index, key, value);
}

/**
 * @brief Insert a key; the base ignores it.
 * @param index Key index.
 * @param key Key position.
 * @param value Key value.
 * @return Zero.
 */
s32 LibWordTrackBase::on_insert_key(s32 index, float key, const void* value)
{
    return 0;
}

/**
 * @brief Replace an indexed key.
 * @param index Key index.
 * @param key Key position.
 * @param value Key value.
 * @return Nonzero when the key was stored.
 */
s32 LibWordTrackBase::replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    return on_replace_key(index, key, value);
}

/**
 * @brief Replace a key; the base ignores it.
 * @param index Key index.
 * @param key Key position.
 * @param value Key value.
 * @return Zero.
 */
s32 LibWordTrackBase::on_replace_key(s32 index, float key, const void* value)
{
    return 0;
}

/**
 * @brief Append a key.
 * @param value Key value.
 * @param in_tangent Optional incoming tangent.
 * @param out_tangent Optional outgoing tangent.
 * @param key Key position.
 * @return Nonzero when the key was stored.
 */
s32 LibWordTrackBase::append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    return on_append_key(value, in_tangent, out_tangent, key);
}

/**
 * @brief Append a key; the base ignores it.
 * @param value Key value.
 * @param in_tangent Incoming tangent.
 * @param out_tangent Outgoing tangent.
 * @param key Key position.
 * @return Zero.
 */
s32 LibWordTrackBase::on_append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    return 0;
}

/**
 * @brief Use external key storage and cache its key span.
 * @param count Key count.
 * @param keys External keys.
 */
void LibWordTrackBase::bind_keys(s32 count, void* keys)
{
    s32 last_index = count - 1;
    state.external_keys = 1;
    key_array = (LibWordTrackKey*)keys;
    state.key_capacity = count;
    state.key_count = count;
    state.span = key_array[last_index].key - key_array[0].key;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C27C0);

/**
 * @brief Store the single key and evaluate it before the first array key.
 * @param value Key value.
 * @param key Key position.
 */
void LibWordKeyTrack::on_set_single_key(const void* value, float key)
{
    set_before_mode(LIB_TRACK_END_USE_PRE_START_KEY);
    single_key.value = *(const u32*)value;
    single_key.key = key;
}

/**
 * @brief Read an indexed key.
 * @param index Key index, checked against the capacity.
 * @param key Optionally receives the key position.
 * @param value Optionally receives the key value.
 * @return One when the key is available, otherwise zero.
 */
s32 LibWordKeyTrack::read_key(s32 index, float* key, void* value, void* first, void* second) const
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
        *(u32*)value = key_array[index].value;
    }

    return 1;
}

/**
 * @brief Insert a key before an index and shift the following keys.
 * @param index Key index below the key count.
 * @param key Key position.
 * @param value Key value.
 * @return One when inserted, or zero when storage is absent, full, or the index is too large.
 */
s32 LibWordKeyTrack::on_insert_key(s32 index, float key, const void* value)
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
        LibWordTrackKey* destination = &key_array[cursor];
        LibWordTrackKey* source = &key_array[cursor - 1];
        destination->key = source->key;
        destination->value = source->value;
    }

    key_array[index].value = *(const u32*)value;
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
 * @brief Replace an indexed key and update the span when it is the last key.
 * @param index Key index, checked against the capacity.
 * @param key Key position.
 * @param value Key value.
 * @return One when stored, or zero when storage is absent or the index is too large.
 */
s32 LibWordKeyTrack::on_replace_key(s32 index, float key, const void* value)
{
    if (key_array == 0)
    {
        return 0;
    }

    if (index >= state.key_capacity)
    {
        return 0;
    }

    key_array[index].value = *(const u32*)value;
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
 * @brief Append a key and update the key span.
 * @param value Key value.
 * @param in_tangent Unused incoming tangent.
 * @param out_tangent Unused outgoing tangent.
 * @param key Key position.
 * @return One when appended, or zero when storage is absent or full.
 */
s32 LibWordKeyTrack::on_append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    if (key_array == 0)
    {
        return 0;
    }

    if (state.key_count >= state.key_capacity)
    {
        return 0;
    }

    key_array[state.key_count].value = *(const u32*)value;
    key_array[state.key_count].key = key;
    state.span = key - key_array[0].key;
    state.segment_lower = -1;
    state.segment_upper = -1;
    state.key_count++;
    return 1;
}

/** @brief Clear the last sampled value, then reset the key state. */
void LibVectorCurveTrack::reset_state()
{
    last_value = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    LibVectorCurveTrackBase::reset_state();
}

/** @brief Clear the last sampled value, then reset the key state. */
void LibVectorTrack::reset_state()
{
    last_value = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    LibVectorTrackBase::reset_state();
}

/**
 * @brief Reset 48-byte record storage, counts, packed controls, and cached indices.
 */
void LibVectorCurveTrackBase::reset_state()
{
    static_cast<LibVectorCurveTrackKey*>(key_array) = 0;
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

/** @brief Reset the keys, counts, modes and cached indices. */
void LibVectorTrackBase::reset_state()
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
 * @brief Multiply two quaternions.
 * @param first Left factor.
 * @param second Right factor.
 * @return first * second.
 */
static inline FieldVec4B quaternion_product(const FieldVec4B& first, const FieldVec4B& second)
{
    FieldVec4B result;
    result.x = first.w * second.x + second.w * first.x + first.y * second.z - first.z * second.y;
    result.y = first.w * second.y + second.w * first.y + first.z * second.x - first.x * second.z;
    result.z = first.w * second.z + second.w * first.z + first.x * second.y - first.y * second.x;
    result.w = first.w * second.w - first.x * second.x - first.y * second.y - first.z * second.z;
    return result;
}

/**
 * @brief Add the channel pose to the changes kept at the last update and renormalize the rotation change.
 * @param object Animation target.
 */
void func_004C2CD0(LibAnimationTarget* object)
{
    object->translation_delta += object->channel_translation;
    object->scale_delta += object->channel_scale;
    object->orientation_delta = quaternion_product(object->channel_rotation, object->orientation_delta);
    lib_normalize_quaternion(&object->orientation_delta);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", __ct__18LibAnimationTargetFv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2F50);

/**
 * @brief Copy the position and keep its change from the previous position.
 * @param value New position.
 */
void LibAnimationTarget::copy_translation(const LibVector4* value)
{
    LibVector4* previous = &translation;

    if (has_translation)
    {
        translation_delta.x = value->x - previous->x;
        translation_delta.y = value->y - previous->y;
        translation_delta.z = value->z - previous->z;
    }
    else
    {
        has_translation = 1;
    }

    transform_dirty = 1;
    copy_vector(&translation, value);
}

/**
 * @brief Copy the position and keep its change from the previous position.
 * @param value New position.
 */
void LibAnimationTarget::set_translation_vector(const LibVector4* value)
{
    LibVector4* previous = &translation;

    if (has_translation)
    {
        translation_delta.x = value->x - previous->x;
        translation_delta.y = value->y - previous->y;
        translation_delta.z = value->z - previous->z;
    }
    else
    {
        has_translation = 1;
    }

    transform_dirty = 1;
    copy_vector(&translation, value);
}

/**
 * @brief Set the position, w of one, and keep its change from the previous position.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void LibAnimationTarget::set_translation(float x, float y, float z)
{
    LibVector4* previous = &translation;

    if (has_translation)
    {
        translation_delta.x = x - previous->x;
        translation_delta.y = y - previous->y;
        translation_delta.z = z - previous->z;
    }
    else
    {
        has_translation = 1;
    }

    transform_dirty = 1;
    translation.x = x;
    translation.y = y;
    translation.z = z;
    translation.w = 1.0f;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3120);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3240);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3360);

/**
 * @brief Copy the scale and keep its change from the previous scale.
 * @param value New scale.
 */
void LibAnimationTarget::copy_scale(const LibVector4* value)
{
    LibVector4* previous = &scale;

    if (has_scale)
    {
        scale_delta.x = value->x - previous->x;
        scale_delta.y = value->y - previous->y;
        scale_delta.z = value->z - previous->z;
    }
    else
    {
        has_scale = 1;
    }

    transform_dirty = 1;
    copy_vector(&scale, value);
}

/**
 * @brief Copy the scale and keep its change from the previous scale.
 * @param value New scale.
 */
void LibAnimationTarget::set_scale_vector(const LibVector4* value)
{
    LibVector4* previous = &scale;

    if (has_scale)
    {
        scale_delta.x = value->x - previous->x;
        scale_delta.y = value->y - previous->y;
        scale_delta.z = value->z - previous->z;
    }
    else
    {
        has_scale = 1;
    }

    transform_dirty = 1;
    copy_vector(&scale, value);
}

/**
 * @brief Set the scale's xyz and keep its change from the previous scale.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void LibAnimationTarget::set_scale(float x, float y, float z)
{
    LibVector4* previous = &scale;

    if (has_scale)
    {
        scale_delta.x = x - previous->x;
        scale_delta.y = y - previous->y;
        scale_delta.z = z - previous->z;
    }
    else
    {
        has_scale = 1;
    }

    transform_dirty = 1;
    scale.x = x;
    scale.y = y;
    scale.z = z;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3590);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C39A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3A50);

s32 func_004C3AC0(void* object)
{
    return 0;
}

s32 func_004C3AD0(void* object)
{
    return 0;
}

void func_004C3AE0(void* object)
{
}

void func_004C3AF0(void* object)
{
}

/** @brief Free the keys. */
LibClass1784E0::~LibClass1784E0()
{
    free_keys();
}

/** @brief Reset the keys, counts, modes and cached indices. */
void LibClass1784E0::reset_state()
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
 * @brief Allocate key storage.
 * @param count Key count.
 */
void LibClass1784E0::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] key_array;
    key_array = new (0) LibWordTrackKey[count];
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
void LibClass1784E0::set_before_mode(u32 mode)
{
    state.before_mode = mode;
    state.extends_segment = state.before_mode == LIB_TRACK_END_EXTEND_SEGMENT || state.after_mode == LIB_TRACK_END_EXTEND_SEGMENT;
}

/**
 * @brief Set the end mode used after the last key, and note whether either end extends its segment.
 * @param mode LIB_TRACK_END_* mode.
 */
void LibClass1784E0::set_after_mode(u32 mode)
{
    state.after_mode = mode;
    state.extends_segment = state.before_mode == LIB_TRACK_END_EXTEND_SEGMENT || state.after_mode == LIB_TRACK_END_EXTEND_SEGMENT;
}

/**
 * @brief Return the number of stored keys.
 * @return Key count.
 */
s16 LibClass1784E0::get_key_count() const
{
    return state.key_count;
}

/**
 * @brief Return the number of keys the storage can hold.
 * @return Key capacity.
 */
s16 LibClass1784E0::get_key_capacity()
{
    return state.key_capacity;
}

/**
 * @brief Return the last sampled value; the base has none.
 * @return Zero.
 */
u32 LibClass1784E0::get_last_value()
{
    return 0;
}

/**
 * @brief Evaluate the track.
 * @param key Key position.
 * @param output Receives the word.
 */
void LibClass1784E0::evaluate(float key, void* output)
{
    *(u32*)output = sample(key);
}

/**
 * @brief Return the key storage.
 * @return Key array, or null.
 */
void* LibClass1784E0::get_keys()
{
    return key_array;
}

/** @brief Delete the key storage unless it is external, and clear the key pointer. */
void LibClass1784E0::free_keys()
{
    if (!state.external_keys)
    {
        delete[] key_array;
    }

    key_array = 0;
}

/**
 * @brief Wrap a key by whole spans between the first and last keys.
 * @param key Key position.
 * @return Wrapped key.
 */
float LibClass1784E0::wrap_key(float key) const
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
 * @brief Return the value of the key at a position.
 * @param key Key position.
 * @return Key value, or zero when no key is there.
 */
u32 LibClass1784E0::find_key_value(float key)
{
    s32 index;

    for (index = 0; index < state.key_count; index++)
    {
        if (key == key_array[index].key)
        {
            LibWordTrackKey* entry = key_array + index;
            return entry->value;
        }
    }

    return 0;
}

/**
 * @brief Return the last key minus the first, or zero below two keys.
 * @return Key span.
 */
float LibClass1784E0::get_key_span() const
{
    s32 last_index;
    LibWordTrackKey* last_entry;

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
s32 LibClass1784E0::has_key(float key) const
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
 * @brief Store the single key used before key storage exists.
 * @param value Key value.
 * @param key Key position.
 */
void LibClass1784E0::set_single_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    on_set_single_key(value, key);
}

/**
 * @brief Store the single key; the base ignores it.
 * @param value Key value.
 * @param key Key position.
 */
void LibClass1784E0::on_set_single_key(const void* value, float key)
{
}

/**
 * @brief Insert a key before an index.
 * @param index Key index.
 * @param key Key position.
 * @param value Key value.
 * @return Nonzero when the key was stored.
 */
s32 LibClass1784E0::insert_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    return on_insert_key(index, key, value);
}

/**
 * @brief Insert a key; the base ignores it.
 * @param index Key index.
 * @param key Key position.
 * @param value Key value.
 * @return Zero.
 */
s32 LibClass1784E0::on_insert_key(s32 index, float key, const void* value)
{
    return 0;
}

/**
 * @brief Replace an indexed key.
 * @param index Key index.
 * @param key Key position.
 * @param value Key value.
 * @return Nonzero when the key was stored.
 */
s32 LibClass1784E0::replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    return on_replace_key(index, key, value);
}

/**
 * @brief Replace a key; the base ignores it.
 * @param index Key index.
 * @param key Key position.
 * @param value Key value.
 * @return Zero.
 */
s32 LibClass1784E0::on_replace_key(s32 index, float key, const void* value)
{
    return 0;
}

/**
 * @brief Append a key.
 * @param value Key value.
 * @param in_tangent Optional incoming tangent.
 * @param out_tangent Optional outgoing tangent.
 * @param key Key position.
 * @return Nonzero when the key was stored.
 */
s32 LibClass1784E0::append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    return on_append_key(value, in_tangent, out_tangent, key);
}

/**
 * @brief Append a key; the base ignores it.
 * @param value Key value.
 * @param in_tangent Incoming tangent.
 * @param out_tangent Outgoing tangent.
 * @param key Key position.
 * @return Zero.
 */
s32 LibClass1784E0::on_append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    return 0;
}

/**
 * @brief Use external key storage and cache its key span.
 * @param count Key count.
 * @param keys External keys.
 */
void LibClass1784E0::bind_keys(s32 count, void* keys)
{
    s32 last_index = count - 1;
    state.external_keys = 1;
    key_array = (LibWordTrackKey*)keys;
    state.key_capacity = count;
    state.key_count = count;
    state.span = key_array[last_index].key - key_array[0].key;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4100);

/**
 * @brief Store the single key and evaluate it before the first array key.
 * @param value Key value.
 * @param key Key position.
 */
void LibClass178450::on_set_single_key(const void* value, float key)
{
    set_before_mode(LIB_TRACK_END_USE_PRE_START_KEY);
    single_key.value = *(const u32*)value;
    single_key.key = key;
}

/**
 * @brief Read an indexed key.
 * @param index Key index, checked against the capacity.
 * @param key Optionally receives the key position.
 * @param value Optionally receives the key value.
 * @return One when the key is available, otherwise zero.
 */
s32 LibClass178450::read_key(s32 index, float* key, void* value, void* first, void* second) const
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
        *(u32*)value = key_array[index].value;
    }

    return 1;
}

/**
 * @brief Insert a key before an index and shift the following keys.
 * @param index Key index below the key count.
 * @param key Key position.
 * @param value Key value.
 * @return One when inserted, or zero when storage is absent, full, or the index is too large.
 */
s32 LibClass178450::on_insert_key(s32 index, float key, const void* value)
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
        LibWordTrackKey* destination = &key_array[cursor];
        LibWordTrackKey* source = &key_array[cursor - 1];
        destination->key = source->key;
        destination->value = source->value;
    }

    key_array[index].value = *(const u32*)value;
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
 * @brief Replace an indexed key and update the span when it is the last key.
 * @param index Key index, checked against the capacity.
 * @param key Key position.
 * @param value Key value.
 * @return One when stored, or zero when storage is absent or the index is too large.
 */
s32 LibClass178450::on_replace_key(s32 index, float key, const void* value)
{
    if (key_array == 0)
    {
        return 0;
    }

    if (index >= state.key_capacity)
    {
        return 0;
    }

    key_array[index].value = *(const u32*)value;
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
 * @brief Append a key and update the key span.
 * @param value Key value.
 * @param in_tangent Unused incoming tangent.
 * @param out_tangent Unused outgoing tangent.
 * @param key Key position.
 * @return One when appended, or zero when storage is absent or full.
 */
s32 LibClass178450::on_append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    if (key_array == 0)
    {
        return 0;
    }

    if (state.key_count >= state.key_capacity)
    {
        return 0;
    }

    key_array[state.key_count].value = *(const u32*)value;
    key_array[state.key_count].key = key;
    state.span = key - key_array[0].key;
    state.segment_lower = -1;
    state.segment_upper = -1;
    state.key_count++;
    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4470);

/**
 * @brief Return the last key's value.
 * @return Last key value.
 */
u32 LibWordTrack::get_last_value()
{
    return key_array[state.key_count - 1].value;
}

extern "C" void func_004C4500(void* object)
{
}

extern "C" void func_004C4510(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4520);

/**
 * @brief Find the keys around a position, starting from the cached search index.
 * @param key Key position.
 * @param lower Receives the lower key index.
 * @param upper Receives the upper key index.
 * @return One when an end mode extends the first or last segment, otherwise zero.
 */
u8 LibWordTrackBase::find_surrounding_keys(float key, s32* lower, s32* upper)
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
 * @brief Wrap a key across the span and store its signed cycle count.
 * @param key Key position.
 * @return Wrapped key, reflected on odd ping-pong cycles.
 */
float LibWordTrackBase::update_cycle_count(float key)
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

        if ((state.before_mode == LIB_TRACK_END_PING_PONG && state.cycle_count < 0) ||
            (state.after_mode == LIB_TRACK_END_PING_PONG && state.cycle_count > 0))
        {
            s32 last_index = state.key_count - 1;
            LibWordTrackKey* last_entry = key_array + last_index;
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

/** @brief Queue a widget outside any container for release, once, and stop it being active. */
void LibWidget::destroy()
{
    if (!unk3a)
    {
        if (!container)
        {
            resident_enqueue_object(g_resident_release_queues, this);
        }

        unk39 = 0;
        unk3a = 1;
    }
}

/** @brief Unlink the widget from its container before detaching its owner. */
LibWidget::~LibWidget()
{
    if (container)
    {
        func_004C6120(container, this);
    }
}

/** @brief Initialize the widget rectangle, container reference, and state bytes. */
LibWidget::LibWidget()
{
    unk18.unk0c = 0.0f;
    unk18.unk08 = 0.0f;
    unk18.unk04 = 0.0f;
    unk18.unk00 = 0.0f;
    unk38 = 0;
    container = 0;
    draw_alpha = 128.0f;
    packet_tag = 0;
    packet = 0;
    unk34 = 0;
    unk39 = 0;
    unk3a = 0;
    unk3d = 1;
    unk3e = 1;
    visible = 1;
    unk3b = 0;
    needs_redraw = 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4A00);

extern "C" void lib_panel_detach(LibPanel* object)
{
    LibPanelAssociationState* state = (LibPanelAssociationState*)object;
    if (state->association != 0)
    {
        state->association->panel = 0;
        state->association = 0;
    }
}

/** Panel transform with its callback interface at 0x90. */
class FieldClass15BA90 : public LibTransformOwner, public LibDmaCallbacks
{
public:
    /** @brief Initialize the panel transform and its callback interface. */
    FieldClass15BA90();
    /** @brief Release the association and destroy the transform. */
    virtual ~FieldClass15BA90();
    /** @brief Set the transform translation. @param x Horizontal component. @param y Vertical component. @param z Third component. */
    virtual void set_translation(float x, float y, float z);
    void* unk94;
    u8 unk98[4];
    LibPanel* panel;
    u8 pending;
    u8 unka1[0xF];
};
extern "C" s32 func_002F99F0(FieldClass15BA90*, LibPanel*);

extern "C" s32 lib_panel_init_transform(LibPanel* object, float z)
{
    object->unk60 = new (0) FieldClass15BA90;
    if (object->unk60 == 0)
        return 0;
    if (func_002F99F0((FieldClass15BA90*)object->unk60, object) == 0)
        return 0;
    ((FieldClass15BA90*)object->unk60)->set_translation(0.0f, 0.0f, z);
    if (object->unk8c != 0)
    {
        ((FieldClass15BA90*)object->unk60)->pending = 1;
        object->unk8c = 0;
    }
    ((LibUpdateList*)g_renderer)->append_node(object->unk60, -1);
    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4B90);

typedef struct LibPanelColorState
{
    u8 pad00[0x3C];
    u8 redraw;
    u8 pad3d[0x27];
    u32 colors[4];
} LibPanelColorState;

/**
 * @brief Set the four panel colors and mark the panel for redraw.
 * @param object Panel widget.
 * @param colors Packed colors whose low 24 bits are stored.
 */
extern "C" void lib_panel_set_colors(LibPanel* object, const LibWidgetColors4C5590* colors)
{
    LibPanelColorState* state = (LibPanelColorState*)object;
    state->colors[0] = colors->values[0] & 0xFFFFFF;
    state->colors[1] = colors->values[1] & 0xFFFFFF;
    state->colors[2] = colors->values[2] & 0xFFFFFF;
    state->colors[3] = colors->values[3] & 0xFFFFFF;
    state->redraw = 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C55E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C56E0);

/** Partial resident panel defaults containing the four packed colors. */
struct LibPanelDefaults
{
    u8 pad00[0x10];
    u32 colors[4];
};
struct LibPanelContext
{
    u8 pad00[0x554];
    LibPanelDefaults* defaults;
};
struct LibPanelInitState
{
    u8 pad00[0x64];
    u32 colors[4];
    u8 pad74[0x10];
    float extra;
    u8 unk88;
    u8 unk89;
    u8 mode;
    u8 unk8b;
    u8 pending;
};
/**
 * @brief Allocate panel drawing storage and initialize its rectangle and colors.
 * @param object Panel widget.
 * @param mode Drawing mode, stored as a byte.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @param extra Additional drawing coordinate.
 * @return One on successful setup, or zero if storage cannot be allocated.
 */
extern "C" s32 lib_panel_init_rectangle(LibPanel* object, s32 mode, float x, float y, float width, float height, float extra)
{
    object->unk18.unk00 = x;
    object->unk18.unk04 = y;
    object->unk18.unk08 = width;
    object->unk18.unk0c = height;
    if (!lib_allocate_drawing_storage(&object->unk40, 0x44))
    {
        return 0;
    }
    LibPanelDefaults* defaults = ((LibPanelContext*)g_field_runtime)->defaults;
    LibPanelInitState* state = (LibPanelInitState*)object;
    state->colors[0] = defaults->colors[0] & 0xFFFFFF;
    state->colors[1] = defaults->colors[1] & 0xFFFFFF;
    state->colors[2] = defaults->colors[2] & 0xFFFFFF;
    state->colors[3] = defaults->colors[3] & 0xFFFFFF;
    object->needs_redraw = 1;
    object->unk34 = 0;
    state->extra = extra;
    state->mode = mode;
    state->unk88 = 0;
    state->unk8b = 0;
    state->pending = 1;
    object->unk60 = 0;
    object->unk39 = 1;
    return 1;
}

/** Archive resources holding the shared font's chunk list and its texture block. */
enum
{
    LIB_SHARED_FONT_CHUNKS_KEY = 8,
    LIB_SHARED_FONT_TEXTURES_KEY = 9
};

#define LIB_SHARED_FONT_REQUEST_TAG 0x80000000
#define LIB_SHARED_FONT_REQUEST_PRIORITY 0x34BC0
#define LIB_SHARED_FONT_REQUEST_READ 1
#define LIB_SHARED_FONT_ALIGNMENT 0x80

/** Tag of the chunk that ends a shared font chunk list. */
#define LIB_FONT_CHUNK_END 'END'

/** VRAM block addresses of the font palettes and of the glyph pages. */
enum
{
    LIB_SHARED_FONT_PALETTE_BLOCK = 0x3FF4,
    LIB_SHARED_FONT_IMAGE_BLOCK = 0x800,
    LIB_FONT_CHUNK0_PALETTE_BLOCK = 0x3FFC,
    LIB_FONT_CHUNK0_IMAGE_BLOCK = 0,
    LIB_FONT_CHUNK1_PALETTE_BLOCK = 0x3FF8,
    LIB_FONT_CHUNK1_IMAGE_BLOCK = 0x400
};

/** Packet operation that uploads a LibImageUpload. */
#define LIB_PACKET_LOAD_IMAGE 1

/**
 * @brief Upload a font resource's glyph pages to VRAM.
 * @param source Decoded font resource.
 * @param start First VRAM page.
 * @param count Number of glyph pages to upload.
 * @return First byte after the uploaded pages.
 */
extern "C" u8* func_00451C00(void* source, s32 start, s32 count);

/** Stored image transfer packet: tags and transfer registers, with the pixels after them. */
struct LibImagePacket
{
    u8 unk00[0x10];
    GsGifTag tag;
    GsRegisterValue bitbltbuf;
    GsRegisterValue trxpos;
    GsRegisterValue trxreg;
    GsRegisterValue trxdir;
    GsGifTag image_tag;
    u8 unk70[0x10];
    u8 pixels[1];
};

/** Glyph page image of a font texture block. */
struct LibFontImage
{
    s16 width;
    s16 height;
    u8 unk04[4];

    /** Offset of its LibImagePacket from the texture header. */
    s32 packet_offset;
};

/** Header of a decoded font texture block, 0x10 bytes into the block. */
struct LibFontTextureHeader
{
    u8 unk00[0xC];

    /** Offset of the glyph page's LibFontImage from this header. */
    s32 image_offset;

    u8 unk10[4];

    /** Offset of the palette's LibImagePacket from this header. */
    s32 palette_offset;

    s16 palette_format;
};

/** Decoded glyph table chunk. */
struct LibFontGlyphHeader
{
    u8 unk00[0x1C];

    /** Bytes of the table copied into the shared font. */
    u32 table_size;

    s32 glyph_count;
};

/** One entry of the shared font's chunk list, followed by its compressed resource. */
struct LibFontChunk
{
    u32 tag;
    u8 unk04[8];

    /** Offset of the next chunk from this one, or zero for none. */
    s32 next_offset;

    ResidentResourceHeader resource;
};

/** Image transfer packet and the pixels it sends. */
struct LibImageUpload
{
    GsLoadImage packet;
    const void* pixels;
};

/** The shared font stored in the resident entry table. */
struct LibSharedFont
{
    void* glyphs;
    void* metrics;
    u8 unk08[0x78];
    u8 glyph_data[0x200];
    u8 metric_data[0x2A00];
};

/**
 * @brief Upload a font texture block's palette and glyph page to VRAM and wait for the packets.
 * @param block Decoded texture block.
 * @param palette_block VRAM block address for the palette, or zero to skip it.
 * @param image_block VRAM block address for the glyph page.
 */
static inline void upload_font_texture(void* block, u16 palette_block, u16 image_block)
{
    LibFontTextureHeader* header = (LibFontTextureHeader*)((u8*)block + 0x10);

    if (palette_block)
    {
        LibImagePacket* palette = (LibImagePacket*)((u8*)header + header->palette_offset);
        LibImageUpload upload;
        sceGsSetDefLoadImage(&upload.packet, palette_block,
                             (palette->bitbltbuf.data >> GS_BITBLTBUF_DBW_SHIFT) & GS_BITBLTBUF_DBW_MASK,
                             header->palette_format, 0, 0, palette->trxreg.data & GS_TRXREG_SIZE_MASK,
                             (palette->trxreg.data >> GS_TRXREG_RRH_SHIFT) & GS_TRXREG_SIZE_MASK);
        upload.pixels = palette->pixels;
        FlushCache(0);
        func_004DC4F0(g_packet_queue, LIB_PACKET_LOAD_IMAGE, 0, &upload, 0, 0);
    }

    LibFontImage* image = (LibFontImage*)((u8*)header + header->image_offset);
    LibImagePacket* packet = (LibImagePacket*)((u8*)header + image->packet_offset);
    LibImageUpload upload;
    sceGsSetDefLoadImage(&upload.packet, image_block,
                         (packet->bitbltbuf.data >> GS_BITBLTBUF_DBW_SHIFT) & GS_BITBLTBUF_DBW_MASK, GS_PSMT4HH,
                         0, 0, image->width, image->height);
    upload.pixels = packet->pixels;
    FlushCache(0);
    func_004DC4F0(g_packet_queue, LIB_PACKET_LOAD_IMAGE, 0, &upload, 0, 0);
    func_004DBEE0(g_packet_queue, 0);
}

/**
 * @brief Load the shared font, upload its textures and store it in the resident entry table.
 * @param data_chunks Loaded chunk list, or null to read archive resources 8 and 9.
 * @param source Loaded texture block; read from the archive when data_chunks is null.
 * @return One when the font is loaded, or zero when an allocation or decode fails.
 */
extern "C" s32 lib_load_shared_font(LibFontChunk* data_chunks, ResidentResourceHeader* source)
{
    LibSharedFont* font = (LibSharedFont*)memalign(LIB_SHARED_FONT_ALIGNMENT, sizeof(LibSharedFont));

    if (!font)
    {
        return 0;
    }

    func_001014B0(resident_get_entry_table(resident_get_system()), font, LIB_ENTRY_SHARED_FONT);
    u8* archive_data = 0;
    LibFontChunk* chunks;

    if (!data_chunks)
    {
        ResidentArchive* archive = resident_get_archive(resident_get_system());
        u32 chunk_size = resident_get_resource_size(archive, LIB_SHARED_FONT_CHUNKS_KEY);
        archive_data = (u8*)memalign(LIB_SHARED_FONT_ALIGNMENT,
                                     chunk_size + resident_get_resource_size(archive, LIB_SHARED_FONT_TEXTURES_KEY));

        if (!archive_data)
        {
            return 0;
        }

        FlushCache(0);
        chunks = (LibFontChunk*)archive_data;
        source = (ResidentResourceHeader*)(archive_data + chunk_size);
        resident_queue_resource_request(g_resource_queue, LIB_SHARED_FONT_CHUNKS_KEY, chunks, LIB_SHARED_FONT_REQUEST_TAG,
                                        LIB_SHARED_FONT_REQUEST_PRIORITY, 0, 0, 0, LIB_SHARED_FONT_REQUEST_READ);
        resident_queue_resource_request(g_resource_queue, LIB_SHARED_FONT_TEXTURES_KEY, source, LIB_SHARED_FONT_REQUEST_TAG,
                                        LIB_SHARED_FONT_REQUEST_PRIORITY, 0, 0, 0, LIB_SHARED_FONT_REQUEST_READ);

        while (resident_find_resource_request(g_resource_queue, LIB_SHARED_FONT_CHUNKS_KEY, (u32)chunks, LIB_SHARED_FONT_REQUEST_TAG,
                                              0xFFFFFFFF, 0))
        {
        }

        while (resident_find_resource_request(g_resource_queue, LIB_SHARED_FONT_TEXTURES_KEY, (u32)source,
                                              LIB_SHARED_FONT_REQUEST_TAG, 0xFFFFFFFF, 0))
        {
        }
    }
    else
    {
        chunks = data_chunks;
    }

    ResidentDecodeObject* decoder = func_001012B0(resident_get_system());
    void* block = memalign(LIB_SHARED_FONT_ALIGNMENT, source->decoded_size);

    if (!block)
    {
        return 0;
    }

    FlushCache(0);

    if (!resident_decode_resource_block(decoder, source, block, 0))
    {
        return 0;
    }

    upload_font_texture(block, LIB_SHARED_FONT_PALETTE_BLOCK, LIB_SHARED_FONT_IMAGE_BLOCK);
    free_guess(block);
    FlushCache(0);

    for (s32 index = 0;; index++)
    {
        source = &chunks->resource;
        void* chunk_block = memalign(LIB_SHARED_FONT_ALIGNMENT, source->decoded_size);

        if (!chunk_block)
        {
            return 0;
        }

        FlushCache(0);

        if (!resident_decode_resource_block(decoder, source, chunk_block, 0))
        {
            return 0;
        }

        u8* data;

        switch (index)
        {
        case 0:
        case 1:
            u16 palette_block;
            u16 image_block;

            if (index == 0)
            {
                image_block = LIB_FONT_CHUNK0_IMAGE_BLOCK;
                palette_block = LIB_FONT_CHUNK0_PALETTE_BLOCK;
            }
            else
            {
                image_block = LIB_FONT_CHUNK1_IMAGE_BLOCK;
                palette_block = LIB_FONT_CHUNK1_PALETTE_BLOCK;
            }

            upload_font_texture(chunk_block, palette_block, image_block);
            break;
        case 2:
            func_00451C00(chunk_block, 0, ((LibFontGlyphHeader*)chunk_block)->glyph_count);
            data = font->glyph_data;
            memcpy_guess(data, chunk_block, ((LibFontGlyphHeader*)chunk_block)->table_size);
            font->glyphs = data;
            break;
        case 3:
            data = font->metric_data;
            memcpy_guess(data, chunk_block, source->decoded_size);
            font->metrics = data;
            break;
        }

        free_guess(chunk_block);
        FlushCache(0);
        chunks = chunks->next_offset == 0 ? 0 : (LibFontChunk*)((u8*)chunks + chunks->next_offset);

        if (chunks->tag == LIB_FONT_CHUNK_END)
        {
            break;
        }
    }

    if (archive_data)
    {
        free_guess(archive_data);
        FlushCache(0);
    }

    return 1;
}

/**
 * @brief Unlink a widget from the container and clear its owner.
 * @param object Container receiver.
 * @param child Widget to detach.
 */
extern "C" void func_004C6120(LibContainer* object, LibWidget* child)
{
    object->LibListReceiver::unlink(child);
    child->container = 0;
}

/**
 * @brief Link a widget into the container after a position and record its owner.
 * @param object Container receiver.
 * @param position Node the widget follows.
 * @param child Widget to insert.
 */
extern "C" void func_004C6150(LibContainer* object, void* position, LibWidget* child)
{
    object->LibListReceiver::insert_after(position, child);
    child->container = object;
}


/**
 * @brief Link the widget into the container and record its owner.
 * @param object Container receiver.
 * @param child Widget to attach.
 */
extern "C" void lib_container_attach_widget(LibContainer* object, LibWidget* child)
{
    object->LibListReceiver::append(child);
    reinterpret_cast<LibWidgetContainerLink*>(child)->container = object;
}

extern "C" void func_004C61D0(void* object)
{
    lib_finish_packet(reinterpret_cast<LibTransformOwner*>((u8*)object + 0x20));
}

struct N54Owner84_004BD360 { u8 pad00[0x84]; u8 active; };

void func_004C61F0(N54Owner84_004BD360* object)
{
    object->active = 1;
    void* adjusted = object;
    if (object != 0)
    {
        adjusted = (u8*)adjusted + 0xB0;
    }
    func_00461830((u8*)object + 0xD0, adjusted);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C6230);

/**
 * @brief Allocate container drawing storage and initialize its transform.
 * @param object Container receiver.
 * @param code Transform code.
 * @param first First byte value.
 * @param second Word value.
 * @param x First coordinate.
 * @param y Second coordinate.
 * @param z Third coordinate.
 * @return One on success, or zero if storage cannot be allocated.
 */
extern "C" s32 lib_container_init(LibContainer* object, s32 code, float x, float y, s32 first, float z, s32 second)
{
    if (!lib_allocate_drawing_storage(&object->unkD0, 12))
    {
        return 0;
    }
    object->LibCallbackTransform::translation.x = x;
    object->LibCallbackTransform::translation.y = y;
    object->LibCallbackTransform::translation.z = 0.0f;
    object->LibCallbackTransform::translation.w = 1.0f;
    object->set_codes_and_z(code, first, z, second, 0);
    object->unkE0 = 128.0f;
    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C65E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C6700);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C6710);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C67C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C6840);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C6910);

typedef struct LibTextBoundsState
{
    u8 pad00[0x70];
    void* drawing;
    u8 pad74[0x40];
    u32 count;
    u8 padb8[0x30];
    LibTextExtent bounds;
    u8 padf8[0x10];
    u32 source;
    u32 key;
    u8 flag;
    u8 pending;
} LibTextBoundsState;
extern "C" s32 func_004C7D40(LibTextWidget* object, u32 source, u32 key, u8 flag);
extern "C" void* func_100B00(u32 size, s32 flags);
extern "C" void func_004C74E0(LibTextWidget* object);

/**
 * @brief Refresh the text layout and return its measured bounds.
 * @param object Text widget.
 * @return Stored bounds, or null when resource loading or allocation fails.
 */
extern "C" LibTextExtent* lib_text_measure_bounds(LibTextWidget* object)
{
    LibTextBoundsState* state = (LibTextBoundsState*)object;
    if (state->pending)
    {
        if (!func_004C7D40(object, state->source, state->key, state->flag))
        {
            return 0;
        }
    }
    state->drawing = func_100B00(state->count * 32, 0);
    if (!state->drawing)
    {
        return 0;
    }
    func_004C74E0(object);
    delete[] (u8*)state->drawing;
    return &state->bounds;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C6A40);

extern "C" void lib_text_set_resource(LibTextWidget* object, s32 slot, u32 key, u8 flag)
{
    LibTextResourceState* state = (LibTextResourceState*)object;
    state->source = slot;
    state->key = key;
    state->flag = flag;
    state->pending = 1;
    state->redraw = 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C6E10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C6F30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C7010);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C71E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C7290);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C74E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C79C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C7D00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C7D40);

/** One glyph's drawing state in a LibClass178780 batch. */
struct LibGlyphDraw6C : public LibDrawState64
{
    /** @brief Initialize the drawing state and clear both trailing words. */
    LibGlyphDraw6C();

    u32 unk64;
    u32 unk68;
};

/** 0x30-byte batch of glyph drawing states a text widget keeps at unkfc, with vtable D_178780 in main data. */
class LibClass178780 : public LibListObject
{
public:
    /** @brief Start without storage or glyphs. */
    LibClass178780() : glyphs(0)
    {
    }

    /** @brief Free the glyphs and the drawing storage. */
    virtual ~LibClass178780();

    /**
     * @brief Allocate drawing storage and glyph states for a glyph count.
     * @param count Number of glyphs.
     * @return One on success, or zero when an allocation fails.
     */
    s32 init(s32 count);

    LibStorageBlock0C storage;
    u8 unk20[4];
    LibGlyphDraw6C* glyphs;
    s32 glyph_capacity;
    s32 glyph_count;
};

/** @brief Initialize the drawing state and clear both trailing words. */
LibGlyphDraw6C::LibGlyphDraw6C()
{
    unk64 = 0;
    unk68 = 0;
}

typedef struct LibTextRectangleState
{
    u8 pad00[0xF8];
    u8 flag;
    u8 padf9[3];
    void* allocation;
    u8 pad100[0x11];
    u8 pending;
} LibTextRectangleState;
/**
 * @brief Initialize the text rectangle and clear its allocation and pending flag.
 * @param object Text widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 */
extern "C" void lib_text_init_rectangle(LibTextWidget* object, float x, float y, float width, float height)
{
    LibTextRectangleState* state = (LibTextRectangleState*)object;
    object->set_rectangle(x, y, width, height);
    state->allocation = 0;
    state->pending = 0;
}

/**
 * @brief Initialize the text rectangle and immediately load its resource.
 * @param object Text widget.
 * @param slot Resource source word.
 * @param key Text resource key.
 * @param flag Text slot state flag.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return Resource initialization status.
 */
extern "C" s32 lib_text_init_resource_rectangle(LibTextWidget* object, s32 slot, s32 key, u8 flag, float x, float y, float width, float height)
{
    LibTextRectangleState* state = (LibTextRectangleState*)object;
    state->flag = flag;
    object->set_rectangle(x, y, width, height);
    state->allocation = 0;
    state->pending = 0;
    return func_004C7D40(object, slot, key, 0);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8040);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C80E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C81B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8280);

s32 func_004C8360(void* object)
{
    return 0;
}

s32 func_004C8370(void* object)
{
    return 11;
}

s32 func_004C8380(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8390);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C83E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8440);

s32 func_004C8510(void* object)
{
    return func_004A4570(object);
}

extern "C" void func_004C8530(void* object)
{
    LibStateBytes62View* state = (LibStateBytes62View*)object;
    state->value64 = 0;
    state->value62 = 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8540);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C85D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8680);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8720);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8810);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8860);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8F80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9010);

extern "C" void func_004C94D0(void* object, const unsigned __int128* value)
{
    LibVectorField850View* state = (LibVectorField850View*)object;
    copy_vector(&state->value850, (const LibVector4*)value);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C94E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C95A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9650);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9660);

s32 func_004C96D0(void* object)
{
    return 67;
}

/** Model that owns morph targets; only the flag a morph target sets is known. */
struct LibMorphOwner
{
    u8 unk00[0x8D];
    u8 unk8d_0 : 1;

    /** Set when a morph target of the model becomes active. */
    u8 morph_dirty : 1;

    u8 unk8d_2 : 6;
};

/**
 * @brief Return the absolute value of a float (one abs.s).
 * @param value Value to convert.
 * @return Absolute value.
 */
static inline float morph_abs(float value)
{
    return __s_abs(value);
}

/**
 * @brief Set a morph target's weight, clamped to its shape's range, and mark its owner when it becomes active.
 * @param target Morph target.
 * @param weight New weight.
 */
void lib_morph_target_set_weight(LibMorphTarget* target, float weight)
{
    float previous = target->weight;
    target->weight = weight;
    float clamped = ee_min(weight, target->shape->max_weight);
    clamped = ee_max(clamped, target->shape->min_weight);
    target->clamped_weight = clamped;

    float previous_size = morph_abs(previous);

    if (morph_abs(clamped) < 1e-5f)
    {
        if (target->idle_frames == 0 && !(previous_size < 1e-5f))
        {
            target->idle_frames = 3;
        }
    }
    else
    {
        if (target->active != 1)
        {
            LibMorphOwner* owner = (LibMorphOwner*)target->owner;

            if (owner)
            {
                owner->morph_dirty = 1;
            }
        }

        target->active = 1;
        target->idle_frames = 0;
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C97A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9840);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C98E0);

void* func_004C9930(void* receiver)
{
    func_004A8F10(receiver);
    *(void**)receiver = D_00174C90;
    ((u8*)receiver)[0xE] = 1;
    return receiver;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9970);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", lib_spot_light_get_frame);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9AC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9BA0);

/** @brief Update the transform matrix if it isn't ready, then cache the position and direction from it. */
void LibLight::update_frame()
{
    if (!matrix_ready)
    {
        update_transform_matrix();
    }

    position.x = world.m[0][3];
    position.y = world.m[1][3];
    position.z = world.m[2][3];
    position.w = 1.0f;
    direction.x = world.m[0][1];
    direction.y = world.m[1][1];
    direction.z = world.m[2][1];
    direction.w = 1.0f;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9CA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9D80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9E80);

/**
 * @brief Read a light's direction (its transform's y axis) from its current transform matrix.
 * @param out Receives the direction, w one.
 * @param light Light.
 */
extern "C" void lib_light_get_direction(LibVector4* out, LibLight* light)
{
    const LibMatrix44Value* matrix = light->get_transform_matrix();
    LibVector4 axis;
    axis.x = matrix->m[0][1];
    axis.y = matrix->m[1][1];
    axis.z = matrix->m[2][1];
    axis.w = 1.0f;
    copy_vector(out, &axis);
}

/**
 * @brief Detach a node and clear its links, ignoring the list sentinel and null.
 * @param node Intrusive node to detach.
 */
void LibListReceiver::unlink(void* node)
{
    LibListSentinel* removed = static_cast<LibListSentinel*>(node);
    if (removed == &sentinel)
    {
        return;
    }
    if (removed == 0)
    {
        return;
    }
    LibListSentinel* previous = removed->previous;
    LibListSentinel* next = removed->next;
    if (previous)
    {
        previous->next = next;
    }
    if (next)
    {
        next->previous = previous;
    }
    if (node_count != 0)
    {
        --node_count;
    }
    removed->previous = 0;
    removed->next = 0;
}

/**
 * @brief Insert a node after a list position and increment the node count.
 * @param position List position preceding the inserted node.
 * @param node Intrusive node to insert.
 */
void LibListReceiver::insert_after(void* position, void* node)
{
    LibListSentinel* after = static_cast<LibListSentinel*>(position);
    LibListSentinel* inserted = static_cast<LibListSentinel*>(node);
    LibListSentinel* next = after->next;
    inserted->previous = after;
    inserted->next = next;
    after->next = inserted;
    if (next)
    {
        next->previous = inserted;
    }
    ++node_count;
}

/**
 * @brief Prepend a node to the beginning of the list and increment its count.
 * @param node Intrusive node to prepend.
 */
void LibListReceiver::prepend(void* node)
{
    LibListSentinel* inserted = static_cast<LibListSentinel*>(node);
    LibListSentinel* first = sentinel.next;
    inserted->previous = &sentinel;
    inserted->next = first;
    sentinel.next = inserted;
    first->previous = inserted;
    ++node_count;
}

/**
 * @brief Append a node to the end of the list and increment its count.
 * @param node Intrusive node to append.
 */
void LibListReceiver::append(void* node)
{
    LibListSentinel* inserted = static_cast<LibListSentinel*>(node);
    LibListSentinel* last = sentinel.previous;
    inserted->previous = last;
    inserted->next = &sentinel;
    sentinel.previous = inserted;
    last->next = inserted;
    ++node_count;
}

/** @brief Initialize an empty intrusive list whose sentinel links point to itself. */
LibListReceiver::LibListReceiver()
{
    node_count = 0;
    sentinel.previous = &sentinel;
    sentinel.next = &sentinel;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CA090);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CA180);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CA270);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CAB20);

/** @brief Recompute the derived perspective-volume coefficients. */
void LibProjectionVolume::update_coefficients()
{
    far_near_ratio = far_distance / near_distance;
    unk54 = (-2.0f * near_half_width) * far_distance;
    unk58 = (-2.0f * near_half_height) * far_distance;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", lib_matrix_to_quaternion);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", lib_matrix_look_at);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CC070);

/**
 * @brief Compute the VU0 sine and cosine approximations for an angle.
 * @param output Aligned vector receiving cosine in z and sine in w; x and y retain shared polynomial coefficients.
 * @param angle Angle in radians.
 */
extern "C" void lib_compute_sine_cosine_pair(LibVector4* output, float angle)
{
    D_0050CC80.phase.angle = angle;
    vu0_sincos_load(&D_0050CC80);
    vu0_sincos_reduce(&D_0050CD10);
    bool cosine_negative = bool(D_0050CD10.cosine_half_turns & 1);
    bool sine_negative = bool(D_0050CD10.sine_half_turns & 1);
    vu0_sincos_square();
    float cosine_sign;
    if (cosine_negative)
    {
        cosine_sign = -1.0f;
    }
    else
    {
        cosine_sign = 1.0f;
    }

    D_0050CC80.sign = cosine_sign;
    float sine_sign;

    if (sine_negative)
    {
        sine_sign = -1.0f;
    }
    else
    {
        sine_sign = 1.0f;
    }

    D_0050CC80.phase.sine_sign = sine_sign;
    vu0_sincos_evaluate(&D_0050CC80);
    vu0_sincos_store(output);
}

/**
 * @brief Compute degree-nine VU0 sine and cosine approximations.
 * @param output Aligned vector receiving cosine in z and sine in w; x and y retain shared polynomial coefficients.
 * @param angle Angle in radians.
 */
extern "C" void lib_compute_sine_cosine_pair_degree9(LibVector4* output, float angle)
{
    D_0050CC80.phase.angle = angle;
    vu0_sincos_load_degree9(&D_0050CC80);
    vu0_sincos_reduce(&D_0050CD00);
    bool cosine_negative = bool(D_0050CD00.cosine_half_turns & 1);
    bool sine_negative = bool(D_0050CD00.sine_half_turns & 1);
    vu0_sincos_square();
    float cosine_sign;
    if (cosine_negative)
    {
        cosine_sign = -1.0f;
    }
    else
    {
        cosine_sign = 1.0f;
    }

    D_0050CC80.sign = cosine_sign;
    float sine_sign;

    if (sine_negative)
    {
        sine_sign = -1.0f;
    }
    else
    {
        sine_sign = 1.0f;
    }

    D_0050CC80.phase.sine_sign = sine_sign;
    vu0_sincos_evaluate_degree9(&D_0050CC80);
    vu0_sincos_store(output);
}

/**
 * @brief Evaluate the degree-thirteen VU0 cosine approximation.
 * @param angle Angle in radians.
 * @return Approximated cosine.
 */
extern "C" float lib_cosine(float angle)
{
    D_0050CC80.phase.angle = angle;
    vu0_cosine_load(&D_0050CC80);
    vu0_cosine_reduce(&D_0050CCF0);
    bool negative = bool(D_0050CCF0.half_turns & 1);
    vu0_trig_square_scalar();
    float sign;
    if (negative)
    {
        sign = -1.0f;
    }
    else
    {
        sign = 1.0f;
    }

    D_0050CC80.sign = sign;
    vu0_cosine_begin_evaluate(&D_0050CC80);
    vu0_trig_finish_evaluate(&D_0050CC80);
    return D_0050CC80.phase.result;
}

/**
 * @brief Evaluate the degree-nine VU0 cosine approximation.
 * @param angle Angle in radians.
 * @return Approximated cosine.
 */
extern "C" float lib_cosine_degree9(float angle)
{
    D_0050CC80.phase.angle = angle;
    vu0_sincos_load_degree9(&D_0050CC80);
    vu0_cosine_reduce(&D_0050CCE0);
    bool negative = bool(D_0050CCE0.half_turns & 1);
    vu0_trig_square_scalar();
    float sign;
    if (negative)
    {
        sign = -1.0f;
    }
    else
    {
        sign = 1.0f;
    }

    D_0050CC80.sign = sign;
    vu0_trig_begin_evaluate_degree9(&D_0050CC80);
    vu0_trig_finish_evaluate_degree9(&D_0050CC80);
    return D_0050CC80.phase.result;
}

/**
 * @brief Evaluate the degree-thirteen VU0 sine approximation.
 * @param angle Angle in radians.
 * @return Approximated sine.
 */
extern "C" float lib_sine(float angle)
{
    D_0050CC80.phase.angle = angle;
    vu0_sine_load(&D_0050CC80);
    vu0_sine_reduce(&D_0050CCD0);
    bool negative = bool(D_0050CCD0.half_turns & 1);
    vu0_trig_square_scalar();
    float sign;
    if (negative)
    {
        sign = -1.0f;
    }
    else
    {
        sign = 1.0f;
    }

    D_0050CC80.sign = sign;
    vu0_sine_begin_evaluate(&D_0050CC80);
    vu0_trig_finish_evaluate(&D_0050CC80);
    return D_0050CC80.phase.result;
}

/**
 * @brief Evaluate the degree-nine VU0 sine approximation.
 * @param angle Angle in radians.
 * @return Approximated sine.
 */
extern "C" float lib_sine_degree9(float angle)
{
    D_0050CC80.phase.angle = angle;
    vu0_sine_load_degree9(&D_0050CC80);
    vu0_sine_reduce(&D_0050CCC0);
    bool negative = bool(D_0050CCC0.half_turns & 1);
    vu0_trig_square_scalar();
    float sign;
    if (negative)
    {
        sign = -1.0f;
    }
    else
    {
        sign = 1.0f;
    }

    D_0050CC80.sign = sign;
    vu0_trig_begin_evaluate_degree9(&D_0050CC80);
    vu0_trig_finish_evaluate_degree9(&D_0050CC80);
    return D_0050CC80.phase.result;
}

/**
 * @brief Compute dot(point - origin, direction) over the xyz components.
 * @param point Aligned point vector.
 * @param direction Aligned vector supplying the dot-product coefficients.
 * @param origin Aligned vector subtracted from point.
 * @return The xyz dot product.
 */
extern "C" float lib_dot_point_offset(const LibVector4* point, const LibVector4* direction, const LibVector4* origin)
{
    LibVector4 result;
    vu0_dot_offset_xyz(&result, point, direction, origin);
    return result.x;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CC7A0);

/**
 * @brief Build a directional shadow projection onto a plane.
 * @param output Projection matrix destination.
 * @param direction Projection direction; its xyz dot product with the plane normal must be nonzero.
 * @param plane Plane equation coefficients (normal.x, normal.y, normal.z, offset).
 */
extern "C" void lib_build_directional_shadow_matrix(LibMatrix44Value* output, const FieldVec4A* direction, const FieldVec4A* plane)
{
    float inverse_dot = 1.0f / (direction->x * plane->x + direction->y * plane->y + direction->z * plane->z);
    float scaled_x = direction->x * inverse_dot;
    float scaled_y = direction->y * inverse_dot;
    float scaled_z = direction->z * inverse_dot;
    FieldVec4A scaled(scaled_x, scaled_y, scaled_z, 0.0f);
    float dot = scaled.x * plane->x + scaled.y * plane->y + scaled.z * plane->z + scaled.w * plane->w;
    output->m[0][0] = dot - scaled.x * plane->x;
    output->m[0][1] = -scaled.x * plane->y;
    output->m[0][2] = -scaled.x * plane->z;
    output->m[0][3] = -scaled.x * plane->w;
    output->m[1][0] = -scaled.y * plane->x;
    output->m[1][1] = dot - scaled.y * plane->y;
    output->m[1][2] = -scaled.y * plane->z;
    output->m[1][3] = -scaled.y * plane->w;
    output->m[2][0] = -scaled.z * plane->x;
    output->m[2][1] = -scaled.z * plane->y;
    output->m[2][2] = dot - scaled.z * plane->z;
    output->m[2][3] = -scaled.z * plane->w;
    output->m[3][0] = 0.0f;
    output->m[3][1] = 0.0f;
    output->m[3][2] = 0.0f;
    output->m[3][3] = 1.0f;
}

/**
 * @brief Build the homogeneous shadow matrix dot(light, plane) * I - light * plane transpose.
 * @param output Projection matrix destination.
 * @param light Homogeneous light vector; w distinguishes a point from a direction.
 * @param plane Plane equation coefficients (normal.x, normal.y, normal.z, offset).
 */
extern "C" void lib_build_projective_shadow_matrix(LibMatrix44Value* output, const FieldVec4A* light, const FieldVec4A* plane)
{
    float x_product = light->x * plane->x;
    float y_product = light->y * plane->y;
    float z_product = light->z * plane->z;
    float w_product = light->w * plane->w;
    float dot = x_product + y_product + z_product + w_product;
    output->m[0][0] = dot - x_product;
    output->m[0][1] = -light->x * plane->y;
    output->m[0][2] = -light->x * plane->z;
    output->m[0][3] = -light->x * plane->w;
    output->m[1][0] = -light->y * plane->x;
    output->m[1][1] = dot - light->y * plane->y;
    output->m[1][2] = -light->y * plane->z;
    output->m[1][3] = -light->y * plane->w;
    output->m[2][0] = -light->z * plane->x;
    output->m[2][1] = -light->z * plane->y;
    output->m[2][2] = dot - light->z * plane->z;
    output->m[2][3] = -light->z * plane->w;
    output->m[3][0] = -light->w * plane->x;
    output->m[3][1] = -light->w * plane->y;
    output->m[3][2] = -light->w * plane->z;
    output->m[3][3] = dot - light->w * plane->w;
}

/**
 * @brief Compute the inverse-rotated positive z direction of a unit quaternion.
 * @param quaternion Unit quaternion to evaluate.
 * @param output Vector receiving the direction in xyz and 1 in w.
 */
extern "C" void lib_quaternion_inverse_z_direction(const FieldVec4B* quaternion, FieldVec4A* output)
{
    float x = quaternion->x;
    float y = quaternion->y;
    output->x = 2.0f * (x * quaternion->z - quaternion->w * y);
    output->y = 2.0f * (quaternion->y * quaternion->z + quaternion->w * quaternion->x);
    output->z = 1.0f - 2.0f * (x * x + y * y);
    output->w = 1.0f;
}

/**
 * @brief Build a quaternion from an origin-to-target direction and supplied z rotation.
 * @param output Four-float quaternion destination.
 * @param target Target position measured from the origin.
 * @param z_angle Rotation about z in radians.
 */
extern "C" void lib_quaternion_from_direction_xz(float* output, const LibVector4* target, float z_angle)
{
    LibVector4 angles;
    angles.x = 0.0f;
    angles.y = 0.0f;
    angles.z = 0.0f;
    angles.w = 1.0f;
    lib_direction_angles_xz(&angles, target, z_angle);
    lib_quaternion_from_euler(reinterpret_cast<FieldVec4B*>(output), &angles.x);
}

/**
 * @brief Compute the fog mapping offset + reciprocal_scale / z for perspective fog.
 * @param offset Receives the constant fog coefficient.
 * @param reciprocal_scale Receives the reciprocal-distance fog coefficient.
 * @param far_factor Fog factor at the far distance.
 * @param near_factor Fog factor at the near distance.
 * @param near_plane Near-plane distance; must differ from far_plane.
 * @param far_plane Far-plane distance.
 */
extern "C" void lib_compute_perspective_fog_coefficients(float* offset, float* reciprocal_scale, float far_factor, float near_factor,
                                                        float near_plane, float far_plane)
{
    float plane_span = far_plane - near_plane;
    *offset = 0.5f * (far_factor + near_factor + (far_factor - near_factor) * (far_plane + near_plane) / plane_span);
    *reciprocal_scale = far_plane * near_plane * (near_factor - far_factor) / plane_span;
}

/**
 * @brief Extract a quaternion after mapping each matrix row from (x, y, z) to (x, -z, y).
 * @param source Source matrix.
 * @param output Destination quaternion.
 */
extern "C" void func_004CCCF0(const LibMatrix44Value* source, FieldVec4B* output)
{
    LibMatrix44Value converted;
    ((unsigned __int128*)&converted)[0] = 0;
    ((unsigned __int128*)&converted)[1] = 0;
    ((unsigned __int128*)&converted)[2] = 0;
    ((unsigned __int128*)&converted)[3] = 0;
    FieldVec4A& row1 = matrix_row_vector(converted, 1);
    FieldVec4A& row2 = matrix_row_vector(converted, 2);
    converted.m[0][0] = source->m[0][0];
    row1.x = source->m[1][0];
    row2.x = source->m[2][0];
    converted.m[0][1] = -source->m[0][2];
    row1.y = -source->m[1][2];
    row2.y = -source->m[2][2];
    converted.m[0][2] = source->m[0][1];
    row1.z = source->m[1][1];
    row2.z = source->m[2][1];
    converted.m[3][3] = 1.0f;
    lib_matrix_to_quaternion(output, &converted);
}

/**
 * @brief Evaluate the degree-six Taylor polynomial for exp(value).
 * @param value Polynomial argument.
 * @return Polynomial approximation to exp(value).
 */
extern "C" float func_004CCD90(float value)
{
    float squared = value * value;
    float cubed = squared * value;
    float result = (1.0f + value) + 0.5f * squared;
    result = ((1.0f / 6.0f) * cubed + result) + (1.0f / 24.0f) * (squared * squared);
    float fifth_term = (1.0f / 120.0f) * (cubed * squared);
    return (fifth_term + result) + (1.0f / 720.0f) * (cubed * cubed);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CCE10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CCEE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CD010);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CD2C0);

