#include "include_asm.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_0046AE20.h"
#include "overlays/lib/trig_vu0.h"
#include "overlays/lib/vector_vu0.h"
#include "overlays/lib/text_004CD3A0.h"
#include "main/resident_data.h"
#include "main/resident_001001E0.h"
#include "main/resident_00101550.h"

/** Partial state shared by the channel implementations using the word getter. */
struct LibChannelWordState
{
    u8 unk00[0x40];
    u32 channel_word;
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

extern "C" LibTrigTable D_50CC80;
extern "C" LibTrigQuotients D_50CD10;
extern "C" LibTrigQuotients D_50CD00;

/** Packed scalar quotient lane written by VU0 range reduction. */
struct LibScalarTrigQuotient
{
    u32 unk00[3];
    s32 half_turns;
} __attribute__((aligned(16)));
extern "C" LibScalarTrigQuotient D_50CCF0;
extern "C" LibScalarTrigQuotient D_50CCD0;
extern "C" LibScalarTrigQuotient D_50CCE0;
extern "C" LibScalarTrigQuotient D_50CCC0;

extern "C" s32 func_00461860(LibStorageBlock0C* storage, s32 count);

/** @brief View an aligned matrix row as a vector. @param matrix Destination matrix. @param row Row index. @return Writable row vector. */
static inline FieldVec4A& matrix_row_vector(LibMatrix44Value& matrix, s32 row)
{
    return *(FieldVec4A*)matrix.m[row];
}

/** @brief Unlink a container child. @param object Container. @param child Widget to unlink. */
extern "C" void func_004C6120(LibObject178660* object, LibClass178600* child);

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
    LibClass178630* panel;
} LibPanelAssociation;

typedef struct LibPanelAssociationState
{
    u8 pad00[0x60];
    LibPanelAssociation* association;
} LibPanelAssociationState;

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD360);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD370);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD380);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD3C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD3D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD3E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD3F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD420);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD490);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD4A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD4B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD4C0);

/**
 * @brief Read the shared word of a native channel implementation.
 * @param object Channel implementation.
 * @return Stored channel word.
 */
extern "C" u32 lib_channel_read_word(const LibChannelWordState* object)
{
    return object->channel_word;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD4E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD4F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD8A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD8F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD970);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD990);

/**
 * @brief Replace an animation entry's channel and descriptor when its index is below the entry count.
 * @param object Animation object.
 * @param index Entry index; only the upper bound is checked.
 * @param channel Replacement channel.
 * @param kind Entry kind.
 * @param type Entry type.
 * @param flags Entry flags.
 */
extern "C" void lib_animation_set_entry_channel(LibClass178220* object, s32 index, LibClass173180* channel, u8 kind, s16 type, u8 flags)
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
extern "C" LibClass173180* lib_animation_channel_at(LibClass178220* object, s32 index, u8 nibble)
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BDAA0);

/**
 * @brief Bind populated animation entries whose state names match over up to sixteen characters.
 * @param object Animation object.
 * @param target Vector state to bind.
 * @param name State name to match.
 */
extern "C" void lib_animation_bind_state(LibClass178220* object, LibClass178370* target, const char* name)
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
extern "C" void lib_animation_clear_targets(LibClass178220* object)
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
extern "C" void lib_animation_clear_targets_by_kind(LibClass178220* object, u8 kind)
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
extern "C" void lib_animation_clear_matching_target(LibClass178220* object, const void* target)
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
extern "C" void lib_animation_release_channels(LibClass178220* object)
{
    if (object->entries)
    {
        s32 count = object->entry_count;
        for (s32 index = 0; index < count; index++)
        {
            if (object->entries[index].channel)
            {
                object->entries[index].channel->func_0042A820();
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BF100);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BFDB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BFE10);

/**
 * @brief Replace the animation data with a decoded resource buffer.
 * @param object Animation object.
 * @param source Resource header to decode.
 */
extern "C" void lib_animation_load_resource(LibClass178220* object, ResidentResourceHeader* source)
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
    u8* data = func_00102920(D_001B65EC, source, 0, 0);
    if (data)
    {
        func_001025A0(D_001B65EC, source, data, 0);
        object->resource_data = data;
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C0370);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", __ct__14LibClass178220Fv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C0530);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C0CA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C0F50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1440);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1460);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C14D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1560);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1600);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1660);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C16C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C16D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C16E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C16F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1720);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1730);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1780);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1870);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C19E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1AC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1C20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1D30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1E50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1F60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2080);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C21A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C22B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C23C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C24E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2570);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C25D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2620);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2670);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C26A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C26B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C26E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C26F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2720);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2730);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2760);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2770);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C27C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2830);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2890);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2910);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2A10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2AA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2B30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2B70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2BB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2C40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2CD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", __ct__14LibClass178370Fv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2F50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3000);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3060);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C30C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3120);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3240);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3360);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3470);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C34D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3530);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3590);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C39A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C39F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3A50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3AC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3AD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3AE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3AF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3B00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3B70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3C00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3CA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3D00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3D60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3D70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3D80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3D90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3DC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3DD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3E20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3EB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3F10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3F60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3FB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3FE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3FF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4020);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4030);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4060);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4070);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C40A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C40B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4100);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4170);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C41D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4350);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C43E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4470);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C44E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4500);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4510);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4520);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4620);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4780);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_003EF740__14LibClass178600Fv);

