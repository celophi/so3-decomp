#ifndef SO3_OVERLAYS_LIB_GRID_BITSET_H
#define SO3_OVERLAYS_LIB_GRID_BITSET_H

#include "types.h"
#include "main/main.h"

#ifdef __cplusplus
/** Bit set of the grid's active cells, with vtable D_173F58 in main data after its data. */
class LibGridBitset
{
public:
    /** @brief Start empty, with no words. */
    LibGridBitset() : bits(0), borrowed(0)
    {
    }

    /**
     * @brief Allocate word storage for a bit count.
     * @param count Number of bits.
     */
    LibGridBitset(u32 count)
    {
        bits = 0;
        borrowed = 0;
        resize(count);
    }

    /**
     * @brief Replace the word storage with room for a bit count.
     * @param count Number of bits.
     */
    void resize(u32 count)
    {
        if (!borrowed)
        {
            delete[] bits;
        }

        this->count = count;
        words = (count + 63) >> 6;
        bits = new (0) u64[words];
        borrowed = 0;
    }

    /**
     * @brief Clear one bit.
     * @param index Bit to clear.
     */
    void clear_bit(s32 index)
    {
        u32 word = (u32)index >> 6;
        u32 bit = index & 63;
        bits[word] &= ~((u64)1 << bit);
    }

    /** @brief Clear every word. */
    void clear()
    {
        s32 total = words;

        for (s32 i = 0; i < total; i++)
        {
            bits[i] = 0;
        }
    }

    s32 count;
    s32 words;
    u64* bits;
    bool borrowed;

    /** @brief Free the words unless they're borrowed. */
    virtual ~LibGridBitset()
    {
        if (!borrowed)
        {
            delete[] bits;
        }
    }
};
#endif

#endif
