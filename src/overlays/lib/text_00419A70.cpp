#include "include_asm.h"
#include "overlays/lib/movie_player.h"
#include "sdk/main/libkernl_00121940.h"
#include "main/resident_00101260.h"
#include "overlays/lib/transform_owner_inlines.h"
#include "overlays/lib/text_00419A70.h"
#include "overlays/lib/text_004DD440.h"
#include "main/resident_0010A0E0.h"
#include "main/resident_data.h"
#include "main/resident_00101550.h"
#include "overlays/lib/text_0045AD10.h"
#include "ee.h"
#include "overlays/lib/image_capture.h"
#include "vu0.h"
#include "clamp.h"
#include "overlays/lib/tracks.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/lib/emission_vu0.h"
#include "overlays/lib/shape_vu0.h"





/** Partial list indicator rectangle, drawing storage, flags, and scalar pair. */
struct LibListIndicatorState
{
    u8 unk00[0x18];
    float x;
    float y;
    float width;
    float height;
    u8 unk28[0xC];
    u32 unk34;
    u8 unk38;
    u8 unk39;
    u8 unk3a[6];
    LibStorageBlock0C storage;
    u8 unk4c[4];
    float extent;
    float position;
};

/** Partial marker rectangle, drawing storage, flags, and packed colors. */
struct LibMarkerState
{
    u8 unk00[0x18];
    float x;
    float y;
    float width;
    float height;
    u8 unk28[0x11];
    u8 active;
    u8 unk3a[2];
    u8 redraw;
    u8 unk3d[3];
    LibStorageBlock0C storage;
    u8 unk4c[4];
    u32 color;
    u32 dark_color;
};

/** Partial receiver with two pointer fields at offsets 0x14 and 0x18. */
typedef struct LibReceiverPointerPair14
{
    u8 unk00[0x14];
    void* unk14;
    void* unk18;
} LibReceiverPointerPair14;

typedef struct PackedModePair
{
    u8 lowMode : 4;
    u8 highMode : 4;
    u8 hasModeFour : 1;
    u8 unk01_1_7 : 7;
} PackedModePair;

typedef struct PackedModesOwner
{
    u8 unk00[0x22];
    PackedModePair at22;
} PackedModesOwner;

extern "C" void func_00414490(void* object);
extern "C" void func_00414BD0(void* object);
extern "C" void func_004159E0(void* object);
extern "C" s32 func_00418540(LibMovieState* state);

// TODO: The retained-set transforms' destructors inline these two ordinary functions, and LibMoviePlayer::destroy
// inlines lib_movie_stop the same way, so I think the original unit was built with auto-inlining. Until the flags are
// settled, this scoped pragma stands in for it here (they have to be defined before the destructors that use them).
#pragma push
#pragma auto_inline on

/**
 * @brief Take an object out of the first retained set, trimming the set when it was the last one.
 * @param object Object to remove.
 */
void func_00428C80(LibListObject* object)
{
    s32 i;

    for (i = 0; i < D_001B650C; i++)
    {
        if (D_00507CD0[i] == object)
        {
            D_00507CD0[i] = 0;

            if (i == D_001B650C - 1)
            {
                while (D_001B650C > 0)
                {
                    if (D_00507CD0[D_001B650C - 1] != 0)
                    {
                        break;
                    }

                    D_001B650C--;
                }
            }

            return;
        }
    }
}

/**
 * @brief Take an object out of the second retained set, trimming the set when it was the last one.
 * @param object Object to remove.
 */
void func_004289B0(LibListObject* object)
{
    s32 i;

    for (i = 0; i < D_001B6514; i++)
    {
        if (D_00507E50[i] == object)
        {
            D_00507E50[i] = 0;

            if (i == D_001B6514 - 1)
            {
                while (D_001B6514 > 0)
                {
                    if (D_00507E50[D_001B6514 - 1] != 0)
                    {
                        break;
                    }

                    D_001B6514--;
                }
            }

            return;
        }
    }
}

#pragma pop

/** @brief Detach and destroy the image capture, if there is one. */
inline void LibClass1728A0::release_capture()
{
    if (capture)
    {
        lib_object_detach_owner(capture);
        capture->destroy();
        capture = 0;
    }
}

/**
 * @brief Stop the movie and its stream.
 * @param player Movie player.
 */
static inline void movie_stop(LibMoviePlayer* player)
{
    player->stopped = 1;
    player->is_playing = 0;
    func_0011C8E0(g_resource_archive);
    func_0011C6B0(g_resource_archive);
    g_resource_queue->unk2c = 0;
    func_00414490(&player->stream);
    player->stopped = 1;
}

/**
 * @brief Start playing a movie: select its resource and start streaming it, unless a movie is already playing.
 * @param player Movie player.
 * @param movie Resource to play.
 * @param loop Nonzero to let the archive restart the stream.
 * @return 1 once started, 0 while a movie plays or the resource queue is busy.
 */
s32 lib_movie_play(LibMoviePlayer* player, s32 movie, s32 loop)
{
    if (player->is_playing)
    {
        return 0;
    }

    if (!resident_poll_resource_queue(g_resource_queue))
    {
        return 0;
    }

    func_00414BD0(&player->stream);

    if (loop)
    {
        if (!g_resource_archive->read_busy)
        {
            g_resource_archive->unk64 = &player->loop_listener;
        }
    }
    else if (!g_resource_archive->read_busy)
    {
        g_resource_archive->unk64 = 0;
    }

    g_resource_queue->unk2c = 1;
    func_0011D080(g_resource_archive, movie);
    func_0011C120(g_resource_archive, reinterpret_cast<void*>((reinterpret_cast<u32>(player->stream_buffer) + 63) & ~63),
                  LIB_MOVIE_STREAM_BUFFER_SIZE, 0);
    player->stopped = 0;
    func_004159E0(&player->decoder);
    player->movie = movie;
    player->is_playing = 1;
    player->unk15E795 = 1;
    player->unk15E7A4 = 0;
    player->unk15E784 = 0;
    player->unk15E790 = 0;
    return 1;
}

