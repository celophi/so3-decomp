#ifndef SO3_OVERLAYS_LIB_TEXT_0044ABE0_H
#define SO3_OVERLAYS_LIB_TEXT_0044ABE0_H

#include "types.h"

#ifdef __cplusplus
#include "main/main.h"
#endif

typedef struct LibImageAnimation LibDrawState64;
typedef struct ItemCreationClass174C40 ItemCreationClass174C40;
typedef struct LibCallbackTransform LibCallbackTransform;
struct LibResourceChunkHeader;

/** Partial receiver whose byte at offset 0x60 is set by func_0044D070. */
typedef struct LibObjectByte60
{
    u8 unk00[0x60];
    u8 unk60;
} LibObjectByte60;

#define LIB_TROPHY_COUNT 300
#define LIB_TROPHY_RECORD_SIZE 0xF10
#define LIB_CHECKSUM_MULTIPLIER 0x19660D
#define LIB_CHECKSUM_INCREMENT 0x3C6EF35F

#ifdef __cplusplus
/** Bit array whose bytes come before the vptr (vtable D_1721D0 in main data). */
class LibBitArray
{
public:
    s32 count;
    s32 size;
    u8* bytes;
    u8 borrowed;

    /** @brief Start with no bytes. */
    LibBitArray()
    {
        bytes = 0;
        borrowed = 0;
    }

    /** @brief Free the bytes unless they're borrowed. */
    virtual ~LibBitArray()
    {
        if (!borrowed)
        {
            delete[] bytes;
        }
    }

    /**
     * @brief Replace the bytes with new ones for a bit count.
     * @param bits Number of bits.
     */
    void resize(s32 bits)
    {
        if (!borrowed)
        {
            delete[] bytes;
        }

        count = bits;
        size = (bits + 7) >> 3;
        bytes = new (0) u8[size];
        borrowed = 0;
    }

    /** @brief Clear every byte. */
    void clear()
    {
        s32 total = size;

        for (s32 i = 0; i < total; i++)
        {
            bytes[i] = 0;
        }
    }
};

/** The battle trophy flags kept with the system settings, one bit per trophy, under their own checksum. */
struct LibTrophyFlags
{
    LibBitArray flags;
    s32 trophy_key;
    u32 checksum_seed;
    u32 checksum;
};

#define LIB_RECORD_SEALED 0x69

/** Masks and sizes used when sealing the saved record. */
enum LibSealedRecordConstants
{
    LIB_RECORD_XOR_BYTE = 0xD7,
    LIB_RECORD_XOR_HALFWORD = 0xF393,
    LIB_RECORD_XOR_WORD = 0x7CE3C7F7,
    LIB_RECORD_ENCODED_TAIL_SIZE = 76,
    LIB_RECORD_CHECKSUM_KEY_FACTOR = 37
};

/**
 * @brief 0xB4-byte saved record that is kept XOR-encoded, with a checksum over the encoded bytes.
 * @note Only the encoding is known; the fields are still unnamed.
 */
typedef struct LibSealedRecord
{
    u8 unk00;
    u16 unk02;
    u32 unk04;
    u32 unk08;
    u32 unk0C;
    u32 unk10;
    u32 unk14;
    u32 unk18;
    u32 unk1C;
    u32 unk20;
    u32 unk24;
    u32 unk28;
    u32 unk2C;
    u32 unk30;
    u32 unk34;
    u32 unk38;
    u32 unk3C;
    u32 unk40;
    u32 unk44;
    u32 unk48;
    u32 unk4C;
    u32 unk50;
    u32 unk54;
    u32 unk58;
    u8 unk5C[8];
    u8 encoded_tail[LIB_RECORD_ENCODED_TAIL_SIZE];
    u16 checksum;
    u8 key;
    u8 sealed;
} LibSealedRecord;

/** Saved sound output choice; the audio system uses a different code for mono and stereo. */
enum LibSoundOutput
{
    LIB_SOUND_MONO,
    LIB_SOUND_STEREO,
    LIB_SOUND_DOLBY_PRO_LOGIC_II,
    LIB_SOUND_HEADPHONES
};

/** Saved voice and subtitle choice. */
enum LibVoiceMode
{
    LIB_VOICE_SUBTITLES_AND_SOUND,
    LIB_VOICE_SOUND_ONLY,
    LIB_VOICE_SUBTITLES_ONLY,
    LIB_VOICE_AUTO
};

