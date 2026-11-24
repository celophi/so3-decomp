#include "include_asm.h"
#include "overlays/lib/movie_player.h"
#include "sdk/main/libkernl_00121940.h"
#include "overlays/lib/transform_owner_inlines.h"
#include "overlays/lib/text_00419A70.h"
#include "overlays/lib/text_004DD440.h"
#include "main/resident_data.h"
#include "overlays/lib/text_0045AD10.h"
#include "ee.h"
#include "overlays/lib/image_capture.h"
#include "vu0.h"
#include "clamp.h"
#include "angle.h"
#include "main/utility.h"
#include "overlays/lib/tracks.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/lib/emission_vu0.h"
#include "overlays/lib/shape_vu0.h"
#include "overlays/lib/link_vu0.h"
#include "overlays/lib/light_random.h"
#include "overlays/lib/quaternion_vu0.h"
#include "overlays/lib/direction_vu0.h"





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

extern "C" s32 func_004159E0(LibMovieDecoder* decoder);

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
    player->decoder.stopped = 1;
    player->is_playing = 0;
    resident_archive_stop_ring_read(g_resource_archive);
    resident_archive_do_nothing(g_resource_archive);
    g_resource_queue->unk2c = 0;
    player->stream.stop_sound();
    player->decoder.stopped = 1;
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

    player->stream.reset();

    if (loop)
    {
        if (!g_resource_archive->read_busy)
        {
            g_resource_archive->disc_thread.unk64 = &player->loop_listener;
        }
    }
    else if (!g_resource_archive->read_busy)
    {
        g_resource_archive->disc_thread.unk64 = 0;
    }

    g_resource_queue->unk2c = 1;
    resident_archive_select_resource(g_resource_archive, movie);
    resident_archive_start_ring_read(g_resource_archive, reinterpret_cast<void*>((reinterpret_cast<u32>(player->decoder.input.data) + 63) & ~63),
                  LIB_MOVIE_STREAM_BUFFER_SIZE, 0);
    player->decoder.stopped = 0;
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
        g_resource_archive->disc_thread.unk64 = 0;
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
    func_00419330(decoder.state, width, height);
    func_00416200(&decoder, LIB_MPEG_CALLBACK_ERROR, 0, func_00414DB0, &decoder);
    func_00416200(&decoder, LIB_MPEG_CALLBACK_BACKGROUND, 0, func_00414AC0, &stream);
    func_00416200(&decoder, LIB_MPEG_CALLBACK_BACKGROUND, 1, func_004149B0, &stream);
    stream.buffer = &decoder.input;
    stream.sound = resident_system_get_sound(resident_get_system());
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
    decoder.thread = thread;
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
    func_004184D0(decoder.state);
    lib_finish_packet(this);
}

/** @brief Queue the player's frame packet for VIF1 DMA. */
void LibMoviePlayer::render()
{
    resident_dma_queue_push(g_vif1_dma_queue, this);
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
        unk15E7A4 = func_00418540(decoder.state);
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

/**
 * @brief Descramble streamed movie data in place, a 64-byte block at a time: each doubleword is XORed with a key
 *        made from the system's SLE key, then lowered by 0x39 and a counter that cycles through 32 blocks.
 * @param data Address of the data to descramble.
 * @param size Size of the data in bytes.
 * @param buffer Start of the ring buffer the data is in.
 * @param buffer_size Size of the ring buffer in bytes; the data wraps to its start at the end.
 */
void LibMovieLoopListener::handle(u32 data, u32 size, u32 buffer, u32 buffer_size)
{
    unsigned __int128 seed = resident_get_system()->sle_key;
    const u64* seed_words = reinterpret_cast<const u64*>(&seed);
    u64 key0 = seed_words[0] ^ 0x432F96439F773428ULL;
    u64 key1 = seed_words[1] ^ 0x7726FDC15439F654ULL;
    u64 key2 = seed_words[0] ^ 0x35F437939FFF7CCDULL;
    u64 key3 = seed_words[1] ^ 0x64327FCCDF7EF358ULL;
    u64 key4 = seed_words[0] ^ 0x5432678932464312ULL;
    u64 key5 = seed_words[1] ^ 0xCCDEFACD32432146ULL;
    u64 key6 = seed_words[0] ^ 0x43299F7658321943ULL;
    u64 key7 = seed_words[1] ^ 0x7739FD014DF73254ULL;
    u64 counter = 0;

    for (s32 left = size; left > 0; left -= 0x40, data += 0x40)
    {
        if (data >= buffer + buffer_size)
        {
            data -= buffer_size;
        }

        u64* words = reinterpret_cast<u64*>(data);
        words[0] = (words[0] ^ key0) - 0x39 - counter;
        words[1] = (words[1] ^ key1) - 0x39 - counter;
        words[2] = (words[2] ^ key2) - 0x39 - counter;
        words[3] = (words[3] ^ key3) - 0x39 - counter;
        words[4] = (words[4] ^ key4) - 0x39 - counter;
        words[5] = (words[5] ^ key5) - 0x39 - counter;
        words[6] = (words[6] ^ key6) - 0x39 - counter;
        words[7] = (words[7] ^ key7) - 0x39 - counter;
        counter = (counter + 1) & 0x1F;
    }

    FlushCache(0);
}

void func_0041A530(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", draw__16LibListIndicatorFv);

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
    *D1_MADR = resident_packet_get_address(packet);
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
    resident_dma_queue_push(g_vif1_dma_queue, this);
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
    *D1_MADR = resident_packet_get_address(packet);
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
    resident_dma_queue_push(g_vif1_dma_queue, this);
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
    resident_dma_queue_push(g_vif1_dma_queue, this);
}

/**
 * @brief Pack a GS XYZ2 value.
 * @param x Horizontal position in 12.4 fixed point.
 * @param y Vertical position in 12.4 fixed point.
 * @param z Depth.
 * @return XYZ2 register value.
 */
static inline u64 gs_xyz2(s32 x, s32 y, u32 z)
{
    return ((u64)y << 16) | (u64)x | ((u64)z << 32);
}

/**
 * @brief Rebuild the packet when the display's frame changes: draw the whole display in 64-pixel sprite strips with
 *        the frame masked off, then restore FRAME_1, ZBUF_1 and TEST_1.
 * @param matrix View matrix; unused.
 * @param context Packet building context; unused.
 */
void LibClass172750::build_packet(const void* matrix, void* context)
{
    u64 frame = func_004DBCA0(display, 0) | ((u64)0xFFFFFF << 32);

    if (tex0 != frame)
    {
        tex0 = frame;
        resident_packet_rewind(packet);
        u64* cursor = reinterpret_cast<u64*>(resident_packet_reserve(packet, 0));
        cursor[0] = 0;
        u32* vif = reinterpret_cast<u32*>(cursor + 1);
        vif[0] = 0x06008000;
        u32* direct = vif + 1;
        owner = (LibUpdateList*)g_renderer;
        LibDisplayArea* area = &display->display_area;
        GsGifTag* tag = reinterpret_cast<GsGifTag*>(cursor + 2);
        tag->tag = GIF_TAG_NREG(1) | 6;
        tag->registers = 0;
        tag->fields.register0 = GIF_REGISTER_AD;
        cursor[4] = frame;
        cursor[5] = GS_REGISTER_FRAME_1;
        cursor[6] = 0x32000000 | ((u64)1 << 32);
        cursor[7] = GS_REGISTER_ZBUF_1;
        cursor[8] = 0x30000;
        cursor[9] = GS_REGISTER_TEST_1;
        cursor[10] = GS_PRIM_SPRITE;
        cursor[11] = GS_REGISTER_PRIM;
        cursor[12] = 0;
        cursor[13] = GS_REGISTER_FBA_1;
        cursor[14] = 0;
        cursor[15] = GS_REGISTER_RGBAQ;

        s32 strips = area->width / 64;
        s32 left = (0x800 - area->width / 2) * 16;
        s32 top = (0x800 - area->height / 2) * 16;

        tag = reinterpret_cast<GsGifTag*>(cursor + 16);
        tag->tag = GIF_TAG_NREG(2) | GIF_TAG_FLG_REGLIST | strips;
        tag->registers = 0;
        tag->fields.register0 = GIF_REGISTER_XYZ2;
        tag->fields.register1 = GIF_REGISTER_XYZ2;
        cursor += 18;

        for (s32 i = 0; i < strips; i++)
        {
            cursor[0] = gs_xyz2(left + i * 0x400, top, 0xFFFFFF);
            cursor[1] = gs_xyz2(left + (i + 1) * 0x400, top + area->height * 16, 0xFFFFFF);
            cursor += 2;
        }

        tag = reinterpret_cast<GsGifTag*>(cursor);
        tag->tag = GIF_TAG_NREG(1) | GIF_TAG_EOP | 3;
        tag->registers = 0;
        tag->fields.register0 = GIF_REGISTER_AD;
        cursor[2] = func_004DBCA0(display, 0);
        cursor[3] = GS_REGISTER_FRAME_1;
        cursor[4] = func_004DBCA0(display, 1);
        cursor[5] = GS_REGISTER_ZBUF_1;
        cursor[6] = func_004DBCA0(display, 4);
        cursor[7] = GS_REGISTER_TEST_1;
        resident_packet_align_cursor(packet, reinterpret_cast<u8*>(cursor + 8));
        packet_quadwords = resident_packet_end_unmask_path3(packet);
        *direct = VIF_DIRECTHL(packet_quadwords - 2);
        packet_address = resident_packet_get_address(packet);
    }

    unk63 = 1;
}

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
    *D1_MADR = resident_packet_get_address(packet);
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
    resident_dma_queue_push(g_vif1_dma_queue, this);
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", draw__23ItemCreationClass172870Fv);

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

/**
 * @brief Read back the 16 by 16 depth block centred on (x, y) and record the share of its values below the threshold.
 *        The first update only starts the read.
 */
void LibClass1728A0::update()
{
    LibRenderer* renderer = static_cast<LibRenderer*>(static_cast<LibListObject*>(unk14)->owner);
    LibCameraContext* display = renderer->display;
    LibDisplayArea* area = &display->display_area;
    s32 left = x - 8;
    s32 top = y - 8;
    s32 width = display->display_area.width;

    if (left < 0)
    {
        left = 0;
    }

    if (top < 0)
    {
        top = 0;
    }

    lib_image_capture_store(capture, depth, (*reinterpret_cast<const u32*>(&display->buffers[0].environment.context1.depth_buffer) & 0x1FF) << 5,
                            width / 64, area->depth_format, left, top, 16, 16);

    if (unk1c)
    {
        unk1c = 0;
        return;
    }

    s32 count = 0;

    switch (area->depth_format)
    {
    case GS_PSMZ32:
    {
        u32* value = (u32*)depth;

        for (s32 i = 0; i < 0x100; i++)
        {
            if (*value < threshold)
            {
                count++;
            }

            value++;
        }

        break;
    }
    case GS_PSMZ24:
    {
        u8* value = depth;

        for (s32 i = 0; i < 0x100; i++)
        {
            u32 depth_value = value[0] | (value[1] << 8) | (value[2] << 16);

            value += 3;

            if (depth_value < threshold)
            {
                count++;
            }
        }

        break;
    }
    case GS_PSMZ16:
    case GS_PSMZ16S:
    {
        u16* value = (u16*)depth;

        for (s32 i = 0; i < 0x100; i++)
        {
            if (*value < threshold)
            {
                count++;
            }

            value++;
        }

        break;
    }
    }

    coverage = count * (1.0f / 256.0f);
}

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
    coverage = 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00421650__14LibClass1728E0FPvUifffffff);

