#ifndef SO3_OVERLAYS_LIB_MEMORY_CARD_H
#define SO3_OVERLAYS_LIB_MEMORY_CARD_H

#include "types.h"
#include "overlays/lib/text_003E68C0.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/semaphore.h"
#include "main/thread.h"

#define LIB_MEMORY_CARD_SLOT_COUNT 2
#define LIB_MEMORY_CARD_SLOT_OPEN 0x2
#define LIB_MEMORY_CARD_STATE_READY 2

/** Operation codes written to a slot's status (or busy byte when it's already running one). */
enum LibMemoryCardOperation
{
    LIB_MEMORY_CARD_OP_20 = 0x20,
    LIB_MEMORY_CARD_OP_TRANSFER = 0x30,
    LIB_MEMORY_CARD_OP_40 = 0x40,
    LIB_MEMORY_CARD_OP_PROBE_FILE = 0x60,
    LIB_MEMORY_CARD_OP_C0 = 0xC0
};

#define LIB_MEMORY_CARD_STATUS_GROUP_MASK 0xF8
#define LIB_MEMORY_CARD_STATUS_DONE 0x10

/** Partial 0x100-byte record the memory card object keeps per slot. */
struct LibMemoryCardSlot
{
    u8 unk00[0x40];
    u16 config;
    u16 state_flags;
    u16 unk44;
    u8 status;
    u8 busy;
    s32 card_state;
    s32 free_space;
    s32 formatted;
    s32 result;
    s32 fd;
    struct LibCardFileRequest* request;
    u8 unk60[0x14];
    u8* buffer;
    s32 unk78;
    s32 unk7C;
    char name[0x40];
    u8 unkC0[0x40];
};

/** Thread with a semaphore, with vtable D_173580 in main data; it sits next to the memory card code. */
class LibClass173580 : public ResidentThread
{
public:
    virtual ~LibClass173580();

    /** @brief Thread body. */
    virtual void run();

    u8 unk10[0xC];
    LibSemaphore semaphore;
};

/** Partial 0x58-byte memory card object that runs the two transfer modes. */
class LibMemoryCard : public LibListObject
{
    public:
        /** @brief Initialize the memory card object. */
        LibMemoryCard();

        virtual ~LibMemoryCard();

        /** @brief Wait for the card command in progress, then detach and queue the object once the library is set up. */
        virtual void destroy();

        /** @brief Run the transfer state machine. */
        virtual void update();

        /**
         * @brief Virtual slot 0x1C, first after LibListObject's.
         * @return Always four.
         */
        virtual s32 func_slot1C();

        LibMemoryCardSlot* slots;
        u8* slot_storage;
        u8 initialized : 1;
        u8 unk1c_bits : 7;

        u8 unk1d;
        u16 unk1e;
        u8 ready;
        u8 unk21[3];
        u32 unk24;
        u8 unk28;
        u8 unk29[3];
        s32 unk2c[10];
        s32 unk54;
};

enum LibCardSlotMask
{
    LIB_CARD_SLOT_1 = 0x1,
    LIB_CARD_SLOT_2 = 0x2
};

/** One entry of a memory card directory listing (Sony's sceMcTblGetDir). */
struct LibCardDirectoryEntry
{
    u8 created[8];
    u8 modified[8];
    u32 size;
    u16 attributes;
    u16 unk16;
    u32 unk18;
    u32 application_number;
    char name[32];
};

/** Contents of a save's icon.sys file (Sony's sceMcIconSys). */
struct LibIconSys
{
    char magic[4];
    u16 unk04;
    u16 title_line_offset;
    u32 unk08;
    u32 background_alpha;
    s32 background_colors[4][4];
    float light_directions[3][4];
    float light_colors[3][4];
    float ambient_color[4];
    char title[0x44];
    char list_icon[0x40];
    char copy_icon[0x40];
    char delete_icon[0x40];
    u8 unk1c4[0x200];
};

/** One file of a memory card request: Lib opens `<directory>/<name>` and transfers size bytes at data. */

struct LibCardFileBuffer
{
    char* name;
    void* data;
    u32 size;
    s32 offset;
};

