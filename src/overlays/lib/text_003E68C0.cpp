#include "include_asm.h"
#include "overlays/lib/text_003E68C0.h"
#include "overlays/lib/dma_callbacks_inlines.h"
#include "overlays/lib/text_0044ABE0.h"
#include "overlays/lib/text_00429B00.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/text_004DD440.h"
#include "overlays/lib/clip_region.h"
#include "overlays/lib/text_004095C0.h"
#include "main/resident_data.h"
#include "main/entry_table.h"
#include "main/system.h"
#include "main/utility.h"

/** Bounding sphere objects without bounds report: centred on the origin, radius 1000000. */
extern "C" LibVector4 g_default_bounding_sphere;

struct LibStateByteB4View
{
    u8 pad00[0x60];
    u8 state60;
    u8 pad61[0x53];
    u8 stateB4;
};

struct LibWordPairView
{
    u32 unk00;
    u32 unk04;
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", draw__14LibClass171DA0Fv);

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

extern "C" void func_003EEDE0(void* object)
{
    LibStateByteB4View* state = (LibStateByteB4View*)object;
    state->state60 = state->stateB4;
}

/** Build a four-word stack value and return its address. */
void* func_003EEDF0(void)
{
    s32 stack[4];
    stack[0] = 0;
    stack[3] = 0x7149F2CA;
    stack[1] = 0;
    s32* result = stack;
    stack[2] = 0;
    return result;
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
 * @param value Notification value; unused.
 */
void LibClipRegion::on_packet_notify(u32 value)
{
    dma_pending = 1;
    *D1_QWC = packet_quadwords;
    *D1_MADR = packet_address;
    *D_STAT = D_STAT_CIS1;
    *D1_CHCR = DMA_CHCR_START | DMA_CHCR_DIR_FROM_MEMORY;
}

/**
 * @brief Finish the region's packet.
 * @param value Notification value; unused.
 */
void LibClipRegion::on_packet_complete(u32 value)
{
    lib_finish_packet(this);
}

/** Queue the DMA submission embedded at offset 0x90 when present. */
s32 func_003EF090(void* object)
{
    DmaSubmission* submission = reinterpret_cast<DmaSubmission*>(object);

    if (object != 0)
    {
        submission = (DmaSubmission*)((u8*)submission + 0x90);
    }

    return resident_dma_queue_push(g_vif1_dma_queue, submission);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003EF0C0);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", __ct__13LibClipRegionFv);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", build_packet__14LibClass171F40FPCvPv);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", build_packet__14LibClass172080FPCvPv);

/** One of LibClass172080's six records; only its enable bit is known. */
struct LibClass172080Record
{
    u8 unk00[8];
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

    s32 unk260;
    LibClass172080Record records[6];
    u8 unk2ac[8];
    s32 unk2b4;
    u8 unk2b8[4];
    s32 unk2bc;
    u8* unk2c0;
    u8 unk2c4_0 : 1;
    u8 unk2c4_1 : 1;
    u8 unk2c4_2 : 1;
    u8 unk2c4_3_7 : 5;
};

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F1160);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F1250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F1330);

/**
 * Transform owner that sends a DMA chain built at 0x150, with vtable D_172120 in main data. Its update is
 * func_003F2CB0 and its destructor func_003F3F10; only its DMA callbacks are written so far.
 */
class LibClass172120 : public LibTransformOwner, public LibDmaCallbacks
{
public:
    /** @brief Release the class's texture and its buffers. */
    virtual ~LibClass172120();

    /**
     * @brief Finish the object's packet.
     * @param value Notification value; unused.
     */
    virtual void on_packet_complete(u32 value);

    /**
     * @brief Start the object's DMA chain on channel 1 (VIF1).
     * @param value Notification value; unused.
     */
    virtual void on_packet_notify(u32 value);

    /** @brief Destroy the transform, then the held object. */
    virtual void destroy();

    u8 unk94[4];
    LibPacketBuffer* packet;
    void* unk9c;
    u8* unka0;
    LibListObject* held;
    u8 unka8[0xA8];
    u8 chain[0x10];
};

/**
 * @brief Start the object's DMA chain on channel 1 (VIF1).
 * @param value Notification value; unused.
 */
void LibClass172120::on_packet_notify(u32 value)
{
    dma_pending = 1;
    *D1_QWC = 0;
    *D1_TADR = reinterpret_cast<u32>(chain) & 0x0FFFFFFF;
    *D_STAT = D_STAT_CIS1;
    *D1_CHCR = DMA_CHCR_START | DMA_CHCR_MODE_CHAIN | DMA_CHCR_DIR_FROM_MEMORY;
}

/**
 * @brief Finish the object's packet.
 * @param value Notification value; unused.
 */
void LibClass172120::on_packet_complete(u32 value)
{
    lib_finish_packet(this);
}

/** Queue the DMA submission embedded at offset 0x90 when present. */
s32 func_003F2570(void* object)
{
    DmaSubmission* submission = reinterpret_cast<DmaSubmission*>(object);

    if (object != 0)
    {
        submission = (DmaSubmission*)((u8*)submission + 0x90);
    }

    return resident_dma_queue_push(g_vif1_dma_queue, submission);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F25A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F2CB0);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F3EA0);

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
        ::operator delete[](unka0 - 0x10);
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F4070);

extern "C" void* func_003F42A0(void* object)
{
    LibWordPairView* state = (LibWordPairView*)object;
    state->unk04 = 0;
    state->unk00 = 0;
    return object;
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
 * @brief Return the fixed value 14.
 * @param object Receiver or first argument; unused.
 * @return Always 14.
 */
extern "C" s32 func_003F4550(void* object)
{
    return 14;
}

extern "C" void func_003F4560(LibTransformOwner* object)
{
    object->draw_bucket = 7;
}

/** Build a four-word stack value and return its address. */
void* func_003F4570(void)
{
    s32 stack[4];
    stack[0] = 0;
    stack[3] = 0x7149F2CA;
    stack[1] = 0;
    s32* result = stack;
    stack[2] = 0;
    return result;
}






INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F45F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F49E0);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F4BF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F4DE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F4EB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F5AC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F5B80);

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
    u32 key = (resident_next_random_word() & 0xFFFF) + LIB_PROTECTED_LARGE_KEY_BASE;
    values->large_key = key;
    values->large_value = value ^ key;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", reset__18LibProtectedValuesFv);

/** @brief Release both owned buffers. */
LibBufferOwner::~LibBufferOwner()
{
    ::operator delete(second);
    ::operator delete(first);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F6000);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F64A0);