/**
 * @brief Lay out the builder's rays: random angles kept apart (the spacing halves after ten failed tries) and two
 *        random lengths per segment, tracking the longest.
 * @param builder Builder whose rays to allocate and fill.
 */
extern "C" void func_00421D80(LibClass1728E0* builder)
{
    builder->rays = new (0) LibLightRay[builder->unk1c];

    s32 count = builder->unk1c;
    float spacing = HALF_PI;

    builder->max_length = 0.0f;

    for (s32 i = 0; i < count; i++)
    {
        float angle;
        s32 tries;

        for (;;)
        {
            for (tries = 0; tries < 10; tries++)
            {
                angle = PI * (2.0f * resident_random_fraction());

                s32 j;

                for (j = 0; j < i; j++)
                {
                    float delta = builder->rays[j].angle - angle;

                    if (delta > PI)
                    {
                        delta -= TWO_PI;
                    }

                    if (ee_abs(delta) < spacing)
                    {
                        break;
                    }
                }

                if (j == i)
                {
                    break;
                }
            }

            if (tries < 10)
            {
                break;
            }

            spacing *= 0.5f;
        }

        builder->rays[i].angle = angle - 0.5f * (builder->unk3c * builder->unk20);

        float first = builder->unk24 + (builder->unk28 - builder->unk24) * resident_random_fraction();
        float second = builder->unk2c + (builder->unk30 - builder->unk2c) * resident_random_fraction();
        s32 segments = builder->unk20;

        for (s32 k = 0; k < segments; k++)
        {
            builder->rays[i].first[k] = first + builder->unk34 * resident_random_fraction();
            builder->rays[i].second[k] = second + builder->unk38 * resident_random_fraction();

            if (builder->rays[i].first[k] > builder->max_length)
            {
                builder->max_length = builder->rays[i].first[k];
            }

            if (builder->rays[i].second[k] > builder->max_length)
            {
                builder->max_length = builder->rays[i].second[k];
            }
        }
    }
}

/** @brief Delete the buffer and destroy the builder. */
LibClass1728E0::~LibClass1728E0()
{
    delete rays;
}

/** @brief Construct the builder without a buffer. */
LibClass1728E0::LibClass1728E0() : rays(0)
{
}

/**
 * @brief Pack a screen position as a GS XY value in 12.4 fixed point.
 * @param x Horizontal position in pixels.
 * @param y Vertical position in pixels.
 * @return XY part of an XYZ2 value.
 */
static inline u64 lib_screen_xy(float x, float y)
{
    return (s64)(s32)(16.0f * x) | ((s64)(s32)(16.0f * y) << 16);
}

/**
 * @brief Write a ring: a fan filling the inner circle in the modulated color, then a strip out to the outer edge that
 *        fades to transparent. Nothing is written when the ring would leave the 4096-pixel drawing area.
 * @param cursor Where to write.
 * @param color Packed RGB color the ring's own color is modulated by.
 * @param x Centre x, in screen pixels.
 * @param y Centre y, in screen pixels.
 * @param scale Size scale.
 * @param angle Rotation in radians.
 * @param alpha Opacity scale.
 * @param scale_x Horizontal stretch.
 * @param scale_y Vertical stretch.
 * @return The cursor after the data.
 */
