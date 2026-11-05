#include "include_asm.h"
#include "overlays/boot/text_001E0900.h"
#include "overlays/boot/text_001F6010.h"
#include "overlays/boot/init.h"
#include "overlays/boot/resident.h"
#include "overlays/lib/text_0045AD10.h"
#include "main/resident_001001E0.h"
#include "main/resident_00101550.h"
#include "vu0.h"

extern "C" {
extern LibVector4 g_default_bounding_sphere;
}

/** Stages of the installer screen's resource loading, unit checks, copy, and exit paths. */
enum BootInstallerStep
{
    BOOT_INSTALL_WAIT_FOR_RESOURCES = 0,
    BOOT_INSTALL_DECODE_SCREEN_IMAGES = 1,
    BOOT_INSTALL_SHOW_INITIAL_PROMPT = 2,
    BOOT_INSTALL_HANDLE_CHOICE = 3,
    BOOT_INSTALL_LEAVE = 4,
    BOOT_INSTALL_WAIT_FOR_UNIT_RESOURCES = 5,
    BOOT_INSTALL_QUERY_UNIT = 6,
    BOOT_INSTALL_WAIT_FOR_UNIT_STATUS = 7,
    BOOT_INSTALL_WAIT_FOR_UNIT_COMMAND = 8,
    BOOT_INSTALL_CHECK_UNIT_RESULT = 9,
    BOOT_INSTALL_SHOW_OVERWRITE_PROMPT = 10,
    BOOT_INSTALL_REQUEST_SPACE = 11,
    BOOT_INSTALL_WAIT_FOR_SPACE = 12,
    BOOT_INSTALL_CHECK_SPACE = 13,
    BOOT_INSTALL_SHOW_NO_SPACE = 14,
    BOOT_INSTALL_WAIT_TO_BEGIN = 15,
    BOOT_INSTALL_PREPARE_FILES = 16,
    BOOT_INSTALL_WAIT_FOR_FILES = 17,
    BOOT_INSTALL_START_COPY = 18,
    BOOT_INSTALL_COPY_PROGRESS = 19,
    BOOT_INSTALL_SHOW_ERROR = 20,
    BOOT_INSTALL_WAIT_FOR_ACKNOWLEDGEMENT = 21,
    BOOT_INSTALL_RETURN_TO_TITLE = 22,
    BOOT_INSTALL_FINISH_COPY = 23,
    BOOT_INSTALL_WAIT_FOR_FINISH = 24,
    BOOT_INSTALL_SHOW_COMPLETE = 25,
    BOOT_INSTALL_RESUME_COPY = 26,
    BOOT_INSTALL_ABORT_COPY = 27,
    BOOT_INSTALL_WAIT_FOR_ABORT = 28,
    BOOT_INSTALL_FINISH_ABORT = 29,
    BOOT_INSTALL_WAIT_FOR_ABORT_FINISH = 30,
    BOOT_INSTALL_RETURN_FROM_ABORT = 31
};

enum BootInstallerLimits
{
    BOOT_INSTALL_TIP_COUNT = 8,
    BOOT_INSTALL_SECOND_TIP_PERCENT = 12,
    BOOT_INSTALL_ABORT_TIMEOUT_FRAMES = 600
};

/**
 * @brief Return the cursor's horizontal position for a yes/no selection.
 * @param selection Selected entry, 0 or 1.
 * @return Cursor x coordinate.
 */
static inline float menu_cursor_x(u8 selection)
{
    float x;

    switch (selection)
    {
    case 0:
        x = 180.0f;
        break;
    case 1:
        x = 374.0f;
        break;
    }

    return x;
}

/**
 * @brief Report the list kind used when registration requests the default.
 * @return Four.
 */
s32 BootInstaller::get_default_list_kind()
{
    return 4;
}

/** @brief Delete the object through its virtual destructor; null is ignored. */
void LibListObject::destroy()
{
    delete this;
}

/** @brief Virtual slot 4; the base implementation does nothing. */
void LibListObject::render()
{
}

/**
 * @brief Replace the tip image with block @p index of the tip image resource.
 * @param index Tip image to decode.
 */
void BootInstaller::show_tip_image(s32 index)
{
    if (tip_image != 0)
    {
        lib_object_detach_owner(tip_image);
        tip_image->destroy();
        tip_image = 0;
    }

    if (tip_image_buffer != 0)
    {
        resident_queue_allocation_release(g_resident_release_queues, tip_image_buffer);
        tip_image_buffer = 0;
    }

    tip_image_buffer = resident_allocate_decode_buffer(g_resident_resource_decoder, reinterpret_cast<ResidentResourceHeader*>(tip_image_data), index, 1);
    resident_decode_resource_block(g_resident_resource_decoder, reinterpret_cast<ResidentResourceHeader*>(tip_image_data),
                                   (void*)RESIDENT_ALIGN_RESOURCE(tip_image_buffer), index);
    tip_image = new (0) BootImage;
    tip_image->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(tip_image_buffer), 0);
    resident_find_entry(resident_get_entry_table(resident_get_system()), 1);
    tip_image->set_rectangle(0, 1, 0x120, 0xC9, 0x80808080, 0);
    tip_image->model->set_translation(-296.0f, -64.0f, 0.0f);
}

