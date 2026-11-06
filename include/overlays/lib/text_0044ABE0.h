#ifndef SO3_OVERLAYS_LIB_TEXT_0044ABE0_H
#define SO3_OVERLAYS_LIB_TEXT_0044ABE0_H

#include "types.h"

typedef struct LibDrawState64 LibDrawState64;
typedef struct ItemCreationClass174C40 ItemCreationClass174C40;
typedef struct LibCallbackTransform LibCallbackTransform;

/** Partial receiver whose byte at offset 0x60 is set by func_0044C050. */
typedef struct LibObjectByte60
{
    u8 unk00[0x60];
    u8 unk60;
} LibObjectByte60;

/** Number of Battle Trophies and of flags in the saved collection. */
#define LIB_TROPHY_COUNT 300

/** Size of one saved trophy record, picture included. */
#define LIB_TROPHY_RECORD_SIZE 0xF10

/** Linear congruential step the saved-data checksums use: value * multiplier + increment. */
#define LIB_CHECKSUM_MULTIPLIER 0x19660D
#define LIB_CHECKSUM_INCREMENT 0x3C6EF35F

#ifdef __cplusplus
/** Bit array whose bytes come before the vptr (vtable D_1721D0 in main data). */
class LibBitArray
{
public:
    u8 unk00[4];

    /** Size of the array in bytes. */
    s32 size;

    u8* bytes;

    /** Nonzero when bytes is borrowed and must not be freed. */
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
};

/** The battle trophy flags kept with the system settings, one bit per trophy, under their own checksum. */
struct LibTrophyFlags
{
    /** Bit i is set once trophy i is earned. */
    LibBitArray flags;

    /** Random word mixed into each trophy record's key; replaced when the flags are reset. */
    s32 trophy_key;

    /** Seed for checksum. */
    u32 checksum_seed;

    u32 checksum;
};

/** Marker byte of an encoded LibSealedRecord. */
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
    /** Tail encoded byte by byte with LIB_RECORD_XOR_BYTE. */
    u8 encoded_tail[LIB_RECORD_ENCODED_TAIL_SIZE];
    u16 checksum;

    /** Random byte; the checksum seed is 37 times this. */
    u8 key;

    /** LIB_RECORD_SEALED once encoded; any other nonzero value marks a damaged record. */
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

/** Partial 0x1C8-byte system settings (resident entry 1), with option bits and two checksummed blocks. */
struct LibSystemSettings
{
    /** @brief Leave the settings uninitialized; the allocator clears them. */
    LibSystemSettings()
    {
    }

    /** Button mask that confirms a selection. */
    u16 confirm_buttons;

    /** Button mask that cancels or skips. */
    u16 cancel_buttons;

    /** Button mask for the other choice of a two-way prompt. */
    u16 alternate_buttons;

    u16 unk06;
    u8 unk08[0x1C];
    u8 unk24_low : 2;
    u8 unk24_mid : 2;
    u8 unk24_bit4 : 1;

    /** Controller vibration on. */
    u8 vibration : 1;

    u8 unk24_bit6 : 1;

    /** Offer to skip events as they start. */
    u8 event_skip : 1;

    u8 unk25_low : 1;
    u8 unk25_bit1 : 1;

    /** Event dialog: subtitles and voice, voice only, subtitles only, or auto-advancing subtitles and voice. */
    u8 voice_mode : 2;

    /** Set when Continue is chosen on the title screen, cleared when a new game starts. */
    u8 continue_selected : 2;

    u8 unk25_bit6 : 1;
    u8 unk25_bit7 : 1;

    /** First byte covered by checksum. */
    u8 checksum_start;

    u8 unk27;

    /** Difficulty: Earth, Galaxy, Universe or 4D. */
    u8 difficulty;

    u8 unk29[0x7B];
    u16 checksum;

    /** Seed for checksum, replaced on every write. */
    u16 key;

    u8 unkA8[0x2C];
    LibSealedRecord sealed_record;
    u8 unk188[4];

    /** Nonzero for the 16:9 screen layout. */
    u8 widescreen;

    u8 unk18D;

    /** LibSoundOutput saved in the settings record. */
    u8 sound_output;

    u8 unk18F;

    /** Angle of each of the four surround speakers, as saved. */
    float speaker_angles[4];

    /** First byte covered by extra_checksum. */
    u8 extra_checksum_start;

    /** Nonzero once Universe difficulty can be chosen. */
    u8 universe_unlocked;

    /** Nonzero once 4D difficulty can be chosen. */
    u8 fourth_dimension_unlocked;

    /** Extra player colors unlocked by battle trophy score: 1 for 2P, 2 for 3P, 3 for 4P. */
    u8 color_unlock_level;

    u16 extra_checksum;

