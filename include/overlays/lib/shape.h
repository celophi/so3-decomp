#ifndef SO3_OVERLAYS_LIB_SHAPE_H
#define SO3_OVERLAYS_LIB_SHAPE_H

#include "types.h"
#include "overlays/lib/vector.h"

#define LIB_SHAPE_ATTRIBUTE_MAGIC 0x415452
#define LIB_SHAPE_DATA_BOUND 0x80
#define LIB_SHAPE_NAME_LENGTH 16
#define LIB_SHAPE_KIND_BOX 0
#define LIB_SHAPE_KIND_SPHERE 1

#ifdef __cplusplus
struct LibTransformOwner;

/** Flags and identifier of a FieldShapeRecord20, at its offset 0xC. */
struct FieldShapeRecordInfo
{
    u8 unk00_0_3 : 4;
    u8 unk00_4 : 1;
    u8 unk00_5 : 1;
    u8 unk00_6_7 : 2;
    u8 unk01;
    u16 unk02;
};

/**
 * 32-byte shape record. The first 16 bytes are read as a FieldVec4B of half
 * extents, so the flag byte at offset 0xC overlaps its fourth component.
 */
struct FieldShapeRecord20
{
    float unk00;
    float unk04;
    float unk08;
    FieldShapeRecordInfo unk0c;
    FieldVec4A unk10;
};

/** Partial owner of FieldClass150330 shapes: an object at offset 4, an index at 0xC and a vector at 0x10. */
struct FieldShapeOwner18
{
    FieldShapeOwner18* unk00;
    LibTransformOwner* unk04;
    u8 unk08[2];
    u8 unk0a;
    u8 unk0b;
    s16 unk0c;
    s16 unk0e;
    FieldVec4A unk10;

    /**
     * @brief Test whether this is the last shape of its sibling run.
     * @return True for the last sibling.
     */
    bool is_last() const
    {
        if (unk0a & 0x20)
        {
            return true;
        }

        return false;
    }
};

/** Opaque 16-byte state attached to a shape. */
struct FieldShapeState10
{
    u8 unk00[0x10];
};

/** Twenty-byte entry containing a shape state at offset 4. */
struct FieldShapeEntry14
{
    u32 unk00;
    FieldShapeState10 unk04;
};

/** Shape data header: the name entry array and the shape-record array, offsets until the data is bound. */
struct FieldShapeData10
{
    u8 unk00;
    u8 flags;
    s16 shape_count;
    u8 unk04[4];
    FieldShapeEntry14* unk08;
    FieldShapeRecord20* unk0c;
};

/** Fixed attribute payload header; the shape descriptors follow it. */
struct FieldShapeData30
{
    FieldShapeData10 prefix;
    u8 unk10[0x20];
};

/**
 * Partial 16-byte class with vtable D_1515D0 in main data. Its vtable pointer
 * follows its data at offset 0xC.
 */
class FieldClass1515D0
{
public:
    /** @brief Initialize empty owned resource storage. */
    FieldClass1515D0()
    {
        unk08 = 0;
        unk04 = 0;
        unk00 = 0;
    }

    FieldShapeData30* unk00;
    void* unk04;
    u8 unk08;
    u8 unk09[3];

    /** @brief Release the buffer when this object owns its storage. */
    virtual ~FieldClass1515D0()
    {
        if (!unk08)
        {
            ::operator delete(unk04);
        }
    }
};
#endif

#endif
