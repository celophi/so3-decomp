#include "main/resident_data.h"
#include "vu0.h"
#include "main/object_list.h"

extern "C" {
extern const ResidentVector4 g_default_bounding_sphere;
extern void* g_image_registry;
extern u8 g_hit_test_restart;

void lib_quaternion_from_euler(ResidentVector4* orientation, const ResidentVector4* rotation);

void func_4486A0(void* object);

void func_4D0260(void* list, void* object);

void func_4D02E0(void* list, void* object);

bool func_4D7D40(ResidentImageSequenceChannel* channel, ResidentRenderDataRecord* record, bool use_inline);

void lib_matrix_look_at(ResidentMatrix* output, const ResidentVector4* position, const ResidentVector4* direction, float roll);

void func_4CFB20(ResidentMatrix* output, const ResidentMatrix* input, float scale, float width, float height, float x_offset,
                 float y_offset);

void func_4CFC50(ResidentMatrix* output, const ResidentMatrix* input, float scale, float width, float height, float x_offset,
                 float y_offset);

void func_4D9E70(ResidentImageObjectBase* object);

void func_4CCCF0(const ResidentMatrix* source, ResidentVector4* output);

void lib_matrix_to_quaternion(ResidentVector4* output, const ResidentMatrix* input);

float func_4E28D0(ResidentImageObjectBase* camera);
}

typedef struct ResidentImageObjectOptions
{
    u8 pad00[0x2B4];
    u32 unk2B4;
    u32 unk2B8;
    u8 pad2BC[0x7];
    u8 unk2C3;
    u8 unk2C4;
} ResidentImageObjectOptions;

/**
 * @brief Replace the image channel with a new one bound to the record, while the object is registered and animated.
 * @param object Object whose channel is rebuilt; it has no channel when binding fails.
 */
static inline void rebuild_image_channel(ResidentImageObject* object)
{
    if (object->registered)
    {
        delete object->channel;
        object->channel = 0;

        if (object->animated)
        {
            object->channel = new (0) ResidentImageSequenceChannel;

            if (object->channel)
            {
                if (func_4D7D40(object->channel, &object->record, false))
                {
                    object->channel->unk3c = 0x8000;
                }
                else
                {
                    delete object->channel;
                    object->channel = 0;
                }
            }
        }
    }
}

/**
 * @brief Subtract one vector's xyz from another's, keeping the first vector's w.
 * @param output Difference.
 * @param left Vector to subtract from.
 * @param right Vector to subtract.
 */
static inline void subtract_xyz(ResidentVector4* output, const ResidentVector4* left, const ResidentVector4* right)
{
    output->x = left->x - right->x;
    output->y = left->y - right->y;
    output->z = left->z - right->z;
    output->w = left->w;
}

/**
 * @brief Test whether a list walk has come back to the list.
 * @param list List sentinel.
 * @param node Current node.
 * @return Whether node is the sentinel.
 */
static inline bool at_list_end(const ResidentListSentinel* list, const ResidentListSentinel* node)
{
    if (list == node)
    {
        return true;
    }

    return false;
}

/** @brief Destroy the list. */
ResidentUpdateList::~ResidentUpdateList()
{
}

/**
 * @brief Set the next list in the chain.
 * @param attached List that follows this list.
 */
void ResidentUpdateList::set_next_list(void* attached)
{
    next_list = static_cast<ResidentObjectList*>(attached);
}

/** @brief Do nothing. */
void ResidentUpdateList::idle()
{
}

/**
 * @brief Return the list's kind.
 * @return Nine.
 */
s32 ResidentUpdateList::get_default_list_kind()
{
    return 9;
}

/** @brief Unregister the object if it is registered, then detach it and queue it for release. */
void ResidentImageObject::destroy()
{
    if (registered != 0)
    {
        ResidentImageSource& registration = *this;

        func_4486A0(&registration);
        func_4D0260(g_image_registry, static_cast<ResidentImageSource*>(this));
        registered = 0;
    }

    ResidentImageObjectBase::destroy();
}

/**
 * @brief Copy another object's settings, record and transform state, and rebuild the image channel when it has one.
 * @param source Object to copy.
 */
