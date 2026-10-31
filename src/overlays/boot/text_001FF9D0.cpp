#include "include_asm.h"
#include "overlays/boot/text_001FF9D0.h"
#include "overlays/boot/init.h"
#include "overlays/boot/resident.h"
#include "main/resident_001001E0.h"
#include "sdk/main/libm_guess_0013F3E0.h"

/** Frame rate used to advance the music visualizer's sample position. */
#define BOOT_MUSIC_FRAME_RATE 59.94f

extern "C" {
float sqrtf(float value);
void resident_packet_add_line(ResidentPacket* packet, s32 x0, s32 y0, s32 x1, s32 y1, u32 z, u32 color);
float lib_cosine(float angle);
float lib_sine(float angle);
void func_109F40(void* handle, void* left, void* right, s32 size);
s32 func_109F20(void* handle, s32 channel, s32 count, float* destination);
s32 func_109FB0(void* handle);
s32 func_109FD0(void* handle);
void lib_container_attach_widget(BootContainer* container, BootDrawWidget* child);
void lib_text_set_resource(BootTextWidget* text, s32 slot, u32 key, u8 flag);

/** Sound played for each track. */
extern const s32 g_music_track_sounds[];

/** Text of the track number label before the first update. */
extern const char g_first_track_number[];

/** Format of the track number label. */
extern const char g_track_number_format[];
}

/** Stages of the music player's loading, playback screen, and exit. */
enum BootMusicPlayerStep
{
    BOOT_MUSIC_WAIT_FOR_RESOURCES = 0,
    BOOT_MUSIC_DECODE_IMAGES = 1,
    BOOT_MUSIC_CREATE_SCREEN = 2,
    BOOT_MUSIC_ACTIVE = 3,
    BOOT_MUSIC_RETURN_TO_TITLE = 4
};

/** Selectable rows of the music player menu. */
enum BootMusicMenuRow
{
    BOOT_MUSIC_ROW_TRACK,
    BOOT_MUSIC_ROW_PLAY,
    BOOT_MUSIC_ROW_STOP,
    BOOT_MUSIC_ROW_MODE,
    BOOT_MUSIC_ROW_COUNT
};

/** @brief Draw in the main list (bucket zero). */
void BootNeedleMeter::set_default_draw_bucket()
{
    draw_bucket = 0;
}

/**
 * @brief Clear dma_pending and run the Lib hook.
 * @param value Notification value; unused.
 */
void BootNeedleMeter::on_packet_complete(u32 value)
{
    dma_pending = 0;
    func_4D00B0(this);
}

/** @brief Mark the meter active and submit its packet. */
void BootNeedleMeter::render()
{
    dma_pending = 1;
    resident_packet_submit(packet, static_cast<BootDmaCallbacks*>(this));
}

/**
 * @brief Move the needles towards their levels and draw them.
 * @param matrix Matrix supplied by the caller; unused.
 * @param context Opaque caller context; unused.
 */
void BootNeedleMeter::build_packet(const void* matrix, void* context)
{
    ResidentPacket* buffer = packet;
    buffer->unk08 = buffer->unk00 + 0x40;
    buffer->unk0c = buffer->unk08;
    log10f_guess(1073741824.0f);

    if (levels[0] > needles[0])
    {
        float step = 0.33f * (levels[0] - needles[0]);

        if (step < 0.25f)
        {
            step = 0.25f;
        }

        needles[0] += step;

        if (needles[0] > levels[0])
        {
            needles[0] = levels[0];
        }

        if (needles[0] > 96.0f)
        {
            needles[0] = 96.0f;
        }
    }
    else if (levels[0] < needles[0])
    {
        float step = 0.2f * (levels[0] - needles[0]);

        if (step > -0.25f)
        {
            step = -0.25f;
        }

        needles[0] += step;

        if (needles[0] < levels[0])
        {
            needles[0] = levels[0];
        }

        if (needles[0] < 0.0f)
        {
            needles[0] = 0.0f;
        }
    }

    if (levels[1] > needles[1])
    {
        float step = 0.33f * (levels[1] - needles[1]);

        if (step < 0.25f)
        {
            step = 0.25f;
        }

        needles[1] += step;

        if (needles[1] > levels[1])
        {
            needles[1] = levels[1];
        }

        if (needles[1] > 96.0f)
        {
            needles[1] = 96.0f;
        }
    }
    else if (levels[1] < needles[1])
    {
        float step = 0.2f * (levels[1] - needles[1]);

        if (step > -0.25f)
        {
            step = -0.25f;
        }

        needles[1] += step;

        if (needles[1] < levels[1])
        {
            needles[1] = levels[1];
        }

        if (needles[1] < 0.0f)
        {
            needles[1] = 0.0f;
        }
    }

    if (peak < levels[0])
    {
        peak = levels[0];
        peak_hold = 2.0f;
    }

    if (peak < levels[1])
    {
        peak = levels[1];
        peak_hold = 2.0f;
    }

    if (peak_hold > 0.0f)
    {
        peak_hold -= g_frame_seconds;

        if (peak_hold < 0.0f)
        {
            peak_hold = 0.0f;
        }
    }

    if (peak_hold == 0.0f)
    {
        peak -= 1.0f;

        if (peak < 0.0f)
        {
            peak = 0.0f;
        }
    }

    float left_angle = 4.5465827f - 0.017453292f * (157.0f * needles[0] / 96.0f);
    float right_angle = 4.5465827f - 0.017453292f * (157.0f * needles[1] / 96.0f);
    float peak_angle = 4.5465827f - 0.017453292f * (157.0f * peak / 96.0f);
    float left_x = lib_cosine(left_angle);
    float left_y = -lib_sine(left_angle);
    float right_x = lib_cosine(right_angle);
    float right_y = -lib_sine(right_angle);
    float peak_x = lib_cosine(peak_angle);
    float peak_y = -lib_sine(peak_angle);
    s32 left_tip_x = x + 75.0f * left_x;
    s32 left_tip_y = y + 75.0f * left_y;
    s32 left_tail_x = x - 10.0f * left_x;
    s32 left_tail_y = y - 10.0f * left_y;
    s32 right_tip_x = x + 75.0f * right_x;
    s32 right_tip_y = y + 75.0f * right_y;
    s32 right_tail_x = x - 10.0f * right_x;
    s32 right_tail_y = y - 10.0f * right_y;
    s32 peak_tip_x = x + 72.0f * peak_x;
    s32 peak_tip_y = y + 72.0f * peak_y;
    s32 peak_tail_x = x - 15.0f * peak_x;
    s32 peak_tail_y = y - 15.0f * peak_y;
    resident_packet_add_line(packet, right_tip_x + 2, right_tip_y + 2, right_tail_x + 2, right_tail_y + 2, 0xFFFFFF, 0x8068261E);
    resident_packet_add_line(packet, left_tip_x + 2, left_tip_y + 2, left_tail_x + 2, left_tail_y + 2, 0xFFFFFF, 0x8068261E);
    resident_packet_add_line(packet, peak_tip_x + 2, peak_tip_y + 2, peak_tail_x + 2, peak_tail_y + 2, 0xFFFFFF, 0x8068261E);
    resident_packet_add_line(packet, right_tip_x, right_tip_y, right_tail_x, right_tail_y, 0xFFFFFF, 0x80A0FFA0);
    resident_packet_add_line(packet, left_tip_x, left_tip_y, left_tail_x, left_tail_y, 0xFFFFFF, 0x80FFD0D0);
    resident_packet_add_line(packet, peak_tip_x, peak_tip_y, peak_tail_x, peak_tail_y, 0xFFFFFF, 0x801010FF);
    unk63 = 1;
}

