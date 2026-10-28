#include "include_asm.h"
#include "overlays/boot/text_001E0900.h"
#include "overlays/boot/init.h"
#include "overlays/lib/text_0045AD10.h"
#include "main/resident_001001E0.h"
#include "main/resident_00101550.h"
#include "vu0.h"

extern "C" {
extern BootVector4DDAA0 D_50CD30;
extern BootClass178DD0* D_001B661C;
extern float D_001B6688;
void func_4CE4C0(void* destination, const float* source);
void func_11EE00(void* queue, void* allocation);
void func_10F000(void* request, s32 first, s32 second);
void func_001FA620(BootImage* object, void* image, s32 mode);
void func_001F9FC0(BootImage* object, s32 first, s32 second, s32 width, s32 height, u32 color, s32 third);
void func_001F8720(BootProgressBar* object, s32 width, s32 height, u32 color, s32 mode);
void func_001F79A0(BootProgressBar* object, s32 done, s32 total);
s32 func_102AA0(void* queue);
s32 func_103640(void* queue, s32 id, s32 first, s32 second, s32 third, s32 fourth);
void func_103B20(void* queue, s32 id, s32 first, s32 second, s32 third, s32 fourth);
void func_112400(void* request, s32 sound, s32 first, s32 second, s32 volume, s32 pan, s32 third);
void func_1126D0(void* request, u8* data, s32 first, s32 second);
void func_1152C0(BootResident1B65E4* object, u8* first, s32 first_size, u8* second, s32 second_size, u8* third, s32 third_size);
void func_1152E0(BootResident1B65E4* object, u8* buffer, u8* first, s32 first_size, u8* second, s32 second_size, u8* third, s32 third_size, u8* fourth, s32 fourth_size);
void func_115420(BootResident1B65E4* object);
s32 func_115430(BootResident1B65E4* object);
s32 func_115460(BootResident1B65E4* object, s32 first, s32 second);
s32 func_115640(BootResident1B65E4* object);
s32 func_115650(BootResident1B65E4* object);
s32 func_115660(BootResident1B65E4* object);
s32 func_115670(BootResident1B65E4* object);
void func_1156B0(BootResident1B65E4* object, u8* buffer);
void func_1156C0(BootResident1B65E4* object);
void func_115810(BootResident1B65E4* object, s32 command, s32 argument);
u32 func_115830(BootResident1B65E4* object);
u32 func_115840(BootResident1B65E4* object);
s32 func_1158A0(BootResident1B65E4* object);
void func_121FE0(s32 value);
void func_139928(void* allocation);
void func_4DF6E0(BootDimensionsACD0* display, s32 red, s32 green, s32 blue, s32 alpha);
void func_467570(BootClass175070* object, s32 first, s32 second, s32 third, float x, float y, float z);
s32 func_465B20(BootRuntime1B657C* runtime, BootClass178A90* object);
void lib_container_attach_widget(BootClass178660* object, BootClass178750* child);
void lib_text_set_resource(BootClass178750* object, s32 slot, u32 key, u8 flag);
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

/** @brief Queue a screen fade on the resident manager list. */
static inline void queue_fade()
{
    BootClass171C00* fade = new (0) BootClass171C00(g_boot_program.display);
    fade->unkd0 = 2.0f;
    D_001B661C->append_node(fade, -1);
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
void BootClass170E90::destroy()
{
    delete this;
}

/** @brief Virtual slot 4; the base implementation does nothing. */
void BootClass170E90::func_001DD4C0()
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
        func_11EE00(D_001B65F4, tip_image_buffer);
        tip_image_buffer = 0;
    }
    tip_image_buffer = func_102920(D_001B65EC, tip_image_data, index, 1);
    func_1025A0(D_001B65EC, tip_image_data, (void*)(((u32)tip_image_buffer + 0x7F) & ~0x7F), index);
    tip_image = new (0) BootImage;
    func_001FA620(tip_image, (void*)(((u32)tip_image_buffer + 0x7F) & ~0x7F), 0);
    func_101440(func_101290(func_10D8E0()), 1);
    func_001F9FC0(tip_image, 0, 1, 0x120, 0xC9, 0x80808080, 0);
    tip_image->unk18->func_001E0520(-296.0f, -64.0f, 0.0f);
}

