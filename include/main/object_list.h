#ifndef SO3_MAIN_OBJECT_LIST_H
#define SO3_MAIN_OBJECT_LIST_H

#include "types.h"
#include "gs.h"
#include "ee.h"
#include "sdk/main/libkernl_00121940.h"
#include "main/object.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Store a byte at offset 0x2C4 and a word at offset 0x2B8. */
void resident_image_object_set_unk2b8(void* object, u8 flag, u32 value);

/** Store a byte at offset 0x2C3 and a word at offset 0x2B4. */
void resident_image_object_set_unk2b4(void* object, u8 flag, u32 value);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/** Four float components, aligned for 128-bit copies. */
typedef struct ResidentVector4
{
    /**
     * @brief Copy all four components at once.
     * @param other Vector to copy.
     * @return This vector.
     */
    ResidentVector4& operator=(const ResidentVector4& other)
    {
        *(unsigned __int128*)this = *(const unsigned __int128*)&other;
        return *this;
    }

    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16))) ResidentVector4;

/** Four aligned rows of a 4x4 matrix, copied a row at a time. */
class ResidentMatrix
{
public:
    /**
     * @brief Copy all four rows.
     * @param other Matrix to copy.
     * @return This matrix.
     */
    ResidentMatrix& operator=(const ResidentMatrix& other)
    {
        ((unsigned __int128*)rows)[0] = ((const unsigned __int128*)other.rows)[0];
        ((unsigned __int128*)rows)[1] = ((const unsigned __int128*)other.rows)[1];
        ((unsigned __int128*)rows)[2] = ((const unsigned __int128*)other.rows)[2];
        ((unsigned __int128*)rows)[3] = ((const unsigned __int128*)other.rows)[3];
        return *this;
    }

    ResidentVector4 rows[4];
};

/** Second base of ResidentImageObject (vtable D_0014FD10), the part registered with the list at g_image_registry. */
class ResidentImageSource
{
public:
    u8 unk00;
    u8 unk01;

    /** @brief Clear the state bytes. */
    ResidentImageSource()
    {
        unk00 = 0;
        unk01 = 0;
    }

    virtual ~ResidentImageSource()
    {
    }

    /**
     * @brief Get the registered data.
     * @return The data, or null.
     */
    virtual void* get_record() = 0;

    virtual s32 get_record_kind() = 0;

    /**
     * @brief Return zero.
     * @return Zero.
     */
    virtual s32 get_default_kind();
};

/**
 * Primary base of ResidentImageObject: the Lib transform that func_4DAD90 constructs and func_4DAC70 destroys. Its slots
 * follow the resident list object's, and Lib implements the ones the resident objects call.
 */
class ResidentImageObjectBase : public ResidentListObject
{
public:
    /** @brief Construct an identity transform. */
    ResidentImageObjectBase();

    /** @brief Destroy the transform. */
    virtual ~ResidentImageObjectBase();

    /** @brief Detach the object and queue it for release. */
    virtual void destroy();

    /** @brief Update the transform relative to its parent. */
    virtual void update();

    /**
     * @brief Set the position and a w component of one.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     */
    virtual void set_translation(float x, float y, float z);

    /**
     * @brief Copy the position.
     * @param value Source vector.
     */
    virtual void set_translation_vector(const ResidentVector4* value);

    /**
     * @brief Copy the position.
     * @param value Source vector.
     */
    virtual void copy_translation(const ResidentVector4* value);

    /**
     * @brief Convert three rotation components into the orientation.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     */
    virtual void set_rotation(float x, float y, float z);

    /**
     * @brief Convert a rotation into the orientation.
     * @param value Source rotation.
     */
    virtual void set_rotation_vector(const ResidentVector4* value);

    /**
     * @brief Convert a rotation into the orientation.
     * @param value Source rotation.
     */
    virtual void convert_rotation(const ResidentVector4* value);

    /**
     * @brief Copy the orientation quaternion.
     * @param value Source quaternion.
     */
    virtual void set_orientation(const ResidentVector4* value);

    /**
     * @brief Copy the orientation quaternion.
     * @param value Source quaternion.
     */
    virtual void copy_orientation(const ResidentVector4* value);

    /**
     * @brief Set all four orientation components.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     * @param w Fourth component.
     */
    virtual void set_orientation_components(float x, float y, float z, float w);

    /**
     * @brief Set the scale's xyz components.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     */
    virtual void set_scale(float x, float y, float z);

    /**
     * @brief Copy the scale.
     * @param value Source vector.
     */
    virtual void set_scale_vector(const ResidentVector4* value);

    /**
     * @brief Copy the scale.
     * @param value Source vector.
     */
    virtual void copy_scale(const ResidentVector4* value);

    /** @brief Draw in the main list (bucket zero). */
    virtual void set_default_draw_bucket();

