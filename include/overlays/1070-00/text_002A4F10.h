#ifndef SO3_OVERLAYS_1070_00_TEXT_002A4F10_H
#define SO3_OVERLAYS_1070_00_TEXT_002A4F10_H

#include "overlays/1070-00/text_001E2B40.h"

/** Partial resource list entry with its size, keys and observed flag byte. */
typedef struct FieldResourceListEntry
{
    FieldListNode link;
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
    FieldListNode unk14;
} FieldResourceList14;

/** Opaque source whose float scale values are read by the entry update. */
typedef struct FieldScaleSource296670 FieldScaleSource296670;
/** Opaque aligned entry in the update buffer. */
typedef struct FieldScaleEntry296670 FieldScaleEntry296670;

/** Partial mask receiver containing its array of 64-bit group flags. */
typedef struct FieldScaleMask296670
{
    u8 unk00[8];
    const u64* unk08;
} FieldScaleMask296670;

/** Partial receiver initialized by func_002B47D0. */
typedef struct FieldResetState24
{
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u16 unk0c;
    u16 unk0e;
    u16 unk10;
    u8 unk12[2];
    u32 unk14;
    u32 unk18;
    u32 unk1c;
    u32 unk20;
    void* unk24;
} FieldResetState24;

#ifdef __cplusplus
class FieldVector1FAD90;

/** Partial destruction interface of the particle allocator ancestor. */
class FieldClass16CF78 : public FieldClass16AB70
{
public:
    /** Destroy the allocator-family receiver. */
    virtual ~FieldClass16CF78();
    /** Allocate from the particle allocator, recording the caller's line and file. */
    static void* operator new(u32 size, s32 line, const char* file);
    /** Release storage obtained from the particle allocator. */
    static void operator delete(void* object);
    /** Placement delete matching the debug operator new; does nothing. */
    static void operator delete(void* object, s32 line, const char* file)
    {
    }
    u8 unk04;
    u8 unk05[0x13];
};

/** Partial destruction interface of the particle receiver base. */
class FieldClass16CF90 : public FieldClass16CF78
{
public:
    /** Destroy the receiver base. */
    virtual ~FieldClass16CF90();
};

/** Partial destruction interface with primary vtable at 0x173A80. */
class FieldClass173A80 : public FieldClass16CF90
{
public:
    /** Construct the receiver and its bases. */
    FieldClass173A80();
    /** Destroy the receiver and release its owned storage. */
    virtual ~FieldClass173A80();
    u8 unk18[0x18];
};

/** Partial destruction interface with primary vtable at 0x1739B0. */
class FieldClass1739B0 : public FieldClass16CF90
{
public:
    /** Construct the receiver and its bases. */
    FieldClass1739B0();
    /** Destroy the receiver and release its owned storage. */
    virtual ~FieldClass1739B0();
    u8 unk18[0x18];
};

/** Partial destruction interface with primary vtable at 0x1738E0. */
class FieldClass1738E0 : public FieldClass16CF90
{
public:
    /** Construct the receiver and its bases. */
    FieldClass1738E0();
    /** Destroy the receiver and release its owned storage. */
    virtual ~FieldClass1738E0();
    u8 unk18[0x18];
};

/** Partial destruction interface with primary vtable at 0x173810. */
class FieldClass173810 : public FieldClass16CF90
{
public:
    /** Construct the receiver and its bases. */
    FieldClass173810();
    /** Destroy the receiver and release its owned storage. */
    virtual ~FieldClass173810();
    u8 unk18[0x18];
};

/** Partial destruction interface with primary vtable at 0x173B50. */
class FieldClass173B50 : public FieldClass16CF90
{
public:
    /** Construct the receiver and its bases. */
    FieldClass173B50();
    /** Destroy the receiver and release its callback registrations. */
    virtual ~FieldClass173B50();
    u8 unk18[0x18];
};

