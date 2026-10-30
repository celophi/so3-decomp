#ifndef SO3_OVERLAYS_BOOT_TEXT_001DD3C0_H
#define SO3_OVERLAYS_BOOT_TEXT_001DD3C0_H

#include "types.h"

/** Marker byte of an encoded BootSealedRecord. */
#define BOOT_RECORD_SEALED 0x69

/** @brief Four aligned floating-point vector components. */
typedef struct BootVector4DDAA0
{
    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16))) BootVector4DDAA0;

/**
 * @brief Copy all 128 bits of an aligned four-component vector.
 * @param destination Vector receiving the copy.
 * @param source Vector to copy.
 */
static inline void copy_vector(BootVector4DDAA0* destination, const BootVector4DDAA0* source)
{
    *(unsigned __int128*)destination = *(const unsigned __int128*)source;
}

/** @brief Matrix storage containing four aligned four-component vectors. */
typedef struct BootMatrix92D0
{
    BootVector4DDAA0 vectors[4];
} BootMatrix92D0;

/** @brief The battle trophy flags kept with the system settings, one bit per trophy, under their own checksum. */
typedef struct BootTrophyFlags
{
    u8 unk00[4];

    /** Size of the flag array in bytes. */
    s32 size;

    /** Flag array: bit i of the array is set once trophy i is earned. */
    u8* flag_bytes;

    u8 unk0C[8];

    /** Random word mixed into each trophy record's key; replaced when the flags are reset. */
    s32 trophy_key;

    /** Seed for checksum. */
    u32 checksum_seed;

    u32 checksum;
} BootTrophyFlags;

/**
 * @brief 0xB4-byte saved record that is kept XOR-encoded, with a checksum over the encoded bytes.
 * @note Only the encoding is known; the fields are still unnamed.
 */
typedef struct BootSealedRecord
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
    u8 unk64[76];
    u16 checksum;

    /** Random byte; the checksum seed is 37 times this. */
    u8 key;

    /** BOOT_RECORD_SEALED once encoded; any other nonzero value marks a damaged record. */
    u8 sealed;
} BootSealedRecord;

/** @brief Partial system settings, with option bits and two checksummed blocks. */
typedef struct BootSystemSettings
{
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
    u8 unk26;

    u8 unk27;

    /** Difficulty: Earth, Galaxy, Universe or 4D. */
    u8 difficulty;

    u8 unk29[0x7B];
    u16 checksum;

    /** Seed for checksum, replaced on every write. */
    u16 key;

    u8 unkA8[0x2C];
    BootSealedRecord sealed_record;
    u8 unk188[4];

    /** Nonzero for the 16:9 screen layout. */
    u8 widescreen;

    u8 unk18D;

    /** Sound output: mono, stereo, Dolby Pro Logic II or headphones. */
    u8 sound_output;

    u8 unk18F;

    /** Angle of each of the four surround speakers, as saved. */
    float speaker_angles[4];

    /** First byte covered by extra_checksum. */
    u8 unk1A0;

    /** Nonzero once Universe difficulty can be chosen. */
    u8 universe_unlocked;

    /** Nonzero once 4D difficulty can be chosen. */
    u8 fourth_dimension_unlocked;

    /** Extra player colors unlocked by battle trophy score: 1 for 2P, 2 for 3P, 3 for 4P. */
    u8 color_unlock_level;

    u16 extra_checksum;

    /** Seed for extra_checksum. */
    u16 extra_key;

    BootTrophyFlags trophy_flags;
} BootSystemSettings;

/** Partial resident memory card and loading state reached through D_001B65E4. */
typedef struct BootResident1B65E4
{
    u8 unk00[0x108];
    u8 unk108;
    u8 unk109[0x32];
    u8 unk13b;
    u8 unk13c[5];
    u8 unk141;
    u8 unk142[0x12041];
    u8 unk12183;
    u8 unk12184;
} BootResident1B65E4;

/** Partial resident display runtime reached through D_001B657C, with the Lib vtable D_174F50. */
class BootRuntime1B657C
{
    public:
        /**
         * @brief Initialize the runtime for a screen size; boot calls the Lib constructor.
         * @param width Screen width.
         * @param height Screen height.
         * @param first First mode.
         * @param second Second mode.
         * @param scale Scale factor.
         */
        BootRuntime1B657C(float width, float height, s32 first, s32 second, float scale);

        /** @brief Destroy the runtime. */
        virtual ~BootRuntime1B657C();

        u8 unk04[0x564];

        /** Number the next formatted message prints. */
        u32 message_value;

        /** Further numbers for messages that print more than one. */
        s32 message_values[9];

        u8 unk590[0x74];
};

/** @brief Partial resident sound stream reached through the sound object. */
struct BootSoundStream
{
    u8 unk00[0x90];

    /** Stream handle. */
    void* handle;
};

/** @brief Partial resident sound object reached through D_001B65F8. */
struct BootSound1B65F8
{
    struct BootSoundStream* stream;
    u8 unk04[0x36C];
    u8 unk370;
    u8 unk371[0x4B];
    s32 unk3bc;
    u8 unk3c0[0x90];

    /** Sound output mode: 1 mono, 0 stereo, 2 Dolby Pro Logic II, 3 headphones. */
    u8 output_mode;

    u8 unk451[0xF4B];

    /** Angle of each of the four surround speakers. */
    float speaker_angles[4];
};

/** @brief Partial display area whose signed dimensions drive the projection. */
struct BootDisplayArea3C60
{
    u8 unk00[0xC];
    s16 width;
    s16 height;
};

/** Partial 0x3F10-byte Lib display with vtable D_178FB0 in main data; its data comes before the vptr. */
class BootDimensionsACD0
{
    public:
        /** @brief Construct the display. */
        BootDimensionsACD0();

        u8 unk00[0x160];
        u16 unk160;
        u8 unk162[0x3AFE];
        BootDisplayArea3C60 unk3C60;
        u8 unk3C70[8];
        void* unk3C78;
        u8 unk3C7C[0x290];

        /** @brief Destroy the display. */
        virtual ~BootDimensionsACD0();
};

