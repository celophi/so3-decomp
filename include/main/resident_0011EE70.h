#ifndef SO3_MAIN_RESIDENT_0011EE70_H
#define SO3_MAIN_RESIDENT_0011EE70_H

#include "types.h"
#include "main/resident_0010A0E0.h"

/**
 * Partial GS packet buffer: base, allocated storage, write cursor, capacity in 64-bit words, a
 * borrowed-storage flag at offset 0x14 and a flag byte at offset 0x15.
 */
typedef struct ResidentPacket
{
    u8* unk00;
    u8* unk04;
    u8* unk08;
    u8* unk0c;
    s32 unk10;
    u8 unk14;
    u8 unk15;
} ResidentPacket;

#ifdef __cplusplus
/** Main's GS packet buffer class (vtable D_0014FDF0); its data comes before the vptr. Boot and Field have their own. */
class ResidentPacketBuffer : public ResidentPacket
{
public:
    /** @brief Free the packet storage unless it is borrowed. */
    virtual ~ResidentPacketBuffer();
};
#endif

/** Sound bank slots a ResidentClass14FC90 manages. */
#define RESIDENT_SOUND_BANK_SLOT_COUNT 3

/** Registered bank data lists per slot. */
#define RESIDENT_SOUND_BANK_LIST_COUNT 16

/** One queued bank load: which slot it fills and the file holding the picked variant. */
typedef struct ResidentSoundBankLoad
{
    u8 slot;
    u8 variant;
    u8 unk02[2];
    s32 file_key;
} ResidentSoundBankLoad;

/** One part of registered sound bank data, which starts with a word holding its part count followed by the parts. */
typedef struct ResidentSoundBankPart
{
    /** Offset of the part from the start of the data, in 2048-byte sectors. */
    u16 sector;

    u16 unk02;
} ResidentSoundBankPart;

/** The files holding each variant of one sound bank. */
typedef struct ResidentSoundBankVariants
{
    s32 count;
    const s32* file_keys;
} ResidentSoundBankVariants;

/** GIF tag: the tag word and the register list, four bits per register. */
typedef struct ResidentGifTag
{
    u64 tag;

    union
    {
        u64 registers;

        struct
        {
            u64 register0 : 4;
            u64 register1 : 4;
            u64 register2 : 4;
            u64 register3 : 4;
            u64 register4 : 4;
            u64 register5 : 4;
            u64 unused : 40;
        } fields;
    };
} ResidentGifTag;

/** One GS register write in A+D (address plus data) form. */
typedef struct ResidentGsRegisterWrite
{
    ResidentGifTag tag;
    u64 data;
    u64 address;
} ResidentGsRegisterWrite;

/** Packed GIF tag, PRIM, colour and two XYZ2 vertices drawing one line. */
typedef struct ResidentLinePacket
{
    ResidentGifTag tag;
    u64 prim;
    u32 rgba;
    u32 q;
    u64 vertices[2];
} ResidentLinePacket;

/** Packed GIF tag, PRIM, colour and four XYZ2 vertices drawing one filled rectangle as a triangle strip. */
typedef struct ResidentRectanglePacket
{
    ResidentGifTag tag;
    u64 prim;
    u32 rgba;
    u32 q;
    u64 vertices[4];
} ResidentRectanglePacket;

/** Display context holding the signed viewport size; the packet builders centre vertices on the GS drawing area. */
typedef struct ResidentDisplayContext
{
    u8 unk00[0x3C6C];
    s16 viewport_width;
    s16 viewport_height;
} ResidentDisplayContext;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize both resident release rings as empty.
 * @param queues Release queues to initialize.
 * @return The initialized queues.
 */
ResidentReleaseQueues* resident_initialize_release_queues(ResidentReleaseQueues* queues);

/**
 * @brief Move the set state from byte 0x25 to byte 0x24 when set.
 * @param object Object containing the state bytes.
 */
void func_0011F9B0(void* object);

/**
 * @brief Append a GIF A+D write of one GS register when the packet has room.
 * @param packet Packet to append to.
 * @param address GS register address.
 * @param data Register value.
 */
void func_0011EF00(ResidentPacket* packet, u64 address, u64 data);

/**
 * @brief Append a GIF A+D write of the GS PRIM register when the packet has room.
 * @param packet Packet to append to.
 * @param data Register value.
 */
