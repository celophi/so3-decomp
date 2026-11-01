#ifndef SO3_MAIN_RESIDENT_0010A0E0_H
#define SO3_MAIN_RESIDENT_0010A0E0_H

#include "types.h"
#include "main/resident_00101550.h"
#include "main/resident_001001E0.h"

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

#ifdef __cplusplus
    /** @brief Drain both release rings. */
    ~ResidentReleaseQueues();
#endif
} ResidentReleaseQueues;

struct ResidentInputSystem;

/** Pads the input system reads. */
#define RESIDENT_PAD_COUNT 2

/** Analog axes of a pad: right stick x and y, then left stick x and y. */
#define RESIDENT_PAD_AXIS_COUNT 4

/** Pressure-sensitive buttons of a pad. */
#define RESIDENT_PAD_PRESSURE_COUNT 12

/** Resources in the archive's table of contents. */
#define RESIDENT_RESOURCE_COUNT 0x1800

/** Values of g_system's status byte. */
enum ResidentStatus
{
    /** Set when the status byte is allocated. */
    RESIDENT_STATUS_CLEAN = 0x66,

    /** Set when main's code no longer matches the copy in the program image. */
    RESIDENT_STATUS_TAMPERED = 0x67
};

/** Sixteen keyed full-word entries in the resident system. */
typedef struct ResidentEntryTable
{
    u32 entries[16];
    s32 keys[16];
} ResidentEntryTable;

/** Clock bytes the archive's clock query fills. */
typedef struct ResidentClock
{
    u8 status;
    u8 second;
    u8 minute;
    u8 hour;
    u8 unk04[4];
} ResidentClock;

/** Tag at the head of the resource table once it is decrypted. */
#define RESIDENT_ARCHIVE_TABLE_TAG 0x34829314

/**
 * The game's resource archive: the packed entry of every resource, plus the worker that installs the archive to the
 * PlayStation BB Unit (the hard disk) and reports its progress.
 */
typedef struct ResidentArchive
{
    u8 unk00[0x6C];
    u8 unk6c;
    u8 unk6d[0x5C];
    u8 unkc9;
    u8 unkca[0xE];

    /** Thread the disc power-off callback is given. */
    u8 unkD8[0x14];

    /** Hard disk worker thread; its fields up to navigator_file_sizes follow. */
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

    /** Thread that constructed the archive. */
    s32 main_thread_id;

    /** RESIDENT_ARCHIVE_TABLE_TAG once the resource table is decrypted; the first table word holds it until then. */
    u32 table_tag;

    /** Per resource: its position in the archive in 2048-byte blocks in the low 24 bits. */
    u32 resource_positions[RESIDENT_RESOURCE_COUNT];

    /** Per resource: its size in 2048-byte blocks in the low 24 bits. */
    u32 resource_entries[RESIDENT_RESOURCE_COUNT];

    /** Per resource: nonzero when the install copies it. */
    u32 install_flags[RESIDENT_RESOURCE_COUNT];

    u8 unk1217c[7];

    /** Set while a resource read is in progress; the reading thread clears it. */
    volatile u8 read_busy;

    u8 unk12184;
    u8 unk12185;
    u8 unk12186;

#ifdef __cplusplus
    /** @brief Destroy the archive and its install worker. */
    ~ResidentArchive();

    /** @brief Get the hard disk worker thread. @return Worker thread at unkEC. */
    class ResidentThread* disk_worker()
    {
        return reinterpret_cast<class ResidentThread*>(unkEC);
    }
#endif
} ResidentArchive;

/** Object a positional sound comes from; only its flag for an attached sound is known. */
typedef struct ResidentSoundEmitter
{
    u8 unk000[0x20E];
    u8 unk20e_0_3 : 4;

    /** Set while a sound slot plays from the object; cleared once no slot follows it any more. */
    u8 has_sound : 1;

    u8 unk20e_5_7 : 3;
} ResidentSoundEmitter;

/** One of the sixty sound slots: a sound effect or voice the stream plays. */
typedef struct ResidentRequestSlot
{
    u8 active;

    /** Set once the stream has answered the play request with a voice handle. */
    u8 started;

    /** A stop that has to wait for the stream's answer. */
    u8 stop_requested;

    u8 unk03;

    /** Set when the slot owns buffer and deletes it when it stops. */
    u8 owns_buffer;

    u8 selector;
    u8 unk06[2];
    u16 value;
    u8 unk0a[2];

    /** Voice handle from the stream. */
    u32 handle;

    s32 identifier;

    /** Mode passed with the stop. */
    s32 stop_mode;

    s32 volume;
    u8 unk1c;
    u8 unk1d[3];

    /** Object a positional sound comes from, or null. */
    struct ResidentSoundEmitter* target;

    /** Sound data the slot plays. */
    u8* buffer;

    u32 unk28;
    u32 unk2c;
    u32 unk30;
    u32 unk34;
    u32 unk38;
} ResidentRequestSlot;

#ifdef __cplusplus
class ResidentStreamThread;


/** A sound bank load waiting in the stream's bank queue. */
struct ResidentBankRequest
{
    /** Sound file: a SEQ or SEQW file (optionally followed by its WAV chunk), or a bare WAV chunk. */
    const void* file;

    /** Receives the loaded size once the bank is in place, or zero when it was dropped; may be null. */
    s32* result;

    /** Bank ID and priority from the sequence header. */
    s16 bank_id;

    s8 priority;

    /** Set once the upload is done and the load waits for func_00106640 to continue it. */
    u8 waiting;

    /** Wave data size from the WAV chunk. */
    s32 wave_size;

    u32 unk10;
    u32 unk14;
    u32 unk18;
    u32 unk1C;
    u32 unk20;
};

/** A sequence upload waiting in the stream's sequence queue. */
struct ResidentSequenceRequest
{
    /** Bytes still to send. */
    s32 remaining;

    /** Next byte to send. */
    const u8* cursor;

    /** Sound file the request was made for. */
    const void* file;

    s32 unk0C;

    /** Entry of the stream's slot table the sequence belongs to. */
    u8 slot;

    u32 unk14;
    u32 unk18;

    /** Receives the IOP's reply once the upload finishes; may be null. */
    s32* result;
};

/** One of the four regions of sound memory the stream loads banks into. */
struct ResidentStreamChannel
{
    /** Size of the bank held here; zero when free, negative when the region continues the previous one's bank. */
    s32 size;

    s16 bank_id;
    s8 priority;

    /** Load counter value when the bank was loaded; the oldest bank is replaced first. */
    u32 age;

    /** Sound memory address of the region. */
    u32 address;

    /** Entry of the stream's slot table for this region. */
    u8 slot;
};

/** Sound stream at g_system + 0x15A5C: queues sound bank loads and sequence uploads for the IOP; vtable D_0014FA90. */
class ResidentSoundStream : public ResidentListener
{
    public:
        u8 unk04[0x40];
        u32 unk44;
        u8 unk48[0x44];

        /** Set while a thread is waiting for the stream thread. */
        u8 waiting;

        /** Thread that talks to the IOP. */
        ResidentStreamThread* thread;

        /** Load counter stored in each channel's age. */
        u32 next_age;

        ResidentStreamChannel channels[4];

        /** Step of the bank load at the front of the bank queue. */
        u8 bank_state;

        u8 bank_channel;
        u8 bank_first_channel;
        u8 bank_channel_count;

        /** IOP request the bank load waits for. */
        s32 bank_request;

        /** Results of the bank load's IOP requests. */
        s32 bank_status[4];

        u8 unk100[0x30];
        u32 bank_address;
        u8 bank_slot;

        /** Ring of 32 bank requests: storage, read and write positions, and end. */
        ResidentBankRequest* bank_queue;

