#include "include_asm.h"
#include "overlays/lib/vector.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/boot/text_001EEC80.h"
#include "overlays/boot/text_001F6010.h"
#include "overlays/boot/text_001DD3C0.h"
#include "overlays/boot/text_001E0900.h"
#include "overlays/boot/text_001FB220.h"
#include "overlays/boot/text_001FF9D0.h"
#include "overlays/boot/resident.h"
#include "main/resident_001001E0.h"

extern "C" {

/** Name given to every trophy texture. */
extern const char g_trophy_texture_name[];

extern const char g_no_trophy_number[];
extern const char g_trophy_number_format[];
char* func_13CD50(char* destination, const char* source, u32 size);
s32 func_13C4F0(char* destination, const char* format, ...);
void func_4CD810(FieldVec4B* output, const BootVector4DDAA0* axis_angle);
void func_4CD630(FieldVec4B* output, const FieldVec4B* from, const FieldVec4B* to, float t);
s32 func_457220(BootTrophyRecord* record);

/** Key each trophy record must carry, stored XOR-encoded. */
extern const u32 g_trophy_keys[];

/** Text of the number label before the grid first updates it. */
extern const char g_first_trophy_number[];

void lib_container_attach_widget(BootContainer* container, BootListObject* child);
void lib_text_set_resource(BootTextWidget* text, s32 slot, u32 key, u8 flag);
}

/** Stages of the Battle Trophies screen's card selection, transfer, and viewer flow. */
enum BootTrophyViewerStep
{
    BOOT_TROPHY_WAIT_FOR_RESOURCES = 0,
    BOOT_TROPHY_DECODE_IMAGES = 1,
    BOOT_TROPHY_SHOW_SLOT_CHOICES = 2,
    BOOT_TROPHY_WAIT_FOR_EXIT = 3,
    BOOT_TROPHY_RETURN_TO_TITLE = 4,
    BOOT_TROPHY_CHOOSE_SLOT = 5,
    BOOT_TROPHY_START_TRANSFER = 6,
    BOOT_TROPHY_WAIT_FOR_TRANSFER = 7,
    BOOT_TROPHY_CHECK_TRANSFER = 8,
    BOOT_TROPHY_BROWSE = 9,
    BOOT_TROPHY_OPEN_MUSIC_PLAYER = 10,
    BOOT_TROPHY_SHOW_TRANSFER_ERROR = 11,
    BOOT_TROPHY_WAIT_FOR_ERROR_ACKNOWLEDGEMENT = 12,
    BOOT_TROPHY_CHECK_SLOT = 13,
    BOOT_TROPHY_WAIT_FOR_SLOT_MESSAGE = 14,
    BOOT_TROPHY_SHOW_UNAVAILABLE_SLOT = 15,
    BOOT_TROPHY_SHOW_INVALID_RECORD = 16
};

enum BootTrophyGrid
{
    BOOT_TROPHY_GRID_COLUMNS = 8,
    BOOT_TROPHY_GRID_ROWS = (BOOT_TROPHY_COUNT + BOOT_TROPHY_GRID_COLUMNS - 1) / BOOT_TROPHY_GRID_COLUMNS
};

/** Earned trophy counts that advance the viewer rank and unlock settings. */
enum BootTrophyMilestone
{
    BOOT_TROPHY_FIRST_COLOR_COUNT = 45,
    BOOT_TROPHY_UNIVERSE_COUNT = 75,
    BOOT_TROPHY_SECOND_COLOR_COUNT = 120,
    BOOT_TROPHY_RANK_THREE_COUNT = 165,
    BOOT_TROPHY_FOURTH_DIMENSION_COUNT = 195,
    BOOT_TROPHY_THIRD_COLOR_COUNT = 240,
    BOOT_TROPHY_FINAL_RANK_COUNT = 285,

    /** The two passes use different score units for the same milestones. */
    BOOT_TROPHY_LOAD_SCORE_PER_EARNED = 13,
    BOOT_TROPHY_BROWSE_SCORE_PER_EARNED = 17
};

