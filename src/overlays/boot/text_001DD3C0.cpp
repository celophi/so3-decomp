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
extern BootVector4DDAA0 D_50CD30;
void func_4CE4C0(void* destination, const float* source);
void func_1126D0(void* request, u8* data, s32 first, s32 second);
void func_1152C0(BootResident1B65E4* resident, u8* first, s32 first_size, u8* second, s32 second_size, u8* third, s32 third_size);
void func_1152E0(BootResident1B65E4* resident, u8* buffer, u8* first, s32 first_size, u8* second, s32 second_size, u8* third, s32 third_size, u8* fourth,
                 s32 fourth_size);
void func_115420(BootResident1B65E4* resident);
s32 func_115460(BootResident1B65E4* resident, s32 first, s32 second);
s32 func_115640(BootResident1B65E4* resident);
s32 func_115660(BootResident1B65E4* resident);
void func_1156B0(BootResident1B65E4* resident, u8* buffer);
void func_1156C0(BootResident1B65E4* resident);
void func_115810(BootResident1B65E4* resident, s32 command, s32 argument);
u32 func_115830(BootResident1B65E4* resident);
u32 func_115840(BootResident1B65E4* resident);
s32 func_1158A0(BootResident1B65E4* resident);
void func_139928(void* allocation);
void lib_container_attach_widget(BootContainer* container, BootTextWidget* child);
void lib_text_set_resource(BootTextWidget* text, s32 slot, u32 key, u8 flag);
}

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
void BootListObject::destroy()
{
    delete this;
}

/** @brief Virtual slot 4; the base implementation does nothing. */
void BootListObject::render()
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
        resident_queue_allocation_release(D_001B65F4, tip_image_buffer);
        tip_image_buffer = 0;
    }

    tip_image_buffer = func_102920(D_001B65EC, tip_image_data, index, 1);
    func_1025A0(D_001B65EC, tip_image_data, (void*)(((u32)tip_image_buffer + 0x7F) & ~0x7F), index);
    tip_image = new (0) BootImage;
    tip_image->set_texture((const BootTextureResource*)(((u32)tip_image_buffer + 0x7F) & ~0x7F), 0);
    resident_find_entry(resident_get_entry_table(resident_get_runtime_owner()), 1);
    tip_image->set_rectangle(0, 1, 0x120, 0xC9, 0x80808080, 0);
    tip_image->model->set_translation(-296.0f, -64.0f, 0.0f);
}