        ResidentBankRequest* bank_read;
        ResidentBankRequest* bank_write;
        ResidentBankRequest* bank_queue_end;

        /** Step of the upload at the front of the sequence queue. */
        u8 sequence_state;

        /** IOP address uploads are sent to. */
        u32 sequence_address;

        /** IOP request the upload waits for. */
        s32 sequence_request;

        /** Result of the upload's IOP request. */
        s32 sequence_status;

        u8 unk158[0x3C];

        /** Ring of 32 sequence requests: storage, read and write positions, and end. */
        ResidentSequenceRequest* sequence_queue;

        ResidentSequenceRequest* sequence_read;
        ResidentSequenceRequest* sequence_write;
        ResidentSequenceRequest* sequence_queue_end;

        /** Loaded sound files, by slot. */
        void* slots[32];

        /**
         * @brief Handle a SIF command from the IOP.
         * @param data Command number.
         */
        virtual void notify(void* data);

        /** @brief Free the queues, the loaded files and the stream thread. */
        virtual ~ResidentSoundStream();
};
#else
typedef struct ResidentSoundStream ResidentSoundStream;
#endif

/** Voice table the sound system reads from its voice file: where each voice lies in the file. */
typedef struct ResidentVoiceTable
{
    u32 count;

    struct
    {
        /** First 2048-byte block of the voice. */
        u16 block;

        /** Length of the voice in 2048-byte blocks. */
        u16 block_count;
    } entries[1];
} ResidentVoiceTable;

/** How one piece of music is played. */
typedef struct ResidentMusicEntry
{
    /** Nonzero when the music is read into memory in one piece, zero when it streams. */
    u8 in_memory;

    u8 unk01;

    /** Resource key of the music. */
    u16 resource;
} ResidentMusicEntry;

/**
 * The sound system: sound effects and voices in sixty slots, streamed music, and the surround output with its
 * listener and speaker placement.
 */
struct ResidentSound
{
    struct ResidentSoundStream* stream;
    ResidentArchive* archive;
    ResidentResourceQueue* resource_queue;
    void* unk0c;

    /** Number of entries in music_entries. */
    s32 music_entry_count;

    /** Every piece of music, by music number minus one. */
    const ResidentMusicEntry* music_entries;

    /** Stream handle of each queued music track, oldest first; request callbacks push the handles they get back. */
    u32 music_handles[3];

    /** Key of each queued music track. */
    s32 music_keys[3];

    /** Number of queued music tracks. */
    s32 music_count;

    /**
     * Handles pushed onto music_handles; request callbacks push from other threads.
     * TODO: volatile is my guess from that; it's the only form I found where func_0010DEF0 rereads the count.
     */
    volatile u32 unk34;

    /** Index of the music track being faded, or -1. */
    s32 unk38;

    s32 unk3c;
    s32 unk40;
    u8 unk44[0xCC];
    u8 state;
    u8 unk111;
    u8 unk112[2];
    u32 unk114;
    u8 unk118[0x1E0];
    struct ResidentRequestSlot* unk2F8[15];
    u32 unk334;
    u32 unk338;
    s32 unk33c;

    /** Volume, 0 to 0x7FFF. */
    s32 volume;

    /** Volume after the volume scale, 0 to 0x7FFF. */
    s32 scaled_volume;

    u8 unk348;
    u8 unk349[3];
    float unk34c;
    u8 unk350;
    u8 unk351;
    u8 unk352;
    u8 unk353;
    u8 unk354;
    u8 unk355;
    u8 unk356;
    u8 unk357[9];
    const void* unk360;
    u8 unk364[4];
    const void* unk368;
    u8 unk36c[4];

    /** Set when music is unavailable; the music calls then do nothing and report success. */
    u8 music_disabled;

    /** Set when sound effects and voices are unavailable; their calls then do nothing and report success. */
    u8 effects_disabled;

    u8 unk372[0x4A];
    s32 unk3bc;
    u8 unk3c0[0x40];
    u8* unk400;
    u32 unk404;

    /** Table of the voices in the voice file, read when the file is set. */
    ResidentVoiceTable* voice_table;

    /** File key of the voice file, or zero when there is none. */
    s32 voice_file_key;

    /** Voices read ahead of time, or null. */
    u8* voice_buffers[8];

    /** Voice index held in each of voice_buffers. */
    s32 voice_indices[8];

    /** Sound output mode: 1 mono, 0 stereo, 2 Dolby Pro Logic II, 3 headphones. */
    u8 output_mode;

    u8 unk451;
    u8 unk452;
    u8 unk453;
    u32 unk454[32];
    s32 unk4d4;

    /** Handler of the sound interrupt. */
    s32 interrupt_handler;

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

    float unk13ac[4];
    void* unk13bc[32];
    s32 unk143c;

#ifdef __cplusplus
    /** @brief Remove the sound interrupt handler and free the sound buffers. */
    virtual ~ResidentSound();
#endif
};

typedef struct ResidentSound ResidentSound;

/** Partial resident DMA queue exposing the asynchronously cleared busy flag. */
typedef struct ResidentDmaQueue
{
    u8 unk00[0x1011];
    volatile u8 busy;
} ResidentDmaQueue;

/** Tag of an allocated heap block. */
#define RESIDENT_HEAP_BLOCK_TAG 0x4D655279

/** Marker of an allocated heap block. */
#define RESIDENT_HEAP_BLOCK_MARKER 0x4058

#ifdef __cplusplus
class ResidentHeap;

/** Header in front of every block of a resident heap, allocated or free. */
struct ResidentHeapBlock
{
    /** Size of the block, header included. */
    s32 size;

    u8 flags;
    u8 allocated;

    /** RESIDENT_HEAP_BLOCK_MARKER while the block is allocated. */
    u16 marker;

    ResidentHeapBlock* physical_previous;
    ResidentHeapBlock* physical_next;
    ResidentHeap* owner;
    ResidentHeapBlock* free_next;
    ResidentHeapBlock* free_previous;

    /** RESIDENT_HEAP_BLOCK_TAG while the block is allocated. */
    u32 tag;
};

/** A resident allocation heap: blocks carved from one memory range, with up to eight child heaps to fall back on. */
class ResidentHeap
{
    public:
        /** Permanently allocated block that starts and ends the block lists. */
        ResidentHeapBlock head;

        /** Block the free list starts and ends at; it points to head once the heap has memory. */
        ResidentHeapBlock* free_anchor;

        /** Memory the heap allocated for itself, or null. */
        void* memory;

        /** Nonzero to allocate from the child heaps when this one has no room. */
        u8 use_fallbacks;

        /** Nonzero to allocate from the top of the free blocks instead. */
        u8 alternate;

        u8 unk2a[2];

        /** Alignment of every allocation, a power of two. */
        s32 alignment;

        s32 fallback_count;
        ResidentHeap* fallbacks[8];

        /** @brief Construct an empty heap with no memory, 16-byte alignment and child heaps enabled. */
        inline ResidentHeap();

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

#ifdef __cplusplus
/** Kernel thread with its own stack; vtable D_0014FBA0. */
class ResidentThread
{
    public:
        /** Priority the thread was created with. */
        s32 priority;

        /** Stack the thread runs on. */
        u8* stack;

        /** Kernel thread ID, or negative before the thread is created. */
        s32 thread_id;

        /** @brief Stop and delete the kernel thread. */
        virtual ~ResidentThread();

        /** @brief Start the kernel thread. @return Nonzero on success. */
        virtual s32 start();

        /** @brief The thread's body; the base class does nothing. */
        virtual void run();
};

/** Thread that shares the CPU with the scheduler's other threads in time slices; vtable D_0014FB60. */
class ResidentTimeSlicedThread : public ResidentThread
{
    public:
        /** Horizontal syncs the thread runs before the next one gets its turn. */
        s16 time_slice;

