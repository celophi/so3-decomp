#ifndef SO3_OVERLAYS_1067_00_TEXT_0020D9A0_H
#define SO3_OVERLAYS_1067_00_TEXT_0020D9A0_H

#include "types.h"

/** Partial receiver with links and an index at offsets 0x14-0x1C. */
typedef struct FieldNodeLink
{
    u8 unk00[0x14];
    void* context;
    void* entry;
    s32 index;
} FieldNodeLink;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Store the context, entry, and index on the receiver.
 * @param object Receiver containing the link fields.
 * @param entry Entry to store at offset 0x18.
 * @param context Context to store at offset 0x14.
 * @param index Index to store at offset 0x1C.
 */
void func_0020DBC0(FieldNodeLink* object, void* entry, void* context, s32 index);

#ifdef __cplusplus
}
#endif

#endif
