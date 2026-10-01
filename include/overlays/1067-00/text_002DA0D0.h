#ifndef SO3_OVERLAYS_1067_00_TEXT_002DA0D0_H
#define SO3_OVERLAYS_1067_00_TEXT_002DA0D0_H

#include "types.h"
#include "overlays/1067-00/text_002D8410.h"
#include "overlays/1067-00/text_001DD3C0.h"

/** Partial view of the object whose bit 0 at offset 0x2C is a state flag. */
struct FieldFlag2DADD0
{
    u8 unk00[0x2C];
    u8 unk2c_0 : 1;
    u8 unk2c_1_7 : 7;
};

#ifdef __cplusplus
/** Four aligned 16-byte values copied individually. */
struct FieldQuad4DA0D0
{
    /** @brief Copy the four values in order. */
    FieldQuad4DA0D0(const FieldQuad4DA0D0& source)
    {
        data[0] = source.data[0];
        data[1] = source.data[1];
        data[2] = source.data[2];
        data[3] = source.data[3];
    }

    /** @brief Assign the four values in order. */
    FieldQuad4DA0D0& operator=(const FieldQuad4DA0D0& source)
    {
        data[0] = source.data[0];
        data[1] = source.data[1];
        data[2] = source.data[2];
        data[3] = source.data[3];
        return *this;
    }

    unsigned __int128 data[4];
} __attribute__((aligned(16)));

/** Source record with six FieldVec4A values at offsets 0x10-0x60. */
struct FieldCopyRecordSourceDA0D0
{
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0c;
    FieldVec4A unk10;
    FieldVec4A unk20;
    FieldVec4A unk30;
    FieldVec4A unk40;
    FieldVec4A unk50;
    FieldVec4A unk60;
    u32 unk70;
    float unk74;
    float unk78;
    float unk7c;
    u8 unk80;
    u8 unk81;
};

/** Destination record with six FieldVec4B values at offsets 0x10-0x60. */
struct FieldCopyRecordDestDA0D0
{
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0c;
    FieldVec4B unk10;
    FieldVec4B unk20;
    FieldVec4B unk30;
    FieldVec4B unk40;
    FieldVec4B unk50;
    FieldVec4B unk60;
    u32 unk70;
    float unk74;
    float unk78;
    float unk7c;
    u8 unk80;
    u8 unk81;
};

#endif

#ifdef __cplusplus
extern "C" {

/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 9.
 */
s32 func_002DA170(FieldClass150070* object);

/**
 * @brief Detach the object and queue it for removal.
 * @param object Object to remove.
 */
void func_002DA180(FieldClass150070* object);

/**
 * @brief Copy four aligned values to an object and return a copy of them.
 * @param destination Object field to update.
 * @param source Values to copy.
 * @return The copied values.
 */
FieldQuad4DA0D0 func_002DACE0(FieldQuad4DA0D0* destination, const FieldQuad4DA0D0* source);

/**
 * @brief Copy a source record into a destination record.
 * @param destination Record to update.
 * @param source Record to copy.
 * @return The destination record.
 */
FieldCopyRecordDestDA0D0* func_002DAD30(FieldCopyRecordDestDA0D0* destination, const FieldCopyRecordSourceDA0D0* source);

/**
 * @brief Set bit 0 in the state byte at offset 0x2C.
 * @param object Object whose flag is updated.
 */
void func_002DADD0(FieldFlag2DADD0* object);

}
#endif

#endif