void func_0011EF90(ResidentPacket* packet, u64 data);

/**
 * @brief Append a GIF A+D write of the GS ALPHA_2 register when the packet has room.
 * @param packet Packet to append to.
 * @param data Register value.
 */
void func_0011F140(ResidentPacket* packet, u64 data);

/**
 * @brief End the packet's pending data with a GIF end tag and send it on DMA channel 2.
 * @param packet Packet buffer to submit.
 * @param notification Object notified when the transfer finishes, or null.
 */
void resident_packet_submit(ResidentPacket* packet, void* notification);

/**
 * @brief Advance the packet cursor to the next 16-byte boundary at or after a supplied cursor.
 * @param packet Packet to update.
 * @param cursor Requested cursor.
 * @return Rounded cursor.
 */
u8* resident_packet_align_cursor(ResidentPacket* packet, u8* cursor);

/**
 * @brief Get the current packet cursor when a requested range fits.
 * @param packet Packet to inspect.
 * @param quadwords Number of 16-byte words required.
 * @return Current cursor, or null when there is insufficient capacity.
 */
u8* resident_packet_reserve(ResidentPacket* packet, s32 quadwords);

/**
 * @brief Read the byte at offset 0x25 of an object.
 * @param object Object to read; the field context passes its object at offset 0x24.
 * @return The byte at offset 0x25.
 */
u8 func_0011F9D0(void* object);

/** Store a resident data pointer in the shared global. */
void func_00120360(const void* value);

/** Return the word at receiver offset 0x14. */
u32 func_001205A0(const void* object);
/** Return the word at receiver offset 0x10. */
u32 func_001205E0(const void* object);
/** Return the word at receiver offset 0xC. */
u32 func_00120630(const void* object);
/** Return the word at receiver offset 0x8. */
u32 func_00120670(const void* object);
/** Return the word at receiver offset 0x4. */
u32 func_001206B0(const void* object);
/** Return the word at receiver offset 0x0. */
u32 func_001206F0(const void* object);

/** Clamp the value to [0, 100], store it at offset 0x10, and return it. */
s32 func_001205B0(void* object, s32 value);

/** Clamp the value to [0, 255], store it at offset 0x8, and return it. */
s32 func_00120640(void* object, s32 value);

/** Clamp the value to [0, 999], store it at offset 0x4, and return it. */
s32 func_00120680(void* object, s32 value);

/** Clamp the value to [0, 9999], store it at offset 0, and return it. */
s32 func_001206C0(void* object, s32 value);


/** Store a byte at offset 0x2C4 and a word at offset 0x2B8. */
void func_00120A50(void* object, u8 flag, u32 value);
/** Store a byte at offset 0x2C3 and a word at offset 0x2B4. */
void func_00120A60(void* object, u8 flag, u32 value);

/**
 * @brief Append an antialiased, flat-coloured line when the packet has room.
 * @param packet Packet to append to.
 * @param x0 First end's X, relative to the centre of the viewport.
 * @param y0 First end's Y, relative to the centre of the viewport.
 * @param x1 Second end's X, relative to the centre of the viewport.
 * @param y1 Second end's Y, relative to the centre of the viewport.
 * @param z Depth.
 * @param color RGBA colour.
 */
void resident_packet_add_line(ResidentPacket* packet, s32 x0, s32 y0, s32 x1, s32 y1, s32 z, u32 color);

/**
 * @brief Append a flat-coloured rectangle, drawn as a triangle strip, when the packet has room.
 * @param packet Packet to append to.
 * @param x0 Left edge, relative to the centre of the viewport.
 * @param y0 Top edge, relative to the centre of the viewport.
 * @param x1 Right edge, relative to the centre of the viewport.
 * @param y1 Bottom edge, relative to the centre of the viewport.
 * @param z Depth.
 * @param color RGBA colour.
 */
void func_0011F1D0(ResidentPacket* packet, s32 x0, s32 y0, s32 x1, s32 y1, s32 z, u32 color);

/**
 * @brief Append a GIF A+D write of the GS TEX0_2 register when the packet has room.
 * @param packet Packet to append to.
 * @param data Register value.
 */
void func_0011F020(ResidentPacket* packet, u64 data);

