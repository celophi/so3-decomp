#include "include_asm.h"
#include "overlays/lib/scratchpad_texture_cache.h"
#include "vu0.h"
#include "overlays/lib/shape_vu0.h"
#include "overlays/lib/text_00419A70.h"
#include "main/resident_data.h"
#include "sdk/main/libkernl_00121940.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_0044ABE0.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "overlays/lib/render_buffer.h"
#include "overlays/lib/character_names.h"
#include "overlays/lib/text_004DD440.h"
#include "overlays/lib/text_0046AE20.h"
#include "overlays/lib/image_model.h"
#include "overlays/lib/model_packet.h"
#include "overlays/lib/grid_bounds_vu0.h"
#include "overlays/lib/transform_inlines.h"
#include "overlays/lib/text_0043A920.h"
#include "overlays/lib/widget_aggregate.h"
#include "overlays/lib/message_window.h"
#include "overlays/lib/text_004095C0.h"
#include "overlays/lib/item_allocation.h"
#include "sdk/main/libm_guess_0013F3E0.h"

extern "C" void func_00461830(void* embedded, void* adjusted);

enum
{
    DRAWING_STORAGE_ALIGNMENT = 128,
    DRAWING_STORAGE_PREFIX = 64,
    DRAWING_STORAGE_DMA_ADDRESS_TAG = 0x30000000
};

/** Partial text resource fields and the inherited redraw flag. */
typedef struct LibMultilineResourceState
{
    u8 pad00[0x3C];
    u8 redraw;
    u8 pad3d[0xCB];
    u32 source;
    u32 key;
    u8 flag;
    u8 pending;
    u8 pad112[0x432];
    u32 mode;
} LibMultilineResourceState;

/** Partial runtime queue links carried by each transform receiver. */
typedef struct LibRuntimeListNode
{
    u8 pad00[0x94];
    FieldRuntime* owner;
    struct LibRuntimeListNode* previous;
    struct LibRuntimeListNode* next;
} LibRuntimeListNode;
/** Partial runtime display queue with its head, tail, and count. */
typedef struct LibRuntimeListState
{
    u8 pad00[0x55C];
    LibRuntimeListNode* first;
    LibRuntimeListNode* last;
    s32 count;
} LibRuntimeListState;

/** @brief Free the buffer and detach. */
LibClass174D70::~LibClass174D70()
{
    delete[] unk3c;
}

/** @brief Start with no objects and flag 0x1 set. */
LibClass174D70::LibClass174D70()
{
    count = 0;
    flags = 1;
    unk3c = 0;
}

/**
 * @brief Return a shape's record at an offset from its first record.
 * @param shape Shape descriptor.
 * @param records Record array of the shape data.
 * @param offset Record offset from the shape's first record.
 * @return The record, or null when the shape has no records.
 */
static inline FieldShapeRecord20* shape_record_at(FieldShapeOwner18* shape, FieldShapeRecord20* records, s32 offset)
{
    return shape->unk0e == -1 ? 0 : &records[shape->unk0e + offset];
}

/**
 * @brief Count the children of a shape.
 * @param shape Shape descriptor.
 * @return Number of child shapes.
 */
static inline s32 shape_child_count(FieldShapeOwner18* shape)
{
    s32 count = 0;
    FieldShapeOwner18* child = shape->unk00;

    if (child == 0)
    {
        return 0;
    }

    for (;;)
    {
        count++;

        if (child->is_last())
        {
            break;
        }

        child++;
    }

    return count;
}

/**
 * @brief Return one child of a shape.
 * @param shape Shape descriptor.
 * @param index Child index.
 * @return The child, or null when the shape has fewer children.
 */
static inline FieldShapeOwner18* shape_child_at(FieldShapeOwner18* shape, s32 index)
{
    FieldShapeOwner18* child = shape->unk00;

    if (child == 0)
    {
        return 0;
    }

    while (child)
    {
        if (--index < 0)
        {
            return child;
        }

        if (child->is_last())
        {
            return 0;
        }

        child++;
    }

    return child;
}

/**
 * @brief Find a record of the shape with the given name in bound shape data.
 * @param storage Shape resource storage.
 * @param name Shape name, compared over sixteen characters.
 * @param offset Record offset from the shape's first record.
 * @return The record, or null when the data is not bound, no shape has the name or the shape has no records.
 */
FieldShapeRecord20* func_0045AE10(FieldClass1515D0* storage, const char* name, s32 offset)
{
    FieldShapeData30* data = storage->unk00;

    if (!(data->prefix.flags & LIB_SHAPE_DATA_BOUND))
    {
        return 0;
    }

    FieldShapeOwner18* shape = reinterpret_cast<FieldShapeOwner18*>(data + 1);
    FieldShapeRecord20* records = data->prefix.unk0c;
    s32 count = data->prefix.shape_count;

    for (s32 i = 0; i < count; i++)
    {
        if (lib_compare_bounded_strings(name, reinterpret_cast<const char*>(&storage->unk00->prefix.unk08[shape->unk0c].unk04),
                                        LIB_SHAPE_NAME_LENGTH) == 0)
        {
            return shape_record_at(shape, records, offset);
        }

        shape++;
    }

    return 0;
}

/**
 * @brief Set the flag of the record with the given identifier, searching a sibling run of shapes and their children.
 * @param storage Shape resource storage.
 * @param shape First shape of the sibling run.
 * @param id Record identifier.
 * @param flag New flag value.
 */
void func_0045AF10(FieldClass1515D0* storage, FieldShapeOwner18* shape, u16 id, s32 flag)
{
    FieldShapeRecord20* records = storage->unk00->prefix.unk0c;

    while (shape)
    {
        if (shape->unk0e != -1)
        {
            FieldShapeRecord20* record = &records[shape->unk0e];

            for (;;)
            {
                FieldShapeRecordInfo* info = &record->unk0c;

                if (record->unk0c.unk02 == id)
                {
                    info->unk00_4 = flag;
                    return;
                }

                if (info->unk00_5)
                {
                    break;
                }

                record++;
            }
        }

        s32 count = shape_child_count(shape);

        for (s32 i = 0; i < count; i++)
        {
            func_0045AF10(storage, shape_child_at(shape, i), id, flag);
        }

        if (shape->is_last())
        {
            return;
        }

        shape++;
    }
}

/**
 * @brief Set the flag of the record with the given identifier anywhere in the shape data.
 * @param storage Shape resource storage.
 * @param id Record identifier.
 * @param flag New flag value.
 */
void func_0045B0E0(FieldClass1515D0* storage, s32 id, s32 flag)
{
    func_0045AF10(storage, reinterpret_cast<FieldShapeOwner18*>(storage->unk00 + 1), id, flag);
}

/**
 * @brief Bind shape data: turn its offsets into pointers once and look up each shape's transform by name.
 * @param storage Shape resource storage.
 * @param manager Entry table searched for the shape names.
 */
void func_0045B110(FieldClass1515D0* storage, LibScene* manager)
{
    if (!(storage->unk00->prefix.flags & LIB_SHAPE_DATA_BOUND))
    {
        storage->unk00->prefix.unk08 =
            reinterpret_cast<FieldShapeEntry14*>(reinterpret_cast<u8*>(storage->unk00) + reinterpret_cast<s32>(storage->unk00->prefix.unk08));
        storage->unk00->prefix.unk0c =
            reinterpret_cast<FieldShapeRecord20*>(reinterpret_cast<u8*>(storage->unk00) + reinterpret_cast<s32>(storage->unk00->prefix.unk0c));
    }

    FieldShapeOwner18* shape = reinterpret_cast<FieldShapeOwner18*>(storage->unk00 + 1);
    s32 count = storage->unk00->prefix.shape_count;

    for (s32 i = 0; i < count; i++)
    {
        if (!(storage->unk00->prefix.flags & LIB_SHAPE_DATA_BOUND) && shape->unk00)
        {
            shape->unk00 = reinterpret_cast<FieldShapeOwner18*>(reinterpret_cast<u8*>(storage->unk00) + reinterpret_cast<s32>(shape->unk00));
        }

        shape->unk04 = static_cast<LibTransformOwner*>(
            lib_find_named_entry_cached(manager, reinterpret_cast<const char*>(&storage->unk00->prefix.unk08[shape->unk0c].unk04), 0));
        shape++;
    }

    storage->unk00->prefix.flags |= LIB_SHAPE_DATA_BOUND;
}

/**
 * @brief Bind shape storage to a resource, freeing the previous one unless it was borrowed, and find its attribute
 *        chunk.
 * @param storage Shape resource storage.
 * @param resource Resource chunks; the storage borrows them.
 * @return One when an attribute chunk was found, otherwise zero.
 */
s32 func_0045B210(FieldClass1515D0* storage, void* resource)
{
    if (!storage->unk08)
    {
        ::operator delete(storage->unk04);
    }

    storage->unk08 = 1;
    storage->unk04 = resource;
    LibResourceChunkHeader* chunk = static_cast<LibResourceChunkHeader*>(resource);

    for (;;)
    {
        if (chunk->magic == LIB_SHAPE_ATTRIBUTE_MAGIC)
        {
            break;
        }

        chunk = lib_next_chunk(chunk);

        if (chunk == 0)
        {
            return 0;
        }
    }

    storage->unk00 = reinterpret_cast<FieldShapeData30*>(chunk + 1);
    return 1;
}

/**
 * @brief Return one child of a shape.
 * @param shape Shape descriptor.
 * @param index Child index.
 * @return The child, or null when the shape has fewer children.
 */
FieldShapeOwner18* func_0045B2B0(FieldShapeOwner18* shape, s32 index)
{
    return shape_child_at(shape, index);
}

/**
 * @brief Count the children of a shape.
 * @param shape Shape descriptor.
 * @return Number of child shapes.
 */
s32 func_0045B320(FieldShapeOwner18* shape)
{
    return shape_child_count(shape);
}

extern "C" u8 D_001B6288;

/** Transform of the shape a record test runs in. */
extern "C" LibTransform* D_001B6574;

/** Fractions along the segment where the last segment test found it enters and leaves a record. */
extern "C" float D_0050CB70[];

#define LIB_FLOAT_INFINITY (1.0f / 0.0f)

/**
 * @brief Test whether a shape transform's transpose of its base matrix is current.
 * @param transform Shape transform.
 * @return Whether the transpose is current.
 */
static inline bool transpose_current(const LibTransform* transform)
{
    return transform->unk20e_1;
}

/**
 * @brief Rebuild a shape transform's transpose of its base matrix unless it is current.
 * @param transform Shape transform.
 */
static inline void refresh_shape_transpose(LibTransform* transform)
{
    if (!transpose_current(transform))
    {
        transform->unk20e_1 = 1;
        transform->unk20e_0 = 0;
        ee_transpose_matrix(&transform->transposed_transform, &transform->base_transform);
    }
}

/**
 * @brief Recompute a shape transform's largest axis scale unless it is current.
 * @param transform Shape transform.
 */
static inline void refresh_shape_scale(LibTransform* transform)
{
    if (!transform->unk20e_3)
    {
        LibVector4 scales;

        transform->unk20e_3 = 1;
        vu0_start_microprogram_7f0_rows(&transform->transform);
        vu0_wait_microprogram();
        vu0_read_vf6(&scales);
        float largest = 0.0f;
        largest = scales.x;
        largest = ee_max(largest, scales.y);
        largest = ee_max(largest, scales.z);
        transform->unk204 = largest;
    }
}

/**
 * @brief Test whether a segment touches a box moved by the matrix in vf1-vf4, its half extents grown by vf5.y,
 *        recording where it enters and leaves.
 * @param centre Aligned box centre.
 * @param half_extents Aligned half extents in xyz.
 * @param start Aligned segment start.
 * @param end Aligned segment end.
 * @return Whether the segment touches the box.
 */
bool func_0045B360(const LibVector4* centre, const void* half_extents, const LibVector4* start,
                   const LibVector4* end)
{
    LibVector4 extents;
    LibVector4 offset;
    LibVector4 direction;

    vu0_box_segment_offset(centre, start, end, half_extents);
    D_0050CB70[0] = -LIB_FLOAT_INFINITY;
    D_0050CB70[1] = LIB_FLOAT_INFINITY;
    vu0_store_vf17(&extents);
    vu0_segment_direction();
    vu0_box_ray_project();
    vu0_store_box_ray_projection(&offset, &direction);
    float start_near = D_0050CB70[0];
    float start_far = D_0050CB70[1];

    bool clip_z = false;
    bool clip_z_low = false;
    bool clip_y = false;
    bool clip_y_low = false;
    bool clip_x = false;

    if (func_0045C350(&D_0050CB70[0], &D_0050CB70[1], direction.x, -offset.x - extents.x) &&
        func_0045C350(&D_0050CB70[0], &D_0050CB70[1], -direction.x, offset.x - extents.x))
    {
        clip_x = true;
    }

    if (clip_x && func_0045C350(&D_0050CB70[0], &D_0050CB70[1], direction.y, -offset.y - extents.y))
    {
        clip_y_low = true;
    }

    if (clip_y_low && func_0045C350(&D_0050CB70[0], &D_0050CB70[1], -direction.y, offset.y - extents.y))
    {
        clip_y = true;
    }

    if (clip_y && func_0045C350(&D_0050CB70[0], &D_0050CB70[1], direction.z, -offset.z - extents.z))
    {
        clip_z_low = true;
    }

    if (clip_z_low && func_0045C350(&D_0050CB70[0], &D_0050CB70[1], -direction.z, offset.z - extents.z))
    {
        clip_z = true;
    }

    bool hit = clip_z != false && (D_0050CB70[0] != start_near || D_0050CB70[1] != start_far);

    if (hit)
    {
        if (!(D_0050CB70[0] <= 0.0f) && D_0050CB70[0] < 1.0f)
        {
            return true;
        }

        if (!(D_0050CB70[1] <= 0.0f) && D_0050CB70[1] < 1.0f)
        {
            return true;
        }

        if (D_0050CB70[0] <= 0.0f && !(D_0050CB70[1] < 1.0f))
        {
            return true;
        }

        if (!(D_0050CB70[0] < 1.0f) && D_0050CB70[1] <= 0.0f)
        {
            return true;
        }

        return false;
    }

    return false;
}

/**
 * @brief Test whether a segment touches a sphere moved by the matrix in vf1-vf4, its radius scaled by vf5.x and grown
 *        by vf5.y, recording where it enters and leaves.
 * @param sphere Aligned sphere: centre in xyz, radius in w.
 * @param start Aligned segment start.
 * @param end Aligned segment end.
 * @return Whether the segment touches the sphere.
 */
extern "C" bool func_0045B740(const LibVector4* sphere, const LibVector4* start, const LibVector4* end)
{
    LibVector4 discriminant;
    LibVector4 enter;
    LibVector4 leave;

    vu0_segment_sphere_setup(sphere, start, end);
    vu0_segment_sphere_store_discriminant(&discriminant);

    if (discriminant.x < 0.0f)
    {
        return false;
    }

    if (!(discriminant.x <= -1e-6f) && discriminant.x < 1e-6f)
    {
        return true;
    }

    vu0_segment_sphere_fractions(&leave, &enter);

    if ((!(leave.x < 1.0f) && !(enter.x < 0.0f)) || (enter.x <= 0.0f && leave.x <= 1.0f))
    {
        return false;
    }

    D_0050CB70[0] = enter.x;
    D_0050CB70[1] = leave.x;
    return true;
}

/** Radius every segment test adds to the spheres it checks. */
extern "C" float D_001B6568;

/**
 * @brief Test whether a segment touches a collision record.
 * @param record Record to test.
 * @param start Aligned segment start.
 * @param end Aligned segment end.
 * @return Whether the record is enabled and the segment touches it.
 */
static inline bool segment_hits_record(FieldShapeRecord20* record, const LibVector4* start, const LibVector4* end)
{
    if (record->unk0c.unk00_4)
    {
        return false;
    }

    switch (record->unk0c.unk00_0_3)
    {
    case LIB_SHAPE_KIND_BOX:
        return func_0045B360((const LibVector4*)&record->unk10, record, start, end);
    case LIB_SHAPE_KIND_SPHERE:
        return func_0045B740((const LibVector4*)&record->unk10, start, end);
    default:
        return false;
    }
}

s32 func_0045B920(FieldShapeOwner18* shape, const LibVector4* start, const LibVector4* end)
{
    if (!(D_001B6288 & shape->unk08[1]))
    {
        return 0;
    }

    LibTransform* transform = (LibTransform*)shape->unk04;

    if (transform == 0)
    {
        return 0;
    }

    LibVector4 saved[8];
    LibVector4 scale;

    vu0_save_vf1_vf5(saved);

    if (!transform->matrix_ready)
    {
        transform->update_transform_matrix();
    }

    refresh_shape_transpose(transform);
    refresh_shape_scale(transform);
    const LibVector4* bound = (const LibVector4*)&shape->unk10;
    scale.x = transform->unk204;
    scale.y = D_001B6568;
    vu0_load_matrix_and_scale(&transform->transposed_transform, &scale);

    if (!func_0045B740(bound, start, end))
    {
        vu0_restore_vf1_vf5(saved);
        return 0;
    }

    s32 index = shape->unk0e;

    if (index >= 0)
    {
        D_001B6574 = transform;

        if (!(D_001B6288 & shape->unk08[0]))
        {
            vu0_restore_vf1_vf5(saved);
            return 0;
        }

        FieldShapeRecord20* record = &D_001B656C[index];

        for (;;)
        {
            if (segment_hits_record(record, start, end))
            {
                D_0050CB30.unk04 = shape;
                D_0050CB30.unk00 = 5;
                D_0050CB30.unk0c = record;
                D_0050CB30.unk2c = start;
                D_0050CB30.unk30 = end;
                D_0050CB30.unk14 = D_001B6574;
                return 1;
            }

            if (record->unk0c.unk00_5)
            {
                break;
            }

            record++;
        }
    }

    FieldShapeOwner18* child = shape->unk00;

    if (child == 0)
    {
        vu0_restore_vf1_vf5(saved);
        return 0;
    }

    for (;;)
    {
        if (func_0045B920(child, start, end))
        {
            return 1;
        }

        if (child->is_last())
        {
            vu0_restore_vf1_vf5(saved);
            return 0;
        }

        child++;
    }
}

/** Select the referenced shape record and test its descriptor. */
s32 func_0045BD20(void* object, void* arg0, void* arg1)
{
    void* descriptor = *(void**)object;
    D_001B656C = (struct FieldShapeRecord20*)*(void**)((u8*)descriptor + 0xC);
    return func_0045B920((FieldShapeOwner18*)((u8*)descriptor + 0x30), (const LibVector4*)arg0,
                         (const LibVector4*)arg1);
}

/**
 * @brief Test whether a point moved by a matrix lies inside an axis-aligned box whose half extents are scaled by vf5.x.
 * @param centre Box centre.
 * @param half_extents Aligned half extents in xyz.
 * @param point Aligned point to test.
 * @param matrix Aligned matrix that moves the point into the box's space.
 * @return Whether the point is inside (or on) the box.
 */
extern "C" bool func_0045BD50(const LibVector4* centre, const void* half_extents, const LibVector4* point,
                              const LibMatrix44Value* matrix)
{
    LibVector4 local;
    LibVector4 extents;

    vu0_box_point_local(point, matrix, half_extents);
    vu0_store_vf14(&local);
    vu0_store_vf30(&extents);

    if (!(centre->x - extents.x <= local.x))
    {
        return false;
    }

    if (centre->x + extents.x < local.x)
    {
        return false;
    }

    if (!(centre->y - extents.y <= local.y))
    {
        return false;
    }

    if (centre->y + extents.y < local.y)
    {
        return false;
    }

    if (!(centre->z - extents.z <= local.z))
    {
        return false;
    }

    if (centre->z + extents.z < local.z)
    {
        return false;
    }

    return true;
}

/**
 * @brief Test whether a point is inside a sphere moved by the matrix in vf1-vf4 and scaled by vf5.x.
 * @param sphere Sphere: centre in xyz, radius in w.
 * @param point Point to test.
 * @return Whether the point is inside (or on) the sphere.
 */
extern "C" bool func_0045BE60(const LibVector4* sphere, const LibVector4* point)
{
    LibVector4 margin;

    vu0_sphere_point_margin(sphere, point);
    vu0_store_vf10(&margin);

    if (margin.w < 0.0f)
    {
        return false;
    }

    return true;
}

/**
 * @brief Test whether a point lies inside a collision shape; boxes are tested in the camera transform's space.
 * @param shape Shape to test.
 * @param point Aligned point to test.
 * @return Whether the shape is enabled and contains the point.
 */
extern "C" bool func_0045BED0(FieldShapeRecord20* shape, const LibVector4* point)
{
    if (shape->unk0c.unk00_4)
    {
        return false;
    }

    switch (shape->unk0c.unk00_0_3)
    {
    case LIB_SHAPE_KIND_BOX:
        if (!D_001B6574->unk20e_2)
        {
            // TODO: only two quadwords are saved, but the frame only matches with room for four.
            LibVector4 registers[4];

            vu0_save_vf6_vf8(registers);
            func_004D9E70(D_001B6574);
            vu0_restore_vf6_vf8(registers);
        }

        return func_0045BD50((const LibVector4*)&shape->unk10, shape, point, &D_001B6574->inverse_transform);
    case LIB_SHAPE_KIND_SPHERE:
        return func_0045BE60((const LibVector4*)&shape->unk10, point);
    default:
        return false;
    }
}



/**
 * @brief Test a point against a shape, its records and its children, recording the first record that contains it.
 *
 * The shape's bounding sphere is checked first, with the shape's transform in vf1-vf5. The caller's vf1-vf5 come
 * back only when nothing is hit.
 * @param shape Shape to test.
 * @param query Aligned point to test.
 * @return One when a record contains the point, otherwise zero.
 */
s32 func_0045BFB0(FieldShapeOwner18* shape, const LibVector4* query)
{
    if (!(D_001B6288 & shape->unk08[1]))
    {
        return 0;
    }

    LibTransform* transform = (LibTransform*)shape->unk04;

    if (transform == 0)
    {
        return 0;
    }

    LibVector4 saved[8];
    LibVector4 scale;
    LibVector4 margin;

    vu0_save_vf1_vf5(saved);

    if (!transform->matrix_ready)
    {
        transform->update_transform_matrix();
    }

    refresh_shape_transpose(transform);

    refresh_shape_scale(transform);

    scale.x = transform->unk204;
    vu0_sphere_point_margin_with(&transform->transposed_transform, &shape->unk10, &scale, query);
    vu0_store_vf10(&margin);

    if (margin.w < 0.0f)
    {
        vu0_restore_vf1_vf5(saved);
        return 0;
    }

    s32 index = shape->unk0e;

    if (index >= 0)
    {
        D_001B6574 = transform;

        if (!(D_001B6288 & shape->unk08[0]))
        {
            vu0_restore_vf1_vf5(saved);
            return 0;
        }

        FieldShapeRecord20* record = &D_001B656C[index];

        for (;;)
        {
            if (func_0045BED0(record, query))
            {
                D_0050CB30.unk04 = shape;
                D_0050CB30.unk00 = 4;
                D_0050CB30.unk0c = record;
                D_0050CB30.unk28 = query;
                D_0050CB30.unk14 = D_001B6574;
                return 1;
            }

            if (record->unk0c.unk00_5)
            {
                break;
            }

            record++;
        }
    }

    FieldShapeOwner18* child = shape->unk00;

    if (child == 0)
    {
        vu0_restore_vf1_vf5(saved);
        return 0;
    }

    for (;;)
    {
        if (func_0045BFB0(child, query))
        {
            return 1;
        }

        if (child->is_last())
        {
            vu0_restore_vf1_vf5(saved);
            return 0;
        }

        child++;
    }
}

/**
 * @brief Clip a ray's fraction interval against one slab plane.
 * @param near_fraction Entry fraction, raised when the plane cuts the start of the interval.
 * @param far_fraction Exit fraction, lowered when the plane cuts the end of the interval.
 * @param direction Ray direction along the slab axis.
 * @param distance Signed distance from the ray start to the plane along the axis.
 * @return One while the interval is not empty, otherwise zero.
 */
extern "C" s32 func_0045C350(float* near_fraction, float* far_fraction, float direction, float distance)
{
    if (direction > 0.0f)
    {
        if (distance > direction * *far_fraction)
        {
            return 0;
        }

        if (distance > direction * *near_fraction)
        {
            *near_fraction = distance / direction;
        }

        return 1;
    }

    if (direction < 0.0f)
    {
        if (distance > direction * *near_fraction)
        {
            return 0;
        }

        if (distance > direction * *far_fraction)
        {
            *far_fraction = distance / direction;
        }

        return 1;
    }

    s32 result = 1;

    if (!(distance <= 0.0f))
    {
        result = 0;
    }

    return result;
}

/**
 * @brief Clip a ray against a box moved by the matrix in vf1-vf4 and store where it enters and leaves.
 * @param centre Aligned box centre.
 * @param half_extents Box half extents.
 * @param ray Aligned ray: origin, then direction.
 * @param points Receives the entry point, then the exit point when the ray leaves the box.
 * @return How many points were stored.
 */
extern "C" s32 func_0045C420(const LibVector4* centre, const float* half_extents, const LibVector4* ray,
                             LibVector4* points)
{
    LibVector4 fractions;
    LibVector4 offset;
    LibVector4 direction;

    vu0_box_ray_offset(ray, centre, ray + 1);
    fractions.x = 0.0f;
    fractions.y = LIB_FLOAT_INFINITY;
    vu0_box_ray_project();
    vu0_store_box_ray_projection(&offset, &direction);
    float start_near = fractions.x;
    float start_far = fractions.y;

    bool clip_z = false;
    bool clip_z_low = false;
    bool clip_y = false;
    bool clip_y_low = false;
    bool clip_x = false;

    if (func_0045C350(&fractions.x, &fractions.y, direction.x, -offset.x - half_extents[0]) &&
        func_0045C350(&fractions.x, &fractions.y, -direction.x, offset.x - half_extents[0]))
    {
        clip_x = true;
    }

    if (clip_x && func_0045C350(&fractions.x, &fractions.y, direction.y, -offset.y - half_extents[1]))
    {
        clip_y_low = true;
    }

    if (clip_y_low && func_0045C350(&fractions.x, &fractions.y, -direction.y, offset.y - half_extents[1]))
    {
        clip_y = true;
    }

    if (clip_y && func_0045C350(&fractions.x, &fractions.y, direction.z, -offset.z - half_extents[2]))
    {
        clip_z_low = true;
    }

    if (clip_z_low && func_0045C350(&fractions.x, &fractions.y, -direction.z, offset.z - half_extents[2]))
    {
        clip_z = true;
    }

    bool hit = clip_z != false && (fractions.x != start_near || fractions.y != start_far);

    if (hit)
    {
        vu0_load_vf16(&fractions);

        if (!(fractions.x <= 0.0f))
        {
            vu0_ray_points_at_fractions();

            if (fractions.y < LIB_FLOAT_INFINITY)
            {
                vu0_store_vf20_vf21(points);
                return 2;
            }

            vu0_store_vf20(points);
            return 1;
        }

        if (fractions.y < LIB_FLOAT_INFINITY)
        {
            vu0_ray_point_at_far_fraction();
            vu0_store_vf20(points);
            return 1;
        }

        return 0;
    }

    return 0;
}

/**
 * @brief Find where a ray, from its origin on, enters and leaves a sphere moved by the matrix in vf1-vf4.
 * @param sphere Aligned sphere: centre in xyz, radius in w.
 * @param ray Aligned ray: origin, then direction.
 * @param points Receives the entry point, then the exit point when both lie ahead of the origin.
 * @return How many points were stored.
 */
extern "C" s32 func_0045C770(const LibVector4* sphere, const LibVector4* ray, LibVector4* points)
{
    LibVector4 discriminant;
    LibVector4 root;
    LibVector4 enter;
    LibVector4 leave;
    LibVector4 touch;

    vu0_load_vf10(sphere);
    vu0_ray_sphere_setup(ray, ray + 1);
    vu0_ray_sphere_store_discriminant(&root, &discriminant);

    if (discriminant.x < 0.0f)
    {
        return 0;
    }

    if (!(discriminant.x <= 0.0f))
    {
        vu0_ray_sphere_fractions();
        vu0_store_ray_sphere_fractions(&enter, &leave);

        if (!(enter.x < 0.0f))
        {
            vu0_ray_sphere_points();
            vu0_store_vf23_vf24(points);
            return 2;
        }

        if (!(leave.x < 0.0f))
        {
            // TODO: this stores the point at the entry fraction, which is behind the origin here; it looks like a
            // slip for the exit point, but it's what the game does.
            vu0_ray_sphere_enter_point();
            vu0_store_vf23(points);
            return 1;
        }

        return 0;
    }

    vu0_ray_sphere_touch();
    vu0_store_vf20(&touch);

    if (!(touch.x < 0.0f))
    {
        vu0_store_vf23(points);
        return 1;
    }

    return 0;
}

/**
 * @brief Test whether a ray passes through a box moved by the matrix in vf1-vf4, by its separating axes.
 * @param centre Aligned box centre.
 * @param half_extents Aligned half extents in xyz.
 * @param ray Aligned ray: origin, then direction.
 * @return Whether no axis separates them.
 */
extern "C" bool func_0045C910(const LibVector4* centre, const void* half_extents, const LibVector4* ray)
{
    LibVector4 tests[2];

    vu0_box_ray_axis_x(centre, ray, ray + 1, half_extents);
    vu0_store_vf24_vf25(tests);

    if (!(tests[0].x <= 0.0f) && !(tests[1].x < 0.0f))
    {
        return false;
    }

    vu0_box_ray_axis_y();
    vu0_store_vf24_vf25(tests);

    if (!(tests[0].y <= 0.0f) && !(tests[1].y < 0.0f))
    {
        return false;
    }

    vu0_box_ray_axis_z();
    vu0_store_vf24_vf25(tests);

    if (!(tests[0].z <= 0.0f) && !(tests[1].z < 0.0f))
    {
        return false;
    }

    vu0_box_ray_cross_x();
    vu0_store_vf24(tests);

    if (tests[0].y < 0.0f)
    {
        return false;
    }

    vu0_box_ray_cross_y();
    vu0_store_vf24(tests);

    if (tests[0].x < 0.0f)
    {
        return false;
    }

    vu0_box_ray_cross_z();
    vu0_store_vf24(tests);

    if (tests[0].x < 0.0f)
    {
        return false;
    }

    return true;
}

