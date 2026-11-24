#include "angle.h"
#include "ee.h"
#include "gs.h"
#include "include_asm.h"
#include "overlays/lib/scratchpad_texture_cache.h"
#include "overlays/lib/segment_vu0.h"
#include "overlays/lib/box_cull_vu0.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/quaternion_vu0.h"
#include "overlays/lib/quaternion_inlines.h"
#include "overlays/lib/vector.h"
#include "overlays/lib/text_0046AE20.h"
#include "overlays/lib/text_0049B820.h"
#include "overlays/lib/trig_vu0.h"
#include "overlays/lib/vector_vu0.h"
#include "overlays/lib/matrix_vu0.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/model.h"
#include "overlays/lib/light_vu0.h"
#include "overlays/lib/text_00429B00.h"
#include "main/resident_data.h"
#include "sdk/main/libgraph_0012EAC8.h"
#include "sdk/main/libc_guess_00137290.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "sdk/main/libkernl_00121940.h"
#include "sdk/main/libm_guess_0013F3E0.h"
#include "overlays/lib/text_004ABA60.h"
#include "clamp.h"
#include "overlays/lib/text_0044ABE0.h"
#include "overlays/lib/vector_inlines.h"
#include "main/system.h"
#include "main/utility.h"
#include "overlays/lib/text_004DD440.h"
#include "overlays/lib/text_004095C0.h"
#include "overlays/lib/item_allocation.h"

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

/**
 * @brief View an aligned matrix row as a vector.
 * @param matrix Destination matrix.
 * @param row Row index.
 * @return Writable row vector.
 */
static inline FieldVec4A& matrix_row_vector(LibMatrix44Value& matrix, s32 row)
{
    return *(FieldVec4A*)matrix.m[row];
}

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

/**
 * @brief Set an entry's unk18 byte; when it changes, flag the entry's list (unk8d_1).
 * @param entry List entry.
 * @param value New value.
 */
extern "C" void func_004BD380(LibClass1779F0* entry, u8 value)
{
    if (entry->unk18 != value && entry->list != 0)
    {
        entry->list->unk8d_1 = 1;
    }

    entry->unk18 = value;
}

/**
 * @brief Store a float in an indexed array slot.
 * @param values Float array.
 * @param index Slot index.
 * @param value Value to store.
 */
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

/**
 * @brief Copy four quadwords.
 * @param destination Destination of the copy.
 * @param source Quadwords to copy.
 * @return The destination.
 */
extern "C" void* func_004BD3F0(void* destination, const void* source)
{
    unsigned __int128* destination_words = (unsigned __int128*)destination;
    const unsigned __int128* source_words = (const unsigned __int128*)source;
    destination_words[0] = source_words[0];
    destination_words[1] = source_words[1];
    destination_words[2] = source_words[2];
    destination_words[3] = source_words[3];
    return destination;
}

/**
 * @brief Return the parent transform's base matrix, updating it first if it isn't ready.
 *
 * When that update changed the parent, the transform is marked dirty too.
 * @param transform Transform whose parent to read.
 * @return The parent's base matrix, or null without a parent.
 */
extern "C" const LibMatrix44Value* func_004BD420(LibTransform* transform)
{
    if (transform->parent_transform == 0)
    {
        return 0;
    }

    if (!transform->parent_transform->matrix_ready)
    {
        transform->parent_transform->update_transform_matrix();

        if (transform->parent_transform->unk51)
        {
            transform->transform_dirty = 1;
        }
    }

    return &transform->parent_transform->base_transform;
}

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

/**
 * @brief Apply one transform entry at a frame: sample its channel and hand the value to the target's translation,
 *        orientation or scale. Other entry types go to func_004B4840.
 * @param object Animation object.
 * @param entry Entry to apply.
 * @param frame Frame.
 * @param mode Nonzero to return as soon as a channel runs longer than the status so far.
 * @param status Longest cycle count so far.
 * @return The longest cycle count, including this entry's.
 */
extern "C" s32 func_004BD4F0(LibAnimation* object, LibAnimationEntry14* entry, float frame, s32 mode, s32 status)
{
    LibAnimationTarget* target = static_cast<LibAnimationTarget*>(entry->target);

    switch (entry->type)
    {
    case 1:
    {
        LibPooledVectorTrack* track = static_cast<LibPooledVectorTrack*>(entry->channel);
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
        target->set_translation_vector(reinterpret_cast<const LibVector4*>(&value));
        break;
    }
    case 2:
    {
        LibPooledVectorCurveTrack* track = static_cast<LibPooledVectorCurveTrack*>(entry->channel);
        FieldVec4A value = track->sample_once(frame);
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
        target->set_translation_vector(reinterpret_cast<const LibVector4*>(&value));
        break;
    }
    case 4:
    {
        LibPooledSlerpQuaternionTrack* track = static_cast<LibPooledSlerpQuaternionTrack*>(entry->channel);
        FieldVec4B value;
        value = track->sample(frame);
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

        target->set_orientation(reinterpret_cast<const LibVector4*>(&value));
        break;
    }
    case 5:
    {
        LibPooledFloatQuaternionTrack* track = static_cast<LibPooledFloatQuaternionTrack*>(entry->channel);
        FieldVec4A value = track->sample_once(frame);
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

        target->set_orientation(reinterpret_cast<const LibVector4*>(&value));
        break;
    }
    case 8:
    {
        LibPooledVectorTrack* track = static_cast<LibPooledVectorTrack*>(entry->channel);
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
        target->set_scale_vector(reinterpret_cast<const LibVector4*>(&value));
        break;
    }
    case 9:
    {
        LibPooledVectorCurveTrack* track = static_cast<LibPooledVectorCurveTrack*>(entry->channel);
        FieldVec4A value = track->sample_once(frame);
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
        target->set_scale_vector(reinterpret_cast<const LibVector4*>(&value));
        break;
    }
    case 6:
    {
        LibPooledQuaternionCurveTrack* track = static_cast<LibPooledQuaternionCurveTrack*>(entry->channel);
        FieldVec4A value = track->sample_once(frame);
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

        target->set_orientation(reinterpret_cast<const LibVector4*>(&value));
        break;
    }
    default:
        if (entry->type == 0x135)
        {
            LibPooledQuaternionTrack* track = static_cast<LibPooledQuaternionTrack*>(entry->channel);
            FieldVec4A value = track->sample_once(frame);
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

            target->set_orientation(reinterpret_cast<const LibVector4*>(&value));
        }
        else
        {
            status = func_004B4840(object, entry, frame, mode, status);
        }

        break;
    }

    return status;
}

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

#define LIB_ANIMATION_TAG_SAFH 0x53414648

/** Chunk of an animation resource: a tag and the offset of the next chunk. */
struct LibAnimationChunk
{
    u32 tag;
    u8 unk04[8];
    s32 next;
    s32 node_count;
    s32 entry_count;
    s32 version;
    float unk1c;
    u32 node_offsets[1];
};

/** Track record inside an animation node; size is the offset of the next one. */
struct LibAnimationTrack
{
    u8 unk00[2];
    u8 flags;
    u8 kind;
    s16 type;
    u8 unk06[2];
    s32 size;
    u8 looped;
};

/** Node record of an animation resource: its name, track count and name checksum, then its tracks. */
struct LibAnimationNode
{
    char name[0x10];
    u32 flags;
    s16 track_count;
    u8 unk16[2];
    s32 checksum;
    u8 unk1c[4];
    LibAnimationTrack tracks[1];
};

/**
 * @brief Bind an animation's tracks to the parts of a target, by part name.
 * @param object Animation object.
 * @param target Scene whose named entries the tracks drive; also registered as the animation's binding owner.
 * @return 1 when bound (or already bound), 0 when the resource has no usable track chunk.
 */
s32 func_004BFE10(void* object, void* target)
{
    LibAnimation* animation = static_cast<LibAnimation*>(object);
    LibAnimationBindingOwner* owner = static_cast<LibAnimationBindingOwner*>(target);
    LibAnimationChunk* chunk = static_cast<LibAnimationChunk*>(animation->resource_data);

    if (!chunk)
    {
        return 0;
    }

    if (animation->targets_bound)
    {
        return 1;
    }

    LibAnimationChunk* cursor = chunk;

    for (;;)
    {
        if (cursor->tag == LIB_ANIMATION_TAG_SAFH)
        {
            break;
        }

        cursor = cursor->next == 0 ? 0 : reinterpret_cast<LibAnimationChunk*>(reinterpret_cast<u8*>(cursor) + cursor->next);

        if (cursor == 0)
        {
            return 0;
        }
    }

    chunk = cursor;

    animation->header = chunk;

    if (chunk->version != 8)
    {
        return 0;
    }

    animation->node_count = chunk->node_count;
    animation->entry_count = chunk->entry_count;
    animation->unk64 = chunk->unk1c;
    animation->node_offsets = chunk->node_offsets;

    if (animation->entries && !animation->unk6d)
    {
        lib_animation_release_channels(animation);
    }

    delete[] animation->entries;
    animation->entries = new (0) LibAnimationEntry14[animation->entry_count];

    if (!animation->entries)
    {
        return 0;
    }

    s32 count = animation->entry_count;

    for (s32 index = 0; index < count; index++)
    {
        animation->entries[index].channel = 0;
    }

    s32 slot = 0;
    count = animation->node_count;

    if (owner)
    {
        lib_animation_register_binding(owner, animation, 0);
        animation->primary_binding_owner = owner;
    }

    for (s32 n = 0; n < count; n++)
    {
        LibAnimationNode* node = reinterpret_cast<LibAnimationNode*>(
            static_cast<u8*>(animation->resource_data) + animation->node_offsets[n]);
        LibAnimationTrack* track = node->tracks;
        s32 track_count = node->track_count;
        void* part = 0;

        if (track->kind < 0xE0 &&
            !(part = lib_find_named_entry_cached(static_cast<LibEntryManager*>(target), node->name, node->checksum)))
        {
            for (s32 index = 0; index < track_count; index++)
            {
                animation->entries[slot++].target = 0;
            }
        }
        else
        {
            for (s32 index = 0; index < track_count; index++, slot++)
            {
                animation->entries[slot].type = track->type;
                animation->entries[slot].kind = track->kind;
                animation->entries[slot].flags = track->flags | ((node->flags & 0x10) ? 0x10 : 0) | (track->looped ? 0x20 : 0);
                animation->entries[slot].target = part;
                *reinterpret_cast<u32*>(animation->entries[slot].unk0c) = 0;
                animation->entries[slot].state_name = node->name;
                track = reinterpret_cast<LibAnimationTrack*>(reinterpret_cast<u8*>(track) + track->size);
            }
        }
    }

    animation->targets_bound = 1;
    return 1;
}

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
    longest_channel = 0;
    started = 0;
    unk6d = 0;
    unk6b = 0;
    cached_entry = 0;
    targets_bound = 0;
    primary_binding_owner = 0;
    secondary_binding_owner = 0;
    object_kind |= LIB_OBJECT_KIND_ANIMATION;
}

// TODO: this one only matches at level 3 while the rest of the file is level 4. I think the two key reads
// in the extrapolation went through a helper I haven't worked out yet.
#pragma push
#pragma optimization_level 3

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

#pragma pop

/**
 * @brief Evaluate the track at a key without wrapping or extrapolating, and cache the value and its change per frame.
 * @param key Evaluation key.
 * @return Evaluated vector; the last key's value at or past the last key.
 */
FieldVec4A LibVectorCurveTrack::sample_once(float key)
{
    FieldVec4B result;

    if (!key_array)
    {
        return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    }

    if (state.key_count == 1)
    {
        return *reinterpret_cast<FieldVec4A*>(&static_cast<LibVectorCurveTrackKey*>(key_array)[0].value);
    }

    if (!(key < key_at(state.key_count - 1)))
    {
        state.cycle_count = 1;
        state.search_index = 0;
        return *reinterpret_cast<FieldVec4A*>(&static_cast<LibVectorCurveTrackKey*>(key_array)[state.key_count - 1].value);
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
        LibVectorCurveTrackKey* first = static_cast<LibVectorCurveTrackKey*>(key_array) + state.search_index;
        LibVectorCurveTrackKey* second = static_cast<LibVectorCurveTrackKey*>(key_array) + (state.search_index + 1);
        curve_segment.set_endpoints(first->value.w, second->value.w, reinterpret_cast<const FieldVec4A*>(&first->value),
                                    reinterpret_cast<const FieldVec4A*>(&first->out_tangent), reinterpret_cast<const FieldVec4A*>(&second->value),
                                    reinterpret_cast<const FieldVec4A*>(&second->in_tangent));
    }

    result = curve_segment.interpolate(key);
    value_rate = vector_scaled(g_inverse_frame_ticks, vector_difference(result, last_value));
    last_value = result;
    return *reinterpret_cast<FieldVec4A*>(&result);
}

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

/**
 * @brief Take a free track from a pool.
 * @param pool Pool to take from; may be null.
 * @return The track with its state reset, or null when there is no pool or every slot is used.
 */
LibPooledFloatTrack* float_track_pool_allocate(LibTrackPool<LibPooledFloatTrack>* pool)
{
    if (pool == 0)
    {
        return 0;
    }

    return pool->allocate();
}

/**
 * @brief Take a free track from a pool.
 * @param pool Pool to take from; may be null.
 * @return The track with its state reset, or null when there is no pool or every slot is used.
 */
LibPooledVectorTrack* vector_track_pool_allocate(LibTrackPool<LibPooledVectorTrack>* pool)
{
    if (pool == 0)
    {
        return 0;
    }

    return pool->allocate();
}

/**
 * @brief Take a free track from a pool.
 * @param pool Pool to take from; may be null.
 * @return The track with its state reset, or null when there is no pool or every slot is used.
 */
LibPooledSlerpQuaternionTrack* slerp_quaternion_track_pool_allocate(LibTrackPool<LibPooledSlerpQuaternionTrack>* pool)
{
    if (pool == 0)
    {
        return 0;
    }

    return pool->allocate();
}

/**
 * @brief Take a free track from a pool.
 * @param pool Pool to take from; may be null.
 * @return The track with its state reset, or null when there is no pool or every slot is used.
 */
LibPooledFloatCurveTrack* float_curve_track_pool_allocate(LibTrackPool<LibPooledFloatCurveTrack>* pool)
{
    if (pool == 0)
    {
        return 0;
    }

    return pool->allocate();
}

/**
 * @brief Take a free track from a pool.
 * @param pool Pool to take from; may be null.
 * @return The track with its state reset, or null when there is no pool or every slot is used.
 */
LibPooledVectorCurveTrack* vector_curve_track_pool_allocate(LibTrackPool<LibPooledVectorCurveTrack>* pool)
{
    if (pool == 0)
    {
        return 0;
    }

    return pool->allocate();
}

/**
 * @brief Take a free track from a pool.
 * @param pool Pool to take from; may be null.
 * @return The track with its state reset, or null when there is no pool or every slot is used.
 */
LibPooledFloatQuaternionTrack* float_quaternion_track_pool_allocate(LibTrackPool<LibPooledFloatQuaternionTrack>* pool)
{
    if (pool == 0)
    {
        return 0;
    }

    return pool->allocate();
}

/**
 * @brief Take a free track from a pool.
 * @param pool Pool to take from; may be null.
 * @return The track with its state reset, or null when there is no pool or every slot is used.
 */
LibPooledQuaternionCurveTrack* quaternion_curve_track_pool_allocate(LibTrackPool<LibPooledQuaternionCurveTrack>* pool)
{
    if (pool == 0)
    {
        return 0;
    }

    return pool->allocate();
}