/** @brief Release the packet and destroy the transform. */
BootNeedleMeter::~BootNeedleMeter()
{
    delete packet;
}

/**
 * @brief Fill the bit-reversal permutation of the sample indices.
 * @param n Transform size.
 * @param table Table of n entries.
 */
inline void BootFft::make_bit_reverse(s32 n, s32* table)
{
    s32 n2 = n / 2;
    s32 i;
    s32 j;
    s32 k;
    i = j = 0;

    for (;;)
    {
        table[i] = j;

        if (++i >= n)
        {
            break;
        }

        k = n2;

        while (k <= j)
        {
            j -= k;
            k /= 2;
        }

        j += k;
    }
}

/**
 * @brief Transform complex samples in place, rebuilding the tables first when the size changes.
 * @param n Number of samples, a power of two; zero releases the tables.
 * @param re Real parts.
 * @param im Imaginary parts.
 */
void BootFft::transform(s32 n, float* re, float* im)
{
    s32 k2;
    s32 n4 = n / 4;

    if (size != n || size == 0)
    {
        size = n;
        delete sine_table;
        delete bit_reverse;
        sine_table = 0;
        bit_reverse = 0;

        if (n == 0)
        {
            return;
        }

        sine_table = new (0) float[(n + n4) * 2];
        bit_reverse = new (0) s32[n * 2];

        if (sine_table == 0 || bit_reverse == 0)
        {
            sine_table = 0;
            bit_reverse = 0;
            return;
        }

        make_sine_table(n, sine_table);

        make_bit_reverse(n, bit_reverse);
    }

    for (s32 i = 0; i < n; i++)
    {
        s32 j = bit_reverse[i];

        if (i < j)
        {
            float t = re[i];
            re[i] = re[j];
            re[j] = t;
            t = im[i];
            im[i] = im[j];
            im[j] = t;
        }
    }

    for (s32 k = 1; k < n; k = k2)
    {
        s32 h = 0;
        k2 = k + k;
        s32 d = n / k2;

        for (s32 j = 0; j < k; j++)
        {
            float c = sine_table[h + n4];
            float s = sine_table[h];

            for (s32 i = j; i < n; i += k2)
            {
                s32 ik = i + k;
                float dx = s * im[ik] + c * re[ik];
                float dy = c * im[ik] - s * re[ik];
                re[ik] = re[i] - dx;
                re[i] += dx;
                im[ik] = im[i] - dy;
                im[i] += dy;
            }

            h += d;
        }
    }

    for (s32 i = 0; i < n; i++)
    {
        re[i] /= n;
        im[i] /= n;
    }
}

/**
 * @brief Fill a sine table covering one and a quarter periods.
 * @param n Transform size.
 * @param table Table of n + n / 4 entries; the cosine of step i is at i + n / 4.
 */
void BootFft::make_sine_table(s32 n, float* table)
{
    s32 n2 = n / 2;
    s32 n4 = n / 4;
    s32 n8 = n / 8;
    float t = sinf_guess(3.1415927f / n);
    float dc = 2.0f * t * t;
    float ds = sqrtf(dc * (2.0f - dc));
    float c;
    float s;
    t = 2.0f * dc;
    c = table[n4] = 1.0f;
    s = table[0] = 0.0f;

    for (s32 i = 1; i < n8; i++)
    {
        c -= dc;
        dc += t * c;
        s += ds;
        ds -= t * s;
        table[i] = s;
        table[n4 - i] = c;
    }

    if (n8 != 0)
    {
        table[n8] = sqrtf(0.5f);
    }

    for (s32 i = 0; i < n4; i++)
    {
        table[n2 - i] = table[i];
    }

    for (s32 i = 0; i < n2 + n4; i++)
    {
        table[i + n2] = -table[i];
    }
}