/**
 * @brief Append a GIF A+D write of the GS ALPHA_1 register when the packet has room.
 * @param packet Packet to append to.
 * @param data Register value.
 */
void func_0011F0B0(ResidentPacket* packet, u64 data);

/**
 * @brief Queue the packet's pending data on the packet queue without an end tag.
 * @param packet Packet whose data is queued.
 * @param completion Object notified when the transfer finishes, or null.
 */
void func_0011F510(ResidentPacket* packet, void* completion);

/**
 * @brief Write a GIF end tag after the pending data without advancing the cursor.
 * @param packet Packet to terminate.
 * @return Quadwords from the pending data's start through the end tag, or zero when nothing is pending.
 */
u32 func_0011F6E0(ResidentPacket* packet);

/**
 * @brief Replace the packet storage with a new allocation for a number of quadwords.
 * @param packet Packet to allocate storage for.
 * @param quadwords Capacity in 16-byte words, not counting the 0x40-byte header the cursor starts after.
 */
void resident_packet_allocate(ResidentPacket* packet, s32 quadwords);

/**
 * @brief Play a voice resource, from an emitter when one is given.
 * @param object Sound bank set; unused.
 * @param resource Voice resource.
 * @param emitter Object the voice follows, or null.
 * @param value Value forwarded to the voice request.
 * @param volume Volume, 0x7F for full.
 * @param low Value forwarded to the voice request.
 * @return Slot identifier of the voice.
 */
s32 func_0011F9E0(void* object, s32 resource, ResidentSoundEmitter* emitter, s32 value, s32 volume, s32 low);

/**
 * @brief Play sound data the caller supplies, from an emitter when one is given.
 * @param object Sound bank set; unused.
 * @param buffer Sound data to play.
 * @param emitter Object the sound follows, or null.
 * @param value Value forwarded to the sound request.
 * @param volume Volume, 0x7F for full.
 * @param low Value forwarded to the sound request.
 * @param owns_buffer Nonzero to free the buffer when the sound ends.
 * @return Slot identifier of the sound.
 */
s32 func_0011FA80(void* object, u8* buffer, ResidentSoundEmitter* emitter, s32 value, s32 volume, s32 low,
                  s32 owns_buffer);

/** Clamp the value to [0, 999999999], store it at offset 0x14, and return it. */
s32 func_00120560(void* object, s32 value);

/** Clamp the value to [0, 99999999], store it at offset 0xC, and return it. */
s32 func_001205F0(void* object, s32 value);

/**
 * @brief Get the hardware address of the packet's pending data.
 * @param packet Packet to inspect.
 * @return The start of the pending data with its upper four address bits cleared.
 */
u32 func_0011F760(const void* packet);

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus
#include "main/resident_00101550.h"

/**
 * Resident object that loads a randomly picked variant of up to three sound banks and plays sounds from them. It reads
 * each picked bank file into a staging buffer and uploads it, or uploads data lists registered with it.
 */
class ResidentClass14FC90 : public ResidentClass14FA40
{
public:
    /** @brief Construct an empty set with no banks assigned and register it with the update list. */
    ResidentClass14FC90();

    /** @brief Detach the set and free its staging buffer. */
    virtual ~ResidentClass14FC90();

    /** @brief Advance the bank loads by one step each frame while loads are in progress. */
    virtual void func_00104770();

    /** Variant loaded into each slot, or -1 when none has been picked. */
    s16 variants[RESIDENT_SOUND_BANK_SLOT_COUNT];

    /** Bank assigned to each slot (one-based index into the variant table), or zero. */
    u8 banks[RESIDENT_SOUND_BANK_SLOT_COUNT];

    u8 unk1d[3];

    /** Staging buffer the bank files are read into. */
    u8* buffer;

    u8 unk24;

    /** Nonzero while loads are in progress. */
    u8 loading;

    u8 unk26[2];
    ResidentSoundBankLoad loads[10];
    u8 load_count;
    u8 load_index;
    u8 load_step;

    /** Nonzero to upload the registered data lists instead of the picked bank files. */
    u8 upload_lists;

    u8 list_index;
    u8 part_index;
    u8 first_part;
    u8 unk7f;

    /** Registered sound bank data (see ResidentSoundBankPart) uploaded instead of picked files. */
    s32* lists[RESIDENT_SOUND_BANK_SLOT_COUNT][RESIDENT_SOUND_BANK_LIST_COUNT];

