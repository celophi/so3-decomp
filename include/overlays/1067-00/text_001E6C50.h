#ifndef SO3_OVERLAYS_1067_00_TEXT_001E6C50_H
#define SO3_OVERLAYS_1067_00_TEXT_001E6C50_H

#include "types.h"
#include "overlays/1067-00/text_001E1590.h"

/** Partial base receiver with a word at offset 0x18 and flag bit 0 at offset 0x20. */
typedef struct FieldFlagObject20
{
    u8 unk00[0x18];
    u32 unk18;
    u8 unk1c[4];
    u8 unk20_0 : 1;
    u8 unk20_1_7 : 7;
} FieldFlagObject20;

/** Four adjacent floats in a 16-byte record. */
typedef struct FieldFloat4
{
    float unk00;
    float unk04;
    float unk08;
    float unk0c;
} FieldFloat4;

/** Partial receiver with flag bit 0 at offset 0x20 and six 16-byte float records at offset 0x130. */
typedef struct FieldRecordObject130
{
    u8 unk00[0x20];
    u8 unk20_0 : 1;
    u8 unk20_1_7 : 7;
    u8 unk21[0x10F];
    FieldFloat4 unk130[6];
} FieldRecordObject130;

/** Partial receiver with three words at offsets 0x10-0x18 and flag bit 1 at offset 0x66. */
typedef struct FieldStateReset66
{
    u8 unk00[0x10];
    u32 unk10;
    u32 unk14;
    u32 unk18;
    u8 unk1c[0x4A];
    u8 unk66_0 : 1;
    u8 unk66_1 : 1;
    u8 unk66_2_7 : 6;
} FieldStateReset66;

/** Partial circular-list node keyed by the word at offset 0x54. */
typedef struct FieldKeyedListNode54
{
    u8 unk00[8];
    struct FieldKeyedListNode54* next;
    u8 unk0c[0x48];
    u32 unk54;
} FieldKeyedListNode54;

/** Partial receiver with a key, five float parameters, a constant float, a flag halfword and a mode word at offsets 0x98-0xB8. */
typedef struct FieldMotionParams98
{
    u8 unk00[0x98];
    u32 unk98;
    float unk9c;
    float unka0;
    float unka4;
    float unka8;
    float unkac;
    float unkb0;
    u16 unkb4;
    u8 unkb6[2];
    s32 unkb8;
} FieldMotionParams98;

/** Partial receiver with a signed halfword at offset 0x3A. */
typedef struct FieldHalfword3A
{
    u8 unk00[0x3A];
    s16 unk3a;
} FieldHalfword3A;

/** Partial receiver with a pointer at offset 0x30, a signed counter at offset 0xC0 and flags at offset 0xC4. */
typedef struct FieldCounterObjectC0
{
    u8 unk00[0x30];
    void* unk30;
    u8 unk34[0x8C];
    s32 unkc0;
    u8 unkc4_0 : 1;
    u8 unkc4_1 : 1;
    u8 unkc4_2_7 : 6;
} FieldCounterObjectC0;

/** Partial record with a leading pointer, flag byte at offset 0xA and signed halfword at offset 0xE. */
typedef struct FieldPackedRecord0E
{
    void* unk00;
    u8 unk04[6];
    u8 unk0a;
    u8 unk0b[3];
    s16 unk0e;
} FieldPackedRecord0E;

/** Partial object receiving a byte flag at offset 0x3C and a signed count at offset 0xFC. */
typedef struct FieldCountTarget
{
    u8 unk00[0x3C];
    u8 unk3c;
    u8 unk3d[0xBF];
    s32 unkfc;
} FieldCountTarget;

/** Partial receiver holding an optional FieldCountTarget at offset 0x34. */
typedef struct FieldCountOwner34
{
    u8 unk00[0x34];
    FieldCountTarget* unk34;
} FieldCountOwner34;

/** Partial receiver with pointers at offsets 0x80 and 0x448 and a disabling bit 5 at offset 0x8C. */
typedef struct FieldGatedObject448
{
    u8 unk00[0x80];
    void* unk80;
    u8 unk84[8];
    u8 unk8c_0_4 : 5;
    u8 unk8c_5 : 1;
    u8 unk8c_6_7 : 2;
    u8 unk8d[0x3BB];
    void* unk448;
} FieldGatedObject448;

/** Partial receiver with an entry array pointer at offset 4 and entry state at offsets 0x30-0x43. */
typedef struct FieldEntryArrayObject30
{
    u8 unk00[4];
    FieldArrayEntry10* unk04;
    u8 unk08[0x28];
    u32 unk30;
    u8 unk34[4];
    s16 unk38;
    s16 unk3a;
    s16 unk3c;
    s16 unk3e;
    s16 unk40;
    u8 unk42_0_3 : 4;
    u8 unk42_4_7 : 4;
    u8 unk43_0 : 1;
    u8 unk43_1 : 1;
    u8 unk43_2_7 : 6;
} FieldEntryArrayObject30;