        /** @brief Remove the thread from the scheduler and destroy it. */
        virtual ~ResidentTimeSlicedThread();
};

/** Thread that hands out time slices to up to eight time-sliced threads in turn; vtable D_0014FB80. */
class ResidentThreadScheduler : public ResidentThread
{
    public:
        u8 unk10[0x20];

        /** Threads that take turns, or null. */
        ResidentTimeSlicedThread* threads[8];

        /** Thread whose slice is running, or null. */
        ResidentTimeSlicedThread* current;

        // TODO: next and alarm_id are volatile because the alarm handler changes them from interrupt context; the
        // target reloads them after every store and test, and nothing else I tried does that.

        /** Index of the next thread to get a slice. */
        volatile s32 next;

        ResidentSemaphore semaphore;

        /** Set while slices are being handed out. */
        u8 active;

        u8 unk61[7];

        /** Alarm that ends the running slice, or -1. */
        volatile s32 alarm_id;

        /** @brief Destroy the scheduler and its semaphore. */
        virtual ~ResidentThreadScheduler();
};

/** Thread that runs the hard disk worker's commands; vtable D_0014FBC0. */
class ResidentArchiveWorker : public ResidentThread
{
    public:
        u8 unk10[0x24];
        ResidentSemaphore unk34;
        ResidentSemaphore unk3c;

        /** @brief Destroy the worker and its semaphores. */
        virtual ~ResidentArchiveWorker();
};

class ResidentStreamDma;

/**
 * Thread owned by the sound stream that moves stream data between the IOP and VU1: it sends blocks to the IOP and
 * fills two output buffers. The sound stream's thread pointer points to one. Vtables D_0014FAE0 and D_0014FAF0
 * (the thread).
 */
class ResidentStreamThread : public ResidentListener, public ResidentThread
{
    public:
        u8* allocation;
        u8 unk18[2];

        /** Which of the two output buffers is filling. */
        u8 output_half;

        /** Which of the two output buffers unk20 points into. */
        u8 unk1B;

        /** Next block of the output buffer. */
        u8* output_cursor;

        u8* unk20;
        u8* unk24;
        s32 unk28;

        /** Blocks left to transfer into each output buffer. */
        s32 output_pending[2];

        u32 unk34[2];

        /** The two output buffers; the first is the allocation rounded up to 128 bytes. */
        u8* output_buffers[2];

        u8* unk44;

        /** Per input (send) block: set once the block has data. */
        u8 input_ready[2];

        /** Send block in use. */
        u8 unk4A;

        /** Which of the two input buffers is filling. */
        u8 input_half;

        /** Next 0x1000-byte chunk of the send block, behind its 0x40-byte header. */
        u8* unk4C;

        /** Next block of the input buffer. */
        u8* input_cursor;

        /** Per send block: chunks left to send. */
        s32 unk54[2];

        /** Per send block: IOP address the chunks go to. */
        void* unk5C[2];

        /** The two input buffers. */
        u8* input_buffers[2];

        u8* unk6C;
        u8* unk70;
        s32 unk74;

        /** Per ring half: nonzero once the half is full. */
        u8 unk78[2];

        u8 unk7A;

        /** Ring half being written. */
        u8 unk7B;

        /**
         * Read position in the ring. The ring pointers are shared with interrupt context.
         * TODO: volatile is my guess from that; nothing else rereads them the way func_0010A530 does.
         */
        u8* volatile unk7C;

        /** Write position in the ring. */
        u8* volatile unk80;

        /** Start of the ring (uncached address). */
        u8* volatile unk84;

        /** Start of the ring's second half (uncached address). */
        u8* volatile unk88;

        /** End of the ring (uncached address). */
        u8* volatile unk8C;

        s32 unk90;
        u8 unk94;
        u8 unk95;
        u8 unk96;
        s32 unk98;
        void* unk9C;
        s32 unkA0;
        u32 unkA4;
        u32 unkA8;

        /** First state the IOP reports; func_0010A0B0 sets it to one from the SIF interrupt handler. */
        volatile s32 first_state;

        /** Second state the IOP reports; func_0010A080 sets it to one from the SIF interrupt handler. */
        volatile s32 second_state;

        u8 unkB4[4];

        /** Nonzero while a send block is queued. */
        u8 unkB8;

        u8 unkB9;

        /** Set while the send path runs, so it isn't entered twice. */
        u8 unkBA;

        /** Chunks sent from the current block. */
        u8 unkBB;

        s8 unkBC;
        u8 unkBD;
        u8 unkBE;
        s32 unkC0;
        u8 unkC4[4];

        /** Next free byte of the debug byte log. */
        u8* log_cursor;

        /** Byte sent in the header of each chunk, by chunk number. */
        u8 unkCC[0x20];

        /**
         * Thread to wake after the next pass of the streaming thread, or zero; other threads set it, then sleep.
         * TODO: volatile is my guess from that; it's the only form I found where func_0010B4C0 rereads it.
         */
        volatile s32 waiting_thread;

        u32* unkF0;
        u32* unkF4;
        ResidentSoundStream* stream;
        u8 unkFC[4];

        /** DMA transfer the thread queues on VIF1. */
        ResidentStreamDma* dma;

        u8 unk104;
        ResidentSemaphore semaphore;
        s32 unk110;

        /** @brief Handle a SIF command forwarded to the thread. @param data Command data. */
        virtual void notify(void* data);

        /** @brief Free the buffers and stop the thread. */
        virtual ~ResidentStreamThread();

        virtual void run();
};

/** VIF1 DMA transfer of the stream thread, with two sample rings it reads back; vtable D_0014FAC0. */
class ResidentStreamDma : public DmaSubmission
{
    public:
        ResidentStreamThread* owner;

        /** Uncached address the next transfer writes to. */
        u32 output;

        /** Which DMA chain the next transfer sends: 1 or 2, or 0 when idle. */
        s8 phase;

        /** Each ring's start, the shared ring size, and each ring's read and write positions. */
        u32 ring_start[2];

        u32 ring_size;
        u32 ring_read[2];
        u32 ring_write[2];

        virtual void submit_dma(u32 channel);
        virtual void complete_dma(u32 channel);
};

/** A command the SIF link sends once the IOP has room for it. */
typedef struct ResidentSifQueuedCommand
{
    s32 command;
    void* source;
    void* destination;
    s32 size;
} ResidentSifQueuedCommand;

/** Where a reply from the IOP goes, and who hears about it. */
typedef struct ResidentSifReply
{
    u32 unk00;

    /** Receives a copy of the reply, or null to leave it in the link's reply buffer. */
    u32* buffer;

    /** Called with the reply and argument, or null. */
    void (*callback)(void* reply, void* argument);

    void* argument;
    u32 unk10;
} ResidentSifReply;

/**
 * The EE side of the link with the IOP: the SIF command handlers, the RPC binding to server 0x1234, a ring of
 * reply slots and a queue for commands the IOP couldn't take yet. Its kernel thread has vtable D_0014FB10.
 */
class ResidentSif : public ResidentThread
{
public:
    /** Allocation the buffers below are carved from. */
    u8* allocation;

    s32 unk14;

    /** Reply slot the last reply went to. */
    s32 reply_index;

    s32 unk1C;
    ResidentSifReply replies[32];

    /** The allocation rounded up to 64 bytes. */
    u8* buffer;

    u8* unk2A4;

    /** Where replies from the IOP arrive. */
    u32* reply_data;

    u8* unk2AC;
    u8* unk2B0;
    SifClientData rpc_client;
    u8 unk2DC[4];
    u8* unk2E0[5];
    SifCommandHandlerEntry handlers[5];
    u8 unk31C[0x10];
    ResidentSemaphore unk32C;
    ResidentSemaphore unk334;

