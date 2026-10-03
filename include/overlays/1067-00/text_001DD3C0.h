#ifndef SO3_OVERLAYS_1067_00_TEXT_001DD3C0_H
#define SO3_OVERLAYS_1067_00_TEXT_001DD3C0_H

#include "types.h"
#include "overlays/0002-01/text_004CD3A0.h"
#include "overlays/1067-00/text_001FD860.h"
#include "overlays/1067-00/text_0022DC70.h"

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

#ifdef __cplusplus
/**
 * 16-byte aligned four-float vector. Assignment copies all 16 bytes with one
 * 128-bit load and store.
 */
class FieldVec4A
{
public:
    /** @brief Leave the components uninitialized. */
    FieldVec4A()
    {
    }

    /**
     * @brief Set the four components.
     * @param px First component.
     * @param py Second component.
     * @param pz Third component.
     * @param pw Fourth component.
     */
    FieldVec4A(float px, float py, float pz, float pw)
    {
        x = px;
        y = py;
        z = pz;
        w = pw;
    }

    /**
     * @brief Copy all four components.
     * @param other Vector to copy.
     * @return This vector.
     */
    FieldVec4A& operator=(const FieldVec4A& other)
    {
        *(unsigned __int128*)this = *(const unsigned __int128*)&other;
        return *this;
    }

    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16)));

/**
 * Second 16-byte aligned four-float vector type. It has a copy constructor and
 * its assignment from FieldVec4A returns a copy, which leaves a 16-byte stack
 * temporary in the caller.
 */
class FieldVec4B
{
public:
    /** @brief Leave the components uninitialized; defined out of line in text_001E6C50. */
    FieldVec4B();

    /**
     * @brief Copy all four components.
     * @param other Vector to copy.
     */
    FieldVec4B(const FieldVec4B& other)
    {
        *(unsigned __int128*)this = *(const unsigned __int128*)&other;
    }

    /**
     * @brief Set the four components.
     * @param px First component.
     * @param py Second component.
     * @param pz Third component.
     * @param pw Fourth component.
     */
    FieldVec4B(float px, float py, float pz, float pw)
    {
        x = px;
        y = py;
        z = pz;
        w = pw;
    }

    /**
     * @brief Copy all four components from a FieldVec4A.
     * @param other Vector to copy.
     */
    FieldVec4B(const FieldVec4A& other)
    {
        *(unsigned __int128*)this = *(const unsigned __int128*)&other;
    }

    /**
     * @brief Copy all four components from a FieldVec4A.
     * @param other Vector to copy.
     * @return A copy of this vector.
     */
    /**
     * @brief Copy all four components from a FieldVec4A without returning a copy.
     * @param other Vector to copy.
     */
    void set(const FieldVec4A& other)
    {
        *(unsigned __int128*)this = *(const unsigned __int128*)&other;
    }

    FieldVec4B operator=(const FieldVec4A& other)
    {
        *(unsigned __int128*)this = *(const unsigned __int128*)&other;
        return *this;
    }

    /**
     * @brief Scale all four components.
     * @param scale Factor to multiply by.
     * @return A copy of this vector.
     */
    FieldVec4B operator*=(float scale)
    {
        x *= scale;
        y *= scale;
        z *= scale;
        w *= scale;
        return *this;
    }

    /**
     * @brief Add the first three components of another vector.
     * @param other Vector to add.
     * @return A copy of this vector.
     */
    FieldVec4B add(const FieldVec4A& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    /**
     * @brief Add the first three components of another vector.
     * @param other Vector to add.
     * @return A copy of this vector.
     */
    FieldVec4B operator+=(const FieldVec4A& other)
    {
        add(other);
        return *this;
    }

    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16)));

/** Root of the FieldClass150070 hierarchy, with vtable D_150050 in boot data. */
class FieldClass150050
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass150050()
    {
    }
};

/** Intermediate base with two list links, with vtable D_150060 in boot data. */
class FieldClass150060 : public FieldClass150050
{
public:
    /** @brief Clear the link words. */
    FieldClass150060()
    {
        unk04 = 0;
        unk08 = 0;
    }

    /** @brief Destroy the object. */
    virtual ~FieldClass150060()
    {
    }

    FieldClass150060* unk04;
    FieldClass150060* unk08;
};

/** Base class with four virtual handlers, with vtable D_150070 in boot data. */
class FieldClass150070 : public FieldClass150060
{
public:
    /** @brief Clear the state bytes and owner pointer. */
    FieldClass150070()
    {
        unk0e = 0;
        unk0f = 0;
        unk10 = 0;
    }