    s32 list_sizes[RESIDENT_SOUND_BANK_SLOT_COUNT];
};
#endif

#ifdef __cplusplus
/** Four float components, aligned for 128-bit copies. */
typedef struct ResidentVector4
{
    /**
     * @brief Copy all four components at once.
     * @param other Vector to copy.
     * @return This vector.
     */
    ResidentVector4& operator=(const ResidentVector4& other)
    {
        *(unsigned __int128*)this = *(const unsigned __int128*)&other;
        return *this;
    }

    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16))) ResidentVector4;

/** Four aligned rows of a 4x4 matrix, copied a row at a time. */
class ResidentMatrix
{
public:
    /**
     * @brief Copy all four rows.
     * @param other Matrix to copy.
     * @return This matrix.
     */
    ResidentMatrix& operator=(const ResidentMatrix& other)
    {
        ((unsigned __int128*)rows)[0] = ((const unsigned __int128*)other.rows)[0];
        ((unsigned __int128*)rows)[1] = ((const unsigned __int128*)other.rows)[1];
        ((unsigned __int128*)rows)[2] = ((const unsigned __int128*)other.rows)[2];
        ((unsigned __int128*)rows)[3] = ((const unsigned __int128*)other.rows)[3];
        return *this;
    }

    ResidentVector4 rows[4];
};

/** Second base of ResidentClass14FD30 (vtable D_0014FD10), the part registered with the list at D_001B6640. */
class ResidentClass14FD10
{
public:
    u8 unk00;
    u8 unk01;

    /** @brief Clear the state bytes. */
    ResidentClass14FD10()
    {
        unk00 = 0;
        unk01 = 0;
    }

    /** @brief Destroy the registration part. */
    virtual ~ResidentClass14FD10()
    {
    }

    /**
     * @brief Get the registered data.
     * @return The data, or null.
     */
    virtual void* func_001217E0() = 0;

    virtual s32 func_001217D0() = 0;

    /**
     * @brief Return zero.
     * @return Zero.
     */
    virtual s32 func_00121570();
};

/**
 * Primary base of ResidentClass14FD30: the Lib transform that func_4DAD90 constructs and func_4DAC70 destroys. Its slots
 * follow the resident list object's, and Lib implements the ones the resident objects call.
 */
class ResidentClass14FD30Base : public ResidentClass14FA40
{
public:
    /** @brief Construct an identity transform. */
    ResidentClass14FD30Base();

    /** @brief Destroy the transform. */
    virtual ~ResidentClass14FD30Base();

    /** @brief Detach the object and queue it for release. */
    virtual void func_00104740();

    /** @brief Update the transform relative to its parent. */
    virtual void func_00104770();

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
    virtual void set_translation_vector(const ResidentVector4* value);

    /**
     * @brief Copy the position.
     * @param value Source vector.
     */
    virtual void copy_translation(const ResidentVector4* value);

    /**
     * @brief Convert three rotation components into the orientation.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     */
    virtual void set_rotation(float x, float y, float z);

    /**
     * @brief Convert a rotation into the orientation.
     * @param value Source rotation.
     */
    virtual void set_rotation_vector(const ResidentVector4* value);

    /**
     * @brief Convert a rotation into the orientation.
     * @param value Source rotation.
     */
    virtual void convert_rotation(const ResidentVector4* value);

    /**
     * @brief Copy the orientation quaternion.
     * @param value Source quaternion.
     */
    virtual void set_orientation(const ResidentVector4* value);

    /**
     * @brief Copy the orientation quaternion.
     * @param value Source quaternion.
     */
    virtual void copy_orientation(const ResidentVector4* value);

    /**
     * @brief Set all four orientation components.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     * @param w Fourth component.
     */
    virtual void set_orientation_components(float x, float y, float z, float w);

    /**
     * @brief Set the scale's xyz components.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     */
    virtual void set_scale(float x, float y, float z);

    /**
     * @brief Copy the scale.
     * @param value Source vector.
     */
    virtual void set_scale_vector(const ResidentVector4* value);

    /**
     * @brief Copy the scale.
     * @param value Source vector.
     */
    virtual void copy_scale(const ResidentVector4* value);

