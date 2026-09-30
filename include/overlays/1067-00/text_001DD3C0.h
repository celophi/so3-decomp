#ifndef SO3_OVERLAYS_1067_00_TEXT_001DD3C0_H
#define SO3_OVERLAYS_1067_00_TEXT_001DD3C0_H

#include "types.h"
#include "overlays/0002-01/text_004CD3A0.h"
#include "overlays/1067-00/text_001FD860.h"

/** Partial receiver whose word at offset 0x70 refers to an attached object. */
typedef struct FieldAttachedObject70
{
    u8 unk00[0x70];
    void* unk70;
} FieldAttachedObject70;

/** Partial object linked into a circular list, with flag and state words. */
typedef struct FieldFlaggedListObject
{
    u8 unk00[8];
    struct FieldFlaggedListObject* next;
    u8 unk0c[0x64];
    s32 unk70;
    s32 unk74;
    u32 unk78;
    void* unk7c;
    u8 unk80[0xC];
    u8 unk8c_0_1 : 2;
    u8 unk8c_2 : 1;
    u8 unk8c_3_7 : 5;
    u8 unk8d[0x17B];
    u32 unk208;
} FieldFlaggedListObject;

/** Partial 32-byte record reset by func_001DEA80. */
typedef struct FieldSlotRecord20
{
    u8 unk00[4];
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
    u8 unk17[9];
} FieldSlotRecord20;

/** Partial receiver owning a counted array of 32-byte records at offset 0x1C. */
typedef struct FieldSlotRecordOwner
{
    u8 unk00[0x1C];
    FieldSlotRecord20* unk1c;
    u32 unk20;
    s32 unk24;
    u8 unk28[5];
    u8 unk2d;
    u8 unk2e;
    u8 unk2f;
} FieldSlotRecordOwner;

#ifdef __cplusplus
/** Root of the FieldClass150070 hierarchy, with vtable D_150050 in boot data. */
class FieldClass150050
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass150050();
};

/** Intermediate base with only a destructor, with vtable D_150060 in boot data. */
class FieldClass150060 : public FieldClass150050
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass150060();
};

/** Base class with four virtual handlers, with vtable D_150070 in boot data. */
class FieldClass150070 : public FieldClass150060
{
public:
    /** @brief Detach the object from the owner at offset 0x10, then destroy it. */
    virtual ~FieldClass150070();

    /**
     * @brief Report the fixed value 3 for this class.
     * @return Always 3.
     */
    virtual s32 func_001DF3D0();

    /** @brief Delete the object through its virtual destructor. */
    virtual void func_001DD7B0();

    /** @brief Default handler that performs no work. */
    virtual void func_001DF360();

    /** @brief Default handler that performs no work. */
    virtual void func_001DD410();

    u8 unk04[0x14];
};

/** Partial 16-byte base class whose first virtual handler is func_001DD400. */
class FieldClass1DD400
{
public:
    /** @brief Default handler that performs no work. */
    virtual void func_001DD400();

    u8 unk04[0xC];
};

/** Partial class with bases at offsets 0x78 and 0x90 and a Lib member at 0xA0, with vtable D_14FE30 in boot data. */
class FieldClass14FE30 : public LibClass178DD0, public FieldClass150070, public FieldClass1DD400
{
public:
    /** @brief Detach the member at offset 0xA0, then destroy the object. */
    virtual ~FieldClass14FE30();

    /** @brief Detach the FieldClass150070 base and queue it on the resident object queue. */
    virtual void func_001DD7B0();

    LibClass178EA0 unkA0;
};

/** Partial class derived from FieldClass150070, with vtable D_150010 in boot data. */
class FieldClass150010 : public FieldClass150070
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass150010();

    /**
     * @brief Report the fixed value 3 for this class.
     * @return Always 3.
     */
    virtual s32 func_001DF3D0();

    /** @brief Detach the object and queue it on the resident object queue. */
    virtual void func_001DD7B0();
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Store the attached object pointer at offset 0x70.
 * @param object Receiver to update.
 * @param attached Object pointer to store.
 */
void func_001DD420(FieldAttachedObject70* object, void* attached);

/**
 * @brief Default virtual handler that performs no work.
 * @param object Receiver of the virtual call.
 */
void func_001DD430(void* object);

/**
 * @brief Report the fixed value 4 for this receiver class.
 * @param object Receiver of the virtual call.
 * @return Always 4.
 */
s32 func_001DD490(const void* object);

/**
 * @brief Call func_002379A0 with a nonzero flag for each listed object whose flag bit 3 is set.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 */
void func_001DD570(FieldFlaggedListObject* list);

/**
 * @brief Clear the word at offset 0x208 for each listed object whose flag bit 1 is set.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 */
void func_001DD6E0(FieldFlaggedListObject* list);

/**
 * @brief Call func_00227130 for each listed object whose flag bit 1 is set.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 */
void func_001DDB30(FieldFlaggedListObject* list);

/**
 * @brief Return the receiver unchanged.
 * @param object Receiver of the virtual call.
 * @return object.
 */
void* func_001DDCD0(void* object);

/**
 * @brief Combine the func_00204420 test with a clear bit 5 at offset 0x8C.
 * @param object Receiver passed to func_00204420.
 * @return True when func_00204420 succeeds and bit 5 of the byte at offset 0x8C is clear.
 */
bool func_001DDCE0(const FieldFloatGateState7C* object);

/**
 * @brief Find a listed object with a matching key, bit 2 at offset 0x8C clear and a nonnull pointer at offset 0x7C.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 * @param key Value compared with the word at offset 0x74.
 * @return The first matching object, or null if none matches.
 */
FieldFlaggedListObject* func_001DDF50(FieldFlaggedListObject* list, s32 key);

/**
 * @brief Default virtual handler that performs no work.
 * @param object Receiver of the virtual call.
 */
void func_001DE3B0(void* object);

/**
 * @brief Default virtual handler that performs no work.
 * @param object Receiver of the virtual call.
 */
void func_001DE3C0(void* object);

/**
 * @brief Reset every 32-byte record in the counted array at offset 0x1C, then clear the word at offset 0x20 and the bytes at offsets 0x2D-0x2F.
 * @param object Receiver owning the records; the loop is skipped when the array pointer is null.
 */
void func_001DEA80(FieldSlotRecordOwner* object);

#ifdef __cplusplus
}
#endif

#endif
