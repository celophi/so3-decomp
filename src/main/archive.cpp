#include "include_asm.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "sdk/main/libc_guess_00137290.h"
#include "sdk/main/libc_guess_0013C948.h"
#include "sdk/main/libc_0013C6D0.h"
#include "sdk/main/libcdvd_00130000.h"
#include "main/debug.h"
#include "main/system.h"
#include "main/utility.h"

// TODO: The archive checks only match with the logical rebuild off; with it on, MWCC turns their || chains into
// sltu compares the game doesn't have. Turning it off changes nothing else in this file, so I think the whole file
// was built that way.
#pragma opt_rebuildlogicals off
#define SCECdFuncRead 1
#define PFS_DEVCTL_CLOSE_ALL 0x5003
#define DEV9_DEVCTL_POWER_OFF 0x4402
#define HDD_DEVCTL_TOTAL_SECTORS 0x4802
#define HDD_DEVCTL_STATUS 0x4807
#define HDD_DEVCTL_IDLE_NOW 0x480B
#define HDD_IOCTL_ADD_SUB_PARTITION 0x6801
#define RESIDENT_INSTALL_HEADER_SIZE 0x2000
#define RESIDENT_INSTALL_ALIGNMENT 0x40000

#define RESIDENT_ARCHIVE_TOC_POSITION 0x400

/** Words in the table of contents: a position, size and install flag per resource. */
#define RESIDENT_ARCHIVE_TOC_WORDS (RESIDENT_RESOURCE_COUNT * 3)

#define RESIDENT_ARCHIVE_TOC_KEY 0x13578642

extern "C" {

void resident_archive_worker_set_system_files(ResidentArchiveWorker* worker, ResidentHddIconHeader* header, u8* first, s32 first_size, u8* second,
                   s32 second_size, u8* third, s32 third_size, u8* fourth, s32 fourth_size);

s32 sceCdDiskReady(s32 mode);

void* sceCdPOffCallback(void (*callback)(void*), void* argument);

s32 sceDevctl(const char* name, s32 command, void* argument, u32 argument_size, void* buffer, u32 buffer_size);

s32 sceCdPowerOff(s32* result);

s32 sceCdStatus(void);

s32 sceCdReadClock(ResidentClock* clock);

u32 sceCdGetReadPos(void);

/** "pfs:", the hard disk file system device. */
extern const char g_pfs_device[];

/** File status as the hard disk's directory reads return it; only the fields the worker uses are named. */
struct SceIoStat
{
    u32 mode;
    u32 attributes;
    u32 size;
    u8 unk0c[0x34];
};

/** Directory entry from sceDread. */
struct SceIoDirent
{
    SceIoStat stat;
    char name[256];
    void* unk140;
};

/** Eight characters the worker passes when it adds a sub-partition. */
struct HddZoneName
{
    char text[8];
};

s32 sceOpen(const char* name, s32 flags, ...);

s32 sceClose(s32 fd);

s32 sceLseek(s32 fd, s32 offset, s32 whence);

s32 sceWrite(s32 fd, const void* buffer, s32 size);

s32 sceIoctl2(s32 fd, s32 request, void* argument, u32 argument_size, void* buffer, u32 buffer_size);

s32 sceRemove(const char* name);

s32 sceMkdir(const char* name, s32 mode);

s32 sceFormat(const char* device, const char* block_device, void* argument, s32 argument_size);

s32 sceDopen(const char* name);

s32 sceDread(s32 fd, SceIoDirent* entry);

s32 sceDclose(s32 fd);

s32 sceMount(const char* device, const char* block_device, s32 flags, void* argument, s32 argument_size);

s32 sceUmount(const char* device);

u32 strlen(const char* string);

/** "hdd0:", the hard disk. */
extern const char g_hdd_device[];

/** "hdd0:PP.SLUS-20488", the start of the game's partition name. */
extern const char g_hdd_partition_name[];

/** ",128M,PFS", the size and file system given when the partition is created or removed. */
extern const char g_hdd_partition_options[];

/** "pfs0:", the mounted partition. */
extern const char g_pfs_mount[];

/** "pfs0:/res" */
extern const char g_pfs_resource_directory[];

/** "pfs0:sotet.bin", the installed resource file. */
extern const char g_pfs_resource_file[];

/** Names stored with every character xored with 0xF3: the partition name's ending and the three navigator files. */
extern const char g_hdd_partition_suffix[];
extern const char g_navigator_file_name_1[];
extern const char g_navigator_file_name_2[];
extern const char g_navigator_file_name_3[];

extern HddZoneName g_hdd_zone_name;

/** "dev9x:", the expansion bay device. */
extern const char g_dev9_device[];

void resident_disc_timeout_alarm(s32 alarm_id, u16 time, void* common);

s32 ReleaseAlarm(s32 alarm_id);

/** Nonzero to read data with spindle control 0 instead of 1. */
extern u8 g_disc_spindle_override;

s32 sceRead(s32 fd, void* buffer, s32 size);

s64 sceLseek64(s32 fd, s64 offset, s32 whence);

/** "PS2ICON3D", the magic of the hard disk icon header. */
extern const char g_hdd_icon_magic[];

/** The archive's disc thread. */
extern ResidentDiscThread* g_disc_thread;

/** "Storage Status", the name the read flag is registered under. */
extern const char g_storage_status_name[];

bool resident_archive_worker_start_command(ResidentArchiveWorker* worker, s32 command, s32 argument);


/** @brief Destroy the worker and its semaphores. */
inline ResidentArchiveWorker::~ResidentArchiveWorker()
{
}

/**
 * @brief Report whether a resource exists in the decrypted resource table.
 * @param archive Resource archive.
 * @param index Resource index, counted from the sixth entry.
 * @return One when the resource has a size, zero when it is empty, or two when the table isn't decrypted.
 */
s32 resident_archive_has_resource(const ResidentArchive* archive, s32 index)
{
    if (archive->table_tag != RESIDENT_ARCHIVE_TABLE_TAG)
    {
        return 2;
    }

    if ((archive->resource_entries[index + 5] & 0x00FFFFFF) << 11)
    {
        return 1;
    }

    return 0;
}

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
                                          s32 third_size)
{
    archive->worker.navigator_files[0] = first;
    archive->worker.navigator_file_sizes[0] = first_size;
    archive->worker.navigator_files[1] = second;
    archive->worker.navigator_file_sizes[1] = second_size;
    archive->worker.navigator_files[2] = third;
    archive->worker.navigator_file_sizes[2] = third_size;
}

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
                                       s32 third_size, u8* fourth, s32 fourth_size)
{
    resident_archive_worker_set_system_files(&archive->worker, (ResidentHddIconHeader*)header, first, first_size, second, second_size, third,
                  third_size, fourth, fourth_size);
}

/**
 * @brief Give the hard disk worker the system files and build their icon header: the magic, then each file's offset
 * (from 0x200, each rounded up to 0x200 bytes) and size.
 * @param worker Hard disk worker.
 * @param header Header to fill, 0x200 bytes.
 * @param first First file.
 * @param first_size Size of first.
 * @param second Second file.
 * @param second_size Size of second.
 * @param third Third file.
 * @param third_size Size of third.
 * @param fourth Fourth file.
 * @param fourth_size Size of fourth.
 */
void resident_archive_worker_set_system_files(ResidentArchiveWorker* worker, ResidentHddIconHeader* header, u8* first, s32 first_size, u8* second,
                   s32 second_size, u8* third, s32 third_size, u8* fourth, s32 fourth_size)
{
    worker->icon_header = header;
    worker->system_files[0] = first;
    worker->system_files[1] = second;
    worker->system_files[2] = third;
    worker->system_files[3] = fourth;
    memset_guess(worker->icon_header, 0, sizeof(ResidentHddIconHeader));
    strcpy_guess(worker->icon_header->magic, g_hdd_icon_magic);
    worker->icon_header->files[0].offset = sizeof(ResidentHddIconHeader);
    worker->icon_header->files[0].size = first_size;
    worker->icon_header->files[1].offset =
        worker->icon_header->files[0].offset + ((worker->icon_header->files[0].size + 0x1FF) & ~0x1FF);
    worker->icon_header->files[1].size = second_size;
    worker->icon_header->files[2].offset =
        worker->icon_header->files[1].offset + ((worker->icon_header->files[1].size + 0x1FF) & ~0x1FF);
    worker->icon_header->files[2].size = third_size;
    worker->icon_header->files[3].offset =
        worker->icon_header->files[2].offset + ((worker->icon_header->files[2].size + 0x1FF) & ~0x1FF);
    worker->icon_header->files[3].size = fourth_size;
}

/**
 * @brief Clear the pending hard disk unit error.
 * @param archive Resource archive.
 */
void resident_archive_clear_unit_error(ResidentArchive* archive)
{
    archive->worker.unk54 = 0;
    archive->disc_thread.unk6c = 0;
}

/**
 * @brief Report whether a hard disk unit error is pending.
 * @param archive Resource archive.
 * @return Whether an error is pending.
 */
static inline bool archive_unit_error_pending(const ResidentArchive* const& archive)
{
    return archive->worker.unk54 || archive->disc_thread.unk6c;
}

/**
 * @brief Report whether a hard disk unit error is pending.
 * @param archive Resource archive.
 * @return Whether an error is pending.
 */
bool resident_archive_has_unit_error(const ResidentArchive* archive)
{
    return archive_unit_error_pending(archive);
}

// TODO: This only matches with the conditional rebuild off: with it on, MWCC turns the inlined checks into
// conditional expressions and their joins lose the padding nops the game has. Turning it off for the whole file
// breaks seven other functions, so it was probably off just here.
#pragma push
#pragma opt_rebuildconditionals off

/**
 * @brief Get unk139, or zero while a unit error is pending.
 * @param archive Resource archive.
 * @return unk139, or zero.
 */
static inline s32 archive_unit_unk139(const ResidentArchive* archive)
{
    if (archive_unit_error_pending(archive))
    {
        return 0;
    }

    return archive->worker.unk4d;
}

/**
 * @brief Get unkfc, or zero while a unit error is pending.
 * @param archive Resource archive.
 * @return unkfc, or zero.
 */