/**
 * @brief Test whether a ray, from its origin on, passes through a sphere moved by the matrix in vf1-vf4 and scaled
 *        by vf5.x.
 * @param sphere Sphere: centre in xyz, radius in w.
 * @param ray Ray: origin, then unit direction.
 * @return Whether the ray touches the sphere.
 */
extern "C" bool func_0045CB40(const LibVector4* sphere, const LibVector4* ray)
{
    LibVector4 gap;

    vu0_sphere_ray_gap(sphere, ray, ray + 1);
    vu0_store_vf10(&gap);

    if (!(gap.w <= 0.0f))
    {
        return false;
    }

    return true;
}

/**
 * @brief Test whether a ray passes through a collision record.
 * @param record Record to test.
 * @param ray Aligned ray: origin, then direction.
 * @return Whether the record is enabled and the ray passes through it.
 */
static inline bool ray_hits_record(FieldShapeRecord20* record, const LibVector4* ray)
{
    if (record->unk0c.unk00_4)
    {
        return false;
    }

    switch (record->unk0c.unk00_0_3)
    {
    case LIB_SHAPE_KIND_BOX:
        return func_0045C910((const LibVector4*)&record->unk10, record, ray);
    case LIB_SHAPE_KIND_SPHERE:
        return func_0045CB40((const LibVector4*)&record->unk10, ray);
    default:
        return false;
    }
}

/**
 * @brief Test a ray against a shape, its records and its children, recording the first record it passes through.
 *
 * The shape's bounding sphere is checked first, with the shape's transform in vf1-vf5. The caller's vf1-vf5 come
 * back only when nothing is hit.
 * @param shape Shape to test.
 * @param ray Aligned ray: origin, then direction.
 * @return One when the ray passes through a record, otherwise zero.
 */
s32 func_0045CBE0(FieldShapeOwner18* shape, const LibVector4* ray)
{
    if (!(D_001B6288 & shape->unk08[1]))
    {
        return 0;
    }

    LibTransform* transform = (LibTransform*)shape->unk04;

    if (transform == 0)
    {
        return 0;
    }

    LibVector4 saved[8];
    LibVector4 scale;
    LibVector4 gap;

    vu0_save_vf1_vf5(saved);

    if (!transform->matrix_ready)
    {
        transform->update_transform_matrix();
    }

    refresh_shape_transpose(transform);

    refresh_shape_scale(transform);

    scale.x = transform->unk204;
    vu0_sphere_ray_gap_with(&transform->transposed_transform, &shape->unk10, &scale, ray, ray + 1);
    vu0_store_vf10(&gap);

    if (!(gap.w <= 0.0f))
    {
        vu0_restore_vf1_vf5(saved);
        return 0;
    }

    s32 index = shape->unk0e;

    if (index >= 0)
    {
        D_001B6574 = transform;

        if (!(D_001B6288 & shape->unk08[0]))
        {
            vu0_restore_vf1_vf5(saved);
            return 0;
        }

        FieldShapeRecord20* record = &D_001B656C[index];

        for (;;)
        {
            if (ray_hits_record(record, ray))
            {
                D_0050CB30.unk04 = shape;
                D_0050CB30.unk00 = 3;
                D_0050CB30.unk0c = record;
                D_0050CB30.unk24 = ray;
                D_0050CB30.unk14 = D_001B6574;
                return 1;
            }

            if (record->unk0c.unk00_5)
            {
                break;
            }

            record++;
        }
    }

    FieldShapeOwner18* child = shape->unk00;

    if (child == 0)
    {
        vu0_restore_vf1_vf5(saved);
        return 0;
    }

    for (;;)
    {
        if (func_0045CBE0(child, ray))
        {
            return 1;
        }

        if (child->is_last())
        {
            vu0_restore_vf1_vf5(saved);
            return 0;
        }

        child++;
    }
}

/** Select the referenced shape record and run the two argument test. */
s32 func_0045D030(void* object, void* query)
{
    void* descriptor = *(void**)object;
    D_001B656C = (struct FieldShapeRecord20*)*(void**)((u8*)descriptor + 0xC);
    return func_0045CBE0((FieldShapeOwner18*)((u8*)descriptor + 0x30), (const LibVector4*)query);
}

/**
 * @brief Test whether a sphere touches a collision record; boxes are tested in the camera transform's space.
 * @param shape Record to test.
 * @param sphere Aligned sphere, moved by vf5-vf8 and scaled by vf9.y.
 * @param matrix Matrix already in vf5-vf8; unused.
 * @return Whether the record is enabled and touches the sphere.
 */
extern "C" bool func_0045D060(FieldShapeRecord20* shape, const LibVector4* sphere, const void* matrix)
{
    if (shape->unk0c.unk00_4)
    {
        return false;
    }

    switch (shape->unk0c.unk00_0_3)
    {
    case LIB_SHAPE_KIND_BOX:
        if (!D_001B6574->unk20e_2)
        {
            // TODO: only two quadwords are saved, but the frame only matches with room for four.
            LibVector4 registers[4];

            vu0_save_vf6_vf8(registers);
            func_004D9E70(D_001B6574);
            vu0_restore_vf6_vf8(registers);
        }

        return func_0045E240((const LibVector4*)&shape->unk10, shape, sphere, 1, &D_001B6574->inverse_transform);
    case LIB_SHAPE_KIND_SPHERE:
        return func_0045E980((const LibVector4*)&shape->unk10, sphere);
    default:
        return false;
    }
}

/** Matrix of the sphere in the last hit func_0045D140 recorded, in its first word. */
extern "C" const void* D_0050CB80[];

/**
 * @brief Test a sphere against a shape, its records and its children, recording the first record it touches.
 *
 * The shape's bounding sphere is checked first, with the shape's transform in vf1-vf4 and the sphere's matrix in
 * vf5-vf8. The caller's vf1-vf9 come back only when nothing is hit.
 * @param shape Shape to test.
 * @param sphere Aligned sphere: centre in xyz, radius in w.
 * @param matrix Aligned matrix that moves the sphere.
 * @param scale Scale of the sphere's radius.
 * @return One when a record touches the sphere, otherwise zero.
 */
s32 func_0045D140(FieldShapeOwner18* shape, const LibVector4* sphere, const void* matrix, float scale)
{
    if (!(D_001B6288 & shape->unk08[1]))
    {
        return 0;
    }

    LibTransform* transform = (LibTransform*)shape->unk04;

    if (transform == 0)
    {
        return 0;
    }

    LibVector4 saved[12];
    LibVector4 scales;
    LibVector4 gap;

    vu0_save_vf1_vf9(saved);

    if (!transform->matrix_ready)
    {
        transform->update_transform_matrix();
    }

    refresh_shape_transpose(transform);

    refresh_shape_scale(transform);

    scales.x = transform->unk204;
    scales.y = scale;
    vu0_sphere_sphere_gap_with(&shape->unk10, &scales, &transform->transposed_transform, sphere, matrix);
    vu0_store_vf12(&gap);

    if (!(gap.x <= 0.0f))
    {
        vu0_restore_vf1_vf9(saved);
        return 0;
    }

    s32 index = shape->unk0e;

    if (index >= 0)
    {
        D_001B6574 = transform;

        if (!(D_001B6288 & shape->unk08[0]))
        {
            vu0_restore_vf1_vf9(saved);
            return 0;
        }

        FieldShapeRecord20* record = &D_001B656C[index];

        for (;;)
        {
            if (func_0045D060(record, sphere, matrix))
            {
                D_0050CB30.unk04 = shape;
                D_0050CB30.unk00 = 2;
                D_0050CB30.unk0c = record;
                D_0050CB30.unk20 = sphere;
                D_0050CB80[0] = matrix;
                D_0050CB30.unk14 = D_001B6574;
                return 1;
            }

            if (record->unk0c.unk00_5)
            {
                break;
            }

            record++;
        }
    }

    FieldShapeOwner18* child = shape->unk00;

    if (child == 0)
    {
        vu0_restore_vf1_vf9(saved);
        return 0;
    }

    for (;;)
    {
        if (func_0045D140(child, sphere, matrix, scale))
        {
            return 1;
        }

        if (child->is_last())
        {
            vu0_restore_vf1_vf9(saved);
            return 0;
        }

        child++;
    }
}

/** Select the referenced shape record and run the four argument test. */
s32 func_0045D590(void* object, const LibVector4* sphere, const void* matrix, float scale)
{
    void* descriptor = *(void**)object;
    D_001B656C = (struct FieldShapeRecord20*)*(void**)((u8*)descriptor + 0xC);
    return func_0045D140((FieldShapeOwner18*)((u8*)descriptor + 0x30), sphere, matrix, scale);
}

/**
 * @brief Test whether a box touches a collision record.
 * @param record Record to test, moved by vf1-vf4.
 * @param box Aligned box block: its centre at index 2, its half extents at index 3.
 * @param inverse Aligned inverse of the box's matrix.
 * @return Whether the record is enabled and touches the box.
 */
static inline bool box_hits_record(FieldShapeRecord20* record, const LibVector4* box, const void* inverse)
{
    if (record->unk0c.unk00_4)
    {
        return false;
    }

    switch (record->unk0c.unk00_0_3)
    {
    case LIB_SHAPE_KIND_BOX:
    {
        const LibVector4* box_extents = box + 3;
        const LibVector4* box_centre = box + 2;
        return func_0045E400((const LibVector4*)&record->unk10, record, box_centre, box_extents);
    }
    case LIB_SHAPE_KIND_SPHERE:
    {
        const LibVector4* sphere = (const LibVector4*)&record->unk10;
        const LibVector4* box_extents = box + 3;
        const LibVector4* box_centre = box + 2;
        return func_0045E240(box_centre, box_extents, sphere, 0, inverse);
    }
    default:
        return false;
    }
}

/**
 * @brief Test a box against a shape, its records and its children, recording the first record it touches.
 *
 * The shape's bounding sphere is checked against the box's first, with the shape's transform in vf1-vf4 and the
 * box's matrix in vf5-vf8. The caller's vf1-vf9 come back only when nothing is hit.
 * @param shape Shape to test.
 * @param box Aligned box block: its bounding sphere (centred on the box) at index 2, its half extents at index 3.
 * @param matrix Aligned matrix that moves the box.
 * @param inverse Aligned inverse of the box's matrix.
 * @param scale Scale of the box.
 * @return One when a record touches the box, otherwise zero.
 */
s32 func_0045D5C0(FieldShapeOwner18* shape, const LibVector4* box, const void* matrix, const void* inverse,
                  float scale)
{
    if (!(D_001B6288 & shape->unk08[1]))
    {
        return 0;
    }

    LibTransform* transform = (LibTransform*)shape->unk04;

    if (transform == 0)
    {
        return 0;
    }

    LibVector4 saved[12];
    LibVector4 scales;
    LibVector4 gap;

    vu0_save_vf1_vf9(saved);

    if (!transform->matrix_ready)
    {
        transform->update_transform_matrix();
    }

    refresh_shape_transpose(transform);
    refresh_shape_scale(transform);
    scales.x = transform->unk204;
    scales.y = scale;
    vu0_sphere_sphere_gap_with(&shape->unk10, &scales, &transform->transposed_transform, box + 2, matrix);
    vu0_store_vf12(&gap);

    if (!(gap.x <= 0.0f))
    {
        vu0_restore_vf1_vf9(saved);
        return 0;
    }

    s32 index = shape->unk0e;

    if (index >= 0)
    {
        D_001B6574 = transform;

        if (!(D_001B6288 & shape->unk08[0]))
        {
            vu0_restore_vf1_vf9(saved);
            return 0;
        }

        FieldShapeRecord20* record = &D_001B656C[index];

        for (;;)
        {
            if (box_hits_record(record, box, inverse))
            {
                D_0050CB30.unk04 = shape;
                D_0050CB30.unk0c = record;
                D_0050CB30.unk1c = box;
                D_0050CB80[0] = matrix;
                D_0050CB30.unk00 = 1;
                D_0050CB30.unk14 = D_001B6574;
                return 1;
            }

            if (record->unk0c.unk00_5)
            {
                break;
            }

            record++;
        }
    }

    FieldShapeOwner18* child = shape->unk00;

    if (child == 0)
    {
        vu0_restore_vf1_vf9(saved);
        return 0;
    }

    for (;;)
    {
        if (func_0045D5C0(child, box, matrix, inverse, scale))
        {
            return 1;
        }

        if (child->is_last())
        {
            vu0_restore_vf1_vf9(saved);
            return 0;
        }

        child++;
    }
}

/** Select the referenced shape record and run the five argument test. */
s32 func_0045DA90(void* object, const LibVector4* box, const void* matrix, const void* inverse, float scale)
{
    void* descriptor = *(void**)object;
    D_001B656C = (struct FieldShapeRecord20*)*(void**)((u8*)descriptor + 0xC);
    return func_0045D5C0((FieldShapeOwner18*)((u8*)descriptor + 0x30), box, matrix, inverse, scale);
}

/**
 * @brief Bring a shape transform's matrices up to date and copy out its transpose and inverse.
 * @param transform Shape transform.
 * @param transposed Receives the transpose of the base matrix.
 * @param inverse Receives the inverse matrix.
 * @return The transform's largest axis scale.
 */
extern "C" float func_0045DAC0(LibTransform* transform, LibMatrix44Value* transposed, LibMatrix44Value* inverse)
{
    if (!transform->matrix_ready)
    {
        transform->update_transform_matrix();
    }

    refresh_shape_transpose(transform);
    *transposed = transform->transposed_transform;

    if (!transform->unk20e_2)
    {
        func_004D9E70(transform);
    }

    *inverse = transform->inverse_transform;
    refresh_shape_scale(transform);
    return transform->unk204;
}

/**
 * @brief Work out where the last recorded hit touched.
 *
 * Ray hits are clipped again and segment hits use the recorded fractions; other hits take, on each axis, the middle
 * of the overlap between the two shapes' moved boxes.
 * @param points Receives the contact points.
 * @return How many points were stored.
 */
extern "C" s32 func_0045DCC0(LibVector4* points)
{
    FieldShapeRecord20* first = (FieldShapeRecord20*)D_0050CB30.unk0c;
    FieldShapeRecord20* second = (FieldShapeRecord20*)D_0050CB30.unk10;
    FieldShapeRecordInfo& first_info = first->unk0c;
    FieldShapeRecordInfo& second_info = second->unk0c;

    if (D_0050CB30.unk00 == 3)
    {
        switch (first_info.unk00_0_3)
        {
        case LIB_SHAPE_KIND_BOX:
            return func_0045C420((const LibVector4*)&first->unk10, (const float*)first,
                                 (const LibVector4*)D_0050CB30.unk24, points);
        case LIB_SHAPE_KIND_SPHERE:
            return func_0045C770((const LibVector4*)&first->unk10, (const LibVector4*)D_0050CB30.unk24, points);
        }
    }
    else if (D_0050CB30.unk00 == 4)
    {
        *(FieldVec4B*)points = *(const FieldVec4B*)D_0050CB30.unk28;
        return 1;
    }
    else if (D_0050CB30.unk00 == 5)
    {
        s32 count = 0;

        const float* fractions = D_0050CB70;
        const void* start = D_0050CB30.unk2c;
        const void* end = D_0050CB30.unk30;
        vu0_segment_load(fractions, start, end);

        if ((!(D_0050CB70[0] <= 0.0f) && D_0050CB70[0] < 1.0f) ||
            (D_0050CB70[0] <= 0.0f && !(D_0050CB70[1] < 1.0f)) || (!(D_0050CB70[0] < 1.0f) && D_0050CB70[1] <= 0.0f))
        {
            vu0_segment_point_x();
            vu0_store_vf16(&points[count]);
            count++;
        }

        if ((!(D_0050CB70[1] <= 0.0f) && D_0050CB70[1] < 1.0f) ||
            (D_0050CB70[0] <= 0.0f && !(D_0050CB70[1] < 1.0f)) || (!(D_0050CB70[0] < 1.0f) && D_0050CB70[1] <= 0.0f))
        {
            vu0_segment_point_y();
            vu0_store_vf16(&points[count]);
            count++;
        }

        return count;
    }

    FieldVec4B first_extents;
    FieldVec4B second_extents;
    LibVector4 first_centre;
    LibVector4 second_centre;
    LibVector4 first_size;
    LibVector4 second_size;
    const void* second_matrix;
    const void* second_position;

    switch (first_info.unk00_0_3)
    {
    case LIB_SHAPE_KIND_BOX:
        first_extents = *(const FieldVec4B*)first;
        break;
    case LIB_SHAPE_KIND_SPHERE:
    {
        float radius = first->unk00;
        first_extents.x = radius;
        first_extents.y = radius;
        first_extents.z = radius;
        break;
    }
    }

    switch (D_0050CB30.unk00)
    {
    case 0:
    {
        second_position = &second->unk10;
        LibTransform* second_transform = static_cast<LibTransform*>(D_0050CB30.unk18);
        second_matrix = &second_transform->transposed_transform;

        switch (second_info.unk00_0_3)
        {
        case LIB_SHAPE_KIND_BOX:
            second_extents = *(const FieldVec4B*)second;
            break;
        case LIB_SHAPE_KIND_SPHERE:
        {
            float radius = second->unk00;
            second_extents.x = radius;
            second_extents.y = radius;
            second_extents.z = radius;
            break;
        }
        }

        break;
    }
    case 1:
    {
        const LibVector4* box = (const LibVector4*)D_0050CB30.unk1c;
        second_position = box + 2;
        second_extents = *(const FieldVec4B*)(box + 3);
        second_matrix = D_0050CB80[0];
        break;
    }
    case 2:
    {
        const LibVector4* sphere = (const LibVector4*)D_0050CB30.unk20;
        second_extents.x = sphere->w;
        second_extents.y = sphere->w;
        second_extents.z = sphere->w;
        second_position = sphere;
        second_matrix = D_0050CB80[0];
        break;
    }
    }

    vu0_move_box_pair(&first_extents, &second_extents, &first->unk10,
                      &static_cast<LibTransform*>(D_0050CB30.unk14)->transposed_transform, second_position,
                      second_matrix);
    vu0_store_box_pair(&first_centre, &second_centre, &first_size, &second_size);

    if (first_centre.x < second_centre.x)
    {
        points->x = 0.5f * ((second_centre.x - second_size.x) + (first_centre.x + first_size.x));
    }
    else
    {
        points->x = 0.5f * ((second_centre.x + second_size.x) + (first_centre.x - first_size.x));
    }

    if (first_centre.y < second_centre.y)
    {
        points->y = 0.5f * ((second_centre.y - second_size.y) + (first_centre.y + first_size.y));
    }
    else
    {
        points->y = 0.5f * ((second_centre.y + second_size.y) + (first_centre.y - first_size.y));
    }

    if (first_centre.z < second_centre.z)
    {
        points->z = 0.5f * ((second_centre.z - second_size.z) + (first_centre.z + first_size.z));
    }
    else
    {
        points->z = 0.5f * ((second_centre.z + second_size.z) + (first_centre.z - first_size.z));
    }

    return 1;
}

/**
 * @brief Test whether a sphere, moved by vf1-vf4 or vf5-vf8, overlaps a box moved by a matrix.
 * @param centre Box centre.
 * @param half_extents Aligned half extents in xyz.
 * @param sphere Aligned sphere: centre in xyz, radius in w.
 * @param second Non-zero to move the sphere by vf5-vf8 and scale it by vf9.y rather than vf1-vf4 and vf9.x.
 * @param matrix Aligned matrix that moves the sphere into the box's space.
 * @return Whether they overlap.
 */
bool func_0045E240(const LibVector4* centre, const void* half_extents, const LibVector4* sphere, s32 second,
                   const void* matrix)
{
    LibVector4 local;
    LibVector4 smallest;
    LibVector4 largest;

    vu0_load_vf16_vf19(matrix);
    vu0_load_vf13(sphere);

    if (second)
    {
        vu0_move_vf13_by_vf5();
        vu0_scale_vf13_radius_y();
    }
    else
    {
        vu0_move_vf13_by_vf1();
        vu0_scale_vf13_radius_x();
    }

    vu0_sphere_into_box_space();
    vu0_store_vf14(&local);
    vu0_load_vf15(centre);
    vu0_load_vf16(half_extents);

    if (second)
    {
        vu0_scale_vf16_x();
    }
    else
    {
        vu0_scale_vf16_y();
    }

    vu0_box_corners();
    float distance = 0.0f;
    vu0_store_box_corners(&largest, &smallest);

    if (local.x < smallest.x)
    {
        float delta = local.x - smallest.x;
        distance += delta * delta;
    }
    else if (!(local.x <= largest.x))
    {
        float delta = local.x - largest.x;
        distance += delta * delta;
    }

    if (local.y < smallest.y)
    {
        float delta = local.y - smallest.y;
        distance += delta * delta;
    }
    else if (!(local.y <= largest.y))
    {
        float delta = local.y - largest.y;
        distance += delta * delta;
    }

    if (local.z < smallest.z)
    {
        float delta = local.z - smallest.z;
        distance += delta * delta;
    }
    else if (!(local.z <= largest.z))
    {
        float delta = local.z - largest.z;
        distance += delta * delta;
    }

    return distance <= local.w;
}

/**
 * @brief Test whether two boxes, moved by the matrices in vf1-vf4 and vf5-vf8 and scaled by vf9.x and vf9.y,
 *        overlap, by their fifteen separating axes.
 * @param first_centre First box centre.
 * @param first_half_extents Aligned half extents of the first box in xyz.
 * @param second_centre Second box centre.
 * @param second_half_extents Aligned half extents of the second box in xyz.
 * @return Whether no axis separates them.
 */
bool func_0045E400(const LibVector4* first_centre, const void* first_half_extents, const LibVector4* second_centre,
                   const void* second_half_extents)
{
    LibVector4 distance;
    LibVector4 extent;

    vu0_box_box_axis_1(first_centre, first_half_extents, second_centre, second_half_extents);
    vu0_store_box_box_axis(&distance, &extent);

    if (!(distance.x <= extent.x))
    {
        return false;
    }

    vu0_box_box_axis_2();
    vu0_store_box_box_axis(&distance, &extent);

    if (!(distance.y <= extent.y))
    {
        return false;
    }

    vu0_box_box_axis_3();
    vu0_store_box_box_axis(&distance, &extent);

    if (!(distance.z <= extent.z))
    {
        return false;
    }

    vu0_box_box_axis_4();
    vu0_store_box_box_axis(&distance, &extent);

    if (!(distance.x <= extent.x) || !(distance.y <= extent.y) || !(distance.z <= extent.z))
    {
        return false;
    }

    vu0_box_box_axis_5();
    vu0_store_box_box_axis(&distance, &extent);

    if (!(distance.x <= extent.x))
    {
        return false;
    }

    vu0_box_box_axis_6();
    vu0_store_box_box_axis(&distance, &extent);

    if (!(distance.y <= extent.y))
    {
        return false;
    }

    vu0_box_box_axis_7();
    vu0_store_box_box_axis(&distance, &extent);

    if (!(distance.z <= extent.z))
    {
        return false;
    }

    vu0_box_box_axis_8();
    vu0_store_box_box_axis(&distance, &extent);

    if (!(distance.x <= extent.x))
    {
        return false;
    }

    vu0_box_box_axis_9();
    vu0_store_box_box_axis(&distance, &extent);

    if (!(distance.y <= extent.y))
    {
        return false;
    }

    vu0_box_box_axis_10();
    vu0_store_box_box_axis(&distance, &extent);

    if (!(distance.z <= extent.z))
    {
        return false;
    }

    vu0_box_box_axis_11();
    vu0_store_box_box_axis(&distance, &extent);

    if (!(distance.x <= extent.x))
    {
        return false;
    }

    vu0_box_box_axis_12();
    vu0_store_box_box_axis(&distance, &extent);

    if (!(distance.y <= extent.y))
    {
        return false;
    }

    vu0_box_box_axis_13();
    vu0_store_box_box_axis(&distance, &extent);

    if (!(distance.z <= extent.z))
    {
        return false;
    }

    return true;
}

/**
 * @brief Test whether two spheres, moved by the matrices in vf1-vf4 and vf5-vf8 and scaled by vf9.x and vf9.y, touch.
 * @param first First sphere: centre in xyz, radius in w.
 * @param second Second sphere.
 * @return Whether they overlap or touch.
 */
extern "C" bool func_0045E980(const LibVector4* first, const LibVector4* second)
{
    LibVector4 gap;

    vu0_sphere_sphere_gap(first, second);
    vu0_store_vf11(&gap);

    if (!(gap.x <= 0.0f))
    {
        return false;
    }

    return true;
}

/** Transform of the second shape in a two-shape test. */
extern "C" LibTransform* D_001B6578;

/**
 * @brief Test whether two collision records touch; boxes are tested in their owners' transform space.
 * @param first First record, moved by vf1-vf4 and scaled by vf9.x.
 * @param second Second record, moved by vf5-vf8 and scaled by vf9.y.
 * @return Whether both records are enabled and touch.
 */
extern "C" bool func_0045EA10(FieldShapeRecord20* first, FieldShapeRecord20* second)
{
    FieldShapeRecordInfo& first_info = first->unk0c;
    FieldShapeRecordInfo& second_info = second->unk0c;

    if (first_info.unk00_4 || second_info.unk00_4)
    {
        return false;
    }

    switch (first_info.unk00_0_3)
    {
    case LIB_SHAPE_KIND_BOX:
        switch (second_info.unk00_0_3)
        {
        case LIB_SHAPE_KIND_BOX:
        {
            const LibVector4* second_centre = (const LibVector4*)&second->unk10;
            const LibVector4* first_centre = (const LibVector4*)&first->unk10;
            return func_0045E400(first_centre, first, second_centre, second);
        }
        case LIB_SHAPE_KIND_SPHERE:
            if (!D_001B6574->unk20e_2)
            {
                // TODO: only two quadwords are saved, but the frame only matches with room for four.
                LibVector4 registers[4];

                vu0_save_vf6_vf8(registers);
                func_004D9E70(D_001B6574);
                vu0_restore_vf6_vf8(registers);
            }

            return func_0045E240((const LibVector4*)&first->unk10, first, (const LibVector4*)&second->unk10, 1,
                                 &D_001B6574->inverse_transform);
        }

        break;
    case LIB_SHAPE_KIND_SPHERE:
        switch (second_info.unk00_0_3)
        {
        case LIB_SHAPE_KIND_BOX:
            if (!D_001B6578->unk20e_2)
            {
                LibVector4 registers[4];

                vu0_save_vf6_vf8(registers);
                func_004D9E70(D_001B6578);
                vu0_restore_vf6_vf8(registers);
            }

            return func_0045E240((const LibVector4*)&second->unk10, second, (const LibVector4*)&first->unk10, 0,
                                 &D_001B6578->inverse_transform);
        case LIB_SHAPE_KIND_SPHERE:
        {
            const LibVector4* second_sphere = (const LibVector4*)&second->unk10;
            const LibVector4* first_sphere = (const LibVector4*)&first->unk10;
            return func_0045E980(first_sphere, second_sphere);
        }
        }

        break;
    }

    return false;
}

/** Shape mask of the second shape in a two-shape test. */
extern "C" u8 D_001B628C;

/**
 * @brief Test two shapes, their records and their children against each other, recording the first touching pair.
 *
 * The bounding spheres are checked first, with the first shape's transform in vf1-vf4 and the second's in vf5-vf8.
 * The caller's vf1-vf9 come back only when nothing is hit.
 * @param first First shape.
 * @param second Second shape.
 * @return One when a pair of records touch, otherwise zero.
 */
s32 func_0045EBD0(FieldShapeOwner18* first, FieldShapeOwner18* second)
{
    if (!(D_001B6288 & first->unk08[1]) || !(D_001B628C & second->unk08[1]))
    {
        return 0;
    }

    LibTransform* first_transform = (LibTransform*)first->unk04;
    LibTransform* second_transform = (LibTransform*)second->unk04;

    if (first_transform == 0)
    {
        return 0;
    }

    if (second_transform == 0)
    {
        return 0;
    }

    LibVector4 saved[12];
    LibVector4 scales;
    LibVector4 gap;

    vu0_save_vf1_vf9(saved);

    if (!first_transform->matrix_ready)
    {
        first_transform->update_transform_matrix();
    }

    if (!second_transform->matrix_ready)
    {
        second_transform->update_transform_matrix();
    }

    refresh_shape_transpose(first_transform);
    refresh_shape_transpose(second_transform);
    refresh_shape_scale(first_transform);
    refresh_shape_scale(second_transform);

    scales.x = first_transform->unk204;
    scales.y = second_transform->unk204;
    vu0_sphere_sphere_gap_with(&first->unk10, &scales, &first_transform->transposed_transform, &second->unk10,
                               &second_transform->transposed_transform);
    vu0_store_vf12(&gap);

    if (!(gap.x <= 0.0f))
    {
        vu0_restore_vf1_vf9(saved);
        return 0;
    }

    s32 first_index = first->unk0e;
    s16 second_index = second->unk0e;

    if (first_index >= 0 && second_index >= 0)
    {
        D_001B6574 = first_transform;
        D_001B6578 = second_transform;

        if (!(D_001B6288 & first->unk08[0]) || !(D_001B628C & second->unk08[0]))
        {
            vu0_restore_vf1_vf9(saved);
            return 0;
        }

        FieldShapeRecord20* first_record = &D_001B656C[first_index];

        for (;;)
        {
            FieldShapeRecord20* second_record = &D_001B6570[second_index];

            for (;;)
            {
                if (func_0045EA10(first_record, second_record))
                {
                    D_0050CB30.unk04 = first;
                    D_0050CB30.unk08 = second;
                    D_0050CB30.unk0c = first_record;
                    D_0050CB30.unk10 = second_record;
                    D_0050CB30.unk00 = 0;
                    D_0050CB30.unk14 = D_001B6574;
                    D_0050CB30.unk18 = D_001B6578;
                    return 1;
                }

                if (second_record->unk0c.unk00_5)
                {
                    break;
                }

                second_record++;
            }

            if (first_record->unk0c.unk00_5)
            {
                break;
            }

            first_record++;
        }
    }

    FieldShapeOwner18* first_child = first->unk00;
    FieldShapeOwner18* second_child = second->unk00;

    if (first_child != 0 && second_child != 0)
    {
        for (;;)
        {
            if (func_0045EBD0(first, second_child))
            {
                return 1;
            }

            if (second_child->is_last())
            {
                break;
            }

            second_child++;
        }

        for (;;)
        {
            if (func_0045EBD0(first_child, second))
            {
                return 1;
            }

            if (first_child->is_last())
            {
                break;
            }

            first_child++;
        }
    }
    else if (first_child != 0)
    {
        for (;;)
        {
            if (func_0045EBD0(first_child, second))
            {
                return 1;
            }

            if (first_child->is_last())
            {
                break;
            }

            first_child++;
        }
    }
    else if (second_child != 0)
    {
        for (;;)
        {
            if (func_0045EBD0(first, second_child))
            {
                return 1;
            }

            if (second_child->is_last())
            {
                break;
            }

            second_child++;
        }
    }

    vu0_restore_vf1_vf9(saved);
    return 0;
}

