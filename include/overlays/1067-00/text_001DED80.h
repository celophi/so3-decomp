#ifndef SO3_OVERLAYS_1067_00_TEXT_001DED80_H
#define SO3_OVERLAYS_1067_00_TEXT_001DED80_H

#include "types.h"
#include "overlays/1067-00/text_001DD3C0.h"
#include "overlays/1067-00/text_001DED80_callbacks.h"

/** 16-byte entry of the array owned by FieldEntryArrayObject: a sort value followed by three floats. */
typedef struct FieldArrayEntry10
{
#ifdef __cplusplus
    /**
     * @brief Copy the key and three values.
     * @param entry Entry to copy.
     * @return This entry.
     */
    FieldArrayEntry10& operator=(const FieldArrayEntry10& entry)
    {
        unk00 = entry.unk00;
        unk04 = entry.unk04;
        unk08 = entry.unk08;
        unk0c = entry.unk0c;
        return *this;
    }

#endif
    float unk00;
    float unk04;
    float unk08;
    float unk0c;
} FieldArrayEntry10;

/** Partial object owning a counted array of 16-byte entries, with index, nibble and flag state. */
typedef struct FieldEntryArrayObject
{
    u8 unk00[4];
    FieldArrayEntry10* unk04;
    float unk08;
    float unk0c;
    float unk10;
    float unk14;
    s32 unk18;
    float unk1c;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    u8 unk2a_0_3 : 4;
    u8 unk2a_4_7 : 4;
    u8 unk2b_0 : 1;
    u8 unk2b_1 : 1;
    u8 unk2b_2 : 1;
    u8 unk2b_3_7 : 5;
    u8 unk2c[0x20];
    u32 unk4c;
    float unk50;
} FieldEntryArrayObject;

/** Partial record of four copied floats, a start/end pair and their cached nonzero span. */
typedef struct FieldFloatSpan1C
{
    float unk00;
    float unk04;
    float unk08;
    float unk0c;
    float unk10;
    float unk14;
    float unk18;
} FieldFloatSpan1C;

#ifdef __cplusplus
/** Seven-float interpolation state followed by vtable D_159960. */
class FieldClass159960 : public FieldFloatSpan1C
{
public:
    /** @brief Construct the interpolation state. */
    FieldClass159960();

    /**
     * @brief Copy four coefficients and cache the segment's key range, using 1.0f when the range is empty.
     * @param a First coefficient, stored at offset 0.
     * @param b Second coefficient, stored at offset 8.
     * @param c Third coefficient, stored at offset 4.
     * @param d Fourth coefficient, stored at offset 0xC.
     * @param start First key, stored at offset 0x10.
     * @param end Last key, stored at offset 0x14.
     */
    virtual void func_001E11E0(const float* a, const float* b, const float* c, const float* d, float start, float end);

    /**
     * @brief Evaluate the interpolation state.
     * @param key Sort value.
     * @return Interpolated value.
     */
    virtual float func_002B6DF0(float key) = 0;
};

/** Interpolation state with vtable D_1591D0, installed by the keyframe constructor. */
class FieldClass1591D0 : public FieldClass159960
{
public:
    /**
     * @brief Evaluate the four cached coefficients through the resident interpolation routine.
     * @param key Sort value.
     * @return Interpolated value.
     */
    virtual float func_002B6DF0(float key);
};
#endif

#ifdef __cplusplus
extern "C" {

/** Resident scale used when caching the change in an evaluated keyframe value. */
extern float D_001B668C;

/**
 * @brief Find the segment containing a key, or select endpoint extrapolation.
 * @param object Keyframe track.
 * @param key Sort value.
 * @param lower Receives the lower entry index.
 * @param upper Receives the upper entry index.
 * @return Nonzero when the key requires endpoint extrapolation.
 */
u8 func_001E1310(FieldEntryArrayObject* object, float key, s32* lower, s32* upper);

/**
 * @brief Release listed objects, optionally preserving the focus object and clearing its track.
 * @param list Circular list sentinel; traversal also stops at a null link.
 * @param preserve_focus Nonzero to clear the focus object's track instead of releasing the object.
 */
void func_001DEF70(FieldClass150060* list, s32 preserve_focus);
#endif

/**
 * @brief Call func_00234000 for each listed object whose flag bit 3 is set.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 */
void func_001DEE90(FieldFlaggedListObject* list);

/**
 * @brief Call func_00233620 for each listed object whose flag bit 3 is set.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 */
void func_001DEF00(FieldFlaggedListObject* list);

/**
 * @brief Report the fixed value 0 for this receiver class.
 * @param object Receiver of the virtual call.
 * @return Always 0.
 */
s32 func_001DF2B0(const void* object);

/**
 * @brief Report the fixed value 0 for this receiver class.
 * @param object Receiver of the virtual call.
 * @return Always 0.
 */
s32 func_001DF2C0(const void* object);

/**
 * @brief Report the fixed value 0 for this receiver class.
 * @param object Receiver of the virtual call.
 * @return Always 0.
 */
s32 func_001DF2D0(const void* object);

/**
 * @brief Default virtual handler that performs no work.
 * @param object Receiver of the virtual call.
 */
void func_001DF2F0(void* object);

/**
 * @brief Wrap a key into the entry span, recording the whole number of spans at offset 0x18.
 * @param object Receiver owning the entry array, the span at offset 0x1C and the count at 0x20.
 * @param key Key to wrap.
 * @return key minus the recorded number of spans; mirrored back from the last entry on odd counts
 *         when the low nibble at 0x2A is 3 and the count is negative, or the high nibble is 3 and
 *         the count is positive. key unchanged when the count is zero.
 */
float func_001E1230(FieldEntryArrayObject* object, float key);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/** Root of the keyframe classes, with only a destructor, with vtable D_14FF50 in main data. */
class FieldClass14FF50
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass14FF50()
    {
    }
};

