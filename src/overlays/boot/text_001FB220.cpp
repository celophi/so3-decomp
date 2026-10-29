#include "include_asm.h"
#include "overlays/lib/vector.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/boot/text_001ED4E0.h"
#include "overlays/boot/text_001DD3C0.h"
#include "overlays/boot/text_001E0900.h"
#include "overlays/boot/text_001FF0A0.h"
#include "overlays/boot/text_001FF9E0.h"
#include "overlays/boot/resident.h"

extern "C" {

/** Name given to every trophy texture. */
extern const char g_trophy_texture_name[];

extern const char g_no_trophy_number[];
extern const char g_trophy_number_format[];
char* func_13CD50(char* destination, const char* source, u32 size);
s32 func_13C4F0(char* destination, const char* format, ...);
void func_4CD810(FieldVec4B* output, const BootVector4DDAA0* axis_angle);
void func_4CD630(FieldVec4B* output, const FieldVec4B* from, const FieldVec4B* to, float t);
s32 func_457220(BootTrophyRecordF10* record);

/** Key each trophy record must carry, stored XOR-encoded. */
extern const u32 g_trophy_keys[];

/** Text of the number label before the grid first updates it. */
extern const char g_first_trophy_number[];

void lib_container_attach_widget(BootClass178660* object, BootClass170E90* child);
void lib_text_set_resource(BootClass178750* object, s32 slot, u32 key, u8 flag);
void func_001F8720(BootProgressBar* object, s32 width, s32 height, u32 color, s32 mode);
void func_001F79A0(BootProgressBar* bar, s32 done, s32 total);

/** @brief Report the list kind used when registration requests the default. @return Four. */
s32 BootBattleTrophyViewer::get_default_list_kind()
{
    return 4;
}

/**
 * @brief Return the time a trophy was earned, as one comparable number.
 * @param viewer Viewer holding the records and display order.
 * @param position List position of the trophy.
 * @return Year, month, day, hour, minute and second packed from the highest byte down, or zero if not earned.
 */
static inline u64 trophy_time(BootBattleTrophyViewer* viewer, s32 position)
{
    BootResource0970* settings = boot_settings();
    s32 index = viewer->order[position];

    if (resource_bit(&settings->unk1A8, index))
    {
        BootTrophyTime* time = &viewer->records[index].time;
        return time->second + (time->minute << 8) + (time->hour << 16) + (time->day << 24) + ((u64)time->month << 32) + ((u64)time->year << 40);
    }

    return 0;
}

/**
 * @brief Reset the display order to trophy number order, then optionally sort it newest first.
 * @param newest_first Nonzero to sort by the time each trophy was earned; unearned ones go last.
 */
void BootBattleTrophyViewer::sort_trophies(u8 newest_first)
{
    for (s32 i = 0; i < 300; i++)
    {
        order[i] = i;
    }

    if (!newest_first)
    {
        return;
    }

    BootResourceBits0970* bits = &boot_settings()->unk1A8;
    u32 seed = bits->checksum_seed;
    u32 checksum;
    func_457670(bits, &seed, &checksum);

    if (bits->checksum != checksum)
    {
        return;
    }

    for (s32 i = 1; i < 300; i++)
    {
        u64 time = trophy_time(this, i);
        s16 current = order[i];
        s32 j;

        for (j = i - 1; j >= 0 && trophy_time(this, j) < time; j--)
        {
            order[j + 1] = order[j];
        }

        order[j + 1] = current;
    }
}

/**
 * @brief Build a trophy's texture from the picture template, the trophy's packed picture and the first palette.
 * @param record Trophy record holding the picture.
 * @param texture Texture resource to fill.
 * @param index Trophy index.
 */
void BootBattleTrophyViewer::build_trophy_texture(const BootTrophyRecordF10* record, BootTextureResource* texture, s32 index)
{
    func_13A4C0(texture, (void*)(((u32)unk1C[2] + 0x7F) & ~0x7F), 0x4600);
    BootTextureHeader* header = &texture->header;
    u32* palette = (u32*)((u8*)header + header->palette_offset + 0x80);
    u8* pixels = (u8*)header + ((BootTextureImage*)((u8*)header + header->image_offset))->pixel_offset + 0x80;
    func_13CD50(header->name, g_trophy_texture_name, 4);
    header->id = index + 1;

    for (s32 i = 0; i < 32; i++)
    {
        palette[i] = palettes[0][i];
    }

    const u8* source = record->image;
    u16 bits = *source++;
    s32 bit_count = 8;

    for (s32 y = 0; y < 96; y++)
    {
        for (s32 x = 0; x < 64; x++)
        {
            *pixels++ = bits & 0x1F;
            bits >>= 5;
            bit_count -= 5;

            if (bit_count < 9)
            {
                bits |= *source++ << bit_count;
                bit_count += 8;
            }
        }

        pixels += 64;
    }
}

/**
 * @brief Check a flag block against its stored checksum.
 * @param bits Flag block.
 * @return True when the checksum matches.
 */
static inline bool flags_intact(BootResourceBits0970* bits)
{
    u32 seed = bits->checksum_seed;
    u32 checksum;
    func_457670(bits, &seed, &checksum);
    return bits->checksum == checksum;
}

/**
 * @brief Test whether a value is above zero.
 * @param value Value to test.
 * @return One when value is above zero, otherwise zero.
 */
static inline s32 positive(s32 value)
{
    return value > 0;
}

/**
 * @brief Move a grid position by the current scroll offset.
 * @param position Unscrolled position.
 * @param scroll Scroll offset.
 * @return The scrolled position.
 */
static inline float scrolled(float position, float scroll)
{
    return position + scroll;
}

/** @brief Scroll the grid, show the cursor's trophy number, turn newly shown pictures and grow the selected one. */
void BootBattleTrophyViewer::update_grid()
{
    FieldVec4B front;
    FieldVec4B back;
    FieldVec4B rotation;
    BootVector4DDAA0 value;
    BootVector4DDAA0 front_axis;
    BootVector4DDAA0 back_axis;

    if (step != 9)
    {
        return;
    }

    if (scroll_step > 0 && ++scroll_step > 4)
    {
        scroll_step = 0;
        first_row++;
    }

    if (scroll_step < 0 && --scroll_step < -4)
    {
        scroll_step = 0;
        first_row--;
    }

    float scroll = -scroll_step * 25 - first_row * 100;
    // TODO: Only the forward half goes through a helper; it's the only way I found that matches.
    s32 selected = cursor_column + (cursor_row + first_row + positive(scroll_step) - (scroll_step < 0)) * 8;

    if (selected >= 300)
    {
        func_13C948(number_text, g_no_trophy_number);
    }
    else
    {
        func_13C4F0(number_text, g_trophy_number_format, order[selected] + 1);
    }

    if (number_label != 0)
    {
        number_label->set_text(number_text);
    }

    if (flags_intact(&boot_settings()->unk1A8))
    {
        front_axis.x = 0.0f;
        front_axis.y = 1.0f;
        front_axis.z = 0.0f;
        front_axis.w = 0.0f;
        func_4CD810(&front, &front_axis);
        back_axis.x = 0.0f;
        back_axis.y = 1.0f;
        back_axis.z = 0.0f;
        back_axis.w = 3.1415927f;
        func_4CD810(&back, &back_axis);

        for (s32 i = 0; i < 300; i++)
        {
            BootClass177820* model;

            if (trophy_images[i] != 0 && (model = trophy_images[i]->unk18) != 0)
            {
                if (unkC94[i] > 0.0f && unkC94[i] < 1.0f)
                {
                    if (model != 0)
                    {
                        func_4CD630(&rotation, &front, &back, unkC94[i]);
                        model->func_001E0670((const BootVector4DDAA0*)&rotation);
                    }

                    unkC94[i] += 4.0f * D_001B6690;

                    if (!(unkC94[i] < 1.0f))
                    {
                        unkC94[i] = 1.0f;
                    }
                }
                else if (unkC94[i] > 0.0f)
                {
                    model->func_001E0670((const BootVector4DDAA0*)&back);
                }
            }
        }
    }

    for (s32 i = 0; i < 300; i++)
    {
        BootImage* image = trophy_images[order[i]];

        if (image != 0)
        {
            BootClass177820* model = image->unk18;
            copy_vector(&value, &model->unk20);
            value.x = -236.0f + (i & 7) * 68;
            value.y = scrolled(-94.0f + i / 8 * 100, scroll);
            model->func_001E0510(&value);
            copy_vector(&value, &model->unk40);

            if (selected == i && scroll_step == 0)
            {
                value.x += 0.04f;
                value.y += 0.04f;
                value.z += 0.04f;

                if (!(value.x <= 1.2f))
                {
                    value.x = 1.2f;
                    value.y = 1.2f;
                    value.z = 1.2f;
                }

                model->func_001E94E0(2);
            }
            else
            {
                if (!(value.x <= 1.0f))
                {
                    value.x -= 0.04f;
                    value.y -= 0.04f;
                    value.z -= 0.04f;

                    if (value.x < 1.0f)
                    {
                        value.x = 1.0f;
                        value.y = 1.0f;
                        value.z = 1.0f;
                    }
                }

                model->func_001E94E0(0);
            }

            model->func_001E0750(&value);
        }
    }
}

/**
 * @brief Set a clip region's rectangle and clear its display.
 * @param clip Clip region.
 * @param left Left edge.
 * @param top Top edge.
 * @param right Right edge.
 * @param bottom Bottom edge.
 */
static inline void set_clip(BootClass171DD0* clip, s32 left, s32 top, s32 right, s32 bottom)
{
    clip->left = left;
    clip->top = top;
    clip->right = right;
    clip->bottom = bottom;
    clip->display = 0;
}

/**
 * @brief Check the trophy data and create a picture for each trophy: its own picture when earned, a blank frame
 * otherwise.
 * @return One when done, or zero when a trophy record fails its check, after clearing that trophy.
 */
s32 BootBattleTrophyViewer::create_trophy_images()
{
    BootResource0970* settings = boot_settings();
    BootResourceBits0970* bits = &settings->unk1A8;

    if (!flags_intact(bits))
    {
        return 0;
    }

    earned_count = 0;

    if (flags_intact(bits))
    {
        for (s32 i = 0; i < 300; i++)
        {
            BootTrophyRecordF10* record = &records[i];

            if (func_457220(record) == 0 || *((BootResidentRoot15CC0*)func_10D8E0())->status == 0x67)
            {
                set_resource_bit(bits, i, 0);
                record->unk0C = 0;
                func_457520(bits);
                return 0;
            }
        }
    }

    for (s32 i = 0; i < 300; i++)
    {
        order[i] = i;
        textures[i] = (BootTextureResource*)func_139700(0x80, 0x4600);
    }

    unkB8 = new (0) BootClass171DD0;
    D_001B661C->append_node(unkB8, -1);

    if (settings->widescreen)
    {
        set_clip(unkB8, 0, 0x4D, 0x27F, 0x180);
    }
    else
    {
        set_clip(unkB8, 0, 0x50, 0x27F, 0x17C);
    }

    if (flags_intact(bits))
    {
        for (s32 i = 0; i < 300; i++)
        {
            trophy_images[i] = new (0) BootImage;
            trophy_images[i]->centered = 1;
            unkC94[i] = 0.0f;

            if (resource_bit(bits, i))
            {
                build_trophy_texture(&records[i], textures[i], i);
                trophy_images[i]->set_texture((const BootTextureResource*)(((u32)unk1C[0] + 0x7F) & ~0x7F), textures[i]);
                func_001F93B0(trophy_images[i], 0, 0xE2, 0x44, 0x64, 0, 0, 0x40, 0x60, 0x80808080, 0);
                earned_count++;
            }
            else
            {
                trophy_images[i]->set_texture((const BootTextureResource*)(((u32)unk1C[0] + 0x7F) & ~0x7F), 0);
                trophy_images[i]->set_rectangle(0, 0xE2, 0x44, 0x64, 0x80808080, 0);
            }

            trophy_images[i]->unk18->func_001E0520(-236.0f + (i & 7) * 68, -94.0f + i / 8 * 100, 0.0f);
        }
    }
    else
    {
        for (s32 i = 0; i < 300; i++)
        {
            trophy_images[i] = new (0) BootImage;
            trophy_images[i]->centered = 1;
            trophy_images[i]->set_texture((const BootTextureResource*)(((u32)unk1C[0] + 0x7F) & ~0x7F), 0);
            trophy_images[i]->set_rectangle(0, 0xE2, 0x44, 0x64, 0x80808080, 0);
            trophy_images[i]->unk18->func_001E0520(-236.0f + (i & 7) * 68, -94.0f + i / 8 * 100, 0.0f);
        }
    }

    func_121FE0(0);
    unkBC = new (0) BootClass171DD0;
    D_001B661C->append_node(unkBC, -1);
    unkBC->display = g_boot_program.display;
    return 1;
}

/**
 * @brief Give the bar's model an even color modulation and recompute its combined color.
 * @param bar Loading bar.
 * @param red Red factor.
 * @param green Green factor.
 * @param blue Blue factor.
 * @param alpha Alpha factor.
 */
static inline void set_bar_color(BootProgressBar* const& bar, float red, float green, float blue, float alpha)
{
    BootVector4DDAA0 color;
    color.x = red;
    color.y = green;
    color.z = blue;
    color.w = alpha;
    BootClass177820* model = bar->unk18;
    copy_vector(&model->unk560, &color);
    model->func_001DDAA0();
}

/** @brief Create the two screen images once the pictures load, place them for the screen shape and fade out the bar. */
void BootBattleTrophyViewer::update_images()
{
    if (unk1C[2] == 0)
    {
        return;
    }

    if (unk28[0] == 0)
    {
        unk28[0] = new (0) BootImage;
        unk28[0]->set_texture((const BootTextureResource*)(((u32)unk1C[0] + 0x7F) & ~0x7F), 0);
        unk28[0]->set_rectangle(0, 1, 488, 223, 0x80808080, 0);
        unk28[0]->unk18->func_001E0520(-244.0f, -112.0f, 0.0f);
    }

    if (unk28[1] == 0)
    {
        unk28[1] = new (0) BootImage;
        unk28[1]->set_texture((const BootTextureResource*)(((u32)unk1C[1] + 0x7F) & ~0x7F), 0);
        unk28[1]->set_rectangle(0, 0, 640, 80, 0x80808080, 0);
        unk28[1]->unk18->func_001E0520(-320.0f, -216.0f, 0.0f);
    }

    if (boot_settings()->widescreen)
    {
        if (unk28[1] != 0)
        {
            unk28[1]->unk18->func_001E0520(-422.66668f, -216.0f, 0.0f);
            unk28[1]->unk18->func_001DDED0(1.31f, 1.0f, 1.0f);
        }
    }
    else if (unk28[1] != 0)
    {
        unk28[1]->unk18->func_001E0520(-320.0f, -216.0f, 0.0f);
        unk28[1]->unk18->func_001DDED0(1.0f, 1.0f, 1.0f);
    }

    if (bar_fading && unkC0 != 0)
    {
        unkC0->unk18->func_001E94E0(2);
        set_bar_color(unkC0, 1.0f, 1.0f, 1.0f, bar_alpha);
        bar_alpha -= 2.0f * D_001B6690;

        if (bar_alpha < 0.0f)
        {
            bar_fading = 0;
            lib_object_detach_owner(unkC0);
            unkC0->destroy();
            unkC0 = 0;
        }
    }
}

/**
 * @brief Check that a trophy's record carries the key the game gave it.
 * @param record Trophy record.
 * @param index Trophy number.
 * @return True when the record's key matches.
 */
static inline bool trophy_genuine(const BootTrophyRecordF10* record, s32 index)
{
    u32 key = g_trophy_keys[index] ^ 0x943FED16 ^ (boot_settings()->unk1A8.unk14 ^ 0x23DACE93);
    return key == record->unk0C;
}

/**
 * @brief Save a byte of the extra protected block and reseal it, unless its checksum is already broken.
 * @param settings System settings.
 * @param field Byte to save.
 * @param value Value to save.
 */
static inline void settings_set_extra_byte(BootResource0970* settings, u8* field, u8 value)
{
    s32 length;
    u8* data = &settings->unk1A0;
    length = (u8*)&settings->extra_checksum - data;

    if (settings->extra_checksum == func_457470(settings->extra_key, data, length))
    {
        *field = value;
        settings->extra_key = resident_next_random_word();
        settings->extra_checksum = func_457470(settings->extra_key, data, length);
    }
}

/**
 * @brief Convert a two-digit binary-coded decimal byte.
 * @param value Byte holding two decimal digits.
 * @return The number it holds.
 */
static inline s32 from_bcd(u8 value)
{
    return (value & 0xF) + ((value & 0xF0) >> 4) * 10;
}

/**
 * @brief Return the screen x of the cursor's grid column for the screen shape.
 * @param viewer Viewer whose cursor is placed.
 * @return Cursor x.
 */
static inline float grid_cursor_x(BootBattleTrophyViewer* viewer)
{
    if (boot_settings()->widescreen)
    {
        return viewer->cursor_column * 52 + 132;
    }

    return viewer->cursor_column * 68 + 64;
}

/**
 * @brief Slide the cursor to the selected grid cell.
 * @param viewer Viewer whose cursor moves.
 */
static inline void move_grid_cursor(BootBattleTrophyViewer* viewer)
{
    viewer->cursor->func_00466E40(grid_cursor_x(viewer), viewer->cursor_row * 100 + 170, 0.05f);
    func_112400(D_001B65F8, 0, 0, 0, 0x7F, 0x40, 0);
}

/** @brief Run the viewer: choose a memory card slot, load its trophy data, then browse the trophy grid. */
void BootBattleTrophyViewer::update()
{
    BootInput* input = g_boot_program.get_input();
    BootResource0970* settings = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);
    s32 card_states[2];
    card_states[0] = input->unk28;
    card_states[1] = input->unk2C;
    s32 slot1_ready = input->slot1_ready;
    s32 slot2_ready = input->slot2_ready;
    BootResourceBits0970* bits = &settings->unk1A8;

    switch (step)
    {
    case 0:
        if (func_102D00(D_001B65E8) != 0)
        {
            func_112990(D_001B65F8, 0x48, 1, 0, 0);
            func_4DF6E0(g_boot_program.display, 0x49, 0x47, 0x9D, 0x7F);

            if (*((BootResidentRoot15CC0*)func_10D8E0())->status != 0x67)
            {
                step++;
            }

            D_001B661C->prepend_node(new (0) BootClass179150, -1);
            unk88 = new (0) BootClass178660(9, 0.0f, 0.0f, 0.0f);
            func_465B20(D_001B657C, unk88);
        }

        break;
    case 1:
        unk1C[images_loaded] = func_102920(D_001B65EC, resource_data, images_loaded, 1);
        func_1025A0(D_001B65EC, resource_data, (void*)(((u32)unk1C[images_loaded] + 0x7F) & ~0x7F), images_loaded);

        if (++images_loaded >= 3)
        {
            step++;
            func_121FE0(0);
        }

        break;
    case 2:
        if (message_text != 0)
        {
            message_text->destroy();
        }

        if (slot1_text != 0)
        {
            slot1_text->destroy();
        }

        if (slot2_text != 0)
        {
            slot2_text->destroy();
        }

        if (cursor != 0)
        {
            cursor->destroy();
        }

        message_text = new (0) BootClass178750(g_boot_program.get_messages(), 0x65, 1, 32.0f, 88.0f, 576.0f, 224.0f);
        slot1_text = new (0) BootClass178750(g_boot_program.get_messages(), 0x66, 1, 180.0f, 144.0f, 512.0f, 224.0f);
        slot2_text = new (0) BootClass178750(g_boot_program.get_messages(), 0x67, 1, 180.0f, 184.0f, 512.0f, 224.0f);
        lib_container_attach_widget(unk88, message_text);
        lib_container_attach_widget(unk88, slot1_text);
        lib_container_attach_widget(unk88, slot2_text);
        message_text->set_color(0x34130F);
        slot1_text->set_color(0x34130F);
        slot2_text->set_color(0x34130F);
        step = 5;
        slot = 0;
        cursor = new (0) BootClass175070;
        func_467570(cursor, 1, 0, 0, 170.0f, 156.0f, 0.0f);
        func_465B20(D_001B657C, cursor);
        break;
    case 3:
        if (input->pressed & settings->unk00)
        {
            func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
            queue_fade();
            step++;
        }

        break;
    case 4:
        func_4DF6E0(g_boot_program.display, 0, 0, 0, 0x7F);
        func_10F000(D_001B65F8, 0x1E, -1);
        release();
        D_001B6614->append_node(new (0) BootTitleMenu(2), -1);
        lib_object_detach_owner(this);
        destroy();
        return;
    case 5:
        if ((input->repeated & 0x50) && cursor->unk35)
        {
            float y;
            slot = (slot + 1) & 1;

            if (slot != 0)
            {
                y = 196.0f;
            }
            else
            {
                y = 156.0f;
            }

            cursor->func_00466E40(170.0f, y, 0.05f);
            func_112400(D_001B65F8, 0, 0, 0, 0x7F, 0x40, 0);
        }

        if (input->pressed & settings->unk00)
        {
            if (slot_ready[slot])
            {
                if (card_states[slot] == 5)
                {
                    func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
                }
                else
                {
                    func_112400(D_001B65F8, 3, 0, 0, 0x7F, 0x40, 0);
                }

                queue_fade();
                step = 13;
            }
            else
            {
                func_112400(D_001B65F8, 3, 0, 0, 0x7F, 0x40, 0);
                step = 15;
            }
        }
        else if (input->pressed & settings->unk02)
        {
            func_112400(D_001B65F8, 2, 0, 0, 0x7F, 0x40, 0);
            queue_fade();
            step = 4;
        }

        break;
    case 13:
        if (card_states[slot] == 5)
        {
            step = 6;
        }
        else
        {
            step = 14;
            cursor->destroy();
            cursor = 0;
            slot1_text->destroy();
            slot1_text = 0;
            slot2_text->destroy();
            slot2_text = 0;
            lib_text_set_resource(message_text, g_boot_program.get_messages(), slot != 0 ? 0x84 : 0x7B, 0);
        }

        break;
    case 14:
        if (input->pressed & (settings->unk00 | settings->unk02))
        {
            func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
            queue_fade();
            step = 2;
        }

        break;
    case 15:
        step = 14;
        cursor->destroy();
        cursor = 0;
        slot1_text->destroy();
        slot1_text = 0;
        slot2_text->destroy();
        slot2_text = 0;
        lib_text_set_resource(message_text, g_boot_program.get_messages(), slot != 0 ? 0x86 : 0x85, 0);
        break;
    case 6:
        func_121FE0(0);

        if (records != 0)
        {
            delete[] records;
        }

        records = new (0) BootTrophyRecordF10[300];
        lib_text_set_resource(message_text, g_boot_program.get_messages(), slot != 0 ? 0x82 : 0x68, 0);

        if (slot1_text != 0)
        {
            slot1_text->destroy();
            slot1_text = 0;
        }

        if (slot2_text != 0)
        {
            slot2_text->destroy();
            slot2_text = 0;
        }

        if (cursor != 0)
        {
            cursor->destroy();
            cursor = 0;
        }

        if (g_boot_program.trophy_card->func_001E0C30(slot, records) != 0)
        {
            input->card_query_enabled = 0;

            if (unkC0 == 0)
            {
                unkC0 = new (0) BootProgressBar;
                func_001F8720(unkC0, 0xF0, 0x18, 0x80FFFFFF, 0);
            }

            unkC0->unk18->func_001E0520(-120.0f, 184.0f, 0.0f);
            load_time = 0.0f;
            bar_fading = 0;
            bar_alpha = 1.0f;
            step++;
        }

        break;
    case 7:
        if (g_boot_program.trophy_card->func_001E0AE0() == 1)
        {
            input->card_query_enabled = 1;
            queue_fade();
            step++;
        }
        else
        {
            load_time += D_001B6690;
            s32 progress = 1000.0f * load_time / 6.9f;

            if (progress > 995)
            {
                progress = 995;
            }

            func_001F79A0(unkC0, progress, 1000);
        }

        break;
    case 8:
        bar_fading = 1;

        if (g_boot_program.trophy_card->func_001E0AD0() < 0)
        {
            step = 11;
            return;
        }

        if (unkC0 != 0)
        {
            func_001F79A0(unkC0, 100, 100);
        }

        if (create_trophy_images() == 0)
        {
            step = 16;
            return;
        }

        if (message_text != 0)
        {
            message_text->destroy();
            message_text = 0;
        }

        cursor_column = 0;
        cursor_row = 0;
        first_row = 0;
        scroll_step = 0;
        unk70 = 0;
        step++;
        sort_text = new (0) BootClass178750(g_boot_program.get_messages(), 0x6F, 1, 430.0f, 55.0f, 512.0f, 224.0f);
        sort_text->set_color(0x34130F);

        if (settings->widescreen)
        {
            unkA8 = new (0) BootClass178750(g_boot_program.get_messages(), 0x6A, 1, 96.0f, 22.0f, 512.0f, 16.0f);
            scroll_indicator = new (0) BootClass1725D0(531.0f, 82.0f, 329.0f, 300.0f / 38.0f, 0.0f);
            number_label = new (0) BootClass175140(g_first_trophy_number, 1, 48.0f, 414.0f, 512.0f, 224.0f);
            name_text = new (0) BootClass178750(g_boot_program.get_messages(), 0x6B, 1, 96.0f, 414.0f, 512.0f, 224.0f);
            date_text = new (0) BootClass178750(g_boot_program.get_messages(), 0x6C, 1, 96.0f, 438.0f, 512.0f, 224.0f);
        }
        else
        {
            unkA8 = new (0) BootClass178750(g_boot_program.get_messages(), 0x6A, 1, 96.0f, 24.0f, 512.0f, 224.0f);
            scroll_indicator = new (0) BootClass1725D0(595.0f, 84.0f, 323.0f, 300.0f / 38.0f, 0.0f);
            number_label = new (0) BootClass175140(g_first_trophy_number, 1, 48.0f, 411.0f, 512.0f, 224.0f);
            name_text = new (0) BootClass178750(g_boot_program.get_messages(), 0x6B, 1, 96.0f, 411.0f, 512.0f, 224.0f);
            date_text = new (0) BootClass178750(g_boot_program.get_messages(), 0x6C, 1, 96.0f, 435.0f, 512.0f, 224.0f);
        }

        sort_text->set_color(0x34130F);
        unkA8->set_color(0x34130F);
        number_label->set_color(0x34130F);
        name_text->set_color(0x34130F);
        date_text->set_color(0x34130F);
        lib_container_attach_widget(unk88, number_label);
        lib_container_attach_widget(unk88, name_text);
        lib_container_attach_widget(unk88, date_text);
        lib_container_attach_widget(unk88, scroll_indicator);
        lib_container_attach_widget(unk88, unkA8);
        lib_container_attach_widget(unk88, sort_text);
        rank = 0;
        rank_timer = 0.0f;
        shown_rank = 0;

        if (flags_intact(bits))
        {
            s32 score = 0;

            for (s32 i = 0; i < 300; i++)
            {
                if (resource_bit(bits, i) && trophy_genuine(&records[i], i))
                {
                    score += 13;
                }
            }

            if (score >= 585)
            {
                rank_text = new (0) BootClass178750(g_boot_program.get_messages(), 0x71, 1, 32.0f, 55.0f, 512.0f, 22.0f);
                rank_text->set_vertical_align(2);
                lib_container_attach_widget(unk88, rank_text);
                rank_text->set_color(0x34130F);
                rank = 0;
            }

            if (score >= 585)
            {
                settings_set_extra_byte(settings, &settings->unk1A3, 1);
                rank = 0;
            }

            if (score >= 975)
            {
                settings_set_extra_byte(settings, &settings->universe_unlocked, 1);
                rank = 1;
            }

            if (score >= 1560)
            {
                settings_set_extra_byte(settings, &settings->unk1A3, 2);
                rank = 2;
            }

            if (score >= 2145)
            {
                rank = 3;
            }

            if (score >= 2535)
            {
                rank = 4;
                settings_set_extra_byte(settings, &settings->fourth_dimension_unlocked, 1);
            }

            if (score >= 3120)
            {
                settings_set_extra_byte(settings, &settings->unk1A3, 3);
                rank = 5;
            }

            if (score >= 3705)
            {
                rank = 6;
                settings_set_extra_byte(settings, &settings->unk1A0, 1);
            }
        }

        D_001B657C->message_values[0] = earned_count;
        D_001B657C->message_values[1] = 300;
        D_001B657C->message_values[2] = earned_count * 100 / 300;
        cursor = new (0) BootClass175070;
        func_467570(cursor, 1, 0, 0, grid_cursor_x(this), cursor_row * 100 + 170, 0.0f);
        func_465B20(D_001B657C, cursor);
        break;
    case 9:
    {
        if (input->pressed & settings->unk02)
        {
            func_112400(D_001B65F8, 2, 0, 0, 0x7F, 0x40, 0);
            queue_fade();
            step = 4;
            return;
        }

        s32 score = 0;

        if (flags_intact(bits))
        {
            for (s32 i = 0; i < 300; i++)
            {
                if (resource_bit(bits, i) && trophy_genuine(&records[i], i))
                {
                    score += 17;
                }
            }

            if (*((BootResidentRoot15CC0*)func_10D8E0())->status != 0x67)
            {
                if (score < 765)
                {
                    if (rank_text != 0)
                    {
                        rank_text->destroy();
                        rank_text = 0;
                    }

                    settings_set_extra_byte(settings, &settings->unk1A3, 0);
                    rank = 0;
                }
                else if (score < 1275)
                {
                    settings_set_extra_byte(settings, &settings->universe_unlocked, 0);
                    rank = 0;
                }
                else if (score < 2040)
                {
                    settings_set_extra_byte(settings, &settings->unk1A3, 1);
                    rank = 1;
                }
                else if (score < 2805)
                {
                    rank = 2;
                }
                else if (score < 3315)
                {
                    rank = 3;
                    settings_set_extra_byte(settings, &settings->fourth_dimension_unlocked, 0);
                }
                else if (score < 4080)
                {
                    settings_set_extra_byte(settings, &settings->unk1A3, 2);
                    rank = 4;
                }
                else if (score < 4845)
                {
                    rank = 5;
                    settings_set_extra_byte(settings, &settings->unk1A0, 0);
                }
            }

            s32 selected = cursor_column + (cursor_row + first_row + positive(scroll_step) - (scroll_step < 0)) * 8;

            if (selected >= 300)
            {
                lib_text_set_resource(name_text, g_boot_program.get_messages(), 0x6C, 0);
                lib_text_set_resource(date_text, g_boot_program.get_messages(), 0x6C, 0);
            }
            else
            {
                s32 index = order[selected];

                if (resource_bit(bits, index) && trophy_genuine(&records[index], index))
                {
                    lib_text_set_resource(name_text, g_boot_program.get_messages(), index + 200, 0);
                    BootTrophyTime* time = &records[index].time;
                    D_001B657C->message_values[3] = from_bcd(time->year);
                    D_001B657C->message_values[4] = from_bcd(time->month);
                    D_001B657C->message_values[5] = from_bcd(time->day);
                    D_001B657C->message_values[6] = from_bcd(time->hour);
                    D_001B657C->message_values[7] = from_bcd(time->minute);
                    D_001B657C->message_values[8] = from_bcd(time->second);

                    if (time->year >= 0x10)
                    {
                        lib_text_set_resource(date_text, g_boot_program.get_messages(), 0x6E, 0);
                    }
                    else
                    {
                        lib_text_set_resource(date_text, g_boot_program.get_messages(), 0x6D, 0);
                    }
                }
                else
                {
                    lib_text_set_resource(name_text, g_boot_program.get_messages(), 0x6B, 0);
                    lib_text_set_resource(date_text, g_boot_program.get_messages(), 0x6C, 0);
                }
            }
        }

        if (score >= 2805 && (input->pressed & settings->unk06))
        {
            func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
            queue_fade();
            step = 10;
            return;
        }

        if (rank_text != 0)
        {
            rank_timer += D_001B6690;

            if (!(rank_timer < 3.0f))
            {
                rank_timer = 0.0f;

                shown_rank--;

                if (shown_rank < 0)
                {
                    shown_rank = rank;
                }

                lib_text_set_resource(rank_text, g_boot_program.get_messages(), shown_rank + 0x71, 0);
            }
        }

        if (unk1144 < 300)
        {
            if (flags_intact(bits))
            {
                if (trophy_genuine(&records[unk1144], unk1144) && resource_bit(bits, unk1144))
                {
                    unkC94[unk1144] = 1e-05f;
                }
            }

            unk1144++;
        }

        if (cursor->unk35 && scroll_step == 0 && unk70 == 0)
        {
            if (input->repeated & 0x20)
            {
                cursor_column++;

                if (cursor_column > 7)
                {
                    cursor_column = 0;
                    cursor_row++;

                    if (cursor_row > 2)
                    {
                        cursor_row = 2;

                        if (first_row < row_count - 3)
                        {
                            scroll_step = 1;
                        }
                    }
                }

                move_grid_cursor(this);
            }

            if (input->repeated & 0x80)
            {
                cursor_column--;

                if (cursor_column < 0)
                {
                    cursor_column = 7;
                    cursor_row--;

                    if (cursor_row < 0)
                    {
                        cursor_row = 0;

                        if (first_row > 0)
                        {
                            scroll_step = -1;
                        }
                    }
                }

                move_grid_cursor(this);
            }

            if (input->repeated & 0x10)
            {
                cursor_row--;

                if (cursor_row < 0)
                {
                    cursor_row = 0;

                    if (first_row > 0)
                    {
                        scroll_step = -1;
                        func_112400(D_001B65F8, 0, 0, 0, 0x7F, 0x40, 0);
                    }
                }
                else
                {
                    move_grid_cursor(this);
                }
            }

            if (page_delay != 0)
            {
                page_delay--;
            }

            if (input->repeated & 0x40)
            {
                cursor_row++;

                if (cursor_row > 2)
                {
                    cursor_row = 2;

                    if (first_row < row_count - 3)
                    {
                        scroll_step = 1;
                        func_112400(D_001B65F8, 0, 0, 0, 0x7F, 0x40, 0);
                    }
                }
                else
                {
                    move_grid_cursor(this);
                }
            }

            if ((input->repeated & 0x400) && page_delay == 0)
            {
                s32 top = 0;

                if (scroll_step == -1)
                {
                    top++;
                }

                if (top < first_row)
                {
                    first_row -= 3;

                    if (first_row < top)
                    {
                        first_row = top;
                    }

                    page_delay = 4;
                    func_112400(D_001B65F8, 0, 0, 0, 0x7F, 0x40, 0);
                }
                else if (cursor_row > 0)
                {
                    cursor_row = 0;
                    move_grid_cursor(this);
                }
            }

            if ((input->repeated & 0x800) && page_delay == 0)
            {
                s32 bottom = row_count - 3;

                if (scroll_step == 1)
                {
                    bottom--;
                }

                if (first_row < bottom)
                {
                    first_row += 3;

                    if (bottom < first_row)
                    {
                        first_row = bottom;
                    }

                    page_delay = 4;
                    func_112400(D_001B65F8, 0, 0, 0, 0x7F, 0x40, 0);
                }
                else if (cursor_row < 2)
                {
                    cursor_row = 2;
                    move_grid_cursor(this);
                }
            }

            if (input->pressed & settings->unk04)
            {
                func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
                by_time ^= 1;
                sort_trophies(by_time);
                lib_text_set_resource(sort_text, g_boot_program.get_messages(), by_time + 0x6F, 0);
            }
        }

        if (unk70 != 0)
        {
            unk70--;
        }

        if (scroll_indicator != 0)
        {
            scroll_indicator->set_position(100.0f * first_row / 38.0f);
        }

        break;
    }
    case 10:
        func_4DF6E0(g_boot_program.display, 0, 0, 0, 0x7F);
        func_10F000(D_001B65F8, 0x1E, -1);
        release();
        D_001B6614->append_node(new (0) BootMusicPlayer, -1);
        lib_object_detach_owner(this);
        destroy();
        return;
    case 11:
        lib_text_set_resource(message_text, g_boot_program.get_messages(), slot != 0 ? 0x83 : 0x78, 0);
        step++;
        break;
    case 12:
        if (input->pressed & settings->unk00)
        {
            func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
            queue_fade();
            step = 4;
        }

        break;
    case 16:
        lib_text_set_resource(message_text, g_boot_program.get_messages(), slot != 0 ? 0x88 : 0x87, 0);
        step = 12;
        break;
    }

    if (slot1_text != 0)
    {
        if (slot1_ready)
        {
            slot1_text->set_tint(0x808080);
            slot_ready[0] = 1;
        }
        else
        {
            slot1_text->set_tint(0x404040);
            slot_ready[0] = 0;
        }
    }

    if (slot2_text != 0)
    {
        if (slot2_ready)
        {
            slot2_text->set_tint(0x808080);
            slot_ready[1] = 1;
        }
        else
        {
            slot2_text->set_tint(0x404040);
            slot_ready[1] = 0;
        }
    }

    update_images();
    update_grid();
}
}