/**
 * @brief Test whether a transform's transpose of its combined matrix is current.
 * @param transform Transform.
 * @return Whether the transpose is current.
 */
static inline bool transform_transpose_current(const LibTransform* transform)
{
    return transform->unk20e_0;
}

/**
 * @brief Rebuild a transform's transpose of its combined matrix unless it is current.
 * @param transform Transform.
 */
static inline void refresh_transform_transpose(LibTransform* transform)
{
    if (!transform_transpose_current(transform))
    {
        transform->unk20e_0 = 1;
        transform->unk20e_1 = 0;
        ee_transpose_matrix(&transform->transposed_transform, &transform->transform);
    }
}

/**
 * @brief Load two shapes' matrices into vf1-vf4 and vf5-vf8 and their largest axis scales into vf9.
 * @param first First shape.
 * @param second Second shape.
 */
extern "C" void func_0045F2B0(FieldShapeOwner18* first, FieldShapeOwner18* second)
{
    LibTransform* first_transform = (LibTransform*)first->unk04;
    LibTransform* second_transform = (LibTransform*)second->unk04;

    if (first_transform != 0 && second_transform != 0)
    {
        LibVector4 scales;

        if (!first_transform->matrix_ready)
        {
            first_transform->update_transform_matrix();
        }

        if (!second_transform->matrix_ready)
        {
            second_transform->update_transform_matrix();
        }

        refresh_transform_transpose(first_transform);
        refresh_transform_transpose(second_transform);
        refresh_shape_scale(first_transform);
        refresh_shape_scale(second_transform);
        scales.x = first_transform->unk204;
        scales.y = second_transform->unk204;
        vu0_load_shape_pair(&first_transform->transposed_transform, &second_transform->transposed_transform, &scales);
    }
}

/**
 * @brief Publish the two bound shape record arrays for subsequent predicates.
 * @param first First shape resource storage.
 * @param second Second shape resource storage.
 */
void func_0045F580(void* first, void* second)
{
    D_001B656C = (struct FieldShapeRecord20*)*(void**)(*(u8**)first + 0xC);
    D_001B6570 = (struct FieldShapeRecord20*)*(void**)(*(u8**)second + 0xC);
}

/**
 * @brief Run func_0045EBD0 on the objects referenced by the first words of two objects.
 *
 * The word at offset 0xC of each referenced object is stored in a global first.
 * @param object Object whose first word refers to the first tested object.
 * @param other Object whose first word refers to the second tested object.
 * @return The func_0045EBD0 result.
 */
s32 func_0045F5A0(void* object, void* other)
{
    u8* first = *(u8**)object;
    u8* second = *(u8**)other + 0x30;
    D_001B656C = (struct FieldShapeRecord20*)*(void**)(first + 0xC);
    D_001B6570 = (struct FieldShapeRecord20*)*(void**)(*(u8**)other + 0xC);
    return func_0045EBD0((FieldShapeOwner18*)(first + 0x30), (FieldShapeOwner18*)second);
}

/** Matrix func_0045F5E0 resets. */
extern "C" LibMatrix44Value D_0050CAF0;

/** @brief Reset D_0050CAF0 to the identity matrix. */
extern "C" void func_0045F5E0()
{
    D_0050CAF0.set_identity();
}

void func_0045F600(void* object)
{
}

void func_0045F610(void* object)
{
}

void func_0045F620(void* object)
{
}

void func_0045F630(void* object)
{
}

void func_0045F640(void* object)
{
}

void func_0045F650(void* object)
{
}

extern "C" s32 func_00451B90(s32 code);

/**
 * @brief Run func_00451B90 on the value at offset 0x564 when the byte at 0x57A is set.
 * @return The func_00451B90 result, or zero.
 */
s32 LibObject174D90::func_0045F660()
{
    s32 result = 0;

    if (unk57a)
    {
        result = func_00451B90(unk564);
    }

    return result;
}

extern "C" void lib_multiline_text_set_resource(LibObject174D90* object, u32 source, s32 key, u32 mode, u32 flag)
{
    LibMultilineResourceState* state = (LibMultilineResourceState*)object;
    state->source = source;
    state->key = key;
    state->mode = mode;
    state->flag = flag;
    state->pending = 1;
    state->redraw = 1;
}

/** @brief Draw the laid-out records once, then finish the text widget's drawing. */
void LibObject174D90::draw()
{
    if (!unk3b)
    {
        s32 count = (u32)(unk74 - unk70) / sizeof(LibDrawRecord);

        if (count > 0)
        {
            draw_records(reinterpret_cast<LibDrawRecord*>(unk70), count);
            func_004C7010();
            unk3b = 1;
        }
    }
}

extern "C" s32 func_004614E0(LibObject174D90* object, s32 slot, s32 key, u32 mode, u8 flag);

extern "C" void func_00460750(LibObject174D90* object);

extern "C" bool func_004C71E0(LibTextWidget* object);

/**
 * @brief Run the text one frame: finish a pending resource load, track the advance button, run the current wait or
 *        scroll, then read records and their control codes until one starts a new wait.
 */
void LibObject174D90::func_00413D20()
{
    if (pending && func_004614E0(this, source, key, resource_mode, flag) == 0)
    {
        return;
    }

    func_004C71E0(this);
    FieldRuntime* runtime = g_field_runtime;
    u16 confirm = runtime->button_map->buttons[0] | runtime->button_map->buttons[1];
    u16 held = runtime->inputs[pad_index].unk00;
    u16 pressed = runtime->inputs[pad_index].unk02;

    switch (unk568)
    {
    case 0:
        unk577 = 0;
        unk570 = 0.0f;
        unk56c = 0;
        unk568++;
    case 1:
        if (pressed & confirm)
        {
            if (!(mode & 0x20) && unk570 < 12.0f && unk56c > 0)
            {
                unk577 = 1;
            }

            unk56c++;
            unk570 = 0.0f;
            unk568++;
        }

        break;
    case 2:
        if (!(held & confirm))
        {
            unk577 = 0;
            unk570 = 0.0f;
            unk568--;
        }

        break;
    }

    unk570 += field_rate(g_field_runtime);

    switch (unk550)
    {
    case 5:
        unk548 = 0;
        func_00460750(this);
        unk74 = unk70;
        line_index = 0;
        unk564 = 0;
        line_bottom = line_heights[0];
        unk7c = 0.0f;
        unk550 = 0;
        func_0045F600();
        break;
    case 1:
    {
        // TODO: Written this way round for the target's movn into the pressed register.
        pressed = unk55c == 0 ? pressed : held;

        if ((mode & 0x21) || unk575 || !(pressed & confirm))
        {
            wait_time -= field_rate(g_field_runtime);
        }
        else
        {
            wait_time = 0.0f;
        }

        if (wait_time <= 0.0f)
        {
            if (!unk55c)
            {
                unk577 = 0;
            }

            unk550 = 0;
        }

        break;
    }
    case 3:
        if (pressed & confirm)
        {
            LibClass175170* box = unk114;

            if (box)
            {
                box->unk88c = 1;
                box->unk890 = 1;
            }

            unk577 = 0;
            unk550 = 0;
        }

        break;
    case 2:
    {
        float step = scroll_speed * field_rate(g_field_runtime);

        if (unk577)
        {
            step *= 2.0f;
        }

        unk7c += step;

        if (!(unk7c < scroll_target))
        {
            unk7c = scroll_target;
            unk550 = 0;
        }

        break;
    }
    case 4:
        if (!unk579)
        {
            LibClass175170* box = unk114;

            if (box)
            {
                box->unk88c = 1;
                box->unk890 = 1;
            }

            unk577 = 0;
            unk550 = 0;
        }

        break;
    }

    if (unk550 != 0)
    {
        goto done;
    }

    for (;;)
    {
        u8 fast = (mode & 1) || unk575;
        LibDrawRecord* record = reinterpret_cast<LibDrawRecord*>(unk74);
        // TODO: The game sign-extends the code to 64 bits before testing it; this cast is the only spelling I've found.
        s32 end = record->code;

        if ((s64)end == 0)
        {
            unk564 = 0;
            unk550 = -1;
            func_0045F610();
            goto done;
        }

        unk74 = reinterpret_cast<u8*>(record + 1);
        u16 code = record->code;

        if (code & 0x4000)
        {
            switch (code)
            {
            case 0x4000:
            {
                func_00460750(this);

                if (++line_index >= 0x100)
                {
                    continue;
                }

                line_bottom += line_heights[line_index];
                float overflow = line_bottom - unk7c - unk18.unk0c;

                if (overflow <= 0.0f)
                {
                    continue;
                }

                scroll_target = unk7c + overflow;
                scroll_speed = overflow / 10.0;
                unk550 = 2;
                goto done;
            }
            case 0x4001:
                unk118 = record->unk10;
                unk568 = 0;
                unk550 = 5;
                goto done;
            case 0x4004:
                if (!fast)
                {
                    unk564 = 0;

                    LibClass175170* box = unk114;

                    if (box)
                    {
                        box->unk88c = 0;
                        box->unk890 = 1;
                    }

                    if (!(mode & 2))
                    {
                        unk550 = 3;
                        goto done;
                    }

                    func_0045F650();
                    unk579 = 1;
                    unk550 = 4;
                    goto done;
                }

                wait_time = 60.0f * unk528;
                unk55c = 1;
                unk550 = 1;
                goto done;
            case 0x4005:
                if (mode & 0x10)
                {
                    continue;
                }

                wait_time = 60.0f * record->unk14.scale;
                unk55c = 1;
                unk550 = 1;
                goto done;
            case 0x4006:
                if (mode & 4)
                {
                    continue;
                }

                unk52c = unk524 / 4.0f / 0.05f * (record->unk14.scale / 4.0f);
                continue;
            case 0x4007:
                if (mode & 4)
                {
                    continue;
                }

                unk52c = unk524 / 4.0f;
                continue;
            case 0x4014:
                func_0045F630(record->color);
                continue;
            case 0x4015:
                func_0045F640(record->color);
                unk579 = 1;
                unk550 = 4;
                goto done;
            case 0x4016:
                unk575 = 1;
                continue;
            case 0x4017:
                unk575 = 0;
                continue;
            case 0x401E:
                func_0045F620(record->values[0], record->values[1], record->glyph);
                continue;
            case 0x4020:
                unk57a = record->value;
                continue;
            }
        }
        else
        {
            unk564 = code;

            if (!fast && unk577)
            {
                continue;
            }

            if (unk52c <= 0.0f)
            {
                continue;
            }

            wait_time = 60.0f * unk52c;
            unk55c = 1;
            unk550 = 1;
            goto done;
        }
    }

done:
    needs_redraw = 1;
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
 * @brief Count the glyphs a text lays out, expanding numbers, names and item names, up to its end code.
 * @param widget Widget the text is laid out for.
 * @param source Encoded text.
 * @return Number of glyphs.
 */
extern "C" s32 func_0045FE90(LibDrawWidget* widget, const u8* source)
{
    u16 codes[64];
    s32 count = 0;
    const u8* text = source;

    for (;;)
    {
        s32 c = *text++;

        if (c & 0x80)
        {
            u16 code = (c & 0x7F) | (*text++ << 7);

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
                    text += 4;
                    break;
                case 0x4011:
                    while (*text)
                    {
                        text++;
                    }

                    text++;
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

                    count += func_00463E60(widget, codes, id, variant);
                    break;
                }
                case 0x401C:
                    while (*text)
                    {
                        text++;
                    }

                    text++;
                    count++;
                    break;
                case 0x401D:
                    text++;
                    count++;
                    break;
                case 0x401F:
                    // TODO: A goto out of the switch is what puts the shared count++ block before the return like the game.
                    goto end;
                }

                continue;
            }
        }

        count++;
    }

end:
    return count;
}

/**
 * @brief Work out the extra spacing that spreads a run of draw records to the widget's width.
 * @param widget Widget whose width the run should fill.
 * @param first First record of the run.
 * @param last Last record of the run.
 * @return Extra spacing per glyph record, at most three, or zero when the run already fills the width.
 */
extern "C" float func_004601F0(LibDrawWidget* widget, LibDrawRecord* first, LibDrawRecord* last)
{
    float spacing = 0.0f;
    s32 count = 0;
    float right = 0.0f;

    for (LibDrawRecord* record = first; record <= last; record++)
    {
        if (!(record->code & 0x4000))
        {
            right = record->right;
            count++;
        }
        else if (record->code == 0x401C)
        {
            right = record->right;
        }
    }

    if (right > 0.0f && count > 0)
    {
        float extra = widget->unk18.unk08 - right;

        if (extra > 0.0f)
        {
            spacing = extra / count;

            if (spacing > 3.0f)
            {
                spacing = 3.0f;
            }
        }
    }

    return spacing;
}

/**
 * @brief Find where a laid-out line may break: walk back from the last record while the glyph classes on either side
 *        must stay together.
 * @param object Multiline text widget.
 * @param first First record of the line.
 * @param last Record the line would break at.
 * @return Record to break at.
 */
extern "C" LibDrawRecord* func_004602B0(LibObject174D90* object, LibDrawRecord* first, LibDrawRecord* last)
{
    s32 next = 0;
    bool joined = false;
    s32 count = 0;
    LibDrawRecord* record = last;

    for (;;)
    {
        if (record == first)
        {
            return last;
        }

        s32 kind;
        s32 code = record->code;

        if (code & 0x4000)
        {
            if (code == 0xFFFF)
            {
                kind = 9;
            }
            else if (code == 0x401C)
            {
                kind = 14;
            }
            else if (code == 0x401D)
            {
                kind = 15;
            }
            else
            {
                if (code == 0x4019)
                {
                    break;
                }

                if (code == 0x4018)
                {
                    joined = true;
                }

                goto keep;
            }
        }
        else if (code == 11)
        {
            kind = 0;
        }
        else if (code == 12)
        {
            kind = 1;
        }
        else if (code > 0 && code < 11)
        {
            kind = 2;
        }
        else if (code >= 13 && code < 0x42)
        {
            kind = 3;
        }
        else if (code == 0x42)
        {
            kind = 10;
        }
        else if (code == 0x9D || code == 0x11B)
        {
            kind = 4;
        }
        else if (code >= 0x43 && code < 0x4D)
        {
            kind = 5;
        }
        else if (code >= 0x4D && code < 0x93)
        {
            kind = 6;
        }
        else if (code >= 0x94 && code < 0x9D)
        {
            kind = 7;
        }
        else if (code >= 0x93 && code < 0xE5)
        {
            kind = 8;
        }
        else if (code == 0xE8 || code == 0xE9)
        {
            kind = 9;
        }
        else if (code == 0x102)
        {
            kind = 3;
        }
        else if (code >= 0xEA && code < 0x107)
        {
            kind = 10;
        }
        else if (code >= 0x107 && code < 0x114)
        {
            kind = 11;
        }
        else if (code == 0x114)
        {
            kind = 16;
        }
        else if (code >= 0x114 && code < 0x125)
        {
            kind = 12;
        }
        else
        {
            kind = 13;
        }

        if (count == 0 && kind == 9)
        {
            return record + 1;
        }

        if (count == 0 || kind == 11 || joined)
        {
            next = kind;
            joined = false;
            goto keep;
        }

        if (kind == next)
        {
            if (kind == 6)
            {
                return record + 1;
            }

            goto keep;
        }

        switch (next)
        {
        case 0:
        case 1:
            if (kind == 2 || kind == 3)
            {
                next = kind;
                goto keep;
            }

            break;
        case 2:
            if (kind == 0 || kind == 1)
            {
                next = kind;
                goto keep;
            }

            break;
        case 4:
        case 5:
        case 7:
        case 10:
            next = kind;
            goto keep;
        case 6:
            switch (kind)
            {
            case 4:
            case 5:
                next = kind;
                goto keep;
            case 13:
                if (object->unk558 < 2)
                {
                    break;
                }

                next = kind;
                goto keep;
            }

            break;
        case 8:
            switch (kind)
            {
            case 4:
            case 7:
                next = kind;
                goto keep;
            case 13:
                if (object->unk558 < 2)
                {
                    break;
                }

                next = kind;
                goto keep;
            }

            break;
        case 13:
            if (object->unk558 < 2)
            {
                break;
            }

            if (kind == 2)
            {
                next = kind;
                goto keep;
            }

            if (kind == 6 && (code == 0x51 || code == 0x7E))
            {
                goto keep;
            }

            break;
        case 14:
            next = kind;
            goto keep;
        case 16:
            switch (kind)
            {
            case 1:
            case 3:
                next = kind;
                goto keep;
            }

            break;
        case 3:
            if (kind == 16)
            {
                next = kind;
                goto keep;
            }

            break;
        }

        return record + 1;

    keep:
        count++;
        record--;
    }

    return record;
}

/** A decoded text code in the scratchpad: the code, a count or length, and its argument. */
struct LibTextRecord
{
    u16 code;
    u16 extra;

    union
    {
        u32 value;
        float number;
        const u8* text;
        u8 bytes[4];
    };
};

#define LIB_TEXT_RECORDS reinterpret_cast<LibTextRecord*>(0x70000000)
#define LIB_TEXT_RECORDS_END reinterpret_cast<LibTextRecord*>(0x70000C78)

extern "C" void func_004C7290(LibDrawWidget* widget, const u8* text);

/**
 * @brief Test a one-based allocation ID against the allocation count.
 * @param identifier One-based allocation ID.
 * @return Nonzero when the ID is in range.
 */
static inline s32 allocation_identifier_valid(s16 identifier)
{
    // TODO: Returned as s32 from a bool local, which gives the game's extra andi before the test.
    bool valid = false;

    if (identifier > 0 && identifier <= LIB_ALLOCATION_COUNT)
    {
        valid = true;
    }

    return valid;
}

/**
 * @brief Walk back from a record to the start of its run.
 * @param record Record inside a run.
 * @return The run's LIB_DRAW_RECORD_RUN record.
 */
static inline LibDrawRecord* run_start(LibDrawRecord* record)
{
    for (;;)
    {
        if (record->code == LIB_DRAW_RECORD_RUN)
        {
            break;
        }

        record--;
    }

    return record;
}

/**
 * @brief Decode the next page of text into scratchpad records, then lay them out line by line, wrapping a line
 *        that runs past the widget's width at the start of its run or the break func_004602B0 picks. Up to 12 lines
 *        wrap; each laid-out line's height goes into line_heights.
 * @param object Multiline text widget.
 */
extern "C" void func_00460750(LibObject174D90* object)
{
    u16 codes[64];

    if (object->unk548 < 0)
    {
        return;
    }

    if (object->unk548 == 0)
    {
        if (object->unkfc != 0)
        {
            LibGlyphDraw6C* glyph = static_cast<LibClass178780*>(object->unkfc)->glyphs;

            for (s32 i = 0; i < static_cast<LibClass178780*>(object->unkfc)->glyph_capacity; i++, glyph++)
            {
                lib_draw_state_init(glyph);
            }
        }

        object->text_cursor = static_cast<const u8*>(object->unk118);
        object->record_cursor = reinterpret_cast<LibDrawRecord*>(object->unk70);
        object->pen_y = 0.0f;
        object->line_count = 0;
        object->unk548++;
    }

    lib_restore_texture_cache(static_cast<LibRenderer*>(g_renderer));

    const u8* text = object->text_cursor;
    LibTextRecord* record = LIB_TEXT_RECORDS;

    for (;;)
    {
        u16 code = *text++;

        // TODO: The game compares the code as 64-bit here; I haven't found a cleaner spelling.
        if ((s64)(s32)code == 0)
        {
            record->code = 0;
            goto decoded;
        }

        if (code & 0x80)
        {
            code = (code & 0x7F) | (*text++ << 7);

            if (code & 0x4000)
            {
                switch (code)
                {
                case 0x4002:
                case 0x401A:
                case 0x4020:
                    record->value = *text++;
                    break;
                case 0x4005:
                case 0x4006:
                case 0x400A:
                case 0x400C:
                case 0x400E:
                case 0x4014:
                case 0x4015:
                {
                    u8* bytes = record->bytes;

                    for (s32 i = 0; i < 4; i++)
                    {
                        *bytes++ = *text++;
                    }

                    break;
                }
                case 0x4000:
                    if (object->mode & 8)
                    {
                        continue;
                    }

                    record->code = 0x4000;
                    goto decoded;
                case 0x4001:
                    record->code = 0x4001;
                    record->text = text;
                    goto decoded;
                case 0x4003:
                    record->value = 0;
                    code = 0x4002;
                    break;
                case 0x4008:
                    record->value = object->get_palette_color(*text++);
                    break;
                case 0x4009:
                    record->value = 0x808080;
                    code = 0x4008;
                    break;
                case 0x400B:
                    code = 0x400A;
                    record->number = 1.0f;
                    break;
                case 0x400D:
                    record->value = 0;
                    code = 0x400C;
                    break;
                case 0x400F:
                    code = 0x400E;
                    record->number = 2.0f;
                    break;
                case 0x4011:
                case 0x401C:
                    record->text = text;

                    while (*text)
                    {
                        text++;
                    }

                    record->extra = text - record->text;
                    text++;
                    break;
                case 0x4012:
                {
                    object->format_number_codes(codes, g_field_runtime->message_arguments[*text++]);

                    for (u16* glyph = codes; *glyph; glyph++)
                    {
                        record->code = *glyph;
                        record++;

                        if (record == LIB_TEXT_RECORDS_END)
                        {
                            record->code = 0x4001;
                            record->text = text;
                            goto decoded;
                        }
                    }

                    continue;
                }
                case 0x4013:
                case 0x4021:
                {
                    s32 index = *text++;

                    index = code == 0x4013 ? index : g_field_runtime->message_arguments[index];

                    func_00464040(object, codes, func_004642E0(object, index));
                    u16* glyph = codes;
                    s32 spacer = 0;

                    while (*glyph)
                    {
                        if (!spacer)
                        {
                            record->code = *glyph++;
                        }
                        else
                        {
                            record->code = 0x4018;
                        }

                        record++;

                        if (record == LIB_TEXT_RECORDS_END)
                        {
                            record->code = 0x4001;
                            record->text = text;
                            goto decoded;
                        }

                        spacer ^= 1;
                    }

                    continue;
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
                        ItemCreationAllocationRecord* allocation;

                        if (allocation_identifier_valid(value))
                        {
                            allocation = reinterpret_cast<ItemCreationAllocationRecord*>(&state->allocations[(s16)value - 1]);
                        }
                        else
                        {
                            allocation = 0;
                        }

                        if (allocation != 0 && allocation_in_use(allocation))
                        {
                            u16 stored = allocation->checksum;
                            u16 index;

                            if (stored != allocation->calculate_checksum())
                            {
                                index = 0;
                            }
                            else
                            {
                                index = allocation->definition_factors.bits.definition_index;
                            }

                            id = index + 1;
                            variant = allocation->modification_number;
                        }
                    }

                    func_00463E60(object, codes, id, variant);

                    for (u16* glyph = codes; *glyph; glyph++)
                    {
                        record->code = *glyph;
                        record++;

                        if (record == LIB_TEXT_RECORDS_END)
                        {
                            record->code = 0x4001;
                            record->text = text;
                            goto decoded;
                        }
                    }

                    continue;
                }
                case 0x401B:
                    record->value = object->unk554;
                    code = 0x401A;
                    break;
                case 0x401D:
                    record->text = text;
                    text++;
                    break;
                case 0x401E:
                {
                    u8* bytes = record->bytes;

                    for (s32 i = 0; i < 4; i++)
                    {
                        *bytes++ = *text++;
                    }

                    record->extra = func_0045FE90(object, text);
                    break;
                }
                }
            }
        }

        record->code = code;
        record++;

        if (record == LIB_TEXT_RECORDS_END)
        {
            record->code = 0x4001;
            record->text = text;
            break;
        }
    }

decoded:
    object->text_cursor = text;

    if (record->code != 0x4000)
    {
        object->unk548 = -1;
    }

    // TODO: Declaring source first and assigning it later is what keeps records in s4 and source in s5.
    LibTextRecord* source;
    LibDrawRecord* records = object->record_cursor;
    s32 total = 0;
    s32 lines = 0;
    source = LIB_TEXT_RECORDS;
    bool more = true;

    while (more)
    {
        LibTextRecord* line_start = source;
        s32 align = object->horizontal_align;
        u32 tint = object->tint;
        LibDrawRecord* wrap = 0;
        float scale = object->draw_scale;
        float scale_y = object->draw_scale_y;
        float spacing = object->unk88;
        float leading = object->unk8c;
        object->unk90 = 0.0f;

    retry:
        object->begin_layout(records, object->pen_y);
        u8 going = 1;
        u8 in_run = 0;

        while (going)
        {
            if (!in_run && object->next_record == wrap)
            {
                lines++;
                object->next_record->code = 0x4000;
                object->next_record++;
                object->record_count++;
                break;
            }

            s32 code = source->code;

            if ((s64)code == 0)
            {
                object->next_record->code = 0;
                going = more = 0;
                object->next_record++;
                object->record_count++;
            }
            else if (code < 0x4000 || code == 0x401C || code == 0x401D)
            {
                LibDrawRecord* glyph = object->next_record;
                float pen_x = object->pen_x;

                switch (source->code)
                {
                case 0x401C:
                    object->add_number_record(const_cast<u8*>(source->text), source->extra);
                    break;
                case 0x401D:
                    func_004C7290(object, source->text);
                    break;
                default:
                    object->add_glyph(source->code);
                    break;
                }

                if (wrap == 0 && lines < 12 && !(pen_x + (glyph->right - glyph->left) <= object->unk18.unk08))
                {
                    if (in_run)
                    {
                        wrap = run_start(glyph);
                    }
                    else if (source->code >= 0x4000 || static_cast<LibManagedResourceSlot*>(glyph->unk10)->flag)
                    {
                        wrap = func_004602B0(object, records, glyph);
                    }
                    else
                    {
                        wrap = glyph;
                    }

                    if (object->unk558 & 1)
                    {
                        object->unk90 = func_004601F0(object, records, wrap - 1);
                    }

                    object->horizontal_align = align;
                    object->tint = tint;
                    source = line_start;
                    object->draw_scale = scale;
                    object->draw_scale_y = scale_y;
                    object->unk88 = spacing;
                    object->unk8c = leading;
                    goto retry;
                }
            }
            else
            {
                switch (code)
                {
                case 0x4000:
                    object->next_record->code = 0x4000;
                    going = more = 0;
                    object->next_record++;
                    object->record_count++;
                    break;
                case 0x4001:
                    object->next_record->code = 0x4001;
                    going = more = 0;
                    object->next_record->unk10 = const_cast<u8*>(source->text);
                    object->next_record++;
                    object->record_count++;
                    break;
                case 0x4002:
                    object->horizontal_align = source->value;
                    break;
                case 0x4008:
                    object->tint = source->value;
                    break;
                case 0x400A:
                    object->draw_scale = object->draw_scale_y = source->number;
                    break;
                case 0x400C:
                    object->unk88 = source->number;
                    break;
                case 0x400E:
                    object->unk8c = source->number;
                    break;
                case 0x4010:
                    object->begin_run();
                    in_run = 1;
                    break;
                case 0x4011:
                    object->end_run(const_cast<u8*>(source->text), source->extra);
                    in_run = 0;
                    break;
                case 0x401A:
                    object->unk558 = source->value;
                    break;
                default:
                    object->next_record->code = code;
                    object->next_record->glyph = source->extra;
                    object->next_record->unk10 = reinterpret_cast<void*>(source->value);
                    object->next_record->unk14.scale = source->number;
                    object->next_record->color = source->value;
                    object->next_record++;
                    object->record_count++;
                    break;
                }
            }

            source++;
        }

        if (object->record_count > 0)
        {
            object->func_004637A0(records, object->record_count);
            records += object->record_count;
            total += object->record_count;

            if (object->line_count < 256)
            {
                object->line_heights[object->line_count] = object->max_height + object->unk8c;
            }

            object->line_count++;
        }
    }

    object->record_count = total;
    object->record_cursor += object->record_count;
}

/**
 * @brief Measure the widget's text page by page: per page, count the glyphs found in its resource (or the runtime's
 *        first slot) and missing ones, the space control codes add, line breaks, quoted string bytes and button
 *        glyphs, and keep the largest page's counts.
 * @param object Multiline text widget.
 */
