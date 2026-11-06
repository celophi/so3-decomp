#ifndef SO3_OVERLAYS_BOOT_TROPHY_CARD_H
#define SO3_OVERLAYS_BOOT_TROPHY_CARD_H

#include "overlays/boot/boot.h"

#define BOOT_TRANSFER_NAME_CAPACITY 64

/** Mask used to align memory card query buffers to 64 bytes. */
#define BOOT_CARD_QUERY_ALIGNMENT_MASK 0x3F

#define BOOT_ALIGN_CARD_QUERY(value) (((u32)(value) + BOOT_CARD_QUERY_ALIGNMENT_MASK) & ~BOOT_CARD_QUERY_ALIGNMENT_MASK)

/** Card checks and file probes performed before a Battle Trophy transfer. */
enum BootTrophyCardStep
{
    BOOT_TROPHY_CARD_UNINITIALIZED = -1,
    BOOT_TROPHY_CARD_IDLE = 0,
    BOOT_TROPHY_CARD_INSPECT_SLOT,
    BOOT_TROPHY_CARD_PROBE_SAVE,
    BOOT_TROPHY_CARD_WAIT_SAVE_PROBE,
    BOOT_TROPHY_CARD_PROBE_TROPHIES,
    BOOT_TROPHY_CARD_WAIT_TROPHY_PROBE,
    BOOT_TROPHY_CARD_TRANSFER = 8
};

/** Phases of a Battle Trophy memory card file request. */
enum BootTrophyTransferPhase
{
    BOOT_TROPHY_TRANSFER_INACTIVE = -1,
    BOOT_TROPHY_TRANSFER_OPEN,
    BOOT_TROPHY_TRANSFER_POLL
};

/** Free-space limits used when classifying memory card save and trophy capacity. */
enum BootCardFreeSpace
{
    BOOT_CARD_SAVE_SPACE_MINIMUM = 175,
    BOOT_CARD_TROPHY_SPACE_MINIMUM = 1200,
    BOOT_CARD_BOTH_SPACE_MINIMUM = BOOT_CARD_SAVE_SPACE_MINIMUM + BOOT_CARD_TROPHY_SPACE_MINIMUM,
    BOOT_CARD_MAX_EXPECTED_SPACE = 8000
};

/**
 * Battle Trophies memory card file (BASLUS-20488BTLCOL), with vtable D_170EB0 in main data. It reads and writes the
 * file through a Lib memory card object and reports each slot's free-space state for the startup checks. Mode 0
 * and mode 1 select the two card slots.
 */
class BootBattleTrophyCard : public LibListObject
{
    public:
        /** @brief Clear the transfer state, both modes, and the filename. */
        BootBattleTrophyCard();

        /** @brief Destroy the object. */
        virtual ~BootBattleTrophyCard();

        /**
         * @brief Report the list kind used when registration requests the default.
         * @return Two.
         */
        virtual s32 get_default_list_kind();

        /** @brief Release the transfer buffer and the memory card object, then queue this object for deletion. */
        virtual void destroy();

        /** @brief Advance the memory card state for the current mode. */
        virtual void update();

        /**
         * @brief Report which card slots hold a ready card.
         * @return Bit 0 for slot 1 and bit 1 for slot 2; zero while the card object is busy.
         */
        u16 get_ready_slots();

        /** @brief Apply transferred flags and header values, copy the payload, and release its buffer. */
        void finish_transfer();

        /**
         * @brief Return the last transfer's result.
         * @return Result code; negative on failure.
         */
        s32 get_transfer_result();

        /**
         * @brief Return the transfer state.
         * @return 1 once the transfer has finished, -1 while it runs or after a reset.
         */
        s16 get_transfer_state();

        /**
         * @brief Advance the stored two-phase request and update its completion state.
         * @return Narrowed request status, or -1 when the phase is unsupported.
         */
        s16 advance_transfer();

        /**
         * @brief Initialize the buffer and request records for a selected transfer mode.
         * @param mode Transfer mode 0 or 1.
         * @param destination Nonnull destination for the transfer.
         * @return 1 when prepared, or 0 for invalid arguments or allocation failure.
         */
        s32 start_transfer(u16 mode, void* destination);