/**
 * @brief Set the position and a w component of one, and mark the transform dirty.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void LibOrientedTransform::set_translation(float x, float y, float z)
{
    transform_dirty = 1;
    translation.x = x;
    translation.y = y;
    translation.z = z;
    translation.w = 1.0f;
}

/** @brief Create the yes/no choice images and pulse the selected one; release them once installing starts. */
void BootInstaller::update_choice_images()
{
    if (screen_image_buffers[1] == 0)
    {
        return;
    }

    if (step >= BOOT_INSTALL_SHOW_NO_SPACE && images[4] != 0)
    {
        lib_object_detach_owner(images[4]);
        images[4]->destroy();
        images[4] = 0;
        lib_object_detach_owner(images[5]);
        images[5]->destroy();
        images[5] = 0;

        if (cursor != 0)
        {
            cursor->destroy();
            cursor = 0;
        }

        return;
    }

    if (images[4] == 0)
    {
        images[4] = new (0) BootImage;
        images[4]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(screen_image_buffers[0]), 0);
        images[4]->set_rectangle(0x1E, 0x131, 0x4C, 0x26, 0x80808080, 0);
        images[5] = new (0) BootImage;
        images[5]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(screen_image_buffers[0]), 0);
        images[5]->set_rectangle(0x1E, 0x167, 0x4C, 0x26, 0x80808080, 0);
    }

    if (((BootSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_system()), 1))->widescreen)
    {
        if (images[4] != 0)
        {
            images[4]->model->set_translation(-174.0f, 0.0f, 0.0f);
        }

        if (images[5] != 0)
        {
            images[5]->model->set_translation(78.0f, 0.0f, 0.0f);
        }
    }
    else
    {
        if (images[4] != 0)
        {
            images[4]->model->set_translation(-132.0f, 0.0f, 0.0f);
        }

        if (images[5] != 0)
        {
            images[5]->model->set_translation(60.0f, 0.0f, 0.0f);
        }
    }

    for (s32 i = 0; i < 2; i++)
    {
        if (images[4 + i] != 0 && images[4 + i]->model != 0)
        {
            LibModel* model = images[4 + i]->model;

            if (selection == i)
            {
                LibVector4 scale;
                copy_vector(&scale, &model->base_color_factor);

                if (choice_growing == 0)
                {
                    scale.x -= 0.01f * g_frame_ticks;
                    scale.y -= 0.005f * g_frame_ticks;

                    if (scale.y < 0.5f)
                    {
                        scale.y = 0.5f;
                    }

                    if (scale.x < 0.5f)
                    {
                        scale.x = 0.5f;
                        choice_growing = 1;
                    }
                }
                else if (choice_growing != 0)
                {
                    scale.x += 0.01f * g_frame_ticks;
                    scale.y += 0.005f * g_frame_ticks;

                    if (!(scale.y <= 1.0f))
                    {
                        scale.y = 1.0f;
                    }

                    if (!(scale.x <= 1.0f))
                    {
                        scale.x = 1.0f;
                        choice_growing = 0;
                    }
                }

                copy_vector(&model->base_color_factor, &scale);
                model->update_combined_color_factor();
            }
            else
            {
                LibVector4 scale;
                scale.x = 1.0f;
                scale.y = 1.0f;
                scale.z = 1.0f;
                scale.w = 1.0f;
                copy_vector(&model->base_color_factor, &scale);
                model->update_combined_color_factor();
            }
        }
    }
}

/** @brief Store the component product of the two input vectors. */
void LibColorModel::update_combined_color_factor()
{
    vu0_multiply_xyzw(&combined_color_factor, &base_color_factor, &color_modulation);
}

/** @brief Create the four screen images once, then place them for the 4:3 or widescreen layout. */
void BootInstaller::place_screen_images()
{
    if (screen_image_buffers[1] == 0)
    {
        return;
    }

    if (images[0] == 0)
    {
        images[0] = new (0) BootImage;
        images[0]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(screen_image_buffers[0]), 0);
        images[0]->set_rectangle(0, 1, 0x1E8, 0xDF, 0x80808080, 0);
        images[0]->model->set_translation(-244.0f, -112.0f, 0.0f);
    }

    if (images[1] == 0)
    {
        images[1] = new (0) BootImage;
        images[1]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(screen_image_buffers[1]), 0);
        images[1]->set_rectangle(0, 0, 0x280, 0x50, 0x80808080, 0);
        images[1]->model->set_translation(-312.0f, -216.0f, 0.0f);
    }

    if (images[2] == 0)
    {
        images[2] = new (0) BootImage;
        images[2]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(screen_image_buffers[0]), 0);
        images[2]->set_rectangle(0, 0xEA, 0xC8, 0x1D, 0x80808080, 0);
    }

    if (images[3] == 0)
    {
        images[3] = new (0) BootImage;
        images[3]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(screen_image_buffers[0]), 0);
        images[3]->set_rectangle(0x1B, 0x190, 0x1B6, 0x31, 0x80808080, 0);
    }

    if (((BootSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_system()), 1))->widescreen)
    {
        if (images[1] != 0)
        {
            images[1]->model->set_translation(-404.0f, -216.0f, 0.0f);
            images[1]->model->set_scale(1.31f, 1.0f, 1.0f);
        }

        if (images[2] != 0)
        {
            images[2]->model->set_translation(220.0f, 180.0f, 0.0f);
        }

        if (images[3] != 0)
        {
            images[3]->model->set_translation(-32.0f, -221.0f, 0.0f);
        }
    }
    else
    {
        if (images[1] != 0)
        {
            images[1]->model->set_translation(-312.0f, -216.0f, 0.0f);
            images[1]->model->set_scale(1.0f, 1.0f, 1.0f);
        }

        if (images[2] != 0)
        {
            images[2]->model->set_translation(150.0f, 180.0f, 0.0f);
        }

        if (images[3] != 0)
        {
            images[3]->model->set_translation(-128.0f, -221.0f, 0.0f);
        }
    }
}