extern "C" void func_00461230(LibObject174D90* object)
{
    object->unkb0 = 0;
    object->unkac = 0;
    object->unka8 = 0;
    object->unka4 = 0;
    object->glyph_count = 0;
    object->unkb4 = 0;
    const u8* text = static_cast<const u8*>(object->unk100);
    bool more = true;

    do
    {
        s32 lines = 0;
        s32 buttons = 0;
        s32 found = 0;
        s32 missing = 0;
        s32 breaks = 0;
        s32 quoted = 0;

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
                    case 0x4004:
                    case 0x4007:
                    case 0x4016:
                    case 0x4017:
                    case 0x4018:
                    case 0x4019:
                    case 0x401F:
                        lines++;
                        break;
                    case 0x4001:
                        lines++;
                        goto page_end;
                    case 0x4020:
                        lines++;
                        text++;
                        break;
                    case 0x4002:
                    case 0x4008:
                    case 0x401A:
                        text++;
                        break;
                    case 0x4005:
                    case 0x4006:
                    case 0x4014:
                    case 0x4015:
                    case 0x401E:
                        lines++;
                        text += 4;
                        break;
                    case 0x400A:
                    case 0x400C:
                    case 0x400E:
                        text += 4;
                        break;
                    case 0x4012:
                        found += 11;
                        text++;
                        break;
                    case 0x4013:
                    case 0x4021:
                        found += 0x20;
                        text++;
                        break;
                    case 0x4022:
                    case 0x4023:
                        missing += 0x40;
                        text++;
                        break;
                    case 0x4010:
                        lines++;
                        breaks++;
                        break;
                    case 0x4011:
                        while (*text)
                        {
                            quoted++;
                            text++;
                        }

                        text++;
                        break;
                    case 0x401C:
                        lines++;
                        breaks++;

                        while (*text)
                        {
                            text++;
                            quoted++;
                        }

                        text++;
                        break;
                    case 0x401D:
                        lines++;
                        buttons++;
                        text++;
                        break;
                    }

                    continue;
                }
            }

            s32 index;
            LibManagedResourceSlot* slot;

            slot = object->resource_slot;
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
                found++;
            }
            else
            {
                missing++;
            }
        }

    page_end:
        lines += found + missing;

        if (object->unkb4 < lines)
        {
            object->unkb4 = lines;
        }

        if (object->glyph_count < buttons)
        {
            object->glyph_count = buttons;
        }

        if (object->unka4 < found)
        {
            object->unka4 = found;
        }

        if (object->unka8 < missing)
        {
            object->unka8 = missing;
        }

        if (object->unkac < breaks)
        {
            object->unkac = breaks;
        }

        if (object->unkb0 < quoted)
        {
            object->unkb0 = quoted;
        }
    } while (more);

    object->unkb4 += 0x80;
}

/**
 * @brief Point the multiline widget at a keyed text of a resource slot: measure it and allocate its drawing storage,
 *        glyph states and line table.
 * @param object Multiline text widget.
 * @param slot Resource slot index.
 * @param key Key of the text in the slot's index.
 * @param mode Drawing mode mask.
 * @param flag Nonzero to reset the drawing state and the scroll speed first.
 * @return One, or zero when an allocation failed.
 */
extern "C" s32 func_004614E0(LibObject174D90* object, s32 slot, s32 key, u32 mode, u8 flag)
{
    object->unk39 = 0;

    if (object->unk70)
    {
        resident_queue_allocation_release(g_resident_release_queues, object->unk70);
        object->unk70 = 0;
    }

    func_004C7D00(object);

    if (flag)
    {
        object->reset_drawing_state();
    }

    object->resource_slot = &g_field_runtime->resource_slots[slot];
    object->unk100 = func_00465340(g_field_runtime, slot, key);
    func_00461230(object);

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

        if (!static_cast<LibClass178780*>(object->unkfc)->init(object->glyph_count))
        {
            return 0;
        }
    }

    object->unk70 = static_cast<u8*>(::operator new[](object->unkb4 * 32, 0));

    if (object->unk70 == 0)
    {
        return 0;
    }

    if (flag)
    {
        object->unk52c = object->unk524;
        object->unk558 = object->unk554;
    }

    object->mode = mode;
    object->unk118 = object->unk100;
    object->unk568 = 0;
    object->unk550 = 5;
    object->unk575 = 0;
    object->unk577 = 0;
    object->pending = 0;
    object->unk57a = 1;
    object->unk39 = 1;
    return 1;
}

typedef struct LibMultilineRectangleState
{
    u8 pad00[0x70];
    void* display;
    u8 pad74[0x84];
    u8 flag;
    u8 padf9[0x1B];
    void* allocation;
    u8 pad118[0x40C];
    float unk524;
    float unk528;
    u8 pad52c[0x28];
    u32 unk554;
    u8 pad558[0xC];
    u32 unk564;
    u8 pad568[0xC];
    u8 unk574;
} LibMultilineRectangleState;

/**
 * @brief Initialize the text rectangle and reset the multiline drawing state.
 * @param object Multiline text widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 */
extern "C" void lib_multiline_text_init_rectangle(LibObject174D90* object, float x, float y, float width, float height)
{
    LibMultilineRectangleState* state = (LibMultilineRectangleState*)object;
    lib_text_init_rectangle((LibTextWidget*)object, x, y, width, height);
    state->allocation = 0;
    state->display = 0;
    state->unk524 = 0.05f;
    state->unk528 = 1.5f;
    state->unk554 = 2;
    state->unk564 = 0;
    state->unk574 = 0;
}

extern "C" s32 func_004614E0(LibObject174D90* object, s32 slot, s32 key, u32 mode, u8 flag);

/**
 * @brief Initialize the multiline text rectangle and load its resource.
 * @param object Multiline text widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @param slot Resource source word.
 * @param key Text resource key.
 * @param mode Drawing mode mask.
 * @param flag Slot state flag whose low byte is stored.
 * @return Resource initialization status.
 */
extern "C" s32 lib_multiline_text_init_resource_rectangle(LibObject174D90* object, float x, float y, float width, float height, s32 slot, s32 key, u32 mode, u32 flag)
{
    LibMultilineRectangleState* state = (LibMultilineRectangleState*)object;
    state->flag = flag;
    lib_text_init_rectangle((LibTextWidget*)object, x, y, width, height);
    state->allocation = 0;
    state->display = 0;
    state->unk524 = 0.05f;
    state->unk528 = 1.5f;
    state->unk554 = 2;
    state->unk564 = 0;
    state->unk574 = 0;
    return func_004614E0(object, slot, key, mode, 1);
}

/** @brief Release the multiline allocation and destroy the text widget. */
LibObject174D90::~LibObject174D90()
{
    if (unk70 != 0)
    {
        delete[] unk70;
        unk70 = 0;
    }
}

/**
 * @brief Queue an embedded packet's data for sending, with a DMA submission to call when it's done.
 * @param embedded Packet embedded in its owner.
 * @param adjusted Owner's DMA submission, or null.
 */
extern "C" void func_00461830(void* embedded, void* adjusted)
{
    func_004DC4F0(g_packet_queue, 3, 0, static_cast<ResidentPacket*>(embedded)->unk04, 0, adjusted);
}

/**
 * @brief Allocate aligned drawing storage for an empty block and flush the data cache.
 * @param storage Storage block to initialize.
 * @param word_count Number of 64-bit drawing words requested.
 * @return One on success, or zero if storage exists or allocation fails.
 */
extern "C" s32 lib_allocate_drawing_storage(LibStorageBlock0C* storage, s32 word_count)
{
    if (storage->allocation != 0)
    {
        return 0;
    }

    storage->allocation = new (0) u8[word_count * sizeof(u64) + DRAWING_STORAGE_PREFIX + DRAWING_STORAGE_ALIGNMENT];

    if (storage->allocation == 0)
    {
        return 0;
    }

    u8* buffer = static_cast<u8*>(storage->allocation) + DRAWING_STORAGE_PREFIX;
    storage->aligned = reinterpret_cast<void*>((reinterpret_cast<u32>(buffer) + DRAWING_STORAGE_ALIGNMENT - 1) & ~(DRAWING_STORAGE_ALIGNMENT - 1u));
    storage->dma_address = reinterpret_cast<u32>(storage->aligned) | DRAWING_STORAGE_DMA_ADDRESS_TAG;
    FlushCache(0);
    return 1;
}

/** @brief Free the owned byte array and clear its allocation pointer. */
LibStorageBlock0C::~LibStorageBlock0C()
{
    if (allocation)
    {
        delete[] (u8*)allocation;
        allocation = 0;
    }
}

/** @brief Hook run when the text restarts; the base window does nothing. */
void LibMessageWindow::func_00461960()
{
}

/** @brief Hook run at the end of the text; the base window does nothing. */
void LibMessageWindow::func_00461970()
{
}

/**
 * @brief Hook for a text control code with three values; the base window does nothing.
 * @param first First value.
 * @param second Second value.
 * @param third Third value.
 */
void LibMessageWindow::func_00461980(s16 first, s16 second, u32 third)
{
}

/** @brief Hook for the event flagged at 0x105F; the base window does nothing. */
void LibMessageWindow::func_00461990()
{
}

/** @brief Hook for the event flagged at 0x1060; the base window does nothing. */
void LibMessageWindow::func_004619A0()
{
}

/** @brief Window hook at slot 0xC8; the base window does nothing. */
void LibMessageWindow::func_004619B0()
{
}

/**
 * @brief Hook for a text control code with one value; the base window does nothing.
 * @param value Control value.
 */
void LibMessageWindow::func_004619C0(u32 value)
{
}

/**
 * @brief Hook for a second text control code with one value; the base window does nothing.
 * @param value Control value.
 */
void LibMessageWindow::func_004619D0(u32 value)
{
}

/** @brief Hook for a text control code; the base window does nothing. */
void LibMessageWindow::func_004619E0()
{
}

/** @brief Destroy the panel. */
inline LibClass1722E0::~LibClass1722E0()
{
}

/** @brief Release the widget storage and destroy its base. */
inline ItemCreationClass1746A0::~ItemCreationClass1746A0()
{
}

/** @brief Destroy the widget. */
inline LibClass175170::~LibClass175170()
{
}

/** @brief Destroy the window and its widgets. */
LibMessageWindow::~LibMessageWindow()
{
}

#define LIB_MESSAGE_WINDOW_STATE_WAIT 4
#define LIB_MESSAGE_WINDOW_STATE_WAIT_END 6

/**
 * @brief Advance from state 4 or 6 to the next state.
 * @return One when the state advanced, otherwise zero.
 */
s32 LibMessageWindow::func_00461B60()
{
    if (state != LIB_MESSAGE_WINDOW_STATE_WAIT && state != LIB_MESSAGE_WINDOW_STATE_WAIT_END)
    {
        return 0;
    }

    state++;
    return 1;
}

#define LIB_MESSAGE_WINDOW_STATE_WAIT 4
#define LIB_MESSAGE_WINDOW_STATE_WAIT_END 6
#define LIB_MESSAGE_WINDOW_STATE_LOAD 2
#define LIB_MESSAGE_WINDOW_KEPT_MODE 0x50000

/**
 * @brief In state 4 or 6, load new text into the window and go back to state 2.
 * @param source Resource source word.
 * @param key Text resource key.
 * @param mode Drawing mode; its bits 16 and 18 are kept from the current mode.
 * @param flag Resource state flag.
 * @return One when the text was loaded, otherwise zero.
 */
s32 LibMessageWindow::func_00461BA0(u32 source, s32 key, u32 mode, u32 flag)
{
    if (state != LIB_MESSAGE_WINDOW_STATE_WAIT && state != LIB_MESSAGE_WINDOW_STATE_WAIT_END)
    {
        return 0;
    }

    this->source = source;
    this->key = key;
    this->mode = (this->mode & LIB_MESSAGE_WINDOW_KEPT_MODE) | (mode & ~LIB_MESSAGE_WINDOW_KEPT_MODE);
    lib_multiline_text_set_resource(&text, this->source, this->key, this->mode, flag);
    state = LIB_MESSAGE_WINDOW_STATE_LOAD;
    return 1;
}

/**
 * @brief Step the window's open/close sequence: open the frame, show the panel and text, wait for the text to finish,
 *        hide the text, close the frame and finish.
 * @param first Unused.
 * @param second Unused.
 * @param third Unused.
 */
void LibMessageWindow::func_00412C40(bool first, bool second, bool third)
{
    switch (state)
    {
    case 0:
        if (!(mode & 0x10000))
        {
            frame.unk3d = 1;
            frame.transition_state = 1;
            state++;
        }
        else
        {
            state = 2;
        }

        break;
    case 1:
        if (frame.in_transition_state(0))
        {
            state++;
        }

        break;
    case 2:
        unk180.unk3d = 1;
        text.unk3d = 1;
        state++;
        break;
    case 3:
        if (!text.text_finished())
        {
            break;
        }

        if (mode & 0x80000)
        {
            unk105f = 1;
        }

        state++;
    case 4:
        if (mode & 0x80000)
        {
            break;
        }

        state++;
    case 5:
        text.unk3d = 0;

        if (mode & 0x100000)
        {
            unk1060 = 1;
        }

        state++;
    case 6:
        if (mode & 0x100000)
        {
            break;
        }

        state++;
    case 7:
        if (!(mode & 0x10000))
        {
            frame.transition_state = 5;
            state++;
        }
        else
        {
            state = 9;
        }

        break;
    case 8:
        if (frame.in_transition_state(0))
        {
            frame.unk3d = 0;
            unk180.unk3d = 0;
            state++;
        }

        break;
    case 9:
        state = -1;
        unkab = 0;
        func_004619B0();

        if (mode & 0x80000000)
        {
            destroy();
        }

        break;
    }
}

/**
 * @brief Update and draw the container, then run the hooks for the text events flagged since the last call.
 * @param first Nonzero to chain the widget packets.
 * @param second Nonzero to update the widgets.
 * @param third Nonzero to draw the widgets.
 */
void LibMessageWindow::func_0044B100(bool first, bool second, bool third)
{
    LibContainer::func_0044B100(first, second, third);

    if (unk105c)
    {
        func_00461960();
        unk105c = 0;
    }

    if (unk105d)
    {
        func_00461970();
        unk105d = 0;
    }

    if (unk105e)
    {
        func_00461980(unk1054, unk1056, unk1058);
        unk105e = 0;
    }

    if (unk1061)
    {
        func_004619C0(unk1050);
        unk1061 = 0;
    }

    if (unk1062)
    {
        func_004619D0(unk1050);
        unk1062 = 0;
    }

    if (unk1063)
    {
        func_004619E0();
        unk1063 = 0;
    }

    if (unk105f)
    {
        func_00461990();
        unk105f = 0;
    }

    if (unk1060)
    {
        func_004619A0();
        unk1060 = 0;
    }
}

extern "C" s32 func_00468230(LibClass175170* object, float x, float y);

/**
 * @brief Set the message window up at a position and size: its frame, cursor, two clipping widgets and its text,
 *        loaded from a keyed text.
 * @param window Window to set up.
 * @param source Resource source word.
 * @param key Text resource key.
 * @param mode Drawing mode; bit 17 hides the text, bit 18 keeps the cursor detached from it.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Window width.
 * @param height Window height.
 * @param flag Resource state flag.
 * @return One on success, or zero when a widget can't be set up.
 */
extern "C" s32 func_00461FA0(LibMessageWindow* window, u32 source, s32 key, u32 mode, float x, float y, float width,
                             float height, u32 flag)
{
    window->source = source;
    window->key = key;
    window->mode = mode;
    lib_container_init(window, 4, x, y, 0, 0.0f, 0);

    if (!window->frame.init_frame(width, height))
    {
        return 0;
    }

    if (!func_00468230(&window->unk180, width - 28.0f, height - 8.0f))
    {
        return 0;
    }

    if (!lib_scissor_init_rectangle(&window->unka18, 0.0f, 16.0f, width, height - 32.0f))
    {
        return 0;
    }

    if (!lib_scissor_init_reset(&window->unka6c, 1))
    {
        return 0;
    }

    if (!lib_multiline_text_init_resource_rectangle(&window->text, 16.0f, 16.0f, width - 32.0f, height - 32.0f,
                                                     window->source, window->key, window->mode, flag))
    {
        return 0;
    }

    window->text.owner = window;
    window->frame.unk3d = 0;
    window->unk180.unk3d = 0;
    window->text.unk3d = 0;

    if (window->mode & 0x20000)
    {
        window->text.visible = 0;
    }

    if (!(window->mode & 0x40000))
    {
        window->text.unk114 = &window->unk180;
    }

    lib_container_attach_widget(window, &window->frame);
    lib_container_attach_widget(window, &window->unka18);
    lib_container_attach_widget(window, &window->text);
    lib_container_attach_widget(window, &window->unka6c);
    lib_container_attach_widget(window, &window->unk180);
    window->state = 0;
    window->unk1064 = 0;
    window->unk1063 = 0;
    window->unk1062 = 0;
    window->unk1061 = 0;
    window->unk1060 = 0;
    window->unk105f = 0;
    window->unk105e = 0;
    window->unk105d = 0;
    window->unk105c = 0;
    return 1;
}

/** @brief Flag a control code for the window and set its flag byte at 0x1064. */
void LibMessageWindowText::func_0045F650()
{
    owner->unk1063 = 1;
    owner->unk1064 = 1;
}

/**
 * @brief Pass a one-value control code to the window and set its flag byte at 0x1064.
 * @param value Control value.
 */
void LibMessageWindowText::func_0045F640(u32 value)
{
    owner->unk1062 = 1;
    owner->unk1050 = value;
    owner->unk1064 = 1;
}

/**
 * @brief Pass a one-value control code to the window.
 * @param value Control value.
 */
void LibMessageWindowText::func_0045F630(u32 value)
{
    owner->unk1061 = 1;
    owner->unk1050 = value;
}

/**
 * @brief Pass a three-value control code to the window.
 * @param first First value.
 * @param second Second value.
 * @param third Third value.
 */
void LibMessageWindowText::func_0045F620(s16 first, s16 second, u32 third)
{
    owner->unk1054 = first;
    owner->unk1056 = second;
    owner->unk1058 = third;
    owner->unk105e = 1;
}

/** @brief Flag the end of the text for the window. */
void LibMessageWindowText::func_0045F610()
{
    owner->unk105d = 1;
}

/** @brief Flag the restart for the window. */
void LibMessageWindowText::func_0045F600()
{
    owner->unk105c = 1;
}

void LibWidget::draw()
{
}

/**
 * @brief Draw laid-out records: runs and numbers by their own routines, glyphs by the glyph routine, other
 *        control records not at all.
 * @param records Records to draw.
 * @param count Number of records.
 */
void LibDrawWidget::draw_records(LibDrawRecord* records, s32 count)
{
    func_00463500(records, count);

    for (s32 i = 0; i < count; i++, records++)
    {
        if (records->code == LIB_DRAW_RECORD_RUN)
        {
            func_00462FC0(records);
        }
        else if (records->code == LIB_DRAW_RECORD_NUMBER)
        {
            func_00462C70(records);
        }
        else if (!(records->code & LIB_DRAW_RECORD_CONTROL))
        {
            func_004624E0(records);
        }
    }

    func_004623F0();
}

/** @brief Close the drawing packet: a texture flush when unkdc is set, REF tags for the two blocks in use, then END. */
void LibDrawWidget::func_004623F0()
{
    u64* packet = packet_cursor;

    if (unkdc > 0)
    {
        packet[0] = DMA_TAG(2, DMA_TAG_ID_CNT, 0);
        packet[2] = GIF_TAG_NREG(1) | GIF_TAG_EOP | 1;
        packet[3] = GIF_REGISTER_AD;
        packet[4] = 0;
        packet[5] = GS_REGISTER_TEXFLUSH;
        packet += 6;
    }

    if (unke0 > 0)
    {
        packet[0] = DMA_TAG((u32)(unk60 - unk5c) >> 4, DMA_TAG_ID_REF, (u32)unk5c & 0x0FFFFFFF);
        packet += 2;
    }

    if (unke4 > 0)
    {
        packet[0] = DMA_TAG((u32)(unk68 - unk64) >> 4, DMA_TAG_ID_REF, (u32)unk64 & 0x0FFFFFFF);
        packet += 2;
    }

    packet_tag = packet;
    packet[0] = DMA_TAG(0, DMA_TAG_ID_END, 0);
    packet_cursor = packet + 2;
}

/**
 * @brief Pack a UV value.
 * @param u Horizontal texel position, in sixteenths.
 * @param v Vertical texel position, in sixteenths.
 * @return UV register value.
 */
static inline u32 lib_glyph_uv(s32 u, s32 v)
{
    return (s64)u | (s64)v << 16;
}

/**
 * @brief Pack an XYZ2 value.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param z Depth.
 * @return XYZ2 register value.
 */
static inline u64 lib_glyph_xyz(s32 x, s32 y, s32 z)
{
    return (s64)z << 32 | ((s64)x | (s64)y << 16);
}

/**
 * @brief Draw a glyph record: copy the glyph into the next upload cell when it isn't resident, draw a seven-sprite
 *        outline when unkf8 is set, then the shadow and the glyph; flush the texture cache once the upload cells run
 *        out.
 * @param record Record to draw; unk10 is its resource slot.
 */
void LibDrawWidget::func_004624E0(LibDrawRecord* record)
{
    u16 glyph = record->glyph;
    FieldRuntime* runtime = g_field_runtime;
    LibContainer* owner = container;
    LibManagedResourceSlot* slot = static_cast<LibManagedResourceSlot*>(record->unk10);
    float scale_x = runtime->screen_scale_x;
    float offset_x = runtime->screen_offset_x;
    float scale_y = runtime->screen_scale_y;
    float offset_y = runtime->screen_offset_y;
    float x = owner->translation.x + unk18.unk00 - unk78;
    float y = owner->translation.y + unk18.unk04 - unk7c;
    // TODO: Declared before they're assigned, top before right, for the target's register order; a guessed shape.
    s32 left;
    s32 top;
    s32 right;
    s32 bottom;
    left = (s32)(offset_x + scale_x * (x + record->left));
    right = (s32)(offset_x + scale_x * (x + record->right));
    top = (s32)(offset_y + scale_y * (y + record->top));
    bottom = (s32)(offset_y + scale_y * (y + record->bottom));
    u32 uv_top;
    u32 uv_bottom;
    bool uploaded;

    if (glyph >= slot->loaded)
    {
        s32 row = runtime->resource_area_end;
        u64* packet = packet_cursor;
        packet[0] = DMA_TAG(6, DMA_TAG_ID_CNT, 0);
        packet[2] = GIF_TAG_NREG(1) | 4;
        packet[3] = GIF_REGISTER_AD;
        packet[4] = (u64)0x24100000 << 32;
        packet[5] = GS_REGISTER_BITBLTBUF;
        packet[6] = (u64)unkd8 << 32 | (u64)row << 48;
        packet[7] = GS_REGISTER_TRXPOS;
        packet[8] = slot->unk28 | (u64)slot->unk2c << 32;
        packet[9] = GS_REGISTER_TRXREG;
        packet[10] = 0;
        packet[11] = GS_REGISTER_TRXDIR;
        packet[12] = (s64)(slot->unk1c / 16) | GIF_TAG_FLG_IMAGE | GIF_TAG_EOP;
        packet[13] = 0;
        packet[14] = DMA_TAG(slot->unk1c / 16, DMA_TAG_ID_REF, slot->sections[3] + slot->unk20 * (record->glyph - slot->loaded));
        packet_cursor = packet + 16;
        uv_top = lib_glyph_uv(unkd8 * 16 + 8, row * 16 + 8);
        uv_bottom = lib_glyph_uv((unkd8 + record->unk14.width) * 16 - 8, (row + slot->unk24) * 16 - 8);
        uploaded = true;
    }
    else
    {
        s32 columns = slot->unit_count;
        uploaded = false;
        s32 u = slot->unk28 * (glyph % columns);
        s32 v = slot->start + slot->unk2c * (glyph / columns);
        uv_top = lib_glyph_uv(u * 16 + 8, v * 16 + 8);
        uv_bottom = lib_glyph_uv((u + record->unk14.width) * 16 - 8, (v + slot->unk24) * 16 - 8);
    }

    // TODO: These are declared ahead of their values for the target's register order; a guessed shape.
    u32 alpha_bits;
    s32 color = record->color;
    alpha_bits = (s32)(draw_alpha * lib_widget_container_alpha(container) / 128.0f) << 24;
    s32 shadow_depth;
    s32 offset;
    u64* packet;
    u32 shadow;

    if (color == 0 || !unkf9)
    {
        shadow = 0;
    }
    else
    {
        shadow = alpha_bits | draw_color;
    }

    u32 fill = color | alpha_bits;
    offset = g_field_runtime->unk544;
    packet = reinterpret_cast<u64*>(unk60);
    s32 depth = container->unka4;
    shadow_depth = depth + 4;
    s32 glyph_depth = depth + 5;

    if (unkf8)
    {
        packet[0] = GIF_TAG_NREG(2) | GIF_TAG_FLG_REGLIST | 1;
        packet[1] = 0xF1;
        packet[2] = shadow;
        packet[3] = 0;
        packet[4] = GIF_TAG_NREG(4) | GIF_TAG_FLG_REGLIST | 7;
        packet[5] = 0x5353;
        packet[6] = uv_top;
        packet[7] = lib_glyph_xyz(left - offset, top - offset, shadow_depth);
        packet[8] = uv_bottom;
        packet[9] = lib_glyph_xyz(right - offset, bottom - offset, shadow_depth);
        packet[10] = uv_top;
        packet[11] = lib_glyph_xyz(left, top - offset, shadow_depth);
        packet[12] = uv_bottom;
        packet[13] = lib_glyph_xyz(right, bottom - offset, shadow_depth);
        packet[14] = uv_top;
        packet[15] = lib_glyph_xyz(left + offset, top - offset, shadow_depth);
        packet[16] = uv_bottom;
        packet[17] = lib_glyph_xyz(right + offset, bottom - offset, shadow_depth);
        packet[18] = uv_top;
        packet[19] = lib_glyph_xyz(left - offset, top, shadow_depth);
        packet[20] = uv_bottom;
        packet[21] = lib_glyph_xyz(right - offset, bottom, shadow_depth);
        packet[22] = uv_top;
        packet[23] = lib_glyph_xyz(left + offset, top, shadow_depth);
        packet[24] = uv_bottom;
        packet[25] = lib_glyph_xyz(right + offset, bottom, shadow_depth);
        packet[26] = uv_top;
        packet[27] = lib_glyph_xyz(left - offset, top + offset, shadow_depth);
        packet[28] = uv_bottom;
        packet[29] = lib_glyph_xyz(right - offset, bottom + offset, shadow_depth);
        packet[30] = uv_top;
        packet[31] = lib_glyph_xyz(left, top + offset, shadow_depth);
        packet[32] = uv_bottom;
        packet[33] = lib_glyph_xyz(right, bottom + offset, shadow_depth);
        packet += 34;
    }

    packet[0] = GIF_TAG_NREG(10) | GIF_TAG_FLG_REGLIST | GIF_TAG_EOP | 1;
    packet[1] = 0x0000005353153531;
    packet[2] = shadow;
    packet[3] = uv_top;
    packet[4] = lib_glyph_xyz(left + offset, top + offset, shadow_depth);
    packet[5] = uv_bottom;
    packet[6] = lib_glyph_xyz(right + offset, bottom + offset, shadow_depth);
    packet[7] = fill;
    packet[8] = uv_top;
    packet[9] = lib_glyph_xyz(left, top, glyph_depth);
    packet[10] = uv_bottom;
    packet[11] = lib_glyph_xyz(right, bottom, glyph_depth);
    unk60 = reinterpret_cast<u8*>(packet + 12);
    unke0++;

    if (uploaded)
    {
        if (++unkdc < g_field_runtime->unk550)
        {
            unkd8 += 32;
        }
        else
        {
            u64* cursor = packet_cursor;
            cursor[0] = DMA_TAG(2, DMA_TAG_ID_CNT, 0);
            cursor[2] = GIF_TAG_NREG(1) | GIF_TAG_EOP | 1;
            cursor[3] = GIF_REGISTER_AD;
            cursor[4] = 0;
            cursor[5] = GS_REGISTER_TEXFLUSH;
            cursor[6] = DMA_TAG((u32)(unk60 - unk5c) >> 4, DMA_TAG_ID_REF, (u32)unk5c & 0x0FFFFFFF);
            packet_cursor = cursor + 8;
            unke0 = 0;
            unkdc = 0;
            unkd8 = 0;
            unk5c = unk60;
        }
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00462C70__13LibDrawWidgetFP13LibDrawRecord);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00462FC0__13LibDrawWidgetFP13LibDrawRecord);

/**
 * @brief Start the drawing packet: reset the block counts, open the main packet with its fixed GS setup, and open
 *        the second block with the same setup when there's one.
 * @param records Records to draw; unused.
 * @param count Number of records; unused.
 */
void LibDrawWidget::func_00463500(LibDrawRecord* records, s32 count)
{
    unke4 = 0;
    unke0 = 0;
    unkdc = 0;
    unkd8 = 0;
    packet = (u64*)dma_address;
    packet_cursor = (u64*)dma_address;

    u64* cursor = packet_cursor;
    cursor[0] = DMA_TAG(3, DMA_TAG_ID_CNT, 0);
    cursor[2] = GIF_TAG_NREG(4) | GIF_TAG_FLG_REGLIST | GIF_TAG_EOP | 1;
    cursor[3] = 0xF077;
    cursor[4] = 0x8007FF8001300000ULL;
    cursor[5] = 0x0007FF86AA440000ULL;
    cursor[6] = 0x356;
    cursor[7] = 0;
    packet_cursor = cursor + 8;
    unk5c = (u8*)dma_address + unk48;
    unk60 = unk5c;

    if (unkac > 0)
    {
        unk64 = unk5c + unk4c;
        unk68 = unk64;

        u64* block = (u64*)unk68;
        block[0] = GIF_TAG_NREG(4) | GIF_TAG_FLG_REGLIST | GIF_TAG_EOP | 1;
        block[1] = 0xF077;
        block[2] = 0x8007FF8001300000ULL;
        block[3] = 0x0007FF8622C10000ULL;
        block[4] = 0x356;
        block[5] = 0;
        unk68 = (u8*)(block + 6);
    }
}