/** @brief Pulse the selected row's image and reset the others. */
void BootMusicPlayer::update_row_colors()
{
    if (image_buffers[1] == 0)
    {
        return;
    }

    for (s32 i = 0; i < 5; i++)
    {
        if (images[4 + i] != 0 && images[4 + i]->model != 0)
        {
            BootModel* model = images[4 + i]->model;

            if (selection == i)
            {
                BootVector4 scale;
                copy_vector(&scale, &model->base_color_factor);

                if (brightening == 0)
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
                        brightening = 1;
                    }
                }
                else if (brightening != 0)
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
                        brightening = 0;
                    }
                }

                copy_vector(&model->base_color_factor, &scale);
                model->update_combined_color_factor();
            }
            else
            {
                BootVector4 scale;
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

/** @brief Create the screen images once both image buffers are loaded, then place them for the 4:3 or widescreen layout. */
void BootMusicPlayer::create_images()
{
    if (image_buffers[1] == 0)
    {
        return;
    }

    if (images[0] == 0)
    {
        images[0] = new (0) BootImage;
        images[0]->set_texture((const BootTextureResource*)BOOT_ALIGN_RESOURCE(image_buffers[0]), 0);
        images[0]->set_rectangle(0, 1, 488, 223, 0x80808080, 0);
        images[0]->model->set_translation(-244.0f, -112.0f, 0.0f);
    }

    if (images[1] == 0)
    {
        images[1] = new (0) BootImage;
        images[1]->set_texture((const BootTextureResource*)BOOT_ALIGN_RESOURCE(image_buffers[1]), 0);
        images[1]->set_rectangle(0, 1, 640, 60, 0x80808080, 0);
        images[1]->model->set_translation(-320.0f, -216.0f, 0.0f);
    }

    if (images[2] == 0)
    {
        images[2] = new (0) BootImage;
        images[2]->set_texture((const BootTextureResource*)BOOT_ALIGN_RESOURCE(image_buffers[0]), 0);
        images[2]->set_rectangle(20, 434, 373, 41, 0x80808080, 0);
    }

    if (images[4] == 0)
    {
        images[4] = new (0) BootImage;
        images[4]->set_texture((const BootTextureResource*)BOOT_ALIGN_RESOURCE(image_buffers[0]), 0);
        images[4]->set_rectangle(17, 241, 105, 32, 0x80808080, 0);
        images[5] = new (0) BootImage;
        images[5]->set_texture((const BootTextureResource*)BOOT_ALIGN_RESOURCE(image_buffers[0]), 0);
        images[5]->set_rectangle(17, 279, 78, 35, 0x80808080, 0);
        images[6] = new (0) BootImage;
        images[6]->set_texture((const BootTextureResource*)BOOT_ALIGN_RESOURCE(image_buffers[0]), 0);
        images[6]->set_rectangle(17, 315, 83, 36, 0x80808080, 0);
        images[7] = new (0) BootImage;
        images[7]->set_texture((const BootTextureResource*)BOOT_ALIGN_RESOURCE(image_buffers[0]), 0);
        images[7]->set_rectangle(17, 351, 274, 34, 0x80808080, 0);
        images[9] = new (0) BootImage;
        images[9]->set_texture((const BootTextureResource*)BOOT_ALIGN_RESOURCE(image_buffers[0]), 0);
        images[9]->set_rectangle(21, 486, 455, 18, 0x80808080, 0);
    }

    if (images[10] == 0)
    {
        images[10] = new (0) BootImage;
        images[10]->set_texture((const BootTextureResource*)BOOT_ALIGN_RESOURCE(image_buffers[0]), 0);
        images[10]->set_rectangle(393, 241, 98, 180, 0x80808080, 0);
        images[11] = new (0) BootImage;
        images[11]->set_texture((const BootTextureResource*)BOOT_ALIGN_RESOURCE(image_buffers[0]), 0);
        images[11]->set_rectangle(393, 241, 98, 180, 0x80808080, 0);
        images[12] = new (0) BootImage;
        images[12]->set_texture((const BootTextureResource*)BOOT_ALIGN_RESOURCE(image_buffers[0]), 0);
        images[12]->set_rectangle(393, 241, 98, 180, 0x80808080, 0);
        images[13] = new (0) BootImage;
        images[13]->set_texture((const BootTextureResource*)BOOT_ALIGN_RESOURCE(image_buffers[0]), 0);
        images[13]->set_rectangle(393, 241, 98, 180, 0x80808080, 0);
        images[14] = new (0) BootImage;
        images[14]->set_texture((const BootTextureResource*)BOOT_ALIGN_RESOURCE(image_buffers[0]), 0);
        images[14]->set_rectangle(393, 241, 98, 180, 0x80808080, 0);
    }

    if (((BootSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_runtime_owner()), 1))->widescreen)
    {
        if (images[1] != 0)
        {
            images[1]->model->set_translation(-422.6667f, -216.0f, 0.0f);
            images[1]->model->set_scale(1.31f, 1.0f, 1.0f);
        }

        if (images[2] != 0)
        {
            images[2]->model->set_translation(30.0f, -217.0f, 0.0f);
        }

        if (images[3] != 0)
        {
            images[3]->model->set_translation(-373.33334f, 28.0f, 0.0f);
            images[3]->model->set_scale(1.31f, 1.0f, 1.0f);
        }

        if (images[4] != 0)
        {
            images[4]->model->set_translation(-341.33334f, -160.0f, 0.0f);
        }

        if (images[5] != 0)
        {
            images[5]->model->set_translation(-341.33334f, -125.0f, 0.0f);
        }

        if (images[6] != 0)
        {
            images[6]->model->set_translation(-341.33334f, -90.0f, 0.0f);
        }

        if (images[7] != 0)
        {
            images[7]->model->set_translation(-341.33334f, -55.0f, 0.0f);
        }

        if (images[9] != 0)
        {
            images[9]->model->set_translation(-232.0f, -138.0f, 0.0f);
            images[9]->model->set_scale(1.31f, 1.0f, 1.0f);
        }

        if (images[10] != 0)
        {
            images[10]->model->set_translation(-356.6667f, -1.0f, 0.0f);
            images[10]->model->set_scale(1.31f, 1.0f, 1.0f);
        }

        if (images[11] != 0)
        {
            images[11]->model->set_translation(-212.66667f, -1.0f, 0.0f);
            images[11]->model->set_scale(1.31f, 1.0f, 1.0f);
        }

        if (images[12] != 0)
        {
            images[12]->model->set_translation(-68.66667f, -1.0f, 0.0f);
            images[12]->model->set_scale(1.31f, 1.0f, 1.0f);
        }

        if (images[13] != 0)
        {
            images[13]->model->set_translation(78.66667f, -1.0f, 0.0f);
            images[13]->model->set_scale(1.31f, 1.0f, 1.0f);
        }

        if (images[14] != 0)
        {
            images[14]->model->set_translation(222.66667f, -1.0f, 0.0f);
            images[14]->model->set_scale(1.31f, 1.0f, 1.0f);
        }
    }
    else
    {
        if (images[1] != 0)
        {
            images[1]->model->set_translation(-320.0f, -216.0f, 0.0f);
            images[1]->model->set_scale(1.0f, 1.0f, 1.0f);
        }

        if (images[2] != 0)
        {
            images[2]->model->set_translation(-64.0f, -217.0f, 0.0f);
        }

        if (images[3] != 0)
        {
            images[3]->model->set_translation(-286.0f, 32.0f, 0.0f);
        }

        if (images[4] != 0)
        {
            images[4]->model->set_translation(-260.0f, -160.0f, 0.0f);
        }

        if (images[5] != 0)
        {
            images[5]->model->set_translation(-260.0f, -125.0f, 0.0f);
        }

        if (images[6] != 0)
        {
            images[6]->model->set_translation(-260.0f, -90.0f, 0.0f);
        }

        if (images[7] != 0)
        {
            images[7]->model->set_translation(-260.0f, -55.0f, 0.0f);
        }

        if (images[9] != 0)
        {
            images[9]->model->set_translation(-154.0f, -138.0f, 0.0f);
        }

        if (images[10] != 0)
        {
            images[10]->model->set_translation(-272.0f, 0.0f, 0.0f);
        }

        if (images[11] != 0)
        {
            images[11]->model->set_translation(-162.0f, 0.0f, 0.0f);
        }

        if (images[12] != 0)
        {
            images[12]->model->set_translation(-52.0f, 0.0f, 0.0f);
        }

        if (images[13] != 0)
        {
            images[13]->model->set_translation(62.0f, 0.0f, 0.0f);
        }

        if (images[14] != 0)
        {
            images[14]->model->set_translation(172.0f, 0.0f, 0.0f);
        }
    }
}

