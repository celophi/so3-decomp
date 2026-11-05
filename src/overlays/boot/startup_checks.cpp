#include "include_asm.h"
#include "overlays/boot/text_001E0900.h"
#include "overlays/boot/init.h"
#include "overlays/boot/resident.h"
#include "main/resident_001001E0.h"
#include "main/resident_0010A0E0.h"
#include "main/resident_00101550.h"
#include "main/resident_0011EE70.h"
#include "main/resident_00121860.h"
#include "sdk/main/libc_0013C6D0.h"
#include "sdk/main/libc_0013CA60.h"
#include "vu0.h"
#include "ee.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/lib/text_00429B00.h"
#include "overlays/lib/text_004DD440.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/lib/text_004AB8B0.h"

/** @brief Destroy the object. */
BootStartupChecks::~BootStartupChecks()
{
}

/**
 * @brief Read the PlayStation BB Unit's state: one when it isn't initialized, two when it's ready.
 * @param archive Resource archive.
 * @return Unit state, or three when the archive has no unit information.
 */
static inline u8 unit_state(ResidentArchive* archive)
{
    return archive->unk12184 != 0 ? archive->unit_state : 3;
}

/** @brief Run the memory card, progressive display and BB Unit screens in turn, then start the opening movie. */
void BootStartupChecks::update()
{
    LibSystemSettings* settings;
    BootInput* input;
    s32 slot1;
    s32 slot2;
    u8 finished;
    u8 again;

    if (resident_archive_has_unit_error(g_resource_archive))
    {
        return;
    }

    settings = (LibSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_system()), 1);
    input = g_boot_program.input;
    slot1 = input->slot1_state;
    slot2 = input->slot2_state;

    if (screen == BOOT_STARTUP_CARD_CHECK)
    {
        switch (step)
        {
        case BOOT_STARTUP_CARD_INSPECT:
            if (RESIDENT_ALIGN_RESOURCE(g_boot_program.message_block) != 0)
            {
                check_main_code();
                g_field_runtime->message_arguments[0] = 175;

                // Statuses 16-17 need no warning; these pairs can split the save and trophy files between cards.
                if ((u32)(slot1 - 16) <= 1 ||
                    (u32)(slot2 - 16) <= 1 ||
                    (slot1 == BOOT_CARD_STATUS_SAVE_SPACE_ONLY && slot2 == BOOT_CARD_STATUS_EITHER_FILE_ONLY) ||
                    (slot1 == BOOT_CARD_STATUS_SAVE_SPACE_ONLY && slot2 == BOOT_CARD_STATUS_TROPHY_PRESENT_NO_SAVE_SPACE) ||
                    (slot1 == BOOT_CARD_STATUS_EITHER_FILE_ONLY && slot2 == BOOT_CARD_STATUS_SAVE_SPACE_ONLY) ||
                    (slot1 == BOOT_CARD_STATUS_EITHER_FILE_ONLY && slot2 == BOOT_CARD_STATUS_EITHER_FILE_ONLY) ||
                    (slot1 == BOOT_CARD_STATUS_EITHER_FILE_ONLY && slot2 == BOOT_CARD_STATUS_SAVE_PRESENT_NO_TROPHY_SPACE) ||
                    (slot1 == BOOT_CARD_STATUS_EITHER_FILE_ONLY && slot2 == BOOT_CARD_STATUS_TROPHY_PRESENT_NO_SAVE_SPACE) ||
                    (slot1 == BOOT_CARD_STATUS_SAVE_PRESENT_NO_TROPHY_SPACE && slot2 == BOOT_CARD_STATUS_EITHER_FILE_ONLY) ||
                    (slot1 == BOOT_CARD_STATUS_SAVE_PRESENT_NO_TROPHY_SPACE && slot2 == BOOT_CARD_STATUS_TROPHY_PRESENT_NO_SAVE_SPACE) ||
                    (slot1 == BOOT_CARD_STATUS_TROPHY_PRESENT_NO_SAVE_SPACE && slot2 == BOOT_CARD_STATUS_SAVE_SPACE_ONLY) ||
                    (slot1 == BOOT_CARD_STATUS_TROPHY_PRESENT_NO_SAVE_SPACE && slot2 == BOOT_CARD_STATUS_EITHER_FILE_ONLY) ||
                    (slot1 == BOOT_CARD_STATUS_TROPHY_PRESENT_NO_SAVE_SPACE && slot2 == BOOT_CARD_STATUS_SAVE_PRESENT_NO_TROPHY_SPACE))
                {
                    screen = BOOT_STARTUP_PROGRESSIVE;
                    step = BOOT_STARTUP_PROGRESSIVE_DETECT;
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_UNAVAILABLE && slot2 == BOOT_CARD_STATUS_UNAVAILABLE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_NO_CARD;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_UNAVAILABLE && slot2 == BOOT_CARD_STATUS_NO_SPACE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT2_FULL;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_UNAVAILABLE && slot2 == BOOT_CARD_STATUS_SAVE_SPACE_ONLY)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT2_FULL;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_UNAVAILABLE && slot2 == BOOT_CARD_STATUS_EITHER_FILE_ONLY)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT2_FULL;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_UNAVAILABLE && slot2 == BOOT_CARD_STATUS_SAVE_PRESENT_NO_TROPHY_SPACE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT2_NO_TROPHY_SPACE;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_UNAVAILABLE && slot2 == BOOT_CARD_STATUS_TROPHY_PRESENT_NO_SAVE_SPACE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT2_NO_SAVE_SPACE;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_NO_SPACE && slot2 == BOOT_CARD_STATUS_UNAVAILABLE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT1_FULL;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_NO_SPACE && slot2 == BOOT_CARD_STATUS_NO_SPACE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_FULL;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_NO_SPACE && slot2 == BOOT_CARD_STATUS_SAVE_SPACE_ONLY)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_FULL;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_NO_SPACE && slot2 == BOOT_CARD_STATUS_EITHER_FILE_ONLY)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_FULL;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_NO_SPACE && slot2 == BOOT_CARD_STATUS_SAVE_PRESENT_NO_TROPHY_SPACE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_NO_TROPHY_SPACE;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_NO_SPACE && slot2 == BOOT_CARD_STATUS_TROPHY_PRESENT_NO_SAVE_SPACE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_NO_SAVE_SPACE;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_SAVE_SPACE_ONLY && slot2 == BOOT_CARD_STATUS_UNAVAILABLE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT1_FULL;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_SAVE_SPACE_ONLY && slot2 == BOOT_CARD_STATUS_NO_SPACE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_FULL;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_SAVE_SPACE_ONLY && slot2 == BOOT_CARD_STATUS_SAVE_SPACE_ONLY)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_FULL;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_SAVE_SPACE_ONLY && slot2 == BOOT_CARD_STATUS_SAVE_PRESENT_NO_TROPHY_SPACE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_NO_TROPHY_SPACE;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_EITHER_FILE_ONLY && slot2 == BOOT_CARD_STATUS_UNAVAILABLE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT1_FULL;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_EITHER_FILE_ONLY && slot2 == BOOT_CARD_STATUS_NO_SPACE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_FULL;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_SAVE_PRESENT_NO_TROPHY_SPACE && slot2 == BOOT_CARD_STATUS_UNAVAILABLE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT1_NO_TROPHY_SPACE;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_SAVE_PRESENT_NO_TROPHY_SPACE && slot2 == BOOT_CARD_STATUS_NO_SPACE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_NO_TROPHY_SPACE;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_SAVE_PRESENT_NO_TROPHY_SPACE && slot2 == BOOT_CARD_STATUS_SAVE_SPACE_ONLY)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_NO_TROPHY_SPACE;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_SAVE_PRESENT_NO_TROPHY_SPACE && slot2 == BOOT_CARD_STATUS_SAVE_PRESENT_NO_TROPHY_SPACE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_NO_TROPHY_SPACE;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_TROPHY_PRESENT_NO_SAVE_SPACE && slot2 == BOOT_CARD_STATUS_UNAVAILABLE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT1_NO_SAVE_SPACE;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_TROPHY_PRESENT_NO_SAVE_SPACE && slot2 == BOOT_CARD_STATUS_NO_SPACE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_NO_SAVE_SPACE;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_TROPHY_PRESENT_NO_SAVE_SPACE && slot2 == BOOT_CARD_STATUS_TROPHY_PRESENT_NO_SAVE_SPACE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_NO_SAVE_SPACE;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }
            }

            break;
        case BOOT_STARTUP_CARD_SHOW_WARNING:
            check_main_code();
            container = new (0) LibContainer(9, 0.0f, 0.0f, 0.0f);
            lib_queue_display_object(g_field_runtime,
                                     reinterpret_cast<LibTransformOwner*>(static_cast<LibTransformOwner*>(container)));
            text = new (0) LibTextWidget(g_boot_program.get_messages(), message, 0, 32.0f, 128.0f, 576.0f, 320.0f);
            lib_container_attach_widget(container, text);
            step = BOOT_STARTUP_CARD_WAIT_FOR_INPUT;
            break;
        case BOOT_STARTUP_CARD_WAIT_FOR_INPUT:
        {
            u16 pressed = input->pressed;

            if (pressed & settings->confirm_buttons)
            {
                check_main_code();
                screen = BOOT_STARTUP_PROGRESSIVE;
                step = BOOT_STARTUP_PROGRESSIVE_DETECT;
                text->destroy();
                text = 0;
                container->destroy();
                container = 0;
                resident_sound_play(g_sound, 1, 0, 0, 0x7F, 0x40, 0);
            }
            else if (pressed & settings->cancel_buttons)
            {
                text->destroy();
                text = 0;
                container->destroy();
                container = 0;
                resident_sound_play(g_sound, 2, 0, 0, 0x7F, 0x40, 0);
                step = BOOT_STARTUP_CARD_INSPECT;
            }
            else if (shown_slot1 != slot1 || shown_slot2 != slot2)
            {
                text->destroy();
                text = 0;
                container->destroy();
                container = 0;
                input->clear_card_states();
                step = BOOT_STARTUP_CARD_INSPECT;
            }

            break;
        }
        }
    }
    else if (screen == BOOT_STARTUP_PROGRESSIVE)
    {
        finished = 0;

        do
        {
            switch (step)
            {
            case BOOT_STARTUP_PROGRESSIVE_DETECT:
                again = 0;
                check_main_code();

                if ((input->held & BOOT_BUTTON_TRIANGLE) && (input->held & BOOT_BUTTON_CROSS))
                {
                    step++;
                    container = new (0) LibContainer(9, 0.0f, 0.0f, 0.0f);
                    lib_queue_display_object(g_field_runtime,
                                             reinterpret_cast<LibTransformOwner*>(static_cast<LibTransformOwner*>(container)));
                }
                else if (++frames >= 30 && RESIDENT_ALIGN_RESOURCE(g_boot_program.message_block) != 0)
                {
                    finished = 1;
                }

                break;
            case BOOT_STARTUP_PROGRESSIVE_LOAD_OFFER:
                again = 0;

                if (RESIDENT_ALIGN_RESOURCE(g_boot_program.message_block) != 0)
                {
                    check_main_code();
                    text = new (0) LibTextWidget(g_boot_program.get_messages(), BOOT_MSG_PROGRESSIVE_OFFER, 0, 32.0f, 96.0f, 576.0f, 320.0f);
                    lib_container_attach_widget(container, text);
                    step++;
                }

                break;
            case BOOT_STARTUP_PROGRESSIVE_OFFER:
                again = 0;
                check_main_code();

                if (input->pressed & settings->confirm_buttons)
                {
                    step++;
                    frames = 0;
                    text->destroy();
                    text = 0;
                    resident_sound_play(g_sound, 1, 0, 0, 0x7F, 0x40, 0);
                    settings->widescreen = BOOT_STARTUP_PROGRESSIVE;
                }
                else if (input->pressed & settings->alternate_buttons)
                {
                    step++;
                    frames = 0;
                    text->destroy();
                    text = 0;
                    resident_sound_play(g_sound, 1, 0, 0, 0x7F, 0x40, 0);
                    settings->widescreen = 0;
                }
                else if (input->pressed & settings->cancel_buttons)
                {
                    resident_sound_play(g_sound, 2, 0, 0, 0x7F, 0x40, 0);
                    finished = 1;
                }

                break;
            case BOOT_STARTUP_PROGRESSIVE_SWITCH_DELAY:
                again = 0;
                check_main_code();

                if (++frames > 10)
                {
                    g_boot_program.set_progressive(1);
                    frames = 0;
                    step++;
                }

                break;
            case BOOT_STARTUP_PROGRESSIVE_SWITCH_WAIT:
                again = 0;
                check_main_code();

                if (++frames > 60)
                {
                    step++;

                    if (settings->widescreen)
                    {
                        text = new (0) LibTextWidget(g_boot_program.get_messages(), BOOT_MSG_PROGRESSIVE_WIDE_STARTED, 0, 32.0f, 128.0f, 576.0f, 320.0f);
                        text->set_scale(0.75f);
                    }
                    else
                    {
                        text = new (0) LibTextWidget(g_boot_program.get_messages(), BOOT_MSG_PROGRESSIVE_NORMAL_STARTED, 0, 32.0f, 128.0f, 576.0f, 320.0f);
                    }

                    lib_container_attach_widget(container, text);
                    frames = 0;
                }

                break;
            case BOOT_STARTUP_PROGRESSIVE_CONFIRM:
                again = 0;
                check_main_code();

                if (input->pressed & settings->confirm_buttons)
                {
                    finished = 1;
                    resident_sound_play(g_sound, 1, 0, 0, 0x7F, 0x40, 0);
                }
                else if (++frames > 539 || (input->pressed & settings->cancel_buttons))
                {
                    text->destroy();
                    text = 0;
                    step++;
                    frames = 0;
                    resident_sound_play(g_sound, 2, 0, 0, 0x7F, 0x40, 0);
                }

                break;
            case BOOT_STARTUP_PROGRESSIVE_REVERT_DELAY:
                check_main_code();
                again = 0;

                if (++frames > 10)
                {
                    settings->widescreen = 0;
                    g_boot_program.set_progressive(0);
                    step++;
                    frames = 0;
                }

                break;
            case BOOT_STARTUP_PROGRESSIVE_REVERT_WAIT:
                check_main_code();
                again = 0;

                if (++frames > 60)
                {
                    step = BOOT_STARTUP_PROGRESSIVE_LOAD_OFFER;
                    frames = 0;
                }

                break;
            default:
                check_main_code();
                again = 0;
                break;
            }
        } while (again);

        if (finished)
        {
            step = BOOT_STARTUP_UNIT_INSPECT;

            if (text != 0)
            {
                text->destroy();
                text = 0;
            }

            if (container != 0)
            {
                container->destroy();
                container = 0;
            }

            screen = BOOT_STARTUP_UNIT_CHECK;
        }
    }
    else
    {
        finished = 0;

        do
        {
            switch (step)
            {
            case BOOT_STARTUP_UNIT_INSPECT:
                again = 0;
                check_main_code();

                if (unit_state(g_resource_archive) != 2)
                {
                    if (unit_state(g_resource_archive) == 1)
                    {
                        step++;
                        container = new (0) LibContainer(9, 0.0f, 0.0f, 0.0f);
                        lib_queue_display_object(g_field_runtime,
                                                 reinterpret_cast<LibTransformOwner*>(static_cast<LibTransformOwner*>(container)));
                    }
                    else if (g_boot_program.unit_data_deleted != 0)
                    {
                        step = BOOT_STARTUP_UNIT_LOAD_DELETED_WARNING;
                        container = new (0) LibContainer(9, 0.0f, 0.0f, 0.0f);
                        lib_queue_display_object(g_field_runtime,
                                                 reinterpret_cast<LibTransformOwner*>(static_cast<LibTransformOwner*>(container)));
                    }
                    else
                    {
                        finished = 1;
                    }
                }

                break;
            case BOOT_STARTUP_UNIT_LOAD_WARNING:
                again = 0;
                check_main_code();

                if (RESIDENT_ALIGN_RESOURCE(g_boot_program.message_block) != 0)
                {
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    text = new (0) LibTextWidget(g_boot_program.get_messages(), BOOT_MSG_UNIT_NOT_INITIALIZED, 0, 32.0f, 96.0f, 576.0f, 320.0f);
                    lib_container_attach_widget(container, text);
                    step++;
                }

                break;
            case BOOT_STARTUP_UNIT_WAIT_FOR_INPUT:
                check_main_code();
                again = 0;

                if (input->pressed & settings->confirm_buttons)
                {
                    resident_sound_play(g_sound, 1, 0, 0, 0x7F, 0x40, 0);
                    finished = 1;
                }

                break;
            case BOOT_STARTUP_UNIT_LOAD_DELETED_WARNING:
                again = 0;

                if (RESIDENT_ALIGN_RESOURCE(g_boot_program.message_block) != 0)
                {
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    text = new (0) LibTextWidget(g_boot_program.get_messages(), BOOT_MSG_UNIT_DATA_DELETED, 0, 32.0f, 128.0f, 576.0f, 320.0f);
                    lib_container_attach_widget(container, text);
                    step = BOOT_STARTUP_UNIT_WAIT_FOR_INPUT;
                }

                break;
            default:
                again = 0;
                break;
            }
        } while (again);

        if (finished)
        {
            if (container != 0)
            {
                container->destroy();
                container = 0;
            }

            if (text != 0)
            {
                text->destroy();
                text = 0;
            }

            lib_object_detach_owner(this);
            destroy();
            g_update_list->append_node(new (0) BootOpeningMovie, -1);
        }
    }
}

/** @brief Start on the memory card check. */
BootStartupChecks::BootStartupChecks()
{
    step = BOOT_STARTUP_CARD_INSPECT;
    frames = 0;
    screen = BOOT_STARTUP_CARD_CHECK;
    container = 0;
    text = 0;
}