#define LIB_ALIGN_CENTER 1

/**
 * @brief Shift laid-out records to the vertical alignment and finish the extent.
 * @param records Records to shift.
 * @param count Number of records.
 */
void LibDrawWidget::align_records_vertically(LibDrawRecord* records, s32 count)
{
    if (vertical_align != 0)
    {
        float offset = unk18.unk0c - (pen_y - unk8c);

        if (vertical_align == LIB_ALIGN_CENTER)
        {
            offset /= 2.0f;
        }

        for (s32 i = 0; i < count; i++)
        {
            records->top += offset;
            records->bottom += offset;
            records++;
        }

        extent.unk04 = offset;
    }

    extent.height = pen_y - unk8c;
    extent.width = extent.width - extent.unk00;
}

/**
 * @brief Shift laid-out records to the horizontal alignment, drop them to the line's bottom, and move the pen to the
 *        next line.
 * @param records Records to shift.
 * @param count Number of records.
 */
void LibDrawWidget::func_004637A0(LibDrawRecord* records, s32 count)
{
    if (horizontal_align != 0)
    {
        float shift = unk18.unk08 - (pen_x - unk88 - unk90);

        if (horizontal_align == 1)
        {
            shift /= 2.0f;
        }

        LibDrawRecord* record = records;

        for (s32 i = 0; i < count; i++, record++)
        {
            record->left += shift;
            record->right += shift;
        }
    }

    if (min_height != max_height)
    {
        float bottom = pen_y + max_height;

        LibDrawRecord* record = records;

        for (s32 i = 0; i < count; i++, record++)
        {
            record->top = bottom - (record->bottom - record->top);
            record->bottom = bottom;
        }
    }

    if (run_head != 0)
    {
        LibDrawRecord* record = records;

        for (s32 i = 0; i < count; i++, record++)
        {
            record->top += 12.0f;
            record->bottom += 12.0f;
        }

        max_height += 12.0f;
    }

    float left = records->left;

    if (left < extent.unk00)
    {
        extent.unk00 = left;
    }

    float right = left + (pen_x - unk88 - unk90);

    if (!(right <= extent.width))
    {
        extent.width = right;
    }

    pen_y += max_height + unk8c;
}

/** "%d". */
extern const char D_00505CF8[];

extern "C" s32 func_00463C90(LibDrawWidget* widget, u16* codes, s32 id, u8 variant);

extern "C" s32 func_00463E60(LibDrawWidget* widget, u16* codes, u16 id, s32 variant);

/**
 * @brief Lay out the text for a 16-bit ID glyph by glyph.
 * @param widget Widget to lay out into.
 * @param id ID passed to the code lookup.
 * @param variant Second lookup argument.
 */
