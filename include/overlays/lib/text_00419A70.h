#ifndef SO3_OVERLAYS_LIB_TEXT_00419A70_H
#define SO3_OVERLAYS_LIB_TEXT_00419A70_H

#include "types.h"
#include "overlays/lib/text_004BD360.h"

#ifdef __cplusplus
/** Partial 0x58-byte list indicator with vtable D_1725D0: a bar showing how far a list is scrolled. */
class LibListIndicator : public LibWidget
{
public:
    /** @brief Initialize the widget storage and select kind 3. */
    inline LibListIndicator();

    virtual ~LibListIndicator();

    /** @brief Draw the list indicator. */
    virtual void draw();

    /**
     * @brief Select widget kind 3, then place the indicator and set its scroll extent and position.
     * @param x Horizontal position.
     * @param y Vertical position.
     * @param height Bar height.
     * @param extent Size of one scroll step, as a share of the bar.
     * @param position Scroll position.
     */
    inline LibListIndicator(float x, float y, float height, float extent, float position);

    /**
     * @brief Set the scroll position and mark the indicator for redraw.
     * @param value Position, from 0 to 100.
     */
    void set_position(float value)
    {
        position = value;
        needs_redraw = 1;
    }

    /**
     * @brief Set the indicator's extent and mark it for redraw.
     * @param value New extent, in percent of the track.
     */
    void set_extent(float value)
    {
        extent = value;
        needs_redraw = 1;
    }

    LibStorageBlock0C unk40;
    u8 unk4c[4];
    float extent;
    float position;
};

/** Partial widget with resident vtable at 0x172870. */
class ItemCreationClass172870 : public LibWidget
{
public:
    /** @brief Initialize the widget storage and select kind 6. */
    inline ItemCreationClass172870();

    virtual ~ItemCreationClass172870();

    /** @brief Draw the marker widget. */
    virtual void draw();

    LibStorageBlock0C unk40;
    u8 unk4c[4];
    u32 unk50;
    u32 unk54;
};

/** Partial widget with resident vtable at 0x172600. */
class ItemCreationClass172600 : public LibWidget
{
public:
    /** @brief Initialize the widget storage and select kind 5. */
    inline ItemCreationClass172600();

    virtual ~ItemCreationClass172600();

    /** @brief Advance the scalar indicator and mark it for refresh. */
    virtual void func_00413D20();

    /** @brief Draw the scalar indicator. */
    virtual void draw();

    LibStorageBlock0C unk40;
    u8 unk4c[4];
    float unk50;
};


/** Partial Lib widget with vtable D_174790 in main data. */
class LibClass174790 : public LibWidget
{
public:
    virtual ~LibClass174790();

    LibStorageBlock0C unk40;
};

/** Number of slots in use in the first retained set; trailing empty slots are trimmed. */
extern "C" u8 D_001B650C;

/** First retained set: objects, and the byte tag each was added with. */
extern "C" LibListObject* D_00507CD0[64];
extern "C" u8 D_00507DD0[64];

/** Number of slots in use in the second retained set; trailing empty slots are trimmed. */
extern "C" u8 D_001B6514;

/** Second retained set: objects, and the byte tag each was added with. */
extern "C" LibListObject* D_00507E50[64];
extern "C" u8 D_00507E10[64];

/**
 * @brief Take an object out of the first retained set, trimming the set when it was the last one.
 * @param object Object to remove.
 */
extern "C" void func_00428C80(LibListObject* object);

/**
 * @brief Take an object out of the second retained set, trimming the set when it was the last one.
 * @param object Object to remove.
 */
extern "C" void func_004289B0(LibListObject* object);

/** Point (0, 0, 0, 1): the transforms' local origin. */
extern "C" LibVector4 D_00507F60;

/** Link solver constants: x and y unused here, z the share a fixed point's partner takes when its weight is tiny, w a scale for the correction. */
extern "C" LibVector4 D_00507F50;

/** Direction (0, -1, 0, 1): the transforms' local down axis. */
extern "C" LibVector4 D_00507F70;

/** Partial Lib transform with vtable D_172A20 in main data, kept in the second retained set. */
class LibClass172A20 : public LibTransform
{
public:
    LibClass172A20()
    {
        unk210 = 0;
        unk214 = 0;
    }

    /** @brief Take the transform out of the second retained set unless unk210 is set, then destroy it. */
    virtual ~LibClass172A20()
    {
        if (!unk210)
        {
            func_004289B0(this);
        }
    }