/**
 * @brief Report the list kind used when registration requests the default.
 * @return Four.
 */
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
    BootSystemSettings* settings = boot_settings();
    s32 index = viewer->order[position];

    if (resource_bit(&settings->trophy_flags, index))
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
    for (s32 i = 0; i < BOOT_TROPHY_COUNT; i++)
    {
        order[i] = i;
    }

    if (!newest_first)
    {
        return;
    }

    BootTrophyFlags* bits = &boot_settings()->trophy_flags;
    u32 seed = bits->checksum_seed;
    u32 checksum;
    func_457670(bits, &seed, &checksum);

    if (bits->checksum != checksum)
    {
        return;
    }

    for (s32 i = 1; i < BOOT_TROPHY_COUNT; i++)
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
void BootBattleTrophyViewer::build_trophy_texture(const BootTrophyRecord* record, BootTextureResource* texture, s32 index)
{
    func_13A4C0(texture, (void*)BOOT_ALIGN_RESOURCE(image_blocks[2]), 0x4600);
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
static inline bool flags_intact(BootTrophyFlags* bits)
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
    // Keep the forward scroll test in its helper to preserve code generation.
    s32 selected = cursor_column + (cursor_row + first_row + positive(scroll_step) - (scroll_step < 0)) * BOOT_TROPHY_GRID_COLUMNS;

    if (selected >= BOOT_TROPHY_COUNT)
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

    if (flags_intact(&boot_settings()->trophy_flags))
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

        for (s32 i = 0; i < BOOT_TROPHY_COUNT; i++)
        {
            BootModel* model;

            if (trophy_images[i] != 0 && (model = trophy_images[i]->model) != 0)
            {
                if (flip_progress[i] > 0.0f && flip_progress[i] < 1.0f)
                {
                    if (model != 0)
                    {
                        func_4CD630(&rotation, &front, &back, flip_progress[i]);
                        model->set_orientation((const BootVector4DDAA0*)&rotation);
                    }

                    flip_progress[i] += 4.0f * D_001B6690;

                    if (!(flip_progress[i] < 1.0f))
                    {
                        flip_progress[i] = 1.0f;
                    }
                }
                else if (flip_progress[i] > 0.0f)
                {
                    model->set_orientation((const BootVector4DDAA0*)&back);
                }
            }
        }
    }

    for (s32 i = 0; i < BOOT_TROPHY_COUNT; i++)
    {
        BootImage* image = trophy_images[order[i]];

        if (image != 0)
        {
            BootModel* model = image->model;
            copy_vector(&value, &model->translation);
            value.x = -236.0f + (i & (BOOT_TROPHY_GRID_COLUMNS - 1)) * 68;
            value.y = scrolled(-94.0f + i / BOOT_TROPHY_GRID_COLUMNS * 100, scroll);
            model->set_translation_vector(&value);
            copy_vector(&value, &model->scale);

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

                model->set_blend_mode(2);
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

                model->set_blend_mode(0);
            }

            model->set_scale_vector(&value);
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
static inline void set_clip(BootClipRegion* clip, s32 left, s32 top, s32 right, s32 bottom)
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
    BootSystemSettings* settings = boot_settings();
    BootTrophyFlags* bits = &settings->trophy_flags;

    if (!flags_intact(bits))
    {
        return 0;
    }

    earned_count = 0;

    if (flags_intact(bits))
    {
        for (s32 i = 0; i < BOOT_TROPHY_COUNT; i++)
        {
            BootTrophyRecord* record = &records[i];

            if (func_457220(record) == 0 || *((BootResidentRoot15CC0*)resident_get_runtime_owner())->status == 0x67)
            {
                set_resource_bit(bits, i, 0);
                record->key = 0;
                func_457520(bits);
                return 0;
            }
        }
    }

    for (s32 i = 0; i < BOOT_TROPHY_COUNT; i++)
    {
        order[i] = i;
        textures[i] = (BootTextureResource*)func_139700(0x80, 0x4600);
    }

    grid_clip = new (0) BootClipRegion;
    D_001B661C->append_node(grid_clip, -1);

    if (settings->widescreen)
    {
        set_clip(grid_clip, 0, 0x4D, 0x27F, 0x180);
    }
    else
    {
        set_clip(grid_clip, 0, 0x50, 0x27F, 0x17C);
    }

    if (flags_intact(bits))
    {
        for (s32 i = 0; i < BOOT_TROPHY_COUNT; i++)
        {
            trophy_images[i] = new (0) BootImage;
            trophy_images[i]->centered = 1;
            flip_progress[i] = 0.0f;

            if (resource_bit(bits, i))
            {
                build_trophy_texture(&records[i], textures[i], i);
                trophy_images[i]->set_texture((const BootTextureResource*)BOOT_ALIGN_RESOURCE(image_blocks[0]), textures[i]);
                image_set_rectangle_with_palette(trophy_images[i], 0, 0xE2, 0x44, 0x64, 0, 0, 0x40, 0x60, 0x80808080, 0);
                earned_count++;
            }
            else
            {
                trophy_images[i]->set_texture((const BootTextureResource*)BOOT_ALIGN_RESOURCE(image_blocks[0]), 0);
                trophy_images[i]->set_rectangle(0, 0xE2, 0x44, 0x64, 0x80808080, 0);
            }

            trophy_images[i]->model->set_translation(-236.0f + (i & (BOOT_TROPHY_GRID_COLUMNS - 1)) * 68,
                                                     -94.0f + i / BOOT_TROPHY_GRID_COLUMNS * 100, 0.0f);
        }
    }
    else
    {
        for (s32 i = 0; i < BOOT_TROPHY_COUNT; i++)
        {
            trophy_images[i] = new (0) BootImage;
            trophy_images[i]->centered = 1;
            trophy_images[i]->set_texture((const BootTextureResource*)BOOT_ALIGN_RESOURCE(image_blocks[0]), 0);
            trophy_images[i]->set_rectangle(0, 0xE2, 0x44, 0x64, 0x80808080, 0);
            trophy_images[i]->model->set_translation(-236.0f + (i & (BOOT_TROPHY_GRID_COLUMNS - 1)) * 68,
                                                     -94.0f + i / BOOT_TROPHY_GRID_COLUMNS * 100, 0.0f);
        }
    }

    FlushCache(0);
    screen_clip = new (0) BootClipRegion;
    D_001B661C->append_node(screen_clip, -1);
    screen_clip->display = g_boot_program.display;
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
    BootModel* model = bar->model;
    copy_vector(&model->base_color_factor, &color);
    model->update_combined_color_factor();
}

