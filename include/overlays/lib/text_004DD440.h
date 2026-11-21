#ifndef SO3_OVERLAYS_LIB_TEXT_004DD440_H
#define SO3_OVERLAYS_LIB_TEXT_004DD440_H

#include "types.h"
#include "gs.h"

#include "main/dma_queue.h"
#include "main/system.h"
#include "main/utility.h"
#include "sdk/main/libdma_0012B2C8.h"

#ifdef __cplusplus
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/vector.h"

/**
 * Area a display draws to (a base size scaled, then rounded up to GS page-friendly sizes) and the formats its draw
 * buffers use.
 */
struct LibDisplayArea
{
    float scale_x;
    float scale_y;
    s16 base_width;
    s16 base_height;
    s16 width;
    s16 height;
    s16 unk10;
    s16 depth_test;
    s16 depth_format;
    u8 scaled;
    u8 unk17;
};

/** GS drawing environment for one draw buffer: a GIF tag and both contexts' registers in A+D form. */
struct LibDrawEnvironment
{
    GsGifTag gif_tag;
    GsDrawContext context1;
    GsDrawContext context2;
};

#define LIB_SCREEN_CLEAR_STRIP_COUNT 30

/** GS packet that clears a draw buffer in 32-pixel-wide strips. */
struct LibScreenClear
{
    GsRegisterValue test;
    GsRegisterValue prim;
    GsRegisterValue color;
    GsRegisterValue vertices[LIB_SCREEN_CLEAR_STRIP_COUNT * 2];
    GsRegisterValue restore_test;
};

/** One of the display's draw buffers: its environment and the packet that clears it. */
struct LibDisplayBuffer
{
    LibDrawEnvironment environment;
    LibScreenClear clear;
};

/** DISPFB and DISPLAY values for one read circuit. */
struct LibDisplayRegisters
{
    u64 framebuffer;
    u64 display;
};

#define LIB_DISPLAY_BUFFER_COUNT 3
#define LIB_DISPLAY_PACKET_COUNT 18
#define LIB_DISPLAY_PACKET_SET_COUNT 2

/** Number of packet lists a display keeps: one per field in each set. */
#define LIB_DISPLAY_PACKET_LIST_COUNT (LIB_DISPLAY_PACKET_SET_COUNT * 2)

#define LIB_DISPLAY_SCREEN_COUNT 4