/**
 * @brief Set the position and a w component of one, and mark the transform dirty.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void BootTransform::set_translation(float x, float y, float z)
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

    if (step >= 0xE && images[4] != 0)
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
        images[4]->set_texture((const BootTextureResource*)(((u32)screen_image_buffers[0] + 0x7F) & ~0x7F), 0);
        images[4]->set_rectangle(0x1E, 0x131, 0x4C, 0x26, 0x80808080, 0);
        images[5] = new (0) BootImage;
        images[5]->set_texture((const BootTextureResource*)(((u32)screen_image_buffers[0] + 0x7F) & ~0x7F), 0);
        images[5]->set_rectangle(0x1E, 0x167, 0x4C, 0x26, 0x80808080, 0);
    }

    if (((BootSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_runtime_owner()), 1))->widescreen)
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
            BootModel* model = images[4 + i]->model;

            if (selection == i)
            {
                BootVector4DDAA0 scale;
                copy_vector(&scale, &model->base_color_factor);

                if (choice_growing == 0)
                {
                    scale.x -= 0.01f * D_001B6688;
                    scale.y -= 0.005f * D_001B6688;

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
                    scale.x += 0.01f * D_001B6688;
                    scale.y += 0.005f * D_001B6688;

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
                BootVector4DDAA0 scale;
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
void BootColorModel::update_combined_color_factor()
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
        images[0]->set_texture((const BootTextureResource*)(((u32)screen_image_buffers[0] + 0x7F) & ~0x7F), 0);
        images[0]->set_rectangle(0, 1, 0x1E8, 0xDF, 0x80808080, 0);
        images[0]->model->set_translation(-244.0f, -112.0f, 0.0f);
    }

    if (images[1] == 0)
    {
        images[1] = new (0) BootImage;
        images[1]->set_texture((const BootTextureResource*)(((u32)screen_image_buffers[1] + 0x7F) & ~0x7F), 0);
        images[1]->set_rectangle(0, 0, 0x280, 0x50, 0x80808080, 0);
        images[1]->model->set_translation(-312.0f, -216.0f, 0.0f);
    }

    if (images[2] == 0)
    {
        images[2] = new (0) BootImage;
        images[2]->set_texture((const BootTextureResource*)(((u32)screen_image_buffers[0] + 0x7F) & ~0x7F), 0);
        images[2]->set_rectangle(0, 0xEA, 0xC8, 0x1D, 0x80808080, 0);
    }

    if (images[3] == 0)
    {
        images[3] = new (0) BootImage;
        images[3]->set_texture((const BootTextureResource*)(((u32)screen_image_buffers[0] + 0x7F) & ~0x7F), 0);
        images[3]->set_rectangle(0x1B, 0x190, 0x1B6, 0x31, 0x80808080, 0);
    }

    if (((BootSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_runtime_owner()), 1))->widescreen)
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
void BootTransform::set_scale(float x, float y, float z)
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
    resource = (BootSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_runtime_owner()), 1);

    switch (step)
    {
    case 0:
        if (func_102D00(D_001B65E8) != 0)
        {
            func_103E70(D_001B65E8, BOOT_RES_SOUND, sound_data, 1, 0x34BC0, 0, 0, 0, 1);
            func_103E70(D_001B65E8, BOOT_RES_SYSTEM_FILES, system_file_data, 1, 0x34BC0, 0, 0, 0, 1);
            func_103E70(D_001B65E8, BOOT_RES_NAVIGATOR_FILES, navigator_file_data, 1, 0x34BC0, 0, 0, 0, 1);
            func_103E70(D_001B65E8, BOOT_RES_TIP_IMAGES, tip_image_data, 1, 0x34BC0, 0, 0, 0, 1);
            func_4DF6E0(g_boot_program.display, 0x49, 0x47, 0x9D, 0x7F);
            D_001B661C->prepend_node(new (0) BootClass179150, -1);
            screen_images_loaded = 0;
            step++;
            container = new (0) BootContainer(9, 0.0f, 0.0f, 0.0f);
            func_465B20(D_001B657C, container);
            message_text = new (0) BootTextWidget(g_boot_program.messages, BOOT_MSG_INSTALL_CONFIRM, 1, 48.0f, 88.0f, 512.0f, 224.0f);
            message_text->set_color(0x34130F);
            lib_container_attach_widget(container, message_text);
            x = menu_cursor_x(selection);
            cursor = new (0) BootSelectionCursor;
            func_467570(cursor, 1, 0, 0, x, 256.0f, 0.0f);
            func_465B20(D_001B657C, cursor);
        }

        break;
    case 1:
        screen_image_buffers[screen_images_loaded] = func_102920(D_001B65EC, screen_image_data, screen_images_loaded, 1);
        func_1025A0(D_001B65EC, screen_image_data, (void*)(((u32)screen_image_buffers[screen_images_loaded] + 0x7F) & ~0x7F), screen_images_loaded);

        if (++screen_images_loaded >= 2)
        {
            step++;
            FlushCache(0);
        }

        break;
    case 2:
        lib_text_set_resource(message_text, g_boot_program.messages, BOOT_MSG_INSTALL_CONFIRM, 0);
        selection = 0;
        no_step = 4;
        yes_step = 5;
        selection = 0;
        x = menu_cursor_x(selection);

        {
            BootSelectionCursor* arrow = cursor;
            ItemCreationClass185050& motion = *arrow;
            motion.unk10 = x;
            motion.unk14 = 256.0f;
            motion.unk35 = 1;
            arrow->unkae = 1;
        }
        choice_growing = 0;
        menu_frames = 0;
        step++;
        break;
    case 3:
        menu_frames++;

        if ((input->repeated & 0xA0) && cursor->unk35)
        {
            selection = (selection + 1) & 1;
            choice_growing = 0;
            x = menu_cursor_x(selection);
            cursor->func_00466E40(x, 256.0f, 0.05f);
            choice_growing = 0;
            func_112400(D_001B65F8, 0, 0, 0, 0x7F, 0x40, 0);
        }

        if (input->pressed & resource->confirm_buttons)
        {
            func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
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
            func_112400(D_001B65F8, 2, 0, 0, 0x7F, 0x40, 0);
            queue_fade();
            step = no_step;
        }

        break;
    case 4:
        if (exiting == 0)
        {
            func_10F000(D_001B65F8, 0, -1);
            resident_cancel_resource_requests(D_001B65E8, BOOT_RES_SOUND, 0, 0, -1, 0);
            resident_cancel_resource_requests(D_001B65E8, BOOT_RES_SYSTEM_FILES, 0, 0, -1, 0);
            resident_cancel_resource_requests(D_001B65E8, BOOT_RES_TIP_IMAGES, 0, 0, -1, 0);
            exiting = 1;
        }
        else if (resident_update_resource_queue(D_001B65E8) == 0 && D_001B65E4->unk12183 == 0)
        {
            func_4DF6E0(g_boot_program.display, 0, 0, 0, 0x7F);

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

            static_cast<BootUpdateList*>(D_001B6614)->append_node(new (0) BootTitleMenu(3), -1);
            lib_object_detach_owner(this);
            destroy();
            return;
        }

        break;
    case 5:
        if (func_102D00(D_001B65E8) != 0)
        {
            step++;
        }

        break;
    case 6:
        if (func_115460(D_001B65E4, 1, 1) != 0)
        {
            step = 7;
        }
        else
        {
            step = 0xB;
        }

        break;
    case 7:
        if (func_115650(D_001B65E4) == 0)
        {
            if (func_115640(D_001B65E4) != 0)
            {
                step = 0xB;
            }
            else
            {
                func_115810(D_001B65E4, 8, 0);
                step++;
            }
        }

        break;
    case 8:
        if (func_115650(D_001B65E4) == 0)
        {
            step++;
        }

        break;
    case 9:
        func_115460(D_001B65E4, 0, 0);

        if (func_115640(D_001B65E4) == 0)
        {
            step = 0xA;
        }
        else
        {
            step = 0xB;
        }

        break;
    case 10:
        lib_text_set_resource(message_text, g_boot_program.messages, BOOT_MSG_OVERWRITE_CONFIRM, 0);
        yes_step = 0xB;
        no_step = 2;
        step = 3;

        if (cursor != 0)
        {
            selection = 1;
            x = menu_cursor_x(selection);
            cursor->func_00466E40(x, 256.0f, 0.05f);
            choice_growing = 0;
        }

        break;
    case 11:
        func_115810(D_001B65E4, 2, 0);
        step++;
        break;
    case 12:
        if (func_115650(D_001B65E4) == 0)
        {
            if (func_115640(D_001B65E4) != 0)
            {
                step = 0x14;
            }
            else
            {
                step++;
            }
        }

        break;
    case 13:
    {
        u32 needed = func_115840(D_001B65E4);

        if (func_115830(D_001B65E4) < needed)
        {
            step = 0xE;
        }
        else
        {
            step = 0xF;
        }

        break;
    }
    case 14:
        D_001B657C->message_value = func_115840(D_001B65E4) >> 11;
        lib_text_set_resource(message_text, g_boot_program.messages, BOOT_MSG_NOT_ENOUGH_SPACE, 0);
        step = 0x15;
        break;
    case 15:
        if (func_102D00(D_001B65E8) != 0)
        {
            queue_fade();
            step++;
        }

        break;
    case 16:
    {
        s32 sizes[3];
        lib_text_set_resource(message_text, g_boot_program.messages, BOOT_MSG_INSTALLING, 0);
        icon_header = func_139700(0x40, 0x200);
        progress_bar = new (0) BootProgressBar;
        progress_bar_reset(progress_bar, 0xF0, 0x18, 0x80FFFFFF, 0);
        tip_text = new (0) BootTextWidget(g_boot_program.messages, BOOT_MSG_FIRST_TIP, 1, 328.0f, 180.0f, 320.0f, 224.0f);
        tip_text->set_color(0x34130F);
        lib_container_attach_widget(container, tip_text);
        show_tip_image(0);
        tip_index = 1;
        next_tip_percent = 0xC;
        D_001B657C->message_value = 0;

        if (resource->widescreen)
        {
            progress_bar->model->set_translation(-366.0f, 180.0f, 0.0f);
            progress_text = new (0) BootTextWidget(g_boot_program.messages, BOOT_MSG_PERCENT, 1, 240.0f, 438.0f, 512.0f, 32.0f);
            progress_text->set_color(0x34130F);
        }
        else
        {
            progress_bar->model->set_translation(-280.0f, 180.0f, 0.0f);
            progress_text = new (0) BootTextWidget(g_boot_program.messages, BOOT_MSG_PERCENT, 1, 290.0f, 432.0f, 512.0f, 32.0f);
            progress_text->set_color(0x34130F);
        }

        lib_container_attach_widget(container, progress_text);
        ResidentResourceHeader* header = (ResidentResourceHeader*)system_file_data;

        for (s32 i = 0; i < 3; i++)
        {
            sizes[i] = header->decoded_size;
            system_file_buffers[i] = func_139700(0x200, header->decoded_size + 0x200);
            func_13A678(system_file_buffers[i], 0, header->decoded_size + 0x200);
            func_1025A0(D_001B65EC, (u8*)header, system_file_buffers[i], 0);
            header = (ResidentResourceHeader*)((u8*)header + header->next_offset);
        }

        func_1152E0(D_001B65E4, icon_header, system_file_buffers[0], sizes[0], system_file_buffers[1], sizes[1], system_file_buffers[2], sizes[2],
                    system_file_buffers[2], sizes[2]);
        header = (ResidentResourceHeader*)navigator_file_data;

        for (s32 i = 0; i < 3; i++)
        {
            sizes[i] = header->decoded_size;
            navigator_file_buffers[i] = func_139700(0x200, header->decoded_size + 0x200);
            func_13A678(navigator_file_buffers[i], 0, header->decoded_size + 0x200);
            func_1025A0(D_001B65EC, (u8*)header, navigator_file_buffers[i], 0);
            header = (ResidentResourceHeader*)((u8*)header + header->next_offset);
        }

        func_1152C0(D_001B65E4, navigator_file_buffers[0], sizes[0], navigator_file_buffers[1], sizes[1], navigator_file_buffers[2], sizes[2]);
        func_115810(D_001B65E4, 1, 0);
        step++;
        break;
    }
    case 17:
        if (func_115650(D_001B65E4) == 0)
        {
            func_139928(system_file_buffers[0]);
            func_139928(system_file_buffers[1]);
            func_139928(system_file_buffers[2]);
            system_file_buffers[0] = 0;
            system_file_buffers[1] = 0;
            system_file_buffers[2] = 0;

            if (func_115640(D_001B65E4) != 0)
            {
                step = 0x14;
            }
            else
            {
                func_115810(D_001B65E4, 3, 0);
                step++;
            }
        }

        break;
    case 18:
        if (func_115650(D_001B65E4) == 0)
        {
            if (func_115640(D_001B65E4) != 0)
            {
                step = 0x14;
            }
            else
            {
                install_buffer = func_139700(0x40, 0x200000);
                FlushCache(0);
                func_1156B0(D_001B65E4, install_buffer);
                D_001B65E4->unk13b = 0;
                func_115810(D_001B65E4, 5, 0);
                install_total = func_1158A0(D_001B65E4) * 4;
                step++;
            }
        }

        break;
    case 19:
        if (func_115650(D_001B65E4) == 0)
        {
            if (func_115640(D_001B65E4) != 0)
            {
                step = 0x14;
            }
            else
            {
                step = 0x17;
            }
        }
        else
        {
            remaining = func_115660(D_001B65E4);
            percent = 99 - remaining * 99 / install_total;
            D_001B657C->message_value = percent;
            lib_text_set_resource(progress_text, g_boot_program.messages, BOOT_MSG_PERCENT, 0);

            if (percent >= next_tip_percent && tip_index < 8)
            {
                show_tip_image(tip_index);
                lib_text_set_resource(tip_text, g_boot_program.messages, tip_index + BOOT_MSG_FIRST_TIP, 0);
                tip_index++;
                next_tip_percent = tip_index * 100 / 8;
            }

            progress_bar_draw(progress_bar, install_total - remaining, install_total);

            if (input->pressed & resource->cancel_buttons)
            {
                lib_text_set_resource(message_text, g_boot_program.messages, BOOT_MSG_ABORT_CONFIRM, 0);
                func_112400(D_001B65F8, 2, 0, 0, 0x7F, 0x40, 0);
                queue_fade();
                D_001B65E4->unk13b = 1;
                selection = 1;
                x = menu_cursor_x(selection);
                cursor = new (0) BootSelectionCursor;
                func_467570(cursor, 1, 0, 0, x, 256.0f, 0.0f);
                func_465B20(D_001B657C, cursor);
                tip_text->visible = 0;
                tip_image->model->draw_flags |= BOOT_DRAW_HIDDEN;
                step = 3;
                yes_step = 0x1B;
                no_step = 0x1A;
            }
        }

        break;
    case 23:
        D_001B657C->message_value = 100;
        lib_text_set_resource(progress_text, g_boot_program.messages, BOOT_MSG_PERCENT, 0);
        progress_bar_draw(progress_bar, 100, 100);
        func_1156B0(D_001B65E4, 0);

        if (install_buffer != 0)
        {
            func_139928(install_buffer);
            install_buffer = 0;
        }

        func_115810(D_001B65E4, 4, 0);
        step++;
        break;
    case 24:
        if (func_115650(D_001B65E4) == 0)
        {
            func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
            queue_fade();
            step++;
        }

        break;
    case 25:
        lib_text_set_resource(message_text, g_boot_program.messages, BOOT_MSG_INSTALL_COMPLETE, 0);
        tip_text->visible = 0;
        tip_image->model->draw_flags |= BOOT_DRAW_HIDDEN;
        step = 0x15;
        break;
    case 20:
        if (func_115430(D_001B65E4) != 0)
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
            func_115420(D_001B65E4);
        }
        else
        {
            lib_text_set_resource(message_text, g_boot_program.messages, BOOT_MSG_ERROR, 0);
        }

        step = 0x15;
        break;
    case 21:
        if (input->pressed & resource->confirm_buttons)
        {
            func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
            queue_fade();
            step = 0x16;
        }

        break;
    case 22:
        func_10F000(D_001B65F8, 0, -1);
        func_4DF6E0(g_boot_program.display, 0, 0, 0, 0x7F);

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

        static_cast<BootUpdateList*>(D_001B6614)->append_node(new (0) BootTitleMenu(-1), -1);
        lib_object_detach_owner(this);
        destroy();
        return;
    case 26:
        tip_text->visible = 1;
        tip_image->model->draw_flags &= ~BOOT_DRAW_HIDDEN;
        lib_text_set_resource(message_text, g_boot_program.messages, BOOT_MSG_INSTALLING, 0);
        D_001B65E4->unk13b = 0;
        step = 0x13;
        break;
    case 27:
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
        D_001B65E4->unk13b = 0;
        func_1156C0(D_001B65E4);
        step++;
        wait_frames = 0;
        break;
    case 28:
        wait_frames++;

        if (func_115650(D_001B65E4) == 0)
        {
            func_115810(D_001B65E4, 4, 0);
            step++;
        }

        if (wait_frames >= 600)
        {
            BootResident1B65E4* resident = D_001B65E4;
            resident->unk108 = 0;
            resident->unk141 = 3;
            step = 0x1F;
        }

        break;
    case 29:
        if (func_115650(D_001B65E4) == 0)
        {
            func_115810(D_001B65E4, 2, 0);
            step++;
        }

        break;
    case 30:
        if (func_115650(D_001B65E4) == 0)
        {
            step++;
        }

        break;
    case 31:
        if (func_115670(D_001B65E4) != 0)
        {
            step = 2;
            selection = 0;
            x = menu_cursor_x(selection);
            cursor = new (0) BootSelectionCursor;
            func_467570(cursor, 1, 0, 0, x, 256.0f, 0.0f);
            func_465B20(D_001B657C, cursor);
        }
        else
        {
            step = 4;
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

    if (exiting == 0 && step > 0 && sound_started == 0 && resident_find_resource_request(D_001B65E8, BOOT_RES_SOUND, 0, 0, -1, 0) == 0)
    {
        func_1126D0(D_001B65F8, sound_data, 1, 0);
        sound_started = 1;
    }

    place_screen_images();
    update_choice_images();
}

/** @brief Destroy the list receiver. */
BootListReceiver::~BootListReceiver()
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
        resident_queue_allocation_release(D_001B65F4, tip_image_buffer);
    }

    delete navigator_file_buffers[0];
    delete navigator_file_buffers[1];
    delete navigator_file_buffers[2];
    func_10F000(D_001B65F8, 0, -1);
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
    screen_image_data = func_139700(0x40, func_11C8C0(D_001B65E4, BOOT_RES_SCREEN_IMAGES));
    func_103E70(D_001B65E8, BOOT_RES_SCREEN_IMAGES, screen_image_data, 1, 0x34BC0, 0, 0, 0, 1);
    sound_data = func_139700(0x40, func_11C8C0(D_001B65E4, BOOT_RES_SOUND));
    tip_image_data = func_139700(0x40, func_11C8C0(D_001B65E4, BOOT_RES_TIP_IMAGES));
    step = 0;

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
    system_file_data = new (0) u8[func_11C8C0(D_001B65E4, BOOT_RES_SYSTEM_FILES)];
    navigator_file_data = new (0) u8[func_11C8C0(D_001B65E4, BOOT_RES_NAVIGATOR_FILES)];
    selection = 0;
    screen_images_loaded = 0;
}