/** @brief Stop the movie if it's playing, then detach and queue the player. */
void LibMoviePlayer::destroy()
{
    if (is_playing)
    {
        movie_stop(this);
    }

    LibTransformOwner::destroy();
}

/** @brief Delete the decoder thread, let go of the archive and destroy the player. */
LibMoviePlayer::~LibMoviePlayer()
{
    lib_object_detach_owner(this);
    delete thread;

    if (!g_resource_archive->read_busy)
    {
        g_resource_archive->unk64 = 0;
    }

    g_movie_player = 0;
}

/**
 * @brief Clear the state's two shown-frame flags, counting down its pending frames for each one set.
 * @param state Playback state.
 */
extern "C" void func_004184D0(LibMovieState* state);

/** Decoder callback types (sceMpegCbType). */
enum
{
    LIB_MPEG_CALLBACK_ERROR = 0,
    LIB_MPEG_CALLBACK_BACKGROUND = 4
};

/** Type ID of the movie player. */
#define LIB_TYPE_ID_MOVIE_PLAYER 0xC00

extern "C"
{
    /** @brief Initialize the MPEG library (libmpeg). */
    void sceMpegInit(void);

    /** @brief Set the decoder up for a frame size. */
    void func_004162F0(LibMovieDecoder* decoder, s32 width, s32 height);

    /** @brief Set the playback state up for a frame size. */
    void func_00419330(LibMovieState* state, s32 width, s32 height);

    /** @brief Register a decoder callback of a sceMpegCbType at an index. */
    void func_00416200(LibMovieDecoder* decoder, s32 type, s32 index, s32 (*callback)(void*, void*, void*), void* data);

    /** @brief Decoder error callback. */
    s32 func_00414DB0(void* decoder, void* data, void* user);

    /** @brief First background callback; feeds the stream. */
    s32 func_00414AC0(void* decoder, void* data, void* user);

    /** @brief Second background callback; feeds the stream. */
    s32 func_004149B0(void* decoder, void* data, void* user);
}

/**
 * @brief Initialize the player and its decoder for a frame size.
 * @param width Frame width.
 * @param height Frame height.
 */
LibMoviePlayer::LibMoviePlayer(s32 width, s32 height)
{
    sceMpegInit();
    this->width = width;
    this->height = height;
    func_004162F0(&decoder, width, height);
    func_00419330(state, width, height);
    func_00416200(&decoder, LIB_MPEG_CALLBACK_ERROR, 0, func_00414DB0, &decoder);
    func_00416200(&decoder, LIB_MPEG_CALLBACK_BACKGROUND, 0, func_00414AC0, &stream);
    func_00416200(&decoder, LIB_MPEG_CALLBACK_BACKGROUND, 1, func_004149B0, &stream);
    stream.buffer = decoder.unkCE580;
    stream.sound = func_00101270(resident_get_system());
    stream.player = this;
    is_playing = 0;
    unk15E795 = 0;
    unk15E796 = 0;
    LibRenderer* renderer = static_cast<LibRenderer*>(g_renderer);
    renderer->insert_node_after(renderer->sentinel.next, this, -1);
    set_type_id(LIB_TYPE_ID_MOVIE_PLAYER);
    unk65 = 0;
    set_draw_flags(LIB_DRAW_FLAG_0400);
    unk15E7A4 = 0;
    thread = new (0) LibMovieThread;
    thread->set_sources(&decoder, &stream);
    thread->player = this;
    thread->start();
    unk15E724 = thread;
    FlushCache(0);
    unk15E797 = 0;
    g_movie_player = this;
}

/**
 * @brief Send the frame packet at unk15E7A4 on VIF1.
 * @param channel DMA channel; unused.
 */
void LibMoviePlayer::submit_dma(u32 channel)
{
    dma_pending = 1;
    *D1_TADR = unk15E7A4;
    *D_STAT = D_STAT_CIS1;
    *D1_CHCR = DMA_CHCR_START | DMA_CHCR_MODE_CHAIN | DMA_CHCR_DIR_FROM_MEMORY;
}

/**
 * @brief Release the shown frame and finish the packet.
 * @param channel DMA channel; unused.
 */
void LibMoviePlayer::complete_dma(u32 channel)
{
    func_004184D0(state);
    lib_finish_packet(this);
}

/** @brief Queue the player's frame packet for VIF1 DMA. */
void LibMoviePlayer::render()
{
    func_00114100(g_vif1_dma_queue, this);
}

/**
 * @brief Build the next frame's packet when the decoder has one ready.
 * @param matrix Matrix supplied by the caller; unused.
 * @param context Opaque caller context; unused.
 */
void LibMoviePlayer::build_packet(const void* matrix, void* context)
{
    unk63 = 0;
    unk62 = 0;

    if (unk15E795)
    {
        unk15E7A4 = func_00418540(state);
        ee_sync();

        if (unk15E7A4)
        {
            unk63 = 1;
        }
    }
}

/**
 * @brief Stop the movie and its stream.
 * @param player Movie player.
 */
