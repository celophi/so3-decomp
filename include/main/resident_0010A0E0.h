#ifndef SO3_MAIN_RESIDENT_0010A0E0_H
#define SO3_MAIN_RESIDENT_0010A0E0_H

#include "types.h"
#include "main/resident_00101550.h"

/**
 * Pointer ring with write_index at the next insertion slot and read_index at the
 * last released slot. Equal indices mean full; an empty ring has write_index
 * one slot ahead of read_index, wrapping at 0x400.
 */
typedef struct ResidentReleaseRing
{
    s32 write_index;
    s32 read_index;
    void* entries[0x400];
} ResidentReleaseRing;

/** Resident rings for deferred allocation release and object destruction. */
typedef struct ResidentReleaseQueues
{
    ResidentReleaseRing allocations;
    ResidentReleaseRing objects;
    void* vtable;
} ResidentReleaseQueues;

/** The two pads (buttons, sticks and vibration) and the vblank counters that time each frame. */
struct ResidentInputSystem;

/**
 * The game's resource archive: the packed entry of every resource, plus the worker that installs the archive to the
 * PlayStation BB Unit (the hard disk) and reports its progress.
 */
typedef struct ResidentArchive
{
    u8 unk00[0x6C];
    u8 unk6c;
    u8 unk6d[0x7F];
    u8 unkEC[0x18];

    /** Free space the last space query found on the unit. */
    u32 free_space;

    /** Set once the unit is present and initialized. */
    u8 unit_ready;

    u8 unk109[3];

    /** Nonzero while a worker command runs. */
    s32 busy;

    /** Result of the last worker command; nonzero is an error. */
    s32 command_result;

    u8 unk114[4];

    /** Words left to copy while installing. */
    s32 copy_remaining;

    u8 unk11c[0x18];

    /** Buffer the install copies through. */
    u8* copy_buffer;

    /** Set to ask the running command to stop. */
    u8 cancel_requested;

    u8 unk139[2];

    /** Set while the install's abort prompt is up. */
    u8 copy_paused;

    u8 unk13c[4];
    u8 unk140;

    /** Unit state: one when it isn't initialized, two when it's ready. */
    u8 unit_state;

    u8 unk142[0x1A];

    /** BB Navigator files written next to the installed archive. */
    u8* navigator_files[3];

    s32 navigator_file_sizes[3];
    u8 unk174[0x6008];

    /** Per resource: its size in 2048-byte blocks in the low 24 bits. */
    u32 resource_entries[0x1800];

    /** Per resource: nonzero when the install copies it. */
    u32 install_flags[0x1800];

    u8 unk1217c[7];
    u8 unk12183;
    u8 unk12184;
} ResidentArchive;

/** One of the sixty resident request slots. */
typedef struct ResidentRequestSlot
{
    u8 active;
    u8 pending;
    u8 flags2;
    u8 flags3;
    u8 flags4;
    u8 selector;
    u8 unk06[2];
    s16 value;
    u8 unk0a[2];
    u32 unk0c;
    s32 identifier;
    u32 unk14;
    s32 unk18;
    u8 unk1c;
    u8 unk1d[3];
    void* target;
    u32 unk24;
    u32 unk28;
    u32 unk2c;
    u32 unk30;
    u8 unk34[8];
} ResidentRequestSlot;

/** Receiver prefix containing the cyclic slot cursor and request identifiers. */
struct ResidentSoundStream
{
    u8 unk00[0x90];

    /** Stream handle. */
    void* handle;
};

/**
 * The sound system: sound effects and voices in sixty slots, streamed music, and the surround output with its
 * listener and speaker placement.
 */
struct ResidentSound
{
    struct ResidentSoundStream* stream;
    u8 unk04[8];
    u32 unk0c;
    u8 unk10[0x100];
    u8 state;
    u8 unk111[0x25F];

    /** Set when sound is unavailable; most calls then do nothing and report success. */
    u8 disabled;

    u8 unk371;
    u8 unk372[0x4A];
    s32 unk3bc;
    u8 unk3c0[0x90];

    /** Sound output mode: 1 mono, 0 stereo, 2 Dolby Pro Logic II, 3 headphones. */
    u8 output_mode;

    u8 unk451[0x8B];
    u32 next_identifier;
    s32 cursor;
    ResidentRequestSlot slots[60];
    u8 unk12f4[0x9C];

