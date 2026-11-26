#ifndef SO3_OVERLAYS_LIB_TRANSFORM_INLINES_H
#define SO3_OVERLAYS_LIB_TRANSFORM_INLINES_H

#include "overlays/lib/text_004CD3A0.h"
#include "ee.h"
#include "vu0.h"

#ifdef __cplusplus
/**
 * @brief Report whether the transform's transposed matrix is up to date.
 * @param transform Transform to check.
 * @return Nonzero when transposed_transform is current.
 */
static inline s32 transpose_is_current(const LibTransform* transform)
{
    return transform->unk20e_0;
}

/**
 * @brief Mark the transpose current and rebuild it from the transform.
 * @param transform Transform to update.
 */
static inline void transpose_transform(LibTransform* transform)
{
    transform->unk20e_0 = 1;
    transform->unk20e_1 = 0;
    ee_transpose_matrix(&transform->transposed_transform, &transform->transform);
}

/**
 * @brief Mark a freshly updated transform's transpose current and rebuild it.
 * @param transform Transform to update.
 */
static inline void mark_transpose_current(LibTransform* transform)
{
    transform->unk20e_0 = true;
    transform->unk20e_1 = 0;
    ee_transpose_matrix(&transform->transposed_transform, &transform->transform);
}

/**
 * @brief Bring the transform's transposed matrix up to date if needed.
 * @param transform Transform to read.
 * @return The transposed matrix.
 */
static inline const LibMatrix44Value* get_transposed_transform(LibTransform* transform)
{
    if (!transpose_is_current(transform))
    {
        transpose_transform(transform);
    }

    return &transform->transposed_transform;
}

/**
 * @brief Move a world-space position into the transform's local space.
 * @param world Position in world space.
 * @param local Receives the position in local space.
 */
inline void LibTransform::to_local(const LibVector4* world, LibVector4* local)
{
    vu0_apply_matrix(&inverse_transform, world, local);
}
#endif

#endif