void lib_movie_stop(LibMoviePlayer* player)
{
    movie_stop(player);
}

/** @brief Destroy the thread. */
LibMovieThread::~LibMovieThread()
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041A2F0);

void func_0041A530(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041A560);

/**
 * @brief Place a list indicator, set its scroll extent and position, and allocate its drawing storage.
 * @param object List indicator.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param height Bar height.
 * @param extent Size of one scroll step, as a share of the bar.
 * @param position Scroll position.
 * @return One on success, or zero when storage initialization fails.
 */
s32 lib_list_indicator_init(LibListIndicator* object, float x, float y, float height, float extent, float position)
{
    LibListIndicatorState* state = reinterpret_cast<LibListIndicatorState*>(object);
    state->x = x;
    state->y = y;
    state->width = 14.0f;
    state->height = height;
    state->extent = extent;
    state->position = position;
    if (!lib_allocate_drawing_storage(&state->storage, 38))
    {
        return 0;
    }
    state->unk34 = 6;
    state->unk39 = 1;
    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041A9A0);

/** @brief Advance the scalar indicator by the runtime rate and mark it for redraw. */
void ItemCreationClass172600::func_00413D20()
{
    unk50 += g_field_runtime->rate;
    needs_redraw = 1;
}

/**
 * @brief Place a scalar indicator, clear its value and allocate its drawing storage.
 * @param object Scalar indicator widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return One on success, or zero when storage initialization fails.
 */
s32 func_0041AD10(ItemCreationClass172600* object, float x, float y, float width, float height)
{
    object->unk18.unk00 = x;
    object->unk18.unk04 = y;
    object->unk18.unk08 = width;
    object->unk18.unk0c = height;

    if (!lib_allocate_drawing_storage(&object->unk40, 22))
    {
        return 0;
    }

    object->unk50 = 0.0f;
    object->unk34 = 2;
    object->unk39 = 1;
    return 1;
}

/** @brief Draw in bucket 7. */
void LibClass172630::set_default_draw_bucket()
{
    draw_bucket = 7;
}

/**
 * @brief Return the bounding sphere Lib culls against.
 * @return Sphere in a local of this function: zero centre and a radius of 1e30, so the object is never culled.
 */
const LibVector4* LibClass172630::get_bounding_sphere()
{
    s32 stack[4];
    stack[0] = 0;
    stack[3] = 0x7149F2CA;
    stack[1] = 0;
    s32* result = stack;
    stack[2] = 0;
    return reinterpret_cast<const LibVector4*>(result);
}

/** @brief Clear the owner and queue the object for release. */
void LibClass172630::destroy()
{
    owner = 0;
    LibTransformOwner::destroy();
}

/**
 * @brief Send the packet on VIF1 in normal mode.
 * @param channel DMA channel; unused.
 */
void LibClass172630::submit_dma(u32 channel)
{
    dma_pending = 1;
    *D1_QWC = packet_quadwords;
    *D1_MADR = func_0011F760(packet);
    *D_STAT = D_STAT_CIS1;
    *D1_CHCR = DMA_CHCR_START | DMA_CHCR_DIR_FROM_MEMORY;
}

/**
 * @brief Finish the packet.
 * @param channel DMA channel; unused.
 */
void LibClass172630::complete_dma(u32 channel)
{
    lib_finish_packet(this);
}

/** @brief Queue the object's DMA submission on VIF1. */
void LibClass172630::render()
{
    func_00114100(g_vif1_dma_queue, this);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041AE80);

/** @brief Delete the packet and destroy the object. */
LibClass172630::~LibClass172630()
{
    delete packet;
}

/** @brief Set the object up and allocate its packet. */
LibClass172630::LibClass172630()
{
    unka0 = 0.5f;
    unka4 = 0;
    color = 0xF0F0F0;
    unkac = 3;
    unkad = 0;
    unkae = 0;
    unkaf = 0;
    unk65 = 0;
    set_type_id(0xE02);
    set_draw_flags(LIB_DRAW_FLAG_0400);
    packet = new (0) LibPacketBuffer(0x1E0);
}

/**
 * @brief Send the packet on VIF1 in normal mode.
 * @param channel DMA channel; unused.
 */
void LibClass1726C0::submit_dma(u32 channel)
{
    dma_pending = 1;
    *D1_QWC = packet_quadwords;
    *D1_MADR = func_0011F760(packet);
    *D_STAT = D_STAT_CIS1;
    *D1_CHCR = DMA_CHCR_START | DMA_CHCR_DIR_FROM_MEMORY;
}

/**
 * @brief Finish the packet.
 * @param channel DMA channel; unused.
 */
void LibClass1726C0::complete_dma(u32 channel)
{
    lib_finish_packet(this);
}

/** @brief Queue the object's DMA submission on VIF1. */
void LibClass1726C0::render()
{
    func_00114100(g_vif1_dma_queue, this);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041D260);

/** @brief Delete the packet and destroy the object. */
LibClass1726C0::~LibClass1726C0()
{
    delete packet;
}

/** @brief Set the object up and allocate its packet. */
LibClass1726C0::LibClass1726C0()
{
    unka0 = 0.5f;
    unka4 = 0;
    color = 0x80808080;
    unkac = 3;
    unkad = 0;
    unkae = 0;
    unkaf = 0;
    unk65 = 0;
    set_type_id(0xE01);
    set_draw_flags(LIB_DRAW_FLAG_0400);
    packet = new (0) LibPacketBuffer(0x1E0);
}

/**
 * @brief Send the data on VIF1 in normal mode.
 * @param channel DMA channel; unused.
 */
