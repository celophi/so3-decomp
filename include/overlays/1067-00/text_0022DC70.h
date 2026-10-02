#ifndef SO3_OVERLAYS_1067_00_TEXT_0022DC70_H
#define SO3_OVERLAYS_1067_00_TEXT_0022DC70_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Update matching attached entries with a caller-supplied word.
 * @param object Receiver holding the attached entries.
 * @param value Word used to select entries.
 */
void func_00232360(void* object, u32 value);

/**
 * @brief Create and attach the receiver's field object.
 * @param object Receiver to update.
 */
void func_00232730(void* object);

typedef struct FieldObject22DD50 FieldObject22DD50;

/**
 * @brief Pass this object's float to its attached object.
 * @param object Receiver holding the float and attachment.
 * @return Always 1.
 */
s32 func_0022DD50(FieldObject22DD50* object);

typedef struct FieldObject22E170 FieldObject22E170;

/**
 * @brief Set the attached float to 1.0 when its nested flag is set.
 * @param object Receiver holding the attached object.
 * @return 0 when the flag is set, otherwise 1.
 */
s32 func_0022E170(FieldObject22E170* object);

typedef struct FieldObject22E380 FieldObject22E380;

/**
 * @brief Copy this object's float at 0x1C to the attached object's float at 0x78.
 * @param object Receiver holding the attached object.
 * @return Always 1.
 */
s32 func_0022E380(FieldObject22E380* object);

typedef struct FieldObject22E680 FieldObject22E680;
typedef struct FieldObject2320D0 FieldObject2320D0;

/**
 * @brief Forward the attached object to the resident release helper.
 * @param object Callback receiver.
 * @return Always 1.
 */
s32 func_0022E350(FieldObject22E170* object);

/**
 * @brief Reset the attached state and point the receiver at its own byte.
 * @param object Receiver to update.
 */
void func_0022E650(FieldObject22E680* object);

/**
 * @brief Reset the receiver's self-pointer, state bit, and signed state word.
 * @param object Receiver to reset.
 */
void func_0022E680(FieldObject22E680* object);

typedef struct FieldObject239A10 FieldObject239A10;

/**
 * @brief Set or clear bit 0 of the receiver byte at 0x69F.
 * @param object Receiver containing the flag byte.
 * @param enabled Nonzero to set the bit; zero to clear it.
 */
void func_00239A10(FieldObject239A10* object, u32 enabled);

typedef struct FieldObject31E30 FieldObject31E30;

/**
 * @brief Store a float on the receiver and its attached object when present.
 * @param object Receiver containing the float and optional attachment.
 * @param value Float to store.
 */
void func_00231E30(FieldObject31E30* object, float value);

typedef struct FieldObject232090 FieldObject232090;

/**
 * @brief Clamp a signed byte to 4, store it, and set the adjacent active bit.
 * @param object Receiver holding the byte and flag.
 * @param value Signed byte to store.
 */
void func_00232090(FieldObject232090* object, s8 value);

typedef struct FieldObject233470 FieldObject233470;

/**
 * @brief Forward the Boolean value to an attached list when present.
 * @param object Receiver holding the optional list pointer.
 * @param value Boolean value to forward.
 */
void func_002320D0(FieldObject2320D0* object, u8 value);

/**
 * @brief Update the receiver and forward the setting to its attached list.
 * @param object Receiver with an optional list.
 * @param enable Boolean setting to apply.
 * @param update Nonzero to store the setting on the receiver.
 */
void func_00232100(FieldObject2320D0* object, u8 enable, s32 update);

/**
 * @brief Initialize the field state when its check succeeds.
 * @param object Receiver to initialize.
 * @return 1 when initialized; otherwise 0.
 */
s32 func_00232A10(void* object);

/**
 * @brief Initialize the receiver's field state.
 * @param object Receiver to initialize.
 */
void func_00234110(void* object);

/**
 * @brief Store three floats when state bit 8 is clear, then set that bit.
 * @param object Receiver holding the state bit and float fields.
 * @param first Value for the float at 0x214.
 * @param second Value for the float at 0x20C.
 * @param third Value for the float at 0x210.
 */
void func_00233470(FieldObject233470* object, float first, float second, float third);

typedef struct FieldObject234B0 FieldObject234B0;

