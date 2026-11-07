#ifndef SO3_OVERLAYS_BOOT_TITLE_MENU_H
#define SO3_OVERLAYS_BOOT_TITLE_MENU_H

#include "types.h"
#include "overlays/boot/boot.h"

/** 0xE0-byte screen fade with vtable D_171C00 in main data: ten strips copied from the display, faded out. */
class BootScreenFade : public LibTransformOwner, public LibDmaCallbacks
{
    public:
        /**
         * @brief Copy the display into ten strips and show them, fully opaque.
         * @param display Display to copy.
         */
        BootScreenFade(LibCameraContext* display);

        /** @brief Destroy the strips, the copy buffer and the packet. */
        virtual ~BootScreenFade();

        /** @brief Fade out; once transparent, destroy the strips and the fade. */
        virtual void update();

        /** @brief Mark the fade active and submit its packet. */
        virtual void render();

        /** @brief Draw in bucket 10 instead of the main list. */
        virtual void set_default_draw_bucket();

        /**
         * @brief Build the fade's GS packet: upload each of the ten strips to VRAM and draw it as a sprite at the
         * fade's alpha. The first call only arms the fade.
         * @param matrix Matrix supplied by the caller; unused.
         * @param context Opaque caller context; unused.
         */
        virtual void build_packet(const void* matrix, void* context);

        /**
         * @brief Mark the fade inactive and run the Lib release helper.
         * @param value Unused.
         */
        virtual void on_packet_complete(u32 value);

        LibImageCapture* images[10];
        u8* buffer;
        LibCameraContext* display;
        LibPacketBuffer* packet;
        u8 armed;
        u8 unkc9[3];
        float alpha;
        float fade_speed;
        u8 unkd4[0xC];
};

/**
 * Title menu, with vtable D_171BB0 in main data: a Lib scene from resources 0x27 and 0xA whose nodes are the New Game,
 * Continue, Battle Collection and Install entries.
 */
class BootTitleMenu : public LibListObject
{
    public:
        /**
         * @brief Queue the scene resources and remember the item to start on.
         * @param initial_item Item to select first, or -1 to pick Continue when a card holds a save.
         */
        BootTitleMenu(s32 initial_item);

        /** @brief Free the resource buffers, then destroy the scene and its model. */
        virtual ~BootTitleMenu();

        /** @brief Run the menu state machine. */
        virtual void update();

        /**
         * @brief Grow and pulse the selected item and ease the others back to normal.
         * @param snap Nonzero to put the selected item straight at full size.
         */
        void animate_items(u8 snap);

        /**
         * @brief Work out the screen position of the cursor beside the selected item.
         * @param x Receives the horizontal position, or zero if the item has no node.
         * @param y Receives the vertical position, or zero if the item has no node.
         */
        void get_cursor_position(float* x, float* y);

        /** @brief Dim Continue and Battle Collection unless a memory card holds the data they need. */
        void update_item_availability();

        LibScene* scene;
        s32 step;

        /** The scene's camera node, made the current display. */
        void* camera;

        /** Arrow beside the selected item. */
        class LibSelectionCursor* cursor;

        u8* scene_data;

        /** Selected item: 0 New Game, 1 Continue, 2 Battle Collection, 3 Install. */
        u8 selected;

        u8 unk29;

        /** Nonzero while the selected item's color brightens again. */
        u8 pulse_up;

        /** Nonzero when a memory card holds a save to continue. */
        u8 continue_ready;

        /** Lets the fourth item start the BB Unit installer; boot only ever clears it. */
        u8 install_ready;

        /** Nonzero when a memory card holds Battle Collection data. */
        u8 collection_ready;

        u8 unk2e[2];

        /** Resource 10; Lib (0x40B3A0) sets up the game's resident records from it before it is freed. */
        u8* game_data;

        /** Item to select first, or -1 to choose from the memory cards. */
        s32 initial_item;

        /** Seconds on the menu without a choice; the opening movie plays again after 45. */
        float idle_time;
};

/** 0x2C-byte progress bar with vtable D_171BD0 in main data; driven with a done/total pair. */
class BootProgressBar : public LibListObject
{
    public:
        /** @brief Initialize the progress bar. */
        BootProgressBar();

        /** @brief Destroy the bar's model, then the bar. */
        virtual ~BootProgressBar();

        /** @brief Detach the bar and its model, destroy the model and delete the bar. */
        virtual void destroy();

        class LibDrawBuffer* draw_buffer;
        LibModel* model;
        s32 width;
        s32 height;
        u32 color;
        s32 mode;
};

/** 0x30-byte image object with vtable D_171C90 in main data, drawn from a decoded FIS image. */
class BootImage : public LibListObject
{
    public:
        /** @brief Clear the object's model and state bytes. */
        BootImage();