    /**
     * @brief Report the list kind used when registration requests the default.
     * @return Always 4.
     */
    virtual s32 get_default_list_kind();

    u8 unk210;
    u32 unk214;
};

/** Partial Lib transform with vtable D_172AB0 in main data, kept in the first retained set. */
class LibClass172AB0 : public LibTransform
{
public:
    LibClass172AB0()
    {
        unk210 = 0;
    }

    /** @brief Take the transform out of the first retained set unless unk210 is set, then destroy it. */
    virtual ~LibClass172AB0()
    {
        if (!unk210)
        {
            func_00428C80(this);
        }
    }

    /**
     * @brief Report the list kind used when registration requests the default.
     * @return Always 4.
     */
    virtual s32 get_default_list_kind();

    /** @brief Update the world-space shape. */
    virtual void update();

    /** @brief Bring the world-space shape up to date; the base shape has none. */
    virtual void func_00425280();

    /**
     * @brief Test against another shape; the base shape never touches anything.
     * @param other Other shape.
     * @param direction Receives a unit direction between the shapes.
     * @param first Receives a distance.
     * @param second Receives a depth.
     * @return Nonzero when the shapes touch.
     */
    virtual s32 func_004284E0(LibClass172AB0* other, LibVector4* direction, float* first, float* second);

    /**
     * @brief Test against another shape with a scale; the base shape never touches anything.
     * @param other Other shape.
     * @param scale Scale vector.
     * @param direction Receives a unit direction between the shapes.
     * @param first Receives a distance.
     * @param second Receives a depth.
     * @return Nonzero when the shapes touch.
     */
    virtual s32 func_004284F0(LibClass172AB0* other, const LibVector4* scale, LibVector4* direction, float* first,
                              float* second);

    u8 unk210;
};

/** Field mask new LibClass172BD0 fields start with. */
extern "C" u32 D_001B6508;

/** Word new LibClass173050 objects start with at 0x1C. */
extern "C" u32 D_001B6504;

/** Flag byte new LibClass173050 objects start with at 0x1B. */
extern "C" u8 D_001B6510;

/** Partial Lib transform with vtable D_172BD0 in main data. */
class LibClass172BD0 : public LibTransform
{
public:
    /** @brief Start with the default field mask. */
    LibClass172BD0()
    {
        field_mask = D_001B6508;
    }

    virtual ~LibClass172BD0()
    {
    }

    /**
     * @brief Work out the effect at a position; the base adds nothing.
     * @param position Position, in world space.
     * @param unk Unused by every implementation seen so far.
     * @param output Receives the effect.
     * @param source Object the effect applies to; its word at 0x1C is a mask.
     */
    virtual void func_00428500(const LibVector4* position, const void* unk, LibVector4* output, const void* source);

    u32 field_mask;
};

/** Partial LibClass172BD0 with vtable D_172B40 in main data. */
class LibClass172B40 : public LibClass172BD0
{
public:
    LibClass172B40()
    {
    }

    virtual ~LibClass172B40();

    /**
     * @brief Report the list kind used when registration requests the default.
     * @return Always 4.
     */
    virtual s32 get_default_list_kind();

    /** @brief Update the matrix and the world position. */
    virtual void update();

    /**
     * @brief Work out the effect at a position.
     * @param position Position, in world space.
     * @param unk Unused.
     * @param output Receives the effect.
     * @param source Object the effect applies to; its word at 0x1C is a mask.
     */
    virtual void func_00428500(const LibVector4* position, const void* unk, LibVector4* output, const void* source);

    float unk220;
    float unk224;
    float unk228;
    u8 unk22c[4];
    LibVector4 position;
};

/** Partial LibClass172BD0 with vtable D_172C60 in main data. */
class LibClass172C60 : public LibClass172BD0
{
public:
    LibClass172C60()
    {
    }

    virtual ~LibClass172C60();

    /** @brief Update the matrices, the inverse copy and the world down axis. */
    virtual void update();

    /**
     * @brief Work out the effect at a position.
     * @param position Position, in world space.
     * @param unk Unused.
     * @param output Receives the effect.
     * @param source Object the effect applies to; its word at 0x1C is a mask.
     */
    virtual void func_00428500(const LibVector4* position, const void* unk, LibVector4* output, const void* source);

    LibMatrix44Value inverse;
    LibVector4 down;
    float unk270;
    float unk274;
    float unk278;
    float unk27c;
};

/** Partial LibClass172BD0 with vtable D_172CF0 in main data. */
class LibClass172CF0 : public LibClass172BD0
{
public:
    LibClass172CF0()
    {
    }

