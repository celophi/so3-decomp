#include "include_asm.h"
#include "overlays/lib/render_buffer.h"
#include "overlays/lib/text_003E68C0.h"
#include "overlays/lib/dma_callbacks_inlines.h"
#include "overlays/lib/text_0044ABE0.h"
#include "overlays/lib/text_00429B00.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/text_004DD440.h"
#include "overlays/lib/clip_region.h"
#include "overlays/lib/transform_owner_inlines.h"
#include "overlays/lib/text_004095C0.h"
#include "overlays/lib/character_record.h"
#include "overlays/lib/item_allocation.h"
#include "main/resident_data.h"
#include "main/entry_table.h"
#include "main/system.h"
#include "main/utility.h"
#include "main/input.h"
#include "overlays/lib/light_random.h"
#include "ee.h"
#include "sdk/main/libdma_0012B2C8.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "sdk/main/libc_guess_0013C948.h"

/** Bounding sphere objects without bounds report: centred on the origin, radius 1000000. */
extern "C" LibVector4 g_default_bounding_sphere;

/** Screen point, zeroed on construction: LibClass172120's warp grid at unka0 and LibClass172080's ring points. */
struct LibClass172120Entry
{
    LibClass172120Entry()
    {
        y = 0;
        x = 0;
    }

    float x;
    float y;
};

/** Widget that plays a frame animation, with vtable D_171DA0 in main data. */
class LibClass171DA0 : public LibWidget
{
public:
    /** @brief Destroy the widget and its drawing storage. */
    virtual ~LibClass171DA0();

    /** @brief Restart the animation when asked, otherwise step it unless it's paused. */
    virtual void func_00413D20();

    virtual void draw();

    LibStorageBlock0C unk40;
    u8 unk4c[4];
    LibImageAnimation animation;
    u32 unkb4;
    void* pending_resource;
    s32 pending_frame;
    u8 paused;
    u8 restart;
};

/** @brief Destroy the widget and its drawing storage. */
LibClass171DA0::~LibClass171DA0()
{
}

/**
 * @brief Report the list kind used when registration requests the default.
 * @return Three.
 */
s32 LibListObject::get_default_list_kind()
{
    return 3;
}

/** @brief Default update handler that performs no work. */
void LibListObject::update()
{
}

/** @brief Leave the base intrusive object unchanged. */
void LibListObject::render()
{
}

/** @brief Draw the animation's current frame into the widget's packet, when it has one. */
void LibClass171DA0::draw()
{
    unk3b = 0;
    u64* start = reinterpret_cast<u64*>(unk40.dma_address);
    u64* cursor = start;
    packet = start;
    animation.unk00 = unkb4;

    if (func_00453150(&animation, &cursor, 0))
    {
        animation.set_position(unk18.unk00, unk18.unk04);
        animation.unk50 = draw_alpha;
        packet_tag = cursor;
        cursor += 2;
        LibContainer* owner = container;
        LibCallbackTransform& transform = *owner;

        func_004535B0(&animation, &cursor, &transform.translation, transform.unka4 + unk34, owner->unkE0, 0);
        *packet_tag = DMA_TAG((reinterpret_cast<u32>(cursor) - reinterpret_cast<u32>(packet_tag) - LIB_DRAW_QWORD_SIZE) / LIB_DRAW_QWORD_SIZE, DMA_TAG_ID_END, 0);
        unk3b = 1;
        needs_redraw = 1;
    }
}

/** @brief Restart the animation when asked, otherwise step it unless it's paused. */
void LibClass171DA0::func_00413D20()
{
    if (pending_resource)
    {
        if (restart)
        {
            animation.resource = pending_resource;
            animation.start(pending_frame);
            restart = 0;
        }
        else if (!paused)
        {
            animation.step();
        }
    }
}

/**
 * @brief Place the image widget, allocate its drawing storage and queue an image to start.
 * @param object Image widget.
 * @param unkb4 Value for unkb4.
 * @param resource Image resource to start.
 * @param frame Frame to start from.
 * @param paused Nonzero to start paused.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @return Nonzero once the storage is allocated.
 */
extern "C" s32 func_003EED40(LibClass171DA0* object, u32 unkb4, void* resource, s32 frame, u8 paused, float x, float y)
{
    object->unk18.unk00 = x;
    object->unk18.unk04 = y;

    if (!lib_allocate_drawing_storage(&object->unk40, 0x3A))
    {
        return 0;
    }

    object->unkb4 = unkb4;
    object->pending_resource = resource;
    object->pending_frame = frame;
    object->paused = paused;
    object->restart = 1;
    object->unk34 = 6;
    object->unk39 = 1;
    return 1;
}

/** @brief Use the region's own draw bucket. */
void LibClipRegion::set_default_draw_bucket()
{
    draw_bucket = default_bucket;
}

// TODO: Returns the address of a local, as the original does: a sphere at the origin with radius 1e30.
/**
 * @brief Return a bounding sphere that covers everything.
 * @return Sphere at the origin with a huge radius.
 */
const LibVector4* LibClipRegion::get_bounding_sphere()
{
    s32 stack[4];
    stack[0] = 0;
    stack[3] = 0x7149F2CA;
    stack[1] = 0;
    s32* result = stack;
    stack[2] = 0;
    return reinterpret_cast<const LibVector4*>(result);
}

/**
 * @brief Return the default output-handler result.
 * @param output Unused output object.
 * @return Zero.
 */
s32 LibTransformOwner::get_box_cull_center(void* output)
{
    return 0;
}

/**
 * @brief Test whether the supplied value is negative.
 * @param value Value to test.
 * @param mode Unused mode.
 * @return One if negative, otherwise zero.
 */
s32 LibTransformOwner::set_fade_alpha(float value, float mode)
{
    s32 result = 1;

    if (!(value < 0.0f))
    {
        result = 0;
    }

    return result;
}

/**
 * @brief Return no replacement transform receiver.
 * @return Null.
 */
LibTransformOwner* LibTransformOwner::clone()
{
    return 0;
}

/** @brief Leave the base transform receiver unchanged. */
void LibTransformOwner::release_clone()
{
}

/** @brief Copy the position and mark the transform dirty. */
void LibOrientedTransform::copy_translation(const LibVector4* value)
{
    transform_dirty = 1;
    copy_vector(&translation, value);
}

/** @brief Copy the position and mark the transform dirty. */
void LibOrientedTransform::set_translation_vector(const LibVector4* value)
{
    transform_dirty = 1;
    copy_vector(&translation, value);
}

/** @brief Set the position and a w component of one, and mark the transform dirty. */
void LibOrientedTransform::set_translation(float x, float y, float z)
{
    transform_dirty = 1;
    translation.x = x;
    translation.y = y;
    translation.z = z;
    translation.w = 1.0f;
}

/**
 * @brief Set all four components of the primary transform vector and mark it dirty.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 * @param w Fourth component.
 */
void LibOrientedTransform::set_orientation_components(float x, float y, float z, float w)
{
    transform_dirty = 1;
    orientation.x = x;
    orientation.y = y;
    orientation.z = z;
    orientation.w = w;
}

/**
 * @brief Copy the primary transform vector and mark it dirty.
 * @param value Source vector.
 */
void LibOrientedTransform::copy_orientation(const LibVector4* value)
{
    transform_dirty = 1;
    copy_vector(&orientation, value);
}

/**
 * @brief Copy the primary transform vector and mark it dirty.
 * @param value Source vector.
 */
void LibOrientedTransform::set_orientation(const LibVector4* value)
{
    transform_dirty = 1;
    copy_vector(&orientation, value);
}

/** @brief Convert a rotation into the rotation vector and mark the transform dirty. */
void LibOrientedTransform::convert_rotation(const LibVector4* value)
{
    transform_dirty = 1;
    lib_quaternion_from_euler(reinterpret_cast<FieldVec4B*>(&orientation), &value->x);
}

/** @brief Convert a rotation into the rotation vector and mark the transform dirty. */
void LibOrientedTransform::set_rotation_vector(const LibVector4* value)
{
    transform_dirty = 1;
    lib_quaternion_from_euler(reinterpret_cast<FieldVec4B*>(&orientation), &value->x);
}

/** @brief Convert three rotation components into the rotation vector and mark the transform dirty. */
void LibOrientedTransform::set_rotation(float x, float y, float z)
{
    transform_dirty = 1;
    LibVector4 value;
    value.x = x;
    value.y = y;
    value.z = z;
    value.w = 1.0f;
    lib_quaternion_from_euler(reinterpret_cast<FieldVec4B*>(&orientation), &value.x);
}

/**
 * @brief Copy the secondary transform vector and mark it dirty.
 * @param value Source vector.
 */
void LibOrientedTransform::copy_scale(const LibVector4* value)
{
    transform_dirty = 1;
    copy_vector(&scale, value);
}

/**
 * @brief Copy the secondary transform vector and mark it dirty.
 * @param value Source vector.
 */
void LibOrientedTransform::set_scale_vector(const LibVector4* value)
{
    transform_dirty = 1;
    copy_vector(&scale, value);
}

/**
 * @brief Set the secondary transform vector's xyz components and mark it dirty.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void LibOrientedTransform::set_scale(float x, float y, float z)
{
    transform_dirty = 1;
    scale.x = x;
    scale.y = y;
    scale.z = z;
}

/**
 * @brief Send the region's packet on DMA channel 1 (VIF1).
 * @param channel DMA channel; unused.
 */
void LibClipRegion::submit_dma(u32 channel)
{
    dma_pending = 1;
    *D1_QWC = packet_quadwords;
    *D1_MADR = packet_address;
    *D_STAT = D_STAT_CIS1;
    *D1_CHCR = DMA_CHCR_START | DMA_CHCR_DIR_FROM_MEMORY;
}

/**
 * @brief Finish the region's packet.
 * @param channel DMA channel; unused.
 */
void LibClipRegion::complete_dma(u32 channel)
{
    lib_finish_packet(this);
}

/** @brief Queue this object's DMA submission on the VIF1 queue. */
void LibClipRegion::render()
{
    resident_dma_queue_push(g_vif1_dma_queue, this);
}

/**
 * @brief Rebuild the packet: set the scissor to the display's, or to the region's rectangle when it has no
 *        display, then record the packet's size and address.
 * @param matrix View matrix; unused.
 * @param context Packet building context; unused.
 */