/** @brief Create the two screen images once the pictures load, place them for the screen shape and fade out the bar. */
void BootBattleTrophyViewer::update_images()
{
    if (image_blocks[2] == 0)
    {
        return;
    }

    if (images[0] == 0)
    {
        images[0] = new (0) BootImage;
        images[0]->set_texture((const BootTextureResource*)BOOT_ALIGN_RESOURCE(image_blocks[0]), 0);
        images[0]->set_rectangle(0, 1, 488, 223, 0x80808080, 0);
        images[0]->model->set_translation(-244.0f, -112.0f, 0.0f);
    }

    if (images[1] == 0)
    {
        images[1] = new (0) BootImage;
        images[1]->set_texture((const BootTextureResource*)BOOT_ALIGN_RESOURCE(image_blocks[1]), 0);
        images[1]->set_rectangle(0, 0, 640, 80, 0x80808080, 0);
        images[1]->model->set_translation(-320.0f, -216.0f, 0.0f);
    }

    if (boot_settings()->widescreen)
    {
        if (images[1] != 0)
        {
            images[1]->model->set_translation(-422.66668f, -216.0f, 0.0f);
            images[1]->model->set_scale(1.31f, 1.0f, 1.0f);
        }
    }
    else if (images[1] != 0)
    {
        images[1]->model->set_translation(-320.0f, -216.0f, 0.0f);
        images[1]->model->set_scale(1.0f, 1.0f, 1.0f);
    }

    if (bar_fading && progress_bar != 0)
    {
        progress_bar->model->set_blend_mode(2);
        set_bar_color(progress_bar, 1.0f, 1.0f, 1.0f, bar_alpha);
        bar_alpha -= 2.0f * D_001B6690;

        if (bar_alpha < 0.0f)
        {
            bar_fading = 0;
            lib_object_detach_owner(progress_bar);
            progress_bar->destroy();
            progress_bar = 0;
        }
    }
}

/**
 * @brief Check that a trophy's record carries the key the game gave it.
 * @param record Trophy record.
 * @param index Trophy number.
 * @return True when the record's key matches.
 */
static inline bool trophy_genuine(const BootTrophyRecord* record, s32 index)
{
    u32 key = g_trophy_keys[index] ^ 0x943FED16 ^ (boot_settings()->trophy_flags.trophy_key ^ 0x23DACE93);
    return key == record->key;
}

/**
 * @brief Save a byte of the extra protected block and reseal it, unless its checksum is already broken.
 * @param settings System settings.
 * @param field Byte to save.
 * @param value Value to save.
 */