    virtual ~LibClass172CF0();

    /** @brief Update the matrix and the world down axis. */
    virtual void update();

    /**
     * @brief Work out the effect at a position.
     * @param position Position, in world space.
     * @param unk Unused.
     * @param output Receives the effect.
     * @param source Object the effect applies to; its word at 0x1C is a mask.
     */
    virtual void func_00428500(const LibVector4* position, const void* unk, LibVector4* output, const void* source);

    float unk220;
    float unk224;
    u8 unk228[8];
    LibVector4 down;
};

/** Partial LibClass172A20 with vtable D_172D80 in main data. */
class LibClass172D80 : public LibClass172A20
{
public:
    LibClass172D80()
    {
    }

    virtual ~LibClass172D80();

    /** @brief Update the matrices, the world position and the world down axis. */
    virtual void update();

    /**
     * @brief Keep a sphere on the outside of the shape.
     * @param position Sphere centre, in world space.
     * @param output Receives the corrected centre.
     * @param radius Sphere radius.
     * @return Whether the centre was moved.
     */
    virtual bool func_00425870(const LibVector4* position, LibVector4* output, float radius);

    LibVector4 down;
    LibVector4 position;
    float extent_x;
    float extent_z;
};

/** Partial LibClass172A20 with vtable D_172E10 in main data. */
class LibClass172E10 : public LibClass172A20
{
public:
    LibClass172E10()
    {
    }

    virtual ~LibClass172E10();

    /** @brief Update the matrices. */
    virtual void update();

    /**
     * @brief Keep a sphere on the outside of the shape.
     * @param position Sphere centre, in world space.
     * @param output Receives the corrected centre.
     * @param radius Sphere radius.
     * @return Whether the centre was moved.
     */
    virtual bool func_00425870(const LibVector4* position, LibVector4* output, float radius);

    LibVector4 extent;
};

/** Partial LibClass172A20 with vtable D_172EA0 in main data. */
class LibClass172EA0 : public LibClass172A20
{
public:
    LibClass172EA0()
    {
    }

    virtual ~LibClass172EA0();

    /** @brief Update the matrix, the world position and the world down axis. */
    virtual void update();

    /**
     * @brief Keep a sphere on the outside of the shape.
     * @param position Sphere centre, in world space.
     * @param output Receives the corrected centre.
     * @param radius Sphere radius.
     * @return Whether the centre was moved.
     */
    virtual bool func_00425870(const LibVector4* position, LibVector4* output, float radius);

    LibVector4 down;
    LibVector4 position;
};

/** Partial LibClass172AB0 with vtable D_172F30 in main data. */
class LibClass172F30 : public LibClass172AB0
{
public:
    LibClass172F30()
    {
    }

    virtual ~LibClass172F30();

    /** @brief Update the matrix and the world position. */
    virtual void func_00425280();

    /**
     * @brief Test against another shape.
     * @param other Other shape.
     * @param direction Receives a unit direction between the shapes.
     * @param first Receives a distance.
     * @param second Receives a depth.
     * @return Nonzero when the shapes touch.
     */
    virtual s32 func_004284E0(LibClass172AB0* other, LibVector4* direction, float* first, float* second);

    /**
     * @brief Test against another shape with a scale.
     * @param other Other shape.
     * @param scale Scale vector.
     * @param direction Receives a unit direction between the shapes.
     * @param first Receives a distance.
     * @param second Receives a depth.
     * @return Nonzero when the shapes touch.
     */
    virtual s32 func_004284F0(LibClass172AB0* other, const LibVector4* scale, LibVector4* direction, float* first,
                              float* second);

    float unk220;
    u8 unk224[0xC];
    LibVector4 position;
};

/** Partial LibClass172AB0 with vtable D_172FC0 in main data. */
class LibClass172FC0 : public LibClass172AB0
{
public:
    LibClass172FC0()
    {
    }

    virtual ~LibClass172FC0();

    /** @brief Update the matrix and move the local point and axis into world space. */
    virtual void func_00425280();

    /**
     * @brief Test against another shape.
     * @param other Other shape.
     * @param direction Receives a unit direction between the shapes.
     * @param first Receives a distance.
     * @param second Receives a depth.
     * @return Nonzero when the shapes touch.
     */
    virtual s32 func_004284E0(LibClass172AB0* other, LibVector4* direction, float* first, float* second);

