#ifndef SO3_OVERLAYS_LIB_ITEM_ALLOCATION_H
#define SO3_OVERLAYS_LIB_ITEM_ALLOCATION_H

#include "types.h"
#include "main/resident_0010A0E0.h"

/** Packed sixteen-byte item allocation record. */
struct ItemCreationAllocationRecord
{
    union
    {
        u16 halves[2];
        struct
        {
            u16 definition_index : 10;
            u16 factor0_low_bits : 6;
            u16 factor0_high_bits : 4;
            u16 factor1 : 10;
            u16 unk03_high : 2;
        } bits;
    } definition_factors;
    union
    {
        u16 halves[2];
        struct
        {
            u16 factor2 : 10;
            u16 factor3_low_bits : 6;
            u16 factor3_high_bits : 4;
            u16 factor4 : 10;
            /** Suppress the allocation ID when the record checksum is valid. */
            u16 suppress_allocation_id : 1;
            u16 unk07_high : 1;
        } bits;
    } factors_234;
    union
    {
        u16 halves[2];
        struct
        {
            u16 factor5 : 10;
            u16 factor6_low_bits : 6;
            u16 factor6_high_bits : 4;
            u16 factor7 : 10;
            u16 unk0b_high : 2;
        } bits;
    } factors_567;
    u8 modification_number : 7;
    u8 equipped_owner_low_bit : 1;
    u8 equipped_owner_high_bits : 3;
    /** @brief Random two-bit shift used in the record checksum. */
    u8 checksum_shift : 2;
    u8 battle_usable : 1;
    u8 allocated : 1;
    u8 new_item : 1;
    /** @brief Checksum of the six halfwords at offsets 00 through 0A. */
    u16 checksum;

    /**
     * @brief Calculate the checksum of the six halfwords for a given shift.
     * @param shift Two-bit shift applied to the checksum key.
     * @return Calculated checksum.
     */
    u16 calculate_checksum(u32 shift) const
    {
        return (0x83CF << shift) ^ ((factors_567.halves[0] + (definition_factors.halves[0] + factors_234.halves[0])) ^
                                  (definition_factors.halves[1] + (factors_234.halves[1] + factors_567.halves[1])));
    }
    /**
     * @brief Calculate the checksum of the six halfwords with the stored shift.
     * @return Calculated checksum.
     */
    u16 calculate_checksum() const
    {
        return (0x83CF << checksum_shift) ^ ((factors_567.halves[0] + (definition_factors.halves[0] + factors_234.halves[0])) ^
                                           (definition_factors.halves[1] + (factors_234.halves[1] + factors_567.halves[1])));
    }
    /**
     * @brief Clear the record, choose its checksum shift and store the checksum.
     * @param key Fixed shift to use instead of a random one, or null.
     */
    void reset(const u8* key)
    {
        *(unsigned __int128*)this = 0;
        checksum_shift = resident_next_random_word() & 3;
        if (key != 0)
        {
            checksum_shift = *key;
        }
        checksum = calculate_checksum(checksum_shift);
    }
    /**
     * @brief Test whether the stored checksum differs from the record contents.
     * @return True when the checksum differs.
     */
    bool invalid() const
    {
        return checksum != calculate_checksum();
    }
    /**
     * @brief Read the catalog definition index from a valid allocation.
     * @return Definition index, or zero when the checksum differs.
     */
    u16 definition_index()
    {
        if (invalid())
        {
            return 0;
        }
        return definition_factors.bits.definition_index;
    }
};

#endif