/**
 * Partial keyframe base with a counted array of 16-byte entries, with vtable
 * D_150090 in main data. Slots 14, 16 and 30-33 are pure virtual. Slots are
 * named after the first implementation.
 */
class FieldClass150090 : public FieldClass14FF50
{
public:
    /** @brief Free the entry array, then destroy the object. */
    virtual ~FieldClass150090();

    /**
     * @brief Replace the entry array with count new entries.
     * @param count Number of entries.
     */
    virtual void func_001DFB70(s32 count);

    /**
     * @brief Install an entry array, set both counts, mark the array as installed and cache its span.
     * @param count Number of entries; must be at least one.
     * @param entries Entry array to install.
     */
    virtual void func_001DFF70(s32 count, FieldArrayEntry10* entries);

    /**
     * @brief Store the low nibble at offset 0x2A, then set flag bit 0 at offset 0x2B when either nibble is 4.
     * @param value Value whose low four bits are stored.
     */
    virtual void func_001DFC10(s32 value);

    /**
     * @brief Store the high nibble at offset 0x2A, then set flag bit 0 at offset 0x2B when either nibble is 4.
     * @param value Value whose low four bits are stored.
     */
    virtual void func_001DFC70(s32 value);

    /**
     * @brief Read the signed cycle count at offset 0x18.
     * @return The stored count.
     */
    virtual s32 func_001DFCD0() const;

    /**
     * @brief Append an entry through slot 24.
     * @param x First component, or null.
     * @param y Second component, or null.
     * @param z Third component, or null.
     * @param key Sort value.
     * @return The result of slot 24.
     */
    virtual s32 func_001E1470(const float* x, const float* y, const float* z, float key);

    /** @brief Default virtual handler that performs no work. */
    virtual void func_001DF220();

    /**
     * @brief Set an entry through slot 25.
     * @param index Entry index.
     * @param key Sort value.
     * @param x First component, or null.
     * @param y Second component, or null.
     * @param z Third component, or null.
     * @return The result of slot 25.
     */
    virtual s32 func_001E14A0(s32 index, float key, const float* x, const float* y, const float* z);

    /**
     * @brief Insert an entry through slot 26.
     * @param index Entry index.
     * @param key Sort value.
     * @param x First component, or null.
     * @param y Second component, or null.
     * @param z Third component, or null.
     * @return The result of slot 26.
     */
    virtual s32 func_001E14D0(s32 index, float key, const float* x, const float* y, const float* z);

    /**
     * @brief Default entry reader that returns zero.
     * @param index Entry index.
     * @param key Receives the sort value, or null.
     * @param x Receives the first component, or null.
     * @param y Receives the second component, or null.
     * @param z Receives the third component, or null.
     * @return Always 0.
     */
    virtual s32 func_001DF2E0(s32 index, float* key, float* x, float* y, float* z) const;

    /**
     * @brief Add an entry through slot 27.
     * @param x First component, or null.
     * @param y Second component, or null.
     * @param z Third component, or null.
     * @param key Sort value.
     */
    virtual void func_001E1500(const float* x, const float* y, const float* z, float key);

    /** @brief Default virtual handler that performs no work. */
    virtual void func_001DF300();

    /**
     * @brief Test whether an entry has exactly the given sort value.
     * @param key Sort value to find.
     * @return 1 when a matching entry exists, otherwise 0.
     */
    virtual s32 func_001DFF20(float key) const;

    /**
     * @brief Pure virtual handler slot 14.
     * @param out Receives a value.
     */
    virtual void func_001DFA40(float* out) const = 0;

