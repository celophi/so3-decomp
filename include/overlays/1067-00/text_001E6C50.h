#ifndef SO3_OVERLAYS_1067_00_TEXT_001E6C50_H
#define SO3_OVERLAYS_1067_00_TEXT_001E6C50_H

#include "types.h"
#include "overlays/1067-00/text_001E1590.h"

/** Partial receiver with three aligned 128-bit slots and a ready byte at offset 0x50. */
typedef struct FieldVectorSlots50
{
    u8 unk00[0x20];
    unsigned __int128 slots[3];
    u8 ready;
} FieldVectorSlots50;

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
/**
 * Partial class derived from FieldClass150070, with vtable D_150220 in boot
 * data. Holds a source record pointer at offset 0x18 and a done flag at bit 0
 * of offset 0x20; slot 8 is pure virtual.
 */
class FieldClass150220 : public FieldClass150070
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass150220()
    {
    }

    /**
     * @brief Store the source record pointer at offset 0x18.
     * @param source Record to store.
     */
    virtual void func_001E6CF0(void* source);

    /**
     * @brief Set flag bit 0 at offset 0x20.
     * @param matrix 4x4 matrix used by the overrides; ignored here.
     */
    virtual void func_001E73D0(const void* matrix);

    /** @brief Clear flag bit 0 at offset 0x20. */
    virtual void func_001E6D00();

    /**
     * @brief Build the object's state from a source record and an optional matrix.
     * @param source Source record, stored at offset 0x18.
     * @param matrix Optional 4x4 matrix.
     * @param scale Scale factor; ignored by FieldClass150250.
     */
    virtual void func_001E6D80(void* source, const void* matrix, float scale) = 0;

    u8 unk14[4];
    void* unk18;
    u8 unk1c[4];
    u8 unk20_0 : 1;
    u8 unk20_1_7 : 7;
};

/** Partial class derived from FieldClass150220, with vtable D_1501F0 in boot data. */
class FieldClass1501F0 : public FieldClass150220
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass1501F0();

    /**
     * @brief Unless flag bit 0 at offset 0x20 is set, pass the matrix and the vectors at offsets 0x1C0 and 0x1D0 to func_433730, then set the flag.
     * @param matrix 4x4 matrix.
     */
    virtual void func_001E73D0(const void* matrix);

    /**
     * @brief Build the vectors at offset 0x30 and 0x1C0 from a source record and an optional matrix.
     * @param source Source record, stored at offset 0x18.
     * @param matrix Optional 4x4 matrix.
     * @param scale Scale applied to the source's first float.
     */
    virtual void func_001E6D80(void* source, const void* matrix, float scale);
};

/** One 16-byte record of four floats. */
struct FieldFloat4
{
    float unk00;
    float unk04;
    float unk08;
    float unk0c;
};

/** Partial class derived from FieldClass150220 with six 16-byte records at offset 0x130, with vtable D_150250 in boot data. */
class FieldClass150250 : public FieldClass150220
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass150250();

    /**
     * @brief Unless flag bit 0 at offset 0x20 is set, transform the eight vectors at offset 0x30 and the vector at offset 0x190 by the matrix, then set the flag.
     * @param matrix 4x4 matrix.
     */
    virtual void func_001E73D0(const void* matrix);

    /** @brief Clear flag bit 0 at offset 0x20 and the last float of each record at offset 0x130. */
    virtual void func_001E6D00();

    /**
     * @brief Build the eight corner vectors at offset 0x30 from a source record, optionally transformed by a matrix.
     * @param source Source record, stored at offset 0x18.
     * @param matrix Optional 4x4 matrix.
     * @param scale Unused by this class.
     */
    virtual void func_001E6D80(void* source, const void* matrix, float scale);

    u8 unk24[0x10C];
    FieldFloat4 unk130[6];
};

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
    virtual ~FieldClass150460()
    {
    }
};

/** Partial class derived from FieldClass150460, with vtable D_150490 in boot data. */
class FieldClass150490 : public FieldClass150460
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass150490()
    {
    }
};

/**
 * Partial class derived from FieldClass150490, with vtable D_1504C0 in boot
 * data. Owns a list of FieldClass150070 objects at offset 0x38.
 */
class FieldClass1504C0 : public FieldClass150490
{
public:
    /** @brief Detach and delete every object in the list at offset 0x38, then destroy the object. */
    virtual ~FieldClass1504C0();

    /** @brief Detach the object and queue it on the resident object queue. */
    virtual void func_001DD7B0();

    /** @brief Advance the counter at offset 0xC0, then call func_001EA730 when the pointer at offset 0x30 and flag bit 1 at offset 0xC4 are set. */
    virtual void func_001DF360();

    /** @brief Update the object; func_001DF360 calls it after advancing the counter when the gating flags are set. */
    void func_001EA730();

    u8 unk14[0x1C];
    void* unk30;
    u8 unk34[4];
    LibClass178DD0 unk38;
    u8 unkb0[0x10];
    s32 unkc0;
    u8 unkc4_0 : 1;
    u8 unkc4_1 : 1;
    u8 unkc4_2_7 : 6;
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Mark the receiver ready and copy a 128-bit value into slot 0.
 * @param object Receiver containing the slots.
 * @param value Value to copy.
 */
void func_001E7E90(FieldVectorSlots50* object, const unsigned __int128* value);

/**
 * @brief Mark the receiver ready and copy a 128-bit value into slot 2.
 * @param object Receiver containing the slots.
 * @param value Value to copy.
 */
void func_001E7EB0(FieldVectorSlots50* object, const unsigned __int128* value);

/**
 * @brief Mark the receiver ready and copy a 128-bit value into slot 1.
 * @param object Receiver containing the slots.
 * @param value Value to copy.
 */
void func_001E7ED0(FieldVectorSlots50* object, const unsigned __int128* value);

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