void LibClipRegion::build_packet(const void* matrix, void* context)
{
    resident_packet_rewind(packet);
    u64* cursor = reinterpret_cast<u64*>(resident_packet_reserve(packet, 0));
    cursor[0] = 0;
    u32* vif = reinterpret_cast<u32*>(cursor + 1);
    vif[0] = 0x06008000;
    u32* direct = vif + 1;
    GsGifTag* tag = reinterpret_cast<GsGifTag*>(cursor + 2);
    tag->tag = GIF_TAG_NREG(1) | 1;
    tag->registers = 0;
    tag->fields.register0 = GIF_REGISTER_AD;
    cursor += 4;

    if (display)
    {
        *cursor++ = func_004DBCA0(display, 3);
    }
    else
    {
        *cursor++ = (left | (right << 16)) | ((u64)top << 32) | ((u64)bottom << 48);
    }

    *cursor++ = GS_REGISTER_SCISSOR_1;
    resident_packet_align_cursor(packet, reinterpret_cast<u8*>(cursor));
    packet_quadwords = resident_packet_end_unmask_path3(packet);
    *direct = VIF_DIRECTHL(packet_quadwords - 2);
    packet_address = resident_packet_get_address(packet);
    unk63 = 1;
}

/** @brief Delete the packet and destroy the region. */
LibClipRegion::~LibClipRegion()
{
    delete packet;
}

/** @brief Free the packet storage unless it is borrowed. */
LibPacketBuffer::~LibPacketBuffer()
{
    if (!unk14)
    {
        delete unk04;
    }
}

/** @brief Start as an unattached kind-2 object with a 16-quadword packet and no camera. */
LibClipRegion::LibClipRegion()
{
    unk65 = 0;
    type_id = 0x1300;
    draw_flags = 0x400;
    packet = new (0) LibPacketBuffer(16);
    FlushCache(0);
    display = 0;
    default_bucket = 0;
}

/** @brief Delete the object through its virtual destructor; null is ignored. */
void LibListObject::destroy()
{
    delete this;
}

/** @brief Store the position components and set the homogeneous component to one. */
void LibPositionTransform::set_translation(float x, float y, float z)
{
    translation.x = x;
    translation.y = y;
    translation.z = z;
    translation.w = 1.0f;
}

/** @brief Copy the position. */
void LibPositionTransform::copy_translation(const LibVector4* value)
{
    copy_vector(&translation, value);
}

/** @brief Copy the position. */
void LibPositionTransform::set_translation_vector(const LibVector4* value)
{
    copy_vector(&translation, value);
}

extern "C" ResidentObject1B64F8* D_001B64F8;
extern "C" u8* D_001B64EC;
extern "C" ItemCreationCategoryDefinition* D_001B64F4;

/** @brief Release the resident category storage and clear its counters. */
void func_003EF860(void)
{
    delete D_001B64F8;
    D_001B64F8 = 0;
    delete D_001B64EC;
    D_001B64EC = 0;
    D_001B64F0 = 0;
    D_001B64F4 = 0;
}

#define LIB_ENTRY_FIELD_BLOCK 0x9525090

/** @brief Remove and free the keyed Lib resource. */
void func_003EF8A0(void)
{
    void* table = resident_get_entry_table(resident_get_system());
    void* entry = reinterpret_cast<void*>(resident_find_entry(table, LIB_ENTRY_FIELD_BLOCK));
    resident_remove_entry(table, LIB_ENTRY_FIELD_BLOCK);
    ::operator delete(entry);
}

/**
 * Transform owner with sixteen child objects and a packet buffer it sends itself, with vtables D_171F40 and D_171FB4
 * in main data.
 */
class LibClass171F40 : public LibClass172000, public LibDmaCallbacks
{
public:
    /** @brief Delete the packet buffer. */
    virtual ~LibClass171F40();

    /**
     * @brief Return the list kind.
     * @return Nine.
     */
    virtual s32 get_default_list_kind();

    /** @brief Destroy the children, then destroy through the base. */
    virtual void destroy();

    /** @brief Destroy the object once it asked to be removed. */
    virtual void update();

    /** @brief Mark the packet in flight and submit the packet buffer, notifying this object when it's sent. */
    virtual void render();

    /** @brief Draw in bucket 9. */
    virtual void set_default_draw_bucket();

    virtual void build_packet(const void* matrix, void* context);

    /**
     * @brief Finish the packet and remember that it was sent.
     * @param value Notification value; unused.
     */
    virtual void on_packet_complete(u32 value);

    LibPacketBuffer* packet;
    LibListObject* children[16];
    u8 sent : 1;
    u8 remove_requested : 1;
    u8 unkd8_2_7 : 6;
};

/**
 * @brief Return the list kind.
 * @return Nine.
 */
s32 LibClass171F40::get_default_list_kind()
{
    return 9;
}

/** @brief Draw in bucket 9. */
void LibClass171F40::set_default_draw_bucket()
{
    draw_bucket = 9;
}

/** @brief Destroy the object once it asked to be removed. */
void LibClass171F40::update()
{
    if (remove_requested)
    {
        destroy();
    }
}

/** @brief Delete the packet buffer. */
LibClass171F40::~LibClass171F40()
{
    delete packet;
    packet = 0;
}

/** @brief Default DMA notification hook; does nothing. */
void LibDmaCallbacks::on_packet_notify(u32 value)
{
}

/**
 * @brief Return the default bounding sphere, which encloses everything.
 * @return Sphere centre in xyz, radius in w.
 */
const LibVector4* LibTransformOwner::get_bounding_sphere()
{
    return &g_default_bounding_sphere;
}

/**
 * @brief Finish the packet and remember that it was sent.
 * @param value Notification value; unused.
 */
void LibClass171F40::on_packet_complete(u32 value)
{
    lib_finish_packet(this);
    sent = 1;
}

/** @brief Mark the packet in flight and submit the packet buffer, notifying this object when it's sent. */
void LibClass171F40::render()
{
    dma_pending = 1;
    resident_packet_submit(packet, static_cast<LibDmaCallbacks*>(this));
}

/**
 * @brief Build the packet: switch to the second drawing context aimed at the free VRAM page, then copy the frame
 *        into it in eighteen strips and restore the texture state.
 * @param matrix Unused.
 * @param context Unused.
 */
void LibClass171F40::build_packet(const void* matrix, void* context)
{
    unk63 = 0;
    dma_pending = 0;

    if (sent)
    {
        return;
    }

    resident_packet_rewind(packet);
    u64* cursor = reinterpret_cast<u64*>(resident_packet_reserve(packet, 8));

    if (cursor == 0)
    {
        return;
    }

    cursor[0] = GIF_TAG_NREG(1) | GIF_TAG_EOP | 15;
    cursor[1] = 0;
    reinterpret_cast<GsGifTag*>(cursor)->fields.register0 = GIF_REGISTER_AD;
    cursor[2] = (u32)(g_display->vram_free_page | 0x2080000);
    cursor[3] = GS_REGISTER_FRAME_2;
    cursor[4] = 0x7000 | 0x7300ULL << 32;
    cursor[5] = 0x19;
    cursor[6] = 0x1FF0000 | 0x19F0000ULL << 32;
    cursor[7] = 0x41;
    cursor[8] = 0;
    cursor[9] = GS_REGISTER_FBA_2;
    cursor[10] = 1;
    cursor[11] = 0x45;
    cursor[12] = (u64)-4;
    cursor[13] = 0x44;
    cursor[14] = 0x61;
    cursor[15] = GS_REGISTER_TEX1_2;
    cursor[16] = 5;
    cursor[17] = GS_REGISTER_CLAMP_2;
    cursor[18] = 0x30000;
    cursor[19] = GS_REGISTER_TEST_2;
    cursor[20] = (u32)(*reinterpret_cast<const u32*>(&g_display->buffers[0].environment.context1.depth_buffer) | 0x32000000) |
                 1ULL << 32;
    cursor[21] = GS_REGISTER_ZBUF_2;
    cursor[22] = 1;
    cursor[23] = GS_REGISTER_TEX1_2;
    cursor[24] = (s64)(s32)(((u32)(g_display->buffers[0].environment.context1.frame.base_pointer << 13) >> 8) | 0x28024000) |
                 (0x8000ULL << 16 | 2ULL << 32);
    cursor[25] = GS_REGISTER_TEX0_2;
    cursor[26] = 0x80 | 0x80ULL << 32;
    cursor[27] = GS_REGISTER_TEXA;
    cursor[28] = 0x316;
    cursor[29] = GS_REGISTER_PRIM;
    cursor[30] = GS_RGBA_NEUTRAL;
    cursor[31] = GS_REGISTER_RGBAQ;
    cursor[32] = GIF_TAG_NREG(4) | GIF_TAG_FLG_REGLIST | GIF_TAG_EOP | 18;
    cursor[33] = 0;
    GsGifTag* strip_tag = reinterpret_cast<GsGifTag*>(&cursor[32]);
    strip_tag->fields.register0 = GIF_REGISTER_UV;
    strip_tag->fields.register1 = GIF_REGISTER_XYZ2;
    strip_tag->fields.register2 = GIF_REGISTER_UV;
    strip_tag->fields.register3 = GIF_REGISTER_XYZ2;
    cursor += 34;
    s32 x = 0x7000;

    // TODO: An unsigned counter compared signed gives the target's unroll by eight with a remainder loop; a plain
    // s32 counter unrolls by six.
    for (u32 i = 0; (s32)i < 18; i++)
    {
        cursor[0] = (s64)(s32)(i << 9);
        cursor[1] = (s64)x | (0x73000000 | 0xFFFFULL << 32);
        cursor[2] = (s64)(s32)(((i + 1) << 9) | 0x1A000000);
        cursor[3] = (s64)(x + 0x1C7) | (0x8D000000 | 0xFFFFULL << 32);
        x += 0x1C7;
        cursor += 4;
    }

    cursor[0] = GIF_TAG_NREG(1) | GIF_TAG_EOP | 3;
    cursor[1] = 0;
    reinterpret_cast<GsGifTag*>(cursor)->fields.register0 = GIF_REGISTER_AD;
    cursor[2] = 0x61;
    cursor[3] = GS_REGISTER_TEX1_2;
    cursor[4] = 0;
    cursor[5] = GS_REGISTER_TEXFLUSH;
    cursor[6] = 0;
    cursor[7] = 0x45;
    resident_packet_align_cursor(packet, reinterpret_cast<u8*>(cursor + 8));
    unk63 = 1;
}

/** @brief Destroy the children, then destroy through the base. */
void LibClass171F40::destroy()
{
    for (s32 i = 0; i < 16; i++)
    {
        if (children[i])
        {
            children[i]->destroy();
            children[i] = 0;
        }
    }

    LibTransformOwner::destroy();
}

/** One of LibClass172080's six expanding rings. */
struct LibClass172080Record
{
    float size;
    float offset;
    u8 enabled : 1;
    u8 unk08_1_7 : 7;
    u8 unk09[3];
};

/** LibClass1748D0 that draws from a 128 KiB uncached buffer of its own, with vtables D_172080 and D_172104 in main data. */
class LibClass172080 : public LibClass1748D0
{
public:
    /** @brief Allocate the packet buffer over a buffer of its own and clear the records. */
    LibClass172080();

