#ifndef SO3_OVERLAYS_LIB_MOVIE_PLAYER_H
#define SO3_OVERLAYS_LIB_MOVIE_PLAYER_H

#include "types.h"
#include "overlays/lib/text_003E68C0.h"
#include "overlays/lib/text_004CD3A0.h"
#include "main/dma_queue.h"
#include "main/sound.h"
#include "main/thread.h"
#include "overlays/lib/semaphore.h"

#define LIB_MOVIE_THREAD_PRIORITY 44
#define LIB_MOVIE_THREAD_STACK_SIZE 0x4000

#define LIB_MOVIE_FRAME_COUNT 2

/** Values of LibMovieState::frame_states. */
enum
{
    LIB_MOVIE_FRAME_FREE = 0,
    LIB_MOVIE_FRAME_SHOWN = 1,
    LIB_MOVIE_FRAME_READY = 2
};

/**
 * Partial movie decoder state reached through the player, with two 64-byte-aligned frame buffers it decodes into in
 * turn. Its vtable pointer sits among its data at 0x80DC.
 */
struct LibMovieState
{
    /**
     * @brief Store the two scale words at offset 0x80C4.
     * @param first First scale.
     * @param second Second scale.
     */
    void set_scale(float first, float second)
    {
        unk80C4 = first;
        unk80C8 = second;
    }

    /**
     * @brief Store the three words at offset 0x80AC.
     * @param first First word.
     * @param second Second word.
     * @param third Third word.
     */
    void set_words(s32 first, s32 second, s32 third)
    {
        unk80AC = first;
        unk80B0 = second;
        unk80B4 = third;
    }

    /** @brief Start with no frame buffers, both frames free, and the default words and scale. */
    LibMovieState();

    u8 unk00[0x40];
    u8* allocations[LIB_MOVIE_FRAME_COUNT];
    u8* frames[LIB_MOVIE_FRAME_COUNT];
    u8 unk50[0x8040];
    u8 frame_states[LIB_MOVIE_FRAME_COUNT];
    u8 unk8092[2];
    s32 current;

    // TODO: Freeing shown frames reloads this after testing it, which only volatile gives me so far; it is shared
    // with the decode side, which updates it with interrupts disabled.

    volatile s32 ready_count;
    s32 frame_count;
    s32 width;
    s32 height;
    s32 unk80A8;
    s32 unk80AC;
    s32 unk80B0;
    s32 unk80B4;
    s32 unk80B8;
    s32 unk80BC;
    s32 current_frame;
    float unk80C4;
    float unk80C8;
    s32 unk80CC;
    s32 unk80D0;
    s32 unk80D4;
    u8 widescreen;

    /** @brief Free the frame buffers. */
    virtual ~LibMovieState();

    u8 unk80E0[0x20];
};

#define LIB_MOVIE_STREAM_BUFFER_SIZE 0x90000
#define LIB_MOVIE_STREAM_DATA_SIZE 0xA0000
#define LIB_MOVIE_STREAM_KIND_1 1

class LibMoviePlayer;
class LibMovieThread;

#define LIB_MOVIE_TIMESTAMP_CAPACITY 800

/** Timestamps of a stretch of stream data in the decoder's ring buffer. */
struct LibMovieTimeStamp
{
    s64 pts;
    s64 dts;
    s32 position;
    s32 length;
};

#define LIB_MOVIE_RING_SECTORS 400
#define LIB_MOVIE_SECTOR_SIZE 0x800

/** Byte ring the archive streams the movie file into, ahead of demultiplexing. */
struct LibMovieStreamBuffer
{
    u8 unk00[0x40];
    u8 data[LIB_MOVIE_STREAM_BUFFER_SIZE + 0x40];
    s32 position;
    s32 fill;
    s32 size;
};

/**
 * Ring buffer of MPEG stream data that DMA channel 4 feeds to the IPU, with the timestamps of what it holds. It is the
 * base of LibMovieDecoder; its vtable pointer follows its data at 0xCE4EC.
 */
class LibMovieRing
{
public:
    /** @brief Set up an empty ring, its DMA chain and its semaphore. */
    LibMovieRing();