    /**
     * @brief Test against another shape with a scale.
     * @param other Other shape.
     * @param scale Scale vector.
     * @param direction Receives a unit direction between the shapes.
     * @param first Receives a distance.
     * @param second Receives a depth.
     * @return Nonzero when the shapes touch.
     */
    virtual s32 func_004284F0(LibClass172AB0* other, const LibVector4* scale, LibVector4* direction, float* first,
                              float* second);

    float unk220;
    u8 unk224[0xC];
    LibVector4 local_point;
    LibVector4 local_axis;
    LibVector4 point;
    LibVector4 axis;
};

class LibImageCapture;

/** Partial Lib transform owner with vtables D_172630 (primary) and D_1726A4 (DMA submission) in main data. */
class LibClass172630 : public LibTransformOwner, public DmaSubmission
{
public:
    /** @brief Set the object up and allocate its packet. */
    LibClass172630();

    /** @brief Delete the packet and destroy the object. */
    virtual ~LibClass172630();

    /** @brief Clear the owner and queue the object for release. */
    virtual void destroy();

    /** @brief Queue the object's DMA submission on VIF1. */
    virtual void render();

    /** @brief Draw in bucket 7. */
    virtual void set_default_draw_bucket();

    /**
     * @brief Return the bounding sphere Lib culls against.
     * @return Sphere in a local of this function: zero centre and a radius of 1e30, so the object is never culled.
     */
    virtual const LibVector4* get_bounding_sphere();

    /**
     * @brief Build the object's packet.
     * @param matrix Matrix supplied by the caller.
     * @param context Opaque caller context.
     */
    virtual void build_packet(const void* matrix, void* context);

    /**
     * @brief Send the packet on VIF1 in normal mode.
     * @param channel DMA channel; unused.
     */
    virtual void submit_dma(u32 channel);

    /**
     * @brief Finish the packet.
     * @param channel DMA channel; unused.
     */
    virtual void complete_dma(u32 channel);

    u8 unk94[4];
    LibPacketBuffer* packet;
    u32 packet_quadwords;
    float unka0;
    u32 unka4;
    u32 color;
    u8 unkac;
    u8 unkad;
    u8 unkae;
    u8 unkaf;
    u8 unkb0[0x10];
};

/** Partial Lib transform owner with vtables D_1726C0 (primary) and D_172734 (DMA submission) in main data. */
class LibClass1726C0 : public LibTransformOwner, public DmaSubmission
{
public:
    /** @brief Set the object up and allocate its packet. */
    LibClass1726C0();

    /** @brief Delete the packet and destroy the object. */
    virtual ~LibClass1726C0();

    /** @brief Clear the owner and queue the object for release. */
    virtual void destroy();

    /** @brief Queue the object's DMA submission on VIF1. */
    virtual void render();

    /** @brief Draw in bucket 7. */
    virtual void set_default_draw_bucket();

    /**
     * @brief Return the bounding sphere Lib culls against.
     * @return Sphere in a local of this function: zero centre and a radius of 1e30, so the object is never culled.
     */
    virtual const LibVector4* get_bounding_sphere();

    /**
     * @brief Build the object's packet.
     * @param matrix Matrix supplied by the caller.
     * @param context Opaque caller context.
     */
    virtual void build_packet(const void* matrix, void* context);

    /**
     * @brief Send the packet on VIF1 in normal mode.
     * @param channel DMA channel; unused.
     */
    virtual void submit_dma(u32 channel);

    /**
     * @brief Finish the packet.
     * @param channel DMA channel; unused.
     */
    virtual void complete_dma(u32 channel);

    LibCameraContext* display;
    LibPacketBuffer* packet;
    u32 packet_quadwords;
    float unka0;
    u32 unka4;
    u32 color;
    u8 unkac;
    u8 unkad;
    u8 unkae;
    u8 unkaf;
    u8 unkb0[0x10];
};

/** Partial Lib transform owner with vtables D_172750 (primary) and D_1727C4 (DMA submission) in main data. */
class LibClass172750 : public LibTransformOwner, public DmaSubmission
{
public:
    /** @brief Set the object up and allocate its packet. */
    LibClass172750();

    /** @brief Delete the packet and destroy the object. */
    virtual ~LibClass172750();

    /** @brief Clear the owner and queue the object for release. */
    virtual void destroy();

    /** @brief Queue the object's DMA submission on VIF1. */
    virtual void render();

    /** @brief Draw in bucket 7. */
    virtual void set_default_draw_bucket();

    /**
     * @brief Return the bounding sphere Lib culls against.
     * @return Sphere in a local of this function: zero centre and a radius of 1e30, so the object is never culled.
     */
    virtual const LibVector4* get_bounding_sphere();