/**
 * @brief Clear the active bit, restore the prior state byte, and update the receiver when allowed.
 * @param object Receiver holding the flags and aligned vector.
 */
void func_002334B0(FieldObject234B0* object);

typedef struct FieldObject232640 FieldObject232640;

/**
 * @brief Select the field table from the receiver's mode and clear its state when bit 2 is absent.
 * @param object Receiver holding the table and mode bit.
 * @param flags Bits controlling whether to update it.
 */
void func_00232640(FieldObject232640* object, u8 flags);

/**
 * @brief Enter state 3, store the supplied flags and float, and update the field table when bit 2 is clear.
 * @param object Receiver holding the state, flags, float, and table.
 * @param flags New flag byte.
 * @param value New float value.
 */
void func_00232690(FieldObject232640* object, u8 flags, float value);

/**
 * @brief Reset the attached field state and select the table for the receiver's mode.
 * @param object Receiver to reset.
 */
void func_00233660(FieldObject232640* object);

/**
 * @brief Store a state word, then clear attached fields when it is 255.
 * @param object Receiver holding the state and optional attachment.
 * @param state State word to store.
 */
void func_002336B0(FieldObject232640* object, s32 state);

typedef struct FieldObject32710 FieldObject32710;
typedef struct FieldObject32710Result FieldObject32710Result;

/**
 * @brief Return the attached object's target when one is present.
 * @param object Receiver holding the optional attachment at 0x588.
 * @return Attached target pointer, or null when there is no attachment.
 */
FieldObject32710Result* func_00232710(FieldObject32710* object);

typedef struct FieldObject239880 FieldObject239880;

/**
 * @brief Check the float at 0x78, falling back to the word at 0xC.
 * @param object Receiver holding the float and word.
 * @return 1 when the float passes the comparison or the word is nonzero; otherwise 0.
 */
s32 func_00239880(FieldObject239880* object);

typedef struct FieldObject239B60 FieldObject239B60;

/**
 * @brief Copy the receiver's aligned vector and store three supplied floats.
 * @param object Receiver containing the vector and float fields.
 * @param first Value for the float at 0x680.
 * @param second Value for the float at 0x688.
 * @param third Value for the float at 0x68C.
 */
void func_00239B60(FieldObject239B60* object, float first, float second, float third);

/**
 * @brief Run the field update and report whether it succeeds.
 * @param object Receiver to update.
 * @return 1 when the update succeeds; otherwise 0.
 */
s32 func_00239B80(void* object);

/**
 * @brief Update the field state and report its integer result.
 * @param object Receiver to update.
 * @return Nonzero on success.
 */
s32 func_002351F0(void* object);

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

typedef struct FieldObject152EB0 FieldObject152EB0;

/**
 * @brief Report the fixed category for this object.
 * @param object Receiver.
 * @return Always 9.
 */
s32 func_00231110(FieldObject152EB0* object);

/**
 * @brief Detach this object and add it to the resident object queue.
 * @param object Object to detach and queue.
 */
void func_00231120(FieldObject152EB0* object);

typedef struct FieldObject1530A0 FieldObject1530A0;

/**
 * @brief Detach this object and add it to the resident object queue.
 * @param object Object to detach and queue.
 */
void func_0023A6E0(FieldObject1530A0* object);

typedef struct FieldObject1530D0 FieldObject1530D0;

/**
 * @brief Report the fixed category for this object.
 * @param object Receiver.
 * @return Always 12.
 */
s32 func_0023B1A0(FieldObject1530D0* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00238520(void* object);

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

    u32 unk00;
    u32 unk04;
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

    /** @brief Run slot 2 to release the object at offset 0x4, then reset the fields as the constructor does. */
    void release()
    {
        func_0023AD00();
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

    /**
     * @brief Return the word at offset 4, rounded up to 128 bytes unless bit 0
     *        at offset 8 or bit 2 at offset 0x16 is set.
     * @return The raw or rounded value.
     */
    u32 rounded_unk04() const
    {
        if (unk08_0 || unk16_2)
        {
            return (u32)unk04;
        }
        return ((u32)unk04 + 0x7F) & ~0x7F;
    }

    /**
     * @brief Delete the object at offset 0x4 when it is set and bit 1 at offset 0x16 is set.
     * @return 1 when the object was deleted, otherwise 0.
     */
    virtual s32 func_0023AD00();
};
#endif

#endif