// Two of the band power loops still colour their FPU registers differently.
/**
 * @brief Return the cursor height for a menu row.
 * @param row Menu row.
 * @return Cursor y coordinate.
 */
static inline float row_y(u32 row)
{
    return 86.0f + 36.0f * row;
}

/** @brief Run the player. */
void BootMusicPlayer::update()
{
    BootSystemSettings* resource;
    s32 i;
    BootInput* input = g_boot_program.input;
    resource = (BootSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_runtime_owner()), 1);

    switch (step)
    {
    case BOOT_MUSIC_WAIT_FOR_RESOURCES:
        if (func_102D00(g_resource_queue) != 0)
        {
            func_4DF6E0(g_boot_program.display, 0x49, 0x47, 0x9D, 0x7F);
            step++;
            D_001B661C->prepend_node(new (0) BootClass179150, -1);
            container = new (0) BootContainer(9, 0.0f, 0.0f, 0.0f);
            func_465B20(D_001B657C, container);
        }

        break;
    case BOOT_MUSIC_DECODE_IMAGES:
        image_buffers[images_loaded] = func_102920(g_resident_resource_decoder, resource_data, images_loaded, 1);
        func_1025A0(g_resident_resource_decoder, resource_data, (void*)BOOT_ALIGN_RESOURCE(image_buffers[images_loaded]), images_loaded);

        if (++images_loaded >= 2)
        {
            step++;
            FlushCache(0);
        }

        break;
    case BOOT_MUSIC_CREATE_SCREEN:
        selection = BOOT_MUSIC_ROW_TRACK;
        track = 0;
        play_mode = BOOT_MUSIC_PLAY_SINGLE;
        unk78 = 0;

        {
            float y = row_y(selection);
            cursor = new (0) BootSelectionCursor;
            func_467570(cursor, 1, 0, 0, 54.0f, y, 0.0f);
        }
        func_465B20(D_001B657C, cursor);
        D_001B661C->append_node(meters[0], -1);
        D_001B661C->append_node(meters[1], -1);
        D_001B661C->append_node(meters[2], -1);
        D_001B661C->append_node(meters[3], -1);
        D_001B661C->append_node(meters[4], -1);
        step++;

        if (resource->widescreen)
        {
            number_text = new (0) BootStringLabel(g_first_track_number, 1, 150.0f, 71.0f, 512.0f, 24.0f);
            name_text = new (0) BootTextWidget(g_boot_program.messages, 0x44C, 1, 185.0f, 71.0f, 512.0f, 24.0f);
            mode_text = new (0) BootTextWidget(g_boot_program.messages, BOOT_MUSIC_PLAY_MODE_MESSAGE_BASE, 1, 270.0f, 186.0f, 512.0f, 224.0f);
        }
        else
        {
            number_text = new (0) BootStringLabel(g_first_track_number, 1, 175.0f, 74.0f, 512.0f, 24.0f);
            name_text = new (0) BootTextWidget(g_boot_program.messages, 0x44C, 1, 210.0f, 74.0f, 512.0f, 24.0f);
            mode_text = new (0) BootTextWidget(g_boot_program.messages, BOOT_MUSIC_PLAY_MODE_MESSAGE_BASE, 1, 330.0f, 186.0f, 512.0f, 224.0f);
        }

        labels[0] = new (0) BootTextWidget(g_boot_program.messages, 0x96, 1, 50.0f, 435.0f, 128.0f, 24.0f);
        labels[1] = new (0) BootTextWidget(g_boot_program.messages, 0x97, 1, 160.0f, 435.0f, 128.0f, 24.0f);
        labels[2] = new (0) BootTextWidget(g_boot_program.messages, 0x98, 1, 270.0f, 435.0f, 128.0f, 24.0f);
        labels[3] = new (0) BootTextWidget(g_boot_program.messages, 0x99, 1, 380.0f, 435.0f, 128.0f, 24.0f);
        labels[4] = new (0) BootTextWidget(g_boot_program.messages, 0x9A, 1, 490.0f, 435.0f, 128.0f, 24.0f);
        name_text->set_vertical_align(2);
        number_text->set_color(0x34130F);
        name_text->set_color(0x34130F);
        mode_text->set_color(0x34130F);
        lib_container_attach_widget(container, number_text);
        lib_container_attach_widget(container, name_text);
        lib_container_attach_widget(container, mode_text);

        for (s32 i = 0; i < 5; i++)
        {
            labels[i]->set_color(0x34130F);
            lib_container_attach_widget(container, labels[i]);
        }

        next_track_delay = 0.0f;
        resident_sound_set_volume_scale(g_sound, 0xFFFF);
        break;
    case BOOT_MUSIC_ACTIVE:
        if (input->repeated == BOOT_BUTTON_DOWN && cursor->unk35)
        {
            selection = (selection + 1) % BOOT_MUSIC_ROW_COUNT;
            cursor->func_00466E40(54.0f, row_y(selection), 0.05f);
            brightening = 0;
        }

        if (input->repeated == BOOT_BUTTON_UP && cursor->unk35)
        {
            selection = (selection + BOOT_MUSIC_ROW_COUNT - 1) % BOOT_MUSIC_ROW_COUNT;
            brightening = 0;
            cursor->func_00466E40(54.0f, row_y(selection), 0.05f);
        }

        if (input->repeated == BOOT_BUTTON_LEFT && cursor->unk35)
        {
            switch (selection)
            {
            case BOOT_MUSIC_ROW_TRACK:
                track = (track + BOOT_MUSIC_TRACK_COUNT - 1) % BOOT_MUSIC_TRACK_COUNT;
                break;
            case BOOT_MUSIC_ROW_MODE:
                play_mode = (play_mode + BOOT_MUSIC_PLAY_MODE_COUNT - 1) % BOOT_MUSIC_PLAY_MODE_COUNT;
                break;
            }
        }

        if (input->repeated == BOOT_BUTTON_RIGHT && cursor->unk35)
        {
            switch (selection)
            {
            case BOOT_MUSIC_ROW_TRACK:
                track = (track + 1) % BOOT_MUSIC_TRACK_COUNT;
                break;
            case BOOT_MUSIC_ROW_MODE:
                play_mode = (play_mode + 1) % BOOT_MUSIC_PLAY_MODE_COUNT;
                break;
            }
        }

        if (input->pressed & resource->confirm_buttons)
        {
            for (s32 i = 0; i < BOOT_MUSIC_TRACK_COUNT; i++)
            {
                shuffle_order[i] = i;
            }

            for (i = 0; i < BOOT_MUSIC_SHUFFLE_SWAPS; i++)
            {
                u32 first = resident_rand() % BOOT_MUSIC_TRACK_COUNT;
                u32 second = resident_rand() % BOOT_MUSIC_TRACK_COUNT;
                u8 swap = shuffle_order[first];
                u8* other = &shuffle_order[second];
                shuffle_order[first] = *other;
                *other = swap;
            }

            shuffle_position = 0;
            samples_analysed = 0.0f;
            samples_played = (float)BOOT_MUSIC_FFT_SIZE;

            switch (selection)
            {
            case BOOT_MUSIC_ROW_TRACK:
            case BOOT_MUSIC_ROW_PLAY:
                playing = 1;
                func_109F40(g_sound->stream->handle, stream_buffers[0], stream_buffers[1], BOOT_MUSIC_STREAM_BUFFER_SIZE);

                if (play_mode == BOOT_MUSIC_PLAY_SHUFFLED)
                {
                    track = shuffle_order[shuffle_position++];

                    if (resident_sound_play_music(g_sound, g_music_track_sounds[track], 1, 0, 0) == 0)
                    {
                        pending_track = g_music_track_sounds[track];
                    }
                }
                else if (resident_sound_play_music(g_sound, g_music_track_sounds[track], 1, 0, 0) == 0)
                {
                    pending_track = g_music_track_sounds[track];
                }

                next_track_delay = 0.0f;
                break;
            case BOOT_MUSIC_ROW_STOP:
                playing = 0;
                resident_sound_stop_music(g_sound, 0x3C, -1);
                next_track_delay = 0.0f;
                break;
            }
        }

        if (input->pressed & resource->cancel_buttons)
        {
            resident_sound_play(g_sound, 2, 0, 0, 0x7F, 0x40, 0);
            resident_sound_stop_music(g_sound, 0x1E, -1);
            BootScreenFade* fade = new (0) BootScreenFade(g_boot_program.display);
            fade->fade_speed = 2.0f;
            D_001B661C->append_node(fade, -1);
            step = BOOT_MUSIC_RETURN_TO_TITLE;
            return;
        }

        if (play_mode > BOOT_MUSIC_PLAY_SINGLE && resident_sound_is_music_playing(g_sound, -1) != 0 && func_109FB0(g_sound->stream->handle) > 0 && playing)
        {
            resident_sound_stop_music(g_sound, 0x1E0, -1);
            next_track_delay = 8.0f;
            playing = 0;
        }

        if (resident_sound_is_music_playing(g_sound, -1) == 0 && next_track_delay == 0.0f && play_mode > BOOT_MUSIC_PLAY_SINGLE && playing)
        {
            next_track_delay = 2.0f;
            playing = 0;
        }

        if (next_track_delay > 0.0f)
        {
            next_track_delay -= g_frame_seconds;

            if (next_track_delay <= 0.0f)
            {
                next_track_delay = 0.0f;

                if (play_mode > BOOT_MUSIC_PLAY_SINGLE)
                {
                    samples_analysed = 0.0f;
                    samples_played = (float)BOOT_MUSIC_NEXT_TRACK_LEAD_SAMPLES;
                    func_109F40(g_sound->stream->handle, stream_buffers[0], stream_buffers[1], BOOT_MUSIC_STREAM_BUFFER_SIZE);
                    playing = 1;

                    switch (play_mode)
                    {
                    case BOOT_MUSIC_PLAY_IN_ORDER:
                        track = (track + 1) % BOOT_MUSIC_TRACK_COUNT;

                        if (resident_sound_play_music(g_sound, g_music_track_sounds[track], 1, 0, 0) == 0)
                        {
                            pending_track = g_music_track_sounds[track];
                        }

                        break;
                    case BOOT_MUSIC_PLAY_SHUFFLED:
                        track = shuffle_order[shuffle_position];
                        shuffle_position = (shuffle_position + 1) % BOOT_MUSIC_TRACK_COUNT;

                        if (resident_sound_play_music(g_sound, g_music_track_sounds[track], 1, 0, 0) == 0)
                        {
                            pending_track = g_music_track_sounds[track];
                        }

                        break;
                    }
                }
            }
        }

        sprintf_guess(number, g_track_number_format, track + 1);

        if (number_text != 0)
        {
            number_text->set_text(number);
        }

        lib_text_set_resource(name_text, g_boot_program.messages, g_music_track_sounds[track] + BOOT_MUSIC_TRACK_NAME_MESSAGE_OFFSET, 0);
        lib_text_set_resource(mode_text, g_boot_program.messages, play_mode + BOOT_MUSIC_PLAY_MODE_MESSAGE_BASE, 0);

        if ((resident_sound_is_music_playing(g_sound, -1) != 0 && (g_sound->disabled ? 1 : g_sound->unk3bc) > 0) || next_track_delay > 0.0f)
        {
            samples_played += (float)BOOT_MUSIC_SAMPLE_RATE * g_frame_ticks / BOOT_MUSIC_FRAME_RATE;

            if (samples_analysed < samples_played - (float)BOOT_MUSIC_FFT_SIZE)
            {
                samples_analysed += (float)BOOT_MUSIC_FFT_SIZE;
                func_109F20(g_sound->stream->handle, 0, BOOT_MUSIC_FFT_SIZE, spectra[0].real);

                if ((u8)func_109F20(g_sound->stream->handle, 1, BOOT_MUSIC_FFT_SIZE, spectra[1].real))
                {
                    for (s32 i = 0; i < BOOT_MUSIC_FFT_SIZE; i++)
                    {
                        spectra[0].imag[i] = 0.0f;
                        spectra[1].imag[i] = 0.0f;
                    }

                    if (func_109FD0(g_sound->stream->handle) != 0)
                    {
                        for (s32 i = 0; i < BOOT_MUSIC_FFT_SIZE; i++)
                        {
                            float left = spectra[0].real[i];
                            float right = spectra[1].real[i];
                            spectra[0].real[i] = left + right;
                            spectra[1].real[i] = left - right;
                        }
                    }

                    fft->transform(BOOT_MUSIC_FFT_SIZE, spectra[0].real, spectra[0].imag);
                    fft->transform(BOOT_MUSIC_FFT_SIZE, spectra[1].real, spectra[1].imag);

                    // Five meter bands use bins 2-3, 5-21, 22-85, 86-169 and 170-319; bin 4 is skipped.
                    float band_power;

                    band_power = 0.0f;

                    for (s32 i = 2; i < 4; i++)
                    {
                        band_power += spectra[0].real[i] * spectra[0].real[i] + spectra[0].imag[i] * spectra[0].imag[i];
                    }

                    meters[0]->levels[0] = 10.0f * log10f_guess(4.0f * band_power / 2.0f);
                    band_power = 0.0f;

                    {
                        s32 i;

                        // Preserve the floating-point accumulation order across these 17 bins.
                        for (i = 5; i < 14; i += 8)
                        {
                            band_power += spectra[0].real[i + 0] * spectra[0].real[i + 0] + spectra[0].imag[i + 0] * spectra[0].imag[i + 0];
                            band_power += spectra[0].real[i + 1] * spectra[0].real[i + 1] + spectra[0].imag[i + 1] * spectra[0].imag[i + 1];
                            band_power += spectra[0].real[i + 2] * spectra[0].real[i + 2] + spectra[0].imag[i + 2] * spectra[0].imag[i + 2];
                            band_power += spectra[0].real[i + 3] * spectra[0].real[i + 3] + spectra[0].imag[i + 3] * spectra[0].imag[i + 3];
                            band_power += spectra[0].real[i + 4] * spectra[0].real[i + 4] + spectra[0].imag[i + 4] * spectra[0].imag[i + 4];
                            band_power += spectra[0].real[i + 5] * spectra[0].real[i + 5] + spectra[0].imag[i + 5] * spectra[0].imag[i + 5];
                            band_power += spectra[0].real[i + 6] * spectra[0].real[i + 6] + spectra[0].imag[i + 6] * spectra[0].imag[i + 6];
                            band_power += spectra[0].real[i + 7] * spectra[0].real[i + 7] + spectra[0].imag[i + 7] * spectra[0].imag[i + 7];
                        }

                        float im = spectra[0].imag[i];
                        float re = spectra[0].real[i];
                        band_power += re * re + im * im;
                    }

                    meters[1]->levels[0] = 10.0f * log10f_guess(4.0f * band_power / 17.0f);
                    band_power = 0.0f;

                    for (s32 i = 22; i < 86; i++)
                    {
                        band_power += spectra[0].real[i] * spectra[0].real[i] + spectra[0].imag[i] * spectra[0].imag[i];
                    }

                    meters[2]->levels[0] = 10.0f * log10f_guess(4.0f * band_power / 64.0f);
                    band_power = 0.0f;

                    for (s32 i = 86; i < 170; i++)
                    {
                        band_power += spectra[0].real[i] * spectra[0].real[i] + spectra[0].imag[i] * spectra[0].imag[i];
                    }

                    meters[3]->levels[0] = 10.0f * log10f_guess(4.0f * band_power / 84.0f);
                    band_power = 0.0f;

                    for (s32 i = 170; i < 320; i++)
                    {
                        band_power += spectra[0].real[i] * spectra[0].real[i] + spectra[0].imag[i] * spectra[0].imag[i];
                    }

                    meters[4]->levels[0] = 10.0f * log10f_guess(4.0f * band_power / 150.0f);
                    band_power = 0.0f;

                    for (s32 i = 2; i < 4; i++)
                    {
                        band_power += spectra[1].real[i] * spectra[1].real[i] + spectra[1].imag[i] * spectra[1].imag[i];
                    }

                    meters[0]->levels[1] = 10.0f * log10f_guess(4.0f * band_power / 2.0f);
                    band_power = 0.0f;

                    {
                        s32 i;

                        // Preserve the floating-point accumulation order across these 17 bins.
                        for (i = 5; i < 14; i += 8)
                        {
                            band_power += spectra[1].real[i + 0] * spectra[1].real[i + 0] + spectra[1].imag[i + 0] * spectra[1].imag[i + 0];
                            band_power += spectra[1].real[i + 1] * spectra[1].real[i + 1] + spectra[1].imag[i + 1] * spectra[1].imag[i + 1];
                            band_power += spectra[1].real[i + 2] * spectra[1].real[i + 2] + spectra[1].imag[i + 2] * spectra[1].imag[i + 2];
                            band_power += spectra[1].real[i + 3] * spectra[1].real[i + 3] + spectra[1].imag[i + 3] * spectra[1].imag[i + 3];
                            band_power += spectra[1].real[i + 4] * spectra[1].real[i + 4] + spectra[1].imag[i + 4] * spectra[1].imag[i + 4];
                            band_power += spectra[1].real[i + 5] * spectra[1].real[i + 5] + spectra[1].imag[i + 5] * spectra[1].imag[i + 5];
                            band_power += spectra[1].real[i + 6] * spectra[1].real[i + 6] + spectra[1].imag[i + 6] * spectra[1].imag[i + 6];
                            band_power += spectra[1].real[i + 7] * spectra[1].real[i + 7] + spectra[1].imag[i + 7] * spectra[1].imag[i + 7];
                        }

                        float im = spectra[1].imag[i];
                        float re = spectra[1].real[i];
                        band_power += re * re + im * im;
                    }

                    meters[1]->levels[1] = 10.0f * log10f_guess(4.0f * band_power / 17.0f);
                    band_power = 0.0f;

                    for (s32 i = 22; i < 86; i++)
                    {
                        band_power += spectra[1].real[i] * spectra[1].real[i] + spectra[1].imag[i] * spectra[1].imag[i];
                    }

                    meters[2]->levels[1] = 10.0f * log10f_guess(4.0f * band_power / 64.0f);
                    band_power = 0.0f;

                    for (s32 i = 86; i < 170; i++)
                    {
                        band_power += spectra[1].real[i] * spectra[1].real[i] + spectra[1].imag[i] * spectra[1].imag[i];
                    }

                    meters[3]->levels[1] = 10.0f * log10f_guess(4.0f * band_power / 84.0f);
                    band_power = 0.0f;

                    for (s32 i = 170; i < 320; i++)
                    {
                        band_power += spectra[1].real[i] * spectra[1].real[i] + spectra[1].imag[i] * spectra[1].imag[i];
                    }

                    meters[4]->levels[1] = 10.0f * log10f_guess(4.0f * band_power / 150.0f);
                }
            }
        }
        else
        {
            for (s32 i = 0; i < BOOT_MUSIC_FFT_SIZE; i++)
            {
                spectra[0].real[i] = 0.0f;
                spectra[1].real[i] = 0.0f;
            }

            meters[0]->levels[0] = 0.0f;
            meters[1]->levels[0] = 0.0f;
            meters[2]->levels[0] = 0.0f;
            meters[3]->levels[0] = 0.0f;
            meters[4]->levels[0] = 0.0f;
            meters[0]->levels[1] = 0.0f;
            meters[1]->levels[1] = 0.0f;
            meters[2]->levels[1] = 0.0f;
            meters[3]->levels[1] = 0.0f;
            meters[4]->levels[1] = 0.0f;
        }

        break;
    case BOOT_MUSIC_RETURN_TO_TITLE:
        func_4DF6E0(g_boot_program.display, 0, 0, 0, 0x7F);
        resident_sound_stop_music(g_sound, 0x1E, -1);
        release();
        D_001B6614->append_node(new (0) BootTitleMenu(BOOT_TITLE_ITEM_AUTO), -1);
        lib_object_detach_owner(this);
        destroy();
        return;
    }

    if (pending_track != 0 && resident_sound_play_music(g_sound, pending_track, 1, 0, 0) != 0)
    {
        pending_track = 0;
    }

    create_images();
    update_row_colors();
}