/** Partial destruction interface with primary vtable at 0x1735E0. */
class FieldClass1735E0 : public FieldClass173B50
{
public:
    /** Initialize the shared particle state. */
    FieldClass1735E0()
    {
        unk38 = 1.0f;
        unk44 = 0;
        unk48 = 0;
        unk4c = 0;
        unk4d = 0;
        unk4f = 1;
        unk50 = 0;
        unk55 = 1;
        unk56 = 0;
        unk57 = 0;
        unk04 = 1;
    }
    /** Destroy the receiver through its primary base. */
    virtual ~FieldClass1735E0()
    {
    }
    float unk30;
    u8 unk34[4];
    float unk38;
    u8 unk3c[8];
    u32 unk44;
    u32 unk48;
    u8 unk4c;
    u8 unk4d;
    u8 unk4e;
    u8 unk4f;
    u32 unk50;
    u8 unk54;
    u8 unk55;
    u8 unk56;
    u8 unk57;
};

/** Partial destruction interface with primary vtable at 0x1736B0. */
class FieldClass1736B0 : public FieldClass1735E0
{
public:
    /** Construct the receiver with empty particle arrays. */
    FieldClass1736B0();
    /** Destroy the receiver and release its owned storage. */
    virtual ~FieldClass1736B0();
    u8 unk58[0x58];
    u8* unkb0;
    FieldVector1FAD90* unkb4;
    u32 unkb8;
    u32 unkbc;
    s32 unkc0;
    s32 unkc4;
    u8 unkc8;
    u8 unkc9;
};

#endif