/**
 * @brief Default DMA notification hook; does nothing.
 * @param value Notification value.
 */
void BootDmaCallbacks::on_packet_notify(u32 value)
{
}

/**
 * @brief Default preparation hook; does nothing.
 * @param value Notification word or packet address.
 */
void BootDmaCallbacks::on_packet_complete(u32 value)
{
}

/**
 * @brief Copy the position.
 * @param value Source vector.
 */
void BootPositionTransform::copy_translation(const BootVector4DDAA0* value)
{
    copy_vector(&translation, value);
}

/**
 * @brief Copy the position.
 * @param value Source vector.
 */
void BootPositionTransform::set_translation_vector(const BootVector4DDAA0* value)
{
    copy_vector(&translation, value);
}

/**
 * @brief Set the position and a w component of one.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void BootPositionTransform::set_translation(float x, float y, float z)
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
s32 BootListObject::get_default_list_kind()
{
    return 3;
}

/** @brief Advance this registered object's state; the base implementation does nothing. */
void BootListObject::update()
{
}

/**
 * @brief Copy the position and mark the transform dirty.
 * @param value Source vector.
 */
void BootTransform::copy_translation(const BootVector4DDAA0* value)
{
    transform_dirty = 1;
    copy_vector(&translation, value);
}

/**
 * @brief Copy the position and mark the transform dirty.
 * @param value Source vector.
 */