static inline s32 archive_unit_unkfc(const ResidentArchive* archive)
{
    if (archive_unit_error_pending(archive))
    {
        return 0;
    }

    return archive->worker.unk10;
}

/**
 * @brief Get unit_ready, or zero while a unit error is pending.
 * @param archive Resource archive.
 * @return unit_ready, or zero.
 */
static inline s32 archive_unit_ready(const ResidentArchive* archive)
{
    if (archive_unit_error_pending(archive))
    {
        return 0;
    }

    return archive->worker.unit_ready;
}

/**
 * @brief Start a query of the unit and any existing install when the unit is usable (worker command 6), or end it
 * (command 7).
 * @param archive Resource archive.
 * @param first Nonzero to start the query, zero to end it.
 * @param second Nonzero to skip the unk139 check when starting.
 * @return True when a query is running or already done (or ended); false while a read is running, the unit isn't
 * usable or the worker couldn't start the command.
 */
bool resident_archive_query_unit(ResidentArchive* archive, s32 first, s32 second)
{
    if (archive->read_busy)
    {
        return 0;
    }

    if (!archive_unit_ready(archive))
    {
        return 0;
    }

    if (!archive_unit_unkfc(archive))
    {
        return 0;
    }

    if (first && !second && !archive_unit_unk139(archive))
    {
        return 0;
    }

    if (first)
    {
        if (!archive->unk12185)
        {
            if (archive_unit_error_pending(archive))
            {
                return 0;
            }

            archive->unk12185 = 1;
            return resident_archive_worker_start_command(&archive->worker, 6, 0);
        }

        return 1;
    }

    if (archive->unk12185)
    {
        archive->unk12185 = 0;
        return resident_archive_worker_start_command(&archive->worker, 7, 0);
    }

    return 1;
}
#pragma pop

/**
 * @brief Get the result of the last worker command.
 * @param archive Resource archive.
 * @return Zero on success, otherwise an error.
 */
s32 resident_archive_get_command_result(const ResidentArchive* archive)
{
    return archive->worker.command_result;
}

/**
 * @brief Report whether a worker command is running.
 * @param archive Resource archive.
 * @return Nonzero while a command runs.
 */
s32 resident_archive_is_busy(const ResidentArchive* archive)
{
    return archive->worker.command;
}

/**
 * @brief Get the words the install still has to copy.
 * @param archive Resource archive.
 * @return Remaining words.
 */
s32 resident_archive_get_copy_remaining(const ResidentArchive* archive)
{
    return archive->worker.copy_remaining;
}

/**
 * @brief Report whether the unit is ready, with no error pending.
 * @param archive Resource archive.
 * @return Nonzero when the unit is ready.
 */
s32 resident_archive_is_unit_ready(const ResidentArchive* archive)
{
    if (archive_unit_error_pending(archive))
    {
        return 0;
    }

    return archive->worker.unit_ready;
}

/**
 * @brief Set the buffer the install copies through.
 * @param archive Resource archive.
 * @param buffer Copy buffer, or null once the copy is done.
 */
void resident_archive_set_copy_buffer(ResidentArchive* archive, u8* buffer)
{
    archive->worker.copy_buffer = buffer;
}

/**
 * @brief Ask the running worker command to stop; nothing happens when no command runs.
 * @param archive Resource archive.
 */
static inline void archive_request_cancel(ResidentArchive* archive)
{
    ResidentSemaphoreLock lock(&archive->worker.command_semaphore);

    if (archive->worker.command == 0)
    {
        return;
    }

    archive->worker.cancel_requested = 1;
}

/**
 * @brief Ask the running worker command to stop.
 * @param archive Resource archive.
 */
void resident_archive_cancel_command(ResidentArchive* archive)
{
    archive_request_cancel(archive);
}

/**
 * @brief Queue a command for the hard disk worker.
 * @param archive Resource archive.
 * @param command Worker command.
 * @param argument Command argument.
 */
void resident_archive_start_command(ResidentArchive* archive, s32 command, s32 argument)
{
    resident_archive_worker_start_command(&archive->worker, command, argument);
}

/**
 * @brief Get the free space the last space query found.
 * @param archive Resource archive.
 * @return Free space in bytes.
 */
u32 resident_archive_get_free_space(const ResidentArchive* archive)
{
    return archive->worker.free_space;
}

/**
 * @brief Get the space the install needs, rounded up to 256 KiB.
 * @param archive Resource archive.
 * @return Needed space in bytes.
 */
u32 resident_archive_get_install_size(const ResidentArchive* archive)
{
    u32 total = 0;

    for (s32 i = 0; i < 0x1800; i++)
    {
        if (archive->install_flags[i] != 0)
        {
            total += archive->resource_entries[i];
        }
    }

    s32 size = total * 4 + RESIDENT_INSTALL_HEADER_SIZE;

    return (size + RESIDENT_INSTALL_ALIGNMENT - 1) & ~(RESIDENT_INSTALL_ALIGNMENT - 1);
}

/**
 * @brief Sum the entries of every resource the install copies.
 * @param archive Resource archive.
 * @return Install size in words.
 */
s32 resident_archive_get_install_words(const ResidentArchive* archive)
{
    u32 total = 0;

    for (s32 i = 0; i < 0x1800; i++)
    {
        if (archive->install_flags[i] != 0)
        {
            total += archive->resource_entries[i];
        }
    }

    return total;
}

/**
 * @brief Decode one of the xored names and append it to a path.
 * @param path Path to extend.
 * @param encoded Name with every character xored with 0xF3.
 */
static inline void append_decoded_name(char* path, const char* encoded)
{
    char name[256];
    char* out = name;

    while (*encoded != 0)
    {
        *out = *encoded ^ 0xF3;
        encoded++;
        out++;
    }

    *out = 0;
    strcat(path, name);
}

/**
 * @brief Stop the archive's streaming read.
 * @param archive Resource archive.
 */
static inline void archive_stop_read(ResidentArchive* archive)
{
    (void)archive->disc_thread.semaphore.wait();
    u8 stopping = archive->disc_thread.unk68;
    (void)archive->disc_thread.semaphore.signal();

    if (!stopping && archive->read_busy)
    {
        (void)archive->disc_thread.semaphore.wait();
        archive->disc_thread.unk68 = 1;

        if (archive->disc_thread.unk5e)
        {
            (void)archive->disc_thread.unk30.signal();
        }

        (void)archive->disc_thread.semaphore.signal();
    }
}

/**
 * @brief Body of the hard disk worker's thread.
 *
 * It first checks the drive, looks for the game's partition and works out the free space. Then it sleeps until a
 * command arrives: create or remove the partition, mount or unmount it, copy the install from the disc, open,
 * close, verify or delete the installed file, or idle the drive. Each command leaves its result in command_result
 * and wakes the thread that asked for it.
 */
