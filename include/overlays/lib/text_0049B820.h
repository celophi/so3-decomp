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

/** Return the floating-point value 1.0f. */
float func_004A2200(void* object);

/** Return the floating-point value 1.0f. */
float func_004A2210(void* object);

/** Return the floating-point value 1.0f. */
float func_004A2220(void* object);

/** Return the floating-point value 1.0f. */
float func_004A2230(void* object);

/** Return the floating-point value 1.0f. */
float func_004A2240(void* object);

/** Return the floating-point value 1.0f. */
float func_004A2250(void* object);

/** Return the floating-point value 1.0f. */
float func_004A2260(void* object);

/** Return the floating-point value 1.0f. */
float func_004A22B0(void* object);

/** Return the fixed integer value 1. */
s32 func_004A08B0(void* object);

/** Return the fixed integer value 13. */
s32 func_004A88A0(void* object);

/** Return the fixed integer value 11. */
s32 func_004A8FF0(void* object);

/** Return the fixed value 0. */
s32 func_004A0C50(void* object);

/** Return the fixed value 0. */
s32 func_004A0C70(void* object);

/** Return the fixed value 0. */
s32 func_004A87F0(void* object);

/** Return the fixed value 0. */
s32 func_004A8800(void* object);

/** Return the fixed value 0. */
s32 func_004A8DD0(void* object);

/** Return the fixed value 0. */
s32 func_004AA410(void* object);

void func_004A08A0(void* object);
void func_004A0C40(void* object);
void func_004A0C60(void* object);
void func_004A6D00(void* object);
void func_004A6D10(void* object);
void func_004A9220(void* object);
void func_004A9230(void* object);

/** Clear the word at receiver offset 0x2C and copy four aligned values from the source. */
void func_004A06B0(void* object, const void* source);

/** Queue the receiver's DMA submission object and return its queue result. */
s32 func_004A4570(void* object);

/** Forward the receiver to func_004D00B0. */
void func_004A4550(void* object);

#ifdef __cplusplus
/** Return the second pointer argument unchanged. */
void* func_004A59C0(void* object, void* value);

}
#endif

#endif