void LibClass172750::submit_dma(u32 channel)
{
    dma_pending = 1;
    *D1_QWC = packet_quadwords;
    *D1_MADR = packet_address;
    *D_STAT = D_STAT_CIS1;
    *D1_CHCR = DMA_CHCR_START | DMA_CHCR_DIR_FROM_MEMORY;
}

/**
 * @brief Finish the packet.
 * @param channel DMA channel; unused.
 */
void LibClass172750::complete_dma(u32 channel)
{
    lib_finish_packet(this);
}

/** @brief Queue the object's DMA submission on VIF1. */
void LibClass172750::render()
{
    func_00114100(g_vif1_dma_queue, this);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041E910);

/** @brief Delete the packet and destroy the object. */
LibClass172750::~LibClass172750()
{
    delete packet;
}

/** @brief Set the object up and allocate its packet. */
LibClass172750::LibClass172750()
{
    unk65 = 0;
    set_type_id(0xE00);
    set_draw_flags(LIB_DRAW_FLAG_0400);
    packet = new (0) LibPacketBuffer(0x40);
    FlushCache(0);
    tex0 = 0;
}

/** @brief Draw in bucket 7. */
void LibClass1726C0::set_default_draw_bucket()
{
    draw_bucket = 7;
}

/**
 * @brief Return the bounding sphere Lib culls against.
 * @return Sphere in a local of this function: zero centre and a radius of 1e30, so the object is never culled.
 */
const LibVector4* LibClass1726C0::get_bounding_sphere()
{
    s32 stack[4];
    stack[0] = 0;
    stack[3] = 0x7149F2CA;
    stack[1] = 0;
    s32* result = stack;
    stack[2] = 0;
    return reinterpret_cast<const LibVector4*>(result);
}

/** @brief Clear the owner and queue the object for release. */
void LibClass1726C0::destroy()
{
    owner = 0;
    LibTransformOwner::destroy();
}

/** @brief Draw in bucket 7. */
void LibClass172750::set_default_draw_bucket()
{
    draw_bucket = 7;
}

/**
 * @brief Return the bounding sphere Lib culls against.
 * @return Sphere in a local of this function: zero centre and a radius of 1e30, so the object is never culled.
 */
const LibVector4* LibClass172750::get_bounding_sphere()
{
    s32 stack[4];
    stack[0] = 0;
    stack[3] = 0x7149F2CA;
    stack[1] = 0;
    s32* result = stack;
    stack[2] = 0;
    return reinterpret_cast<const LibVector4*>(result);
}

/** @brief Clear the owner and queue the object for release. */
void LibClass172750::destroy()
{
    owner = 0;
    LibTransformOwner::destroy();
}

/** @brief Draw in bucket 7. */
void LibClass1727E0::set_default_draw_bucket()
{
    draw_bucket = 7;
}

/**
 * @brief Return the bounding sphere Lib culls against.
 * @return Sphere in a local of this function: zero centre and a radius of 1e30, so the object is never culled.
 */
const LibVector4* LibClass1727E0::get_bounding_sphere()
{
    s32 stack[4];
    stack[0] = 0;
    stack[3] = 0x7149F2CA;
    stack[1] = 0;
    s32* result = stack;
    stack[2] = 0;
    return reinterpret_cast<const LibVector4*>(result);
}

/** @brief Clear the owner and queue the object for release. */
void LibClass1727E0::destroy()
{
    owner = 0;
    LibTransformOwner::destroy();
}

/**
 * @brief Send the packet on VIF1 in normal mode.
 * @param channel DMA channel; unused.
 */
void LibClass1727E0::submit_dma(u32 channel)
{
    dma_pending = 1;
    *D1_QWC = packet_quadwords;
    *D1_MADR = func_0011F760(packet);
    *D_STAT = D_STAT_CIS1;
    *D1_CHCR = DMA_CHCR_START | DMA_CHCR_DIR_FROM_MEMORY;
}

/**
 * @brief Finish the packet.
 * @param channel DMA channel; unused.
 */
void LibClass1727E0::complete_dma(u32 channel)
{
    lib_finish_packet(this);
}

/** @brief Queue the object's DMA submission on VIF1. */
void LibClass1727E0::render()
{
    func_00114100(g_vif1_dma_queue, this);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F350);

/**
 * @brief Allocate VRAM for a power-of-two image and record its size, slot and address.
 * @param object Object to set up.
 * @param width_log2 Image width, as a power of two.
 * @param height_log2 Image height, as a power of two.
 */
void func_004209C0(LibClass1727E0* object, s32 width_log2, s32 height_log2)
{
    object->width_log2 = width_log2;
    object->height_log2 = height_log2;
    object->vram_slot = func_004DCA70(g_vram_allocator, (1 << width_log2) * (1 << height_log2), 0x800, -1);
    object->vram_address = (g_vram_allocator->unk04[object->vram_slot] & 0x3FFF) << 6;
}

/** @brief Delete the packet and destroy the object. */
LibClass1727E0::~LibClass1727E0()
{
    delete packet;
}