    /** @brief Draw in the main list (bucket zero). */
    virtual void set_default_draw_bucket();

    /**
     * @brief Give the centre for Lib's oriented-box visibility test.
     * @param output Receives the centre in local space.
     * @return Nonzero when a centre was written.
     */
    virtual s32 get_box_cull_center(void* output);

    /**
     * @brief Fade the object as it nears the camera.
     * @param value Distance in front of the camera over the fade range, clamped to one.
     * @param mode Mode from Lib's caller.
     * @return Whether the value is negative.
     */
    virtual bool set_fade_alpha(float value, float mode);

    /**
     * @brief Return the bounding sphere Lib culls against (centre in xyz, radius in w).
     * @return Bounding sphere.
     */
    virtual const ResidentVector4* get_bounding_sphere();

    /**
     * @brief Build the object's draw packet.
     * @param matrix Matrix supplied by the caller.
     * @param context Opaque caller context.
     */
    virtual void build_packet(const void* matrix, void* context);

    /** @brief Rebuild the transformation matrices from the position, orientation and scale. */
    virtual void update_transform_matrix();

    /**
     * @brief Read the stored transformation matrix.
     * @return Matrix pointer.
     */
    virtual const ResidentMatrix* get_transform_matrix();

    /**
     * @brief Copy the source's transformation state.
     * @param source Transform source.
     */
    virtual void copy_transform_state(const ResidentClass14FD30Base* source);

    /**
     * @brief Make a copy of this object that stays linked to it.
     * @return The copy, or null.
     */
    virtual ResidentClass14FD30Base* clone();

    /** @brief Unlink a copy from its original and queue it for release. */
    virtual void release_clone();

    /**
     * @brief Read the additional local translation.
     * @return Stored translation.
     */
    virtual const ResidentVector4* get_offset_translation() const;

    /**
     * @brief Read the additional local rotation.
     * @return Stored quaternion.
     */
    virtual const ResidentVector4* get_offset_rotation() const;

    /**
     * @brief Read the additional local scale.
     * @return Stored scale.
     */
    virtual const ResidentVector4* get_offset_scale() const;

    /**
     * @brief Copy another transform's state and its offset vectors.
     * @param source Transform source.
     */
    virtual void copy_offset_transform_state(const ResidentClass14FD30Base* source);

    u8 unk14[0xC];
    ResidentVector4 translation;

    /** Rotation as a quaternion. */
    ResidentVector4 orientation;

    ResidentVector4 scale;

    /** Nonzero when the transformation matrices need rebuilding. */
    u8 transform_dirty;

    u8 unk51;
    u8 unk52[0xE];

    /** Draw bucket; zero is the main list. */
    u8 draw_bucket;

    /** Nonzero once transform holds the current matrix. */
    u8 matrix_ready;

    u8 unk62[0xA];
    u16 unk6c;
    u8 unk6e[0x22];
    ResidentMatrix transform;
    ResidentMatrix base_transform;
    ResidentMatrix offset_transform;

    /** Transpose of transform, which func_4D9E70 inverts into inverse_transform. */
    ResidentMatrix transposed_transform;

    /** Inverse of transform: world space to local space. */
    ResidentMatrix inverse_transform;

    ResidentVector4 offset_translation;
    ResidentVector4 offset_rotation;
    ResidentVector4 offset_scale;
    float unk200;
    u8 unk204[4];
    ResidentClass14FD30Base* parent_transform;
    u16 unk20c;
    u8 unk20e_0 : 1;
    u8 unk20e_1 : 1;
    u8 unk20e_2 : 1;
    u8 unk20f;
};

/** Transform followed by a box's half extents, which hit tests check points against in the transform's space. */
class ResidentHitBox : public ResidentClass14FD30Base
{
public:
    ResidentVector4 half_extents;
};

/** Resource record as Lib's render data loaders keep it; data can hold an offset or a resolved pointer. */
typedef struct ResidentRenderDataRecord
{
    u32 next_offset;
    s16 storage_kind;
    s16 index;
    u32 key08;
    u32 key0c;
    u64 unk10[2];
    u32 resolved_data;
    u8 unk24[4];
    u8* data;
    u32 unk2c;
} ResidentRenderDataRecord;