void BootTransform::set_translation_vector(const BootVector4DDAA0* value)
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
void BootTransform::set_orientation_components(float x, float y, float z, float w)
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
void BootTransform::copy_orientation(const BootVector4DDAA0* value)
{
    transform_dirty = 1;
    copy_vector(&orientation, value);
}

/**
 * @brief Copy the rotation vector and mark the transform dirty.
 * @param value Source vector.
 */
void BootTransform::set_orientation(const BootVector4DDAA0* value)
{
    transform_dirty = 1;
    copy_vector(&orientation, value);
}

/**
 * @brief Convert a rotation into the rotation vector and mark the transform dirty.
 * @param value Source rotation.
 */
void BootTransform::convert_rotation(const BootVector4DDAA0* value)
{
    transform_dirty = 1;
    func_4CE4C0(&orientation, &value->x);
}

/**
 * @brief Convert a rotation into the rotation vector and mark the transform dirty.
 * @param value Source rotation.
 */
void BootTransform::set_rotation_vector(const BootVector4DDAA0* value)
{
    transform_dirty = 1;
    func_4CE4C0(&orientation, &value->x);
}

/**
 * @brief Convert three rotation components into the rotation vector and mark the transform dirty.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void BootTransform::set_rotation(float x, float y, float z)
{
    transform_dirty = 1;
    BootVector4DDAA0 value;
    value.x = x;
    value.y = y;
    value.z = z;
    value.w = 1.0f;
    func_4CE4C0(&orientation, &value.x);
}

/**
 * @brief Copy the scale vector and mark the transform dirty.
 * @param value Source vector.
 */