/** Saved difficulty choice. */
enum LibDifficulty
{
    LIB_DIFFICULTY_EARTH,
    LIB_DIFFICULTY_GALAXY,
    LIB_DIFFICULTY_UNIVERSE,
    LIB_DIFFICULTY_FOURTH_DIMENSION
};

#define LIB_DTT_CHUNK_MAGIC 0x00545444

/** Size and address of a DTT chunk's data. */
struct LibChunkData
{
    u32 size;
    void* data;
};

#define LIB_COUNTED_FACTOR_COUNT 40

/** Saved counts of the factors in the counted factor table, with checksums over the counts and the table. */
struct LibFactorCounts
{
    u16 checksum;
    s8 counts[LIB_COUNTED_FACTOR_COUNT];
    u16 table_checksum;
};

#define LIB_SETTINGS_GRID_SIZE 10

/** Partial 0x1C8-byte system settings (resident entry 1), with option bits and two checksummed blocks. */
struct LibSystemSettings
{
    LibSystemSettings()
    {
    }

    u16 confirm_buttons;
    u16 cancel_buttons;
    u16 alternate_buttons;
    u16 extra_buttons;
    u8 unk08[0x1C];
    u8 unk24_low : 2;
    u8 unk24_mid : 2;
    u8 unk24_bit4 : 1;
    u8 vibration : 1;
    u8 unk24_bit6 : 1;
    u8 event_skip : 1;
    u8 unk25_low : 1;
    u8 unk25_bit1 : 1;
    u8 voice_mode : 2;
    u8 continue_selected : 2;
    u8 unk25_bit6 : 1;
    u8 unk25_bit7 : 1;
    u8 checksum_start;
    u8 unk27;
    u8 difficulty;
    u8 unk29[0xB];
    u32 encoded_fol;
    u8 unk38[8];
    u8 unk40[LIB_SETTINGS_GRID_SIZE][LIB_SETTINGS_GRID_SIZE];
    u16 checksum;
    u16 key;
    LibFactorCounts factor_counts;
    LibSealedRecord sealed_record;
    u8 unk188[4];
    u8 widescreen;
    u8 unk18D;
    u8 sound_output;
    u8 unk18F;
    float speaker_angles[4];
    u8 extra_checksum_start;
    u8 universe_unlocked;
    u8 fourth_dimension_unlocked;
    u8 color_unlock_level;
    u16 extra_checksum;
    u16 extra_key;
    LibTrophyFlags trophy_flags;
};

