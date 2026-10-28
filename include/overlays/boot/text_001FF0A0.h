#ifndef SO3_OVERLAYS_BOOT_TEXT_001FF0A0_H
#define SO3_OVERLAYS_BOOT_TEXT_001FF0A0_H

#include "types.h"

#ifdef __cplusplus
#include "overlays/boot/text_001DD3C0.h"

/** Partial 0xF10-byte record the Battle Trophies viewer keeps for each of the 300 trophies. */
struct BootTrophyRecordF10
{
    /** @brief Leave the record uninitialized. */
    BootTrophyRecordF10()
    {
    }

    u8 unk00[0xF10];
};

/**
 * Battle Trophies viewer, with vtable D_171CD0 in main data. It loads the trophy data from a memory card slot and
 * lists the 300 battle trophies.
 */
class BootBattleTrophyViewer : public BootClass170E90
{
    public:
        /** @brief Start loading resource 0x2B, clear the owned objects and build the three palettes. */
        BootBattleTrophyViewer();

        /** @brief Release the loaded data and every owned object. */
        virtual ~BootBattleTrophyViewer();

        /** @brief Report the list kind used when registration requests the default. @return Four. */
        virtual s32 get_default_list_kind();

        /** @brief Run the viewer. */
        virtual void update();

        /** @brief Destroy every owned object and release the per-trophy allocations. */
        void release();

        u8* unk14;

        /** Resource 0x2B. */
        u8* resource_data;

        u8* unk1C[3];
        BootClass170E90* unk28[10];
        s32 unk50;
        u8 unk54;

        /** Memory card slot being read: zero for slot 1, one for slot 2. */
        u8 slot;

        u8 unk56;
        u8 unk57;
        u8 unk58;
        u8 unk59[0x13];
        s32 unk6C;
        u8 unk70[0x10];
        s32 unk80;
        u8 unk84[4];
        BootClass178660* unk88;
        BootClass170E90* unk8C;
        BootClass170E90* unk90;
        BootClass170E90* unk94;
        BootClass170E90* unk98;
        BootClass170E90* unk9C;
        BootClass170E90* unkA0;
        BootClass170E90* unkA4;
        BootClass170E90* unkA8;
        BootClass170E90* unkAC;
        BootClass170E90* unkB0;
        BootClass170E90* unkB4;
        BootClass170E90* unkB8;
        BootClass170E90* unkBC;
        BootClass170E90* unkC0;
        u8 unkC4[8];
        u8 unkCC;
        u8 unkCD[0x263];
        BootClass170E90* unk330[300];
        BootTrophyRecordF10* unk7E0;
        void* unk7E4[300];
        u8 unkC94[0x4B0];
        s32 unk1144;
        u8 unk1148[4];

        /** Three 32-color grey-blue ramps, stored in the GS swizzled CLUT order. */
        u32 palettes[3][32];
};
#endif

#endif
