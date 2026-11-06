#include "include_asm.h"
#include "vu0.h"
#include "overlays/lib/blend_transform.h"
#include "overlays/lib/model.h"
#include "main/resident_data.h"
#include "overlays/lib/text_00429B00.h"
#include "overlays/lib/tracks.h"
#include "overlays/lib/emission.h"
#include "overlays/lib/emission_vu0.h"
#include "overlays/lib/light_vu0.h"
#include "overlays/lib/memory_card.h"
#include "overlays/lib/image_capture.h"
#include "overlays/lib/transform_owner_inlines.h"
#include "sdk/main/libkernl_00121940.h"
#include "ee.h"
#include "overlays/lib/text_004DD440.h"
#include "main/resident_0010A0E0.h"

#include "sdk/main/libmc_0012BB10.h"
#include "overlays/lib/text_004CD3A0.h"
#include "main/resident_00101260.h"
#include "sdk/main/libc_guess_00137290.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "sdk/main/libc_guess_0013CD50.h"

/**
 * LibModel of type 0x120 with three owned child objects and its own update list, with vtable D_173380 in main data.
 * What it draws isn't known yet.
 */
class LibClass173380 : public LibModel
{
public:
    /** @brief Construct the model with its default settings. */
    LibClass173380();

    /** @brief Destroy the child objects, then the model. */
    virtual ~LibClass173380()
    {
        for (s32 i = 0; i < 3; i++)
        {
            if (children[i])
            {
                children[i]->destroy();
                children[i] = 0;
            }
        }
    }

    /** @brief Destroy the child objects, then destroy the model through its base. */
    virtual void destroy();

    /** @brief Update the objects in the model's own list, then the model. */
    virtual void update();

    virtual void render();

    /** @brief Use the draw bucket stored at unk83c. */
    virtual void set_default_draw_bucket();

    /**
     * @brief Give no centre for the oriented-box visibility test.
     * @param output Unused.
     * @return Zero.
     */
    virtual s32 get_box_cull_center(void* output);

    /**
     * @brief Return LibModel's bounding sphere with the radius scaled by unk848.
     * @return Bounding sphere (centre in xyz, radius in w).
     */
    virtual const LibVector4* get_bounding_sphere();

    virtual void build_packet(const void* matrix, void* context);

    /** @brief Build LibModel's packets, then this model's own unless it was built from another one. */
    virtual void build_packets();

    /**
     * @brief Extra quadwords to reserve in the draw packet.
     * @return 256.
     */
    virtual s32 get_extra_packet_size();

    /**
     * @brief Slot 0x44 of the second vtable; its purpose is unknown.
     * @return 128.
     */
    virtual s32 func_slot44();

    /**
     * @brief Build this model from another one of the same kind and copy its settings.
     * @param links Display list the model draws through, or null.
     * @param source Model to copy.
     * @return Nonzero on success.
     */
    virtual s32 build_from(LibUpdateList* links, LibClass173380* source);

    /** @brief Finish the packet, or mark the transfer done when unk838 is set. */
    virtual void func_slot4C();

    LibVector4 unk820;

    /** Shared model whose unk790 counts the models built from it. */
    LibModel* unk830;

    u8 unk834;
    u8 unk835;
    u8 unk836;
    u8 unk837;
    u8 unk838;
    u8 unk839;
    u8 unk83a;
    u8 unk83b;
    u8 unk83c;
    u8 unk83d;
    u8 unk83e;

    /** Set once the model was built from another one. */
    u8 built_from_source;

    float unk840;
    float unk844;

    /** Scale applied to LibModel's bounding sphere radius. */
    float unk848;

    float unk84c;
    float unk850;
    float unk854;
    float unk858;
    u32 unk85c;
    u32 unk860[6];

    /** Owned objects, destroyed with the model. */
    LibTransformOwner* children[3];

    LibUpdateList objects;
};

/** LibClass173380 that LibClass173380::build_packet creates, with vtable D_173270 in main data. */
class LibClass173270 : public LibClass173380
{
public:
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
};

/** LibClass1779F0 entry of type 3, with vtable D_1734B0 in main data. */
class LibClass1734B0 : public LibClass1779F0
{
public:
    /** @brief Start unattached, with no data. */
    LibClass1734B0();

    /**
     * @brief Return the entry's type code.
     * @return Three.
     */
    virtual s32 func_slot14();
};

/** 16-byte element of LibClass173490's two arrays; its contents aren't known yet. */
struct LibClass173490Entry
{
    /** @brief Leave the element uninitialized. */
    LibClass173490Entry();