/** One screen the display can show: its output registers, draw buffers and settings. */
struct LibDisplayScreen
{
    GsDisplayEnvironment display_environment;
    u8 unk28[8];
    LibDisplayBuffer buffers[2];
    u8 enabled;
    u8 unkA51;
    u8 field;
    u8 unkA53;
    u8 circuit1;
    u8 circuit2;
    u8 unkA56;
    u8 unkA57;
    s16 pixel_format;
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
     * @brief Build a clear packet like build_clear, for the second drawing context (TEST_2, PRIM context bit).
     * @param clear Packet to fill.
     * @param depth_method Depth test restored after the clear; 0 leaves depth testing off.
     * @param x Left edge in GS coordinates.
     * @param y Top edge in GS coordinates.
     * @param width Width in pixels.
     * @param height Height in pixels.
     * @param red Red component.
     * @param green Green component.
     * @param blue Blue component.
     * @param alpha Alpha component.
     * @param depth Depth the cleared pixels get.
     */
    void func_004DB600(LibScreenClear* clear, s16 depth_method, s16 x, s16 y, s16 width, s16 height, u8 red, u8 green,
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

    /** @brief Size the draw area from its base size and scale, rounded up to 64 by 32 pixels. */
    void resize_display_area()
    {
        s32 fields;

        fields = 1;

        if (resident_get_system()->progressive)
        {
            fields = 2;
        }

        display_area.width = ((s32)(display_area.base_width * display_area.scale_x) + 63) & ~63;
        display_area.height = ((s32)(display_area.base_height * display_area.scale_y / fields) + 31) & ~31;
    }

public:
    /**
     * @brief Set up the display environments for a frame size. The three frame buffers follow the depth buffer;
     *        each gets circuit-1 registers and a copy that blends both circuits.
     * @param pixel_format Frame buffer pixel format.
     * @param width Frame width in pixels.
     * @param height Frame height in pixels.
     */
    void configure_display(s16 pixel_format, s16 width, s16 height);

    /**
     * @brief Set up the draw buffers for a frame size and lay out VRAM: the depth buffer at vram_base_page, then
     *        the frame buffers. A scaled display also places the draw area and each enabled screen's buffers after
     *        them.
     * @param pixel_format Frame buffer pixel format.
     * @param width Frame width in pixels.
     * @param height Frame height in pixels (one field when interlaced).
     * @param depth_test Depth test method; 0 for no depth buffer.
     * @param depth_format Depth buffer pixel format.
     */
    void configure_buffers(s16 pixel_format, s16 width, s16 height, s16 depth_test, s16 depth_format);

    /**
     * @brief Show the field that's starting: point the read circuits at the screens drawn for it and, when the
     *        display is scaled and no screen is on circuit 2, send the packets that draw the scaled area.
     * @param field Interlaced field (0 or 1) from GS CSR.
     */
    void vblank(s32 field);

    /**
     * @brief Finish a render iteration: send its draw packets to the queue and pick the buffers to show.
     * @param frame Render iteration.
     * @param queue Packet queue the frame's packets go to.
     */
    void flip(s32 frame, LibPacketQueue* queue);

    /**
     * @brief Send one field's packet list from send_list_set. Entries flagged in unk3E08 are drawn with
     *        environments[0]; the draw environment is put back when the flagged run ends.
     * @param field Interlaced field whose list is sent.
     * @param per_screen Put back the environments of the field's circuit-2 screens instead of buffers[1]'s.
     */
    void send_packet_list(s32 field, bool per_screen);

    /** @brief Send the ready packet, once, if there is one and a packet queue to send it to. */
    void send_ready_packet();

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
     * @param pixel_format Pixel format of the screen's buffers.
     * @param width Screen width in pixels.
     * @param height Screen height in pixels.
     */
    void configure_screen(s32 index, u8 enabled, u8 unk3, u8 circuit1, u8 circuit2, u8 unk6, u8 field,
                          s16 pixel_format, s16 width, s16 height);

    /**
     * @brief Set the rectangle of a screen that is drawn to.
     * @param index Screen index.
     * @param x Left edge.
     * @param y Top edge.
     * @param width Width in pixels.
     * @param height Height in pixels.
     */
    void set_screen_view(s32 index, s32 x, s32 y, s32 width, s32 height);

    /**
     * @brief Turn the display output on or off. Circuit 1 only comes on when the display allows it (0x3E64).
     * @param enabled Show read circuit 2.
     * @param circuit1 Also show read circuit 1.
     */
    void set_output(bool enabled, bool circuit1);

    /** @brief Rebuild the scaled display's packets, if it's scaled and has a draw area. */
    void refresh_scaled_packets();

    /** @brief Build the packets that draw the scaled draw area onto each screen. */
    void build_scaled_packets();

    /**
     * @brief Get the scale from screen pixels to the draw area. Interlaced output draws one field, so it counts y
     *        in field lines.
     * @param x Receives the horizontal scale.
     * @param y Receives the vertical scale.
     */
    void get_area_scale(float* x, float* y);

    /**
     * @brief Set the depth one level of the first effect is drawn at.
     * @param index Effect level.
     * @param depth Screen depth.
     */
    void set_effect_first_depth(s32 index, s32 depth)
    {
        effect_first_depths[index] = depth;
    }

    /**
     * @brief Set the depth one level of the second effect is drawn at.
     * @param index Effect level.
     * @param depth Screen depth.
     */
    void set_effect_second_depth(s32 index, s32 depth)
    {
        effect_second_depths[index] = depth;
    }

    /**
     * @brief Wait for the next field and set the draw buffers' half-pixel offsets for it.
     * @param frame Render iteration, which picks the draw buffer.
     * @return Field the frame is drawn for (always 0 for progressive output).
     */
    u32 wait_for_field(s32 frame);

    GsDisplayEnvironment display_environments[LIB_DISPLAY_BUFFER_COUNT];
    LibDisplayRegisters circuit1_registers[LIB_DISPLAY_BUFFER_COUNT];
    GsDisplayEnvironment blend_environments[LIB_DISPLAY_BUFFER_COUNT];
    LibDisplayRegisters blend_registers[LIB_DISPLAY_BUFFER_COUNT];
    LibDisplayBuffer buffers[LIB_DISPLAY_BUFFER_COUNT];
    LibDrawEnvironment environments[2];
    LibDisplayScreen screens[LIB_DISPLAY_SCREEN_COUNT];
    LibDisplayArea display_area;
    u32 vram_free_page;
    u32 vram_base_page;
    u32 depth_buffer_pages;
    LibPacketQueue* packet_queue;
    u8* effect_buffers[2];
    u32 unk3C90[2];
    u8* ready_packets[2];
    u32 ready_sizes[2];
    u8* unk3CA8[2];
    u8 unk3CB0;
    u8 ready_index;
    u8 unk3CB2[2];
    u8* packets[LIB_DISPLAY_PACKET_SET_COUNT][LIB_DISPLAY_PACKET_COUNT];
    u32 packet_sizes[LIB_DISPLAY_PACKET_SET_COUNT][LIB_DISPLAY_PACKET_COUNT];
    s32 packet_set;
    u8* list_buffers[LIB_DISPLAY_PACKET_LIST_COUNT];
    u8** list_packets[LIB_DISPLAY_PACKET_LIST_COUNT];
    u32* list_sizes[LIB_DISPLAY_PACKET_LIST_COUNT];
    u8* unk3E08[LIB_DISPLAY_PACKET_SET_COUNT];
    s32 unk3E10;
    s32 unk3E14;
    s32 unk3E18;
    u8 unk3E1C[4];
    u8* unk3E20;
    u8* unk3E24;
    s32 send_list_set;
    s32 send_list_count;
    u8 unk3E30;
    u8 unk3E31[3];
    u8* unk3E34;
    u64* unk3E38;
    u32 unk3E3C;
    s32 unk3E40;
    u32 unk3E44;
    u8 unk3E48;
    u8 unk3E49[3];
    u32 unk3E4C;
    u32 unk3E50;
    u32 shown_buffers[2];
    s32 frame_buffer_count;
    u32 blend_field_alpha;
    u8 unk3E64;
    u8 unk3E65;
    u8 unk3E66;
    u8 unk3E67;
    u8 unk3E68;
    u8 unk3E69;
    u8 unk3E6A;
    u8 unk3E6B;
    u8 blend_enabled;
    u8 current_buffer;
    u8 unk3E6E[2];
    float blend_alpha;
    u32 clear_color;
    s16 unk3E78;
    s16 unk3E7A;
    u8 effect_enabled;
    u8 effect_first_flag;
    u8 effect_second_flag;
    s8 effect_level;
    float effect_first_scale;
    float effect_second_scale;
    u32 effect_mask;
    u32 effect_first_depths[16];
    u32 effect_second_depths[16];

    /** @brief Destroy the display. */
    virtual ~LibCameraContext();
};

/** Rectangle in screen pixels. Lib's colour fades cover it. */
struct LibScreenRect
{
    /** @brief Clear the rectangle. */
    inline LibScreenRect();