#ifdef __cplusplus
extern "C" {
#endif

extern class BootProjectionACD0* D_001B6654;

void* func_10D8E0(void);
void* func_101290(void* object);
void* func_101440(void* table, s32 selector);
void* func_13A678(void* destination, s32 value, u32 size);
extern BootRuntime1B657C* D_001B657C;
u8* func_102920(void* decoder, u8* source, s32 index, s32 aligned);
s32 func_1025A0(void* decoder, u8* source, void* destination, s32 index);
s32 func_102D00(void* queue);
extern BootResident1B65E4* D_001B65E4;
extern void* D_001B65E8;
extern void* D_001B65F4;
extern struct BootSound1B65F8* D_001B65F8;
u32 func_11C8C0(void* table, s32 id);
u8* func_139700(u32 alignment, u32 size);
void func_103E70(void* queue, s32 id, void* destination, s32 first, u32 size, s32 second, s32 third, s32 fourth, s32 fifth);
u16 func_457470(u16 seed, const void* data, s32 size);

/**
 * @brief Compute the checksum of a flag block from a seed.
 * @param bits Flag block.
 * @param seed Seed, passed by address.
 * @param checksum Receives the checksum.
 */
void func_457670(BootTrophyFlags* bits, u32* seed, u32* checksum);

/**
 * @brief Recompute the checksum of a flag block from its key.
 * @param bits Flag block.
 */
void func_457520(BootTrophyFlags* bits);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * @brief Return the system settings in the resident save data.
 * @return System settings.
 */
static inline BootSystemSettings* boot_settings()
{
    return (BootSystemSettings*)func_101440(func_101290(func_10D8E0()), 1);
}

/**
 * @brief Read a selected bit in the resource's flag array.
 * @param bits Resource storage containing the flag array.
 * @param index Unsigned flag index.
 * @return One if the bit is set, otherwise zero.
 */
static inline s32 resource_bit(BootTrophyFlags* bits, u32 index)
{
    return (bits->flag_bytes[index / 8] >> (index % 8)) & 1;
}

/**
 * @brief Set or clear a selected bit in the resource's flag array.
 * @param bits Resource storage containing the flag array.
 * @param index Unsigned flag index.
 * @param enabled Nonzero to set the bit, or zero to clear it.
 */
static inline void set_resource_bit(BootTrophyFlags* bits, u32 index, s32 enabled)
{
    u32 byte_index = index / 8;
    u32 bit_index = index % 8;
    u8 mask;

    if (enabled)
    {
        mask = 1ULL << bit_index;
        bits->flag_bytes[byte_index] |= mask;
    }
    else
    {
        mask = ~(1ULL << bit_index);
        bits->flag_bytes[byte_index] &= mask;
    }
}

#include "overlays/lib/text_0045AD10.h"

/**
 * @brief Detach an object from its owner.
 * @param object Intrusive receiver.
 */
extern "C" void lib_object_detach_owner(void* object);

class BootContainer;
class BootClass179150;
class BootClass170F30;
extern "C" s32 lib_container_init(BootContainer* container, s32 code, float x, float y, s32 first, float z, s32 second);
extern "C" s32 lib_text_init_resource_rectangle(void* object, s32 slot, s32 key, u8 flag, float x, float y, float width, float height);
extern "C" s32 lib_panel_init_rectangle(void* object, s32 mode, float x, float y, float width, float height, float extra);

/**
 * @brief Place a list indicator and set its scroll extent and position.
 * @param object List indicator.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param height Bar height.
 * @param extent Size of one scroll step, as a share of the bar.
 * @param position Scroll position.
 * @return One on success, or zero if its storage could not be initialized.
 */
extern "C" s32 lib_list_indicator_init(class BootListIndicator* object, float x, float y, float height, float extent, float position);
extern "C" void func_4E32F0(BootClass179150* object);
extern "C" void func_4D5C90(void* object);

/** Boot's copy of the virtual intrusive-link root, with vtable D_170E70 in main data. */
class BootLink
{
    public:
        /** @brief Destroy the intrusive-link root. */
        virtual ~BootLink()
        {
        }
};

/** Boot's copy of the intrusive list sentinel, with vtable D_170E80 in main data. */
class BootListSentinel : public BootLink
{
    public:
        /** @brief Clear the intrusive links. */
        BootListSentinel() : previous(0), next(0)
        {
        }

        /** @brief Destroy the list sentinel and its virtual root. */
        virtual ~BootListSentinel()
        {
        }

        BootListSentinel* previous;
        BootListSentinel* next;
};

/** Boot's copy of the 0x14-byte owned list object, with vtable D_170E90 in main data. */
class BootListObject : public BootListSentinel
{
    public:
        /** @brief Clear the object flags and its owner after initializing the links. */
        BootListObject() : is_listed(0), unk0f(0), owner(0)
        {
        }

        /** @brief Detach from the owner, then destroy the intrusive links. */
        virtual ~BootListObject()
        {
            lib_object_detach_owner(this);
        }

        /**
         * @brief Report the list kind used when registration requests the default.
         * @return Three in the base implementation.
         */
        virtual s32 get_default_list_kind();

        /** @brief Delete the object through its virtual destructor; null is ignored. */
        virtual void destroy();

        /** @brief Advance this registered object's state; the owning list's update pass calls it. */
        virtual void update();

        /** @brief Virtual slot 4; the base implementation does nothing. */
        virtual void render();

        s16 list_kind;
        u8 is_listed;
        u8 unk0f;
        void* owner;
};

/** Partial 0x880-byte Lib projection object; boot calls the Lib constructor. */
class BootProjectionACD0 : public BootListObject
{
    public:
        /**
         * @brief Initialize the projection; boot calls the Lib constructor.
         * @param display Display the projection draws to.
         */
        BootProjectionACD0(BootDimensionsACD0* display);

        /**
         * @brief Set the position.
         * @param x First component.
         * @param y Second component.
         * @param z Third component.
         */
        virtual void set_translation(float x, float y, float z);

        u8 unk14[0x23C];
        float unk250;
        u8 unk254[8];
        float unk25C;
        u8 unk260[0x18];
        float unk278;
        u8 unk27C[0x604];
};

/** Boot's copy of the position transform, with vtable D_170D60 in main data. */
class BootPositionTransform : public BootListObject
{
    public:
        /** @brief Destroy the transform. */
        virtual ~BootPositionTransform()
        {
        }

        /**
         * @brief Set the position and a w component of one.
         * @param x First component.
         * @param y Second component.
         * @param z Third component.
         */
        virtual void set_translation(float x, float y, float z);

        /**
         * @brief Copy the position.
         * @param value Source vector.
         */
        virtual void set_translation_vector(const BootVector4DDAA0* value);

        /**
         * @brief Copy the position.
         * @param value Source vector.
         */
        virtual void copy_translation(const BootVector4DDAA0* value);

        u8 unk14[0xC];
        BootVector4DDAA0 unk20;
};

/** Boot's copy of the position, rotation and scale transform, with vtable D_170D90 in main data. */
class BootTransform : public BootPositionTransform
{
    public:
        /** @brief Initialize the transform; boot calls the Lib copy of this constructor. */
        BootTransform();

        /** @brief Destroy the transform. */
        virtual ~BootTransform()
        {
        }

        /**
         * @brief Set the position and a w component of one, and mark the transform dirty.
         * @param x First component.
         * @param y Second component.
         * @param z Third component.
         */
        virtual void set_translation(float x, float y, float z);

        /**
         * @brief Copy the position and mark the transform dirty.
         * @param value Source vector.
         */
        virtual void set_translation_vector(const BootVector4DDAA0* value);

        /**
         * @brief Copy the position and mark the transform dirty.
         * @param value Source vector.
         */
        virtual void copy_translation(const BootVector4DDAA0* value);

        /**
         * @brief Convert three rotation components into the rotation vector and mark the transform dirty.
         * @param x First component.
         * @param y Second component.
         * @param z Third component.
         */
        virtual void set_rotation(float x, float y, float z);

        /**
         * @brief Convert a rotation into the rotation vector and mark the transform dirty.
         * @param value Source rotation.
         */
        virtual void set_rotation_vector(const BootVector4DDAA0* value);

        /**
         * @brief Convert a rotation into the rotation vector and mark the transform dirty.
         * @param value Source rotation.
         */
        virtual void convert_rotation(const BootVector4DDAA0* value);

        /**
         * @brief Copy the rotation vector and mark the transform dirty.
         * @param value Source vector.
         */
        virtual void set_orientation(const BootVector4DDAA0* value);

        /**
         * @brief Copy the rotation vector and mark the transform dirty.
         * @param value Source vector.
         */
        virtual void copy_orientation(const BootVector4DDAA0* value);

        /**
         * @brief Set all four rotation components and mark the transform dirty.
         * @param x First component.
         * @param y Second component.
         * @param z Third component.
         * @param w Fourth component.
         */
        virtual void set_orientation_components(float x, float y, float z, float w);

        /**
         * @brief Set the scale's xyz components and mark the transform dirty.
         * @param x First component.
         * @param y Second component.
         * @param z Third component.
         */
        virtual void set_scale(float x, float y, float z);

        /**
         * @brief Copy the scale vector and mark the transform dirty.
         * @param value Source vector.
         */
        virtual void set_scale_vector(const BootVector4DDAA0* value);

        /**
         * @brief Copy the scale vector and mark the transform dirty.
         * @param value Source vector.
         */
        virtual void copy_scale(const BootVector4DDAA0* value);

        BootVector4DDAA0 unk30;
        BootVector4DDAA0 unk40;

        /** Nonzero when the transformation matrices need rebuilding. */
        u8 transform_dirty;

        u8 unk51;
};

extern "C" u32 D_001B65BC;
extern "C" u8 D_001B65C0;

/** Bits of BootTransformOwner::draw_flags. */
enum
{
    /** Don't draw the object. */
    BOOT_DRAW_HIDDEN = 0x0001,
    BOOT_DRAW_FLAG_0010 = 0x0010,
    BOOT_DRAW_FLAG_0400 = 0x0400
};

/** Boot's view of the transform owner with the shared vtable D_178A90 in main data. */
class BootTransformOwner : public BootTransform
{
    public:
        /** @brief Initialize the owner's state bytes and tracking words. */
        inline BootTransformOwner();

        /** @brief Remove this object's mask from the resident flags, then destroy the transform. */
        virtual ~BootTransformOwner()
        {
            u32 mask = ~unk8c;
            u32 previous = D_001B65BC;
            unk8c &= mask;
            D_001B65BC &= mask;

            if (previous != D_001B65BC)
            {
                D_001B65C0 = 1;
            }
        }

        /** @brief Virtual slot 4; the owner's implementation does nothing. */
        virtual void render();

        /** @brief Detach and queue the owner; boot uses the Lib implementation. */
        virtual void destroy();

        /** @brief Clear the byte at offset 0x60. */
        virtual void func_001E0860();

        /**
         * @brief Default output handler.
         * @param output Opaque output object.
         * @return Zero.
         */
        virtual s32 func_001E0880(void* output);

        /**
         * @brief Test the supplied value.
         * @param value Value to test.
         * @param mode Additional mode used by derived implementations.
         * @return Whether the value is negative.
         */
        virtual bool func_001E0890(float value, float mode);

        /**
         * @brief Return the shared fallback vector.
         * @return Vector pointer.
         */
        virtual const BootVector4DDAA0* func_001E08B0();

        /**
         * @brief Default matrix handler; does nothing.
         * @param matrix Matrix supplied by the caller.
         * @param context Opaque caller context.
         */
        virtual void build_packet(const void* matrix, void* context);

        /** @brief Mark the matrix state ready; boot uses the Lib implementation. */
        virtual void update_transform_matrix();

        /**
         * @brief Read the stored transformation matrix; boot uses the Lib implementation.
         * @return Matrix pointer.
         */
        virtual const void* get_transform_matrix();

        /**
         * @brief Copy the source transformation state; boot uses the Lib implementation.
         * @param source Transform source.
         */
        virtual void copy_transform_state(const BootTransformOwner* source);

        /**
         * @brief Produce a transformation receiver.
         * @return Null.
         */
        virtual BootTransformOwner* func_001E08D0();

        /** @brief Default hook; does nothing. */
        virtual void func_001E08E0();

        /**
         * @brief Set the draw flags (BOOT_DRAW_*).
         * @param value New flags.
         */
        inline void set_draw_flags(u16 value);

        /**
         * @brief Store the halfword at offset 0x6C.
         * @param value Value to store.
         */
        inline void func_001DFE40(u16 value);

        u8 unk60;
        u8 matrix_ready;
        u8 unk62;
        u8 unk63;
        u8 dma_pending;
        u8 unk65;
        u8 unk66;
        u8 unk67;
        u8 unk68;
        u8 unk69;
        u16 draw_flags;
        u16 unk6c;
        u8 unk6e[0x12];
        void* unk80;
        u8 unk84[4];
        u32 unk88;
        u32 unk8c;
};

/** Boot's copy of the transform subclass between D_178A90 and D_174610, with vtable D_170DE0 in main data. */
class BootClass170DE0 : public BootTransformOwner
{
    public:
        /** @brief Destroy the transform subclass. */
        virtual ~BootClass170DE0()
        {
        }
};

/** Boot's copy of the two-callback DMA interface, with vtable D_170D50 in main data. */
class BootDmaCallbacks
{
    public:
        /** @brief Install the interface's vtable. */
        inline BootDmaCallbacks();

        /**
         * @brief Default DMA notification hook; does nothing.
         * @param value Notification value.
         */
        virtual void on_packet_notify(u32 value);

        /**
         * @brief Default preparation hook; does nothing.
         * @param value Notification word or packet address.
         */
        virtual void on_packet_complete(u32 value);
};

/** Boot's view of the transform with callback interface, with the shared vtable D_174610 in main data. */
class BootCallbackTransform : public BootClass170DE0, public BootDmaCallbacks
{
    public:
        /** @brief Initialize the transform and callback interface; boot calls the Lib constructor. */
        BootCallbackTransform();

        /** @brief Destroy the transform receiver. */
        virtual ~BootCallbackTransform()
        {
        }

        /**
         * @brief Run the default transform state hook.
         * @param first First state value.
         * @param second Second state value.
         * @param third Third state value.
         */
        virtual void func_0044B100(u32 first, u32 second, u32 third);

        u8 unk94[0x1A];
        u8 unkae;
        u8 unkaf;
};

/** Boot's view of the 0x14-byte list receiver with the shared vtable D_178A70 in main data. */
class BootListReceiver
{
    public:
        BootListSentinel sentinel;
        u32 node_count;

        /** @brief Initialize the list receiver; boot calls the Lib constructor. */
        BootListReceiver();

        /** @brief Destroy the list receiver. */
        virtual ~BootListReceiver();

        /**
         * @brief Append a node to the end of the list.
         * @param node Node to append.
         */
        virtual void append(void* node);

        /**
         * @brief Prepend a node to the beginning of the list.
         * @param node Node to prepend.
         */
        virtual void prepend(void* node);

        /**
         * @brief Link a node after a list position.
         * @param position Insertion position.
         * @param node Node to insert.
         */
        virtual void insert_after(void* position, void* node);

        /**
         * @brief Unlink a node and clear its list links.
         * @param node Node to remove.
         */
        virtual void unlink(void* node);
};

/** Resident manager list that updates its nodes, with the Lib vtable D_178DD0. */
class BootUpdateList : public BootListReceiver
{
    public:
        /** @brief Destroy the manager list. */
        virtual ~BootUpdateList();

        /**
         * @brief Remove a node.
         * @param object Node to remove.
         */
        virtual void remove_node(void* object);

        /** @brief Update every node. */
        virtual void update_nodes();

        /**
         * @brief Append a node of a kind.
         * @param object Node.
         * @param kind Node kind, or -1 for the node's default.
         */
        virtual void append_node(void* object, s32 kind);

        /**
         * @brief Prepend a node of a kind.
         * @param object Node.
         * @param kind Node kind, or -1 for the node's default.
         */
        virtual void prepend_node(void* object, s32 kind);
};

/** Partial resident display manager D_001B6628 with the Lib vtable D_178F30. */
class BootDisplayManager : public BootUpdateList
{
    public:
        u8 unk14[0x7C];

        /** Display object the manager draws through. */
        void* current_display;
};

extern "C" BootDisplayManager* D_001B6628;

/** Boot's view of the 0xF0-byte container with the Lib vtable D_178660. */
class BootContainer : public BootListReceiver, public BootCallbackTransform
{
    public:
        /**
         * @brief Initialize the container with its mode and transform.
         * @param code Container mode.
         * @param x First transform component.
         * @param y Second transform component.
         * @param z Third transform component.
         */
        BootContainer(s32 code, float x, float y, float z)
        {
            unk6c = 0x6FF1;
            lib_container_init(this, code, x, y, 0, z, 0);
        }

        /** @brief Destroy the container. */
        virtual ~BootContainer();

        LibStorageBlock0C unkd0;
        u8 unkdc[0x14];
};

/** Four words cleared by an out-of-line constructor. */
class BootWordQuad
{
    public:
        /** @brief Clear all four words. */
        inline BootWordQuad();

        u32 unk00;
        u32 unk04;
        u32 unk08;
        u32 unk0c;
};

/** Partial 0xC0-byte transform with the Lib vtable D_179150. */
class BootClass179150 : public BootTransformOwner, public BootDmaCallbacks
{
    public:
        /** @brief Initialize the transform's modes and timing. */
        BootClass179150()
        {
            func_4E32F0(this);
            unk94 = 0x80000000;
            unk9c = 0x80000000;
            unk98 = 0;
            unka4 = 30.0f;
            func_001DFE40(0x300);
            unk65 = 1;
            set_draw_flags(BOOT_DRAW_FLAG_0400);
        }

        /** @brief Destroy the transform. */
        virtual ~BootClass179150();

        u32 unk94;
        u32 unk98;
        u32 unk9c;
        u8 unka0[4];
        float unka4;
        BootWordQuad unka8;
        u8 unkb8[8];
};

/** Partial 0xC0-byte Lib transform with vtable D_171DD0 in main data; boot calls its Lib constructor. */
class BootClipRegion : public BootTransformOwner, public BootDmaCallbacks
{
    public:
        /** @brief Initialize the object; boot calls the Lib constructor. */
        BootClipRegion();

        /** @brief Destroy the object. */
        virtual ~BootClipRegion();

        BootDimensionsACD0* display;
        void* unk98;
        u8 unk9c[8];
        s32 left;
        s32 top;
        s32 right;
        s32 bottom;
        u8 unkb4[0xC];
};

/** Partial 0xF0-byte selection cursor with the Lib vtable D_175070. */
class BootSelectionCursor : public BootCallbackTransform, public ItemCreationClass185050
{
    public:
        /** @brief Initialize the cursor transform. */
        BootSelectionCursor()
        {
            unk6c = 0x6FF0;
        }

        /** @brief Destroy the cursor. */
        virtual ~BootSelectionCursor();
};

/** Boot's view of the 0xFC-byte Lib drawing widget with vtable D_174EF0. */
class BootDrawWidget : public BootListObject
{
    public:
        /** @brief Initialize the widget; boot calls the Lib constructor. */
        BootDrawWidget();

        /** @brief Destroy the widget. */
        virtual ~BootDrawWidget();

        /**
         * @brief Set the draw color and mark the widget visible.
         * @param color Packed color.
         */
        void set_color(u32 color)
        {
            draw_color = color;
            needs_redraw = 1;
        }

        /**
         * @brief Set the text scale and mark the widget for redraw.
         * @param scale Scale factor.
         */
        void set_scale(float scale)
        {
            draw_scale = scale;
            needs_redraw = 1;
        }

        /**
         * @brief Set the alpha and mark the widget for redraw.
         * @param alpha Alpha, 128 for opaque.
         */
        void set_alpha(float alpha)
        {
            draw_alpha = alpha;
            needs_redraw = 1;
        }

        /**
         * @brief Set the color the widget is modulated by and mark it for redraw.
         * @param color Packed color, 0x808080 for unchanged.
         */
        void set_tint(u32 color)
        {
            tint = color;
            needs_redraw = 1;
        }

        /**
         * @brief Set the horizontal alignment and mark the widget for redraw.
         * @param align Alignment.
         */
        void set_horizontal_align(s32 align)
        {
            horizontal_align = align;
            needs_redraw = 1;
        }

        /**
         * @brief Set the vertical alignment and mark the widget for redraw.
         * @param align Alignment.
         */
        void set_vertical_align(s32 align)
        {
            vertical_align = align;
            needs_redraw = 1;
        }

        u8 unk14[0x14];
        float draw_alpha;
        u8 unk2c[0xC];
        u8 unk38;
        u8 unk39[3];
        u8 needs_redraw;
        u8 unk3d[2];
        u8 visible;
        u8 unk40[0x40];
        float draw_scale;
        u8 unk84[0x10];
        u32 tint;
        u32 draw_color;
        s32 horizontal_align;
        s32 vertical_align;
        u8 unka4[0x58];
};

/** Boot's view of the 0x114-byte Lib text widget with vtable D_178750. */
class BootTextWidget : public BootDrawWidget
{
    public:
        /**
         * @brief Initialize the text widget with a resource string and rectangle.
         * @param slot Resource slot.
         * @param key Resource key.
         * @param flag Slot state flag.
         * @param x Origin x.
         * @param y Origin y.
         * @param width Rectangle width.
         * @param height Rectangle height.
         */
        BootTextWidget(s32 slot, s32 key, u8 flag, float x, float y, float width, float height)
        {
            unk38 = 11;
            lib_text_init_resource_rectangle(this, slot, key, flag, x, y, width, height);
        }

        /** @brief Destroy the text widget. */
        virtual ~BootTextWidget();

        u8 unkfc[0x18];
};

/** Boot's view of the 0x40-byte Lib widget base with vtable D_178600; boot calls the Lib constructor. */
class BootWidget : public BootListObject
{
    public:
        /** @brief Initialize the widget rectangle and state bytes. */
        BootWidget();

        /** @brief Destroy the widget. */
        virtual ~BootWidget();

        u8 unk14[0x24];
        u8 unk38;
        u8 unk39[3];
        u8 unk3c;
        u8 unk3d[3];
};

/** Boot's view of the 0x58-byte Lib list indicator with vtable D_1725D0, a bar showing how far a list is scrolled. */
class BootListIndicator : public BootWidget
{
    public:
        /**
         * @brief Select widget kind 3, then place the indicator and set its scroll extent and position.
         * @param x Horizontal position.
         * @param y Vertical position.
         * @param height Bar height.
         * @param extent Size of one scroll step, as a share of the bar.
         * @param position Scroll position.
         */
        BootListIndicator(float x, float y, float height, float extent, float position)
        {
            unk38 = 3;
            lib_list_indicator_init(this, x, y, height, extent, position);
        }

        /** @brief Destroy the indicator. */
        virtual ~BootListIndicator();

        /**
         * @brief Set the scroll position and mark the indicator for redraw.
         * @param value Position, from 0 to 100.
         */
        void set_position(float value)
        {
            position = value;
            unk3c = 1;
        }

        LibStorageBlock0C unk40;
        u8 unk4c[4];
        float unk50;

        /** Scroll position, from 0 to 100. */
        float position;
};

/** Four floats of a panel rectangle. */
struct BootPanelRect50
{
    float unk00;
    float unk04;
    float unk08;
    float unk0c;
};

/** Boot's view of the 0x90-byte Lib panel with vtable D_178630. */
class BootPanel : public BootWidget
{
    public:
        /**
         * @brief Initialize the panel state and drawing rectangle.
         * @param mode Drawing mode.
         * @param x Horizontal position.
         * @param y Vertical position.
         * @param width Drawing width.
         * @param height Drawing height.
         * @param extra Extra drawing coordinate.
         */
        BootPanel(s32 mode, float x, float y, float width, float height, float extra)
        {
            unk50.unk0c = 0.0f;
            unk50.unk08 = 0.0f;
            unk50.unk04 = 0.0f;
            unk50.unk00 = 0.0f;
            unk38 = 1;
            lib_panel_init_rectangle(this, mode, x, y, width, height, extra);
        }

        /** @brief Destroy the panel. */
        virtual ~BootPanel();

        LibStorageBlock0C unk40;
        u8 unk4c[4];
        BootPanelRect50 unk50;
        void* unk60;
        u8 unk64[0x2C];
};

class BootPacketBuffer;

/** Partial 0x210-byte Lib image strip with vtable D_1735A0 in main data; boot calls the Lib constructor. */
class BootImageStrip : public BootTransformOwner, public BootDmaCallbacks
{
    public:
        /** @brief Construct the strip. */
        BootImageStrip();

        u8 unk94[0x17C];
};

/** 0xE0-byte screen fade with vtable D_171C00 in main data: ten strips copied from the display, faded out. */
class BootScreenFade : public BootTransformOwner, public BootDmaCallbacks
{
    public:
        /**
         * @brief Copy the display into ten strips and show them, fully opaque.
         * @param display Display to copy.
         */
        BootScreenFade(BootDimensionsACD0* display);

        /** @brief Destroy the strips, the copy buffer and the packet. */
        virtual ~BootScreenFade();

        /** @brief Fade out; once transparent, destroy the strips and the fade. */
        virtual void update();

        /** @brief Mark the fade active and submit its packet. */
        virtual void render();

        /** @brief Set the byte at offset 0x60 to 10. */
        virtual void func_001E0860();

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

        BootImageStrip* images[10];
        u8* buffer;
        BootDimensionsACD0* display;
        BootPacketBuffer* packet;
        u8 armed;
        u8 unkc9[3];
        float alpha;
        float fade_speed;
        u8 unkd4[0xC];
};

class BootScene;

/**
 * Title menu, with vtable D_171BB0 in main data: a Lib scene from resources 0x27 and 0xA whose nodes are the New Game,
 * Continue, Battle Collection and Install entries.
 */
class BootTitleMenu : public BootListObject
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

        BootScene* scene;
        s32 step;

        /** The scene's camera node, made the current display. */
        void* camera;

        /** Arrow beside the selected item. */
        class BootSelectionCursor* cursor;

        u8* scene_data;

        /** Selected item: 0 New Game, 1 Continue, 2 Battle Collection, 3 Install. */
        u8 selected;

        u8 unk29;

        /** Nonzero while the selected item's color brightens again. */
        u8 pulse_up;

        /** Nonzero when a memory card holds a save to continue. */
        u8 continue_ready;

        u8 unk2c;

        /** Nonzero when a memory card holds Battle Collection data. */
        u8 collection_ready;

        u8 unk2e[2];
        u8* unk30;

        /** Item to select first, or -1 to choose from the memory cards. */
        s32 initial_item;

        /** Seconds on the menu without a choice; the opening movie plays again after 45. */
        float idle_time;
};