    /** Next packet for sends from interrupt context. */
    s32 interrupt_packet_index;

    SifCommandHeader interrupt_packets[256];

    /** Queue slot sent last; the queue is empty when the next slot is write_index. */
    s32 queue_read_index;

    /** Next free queue slot; the queue is full when it equals queue_read_index. */
    s32 queue_write_index;

    ResidentSifQueuedCommand queue[256];
    u8 unk2348[8];
    SifCommandHeader queue_packets[256];
};

/** The input system's pad polling thread, at g_system + 0x1784; vtable D_0014FC60. */
class ResidentClass14FC60 : public ResidentThread
{
    public:
        /** Input system the thread polls. */
        ResidentInputSystem* input;

        /** Set while the thread is reading the pads. */
        u8 polling;

        u8 unk15[3];

        /** @brief Destroy the thread. */
        virtual ~ResidentClass14FC60()
        {
        }
};

/** Display the vblank handler updates; only the fields the input system touches are known. */
struct ResidentDisplay
{
    u8 unk0000[0x3E40];
    s32 unk3e40;
    u8 unk3e44[0x21];

    /** Set while the input system's vblank handler updates this display. */
    u8 vblank_enabled;
};

/** Object that takes over a frame's pad input; the poll calls it after reading both pads. */
class ResidentPadHook
{
    public:
        virtual void func_slot08();

        /** @brief Handle the pads the poll just read. @param input Input system. */
        virtual void update(ResidentInputSystem* input);
};

/**
 * The two pads (buttons, sticks and vibration) and the vblank counters that time each frame, at g_system + 0x1480.
 * It owns a polling thread and a semaphore.
 */
struct ResidentInputSystem
{
    u8 unk000[4];

    /** Vblank interrupt handler ID. */
    s32 vblank_handler;

    /** Seconds counted from vblanks. */
    u32 seconds;

    /** Vblanks since a wait for the next vblank cleared it; the vblank handler counts it. */
    volatile u32 vblank_wait_count;

    /** Vblanks since the count was last taken. */
    u32 vblank_count;

    /** Object that takes over pad input, or null for normal button processing. */
    ResidentPadHook* hook;

    u8 unk018[0x28];

    /** DMA buffer of each pad's socket. */
    u8 pad_buffers[RESIDENT_PAD_COUNT][0x100];

    s32 sockets[RESIDENT_PAD_COUNT];

    /** Socket state from the last poll; one when the pad is ready. */
    s32 states[RESIDENT_PAD_COUNT];

    s32 unk250;
    u8 unk254[0xC];

    /** Buttons held this frame. */
    u16 held[RESIDENT_PAD_COUNT];

    /** Buttons held last frame. */
    u16 previous_held[RESIDENT_PAD_COUNT];

    /** Buttons held at some point since the latches were cleared. */
    u16 held_since_clear[RESIDENT_PAD_COUNT];

    /** Buttons newly pressed since the latches were cleared. */
    u16 pressed[RESIDENT_PAD_COUNT];

    /** Frames the same buttons have been held, up to repeat_delay. */
    u8 repeat_counts[RESIDENT_PAD_COUNT];

    /** Polls to skip after a pad error before reading it again. */
    u8 retry_delays[RESIDENT_PAD_COUNT];

    /** Raw analog stick axes. */
    u8 sticks[RESIDENT_PAD_COUNT][RESIDENT_PAD_AXIS_COUNT];

    /** Pressure of each pressure-sensitive button. */
    u8 pressures[RESIDENT_PAD_COUNT][RESIDENT_PAD_PRESSURE_COUNT];

    /** Set while the pad reports analog sticks. */
    u8 analog[RESIDENT_PAD_COUNT];

    /** Set to map the left stick onto the direction buttons. */
    u8 stick_dpad[RESIDENT_PAD_COUNT];

    u8 vibration_enabled[RESIDENT_PAD_COUNT];

    /** Set when the motor levels changed and must be sent to the pad. */
    u8 vibration_dirty[RESIDENT_PAD_COUNT];

    /** Set once the pad's vibration profile has been read. */
    u8 vibration_profile_read[RESIDENT_PAD_COUNT];

    /** Largest value each stick axis reports. */
    u8 stick_limits[RESIDENT_PAD_COUNT][RESIDENT_PAD_AXIS_COUNT];

    /** Stick distance from centre that reads as zero. */
    u8 dead_zones[RESIDENT_PAD_COUNT];

    u8 unk2a8[RESIDENT_PAD_COUNT];

    /** Vibration profile, then the motor parameters sent to the pad. */
    u8 vibration_profiles[RESIDENT_PAD_COUNT][0x20];

    u8 unk2ea[2];

    /** Centre offset of each stick axis. */
    s8 stick_offsets[RESIDENT_PAD_COUNT][RESIDENT_PAD_AXIS_COUNT];

    /** Small motor, on when nonzero. */
    u8 small_motor[RESIDENT_PAD_COUNT];

    /** Large motor strength. */
    u8 large_motor[RESIDENT_PAD_COUNT];

    /** Frames buttons must be held before they repeat. */
    u8 repeat_delay;

    /** Vblanks counted towards the next second. */
    u8 second_vblanks;

    /** GS field (zero or one) at the last vblank. */
    u8 field;

    /** Set to update the attached display each vblank. */
    u8 display_enabled;

    u8 unk2fc;
    u8 unk2fd[3];

    /** Vblanks since the input system started. */
    u32 vblank_total;

    ResidentClass14FC60 poll_thread;
    ResidentSemaphore semaphore;

    /** Display updated each vblank, or null. */
    ResidentDisplay* display;

    u8 unk328[0x18];
};

/**
 * The resident system g_system, which outlives every program. It holds the sound system, the resource archive, the
 * entry table, the release and resource queues and the decoder that loads each program's overlay, and it switches
 * from one program to the next.
 */
struct ResidentSystem
{
    /** @brief Destroy every part of the system. */
    ~ResidentSystem();

    /** @brief Free the system through the resident heap. @param memory Allocation, or null. */
    static void operator delete(void* memory) throw()
    {
        resident_delete(memory);
    }

    ResidentSound sound;
    u8 unk_sound_end[0x1480 - sizeof(ResidentSound)];
    ResidentInputSystem input;
    ResidentArchive archive;
    u8 unk_archive_end[0x1398C - 0x17C0 - sizeof(ResidentArchive)];

    /** Decoder that unpacks each program's overlay. */
    ResidentDecodeObject decoder;

    u8 unk1398D[3];
    ResidentEntryTable entry_table;
    ResidentReleaseQueues release_queues;
    ResidentResourceQueue resource_queue;
    ResidentSoundStream sound_stream;
    u32 unk15C80;

    /** Nonzero for progressive (525p) output. */
    u8 progressive;

    u8 unk15C85[0xB];
    u32 unk15C90;
    u32 unk15C94;
    u32 unk15C98;

    /** Main's stack and frame pointers, restored when switching programs. */
    void* saved_sp;
    void* saved_fp;

    u8 unk15CA4[0xC];

    /** Key that decrypts SLE resource blocks. */
    unsigned __int128 sle_key;