    /**
     * @brief Build the object's packet.
     * @param matrix Matrix supplied by the caller.
     * @param context Opaque caller context.
     */
    virtual void build_packet(const void* matrix, void* context);

    /**
     * @brief Send the packet on VIF1 in normal mode.
     * @param channel DMA channel; unused.
     */
    virtual void submit_dma(u32 channel);

    /**
     * @brief Finish the packet.
     * @param channel DMA channel; unused.
     */
    virtual void complete_dma(u32 channel);

    LibCameraContext* display;
    LibPacketBuffer* packet;
    u32 packet_quadwords;
    u32 packet_address;
    u8 unka4[4];
    u64 tex0;
};

/** Partial Lib transform owner with vtables D_1727E0 (primary) and D_172854 (DMA submission) in main data. */
class LibClass1727E0 : public LibTransformOwner, public DmaSubmission
{
public:
    /** @brief Set the object up and allocate its packet. */
    LibClass1727E0();

    /** @brief Delete the packet and destroy the object. */
    virtual ~LibClass1727E0();

    /** @brief Clear the owner and queue the object for release. */
    virtual void destroy();

    /** @brief Queue the object's DMA submission on VIF1. */
    virtual void render();

    /** @brief Draw in bucket 7. */
    virtual void set_default_draw_bucket();

    /**
     * @brief Return the bounding sphere Lib culls against.
     * @return Sphere in a local of this function: zero centre and a radius of 1e30, so the object is never culled.
     */
    virtual const LibVector4* get_bounding_sphere();

    /**
     * @brief Build the object's packet.
     * @param matrix Matrix supplied by the caller.
     * @param context Opaque caller context.
     */
    virtual void build_packet(const void* matrix, void* context);

    /**
     * @brief Send the packet on VIF1 in normal mode.
     * @param channel DMA channel; unused.
     */
    virtual void submit_dma(u32 channel);

    /**
     * @brief Finish the packet.
     * @param channel DMA channel; unused.
     */
    virtual void complete_dma(u32 channel);

    s16 vram_slot;
    u8 unk96;
    u8 unk97;
    u8 unk98;
    u8 unk99;
    u8 unk9a;
    u8 width_log2;
    u8 height_log2;
    u8 unk9d;
    u8 unk9e;
    u8 unk9f;
    float unka0[4];
    u32 unkb0;
    u32 unkb4;
    u32 unkb8[8];
    float unkd8;
    float unkdc[8];
    float unkfc[8];
    float unk11c;
    u32 packet_quadwords;
    u32 vram_address;
    LibCameraContext* display;
    LibPacketBuffer* packet;
};

/**
 * @brief Allocate VRAM for a power-of-two image and record its size, slot and address.
 * @param object Object to set up.
 * @param width_log2 Image width, as a power of two.
 * @param height_log2 Image height, as a power of two.
 */
extern "C" void func_004209C0(LibClass1727E0* object, s32 width_log2, s32 height_log2);


/** Partial Lib object with vtable D_1728A0 in main data that owns an image capture. */
class LibClass1728A0 : public LibListObject
{
public:
    /** @brief Create the image capture and add it to the renderer. */
    LibClass1728A0();

    /** @brief Release the image capture and destroy the object. */
    virtual ~LibClass1728A0();

    /**
     * @brief Report the list kind used when registration requests the default.
     * @return Always 16.
     */
    virtual s32 get_default_list_kind();

    /** @brief Release the image capture, then delete the object. */
    virtual void destroy();

    /**
     * @brief Read back the 16 by 16 depth block centred on (x, y) and record the share of its values below the
     *        threshold. The first update only starts the read.
     */
    virtual void update();

    /** @brief Detach and destroy the image capture, if there is one. */
    inline void release_capture();

    /**
     * @brief Set the screen point to sample and the depth to compare against.
     * @param px Screen x.
     * @param py Screen y.
     * @param depth Depth threshold.
     */
    void set_query(s32 px, s32 py, u32 depth)
    {
        x = px;
        y = py;
        threshold = depth;
    }

    void* unk14;
    void* unk18;
    u8 unk1c;
    u8 unk1d[3];
    u8 depth[0x400];
    s32 x;
    s32 y;
    u32 threshold;
    float coverage;
    LibImageCapture* capture;
    u8 unk434[0xC];
};

/** One ray of a LibClass1728E0 burst: its angle and two lengths for each segment. */
struct LibLightRay
{
    float angle;
    float first[8];
    float second[8];
};