class BootResident113E40;
class BootMoviePlayer;

/**
 * Starts the game, with vtable D_171CB0 in main data. On a new game with Dolby Pro Logic II output it first plays
 * movie 13, then loads resource 0x42B and hands it to the boot program to run next.
 */
class BootGameLauncher : public BootListObject
{
    public:
        /** @brief Clear the state and allocate the 0x12000-byte work buffer. */
        BootGameLauncher();

        /** @brief Release the player, its heap and the work buffer. */
        virtual ~BootGameLauncher();

        /** @brief Run the launch steps: seed, movie, load, hand over. */
        virtual void update();

        /** Resource 0x42B, the program to run next. */
        u8* program;

        u8* buffer;
        s32 step;
        s32 timer;
        BootResident113E40* movie_heap;
        BootMoviePlayer* player;
};

class BootModel;

/** Partial 0x2C-byte progress bar with vtable D_171BD0 in main data; driven with a done/total pair. */
class BootProgressBar : public BootListObject
{
    public:
        /** @brief Initialize the progress bar. */
        BootProgressBar();

        /** @brief Destroy the bar's model, then the bar. */
        virtual ~BootProgressBar();

        /** @brief Detach the bar and its model, destroy the model and delete the bar. */
        virtual void destroy();

        class LibDrawBuffer* draw_buffer;
        BootModel* model;
        s32 width;
        s32 height;
        u32 color;
        s32 mode;
};

