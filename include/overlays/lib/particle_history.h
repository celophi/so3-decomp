#ifndef SO3_OVERLAYS_LIB_PARTICLE_HISTORY_H
#define SO3_OVERLAYS_LIB_PARTICLE_HISTORY_H

#include "types.h"

/** Aligned vector with floating-point and raw-word views. */
typedef union LibQuad128
{
    unsigned __int128 raw;
    float value[4];
    u32 word[4];
#ifdef __cplusplus
    /** @brief Access the vector's four floating-point components. @return The components. */
    float* data()
    {
        return value;
    }

    /** @brief Access the vector's four floating-point components. @return The components. */
    const float* data() const
    {
        return value;
    }

    /** @brief Copy all four words at once. @param other Vector to copy. @return This vector. */
    LibQuad128& operator=(const LibQuad128& other)
    {
        raw = other.raw;
        return *this;
    }
#endif
} LibQuad128;

/** Bit mask selecting which groups a history receiver copies. */
typedef struct LibHistoryMask
{
    u8 unk00[8];
    const u64* bits;
} LibHistoryMask;

/** History record with position, attributes, and control words. */
typedef struct LibHistoryRecord40
{
    LibQuad128 unk00;
    LibQuad128 position;
    LibQuad128 attributes;
    LibQuad128 control;
} LibHistoryRecord40;

/** Three-vector output record. */
typedef struct LibHistoryOutput30
{
    LibQuad128 position;
    LibQuad128 attributes;
    LibQuad128 control;
} LibHistoryOutput30;

/** Source record of size 0x170 with position and attribute vectors. */
typedef struct LibHistorySource170
{
    LibQuad128 unk00;
    LibQuad128 position;
    LibQuad128 attributes;
    u8 unk30[0x140];
} LibHistorySource170;

/** Source record of size 0x120 with position and attribute vectors. */
typedef struct LibHistorySource120
{
    LibQuad128 unk00;
    LibQuad128 position;
    LibQuad128 attributes;
    u8 unk30[0xF0];
} LibHistorySource120;

/** Source record of size 0xB0 with position and attribute vectors. */
typedef struct LibHistorySourceB0
{
    LibQuad128 unk00;
    LibQuad128 position;
    LibQuad128 attributes;
    u8 unk30[0x80];
} LibHistorySourceB0;

/** Receiver prefix the history copier at 0x441C40 reads; its sources are 0x170-byte records. */
typedef struct LibHistoryReceiver441C40
{
    u8 unk00[0xC];
    s32 limit;
    s32 samples;
    LibHistorySource170* source;
    u32 unk18;
    LibHistoryMask* mask;
    LibHistoryRecord40* history;
    u32 unk24;
    union
    {
        float value;
        u32 bits;
    } unk28;
    s32 index;
    float unk30;
    float decrement;
    u8 unk38[0xC];
    float scale;
    u8 unk48[5];
    u8 mode;
    u8 unk4e[8];
    u8 policy;
} LibHistoryReceiver441C40;

/** Receiver prefix the history copier at 0x48ECB0 reads; its sources are 0xB0-byte records. */
typedef struct LibHistoryReceiver48ECB0
{
    u8 unk00[0xC];
    s32 limit;
    s32 samples;
    LibHistorySourceB0* source;
    u32 unk18;
    LibHistoryMask* mask;
    LibHistoryRecord40* history;
    u32 unk24;
    union
    {
        float value;
        u32 bits;
    } unk28;
    s32 index;
    float unk30;
    float decrement;
    u8 unk38[0xC];
    float scale;
    u8 unk48[5];
    u8 mode;
    u8 unk4e[8];
    u8 policy;
} LibHistoryReceiver48ECB0;

/** Receiver prefix the history copier at 0x4952D0 reads; its sources are 0x120-byte records. */
typedef struct LibHistoryReceiver4952D0
{
    u8 unk00[0xC];
    s32 limit;
    s32 samples;
    LibHistorySource120* source;
    u32 unk18;
    LibHistoryMask* mask;
    LibHistoryRecord40* history;
    u32 unk24;
    union
    {
        float value;
        u32 bits;
    } unk28;
    s32 index;
    float unk30;
    float decrement;
    u8 unk38[0xC];
    float scale;
    u8 unk48[5];
    u8 mode;
    u8 unk4e[8];
    u8 policy;
} LibHistoryReceiver4952D0;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Copy selected group histories and extend the caller's VU0 bounds.
 * @param object Receiver containing selection masks, source records, and histories.
 * @param capacity Output-record count at which processing stops before the next group.
 * @param output Destination array of three-vector records.
 * @param stamp Nonzero to copy the receiver's raw word at 0x28 into control records.
 */
void func_00441C40(LibHistoryReceiver441C40* object, s32 capacity, LibHistoryOutput30* output, u32 stamp);

/**
 * @brief Copy selected group histories and extend the caller's VU0 bounds.
 * @param object Receiver containing selection masks, source records, and histories.
 * @param capacity Output-record count at which processing stops before the next group.
 * @param output Destination array of three-vector records.
 * @param stamp Nonzero to copy the receiver's raw word at 0x28 into control records.
 */
void func_0048ECB0(LibHistoryReceiver48ECB0* object, s32 capacity, LibHistoryOutput30* output, u32 stamp);

/**
 * @brief Copy selected group histories and extend the caller's VU0 bounds.
 * @param object Receiver containing selection masks, source records, and histories.
 * @param capacity Output-record count at which processing stops before the next group.
 * @param output Destination array of three-vector records.
 * @param stamp Nonzero to copy the receiver's raw word at 0x28 into control records.
 */
void func_004952D0(LibHistoryReceiver4952D0* object, s32 capacity, LibHistoryOutput30* output, u32 stamp);

#ifdef __cplusplus
}
#endif

#endif
