#ifndef SO3_MAIN_INPUT_H
#define SO3_MAIN_INPUT_H

#include "types.h"
#include "sdk/main/libkernl_00121940.h"
#include "ee.h"
#include "main/semaphore.h"
#include "main/thread.h"

#ifdef __cplusplus
struct ResidentSystem;
#else
typedef struct ResidentSystem ResidentSystem;
#endif

#ifndef __cplusplus
typedef struct ResidentPadThread ResidentPadThread;
typedef struct ResidentDisplay ResidentDisplay;
typedef struct ResidentPadHook ResidentPadHook;
#endif

struct ResidentInputSystem;

#define RESIDENT_PAD_COUNT 2
#define RESIDENT_PAD_AXIS_COUNT 4
#define RESIDENT_PAD_PRESSURE_COUNT 12
#ifdef __cplusplus

/** The input system's pad polling thread, at g_system + 0x1784; vtable D_0014FC60. */
class ResidentPadThread : public ResidentThread
{
    public:
        ResidentInputSystem* input;
        u8 polling;
        u8 unk15[3];

        /** @brief Create the kernel thread, not polling yet. */
        ResidentPadThread()
        {
            resident_thread_create(this, 0x26, 0x4000);
            polling = 0;
        }

        virtual ~ResidentPadThread()
        {
        }

        /** @brief Body of the pad polling thread: on every wakeup, read the pads. */
        virtual void run();
};

/** Display the vblank handler updates; only the fields the input system touches are known. */
struct ResidentDisplay
{
    u8 unk0000[0x3E40];
    s32 unk3e40;
    u8 unk3e44[0x21];
    u8 vblank_enabled;
};

/** Object that takes over a frame's pad input; the poll calls it after reading both pads. */
class ResidentPadHook
{
    public:
        virtual void func_slot08();

        /**
         * @brief Handle the pads the poll just read.
         * @param input Input system.
         */
        virtual void update(ResidentInputSystem* input);
};

/**
 * The two pads (buttons, sticks and vibration) and the vblank counters that time each frame, at g_system + 0x1480.
 * It owns a polling thread and a semaphore.
 */
struct ResidentInputSystem
{
    u8 unk000[4];
    s32 vblank_handler;
    u32 seconds;
    volatile u32 vblank_wait_count;
    u32 vblank_count;
    ResidentPadHook* hook;
    u8 unk018[0x28];
    u8 pad_buffers[RESIDENT_PAD_COUNT][0x100];
    s32 sockets[RESIDENT_PAD_COUNT];
    s32 states[RESIDENT_PAD_COUNT];
    s32 unk250;
    u8 unk254[0xC];
    u16 held[RESIDENT_PAD_COUNT];
    u16 previous_held[RESIDENT_PAD_COUNT];
    u16 held_since_clear[RESIDENT_PAD_COUNT];
    u16 pressed[RESIDENT_PAD_COUNT];
    u8 repeat_counts[RESIDENT_PAD_COUNT];
    u8 retry_delays[RESIDENT_PAD_COUNT];
    u8 sticks[RESIDENT_PAD_COUNT][RESIDENT_PAD_AXIS_COUNT];
    u8 pressures[RESIDENT_PAD_COUNT][RESIDENT_PAD_PRESSURE_COUNT];
    u8 analog[RESIDENT_PAD_COUNT];
    u8 stick_dpad[RESIDENT_PAD_COUNT];
    u8 vibration_enabled[RESIDENT_PAD_COUNT];
    u8 vibration_dirty[RESIDENT_PAD_COUNT];
    u8 vibration_profile_read[RESIDENT_PAD_COUNT];
    u8 stick_limits[RESIDENT_PAD_COUNT][RESIDENT_PAD_AXIS_COUNT];
    u8 dead_zones[RESIDENT_PAD_COUNT];
    u8 unk2a8[RESIDENT_PAD_COUNT];
    u8 vibration_profiles[RESIDENT_PAD_COUNT][0x20];
    u8 unk2ea[2];
    s8 stick_offsets[RESIDENT_PAD_COUNT][RESIDENT_PAD_AXIS_COUNT];
    u8 small_motor[RESIDENT_PAD_COUNT];
    u8 large_motor[RESIDENT_PAD_COUNT];
    u8 repeat_delay;
    u8 second_vblanks;
    u8 field;
    u8 display_enabled;
    u8 unk2fc;
    u8 unk2fd[3];
    u32 vblank_total;
    ResidentPadThread poll_thread;
    ResidentSemaphore semaphore;
    ResidentDisplay* display;
    u8 unk328[0x18];

    /** @brief Create the polling thread and the semaphore, with no pad hook. */
    ResidentInputSystem();
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Start the input system.
 * @param input Input system.
 */
void resident_input_start(struct ResidentInputSystem* input);


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
s32 resident_pad_get_pressures(struct ResidentInputSystem* input, s32 slot, u8* pressures, s32 first, s32 last);

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
 * @brief Wait for the next display interrupt and return the retained GS field bit.
 * @param root Resident input and display state.
 * @param mode Minus one reads the field without waiting; other values wait.
 * @return Retained display field, zero or one.
 */
u32 resident_input_wait_vblank(struct ResidentInputSystem* root, s32 mode);

/**
 * @brief Set the seconds clock the vblank handler counts.
 * @param input Input system.
 * @param seconds New clock value.
 */
void resident_input_set_seconds(struct ResidentInputSystem* input, u32 seconds);

/**
 * @brief Get the seconds clock the vblank handler counts.
 * @param input Input system.
 * @return Seconds counted.
 */
u32 resident_input_get_seconds(const struct ResidentInputSystem* input);

/**
 * @brief Reset the seconds clock the vblank handler counts.
 * @param input Input system.
 */
void resident_input_reset_seconds(struct ResidentInputSystem* input);

/** Synchronize the GS path while holding the receiver's semaphore. */
s32 resident_sync_gs_path(void* object, s32 first, u16 second);

/**
 * @brief Get the resident system's input system.
 * @param system Resident system.
 * @return Input system at offset 0x1480.
 */
struct ResidentInputSystem* resident_system_get_input(struct ResidentSystem* system);

#ifdef __cplusplus
}
#endif

#endif
