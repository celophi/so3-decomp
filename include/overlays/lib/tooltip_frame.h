#ifndef SO3_OVERLAYS_LIB_TOOLTIP_FRAME_H
#define SO3_OVERLAYS_LIB_TOOLTIP_FRAME_H

#include "types.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_0045AD10.h"

#ifdef __cplusplus
/** Contextual tooltip widget with its owned DMA storage and resident table, with vtable D_1797B0 in main data. */
class EquipTooltipFrame : public LibWidget
{
    public:
        /** @brief Initialize the tooltip display and drawing storage. */
        EquipTooltipFrame()
        {
            unk38 = 0x12;
        }

        virtual ~EquipTooltipFrame();

        /** @brief Draw the tooltip rectangle and its stored resource. */
        virtual void draw();

        LibStorageBlock0C unk40;
        u8 unk4c[4];
};

/** Resident tooltip container with one tooltip and eight owned text widgets. */
class EquipFactorTooltip : public LibContainer
{
    public:
        /** @brief Initialize the tooltip container and its embedded displays. */
        EquipFactorTooltip()
        {
            type_id = 0x6FF8;
        }

        virtual ~EquipFactorTooltip();

        /**
         * @brief Update the tooltip text animation.
         * @param first First update flag.
         * @param second Second update flag.
         * @param third Third update flag.
         */
        virtual void func_00412C40(u32 first, u32 second, u32 third);

        EquipTooltipFrame frame;
        LibTextWidget factor_texts[8];
        float position_x;
        float position_y;
        float position_z;
        s32 factor_ids[8];
        u8 unka0c;
};
#endif

#endif