/** @brief Destroy every owned object and release the resource. */
void BootMusicPlayer::release()
{
    delete resource_data;
    resource_data = 0;

    for (s32 i = 0; i < 20; i++)
    {
        if (images[i] != 0)
        {
            lib_object_detach_owner(images[i]);
            images[i]->destroy();
            images[i] = 0;
        }
    }

    if (meters[0] != 0)
    {
        lib_object_detach_owner(meters[0]);
        meters[0]->destroy();
        meters[0] = 0;
    }

    if (meters[1] != 0)
    {
        lib_object_detach_owner(meters[1]);
        meters[1]->destroy();
        meters[1] = 0;
    }

    if (meters[2] != 0)
    {
        lib_object_detach_owner(meters[2]);
        meters[2]->destroy();
        meters[2] = 0;
    }

    if (meters[3] != 0)
    {
        lib_object_detach_owner(meters[3]);
        meters[3]->destroy();
        meters[3] = 0;
    }

    if (meters[4] != 0)
    {
        lib_object_detach_owner(meters[4]);
        meters[4]->destroy();
        meters[4] = 0;
    }

    for (s32 i = 0; i < 5; i++)
    {
        if (labels[i] != 0)
        {
            labels[i]->destroy();
            labels[i] = 0;
        }
    }

    if (container != 0)
    {
        container->destroy();
        container = 0;
    }

    if (unk4050f4 != 0)
    {
        unk4050f4->destroy();
        unk4050f4 = 0;
    }

    if (cursor != 0)
    {
        cursor->destroy();
        cursor = 0;
    }

    if (number_text != 0)
    {
        number_text->destroy();
        number_text = 0;
    }

    if (name_text != 0)
    {
        name_text->destroy();
        name_text = 0;
    }

    if (mode_text != 0)
    {
        mode_text->destroy();
        mode_text = 0;
    }
}