/** Boot's view of the Lib model base that adds a matrix and three vectors, with the Lib vtable D_172080. */
class BootModelBase : public BootTransformOwner
{
    public:
        /** @brief Destroy the model base; boot uses the Lib implementation. */
        virtual ~BootModelBase();

        /** @brief Rebuild the transformation matrix; boot uses the Lib implementation. */
        virtual void update_transform_matrix();

        /**
         * @brief Read the transformation matrix.
         * @return The matrix.
         */
        virtual const void* get_transform_matrix()
        {
            return &unk90;
        }

        /**
         * @brief Read the first stored vector.
         * @return Vector at offset 0x1D0.
         */
        virtual const BootVector4DDAA0* func_001E9560() const
        {
            return &unk1D0;
        }

        /**
         * @brief Read the second stored vector.
         * @return Vector at offset 0x1E0.
         */
        virtual const BootVector4DDAA0* func_001E9570() const
        {
            return &unk1E0;
        }

        /**
         * @brief Read the third stored vector.
         * @return Vector at offset 0x1F0.
         */
        virtual const BootVector4DDAA0* func_001E9580() const
        {
            return &unk1F0;
        }

        /**
         * @brief Copy another model's state; boot uses the Lib implementation.
         * @param source Model to copy.
         */
        virtual void func_4D9F40(const BootModelBase* source);