    /**
     * @brief Wrap a value into the span between the first and last entry sort values.
     * @param value Value to wrap.
     * @return value reduced by a whole number of spans, or value unchanged when that number is zero.
     */
    virtual float func_001DFDE0(float value) const;

    /**
     * @brief Pure virtual handler slot 16.
     * @param out Receives a value.
     */
    virtual void func_001DFA30(float* out) const = 0;

    /**
     * @brief Compute the span between the first and last entry sort values.
     * @return The span, or 0.0f when fewer than two entries exist.
     */
    virtual float func_001DFED0() const;

    /**
     * @brief Store slot 30's value for a sort value.
     * @param key Sort value.
     * @param out Receives the value.
     */
    virtual void func_001DFD50(float key, float* out);

    /**
     * @brief Read the signed entry count at offset 0x20.
     * @return The stored count.
     */
    virtual s16 func_001DFCE0() const;

    /** @brief Delete the object through its virtual destructor. */
    virtual void func_001DF230();

    /**
     * @brief Read the entry array pointer at offset 4.
     * @return The stored entry array, possibly null.
     */
    virtual FieldArrayEntry10* func_001DFD80() const;

    /**
     * @brief Reset the entry array pointer, counters, indices, nibbles and ownership flags.
     */
    virtual void func_001DFAE0();

    /**
     * @brief Read the signed halfword at offset 0x22.
     * @return The stored halfword.
     */
    virtual s16 func_001DFCF0() const;

    /**
     * @brief Default append handler.
     * @param x First component, or null.
     * @param y Second component, or null.
     * @param z Third component, or null.
     * @param key Sort value.
     * @return Always 0.
     */
    virtual s32 func_001DFD00(const float* x, const float* y, const float* z, float key);

    /**
     * @brief Default set handler.
     * @param index Entry index.
     * @param key Sort value.
     * @param x First component, or null.
     * @param y Second component, or null.
     * @param z Third component, or null.
     * @return Always 0.
     */
    virtual s32 func_001DFD10(s32 index, float key, const float* x, const float* y, const float* z);

    /**
     * @brief Default insert handler.
     * @param index Entry index.
     * @param key Sort value.
     * @param x First component, or null.
     * @param y Second component, or null.
     * @param z Third component, or null.
     * @return Always 0.
     */
    virtual s32 func_001DFD20(s32 index, float key, const float* x, const float* y, const float* z);

    /**
     * @brief Default add handler.
     * @param x First component, or null.
     * @param y Second component, or null.
     * @param z Third component, or null.
     * @param key Sort value.
     */
    virtual void func_001DFD30(const float* x, const float* y, const float* z, float key);

    /**
     * @brief Report a fixed zero value for this receiver class.
     * @return Always 0.0f.
     */
    virtual float func_001DFD40() const;

    /**
     * @brief Find the first entry with the requested sort value.
     * @param key Sort value to find.
     * @return The entry's first component, or zero when no entry matches.
     */
    virtual float func_001DFE70(float key);

    /**
     * @brief Pure virtual evaluation slot 30.
     * @param key Sort value.
     * @return The value for key.
     */
    virtual float func_001E0380(float key) = 0;

    /**
     * @brief Pure virtual append slot 31.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     * @param key Sort value.
     * @return A status value.
     */
    virtual s32 func_001E02C0(const float* x, const float* y, const float* z, float key) = 0;

    /**
     * @brief Pure virtual set slot 32.
     * @param index Entry index.
     * @param key Sort value.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     * @return A status value.
     */
    virtual s32 func_001E0220(s32 index, float key, const float* x, const float* y, const float* z) = 0;

    /**
     * @brief Pure virtual insert slot 33.
     * @param index Entry index.
     * @param key Sort value.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     * @return A status value.
     */
    virtual s32 func_001E0100(s32 index, float key, const float* x, const float* y, const float* z) = 0;

    /** @brief Free the entry array unless bit 1 at offset 0x2B marks it as external. */
    void func_001DFD90();

    FieldArrayEntry10* unk04;
    FieldArrayEntry10 unk08;
    s32 unk18;
    float unk1c;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    u8 unk2a_0_3 : 4;
    u8 unk2a_4_7 : 4;
    u8 unk2b_0 : 1;
    u8 unk2b_1 : 1;
    u8 unk2b_2 : 1;
    u8 unk2b_3_7 : 5;
    FieldClass1591D0 unk2c;
    float unk4c;
    float unk50;
};

/** Partial three-component keyframe class, with vtable D_14FEB0 in main data. */
class FieldClass14FEB0 : public FieldClass150090
{
public:
    /**
     * @brief Copy one entry's sort value and floats to the optional outputs.
     * @param index Entry index; rejected unless below the halfword at offset 0x22.
     * @param key Optional destination for the sort value.
     * @param x Optional destination for the first float.
     * @param y Optional destination for the second float.
     * @param z Optional destination for the third float.
     * @return 1 when the entry was read, or 0 when the array is null or the index is rejected.
     */
    virtual s32 func_001DF2E0(s32 index, float* key, float* x, float* y, float* z) const;