/**
 * @brief Set the scale's xyz components and mark the transform dirty.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void LibOrientedTransform::set_scale(float x, float y, float z)
{
    transform_dirty = 1;
    scale.x = x;
    scale.y = y;
    scale.z = z;
}

/** @brief Advance the install sequence: load the screen, ask, check the BB Unit, install, then hand over. */
void BootInstaller::update()
{
    BootSystemSettings* resource;
    float x;
    s32 remaining;
    s32 percent;
    BootInput* input;
    input = g_boot_program.input;
    resource = (BootSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_system()), 1);

    switch (step)
    {
    case BOOT_INSTALL_WAIT_FOR_RESOURCES:
        if (resident_poll_resource_queue(g_resource_queue) != 0)
        {
            resident_queue_resource_request(g_resource_queue, BOOT_RES_SOUND, sound_data,
                                            BOOT_RESOURCE_TAG, BOOT_RESOURCE_PRIORITY, 0, 0, 0, BOOT_RESOURCE_READ);
            resident_queue_resource_request(g_resource_queue, BOOT_RES_SYSTEM_FILES, system_file_data,
                                            BOOT_RESOURCE_TAG, BOOT_RESOURCE_PRIORITY, 0, 0, 0, BOOT_RESOURCE_READ);
            resident_queue_resource_request(g_resource_queue, BOOT_RES_NAVIGATOR_FILES, navigator_file_data,
                                            BOOT_RESOURCE_TAG, BOOT_RESOURCE_PRIORITY, 0, 0, 0, BOOT_RESOURCE_READ);
            resident_queue_resource_request(g_resource_queue, BOOT_RES_TIP_IMAGES, tip_image_data,
                                            BOOT_RESOURCE_TAG, BOOT_RESOURCE_PRIORITY, 0, 0, 0, BOOT_RESOURCE_READ);
            clear_to_menu_background();
            D_001B661C->prepend_node(new (0) LibColorFade, -1);
            screen_images_loaded = 0;
            step++;
            container = new (0) LibContainer(9, 0.0f, 0.0f, 0.0f);
            lib_queue_display_object(D_001B657C,
                                     reinterpret_cast<LibTransformOwner*>(static_cast<LibTransformOwner*>(container)));
            message_text = new (0) LibTextWidget(g_boot_program.messages, BOOT_MSG_INSTALL_CONFIRM, 1, 48.0f, 88.0f, 512.0f, 224.0f);
            message_text->set_color(0x34130F);
            lib_container_attach_widget(container, message_text);
            x = menu_cursor_x(selection);
            cursor = new (0) LibSelectionCursor;
            cursor->init(1, 0, 0, x, 256.0f, 0.0f);
            lib_queue_display_object(D_001B657C, reinterpret_cast<LibTransformOwner*>(static_cast<LibTransformOwner*>(cursor)));
        }

        break;
    case BOOT_INSTALL_DECODE_SCREEN_IMAGES:
        screen_image_buffers[screen_images_loaded] =
            resident_allocate_decode_buffer(g_resident_resource_decoder, reinterpret_cast<ResidentResourceHeader*>(screen_image_data), screen_images_loaded, 1);
        resident_decode_resource_block(g_resident_resource_decoder, reinterpret_cast<ResidentResourceHeader*>(screen_image_data),
                                       (void*)RESIDENT_ALIGN_RESOURCE(screen_image_buffers[screen_images_loaded]), screen_images_loaded);

        if (++screen_images_loaded >= 2)
        {
            step++;
            FlushCache(0);
        }

        break;
    case BOOT_INSTALL_SHOW_INITIAL_PROMPT:
        lib_text_set_resource(message_text, g_boot_program.messages, BOOT_MSG_INSTALL_CONFIRM, 0);
        selection = 0;
        no_step = BOOT_INSTALL_LEAVE;
        yes_step = BOOT_INSTALL_WAIT_FOR_UNIT_RESOURCES;
        selection = 0;
        x = menu_cursor_x(selection);

        {
            LibSelectionCursor* arrow = cursor;
            ItemCreationClass185050& motion = *arrow;
            motion.position.x = x;
            motion.position.y = 256.0f;
            motion.unk35 = 1;
            arrow->unkae = 1;
        }
        choice_growing = 0;
        menu_frames = 0;
        step++;
        break;
    case BOOT_INSTALL_HANDLE_CHOICE:
        menu_frames++;

        if ((input->repeated & (BOOT_BUTTON_RIGHT | BOOT_BUTTON_LEFT)) && cursor->unk35)
        {
            selection = (selection + 1) & 1;
            choice_growing = 0;
            x = menu_cursor_x(selection);
            cursor->set_move_target(x, 256.0f, 0.05f);
            choice_growing = 0;
            resident_sound_play(g_sound, 0, 0, 0, 0x7F, 0x40, 0);
        }

        if (input->pressed & resource->confirm_buttons)
        {
            resident_sound_play(g_sound, 1, 0, 0, 0x7F, 0x40, 0);
            queue_fade();

            if (selection == 0)
            {
                step = yes_step;
            }
            else
            {
                step = no_step;
            }
        }
        else if (input->pressed & resource->cancel_buttons)
        {
            resident_sound_play(g_sound, 2, 0, 0, 0x7F, 0x40, 0);
            queue_fade();
            step = no_step;
        }

        break;
    case BOOT_INSTALL_LEAVE:
        if (exiting == 0)
        {
            resident_sound_stop_music(g_sound, 0, -1);
            resident_cancel_resource_requests(g_resource_queue, BOOT_RES_SOUND, 0, 0, -1, 0);
            resident_cancel_resource_requests(g_resource_queue, BOOT_RES_SYSTEM_FILES, 0, 0, -1, 0);
            resident_cancel_resource_requests(g_resource_queue, BOOT_RES_TIP_IMAGES, 0, 0, -1, 0);
            exiting = 1;
        }
        else if (resident_update_resource_queue(g_resource_queue) == 0 && g_resource_archive->read_busy == 0)
        {
            clear_to_black();

            for (s32 i = 0; i < 20; i++)
            {
                if (images[i] != 0)
                {
                    lib_object_detach_owner(images[i]);
                    images[i]->destroy();
                    images[i] = 0;
                }
            }

            if (container != 0)
            {
                container->destroy();
                container = 0;
            }

            if (message_text != 0)
            {
                message_text->destroy();
                message_text = 0;
            }

            if (progress_text != 0)
            {
                progress_text->destroy();
                progress_text = 0;
            }

            if (tip_text != 0)
            {
                tip_text->destroy();
                tip_text = 0;
            }

            if (cursor != 0)
            {
                cursor->destroy();
                cursor = 0;
            }

            if (tip_image != 0)
            {
                lib_object_detach_owner(tip_image);
                tip_image->destroy();
                tip_image = 0;
            }

            if (progress_bar != 0)
            {
                progress_bar->destroy();
                progress_bar = 0;
            }

            static_cast<LibUpdateList*>(D_001B6614)->append_node(new (0) BootTitleMenu(BOOT_TITLE_ITEM_INSTALL), -1);
            lib_object_detach_owner(this);
            destroy();
            return;
        }

        break;
    case BOOT_INSTALL_WAIT_FOR_UNIT_RESOURCES:
        if (resident_poll_resource_queue(g_resource_queue) != 0)
        {
            step++;
        }

        break;
    case BOOT_INSTALL_QUERY_UNIT:
        if (resident_archive_query_unit(g_resource_archive, 1, 1) != 0)
        {
            step = BOOT_INSTALL_WAIT_FOR_UNIT_STATUS;
        }
        else
        {
            step = BOOT_INSTALL_REQUEST_SPACE;
        }

        break;
    case BOOT_INSTALL_WAIT_FOR_UNIT_STATUS:
        if (resident_archive_is_busy(g_resource_archive) == 0)
        {
            if (resident_archive_get_command_result(g_resource_archive) != 0)
            {
                step = BOOT_INSTALL_REQUEST_SPACE;
            }
            else
            {
                resident_archive_start_command(g_resource_archive, 8, 0);
                step++;
            }
        }

        break;
    case BOOT_INSTALL_WAIT_FOR_UNIT_COMMAND:
        if (resident_archive_is_busy(g_resource_archive) == 0)
        {
            step++;
        }

        break;
    case BOOT_INSTALL_CHECK_UNIT_RESULT:
        resident_archive_query_unit(g_resource_archive, 0, 0);

        if (resident_archive_get_command_result(g_resource_archive) == 0)
        {
            step = BOOT_INSTALL_SHOW_OVERWRITE_PROMPT;
        }
        else
        {
            step = BOOT_INSTALL_REQUEST_SPACE;
        }

        break;
    case BOOT_INSTALL_SHOW_OVERWRITE_PROMPT:
        lib_text_set_resource(message_text, g_boot_program.messages, BOOT_MSG_OVERWRITE_CONFIRM, 0);
        yes_step = BOOT_INSTALL_REQUEST_SPACE;
        no_step = BOOT_INSTALL_SHOW_INITIAL_PROMPT;
        step = BOOT_INSTALL_HANDLE_CHOICE;

        if (cursor != 0)
        {
            selection = 1;
            x = menu_cursor_x(selection);
            cursor->set_move_target(x, 256.0f, 0.05f);
            choice_growing = 0;
        }

        break;
    case BOOT_INSTALL_REQUEST_SPACE:
        resident_archive_start_command(g_resource_archive, 2, 0);
        step++;
        break;
    case BOOT_INSTALL_WAIT_FOR_SPACE:
        if (resident_archive_is_busy(g_resource_archive) == 0)
        {
            if (resident_archive_get_command_result(g_resource_archive) != 0)
            {
                step = BOOT_INSTALL_SHOW_ERROR;
            }
            else
            {
                step++;
            }
        }

        break;
    case BOOT_INSTALL_CHECK_SPACE:
    {
        u32 needed = resident_archive_get_install_size(g_resource_archive);

        if (resident_archive_get_free_space(g_resource_archive) < needed)
        {
            step = BOOT_INSTALL_SHOW_NO_SPACE;
        }
        else
        {
            step = BOOT_INSTALL_WAIT_TO_BEGIN;
        }

        break;
    }
    case BOOT_INSTALL_SHOW_NO_SPACE:
        D_001B657C->message_arguments[0] = resident_archive_get_install_size(g_resource_archive) >> 11;
        lib_text_set_resource(message_text, g_boot_program.messages, BOOT_MSG_NOT_ENOUGH_SPACE, 0);
        step = BOOT_INSTALL_WAIT_FOR_ACKNOWLEDGEMENT;
        break;
    case BOOT_INSTALL_WAIT_TO_BEGIN:
        if (resident_poll_resource_queue(g_resource_queue) != 0)
        {
            queue_fade();
            step++;
        }

        break;
    case BOOT_INSTALL_PREPARE_FILES:
    {
        s32 sizes[3];
        lib_text_set_resource(message_text, g_boot_program.messages, BOOT_MSG_INSTALLING, 0);
        icon_header = (u8*)memalign(0x40, 0x200);
        progress_bar = new (0) BootProgressBar;
        progress_bar_reset(progress_bar, 0xF0, 0x18, 0x80FFFFFF, 0);
        tip_text = new (0) LibTextWidget(g_boot_program.messages, BOOT_MSG_FIRST_TIP, 1, 328.0f, 180.0f, 320.0f, 224.0f);
        tip_text->set_color(0x34130F);
        lib_container_attach_widget(container, tip_text);
        show_tip_image(0);
        tip_index = 1;
        next_tip_percent = BOOT_INSTALL_SECOND_TIP_PERCENT;
        D_001B657C->message_arguments[0] = 0;

        if (resource->widescreen)
        {
            progress_bar->model->set_translation(-366.0f, 180.0f, 0.0f);
            progress_text = new (0) LibTextWidget(g_boot_program.messages, BOOT_MSG_PERCENT, 1, 240.0f, 438.0f, 512.0f, 32.0f);
            progress_text->set_color(0x34130F);
        }
        else
        {
            progress_bar->model->set_translation(-280.0f, 180.0f, 0.0f);
            progress_text = new (0) LibTextWidget(g_boot_program.messages, BOOT_MSG_PERCENT, 1, 290.0f, 432.0f, 512.0f, 32.0f);
            progress_text->set_color(0x34130F);
        }

        lib_container_attach_widget(container, progress_text);
        ResidentResourceHeader* header = (ResidentResourceHeader*)system_file_data;

        for (s32 i = 0; i < 3; i++)
        {
            sizes[i] = header->decoded_size;
            system_file_buffers[i] = (u8*)memalign(0x200, header->decoded_size + 0x200);
            memset_guess(system_file_buffers[i], 0, header->decoded_size + 0x200);
            resident_decode_resource_block(g_resident_resource_decoder, header, system_file_buffers[i], 0);
            header = (ResidentResourceHeader*)((u8*)header + header->next_offset);
        }

        resident_archive_set_system_files(g_resource_archive, icon_header, system_file_buffers[0], sizes[0], system_file_buffers[1], sizes[1], system_file_buffers[2], sizes[2],
                    system_file_buffers[2], sizes[2]);
        header = (ResidentResourceHeader*)navigator_file_data;

        for (s32 i = 0; i < 3; i++)
        {
            sizes[i] = header->decoded_size;
            navigator_file_buffers[i] = (u8*)memalign(0x200, header->decoded_size + 0x200);
            memset_guess(navigator_file_buffers[i], 0, header->decoded_size + 0x200);
            resident_decode_resource_block(g_resident_resource_decoder, header, navigator_file_buffers[i], 0);
            header = (ResidentResourceHeader*)((u8*)header + header->next_offset);
        }

        resident_archive_set_navigator_files(g_resource_archive, navigator_file_buffers[0], sizes[0], navigator_file_buffers[1], sizes[1], navigator_file_buffers[2], sizes[2]);
        resident_archive_start_command(g_resource_archive, 1, 0);
        step++;
        break;
    }
    case BOOT_INSTALL_WAIT_FOR_FILES:
        if (resident_archive_is_busy(g_resource_archive) == 0)
        {
            free_guess(system_file_buffers[0]);
            free_guess(system_file_buffers[1]);
            free_guess(system_file_buffers[2]);
            system_file_buffers[0] = 0;
            system_file_buffers[1] = 0;
            system_file_buffers[2] = 0;

            if (resident_archive_get_command_result(g_resource_archive) != 0)
            {
                step = BOOT_INSTALL_SHOW_ERROR;
            }
            else
            {
                resident_archive_start_command(g_resource_archive, 3, 0);
                step++;
            }
        }

        break;
    case BOOT_INSTALL_START_COPY:
        if (resident_archive_is_busy(g_resource_archive) == 0)
        {
            if (resident_archive_get_command_result(g_resource_archive) != 0)
            {
                step = BOOT_INSTALL_SHOW_ERROR;
            }
            else
            {
                install_buffer = (u8*)memalign(0x40, 0x200000);
                FlushCache(0);
                resident_archive_set_copy_buffer(g_resource_archive, install_buffer);
                g_resource_archive->copy_paused = 0;
                resident_archive_start_command(g_resource_archive, 5, 0);
                install_total = resident_archive_get_install_words(g_resource_archive) * 4;
                step++;
            }
        }

        break;
    case BOOT_INSTALL_COPY_PROGRESS:
        if (resident_archive_is_busy(g_resource_archive) == 0)
        {
            if (resident_archive_get_command_result(g_resource_archive) != 0)
            {
                step = BOOT_INSTALL_SHOW_ERROR;
            }
            else
            {
                step = BOOT_INSTALL_FINISH_COPY;
            }
        }
        else
        {
            remaining = resident_archive_get_copy_remaining(g_resource_archive);
            percent = 99 - remaining * 99 / install_total;
            D_001B657C->message_arguments[0] = percent;
            lib_text_set_resource(progress_text, g_boot_program.messages, BOOT_MSG_PERCENT, 0);

            if (percent >= next_tip_percent && tip_index < BOOT_INSTALL_TIP_COUNT)
            {
                show_tip_image(tip_index);
                lib_text_set_resource(tip_text, g_boot_program.messages, tip_index + BOOT_MSG_FIRST_TIP, 0);
                tip_index++;
                next_tip_percent = tip_index * 100 / BOOT_INSTALL_TIP_COUNT;
            }

            progress_bar_draw(progress_bar, install_total - remaining, install_total);

            if (input->pressed & resource->cancel_buttons)
            {
                lib_text_set_resource(message_text, g_boot_program.messages, BOOT_MSG_ABORT_CONFIRM, 0);
                resident_sound_play(g_sound, 2, 0, 0, 0x7F, 0x40, 0);
                queue_fade();
                g_resource_archive->copy_paused = 1;
                selection = 1;
                x = menu_cursor_x(selection);
                cursor = new (0) LibSelectionCursor;
                cursor->init(1, 0, 0, x, 256.0f, 0.0f);
                lib_queue_display_object(D_001B657C,
                                         reinterpret_cast<LibTransformOwner*>(static_cast<LibTransformOwner*>(cursor)));
                tip_text->visible = 0;
                tip_image->model->draw_flags |= LIB_DRAW_HIDDEN;
                step = BOOT_INSTALL_HANDLE_CHOICE;
                yes_step = BOOT_INSTALL_ABORT_COPY;
                no_step = BOOT_INSTALL_RESUME_COPY;
            }
        }

        break;
    case BOOT_INSTALL_FINISH_COPY:
        D_001B657C->message_arguments[0] = 100;
        lib_text_set_resource(progress_text, g_boot_program.messages, BOOT_MSG_PERCENT, 0);
        progress_bar_draw(progress_bar, 100, 100);
        resident_archive_set_copy_buffer(g_resource_archive, 0);

        if (install_buffer != 0)
        {
            free_guess(install_buffer);
            install_buffer = 0;
        }

        resident_archive_start_command(g_resource_archive, 4, 0);
        step++;
        break;
    case BOOT_INSTALL_WAIT_FOR_FINISH:
        if (resident_archive_is_busy(g_resource_archive) == 0)
        {
            resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
            queue_fade();
            step++;
        }

        break;
    case BOOT_INSTALL_SHOW_COMPLETE:
        lib_text_set_resource(message_text, g_boot_program.messages, BOOT_MSG_INSTALL_COMPLETE, 0);
        tip_text->visible = 0;
        tip_image->model->draw_flags |= LIB_DRAW_HIDDEN;
        step = BOOT_INSTALL_WAIT_FOR_ACKNOWLEDGEMENT;
        break;
    case BOOT_INSTALL_SHOW_ERROR:
        if (resident_archive_has_unit_error(g_resource_archive))
        {
            if (tip_text != 0)
            {
                tip_text->destroy();
                tip_text = 0;
            }

            if (tip_image != 0)
            {
                lib_object_detach_owner(tip_image);
                tip_image->destroy();
                tip_image = 0;
            }

            lib_text_set_resource(message_text, g_boot_program.messages, BOOT_MSG_UNIT_ERROR, 0);
            resident_archive_clear_unit_error(g_resource_archive);
        }
        else
        {
            lib_text_set_resource(message_text, g_boot_program.messages, BOOT_MSG_ERROR, 0);
        }

        step = BOOT_INSTALL_WAIT_FOR_ACKNOWLEDGEMENT;
        break;
    case BOOT_INSTALL_WAIT_FOR_ACKNOWLEDGEMENT:
        if (input->pressed & resource->confirm_buttons)
        {
            resident_sound_play(g_sound, 1, 0, 0, 0x7F, 0x40, 0);
            queue_fade();
            step = BOOT_INSTALL_RETURN_TO_TITLE;
        }

        break;
    case BOOT_INSTALL_RETURN_TO_TITLE:
        resident_sound_stop_music(g_sound, 0, -1);
        clear_to_black();

        for (s32 i = 0; i < 20; i++)
        {
            if (images[i] != 0)
            {
                lib_object_detach_owner(images[i]);
                images[i]->destroy();
                images[i] = 0;
            }
        }

        if (container != 0)
        {
            container->destroy();
            container = 0;
        }

        if (message_text != 0)
        {
            message_text->destroy();
            message_text = 0;
        }

        if (progress_text != 0)
        {
            progress_text->destroy();
            progress_text = 0;
        }

        if (tip_text != 0)
        {
            tip_text->destroy();
            tip_text = 0;
        }

        if (cursor != 0)
        {
            cursor->destroy();
            cursor = 0;
        }

        if (progress_bar != 0)
        {
            lib_object_detach_owner(progress_bar);
            progress_bar->destroy();
            progress_bar = 0;
        }

        if (tip_image != 0)
        {
            lib_object_detach_owner(tip_image);
            tip_image->destroy();
            tip_image = 0;
        }

        static_cast<LibUpdateList*>(D_001B6614)->append_node(new (0) BootTitleMenu(BOOT_TITLE_ITEM_AUTO), -1);
        lib_object_detach_owner(this);
        destroy();
        return;
    case BOOT_INSTALL_RESUME_COPY:
        tip_text->visible = 1;
        tip_image->model->draw_flags &= ~LIB_DRAW_HIDDEN;
        lib_text_set_resource(message_text, g_boot_program.messages, BOOT_MSG_INSTALLING, 0);
        g_resource_archive->copy_paused = 0;
        step = BOOT_INSTALL_COPY_PROGRESS;
        break;
    case BOOT_INSTALL_ABORT_COPY:
        if (tip_text != 0)
        {
            tip_text->destroy();
            tip_text = 0;
        }

        if (tip_image != 0)
        {
            lib_object_detach_owner(tip_image);
            tip_image->destroy();
            tip_image = 0;
        }

        queue_fade();
        g_resource_archive->copy_paused = 0;
        resident_archive_cancel_command(g_resource_archive);
        step++;
        wait_frames = 0;
        break;
    case BOOT_INSTALL_WAIT_FOR_ABORT:
        wait_frames++;

        if (resident_archive_is_busy(g_resource_archive) == 0)
        {
            resident_archive_start_command(g_resource_archive, 4, 0);
            step++;
        }

        if (wait_frames >= BOOT_INSTALL_ABORT_TIMEOUT_FRAMES)
        {
            ResidentArchive* archive = g_resource_archive;
            archive->unit_ready = 0;
            archive->unit_state = 3;
            step = BOOT_INSTALL_RETURN_FROM_ABORT;
        }

        break;
    case BOOT_INSTALL_FINISH_ABORT:
        if (resident_archive_is_busy(g_resource_archive) == 0)
        {
            resident_archive_start_command(g_resource_archive, 2, 0);
            step++;
        }

        break;
    case BOOT_INSTALL_WAIT_FOR_ABORT_FINISH:
        if (resident_archive_is_busy(g_resource_archive) == 0)
        {
            step++;
        }

        break;
    case BOOT_INSTALL_RETURN_FROM_ABORT:
        if (resident_archive_is_unit_ready(g_resource_archive) != 0)
        {
            step = BOOT_INSTALL_SHOW_INITIAL_PROMPT;
            selection = 0;
            x = menu_cursor_x(selection);
            cursor = new (0) LibSelectionCursor;
            cursor->init(1, 0, 0, x, 256.0f, 0.0f);
            lib_queue_display_object(D_001B657C, reinterpret_cast<LibTransformOwner*>(static_cast<LibTransformOwner*>(cursor)));
        }
        else
        {
            step = BOOT_INSTALL_LEAVE;
        }

        if (progress_text != 0)
        {
            progress_text->destroy();
            progress_text = 0;
        }

        if (tip_text != 0)
        {
            tip_text->destroy();
            tip_text = 0;
        }

        if (tip_image != 0)
        {
            lib_object_detach_owner(tip_image);
            tip_image->destroy();
            tip_image = 0;
        }

        if (progress_bar != 0)
        {
            lib_object_detach_owner(progress_bar);
            progress_bar->destroy();
            progress_bar = 0;
        }

        break;
    }

    if (exiting == 0 && step > 0 && sound_started == 0 && resident_find_resource_request(g_resource_queue, BOOT_RES_SOUND, 0, 0, -1, 0) == 0)
    {
        resident_sound_load_bank(g_sound, sound_data, 1, 0);
        sound_started = 1;
    }

    place_screen_images();
    update_choice_images();
}

