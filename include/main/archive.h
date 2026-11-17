#ifndef SO3_MAIN_ARCHIVE_H
#define SO3_MAIN_ARCHIVE_H

#include "types.h"
#include "sdk/main/libkernl_00121940.h"
#include "ee.h"
#include "main/semaphore.h"
#include "main/resource_queue.h"
#include "main/thread.h"

#ifndef __cplusplus
/* C units see the resident C++ classes as opaque types. */
typedef struct ResidentArchiveWorker ResidentArchiveWorker;
#endif

struct ResidentArchive;
#define RESIDENT_RESOURCE_COUNT 0x1800

/** Clock bytes the archive's clock query fills. */
typedef struct ResidentClock
{
    u8 status;
    u8 second;
    u8 minute;
    u8 hour;
    u8 pad;
    u8 day;
    u8 month;
    u8 year;
} ResidentClock;

#define RESIDENT_ARCHIVE_TABLE_TAG 0x34829314

typedef struct ResidentArchive ResidentArchive;

#ifdef __cplusplus

/** The 0x200-byte "PS2ICON3D" header the worker writes in front of the four system files. */
struct ResidentHddIconHeader
{
    char magic[0x10];
    struct
    {
        u32 offset;
        u32 size;
    } files[4];
    u8 unk30[0x1D0];
};

/** Listener the hard disk worker registers; a notification wakes the thread it is given. Vtable D_0014FBE0. */
class ResidentArchiveWorkerListener : public ResidentListener
{
    public:
        /**
         * @brief Wake a thread.
         * @param data Thread to wake.
         */
        virtual void notify(void* data);
};

/** Thread that runs the hard disk worker's commands; vtable D_0014FBC0. */
class ResidentArchiveWorker : public ResidentThread
{
    public:
        u8 unk10;
        u8 unk11[3];
        s32 unk14;
        u32 free_space;
        u8 unit_ready;
        u8 unk1d[3];
        s32 command;

        // TODO: volatile is my guess; run reads it again for its second test after the copy loop, and only this does that
        volatile s32 command_result;
        s32 unk28;
        s32 copy_remaining;
        struct ResidentArchive* archive;
        ResidentSemaphore command_semaphore;
        ResidentSemaphore unk3c;
        s32 argument;
        u8* copy_buffer;
        u8 cancel_requested;
        u8 unk4d;
        u8 unk4e;
        u8 copy_paused;
        s32 unk50;
        u8 unk54;
        u8 unit_state;
        u8 unk56[2];
        ResidentArchiveWorkerListener listener;
        struct ResidentHddIconHeader* icon_header;
        u8* system_files[4];
        u8* navigator_files[3];
        s32 navigator_file_sizes[3];

        /** @brief Create the worker's thread and semaphores, idle and with no files. */
        ResidentArchiveWorker();

        virtual ~ResidentArchiveWorker();

        virtual void run();
};

/** The disc thread's thread at + 0xAC, which reads the disc drive's status and clock; vtable D_0014FC40. */
class ResidentDiscStatusThread : public ResidentThread
{
    public:
        class ResidentDiscThread* owner;
        s32 unk14;
        u32 unk18;
        u8 unk1c;
        u8 unk1d;
        u8 unk1e[2];
        u32 unk20;
        ResidentClock clock;

        /** @brief Create the kernel thread with the clock at 2003-02-27 12:00:00. */
        ResidentDiscStatusThread()
        {
            resident_thread_create(this, 0x25, 0x4000);
            unk14 = 0x80;
            unk18 = 0;
            unk1d = 0;
            unk1c = 0;
            clock.status = 0x80;
            clock.second = 0;
            clock.minute = 0;
            clock.hour = 0x12;
            clock.day = 0x27;
            clock.month = 2;
            clock.year = 3;
        }

        virtual ~ResidentDiscStatusThread();

        virtual void run();
};

/** The archive's thread at archive + 0xD8, which the disc power-off callback is given; vtable D_0014FBF0. */
class ResidentPowerOffThread : public ResidentThread
{
    public:
        ResidentArchiveWorker* worker;

        /** @brief Create the kernel thread, with no worker yet. */
        ResidentPowerOffThread()
        {
            resident_thread_create(this, 0x24, 0x4000);
            worker = 0;
        }

        virtual ~ResidentPowerOffThread();

        virtual void run();
};

/** What the disc thread tells about each block it reads while streaming into a ring. */
class ResidentReadListener
{
    public:
        /**
         * @brief Handle one block that was just read.
         * @param address Where the block was read to.
         * @param size Block size in bytes.
         * @param ring_start Start of the ring.
         * @param ring_size Size of the ring in bytes.
         */
        virtual void handle(u32 address, s32 size, u32 ring_start, s32 ring_size);
};