/** @brief Set the object up and allocate its packet. */
LibClass1727E0::LibClass1727E0()
{
    s32 i;

    unk96 = 0;
    unk97 = 0;
    unk99 = 1;
    unk9a = 1;
    unk9d = 0;
    unk65 = 0;
    set_type_id(0xF00);
    set_draw_flags(LIB_DRAW_FLAG_0400);
    packet = new (0) LibPacketBuffer(0x400);
    unkb0 = 0x7C808080;
    unkb4 = 0x80808080;
    unka0[0] = 0.0f;
    unka0[1] = 0.0f;
    unka0[2] = 0.0f;
    unka0[3] = 0.0f;
    unk98 = 0;
    unkd8 = 0.5f;
    unk11c = 0.5f;
    unk9e = 1;

    for (i = 0; i < 8; i++)
    {
        unkb8[i] = 0x808080;
        unkdc[i] = 0.0f;
        unkfc[i] = 0.0f;
    }
}

/**
 * @brief Set the marker color to a packed RGB color brightened by 1.8, and mark the marker for redraw.
 * @param object Marker widget.
 * @param color Packed RGB color; each channel is clamped to 255 after brightening.
 */
void func_00420D20(ItemCreationClass172870* object, u32 color)
{
    LibMarkerState* state = reinterpret_cast<LibMarkerState*>(object);
    float red = (color & 0xFF) * 1.8f;
    float green;
    float blue;

    if (red > 255.0f)
    {
        red = 255.0f;
    }

    green = ((color >> 8) & 0xFF) * 1.8f;

    if (green > 255.0f)
    {
        green = 255.0f;
    }

    blue = ((color >> 16) & 0xFF) * 1.8f;

    if (blue > 255.0f)
    {
        blue = 255.0f;
    }

    state->color = ((u32)blue << 16) | ((u32)green << 8) | (u32)red;
    state->redraw = 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00420F20);

/**
 * @brief Allocate marker drawing storage and initialize its rectangle and colors.
 * @param object Marker widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return One on success, or zero if storage cannot be allocated.
 */
s32 lib_marker_init_rectangle(ItemCreationClass172870* object, float x, float y, float width, float height)
{
    LibMarkerState* state = reinterpret_cast<LibMarkerState*>(object);
    u32 shade;
    float intensity;
    state->x = x;
    state->y = y;
    state->width = width;
    state->height = height;
    if (!lib_allocate_drawing_storage(&state->storage, 12))
    {
        return 0;
    }
    intensity = 0.9f;
    shade = (u32)(256.0f * intensity);
    state->color = (shade << 16) | (shade << 8) | shade;
    state->redraw = 1;
    state->dark_color = 0x020202;
    state->active = 1;
    return 1;
}

/**
 * @brief Report the list kind used when registration requests the default.
 * @return Always 16.
 */
s32 LibClass1728A0::get_default_list_kind()
{
    return 16;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00421250);

/** @brief Release the image capture, then delete the object. */
void LibClass1728A0::destroy()
{
    release_capture();
    delete this;
}

void func_004214C0(void* object, void* first, void* second)
{
    LibReceiverPointerPair14* state = (LibReceiverPointerPair14*)object;
    state->unk14 = first;
    state->unk18 = second;
}

/** @brief Release the image capture and destroy the object. */
LibClass1728A0::~LibClass1728A0()
{
    release_capture();
}

/** @brief Create the image capture and add it to the renderer. */
LibClass1728A0::LibClass1728A0() : unk14(0), unk18(0)
{
    capture = new (0) LibImageCapture;
    ((LibUpdateList*)g_renderer)->append_node(capture, -1);
    unk1c = 1;
    unk42c = 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00421650);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00421D80);

/** @brief Delete the buffer and destroy the builder. */
LibClass1728E0::~LibClass1728E0()
{
    delete unk44;
}

/** @brief Construct the builder without a buffer. */
LibClass1728E0::LibClass1728E0() : unk44(0)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004221A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00422850);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00422F70);

/**
 * @brief Send the data on VIF1 in normal mode.
 * @param channel DMA channel; unused.
 */
void LibClass172960::submit_dma(u32 channel)
{
    dma_pending = 1;
    *D1_QWC = packet_quadwords;
    *D1_MADR = packet_address;
    *D_STAT = D_STAT_CIS1;
    *D1_CHCR = DMA_CHCR_START | DMA_CHCR_DIR_FROM_MEMORY;
}

/**
 * @brief Finish the packet.
 * @param channel DMA channel; unused.
 */
void LibClass172960::complete_dma(u32 channel)
{
    lib_finish_packet(this);
}

/** @brief Queue the object's DMA submission on VIF1. */
void LibClass172960::render()
{
    func_00114100(g_vif1_dma_queue, this);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004239C0);

/** @brief Destroy the list receiver and its embedded sentinel. */
inline LibListReceiver::~LibListReceiver()
{
}

/** @brief Allocate a packet big enough for every builder in the list, plus 20 quadwords. */
void LibClass172960::allocate_packet()
{
    s32 size = 20;
    LibListSentinel* node = sentinel.next;

    for (;;)
    {
        if (&sentinel == node)
        {
            break;
        }

        size += static_cast<LibClass1728C0*>(node)->func_00424860();
        node = node->next;
    }

    packet = new (0) LibPacketBuffer(size);
}

/** @brief Release the object at unk240 if unk23d is set, then queue the transform for release. */
void LibClass172960::destroy()
{
    if (unk23d && unk240)
    {
        lib_object_detach_owner(unk240);
        unk240->destroy();
        unk240 = 0;
    }

    LibTransformOwner::destroy();
}

/** @brief Delete the packet, then release the object at unk240 and delete the builders if unk23d is set. */
LibClass172960::~LibClass172960()
{
    delete packet;

    if (unk23d)
    {
        if (unk240)
        {
            lib_object_detach_owner(unk240);
            unk240->destroy();
        }

        LibListSentinel* node = sentinel.next;

        for (;;)
        {
            if (&sentinel == node)
            {
                break;
            }

            LibListSentinel* next = node->next;
            delete node;
            node = next;
        }
    }
}