        BootMatrix92D0 unk90;
        BootMatrix92D0 unkD0;
        u8 unk110[0xC0];
        BootVector4DDAA0 unk1D0;
        BootVector4DDAA0 unk1E0;
        BootVector4DDAA0 unk1F0;
        u8 unk200[8];
        s32 unk208;
        u8 unk20C[4];
        u8 unk210;
};

/** Boot's view of the Lib model with color factors, with the Lib vtable D_174310. */
class BootColorModel : public BootModelBase
{
    public:
        /** @brief Destroy the model; boot uses the Lib implementation. */
        virtual ~BootColorModel();

        /** @brief Detach and queue the model; boot uses the Lib implementation. */
        virtual void destroy();

        /**
         * @brief Store the byte at offset 0x210 and set its flag.
         * @param value Byte to store.
         */
        virtual void func_001E94E0(u8 value)
        {
            unk210 = value;
            unk59d_3 = 1;
        }

        /**
         * @brief Copy another model's byte at offset 0x210 and its Lib state.
         * @param source Model to copy.
         */
        virtual void func_001E9500(const BootColorModel* source)
        {
            func_001E94E0(source->unk210);
            BootModelBase::func_4D9F40(source);
        }

        /** @brief Store the component product of the two input vectors. */
        virtual void update_combined_color_factor();