/** @brief Destroy the transform receiver. */
LibCallbackTransform::~LibCallbackTransform()
{
}

/** @brief Destroy the list receiver. */
LibListReceiver::~LibListReceiver()
{
}

#include "overlays/boot/transform_inlines.h"

/** @brief Release the owned objects and buffers. */
BootInstaller::~BootInstaller()
{
    delete screen_image_data;

    for (s32 i = 0; i < 2; i++)
    {
        delete screen_image_buffers[i];
    }

    for (s32 i = 0; i < 20; i++)
    {
        if (images[i] != 0)
        {
            lib_object_detach_owner(images[i]);
            images[i]->destroy();
        }
    }

    if (tip_image != 0)
    {
        lib_object_detach_owner(tip_image);
        tip_image->destroy();
    }

    if (progress_bar != 0)
    {
        lib_object_detach_owner(progress_bar);
        progress_bar->destroy();
    }

    if (container != 0)
    {
        container->destroy();
    }

    if (message_text != 0)
    {
        message_text->destroy();
    }

    if (progress_text != 0)
    {
        progress_text->destroy();
    }

    if (tip_text != 0)
    {
        tip_text->destroy();
    }

    if (cursor != 0)
    {
        cursor->destroy();
    }

    delete tip_image_data;
    delete unkbc;
    delete system_file_data;
    delete navigator_file_data;
    delete install_buffer;
    delete icon_header;
    delete system_file_buffers[0];
    delete system_file_buffers[1];
    delete system_file_buffers[2];

    if (tip_image_buffer != 0)
    {
        resident_queue_allocation_release(g_resident_release_queues, tip_image_buffer);
    }

    delete navigator_file_buffers[0];
    delete navigator_file_buffers[1];
    delete navigator_file_buffers[2];
    resident_sound_stop_music(g_sound, 0, -1);
    delete sound_data;
    g_boot_program.error_popup->set_enabled(1);
}