    s32 x;
    s32 y;
    s32 width;
    s32 height;
};

/** Area new colour fades cover. */
extern LibScreenRect D_0050CD40;

/** Depth new colour fades draw at. */
extern "C" s32 D_001B6694;

/**
 * @brief Set the area and depth that new colour fades use.
 * @param rect Area in screen pixels.
 * @param depth Depth the fades draw at.
 */
extern "C" void lib_set_color_fade_area(const LibScreenRect* rect, s32 depth);

/**
 * @brief Set up the display's effect with the scales its level picked.
 * @param display Display.
 * @param enabled Turn the effect on.
 * @param first_flag Effect flag.
 * @param second_flag Effect flag.
 * @param level Effect level.
 * @param mask Effect mask.
 * @param first_scale First scale.
 * @param second_scale Second scale.
 */
extern "C" void func_004DCDE0(LibCameraContext* display, bool enabled, bool first_flag, bool second_flag, s32 level,
                              u32 mask, float first_scale, float second_scale);

/**
 * @brief Apply the display's effect once it's been set up.
 * @param display Display.
 */
extern "C" void func_004DE500(LibCameraContext* display);

/**
 * @brief Build the projection and clip matrices for a screen grown by a step, keeping its aspect, and write the
 * camera's projection and clip matrices into its uncached step packet.
 * @param camera Camera.
 * @param step Pixels added to the screen width.
 * @param projection Receives the stepped projection matrix, converted by func_004CECD0.
 * @param clip Receives the stepped clip matrix, converted by func_004CECD0.
 */
extern "C" void func_004E22B0(class LibCamera* camera, s32 step, LibMatrix44Value* projection, LibMatrix44Value* clip);

/**
 * @brief Build a packet that draws a rectangle into one of the display's buffers.
 * @param display Display.
 * @param packet Packet to fill.
 * @param field Interlaced field the packet draws.
 * @param frame_base Frame buffer page.
 * @param pixel_format Frame buffer pixel format.
 * @param width Width drawn.
 * @param height Height drawn.
 * @param base_width Width of the buffer drawn from.
 * @param base_height Height of the buffer drawn from.
 * @param depth_mask Mask for the depth buffer's pixel format.
 * @param blend Blend the packet with the alpha.
 * @param alpha Blend alpha, 0x80 for one.
 * @param unk12 Unknown.
 * @param unk13 Unknown.
 * @param unk14 Unknown.
 * @param unk15 Unknown.
 * @param x Rectangle left edge.
 * @param y Rectangle top edge.
 * @param rect_width Rectangle width.
 * @param rect_height Rectangle height.
 * @return Packet size.
 */
extern "C" u32 func_004DEA70(LibCameraContext* display, u8* packet, u8 field, u32 frame_base, s16 pixel_format, s16 width,
                             s16 height, s16 base_width, s16 base_height, u32 depth_mask, u8 blend, s32 alpha,
                             s32 unk12, s32 unk13, s32 unk14, u8 unk15, s32 x, s32 y, s32 rect_width, s32 rect_height);

/** GS ALPHA register values; the first is the usual (Cs - Cd) * As + Cd blend. */
extern "C" u64 D_004ED330[];

/** Rectangle of one colour that blends from a start colour to an end colour, then destroys itself (vtable D_179150). */
class LibColorFade : public LibTransformOwner, public LibDmaCallbacks
{
public:
    /** @brief Fade from black (alpha 128) to transparent over 30 frames. */
    LibColorFade()
    {
        reset();
        start_color = 0x80000000;
        color = 0x80000000;
        end_color = 0;
        duration = 30.0f;
        set_type_id(0x300);
        unk65 = 1;
        set_draw_flags(LIB_DRAW_FLAG_0400);
    }