    u32 unk00[4];
};

/** LibClass1734B0 entry of type 34 with two element arrays, with vtable D_173490 in main data. */
class LibClass173490 : public LibClass1734B0
{
public:
    /** @brief Start with no entry arrays. */
    LibClass173490();

    /** @brief Free both entry arrays, then destroy the entry. */
    virtual ~LibClass173490();

    virtual void set_borrowed_data(void* value);
    virtual void func_slot10();

    /**
     * @brief Return the entry's type code.
     * @return 34.
     */
    virtual s32 func_slot14();

    virtual s32 func_slot18();

    /** @brief Slot 0x1C, first after LibClass1779F0's; its purpose is unknown. */
    virtual void func_slot1C();

    u32* unk30;
    u32* unk34;
    u32 unk38;
    u32 unk3c;
    LibClass173490Entry* unk40;
    LibClass173490Entry* unk44;
    u32* unk48;
    u8 unk4c;
    u8 unk4d;
};

/**
 * Light: a LibTransform with a kind byte that the scene's models are lit by, with vtable D_1736C0 in main data.
 * Lib's object factory builds the five kinds below with inline constructors.
 */
class LibClass1736C0 : public LibTransform
{
public:
    /**
     * @brief Slot 0x84: bring the light into a view's space.
     * @param matrix View matrix.
     * @param rotation View matrix with its rows normalised, for directions.
     * @param unk_matrix Third matrix the scene passes; none of the lights here use it.
     */
    virtual void func_slot84(const LibMatrix44Value* matrix, const LibMatrix44Value* rotation, const LibMatrix44Value* unk_matrix) = 0;

    /**
     * @brief Slot 0x88: work out the light reaching a point.
     * @param point Point being lit.
     * @param normal Normal at the point.
     * @return Light vector; stored in the light.
     */
    virtual const LibVector4* func_slot88(const LibVector4* point, const LibVector4* normal) = 0;

    /** Light kind; the factory sets it after the constructor. */
    u8 kind;
};

/** Point light of type 0x703, with vtable D_173750 in main data. */
class LibClass173750 : public LibClass1736C0
{
public:
    /**
     * @brief Transform the light's position into the view's space.
     * @param matrix View matrix.
     * @param rotation Unused.
     * @param unk_matrix Unused.
     */
    virtual void func_slot84(const LibMatrix44Value* matrix, const LibMatrix44Value* rotation, const LibMatrix44Value* unk_matrix);

    /**
     * @brief Work out the vector from a point to the light, falling off with distance.
     * @param point Point being lit.
     * @param normal Unused.
     * @return Light vector at unk220.
     */
    virtual const LibVector4* func_slot88(const LibVector4* point, const LibVector4* normal);

    /** Last result of func_slot88. */
    LibVector4 unk220;

    /** Factors: x scales the result, w is added to the squared distance. */
    LibVector4 unk230;

    /** Position in the view's space. */
    LibVector4 view_position;
};

/** Light of type 0x702 that scales normals, with vtable D_1737E0 in main data. */
class LibClass1737E0 : public LibClass1736C0
{
public:
    /**
     * @brief Do nothing; this light doesn't depend on the view.
     * @param matrix Unused.
     * @param rotation Unused.
     * @param unk_matrix Unused.
     */
    virtual void func_slot84(const LibMatrix44Value* matrix, const LibMatrix44Value* rotation, const LibMatrix44Value* unk_matrix)
    {
    }

    /**
     * @brief Scale a normal by the light's factors.
     * @param point Unused.
     * @param normal Normal at the point.
     * @return Light vector at unk220.
     */
    virtual const LibVector4* func_slot88(const LibVector4* point, const LibVector4* normal);

    /** Last result of func_slot88. */
    LibVector4 unk220;

    /** Factors: the result is normal * w * (|normal| * x + y). */
    LibVector4 unk230;
};

/** Light of type 0x704 with a position, a radius and two directions, with vtable D_173630 in main data. */
class LibClass173630 : public LibClass1736C0
{
public:
    /**
     * @brief Bring the position and both directions into the view's space.
     * @param matrix View matrix.
     * @param rotation View matrix with its rows normalised.
     * @param unk_matrix Unused.
     */
    virtual void func_slot84(const LibMatrix44Value* matrix, const LibMatrix44Value* rotation, const LibMatrix44Value* unk_matrix);