    /** @brief Delete the extra buffer. */
    virtual ~LibClass172080();

    /** @brief Update through the base. */
    virtual void update();

    virtual void build_packet(const void* matrix, void* context);

    float unk260;
    LibClass172080Record records[6];
    float unk2ac;
    float unk2b0;
    float unk2b4;
    float unk2b8;
    s32 unk2bc;
    u8* unk2c0;
    u8 unk2c4_0 : 1;
    u8 unk2c4_1 : 1;
    u8 unk2c4_2 : 1;
    u8 unk2c4_3_7 : 5;
};

/**
 * @brief Draw the glare: a ripple of 32-pixel tiles while the flash runs, then each live ring as three bands of quads
 *        between six radii, 33 steps around.
 * @param matrix Camera matrix, passed to the base.
 * @param context Packet building context, passed to the base.
 */
void LibClass172080::build_packet(const void* matrix, void* context)
{
    s32 i;

    if (!packet || !unk2c0 || unk2c4_2)
    {
        unk63 = 0;
        return;
    }

    LibClass1748D0::build_packet(matrix, context);
    unk260 -= unk2b8;

    if (unk260 <= 0.0f)
    {
        for (s32 slot = 0; slot < 6; slot++)
        {
            if (!records[slot].enabled)
            {
                records[slot].enabled = 1;
                records[slot].size = resident_random_range(0x10, 0x20);
                records[slot].offset = 0;
                unk260 = resident_random_range(0xF, 0x3C);
                break;
            }
        }
    }

    for (s32 slot = 0; slot < 6; slot++)
    {
        if (records[slot].enabled)
        {
            records[slot].size -= 0.3f * unk2b8;

            if (records[slot].size <= 0.0f)
            {
                records[slot].enabled = 0;
            }
            else
            {
                records[slot].offset += 2.0f * unk2b8;
            }
        }
    }

    s32 row;
    s32 index;
    s32 left = 0x800 - g_display->display_area.width / 2;
    s32 top = 0x800 - g_display->display_area.height / 2;
    s32 right = g_display->display_area.width / 2 + 0x800;
    s32 bottom = g_display->display_area.height / 2 + 0x800;
    LibScreenVertex quad[4];

    if (unk2c4_0)
    {
        if (unk2c4_1)
        {
            unk2b0 -= unk2b8;

            if (unk2b0 <= 0.0f)
            {
                unk2c4_2 = 1;
            }
        }
        else
        {
            unk2b0 += unk2ac / 10.0f * unk2b8;

            if (!(unk2b0 < unk2ac))
            {
                unk2c4_1 = 1;
                unk2b0 -= 10.0f;
            }
        }

        unk2b4 += 0.2f * unk2b8;

        if (!(unk2b4 < 6.2831855f))
        {
            unk2b4 -= 6.2831855f;
        }

        LibClass172120Entry ring[7];
        float angle;
        float radius = 4.0f * (unk2b0 / unk2ac);
        angle = unk2b4;

        for (s32 i = 0; i < 7; i++, angle += 0.8975979f)
        {
            ring[i].x = radius * lib_cosine(angle);
            ring[i].y = radius * lib_sine(angle);
        }

        float width = right - left;
        float height = bottom - top;
        row = 0;

        for (float y = 1.0f; y < height; y += 32.0f)
        {
            index = row;

            for (float x = 0.0f; x < width; x += 32.0f)
            {
                quad[0].u = x;
                quad[0].v = y;
                quad[1].u = x;
                quad[1].v = 32.0f + y;
                quad[2].u = 32.0f + x;
                quad[2].v = y;
                quad[3].u = 32.0f + x;
                quad[3].v = 32.0f + y;
                s32 point = index;

                for (s32 k = 0; k < 4; k++)
                {
                    quad[k].x = quad[k].u + ring[point].x;
                    quad[k].y = quad[k].v + ring[point].y;

                    if (++point >= 7)
                    {
                        point -= 7;
                    }

                    switch (D_001B655C)
                    {
                    case 1:
                        quad[k].v *= 1.2307693f;
                        break;
                    case 2:
                        quad[k].v *= 0.61538464f;
                        break;
                    }
                }

                func_0044D9C0(this, 4, quad, D_001B6694 - unk2bc, 0x80808080, 0, 0);
                index += 2;

                if (index >= 7)
                {
                    index -= 7;
                }
            }

            if (++row >= 7)
            {
                row -= 7;
            }
        }
    }

    // TODO: The original reuses row and index for the ring centre; their spill slots only match that way.
    row = (right - left) / 2;
    index = (bottom - top) / 2;

    for (i = 0; i < 6; i++)
    {
        if (!records[i].enabled)
        {
            continue;
        }

        float angle;
        float offset;
        float cosine;
        float size = records[i].size;
        offset = records[i].offset;
        LibClass172120Entry previous[6];
        angle = 0.0f;

        for (s32 step = 0; step < 33; step++, angle += 0.19634955f)
        {
            cosine = lib_cosine(angle);
            float sine = lib_sine(angle);
            LibClass172120Entry current[6];
            current[0].x = row + cosine * (offset + size);
            current[0].y = index + sine * (offset + size);
            current[1].x = row + cosine * (offset + 0.25f * size);
            current[1].y = index + sine * (offset + 0.25f * size);
            current[2].x = row + cosine * (offset + 0.75f * size);
            current[2].y = index + sine * (offset + 0.75f * size);
            current[3].x = row + cosine * offset;
            current[3].y = index + sine * offset;
            current[4].x = row + cosine * (offset + 0.4f * size);
            current[4].y = index + sine * (offset + 0.4f * size);
            current[5].x = row + cosine * (offset + 0.6f * size);
            current[5].y = index + sine * (offset + 0.6f * size);

            if (step == 0)
            {
                for (s32 k = 0; k < 6; k++)
                {
                    previous[k] = current[k];
                }
            }
            else
            {
                quad[0].u = quad[0].x = previous[0].x;
                quad[0].v = quad[0].y = previous[0].y;
                quad[1].u = quad[1].x = current[0].x;
                quad[1].v = quad[1].y = current[0].y;
                quad[2].u = previous[4].x;
                quad[2].v = previous[4].y;
                quad[2].x = previous[1].x;
                quad[2].y = previous[1].y;
                quad[3].u = current[4].x;
                quad[3].v = current[4].y;
                quad[3].x = current[1].x;
                quad[3].y = current[1].y;

                for (s32 k = 0; k < 4; k++)
                {
                    switch (D_001B655C)
                    {
                    case 1:
                        quad[k].v *= 1.2307693f;
                        break;
                    case 2:
                        quad[k].v *= 0.61538464f;
                        break;
                    }
                }

                func_0044D9C0(this, 4, quad, D_001B6694 - unk2bc, 0x80808080, 0, 0);
                quad[0].u = previous[4].x;
                quad[0].v = previous[4].y;
                quad[0].x = previous[1].x;
                quad[0].y = previous[1].y;
                quad[1].u = current[4].x;
                quad[1].v = current[4].y;
                quad[1].x = current[1].x;
                quad[1].y = current[1].y;
                quad[2].u = previous[5].x;
                quad[2].v = previous[5].y;
                quad[2].x = previous[2].x;
                quad[2].y = previous[2].y;
                quad[3].u = current[5].x;
                quad[3].v = current[5].y;
                quad[3].x = current[2].x;
                quad[3].y = current[2].y;

                for (s32 k = 0; k < 4; k++)
                {
                    switch (D_001B655C)
                    {
                    case 1:
                        quad[k].v *= 1.2307693f;
                        break;
                    case 2:
                        quad[k].v *= 0.61538464f;
                        break;
                    }
                }

                func_0044D9C0(this, 4, quad, D_001B6694 - unk2bc, 0x80808080, 0, 0);
                quad[0].u = previous[5].x;
                quad[0].v = previous[5].y;
                quad[0].x = previous[2].x;
                quad[0].y = previous[2].y;
                quad[1].u = current[5].x;
                quad[1].v = current[5].y;
                quad[1].x = current[2].x;
                quad[1].y = current[2].y;
                quad[2].u = quad[2].x = previous[3].x;
                quad[2].v = quad[2].y = previous[3].y;
                quad[3].u = quad[3].x = current[3].x;
                quad[3].v = quad[3].y = current[3].y;

                for (s32 k = 0; k < 4; k++)
                {
                    switch (D_001B655C)
                    {
                    case 1:
                        quad[k].v *= 1.2307693f;
                        break;
                    case 2:
                        quad[k].v *= 0.61538464f;
                        break;
                    }
                }

                func_0044D9C0(this, 4, quad, D_001B6694 - unk2bc, 0x80808080, 0, 0);

                for (s32 k = 0; k < 6; k++)
                {
                    previous[k] = current[k];
                }
            }

        }
    }

    func_0044E080(this);
    unk63 = 1;
}

/** @brief Allocate the packet buffer over a buffer of its own and clear the records. */
LibClass172080::LibClass172080()
{
    type_id = 0x4201;
    draw_flags |= 0x400;
    LibVector4 origin;
    origin.w = 1.0f;
    origin.x = 0.0f;
    origin.y = 0.0f;
    origin.z = 0.0f;
    set_translation_vector(&origin);
    unk2c0 = static_cast<u8*>(func_00433880(0x20080, 0));

    if (unk2c0)
    {
        packet = new (0) LibPacketBuffer;

        LibPacketBuffer* buffer = packet;

        if (buffer)
        {
            buffer->unk00 = reinterpret_cast<u8*>((u32)unk2c0 | EE_UNCACHED_ACCELERATED);
            buffer->unk14 = 1;
            buffer->unk10 = 0x4000;
            resident_packet_rewind(buffer);
        }
    }

    unk2c4_0 = 0;
    unk2c4_1 = 0;
    unk2c4_2 = 0;
    unk2b4 = 0;
    unk2bc = 0x80;

    for (s32 i = 0; i < 6; i++)
    {
        records[i].enabled = 0;
    }

    unk260 = 0;
}

/**
 * Transform owner that sends a DMA chain built at 0x150 and draws through a display of its own, with vtable
 * D_172120 in main data. It runs a timed transition (func_003F1160) on itself and on the held LibClass172080.
 */
class LibClass172120 : public LibTransformOwner, public DmaSubmission
{
public:
    /** @brief Set up the transform, its packet buffer, entry array and own display, with the transition idle. */
    LibClass172120();

    virtual ~LibClass172120();

    /**
     * @brief Finish the object's packet.
     * @param channel DMA channel; unused.
     */
    virtual void complete_dma(u32 channel);

    /**
     * @brief Start the object's DMA chain on channel 1 (VIF1).
     * @param channel DMA channel; unused.
     */
    virtual void submit_dma(u32 channel);

    /**
     * @brief Report the list kind used when registration requests the default.
     * @return Always 14.
     */
    virtual s32 get_default_list_kind();