    /** @brief Release the packet. */
    virtual ~LibColorFade();

    /**
     * @brief Return the list a colour fade goes in.
     * @return List kind 3.
     */
    virtual s32 get_default_list_kind();

    /** @brief Blend the colour for the time so far; once the fade is over, destroy it. */
    virtual void update();

    /** @brief Mark the fade pending and submit its packet. */
    virtual void render();

    /** @brief Draw in bucket 10. */
    virtual void set_default_draw_bucket();

    /**
     * @brief Build the packet: one sprite over the rectangle, scaled to the display.
     * @param matrix Matrix supplied by the caller; unused.
     * @param context Opaque caller context; unused.
     */
    virtual void build_packet(const void* matrix, void* context);

    /**
     * @brief Finish the fade's drawing packet.
     * @param value Notification word.
     */
    virtual void on_packet_complete(u32 value);

    /** @brief Clear the colour and time, take the default area and depth, and allocate the packet. */
    void reset();

    u32 start_color;
    u32 end_color;
    u32 color;
    float elapsed;
    float duration;
    LibScreenRect rect;
    s32 depth;
    LibPacketBuffer* packet;
};

/** Partial 0x28-byte screen text printer g_screen_text (vtable D_178E90); its data comes before the vptr. */
class LibScreenText
{
public:
    /**
     * @brief Set the default colours and cell size for the display's scale, put the cursor at a screen position
     *        and start the text packet with the font's drawing state.
     * @param x Left margin in screen pixels.
     * @param y Top line in screen pixels.
     */
    void begin(u16 x, u16 y);