        /** @brief Destroy the image's model, then the image. */
        virtual ~BootImage();

        /** @brief Detach the image and its model, destroy the model and delete the image. */
        virtual void destroy();

        /**
         * @brief Recreate the draw buffer and model and upload a texture and optional palette.
         * @param texture Texture resource.
         * @param palette Palette resource, or null.
         */
        void set_texture(const LibImageResource* texture, const LibImageResource* palette);

        /**
         * @brief Build the image's quad from a rectangle of its texture and queue the model for drawing.
         * @param x Left edge of the rectangle in the texture, in texels.
         * @param y Top edge of the rectangle in the texture.
         * @param width Rectangle width, which is also the quad's width.
         * @param height Rectangle height, which is also the quad's height.
         * @param color Vertex color.
         * @param depth Z position of the quad.
         */
        void set_rectangle(s32 x, s32 y, s32 width, s32 height, u32 color, s32 depth);

        class LibDrawBuffer* draw_buffer;
        LibModel* model;

        /** Texture width in texels. */
        s32 texture_width;

        /** Texture height in texels. */
        s32 texture_height;

        s32 palette_width;
        s32 palette_height;

        /** Flag passed when the draw buffer is closed (Lib then writes 0x60 in its header); boot only ever clears it. */
        u8 end_mode;

        /** Nonzero to center the quad on the model's origin; otherwise its top-left corner sits there. */
        u8 centered;

        /** Nonzero once a palette has been uploaded. */
        u8 has_palette;
};

/** One fade strip's packet: upload the strip's image to VRAM, then draw it as a textured sprite. */
struct BootFadeStripPacket
{
    u64 transfer_dma;

    /** Upper half of the DMA tag; left unwritten, as the tag doesn't transfer it. */
    u64 transfer_dma_high;

    GsGifTag transfer_tag;
    u64 bitbltbuf;
    u64 bitbltbuf_register;
    u64 trxpos;
    u64 trxpos_register;
    u64 trxreg;
    u64 trxreg_register;
    u64 trxdir;
    u64 trxdir_register;
    u64 image_tag;

    /** REGS half of the IMAGE-mode GIF tag; unused, so left unwritten. */
    u64 image_tag_registers;

    u64 image_dma;
    u64 image_dma_high;
    u64 draw_dma;
    u64 draw_dma_high;
    GsGifTag draw_tag;
    u64 texflush;
    u64 texflush_register;
    u64 tex0;
    u64 tex0_register;
    u64 prim;
    u64 prim_register;
    u64 rgbaq;
    u64 rgbaq_register;
    GsGifTag sprite_tag;
    u64 uv0;
    u64 xyz0;
    u64 uv1;
    u64 xyz1;
};

/**
 * @brief Initialize the settings record to its default values.
 * @param settings Settings record to initialize.
 */
void init_draw_settings(LibDrawSettings* settings);

/**
 * @brief Build an image's quad from a rectangle of its texture and a rectangle of its palette, and queue the
 * model for drawing.
 * @param image Image to build.
 * @param x Left edge of the texture rectangle, in texels.
 * @param y Top edge of the texture rectangle.
 * @param width Rectangle width, which is also the quad's width.
 * @param height Rectangle height, which is also the quad's height.
 * @param palette_x Left edge of the palette rectangle.
 * @param palette_y Top edge of the palette rectangle.
 * @param palette_width Palette rectangle width.
 * @param palette_height Palette rectangle height.
 * @param color Vertex color.
 * @param depth Z position of the quad.
 */
void image_set_rectangle_with_palette(BootImage* image, s32 x, s32 y, s32 width, s32 height, s32 palette_x, s32 palette_y, s32 palette_width,
                                      s32 palette_height, u32 color, s32 depth);

/**
 * @brief Encode a saved record and seal it with a fresh checksum; a damaged record is wiped instead.
 * @param record Record to seal; an already sealed record is left alone.
 */
void seal_record(LibSealedRecord* record);

/**
 * @brief Draw a progress bar: a dark border, the bar outline and a fill proportional to done / total.
 * @param bar Progress bar to draw.
 * @param done Completed amount; clamped to total.
 * @param total Total amount.
 */
void progress_bar_draw(BootProgressBar* bar, s32 done, s32 total);

/**
 * @brief Recreate the bar's draw buffer and model, then draw it empty and show it.
 * @param bar Progress bar.
 * @param width Bar width.
 * @param height Bar height.
 * @param color Bar color.
 * @param mode Draw mode.
 */
void progress_bar_reset(BootProgressBar* bar, s32 width, s32 height, u32 color, s32 mode);

#endif
