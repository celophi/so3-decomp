#ifndef SO3_MAIN_UTILITY_H
#define SO3_MAIN_UTILITY_H

#include "types.h"
#include "ee.h"
#include "sdk/main/libkernl_00121940.h"

#ifdef __cplusplus
struct ResidentSystem;
#else
typedef struct ResidentSystem ResidentSystem;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get the resident system.
 * @return g_system.
 */
ResidentSystem* resident_get_system(void);

/**
 * @brief Seed the resident random sequence; main seeds it from timer 0.
 * @param seed Seed value.
 */
void resident_seed_random(u32 seed);

/**
 * @brief Advance the resident random sequence and return its next word.
 * @return Next unsigned random word.
 */
u32 resident_next_random_word(void);

/**
 * @brief Return the next resident random number.
 * @return Random number.
 */
u32 resident_rand(void);

/**
 * @brief Return a random fraction.
 * @return Random value from 0 up to 1.
 */
float resident_random_fraction(void);

/**
 * @brief Return a random number below a limit.
 * @param limit Exclusive upper bound.
 * @return Random number from 0 to limit - 1, or 0 when limit is 0.
 */
u32 resident_random_below(u32 limit);

/**
 * @brief Return a random number between two bounds.
 * @param low First bound, included.
 * @param high Second bound, excluded; it may be below low.
 * @return Random number from low up to (but not including) high, or low when the bounds are equal.
 */
s32 resident_random_range(s32 low, s32 high);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {

/**
 * @brief Write a number as decimal text.
 * @param buffer Receives the text and its terminating zero.
 * @param value Number to write; negative numbers get a leading '-'.
 * @param width Number of digits to write, padded on the left with pad and losing the leading digits that don't fit;
 * zero or less writes every digit.
 * @param pad Padding character.
 * @return buffer.
 */
char* resident_format_decimal(char* buffer, s32 value, s32 width, char pad);
}
#endif

#endif