/** Partial packet builder base with vtable D_1728C0 in main data; its two builder slots are pure. */
class LibClass1728C0 : public LibListSentinel
{
public:
    LibClass1728C0()
    {
    }

    virtual ~LibClass1728C0()
    {
    }

    /**
     * @brief Write the object's GIF data at a cursor.
     * @param cursor Where to write.
     * @param x Centre x, in screen pixels.
     * @param y Centre y, in screen pixels.
     * @param color Packed RGB color the object's own color is modulated by.
     * @param scale Size scale.
     * @param angle Rotation in radians.
     * @param alpha Opacity scale.
     * @param scale_x Horizontal stretch.
     * @param scale_y Vertical stretch.
     * @return The cursor after the data.
     */
    virtual void* func_00421650(void* cursor, float x, float y, u32 color, float scale, float angle, float alpha,
                                float scale_x, float scale_y) = 0;

    /**
     * @brief Return the size of the object's packet.
     * @return Size, in quadwords.
     */
    virtual s32 func_00424860() = 0;

    float axis_offset;
};

/** Partial packet builder with vtable D_1728E0 in main data and an owned buffer. */
class LibClass1728E0 : public LibClass1728C0
{
public:
    /** @brief Construct the builder without a buffer. */
    LibClass1728E0();

    /** @brief Delete the buffer and destroy the builder. */
    virtual ~LibClass1728E0();

    /**
     * @brief Write the object's GIF data at a cursor.
     * @param cursor Where to write.
     * @param x Centre x, in screen pixels.
     * @param y Centre y, in screen pixels.
     * @param color Packed RGB color the object's own color is modulated by.
     * @param scale Size scale.
     * @param angle Rotation in radians.
     * @param alpha Opacity scale.
     * @param scale_x Horizontal stretch.
     * @param scale_y Vertical stretch.
     * @return The cursor after the data.
     */
    virtual void* func_00421650(void* cursor, float x, float y, u32 color, float scale, float angle, float alpha,
                                float scale_x, float scale_y);

    /**
     * @brief Return the size of the object's packet.
     * @return Size, in quadwords.
     */
    virtual s32 func_00424860();

    float alpha;
    u32 edge_color;
    u32 centre_color;
    s32 unk1c;
    s32 unk20;
    float unk24;
    float unk28;
    float unk2c;
    float unk30;
    float unk34;
    float unk38;
    float unk3c;
    float max_length;
    LibLightRay* rays;
};

/** Partial packet builder with vtable D_172900 in main data. */
class LibClass172900 : public LibClass1728C0
{
public:
    /** @brief Start with five segments. */
    LibClass172900()
    {
        segments = 5;
    }

    virtual ~LibClass172900();

    /**
     * @brief Write the object's GIF data at a cursor.
     * @param cursor Where to write.
     * @param x Centre x, in screen pixels.
     * @param y Centre y, in screen pixels.
     * @param color Packed RGB color the object's own color is modulated by.
     * @param scale Size scale.
     * @param angle Rotation in radians.
     * @param alpha Opacity scale.
     * @param scale_x Horizontal stretch.
     * @param scale_y Vertical stretch.
     * @return The cursor after the data.
     */
    virtual void* func_00421650(void* cursor, float x, float y, u32 color, float scale, float angle, float alpha,
                                float scale_x, float scale_y);

    /**
     * @brief Return the size of the object's packet.
     * @return Size, in quadwords.
     */
    virtual s32 func_00424860();

    float alpha;
    u32 color;
    float inner_radius;
    float width;
    s32 segments;
};

/** Partial packet builder with vtable D_172920 in main data. */
class LibClass172920 : public LibClass1728C0
{
public:
    LibClass172920()
    {
    }

    virtual ~LibClass172920();

    /**
     * @brief Write the object's GIF data at a cursor.
     * @param cursor Where to write.
     * @param x Centre x, in screen pixels.
     * @param y Centre y, in screen pixels.
     * @param color Packed RGB color the object's own color is modulated by.
     * @param scale Size scale.
     * @param angle Rotation in radians.
     * @param alpha Opacity scale.
     * @param scale_x Horizontal stretch.
     * @param scale_y Vertical stretch.
     * @return The cursor after the data.
     */
    virtual void* func_00421650(void* cursor, float x, float y, u32 color, float scale, float angle, float alpha,
                                float scale_x, float scale_y);

    /**
     * @brief Return the size of the object's packet.
     * @return Size, in quadwords.
     */
    virtual s32 func_00424860();

    float alpha;
    u32 colors[5];
    float widths[5];
};