void ResidentArchiveWorker::run()
{
    char path[256];

    (void)unk3c.wait();
    unk14 = sceDevctl(g_hdd_device, HDD_DEVCTL_STATUS, 0, 0, 0, 0);
    (void)unk3c.signal();
    unit_state = unk14;

    if (unk14 == 0)
    {
        strcpy_guess(path, g_hdd_partition_name);
        append_decoded_name(path, g_hdd_partition_suffix);
        append_decoded_name(path, g_hdd_partition_suffix);
        (void)unk3c.wait();
        s32 fd = sceOpen(path, 1);
        (void)unk3c.signal();

        if (fd < 0)
        {
            unk10 = 0;
        }
        else
        {
            (void)unk3c.wait();
            sceClose(fd);
            (void)unk3c.signal();
            unk10 = 1;
        }

        (void)unk3c.wait();
        s32 space = sceDevctl(g_hdd_device, HDD_DEVCTL_TOTAL_SECTORS, 0, 0, 0, 0);
        (void)unk3c.signal();
        s32 free;

        if (space > 0)
        {
            free = space;
        }
        else
        {
            free = 0;
        }

        if (free != 0)
        {
            (void)unk3c.wait();
            fd = sceDopen(g_hdd_device);
            (void)unk3c.signal();

            if (fd >= 0)
            {
                SceIoDirent entry;

                for (;;)
                {
                    (void)unk3c.wait();
                    s32 result = sceDread(fd, &entry);
                    (void)unk3c.signal();

                    if (result <= 0)
                    {
                        break;
                    }

                    if (entry.stat.mode != 0)
                    {
                        free -= entry.stat.size;
                    }
                }

                (void)unk3c.wait();
                sceDclose(fd);
                (void)unk3c.signal();
            }
            else
            {
                free = 0;
            }
        }

        free_space = free;
        unit_ready = 1;
    }

    for (;;)
    {
        resident_thread_sleep();

        switch (command)
        {
            case 1:
            {
                strcpy_guess(path, g_hdd_partition_name);
                append_decoded_name(path, g_hdd_partition_suffix);
                append_decoded_name(path, g_hdd_partition_suffix);
                strcat(path, g_hdd_partition_options);
                (void)unk3c.wait();
                s32 fd = sceOpen(path, 0x203);
                (void)unk3c.signal();

                if (fd < 0)
                {
                    if (fd == -5)
                    {
                        unk54 = 1;
                    }

                    command_result = 1;
                    break;
                }

                if (icon_header == 0)
                {
                    command_result = 1;
                    (void)unk3c.wait();
                    sceClose(fd);
                    (void)unk3c.signal();
                    break;
                }

                (void)unk3c.wait();
                s32 result = sceWrite(fd, icon_header, 0x200);
                (void)unk3c.signal();

                if (result < 0)
                {
                    if (result == -5)
                    {
                        unk54 = 1;
                    }

                    command_result = 1;
                    (void)unk3c.wait();
                    sceClose(fd);
                    (void)unk3c.signal();
                    break;
                }

                for (s32 i = 0; i < 4; i++)
                {
                    s32 offset = icon_header->files[i].offset;
                    s32 length = (icon_header->files[i].size + 0x1FF) & ~0x1FF;

                    (void)unk3c.wait();
                    result = sceLseek(fd, offset, 0);
                    (void)unk3c.signal();

                    if (result < 0)
                    {
                        if (result == -5)
                        {
                            unk54 = 1;
                        }

                        command_result = 1;
                        (void)unk3c.wait();
                        sceClose(fd);
                        (void)unk3c.signal();
                        break;
                    }

                    (void)unk3c.wait();
                    result = sceWrite(fd, system_files[i], length);
                    (void)unk3c.signal();

                    if (result < 0)
                    {
                        if (result == -5)
                        {
                            unk54 = 1;
                        }

                        command_result = 1;
                        (void)unk3c.wait();
                        sceClose(fd);
                        (void)unk3c.signal();
                        break;
                    }
                }

                const ResidentArchive* owner = archive;
                u32 total = 0;

                for (s32 i = 0; i < 0x1800; i++)
                {
                    if (owner->install_flags[i] != 0)
                    {
                        total += owner->resource_entries[i];
                    }
                }

                u32 size = total * 4 + RESIDENT_INSTALL_HEADER_SIZE;

                size = (size + RESIDENT_INSTALL_ALIGNMENT - 1) & ~(RESIDENT_INSTALL_ALIGNMENT - 1);
                s32 zones = (size + RESIDENT_INSTALL_ALIGNMENT - 1) >> 18;

                for (s32 i = 0; i < zones - 1; i++)
                {
                    HddZoneName name = g_hdd_zone_name;

                    (void)unk3c.wait();
                    s32 added = sceIoctl2(fd, HDD_IOCTL_ADD_SUB_PARTITION, &name, strlen(name.text) + 1, 0, 0);
                    (void)unk3c.signal();

                    if (added < 0)
                    {
                        if (added == -5)
                        {
                            unk54 = 1;
                        }

                        command_result = 1;
                        (void)unk3c.wait();
                        sceClose(fd);
                        (void)unk3c.signal();
                        break;
                    }
                }

                (void)unk3c.wait();
                sceClose(fd);
                (void)unk3c.signal();

                s32 zone_size = 0x2000;

                strcpy_guess(path, g_hdd_partition_name);
                append_decoded_name(path, g_hdd_partition_suffix);
                (void)unk3c.wait();
                result = sceFormat(g_pfs_device, path, &zone_size, 4);
                (void)unk3c.signal();

                if (result < 0)
                {
                    if (result == -5)
                    {
                        unk54 = 1;
                    }

                    command_result = 2;
                    break;
                }

                unk10 = 1;
                unk4d = 0;
                command_result = 0;
                break;
            }

            case 2:
            {
                strcpy_guess(path, g_hdd_partition_name);
                append_decoded_name(path, g_hdd_partition_suffix);
                append_decoded_name(path, g_hdd_partition_suffix);
                strcat(path, g_hdd_partition_options);
                (void)unk3c.wait();
                s32 result = sceRemove(path);
                (void)unk3c.signal();

                if (result < 0)
                {
                    if (result == -5)
                    {
                        unk54 = 1;
                        command_result = 4;
                        break;
                    }
                }
                else
                {
                    (void)unk3c.wait();
                    s32 space = sceDevctl(g_hdd_device, HDD_DEVCTL_TOTAL_SECTORS, 0, 0, 0, 0);
                    (void)unk3c.signal();
                    s32 free;

                    if (space > 0)
                    {
                        free = space;
                    }
                    else
                    {
                        free = 0;
                        command_result = 4;
                    }

                    if (free != 0)
                    {
                        (void)unk3c.wait();
                        s32 directory = sceDopen(g_hdd_device);
                        (void)unk3c.signal();

                        if (directory >= 0)
                        {
                            SceIoDirent entry;
                            s32 read;

                            for (;;)
                            {
                                (void)unk3c.wait();
                                read = sceDread(directory, &entry);
                                (void)unk3c.signal();

                                if (read <= 0)
                                {
                                    break;
                                }

                                if (entry.stat.mode != 0)
                                {
                                    free -= entry.stat.size;
                                }
                            }

                            if (read < 0)
                            {
                                command_result = 4;

                                if (read == -5)
                                {
                                    unk54 = 1;
                                }
                            }

                            (void)unk3c.wait();
                            sceDclose(directory);
                            (void)unk3c.signal();
                        }
                        else
                        {
                            free = 0;
                            command_result = 4;
                        }
                    }

                    free_space = free;
                }

                command_result = 0;
                unk10 = 0;
                unk4d = 0;
                break;
            }

            case 3:
            {
                strcpy_guess(path, g_hdd_partition_name);
                append_decoded_name(path, g_hdd_partition_suffix);
                append_decoded_name(path, g_hdd_partition_suffix);
                (void)unk3c.wait();
                s32 result = sceMount(g_pfs_mount, path, 0, 0, 0);
                (void)unk3c.signal();

                if (result < 0)
                {
                    command_result = 5;
                    break;
                }

                unk4e = 1;
                command_result = 0;
                break;
            }

            case 4:
                if (unk4e)
                {
                    (void)unk3c.wait();
                    s32 result = sceUmount(g_pfs_mount);
                    (void)unk3c.signal();

                    if (result < 0)
                    {
                        if (result == -5)
                        {
                            unk54 = 1;
                        }

                        command_result = 6;
                        break;
                    }

                    unk4e = 0;
                }

                command_result = 0;
                break;

            case 5:
            {
                command_result = 0;

                if (!unk4e)
                {
                    command_result = 7;
                    break;
                }

                if (copy_buffer == 0)
                {
                    command_result = 7;
                    break;
                }

                s32 words = 0;

                for (s32 i = 0; i < 0x1800; i++)
                {
                    if (archive->install_flags[i] != 0)
                    {
                        words += archive->resource_entries[i];
                    }
                }

                unk28 = words * 4;
                copy_remaining = words * 4;

                if (navigator_files[0] == 0 || navigator_files[1] == 0 || navigator_files[2] == 0)
                {
                    command_result = 7;
                    break;
                }

                (void)unk3c.wait();
                sceMkdir(g_pfs_resource_directory, 0x1ED);
                (void)unk3c.signal();

                strcpy_guess(path, g_pfs_mount);
                append_decoded_name(path, g_navigator_file_name_1);
                (void)unk3c.wait();
                s32 fd = sceOpen(path, 0x602, 0x1ED);
                (void)unk3c.signal();

                if (fd < 0)
                {
                    if (fd == -5)
                    {
                        unk54 = 1;
                    }

                    command_result = 7;
                    break;
                }

                (void)unk3c.wait();
                s32 result = sceWrite(fd, navigator_files[0], navigator_file_sizes[0]);
                (void)unk3c.signal();

                if (result < 0)
                {
                    command_result = 7;
                    break;
                }

                (void)unk3c.wait();
                sceClose(fd);
                (void)unk3c.signal();

                strcpy_guess(path, g_pfs_mount);
                append_decoded_name(path, g_navigator_file_name_2);
                (void)unk3c.wait();
                fd = sceOpen(path, 0x602, 0x1ED);
                (void)unk3c.signal();

                if (fd < 0)
                {
                    if (fd == -5)
                    {
                        unk54 = 1;
                    }

                    command_result = 7;
                    break;
                }

                (void)unk3c.wait();
                result = sceWrite(fd, navigator_files[1], navigator_file_sizes[1]);
                (void)unk3c.signal();

                if (result < 0)
                {
                    command_result = 7;
                    break;
                }

                (void)unk3c.wait();
                sceClose(fd);
                (void)unk3c.signal();

                strcpy_guess(path, g_pfs_mount);
                append_decoded_name(path, g_navigator_file_name_3);
                (void)unk3c.wait();
                fd = sceOpen(path, 0x602, 0x1ED);
                (void)unk3c.signal();

                if (fd < 0)
                {
                    if (fd == -5)
                    {
                        unk54 = 1;
                    }

                    command_result = 7;
                    break;
                }

                (void)unk3c.wait();
                result = sceWrite(fd, navigator_files[2], navigator_file_sizes[2]);
                (void)unk3c.signal();

                if (result < 0)
                {
                    command_result = 7;
                    break;
                }

                (void)unk3c.wait();
                sceClose(fd);
                (void)unk3c.signal();

                (void)unk3c.wait();
                fd = sceOpen(g_pfs_resource_file, 0x602, 0x1ED);
                (void)unk3c.signal();

                if (fd < 0)
                {
                    if (fd == -5)
                    {
                        unk54 = 1;
                    }

                    command_result = 7;
                    break;
                }

                s32 pending[2];
                s32 unit;
                ResidentArchive* owner = archive;

                {
                    ResidentSemaphoreLock lock(&owner->disc_thread.semaphore);
                }

                (void)owner->disc_thread.semaphore.wait();
                owner->disc_thread.listener = &listener;
                owner->disc_thread.listener_context = this;
                (void)owner->disc_thread.semaphore.signal();

                s32 write_half = 0;
                s32 read_half = 0;

                pending[0] = 0;
                pending[1] = 0;

                for (unit = 0; unit < 0x1800; unit++)
                {
                    if (archive->install_flags[unit] == 0)
                    {
                        continue;
                    }

                    if (cancel_requested)
                    {
                        (void)unk3c.wait();
                        sceClose(fd);
                        sceRemove(g_pfs_resource_file);
                        (void)unk3c.signal();
                        command_result = 8;
                        break;
                    }

                    s32 size = (archive->resource_entries[unit] & 0x00FFFFFF) << 11;
                    s32 sector = 0;

                    while (size != 0)
                    {
                        if (copy_paused)
                        {
                            resident_sound_add_wake_thread(resident_system_get_sound(resident_get_system()), this);
                            resident_thread_sleep();
                            continue;
                        }

                        s32 chunk = size > 0x100000 ? 0x100000 : size;

                        resident_archive_select_resource(archive, unit);
                        resident_archive_select_counted(archive, sector, unit);
                        resident_archive_start_read(archive, copy_buffer + (read_half << 20), chunk);

                        if (pending[write_half] != 0)
                        {
                            (void)unk3c.wait();
                            s32 written = sceWrite(fd, copy_buffer + (write_half << 20), pending[write_half]);
                            (void)unk3c.signal();
                            pending[write_half] = 0;

                            if (written < 0)
                            {
                                command_result = 7;
                                break;
                            }

                            write_half ^= 1;
                        }

                        resident_thread_sleep();
                        size -= chunk;
                        pending[read_half] = chunk;
                        read_half ^= 1;
                        sector += chunk / 0x800;
                        copy_remaining -= chunk / 0x200;

                        if (cancel_requested)
                        {
                            archive_stop_read(archive);
                            (void)unk3c.wait();
                            sceClose(fd);
                            sceRemove(g_pfs_resource_file);
                            (void)unk3c.signal();
                            command_result = 8;
                            break;
                        }
                    }

                    if (command_result == 8)
                    {
                        break;
                    }

                    if (command_result == 7)
                    {
                        archive_stop_read(archive);
                        (void)unk3c.wait();
                        sceClose(fd);
                        result = sceRemove(g_pfs_resource_file);
                        (void)unk3c.signal();

                        if (result == -5)
                        {
                            unk54 = 1;
                        }

                        break;
                    }
                }

                if (pending[write_half] != 0)
                {
                    (void)unk3c.wait();
                    result = sceWrite(fd, copy_buffer + (write_half << 20), pending[write_half]);
                    (void)unk3c.signal();

                    if (result < 0)
                    {
                        command_result = 7;
                    }

                    pending[write_half] = 0;
                }

                if (unit == 0x1800)
                {
                    s32 marker = 1;

                    (void)unk3c.wait();
                    sceWrite(fd, &marker, 4);
                    (void)unk3c.signal();
                }

                resident_reregister_resource_queue(resident_system_get_resource_queue(resident_get_system()));

                if (command_result != 0)
                {
                    break;
                }

                unk4d = 1;
                (void)unk3c.wait();
                sceClose(fd);
                (void)unk3c.signal();
                break;
            }

            case 6:
            {
                if (unk50 >= 0)
                {
                    command_result = 0;
                    break;
                }

                strcpy_guess(path, g_hdd_partition_name);
                append_decoded_name(path, g_hdd_partition_suffix);
                append_decoded_name(path, g_hdd_partition_suffix);
                strcat(path, g_hdd_partition_options);
                (void)unk3c.wait();
                s32 result = sceMount(g_pfs_mount, path, 0, 0, 0);
                (void)unk3c.signal();

                if (result < 0)
                {
                    command_result = 9;
                    break;
                }

                unk4e = 1;
                (void)unk3c.wait();
                unk50 = sceOpen(g_pfs_resource_file, 1, 0x1FF);
                (void)unk3c.signal();

                if (unk50 < 0)
                {
                    (void)unk3c.wait();
                    sceUmount(g_pfs_mount);
                    (void)unk3c.signal();
                    unk4e = 0;

                    if (unk50 == -5)
                    {
                        unk54 = 1;
                    }

                    command_result = 9;
                    break;
                }

                command_result = 0;
                break;
            }

            case 7:
            {
                s32 result;

                if (unk50 >= 0)
                {
                    (void)unk3c.wait();
                    result = sceClose(unk50);
                    (void)unk3c.signal();

                    if (result < 0)
                    {
                        command_result = 0xA;
                        break;
                    }
                }

                unk50 = -1;

                if (unk4e)
                {
                    (void)unk3c.wait();
                    result = sceUmount(g_pfs_mount);
                    (void)unk3c.signal();

                    if (result < 0)
                    {
                        if (result == -5)
                        {
                            unk54 = 1;
                        }

                        command_result = 0xA;
                        break;
                    }

                    unk4e = 0;
                }

                (void)unk3c.wait();
                result = sceDevctl(g_hdd_device, HDD_DEVCTL_IDLE_NOW, 0, 0, 0, 0);
                (void)unk3c.signal();

                if (result < 0)
                {
                    if (result == -5)
                    {
                        unk54 = 1;
                    }

                    command_result = 0xA;
                    break;
                }

                command_result = 0;
                break;
            }

            case 8:
            {
                if (!unk4e)
                {
                    command_result = 0xB;
                    break;
                }

                if (unk50 < 0)
                {
                    command_result = 0xB;
                    break;
                }

                (void)unk3c.wait();
                s64 end = sceLseek64(unk50, 0, 2);
                (void)unk3c.signal();

                if (end < 0)
                {
                    if (end == -5)
                    {
                        unk54 = 1;
                    }

                    command_result = 0xB;
                    break;
                }

                (void)unk3c.wait();
                s64 position = sceLseek64(unk50, -4, 2);
                (void)unk3c.signal();

                if (position < 0)
                {
                    if (position == -5)
                    {
                        unk54 = 1;
                    }

                    command_result = 0xB;
                    break;
                }

                s32 marker;

                (void)unk3c.wait();
                s32 result = sceRead(unk50, &marker, 4);
                (void)unk3c.signal();

                if ((u32)result < sizeof(marker))
                {
                    if (result == -5)
                    {
                        unk54 = 1;
                    }

                    command_result = 0xB;
                    break;
                }

                s32 i;
                u64 total = 0;

                for (i = 0; i < 0x1800; i++)
                {
                    if (archive->install_flags[i] != 0)
                    {
                        total += (archive->resource_entries[i] & 0x00FFFFFF) << 11;
                    }
                }

                if (total + 4 == end && marker == 1)
                {
                    command_result = 0;
                    unk4d = 1;
                    break;
                }

                command_result = 0xC;
                break;
            }

            case 9:
            {
                s32 result;

                if (unk50 >= 0)
                {
                    (void)unk3c.wait();
                    result = sceClose(unk50);
                    (void)unk3c.signal();

                    if (result < 0)
                    {
                        command_result = 0xD;
                        break;
                    }
                }

                unk50 = -1;
                unk4d = 0;
                (void)unk3c.wait();
                result = sceRemove(g_pfs_resource_file);
                (void)unk3c.signal();

                if (result == -5)
                {
                    unk54 = 1;
                    command_result = 0xD;
                    break;
                }

                if (unk4e)
                {
                    (void)unk3c.wait();
                    result = sceUmount(g_pfs_mount);
                    (void)unk3c.signal();

                    if (result < 0)
                    {
                        if (result == -5)
                        {
                            unk54 = 1;
                        }

                        command_result = 0xD;
                        break;
                    }

                    unk4e = 0;
                }

                command_result = 0;
                break;
            }

            case 10:
            {
                (void)unk3c.wait();
                s32 result = sceDevctl(g_hdd_device, HDD_DEVCTL_IDLE_NOW, 0, 0, 0, 0);
                (void)unk3c.signal();

                if (result < 0)
                {
                    command_result = 0xE;
                    break;
                }

                command_result = 0;
                break;
            }
        }

        if (command != 0)
        {
            command = 0;
            cancel_requested = 0;

            if (argument != 0)
            {
                resident_thread_wake((ResidentThread*)argument);
                argument = 0;
            }
        }
    }
}