    /** @brief Destroy the transform, then the held object. */
    virtual void destroy();

    virtual void update();

    /** @brief Queue this object's DMA submission on the VIF1 queue. */
    virtual void render();

    /** @brief Use draw bucket 7. */
    virtual void set_default_draw_bucket();

    /**
     * @brief Return a bounding sphere that covers everything.
     * @return Sphere at the origin with a huge radius.
     */
    virtual const LibVector4* get_bounding_sphere();

    /**
     * @brief Build this object's packet.
     * @param matrix View matrix.
     * @param context Packet building context.
     */
    virtual void build_packet(const void* matrix, void* context);

    LibCameraContext* display;
    LibPacketBuffer* packet;
    void* unk9c;
    LibClass172120Entry* unka0;
    LibListObject* held;
    u8 unka8[8];
    u32 unkb0;
    float unkb4;
    float unkb8;
    float unkbc;
    float unkc0;
    float unkc4;
    float unkc8;
    float unkcc;
    float unkd0;
    float unkd4;
    float unkd8;
    float unkdc;
    u32 unke0;
    u8 unke4[4];
    float unke8;
    u32* unkec;
    u32* unkf0;
    u8 unkf4[4];
    u8 unkf8;
    u8 unkf9;
    u8 unkfa;
    u8 unkfb;
    u32 unkfc;
    s32 unk100;
    u32 unk104;
    u8 unk108[0x48];
    u8 chain[0x840];
    DmaSourceTag* chain_cursor;
    u64* packet_start;
};

/**
 * @brief Start a timed transition unless one is running: store its mode, duration and rate, and in mode 1 the step
 *        towards 208. When unkf9 is 1 it also starts the held object's own transition.
 * @param object Object to update.
 * @param mode Transition mode.
 * @param duration Duration.
 * @param rate Rate the step is derived from.
 */
extern "C" void func_003F1160(LibClass172120* object, u8 mode, float duration, float rate)
{
    if (!(object->unkc8 <= 0.0f && object->unkcc <= 0.0f))
    {
        return;
    }

    object->unkfa = mode;
    object->unkd0 = duration;
    object->unkd4 = rate;
    object->unkc8 = 1e-05f;
    object->unkcc = 1e-05f;

    if (mode == 1)
    {
        object->unkdc = (208.0f - object->unkc4) / duration;
    }

    if (object->unkf9 == 1)
    {
        object->unkc0 = 1.0f;
        LibClass172080* target = static_cast<LibClass172080*>(object->held);

        if (target)
        {
            target->unk2c4_0 = 1;
            target->unk2ac = duration;
            target->unk2b0 = 0;
            target->unk2b8 = g_frame_ticks;
            target->unk2bc = 0xF6;
        }
    }

    object->unkd8 = -object->unkc0 / object->unkd4;
}

/** GS A+D packet that flushes the texture cache and sets context 2's texture, blend and test state. */
struct LibTextureStatePacket
{
    GsGifTag tag;
    GsRegisterValue registers[6];
};

/**
 * @brief Add the texture state packet to the region's packet: TEXFLUSH, TEXCLUT, TEX1_2, ALPHA_2, TEST_2 and TEXA.
 * @param object Region whose packet to extend.
 */
extern "C" void func_003F1250(LibClipRegion* object)
{
    LibTextureStatePacket* state = reinterpret_cast<LibTextureStatePacket*>(resident_packet_reserve(object->packet, 7));

    if (state == 0)
    {
        return;
    }

    state->tag.tag = GIF_TAG_NREG(1) | GIF_TAG_EOP | 6;
    state->tag.registers = 0;
    state->tag.fields.register0 = GIF_REGISTER_AD;
    state->registers[0].data = 1;
    state->registers[0].address = GS_REGISTER_TEXFLUSH;
    state->registers[1].data = 4;
    state->registers[1].address = GS_REGISTER_TEXCLUT;
    state->registers[2].data = 0x61;
    state->registers[2].address = GS_REGISTER_TEX1_2;
    state->registers[3].data = 0x44;
    state->registers[3].address = GS_REGISTER_ALPHA_2;
    state->registers[4].data = 0x5000D;
    state->registers[4].address = GS_REGISTER_TEST_2;
    state->registers[5].data = 0x8000008080ULL;
    state->registers[5].address = GS_REGISTER_TEXA;
    resident_packet_align_cursor(object->packet, reinterpret_cast<u8*>(state + 1));
}

/** Second entry of the ALPHA_2 table D_004ED320, which the original reads through its own label. */
extern "C" u64 D_004ED328[];

/** Screen-space rectangle of the display area, centred on the GS 0x800 origin. */
struct LibScreenBounds
{
    s32 left;
    s32 top;
    s32 right;
    s32 bottom;
};

/**
 * @brief Get the display area's rectangle around the GS origin.
 * @param bounds Rectangle to fill.
 * @param display Display whose area to use.
 */
static inline void lib_screen_bounds(LibScreenBounds* bounds, LibCameraContext* display)
{
    bounds->left = 0x800 - display->display_area.width / 2;
    bounds->top = 0x800 - display->display_area.height / 2;
    bounds->right = display->display_area.width / 2 + 0x800;
    bounds->bottom = display->display_area.height / 2 + 0x800;
}

/**
 * @brief Draw the captured screen strips. In mode 1 each strip's upload chain is sent straight to the GIF and the
 *        strip is drawn flat; in mode 0 the uploads are chained, each strip is drawn as two quads warped by the
 *        unka0 grid, and then the display's second frame buffer is drawn back over the screen in 64x32 tiles.
 * @param object Object whose capture to draw.
 * @param mode 1 for the flat pass, 0 for the warped pass.
 */