/**
 * @brief Take a free track from a pool.
 * @param pool Pool to take from; may be null.
 * @return The track with its state reset, or null when there is no pool or every slot is used.
 */
LibPooledQuaternionTrack* quaternion_track_pool_allocate(LibTrackPool<LibPooledQuaternionTrack>* pool)
{
    if (pool == 0)
    {
        return 0;
    }

    return pool->allocate();
}

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
bool LibWordTrackBase::replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
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
bool LibWordTrackBase::on_replace_key(s32 index, float key, const void* value)
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
bool LibWordTrackBase::append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
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
bool LibWordTrackBase::on_append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
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

/** @brief Start with internal key storage and reset the state. */
LibWordTrackBase::LibWordTrackBase()
{
    state.pooled = false;
    reset_state();
}

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
bool LibWordKeyTrack::on_replace_key(s32 index, float key, const void* value)
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
bool LibWordKeyTrack::on_append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
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

/** @brief Start with identity deltas and channels and no channel flags. */
LibAnimationTarget::LibAnimationTarget()
{
    translation_delta = FieldVec4A(0.0f, 0.0f, 0.0f, 1.0f);
    orientation_delta = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    scale_delta = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    channel_translation = FieldVec4A(0.0f, 0.0f, 0.0f, 1.0f);
    channel_rotation = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    channel_scale = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    has_translation = 0;
    has_orientation = 0;
    has_scale = 0;
}

/** @brief Destroy the target. */
LibAnimationTarget::~LibAnimationTarget()
{
}

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

/**
 * @brief Copy the rotation and keep the rotation from the previous one.
 * @param value New rotation quaternion.
 */
void LibAnimationTarget::copy_orientation(const LibVector4* value)
{
    LibVector4* previous = &orientation;

    if (has_orientation)
    {
        orientation_delta = quaternion_product(lib_quaternion_inverse(*reinterpret_cast<const FieldVec4B*>(previous)),
                                               *reinterpret_cast<const FieldVec4B*>(value));
    }
    else
    {
        has_orientation = 1;
    }

    transform_dirty = 1;
    copy_vector(&orientation, value);
}

/**
 * @brief Copy the rotation and keep the rotation from the previous one.
 * @param value New rotation quaternion.
 */
void LibAnimationTarget::set_orientation(const LibVector4* value)
{
    LibVector4* previous = &orientation;

    if (has_orientation)
    {
        orientation_delta = quaternion_product(lib_quaternion_inverse(*reinterpret_cast<const FieldVec4B*>(previous)),
                                               *reinterpret_cast<const FieldVec4B*>(value));
    }
    else
    {
        has_orientation = 1;
    }

    transform_dirty = 1;
    copy_vector(&orientation, value);
}

/**
 * @brief Set the rotation and keep the rotation from the previous one.
 * @param x First quaternion component.
 * @param y Second quaternion component.
 * @param z Third quaternion component.
 * @param w Fourth quaternion component.
 */
void LibAnimationTarget::set_orientation_components(float x, float y, float z, float w)
{
    LibVector4* previous = &orientation;

    if (has_orientation)
    {
        orientation_delta = quaternion_product(lib_quaternion_inverse(*reinterpret_cast<const FieldVec4B*>(previous)), FieldVec4B(x, y, z, w));
    }
    else
    {
        has_orientation = 1;
    }

    transform_dirty = 1;
    orientation.x = x;
    orientation.y = y;
    orientation.z = z;
    orientation.w = w;
}

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

/** Partial aim settings of a func_004C3590 record. */
struct LibAimSettings
{
    u8 unk00[4];
    s32 positive;
    u8 unk08[4];
    s32 axis;
};

/** Partial record func_004C3590 aims. */
struct LibAimRecord
{
    u8 unk00[4];
    LibAimSettings* settings;
    u8 unk08[0x1C];
    float roll;
    LibTransform* target;
};

/**
 * @brief Dot product of the x, y and z components.
 * @param first First vector.
 * @param second Second vector.
 * @return Dot product.
 */
static inline float lib_dot3(const LibVector4* first, const FieldVec4B* second)
{
    return first->x * second->x + first->y * second->y + first->z * second->z;
}

/**
 * @brief Cross product of the x, y and z components; w is left alone.
 * @param output Receives first cross second.
 * @param first First vector.
 * @param second Second vector.
 */
static inline void lib_cross3(LibVector4* output, const FieldVec4B* first, const LibVector4* second)
{
    output->x = first->y * second->z - first->z * second->y;
    output->y = first->z * second->x - first->x * second->z;
    output->z = first->x * second->y - first->y * second->x;
}

/**
 * @brief Build the rotation that turns a record's aim axis towards its target, seen from an origin in a matrix's
 * space, then rolls it about that axis.
 * @param record Record with the aim settings, roll angle and target transform.
 * @param matrix Matrix whose inverse takes the target's position into the origin's space.
 * @param origin Position the axis turns from.
 * @return Quaternion roll, then flip, then turn; the identity when the axis already points at the target.
 */
extern "C" FieldVec4B func_004C3590(LibAimRecord* record, const LibMatrix44Value* matrix, const FieldVec4B* origin)
{
    LibVector4 axis_angle;
    axis_angle.x = 0.0f;
    axis_angle.y = 0.0f;
    axis_angle.z = 0.0f;
    axis_angle.w = 0.0f;
    s32 axis = record->settings->axis;
    axis_angle.w = 1.0f;
    LibVector4 flip;
    flip.x = 0.0f;
    flip.y = 0.0f;
    flip.z = 0.0f;
    flip.w = 0.0f;
    float sign = 1.0f;

    if (record->settings->positive == 0)
    {
        sign = -1.0f;
    }

    float offset = 0.0f;

    switch (axis)
    {
    case 0:
        axis_angle.x = sign;

        if (sign < 0.0f)
        {
            axis_angle.x = 1.0f;
            flip.y = 1.0f;
            flip.w = PI;
        }

        offset = -PI / 2;
        break;

    case 1:
        axis_angle.y = sign;
        break;

    case 2:
        axis_angle.z = sign;

        if (sign < 0.0f)
        {
            axis_angle.z = 1.0f;
            flip.x = 1.0f;
            flip.w = PI;
        }

        break;
    }

    LibMatrix44Value inverse = func_004CF0B0(*matrix);
    LibTransform* target = record->target;

    if (!target->matrix_ready)
    {
        target->update_transform_matrix();
    }

    target = record->target;
    FieldVec4B direction;
    direction.x = target->transform.m[0][3];
    direction.y = target->transform.m[1][3];
    direction.z = target->transform.m[2][3];
    direction.w = 1.0f;
    direction = func_004CF6C0(inverse, reinterpret_cast<const FieldVec4A&>(direction));
    direction -= *origin;
    lib_normalize_vector3(&direction.x);
    float dot = lib_dot3(&axis_angle, &direction);

    if (dot < 0.9999999f)
    {
        LibVector4 turn;
        lib_cross3(&turn, &direction, &axis_angle);
        turn.w = 1.0f;
        lib_normalize_vector3(&turn.x);
        turn.w = func_00141F48(dot);
        FieldVec4B turn_rotation;
        FieldVec4B roll_rotation;
        FieldVec4B flip_rotation;
        lib_quaternion_from_axis_angle(&turn_rotation, &turn);
        lib_quaternion_from_axis_angle(&flip_rotation, &flip);
        axis_angle.w = record->roll + offset;
        lib_quaternion_from_axis_angle(&roll_rotation, &axis_angle);
        return multiply_rotations(multiply_rotations(roll_rotation, flip_rotation), turn_rotation);
    }

    return FieldVec4B(0.0f, 0.0f, 0.0f, 1.0f);
}

/** @brief Construct the track with both trailing words cleared. */
LibClass1783C0::LibClass1783C0()
{
    unk24 = 0;
    unk28 = 0;
}

/** @brief Destroy the track. */
LibClass1783C0::~LibClass1783C0()
{
}

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
bool LibClass1784E0::replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
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
bool LibClass1784E0::on_replace_key(s32 index, float key, const void* value)
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
bool LibClass1784E0::append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
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
bool LibClass1784E0::on_append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
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

/** @brief Start with internal key storage and reset the state. */
LibClass1784E0::LibClass1784E0()
{
    state.pooled = false;
    reset_state();
}

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
bool LibClass178450::on_replace_key(s32 index, float key, const void* value)
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
bool LibClass178450::on_append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
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

/** @brief Destroy the track. */
LibWordTrack::~LibWordTrack()
{
}

/**
 * @brief Return the last key's value.
 * @return Last key value.
 */
u32 LibWordTrack::get_last_value()
{
    return key_array[state.key_count - 1].value;
}

/**
 * @brief Word tracks have no end delta; leave the output alone.
 * @param output Unused.
 */
void LibWordTrack::get_end_delta(void* output) const
{
}

/**
 * @brief Word tracks have no value rate; leave the output alone.
 * @param output Unused.
 */
void LibWordTrack::get_value_rate(void* output) const
{
}

/**
 * @brief Return the value of the key at or before a position, without interpolating.
 * @param key Evaluation key.
 * @return Key value, or zero when the track has no keys.
 */
u32 LibWordTrack::sample(float key)
{
    s32 lower;
    s32 upper;

    if (!state.key_count)
    {
        return 0;
    }

    if (state.search_index >= state.key_capacity)
    {
        state.search_index = 0;
    }

    if (state.key_count == 1)
    {
        return key_array[0].value;
    }

    float wrapped_key = update_cycle_count(key);

    if (state.before_mode == LIB_TRACK_END_HOLD && state.cycle_count < 0)
    {
        return key_array[0].value;
    }

    if (state.after_mode == LIB_TRACK_END_HOLD && state.cycle_count > 0)
    {
        return key_array[state.key_count - 1].value;
    }

    find_surrounding_keys(wrapped_key, &lower, &upper);
    return key_array[lower].value;
}

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

// TODO: The game inlines this into LibPanel's destructor copy, which the vtable emits at the end of the unit, so
// it was an inline candidate there; scoped auto_inline is the only way I've found to get that.
#pragma push
#pragma auto_inline on
extern "C" void lib_panel_detach(LibPanel* object)
{
    LibPanelAssociationState* state = (LibPanelAssociationState*)object;

    if (state->association != 0)
    {
        state->association->panel = 0;
        state->association = 0;
    }
}
#pragma pop

/** Panel transform with its callback interface at 0x90. */
class FieldClass15BA90 : public LibTransformOwner, public LibDmaCallbacks
{
public:
    /** @brief Initialize the panel transform and its callback interface. */
    FieldClass15BA90();

    /** @brief Release the association and destroy the transform. */
    virtual ~FieldClass15BA90();

    /**
     * @brief Set the transform translation.
     * @param x Horizontal component.
     * @param y Vertical component.
     * @param z Third component.
     */
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

/** Arguments func_004C4B90 builds a panel's packet from. */
struct LibPanelDrawArgs
{
    const LibVector4* position;
    const LibUiRect16* rect;
    u32 address;
    u32* colors;
    float alpha;
    float unk84;
    u8 unk8b;
    u8 unk8a;
};

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4B90);

/**
 * @brief Write a panel's drawing packet.
 * @param panel Panel.
 * @param packet Where the packet's contents start.
 * @param args What to draw.
 * @return The end of the packet.
 */
extern "C" u8* func_004C4B90(LibPanel* panel, u8* packet, const LibPanelDrawArgs* args);

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

/**
 * @brief Read a container's alpha, which scales its widgets' alpha.
 * @param container Container.
 * @return Alpha, 128 for opaque.
 */
static inline float container_alpha(const LibContainer* container)
{
    return container->unkE0;
}

/** @brief Build the panel's packet once until it is marked for redrawing; a hidden panel just clears the flag. */
void LibPanel::draw()
{
    if (!unk8c)
    {
        unk3b = 0;
    }
    else if (!unk3b)
    {
        LibPanelDrawArgs args;
        u64* buffer = reinterpret_cast<u64*>(unk40.dma_address);

        packet = packet_tag = buffer;
        args.position = &container->translation;
        args.rect = transition_state == 0 ? &unk18 : &unk50;
        args.address = container->unka4 + unk34;
        args.colors = colors;
        args.alpha = draw_alpha * container_alpha(container) / 128.0f;
        args.unk84 = unk84;
        args.unk8b = unk8b;
        args.unk8a = unk8a;
        u8* end = func_004C4B90(this, reinterpret_cast<u8*>(buffer) + 0x10, &args);
        *packet_tag = DMA_TAG((u32)(end - reinterpret_cast<u8*>(packet_tag) - 0x10) >> 4, DMA_TAG_ID_END, 0);
        unk3b = 1;
    }
}

/** @brief Run the open/close transition: grow or shrink the frame about its centre and fade it in or out. */
void LibPanel::func_00413D20()
{
    s32 state = transition_state;

    if (!state)
    {
        return;
    }

    switch (state)
    {
    case 1:
        centre_x = unk18.unk08 / 2.0f + unk18.unk00;
        centre_y = unk18.unk0c / 2.0f + unk18.unk04;
        unk50.unk08 = 48.0f;
        unk50.unk0c = 48.0f;
        step_width = (unk18.unk08 - 48.0f) / 4.7999997f;
        step_height = (unk18.unk0c - 48.0f) / 4.7999997f;
        draw_alpha = 0.0f;
        unk89 = 1;
        unk8c = 1;
        transition_state++;
        break;
    case 2:
        unk50.unk08 += step_width * field_rate(g_field_runtime);

        if (!(unk50.unk08 < unk18.unk08))
        {
            unk50.unk08 = unk18.unk08;
            transition_state++;
        }

        break;
    case 3:
        unk50.unk0c += step_height * field_rate(g_field_runtime);

        if (!(unk50.unk0c < unk18.unk0c))
        {
            unk50.unk0c = unk18.unk0c;
            transition_state++;
        }

        break;
    case 4:
        if (draw_alpha == 128.0f)
        {
            unk89 = 0;
            transition_state = 0;

            if (unk60)
            {
                static_cast<FieldClass15BA90*>(unk60)->pending = 1;
            }
        }

        break;
    case 5:
        if (unk60)
        {
            static_cast<FieldClass15BA90*>(unk60)->pending = 0;
        }

        centre_x = unk18.unk08 / 2.0f + unk18.unk00;
        centre_y = unk18.unk0c / 2.0f + unk18.unk04;
        unk50.unk08 = unk18.unk08;
        unk50.unk0c = unk18.unk0c;
        step_width = (unk50.unk08 - 48.0f) / 4.7999997f;
        step_height = (unk50.unk0c - 48.0f) / 4.7999997f;
        unk89 = 2;
        transition_state++;
        break;
    case 6:
        unk50.unk0c -= step_height * field_rate(g_field_runtime);

        if (unk50.unk0c <= 48.0f)
        {
            unk50.unk0c = 48.0f;
            transition_state++;
        }

        break;
    case 7:
        unk50.unk08 -= step_width * field_rate(g_field_runtime);

        if (unk50.unk08 <= 48.0f)
        {
            unk50.unk08 = 48.0f;
            transition_state++;
        }

        break;
    case 8:
        if (draw_alpha == 0.0f)
        {
            unk8c = 0;
            unk89 = 0;
            transition_state = 0;
        }

        break;
    }

    float alpha = draw_alpha;
    float rate = g_field_runtime->rate;

    if (unk89 == 1)
    {
        alpha += 13.333334f * rate;

        if (!(alpha <= 128.0f))
        {
            alpha = 128.0f;
        }
    }
    else if (unk89 == 2)
    {
        alpha -= 13.333334f * rate;

        if (alpha < 0.0f)
        {
            alpha = 0.0f;
        }
    }

    draw_alpha = alpha;
    unk50.unk00 = centre_x - unk50.unk08 / 2.0f;
    unk50.unk04 = centre_y - unk50.unk0c / 2.0f;
    needs_redraw = 1;
}

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
    s32 packet_offset;
};