    /** Status byte (a ResidentStatus), allocated on first use at a random heap address. */
    u8* status;
};
#endif

typedef struct ResidentSystem ResidentSystem;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Start reading the resource func_0011D080 selected.
 * @param archive Resource archive.
 * @param buffer Destination.
 * @param size Bytes to read, or zero for the whole resource.
 * @return Nonzero when the read started.
 */
s32 func_0011CC00(ResidentArchive* archive, void* buffer, s32 size);

/**
 * @brief Start reading the selected resource without checking the result.
 * @param archive Resource archive.
 * @param buffer Destination.
 * @param size Bytes to read, or zero for the whole resource.
 */
void func_0011D060(ResidentArchive* archive, void* buffer, s32 size);

/**
 * @brief Forward the manager's first pointer and the argument to func_00107D90.
 * @param argument Value forwarded as the helper's second argument.
 */
void func_0010DFC0(const s32* value);

/** Run the resident helper on the object's pointer when it is non-null. */
void func_0010ECF0(ResidentSound* sound);

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

/** The resident system. */
extern ResidentSystem g_system;

/**
 * @brief Read the clock.
 * @param archive Resource archive.
 * @param clock Receives the clock bytes.
 * @return Nonzero on success.
 */
s32 resident_archive_get_clock(ResidentArchive* archive, ResidentClock* clock);

/** @brief Seed the resident random sequence; main seeds it from timer 0. @param seed Seed value. */
void func_0010D100(u32 seed);

/** @brief Archive setup that main runs right after rebooting the IOP. @param archive Resource archive. */
void func_0011DA80(ResidentArchive* archive);

/**
 * @brief Read and decrypt the archive's table of contents; main runs it after storing its arguments.
 * @param archive Resource archive.
 * @return One once the table is loaded, or zero while another read is running.
 */
s32 func_0011D470(ResidentArchive* archive);

/**
 * @brief Select the resource the next read loads; main passes 1 for the IOP modules and 2 for the programs.
 * @param archive Resource archive.
 * @param key Resource key.
 * @return Nonzero when the resource was selected.
 */
s32 func_0011D080(ResidentArchive* archive, s32 key);

/**
 * @brief Set the listener the archive notifies when a read finishes.
 * @param archive Resource archive.
 * @param listener Listener, or null to remove it.
 * @param context Object passed back to the listener.
 */
void func_0011D320(ResidentArchive* archive, struct ResidentListener* listener, void* context);

/** @brief Abort the archive's current read. @param archive Resource archive. */
void func_0011BA90(ResidentArchive* archive);

/**
 * @brief Install the disc power-off callback and start the hard disk worker; main runs it once the IOP modules are
 * loaded.
 * @param archive Resource archive.
 */
void func_0011D950(ResidentArchive* archive);

#ifdef __cplusplus
/** The SIF link with the IOP. */
extern ResidentSif D_001CC590;

/**
 * @brief Set up the SIF link: carve its buffers, register its SIF command handlers and start its thread.
 * @param sif SIF link.
 */
void func_0010C700(ResidentSif* sif);

/**
 * @brief Wait a moment, then try to bind the SIF link's RPC client to server 0x1234.
 * @param sif SIF link.
 * @return Zero once the server answers, minus one when binding fails.
 */
s32 func_0010C640(ResidentSif* sif);

/**
 * @brief Send queued SIF commands until the queue is empty or the IOP has no room.
 * @param sif SIF link.
 */
void func_0010BD10(ResidentSif* sif);

/**
 * @brief Queue a SIF command to send later.
 * @param sif SIF link.
 * @param command Command ID.
 * @param source EE data sent with the command.
 * @param destination IOP address of the data.
 * @param size Data size in bytes.
 * @param in_interrupt Nonzero when called with interrupts already disabled.
 * @return One when queued, zero when the queue is full.
 */
s32 func_0010BDA0(ResidentSif* sif, s32 command, void* source, void* destination, s32 size, s32 in_interrupt);

/**
 * @brief Send a SIF command from interrupt context, queueing it if earlier commands are waiting or the IOP has no
 * room.
 * @param sif SIF link.
 * @param command Command ID.
 * @param source EE data sent with the command.
 * @param destination IOP address of the data.
 * @param size Data size in bytes; zero sends nothing.
 */
void func_0010BE80(ResidentSif* sif, s32 command, void* source, void* destination, s32 size);

/**
 * @brief Check whether a request sent over the SIF link is still waiting for its reply.
 * @param sif SIF link.
 * @param handle Request handle.
 * @return Nonzero while the request is outstanding.
 */
s32 func_0010C0E0(ResidentSif* sif, u32 handle);

/**
 * @brief Send a SIF command, queueing it if earlier commands are waiting or the IOP has no room.
 * @param sif SIF link.
 * @param command Command ID.
 * @param source EE data sent with the command.
 * @param destination IOP address of the data.
 * @param size Data size in bytes; zero sends nothing.
 */
void func_0010BFA0(ResidentSif* sif, s32 command, void* source, void* destination, s32 size);

/**
 * @brief Move to the next reply slot and deliver the reply in the reply buffer to it.
 * @param sif SIF link.
 */
void func_0010C420(ResidentSif* sif);
#endif

/** @brief Start the input system. @param input Input system. */
void func_0011EA80(struct ResidentInputSystem* input);

/** @brief Start the sound system and its stream. @param sound Sound system. */
void func_00112D80(ResidentSound* sound);

/** One entry of the table func_0010EC00 sends to the stream. */
typedef struct ResidentSoundSetupEntry
{
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0C;
    u32 unk10;
} ResidentSoundSetupEntry;

/**
 * @brief Construct the sound system.
 * @param sound Sound system to construct.
 * @return The constructed sound system.
 */
ResidentSound* func_00112FE0(ResidentSound* sound);

/**
 * @brief Construct the input system.
 * @param input Input system to construct.
 * @return The constructed input system.
 */
struct ResidentInputSystem* func_0011EC30(struct ResidentInputSystem* input);

/**
 * @brief Construct the resource archive.
 * @param archive Archive to construct.
 * @return The constructed archive.
 */
ResidentArchive* func_0011DC00(ResidentArchive* archive);



#ifdef __cplusplus
/**
 * @brief Upload a sound file through the stream into a slot, using that slot's unk454 value.
 * @param sound Sound system.
 * @param file Sound file to upload; kept at unk360.
 * @param index Stream slot, and index into unk454.
 * @param append True to add to the slot's existing data.
 * @return Zero while the sound system is busy, otherwise one.
 */
s32 func_0010EB90(ResidentSound* sound, const void* file, s32 index, bool append);
#endif

/**
 * @brief Send each entry of a setup table to the stream, waiting for each reply and keeping its first word in unk454;
 * main runs it after starting the sound system.
 * @param sound Sound system.
 * @param count Number of entries, below 32.
 * @param entries Setup table.
 * @return One when sent, zero when count is too large.
 */
s32 func_0010EC00(ResidentSound* sound, s32 count, const ResidentSoundSetupEntry* entries);

/**
 * @brief Allocate a buffer for a resource and start loading it; main runs it once the archive is idle.
 * @param sound Sound system.
 * @param key Resource key.
 * @return One when the load started, zero while busy or when the buffer can't be allocated.
 */
s32 func_0010EAD0(ResidentSound* sound, s32 key);

/**
 * @brief Update the sound system; main calls it until sound->state is zero.
 * @param sound Sound system.
 * @param mode Mode.
 */
void func_0010F250(ResidentSound* sound, s32 mode);

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
void func_0010EF50(const void* reply);
/** Run the resident helper on the pointer at offset zero with its final flag set. */
s32 func_0010EFD0(ResidentSound* sound);

/** Return whether the resident double comparison reports left greater than right. */
s32 func_001143E0(double left, double right);
/** Return whether the resident double comparison reports left less than right. */
s32 func_00114400(double left, double right);
/** Return whether the resident double comparison reports the values equal. */
s32 func_00114420(double left, double right);

/**
 * @brief Set a time-sliced thread's slice and create it at the normal resident priority.
 * @param thread Thread.
 * @param time_slice Horizontal syncs per slice.
 * @param stack_size Stack size in bytes.
 * @return Nonzero when the thread was created.
 */
s32 func_00114560(ResidentTimeSlicedThread* thread, s16 time_slice, s32 stack_size);
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
 * @brief Return a random fraction.
 * @return Random value from 0 up to 1.
 */
float func_0010C8E0(void);

/**
 * @brief Return a random number below a limit.
 * @param limit Exclusive upper bound.
 * @return Random number from 0 to limit - 1, or 0 when limit is 0.
 */
u32 resident_random_below(u32 limit);

/**
 * @brief Return a random number between two bounds.
 * @param low First bound, included.
 * @param high Second bound, excluded; it may be below low.
 * @return Random number from low up to (but not including) high, or low when the bounds are equal.
 */
s32 resident_random_range(s32 low, s32 high);

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
void resident_input_attach_display(struct ResidentInputSystem* input, void* display, u8 enabled);

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
 * @brief Choose whether a pad's left stick also presses the direction buttons.
 * @param input Input system.
 * @param slot Pad slot.
 * @param enabled Nonzero to map the stick onto the direction buttons.
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
 * @param right_x Receives the right stick's x axis.
 * @param right_y Receives the right stick's y axis.
 * @param left_x Receives the left stick's x axis.
 * @param left_y Receives the left stick's y axis.
 * @return Nonzero when the pad is in analog mode; the axes are zero otherwise.
 */
s32 resident_pad_get_sticks(struct ResidentInputSystem* input, s32 slot, s32* right_x, s32* right_y, s32* left_x,
                            s32* left_y);

/**
 * @brief Copy a range of a pad's button pressures.
 * @param input Input system.
 * @param slot Pad slot.
 * @param pressures Receives the pressures, zero when the pad isn't analog.
 * @param first First pressure index.
 * @param last Last pressure index, inclusive.
 * @return Nonzero when the pad is in analog mode.
 */
s32 func_0011E290(struct ResidentInputSystem* input, s32 slot, u8* pressures, s32 first, s32 last);

/**
 * @brief Poll both pads: read their buttons, sticks and pressures, update the latches and send vibration.
 * @param input Input system.
 */
void resident_pad_update(struct ResidentInputSystem* input);

/**
 * @brief Count a vblank, update the attached display and wake the pad polling thread.
 * @param input Input system.
 */
void resident_input_handle_vblank(struct ResidentInputSystem* input);

/**
 * @brief Get the position of a resource in the archive.
 * @param archive Resource archive.
 * @param key Resource key.
 * @return Position in 2048-byte blocks.
 */
u32 func_0011C6C0(const ResidentArchive* archive, s32 key);

/**
 * @brief Read a resource and wait for the read to finish, retrying until it starts.
 * @param archive Resource archive.
 * @param buffer Destination.
 * @param key Resource key.
 * @param size Bytes to read, or zero for the whole resource.
 * @return One.
 */
s32 func_0011CA60(ResidentArchive* archive, void* buffer, s32 key, s32 size);

/**
 * @brief Queue an object for destruction by its virtual destructor.
 * @param queue Deferred release queues.
 * @param object Object to destroy later; null succeeds without insertion.
 * @return One on success, or zero when the object ring is full.
 */
s32 resident_enqueue_object(ResidentReleaseQueues* queue, void* object);

/**
 * @brief Play a sound effect in a free slot.
 * @param sound Sound system.
 * @param number Sound number; its low 16 bits are stored.
 * @param selector Request selector.
 * @param value Value forwarded to request dispatch.
 * @param volume Volume, 0x7F for full; stored and packed into the upper byte.
 * @param pan Pan, 0x40 for centre; packed into the next byte.
 * @param low Value packed into the lower 16 bits.
 * @return Slot identifier, zero on dispatch failure, one when disabled, or minus one when no slot is free.
 */
s32 resident_sound_play(ResidentSound* sound, s32 number, s32 selector, s32 value, s32 volume, s32 pan, s32 low);

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

/**
 * @brief Set the seconds clock the vblank handler counts.
 * @param input Input system.
 * @param seconds New clock value.
 */
void func_0011DF60(struct ResidentInputSystem* input, u32 seconds);

/**
 * @brief Get the seconds clock the vblank handler counts.
 * @param input Input system.
 * @return Seconds counted.
 */
u32 func_0011DF70(const struct ResidentInputSystem* input);

/**
 * @brief Reset the seconds clock the vblank handler counts.
 * @param input Input system.
 */
void func_0011DF80(struct ResidentInputSystem* input);


/** Store the byte constant at receiver offset 0x1012. */
void func_001140F0(void* object);

void func_0010EE50(void* object);

/**
 * @brief Set the table of music the sound system plays.
 * @param sound Sound system.
 * @param count Number of entries.
 * @param entries Music entries, by music number minus one.
 */
void func_00112D70(ResidentSound* sound, s32 count, const ResidentMusicEntry* entries);
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

/**
 * @brief Free every voice read ahead of time, cancelling reads still in progress.
 * @param sound Sound system.
 */
void func_00110C60(ResidentSound* sound);

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