    /**
     * @brief Load and decode the font unless one is attached, upload it to its VRAM slot and restart the text at
     *        the top-left corner.
     */
    void load_font();

    s16 left;
    s16 cursor_y;
    s16 cursor_x;
    s16 cell_width;
    s16 cell_height;
    u8 unk0a[2];
    u32 depth;
    u32 color;
    u32 shadow_color;
    u8 unk18;
    u8 shared_font;
    u8 unk1a[2];
    u8* font_image;
    LibPacketBuffer* packet;

    /** @brief Destroy the printer. */
    virtual ~LibScreenText();
};

/**
 * @brief Rebuild Lib's frame packet, which resets the context-2 drawing state, and send it.
 */
extern "C" void lib_begin_frame_packet(void);

/** A packet sent on VIF1 through the VIF1 DMA queue, with vtable D_179130 in main data. */
class LibClass179130 : public DmaSubmission
{
public:
    /**
     * @brief Send the packet on VIF1 in normal mode.
     * @param channel DMA channel; unused.
     */
    virtual void submit_dma(u32 channel);

    /**
     * @brief Do nothing when the transfer ends.
     * @param channel DMA channel; unused.
     */
    virtual void complete_dma(u32 channel);

    /** @brief Delete the packet. */
    virtual ~LibClass179130();

    LibPacketBuffer* packet;
    u32 qwc;
};

#define LIB_CAMERA_MODE_FACE_CURRENT_CAMERA 1

/** Part of a camera's uncached packet that func_004E22B0 fills: the projection and the clip matrix. */
struct LibCameraStepPacket
{
    u8 unk00[0x10];
    LibMatrix44Value projection;
    u8 unk50[0x10];
    LibMatrix44Value clip;
    u8 unka0[0x40];
};

/**
 * VU packet the camera keeps at 0x5C0 and writes through the uncached segment: its matrices and screen terms. The
 * word at 0x120 is what LibClass178FC0 writes to register 0x4F.
 */
struct LibCameraPacket5C0
{
    u8 unk000[0x10];
    LibMatrix44Value view;
    LibMatrix44Value projection;
    LibMatrix44Value unk090;
    float distance;
    float scaled_distance;
    u8 unk0d8[4];
    float centre_depth;
    LibMatrix44Value unk0e0;
    u32 unk120;
    u8 unk124[0x30];
    float roll;
    float fog_offset;
    float fog_scale;
    u8 unk160[0x60];
    LibCameraStepPacket step;
};

/** Scene and model-preview camera, with its submission callback interface at 0x220. */
class LibCamera : public LibLookAtTransform, public DmaSubmission
{
public:
    /**
     * @brief Initialize the camera from the resident context.
     * @param context Resident context.
     */
    LibCamera(void* context);