/**
 * @brief Start a command on the hard disk worker and wake it.
 * @param worker Hard disk worker.
 * @param command Worker command.
 * @param argument Command argument.
 * @return True when the command started; false when the unit isn't ready or another command is running.
 */
bool resident_archive_worker_start_command(ResidentArchiveWorker* worker, s32 command, s32 argument)
{
    ResidentSemaphoreLock lock(&worker->command_semaphore);

    if (!worker->unit_ready)
    {
        return false;
    }

    if (worker->command)
    {
        return false;
    }

    worker->command = command;
    worker->argument = argument;
    worker->cancel_requested = 0;
    resident_thread_wake(worker);
    return true;
}

/** @brief Create the worker's thread and semaphores, idle and with no files. */
ResidentArchiveWorker::ResidentArchiveWorker()
{
    unk10 = 0;
    unk14 = 3;
    free_space = 0;
    unit_ready = 0;
    resident_thread_create(this, 0x25, 0x4000);
    command_result = 0;
    command = 0;
    argument = 0;
    copy_buffer = 0;
    cancel_requested = 0;
    unk4d = 0;
    unk4e = 0;
    unk28 = 0;
    unk50 = -1;
    unk54 = 0;
    icon_header = 0;
    copy_paused = 0;
    navigator_files[0] = 0;
    navigator_files[1] = 0;
    navigator_files[2] = 0;
    unit_state = 2;
    unk3c.create(1, 1);
    command_semaphore.create(1, 1);
}

/**
 * @brief Wake a thread.
 * @param data Thread to wake.
 */
void ResidentArchiveWorkerListener::notify(void* data)
{
    resident_thread_wake((ResidentThread*)data);
}

/**
 * @brief Body of the power-off thread: each time it is woken, wait for the hard disk worker, close the hard disk's
 * files, switch the expansion bay off and power the console off.
 */
void ResidentPowerOffThread::run()
{
    for (;;)
    {
        s32 result;

        resident_thread_sleep();

        // TODO: Only matches with the double negation; my guess is a small inline test was here.
        if (!!this->worker)
        {
            WaitSema(this->worker->unk3c.id);
        }

        sceDevctl(g_pfs_device, PFS_DEVCTL_CLOSE_ALL, 0, 0, 0, 0);

        while (sceDevctl(g_dev9_device, DEV9_DEVCTL_POWER_OFF, 0, 0, 0, 0) < 0)
        {
        }

        while (!sceCdPowerOff(&result) || result != 0)
        {
        }
    }
}

/**
 * @brief Disc power-off callback: wake the power-off thread.
 * @param argument Power-off thread.
 */
void resident_archive_on_power_off(void* argument)
{
    resident_thread_wakeup(argument);
}

/**
 * @brief Disc thread: seek to the selected resource and read it, at most 512 KiB at a time.
 * @param thread Disc thread.
 * @return One when the read finished or was stopped, zero after a read error.
 */
