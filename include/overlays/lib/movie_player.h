#ifndef SO3_OVERLAYS_LIB_MOVIE_PLAYER_H
#define SO3_OVERLAYS_LIB_MOVIE_PLAYER_H

#include "types.h"
#include "overlays/lib/text_003E68C0.h"
#include "overlays/lib/text_004CD3A0.h"
#include "main/resident_0010A0E0.h"

/** Thread priority of the movie decoder thread. */
#define LIB_MOVIE_THREAD_PRIORITY 44

/** Stack size of the movie decoder thread, in bytes. */
#define LIB_MOVIE_THREAD_STACK_SIZE 0x4000

/** Partial movie decoder state reached through the player. */
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

    u8 unk00[0x80AC];
    s32 unk80AC;
    s32 unk80B0;
    s32 unk80B4;
    u8 unk80B8[8];

    /** Frame being shown. */
    s32 current_frame;

    float unk80C4;
    float unk80C8;
    u8 unk80CC[0xC];

    /** Nonzero to shape the picture for a 16:9 television: the decoder narrows it by about 0.89 and stretches it by about 1.15. */
    u8 widescreen;
};

/** Streaming buffer the archive reads a movie into. */
#define LIB_MOVIE_STREAM_BUFFER_SIZE 0x90000

class LibMoviePlayer;

/**
 * Partial MPEG decoder at offset 0xC0 of the player. Its constructor (0x416510) also sets up the player fields
 * after it, up to the stream at 0x15E740, so the real object is probably larger.
 */
class LibMovieDecoder
{
public:
    /** @brief Initialize the decoder. */
    LibMovieDecoder();

    u8 unk00[0xCE580];

    /** Buffer the stream state points at. */
    u8 unkCE580[0x40];
};

/** Partial 0x38-byte movie stream state with vtable D_172468 in main data; its data comes before the vptr. */
class LibMovieStream
{
public:
    u8* buffer;
    ResidentSound* sound;
    u8 unk08[0x24];
    LibMoviePlayer* player;
    u8 unk30[4];

    /** @brief Allocate the stream's ring buffer and clear its state. */
    LibMovieStream();

    /** @brief Destroy the stream. */
    virtual ~LibMovieStream();
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
        func_00115000(this, LIB_MOVIE_THREAD_PRIORITY, LIB_MOVIE_THREAD_STACK_SIZE);
    }

    /** @brief Destroy the thread. */
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

    /** @brief Queue the player's frame packet for VIF1 DMA. */
    virtual void render();

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

    /** Streaming buffer, with room to align it to 64 bytes. */
    u8 stream_buffer[LIB_MOVIE_STREAM_BUFFER_SIZE + 0x40];

    u8 unk15E6C0[0x40];
    LibMovieState* state;
    u8 unk15E704[4];

    /** Set once playback stops. */
    s32 stopped;

    u8 unk15E70C[0x18];
    LibMovieThread* unk15E724;
    u8 unk15E728[0x18];
    LibMovieStream stream;
    LibMovieThread* thread;

    /** What the archive points at while it streams the movie (when the movie loops). */
    LibMovieLoopListener loop_listener;

    /** Resource being played. */
    s32 movie;

    s32 unk15E784;
    u8 unk15E788[4];

    /** Frame size. */
    s16 width;
    s16 height;

    s32 unk15E790;

    /** Nonzero while the movie plays. */
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
