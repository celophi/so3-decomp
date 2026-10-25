#ifndef SO3_OVERLAYS_1067_00_GRID_FRAME_H
#define SO3_OVERLAYS_1067_00_GRID_FRAME_H

#include "types.h"
#include "overlays/1067-00/field_vector4.h"

/** A vector whose fourth word can hold a frame index. */
typedef union FieldGridFrameVector
{
    FieldQword packed;
    float floats[4];

    struct
    {
        float xyz[3];
        s32 frame_index;
    } components;
} FieldGridFrameVector;

/** Behavior when playback reaches the final frame. */
enum FieldGridFrameLoopMode
{
    FIELD_GRID_FRAME_WRAP = 0,
    FIELD_GRID_FRAME_PING_PONG = 1,
    FIELD_GRID_FRAME_HOLD_LAST = 2
};

/** Per-cell frame playback state. */
typedef struct FieldGridFrameState
{
    s32 reverse;
    s32 frame_index;
    float remaining_time;
    s32 boundary_count;
} FieldGridFrameState;

/** An animated vector, its rate, and the cell's frame playback state. */
typedef struct FieldGridFrameMotion
{
    FieldVector4 value;
    FieldVector4 rate;
    FieldGridFrameState frame;
} FieldGridFrameMotion;

/** Output record containing an updated vector and an optional frame index. */
typedef struct FieldGridOutputRecord
{
    u8 unk00[0x20];
    FieldGridFrameVector frame_vector;
} FieldGridOutputRecord;

#endif
