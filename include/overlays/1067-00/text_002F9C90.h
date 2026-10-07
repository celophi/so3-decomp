#ifndef SO3_OVERLAYS_1067_00_TEXT_002F9C90_H
#define SO3_OVERLAYS_1067_00_TEXT_002F9C90_H

#include "types.h"
#ifdef __cplusplus
#include "overlays/1067-00/text_002F3310.h"
#include "overlays/1067-00/text_001DD3C0.h"
#else
#include "overlays/1067-00/text_002F1B20.h"
#endif

typedef struct FieldByte60F9C90 FieldByte60F9C90;
typedef struct FieldByte4F9C90 FieldByte4F9C90;

/** Partial receiver with an enable byte and five floats at offsets 0x5C-0x74. */
typedef struct FieldFloatState5C
{
    u8 unk00[0x5C];
    u8 enabled;
    u8 unk5D[7];
    float values[5];
} FieldFloatState5C;

#ifdef __cplusplus
/** Status window with an owned transform/display object. */
class FieldClass15BB90 : public FieldClass150070
{
public:
    /** @brief Initialize the window and its owned display object. */
    FieldClass15BB90();

    /** @brief Destroy the window and its owned display object. */
    virtual ~FieldClass15BB90();

    /** @brief Release the window resources. */
    virtual void func_001DD7B0();

    /** @brief Update the window state. */
    virtual void func_001DF360();

    s16 status;
    u8 unk16[6];
    u32 unk1c;
    u32 unk20;
    u32 unk24;
    u32 unk28;
    u32 unk2c;
    u32 unk30;
    u32 unk34;
    u32 unk38;
    u32 unk3c;
    u32 unk40;
    u32 unk44;
    u32 unk48;
    u32 unk4c;
    u32 unk50;
    u32 unk54;
    u8 unk58;
    u8 unk59[2];
    u8 unk5b;
    u8 unk5c;
    u8 unk5d;
    u8 unk5e[0x1A];
    u32 unk78;
    u8 unk7c[4];
    LibVector4 unk80;
    LibVector4 unk90;
    u32 unka0;
    u32 unka4;
    u8 unka8[8];
    LibClass178EA0 member;
    u8 unk2c0[0x10];
};
typedef FieldClass15BB90 FieldStatus14;
#else
/** Partial receiver with a signed halfword at offset 0x14. */
typedef struct FieldStatus14
{
    u8 unk00[0x14];
    s16 status;
} FieldStatus14;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Store nine in the receiver's byte at offset 0x60.
 * @param object Receiver containing the byte.
 */
void func_002FE880(FieldByte60F9C90* object);

/**
 * @brief Store one in the receiver's byte at offset 4.
 * @param object Receiver containing the byte.
 */
void func_00301090(FieldByte4F9C90* object);

/**
 * @brief Enable the receiver and store five float values.
 * @param object Receiver containing the enable byte and values.
 * @param first First value to store.
 * @param second Second value to store.
 * @param third Third value to store.
 * @param fourth Fourth value to store.
 * @param fifth Fifth value to store.
 */
void func_002FD1B0(FieldFloatState5C* object, float first, float second, float third, float fourth, float fifth);

/**
 * @brief Attach the current auxiliary display to its manager.
 * @param object Status window containing the display.
 */
void func_002FD1D0(FieldStatus14* object);

/**
 * @brief Replace the auxiliary display and attach its associated object.
 * @param object Status window containing the display.
 * @param attached Associated object passed to the display.
 */
void func_002FD220(FieldStatus14* object, void* attached);

/**
 * @brief Request the keyed status resource while the window is idle.
 * @param object Status window receiving the request.
 * @param key Resource key.
 * @return One after a successful request, or zero otherwise.
 */
s32 func_002FDC00(FieldStatus14* object, s32 key);

/**
 * @brief Advance cancellation state or clear the receiver's associated object.
 * @param object Receiver with a signed status at offset 0x14 and associated resources.
 */
void func_002FD940(FieldStatus14* object);

/**
 * @brief Return whether the receiver's halfword at offset 0x14 is zero.
 * @param object Receiver containing the halfword.
 * @return Nonzero if the halfword is zero.
 */
s32 func_002FD480(const FieldStatus14* object);

/**
 * @brief Reset the byte counts and associated totals.
 * @param object Receiver containing the counts and totals.
 */
void func_002FA210(FieldHalfwordBuckets* object);

/**
 * @brief Read a halfword from an in-range category and populated bucket index.
 * @param object Receiver containing the buckets.
 * @param category Bucket category.
 * @param index Index within the selected bucket.
 * @return The stored halfword, or zero when either index is out of range.
 */
u16 func_002FAB20(const FieldHalfwordBuckets* object, u8 category, u16 index);

/**
 * @brief Find a target entry by its byte key and return its state.
 * @param object Receiver containing the target entries.
 * @param key Byte key to find.
 * @return The first matching entry state, or zero if no entry matches.
 */
u8 func_002FB510(const FieldStateTargets* object, u8 key);

/**
 * @brief Set every populated target state to two.
 * @param object Receiver containing the target entries.
 */
void func_002FB8A0(FieldStateTargets* object);

#ifdef __cplusplus
/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 3.
 */
s32 func_002FE870(FieldClass150070* object);
#endif

/**
 * @brief Test whether an identifier contains a qualifying nonempty entry.
 * @param identifier Signed item identifier.
 * @return One when the predicate holds, otherwise zero.
 */
u8 func_002FBED0(s16 identifier);

/**
 * @brief Test whether an identifier passes the empty-entry predicate.
 * @param identifier Signed item identifier.
 * @return One when the predicate holds, otherwise zero.
 */
u8 func_002FC730(s16 identifier);

/**
 * @brief Test whether an identifier passes the nonempty-entry predicate.
 * @param identifier Signed item identifier.
 * @return One when the predicate holds, otherwise zero.
 */
u8 func_002FC880(s16 identifier);

#ifdef __cplusplus
}
#endif

#endif
