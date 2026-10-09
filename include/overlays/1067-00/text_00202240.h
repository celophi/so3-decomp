#ifndef SO3_OVERLAYS_1067_00_TEXT_00202240_H
#define SO3_OVERLAYS_1067_00_TEXT_00202240_H

#include "types.h"
#include "overlays/1067-00/text_00200710.h"
#include "overlays/1067-00/text_001DD3C0.h"
#include "overlays/1067-00/text_00202240_callbacks.h"

#ifdef __cplusplus
/** Queued field object storing a channel index, float value and flags. */
class FieldClass150F50 : public FieldClass150070
{
public:
    /** @brief Destroy the queued object. */
    virtual ~FieldClass150F50();
    /** @brief Return the object kind. @return Five. */
    virtual s32 func_001DF3D0();
    /** @brief Process the selected channel using the stored value and flags. */
    virtual void func_001DF360();
    s32 unk14;
    float unk18;
    u32 unk1c;
};

#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Release the receiver's attached field resources.
 * @param object Receiver to clear.
 */
void func_00202840(void* object);

/**
 * @brief Combine the receiver and owner components into a packed resource key.
 * @param object Receiver supplying the key components.
 * @return The combined packed key.
 */
u32 func_00202240(const FieldPackedKeySource* object);

/**
 * @brief Copy the known fields from one record to another.
 * @param dest Destination record.
 * @param src Source record.
 * @return The destination record.
 */
FieldAssign14* func_00202990(FieldAssign14* dest, const FieldAssign14* src);

/**
 * @brief Initialize two aligned vectors and clear related fields.
 * @param obj Transform receiver.
 */
void func_00202BF0(FieldTransform* obj);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_00203500(void* object);

/**
 * @brief Set the receiver flag after a successful helper call.
 * @param obj Receiver to update.
 * @return True if the helper succeeds.
 */
bool func_00203930(FieldState3BA* obj);

/**
 * @brief Return the fixed value five.
 * @param object Receiver of the call.
 * @return Five.
 */
s32 func_00203B10(void* object);

/**
 * @brief Store a byte and set the related bit flag.
 * @param obj Receiver to update.
 * @param value Byte to store.
 */
void func_00204FA0(FieldByteState210* obj, u8 value);

/**
 * @brief Return the fixed value fourteen.
 * @param object Receiver of the call.
 * @return Fourteen.
 */
s32 func_00205700(void* object);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_00205790(void* object);

/**
 * @brief Return the fixed value eleven.
 * @param object Receiver of the call.
 * @return Eleven.
 */
int func_002057A0(void* object);

/**
 * @brief Return the fixed value one.
 * @param object Receiver of the call.
 * @return One.
 */
int func_002057B0(void* object);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_002057C0(void* object);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_002057D0(void* object);

/**
 * @brief Test the word at offset 0x704.
 * @param object Receiver to test.
 * @return True when the word is nonzero.
 */
bool func_002057E0(const FieldState704* object);

/**
 * @brief Find the field at offset 0x79C.
 * @param object Containing receiver.
 * @return The field address.
 */
void* func_002057F0(FieldState79C* object);

/**
 * @brief Read the byte at offset 0x794.
 * @param object Receiver to read.
 * @return The byte value.
 */
u32 func_00205800(const FieldState794* object);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_00205810(void* object);

/**
 * @brief Find the field at offset 0x570.
 * @param object Containing receiver.
 * @return The field address.
 */
void* func_00205850(FieldState570* object);

/**
 * @brief Run the callback when nested state and helper permit it.
 * @param object Receiver to inspect.
 * @param arg First callback argument.
 * @param other Second callback argument.
 */
void func_00206020(FieldOuter870* object, void* arg, void* other);

/**
 * @brief Update target flags for marked list entries.
 * @param object List owner.
 * @param value Selects whether to clear or set the flag.
 */
void func_00206200(FieldListAC* object, bool value);

/**
 * @brief Run the helper and clear a receiver bit when an object is present.
 * @param object Receiver to update.
 */
void func_002067F0(FieldStateAD* object);

/**
 * @brief Run the callback when the state helper succeeds.
 * @param object Receiver to inspect.
 * @param arg First callback argument.
 * @param other Second callback argument.
 */
void func_00207360(FieldState820* object, void* arg, void* other);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_002073C0(void* object);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_002073D0(void* object);

