#include "include_asm.h"
#include "main/resident_data.h"
#include "sdk/main/libdma_0012B2C8.h"
#include "sdk/main/libgraph_0012EAC8.h"
#include "sdk/main/libcdvd_00130000.h"
#include "sdk/main/libc_guess_00131D18.h"
#include "sdk/main/libc_guess_00137290.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "sdk/main/mslgcc_00142A40.h"
#include "vu0.h"
#include "main/debug.h"
#include "main/sif.h"
#include "main/sound_set.h"
#include "main/system.h"
#include "main/utility.h"

/** Object that reports running out of memory in place of the default message; null by default. */
class ResidentMemoryHook
{
public:
    /** @brief First virtual slot; nothing here calls it. */
    virtual void func_slot08();

    /**
     * @brief Report running out of memory.
     * @param data g_out_of_memory_data.
     */
    virtual void func_slot0c(void* data);
};

/** Startup state at g_startup_state: the out-of-memory hook, the output mode, and main's arguments. */
struct ResidentStartupState
{
    ResidentMemoryHook* hook;
    u8 progressive;
    s32 argc;
    char** argv;
};

/** A 16-byte vector that copies as one quadword. */
union ResidentVector
{
    unsigned __int128 qword;
    float f[4];
    u32 words[4];
};

/** End of the program image, where the C library heap starts. */
extern "C" u8 _end[];

/** Size of the main thread's stack; the linker passes it as an address. */
extern "C" u8 _stack_size[];

#define D0_CHCR (*(volatile u32*)0x10008000)
#define D0_QWC (*(volatile u32*)0x10008020)
#define D0_TADR (*(volatile u32*)0x10008030)
#define D_CTRL (*(volatile u32*)0x1000E000)

#define D_CTRL_DMA_ENABLE 0x1
#define D_CTRL_RELEASE_ENABLE 0x2
#define D_CTRL_RELEASE_CYCLE_256 0x500
#define D_CHCR_FROM_MEMORY 0x1
#define D_CHCR_CHAIN_MODE 0x4
#define D_CHCR_TRANSFER_TAG 0x40
#define D_CHCR_START 0x100
#define D_STAT_CHANNEL_0 0x1
#define RESIDENT_MEMORY_END 0x2000000

#define RESIDENT_MAIN_THREAD_PRIORITY 0x2D

extern "C" {
extern ResidentStartupState g_startup_state;
extern u8 g_out_of_memory_data[];
extern ResidentVector g_vu0_seed_vector;

/** "Memory exhaused.\n" */
extern const char g_out_of_memory_message[];

/** "cdrom0:\\IOPRP271.IMG;1" */
extern const char g_iop_image_path[];

/** "iop reset error\n" */
extern const char g_iop_reset_error_message[];

/** "-o" */
extern const char g_module_option_o[];

/** "-m" */
extern const char g_module_option_m[];

/** DMA chain that uploads the VU0 microcode. */
extern u8 g_vu0_microcode_chain[];

/** Every piece of music, by music number minus one. */
extern const ResidentMusicEntry g_music_table[];

/** Setup table main sends to the sound stream. */
extern const ResidentSoundSetupEntry g_sound_setup_table[];

extern u8 g_default_sound_bank_variants[];
}

/**
 * @brief Start the game: reset the IOP and load its modules, set up the GS, sound and input, then load the overlays
 * and run the first program.
 * @param argc Argument count.
 * @param argv Arguments.
 * @return Zero.
 */