extern "C" void func_003F1330(LibClass172120* object, s32 mode)
{
    u32 buffer = reinterpret_cast<u32>(object->unk9c) + 0x7F & ~0x7F;
    // TODO: The original converts the width to float and sign-extends the height at run time, so they're locals.
    s32 width = 0x200;
    s16 height = 0x1A0;
    LibScreenBounds bounds;
    lib_screen_bounds(&bounds, g_display);
    s32 step;
    s32 strip_height;

    if (mode)
    {
        step = 40960.0f / width;

        if (resident_get_system()->progressive)
        {
            strip_height = 0x1C0;
        }
        else
        {
            strip_height = 0xE0;
        }
    }
    else
    {
        strip_height = height;
        step = 0x40;
    }

    for (s32 i = 0; i < object->unk100; i++)
    {
        LibTextureRequest* request = reinterpret_cast<LibTextureRequest*>(buffer | 0x20000000);
        u64* cursor;

        if (((reinterpret_cast<u32>(object->chain_cursor) & 0x0FFFFFFF) - reinterpret_cast<u32>(object->chain)) >> 4 <
            0x7E)
        {
            u64* packet = reinterpret_cast<u64*>(request + 1);
            u32 qwords = request->size >> 4;
            packet[4] = (packet[4] & ~(0x3FFFULL << 32)) | ((u64)object->unk104 >> 6) << 32;

            if (mode)
            {
                (object->chain_cursor++)->control =
                    DMA_TAG(qwords + 7, DMA_TAG_ID_REF, reinterpret_cast<u32>(packet + 2) & 0x0FFFFFFF);
                (object->chain_cursor++)->control = DMA_TAG_ID_END;
                DmaChannel* dma = sceDmaGetChan(2);
                dma->chcr.tag_transfer_enable = 0;
                FlushCache(0);
                sceDmaSend(dma, reinterpret_cast<void*>(reinterpret_cast<u32>(object->chain_cursor - 2) & 0x0FFFFFFF));
            }
            else
            {
                (object->chain_cursor++)->control =
                    DMA_TAG(qwords + 8, DMA_TAG_ID_REF, reinterpret_cast<u32>(packet) & 0x0FFFFFFF);
            }
        }

        resident_packet_add_register(object->packet, GS_REGISTER_TEXFLUSH, 0);
        resident_packet_set_tex0_2(object->packet, g_texture_cache->entries[g_texture_cache->slot_entries[0x3F]].tex0);

        if (mode)
        {
            cursor = reinterpret_cast<u64*>(resident_packet_reserve(object->packet, 4));

            if (!cursor)
            {
                return;
            }

            *cursor++ = GIF_TAG_NREG(4) | GIF_TAG_FLG_REGLIST | GIF_TAG_EOP | 1;
            *cursor = 0;
            reinterpret_cast<GsGifTag*>(cursor - 1)->fields.register0 = GIF_REGISTER_UV;
            reinterpret_cast<GsGifTag*>(cursor - 1)->fields.register1 = GIF_REGISTER_XYZ2;
            reinterpret_cast<GsGifTag*>(cursor - 1)->fields.register2 = GIF_REGISTER_UV;
            reinterpret_cast<GsGifTag*>(cursor - 1)->fields.register3 = GIF_REGISTER_XYZ2;
            cursor++;
            *cursor++ = 0;
            *cursor++ = ((s64)(bounds.top << 4) << 16 | ((bounds.left + i * step) << 4)) |
                        (s64)(D_001B6694 - 1 - (s32)object->unke0) << 32;
            *cursor++ = (s64)(s32)(request->width << 4 | (u16)request->height << 20);
            *cursor++ = ((s64)((strip_height + bounds.top) << 4) << 16 | ((bounds.left + (i + 1) * step) << 4)) |
                        (s64)(D_001B6694 - 1 - (s32)object->unke0) << 32;
            resident_packet_align_cursor(object->packet, reinterpret_cast<u8*>(cursor));
            sceGsSyncPath(0, 0);
            resident_packet_send(object->packet);
            sceGsSyncPath(0, 0);
        }
        else
        {
            for (s32 j = 0; j < 2; j++)
            {
                LibClass172120Entry* points = &object->unka0[i * 4 + j * 2];
                float max_x;
                float left = points[0].x;
                max_x = ee_max(left, points[1].x);
                max_x = ee_max(max_x, points[2].x);
                max_x = ee_max(max_x, points[3].x);
                float max_y = ee_max_in_place(points[0].y, points[1].y);
                max_y = ee_max(max_y, points[2].y);
                max_y = ee_max(max_y, points[3].y);

                if (max_x <= 65536.0f && max_y <= 65536.0f)
                {
                    if (points[0].x <= 0.0f && points[1].x <= 0.0f)
                    {
                        continue;
                    }

                    if (points[2].x <= 0.0f && points[3].x <= 0.0f)
                    {
                        continue;
                    }

                    if (points[0].y <= 0.0f && points[1].y <= 0.0f)
                    {
                        continue;
                    }

                    if (points[2].y <= 0.0f && points[3].y <= 0.0f)
                    {
                        continue;
                    }

                    cursor = reinterpret_cast<u64*>(resident_packet_reserve(object->packet, 5));

                    if (!cursor)
                    {
                        return;
                    }

                    *cursor++ = GIF_TAG_NREG(8) | GIF_TAG_FLG_REGLIST | GIF_TAG_EOP | 1;
                    *cursor = 0;
                    reinterpret_cast<GsGifTag*>(cursor - 1)->fields.register0 = GIF_REGISTER_UV;
                    reinterpret_cast<GsGifTag*>(cursor - 1)->fields.register1 = GIF_REGISTER_XYZ2;
                    reinterpret_cast<GsGifTag*>(cursor - 1)->fields.register2 = GIF_REGISTER_UV;
                    reinterpret_cast<GsGifTag*>(cursor - 1)->fields.register3 = GIF_REGISTER_XYZ2;
                    reinterpret_cast<GsGifTag*>(cursor - 1)->fields.register4 = GIF_REGISTER_UV;
                    reinterpret_cast<GsGifTag*>(cursor - 1)->fields.register5 = GIF_REGISTER_XYZ2;
                    reinterpret_cast<GsGifTag*>(cursor - 1)->fields.register6 = GIF_REGISTER_UV;
                    reinterpret_cast<GsGifTag*>(cursor - 1)->fields.register7 = GIF_REGISTER_XYZ2;
                    cursor++;
                    *cursor++ = (s64)(s32)((s32)(((u32)object->unkc4 & 0xFFFF) << 20) | (j * request->width / 2) << 4);
                    *cursor++ = (s64)(s32)(u16)(u32)points[0].x | (u64)((u32)points[0].y & 0xFFFF) << 16 |
                                (s64)(D_001B6694 - 1 - (s32)object->unke0) << 32;
                    *cursor++ = (s64)(s32)((s32)(((u16)request->height - ((u32)object->unkc4 & 0xFFFF)) << 20) |
                                           (j * request->width / 2) << 4);
                    *cursor++ = (s64)(s32)(u16)(u32)points[1].x | (u64)((u32)points[1].y & 0xFFFF) << 16 |
                                (s64)(D_001B6694 - 1 - (s32)object->unke0) << 32;
                    *cursor++ =
                        (s64)(s32)((s32)(((u32)object->unkc4 & 0xFFFF) << 20) | ((j + 1) * request->width / 2) << 4);
                    *cursor++ = (s64)(s32)(u16)(u32)points[2].x | (u64)((u32)points[2].y & 0xFFFF) << 16 |
                                (s64)(D_001B6694 - 1 - (s32)object->unke0) << 32;
                    *cursor++ = (s64)(s32)((s32)(((u16)request->height - ((u32)object->unkc4 & 0xFFFF)) << 20) |
                                           ((j + 1) * request->width / 2) << 4);
                    *cursor++ = (s64)(s32)(u16)(u32)points[3].x | (u64)((u32)points[3].y & 0xFFFF) << 16 |
                                (s64)(D_001B6694 - 1 - (s32)object->unke0) << 32;
                    resident_packet_align_cursor(object->packet, reinterpret_cast<u8*>(cursor));
                }
            }

            cursor = reinterpret_cast<u64*>(resident_packet_reserve(object->packet, 0));

            if (!cursor)
            {
                return;
            }

            if (reinterpret_cast<u8*>(cursor) != reinterpret_cast<u8*>(object->unkf0) + 0x10)
            {
                *cursor++ = GIF_TAG_EOP;
                *cursor++ = 0;
                resident_packet_align_cursor(object->packet, reinterpret_cast<u8*>(cursor));
                u32 start = reinterpret_cast<u32>(object->packet_start) & 0x0FFFFFFF;
                s32 qwords = ((reinterpret_cast<u32>(cursor) & 0x0FFFFFFF) - start) >> 4;
                u64 address = (u64)start << 32;
                (object->chain_cursor++)->control = (s64)qwords | DMA_TAG_ID_REF | address;
                *object->unkec = VIF_DIRECTHL(qwords - 1);
                object->packet_start = cursor;
                object->unkf0 = reinterpret_cast<u32*>(cursor);
                *cursor = 0;
                *object->unkf0 = 0x11000000;
                cursor++;
                *cursor = 0;
                *reinterpret_cast<u32*>(cursor) = 0x06008000;
                object->unkec = reinterpret_cast<u32*>(cursor) + 1;
                cursor++;
                resident_packet_align_cursor(object->packet, reinterpret_cast<u8*>(cursor));
            }
        }

        buffer += object->unkfc & ~0xF;
    }

    if (mode)
    {
        return;
    }

    LibPacketBuffer* packet = object->packet;
    packet->unk15 = 1;
    u32 color;

    if (object->unkf9 == 0)
    {
        resident_packet_set_alpha_2(object->packet, D_004ED330[0]);
        color = (u32)(128.0f * object->unkc0) << 24 | 0x848484;
    }
    else
    {
        u64 alpha = D_004ED328[0];
        resident_packet_set_alpha_2(object->packet, alpha);
        color = (u32)(128.0f * object->unkc0) << 24 | 0x808080;
    }

    u64* cursor = reinterpret_cast<u64*>(resident_packet_reserve(object->packet, 8));

    if (!cursor)
    {
        return;
    }

    *cursor++ = GIF_TAG_NREG(1) | GIF_TAG_EOP | 7;
    reinterpret_cast<GsGifTag*>(cursor - 1)->fields.register0 = GIF_REGISTER_AD;
    cursor++;
    *cursor++ = 0x15;
    *cursor++ = GS_REGISTER_TEX1_2;
    *cursor++ = 0x356;
    *cursor++ = GS_REGISTER_PRIM;
    *cursor++ = color;
    *cursor++ = GS_REGISTER_RGBAQ;
    *cursor++ = 1;
    *cursor++ = GS_REGISTER_COLCLAMP;
    *cursor++ = *reinterpret_cast<const u32*>(&g_display->buffers[0].environment.context1.depth_buffer);
    *cursor++ = GS_REGISTER_ZBUF_2;
    *cursor++ = 0x30000;
    *cursor++ = GS_REGISTER_TEST_2;
    *cursor++ = 0x60;
    *cursor++ = GS_REGISTER_TEXA;
    resident_packet_align_cursor(object->packet, reinterpret_cast<u8*>(cursor));
    s32 texture = g_display->buffers[1].environment.context1.frame.base_pointer << 5;
    LibScreenBounds screen;
    lib_screen_bounds(&screen, g_display);
    float scale_x;
    float scale_y;
    g_display->get_area_scale(&scale_x, &scale_y);
    float fields = resident_get_system()->progressive ? 2.0f : 1.0f;
    s32 page_step = 0x20;

    for (float y = 0.0f; y < 224.0f * fields; y += 32.0f)
    {
        for (float x = 0.0f; x < 640.0f; x += 64.0f)
        {
            cursor = reinterpret_cast<u64*>(resident_packet_reserve(object->packet, 4));

            if (!cursor)
            {
                return;
            }

            *cursor++ = GIF_TAG_NREG(6) | GIF_TAG_FLG_REGLIST | GIF_TAG_EOP | 1;
            *cursor = 0;
            reinterpret_cast<GsGifTag*>(cursor - 1)->fields.register0 = GIF_REGISTER_TEX0_2;
            reinterpret_cast<GsGifTag*>(cursor - 1)->fields.register1 = GIF_REGISTER_UV;
            reinterpret_cast<GsGifTag*>(cursor - 1)->fields.register2 = GIF_REGISTER_XYZ2;
            reinterpret_cast<GsGifTag*>(cursor - 1)->fields.register3 = GIF_REGISTER_UV;
            reinterpret_cast<GsGifTag*>(cursor - 1)->fields.register4 = GIF_REGISTER_XYZ2;
            reinterpret_cast<GsGifTag*>(cursor - 1)->fields.register5 = GIF_REGISTER_NOP;
            cursor++;
            *cursor++ = (s64)texture | (0x58104000 | 5ULL << 32);
            *cursor++ = 0;
            *cursor++ = (s64)(D_001B6694 - (s32)object->unke0) << 32 |
                        ((s64)(s32)(16.0f * (screen.left + x * scale_x)) |
                         (s64)(s32)(16.0f * (screen.top + y * scale_y / fields)) << 16);
            *cursor++ = 0x02000400;
            *cursor++ = (s64)(D_001B6694 - (s32)object->unke0) << 32 |
                        ((s64)(s32)(16.0f * (screen.left + (64.0f + x) * scale_x)) |
                         (s64)(s32)(16.0f * (screen.top + (32.0f + y) * scale_y / fields)) << 16);
            *cursor++ = 0;
            resident_packet_align_cursor(object->packet, reinterpret_cast<u8*>(cursor));
            texture += page_step;
        }
    }
}

/**
 * @brief Start the object's DMA chain on channel 1 (VIF1).
 * @param channel DMA channel; unused.
 */
void LibClass172120::submit_dma(u32 channel)
{
    dma_pending = 1;
    *D1_QWC = 0;
    *D1_TADR = reinterpret_cast<u32>(chain) & 0x0FFFFFFF;
    *D_STAT = D_STAT_CIS1;
    *D1_CHCR = DMA_CHCR_START | DMA_CHCR_MODE_CHAIN | DMA_CHCR_DIR_FROM_MEMORY;
}

/**
 * @brief Finish the object's packet.
 * @param channel DMA channel; unused.
 */
void LibClass172120::complete_dma(u32 channel)
{
    lib_finish_packet(this);
}

/** @brief Queue this object's DMA submission on the VIF1 queue. */
void LibClass172120::render()
{
    resident_dma_queue_push(g_vif1_dma_queue, this);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", build_packet__14LibClass172120FPCvPv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", update__14LibClass172120Fv);

extern "C" void func_003F3E60(void* object, u32 value)
{
    *(u32*)((u8*)object + 0x14) = value;
}

extern "C" u32 func_003F3E70(const void* object)
{
    return *(const u32*)((const u8*)object + 0x3C78);
}

extern "C" void func_003F3E80(void* object, u32 value)
{
    *(u32*)((u8*)object + 0x4) = value;
}

extern "C" void func_003F3E90(void* object, u32 value)
{
    *(u32*)((u8*)object + 0x8C) = value;
}

/**
 * @brief Make the renderer, its passes and the global display pointers draw on a display.
 * @param renderer Renderer.
 * @param display Display to draw on.
 */
extern "C" void func_003F3EA0(LibRenderer* renderer, LibCameraContext* display)
{
    renderer->set_display(display);
}

extern "C" void* func_003F3EF0(void* object)
{
    return (u8*)object + 0x3C60;
}

extern "C" void func_003F3F00(void* object, u32 value)
{
    *(u32*)((u8*)object + 0x3C7C) = value;
}

#define LIB_CLASS_172120_TEXTURE_TAG 0x4A6F686E