    /**
     * @brief Give a random vector from the view-space directions for points close enough to the light's axis.
     * @param point Point being lit.
     * @param normal Unused.
     * @return Light vector at unk290; zero for points out of reach.
     */
    virtual const LibVector4* func_slot88(const LibVector4* point, const LibVector4* normal);

    /** Position in the view's space; w holds radius squared. */
    LibVector4 view_position;

    /** First direction in the light's own space. */
    LibVector4 unk230;

    /** unk230 in the view's space. */
    LibVector4 unk240;

    /** unk240 normalised: the light's axis. */
    LibVector4 axis;

    /** Second direction in the light's own space. */
    LibVector4 unk260;

    /** unk260 in the view's space. */
    LibVector4 unk270;

    /** Half of unk270. */
    LibVector4 unk280;

    /** Last result of func_slot88. */
    LibVector4 unk290;

    float radius;
};

/** Light of type 0x701 that gives a random vector between two directions, with vtable D_173870 in main data. */
class LibClass173870 : public LibClass1736C0
{
public:
    /**
     * @brief Turn both directions into the view's space and halve the second.
     * @param matrix Unused.
     * @param rotation View matrix with its rows normalised.
     * @param unk_matrix Unused.
     */
    virtual void func_slot84(const LibMatrix44Value* matrix, const LibMatrix44Value* rotation, const LibMatrix44Value* unk_matrix);

    /**
     * @brief Pick a random vector from the view-space directions.
     * @param point Unused.
     * @param normal Unused.
     * @return Light vector at unk270.
     */
    virtual const LibVector4* func_slot88(const LibVector4* point, const LibVector4* normal);

    /** First direction in the light's own space. */
    LibVector4 unk220;

    /** unk220 in the view's space. */
    LibVector4 unk230;

    /** Second direction in the light's own space. */
    LibVector4 unk240;

    /** unk240 in the view's space. */
    LibVector4 unk250;

    /** Half of unk250. */
    LibVector4 unk260;

    /** Last result of func_slot88. */
    LibVector4 unk270;
};

/** Directional light of type 0x700, with vtable D_173900 in main data. */
class LibClass173900 : public LibClass1736C0
{
public:
    /**
     * @brief Turn the direction into the view's space.
     * @param matrix Unused.
     * @param rotation View matrix with its rows normalised.
     * @param unk_matrix Unused.
     */
    virtual void func_slot84(const LibMatrix44Value* matrix, const LibMatrix44Value* rotation, const LibMatrix44Value* unk_matrix);

    /**
     * @brief Give the view-space direction, the same for every point.
     * @param point Unused.
     * @param normal Unused.
     * @return Direction at unk230.
     */
    virtual const LibVector4* func_slot88(const LibVector4* point, const LibVector4* normal)
    {
        return &unk230;
    }

    /** Direction in the light's own space. */
    LibVector4 unk220;

    /** unk220 in the view's space. */
    LibVector4 unk230;
};

/** LibTransform of type 0x1100 with no state of its own, with vtable D_1734D0 in main data. */
class LibClass1734D0 : public LibTransform
{
public:
    /** @brief Construct the transform. */
    LibClass1734D0();
};

/** Seed of the 1664525/1013904223 linear congruential sequence Lib's lights draw from. */
extern "C" u32 D_001B65B8;

/**
 * @brief Advance the light random seed.
 * @return New seed.
 */
static inline u32 lib_light_random()
{
    return D_001B65B8 = 1664525L * D_001B65B8 + 1013904223L;
}

/**
 * @brief Turn the next light random seed into a fraction by using its low 23 bits as a float mantissa.
 * @return Random value from 0 up to 1.
 */
static inline float lib_light_random_fraction()
{
    u32 bits = (lib_light_random() & 0x7FFFFF) | 0x3F800000;
    return *(float*)&bits - 1.0f;
}

/**
 * @brief Report whether the transform's transposed matrix is up to date.
 * @param transform Transform to check.
 * @return Nonzero when transposed_transform is current.
 */
static inline s32 transpose_is_current(const LibTransform* transform)
{
    return transform->unk20e_0;
}

/**
 * @brief Mark the transpose current and rebuild it from the transform.
 * @param transform Transform to update.
 */
static inline void transpose_transform(LibTransform* transform)
{
    transform->unk20e_0 = 1;
    transform->unk20e_1 = 0;
    ee_transpose_matrix(&transform->transposed_transform, &transform->transform);
}