void ResidentImageObject::copy_state(const ResidentImageObject* source)
{
    unk218 = source->unk218;
    unk21c = source->unk21c;
    unk220 = source->unk220;
    unk224 = source->unk224;
    elapsed = source->elapsed;
    hit_mask = source->hit_mask;
    hit_volume = source->hit_volume;
    record.next_offset = source->record.next_offset;
    record.storage_kind = source->record.storage_kind;
    record.index = source->record.index;
    record.key08 = source->record.key08;
    record.key0c = source->record.key0c;
    record.unk10[0] = source->record.unk10[0];
    record.unk10[1] = source->record.unk10[1];
    record.resolved_data = source->record.resolved_data;
    record.unk24[0] = source->record.unk24[0];
    record.unk24[1] = source->record.unk24[1];
    record.unk24[2] = source->record.unk24[2];
    record.unk24[3] = source->record.unk24[3];
    record.data = source->record.data;
    record.unk2c = source->record.unk2c;

    if (source->channel)
    {
        animated = 1;
        rebuild_image_channel(this);
    }

    position_source = source->position_source;
    camera = source->camera;
    faces_target = source->faces_target;
    unk2bd = source->unk2bd;
    unk2be = source->unk2be;
    animated = source->animated;
    registered = source->registered;
    unk2c1 = source->unk2c1;
    shared_image = source->shared_image;
    follow_position = source->follow_position;
    follow_camera = source->follow_camera;
    unk2c5 = source->unk2c5;
    unk2c6 = source->unk2c6;
    unk2c7 = source->unk2c7;
    ResidentImageObjectBase::copy_offset_transform_state(source);
}

void resident_image_object_set_unk2b8(void* object, u8 flag, u32 value)
{
    ResidentImageObjectOptions* receiver = (ResidentImageObjectOptions*)object;
    receiver->unk2C4 = flag;
    receiver->unk2B8 = value;
}

void resident_image_object_set_unk2b4(void* object, u8 flag, u32 value)
{
    ResidentImageObjectOptions* receiver = (ResidentImageObjectOptions*)object;
    receiver->unk2C3 = flag;
    receiver->unk2B4 = value;
}

/**
 * @brief Find the first object from a start node whose hit box a sphere touches, turning it to face the sphere.
 * @param list Object list to walk.
 * @param mask Bits an object's hit mask must share.
 * @param point Sphere centre in xyz and radius in w.
 * @param start Node to start from, or null for the first; the walk also starts from the first while unk8c is set.
 * @return The object hit, or null.
 */
ResidentImageObject* resident_update_list_hit_test(ResidentUpdateList* list, u32 mask, const ResidentVector4* point, ResidentImageObject* start)
{
    ResidentImageObject* node;

    if (start == 0 || list->unk8c != 0)
    {
        start = static_cast<ResidentImageObject*>(list->sentinel.next);
    }

    node = start;

    do
    {
        if (!at_list_end(&list->sentinel, node) && (mask & node->hit_mask) != 0 && (node->registered || node->shared_image))
        {
            ResidentVector4 world;
            ResidentVector4 local;
            ResidentHitBox* box = node->hit_volume;

            world = *point;
            world.w = 1.0f;
            vu0_apply_matrix(&box->inverse_transform, &world, &local);

            const ResidentVector4* extents = &box->half_extents;
            float x = extents->x + point->w;
            float y = extents->y + point->w;
            float z = extents->z + point->w;

            if (local.x >= -x && local.x <= x && local.z >= -z && local.z <= z && local.y >= -y && local.y <= y)
            {
                if (node->faces_target)
                {
                    resident_image_object_update_transform(node, &world);
                }

                return node;
            }
        }

        node = static_cast<ResidentImageObject*>(node->next);
    } while (node != start);

    return 0;
}

/**
 * @brief Advance an object's image time.
 * @param object Object to advance.
 * @param ticks Frame ticks to add.
 */
static inline void advance_elapsed(ResidentImageObject* object, float ticks)
{
    object->elapsed += ticks;
}

/**
 * @brief Update every node: follow targets, advance the images and rebuild hit boxes.
 */
