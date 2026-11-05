#ifndef SO3_OVERLAYS_LIB_TEXT_004DD440_H
#define SO3_OVERLAYS_LIB_TEXT_004DD440_H

#include "types.h"
#include "gs.h"

typedef struct N50Owner114_004DD440 N50Owner114_004DD440;
typedef struct N50OwnerBC_004DD440 N50OwnerBC_004DD440;
#include "main/resident_0010A0E0.h"
#include "sdk/main/libdma_0012B2C8.h"

#ifdef __cplusplus
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/vector.h"

/** Transform that faces an optional target with a roll about the viewing direction. */
class LibLookAtTransform : public LibTransform
{
public:
    /** @brief Initialize the transform without a look-at target or roll. */
    LibLookAtTransform();
    /** @brief Destroy the look-at transform and its transform base. */
    virtual ~LibLookAtTransform();

    /**
     * @brief Copy the look-at target and inherited transform state.
     * @param source Transform to copy; its roll angle is not copied.
     */
    virtual void copy_look_at_state(const LibLookAtTransform* source);

    /** @brief Update the matrix to face the target when one is attached. */
    virtual void update_transform_matrix();

    /** Transform whose position supplies the viewing direction, or null. */
    LibTransform* look_at_target;

    /** Rotation about the viewing direction, passed to the sine/cosine helper. */
    float roll_angle;
};
/** Size of the area a display draws to: a base size scaled, then rounded up to GS page-friendly sizes. */
struct LibDisplayArea
{
    float scale_x;
    float scale_y;
    s16 base_width;
    s16 base_height;
    s16 width;
    s16 height;
};

/**
 * GS drawing environment for one draw buffer: a GIF tag and the context-1
 * registers in A+D form, in the order libgraph's sceGsDrawEnv1 uses.
 */
struct LibDrawEnvironment
{
    GsGifTag gif_tag;
    GsFrame frame;
    u64 frame_address;
    u64 depth_buffer;
    u64 depth_buffer_address;
    u64 offset;
    u64 offset_address;
    GsScissor scissor;
    u64 scissor_address;
    u64 unk40[6];
    GsTest test;
    u64 test_address;
    u8 unk80[0x80];
};

/** GS packet that clears a draw buffer in 32-pixel-wide strips. */
struct LibScreenClear
{
    u8 unk00[0x400];
};

/** One of the display's draw buffers: its environment and the packet that clears it. */
struct LibDisplayBuffer
{
    LibDrawEnvironment environment;
    LibScreenClear clear;
};

/** Number of draw buffers a display keeps (two alternate; the third is drawn separately). */
#define LIB_DISPLAY_BUFFER_COUNT 3

/** Number of screens a display can show (one per interlaced field per read circuit). */
#define LIB_DISPLAY_SCREEN_COUNT 4

/** One screen the display can show: its output registers, draw buffers and settings. */
struct LibDisplayScreen
{
    u8 unk00[0x10];

    /** DISPFB value for the read circuit this screen is shown on. */
    u64 framebuffer_register;

    /** DISPLAY value for the read circuit this screen is shown on. */
    u64 display_register;

    u8 unk20[0x10];
    LibDisplayBuffer buffers[2];
    u8 enabled;
    u8 unkA51;

    /** Interlaced field (0 or 1) the screen is shown in. */
    u8 field;

    u8 unkA53;

    /** Show the screen on read circuit 1. */
    u8 circuit1;

    /** Show the screen on read circuit 2. */
    u8 circuit2;

    u8 unkA56;
    u8 unkA57;
    s16 unkA58;
    s16 width;
    s16 height;
    s16 view_x;
    s16 view_y;
    s16 view_width;
    s16 view_height;
    u8 unkA66[0xA];
};

/** Partial 0x3F10-byte Lib display, with vtable D_178FB0 in main data; its data comes before the vptr. */
class LibCameraContext
{
public:
    /** @brief Initialize the display. */
    LibCameraContext();

    /**
     * @brief Build a clear packet that fills a rectangle with one colour.
     * @param clear Packet to fill.
     * @param depth_method Depth test method the packet restores afterwards.
     * @param x Left edge, in primitive coordinates.
     * @param y Top edge, in primitive coordinates.
     * @param width Width in pixels.
     * @param height Height in pixels.
     * @param red Red component.
     * @param green Green component.
     * @param blue Blue component.
     * @param alpha Alpha component.
     * @param depth Depth the cleared pixels get.
     */
    void build_clear(LibScreenClear* clear, s16 depth_method, s16 x, s16 y, s16 width, s16 height, u8 red, u8 green,
                     u8 blue, u8 alpha, u32 depth);