/**
 * @brief Bring the transform's transposed matrix up to date if needed.
 * @param transform Transform to read.
 * @return The transposed matrix.
 */
static inline const LibMatrix44Value* get_transposed_transform(LibTransform* transform)
{
    if (!transpose_is_current(transform))
    {
        transpose_transform(transform);
    }

    return &transform->transposed_transform;
}

/** Sound bank set Lib plays its sounds through. */
extern ResidentClass14FC90* D_001B6524;

/** Sound number tables for func_0042EB50, four numbers each; entries 1 to 10 are used. */
extern s16* D_4ED0EC[];

extern "C" {

void func_004486A0(void* object);

typedef struct WordSetterOwnertext_00429B00
{
    u8 unk00[0x24];
    u32 unk24;
    u8 unk28[0x400];
    u32 unk428;
} WordSetterOwnertext_00429B00;



INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00429B00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00429BF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00429DF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00429F70);

void func_0042A120(void* object)
{
    static_cast<LibQuaternionTrackBase*>(object)->LibQuaternionTrackBase::reset_state();
}

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
s32 LibQuaternionTrackBase::on_append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
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
s32 LibQuaternionTrackBase::on_replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
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

extern "C" {

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042A4E0);

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

extern "C" {

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042A720);

}

/**
 * @brief Ignore the keyframe; the root has no key storage.
 * @param value Keyframe value.
 * @param in_tangent Incoming tangent.
 * @param out_tangent Outgoing tangent.
 * @param key Sort key.
 * @return Zero.
 */
s32 LibClass173180::append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
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
s32 LibClass173180::replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
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
s32 LibQuaternionTrackBase::append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
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
s32 LibQuaternionTrackBase::replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
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
 * @param value Keyframe value.
 * @param first First auxiliary value.
 * @param second Second auxiliary value.
 * @param key Sort key.
 */
void LibQuaternionTrackBase::on_set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
}

/**
 * @brief Store a single keyframe through on_set_single_key.
 * @param value Keyframe value.
 * @param in_tangent First auxiliary value.
 * @param out_tangent Second auxiliary value.
 * @param key Sort key.
 */
void LibQuaternionTrackBase::set_single_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    on_set_single_key(static_cast<const FieldVec4A*>(value), static_cast<const FieldVec4A*>(in_tangent), static_cast<const FieldVec4A*>(out_tangent), key);
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

extern "C" void func_0042B000(LibClass173380* model);

/** @brief Build LibModel's packets, then this model's own unless it was built from another one. */
void LibClass173380::build_packets()
{
    LibModel::build_packets();

    if (!built_from_source)
    {
        func_0042B000(this);
    }
}

extern "C" {

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042AEC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042B000);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042B110);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042C450);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042C5C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042CC80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042D0B0);

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
    unk860[2] = 0;
    unk860[3] = 0;
    unk860[4] = 0;
    unk860[5] = 0;
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

/** @brief Upload the palette image at D_4EC600. */
void lib_upload_default_palette(void)
{
    func_004D8C20(D_4EC600, 30);
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042D9B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042DCE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042DFF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042E240);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042E6E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042E710);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042E860);

/**
 * @brief Return the input pointer unchanged.
 * @param object Pointer to return.
 * @return The input pointer.
 */
void* func_0042E9A0(void* object) {
    return object;
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

extern "C" {

/**
 * @brief Store a word at offset 0x14 and mark the state active at 0x0C.
 * @param state State to update.
 * @param value Word to store.
 */
void func_0042EB30(LibTextValueState* state, u32 value) {
    state->unk14 = value;
    state->unk0C = 1;
}

s32 func_0042EB40(void* object)
{
    return 0;
}

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

    numbers = D_4ED0EC[table];
    return func_0011F9E0(D_001B6524, numbers[resident_random_below(4)], emitter, 0, 0x7F, 0);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042EBE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042EF30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042F0D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042F160);

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

    return func_0011FA80(D_001B6524, buffer, emitter, 0, 0x7F, 0, owns_buffer);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042F250);

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

    return func_0011FA80(D_001B6524, buffer, emitter, 0, 0x7F, 0, owns_buffer);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042F420);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042F550);

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

    return func_0011FB40(D_001B6524, slot, 9, emitter, 0, 0x7F, 0);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00430B00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00430CA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00430E00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00431020);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00431090);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004317F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00431AB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", update__13LibMemoryCardFv);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004329C0);

