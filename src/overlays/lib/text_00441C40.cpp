#include "include_asm.h"
#include "overlays/lib/tracks.h"
#include "clamp.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/lib/particle_history.h"
#include "overlays/lib/particle_grid.h"
#include "overlays/lib/grid_frame_vu0.h"
#include "overlays/lib/text_004CD3A0.h"
#include "vu0.h"
#include "ee.h"
#include "overlays/lib/blend_transform.h"
#include "overlays/lib/model.h"
#include "main/resident_data.h"
#include "overlays/lib/text_004DD440.h"
#include "overlays/lib/text_0043A920.h"
#include "overlays/lib/vector.h"

extern LibTrackPool<LibPooledQuaternionCurveTrack>* g_quaternion_curve_track_pool;

/**
 * @brief Mark a track's g_quaternion_curve_track_pool slot as free.
 * @param pool Pool that owns the track.
 * @param track Track to release.
 */
void quaternion_curve_track_pool_free(LibTrackPool<LibPooledQuaternionCurveTrack>* pool, LibPooledQuaternionCurveTrack* track);

/**
 * @brief Subtract all four components of one rotation from another.
 * @param left Rotation to subtract from.
 * @param right Rotation to subtract.
 * @return left minus right.
 */
static inline FieldVec4B quaternion_difference(const FieldVec4B& left, const FieldVec4B& right)
{
    FieldVec4B value;
    value.x = left.x - right.x;
    value.y = left.y - right.y;
    value.z = left.z - right.z;
    value.w = left.w - right.w;
    return value;
}

/**
 * @brief Scale all four components of a rotation.
 * @param scale Factor to multiply by.
 * @param vector Rotation to scale.
 * @return The scaled rotation.
 */
static inline FieldVec4B quaternion_scaled(float scale, const FieldVec4B& vector)
{
    FieldVec4B value;
    value.x = vector.x * scale;
    value.y = vector.y * scale;
    value.z = vector.z * scale;
    value.w = vector.w * scale;
    return value;
}

/**
 * @brief Return a vector, or a zeroed fallback when it is missing.
 * @param vector Optional vector.
 * @param zero Storage for the zero vector.
 * @return The vector, or zero after clearing it.
 */
static inline const FieldVec4A* track_vector(const FieldVec4A* vector, FieldVec4A* zero)
{
    if (!vector)
    {
        zero->x = 0.0f;
        zero->y = 0.0f;
        zero->z = 0.0f;
        zero->w = 0.0f;
        return zero;
    }

    return vector;
}

/** Blend mode a fading model draws with. */
#define LIB_BLEND_MODE_FADE 2


typedef struct ConstantByteSetterOwnertext_0043A920
{
    u8 unk00[0x60];
    u8 unk60;
} ConstantByteSetterOwnertext_0043A920;

typedef struct WordNonzeroOwnertext_0043A920
{
    u8 unk00[0x14];
    u32 unk14;
} WordNonzeroOwnertext_0043A920;

typedef struct ByteClearOwnertext_0043A920
{
    u8 unk00[0x480];
    u8 unk480;
} ByteClearOwnertext_0043A920;

typedef struct HalfwordGetterOwnertext_0043A920
{
    u8 unk00[0x48];
    s16 unk48;
    s16 unk4a;
} HalfwordGetterOwnertext_0043A920;

typedef struct ByteGetterOwnertext_0043A920
{
    u8 unk00[0x4D];
    u8 unk4d;
    u8 unk4e[0x8];
    u8 unk56;
} ByteGetterOwnertext_0043A920;

typedef struct ByteSetterOwnertext_0043A920
{
    u8 unk00[0x4D];
    u8 unk4d;
    u8 unk4e;
    u8 unk4f;
    u8 unk50[0x4];
    u8 unk54;
    u8 unk55;
    u8 unk56;
} ByteSetterOwnertext_0043A920;

typedef struct WordSetterOwnertext_0043A920
{
    u8 unk00[0x48];
    u32 unk48;
    u8 unk4c[0x4];
    u32 unk50;
    u8 unk54[0x64];
    u32 unkb8;
    u32 unkbc;
} WordSetterOwnertext_0043A920;

typedef struct WordGetterOwnertext_0043A920
{
    u8 unk00[0x4];
    u32 unk04;
    u8 unk08[0x4];
    u32 unk0c;
    u32 unk10;
    u8 unk14[0x8];
    u32 unk1c;
    u8 unk20[0x20];
    u32 unk40;
    u8 unk44[0x4];
    u32 unk48;
    u8 unk4c[0x4];
    u32 unk50;
    u8 unk54[0x64];
    u32 unkb8;
    u32 unkbc;
} WordGetterOwnertext_0043A920;

typedef struct LibFloatFieldOwner0043A920
{
    u8 unk00[0x28];
    float unk28;
    u8 unk2c[4];
    float unk30;
    float unk34;
    float unk38;
    float unk3c;
    float unk40;
    float unk44;
} LibFloatFieldOwner0043A920;

typedef struct QuadwordSetter230Ownertext_0043A920 { u8 unk00[0x230]; unsigned __int128 value230; u8 unk240[0x241]; u8 flag481; } QuadwordSetter230Ownertext_0043A920;

typedef struct QuadwordSetter250Ownertext_0043A920 { u8 unk00[0x250]; unsigned __int128 value250; u8 unk260[0x222]; u8 flag482; } QuadwordSetter250Ownertext_0043A920;

typedef struct QuadwordSetter2B0Ownertext_0043A920 { u8 unk00[0x2B0]; unsigned __int128 value2B0; u8 unk2C0[0x1C5]; u8 flag485; } QuadwordSetter2B0Ownertext_0043A920;

typedef struct FourWordClearOwnertext_0043A920 { u32 words[4]; } FourWordClearOwnertext_0043A920;

typedef struct FlagFloat340Ownertext_0043A920 { u8 pad00[0x340]; float xy[2]; u8 pad348[0x8]; float zw[2]; u8 pad358[0x132]; u8 flag48A; } FlagFloat340Ownertext_0043A920;

typedef struct FlagFloat300Ownertext_0043A920 { u8 pad00[0x300]; float xy[2]; u8 pad308[0x8]; float zw[2]; u8 pad318[0x170]; u8 flag488; } FlagFloat300Ownertext_0043A920;

typedef struct FlagFloat2C0Ownertext_0043A920 { u8 pad00[0x2C0]; float xy[2]; u8 pad2C8[0x8]; float zw[2]; u8 pad2D8[0x1AE]; u8 flag486; } FlagFloat2C0Ownertext_0043A920;

typedef struct FlagFloat230Receivertext_0043A920 { u8 pad00[0x230]; float x230; u8 pad234[4]; float z238; u8 pad23C[4]; float y240; u8 pad244[0x23D]; u8 flag481; } FlagFloat230Receivertext_0043A920;

typedef struct FlagFloat220Receivertext_0043A920 { u8 pad00[0x220]; float x220; float y224; u8 pad228[0x1D0]; float z3F8; u8 pad3FC[0x84]; u8 flag480; } FlagFloat220Receivertext_0043A920;

typedef struct ClearFlagQuadwordOwnertext_0043A920 { u8 pad00[0x3A0]; unsigned __int128 value3A0; u8 pad3B0[0xDF]; u8 flag48F; } ClearFlagQuadwordOwnertext_0043A920;