/**
 * @brief Turn the popup on or off.
 * @param value Nonzero to allow the popup.
 */
void BootUnitErrorPopup::set_enabled(u8 value)
{
    enabled = value;
}

/** @brief Allocate the boot buffers and clear the owned objects. */
BootInstaller::BootInstaller()
{
    s32 i;
    screen_image_data = (u8*)memalign(0x40, resident_get_resource_size(g_resource_archive, BOOT_RES_SCREEN_IMAGES));
    resident_queue_resource_request(g_resource_queue, BOOT_RES_SCREEN_IMAGES, screen_image_data,
                                    BOOT_RESOURCE_TAG, BOOT_RESOURCE_PRIORITY, 0, 0, 0, BOOT_RESOURCE_READ);
    sound_data = (u8*)memalign(0x40, resident_get_resource_size(g_resource_archive, BOOT_RES_SOUND));
    tip_image_data = (u8*)memalign(0x40, resident_get_resource_size(g_resource_archive, BOOT_RES_TIP_IMAGES));
    step = BOOT_INSTALL_WAIT_FOR_RESOURCES;

    for (i = 0; i < 2; i++)
    {
        screen_image_buffers[i] = 0;
    }

    for (i = 0; i < 20; i++)
    {
        images[i] = 0;
    }

    tip_image = 0;
    icon_header = 0;
    progress_bar = 0;
    container = 0;
    message_text = 0;
    progress_text = 0;
    tip_text = 0;
    cursor = 0;
    sound_started = 0;
    exiting = 0;
    g_boot_program.error_popup->set_enabled(0);
    tip_image_buffer = 0;
    system_file_buffers[0] = 0;
    system_file_buffers[1] = 0;
    system_file_buffers[2] = 0;
    install_buffer = 0;
    unkbc = 0;
    navigator_file_buffers[0] = 0;
    navigator_file_buffers[1] = 0;
    navigator_file_buffers[2] = 0;
    system_file_data = new (0) u8[resident_get_resource_size(g_resource_archive, BOOT_RES_SYSTEM_FILES)];
    navigator_file_data = new (0) u8[resident_get_resource_size(g_resource_archive, BOOT_RES_NAVIGATOR_FILES)];
    selection = 0;
    screen_images_loaded = 0;
}

