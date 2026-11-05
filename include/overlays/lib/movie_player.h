#ifndef SO3_OVERLAYS_LIB_MOVIE_PLAYER_H
#define SO3_OVERLAYS_LIB_MOVIE_PLAYER_H

#include "types.h"
#include "overlays/lib/text_003E68C0.h"

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
    u8 unk80D8;
};

/** Streaming buffer the archive reads a movie into. */
#define LIB_MOVIE_STREAM_BUFFER_SIZE 0x90000

/** Partial 0x15E7C0-byte movie player with vtable D_172500 in main data: a decoder, the streaming buffer and the playback state. */
class LibMoviePlayer : public LibListObject
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

    u8 unk14[0xAC];
    u8 decoder[0xCE5C0];

    /** Streaming buffer, with room to align it to 64 bytes. */
    u8 stream_buffer[LIB_MOVIE_STREAM_BUFFER_SIZE + 0x40];

    u8 unk15E6C0[0x40];
    LibMovieState* state;
    u8 unk15E704[4];

    /** Set once playback stops. */
    s32 stopped;

    u8 unk15E70C[0x34];
    u8 unk15E740[0x3C];

    /** What the archive points at while it streams the movie (when the movie loops). */
    u8 unk15E77C[4];

    /** Resource being played. */
    s32 movie;

    s32 unk15E784;
    u8 unk15E788[8];
    s32 unk15E790;

    /** Nonzero while the movie plays. */
    u8 is_playing;

    u8 unk15E795;
    u8 unk15E796[0xE];
    s32 unk15E7A4;
    u8 unk15E7A8[0x18];
};

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