/** Lib's image-sequence channel (0x60 bytes) that animates a bound FIS record. */
class ResidentImageSequenceChannel
{
public:
    ResidentImageSequenceChannel();

    virtual ~ResidentImageSequenceChannel();

    u8 unk04[0x38];
    u32 unk3c;
    u8 unk40[8];
    s32 unk48;
    u8 unk4c[0x14];
};

/** Image header whose texture size is stored as powers of two. */
typedef struct ResidentImageHeader
{
    u8 unk00[0xE];
    u8 width_log2;
    u8 height_log2;
    u8 unk10[0x58];
} ResidentImageHeader;

/** Partial display manager at D_001B661C, holding the shared image headers. */
typedef struct ResidentDisplayManager
{
    u8 unk0000[0xB3C8];
    ResidentImageHeader images[1];
} ResidentDisplayManager;

/**
 * Resident transform object (vtable D_0014FD30) that draws an image from its render data record. It registers its
 * second base with the list at D_001B6640, and can follow another transform's position and a camera's orientation.
 */
class ResidentClass14FD30 : public ResidentClass14FD30Base, public ResidentClass14FD10
{
public:
    /** @brief Construct an unregistered object with no channel and the image centred. */
    ResidentClass14FD30();

    /** @brief Unregister the object and destroy its image channel. */
    virtual ~ResidentClass14FD30();

    /** @brief Unregister the object if it is registered, then detach it and queue it for release. */
    virtual void func_00104740();

    /** @brief Do nothing. */
    virtual void func_00104780();

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
    virtual void set_translation_vector(const ResidentVector4* value);

    /**
     * @brief Copy the position.
     * @param value Source vector.
     */
    virtual void copy_translation(const ResidentVector4* value);

    /**
     * @brief Convert three rotation components into the orientation.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     */
    virtual void set_rotation(float x, float y, float z);

    /**
     * @brief Convert a rotation into the orientation.
     * @param value Source rotation.
     */
    virtual void set_rotation_vector(const ResidentVector4* value);

    /**
     * @brief Convert a rotation into the orientation.
     * @param value Source rotation.
     */
    virtual void convert_rotation(const ResidentVector4* value);

    /**
     * @brief Copy the orientation quaternion.
     * @param value Source quaternion.
     */
    virtual void set_orientation(const ResidentVector4* value);

    /**
     * @brief Copy the orientation quaternion.
     * @param value Source quaternion.
     */
    virtual void copy_orientation(const ResidentVector4* value);

    /**
     * @brief Set all four orientation components.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     * @param w Fourth component.
     */
    virtual void set_orientation_components(float x, float y, float z, float w);

    /**
     * @brief Set the scale's xyz components.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     */
    virtual void set_scale(float x, float y, float z);

    /**
     * @brief Copy the scale.
     * @param value Source vector.
     */
    virtual void set_scale_vector(const ResidentVector4* value);

    /**
     * @brief Copy the scale.
     * @param value Source vector.
     */
    virtual void copy_scale(const ResidentVector4* value);

    /** @brief Draw in the main list (bucket zero). */
    virtual void set_default_draw_bucket();

    /**
     * @brief Give no centre for Lib's oriented-box visibility test.
     * @param output Unused.
     * @return Zero, so the test is skipped.
     */
    virtual s32 get_box_cull_center(void* output);

    /**
     * @brief Don't fade near the camera.
     * @param value Distance in front of the camera over the fade range.
     * @param mode Unused.
     * @return Whether the value is negative.
     */
    virtual bool set_fade_alpha(float value, float mode);

    /**
     * @brief Return Lib's shared default bounding sphere.
     * @return Bounding sphere.
     */
    virtual const ResidentVector4* get_bounding_sphere();

    /**
     * @brief Do nothing.
     * @param matrix Unused.
     * @param context Unused.
     */
    virtual void build_packet(const void* matrix, void* context);

    /**
     * @brief Read the stored transformation matrix.
     * @return Matrix pointer.
     */
    virtual const ResidentMatrix* get_transform_matrix();

    /**
     * @brief Don't copy this object.
     * @return Null.
     */
    virtual ResidentClass14FD30Base* clone();

    /** @brief Do nothing; this object has no copies. */
    virtual void release_clone();

    /**
     * @brief Read the additional local translation.
     * @return Stored translation.
     */
    virtual const ResidentVector4* get_offset_translation() const;