/** @brief Mark the packet being stored as done and finish the capture. */
void LibImageCapture::on_store_complete()
{
    stored[storing] = 1;
    lib_finish_packet(this);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00432A80);

/**
 * @brief Let the store thread know the store packet's transfer is over.
 * @param channel DMA channel number.
 */
void LibImageCapture::complete_dma(u32 channel)
{
    func_001140F0(g_vif1_dma_queue);
    iSignalSema(D_005081D0.semaphore);
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

    if (!func_00114DD0(&D_005081D0))
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
    func_00114100(g_vif1_dma_queue, capture);
}

/** @brief Queue the capture's DMA, or hand it to the packet queue when unk65 is set. */
void LibImageCapture::render()
{
    if (!unk65)
    {
        func_00114100(g_vif1_dma_queue, this);
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004336E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00433730);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00433790);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00433880);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004339F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00433AA0);

void* func_00433BE0(u32 alignment, u32 size) { return memalign(alignment, size); }

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", __dt__14LibClass173630Fv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00433C70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00433EF0);

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
 * @param unk_matrix Unused.
 */
void LibClass173750::func_slot84(const LibMatrix44Value* matrix, const LibMatrix44Value* rotation, const LibMatrix44Value* unk_matrix)
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00434330);

}

/**
 * @brief Turn both directions into the view's space and halve the second.
 * @param matrix Unused.
 * @param rotation View matrix with its rows normalised.
 * @param unk_matrix Unused.
 */
void LibClass173870::func_slot84(const LibMatrix44Value* matrix, const LibMatrix44Value* rotation, const LibMatrix44Value* unk_matrix)
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
 * @param unk_matrix Unused.
 */
void LibClass173900::func_slot84(const LibMatrix44Value* matrix, const LibMatrix44Value* rotation, const LibMatrix44Value* unk_matrix)
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004348E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004349D0);

s32 func_00434F20(void* object)
{
    return 6;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00434F30);

void func_00434FA0(void* object)
{
    func_004486A0((u8*)object + 0x5A4);
    ((LibColorModel*)object)->LibColorModel::destroy();
}

// TODO: These six look like the operator new and operator delete of classes used all over Lib, but I haven't
// found which classes yet, so they stay plain functions for now.
/**
 * @brief Free memory through the heap at D_001B6684 when one is set, otherwise through operator delete.
 * @param memory Allocation, or null.
 */
void func_00434FD0(void* memory)
{
    if (D_001B6684)
    {
        if (memory)
        {
            resident_heap_release(memory);
        }
    }
    else
    {
        ::operator delete(memory);
    }
}

/**
 * @brief Free memory through the heap at D_001B6684 when one is set, otherwise through operator delete.
 * @param memory Allocation, or null.
 */
void func_00435020(void* memory)
{
    if (D_001B6684)
    {
        if (memory)
        {
            resident_heap_release(memory);
        }
    }
    else
    {
        ::operator delete(memory);
    }
}

/**
 * @brief Free memory through the heap at D_001B6684 when one is set, otherwise through operator delete.
 * @param memory Allocation, or null.
 */
void func_00435070(void* memory)
{
    if (D_001B6684)
    {
        if (memory)
        {
            resident_heap_release(memory);
        }
    }
    else
    {
        ::operator delete(memory);
    }
}

/**
 * @brief Free memory through the heap at D_001B6684 when one is set, otherwise through operator delete.
 * @param memory Allocation, or null.
 */
void func_004350C0(void* memory)
{
    if (D_001B6684)
    {
        if (memory)
        {
            resident_heap_release(memory);
        }
    }
    else
    {
        ::operator delete(memory);
    }
}

/**
 * @brief Allocate from the heap at D_001B6684 when one is set, otherwise through operator new.
 * @param size Size in bytes.
 * @param heap Heap selector passed on to operator new.
 * @return The allocation.
 */
void* func_00435110(u32 size, s32 heap)
{
    if (D_001B6684)
    {
        return resident_heap_allocate(D_001B6684, size);
    }

    return ::operator new(size, heap);
}

/**
 * @brief Allocate from the heap at D_001B6684 when one is set, otherwise through operator new.
 * @param size Size in bytes.
 * @param heap Heap selector passed on to operator new.
 * @return The allocation.
 */
void* func_00435150(u32 size, s32 heap)
{
    if (D_001B6684)
    {
        return resident_heap_allocate(D_001B6684, size);
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
void func_00435270(LibClass173990* emitter, u32 first_flag, u32 second_flag, u8 value, float factor)
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004352E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00435840);

}
