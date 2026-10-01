#ifndef SO3_OVERLAYS_1067_00_TEXT_0022DC70_H
#define SO3_OVERLAYS_1067_00_TEXT_0022DC70_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Release the object stored at offset 0x548 through its virtual handler at vtable offset 0x10, then clear the field.
 * @param object Receiver owning the stored object.
 */
void func_00233620(void* object);

/**
 * @brief Create and register the object stored at offset 0x548 when the current state permits it.
 * @param object Receiver owning the stored object.
 */
void func_00234000(void* object);

/**
 * @brief Submit a newly allocated request for the receiver when its state bits permit, then update those bits.
 * @param object Receiver whose state bits are checked and updated.
 * @param flag Nonzero to give the request a pseudo-random bit.
 */
void func_002379A0(void* object, s32 flag);

#ifdef __cplusplus
}

/**
 * Partial base of 32-byte records, with vtable D_1530C0 in boot data. Its
 * vtable pointer follows its data at offset 0x18.
 */
class FieldClass1530C0
{
public:
    /** @brief Clear the state words and flags, and set bit 1 at offset 0x16. */
    FieldClass1530C0()
    {
        unk0c = -1;
        unk04 = 0;
        unk10 = 0;
        unk16_0 = 0;
        unk16_1 = 1;
        unk08_0 = 0;
        unk16_2 = 0;
        unk14 = 0;
        unk15 = 0;
    }

    u8 unk00[4];
    void* unk04;
    u8 unk08_0 : 1;
    u8 unk08_1_7 : 7;
    u8 unk09[3];
    s32 unk0c;
    u32 unk10;
    u8 unk14;
    u8 unk15;
    u8 unk16_0 : 1;
    u8 unk16_1 : 1;
    u8 unk16_2 : 1;
    u8 unk16_3_7 : 5;
    u8 unk17;

    /**
     * @brief Delete the object at offset 0x4 when it is set and bit 1 at offset 0x16 is set.
     * @return 1 when the object was deleted, otherwise 0.
     */
    virtual s32 func_0023AD00();
};
#endif

#endif
