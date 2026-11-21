#ifndef SO3_OVERLAYS_LIB_HEIGHT_GRID_H
#define SO3_OVERLAYS_LIB_HEIGHT_GRID_H

#include "overlays/lib/text_004CD3A0.h"

#define LIB_HEIGHT_GRID_HOLE 0x7FFF

/** Grid of 16-bit heights over a rectangle in a transform's local space. */
struct LibHeightGrid
{
    s32 cell_width;
    s32 cell_depth;
    s32 stride;
    u8 unk0c[4];
    s32 min_x;
    s32 min_z;
    s32 max_x;
    s32 max_z;
    s16 heights[1];
};

#ifdef __cplusplus
/** Transform carrying a height grid, with vtable D_175530 in main data. */
class LibClass175530 : public LibTransform
{
public:
    /** @brief Free the grid unless it is borrowed, then destroy the transform. */
    virtual ~LibClass175530();

    LibMatrix44Value world_to_local;
    LibHeightGrid* grid;
    u8 grid_is_borrowed;
    u8 out_of_range;
};

/**
 * @brief Sample the grid's height under a world position, filling holes from neighbouring corners.
 * @param object Grid transform.
 * @param position World position.
 * @return World height at the position, or the transform's height when the position is off the grid or on a hole.
 */
extern "C" float func_004E7250(LibClass175530* object, const LibVector4* position);
#endif

#endif