/**
 * @brief Set the position and a w component of one, and mark the transform dirty.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void BootClass170D90::func_001E0520(float x, float y, float z)
{
    transform_dirty = 1;
    unk20.x = x;
    unk20.y = y;
    unk20.z = z;
    unk20.w = 1.0f;
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
        func_001FA620(images[4], (void*)(((u32)screen_image_buffers[0] + 0x7F) & ~0x7F), 0);
        func_001F9FC0(images[4], 0x1E, 0x131, 0x4C, 0x26, 0x80808080, 0);
        images[5] = new (0) BootImage;
        func_001FA620(images[5], (void*)(((u32)screen_image_buffers[0] + 0x7F) & ~0x7F), 0);
        func_001F9FC0(images[5], 0x1E, 0x167, 0x4C, 0x26, 0x80808080, 0);
    }
    if (((BootResource0970*)func_101440(func_101290(func_10D8E0()), 1))->widescreen)
    {
        if (images[4] != 0)
        {
            images[4]->unk18->func_001E0520(-174.0f, 0.0f, 0.0f);
        }
        if (images[5] != 0)
        {
            images[5]->unk18->func_001E0520(78.0f, 0.0f, 0.0f);
        }
    }
    else
    {
        if (images[4] != 0)
        {
            images[4]->unk18->func_001E0520(-132.0f, 0.0f, 0.0f);
        }
        if (images[5] != 0)
        {
            images[5]->unk18->func_001E0520(60.0f, 0.0f, 0.0f);
        }
    }
    for (s32 i = 0; i < 2; i++)
    {
        if (images[4 + i] != 0 && images[4 + i]->unk18 != 0)
        {
            BootClass177820* model = images[4 + i]->unk18;
            if (selection == i)
            {
                BootVector4DDAA0 scale;
                copy_vector(&scale, &model->unk560);
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
                copy_vector(&model->unk560, &scale);
                model->func_001DDAA0();
            }
            else
            {
                BootVector4DDAA0 scale;
                scale.x = 1.0f;
                scale.y = 1.0f;
                scale.z = 1.0f;
                scale.w = 1.0f;
                copy_vector(&model->unk560, &scale);
                model->func_001DDAA0();
            }
        }
    }
}

/** @brief Store the component product of the two input vectors. */
void BootClass174310::func_001DDAA0()
{
    vu0_multiply_xyzw(&unk580, &unk560, &unk570);
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
        func_001FA620(images[0], (void*)(((u32)screen_image_buffers[0] + 0x7F) & ~0x7F), 0);
        func_001F9FC0(images[0], 0, 1, 0x1E8, 0xDF, 0x80808080, 0);
        images[0]->unk18->func_001E0520(-244.0f, -112.0f, 0.0f);
    }
    if (images[1] == 0)
    {
        images[1] = new (0) BootImage;
        func_001FA620(images[1], (void*)(((u32)screen_image_buffers[1] + 0x7F) & ~0x7F), 0);
        func_001F9FC0(images[1], 0, 0, 0x280, 0x50, 0x80808080, 0);
        images[1]->unk18->func_001E0520(-312.0f, -216.0f, 0.0f);
    }
    if (images[2] == 0)
    {
        images[2] = new (0) BootImage;
        func_001FA620(images[2], (void*)(((u32)screen_image_buffers[0] + 0x7F) & ~0x7F), 0);
        func_001F9FC0(images[2], 0, 0xEA, 0xC8, 0x1D, 0x80808080, 0);
    }
    if (images[3] == 0)
    {
        images[3] = new (0) BootImage;
        func_001FA620(images[3], (void*)(((u32)screen_image_buffers[0] + 0x7F) & ~0x7F), 0);
        func_001F9FC0(images[3], 0x1B, 0x190, 0x1B6, 0x31, 0x80808080, 0);
    }
    if (((BootResource0970*)func_101440(func_101290(func_10D8E0()), 1))->widescreen)
    {
        if (images[1] != 0)
        {
            images[1]->unk18->func_001E0520(-404.0f, -216.0f, 0.0f);
            images[1]->unk18->func_001DDED0(1.31f, 1.0f, 1.0f);
        }
        if (images[2] != 0)
        {
            images[2]->unk18->func_001E0520(220.0f, 180.0f, 0.0f);
        }
        if (images[3] != 0)
        {
            images[3]->unk18->func_001E0520(-32.0f, -221.0f, 0.0f);
        }
    }
    else
    {
        if (images[1] != 0)
        {
            images[1]->unk18->func_001E0520(-312.0f, -216.0f, 0.0f);
            images[1]->unk18->func_001DDED0(1.0f, 1.0f, 1.0f);
        }
        if (images[2] != 0)
        {
            images[2]->unk18->func_001E0520(150.0f, 180.0f, 0.0f);
        }
        if (images[3] != 0)
        {
            images[3]->unk18->func_001E0520(-128.0f, -221.0f, 0.0f);
        }
    }
}