/** @brief Release the class's texture and its buffers. */
LibClass172120::~LibClass172120()
{
    g_texture_cache->release_texture(LIB_CLASS_172120_TEXTURE_TAG, 0x3F);
    ::operator delete(unk9c);
    delete packet;

    if (unka0)
    {
        ::operator delete[](reinterpret_cast<u8*>(unka0) - 0x10);
    }
}

/** @brief Set up the transform, its packet buffer, entry array and own display, with the transition idle. */
LibClass172120::LibClass172120()
{
    unk9c = 0;
    display = 0;
    packet = 0;
    held = 0;
    unka0 = 0;
    unkec = 0;
    unkf8 = 0;
    unk104 = 0;
    unke8 = g_frame_ticks;
    unke0 = 0x100;
    unk65 = 0;
    draw_flags = 0x400;
    LibVector4 origin;
    origin.w = 1.0f;
    origin.x = 0.0f;
    origin.y = 0.0f;
    origin.z = 0.0f;
    set_translation_vector(&origin);
    type_id = 0x4200;
    float scale_x;
    float scale_y;
    g_display->get_area_scale(&scale_x, &scale_y);
    unkfc = 0xD090;
    unk100 = 8;
    unkb0 = 0;
    unkb8 = 1.0f;
    unkc0 = 0.0f;
    unkbc = 0.005f;
    unkc4 = 0.0f;
    unkb4 = 0.01f;
    unkc8 = 0.0f;
    unkcc = 0.0f;
    unkf9 = 0;
    static_cast<LibRenderer*>(g_renderer)->unk4458->unk9d = 0;
    packet = new (0) LibPacketBuffer(0x400);
    unka0 = new (0) LibClass172120Entry[(unk100 * 2 + 1) * 2];
    display = new (0) LibCameraContext;

    if (display)
    {
        display->initialize(2);
    }

    FlushCache(0);
}

/** @brief Destroy the held object, then leave the owner's list and delete this object. */
void LibClass171FD0::update()
{
    if (held)
    {
        held->destroy();
        held = 0;
    }

    lib_object_detach_owner(this);
    delete this;
}

/** @brief Destroy the transform, then the held object. */
void LibClass172120::destroy()
{
    LibTransformOwner::destroy();

    if (held)
    {
        held->destroy();
        held = 0;
    }
}

/**
 * @brief Return the list kind.
 * @return Nine.
 */
s32 LibClass171FD0::get_default_list_kind()
{
    return 9;
}

LibClass171FD0::~LibClass171FD0()
{
}

/** @brief Default preparation hook; does nothing. */
void LibDmaCallbacks::on_packet_complete(u32 value)
{
}

/** @brief Clear the transform's first state byte. */
void LibTransformOwner::set_default_draw_bucket()
{
    draw_bucket = 0;
}

/** @brief Leave the default transform update hook unchanged. */
void LibTransformOwner::render()
{
}

/**
 * @brief Leave the default transform output handler unchanged.
 * @param matrix Unused matrix.
 * @param context Unused caller context.
 */
void LibTransformOwner::build_packet(const void* matrix, void* context)
{
}

/** @brief Delete the extra buffer. */
LibClass172080::~LibClass172080()
{
    if (unk2c0)
    {
        delete unk2c0;
    }
}

/** @brief Update through the base. */
void LibClass172080::update()
{
    LibClass1748D0::update();
}

/** @brief Draw in bucket 8. */
void LibClass1748D0::set_default_draw_bucket()
{
    draw_bucket = 8;
}

/**
 * @brief Read the cached combined transformation matrix.
 * @return Pointer to the stored matrix; this call does not update it.
 */
const LibMatrix44Value* LibTransform::get_transform_matrix()
{
    return &transform;
}

/**
 * @brief Read the additional local translation.
 * @return Stored translation vector; only xyz is used to build the offset matrix.
 */
const LibVector4* LibTransform::get_offset_translation() const
{
    return &offset_translation;
}

/**
 * @brief Read the additional local rotation.
 * @return Stored quaternion in x, y, z, w order.
 */
const LibVector4* LibTransform::get_offset_rotation() const
{
    return &offset_rotation;
}

/**
 * @brief Read the additional local scale.
 * @return Stored scale vector; only xyz is used to build the offset matrix.
 */
const LibVector4* LibTransform::get_offset_scale() const
{
    return &offset_scale;
}

/**
 * @brief Report the list kind used when registration requests the default.
 * @return Always 14.
 */
s32 LibClass172120::get_default_list_kind()
{
    return 14;
}

/** @brief Use draw bucket 7. */
void LibClass172120::set_default_draw_bucket()
{
    draw_bucket = 7;
}

// TODO: Returns the address of a local, as the original does: a sphere at the origin with radius 1e30.
/**
 * @brief Return a bounding sphere that covers everything.
 * @return Sphere at the origin with a huge radius.
 */
const LibVector4* LibClass172120::get_bounding_sphere()
{
    s32 stack[4];
    stack[0] = 0;
    stack[3] = 0x7149F2CA;
    stack[1] = 0;
    s32* result = stack;
    stack[2] = 0;
    return reinterpret_cast<const LibVector4*>(result);
}

extern "C" u8 D_001B64A8;

/** Per-level rows of six learned codes, picked by a slot's row index. */
extern "C" const u8* D_004EC22C[];

/**
 * @brief Build a party slot's record at its level and learn the codes of its row.
 *
 * Slots outside zero through two, or at a level outside one through ten, only
 * get the default record. Each learned code also takes the next battle skill
 * index entry. The battle strategy is reset and the first anti-attack aura chosen.
 * @param slot Party slot, from zero through two, or -1.
 * @param output Record func_004076D0 fills.
 * @param equipment Character equipment record.
 */
void LibClass3F5B80::func_003F45F0(s32 slot, LibResourceRecordC4* output, LibCharacterEquipment* equipment)
{
    LibClass3F5B80Buffer* data = buffer;
    s32 level;
    const u8* codes;
    s32 i;

    if (slot >= 0 && slot < 3)
    {
        level = data->unk678[slot];
    }
    else
    {
        level = -1;
    }

    if (level <= 0 || level > 10)
    {
        func_004076D0(reinterpret_cast<LibCharacterRecord*>(output), equipment, 0);
        return;
    }

    D_001B64A8 = 1;
    func_004076D0(reinterpret_cast<LibCharacterRecord*>(output), equipment, level);
    D_001B64A8 = 0;
    codes = D_004EC22C[level] + data->unk67B[slot] * 6;

    for (i = 0; i < 6; i++)
    {
        s32 code = codes[i];
        bool learned = false;

        if (code > 0 && code < 30)
        {
            s32 amount;

            if (code == 1)
            {
                if (level == 9)
                {
                    amount = 980;
                }
                else
                {
                    amount = 175;
                }
            }
            else
            {
                amount = 120;
            }

            func_0040A370(equipment, level, code, amount);
            learned = true;
        }
        else if (code >= 30 && code < 155)
        {
            func_0040A5C0(equipment, level, code, code == 0x92 ? 705 : 150);
            learned = true;
        }

        if (learned)
        {
            set_battle_skill_index(equipment, i, func_0040AE00(level, code));
        }
    }

    equipment->battle_strategy = 0;
    equipment->character_resource_variant = data->unk675[slot];
    equipment->encoded_anti_attack_aura_mask = 1 ^ 0x77;
    set_tactical_skill_state(equipment, 4, 1);
}

/**
 * @brief Store the halfword at 0x66C, using 1000 for values outside 0 to 999.
 * @param value Value to store.
 */
void LibClass3F5B80::func_003F49E0(s32 value)
{
    if (!(-1 < value && value < 1000))
    {
        value = 1000;
    }

    buffer->unk66C = value;
}

/**
 * @brief Store a byte in one of three backing-buffer slots.
 * @param index Slot index.
 * @param value Byte value.
 */
void LibClass3F5B80::func_003F4A10(s32 index, u8 value)
{
    if (index <= -1 || index >= 3)
    {
        return;
    }

    buffer->unk67B[index] = value;
}

/**
 * @brief Store a byte in one of three backing-buffer slots.
 * @param index Slot index.
 * @param value Byte value.
 */
void LibClass3F5B80::func_003F4A50(s32 index, u8 value)
{
    if (index <= -1 || index >= 3)
    {
        return;
    }

    buffer->unk678[index] = value;
}

/**
 * @brief Store a byte in one of three backing-buffer slots.
 * @param index Slot index.
 * @param value Byte value.
 */
void LibClass3F5B80::func_003F4A90(s32 index, u8 value)
{
    if (index <= -1 || index >= 3)
    {
        return;
    }

    buffer->unk675[index] = value;
}

/**
 * @brief Read an entry's state byte when the index is in range.
 * @param index Entry index.
 * @return The state byte, or zero when the index is invalid.
 */
u8 LibClass3F5B80::func_003F4AD0(s32 index)
{
    if (index >= 0)
    {
        if (index < 0x1A)
        {
            return buffer->entries[index].unk04;
        }
    }

    return 0;
}

/**
 * @brief Read an entry's first word when the index is in range.
 * @param index Entry index.
 * @return The word, or zero when the index is invalid.
 */
u32 LibClass3F5B80::func_003F4B10(s32 index)
{
    if (index >= 0)
    {
        if (index < 0x1A)
        {
            return buffer->entries[index].unk00;
        }
    }

    return 0;
}

/**
 * @brief Return an entry's signed 16-bit value when the index is in range.
 * @param index Entry index.
 * @return The entry value, or -1 when the index is invalid.
 */
s32 LibClass3F5B80::func_003F4B50(s32 index)
{
    if (index >= 0)
    {
        if (index < 0x1A)
        {
            return buffer->entries[index].unk06;
        }
    }

    return -1;
}

/**
 * @brief Store a halfword value in the backing buffer, mapping -1 to 0x37.
 * @param value Value to store.
 */
void LibClass3F5B80::func_003F4B90(s32 value)
{
    if ((s16)value == -1)
    {
        value = 0x37;
    }

    buffer->unk668 = value;
}

/**
 * @brief Store two values in an entry when the index is in range.
 * @param index Entry index.
 * @param value Word value.
 * @param state Byte value.
 */
void LibClass3F5B80::func_003F4BC0(s32 index, u32 value, u8 state)
{
    if (index >= 0)
    {
        if (index < 0x1A)
        {
            LibClass3F5B80Entry* entry = &buffer->entries[index];
            entry->unk00 = value;
            entry->unk04 = state;
        }
    }
}

extern "C" const u8 D_004EC0D0[0x1A];

/** @brief Put the 26 entries in the order of the table at D_004EC0D0. */
void LibClass3F5B80::func_003F4BF0()
{
    LibClass3F5B80Entry sorted[0x1A];

    LibClass3F5B80Entry* out = sorted;

    for (s32 i = 0; i < 0x1A; i++, out++)
    {
        LibClass3F5B80Entry* entry = &buffer->entries[D_004EC0D0[i]];
        out->unk00 = entry->unk00;
        out->unk04 = entry->unk04;
        out->unk06 = entry->unk06;
    }

    memcpy_guess(buffer, sorted, sizeof(sorted));
}