void* LibClass172900::func_00421650(void* cursor, u32 color, float x, float y, float scale, float angle, float alpha,
                                    float scale_x, float scale_y)
{
    float cosines[48];
    float sines[48];
    float px;
    float py;
    u64* out = static_cast<u64*>(cursor);
    float outer = scale * (width + inner_radius);

    if (x - outer < 0.0f)
    {
        return out;
    }

    if (!(x + outer <= 4095.0f))
    {
        return out;
    }

    if (y - outer < 0.0f)
    {
        return out;
    }

    if (!(y + outer <= 4095.0f))
    {
        return out;
    }

    float inner = inner_radius * scale;
    u32 opacity = (u32)(128.0f * (alpha * this->alpha));

    if (opacity > 0x80)
    {
        opacity = 0x80;
    }

    s32 count = segments + 1;

    if (count <= 0)
    {
        return out;
    }

    GsGifTag* tag = reinterpret_cast<GsGifTag*>(out);
    tag->tag = GIF_TAG_NREG(1) | 2;
    tag->registers = 0;
    tag->fields.register0 = GIF_REGISTER_AD;
    out[2] = 0x4D;
    out[3] = GS_REGISTER_PRIM;
    u32 red = (this->color & 0xFF) * (color & 0xFF) / 255;
    u32 green = ((this->color >> 8) & 0xFF) * ((color >> 8) & 0xFF) / 255;
    u32 blue = ((this->color >> 16) & 0xFF) * ((color >> 16) & 0xFF) / 255;

    if (red > 0xFF)
    {
        red = 0xFF;
    }

    if (green > 0xFF)
    {
        green = 0xFF;
    }

    if (blue > 0xFF)
    {
        blue = 0xFF;
    }

    out[4] = (opacity << 24) | ((blue << 16) | (red | (green << 8)));
    out[5] = GS_REGISTER_RGBAQ;
    tag = reinterpret_cast<GsGifTag*>(out + 6);
    tag->tag = GIF_TAG_NREG(1) | GIF_TAG_FLG_REGLIST | 1;
    tag->registers = 0;
    tag->fields.register0 = GIF_REGISTER_XYZ2;
    out[8] = lib_screen_xy(x, y);

    if (count <= 0)
    {
        count = 1;
    }

    tag = reinterpret_cast<GsGifTag*>(out + 10);
    tag->tag = GIF_TAG_NREG(1) | GIF_TAG_FLG_REGLIST | count;
    tag->registers = 0;
    tag->fields.register0 = GIF_REGISTER_XYZ2;
    out += 12;

    for (s32 i = 0; i < count; i++)
    {
        LibVector4 pair;

        lib_compute_sine_cosine_pair((1.5707964f + angle) + 6.2831855f * (float)i / (float)(count - 1), &pair);
        cosines[i] = pair.z * scale_x;
        sines[i] = pair.w * scale_y;
        px = x + inner * cosines[i];
        py = y + inner * sines[i];
        *out++ = lib_screen_xy(px, py);
    }

    if (count & 1)
    {
        out++;
    }

    tag = reinterpret_cast<GsGifTag*>(out);
    tag->tag = GIF_TAG_NREG(1) | 1;
    tag->registers = 0;
    tag->fields.register0 = GIF_REGISTER_AD;
    out[2] = 0x4C;
    out[3] = GS_REGISTER_PRIM;
    tag = reinterpret_cast<GsGifTag*>(out + 4);
    tag->tag = GIF_TAG_NREG(2) | GIF_TAG_FLG_REGLIST | (count * 2);
    tag->registers = 0;
    tag->fields.register0 = GIF_REGISTER_RGBAQ;
    tag->fields.register1 = GIF_REGISTER_XYZ2;
    out += 6;
    red = (this->color & 0xFF) * (color & 0xFF) / 255;
    green = ((this->color >> 8) & 0xFF) * ((color >> 8) & 0xFF) / 255;
    blue = ((this->color >> 16) & 0xFF) * ((color >> 16) & 0xFF) / 255;

    if (red > 0xFF)
    {
        red = 0xFF;
    }

    if (green > 0xFF)
    {
        green = 0xFF;
    }

    if (blue > 0xFF)
    {
        blue = 0xFF;
    }

    u32 edge = (blue << 16) | (red | (green << 8));
    u32 centre = edge | (opacity << 24);

    for (s32 i = 0; i < count; i++)
    {
        px = x + inner * cosines[i];
        py = y + inner * sines[i];
        out[0] = centre;
        out[1] = lib_screen_xy(px, py);
        out[2] = edge;
        out[3] = lib_screen_xy(x + outer * cosines[i], y + outer * sines[i]);
        out += 4;
    }

    return out;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00421650__14LibClass172920FPvUifffffff);

/**
 * @brief Write a banded ring: a fan filling the inner circle, a solid band out to the middle radius, then a band out
 *        to the outer edge that fades to the last color. The segment count follows the ring's size. Nothing is written
 *        when the ring would leave the 4096-pixel drawing area.
 * @param cursor Where to write.
 * @param color Packed RGB color the ring's centre, rim and outer colors are modulated by.
 * @param x Centre x, in screen pixels.
 * @param y Centre y, in screen pixels.
 * @param scale Size scale.
 * @param angle Rotation in radians.
 * @param alpha Opacity scale.
 * @param scale_x Horizontal stretch.
 * @param scale_y Vertical stretch.
 * @return The cursor after the data.
 */