void ResidentUpdateList::update()
{
    ResidentListSentinel* link;

    if (unk8c)
    {
        unk8c--;
    }

    link = &sentinel;

    for (;;)
    {
        ResidentImageObject* node;
        ResidentHitBox* box;

        link = link->next;

        if (at_list_end(&sentinel, link))
        {
            break;
        }

        node = static_cast<ResidentImageObject*>(link);

        if (node->follow_position)
        {
            ResidentVector4 position;
            ResidentVector4 orientation;
            ResidentImageObjectBase* source;

            if (!node->position_source->matrix_ready)
            {
                node->position_source->update_transform_matrix();
            }

            source = node->position_source;
            position.x = source->transform.rows[0].w;
            position.y = source->transform.rows[1].w;
            position.z = source->transform.rows[2].w;
            position.w = 1.0f;
            func_4CCCF0(&source->transform, &orientation);
            node->set_translation_vector(&position);
            node->set_orientation(&orientation);
        }

        if (node->follow_camera)
        {
            ResidentVector4 position;
            ResidentVector4 orientation;
            ResidentImageObjectBase* source;

            if (!node->camera->matrix_ready)
            {
                node->camera->update_transform_matrix();
            }

            source = node->camera;
            position.x = source->transform.rows[0].w;
            position.y = source->transform.rows[1].w;
            position.z = source->transform.rows[2].w;
            position.w = 1.0f;
            lib_matrix_to_quaternion(&orientation, &source->transform);
            node->set_translation_vector(&position);
            node->set_orientation(&orientation);

            if (!node->unk2c5)
            {
                node->unk218 = func_4E28D0(node->camera) * 2.0f;
            }
        }

        advance_elapsed(node, g_frame_ticks);

        if (node->channel)
        {
            s32 frame = node->elapsed;

            node->channel->unk48 = frame;
        }

        if (!node->faces_target)
        {
            if (node->transform_dirty)
            {
                resident_image_object_update_transform(node, 0);
            }
        }
        else
        {
            node->matrix_ready = 0;
            node->unk51 = 0;
        }

        box = node->hit_volume;

        if (box && box->transform_dirty)
        {
            box->update_transform_matrix();
            box->unk20e_0 = 1;
            box->unk20e_1 = 0;
            ee_transpose_matrix(&box->transposed_transform, &box->transform);
            func_4D9E70(box);
        }
    }
}

/**
 * @brief Copy the orientation quaternion.
 * @param value Source quaternion.
 */
void ResidentImageObject::set_orientation(const ResidentVector4* value)
{
    transform_dirty = 1;
    orientation = *value;
}

/**
 * @brief Copy the position.
 * @param value Source vector.
 */
void ResidentImageObject::set_translation_vector(const ResidentVector4* value)
{
    transform_dirty = 1;
    translation = *value;
}

/**
 * @brief Remove a registered node, and make the next two hit tests start from the first node.
 * @param object Node to remove.
 */
void ResidentUpdateList::remove_node(void* object)
{
    unk8c = 2;
    g_hit_test_restart |= 1;
    ResidentObjectList::remove_node(object);
}

/**
 * @brief Rebuild the hit box's matrices from its transform: the transpose, then the inverse from it.
 * @param object Object whose hit box is updated.
 */
void resident_image_object_rebuild_hit_box(ResidentImageObject* object)
{
    ResidentHitBox* box = object->hit_volume;

    if (box)
    {
        box->update_transform_matrix();
        box->unk20e_0 = 1;
        box->unk20e_1 = 0;
        ee_transpose_matrix(&box->transposed_transform, &box->transform);
        func_4D9E70(box);
    }
}

/**
 * @brief Turn the image animation on or off, rebuilding the image channel while the object is registered.
 * @param object Object to update.
 * @param animated Nonzero to animate the record through an image channel.
 */
void resident_image_object_set_animated(ResidentImageObject* object, u8 animated)
{
    object->animated = animated;
    rebuild_image_channel(object);
}

/**
 * @brief Update the transform, turning it to face a point when asked to, then build the image's projection matrix.
 * @param object Object to update.
 * @param target Point to face, or null for the plain transform.
 */