typedef struct ClearFlagSlot3A0Ownertext_0043A920 { u8 pad00[0x3A0]; unsigned __int128 value3A0; u8 pad3B0[0xDF]; u8 flag48F; } ClearFlagSlot3A0Ownertext_0043A920;

typedef struct ClearFlagSlot380Ownertext_0043A920 { u8 pad00[0x380]; unsigned __int128 value380; u8 pad390[0xFE]; u8 flag48E; } ClearFlagSlot380Ownertext_0043A920;

typedef struct ClearFlagSlot360Ownertext_0043A920 { u8 pad00[0x360]; unsigned __int128 value360; u8 pad370[0x11B]; u8 flag48B; } ClearFlagSlot360Ownertext_0043A920;

typedef struct ClearFlagSlot320Ownertext_0043A920 { u8 pad00[0x320]; unsigned __int128 value320; u8 pad330[0x159]; u8 flag489; } ClearFlagSlot320Ownertext_0043A920;

typedef struct ClearFlagSlot2E0Ownertext_0043A920 { u8 pad00[0x2E0]; unsigned __int128 value2E0; u8 pad2F0[0x197]; u8 flag487; } ClearFlagSlot2E0Ownertext_0043A920;

typedef struct ClearFlagSlot2B0Ownertext_0043A920 { u8 pad00[0x2B0]; unsigned __int128 value2B0; u8 pad2C0[0x1C5]; u8 flag485; } ClearFlagSlot2B0Ownertext_0043A920;

typedef struct ClearFlagSlot290Ownertext_0043A920 { u8 pad00[0x290]; unsigned __int128 value290; u8 pad2A0[0x1E4]; u8 flag484; } ClearFlagSlot290Ownertext_0043A920;

typedef struct ClearFlagSlot270Ownertext_0043A920 { u8 pad00[0x270]; unsigned __int128 value270; u8 pad280[0x203]; u8 flag483; } ClearFlagSlot270Ownertext_0043A920;

typedef struct ClearFlagSlot250Ownertext_0043A920 { u8 pad00[0x250]; unsigned __int128 value250; u8 pad260[0x222]; u8 flag482; } ClearFlagSlot250Ownertext_0043A920;

typedef struct ClearFlagSlot230Ownertext_0043A920 { u8 pad00[0x230]; unsigned __int128 value230; u8 pad240[0x241]; u8 flag481; } ClearFlagSlot230Ownertext_0043A920;

typedef struct TwoQuadwordFlag3A0Ownertext_0043A920 { u8 pad00[0x3A0]; unsigned __int128 values[2]; u8 pad3C0[0xCF]; u8 flag48F; } TwoQuadwordFlag3A0Ownertext_0043A920;

typedef struct TwoQuadwordFlag380Ownertext_0043A920 { u8 pad00[0x380]; unsigned __int128 values[2]; u8 pad3A0[0xEE]; u8 flag48E; } TwoQuadwordFlag380Ownertext_0043A920;

typedef struct TwoQuadwordFlag360Ownertext_0043A920 { u8 pad00[0x360]; unsigned __int128 values[2]; u8 pad380[0x10B]; u8 flag48B; } TwoQuadwordFlag360Ownertext_0043A920;

typedef struct TwoQuadwordFlag320Ownertext_0043A920 { u8 pad00[0x320]; unsigned __int128 values[2]; u8 pad340[0x149]; u8 flag489; } TwoQuadwordFlag320Ownertext_0043A920;

typedef struct TwoQuadwordFlag2E0Ownertext_0043A920 { u8 pad00[0x2E0]; unsigned __int128 values[2]; u8 pad300[0x187]; u8 flag487; } TwoQuadwordFlag2E0Ownertext_0043A920;

typedef struct TwoQuadwordFlag290Ownertext_0043A920 { u8 pad00[0x290]; unsigned __int128 values[2]; u8 pad2B0[0x1D4]; u8 flag484; } TwoQuadwordFlag290Ownertext_0043A920;

typedef struct TwoQuadwordFlag270Ownertext_0043A920 { u8 pad00[0x270]; unsigned __int128 values[2]; u8 pad290[0x1F3]; u8 flag483; } TwoQuadwordFlag270Ownertext_0043A920;

typedef struct TwoQuadwordFlag250Ownertext_0043A920 { u8 pad00[0x250]; unsigned __int128 values[2]; u8 pad270[0x212]; u8 flag482; } TwoQuadwordFlag250Ownertext_0043A920;

typedef struct TwoQuadwordFlag230Ownertext_0043A920 { u8 pad00[0x230]; unsigned __int128 values[2]; u8 pad250[0x231]; u8 flag481; } TwoQuadwordFlag230Ownertext_0043A920;

typedef struct ByteSourceStateOwnertext_0043A920 { u8 pad00[0x57]; u8 state57; u8 pad58[0x48]; const u8* sourceA0; u32 valueA4; } ByteSourceStateOwnertext_0043A920;

typedef struct TwoWordClearArgStateOwnertext_0043A920 { u8 pad00[0x57]; u8 state57; u8 pad58[0x48]; void* unkA0; void* unkA4; } TwoWordClearArgStateOwnertext_0043A920;

typedef struct FourQuadwordCopyTargetOwnertext_0043A920
{
    u8 pad00[0x2C];
    u32 unk2C;
    u8 pad30[0x30];
    unsigned __int128 values60[4];
} FourQuadwordCopyTargetOwnertext_0043A920;

typedef struct FourQuadwordCopySourceOwnertext_0043A920
{
    u8 pad00[0x150];
    unsigned __int128 values150[4];
} FourQuadwordCopySourceOwnertext_0043A920;

typedef struct FieldVec4CopySource_00441C40
{
    u8 unk00[0x80];
    FieldVec4A unk80;
} FieldVec4CopySource_00441C40;

typedef struct TwoIndexTableEntryOwnertext_0043A920
{
    u8 data[0x40];
} TwoIndexTableEntryOwnertext_0043A920;

typedef struct TwoIndexTableAddressOwnertext_0043A920
{
    u8 pad00[0x10];
    s32 count;
    u8 pad14[0xC];
    TwoIndexTableEntryOwnertext_0043A920* entries;
} TwoIndexTableAddressOwnertext_0043A920;

typedef struct SingleIndexTableAddressOwnertext_0043A920
{
    u8 pad00[0x14];
    u8* base14;
} SingleIndexTableAddressOwnertext_0043A920;

typedef struct PackedModePair
{
    u8 lowMode : 4;
    u8 highMode : 4;
    u8 hasModeFour : 1;
    u8 unk01_1_7 : 7;
} PackedModePair;

typedef struct PackedModesOwner
{
    u8 unk00[0x52];
    PackedModePair at52;
} PackedModesOwner;

typedef struct FloatKeyScanEntry_text_0043A920_30
{
    float key00;
    u8 unk04[0x8];
    float key0c;
    u8 unk10[0x20];
} FloatKeyScanEntry_text_0043A920_30;

typedef struct FloatKeyScanOwner_text_0043A920_30
{
    u8 unk00[0x4];
    FloatKeyScanEntry_text_0043A920_30* entries;
    u8 unk08[0x40];
    s16 count48;
} FloatKeyScanOwner_text_0043A920_30;

