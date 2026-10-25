#ifndef SO3_OVERLAYS_LIB_BLEND_TRANSFORM_H
#define SO3_OVERLAYS_LIB_BLEND_TRANSFORM_H

#include "overlays/lib/text_004CD3A0.h"

#ifdef __cplusplus
/** Transform with a stored blend mode. */
class LibBlendTransform : public LibTransform
{
public:
    /** @brief Initialize the transform and clear its blend state. */
    LibBlendTransform()
    {
        blend_mode = 0;
        unk211 = 0;
    }

    /** @brief Destroy the blend transform and its transform base. */
    virtual ~LibBlendTransform()
    {
    }

    /** @brief Set the inherited state byte to two when blending is enabled. */
    virtual void func_003F4420();

    /**
     * @brief Store the blend mode.
     * @param mode Blend mode to store.
     */
    virtual void set_blend_mode(u8 mode);

    /**
     * @brief Apply the source blend mode and copy its inherited transform state.
     * @param source Blend transform to copy.
     */
    virtual void copy_blend_state(const LibBlendTransform* source);

    u8 blend_mode;
    u8 unk211;
};
#endif

#endif