    /** @brief Clear the cached change and reset the entry array state. */
    virtual void func_001DFAE0();

    /**
     * @brief Evaluate the keyframe track, applying its wrap and extrapolation modes.
     * @param key Sort value.
     * @return Evaluated value; also updates the cached value and scaled change.
     */
    virtual float func_001E0380(float key);

    /** @brief Destroy the object. */
    virtual ~FieldClass14FEB0()
    {
    }

    /**
     * @brief Append an entry, using 0 for a missing second or third component.
     * @param x First component.
     * @param y Second component, or null.
     * @param z Third component, or null.
     * @param key Sort value.
     * @return The result of slot 31.
     */
    virtual s32 func_001E1470(const float* x, const float* y, const float* z, float key);

    /**
     * @brief Set an entry, using 0 for a missing second or third component.
     * @param index Entry index.
     * @param key Sort value.
     * @param x First component.
     * @param y Second component, or null.
     * @param z Third component, or null.
     * @return The result of slot 32.
     */
    virtual s32 func_001E14A0(s32 index, float key, const float* x, const float* y, const float* z);

    /**
     * @brief Insert an entry, using 0 for a missing second or third component.
     * @param index Entry index.
     * @param key Sort value.
     * @param x First component.
     * @param y Second component, or null.
     * @param z Third component, or null.
     * @return The result of slot 33.
     */
    virtual s32 func_001E14D0(s32 index, float key, const float* x, const float* y, const float* z);

    /**
     * @brief Add an entry, using 0 for a missing second or third component.
     * @param x First component.
     * @param y Second component, or null.
     * @param z Third component, or null.
     * @param key Sort value.
     */
    virtual void func_001E1500(const float* x, const float* y, const float* z, float key);

    /** @brief Add an all-zero entry with sort value 0 through slot 11. */
    virtual void func_001DF300();

    /**
     * @brief Virtual handler slot 34.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     * @param key Sort value.
     */
    virtual void func_001E0080(const float* x, const float* y, const float* z, float key);

    /**
     * @brief Store the difference between the float at offset 4 of the last and first entries.
     * @param out Destination for the difference; unchanged when the array pointer is null.
     */
    virtual void func_001DFA40(float* out) const;

    /**
     * @brief Copy the float at offset 0x50 to the output.
     * @param out Destination for the float.
     */
    virtual void func_001DFA30(float* out) const;

    /**
     * @brief Append an entry after the active ones and refresh the cached span.
     * @param x First float to store.
     * @param y Second float to store.
     * @param z Third float to store.
     * @param key Sort value to store.
     * @return 1 when the entry was appended, or 0 when the array is null or full.
     */
    virtual s32 func_001E02C0(const float* x, const float* y, const float* z, float key);

    /**
     * @brief Write one entry, refreshing the cached span when it is the last active entry.
     * @param index Entry index; rejected unless below the halfword at offset 0x22.
     * @param key Sort value to store.
     * @param x First float to store.
     * @param y Second float to store.
     * @param z Third float to store.
     * @return 1 when the entry was written, or 0 when the array is null or the index is rejected.
     */
    virtual s32 func_001E0220(s32 index, float key, const float* x, const float* y, const float* z);

    /**
     * @brief Insert an entry before the given active index, shifting later entries up by one.
     * @param index Insertion index; rejected unless below the active count.
     * @param key Sort value to store.
     * @param x First float to store.
     * @param y Second float to store.
     * @param z Third float to store.
     * @return 1 when the entry was inserted, or 0 when the array is null, full or the index is rejected.
     */
    virtual s32 func_001E0100(s32 index, float key, const float* x, const float* y, const float* z);
};

/**
 * Partial keyframe class sharing vtable D_177C70 with the resident library.
 * The Field array constructor installs FieldClass14FEB0 before this table;
 * its additional virtual handlers are not declared yet.
 */
class FieldClass177C70 : public FieldClass14FEB0
{
public:
    /** @brief Construct the keyframe object. */
    FieldClass177C70();
    /** @brief Destroy the keyframe object. */
    virtual ~FieldClass177C70();
};
extern "C" {
/**
 * @brief Allocate a 128-byte-aligned buffer, retrying after other loaders release storage.
 * @param owner Loader attached to the resource list.
 * @param size Requested buffer size in bytes.
 * @param mode Nonzero for the library allocator, zero for the resident allocator.
 * @return Allocated buffer, or null after allocation or recovery fails.
 */
void* func_001E1100(FieldClass150070* owner, u32 size, s32 mode);
}
#endif

#endif