    u8 unk00[0x40];
    u8 sectors[LIB_MOVIE_RING_SECTORS][LIB_MOVIE_SECTOR_SIZE];
    u64 tags[LIB_MOVIE_RING_SECTORS + 1][2];
    u8 unkC9950[0x40];
    s32 ring_sectors;
    s32 unkC9994;
    s32 unkC9998;
    s32 unkC999C;
    s32 ring_size;
    u32 saved_d4_madr;
    u32 saved_d4_tadr;
    u32 saved_d4_qwc;
    u32 saved_d4_chcr;
    u32 saved_d3_madr;
    u32 saved_d3_qwc;
    u32 saved_d3_chcr;
    s32 saved_ipu_bp;
    u32 saved_ipu_ctrl;
    LibSemaphore semaphore;
    s32 unkC99D0;
    u8 unkC99D4[4];
    s64 unkC99D8;
    LibMovieTimeStamp timestamps[LIB_MOVIE_TIMESTAMP_CAPACITY];
    s32 timestamp_capacity;
    s32 timestamp_count;
    s32 timestamp_write;

    /** @brief Stop DMA channel 4 and delete the semaphore. */
    virtual ~LibMovieRing();

    /**
     * @brief Add timestamps to the queue while holding the semaphore.
     * @param stamp Timestamps to add; the entry is skipped when both are negative.
     * @return 0 when the queue is full, otherwise 1.
     */
    virtual s32 push_timestamp(LibMovieTimeStamp* stamp);

    /**
     * @brief Round unkC999C up to a whole 0x800-byte sector while holding the semaphore.
     * @return Always 0.
     */
    virtual s32 end_stream();
};

/** MPEG decoder at offset 0xC0 of the player, with the stream buffer the archive reads into. */
class LibMovieDecoder : public LibMovieRing
{
public:
    /** @brief Initialize the decoder. */
    LibMovieDecoder();

    /** @brief Delete libmpeg's state, its work area and the decoder state. */
    virtual ~LibMovieDecoder();

    /**
     * @brief Write an MPEG sequence end code into the ring buffer once, then round the fill up to a sector.
     * @return 1 when the end code was written, 0 when it already was or there is no room.
     */
    virtual s32 end_stream();

    /**
     * @brief Queue the timestamps of stream data that just arrived in the ring buffer.
     * @param pts Presentation timestamp.
     * @param dts Decoding timestamp.
     * @param data Start of the data in the ring buffer.
     * @param length Length of the data.
     * @return 0 when the queue is full, otherwise 1.
     */
    virtual s32 add_timestamp(s64 pts, s64 dts, u8* data, s32 length);

    u8 unkCE4F0[0x10];
    u8 mpeg[0x48];
    u8* mpeg_work;
    u8 unkCE54C[0x34];
    LibMovieStreamBuffer input;
    u8 unk15E60C[0x34];
    LibMovieState* state;
    u8 unk15E644;
    u8 unk15E645;
    s32 stopped;
    s32 unk15E64C;
    u8 unk15E650[4];
    u8 unk15E654;
    s32 unk15E658;
    s32 width;
    s32 height;
    LibMovieThread* thread;
};

/** Partial 0x38-byte movie stream state with vtable D_172468 in main data; its data comes before the vptr. */
class LibMovieStream
{
public:
    LibMovieStreamBuffer* buffer;
    ResidentSound* sound;
    s32 unk08;
    u8* data;
    s32 position;
    s32 fill;
    s32 size;
    s32 total;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    LibMoviePlayer* player;
    u8 kind;
    u8 unk31;
    u8 unk32;
    u8 unk33;

    /** @brief Allocate the stream's data buffer and clear its state. */
    LibMovieStream();

    /** @brief Free the data buffer. */
    virtual ~LibMovieStream();

    /** @brief Clear the stream's read state for a new movie. */
    void reset();

    /** @brief Stop the sound stream, or restore the volume, if the stream started either. */
    void stop_sound();
};

/** Lib callback interface with one handler, vtable D_172590 in main data. */
class LibMovieListener
{
public:
    /**
     * @brief Handle a callback; the base class ignores it.
     * @param first First argument.
     * @param second Second argument.
     * @param third Third argument.
     * @param fourth Fourth argument.
     */
    virtual void handle(u32 first, u32 second, u32 third, u32 fourth);
};