/** Resident entry table keys of the saved system data. */
enum
{
    LIB_ENTRY_SYSTEM_SETTINGS = 1,
    LIB_ENTRY_RECORD_OUTPUTS = 2,
    LIB_ENTRY_RECORD_INPUTS = 3,
    LIB_ENTRY_08 = 8,
    LIB_ENTRY_PADDING = 9
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Free the system settings, the two record arrays and the padding block, and remove their entries. */
void lib_free_system_data(void);

/**
 * @brief Allocate the system settings, the two record arrays and func_0040B760's data in a random order, after a
 *        random-sized padding block, register them in the resident entry table and initialize them.
 */
void lib_allocate_system_data(void);

/**
 * @brief Compute the trophy flags' checksum from a seed: each flag, flipped by the seed's low bit, weighted by the
 *        next value of the seed sequence, plus the trophy key mixed with the final seed.
 * @param flags Trophy flags.
 * @param seed Seed.
 * @param checksum Receives the checksum.
 */
void lib_trophy_flags_checksum(LibTrophyFlags* flags, const u32* seed, u32* checksum);

/**
 * @brief Pick a new random checksum seed for the trophy flags and recompute their checksum.
 * @param flags Trophy flags.
 */
void lib_trophy_flags_update_checksum(LibTrophyFlags* flags);

#ifdef __cplusplus
/**
 * @brief Decode a trophy record in place, then check it against the checksum in its first word.
 * @param record Encoded record (LIB_TROPHY_RECORD_SIZE bytes).
 * @return Whether the decoded record's checksum matches.
 */
bool lib_trophy_record_decode(void* record);

/**
 * @brief Store a trophy record's checksum in its first word, then encode the record in place.
 * @param record Decoded record (LIB_TROPHY_RECORD_SIZE bytes).
 */
void lib_trophy_record_encode(void* record);

#endif

/**
 * @brief Set the receiver's byte at offset 0x60 to 8.
 * @param object Receiver to update.
 */
void func_0044D070(LibObjectByte60* object);

/**
 * @brief Return the address of D_00508230.
 * @return The data symbol's address.
 */
const void* func_0044D080(void);

/**
 * @brief Return the fixed value 35.
 * @param object Unused receiver.
 * @return Always 35.
 */
s32 func_00451E20(void* object);

/**
 * @brief Return the fixed value 9.
 * @return Always 9.
 */
s32 func_0045ABA0(void);

/**
 * @brief Detach the transform once and mark it released.
 * @param object Transform receiver.
 */
void func_0044B1C0(LibCallbackTransform* object);

/**
 * @brief Detach the transform receiver from its parent container when attached.
 * @param object Transform receiver to detach.
 */
void func_0044B210(LibCallbackTransform* object);

/**
 * @brief Apply the saved sound output mode, speaker angles and vibration setting.
 * @param settings System settings.
 */
void func_004587C0(LibSystemSettings* settings);

/**
 * @brief Compute the seeded checksum over a byte range.
 * @param seed Initial checksum seed.
 * @param data Bytes to checksum.
 * @param size Signed byte count.
 * @return Low sixteen bits of the resulting checksum.
 */
u16 lib_compute_checksum(u16 seed, const void* data, s32 size);

/**
 * @brief Find the first DTT chunk in a chunk list.
 * @param out Receives the chunk's data size and address.
 * @param chunk First chunk.
 * @return Whether a DTT chunk was found.
 */
bool func_00456D60(LibChunkData* out, LibResourceChunkHeader* chunk);

/**
 * @brief Store an entry of the settings' 10 by 10 byte grid, limited to 0 through 70, when the settings checksum is
 *        valid, and reseal the checksum.
 * @param settings System settings.
 * @param row Row, 1 through 10.
 * @param column Column, 1 through 10.
 * @param value Value to store.
 */
void func_004577A0(LibSystemSettings* settings, s32 row, s32 column, s32 value);

/**
 * @brief Read an entry of the settings' 10 by 10 byte grid.
 * @param settings System settings.
 * @param row Row, 1 through 10.
 * @param column Column, 1 through 10.
 * @return Entry, or zero when the checksum is invalid or the position is out of range.
 */
s32 func_00457980(LibSystemSettings* settings, s32 row, s32 column);

/**
 * @brief Add up a byte range for a factor count list's checksums, each byte plus three times its index.
 * @param list Factor count list; unused.
 * @param data Bytes to add up.
 * @param size Byte count.
 * @return Sum.
 */
u16 lib_factor_checksum(LibFactorCounts* list, const u8* data, s32 size);

/**
 * @brief Check both of a factor count list's checksums.
 * @param list Factor count list.
 * @return Whether the counts and the factor table both match their checksums.
 */
bool lib_factor_counts_valid(LibFactorCounts* list);

/**
 * @brief Check whether a factor has been counted, clearing the list first if its checksums are bad.
 * @param list Factor count list.
 * @param factor Factor ID.
 * @return Whether the factor's count is positive.
 */
bool lib_factor_counted(LibFactorCounts* list, s32 factor);

/**
 * @brief Lower a factor's count by one.
 * @param list Factor count list.
 * @param factor Factor ID.
 */
void lib_factor_count_lower(LibFactorCounts* list, s32 factor);

/**
 * @brief Raise a factor's count by one.
 * @param list Factor count list.
 * @param factor Factor ID.
 */
void lib_factor_count_raise(LibFactorCounts* list, s32 factor);

/**
 * @brief Look up a factor's count.
 * @param list Factor count list.
 * @param factor Factor ID.
 * @return Count, or zero for a factor that isn't counted.
 */
s32 lib_factor_count(LibFactorCounts* list, s32 factor);

/**
 * @brief Set a factor's count and refresh the counts' checksum.
 * @param list Factor count list.
 * @param factor Factor ID.
 * @param count New count.
 * @return Whether the factor is counted.
 */
bool lib_factor_count_set(LibFactorCounts* list, s32 factor, s32 count);

/**
 * @brief Clear every count and rewrite both checksums.
 * @param list Factor count list.
 */
void lib_factor_counts_reset(LibFactorCounts* list);

/**
 * @brief Select the indexed resource and initialize its drawing position.
 * @param object Resource widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param index Resource index.
 * @return Initialization status.
 */
s32 lib_indexed_resource_init(ItemCreationClass174C40* object, float x, float y, s32 index);

/**
 * @brief Initialize resource pointers, drawing scales, colors, and descriptor defaults.
 * @param state State to initialize.
 */
void lib_draw_state_init(LibDrawState64* state);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include "overlays/lib/text_004BD360.h"

/**
 * @brief Clear the intrusive owner and invoke the base transform release.
 * @param object Transform owner to detach.
 */
extern "C" void func_0044D090(LibTransformOwner* object);

/** Four scalar components stored in a LibVectorUpdateView. */
typedef struct LibFloatVector4
{
    float x;
    float y;
    float z;
    float w;
} LibFloatVector4;

/** Partial state updated by func_0044B190; its caller passes the containing object's +0x20 address. */
typedef struct LibVectorUpdateView
{
    u8 unk00[0x20];
    LibFloatVector4 unk20;
    u8 unk30[0x7E];
    u8 unkAE;
} LibVectorUpdateView;

/**
 * @brief Update x and y, preserve z, set w to one, and mark the state.
 * @param state Partial vector state.
 * @param x Horizontal component.
 * @param y Vertical component.
 */
extern "C" void func_0044B190(LibVectorUpdateView* state, float x, float y);

/**
 * @brief Queue the receiver's DMA callback interface.
 * @param object Transform receiver.
 * @return Queue insertion result.
 */
extern "C" s32 func_0044C110(LibCallbackTransform* object);

/** One 16-byte entry of an image resource's animation frame list. */
struct LibImageFrame
{
    u8 unk00[0xD];
    u8 kind;
    u16 duration;
};

/** Frame list header at 0x10 in an image resource: the frame count, then the frames. */
struct LibImageFrameList
{
    u32 count;
    LibImageFrame frames[1];
};

/** Drawing format an image animation passes on to its draws. */
struct LibImageFormat
{
    u16 unk00;
    u16 unk02;
    u8 unk04;
    u8 unk05;
    u8 unk06;
    u8 unk07;
};

/** Partial frame animation over an image resource's frame list. */
struct LibImageAnimation
{
    /** @brief Initialize resource pointers, drawing scales, colours and format defaults. */
    LibImageAnimation()
    {
        lib_draw_state_init(this);
    }