typedef struct MappedEntry0043D240
{
    u8 unk00[0x30];
} MappedEntry0043D240;

typedef struct MappedOwner0043D240
{
    u8 unk00[0x14];
    MappedEntry0043D240* entries;
} MappedOwner0043D240;


/**
 * @brief Copy selected group histories and extend the caller's VU0 bounds.
 * @param object Receiver containing selection masks, source records, and histories.
 * @param capacity Output-record count at which processing stops before the next group.
 * @param output Destination array of three-vector records.
 * @param stamp Nonzero to copy the receiver's raw word at 0x28 into control records.
 */
void func_00441C40(LibHistoryReceiver441C40* object, s32 capacity, LibHistoryOutput30* output, u32 stamp)
{
    s32 samples = object->samples;
    s32 index = object->index;
    s32 limit = object->limit;
    const u64* masks = object->mask->bits;
    u64 bit = (u64)1 << (index & 63);
    s32 mask_index = index / 64;
    s32 processed = 0;
    u64 mask = masks[mask_index++];
    switch (object->policy)
    {
        case 0:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource170* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource170* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource170* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource170* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource170* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource170* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource170* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource170* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
        case 1:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource170* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource170* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource170* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource170* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource170* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource170* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource170* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource170* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
        case 2:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            LibHistorySource170* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            LibHistorySource170* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            LibHistorySource170* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            LibHistorySource170* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            LibHistorySource170* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            LibHistorySource170* source = &object->source[index - 1];
                            s32 history_index = index * (samples - 1) - 1;
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            LibHistorySource170* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            LibHistorySource170* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_004447B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_004447E0);

/**
 * @brief Fill a row of secondary elements from a cell, or from an explicit vector.
 * @param object Grid owning the row.
 * @param cell Cell whose vectors are copied.
 * @param row First secondary element of the row.
 * @param index Unused.
 * @param source Vector copied to each element, or null to use the cell's position.
 */
void func_00444BF0(LibGridEmitter* object, LibGridElement40* cell, LibGridRow40* row, s32 index, const LibGridVector4* source)
{
    if (object->unk50 != 0)
    {
        cell->unk3C = object->unk3C;
    }

    bool blend = false;

    if (object->unk4D != 1 && object->unk4D != 3)
    {
        blend = true;
    }

    s32 count = object->columns - 1;

    if (source == 0)
    {
        for (s32 i = 0; i < count; i++)
        {
            row->unk10 = cell->position();

            if (blend)
            {
                row->unk20 = cell->unk20;
            }

            row->unk30.packed = 0;
            row++;
        }
    }
    else
    {
        for (s32 i = 0; i < count; i++)
        {
            row->unk10 = *source;

            if (blend)
            {
                row->unk20 = cell->unk20;
            }

            row->unk30.packed = 0;
            row++;
        }
    }
}

/**
 * @brief Store the value at receiver offset 0x28.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_00444CF0(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    receiver->unk28 = value;
}

/**
 * @brief Store the value at receiver offset 0x30.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_00444D00(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    receiver->unk30 = value;
}

/** Return the float member at receiver offset 0x30. */
float func_00444D10(void* object)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    return receiver->unk30;
}

/** Store the byte at receiver offset 0x4D. */
void func_00444D20(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = (ByteSetterOwnertext_0043A920*)object;
    receiver->unk4d = value;
}

/** Return the unsigned byte at receiver offset 0x4D. */
u8 func_00444D30(const void* object)
{
    const ByteGetterOwnertext_0043A920* receiver = (const ByteGetterOwnertext_0043A920*)object;
    return receiver->unk4d;
}

/**
 * @brief Store the value at receiver offset 0x34.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_00444D40(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    receiver->unk34 = value;
}

/** Store the byte at receiver offset 0x56. */
void func_00444D50(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = (ByteSetterOwnertext_0043A920*)object;
    receiver->unk56 = value;
}

/** Return the unsigned byte at receiver offset 0x56. */
u8 func_00444D60(const void* object)
{
    const ByteGetterOwnertext_0043A920* receiver = (const ByteGetterOwnertext_0043A920*)object;
    return receiver->unk56;
}

/**
 * @brief Store the value at receiver offset 0x44.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_00444D70(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    receiver->unk44 = value;
}

/** Return the float member at receiver offset 0x44. */
float func_00444D80(void* object)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    return receiver->unk44;
}

/** Return the float member at receiver offset 0x28. */
float func_00444D90(void* object)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    return receiver->unk28;
}

/** Store the word at receiver offset 0x48. */
void func_00444DA0(void* object, u32 value)
{
    WordSetterOwnertext_0043A920* receiver = (WordSetterOwnertext_0043A920*)object;
    receiver->unk48 = value;
}

/** Return the word at receiver offset 0x48. */
u32 func_00444DB0(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = (const WordGetterOwnertext_0043A920*)object;
    return receiver->unk48;
}

/** Store the byte at receiver offset 0x4F. */
void func_00444DC0(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = (ByteSetterOwnertext_0043A920*)object;
    receiver->unk4f = value;
}

/** Store the byte at receiver offset 0x4E. */
void func_00444DD0(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = (ByteSetterOwnertext_0043A920*)object;
    receiver->unk4e = value;
}

/** Store the word at receiver offset 0x50. */
void func_00444DE0(void* object, u32 value)
{
    WordSetterOwnertext_0043A920* receiver = (WordSetterOwnertext_0043A920*)object;
    receiver->unk50 = value;
}

/** Return the word at receiver offset 0x50. */
u32 func_00444DF0(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = (const WordGetterOwnertext_0043A920*)object;
    return receiver->unk50;
}

/** Store the byte at receiver offset 0x55. */
void func_00444E00(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = (ByteSetterOwnertext_0043A920*)object;
    receiver->unk55 = value;
}

/**
 * @brief Store the value at receiver offset 0x3C.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_00444E10(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    receiver->unk3c = value;
}

/** Store the byte at receiver offset 0x54. */
void func_00444E20(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = (ByteSetterOwnertext_0043A920*)object;
    receiver->unk54 = value;
}

/**
 * @brief Store the value at receiver offset 0x40.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_00444E30(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    receiver->unk40 = value;
}

void func_00444E40(void* object, const u8* source, u32 value)
{
    ByteSourceStateOwnertext_0043A920* receiver = (ByteSourceStateOwnertext_0043A920*)object;
    receiver->sourceA0 = (const u8*)source;
    receiver->valueA4 = value;
    if (*receiver->sourceA0 == 1)
    {
        receiver->state57 = 1;
    }
    else
    {
        receiver->state57 = 0;
    }
}

void func_00444E80(void* object, s32 enabled)
{
    TwoWordClearArgStateOwnertext_0043A920* receiver = (TwoWordClearArgStateOwnertext_0043A920*)object;
    receiver->unkA0 = 0;
    receiver->unkA4 = 0;
    if (enabled)
    {
        receiver->state57 = 1;
    }
    else
    {
        receiver->state57 = 0;
    }
}

/**
 * @brief Store the value at receiver offset 0x38.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_00444EB0(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    receiver->unk38 = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_00444EC0);

void* func_00444EE0(void* object, s32 row, s32 column)
{
    TwoIndexTableAddressOwnertext_0043A920* receiver = (TwoIndexTableAddressOwnertext_0043A920*)object;
    return &receiver->entries[row * (receiver->count - 1) + column];
}

/** Return the word at receiver offset 0x1C. */
u32 func_00444F00(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = (const WordGetterOwnertext_0043A920*)object;
    return receiver->unk1c;
}