/**
 * @brief Default DMA notification hook; does nothing.
 * @param value Notification value.
 */
void LibDmaCallbacks::on_packet_notify(u32 value)
{
}

/**
 * @brief Default preparation hook; does nothing.
 * @param value Notification word or packet address.
 */
void LibDmaCallbacks::on_packet_complete(u32 value)
{
}

/**
 * @brief Copy the position.
 * @param value Source vector.
 */
void LibPositionTransform::copy_translation(const LibVector4* value)
{
    copy_vector(&translation, value);
}

/**
 * @brief Copy the position.
 * @param value Source vector.
 */
void LibPositionTransform::set_translation_vector(const LibVector4* value)
{
    copy_vector(&translation, value);
}

/**
 * @brief Set the position and a w component of one.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void LibPositionTransform::set_translation(float x, float y, float z)
{
    translation.x = x;
    translation.y = y;
    translation.z = z;
    translation.w = 1.0f;
}

/**
 * @brief Report the list kind used when registration requests the default.
 * @return Three in the base implementation.
 */
s32 LibListObject::get_default_list_kind()
{
    return 3;
}

/** @brief Advance this registered object's state; the base implementation does nothing. */
void LibListObject::update()
{
}

/**
 * @brief Copy the position and mark the transform dirty.
 * @param value Source vector.
 */