    /** @brief Detach the object from the owner at offset 0x10, then destroy it. */
    virtual ~FieldClass150070()
    {
        func_004D65C0(this);
    }

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

    u8 unk0c[2];
    u8 unk0e;
    u8 unk0f;
    void* unk10;
};

/**
 * Partial base class with two virtual handlers, with vtable D_150000 in boot
 * data. Slot 1 is named after its lowest known override (func_001DDB30); its
 * own implementation is func_001DF370.
 */
class FieldClass1DD400
{
public:
    /** @brief Default handler that performs no work. */
    virtual void func_001DD400();

    /**
     * @brief Default handler that performs no work.
     * @param arg Pointer argument; the FieldClass14FFB0 state machine passes null and
     *        FieldClass150120's override reads its word at offset 0x1C.
     */
    virtual void func_001DDB30(void* arg);
};

/**
 * Field context object at offset 0x30, with vtable D_1530D0 in boot data; its
 * methods (destructor 0x23B0C0, func_0023AEB0) are in text_0022DC70. A
 * FieldClass150070 list node that owns a Lib list (the LibClass178DD0 base at
 * offset 0x14) of record loaders, FieldClass150010 objects whose word at offset
 * 0x10 points back to that list. The list's first 12 bytes (unk00) are its
 * sentinel node: the word at +8 is the first loader.
 */
class FieldClass1530D0 : public FieldClass150070, public LibClass178DD0
{
public:
    virtual ~FieldClass1530D0();

    /** @brief Append node to the record-loader list (Lib virtual slot 9, position -1). */
    void insert(void* node)
    {
        LibClass178DD0& list = *this;
        void* self = &list;
        list.func_004D73B0(self, node, (void*)-1);
    }
};

/** Partial 16-byte, 8-byte-aligned FieldClass1DD400 used as the base at offset 0x90 of FieldClass14FE30 (vtable part D_14FE84). */
class FieldClass14FE84 : public FieldClass1DD400
{
public:
    u8 unk04[4];
    u64 unk08;
};

/** Partial class with bases at offsets 0x78 and 0x90 and a Lib member at 0xA0, with vtable D_14FE30 in boot data. */
class FieldClass14FE30 : public LibClass178DD0, public FieldClass150070, public FieldClass14FE84
{
public:
    /** @brief Detach the member at offset 0xA0, then destroy the object. */
    virtual ~FieldClass14FE30();

    /**
     * @brief Release the object's storage through the Lib heap.
     * @param object Storage to release.
     */
    static void operator delete(void* object)
    {
        func_004DB570(object);
    }

    /**
     * @brief Report the fixed value 4 for this class.
     * @return Always 4.
     */
    virtual s32 func_001DF3D0();

    /** @brief Detach the FieldClass150070 base and queue it on the resident object queue. */
    virtual void func_001DD7B0();

    /**
     * @brief Sort the list items by height, then run their per-frame handlers.
     *
     * Items are collected into a temporary array and bubble-sorted from the
     * second entry on by unk464 (type-0x400 objects) or the y component of
     * unk20. Unless the context object at offset 0x8 has a positive float at
     * offset 0x90, live type-0x2 items then run slots 21, 23 and 24; every live
     * item runs slot 13. Nothing happens when bit 7 at context offset 0xDD is set.
     */
    virtual void func_004D6730();

    /**
     * @brief Point the context's FieldClass155640 at the nearest live type-0x20 list item.
     *
     * Skipped while context flags or the focus object block it. Otherwise runs
     * the per-frame list handler, then finds the type-0x20 item nearest to the
     * context object at offset 0x18 among those with a valid word at offset
     * 0x690. The context's FieldClass155640, created on first use, is updated
     * through func_00279EA0 when its settings differ from that item's.
     */
    virtual void func_001DF360();

    LibClass178EA0 unkA0;
};

/**
 * Lib list class with vtable D_1502A0 in boot data. It adds no data to
 * LibClass178DD0; its sentinel is the list's first 12 bytes (unk00).
 */
class FieldClass1502A0 : public LibClass178DD0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass1502A0()
    {
    }

    /**
     * @brief Store the attached object pointer at offset 0x70.
     * @param attached Object pointer to store.
     */
    virtual void func_004295B0(void* attached);

    /** @brief Default handler that performs no work. */
    virtual void func_004295C0();

    /** @brief Detach and delete every listed object; traversal stops on return to the sentinel or at a null link. */
    virtual void func_001DD730();
};

/**
 * Partial class derived from FieldClass150070, with vtable D_150010 in boot
 * data. Slots 5-7 are pure virtual (zero vtable entries); they are named after
 * FieldClass14FFB0's implementations.
 */
