#include "include_asm.h"
#include "main/system.h"
#include "main/utility.h"

/** GS CSR; bit 13 is the field being displayed. */
#define GS_CSR (*(volatile u64*)0x12001000)
#define SCE_PADLup 0x10
#define SCE_PADLright 0x20
#define SCE_PADLdown 0x40
#define SCE_PADLleft 0x80
#define INTC_VBLANK_S 2
#define SCE_PAD2_SPECIFIC_PORT 2

/** Socket parameters for scePad2CreateSocket. */
typedef struct scePad2SocketParam
{
    s32 option;
    s32 port;
    s32 slot;
    s32 number;
    u8 name[16];
} scePad2SocketParam;

extern "C" {
/** The time-slice scheduler. */
extern ResidentThreadScheduler g_scheduler;

s32 sceGsSyncPath(s32 mode, u16 timeout);

s32 EnableIntc(s32 cause);

s32 sceDbcInit(void);

s32 scePad2Init(s32 mode);

s32 scePad2CreateSocket(scePad2SocketParam* param, void* buffer);

s32 scePad2GetState(s32 socket);

s32 scePad2Read(s32 socket, u8* data);

s32 scePad2GetButtonProfile(s32 socket, u8* profile);

s32 sceVibGetProfile(s32 socket, u8* profile);

s32 sceVibSetActParam(s32 socket, s32 profile_size, u8* profile, s32 data_size, u8* data);

s32 AddIntcHandler(s32 cause, s32 (*handler)(s32), s32 next);

void func_4DD520(ResidentDisplay* display, s32 field);

void func_4DCDA0(ResidentDisplay* display, s32 value);

void resident_pad_reset(ResidentInputSystem* input, s32 slot, s32 full);

extern u32 g_vblank_wait_flag;

/**
 * @brief Wait for a GS path to finish, holding the input system's semaphore.
 * @param object Input system.
 * @param first sceGsSyncPath mode.
 * @param second sceGsSyncPath timeout.
 * @return sceGsSyncPath's result.
 */
s32 resident_sync_gs_path(void* object, s32 first, u16 second)
{
    ResidentInputSystem* input = (ResidentInputSystem*)object;
    ResidentSemaphoreLock lock(&input->semaphore);

    return sceGsSyncPath(first, second);
}

/**
 * @brief Attach the display whose field the vblank handler updates.
 * @param input Input system.
 * @param display Display to update each vblank, or null.
 * @param enabled Nonzero to update the display each vblank.
 */
void resident_input_attach_display(ResidentInputSystem* input, void* display, u8 enabled)
{
    ResidentDisplay* attached = static_cast<ResidentDisplay*>(display);

    input->display_enabled = enabled;
    input->display = attached;

    if (attached != 0)
    {
        attached->vblank_enabled = enabled;
    }
}

/**
 * @brief Take the number of vblanks counted since the last call.
 * @param input Input system.
 * @return Vblanks since the last call.
 */
s32 resident_input_take_vblank_count(ResidentInputSystem* input)
{
    u32 count = input->vblank_count;
    input->vblank_count = 0;
    return count;
}

/**
 * @brief Wait for the next vblank and return the GS field it recorded.
 * @param input Input system.
 * @param mode Minus one reads the field without waiting; other values wait.
 * @return Display field, zero or one.
 */
u32 resident_input_wait_vblank(ResidentInputSystem* input, s32 mode)
{
    g_vblank_wait_flag = 0;

    if (mode == -1)
    {
        return input->field;
    }

    input->vblank_wait_count = 0;

    while (!input->vblank_wait_count)
    {
    }

    return input->field;
}

/**
 * @brief Set the seconds clock the vblank handler counts.
 * @param input Input system.
 * @param seconds New clock value.
 */
void resident_input_set_seconds(ResidentInputSystem* input, u32 seconds)
{
    input->seconds = seconds;
    input->second_vblanks = 0;
}

/**
 * @brief Get the seconds clock the vblank handler counts.
 * @param input Input system.
 * @return Seconds counted.
 */
u32 resident_input_get_seconds(const ResidentInputSystem* input)
{
    return input->seconds;
}

/**
 * @brief Reset the seconds clock the vblank handler counts.
 * @param input Input system.
 */
void resident_input_reset_seconds(ResidentInputSystem* input)
{
    input->seconds = 0;
    input->second_vblanks = 0;
}

/**
 * @brief Clear the pressed and held-since-clear latches of a pad.
 * @param input Input system.
 * @param slot Pad slot.
 */
void resident_pad_clear_latched(ResidentInputSystem* input, s32 slot)
{
    input->held_since_clear[slot] = 0;
    input->pressed[slot] = 0;
}

/**
 * @brief Get the pressed buttons, or the held ones once they have been held long enough to repeat.
 * @param input Input system.
 * @param slot Pad slot.
 * @return Button bits.
 */
u16 resident_pad_get_repeated(const ResidentInputSystem* input, s32 slot)
{
    if (input->repeat_counts[slot] >= input->repeat_delay)
    {
        return input->held[slot];
    }

    return input->pressed[slot];
}

/**
 * @brief Get the buttons newly pressed since the latches were last cleared.
 * @param input Input system.
 * @param slot Pad slot.
 * @return Pressed button bits.
 */
u16 resident_pad_get_pressed(const ResidentInputSystem* input, s32 slot)
{
    return input->pressed[slot];
}

/**
 * @brief Get every button held at some point since the latches were last cleared.
 * @param input Input system.
 * @param slot Pad slot.
 * @return Held button bits.
 */
u16 resident_pad_get_held_since_clear(const ResidentInputSystem* input, s32 slot)
{
    return input->held_since_clear[slot];
}

/**
 * @brief Get the buttons a pad holds this frame.
 * @param input Input system.
 * @param slot Pad slot.
 * @return Held button bits.
 */
u16 resident_pad_get_held(const ResidentInputSystem* input, s32 slot)
{
    return input->held[slot];
}

/**
 * @brief Choose whether a pad's left stick also presses the direction buttons.
 * @param input Input system.
 * @param slot Pad slot.
 * @param enabled Nonzero to map the stick onto the direction buttons.
 */
void resident_pad_set_stick_dpad(ResidentInputSystem* input, s32 slot, s32 enabled)
{
    input->stick_dpad[slot] = enabled;
}

/**
 * @brief Enable or disable a pad's vibration; disabling stops both motors.
 * @param input Input system.
 * @param slot Pad slot.
 * @param enabled Nonzero to allow vibration.
 */
void resident_pad_set_vibration_enabled(ResidentInputSystem* input, s32 slot, s32 enabled)
{
    if (!enabled)
    {
        input->small_motor[slot] = 0;
        input->large_motor[slot] = 0;
        input->vibration_dirty[slot] = 1;
    }

    input->vibration_enabled[slot] = enabled;
}

/**
 * @brief Send a pad's motor levels to it when they changed or a motor is running.
 * @param input Input system.
 * @param slot Pad slot.
 */
void resident_pad_update_vibration(ResidentInputSystem* input, s32 slot)
{
    u8 levels[2];
    s32 level_count;

    if (input->states[slot] != 1)
    {
        return;
    }

    if (!input->vibration_dirty[slot])
    {
        if (!input->vibration_enabled[slot])
        {
            return;
        }

        if (!input->small_motor[slot] && !input->large_motor[slot])
        {
            return;
        }
    }

    if (!input->vibration_profile_read[slot])
    {
        if (sceVibGetProfile(input->sockets[slot], input->vibration_profiles[slot]) <= 0)
        {
            return;
        }

        input->vibration_profile_read[slot] = 1;
    }

    input->vibration_profiles[slot][0] &= 3;

    switch (input->vibration_profiles[slot][0])
    {
    case 1:
        levels[0] = (input->small_motor[slot] & 1) | (input->large_motor[slot] != 0);
        level_count = 1;
        break;

    case 2:
        levels[0] = input->large_motor[slot];
        level_count = 1;
        break;

    case 3:
        levels[0] = ((input->large_motor[slot] & 0x7F) << 1) | (input->small_motor[slot] & 1);
        levels[1] = input->large_motor[slot] >> 7;
        level_count = 2;
        break;

    default:
        return;
    }

    if (sceVibSetActParam(input->sockets[slot], 1, input->vibration_profiles[slot], level_count, levels) == 1)
    {
        input->vibration_dirty[slot] = 0;
    }
}

/**
 * @brief Set a pad's motor levels while vibration is enabled.
 * @param input Input system.
 * @param slot Pad slot.
 * @param small Small motor, on when nonzero.
 * @param large Large motor strength.
 */
void resident_pad_set_vibration(ResidentInputSystem* input, s32 slot, s32 small, s32 large)
{
    if (!input->vibration_enabled[slot])
    {
        input->small_motor[slot] = 0;
        input->large_motor[slot] = 0;
        return;
    }

    if ((input->small_motor[slot] || input->large_motor[slot]) && !small && !large)
    {
        input->small_motor[slot] = 0;
        input->large_motor[slot] = 0;
        input->vibration_dirty[slot] = 1;
        return;
    }

    input->small_motor[slot] = small;
    input->large_motor[slot] = large;
}

/**
 * @brief Copy a range of a pad's button pressures.
 * @param input Input system.
 * @param slot Pad slot.
 * @param pressures Receives the pressures, zero when the pad isn't analog.
 * @param first First pressure index.
 * @param last Last pressure index, inclusive.
 * @return Nonzero when the pad is in analog mode.
 */
s32 resident_pad_get_pressures(ResidentInputSystem* input, s32 slot, u8* pressures, s32 first, s32 last)
{
    if (!input->analog[slot])
    {
        for (s32 i = first; i <= last; i++)
        {
            *pressures++ = 0;
        }

        return 0;
    }

    for (s32 i = first; i <= last; i++)
    {
        *pressures++ = input->pressures[slot][i];
    }

    return 1;
}

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
s32 resident_pad_get_sticks(ResidentInputSystem* input, s32 slot, s32* right_x, s32* right_y, s32* left_x, s32* left_y)
{
    if (!input->analog[slot])
    {
        *left_y = 0;
        *left_x = 0;
        *right_y = 0;
        *right_x = 0;
        return 0;
    }

    s32 dead_zone = input->dead_zones[slot];

    for (s32 axis = 0; axis < RESIDENT_PAD_AXIS_COUNT; axis++)
    {
        s32* out;

        switch (axis)
        {
        case 0:
            out = right_x;
            break;

        case 1:
            out = right_y;
            break;

        case 2:
            out = left_x;
            break;

        default:
            out = left_y;
            break;
        }

        s32 value = input->sticks[slot][axis] - 0x80 - input->stick_offsets[slot][axis];
        s32 distance = value >= 0 ? value : -value;

        if (distance < dead_zone)
        {
            value = 0;
        }
        else if (value > 0)
        {
            value -= dead_zone;
        }
        else
        {
            value += dead_zone;
        }

        s32 limit = input->stick_limits[slot][axis];

        if (value > limit)
        {
            value = limit;
        }

        if (value < -limit)
        {
            value = -limit;
        }

        *out = value;
    }

    return 1;
}

/**
 * @brief Count a vblank, update the attached display and wake the pad polling thread.
 * @param input Input system.
 */
void resident_input_handle_vblank(ResidentInputSystem* input)
{
    input->field = (GS_CSR >> 13) & 1;
    input->vblank_total++;

    if (++input->second_vblanks > 59)
    {
        input->second_vblanks = 0;
        input->seconds++;
    }

    if (input->display_enabled)
    {
        func_4DD520(input->display, input->field);
    }

    if (input->unk2fc)
    {
        s32 value = input->display->unk3e40;

        if (value >= 0x800000 || value <= 0)
        {
            input->unk2fc = 0;
        }
        else
        {
            value += input->unk250;
            func_4DCDA0(input->display, value);
        }
    }

    resident_lower_resource_priorities(resident_system_get_resource_queue(resident_get_system()));
    input->vblank_wait_count++;
    input->vblank_count++;
    resident_thread_wakeup(&input->poll_thread);
}

/**
 * @brief Poll both pads: read their buttons, sticks and pressures, update the latches and send vibration.
 * @param input Input system.
 */
void resident_pad_update(ResidentInputSystem* input)
{
    for (s32 slot = 0; slot < RESIDENT_PAD_COUNT; slot++)
    {
        s32 left_x;
        s32 left_y;
        s32 right_x;
        s32 right_y;
        u8 data[0x20];
        u8 profile[0x20];

        s32 state = scePad2GetState(input->sockets[slot]);
        input->states[slot] = state;

        if (state != 1)
        {
            resident_pad_reset(input, slot, 1);
            input->retry_delays[slot] = 2;
            continue;
        }

        s32 data_size;

        if ((data_size = scePad2Read(input->sockets[slot], data)) < 0)
        {
            resident_pad_reset(input, slot, 1);
            continue;
        }

        s32 profile_size = scePad2GetButtonProfile(input->sockets[slot], profile);

        if (profile_size < 0)
        {
            resident_pad_reset(input, slot, 1);
            continue;
        }

        if (input->retry_delays[slot] > 0)
        {
            input->retry_delays[slot]--;
            continue;
        }

        input->previous_held[slot] = input->held[slot];

        if (profile[0] == 0xF9 && profile[1] == 0xFF && profile[2] == 0 && profile[3] == 0)
        {
            input->held[slot] = ~((data[0] & 1) | ((data[0] & 0xFE) << 2) | 6 | (data[1] << 10));
        }
        else
        {
            input->held[slot] = ~(data[0] | (data[1] << 8));
        }

        if (profile_size >= 3 && (profile[2] & 0xF) == 0xF)
        {
            if (data_size >= 6)
            {
                input->analog[slot] = 1;

                for (s32 axis = 0; axis < RESIDENT_PAD_AXIS_COUNT; axis++)
                {
                    input->sticks[slot][axis] = data[2 + axis];
                }
            }

            if (data_size >= 18 && profile_size >= 4 && (profile[2] & 0xF0) == 0xF0 && profile[3] == 0xFF)
            {
                for (s32 i = 0; i < RESIDENT_PAD_PRESSURE_COUNT; i++)
                {
                    input->pressures[slot][i] = data[6 + i];
                }
            }

            if (input->hook == 0 && input->stick_dpad[slot] &&
                resident_pad_get_sticks(input, slot, &right_x, &right_y, &left_x, &left_y))
            {
                if (left_x <= -(input->stick_limits[slot][2] >> 1))
                {
                    input->held[slot] |= SCE_PADLleft;
                }

                if (left_x >= input->stick_limits[slot][2] >> 1)
                {
                    input->held[slot] |= SCE_PADLright;
                }

                if (left_y <= -(input->stick_limits[slot][3] >> 1))
                {
                    input->held[slot] |= SCE_PADLup;
                }

                if (left_y >= input->stick_limits[slot][3] >> 1)
                {
                    input->held[slot] |= SCE_PADLdown;
                }
            }
        }
        else
        {
            input->analog[slot] = 0;
        }

        if (input->hook == 0)
        {
            if (input->previous_held[slot] == input->held[slot] && input->held[slot] != 0)
            {
                if (input->repeat_counts[slot] < input->repeat_delay)
                {
                    input->repeat_counts[slot]++;
                }
            }
            else
            {
                input->repeat_counts[slot] = 0;
            }

            input->held_since_clear[slot] |= input->held[slot];
            input->pressed[slot] |= input->held[slot] & ~input->previous_held[slot];
        }

        resident_pad_update_vibration(input, slot);
    }

    if (input->hook != 0)
    {
        input->hook->update(input);
    }
}

/**
 * @brief Body of the pad polling thread: on every wakeup, read the pads.
 */
void ResidentPadThread::run()
{
    for (;;)
    {
        resident_thread_sleep();
        this->polling = 1;
        resident_pad_update(this->input);
        this->polling = 0;
    }
}

/**
 * @brief Vblank interrupt handler: let the scheduler run, then update the input system.
 * @param cause Interrupt cause.
 * @return Zero.
 */
s32 resident_input_vblank_handler(s32 cause)
{
    resident_scheduler_stop(&g_scheduler);
    resident_input_handle_vblank(resident_system_get_input(&g_system));
    ee_exit_handler();
    return 0;
}

/**
 * @brief Clear a pad's buttons, sticks and pressures, and wait a couple of polls before reading it again.
 * @param input Input system.
 * @param slot Pad slot.
 * @param full Nonzero in its low byte to also clear unk2a8.
 */
void resident_pad_reset(ResidentInputSystem* input, s32 slot, s32 full)
{
    input->held[slot] = 0;
    input->previous_held[slot] = 0;
    input->held_since_clear[slot] = 0;
    input->pressed[slot] = 0;
    input->repeat_counts[slot] = 0;
    input->retry_delays[slot] = 2;
    input->vibration_profile_read[slot] = 0;
    input->analog[slot] = 0;

    // TODO: I'd expect input->sticks[slot][axis] here, but only a byte pointer into the array puts the row address
    // where the original computes it.
    u8* sticks = (u8*)input->sticks + slot * RESIDENT_PAD_AXIS_COUNT;

    for (s32 axis = 0; axis < RESIDENT_PAD_AXIS_COUNT; axis++)
    {
        sticks[axis] = 0;
    }

    for (s32 i = 0; i < RESIDENT_PAD_PRESSURE_COUNT; i++)
    {
        input->pressures[slot][i] = 0;
    }

    if ((u8)full)
    {
        input->unk2a8[slot] = 0;
    }
}

/**
 * @brief Start the input system: open both pad sockets, install the vblank handler and start the polling thread.
 * @param input Input system.
 */
void resident_input_start(ResidentInputSystem* input)
{
    while (!sceDbcInit())
    {
    }

    while (!scePad2Init(0))
    {
    }

    input->repeat_delay = 12;

    for (s32 slot = 0; slot < RESIDENT_PAD_COUNT; slot++)
    {
        scePad2SocketParam param;

        param.option = SCE_PAD2_SPECIFIC_PORT;
        param.port = slot != 0;
        param.slot = 0;
        param.number = 0;
        param.name[0] = 0;
        input->vibration_profile_read[slot] = 0;
        input->vibration_dirty[slot] = 0;
        input->vibration_enabled[slot] = 0;
        input->sockets[slot] = scePad2CreateSocket(&param, input->pad_buffers[slot]);
        input->states[slot] = 0;
        resident_pad_reset(input, slot, 1);
        input->stick_dpad[slot] = 1;

        input->stick_offsets[slot][0] = 0;
        input->stick_offsets[slot][1] = 0;
        input->stick_offsets[slot][2] = 0;
        input->stick_offsets[slot][3] = 0;

        input->dead_zones[slot] = 0x20;

        input->stick_limits[slot][0] = 0x50;
        input->stick_limits[slot][1] = 0x50;
        input->stick_limits[slot][2] = 0x50;
        input->stick_limits[slot][3] = 0x50;

        input->small_motor[slot] = 0;
        input->large_motor[slot] = 0;
    }

    input->vblank_handler = AddIntcHandler(INTC_VBLANK_S, resident_input_vblank_handler, 0);
    EnableIntc(INTC_VBLANK_S);
    input->hook = 0;
    input->display = 0;
    input->vblank_count = 0;
    input->unk2fc = 0;
    input->poll_thread.input = input;
    input->poll_thread.start();
}

/** @brief Create the polling thread and the semaphore, with no pad hook. */
ResidentInputSystem::ResidentInputSystem()
{
    semaphore.create(1, 1);
    hook = 0;
    vblank_total = 0;
}
}
