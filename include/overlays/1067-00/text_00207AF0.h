#ifndef SO3_OVERLAYS_1067_00_TEXT_00207AF0_H
#define SO3_OVERLAYS_1067_00_TEXT_00207AF0_H

#include "types.h"
#include "overlays/1067-00/text_00207580.h"

typedef struct FieldMotionRange FieldMotionRange;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Copy the receiver's float and aligned vector fields.
 * @param object Receiver to update.
 */
void func_00209B30(FieldCopyState* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_0020BCF0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_0020BD00(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_0020BDA0(void* object);

/**
 * @brief Test whether the lookup helper returns an object.
 * @param object Receiver to query.
 * @return True when the helper returns a nonnull object.
 */
bool func_0020BDB0(void* object);

/**
 * @brief Run an update helper and finish the attached callback object.
 * @param object Callback receiver.
 */
void func_0020BD60(FieldCallbackState* object);

/**
 * @brief Forward the callback when the receiver is active.
 * @param object Callback receiver.
 * @param context Context passed to the callback.
 * @param enabled Value converted to a boolean for the callback.
 */
void func_0020BDD0(FieldCallbackState* object, void* context, u32 enabled);

/**
 * @brief Clear the attached callback object after notifying it.
 * @param object Callback receiver.
 */
void func_0020BE00(FieldCallbackState* object);

/**
 * @brief Store a word at offset 0xC4.
 * @param object Receiver to update.
 * @param value Word to store.
 */
void func_0020BEF0(FieldAtC4* object, u32 value);

/**
 * @brief Store a size and its 128-byte rounded form.
 * @param object Receiver to update.
 * @param size Size to store and round.
 */
void func_0020BF50(FieldAlignedSize* object, u32 size);

/**
 * @brief Find a list entry with the requested kind.
 * @param object List owner.
 * @param kind Kind to search for.
 * @return One if found, otherwise zero.
 */
s32 func_0020CB20(FieldCbOwner* object, u16 kind);

/**
 * @brief Return the receiver unchanged.
 * @param object Receiver of the call.
 * @return The receiver.
 */
void* func_0020CE30(void* object);

/**
 * @brief Test bit zero of the byte at offset 0x81.
 * @param object Receiver to test.
 * @return True when the bit is set.
 */
bool func_00208C80(const FieldState81* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_00207EE0(void* object);

/**
 * @brief Set a target float and its change rate.
 * @param object Motion receiver.
 * @param target New target value.
 * @param duration Duration used for the rate.
 */
void func_00209780(FieldMotion* object, float target, float duration);

/**
 * @brief Set a range target and its change rate.
 *
 * A zero target is replaced by the xyz distance from the receiver's position
 * to the vector at offset 0x260 of the field context's object at offset 0x14.
 * A zero duration copies the target to the start; otherwise the step is the
 * start-to-target change per unit of duration and flag 0x100 is set.
 * @param object Range receiver.
 * @param target New target value, or zero to measure it.
 * @param duration Duration used for the rate, or zero for an immediate change.
 */
void func_002098C0(FieldMotionRange* object, float target, float duration);

/**
 * @brief Set the first motion target and rate, substituting the fallback sentinel.
 * @param object Motion receiver.
 * @param target New value or sentinel.
 * @param duration Duration used for the rate.
 */
void func_00209BB0(FieldMotion2* object, float target, float duration);

/**
 * @brief Set the second motion target and rate, substituting the fallback sentinel.
 * @param object Motion receiver.
 * @param target New value or sentinel.
 * @param duration Duration used for the rate.
 */
void func_00209C20(FieldMotion3* object, float target, float duration);

/**
 * @brief Set or immediately apply the motion target.
 * @param object Motion receiver.
 * @param target New target value.
 * @param duration Duration used for the rate.
 */
void func_00209C90(FieldMotion4* object, float target, float duration);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * Partial 16-byte class with vtable D_1515D0 in main data. Its vtable pointer
 * follows its data at offset 0xC.
 */
class FieldClass1515D0
{
public:
    void* unk00;
    u32 unk04;
    u8 unk08;
    u8 unk09[3];

    /** @brief Destroy the object. */
    virtual ~FieldClass1515D0();
};

/** Partial FieldClass1515D0 with four more virtual slots, with vtable D_154D20 in main data. */
class FieldClass154D20 : public FieldClass1515D0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass154D20();

    /** @brief Virtual handler slot 1. */
    virtual void func_0020BDA0();

    /** @brief Virtual handler slot 2. */
    virtual void func_0020BD00();

    /**
     * @brief Return the FieldClass1515D0 part to use.
     * @return This object.
     */
    virtual FieldClass1515D0* func_001DDCD0();

    /** @brief Virtual handler slot 4. */
    virtual void func_0020BCF0();
};

/**
 * Partial FieldClass150F90 with three more virtual slots, with vtable D_151510
 * in main data. Its constructor (func_0020BF70) sets type bit 0x1 in unk78.
 * Overrides of earlier slots are not declared yet.
 */
class FieldClass151510 : public FieldClass150F90
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass151510();

    /** @brief Virtual handler slot 16. */
    virtual void func_0020BE50();

    /** @brief Virtual handler slot 17. */
    virtual void func_0020BF00();

    /**
     * @brief Virtual handler slot 18.
     * @param arg Argument whose meaning is not yet known.
     */
    virtual void func_0020BF50(void* arg);

    /**
     * @brief Test whether an object is stored at offset 0x148.
     * @return True when the pointer at offset 0x148 is set.
     */
    bool test_unk148() const
    {
        if (unk148)
        {
            return true;
        }
        return false;
    }

    /**
     * @brief Test bits of the word at offset 0x204.
     * @param mask Bits to test.
     * @return True when any bit in mask is set.
     */
    bool test_unk204(u32 mask) const
    {
        if (unk204 & mask)
        {
            return true;
        }
        return false;
    }

    float unkA0;
    float unkA4;
    FieldClass154D20* unkA8;
    u32 unkAC;
    u32 unkB0;
    u8 unkB4[0x94];
    void* unk148;
    u8 unk14c[0x24];
    FieldVec4A unk170;
    FieldVec4A unk180;
    FieldVec4A unk190;
    u8 unk1a0[0x64];
    u32 unk204;
    u32 unk208;
};
#endif

#endif