/** Header of a decoded font texture block, 0x10 bytes into the block. */
struct LibFontTextureHeader
{
    u8 unk00[0xC];
    s32 image_offset;
    u8 unk10[4];
    s32 palette_offset;
    s16 palette_format;
};

/** Decoded glyph table chunk. */
struct LibFontGlyphHeader
{
    u8 unk00[0x1C];
    u32 table_size;
    s32 glyph_count;
};

/** One entry of the shared font's chunk list, followed by its compressed resource. */
struct LibFontChunk
{
    u32 tag;
    u8 unk04[8];
    s32 next_offset;
    ResidentResourceHeader resource;
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

    resident_store_entry(resident_get_entry_table(resident_get_system()), font, LIB_ENTRY_SHARED_FONT);
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

    ResidentDecodeObject* decoder = resident_system_get_decoder(resident_get_system());
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

/**
 * @brief Release the widgets marked for removal, then update and draw the rest and chain their packets behind a
 *        context-2 setup packet.
 * @param first Nonzero to chain the widget packets.
 * @param second Nonzero to update the widgets.
 * @param third Nonzero to draw the widgets.
 */
void LibContainer::func_0044B100(bool first, bool second, bool third)
{
    if (first && second)
    {
        func_00412C40(first, second, third);

        if (unkaf)
        {
            return;
        }
    }

    LibListSentinel* previous = &sentinel;

    for (;;)
    {
        LibWidget* child = reinterpret_cast<LibWidget*>(previous->next);

        if (reinterpret_cast<LibWidget*>(this) == child)
        {
            break;
        }

        if (child->unk3a)
        {
            LibListReceiver::unlink(child);
            child->container = 0;
            resident_enqueue_object(g_resident_release_queues, child);
        }
        else
        {
            previous = child;
        }
    }

    if (first && unkab)
    {
        u32 head = 0;
        u64* tail;
        LibWidget* child = reinterpret_cast<LibWidget*>(this);

        for (;;)
        {
            child = reinterpret_cast<LibWidget*>(child->next);

            if (reinterpret_cast<LibWidget*>(this) == child)
            {
                break;
            }

            if (!child->unk39 || !child->unk3d)
            {
                continue;
            }

            if (second && unkac && child->unk3e)
            {
                child->func_00413D20();
            }

            if (!third || !unkad || !child->unk39 || !child->unk3d || !child->visible)
            {
                continue;
            }

            if (geometry_dirty)
            {
                child->needs_redraw = 1;
            }

            if (child->needs_redraw)
            {
                child->unk3b = 0;
                child->needs_redraw = 0;
            }

            child->draw();

            if (!child->unk3b)
            {
                continue;
            }

            u32 address = (u32)child->packet & 0x0FFFFFFF;

            if (head == 0)
            {
                head = address;
            }
            else
            {
                *tail = DMA_TAG(*(u16*)tail, DMA_TAG_ID_NEXT, address);
            }

            tail = reinterpret_cast<u64*>(((u32)child->packet_tag & 0x0FFFFFFF) | 0x20000000);
        }

        if (third && unkad && head)
        {
            *tail = DMA_TAG(*(u16*)tail, DMA_TAG_ID_END, 0);
            u64* packet = reinterpret_cast<u64*>(unkD0.dma_address);
            packet[0] = DMA_TAG(5, DMA_TAG_ID_NEXT, head);
            packet[2] = GIF_TAG_NREG(1) | GIF_TAG_EOP | 4;
            packet[3] = 0xE;
            packet[4] = 0x1000F | ((u64)unkaa << 17);
            packet[5] = GS_REGISTER_TEST_2;
            // TODO: The target loads only the low word of ZBUF_1 (lwu); find the field it really reads.
            packet[6] = *reinterpret_cast<u32*>(&g_display->buffers[0].environment.context1.depth_buffer);
            packet[7] = GS_REGISTER_ZBUF_2;
            packet[8] = 0x61;
            packet[9] = GS_REGISTER_TEX1_2;
            packet[10] = GS_ALPHA_NORMAL;
            packet[11] = GS_REGISTER_ALPHA_2;
            unk63 = 1;
        }

        geometry_dirty = 0;
    }
}

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

/** @brief Destroy the list receiver and its sentinel. */
inline LibListReceiver::~LibListReceiver()
{
}

// TODO: The container's destructor inlines LibCallbackTransform's, which text_0044ABE0 keeps out of line, so the base
// destructor is only inline in this unit.
inline LibCallbackTransform::~LibCallbackTransform()
{
}

/** @brief Delete every attached widget, then release the drawing storage. */
LibContainer::~LibContainer()
{
    for (;;)
    {
        LibWidget* child = reinterpret_cast<LibWidget*>(sentinel.next);

        if (reinterpret_cast<LibWidget*>(this) == child)
        {
            break;
        }

        LibListReceiver::unlink(child);
        child->container = 0;
        delete child;
    }
}

extern "C" void func_004C74E0(LibTextWidget* object);

/**
 * @brief Point the text widget at a keyed text of one of the runtime's resource slots and lay it out once.
 * @param object Text widget.
 * @param slot Resource slot index.
 * @param key Key of the text in the slot's index.
 */
extern "C" void func_004C67C0(LibTextWidget* object, s32 slot, s32 key)
{
    object->resource_slot = &g_field_runtime->resource_slots[slot];
    object->unk100 = func_00465340(g_field_runtime, slot, key);
    object->unk70 = static_cast<u8*>(::operator new[](0x1000, 0));

    if (object->unk70)
    {
        func_004C74E0(object);
        delete[] object->unk70;
    }

    object->needs_redraw = 1;
}

/** @brief Lay the text out in the scratchpad and draw it, once. */
void LibClass178720::draw()
{
    if (unk100 == 0)
    {
        unk3b = 0;
        return;
    }

    if (!unk3b)
    {
        lib_restore_texture_cache(static_cast<LibRenderer*>(g_renderer));
        unk70 = reinterpret_cast<u8*>(0x70000000);
        func_004C74E0(this);
        draw_records(reinterpret_cast<LibDrawRecord*>(unk70), record_count);
        unk3b = 1;
    }
}

/**
 * @brief Set the text widget up for free text: no resource slot, a 1024 by 1024 area and storage for the records.
 * @param object Text widget.
 * @param capacity Record capacity.
 * @return Nonzero once the storage is allocated.
 */
extern "C" s32 func_004C6910(LibTextWidget* object, s32 capacity)
{
    object->set_rectangle(0.0f, 0.0f, 0.0f, 0.0f);
    object->unkfc = 0;
    object->pending = 0;

    if (!object->allocate_storage(0, capacity, 0, 0))
    {
        return 0;
    }

    object->unk18.unk0c = 1024.0f;
    object->unk18.unk08 = 1024.0f;
    object->resource_slot = 0;
    object->unk100 = 0;
    object->unk39 = 1;
    return 1;
}

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

extern "C" s32 func_004C7D40(LibTextWidget* object, s32 source, u32 key, u8 flag);

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

    state->drawing = ::operator new[](state->count * 32, 0);

    if (!state->drawing)
    {
        return 0;
    }

    func_004C74E0(object);
    delete[] (u8*)state->drawing;
    return &state->bounds;
}

/**
 * @brief Test whether an allocation record is in use.
 * @param record Allocation record.
 * @return Its allocated flag.
 */
static inline bool allocation_in_use(const ItemCreationAllocationRecord* record)
{
    return record->allocated;
}

extern "C" ResidentObject1B64F8* D_001B64F8;

extern "C" char* func_004642E0(void* context, s32 index);

extern "C" s32 func_00464040(LibDrawWidget* widget, u16* codes, const char* text);

extern "C" s32 func_00463E60(LibDrawWidget* widget, u16* codes, u16 id, s32 variant);

/**
 * @brief Count the glyphs the widget's text lays out, expanding numbers, names and item names.
 * @param widget Text widget.
 * @return Number of glyphs.
 */
extern "C" s32 func_004C6A40(LibTextWidget* widget)
{
    u16 codes[0x80];
    s32 count = 0;
    const u8* text;

    if (widget->pending)
    {
        text = static_cast<const u8*>(func_00465340(g_field_runtime, widget->source, widget->key));
    }
    else
    {
        text = static_cast<const u8*>(widget->unk100);
    }

    while (*text)
    {
        s32 c = *text++;

        if (c & 0x80)
        {
            s32 code = (c & 0x7F) | (*text++ << 7);

            if (code & 0x4000)
            {
                switch (code)
                {
                case 0x4002:
                case 0x4008:
                case 0x401A:
                case 0x4020:
                    text++;
                    break;
                case 0x4005:
                case 0x4006:
                case 0x400A:
                case 0x400C:
                case 0x400E:
                case 0x4014:
                case 0x4015:
                case 0x401E:
                    text += 4;
                    break;
                case 0x4012:
                    count += widget->format_number_codes(codes, g_field_runtime->message_arguments[*text++]);
                    break;
                case 0x4013:
                case 0x4021:
                {
                    s32 index = *text++;

                    index = code == 0x4013 ? index : g_field_runtime->message_arguments[index];
                    count += func_00464040(widget, codes, func_004642E0(widget, index));
                    break;
                }
                case 0x4022:
                case 0x4023:
                {
                    s32 value = g_field_runtime->message_arguments[*text++];
                    u16 id = 0;
                    s32 variant = 0;

                    if (code == 0x4022)
                    {
                        u16 key = value;
                        bool valid = false;

                        if (key > 0 && key < 0x2EF)
                        {
                            valid = true;
                        }

                        if (valid)
                        {
                            id = value;
                        }
                    }
                    else
                    {
                        LibGameState* state = reinterpret_cast<LibGameState*>(D_001B64F8);
                        s16 identifier = value;
                        bool valid = false;

                        if (identifier > 0 && identifier <= LIB_ALLOCATION_COUNT)
                        {
                            valid = true;
                        }

                        ItemCreationAllocationRecord* record;

                        if (valid)
                        {
                            record = reinterpret_cast<ItemCreationAllocationRecord*>(&state->allocations[identifier - 1]);
                        }
                        else
                        {
                            record = 0;
                        }

                        if (record != 0 && allocation_in_use(record))
                        {
                            id = record->definition_index() + 1;
                            variant = record->modification_number;
                        }
                    }

                    if (id)
                    {
                        count += func_00463E60(widget, codes, id, variant);
                    }

                    break;
                }
                case 0x4011:
                    while (*text)
                    {
                        text++;
                    }

                    text++;
                    break;
                case 0x401C:
                    while (*text)
                    {
                        count++;
                        text++;
                    }

                    text++;
                    break;
                case 0x401D:
                    count++;
                    text++;
                    break;
                }

                continue;
            }
        }

        count++;
    }

    return count;
}

extern "C" void lib_text_set_resource(LibTextWidget* object, s32 slot, u32 key, u8 flag)
{
    LibTextResourceState* state = (LibTextResourceState*)object;
    state->source = slot;
    state->key = key;
    state->flag = flag;
    state->pending = 1;
    state->redraw = 1;
}

/**
 * @brief Lay the text out and draw it, once: in the scratchpad, or in a heap block when it has more than 0x200
 *        glyphs.
 */
void LibTextWidget::draw()
{
    if (unk100 == 0)
    {
        unk3b = 0;
        return;
    }

    if (!unk3b)
    {
        if ((u32)unkb4 > 0x200)
        {
            unk70 = new (0) u8[unkb4 * sizeof(LibDrawRecord)];

            if (unk70 == 0)
            {
                return;
            }
        }
        else
        {
            lib_restore_texture_cache(static_cast<LibRenderer*>(g_renderer));
            unk70 = reinterpret_cast<u8*>(0x70000000);
        }

        func_004C74E0(this);
        draw_records(reinterpret_cast<LibDrawRecord*>(unk70), record_count);
        func_004C7010();

        if ((u32)unkb4 > 0x200)
        {
            delete[] unk70;
        }

        unk3b = 1;
    }
}

/**
 * @brief Step the animation of every glyph that is animated and started before the widget's time.
 * @param object Text widget.
 * @return Whether a glyph was stepped.
 */
static inline bool step_glyphs(LibTextWidget* object)
{
    LibClass178780* batch = static_cast<LibClass178780*>(object->unkfc);
    bool stepped = false;

    if (batch != 0 && batch->glyph_count > 0)
    {
        LibGlyphDraw6C* glyph = batch->glyphs;

        for (s32 i = 0; i < static_cast<LibClass178780*>(object->unkfc)->glyph_capacity; i++, glyph++)
        {
            if (glyph->unk60 && (u32)object->unk74 > glyph->unk64)
            {
                glyph->step();
                stepped = true;
            }
        }
    }

    return stepped;
}

/** @brief Load the pending text resource, then step the glyph animations and redraw when one moved. */
void LibTextWidget::func_00413D20()
{
    if (pending && !func_004C7D40(this, source, key, flag))
    {
        return;
    }

    if (step_glyphs(this))
    {
        needs_redraw = 1;
    }
}

/** Glyph placement record in a text resource: position, then the scale pair the glyph draws with. */
struct LibGlyphSource
{
    float x;
    float y;
    u8 unk08[0xC];
    float unk14;
    float unk18;
};

/**
 * @brief Write the visible glyphs of the widget's batch into its packet storage and chain the storage after the
 *        widget's packet tag.
 */
void LibTextWidget::func_004C7010()
{
    LibClass178780* batch = static_cast<LibClass178780*>(unkfc);

    if (batch != 0 && batch->glyph_count > 0)
    {
        s32 drawn = 0;
        u64* start = reinterpret_cast<u64*>(batch->storage.dma_address);
        u64* cursor = start;
        cursor += 2;
        LibContainer* owner = container;
        LibVector4 origin;
        origin.x = owner->translation.x + unk18.unk00 - unk78;
        origin.y = owner->translation.y + unk18.unk04 - unk7c;
        LibContainer* parent = container;
        u32 depth = parent->unka4 + 5;
        float scale = draw_alpha * container_alpha(parent) / 128.0f;
        LibGlyphDraw6C* glyph = static_cast<LibClass178780*>(unkfc)->glyphs;

        for (s32 i = 0; i < static_cast<LibClass178780*>(unkfc)->glyph_capacity; i++, glyph++)
        {
            if (glyph->unk60 && glyph->unk64 < reinterpret_cast<u32>(unk74))
            {
                const LibGlyphSource* source = reinterpret_cast<const LibGlyphSource*>(glyph->unk64);
                glyph->set_position(source->x, source->y);
                glyph->unk30 = source->unk14;
                glyph->unk34 = source->unk18;
                func_004535B0(glyph, &cursor, &origin, depth, scale, 0);
                drawn++;
            }
        }

        if (drawn > 0)
        {
            s32 address = reinterpret_cast<u32>(start) & 0x0FFFFFFF;
            *packet_tag = DMA_TAG(*reinterpret_cast<u16*>(packet_tag), DMA_TAG_ID_NEXT, address);
            *start = DMA_TAG((reinterpret_cast<u32>(cursor) - reinterpret_cast<u32>(start + 2)) / LIB_DRAW_QWORD_SIZE, DMA_TAG_ID_END, 0);
            packet_tag = start;
        }
    }
}

/**
 * @brief Step the animation of every glyph that is animated and started before the widget's time.
 * @param object Text widget.
 * @return Whether a glyph was stepped.
 */
extern "C" bool func_004C71E0(LibTextWidget* object)
{
    return step_glyphs(object);
}

