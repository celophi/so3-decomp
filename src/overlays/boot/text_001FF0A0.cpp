#include "include_asm.h"
#include "overlays/boot/text_001FF0A0.h"
#include "overlays/boot/text_001FF9E0.h"
#include "main/resident_001001E0.h"

extern "C" {
extern void* D_001B65F4;
s32 func_10CAA0(s32 upper);
void func_11EE00(void* queue, void* allocation);
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

    if (unk8C != 0)
    {
        unk8C->destroy();
        unk8C = 0;
    }

    if (unk94 != 0)
    {
        unk94->destroy();
        unk94 = 0;
    }

    if (unk98 != 0)
    {
        unk98->destroy();
        unk98 = 0;
    }

    if (unk9C != 0)
    {
        unk9C->destroy();
        unk9C = 0;
    }

    if (unkA0 != 0)
    {
        unkA0->destroy();
        unkA0 = 0;
    }

    if (unkA4 != 0)
    {
        unkA4->destroy();
        unkA4 = 0;
    }

    if (unkA8 != 0)
    {
        unkA8->destroy();
        unkA8 = 0;
    }

    if (unkAC != 0)
    {
        unkAC->destroy();
        unkAC = 0;
    }

    if (unkB4 != 0)
    {
        unkB4->destroy();
        unkB4 = 0;
    }

    if (unk90 != 0)
    {
        unk90->destroy();
        unk90 = 0;
    }

    if (unkB0 != 0)
    {
        unkB0->destroy();
        unkB0 = 0;
    }

    for (s32 i = 0; i < 300; i++)
    {
        if (unk330[i] != 0)
        {
            lib_object_detach_owner(unk330[i]);
            unk330[i]->destroy();
            unk330[i] = 0;
        }

        if (unk7E4[i] != 0)
        {
            func_11EE00(D_001B65F4, unk7E4[i]);
            unk7E4[i] = 0;
        }
    }

    if (unk7E0 != 0)
    {
        delete[] unk7E0;
        unk7E0 = 0;
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
        if (unk330[i] != 0)
        {
            lib_object_detach_owner(unk330[i]);
            unk330[i]->destroy();
        }

        if (unk7E4[i] != 0)
        {
            func_11EE00(D_001B65F4, unk7E4[i]);
        }
    }

    if (unk7E0 != 0)
    {
        delete[] unk7E0;
    }

    if (unk88 != 0)
    {
        unk88->destroy();
    }

    if (unk8C != 0)
    {
        unk8C->destroy();
    }

    if (unk90 != 0)
    {
        unk90->destroy();
    }

    if (unk94 != 0)
    {
        unk94->destroy();
    }

    if (unk98 != 0)
    {
        unk98->destroy();
    }

    if (unk9C != 0)
    {
        unk9C->destroy();
    }

    if (unkB0 != 0)
    {
        unkB0->destroy();
    }

    if (unkA0 != 0)
    {
        unkA0->destroy();
    }

    if (unkA4 != 0)
    {
        unkA4->destroy();
    }

    if (unkA8 != 0)
    {
        unkA8->destroy();
    }

    if (unkAC != 0)
    {
        unkAC->destroy();
    }

    if (unkB4 != 0)
    {
        unkB4->destroy();
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
        unk330[i] = 0;
        unk7E4[i] = 0;
    }

    unk7E0 = 0;
    slot = 0;
    unkCC = 0;
    unk88 = 0;
    unk8C = 0;
    unk90 = 0;
    unk94 = 0;
    unk98 = 0;
    unkB8 = 0;
    unkBC = 0;
    unk9C = 0;
    unkB0 = 0;
    unkA0 = 0;
    unkA4 = 0;
    unkA8 = 0;
    unkAC = 0;
    unkB4 = 0;
    unkC0 = 0;
    unk57 = 0;
    unk58 = 0;
    unk6C = 0x26;
    unk54 = 0;
    unk56 = 0;
    unk50 = 0;
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

    unk80 = 0;
}

/** @brief Clear the byte at offset 0x60. */
void BootNeedleMeter::func_001E0860()
{
    unk60 = 0;
}