/**
 * @brief Set the scale's xyz components and mark the transform dirty.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void BootClass170D90::func_001DDED0(float x, float y, float z)
{
    transform_dirty = 1;
    unk40.x = x;
    unk40.y = y;
    unk40.z = z;
}

/** @brief Advance the install sequence: load the screen, ask, check the BB Unit, install, then hand over. */
void BootInstaller::update()
{
    BootResource0970* resource;
    float x;
    s32 remaining;
    s32 percent;
    BootInput* input;
    input = g_boot_program.input;
    resource = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);
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
            container = new (0) BootClass178660(9, 0.0f, 0.0f, 0.0f);
            func_465B20(D_001B657C, container);
            message_text = new (0) BootClass178750(g_boot_program.messages, BOOT_MSG_INSTALL_CONFIRM, 1, 48.0f, 88.0f, 512.0f, 224.0f);
            message_text->set_color(0x34130F);
            lib_container_attach_widget(container, message_text);
            x = menu_cursor_x(selection);
            cursor = new (0) BootClass175070;
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
            func_121FE0(0);
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
            BootClass175070* arrow = cursor;
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
        if (input->pressed & resource->unk00)
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
        else if (input->pressed & resource->unk02)
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
            func_103B20(D_001B65E8, BOOT_RES_SOUND, 0, 0, -1, 0);
            func_103B20(D_001B65E8, BOOT_RES_SYSTEM_FILES, 0, 0, -1, 0);
            func_103B20(D_001B65E8, BOOT_RES_TIP_IMAGES, 0, 0, -1, 0);
            exiting = 1;
        }
        else if (func_102AA0(D_001B65E8) == 0 && D_001B65E4->unk12183 == 0)
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
            static_cast<BootClass178DD0*>(D_001B6614)->append_node(new (0) BootClass171BB0(3), -1);
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
        func_001F8720(progress_bar, 0xF0, 0x18, 0x80FFFFFF, 0);
        tip_text = new (0) BootClass178750(g_boot_program.messages, BOOT_MSG_FIRST_TIP, 1, 328.0f, 180.0f, 320.0f, 224.0f);
        tip_text->set_color(0x34130F);
        lib_container_attach_widget(container, tip_text);
        show_tip_image(0);
        tip_index = 1;
        next_tip_percent = 0xC;
        D_001B657C->message_value = 0;
        if (resource->widescreen)
        {
            progress_bar->unk18->func_001E0520(-366.0f, 180.0f, 0.0f);
            progress_text = new (0) BootClass178750(g_boot_program.messages, BOOT_MSG_PERCENT, 1, 240.0f, 438.0f, 512.0f, 32.0f);
            progress_text->set_color(0x34130F);
        }
        else
        {
            progress_bar->unk18->func_001E0520(-280.0f, 180.0f, 0.0f);
            progress_text = new (0) BootClass178750(g_boot_program.messages, BOOT_MSG_PERCENT, 1, 290.0f, 432.0f, 512.0f, 32.0f);
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
        func_1152E0(D_001B65E4, icon_header, system_file_buffers[0], sizes[0], system_file_buffers[1], sizes[1], system_file_buffers[2], sizes[2], system_file_buffers[2], sizes[2]);
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
                func_121FE0(0);
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
            func_001F79A0(progress_bar, install_total - remaining, install_total);
            if (input->pressed & resource->unk02)
            {
                lib_text_set_resource(message_text, g_boot_program.messages, BOOT_MSG_ABORT_CONFIRM, 0);
                func_112400(D_001B65F8, 2, 0, 0, 0x7F, 0x40, 0);
                queue_fade();
                D_001B65E4->unk13b = 1;
                selection = 1;
                x = menu_cursor_x(selection);
                cursor = new (0) BootClass175070;
                func_467570(cursor, 1, 0, 0, x, 256.0f, 0.0f);
                func_465B20(D_001B657C, cursor);
                tip_text->unk3f = 0;
                tip_image->unk18->unk6a |= 1;
                step = 3;
                yes_step = 0x1B;
                no_step = 0x1A;
            }
        }
        break;
    case 23:
        D_001B657C->message_value = 100;
        lib_text_set_resource(progress_text, g_boot_program.messages, BOOT_MSG_PERCENT, 0);
        func_001F79A0(progress_bar, 100, 100);
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
        tip_text->unk3f = 0;
        tip_image->unk18->unk6a |= 1;
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
        if (input->pressed & resource->unk00)
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
        static_cast<BootClass178DD0*>(D_001B6614)->append_node(new (0) BootClass171BB0(-1), -1);
        lib_object_detach_owner(this);
        destroy();
        return;
    case 26:
        tip_text->unk3f = 1;
        tip_image->unk18->unk6a &= ~1;
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
            cursor = new (0) BootClass175070;
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
    if (exiting == 0 && step > 0 && sound_started == 0 && func_103640(D_001B65E8, BOOT_RES_SOUND, 0, 0, -1, 0) == 0)
    {
        func_1126D0(D_001B65F8, sound_data, 1, 0);
        sound_started = 1;
    }
    place_screen_images();
    update_choice_images();
}