/** @brief Unlink the widget from its container before detaching its owner. */
LibClass178600::~LibClass178600()
{
    if (container)
    {
        func_004C6120(container, this);
    }
}

/** @brief Initialize the widget rectangle, container reference, and state bytes. */
LibClass178600::LibClass178600()
{
    unk18.unk0c = 0.0f;
    unk18.unk08 = 0.0f;
    unk18.unk04 = 0.0f;
    unk18.unk00 = 0.0f;
    unk38 = 0;
    container = 0;
    unk28 = 128.0f;
    unk2c[1] = 0;
    unk2c[0] = 0;
    unk34 = 0;
    unk39 = 0;
    unk3a = 0;
    unk3d = 1;
    unk3e = 1;
    unk3f = 1;
    unk3b = 0;
    unk3c = 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4A00);

extern "C" void lib_panel_detach(LibClass178630* object)
{
    LibPanelAssociationState* state = (LibPanelAssociationState*)object;
    if (state->association != 0)
    {
        state->association->panel = 0;
        state->association = 0;
    }
}

/** Panel transform with its callback interface at 0x90. */
class FieldClass15BA90 : public LibClass178A90, public LibClass171FF0
{
public:
    /** @brief Initialize the panel transform and its callback interface. */
    FieldClass15BA90();
    /** @brief Release the association and destroy the transform. */
    virtual ~FieldClass15BA90();
    /** @brief Set the transform translation. @param x Horizontal component. @param y Vertical component. @param z Third component. */
    virtual void func_003EF790(float x, float y, float z);
    void* unk94;
    u8 unk98[4];
    LibClass178630* panel;
    u8 pending;
    u8 unka1[0xF];
};
extern "C" s32 func_002F99F0(FieldClass15BA90*, LibClass178630*);

extern "C" s32 lib_panel_init_transform(LibClass178630* object, float z)
{
    object->unk60 = new (0) FieldClass15BA90;
    if (object->unk60 == 0)
        return 0;
    if (func_002F99F0((FieldClass15BA90*)object->unk60, object) == 0)
        return 0;
    ((FieldClass15BA90*)object->unk60)->func_003EF790(0.0f, 0.0f, z);
    if (object->unk8c != 0)
    {
        ((FieldClass15BA90*)object->unk60)->pending = 1;
        object->unk8c = 0;
    }
    ((LibClass178DD0*)D_001B661C)->func_004D74F0(object->unk60, -1);
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
extern "C" void lib_panel_set_colors(LibClass178630* object, const LibWidgetColors4C5590* colors)
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
extern "C" s32 lib_panel_init_rectangle(LibClass178630* object, s32 mode, float x, float y, float width, float height, float extra)
{
    object->unk18.unk00 = x;
    object->unk18.unk04 = y;
    object->unk18.unk08 = width;
    object->unk18.unk0c = height;
    if (!func_00461860(&object->unk40, 0x44))
    {
        return 0;
    }
    LibPanelDefaults* defaults = ((LibPanelContext*)D_001B657C)->defaults;
    LibPanelInitState* state = (LibPanelInitState*)object;
    state->colors[0] = defaults->colors[0] & 0xFFFFFF;
    state->colors[1] = defaults->colors[1] & 0xFFFFFF;
    state->colors[2] = defaults->colors[2] & 0xFFFFFF;
    state->colors[3] = defaults->colors[3] & 0xFFFFFF;
    object->unk3c = 1;
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C5B60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C6120);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C6150);

