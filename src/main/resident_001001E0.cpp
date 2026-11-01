#include "include_asm.h"
#include "main/resident_001001E0.h"
#include "main/resident_00101260.h"
#include "main/resident_0010A0E0.h"
#include "main/resident_0011EE70.h"
#include "main/resident_00121730.h"
#include "sdk/main/libkernl_00121940.h"
#include "sdk/main/libdma_0012B2C8.h"
#include "sdk/main/libgraph_0012EAC8.h"
#include "sdk/main/libcdvd_00130000.h"
#include "sdk/main/libc_guess_00131D18.h"
#include "sdk/main/libc_guess_00137290.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "sdk/main/mslgcc_00142A40.h"
#include "vu0.h"

extern u8 D_001B6420;

/** Object that reports running out of memory in place of the default message; null by default. */
class ResidentMemoryHook
{
public:
    virtual void func_slot08();

    /** @brief Report running out of memory. @param data D_001CC510. */
    virtual void func_slot0c(void* data);
};

/** Startup state at g_startup_state: the out-of-memory hook, the output mode, and main's arguments. */
struct ResidentStartupState
{
    ResidentMemoryHook* hook;

    /** Nonzero to start in progressive (525p) output. */
    u8 progressive;

    s32 argc;
    char** argv;
};

/** A 16-byte vector that copies as one quadword. */
union ResidentVector
{
    unsigned __int128 qword;
    float f[4];
};

/** End of the program image, where the C library heap starts. */
extern "C" u8 _end[];

/** Size of the main thread's stack; the linker passes it as an address. */
extern "C" u8 _stack_size[];

#define TIMER0_COUNT (*(volatile u32*)0x10000000)
#define TIMER0_MODE (*(volatile u32*)0x10000010)
#define D0_CHCR (*(volatile u32*)0x10008000)
#define D0_QWC (*(volatile u32*)0x10008020)
#define D0_TADR (*(volatile u32*)0x10008030)
#define D_CTRL (*(volatile u32*)0x1000E000)
#define D_STAT (*(volatile u32*)0x1000E010)

extern "C" {
extern ResidentStartupState g_startup_state;
extern u8 D_001CC510[];
extern ResidentVector D_001CC530;
extern u8 D_001CC590[];

/** "Memory exhaused.\n" */
extern const char D_0014D660[];

/** "cdrom0:\\IOPRP271.IMG;1" */
extern const char D_0014D640[];

/** "iop reset error\n" */
extern const char D_0014D620[];

/** "-o" */
extern const char D_0014D600[];

/** "-m" */
extern const char D_0014D610[];

/** DMA chain that uploads the VU0 microcode. */
extern u8 D_00143B80[];

extern u8 D_00143C00[];
extern u8 D_00143D70[];
extern u8 D_00144130[];

void func_0010D100(u32 seed);
void func_0011DA80(ResidentArchive* archive);
void func_0011D470(ResidentArchive* archive);
void func_0011D080(ResidentArchive* archive, s32 mode);
void func_0011D950(ResidentArchive* archive);
void func_0010C700(void* object);
s32 func_0010C640(void* object);
void func_0011EA80(ResidentInputSystem* input);
void func_00112D80(ResidentSound* sound);
void func_0010EC00(ResidentSound* sound, s32 count, const void* data);
void func_0010EAD0(ResidentSound* sound, s32 value);
void func_0010F250(ResidentSound* sound, s32 mode);
void func_001058C0(ResidentSoundStream* stream, float* x, float* y, float* z, float* w);
}

