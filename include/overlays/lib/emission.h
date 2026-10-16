#ifndef SO3_OVERLAYS_LIB_EMISSION_H
#define SO3_OVERLAYS_LIB_EMISSION_H

#include "overlays/lib/text_004CD3A0.h"

/** Secondary polymorphic base of the Lib grid emitter. */
class LibClass173A28 : public LibClass171E80
{
public:
    /** @brief Destroy the secondary base. */
    virtual ~LibClass173A28();
};

/** 0x4A0-byte emitter whose remaining resource and grid settings are unrecovered. */
class LibClass173990 : public LibClass178EA0, public LibClass173A28
{
public:
    /** @brief Initialize the emitter's resources and grid settings. */
    LibClass173990();

    /** @brief Release the emitter's resource and storage. */
    virtual ~LibClass173990();

    /** @brief Report the emitter object kind. @return Six. */
    virtual s32 func_003EEBC0();

    /** @brief Detach and queue the emitter. */
    virtual void func_003EF740();

    /** @brief Update the emitter and its attached grid. */
    virtual void func_003EEBD0();

    /**
     * @brief Initialize entries in the attached grid using optional vectors.
     * @param count Number of entries to generate.
     * @param position_offset Position added to each generated entry, or null.
     * @param first_offset First additional three-component offset, or null.
     * @param second_offset Second additional three-component offset, or null.
     * @param color_scale Four-component color multiplier, or null.
     * @param extra6 Optional four-float input.
     * @param extra7 Optional two-component offset.
     * @param extra8 Optional three-component offset.
     * @param extra9 Optional three-component offset.
     * @param extra10 Optional three-component offset.
     * @param extra11 Optional three-component offset.
     */
    virtual void emit_entries(s32 count, const LibVector4* position_offset, const LibVector4* first_offset, const LibVector4* second_offset,
                              const LibVector4* color_scale, const LibVector4* extra6, const LibVector4* extra7, const LibVector4* extra8,
                              const LibVector4* extra9, const LibVector4* extra10, const LibVector4* extra11);

    /**
     * @brief Copy emission settings from another emitter.
     * @param other Emitter supplying the settings.
     */
    virtual void copy_state(const LibClass173990* other);

    u8 unk214[0x28C];
};

#endif