void BootTransform::copy_scale(const BootVector4DDAA0* value)
{
    transform_dirty = 1;
    copy_vector(&scale, value);
}

/**
 * @brief Copy the scale vector and mark the transform dirty.
 * @param value Source vector.
 */
void BootTransform::set_scale_vector(const BootVector4DDAA0* value)
{
    transform_dirty = 1;
    copy_vector(&scale, value);
}

/** @brief Draw in the main list (bucket zero). */
void BootTransformOwner::set_default_draw_bucket()
{
    draw_bucket = 0;
}

/** @brief Virtual slot 4; the owner's implementation does nothing. */
void BootTransformOwner::render()
{
}

/**
 * @brief Give the centre for Lib's oriented-box visibility test; this owner has none.
 * @param output Receives the centre in local space.
 * @return Nonzero when a centre was written; zero here, so the test is skipped.
 */
s32 BootTransformOwner::get_box_cull_center(void* output)
{
    return 0;
}

/**
 * @brief Fade the owner as it nears the camera; Lib calls this for owners with draw flag 0x800. This owner doesn't fade.
 * @param value Distance in front of the camera over the fade range, clamped to one.
 * @param mode Two from Lib's caller; unused here.
 * @return Whether the value is negative.
 */
bool BootTransformOwner::set_fade_alpha(float value, float mode)
{
    return value < 0.0f;
}

/**
 * @brief Return the bounding sphere Lib culls against (centre in xyz, radius in w); this owner has Lib's shared default.
 * @return Bounding sphere.
 */
const BootVector4DDAA0* BootTransformOwner::get_bounding_sphere()
{
    return &D_50CD30;
}

/**
 * @brief Default matrix handler; does nothing.
 * @param matrix Matrix supplied by the caller.
 * @param context Opaque caller context.
 */
void BootTransformOwner::build_packet(const void* matrix, void* context)
{
}

/**
 * @brief Make a copy of this object that stays linked to it; this owner can't be copied.
 * @return The copy, or null.
 */
BootTransformOwner* BootTransformOwner::clone()
{
    return 0;
}

/** @brief Unlink a copy from its original and queue it for release; this owner never has copies, so it does nothing. */
void BootTransformOwner::release_clone()
{
}

/** @brief Default dispatch slot; does nothing. */
void ItemCreationClass185050::func_slot0c()
{
}
