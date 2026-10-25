#ifndef SO3_OVERLAYS_1067_00_TEXT_002CEAF0_H
#define SO3_OVERLAYS_1067_00_TEXT_002CEAF0_H

#include "types.h"

/** Runtime window directory containing a deferred-removal list. */
typedef struct FieldWindowRemovalContext FieldWindowRemovalContext;
#ifdef __cplusplus
class FieldClass15AE70;
#else
typedef struct FieldClass15AE70 FieldClass15AE70;
#endif

/** Partial receiver containing 64 allocations and three aligned buffer slots. */
typedef struct FieldBufferSlots
{
    u8 unk00[0x14];
    void* allocations[64];
    void* block_chain_allocation;
    s32 block_chain_size;
    void* buffer_allocations[3];
    void* aligned_buffers[3];
    s32 buffer_sizes[3];
    u8 unk140;
} FieldBufferSlots;

/** Partial header of a resource record linked by a byte offset. */
typedef struct FieldResourceRecord
{
    u8 unk00[8];
    u32 unk08;
    u32 next_offset;
} FieldResourceRecord;

typedef struct FieldMenuManager FieldMenuManager;

#ifdef __cplusplus
#include "overlays/1067-00/text_001DD3C0.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Queue a non-null window for removal by the runtime update.
 * @param context Runtime window directory.
 * @param window Window to remove after the current update.
 */
void field_queue_window_removal(FieldWindowRemovalContext* context, FieldClass15AE70* window);

#ifdef __cplusplus
#endif

/**
 * @brief Store a byte and flags on an object, then update its 0x88 byte from flag bit 3.
 * @param object Object to update.
 * @param value Byte to store at offset 0x18.
 * @param flags Flags to store at offset 0x1A.
 * @return Always 1.
 */
s32 func_002D1440(FieldMenuManager* object, u8 value, u32 flags);

/**
 * @brief Advance the menu load: request resources, fade out, release the old controller, launch the new one and fade in.
 * @param manager Menu manager.
 * @return Load state after this step, or zero while waiting on resources or when the launch fails.
 */
u8 field_advance_menu_load(FieldMenuManager* manager);

/**
 * @brief Start one of the menu's eight sounds.
 * @param manager Menu manager.
 * @param sound Sound slot.
 * @return One when the sound was started; zero for a slot out of range.
 */
s32 field_play_menu_sound(FieldMenuManager* manager, s16 sound);

#ifdef __cplusplus
/**
 * @brief Create the requested menu's controller, register it, and make it the active State.
 * @param manager Menu manager.
 * @param menu Menu to open.
 * @return True when the controller's record selection was created; false for an unknown menu.
 */
s32 field_launch_menu(FieldMenuManager* manager, u8 menu);
#endif

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include "overlays/1067-00/text_001DD3C0.h"
#include "overlays/1067-00/text_001E1590.h"

class FieldClass1504F0;
class FieldClass1538D0;
class LibClass171EA0;
class LibDrawBuffer;
class LibObject178660;
struct FieldVec4A;

/** Resource loader with vtable D_15B040 in main data, attached to the field context's object at offset 0x58. */
class FieldClass15B040 : public FieldResourceLoader
{
    public:
        /** @brief Clear the context's pointer to this loader unless flag 0 is set. */
        virtual ~FieldClass15B040();

        /**
         * @brief Allocate the next record's buffer and start its read once the field is idle.
         * @param cancel_request Nonzero skips the start while the loader is idle.
         */
        virtual void update_requests(s32 cancel_request);

        u8 unk34_0 : 1;
        u8 unk34_1_7 : 7;
        u8 unk35[3];
};

/** Retained field attachment with a context callback; it owns a level table and its display objects. */
class FieldClass15B0E0 : public FieldListObject, public FieldClass1DD400
{
    public:
        static void* operator new(u32 size);

        /** @brief Release storage through the Lib heap. @param object Storage to release. */
        static void operator delete(void* object);

        FieldClass15B0E0();

        virtual ~FieldClass15B0E0();

        /** @brief Report this object's list kind. @return Always 4. */
        virtual s32 get_default_list_kind();

        /** @brief Release the display objects and add the object to the resident release queue. */
        virtual void func_001DD7B0();

        virtual void update();

        /** @brief Clear the display object at offset 0x20. @param arg Unused. */
        virtual void func_001DDB30(void* arg);

        /** @brief Release the Lib container and clear its state bit. */
        void func_002D1D70();

        /**
         * @brief Pick a random entry pair from the level table.
         * @param first Receives the entry's first value.
         * @param second Receives the entry's second value.
         * @param level Level to look up; the first group above it is used, or the last group.
         * @return One when an entry was picked; zero without a table.
         */
        s32 func_002D1DE0(u32* first, u32* second, s32 level);

        /** @brief Load the level table resource. */
        void func_002D1FD0();

        /** @brief Set flag 3 on the attached field object. */
        void func_002D2020();

        /** @brief Release the retained objects and reset the timer. */
        void func_002D2170();

        /**
         * @brief Record the flag and the context's current value, and reset the timer.
         * @param flag New value of flag 0.
         */
        void func_002D2210(s32 flag);

        /**
         * @brief Create and register a FieldClass15B090 at a position.
         * @param position Position for the new object.
         * @return One when it was created; zero without a table or on allocation failure.
         */
        s32 func_002D22B0(const FieldVec4A* position);

        /** @brief Step the resident entry's timer down by three, to no less than one. */
        void func_002D23B0();

        /** @brief Clear the resident entry's timer state and reset the angle. */
        void func_002D3920();

        u32 unk18;
        u16* table;
        FieldClass1538D0* unk20;
        float unk24;
        float unk28;
        u32 unk2c;
        u32 unk30;
        s32 unk34;
        s32 unk38;
        u32 unk3c;
        LibDrawBuffer* unk40;
        LibClass171EA0* unk44;
        FieldClass1504F0* unk48;
        LibObject178660* unk4c;
        u32 unk50;
        s8 unk54;
        u8 unk55_0 : 1;
        u8 unk55_1 : 1;
        u8 unk55_2 : 1;
        u8 unk55_3 : 1;
        u8 unk55_4_7 : 4;
};
#endif

#endif