void* LibClass172940::func_00421650(void* cursor, u32 color, float x, float y, float scale, float angle, float alpha,
                                    float scale_x, float scale_y)
{
    float cosines[48];
    float sines[48];
    float px;
    float py;
    u64* out = static_cast<u64*>(cursor);
    float outer = scale * (inner_radius + (widths[1] + widths[0]));

    if (x - outer < 0.0f)
    {
        return out;
    }

    if (!(x + outer <= 4095.0f))
    {
        return out;
    }

    if (y - outer < 0.0f)
    {
        return out;
    }

    if (!(y + outer <= 4095.0f))
    {
        return out;
    }

    float middle = scale * (widths[0] + inner_radius);
    float inner = inner_radius * scale;
    u32 opacity = (u32)(128.0f * (alpha * this->alpha));

    if (opacity > 0x80)
    {
        opacity = 0x80;
    }

    s32 count = (s32)(0.2f * middle) + 9;

    if (count > 0x30)
    {
        count = 0x30;
    }

    if (count <= 0)
    {
        return out;
    }

    GsGifTag* tag = reinterpret_cast<GsGifTag*>(out);
    tag->tag = GIF_TAG_NREG(1) | 2;
    tag->registers = 0;
    tag->fields.register0 = GIF_REGISTER_AD;
    out[2] = 0x4D;
    out[3] = GS_REGISTER_PRIM;
    u32 red = (colors[0] & 0xFF) * (color & 0xFF) / 255;
    u32 green = ((colors[0] >> 8) & 0xFF) * ((color >> 8) & 0xFF) / 255;
    u32 blue = ((colors[0] >> 16) & 0xFF) * ((color >> 16) & 0xFF) / 255;

    if (red > 0xFF)
    {
        red = 0xFF;
    }

    if (green > 0xFF)
    {
        green = 0xFF;
    }

    if (blue > 0xFF)
    {
        blue = 0xFF;
    }

    u32 alpha_bits = opacity << 24;
    out[4] = alpha_bits | ((blue << 16) | (red | (green << 8)));
    out[5] = GS_REGISTER_RGBAQ;
    tag = reinterpret_cast<GsGifTag*>(out + 6);
    tag->tag = GIF_TAG_NREG(1) | GIF_TAG_FLG_REGLIST | 1;
    tag->registers = 0;
    tag->fields.register0 = GIF_REGISTER_XYZ2;
    out[8] = lib_screen_xy(x, y);
    tag = reinterpret_cast<GsGifTag*>(out + 10);
    tag->tag = GIF_TAG_NREG(1) | 1;
    tag->registers = 0;
    tag->fields.register0 = GIF_REGISTER_AD;
    red = (colors[1] & 0xFF) * (color & 0xFF) / 255;
    green = ((colors[1] >> 8) & 0xFF) * ((color >> 8) & 0xFF) / 255;
    blue = ((colors[1] >> 16) & 0xFF) * ((color >> 16) & 0xFF) / 255;

    if (red > 0xFF)
    {
        red = 0xFF;
    }

    if (green > 0xFF)
    {
        green = 0xFF;
    }

    if (blue > 0xFF)
    {
        blue = 0xFF;
    }

    out[12] = alpha_bits | ((blue << 16) | (red | (green << 8)));
    out[13] = GS_REGISTER_RGBAQ;

    if (count <= 0)
    {
        count = 1;
    }

    tag = reinterpret_cast<GsGifTag*>(out + 14);
    tag->tag = GIF_TAG_NREG(1) | GIF_TAG_FLG_REGLIST | count;
    tag->registers = 0;
    tag->fields.register0 = GIF_REGISTER_XYZ2;
    out += 16;

    for (s32 i = 0; i < count; i++)
    {
        LibVector4 pair;

        lib_compute_sine_cosine_pair(angle + 6.2831855f * (float)i / (float)(count - 1), &pair);
        cosines[i] = pair.z * scale_x;
        sines[i] = pair.w * scale_y;
        px = x + inner * cosines[i];
        py = y + inner * sines[i];
        *out++ = lib_screen_xy(px, py);
    }

    if (count & 1)
    {
        out++;
    }

    tag = reinterpret_cast<GsGifTag*>(out);
    tag->tag = GIF_TAG_NREG(1) | 1;
    tag->registers = 0;
    tag->fields.register0 = GIF_REGISTER_AD;
    out[2] = 0x4C;
    out[3] = GS_REGISTER_PRIM;
    tag = reinterpret_cast<GsGifTag*>(out + 4);
    tag->tag = GIF_TAG_NREG(2) | GIF_TAG_FLG_REGLIST | (count * 2);
    tag->registers = 0;
    tag->fields.register0 = GIF_REGISTER_RGBAQ;
    tag->fields.register1 = GIF_REGISTER_XYZ2;
    out += 6;

    for (s32 i = 0; i < count; i++)
    {
        px = x + inner * cosines[i];
        py = y + inner * sines[i];
        out[0] = colors[1] | alpha_bits;
        out[1] = lib_screen_xy(px, py);
        out[2] = colors[2] | alpha_bits;
        out[3] = lib_screen_xy(x + middle * cosines[i], y + middle * sines[i]);
        out += 4;
    }

    tag = reinterpret_cast<GsGifTag*>(out);
    tag->tag = GIF_TAG_NREG(1) | 1;
    tag->registers = 0;
    tag->fields.register0 = GIF_REGISTER_AD;
    out[2] = 0x4C;
    out[3] = GS_REGISTER_PRIM;
    tag = reinterpret_cast<GsGifTag*>(out + 4);
    tag->tag = GIF_TAG_NREG(2) | GIF_TAG_FLG_REGLIST | (count * 2);
    tag->registers = 0;
    tag->fields.register0 = GIF_REGISTER_RGBAQ;
    tag->fields.register1 = GIF_REGISTER_XYZ2;
    out += 6;
    red = (colors[2] & 0xFF) * (color & 0xFF) / 255;
    green = ((colors[2] >> 8) & 0xFF) * ((color >> 8) & 0xFF) / 255;
    blue = ((colors[2] >> 16) & 0xFF) * ((color >> 16) & 0xFF) / 255;

    if (red > 0xFF)
    {
        red = 0xFF;
    }

    if (green > 0xFF)
    {
        green = 0xFF;
    }

    if (blue > 0xFF)
    {
        blue = 0xFF;
    }

    u32 centre = alpha_bits | ((blue << 16) | (red | (green << 8)));
    u32 rim_red = (colors[3] & 0xFF) * (color & 0xFF) / 255;
    u32 rim_green = ((colors[3] >> 8) & 0xFF) * ((color >> 8) & 0xFF) / 255;
    u32 rim_blue = ((colors[3] >> 16) & 0xFF) * ((color >> 16) & 0xFF) / 255;

    if (rim_red > 0xFF)
    {
        rim_red = 0xFF;
    }

    if (rim_green > 0xFF)
    {
        rim_green = 0xFF;
    }

    if (rim_blue > 0xFF)
    {
        rim_blue = 0xFF;
    }

    u32 edge = (rim_blue << 16) | (rim_red | (rim_green << 8));

    for (s32 i = 0; i < count; i++)
    {
        px = x + middle * cosines[i];
        py = y + middle * sines[i];
        out[0] = centre;
        out[1] = lib_screen_xy(px, py);
        out[2] = edge;
        out[3] = lib_screen_xy(x + outer * cosines[i], y + outer * sines[i]);
        out += 4;
    }

    return out;
}

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
    resident_dma_queue_push(g_vif1_dma_queue, this);
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
    return segments / 2 + segments * 2 + 9;
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

/** Partial particle a field acts on: the masks of the fields that skip it. */
struct LibFieldTarget
{
    u8 unk00[0x1C];
    u32 skip_mask;
};

/**
 * @brief Push a particle away from the field's centre (round it in x/z when unk228 is negative) by a random amount
 *        between unk220 and unk220 + unk224, falling off with distance past unk228, unless the particle's mask skips
 *        this field.
 * @param position Particle position.
 * @param unk Unused.
 * @param output Receives the push.
 * @param source Particle.
 */
void LibClass172B40::func_00428500(const LibVector4* position, const void* unk, LibVector4* output, const void* source)
{
    u32 skip = static_cast<const LibFieldTarget*>(source)->skip_mask;

    if (unk210 & skip)
    {
        *(unsigned __int128*)output = 0;
        return;
    }

    float falloff = unk228;
    bool swirl;

    if (falloff < 0.0f)
    {
        swirl = true;
        falloff = -falloff;
    }
    else
    {
        swirl = false;
    }

    vu0_field_load_points(position, &this->position);
    vu0_set_vf12(falloff);

    if (swirl)
    {
        vu0_field_swirl_start();
        vu0_field_swirl_finish();
    }
    else
    {
        vu0_field_offset();
    }

    vu0_field_falloff();
    vu0_set_vf13_x(unk220 + unk224 * lib_light_random_fraction());
    vu0_field_store_push(output);
}