        /**
         * @brief Store the color modulation, then recompute the combined color factor.
         * @param key Caller's key; unused here.
         * @param modulation Color modulation to store.
         */
        virtual void set_color_modulation(s32 key, const BootVector4DDAA0* modulation)
        {
            copy_vector(&color_modulation, modulation);
            update_combined_color_factor();
        }

        /**
         * @brief Read the color modulation.
         * @return Vector at offset 0x570.
         */
        virtual const BootVector4DDAA0* get_color_modulation() const
        {
            return &color_modulation;
        }

        /** @brief Virtual slot 0x98; boot uses the Lib implementation. */
        virtual void func_slot98();

        /** @brief Virtual slot 0x9C; boot uses the Lib implementation. */
        virtual void func_448180();

        u8 unk220[0x340];
        BootVector4DDAA0 base_color_factor;
        BootVector4DDAA0 color_modulation;
        BootVector4DDAA0 combined_color_factor;
        u8 unk590[0xD];
        u8 unk59d_0_2 : 3;
        u8 unk59d_3 : 1;
        u8 unk59d_4_7 : 4;
        u8 unk59e[2];
        u8 unk5a0;
        u8 unk5a1[3];

        /** Child objects, such as the face's morph targets. */
        BootListSentinel children;

        u8 unk5b0[0x84];
        void* unk634;
        u8 unk638[8];
};

/** Boot's view of the Lib model base that adds five more slots; no vtable of its own appears in main data. */
class BootModelPrimaryBase : public BootColorModel
{
    public:
        /** @brief Destroy the model; boot uses the Lib implementation. */
        virtual ~BootModelPrimaryBase();

        /** @brief Virtual slot 0xA0; boot uses the Lib implementation. */
        virtual void func_4A3F50();

        /** @brief Virtual slot 0xA4; boot uses the Lib implementation. */
        virtual void func_4A3EC0();

        /** @brief Virtual slot 0xA8; boot uses the Lib implementation. */
        virtual void func_4A3E50();

        /**
         * @brief Virtual slot 0xAC.
         * @return Nonzero when set.
         */
        virtual s32 func_001E9460();

        /**
         * @brief Virtual slot 0xB0.
         * @return Byte pointer.
         */
        virtual u8* func_001E9470();
};

/** Boot's view of the Lib model's second base at offset 0x640. */
class BootModelSecondaryBase
{
    public:
        /** @brief First secondary slot. */
        virtual void func_4A4510();

        /** @brief Second secondary slot. */
        virtual void func_4A4550();
};

/** Boot's view of the Lib model with vtable D_177820; boot calls its Lib constructor and destructor. */
class BootModel : public BootModelPrimaryBase, public BootModelSecondaryBase
{
    public:
        /** @brief Construct an empty model; boot uses the Lib implementation. */
        BootModel();

        /** @brief Destroy the model; boot uses the Lib implementation. */
        virtual ~BootModel();

        /** @brief Detach the attached object when the gate is set, then destroy the model through its base. */
        virtual void destroy()
        {
            if (unk5a0 != 0 && unk634 != 0)
            {
                func_4D5C90(unk634);
            }

            BootColorModel::destroy();
        }

        /** @brief Advance the model; boot uses the Lib implementation. */
        virtual void update();

