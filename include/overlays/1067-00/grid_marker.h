#ifndef SO3_OVERLAYS_1067_00_GRID_MARKER_H
#define SO3_OVERLAYS_1067_00_GRID_MARKER_H

#include "overlays/1067-00/text_0023B1D0.h"
#include "overlays/lib/text_00419A70.h"

#ifdef __cplusplus
/** Grid selection marker with resident table 0x1531A0. */
struct FieldObject23BE00 : public ItemCreationClass172870
{
    /** @brief Construct the marker with no grid and unit vertical scale. */
    FieldObject23BE00();
    /** @brief Destroy inherited drawing storage and the widget base. */
    virtual ~FieldObject23BE00();
    /** @brief Empty refresh callback. */
    virtual void func_00413D20();
    /**
     * @brief Configure the marker rectangle and the grid it follows.
     * @param x Horizontal marker origin.
     * @param y Vertical marker origin.
     * @param width Positive marker width.
     * @param scale Vertical marker scale.
     * @param target Existing grid, or null to allocate a default grid.
     * @param color Packed marker color.
     * @return Zero for nonpositive width, otherwise one.
     */
    s32 func_0023BB20(float x, float y, float width, float scale,
                     FieldObject23CEA0* target, u32 color);
    /**
     * @brief Position the marker at a grid entry.
     * @param size Positive width of the selected entry.
     * @param index Nonnegative grid entry index.
     * @return One after updating, or zero for no grid or invalid dimensions/index.
     */
    s32 func_0023B9B0(float size, s16 index);
    FieldObject23CEA0* grid;
    float origin_x;
    float origin_y;
    float entry_width;
    float vertical_scale;
};
#endif

#endif