void LibOrientedTransform::copy_translation(const LibVector4* value)
{
    transform_dirty = 1;
    copy_vector(&translation, value);
}

/**
 * @brief Copy the position and mark the transform dirty.
 * @param value Source vector.
 */
void LibOrientedTransform::set_translation_vector(const LibVector4* value)
{
    transform_dirty = 1;
    copy_vector(&translation, value);
}

/**
 * @brief Set all four rotation components and mark the transform dirty.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 * @param w Fourth component.
 */
void LibOrientedTransform::set_orientation_components(float x, float y, float z, float w)
{
    transform_dirty = 1;
    orientation.x = x;
    orientation.y = y;
    orientation.z = z;
    orientation.w = w;
}

/**
 * @brief Copy the rotation vector and mark the transform dirty.
 * @param value Source vector.
 */
void LibOrientedTransform::copy_orientation(const LibVector4* value)
{
    transform_dirty = 1;
    copy_vector(&orientation, value);
}

/**
 * @brief Copy the rotation vector and mark the transform dirty.
 * @param value Source vector.
 */
void LibOrientedTransform::set_orientation(const LibVector4* value)
{
    transform_dirty = 1;
    copy_vector(&orientation, value);
}

/**
 * @brief Convert a rotation into the rotation vector and mark the transform dirty.
 * @param value Source rotation.
 */
