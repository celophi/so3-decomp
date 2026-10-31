#ifndef SO3_SDK_MAIN_LIBM_GUESS_0013F3E0_H
#define SO3_SDK_MAIN_LIBM_GUESS_0013F3E0_H

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Compute the single-precision cosine. @param angle Angle in radians. @return Cosine of the angle. */
float cosf_guess(float angle);

/** @brief Compute the single-precision sine. @param angle Angle in radians. @return Sine of the angle. */
float sinf_guess(float angle);

/**
 * @brief Compute the single-precision tangent.
 * @param angle Angle in radians.
 * @return Tangent of the angle.
 */
float func_00141EC0(float angle);

/**
 * @brief Compute the angle from two floating-point components.
 * @param y First component.
 * @param x Second component.
 * @return Angle in radians.
 */
float func_00142148(float y, float x);

/**
 * @brief Compute the single-precision base-10 logarithm.
 * @param value Value to take the logarithm of.
 * @return Base-10 logarithm of value.
 */
float log10f_guess(float value);

#ifdef __cplusplus
}
#endif

#endif
