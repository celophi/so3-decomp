#ifndef SO3_OVERLAYS_LIB_TEXT_004AB8B0_H
#define SO3_OVERLAYS_LIB_TEXT_004AB8B0_H

#include "types.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/tracks.h"

#ifdef __cplusplus
struct FieldFloatSpan1C;
class LibAnimation;
class LibAnimationTarget;
extern "C" {

void func_004AD380(void* object);
void func_004B1890(void* object);
void func_004B2580(void* object);

/** Clear receiver state at 0x58 and 0x50, then run the shared reset helper. */
void func_004ACFF0(void* object);
/** Reset receiver state at 0xB0 and 0xB4, then run the shared reset helper. */
void func_004B1800(void* object);

/** Forward two float values, passing the second through a stack address. */
void func_004B24A0(void* object, float value1, float value2);
void func_004B2500(void* object, float value1, float value2);

/** Copy the float at receiver offset 0x54 to the output. */
void func_004AD2B0(const void* object, float* value);

/** Copy the float at receiver offset 0x50 to the output. */
void func_004AFF60(const void* object, float* value);

/** Copy the float at receiver offset 0xB8 to the output. */
void func_004B1820(const void* object, float* value);

/** Copy the float at receiver offset 0x4C to the output. */
void func_004B2750(const void* object, float* value);

/** Write the difference between the selected 16-byte entry value and the first value. */
void func_004AFF70(const void* object, float* output);

/** Write the difference between the selected 8-byte entry value and the first value. */
void func_004B2720(const void* object, float* output);

/**
 * @brief Evaluate four interpolation coefficients over their cached key range.
 * @param span Coefficients and segment bounds.
 * @param key Sort value.
 * @return Interpolated value.
 */
float func_4B16C0(FieldFloatSpan1C* span, float key);

/**
 * @brief Apply every eligible animation entry at a frame.
 * @param object Animation object.
 * @param frame Requested frame; a negative frame leaves the animation marked as restarting.
 * @param mode Nonzero to stop at the first entry that returns a nonzero status.
 * @return Status of the last applied entry, or 0 when the animation has no entries.
 */
s32 lib_animation_apply_frame(LibAnimation* object, float frame, s32 mode);

/**
 * @brief Apply one animation entry.
 * @param object Animation object.
 * @param entry Entry to apply.
 * @param frame Frame to apply it at.
 * @param mode Mode passed to lib_animation_apply_frame.
 * @param status Status so far.
 * @return The new status.
 */
s32 func_004B4840(LibAnimation* object, LibAnimationEntry14* entry, float frame, s32 mode, s32 status);

/**
 * @brief Read a target's translation, rotation and scale from its animation channels.
 *
 * A whole-vector channel wins; otherwise up to three per-axis channels fill the components in order, and
 * per-axis rotation angles are converted to a quaternion.
 * @param object Animation object.
 * @param target Bound target to update.
 */
void lib_animation_read_channel_pose(LibAnimation* object, LibAnimationTarget* target);

/**
 * @brief Process the animation at a requested frame.
 * @param object Animation object.
 * @param frame Requested frame.
 * @param mode Processing mode.
 * @return Processing status.
 */
s32 func_004B43C0(LibAnimation* object, float frame, s32 mode);

/**
 * @brief Process the animation into a vector state at a requested frame.
 * @param object Animation object.
 * @param target Vector state.
 * @param frame Requested frame.
 * @param mode Processing mode.
 * @return Processing status.
 */
s32 func_004B46E0(LibAnimation* object, LibAnimationTarget* target, float frame, s32 mode);

/**
 * @brief Return the floating-point value 0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_004B0E20(void* object);

/**
 * @brief Return the floating-point value 0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_004B2A90(void* object);

/** Return the word at receiver offset 0x30. */
u32 func_004AC910(const void* object);

/** Return the word at receiver offset 0x4. */
u32 func_004ACAE0(const void* object);

/** Return the word at receiver offset 0x30. */
u32 func_004B0600(const void* object);

/** Return the word at receiver offset 0x4. */
u32 func_004B0810(const void* object);

/** Return the word at receiver offset 0x18. */
u32 func_004B0D60(const void* object);

/** Return the word at receiver offset 0x4. */
u32 func_004B0F40(const void* object);

/** Return the word at receiver offset 0x10. */
u32 func_004B2A60(const void* object);

/** Return the word at receiver offset 0x4. */
u32 func_004B2AD0(const void* object);


/** Return the signed halfword at receiver offset 0x38. */
s16 func_004AC920(const void* object);

/** Return the signed halfword at receiver offset 0x3A. */
s16 func_004AC930(const void* object);

/** Return the signed halfword at receiver offset 0x38. */
s16 func_004B0610(const void* object);

/** Return the signed halfword at receiver offset 0x3A. */
s16 func_004B0620(const void* object);

/** Return the signed halfword at receiver offset 0x20. */
s16 func_004B0D70(const void* object);

/** Return the signed halfword at receiver offset 0x22. */
s16 func_004B0D80(const void* object);

/** Return the signed halfword at receiver offset 0x18. */
s16 func_004B2A70(const void* object);

/** Return the signed halfword at receiver offset 0x1A. */
s16 func_004B2A80(const void* object);


/** Return the fixed integer value 99. */
s32 func_004ABAA0(void* object);

/** Return the fixed value 0. */
s32 func_004ACC10(void* object);

/** Return the fixed value 0. */
s32 func_004ACC50(void* object);

/** Return the fixed value 0. */
s32 func_004ACC90(void* object);

/** Return the fixed value 0. */
s32 func_004B0630(void* object);

/** Return the fixed value 0. */
s32 func_004B0640(void* object);

/** Return the fixed value 0. */
s32 func_004B0650(void* object);

/** Return the fixed value 0. */
s32 func_004B0D90(void* object);

/** Return the fixed value 0. */
s32 func_004B0DA0(void* object);

/** Return the fixed value 0. */
s32 func_004B0DB0(void* object);

/** Return the fixed value 0. */
s32 func_004B2DD0(void* object);

/** Return the fixed value 0. */
s32 func_004B2E10(void* object);

/** Return the fixed value 0. */
s32 func_004B2E50(void* object);

/** Return the fixed value 0. */
s32 func_004B3D60(void* object);

/** Return the fixed value 0. */
s32 func_004B3D70(void* object);

void func_004ABAB0(void* object);
void func_004ABD30(void* object);
void func_004ACBD0(void* object);
void func_004B0660(void* object);
void func_004B0DC0(void* object);
void func_004B2D90(void* object);


/** Clear four consecutive words at the start of the receiver. */
void func_004AC990(void* object);

/** Clear four consecutive words at the start of the receiver. */
void func_004B06C0(void* object);

/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_004AC850(void* object, u8 mode);

/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_004AD410(void* object, u8 mode);

/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_004B0CA0(void* object, u8 mode);

/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_004B29A0(void* object, u8 mode);


/** Set the high packed mode at its target field and record whether either mode equals four. */
void func_004AC8B0(void* object, u8 mode);

/** Set the high packed mode at its target field and record whether either mode equals four. */
void func_004B05A0(void* object, u8 mode);

/** Set the high packed mode at its target field and record whether either mode equals four. */
void func_004B0D00(void* object, u8 mode);

/** Set the high packed mode at its target field and record whether either mode equals four. */
void func_004B2A00(void* object, u8 mode);


/** Find a key in the receiver's fixed-size entry array. */
s32 func_004AC940(void* object, float key);

/** Return the key span between the first and last entries. */
float func_004AC9B0(void* object);
float func_004B06E0(void* object);
float func_004B0E30(void* object);
float func_004B2CC0(void* object);

/** Find a key in the receiver's fixed-size entry array. */
s32 func_004B0670(void* object, float key);

/** Find a key in the receiver's fixed-size entry array. */
s32 func_004B0DD0(void* object, float key);

/** Find a key in the receiver's fixed-size entry array. */
s32 func_004B2D10(void* object, float key);


}
#endif

#endif