/** The archive's disc thread, at the start of the archive: it reads the disc for the archive; vtable D_0014FC10. */
class ResidentDiscThread : public ResidentThread
{
    public:
        ResidentSemaphore unk10;
        ResidentSemaphore semaphore;
        ResidentSemaphore unk20;
        ResidentSemaphore unk28;
        ResidentSemaphore unk30;
        ResidentSemaphore timeout_semaphore;
        ResidentSemaphore unk40;
        ResidentSemaphore unk48;
        s32 unk50;
        s32 unk54;
        s32 unk58;
        u8 unk5c;
        u8 unk5d;
        u8 unk5e;
        u8 unk5f;
        u8 unk60;
        u8 unk61;
        u8 unk62;
        u8 unk63;
        void* unk64;
        u8 unk68;
        u8 unk69;
        u8 unk6a;
        u8 unk6b;
        u8 unk6c;
        u8 timed_out;
        u8 unk6e[2];
        s32 unk70;
        s32 timeout_ticks;
        volatile s32 timeout_alarm;
        s32 unk7c;
        // TODO: Other threads set the size left to read; only a volatile field makes the read loop load it again.
        volatile s32 unk80;

        u32 unk84;
        s32 unk88;
        u32 unk8c;
        s32 unk90;
        s32 unk94;
        s32 unk98;
        struct ResidentListener* listener;
        void* listener_context;
        struct ResidentArchive* owner;
        u8 unka8[4];
        ResidentDiscStatusThread unkAC;

        /** @brief Create the semaphores and start the status thread. */
        ResidentDiscThread();

        virtual ~ResidentDiscThread();

        /** @brief Thread body: wait for a read request, do the read, and notify the listener. */
        virtual void run();
};

/**
 * The game's resource archive: the packed entry of every resource, plus the worker that installs the archive to the
 * PlayStation BB Unit (the hard disk) and reports its progress.
 */
struct ResidentArchive
{
    ResidentDiscThread disc_thread;
    ResidentPowerOffThread unkD8;
    ResidentArchiveWorker worker;
    s32 main_thread_id;
    u32 table_tag;
    u32 resource_positions[RESIDENT_RESOURCE_COUNT];
    u32 resource_entries[RESIDENT_RESOURCE_COUNT];
    u32 install_flags[RESIDENT_RESOURCE_COUNT];
    u8 unk1217c[4];
    u8 unk12180;
    u8 unk12181;
    u8 unk12182;
    volatile u8 read_busy;
    u8 unk12184;
    u8 unk12185;
    u8 unk12186;
    u8 unk12187;
    u8 unk12188[0xC];
    u32 unk12194;
    s32 unk12198;
    u8 unk1219c[4];
    u32 unk121a0;
    u8 unk121a4[4];
    s32 unk121a8;
    void* cd_callback_stack;
    u8 unk121b0[0x18];

    /** @brief Construct the archive's threads and start them. */
    ResidentArchive();