    /** @brief Release camera resources and its transform base. */
    virtual ~LibCamera();

    /** @brief Clear the manager camera reference, then detach and queue the transform. */
    virtual void destroy();

    /**
     * @brief Initialize viewport bounds and default projection settings.
     * @param context Resident viewport context.
     */
    void initialize_projection(const LibCameraContext* context);

    /**
     * @brief Build the local perspective volume for visibility tests.
     * @param volume Destination volume.
     */
    void build_projection_volume(LibProjectionVolume* volume) const;

    /** @brief Upload the camera's clip geometry into VU0 data memory. */
    void upload_clip_geometry() const;

    /** @brief Update the transform and extract its rotation components. */
    virtual void update_transform_matrix();

    /** @brief Update camera state and its attached-transform distance. */
    virtual void update();

    /** @brief Rebuild the view and projection matrices and upload the projection to VU0. */
    void update_projection();

    /**
     * @brief Submit the camera's DMA chain.
     * @param channel DMA channel number.
     */
    virtual void submit_dma(u32 channel);

    /**
     * @brief Complete the camera transfer.
     * @param channel DMA channel number.
     */
    virtual void complete_dma(u32 channel);

    /**
     * @brief Queue the camera for VIF1 DMA.
     * @return 1 on success, 0 when the queue is full.
     */
    s32 enqueue_submission();

    /** @brief Store unk530 in the packet at unk558 and queue the packet at unk860 for VIF1 DMA. */
    void func_004E1E70();

    /** @brief Write the camera's matrices into its uncached packet. */
    void func_004E2120();

    /**
     * @brief Copy view and projection state from another camera.
     * @param source Camera source.
     */
    virtual void copy_camera(const LibCamera* source);

    /**
     * @brief Copy the camera's view and fog settings.
     * @param source Camera to copy.
     */
    void copy_view_and_fog(const LibCamera* source);

    /**
     * @brief Set the screen centre in GS coordinates.
     * @param x Centre x.
     * @param y Centre y.
     */
    void set_centre(float x, float y)
    {
        centre_x = x;
        centre_y = y;
    }

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

    /**
     * @brief Set the near fog-distance fraction and recompute fog coefficients.
     * @param fraction Fraction of the configured distance range.
     */
    void set_near_fog_fraction(float fraction);