void resident_image_object_update_transform(ResidentImageObject* object, const ResidentVector4* target)
{
    ResidentImageHeader* image;
    s32 width;
    s32 height;

    if (object->faces_target && target)
    {
        ResidentVector4 position;
        ResidentVector4 direction;
        ResidentMatrix matrix;

        if (!object->matrix_ready)
        {
            object->update_transform_matrix();
        }

        position.x = object->transform.rows[0].w;
        position.y = object->transform.rows[1].w;
        position.z = object->transform.rows[2].w;
        position.w = 1.0f;
        subtract_xyz(&direction, target, &position);
        lib_matrix_look_at(&matrix, &position, &direction, 0.0f);
        matrix.rows[0].w = position.x;
        matrix.rows[1].w = position.y;
        matrix.rows[2].w = position.z;
        object->transform = matrix;
    }
    else
    {
        object->update_transform_matrix();
    }

    if (object->shared_image)
    {
        image = &static_cast<ResidentDisplayManager*>(g_renderer)->images[object->shared_image - 1];
    }
    else
    {
        u8* data = object->record.data;
        image = (ResidentImageHeader*)(data + ((u32*)data)[3]);
    }

    width = 1 << image->width_log2;
    height = 1 << image->height_log2;

    if (object->unk2c5)
    {
        func_4CFB20(&object->unk270, &object->transform, object->unk218, width, height, object->unk220, object->unk224);
    }
    else
    {
        func_4CFC50(&object->unk270, &object->transform, object->unk218, width, height, object->unk220, object->unk224);
    }
}

/**
 * @brief Point the record at a resource's data, register the object and rebuild its image channel.
 * @param object Object to update.
 * @param resource Resource whose data follows a 16-byte prefix.
 */
void resident_image_object_attach(ResidentImageObject* object, u8* resource)
{
    object->record.data = resource + 0x10;
    object->record.storage_kind = 0;
    object->record.resolved_data = 0;
    FlushCache(0);
    object->record.next_offset = 0;
    object->registered = 1;
    func_4D02E0(g_image_registry, static_cast<ResidentImageSource*>(object));
    rebuild_image_channel(object);
}

/** @brief Unregister the object and destroy its image channel. */
ResidentImageObject::~ResidentImageObject()
{
    if (registered)
    {
        ResidentImageSource& registration = *this;

        func_4486A0(&registration);
        func_4D0260(g_image_registry, static_cast<ResidentImageSource*>(this));
    }

    delete channel;
}

/** @brief Construct an unregistered object with no channel and the image centred. */
ResidentImageObject::ResidentImageObject()
{
    unk220 = 0.5f;
    unk224 = 0.5f;
    elapsed = 0.0f;
    unk2bd = 0;
    registered = 0;
    shared_image = 0;
    follow_position = 0;
    follow_camera = 0;
    unk2c5 = 0;
    unk2c6 = 0;
    unk2c7 = 0;
    unk6c = 0xD00;
    channel = 0;
}

/**
 * @brief Return zero.
 * @return Zero.
 */
s32 ResidentImageSource::get_default_kind()
{
    return 0;
}

/**
 * @brief Read the stored transformation matrix.
 * @return Matrix pointer.
 */
const ResidentMatrix* ResidentImageObject::get_transform_matrix()
{
    return &transform;
}

/**
 * @brief Read the additional local translation.
 * @return Stored translation.
 */
const ResidentVector4* ResidentImageObject::get_offset_translation() const
{
    return &offset_translation;
}

/**
 * @brief Read the additional local rotation.
 * @return Stored quaternion.
 */
const ResidentVector4* ResidentImageObject::get_offset_rotation() const
{
    return &offset_rotation;
}

/**
 * @brief Read the additional local scale.
 * @return Stored scale.
 */
const ResidentVector4* ResidentImageObject::get_offset_scale() const
{
    return &offset_scale;
}

/** @brief Draw in the main list (bucket zero). */
void ResidentImageObject::set_default_draw_bucket()
{
    draw_bucket = 0;
}