extern "C" void func_00463C00(LibDrawWidget* widget, s32 id, u8 variant)
{
    u16 codes[0x80];
    s32 count = func_00463C90(widget, codes, id, variant);

    if (count > 0)
    {
        u16* code = codes;

        for (s32 i = 0; i < count; i++)
        {
            widget->add_glyph(*code++);
        }
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00463C90);

/**
 * @brief Lay out the text for a 16-bit ID glyph by glyph.
 * @param widget Widget to lay out into.
 * @param id ID passed to the code lookup.
 * @param variant Second lookup argument.
 */
extern "C" void func_00463DD0(LibDrawWidget* widget, u16 id, s32 variant)
{
    u16 codes[0x80];
    s32 count = func_00463E60(widget, codes, id, variant);

    if (count > 0)
    {
        u16* code = codes;

        for (s32 i = 0; i < count; i++)
        {
            widget->add_glyph(*code++);
        }
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00463E60);

extern "C" s32 func_00464040(LibDrawWidget* widget, u16* codes, const char* text);

/**
 * @brief Lay out text glyph by glyph.
 * @param text Text to lay out.
 */
void LibDrawWidget::add_text(const char* text)
{
    u16 codes[0x80];
    s32 count = func_00464040(this, codes, text);

    if (count > 0)
    {
        u16* code = codes;

        for (s32 i = 0; i < count; i++)
        {
            add_glyph(*code++);
        }
    }
}

/** Glyph code for a character the converter has no range for. */
struct LibCharacterGlyph
{
    u8 character;
    u16 code;
};

/** Glyph codes for the punctuation in ASCII text, ending with a zero character. */
extern "C" const LibCharacterGlyph D_004ED230[];

/**
 * @brief Convert ASCII and half-width katakana text to glyph codes. A '~' switches between hiragana and katakana;
 *        a following dakuten or handakuten mark is merged into the kana.
 * @param widget Widget the codes are for; unused.
 * @param codes Receives the glyph codes, ending with zero.
 * @param text Text to convert.
 * @return Number of glyphs written.
 */
extern "C" s32 func_00464040(LibDrawWidget* widget, u16* codes, const char* text)
{
    s32 count = 0;

    if (text != 0)
    {
        u8 hiragana = 0;

        while (1)
        {
            u8 character = *text++;
            u16 code;

            // TODO: Comparing with 0L (long is 64 bits here) is the only way I've found to get the sign extension before
            // this test. My guess is the original compared the character with NULL.
            if (character == 0L)
            {
                *codes = 0;
                break;
            }

            if (character == '~')
            {
                hiragana ^= 1;
                continue;
            }

            code = 0xF1;

            if (character >= '0' && character <= '9')
            {
                code = character - 0x2F;
            }
            else if (character >= 'A' && character <= 'Z')
            {
                code = character - 0x33;
            }
            else if (character >= 'a' && character <= 'z')
            {
                code = character - 0x39;
            }
            else if (character == 0xB0)
            {
                code = 0x9D;
            }
            else if (character >= 0xA6 && character < 0xDE)
            {
                if (hiragana)
                {
                    if (character < 0xB0)
                    {
                        code = character - 0x64;
                    }
                    else if (static_cast<u8>(*text) == 0xDE)
                    {
                        text++;

                        if (character >= 0xB6 && character < 0xC5)
                        {
                            code = character - 0x3C;
                        }
                        else if (character >= 0xCA && character < 0xCF)
                        {
                            code = character - 0x41;
                        }
                    }
                    else if (static_cast<u8>(*text) == 0xDF)
                    {
                        text++;

                        if (character >= 0xCA && character < 0xCF)
                        {
                            code = character - 0x3C;
                        }
                    }
                    else
                    {
                        code = character - 0x64;
                    }
                }
                else
                {
                    if (character < 0xB0)
                    {
                        code = character - 0x13;
                    }
                    else if (static_cast<u8>(*text) == 0xDE)
                    {
                        text++;

                        if (character == 0xB3)
                        {
                            code = 0xCB;
                        }
                        else if (character >= 0xB6 && character < 0xC5)
                        {
                            code = character + 0x16;
                        }
                        else if (character >= 0xCA && character < 0xCF)
                        {
                            code = character + 0x11;
                        }
                    }
                    else if (static_cast<u8>(*text) == 0xDF)
                    {
                        text++;

                        if (character >= 0xCA && character < 0xCF)
                        {
                            code = character + 0x16;
                        }
                    }
                    else
                    {
                        code = character - 0x13;
                    }
                }
            }
            else
            {
                u8 key;

                for (const LibCharacterGlyph* entry = D_004ED230; (key = entry->character) != 0; entry++)
                {
                    if (key == character)
                    {
                        code = entry->code;
                        break;
                    }
                }
            }

            *codes++ = code;
            count++;
        }
    }

    return count;
}

/**
 * @brief Text code callback: the name of party slot `index`.
 * @param context Text layout context; unused.
 * @param index One-based character slot, 1 through 10.
 * @return Name, or null for an out-of-range slot or with no name provider.
 */
extern "C" char* func_004642E0(void* context, s32 index)
{
    if (index <= 0 || index > 10)
    {
        return 0;
    }

    if (g_field_runtime->character_names == 0)
    {
        return 0;
    }

    return g_field_runtime->character_names->get_character_name(index);
}

/**
 * @brief Lay out a number glyph by glyph.
 * @param value Number to lay out.
 */
void LibDrawWidget::add_number(s32 value)
{
    u16 codes[0x80];
    s32 count = format_number_codes(codes, value);
    u16* code = codes;

    for (s32 i = 0; i < count; i++)
    {
        add_glyph(*code++);
    }
}

#define LIB_NUMBER_CODE_OTHER 11

/**
 * @brief Format a number as character codes: one plus the digit for digits, 11 for anything else.
 * @param codes Receives the codes and a terminating zero.
 * @param value Number to format.
 * @return Number of codes written before the terminator.
 */
s32 LibDrawWidget::format_number_codes(u16* codes, s32 value)
{
    char text[32];
    s32 count = 0;

    sprintf_guess(text, D_00505CF8, value);

    for (char* cursor = text;; count++)
    {
        u16 character = *cursor++;
        u16 code;

        // TODO: Comparing with 0L (long is 64 bits here) is the only way I've found to get the sign extension before
        // this test. My guess is the original compared the character with NULL.
        if (character == 0L)
        {
            *codes = 0;
            break;
        }

        if (character >= '0' && character <= '9')
        {
            code = character - '0' + 1;
        }
        else
        {
            code = LIB_NUMBER_CODE_OTHER;
        }

        *codes++ = code;
    }

    return count;
}

#define LIB_NUMBER_DIGIT_WIDTH 9.0f

/**
 * @brief Lay out a number as one record.
 * @param value Value stored in the record.
 * @param digits Number of digits.
 */
void LibDrawWidget::add_number_record(void* value, s32 digits)
{
    float width = LIB_NUMBER_DIGIT_WIDTH * digits;

    next_record->code = LIB_DRAW_RECORD_NUMBER;
    next_record->left = pen_x - unk88 - unk90;
    next_record->right = next_record->left + width * draw_scale;
    next_record->top = pen_y;
    next_record->bottom = next_record->top + line_height;
    next_record->unk14.scale = draw_scale_y;
    next_record->color = tint;
    next_record->unk10 = value;
    next_record->glyph = digits;
    pen_x = next_record->right + unk88 + unk90;
    next_record++;
    record_count++;
}

/**
 * @brief Close the current run of records.
 * @param value Value stored in the run's head record.
 * @param count Value stored as the run's glyph index.
 */
void LibDrawWidget::end_run(void* value, s32 count)
{
    run_head->unk10 = value;
    run_head->glyph = count;
    run_head->right = pen_x - unk88;
    run_head->bottom = run_head->top + line_height;
    run_head->unk14.end = next_record;
}

/** @brief Start a run of records at the pen position. */
void LibDrawWidget::begin_run()
{
    run_head = next_record;
    run_head->code = LIB_DRAW_RECORD_RUN;
    run_head->color = tint;
    run_head->left = pen_x;
    run_head->top = pen_y;
    next_record++;
    record_count++;
}

#define LIB_SHARED_GLYPH_COUNT 300

/**
 * @brief Lay out one glyph and advance the pen.
 * @param code Character code.
 */
void LibDrawWidget::add_glyph(s32 code)
{
    LibManagedResourceSlot* slot;
    float spacing;
    float width;
    float height;

    next_record->glyph = code - 1;
    slot = resource_slot;
    spacing = unk88;

    if (slot->flag)
    {
        if (code <= LIB_SHARED_GLYPH_COUNT)
        {
            slot = g_field_runtime->resource_slots;

            if (code == 0xE8 || code == 0xE9)
            {
                code = 0xFFFF;
            }
        }
        else
        {
            next_record->glyph -= LIB_SHARED_GLYPH_COUNT;
        }

        if ((code >= 0x94 && code <= 0x9C) || (code >= 0x43 && code < 0x4D))
        {
            pen_x -= 1.0f;
            spacing -= 1.5f;
        }
        else if (code >= 0x93 && code < 0xEA && code != 0x9D)
        {
            spacing -= 1.0f;
        }
    }

    next_record->unk10 = slot;
    next_record->code = code;
    next_record->color = tint;
    next_record->unk14.width = slot->sections[2][next_record->glyph];
    width = next_record->unk14.width * draw_scale;
    next_record->left = pen_x;
    next_record->right = pen_x + width;
    pen_x += unk90 + (width + spacing * draw_scale);
    height = slot->unk24 * draw_scale_y;
    next_record->top = pen_y;
    next_record->bottom = pen_y + height;
    line_height = height;

    if (height < min_height)
    {
        min_height = height;
    }

    if (height > max_height)
    {
        max_height = height;
    }

    next_record++;
    record_count++;
}

#define LIB_LAYOUT_HEIGHT_MAX 9999.0f

/**
 * @brief Start laying out records at the left edge of a line.
 * @param records First record to fill.
 * @param y Vertical pen position; zero also resets the measured extent.
 */
void LibDrawWidget::begin_layout(LibDrawRecord* records, float y)
{
    min_height = LIB_LAYOUT_HEIGHT_MAX;
    max_height = 0.0f;
    line_height = 0.0f;
    pen_x = 0.0f;
    pen_y = y;
    run_head = 0;
    next_record = records;
    record_count = 0;

    if (y == 0.0f)
    {
        extent.unk00 = LIB_LAYOUT_HEIGHT_MAX;
        extent.height = 0.0f;
        extent.width = 0.0f;
        extent.unk04 = 0.0f;
    }
}

#define LIB_TEXT_PALETTE_SIZE 11

/** Text palette colours. */
extern u32 D_004ED200[LIB_TEXT_PALETTE_SIZE];

/**
 * @brief Look up one of the eleven text palette colours.
 * @param index Palette index; larger values select the last colour.
 * @return Packed colour.
 */
u32 LibDrawWidget::get_palette_color(u8 index)
{
    if (index > LIB_TEXT_PALETTE_SIZE - 1)
    {
        index = LIB_TEXT_PALETTE_SIZE - 1;
    }

    return D_004ED200[index];
}

#define LIB_DRAW_WIDGET_DEFAULT_EXTENT 1024.0f

/**
 * @brief Set the display rectangle; a zero width or height selects 1024.
 * @param x Left edge.
 * @param y Top edge.
 * @param width Width.
 * @param height Height.
 */
void LibDrawWidget::set_rectangle(float x, float y, float width, float height)
{
    if (width == 0.0f)
    {
        width = LIB_DRAW_WIDGET_DEFAULT_EXTENT;
    }

    if (height == 0.0f)
    {
        height = LIB_DRAW_WIDGET_DEFAULT_EXTENT;
    }

    unk18.unk00 = x;
    unk18.unk04 = y;
    unk18.unk08 = width;
    unk18.unk0c = height;
}

/** @brief Hand the drawing storage to the resident release queue. */
void LibDrawWidget::release_storage()
{
    if (allocation != 0)
    {
        resident_queue_allocation_release(g_resident_release_queues, allocation);
        allocation = 0;
    }
}

/**
 * @brief Size and allocate the drawing storage.
 * @param first First entry count.
 * @param capacity Second entry count.
 * @param second Third entry count.
 * @param third Fourth entry count.
 * @return One on success, or zero when nothing could be allocated.
 */
s32 LibDrawWidget::allocate_storage(s32 first, s32 capacity, s32 second, s32 third)
{
    s32 lines;

    unka4 = first;
    unka8 = capacity;
    unkac = second;
    unkb0 = third;

    if (capacity == 0)
    {
        lines = 0;
    }
    else
    {
        lines = (capacity - 1) / g_field_runtime->unk550 + 1;
    }

    unk48 = capacity * 128 + 160 + lines * 64;
    unk4c = (unkf8 ? 368 : 96) * (first + capacity);
    unk50 = second == 0 ? 0 : unkac * 16 + 48 + unkb0 * 80;
    allocation = new (0) u8[unk48 + unk4c + unk50 + 256];

    if (allocation == 0)
    {
        return 0;
    }

    u8* buffer = static_cast<u8*>(allocation) + DRAWING_STORAGE_PREFIX;
    aligned = reinterpret_cast<void*>((reinterpret_cast<u32>(buffer) + DRAWING_STORAGE_ALIGNMENT - 1) & ~(DRAWING_STORAGE_ALIGNMENT - 1u));
    dma_address = reinterpret_cast<u32>(aligned) | DRAWING_STORAGE_DMA_ADDRESS_TAG;
    FlushCache(0);
    return 1;
}

/** @brief Clear the storage and restore the default scale, colours and alignment. */
void LibDrawWidget::reset_drawing_state()
{
    allocation = 0;
    unk7c = 0;
    unk78 = 0;
    draw_scale_y = 1.0f;
    draw_scale = 1.0f;
    unk88 = 0.0f;
    unk8c = 2.0f;
    unk90 = 0.0f;
    tint = 0x808080;
    draw_color = 0x020202;
    horizontal_align = 0;
    vertical_align = 0;
}

#define LIB_DRAW_WIDGET_HEAP_ADDRESS_MIN 0x10000

/** @brief Free the drawing storage, then destroy the widget. */
LibDrawWidget::~LibDrawWidget()
{
    if (allocation != 0)
    {
        if (reinterpret_cast<u32>(allocation) >= LIB_DRAW_WIDGET_HEAP_ADDRESS_MIN)
        {
            delete[] static_cast<u8*>(allocation);
        }

        allocation = 0;
    }
}

/** @brief Initialize drawing storage, bounds, scale, colors, and display flags. */
LibDrawWidget::LibDrawWidget()
{
    extent.height = 0.0f;
    extent.width = 0.0f;
    extent.unk04 = 0.0f;
    extent.unk00 = 0.0f;
    unk38 = 10;
    unkf8 = 0;
    unkf9 = 1;
    unkfa = 0;
    allocation = 0;
    unk7c = 0;
    unk78 = 0;
    draw_scale_y = 1.0f;
    draw_scale = 1.0f;
    unk88 = 0.0f;
    unk8c = 2.0f;
    unk90 = 0;
    tint = 0x808080;
    draw_color = 0x020202;
    horizontal_align = 0;
    vertical_align = 0;
}

/** @brief Destroy the widget. */
LibObject174F20::~LibObject174F20()
{
}

/**
 * @brief Lay the numeric widget's number out off screen and measure it.
 * @param object Numeric widget to measure.
 * @return Extent of the laid-out number.
 */
LibTextExtent* func_00464C20(LibObject174F20* object)
{
    LibDrawRecord records[0x40];
    object->begin_layout(records, 0.0f);
    object->add_number(object->numeric_value);
    object->func_004637A0(records, object->record_count);
    object->align_records_vertically(records, object->record_count);
    return &object->extent;
}

/** @brief Lay the number out in the scratchpad and draw it, once; the largest s32 means no number. */
void LibObject174F20::draw()
{
    if (numeric_value == 0x7FFFFFFF)
    {
        unk3b = 0;
        return;
    }

    if (!unk3b)
    {
        lib_restore_texture_cache(static_cast<LibRenderer*>(g_renderer));
        LibDrawRecord* records = reinterpret_cast<LibDrawRecord*>(0x70000000);
        begin_layout(records, 0.0f);
        add_number(numeric_value);
        func_004637A0(records, record_count);
        align_records_vertically(records, record_count);
        draw_records(records, record_count);
        unk3b = 1;
    }
}

/** One opaque 0x50-byte resource slot in the runtime's sixteen-slot table. */
typedef struct LibNumericResourceSlot
{
    u8 bytes[0x50];
} LibNumericResourceSlot;

/** Partial runtime prefix containing the resource slot table. */
typedef struct LibNumericResourceOwner
{
    u8 pad00[0x14];
    LibNumericResourceSlot slots[16];
} LibNumericResourceOwner;

/** Partial numeric widget fields used during resource initialization. */
typedef struct LibNumericResourceState
{
    u8 pad00[0x39];
    u8 initialized;
    u8 pad3a[0x32];
    LibNumericResourceSlot* source;
    u8 pad70[0x2C];
    s32 mode;
    u8 pada0[0x58];
    u8 flag;
    u8 padf9[3];
    u32 value;
} LibNumericResourceState;

/**
 * @brief Initialize the numeric widget rectangle, resource slot, and displayed value.
 * @param object Numeric widget.
 * @param value Initial numeric value.
 * @param slot Runtime resource slot index.
 * @param flag Slot state flag.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return One when initialization succeeds, otherwise zero.
 */
extern "C" s32 lib_numeric_widget_init_rectangle(LibObject174F20* object, u32 value, s32 slot, u8 flag, float x, float y, float width, float height)
{
    LibNumericResourceState* state = (LibNumericResourceState*)object;
    state->flag = flag;
    object->set_rectangle(x, y, width, height);
    state->source = &((LibNumericResourceOwner*)g_field_runtime)->slots[slot];

    if (!object->allocate_storage(0, 16, 0, 0))
    {
        return 0;
    }

    state->value = value;
    state->mode = 2;
    state->initialized = 1;
    return 1;
}

/**
 * @brief Return the list kind the runtime is queued under.
 * @return Three.
 */
s32 FieldRuntime::get_default_list_kind()
{
    return 3;
}

/**
 * @brief Copy both pads' held, pressed and repeated buttons into the runtime, or clear them while time is stopped.
 * @param runtime Field runtime.
 */
extern "C" void func_00464E40(FieldRuntime* runtime)
{
    if (runtime->rate != 0.0f)
    {
        ResidentInputSystem* input = g_input_system;
        FieldRuntime::Input* entry = runtime->inputs;

        for (s32 slot = 0; slot < 2; slot++, entry++)
        {
            entry->unk00 = resident_pad_get_held(input, slot);
            entry->unk02 = resident_pad_get_pressed(input, slot);
            entry->unk04 = resident_pad_get_repeated(input, slot);
        }
    }
    else
    {
        memset_guess(runtime->inputs, 0, sizeof(runtime->inputs));
    }
}

extern "C" const u16 D_004ED2D0[16];

/**
 * @brief Turn a button glyph code into the glyph of the pad button the player has mapped to it.
 * @param runtime Runtime holding the button map.
 * @param code Glyph code; 0x20-0x27 and 0x30-0x37 name the eight mapped actions in two glyph styles.
 * @return Codes below 0x20 unchanged; otherwise the mapped button's index in the first style or index + 0x10 in the
 *         second, or 0x20 when the code or its button isn't known.
 */
extern "C" s32 func_00464EF0(FieldRuntime* runtime, s32 code)
{
    s32 result;

    if (code < 0x20)
    {
        result = code;
    }
    else if (code < 0x40)
    {
        u16 button;

        switch (code)
        {
        case 0x20:
        case 0x30:
            button = runtime->button_map->buttons[0];
            break;

        case 0x21:
        case 0x31:
            button = runtime->button_map->buttons[1];
            break;

        case 0x22:
        case 0x32:
            button = runtime->button_map->buttons[2];
            break;

        case 0x23:
        case 0x33:
            button = runtime->button_map->buttons[3];
            break;

        case 0x24:
        case 0x34:
            button = runtime->button_map->buttons[4];
            break;

        case 0x25:
        case 0x35:
            button = runtime->button_map->buttons[5];
            break;

        case 0x26:
        case 0x36:
            button = runtime->button_map->buttons[6];
            break;

        case 0x27:
        case 0x37:
            button = runtime->button_map->buttons[7];
            break;
        }

        const u16* entry = D_004ED2D0;
        s32 index;

        for (index = 0; index < 16; index++, entry++)
        {
            if (*entry == button)
            {
                break;
            }
        }

        if (index < 16)
        {
            if (code < 0x30)
            {
                result = index;
            }
            else
            {
                result = index + 0x10;
            }
        }
        else
        {
            result = 0x20;
        }
    }
    else
    {
        result = 0x20;
    }

    return result;
}

/**
 * @brief Find one of the field runtime's display chunks.
 * @param runtime Field runtime.
 * @param index Chunk index.
 * @return Chunk, or null when the list is shorter.
 */
extern "C" LibResourceChunkHeader* func_004650B0(FieldRuntime* runtime, s32 index)
{
    LibResourceChunkHeader* chunk = static_cast<LibResourceChunkHeader*>(runtime->display_chunks);

    for (s32 i = 0;; i++)
    {
        if (i == index)
        {
            return chunk;
        }

        chunk = chunk->next_offset == 0 ? 0 : reinterpret_cast<LibResourceChunkHeader*>(reinterpret_cast<u8*>(chunk) + chunk->next_offset);

        if (!chunk)
        {
            break;
        }
    }

    return 0;
}

/**
 * @brief Count the 0x401E control codes in a keyed text and copy their four-byte arguments.
 * @param runtime Field runtime.
 * @param slot Resource slot index.
 * @param key Key of the text in the slot's index.
 * @param arguments Receives four bytes per code, or null.
 * @return Number of 0x401E codes.
 */
extern "C" s32 func_00465100(FieldRuntime* runtime, s32 slot, s32 key, u8* arguments)
{
    s32 count = 0;
    const u8* text = static_cast<const u8*>(func_00465340(runtime, slot, key));

    while (*text)
    {
        u16 code = *text++;

        // TODO: The game sign-extends the code before this test, which a compare with a long zero gives.
        if (code == 0L)
        {
            break;
        }

        if (code & 0x80)
        {
            code = (code & 0x7F) | (*text++ << 7);

            if (code & 0x4000)
            {
                switch (code)
                {
                case 0x4002:
                case 0x4008:
                case 0x4012:
                case 0x4013:
                case 0x401A:
                case 0x401D:
                case 0x4020:
                case 0x4021:
                case 0x4022:
                case 0x4023:
                    text++;
                    break;
                case 0x4005:
                case 0x4006:
                case 0x400A:
                case 0x400C:
                case 0x400E:
                case 0x4014:
                case 0x4015:
                    text += 4;
                    break;
                case 0x4011:
                case 0x401C:
                    while (*text)
                    {
                        text++;
                    }

                    text++;
                    break;
                case 0x401E:
                    count++;

                    if (arguments)
                    {
                        arguments[0] = text[0];
                        arguments[1] = text[1];
                        arguments[2] = text[2];
                        arguments[3] = text[3];
                        text += 4;
                        arguments += 4;
                    }
                    else
                    {
                        text += 4;
                    }

                    break;
                }
            }
        }
    }

    return count;
}

/** One entry of a resource slot's key index: a key and the offset of its data in the second section. */
struct LibResourceIndexEntry
{
    s32 key;
    s32 offset;
};

extern "C" u8 D_00505D00[];

/**
 * @brief Look a key up in a resource slot's sorted index by halving steps.
 * @param runtime Runtime that owns the slot table.
 * @param slot_index Resource slot index.
 * @param key Key to find.
 * @return The key's data in the slot's second section, or the placeholder text at D_00505D00 when it isn't there.
 */
extern "C" void* func_00465340(FieldRuntime* runtime, u32 slot_index, s32 key)
{
    void* result = D_00505D00;
    LibManagedResourceSlot* slot = &runtime->resource_slots[slot_index];
    LibResourceIndexEntry* table = reinterpret_cast<LibResourceIndexEntry*>(slot->sections[0]);
    s32 step = slot->unk30;
    LibResourceIndexEntry* end = table + step;
    step /= 2;
    LibResourceIndexEntry* entry = table + step;
    LibResourceIndexEntry* previous = 0;

    for (;;)
    {
        if (key == entry->key)
        {
            result = slot->sections[1] + entry->offset;
            break;
        }

        if (step >= 2)
        {
            step /= 2;
        }

        LibResourceIndexEntry* next;

        if (entry->key < key)
        {
            next = entry + step;

            if (next >= end)
            {
                break;
            }
        }
        else
        {
            next = entry - step;

            if (next < table)
            {
                break;
            }
        }

        if (next == previous)
        {
            break;
        }

        previous = entry;
        entry = next;
    }

    return result;
}

typedef struct LibResourceSlotOwner
{
    u8 pad00[0x14];
    LibManagedResourceSlot slots[16];
} LibResourceSlotOwner;

/**
 * @brief Queue the slot allocation for release and deactivate the resource slot.
 * @param manager Owner of the sixteen resource slots.
 * @param index Resource slot to release.
 */
extern "C" void lib_release_resource_slot(void* manager, s32 index)
{
    LibManagedResourceSlot* slot = &((LibResourceSlotOwner*)manager)->slots[index];

    if (slot->active)
    {
        if (slot->allocation)
        {
            resident_queue_allocation_release(g_resident_release_queues, slot->allocation);
            slot->allocation = 0;
        }

        slot->active = 0;
        FlushCache(0);
    }
}

extern "C" void func_00465610(void* manager, LibManagedResourceSlot* slot, void* data, void* allocation);

/**
 * @brief Find the first inactive resource slot.
 * @param manager Owner of the sixteen resource slots.
 * @return Slot, or null when all are active.
 */
static inline LibManagedResourceSlot* find_free_resource_slot(void* manager)
{
    LibManagedResourceSlot* slot = ((LibResourceSlotOwner*)manager)->slots;

    for (s32 i = 0; i < 16; i++, slot++)
    {
        if (!slot->active)
        {
            return slot;
        }
    }

    return 0;
}

/**
 * @brief Put resource data that's already in memory into a free resource slot.
 * @param manager Owner of the sixteen resource slots.
 * @param data Resource data.
 * @return The slot's identifier, or zero when no slot is free.
 */
extern "C" u16 func_004654A0(void* manager, void* data)
{
    LibManagedResourceSlot* slot = find_free_resource_slot(manager);

    if (!slot)
    {
        return 0;
    }

    func_00465610(manager, slot, data, 0);
    FlushCache(0);
    return slot->identifier;
}

/**
 * @brief Copy a resource into a new 128-byte aligned allocation and bind a free resource slot to the copy.
 * @param manager Runtime that owns the slot table.
 * @param data Resource to copy.
 * @return The slot's identifier, or zero when no slot is free or the allocation fails.
 */
extern "C" u16 func_00465520(void* manager, void* data)
{
    LibManagedResourceSlot* slot = find_free_resource_slot(manager);

    if (!slot)
    {
        return 0;
    }

    LibResourceHeader* header = static_cast<LibResourceHeader*>(data);
    u8* allocation = new (0) u8[header->size + 128];

    if (!allocation)
    {
        return 0;
    }

    void* aligned = reinterpret_cast<void*>((reinterpret_cast<u32>(allocation) + 127) & ~127);
    memcpy_guess(aligned, header, header->size);
    func_00465610(manager, slot, aligned, allocation);
    FlushCache(0);
    return slot->identifier;
}

/**
 * @brief Bind a resource slot to a resource: resolve its four section offsets and copy its header values.
 * @param manager Runtime that owns the slot table; unused.
 * @param slot Slot to fill.
 * @param data Resource header.
 * @param allocation Allocation that holds the resource when the slot owns it, otherwise null.
 */
extern "C" void func_00465610(void* manager, LibManagedResourceSlot* slot, void* data, void* allocation)
{
    LibResourceHeader* header = static_cast<LibResourceHeader*>(data);
    slot->allocation = allocation;
    slot->data = header;
    slot->sections[0] = reinterpret_cast<u8*>(header) + header->offsets[0];
    slot->sections[1] = reinterpret_cast<u8*>(header) + header->offsets[1];
    slot->sections[2] = reinterpret_cast<u8*>(header) + header->offsets[2];
    slot->sections[3] = reinterpret_cast<u8*>(header) + header->offsets[3];
    slot->unk18 = header->unk20;
    slot->unk1c = header->unk24;
    slot->unk20 = header->unk28;
    slot->unk24 = header->unk2c;
    slot->unk28 = header->unk30;
    slot->unk2c = header->unk34;
    slot->unk30 = header->unk3c;
    slot->loaded = 0;
    slot->unk48 = header->unk20;
    slot->flag = header->unk38 != 1;
    slot->active = 1;
}

/** Available transfer range in one of the runtime's sixteen resource slots. */
struct LibResourceGap {
    u8 available;
    u8 unk01[3];
    s32 start, end, size;
};

extern "C" LibManagedResourceSlot* func_004659B0(FieldRuntime*, LibResourceGap*);

extern "C" u8* func_00451C00(LibResourceHeader*, s32, s32);

extern "C" s32 lib_load_resource_slot(FieldRuntime* runtime, void* data)
{
    LibResourceHeader* source = (LibResourceHeader*)data;
    LibResourceGap gaps[16];
    LibManagedResourceSlot* slot = func_004659B0(runtime, gaps);
    s32 prefix;
    u8* remainder;
    s32 remainder_size;
    if (slot == 0)
        return 0;
    remainder = 0;
    slot->unk18 = source->unk20;
    slot->unk1c = source->unk24;
    slot->unk20 = source->unk28;
    slot->unk24 = source->unk2c;
    slot->unk28 = source->unk30;
    slot->unk2c = source->unk34;
    slot->unk30 = source->unk3c;
    slot->flag = source->unk38 != 1;
    remainder_size = 0;

    if (slot->unk18 > 0)
    {
        slot->unit_count = 1024 / slot->unk28;
        s32 required = slot->unk18 / slot->unit_count + 1;
        s32 selected = -1;
        s32 capacity = 0;
        LibResourceGap* gap = gaps;

        for (s32 i = 0; i < 16; i++, gap++)
        {
            if (gap->available)
            {
                s32 units = gap->size / slot->unk2c;

                if (capacity < required)
                {
                    if (capacity < units)
                    {
                        capacity = units;
                        selected = i;
                    }
                }
                else if (units >= required && units < capacity)
                {
                    capacity = units;
                    selected = i;
                }
            }
        }

        if (selected >= 0)
        {
            prefix = source->offsets[3];
            slot->start = gaps[selected].start;

            if (capacity >= required)
            {
                slot->loaded = source->unk20;
                slot->loaded_units = required;
                slot->unk48 = 0;
                func_00451C00(source, slot->start, slot->loaded);
            }
            else
            {
                slot->loaded = slot->unit_count * capacity;
                slot->loaded_units = capacity;
                slot->unk48 = slot->unk18 - slot->loaded;
                remainder = func_00451C00(source, slot->start, slot->loaded);
                remainder_size = source->size - (remainder - (u8*)source);
            }

            slot->end = slot->start + slot->unk2c * slot->loaded_units;
        }
        else
        {
            prefix = source->size;
            slot->loaded = 0;
            slot->unk48 = slot->unk18;
        }
    }
    else
    {
        prefix = source->size;
        slot->unk48 = 0;
        slot->loaded = 0;
    }

    u8* allocation = new (0) u8[prefix + remainder_size + 128];
    if (allocation == 0)
        return 0;
    source = (LibResourceHeader*)RESIDENT_ALIGN_RESOURCE(allocation);
    memcpy_guess(source, data, prefix);
    if (remainder_size != 0)
        memcpy_guess((u8*)source + prefix, remainder, remainder_size);
    slot->allocation = allocation;
    slot->data = source;
    slot->sections[0] = (u8*)source + source->offsets[0];
    slot->sections[1] = (u8*)source + source->offsets[1];
    slot->sections[2] = (u8*)source + source->offsets[2];
    slot->sections[3] = (u8*)source + source->offsets[3];
    slot->active = 1;
    FlushCache(0);
    return slot->identifier;
}

/**
 * @brief List the free space after each loaded resource slot and find a free slot.
 * @param runtime Runtime that owns the slot table.
 * @param gaps Sixteen entries, one per slot; each receives the gap between its slot's end and the next loaded
 *             slot's start (or the end of the resource area) and is marked available when the gap is not empty.
 * @return The first inactive slot, or null when every slot is active.
 */
extern "C" LibManagedResourceSlot* func_004659B0(FieldRuntime* runtime, LibResourceGap* gaps)
{
    LibManagedResourceSlot* free_slot = 0;
    LibManagedResourceSlot* slot = runtime->resource_slots;

    for (s32 i = 0; i < 16; i++, slot++, gaps++)
    {
        gaps->available = 0;

        if (slot->active)
        {
            if (slot->loaded > 0)
            {
                s32 start = slot->end;
                s32 end = runtime->resource_area_end;
                LibManagedResourceSlot* other = runtime->resource_slots;

                for (s32 j = 0; j < 16; j++, other++)
                {
                    if (other->active && other->loaded > 0)
                    {
                        s32 other_start = other->start;

                        if (other_start >= start && other_start < end)
                        {
                            end = other_start;
                        }
                    }
                }

                if (start != end)
                {
                    gaps->start = start;
                    gaps->end = end;
                    gaps->size = end - start;
                    gaps->available = 1;
                }
            }
        }
        else if (!free_slot)
        {
            free_slot = slot;
        }
    }

    return free_slot;
}

/**
 * @brief Remove a transform receiver from the runtime display queue and detach it from its update list.
 * @param runtime Runtime manager.
 * @param object Transform receiver.
 * @return One when it was queued, otherwise zero.
 */
extern "C" s32 func_00465A90(FieldRuntime* runtime, LibTransformOwner* object)
{
    LibRuntimeListState* list = (LibRuntimeListState*)runtime;
    LibRuntimeListNode* node = (LibRuntimeListNode*)object;

    if (!node->owner)
    {
        return 0;
    }

    node->owner = 0;
    LibRuntimeListNode* previous = node->previous;
    LibRuntimeListNode* next = node->next;

    if (!previous)
    {
        list->first = next;
    }
    else
    {
        previous->next = next;
    }

    if (!next)
    {
        list->last = previous;
    }
    else
    {
        next->previous = previous;
    }

    if (object->owner)
    {
        lib_object_detach_owner(object);
    }

    list->count--;
    return 1;
}

/**
 * @brief Append a transform receiver to the runtime display queue.
 * @param runtime Runtime manager.
 * @param object Transform receiver.
 * @return One when queued, or zero if the receiver already has an owner.
 */
extern "C" s32 lib_queue_display_object(FieldRuntime* runtime, LibTransformOwner* object)
{
    LibRuntimeListState* list = (LibRuntimeListState*)runtime;
    LibRuntimeListNode* node = (LibRuntimeListNode*)object;

    if (node->owner)
    {
        return 0;
    }

    node->owner = runtime;

    if (!list->first)
    {
        list->last = node;
        list->first = node;
        node->previous = 0;
        node->next = 0;
    }
    else
    {
        LibRuntimeListNode* last = list->last;
        last->next = node;
        node->previous = last;
        node->next = 0;
        list->last = node;
    }

    list->count++;
    return 1;
}

/** One queued display object with the keys FieldRuntime::update sorts by. */
struct FieldDisplayEntry
{
    LibCallbackTransform* object;
    s32 order;
    s32 unk08;
    s32 priority;
};

/** @brief Hand the queued display objects to the renderer, ordered by priority and then by their order value. */
void FieldRuntime::update()
{
    if (display_count <= 0)
    {
        return;
    }

    FieldDisplayEntry entries[256];
    LibCallbackTransform* object = static_cast<LibCallbackTransform*>(display_first);
    FieldDisplayEntry* entry = entries;

    for (; object; object = reinterpret_cast<LibCallbackTransform*>(reinterpret_cast<LibRuntimeListNode*>(object)->next))
    {
        if (object->owner)
        {
            lib_object_detach_owner(object);
        }

        entry->object = object;
        entry->order = object->unka4;
        entry->unk08 = object->unka0;
        entry->priority = object->unka9;
        entry++;
    }

    if (display_count >= 2)
    {
        for (s32 i = 0; i < display_count - 1; i++)
        {
            s32 j = display_count - 1;
            FieldDisplayEntry* current = &entries[j];
            FieldDisplayEntry* previous = current - 1;

            for (; j > i; j--, current--, previous--)
            {
                if (current->order < previous->order)
                {
                    LibCallbackTransform* first = previous->object;
                    s32 order = previous->order;
                    s32 unk08 = previous->unk08;
                    s32 priority = previous->priority;
                    previous->object = current->object;
                    previous->order = current->order;
                    previous->unk08 = current->unk08;
                    previous->priority = current->priority;
                    current->object = first;
                    current->order = order;
                    current->unk08 = unk08;
                    current->priority = priority;
                }
            }
        }

        for (s32 i = 0; i < display_count - 1; i++)
        {
            s32 j = display_count - 1;
            FieldDisplayEntry* current = &entries[j];
            FieldDisplayEntry* previous = current - 1;

            for (; j > i; j--, current--, previous--)
            {
                if (previous->priority < current->priority)
                {
                    LibCallbackTransform* first = previous->object;
                    s32 order = previous->order;
                    s32 unk08 = previous->unk08;
                    s32 priority = previous->priority;
                    previous->object = current->object;
                    previous->order = current->order;
                    previous->unk08 = current->unk08;
                    previous->priority = current->priority;
                    current->object = first;
                    current->order = order;
                    current->unk08 = unk08;
                    current->priority = priority;
                }
            }
        }
    }

    FieldDisplayEntry* queued = entries;

    for (s32 i = 0; i < display_count; i++, queued++)
    {
        static_cast<LibUpdateList*>(g_renderer)->append_node(queued->object, -1);
    }
}

/** @brief Hand the runtime to the release queues once, so it's deleted after the frame. */
void FieldRuntime::destroy()
{
    if (!release_queued)
    {
        resident_enqueue_object(g_resident_release_queues, this);
        release_queued = 1;
    }
}

/** @brief Destroy the queued display objects and release every loaded resource slot's allocation but the first. */
FieldRuntime::~FieldRuntime()
{
    lib_object_detach_owner(this);

    if (display_count > 0)
    {
        for (;;)
        {
            LibTransformOwner* node = static_cast<LibTransformOwner*>(display_first);

            if (!node)
            {
                break;
            }

            func_00465A90(this, node);
            node->destroy();
        }
    }

    LibManagedResourceSlot* slot = &resource_slots[1];

    for (s32 i = 1; i < 16; i++, slot++)
    {
        if (slot->active && slot->allocation)
        {
            resident_queue_allocation_release(g_resident_release_queues, slot->allocation);
            slot->allocation = 0;
        }
    }
}

extern LibUpdateList* g_update_list;


/**
 * @brief Initialize the runtime for a screen size: its screen scale, resource space, first resource slot and queues.
 * @param width Screen width.
 * @param height Screen height.
 * @param reserved_width Width of an area kept out of the resource space, or zero.
 * @param reserved_height Height of that area, or zero.
 * @param scale Scale factor.
 */
FieldRuntime::FieldRuntime(float width, float height, u16 reserved_width, u16 reserved_height, float scale)
{
    g_vram_allocator->unk14 = 0xFFD00;
    s32 display_width = g_display->display_area.width;
    s32 display_height = g_display->display_area.height;
    LibDisplayArea* area = &g_display->display_area;
    unk524 = width;
    unk528 = height;
    unk52c = display_width - 1;
    unk530 = display_height - 1;
    screen_scale_x = 16.0f * (display_width / width);
    screen_scale_y = 16.0f * (display_height / height);
    screen_offset_x = 16.0f * (GS_COORDINATE_CENTRE - display_width / 2);
    screen_offset_y = 16.0f * (GS_COORDINATE_CENTRE - display_height / 2);
    unk544 = screen_scale_x * scale;
    u32 size = display_width * display_height + area->base_width * area->base_height;
    u16 pages = 0;

    if (reserved_width > 0 && reserved_height > 0)
    {
        size = (size - reserved_width * reserved_height) & ~0x3F;
        pages = size >> 6;
    }

    unk548 = size;
    unk5fc = pages;
    size >>= 10;
    u32 end = size & ~0x1F;
    s32 low = size & 0x1F;
    s32 remainder = (low << 10) / 32 / 32;

    if (remainder == 0)
    {
        end -= 32;
        remainder = 32;
    }

    resource_area_end = end;
    unk550 = remainder;
    ResidentEntryTable* table = resident_get_entry_table(resident_get_system());
    button_map = reinterpret_cast<ButtonMap*>(resident_find_entry(table, 1));
    void** chunks = reinterpret_cast<void**>(resident_find_entry(table, 0x25466887));
    display_chunks = chunks[1];
    LibResourceHeader* header = static_cast<LibResourceHeader*>(chunks[0]);
    LibManagedResourceSlot* slot = resource_slots;

    for (s32 i = 0; i < 16; i++, slot++)
    {
        slot->identifier = i;

        if (i == 0)
        {
            slot->data = header;
            slot->sections[2] = reinterpret_cast<u8*>(header) + header->offsets[2];
            slot->sections[3] = 0;
            slot->sections[0] = 0;
            slot->sections[1] = 0;
            slot->unk18 = header->unk20;
            slot->unk1c = header->unk24;
            slot->unk20 = header->unk28;
            slot->unk24 = header->unk2c;
            slot->unk28 = header->unk30;
            slot->unk2c = header->unk34;
            slot->unk30 = 0;
            slot->loaded = slot->unk18;
            slot->unit_count = 1024 / slot->unk28;
            slot->loaded_units = slot->unk18 / slot->unit_count + 1;
            slot->start = 0;
            slot->end = slot->unk2c * slot->loaded_units;
            slot->unk48 = 0;
            slot->flag = 1;
            slot->active = 1;
        }
        else
        {
            slot->active = 0;
        }
    }

    display_last = 0;
    display_first = 0;
    display_count = 0;
    text_banks[0].resource_slot = 0;
    text_banks[0].base_key = 0;
    text_banks[1].resource_slot = 0;
    text_banks[1].base_key = 0;
    character_names = 0;
    rate = 1.0f;
    inputs[0].unk02 = 0;
    inputs[0].unk00 = 0;
    inputs[1].unk02 = 0;
    inputs[1].unk00 = 0;
    unk600 = 1;
    unk5ff = 1;
    unk5fe = 1;
    release_queued = 0;
    g_update_list->append_node(this, -1);
}

/**
 * @brief Called by the state hook when the list closes; the base does nothing.
 * @param result Chosen item number, or zero when cancelled.
 */
void LibClass174F70::func_004662A0(s32 result)
{
}

/** @brief Release the widget storage and destroy its bases. */
inline ItemCreationClass175030::~ItemCreationClass175030()
{
}

/** @brief Release the widget storage and destroy its base. */
inline ItemCreationClass172600::~ItemCreationClass172600()
{
}

/** @brief Release the widget storage and destroy its base. */
inline ItemCreationClass172870::~ItemCreationClass172870()
{
}

/** @brief Destroy the lines, the frame widgets and the container. */
LibClass174F70::~LibClass174F70()
{
}

/**
 * @brief Add a line of text from a resource slot.
 * @param slot Resource slot index.
 * @param key Key of the text in the slot.
 * @return The line's widget, or null when the lines are used up or the text can't be measured.
 */
LibTextWidget* LibClass174F70::add_item(s32 slot, u32 key)
{
    if (item_count >= item_capacity)
    {
        return 0;
    }

    LibTextWidget* item = &items[item_count];
    lib_text_set_resource(item, slot, key, 0);

    if (!lib_text_measure_bounds(item))
    {
        return 0;
    }

    item_count++;
    return item;
}

/**
 * @brief Run the list's open, select and close states: open the frame, show the items, fade in, move the cursor with
 *        the pad until an item is confirmed or the list cancelled, then fade out, hide and close.
 * @param first First update flag, unused here.
 * @param second Second update flag, unused here.
 * @param third Third update flag, unused here.
 */
void LibClass174F70::func_00412C40(bool first, bool second, bool third)
{
    if (unk13f8 == 0)
    {
        return;
    }

    switch (unk13f8)
    {
    case 1:
        if (show_frame)
        {
            unk16c.transition_state = 1;
            unk13f8++;
        }
        else
        {
            unk13f8 = 3;
        }

        break;
    case 2:
        if (unk16c.in_transition_state(0))
        {
            unk13f8++;
        }

        break;
    case 3:
    {
        LibTextWidget* item = items;

        for (s32 i = 0; i < item_capacity; i++, item++)
        {
            item->unk3d = 1;
        }

        unk1fc.unk3d = 1;
        unk250.unk3d = 1;
        unkf0.unk3d = 1;
        s32 index = unk13f0 < 0 ? 0 : unk13f0 - 1;
        float y = index * 28;
        LibTextWidget* selected = &items[index];
        unk1fc.unk18.unk04 = 16.0f + y;
        unk1fc.needs_redraw = 1;
        unk250.unk18.unk04 = 40.0f + y;
        unk250.needs_redraw = 1;
        unkf0.position.y = 30.0f + y;
        unkf0.needs_redraw = 1;
        float width = selected->extent.width;
        unk1fc.unk18.unk08 = 2.0f + width;
        unk250.unk18.unk08 = width;

        if (show_frame)
        {
            unk13f8 = 5;
        }
        else
        {
            unkE0 = 0.0f;
            unk13f8++;
        }

        break;
    }
    case 4:
    {
        float alpha = unkE0;

        alpha += 21.333334f * field_rate(g_field_runtime);

        if (!(alpha < 128.0f))
        {
            alpha = 128.0f;
            unk13f8++;
        }

        unkE0 = alpha;
        geometry_dirty = 1;
        break;
    }
    case 5:
        if (unk13f0 < 0)
        {
            unk13f0 = 1;
        }

        unk13f4 = -1;
        unk13f8++;
        break;
    case 6:
    {
        if (!unkf0.arrived)
        {
            break;
        }

        s32 index = unk13f0 < 0 ? 0 : unk13f0 - 1;
        float y = index * 28;
        LibTextWidget* selected = &items[index];
        unk1fc.unk18.unk04 = 16.0f + y;
        unk1fc.needs_redraw = 1;
        unk250.unk18.unk04 = 40.0f + y;
        unk250.needs_redraw = 1;
        unkf0.position.y = 30.0f + y;
        unkf0.needs_redraw = 1;
        float width = selected->extent.width;
        unk1fc.unk18.unk08 = 2.0f + width;
        unk250.unk18.unk08 = width;

        u16 repeat = g_field_runtime->inputs[unk13fc].unk04;
        bool moved = false;

        if (repeat & 0x10)
        {
            if (unk13f0 > 1)
            {
                unk13f0--;
            }
            else
            {
                unk13f0 = item_capacity;
            }

            moved = true;
        }
        else if (repeat & 0x40)
        {
            if (unk13f0 < item_capacity)
            {
                unk13f0++;
            }
            else
            {
                unk13f0 = 1;
            }

            moved = true;
        }

        if (moved)
        {
            resident_sound_play(g_sound, 0, 0, 0, 127, 64, 0);

            if (show_cursor)
            {
                unkf0.set_move_target(36.0f, (unk13f0 - 1) * 28 + 30, 0.05f);
            }

            break;
        }

        u16 pressed = g_field_runtime->inputs[unk13fc].unk02;

        if (pressed & g_field_runtime->button_map->buttons[0])
        {
            resident_sound_play(g_sound, 1, 0, 0, 127, 64, 0);
            unk13f4 = unk13f0;
        }
        else if (unk13fe && (pressed & g_field_runtime->button_map->buttons[1]))
        {
            resident_sound_play(g_sound, 2, 0, 0, 127, 64, 0);
            unk13f4 = 0;
        }

        if (unk13f4 >= 0)
        {
            if (unk13ff)
            {
                unk13f8 = 0;
            }
            else
            {
                unk13f8++;
            }
        }

        break;
    }
    case 7:
        if (show_frame)
        {
            unk13f8 = 9;
        }
        else
        {
            unk13f8++;
        }

        break;
    case 8:
    {
        float alpha = unkE0;

        alpha -= 21.333334f * field_rate(g_field_runtime);

        if (alpha <= 0.0f)
        {
            alpha = 0.0f;
            unk13f8++;
        }

        unkE0 = alpha;
        geometry_dirty = 1;
        break;
    }
    case 9:
        LibTextWidget* item = items;

        for (s32 i = 0; i < item_capacity; i++, item++)
        {
            item->unk3d = 0;
        }

        unk1fc.unk3d = 0;
        unk250.unk3d = 0;
        unkf0.unk3d = 0;

        if (show_frame)
        {
            unk16c.transition_state = 5;
            unk13f8++;
        }
        else
        {
            unk13f8 = 11;
        }

        break;
    case 10:
        if (unk16c.in_transition_state(0))
        {
            unk13f8++;
        }

        break;
    case 11:
        unk13f8 = 0;
        unkab = 0;
        func_004662A0(unk13f4);

        if (unk1404)
        {
            destroy();
        }

        break;
    }
}

/**
 * @brief Set the list up for up to 16 items: frame, cursor, markers and item text widgets, attached by the flags.
 * @param capacity Number of items, at most 16.
 * @param flags Bit 0x10000 hides the frame, 0x4 the cursor, 0x8 both markers; 0x2 picks the single marker over the
 *        pair; 0x20 clears unk13f8 and unkab; 0x1, 0x10 and 0x80000000 are kept as flags.
 * @param text_flag Flag passed to each item's text setup.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Frame width.
 * @param height Frame height.
 * @return 1 on success, 0 when a part can't be set up or the capacity is too large.
 */
s32 LibClass174F70::init(s32 capacity, u32 flags, u8 text_flag, float x, float y, float width, float height)
{
    if (capacity > 16)
    {
        return 0;
    }

    item_capacity = capacity;
    item_count = 0;
    unk13f4 = -1;
    unk13f0 = -1;
    unk13fc = 0;
    this->text_flag = text_flag;
    unk13fe = (flags & 0x1) != 0;
    unk13ff = (flags & 0x10) != 0;
    show_frame = (flags & 0x10000) == 0;
    show_cursor = (flags & 0x4) == 0;
    unk1404 = (flags & 0x80000000) != 0;
    bool marker = false;
    bool markers = false;

    if (!(flags & 0x8))
    {
        if (flags & 0x2)
        {
            marker = true;
        }
        else
        {
            markers = true;
        }
    }

    show_marker = marker;
    show_markers = markers;
    lib_container_init(this, 3, x, y, 0, 0.0f, 0);

    if (!unk16c.init_frame(width, height))
    {
        return 0;
    }

    if (show_frame)
    {
        lib_container_attach_widget(this, &unk16c);
    }

    if (!func_0041AD10(&unk1fc, 40.0f, 16.0f, 0.0f, 28.0f))
    {
        return 0;
    }

    if (show_markers)
    {
        lib_container_attach_widget(this, &unk1fc);
    }

    if (!lib_marker_init_rectangle(&unk250, 40.0f, 40.0f, 0.0f, 2.25f))
    {
        return 0;
    }

    if (show_marker)
    {
        lib_container_attach_widget(this, &unk250);
    }

    LibTextWidget* item = items;

    for (s32 i = 0; i < item_capacity; i++, item++)
    {
        if (!lib_text_init_resource_rectangle(item, 0, 0, this->text_flag, 0.0f, 0.0f, 0.0f, 0.0f))
        {
            return 0;
        }

        item->unk18.unk00 = 40.0f;
        item->unk18.unk04 = 16 + i * 28;
        item->needs_redraw = 1;
        lib_container_attach_widget(this, item);
    }

    if (!lib_moving_widget_init_position(&unkf0, 36.0f, 30.0f))
    {
        return 0;
    }

    if (show_cursor)
    {
        lib_container_attach_widget(this, &unkf0);
    }

    LibTextWidget* hidden = items;

    for (s32 i = 0; i < item_capacity; i++, hidden++)
    {
        hidden->unk3d = 0;
    }

    unk1fc.unk3d = 0;
    unk250.unk3d = 0;
    unkf0.unk3d = 0;

    if (flags & 0x20)
    {
        unk13f8 = 0;
        unkab = 0;
    }
    else
    {
        unk13f8 = 1;
    }

    return 1;
}

/**
 * @brief Set the movement target and reset its completion flags.
 * @param x Target horizontal coordinate.
 * @param y Target vertical coordinate.
 * @param duration Duration in seconds, converted to sixty frames per second.
 */
void LibMovementState::set_move_target(float x, float y, float duration)
{
    target.x = x;
    target.y = y;
    move_frames = 60.0f * duration;
    speed_ready = 0;
    arrived = 0;
}

/**
 * @brief Pack an XYZ2 value.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param z Depth.
 * @return XYZ2 register value.
 */
static inline u64 lib_sprite_xyz(s32 x, s32 y, s32 z)
{
    return (u64)z << 32 | ((u64)x | (u64)y << 16);
}

/**
 * @brief Rebuild the drawing packet: the 32x32 sprite at the position relative to an origin, after a half-alpha copy
 *        of it 4 pixels down and to the right.
 * @param origin Origin the position is relative to, or null for the screen's.
 * @param depth Z value of the vertices.
 * @param alpha Draw alpha, scaled by the state's own alpha over 128.
 */
void LibMovementState::func_00466E70(const LibVector4* origin, u32 depth, float alpha)
{
    u64* packet = reinterpret_cast<u64*>(unk00.dma_address);
    packet[0] = 0x70000008;
    packet[2] = GIF_TAG_NREG(14) | GIF_TAG_FLG_REGLIST | GIF_TAG_EOP | 1;
    packet[3] = 0x005353153531F077;
    packet[4] = 0x8007FF0001300000;
    packet[5] = 0x0107FF0622C10400;
    packet[6] = 0x356;
    packet[7] = 0;
    float x;
    float y;
    FieldRuntime* runtime = g_field_runtime;
    float scale_x = runtime->screen_scale_x;
    float scale_y = runtime->screen_scale_y;
    float offset_x = runtime->screen_offset_x;
    float offset_y = runtime->screen_offset_y;

    if (origin == 0)
    {
        y = 0.0f;
        x = y;
    }
    else
    {
        x = origin->x;
        y = origin->y;
    }

    x += position.x - 32.0f;
    y += position.y;
    float level = (alpha * this->alpha) / 128.0f;
    s32 left = (s32)(offset_x + x * scale_x);
    s32 right = (s32)(offset_x + (32.0f + x) * scale_x);
    s32 top = (s32)(offset_y + y * scale_y);
    s32 bottom = (s32)(offset_y + (32.0f + y) * scale_y);
    packet[8] = (u64)(s32)(0.5f * level) << 24;
    packet[9] = 0x0A080008;
    packet[10] = lib_sprite_xyz(left + 0x40, top + 0x40, depth);
    packet[11] = 0x0BF801F8;
    packet[12] = lib_sprite_xyz(right + 0x40, bottom + 0x40, depth);
    packet[13] = (u64)(s32)level << 24 | 0x808080;
    packet[14] = 0x0A080008;
    packet[15] = lib_sprite_xyz(left, top, depth);
    packet[16] = 0x0BF801F8;
    packet[17] = lib_sprite_xyz(right, bottom, depth);
}

/**
 * @brief Measure an offset's length from the absolute values of its components.
 * @param x Horizontal offset.
 * @param y Vertical offset.
 * @return Length.
 */
static inline float movement_length(float x, float y)
{
    float abs_x = ee_abs(x);
    float abs_y = __s_abs(y);
    float squared = abs_x * abs_x + abs_y * abs_y;
    return __sqrt(squared, squared);
}

/**
 * @brief Move towards the target by the speed scaled by the frame rate, arriving once within a quarter pixel.
 * @return Whether the position changed.
 */
bool LibMovementState::step()
{
    bool changed = false;

    if (!arrived)
    {
        for (s32 moved = 0;; moved++)
        {
            float dx = target.x - position.x;
            float dy = target.y - position.y;
            float distance = __s_abs(movement_length(dx, dy));

            if (!(distance < 0.25f))
            {
                if (moved)
                {
                    break;
                }

                if (!speed_ready)
                {
                    speed = distance / move_frames;
                    speed_ready++;
                }

                float step = speed * field_rate(g_field_runtime);

                if (!(step <= distance))
                {
                    step = distance;
                }

                float angle = func_00142148(dy, dx);

                position.x += step * lib_cosine_degree9(angle);
                position.y += step * lib_sine_degree9(angle);
            }
            else
            {
                arrived = 1;
                on_arrived();
                break;
            }
        }
    }

    if (position.x != previous_position.x || position.y != previous_position.y)
    {
        changed = true;
    }

    previous_position = position;
    return changed;
}

/**
 * @brief Allocate the drawing storage and show the state at a position at full alpha.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @return One on success, or zero when the storage couldn't be allocated.
 */
s32 LibMovementState::init_position(float x, float y)
{
    if (!lib_allocate_drawing_storage(&unk00, 0x12))
    {
        return 0;
    }

    position.x = x;
    position.y = y;
    alpha = 128.0f;
    speed_ready = 0;
    arrived = 1;
    return 1;
}

/** @brief Build the packet once, at the container's position, and point the widget's packet at it. */
void ItemCreationClass175030::draw()
{
    if (!unk3b)
    {
        LibContainer* owner = container;
        LibCallbackTransform& transform = *owner;

        func_00466E70(&transform.translation, transform.unka4 + unk34, owner->unkE0);
        packet = packet_tag = reinterpret_cast<u64*>(unk00.dma_address);
        unk3b = 1;
    }
}

/** @brief Move one step and redraw when the position changed. */
void ItemCreationClass175030::func_00413D20()
{
    if (step())
    {
        needs_redraw = 1;
    }
}

typedef struct LibFieldWidgetState
{
    u8 pad00[0x34];
    u32 unk34;
    u8 pad38;
    u8 unk39;
    u8 pad3a[6];
    LibMovementState movement;
} LibFieldWidgetState;

/**
 * @brief Initialize the moving widget storage and position, then set its drawing flags.
 * @param object Moving widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @return One on success, or zero when storage initialization fails.
 */
extern "C" s32 lib_moving_widget_init_position(LibClass175030* object, float x, float y)
{
    LibFieldWidgetState* state = (LibFieldWidgetState*)object;

    if (!state->movement.init_position(x, y))
    {
        return 0;
    }

    state->unk34 = 8;
    state->unk39 = 1;
    return 1;
}

// TODO: The cursor's destructor inlines LibCallbackTransform's (which text_0044ABE0 keeps out of line) but not
// LibClass172000's, so the base destructor is only inline in this unit and the inline depth is one here.
inline LibCallbackTransform::~LibCallbackTransform()
{
}

#pragma push
#pragma inline_depth(1)

LibSelectionCursor::~LibSelectionCursor()
{
}

#pragma pop

/**
 * @brief Finish the cursor's drawing packet.
 * @param value Notification word.
 */
void LibSelectionCursor::on_packet_complete(u32 value)
{
    lib_finish_packet(this);
}

/** @brief Mark the DMA pending and queue the cursor's packet. */
void LibSelectionCursor::render()
{
    dma_pending = 1;
    func_00461830(&this->LibMovementState::unk00, static_cast<LibDmaCallbacks*>(this));
}

/**
 * @brief Move the cursor one step and redraw it when asked.
 * @param first Nothing happens unless set.
 * @param second Step the movement; a changed position marks the geometry dirty.
 * @param third Rebuild the packet if the geometry is dirty, then mark the cursor for drawing.
 */
void LibSelectionCursor::func_0044B100(bool first, bool second, bool third)
{
    if (!first)
    {
        return;
    }

    if (second && step())
    {
        geometry_dirty = 1;
    }

    if (third)
    {
        if (geometry_dirty)
        {
            func_00466E70(0, unka4, 128.0f);
        }

        unk63 = 1;
    }
}

/**
 * @brief Reset the translation, set the drawing codes and depth, and place the cursor.
 * @param code Drawing code.
 * @param first First drawing value.
 * @param second Second drawing value.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param z Depth.
 */
void LibSelectionCursor::init(s32 code, u32 first, u32 second, float x, float y, float z)
{
    translation.x = 0.0f;
    translation.y = 0.0f;
    translation.z = 0.0f;
    translation.w = 1.0f;
    set_codes_and_z(code, first, z, second, 0);
    init_position(x, y);
}

/** @brief Release the widget storage and destroy its base. */
ItemCreationClass175110::~ItemCreationClass175110()
{
}

/** @brief Draw the animation's current frame into the widget's packet. */
void ItemCreationClass175110::draw()
{
    if (unkc0 < 0 && !unkb4)
    {
        unk3b = 0;
        return;
    }

    if (unk3b)
    {
        return;
    }

    unk50.set_position(unk18.unk00, unk18.unk04);
    unk50.unk50 = draw_alpha;
    u64* start = reinterpret_cast<u64*>(unk40.dma_address);
    u64* cursor = start;
    packet_tag = start;
    packet = start;
    cursor += 2;
    LibContainer* owner = container;
    LibCallbackTransform& transform = *owner;

    func_004535B0(&unk50, &cursor, &transform.translation, transform.unka4 + unk34, owner->unkE0, 0);
    *packet_tag = DMA_TAG((reinterpret_cast<u32>(cursor) - reinterpret_cast<u32>(packet_tag) - LIB_DRAW_QWORD_SIZE) / LIB_DRAW_QWORD_SIZE, DMA_TAG_ID_END, 0);
    unk3b = 1;
}

/** @brief Restart the animation when its resource changed, otherwise step it and redraw on a frame change. */
void ItemCreationClass175110::func_00413D20()
{
    if (unkc0 < 0 && !unkb4)
    {
        return;
    }

    if (unkc9)
    {
        if (!unkb4)
        {
            unk50.set_display_chunk(unkc0);
        }
        else
        {
            unk50.set_resource(unkb4, &unkb8);
        }

        unk50.start(unkc4);
        unkc9 = 0;
    }
    else if (!unkc8 && unk50.step())
    {
        needs_redraw = 1;
    }
}

/**
 * @brief Set the animated image widget up: its position, drawing storage, resource and image format.
 * @param object Widget to set up.
 * @param resource Resource identifier, or negative for none.
 * @param source Image source, or null.
 * @param format Image format to copy, or null to keep the widget's.
 * @param first Value stored at unkc4.
 * @param second Value stored at unkc8.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @return One on success, or zero when the drawing storage can't be allocated.
 */
extern "C" s32 func_00467800(ItemCreationClass175110* object, s32 resource, void* source, const LibImageFormat* format, u32 first, u8 second, float x, float y)
{
    object->unk18.unk00 = x;
    object->unk18.unk04 = y;

    if (!lib_allocate_drawing_storage(&object->unk40, 16))
    {
        return 0;
    }

    object->unkc0 = resource;
    object->unkb4 = source;

    if (format)
    {
        object->unkb8 = *format;
    }

    object->unkc4 = first;
    object->unkc8 = second;
    object->unkc9 = 1;
    object->unk34 = 6;
    object->unk39 = 1;
    return 1;
}

/** @brief Destroy the label. */
LibStringLabel::~LibStringLabel()
{
}

/**
 * @brief Lay the label's string out off screen and measure it.
 * @param object Label to measure.
 * @return Extent of the laid-out string.
 */
LibTextExtent* func_00467950(LibStringLabel* object)
{
    LibDrawRecord records[0x40];
    object->begin_layout(records, 0.0f);
    object->add_text(object->text);
    object->func_004637A0(records, object->record_count);
    object->align_records_vertically(records, object->record_count);
    return &object->extent;
}

/**
 * @brief Count the character codes in the label's string.
 * @param object Label to read.
 * @return Number of codes.
 */
s32 func_004679B0(LibStringLabel* object)
{
    u16 codes[0x80];
    return func_00464040(object, codes, object->text);
}

/** @brief Lay the text out in the scratchpad and draw it, once. */
void LibStringLabel::draw()
{
    if (text == 0)
    {
        unk3b = 0;
        return;
    }

    if (!unk3b)
    {
        lib_restore_texture_cache(static_cast<LibRenderer*>(g_renderer));
        LibDrawRecord* records = reinterpret_cast<LibDrawRecord*>(0x70000000);
        begin_layout(records, 0.0f);
        add_text(text);
        func_004637A0(records, record_count);
        align_records_vertically(records, record_count);
        draw_records(records, record_count);
        unk3b = 1;
    }
}

/**
 * @brief Configure the drawing rectangle and string.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Drawing width.
 * @param height Drawing height.
 * @param value String to draw.
 * @param flag Drawing flag.
 * @return One on success, or zero when the drawing storage couldn't be set up.
 */
s32 LibStringLabel::init_text_rectangle(float x, float y, float width, float height, const char* value, u8 flag)
{
    unkf8 = flag;
    set_rectangle(x, y, width, height);
    resource_slot = g_field_runtime->resource_slots;

    if (!allocate_storage(32, 0, 0, 0))
    {
        return 0;
    }

    text = value;
    unk39 = 1;
    return 1;
}

/** @brief Lay the twenty cells out on two arcs around the centre cell and draw them, the back arc first. */
void LibClass175170::draw()
{
    if (!unk894)
    {
        unk3b = 0;
        return;
    }

    if (unk3b)
    {
        return;
    }

    LibImageAnimation* cell = &cells[0][0];
    float tilt_cos = lib_cosine_degree9(-0.7853982f);
    float tilt_sin = lib_sine_degree9(-0.7853982f);
    float angle = -unk884;
    float limit = -180.0f;
    float step = 12.5f;

    for (s32 side = 0; side < 2; side++)
    {
        for (s32 i = 0; i < 10; i++)
        {
            float radians = (3.1415927f * angle) / 180.0f;
            float x = 18.0f * lib_cosine_degree9(radians);
            float y = 8.0f * lib_sine_degree9(radians);
            cell->unk18 = x * tilt_cos - y * tilt_sin;
            cell->unk1c = x * tilt_sin + y * tilt_cos;
            float scale = unk888 - 0.06f * (float)i;

            if (scale < 0.0f)
            {
                scale = 0.0f;
            }

            cell->unk34 = scale;
            cell->unk30 = scale;
            cell->unk60 = (float)((s32)angle % 360) >= limit;
            cell->unk50 = draw_alpha;
            angle += step;
            cell++;
        }

        tilt_sin = -tilt_sin;
        limit = -limit;
        step = -step;
        angle = 180.0f + unk884;
    }

    unk50.unk50 = draw_alpha;
    u64* start = reinterpret_cast<u64*>(unk40.dma_address);
    u64* cursor = start;
    packet_tag = start;
    packet = start;
    cursor += 2;
    LibContainer* owner = container;
    LibVector4 origin;
    origin.x = owner->translation.x + unk18.unk00;
    origin.y = owner->translation.y + unk18.unk04;
    owner = container;
    u32 depth = owner->unka4 + unk34;
    float scale = owner->unkE0;
    *cursor++ = GIF_TAG_NREG(1) | GIF_TAG_EOP | 1;
    *cursor++ = GIF_REGISTER_AD;
    *cursor++ = 0x48;
    *cursor++ = GS_REGISTER_ALPHA_2;
    LibImageAnimation* front_cell = &cells[0][0];

    for (s32 i = 0; i < 20; i++, front_cell++)
    {
        if (front_cell->unk60)
        {
            func_004535B0(front_cell, &cursor, &origin, depth, scale, 0);
        }
    }

    *cursor++ = GIF_TAG_NREG(1) | GIF_TAG_EOP | 1;
    *cursor++ = GIF_REGISTER_AD;
    *cursor++ = GS_ALPHA_NORMAL;
    *cursor++ = GS_REGISTER_ALPHA_2;
    func_004535B0(&unk50, &cursor, &origin, depth, scale, 0);
    *cursor++ = GIF_TAG_NREG(1) | GIF_TAG_EOP | 1;
    *cursor++ = GIF_REGISTER_AD;
    *cursor++ = 0x48;
    *cursor++ = GS_REGISTER_ALPHA_2;
    LibImageAnimation* back_cell = &cells[0][0];

    for (s32 i = 0; i < 20; i++, back_cell++)
    {
        if (!back_cell->unk60)
        {
            func_004535B0(back_cell, &cursor, &origin, depth, scale, 0);
        }
    }

    *cursor++ = GIF_TAG_NREG(1) | GIF_TAG_EOP | 1;
    *cursor++ = GIF_REGISTER_AD;
    *cursor++ = GS_ALPHA_NORMAL;
    *cursor++ = GS_REGISTER_ALPHA_2;
    *packet_tag = DMA_TAG((reinterpret_cast<u32>(cursor) - reinterpret_cast<u32>(packet_tag) - LIB_DRAW_QWORD_SIZE) / LIB_DRAW_QWORD_SIZE, DMA_TAG_ID_END, 0);
    unk3b = 1;
}

/** @brief Fade the widget in or out while it opens or closes, and turn the rings while it shows. */
void LibClass175170::func_00413D20()
{
    if (unk890)
    {
        if (unk88c == 0)
        {
            if (unk890 == 1)
            {
                unk888 = 0.0f;
                draw_alpha = 0.0f;
                unk894 = 1;
                unk890++;
            }

            unk888 += 0.12f * field_rate(g_field_runtime);
            draw_alpha += 17.066668f * field_rate(g_field_runtime);

            if (!(draw_alpha < 128.0f))
            {
                draw_alpha = 128.0f;
                unk890 = 0;
            }
        }
        else
        {
            unk888 -= 0.12f * field_rate(g_field_runtime);
            draw_alpha -= 17.066668f * field_rate(g_field_runtime);

            if (draw_alpha <= 0.0f)
            {
                unk894 = 0;
                unk890 = 0;
            }
        }
    }

    if (unk894)
    {
        unk884 += 5.0f * field_rate(g_field_runtime);

        if (!(unk884 <= 360.0f))
        {
            unk884 -= 360.0f;
        }

        unk50.step();
        needs_redraw = 1;
    }
}

/**
 * @brief Place the widget and set up its animations: the main one from display chunk 0x43, then two rows of ten
 *        cells from chunk 0x44 in the two row colors.
 * @param object Widget to set up.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @return 1 on success, 0 when the drawing storage can't be allocated.
 */
extern "C" s32 func_00468230(LibClass175170* object, float x, float y)
{
    object->unk18.unk00 = x;
    object->unk18.unk04 = y;

    if (!lib_allocate_drawing_storage(&object->unk40, 0x138))
    {
        return 0;
    }

    object->unk50.set_display_chunk(0x43);
    object->unk50.start(0);
    object->unk50.unk20 = 12.0f;
    object->unk50.unk24 = 12.0f;

    LibImageAnimation* cell = object->cells[0];

    for (s32 row = 0; row < 2; row++)
    {
        for (s32 column = 0; column < 10; column++, cell++)
        {
            cell->set_display_chunk(0x44);
            cell->start(0);
            cell->unk20 = 4.0f;
            cell->unk24 = 4.0f;

            if (row == 0)
            {
                cell->unk44 = 128.0f;
                cell->unk48 = 28.0f;
                cell->unk4c = 28.0f;
            }
            else
            {
                cell->unk44 = 40.0f;
                cell->unk48 = 40.0f;
                cell->unk4c = 128.0f;
            }
        }
    }

    object->unk884 = 0;
    object->unk890 = 0;
    object->unk894 = 0;
    object->unk34 = 7;
    object->unk39 = 1;
    return 1;
}

/**
 * @brief Report the model's list kind.
 * @return Seven.
 */
s32 LibObject1751A0::get_default_list_kind()
{
    return 7;
}

/**
 * @brief Resolve an offset; this model has none.
 * @param offset Offset to resolve.
 * @return Null.
 */
void* LibObject1751A0::resolve_offset(const u32* offset)
{
    return 0;
}

/**
 * @brief Return the image record while an image is set.
 * @return The record, or null.
 */
void* LibObject1751A0::get_data()
{
    if (image != 0)
    {
        return &record;
    }

    return 0;
}

/** Next phase handed out by LibObject1751A0::set_phase_period. */
extern "C" u8 D_001B6580;

/**
 * @brief Take the next phase of a shared counter that cycles through a period.
 * @param period Period length; zero leaves the counter alone.
 */
void LibObject1751A0::set_phase_period(u8 period)
{
    phase_period = period;
    phase = D_001B6580;

    if (period)
    {
        D_001B6580 = (D_001B6580 + 1) % period;
    }
}

/**
 * @brief Bind the renderer's first pass target (LATF image 1) as the model's texture and point the setup packet's
 *        TEX0 registers at it.
 */
void LibObject1751A0::func_004683E0()
{
    void* data = &record;

    if (record.resolved_data == 0)
    {
        data = func_00448A10(&static_cast<LibRenderResource&>(*this), LIB_TEXTURE_TAG_LATF, 1);
        record.resolved_data = reinterpret_cast<u32>(data);
    }

    if (data != 0)
    {
        g_texture_cache->find_texture(0, LIB_TEXTURE_TAG_LATF, 1, 0, 1, 0, 0);
    }

    LibImageSetupPacket* packet = reinterpret_cast<LibImageSetupPacket*>(reinterpret_cast<u32>(&setup) | EE_UNCACHED_ACCELERATED);
    u64 tex0 = (packet->texture_2_data & 0x0000001FFC000000ULL) | g_texture_cache->entries[g_texture_cache->slot_entries[0]].tex0 | (4ULL << 32);

    switch ((s32)((g_texture_cache->entries[g_texture_cache->slot_entries[0]].tex0 >> 20) & 0x3F))
    {
    case GS_PSMT4:
        packet->texture_2_data = tex0 | (g_texture_cache->cluts[g_texture_cache->clut_slot_entries[0]].tex0 | (u64)(u32)image->unk02 << 56);
        packet->texture_data = g_texture_cache->cluts[g_texture_cache->clut_slot_entries[0]].tex0 | 0x4000000621300000ULL;
        break;
    case GS_PSMT8:
        packet->texture_2_data = tex0 | g_texture_cache->cluts[g_texture_cache->clut_slot_entries[0]].tex0;
        packet->texture_data = g_texture_cache->cluts[g_texture_cache->clut_slot_entries[0]].tex0 | 0x4000000621300000ULL;
        break;
    default:
        packet->texture_data = tex0;
        packet->texture_2_data = tex0;
        break;
    }
}

/**
 * @brief Get the record a by-key image record refers to, looking it up by its two keys the first time.
 * @param object Model holding the record.
 * @return The record holding the image, or null when none is registered yet.
 */
static inline ResidentRenderDataRecord* lib_image_model_resolved_record(LibObject1751A0* object)
{
    ResidentRenderDataRecord* found = reinterpret_cast<ResidentRenderDataRecord*>(object->record.resolved_data);

    if (found == 0)
    {
        found = static_cast<ResidentRenderDataRecord*>(
            func_00448A10(&static_cast<LibRenderResource&>(*object), object->record.key08, object->record.key0c));
        object->record.resolved_data = reinterpret_cast<u32>(found);
        return found;
    }

    return found;
}

/**
 * @brief Load the image record's texture and palette into the texture cache if they are not there yet, then point
 *        the setup packet's TEX0 registers at slot 0's texture.
 */
void LibObject1751A0::bind_texture()
{
    ResidentRenderDataRecord* current = &record;
    s16 kind = record.storage_kind;

    if (kind == 1)
    {
        current = lib_image_model_resolved_record(this);

        if (current != 0)
        {
            kind = current->storage_kind;
        }
    }
    else if (kind == 4)
    {
        current->storage_kind = 0;
        kind = 0;
        current->data = reinterpret_cast<u8*>(current) + reinterpret_cast<u32>(current->data);
        current->resolved_data = reinterpret_cast<u32>(current->data);
    }

    if ((kind == 0 || kind == 5) && current != 0)
    {
        LibImageHeader* image;

        if (current->data != 0)
        {
            image = reinterpret_cast<LibImageHeader*>(current->data);
        }
        else
        {
            image = reinterpret_cast<LibImageHeader*>(reinterpret_cast<u8*>(current) + 0x40);
        }

        LibImageInfo* info = reinterpret_cast<LibImageInfo*>(reinterpret_cast<u8*>(image) + image->image_offset);

        if (g_texture_cache->func_004A6D20(image, 0, reinterpret_cast<LibTextureUser*>(current)))
        {
            u32 address = func_004A7100(g_texture_cache, reinterpret_cast<LibTextureRequest*>(info), *reinterpret_cast<u32*>(image->name),
                                        image->id, 0, image->flags, reinterpret_cast<LibTextureUser*>(current));

            if (address == 1)
            {
                g_texture_cache->release_unstamped();
                address = func_004A7100(g_texture_cache, reinterpret_cast<LibTextureRequest*>(info), *reinterpret_cast<u32*>(image->name),
                                        image->id, 0, image->flags, reinterpret_cast<LibTextureUser*>(current));

                if (address == 1)
                {
                    address = 0;
                }
            }

            u64 bitbltbuf = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(image) + info->pixel_offset + 0x20);
            record.unk10[0] = (bitbltbuf & ~(0x3FFFULL << 32)) | (((u64)address >> 6) << 32);
            unkae3 |= 1;
        }

        if (image->unk02)
        {
            u8* palette = reinterpret_cast<u8*>(image) + image->palette_offset;
            u32 clut = g_texture_cache->func_004A6EA0(image, 0, 0);

            if (clut != 0)
            {
                record.unk10[1] = (*reinterpret_cast<u64*>(palette + 0x20) & ~(0x3FFFULL << 32)) | (((u64)clut >> 6) << 32);
                unkae3 |= 4;
            }
        }
    }

    LibImageSetupPacket* packet = reinterpret_cast<LibImageSetupPacket*>(reinterpret_cast<u32>(&setup) | EE_UNCACHED_ACCELERATED);
    u64 tex0 = (packet->texture_2_data & 0x0000001FFC000000ULL) | g_texture_cache->entries[g_texture_cache->slot_entries[0]].tex0 | (4ULL << 32);

    switch ((s32)((g_texture_cache->entries[g_texture_cache->slot_entries[0]].tex0 >> 20) & 0x3F))
    {
    case GS_PSMT4:
        packet->texture_2_data = tex0 | (g_texture_cache->cluts[g_texture_cache->clut_slot_entries[0]].tex0 | (u64)(u32)this->image->unk02 << 56);
        packet->texture_data = g_texture_cache->cluts[g_texture_cache->clut_slot_entries[0]].tex0 | 0x4000000621300000ULL;
        break;
    case GS_PSMT8:
        packet->texture_2_data = tex0 | g_texture_cache->cluts[g_texture_cache->clut_slot_entries[0]].tex0;
        packet->texture_data = g_texture_cache->cluts[g_texture_cache->clut_slot_entries[0]].tex0 | 0x4000000621300000ULL;
        break;
    default:
        packet->texture_data = tex0;
        packet->texture_2_data = tex0;
        break;
    }
}

/**
 * @brief Claim the next free cell of the referenced grid, searching on from next_cell, and place it.
 * @param position Position to give the cell.
 * @param cell Receives the cell.
 * @param value Receives the grid's value for the cell, when not null.
 * @return The cell index, or -1 when there is no grid or every cell is taken.
 */
s32 LibObject1751A0::claim_cell(const LibVector4* position, LibClass174228** cell, s32* value)
{
    if (reference == 0)
    {
        return -1;
    }

    s32 count = reference->func_slot34();
    LibGridBitset* used = reference->func_slot30();
    LibClass174228* claimed;

    for (s32 i = 0; i < count; i++)
    {
        s32 index = next_cell;
        // TODO: bits holds the word array before the word; a pointer local of its own swaps two registers.
        u64 bits = (u64)used->bits;
        u64* word = (u64*)bits + ((u32)index >> 6);
        bits = *word;
        u32 bit = index & 0x3F;

        if (!((bits >> bit) & 1))
        {
            *word = bits | ((u64)1 << bit);
            reference->func_slot38();
            claimed = reference->func_slot1c(next_cell);

            if (value)
            {
                *value = reference->func_slot20(next_cell);
            }

            *cell = claimed;
            claimed->unk10.packed = *(const unsigned __int128*)position;

            if (++next_cell >= count)
            {
                next_cell = 0;
            }

            unkada[0] = 1;
            unkada[1] = 1;
            return index;
        }

        if (++next_cell >= count)
        {
            next_cell = 0;
        }
    }

    return -1;
}

/**
 * @brief Make a copy of this model that stays linked to it.
 * @return The copy, or null.
 */
LibTransformOwner* LibObject1751A0::clone()
{
    LibObject1751A0* copy = new (0) LibObject1751A0;

    if (copy == 0)
    {
        return 0;
    }

    copy->copy_image_state(this);
    add_clone(copy);
    lib_object_set_list_kind(this, LIB_LIST_KIND_LATE_MODEL);
    return copy;
}

/**
 * @brief Copy another model's image state.
 * @param model Model to copy.
 */
void LibObject1751A0::copy_image_state(LibObject1751A0* model)
{
    unkaa4 = model->unkaa4;
    unkadf = model->unkadf;
    unkabc = model->unkabc;
    unkac0 = model->unkac0;
    unkae0 = model->unkae0;
    image = model->image;
    unkae6 = model->unkae6;
    unkac4 = model->unkac4;
    copied = 1;
    source = model;

    if (image)
    {
        record.data = model->record.data;
        record.storage_kind = model->record.storage_kind;
        record.resolved_data = 0;
        record.next_offset = 0;
        reset_texture_uploads();
        setup = model->setup;
    }

    hold_reference(model->reference);
    diagonal = model->diagonal;
    unkade = model->unkade;
    unkadd = model->unkadd;
    kind = model->kind;
    unkae2 = model->unkae2;
    LibColorModel::copy_color_state(model);

    if (unka90[0] == 0)
    {
        allocate_packets();
    }

    unk59d_0 = 1;
}

/**
 * @brief Turn fogging on or off in the model's packet.
 * @param enabled Nonzero for fog.
 */
void LibObject1751A0::set_fog_enabled(u8 enabled)
{
    if (packet != 0 && fog_enabled != enabled)
    {
        unk59d_0 = 1;
        LibImagePacket* uncached = reinterpret_cast<LibImagePacket*>(reinterpret_cast<u32>(packet) | UNCACHED_SEGMENT);

        if (enabled)
        {
            uncached->primitive_tag_words[1] |= GIF_TAG_HIGH_PRIM_FGE;
        }
        else
        {
            uncached->primitive_tag_words[1] &= ~GIF_TAG_HIGH_PRIM_FGE;
        }

        fog_enabled = enabled;
    }
}

/**
 * @brief Set the primitive the model draws, its blend mode and the packet values that go with them.
 * @param primitive Primitive kind, 0 to 6.
 * @param value Value stored in the packet and at unkade.
 * @param blend Blend mode; nonzero also turns alpha blending on in the primitive.
 * @param unk54 Value stored in the packet at 0x54.
 */
void LibObject1751A0::set_primitive(s32 primitive, u8 value, s32 blend, float unk54)
{
    kind = primitive;

    if (unka90[0] == 0)
    {
        allocate_packets();
    }

    if (unka90[0] != 0 && packet != 0)
    {
        LibImagePacket* uncached = reinterpret_cast<LibImagePacket*>(reinterpret_cast<u32>(packet) | EE_UNCACHED_ACCELERATED);
        uncached->unpack = VIF_UNPACK(VIF_UNPACK_V4_32, 0xE, 0x60);
        uncached->unk54 = unk54;
        uncached->unk24 = value;
        unkade = value;

        if (image)
        {
            for (s32 i = 0; i < image->flag_count; i++)
            {
                if (image->flags[i])
                {
                    unkae2 = 1;
                    break;
                }
            }
        }
        else
        {
            unkae2 = blend;
        }

        uncached->alpha = D_004ED320[blend];
        uncached->alpha_address = GS_REGISTER_ALPHA_1;

        if (blend)
        {
            uncached->unk2c = 1;
        }

        uncached->gif_tag = 4 | GIF_TAG_EOP | GIF_TAG_NREG(1);
        uncached->gif_registers = LIB_DRAW_AD_REGISTERS;

        switch (primitive)
        {
        case 0:
            uncached->primitive_tag = GIF_TAG_EOP | GIF_TAG_PRE | GIF_TAG_PRIM((u32)(blend ? GS_PRIM_ABE : 0)) | GIF_TAG_NREG(2);
            uncached->primitive_registers = 0x41;
            break;
        case 1:
            uncached->primitive_tag = GIF_TAG_EOP | GIF_TAG_PRE | GIF_TAG_PRIM((u32)(blend ? GS_PRIM_ABE : 0) | 0xA) | GIF_TAG_NREG(2);
            uncached->primitive_registers = 0x41;
            break;
        case 2:
            uncached->primitive_tag = GIF_TAG_EOP | GIF_TAG_PRE | GIF_TAG_PRIM((u32)(blend ? GS_PRIM_ABE : 0) | 0xC) | GIF_TAG_NREG(2);
            uncached->primitive_registers = 0x41;
            break;
        case 3:
            uncached->primitive_tag = GIF_TAG_EOP | GIF_TAG_PRE | GIF_TAG_PRIM(0x54) | GIF_TAG_NREG(3);
            uncached->primitive_registers = 0x412;
            break;
        case 4:
            uncached->primitive_tag = GIF_TAG_EOP | GIF_TAG_PRE | GIF_TAG_PRIM(0x5C) | GIF_TAG_NREG(3);
            uncached->primitive_registers = 0x412;
            break;
        case 5:
            uncached->primitive_tag = GIF_TAG_EOP | GIF_TAG_PRE | GIF_TAG_PRIM((u32)(blend ? GS_PRIM_ABE : 0) | 0x14) | GIF_TAG_NREG(3);
            uncached->primitive_registers = 0x412;
            break;
        case 6:
            uncached->primitive_tag = GIF_TAG_EOP | GIF_TAG_PRE | GIF_TAG_PRIM(0x54) | GIF_TAG_NREG(3);
            uncached->primitive_registers = 0x412;
            break;
        }

        if (fog_enabled)
        {
            uncached->primitive_tag_words[1] |= GIF_TAG_HIGH_PRIM_FGE;
        }

        unk59d_0 = 1;
    }
}

/**
 * @brief Write the image model's DMA chain into the free buffer: the kind's microprogram, the texture and palette
 *        uploads bind_texture marked dirty and the setup packet, then the cell packet calls when the cell count
 *        changed.
 */
void LibObject1751A0::build_dma_chain()
{
    s32 index;

    if (copied)
    {
        index = (u8)!source->unkadd;
    }
    else
    {
        index = (u8)!unkadd;
    }

    u64* cursor = reinterpret_cast<u64*>((reinterpret_cast<u32>(unka8c) + 0x40) | EE_UNCACHED_ACCELERATED);
    u64* tail = reinterpret_cast<u64*>((reinterpret_cast<u32>(unka84[index]) + 0x40) | EE_UNCACHED_ACCELERATED);
    chain_address = reinterpret_cast<u32>(&chains[index]);
    s32 program;
    u32 first_call;
    u32 next_call;

    // TODO: Every case recomputes both microprogram addresses, like LibModel::func_slotF0; maybe they came from a macro.
    switch (kind)
    {
    case 0:
        program = 3;
        first_call = reinterpret_cast<u32>(D_6E0) >> 3;
        next_call = reinterpret_cast<u32>(D_818) >> 3;
        break;
    case 1:
        program = 4;
        first_call = reinterpret_cast<u32>(D_6E0) >> 3;
        next_call = reinterpret_cast<u32>(D_818) >> 3;
        break;
    case 2:
        program = 5;
        first_call = reinterpret_cast<u32>(D_6E0) >> 3;
        next_call = reinterpret_cast<u32>(D_818) >> 3;
        break;
    case 3:
        program = 6;
        first_call = reinterpret_cast<u32>(D_6E0) >> 3;
        next_call = reinterpret_cast<u32>(D_818) >> 3;
        break;
    case 4:
        program = 7;
        first_call = reinterpret_cast<u32>(D_6E0) >> 3;
        next_call = reinterpret_cast<u32>(D_818) >> 3;
        break;
    case 5:
        program = 8;
        first_call = reinterpret_cast<u32>(D_6E0) >> 3;
        next_call = reinterpret_cast<u32>(D_818) >> 3;
        break;
    case 6:
        program = 9;
        first_call = reinterpret_cast<u32>(D_6E0) >> 3;
        next_call = reinterpret_cast<u32>(D_818) >> 3;
        break;
    }

    if (g_microcode_loader->select_program(program))
    {
        *cursor = g_microcode_loader->get_program_tag(program);
        cursor += 2;
    }

    cursor[0] = DMA_TAG(1, DMA_TAG_ID_CNT, 0);
    *(unsigned __int128*)(cursor + 2) = 0;
    reinterpret_cast<u32*>(cursor)[7] = 0x06008000;
    cursor += 4;

    if (image)
    {
        ResidentRenderDataRecord* own = &record;
        s16 storage = own->storage_kind;
        LibImageHeader* header;
        s32 uploaded = 0;
        ResidentRenderDataRecord* current = own;

        if (storage == 1)
        {
            current = reinterpret_cast<ResidentRenderDataRecord*>(own->resolved_data);

            if (current != 0)
            {
                storage = 0;
            }
        }

        if (storage == 0 || storage == 5)
        {
            if (current->data != 0)
            {
                header = reinterpret_cast<LibImageHeader*>(current->data);
            }
            else
            {
                header = reinterpret_cast<LibImageHeader*>(reinterpret_cast<u8*>(current) + 0x40);
            }

            if (unkae3 & 1)
            {
                unkae3 &= ~1;
                LibImageInfo* info = reinterpret_cast<LibImageInfo*>(reinterpret_cast<u8*>(header) + header->image_offset);
                LibTextureUpload* upload = reinterpret_cast<LibTextureUpload*>(reinterpret_cast<u32>(&texture_uploads[1]) | EE_UNCACHED_ACCELERATED);
                LibTextureUpload* packet = reinterpret_cast<LibTextureUpload*>(reinterpret_cast<u8*>(header) + info->pixel_offset);

                if (!(unkae3 & 2))
                {
                    unsigned __int128 bitbltbuf;
                    unsigned __int128 trxreg;
                    unsigned __int128 image_tag;
                    u64 unk68;

                    bitbltbuf = *(unsigned __int128*)&packet->bitbltbuf;
                    trxreg = *(unsigned __int128*)&packet->trxreg;
                    unk68 = *(u64*)&packet->unk64[4];
                    image_tag = *(unsigned __int128*)&packet->unk64[0xC];
                    *(unsigned __int128*)&upload->bitbltbuf = bitbltbuf;
                    *(unsigned __int128*)&upload->trxreg = trxreg;
                    *(u64*)&upload->unk64[4] = unk68;
                    *(unsigned __int128*)&upload->unk64[0xC] = image_tag;
                    unkae3 |= 2;
                }

                upload->bitbltbuf.data = own->unk10[0];
                s32 quadwords = (s32)(info->data_size + 15) / 16;
                cursor[0] = DMA_TAG(8, DMA_TAG_ID_REF, &texture_uploads[1]);
                cursor[2] = DMA_TAG(quadwords, DMA_TAG_ID_REF, reinterpret_cast<u8*>(packet) + sizeof(LibTextureUpload));
                cursor += 4;
                uploaded = 1;
            }

            if (unkae3 & 4)
            {
                unkae3 &= ~4;
                LibTextureUpload* upload = reinterpret_cast<LibTextureUpload*>(reinterpret_cast<u32>(&texture_uploads[2]) | EE_UNCACHED_ACCELERATED);
                LibTextureUpload* packet = reinterpret_cast<LibTextureUpload*>(reinterpret_cast<u8*>(header) + header->palette_offset);

                if (!(unkae3 & 8))
                {
                    unsigned __int128 bitbltbuf;
                    unsigned __int128 trxreg;
                    unsigned __int128 image_tag;
                    u64 unk68;

                    bitbltbuf = *(unsigned __int128*)&packet->bitbltbuf;
                    trxreg = *(unsigned __int128*)&packet->trxreg;
                    unk68 = *(u64*)&packet->unk64[4];
                    image_tag = *(unsigned __int128*)&packet->unk64[0xC];
                    *(unsigned __int128*)&upload->bitbltbuf = bitbltbuf;
                    *(unsigned __int128*)&upload->trxreg = trxreg;
                    *(u64*)&upload->unk64[4] = unk68;
                    *(unsigned __int128*)&upload->unk64[0xC] = image_tag;
                    unkae3 |= 8;
                }

                upload->bitbltbuf.data = own->unk10[1];
                s32 quadwords = (header->palette_size + 15) / 16;
                cursor[0] = DMA_TAG(8, DMA_TAG_ID_REF, &texture_uploads[2]);
                cursor[2] = DMA_TAG(quadwords, DMA_TAG_ID_REF, reinterpret_cast<u8*>(packet) + sizeof(LibTextureUpload));
                cursor += 4;
                uploaded = 1;
            }
        }

        if (uploaded)
        {
            cursor[0] = DMA_TAG(3, DMA_TAG_ID_CNT, 0);
            *(unsigned __int128*)(cursor + 2) = 0;
            reinterpret_cast<u32*>(cursor)[7] = VIF_DIRECTHL(2);
            cursor[4] = GIF_TAG_NREG(1) | GIF_TAG_EOP | 1;
            cursor[5] = GIF_REGISTER_AD;
            cursor[6] = 0;
            cursor[7] = GS_REGISTER_TEXFLUSH;
            cursor += 8;
        }

        cursor[0] = DMA_TAG(0xA, DMA_TAG_ID_REF, &setup);
        s32 quadwords = (u32)(image->flag_count * (image->unk00 * 80)) / 16 + 1;
        cursor[2] = DMA_TAG(quadwords, DMA_TAG_ID_REF, image->unkb0);
        cursor += 4;
    }
    else if (kind == 5)
    {
        cursor[0] = DMA_TAG(0xA, DMA_TAG_ID_REF, &setup);
        cursor += 2;
    }

    *cursor = DMA_TAG_ID_RET;
    tail[0] = DMA_TAG(3, DMA_TAG_ID_CNT, 0);
    *(unsigned __int128*)(tail + 2) = 0;
    reinterpret_cast<u32*>(tail)[7] = VIF_DIRECTHL(2);
    tail[4] = GIF_TAG_NREG(1) | GIF_TAG_EOP | 1;
    tail[5] = GIF_REGISTER_AD;

    if (kind == 5)
    {
        tail[6] = 0xFFFFFFFF5ULL;
        tail[7] = GS_REGISTER_CLAMP_1;
        tail += 8;
    }
    else
    {
        tail[6] = 0xFFFFFFFF0ULL;
        tail[7] = GS_REGISTER_CLAMP_1;
        tail += 8;
    }

    if (copied)
    {
        if (unka98[index] != source->unkaac)
        {
            unka98[index] = source->unkaac;
            tail[0] = DMA_TAG(0x31, DMA_TAG_ID_REF, &draw_packet);
            tail[2] = DMA_TAG(0xF, DMA_TAG_ID_REF, source->packet);
            tail += 4;
            u8* cell = source->unka90[index] + 0x20;
            s32 count = source->unkab0[index];

            for (s32 i = 0; i < count; i++)
            {
                s32 quadwords = *reinterpret_cast<s32*>((reinterpret_cast<u32>(cell) | UNCACHED_SEGMENT) + 0x14);
                tail[0] = DMA_TAG(quadwords, DMA_TAG_ID_REF, cell);
                tail[2] = DMA_TAG(1, DMA_TAG_ID_CNT, 0);

                if (i == 0)
                {
                    *(unsigned __int128*)(tail + 4) = 0;
                    reinterpret_cast<u32*>(tail)[11] = VIF_MSCALF(first_call);
                }
                else
                {
                    *(unsigned __int128*)(tail + 4) = 0;
                    reinterpret_cast<u32*>(tail)[11] = VIF_MSCAL(next_call);
                }

                cell += quadwords * 16;
                tail += 6;
            }

            tail[0] = DMA_TAG(1, DMA_TAG_ID_REF, reinterpret_cast<u8*>(g_microcode_loader) + 0x20);
            tail[2] = DMA_TAG(1, DMA_TAG_ID_CNT, 0);
            *(unsigned __int128*)(tail + 4) = 0;
            reinterpret_cast<u32*>(tail)[11] = 0x06000000;
            tail[6] = DMA_TAG_ID_RET;
        }
    }
    else if (unka98[index] != unkaac)
    {
        unka98[index] = unkaac;
        tail[0] = DMA_TAG(0x31, DMA_TAG_ID_REF, &draw_packet);
        tail[2] = DMA_TAG(0xF, DMA_TAG_ID_REF, packet);
        tail += 4;
        u8* cell = unka90[index] + 0x20;
        s32 count = unkab0[index];

        for (s32 i = 0; i < count; i++)
        {
            s32 quadwords = *reinterpret_cast<s32*>((reinterpret_cast<u32>(cell) | UNCACHED_SEGMENT) + 0x14);
            tail[0] = DMA_TAG(quadwords, DMA_TAG_ID_REF, cell);
            tail[2] = DMA_TAG(1, DMA_TAG_ID_CNT, 0);

            if (i == 0)
            {
                *(unsigned __int128*)(tail + 4) = 0;
                reinterpret_cast<u32*>(tail)[11] = VIF_MSCALF(first_call);
            }
            else
            {
                *(unsigned __int128*)(tail + 4) = 0;
                reinterpret_cast<u32*>(tail)[11] = VIF_MSCAL(next_call);
            }

            cell += quadwords * 16;
            tail += 6;
        }

        tail[0] = DMA_TAG(1, DMA_TAG_ID_CNT, 0);
        tail[2] = 0;
        reinterpret_cast<u32*>(tail)[6] = VIF_FLUSH;
        reinterpret_cast<u32*>(tail)[7] = 0x06000000;
        tail[4] = DMA_TAG_ID_RET;
    }
}

// TODO: The bounds starts and their two flags look like function-local statics and their guards; they are written
// out because the guards sit at fixed addresses in sbss.
/** Set once D_0050CB90 holds the bounds minimum start. */
extern "C" s8 D_001B6584;

/** Set once D_0050CBA0 holds the bounds maximum start. */
extern "C" s8 D_001B6588;

/** Bounds minimum start: positive infinity, with w = 1. */
extern "C" LibVector4 D_0050CB90;

/** Bounds maximum start: negative infinity, with w = 0.5 to halve the sum into the centre. */
extern "C" LibVector4 D_0050CBA0;

/**
 * @brief Flag a renderer pass ready to draw.
 * @param pass Pass to flag.
 */
static inline void lib_mark_pass_ready(LibRendererPass* pass)
{
    pass->unk9c = 1;
}

/**
 * @brief Advance the model while its grid is ready: run the phase and lifetime, then, on the model's own frames,
 *        refresh the transform, pick the detail level from the camera depth and, when the cells changed, stream the
 *        grid's packets through the scratchpad into the free buffer and refit the bounds.
 */
void LibObject1751A0::update()
{
    if (reference != 0 && reference->func_slotc0())
    {
        LibColorModel::update();

        if (kind == 5)
        {
            lib_mark_pass_ready(static_cast<LibRenderer*>(g_renderer)->unk4458);
        }

        if (g_frame_ticks == 0.0f)
        {
            return;
        }

        if (g_frame_seconds == 0.0f)
        {
            return;
        }

        unkac8 += g_frame_seconds;

        if (unkaac == 0)
        {
            *(unsigned __int128*)&bounding_sphere = 0;
            bounding_sphere.w = 1.0f;
            bounding_sphere.w = 10000.0f;
        }

        if (!(unkabc <= 0.0f))
        {
            if (unkadf && (draw_flags & 0x10) && phase_period)
            {
                phase = (phase + 1) % phase_period;

                if (phase)
                {
                    return;
                }
            }

            unkabc -= g_frame_seconds;
        }
        else
        {
            unkabc = 0.0f;

            if (unkadf && (draw_flags & 0x10))
            {
                return;
            }
        }

        if (copied)
        {
            return;
        }

        update_transform_matrix();
        mark_transpose_current(this);

        if (!D_001B6584)
        {
            D_0050CB90.x = LIB_FLOAT_INFINITY;
            D_0050CB90.y = LIB_FLOAT_INFINITY;
            D_0050CB90.z = LIB_FLOAT_INFINITY;
            D_0050CB90.w = 1.0f;
            D_001B6584 = 1;
        }

        if (!D_001B6588)
        {
            D_0050CBA0.x = -LIB_FLOAT_INFINITY;
            D_0050CBA0.y = -LIB_FLOAT_INFINITY;
            D_0050CBA0.z = -LIB_FLOAT_INFINITY;
            D_0050CBA0.w = 0.5f;
            D_001B6588 = 1;
        }

        if (reference->func_slot2c())
        {
            unkada[0] = 1;
            unkada[1] = 1;
        }

        s32 buffer = unkadd ? 1 : 0;
        s32 level = 0;

        if (unkae6)
        {
            FieldVec4B position;
            position.x = transform.m[0][3];
            position.y = transform.m[1][3];
            position.z = transform.m[2][3];
            position.w = 1.0f;

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
                LibMatrix44Value view;
                LibVector4 local;

                ee_transpose_matrix(&view, &camera->view_matrix);
                vu0_apply_matrix_vector_first(&view, &position, &local);

                if (!(local.z <= 0.0f))
                {
                    s32 steps = local.z / unkac4;

                    if (steps > 0)
                    {
                        s32 limit = 2;
                        level = 2;

                        for (;;)
                        {
                            if (limit > steps)
                            {
                                break;
                            }

                            level <<= 1;

                            if (level >= 16)
                            {
                                break;
                            }

                            limit <<= 1;
                        }

                        level--;
                    }

                    if (unkacc != level)
                    {
                        unkada[0] = 1;
                        unkada[1] = 1;
                        unkacc = level;
                    }
                }
            }
        }

        if (!unkada[buffer])
        {
            unkadd ^= 1;
            return;
        }

        unkada[buffer] = 0;
        u8* destination = unka90[buffer] + 0x20;
        ResidentDmaQueue* queue = D_001B6604;
        queue->current = 0;
        DisableDmac(queue->channel);
        *D8_QWC = 0;
        s32 batches = 0;
        s32 stride = reference->func_slot38();
        s32 count = 0x30 / stride;

        switch (kind)
        {
        case 2:
        case 4:
            count /= 2;
            break;

        case 3:
        case 5:
        case 6:
            count = 0x12 / stride;
            break;
        }

        count *= stride;
        float seconds = g_frame_seconds;
        s32 steps = 1;
        u8 interpolate;

        if (stride > 1)
        {
            steps = g_frame_ticks;

            if (steps > 4)
            {
                steps = 4;
            }

            if (steps <= 0)
            {
                steps = 1;
            }

            if (!(g_frame_seconds <= 0.0f))
            {
                g_frame_seconds = 1.0f / 60.0f;
            }

            if (kind == 2 || kind == 4)
            {
                interpolate = true;
            }
            else
            {
                interpolate = false;
            }
        }
        else
        {
            interpolate = false;
        }

        s32 skip;
        u8* scratch;
        g_frame_seconds *= unkac0;
        u8 first = 0;

        if (kind >= 3)
        {
            first = 1;
        }

        unkaac = 0;

        for (s32 step = 0; step < steps; step++)
        {
            if (step == steps - 1)
            {
                reference->func_slot0c(this);
                vu0_load_bounds(&D_0050CB90, &D_0050CBA0);
                skip = 0;

                for (;;)
                {
                    scratch = (u8*)(((batches & 1) ? 0xA00 : 0) + EE_SCRATCHPAD);

                    if (first)
                    {
                        reference->func_slot10(count, scratch + 0x20, interpolate);
                    }

                    if (stride > 1)
                    {
                        reference->func_slot14(count, scratch + 0x20, interpolate);
                    }

                    s32 written = reference->func_slot18(count, scratch + 0x20);

                    if (written == 0)
                    {
                        break;
                    }

                    if (level != 0)
                    {
                        unsigned __int128* to = (unsigned __int128*)(scratch + 0x20);
                        unsigned __int128* from = to;
                        s32 kept = 0;

                        for (s32 i = 0; i < written; i += stride)
                        {
                            if (--skip < 0)
                            {
                                skip = level;
                                kept += stride;

                                if (to != from)
                                {
                                    for (s32 j = 0; j < stride; j++)
                                    {
                                        to[0] = from[0];
                                        to[1] = from[1];
                                        to[2] = from[2];
                                        from += 3;
                                        to += 3;
                                    }
                                }
                                else
                                {
                                    to += stride * 3;
                                    from += stride * 3;
                                }
                            }
                            else
                            {
                                from += stride * 3;
                            }
                        }

                        if (kept == 0)
                        {
                            continue;
                        }

                        written = kept;
                    }

                    u32* header = (u32*)scratch;
                    header[4] = written;
                    header[6] = stride;
                    u32 quadwords = (u32)(written * 0x30 + 0x2F) >> 4;
                    *(unsigned __int128*)header = 0;
                    header[3] = VIF_UNPACK(VIF_UNPACK_V4_32, quadwords - 1, 0x8000);
                    header[5] = quadwords;
                    ee_sync();

                    if (batches > 0)
                    {
                        while ((*D_STAT & D_STAT_CIS8) == 0)
                        {
                        }
                    }

                    *D8_MADR = (u32)destination;
                    *D8_SADR = (u32)scratch;
                    *D8_QWC = quadwords;
                    *D_STAT = D_STAT_CIS8;
                    destination += quadwords * 16;
                    batches++;
                    *D8_CHCR = DMA_CHCR_START | DMA_CHCR_DIR_FROM_MEMORY;
                    unkaac += written;
                }
            }
            else
            {
                reference->func_slot0c(this);
                scratch = (u8*)EE_SCRATCHPAD;

                do
                {
                    if (first)
                    {
                        reference->func_slot10(count, scratch + 0x20, interpolate);
                    }

                    if (stride > 1)
                    {
                        reference->func_slot14(count, scratch + 0x20, interpolate);
                    }
                } while (reference->func_slot18(count, scratch + 0x20) != 0);
            }
        }

        g_frame_seconds = seconds;
        unkab0[buffer] = batches;

        if (reference->unk04 && unkaac)
        {
            LibVector4 padding;
            padding.x = unkaa4 + reference->func_slot48();
            vu0_begin_bounds_sphere(&padding);
            vu0_store_bounds(&box_min);
            vu0_store_bounds_sphere(&bounding_sphere);
            bounding_sphere.w += diagonal;

            if (bounding_sphere.w < unkaa8)
            {
                bounding_sphere.w = unkaa8;
            }
        }

        if (batches > 0)
        {
            while ((*D_STAT & D_STAT_CIS8) == 0)
            {
            }
        }

        reference->func_slot28();
        unkadd ^= 1;
        EnableDmac(D_001B6604->channel);
    }
}