/** @brief The new handler main installs: report through the hook, or print a message and exit. */
void resident_handle_out_of_memory(void);

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
    *(u64*)(0x2000000 - (u32)_stack_size) = 0x5470466353744D67;
    TIMER0_MODE = 0x83;
    TIMER0_COUNT = 0;
    func_00142AE0();
    sceSifInitRpc(0);
    sceCdInit(0);
    sceCdMmode(2);

    while (!sceSifRebootIop(D_0014D640))
    {
        printf(D_0014D620);
    }

    while (!sceSifSyncIop())
    {
    }

    sceSifInitRpc(0);
    sceSifLoadFileReset();
    sceFsReset();
    ChangeThreadPriority(GetThreadId(), 0x2D);
    archive = resident_get_archive(&g_system);
    func_0011DA80(archive);
    sceSifInitIopHeap();
    func_0010D100((TIMER0_COUNT + 1) * 0x9534C85 + 0xCAD);
    g_startup_state.argc = argc;
    g_startup_state.argv = argv;
    func_0011D470(resident_get_archive(&g_system));
    decoder = func_001012B0(&g_system);
    func_0010C700(D_001CC590);

    modules = (ResidentResourceHeader*)memalign(0x40, 0x80000);
    FlushCache(0);
    func_0011D080(archive, 1);
    func_0011D060(archive, modules, 0);

    while (archive->unk12183)
    {
        resident_next_random_word();
    }

    programs = (ResidentResourceHeader*)memalign(0x40, 0x400000);
    FlushCache(0);
    func_0011D080(archive, 2);
    func_0011D060(archive, programs, 0);

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

                while (sceSifLoadStartModuleBuffer(iop, 11, D_0014D600, &result) < 0)
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

                while (sceSifLoadStartModuleBuffer(iop, 16, D_0014D610, &result) < 0)
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
    func_00121870();
    func_0011D950(resident_get_archive(&g_system));
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

    func_0011EA80(func_001012D0(&g_system));
    resident_system_save_stack(&g_system);
    func_0011DE00(func_001012D0(&g_system), 0, 0);

    blank = new (0) u8[0x40000];
    memset_guess(blank, 0, 0x40000);

    for (s32 k = 0; k < 16; k++)
    {
        sceGsSetDefLoadImage(&image, k * 0x10000 / 64, 4, 0, 0, 0, 256, 256);
        FlushCache(0);
        sceGsExecLoadImage(&image, blank);
        func_0011DE00(func_001012D0(&g_system), 0, 0);
    }

    delete blank;

    while (func_0010C640(D_001CC590) < 0)
    {
        resident_next_random_word();
    }

    func_00112D80(func_00101270(&g_system));
    func_0010EC00(func_00101270(&g_system), 8, D_00143D70);
    func_00112D70(func_00101270(&g_system), 0x59, D_00143C00);
    func_00120360(D_00144130);

    while (archive->unk12183)
    {
        resident_next_random_word();
    }

    func_0010EAD0(func_00101270(&g_system), 0x40A);

    do
    {
        resident_next_random_word();
        func_00101250(&g_system)->func_00104770();
        func_0011DF10(func_001012D0(&g_system), 0);
        sound = func_00101270(&g_system);
        func_0010F250(sound, 0);
    } while (sound->state);

    // TODO: The original calls func_00100A40 through a register and reads the input system right before, without
    // using it; a call through a cast pointer is the only form I've found that gives the jalr.
    func_001012D0(&g_system);
    ((void (*)(u8))func_00100A40)(1);

    D_CTRL = 0x503;
    D0_QWC = 0;
    D0_TADR = (u32)D_00143B80;
    D_STAT = 1;
    D0_CHCR = 0x145;

    while (!(D_STAT & 1))
    {
    }

    D_STAT = 1;

    v = &vector;
    func_001058C0(func_00101270(&g_system)->stream, &v->f[0], &v->f[1], &v->f[2], &v->f[3]);
    vu0_run_microprogram_vf1_vf3(&vector);
    D_001CC530.qword = vector.qword;

    resident_archive_get_clock(archive, &clock);
    count = (u8)(clock.hour + (clock.second + clock.minute));

    for (j = 0; j < count; j++)
    {
        resident_next_random_word();
    }

    for (j = 0;; j++)
    {
        ResidentResourceHeader* program = resident_find_resource_block(func_001012B0(&g_system), programs, j + 1);

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


void func_00100A40(u8 value)
{
    D_001B6420 = value;
}

/** @brief The new handler main installs: report through the hook, or print a message and exit. */
void resident_handle_out_of_memory(void)
{
    if (g_startup_state.hook != 0)
    {
        g_startup_state.hook->func_slot0c(D_001CC510);
    }
    else
    {
        printf(D_0014D660);
        exit(1);
    }
}

void func_00100AB0(void* object)
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
    u32 size = 0x2000000 - ((u32)_end + stack + 0x1000);
    free_guess(malloc_guess(size - 0x10));
    return size - 0x10;
}

/** @brief Destroy every part of the system. */
ResidentSystem::~ResidentSystem()
{
}

/**
 * @brief Allocate the system's status byte at a random heap address and mark it clean.
 * @param system Resident system.
 */
void resident_system_create_status(ResidentSystem* system)
{
    // Never freed; it only moves the status byte to a different address on each boot.
    new (0) u8[(resident_rand() & 0x3FF) + 0x40];
    system->status = new (0) u8[0x10];
    *system->status = 0x66;
}

