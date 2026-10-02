#ifndef SO3_BOOT_RESIDENT_00101550_H
#define SO3_BOOT_RESIDENT_00101550_H

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

#ifdef __cplusplus
}
#endif

#endif
