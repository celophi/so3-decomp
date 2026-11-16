#ifndef SO3_OVERLAYS_LIB_ROW_FILL_H
#define SO3_OVERLAYS_LIB_ROW_FILL_H

#include "types.h"
#include "overlays/lib/emission.h"

#ifdef __cplusplus
/** One 16-byte value also accessed as four floats. */
typedef union RowFillVector
{
    float floats[4];
    unsigned __int128 packed;
} RowFillVector;

/** Partial view of a grid's emission settings used when filling secondary rows. */
struct RowFillOwner
{
    u8 unk00[0x10];
    s32 unk10;
    u8 unk14[0x14];
    float unk28;
    u8 unk2c[0x10];
    float unk3c;
    u8 unk40[0xD];
    u8 unk4d;
    u8 unk4e[2];
    LibClass173990* secondary_emitter;
};

/** Partial view of a grid cell: its position and secondary vector. */
struct RowFillCell
{
    /**
     * @brief Get the cell position.
     * @return The position vector.
     */
    const RowFillVector& position() const
    {
        return unk10;
    }

    u8 unk00[0x10];
    RowFillVector unk10;
    RowFillVector unk20;
    u8 unk30[0xC];
    float unk3c;
};

/** Partial view of a 64-byte secondary row element. */
struct RowFillElement
{
    u8 unk00[0x10];
    RowFillVector unk10;
    RowFillVector unk20;
    RowFillVector unk30;
};
#endif

#endif