/**
 * @brief Return the second argument.
 * @param object Receiver of the call.
 * @param value Value to return.
 * @return The second argument.
 */
void* func_002073E0(void* object, void* value);

/**
 * @brief Return the second argument.
 * @param object Receiver of the call.
 * @param value Value to return.
 * @return The second argument.
 */
void* func_002073F0(void* object, void* value);

/**
 * @brief Run the receiver cleanup helpers.
 * @param object Receiver to clean up.
 */
void func_00207400(FieldState634* object);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * Partial base of the field object classes, with vtable D_150F90 in main data.
 * Derived classes set a type bit in unk78 (0x1 FieldClass151510, 0x2
 * FieldClass152430, 0x400 FieldClass153330, 0x20000 FieldClass15B090).
 */
class FieldClass150F90 : public FieldClass150070
{
public:
    /** @brief Set the default vectors, clear the table pointers and flags, and set unk74 to -1 and unk90 to 3.0. */
    FieldClass150F90();

    /** @brief Destroy the object. */
    virtual ~FieldClass150F90();

    /**
     * @brief Report the fixed value 4 for this class.
     * @return Always 4.
     */
    virtual s32 func_001DF3D0();

    /** @brief Virtual handler slot 2. */
    virtual void func_001DD7B0();

    /** @brief Virtual handler slot 3. */
    virtual void func_001DF360();

    /** @brief Virtual handler slot 5. */
    virtual void func_00204210();

    /**
     * @brief Load the actor resource selected by its key.
     * @param key Resource key, or -1 for the sentinel path.
     * @return One on success, zero when resource setup fails.
     */
    virtual s32 func_00204A10(s32 key);

    /** @brief Virtual handler slot 7. */
    virtual void func_00204E40();

    /** @brief Test or update the actor using another object. @param other Other object. @return Status result. */
    virtual s32 func_00204480(void* other);

    /**
     * @brief Test the table pointer, bit 0 at offset 0x8C and the float at offset 0x90.
     * @return True when the table at offset 0x7C is set, bit 0 at offset 0x8C is clear and the float is not positive.
     */
    virtual bool func_00204420();

    /**
     * @brief Virtual handler slot 10.
     * @return A value whose meaning is not yet known.
     */
    virtual s32 func_00205140();

    /**
     * @brief Virtual handler slot 11.
     * @param arg Argument whose meaning is not yet known.
     */
    virtual void func_00204EC0(void* arg);

    /**
     * @brief Update the table at offset 0x7C and, when enabling, run slot 14; optionally store the setting in bit 5 at offset 0x8C.
     * @param enable Nonzero to enable.
     * @param update Nonzero to store !enable in bit 5 at offset 0x8C.
     */
    virtual void func_00204370(u8 enable, s32 update);

    /** @brief Default handler that performs no work. */
    virtual void func_001DE3B0();

    /**
     * @brief Store !enable in bit 6 at offset 0x8C, then update the matching table entries.
     * @param enable Nonzero to enable.
     */
    virtual void func_002042A0(u8 enable);

    /**
     * @brief Copy a 16-byte vector to offset 0x20.
     * @param value Vector to copy.
     */
    virtual void func_00205710(const FieldVec4A* value);

    /**
     * @brief Test bits of the word at offset 0x70.
     * @param mask Bits to test.
     * @return True when any bit in mask is set.
     */
    bool test_unk70(u32 mask) const
    {
        if (unk70 & mask)
        {
            return true;
        }
        return false;
    }

    u8 unk14[0xC];
    FieldVec4A unk20;
    FieldVec4A unk30;
    FieldVec4A unk40;
    FieldVec4A unk50;
    FieldVec4A unk60;
    s32 unk70;
    s32 unk74;
    u32 unk78;
    void* unk7c;
    void* unk80;
    u32 unk84;
    u32 unk88;
    u8 unk8c_0 : 1;
    u8 unk8c_1 : 1;
    u8 unk8c_2 : 1;
    u8 unk8c_3 : 1;
    u8 unk8c_4 : 1;
    u8 unk8c_5 : 1;
    u8 unk8c_6 : 1;
    u8 unk8c_7 : 1;
    u8 unk8d_0 : 1;
    u8 unk8d_1 : 1;
    u8 unk8d_2_7 : 6;
    u8 unk8e[2];
    float unk90;
};
#endif

#endif