    virtual ~ResidentArchive();
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Select a resource for the next read, adding size to the counters at unk54 and unk58 when unk12181 is set.
 * @param archive Resource archive.
 * @param size Amount added to both counters.
 * @param key Resource key.
 * @return Nonzero when the resource was selected, or zero while a read is running.
 */
u8 resident_archive_select_counted(ResidentArchive* archive, s32 size, s32 key);

/**
 * @brief Start reading the resource resident_archive_select_resource selected.
 * @param archive Resource archive.
 * @param buffer Destination.
 * @param size Bytes to read, or zero for the whole resource.
 * @return Nonzero when the read started.
 */
s32 resident_archive_start_read(ResidentArchive* archive, void* buffer, s32 size);

/**
 * @brief Start reading the selected resource without checking the result.
 * @param archive Resource archive.
 * @param buffer Destination.
 * @param size Bytes to read, or zero for the whole resource.
 */
void resident_archive_start_read_unchecked(ResidentArchive* archive, void* buffer, s32 size);

/**
 * @brief Read the clock.
 * @param archive Resource archive.
 * @param clock Receives the clock bytes.
 * @return Nonzero on success.
 */
s32 resident_archive_get_clock(ResidentArchive* archive, ResidentClock* clock);

/**
 * @brief Archive setup that main runs right after rebooting the IOP.
 * @param archive Resource archive.
 */
void resident_archive_start_disc(ResidentArchive* archive);

/**
 * @brief Read and decrypt the archive's table of contents; main runs it after storing its arguments.
 * @param archive Resource archive.
 * @return One once the table is loaded, or zero while another read is running.
 */
s32 resident_archive_read_table(ResidentArchive* archive);

/**
 * @brief Select the resource the next read loads; main passes 1 for the IOP modules and 2 for the programs.
 * @param archive Resource archive.
 * @param key Resource key.
 * @return One when the resource was selected, or zero while a read is running.
 */
s32 resident_archive_select_resource(ResidentArchive* archive, s32 key);

/**
 * @brief Start streaming the selected resource through a ring buffer.
 * @param archive Resource archive.
 * @param buffer Ring buffer.
 * @param ring_size Ring size in bytes; a multiple of 64 KiB.
 * @param size Bytes to read, or zero for the whole resource.
 * @return One once the read is started, or zero while another read is running, the ring size is wrong or nothing is
 * selected.
 */
s32 resident_archive_start_ring_read(ResidentArchive* archive, void* buffer, u32 ring_size, s32 size);

/**
 * @brief Stop the archive's streaming read.
 * @param archive Resource archive.
 */
void resident_archive_stop_ring_read(ResidentArchive* archive);

/**
 * @brief Read the two positions at unk88 and unk8C under the archive's semaphore.
 * @param archive Resource archive.
 * @param position Receives unk8C plus one, less unk121A0 once it reaches unk12194 plus unk121A0.
 * @return unk88.
 */
s32 resident_archive_get_ring_positions(ResidentArchive* archive, u32* position);

/**
 * @brief Abort the archive's current read.
 * @param archive Resource archive.
 */
void resident_archive_release_read(ResidentArchive* archive);

/**
 * @brief Set unk6A once, while unk5E is set and a read is in progress.
 * @param archive Resource archive.
 */
void resident_archive_hold_read(ResidentArchive* archive);

#ifdef __cplusplus
/**
 * @brief Report whether the archive is idle: unk5C, unk5D and unk6B all clear, read under its semaphore.
 * @param archive Resource archive.
 * @return True when all three are clear.
 */
bool resident_archive_is_idle(ResidentArchive* archive);
#endif

/**
 * @brief Install the disc power-off callback and start the hard disk worker; main runs it once the IOP modules are
 * loaded.
 * @param archive Resource archive.
 */
void resident_archive_start_hard_disk(ResidentArchive* archive);


/**
 * @brief Read the byte size associated with a key in the resident descriptor table.
 * @param object Resident descriptor table owner.
 * @param key Descriptor key.
 * @return Resource size in bytes.
 */
u32 resident_get_resource_size(const ResidentArchive* archive, s32 key);

/**
 * @brief Get the position of a resource in the archive.
 * @param archive Resource archive.
 * @param key Resource key.
 * @return Position in 2048-byte blocks.
 */
u32 resident_archive_get_resource_position(const ResidentArchive* archive, s32 key);

/**
 * @brief Read a resource and wait for the read to finish, retrying until it starts.
 * @param archive Resource archive.
 * @param buffer Destination.
 * @param key Resource key.
 * @param size Bytes to read, or zero for the whole resource.
 * @return One.
 */
s32 resident_archive_read_resource(ResidentArchive* archive, void* buffer, s32 key, s32 size);

#ifdef __cplusplus
/**
 * @brief Report whether a hard disk unit error is pending.
 * @param archive Resource archive.
 * @return Whether an error is pending.
 */
bool resident_archive_has_unit_error(const ResidentArchive* archive);
#endif

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

#ifdef __cplusplus
/**
 * @brief Start a query of the unit and any existing install when the unit is usable (worker command 6), or end it
 * (command 7).
 * @param archive Resource archive.
 * @param first Nonzero to start the query, zero to end it.
 * @param second Nonzero to skip the unk139 check when starting.
 * @return True when a query is running or already done (or ended); false while a read is running, the unit isn't
 * usable or the worker couldn't start the command.
 */
bool resident_archive_query_unit(ResidentArchive* archive, s32 first, s32 second);
#endif

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
 * @brief Do nothing.
 * @param object Unused.
 */
void resident_archive_do_nothing(void* object);

/** Return bit 0 of the word at receiver offset 0xCC. */
s32 resident_archive_get_flag_cc(const void* object);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {

    /**
     * @brief Report whether a resource exists in the decrypted resource table.
     * @param archive Resource archive.
     * @param index Resource index, counted from the sixth entry.
     * @return One when the resource has a size, zero when it is empty, or two when the table isn't decrypted.
     */
    s32 resident_archive_has_resource(const ResidentArchive* archive, s32 index);
}
#endif

#endif