int main(int argc, char** argv)
{
    ResidentArchive* archive;
    ResidentDecodeObject* decoder;
    ResidentResourceHeader* modules;
    ResidentResourceHeader* programs;
    ResidentResourceHeader* block;
    u8* buffer;
    u32 id;
    s32 i;
    void* iop;
    s32 j;
    s32 count;
    u8* blank;
    ResidentSound* sound;
    SifDmaTransfer transfer;
    GsLoadImage image;
    ResidentVector vector;
    ResidentVector* v;
    ResidentClock clock;

    resident_prime_heap();

    // Stack canary at the bottom of the stack ("gMtScFpT" in memory).
    *(u64*)(RESIDENT_MEMORY_END - (u32)_stack_size) = 0x5470466353744D67;
    TIMER0_MODE = TIMER_MODE_COUNT_ENABLE | TIMER_MODE_CLOCK_HBLANK;
    TIMER0_COUNT = 0;
    func_00142AE0();
    sceSifInitRpc(0);
    sceCdInit(0);
    sceCdMmode(2);

    while (!sceSifRebootIop(g_iop_image_path))
    {
        printf(g_iop_reset_error_message);
    }

    while (!sceSifSyncIop())
    {
    }

    sceSifInitRpc(0);
    sceSifLoadFileReset();
    sceFsReset();
    ChangeThreadPriority(GetThreadId(), RESIDENT_MAIN_THREAD_PRIORITY);
    archive = resident_get_archive(&g_system);
    resident_archive_start_disc(archive);
    sceSifInitIopHeap();
    resident_seed_random((TIMER0_COUNT + 1) * 0x9534C85 + 0xCAD);
    g_startup_state.argc = argc;
    g_startup_state.argv = argv;
    resident_archive_read_table(resident_get_archive(&g_system));
    decoder = resident_system_get_decoder(&g_system);
    resident_sif_start(&g_sif);

    modules = (ResidentResourceHeader*)memalign(0x40, 0x80000);
    FlushCache(0);
    resident_archive_select_resource(archive, 1);
    resident_archive_start_read_unchecked(archive, modules, 0);

    while (archive->read_busy)
    {
        resident_next_random_word();
    }

    programs = (ResidentResourceHeader*)memalign(0x40, 0x400000);
    FlushCache(0);
    resident_archive_select_resource(archive, 2);
    resident_archive_start_read_unchecked(archive, programs, 0);

    for (i = 0; i < 12; i++)
    {
        buffer = resident_allocate_decode_buffer(decoder, modules, i, 0);
        resident_decode_resource_block(decoder, modules, buffer, i);
        FlushCache(0);
        block = resident_find_resource_block(decoder, modules, i);
        iop = sceSifAllocIopHeap((block->decoded_size + 15) & ~15);
        transfer.data = buffer;
        transfer.address = iop;
        transfer.size = (block->decoded_size + 15) & ~15;
        transfer.mode = 0;
        id = sceSifSetDma(&transfer, 1);

        while (sceSifDmaStat(id) >= 0)
        {
        }

        if (i == 8)
        {
            if (resident_get_archive(&g_system)->unk12184)
            {
                s32 result;

                while (sceSifLoadStartModuleBuffer(iop, 11, g_module_option_o, &result) < 0)
                {
                }

                if (result == 1)
                {
                    resident_get_archive(&g_system)->unk12184 = 0;
                }
            }
        }
        else if (i == 9)
        {
            if (resident_get_archive(&g_system)->unk12184)
            {
                s32 result;

                while (sceSifLoadStartModuleBuffer(iop, 16, g_module_option_m, &result) < 0)
                {
                }

                if (result == 1)
                {
                    resident_get_archive(&g_system)->unk12184 = 0;
                }
            }
        }
        else
        {
            while (sceSifLoadModuleBuffer(iop, 0, 0) < 0)
            {
            }
        }

        sceSifFreeIopHeap(iop);
        delete buffer;
    }

    free_guess(modules);
    resident_debug_initialize();
    resident_archive_start_hard_disk(resident_get_archive(&g_system));
    sceSifInitRpc(0);
    func_001430D0(resident_handle_out_of_memory);
    sceGsResetPath();
    sceDmaReset(1);

    if (g_startup_state.progressive)
    {
        sceGsResetGraph(0, SCE_GS_NOINTERLACE, SCE_GS_DTV480P, SCE_GS_FRAME);
    }
    else
    {
        sceGsResetGraph(0, SCE_GS_INTERLACE, SCE_GS_NTSC, SCE_GS_FRAME);
    }

    resident_input_start(resident_system_get_input(&g_system));
    resident_system_save_stack(&g_system);
    resident_sync_gs_path(resident_system_get_input(&g_system), 0, 0);

    blank = new (0) u8[0x40000];
    memset_guess(blank, 0, 0x40000);

    for (s32 k = 0; k < 16; k++)
    {
        sceGsSetDefLoadImage(&image, k * 0x10000 / 64, 4, 0, 0, 0, 256, 256);
        FlushCache(0);
        sceGsExecLoadImage(&image, blank);
        resident_sync_gs_path(resident_system_get_input(&g_system), 0, 0);
    }

    delete blank;

    while (resident_sif_bind(&g_sif) < 0)
    {
        resident_next_random_word();
    }

    resident_sound_start(resident_system_get_sound(&g_system));
    resident_sound_send_setup(resident_system_get_sound(&g_system), 8, g_sound_setup_table);
    resident_sound_set_music_table(resident_system_get_sound(&g_system), 0x59, g_music_table);
    resident_sound_bank_set_install_variants(g_default_sound_bank_variants);

    while (archive->read_busy)
    {
        resident_next_random_word();
    }

    resident_sound_load_resource(resident_system_get_sound(&g_system), 0x40A);

    do
    {
        resident_next_random_word();
        resident_system_get_resource_queue(&g_system)->update();
        resident_input_wait_vblank(resident_system_get_input(&g_system), 0);
        sound = resident_system_get_sound(&g_system);
        resident_sound_update(sound, 0);
    } while (sound->state);

    // TODO: The original calls resident_set_program_running through a register and reads the input system right
    // before, without using it; a call through a cast pointer is the only form I've found that gives the jalr.
    resident_system_get_input(&g_system);
    ((void (*)(u8))resident_set_program_running)(1);

    D_CTRL = D_CTRL_RELEASE_CYCLE_256 | D_CTRL_RELEASE_ENABLE | D_CTRL_DMA_ENABLE;
    D0_QWC = 0;
    D0_TADR = (u32)g_vu0_microcode_chain;
    *D_STAT = D_STAT_CHANNEL_0;
    D0_CHCR = D_CHCR_START | D_CHCR_TRANSFER_TAG | D_CHCR_CHAIN_MODE | D_CHCR_FROM_MEMORY;

    while (!(*D_STAT & D_STAT_CHANNEL_0))
    {
    }

    *D_STAT = D_STAT_CHANNEL_0;

    v = &vector;
    resident_stream_read_iop_vector(resident_system_get_sound(&g_system)->stream, &v->words[0], &v->words[1], &v->words[2], &v->words[3]);
    vu0_run_microprogram_vf1_vf3(&vector);
    g_vu0_seed_vector.qword = vector.qword;

    resident_archive_get_clock(archive, &clock);
    count = (u8)(clock.hour + (clock.second + clock.minute));

    for (j = 0; j < count; j++)
    {
        resident_next_random_word();
    }

    for (j = 0;; j++)
    {
        ResidentResourceHeader* program = resident_find_resource_block(resident_system_get_decoder(&g_system), programs, j + 1);

        if (program == 0)
        {
            break;
        }

        resident_system_load_overlay(&g_system, program, j + 2);
    }

    resident_system_switch_program(&g_system, programs, 1);
    func_00142AC0();
    return 0;
}