    /**
     * @brief Start playing from a frame.
     * @param frame Frame index.
     */
    void start(s32 frame);

    /**
     * @brief Count the frame time down and move on when it runs out.
     * @return -1 once the last frame ended, 2 after moving to the next frame, 1 after jumping back, 0 otherwise.
     */
    s8 step();

    /**
     * @brief Use an image resource and, when given, its drawing format.
     * @param resource Image resource.
     * @param format Drawing format, or null to keep the current one.
     */
    void set_resource(void* resource, const LibImageFormat* format);

    /**
     * @brief Use one of the field runtime's display chunks, with the default drawing format for its range.
     * @param id Chunk index; below 34 and from 34 on use different defaults.
     */
    void set_display_chunk(s32 id);

    /**
     * @brief Set the drawing position.
     * @param x Horizontal position.
     * @param y Vertical position.
     */
    void set_position(float x, float y)
    {
        unk18 = x;
        unk1c = y;
    }

    u32 unk00;
    void* resource;
    LibImageFrame* frame;
    u32 frame_count;
    s32 index;
    float timer;
    float unk18;
    float unk1c;
    float unk20;
    float unk24;
    float unk28;
    float unk2c;
    float unk30;
    float unk34;
    float unk38;
    float unk3c;
    float unk40;
    float unk44;
    float unk48;
    float unk4c;
    float unk50;
    LibImageFormat format;
    s8 state;
    u8 active;
    s8 unk5e;
    u8 unk5f;
    u8 unk60;
    u8 unk61[3];
};

/**
 * Transform that draws one VIF1 packet of its own, with vtables D_1748D0 and D_174954 in main data; LibClass172080
 * and the other emitter-like classes derive from it.
 */
class LibClass1748D0 : public LibTransform, public DmaSubmission
{
public:
    /** @brief Start with no packet buffer, type ID 0xA00 and the class's draw bucket. */
    LibClass1748D0();

    /** @brief Draw in bucket 8. */
    virtual void set_default_draw_bucket();

    /** @brief Delete the packet buffer. */
    virtual ~LibClass1748D0();

    /** @brief Update the transform and mark the renderer's first pass ready. */
    virtual void update();

    /** @brief Close the packet with a DIRECTHL tag for its size and queue it on VIF1. */
    virtual void render();

    virtual const LibVector4* get_bounding_sphere();

    virtual void build_packet(const void* matrix, void* context);

    /**
     * @brief Send the packet on VIF1 in normal mode.
     * @param channel DMA channel; unused.
     */
    virtual void submit_dma(u32 channel);