/**
 * @brief Send the model's packet chain on VIF1.
 * @param channel DMA channel; unused.
 */
void LibObject1751A0::submit_dma(u32 channel)
{
    dma_pending = 1;
    *D1_QWC = 0;
    *D1_TADR = chain_address;
    *D_STAT = D_STAT_CIS1;
    *D1_CHCR = DMA_CHCR_START | DMA_CHCR_MODE_CHAIN | DMA_CHCR_DIR_FROM_MEMORY;
}

/**
 * @brief Finish the model's packet.
 * @param channel DMA channel; unused.
 */
void LibObject1751A0::complete_dma(u32 channel)
{
    lib_finish_packet(this);
}

/** @brief Queue the model's DMA submission. */
void LibObject1751A0::render()
{
    resident_dma_queue_push(g_vif1_dma_queue, this);
}

/**
 * @brief Refresh the draw packet from the model's state while its grid has cells to draw: transform, lighting,
 *        colour, TEST register, fog and blend flags and the texture, then build the cell packets.
 * @param matrix Camera the model is drawn with.
 * @param context Light list, or null for none.
 */
void LibObject1751A0::build_packet(const void* matrix, void* context)
{
    if (reference != 0 && reference->func_slotc0())
    {
        if (copied)
        {
            if (source->unkaac == 0)
            {
                return;
            }
        }
        else
        {
            if (unka90[0] == 0)
            {
                return;
            }

            if (unkaac == 0)
            {
                return;
            }
        }

        LibLightList* lights = static_cast<LibLightList*>(context);
        LibModelPacketHeader* packet = (LibModelPacketHeader*)((u32)&draw_packet | EE_UNCACHED_ACCELERATED);
        const unsigned __int128* from = reinterpret_cast<const unsigned __int128*>(get_transform_matrix());
        unsigned __int128* to = packet->transform;
        LibVector4 color;

        *to++ = *from++;
        *to++ = *from++;
        *to++ = *from++;
        *to++ = *from++;

        if (lights != 0)
        {
            vu0_multiply_xyzw_right_first(&color, &combined_color_factor, &lights->unk340);

            if (unkade || lights->has_local_lights)
            {
                FieldVec4B position;
                position.x = transform.m[0][3];
                position.y = transform.m[1][3];
                position.z = transform.m[2][3];
                position.w = 1.0f;

                if (unkade)
                {
                    LibVector4 ambient;

                    func_004E8510(lights, &color, &position, light_mask, 0);

                    const unsigned __int128* rows = reinterpret_cast<const unsigned __int128*>(&lights->unk90);
                    packet->light_matrix[0] = rows[0];
                    packet->light_matrix[1] = rows[1];
                    packet->light_matrix[2] = rows[2];
                    packet->light_matrix[3] = rows[3];
                    vu0_multiply_xyzw_vf1(&ambient, &lights->unk310, &color);
                    packet->ambient = *reinterpret_cast<unsigned __int128*>(&ambient);
                    ee_transpose_matrix_input_first(&packet->light_transposed, &lights->unk1d0);
                }

                if (lights->has_local_lights)
                {
                    func_004E7AA0(lights, &bounding_sphere, &color, &position, light_mask, 0);

                    s32 any = 0;

                    if (lights->unk37c)
                    {
                        packet->unkf4 = 1;
                        const unsigned __int128* rows = reinterpret_cast<const unsigned __int128*>(lights->unk210);
                        packet->unk150[0] = rows[0];
                        packet->unk150[1] = rows[1];
                        packet->unk150[2] = rows[2];
                        ee_transpose_matrix_input_first(&packet->unk180, &lights->unk240);
                        const unsigned __int128* vector = reinterpret_cast<const unsigned __int128*>(&lights->unk280);
                        *reinterpret_cast<FieldVec4B*>(&packet->unk1c0) = *reinterpret_cast<const FieldVec4B*>(vector);
                        any = 1;
                    }
                    else
                    {
                        packet->unkf4 = 0;
                    }

                    s32 count = lights->unk37d;

                    if (count)
                    {
                        packet->unkf8 = count;
                        packet->unk1d0[0] = lights->unk2b0[0];
                        packet->unk1d0[2] = lights->unk290[0];
                        packet->unk1d0[4] = lights->unk2d0[0];
                        packet->unk1d0[6] = lights->unk2f0[0];

                        if (count == 2)
                        {
                            packet->unk1d0[1] = lights->unk2b0[1];
                            packet->unk1d0[3] = lights->unk290[1];
                            packet->unk1d0[5] = lights->unk2d0[1];
                            packet->unk1d0[7] = lights->unk2f0[1];
                        }

                        any = 1;
                    }
                    else
                    {
                        packet->unkf8 = 0;
                    }

                    if (any)
                    {
                        packet->light_mode = 2;
                    }
                    else
                    {
                        packet->light_mode = 1;
                    }
                    }
                    else
                    {
                        packet->light_mode = 1;
                    }
            }
            else
            {
                packet->light_mode = 0;
            }
        }
        else
        {
            packet->light_mode = 0;
        }

        if (D_001B6550 && !unk59d_1 && !(color.w <= 0.993f))
        {
            color.w = 0.993f;
        }

        *reinterpret_cast<FieldVec4B*>(&packet->color) = *reinterpret_cast<FieldVec4B*>(&color);

        if (unk59d_0)
        {
            unk59d_0 = 0;
            packet->unk120 = unk59d_1;
            packet->test = lib_model_test_register(this, static_cast<const LibCamera*>(matrix));

            if (kind == 3 || kind == 5 || kind == 6)
            {
                packet->unk250 = 0x110;
                packet->unk254 = 0x1F8;
            }
            else
            {
                packet->unk250 = 0x1A0;
                packet->unk254 = 0x240;
            }
        }

        packet->unk10c = (u8)(fog_enabled ? (unk67 ? true : false) : false);

        if (color.x == 1.0f && color.y == 1.0f && color.z == 1.0f && color.w == 1.0f)
        {
            packet->white = 1;
        }
        else
        {
            packet->white = 0;
        }

        if (image)
        {
            bind_texture();

            if (image->flags[0] || image->flags[1] || image->flags[2] || image->flags[3])
            {
                packet->unk104 = 1;
            }
            else
            {
                packet->unk104 = 0;
            }
        }
        else
        {
            if (kind == 5)
            {
                func_004683E0();

                const LibVector4* scale = D_00508210;
                const LibVector4* offset = D_00508220;
                LibVector4 value;
                *(unsigned __int128*)&value = *(const unsigned __int128*)scale;
                value.x *= unka70[0];
                value.y *= unka70[1];
                packet->unk270 = *(unsigned __int128*)&value;
                *(unsigned __int128*)&value = *(const unsigned __int128*)offset;
                value.x += unka70[2];
                value.y += unka70[3];
                packet->unk280 = *(unsigned __int128*)&value;
            }

            packet->unk104 = (u8)(blend_mode ? true : false);
        }

        build_dma_chain();
        ee_sync();
        unk63 = 1;
    }
}

