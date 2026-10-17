#ifndef SO3_OVERLAYS_1067_00_TEXT_002541F0_H
#define SO3_OVERLAYS_1067_00_TEXT_002541F0_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct FieldObject1537C0 FieldObject1537C0;

/**
 * @brief Report the fixed category for this object.
 * @param object Receiver.
 * @return Always 3.
 */
s32 func_002541F0(FieldObject1537C0* object);

/**
 * @brief Detach the receiver from its owner and append it to the resident object queue.
 * @param object Receiver to detach and append.
 */
void func_00254200(void* object);

/**
 * @brief Return 8 when bit 1 of the resident context byte at 0xDF is clear.
 * @return 8 if the bit is clear, otherwise zero.
 */
s32 func_00254BD0(void);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include "overlays/1067-00/text_001DD3C0.h"

/** Camera controller retained by the field context. */
class FieldClass1537C0 : public FieldListObject, public FieldClass1DD400
{
public:
    FieldClass1537C0();
    virtual ~FieldClass1537C0();

    u8 unk18[8];
    float unk20;
    u8 unk24[0x10];
    u32 unk34;
    u8 unk38[4];
    u32 unk3c;
    u8 unk40[0x11];
    u8 unk51_0 : 1;
    u8 unk51_1 : 1;
    u8 unk51_2 : 1;
    u8 unk51_3_7 : 5;
    u8 unk52[2];
};
#endif

#ifdef __cplusplus
extern "C"
{
    u32 func_00254230(void* object, s32 first, s32 second, float third);
}
#endif

#endif