/** @brief Copy the buffer's three records into resident entries 2 and 3. */
void LibClass3F5B80::func_003F4DE0()
{
    ResidentEntryTable* table = resident_get_entry_table(resident_get_system());
    u8* first = reinterpret_cast<u8*>(resident_find_entry(table, 2));
    u8* second = reinterpret_cast<u8*>(resident_find_entry(table, 3));

    for (s32 i = 0; i < 3; i++)
    {
        memcpy_guess(first, buffer->unk0E0[i], 0xC4);
        memcpy_guess(second, buffer->unk32C[i], 0x114);
        first += 0xC4;
        second += 0x114;
    }
}

/** The party members' record pointers func_003F9860 fills: three character records, then their equipment. */
struct LibPartyRecords
{
    LibCharacterRecord* records[3];
    LibCharacterEquipment* equipment[3];
};

/**
 * @brief Set up the preset battle party.
 * @param party The three members' record pointers.
 * @param mode Battle buffer halfword 0x66A.
 * @param first_name Name for character 1.
 * @param second_name Name for character 2.
 */
extern "C" void func_003F64A0(LibPartyRecords* party, s32 mode, char* first_name, char* second_name);

extern "C" const u16 D_00143BFE[];
extern "C" const s16 D_004EBFB0[];
extern "C" const u8 D_004EC0C0[];
extern "C" const s16 D_004EBEB0[];
extern "C" const s16 D_004EBFD0[];
extern "C" const s16 D_004EC010[];
extern "C" const s16 D_004EBFEC[];

/** Battle music override: an ID and kind pair and the track it picks. */
struct LibBattleTrackRow
{
    u16 id;
    u8 kind;
    u8 track;
};

extern "C" LibBattleTrackRow D_004EB980[];

// TODO: The track column is read through its own symbol; one table read as `.track` folds the +3 into the load.
extern "C" u8 D_004EB983[];

/**
 * @brief Set the battle up: store the settings, copy (or, for a preset battle, rebuild) the three party records,
 *        then fill the entry list: two fixed tracks, the area's track, each member's voice and six battle skill
 *        sounds, the battle ID's track and an override from D_004EB980.
 * @param id Battle ID.
 * @param kind Battle kind.
 * @param area Area; 0x32 sometimes becomes 0x34.
 * @param flags Option bits.
 */
void LibClass3F5B80::func_003F4EB0(s32 id, s32 kind, s32 area, u8 flags)
{
    s32 skill_kind;
    s32 skill_value;
    s32 skill_index;
    s32 skill_remainder;
    u8 party[0x20];
    char names[2][0x40];
    s32 used[6];
    LibClass3F5B80Buffer* data = buffer;
    bool preset = (data->unk0DC & 0x80) != 0;

    if (area == 0x32 && (resident_next_random_word() & 0xFFFF) < 0x4C2C)
    {
        area = 0x34;
    }

    if (preset)
    {
        area = data->unk674;
    }

    u8 clear = 0;
    data->unk673_2 = clear;
    data->unk673_3 = clear;
    data->unk673_4 = clear;
    data->unk673_0 = clear;
    data->unk0D0 = id;
    data->unk0D4 = kind;
    data->unk0D8 = area;
    data->unk670 = flags;

    if (data->unk66A >= 0 || preset)
    {
        ResidentEntryTable* table = resident_get_entry_table(resident_get_system());
        LibCharacterRecord* records = reinterpret_cast<LibCharacterRecord*>(resident_find_entry(table, 2));
        LibCharacterEquipment* equipment = reinterpret_cast<LibCharacterEquipment*>(resident_find_entry(table, 3));

        if (preset)
        {
            s32 members = data->unk671 + data->unk672;

            for (s32 i = 0; i < 3; i++)
            {
                memcpy_guess(data->unk0E0[i], records, 0xC4);
                memcpy_guess(data->unk32C[i], equipment, 0x114);

                if (i < members)
                {
                    func_003F45F0(i, reinterpret_cast<LibResourceRecordC4*>(records), equipment);
                }
                else
                {
                    func_003F45F0(-1, reinterpret_cast<LibResourceRecordC4*>(records), equipment);
                }

                records++;
                equipment++;
            }
        }
        else
        {
            for (s32 i = 0; i < 8; i++)
            {
                if (i < 3)
                {
                    memcpy_guess(data->unk0E0[i], records, 0xC4);
                    memcpy_guess(data->unk32C[i], equipment, 0x114);
                    func_003F9860(party, i, (s32)records, (s32)equipment);
                }

                if (records->character_id == 1)
                {
                    strcpy_guess(names[0], equipment->character_name);
                }
                else if (records->character_id == 2)
                {
                    strcpy_guess(names[1], equipment->character_name);
                }

                records++;
                equipment++;
            }

            func_003F64A0(reinterpret_cast<LibPartyRecords*>(party), data->unk66A, names[0], names[1]);
        }
    }

    LibClass3F5B80Entry* entry = data->entries;
    data->entries[0].unk06 = 0xD7F;

    if (area >= 0x38)
    {
        area = 0x37;
    }
    else if (area < 0)
    {
        area = 0;
    }

    data->entries[1].unk06 = area + 0xD85;

    if (data->unk673_1 || (data->unk0DC & 2))
    {
        data->entries[2].unk06 = -1;
    }
    else
    {
        data->entries[2].unk06 = D_00143BFE[data->unk668 * 2];
    }

    entry += 3;
    ResidentEntryTable* table = resident_get_entry_table(resident_get_system());
    LibCharacterRecord* records = reinterpret_cast<LibCharacterRecord*>(resident_find_entry(table, 2));
    LibCharacterEquipment* equipment = reinterpret_cast<LibCharacterEquipment*>(resident_find_entry(table, 3));
    u32 options = flags;
    u32 special = options & 0x11;
    u32 option2 = options & 2;
    u32 option4 = options & 4;
    u32 option8 = options & 8;

    for (s32 slot = 0; slot < 3; slot++)
    {
        s32 i;
        s32 character = records->character_id;

        if (character > 0)
        {
            entry->unk06 = D_004EBFB0[character - 1];
            s16 item_id = equipment_item_id(equipment, 0);
            LibGameState* state = reinterpret_cast<LibGameState*>(D_001B64F8);
            bool valid = false;

            if (item_id > 0 && item_id <= LIB_ALLOCATION_COUNT)
            {
                valid = true;
            }

            ItemCreationAllocationRecord* record =
                valid ? reinterpret_cast<ItemCreationAllocationRecord*>(&state->allocations[item_id - 1]) : 0;
            s32 count = D_004EC0C0[character - 1];
            s32 weapon = 0;

            if (record != 0)
            {
                u16 index = record->definition_index();
                weapon = (u16)D_001B64F0[index].weapon_variant;

                if (!(weapon < count) || weapon <= -1)
                {
                    weapon = 0;
                }
            }

            if (options != 0)
            {
                if (character == 1)
                {
                    if (special)
                    {
                        if (weapon == 10)
                        {
                            entry->unk06 = 0xF2C;
                        }
                        else
                        {
                            entry->unk06 = 0xF2A;
                        }

                        data->unk673_4 = 1;
                        data->unk673_2 = 1;
                    }
                    else if (option2 || data->unk66A >= 0)
                    {
                        entry->unk06 = 0xF2B;
                        data->unk673_2 = 1;
                        data->unk673_0 = 1;
                    }
                }
                else if (character == 2)
                {
                    if (option4 || data->unk66A >= 0)
                    {
                        entry->unk06 = 0xF63;
                        data->unk673_3 = 1;
                    }
                    else if (option8)
                    {
                        entry->unk06 = 0xF64;
                        data->unk673_3 = 1;
                    }
                }
            }
            else
            {
                s32 variant = equipment->character_resource_variant;

                if (preset)
                {
                    bool changed = false;

                    if (variant <= -1)
                    {
                        variant = 0;
                        changed = true;
                    }
                    else if (character == 1 || character == 2)
                    {
                        if (variant >= 6)
                        {
                            variant = 5;
                            changed = true;
                        }
                    }
                    else if (variant >= 4)
                    {
                        changed = true;
                        variant = 3;
                    }

                    if (changed)
                    {
                        equipment->character_resource_variant = variant;
                    }
                }
                else if (variant <= -1 || variant >= 4)
                {
                    equipment->character_resource_variant = 0;
                    variant = 0;
                }

                s32 voice = entry->unk06 + (weapon + variant * count);

                if (preset)
                {
                    if (character == 1)
                    {
                        if (variant == 4)
                        {
                            voice = 0xF2A;
                            data->unk673_4 = 1;
                            data->unk673_2 = 1;
                        }
                        else if (variant >= 5)
                        {
                            voice = 0xF2B;
                            data->unk673_2 = 1;
                            data->unk673_0 = 1;
                        }
                    }
                    else if (character == 2)
                    {
                        if (variant == 4)
                        {
                            voice = 0xF64;
                            data->unk673_3 = 1;
                        }
                        else if (variant >= 5)
                        {
                            voice = 0xF63;
                            data->unk673_3 = 1;
                        }
                    }
                }

                entry->unk06 = voice;
            }

            entry++;

            for (s32 i = 0; i < 6; i++)
            {
                used[i] = -1;
            }


            for (i = 0; i < 6; i++)
            {
                bool found = false;
                s32 skill = battle_skill_index(equipment, i) - 1;

                if (skill >= 0)
                {
                    s32 result = func_00408850(equipment, character, skill, &skill_kind, &skill_value, &skill_index,
                                               &skill_remainder);

                    if (result == 1 && skill_kind >= 30 && skill_kind <= 128)
                    {
                        entry->unk06 = D_004EBEB0[skill_kind - 1];
                        found = true;
                    }
                    else if (result != 0 && skill_kind > 0 && skill_kind < 30)
                    {
                        if (character == 2)
                        {
                            found = true;
                            entry->unk06 = D_004EBFD0[skill_kind - 1];
                        }
                        else if (character == 9)
                        {
                            found = true;
                            entry->unk06 = D_004EC010[skill_kind - 1];
                        }
                    }
                }

                if (!found)
                {
                    entry->unk06 = -1;
                }
                else
                {
                    s32 j;

                    for (j = 0; j < 6; j++)
                    {
                        if (entry->unk06 == used[j])
                        {
                            entry->unk06 = -1;
                            break;
                        }
                    }

                    if (j >= 6)
                    {
                        used[i] = entry->unk06;
                    }
                }

                entry++;
            }
        }
        else
        {
            for (s32 i = 0; i < 7; i++, entry++)
            {
                entry->unk06 = -1;
            }
        }

        records++;
        equipment++;
    }

    if (id > 0x16C)
    {
        id = 0x16C;
    }
    else if (id < 0)
    {
        id = 0;
    }

    if (!(data->unk0DC & 0x80))
    {
        entry->unk06 = id + 0xDBD;
        entry++;
    }
    else
    {
        entry->unk06 = -1;
        entry++;
    }

    entry->unk06 = -1;
    data->unk66F = 0;

    if (!(data->unk0DC & 0x80))
    {
        for (u32 i = 0; i < 0x14A; i++)
        {
            if (id == D_004EB980[i].id && kind == D_004EB980[i].kind)
            {
                u8* track = &D_004EB983[i * sizeof(LibBattleTrackRow)];
                entry->unk06 = D_004EBFEC[*track];
                data->unk66F = *track;
                break;
            }
        }
    }
}