    /**
     * @brief Give a heap memory of its own.
     * @param heap Heap.
     * @param size Usable size in bytes.
     * @return Nonzero on success, zero when the memory can't be allocated.
     */
    u32 func_00113930(ResidentHeap* heap, u32 size);

    /**
     * @brief Give a heap a memory range to allocate from.
     * @param heap Heap.
     * @param address Start of the range, or null.
     * @param size Size of the range in bytes.
     * @return Nonzero on success, zero for a null range.
     */
    u32 func_001138B0(ResidentHeap* heap, void* address, u32 size);

    /**
     * @brief Allocate from the top of a heap's free blocks, trying its child heaps first.
     * @param heap Heap.
     * @param size Requested payload size in bytes.
     * @return Allocation, or null when no block is available.
     */
    void* func_001135B0(ResidentHeap* heap, s32 size);

    /**
     * @brief Measure a heap and its child heaps.
     * @param heap Heap to measure.
     * @param free_bytes Receives the total size of the free blocks.
     * @param used_bytes Receives the total size of the allocated blocks.
     * @return Largest allocation that would fit in one free block.
     */
    s32 func_00113190(ResidentHeap* heap, s32* free_bytes, s32* used_bytes);
}
#endif

#ifdef __cplusplus
extern "C"
{
    /**
     * @brief Send voice command 4 to a started sound.
     * @param sound Sound system.
     * @param identifier Identifier resident_sound_play returned.
     * @param first First command argument.
     * @param second Second command argument.
     */
    void func_00110340(ResidentSound* sound, s32 identifier, s32 first, s32 second);

    /**
     * @brief Send voice command 5 to a started sound.
     * @param sound Sound system.
     * @param identifier Identifier resident_sound_play returned.
     * @param first First command argument.
     * @param second Second command argument.
     */
    void func_001103E0(ResidentSound* sound, s32 identifier, s32 first, s32 second);

    /**
     * @brief Send voice command 1 to a started sound that has no target.
     * @param sound Sound system.
     * @param identifier Identifier resident_sound_play returned.
     * @param first First command argument.
     * @param second Second command argument.
     */
    void func_00110480(ResidentSound* sound, s32 identifier, s32 first, s32 second);

    /**
     * @brief Send voice command 0 to a started sound, optionally recording its new volume.
     * @param sound Sound system.
     * @param identifier Identifier resident_sound_play returned.
     * @param volume Volume, sent as the first command argument.
     * @param second Second command argument.
     * @param keep_volume Zero to also store volume in the slot.
     */
    void func_00110520(ResidentSound* sound, s32 identifier, s32 volume, s32 second, s32 keep_volume);

    /**
     * @brief Report whether a sound still holds its slot.
     * @param sound Sound system.
     * @param identifier Identifier resident_sound_play returned.
     * @return One while the sound's slot is in use, otherwise zero.
     */
    s32 resident_sound_is_active(ResidentSound* sound, s32 identifier);

    /**
     * @brief Free one voice read ahead of time, cancelling its read if it is still in progress.
     * @param sound Sound system.
     * @param voice Index of the voice in the voice table.
     */
    void func_00110CE0(ResidentSound* sound, s32 voice);

    /**
     * @brief Read a voice into one of the read-ahead buffers.
     * @param sound Sound system.
     * @param voice Index of the voice in the voice table.
     * @return Zero once the read is queued, or -1 when the voice can't be read now.
     */
    s32 func_00110D80(ResidentSound* sound, s32 voice);

    /**
     * @brief Play a voice from an object in a free slot, reading it unless it was read ahead of time.
     * @param sound Sound system.
     * @param voice Index of the voice in the voice table.
     * @param emitter Object the voice comes from.
     * @param value Stored in the slot; its use is unknown.
     * @param volume Volume, 0x7F for full; stored and packed into the upper byte.
     * @param low Value packed into the lower 16 bits.
     * @return Slot identifier, one when effects are disabled, or -1 when the voice can't be played.
     */
    s32 func_00110FB0(ResidentSound* sound, s32 voice, ResidentSoundEmitter* emitter, s32 value, s32 volume, s32 low);

    /**
     * @brief Play a voice in a free slot, reading it unless it was read ahead of time.
     * @param sound Sound system.
     * @param voice Index of the voice in the voice table.
     * @param value Stored in the slot; its use is unknown.
     * @param volume Volume, 0x7F for full; stored and packed into the upper byte.
     * @param pan Pan, 0x40 for centre; packed into the next byte.
     * @param low Value packed into the lower 16 bits.
     * @return Slot identifier, one when effects are disabled, or -1 when the voice can't be played.
     */
    s32 func_00111420(ResidentSound* sound, s32 voice, s32 value, s32 volume, s32 pan, s32 low);

    /**
     * @brief Play sound data already in memory from an object, in a free slot.
     * @param sound Sound system.
     * @param buffer Sound data.
     * @param emitter Object the sound comes from.
     * @param value Stored in the slot; its use is unknown.
     * @param volume Volume, 0x7F for full; stored and packed into the upper byte.
     * @param low Value packed into the lower 16 bits.
     * @param owns_buffer Nonzero to delete buffer once the sound stops, or now when effects are disabled.
     * @return Slot identifier, one when effects are disabled, or -1 when no slot is free.
     */
    s32 func_00111860(ResidentSound* sound, u8* buffer, ResidentSoundEmitter* emitter, s32 value, s32 volume, s32 low,
                      s32 owns_buffer);

    /**
     * @brief Play sound data already in memory, in a free slot.
     * @param sound Sound system.
     * @param buffer Sound data.
     * @param value Stored in the slot; its use is unknown.
     * @param volume Volume, 0x7F for full; packed into the upper byte.
     * @param pan Pan, 0x40 for centre; packed into the next byte.
     * @param low Value packed into the lower 16 bits.
     * @param owns_buffer Nonzero to delete buffer once the sound stops, or now when effects are disabled.
     * @return Slot identifier, one when effects are disabled, or -1 when no slot is free.
     */
    s32 func_00111A90(ResidentSound* sound, u8* buffer, s32 value, s32 volume, s32 pan, s32 low, s32 owns_buffer);

    /**
     * @brief Play a voice resource from an object in a free slot, reading the resource for it.
     * @param sound Sound system.
     * @param resource Resource key of the voice.
     * @param emitter Object the voice comes from.
     * @param value Stored in the slot; its use is unknown.
     * @param volume Volume, 0x7F for full; stored and packed into the upper byte.
     * @param low Value packed into the lower 16 bits.
     * @return Slot identifier, one when effects are disabled, or -1 when the voice can't be played.
     */
    s32 resident_sound_play_voice(ResidentSound* sound, s32 resource, ResidentSoundEmitter* emitter, s32 value, s32 volume, s32 low);

    /**
     * @brief Play a voice resource in a free slot, reading the resource for it.
     * @param sound Sound system.
     * @param resource Resource key of the voice.
     * @param value Stored in the slot; its use is unknown.
     * @param volume Volume, 0x7F for full; stored and packed into the upper byte.
     * @param pan Pan, 0x40 for centre; packed into the next byte.
     * @param low Value packed into the lower 16 bits.
     * @return Slot identifier, one when effects are disabled, or -1 when the voice can't be played.
     */
    s32 func_00111EF0(ResidentSound* sound, s32 resource, s32 value, s32 volume, s32 pan, s32 low);

    /**
     * @brief Play a sound effect from an object in a free slot.
     * @param sound Sound system.
     * @param number Sound number; its low 16 bits are stored.
     * @param emitter Object the sound comes from.
     * @param selector Request selector.
     * @param value Value forwarded to request dispatch.
     * @param volume Volume, 0x7F for full; stored and packed into the upper byte.
     * @param low Value packed into the lower 16 bits.
     * @return Slot identifier, zero on dispatch failure, one when effects are disabled, or -1 without an emitter or a free
     *         slot.
     */
    s32 func_00112160(ResidentSound* sound, s32 number, ResidentSoundEmitter* emitter, s32 selector, s32 value, s32 volume,
                      s32 low);

    /**
     * @brief Queue streamed music from a music file already in memory.
     * @param sound Sound system.
     * @param music Music file, non-null.
     * @param stop_others Nonzero to stop the queued music first.
     * @param value Stored for the music; its use is unknown.
     * @return One when the music was queued or music is disabled, otherwise zero.
     */
    s32 resident_sound_load_bank(ResidentSound* sound, const void* music, s32 stop_others, s32 value);

    /**
     * @brief Queue music.
     * @param sound Sound system.
     * @param music Music number, from one.
     * @param stop_others Nonzero to stop the queued music first.
     * @param value Stored for the music; its use is unknown.
     * @param second Stored for streamed music; nonzero also sets a flag.
     * @return One when the music was queued or music is disabled, otherwise zero.
     */
    s32 resident_sound_play_music(ResidentSound* sound, s32 music, s32 stop_others, s32 value, s32 second);

    /**
     * @brief Stop music.
     * @param sound Sound system.
     * @param mode Stop mode.
     * @param key Music to stop, or -1 for all of it.
     * @return One when music was stopped or music is disabled, otherwise zero.
     */
    s32 resident_sound_stop_music(ResidentSound* sound, s32 mode, s32 key);

    /**
     * @brief Delete a heap's child heaps.
     * @param heap Heap.
     */
    void func_00113A10(ResidentHeap* heap);

    /**
     * @brief Add a child heap over a memory range.
     * @param heap Parent heap.
     * @param address Start of the child's range.
     * @param size Size of the child's range in bytes.
     * @return Nonzero when the child was added, zero when the parent is full or the child can't be made.
     */
    u32 func_00113AB0(ResidentHeap* heap, void* address, u32 size);

    /**
     * @brief Add a child heap with memory of its own.
     * @param heap Parent heap.
     * @param size Usable size of the child in bytes.
     * @return Nonzero when the child was added, zero when the parent is full or the child can't be made.
     */
    u32 func_00113C40(ResidentHeap* heap, u32 size);

    /**
     * @brief Stop handing out time slices, returning the running thread to the normal priority.
     * @param scheduler Scheduler.
     */
    void func_00114720(ResidentThreadScheduler* scheduler);

    /**
     * @brief End the running time slice and give the next thread its slice, from interrupt context.
     * @param scheduler Scheduler.
     */
    void func_00114790(ResidentThreadScheduler* scheduler);

    /**
     * @brief Entry point of every resident thread: run the thread's body, then delete the thread.
     * @param argument The thread.
     */
    void func_00114EE0(void* argument);

    /**
     * @brief Create the kernel thread with a new stack; it runs the thread's body once started.
     * @param thread Thread.
     * @param priority Thread priority.
     * @param stack_size Stack size in bytes.
     * @return Nonzero when the thread was created, zero when it already exists or creation failed.
     */
    s32 func_00115000(ResidentThread* thread, s32 priority, s32 stack_size);

    /**
     * @brief Report whether a resource exists in the decrypted resource table.
     * @param archive Resource archive.
     * @param index Resource index, counted from the sixth entry.
     * @return One when the resource has a size, zero when it is empty, or two when the table isn't decrypted.
     */
    s32 func_00115270(const ResidentArchive* archive, s32 index);
}
#endif