/**
 * @brief Pick 0x200020 for codes whose low four bits are below 14, else 0x200030.
 * @param code Code.
 * @return Selected value.
 */
extern "C" s32 func_00451B60(s32 code);

/**
 * @brief Turn a button glyph code into the glyph of the pad button the player has mapped to it.
 * @param runtime Runtime holding the button map.
 * @param code Glyph code.
 * @return Glyph index.
 */
extern "C" s32 func_00464EF0(FieldRuntime* runtime, s32 code);

/**
 * @brief Lay out a pad-button glyph as a record at the pen and bind an animated glyph slot of the widget's batch to
 *        it, reusing the slot already bound to this text position.
 * @param widget Text widget.
 * @param text Text position of the glyph code.
 */
extern "C" void func_004C7290(LibTextWidget* widget, const u8* text)
{
    LibGlyphDraw6C* candidate;
    LibClass178780* batch;
    LibDrawRecord* record = widget->next_record;
    s32 glyph = func_00464EF0(g_field_runtime, *text);

    record->code = 0x401D;
    record->left = widget->pen_x;
    record->top = widget->pen_y;
    record->unk14.scale = widget->draw_scale;
    record->scale_y = widget->draw_scale_y;
    u32 size = func_00451B60(glyph);
    record->right = widget->pen_x + (float)(size & 0xFFFF) * widget->draw_scale;
    float height = (float)(size >> 16) * widget->draw_scale_y;
    record->bottom = widget->pen_y + height;
    widget->line_height = height;

    if (height < widget->min_height)
    {
        widget->min_height = height;
    }

    if (height > widget->max_height)
    {
        widget->max_height = height;
    }

    widget->pen_x = widget->unk90 + (widget->next_record->right + widget->unk88);
    widget->next_record++;
    widget->record_count++;
    batch = static_cast<LibClass178780*>(widget->unkfc);

    if (batch == 0)
    {
        return;
    }

    LibGlyphDraw6C* slot = 0;
    candidate = batch->glyphs;

    for (s32 i = 0; i < batch->glyph_capacity; i++, candidate++)
    {
        if (candidate->unk60)
        {
            if (candidate->unk68 == reinterpret_cast<u32>(text))
            {
                slot = candidate;
                break;
            }
        }
        else if (slot == 0)
        {
            slot = candidate;
        }
    }

    if (slot == 0)
    {
        return;
    }

    if (!slot->unk60)
    {
        batch->glyph_count++;
        slot->unk60 = 1;
        slot->unk68 = reinterpret_cast<u32>(text);
        slot->set_display_chunk(glyph + 0x22);
        slot->start(0);
    }

    slot->set_position(record->left, record->top);
    slot->unk30 = record->unk14.scale;
    slot->unk34 = record->scale_y;
    slot->unk64 = reinterpret_cast<u32>(record);
}

extern "C" void func_00463DD0(LibDrawWidget* widget, u16 id, s32 variant);

/**
 * @brief Lay the widget's text out line by line into its records, applying the style codes, and restore the style the
 *        text started with.
 * @param widget Text widget.
 */
extern "C" void func_004C74E0(LibTextWidget* widget)
{
    u32 tint = widget->tint;
    float scale = widget->draw_scale;
    float scale_y = widget->draw_scale_y;
    s32 align = widget->horizontal_align;
    float spacing = widget->unk88;
    float line_spacing = widget->unk8c;
    s32 total = 0;
    bool more = true;

    widget->pen_y = 0.0f;
    const u8* text = static_cast<const u8*>(widget->unk100);
    LibDrawRecord* records = reinterpret_cast<LibDrawRecord*>(widget->unk70);

    do
    {
        widget->begin_layout(records, widget->pen_y);

        for (;;)
        {
            s32 code = *text++;

            // TODO: The game sign-extends the code before this test, which a compare with a long zero gives.
            if (code == 0L)
            {
                more = false;
                break;
            }

            if (code & 0x80)
            {
                code = (code & 0x7F) | (*text++ << 7);

                if (code & 0x4000)
                {
                    switch (code)
                    {
                    case 0x4000:
                    case 0x4001:
                        goto line_end;
                    case 0x4002:
                        widget->horizontal_align = *text++;
                        break;
                    case 0x4003:
                        widget->horizontal_align = align;
                        break;
                    case 0x4005:
                    case 0x4006:
                    case 0x4014:
                    case 0x4015:
                    case 0x401E:
                        text += 4;
                        break;
                    case 0x401A:
                    case 0x4020:
                        text++;
                        break;
                    case 0x4008:
                        widget->tint = widget->get_palette_color(*text++);
                        break;
                    case 0x4009:
                        widget->tint = tint;
                        break;
                    case 0x400A:
                    {
                        float factor;
                        u8* bytes = reinterpret_cast<u8*>(&factor);

                        bytes[0] = text[0];
                        bytes[1] = text[1];
                        bytes[2] = text[2];
                        bytes[3] = text[3];
                        text += 4;
                        widget->draw_scale = factor * scale;
                        widget->draw_scale_y = factor * scale_y;
                        break;
                    }
                    case 0x400B:
                        widget->draw_scale = scale;
                        widget->draw_scale_y = scale_y;
                        break;
                    case 0x400C:
                    {
                        u8* bytes = reinterpret_cast<u8*>(&widget->unk88);

                        bytes[0] = text[0];
                        bytes[1] = text[1];
                        bytes[2] = text[2];
                        bytes[3] = text[3];
                        text += 4;
                        break;
                    }
                    case 0x400D:
                        widget->unk88 = spacing;
                        break;
                    case 0x400E:
                    {
                        u8* bytes = reinterpret_cast<u8*>(&widget->unk8c);

                        bytes[0] = text[0];
                        bytes[1] = text[1];
                        bytes[2] = text[2];
                        bytes[3] = text[3];
                        text += 4;
                        break;
                    }
                    case 0x400F:
                        widget->unk8c = line_spacing;
                        break;
                    case 0x4010:
                        widget->begin_run();
                        break;
                    case 0x4011:
                    {
                        const u8* start = text;

                        while (*text)
                        {
                            text++;
                        }

                        widget->end_run(const_cast<u8*>(start), text - start);
                        text++;
                        break;
                    }
                    case 0x4012:
                        widget->add_number(g_field_runtime->message_arguments[*text++]);
                        break;
                    case 0x4013:
                    case 0x4021:
                    {
                        s32 index = *text++;

                        index = code == 0x4013 ? index : g_field_runtime->message_arguments[index];
                        widget->add_text(func_004642E0(widget, index));
                        break;
                    }
                    case 0x4022:
                    case 0x4023:
                    {
                        s32 value = g_field_runtime->message_arguments[*text++];
                        u16 id = 0;
                        s32 variant = 0;

                        if (code == 0x4022)
                        {
                            id = value;
                        }
                        else
                        {
                            LibGameState* state = reinterpret_cast<LibGameState*>(D_001B64F8);
                            s16 identifier = value;
                            bool valid = false;

                            if (identifier > 0 && identifier <= LIB_ALLOCATION_COUNT)
                            {
                                valid = true;
                            }

                            ItemCreationAllocationRecord* record;

                            if (valid)
                            {
                                record = reinterpret_cast<ItemCreationAllocationRecord*>(&state->allocations[identifier - 1]);
                            }
                            else
                            {
                                record = 0;
                            }

                            if (record != 0 && allocation_in_use(record))
                            {
                                id = record->definition_index() + 1;
                                variant = record->modification_number;
                            }
                        }

                        func_00463DD0(widget, id, variant);
                        break;
                    }
                    case 0x401C:
                    {
                        const u8* start = text;

                        while (*text)
                        {
                            text++;
                        }

                        widget->add_number_record(const_cast<u8*>(start), text - start);
                        text++;
                        break;
                    }
                    case 0x401D:
                        func_004C7290(widget, text++);
                        break;
                    }

                    continue;
                }
            }

            widget->add_glyph(code);
        }

    line_end:
        if (widget->record_count > 0)
        {
            widget->func_004637A0(records, widget->record_count);
            records += widget->record_count;
            total += widget->record_count;
        }
    } while (more);

    widget->align_records_vertically(reinterpret_cast<LibDrawRecord*>(widget->unk70), total);
    widget->unk74 = reinterpret_cast<u8*>(records);
    widget->record_count = total;
    widget->tint = tint;
    widget->draw_scale = scale;
    widget->draw_scale_y = scale_y;
    widget->unk88 = spacing;
    widget->unk8c = line_spacing;
    widget->horizontal_align = align;
}

/**
 * @brief Count what the widget's text holds: glyphs found in its resource (or the runtime's first slot) and
 *        missing ones, the space control codes add, line breaks, quoted string bytes and button glyphs.
 * @param widget Text widget.
 */
extern "C" void func_004C79C0(LibTextWidget* widget)
{
    widget->unkb0 = 0;
    widget->unkac = 0;
    widget->unka8 = 0;
    widget->unka4 = 0;
    widget->glyph_count = 0;
    widget->unkb4 = 0;
    const u8* text = static_cast<const u8*>(widget->unk100);

    while (*text)
    {
        s32 code = *text++;

        if (code & 0x80)
        {
            code = (code & 0x7F) | (*text++ << 7);

            if (code & 0x4000)
            {
                switch (code)
                {
                case 0x4002:
                case 0x4008:
                case 0x401A:
                case 0x4020:
                    text++;
                    break;
                case 0x4005:
                case 0x4006:
                case 0x400A:
                case 0x400C:
                case 0x400E:
                case 0x4014:
                case 0x4015:
                case 0x401E:
                    text += 4;
                    break;
                case 0x4012:
                    text++;
                    widget->unka4 += 11;
                    break;
                case 0x4013:
                case 0x4021:
                    text++;
                    widget->unka4 += 0x20;
                    break;
                case 0x4022:
                case 0x4023:
                    text++;
                    widget->unka8 += 0x40;
                    break;
                case 0x4010:
                    widget->unkb4++;
                    widget->unkac++;
                    break;
                case 0x4011:
                    while (*text)
                    {
                        text++;
                        widget->unkb0++;
                    }

                    text++;
                    break;
                case 0x401C:
                    widget->unkb4++;
                    widget->unkac++;

                    while (*text)
                    {
                        text++;
                        widget->unkb0++;
                    }

                    text++;
                    break;
                case 0x401D:
                    text++;
                    widget->unkb4++;
                    widget->glyph_count++;
                    break;
                }

                continue;
            }
        }

        s32 index;
        LibManagedResourceSlot* slot;

        slot = widget->resource_slot;
        index = code - 1;

        if (slot->flag)
        {
            if (code <= 300)
            {
                slot = &g_field_runtime->resource_slots[0];
            }
            else
            {
                index -= 300;
            }
        }

        if (index < slot->loaded)
        {
            widget->unka4++;
        }
        else
        {
            widget->unka8++;
        }
    }

    widget->unkb4 += widget->unka4 + widget->unka8;
}

/**
 * @brief Hand the widget's attached object to the resident release queue, then release its drawing storage.
 * @param widget Widget to clear.
 */
static inline void lib_text_release_glyphs(LibTextWidget* widget)
{
    if (widget->unkfc != 0)
    {
        resident_enqueue_object(g_resident_release_queues, widget->unkfc);
        widget->unkfc = 0;
    }

    widget->release_storage();
}

/**
 * @brief Hand the widget's attached object to the resident release queue, then release its drawing storage.
 * @param widget Widget to clear.
 */
extern "C" void func_004C7D00(LibTextWidget* widget)
{
    lib_text_release_glyphs(widget);
}

/**
 * @brief Allocate a glyph batch's drawing storage and glyph states for a glyph count.
 * @param batch Glyph batch.
 * @param count Number of glyphs.
 * @return Whether both allocations succeeded.
 */
static inline bool lib_glyph_batch_init(LibClass178780* batch, s32 count)
{
    batch->glyph_capacity = count;
    batch->glyph_count = 0;

    if (count > 0)
    {
        if (!lib_allocate_drawing_storage(&batch->storage, (u32)(count * 0x70 + 0x10) / 8))
        {
            return 0;
        }

        batch->glyphs = new (0) LibGlyphDraw6C[count];

        if (batch->glyphs == 0)
        {
            return 0;
        }
    }

    return 1;
}

/**
 * @brief Allocate drawing storage and glyph states for a glyph count.
 * @param count Number of glyphs.
 * @return One on success, or zero when an allocation fails.
 */
s32 LibClass178780::init(s32 count)
{
    glyph_capacity = count;
    glyph_count = 0;

    if (count > 0)
    {
        if (!lib_allocate_drawing_storage(&storage, (u32)(count * 0x70 + 0x10) / 8))
        {
            return 0;
        }

        glyphs = new (0) LibGlyphDraw6C[count];

        if (glyphs == 0)
        {
            return 0;
        }
    }

    return 1;
}

/**
 * @brief Measure the widget's text.
 * @param object Text widget.
 */
extern "C" void func_004C79C0(LibTextWidget* object);

/**
 * @brief Point the text widget at a keyed text of a resource slot: measure it, allocate its drawing storage and its
 *        glyph states. Slot or key zero leaves the widget without text.
 * @param object Text widget.
 * @param slot Resource slot index.
 * @param key Key of the text in the slot's index.
 * @param flag Nonzero to reset the drawing state first.
 * @return One, or zero when an allocation failed.
 */
extern "C" s32 func_004C7D40(LibTextWidget* object, s32 slot, u32 key, u8 flag)
{
    object->unk39 = 0;
    lib_text_release_glyphs(object);

    if (flag)
    {
        object->reset_drawing_state();
    }

    // TODO: The game sign-extends the slot before testing it, which a compare with a long zero gives; I don't know
    // what the original compared against.
    if (slot == 0L || key == 0)
    {
        object->unk100 = 0;
    }
    else
    {
        object->resource_slot = &g_field_runtime->resource_slots[slot];
        object->unk100 = func_00465340(g_field_runtime, slot, key);
        func_004C79C0(object);

        if (!object->allocate_storage(object->unka4, object->unka8, object->unkac, object->unkb0))
        {
            return 0;
        }

        if (object->glyph_count > 0)
        {
            object->unkfc = new (0) LibClass178780;

            if (object->unkfc == 0)
            {
                return 0;
            }

            s32 count = object->glyph_count;

            if (!lib_glyph_batch_init(static_cast<LibClass178780*>(object->unkfc), count))
            {
                return 0;
            }
        }
    }

    object->pending = 0;
    object->unk39 = 1;
    return 1;
}

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

/** @brief Delete the attached list object, then destroy the drawing widget. */
inline LibTextWidget::~LibTextWidget()
{
    if (unkfc != 0)
    {
        delete unkfc;
        unkfc = 0;
    }
}

/** @brief Destroy the text widget. */
LibClass178720::~LibClass178720()
{
}

/** @brief Free the glyphs and the drawing storage. */
LibClass178780::~LibClass178780()
{
    if (glyphs != 0)
    {
        delete[] glyphs;
        glyphs = 0;
    }
}

/** Model with three owned list objects, with vtables D_1788B0 and D_178964 in main data. */
class LibClass1788B0 : public LibModel
{
public:
    /** @brief Construct the model with its defaults. */
    LibClass1788B0();

    /** @brief Destroy the owned list objects, then the model. */
    virtual ~LibClass1788B0()
    {
        for (s32 i = 0; i < 3; i++)
        {
            if (unk83c[i] != 0)
            {
                unk83c[i]->destroy();
                unk83c[i] = 0;
            }
        }
    }

    /**
     * @brief Report no box-culling centre.
     * @param output Unused.
     * @return Zero.
     */
    virtual s32 get_box_cull_center(void* output);

