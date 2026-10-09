#ifndef SO3_OVERLAYS_1067_00_FIELD_DURATION_H
#define SO3_OVERLAYS_1067_00_FIELD_DURATION_H

#include "types.h"

#ifdef __cplusplus
/** Sixteen-byte duration decoder with its MAIN vtable at 0x153E20 and its vtable pointer at offset 0xC. */
class FieldDuration
{
public:
    /** @brief Clear the duration components. */
    FieldDuration();
    u32 unk00;
    s16 hours;
    s16 minutes;
    s16 seconds;
    /** @brief Destroy the duration decoder. */
    virtual ~FieldDuration();
    /**
     * @brief Split seconds into hours, minutes, and seconds, capped at 999:59:59.
     * @param value Unsigned duration in seconds.
     */
    void set_seconds(u32 value);
    /**
     * @brief Read the whole hours value or one decimal digit.
     * @param position Zero for the whole value; 1 for units, 2 for tens, 3 for hundreds.
     * @return Selected signed halfword, zero for nonpositive hours, or -1 for an invalid position.
     */
    s16 hour_digit(s32 position);
    /**
     * @brief Read the whole minutes value or one decimal digit.
     * @param position Zero for the whole value; 1 for units, 2 for tens.
     * @return Selected signed halfword, zero for nonpositive minutes, or -1 for an invalid position.
     */
    s16 minute_digit(s32 position);
    /**
     * @brief Read the whole seconds value or one decimal digit.
     * @param position Zero for the whole value; 1 for units, 2 for tens.
     * @return Selected signed halfword, zero for nonpositive seconds, or -1 for an invalid position.
     */
    s16 second_digit(s32 position);
};
#endif

#endif
