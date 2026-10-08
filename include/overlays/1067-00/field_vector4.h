#ifndef SO3_OVERLAYS_1067_00_FIELD_VECTOR4_H
#define SO3_OVERLAYS_1067_00_FIELD_VECTOR4_H

/** One 16-byte value also accessed as four floats. */
typedef unsigned __int128 FieldQword;
typedef union FieldVector4
{
    float floats[4];
    FieldQword packed;
} FieldVector4;

#endif
