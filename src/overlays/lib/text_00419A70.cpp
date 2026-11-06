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


typedef struct WordSetterOwnertext_00419A70
{
    u8 unk00[0x70];
    u32 unk70;
} WordSetterOwnertext_00419A70;



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

/** Partial receiver view with an observed byte at offset 0x60. */
typedef struct LibReceiverByte60
{
    u8 unk00[0x60];
    u8 unk60;
} LibReceiverByte60;

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00419BE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00419C70);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041A1A0);

/**
 * @brief Stop the movie and its stream.
 * @param player Movie player.
 */
void lib_movie_stop(LibMoviePlayer* player)
{
    player->stopped = 1;
    player->is_playing = 0;
    func_0011C8E0(g_resource_archive);
    func_0011C6B0(g_resource_archive);
    g_resource_queue->unk2c = 0;
    func_00414490(&player->stream);
    player->stopped = 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041A290);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041A2F0);

void func_0041A530(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041A540);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041A550);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041ACF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041AD10);

void func_0041AD80(void* object)
{
    ((LibReceiverByte60*)object)->unk60 = 7;
}

/** Build a four-word stack value and return its address. */
void* func_0041AD90(void)
{
    s32 stack[4];
    stack[0] = 0;
    stack[3] = 0x7149F2CA;
    stack[1] = 0;
    s32* result = stack;
    stack[2] = 0;
    return result;
}

/** @brief Clear the intrusive owner and call the transform release hook. */
extern "C" void func_0041ADC0(LibTransformOwner* object)
{
    object->owner = 0;
    object->LibTransformOwner::destroy();
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041ADE0);

/** Forward the receiver to lib_finish_packet. */
void func_0041AE30(void* object)
{
    lib_finish_packet(static_cast<LibTransformOwner*>(object));
}

/** Queue the DMA submission embedded at offset 0x90 when present. */
s32 func_0041AE50(void* object)
{
    DmaSubmission* submission = reinterpret_cast<DmaSubmission*>(object);
    if (object != 0)
    {
        submission = (DmaSubmission*)((u8*)submission + 0x90);
    }
    return func_00114100(g_vif1_dma_queue, submission);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041AE80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041CF80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041D0A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041D1C0);

/** Forward the receiver to lib_finish_packet. */
void func_0041D210(void* object)
{
    lib_finish_packet(static_cast<LibTransformOwner*>(object));
}

/** Queue the DMA submission embedded at offset 0x90 when present. */
s32 func_0041D230(void* object)
{
    DmaSubmission* submission = reinterpret_cast<DmaSubmission*>(object);
    if (object != 0)
    {
        submission = (DmaSubmission*)((u8*)submission + 0x90);
    }
    return func_00114100(g_vif1_dma_queue, submission);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041D260);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041E640);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041E760);

void func_0041E880(u8* object)
{
    object[0x64] = 1;
    *(volatile u32*)0x10009020 = *(u32*)(object + 0x9C);
    *(volatile u32*)0x10009010 = *(u32*)(object + 0xA0);
    *(volatile u32*)0x1000E010 = 2;
    *(volatile u32*)0x10009000 = 0x101;
}

/** Forward the receiver to lib_finish_packet. */
void func_0041E8C0(void* object)
{
    lib_finish_packet(static_cast<LibTransformOwner*>(object));
}

/** Queue the DMA submission embedded at offset 0x90 when present. */
s32 func_0041E8E0(void* object)
{
    DmaSubmission* submission = reinterpret_cast<DmaSubmission*>(object);
    if (object != 0)
    {
        submission = (DmaSubmission*)((u8*)submission + 0x90);
    }
    return func_00114100(g_vif1_dma_queue, submission);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041E910);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041EF10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F030);

void func_0041F130(void* object)
{
    ((LibReceiverByte60*)object)->unk60 = 7;
}

/** Build a four-word stack value and return its address. */
void* func_0041F140(void)
{
    s32 stack[4];
    stack[0] = 0;
    stack[3] = 0x7149F2CA;
    stack[1] = 0;
    s32* result = stack;
    stack[2] = 0;
    return result;
}

/** @brief Clear the intrusive owner and call the transform release hook. */
extern "C" void func_0041F170(LibTransformOwner* object)
{
    object->owner = 0;
    object->LibTransformOwner::destroy();
}

void func_0041F190(void* object)
{
    ((LibReceiverByte60*)object)->unk60 = 7;
}

/** Build a four-word stack value and return its address. */
void* func_0041F1A0(void)
{
    s32 stack[4];
    stack[0] = 0;
    stack[3] = 0x7149F2CA;
    stack[1] = 0;
    s32* result = stack;
    stack[2] = 0;
    return result;
}

