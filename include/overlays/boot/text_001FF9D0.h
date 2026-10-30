#ifndef SO3_OVERLAYS_BOOT_TEXT_001FF9D0_H
#define SO3_OVERLAYS_BOOT_TEXT_001FF9D0_H

#include "types.h"
#include "main/resident_0011EE70.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Run the Lib hook at 0x4D00B0 on an object.
 * @param object Object to pass.
 */
void func_4D00B0(void* object);

/**
 * @brief Allocate a packet's storage.
 * @param packet Packet to set up.
 * @param size Storage size in bytes.
 */
void func_11F8A0(ResidentPacket* packet, s32 size);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include "overlays/boot/text_001E0900.h"

class BootStringLabel;

/**
 * @brief Set a string label's rectangle and string.
 * @param object Label to set up.
 * @param text String to draw.
 * @param flag Drawing flag.
 * @param x Origin x.
 * @param y Origin y.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return Lib status.
 */
extern "C" s32 func_467AD0(BootStringLabel* object, const char* text, u8 flag, float x, float y, float width, float height);

/** GS packet buffer with vtable D_171BF0 in main data; its data comes before the vptr. */
class BootPacketBuffer : public ResidentPacket
{
    public:
        /**
         * @brief Allocate the packet's storage.
         * @param size Storage size in bytes.
         */
        BootPacketBuffer(s32 size)
        {
            unk04 = 0;
            unk15 = 0;
            func_11F8A0(this, size);
        }

        /** @brief Release the packet storage. */
        virtual ~BootPacketBuffer();
};

/** Fast Fourier transform with the bit-reversal and sine tables for its current size. */
class BootFft
{
    public:
        /** @brief Start with no tables. */
        BootFft()
        {
            size = 0;
            unk04 = 0;
            unk14 = 0;
            unk24 = 0;
            bit_reverse = 0;
            sine_table = 0;
            unk10 = 0;
            unk18 = 0;
            unk1c = 0;
            unk28 = 0;
            unk2c = 0;
        }

        /** @brief Release the tables. */
        ~BootFft()
        {
            delete bit_reverse;
            delete sine_table;
            delete unk10;
            delete unk18;
            delete unk1c;
            delete unk28;
            delete unk2c;
        }

        /**
         * @brief Transform complex samples in place, rebuilding the tables first when the size changes.
         * @param n Number of samples, a power of two; zero releases the tables.
         * @param re Real parts.
         * @param im Imaginary parts.
         */
        void transform(s32 n, float* re, float* im);

        /**
         * @brief Fill a sine table covering one and a quarter periods.
         * @param n Transform size.
         * @param table Table of n + n / 4 entries; the cosine of step i is at i + n / 4.
         */
        void make_sine_table(s32 n, float* table);

        /**
         * @brief Fill the bit-reversal permutation of the sample indices.
         * @param n Transform size.
         * @param table Table of n entries.
         */
        inline void make_bit_reverse(s32 n, s32* table);

        /** Size the tables were built for. */
        s32 size;

        s32 unk04;
        s32* bit_reverse;
        float* sine_table;
        u8* unk10;
        s32 unk14;
        u8* unk18;
        u8* unk1c;
        u8 unk20[4];
        s32 unk24;
        u8* unk28;
        u8* unk2c;
        u8 unk30[4];
};

/**
 * Stereo needle meter with vtable D_171CF0 in main data. It eases a needle towards each channel's level and keeps a
 * third needle on the decaying peak, drawing all three as GS lines into its own packet.
 */
class BootNeedleMeter : public BootTransformOwner, public BootDmaCallbacks
{
    public:
        /** @brief Set up the meter's transform and packet, with every needle at rest. */
        BootNeedleMeter();

        /** @brief Release the packet and destroy the transform. */
        virtual ~BootNeedleMeter();

        /** @brief Mark the meter active and submit its packet. */
        virtual void render();

        /** @brief Clear the byte at offset 0x60. */
        virtual void func_001E0860();

        /**
         * @brief Move the needles towards their levels and draw them.
         * @param matrix Matrix supplied by the caller; unused.
         * @param context Opaque caller context; unused.
         */
        virtual void build_packet(const void* matrix, void* context);

        /**
         * @brief Clear dma_pending and run the Lib hook.
         * @param value Notification value; unused.
         */
        virtual void on_packet_complete(u32 value);

