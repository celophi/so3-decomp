#include "include_asm.h"
#include "overlays/boot/text_001FF9E0.h"
#include "overlays/boot/init.h"
#include "main/resident_001001E0.h"

extern "C" {
extern float D_001B6688;
extern float D_001B6690;
float func_141DD0(float angle);
float func_142270(float value);
float sqrtf(float value);
void func_11F390(ResidentPacket* packet, s32 x0, s32 y0, s32 x1, s32 y1, u32 z, u32 color);
void func_11F770(ResidentPacket* packet, void* notification);
float func_4CC3E0(float angle);
float func_4CC5B0(float angle);
void func_001FA620(BootImage* object, void* image, s32 mode);
void func_001F9FC0(BootImage* object, s32 first, s32 second, s32 width, s32 height, u32 color, s32 third);
void func_109F40(void* handle, void* left, void* right, s32 size);
void func_10DB10(BootSound1B65F8* sound, s32 value);
}

/**
 * @brief Clear the byte at offset 0x64 and run the Lib hook.
 * @param value Notification value; unused.
 */
void BootNeedleMeter::func_001E04F0(u32 value)
{
    unk64 = 0;
    func_4D00B0(this);
}

/** @brief Mark the meter active and submit its packet. */
void BootNeedleMeter::func_001DD4C0()
{
    unk64 = 1;
    func_11F770(packet, static_cast<BootClass170D50*>(this));
}

/**
 * @brief Move the needles towards their levels and draw them.
 * @param matrix Matrix supplied by the caller; unused.
 * @param context Opaque caller context; unused.
 */
