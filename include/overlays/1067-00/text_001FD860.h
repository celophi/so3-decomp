#ifndef SO3_OVERLAYS_1067_00_TEXT_001FD860_H
#define SO3_OVERLAYS_1067_00_TEXT_001FD860_H

#include "types.h"

/** Partial resource-list link; the complete node extent is unknown. */
typedef struct FieldResourceListNode
{
    u8 unk00[8];
    struct FieldResourceListNode* next;
} FieldResourceListNode;

/** Partial resource entry with size words, keys, a counter and flags. */
typedef struct FieldResourceListEntry
{
    FieldResourceListNode link;
    u8 unk0c[8];
    u32 unk14;
    u32 unk18;
    u32 unk1c;
    u32 unk20;
    u8 unk24[0x1C];
    s32 unk40;
    u8 unk44[5];
    u8 unk49_0 : 1;
    u8 unk49_1 : 1;
    u8 unk49_2 : 1;
    u8 unk49_3 : 1;
    u8 unk49_4_7 : 4;
} FieldResourceListEntry;

/** Partial resource-list owner with an embedded sentinel. */
typedef struct FieldResourceList14
{
    u8 unk00[0x14];
    FieldResourceListNode unk14;
} FieldResourceList14;

/** Partial owner containing a word used in packed resource keys. */
typedef struct FieldPackedKeyOwner3AC
{
    u8 unk00[0x3AC];
    u32 unk3ac;
} FieldPackedKeyOwner3AC;

/** Partial receiver supplying three components of a packed resource key. */
typedef struct FieldPackedKeySource
{
    u8 unk00[8];
    FieldPackedKeyOwner3AC* unk08;
    u16* unk0c;
    u8 unk10[4];
    u32 unk14;
} FieldPackedKeySource;

/** Partial receiver containing word flags and an object pointer. */
typedef struct FieldFlaggedPointerA0
{
    u8 unk00[0x70];
    u32 unk70;
    u8 unk74[0x2C];
    void* unka0;
} FieldFlaggedPointerA0;

/** Partial receiver containing an object pointer, flag and float value. */
typedef struct FieldFloatGateState7C
{
    u8 unk00[0x7C];
    void* unk7c;
    u8 unk80[0xC];
    u8 unk8c_0 : 1;
    u8 unk8c_1_4 : 4;
    u8 unk8c_5 : 1;
    u8 unk8c_6_7 : 2;
    u8 unk8d[3];
    float unk90;
} FieldFloatGateState7C;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Clear a matching object pointer when the word flag is set.
 * @param object Receiver containing the pointer and flags.
 * @param value Object pointer to compare.
 */
void func_001FF4A0(FieldFlaggedPointerA0* object, void* value);

/**
 * @brief Decrement counters for matching resource entries that pass their flag checks.
 * @param object Resource list to update.
 * @param first Low-halfword key for kinds 0x43484152 and 0x41545243.
 * @param second Low-halfword key for kind 0x414E494D.
 */
void func_002016F0(FieldResourceList14* object, s32 first, s32 second);

/**
 * @brief Increment counters for matching resource entries that pass their flag checks.
 * @param object Resource list to update.
 * @param first Low-halfword key for kinds 0x43484152 and 0x41545243.
 * @param second Low-halfword key for kind 0x414E494D.
 */
void func_002017B0(FieldResourceList14* object, s32 first, s32 second);

/**
 * @brief Find the size selected by a resource entry's flag.
 * @param object Resource list to search.
 * @param kind Resource kind to match.
 * @param key Resource key to match.
 * @return The selected size, or zero when no matching entry exists.
 */
u32 func_00201E20(FieldResourceList14* object, u32 kind, u32 key);

/**
 * @brief Combine the receiver and owner components into a packed resource key.
 * @param object Receiver supplying the key components.
 * @return The combined packed key.
 */
u32 func_00202240(const FieldPackedKeySource* object);

/**
 * @brief Test the float value when the object pointer and flag permit it.
 * @param object Receiver containing the pointer, flag and float value.
 * @return True when the object pointer is nonnull, bit zero is clear and the float value is not positive.
 */
bool func_00204420(const FieldFloatGateState7C* object);

#ifdef __cplusplus
}
#endif

#endif