        /** @brief Virtual slot 4; boot uses the Lib implementation. */
        virtual void render();

        /** @brief Boot uses the Lib implementation. */
        virtual void func_001E0860();

        /**
         * @brief Boot uses the Lib implementation.
         * @param output Opaque output object.
         * @return Lib result.
         */
        virtual s32 func_001E0880(void* output);

        /**
         * @brief Boot uses the Lib implementation.
         * @param value Value to test.
         * @param mode Mode.
         * @return Lib result.
         */
        virtual bool func_001E0890(float value, float mode);

        /**
         * @brief Boot uses the Lib implementation.
         * @return Vector pointer.
         */
        virtual const BootVector4DDAA0* func_001E08B0();

        /**
         * @brief Apply a matrix; boot uses the Lib implementation.
         * @param matrix Matrix supplied by the caller.
         * @param context Opaque caller context.
         */
        virtual void build_packet(const void* matrix, void* context);

        /**
         * @brief Boot uses the Lib implementation.
         * @return Transformation receiver.
         */
        virtual BootTransformOwner* func_001E08D0();

        /** @brief Boot uses the Lib implementation. */
        virtual void func_001E08E0();

        /** @brief Virtual slot 0x98; boot uses the Lib implementation. */
        virtual void func_slot98();

        /**
         * @brief Check whether the word at offset 0x704 is nonzero.
         * @return One if nonzero, otherwise zero.
         */
        virtual s32 func_001E9460()
        {
            return unk704 != 0;
        }

        /**
         * @brief Return the address of the bytes at offset 0x79C.
         * @return Pointer to the bytes.
         */
        virtual u8* func_001E9470()
        {
            return unk79c;
        }

        /**
         * @brief Return zero.
         * @return Always 0.
         */
        virtual s32 func_001E9400()
        {
            return 0;
        }

        /**
         * @brief Return zero.
         * @return Always 0.
         */
        virtual s32 func_001E9410()
        {
            return 0;
        }

        /**
         * @brief Return the supplied value.
         * @param value Value to return.
         * @return The supplied value.
         */
        virtual s32 func_001E9420(s32 value)
        {
            return value;
        }

        /**
         * @brief Return the supplied value.
         * @param value Value to return.
         * @return The supplied value.
         */
        virtual s32 func_001E9430(s32 value)
        {
            return value;
        }

        /**
         * @brief Return zero.
         * @return Always 0.
         */
        virtual s32 func_001E9440()
        {
            return 0;
        }

        /**
         * @brief Return zero.
         * @return Always 0.
         */
        virtual s32 func_001E9450()
        {
            return 0;
        }

        /** @brief First secondary slot; boot uses the Lib implementation. */
        virtual void func_4A4510();

        /** @brief Second secondary slot; boot uses the Lib implementation. */
        virtual void func_4A4550();

        /**
         * @brief Return the byte at offset 0x794.
         * @return The stored byte.
         */
        virtual u8 func_001E9480()
        {
            return unk794;
        }

        /**
         * @brief Build this model from a model in a loaded scene; boot uses the Lib implementation.
         * @param links Display list the model draws through.
         * @param source Scene model to copy.
         */
        virtual void func_4A37C0(BootUpdateList* links, BootClass170F30* source);

        /** @brief Boot uses the Lib implementation. */
        virtual void func_4A7E80();

        /** @brief Boot uses the Lib implementation. */
        virtual void func_4A4ED0();

        /**
         * @brief Return zero.
         * @return Always 0.
         */
        virtual s32 func_001E9490()
        {
            return 0;
        }

        u8 unk644[0xC0];
        u32 unk704;
        u8 unk708[0x8C];
        u8 unk794;
        u8 unk795[7];
        u8 unk79c[0x84];
};

/** Partial model object with vtable D_170F30 in main data. */
class BootClass170F30 : public BootModel
{
    public:
        /** @brief Destroy the model object. */
        virtual ~BootClass170F30();

        /**
         * @brief Negate the matrix's second vector, then apply the matrix through the Lib model.
         * @param matrix Matrix supplied by the caller.
         * @param context Opaque caller context.
         */
        virtual void build_packet(const void* matrix, void* context);
};

/** Block of a texture resource that holds its size; the width and height are powers of two. */
struct BootTextureImage
{
    u8 unk00[8];

    /** Offset of the pixel block from the texture header. */
    u32 pixel_offset;

    u8 unk0C[2];
    u8 width_log2;
    u8 height_log2;
};

/** Header of a texture resource; the image block sits image_offset bytes after it. */
struct BootTextureHeader
{
    u8 unk00[4];
    char name[4];
    s32 id;
    u32 image_offset;
    u8 unk10[4];

    /** Offset of the palette block from the texture header. */
    u32 palette_offset;
};

/** Partial texture resource with its header after a 0x10-byte prefix. */
struct BootTextureResource
{
    u8 unk00[0x10];
    BootTextureHeader header;
};

/**
 * @brief Return the size block of a texture resource.
 * @param resource Texture resource.
 * @return Its size block.
 */
static inline const BootTextureImage* texture_image(const BootTextureResource* resource)
{
    const BootTextureHeader* header = &resource->header;
    return (const BootTextureImage*)((const u8*)header + header->image_offset);
}

/** Partial 0x30-byte image object with vtable D_171C90 in main data, drawn from a decoded FIS image. */
class BootImage : public BootListObject
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
        void set_texture(const BootTextureResource* texture, const BootTextureResource* palette);

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
        BootModel* model;

        /** Texture width in texels. */
        s32 texture_width;

        /** Texture height in texels. */
        s32 texture_height;

        s32 palette_width;
        s32 palette_height;
        u8 unk2c;

        /** Nonzero to center the quad on the model's origin; otherwise its top-left corner sits there. */
        u8 centered;

        /** Nonzero once a palette has been uploaded. */
        u8 has_palette;
};

/**
 * Popup with vtable D_171070 in main data that tells the player to fix the PlayStation BB Unit while the resident
 * loader reports an error, and removes itself once the error clears.
 */
class BootUnitErrorPopup : public BootListObject
{
    public:
        /**
         * @brief Start enabled, with nothing shown.
         * @param owner Program whose message bank the popup uses.
         */
        BootUnitErrorPopup(class BootProgram* owner)
        {
            program = owner;
            container = 0;
            text = 0;
            panel = 0;
            enabled = 1;
        }

        /** @brief Destroy the object. */
        virtual ~BootUnitErrorPopup();

        /** @brief Release the owned objects, then queue this object for deletion. */
        virtual void destroy();

        /** @brief Show the popup while the loader reports a BB Unit error, and remove it once the error clears. */
        virtual void update();

        /**
         * @brief Turn the popup on or off.
         * @param value Nonzero to allow the popup.
         */
        virtual void set_enabled(u8 value);

