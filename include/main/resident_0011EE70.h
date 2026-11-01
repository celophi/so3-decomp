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
 * @brief Store three components and set the fourth to 1.0 at offset 0x20.
 * @param object Object containing the vector and flag.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void func_00121670(void* object, float x, float y, float z);

/**
 * @brief Move the set state from byte 0x25 to byte 0x24 when set.
 * @param object Object containing the state bytes.
 */
void func_0011F9B0(void* object);

/** Mark the transform as changed and copy a four-float value into it. */
void func_001216D0(u8* object, const float* input);
/** Mark the transform as changed and copy a four-float value into it. */
void func_00121700(u8* object, const float* input);

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

/** Clear the byte at receiver offset 0x60. */
void func_001215C0(void* object);

/** Return the address of the shared global at 0x50CD30. */
const void* func_00121610(void);

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


/** Store the word at receiver offset 0x70. */
void func_001207B0(void* object, u32 value);

/** Store a byte at offset 0x2C4 and a word at offset 0x2B8. */
void func_00120A50(void* object, u8 flag, u32 value);
/** Store a byte at offset 0x2C3 and a word at offset 0x2B4. */
void func_00120A60(void* object, u8 flag, u32 value);

/** Return the fixed integer value 9. */
s32 func_001207D0(void* object);
void* func_00120700(void* object);
void* func_001213B0(void* object);
void func_00120BF0(void* object);

/** Return the fixed value 0. */
s32 func_00121570(void* object);

/** Return the fixed value 0. */
s32 func_001215E0(void* object);

/** Test whether a floating-point value is negative. */
s32 func_001215F0(float value);

/** Return the fixed value 0. */
s32 func_00121630(void* object);

void func_001207C0(void* object);
void func_001215D0(void* object);
void func_00121620(void* object);
void func_00121640(void* object);

/** Return the receiver address at byte offset 0x90. */
void* func_00121580(void* object);

/** Return the receiver address at byte offset 0x1D0. */
void* func_00121590(void* object);

/** Return the receiver address at byte offset 0x1E0. */
void* func_001215A0(void* object);

/** Return the receiver address at byte offset 0x1F0. */
void* func_001215B0(void* object);

/** Set the ready flag and copy a 128-bit value into the receiver. */
void func_00120EB0(void* object, const unsigned __int128* value);

/** Set the ready flag and copy a 128-bit value into the receiver. */
void func_00120ED0(void* object, const unsigned __int128* value);

/** Set the ready flag and copy a 128-bit value into the receiver. */
void func_00121650(void* object, const unsigned __int128* value);

/** Set the ready flag and copy a 128-bit value into the receiver. */
void func_001216B0(void* object, const unsigned __int128* value);

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

/**
 * @brief Set the word at offset 0x8C to 2, set bit 0 of the shared flag byte D_001B65D0 and call func_4D72A0.
 * @param object Object containing the word.
 */
void func_00120EF0(void* object);

#ifdef __cplusplus
/** Set the receiver flag and store four float values. */
void func_00121690(void* object, float x, float y, float z, float w);

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
    ResidentClass14FC90();

    virtual ~ResidentClass14FC90();

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
/** Second base of ResidentClass14FD30 (vtable D_0014FD10), the part registered with the list at D_001B6640. */
class ResidentClass14FD10
{
public:
    u8 unk00;
    u8 unk01;

    virtual ~ResidentClass14FD10();
};

/** Primary base of ResidentClass14FD30: the Lib transform that func_4DAD90 constructs and func_4DAC70 destroys. */
class ResidentClass14FD30Base
{
public:
    virtual ~ResidentClass14FD30Base();

    u8 unk004[0x20C];
};

/** Resident transform object (vtable D_0014FD30) that registers its second base with the list at D_001B6640. */
class ResidentClass14FD30 : public ResidentClass14FD30Base, public ResidentClass14FD10
{
public:
    u8 unk218[0xA8];

    /** Nonzero while the second base is registered. */
    u8 registered;
};
#endif

#ifdef __cplusplus
extern "C"
{
    /**
     * @brief Unregister the object if it is registered, then detach it and queue it for release.
     * @param object Object to release.
     */
    void func_001207E0(ResidentClass14FD30* object);

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
     * @brief Advance the bank loads by one step each frame while loads are in progress.
     * @param set Sound bank set.
     */
    void func_0011FC20(ResidentClass14FC90* set);

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