        /**
         * @brief Place the needles' pivot.
         * @param pivot_x Screen x.
         * @param pivot_y Screen y.
         */
        void set_position(s32 pivot_x, s32 pivot_y)
        {
            x = pivot_x;
            y = pivot_y;
        }

        BootPacketBuffer* packet;
        u8 unk98[0x898];

        /** Left and right needle positions, 0 to 96. */
        float needles[2];

        /** Left and right levels the needles move towards. */
        float levels[2];

        /** Peak needle position. */
        float peak;

        /** Seconds left before the peak needle starts to fall. */
        float peak_hold;

        /** Pivot of the needles on screen. */
        s32 x;

        s32 y;
};

/** Boot's view of the 0x100-byte Lib string label with vtable D_175140 in main data. */
class BootStringLabel : public BootDrawWidget
{
    public:
        /**
         * @brief Initialize the label with its string and rectangle.
         * @param text String to draw.
         * @param flag Drawing flag.
         * @param x Origin x.
         * @param y Origin y.
         * @param width Rectangle width.
         * @param height Rectangle height.
         */
        BootStringLabel(const char* text, u8 flag, float x, float y, float width, float height)
        {
            unk38 = 14;
            func_467AD0(this, text, flag, x, y, width, height);
        }

        /** @brief Destroy the label. */
        virtual ~BootStringLabel();

        /**
         * @brief Change the string and mark the label for redraw.
         * @param value String to draw.
         */
        void set_text(const char* value)
        {
            text = value;
            needs_redraw = 1;
        }

        /** String the label draws. */
        const char* text;
};

/** Real and imaginary parts of one channel's spectrum. */
struct BootSpectrum
{
    float real[1024];
    float imag[1024];
};

/** Music player limits. */
enum BootMusicConstants
{
    /** Number of tracks the player can play. */
    BOOT_MUSIC_TRACK_COUNT = 87
};

/**
 * Music player with vtable D_171D80 in main data, opened from the Battle Trophies screen. It streams one of 87 tracks
 * in order, on repeat or shuffled, and shows five frequency bands of each channel on a row of needle meters.
 */
class BootMusicPlayer : public BootListObject
{
    public:
        /** @brief Start loading resource 0x2C, create the meters and build the analysis window. */
        BootMusicPlayer();

        /** @brief Release the loaded data, the owned objects and the transform, then stop the stream. */
        virtual ~BootMusicPlayer();

        /**
         * @brief Report the list kind used when registration requests the default.
         * @return Four.
         */
        virtual s32 get_default_list_kind();

        /** @brief Run the player. */
        virtual void update();

        /** @brief Destroy every owned object and release the resource. */
        void release();

        /** @brief Pulse the selected row's image and reset the others. */
        void update_row_colors();

        /** @brief Create the screen images once both image buffers are loaded. */
        void create_images();

        /** Resource 0x2C. */
        u8* resource_data;

        u8* image_buffers[2];
        BootImage* images[20];
        s32 step;
        u8 images_loaded;

        /** Selected menu row. */
        u8 selection;

        /** Nonzero while the selected row's image brightens again. */
        u8 brightening;

        /** Zero plays one track, one plays the list in order and two plays it shuffled. */
        u8 play_mode;

        u8 unk78;

        /** Index of the current track in the track table. */
        u8 track;

        /** Shuffled track indices. */
        u8 shuffle_order[BOOT_MUSIC_TRACK_COUNT];

        /** Next entry of shuffle_order to play. */
        u8 shuffle_position;

        /** Nonzero while a track is streaming. */
        u8 playing;

        /** Track whose start request failed, retried every frame. */
        s32 pending_track;

        /** Samples analysed so far. */
        float samples_analysed;

        /** Samples played so far. */
        float samples_played;

        /** Seconds before the next track starts. */
        float next_track_delay;

        u8 unke4[0xC];

        /** Left and right stream buffers. */
        u8 stream_buffers[2][0x200000];

        /** Spectrum of each channel. */
        BootSpectrum spectra[2];

        /** Hann window over one block of samples. */
        float window[1024];

        BootContainer* container;
        BootListObject* unk4050f4;
        BootSelectionCursor* cursor;

        /** Track number. */
        BootStringLabel* number_text;

        /** Track name. */
        BootTextWidget* name_text;

        /** Play mode. */
        BootTextWidget* mode_text;

        /** Row labels. */
        BootTextWidget* labels[5];

        /** One meter per frequency band. */
        BootNeedleMeter* meters[5];

        BootFft* fft;

        /** Formatted track number. */
        char number[12];
};

#endif

#endif