void LibOrientedTransform::convert_rotation(const LibVector4* value)
{
    transform_dirty = 1;
    lib_quaternion_from_euler(reinterpret_cast<FieldVec4B*>(&orientation), &value->x);
}

/**
 * @brief Convert a rotation into the rotation vector and mark the transform dirty.
 * @param value Source rotation.
 */
void LibOrientedTransform::set_rotation_vector(const LibVector4* value)
{
    transform_dirty = 1;
    lib_quaternion_from_euler(reinterpret_cast<FieldVec4B*>(&orientation), &value->x);
}

/**
 * @brief Convert three rotation components into the rotation vector and mark the transform dirty.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void LibOrientedTransform::set_rotation(float x, float y, float z)
{
    transform_dirty = 1;
    LibVector4 value;
    value.x = x;
    value.y = y;
    value.z = z;
    value.w = 1.0f;
    lib_quaternion_from_euler(reinterpret_cast<FieldVec4B*>(&orientation), &value.x);
}

/**
 * @brief Copy the scale vector and mark the transform dirty.
 * @param value Source vector.
 */
void LibOrientedTransform::copy_scale(const LibVector4* value)
{
    transform_dirty = 1;
    copy_vector(&scale, value);
}

/**
 * @brief Copy the scale vector and mark the transform dirty.
 * @param value Source vector.
 */
void LibOrientedTransform::set_scale_vector(const LibVector4* value)
{
    transform_dirty = 1;
    copy_vector(&scale, value);
}

/** @brief Draw in the main list (bucket zero). */
void LibTransformOwner::set_default_draw_bucket()
{
    draw_bucket = 0;
}

/** @brief Virtual slot 4; the owner's implementation does nothing. */
void LibTransformOwner::render()
{
}

/**
 * @brief Give the centre for Lib's oriented-box visibility test; this owner has none.
 * @param output Receives the centre in local space.
 * @return Nonzero when a centre was written; zero here, so the test is skipped.
 */
s32 LibTransformOwner::get_box_cull_center(void* output)
{
    return 0;
}

/**
 * @brief Fade the owner as it nears the camera; Lib calls this for owners with draw flag 0x800. This owner doesn't fade.
 * @param value Distance in front of the camera over the fade range, clamped to one.
 * @param mode Two from Lib's caller; unused here.
 * @return Whether the value is negative.
 */
s32 LibTransformOwner::set_fade_alpha(float value, float mode)
{
    s32 result = 1;
    if (!(value < 0.0f))
    {
        result = 0;
    }
    return result;
}

/**
 * @brief Return the bounding sphere Lib culls against (centre in xyz, radius in w); this owner has Lib's shared default.
 * @return Bounding sphere.
 */
const LibVector4* LibTransformOwner::get_bounding_sphere()
{
    return &g_default_bounding_sphere;
}

/**
 * @brief Default matrix handler; does nothing.
 * @param matrix Matrix supplied by the caller.
 * @param context Opaque caller context.
 */
void LibTransformOwner::build_packet(const void* matrix, void* context)
{
}

/**
 * @brief Make a copy of this object that stays linked to it; this owner can't be copied.
 * @return The copy, or null.
 */
LibTransformOwner* LibTransformOwner::clone()
{
    return 0;
}

/** @brief Unlink a copy from its original and queue it for release; this owner never has copies, so it does nothing. */
void LibTransformOwner::release_clone()
{
}

/** @brief Default dispatch slot; does nothing. */
void ItemCreationClass185050::func_slot0c()
{
}
