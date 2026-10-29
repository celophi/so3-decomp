#include "include_asm.h"
#include "overlays/boot/text_001FF9E0.h"
#include "overlays/boot/init.h"
#include "overlays/boot/resident.h"
#include "main/resident_001001E0.h"

extern "C" {
float func_141DD0(float angle);
float func_142270(float value);
float sqrtf(float value);
void func_11F390(ResidentPacket* packet, s32 x0, s32 y0, s32 x1, s32 y1, u32 z, u32 color);
void func_11F770(ResidentPacket* packet, void* notification);
float lib_cosine(float angle);
float lib_sine(float angle);
void func_109F40(void* handle, void* left, void* right, s32 size);
s32 func_109F20(void* handle, s32 channel, s32 count, float* destination);
s32 func_109FB0(void* handle);
s32 func_109FD0(void* handle);
s32 func_112610(void* request, s32 sound);
s32 func_13C4F0(char* buffer, const char* format, ...);
void lib_container_attach_widget(BootContainer* object, BootDrawWidget* child);
void lib_text_set_resource(BootTextWidget* object, s32 slot, u32 key, u8 flag);

/** Sound played for each track. */
extern const s32 g_music_track_sounds[];

/** Text of the track number label before the first update. */
extern const char g_first_track_number[];

/** Format of the track number label. */
extern const char g_track_number_format[];
}

