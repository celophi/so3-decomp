#ifndef SO3_OVERLAYS_LIB_GRID_EMISSION_H
#define SO3_OVERLAYS_LIB_GRID_EMISSION_H

#include "types.h"
#include "overlays/lib/particle_grid.h"
#include "overlays/lib/emission_vu0.h"
#include "main/resident_data.h"

/** Optional vector inputs a grid supplies to its linked emitters. */
enum LibEmissionInputFlags
{
    LIB_EMISSION_POSITION = 0x01,
    LIB_EMISSION_FIRST_OFFSET = 0x02,
    LIB_EMISSION_SECOND_OFFSET = 0x04,
    LIB_EMISSION_COLOR_SCALE = 0x08
};

#ifdef __cplusplus
/**
 * @brief Emit entries through a grid's primary linked emitter.
 * @param grid Grid owning the emitter, its settings and its transform.
 * @param position Position transformed when the position flag is set.
 * @param first_offset First offset, transformed when its flag is set.
 * @param second_offset Second offset, transformed when its flag is set.
 * @param color_scale Color multiplier used when its flag is set.
 */
static inline void lib_grid_emit_primary(LibGridEmitter* grid, const LibVector4* position, const LibVector4* first_offset,
                                         const LibVector4* second_offset, const LibVector4* color_scale)
{
    LibVector4 transformed_position;
    LibVector4 transformed_first;
    LibVector4 transformed_second;
    LibVector4 saved_state[2];
    const LibVector4* position_arg;
    const LibVector4* first_offset_arg;
    const LibVector4* second_offset_arg;
    const LibVector4* color_arg;
    u8 flags = grid->primary_emission_flags;

    if (flags & LIB_EMISSION_POSITION)
    {
        vu0_transform_emission_point(&grid->unk60, position, &transformed_position);
        position_arg = &transformed_position;
    }
    else
    {
        position_arg = 0;
    }

    if (flags & LIB_EMISSION_FIRST_OFFSET)
    {
        vu0_transform_emission_direction(&grid->unk60, first_offset, &transformed_first);
        first_offset_arg = &transformed_first;
    }
    else
    {
        first_offset_arg = 0;
    }

    if (flags & LIB_EMISSION_SECOND_OFFSET)
    {
        vu0_transform_emission_direction(&grid->unk60, second_offset, &transformed_second);
        second_offset_arg = &transformed_second;
    }
    else
    {
        second_offset_arg = 0;
    }

    if (flags & LIB_EMISSION_COLOR_SCALE)
    {
        color_arg = color_scale;
    }
    else
    {
        color_arg = 0;
    }

    vu0_save_emission_state(saved_state);
    grid->primary_emitter->emit_entries(grid->primary_emission_count, position_arg, first_offset_arg, second_offset_arg,
                                        color_arg, 0, 0, 0, 0, 0, 0);
    vu0_reset_emission_state();
    vu0_set_emission_delta(g_frame_seconds);
    vu0_restore_emission_state(saved_state);
}

/**
 * @brief Emit entries through a grid's secondary linked emitter, if it has one.
 * @param grid Grid owning the emitter, its settings and its transform.
 * @param position Position transformed when the position flag is set.
 * @param first_offset First offset, transformed and scaled when its flag is set. Its fourth component receives the
 * grid's unk3C after emission.
 * @param second_offset Second offset, transformed when its flag is set.
 * @param color_scale Color multiplier used when its flag is set.
 */
static inline void lib_grid_emit_secondary(LibGridEmitter* grid, const LibVector4* position, LibVector4* first_offset,
                                           const LibVector4* second_offset, const LibVector4* color_scale)
{
    if (grid->secondary_emitter != 0)
    {
        LibVector4 transformed_position;
        LibVector4 transformed_first;
        LibVector4 transformed_second;
        LibVector4 saved_state[2];
        const LibVector4* position_arg;
        const LibVector4* first_offset_arg;
        const LibVector4* second_offset_arg;
        const LibVector4* color_arg;
        u8 flags = grid->secondary_emission_flags;

        if (flags & LIB_EMISSION_POSITION)
        {
            vu0_transform_emission_point(&grid->unk60, position, &transformed_position);
            position_arg = &transformed_position;
        }
        else
        {
            position_arg = 0;
        }

        if (flags & LIB_EMISSION_FIRST_OFFSET)
        {
            vu0_transform_emission_direction(&grid->unk60, first_offset, &transformed_first);
            first_offset_arg = &transformed_first;
            float scale = grid->secondary_emission_scale;
            transformed_first.x *= scale;
            transformed_first.y *= scale;
            transformed_first.z *= scale;
        }
        else
        {
            first_offset_arg = 0;
        }

        if (flags & LIB_EMISSION_SECOND_OFFSET)
        {
            vu0_transform_emission_direction(&grid->unk60, second_offset, &transformed_second);
            second_offset_arg = &transformed_second;
        }
        else
        {
            second_offset_arg = 0;
        }

        if (flags & LIB_EMISSION_COLOR_SCALE)
        {
            color_arg = color_scale;
        }
        else
        {
            color_arg = 0;
        }

        vu0_save_emission_state(saved_state);
        grid->secondary_emitter->emit_entries(grid->secondary_emission_count, position_arg, first_offset_arg,
                                              second_offset_arg, color_arg, 0, 0, 0, 0, 0, 0);
        vu0_reset_emission_state();
        vu0_set_emission_delta(g_frame_seconds);
        vu0_restore_emission_state(saved_state);
        first_offset->w = grid->unk3C;
    }
}
#endif

#endif