/** Listener the archive calls while it streams a looping movie, vtable D_1725B8 in main data. */
class LibMovieLoopListener : public LibMovieListener
{
public:
    /**
     * @brief Handle a callback from the archive.
     * @param first First argument.
     * @param second Second argument.
     * @param third Third argument.
     * @param fourth Fourth argument.
     */
    virtual void handle(u32 first, u32 second, u32 third, u32 fourth);
};

/** 0x20-byte thread that feeds the decoder, vtable D_1725A0 in main data. */
class LibMovieThread : public ResidentThread
{
public:
    /** @brief Create the kernel thread. */
    LibMovieThread() : unk10(0)
    {
        resident_thread_create(this, LIB_MOVIE_THREAD_PRIORITY, LIB_MOVIE_THREAD_STACK_SIZE);
    }

    virtual ~LibMovieThread();

    /** @brief Run the decoder. */
    virtual void run();

    /**
     * @brief Set the decoder and stream the thread feeds.
     * @param target Decoder.
     * @param source Stream state.
     */
    void set_sources(LibMovieDecoder* target, LibMovieStream* source)
    {
        decoder = target;
        stream = source;
    }

    u32 unk10;
    LibMovieDecoder* decoder;
    LibMovieStream* stream;
    LibMoviePlayer* player;
};

/**
 * Partial 0x15E7C0-byte movie player with vtables D_172500 and D_172574 (the DMA submission) in main data: a
 * decoder, the streaming buffer and the playback state.
 */
class LibMoviePlayer : public LibTransformOwner, public DmaSubmission
{
public:
    /**
     * @brief Initialize the player and its decoder for a frame size.
     * @param width Frame width.
     * @param height Frame height.
     */
    LibMoviePlayer(s32 width, s32 height);

    /** @brief Destroy the player. */
    virtual ~LibMoviePlayer();

    /**
     * @brief Report the list kind used when registration requests the default.
     * @return The player's list kind.
     */
    virtual s32 get_default_list_kind();

    /** @brief Advance playback. */
    virtual void update();

    /** @brief Queue the player's frame packet for VIF1 DMA. */
    virtual void render();

    /** @brief Stop the movie if it's playing, then detach and queue the player. */
    virtual void destroy();

    /**
     * @brief Build the next frame's packet when the decoder has one ready.
     * @param matrix Matrix supplied by the caller; unused.
     * @param context Opaque caller context; unused.
     */
    virtual void build_packet(const void* matrix, void* context);

    /**
     * @brief Send the frame packet at unk15E7A4 on VIF1.
     * @param channel DMA channel; unused.
     */
    virtual void submit_dma(u32 channel);

    /**
     * @brief Release the shown frame and finish the packet.
     * @param channel DMA channel; unused.
     */
    virtual void complete_dma(u32 channel);

    u8 unk94[0x2C];
    LibMovieDecoder decoder;
    u8 unk15E728[0x18];
    LibMovieStream stream;
    LibMovieThread* thread;
    LibMovieLoopListener loop_listener;
    s32 movie;
    s32 unk15E784;
    u8 unk15E788[4];
    s16 width;
    s16 height;

    s32 unk15E790;
    u8 is_playing;
    u8 unk15E795;
    u8 unk15E796;
    u8 unk15E797;
    u8 unk15E798[0xC];
    s32 unk15E7A4;
    u8 unk15E7A8[0x18];
};

/** The movie player being played, set by its constructor. */
extern LibMoviePlayer* g_movie_player;

extern "C"
{
    /**
     * @brief Start playing a movie: select its resource and start streaming it, unless a movie is already playing.
     * @param player Movie player.
     * @param movie Resource to play.
     * @param loop Nonzero to let the archive restart the stream.
     * @return 1 once started, 0 while a movie plays or the resource queue is busy.
     */
    s32 lib_movie_play(LibMoviePlayer* player, s32 movie, s32 loop);

    /**
     * @brief Stop the movie and its stream.
     * @param player Movie player.
     */
    void lib_movie_stop(LibMoviePlayer* player);
}

#endif