    /** Seed for extra_checksum. */
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

void* func_004568A0(void* receiver);
#endif
/** @brief Set the receiver's byte at offset 0x60 to 8. @param object Receiver to update. */
void func_0044C050(LibObjectByte60* object);
/** @brief Set the receiver's byte at offset 0x60 to 8. @param object Receiver to update. */
void func_0044D070(LibObjectByte60* object);
/** @brief Return the address of D_00508230. @return The data symbol's address. */
const void* func_0044D080(void);
/** @brief Update the transform and mark the current display ready. @param object Transform receiver. */
void func_0044D0D0(void* object);
/** @brief Return the fixed value 35. @param object Unused receiver. @return Always 35. */
s32 func_00451E20(void* object);
/** @brief Return the fixed value 43. @return Always 43. */
s32 func_004540D0(void);
/** @brief Return the fixed value 10. @return Always 10. */
s32 func_00454730(void);
/** @brief Return the fixed value 43. @return Always 43. */
s32 func_004547B0(void);
/** @brief Return the fixed value 40. @return Always 40. */
s32 func_00456200(void);
/** @brief Return the fixed value 6. @return Always 6. */
s32 func_00456940(void);
/** @brief Return the fixed value 36. @return Always 36. */
s32 func_004569C0(void);
/** @brief Return the fixed value 9. @return Always 9. */
s32 func_0045ABA0(void);
/** @brief Perform no work. @param object Unused receiver. */
void func_0044C060(void* object);
/** @brief Return the address of D_00508240. @return The data symbol's address. */
const void* func_0044C070(void);
/** @brief Clear the selected state in the shared lib object. */
void func_0044C080(void);
/** @brief Forward the receiver to the base transform update. @param object Transform receiver. */
void func_0044C0F0(void* object);
/** @brief Forward the receiver to the base transform update. @param object Transform receiver. */
void func_0044D150(void* object);
/** @brief Detach the transform once and mark it released. @param object Transform receiver. */
void func_0044B1C0(LibCallbackTransform* object);

/**
 * @brief Detach the transform receiver from its parent container when attached.
 * @param object Transform receiver to detach.
 */
void func_0044B210(LibCallbackTransform* object);

/**
 * @brief Apply the saved input mode, slot configuration, and input flag.
 * @param settings Saved settings receiver.
 */
void func_004587C0(void* settings);

/**
 * @brief Compute the seeded checksum over a byte range.
 * @param seed Initial checksum seed.
 * @param data Bytes to checksum.
 * @param size Signed byte count.
 * @return Low sixteen bits of the resulting checksum.
 */
u16 lib_compute_checksum(u16 seed, const void* data, s32 size);

/**
 * @brief Select the indexed resource and initialize its drawing position.
 * @param object Resource widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param index Resource index.
 * @return Initialization status.
 */
s32 lib_indexed_resource_init(ItemCreationClass174C40* object, float x, float y, s32 index);

/** @brief Initialize resource pointers, drawing scales, colors, and descriptor defaults. @param state State to initialize. */
void lib_draw_state_init(LibDrawState64* state);
#ifdef __cplusplus
}
#endif

/** Drawing state containing resource pointers, scalar coordinates, and descriptor bytes. */
struct LibDrawState64
{
    u32 unk00;
    void* unk04;
    void* unk08;
    u32 unk0c;
    u32 unk10;
    u8 unk14[4];
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
    u16 unk54;
    u16 unk56;
    u8 unk58;
    u8 unk59;
    u8 unk5a;
    u8 unk5b;
    u8 unk5c[2];
    /** Negative values use the resource record's default descriptor byte. */
    s8 unk5e;
    u8 unk5f;
    u8 unk60;
    u8 unk61[3];
#ifdef __cplusplus
    /** @brief Initialize the drawing state. */
    LibDrawState64()
    {
        lib_draw_state_init(this);
    }
#endif
};

#ifdef __cplusplus
#include "overlays/lib/text_004BD360.h"

/** @brief Clear the intrusive owner and invoke the base transform release. @param object Transform owner to detach. */
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

/** @brief Update x and y, preserve z, set w to one, and mark the state. @param state Partial vector state. @param x Horizontal component. @param y Vertical component. */
extern "C" void func_0044B190(LibVectorUpdateView* state, float x, float y);

/** @brief Queue the receiver's DMA callback interface. @param object Transform receiver. @return Queue insertion result. */
extern "C" s32 func_0044C110(LibCallbackTransform* object);

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
    /** @brief Initialize storage that restores the runtime clipping bounds. @param code Initialization code passed to the resident routine. */
    inline ItemCreationClass1746A0(s32 code);
    /** @brief Release the widget storage and destroy its base. */
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
    /** @brief Release the widget storage and destroy its base. */
    virtual ~ItemCreationClass175110();
    /** @brief Refresh the resource drawing state. */
    virtual void func_00413D20();
    /** @brief Draw the resource widget. */
    virtual void draw();
    LibStorageBlock0C unk40;
    u8 unk4c[4];
    LibDrawState64 unk50;
    void* unkb4;
    u16 unkb8;
    u16 unkba;
    u8 unkbc;
    u8 unkbd;
    u8 unkbe;
    u8 unkbf;
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
    /** @brief Initialize the resource widget. */
    ItemCreationClass174C40()
    {
    }
    /** @brief Release the resource widget and destroy its base. */
    virtual ~ItemCreationClass174C40();
    /** @brief Refresh the indexed resource drawing state. */
    virtual void func_00413D20();
    s32 unkcc;
    s32 unkd0;
    /** @brief Set both drawing scales. @param x Horizontal scale. @param y Vertical scale. */
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

/** @brief Initialize storage that restores the runtime clipping bounds. @param object Clipping widget. @param code Unused initialization argument. @return True when drawing storage was allocated. */
extern "C" bool lib_scissor_init_reset(ItemCreationClass1746A0* object, s32 code);
/** @brief Initialize clipping rectangle geometry and drawing storage. @param object Clipping widget. @param x Horizontal position. @param y Vertical position. @param width Drawing width. @param height Drawing height. @return True when drawing storage was allocated. */
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
/** @brief Initialize storage that restores the runtime clipping bounds. @param code Initialization code passed to the resident routine. */
inline ItemCreationClass1746A0::ItemCreationClass1746A0(s32 code)
{
    unk38 = 4;
    lib_scissor_init_reset(this, code);
}

#endif

#endif