/**
 * @brief Pick a new 16-byte aligned place for the buffer inside the object at random, clear it and set its defaults.
 * @param object Object to reset.
 */
static inline void reset_buffer(LibClass3F5B80* object)
{
    object->buffer = reinterpret_cast<LibClass3F5B80Buffer*>(object->unk00 + ((TIMER0_COUNT + resident_next_random_word()) & 0xF) * 16);
    memset_guess(object->buffer, 0, sizeof(LibClass3F5B80Buffer));
    LibClass3F5B80Entry* entry = object->buffer->entries;

    for (s32 i = 0; i < 0x1A; i++, entry++)
    {
        entry->unk06 = -1;
    }

    object->buffer->unk668 = 0x37;
    object->buffer->unk66A = -1;
    object->buffer->unk66C = 0x5A;
}

/** @brief Pick a new aligned buffer and reset it as the constructor does. */
void LibClass3F5B80::func_003F5AC0()
{
    reset_buffer(this);
}

/** @brief Initialize the buffer and its entry table. */
LibClass3F5B80::LibClass3F5B80()
{
    reset_buffer(this);
}

// TODO: reset() inlines the three setters and the constructor inlines reset(), so I think the unit was built with
// auto-inlining; this scoped pragma stands in for it until the flags are settled.
#pragma push
#pragma auto_inline on

/**
 * @brief Read the checked word.
 * @return The word, or zero when its two copies disagree.
 */
u32 LibProtectedValues::get_checked_word()
{
    LibProtectedRecord* values = record();

    if (values->word == (values->check ^ (LIB_PROTECTED_WORD_KEY ^ LIB_PROTECTED_CHECK_KEY)))
    {
        return values->word ^ LIB_PROTECTED_WORD_KEY;
    }

    return 0;
}

/**
 * @brief Store the checked word and its check copy.
 * @param value Word to store.
 */
void LibProtectedValues::set_checked_word(u32 value)
{
    LibProtectedRecord* values = record();
    values->word = value ^ LIB_PROTECTED_WORD_KEY;
    values->check = value ^ LIB_PROTECTED_CHECK_KEY;
}

/**
 * @brief Read the small value.
 * @return The value, 0 to LIB_PROTECTED_SMALL_MAX.
 */
s32 LibProtectedValues::get_small_value()
{
    return (record()->small_value ^ LIB_PROTECTED_SMALL_KEY) - LIB_PROTECTED_SMALL_BIAS;
}

/**
 * @brief Store the small value, clamped to 0 to LIB_PROTECTED_SMALL_MAX.
 * @param value Value to store.
 */
void LibProtectedValues::set_small_value(s32 value)
{
    value += LIB_PROTECTED_SMALL_BIAS;

    if (value > LIB_PROTECTED_SMALL_BIAS + LIB_PROTECTED_SMALL_MAX)
    {
        value = LIB_PROTECTED_SMALL_BIAS + LIB_PROTECTED_SMALL_MAX;
    }
    else if (value < LIB_PROTECTED_SMALL_BIAS)
    {
        value = LIB_PROTECTED_SMALL_BIAS;
    }

    record()->small_value = value ^ LIB_PROTECTED_SMALL_KEY;
}

/**
 * @brief Read the large value.
 * @return The value, 0 to LIB_PROTECTED_LARGE_MAX.
 */
s32 LibProtectedValues::get_large_value()
{
    LibProtectedRecord* values = record();
    return (values->large_value ^ values->large_key) - LIB_PROTECTED_LARGE_BIAS;
}

/**
 * @brief Store the large value, clamped to 0 to LIB_PROTECTED_LARGE_MAX, under a fresh random key.
 * @param value Value to store.
 */
void LibProtectedValues::set_large_value(s32 value)
{
    value += LIB_PROTECTED_LARGE_BIAS;

    if (value > LIB_PROTECTED_LARGE_BIAS + LIB_PROTECTED_LARGE_MAX)
    {
        value = LIB_PROTECTED_LARGE_BIAS + LIB_PROTECTED_LARGE_MAX;
    }
    else if (value < LIB_PROTECTED_LARGE_BIAS)
    {
        value = LIB_PROTECTED_LARGE_BIAS;
    }

    LibProtectedRecord* values = record();
    // TODO: The key is a chained assignment, not a local, so reset() and the constructor get the game's registers
    // when they inline this.
    values->large_value =
        value ^ (values->large_key = (resident_next_random_word() & 0xFFFF) + LIB_PROTECTED_LARGE_KEY_BASE);
}

/** @brief Pick a new random offset into the storage and store zero in every value. */
void LibProtectedValues::reset()
{
    u32 seed = D_001B65B8 = 1664525L * D_001B65B8 + 1013904223L;
    key = ((resident_input_get_seconds(resident_system_get_input(resident_get_system())) +
            (seed + TIMER0_COUNT * resident_next_random_word())) &
           0xF) *
          8;
    key ^= LIB_PROTECTED_OFFSET_KEY;
    set_large_value(0);
    set_small_value(0);
    set_checked_word(0);
}

/** @brief Release both owned buffers. */
LibBufferOwner::~LibBufferOwner()
{
    ::operator delete(second);
    ::operator delete(first);
}

/** @brief Allocate the storage at a random size and offset and store zero in every value. */
LibProtectedValues::LibProtectedValues()
{
    s32 count;

    // TODO: count is read before it's set, so the decoy's size comes from whatever the register held. That's the
    // game's code.
    decoy = new (0) u8[(count + 0x24D + resident_next_random_word()) % 150];
    count = resident_random_below(80) + 1;

    for (s32 i = 0; i < count; i++)
    {
        lib_light_random();
    }

    storage = new (0) u8[resident_random_below(20) * 16 + 0xA8];
    reset();
}

#pragma pop

/**
 * @brief Set up the preset battle party: clear all three members, rebuild characters 1 and 2 with their names and
 *        battle strategy, give character 1 two codes and four battle skills, and give both fixed hit points, MP,
 *        fury and base stats. Mode 3 also sets character 1's aura mask and a tactical skill, and character 2's first
 *        two symbology masteries.
 * @param party The three members' record pointers.
 * @param mode Battle buffer halfword 0x66A.
 * @param first_name Name for character 1.
 * @param second_name Name for character 2.
 */
extern "C" void func_003F64A0(LibPartyRecords* party, s32 mode, char* first_name, char* second_name)
{
    for (s32 i = 0; i < 3; i++)
    {
        func_004076D0(party->records[i], party->equipment[i], 0);
    }

    LibCharacterRecord* first = party->records[0];
    LibCharacterRecord* second = party->records[1];
    LibCharacterEquipment* first_equipment = party->equipment[0];
    LibCharacterEquipment* second_equipment = party->equipment[1];
    func_004076D0(first, first_equipment, 1);
    func_004076D0(second, second_equipment, 2);
    copy_character_name(first_equipment->character_name, first_name);
    copy_character_name(second_equipment->character_name, second_name);
    first_equipment->battle_strategy = 5;
    second_equipment->battle_strategy = 5;
    func_0040A5C0(first_equipment, 1, 0x1F, 8);
    func_0040A5C0(first_equipment, 1, 0x23, 8);
    set_battle_skill_index(first_equipment, 0, func_0040AE00(1, 0x1F));
    set_battle_skill_index(first_equipment, 1, func_0040AE00(1, 0x1F));
    set_battle_skill_index(first_equipment, 2, func_0040AE00(1, 0x23));
    set_battle_skill_index(first_equipment, 3, func_0040AE00(1, 0x23));

    if (mode == 3)
    {
        store_aura_mask(first_equipment, 3);
        set_tactical_skill_state(first_equipment, 4, 1);
        store_symbology_mastery(second_equipment, 0, 1);
        store_symbology_mastery(second_equipment, 1, 1);
    }

    raise_base_hp(first, 0xB45);
    raise_base_hp(first, character_base_hp(first) + 0x64F);
    raise_max_hp(first, 0xB45);
    raise_max_hp(first, character_max_hp(first) + 0x64F);
    lower_hp(first, 0xB45);
    lower_hp(first, character_hp(first) + 0x64F);
    raise_base_mp(first, 0x3A0);
    raise_base_mp(first, character_base_mp(first) + 0x16);
    raise_max_mp(first, 0x3A0);
    raise_max_mp(first, character_max_mp(first) + 0x16);
    lower_mp(first, 0x3A0);
    lower_mp(first, character_mp(first) + 0x16);
    store_character_unk28(first, 100.0f);
    store_character_max_fury(first, 100.0f);
    set_character_fury(first, 100.0f);
    raise_base_attack(first, 50);
    raise_base_defense(first, 10);
    raise_base_agility(first, 20);
    raise_base_hit(first, 20);
    set_character_intelligence(first, 20);
    store_base_knockback_power(first, 64);
    store_base_knockback_resistance(first, 40);
    store_character_flags(first, 0);
    raise_base_hp(second, 0x501);
    raise_base_hp(second, character_base_hp(second) + 0x207);
    raise_max_hp(second, 0x501);
    raise_max_hp(second, character_max_hp(second) + 0x207);
    lower_hp(second, 0x501);
    lower_hp(second, character_hp(second) + 0x207);
    raise_base_mp(second, 0x67);
    raise_base_mp(second, character_base_mp(second) + 0x449);
    raise_max_mp(second, 0x67);
    raise_max_mp(second, character_max_mp(second) + 0x449);
    lower_mp(second, 0x67);
    lower_mp(second, character_mp(second) + 0x449);
    store_character_unk28(second, 100.0f);
    store_character_max_fury(second, 100.0f);
    set_character_fury(second, 100.0f);
    raise_base_attack(second, 40);
    raise_base_defense(second, 40);
    raise_base_agility(second, 20);
    raise_base_hit(second, 20);
    set_character_intelligence(second, 20);
    store_base_knockback_power(second, 64);
    store_base_knockback_resistance(second, 40);
    store_character_flags(second, 0);
}