    /**
     * @brief Set the far fog-distance fraction and recompute fog coefficients.
     * @param fraction Fraction of the configured distance range.
     */
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
    /**
     * @brief Recompute the perspective fog mapping.
     * @param far_factor Far fog factor.
     * @param near_factor Near fog factor.
     */
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
    float width_scale;
    float unk254;
    u32 unk258;
    float horizontal_fov;
    float unk260;
    float unk264;
    float unk268;
    float unk26c;
    float unk270;
    float projection_distance;
    float pixel_aspect;
    float roll;
    float centre_x;
    float centre_y;
    u8 unk288[8];
    FieldVec4B screen_min;
    FieldVec4B screen_max;
    u8 unk2b0[0x10];
    LibMatrix44Value view_matrix;
    LibMatrix44Value projection_matrix;
    LibMatrix44Value unk340;
    LibMatrix44Value unk380;
    u32 test;
    float centre_depth;
    s32 unk3c8;
    s32 unk3cc;
    u8 mode;
    u8 unk3d1;
    u8 unk3d2;
    u8 unk3d3;
    LibTransform* anchor;
    u8 unk3d8[8];
    float unk3e0;
    float unk3e4;
    u8 unk3e8[8];
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
    u8* unk558;
    u8 unk55c[4];
    float rotation_angles[3];
    u8 unk56c[0x54];
    LibCameraPacket5C0 unk5c0;
    LibClass179130* unk860;
    u8 unk864[0x1C];
};

/**
 * @brief Hand the camera's view-projection matrix to the VU0 microprogram at 0x1F0.
 * @param camera Camera whose matrices are used.
 */
extern "C" void lib_load_camera_screen_matrix(const LibCamera* camera);

/**
 * @brief Load the camera's transform into VU0 (microprogram 0x1F0) and build its screen clip data.
 * @param camera Camera to upload.
 */
extern "C" void func_004E1670(LibCamera* camera);

class LibLightList;

/**
 * @brief Light step run before the renderer tests its models: refresh the list's light matrices and sort its lights.
 * @param list Light list.
 */
extern "C" void func_004E9290(LibLightList* list);
#endif

#ifdef __cplusplus
extern "C" {
#endif

void func_004E59A0(void* object);

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

/** Return the word at receiver offset 0x4. */
u32 func_004E6680(const void* object);

/** Return the signed halfword at receiver offset 0x48. */
s16 func_004E6400(const void* object);

/** Return the signed halfword at receiver offset 0x4A. */
s16 func_004E6410(const void* object);

/** Hide the equipment menu's factor tooltip by clearing its visible byte at 0xCB. */
void lib_factor_tooltip_hide(void* object);

#ifdef __cplusplus
/** Return the first pointer argument unchanged. */
void* func_004E6DF0(void* value);

/** Clear four consecutive words at the start of the receiver. */
void func_004E64B0(void* object);

/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_004E6340(void* object, u8 mode);

/** Set the high packed mode at its target field and record whether either mode equals four. */
void func_004E63A0(void* object, u8 mode);

/** Find a key in the receiver's fixed-size entry array. */
s32 func_004E6460(void* object, float key);

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

/**
 * @brief Create Lib's global objects, link them into the update lists and set up the scene camera.
 * @param display Display Lib draws to.
 * @param depth_far Integer depth at the scene camera's far plane.
 * @param texture_cache_size Texture cache size in bytes.
 * @param texture_cache_blocks Texture cache block count.
 * @param node_count Node pointers the temporary node buffer holds.
 * @param first First extra renderer argument; with second, both nonzero turn the extra renderer state on.
 * @param second Second extra renderer argument.
 */
void lib_initialize(LibCameraContext* display, s32 depth_far, s32 texture_cache_size, s32 texture_cache_blocks, s32 node_count,
                    s32 first, s32 second);

/** @brief Destroy Lib's global objects, free their storage and clear the pointers. */
void lib_shutdown(void);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/** Transform owner with an intrusive list and DMA notification interface. */
class LibClass178FC0 : public LibClass172000, public LibUpdateList, public LibDmaCallbacks
{
public:
    /** @brief Start with type ID 0x200 and no packet buffer. */
    LibClass178FC0();

    /** @brief Delete the packet buffer. */
    virtual ~LibClass178FC0();

    /** @brief Update the listed nodes. */
    virtual void update();

    /** @brief Mark the packet in flight and submit the packet buffer, notifying this object when it's sent. */
    virtual void render();

    /**
     * @brief Return the shared bounding sphere every object of this class uses.
     * @return Bounding sphere.
     */
    virtual const LibVector4* get_bounding_sphere();

    virtual void build_packet(const void* matrix, void* context);

    /**
     * @brief Clear the packet-in-flight flag and finish the packet.
     * @param value Notification value.
     */
    virtual void on_packet_complete(u32 value);

    /** @brief Forget the packet buffer without deleting it. */
    void func_004E13D0();

    /**
     * @brief Allocate the packet buffer.
     * @param size Size in quadwords.
     * @return One on success, zero when the allocation failed.
     */
    s32 func_004E10B0(s32 size);

    const class LibCamera* camera;
    void* context;
    LibPacketBuffer* unk114;
};
#endif


#endif