    /** @brief Destroy the model's attachments, then the model. */
    virtual void destroy();

    /** @brief Draw the model. */
    virtual void render();

    virtual const LibVector4* get_bounding_sphere();

    virtual void build_packet(const void* matrix, void* context);

    virtual LibTransformOwner* clone();

    /**
     * @brief Return the before packet's size.
     * @return Eleven.
     */
    virtual s32 get_before_packet_size();

    /**
     * @brief Return the after packet's size.
     * @return One.
     */
    virtual s32 get_after_packet_size();

    virtual s32 build_before_packet(s32 block, s32 address);

    /**
     * @brief Chain the model's after block in with a DMA reference, unless the model has a display manager or
     *        D_001B65B0 is clear.
     * @param block Block address (uncached).
     * @param address Address of the model's draw packet.
     * @return End of what was written.
     */
    virtual s32 build_after_packet(s32 block, s32 address);

    /**
     * @brief Build from another model of this class, sharing its owner.
     * @param links Update list for the new model.
     * @param source Model to copy.
     * @return Nonzero on success.
     */
    virtual s32 func_004C8720(LibUpdateList* links, LibClass1788B0* source);

    /**
     * @brief Build from a model of the source class, sharing its owner.
     * @param links Update list for the new model.
     * @param source Model to copy.
     * @return Nonzero on success.
     */
    virtual s32 func_004C8680(LibUpdateList* links, LibClass173380* source);

    /**
     * @brief Virtual slot 0x100.
     * @param index Index.
     * @param matrix Matrix.
     * @param context Context.
     * @param scale Scale.
     */
    virtual void func_004C8860(s32 index, void* matrix, void* context, float scale);

    /**
     * @brief Set the two values at 0x864.
     * @param first Value at 0x864.
     * @param second Value at 0x868.
     */
    void set_unk864(float first, float second)
    {
        unk864 = first;
        unk868 = second;
    }

    u8 unk820;
    u8 unk821;
    u8 unk822;
    u8 unk823;
    u8 unk824;
    u8 unk825;
    u8 unk826;
    u8 unk827;
    float sphere_radius_scale;
    float unk82c;
    float unk830;
    float unk834;
    LibModel* unk838;
    LibTransformOwner* unk83c[3];
    u8 unk848[8];
    FieldVec4B unk850;
    float unk860;
    float unk864;
    float unk868;
    u8 unk86c[4];
};

/** Extra shadow model a LibClass1788B0 keeps for each light past its first (vtables D_1787A0 and D_178854). */
class LibClass1787A0 : public LibClass1788B0
{
public:
    /** @brief Create the shadow model with no light and no lifetime. */
    LibClass1787A0()
    {
        lifetime = 0;
        light_index = -1;
        type_id = 0x111;
    }

    /** @brief Destroy the model. */
    virtual ~LibClass1787A0();

    /** @brief Draw the model the way a plain LibModel does. */
    virtual void render();

    /**
     * @brief Clear the packet-in-flight flag and mark the packet sent.
     * @param channel DMA channel; unused.
     */
    virtual void complete_dma(u32 channel);

    /**
     * @brief Set the light this shadow is drawn for.
     * @param index Light number in the caster's shadow light list.
     */
    void set_light_index(s8 index)
    {
        light_index = index;
    }

    /**
     * @brief Count one frame off the shadow's lifetime.
     * @return True when the lifetime ran out.
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
    u8 unk878[8];
};

/** @brief Destroy the model. */
LibClass1787A0::~LibClass1787A0()
{
}

/**
 * @brief Report no box-culling centre.
 * @param output Unused.
 * @return Zero.
 */
s32 LibClass1788B0::get_box_cull_center(void* output)
{
    return 0;
}

/**
 * @brief Return the before packet's size.
 * @return Eleven.
 */
s32 LibClass1788B0::get_before_packet_size()
{
    return 11;
}

/**
 * @brief Return the after packet's size.
 * @return One.
 */
s32 LibClass1788B0::get_after_packet_size()
{
    return 1;
}

extern "C" u8 D_001B65B0;
extern "C" s32 D_001B65B4;
extern "C" LibMatrix44Value D_0050CBC0;
extern "C" LibMatrix44Value D_0050CC00;

/**
 * @brief Step the manager's current camera with Lib's two camera work buffers when the step is enabled.
 * @param manager Display manager whose camera to step.
 */
void func_004C8390(LibDisplayManager* manager)
{
    if (D_001B65B0 && manager->current_display != 0)
    {
        func_004E22B0(static_cast<LibCamera*>(manager->current_display), D_001B65B4, &D_0050CBC0, &D_0050CC00);
    }
}

/**
 * @brief Chain the model's after block in with a DMA reference, unless the model has a display manager or D_001B65B0
 *        is clear.
 * @param block Block address (uncached).
 * @param address Address of the model's draw packet.
 * @return End of what was written.
 */
s32 LibClass1788B0::build_after_packet(s32 block, s32 address)
{
    if (!D_001B65B0)
    {
        return block;
    }

    if (display_manager)
    {
        return block;
    }

    *(u64*)block = DMA_TAG(10, DMA_TAG_ID_REF, address + 0x780);
    return block + 0x10;
}

/**
 * @brief Copy a matrix's four rows, each as one 128-bit value.
 * @param rows Destination rows.
 * @param matrix Matrix to copy.
 */
static inline void copy_matrix_rows(LibVector4* rows, const LibMatrix44Value* matrix)
{
    ((unsigned __int128*)rows)[0] = ((const unsigned __int128*)matrix)[0];
    ((unsigned __int128*)rows)[1] = ((const unsigned __int128*)matrix)[1];
    ((unsigned __int128*)rows)[2] = ((const unsigned __int128*)matrix)[2];
    ((unsigned __int128*)rows)[3] = ((const unsigned __int128*)matrix)[3];
}

/** One matrix and the VIF codes that unpack it into VU1 data memory. */
struct LibMatrixUpload
{
    union
    {
        u32 vif_codes[4];
        unsigned __int128 vif_qword;
    };

