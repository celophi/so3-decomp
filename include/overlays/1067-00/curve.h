#ifndef SO3_OVERLAYS_1067_00_CURVE_H
#define SO3_OVERLAYS_1067_00_CURVE_H

#include "types.h"

#ifdef __cplusplus
class FieldVec4B;

/** Twelve-byte owner of a counted vector array, with table D_1514F8. */
class FieldClass1514F8
{
public:
    s32 unk00;
    FieldVec4B* unk04;

    /** @brief Initialize an empty vector array. */
    FieldClass1514F8()
    {
        unk04 = 0;
        unk00 = 0;
    }

    /** @brief Release the owned vector array. */
    virtual ~FieldClass1514F8();
};

#else
/** C view of the curve owner's data prefix and trailing vtable pointer. */
typedef struct FieldClass1514F8
{
    s32 unk00;
    struct FieldVec4B* unk04;
    void* unk08;
} FieldClass1514F8;
#endif

#endif