#ifdef __cplusplus
extern "C" {

/**
 * @brief Reset the streaming state and send a stream request (command -5) to the IOP.
 * @param stream Streaming thread.
 * @param arg1 Request argument.
 * @param callback Called when the request completes.
 * @param argument Passed to callback.
 * @param entry Resource entry to stream; its words at 0x10 and 0x14 are kept.
 * @param value Kept at unk90.
 * @param arg6 Request argument.
 * @return The request result, or zero while a request is already running.
 */
s32 func_0010A0E0(ResidentStreamThread* stream, s32 arg1, void* callback, void* argument, u32* entry, s32 value,
                  s32 arg6);

/**
 * @brief Reset the streaming state and send a stream request (command -4) to the IOP.
 * @param stream Streaming thread.
 * @param arg1 Request argument.
 * @param callback Called when the request completes.
 * @param argument Passed to callback.
 * @param entry Resource entry to stream; its words at 0x10 and 0x14 are kept.
 * @param arg6 Request argument.
 * @return The request result, or zero while a request is already running.
 */
s32 func_0010A200(ResidentStreamThread* stream, s32 arg1, void* callback, void* argument, u32* entry, s32 arg6);

/**
 * @brief Reset the block state and send a stream request (command -3) to the IOP; the ring is left alone.
 * @param stream Streaming thread.
 * @param arg1 Request argument.
 * @param callback Called when the request completes.
 * @param argument Passed to callback.
 * @param entry Resource entry to stream; its words at 0x10 and 0x14 are kept.
 * @param arg6 Request argument.
 * @return The request result, or zero while a request is already running.
 */
s32 func_0010A310(ResidentStreamThread* stream, s32 arg1, void* callback, void* argument, u32* entry, s32 arg6);

/**
 * @brief Send command -2 to the IOP.
 * @param stream Streaming thread.
 * @param arg1 Request argument.
 * @param callback Called when the request completes.
 * @param argument Passed to callback.
 * @param arg6 Request argument.
 * @return The request result, or zero while unkB0 is set.
 */
s32 func_0010A400(ResidentStreamThread* stream, s32 arg1, void* callback, void* argument, s32 arg6);

/**
 * @brief Reset the block state and send command -1 to the IOP at full volume, centred.
 * @param stream Streaming thread.
 * @param arg1 Request argument.
 * @param callback Called when the request completes.
 * @param argument Passed to callback.
 * @param value Kept at unk90.
 * @param arg6 Request argument.
 * @param arg10 Request argument.
 * @return The request result, or zero while a request is already running.
 */
s32 func_0010A450(ResidentStreamThread* stream, s32 arg1, void* callback, void* argument, s32 value, s32 arg6,
                  s32 arg10);

/**
 * @brief Append bytes to the ring, first moving unread data back to the start of the ring when the end is too close.
 * @param stream Streaming thread.
 * @param data Bytes to append.
 * @param size Number of bytes in data.
 * @return Number of bytes appended.
 */
s32 func_0010A530(ResidentStreamThread* stream, const void* data, s32 size);

/**
 * @brief Copy words into the ring half being written, marking the half full and moving to the other half when it
 * fills.
 * @param stream Streaming thread.
 * @param words Words to copy.
 * @param size Number of bytes in words.
 * @return Number of bytes copied, or zero when the ring can't take data.
 */
s32 func_0010A650(ResidentStreamThread* stream, const u32* words, s32 size);

/**
 * @brief Body of the streaming thread: on every wakeup run both streaming passes, then wake the waiting thread, if any.
 * @param stream Streaming thread.
 */
void func_0010B4C0(ResidentStreamThread* stream);

/**
 * @brief Handle a notification from the IOP side of the stream.
 * @param stream Streaming thread.
 * @param event 0 when a receive block arrived, 2 to set unk74, 4 to send the next chunk.
 */
void func_0010B510(ResidentStreamThread* stream, s32 event);

/**
 * @brief Write a number as decimal text.
 * @param buffer Receives the text and its terminating zero.
 * @param value Number to write; negative numbers get a leading '-'.
 * @param width Number of digits to write, padded on the left with pad and losing the leading digits that don't fit;
 * zero or less writes every digit.
 * @param pad Padding character.
 * @return buffer.
 */
char* func_0010D710(char* buffer, s32 value, s32 width, char pad);

/**
 * @brief Ask the sound system to switch unk354 to a new value.
 * @param sound Sound system.
 * @param value New value.
 * @return Zero while the sound system is busy, otherwise one.
 */
s32 func_0010DAA0(ResidentSound* sound, s32 value);

/**
 * @brief Scale the sound volume and send it to the stream.
 * @param sound Sound system.
 * @param scale Scale, 0x7FFF for the full volume.
 */
void resident_sound_set_volume_scale(ResidentSound* sound, s32 scale);

/**
 * @brief Send stream command func_00107420 when unk30 is set and unk38 isn't minus one, then copy unk40 to unk33C.
 * @param sound Sound system.
 */
void func_0010DE90(ResidentSound* sound);

/**
 * @brief Pop the stream result stack and resend the scaled volume.
 * @param sound Sound system.
 */
void func_0010DEF0(ResidentSound* sound);

/**
 * @brief Send stream command func_00107B60 in mode 2.
 * @param sound Sound system.
 */
void func_0010DF70(ResidentSound* sound);

/**
 * @brief Count the entries of the loaded sound bank.
 * @param sound Sound system.
 * @return Number of entries, or zero while no bank is loaded or it is still loading.
 */
s32 func_0010DFF0(ResidentSound* sound);

/**
 * @brief Read an entry of the loaded sound bank.
 * @param sound Sound system.
 * @param index Entry index.
 * @param second Receives the entry's second halfword, or zero.
 * @return The entry's first halfword, or minus one when there is no such entry.
 */
s32 func_0010E060(ResidentSound* sound, s32 index, u32* second);

/**
 * @brief Load another sound bank, first releasing everything allocated from the current one.
 * @param sound Sound system.
 * @param key Resource key of the bank.
 */
void func_0010E130(ResidentSound* sound, s32 key);

/**
 * @brief Get the voice data of a request slot, asking the stream for it the first time.
 * @param sound Sound system.
 * @param identifier Slot identifier.
 * @return The voice data, or zero when there is none.
 */
u32 func_0010E200(ResidentSound* sound, s32 identifier);


/**
 * @brief Clear the target of every active request slot aimed at an object.
 * @param sound Sound system.
 * @param target Object to forget.
 */
void func_0010ED20(ResidentSound* sound, ResidentSoundEmitter* target);

/**
 * @brief Request callback: push the stream's answer onto the sound system's stack.
 * @param reply Reply from the IOP.
 */
void func_0010EF80(void* reply);

/**
 * @brief Request callback for a played sound: keep the IOP's answer in the slot and free the slot unless it repeats.
 * @param reply Reply from the IOP.
 * @param slot Request slot.
 */
void func_0010EE60(void* reply, ResidentRequestSlot* slot);

/**
 * @brief Request callback: free each listed request slot whose reply word is zero, then clear unk348.
 * @param reply Reply from the IOP, one word per entry of sound->unk2F8.
 * @param sound Sound system.
 */
void func_0010ED90(const u32* reply, ResidentSound* sound);

}
#endif

#endif