/** @brief Destroy the list receiver. */
BootClass178A70::~BootClass178A70()
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
        func_11EE00(D_001B65F4, tip_image_buffer);
    }
    delete navigator_file_buffers[0];
    delete navigator_file_buffers[1];
    delete navigator_file_buffers[2];
    func_10F000(D_001B65F8, 0, -1);
    delete sound_data;
    g_boot_program.error_popup->set_enabled(1);
}

/** @brief Turn the popup on or off. @param value Nonzero to allow the popup. */
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

/** @brief Default DMA notification hook; does nothing. @param value Notification value. */
void BootClass170D50::func_001E04E0(u32 value)
{
}

/** @brief Default preparation hook; does nothing. @param value Notification word or packet address. */
void BootClass170D50::func_001E04F0(u32 value)
{
}

/** @brief Copy the position. @param value Source vector. */
void BootClass170D60::func_001E0500(const BootVector4DDAA0* value)
{
    copy_vector(&unk20, value);
}

/** @brief Copy the position. @param value Source vector. */
void BootClass170D60::func_001E0510(const BootVector4DDAA0* value)
{
    copy_vector(&unk20, value);
}

/**
 * @brief Set the position and a w component of one.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void BootClass170D60::func_001E0520(float x, float y, float z)
{
    unk20.x = x;
    unk20.y = y;
    unk20.z = z;
    unk20.w = 1.0f;
}

/**
 * @brief Report the list kind used when registration requests the default.
 * @return Three in the base implementation.
 */
s32 BootClass170E90::get_default_list_kind()
{
    return 3;
}

/** @brief Advance this registered object's state; the base implementation does nothing. */
void BootClass170E90::update()
{
}

