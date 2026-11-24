#ifndef SO3_OVERLAYS_LIB_EMISSION_H
#define SO3_OVERLAYS_LIB_EMISSION_H

#include "overlays/lib/text_004CD3A0.h"
#include "main/main.h"

/** Secondary polymorphic base of the Lib grid emitter. */
class LibClass173A28 : public LibLink
{
public:
    virtual ~LibClass173A28()
    {
    }

    /**
     * @brief Free an object through the heap at g_field_allocation_heap when one is set, otherwise through operator delete.
     * @param object Object storage, or null.
     */
    static void operator delete(void* object);

    /**
     * @brief Free an object whose construction failed, the same way as operator delete(void*).
     * @param object Object storage, or null.
     * @param heap Heap selector the object was allocated with.
     */
    static void operator delete(void* object, s32 heap);

    /**
     * @brief Allocate an object from the heap at g_field_allocation_heap when one is set, otherwise through operator
     *        new.
     * @param size Size in bytes.
     * @param heap Heap selector passed on to operator new.
     * @return The allocation.
     */
    static void* operator new(u32 size, s32 heap);

    /**
     * @brief Allocate an array from the heap at g_field_allocation_heap when one is set, otherwise through operator new.
     * @param size Size in bytes.
     * @param heap Heap selector passed on to operator new.
     * @return The allocation.
     */
    static void* operator new[](u32 size, s32 heap);

    /**
     * @brief Free an array through the heap at g_field_allocation_heap when one is set, otherwise through operator delete.
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

class LibObject1751A0;
/** 16-byte element of LibClass173490's two arrays; its contents aren't known yet, it's copied as one 128-bit value. */
struct LibClass173490Entry
{
    inline LibClass173490Entry();

    /**
     * @brief Copy all 16 bytes.
     * @param other Element to copy.
     * @return This element.
     */
    LibClass173490Entry& operator=(const LibClass173490Entry& other)
    {
        *(unsigned __int128*)this = *(const unsigned __int128*)&other;
        return *this;
    }

    u32 unk00[4];
};

/** 0x4A0-byte emitter whose remaining resource and grid settings are unrecovered. */
class LibClass173990 : public LibTransform, public LibClass173A28
{
public:
    /** @brief Initialize the emitter's resources and grid settings. */
    LibClass173990();

    /** @brief Release the emitter's resource and storage. */
    virtual ~LibClass173990();

    /**
     * @brief Report the emitter object kind.
     * @return Six.
     */
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

    /** @brief Stop using the source image model, destroying it when this was its last user. */
    void release_source();

    u8 unk214[0xC];
    FieldVec4A unk220;
    FieldVec4A unk230;
    FieldVec4A unk240;
    FieldVec4A unk250;
    FieldVec4A unk260;
    FieldVec4A unk270;
    u8 unk280[0x10];
    FieldVec4A unk290;
    FieldVec4A unk2a0;
    FieldVec4A unk2b0;
    FieldVec4A unk2c0;
    FieldVec4A unk2d0;
    FieldVec4A unk2e0;
    FieldVec4A unk2f0;
    FieldVec4A unk300;
    FieldVec4A unk310;
    FieldVec4A unk320;
    FieldVec4A unk330;
    FieldVec4A unk340;
    FieldVec4A unk350;
    FieldVec4A unk360;
    FieldVec4A unk370;
    FieldVec4A unk380;
    FieldVec4A unk390;
    FieldVec4A unk3a0;
    FieldVec4A unk3b0;
    float unk3c0[8];
    LibClass173490Entry* entries;
    LibObject1751A0* source;
    u32 unk3e8;
    float unk3ec;
    float unk3f0;
    float unk3f4;
    float unk3f8;
    float unk3fc;
    float unk400;
    float unk404;
    float unk408;
    float unk40c;
    float unk410;
    float unk414;
    float unk418;
    float unk41c;
    float unk420;
    s32 entry_count;
    u32 unk428;
    u32 unk42c;
    u8 unk430[4];
    float unk434;
    float unk438;
    u8 unk43c[0x14];
    FieldVec4A velocity;
    FieldVec4A previous_position;
    FieldVec4A position_delta;
    u8 unk480[8];
    u8 unk488[8];
    u8 unk490;
    u8 unk491;
    u8 unk492;
    u8 unk493;
    u8 unk494;
    u8 unk495;
    u8 unk496;
    u8 unk497;
    u8 unk498;
    u8 unk499_0 : 1;
    u8 unk499_1 : 1;
    u8 unk499_2_7 : 6;
    u8 unk49a;
    u8 unk49b_0 : 1;
    u8 unk49b_1 : 1;
    u8 unk49b_2 : 1;
    u8 unk49b_3 : 1;
    u8 unk49b_4 : 1;
    u8 unk49b_5 : 1;
    u8 unk49b_6 : 1;
    u8 unk49b_7 : 1;
    u8 unk49c_0 : 1;
    u8 unk49c_1 : 1;
    u8 unk49c_2 : 1;
    u8 unk49c_3 : 1;
    u8 unk49c_4 : 1;
    u8 unk49c_5 : 1;
    u8 unk49c_6 : 1;
    u8 unk49c_7 : 1;
    u8 unk49d[3];
};

#endif