    /**
     * @brief Set the colour every draw buffer is cleared to.
     * @param red Red component.
     * @param green Green component.
     * @param blue Blue component.
     * @param alpha Alpha component.
     */
    void set_clear_color(u8 red, u8 green, u8 blue, u8 alpha);

    /**
     * @brief Set up the display's GIF tags and default state, size the draw area and allocate its buffers.
     * @param frame_buffer_count Frame buffers the display cycles through.
     */
    void initialize(s32 frame_buffer_count);

    /**
     * @brief Set the draw area's scale and resize it. A scaled display draws its second buffer's environment on
     *        its own.
     * @param unk3C77 Stored at 0x3C77.
     * @param scale_x Horizontal scale.
     * @param scale_y Vertical scale.
     * @param unk3C70 Stored at 0x3C70.
     */
    void set_scale(u8 unk3C77, float scale_x, float scale_y, s16 unk3C70);

private:
    /**
     * @brief Body of set_scale, which initialize also inlines.
     * @param unk3C77 Stored at 0x3C77.
     * @param scale_x Horizontal scale.
     * @param scale_y Vertical scale.
     * @param unk3C70 Stored at 0x3C70.
     */
    void apply_scale(u8 unk3C77, float scale_x, float scale_y, s16 unk3C70);

public:

    /**
     * @brief Configure one of the display's screens. Progressive output has no second read circuit, so a
     *        circuit-2 screen is left alone there.
     * @param index Screen index.
     * @param enabled Nonzero to show the screen.
     * @param unk3 Stored at 0xA53.
     * @param circuit1 Show the screen on read circuit 1.
     * @param circuit2 Show the screen on read circuit 2.
     * @param unk6 Stored at 0xA56.
     * @param field Interlaced field the screen is shown in.
     * @param unk8 Stored at 0xA58.
     * @param width Screen width in pixels.
     * @param height Screen height in pixels.
     */
    void configure_screen(s32 index, u8 enabled, u8 unk3, u8 circuit1, u8 circuit2, u8 unk6, u8 field, s16 unk8,
                          s16 width, s16 height);

    /**
     * @brief Set the rectangle of a screen that is drawn to.
     * @param index Screen index.
     * @param x Left edge.
     * @param y Top edge.
     * @param width Width in pixels.
     * @param height Height in pixels.
     */
    void set_screen_view(s32 index, s32 x, s32 y, s32 width, s32 height);

    u8 unk00[0x10];

    /** DISPFB value used when a screen doesn't supply its own. */
    u64 framebuffer_register;

    /** DISPLAY value used when a screen doesn't supply its own. */
    u64 display_register;

    u8 unk20[0x130];
    LibDisplayBuffer buffers[LIB_DISPLAY_BUFFER_COUNT];
    LibDrawEnvironment environments[2];
    LibDisplayScreen screens[LIB_DISPLAY_SCREEN_COUNT];
    LibDisplayArea display_area;
    s16 unk3C70;
    u8 unk3C72[4];

    /** The draw area isn't drawn at 1:1. */
    u8 scaled;

    u8 unk3C77;
    /** First VRAM page (8 KB) after the display's buffers; textures go from here. */
    u32 vram_free_page;
    u32 unk3C7C;
    u8 unk3C80[0x34];
    u8* unk3CB4[18];
    u8* unk3CFC[18];
    u8 unk3D44[0x108];
    u32 unk3E4C;
    u32 unk3E50;
    u32 unk3E54;
    u32 unk3E58;
    /** Frame buffers the display cycles through. */
    s32 frame_buffer_count;
    u8 unk3E60[4];
    u8 unk3E64;
    u8 unk3E65;
    u8 unk3E66;
    u8 unk3E67;
    u8 unk3E68;
    u8 unk3E69;
    u8 unk3E6A[2];

    /** Enable alpha blending in the display drawing commands. */
    u8 blend_enabled;

    /** Which of the two alternating draw buffers is in use. */
    u8 current_buffer;

    u8 unk3E6E[2];

    /** Alpha multiplied by 128 when building display drawing commands. */
    float blend_alpha;

    /** Packed RGBA the draw buffers are cleared to. */
    u32 clear_color;

    s16 unk3E78;
    s16 unk3E7A;
    u8 unk3E7C[0x90];

    /** @brief Destroy the display. */
    virtual ~LibCameraContext();
};

/** The game's display. */
extern LibCameraContext* D_001B6650;