    /**
     * @brief Read the additional local rotation.
     * @return Stored quaternion.
     */
    virtual const ResidentVector4* get_offset_rotation() const;

    /**
     * @brief Read the additional local scale.
     * @return Stored scale.
     */
    virtual const ResidentVector4* get_offset_scale() const;

    /**
     * @brief Copy another object's settings, record and transform state, and rebuild the image channel when it has one.
     * @param source Object to copy.
     */
    virtual void copy_state(const ResidentClass14FD30* source);

    /**
     * @brief Get the record while the object is registered.
     * @return The record, or null.
     */
    virtual void* func_001217E0();

    /**
     * @brief Return zero.
     * @return Zero.
     */
    virtual s32 func_001217D0();

    float unk218;
    float unk21c;
    float unk220;
    float unk224;

    /** Frame ticks since the image started, which drive the image channel. */
    float elapsed;

    /** Bits matched against the hit-test mask. */
    u32 hit_mask;

    /** Box that hit tests check against. */
    ResidentHitBox* hit_volume;

    u8 unk234[4];
    ResidentRenderDataRecord record;
    u8 unk268[8];
    ResidentMatrix unk270;

    /** Channel animating the record's image sequence, or null. */
    ResidentImageSequenceChannel* channel;

    /** Transform whose position and orientation this object copies, used while follow_position is set. */
    ResidentClass14FD30Base* position_source;

    /** Camera whose position and orientation this object copies, used while follow_camera is set. */
    ResidentClass14FD30Base* camera;

    /** Nonzero to face func_001210B0's target point instead of using the plain transform. */
    u8 faces_target;

    u8 unk2bd;
    u8 unk2be;

    /** Nonzero to animate the record through an image channel. */
    u8 animated;

    /** Nonzero while the second base is registered. */
    u8 registered;

    u8 unk2c1;

    /** One-based index of a shared display-manager image, or zero to use the record's own. */
    u8 shared_image;

    u8 follow_position;
    u8 follow_camera;

    /** Zero to size unk218 from the camera's projection distance. */
    u8 unk2c5;

    u8 unk2c6;
    u8 unk2c7;
};

/** Lib's object list: a sentinel node and count before the list's own vptr; Lib implements every slot. */
class ResidentObjectList
{
public:
    ResidentClass14FA30 sentinel;
    u32 node_count;

    virtual ~ResidentObjectList();

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

    /**
     * @brief Remove a registered node.
     * @param object Node to remove.
     */
    virtual void remove_node(void* object);

    /** @brief Run the registered nodes' update handlers. */
    virtual void update_nodes();

    /**
     * @brief Register and append a node.
     * @param object Node to append.
     * @param kind List kind, or -1 to use the node's own kind.
     */
    virtual void append_node(void* object, s32 kind);

    /**
     * @brief Register and prepend a node.
     * @param object Node to prepend.
     * @param kind List kind, or -1 to use the node's own kind.
     */
    virtual void prepend_node(void* object, s32 kind);

    /**
     * @brief Register a node after a list position.
     * @param position Insertion position.
     * @param object Node to insert.
     * @param kind List kind, or -1 to use the node's own kind.
     */
    virtual void insert_node_after(void* position, void* object, s32 kind);

    /**
     * @brief Set the next list in the chain.
     * @param attached List that follows this list.
     */
    virtual void func_004295B0(void* attached);

    /** @brief Hook with no work in Lib's list. */
    virtual void func_004295C0();

    u32 node_counts_by_kind[17];
    u32 unk58;
    s32 active_node_index;
    s32 active_node_count;
    s32 node_buffer_capacity;
    void** owned_node_buffer;
    void** active_node_buffer;
    ResidentObjectList* next_list;
    ResidentObjectList* active_buffer_owner;
};

/** Resident object list (vtable D_0014FCB0) that is also a list object, and updates its ResidentClass14FD30 nodes. */
class ResidentClass14FCB0 : public ResidentObjectList, public ResidentClass14FA40
{
public:
    /** @brief Destroy the list. */
    virtual ~ResidentClass14FCB0();

    /**
     * @brief Remove a registered node, and make the next two hit tests start from the first node.
     * @param object Node to remove.
     */
    virtual void remove_node(void* object);

