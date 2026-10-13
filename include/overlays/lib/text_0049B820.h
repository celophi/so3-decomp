#ifndef SO3_OVERLAYS_LIB_TEXT_0049B820_H
#define SO3_OVERLAYS_LIB_TEXT_0049B820_H

#include "types.h"

#ifdef __cplusplus
#include "overlays/lib/text_004CD3A0.h"

enum
{
    LIB_LOD_LEVEL_CAPACITY = 8,
    LIB_LOD_OBJECT_CAPACITY = 64
};

/** Partial level-selection controller with primary vtable at 0x177960. */
class LibLodController : public LibClass178EA0
{
public:
    /** @brief Initialize the level-selection controller. */
    LibLodController();
    /** @brief Destroy the controller. */
    virtual ~LibLodController();
    /** @brief Report the controller kind. @return Kind nine. */
    virtual s32 func_003EEBC0();
    /** @brief Select the active object range from the current transformed depth. */
    virtual void func_003EEBD0();
    /** @brief Copy level-selection state and inherited transform state. @param source Source controller. */
    virtual void copy_state(const LibLodController* source);

    /**
     * @brief Store and apply an offset to the controller's position.
     * @param offset Position offset.
     */
    void apply_position_offset(const FieldVec4A& offset);

    u8 position_offset_applied;
    u8 unk211[3];
    s32 object_count;
    s32 level_boundaries[LIB_LOD_LEVEL_CAPACITY];
    s32 level_count;
    s32 active_level;
    float range_minimums[LIB_LOD_LEVEL_CAPACITY];
    float range_maximums[LIB_LOD_LEVEL_CAPACITY];
    void* display_manager;
    void* objects[LIB_LOD_OBJECT_CAPACITY];
    u8 unk384[0xC];
    FieldVec4B position_offset;
};

typedef LibLodController LibEntryHandleCollection;
#else
/** Opaque level-selection controller used by the C handle-collection interface. */
typedef struct LibLodController LibEntryHandleCollection;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Append a handle when the collection has fewer than sixty-four entries.
 * @param collection Destination collection.
 * @param object Handle to append.
 */
void lib_append_entry_handle(LibEntryHandleCollection* collection, void* object);

/**
 * @brief Update the renderable object's resource buffers and state flags.
 * @param object Renderable object.
 */
void func_004A2370(void* object);


/**
 * @brief Set renderable resource state when its buffers are eligible.
 * @param object Renderable receiver.
 * @return One when state was applied, or zero when the request was skipped.
 */
s32 func_004A29D0(void* object);

#ifdef __cplusplus
}
#endif

#endif