/** @brief Clear the intrusive owner and call the transform release hook. */
extern "C" void func_0041F1D0(LibTransformOwner* object)
{
    object->owner = 0;
    object->LibTransformOwner::destroy();
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F1F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F200);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F210);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F220);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F230);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F240);

void func_0041F250(void* object)
{
    ((LibReceiverByte60*)object)->unk60 = 7;
}

/** Build a four-word stack value and return its address. */
void* func_0041F260(void)
{
    s32 stack[4];
    stack[0] = 0;
    stack[3] = 0x7149F2CA;
    stack[1] = 0;
    s32* result = stack;
    stack[2] = 0;
    return result;
}

/** @brief Clear the intrusive owner and call the transform release hook. */
extern "C" void func_0041F290(LibTransformOwner* object)
{
    object->owner = 0;
    object->LibTransformOwner::destroy();
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F2B0);

/** Forward the receiver to lib_finish_packet. */
void func_0041F300(void* object)
{
    lib_finish_packet(static_cast<LibTransformOwner*>(object));
}

/** Queue the DMA submission embedded at offset 0x90 when present. */
s32 func_0041F320(void* object)
{
    DmaSubmission* submission = reinterpret_cast<DmaSubmission*>(object);
    if (object != 0)
    {
        submission = (DmaSubmission*)((u8*)submission + 0x90);
    }
    return func_00114100(g_vif1_dma_queue, submission);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F350);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004209C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00420A30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00420B50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00420D00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00420D10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00420D20);

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

s32 func_00421240(void* object)
{
    return 16;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00421250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00421450);

void func_004214C0(void* object, void* first, void* second)
{
    LibReceiverPointerPair14* state = (LibReceiverPointerPair14*)object;
    state->unk14 = first;
    state->unk18 = second;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004214D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00421590);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00421650);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00421D80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00422050);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004220E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00422130);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004221A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00422850);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00422F70);

void func_00423930(u8* object)
{
    object[0x64] = 1;
    *(volatile u32*)0x10009020 = *(u32*)(object + 0x234);
    *(volatile u32*)0x10009010 = *(u32*)(object + 0x238);
    *(volatile u32*)0x1000E010 = 2;
    *(volatile u32*)0x10009000 = 0x101;
}

/** Forward the receiver to lib_finish_packet. */
void func_00423970(void* object)
{
    lib_finish_packet(static_cast<LibTransformOwner*>(object));
}

/** Queue the DMA submission embedded at offset 0x210 when present. */
s32 func_00423990(void* object)
{
    DmaSubmission* submission = reinterpret_cast<DmaSubmission*>(object);
    if (object != 0)
    {
        submission = (DmaSubmission*)((u8*)submission + 0x210);
    }
    return func_00114100(g_vif1_dma_queue, submission);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004239C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424510);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004245B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424610);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424760);

/** @brief Destroy the list receiver and its embedded sentinel. */
LibListReceiver::~LibListReceiver()
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424860);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424890);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424910);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424940);

s32 func_004249C0(void* object)
{
    return 398;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004249D0);

s32 func_00424A50(void* object)
{
    return 230;
}

void func_00424A60(void* object)
{
    ((LibReceiverByte60*)object)->unk60 = 9;
}

/** Build a four-word stack value and return its address. */
void* func_00424A70(void)
{
    s32 stack[4];
    stack[0] = 0;
    stack[3] = 0x7149F2CA;
    stack[1] = 0;
    s32* result = stack;
    stack[2] = 0;
    return result;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424AA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424AB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424AC0);

s32 func_00424AD0(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424AE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424BE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424CE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424D30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424E50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424F40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425070);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425130);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425250);

void func_00425280(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425290);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004253A0);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428390);

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

s32 func_004284E0(void* object)
{
    return 0;
}

s32 func_004284F0(void* object)
{
    return 0;
}

void func_00428500(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428510);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428570);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428670);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004288C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004289B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428A50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428AF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428B40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428B90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428C80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428D20);

s32 func_00428DC0(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428DD0);

s32 func_00428E40(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428E50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428EB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428F20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428F90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004290A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004291B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004292C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004293D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00429480);

s32 func_004294F0(void* object)
{
    return 5;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00429500);

/** Store the word at receiver offset 0x70. */
void func_004295B0(void* object, u32 value)
{
    WordSetterOwnertext_00419A70* receiver = static_cast<WordSetterOwnertext_00419A70*>(object);
    receiver->unk70 = value;
}

void func_004295C0(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004295D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004295E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004295F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00429620);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00429650);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00429680);

void func_004296B0(void* unused, void* output)
{
    *(unsigned __int128*)output = 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004296C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00429730);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00429790);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00429860);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004299C0);