s32 resident_disc_thread_read(ResidentDiscThread* thread)
{
    thread->unk70 = 0;

    (void)thread->semaphore.wait();
    thread->unk69 = 1;
    (void)thread->semaphore.signal();

    // TODO: Nothing reads this result (or limit_locked below), but the target keeps it and a (void) call doesn't.
    bool locked = thread->semaphore.wait();
    s32 offset = thread->unk98;
    (void)thread->semaphore.signal();

    // TODO: Only the first lock goes through this local; the target reads the owner before the position and again
    // for every later use.
    ResidentArchive* owner = thread->owner;
    s64 position = ((s64)thread->unk58 << 11) + offset;
    (void)owner->worker.unk3c.wait();
    sceLseek64(thread->owner->worker.unk50, position, 0);
    (void)thread->owner->worker.unk3c.signal();

    s32 saved_size = thread->unk80;
    u32 saved_cursor = thread->unk84;

    while (thread->unk80 > 0)
    {
        s32 chunk;

        if (thread->unk80 > 0x80000)
        {
            chunk = 0x80000;
        }
        else
        {
            chunk = thread->unk80;
        }

        (void)thread->semaphore.wait();
        u8 stopping = thread->unk68;
        (void)thread->semaphore.signal();

        if (stopping)
        {
            (void)thread->semaphore.wait();
            thread->unk68 = 0;
            (void)thread->semaphore.signal();
            break;
        }

        (void)thread->semaphore.wait();
        u8 streaming = thread->unk5e;
        (void)thread->semaphore.signal();

        if (streaming)
        {
            (void)thread->semaphore.wait();
            u8 paused = thread->unk6a;
            (void)thread->semaphore.signal();

            if (paused)
            {
                (void)thread->semaphore.wait();
                thread->unk69 = 0;
                (void)thread->semaphore.signal();
                (void)thread->unk28.wait();
                (void)thread->semaphore.wait();
                thread->unk69 = 1;
                (void)thread->semaphore.signal();
                continue;
            }

            if (thread->unk84 + chunk >= thread->owner->unk12194 + thread->owner->unk121a0)
            {
                chunk = thread->owner->unk12194 + thread->owner->unk121a0 - thread->unk84;
            }

            bool limit_locked = thread->semaphore.wait();
            u32 limit = thread->unk8c;
            (void)thread->semaphore.signal();

            limit -= 0x4000;

            if (limit <= thread->owner->unk12194)
            {
                limit += thread->owner->unk121a0;
            }

            if (thread->unk84 <= limit && thread->unk84 + chunk >= limit)
            {
                chunk = limit - thread->unk84;
            }

            if (chunk == 0)
            {
                thread->unk60 = 3;
                (void)thread->unk30.wait();
                continue;
            }
        }

        chunk &= ~0x7FF;
        thread->unk60 = 4;
        (void)thread->owner->worker.unk3c.wait();
        s32 read = sceRead(thread->owner->worker.unk50, (void*)thread->unk84, chunk);
        (void)thread->owner->worker.unk3c.signal();

        if (read == -5)
        {
            thread->unk6c = 1;
            thread->unk80 = saved_size;
            thread->unk84 = saved_cursor;
            thread->owner->unk12185 = 0;
            resident_archive_worker_start_command(&thread->owner->worker, 7, 0);
            return 0;
        }

        if (read == -5)
        {
            thread->unk6c = 1;
            thread->unk80 = saved_size;
            thread->unk84 = saved_cursor;
            thread->owner->unk12185 = 0;
            resident_archive_worker_start_command(&thread->owner->worker, 9, 0);
            return 0;
        }

        thread->unk84 += read;
        thread->unk80 -= read;

        (void)thread->semaphore.wait();
        u8 ring = thread->unk5e;
        (void)thread->semaphore.signal();

        if (ring)
        {
            (void)thread->semaphore.wait();
            thread->unk88 += read;

            if (thread->unk88 < 0)
            {
                thread->unk88 = 0;
            }

            (void)thread->semaphore.signal();

            u32 cursor = thread->unk84;

            if (cursor >= thread->owner->unk12194 + thread->owner->unk121a0)
            {
                cursor -= thread->owner->unk121a0;
                thread->unk84 = cursor;
            }
        }

        if (thread->unk80 <= 0)
        {
            break;
        }
    }

    thread->unk60 = 9;
    thread->owner->read_busy = 0;

    (void)thread->semaphore.wait();
    ResidentListener* listener = thread->listener;
    void* context = thread->listener_context;
    (void)thread->semaphore.signal();

    if (listener)
    {
        listener->notify(context);
    }

    thread->unk50 = 0;

    (void)thread->semaphore.wait();
    thread->unk69 = 0;
    (void)thread->semaphore.signal();
    return 1;
}

/**
 * @brief Sleep until the sound interrupt wakes the thread.
 * @param thread Calling thread.
 */
static inline void sleep_until_sound_interrupt(ResidentThread* thread)
{
    resident_sound_add_wake_thread(resident_system_get_sound(resident_get_system()), thread);
    resident_thread_sleep();
}

/**
 * @brief Read the disc thread's stop request under its semaphore.
 * @param thread Disc thread.
 * @return Nonzero when the current read was asked to stop.
 */
static inline u8 disc_stop_requested(ResidentDiscThread* thread)
{
    (void)thread->semaphore.wait();
    u8 requested = thread->unk68;
    (void)thread->semaphore.signal();
    return requested;
}

/**
 * @brief Body of the disc thread: sleep until a read is requested, then read the selected resource from the hard
 * disk or, sector by sector, from the disc, retrying after errors and timeouts, and notify the listener at the end.
 */