typedef struct LibWidgetContainerLink
{
    u8 pad00[0x14];
    LibObject178660* container;
} LibWidgetContainerLink;
extern "C" void func_004CA020(LibObject178660* list, LibClass178600* node);

/**
 * @brief Link the widget into the container and record its owner.
 * @param object Container receiver.
 * @param child Widget to attach.
 */
extern "C" void lib_container_attach_widget(LibObject178660* object, LibClass178600* child)
{
    func_004CA020(object, child);
    ((LibWidgetContainerLink*)child)->container = object;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C61D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C61F0);

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
extern "C" s32 lib_container_init(LibObject178660* object, s32 code, float x, float y, s32 first, float z, s32 second)
{
    if (!func_00461860(&object->unkD0, 12))
    {
        return 0;
    }
    object->LibClass171EC0::func_003EF790(x, y, 0.0f);
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
    LibBounds4C69B0 bounds;
    u8 padf8[0x10];
    u32 source;
    u32 key;
    u8 flag;
    u8 pending;
} LibTextBoundsState;
extern "C" s32 func_004C7D40(LibObject178750* object, u32 source, u32 key, u8 flag);
extern "C" void* func_100B00(u32 size, s32 flags);
extern "C" void func_004C74E0(LibObject178750* object);

/**
 * @brief Refresh the text layout and return its measured bounds.
 * @param object Text widget.
 * @return Stored bounds, or null when resource loading or allocation fails.
 */
extern "C" LibBounds4C69B0* lib_text_measure_bounds(LibObject178750* object)
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

extern "C" void lib_text_set_resource(LibObject178750* object, u32 source, u32 key, u8 flag)
{
    LibTextResourceState* state = (LibTextResourceState*)object;
    state->source = source;
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C7F80);

typedef struct LibTextRectangleState
{
    u8 pad00[0xF8];
    u8 flag;
    u8 padf9[3];
    void* allocation;
    u8 pad100[0x11];
    u8 pending;
} LibTextRectangleState;
extern "C" void func_00464870(LibObject178750* object, float x, float y, float width, float height);
/**
 * @brief Initialize the text rectangle and clear its allocation and pending flag.
 * @param object Text widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 */
extern "C" void lib_text_init_rectangle(LibObject178750* object, float x, float y, float width, float height)
{
    LibTextRectangleState* state = (LibTextRectangleState*)object;
    func_00464870(object, x, y, width, height);
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
extern "C" s32 lib_text_init_resource_rectangle(LibObject178750* object, s32 slot, s32 key, u8 flag, float x, float y, float width, float height)
{
    LibTextRectangleState* state = (LibTextRectangleState*)object;
    state->flag = flag;
    func_00464870(object, x, y, width, height);
    state->allocation = 0;
    state->pending = 0;
    return func_004C7D40(object, slot, key, 0);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8040);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C80E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C81B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8280);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8360);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8370);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8380);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8390);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C83E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8440);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8510);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8530);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8540);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C85D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8680);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8720);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8810);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8860);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8F80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9010);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C94D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C94E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C95A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9650);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9660);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C96D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C96E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C97A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9840);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C98E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9930);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9970);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C99E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9AC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9BA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9C20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9CA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9D80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9E80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9F00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9F60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9FC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9FF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CA020);

/** @brief Initialize an empty intrusive list whose sentinel links point to itself. */
LibClass178A70::LibClass178A70()
{
    node_count = 0;
    unk00.previous = &unk00;
    unk00.next = &unk00;
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CBAC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CBD20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CC070);

/**
 * @brief Compute the VU0 sine and cosine approximations for an angle.
 * @param output Aligned vector receiving cosine in z and sine in w; x and y retain shared polynomial coefficients.
 * @param angle Angle in radians.
 */
extern "C" void lib_compute_sine_cosine_pair(LibVector4* output, float angle)
{
    D_50CC80.phase.angle = angle;
    vu0_sincos_load(&D_50CC80);
    vu0_sincos_reduce(&D_50CD10);
    bool cosine_negative = bool(D_50CD10.cosine_half_turns & 1);
    bool sine_negative = bool(D_50CD10.sine_half_turns & 1);
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
    D_50CC80.sign = cosine_sign;
    float sine_sign;
    if (sine_negative)
    {
        sine_sign = -1.0f;
    }
    else
    {
        sine_sign = 1.0f;
    }
    D_50CC80.phase.sine_sign = sine_sign;
    vu0_sincos_evaluate(&D_50CC80);
    vu0_sincos_store(output);
}