    /** Object the positional sounds are heard from. */
    void* listener;

    float unk1394;

    /** Square of the distance positional sounds reach. */
    float range_squared;

    /** Angle of each of the four surround speakers. */
    float speaker_angles[4];
};

typedef struct ResidentSound ResidentSound;

/** Partial resident DMA queue exposing the asynchronously cleared busy flag. */
typedef struct ResidentDmaQueue
{
    u8 unk00[0x1011];
    volatile u8 busy;
} ResidentDmaQueue;

#ifdef __cplusplus
/** Resident allocation heap with its virtual pointer following the heap state. */
class ResidentHeap
{
public:
    ResidentHeap();

    u8 unk00[0x54];

    /** @brief Release heap storage and child heaps. */
    virtual ~ResidentHeap();
};
#endif

#ifdef __cplusplus
/** Interface called by the resident queue when a DMA transfer starts or completes. */
class DmaSubmission
{
public:
    /** @brief Start the queued DMA transfer. @param channel DMA channel number. */
    virtual void submit_dma(u32 channel) = 0;
    /** @brief Complete the queued DMA transfer. @param channel DMA channel number. */
    virtual void complete_dma(u32 channel) = 0;
};
#else
typedef struct DmaSubmission DmaSubmission;
#endif

/**
 * The resident system g_system, which outlives every program. It holds the resource archive, the entry table, the
 * resource queue and the decoder that loads each program's overlay, and it switches from one program to the next.
 */
typedef struct ResidentSystem
{
    u8 unk00[0x1398C];

    /** Decoder that unpacks each program's overlay. */
    ResidentDecodeObject decoder;

    u8 unk1398D[0x22F7];

    /** Nonzero for progressive (525p) output. */
    u8 progressive;

    u8 unk15C85[0x17];

    /** Main's stack and frame pointers, restored when switching programs. */
    void* saved_sp;
    void* saved_fp;

    u8 unk15CA4[0x1C];

    /** Status byte, allocated on first use; a failed main code check sets it to 0x67. */
    u8* status;
} ResidentSystem;

