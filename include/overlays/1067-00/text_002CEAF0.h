#ifndef SO3_OVERLAYS_1067_00_TEXT_002CEAF0_H
#define SO3_OVERLAYS_1067_00_TEXT_002CEAF0_H

#include "types.h"

/** Partial receiver containing 64 allocations and three aligned buffer slots. */
typedef struct FieldBufferSlots
{
    u8 unk00[0x14];
    void* unk14[64];
    void* unk114;
    s32 unk118;
    void* unk11c[3];
    void* unk128[3];
    s32 unk134[3];
} FieldBufferSlots;

/** Partial header of a resource record linked by a byte offset. */
typedef struct FieldResourceRecord
{
    u8 unk00[0xC];
    u32 next_offset;
} FieldResourceRecord;

#include "overlays/1067-00/text_001DD3C0.h"

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 3.
 */
s32 func_002CFE00(FieldClass150070* object);
/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 4.
 */
s32 func_002D3BB0(FieldClass150070* object);
#endif

#ifdef __cplusplus
}
#endif

#endif