/** @brief Release the loaded data, the owned objects and the transform, then stop the stream. */
BootMusicPlayer::~BootMusicPlayer()
{
    delete resource_data;
    resource_data = 0;

    for (s32 i = 0; i < 2; i++)
    {
        delete image_buffers[i];
    }

    for (s32 i = 0; i < 20; i++)
    {
        if (images[i] != 0)
        {
            lib_object_detach_owner(images[i]);
            images[i]->destroy();
            images[i] = 0;
        }
    }

    if (unk4050f4 != 0)
    {
        unk4050f4->destroy();
    }

    if (cursor != 0)
    {
        cursor->destroy();
    }

    for (s32 i = 0; i < 5; i++)
    {
        if (labels[i] != 0)
        {
            labels[i]->destroy();
        }
    }

    if (meters[0] != 0)
    {
        lib_object_detach_owner(meters[0]);
        meters[0]->destroy();
    }

    if (meters[1] != 0)
    {
        lib_object_detach_owner(meters[1]);
        meters[1]->destroy();
    }

    if (meters[2] != 0)
    {
        lib_object_detach_owner(meters[2]);
        meters[2]->destroy();
    }

    if (meters[3] != 0)
    {
        lib_object_detach_owner(meters[3]);
        meters[3]->destroy();
    }

    if (meters[4] != 0)
    {
        lib_object_detach_owner(meters[4]);
        meters[4]->destroy();
    }

    if (number_text != 0)
    {
        number_text->destroy();
    }

    if (name_text != 0)
    {
        name_text->destroy();
    }

    if (mode_text != 0)
    {
        mode_text->destroy();
    }

    if (container != 0)
    {
        container->destroy();
    }

    delete fft;
    func_109F40(g_sound->stream->handle, 0, 0, 0);
    resident_sound_set_volume_scale(g_sound, 0x7FFF);
}