static inline void settings_set_extra_byte(BootSystemSettings* settings, u8* field, u8 value)
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
    BootSystemSettings* settings = (BootSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_runtime_owner()), 1);
    s32 card_states[2];
    card_states[0] = input->slot1_raw_state;
    card_states[1] = input->slot2_raw_state;
    s32 slot1_ready = input->slot1_ready;
    s32 slot2_ready = input->slot2_ready;
    BootTrophyFlags* bits = &settings->trophy_flags;

    switch (step)
    {
    case BOOT_TROPHY_WAIT_FOR_RESOURCES:
        if (func_102D00(D_001B65E8) != 0)
        {
            func_112990(D_001B65F8, 0x48, 1, 0, 0);
            func_4DF6E0(g_boot_program.display, 0x49, 0x47, 0x9D, 0x7F);

            if (*((BootResidentRoot15CC0*)resident_get_runtime_owner())->status != 0x67)
            {
                step++;
            }

            D_001B661C->prepend_node(new (0) BootClass179150, -1);
            container = new (0) BootContainer(9, 0.0f, 0.0f, 0.0f);
            func_465B20(D_001B657C, container);
        }

        break;
    case BOOT_TROPHY_DECODE_IMAGES:
        image_blocks[images_loaded] = func_102920(g_resident_resource_decoder, resource_data, images_loaded, 1);
        func_1025A0(g_resident_resource_decoder, resource_data, (void*)BOOT_ALIGN_RESOURCE(image_blocks[images_loaded]), images_loaded);

        if (++images_loaded >= 3)
        {
            step++;
            FlushCache(0);
        }

        break;
    case BOOT_TROPHY_SHOW_SLOT_CHOICES:
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

        message_text = new (0) BootTextWidget(g_boot_program.get_messages(), 0x65, 1, 32.0f, 88.0f, 576.0f, 224.0f);
        slot1_text = new (0) BootTextWidget(g_boot_program.get_messages(), 0x66, 1, 180.0f, 144.0f, 512.0f, 224.0f);
        slot2_text = new (0) BootTextWidget(g_boot_program.get_messages(), 0x67, 1, 180.0f, 184.0f, 512.0f, 224.0f);
        lib_container_attach_widget(container, message_text);
        lib_container_attach_widget(container, slot1_text);
        lib_container_attach_widget(container, slot2_text);
        message_text->set_color(0x34130F);
        slot1_text->set_color(0x34130F);
        slot2_text->set_color(0x34130F);
        step = BOOT_TROPHY_CHOOSE_SLOT;
        slot = 0;
        cursor = new (0) BootSelectionCursor;
        func_467570(cursor, 1, 0, 0, 170.0f, 156.0f, 0.0f);
        func_465B20(D_001B657C, cursor);
        break;
    case BOOT_TROPHY_WAIT_FOR_EXIT:
        if (input->pressed & settings->confirm_buttons)
        {
            func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
            queue_fade();
            step++;
        }

        break;
    case BOOT_TROPHY_RETURN_TO_TITLE:
        func_4DF6E0(g_boot_program.display, 0, 0, 0, 0x7F);
        func_10F000(D_001B65F8, 0x1E, -1);
        release();
        D_001B6614->append_node(new (0) BootTitleMenu(BOOT_TITLE_ITEM_BATTLE_TROPHIES), -1);
        lib_object_detach_owner(this);
        destroy();
        return;
    case BOOT_TROPHY_CHOOSE_SLOT:
        if ((input->repeated & (BOOT_BUTTON_UP | BOOT_BUTTON_DOWN)) && cursor->unk35)
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

        if (input->pressed & settings->confirm_buttons)
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
                step = BOOT_TROPHY_CHECK_SLOT;
            }
            else
            {
                func_112400(D_001B65F8, 3, 0, 0, 0x7F, 0x40, 0);
                step = BOOT_TROPHY_SHOW_UNAVAILABLE_SLOT;
            }
        }
        else if (input->pressed & settings->cancel_buttons)
        {
            func_112400(D_001B65F8, 2, 0, 0, 0x7F, 0x40, 0);
            queue_fade();
            step = BOOT_TROPHY_RETURN_TO_TITLE;
        }

        break;
    case BOOT_TROPHY_CHECK_SLOT:
        if (card_states[slot] == 5)
        {
            step = BOOT_TROPHY_START_TRANSFER;
        }
        else
        {
            step = BOOT_TROPHY_WAIT_FOR_SLOT_MESSAGE;
            cursor->destroy();
            cursor = 0;
            slot1_text->destroy();
            slot1_text = 0;
            slot2_text->destroy();
            slot2_text = 0;
            lib_text_set_resource(message_text, g_boot_program.get_messages(), slot != 0 ? 0x84 : 0x7B, 0);
        }

        break;
    case BOOT_TROPHY_WAIT_FOR_SLOT_MESSAGE:
        if (input->pressed & (settings->confirm_buttons | settings->cancel_buttons))
        {
            func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
            queue_fade();
            step = BOOT_TROPHY_SHOW_SLOT_CHOICES;
        }

        break;
    case BOOT_TROPHY_SHOW_UNAVAILABLE_SLOT:
        step = BOOT_TROPHY_WAIT_FOR_SLOT_MESSAGE;
        cursor->destroy();
        cursor = 0;
        slot1_text->destroy();
        slot1_text = 0;
        slot2_text->destroy();
        slot2_text = 0;
        lib_text_set_resource(message_text, g_boot_program.get_messages(), slot != 0 ? 0x86 : 0x85, 0);
        break;
    case BOOT_TROPHY_START_TRANSFER:
        FlushCache(0);

        if (records != 0)
        {
            delete[] records;
        }

        records = new (0) BootTrophyRecord[BOOT_TROPHY_COUNT];
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

        if (g_boot_program.trophy_card->start_transfer(slot, records) != 0)
        {
            input->card_query_enabled = 0;

            if (progress_bar == 0)
            {
                progress_bar = new (0) BootProgressBar;
                progress_bar_reset(progress_bar, 0xF0, 0x18, 0x80FFFFFF, 0);
            }

            progress_bar->model->set_translation(-120.0f, 184.0f, 0.0f);
            load_time = 0.0f;
            bar_fading = 0;
            bar_alpha = 1.0f;
            step++;
        }

        break;
    case BOOT_TROPHY_WAIT_FOR_TRANSFER:
        if (g_boot_program.trophy_card->get_transfer_state() == 1)
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

            progress_bar_draw(progress_bar, progress, 1000);
        }

        break;
    case BOOT_TROPHY_CHECK_TRANSFER:
        bar_fading = 1;

        if (g_boot_program.trophy_card->get_transfer_result() < 0)
        {
            step = BOOT_TROPHY_SHOW_TRANSFER_ERROR;
            return;
        }

        if (progress_bar != 0)
        {
            progress_bar_draw(progress_bar, 100, 100);
        }

        if (create_trophy_images() == 0)
        {
            step = BOOT_TROPHY_SHOW_INVALID_RECORD;
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
        input_delay = 0;
        step++;
        sort_text = new (0) BootTextWidget(g_boot_program.get_messages(), 0x6F, 1, 430.0f, 55.0f, 512.0f, 224.0f);
        sort_text->set_color(0x34130F);

        if (settings->widescreen)
        {
            percentage_text = new (0) BootTextWidget(g_boot_program.get_messages(), 0x6A, 1, 96.0f, 22.0f, 512.0f, 16.0f);
            scroll_indicator = new (0) BootListIndicator(531.0f, 82.0f, 329.0f, 300.0f / (float)BOOT_TROPHY_GRID_ROWS, 0.0f);
            number_label = new (0) BootStringLabel(g_first_trophy_number, 1, 48.0f, 414.0f, 512.0f, 224.0f);
            name_text = new (0) BootTextWidget(g_boot_program.get_messages(), 0x6B, 1, 96.0f, 414.0f, 512.0f, 224.0f);
            date_text = new (0) BootTextWidget(g_boot_program.get_messages(), 0x6C, 1, 96.0f, 438.0f, 512.0f, 224.0f);
        }
        else
        {
            percentage_text = new (0) BootTextWidget(g_boot_program.get_messages(), 0x6A, 1, 96.0f, 24.0f, 512.0f, 224.0f);
            scroll_indicator = new (0) BootListIndicator(595.0f, 84.0f, 323.0f, 300.0f / (float)BOOT_TROPHY_GRID_ROWS, 0.0f);
            number_label = new (0) BootStringLabel(g_first_trophy_number, 1, 48.0f, 411.0f, 512.0f, 224.0f);
            name_text = new (0) BootTextWidget(g_boot_program.get_messages(), 0x6B, 1, 96.0f, 411.0f, 512.0f, 224.0f);
            date_text = new (0) BootTextWidget(g_boot_program.get_messages(), 0x6C, 1, 96.0f, 435.0f, 512.0f, 224.0f);
        }

        sort_text->set_color(0x34130F);
        percentage_text->set_color(0x34130F);
        number_label->set_color(0x34130F);
        name_text->set_color(0x34130F);
        date_text->set_color(0x34130F);
        lib_container_attach_widget(container, number_label);
        lib_container_attach_widget(container, name_text);
        lib_container_attach_widget(container, date_text);
        lib_container_attach_widget(container, scroll_indicator);
        lib_container_attach_widget(container, percentage_text);
        lib_container_attach_widget(container, sort_text);
        rank = 0;
        rank_timer = 0.0f;
        shown_rank = 0;

        if (flags_intact(bits))
        {
            s32 score = 0;

            for (s32 i = 0; i < BOOT_TROPHY_COUNT; i++)
            {
                if (resource_bit(bits, i) && trophy_genuine(&records[i], i))
                {
                    score += BOOT_TROPHY_LOAD_SCORE_PER_EARNED;
                }
            }

            if (score >= BOOT_TROPHY_FIRST_COLOR_COUNT * BOOT_TROPHY_LOAD_SCORE_PER_EARNED)
            {
                rank_text = new (0) BootTextWidget(g_boot_program.get_messages(), 0x71, 1, 32.0f, 55.0f, 512.0f, 22.0f);
                rank_text->set_vertical_align(2);
                lib_container_attach_widget(container, rank_text);
                rank_text->set_color(0x34130F);
                rank = 0;
            }

            if (score >= BOOT_TROPHY_FIRST_COLOR_COUNT * BOOT_TROPHY_LOAD_SCORE_PER_EARNED)
            {
                settings_set_extra_byte(settings, &settings->color_unlock_level, 1);
                rank = 0;
            }

            if (score >= BOOT_TROPHY_UNIVERSE_COUNT * BOOT_TROPHY_LOAD_SCORE_PER_EARNED)
            {
                settings_set_extra_byte(settings, &settings->universe_unlocked, 1);
                rank = 1;
            }

            if (score >= BOOT_TROPHY_SECOND_COLOR_COUNT * BOOT_TROPHY_LOAD_SCORE_PER_EARNED)
            {
                settings_set_extra_byte(settings, &settings->color_unlock_level, 2);
                rank = 2;
            }

            if (score >= BOOT_TROPHY_RANK_THREE_COUNT * BOOT_TROPHY_LOAD_SCORE_PER_EARNED)
            {
                rank = 3;
            }

            if (score >= BOOT_TROPHY_FOURTH_DIMENSION_COUNT * BOOT_TROPHY_LOAD_SCORE_PER_EARNED)
            {
                rank = 4;
                settings_set_extra_byte(settings, &settings->fourth_dimension_unlocked, 1);
            }

            if (score >= BOOT_TROPHY_THIRD_COLOR_COUNT * BOOT_TROPHY_LOAD_SCORE_PER_EARNED)
            {
                settings_set_extra_byte(settings, &settings->color_unlock_level, 3);
                rank = 5;
            }

            if (score >= BOOT_TROPHY_FINAL_RANK_COUNT * BOOT_TROPHY_LOAD_SCORE_PER_EARNED)
            {
                rank = 6;
                settings_set_extra_byte(settings, &settings->unk1A0, 1);
            }
        }

        D_001B657C->message_values[0] = earned_count;
        D_001B657C->message_values[1] = BOOT_TROPHY_COUNT;
        D_001B657C->message_values[2] = earned_count * 100 / BOOT_TROPHY_COUNT;
        cursor = new (0) BootSelectionCursor;
        func_467570(cursor, 1, 0, 0, grid_cursor_x(this), cursor_row * 100 + 170, 0.0f);
        func_465B20(D_001B657C, cursor);
        break;
    case BOOT_TROPHY_BROWSE:
    {
        if (input->pressed & settings->cancel_buttons)
        {
            func_112400(D_001B65F8, 2, 0, 0, 0x7F, 0x40, 0);
            queue_fade();
            step = BOOT_TROPHY_RETURN_TO_TITLE;
            return;
        }

        s32 score = 0;

        if (flags_intact(bits))
        {
            for (s32 i = 0; i < BOOT_TROPHY_COUNT; i++)
            {
                if (resource_bit(bits, i) && trophy_genuine(&records[i], i))
                {
                    score += BOOT_TROPHY_BROWSE_SCORE_PER_EARNED;
                }
            }

            if (*((BootResidentRoot15CC0*)resident_get_runtime_owner())->status != 0x67)
            {
                if (score < BOOT_TROPHY_FIRST_COLOR_COUNT * BOOT_TROPHY_BROWSE_SCORE_PER_EARNED)
                {
                    if (rank_text != 0)
                    {
                        rank_text->destroy();
                        rank_text = 0;
                    }

                    settings_set_extra_byte(settings, &settings->color_unlock_level, 0);
                    rank = 0;
                }
                else if (score < BOOT_TROPHY_UNIVERSE_COUNT * BOOT_TROPHY_BROWSE_SCORE_PER_EARNED)
                {
                    settings_set_extra_byte(settings, &settings->universe_unlocked, 0);
                    rank = 0;
                }
                else if (score < BOOT_TROPHY_SECOND_COLOR_COUNT * BOOT_TROPHY_BROWSE_SCORE_PER_EARNED)
                {
                    settings_set_extra_byte(settings, &settings->color_unlock_level, 1);
                    rank = 1;
                }
                else if (score < BOOT_TROPHY_RANK_THREE_COUNT * BOOT_TROPHY_BROWSE_SCORE_PER_EARNED)
                {
                    rank = 2;
                }
                else if (score < BOOT_TROPHY_FOURTH_DIMENSION_COUNT * BOOT_TROPHY_BROWSE_SCORE_PER_EARNED)
                {
                    rank = 3;
                    settings_set_extra_byte(settings, &settings->fourth_dimension_unlocked, 0);
                }
                else if (score < BOOT_TROPHY_THIRD_COLOR_COUNT * BOOT_TROPHY_BROWSE_SCORE_PER_EARNED)
                {
                    settings_set_extra_byte(settings, &settings->color_unlock_level, 2);
                    rank = 4;
                }
                else if (score < BOOT_TROPHY_FINAL_RANK_COUNT * BOOT_TROPHY_BROWSE_SCORE_PER_EARNED)
                {
                    rank = 5;
                    settings_set_extra_byte(settings, &settings->unk1A0, 0);
                }
            }

            s32 selected = cursor_column + (cursor_row + first_row + positive(scroll_step) - (scroll_step < 0)) * BOOT_TROPHY_GRID_COLUMNS;

            if (selected >= BOOT_TROPHY_COUNT)
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

        if (score >= BOOT_TROPHY_RANK_THREE_COUNT * BOOT_TROPHY_BROWSE_SCORE_PER_EARNED && (input->pressed & settings->unk06))
        {
            func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
            queue_fade();
            step = BOOT_TROPHY_OPEN_MUSIC_PLAYER;
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

        if (reveal_index < BOOT_TROPHY_COUNT)
        {
            if (flags_intact(bits))
            {
                if (trophy_genuine(&records[reveal_index], reveal_index) && resource_bit(bits, reveal_index))
                {
                    flip_progress[reveal_index] = 1e-05f;
                }
            }

            reveal_index++;
        }

        if (cursor->unk35 && scroll_step == 0 && input_delay == 0)
        {
            if (input->repeated & BOOT_BUTTON_RIGHT)
            {
                cursor_column++;

                if (cursor_column > BOOT_TROPHY_GRID_COLUMNS - 1)
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

            if (input->repeated & BOOT_BUTTON_LEFT)
            {
                cursor_column--;

                if (cursor_column < 0)
                {
                    cursor_column = BOOT_TROPHY_GRID_COLUMNS - 1;
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

            if (input->repeated & BOOT_BUTTON_UP)
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

            if (input->repeated & BOOT_BUTTON_DOWN)
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

            if ((input->repeated & BOOT_BUTTON_L1) && page_delay == 0)
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

            if ((input->repeated & BOOT_BUTTON_R1) && page_delay == 0)
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

            if (input->pressed & settings->alternate_buttons)
            {
                func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
                by_time ^= 1;
                sort_trophies(by_time);
                lib_text_set_resource(sort_text, g_boot_program.get_messages(), by_time + 0x6F, 0);
            }
        }

        if (input_delay != 0)
        {
            input_delay--;
        }

        if (scroll_indicator != 0)
        {
            scroll_indicator->set_position(100.0f * first_row / (float)BOOT_TROPHY_GRID_ROWS);
        }

        break;
    }
    case BOOT_TROPHY_OPEN_MUSIC_PLAYER:
        func_4DF6E0(g_boot_program.display, 0, 0, 0, 0x7F);
        func_10F000(D_001B65F8, 0x1E, -1);
        release();
        D_001B6614->append_node(new (0) BootMusicPlayer, -1);
        lib_object_detach_owner(this);
        destroy();
        return;
    case BOOT_TROPHY_SHOW_TRANSFER_ERROR:
        lib_text_set_resource(message_text, g_boot_program.get_messages(), slot != 0 ? 0x83 : 0x78, 0);
        step++;
        break;
    case BOOT_TROPHY_WAIT_FOR_ERROR_ACKNOWLEDGEMENT:
        if (input->pressed & settings->confirm_buttons)
        {
            func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
            queue_fade();
            step = BOOT_TROPHY_RETURN_TO_TITLE;
        }

        break;
    case BOOT_TROPHY_SHOW_INVALID_RECORD:
        lib_text_set_resource(message_text, g_boot_program.get_messages(), slot != 0 ? 0x88 : 0x87, 0);
        step = BOOT_TROPHY_WAIT_FOR_ERROR_ACKNOWLEDGEMENT;
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

/** @brief Destroy every owned object and release the per-trophy allocations. */
void BootBattleTrophyViewer::release()
{
    for (s32 i = 0; i < 10; i++)
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

    if (number_label != 0)
    {
        number_label->destroy();
        number_label = 0;
    }

    if (name_text != 0)
    {
        name_text->destroy();
        name_text = 0;
    }

    if (date_text != 0)
    {
        date_text->destroy();
        date_text = 0;
    }

    if (percentage_text != 0)
    {
        percentage_text->destroy();
        percentage_text = 0;
    }

    if (sort_text != 0)
    {
        sort_text->destroy();
        sort_text = 0;
    }

    if (rank_text != 0)
    {
        rank_text->destroy();
        rank_text = 0;
    }

    if (cursor != 0)
    {
        cursor->destroy();
        cursor = 0;
    }

    if (scroll_indicator != 0)
    {
        scroll_indicator->destroy();
        scroll_indicator = 0;
    }

    for (s32 i = 0; i < BOOT_TROPHY_COUNT; i++)
    {
        if (trophy_images[i] != 0)
        {
            lib_object_detach_owner(trophy_images[i]);
            trophy_images[i]->destroy();
            trophy_images[i] = 0;
        }

        if (textures[i] != 0)
        {
            resident_queue_allocation_release(g_resident_release_queues, textures[i]);
            textures[i] = 0;
        }
    }

    if (records != 0)
    {
        delete[] records;
        records = 0;
    }

    if (grid_clip != 0)
    {
        lib_object_detach_owner(grid_clip);
        grid_clip->destroy();
        grid_clip = 0;
    }

    if (screen_clip != 0)
    {
        lib_object_detach_owner(screen_clip);
        screen_clip->destroy();
        screen_clip = 0;
    }

    if (progress_bar != 0)
    {
        progress_bar->destroy();
        progress_bar = 0;
    }
}

/** @brief Release the loaded data and every owned object. */
BootBattleTrophyViewer::~BootBattleTrophyViewer()
{
    delete unk14;

    for (s32 i = 0; i < 3; i++)
    {
        delete image_blocks[i];
    }

    for (s32 i = 0; i < 10; i++)
    {
        if (images[i] != 0)
        {
            lib_object_detach_owner(images[i]);
            images[i]->destroy();
            images[i] = 0;
        }
    }

    delete resource_data;

    for (s32 i = 0; i < BOOT_TROPHY_COUNT; i++)
    {
        if (trophy_images[i] != 0)
        {
            lib_object_detach_owner(trophy_images[i]);
            trophy_images[i]->destroy();
        }

        if (textures[i] != 0)
        {
            resident_queue_allocation_release(g_resident_release_queues, textures[i]);
        }
    }

    if (records != 0)
    {
        delete[] records;
    }

    if (container != 0)
    {
        container->destroy();
    }

    if (message_text != 0)
    {
        message_text->destroy();
    }

    if (cursor != 0)
    {
        cursor->destroy();
    }

    if (slot1_text != 0)
    {
        slot1_text->destroy();
    }

    if (slot2_text != 0)
    {
        slot2_text->destroy();
    }

    if (number_label != 0)
    {
        number_label->destroy();
    }

    if (scroll_indicator != 0)
    {
        scroll_indicator->destroy();
    }

    if (name_text != 0)
    {
        name_text->destroy();
    }

    if (date_text != 0)
    {
        date_text->destroy();
    }

    if (percentage_text != 0)
    {
        percentage_text->destroy();
    }

    if (sort_text != 0)
    {
        sort_text->destroy();
    }

    if (rank_text != 0)
    {
        rank_text->destroy();
    }

    if (progress_bar != 0)
    {
        progress_bar->destroy();
        progress_bar = 0;
    }

    if (grid_clip != 0)
    {
        lib_object_detach_owner(grid_clip);
        grid_clip->destroy();
    }

    if (screen_clip != 0)
    {
        lib_object_detach_owner(screen_clip);
        screen_clip->destroy();
    }
}

/** @brief Start loading resource 0x2B, clear the owned objects and build the three palettes. */
BootBattleTrophyViewer::BootBattleTrophyViewer()
{
    resource_data = func_139700(0x40, resident_get_resource_size(D_001B65E4, BOOT_RES_TROPHY_VIEWER));
    func_103E70(D_001B65E8, BOOT_RES_TROPHY_VIEWER, resource_data, 1, 0x34BC0, 0, 0, 0, 1);
    unk14 = new (0) u8[func_10CAA0(0x400) * 4 + 0x400];
    image_blocks[0] = 0;
    image_blocks[1] = 0;
    image_blocks[2] = 0;

    for (s32 i = 0; i < 10; i++)
    {
        images[i] = 0;
    }

    for (s32 i = 0; i < BOOT_TROPHY_COUNT; i++)
    {
        trophy_images[i] = 0;
        textures[i] = 0;
    }

    records = 0;
    slot = 0;
    bar_fading = 0;
    container = 0;
    message_text = 0;
    cursor = 0;
    slot1_text = 0;
    slot2_text = 0;
    grid_clip = 0;
    screen_clip = 0;
    number_label = 0;
    scroll_indicator = 0;
    name_text = 0;
    date_text = 0;
    percentage_text = 0;
    sort_text = 0;
    rank_text = 0;
    progress_bar = 0;
    slot_ready[0] = 0;
    slot_ready[1] = 0;
    row_count = BOOT_TROPHY_GRID_ROWS;
    images_loaded = 0;
    by_time = 0;
    step = BOOT_TROPHY_WAIT_FOR_RESOURCES;
    reveal_index = 0;
    u32 step = 0;

    for (s32 i = 0; i < 2; i++)
    {
        for (s32 j = 0; j < 2; j++)
        {
            for (s32 k = 0; k < 8; k++)
            {
                palettes[0][k + i * 8 + j * 16] = (step * 8) | ((step * 7) << 8) | ((step * 4) << 16) | 0x80000000;
                palettes[1][k + i * 8 + j * 16] = (step * 8) | ((step * 7) << 8) | ((step * 4) << 16) | 0x80000000;
                palettes[2][k + i * 8 + j * 16] = (step * 8) | ((step * 7) << 8) | ((step * 4) << 16) | 0x80000000;
                step++;
            }
        }
    }

    page_delay = 0;
}