        /** Program whose message bank the popup uses. */
        class BootProgram* program;

        u8 enabled;
        u8 unk19[3];
        BootContainer* container;
        BootListObject* text;

        /** Frame behind the text. */
        BootListObject* panel;
};

/** Message keys in boot's English message bank (resource 38, block 0). */
enum BootMessage
{
    BOOT_MSG_PROGRESSIVE_OFFER = 0x1,
    BOOT_MSG_PROGRESSIVE_WIDE_STARTED = 0x2,
    BOOT_MSG_PROGRESSIVE_NORMAL_STARTED = 0x7,
    BOOT_MSG_UNIT_NOT_INITIALIZED = 0x8,
    /** First of the descriptions for each page's options; see BootNewGameSettings::get_value_message. */
    BOOT_MSG_TV_NORMAL = 0xA,
    BOOT_MSG_SOUND_MONO = 0xC,
    BOOT_MSG_SPEAKER_SETUP = 0xF,
    BOOT_MSG_EVENT_SKIP_ON = 0x10,
    BOOT_MSG_VOICE_SUBTITLES_AND_SOUND = 0x12,
    BOOT_MSG_VIBRATION_ON = 0x15,
    BOOT_MSG_DIFFICULTY_EARTH = 0x17,
    BOOT_MSG_UNIVERSE_UNLOCKED = 0x1A,
    BOOT_MSG_SOUND_HEADPHONES = 0x1B,
    BOOT_MSG_VOICE_AUTO = 0x1C,
    BOOT_MSG_INSTALL_CONFIRM = 0x1E,
    BOOT_MSG_OVERWRITE_CONFIRM = 0x1F,
    BOOT_MSG_NOT_ENOUGH_SPACE = 0x20,
    BOOT_MSG_ERROR = 0x21,
    BOOT_MSG_UNIT_ERROR = 0x22,
    BOOT_MSG_INSTALLING = 0x23,
    BOOT_MSG_PERCENT = 0x24,
    BOOT_MSG_ABORT_CONFIRM = 0x25,
    BOOT_MSG_INSTALL_COMPLETE = 0x26,
    /** First of the eight battle-system tips shown while installing. */
    BOOT_MSG_FIRST_TIP = 0x28,
    BOOT_MSG_UNIT_FIX = 0x32,
    BOOT_MSG_UNIT_DATA_DELETED = 0x33,
    BOOT_MSG_FOURTH_DIMENSION_LOCKED = 0x50,
    BOOT_MSG_FOURTH_DIMENSION = 0x51,
    /** The memory card free-space warnings shown at startup. */
    BOOT_MSG_NO_CARD = 0x7D0,
    BOOT_MSG_SLOT1_FULL = 0x7D1,
    BOOT_MSG_SLOT2_FULL = 0x7D2,
    BOOT_MSG_BOTH_SLOTS_FULL = 0x7D3,
    BOOT_MSG_SLOT1_NO_TROPHY_SPACE = 0x7D5,
    BOOT_MSG_SLOT2_NO_TROPHY_SPACE = 0x7D6,
    BOOT_MSG_BOTH_SLOTS_NO_TROPHY_SPACE = 0x7D7,
    BOOT_MSG_SLOT1_NO_SAVE_SPACE = 0x7D8,
    BOOT_MSG_SLOT2_NO_SAVE_SPACE = 0x7D9,
    BOOT_MSG_BOTH_SLOTS_NO_SAVE_SPACE = 0x7DA
};

/** Resources the installer loads. */
enum BootInstallResource
{
    /** Two images: the screen sprite sheet and its banner. */
    BOOT_RES_SCREEN_IMAGES = 0x2A,
    /** SYSTEM.CNF, icon.sys and the icon written to the BB Unit partition. */
    BOOT_RES_SYSTEM_FILES = 0x2D,
    /** PlayStation BB Navigator icons and title file. */
    BOOT_RES_NAVIGATOR_FILES = 0x2E,
    /** The eight images shown with the battle-system tips. */
    BOOT_RES_TIP_IMAGES = 0x2F,
    BOOT_RES_SOUND = 0x427
};

/**
 * Boot screen that offers to install the game on the PlayStation BB Unit (hard disk), with vtable D_170D30
 * in main data. It asks yes/no, checks the unit and its free space, writes the partition files while
 * showing a progress bar and battle-system tips, then hands over to the next boot stage.
 */
class BootInstaller : public BootListObject
{
    public:
        /** @brief Allocate the boot buffers and clear the owned objects. */
        BootInstaller();

        /** @brief Release the owned objects and buffers. */
        virtual ~BootInstaller();

        /**
         * @brief Report the list kind used when registration requests the default.
         * @return Four.
         */
        virtual s32 get_default_list_kind();

        /** @brief Advance the install sequence: load the screen, ask, check the BB Unit, install, then hand over. */
        virtual void update();

        /**
         * @brief Replace the tip image with block @p index of the tip image resource.
         * @param index Tip image to decode.
         */
        void show_tip_image(s32 index);

        /** @brief Create the yes/no choice images and pulse the selected one; release them once installing starts. */
        void update_choice_images();

        /** @brief Create the four screen images once, then place them for the 4:3 or widescreen layout. */
        void place_screen_images();

        u8* screen_image_data;
        u8* sound_data;
        u8* screen_image_buffers[2];
        u8* system_file_data;
        u8* navigator_file_data;
        u8* system_file_buffers[3];
        u8* navigator_file_buffers[3];
        u8* install_buffer;
        BootImage* images[20];
        BootProgressBar* progress_bar;
        BootImage* tip_image;
        u8* tip_image_buffer;
        u8* tip_image_data;

        /** Current step of the install sequence. */
        s32 step;

        /** Step taken when the player answers no or cancels. */
        s32 no_step;

        /** Step taken when the player answers yes. */
        s32 yes_step;

        u8 selection;
        u8 screen_images_loaded;
        u8 sound_started;
        u8 exiting;

        /** Nonzero while the selected choice image grows back to full size. */
        u8 choice_growing;

        u8 unkb9[3];
        u8* unkbc;

        /** Install size used as the progress denominator. */
        s32 install_total;

        /** Next tip to show. */
        s32 tip_index;

        /** Progress percentage at which the next tip is shown. */
        s32 next_tip_percent;

        s32 menu_frames;
        s32 wait_frames;

        /** 0x200-byte buffer the resident install code fills with the icon.sys header. */
        u8* icon_header;

        BootContainer* container;
        BootTextWidget* message_text;
        BootTextWidget* progress_text;
        BootTextWidget* tip_text;
        BootSelectionCursor* cursor;
};

/** Partial loaded program image; the offset locates the copy of the main executable's code. */
struct BootProgramImage
{
    u8 unk00[0x38];
    u32 code_offset;
};

#endif

#endif