/** @brief Copy the position and mark the transform dirty. @param value Source vector. */
void BootClass170D90::func_001E0500(const BootVector4DDAA0* value)
{
    transform_dirty = 1;
    copy_vector(&unk20, value);
}

/** @brief Copy the position and mark the transform dirty. @param value Source vector. */
void BootClass170D90::func_001E0510(const BootVector4DDAA0* value)
{
    transform_dirty = 1;
    copy_vector(&unk20, value);
}

/**
 * @brief Set all four rotation components and mark the transform dirty.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 * @param w Fourth component.
 */
void BootClass170D90::func_001E0630(float x, float y, float z, float w)
{
    transform_dirty = 1;
    unk30.x = x;
    unk30.y = y;
    unk30.z = z;
    unk30.w = w;
}

/** @brief Copy the rotation vector and mark the transform dirty. @param value Source vector. */
void BootClass170D90::func_001E0650(const BootVector4DDAA0* value)
{
    transform_dirty = 1;
    copy_vector(&unk30, value);
}

/** @brief Copy the rotation vector and mark the transform dirty. @param value Source vector. */
void BootClass170D90::func_001E0670(const BootVector4DDAA0* value)
{
    transform_dirty = 1;
    copy_vector(&unk30, value);
}

/** @brief Convert a rotation into the rotation vector and mark the transform dirty. @param value Source rotation. */
void BootClass170D90::func_001E0690(const BootVector4DDAA0* value)
{
    transform_dirty = 1;
    func_4CE4C0(&unk30, &value->x);
}

/** @brief Convert a rotation into the rotation vector and mark the transform dirty. @param value Source rotation. */
void BootClass170D90::func_001E06C0(const BootVector4DDAA0* value)
{
    transform_dirty = 1;
    func_4CE4C0(&unk30, &value->x);
}

/**
 * @brief Convert three rotation components into the rotation vector and mark the transform dirty.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void BootClass170D90::func_001E06F0(float x, float y, float z)
{
    transform_dirty = 1;
    BootVector4DDAA0 value;
    value.x = x;
    value.y = y;
    value.z = z;
    value.w = 1.0f;
    func_4CE4C0(&unk30, &value.x);
}

/** @brief Copy the scale vector and mark the transform dirty. @param value Source vector. */
void BootClass170D90::func_001E0730(const BootVector4DDAA0* value)
{
    transform_dirty = 1;
    copy_vector(&unk40, value);
}

/** @brief Copy the scale vector and mark the transform dirty. @param value Source vector. */
void BootClass170D90::func_001E0750(const BootVector4DDAA0* value)
{
    transform_dirty = 1;
    copy_vector(&unk40, value);
}

/** @brief Clear the byte at offset 0x60. */
void BootClass178A90::func_001E0860()
{
    unk60 = 0;
}

/** @brief Virtual slot 4; the owner's implementation does nothing. */
void BootClass178A90::func_001DD4C0()
{
}

/** @brief Default output handler. @param output Opaque output object. @return Zero. */
s32 BootClass178A90::func_001E0880(void* output)
{
    return 0;
}

/**
 * @brief Test the supplied value.
 * @param value Value to test.
 * @param mode Additional mode used by derived implementations.
 * @return Whether the value is negative.
 */
bool BootClass178A90::func_001E0890(float value, float mode)
{
    return value < 0.0f;
}

/** @brief Return the shared fallback vector. @return Vector pointer. */
const BootVector4DDAA0* BootClass178A90::func_001E08B0()
{
    return &D_50CD30;
}

/**
 * @brief Default matrix handler; does nothing.
 * @param matrix Matrix supplied by the caller.
 * @param context Opaque caller context.
 */
void BootClass178A90::func_001E08C0(const void* matrix, void* context)
{
}

/** @brief Produce a transformation receiver. @return Null. */
BootClass178A90* BootClass178A90::func_001E08D0()
{
    return 0;
}

/** @brief Default hook; does nothing. */
void BootClass178A90::func_001E08E0()
{
}

/** @brief Default dispatch slot; does nothing. */
void ItemCreationClass185050::func_slot0c()
{
}