/**
 * @brief Set an alarm from interrupt context, doubling the time in progressive mode so it lasts as long as in
 * interlaced mode.
 * @param system Resident system.
 * @param time Horizontal syncs to wait in interlaced mode.
 * @param handler Handler to call from interrupt context.
 * @param common Argument passed to the handler.
 * @return Alarm ID, or a negative value on failure.
 */
s32 resident_system_iset_alarm(ResidentSystem* system, u16 time, KernelAlarmHandler handler, void* common)
{
    if (system->progressive)
    {
        time *= 2;
    }
    return iSetAlarm(time, handler, common);
}

/**
 * @brief Set an alarm, doubling the time in progressive mode so it lasts as long as in interlaced mode.
 * @param system Resident system.
 * @param time Horizontal syncs to wait in interlaced mode.
 * @param handler Handler to call from interrupt context.
 * @param common Argument passed to the handler.
 * @return Alarm ID, or a negative value on failure.
 */
s32 resident_system_set_alarm(ResidentSystem* system, u16 time, KernelAlarmHandler handler, void* common)
{
    if (system->progressive)
    {
        time *= 2;
    }
    return SetAlarm(time, handler, common);
}

/**
 * @brief Set progressive (525p) or interlaced output and reset the GS to match.
 * @param system Resident system.
 * @param progressive Nonzero for progressive output.
 */
void resident_system_set_progressive(ResidentSystem* system, u8 progressive)
{
    system->progressive = progressive;

    if (progressive)
    {
        sceGsResetGraph(0, SCE_GS_NOINTERLACE, SCE_GS_DTV480P, SCE_GS_FRAME);
    }
    else
    {
        sceGsResetGraph(0, SCE_GS_INTERLACE, SCE_GS_NTSC, SCE_GS_FRAME);
    }
}

/**
 * @brief Save main's stack and frame pointers, so each program can start from main's stack depth.
 * TODO: Come back to this, and figure out if the compiler can express this somehow.
 * @param system Resident system.
 */
void resident_system_save_stack(ResidentSystem* system)
{
    void** sp_slot = &system->saved_sp;
    void** fp_slot = &system->saved_fp;

    asm("sw $sp, 0(%0)" : : "r"(sp_slot));
    asm("sw $fp, 0(%0)" : : "r"(fp_slot));
}

/** Load address of the overlay in each slot, or null for an empty slot. */
extern "C" void* D_001B5FB0[];

/**
 * @brief Decode an overlay into its slot and delete the loaded resource, then go back to main's stack depth and run
 * the new program, which never returns.
 * TODO: Same as resident_system_save_stack; the stack reset matches, but I want to dig into how the original did it.
 * @param system Resident system.
 * @param source Loaded, compressed overlay resource; switching deletes it.
 * @param slot Slot in the resident overlay table D_001B5FB0.
 */
void resident_system_switch_program(ResidentSystem* system, ResidentResourceHeader* source, s32 slot)
{
    void* overlay = D_001B5FB0[slot];
    u32 size;

    if (overlay != 0)
    {
        resident_decode_resource_block(&system->decoder, source, overlay, 0);
        size = source->decoded_size;
        delete source;
        FlushCache(0);
        mwOverlayInit(overlay, size);
        FlushCache(2);
    }

    void** sp_slot = &system->saved_sp;
    void** fp_slot = &system->saved_fp;

    asm("lw $sp, 0(%0)" : : "r"(sp_slot));
    asm("lw $fp, 0(%0)" : : "r"(fp_slot));
    g_current_program->run();
}

/**
 * @brief Clear a decoded overlay's BSS and run its static initializers.
 * @param system Resident system.
 * @param overlay Decoded overlay image.
 * @param slot The overlay's slot in the resident overlay table D_001B5FB0.
 * @param size Decoded size of the overlay image; its BSS follows it.
 */
void resident_system_init_overlay(ResidentSystem* system, void* overlay, s32 slot, u32 size)
{
    mwOverlayInit(overlay, size);
}

/**
 * @brief Decode an overlay into its slot and run its static initializers.
 * @param system Resident system.
 * @param source Loaded, compressed overlay resource.
 * @param slot Slot in the resident overlay table D_001B5FB0.
 */
void resident_system_load_overlay(ResidentSystem* system, ResidentResourceHeader* source, s32 slot)
{
    u32 size;
    void* overlay = D_001B5FB0[slot];

    if (overlay != 0)
    {
        resident_decode_resource_block(&system->decoder, source, overlay, 0);
        size = source->decoded_size;
        FlushCache(0);
        mwOverlayInit(overlay, size);
        FlushCache(2);
    }
}