void BootNeedleMeter::func_001E08C0(const void* matrix, void* context)
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
    float left_x = func_4CC3E0(left_angle);
    float left_y = -func_4CC5B0(left_angle);
    float right_x = func_4CC3E0(right_angle);
    float right_y = -func_4CC5B0(right_angle);
    float peak_x = func_4CC3E0(peak_angle);
    float peak_y = -func_4CC5B0(peak_angle);
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
            BootClass170F30* model = images[4 + i]->unk18;

            if (selection == i)
            {
                BootVector4DDAA0 scale;
                copy_vector(&scale, &model->unk560);

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
        func_001FA620(images[0], (void*)(((u32)image_buffers[0] + 0x7F) & ~0x7F), 0);
        func_001F9FC0(images[0], 0, 1, 488, 223, 0x80808080, 0);
        images[0]->unk18->func_001E0520(-244.0f, -112.0f, 0.0f);
    }

    if (images[1] == 0)
    {
        images[1] = new (0) BootImage;
        func_001FA620(images[1], (void*)(((u32)image_buffers[1] + 0x7F) & ~0x7F), 0);
        func_001F9FC0(images[1], 0, 1, 640, 60, 0x80808080, 0);
        images[1]->unk18->func_001E0520(-320.0f, -216.0f, 0.0f);
    }

    if (images[2] == 0)
    {
        images[2] = new (0) BootImage;
        func_001FA620(images[2], (void*)(((u32)image_buffers[0] + 0x7F) & ~0x7F), 0);
        func_001F9FC0(images[2], 20, 434, 373, 41, 0x80808080, 0);
    }

    if (images[4] == 0)
    {
        images[4] = new (0) BootImage;
        func_001FA620(images[4], (void*)(((u32)image_buffers[0] + 0x7F) & ~0x7F), 0);
        func_001F9FC0(images[4], 17, 241, 105, 32, 0x80808080, 0);
        images[5] = new (0) BootImage;
        func_001FA620(images[5], (void*)(((u32)image_buffers[0] + 0x7F) & ~0x7F), 0);
        func_001F9FC0(images[5], 17, 279, 78, 35, 0x80808080, 0);
        images[6] = new (0) BootImage;
        func_001FA620(images[6], (void*)(((u32)image_buffers[0] + 0x7F) & ~0x7F), 0);
        func_001F9FC0(images[6], 17, 315, 83, 36, 0x80808080, 0);
        images[7] = new (0) BootImage;
        func_001FA620(images[7], (void*)(((u32)image_buffers[0] + 0x7F) & ~0x7F), 0);
        func_001F9FC0(images[7], 17, 351, 274, 34, 0x80808080, 0);
        images[9] = new (0) BootImage;
        func_001FA620(images[9], (void*)(((u32)image_buffers[0] + 0x7F) & ~0x7F), 0);
        func_001F9FC0(images[9], 21, 486, 455, 18, 0x80808080, 0);
    }

    if (images[10] == 0)
    {
        images[10] = new (0) BootImage;
        func_001FA620(images[10], (void*)(((u32)image_buffers[0] + 0x7F) & ~0x7F), 0);
        func_001F9FC0(images[10], 393, 241, 98, 180, 0x80808080, 0);
        images[11] = new (0) BootImage;
        func_001FA620(images[11], (void*)(((u32)image_buffers[0] + 0x7F) & ~0x7F), 0);
        func_001F9FC0(images[11], 393, 241, 98, 180, 0x80808080, 0);
        images[12] = new (0) BootImage;
        func_001FA620(images[12], (void*)(((u32)image_buffers[0] + 0x7F) & ~0x7F), 0);
        func_001F9FC0(images[12], 393, 241, 98, 180, 0x80808080, 0);
        images[13] = new (0) BootImage;
        func_001FA620(images[13], (void*)(((u32)image_buffers[0] + 0x7F) & ~0x7F), 0);
        func_001F9FC0(images[13], 393, 241, 98, 180, 0x80808080, 0);
        images[14] = new (0) BootImage;
        func_001FA620(images[14], (void*)(((u32)image_buffers[0] + 0x7F) & ~0x7F), 0);
        func_001F9FC0(images[14], 393, 241, 98, 180, 0x80808080, 0);
    }

    if (((BootResource0970*)func_101440(func_101290(func_10D8E0()), 1))->widescreen)
    {
        if (images[1] != 0)
        {
            images[1]->unk18->func_001E0520(-422.6667f, -216.0f, 0.0f);
            images[1]->unk18->func_001DDED0(1.31f, 1.0f, 1.0f);
        }

        if (images[2] != 0)
        {
            images[2]->unk18->func_001E0520(3e+01f, -217.0f, 0.0f);
        }

        if (images[3] != 0)
        {
            images[3]->unk18->func_001E0520(-373.33334f, 28.0f, 0.0f);
            images[3]->unk18->func_001DDED0(1.31f, 1.0f, 1.0f);
        }

        if (images[4] != 0)
        {
            images[4]->unk18->func_001E0520(-341.33334f, -1.6e+02f, 0.0f);
        }

        if (images[5] != 0)
        {
            images[5]->unk18->func_001E0520(-341.33334f, -125.0f, 0.0f);
        }

        if (images[6] != 0)
        {
            images[6]->unk18->func_001E0520(-341.33334f, -9e+01f, 0.0f);
        }

        if (images[7] != 0)
        {
            images[7]->unk18->func_001E0520(-341.33334f, -55.0f, 0.0f);
        }

        if (images[9] != 0)
        {
            images[9]->unk18->func_001E0520(-232.0f, -138.0f, 0.0f);
            images[9]->unk18->func_001DDED0(1.31f, 1.0f, 1.0f);
        }

        if (images[10] != 0)
        {
            images[10]->unk18->func_001E0520(-356.6667f, -1.0f, 0.0f);
            images[10]->unk18->func_001DDED0(1.31f, 1.0f, 1.0f);
        }

        if (images[11] != 0)
        {
            images[11]->unk18->func_001E0520(-212.66667f, -1.0f, 0.0f);
            images[11]->unk18->func_001DDED0(1.31f, 1.0f, 1.0f);
        }

        if (images[12] != 0)
        {
            images[12]->unk18->func_001E0520(-68.66667f, -1.0f, 0.0f);
            images[12]->unk18->func_001DDED0(1.31f, 1.0f, 1.0f);
        }

        if (images[13] != 0)
        {
            images[13]->unk18->func_001E0520(78.66667f, -1.0f, 0.0f);
            images[13]->unk18->func_001DDED0(1.31f, 1.0f, 1.0f);
        }

        if (images[14] != 0)
        {
            images[14]->unk18->func_001E0520(222.66667f, -1.0f, 0.0f);
            images[14]->unk18->func_001DDED0(1.31f, 1.0f, 1.0f);
        }
    }
    else
    {
        if (images[1] != 0)
        {
            images[1]->unk18->func_001E0520(-3.2e+02f, -216.0f, 0.0f);
            images[1]->unk18->func_001DDED0(1.0f, 1.0f, 1.0f);
        }

        if (images[2] != 0)
        {
            images[2]->unk18->func_001E0520(-64.0f, -217.0f, 0.0f);
        }

        if (images[3] != 0)
        {
            images[3]->unk18->func_001E0520(-286.0f, 32.0f, 0.0f);
        }

        if (images[4] != 0)
        {
            images[4]->unk18->func_001E0520(-2.6e+02f, -1.6e+02f, 0.0f);
        }

        if (images[5] != 0)
        {
            images[5]->unk18->func_001E0520(-2.6e+02f, -125.0f, 0.0f);
        }

        if (images[6] != 0)
        {
            images[6]->unk18->func_001E0520(-2.6e+02f, -9e+01f, 0.0f);
        }

        if (images[7] != 0)
        {
            images[7]->unk18->func_001E0520(-2.6e+02f, -55.0f, 0.0f);
        }

        if (images[9] != 0)
        {
            images[9]->unk18->func_001E0520(-154.0f, -138.0f, 0.0f);
        }

        if (images[10] != 0)
        {
            images[10]->unk18->func_001E0520(-272.0f, 0.0f, 0.0f);
        }

        if (images[11] != 0)
        {
            images[11]->unk18->func_001E0520(-162.0f, 0.0f, 0.0f);
        }

        if (images[12] != 0)
        {
            images[12]->unk18->func_001E0520(-52.0f, 0.0f, 0.0f);
        }

        if (images[13] != 0)
        {
            images[13]->unk18->func_001E0520(62.0f, 0.0f, 0.0f);
        }

        if (images[14] != 0)
        {
            images[14]->unk18->func_001E0520(172.0f, 0.0f, 0.0f);
        }
    }
}

// Two of the band power loops still colour their FPU registers differently.
INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001FF9E0", update__15BootMusicPlayerFv);

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
        window[i] = func_4CC5B0(3.1415927f * i / 1024.0f);
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
    packet = new (0) BootClass171BF0(0x800);
    levels[0] = 0.0f;
    levels[1] = 0.0f;
    peak = 0.0f;
    peak_hold = 0.0f;
    needles[0] = 0.0f;
    needles[1] = 0.0f;
}