/**
 * @brief Clear the byte at offset 0x64 and run the Lib hook.
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
    func_11F770(packet, static_cast<BootDmaCallbacks*>(this));
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
    func_142270(1073741824.0f);

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
        peak_hold -= D_001B6690;

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
    func_11F390(packet, right_tip_x + 2, right_tip_y + 2, right_tail_x + 2, right_tail_y + 2, 0xFFFFFF, 0x8068261E);
    func_11F390(packet, left_tip_x + 2, left_tip_y + 2, left_tail_x + 2, left_tail_y + 2, 0xFFFFFF, 0x8068261E);
    func_11F390(packet, peak_tip_x + 2, peak_tip_y + 2, peak_tail_x + 2, peak_tail_y + 2, 0xFFFFFF, 0x8068261E);
    func_11F390(packet, right_tip_x, right_tip_y, right_tail_x, right_tail_y, 0xFFFFFF, 0x80A0FFA0);
    func_11F390(packet, left_tip_x, left_tip_y, left_tail_x, left_tail_y, 0xFFFFFF, 0x80FFD0D0);
    func_11F390(packet, peak_tip_x, peak_tip_y, peak_tail_x, peak_tail_y, 0xFFFFFF, 0x801010FF);
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
    float t = func_141DD0(3.1415927f / n);
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
        if (images[4 + i] != 0 && images[4 + i]->unk18 != 0)
        {
            BootModel* model = images[4 + i]->unk18;

            if (selection == i)
            {
                BootVector4DDAA0 scale;
                copy_vector(&scale, &model->base_color_factor);

                if (brightening == 0)
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
                        brightening = 1;
                    }
                }
                else if (brightening != 0)
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
                        brightening = 0;
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
        images[0]->set_texture((const BootTextureResource*)(((u32)image_buffers[0] + 0x7F) & ~0x7F), 0);
        images[0]->set_rectangle(0, 1, 488, 223, 0x80808080, 0);
        images[0]->unk18->set_translation(-244.0f, -112.0f, 0.0f);
    }

    if (images[1] == 0)
    {
        images[1] = new (0) BootImage;
        images[1]->set_texture((const BootTextureResource*)(((u32)image_buffers[1] + 0x7F) & ~0x7F), 0);
        images[1]->set_rectangle(0, 1, 640, 60, 0x80808080, 0);
        images[1]->unk18->set_translation(-320.0f, -216.0f, 0.0f);
    }

    if (images[2] == 0)
    {
        images[2] = new (0) BootImage;
        images[2]->set_texture((const BootTextureResource*)(((u32)image_buffers[0] + 0x7F) & ~0x7F), 0);
        images[2]->set_rectangle(20, 434, 373, 41, 0x80808080, 0);
    }

    if (images[4] == 0)
    {
        images[4] = new (0) BootImage;
        images[4]->set_texture((const BootTextureResource*)(((u32)image_buffers[0] + 0x7F) & ~0x7F), 0);
        images[4]->set_rectangle(17, 241, 105, 32, 0x80808080, 0);
        images[5] = new (0) BootImage;
        images[5]->set_texture((const BootTextureResource*)(((u32)image_buffers[0] + 0x7F) & ~0x7F), 0);
        images[5]->set_rectangle(17, 279, 78, 35, 0x80808080, 0);
        images[6] = new (0) BootImage;
        images[6]->set_texture((const BootTextureResource*)(((u32)image_buffers[0] + 0x7F) & ~0x7F), 0);
        images[6]->set_rectangle(17, 315, 83, 36, 0x80808080, 0);
        images[7] = new (0) BootImage;
        images[7]->set_texture((const BootTextureResource*)(((u32)image_buffers[0] + 0x7F) & ~0x7F), 0);
        images[7]->set_rectangle(17, 351, 274, 34, 0x80808080, 0);
        images[9] = new (0) BootImage;
        images[9]->set_texture((const BootTextureResource*)(((u32)image_buffers[0] + 0x7F) & ~0x7F), 0);
        images[9]->set_rectangle(21, 486, 455, 18, 0x80808080, 0);
    }

    if (images[10] == 0)
    {
        images[10] = new (0) BootImage;
        images[10]->set_texture((const BootTextureResource*)(((u32)image_buffers[0] + 0x7F) & ~0x7F), 0);
        images[10]->set_rectangle(393, 241, 98, 180, 0x80808080, 0);
        images[11] = new (0) BootImage;
        images[11]->set_texture((const BootTextureResource*)(((u32)image_buffers[0] + 0x7F) & ~0x7F), 0);
        images[11]->set_rectangle(393, 241, 98, 180, 0x80808080, 0);
        images[12] = new (0) BootImage;
        images[12]->set_texture((const BootTextureResource*)(((u32)image_buffers[0] + 0x7F) & ~0x7F), 0);
        images[12]->set_rectangle(393, 241, 98, 180, 0x80808080, 0);
        images[13] = new (0) BootImage;
        images[13]->set_texture((const BootTextureResource*)(((u32)image_buffers[0] + 0x7F) & ~0x7F), 0);
        images[13]->set_rectangle(393, 241, 98, 180, 0x80808080, 0);
        images[14] = new (0) BootImage;
        images[14]->set_texture((const BootTextureResource*)(((u32)image_buffers[0] + 0x7F) & ~0x7F), 0);
        images[14]->set_rectangle(393, 241, 98, 180, 0x80808080, 0);
    }

    if (((BootSystemSettings*)func_101440(func_101290(func_10D8E0()), 1))->widescreen)
    {
        if (images[1] != 0)
        {
            images[1]->unk18->set_translation(-422.6667f, -216.0f, 0.0f);
            images[1]->unk18->set_scale(1.31f, 1.0f, 1.0f);
        }

        if (images[2] != 0)
        {
            images[2]->unk18->set_translation(3e+01f, -217.0f, 0.0f);
        }

        if (images[3] != 0)
        {
            images[3]->unk18->set_translation(-373.33334f, 28.0f, 0.0f);
            images[3]->unk18->set_scale(1.31f, 1.0f, 1.0f);
        }

        if (images[4] != 0)
        {
            images[4]->unk18->set_translation(-341.33334f, -1.6e+02f, 0.0f);
        }

        if (images[5] != 0)
        {
            images[5]->unk18->set_translation(-341.33334f, -125.0f, 0.0f);
        }

        if (images[6] != 0)
        {
            images[6]->unk18->set_translation(-341.33334f, -9e+01f, 0.0f);
        }

        if (images[7] != 0)
        {
            images[7]->unk18->set_translation(-341.33334f, -55.0f, 0.0f);
        }

        if (images[9] != 0)
        {
            images[9]->unk18->set_translation(-232.0f, -138.0f, 0.0f);
            images[9]->unk18->set_scale(1.31f, 1.0f, 1.0f);
        }

        if (images[10] != 0)
        {
            images[10]->unk18->set_translation(-356.6667f, -1.0f, 0.0f);
            images[10]->unk18->set_scale(1.31f, 1.0f, 1.0f);
        }

        if (images[11] != 0)
        {
            images[11]->unk18->set_translation(-212.66667f, -1.0f, 0.0f);
            images[11]->unk18->set_scale(1.31f, 1.0f, 1.0f);
        }

        if (images[12] != 0)
        {
            images[12]->unk18->set_translation(-68.66667f, -1.0f, 0.0f);
            images[12]->unk18->set_scale(1.31f, 1.0f, 1.0f);
        }

        if (images[13] != 0)
        {
            images[13]->unk18->set_translation(78.66667f, -1.0f, 0.0f);
            images[13]->unk18->set_scale(1.31f, 1.0f, 1.0f);
        }

        if (images[14] != 0)
        {
            images[14]->unk18->set_translation(222.66667f, -1.0f, 0.0f);
            images[14]->unk18->set_scale(1.31f, 1.0f, 1.0f);
        }
    }
    else
    {
        if (images[1] != 0)
        {
            images[1]->unk18->set_translation(-3.2e+02f, -216.0f, 0.0f);
            images[1]->unk18->set_scale(1.0f, 1.0f, 1.0f);
        }

        if (images[2] != 0)
        {
            images[2]->unk18->set_translation(-64.0f, -217.0f, 0.0f);
        }

        if (images[3] != 0)
        {
            images[3]->unk18->set_translation(-286.0f, 32.0f, 0.0f);
        }

        if (images[4] != 0)
        {
            images[4]->unk18->set_translation(-2.6e+02f, -1.6e+02f, 0.0f);
        }

        if (images[5] != 0)
        {
            images[5]->unk18->set_translation(-2.6e+02f, -125.0f, 0.0f);
        }

        if (images[6] != 0)
        {
            images[6]->unk18->set_translation(-2.6e+02f, -9e+01f, 0.0f);
        }

        if (images[7] != 0)
        {
            images[7]->unk18->set_translation(-2.6e+02f, -55.0f, 0.0f);
        }

        if (images[9] != 0)
        {
            images[9]->unk18->set_translation(-154.0f, -138.0f, 0.0f);
        }

        if (images[10] != 0)
        {
            images[10]->unk18->set_translation(-272.0f, 0.0f, 0.0f);
        }

        if (images[11] != 0)
        {
            images[11]->unk18->set_translation(-162.0f, 0.0f, 0.0f);
        }

        if (images[12] != 0)
        {
            images[12]->unk18->set_translation(-52.0f, 0.0f, 0.0f);
        }

        if (images[13] != 0)
        {
            images[13]->unk18->set_translation(62.0f, 0.0f, 0.0f);
        }

        if (images[14] != 0)
        {
            images[14]->unk18->set_translation(172.0f, 0.0f, 0.0f);
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
    resource = (BootSystemSettings*)func_101440(func_101290(func_10D8E0()), 1);

    switch (step)
    {
    case 0:
        if (func_102D00(D_001B65E8) != 0)
        {
            func_4DF6E0(g_boot_program.display, 0x49, 0x47, 0x9D, 0x7F);
            step++;
            D_001B661C->prepend_node(new (0) BootClass179150, -1);
            container = new (0) BootContainer(9, 0.0f, 0.0f, 0.0f);
            func_465B20(D_001B657C, container);
        }

        break;
    case 1:
        image_buffers[images_loaded] = func_102920(D_001B65EC, resource_data, images_loaded, 1);
        func_1025A0(D_001B65EC, resource_data, (void*)(((u32)image_buffers[images_loaded] + 0x7F) & ~0x7F), images_loaded);

        if (++images_loaded >= 2)
        {
            step++;
            func_121FE0(0);
        }

        break;
    case 2:
        selection = 0;
        track = 0;
        play_mode = 0;
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
            mode_text = new (0) BootTextWidget(g_boot_program.messages, 0x3E8, 1, 270.0f, 186.0f, 512.0f, 224.0f);
        }
        else
        {
            number_text = new (0) BootStringLabel(g_first_track_number, 1, 175.0f, 74.0f, 512.0f, 24.0f);
            name_text = new (0) BootTextWidget(g_boot_program.messages, 0x44C, 1, 210.0f, 74.0f, 512.0f, 24.0f);
            mode_text = new (0) BootTextWidget(g_boot_program.messages, 0x3E8, 1, 330.0f, 186.0f, 512.0f, 224.0f);
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
        func_10DB10(D_001B65F8, 0xFFFF);
        break;
    case 3:
        if (input->repeated == 0x40 && cursor->unk35)
        {
            selection = (selection + 1) % 4;
            cursor->func_00466E40(54.0f, row_y(selection), 0.05f);
            brightening = 0;
        }

        if (input->repeated == 0x10 && cursor->unk35)
        {
            selection = (selection + 3) % 4;
            brightening = 0;
            cursor->func_00466E40(54.0f, row_y(selection), 0.05f);
        }

        if (input->repeated == 0x80 && cursor->unk35)
        {
            switch (selection)
            {
            case 0:
                track = (track + BOOT_MUSIC_TRACK_COUNT - 1) % BOOT_MUSIC_TRACK_COUNT;
                break;
            case 3:
                play_mode = (play_mode + 2) % 3;
                break;
            }
        }

        if (input->repeated == 0x20 && cursor->unk35)
        {
            switch (selection)
            {
            case 0:
                track = (track + 1) % BOOT_MUSIC_TRACK_COUNT;
                break;
            case 3:
                play_mode = (play_mode + 1) % 3;
                break;
            }
        }

        if (input->pressed & resource->confirm_buttons)
        {
            for (s32 i = 0; i < BOOT_MUSIC_TRACK_COUNT; i++)
            {
                shuffle_order[i] = i;
            }

            for (i = 0; i < 500; i++)
            {
                u32 first = func_10CE00() % BOOT_MUSIC_TRACK_COUNT;
                u32 second = func_10CE00() % BOOT_MUSIC_TRACK_COUNT;
                u8 swap = shuffle_order[first];
                u8* other = &shuffle_order[second];
                shuffle_order[first] = *other;
                *other = swap;
            }

            shuffle_position = 0;
            samples_analysed = 0.0f;
            samples_played = 1024.0f;

            switch (selection)
            {
            case 0:
            case 1:
                playing = 1;
                func_109F40(D_001B65F8->stream->handle, stream_buffers[0], stream_buffers[1], 0x200000);

                if (play_mode == 2)
                {
                    track = shuffle_order[shuffle_position++];

                    if (func_112990(D_001B65F8, g_music_track_sounds[track], 1, 0, 0) == 0)
                    {
                        pending_track = g_music_track_sounds[track];
                    }
                }
                else if (func_112990(D_001B65F8, g_music_track_sounds[track], 1, 0, 0) == 0)
                {
                    pending_track = g_music_track_sounds[track];
                }

                next_track_delay = 0.0f;
                break;
            case 2:
                playing = 0;
                func_10F000(D_001B65F8, 0x3C, -1);
                next_track_delay = 0.0f;
                break;
            }
        }

        if (input->pressed & resource->cancel_buttons)
        {
            func_112400(D_001B65F8, 2, 0, 0, 0x7F, 0x40, 0);
            func_10F000(D_001B65F8, 0x1E, -1);
            BootScreenFade* fade = new (0) BootScreenFade(g_boot_program.display);
            fade->unkd0 = 2.0f;
            D_001B661C->append_node(fade, -1);
            step = 4;
            return;
        }

        if (play_mode > 0 && func_112610(D_001B65F8, -1) != 0 && func_109FB0(D_001B65F8->stream->handle) > 0 && playing)
        {
            func_10F000(D_001B65F8, 0x1E0, -1);
            next_track_delay = 8.0f;
            playing = 0;
        }

        if (func_112610(D_001B65F8, -1) == 0 && next_track_delay == 0.0f && play_mode > 0 && playing)
        {
            next_track_delay = 2.0f;
            playing = 0;
        }

        if (next_track_delay > 0.0f)
        {
            next_track_delay -= D_001B6690;

            if (next_track_delay <= 0.0f)
            {
                next_track_delay = 0.0f;

                if (play_mode > 0)
                {
                    samples_analysed = 0.0f;
                    samples_played = 4096.0f;
                    func_109F40(D_001B65F8->stream->handle, stream_buffers[0], stream_buffers[1], 0x200000);
                    playing = 1;

                    switch (play_mode)
                    {
                    case 1:
                        track = (track + 1) % BOOT_MUSIC_TRACK_COUNT;

                        if (func_112990(D_001B65F8, g_music_track_sounds[track], 1, 0, 0) == 0)
                        {
                            pending_track = g_music_track_sounds[track];
                        }

                        break;
                    case 2:
                        track = shuffle_order[shuffle_position];
                        shuffle_position = (shuffle_position + 1) % BOOT_MUSIC_TRACK_COUNT;

                        if (func_112990(D_001B65F8, g_music_track_sounds[track], 1, 0, 0) == 0)
                        {
                            pending_track = g_music_track_sounds[track];
                        }

                        break;
                    }
                }
            }
        }

        func_13C4F0(number, g_track_number_format, track + 1);

        if (number_text != 0)
        {
            number_text->set_text(number);
        }

        lib_text_set_resource(name_text, g_boot_program.messages, g_music_track_sounds[track] + 0x44B, 0);
        lib_text_set_resource(mode_text, g_boot_program.messages, play_mode + 0x3E8, 0);

        if ((func_112610(D_001B65F8, -1) != 0 && (D_001B65F8->unk370 ? 1 : D_001B65F8->unk3bc) > 0) || next_track_delay > 0.0f)
        {
            samples_played += 48000.0f * D_001B6688 / 59.94f;

            if (samples_analysed < samples_played - 1024.0f)
            {
                samples_analysed += 1024.0f;
                func_109F20(D_001B65F8->stream->handle, 0, 1024, spectra[0].real);

                if ((u8)func_109F20(D_001B65F8->stream->handle, 1, 1024, spectra[1].real))
                {
                    for (s32 i = 0; i < 1024; i++)
                    {
                        spectra[0].imag[i] = 0.0f;
                        spectra[1].imag[i] = 0.0f;
                    }

                    if (func_109FD0(D_001B65F8->stream->handle) != 0)
                    {
                        for (s32 i = 0; i < 1024; i++)
                        {
                            float left = spectra[0].real[i];
                            float right = spectra[1].real[i];
                            spectra[0].real[i] = left + right;
                            spectra[1].real[i] = left - right;
                        }
                    }

                    fft->transform(1024, spectra[0].real, spectra[0].imag);
                    fft->transform(1024, spectra[1].real, spectra[1].imag);

                    float sum;

                    sum = 0.0f;

                    for (s32 i = 2; i < 4; i++)
                    {
                        sum += spectra[0].real[i] * spectra[0].real[i] + spectra[0].imag[i] * spectra[0].imag[i];
                    }

                    meters[0]->levels[0] = 10.0f * func_142270(4.0f * sum / 2.0f);
                    sum = 0.0f;

                    {
                        s32 i;

                        // TODO: My guess is one loop over the 17 bins; unrolling it by hand is the only way I found that matches.
                        for (i = 5; i < 14; i += 8)
                        {
                            sum += spectra[0].real[i + 0] * spectra[0].real[i + 0] + spectra[0].imag[i + 0] * spectra[0].imag[i + 0];
                            sum += spectra[0].real[i + 1] * spectra[0].real[i + 1] + spectra[0].imag[i + 1] * spectra[0].imag[i + 1];
                            sum += spectra[0].real[i + 2] * spectra[0].real[i + 2] + spectra[0].imag[i + 2] * spectra[0].imag[i + 2];
                            sum += spectra[0].real[i + 3] * spectra[0].real[i + 3] + spectra[0].imag[i + 3] * spectra[0].imag[i + 3];
                            sum += spectra[0].real[i + 4] * spectra[0].real[i + 4] + spectra[0].imag[i + 4] * spectra[0].imag[i + 4];
                            sum += spectra[0].real[i + 5] * spectra[0].real[i + 5] + spectra[0].imag[i + 5] * spectra[0].imag[i + 5];
                            sum += spectra[0].real[i + 6] * spectra[0].real[i + 6] + spectra[0].imag[i + 6] * spectra[0].imag[i + 6];
                            sum += spectra[0].real[i + 7] * spectra[0].real[i + 7] + spectra[0].imag[i + 7] * spectra[0].imag[i + 7];
                        }

                        float im = spectra[0].imag[i];
                        float re = spectra[0].real[i];
                        sum += re * re + im * im;
                    }

                    meters[1]->levels[0] = 10.0f * func_142270(4.0f * sum / 17.0f);
                    sum = 0.0f;

                    for (s32 i = 22; i < 86; i++)
                    {
                        sum += spectra[0].real[i] * spectra[0].real[i] + spectra[0].imag[i] * spectra[0].imag[i];
                    }

                    meters[2]->levels[0] = 10.0f * func_142270(4.0f * sum / 64.0f);
                    sum = 0.0f;

                    for (s32 i = 86; i < 170; i++)
                    {
                        sum += spectra[0].real[i] * spectra[0].real[i] + spectra[0].imag[i] * spectra[0].imag[i];
                    }

                    meters[3]->levels[0] = 10.0f * func_142270(4.0f * sum / 84.0f);
                    sum = 0.0f;

                    for (s32 i = 170; i < 320; i++)
                    {
                        sum += spectra[0].real[i] * spectra[0].real[i] + spectra[0].imag[i] * spectra[0].imag[i];
                    }

                    meters[4]->levels[0] = 10.0f * func_142270(4.0f * sum / 150.0f);
                    sum = 0.0f;

                    for (s32 i = 2; i < 4; i++)
                    {
                        sum += spectra[1].real[i] * spectra[1].real[i] + spectra[1].imag[i] * spectra[1].imag[i];
                    }

                    meters[0]->levels[1] = 10.0f * func_142270(4.0f * sum / 2.0f);
                    sum = 0.0f;

                    {
                        s32 i;

                        // TODO: My guess is one loop over the 17 bins; unrolling it by hand is the only way I found that matches.
                        for (i = 5; i < 14; i += 8)
                        {
                            sum += spectra[1].real[i + 0] * spectra[1].real[i + 0] + spectra[1].imag[i + 0] * spectra[1].imag[i + 0];
                            sum += spectra[1].real[i + 1] * spectra[1].real[i + 1] + spectra[1].imag[i + 1] * spectra[1].imag[i + 1];
                            sum += spectra[1].real[i + 2] * spectra[1].real[i + 2] + spectra[1].imag[i + 2] * spectra[1].imag[i + 2];
                            sum += spectra[1].real[i + 3] * spectra[1].real[i + 3] + spectra[1].imag[i + 3] * spectra[1].imag[i + 3];
                            sum += spectra[1].real[i + 4] * spectra[1].real[i + 4] + spectra[1].imag[i + 4] * spectra[1].imag[i + 4];
                            sum += spectra[1].real[i + 5] * spectra[1].real[i + 5] + spectra[1].imag[i + 5] * spectra[1].imag[i + 5];
                            sum += spectra[1].real[i + 6] * spectra[1].real[i + 6] + spectra[1].imag[i + 6] * spectra[1].imag[i + 6];
                            sum += spectra[1].real[i + 7] * spectra[1].real[i + 7] + spectra[1].imag[i + 7] * spectra[1].imag[i + 7];
                        }

                        float im = spectra[1].imag[i];
                        float re = spectra[1].real[i];
                        sum += re * re + im * im;
                    }

                    meters[1]->levels[1] = 10.0f * func_142270(4.0f * sum / 17.0f);
                    sum = 0.0f;

                    for (s32 i = 22; i < 86; i++)
                    {
                        sum += spectra[1].real[i] * spectra[1].real[i] + spectra[1].imag[i] * spectra[1].imag[i];
                    }

                    meters[2]->levels[1] = 10.0f * func_142270(4.0f * sum / 64.0f);
                    sum = 0.0f;

                    for (s32 i = 86; i < 170; i++)
                    {
                        sum += spectra[1].real[i] * spectra[1].real[i] + spectra[1].imag[i] * spectra[1].imag[i];
                    }

                    meters[3]->levels[1] = 10.0f * func_142270(4.0f * sum / 84.0f);
                    sum = 0.0f;

                    for (s32 i = 170; i < 320; i++)
                    {
                        sum += spectra[1].real[i] * spectra[1].real[i] + spectra[1].imag[i] * spectra[1].imag[i];
                    }

                    meters[4]->levels[1] = 10.0f * func_142270(4.0f * sum / 150.0f);
                }
            }
        }
        else
        {
            for (s32 i = 0; i < 1024; i++)
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
    case 4:
        func_4DF6E0(g_boot_program.display, 0, 0, 0, 0x7F);
        func_10F000(D_001B65F8, 0x1E, -1);
        release();
        D_001B6614->append_node(new (0) BootTitleMenu(-1), -1);
        lib_object_detach_owner(this);
        destroy();
        return;
    }

    if (pending_track != 0 && func_112990(D_001B65F8, pending_track, 1, 0, 0) != 0)
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
    func_109F40(D_001B65F8->stream->handle, 0, 0, 0);
    func_10DB10(D_001B65F8, 0x7FFF);
}

/** @brief Start loading resource 0x2C, create the meters and build the analysis window. */
BootMusicPlayer::BootMusicPlayer()
{
    resource_data = func_139700(0x40, func_11C8C0(D_001B65E4, 0x2C));
    func_103E70(D_001B65E8, 0x2C, resource_data, 1, 0x34BC0, 0, 0, 0, 1);
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
    step = 0;
    images_loaded = 0;

    for (s32 i = 0; i < 1024; i++)
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

    for (s32 i = 0; i < 1024; i++)
    {
        window[i] = lib_sine(3.1415927f * i / 1024.0f);
        window[i] = window[i] * window[i];
    }
}

/** @brief Report the list kind used when registration requests the default. @return Four. */
s32 BootMusicPlayer::get_default_list_kind()
{
    return 4;
}

#include "overlays/boot/transform_inlines.h"

/** @brief Set up the meter's transform and packet, with every needle at rest. */
BootNeedleMeter::BootNeedleMeter()
{
    func_001DFE40(0x4001);
    unk65 = 1;
    func_001DFE30(0x400);
    packet = new (0) BootPacketBuffer(0x800);
    levels[0] = 0.0f;
    levels[1] = 0.0f;
    peak = 0.0f;
    peak_hold = 0.0f;
    needles[0] = 0.0f;
    needles[1] = 0.0f;
}
