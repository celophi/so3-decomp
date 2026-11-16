#ifndef SO3_OVERLAYS_LIB_GRID_FRAME_H
#define SO3_OVERLAYS_LIB_GRID_FRAME_H

#include "types.h"

/** A vector whose fourth word can hold a frame index. */
typedef union GridFrameVector
{
    unsigned __int128 packed;
    float floats[4];

    struct
    {
        float xyz[3];
        s32 frame_index;
    } components;
} GridFrameVector;

/** Per-cell frame playback state. */
typedef struct GridFrameState
{
    s32 reverse;
    s32 frame_index;
    float remaining_time;
    s32 boundary_count;
} GridFrameState;

/** An animated vector, its rate, and the cell's frame playback state. */
typedef struct GridFrameMotion
{
    GridFrameVector value;
    GridFrameVector rate;
    GridFrameState frame;
} GridFrameMotion;

typedef struct GridRowElement
{
    u8 unk00[0x30];
    GridFrameVector unk30;
} GridRowElement;

/** Output record containing an updated vector and an optional frame index. */
typedef struct GridOutputRecord
{
    u8 unk00[0x20];
    GridFrameVector frame_vector;
} GridOutputRecord;

typedef struct GridBitset
{
    u8 unk00[0x8];
    u64* unk08;
} GridBitset;

typedef struct GridFrameHeader
{
    u8 frame_count;
    u8 unk01[2];
    u8 loop_mode;
} GridFrameHeader;

/** A 0x50-byte frame record with its duration measured in frames. */
typedef struct GridFrameRecord
{
    u8 unk00[0xC];
    float duration_frames;
    u8 unk10[0x40];
} GridFrameRecord;

/**
 * @brief Clear an active cell bit.
 * @param object Bit set owning the storage.
 * @param index Unsigned cell index.
 */
static inline void grid_clear_cell_bit(GridBitset* object, u32 index)
{
    u32 word_index = index >> 6;
    u64 keep_mask = ~((u64)1 << (index & 63));
    object->unk08[word_index] &= keep_mask;
}

typedef struct GridCell00481B90
{
    u8 unk00[0x30];
    GridFrameMotion motion;
} GridCell00481B90;

typedef struct GridOwner00481B90
{
    u8 unk00[0xC];
    s32 unk0C;
    s32 unk10;
    GridCell00481B90* unk14;
    u8 unk18[4];
    GridBitset* unk1C;
    GridRowElement* unk20;
    u8 unk24[8];
    s32 unk2C;
    float unk30;
    u8 unk34[0x18];
    u8 unk4C;
    u8 unk4d[0xA];
    u8 skip_frame_playback;
    u8 unk58[0x48];
    GridFrameHeader* frame_header;
    GridFrameRecord* frame_records;
} GridOwner00481B90;

/**
 * @brief Get a 0x60-byte cell's motion state at offset 0x30.
 * @param cell Cell to read.
 * @return The motion state, or null when the cell address is null.
 */
static inline GridFrameMotion* grid_cell_motion_00481B90(GridCell00481B90* cell)
{
    GridFrameMotion* motion = (GridFrameMotion*)cell;

    if (cell != 0)
    {
        motion = &cell->motion;
    }

    return motion;
}

typedef struct GridCell00488110
{
    u8 unk00[0x60];
    GridFrameMotion motion;
} GridCell00488110;

typedef struct GridOwner00488110
{
    u8 unk00[0xC];
    s32 unk0C;
    s32 unk10;
    GridCell00488110* unk14;
    u8 unk18[4];
    GridBitset* unk1C;
    GridRowElement* unk20;
    u8 unk24[8];
    s32 unk2C;
    float unk30;
    u8 unk34[0x18];
    u8 unk4C;
    u8 unk4d[0xA];
    u8 skip_frame_playback;
    u8 unk58[0x48];
    GridFrameHeader* frame_header;
    GridFrameRecord* frame_records;
} GridOwner00488110;

/**
 * @brief Get a 0x90-byte cell's motion state at offset 0x60.
 * @param cell Cell to read.
 * @return The motion state, or null when the cell address is null.
 */
static inline GridFrameMotion* grid_cell_motion_00488110(GridCell00488110* cell)
{
    GridFrameMotion* motion = (GridFrameMotion*)cell;

    if (cell != 0)
    {
        motion = &cell->motion;
    }

    return motion;
}

#endif