/** Memory card request for files in one directory; Lib keeps a pointer to it in the slot until it finishes. */
struct LibCardFileRequest
{
    char* directory;
    s32 file_count;
    u32 unk08;
    LibCardFileBuffer* files;
};

extern "C"
{
    /**
     * @brief Read the result of a slot's last operation.
     * @param card Memory card object.
     * @param slot Slot index.
     * @param result Receives the result when one is ready; cleared first. May be null.
     * @return 1 with a result, 0 while the slot is busy or its status has no result, -1 when the card library isn't
     *         set up or the slot doesn't exist.
     */
    s32 lib_memory_card_get_result(LibMemoryCard* card, s32 slot, s32* result);

    /**
     * @brief Start looking for a file on the card in a slot.
     * @param card Memory card object.
     * @param slot Slot index.
     * @param name File to look for.
     * @param unk7C Stored in the slot at 0x7C.
     * @param unk78 Stored in the slot at 0x78.
     * @param buffer Buffer the probe reads into; it is aligned to 64 bytes first.
     * @return 0 once started, -1 when the slot can't start an operation.
     */
    s32 lib_memory_card_probe_file(LibMemoryCard* card, u32 slot, const char* name, s32 unk7C, s32 unk78, u8* buffer);

    /**
     * @brief Start a file transfer on the card in a slot.
     * @param card Memory card object.
     * @param slot Slot index.
     * @param request Files to transfer; the slot keeps the pointer until it finishes.
     * @return 0 once started, -1 when the slot can't start an operation.
     */
    s32 lib_memory_card_start_transfer(LibMemoryCard* card, u32 slot, LibCardFileRequest* request);

    /**
     * @brief Open a slot that isn't running anything: clear its record and mark it open.
     * @param card Memory card object.
     * @param slot Slot index.
     * @param enabled Low bit goes to bit 4 of the slot's config.
     * @param flags Low two bits go to bits 0-1 of the slot's config.
     */
    void lib_memory_card_open_slot(LibMemoryCard* card, s32 slot, u32 enabled, u32 flags);

    /**
     * @brief Set up the card library and the slot records, then add the card to an update list.
     * @param card Memory card object.
     * @param list List to add the card to, or null.
     * @return 1 once set up, 0 when it already was or the card library failed to start.
     */
    s32 lib_memory_card_init(LibMemoryCard* card, LibUpdateList* list);

    /**
     * @brief Set unk54 and every unk2c entry to -1.
     * @param card Memory card object.
     */
    void func_00431730(LibMemoryCard* card);

    /**
     * @brief Read an unk2c entry.
     * @param card Memory card object.
     * @param index Entry index; the check lets 10 through, which reads unk54.
     * @return The entry, or -1 when the index is out of range.
     */
    s32 func_00431770(LibMemoryCard* card, s32 index);

    /**
     * @brief Store a value from 0 to 10 in unk54.
     * @param card Memory card object.
     * @param value Value to store.
     * @return 1 once stored, 0 when the value is out of range.
     */
    s32 func_004317B0(LibMemoryCard* card, s32 value);

    /**
     * @brief Start operation 0xC0 on the card in a slot for a named file.
     * @param card Memory card object.
     * @param slot Slot index.
     * @param name File name, copied into the slot.
     * @param unk78 Stored in the slot at 0x78.
     * @param buffer Stored as the slot's buffer, without aligning it.
     * @return 0 once started, -1 when the slot can't start an operation.
     */
    s32 func_004323E0(LibMemoryCard* card, u32 slot, const char* name, s32 unk78, u8* buffer);

    /**
     * @brief Start operation 0x40 on the card in a slot for a file request.
     * @param card Memory card object.
     * @param slot Slot index.
     * @param request Files to work on; the slot keeps the pointer until it finishes.
     * @return 0 once started, -1 when the slot can't start an operation.
     */
    s32 func_004324D0(LibMemoryCard* card, u32 slot, LibCardFileRequest* request);

    /**
     * @brief Start operation 0x20 on the card in a slot.
     * @param card Memory card object.
     * @param slot Slot index.
     * @return 0 once started, -1 when the slot can't start an operation.
     */
    s32 func_004325A0(LibMemoryCard* card, u32 slot);
}

#endif