        /**
         * @brief Store mode 1 or 2 and reset the state for selector 0.
         * @param mode Mode to store; values other than 1 or 2 have no effect.
         */
        void set_mode(u8 mode);

        /**
         * @brief Query a slot's state byte, resetting slot 0 when its reset flag is set.
         * @param mode Slot 0 or 1 to query; other values return zero without a reset.
         * @param kind Select guarded values with 1, or the direct mode byte otherwise.
         * @return The selected byte before any reset.
         */
        u16 get_slot_state(u16 mode, u16 kind);

        /**
         * @brief Apply an event to the selected mode and update its reset and completion flags.
         * @param enabled Process the event when this byte equals 1.
         * @param event Event code or direct byte status to store.
         * @param kind Classify the event with 1, or store its byte status with 2.
         */
        void handle_card_event(u8 enabled, u16 event, u16 kind);

        /**
         * @brief Select an event's byte status and update the current mode's stored status.
         * @param event Event code to classify.
         * @param result Byte receiving the selected status, initially cleared to zero.
         */
        void classify_card_event(u16 event, u8* result);

        /**
         * @brief Select a slot and reset its fields along with the shared state.
         * @param mode Slot 0 or 1 to select; other values reset only the shared state.
         */
        void reset_slot(s16 mode);

        /**
         * @brief Create the memory card object for both slots and prepare the transfer buffer.
         * @return 1 when initialized, or 0 when the card object, settings or buffer is unavailable.
         */
        s32 initialize();

        LibMemoryCard* card;

        /** Selected slot, or -1. */
        s16 slot;

        /** Card status last read for the selected slot; a change restarts card_step. */
        s16 last_card_status;

        /** Step of update()'s card state machine; 0 is idle, 8 runs the transfer. */
        s16 card_step;

        /** Skip polling the selected card while a slot result awaits consumption. */
        u8 card_poll_paused;
        u8 unk1F;

        /** Copy of the slot's formatted flag from the last check. */
        u32 card_formatted;

        s32 free_space;
        /** Reset slot 0 after a caller reads a pending slot result. */
        u8 pending_slot_reset;
        u8 slot1_status_valid;
        u8 slot2_status_valid;
        u8 slot1_status;
        u8 slot2_status;

        /** Set when the slot had under 175 units free. */
        u8 low_space;

        char filename[BOOT_TRANSFER_NAME_CAPACITY];
        /** Backing storage for the general save-file card query. */
        u8 save_file_probe_storage[0xCC0];

        /** 64-byte-aligned pointer into save_file_probe_storage. */
        u8* save_file_probe_buffer;
        u8 card_mode;
        /** Whether each direct mode status has been set. */
        u8 mode_status_valid[2];

        /** Direct status returned by get_slot_state for each mode. */
        u8 mode_status[2];
        /** Backing storage for the Battle Trophies file query. */
        u8 trophy_file_probe_storage[0x80];

        /** 64-byte-aligned pointer into trophy_file_probe_storage. */
        u8* trophy_file_probe_buffer;
        s16 transfer_phase;
        u8* transfer_buffer;
        void* transfer_destination;
        s16 transfer_slot;

        /** 1 once the transfer has finished, -1 while it runs or after a reset. */
        s16 transfer_state;

        s32 transfer_result;
        LibCardFileBuffer file_buffer;
        LibCardFileRequest file_request;
        LibSystemSettings* settings;

        /** Set by start_transfer until the transfer finishes or fails. */
        u8 transfer_pending;

        /** Set once the card file has been opened for the transfer. */
        u8 transfer_open;

        s32 slot_free_space[2];
        /** Save-file probe status used when classifying each slot. */
        s32 save_probe_status[2];
};

/** Product code at the start of every save name: "BASLUS-20488". */
extern const char g_card_product_code[];

/** Save name suffix of the battle trophy file: "BTLCOL". */
extern const char g_trophy_file_suffix[];

/** Suffix that matches any of the game's saves: "-*". */
extern const char g_any_file_suffix[];

#endif