#ifdef __cplusplus
extern "C" {
#endif

s32 func_0011CC00(void* object, void* entry, void* descriptor);
void func_0011D060(void* object, void* entry, void* descriptor);

/**
 * @brief Forward the manager's first pointer and the argument to func_00107D90.
 * @param argument Value forwarded as the helper's second argument.
 */
void func_0010DFC0(void* argument);

/** Run the resident helper on the object's pointer when it is non-null. */
void func_0010ECF0(void* object);

/**
 * @brief Queue a DMA submission and start processing if the channel is idle.
 * @param queue Resident queue for the DMA channel.
 * @param submission Transfer callbacks to enqueue.
 * @return 1 on success, 0 when the queue is full.
 */
s32 func_00114100(ResidentDmaQueue* queue, DmaSubmission* submission);

/**
 * @brief Get the resident system.
 * @return g_system.
 */
ResidentSystem* resident_get_system(void);

/**
 * @brief Allocate a block from a resident heap.
 * @param heap Heap to allocate from.
 * @param size Requested payload size in bytes.
 * @return Allocation base, or null when no block is available.
 */
void* resident_heap_allocate(void* heap, s32 size);

/**
 * @brief Resize a block, releasing and replacing it when it must grow.
 *
 * Growing a block does not preserve its contents.
 *
 * @param memory Resident heap allocation to resize.
 * @param size Requested payload size in bytes.
 * @return Allocation base, or null if a replacement cannot be allocated.
 */
void* resident_heap_resize(void* memory, s32 size);

/**
 * @brief Return a block to its resident heap.
 * @param memory Allocation to release.
 */
void resident_heap_release(void* memory);

/** Clear bytes at 0x78-0x7B and copy the word at 0x84 to offsets 0x7C and 0x80. */
void func_0010B730(void* object);

/**
 * @brief Put the four surround speakers back at their default angles.
 * @param sound Sound system.
 */
void resident_sound_reset_speaker_angles(ResidentSound* sound);

/**
 * @brief Set the sound output mode.
 * @param sound Sound system.
 * @param mode Output mode: 1 mono, 0 stereo, 2 Dolby Pro Logic II, 3 headphones.
 */
void resident_sound_set_output_mode(ResidentSound* sound, s32 mode);

/**
 * @brief Set the object positional sounds are heard from.
 * @param sound Sound system.
 * @param listener Listening object.
 * @param value Stored with the listener; its use is unknown.
 * @param range Distance positional sounds reach.
 */
void resident_sound_set_listener(ResidentSound* sound, void* listener, float value, float range);

/**
 * @brief Set the angle of one surround speaker.
 * @param sound Sound system.
 * @param speaker Speaker index, 0 to 3.
 * @param angle Speaker angle in radians.
 */
void resident_sound_set_speaker_angle(ResidentSound* sound, s32 speaker, float angle);

/**
 * @brief Set the angles of all four surround speakers.
 * @param sound Sound system.
 * @param angles Four speaker angles in radians.
 */
void resident_sound_set_speaker_angles(ResidentSound* sound, const float* angles);
/** Append the pointer at object offset zero to the resident manager array. */
void func_0010EF50(const void* object);
/** Run the resident helper on the pointer at offset zero with its final flag set. */
s32 func_0010EFD0(void* object);

/** Return whether the resident double comparison reports left greater than right. */
s32 func_001143E0(double left, double right);
/** Return whether the resident double comparison reports left less than right. */
s32 func_00114400(double left, double right);
/** Return whether the resident double comparison reports the values equal. */
s32 func_00114420(double left, double right);

/** Store a halfword at offset 0x10, then request resident processing with mode 50. */
s32 func_00114560(void* object, s16 value, s32 size);

/**
 * @brief Advance the resident random sequence and return its next word.
 * @return Next unsigned random word.
 */
u32 resident_next_random_word(void);

/**
 * @brief Return the next resident random number.
 * @return Random number.
 */
u32 resident_rand(void);

/**
 * @brief Read the byte size associated with a key in the resident descriptor table.
 * @param object Resident descriptor table owner.
 * @param key Descriptor key.
 * @return Resource size in bytes.
 */
u32 resident_get_resource_size(const ResidentArchive* archive, s32 key);

/**
 * @brief Attach the display whose field the vblank handler updates.
 * @param input Input system.
 * @param display Display to update each vblank, or null.
 * @param enabled Nonzero to update the display each vblank.
 */
void resident_input_attach_display(struct ResidentInputSystem* input, void* display, s32 enabled);

/**
 * @brief Take the number of vblanks counted since the last call.
 * @param input Input system.
 * @return Vblanks since the last call.
 */
s32 resident_input_take_vblank_count(struct ResidentInputSystem* input);

/**
 * @brief Get the buttons a pad holds this frame.
 * @param input Input system.
 * @param slot Pad slot.
 * @return Held button bits.
 */
u16 resident_pad_get_held(const struct ResidentInputSystem* input, s32 slot);

/**
 * @brief Get the buttons newly pressed since the latches were last cleared.
 * @param input Input system.
 * @param slot Pad slot.
 * @return Pressed button bits.
 */
u16 resident_pad_get_pressed(const struct ResidentInputSystem* input, s32 slot);

/**
 * @brief Get every button held at some point since the latches were last cleared.
 * @param input Input system.
 * @param slot Pad slot.
 * @return Held button bits.
 */
u16 resident_pad_get_held_since_clear(const struct ResidentInputSystem* input, s32 slot);

/**
 * @brief Get the pressed buttons, or the held ones once they have been held long enough to repeat.
 * @param input Input system.
 * @param slot Pad slot.
 * @return Button bits.
 */
u16 resident_pad_get_repeated(const struct ResidentInputSystem* input, s32 slot);

/**
 * @brief Clear the pressed and held-since-clear latches of a pad.
 * @param input Input system.
 * @param slot Pad slot.
 */
void resident_pad_clear_latched(struct ResidentInputSystem* input, s32 slot);

/**
 * @brief Choose whether a pad's analog sticks also press the direction buttons.
 * @param input Input system.
 * @param slot Pad slot.
 * @param enabled Nonzero to map the sticks onto the direction buttons.
 */
void resident_pad_set_stick_dpad(struct ResidentInputSystem* input, s32 slot, s32 enabled);

/**
 * @brief Enable or disable a pad's vibration; disabling stops both motors.
 * @param input Input system.
 * @param slot Pad slot.
 * @param enabled Nonzero to allow vibration.
 */
void resident_pad_set_vibration_enabled(struct ResidentInputSystem* input, s32 slot, s32 enabled);

/**
 * @brief Set a pad's motor levels while vibration is enabled.
 * @param input Input system.
 * @param slot Pad slot.
 * @param small Small motor, on when nonzero.
 * @param large Large motor strength.
 */
void resident_pad_set_vibration(struct ResidentInputSystem* input, s32 slot, s32 small, s32 large);

/**
 * @brief Read a pad's four analog stick axes with the dead zone and calibration applied.
 * @param input Input system.
 * @param slot Pad slot.
 * @param first Receives the first axis.
 * @param second Receives the second axis.
 * @param third Receives the third axis.
 * @param fourth Receives the fourth axis.
 * @return Nonzero when the pad is in analog mode; the axes are zero otherwise.
 */
s32 resident_pad_get_sticks(struct ResidentInputSystem* input, s32 slot, s32* first, s32* second, s32* third, s32* fourth);

/**
 * @brief Queue an object for destruction by its virtual destructor.
 * @param queue Deferred release queues.
 * @param object Object to destroy later; null succeeds without insertion.
 * @return One on success, or zero when the object ring is full.
 */
s32 resident_enqueue_object(ResidentReleaseQueues* queue, void* object);

/**
 * @brief Play a sound effect in a free slot.
 * @param receiver Sound system.
 * @param arg1 Sound number; its low 16 bits are stored.
 * @param arg2 Request selector.
 * @param arg3 Value forwarded to request dispatch.
 * @param arg4 Volume, 0x7F for full; stored and packed into the upper byte.
 * @param arg5 Pan, 0x40 for centre; packed into the next byte.
 * @param arg6 Value packed into the lower 16 bits.
 * @return Slot identifier, zero on dispatch failure, one when disabled, or minus one when no slot is free.
 */
s32 resident_sound_play(ResidentSound* receiver, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);

/**
 * @brief Report whether music is playing.
 * @param sound Sound system.
 * @param key Music to check for, or -1 for any.
 * @return Nonzero while that music plays, or always when sound is disabled.
 */
s32 resident_sound_is_music_playing(ResidentSound* sound, s32 key);

/**
 * @brief Report whether a hard disk unit error is pending.
 * @param archive Resource archive.
 * @return One when an error is pending, otherwise zero.
 */
s32 resident_archive_has_unit_error(const ResidentArchive* archive);

/**
 * @brief Clear the pending hard disk unit error.
 * @param archive Resource archive.
 */
void resident_archive_clear_unit_error(ResidentArchive* archive);

/**
 * @brief Report whether the unit is ready, with no error pending.
 * @param archive Resource archive.
 * @return Nonzero when the unit is ready.
 */
s32 resident_archive_is_unit_ready(const ResidentArchive* archive);

/**
 * @brief Start a query of the unit and any existing install when the unit is usable.
 * @param archive Resource archive.
 * @param first Nonzero to start the query.
 * @param second Selects which checks the query skips.
 * @return Nonzero when a query is running or already done.
 */
s32 resident_archive_query_unit(ResidentArchive* archive, s32 first, s32 second);

/**
 * @brief Queue a command for the hard disk worker.
 * @param archive Resource archive.
 * @param command Worker command.
 * @param argument Command argument.
 */
void resident_archive_start_command(ResidentArchive* archive, s32 command, s32 argument);

/**
 * @brief Ask the running worker command to stop.
 * @param archive Resource archive.
 */
void resident_archive_cancel_command(ResidentArchive* archive);

/**
 * @brief Report whether a worker command is running.
 * @param archive Resource archive.
 * @return Nonzero while a command runs.
 */
s32 resident_archive_is_busy(const ResidentArchive* archive);

/**
 * @brief Get the result of the last worker command.
 * @param archive Resource archive.
 * @return Zero on success, otherwise an error.
 */
s32 resident_archive_get_command_result(const ResidentArchive* archive);

/**
 * @brief Get the words the install still has to copy.
 * @param archive Resource archive.
 * @return Remaining words.
 */
s32 resident_archive_get_copy_remaining(const ResidentArchive* archive);

/**
 * @brief Get the free space the last space query found.
 * @param archive Resource archive.
 * @return Free space in bytes.
 */
u32 resident_archive_get_free_space(const ResidentArchive* archive);

/**
 * @brief Get the space the install needs, rounded up to 256 KiB.
 * @param archive Resource archive.
 * @return Needed space in bytes.
 */
u32 resident_archive_get_install_size(const ResidentArchive* archive);

/**
 * @brief Sum the entries of every resource the install copies.
 * @param archive Resource archive.
 * @return Install size in words.
 */
s32 resident_archive_get_install_words(const ResidentArchive* archive);

/**
 * @brief Set the buffer the install copies through.
 * @param archive Resource archive.
 * @param buffer Copy buffer, or null once the copy is done.
 */
void resident_archive_set_copy_buffer(ResidentArchive* archive, u8* buffer);

/**
 * @brief Set the three BB Navigator files the install writes.
 * @param archive Resource archive.
 * @param first First file.
 * @param first_size Size of first.
 * @param second Second file.
 * @param second_size Size of second.
 * @param third Third file.
 * @param third_size Size of third.
 */
void resident_archive_set_navigator_files(ResidentArchive* archive, u8* first, s32 first_size, u8* second, s32 second_size, u8* third,
                                          s32 third_size);

/**
 * @brief Hand the system files and their icon header to the hard disk worker.
 * @param archive Resource archive.
 * @param header Icon header.
 * @param first First file.
 * @param first_size Size of first.
 * @param second Second file.
 * @param second_size Size of second.
 * @param third Third file.
 * @param third_size Size of third.
 * @param fourth Fourth file.
 * @param fourth_size Size of fourth.
 */
void resident_archive_set_system_files(ResidentArchive* archive, u8* header, u8* first, s32 first_size, u8* second, s32 second_size, u8* third,
                                       s32 third_size, u8* fourth, s32 fourth_size);

/**
 * @brief Wait for the next display interrupt and return the retained GS field bit.
 * @param root Resident input and display state.
 * @param mode Minus one reads the field without waiting; other values wait.
 * @return Retained display field, zero or one.
 */
u32 func_0011DF10(struct ResidentInputSystem* root, s32 mode);

/**
 * @brief Release pending allocations, then destroy pending objects and flush the cache.
 * @param queues Deferred release queues to drain.
 */
void resident_drain_release_queues(ResidentReleaseQueues* queues);

/** Store the word at receiver offset 0x8 and clear its byte at offset 0x2F9. */
void func_0011DF60(void* object, u32 value);
/** Return the word at receiver offset 0x8. */
u32 func_0011DF70(const void* object);
/** Clear the word at receiver offset 0x8 and its byte at offset 0x2F9. */
void func_0011DF80(void* object);


/** Store the byte constant at receiver offset 0x1012. */
void func_001140F0(void* object);

void func_0010EE50(void* object);

/**
 * @brief Store a word and pointer at receiver offsets 0x10 and 0x14.
 * @param object Receiver to update.
 * @param value Word stored at offset 0x10.
 * @param pointer Pointer stored at offset 0x14.
 */
void func_00112D70(void* object, u32 value, void* pointer);

void func_00113180(void* object);
void func_00113EA0(void* object);

/**
 * @brief Return the state byte or wait for it to clear when requested.
 * @param object State receiver whose byte is at offset 0x1011.
 * @param wait Nonzero returns the current byte; zero waits until it is clear.
 * @return Current state byte when waiting is disabled, otherwise zero.
 */
u32 func_00113EB0(void* object, s32 wait);
void func_00114450(void* object);

/** Return whether waking the resident thread succeeds. */
s32 func_00114DD0(const void* object);
/** Return whether the resident thread sleep request succeeds. */
s32 func_00114E80(void);
/** Return whether the resident thread starts successfully. */
s32 func_00114EB0(void* object);

/** Call func_00114E00 with the second argument. */
void func_00118B80(void* object, void* value);

void func_0011C6B0(void* object);
/** Return bit 0 of the word at receiver offset 0xCC. */
s32 func_0011C7C0(const void* object);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** Clear the receiver's eight retained request buffers. */
void func_00110C60(ResidentSound* request);

/** Reconfigure the resident request receiver. */
s32 func_001106B0(ResidentSound* request, s32 value);

/** Synchronize the GS path while holding the receiver's semaphore. */
s32 func_0011DE00(void* object, s32 first, s32 second);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
    void func_00114650(void* object, s32 value);

    u32 func_00113930(ResidentHeap* heap, u32 size);

    u32 func_001138B0(ResidentHeap* heap, void* address, u32 size);
}
#endif

#endif