void ResidentDiscThread::run()
{
    for (;;)
    {
        switch (unk50)
        {
        case 0:
            unk70 = 0;
            unk60 = 0;
            (void)semaphore.wait();

            if (unk5d)
            {
                unk50 = 2;
                unk94 = unk90;
                unk5d = 0;
            }
            else if (unk5c)
            {
                unk50 = 1;
                unk5c = 0;
            }

            if (unk50 == 0)
            {
                resident_sound_add_wake_thread(resident_system_get_sound(resident_get_system()), this);
                (void)semaphore.signal();

                (void)semaphore.wait();
                unk6b = 0;
                (void)semaphore.signal();

                resident_thread_sleep();

                (void)semaphore.wait();
                unk6b = 1;
                (void)semaphore.signal();
            }
            else
            {
                (void)semaphore.signal();
                (void)unk48.wait();
                (void)unk48.signal();
            }

            break;

        case 1:
        {
            if (unk61 && owner->worker.unk50 >= 0)
            {
                if (resident_disc_thread_read(this))
                {
                    break;
                }
            }

            (void)semaphore.wait();
            u8 streaming = unk5e;
            (void)semaphore.signal();

            if (streaming)
            {
                (void)semaphore.wait();
                unk69 = 1;
                (void)semaphore.signal();

                unk70 = 0;
                bool checked = false;

                for (;;)
                {
                    (void)semaphore.wait();
                    u8 stopping = unk68;
                    (void)semaphore.signal();

                    if (stopping)
                    {
                        break;
                    }

                    if (unk80 <= 0)
                    {
                        break;
                    }

                    if (checked)
                    {
                        unk60 = 1;
                        (void)unk48.wait();
                        s32 status = sceCdStatus();
                        (void)unk48.signal();

                        if (status == -1)
                        {
                            sleep_until_sound_interrupt(this);
                            unk70++;
                            continue;
                        }

                        switch (status)
                        {
                        case 1:
                            unk60 = 2;
                            sleep_until_sound_interrupt(this);
                            unk70++;
                            continue;
                        }
                    }
                    else
                    {
                        checked = true;
                    }

                    if (unk6a)
                    {
                        (void)unk48.signal();
                        sceCdSync(0);
                        (void)unk48.wait();

                        (void)semaphore.wait();
                        unk69 = 0;
                        (void)semaphore.signal();

                        sleep_until_sound_interrupt(this);

                        (void)semaphore.wait();
                        unk69 = 1;
                        (void)semaphore.signal();
                        continue;
                    }

                    s32 chunk;

                    if (unk80 > 0x80000)
                    {
                        chunk = 0x80000;
                    }
                    else
                    {
                        chunk = unk80;
                    }

                    if (unk84 + chunk >= owner->unk12194 + owner->unk121a0)
                    {
                        chunk = owner->unk12194 + owner->unk121a0 - unk84;
                    }

                    // TODO: Nothing reads this result, but the target keeps it and a (void) call doesn't.
                    bool limit_locked = semaphore.wait();
                    u32 limit = unk8c;
                    (void)semaphore.signal();

                    limit -= 0x4000;

                    if (limit <= owner->unk12194)
                    {
                        limit += owner->unk121a0;
                    }

                    if (unk84 <= limit && unk84 + chunk >= limit)
                    {
                        chunk = limit - unk84;
                    }

                    chunk &= ~0x7FF;

                    if (chunk == 0)
                    {
                        unk60 = 3;
                        (void)unk30.wait();
                        checked = false;
                        continue;
                    }

                    sceCdRMode mode;
                    mode.trycount = 0;
                    mode.spindlctrl = 0;
                    mode.datapattern = 0;
                    unk60 = 4;

                    s32 size;
                    s32 result;

                    for (;;)
                    {
                        while (timeout_semaphore.poll())
                        {
                        }

                        (void)unk48.wait();
                        timed_out = 0;

                        if (unk80 - chunk < 0)
                        {
                            result = sceCdRead(unk54, (u32)unk80 >> 11, (void*)unk84, &mode);
                            size = unk80;
                        }
                        else
                        {
                            result = sceCdRead(unk54, (u32)chunk >> 11, (void*)unk84, &mode);
                            size = chunk;
                        }

                        (void)unk48.signal();

                        if (!result)
                        {
                            sleep_until_sound_interrupt(this);
                            unk70++;
                            continue;
                        }

                        timeout_ticks = 0;
                        timeout_alarm = resident_system_set_alarm(resident_get_system(), 0x106, resident_disc_timeout_alarm, this);
                        unk60 = 5;
                        (void)timeout_semaphore.wait();

                        if (!timed_out)
                        {
                            break;
                        }

                        for (;;)
                        {
                            unk60 = 0xB;
                            (void)unk48.wait();

                            if (sceCdBreak())
                            {
                                (void)unk48.signal();
                                break;
                            }

                            (void)unk48.signal();
                            sleep_until_sound_interrupt(this);
                            unk70++;
                        }

                        (void)unk48.wait();
                        sceCdSync(0);
                        (void)unk48.signal();
                    }

                    DIntr();

                    if (timeout_alarm >= 0)
                    {
                        ReleaseAlarm(timeout_alarm);
                    }

                    EIntr();

                    (void)semaphore.wait();
                    u8 cancelled = unk68;
                    (void)semaphore.signal();

                    if (cancelled)
                    {
                        for (;;)
                        {
                            unk60 = 0xA;
                            (void)unk48.wait();

                            if (sceCdBreak())
                            {
                                (void)unk48.signal();
                                break;
                            }

                            (void)unk48.signal();
                            sleep_until_sound_interrupt(this);
                            unk70++;
                        }

                        (void)unk48.wait();
                        sceCdSync(0);
                        (void)unk48.signal();
                    }

                    for (;;)
                    {
                        unk60 = 6;
                        (void)unk48.wait();
                        result = sceCdGetError();
                        (void)unk48.signal();

                        if (result != -1)
                        {
                            break;
                        }

                        sleep_until_sound_interrupt(this);
                        unk70++;
                    }

                    if (result != 0 && (result != 1 || !disc_stop_requested(this)))
                    {
                        unk60 = 7;
                        sleep_until_sound_interrupt(this);
                        unk70++;
                        continue;
                    }

                    ResidentReadListener* reader = (ResidentReadListener*)unk64;

                    if (reader)
                    {
                        reader->handle(unk84, size, owner->unk12194, owner->unk121a0);
                    }

                    unk84 += size;
                    unk80 -= size;
                    unk54 += size / 2048;

                    (void)semaphore.wait();
                    unk88 += size;

                    if (unk88 < 0)
                    {
                        unk88 = 0;
                    }

                    (void)semaphore.signal();

                    u32 cursor = unk84;

                    if (cursor >= owner->unk12194 + owner->unk121a0)
                    {
                        cursor -= owner->unk121a0;
                        unk84 = cursor;
                    }

                    checked = false;
                }
            }
            else
            {
                unk70 = 0;
                bool checked = false;

                (void)semaphore.wait();
                unk69 = 1;
                (void)semaphore.signal();

                for (;;)
                {
                    (void)semaphore.wait();
                    u8 stopping = unk68;
                    (void)semaphore.signal();

                    if (stopping)
                    {
                        break;
                    }

                    if (checked)
                    {
                        unk60 = 1;
                        (void)unk48.wait();
                        s32 status = sceCdStatus();
                        (void)unk48.signal();

                        if (status == -1)
                        {
                            sleep_until_sound_interrupt(this);
                            unk70++;
                            continue;
                        }

                        switch (status)
                        {
                        case 1:
                            unk60 = 2;
                            sleep_until_sound_interrupt(this);
                            unk70++;
                            continue;
                        }
                    }
                    else
                    {
                        checked = true;
                    }

                    sceCdRMode mode;
                    mode.trycount = 0;
                    mode.spindlctrl = g_disc_spindle_override ? 0 : 1;
                    mode.datapattern = 0;
                    unk60 = 4;

                    while (timeout_semaphore.poll())
                    {
                    }

                    (void)unk48.wait();
                    timed_out = 0;
                    s32 started = sceCdRead(unk54, (u32)unk80 >> 11, (void*)unk84, &mode);
                    (void)unk48.signal();

                    if (!started)
                    {
                        sleep_until_sound_interrupt(this);
                        unk70++;
                        continue;
                    }

                    timeout_ticks = 0;

                    if ((timeout_alarm = resident_system_set_alarm(resident_get_system(), 0x106, resident_disc_timeout_alarm, this)) != -1)
                    {
                        unk60 = 5;
                        (void)timeout_semaphore.wait();
                    }

                    if (timed_out)
                    {
                        for (;;)
                        {
                            unk60 = 0xB;
                            (void)unk48.wait();

                            if (sceCdBreak())
                            {
                                (void)unk48.signal();
                                break;
                            }

                            (void)unk48.signal();
                            sleep_until_sound_interrupt(this);
                            unk70++;
                        }

                        (void)unk48.wait();
                        sceCdSync(0);
                        (void)unk48.signal();
                        continue;
                    }

                    DIntr();

                    if (timeout_alarm >= 0)
                    {
                        ReleaseAlarm(timeout_alarm);
                    }

                    EIntr();

                    (void)semaphore.wait();
                    u8 cancelled = unk68;
                    (void)semaphore.signal();

                    if (cancelled)
                    {
                        for (;;)
                        {
                            unk60 = 0xA;
                            (void)unk48.wait();

                            if (sceCdBreak())
                            {
                                (void)unk48.signal();
                                break;
                            }

                            (void)unk48.signal();
                            sleep_until_sound_interrupt(this);
                            unk70++;
                        }

                        (void)unk48.wait();
                        sceCdSync(0);
                        (void)unk48.signal();
                        break;
                    }

                    s32 error;

                    for (;;)
                    {
                        unk60 = 6;
                        (void)unk48.wait();
                        error = sceCdGetError();
                        (void)unk48.signal();

                        if (error != -1)
                        {
                            break;
                        }

                        sleep_until_sound_interrupt(this);
                        unk70++;
                    }

                    if (error == 0)
                    {
                        break;
                    }

                    if (error == 1)
                    {
                        (void)semaphore.wait();
                        u8 stopped = unk68;
                        (void)semaphore.signal();

                        if (stopped)
                        {
                            break;
                        }
                    }

                    unk60 = 7;
                    sleep_until_sound_interrupt(this);
                    unk70++;
                }
            }

            (void)unk48.wait();
            sceCdSync(0);
            (void)unk48.signal();

            unk60 = 9;
            owner->read_busy = 0;

            (void)semaphore.wait();
            unk69 = 0;
            (void)semaphore.signal();

            unk50 = 0;

            (void)semaphore.wait();
            ResidentListener* finished = listener;
            void* context = listener_context;
            (void)semaphore.signal();

            if (finished)
            {
                finished->notify(context);
            }

            break;
        }

        case 2:
            unk50 = 0;
            break;
        }
    }
}

/**
 * @brief Body of the status thread: while the disc library is up, poll the drive status and the clock, then the read
 * position thirty times, sleeping until the sound interrupt between polls.
 */
void ResidentDiscStatusThread::run()
{
    for (;;)
    {
        if (!owner->unk5f)
        {
            sleep_until_sound_interrupt(this);
            continue;
        }

        if (owner->unk50 != 1)
        {
            unk1c = 1;
            (void)owner->unk48.wait();

            if (sceCdStatus() == 1)
            {
                unk20 |= 1;
            }
            else
            {
                unk20 &= ~1;
            }

            (void)owner->unk48.signal();
            unk1c = 0;
        }

        DIntr();

        if (unk1d)
        {
            EIntr();
            sleep_until_sound_interrupt(this);
            continue;
        }

        unk1c = 1;
        EIntr();
        (void)owner->unk48.wait();
        ResidentClock reported;
        unk14 = sceCdReadClock(&reported);
        (void)owner->unk48.signal();
        unk1c = 0;

        if (unk14)
        {
            clock.status = reported.status;
            clock.second = reported.second;
            clock.minute = reported.minute;
            clock.hour = reported.hour;
            clock.pad = reported.pad;
            clock.day = reported.day;
            clock.month = reported.month;
            clock.year = reported.year;
        }

        s32 polls = 30;

        for (s32 i = 0; i < polls; i++)
        {
            if (owner->unk50 == 1)
            {
                DIntr();

                if (unk1d)
                {
                    EIntr();
                    sleep_until_sound_interrupt(this);
                    continue;
                }

                unk1c = 1;
                EIntr();
                (void)owner->unk48.wait();
                unk18 = sceCdGetReadPos();
                (void)owner->unk48.signal();
                unk1c = 0;
            }

            sleep_until_sound_interrupt(this);
        }
    }
}

/**
 * @brief Disc library callback: wake the disc thread when a read finishes.
 * @param reason Disc function that finished.
 */
void resident_disc_callback(s32 reason)
{
    if (reason == SCECdFuncRead)
    {
        ResidentDiscThread* thread = g_disc_thread;
        (void)thread->timeout_semaphore.signal();
    }
}

/**
 * @brief Disc command timeout alarm: count a tick, and signal the timeout semaphore once the count runs out or the
 * command finished; otherwise set the alarm again.
 * @param alarm_id Alarm.
 * @param time Time the alarm fired.
 * @param common Resource archive.
 */
extern "C" void resident_disc_timeout_alarm(s32 alarm_id, u16 time, void* common)
{
    ResidentArchive* archive = (ResidentArchive*)common;

    archive->disc_thread.timeout_ticks++;
    archive->disc_thread.unk70++;
    archive->disc_thread.timeout_alarm = -1;

    if (archive->disc_thread.timeout_ticks >= 0x708)
    {
        archive->disc_thread.timed_out = 1;
        (void)archive->disc_thread.timeout_semaphore.isignal();
    }
    else if (archive->disc_thread.unk68)
    {
        (void)archive->disc_thread.timeout_semaphore.isignal();
    }
    else
    {
        archive->disc_thread.timeout_alarm = resident_system_iset_alarm(resident_get_system(), 0x106, resident_disc_timeout_alarm, archive);
    }

    ee_exit_handler();
}

/** @brief Destroy the thread. */
inline ResidentDiscStatusThread::~ResidentDiscStatusThread()
{
}

/** @brief Destroy the thread. */
inline ResidentPowerOffThread::~ResidentPowerOffThread()
{
}

/** @brief Destroy the thread and its semaphores. */
ResidentDiscThread::~ResidentDiscThread()
{
}

