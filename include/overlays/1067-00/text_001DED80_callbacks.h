#ifndef SO3_OVERLAYS_1067_00_TEXT_001DED80_CALLBACKS_H
#define SO3_OVERLAYS_1067_00_TEXT_001DED80_CALLBACKS_H

#include "types.h"

typedef struct FieldFlaggedListObject FieldFlaggedListObject;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Find a listed object whose flag word shares a bit with the mask and whose word at offset 0x70 matches the key.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 * @param key Value compared with the word at offset 0x70.
 * @param mask Bits tested against the flag word at offset 0x78.
 * @return The first matching object, or null if none matches.
 */
FieldFlaggedListObject* func_001DEE30(FieldFlaggedListObject* list, s32 key, u32 mask);

/**
 * @brief Detach the supplied object and invoke its release handler.
 * @param list First argument; unused by this callee.
 * @param object Object to detach and release.
 */
void func_001DEDF0(void* list, void* object);

#ifdef __cplusplus
}
#endif

#endif