/**
 * @brief Push a particle along the field's direction by a random amount between unk270 and unk270 + unk274,
 *        falling off with its squared distance from the field (unk27c squared halves it), while it is within unk278
 *        of the field's axis, unless the particle's mask skips this field.
 * @param position Particle position.
 * @param unk Unused.
 * @param output Receives the push.
 * @param source Particle.
 */
void LibClass172C60::func_00428500(const LibVector4* position, const void* unk, LibVector4* output, const void* source)
{
    u32 skip = static_cast<const LibFieldTarget*>(source)->skip_mask;

    if (unk210 & skip)
    {
        *(unsigned __int128*)output = 0;
        return;
    }

    LibVector4 local;
    LibVector4 flat;
    LibVector4 radial;
    LibVector4 distance;

    vu0_field_to_local(position, &inverse, &local);
    copy_vector(&flat, &local);
    flat.y = 0.0f;
    vu0_field_length_squared(&flat, &radial);

    float radial_squared = radial.x;

    if (!(radial_squared <= unk278 * unk278))
    {
        *(unsigned __int128*)output = 0;
        return;
    }

    vu0_field_length_squared(&local, &distance);
    float distance_squared = distance.x;
    float spread = unk27c * unk27c;
    float falloff = spread / (spread + distance_squared);
    float amount = falloff * (unk270 + unk274 * lib_light_random_fraction());
    output->x = down.x * amount;
    output->y = down.y * amount;
    output->z = down.z * amount;
}

/**
 * @brief Push along the field's direction by a random amount between unk220 and unk220 + unk224, unless the
 * particle's mask skips this field.
 * @param position Particle position; unused.
 * @param unk Unused.
 * @param output Receives the push.
 * @param source Particle.
 */
void LibClass172CF0::func_00428500(const LibVector4* position, const void* unk, LibVector4* output, const void* source)
{
    u32 skip = static_cast<const LibFieldTarget*>(source)->skip_mask;

    if (unk210_mask & skip)
    {
        *(unsigned __int128*)output = 0;
        return;
    }

    float scale = unk220 + unk224 * lib_light_random_fraction();
    output->x = down.x * scale;
    output->y = down.y * scale;
    output->z = down.z * scale;
}

/**
 * @brief Keep a sphere above the shape's plane while it is over the shape's rectangle.
 * @param centre Sphere centre, in world space.
 * @param output Receives the corrected centre.
 * @param radius Sphere radius.
 * @return Whether the sphere touches the plane inside the rectangle; the centre is moved out of the plane either way.
 */
bool LibClass172D80::func_00425870(const LibVector4* centre, LibVector4* output, float radius)
{
    LibVector4 distance;
    LibVector4 local;

    vu0_shape_load_plane(centre, &position, &down);
    vu0_shape_set_radius(radius);
    vu0_shape_plane_distance(&distance);

    if (distance.x <= 0.0f)
    {
        vu0_shape_push_out(output);
        vu0_apply_matrix(&inverse_transform, centre, &local);

        if (!(local.x - radius < -extent_x) && local.x + radius <= extent_x && !(local.z - radius < -extent_z) &&
            local.z + radius <= extent_z)
        {
            return true;
        }
    }

    return false;
}

/**
 * @brief Keep a sphere on the outside of the box, worked out in the box's local space.
 * @param centre Sphere centre, in world space.
 * @param output Receives the corrected centre.
 * @param radius Sphere radius.
 * @return Whether the centre was moved.
 */
bool LibClass172E10::func_00425870(const LibVector4* centre, LibVector4* output, float radius)
{
    LibVector4 local;

    vu0_apply_matrix(&inverse_transform, centre, &local);
    copy_vector(output, &local);
    bool moved = false;

    if (local.x - radius < -extent.x)
    {
        output->x = -extent.x + radius;
        moved = true;
    }
    else if (!(local.x + radius <= extent.x))
    {
        output->x = extent.x - radius;
        moved = true;
    }

    if (local.y - radius < -extent.y)
    {
        output->y = -extent.y + radius;
        moved = true;
    }
    else if (!(local.y + radius <= extent.y))
    {
        output->y = extent.y - radius;
        moved = true;
    }

    if (local.z - radius < -extent.z)
    {
        output->z = -extent.z + radius;
        moved = true;
    }
    else if (!(local.z + radius <= extent.z))
    {
        output->z = extent.z - radius;
        moved = true;
    }

    if (moved)
    {
        vu0_apply_matrix(&transposed_transform, output, output);
    }

    return moved;
}

/**
 * @brief Keep a sphere on the outside of the shape's plane.
 * @param centre Sphere centre, in world space.
 * @param output Receives the corrected centre.
 * @param radius Sphere radius.
 * @return Whether the centre was moved.
 */
bool LibClass172EA0::func_00425870(const LibVector4* centre, LibVector4* output, float radius)
{
    LibVector4 distance;

    vu0_shape_load_plane(centre, &position, &down);
    vu0_shape_set_radius(radius);
    vu0_shape_plane_distance(&distance);

    if (distance.x <= 0.0f)
    {
        vu0_shape_push_out(output);
        return true;
    }

    return false;
}

/**
 * @brief Pull a link's two nodes together along a direction, splitting the move by weight unless one end is fixed.
 * @param node First node.
 * @param link Link from the first node to the second.
 * @param direction Aligned correction direction.
 * @param weight Share of the move the second node takes.
 * @param amount Length of the correction.
 */
extern "C" void func_00425B40(LibClass173070* node, LibClass173070Link* link, const LibVector4* direction, float weight,
                              float amount)
{
    vu0_load_vf2(&D_00507F50);
    vu0_shape_set_parameter(amount);
    vu0_set_vf7(weight);
    vu0_load_vf1(direction);
    LibClass173070* target = link->target;
    vu0_link_scale_vf3();

    if (node->fixed == 1 && target->fixed == 1)
    {
        return;
    }

    vu0_link_correction();

    if (node->fixed == 0 && target->fixed == 0)
    {
        LibVector4* first = &node->position;
        LibVector4* second = &target->position;
        vu0_link_move_pair(first, second);
        vu0_store_vf6(second);
        return;
    }

    if (node->fixed == 1)
    {
        vu0_load_vf5(&target->position);

        if (weight < 0.01f)
        {
            vu0_link_accumulate_vf5();
            vu0_link_add_scaled_z();
        }
        else
        {
            vu0_link_start_reciprocal();
            vu0_link_accumulate_vf5();
            vu0_link_add_divided();
        }

        vu0_store_vf5(&target->position);
    }
    else
    {
        vu0_load_vf5(&node->position);

        if (!(weight <= 0.99f))
        {
            vu0_link_accumulate_vf5();
            vu0_link_add_scaled_z();
        }
        else
        {
            vu0_link_start_reciprocal();
            vu0_link_accumulate_vf5();
            vu0_link_add_divided();
        }

        vu0_store_vf5(&node->position);
    }
}

/**
 * @brief Find the squared distance from a point to a segment and the fraction along it of the closest point.
 * @param segment Aligned segment: start, then axis.
 * @param point Aligned point.
 * @param fraction Receives the fraction along the axis.
 * @return The squared distance.
 */
extern "C" float func_004CA180(const LibVector4* segment, const LibVector4* point, float* fraction);

/**
 * @brief Find the squared distance between two segments and the fractions along them of the closest points.
 * @param first Aligned first segment: start, then axis.
 * @param second Aligned second segment: start, then axis.
 * @param first_fraction Receives the fraction along the first segment.
 * @param second_fraction Receives the fraction along the second segment.
 * @return The squared distance.
 */