/** @brief Initialize the transform with an empty builder list and no packet. */
LibClass172960::LibClass172960() : packet(0)
{
    unk65 = 0;
    unk230 = 0xFFFFFF;
    unk23c = 0;
    unk23d = 0;
    unk23e = 1;
    unk240 = 0;
    set_type_id(0x1000);
}

/**
 * @brief Return the size of the builder's packet.
 * @return Size, in quadwords.
 */
s32 LibClass1728E0::func_00424860()
{
    return unk20 * unk1c * 7 / 2 + 4;
}

/** @brief Destroy the builder. */
LibClass172900::~LibClass172900()
{
}

/**
 * @brief Return the size of the builder's packet.
 * @return Size, in quadwords.
 */
s32 LibClass172900::func_00424860()
{
    return unk20 / 2 + unk20 * 2 + 9;
}

/** @brief Destroy the builder. */
LibClass172920::~LibClass172920()
{
}

/**
 * @brief Return the size of the builder's packet.
 * @return Always 398 quadwords.
 */
s32 LibClass172920::func_00424860()
{
    return 398;
}

/** @brief Destroy the builder. */
LibClass172940::~LibClass172940()
{
}

/**
 * @brief Return the size of the builder's packet.
 * @return Always 230 quadwords.
 */
s32 LibClass172940::func_00424860()
{
    return 230;
}

/** @brief Draw in bucket 9. */
void LibClass172960::set_default_draw_bucket()
{
    draw_bucket = 9;
}

/**
 * @brief Return the bounding sphere Lib culls against.
 * @return Sphere in a local of this function: zero centre and a radius of 1e30, so the object is never culled.
 */
const LibVector4* LibClass172960::get_bounding_sphere()
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
 * @brief Report the list kind used when registration requests the default.
 * @return Always 4.
 */
s32 LibClass172A20::get_default_list_kind()
{
    return 4;
}

/**
 * @brief Copy a matrix as four 128-bit rows.
 * @param destination Matrix receiving the copy.
 * @param source Matrix to copy.
 */
static inline void copy_matrix(LibMatrix44Value* destination, const LibMatrix44Value* source)
{
    ((unsigned __int128*)destination)[0] = ((const unsigned __int128*)source)[0];
    ((unsigned __int128*)destination)[1] = ((const unsigned __int128*)source)[1];
    ((unsigned __int128*)destination)[2] = ((const unsigned __int128*)source)[2];
    ((unsigned __int128*)destination)[3] = ((const unsigned __int128*)source)[3];
}

/**
 * @brief Report whether the transform's transpose is current.
 * @param transform Transform to check.
 * @return Nonzero when the transpose was rebuilt since the matrix last changed.
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

/** @brief Update the matrix and the world position. */
void LibClass172B40::update()
{
    update_transform_matrix();
    position.x = transform.m[0][3];
    position.y = transform.m[1][3];
    position.z = transform.m[2][3];
    position.w = 1.0f;
}

/** @brief Update the matrices, the inverse copy and the world down axis. */
void LibClass172C60::update()
{
    update_transform_matrix();

    if (!transpose_is_current(this))
    {
        transpose_transform(this);
        func_004D9E70(this);
        vu0_transform_emission_direction(&transposed_transform, &D_00507F70, &down);
        const LibMatrix44Value* source = &inverse_transform;
        copy_matrix(&inverse, source);
    }
}

/** @brief Update the matrix and the world down axis. */
void LibClass172CF0::update()
{
    update_transform_matrix();

    if (!transpose_is_current(this))
    {
        transpose_transform(this);
        vu0_transform_emission_direction(&transposed_transform, &D_00507F70, &down);
    }
}

/** @brief Update the matrices, the world position and the world down axis. */
void LibClass172D80::update()
{
    update_transform_matrix();

    if (!transpose_is_current(this))
    {
        transpose_transform(this);
        func_004D9E70(this);
        vu0_apply_matrix(&transposed_transform, &D_00507F60, &position);
        vu0_transform_emission_direction(&transposed_transform, &D_00507F70, &down);
    }
}

/** @brief Update the matrices. */
void LibClass172E10::update()
{
    update_transform_matrix();

    if (!transpose_is_current(this))
    {
        transpose_transform(this);
        func_004D9E70(this);
    }
}

/** @brief Update the matrix, the world position and the world down axis. */
void LibClass172EA0::update()
{
    update_transform_matrix();

    if (!transpose_is_current(this))
    {
        transpose_transform(this);
        vu0_apply_matrix(&transposed_transform, &D_00507F60, &position);
        vu0_transform_emission_direction(&transposed_transform, &D_00507F70, &down);
    }
}

/** @brief Update the world-space shape. */
void LibClass172AB0::update()
{
    func_00425280();
}

/** @brief Bring the world-space shape up to date; the base shape has none. */
void LibClass172AB0::func_00425280()
{
}

/** @brief Update the matrix and move the local point and axis into world space. */
void LibClass172FC0::func_00425280()
{
    update_transform_matrix();

    if (!transpose_is_current(this))
    {
        transpose_transform(this);
        copy_vector(&point, &local_point);
        copy_vector(&axis, &local_axis);
        vu0_transform_point_and_direction(&transposed_transform, &point, &axis);
    }
}