    /**
     * @brief Set the next list in the chain.
     * @param attached List that follows this list.
     */
    virtual void func_004295B0(void* attached);

    /** @brief Do nothing. */
    virtual void func_004295C0();

    /**
     * @brief Return the list's kind.
     * @return Nine.
     */
    virtual s32 func_00104730();

    /** @brief Update every node: follow targets, advance the images and rebuild hit boxes. */
    virtual void func_00104770();

    /** Updates left during which the list is walked from the start; set to two when a node is removed. */
    u32 unk8c;
};
#endif

#ifdef __cplusplus
extern "C"
{
    /**
     * @brief Find the first object from a start node whose hit box a sphere touches, turning it to face the sphere.
     * @param list Object list to walk.
     * @param mask Bits an object's hit mask must share.
     * @param point Sphere centre in xyz and radius in w.
     * @param start Node to start from, or null for the first; the walk also starts from the first while unk8c is set.
     * @return The object hit, or null.
     */
    ResidentClass14FD30* func_00120A70(ResidentClass14FCB0* list, u32 mask, const ResidentVector4* point,
                                       ResidentClass14FD30* start);

    /**
     * @brief Turn the image animation on or off, rebuilding the image channel while the object is registered.
     * @param object Object to update.
     * @param animated Nonzero to animate the record through an image channel.
     */
    void func_00120FE0(ResidentClass14FD30* object, u8 animated);

    /**
     * @brief Update the transform, turning it to face a point when asked to, then build the image's projection matrix.
     * @param object Object to update.
     * @param target Point to face, or null for the plain transform.
     */
    void func_001210B0(ResidentClass14FD30* object, const ResidentVector4* target);

    /**
     * @brief Point the record at a resource's data, register the object and rebuild its image channel.
     * @param object Object to update.
     * @param resource Resource whose data follows a 16-byte prefix.
     */
    void func_001212A0(ResidentClass14FD30* object, u8* resource);

    /**
     * @brief Cancel the bank file reads and forget each slot's variant unless loads are in progress.
     * @param set Sound bank set.
     */
    void func_0011F940(ResidentClass14FC90* set);

    /**
     * @brief Play a sound from a slot's bank, from an emitter when one is given.
     * @param set Sound bank set.
     * @param slot Bank slot.
     * @param id Sound number within the bank.
     * @param emitter Object the sound follows, or null.
     * @param arg4 Value forwarded to the sound request.
     * @param arg5 Value forwarded to the sound request.
     * @param arg6 Value forwarded to the sound request.
     * @return Slot identifier of the sound, or -1 when the slot has no bank loaded.
     */
    s32 func_0011FB40(ResidentClass14FC90* set, s32 slot, s32 id, ResidentSoundEmitter* emitter, s32 arg4, s32 arg5,
                      s32 arg6);

    /**
     * @brief Start uploading the registered data lists unless loads are in progress.
     * @param set Sound bank set.
     */
    void func_0011FFD0(ResidentClass14FC90* set);

    /**
     * @brief Register bank data in the first free entry of a list unless loads are in progress.
     * @param set Sound bank set.
     * @param list List to add to.
     * @param data Bank data.
     */
    void func_00120000(ResidentClass14FC90* set, s32 list, s32* data);

    /**
     * @brief Clear every registered data list and its size unless loads are in progress.
     * @param set Sound bank set.
     */
    void func_00120050(ResidentClass14FC90* set);

    /**
     * @brief Get the budget picking a variant for every assigned slot without one would cost.
     * @param set Sound bank set.
     * @return The pick cost times the number of such slots.
     */
    s32 func_00120370(ResidentClass14FC90* set);

    /**
     * @brief Pick variants for the slots and start loading them.
     * @param set Sound bank set.
     * @param budget Budget each pick spends from.
     * @return One when loading started, or zero otherwise.
     */
    s32 func_001200C0(ResidentClass14FC90* set, s32 budget);

    /**
     * @brief Assign a bank to a slot unless loads are in progress, forgetting its variant when the bank changes.
     * @param set Sound bank set.
     * @param slot Slot to assign.
     * @param bank One-based bank number, or zero for none.
     * @return One when assigned, or zero while loads are in progress.
     */
    s32 func_001203C0(ResidentClass14FC90* set, s32 slot, s32 bank);
}
#endif

#endif