    /**
     * @brief Give the centre for Lib's oriented-box visibility test.
     * @param output Receives the centre in local space.
     * @return Nonzero when a centre was written.
     */
    virtual s32 get_box_cull_center(void* output);

    /**
     * @brief Fade the object as it nears the camera.
     * @param value Distance in front of the camera over the fade range, clamped to one.
     * @param mode Mode from Lib's caller.
     * @return Whether the value is negative.
     */
    virtual bool set_fade_alpha(float value, float mode);

    /**
     * @brief Return the bounding sphere Lib culls against (centre in xyz, radius in w).
     * @return Bounding sphere.
     */
    virtual const ResidentVector4* get_bounding_sphere();

    /**
     * @brief Build the object's draw packet.
     * @param matrix Matrix supplied by the caller.
     * @param context Opaque caller context.
     */
    virtual void build_packet(const void* matrix, void* context);

    /** @brief Rebuild the transformation matrices from the position, orientation and scale. */
    virtual void update_transform_matrix();

    /**
     * @brief Read the stored transformation matrix.
     * @return Matrix pointer.
     */
    virtual const ResidentMatrix* get_transform_matrix();

    /**
     * @brief Copy the source's transformation state.
     * @param source Transform source.
     */
    virtual void copy_transform_state(const ResidentImageObjectBase* source);

    /**
     * @brief Make a copy of this object that stays linked to it.
     * @return The copy, or null.
     */
    virtual ResidentImageObjectBase* clone();

    /** @brief Unlink a copy from its original and queue it for release. */
    virtual void release_clone();

    /**
     * @brief Read the additional local translation.
     * @return Stored translation.
     */
    virtual const ResidentVector4* get_offset_translation() const;

    /**
     * @brief Read the additional local rotation.
     * @return Stored quaternion.
     */
    virtual const ResidentVector4* get_offset_rotation() const;

    /**
     * @brief Read the additional local scale.
     * @return Stored scale.
     */
    virtual const ResidentVector4* get_offset_scale() const;

    /**
     * @brief Copy another transform's state and its offset vectors.
     * @param source Transform source.
     */
    virtual void copy_offset_transform_state(const ResidentImageObjectBase* source);

    u8 unk14[0xC];
    ResidentVector4 translation;
    ResidentVector4 orientation;
    ResidentVector4 scale;
    u8 transform_dirty;
    u8 unk51;
    u8 unk52[0xE];
    u8 draw_bucket;
    u8 matrix_ready;
    u8 unk62[0xA];
    u16 unk6c;
    u8 unk6e[0x22];
    ResidentMatrix transform;
    ResidentMatrix base_transform;
    ResidentMatrix offset_transform;
    ResidentMatrix transposed_transform;
    ResidentMatrix inverse_transform;
    ResidentVector4 offset_translation;
    ResidentVector4 offset_rotation;
    ResidentVector4 offset_scale;
    float unk200;
    u8 unk204[4];
    ResidentImageObjectBase* parent_transform;
    u16 unk20c;
    u8 unk20e_0 : 1;
    u8 unk20e_1 : 1;
    u8 unk20e_2 : 1;
    u8 unk20f;
};

/** Transform followed by a box's half extents, which hit tests check points against in the transform's space. */
class ResidentHitBox : public ResidentImageObjectBase
{
public:
    ResidentVector4 half_extents;
};

/** Resource record as Lib's render data loaders keep it; data can hold an offset or a resolved pointer. */
typedef struct ResidentRenderDataRecord
{
    u32 next_offset;
    s16 storage_kind;
    s16 index;
    u32 key08;
    u32 key0c;
    u64 unk10[2];
    u32 resolved_data;
    u8 unk24[4];
    u8* data;
    u32 unk2c;
} ResidentRenderDataRecord;

/** Lib's image-sequence channel (0x60 bytes) that animates a bound FIS record. */
class ResidentImageSequenceChannel
{
public:
    ResidentImageSequenceChannel();

    virtual ~ResidentImageSequenceChannel();

    u8 unk04[0x38];
    u32 unk3c;
    u8 unk40[8];
    s32 unk48;
    u8 unk4c[0x14];
};

/** Image header whose texture size is stored as powers of two. */
typedef struct ResidentImageHeader
{
    u8 unk00[0xE];
    u8 width_log2;
    u8 height_log2;
    u8 unk10[0x58];
} ResidentImageHeader;

/** Partial display manager at g_renderer, holding the shared image headers. */
typedef struct ResidentDisplayManager
{
    u8 unk0000[0xB3C8];
    ResidentImageHeader images[1];
} ResidentDisplayManager;

/**
 * Resident transform object (vtable D_0014FD30) that draws an image from its render data record. It registers its
 * second base with the list at g_image_registry, and can follow another transform's position and a camera's orientation.
 */