/** Partial packet builder with vtable D_172940 in main data. */
class LibClass172940 : public LibClass1728C0
{
public:
    LibClass172940()
    {
    }

    virtual ~LibClass172940();

    /**
     * @brief Write the object's GIF data at a cursor.
     * @param cursor Where to write.
     * @param x Centre x, in screen pixels.
     * @param y Centre y, in screen pixels.
     * @param color Packed RGB color the object's own color is modulated by.
     * @param scale Size scale.
     * @param angle Rotation in radians.
     * @param alpha Opacity scale.
     * @param scale_x Horizontal stretch.
     * @param scale_y Vertical stretch.
     * @return The cursor after the data.
     */
    virtual void* func_00421650(void* cursor, float x, float y, u32 color, float scale, float angle, float alpha,
                                float scale_x, float scale_y);

    /**
     * @brief Return the size of the object's packet.
     * @return Size, in quadwords.
     */
    virtual s32 func_00424860();

    float alpha;
    u32 colors[4];
    float inner_radius;
    float widths[2];
};

/**
 * Partial Lib transform with vtables D_172960 (primary), D_1729E4 (DMA submission) and D_1729F4 (list receiver) in
 * main data. Its list holds the packet builders whose packets go into its own packet.
 */
class LibClass172960 : public LibTransform, public DmaSubmission, public LibListReceiver
{
public:
    /** @brief Initialize the transform with an empty builder list and no packet. */
    LibClass172960();

    /** @brief Delete the packet, then release the object at unk240 and delete the builders if unk23d is set. */
    virtual ~LibClass172960();

    /** @brief Release the object at unk240 if unk23d is set, then queue the transform for release. */
    virtual void destroy();

    /** @brief Queue the object's DMA submission on VIF1. */
    virtual void render();

    /** @brief Draw in bucket 9. */
    virtual void set_default_draw_bucket();

    /**
     * @brief Return the bounding sphere Lib culls against.
     * @return Sphere in a local of this function: zero centre and a radius of 1e30, so the object is never culled.
     */
    virtual const LibVector4* get_bounding_sphere();

    /**
     * @brief Build the object's packet.
     * @param matrix Matrix supplied by the caller.
     * @param context Opaque caller context.
     */
    virtual void build_packet(const void* matrix, void* context);

    /**
     * @brief Send the packet on VIF1 in normal mode.
     * @param channel DMA channel; unused.
     */
    virtual void submit_dma(u32 channel);

    /**
     * @brief Finish the packet.
     * @param channel DMA channel; unused.
     */
    virtual void complete_dma(u32 channel);

    /** @brief Allocate a packet big enough for every builder in the list, plus 20 quadwords. */
    void allocate_packet();

    LibPacketBuffer* packet;
    float unk22c;
    u32 unk230;
    u32 packet_quadwords;
    u32 packet_address;
    u8 unk23c;
    u8 unk23d;
    u8 unk23e;
    u8 unk23f;
    LibClass1728A0* unk240;
};

/** Update list that is also a list object, with vtables D_173080 (primary) and D_1730B8 (list object) in main data. */
class LibClass173080 : public LibUpdateList, public LibListObject
{
public:
    virtual ~LibClass173080();

    /** @brief Update every node in the list, in order. */
    virtual void update();
};

class LibClass173070;

/** 0x40-byte link from one LibClass173070 node to another. */
struct LibClass173070Link
{
    LibVector4 unk00;
    LibVector4 unk10;
    u8 flags;
    u8 blocked;
    u8 unk22[2];
    float unk24;
    float rest_length;
    float stiffness;
    float unk30;
    float unk34;
    LibClass173070* target;
    u8 unk3c[4];

    LibClass173070Link() {}
};

#define LIB_LINK_NODE_GRAVITY 0x01
#define LIB_LINK_NODE_DAMPING 0x02
#define LIB_LINK_NODE_FORCE 0x40

/** Node with a table of links to other nodes, built in arrays by the scene loader; 0xA0 bytes, vtable D_173070. */
class LibClass173070
{
public:
    u8 fixed;
    u8 flags;
    u8 group;
    u8 unk03;
    LibTransform* transform;
    LibClass172AB0* unk08;
    LibClass173070Link* links;
    float unk10;
    s32 link_count;
    float unk18;
    u32 unk1c;
    float unk20;
    float weight;
    float damping;
    u8 unk2c[4];
    LibVector4 position;
    LibVector4 previous_position;
    LibVector4 velocity;
    LibVector4 orientation;
    u8 unk70[0x20];

    /** @brief Clear the link table and its counts. */
    LibClass173070();