/** @brief Do nothing. */
void ResidentImageObject::render()
{
}

/**
 * @brief Give no centre for Lib's oriented-box visibility test.
 * @param output Unused.
 * @return Zero, so the test is skipped.
 */
s32 ResidentImageObject::get_box_cull_center(void* output)
{
    return 0;
}

/**
 * @brief Don't fade near the camera.
 * @param value Distance in front of the camera over the fade range.
 * @param mode Unused.
 * @return Whether the value is negative.
 */
bool ResidentImageObject::set_fade_alpha(float value, float mode)
{
    return value < 0.0f;
}

/**
 * @brief Return Lib's shared default bounding sphere.
 * @return Bounding sphere.
 */
const ResidentVector4* ResidentImageObject::get_bounding_sphere()
{
    return &g_default_bounding_sphere;
}

/**
 * @brief Do nothing.
 * @param matrix Unused.
 * @param context Unused.
 */
void ResidentImageObject::build_packet(const void* matrix, void* context)
{
}

/**
 * @brief Don't copy this object.
 * @return Null.
 */
ResidentImageObjectBase* ResidentImageObject::clone()
{
    return 0;
}

/** @brief Do nothing; this object has no copies. */
void ResidentImageObject::release_clone()
{
}

/**
 * @brief Copy the position.
 * @param value Source vector.
 */
void ResidentImageObject::copy_translation(const ResidentVector4* value)
{
    transform_dirty = 1;
    translation = *value;
}

/**
 * @brief Set the position and a w component of one.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void ResidentImageObject::set_translation(float x, float y, float z)
{
    transform_dirty = 1;
    translation.x = x;
    translation.y = y;
    translation.z = z;
    translation.w = 1.0f;
}

/**
 * @brief Set all four orientation components.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 * @param w Fourth component.
 */
void ResidentImageObject::set_orientation_components(float x, float y, float z, float w)
{
    transform_dirty = 1;
    orientation.x = x;
    orientation.y = y;
    orientation.z = z;
    orientation.w = w;
}

/**
 * @brief Copy the orientation quaternion.
 * @param value Source quaternion.
 */
void ResidentImageObject::copy_orientation(const ResidentVector4* value)
{
    transform_dirty = 1;
    orientation = *value;
}

/**
 * @brief Convert a rotation into the orientation.
 * @param value Source rotation.
 */
void ResidentImageObject::convert_rotation(const ResidentVector4* value)
{
    transform_dirty = 1;
    lib_quaternion_from_euler(&orientation, value);
}

/**
 * @brief Convert a rotation into the orientation.
 * @param value Source rotation.
 */
void ResidentImageObject::set_rotation_vector(const ResidentVector4* value)
{
    transform_dirty = 1;
    lib_quaternion_from_euler(&orientation, value);
}

/**
 * @brief Convert three rotation components into the orientation.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void ResidentImageObject::set_rotation(float x, float y, float z)
{
    ResidentVector4 rotation;

    transform_dirty = 1;
    rotation.x = x;
    rotation.y = y;
    rotation.z = z;
    rotation.w = 1.0f;
    lib_quaternion_from_euler(&orientation, &rotation);
}

/**
 * @brief Copy the scale.
 * @param value Source vector.
 */
void ResidentImageObject::copy_scale(const ResidentVector4* value)
{
    transform_dirty = 1;
    scale = *value;
}

/**
 * @brief Copy the scale.
 * @param value Source vector.
 */
void ResidentImageObject::set_scale_vector(const ResidentVector4* value)
{
    transform_dirty = 1;
    scale = *value;
}

/**
 * @brief Set the scale's xyz components.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void ResidentImageObject::set_scale(float x, float y, float z)
{
    transform_dirty = 1;
    scale.x = x;
    scale.y = y;
    scale.z = z;
}

/**
 * @brief Return zero.
 * @return Zero.
 */
s32 ResidentImageObject::get_record_kind()
{
    return 0;
}

/**
 * @brief Get the record while the object is registered.
 * @return The record, or null.
 */
void* ResidentImageObject::get_record()
{
    if (registered != 0)
    {
        return &record;
    }

    return 0;
}
