#ifndef SO3_OVERLAYS_LIB_EMISSION_H
#define SO3_OVERLAYS_LIB_EMISSION_H

#include "overlays/lib/text_004CD3A0.h"

/** Secondary polymorphic base of the Lib grid emitter. */
class LibClass173A28 : public LibLink
{
public:
    /** @brief Destroy the secondary base. */
    virtual ~LibClass173A28()
    {
    }

    /**
     * @brief Free an object through the heap at D_001B6684 when one is set, otherwise through operator delete.
     * @param object Object storage, or null.
     */
    static void operator delete(void* object);

    /**
     * @brief Allocate an array from the heap at D_001B6684 when one is set, otherwise through operator new.
     * @param size Size in bytes.
     * @param heap Heap selector passed on to operator new.
     * @return The allocation.
     */
    static void* operator new[](u32 size, s32 heap);

    /**
     * @brief Free an array through the heap at D_001B6684 when one is set, otherwise through operator delete.
     * @param object Array storage, or null.
     */
    static void operator delete[](void* object);

    /**
     * @brief Free an array whose construction failed, the same way as operator delete[](void*).
     * @param object Array storage, or null.
     * @param heap Heap selector the array was allocated with.
     */
    static void operator delete[](void* object, s32 heap);
};

/** 0x4A0-byte emitter whose remaining resource and grid settings are unrecovered. */
class LibClass173990 : public LibTransform, public LibClass173A28
{
public:
    /** @brief Initialize the emitter's resources and grid settings. */
    LibClass173990();

    /** @brief Release the emitter's resource and storage. */
    virtual ~LibClass173990();

    /** @brief Report the emitter object kind. @return Six. */
    virtual s32 get_default_list_kind();

    /** @brief Detach and queue the emitter. */
    virtual void destroy();

    /** @brief Update the emitter and its attached grid. */
    virtual void update();

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

    u8 unk214[0x1F0];
    float unk404;
    float unk408;
    float unk40c;
    float unk410;
    float unk414;

    /** Squared cosine of half of unk414. */
    float unk418;

    /** One over the squared cosines of half of unk410 and half of unk414 subtracted. */
    float unk41c;

    u8 unk420[8];
    u32 unk428;
    u8 unk42c[0x65];
    u8 unk491;
    u8 unk492;
    u8 unk493;
    u8 unk494[7];
    u8 unk49b_0_5 : 6;
    u8 unk49b_6 : 1;
    u8 unk49b_7 : 1;
    u8 unk49c_0 : 1;
    u8 unk49c_1 : 1;
    u8 unk49c_2 : 1;
    u8 unk49c_3_7 : 5;
    u8 unk49d[3];
};

#endif
