#include "include_asm.h"
#include "main/system.h"

extern "C" {

extern s32 g_random_index;
extern u32 g_random_table[56];

/** @brief Regenerate all 55 words of the resident subtractive random table. */
static inline void refresh_random_table(void)
{
    s32 i;
    s32 j;

    for (i = 24; i > 0; --i)
    {
        g_random_table[i] -= g_random_table[i + 31];
    }

    for (j = 25; j <= 55; ++j)
    {
        g_random_table[j] -= g_random_table[j - 24];
    }
}

/**
 * @brief Advance the resident subtractive random sequence and return its next word.
 * @return Next unsigned word from the 55-element sequence.
 */
static inline u32 next_random_word(void)
{
    if (++g_random_index > 55)
    {
        refresh_random_table();
        g_random_index = 1;
    }

    return g_random_table[g_random_index];
}

/**
 * @brief Return a random fraction.
 * @return Random value from 0 up to 1.
 */
float resident_random_fraction(void)
{
    return next_random_word() * 2.32830671e-10f;
}

/**
 * @brief Return a random number below a limit.
 * @param limit Exclusive upper bound.
 * @return Random number from 0 to limit - 1, or 0 when limit is 0.
 */
u32 resident_random_below(u32 limit)
{
    if (limit == 0)
    {
        return 0;
    }

    return next_random_word() % limit;
}

/**
 * @brief Return a random number between two bounds.
 * @param low First bound, included.
 * @param high Second bound, excluded; it may be below low.
 * @return Random number from low up to (but not including) high, or low when the bounds are equal.
 */
s32 resident_random_range(s32 low, s32 high)
{
    s32 span;
    s32 result;

    if (high == low)
    {
        result = low;
    }
    else
    {
        span = high - low;
        span = span >= 0 ? span : -span;
        result = low + next_random_word() % span;
    }

    return result;
}

/**
 * @brief Return the next resident random number.
 * @return Random number from 0 to 0x7FFF.
 */
u32 resident_rand(void)
{
    return next_random_word() & 0x7FFF;
}

/**
 * @brief Advance the resident subtractive random sequence and return its next word.
 * @return Next unsigned word from the 55-element sequence.
 */
u32 resident_next_random_word(void)
{
    return next_random_word();
}

/**
 * @brief Seed the resident subtractive random table and warm it up.
 * @param seed Seed value.
 */
void resident_seed_random(u32 seed)
{
    s32 i;
    u32 value;
    s32 index;

    g_random_table[55] = seed;
    value = 1;

    for (i = 1; i <= 54; i++)
    {
        index = (21 * i) % 55;
        g_random_table[index] = value;
        value = seed - value;
        seed = g_random_table[index];
    }

    refresh_random_table();
    refresh_random_table();
    refresh_random_table();
    g_random_index = 55;
}

/**
 * @brief Write a number as decimal text.
 * @param buffer Receives the text and its terminating zero.
 * @param value Number to write; negative numbers get a leading '-'.
 * @param width Number of digits to write, padded on the left with pad and losing the leading digits that don't fit;
 * zero or less writes every digit.
 * @param pad Padding character.
 * @return buffer.
 */
char* resident_format_decimal(char* buffer, s32 value, s32 width, char pad)
{
    char* cursor;
    char digits[12];
    char* digit;
    s32 count;
    s32 i;
    s32 j;

    cursor = buffer;

    if (value < 0)
    {
        *cursor++ = '-';
        value = -value;
    }

    if (width > 0)
    {
        cursor += width;
        *cursor = 0;
        i = 0;

        for (i = 0; i < width; i++)
        {
            *--cursor = value % 10 + '0';
            value /= 10;

            if (value == 0)
            {
                i++;
                break;
            }
        }

        while (i < width)
        {
            *--cursor = pad;
            i++;
        }
    }
    else
    {
        digit = digits + sizeof(digits);
        count = 0;

        do
        {
            *--digit = value % 10 + '0';
            count++;
            value /= 10;
        } while (value > 0);

        for (j = 0; j < count; j++)
        {
            *cursor++ = *digit++;
        }

        *cursor = 0;
    }

    return buffer;
}

/**
 * @brief Get the resident system.
 * @return g_system.
 */
ResidentSystem* resident_get_system(void)
{
    return &g_system;
}
}