/** @brief Create the semaphores and start the status thread. */
ResidentDiscThread::ResidentDiscThread()
{
    resident_thread_create(this, 0x25, 0x4000);
    unk64 = 0;
    unk50 = 0;
    unk6b = 0;
    unk10.create(0, 1);
    unk20.create(0, 1);
    unk28.create(0, 0);
    unk30.create(0, 0);
    semaphore.create(1, 1);
    timeout_semaphore.create(0, 1);
    unk48.create(1, 1);
    owner = 0;
    unk68 = 0;
    unk5d = 0;
    unk7c = -1;
    unk61 = 0;
    unk62 = 0;
    timeout_ticks = 0;
    timed_out = 0;
    unk5e = 0;
    unk6a = 0;
    listener = 0;
    unk5f = 0;
    unk6c = 0;
    unk54 = 0;
    unk60 = 0;
    g_disc_thread = this;
    unkAC.owner = this;
    unkAC.start();
}

/**
 * @brief Read the archive's unk5E flag under its semaphore.
 * @param archive Resource archive.
 * @return The flag.
 */
static inline u8 archive_read_unk5e(ResidentArchive* archive)
{
    (void)archive->disc_thread.semaphore.wait();
    u8 value = archive->disc_thread.unk5e;
    (void)archive->disc_thread.semaphore.signal();
    return value;
}

/**
 * @brief Report whether the archive's unk5E flag is clear.
 * @param archive Resource archive.
 * @return True when it is clear.
 */
static inline bool archive_unk5e_clear(ResidentArchive* archive)
{
    return !archive_read_unk5e(archive);
}

/**
 * @brief Clear unk6A and signal unk28, while unk5E is set, a read is in progress and unk6A is set.
 * @param archive Resource archive.
 */
void resident_archive_release_read(ResidentArchive* archive)
{
    if (!archive_read_unk5e(archive) || !archive->read_busy)
    {
        return;
    }

    (void)archive->disc_thread.semaphore.wait();
    u8 pending = archive->disc_thread.unk6a;
    (void)archive->disc_thread.semaphore.signal();

    if (!pending)
    {
        return;
    }

    (void)archive->disc_thread.semaphore.wait();
    archive->disc_thread.unk6a = 0;
    (void)archive->disc_thread.semaphore.signal();
    (void)archive->disc_thread.unk28.signal();
}

/**
 * @brief Set unk6A once, while unk5E is set and a read is in progress.
 * @param archive Resource archive.
 */
void resident_archive_hold_read(ResidentArchive* archive)
{
    if (!archive_read_unk5e(archive) || !archive->read_busy)
    {
        return;
    }

    (void)archive->disc_thread.semaphore.wait();
    u8 pending = archive->disc_thread.unk6a;
    (void)archive->disc_thread.semaphore.signal();

    if (pending)
    {
        return;
    }

    (void)archive->disc_thread.semaphore.wait();
    archive->disc_thread.unk6a = 1;
    (void)archive->disc_thread.semaphore.signal();
}

/**
 * @brief Advance the position at unk8C by count, wrapping it like resident_archive_get_ring_positions, take count off unk88 (stopping at
 * zero), then signal unk30.
 * @param archive Resource archive.
 * @param count Amount to move by.
 */
void resident_archive_consume_ring(ResidentArchive* archive, s32 count)
{
    (void)archive->disc_thread.semaphore.wait();
    archive->disc_thread.unk8c += count;

    if (archive->disc_thread.unk8c >= archive->disc_thread.owner->unk12194 + archive->disc_thread.owner->unk121a0)
    {
        archive->disc_thread.unk8c -= archive->disc_thread.owner->unk121a0;
    }

    (void)archive->disc_thread.semaphore.signal();
    (void)archive->disc_thread.semaphore.wait();
    archive->disc_thread.unk88 -= count;

    if (archive->disc_thread.unk88 < 0)
    {
        archive->disc_thread.unk88 = 0;
    }

    (void)archive->disc_thread.semaphore.signal();
    (void)archive->disc_thread.unk30.signal();
}

/**
 * @brief Read the two positions at unk88 and unk8C under the archive's semaphore.
 * @param archive Resource archive.
 * @param position Receives unk8C plus one, less unk121A0 once it reaches unk12194 plus unk121A0.
 * @return unk88.
 */
s32 resident_archive_get_ring_positions(ResidentArchive* archive, u32* position)
{
    (void)archive->disc_thread.semaphore.wait();
    u32 current = archive->disc_thread.unk8c;
    (void)archive->disc_thread.semaphore.signal();

    *position = current + 1;

    if (*position >= archive->unk12194 + archive->unk121a0)
    {
        *position -= archive->unk121a0;
    }

    (void)archive->disc_thread.semaphore.wait();
    s32 result = archive->disc_thread.unk88;
    (void)archive->disc_thread.semaphore.signal();
    return result;
}

/**
 * @brief Start streaming the selected resource through a ring buffer: reset the read state, keep the ring, mark the
 * read busy and wake the disc thread.
 * @param archive Resource archive.
 * @param buffer Ring buffer.
 * @param ring_size Ring size in bytes; a multiple of 64 KiB.
 * @param size Bytes to read, or zero for the whole resource.
 * @return One once the read is started, or zero while another read is running, the ring size is wrong or nothing is
 * selected.
 */
s32 resident_archive_start_ring_read(ResidentArchive* archive, void* buffer, u32 ring_size, s32 size)
{
    if (archive->read_busy)
    {
        return 0;
    }

    if (ring_size & 0xFFFF)
    {
        return 0;
    }

    (void)archive->disc_thread.semaphore.wait();
    u8 busy = archive->disc_thread.unk5c;
    (void)archive->disc_thread.semaphore.signal();

    if (busy)
    {
        return 0;
    }

    (void)archive->disc_thread.semaphore.wait();
    archive->disc_thread.unk68 = 0;
    (void)archive->disc_thread.semaphore.signal();

    (void)archive->disc_thread.semaphore.wait();
    archive->disc_thread.unk69 = 0;
    (void)archive->disc_thread.semaphore.signal();

    (void)archive->disc_thread.semaphore.wait();
    archive->disc_thread.unk5e = 1;
    (void)archive->disc_thread.semaphore.signal();

    (void)archive->disc_thread.semaphore.wait();
    archive->disc_thread.unk6a = 0;
    (void)archive->disc_thread.semaphore.signal();

    (void)archive->disc_thread.unk28.signal();
    archive->unk12194 = (u32)buffer;
    archive->unk121a0 = ring_size;
    u32 end = (u32)buffer + archive->unk121a0 - 1;

    (void)archive->disc_thread.semaphore.wait();
    archive->disc_thread.unk8c = end;
    (void)archive->disc_thread.semaphore.signal();

    (void)archive->disc_thread.semaphore.wait();
    archive->disc_thread.unk88 = 0;
    (void)archive->disc_thread.semaphore.signal();

    if (archive->unk12181)
    {
        if (size)
        {
            archive->disc_thread.unk80 = size;
        }

        archive->disc_thread.unk84 = (u32)buffer;
        archive->read_busy = 1;
        archive->disc_thread.unkAC.unk18 = 0;

        (void)archive->disc_thread.semaphore.wait();

        if (archive->disc_thread.unk5c)
        {
            (void)archive->disc_thread.semaphore.signal();
        }
        else
        {
            archive->disc_thread.unk5c = 1;
            (void)archive->disc_thread.semaphore.signal();
            (void)archive->disc_thread.unk10.signal();
        }
    }
    else
    {
        return 0;
    }

    return 1;
}

void resident_archive_do_nothing(void* object)
{
}

/**
 * @brief Get the position of a resource in the archive.
 * @param archive Resource archive.
 * @param key Resource key.
 * @return Position in 2048-byte blocks.
 */
u32 resident_archive_get_resource_position(const ResidentArchive* archive, s32 key)
{
    return archive->resource_positions[key] & 0x00FFFFFF;
}

/**
 * @brief Report whether the archive is idle: unk5C, unk5D and unk6B all clear, read under its semaphore.
 * @param archive Resource archive.
 * @return True when all three are clear.
 */
extern "C" bool resident_archive_is_idle(ResidentArchive* archive)
{
    (void)archive->disc_thread.semaphore.wait();
    bool active = archive->disc_thread.unk5c || archive->disc_thread.unk5d || archive->disc_thread.unk6b;
    (void)archive->disc_thread.semaphore.signal();
    return !active;
}

/** Return bit 0 of the word at receiver offset 0xCC. */
s32 resident_archive_get_flag_cc(const void* object)
{
    const u32* values = (const u32*)object;
    return (values[0x33] & 1) != 0;
}

/**
 * @brief Get unk70 when unk12186 is set, or a read is in progress with unk5E clear; otherwise zero.
 * @param archive Resource archive.
 * @return unk70, or zero.
 */
extern "C" s32 resident_archive_get_read_result(ResidentArchive* archive)
{
    u8 ready = archive->unk12186;

    if (!ready)
    {
        u8 reading = archive->read_busy;

        if (reading)
        {
            reading = archive_unk5e_clear(archive);
        }

        ready = reading;
    }

    if (ready)
    {
        return archive->disc_thread.unk70;
    }

    return 0;
}

/**
 * @brief Get the size of a resource, in whole 2048-byte blocks.
 * @param archive Resource archive.
 * @param key Resource key.
 * @return Resource size in bytes.
 */
u32 resident_get_resource_size(const ResidentArchive* archive, s32 key)
{
    return (archive->resource_entries[key] & 0x00FFFFFF) << 11;
}

/**
 * @brief Stop the archive's streaming read.
 * @param archive Resource archive.
 */
void resident_archive_stop_ring_read(ResidentArchive* archive)
{
    archive_stop_read(archive);
}

/**
 * @brief Read a resource and wait for the read to finish, retrying until it starts.
 * @param archive Resource archive.
 * @param buffer Destination.
 * @param key Resource key.
 * @param size Bytes to read, or zero for the whole resource.
 * @return One.
 */
s32 resident_archive_read_resource(ResidentArchive* archive, void* buffer, s32 key, s32 size)
{
    do
    {
        while (!resident_archive_select_resource(archive, key))
        {
        }
    } while (!resident_archive_start_read(archive, buffer, size));

    while (archive->read_busy)
    {
    }

    return 1;
}

/**
 * @brief Select a resource for the next read, adding size to the counters at unk54 and unk58 when unk12181 is set.
 * @param archive Resource archive.
 * @param size Amount added to both counters.
 * @param key Resource key.
 * @return Nonzero when the resource was selected, or zero while a read is running.
 */
