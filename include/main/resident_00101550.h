#ifndef SO3_MAIN_RESIDENT_00101550_H
#define SO3_MAIN_RESIDENT_00101550_H

#include "types.h"

/** Dispatch table whose complete layout is not yet known. */
typedef struct ResidentDispatchTable ResidentDispatchTable;

/** Partial prefix of an object registered with the resident dispatcher. */
typedef struct ResidentRegisteredObject
{
    const ResidentDispatchTable* dispatch;
} ResidentRegisteredObject;

/** Partial resident object reached through D_001B65E8. */
typedef struct ResidentObject1B65E8
{
    u8 unk00[0x30];
    u8 unk30;
} ResidentObject1B65E8;

/** Opaque resident decoder used by the resource loading helpers. */
typedef struct ResidentDecodeObject ResidentDecodeObject;

/** Partial resource header containing a payload size and relative link. */
typedef struct ResidentResourceHeader
{
    u8 unk00[8];
    u32 unk08;
    u32 next_offset;
} ResidentResourceHeader;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Run the object's two update steps until the second reports no more work.
 * @param object Object to update.
 * @return Nonzero while the object is still busy.
 */
s32 func_00102AA0(ResidentObject1B65E8* object);

/**
 * @brief Submit a request to the object at D_001B65E8.
 * @param object Receiving object.
 * @param key First request word.
 * @param size Request size.
 * @param mask Third request word.
 * @param word Fourth request word.
 * @param mode Fifth request word.
 * @return Request result; meaning not yet known.
 */
s32 func_00103640(ResidentObject1B65E8* object, s32 key, u32 size, u32 mask, u32 word, s32 mode);

/**
 * @brief Submit the alternative request form to the object at D_001B65E8.
 * @param object Receiving object.
 * @param key First request word.
 * @param size Request size.
 * @param mask Third request word.
 * @param word Fourth request word.
 * @param mode Fifth request word.
 * @return Request result; meaning not yet known.
 */
s32 func_00103B20(ResidentObject1B65E8* object, s32 key, u32 size, u32 mask, u32 word, s32 mode);

/**
 * @brief Submit a resident request with an owner and two extra words; meaning not yet known.
 * @param object Resident object D_001B65E8.
 * @param key First request word.
 * @param size Second request word.
 * @param mask Third request word.
 * @param value Fourth request word.
 * @param owner Owner passed through to the request.
 * @param word Sixth request word.
 * @param mode Seventh request word.
 * @param flag Eighth request word.
 * @return Request result; meaning not yet known.
 */
s32 func_00103E70(ResidentObject1B65E8* object, s32 key, u32 size, u32 mask, s32 value, void* owner, u32 word, s32 mode,
                  s32 flag);

/**
 * @brief Initialize the dispatch pointer and register the object.
 * @param object Object to register.
 * @return The registered object.
 */
ResidentRegisteredObject* func_00101560(ResidentRegisteredObject* object);

/** Resident resource decoder. */
extern ResidentDecodeObject* D_001B65EC;

/**
 * @brief Decode or copy the selected resource into a destination buffer.
 * @param decoder Resident decoder.
 * @param source Resource header.
 * @param destination Destination buffer.
 * @param index Resource index.
 * @return Decode result.
 */
s32 func_001025A0(ResidentDecodeObject* decoder, ResidentResourceHeader* source, void* destination, s32 index);

/**
 * @brief Allocate storage for the selected resource.
 * @param decoder Resident decoder.
 * @param source Resource header.
 * @param index Resource index.
 * @param aligned Allocation alignment mode.
 * @return Allocated byte buffer, or null when allocation fails.
 */
u8* func_00102920(ResidentDecodeObject* decoder, ResidentResourceHeader* source, s32 index, s32 aligned);

/**
 * @brief Find a resource header by following its relative links.
 * @param decoder Resident decoder; unused.
 * @param source First resource header.
 * @param index Number of links to follow.
 * @return Selected header, or null when the chain ends.
 */
ResidentResourceHeader* func_00102A40(ResidentDecodeObject* decoder, ResidentResourceHeader* source, s32 index);

#ifdef __cplusplus
}
#endif

#endif