class ResidentImageObject : public ResidentImageObjectBase, public ResidentImageSource
{
public:
    /** @brief Construct an unregistered object with no channel and the image centred. */
    ResidentImageObject();

    /** @brief Unregister the object and destroy its image channel. */
    virtual ~ResidentImageObject();

    /** @brief Unregister the object if it is registered, then detach it and queue it for release. */
    virtual void destroy();

    /** @brief Do nothing. */
    virtual void render();

    /**
     * @brief Set the position and a w component of one.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     */
    virtual void set_translation(float x, float y, float z);

    /**
     * @brief Copy the position.
     * @param value Source vector.
     */
    virtual void set_translation_vector(const ResidentVector4* value);

    /**
     * @brief Copy the position.
     * @param value Source vector.
     */
    virtual void copy_translation(const ResidentVector4* value);

    /**
     * @brief Convert three rotation components into the orientation.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     */
    virtual void set_rotation(float x, float y, float z);

    /**
     * @brief Convert a rotation into the orientation.
     * @param value Source rotation.
     */
    virtual void set_rotation_vector(const ResidentVector4* value);

    /**
     * @brief Convert a rotation into the orientation.
     * @param value Source rotation.
     */
    virtual void convert_rotation(const ResidentVector4* value);

    /**
     * @brief Copy the orientation quaternion.
     * @param value Source quaternion.
     */
    virtual void set_orientation(const ResidentVector4* value);

    /**
     * @brief Copy the orientation quaternion.
     * @param value Source quaternion.
     */
    virtual void copy_orientation(const ResidentVector4* value);

    /**
     * @brief Set all four orientation components.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     * @param w Fourth component.
     */
    virtual void set_orientation_components(float x, float y, float z, float w);

    /**
     * @brief Set the scale's xyz components.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     */
    virtual void set_scale(float x, float y, float z);

    /**
     * @brief Copy the scale.
     * @param value Source vector.
     */
    virtual void set_scale_vector(const ResidentVector4* value);

    /**
     * @brief Copy the scale.
     * @param value Source vector.
     */
    virtual void copy_scale(const ResidentVector4* value);

    /** @brief Draw in the main list (bucket zero). */
    virtual void set_default_draw_bucket();

    /**
     * @brief Give no centre for Lib's oriented-box visibility test.
     * @param output Unused.
     * @return Zero, so the test is skipped.
     */
    virtual s32 get_box_cull_center(void* output);

    /**
     * @brief Don't fade near the camera.
     * @param value Distance in front of the camera over the fade range.
     * @param mode Unused.
     * @return Whether the value is negative.
     */
    virtual bool set_fade_alpha(float value, float mode);

    /**
     * @brief Return Lib's shared default bounding sphere.
     * @return Bounding sphere.
     */
    virtual const ResidentVector4* get_bounding_sphere();

    /**
     * @brief Do nothing.
     * @param matrix Unused.
     * @param context Unused.
     */
    virtual void build_packet(const void* matrix, void* context);

    /**
     * @brief Read the stored transformation matrix.
     * @return Matrix pointer.
     */
    virtual const ResidentMatrix* get_transform_matrix();

    /**
     * @brief Don't copy this object.
     * @return Null.
     */
    virtual ResidentImageObjectBase* clone();

    /** @brief Do nothing; this object has no copies. */
    virtual void release_clone();

    /**
     * @brief Read the additional local translation.
     * @return Stored translation.
     */
    virtual const ResidentVector4* get_offset_translation() const;

    /**
     * @brief Read the additional local rotation.
     * @return Stored quaternion.
     */
    virtual const ResidentVector4* get_offset_rotation() const;

    /**
     * @brief Read the additional local scale.
     * @return Stored scale.
     */
    virtual const ResidentVector4* get_offset_scale() const;

    /**
     * @brief Copy another object's settings, record and transform state, and rebuild the image channel when it has one.
     * @param source Object to copy.
     */
    virtual void copy_state(const ResidentImageObject* source);

    /**
     * @brief Get the record while the object is registered.
     * @return The record, or null.
     */
    virtual void* get_record();

    /**
     * @brief Return zero.
     * @return Zero.
     */
    virtual s32 get_record_kind();

    float unk218;
    float unk21c;
    float unk220;
    float unk224;
    float elapsed;
    u32 hit_mask;
    ResidentHitBox* hit_volume;
    u8 unk234[4];
    ResidentRenderDataRecord record;
    u8 unk268[8];
    ResidentMatrix unk270;
    ResidentImageSequenceChannel* channel;
    ResidentImageObjectBase* position_source;
    ResidentImageObjectBase* camera;
    u8 faces_target;
    u8 unk2bd;
    u8 unk2be;
    u8 animated;
    u8 registered;
    u8 unk2c1;
    u8 shared_image;
    u8 follow_position;
    u8 follow_camera;
    u8 unk2c5;
    u8 unk2c6;
    u8 unk2c7;
};