class FieldClass150010 : public FieldClass150070
{
public:
    /** @brief Set the byte at offset 0x14 to 5 and clear the byte at offset 0x15. */
    FieldClass150010()
    {
        unk14 = 5;
        unk15 = 0;
    }

    /** @brief Destroy the object. */
    virtual ~FieldClass150010()
    {
    }

    /**
     * @brief Report the fixed value 3 for this class.
     * @return Always 3.
     */
    virtual s32 func_001DF3D0();

    /** @brief Detach the object and queue it on the resident object queue. */
    virtual void func_001DD7B0();

    /**
     * @brief Pure virtual handler slot 5.
     * @param flag Value tested for nonzero by FieldClass14FFB0's implementation.
     */
    virtual void func_001E0A50(s32 flag) = 0;

    /** @brief Pure virtual handler slot 6. */
    virtual s32 func_001E07A0() = 0;

    /** @brief Pure virtual handler slot 7. */
    virtual s32 func_001DF640() = 0;

    /**
     * @brief Read the byte at offset 0x14.
     * @return The stored byte.
     */
    virtual u8 func_001DF350();

    u8 unk14;
    u8 unk15;
};

/**
 * Partial 32-byte record with vtable D_150040 in boot data. Its base keeps its
 * vtable pointer at offset 0x18, after the base's data.
 */
class FieldClass150040 : public FieldClass1530C0
{
public:
    /** @brief Construct the base, then clear bits 0 and 1 at offset 0x1C. */
    FieldClass150040();

    /**
     * @brief Clear bits 0 and 1 at offset 0x1C, then run the base handler.
     * @return The base handler's result.
     */
    virtual s32 func_0023AD00();

    u8 unk1c_0 : 1;
    u8 unk1c_1 : 1;
    u8 unk1c_2_7 : 6;
    u8 unk1d[3];
};

/**
 * Partial FieldClass150010 with a FieldClass1DD400 base at offset 0x18 and a
 * counted array of FieldClass150040 records at offset 0x1C, with vtable
 * D_14FFB0 in boot data. The FieldClass1DD400 vtable part is D_14FFDC
 * (__vt__16FieldClass14FFB0 + 0x2C).
 */
class FieldClass14FFB0 : public FieldClass150010, public FieldClass1DD400
{
public:
    /** @brief Clear the record array and state, set the defaults, then reset the records. */
    FieldClass14FFB0();

    /** @brief Free the record array, then destroy the object. */
    virtual ~FieldClass14FFB0();

    /**
     * @brief Virtual handler slot 5.
     * @param flag Value tested for nonzero.
     */
    virtual void func_001E0A50(s32 flag);

    /**
     * @brief Finish the record requests according to the state at offset 0x15.
     *
     * State 1 releases every record not flagged by bit 0 at its offset 0x08 and moves to
     * state 10. State 10 only reports. State 9 waits while field_records_blocked() reports
     * a block; otherwise, like any other state, it notes whether a record still has a
     * nonzero rounded size, runs virtual slot 0 of the first count (offset 0x24) records,
     * and resets the state and the record index at offset 0x2E.
     * @return 1 if that scan found such a record, otherwise 2 if a record still has a
     *         nonzero rounded size, otherwise 0.
     */
    virtual s32 func_001E07A0();

    /**
     * @brief Advance the record release state at offset 0x15.
     *
     * State 7 is finished; states 9 and 10 become 7. In state 1 every record not flagged by
     * bit 0 at its offset 0x08 is released through func_00103B20, then the state becomes 7.
     * Any other state releases the object through virtual slot 2 (func_001DD7B0).
     * @return 1 after releasing the object, otherwise 0.
     */
    virtual s32 func_001DF640();

    /**
     * @brief Start the request for the current record (index at offset 0x2E).
     *
     * Does nothing when the record's rounded size is zero. Otherwise passes it to func_00103E70
     * and func_00103640, keeps the second result at the record's offset 0x10, sets state 1 at
     * offset 0x15 and clears bit 1 at offset 0x30.
     */
    virtual void func_001DF3E0();

    /** @brief Second virtual handler introduced by this class. */
    virtual void func_001E0F60();

    /** @brief Reset every record, then clear the word at offset 0x20 and the bytes at offsets 0x2D-0x2F. */
    virtual void func_001DEA80();

    /** @brief Virtual handler called by the destructor before the record array is freed. */
    virtual void func_001DF780();

    /** @brief FieldClass1DD400 slot 1 override; ignores arg. */
    virtual void func_001DDB30(void* arg);