/** Return the word at receiver offset 0xC. */
u32 func_00444F10(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = (const WordGetterOwnertext_0043A920*)object;
    return receiver->unk0c;
}

/** Return the word at receiver offset 0x10. */
u32 func_00444F20(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = (const WordGetterOwnertext_0043A920*)object;
    return receiver->unk10;
}

s32 func_00444F30(void* object)
{
    return 63;
}

s32 func_00444F40(void* receiver)
{
    WordNonzeroOwnertext_0043A920* object = (WordNonzeroOwnertext_0043A920*)receiver;
    return object->unk14 != 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_00444F50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_004454B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_00445520);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_004455D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_00445670);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_00445700);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_00445780);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_00445840);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_00445950);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_00446EA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_00446F90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_00447030);

/**
 * @brief Copy another grid's size and settings, reallocating this grid to match.
 *
 * LibClass174050's copy_settings (vtable slot 0xB4).
 * @param object Grid to update.
 * @param other Grid to copy.
 */
void func_00447090(LibGridEmitter* object, const LibGridEmitter* other)
{
    object->cell_count = other->cell_count;
    object->columns = other->columns;
    object->resize(object->cell_count, object->columns);
    object->unk28 = other->unk28;
    object->unk30 = other->unk30;
    object->unk34 = other->unk34;
    object->unk38 = other->unk38;
    object->unk48 = other->unk48;
    object->unk4C = other->unk4C;
    object->unk4D = other->unk4D;
    object->unk4E = other->unk4E;
    object->unk4F = other->unk4F;
    object->unk50 = other->unk50;
    object->unk54 = other->unk54;
    object->unk55 = other->unk55;
    object->unk3C = other->unk3C;
    object->frame_header = other->frame_header;
    object->frame_records = other->frame_records;
}

void func_00447160(void* object, const void* source)
{
    FourQuadwordCopyTargetOwnertext_0043A920* receiver = (FourQuadwordCopyTargetOwnertext_0043A920*)object;
    const FourQuadwordCopySourceOwnertext_0043A920* values = (const FourQuadwordCopySourceOwnertext_0043A920*)source;
    receiver->unk2C = 0;
    receiver->values60[0] = values->values150[0];
    receiver->values60[1] = values->values150[1];
    receiver->values60[2] = values->values150[2];
    receiver->values60[3] = values->values150[3];
}

void func_00447190(void* object)
{
}

s32 func_004471A0(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_004471B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_00447330);

/**
 * @brief Clear an active cell bit.
 * @param object Bit set owning the storage.
 * @param index Unsigned cell index.
 */
static inline void lib_clear_grid_cell_bit(LibGridBitset* object, u32 index)
{
    u32 word_index = index >> 6;
    u64 keep_mask = ~((u64)1 << (index & 63));
    object->bits[word_index] &= keep_mask;
}

/**
 * @brief Advance active cells' frame vectors and playback state into an output batch.
 * @param object Grid owning the cells and frame resource.
 * @param capacity Output-entry budget, counted in steps of the grid column count.
 * @param output Output records, with each cell written at the start of its row.
 * @param preserve_row_vector Nonzero to retain the saved xyz components in the first secondary element.
 */
