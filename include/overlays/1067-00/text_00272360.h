#ifndef SO3_OVERLAYS_1067_00_TEXT_00272360_H
#define SO3_OVERLAYS_1067_00_TEXT_00272360_H

#include "types.h"
#include "overlays/1067-00/curve.h"

#ifdef __cplusplus
#include "overlays/1067-00/text_001DD3C0.h"
#include "overlays/lib/text_004BD360.h"

/** 0x90-byte field list with its secondary list base at offset 0x14. */
class FieldClass154E90 : public FieldClass150070, public FieldClass1502A0
{
public:
    /** @brief Allocate through the Lib heap. @param size Allocation size. @return Allocated storage or null. */
    static void* operator new(u32 size);

    /** @brief Release storage through the Lib heap. @param object Storage to release. */
    static void operator delete(void* object)
    {
        func_004DB570(object);
    }

    /** @brief Initialize the inherited node and list. */
    FieldClass154E90()
    {
    }

    /** @brief Destroy both list bases. */
    virtual ~FieldClass154E90();

    /** @brief Report the fixed list kind. @return Four. */
    virtual s32 func_001DF3D0();

    /** @brief Release the listed objects, detach this node and queue it for release. */
    virtual void func_001DD7B0();

    /** @brief Advance the list's objects when their update conditions hold. */
    virtual void func_001DF360();

    u8 unk8c[4];
};

extern "C" {
#endif

/**
 * @brief Compute coefficients for the owner's component curve.
 * @param object Component-curve owner.
 */
void func_002723E0(FieldClass1514F8* object);

/** Release the auxiliary state at 0x5A4, then clean up the receiver. */
void func_00272B50(void* object);

/**
 * @brief Append a pair of components to the owner's vector array.
 * @param object Component-curve owner.
 * @param first First component.
 * @param second Second component.
 * @return Index of the appended pair.
 */
s32 func_00272950(FieldClass1514F8* object, float first, float second);

/**
 * @brief Evaluate the curve at a floating-point position.
 * @param curve Curve records and count.
 * @param position Input position.
 * @return Interpolated value, or zero when the curve has fewer than two points.
 */
float func_00272820(FieldClass1514F8* curve, float position);

#ifdef __cplusplus
}
#endif

#endif
