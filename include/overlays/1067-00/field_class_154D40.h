#ifndef SO3_OVERLAYS_1067_00_FIELD_CLASS_154D40_H
#define SO3_OVERLAYS_1067_00_FIELD_CLASS_154D40_H

#include "types.h"
#include "overlays/1067-00/text_001DD3C0.h"
#include "main/resident_001001E0.h"
#include "overlays/1067-00/field_vector4.h"

#ifdef __cplusplus
/** Partial FieldClass150050 with vtable D_154D40 in main data; its only virtual is the destructor. */
class FieldClass154D40 : public FieldClass150050
{
public:
    /** @brief Construct the object. */
    FieldClass154D40()
    {
    }

    /** @brief Destroy the object. */
    virtual ~FieldClass154D40()
    {
    }

    /**
     * @brief Release the object's storage through the Lib allocator.
     * @param object Storage to release.
     */
    static void operator delete(void* object);

    /**
     * @brief Allocate array storage through the Lib allocator.
     * @param size Byte count, including the array cookie.
     * @param heap Lib heap selector.
     * @return Array storage.
     */
    static void* operator new[](u32 size, s32 heap);

    /**
     * @brief Release array storage through the Lib allocator.
     * @param object Storage to release.
     */
    static void operator delete[](void* object);

    /**
     * @brief Release array storage when its construction throws.
     * @param object Storage to release.
     * @param heap Lib heap selector passed to operator new[].
     */
    static void operator delete[](void* object, s32 heap);
};

/** Partial FieldClass154D40 with vtable D_154E70 in main data; its only virtual is the destructor. */
class FieldClass154E70 : public FieldClass154D40
{
public:
    /** @brief Construct the object. */
    FieldClass154E70()
    {
    }

    /** @brief Destroy the object. */
    virtual ~FieldClass154E70()
    {
    }
};

/** Partial FieldClass154E70 with vtable D_154E60 in main data: the 64-byte secondary grid element. */
class FieldClass154E60 : public FieldClass154E70
{
public:
    /** @brief Construct the object. */
    FieldClass154E60();

    /** @brief Destroy the object. */
    virtual ~FieldClass154E60();

    u8 unk04[0xC];
    FieldVector4 unk10;
    FieldVector4 unk20;
    FieldVector4 unk30;
};

/** Bit set with vtable D_154E80 in main data; its data comes before the vptr. */
struct FieldBitset154E80
{
    /**
     * @brief Allocate cleared-on-demand word storage for a bit count.
     * @param count Number of bits.
     */
    FieldBitset154E80(u32 count)
    {
        unk08 = 0;
        unk0C = 0;
        resize(count);
    }

    /**
     * @brief Replace the word storage with room for a bit count.
     * @param count Number of bits.
     */
    void resize(u32 count)
    {
        if (!unk0C)
        {
            delete[] unk08;
        }
        unk00 = count;
        unk04 = (count + 63) >> 6;
        unk08 = new (0) u64[unk04];
        unk0C = 0;
    }

    /** @brief Clear every word. */
    void clear()
    {
        s32 words = unk04;
        for (s32 i = 0; i < words; i++)
        {
            unk08[i] = 0;
        }
    }

    s32 unk00;
    s32 unk04;
    u64* unk08;
    bool unk0C;

    /** @brief Release the word storage unless it is borrowed. */
    virtual ~FieldBitset154E80();
};

/** Partial grid base with vtable D_154D50 in main data; its only virtual is the destructor. */
class FieldClass154D50 : public FieldClass154D40
{
public:
    /** @brief Clear the borrowed-storage word. */
    FieldClass154D50()
    {
        unk08 = 0;
    }

    /** @brief Destroy the object. */
    virtual ~FieldClass154D50()
    {
    }

    // Virtuals in vtable order (byte offset in the name). Most slots are pure here
    // and filled by the grid classes; only the slots used so far are listed.
    virtual void func_slot0c() = 0;
    /** @brief Do nothing (shared by every grid). */
    virtual void func_002729A0();
    /** @brief Do nothing (shared by every grid). */
    virtual void func_002729B0();
    virtual void func_slot18() = 0;
    virtual void func_slot1c() = 0;
    virtual void func_slot20() = 0;
    virtual void func_slot24() = 0;
    virtual void func_slot28() = 0;
    virtual void func_slot2c() = 0;
    virtual void func_slot30() = 0;
    virtual void func_slot34() = 0;
    virtual void func_slot38() = 0;
    /**
     * @brief Report no selected cell.
     * @return -1.
     */
    virtual s32 func_00272D60();
    virtual void func_slot40() = 0;
    virtual void func_slot44() = 0;
    virtual void func_slot48() = 0;
    virtual void func_slot4c() = 0;
    virtual void func_slot50() = 0;
    virtual void func_slot54() = 0;
    /**
     * @brief Reallocate the cells, the bit set and the secondary elements for a new size.
     * @param rows Cell count.
     * @param columns Secondary elements per cell plus one.
     */
    virtual void resize(s32 rows, s32 columns) = 0;

    u8 unk04;
    s32 unk08;
    s32 unk0C;
    s32 unk10;
};
#endif

#endif