    /** @brief Release the buffer's allocation. */
    virtual ~LibClass173070();

    u8 unk94[0xC];
};

/** List object with an array of LibClass173070 and two buffers, with vtable D_173050 in main data; only its destructor is known. */
class LibClass173050 : public LibListObject
{
public:
    /** @brief Start empty with the default flag byte and word, and mark the object. */
    LibClass173050()
    {
        node_count = 0;
        unk16 = 0;
        unk1a = 0;
        unk24 = 0;
        unk28 = 0;
        unk2c = 0;
        unk30 = 0;
        unk40 = 0;
        unk44 = 0;
        unk48 = 0;
        unk4c = 0;
        unk1c = D_001B6504;
        unk1b = D_001B6510;
        object_kind |= 4;
    }

    /** @brief Destroy the array and release both buffers. */
    virtual ~LibClass173050();

    /**
     * @brief Return the list kind.
     * @return Five.
     */
    virtual s32 get_default_list_kind();

    virtual void update();

    s16 node_count;
    s16 unk16;
    s16 group_count;
    u8 unk1a;
    u8 unk1b;
    u32 unk1c;
    float unk20;
    LibClass173070* unk24;
    LibClass172AB0** unk28;
    u8* unk2c;
    void* unk30;
    u8 unk34[0xC];
    u32 unk40;
    u32 unk44;
    u32 unk48;
    u32 unk4c;
};

/**
 * @brief Set the links up from the nodes' current transforms: each node starts at its transform's position at rest
 *        with its orientation copied, each link's rest length becomes the current distance, the nodes are grouped
 *        along their links, and the group buffer is reallocated for the group count.
 * @param owner Link system.
 */
extern "C" void func_00428670(LibClass173050* owner);

typedef ItemCreationClass172600 LibClass172600;
typedef LibListIndicator LibClass1725D0;
typedef ItemCreationClass172870 LibClass172870;
extern "C" {
#else
typedef struct ItemCreationClass172600 ItemCreationClass172600;
typedef struct LibListIndicator LibListIndicator;
typedef struct ItemCreationClass172870 ItemCreationClass172870;
#endif

/**
 * @brief Place a list indicator and set its scroll extent and position.
 * @param object List indicator.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param height Bar height.
 * @param extent Size of one scroll step, as a share of the bar.
 * @param position Scroll position.
 * @return One on success, or zero if its storage could not be initialized.
 */
s32 lib_list_indicator_init(LibListIndicator* object, float x, float y, float height, float extent, float position);

/**
 * @brief Allocate marker drawing storage and initialize its rectangle and colors.
 * @param object Marker widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return One on success, or zero if storage cannot be allocated.
 */
s32 lib_marker_init_rectangle(ItemCreationClass172870* object, float x, float y, float width, float height);

/**
 * @brief Set the marker color to a packed RGB color brightened by 1.8, and mark the marker for redraw.
 * @param object Marker widget.
 * @param color Packed RGB color; each channel is clamped to 255 after brightening.
 */
void func_00420D20(ItemCreationClass172870* object, u32 color);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0041A530(void* object);

/**
 * @brief Initialize the scalar indicator rectangle and storage.
 * @param object Scalar indicator widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return One on success, or zero when storage initialization fails.
 */
s32 func_0041AD10(ItemCreationClass172600* object, float x, float y, float width, float height);

/**
 * @brief Store two pointers in the receiver at offsets 0x14 and 0x18.
 * @param object Receiver to update.
 * @param first Pointer stored at offset 0x14.
 * @param second Pointer stored at offset 0x18.
 */
void func_004214C0(void* object, void* first, void* second);



/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00429850(void* object);



/**
 * @brief Zero the 16-byte output argument.
 * @param unused Unused first argument.
 * @param output Address to clear.
 */
#ifdef __cplusplus
/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_004297F0(void* object, u8 mode);


}
#endif

#ifdef __cplusplus
/** Set the output values when the input float is positive. */
extern "C" s32 func_004284A0(void* object, const void* value, float* zero_output, float* small_output);
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** Detach and release the retained objects with the supplied byte tag. */
void func_00428B90(u8 tag);

/** Detach and release the first retained set with the supplied byte tag. */
void func_004288C0(u8 tag);

/**
 * @brief Count the objects in the second retained set.
 * @return Number of occupied slots.
 */
s32 func_00428AF0(void);

/**
 * @brief Count the objects in the first retained set.
 * @return Number of occupied slots.
 */
s32 func_00428B40(void);

#ifdef __cplusplus
}
#endif

#endif
