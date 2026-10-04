#ifndef SO3_OVERLAYS_1067_00_TEXT_00200710_H
#define SO3_OVERLAYS_1067_00_TEXT_00200710_H

#include "types.h"
#ifdef __cplusplus
#include "overlays/1067-00/text_001DD3C0.h"

/** Script context base with its command flags after the opaque state. */
class FieldClass150DC0 : public FieldClass150070
{
public:
    /** @brief Destroy the script state and its inherited node. */
    virtual ~FieldClass150DC0();
    /** @brief Return the context's fixed state value. @return Always one. */
    virtual s32 func_00201520();
    /** @brief Return the current context scale. @return Context scale. */
    virtual float func_00201530();
    u8 unk14[0x4B4];
    u8 unk4c8_0 : 1;
    u8 unk4c8_1 : 1;
    u8 unk4c8_2_7 : 6;
};
#endif

#include "overlays/1067-00/text_001FF260.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Load the selected character and animation resources.
 * @param object Resource list to process.
 * @param character_key Key of character resources to process.
 * @param animation_key Key of animation resources to process.
 * @param mode Select synchronous loading when nonzero.
 * @return One when loading succeeds and the resident state permits it, otherwise zero.
 */
s32 func_002019C0(FieldResourceList14* object, s32 character_key, s32 animation_key, s32 mode);

/**
 * @brief Decrement counters for matching resource entries that pass their flag checks.
 * @param object Resource list to update.
 * @param first Low-halfword key for kinds 0x43484152 and 0x41545243.
 * @param second Low-halfword key for kind 0x414E494D.
 */
void func_002016F0(FieldResourceList14* object, s32 first, s32 second);

/**
 * @brief Increment counters for matching resource entries that pass their flag checks.
 * @param object Resource list to update.
 * @param first Low-halfword key for kinds 0x43484152 and 0x41545243.
 * @param second Low-halfword key for kind 0x414E494D.
 */
void func_002017B0(FieldResourceList14* object, s32 first, s32 second);

/**
 * @brief Release the resource entry matching all three keys.
 * @param object Resource list to search.
 * @param first First key.
 * @param second Second key.
 * @param key Third key.
 */
void func_00201D70(FieldResourceList14* object, u32 first, u32 second, u32 key);

/**
 * @brief Find the size selected by a resource entry's flag.
 * @param object Resource list to search.
 * @param kind Resource kind to match.
 * @param key Resource key to match.
 * @return The selected size, or zero when no matching entry exists.
 */
u32 func_00201E20(FieldResourceList14* object, u32 kind, u32 key);

/**
 * @brief Find the data of a resource entry.
 * @param object Resource list to search.
 * @param kind Resource kind to match.
 * @param key Resource key to match.
 * @param mode Lookup option; zero in the known callers.
 * @return The entry's data, or null when no matching entry exists.
 */
void* func_00201EA0(FieldResourceList14* object, u32 kind, u32 key, s32 mode);

/**
 * @brief Return the fixed value one.
 * @param object Receiver of the call.
 * @return One.
 */
s32 func_00201510(void* object);

/**
 * @brief Return the fixed value one.
 * @param object Receiver of the call.
 * @return One.
 */
s32 func_00201520(void* object);

/**
 * @brief Return the current field frame delta.
 * @param object Receiver of the call; unused.
 * @return Current frame delta.
 */
float func_00201530(void* object);

/**
 * @brief Add an object to the resident object queue.
 * @param object Object to queue.
 */
void func_00201540(void* object);

/**
 * @brief Detach an object and add it to the resident object queue.
 * @param object Object to detach and queue.
 */
void func_00201560(void* object);

/**
 * @brief Return the fixed value twelve.
 * @param object Receiver of the call.
 * @return Twelve.
 */
s32 func_00202120(void* object);

#ifdef __cplusplus
}
#endif

#endif
