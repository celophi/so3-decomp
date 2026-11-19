#ifndef SO3_OVERLAYS_LIB_TEXT_004ABA60_H
#define SO3_OVERLAYS_LIB_TEXT_004ABA60_H

#include "types.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/tracks.h"

#ifdef __cplusplus
struct FieldFloatSpan1C;
class LibAnimation;
class LibAnimationTarget;
extern "C" {

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
 * @brief Apply every eligible animation entry at a frame through func_004BD4F0.
 * @param object Animation object.
 * @param frame Requested frame; a negative frame leaves the animation marked as restarting.
 * @param mode Nonzero to stop at the first entry that returns a nonzero status.
 * @return Status of the last applied entry, or 0 when the animation has no entries.
 */
s32 func_004B43C0(LibAnimation* object, float frame, s32 mode);

/**
 * @brief Apply every entry of one target at a frame, when the animation belongs to the current scene.
 * @param object Animation object.
 * @param target Target whose entries to apply.
 * @param frame Requested frame; a negative frame leaves the animation marked as restarting.
 * @param mode Nonzero to stop at the first entry that returns a nonzero status.
 * @return Status of the last applied entry, or 0 when nothing was applied.
 */
s32 func_004B46E0(LibAnimation* object, LibAnimationTarget* target, float frame, s32 mode);

/**
 * @brief Return the floating-point value 0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
/**
 * @brief Return the floating-point value 0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */


/** Return the fixed value 0. */
s32 func_004B3D60(void* object);

/** Return the fixed value 0. */
s32 func_004B3D70(void* object);






}
#endif

#endif