/**
 * @brief Set g_program_running; main sets it once start-up is done, and boot and field set it while they run.
 * @param value New flag value.
 */
void resident_set_program_running(u8 value)
{
    g_program_running = value;
}

/** @brief The new handler main installs: report through the hook, or print a message and exit. */
void resident_handle_out_of_memory(void)
{
    if (g_startup_state.hook != 0)
    {
        g_startup_state.hook->func_slot0c(g_out_of_memory_data);
    }
    else
    {
        printf(g_out_of_memory_message);
        exit(1);
    }
}

/**
 * @brief Ignore a notification; the base class does nothing.
 * @param data Ignored.
 */
void ResidentListener::notify(void* data)
{
}

/**
 * @brief Allocate memory from the current heap, or from the default allocator when none is set.
 * @param size Number of bytes to allocate.
 * @param unused Second argument passed by callers; the resident implementation ignores it.
 * @return The allocated memory.
 */
void* operator new(u32 size, s32 unused)
{
    if (g_allocation_heap != 0)
    {
        return resident_heap_allocate(g_allocation_heap, size);
    }

    return ::operator new(size);
}

/**
 * @brief Allocate array memory from the current heap, or from the default allocator when none is set.
 * @param size Number of bytes to allocate.
 * @param unused Second argument passed by callers; the resident implementation ignores it.
 * @return The allocated memory.
 */
void* operator new[](u32 size, s32 unused)
{
    if (g_allocation_heap != 0)
    {
        return resident_heap_allocate(g_allocation_heap, size);
    }

    return ::operator new(size);
}

/**
 * @brief Release resident heap allocations or use the default free routine.
 * @param memory Allocation to release, or null.
 */
void operator delete(void* memory) throw()
{
    if (memory != 0)
    {
        ResidentAllocationHeader* header = (ResidentAllocationHeader*)((u8*)memory - 0x20);

        if (header->tag == 0x4D655279 && header->marker == 0x4058)
        {
            resident_heap_release(memory);
            return;
        }
        else
        {
            free_guess(memory);
        }
    }
}

/**
 * @brief Release resident heap arrays or use the default free routine.
 * @param memory Allocation to release, or null.
 */
void operator delete[](void* memory) throw()
{
    if (memory != 0)
    {
        ResidentAllocationHeader* header = (ResidentAllocationHeader*)((u8*)memory - 0x20);

        if (header->tag == 0x4D655279 && header->marker == 0x4058)
        {
            resident_heap_release(memory);
            return;
        }
        else
        {
            free_guess(memory);
        }
    }
}

/**
 * @brief Exchange the heap selected for resident new allocations.
 * @param heap New heap, or null for the default allocator.
 * @return Previous heap.
 */
void* resident_exchange_allocation_heap(void* heap)
{
    void* previous = g_allocation_heap;
    g_allocation_heap = heap;
    return previous;
}

/**
 * @brief Read the heap selected for resident new allocations.
 * @return Current heap, or null for the default allocator.
 */
void* resident_get_allocation_heap(void)
{
    return g_allocation_heap;
}

/**
 * @brief Allocate and free all memory between the program and the stack, so the C library claims it in one block.
 * @return Size of the block.
 */
u32 resident_prime_heap(void)
{
    u32 stack = (u32)_stack_size + 0x1000;
    u32 size = RESIDENT_MEMORY_END - ((u32)_end + stack + 0x1000);
    free_guess(malloc_guess(size - 0x10));
    return size - 0x10;
}

/** @brief Destroy every part of the system. */
ResidentSystem::~ResidentSystem()
{
}