/** @brief Start loading resource 0x2C, create the meters and build the analysis window. */
BootMusicPlayer::BootMusicPlayer()
{
    resource_data = (u8*)memalign(0x40, resident_get_resource_size(g_resource_archive, BOOT_RES_MUSIC_PLAYER));
    resident_queue_resource_request(g_resource_queue, BOOT_RES_MUSIC_PLAYER, resource_data,
                                    BOOT_RESOURCE_TAG, BOOT_RESOURCE_PRIORITY, 0, 0, 0, BOOT_RESOURCE_READ);
    playing = 0;
    image_buffers[0] = 0;
    image_buffers[1] = 0;

    for (s32 i = 0; i < 20; i++)
    {
        images[i] = 0;
    }

    labels[0] = 0;
    labels[1] = 0;
    labels[2] = 0;
    labels[3] = 0;
    labels[4] = 0;
    container = 0;
    unk4050f4 = 0;
    cursor = 0;
    brightening = 0;
    pending_track = 0;
    number_text = 0;
    name_text = 0;
    mode_text = 0;
    fft = new (0) BootFft;
    step = BOOT_MUSIC_WAIT_FOR_RESOURCES;
    images_loaded = 0;

    for (s32 i = 0; i < BOOT_MUSIC_FFT_SIZE; i++)
    {
        spectra[0].real[i] = 0.0f;
        spectra[1].real[i] = 0.0f;
    }

    meters[0] = new (0) BootNeedleMeter;
    meters[1] = new (0) BootNeedleMeter;
    meters[2] = new (0) BootNeedleMeter;
    meters[3] = new (0) BootNeedleMeter;
    meters[4] = new (0) BootNeedleMeter;

    meters[0]->set_position(144, 314);
    meters[1]->set_position(254, 314);
    meters[2]->set_position(364, 314);
    meters[3]->set_position(476, 314);
    meters[4]->set_position(586, 314);

    for (s32 i = 0; i < BOOT_MUSIC_FFT_SIZE; i++)
    {
        window[i] = lib_sine(3.1415927f * i / (float)BOOT_MUSIC_FFT_SIZE);
        window[i] = window[i] * window[i];
    }
}

/**
 * @brief Report the list kind used when registration requests the default.
 * @return Four.
 */
s32 BootMusicPlayer::get_default_list_kind()
{
    return 4;
}

#include "overlays/boot/transform_inlines.h"

/** @brief Set up the meter's transform and packet, with every needle at rest. */
BootNeedleMeter::BootNeedleMeter()
{
    set_type_id(0x4001);
    unk65 = 1;
    set_draw_flags(BOOT_DRAW_FLAG_0400);
    packet = new (0) BootPacketBuffer(0x800);
    levels[0] = 0.0f;
    levels[1] = 0.0f;
    peak = 0.0f;
    peak_hold = 0.0f;
    needles[0] = 0.0f;
    needles[1] = 0.0f;
}
