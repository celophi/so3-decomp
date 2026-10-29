#include "include_asm.h"
#include "overlays/boot/text_001FF0A0.h"
#include "overlays/boot/text_001FF9E0.h"
#include "overlays/boot/resident.h"
#include "main/resident_001001E0.h"

extern "C" {
}

/** @brief Destroy every owned object and release the per-trophy allocations. */
void BootBattleTrophyViewer::release()
{
    for (s32 i = 0; i < 10; i++)
    {
        if (unk28[i] != 0)
        {
            lib_object_detach_owner(unk28[i]);
            unk28[i]->destroy();
            unk28[i] = 0;
        }
    }

    if (unk88 != 0)
    {
        unk88->destroy();
        unk88 = 0;
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

    if (unkA8 != 0)
    {
        unkA8->destroy();
        unkA8 = 0;
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

    for (s32 i = 0; i < 300; i++)
    {
        if (trophy_images[i] != 0)
        {
            lib_object_detach_owner(trophy_images[i]);
            trophy_images[i]->destroy();
            trophy_images[i] = 0;
        }

        if (textures[i] != 0)
        {
            func_11EE00(D_001B65F4, textures[i]);
            textures[i] = 0;
        }
    }

    if (records != 0)
    {
        delete[] records;
        records = 0;
    }

    if (unkB8 != 0)
    {
        lib_object_detach_owner(unkB8);
        unkB8->destroy();
        unkB8 = 0;
    }

    if (unkBC != 0)
    {
        lib_object_detach_owner(unkBC);
        unkBC->destroy();
        unkBC = 0;
    }

    if (unkC0 != 0)
    {
        unkC0->destroy();
        unkC0 = 0;
    }
}

/** @brief Release the loaded data and every owned object. */
BootBattleTrophyViewer::~BootBattleTrophyViewer()
{
    delete unk14;

    for (s32 i = 0; i < 3; i++)
    {
        delete unk1C[i];
    }

    for (s32 i = 0; i < 10; i++)
    {
        if (unk28[i] != 0)
        {
            lib_object_detach_owner(unk28[i]);
            unk28[i]->destroy();
            unk28[i] = 0;
        }
    }

    delete resource_data;

    for (s32 i = 0; i < 300; i++)
    {
        if (trophy_images[i] != 0)
        {
            lib_object_detach_owner(trophy_images[i]);
            trophy_images[i]->destroy();
        }

        if (textures[i] != 0)
        {
            func_11EE00(D_001B65F4, textures[i]);
        }
    }

    if (records != 0)
    {
        delete[] records;
    }

    if (unk88 != 0)
    {
        unk88->destroy();
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

    if (unkA8 != 0)
    {
        unkA8->destroy();
    }

    if (sort_text != 0)
    {
        sort_text->destroy();
    }

    if (rank_text != 0)
    {
        rank_text->destroy();
    }

    if (unkC0 != 0)
    {
        unkC0->destroy();
        unkC0 = 0;
    }

    if (unkB8 != 0)
    {
        lib_object_detach_owner(unkB8);
        unkB8->destroy();
    }

    if (unkBC != 0)
    {
        lib_object_detach_owner(unkBC);
        unkBC->destroy();
    }
}

/** @brief Start loading resource 0x2B, clear the owned objects and build the three palettes. */
BootBattleTrophyViewer::BootBattleTrophyViewer()
{
    resource_data = func_139700(0x40, func_11C8C0(D_001B65E4, 0x2B));
    func_103E70(D_001B65E8, 0x2B, resource_data, 1, 0x34BC0, 0, 0, 0, 1);
    unk14 = new (0) u8[func_10CAA0(0x400) * 4 + 0x400];
    unk1C[0] = 0;
    unk1C[1] = 0;
    unk1C[2] = 0;

    for (s32 i = 0; i < 10; i++)
    {
        unk28[i] = 0;
    }

    for (s32 i = 0; i < 300; i++)
    {
        trophy_images[i] = 0;
        textures[i] = 0;
    }

    records = 0;
    slot = 0;
    bar_fading = 0;
    unk88 = 0;
    message_text = 0;
    cursor = 0;
    slot1_text = 0;
    slot2_text = 0;
    unkB8 = 0;
    unkBC = 0;
    number_label = 0;
    scroll_indicator = 0;
    name_text = 0;
    date_text = 0;
    unkA8 = 0;
    sort_text = 0;
    rank_text = 0;
    unkC0 = 0;
    slot_ready[0] = 0;
    slot_ready[1] = 0;
    row_count = 0x26;
    images_loaded = 0;
    by_time = 0;
    step = 0;
    unk1144 = 0;
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

/** @brief Clear the byte at offset 0x60. */
void BootNeedleMeter::func_001E0860()
{
    unk60 = 0;
}