/**
 * @brief Compute degree-nine VU0 sine and cosine approximations.
 * @param output Aligned vector receiving cosine in z and sine in w; x and y retain shared polynomial coefficients.
 * @param angle Angle in radians.
 */
extern "C" void lib_compute_sine_cosine_pair_degree9(LibVector4* output, float angle)
{
    D_50CC80.phase.angle = angle;
    vu0_sincos_load_degree9(&D_50CC80);
    vu0_sincos_reduce(&D_50CD00);
    bool cosine_negative = bool(D_50CD00.cosine_half_turns & 1);
    bool sine_negative = bool(D_50CD00.sine_half_turns & 1);
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
    D_50CC80.sign = cosine_sign;
    float sine_sign;
    if (sine_negative)
    {
        sine_sign = -1.0f;
    }
    else
    {
        sine_sign = 1.0f;
    }
    D_50CC80.phase.sine_sign = sine_sign;
    vu0_sincos_evaluate_degree9(&D_50CC80);
    vu0_sincos_store(output);
}

/**
 * @brief Evaluate the degree-thirteen VU0 cosine approximation.
 * @param angle Angle in radians.
 * @return Approximated cosine.
 */
extern "C" float lib_cosine(float angle)
{
    D_50CC80.phase.angle = angle;
    vu0_cosine_load(&D_50CC80);
    vu0_cosine_reduce(&D_50CCF0);
    bool negative = bool(D_50CCF0.half_turns & 1);
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
    D_50CC80.sign = sign;
    vu0_cosine_begin_evaluate(&D_50CC80);
    vu0_trig_finish_evaluate(&D_50CC80);
    return D_50CC80.phase.result;
}

/**
 * @brief Evaluate the degree-nine VU0 cosine approximation.
 * @param angle Angle in radians.
 * @return Approximated cosine.
 */
extern "C" float lib_cosine_degree9(float angle)
{
    D_50CC80.phase.angle = angle;
    vu0_sincos_load_degree9(&D_50CC80);
    vu0_cosine_reduce(&D_50CCE0);
    bool negative = bool(D_50CCE0.half_turns & 1);
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
    D_50CC80.sign = sign;
    vu0_trig_begin_evaluate_degree9(&D_50CC80);
    vu0_trig_finish_evaluate_degree9(&D_50CC80);
    return D_50CC80.phase.result;
}

/**
 * @brief Evaluate the degree-thirteen VU0 sine approximation.
 * @param angle Angle in radians.
 * @return Approximated sine.
 */
extern "C" float lib_sine(float angle)
{
    D_50CC80.phase.angle = angle;
    vu0_sine_load(&D_50CC80);
    vu0_sine_reduce(&D_50CCD0);
    bool negative = bool(D_50CCD0.half_turns & 1);
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
    D_50CC80.sign = sign;
    vu0_sine_begin_evaluate(&D_50CC80);
    vu0_trig_finish_evaluate(&D_50CC80);
    return D_50CC80.phase.result;
}

/**
 * @brief Evaluate the degree-nine VU0 sine approximation.
 * @param angle Angle in radians.
 * @return Approximated sine.
 */
extern "C" float lib_sine_degree9(float angle)
{
    D_50CC80.phase.angle = angle;
    vu0_sine_load_degree9(&D_50CC80);
    vu0_sine_reduce(&D_50CCC0);
    bool negative = bool(D_50CCC0.half_turns & 1);
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
    D_50CC80.sign = sign;
    vu0_trig_begin_evaluate_degree9(&D_50CC80);
    vu0_trig_finish_evaluate_degree9(&D_50CC80);
    return D_50CC80.phase.result;
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
    return result.components[0];
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
    angles.components[0] = 0.0f;
    angles.components[1] = 0.0f;
    angles.components[2] = 0.0f;
    angles.components[3] = 1.0f;
    lib_direction_angles_xz(&angles, target, z_angle);
    func_004CE4C0(output, angles.components);
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
    func_004CBAC0(output, &converted);
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