    /**
     * @brief Replace the record array with count newly constructed records.
     * @param count Number of records to allocate.
     */
    void func_001DE8B0(s32 count);

    FieldClass150040* unk1c;
    u32 unk20;
    s32 unk24;
    s32 unk28;
    u8 unk2c;
    u8 unk2d;
    u8 unk2e;
    u8 unk2f;
    u8 unk30_0 : 1;
    u8 unk30_1 : 1;
    u8 unk30_2_7 : 6;
};

/**
 * @brief Pass the table entries of each listed type-0x8 object to the D_001B661C manager.
 *
 * Objects whose func_00204420 check fails or that have no table at offset 0x7C
 * are skipped. At most 32 entries are collected per object.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 */
extern "C" void func_001DD5E0(FieldClass150060* list);

/**
 * @brief Run each listed object's type-specific update.
 *
 * Type-0x400 objects run slot 37 with 1; type-0x20000 objects are detached and
 * released; type-0x20 objects without an object at offset 0x148 copy the vector
 * at offset 0x670 through slot 15. Afterwards the D_001B645C holder, if any,
 * releases its attached object and clears its word at offset 0x250.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 */
extern "C" void func_001DD860(FieldClass150060* list);
#endif

#ifdef __cplusplus
class FieldClass151510;

/**
 * @brief Update the type-0x2 and type-0x20000 objects in a list through slots 12 and 14.
 *
 * Objects whose word at offset 0x70 has its sign bit set are skipped. With mode
 * 2 or more, each object's own bits 5 and 6 at offset 0x8C select the settings
 * and type-0x10 objects are also passed to func_00220150; otherwise mode and arg
 * are passed to slot 12.
 * @param list Head of a circular object list.
 * @param mode Setting passed to slot 12, or 2 or more to use each object's own settings.
 * @param arg Update argument passed to slot 12 when mode is below 2.
 */
extern "C" void func_001DD9A0(FieldClass150060* list, s8 mode, s32 arg);

/**
 * @brief Test the listed type-0x1 objects other than self with func_0045BD20.
 *
 * Objects with type bit 0x10000 but not 0x200, failing func_00204420, with bit 3
 * at offset 0x204 set, or without an object at offset 0xA8 are skipped.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 * @param self Object to skip; nothing is tested when bit 22 at its offset 0x204 is set.
 * @param arg0 First argument passed to func_0045BD20.
 * @param arg1 Second argument passed to func_0045BD20.
 * @return 1 when a test succeeds, otherwise 0.
 */
extern "C" s32 func_001DDBA0(FieldClass150060* list, FieldClass151510* self, void* arg0, void* arg1);

/**
 * Partial list head reached through a listed object's owner pointer at offset
 * 0x10, recording the last object found by func_001DDD30.
 */
class FieldListOwner94 : public FieldClass150060
{
public:
    u8 unk0c[0x88];
    FieldClass150060* unk94;
};

/**
 * @brief Find the first listed type-0x1 object whose shape passes func_0045F5A0 against the target's shape.
 *
 * Objects equal to the target, with type bit 0x10000 but not 0x200, type-0x10
 * objects with a positive float at offset 0x638, objects failing
 * func_00204420, with bit 3 at offset 0x204 set, or without an object at offset
 * 0xA8 are skipped. When the target is a type-0x20 object with bit 0 at offset
 * 0x69F set, type-0x10 objects are skipped; type-0x20 objects are skipped when
 * their own bit 0 at offset 0x69F is set or the target is a type-0x10 object
 * with a positive float at offset 0x638.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 * @param target In: object whose shape is tested; nothing is tested when bit 22 at its offset 0x204 is set. Out: the object found.
 * @return True when an object is found; it is also stored at the list's offset 0x94.
 */
extern "C" bool func_001DDD30(FieldListOwner94* list, FieldClass151510** target);

/** Resident Lib list that many Field objects insert themselves into. */
extern "C" LibClass178DD0* D_001B6614;
#endif

#ifdef __cplusplus
extern "C" {
#endif

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
 * @brief Update the table of every listed object that has one at offset 0x7C.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 * @param flag Nonzero to enable the setting passed to func_004728A0.
 */
void func_001DE400(FieldFlaggedListObject* list, s32 flag);

/**
 * @brief Append listed objects to the field context's queue, all of them or only those with a nonzero word at offset 0x70.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 * @param only_keyed Nonzero to skip objects whose word at offset 0x70 is zero.
 */
void func_001DE470(FieldFlaggedListObject* list, s32 only_keyed);

#ifdef __cplusplus
}
#endif

#endif