extern "C" float func_004CA270(const LibVector4* first, const LibVector4* second, float* first_fraction,
                               float* second_fraction);

/**
 * @brief Test this sphere against a scaled capsule whose matrix the caller has loaded into vf24-vf27: bring the centre
 *        into the capsule's space, rescale it per axis for the capsule's scale, then test as with an unscaled one.
 * @param other Capsule (a LibClass172FC0).
 * @param scale Capsule's per-axis scale.
 * @param direction Receives the unit direction from this sphere to the capsule's closest point.
 * @param first Receives the fraction along the capsule's axis.
 * @param second Receives the overlap depth.
 * @return Nonzero when they touch.
 */
s32 LibClass172F30::func_004284F0(LibClass172AB0* other, const LibVector4* scale, LibVector4* direction, float* first,
                                  float* second)
{
    LibVector4 centre;
    float fraction;
    vu0_point_through_vf24(&position);
    vu0_scale_by_radii(static_cast<LibClass172FC0*>(other)->unk220, unk220, scale);
    vu0_store_vf1(&centre);
    float distance_squared = func_004CA180(&static_cast<LibClass172FC0*>(other)->local_point, &centre, &fraction);
    float other_radius = static_cast<LibClass172FC0*>(other)->unk220;
    float reach = unk220 + other_radius;

    if (distance_squared <= reach * reach)
    {
        const LibVector4* segment = &static_cast<LibClass172FC0*>(other)->local_point;
        const LibVector4* start = &static_cast<LibClass172FC0*>(other)->local_point;
        const LibVector4* point = &centre;
        vu0_segment_point_offset(start, segment + 1, fraction, point);
        *first = fraction;
        *second = reach - __sqrt(distance_squared, distance_squared);
        vu0_store_unit_offset(direction);
        return 1;
    }

    return 0;
}

/**
 * @brief Test this capsule against a scaled one whose matrix the caller has loaded into vf24-vf27: bring this
 *        capsule's segment into the other's space, rescale its start per axis for the other's scale, then test as
 *        with an unscaled one.
 * @param other Other capsule (a LibClass172FC0).
 * @param scale Other capsule's per-axis scale.
 * @param direction Receives the unit direction from this capsule's closest point to the other's.
 * @param first Receives the fraction along the other capsule's axis.
 * @param second Receives the overlap depth.
 * @return Nonzero when they touch.
 */
s32 LibClass172FC0::func_004284F0(LibClass172AB0* other, const LibVector4* scale, LibVector4* direction, float* first,
                                  float* second)
{
    LibVector4 segment[2];
    float own_fraction;
    float other_fraction;
    vu0_segment_through_vf24(&point);
    vu0_scale_by_radii(static_cast<LibClass172FC0*>(other)->unk220, unk220, scale);
    vu0_store_segment(segment);
    const LibVector4* other_capsule = &static_cast<LibClass172FC0*>(other)->local_point;
    float distance_squared = func_004CA270(segment, other_capsule, &own_fraction, &other_fraction);
    float other_radius = static_cast<LibClass172FC0*>(other)->unk220;
    float reach = unk220 + other_radius;

    if (distance_squared <= reach * reach)
    {
        const LibVector4* start = &segment[0];
        const LibVector4* direction_axis = &segment[1];
        const LibVector4* other_segment = &static_cast<LibClass172FC0*>(other)->local_point;
        const LibVector4* other_start = &static_cast<LibClass172FC0*>(other)->local_point;
        float fraction = own_fraction;
        vu0_segment_segment_offset(start, direction_axis, fraction, other_start, other_segment + 1, other_fraction);
        *first = other_fraction;
        *second = reach - __sqrt(distance_squared, distance_squared);
        vu0_store_unit_segment_offset(direction);
        return 1;
    }

    return 0;
}

/**
 * @brief Test this sphere against a capsule.
 * @param other Capsule (a LibClass172FC0).
 * @param direction Receives the unit direction from this sphere to the capsule's closest point.
 * @param first Receives the fraction along the capsule's axis.
 * @param second Receives the overlap depth.
 * @return Nonzero when they touch.
 */
s32 LibClass172F30::func_004284E0(LibClass172AB0* other, LibVector4* direction, float* first, float* second)
{
    float fraction;
    float distance_squared = func_004CA180(&static_cast<LibClass172FC0*>(other)->local_point, &position, &fraction);
    float other_radius = static_cast<LibClass172FC0*>(other)->unk220;
    float reach = unk220 + other_radius;

    if (distance_squared <= reach * reach)
    {
        const LibVector4* segment = &static_cast<LibClass172FC0*>(other)->local_point;
        const LibVector4* point = &position;
        vu0_segment_point_offset(segment, segment + 1, fraction, point);
        *first = fraction;
        *second = reach - __sqrt(distance_squared, distance_squared);
        vu0_store_unit_offset(direction);
        return 1;
    }

    return 0;
}

/**
 * @brief Test this capsule against another.
 * @param other Other capsule (a LibClass172FC0).
 * @param direction Receives the unit direction from this capsule's closest point to the other's.
 * @param first Receives the fraction along the other capsule's axis.
 * @param second Receives the overlap depth.
 * @return Nonzero when they touch.
 */
s32 LibClass172FC0::func_004284E0(LibClass172AB0* other, LibVector4* direction, float* first, float* second)
{
    float reach;
    float own_fraction;
    float other_fraction;
    float distance_squared;
    const LibVector4* other_segment = &static_cast<LibClass172FC0*>(other)->local_point;
    const LibVector4* own_segment = &point;
    distance_squared = func_004CA270(own_segment, other_segment, &own_fraction, &other_fraction);
    float other_radius = static_cast<LibClass172FC0*>(other)->unk220;
    reach = unk220 + other_radius;

    if (distance_squared <= reach * reach)
    {
        const LibVector4* start = &point;
        const LibVector4* direction_axis = &axis;
        const LibVector4* segment = &static_cast<LibClass172FC0*>(other)->local_point;
        float fraction = own_fraction;
        vu0_segment_segment_offset(start, direction_axis, fraction, segment, segment + 1, other_fraction);
        *first = other_fraction;
        *second = reach - __sqrt(distance_squared, distance_squared);
        vu0_store_unit_segment_offset(direction);
        return 1;
    }

    return 0;
}

/**
 * @brief Pull two linked nodes towards the link's rest length, a stiffness times the step of the way, sharing the
 *        move by the nodes' weights (all of it to the free one when the other is fixed).
 * @param node First node.
 * @param link Link between them.
 * @param other Second node.
 * @param step Time step.
 */