    /**
     * @brief Finish the packet.
     * @param channel DMA channel; unused.
     */
    virtual void complete_dma(u32 channel);

    u8 unk214[0xC];
    LibVector4 bounding_sphere;
    LibPacketBuffer* packet;
    u32* packet_tag;
    u8 unk238[8];
    u32 qwc;
    u8 unk244;
    u8 unk245;
    float unk248;
    float unk24c;
    float unk250;
};

/** Partial Lib class with vtable D_174C20 in main data; its destructor is func_00452F00. */
class LibClass174C20
{
public:
    /** @brief Destroy the object. */
    virtual ~LibClass174C20();
};

/** Clipping widget with resident vtable at 0x1746A0. */
class ItemCreationClass1746A0 : public LibWidget
{
public:
    /** @brief Initialize the widget storage and select kind 4. */
    inline ItemCreationClass1746A0();

    /**
     * @brief Initialize clipping rectangle geometry and drawing storage.
     * @param x Horizontal position.
     * @param y Vertical position.
     * @param width Drawing width.
     * @param height Drawing height.
     */
    inline ItemCreationClass1746A0(float x, float y, float width, float height);

    /**
     * @brief Initialize storage that restores the runtime clipping bounds.
     * @param code Initialization code passed to the resident routine.
     */
    inline ItemCreationClass1746A0(s32 code);

    virtual ~ItemCreationClass1746A0();

    /** @brief Write the widget clipping bounds into its drawing packet. */
    virtual void draw();

    LibStorageBlock0C unk40;
    u8 unk4c[4];
    u8 unk50;
};

/** Partial widget with resident vtable at 0x175110. */
class ItemCreationClass175110 : public LibWidget
{
public:
    /** @brief Initialize the owned storage and drawing state for kind 7. */
    ItemCreationClass175110()
    {
        unk38 = 7;
    }

    virtual ~ItemCreationClass175110();

    /** @brief Refresh the resource drawing state. */
    virtual void func_00413D20();

    /** @brief Draw the resource widget. */
    virtual void draw();

    LibStorageBlock0C unk40;
    u8 unk4c[4];
    LibImageAnimation unk50;
    void* unkb4;
    LibImageFormat unkb8;
    s32 unkc0;
    u32 unkc4;
    u8 unkc8;
    u8 unkc9;
    u8 unkca[2];
};

/** Resident resource widget with its two resource indices at CC and D0. */
class ItemCreationClass174C40 : public ItemCreationClass175110
{
public:
    ItemCreationClass174C40()
    {
    }

    virtual ~ItemCreationClass174C40();

    /** @brief Refresh the indexed resource drawing state. */
    virtual void func_00413D20();

    s32 unkcc;
    s32 unkd0;

    /**
     * @brief Set both drawing scales.
     * @param x Horizontal scale.
     * @param y Vertical scale.
     */
    void set_scale(float x, float y)
    {
        unk50.unk34 = y;
        unk50.unk30 = x;
        needs_redraw = 1;
    }
};

typedef ItemCreationClass1746A0 LibClass1746A0;
typedef ItemCreationClass175110 LibClass175110;
typedef ItemCreationClass174C40 LibClass174C40;

/**
 * @brief Initialize storage that restores the runtime clipping bounds.
 * @param object Clipping widget.
 * @param code Unused initialization argument.
 * @return True when drawing storage was allocated.
 */
extern "C" bool lib_scissor_init_reset(ItemCreationClass1746A0* object, s32 code);

/**
 * @brief Initialize clipping rectangle geometry and drawing storage.
 * @param object Clipping widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Drawing width.
 * @param height Drawing height.
 * @return True when drawing storage was allocated.
 */
extern "C" bool lib_scissor_init_rectangle(ItemCreationClass1746A0* object, float x, float y, float width, float height);

/**
 * @brief Initialize clipping rectangle geometry and drawing storage.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Drawing width.
 * @param height Drawing height.
 */
inline ItemCreationClass1746A0::ItemCreationClass1746A0(float x, float y, float width, float height)
{
    unk38 = 4;
    lib_scissor_init_rectangle(this, x, y, width, height);
}

/**
 * @brief Initialize storage that restores the runtime clipping bounds.
 * @param code Initialization code passed to the resident routine.
 */
inline ItemCreationClass1746A0::ItemCreationClass1746A0(s32 code)
{
    unk38 = 4;
    lib_scissor_init_reset(this, code);
}

#endif

#endif