/**
 * @brief Give the centre and half extent of the image's bounding box.
 * @param output Receives the box (LibCullBox).
 * @return Nonzero when the shared object is ready and the box was written.
 */
s32 LibObject1751A0::get_box_cull_center(void* output)
{
    LibVector4 extent;

    if (!reference->unk04)
    {
        return 0;
    }

    LibCullBox* box = static_cast<LibCullBox*>(output);
    extent.x = 0.5f * (box_max.x - box_min.x);
    extent.y = 0.5f * (box_max.y - box_min.y);
    extent.z = 0.5f * (box_max.z - box_min.z);
    extent.w = 1.0f;
    copy_vector(&box->half_extents, &extent);
    extent.x += box_min.x;
    extent.y += box_min.y;
    extent.z += box_min.z;
    copy_vector(&box->center, &extent);
    return 1;
}

/**
 * @brief Transform the bounding sphere's centre into world space; the radius stays.
 * @return Bounding sphere in world space.
 */
const LibVector4* LibObject1751A0::get_bounding_sphere()
{
    LibVector4 center;
    copy_vector(&center, &bounding_sphere);
    center.w = 1.0f;
    vu0_dot_matrix_rows(&transform, &center, &world_bounding_sphere);
    world_bounding_sphere.w = bounding_sphere.w;
    return &world_bounding_sphere;
}

/** @brief Pick the draw bucket from the blend and image state. */
void LibObject1751A0::set_default_draw_bucket()
{
    draw_bucket = blend_mode ? 2 : 0;

    if (draw_flags & 0x1000)
    {
        draw_bucket = 7;
    }
    else if (kind == 5)
    {
        draw_bucket = 8;
    }
    else if (unkae2)
    {
        switch (unkae0)
        {
        case 0:
            draw_bucket = 1;
            break;
        case 1:
            draw_bucket = 5;
            break;
        case 2:
            draw_bucket = 2;
            break;
        case 3:
            draw_bucket = 3;
            break;
        }
    }
}

/** @brief Clear the image and reset the texture state. */
void LibObject1751A0::clear_image()
{
    record.data = 0;
    image = 0;
    record.storage_kind = 0;
    record.resolved_data = 0;
    reset_texture_uploads();
    memset_guess(&setup, 0, sizeof(setup));
    setup.unpack = VIF_UNPACK(VIF_UNPACK_V4_32, 9, 0x2E0);
    setup.unk10 = 1;
    setup.unk14 = 1;
    setup.unk18 = 1;
    setup.texture_tag = 2 | GIF_TAG_NREG(1);
    setup.texture_registers = 0;
    setup.texture_register_fields.register0 = GIF_REGISTER_AD;
    setup.texture_address = GS_REGISTER_TEX0_1;
    setup.texture_2_address = GS_REGISTER_TEX0_1;
    setup.alpha_tag = 1 | GIF_TAG_NREG(1);
    setup.alpha_registers = 0;
    setup.alpha_register_fields.register0 = GIF_REGISTER_AD;
    setup.alpha_address = GS_REGISTER_ALPHA_1;
    FlushCache(0);

    if (reference)
    {
        reference->func_slot54(1);
    }

    record.next_offset = 0;
}