/** Scene and model-preview camera, with its submission callback interface at 0x220. */
class LibClass179080 : public LibLookAtTransform, public DmaSubmission
{
public:
    /** @brief Initialize the camera from the resident context. @param context Resident context. */
    LibClass179080(void* context);
    /** @brief Release camera resources and its transform base. */
    virtual ~LibClass179080();
    /** @brief Clear the manager camera reference, then detach and queue the transform. */
    virtual void destroy();
    /** @brief Initialize viewport bounds and default projection settings. @param context Resident viewport context. */
    void initialize_projection(const LibCameraContext* context);
    /** @brief Build the local perspective volume for visibility tests. @param volume Destination volume. */
    void build_projection_volume(LibProjectionVolume* volume) const;
    /** @brief Upload the camera's clip geometry into VU0 data memory. */
    void upload_clip_geometry() const;
    /** @brief Update the transform and extract its rotation components. */
    virtual void update_transform_matrix();
    /** @brief Update camera state and its attached-transform distance. */
    virtual void update();
    /** @brief Update the active camera projection state. */
    void func_004E24D0();
    /** @brief Submit the camera's DMA chain. @param channel DMA channel number. */
    virtual void submit_dma(u32 channel);
    /** @brief Complete the camera transfer. @param channel DMA channel number. */
    virtual void complete_dma(u32 channel);
    /** @brief Queue the camera for VIF1 DMA. @return 1 on success, 0 when the queue is full. */
    s32 enqueue_submission();
    /** @brief Copy view and projection state from another camera. @param source Camera source. */
    virtual void copy_camera(const LibClass179080* source);
    /** @brief Copy the camera's view and fog settings. @param source Camera to copy. */
    void copy_view_and_fog(const LibClass179080* source);
    /**
     * @brief Read the configured far and near fog factors.
     * @param far_factor Receives the far fog factor.
     * @param near_factor Receives the near fog factor.
     */
    void get_fog_factors(float* far_factor, float* near_factor) const;
    /**
     * @brief Set the perspective fog mapping coefficients directly.
     * @param offset Constant fog coefficient.
     * @param reciprocal_scale Reciprocal-distance fog coefficient.
     */
    void set_fog_coefficients(float offset, float reciprocal_scale);
    /**
     * @brief Read the perspective fog mapping coefficients.
     * @param offset Receives the constant fog coefficient.
     * @param reciprocal_scale Receives the reciprocal-distance fog coefficient.
     */
    void get_fog_coefficients(float* offset, float* reciprocal_scale) const;
    /** @brief Set the near fog-distance fraction and recompute fog coefficients. @param fraction Fraction of the configured distance range. */
    void set_near_fog_fraction(float fraction);
    /** @brief Set the far fog-distance fraction and recompute fog coefficients. @param fraction Fraction of the configured distance range. */
    void set_far_fog_fraction(float fraction);
    /**
     * @brief Set the fog color, factors and distance range, then recompute the perspective coefficients.
     * @param color Packed RGB fog color.
     * @param far_factor Fog factor at the far distance.
     * @param near_factor Fog factor at the near distance.
     * @param near_distance Near fog distance.
     * @param far_distance Far fog distance.
     */
    void set_fog(u32 color, float far_factor, float near_factor, float near_distance, float far_distance);
    /**
     * @brief Calculate the scaled screen-plane distance from the horizontal field of view.
     * @return Perspective projection distance.
     */
    float compute_projection_distance() const;
private:
    /** @brief Recompute the perspective fog mapping. @param far_factor Far fog factor. @param near_factor Near fog factor. */
    void update_fog_coefficients(float far_factor, float near_factor)
    {
        float distance_span = far_fog_distance - near_fog_distance;
        lib_compute_perspective_fog_coefficients(&fog_offset, &fog_reciprocal_scale, far_factor, near_factor,
                                               near_fog_distance + near_fog_fraction * distance_span,
                                               near_fog_distance + far_fog_fraction * distance_span);
    }
public:
    u8 unk224[0xC];
    DmaSourceTag dma_chain;
    float unk240;
    float unk244;
    u32 unk248;
    float unk24c;
    float unk250;
    float unk254;
    u32 unk258;
    float horizontal_fov;
    float unk260;
    float unk264;
    float unk268;
    float unk26c;
    float unk270;
    float projection_distance;
    float unk278;
    u32 unk27c;
    float unk280;
    float unk284;
    u8 unk288[8];
    FieldVec4B screen_min;
    FieldVec4B screen_max;
    u8 unk2b0[0x118];
    u32 unk3c8;
    u32 unk3cc;
    u8 unk3d0;
    u8 unk3d1;
    u8 unk3d2;
    u8 unk3d3;
    u32 unk3d4;
    u8 unk3d8[0x18];
    FieldVec4A clip_points[10];
    FieldVec4A clip_normals[10];
    u32 fog_color;
    u8 fog_enabled;
    u8 unk535[3];
    float fog_offset;
    float fog_reciprocal_scale;
    float far_fog_fraction;
    float near_fog_fraction;
    float far_fog_distance;
    float near_fog_distance;
    float near_fog_factor;
    float far_fog_factor;
    u8 unk558[8];
    float rotation_angles[3];
    u8 unk56c[0x314];
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** Resident VIF1 DMA queue initialized by the Lib runtime. */
extern ResidentDmaQueue* g_vif1_dma_queue;

struct FieldPacketQueue;

/**
 * @brief Process the render iteration and submit its queued packets.
 * @param object Display state.
 * @param frame Render iteration.
 * @param queue Packet queue to process.
 */
void func_4DD830(void* object, s32 frame, struct FieldPacketQueue* queue);


void func_004E59A0(void* object);
void func_004E5B00(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_004E2E30(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_004E2EF0(void* object);

/**
 * @brief Return the fixed value 16.
 * @param object Receiver or first argument; unused.
 * @return Always 16.
 */
s32 func_004E44E0(void* object);

/** @brief Toggle bit zero of the word at receiver offset 0x14. @param object Receiver containing the word. */
void func_004E44F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_004E6420(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_004E6430(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_004E6440(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_004E6450(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_004E6BB0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_004E6BF0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_004E6C30(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_004E6C70(void* object);

/**
 * @brief Return the fixed value 8.
 * @param object Receiver or first argument; unused.
 * @return Always 8.
 */
s32 func_004E7820(void* object);


/** Return the word at receiver offset 0x4. */
u32 func_004E6680(const void* object);

/** Return the word at receiver offset 0x4. */
u32 func_004E6A80(const void* object);


/** Return the signed halfword at receiver offset 0x48. */
s16 func_004E6400(const void* object);

/** Return the signed halfword at receiver offset 0x4A. */
s16 func_004E6410(const void* object);

/** Return the signed halfword at receiver offset 0x28. */
s16 func_004E6860(const void* object);

/** Return the signed halfword at receiver offset 0x2A. */
s16 func_004E6870(const void* object);


/** Store the byte constant at receiver offset 0x60. */
void func_004E2EE0(void* object);

/** Hide the equipment menu's factor tooltip by clearing its visible byte at 0xCB. */
void lib_factor_tooltip_hide(void* object);

/** Clear the word at receiver offset 0x114. */
void func_004E13D0(void* object);

/** Return the address of the global at 0x50CD80. */
const void* func_004E0FB0(void);

/** Set the active flag and forward the optional child pointer. */
void func_004E1040(N50Owner114_004DD440* object);
/** Set the active flag and forward the optional child pointer. */
void func_004E2F20(N50OwnerBC_004DD440* object);

#ifdef __cplusplus
/** Return the first pointer argument unchanged. */
void* func_004E6D30(void* value);
/** Return the first pointer argument unchanged. */
void* func_004E6DF0(void* value);

/** Clear four consecutive words at the start of the receiver. */
void func_004E64B0(void* object);

/** Clear four consecutive words at the start of the receiver. */
void func_004E68D0(void* object);

/** Forward the receiver to func_004D00B0. */
void func_004E2F00(void* object);

/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_004E6340(void* object, u8 mode);

/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_004E67A0(void* object, u8 mode);


/** Set the high packed mode at its target field and record whether either mode equals four. */
void func_004E63A0(void* object, u8 mode);

/** Set the high packed mode at its target field and record whether either mode equals four. */
void func_004E6800(void* object, u8 mode);


/** Find a key in the receiver's fixed-size entry array. */
s32 func_004E6460(void* object, float key);

/** Return the key span between the first and last entries. */
float func_004E68F0(void* object);

/** Find a key in the receiver's fixed-size entry array. */
s32 func_004E6880(void* object, float key);

/**
 * @brief Clear the byte at offset 0x64 and run the cleanup helper.
 * @param object Object containing the byte.
 */
void func_004E1020(void* object);

void* func_004E4590(void* object);
void* func_004E4650(void* object);
void* func_004E4710(void* object);
void* func_004E47D0(void* object);
void* func_004E4890(void* object);
void* func_004E4950(void* object);
void* func_004E4A10(void* object);
void* func_004E4AD0(void* object);


}
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** Release the retained display objects and storage. */
void func_004E33B0(void);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/** Transform owner with an intrusive list and DMA notification interface. */
class LibClass178FC0 : public LibClass172000, public LibUpdateList, public LibDmaCallbacks
{
public:
    LibClass178FC0();

    virtual ~LibClass178FC0();

    virtual void update();

    virtual void render();

    virtual const LibVector4* get_bounding_sphere();

    virtual void build_packet(const void* matrix, void* context);

    virtual void on_packet_complete(u32 value);

    void func_004E13D0();

    s32 func_004E10B0(s32 size);

    u8 unk10c[8];
    void* unk114;
};
#endif

#endif
