#ifndef SO3_OVERLAYS_BOOT_TEXT_001EEC80_H
#define SO3_OVERLAYS_BOOT_TEXT_001EEC80_H

#include "types.h"
#include "overlays/boot/text_001DD3C0.h"

#ifdef __cplusplus
class FieldVec4A;
template <class T> struct BootTrackPool;
class BootPooledVectorTrack;
class BootPooledVectorCurveTrack;
class BootQuaternionTrackBase;
extern "C" {
#endif

/**
 * @brief BootTrack's slot 0x24, between append_key and replace_key; every family inherits it and none overrides it, so
 * its purpose is unknown. It does nothing, as Lib's copy (0x429850) does.
 * @param track Track; unused.
 */
void track_default_func_slot24(void* track);

/**
 * @brief BootTrack's append_key (slot 0x20), which the families' base classes inherit; it does nothing.
 * @param track Track; unused.
 * @return Zero.
 */
s32 track_default_append_key(void* track);

/**
 * @brief BootTrack's replace_key (slot 0x28), which the families' base classes inherit; it does nothing.
 * @param track Track; unused.
 * @return Zero.
 */
s32 track_default_replace_key(void* track);

/**
 * @brief BootTrack's insert_key (slot 0x2C), which the families' base classes inherit; it does nothing.
 * @param track Track; unused.
 * @return Zero.
 */
s32 track_default_insert_key(void* track);

/**
 * @brief BootTrack's read_key (slot 0x30), which the families' base classes inherit; it does nothing.
 * @param track Track; unused.
 * @return Zero.
 */
s32 track_default_read_key(void* track);

/**
 * @brief BootTrack's set_single_key (slot 0x34), which the families' base classes inherit; it does nothing.
 * @param track Track; unused.
 */
void track_default_set_single_key(void* track);

/**
 * @brief BootTrack's reset_keys (slot 0x38), which the families' base classes inherit; it does nothing.
 * @param track Track; unused.
 */
void track_default_reset_keys(void* track);

/**
 * @brief Mark a track's pool slot as free.
 * @param pool Pool that owns the track.
 * @param track Track to release.
 */
void vector_curve_track_pool_free(BootTrackPool<BootPooledVectorCurveTrack>* pool, BootPooledVectorCurveTrack* track);

/**
 * @brief Mark a track's pool slot as free.
 * @param pool Pool that owns the track.
 * @param track Track to release.
 */
void vector_track_pool_free(BootTrackPool<BootPooledVectorTrack>* pool, BootPooledVectorTrack* track);

/**
 * @brief BootQuaternionTrackBase's find_key_value (slot 0x7C): find the keyframe with a key and decode its rotation.
 * @param out Receives the rotation, or zero when the key is absent.
 * @param track Track to search.
 * @param key Key to find.
 */
void quaternion_track_find_key_value(FieldVec4A* out, BootQuaternionTrackBase* track, float key);

#ifdef __cplusplus
}
#endif

#endif