u8 resident_archive_select_counted(ResidentArchive* archive, s32 size, s32 key)
{
    if (archive->read_busy)
    {
        return 0;
    }

    (void)archive->disc_thread.semaphore.wait();
    archive->disc_thread.unk68 = 0;
    (void)archive->disc_thread.semaphore.signal();

    u8 selected = resident_archive_select_resource(archive, key);

    if (archive->unk12181 && selected && size)
    {
        archive->disc_thread.unk54 += size;
        archive->disc_thread.unk58 += size;
    }

    return selected;
}

/**
 * @brief Start reading the resource resident_archive_select_resource selected: reset the read state, keep the buffer and size, mark the
 * read busy and wake the disc thread.
 * @param archive Resource archive.
 * @param buffer Destination.
 * @param size Bytes to read, or zero for the whole resource.
 * @return One once the read is started, or zero while another read is running or nothing is selected.
 */
s32 resident_archive_start_read(ResidentArchive* archive, void* buffer, s32 size)
{
    if (archive->read_busy)
    {
        return 0;
    }

    (void)archive->disc_thread.semaphore.wait();
    u8 busy = archive->disc_thread.unk5c;
    (void)archive->disc_thread.semaphore.signal();

    if (busy)
    {
        return 0;
    }

    (void)archive->disc_thread.semaphore.wait();
    archive->disc_thread.unk68 = 0;
    (void)archive->disc_thread.semaphore.signal();

    (void)archive->disc_thread.semaphore.wait();
    archive->disc_thread.unk69 = 0;
    (void)archive->disc_thread.semaphore.signal();

    (void)archive->disc_thread.semaphore.wait();
    archive->disc_thread.unk5e = 0;
    (void)archive->disc_thread.semaphore.signal();

    (void)archive->disc_thread.semaphore.wait();
    archive->disc_thread.unk6a = 0;
    (void)archive->disc_thread.semaphore.signal();

    (void)archive->disc_thread.unk28.signal();
    archive->disc_thread.unk70 = 0;

    if (archive->unk12181)
    {
        if (size)
        {
            archive->disc_thread.unk80 = size;
        }

        archive->disc_thread.unk84 = (u32)buffer;
        archive->read_busy = 1;

        (void)archive->disc_thread.semaphore.wait();

        if (archive->disc_thread.unk5c)
        {
            (void)archive->disc_thread.semaphore.signal();
        }
        else
        {
            archive->disc_thread.unk5c = 1;
            (void)archive->disc_thread.semaphore.signal();
            (void)archive->disc_thread.unk10.signal();
        }
    }
    else
    {
        return 0;
    }

    return 1;
}

/**
 * @brief Start reading the selected resource without checking the result.
 * @param archive Resource archive.
 * @param buffer Destination.
 * @param size Bytes to read, or zero for the whole resource.
 */
void resident_archive_start_read_unchecked(ResidentArchive* archive, void* buffer, s32 size)
{
    resident_archive_start_read(archive, buffer, size);
}

/**
 * @brief Select the resource the next read loads: keep its position and size, and the install entry when unk12185
 * is set.
 * @param archive Resource archive.
 * @param key Resource key.
 * @return One when the resource was selected, or zero while a read is running.
 */
s32 resident_archive_select_resource(ResidentArchive* archive, s32 key)
{
    if (archive->read_busy)
    {
        return 0;
    }

    (void)archive->disc_thread.semaphore.wait();
    archive->disc_thread.unk98 = 0;
    (void)archive->disc_thread.semaphore.signal();

    archive->disc_thread.unk54 = archive->resource_positions[key] & 0x00FFFFFF;
    archive->unk12181 = 1;

    (void)archive->disc_thread.semaphore.wait();
    archive->disc_thread.unk68 = 0;
    (void)archive->disc_thread.semaphore.signal();

    if (archive->unk12185 && archive->install_flags[key] && key)
    {
        (void)archive->disc_thread.semaphore.wait();
        archive->disc_thread.unk61 = 1;
        (void)archive->disc_thread.semaphore.signal();
        archive->disc_thread.unk58 = archive->install_flags[key] - 1;
    }
    else
    {
        (void)archive->disc_thread.semaphore.wait();
        archive->disc_thread.unk61 = 0;
        (void)archive->disc_thread.semaphore.signal();
    }

    archive->disc_thread.unk80 = (archive->resource_entries[key] & 0x00FFFFFF) << 11;
    return 1;
}

/**
 * @brief Set the listener the archive notifies when a read finishes.
 * @param archive Resource archive.
 * @param listener Listener, or null to remove it.
 * @param context Object passed back to the listener.
 * @return The listener it replaces.
 */
ResidentListener* resident_archive_set_listener(ResidentArchive* archive, ResidentListener* listener, void* context)
{
    ResidentListener* previous;

    {
        ResidentSemaphoreLock lock(&archive->disc_thread.semaphore);
        previous = archive->disc_thread.listener;
    }

    (void)archive->disc_thread.semaphore.wait();
    archive->disc_thread.listener = listener;
    archive->disc_thread.listener_context = context;
    (void)archive->disc_thread.semaphore.signal();
    return previous;
}

/**
 * @brief Read and decrypt the archive's table of contents.
 * @param archive Resource archive.
 * @return One once the table is loaded, or zero while another read is running.
 */
s32 resident_archive_read_table(ResidentArchive* archive)
{
    if (archive->read_busy)
    {
        return 0;
    }

    sceCdDiskReady(0);
    archive->resource_positions[0] = RESIDENT_ARCHIVE_TOC_POSITION;
    resident_archive_select_resource(archive, 0);

    u32* buffer = new (0) u32[RESIDENT_ARCHIVE_TOC_WORDS];
    resident_archive_start_read(archive, buffer, RESIDENT_ARCHIVE_TOC_WORDS * sizeof(u32));

    while (archive->read_busy)
    {
    }

    u32* toc = archive->resource_positions;
    u32* source = buffer;

    for (s32 i = 0; i < RESIDENT_ARCHIVE_TOC_WORDS; i++)
    {
        *toc++ = *source++;
    }

    delete buffer;

    u32 key = RESIDENT_ARCHIVE_TOC_KEY;

    for (s32 i = 0; i < RESIDENT_RESOURCE_COUNT; i++)
    {
        archive->resource_positions[i] ^= key;
        key ^= key << 1;
        archive->resource_entries[i] ^= key;
        key = ~key ^ RESIDENT_ARCHIVE_TOC_KEY;
        archive->install_flags[i] ^= key;
        key ^= (key << 2) ^ RESIDENT_ARCHIVE_TOC_KEY;
    }

    archive->table_tag = archive->resource_positions[0];
    archive->resource_positions[0] = RESIDENT_ARCHIVE_TOC_POSITION;
    return 1;
}

/** @brief Destroy the archive and its threads. */
ResidentArchive::~ResidentArchive()
{
}

/**
 * @brief Install the disc power-off callback and start the hard disk worker, when the archive uses the hard disk.
 * @param archive Resource archive.
 */
void resident_archive_start_hard_disk(ResidentArchive* archive)
{
    if (archive->unk12184)
    {
        sceCdPOffCallback(resident_archive_on_power_off, &archive->unkD8);
        archive->worker.start();
    }
}

/**
 * @brief Read the clock.
 * @param archive Resource archive.
 * @param clock Receives the clock bytes.
 * @return Nonzero on success.
 */
s32 resident_archive_get_clock(ResidentArchive* archive, ResidentClock* clock)
{
    s32 result;

    (void)archive->disc_thread.semaphore.wait();
    clock->status = archive->disc_thread.unkAC.clock.status;
    clock->second = archive->disc_thread.unkAC.clock.second;
    clock->minute = archive->disc_thread.unkAC.clock.minute;
    clock->hour = archive->disc_thread.unkAC.clock.hour;
    clock->pad = archive->disc_thread.unkAC.clock.pad;
    clock->day = archive->disc_thread.unkAC.clock.day;
    clock->month = archive->disc_thread.unkAC.clock.month;
    clock->year = archive->disc_thread.unkAC.clock.year;
    result = archive->disc_thread.unkAC.unk14;
    (void)archive->disc_thread.semaphore.signal();
    return result;
}

/**
 * @brief Start the disc library in DVD mode with the archive's disc callback, and mark the archive's unk5F.
 * @param archive Resource archive.
 */
void resident_archive_start_disc(ResidentArchive* archive)
{
    sceCdInit(0);
    void* stack = malloc_guess(0x1000);
    sceCdInitEeCB(0x24, stack, 0x1000);
    archive->cd_callback_stack = stack;
    sceCdMmode(2);
    sceCdCallback(resident_disc_callback);
    archive->disc_thread.unk5f = 1;
    (void)archive->disc_thread.semaphore.wait();

    // The clock is copied out under the semaphore but never used.
    ResidentClock clock;
    clock.status = archive->disc_thread.unkAC.clock.status;
    clock.second = archive->disc_thread.unkAC.clock.second;
    clock.minute = archive->disc_thread.unkAC.clock.minute;
    clock.hour = archive->disc_thread.unkAC.clock.hour;
    clock.pad = archive->disc_thread.unkAC.clock.pad;
    clock.day = archive->disc_thread.unkAC.clock.day;
    clock.month = archive->disc_thread.unkAC.clock.month;
    clock.year = archive->disc_thread.unkAC.clock.year;
    (void)archive->disc_thread.semaphore.signal();
}

/** @brief Construct the archive's threads and start them. */
ResidentArchive::ResidentArchive()
{
    read_busy = 0;
    unk12180 = 0;
    table_tag = 0;
    unk12181 = 0;
    disc_thread.owner = this;
    disc_thread.start();
    unkD8.worker = &worker;
    unkD8.start();
    worker.archive = this;
    unk12184 = 0;
    main_thread_id = GetThreadId();
    unk12198 = 0;
    unk121a8 = 0;
    unk12185 = 0;
    unk12186 = 0;
    resident_debug_register_value(g_storage_status_name, (u8*)&read_busy, 1);
}
}