void func_00447500(LibGridReceiver447500* object, s32 capacity, LibGridOutputRecord* output, s32 preserve_row_vector)
{
    s32 columns = object->columns;
    s32 index = object->index;
    s32 cells = object->cell_count;
    u64* words = object->active->bits;
    u64 mask = (u64)1 << (index & 63);
    s32 word_index = index / 64;
    u64 active_word = words[word_index++];

    if (object->skip_frame_playback != 0)
    {
        s32 consumed = 0;
        vu0_set_grid_frame_delta(g_frame_seconds);

        if (columns == 1)
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                mask <<= 1;

                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }

                if (active == 0)
                {
                    index++;
                    continue;
                }

                LibGridFrameMotion* state = &object->cells[index];

                vu0_load_grid_frame_vectors(&state->value, &state->rate);
                index++;
                ee_prefetch(&object->cells[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
        else
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                mask <<= 1;

                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }

                if (active == 0)
                {
                    index++;
                    continue;
                }

                LibGridFrameMotion* state = &object->cells[index];

                LibGridFrameVector* previous = &object->rows[index * (columns - 1)].unk30;

                if (preserve_row_vector == 0)
                {
                    previous->packed = state->value.packed;
                }

                vu0_load_grid_frame_vectors(&state->value, &state->rate);
                previous->components.frame_index = 0;
                index++;
                ee_prefetch(&object->cells[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
    }
    else
    {
        s32 consumed = 0;
        s32 frame_count = object->frame_header->frame_count;
        s32 loop_mode = object->frame_header->loop_mode;
        s32 boundary_limit = (s32)object->unk30;
        float frame_seconds = 1.0f / 60.0f;
        vu0_set_grid_frame_delta(g_frame_seconds);

        if (columns == 1)
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                mask <<= 1;

                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }

                if (active == 0)
                {
                    index++;
                    continue;
                }

                LibGridFrameMotion* state = &object->cells[index];

                LibGridFrameState* frame = &state->frame;

                if (object->unk4C == 4 && boundary_limit < frame->boundary_count)
                {
                    lib_clear_grid_cell_bit(object->active, index);
                    index++;
                    continue;
                }

                frame->remaining_time -= g_frame_seconds;

                s32 frame_index = frame->frame_index;
                vu0_load_grid_frame_vectors(&state->value, &state->rate);

                while (frame->remaining_time <= 0.0f)
                {
                    frame_index += frame->reverse != 0 ? -1 : 1;

                    if (frame_index >= frame_count)
                    {
                        switch (loop_mode)
                        {
                        case LIB_GRID_FRAME_WRAP:
                            frame_index = 0;
                            break;
                        case LIB_GRID_FRAME_PING_PONG:
                            frame->reverse = 1;
                            frame_index--;
                            break;
                        case LIB_GRID_FRAME_HOLD_LAST:
                            frame_index--;
                            break;
                        }

                        frame->boundary_count++;
                    }
                    else if (frame_index < 0)
                    {
                        frame->reverse = 0;
                        frame_index = 0;
                        frame->boundary_count++;
                    }

                    frame->frame_index = frame_index;
                    frame->remaining_time += frame_seconds * object->frame_records[frame_index].duration_frames;
                }

                index++;
                ee_prefetch(&object->cells[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                output->frame_vector.components.frame_index = frame_index;
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
        else
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                mask <<= 1;

                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }

                if (active == 0)
                {
                    index++;
                    continue;
                }

                LibGridFrameMotion* state = &object->cells[index];

                LibGridFrameState* frame = &state->frame;

                if (object->unk4C == 4 && boundary_limit < frame->boundary_count)
                {
                    lib_clear_grid_cell_bit(object->active, index);
                    index++;
                    continue;
                }

                frame->remaining_time -= g_frame_seconds;

                s32 frame_index = frame->frame_index;
                LibGridFrameVector* previous = &object->rows[index * (columns - 1)].unk30;

                if (preserve_row_vector == 0)
                {
                    previous->packed = state->value.packed;
                }
                previous->components.frame_index = frame_index;
                vu0_load_grid_frame_vectors(&state->value, &state->rate);

                while (frame->remaining_time <= 0.0f)
                {
                    frame_index += frame->reverse != 0 ? -1 : 1;

                    if (frame_index >= frame_count)
                    {
                        switch (loop_mode)
                        {
                        case LIB_GRID_FRAME_WRAP:
                            frame_index = 0;
                            break;
                        case LIB_GRID_FRAME_PING_PONG:
                            frame->reverse = 1;
                            frame_index--;
                            break;
                        case LIB_GRID_FRAME_HOLD_LAST:
                            frame_index--;
                            break;
                        }

                        frame->boundary_count++;
                    }
                    else if (frame_index < 0)
                    {
                        frame->reverse = 0;
                        frame_index = 0;
                        frame->boundary_count++;
                    }

                    frame->frame_index = frame_index;
                    frame->remaining_time += frame_seconds * object->frame_records[frame_index].duration_frames;
                }

                index++;
                ee_prefetch(&object->cells[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                output->frame_vector.components.frame_index = frame_index;
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
    }
}

void func_00447C60(void* object)
{
}

s32 func_00447C70(void* object)
{
    return 0;
}

void func_00447C80(void* object)
{
}

s32 func_00447C90(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_00447CA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_00447D80);

float func_00447DC0(void* object)
{
    return 1.0f;
}

/**
 * @brief Turn fogging on or off.
 * @param enabled Nonzero for fog.
 */
void LibColorModel::set_fog_enabled(u8 enabled)
{
    fog_enabled = enabled;
}

/** @brief Set the inherited state byte to two when blending is enabled. */
void LibBlendTransform::set_default_draw_bucket()
{
    draw_bucket = blend_mode ? 2 : 0;
}

/**
 * @brief Fade the model near the camera. Below one it blends with the value as alpha, otherwise opaque.
 * @param value Distance in front of the camera over the fade range, clamped to one.
 * @param mode Two from Lib's caller; unused here.
 * @return Whether the value is negative.
 */
s32 LibColorModel::set_fade_alpha(float value, float mode)
{
    LibVector4 modulation;

    if (value < 0.0f)
    {
        return 1;
    }

    if (value < 1.0f)
    {
        set_blend_mode(LIB_BLEND_MODE_FADE);
        copy_vector(&modulation, &color_modulation);
        modulation.w = value;
        copy_vector(&color_modulation, &modulation);
        update_combined_color_factor();
    }
    else
    {
        set_blend_mode(0);
        copy_vector(&modulation, &color_modulation);
        modulation.w = 1.0f;
        copy_vector(&color_modulation, &modulation);
        update_combined_color_factor();
    }

    return 0;
}

/** @brief Unlink this copy from its original's copies and queue it for release. */
void LibColorModel::release_clone()
{
    LibColorModel* node = original;

    if (node == 0)
    {
        return;
    }

    LibColorModel* previous = 0;

    for (;;)
    {
        LibColorModel* next = node->next_clone;

        if (next == 0)
        {
            break;
        }

        if (next == this)
        {
            previous = node;
            break;
        }

        node = next;
    }

    if (previous != 0)
    {
        previous->next_clone = next_clone;
    }

    original = 0;
    next_clone = 0;
    resident_enqueue_object(g_resident_release_queues, this);
}

/**
 * @brief Link a copy to this model as the last of its clones.
 * @param copy Copy to link.
 */
void LibColorModel::add_clone(LibColorModel* copy)
{
    copy->original = this;
    LibColorModel* node = this;

    for (;;)
    {
        LibColorModel* next = node->next_clone;

        if (next == 0)
        {
            node->next_clone = copy;
            break;
        }

        node = next;
    }
}

/**
 * @brief Update the transform. A clone takes its original's color state and its layer's display manager, and a
 * model with LIB_DRAW_FOLLOW_CAMERA follows the camera across the ground.
 */
void LibColorModel::update()
{
    LibTransform::update();
    LibColorModel* source = original;

    if (source != 0)
    {
        light_mask = source->light_mask;
        set_fog_enabled(source->fog_enabled);
        unk59d_1 = source->unk59d_1;
        unk59c = source->unk59c;
        unk59d_0 = 1;
        copy_vector(&base_color_factor, &source->base_color_factor);
        copy_vector(&color_modulation, &source->color_modulation);
        copy_vector(&combined_color_factor, &source->combined_color_factor);
        set_blend_mode(source->blend_mode);
        LibTransform::copy_offset_transform_state(source);
        display_manager = reinterpret_cast<LibSceneLayerTable*>(owner)->get_display_manager(layer);
    }

    if (draw_flags & LIB_DRAW_FLAG_0020)
    {
        if (func_004DA0F0(this) >= 0.5f)
        {
            draw_flags &= ~LIB_DRAW_FLAG_0040;
        }
        else
        {
            draw_flags |= LIB_DRAW_FLAG_0040;
        }
    }

    if (draw_flags & LIB_DRAW_FOLLOW_CAMERA)
    {
        LibCamera* camera;

        if (display_manager != 0)
        {
            camera = static_cast<LibCamera*>(display_manager->current_display);
        }
        else
        {
            camera = static_cast<LibCamera*>(g_display_manager->current_display);
        }

        if (camera != 0)
        {
            if (camera->matrix_ready == 0)
            {
                camera->update_transform_matrix();
            }

            const LibMatrix44Value* matrix = camera->get_transform_matrix();
            set_translation(matrix->m[0][3], translation.y, matrix->m[2][3]);
        }
    }
}

/**
 * @brief Copy another model's color state, blend mode and offset transform.
 * @param source Model to copy.
 */
void LibColorModel::copy_color_state(const LibColorModel* source)
{
    light_mask = source->light_mask;
    set_fog_enabled(source->fog_enabled);
    unk59d_1 = source->unk59d_1;
    unk59c = source->unk59c;
    unk59d_0 = 1;
    copy_vector(&base_color_factor, &source->base_color_factor);
    copy_vector(&color_modulation, &source->color_modulation);
    copy_vector(&combined_color_factor, &source->combined_color_factor);
    set_blend_mode(source->blend_mode);
    LibTransform::copy_offset_transform_state(source);
}

/** @brief Detach and destroy the model's clones, then detach and queue the model. */
void LibColorModel::destroy()
{
    if (next_clone != 0)
    {
        lib_object_detach_owner(next_clone);
        next_clone->destroy();
        next_clone = 0;
    }

    LibTransformOwner::destroy();
}

/** @brief Detach and delete the model's clones. */
LibColorModel::~LibColorModel()
{
    if (next_clone != 0)
    {
        lib_object_detach_owner(next_clone);
        delete next_clone;
        next_clone = 0;
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_00448360);

void* func_00448690(void* value)
{
    return value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_004486A0);

s32 func_00448900(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_00448910);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_00448A10);

/**
 * @brief Append a keyframe through append_curve_key, with a zero control rotation when none is given.
 * @param value Keyframe rotation.
 * @param in_tangent Control rotation, or null.
 * @param out_tangent Passed on unchanged.
 * @param key Sort key.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibPooledQuaternionCurveTrack::append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    FieldVec4A zero;
    in_tangent = track_vector(static_cast<const FieldVec4A*>(in_tangent), &zero);
    return append_curve_key(static_cast<const FieldVec4A*>(value), static_cast<const FieldVec4A*>(in_tangent), static_cast<const FieldVec4A*>(out_tangent), key);
}

/**
 * @brief Replace a keyframe through replace_curve_key, with a zero control rotation when none is given.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe rotation.
 * @param in_tangent Control rotation, or null.
 * @param out_tangent Passed on unchanged.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibPooledQuaternionCurveTrack::replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    FieldVec4A zero;
    in_tangent = track_vector(static_cast<const FieldVec4A*>(in_tangent), &zero);
    return replace_curve_key(index, key, static_cast<const FieldVec4A*>(value), static_cast<const FieldVec4A*>(in_tangent), static_cast<const FieldVec4A*>(out_tangent));
}

/**
 * @brief Insert a keyframe through insert_curve_key, with a zero control rotation when none is given.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe rotation.
 * @param in_tangent Control rotation, or null.
 * @param out_tangent Passed on unchanged.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibPooledQuaternionCurveTrack::insert_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    FieldVec4A zero;
    in_tangent = track_vector(static_cast<const FieldVec4A*>(in_tangent), &zero);
    return insert_curve_key(index, key, static_cast<const FieldVec4A*>(value), static_cast<const FieldVec4A*>(in_tangent), static_cast<const FieldVec4A*>(out_tangent));
}

/**
 * @brief Store a single keyframe through set_single_curve_key, with a zero control rotation when none is given.
 * @param value Keyframe rotation.
 * @param in_tangent Control rotation, or null.
 * @param out_tangent Passed on unchanged.
 * @param key Sort key.
 */
void LibPooledQuaternionCurveTrack::set_single_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    FieldVec4A zero;
    in_tangent = track_vector(static_cast<const FieldVec4A*>(in_tangent), &zero);
    set_single_curve_key(static_cast<const FieldVec4A*>(value), static_cast<const FieldVec4A*>(in_tangent), static_cast<const FieldVec4A*>(out_tangent), key);
}

/**
 * @brief Write how fast the rotation changed at the last sample, per second.
 * @param output Receives the rate.
 */
void LibPooledQuaternionCurveTrack::get_value_rate(void* output) const
{
    *static_cast<FieldVec4B*>(output) = value_rate;
}

/** @brief Return a pooled track to its pool, or delete an ordinary track. */
void LibPooledQuaternionCurveTrack::release()
{
    if (this != 0)
    {
        if (state.pooled)
        {
            free_keys();
            quaternion_curve_track_pool_free(g_quaternion_curve_track_pool, this);
        }
        else
        {
            delete this;
        }
    }
}

/** @brief Select the cycle end mode, then reset to a single zero keyframe at key zero. */
void LibPooledQuaternionCurveTrack::reset_keys()
{
    set_before_mode(LIB_TRACK_END_CYCLE);
    FieldVec4A zero(0.0f, 0.0f, 0.0f, 0.0f);
    set_single_key(&zero, &zero, &zero, 0.0f);
}

/** @brief Destroy the track. */
LibPooledQuaternionCurveTrack::~LibPooledQuaternionCurveTrack()
{
}

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param mode LIB_TRACK_END_* mode.
 */
void LibQuaternionCurveTrackBase::set_before_mode(u32 mode)
{
    state.before_mode = mode;
    state.extends_segment = state.before_mode == LIB_TRACK_END_EXTEND_SEGMENT || state.after_mode == LIB_TRACK_END_EXTEND_SEGMENT;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_00448E80);

/**
 * @brief Write the difference between the last and first key rotations, all four components.
 * @param output Receives the difference.
 */
void LibPooledQuaternionCurveTrack::get_end_delta(void* output) const
{
    const LibQuaternionCurveTrackKey* last = &key_array[state.key_count - 1];
    *static_cast<FieldVec4B*>(output) = quaternion_difference(last->value, key_array[0].value);
}

/**
 * @brief Store a single keyframe and its control rotation in the cached key, and use it before the first key.
 * @param value Keyframe rotation.
 * @param control Control rotation.
 * @param unused Unused.
 * @param key Sort key.
 */
void LibPooledQuaternionCurveTrack::set_single_curve_key(const FieldVec4A* value, const FieldVec4A* control, const FieldVec4A* unused, float key)
{
    set_before_mode(LIB_TRACK_END_USE_PRE_START_KEY);
    *reinterpret_cast<FieldVec4A*>(&single_key.value) = *value;
    *reinterpret_cast<FieldVec4A*>(&single_key.control) = *control;
    single_key.key = key;
}

/**
 * @brief Read an indexed keyframe.
 * @param index Keyframe index.
 * @param key Receives the sort key, or null.
 * @param value Receives the rotation, or null.
 * @param first Receives the control rotation, or null.
 * @param second Unused.
 * @return One when the index is within the capacity, otherwise zero.
 */
s32 LibPooledQuaternionCurveTrack::read_key(s32 index, float* key, void* value, void* first, void* second) const
{
    if (index >= state.key_capacity)
    {
        return 0;
    }

    if (key)
    {
        *key = key_array[index].key;
    }

    if (value)
    {
        *static_cast<FieldVec4B*>(value) = key_array[index].value;
    }

    if (first)
    {
        *static_cast<FieldVec4B*>(first) = key_array[index].control;
    }

    return 1;
}

// Every instruction matches; the two vector copies in the shift loop use each other's stack slots.
INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", insert_curve_key__29LibPooledQuaternionCurveTrackFifPC10FieldVec4APC10FieldVec4APC10FieldVec4A);

/**
 * @brief Replace an indexed keyframe and its control rotation.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe rotation.
 * @param control Control rotation.
 * @param unused Unused.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibPooledQuaternionCurveTrack::replace_curve_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* control, const FieldVec4A* unused)
{
    if (index >= state.key_capacity)
    {
        return 0;
    }

    key_array[index].value = *value;
    key_array[index].control = *control;
    key_array[index].key = key;

    if (index == state.key_count - 1)
    {
        state.span = key - key_array[0].key;
    }

    return 1;
}

/**
 * @brief Append a keyframe with its control rotation.
 * @param value Keyframe rotation.
 * @param control Control rotation.
 * @param unused Unused.
 * @param key Sort key.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibPooledQuaternionCurveTrack::append_curve_key(const FieldVec4A* value, const FieldVec4A* control, const FieldVec4A* unused, float key)
{
    if (state.key_count >= state.key_capacity)
    {
        return 0;
    }

    key_array[state.key_count].value = *value;
    key_array[state.key_count].control = *control;
    key_array[state.key_count].key = key;
    state.span = key - key_array[0].key;
    state.key_count++;
    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_004492D0);

/**
 * @brief Interpolate the track at a key and cache the rotation and its change per second.
 * @param key Evaluation key.
 * @return Rotation at the key.
 */
FieldVec4A LibPooledQuaternionCurveTrack::sample(float key)
{
    s32 lower;
    s32 upper;
    float wrapped_key;
    u8 extrapolate;
    FieldVec4B result;

    if (!key_array || !state.key_count)
    {
        return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    }

    if (state.search_index >= state.key_capacity)
    {
        state.search_index = 0;
    }

    if (state.key_count == 1 && (!(key < key_array[0].key) || state.before_mode != LIB_TRACK_END_USE_PRE_START_KEY))
    {
        return *reinterpret_cast<FieldVec4A*>(&key_array[0].value);
    }

    extrapolate = 0;

    if (key < key_array[0].key && state.before_mode == LIB_TRACK_END_USE_PRE_START_KEY)
    {
        upper = 0;
        wrapped_key = key;
        lower = -1;
    }
    else
    {
        wrapped_key = update_cycle_count(key);

        if (state.cycle_count != 0)
        {
            if (state.before_mode == LIB_TRACK_END_HOLD && state.cycle_count < 0)
            {
                return *reinterpret_cast<FieldVec4A*>(&key_array[0].value);
            }

            if (state.after_mode == LIB_TRACK_END_HOLD && state.cycle_count > 0)
            {
                return *reinterpret_cast<FieldVec4A*>(&key_array[state.key_count - 1].value);
            }
        }

        extrapolate = find_surrounding_keys(wrapped_key, &lower, &upper);

        if (extrapolate)
        {
            wrapped_key = key;
        }
    }

    if (!extrapolate)
    {
        LibQuaternionCurveTrackKey* first = lower >= 0 ? key_array + lower : &single_key;
        LibQuaternionCurveTrackKey* second;
        s32 last = state.key_count - 1;

        if (upper == last && ((!(key < key_array[0].key) && state.after_mode == LIB_TRACK_END_CYCLE_TO_FIRST) ||
            (key < key_array[0].key && state.before_mode == LIB_TRACK_END_CYCLE_TO_FIRST)))
        {
            second = key_array;
        }
        else if (lower < upper)
        {
            second = key_array + upper;
        }
        else
        {
            second = key_array + last;
        }

        func_004CCE10(&result, &first->value, &second->value, &first->control, &second->control, (wrapped_key - first->key) / (second->key - first->key));

        if (state.cycle_count != 0 && ((state.before_mode == LIB_TRACK_END_OFFSET_CYCLE && state.cycle_count < 0) ||
                                       (state.after_mode == LIB_TRACK_END_OFFSET_CYCLE && state.cycle_count > 0)))
        {
            FieldVec4B delta = quaternion_difference(key_array[state.key_count - 1].value, key_array[0].value);
            lib_quaternion_add_assign(result, quaternion_scaled((float)state.cycle_count, delta));
        }
    }
    else if (wrapped_key < key)
    {
        LibQuaternionCurveTrackKey* first = &key_array[state.key_count - 2];
        LibQuaternionCurveTrackKey* second = &key_array[state.key_count - 1];
        func_004CCE10(&result, &first->value, &second->value, &first->control, &second->control, (wrapped_key - first->key) / (second->key - first->key));
    }
    else
    {
        func_004CCE10(&result, &key_array[0].value, &key_array[1].value, &key_array[0].control, &key_array[1].control,
                      (wrapped_key - key_array[0].key) / (key_array[1].key - key_array[0].key));
    }

    last_key = key;
    value_rate = quaternion_scaled(g_inverse_frame_ticks, quaternion_difference(result, last_value));
    last_value = result;
    return *reinterpret_cast<FieldVec4A*>(&result);
}

struct ResetVector70_0043A920 { u8 pad[0x70]; FieldVec4B value; };

/** @brief Clear the last sampled rotation, then reset the key state. */
void LibPooledQuaternionCurveTrack::reset_state()
{
    last_value = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    LibQuaternionCurveTrackBase::reset_state();
}

/**
 * @brief Normalize a key across the cached span and store its signed period count.
 * @param key Key whose period count is representable as a signed 32-bit integer.
 * @return Normalized key, with odd-period reflection selected by the control fields.
 */
float LibQuaternionCurveTrackBase::update_cycle_count(float key)
{
    float first = static_cast<LibQuaternionCurveTrackKey*>(key_array)[0].key;
    float quotient = (key - first) / state.span;

    if (key < first)
    {
        quotient -= 1.0f;
    }

    state.cycle_count = quotient;

    if (state.cycle_count)
    {
        float result = key - (float)state.cycle_count * state.span;

        if ((state.before_mode == LIB_TRACK_END_PING_PONG && state.cycle_count < 0) || (state.after_mode == LIB_TRACK_END_PING_PONG && state.cycle_count > 0))
        {
            s32 last_index = state.key_count - 1;
            LibQuaternionCurveTrackKey* last_entry = static_cast<LibQuaternionCurveTrackKey*>(key_array) + last_index;
            float last = last_entry->key;

            if (state.cycle_count & 1)
            {
                result = first + (last - result);
            }
        }

        return result;
    }

    return key;
}

/**
 * @brief Find the entries around a key, starting from the cached cursor.
 * @param key Key to place.
 * @param lower Receives the lower entry index.
 * @param upper Receives the upper entry index.
 * @return One when the active end mode extends the first or last segment, otherwise zero.
 */
u8 LibQuaternionCurveTrackBase::find_surrounding_keys(float key, s32* lower, s32* upper)
{
    s32 index;
    s32 count;
    s32 next;

    if (state.extends_segment)
    {
        if (state.before_mode == LIB_TRACK_END_EXTEND_SEGMENT && state.cycle_count < 0)
        {
            *lower = 0;
            *upper = 1;
            state.search_index = 0;
            return 1;
        }

        if (state.after_mode == LIB_TRACK_END_EXTEND_SEGMENT && state.cycle_count > 0)
        {
            *lower = state.key_count - 2;
            *upper = state.key_count - 1;
            state.search_index = state.key_count - 2;
            return 1;
        }
    }

    index = state.search_index;
    count = state.key_count;

    while (index > 0 && key < static_cast<LibQuaternionCurveTrackKey*>(key_array)[index].key)
    {
        index--;
    }

    index = clamp_low(index, 0);

    while ((next = index + 1) < count && !(key < static_cast<LibQuaternionCurveTrackKey*>(key_array)[next].key))
    {
        index++;
    }

    if (index >= count - 1)
    {
        *lower = count - 2;
        *upper = count - 1;
    }
    else
    {
        *lower = index;
        *upper = index + 1;
    }

    state.search_index = index;
    return 0;
}

/** @brief Release the keyframe storage. */
LibQuaternionCurveTrackBase::~LibQuaternionCurveTrackBase()
{
    free_keys();
}

/**
 * @brief Reset 48-byte record storage, counts, packed controls, and cached indices.
 */
void LibQuaternionCurveTrackBase::reset_state()
{
    key_array = 0;
    state.before_mode = LIB_TRACK_END_CYCLE;
    state.after_mode = LIB_TRACK_END_CYCLE;
    state.key_capacity = 0;
    state.key_count = 0;
    state.search_index = -1;
    state.cycle_count = 0;
    state.segment_lower = -1;
    state.segment_upper = -1;
    state.extends_segment = 0;
    state.external_keys = 0;
}

/**
 * @brief Bind external 48-byte records and cache their first-to-last key span.
 * @param count Positive entry count representable in the receiver count fields.
 * @param keys External storage containing the specified number of entries.
 */
void LibQuaternionCurveTrackBase::bind_keys(s32 count, void* keys)
{
    s32 last_index = count - 1;
    LibQuaternionCurveTrackKey* last;
    state.external_keys = 1;
    key_array = static_cast<LibQuaternionCurveTrackKey*>(keys);
    state.key_capacity = count;
    state.key_count = count;
    last = key_array + last_index;
    state.span = last->key - key_array[0].key;
}

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param mode LIB_TRACK_END_* mode.
 */
void LibQuaternionCurveTrackBase::set_after_mode(u32 mode)
{
    state.after_mode = mode;
    state.extends_segment = state.before_mode == LIB_TRACK_END_EXTEND_SEGMENT || state.after_mode == LIB_TRACK_END_EXTEND_SEGMENT;
}

/**
 * @brief Return how many key spans the last wrapped key was past the first key.
 * @return Signed cycle count.
 */
s32 LibQuaternionCurveTrackBase::get_cycle_count() const
{
    return state.cycle_count;
}

/**
 * @brief Return the number of stored keys.
 * @return Key count.
 */
s16 LibQuaternionCurveTrackBase::get_key_count() const
{
    return state.key_count;
}

/**
 * @brief Return the number of keys the storage can hold.
 * @return Key capacity.
 */
s16 LibQuaternionCurveTrackBase::get_key_capacity()
{
    return state.key_capacity;
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 * @return Zero.
 */
s32 LibQuaternionCurveTrackBase::on_append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return 0;
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @return Zero.
 */
s32 LibQuaternionCurveTrackBase::on_replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return 0;
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @return Zero.
 */
s32 LibQuaternionCurveTrackBase::on_insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return 0;
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 */
void LibQuaternionCurveTrackBase::on_set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
}

/**
 * @brief Test whether the 48-byte record array contains an exactly equal key.
 * @param key Scalar key to find.
 * @return One for an equal key, or zero when none is present.
 */
s32 LibQuaternionCurveTrackBase::has_key(float key) const
{
    s16 count = state.key_count;
    s32 index;

    for (index = 0; index < count; index++)
    {
        if (key == key_array[index].key)
        {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Return a zero vector; the track's value when it has no keys.
 * @return Zero vector.
 */
FieldVec4A LibQuaternionCurveTrackBase::get_zero_value() const
{
    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Return the last-to-first key difference, or zero below two records.
 * @return Difference between the last and first scalar keys, or zero.
 */
float LibQuaternionCurveTrackBase::get_key_span() const
{
    s32 last_index;
    LibQuaternionCurveTrackKey* last_entry;

    if (state.key_count < 2)
    {
        return 0.0f;
    }

    last_index = state.key_count - 1;
    last_entry = key_array + last_index;
    return last_entry->key - key_array[0].key;
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void LibQuaternionCurveTrackBase::evaluate(float key, void* output)
{
    *static_cast<FieldVec4B*>(output) = sample(key);
}

/**
 * @brief Adjust a scalar key by whole spans determined from the endpoint records.
 * @param key Scalar key whose normalized span quotient must fit in a signed word.
 * @return Key minus the computed number of endpoint spans, or the key for zero spans.
 */
float LibQuaternionCurveTrackBase::wrap_key(float key) const
{
    s32 last_index = state.key_count - 1;
    LibQuaternionCurveTrackKey* entries = key_array;
    LibQuaternionCurveTrackKey* last = entries + last_index;
    float first = entries[0].key;
    float span = last->key - first;
    float quotient = (key - first) / span;
    s32 periods;

    if (quotient < 0.0f)
    {
        quotient -= 1.0f;
    }

    periods = quotient;

    if (periods != 0)
    {
        return key - (float)periods * span;
    }

    return key;
}

/**
 * @brief Return the key storage.
 * @return Key array, or null.
 */
void* LibQuaternionCurveTrackBase::get_keys()
{
    return key_array;
}

/** @brief Delete the key storage unless it is external, and clear the key pointer. */
void LibQuaternionCurveTrackBase::free_keys()
{
    if (!state.external_keys)
    {
        delete[] key_array;
    }

    key_array = 0;
}

/**
 * @brief Mark a track's g_quaternion_curve_track_pool slot as free.
 * @param pool Pool that owns the track.
 * @param track Track to release.
 */
void quaternion_curve_track_pool_free(LibTrackPool<LibPooledQuaternionCurveTrack>* pool, LibPooledQuaternionCurveTrack* track)
{
    pool->free(track);
}

/**
 * @brief Read the vector value associated with the first exactly equal key.
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A LibQuaternionCurveTrackBase::find_key_value(float key)
{
    s32 index;

    for (index = 0; index < state.key_count; index++)
    {
        if (key == key_array[index].key)
        {
            LibQuaternionCurveTrackKey* entry = key_array + index;
            return *reinterpret_cast<const FieldVec4A*>(&entry->value);
        }
    }

    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param count Requested keyframe count.
 */
void LibQuaternionCurveTrackBase::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] key_array;
    key_array = new (0) LibQuaternionCurveTrackKey[count];
    state.key_capacity = count;

    if (!key_array)
    {
        state.key_capacity = 0;
    }
}

/** @brief Leave the keyframe uninitialized. */
LibQuaternionCurveTrackKey::LibQuaternionCurveTrackKey()
{
}

/**
 * @brief Forward to slot 0x68.
 * @param value Key value.
 * @param in_tangent First auxiliary vector.
 * @param out_tangent Second auxiliary vector.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibQuaternionCurveTrackBase::append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    return on_append_key(static_cast<const FieldVec4A*>(value), static_cast<const FieldVec4A*>(in_tangent), static_cast<const FieldVec4A*>(out_tangent), key);
}

/**
 * @brief Forward to slot 0x6C.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param in_tangent First auxiliary vector.
 * @param out_tangent Second auxiliary vector.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibQuaternionCurveTrackBase::replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    return on_replace_key(index, key, static_cast<const FieldVec4A*>(value), static_cast<const FieldVec4A*>(in_tangent), static_cast<const FieldVec4A*>(out_tangent));
}

/**
 * @brief Forward to slot 0x70.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param in_tangent First auxiliary vector.
 * @param out_tangent Second auxiliary vector.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibQuaternionCurveTrackBase::insert_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    return on_insert_key(index, key, static_cast<const FieldVec4A*>(value), static_cast<const FieldVec4A*>(in_tangent), static_cast<const FieldVec4A*>(out_tangent));
}

/**
 * @brief Forward to slot 0x74.
 * @param value Key value.
 * @param in_tangent First auxiliary vector.
 * @param out_tangent Second auxiliary vector.
 * @param key Key the keyframe sits at.
 */
void LibQuaternionCurveTrackBase::set_single_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    on_set_single_key(static_cast<const FieldVec4A*>(value), static_cast<const FieldVec4A*>(in_tangent), static_cast<const FieldVec4A*>(out_tangent), key);
}

/** Store 0x8 at receiver offset 0x60. */
void func_0044A400(void* object)
{
    ConstantByteSetterOwnertext_0043A920* receiver = (ConstantByteSetterOwnertext_0043A920*)object;
    receiver->unk60 = 0x8;
}

/** Build a four-word stack value and return its address. */
void* func_0044A410(void)
{
    s32 stack[4];
    s32* result;
    stack[0] = 0;
    stack[3] = 0x7149F2CA;
    stack[1] = 0;
    result = stack;
    stack[2] = 0;
    return result;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_0044A440);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_0044A530);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_0044A5A0);

s32 func_0044A5E0(void* object)
{
    return 14;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00441C40", func_0044A5F0);