extern "C" void func_004261E0(LibClass173070* node, LibClass173070Link* link, LibClass173070* other, float step)
{
    LibVector4 length;

    vu0_link_load_ends(&other->position, &node->position);

    if (other->fixed == 1 && node->fixed == 1)
    {
        return;
    }

    vu0_link_span_vf20();
    vu0_link_ones_vf31();
    float weight = node->weight;
    vu0_link_square_vf20();
    float other_weight = other->weight;
    vu0_link_sum_start_vf21();
    vu0_link_sum_finish_vf21();

    if (node->fixed == 1)
    {
        other_weight = 0.0f;
        weight = 1.0f;
    }
    else if (other->fixed == 1)
    {
        weight = 0.0f;
        other_weight = 1.0f;
    }

    vu0_link_sqrt_vf22();
    bool weightless = weight == 0.0f && other_weight == 0.0f;
    vu0_link_length_vf24();
    vu0_store_vf24(&length);
    vu0_link_reciprocal_vf24();
    float current = length.x;
    float stretch = (current - link->rest_length) * (link->stiffness * step);
    vu0_link_wait_q();
    vu0_link_unit_vf24();

    if (weightless)
    {
        LibVector4* first = &node->position;
        LibVector4* second = &other->position;
        vu0_set_vf22(0.5f * stretch);
        vu0_link_accumulate_vf10();
        vu0_link_push_vf10_vf22();
        vu0_link_accumulate_vf11();
        vu0_link_pull_vf11_vf22();
        vu0_store_vf10(first);
        vu0_store_vf11(second);
    }
    else
    {
        LibVector4* first = &node->position;
        LibVector4* second = &other->position;
        float share = stretch / (weight + other_weight);
        float second_share = other_weight * share;
        float first_share = weight * share;
        vu0_set_vf22(second_share);
        vu0_set_vf23(first_share);
        vu0_link_accumulate_vf10();
        vu0_link_push_vf10_vf22();
        vu0_link_accumulate_vf11();
        vu0_link_pull_vf11_vf23();
        vu0_store_vf10(first);
        vu0_store_vf11(second);
    }
}

/**
 * @brief Pull two linked nodes all the way to the link's rest length, sharing the move by the nodes' weights (all of
 *        it to the free one when the other is fixed).
 * @param node First node.
 * @param link Link between them.
 * @param other Second node.
 */
extern "C" void func_00426370(LibClass173070* node, LibClass173070Link* link, LibClass173070* other)
{
    LibVector4 length;

    vu0_link_load_ends(&other->position, &node->position);

    if (other->fixed == 1 && node->fixed == 1)
    {
        return;
    }

    vu0_link_span_vf23();
    float weight = node->weight;
    vu0_link_square_vf23();
    vu0_link_ones_vf25();
    vu0_link_sum_start_vf24();
    vu0_link_sum_finish_vf24();
    float other_weight = other->weight;
    vu0_link_sqrt_vf24();

    if (node->fixed == 1)
    {
        other_weight = 0.0f;
        weight = 1.0f;
    }
    else if (other->fixed == 1)
    {
        weight = 0.0f;
        other_weight = 1.0f;
    }

    vu0_link_length_vf24();
    vu0_store_vf24(&length);
    vu0_link_reciprocal_vf24();
    bool weightless = weight == 0.0f && other_weight == 0.0f;
    float current = length.x;
    float stretch = current - link->rest_length;
    vu0_link_wait_q();
    vu0_link_unit_vf23();

    if (weightless)
    {
        LibVector4* first = &node->position;
        LibVector4* second = &other->position;
        vu0_set_vf13(0.5f * stretch);
        vu0_link_accumulate_vf10();
        vu0_link_push_vf10_vf13();
        vu0_link_accumulate_vf11();
        vu0_link_pull_vf11_vf13();
        vu0_store_vf10(first);
        vu0_store_vf11(second);
    }
    else
    {
        LibVector4* first = &node->position;
        LibVector4* second = &other->position;
        float share = stretch / (weight + other_weight);
        float second_share = other_weight * share;
        float first_share = weight * share;
        vu0_set_vf13(second_share);
        vu0_set_vf14(first_share);
        vu0_link_accumulate_vf10();
        vu0_link_push_vf10_vf13();
        vu0_link_accumulate_vf11();
        vu0_link_pull_vf11_vf14();
        vu0_store_vf10(first);
        vu0_store_vf11(second);
    }
}

/**
 * @brief Step a node: a fixed node follows its transform, a free one moves by its velocity plus gravity and a force
 *        and minus damping, as its flags ask.
 * @param node Node.
 * @param force Aligned force for LIB_LINK_NODE_FORCE.
 * @param step Time step.
 */
extern "C" void func_004264F0(LibClass173070* node, const LibVector4* force, float step)
{
    if (node->fixed == 1)
    {
        copy_vector(&node->previous_position, &node->position);
        node->transform->set_orientation(&node->orientation);
        LibTransform* transform = node->transform;
        transform->transform_dirty = 1;
        transform->matrix_ready = 0;
        transform->unk51 = 0;
        transform->update_transform_matrix();
        node->position.x = transform->base_transform.m[0][3];
        node->position.y = transform->base_transform.m[1][3];
        node->position.z = transform->base_transform.m[2][3];
        node->position.w = 1.0f;
        transform->transform_dirty = 1;
        transform->matrix_ready = 0;
        transform->unk51 = 0;
        return;
    }

    copy_vector(&node->previous_position, &node->position);
    vu0_link_step_start(&node->position, step, &D_00507F50, &node->velocity);

    if (node->flags & LIB_LINK_NODE_GRAVITY)
    {
        vu0_link_step_gravity();
    }

    if (node->flags & LIB_LINK_NODE_FORCE)
    {
        vu0_link_step_force(force);
    }

    if (node->flags & LIB_LINK_NODE_DAMPING)
    {
        vu0_link_step_damping(node->damping);
    }

    vu0_link_step_finish();
    node->transform->set_orientation(&node->orientation);
    vu0_store_vf16(&node->position);
}

/**
 * @brief Turn each linked parent so its child's position points at the linked node, ease the nodes' orientations
 *        toward their stored targets, move every free node's transform to its simulated position, then read the
 *        positions back from the updated transforms.
 * @param owner Link system.
 * @param rate Rate the orientation easing is scaled by.
 */