#ifdef __cplusplus
extern "C" {
void* func_002A8E50(void* receiver);

void func_002B0A50(void* object, void* cell, void* row, s32 index, void* extra4, void* extra5, void* extra6, void* extra7, void* extra8);

/** @brief Copy two words to the receiver, then pass them to its callback. */
void func_002B0950(void* object, const void* source);

/** @brief Copy two words to the receiver, then pass them to its callback. */
void func_002B0990(void* object, const void* source);

/** @brief Copy two words to the receiver, then pass them to its callback. */
void func_002B09D0(void* object, const void* source);

/**
 * @brief Copy two words to the receiver, then pass them to its callback.
 * @param object Receiver with words at offsets 0x0C and 0x10.
 * @param source Source of the words to copy.
 */
void func_002B0A10(void* object, const void* source);

/**
 * @brief Copy two words to the receiver, then pass them to its callback.
 * @param object Receiver with words at offsets 0x0C and 0x10.
 * @param source Source of the words to copy.
 */
void func_002B26C0(void* object, const void* source);

/**
 * @brief Initialize the receiver, then pass it to the shared owner.
 * @param object Receiver to initialize and process.
 */
void func_002B2710(void* object);

/**
 * @brief Initialize the receiver, then pass it to the shared owner.
 * @param object Receiver to initialize and process.
 */
void func_002B3410(void* object);

/** @brief Forward the receiver and shared owner to the common helper. */
void func_002B4540(void* object);

/**
 * @brief Initialize the observed state fields and return the receiver.
 * @param object Receiver to initialize.
 * @return object.
 */
FieldResetState24* func_002B47D0(FieldResetState24* object);

/**
 * @brief Set bit zero of the child halfword at offset 0x6C when present.
 * @param object Receiver containing the child pointer at offset 0x1B4.
 */
void func_002B3800(void* object);

/**
 * @brief Clear bit zero of the child halfword at offset 0x6C when present.
 * @param object Receiver containing the child pointer at offset 0x1B4.
 */
void func_002B3820(void* object);

/**
 * @brief Clear destination word 0x2C and copy four 128-bit values from offset 0x150.
 * @param destination Receiver whose four values are updated.
 * @param source Object containing the source values.
 */
void func_002A5220(void* destination, const void* source);

/**
 * @brief Clear destination word 0x2C and copy four 128-bit values from offset 0x150.
 * @param destination Receiver whose four values are updated.
 * @param source Object containing the source values.
 */
void func_002B0920(void* destination, const void* source);
#endif

/**
 * @brief Initialize the particle arrays and their group mask.
 * @param object Receiver whose arrays are initialized.
 * @param count Number of groups.
 * @param group_size Number of entries per group.
 */
void func_002AA770(void* object, s32 count, s32 group_size);

/**
 * @brief Initialize the particle arrays and their group mask.
 * @param object Receiver whose arrays are initialized.
 * @param count Number of groups.
 * @param group_size Number of entries per group.
 */
void func_002A97A0(void* object, s32 count, s32 group_size);

/**
 * @brief Initialize the particle arrays and their group mask.
 * @param object Receiver whose arrays are initialized.
 * @param count Number of groups.
 * @param group_size Number of entries per group.
 */
void func_002A9F70(void* object, s32 count, s32 group_size);

/**
 * @brief Initialize the particle arrays and their group mask.
 * @param object Receiver whose arrays are initialized.
 * @param count Number of groups.
 * @param group_size Number of entries per group.
 */
void func_002A8FF0(void* object, s32 count, s32 group_size);

/**
 * @brief Initialize the particle arrays and their group mask.
 * @param object Receiver whose arrays are initialized.
 * @param count Number of groups.
 * @param group_size Number of entries per group.
 */
void func_002A88E0(void* object, s32 count, s32 group_size);

/**
 * @brief Update the particle entries belonging to the receiver.
 * @param object Receiver containing group state and arrays.
 * @param count Number of entries to update.
 * @param entries Entry buffer.
 */
void func_002AC070(void* object, s32 count, FieldScaleEntry296670* entries);

/**
 * @brief Update the particle entries belonging to the receiver.
 * @param object Receiver containing group state and arrays.
 * @param count Number of entries to update.
 * @param entries Entry buffer.
 */
void func_002AC920(void* object, s32 count, FieldScaleEntry296670* entries);

/**
 * @brief Update the particle entries belonging to the receiver.
 * @param object Receiver containing group state and arrays.
 * @param count Number of entries to update.
 * @param entries Entry buffer.
 */
void func_002AB800(void* object, s32 count, FieldScaleEntry296670* entries);

/**
 * @brief Update the particle entries belonging to the receiver.
 * @param object Receiver containing group state and arrays.
 * @param count Number of entries to update.
 * @param entries Entry buffer.
 */
void func_002AAF90(void* object, s32 count, FieldScaleEntry296670* entries);


/**
 * @brief Find the size selected by a resource entry's flag.
 * @param object Resource list to search.
 * @param kind Resource kind to match.
 * @param key Resource key to match.
 * @return The selected size, or zero when no matching entry exists.
 */
u32 func_002B3140(FieldResourceList14* object, u32 kind, u32 key);

/**
 * @brief Count flagged resource entries matching either of two kind and key conditions.
 * @param object Resource list to search.
 * @param first Low-halfword key for kinds 0x43484152 and 0x41545243.
 * @param second Low-halfword key for kind 0x414E494D.
 * @return Number of flagged entries with a matching kind and key.
 */
s32 func_002B2950(FieldResourceList14* object, s32 first, s32 second);

/**
 * @brief Decrement counters for matching resource entries that pass their flag checks.
 * @param object Resource list to update.
 * @param first Low-halfword key for kinds 0x43484152 and 0x41545243.
 * @param second Low-halfword key for kind 0x414E494D.
 */
void func_002B29F0(FieldResourceList14* object, s32 first, s32 second);

/**
 * @brief Increment counters for matching resource entries that pass their flag checks.
 * @param object Resource list to update.
 * @param first Low-halfword key for kinds 0x43484152 and 0x41545243.
 * @param second Low-halfword key for kind 0x414E494D.
 */
void func_002B2AB0(FieldResourceList14* object, s32 first, s32 second);

/**
 * @brief Write the float field at offset 0x28.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A5010(u8* object, float value);

/**
 * @brief Write the float field at offset 0x30.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A5020(u8* object, float value);

/**
 * @brief Read the float field at offset 0x30.
 * @param object Object containing the field.
 * @return Field value.
 */
float func_002A5030(u8* object);

/**
 * @brief Write the u8 field at offset 0x4D.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A5040(u8* object, u8 value);

/**
 * @brief Read the u8 field at offset 0x4D.
 * @param object Object containing the field.
 * @return Field value.
 */
u8 func_002A5050(u8* object);

/**
 * @brief Write the float field at offset 0x34.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A5060(u8* object, float value);

/**
 * @brief Write the u8 field at offset 0x56.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A5070(u8* object, u8 value);

/**
 * @brief Read the u8 field at offset 0x56.
 * @param object Object containing the field.
 * @return Field value.
 */
u8 func_002A5080(u8* object);

/**
 * @brief Write the float field at offset 0x44.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A5090(u8* object, float value);

/**
 * @brief Read the float field at offset 0x44.
 * @param object Object containing the field.
 * @return Field value.
 */
float func_002A50A0(u8* object);

/**
 * @brief Read the float field at offset 0x28.
 * @param object Object containing the field.
 * @return Field value.
 */
float func_002A50B0(u8* object);

/**
 * @brief Write the u32 field at offset 0x48.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A50C0(u8* object, u32 value);

/**
 * @brief Read the u32 field at offset 0x48.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A50D0(u8* object);

/**
 * @brief Write the u8 field at offset 0x4F.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A50E0(u8* object, u8 value);

/**
 * @brief Write the u8 field at offset 0x4E.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A50F0(u8* object, u8 value);

/**
 * @brief Write the u32 field at offset 0x50.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A5100(u8* object, u32 value);

/**
 * @brief Read the u32 field at offset 0x50.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A5110(u8* object);

/**
 * @brief Write the u8 field at offset 0x55.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A5120(u8* object, u8 value);

/**
 * @brief Write the float field at offset 0x3C.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A5130(u8* object, float value);

/**
 * @brief Write the u8 field at offset 0x54.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A5140(u8* object, u8 value);

/**
 * @brief Write the float field at offset 0x40.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A5150(u8* object, float value);

/**
 * @brief Save the input pointer and value, then set the state byte if input begins with one.
 * @param object Particle state receiver.
 * @param input Input bytes whose first byte controls state byte 0x57.
 * @param value Value saved at receiver offset 0xA4.
 */
void func_002A5160(void* object, const u8* input, u32 value);

/**
 * @brief Save the input pointer and value, then set state byte 0x57 if input begins with one.
 * @param object Particle state receiver.
 * @param input Input bytes whose first byte controls the state byte.
 * @param value Value saved at receiver offset 0xA4.
 */
void func_002A83D0(void* object, const u8* input, u32 value);

/**
 * @brief Write the float field at offset 0x38.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A51D0(u8* object, float value);

/**
 * @brief Write the float field at offset 0x28.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A8280(u8* object, float value);

/**
 * @brief Write the float field at offset 0x30.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A8290(u8* object, float value);

/**
 * @brief Read the float field at offset 0x30.
 * @param object Object containing the field.
 * @return Field value.
 */
float func_002A82A0(u8* object);

/**
 * @brief Write the u8 field at offset 0x4D.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A82B0(u8* object, u8 value);

/**
 * @brief Read the u8 field at offset 0x4D.
 * @param object Object containing the field.
 * @return Field value.
 */
u8 func_002A82C0(u8* object);

/**
 * @brief Write the float field at offset 0x34.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A82D0(u8* object, float value);

/**
 * @brief Write the u8 field at offset 0x56.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A82E0(u8* object, u8 value);

/**
 * @brief Read the u8 field at offset 0x56.
 * @param object Object containing the field.
 * @return Field value.
 */
u8 func_002A82F0(u8* object);

/**
 * @brief Write the float field at offset 0x44.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A8300(u8* object, float value);

/**
 * @brief Read the float field at offset 0x44.
 * @param object Object containing the field.
 * @return Field value.
 */
float func_002A8310(u8* object);

/**
 * @brief Read the float field at offset 0x28.
 * @param object Object containing the field.
 * @return Field value.
 */
float func_002A8320(u8* object);

/**
 * @brief Write the u32 field at offset 0x48.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A8330(u8* object, u32 value);

/**
 * @brief Read the u32 field at offset 0x48.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A8340(u8* object);

/**
 * @brief Write the u8 field at offset 0x4F.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A8350(u8* object, u8 value);

/**
 * @brief Write the u8 field at offset 0x4E.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A8360(u8* object, u8 value);

/**
 * @brief Write the u32 field at offset 0x50.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A8370(u8* object, u32 value);

/**
 * @brief Read the u32 field at offset 0x50.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A8380(u8* object);

/**
 * @brief Write the u8 field at offset 0x55.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A8390(u8* object, u8 value);

/**
 * @brief Write the float field at offset 0x3C.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A83A0(u8* object, float value);

/**
 * @brief Write the u8 field at offset 0x54.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A83B0(u8* object, u8 value);

/**
 * @brief Write the float field at offset 0x40.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A83C0(u8* object, float value);

/**
 * @brief Write the float field at offset 0x38.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A8440(u8* object, float value);

/**
 * @brief Clear two counters and set the enabled byte.
 * @param object Object containing the fields.
 * @param enabled Whether to set the enabled byte.
 */
void func_002A51A0(u8* object, u32 enabled);

/**
 * @brief Clear two counters and set the enabled byte.
 * @param object Object containing the fields.
 * @param enabled Whether to set the enabled byte.
 */
void func_002A8410(u8* object, u32 enabled);

/**
 * @brief Return the fixed value 1.0f.
 * @param object Receiver or first argument; unused.
 * @return Always 1.0f.
 */
float func_002B2680(void* object);

/**
 * @brief Return the fixed value 1.0f.
 * @param object Receiver or first argument; unused.
 * @return Always 1.0f.
 */
float func_002B2690(void* object);

/**
 * @brief Return the fixed value 1.0f.
 * @param object Receiver or first argument; unused.
 * @return Always 1.0f.
 */
float func_002B26A0(void* object);

/**
 * @brief Return the fixed value 1.0f.
 * @param object Receiver or first argument; unused.
 * @return Always 1.0f.
 */
float func_002B26B0(void* object);

/**
 * @brief Return the fixed value 1.0f.
 * @param object Receiver or first argument; unused.
 * @return Always 1.0f.
 */
float func_002B2700(void* object);

/**
 * @brief Read the word at offset 0x1C.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A84D0(u8* object);

/**
 * @brief Read the word at offset 0xC.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A84E0(u8* object);

/**
 * @brief Read the word at offset 0x10.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A84F0(u8* object);

/**
 * @brief Read the word at offset 0x1C.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A85C0(u8* object);

/**
 * @brief Read the word at offset 0xC.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A85D0(u8* object);

/**
 * @brief Read the word at offset 0x10.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A85E0(u8* object);

/**
 * @brief Read the word at offset 0x1C.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A86B0(u8* object);

/**
 * @brief Read the word at offset 0xC.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A86C0(u8* object);

/**
 * @brief Read the word at offset 0x10.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A86D0(u8* object);

/**
 * @brief Read the word at offset 0x1C.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A87A0(u8* object);

/**
 * @brief Read the word at offset 0xC.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A87B0(u8* object);

/**
 * @brief Read the word at offset 0x10.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A87C0(u8* object);

/**
 * @brief Read the word at offset 0x1C.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A8890(u8* object);

/**
 * @brief Read the word at offset 0xC.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A88A0(u8* object);

/**
 * @brief Read the word at offset 0x10.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A88B0(u8* object);

/**
 * @brief Test whether the word at offset 0x14 is nonzero.
 * @param object Object containing the field.
 * @return One if the word is nonzero, otherwise zero.
 */
s32 func_002A8510(u8* object);

/**
 * @brief Test whether the word at offset 0x14 is nonzero.
 * @param object Object containing the field.
 * @return One if the word is nonzero, otherwise zero.
 */
s32 func_002A8600(u8* object);

/**
 * @brief Test whether the word at offset 0x14 is nonzero.
 * @param object Object containing the field.
 * @return One if the word is nonzero, otherwise zero.
 */
s32 func_002A86F0(u8* object);

/**
 * @brief Test whether the word at offset 0x14 is nonzero.
 * @param object Object containing the field.
 * @return One if the word is nonzero, otherwise zero.
 */
s32 func_002A87E0(u8* object);

/**
 * @brief Test whether the word at offset 0x14 is nonzero.
 * @param object Object containing the field.
 * @return One if the word is nonzero, otherwise zero.
 */
s32 func_002A88D0(u8* object);

/**
 * @brief Return an entry address using a stride of 368 bytes.
 * @param object Object holding the entry pointer at offset 0x14.
 * @param index Entry index.
 * @return Address of the indexed entry.
 */
u8* func_002A8490(u8* object, s32 index);

/**
 * @brief Return an entry address using a stride of 288 bytes.
 * @param object Object holding the entry pointer at offset 0x14.
 * @param index Entry index.
 * @return Address of the indexed entry.
 */
u8* func_002A8580(u8* object, s32 index);

/**
 * @brief Return an entry address using a stride of 176 bytes.
 * @param object Object holding the entry pointer at offset 0x14.
 * @param index Entry index.
 * @return Address of the indexed entry.
 */
u8* func_002A8670(u8* object, s32 index);

/**
 * @brief Return an entry address using a stride of 144 bytes.
 * @param object Object holding the entry pointer at offset 0x14.
 * @param index Entry index.
 * @return Address of the indexed entry.
 */
u8* func_002A8760(u8* object, s32 index);

/**
 * @brief Return an entry address using a stride of 96 bytes.
 * @param object Object holding the entry pointer at offset 0x14.
 * @param index Entry index.
 * @return Address of the indexed entry.
 */
u8* func_002A8850(u8* object, s32 index);

/**
 * @brief Return the element subobject at offset 0x30 from a 96-byte-stride entry.
 * @param object Object holding the entry pointer at offset 0x14.
 * @param index Entry index.
 * @return Address of the selected subobject, or null when its computed address is null.
 */
u8* func_002A7D40(u8* object, s32 index);

/**
 * @brief Return an entry address from row and column indices.
 * @param object Object holding the row width and entry pointer.
 * @param row Row index.
 * @param column Column index.
 * @return Address of the selected 64-byte entry.
 */
u8* func_002A84B0(u8* object, s32 row, s32 column);

/**
 * @brief Return an entry address from row and column indices.
 * @param object Object holding the row width and entry pointer.
 * @param row Row index.
 * @param column Column index.
 * @return Address of the selected 64-byte entry.
 */
u8* func_002A85A0(u8* object, s32 row, s32 column);

/**
 * @brief Return an entry address from row and column indices.
 * @param object Object holding the row width and entry pointer.
 * @param row Row index.
 * @param column Column index.
 * @return Address of the selected 64-byte entry.
 */
u8* func_002A8690(u8* object, s32 row, s32 column);

/**
 * @brief Return an entry address from row and column indices.
 * @param object Object holding the row width and entry pointer.
 * @param row Row index.
 * @param column Column index.
 * @return Address of the selected 64-byte entry.
 */
u8* func_002A8780(u8* object, s32 row, s32 column);

/**
 * @brief Return an entry address from row and column indices.
 * @param object Object holding the row width and entry pointer.
 * @param row Row index.
 * @param column Column index.
 * @return Address of the selected 64-byte entry.
 */
u8* func_002A8870(u8* object, s32 row, s32 column);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A51E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A51F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A5200(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A5210(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A5250(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002A7D30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A8450(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A8460(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A8470(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A8480(void* object);

/**
 * @brief Return the fixed value 63.
 * @param object Receiver or first argument; unused.
 * @return Always 63.
 */
s32 func_002A8500(void* object);

/**
 * @brief Return the fixed value 47.
 * @param object Receiver or first argument; unused.
 * @return Always 47.
 */
s32 func_002A85F0(void* object);

/**
 * @brief Return the fixed value 39.
 * @param object Receiver or first argument; unused.
 * @return Always 39.
 */
s32 func_002A86E0(void* object);

/**
 * @brief Return the fixed value 35.
 * @param object Receiver or first argument; unused.
 * @return Always 35.
 */
s32 func_002A87D0(void* object);

/**
 * @brief Return the fixed value 33.
 * @param object Receiver or first argument; unused.
 * @return Always 33.
 */
s32 func_002A88C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B0AB0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002B0AC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B1B10(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B1B20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B1B30(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B1B40(void* object);

/**
 * @brief Return the fixed value 12.
 * @param object Receiver or first argument; unused.
 * @return Always 12.
 */
s32 func_002B3440(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002B3640(void* object);

/**
 * @brief Set the receiver's byte at offset 0x60 to four.
 * @param object Receiver to update.
 */
void func_002B4510(void* object);

/**
 * @brief Return the fixed value 14.
 * @param object Receiver or first argument; unused.
 * @return Always 14.
 */
s32 func_002B4520(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B4530(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B4560(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B4570(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B4810(void* object);

/**
 * @brief Clear four output state bytes, then update the output block from the receiver.
 * @param object Receiver used to update the output.
 * @param output Output block whose bytes at 0x130 through 0x133 are cleared.
 */
void func_002B0A80(void* object, void* output);

#ifdef __cplusplus
}
#endif

#endif