/** @brief Update the matrix and the world position. */
void LibClass172F30::func_00425280()
{
    update_transform_matrix();

    if (!transpose_is_current(this))
    {
        transpose_transform(this);
        vu0_apply_matrix(&transposed_transform, &D_00507F60, &position);
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425490);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425600);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004257A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425870);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425970);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425AC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425B40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425C90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425E10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425FC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004260C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004261E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00426370);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004264F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00426650);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00426C20);

/** @brief Destroy the transform. */
LibClass172FC0::~LibClass172FC0()
{
}

struct SmallConditionalInput04
{
    u8 unk00[4];
    float unk04;
};

extern "C" s32 func_004284A0(void* object, const void* value, float* zero_output, float* small_output)
{
    const SmallConditionalInput04* state = (const SmallConditionalInput04*)value;
    if (!(state->unk04 <= 0.0f))
    {
        *zero_output = 0.0f;
        *small_output = 0.05f;
        return 1;
    }
    return 0;
}

/**
 * @brief Test against another shape; the base shape never touches anything.
 * @param other Other shape; unused.
 * @param direction Unused.
 * @param first Unused.
 * @param second Unused.
 * @return Always 0.
 */
s32 LibClass172AB0::func_004284E0(LibClass172AB0* other, LibVector4* direction, float* first, float* second)
{
    return 0;
}

/**
 * @brief Test against another shape with a scale; the base shape never touches anything.
 * @param other Other shape; unused.
 * @param scale Unused.
 * @param direction Unused.
 * @param first Unused.
 * @param second Unused.
 * @return Always 0.
 */
s32 LibClass172AB0::func_004284F0(LibClass172AB0* other, const LibVector4* scale, LibVector4* direction, float* first,
                                  float* second)
{
    return 0;
}

/**
 * @brief Work out the effect at a position; the base adds nothing.
 * @param position Unused.
 * @param unk Unused.
 * @param output Unused.
 * @param source Unused.
 */
void LibClass172BD0::func_00428500(const LibVector4* position, const void* unk, LibVector4* output, const void* source)
{
}

// TODO: Like LibClass173380::update, the game enters this list loop with a jump to its test instead of a guard, which
// I've only got with loop rotation off.
#pragma push
#pragma opt_rotateloops off

/** @brief Update every node in the list, in order. */
void LibClass173080::update()
{
    LibListSentinel* end = &sentinel;
    LibListSentinel* node = end->next;

    while (end != node)
    {
        static_cast<LibListObject*>(node)->update();
        node = node->next;
    }
}

#pragma pop

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428570);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428670);

/**
 * @brief Detach and destroy every object in the second retained set that was added with a tag, then trim the set.
 * @param tag Tag to release.
 */