extern "C" void func_00426650(LibClass173050* owner, float rate)
{
    LibVector4 position;
    LibMatrix44Value inverse;
    LibVector4 dot;
    FieldVec4B rotation;
    FieldVec4B eased;
    FieldVec4B swung;

    vu0_set_vf29(0.5f);
    s32 count = owner->node_count;
    LibClass173070* nodes = owner->unk24;

    for (s32 i = 0; i < count; i++)
    {
        LibClass173070* node = &nodes[i];
        s32 links = node->link_count;

        for (s32 j = 0; j < links; j++)
        {
            LibClass173070Link* link = &node->links[j];

            if (link->blocked)
            {
                continue;
            }

            LibTransform* parent = node->transform;
            LibTransform* child = link->target->transform;

            if (parent != child->parent_transform)
            {
                continue;
            }

            if (node->flags & 0x20)
            {
                parent->set_orientation((const LibVector4*)&node->unk70[0]);
            }

            child->update_transform_matrix();
            func_004CEFD0(lib_get_parent_matrix(child), &inverse);
            position.x = matrix_row(&child->base_transform, 0)->w;
            position.y = matrix_row(&child->base_transform, 1)->w;
            position.z = matrix_row(&child->base_transform, 2)->w;
            position.w = 1.0f;
            ee_transpose_matrix(&inverse, &inverse);
            vu0_direction_pair_begin(&inverse, &position, &link->target->position);
            float limit = 0.99999988f;
            vu0_direction_pair_dot_cross_half();
            vu0_direction_pair_store_dot_half(&dot);

            if (dot.x < limit)
            {
                vu0_direction_pair_start_half_angle();
                vu0_direction_pair_store_rotation(&rotation);
                vu0_quaternion_premultiply_assign(&rotation, (const FieldVec4B*)&parent->orientation);
                parent->copy_orientation((const LibVector4*)&rotation);
            }

            if (node->flags & 0x4)
            {
                LibTransform* transform = node->transform;
                float amount = node->unk10 * rate;
                amount = ee_min(amount, 1.0f);
                const FieldVec4B* from = (const FieldVec4B*)&transform->orientation;
                lib_quaternion_slerp_async(&eased, from, (const FieldVec4B*)&node->unk70[0], amount);
                transform->set_orientation((const LibVector4*)&eased);
            }

            if (!(owner->unk20 <= 1e-6f))
            {
                float amount = owner->unk20 * node->unk20;

                if (!(amount <= 1e-6f))
                {
                    LibTransform* transform = node->transform;
                    float fraction = amount * rate;
                    fraction = ee_min(fraction, 1.0f);
                    const FieldVec4B* from = (const FieldVec4B*)&transform->orientation;
                    lib_quaternion_slerp_async(&swung, from, (const FieldVec4B*)&node->unk70[0x10], fraction);
                    transform->set_orientation((const LibVector4*)&swung);
                }
            }

            parent->transform_dirty = 1;
            parent->matrix_ready = 0;
            parent->unk51 = 0;
            child->transform_dirty = 1;
            child->matrix_ready = 0;
            child->unk51 = 0;
        }
    }

    for (s32 i = 0; i < count; i++)
    {
        LibClass173070* node = &nodes[i];

        if (node->unk03 || node->fixed)
        {
            continue;
        }

        if (node->transform->parent_transform)
        {
            LibMatrix44Value world_inverse;
            LibVector4 local;
            func_004CEFD0(node->transform->parent_transform->get_transform_matrix(), &world_inverse);
            vu0_dot_matrix_rows(&world_inverse, &node->position, &local);
            node->transform->set_translation_vector(&local);
        }
        else
        {
            node->transform->set_translation_vector(&node->position);
        }
    }

    for (s32 i = 0; i < count; i++)
    {
        LibClass173070* node = &nodes[i];
        node->unk1c = 0;

        if (node->fixed)
        {
            continue;
        }

        LibTransform* transform = node->transform;
        transform->update_transform_matrix();
        node->position.x = transform->base_transform.m[0][3];
        node->position.y = transform->base_transform.m[1][3];
        node->position.z = transform->base_transform.m[2][3];
        node->position.w = 1.0f;
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", update__14LibClass173050Fv);

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

/**
 * @brief Give a group number to every node reachable over unblocked links whose target's transform hangs off the
 * node's own transform, stopping at a link between two nodes that are both grouped already.
 * @param owner Node owner, passed on.
 * @param node Node to spread from.
 * @param group Group number.
 * @return Whether any node was grouped.
 */
extern "C" bool func_00428570(LibClass173050* owner, LibClass173070* node, s32 group)
{
    bool grouped = false;
    s32 count = node->link_count;

    for (s32 i = 0; i < count; i++)
    {
        LibClass173070Link* link = &node->links[i];

        if (node->group != 0xFF && link->target->group != 0xFF)
        {
            return grouped;
        }

        if (link->target->transform->parent_transform == node->transform && !link->blocked)
        {
            node->group = group;
            link->target->group = group;
            func_00428570(owner, link->target, group);
            grouped = true;
        }
    }

    return grouped;
}

/**
 * @brief Set the links up from the nodes' current transforms: each node starts at its transform's position at rest
 *        with its orientation copied, each link's rest length becomes the current distance, the nodes are grouped
 *        along their links, and the group buffer is reallocated for the group count.
 * @param owner Link system.
 */
extern "C" void func_00428670(LibClass173050* owner)
{
    s32 count = owner->node_count;

    for (s32 i = 0; i < count; i++)
    {
        LibClass173070* node = &owner->unk24[i];
        LibTransform* transform = node->transform;

        if (!transform->matrix_ready)
        {
            transform->update_transform_matrix();
        }

        node->position.x = transform->base_transform.m[0][3];
        node->position.y = transform->base_transform.m[1][3];
        node->position.z = transform->base_transform.m[2][3];
        node->position.w = 1.0f;
        copy_vector(&node->previous_position, &node->position);
        copy_vector(&node->orientation, &transform->orientation);
        copy_vector((LibVector4*)&node->unk70[0], &transform->orientation);
        copy_vector((LibVector4*)&node->unk70[0x10], &transform->orientation);
        *(unsigned __int128*)&node->velocity = 0;
        owner->unk24[i].group = 0xFF;
    }

    for (s32 i = 0; i < count; i++)
    {
        LibClass173070* node = &owner->unk24[i];
        s32 links = node->link_count;

        for (s32 j = 0; j < links; j++)
        {
            LibClass173070Link* link = &node->links[j];
            LibVector4 distance;
            vu0_link_distance(&node->position, &link->target->position, &distance);
            link->rest_length = distance.x;
        }
    }

    s32 groups = 0;

    for (s32 i = 0; i < count; i++)
    {
        if (func_00428570(owner, &owner->unk24[i], groups))
        {
            groups++;
        }
    }

    for (s32 i = 0; i < count; i++)
    {
        LibClass173070* node = &owner->unk24[i];

        if (node->group == 0xFF)
        {
            node->group = 0;
        }
    }

    delete[] owner->unk2c;
    owner->group_count = groups;
    owner->unk2c = new (0) u8[owner->group_count];
}

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

/**
 * @brief Add an object to the second retained set, reusing a free slot first.
 * @param object Object to retain.
 * @param kind Kind byte stored with it.
 */
extern "C" void func_00428A50(LibListObject* object, u8 kind)
{
    s32 i;

    for (i = 0; i < D_001B6514; i++)
    {
        if (D_00507E50[i] == 0)
        {
            D_00507E50[i] = object;
            D_00507E10[i] = kind;
            return;
        }
    }

    if (D_001B6514 < 64)
    {
        D_00507E10[D_001B6514] = kind;
        D_00507E50[D_001B6514] = object;
        D_001B6514++;
    }
}

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

/**
 * @brief Add an object to the first retained set, reusing a free slot first.
 * @param object Object to retain.
 * @param kind Kind byte stored with it.
 */
extern "C" void func_00428D20(LibListObject* object, u8 kind)
{
    s32 i;

    for (i = 0; i < D_001B650C; i++)
    {
        if (D_00507CD0[i] == 0)
        {
            D_00507CD0[i] = object;
            D_00507DD0[i] = kind;
            return;
        }
    }

    if (D_001B650C < 64)
    {
        D_00507DD0[D_001B650C] = kind;
        D_00507CD0[D_001B650C] = object;
        D_001B650C++;
    }
}

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


/** @brief Destroy the array and release both buffers. */
LibClass173050::~LibClass173050()
{
    delete[] unk24;
    delete[] unk28;
    delete[] unk2c;
}

/** @brief Release the buffer's allocation. */
LibClass173070::~LibClass173070()
{
    if (links)
    {
        ::operator delete[](reinterpret_cast<u8*>(links) - 0x10);
    }
}

/**
 * @brief Return the list kind.
 * @return Five.
 */
s32 LibClass173050::get_default_list_kind()
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
bool LibPooledQuaternionTrack::append_key(const void* value, const void* first, const void* second, float key)
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
bool LibPooledQuaternionTrack::replace_key(s32 index, float key, const void* value, const void* first, const void* second)
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
