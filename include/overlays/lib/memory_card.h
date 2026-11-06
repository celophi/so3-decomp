#ifndef SO3_OVERLAYS_LIB_MEMORY_CARD_H
#define SO3_OVERLAYS_LIB_MEMORY_CARD_H

#include "types.h"
#include "overlays/lib/text_003E68C0.h"
#include "overlays/lib/text_004CD3A0.h"

/** Memory card slots a card object serves. */
#define LIB_MEMORY_CARD_SLOT_COUNT 2

/** LibMemoryCardSlot::state_flags bit set once the slot is opened. */
#define LIB_MEMORY_CARD_SLOT_OPEN 0x2

/** LibMemoryCardSlot::card_state once the card in the slot is ready. */
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

/** Bits of a slot status that give its group. */
#define LIB_MEMORY_CARD_STATUS_GROUP_MASK 0xF8

/** Status group of an operation that finished with a result to read. */
#define LIB_MEMORY_CARD_STATUS_DONE 0x10

/** Partial 0x100-byte record the memory card object keeps per slot. */
struct LibMemoryCardSlot
{
    u8 unk00[0x40];

    /** Set when the slot is opened: bit 4 and bits 0-1 come from the open call. */
    u16 config;

    /** LIB_MEMORY_CARD_SLOT_OPEN once the slot is opened. */
    u16 state_flags;

    u16 unk44;

    /** Status of the last operation; zero or 0x10-0x17 once it can be read. */
    u8 status;

    /** Nonzero while an operation is running. */
    u8 busy;

    /** Card state; two once the card is ready. */
    s32 card_state;

    /** Free space. */
    s32 free_space;

    /** Nonzero when the card is formatted. */
    s32 formatted;

    /** Result of the last operation. */
    s32 result;

    u8 unk58[4];

    /** File request the running transfer works through. */
    struct LibCardFileRequest* request;

    u8 unk60[0x14];

    /** Buffer a file probe reads into, aligned to 64 bytes. */
    u8* buffer;

    s32 unk78;
    s32 unk7C;

    /** File a probe looks for. */
    char name[0x40];

    u8 unkC0[0x40];
};

/** Partial 0x58-byte memory card object that runs the two transfer modes. */
class LibMemoryCard : public LibListObject
{
    public:
        /** @brief Initialize the memory card object. */
        LibMemoryCard();

        /** @brief Destroy the memory card object. */
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

        /** The two card slots. */
        LibMemoryCardSlot* slots;

        /** Static storage the slot records are carved from. */
        u8* slot_storage;

        /** Set once the card library is set up. */
        u8 initialized : 1;

        u8 unk1c_bits : 7;

        u8 unk1d;
        u16 unk1e;

        /** Zero while the card object is busy. */
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

/** One file of a memory card request: Lib opens `<directory>/<name>` and transfers size bytes at data. */
struct LibCardFileBuffer
{
    char* name;
    void* data;
    u32 size;
    u32 unk0C;
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