    LibVector4 rows[4];
};

/** Packet that uploads the two camera matrices ahead of a model's own packet. */
struct LibCameraMatrixPacket
{
    u64 dma_tag;
    u64 unk08;
    LibMatrixUpload first;
    LibMatrixUpload second;
};

/**
 * @brief Upload the two camera work matrices before the model's packet when it has no display manager of its own.
 * @param block Packet to write.
 * @param address Unused.
 * @return The end of the written packet.
 */
s32 LibClass1788B0::build_before_packet(s32 block, s32 address)
{
    if (!D_001B65B0)
    {
        return block;
    }

    if (display_manager)
    {
        return block;
    }

    LibCameraMatrixPacket* packet = reinterpret_cast<LibCameraMatrixPacket*>(block);
    packet->dma_tag = DMA_TAG(10, DMA_TAG_ID_CNT, 0);
    packet->first.vif_qword = 0;
    packet->first.vif_codes[3] = VIF_UNPACK(VIF_UNPACK_V4_32, 4, 0x34);
    copy_matrix_rows(packet->first.rows, &D_0050CBC0);
    packet->second.vif_qword = 0;
    packet->second.vif_codes[3] = VIF_UNPACK(VIF_UNPACK_V4_32, 4, 0x3D);
    copy_matrix_rows(packet->second.rows, &D_0050CC00);
    return block + sizeof(LibCameraMatrixPacket);
}

/** @brief Draw the model the way a plain LibModel does. */
void LibClass1787A0::render()
{
    LibModel::render();
}

/**
 * @brief Clear the packet-in-flight flag and mark the packet sent.
 * @param channel DMA channel; unused.
 */
void LibClass1787A0::complete_dma(u32 channel)
{
    dma_pending = 0;
    unk62 = 1;
}

/** @brief Draw the attached objects whose packets are built, then the model, or finish at once when it's hidden. */
void LibClass1788B0::render()
{
    for (s32 i = 2; i >= 0; i--)
    {
        LibTransformOwner* child = unk83c[i];

        if (child && child->unk63)
        {
            child->render();
        }
    }

    if (unk826)
    {
        LibModel::complete_dma(0);
    }
    else
    {
        LibModel::render();
    }
}

/**
 * @brief Make a copy of the model built from this one and linked to it.
 * @return The copy, or null when it couldn't be built.
 */
LibTransformOwner* LibClass1788B0::clone()
{
    LibClass1788B0* copy = new (0) LibClass1788B0;

    if (copy == 0)
    {
        return 0;
    }

    if (!copy->func_004C8720(0, this))
    {
        return 0;
    }

    add_clone(copy);
    lib_object_set_list_kind(this, LIB_LIST_KIND_LATE_MODEL);
    return copy;
}

/**
 * @brief Build from a model of the source class, sharing its owner.
 * @param links Update list for the new model.
 * @param source Model to copy.
 * @return Nonzero on success.
 */
s32 LibClass1788B0::func_004C8680(LibUpdateList* links, LibClass173380* source)
{
    if (!LibModel::build_from(links, source))
    {
        return 0;
    }

    LibModel* owner = source->unk830;
    unk838 = owner;
    owner->unk790++;
    unk821 = source->unk836;
    unk822 = source->unk837;
    unk825 = source->unk835;
    unk823 = source->unk834;
    sphere_radius_scale = source->unk848;
    copy_vector(&unk850, &source->unk820);
    unk82c = source->unk854;
    unk830 = source->unk858;
    return 1;
}

/**
 * @brief Build from another model of this class, sharing its owner.
 * @param links Update list for the new model.
 * @param source Model to copy.
 * @return Nonzero on success.
 */
s32 LibClass1788B0::func_004C8720(LibUpdateList* links, LibClass1788B0* source)
{
    if (!LibModel::build_from(links, source))
    {
        return 0;
    }

    LibModel* owner = source->unk838;
    unk838 = owner;
    owner->unk790++;
    unk820 = source->unk820;
    unk59c = unk820 ? 2 : 0;
    unk59d_0 = 1;
    unk821 = source->unk821;
    unk822 = source->unk822;
    unk825 = source->unk825;
    unk823 = source->unk823;
    sphere_radius_scale = source->sphere_radius_scale;
    unk850.set(source->unk850);
    unk82c = source->unk82c;
    unk830 = source->unk830;
    unk860 = source->unk860;
    set_unk864(source->unk864, source->unk868);
    return 1;
}

/**
 * @brief Return the model's bounding sphere with its radius scaled.
 * @return Bounding sphere.
 */
const LibVector4* LibClass1788B0::get_bounding_sphere()
{
    LibVector4 sphere;
    copy_vector(&sphere, LibModel::get_bounding_sphere());
    sphere.w *= sphere_radius_scale;
    copy_vector(&bounding_sphere, &sphere);
    return &bounding_sphere;
}

/** Ground the second kind of shadow model is cast on, or null for none. */
extern "C" LibShadowGround* D_001B65AC;

/**
 * @brief Set this shadow model up for one of the caster's lights: the shadow plane (case 1: a flat plane through the
 *        caster; case 2: the ground under three projected points), the light's shadow matrix, the shadow's fade, then
 *        the packet.
 * @param index Light number in the caster's shadow light list.
 * @param matrix Camera.
 * @param context Packet building context.
 * @param scale Light weight scale.
 */
void LibClass1788B0::func_004C8860(s32 index, void* matrix, void* context, float scale)
{
    LibModel* caster = unk838;
    LibShadowLightList* lights = &caster->shadow_lights;

    switch (unk823)
    {
    case 1:
    {
        FieldVec4B origin;
        origin.x = caster->transform.m[0][3];
        origin.y = caster->transform.m[1][3];
        origin.z = caster->transform.m[2][3];
        origin.w = 1.0f;
        unk850.x = 0.0f;
        unk850.y = 1.0f;
        unk850.z = 0.0f;
        unk850.w = -origin.y + unk860;
        break;
    }
    case 2:
    {
        if (D_001B65AC == 0)
        {
            break;
        }

        FieldVec4B origin;
        FieldVec4B lowered;
        FieldVec4B first;
        FieldVec4B second;
        FieldVec4B third;
        LibMatrix44Value shadow;
        FieldVec4B direction;
        origin.x = caster->transform.m[0][3];
        origin.y = caster->transform.m[1][3];
        origin.z = caster->transform.m[2][3];
        origin.w = 1.0f;
        lowered.x = origin.x;
        lowered.y = origin.y - unk868;
        lowered.z = origin.z;
        lowered.w = origin.w;
        unk850.x = 0.0f;
        unk850.y = -1.0f;
        unk850.z = 0.0f;
        unk850.w = D_001B65AC->get_height(&origin, this);
        LibLight* light = lights->lights[index];

        if (light->kind & 3)
        {
            const FieldVec4B* position = reinterpret_cast<const FieldVec4B*>(&light->position);
            lib_build_projective_shadow_matrix(&shadow, (const FieldVec4A*)position, (const FieldVec4A*)&unk850);
            direction = origin - *position;
            lib_normalize_vector3(&direction.x);
        }
        else
        {
            const FieldVec4B* position = reinterpret_cast<const FieldVec4B*>(&light->direction);
            lib_build_directional_shadow_matrix(&shadow, (const FieldVec4A*)position, (const FieldVec4A*)&unk850);
            direction.set(*position);
        }

        vu0_dot_matrix_rows(&shadow, &origin, &first);
        // TODO: The game divides by w here and never uses the result.
        float inverse = 1.0f / first.w;
        vu0_divide_by_w(&first, &first);
        vu0_dot_matrix_rows(&shadow, &lowered, &second);
        inverse = 1.0f / second.w;
        vu0_divide_by_w(&second, &second);
        float abs_x = ee_abs(direction.x);
        third.w = 1.0f;
        float abs_z = ee_abs(direction.z);

        if (abs_x < 0.000001f && abs_z < 0.000001f)
        {
            third.x = first.x + unk864;
            third.y = 0.0f;
            third.z = first.z;
        }
        else
        {
            third.x = first.x + direction.z * unk864;
            third.y = 0.0f;
            third.z = first.z - direction.x * unk864;
        }

        first.y = D_001B65AC->get_height(&first, this) - unk860;
        second.y = D_001B65AC->get_height(&second, this) - unk860;
        third.y = D_001B65AC->get_height(&third, this) - unk860;
        func_004CC7A0(&unk850.x, &first.x, &second.x, &third.x);

        if (unk850.y < 0.0f)
        {
            unk850 *= -1.0f;
        }

        break;
    }
    }

    LibMatrix44Value projection;
    LibLight* light = lights->lights[index];

    if (light->kind & 3)
    {
        lib_build_projective_shadow_matrix(&projection, (const FieldVec4A*)&light->position, (const FieldVec4A*)&unk850);
    }
    else
    {
        lib_build_directional_shadow_matrix(&projection, (const FieldVec4A*)&light->direction, (const FieldVec4A*)&unk850);
    }

    if (unk821 || unk822)
    {
        LibVector4 color;
        *reinterpret_cast<unsigned __int128*>(&color) = *reinterpret_cast<const unsigned __int128*>(&base_color_factor);
        float alpha = 1.0f;

        if (unk821)
        {
            alpha = 0.01f * (unk82c * (lights->weights[index] * scale));

            if (alpha <= 0.0f)
            {
                return;
            }
        }

        if (unk822)
        {
            FieldVec4B position;
            position.x = transform.m[0][3];
            position.y = transform.m[1][3];
            position.z = transform.m[2][3];
            position.w = 1.0f;
            float distance = unk850.w + (unk850.x * position.x + unk850.y * position.y + unk850.z * position.z);
            float length_squared = unk850.x * unk850.x + unk850.y * unk850.y + unk850.z * unk850.z;

            if (!(distance <= 0.0f) && unk823 != 1)
            {
                alpha = 0.0f;
            }
            else
            {
                float fade = 0.001f * (unk830 * (-distance * ee_rsqrt_in_place(length_squared, 1.0f)));

                if (!(fade <= 1.0f))
                {
                    alpha /= fade;
                }
            }
        }

        if (alpha <= 0.001f)
        {
            return;
        }

        alpha = ee_min(alpha, 1.0f);
        color.w = alpha;
        *reinterpret_cast<unsigned __int128*>(&base_color_factor) = *reinterpret_cast<const unsigned __int128*>(&color);
        update_combined_color_factor();
    }

    vu0_multiply_matrix_output_first(&transform, &projection, &transform);
    transform_dirty = 1;
    unk66 = 1;
    LibModel::build_packet(matrix, context);
}

/** @brief Destroy the three held objects, then destroy the model. */
void LibClass1788B0::destroy()
{
    for (s32 i = 0; i < 3; i++)
    {
        if (unk83c[i] != 0)
        {
            unk83c[i]->destroy();
            unk83c[i] = 0;
        }
    }

    LibModel::destroy();
}

/** Most lights a LibClass1788B0 shadow draws shadows for. */
extern "C" u8 D_001B6294;

/** Frames a LibClass1788B0 shadow's extra child lives without being chosen again. */
extern "C" s32 D_001B6298;

/**
 * @brief Pick the caster's strongest lights (up to unk825), keep one child shadow model per extra light, and build the
 *        shadows of the children and this model.
 * @param matrix Camera.
 * @param context Packet building context.
 */
void LibClass1788B0::build_packet(const void* matrix, void* context)
{
    if (unk838 == 0)
    {
        return;
    }

    if (unk838->type_id == 2)
    {
        return;
    }

    if (!unk838->unk63)
    {
        func_004A59D0(unk838, context);
    }

    LibModel* caster = unk838;
    s32 count = caster->shadow_lights.count;
    LibShadowLightList* lights = &caster->shadow_lights;

    if (count == 0)
    {
        return;
    }

    s32 limit = unk825;

    if (D_001B6294 < limit)
    {
        limit = D_001B6294;
    }

    s32 visible = 0;
    float total = unk834;
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
        if (unk83c[i])
        {
            static_cast<LibClass1787A0*>(unk83c[i])->light_index = -1;

            if (static_cast<LibClass1787A0*>(unk83c[i])->expire())
            {
                LibClass1788B0* child = static_cast<LibClass1788B0*>(unk83c[i]);

                if (child->unk838)
                {
                    if (child->unk838->unk790)
                    {
                        child->unk838->unk790--;
                    }

                    child->unk838 = 0;
                }

                unk83c[i]->destroy();
                unk83c[i] = 0;
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
            if (unk83c[i - 1] == 0)
            {
                LibClass1787A0* child = new (0) LibClass1787A0;

                if (child)
                {
                    if (child->func_004C8720(0, this))
                    {
                        unk83c[i - 1] = child;
                    }
                    else
                    {
                        child->destroy();
                    }
                }
            }

            if (unk83c[i - 1])
            {
                static_cast<LibClass1787A0*>(unk83c[i - 1])->lifetime = D_001B6298;
                static_cast<LibClass1787A0*>(unk83c[i - 1])->set_light_index(order[i]);
            }
        }
    }

    bool drawn = false;

    for (s32 i = 2; i >= 0; i--)
    {
        if (unk83c[i] == 0)
        {
            continue;
        }

        s32 index = static_cast<LibClass1787A0*>(unk83c[i])->light_index;
        unk83c[i]->unk63 = 0;

        if (index >= 0)
        {
            unk83c[i]->unk62 = 0;
            unk83c[i]->update_transform_matrix();
            static_cast<LibClass1788B0*>(unk83c[i])->func_004C8860(index, const_cast<void*>(matrix), context, total);

            if (unk83c[i]->unk63)
            {
                drawn = true;
            }
        }
    }

    unk826 = 0;
    func_004C8860(order[0], const_cast<void*>(matrix), context, total);

    if (drawn && !unk63)
    {
        unk63 = 1;
        unk826 = 1;
    }
}

extern "C" void func_004C94D0(void* object, const unsigned __int128* value)
{
    LibVectorField850View* state = (LibVectorField850View*)object;
    copy_vector(&state->value850, (const LibVector4*)value);
}

/** @brief Construct the model with its defaults. */
LibClass1788B0::LibClass1788B0()
{
    type_id = 0x110;
    unk826 = 0;
    unk820 = 0;
    unk823 = 0;
    unk824 = 0;
    unk838 = 0;
    unk850 = FieldVec4A(0.0f, 1.0f, 0.0f, 1.0f);
    unk821 = 0;
    unk822 = 0;
    unk82c = 100.0f;
    unk830 = 50.0f;
    unk834 = 1.0f;
    unk825 = 4;
    unk67 = 0;

    for (s32 i = 0; i < 3; i++)
    {
        unk83c[i] = 0;
    }
}


/** @brief Destroy the entry. */
LibClass1789C0::~LibClass1789C0()
{
}

/**
 * @brief Return the entry's type code.
 * @return 67.
 */
s32 LibClass1789C0::func_slot14()
{
    return 67;
}

/** Model that owns morph targets; only the flag a morph target sets is known. */
struct LibMorphOwner
{
    u8 unk00[0x8D];
    u8 unk8d_0 : 1;
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

/**
 * @brief Note whether every bit is set, count the idle frames down and rewind the records.
 * @param root Model transform; unused.
 * @return Zero on the step the countdown ends, otherwise one.
 */
s32 LibClass1789C0::func_slot1C(LibTransform* root)
{
    if (shape->bit_count == shape->unk08)
    {
        unk19 = 1;
    }
    else
    {
        unk19 = 0;
    }

    if (idle_frames != 0 && --idle_frames == 0)
    {
        if (unk18 && list)
        {
            list->unk8d_1 = 1;
        }

        unk18 = 0;
        return 0;
    }

    cursor = records;
    return 1;
}

/**
 * @brief Use a morph shape resource without owning it, and apply its weight.
 * @param value Resource data.
 */
void LibClass1789C0::set_borrowed_data(void* value)
{
    data = value;
    data_is_borrowed = 1;
    shape = reinterpret_cast<LibMorphShape*>(static_cast<u8*>(value) + 0x10);
    u32* words = shape->words;
    u32 count = shape->bit_count;
    bits.borrow_words(count, words);
    records = reinterpret_cast<u8*>(shape) + shape->records_offset;
    lib_morph_target_set_weight(reinterpret_cast<LibMorphTarget*>(this), shape->weight);
}

/** @brief Start as an unattached entry of kind 2 with unk54 set to three. */
LibClass1789C0::LibClass1789C0()
{
    unk19 = 0;
    unk0f = 2;
    weight = 0.0f;
    idle_frames = 3;
}

/** @brief Start unattached, with unk0e set. */
LibClass174C90::LibClass174C90()
{
    unk0e = 1;
}

// TODO: The light's destructor inlines its base's, which text_0046AE20 keeps out of line, so the base destructor is
// only inline in this unit.
/** @brief Destroy the look-at transform. */
inline LibLookAtTransform::~LibLookAtTransform()
{
}

/** @brief Destroy the light and its look-at transform. */
LibLight::~LibLight()
{
}

/**
 * @brief Read a spotlight's position, direction, and the cosine and sine of its cone angle.
 * @param light Spotlight; its transform matrix is updated first if it isn't ready.
 * @param frame Receives the position (w 1), the direction, and the cosine and sine in x and y.
 */
extern "C" void lib_spot_light_get_frame(LibLight* light, LibVector4* frame)
{
    LibVector4 value;

    if (!light->matrix_ready)
    {
        light->update_transform_matrix();
    }

    value.x = light->transform.m[0][3];
    value.y = light->transform.m[1][3];
    value.z = light->transform.m[2][3];
    value.w = 1.0f;
    copy_vector(&frame[0], &value);
    value.x = light->transform.m[0][1];
    value.y = light->transform.m[1][1];
    value.z = light->transform.m[2][1];
    copy_vector(&frame[1], &value);
    lib_compute_sine_cosine_pair_degree9(&value, DEGREES_TO_RADIANS * light->cone_angle);
    frame[2].x = value.z;
    frame[2].y = value.w;
}

/**
 * @brief Copy another light's colour, frame, cone and flags.
 * @param source Light to copy.
 */
void LibLight::copy_light_state(const LibLight* source)
{
    copy_vector(&color, &source->color);
    copy_vector(&tinted_color, &source->tinted_color);
    copy_vector(&position, &source->position);
    copy_vector(&direction, &source->direction);
    cone_angle = source->cone_angle;
    packed_intensity = source->packed_intensity;
    unk268 = source->unk268;
    unk26c = source->unk26c;
    unk270 = source->unk270;
    unk274 = source->unk274;
    unk278 = source->unk278;
    unk27c = source->unk27c;
    unk280 = source->unk280;
    unk284 = source->unk284;
    unk288 = source->unk288;
    unk289 = source->unk289;
    unk28a = source->unk28a;
    unk28b = source->unk28b;
    unk28c = source->unk28c;
    unk28d = source->unk28d;
    unk28e = source->unk28e;
    enabled = source->enabled;
    unk290 = source->unk290;
    unk291 = source->unk291;
    kind = source->kind;
    mask = source->mask;
}

/**
 * @brief Cache the spotlight's cone falloff terms from the cosines of its two half-angles.
 * @param light Spotlight to update.
 */
extern "C" void func_004C9BA0(LibLight* light)
{
    float outer = lib_cosine_degree9((DEGREES_TO_RADIANS / 2) * light->cone_angle);
    float inner = lib_cosine_degree9((DEGREES_TO_RADIANS / 2) * light->unk278);
    outer *= outer;
    inner *= inner;
    float range = outer - inner;
    light->unk26c = inner;
    light->unk270 = 1.0f / range;
}

/** @brief Update the transform matrix if it isn't ready, then cache the position and direction from it. */
void LibLight::update_frame()
{
    if (!matrix_ready)
    {
        update_transform_matrix();
    }

    position.x = transform.m[0][3];
    position.y = transform.m[1][3];
    position.z = transform.m[2][3];
    position.w = 1.0f;
    direction.x = transform.m[0][1];
    direction.y = transform.m[1][1];
    direction.z = transform.m[2][1];
    direction.w = 1.0f;
}

/** @brief Face the look-at target, if any, by turning the light's orientation towards it, then update the matrix. */
void LibLight::update_transform_matrix()
{
    transform_dirty = 1;

    if (look_at_target)
    {
        if (!look_at_target->matrix_ready)
        {
            look_at_target->update_transform_matrix();
        }

        LibTransform::update_transform_matrix();
        matrix_ready = 0;

        LibVector4 target;
        LibVector4 angles;
        LibVector4 orientation;
        const LibTransform* target_transform = look_at_target;
        target.x = target_transform->transform.m[0][3];
        target.y = target_transform->transform.m[1][3];
        target.z = target_transform->transform.m[2][3];
        target.w = 1.0f;
        angles.x = transform.m[0][3];
        angles.y = transform.m[1][3];
        angles.z = transform.m[2][3];
        angles.w = 1.0f;
        lib_direction_angles_xy(&angles, &target, roll_angle);
        func_004CDBC0(&orientation, &angles);
        copy_orientation(&orientation);
    }

    LibTransform::update_transform_matrix();
}

/**
 * @brief Return how strongly a spotlight lights a point: zero behind it, rising to one inside its inner cone.
 * @param light Spotlight.
 * @param point Point to light.
 * @return Falloff from zero to one.
 */
extern "C" float func_004C9D80(LibLight* light, const LibVector4* point)
{
    LibVector4 offset;
    LibVector4 axis;
    offset.x = point->x - light->position.x;
    offset.y = point->y - light->position.y;
    offset.z = point->z - light->position.z;
    vu0_load_vf20(&offset);
    axis.x = light->direction.x;
    vu0_light_start_normalize_vf20();
    axis.y = light->direction.y;
    axis.z = light->direction.z;
    vu0_light_store_normalized_vf20(&offset);
    float cosine = offset.x * axis.x + offset.y * axis.y + offset.z * axis.z;

    if (cosine <= 0.0f)
    {
        return 0.0f;
    }

    float value = light->unk270 * (cosine * cosine - light->unk26c);
    value = ee_max(value, 0.0f);
    value = ee_min(value, 1.0f);
    return value;
}

/**
 * @brief Return one row of a light's transform.
 * @param light Light.
 * @param axis Row index.
 * @return The row's four values.
 */
static inline const float* light_row(const LibLight* light, s32 axis)
{
    return light->transform.m[axis];
}

/**
 * @brief Read one coordinate of a light's position.
 * @param light Light.
 * @param axis Axis index.
 * @return The translation along the axis.
 */
static inline float light_translation(const LibLight* light, s32 axis)
{
    return light_row(light, axis)[3];
}

/**
 * @brief Return the direction a light shines on a point: from the light's position for point and spot kinds when
 *        it has one, otherwise its own direction.
 * @param light Light.
 * @param out Receives the unit direction.
 * @param point Point being lit.
 */
extern "C" void func_004C9E80(LibLight* light, LibVector4* out, const LibVector4* point)
{
    if ((light->kind & 3) && light->unk288)
    {
        out->x = point->x - light_translation(light, 0);
        out->y = point->y - light_translation(light, 1);
        out->z = point->z - light_translation(light, 2);
        lib_normalize_vector3(&out->x);
    }
    else
    {
        copy_vector(out, &light->direction);
    }
}

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

#define LIB_FLOAT_BITS_ONE 0x3F800000
#define LIB_FLOAT_BITS_MINUS_ONE 0xBF800000

/**
 * @brief Compute three sines on VU0 and store them.
 * @param output Receives the sines of x, y and z.
 * @param x First angle in radians.
 * @param y Second angle in radians.
 * @param z Third angle in radians.
 */
void func_004CA090(FieldVec4A* output, float x, float y, float z)
{
    // TODO: Same shape as func_004CD2C0 (signs as float bit patterns, `!!` odd tests).
    union
    {
        float angles[4];
        u32 signs[4];
    } values __attribute__((aligned(16)));
    s32 count_words[4] __attribute__((aligned(16)));

    values.angles[0] = x;
    values.angles[1] = y;
    values.angles[2] = z;
    vu0_sines_load(&values);
    u32 negative = LIB_FLOAT_BITS_MINUS_ONE;
    vu0_sines_reduce();
    s32* counts = count_words;
    vu0_sines_store_counts(counts);
    u32 positive = LIB_FLOAT_BITS_ONE;
    vu0_sines_evaluate();

    bool odd_x = !!(counts[0] & 1);
    bool odd_y = !!(counts[1] & 1);
    bool odd_z = !!(counts[2] & 1);

    values.signs[0] = odd_x ? negative : positive;
    values.signs[1] = odd_y ? negative : positive;
    values.signs[2] = odd_z ? negative : positive;
    vu0_sines_apply_signs(&values);
    vu0_sines_store(output);
}

/**
 * @brief Find the squared distance from a point to a segment and the fraction along it of the closest point.
 * @param segment Aligned segment: start, then axis.
 * @param point Aligned point.
 * @param fraction Receives the fraction along the axis, clamped to [0, 1].
 * @return The squared distance.
 */
extern "C" float func_004CA180(const LibVector4* segment, const LibVector4* point, float* fraction)
{
    LibVector4 projection;
    LibVector4 length;

    vu0_segment_project_start(point, segment, segment + 1);
    vu0_segment_store_dot(&projection);

    if (projection.x <= 0.0f)
    {
        projection.x = 0.0f;
        vu0_segment_square_start_offset();
    }
    else
    {
        vu0_segment_start_fraction(&length);

        if (!(projection.x < length.x))
        {
            projection.x = 1.0f;
            vu0_segment_end_offset();
        }
        else
        {
            vu0_segment_inner_offset(&projection);
        }

        vu0_segment_square_offset();
    }

    *fraction = projection.x;
    vu0_segment_store_distance(&projection);
    return projection.x;
}

/**
 * @brief Find the squared distance between two segments and the fractions along them of the closest points.
 * @param first Aligned first segment: start, then axis.
 * @param second Aligned second segment: start, then axis.
 * @param first_fraction Receives the fraction along the first segment.
 * @param second_fraction Receives the fraction along the second segment.
 * @return The squared distance.
 */
extern "C" float func_004CA270(const LibVector4* first, const LibVector4* second, float* first_fraction,
                               float* second_fraction)
{
    LibVector4 offset;

    float a00;
    float a01;
    float a11;
    float b0;
    float det;
    float b1;
    float s;
    float t;
    float c;
    float distance;
    float temp;

    const LibVector4* first_axis = first + 1;
    const LibVector4* second_axis = second + 1;
    vu0_segment_pair_dots(first, second, first_axis, second_axis);
    vu0_segment_pair_store_offset(&offset);
    a00 = vu0_read_vf12_x();
    a01 = vu0_read_vf14_x();
    a11 = vu0_read_vf16_x();
    vu0_segment_pair_offset_second();
    b0 = vu0_read_vf18_x();
    c = vu0_read_vf20_x();
    det = vu0_read_vf21_x();

    if (!(det < 0.00001f))
    {
        vu0_segment_pair_solve();
        b1 = vu0_read_vf23_x();
        t = vu0_read_vf25_x();
        s = vu0_read_vf24_x();

        if (!(s < 0.0f))
        {
            if (s <= det)
            {
                if (!(t < 0.0f))
                {
                    if (t <= det)
                    {
                        float inverse = 1.0f / det;
                        s *= inverse;
                        t *= inverse;
                        distance = s * (a00 * s + a01 * t + 2.0f * b0) + t * (a01 * s + a11 * t + 2.0f * b1) + c;
                    }
                    else
                    {
                        t = 1.0f;
                        temp = a01 + b0;

                        if (!(temp < 0.0f))
                        {
                            s = 0.0f;
                            distance = a11 + 2.0f * b1 + c;
                        }
                        else if (!(-temp < a00))
                        {
                            s = 1.0f;
                            distance = a00 + a11 + c + 2.0f * (b1 + temp);
                        }
                        else
                        {
                            s = -temp / a00;
                            distance = temp * s + a11 + 2.0f * b1 + c;
                        }
                    }
                }
                else
                {
                    t = 0.0f;

                    if (!(b0 < 0.0f))
                    {
                        s = 0.0f;
                        distance = c;
                    }
                    else if (!(-b0 < a00))
                    {
                        s = 1.0f;
                        distance = a00 + 2.0f * b0 + c;
                    }
                    else
                    {
                        s = -b0 / a00;
                        distance = b0 * s + c;
                    }
                }
            }
            else
            {
                if (!(t < 0.0f))
                {
                    if (t <= det)
                    {
                        s = 1.0f;
                        temp = a01 + b1;

                        if (!(temp < 0.0f))
                        {
                            t = 0.0f;
                            distance = a00 + 2.0f * b0 + c;
                        }
                        else if (!(-temp < a11))
                        {
                            t = 1.0f;
                            distance = a00 + a11 + c + 2.0f * (b0 + temp);
                        }
                        else
                        {
                            t = -temp / a11;
                            distance = temp * t + a00 + 2.0f * b0 + c;
                        }
                    }
                    else
                    {
                        temp = a01 + b0;

                        if (-temp <= a00)
                        {
                            t = 1.0f;

                            if (!(temp < 0.0f))
                            {
                                s = 0.0f;
                                distance = a11 + 2.0f * b1 + c;
                            }
                            else
                            {
                                s = -temp / a00;
                                distance = temp * s + a11 + 2.0f * b1 + c;
                            }
                        }
                        else
                        {
                            s = 1.0f;
                            temp = a01 + b1;

                            if (!(temp < 0.0f))
                            {
                                t = 0.0f;
                                distance = a00 + 2.0f * b0 + c;
                            }
                            else if (!(-temp < a11))
                            {
                                t = 1.0f;
                                distance = a00 + a11 + c + 2.0f * (b0 + temp);
                            }
                            else
                            {
                                t = -temp / a11;
                                distance = temp * t + a00 + 2.0f * b0 + c;
                            }
                        }
                    }
                }
                else
                {
                    if (-b0 < a00)
                    {
                        t = 0.0f;

                        if (!(b0 < 0.0f))
                        {
                            s = 0.0f;
                            distance = c;
                        }
                        else
                        {
                            s = -b0 / a00;
                            distance = b0 * s + c;
                        }
                    }
                    else
                    {
                        s = 1.0f;
                        temp = a01 + b1;

                        if (!(temp < 0.0f))
                        {
                            t = 0.0f;
                            distance = a00 + 2.0f * b0 + c;
                        }
                        else if (!(-temp < a11))
                        {
                            t = 1.0f;
                            distance = a00 + a11 + c + 2.0f * (b0 + temp);
                        }
                        else
                        {
                            t = -temp / a11;
                            distance = temp * t + a00 + 2.0f * b0 + c;
                        }
                    }
                }
            }
        }
        else
        {
            if (!(t < 0.0f))
            {
                if (t <= det)
                {
                    s = 0.0f;

                    if (!(b1 < 0.0f))
                    {
                        t = 0.0f;
                        distance = c;
                    }
                    else if (!(-b1 < a11))
                    {
                        t = 1.0f;
                        distance = a11 + 2.0f * b1 + c;
                    }
                    else
                    {
                        t = -b1 / a11;
                        distance = b1 * t + c;
                    }
                }
                else
                {
                    temp = a01 + b0;

                    if (temp < 0.0f)
                    {
                        t = 1.0f;

                        if (!(-temp < a00))
                        {
                            s = 1.0f;
                            distance = a00 + a11 + c + 2.0f * (b1 + temp);
                        }
                        else
                        {
                            s = -temp / a00;
                            distance = temp * s + a11 + 2.0f * b1 + c;
                        }
                    }
                    else
                    {
                        s = 0.0f;

                        if (!(b1 < 0.0f))
                        {
                            t = 0.0f;
                            distance = c;
                        }
                        else if (!(-b1 < a11))
                        {
                            t = 1.0f;
                            distance = a11 + 2.0f * b1 + c;
                        }
                        else
                        {
                            t = -b1 / a11;
                            distance = b1 * t + c;
                        }
                    }
                }
            }
            else
            {
                if (b0 < 0.0f)
                {
                    t = 0.0f;

                    if (!(-b0 < a00))
                    {
                        s = 1.0f;
                        distance = a00 + 2.0f * b0 + c;
                    }
                    else
                    {
                        s = -b0 / a00;
                        distance = b0 * s + c;
                    }
                }
                else
                {
                    s = 0.0f;

                    if (!(b1 < 0.0f))
                    {
                        t = 0.0f;
                        distance = c;
                    }
                    else if (!(-b1 < a11))
                    {
                        t = 1.0f;
                        distance = a11 + 2.0f * b1 + c;
                    }
                    else
                    {
                        t = -b1 / a11;
                        distance = b1 * t + c;
                    }
                }
            }
        }
    }
    else
    {
        if (!(a01 <= 0.0f))
        {
            if (!(b0 < 0.0f))
            {
                s = 0.0f;
                t = 0.0f;
                distance = c;
            }
            else if (-b0 <= a00)
            {
                s = -b0 / a00;
                t = 0.0f;
                distance = b0 * s + c;
            }
            else
            {
                b1 = -(offset.x * second_axis->x + offset.y * second_axis->y + offset.z * second_axis->z);
                s = 1.0f;
                temp = a00 + b0;

                if (!(-temp < a01))
                {
                    t = 1.0f;
                    distance = a00 + a11 + c + 2.0f * (a01 + b0 + b1);
                }
                else
                {
                    t = -temp / a01;
                    distance = a00 + 2.0f * b0 + c + t * (a11 * t + 2.0f * (a01 + b1));
                }
            }
        }
        else
        {
            if (!(-b0 < a00))
            {
                s = 1.0f;
                t = 0.0f;
                distance = a00 + 2.0f * b0 + c;
            }
            else if (b0 <= 0.0f)
            {
                s = -b0 / a00;
                t = 0.0f;
                distance = b0 * s + c;
            }
            else
            {
                b1 = -(offset.x * second_axis->x + offset.y * second_axis->y + offset.z * second_axis->z);
                s = 0.0f;

                if (!(b0 < -a01))
                {
                    t = 1.0f;
                    distance = a11 + 2.0f * b1 + c;
                }
                else
                {
                    t = -b0 / a01;
                    distance = c + t * (2.0f * b1 + a11 * t);
                }
            }
        }
    }

    *first_fraction = s;
    *second_fraction = t;
    return ee_abs(distance);
}

/**
 * @brief Test an oriented box against a projection volume with separating axes: the volume's depth range and side
 *        planes, the box's own axes, and the cross products of both sets of axes.
 * @param volume Projection volume.
 * @param box Oriented box.
 * @return Zero when an axis separates them, else one.
 */
extern "C" s32 func_004CAB20(const LibProjectionVolume* volume, const LibCullBox* box)
{
    LibVector4 rows[4];
    float low;
    float high;
    float limit;

    vu0_box_cull_step0(box, volume);
    vu0_box_cull_step1(box->axes, &box->half_extents);
    vu0_box_cull_step2(&volume->z_axis);
    vu0_box_cull_step3(rows, &volume->x_axis, &volume->near_half_width);
    limit = volume->near_distance;

    if (rows[0].z + rows[1].x < limit || !((high = rows[0].z - rows[1].x) <= volume->far_distance))
    {
        return 0;
    }

    vu0_box_cull_step4();
    limit = volume->unk54;
    vu0_box_cull_step5(rows);

    if (rows[1].x + rows[0].x < limit || !(rows[1].x <= rows[0].x))
    {
        return 0;
    }

    vu0_box_cull_step6();
    vu0_box_cull_step7(rows);

    if (rows[0].x + rows[1].x < limit || !(rows[1].x <= rows[0].x))
    {
        return 0;
    }

    vu0_box_cull_step8(&volume->y_axis);
    limit = volume->unk58;
    vu0_box_cull_step9(rows);

    if (rows[1].y + rows[0].x < limit || !(rows[1].y <= rows[0].x))
    {
        return 0;
    }

    vu0_box_cull_step10();
    vu0_box_cull_step11(rows);

    if (rows[1].x + rows[0].x < limit || !(rows[1].x <= rows[0].x))
    {
        return 0;
    }

    vu0_box_cull_step12();
    vu0_box_cull_step13(rows);
    low = rows[1].x;
    high = rows[2].x;

    if (low < 0.0f)
    {
        low *= volume->far_near_ratio;
    }

    if (!(high <= 0.0f))
    {
        high *= volume->far_near_ratio;
    }

    if (rows[0].x + rows[3].x < low || !(rows[0].x - rows[3].x <= high))
    {
        return 0;
    }

    low = rows[1].y;
    high = rows[2].y;

    if (low < 0.0f)
    {
        low *= volume->far_near_ratio;
    }

    if (!(high <= 0.0f))
    {
        high *= volume->far_near_ratio;
    }

    if (rows[0].y + rows[3].y < low || !(rows[0].y - rows[3].y <= high))
    {
        return 0;
    }

    low = rows[1].z;
    high = rows[2].z;

    if (low < 0.0f)
    {
        low *= volume->far_near_ratio;
    }

    if (!(high <= 0.0f))
    {
        high *= volume->far_near_ratio;
    }

    if (rows[0].z + rows[3].z < low || !(rows[0].z - rows[3].z <= high))
    {
        return 0;
    }

    vu0_box_cull_step14();
    vu0_box_cull_step15(rows);
    low = rows[1].x;
    high = rows[2].x;
    vu0_box_cull_step16(rows);

    if (low < 0.0f)
    {
        low *= volume->far_near_ratio;
    }

    if (!(high <= 0.0f))
    {
        high *= volume->far_near_ratio;
    }

    if (rows[0].x + rows[3].x < low || !(rows[0].x - rows[3].x <= high))
    {
        return 0;
    }

    low = rows[1].y;
    high = rows[2].y;

    if (low < 0.0f)
    {
        low *= volume->far_near_ratio;
    }

    if (!(high <= 0.0f))
    {
        high *= volume->far_near_ratio;
    }

    if (rows[0].y + rows[3].y < low || !(rows[0].y - rows[3].y <= high))
    {
        return 0;
    }

    low = rows[1].z;
    high = rows[2].z;

    if (low < 0.0f)
    {
        low *= volume->far_near_ratio;
    }

    if (!(high <= 0.0f))
    {
        high *= volume->far_near_ratio;
    }

    if (rows[0].z + rows[3].z < low || !(rows[0].z - rows[3].z <= high))
    {
        return 0;
    }

    vu0_box_cull_step17();
    vu0_box_cull_step18(rows);
    low = rows[0].x;
    high = rows[1].x;
    vu0_box_cull_step19(rows);

    if (low < 0.0f)
    {
        low *= volume->far_near_ratio;
    }

    if (!(high <= 0.0f))
    {
        high *= volume->far_near_ratio;
    }

    if (rows[2].x + rows[3].x < low || !(rows[2].x - rows[3].x <= high))
    {
        return 0;
    }

    low = rows[0].y;
    high = rows[1].y;

    if (low < 0.0f)
    {
        low *= volume->far_near_ratio;
    }

    if (!(high <= 0.0f))
    {
        high *= volume->far_near_ratio;
    }

    if (rows[2].y + rows[3].y < low || !(rows[2].y - rows[3].y <= high))
    {
        return 0;
    }

    low = rows[0].z;
    high = rows[1].z;

    if (low < 0.0f)
    {
        low *= volume->far_near_ratio;
    }

    if (!(high <= 0.0f))
    {
        high *= volume->far_near_ratio;
    }

    if (rows[2].z + rows[3].z < low || !(rows[2].z - rows[3].z <= high))
    {
        return 0;
    }

    vu0_box_cull_step20();
    vu0_box_cull_step21(rows);
    low = rows[0].x;
    high = rows[1].x;
    vu0_box_cull_step22(rows);

    if (low < 0.0f)
    {
        low *= volume->far_near_ratio;
    }

    if (!(high <= 0.0f))
    {
        high *= volume->far_near_ratio;
    }

    if (rows[2].x + rows[3].x < low || !(rows[2].x - rows[3].x <= high))
    {
        return 0;
    }

    low = rows[0].y;
    high = rows[1].y;

    if (low < 0.0f)
    {
        low *= volume->far_near_ratio;
    }

    if (!(high <= 0.0f))
    {
        high *= volume->far_near_ratio;
    }

    if (rows[2].y + rows[3].y < low || !(rows[2].y - rows[3].y <= high))
    {
        return 0;
    }

    low = rows[0].z;
    high = rows[1].z;

    if (low < 0.0f)
    {
        low *= volume->far_near_ratio;
    }

    if (!(high <= 0.0f))
    {
        high *= volume->far_near_ratio;
    }

    if (rows[2].z + rows[3].z < low || !(rows[2].z - rows[3].z <= high))
    {
        return 0;
    }

    vu0_box_cull_step23();
    vu0_box_cull_step24(rows);
    low = rows[0].x;
    high = rows[1].x;
    vu0_box_cull_step25(rows);

    if (low < 0.0f)
    {
        low *= volume->far_near_ratio;
    }

    if (!(high <= 0.0f))
    {
        high *= volume->far_near_ratio;
    }

    if (rows[2].x + rows[3].x < low || !(rows[2].x - rows[3].x <= high))
    {
        return 0;
    }

    low = rows[0].y;
    high = rows[1].y;

    if (low < 0.0f)
    {
        low *= volume->far_near_ratio;
    }

    if (!(high <= 0.0f))
    {
        high *= volume->far_near_ratio;
    }

    if (rows[2].y + rows[3].y < low || !(rows[2].y - rows[3].y <= high))
    {
        return 0;
    }

    low = rows[0].z;
    high = rows[1].z;

    if (low < 0.0f)
    {
        low *= volume->far_near_ratio;
    }

    if (!(high <= 0.0f))
    {
        high *= volume->far_near_ratio;
    }

    if (rows[2].z + rows[3].z < low || !(rows[2].z - rows[3].z <= high))
    {
        return 0;
    }

    vu0_box_cull_step26();
    vu0_box_cull_step27(rows);
    low = rows[0].x;
    high = rows[1].x;
    vu0_box_cull_step28(rows);

    if (low < 0.0f)
    {
        low *= volume->far_near_ratio;
    }

    if (!(high <= 0.0f))
    {
        high *= volume->far_near_ratio;
    }

    if (rows[2].x + rows[3].x < low || !(rows[2].x - rows[3].x <= high))
    {
        return 0;
    }

    low = rows[0].y;
    high = rows[1].y;

    if (low < 0.0f)
    {
        low *= volume->far_near_ratio;
    }

    if (!(high <= 0.0f))
    {
        high *= volume->far_near_ratio;
    }

    if (rows[2].y + rows[3].y < low || !(rows[2].y - rows[3].y <= high))
    {
        return 0;
    }

    low = rows[0].z;
    high = rows[1].z;

    if (low < 0.0f)
    {
        low *= volume->far_near_ratio;
    }

    if (!(high <= 0.0f))
    {
        high *= volume->far_near_ratio;
    }

    if (rows[2].z + rows[3].z < low || !(rows[2].z - rows[3].z <= high))
    {
        return 0;
    }

    vu0_box_cull_step29();
    vu0_box_cull_step30(rows);
    low = rows[0].x;
    high = rows[1].x;
    vu0_box_cull_step31(rows);

    if (low < 0.0f)
    {
        low *= volume->far_near_ratio;
    }

    if (!(high <= 0.0f))
    {
        high *= volume->far_near_ratio;
    }

    if (rows[2].x + rows[3].x < low || !(rows[2].x - rows[3].x <= high))
    {
        return 0;
    }

    low = rows[0].y;
    high = rows[1].y;

    if (low < 0.0f)
    {
        low *= volume->far_near_ratio;
    }

    if (!(high <= 0.0f))
    {
        high *= volume->far_near_ratio;
    }

    if (rows[2].y + rows[3].y < low || !(rows[2].y - rows[3].y <= high))
    {
        return 0;
    }

    low = rows[0].z;
    high = rows[1].z;

    if (low < 0.0f)
    {
        low *= volume->far_near_ratio;
    }

    if (!(high <= 0.0f))
    {
        high *= volume->far_near_ratio;
    }

    if (rows[2].z + rows[3].z < low || !(rows[2].z - rows[3].z <= high))
    {
        return 0;
    }

    return 1;
}

/** @brief Recompute the derived perspective-volume coefficients. */
void LibProjectionVolume::update_coefficients()
{
    far_near_ratio = far_distance / near_distance;
    unk54 = (-2.0f * near_half_width) * far_distance;
    unk58 = (-2.0f * near_half_height) * far_distance;
}

/**
 * @brief Point at one row of a matrix.
 * @param matrix Matrix.
 * @param row Row index.
 * @return The row's four components.
 */
static inline const float* lib_matrix_row(const LibMatrix44Value* matrix, s32 row)
{
    return matrix->m[row];
}

/**
 * @brief Convert a rotation matrix to a quaternion.
 * @param output Receives the quaternion.
 * @param input Rotation matrix.
 */
void lib_matrix_to_quaternion(FieldVec4B* output, const LibMatrix44Value* input)
{
    float* q = &output->x;
    float trace = input->m[0][0] + input->m[1][1] + input->m[2][2] + input->m[3][3];

    if (trace >= 1.0f)
    {
        float s = 2.0f * ee_sqrt(trace);
        q[3] = 0.25f * s;
        s = 1.0f / s;
        q[0] = s * (lib_matrix_row(input, 1)[2] - lib_matrix_row(input, 2)[1]);
        q[1] = s * (lib_matrix_row(input, 2)[0] - lib_matrix_row(input, 0)[2]);
        q[2] = s * (lib_matrix_row(input, 0)[1] - lib_matrix_row(input, 1)[0]);
    }
    else
    {
        s32 i = input->m[0][0] > input->m[1][1] ? 0 : 1;

        if (input->m[2][2] > lib_matrix_row(input, i)[i])
        {
            i = 2;
        }

        s32 j = i + 1;
        s32 k = j + 1;

        if (j > 2)
        {
            j -= 3;
        }

        if (k > 2)
        {
            k -= 3;
        }

        float sum = 1.0f + (lib_matrix_row(input, i)[i] - lib_matrix_row(input, j)[j] - lib_matrix_row(input, k)[k]);
        float s = 2.0f * ee_sqrt(sum);
        q[i] = 0.25f * s;
        s = 1.0f / s;
        q[j] = s * (lib_matrix_row(input, i)[j] + lib_matrix_row(input, j)[i]);
        q[k] = s * (lib_matrix_row(input, i)[k] + lib_matrix_row(input, k)[i]);
        q[3] = s * (lib_matrix_row(input, j)[k] - lib_matrix_row(input, k)[j]);
    }
}

/**
 * @brief Scale three components to unit length.
 * @param value Three components, changed in place.
 */
static inline void normalize_vector3(float* value)
{
    float scale = ee_rsqrt(1.0f, value[0] * value[0] + value[1] * value[1] + value[2] * value[2]);
    value[0] *= scale;
    value[1] *= scale;
    value[2] *= scale;
}

/**
 * @brief Set a matrix to the identity, written out in place.
 * @param matrix Matrix to set.
 */
static inline void set_identity_matrix(LibMatrix44Value* matrix)
{
    ((unsigned __int128*)matrix)[0] = 0;
    ((unsigned __int128*)matrix)[1] = 0;
    ((unsigned __int128*)matrix)[2] = 0;
    ((unsigned __int128*)matrix)[3] = 0;
    matrix->m[0][0] = 1.0f;
    matrix->m[1][1] = 1.0f;
    matrix->m[2][2] = 1.0f;
    matrix->m[3][3] = 1.0f;
}

/**
 * @brief Return a matrix row as a vector.
 * @param matrix Matrix to read.
 * @param row Row index.
 * @return The row.
 */
static inline LibVector4* matrix_row_vector(LibMatrix44Value* matrix, s32 row)
{
    return reinterpret_cast<LibVector4*>(matrix->m[row]);
}

/**
 * @brief Cross product of the x, y and z components with w set to one.
 * @param output Receives first cross second.
 * @param first First vector.
 * @param second Second vector.
 */
static inline void cross_vector3_w1(LibVector4* output, const FieldVec4B* first, const LibVector4* second)
{
    output->x = first->y * second->z - first->z * second->y;
    output->y = first->z * second->x - first->x * second->z;
    output->z = first->x * second->y - first->y * second->x;
    output->w = 1.0f;
}

/**
 * @brief Build a camera-style matrix: the z axis along the direction, the x axis from the direction and a down
 *        vector (or one along z when the direction is nearly vertical), the position as translation; then invert it
 *        and roll it about z.
 * @param output Receives the matrix.
 * @param position Translation.
 * @param direction Direction the z axis points along.
 * @param roll Roll angle.
 */
void lib_matrix_look_at(LibMatrix44Value* output, const FieldVec4B* position, const FieldVec4B* direction, float roll)
{
    LibMatrix44Value basis;
    LibVector4 up;
    LibVector4 pair;
    LibMatrix44Value rotation;

    set_identity_matrix(&basis);
    up.y = -1.0f;
    up.w = 1.0f;
    up.x = 0.0f;
    up.z = 0.0f;
    LibVector4* z_axis = reinterpret_cast<LibVector4*>(basis.m[2]);
    *(unsigned __int128*)z_axis = *(const unsigned __int128*)direction;
    normalize_vector3(&z_axis->x);

    // TODO: Read through a row view; plain basis.m[2][1] folds into the reload below and the abs gets its own register.
    if (!(ee_abs(reinterpret_cast<const LibVector4*>(&basis.m[2][0])->y) <= 0.999f))
    {
        up.y = 0.0f;
        up.z = basis.m[2][1];
    }

    cross_vector3_w1(matrix_row_vector(&basis, 0), direction, &up);
    normalize_vector3(&matrix_row_vector(&basis, 0)->x);
    cross_vector3_w1(matrix_row_vector(&basis, 1), reinterpret_cast<const FieldVec4B*>(matrix_row_vector(&basis, 2)),
                     matrix_row_vector(&basis, 0));
    basis.m[0][3] = position->x;
    basis.m[1][3] = position->y;
    basis.m[2][3] = position->z;
    lib_compute_sine_cosine_pair(roll, &pair);
    set_identity_matrix(&rotation);
    rotation.m[0][0] = pair.z;
    rotation.m[1][1] = pair.z;
    rotation.m[0][1] = pair.w;
    rotation.m[1][0] = -pair.w;
    basis = func_004CF0B0(basis);
    vu0_multiply_matrix(output, &basis, &rotation);
}

extern "C" LibTrigQuotients D_0050CD20;

/**
 * @brief Evaluate the degree-nine VU0 tangent: sine over cosine of one angle.
 * @param angle Angle in radians.
 * @return Approximated tangent.
 */
extern "C" float func_004CC070(float angle)
{
    D_0050CC80.phase.angle = angle;
    vu0_sincos_load_degree9(&D_0050CC80);
    vu0_sincos_reduce(&D_0050CD20);
    bool cosine_negative = bool(D_0050CD20.cosine_half_turns & 1);
    bool sine_negative = bool(D_0050CD20.sine_half_turns & 1);
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
    vu0_sincos_begin_evaluate_degree9(&D_0050CC80);
    vu0_sincos_finish_to_table(&D_0050CC80);
    return D_0050CC80.phase.result / D_0050CC80.sign;
}

/**
 * @brief Compute the VU0 sine and cosine approximations for an angle.
 * @param angle Angle in radians.
 * @param output Aligned vector receiving cosine in z and sine in w; x and y retain shared polynomial coefficients.
 */
extern "C" void lib_compute_sine_cosine_pair(float angle, LibVector4* output)
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

/**
 * @brief Build the plane through three points: the normal is the cross product of the normalized directions from the
 *        origin to the other two points, and the fourth component is minus the normal dotted with the origin.
 * @param plane Receives the normal and the distance term.
 * @param origin Point on the plane the two directions start from.
 * @param first Second point.
 * @param second Third point.
 */
extern "C" void func_004CC7A0(float* plane, const float* origin, const float* first, const float* second)
{
    float u[3];
    float v[3];

    u[0] = first[0] - origin[0];
    u[1] = first[1] - origin[1];
    u[2] = first[2] - origin[2];
    normalize_vector3(u);
    v[0] = second[0] - origin[0];
    v[1] = second[1] - origin[1];
    v[2] = second[2] - origin[2];
    normalize_vector3(v);
    plane[0] = u[1] * v[2] - u[2] * v[1];
    plane[1] = -(u[0] * v[2] - u[2] * v[0]);
    plane[2] = u[0] * v[1] - u[1] * v[0];
    plane[3] = -(plane[0] * origin[0] + plane[1] * origin[1] + plane[2] * origin[2]);
}

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


extern "C" void func_004CCEE0(FieldVec4B* output, const FieldVec4B* from, const FieldVec4B* to, float t);

/**
 * @brief Interpolate a rotation curve segment: slerp the keys and the control rotations, then slerp those two by
 *        2t(1 - t).
 * @param output Receives the rotation.
 * @param from Rotation at the start of the segment.
 * @param to Rotation at the end of the segment.
 * @param from_control Control rotation of the start key.
 * @param to_control Control rotation of the end key.
 * @param t Position in the segment, zero to one.
 */
extern "C" void func_004CCE10(FieldVec4B* output, const FieldVec4B* from, const FieldVec4B* to, const FieldVec4B* from_control, const FieldVec4B* to_control,
                              float t)
{
    FieldVec4B keys;
    FieldVec4B controls;

    func_004CCEE0(&keys, from, to, t);
    float weight = 2.0f * (1.0f - t) * t;
    vu0_quaternion_norm_finish(&keys);
    func_004CCEE0(&controls, from_control, to_control, t);
    vu0_quaternion_norm_finish(&controls);
    func_004CCEE0(output, &keys, &controls, weight);
    vu0_quaternion_norm_finish(output);
}

/**
 * @brief Start a spherical interpolation between two rotations (linear when they're within about 18 degrees of
 *        parallel); the result is left in vf16 with its normalization pending in Q, for vu0_quaternion_norm_finish.
 * @param output Destination the caller stores into; unused here.
 * @param from Rotation at t = 0.
 * @param to Rotation at t = 1.
 * @param t Interpolation position.
 */
extern "C" void func_004CCEE0(FieldVec4B* output, const FieldVec4B* from, const FieldVec4B* to, float t)
{
    float lower_dot = -0.95f;
    float dot = ((from->x * to->x + from->y * to->y) + from->z * to->z) + from->w * to->w;
    float full_weight = 1.0f;
    float upper_dot = 0.95f;

    if (dot > lower_dot && dot < upper_dot)
    {
        float angle = func_004CD010(dot);
        func_004CD2C0(angle * (full_weight - t), angle * t, angle);
        vu0_quaternion_spherical_positive_wait(from, to);
    }
    else
    {
        FieldVec4A weights;
        weights.y = t;
        weights.x = full_weight - t;
        vu0_quaternion_linear_positive(from, to, &weights);
    }

    vu0_quaternion_norm_begin();
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CD010);

/**
 * @brief Start the native three-angle trigonometric approximation, leaving its result in VU0 vf13.
 *
 * The caller must wait for VU0 before consuming the result.
 * @param x First angle in radians.
 * @param y Second angle in radians.
 * @param z Third angle in radians.
 */
void func_004CD2C0(float x, float y, float z)
{
    // TODO: The signs only match as float bit patterns moved through integer registers, and the odd tests only with
    // `!!`, so the original probably built the sign vector some other way.
    union
    {
        float angles[4];
        u32 signs[4];
    } values __attribute__((aligned(16)));
    s32 count_words[4] __attribute__((aligned(16)));

    values.angles[0] = x;
    values.angles[1] = y;
    values.angles[2] = z;
    vu0_sines_load(&values);
    u32 negative = LIB_FLOAT_BITS_MINUS_ONE;
    vu0_sines_reduce();
    s32* counts = count_words;
    vu0_sines_store_counts(counts);
    u32 positive = LIB_FLOAT_BITS_ONE;
    vu0_sines_evaluate();

    bool odd_x = !!(counts[0] & 1);
    bool odd_y = !!(counts[1] & 1);
    bool odd_z = !!(counts[2] & 1);

    values.signs[0] = odd_x ? negative : positive;
    values.signs[1] = odd_y ? negative : positive;
    values.signs[2] = odd_z ? negative : positive;
    vu0_sines_apply_signs(&values);
}