void func_004288C0(u8 tag)
{
    s32 i;

    for (i = 0; i < D_001B6514; i++)
    {
        if (D_00507E50[i] != 0 && D_00507E10[i] == tag)
        {
            lib_object_detach_owner(D_00507E50[i]);
            D_00507E50[i]->destroy();
            D_00507E50[i] = 0;
        }
    }

    while (D_001B6514 > 0)
    {
        if (D_00507E50[D_001B6514 - 1] != 0)
        {
            break;
        }

        D_001B6514--;
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428A50);

/**
 * @brief Count the objects in the second retained set.
 * @return Number of occupied slots.
 */
s32 func_00428AF0(void)
{
    s32 count = 0;
    s32 i;

    for (i = 0; i < D_001B6514; i++)
    {
        if (D_00507E50[i] != 0)
        {
            count++;
        }
    }

    return count;
}

/**
 * @brief Count the objects in the first retained set.
 * @return Number of occupied slots.
 */
s32 func_00428B40(void)
{
    s32 count = 0;
    s32 i;

    for (i = 0; i < D_001B650C; i++)
    {
        if (D_00507CD0[i] != 0)
        {
            count++;
        }
    }

    return count;
}

/**
 * @brief Detach and destroy every object in the first retained set that was added with a tag, then trim the set.
 * @param tag Tag to release.
 */
void func_00428B90(u8 tag)
{
    s32 i;

    for (i = 0; i < D_001B650C; i++)
    {
        if (D_00507CD0[i] != 0 && D_00507DD0[i] == tag)
        {
            lib_object_detach_owner(D_00507CD0[i]);
            D_00507CD0[i]->destroy();
            D_00507CD0[i] = 0;
        }
    }

    while (D_001B650C > 0)
    {
        if (D_00507CD0[D_001B650C - 1] != 0)
        {
            break;
        }

        D_001B650C--;
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428D20);

/**
 * @brief Report the list kind used when registration requests the default.
 * @return Always 4.
 */
s32 LibClass172AB0::get_default_list_kind()
{
    return 4;
}

/** @brief Destroy the transform. */
LibClass172B40::~LibClass172B40()
{
}

/**
 * @brief Report the list kind used when registration requests the default.
 * @return Always 4.
 */
s32 LibClass172B40::get_default_list_kind()
{
    return 4;
}

/** @brief Destroy the transform. */
LibClass172C60::~LibClass172C60()
{
}

/** @brief Destroy the transform. */
LibClass172CF0::~LibClass172CF0()
{
}

/** @brief Destroy the transform. */
LibClass172D80::~LibClass172D80()
{
}

/** @brief Destroy the transform. */
LibClass172E10::~LibClass172E10()
{
}

/** @brief Destroy the transform. */
LibClass172EA0::~LibClass172EA0()
{
}

/** @brief Destroy the transform. */
LibClass172F30::~LibClass172F30()
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004293D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00429480);

s32 func_004294F0(void* object)
{
    return 5;
}

extern LibTrackPool<LibPooledQuaternionTrack>* g_quaternion_track_pool;

/**
 * @brief Decode a packed keyframe rotation, rebuilding w.
 * @param entry Keyframe.
 * @return Rotation.
 */
static inline FieldVec4B decoded_rotation(const LibQuaternionTrackKey* entry)
{
    FieldVec4A value;
    vu0_decode_short_quaternion(entry);
    vu0_store_decoded_quaternion(&value);
    return value;
}

/**
 * @brief Subtract two rotations, all four components.
 * @param left Rotation to subtract from.
 * @param right Rotation to subtract.
 * @return left - right.
 */
static inline FieldVec4B rotation_difference(const FieldVec4B& left, const FieldVec4B& right)
{
    FieldVec4B value;
    value.x = left.x - right.x;
    value.y = left.y - right.y;
    value.z = left.z - right.z;
    value.w = left.w - right.w;
    return value;
}

/**
 * @brief Pack a unit rotation's x, y and z into 1.15 fixed point, negated when w is negative so w can be rebuilt.
 * @param value Rotation.
 * @param x Receives the packed x.
 * @param y Receives the packed y.
 * @param z Receives the packed z.
 */
static inline void pack_rotation(const FieldVec4A* value, s32& x, s32& y, s32& z)
{
    x = value->x * 32768.0f;
    y = value->y * 32768.0f;
    z = value->z * 32768.0f;

    if (value->w < 0.0f)
    {
        x = -x;
        y = -y;
        z = -z;
    }

    x = clamp_high(x, 0x7FFF);
    y = clamp_high(y, 0x7FFF);
    z = clamp_high(z, 0x7FFF);
    x = clamp_low(x, -0x8000);
    y = clamp_low(y, -0x8000);
    z = clamp_low(z, -0x8000);
}

/** @brief Destroy the list. */
LibClass173080::~LibClass173080()
{
}

/**
 * @brief Append a keyframe through append_rotation.
 * @param value Keyframe rotation.
 * @param first Unused.
 * @param second Unused.
 * @param key Sort key.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibPooledQuaternionTrack::append_key(const void* value, const void* first, const void* second, float key)
{
    return append_rotation(static_cast<const FieldVec4A*>(value), key);
}

/**
 * @brief Replace a keyframe through replace_rotation.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe rotation.
 * @param first Unused.
 * @param second Unused.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibPooledQuaternionTrack::replace_key(s32 index, float key, const void* value, const void* first, const void* second)
{
    return replace_rotation(index, key, static_cast<const FieldVec4A*>(value));
}

/**
 * @brief Insert a keyframe through insert_rotation.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe rotation.
 * @param first Unused.
 * @param second Unused.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibPooledQuaternionTrack::insert_key(s32 index, float key, const void* value, const void* first, const void* second)
{
    return insert_rotation(index, key, static_cast<const FieldVec4A*>(value));
}

/**
 * @brief Store a single keyframe through on_set_single_key.
 * @param value Keyframe rotation.
 * @param first Unused.
 * @param second Unused.
 * @param key Sort key.
 */
void LibPooledQuaternionTrack::set_single_key(const void* value, const void* first, const void* second, float key)
{
    on_set_single_key(static_cast<const FieldVec4A*>(value), key);
}

/**
 * @brief Report how fast the sampled rotation was changing; this track always reports zero.
 * @param output Receives the rate.
 */
void LibPooledQuaternionTrack::get_value_rate(void* output) const
{
    *(unsigned __int128*)output = 0;
}

/** @brief Give the track back to g_quaternion_track_pool when it came from one, otherwise delete it. */
void LibPooledQuaternionTrack::release()
{
    if (this != 0)
    {
        if (state.pooled)
        {
            LibQuaternionTrackBase::free_keys();
            quaternion_track_pool_free(g_quaternion_track_pool, this);
        }
        else
        {
            delete this;
        }
    }
}

/** @brief Cycle past the ends, then reset to a single zero keyframe at key zero. */
void LibPooledQuaternionTrack::reset_keys()
{
    set_before_mode(LIB_TRACK_END_CYCLE);
    FieldVec4A zero(0.0f, 0.0f, 0.0f, 0.0f);
    on_set_single_key(&zero, 0.0f);
}

/** @brief Destroy the track. */
LibPooledQuaternionTrack::~LibPooledQuaternionTrack()
{
}

/** Set the low packed mode at 0x22 and record whether either mode equals four. */
void func_004297F0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at22.lowMode = mode;
    receiver->at22.hasModeFour = receiver->at22.lowMode == 4 || receiver->at22.highMode == 4;
}

void func_00429850(void* object)
{
}

/**
 * @brief Write the difference between the last and first key rotations, all four components.
 * @param output Receives the difference.
 */
void LibPooledQuaternionTrack::get_end_delta(void* output) const
{
    *static_cast<FieldVec4B*>(output) = rotation_difference(decoded_rotation(&key_array[state.key_count - 1]), decoded_rotation(key_array));
}

/**
 * @brief Pack a rotation into the cached single key, and use it before the first key.
 * @param value Keyframe rotation.
 * @param key Sort key.
 */
void LibPooledQuaternionTrack::on_set_single_key(const FieldVec4A* value, float key)
{
    s32 x;
    s32 y;
    s32 z;

    set_before_mode(LIB_TRACK_END_USE_PRE_START_KEY);
    pack_rotation(value, x, y, z);
    single_key.packed_rotation[0] = x;
    single_key.packed_rotation[1] = y;
    single_key.packed_rotation[2] = z;
    single_key.key = key;
}
