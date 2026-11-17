#include "main/stats.h"

typedef struct ResidentStats
{
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0c;
    u32 unk10;
    u32 unk14;
} ResidentStats;

/**
 * @brief Clamp a value to [0, 999999999] and store it at offset 0x14.
 * @param object Object containing the word.
 * @param value Value to store.
 * @return The clamped value.
 */
s32 resident_stats_set_word14(void* object, s32 value)
{
    ResidentStats* receiver = (ResidentStats*)object;

    if (value < 0)
    {
        value = 0;
    }

    if (value > 999999999)
    {
        value = 999999999;
    }

    receiver->unk14 = value;
    return value;
}

/** Return the word at receiver offset 0x14. */
u32 resident_stats_get_word14(const void* object)
{
    const ResidentStats* receiver = (const ResidentStats*)object;
    return receiver->unk14;
}

s32 resident_stats_set_word10(void* object, s32 value)
{
    ResidentStats* receiver = (ResidentStats*)object;

    if (value < 0)
    {
        value = 0;
    }

    if (value > 100)
    {
        value = 100;
    }

    receiver->unk10 = value;
    return value;
}

/** Return the word at receiver offset 0x10. */
u32 resident_stats_get_word10(const void* object)
{
    const ResidentStats* receiver = (const ResidentStats*)object;
    return receiver->unk10;
}

/**
 * @brief Clamp a value to [0, 99999999] and store it at offset 0xC.
 * @param object Object containing the word.
 * @param value Value to store.
 * @return The clamped value.
 */
s32 resident_stats_set_word0c(void* object, s32 value)
{
    ResidentStats* receiver = (ResidentStats*)object;

    if (value < 0)
    {
        value = 0;
    }

    if (value > 99999999)
    {
        value = 99999999;
    }

    receiver->unk0c = value;
    return value;
}

/** Return the word at receiver offset 0xC. */
u32 resident_stats_get_word0c(const void* object)
{
    const ResidentStats* receiver = (const ResidentStats*)object;
    return receiver->unk0c;
}

s32 resident_stats_set_word08(void* object, s32 value)
{
    ResidentStats* receiver = (ResidentStats*)object;

    if (value < 0)
    {
        value = 0;
    }

    if (value > 255)
    {
        value = 255;
    }

    receiver->unk08 = value;
    return value;
}

/** Return the word at receiver offset 0x8. */
u32 resident_stats_get_word08(const void* object)
{
    const ResidentStats* receiver = (const ResidentStats*)object;
    return receiver->unk08;
}

s32 resident_stats_set_word04(void* object, s32 value)
{
    ResidentStats* receiver = (ResidentStats*)object;

    if (value < 0)
    {
        value = 0;
    }

    if (value > 999)
    {
        value = 999;
    }

    receiver->unk04 = value;
    return value;
}

/** Return the word at receiver offset 0x4. */
u32 resident_stats_get_word04(const void* object)
{
    const ResidentStats* receiver = (const ResidentStats*)object;
    return receiver->unk04;
}

s32 resident_stats_set_word00(void* object, s32 value)
{
    ResidentStats* receiver = (ResidentStats*)object;

    if (value < 0)
    {
        value = 0;
    }

    if (value > 9999)
    {
        value = 9999;
    }

    receiver->unk00 = value;
    return value;
}

/** Return the word at receiver offset 0x0. */
u32 resident_stats_get_word00(const void* object)
{
    const ResidentStats* receiver = (const ResidentStats*)object;
    return receiver->unk00;
}