#ifdef __cplusplus
/** Partial class derived from FieldClass150070, with vtable D_150330 in boot data. */
class FieldClass150330 : public FieldClass150070
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass150330();

    /** @brief Detach the object and queue it on the resident object queue. */
    virtual void func_001DD7B0();
};

/** Partial class derived from FieldClass150070, with vtable D_150460 in boot data. */
class FieldClass150460 : public FieldClass150070
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass150460();
};

/** Partial class derived from FieldClass150460, with vtable D_150490 in boot data. */
class FieldClass150490 : public FieldClass150460
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass150490();
};

/** Partial class derived from FieldClass150490, with vtable D_1504C0 in boot data. */
class FieldClass1504C0 : public FieldClass150490
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass1504C0();

    /** @brief Detach the object and queue it on the resident object queue. */
    virtual void func_001DD7B0();
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Store the word at offset 0x18.
 * @param object Receiver to update.
 * @param value Word to store.
 */
void func_001E6CF0(FieldFlagObject20* object, u32 value);

/**
 * @brief Clear flag bit 0 at offset 0x20.
 * @param object Receiver to update.
 */
void func_001E6D00(FieldFlagObject20* object);

/**
 * @brief Set flag bit 0 at offset 0x20.
 * @param object Receiver to update.
 */
void func_001E73D0(FieldFlagObject20* object);

/**
 * @brief Clear flag bit 0 at offset 0x20 and the last float of each of the six records at offset 0x130.
 * @param object Receiver to update.
 */
void func_001E7520(FieldRecordObject130* object);

/**
 * @brief Clear the words at offsets 0x10-0x18 and flag bit 1 at offset 0x66.
 * @param object Receiver to reset.
 */
void func_001E7560(FieldStateReset66* object);

/**
 * @brief Find a node whose word at offset 0x54 matches the key, stopping on return to the list head.
 * @param list Head of a circular list; its links are assumed nonnull.
 * @param key Value compared with the word at offset 0x54.
 * @return The first matching node, or null if none matches.
 */
FieldKeyedListNode54* func_001E8490(FieldKeyedListNode54* list, u32 key);

/**
 * @brief Store the key and float parameters, the fixed value 300.0f, the low flag bits at offset 0xB4 and mode 2.
 * @param object Receiver to configure.
 * @param key Word stored at offset 0x98.
 * @param flags Value merged into the low byte of the halfword at offset 0xB4, preserving its high byte.
 * @param a Float stored at offset 0x9C.
 * @param b Float stored at offset 0xA0.
 * @param c Float stored at offset 0xA8.
 * @param d Float stored at offset 0xB0.
 * @param e Float stored at offset 0xA4.
 */
void func_001E8E00(FieldMotionParams98* object, u32 key, u16 flags, float a, float b, float c, float d, float e);

/**
 * @brief Read the signed halfword at offset 0x3A.
 * @param object Receiver to inspect.
 * @return The stored halfword.
 */
s16 func_001E9380(const FieldHalfword3A* object);

/**
 * @brief Return the receiver unchanged.
 * @param object Receiver to return.
 * @return object.
 */
void* func_001E9E80(void* object);

/**
 * @brief Return the receiver unchanged.
 * @param object Receiver to return.
 * @return object.
 */
void* func_001E9E90(void* object);

/**
 * @brief Update the receiver; func_001EA9B0 calls it after advancing the counter when the gating flags are set.
 * @param object Receiver to process.
 */
void func_001EA730(FieldCounterObjectC0* object);

/**
 * @brief Advance the counter at offset 0xC0, then call func_001EA730 when the pointer at offset 0x30 is set and flag bit 1 at offset 0xC4 is set.
 * @param object Receiver to update.
 */
void func_001EA9B0(FieldCounterObjectC0* object);

/**
 * @brief Test bit 5 of the flag byte at offset 0xA.
 * @param record Record to inspect.
 * @return 1 when the bit is set, otherwise 0.
 */
s32 func_001EB2C0(const FieldPackedRecord0E* record);

/**
 * @brief Read the leading pointer.
 * @param record Record to inspect.
 * @return The stored pointer.
 */
void* func_001EB2D0(const FieldPackedRecord0E* record);

/**
 * @brief Read the signed halfword at offset 0xE.
 * @param record Record to inspect.
 * @return The stored halfword.
 */
s16 func_001EB2E0(const FieldPackedRecord0E* record);

/**
 * @brief Store a count and set the byte flag in the optional target at offset 0x34.
 * @param object Receiver holding the target.
 * @param count Signed count stored at the target's offset 0xFC.
 */
void func_001EB690(FieldCountOwner34* object, s32 count);

/**
 * @brief Test that both pointers at offsets 0x80 and 0x448 are set and bit 5 at offset 0x8C is clear.
 * @param object Receiver to inspect.
 * @return 1 when all conditions hold, otherwise 0.
 */
s32 func_001ECF10(const FieldGatedObject448* object);

/**
 * @brief Clear the entry array pointer, counters and flags, and set both nibbles and the three halfword indices to their initial values.
 * @param object Receiver to reset.
 */
void func_001E94F0(FieldEntryArrayObject30* object);

#ifdef __cplusplus
}
#endif

#endif
