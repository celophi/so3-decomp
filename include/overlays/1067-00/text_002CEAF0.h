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

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

#endif