/** Lib's object list: a sentinel node and count before the list's own vptr; Lib implements every slot. */
class ResidentObjectList
{
public:
    ResidentListSentinel sentinel;
    u32 node_count;

    virtual ~ResidentObjectList();

    /**
     * @brief Append a node to the end of the list.
     * @param node Node to append.
     */
    virtual void append(void* node);

    /**
     * @brief Prepend a node to the beginning of the list.
     * @param node Node to prepend.
     */
    virtual void prepend(void* node);

    /**
     * @brief Link a node after a list position.
     * @param position Insertion position.
     * @param node Node to insert.
     */
    virtual void insert_after(void* position, void* node);

    /**
     * @brief Unlink a node and clear its list links.
     * @param node Node to remove.
     */
    virtual void unlink(void* node);

    /**
     * @brief Remove a registered node.
     * @param object Node to remove.
     */
    virtual void remove_node(void* object);

    /** @brief Run the registered nodes' update handlers. */
    virtual void update_nodes();

    /**
     * @brief Register and append a node.
     * @param object Node to append.
     * @param kind List kind, or -1 to use the node's own kind.
     */
    virtual void append_node(void* object, s32 kind);

    /**
     * @brief Register and prepend a node.
     * @param object Node to prepend.
     * @param kind List kind, or -1 to use the node's own kind.
     */
    virtual void prepend_node(void* object, s32 kind);

    /**
     * @brief Register a node after a list position.
     * @param position Insertion position.
     * @param object Node to insert.
     * @param kind List kind, or -1 to use the node's own kind.
     */
    virtual void insert_node_after(void* position, void* object, s32 kind);

    /**
     * @brief Set the next list in the chain.
     * @param attached List that follows this list.
     */
    virtual void set_next_list(void* attached);

    /** @brief Hook with no work in Lib's list. */
    virtual void idle();

    u32 node_counts_by_kind[17];
    u32 unk58;
    s32 active_node_index;
    s32 active_node_count;
    s32 node_buffer_capacity;
    void** owned_node_buffer;
    void** active_node_buffer;
    ResidentObjectList* next_list;
    ResidentObjectList* active_buffer_owner;
};

/** Resident object list (vtable D_0014FCB0) that is also a list object, and updates its ResidentImageObject nodes. */
class ResidentUpdateList : public ResidentObjectList, public ResidentListObject
{
public:
    virtual ~ResidentUpdateList();

    /**
     * @brief Remove a registered node, and make the next two hit tests start from the first node.
     * @param object Node to remove.
     */
    virtual void remove_node(void* object);

    /**
     * @brief Set the next list in the chain.
     * @param attached List that follows this list.
     */
    virtual void set_next_list(void* attached);

    /** @brief Do nothing. */
    virtual void idle();

    /**
     * @brief Return the list's kind.
     * @return Nine.
     */
    virtual s32 get_default_list_kind();

    /** @brief Update every node: follow targets, advance the images and rebuild hit boxes. */
    virtual void update();

    u32 unk8c;
};
extern "C" {
    /**
     * @brief Find the first object from a start node whose hit box a sphere touches, turning it to face the sphere.
     * @param list Object list to walk.
     * @param mask Bits an object's hit mask must share.
     * @param point Sphere centre in xyz and radius in w.
     * @param start Node to start from, or null for the first; the walk also starts from the first while unk8c is set.
     * @return The object hit, or null.
     */
    ResidentImageObject* resident_update_list_hit_test(ResidentUpdateList* list, u32 mask, const ResidentVector4* point,
                                       ResidentImageObject* start);

    /**
     * @brief Rebuild the hit box's matrices from its transform: the transpose, then the inverse from it.
     * @param object Object whose hit box is updated.
     */
    void resident_image_object_rebuild_hit_box(ResidentImageObject* object);

    /**
     * @brief Turn the image animation on or off, rebuilding the image channel while the object is registered.
     * @param object Object to update.
     * @param animated Nonzero to animate the record through an image channel.
     */
    void resident_image_object_set_animated(ResidentImageObject* object, u8 animated);

    /**
     * @brief Update the transform, turning it to face a point when asked to, then build the image's projection matrix.
     * @param object Object to update.
     * @param target Point to face, or null for the plain transform.
     */
    void resident_image_object_update_transform(ResidentImageObject* object, const ResidentVector4* target);

    /**
     * @brief Point the record at a resource's data, register the object and rebuild its image channel.
     * @param object Object to update.
     * @param resource Resource whose data follows a 16-byte prefix.
     */
    void resident_image_object_attach(ResidentImageObject* object, u8* resource);
}
#endif

#endif
