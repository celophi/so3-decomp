#ifndef SO3_OVERLAYS_1067_00_TEXT_002AE9E0_H
#define SO3_OVERLAYS_1067_00_TEXT_002AE9E0_H

#include "types.h"
#include "overlays/1067-00/text_001DD3C0.h"
#include "overlays/1067-00/field_packet.h"
#ifdef __cplusplus
#include "overlays/1067-00/text_001DED80.h"
#include "overlays/lib/text_004BD360.h"
#endif

/** Shared sequence fields with signed counters, halfword indices, and packed modes. */
typedef struct FieldSequenceTail
{
    s32 unk00;
    /* Last key minus first key. */
    float span;
    s16 unk08;
    s16 unk0a;
    s16 unk0c;
    s16 unk0e;
    s16 unk10;
    u8 unk12_0_3 : 4;
    u8 unk12_4_7 : 4;
    u8 unk13_0 : 1;
    u8 unk13_1 : 1;
    u8 unk13_2 : 1;
    u8 unk13_3_7 : 5;
} FieldSequenceTail;

#ifdef __cplusplus
/** Partial object with vtable D_159950 in main data; its vtable pointer follows its data at offset 0x1C. */
class FieldClass159950
{
public:
    u8 unk00[0x10];
    u16 unk10;
    u16 unk12;
    u32 unk14;
    u32 unk18;

    /** @brief Construct the object with its state cleared. */
    FieldClass159950();
    /** @brief Clear the halfwords at offsets 0x10 and 0x12 and the words at 0x14 and 0x18. */
    void func_002B7DA0();
    /** @brief Default handler that performs no work. */
    virtual void func_002BAE60();
};

/** Partial object with vtable D_159940 in main data; its vtable pointer follows its data at offset 0x1C. */
class FieldClass159940
{
public:
    u8 unk00[0x10];
    u16 unk10;
    u16 unk12;
    u32 unk14;
    u32 unk18;

    /** @brief Construct the object with its state cleared. */
    FieldClass159940();
    /** @brief Clear the halfwords at offsets 0x10 and 0x12 and the words at 0x14 and 0x18. */
    void func_002B7E00();
    /** @brief Default handler that performs no work. */
    virtual void func_002BAE70();
};

/** Partial object with vtable D_159930 in main data; its vtable pointer follows its data at offset 0x10. */
class FieldClass159930
{
public:
    s32 unk00;
    u16 unk04;
    u16 unk06;
    u32 unk08;
    u32 unk0c;

    /** @brief Construct the object with its state cleared. */
    FieldClass159930();
    /** @brief Clear the halfwords at offsets 4 and 6 and the words at 8 and 0xC. */
    void func_002B7E60();
    /** @brief Default handler that performs no work. */
    virtual void func_002BAE80();
};

/** Partial FieldClass159930 with vtable D_159980 in main data. */
class FieldClass159980 : public FieldClass159930
{
public:
    /** @brief Construct the object and clear the word at offset 0. */
    FieldClass159980();
};

/**
 * Partial 0x50-byte object with vtable D_159970 in main data. Its vtable
 * pointer follows its data at offset 0x4C; slot 0x0C is pure virtual.
 */
class FieldClass159970
{
public:
    u8 unk00[0x4C];

    /** @brief Construct the object. */
    FieldClass159970();

    // Slots in vtable order; only their positions are known.
    virtual void func_00239460();
    virtual void func_slot0c() = 0;
};

#endif

#ifdef __cplusplus
/** Partial Field object with vtable D_159050 in main data. */
class FieldClass159050 : public FieldClass150070
{
public:
    /** @brief Clear the global flag at offset 0x3E6C, set its float at 0x3E70 to one half, then destroy the object. */
    virtual ~FieldClass159050();
    /** @brief Detach the object and add it to the resident release queue. */
    virtual void func_001DD7B0();
    /** @brief Run the update on the global state object. */
    virtual void func_001DF360();
};
#endif

#ifdef __cplusplus
/** Partial vector-keyframe base with root table D_1595D0, derived directly from FieldClass14FF50. */
class FieldClass1595D0 : public FieldClass14FF50
{
public:
    /** @brief Clear the pooled flag and reset the sequence. */
    FieldClass1595D0();
    /**
     * @brief Release the track storage.
     */
    virtual ~FieldClass1595D0();
    /**
     * @brief Allocate storage for the requested keyframe count.
     * @param count Requested keyframe count.
     */
    virtual void func_002B9320(s32 count);
    /**
     * @brief Bind an external keyframe array.
     * @param count Keyframe count.
     * @param entries External keyframe storage.
     */
    virtual void func_002B8CE0(s32 count, void* entries);
    /**
     * @brief Set the lower mode nibble.
     * @param mode Mode value.
     */
    virtual void func_002B8D30(s32 mode);
    /**
     * @brief Set the upper mode nibble.
     * @param mode Mode value.
     */
    virtual void func_002B8D90(s32 mode);
    /**
     * @brief Return the stored word at offset 0x40.
     * @return Stored word.
     */
    virtual s32 func_002B8DF0() const;
    /**
     * @brief Append a vector keyframe.
     * @param value Keyframe value.
     * @param first Optional first auxiliary vector.
     * @param second Optional second auxiliary vector.
     * @param key Sort key.
     * @return Append status.
     */
    virtual s32 func_002BB970(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);
    /**
     * @brief Run the default track hook.
     */
    virtual void func_001DF220();
    /**
     * @brief Replace an indexed vector keyframe.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @param first Optional first auxiliary vector.
     * @param second Optional second auxiliary vector.
     * @return Replacement status.
     */
    virtual s32 func_002BB9A0(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
    /**
     * @brief Insert an indexed vector keyframe.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @param first Optional first auxiliary vector.
     * @param second Optional second auxiliary vector.
     * @return Insertion status.
     */
    virtual s32 func_002BB9D0(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
    /**
     * @brief Read an indexed vector keyframe.
     * @param index Keyframe index.
     * @param key Receives the sort key.
     * @param value Receives the value.
     * @param first Receives the first auxiliary vector.
     * @param second Receives the second auxiliary vector.
     * @return Nonzero when the keyframe is available.
     */
    virtual s32 func_001DF2E0(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;
    /**
     * @brief Add a vector keyframe through the track implementation.
     * @param value Keyframe value.
     * @param first Optional first auxiliary vector.
     * @param second Optional second auxiliary vector.
     * @param key Sort key.
     */
    virtual void func_002BBA00(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);
    /**
     * @brief Run the default update hook.
     */
    virtual void func_001DF300();
    /**
     * @brief Test whether the track contains the supplied key.
     * @param key Key to find.
     * @return Nonzero when the key exists.
     */
    virtual s32 func_002B8E60(float key) const;
    /**
     * @brief Return the difference between the endpoint vectors.
     * @param output Receives the vector difference.
     */
    virtual void func_002B7CA0(FieldVec4B* output) const = 0;
    /**
     * @brief Wrap a key into the stored key range.
     * @param key Key to wrap.
     * @return Wrapped key.
     */
    virtual float func_002B8FE0(float key) const;
    /**
     * @brief Return the cached vector.
     * @param output Receives the cached vector.
     */
    virtual void func_002B7C80(FieldVec4B* output) const = 0;
    /**
     * @brief Return the span between the first and last keys.
     * @return Key span, or zero when fewer than two keys are stored.
     */
    virtual float func_002B8ED0() const;
    /**
     * @brief Evaluate the vector track at a key.
     * @param key Evaluation key.
     * @param output Receives the evaluated vector.
     */
    virtual void func_002B8F90(float key, FieldVec4B* output) const;
    /**
     * @brief Return the stored keyframe count.
     * @return Keyframe count.
     */
    virtual s16 func_002B8E00() const;
    /**
     * @brief Return a pooled track or delete an ordinary track.
     */
    virtual void func_001DF230();
    // Slots 0x5C-0x64 in vtable order; only their positions are known.
    virtual void* func_002B9080();
    /** @brief Reset the sequence fields and set both modes to one. */
    virtual void func_002B8C50();
    virtual s16 func_002B8E10();
    /** @brief Handle a vector set with a key; the base implementation ignores it. @return Handler result. */
    virtual s32 func_002B8E20(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);
    /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
    virtual s32 func_002B8E30(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
    /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
    virtual s32 func_002B8E40(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
    /** @brief Handle a vector set with a key; the base implementation ignores it. */
    virtual void func_002B8E50(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);
    /** @brief Return a zero vector. @return Zero vector. */
    virtual FieldVec4A func_002B8EB0() const;
    /** @brief Return the value of the keyframe with the supplied key. @param key Key to find. @return Keyframe value, or zero when the key is absent. */
    virtual FieldVec4A func_002B8F20(float key) const;
    /** @brief Evaluate the track at a key. @param key Evaluation key. @return Evaluated vector. */
    virtual FieldVec4A func_slot80(float key) const = 0;
    /** @brief Append a keyframe. @param value Keyframe value. @param first First auxiliary vector. @param second Second auxiliary vector. @param key Sort key. @return Nonzero when the keyframe was stored. */
    virtual s32 func_002B7810(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key) = 0;
    /** @brief Replace an indexed keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @param first First auxiliary vector. @param second Second auxiliary vector. @return Nonzero when the keyframe was stored. */
    virtual s32 func_002B7960(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second) = 0;
    /** @brief Insert a keyframe at an index. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @param first First auxiliary vector. @param second Second auxiliary vector. @return Nonzero when the keyframe was stored. */
    virtual s32 func_002B9F50(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second) = 0;

    void* unk04;
    u8 unk08[8];
    FieldVec4B unk10;
    FieldVec4B unk20;
    FieldVec4B unk30;
    FieldSequenceTail state;
};

/**
 * Partial FieldClass1595D0 with vtable D_159090 in main data. It caches vectors
 * at offsets 0xB0 and 0xC0; its overrides are not declared yet.
 */
class FieldClass159090 : public FieldClass1595D0
{
public:
    /** @brief Destroy the track. */
    virtual ~FieldClass159090()
    {
    }
    /** @brief Append a keyframe, using zero vectors for missing auxiliary vectors. @param value Keyframe value. @param first Optional first auxiliary vector. @param second Optional second auxiliary vector. @param key Sort key. @return Append status. */
    virtual s32 func_002BB970(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);
    /** @brief Replace an indexed keyframe, using zero vectors for missing auxiliary vectors. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @param first Optional first auxiliary vector. @param second Optional second auxiliary vector. @return Replacement status. */
    virtual s32 func_002BB9A0(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
    /** @brief Insert an indexed keyframe, using zero vectors for missing auxiliary vectors. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @param first Optional first auxiliary vector. @param second Optional second auxiliary vector. @return Insertion status. */
    virtual s32 func_002BB9D0(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
    /**
     * @brief Read an indexed keyframe.
     * @param index Keyframe index.
     * @param key Optional; receives the sort key.
     * @param value Optional; receives the value.
     * @param first Optional; receives the first auxiliary vector.
     * @param second Optional; receives the second auxiliary vector.
     * @return One when the index is within the capacity, otherwise zero.
     */
    virtual s32 func_001DF2E0(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;
    /** @brief Store a single keyframe, using zero vectors for missing auxiliary vectors. @param value Keyframe value. @param first Optional first auxiliary vector. @param second Optional second auxiliary vector. @param key Sort key. */
    virtual void func_002BBA00(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);
    /** @brief Reset to a single zero keyframe at key zero. */
    virtual void func_001DF300();
    /** @brief Clear the cached vector at offset 0xB0 and reset the sequence. */
    virtual void func_002B8C50();
    /** @brief Append a keyframe. @param value Keyframe value. @param first First auxiliary vector. @param second Second auxiliary vector. @param key Sort key. @return Nonzero when the keyframe was stored. */
    virtual s32 func_002B7810(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);
    /** @brief Replace an indexed keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @param first First auxiliary vector. @param second Second auxiliary vector. @return Nonzero when the keyframe was stored. */
    virtual s32 func_002B7960(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
    /** @brief Insert a keyframe at an index. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @param first First auxiliary vector. @param second Second auxiliary vector. @return Nonzero when the keyframe was stored. */
    virtual s32 func_002B9F50(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
    /** @brief Return the difference between the endpoint vectors. @param output Receives the difference. */
    virtual void func_002B7CA0(FieldVec4B* output) const;
    /** @brief Return the cached vector at offset 0xC0. @param output Receives the vector. */
    virtual void func_002B7C80(FieldVec4B* output) const;
    /** @brief Evaluate the track at a key. @param key Evaluation key. @return Evaluated vector. */
    virtual FieldVec4A func_slot80(float key) const;
    /**
     * @brief Store a single keyframe in the cached vectors.
     * @param value Keyframe value.
     * @param first First auxiliary vector.
     * @param second Second auxiliary vector.
     * @param key Key, stored in the value's fourth component.
     */
    virtual void func_002B9EC0(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);
    /** @brief Return the track to its pool. */
    virtual void func_slot94() = 0;

    u8 unk60[0x50];
    FieldVec4B unkB0;
    FieldVec4B unkC0;
};

/** Partial FieldClass159090 with vtable D_159130 in main data, allocated from a pool. */
class FieldClass159130 : public FieldClass159090
{
public:
    /** @brief Construct the track. */
    FieldClass159130();
    /** @brief Destroy the track. */
    virtual ~FieldClass159130();
    /** @brief Return a pooled track to its pool, or delete an ordinary track. */
    virtual void func_001DF230();
    /** @brief Release the keyframe storage and free this track's pool slot. */
    virtual void func_slot94();
};

/**
 * Partial vector-keyframe base with root table D_159780, derived directly from
 * FieldClass14FF50. Its slots mirror FieldClass1595D0's, with 16-byte entries with the key in the fourth component, and sequence state at offset 0x20.
 */
class FieldClass159780 : public FieldClass14FF50
{
public:
    /** @brief Clear the pooled flag and reset the sequence. */
    FieldClass159780();
    /**
     * @brief Release the track storage.
     */
    virtual ~FieldClass159780();
    /**
     * @brief Allocate storage for the requested keyframe count.
     * @param count Requested keyframe count.
     */
    virtual void func_002B9910(s32 count);
    /**
     * @brief Bind an external keyframe array.
     * @param count Keyframe count.
     * @param entries External keyframe storage.
     */
    virtual void func_002B8450(s32 count, void* entries);
    /**
     * @brief Set the lower mode nibble.
     * @param mode Mode value.
     */
    virtual void func_002B84A0(s32 mode);
    /**
     * @brief Set the upper mode nibble.
     * @param mode Mode value.
     */
    virtual void func_002B8500(s32 mode);
    /**
     * @brief Return the stored word at offset 0x20.
     * @return Stored word.
     */
    virtual s32 func_002B8560() const;
    /**
     * @brief Append a vector keyframe.
     * @param value Keyframe value.
     * @param key Sort key.
     * @return Append status.
     */
    virtual s32 func_002B98D0(const FieldVec4A* value, float key);
    /**
     * @brief Run the default track hook.
     */
    virtual void func_001DF220();
    /**
     * @brief Replace an indexed vector keyframe.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @return Replacement status.
     */
    virtual s32 func_002B9890(s32 index, float key, const FieldVec4A* value);
    /**
     * @brief Insert an indexed vector keyframe.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @return Insertion status.
     */
    virtual s32 func_002B9850(s32 index, float key, const FieldVec4A* value);
    /**
     * @brief Read an indexed vector keyframe.
     * @param index Keyframe index.
     * @param key Receives the sort key.
     * @param value Receives the value.
     * @param first Receives the first auxiliary vector.
     * @param second Receives the second auxiliary vector.
     * @return Nonzero when the keyframe is available.
     */
    virtual s32 func_001DF2E0(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;
    /**
     * @brief Add a vector keyframe through the track implementation.
     * @param value Keyframe value.
     * @param key Sort key.
     */
    virtual void func_002B9810(const FieldVec4A* value, float key);
    /**
     * @brief Run the default update hook.
     */
    virtual void func_001DF300();
    /**
     * @brief Test whether the track contains the supplied key.
     * @param key Key to find.
     * @return Nonzero when the key exists.
     */
    virtual s32 func_002B8590(float key) const;
    /**
     * @brief Return the difference between the endpoint vectors.
     * @param output Receives the vector difference.
     */
    virtual void func_002B73D0(FieldVec4B* output) const = 0;
    /**
     * @brief Wrap a key into the stored key range.
     * @param key Key to wrap.
     * @return Wrapped key.
     */
    virtual float func_002B8700(float key) const;
    /**
     * @brief Return the cached vector.
     * @param output Receives the cached vector.
     */
    virtual void func_002B7440(FieldVec4B* output) const = 0;
    /**
     * @brief Return the span between the first and last keys.
     * @return Key span, or zero when fewer than two keys are stored.
     */
    virtual float func_002B8600() const;
    /**
     * @brief Evaluate the vector track at a key.
     * @param key Evaluation key.
     * @param output Receives the evaluated vector.
     */
    virtual void func_002B86B0(float key, FieldVec4B* output) const;
    /**
     * @brief Return the stored keyframe count.
     * @return Keyframe count.
     */
    virtual s16 func_002B8570() const;
    /**
     * @brief Return a pooled track or delete an ordinary track.
     */
    virtual void func_001DF230();
    // Slots 0x5C-0x64 in vtable order; only their positions are known.
    virtual void* func_002B8790();
    /** @brief Reset the sequence fields and set both modes to one. */
    virtual void func_002B83C0();
    virtual s16 func_002B8580();
    /** @brief Handle a vector set with a key; the base implementation ignores it. @return Handler result. */
    virtual s32 func_002B9900(const FieldVec4A* value, float key);
    /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
    virtual s32 func_002B98C0(s32 index, float key, const FieldVec4A* value);
    /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
    virtual s32 func_002B9880(s32 index, float key, const FieldVec4A* value);
    /** @brief Handle a vector set with a key; the base implementation ignores it. */
    virtual void func_002B9840(const FieldVec4A* value, float key);
    /** @brief Return a zero vector. @return Zero vector. */
    virtual FieldVec4A func_002B85E0() const;
    /** @brief Return the value of the keyframe with the supplied key. @param key Key to find. @return Keyframe value, or zero when the key is absent. */
    virtual FieldVec4A func_002B8650(float key) const;
    /** @brief Evaluate the track at a key. @param key Evaluation key. @return Evaluated vector. */
    virtual FieldVec4A func_slot80(float key) const = 0;
    /** @brief Return the track to its pool. */
    virtual void func_slot84() = 0;

    void* unk04;
    u8 unk08[8];
    FieldVec4B unk10;
    FieldSequenceTail state;
};

/**
 * Partial FieldClass159780 with vtable D_159270 in main data. It stores the
 * keyframes itself and resets the cached segment indices on each change.
 */
class FieldClass159270 : public FieldClass159780
{
public:
    /** @brief Destroy the track. */
    virtual ~FieldClass159270()
    {
    }
    /**
     * @brief Read an indexed keyframe.
     * @param index Keyframe index.
     * @param key Optional; receives the sort key.
     * @param value Optional; receives the value.
     * @param first Unused.
     * @param second Unused.
     * @return One when the index is within the capacity, otherwise zero.
     */
    virtual s32 func_001DF2E0(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;
    /** @brief Append a keyframe. @param value Keyframe value. @param key Sort key. @return Nonzero when the keyframe was stored. */
    virtual s32 func_002B9900(const FieldVec4A* value, float key);
    /** @brief Replace an indexed keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @return Nonzero when the keyframe was stored. */
    virtual s32 func_002B98C0(s32 index, float key, const FieldVec4A* value);
    /** @brief Insert a keyframe at an index. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @return Nonzero when the keyframe was stored. */
    virtual s32 func_002B9880(s32 index, float key, const FieldVec4A* value);
    /** @brief Store a single keyframe in the cached vector. @param value Keyframe value. @param key Sort key. */
    virtual void func_002B9840(const FieldVec4A* value, float key);
};

/** Partial FieldClass159270 with vtable D_159300 in main data and cached vectors at offsets 0x90 and 0xA0. */
class FieldClass159300 : public FieldClass159270
{
public:
    /** @brief Destroy the track. */
    virtual ~FieldClass159300()
    {
    }
    /** @brief Reset to a single zero keyframe at key zero, then set the lower mode to one. */
    virtual void func_001DF300();
    /**
     * @brief Return the difference between the endpoint vectors.
     * @param output Receives the difference; unchanged when there are no entries.
     */
    virtual void func_002B73D0(FieldVec4B* output) const;
    /** @brief Clear the cached vector at offset 0x90 and reset the sequence. */
    virtual void func_002B83C0();
    /** @brief Return the cached vector at offset 0xA0. @param output Receives the vector. */
    virtual void func_002B7440(FieldVec4B* output) const;
    /** @brief Evaluate the track at a key. @param key Evaluation key. @return Evaluated vector. */
    virtual FieldVec4A func_slot80(float key) const;

    u8 unk40[0x50];
    FieldVec4B unk90;
    FieldVec4A unkA0;
};

/** Partial FieldClass159300 with vtable D_159390 in main data, allocated from a pool. */
class FieldClass159390 : public FieldClass159300
{
public:
    /** @brief Construct the track. */
    FieldClass159390();
    /** @brief Destroy the track. */
    virtual ~FieldClass159390();
    /** @brief Return a pooled track to its pool, or delete an ordinary track. */
    virtual void func_001DF230();
    /** @brief Release the keyframe storage and free this track's pool slot. */
    virtual void func_slot84();
};

/**
 * Partial vector-keyframe base with root table D_159810, derived directly from
 * FieldClass14FF50. Its slots mirror FieldClass1595D0's, with 32-byte entries with the key first, and sequence state at offset 0x30.
 */
class FieldClass159810 : public FieldClass14FF50
{
public:
    /** @brief Clear the pooled flag and reset the sequence. */
    FieldClass159810();
    /**
     * @brief Release the track storage.
     */
    virtual ~FieldClass159810();
    /**
     * @brief Allocate storage for the requested keyframe count.
     * @param count Requested keyframe count.
     */
    virtual void func_002B9D20(s32 count);
    /**
     * @brief Bind an external keyframe array.
     * @param count Keyframe count.
     * @param entries External keyframe storage.
     */
    virtual void func_002B9CD0(s32 count, void* entries);
    /**
     * @brief Set the lower mode nibble.
     * @param mode Mode value.
     */
    virtual void func_002B7FB0(s32 mode);
    /**
     * @brief Set the upper mode nibble.
     * @param mode Mode value.
     */
    virtual void func_002B8010(s32 mode);
    /**
     * @brief Return the stored word at offset 0x30.
     * @return Stored word.
     */
    virtual s32 func_002B8070() const;
    /**
     * @brief Append a vector keyframe.
     * @param value Keyframe value.
     * @param key Sort key.
     * @return Append status.
     */
    virtual s32 func_002B9C90(const FieldVec4A* value, float key);
    /**
     * @brief Run the default track hook.
     */
    virtual void func_001DF220();
    /**
     * @brief Replace an indexed vector keyframe.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @return Replacement status.
     */
    virtual s32 func_002B9C50(s32 index, float key, const FieldVec4A* value);
    /**
     * @brief Insert an indexed vector keyframe.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @return Insertion status.
     */
    virtual s32 func_002B9C10(s32 index, float key, const FieldVec4A* value);
    /**
     * @brief Read an indexed vector keyframe.
     * @param index Keyframe index.
     * @param key Receives the sort key.
     * @param value Receives the value.
     * @param first Receives the first auxiliary vector.
     * @param second Receives the second auxiliary vector.
     * @return Nonzero when the keyframe is available.
     */
    virtual s32 func_001DF2E0(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;
    /**
     * @brief Add a vector keyframe through the track implementation.
     * @param value Keyframe value.
     * @param key Sort key.
     */
    virtual void func_002B9BD0(const FieldVec4A* value, float key);
    /**
     * @brief Run the default update hook.
     */
    virtual void func_001DF300();
    /**
     * @brief Test whether the track contains the supplied key.
     * @param key Key to find.
     * @return Nonzero when the key exists.
     */
    virtual s32 func_002B9B80(float key) const;
    /**
     * @brief Return the difference between the endpoint vectors.
     * @param output Receives the vector difference.
     */
    virtual void func_slot40(FieldVec4B* output) const = 0;
    /**
     * @brief Wrap a key into the stored key range.
     * @param key Key to wrap.
     * @return Wrapped key.
     */
    virtual float func_002B9A40(float key) const;
    /**
     * @brief Return the cached vector.
     * @param output Receives the cached vector.
     */
    virtual void func_slot48(FieldVec4B* output) const = 0;
    /**
     * @brief Return the span between the first and last keys.
     * @return Key span, or zero when fewer than two keys are stored.
     */
    virtual float func_002B9B30() const;
    /**
     * @brief Evaluate the vector track at a key.
     * @param key Evaluation key.
     * @param output Receives the evaluated vector.
     */
    virtual void func_002B80B0(float key, FieldVec4B* output) const;
    /**
     * @brief Return the stored keyframe count.
     * @return Keyframe count.
     */
    virtual s16 func_002B8080() const;
    /**
     * @brief Return a pooled track or delete an ordinary track.
     */
    virtual void func_001DF230();
    // Slots 0x5C-0x64 in vtable order; only their positions are known.
    virtual void* func_002B8100();
    virtual void func_001E94F0();
    virtual s16 func_001E9380();
    /** @brief Handle a vector set with a key; the base implementation ignores it. @return Handler result. */
    virtual s32 func_002B9CC0(const FieldVec4A* value, float key);
    /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
    virtual s32 func_002B9C80(s32 index, float key, const FieldVec4A* value);
    /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
    virtual s32 func_002B9C40(s32 index, float key, const FieldVec4A* value);
    /** @brief Handle a vector set with a key; the base implementation ignores it. */
    virtual void func_002B9C00(const FieldVec4A* value, float key);
    /** @brief Return a zero vector. @return Zero vector. */
    virtual FieldVec4A func_002B8090() const;
    /** @brief Return the value of the keyframe with the supplied key. @param key Key to find. @return Keyframe value, or zero when the key is absent. */
    virtual FieldVec4A func_002B9AD0(float key) const;
    /** @brief Evaluate the track at a key. @param key Evaluation key. @return Evaluated vector. */
    virtual FieldVec4A func_slot80(float key) const = 0;
    // Pure virtual slot 0x84; only its position is known.
    virtual void func_slot84() = 0;

    void* unk04;
    u8 unk08[8];
    float unk10;
    u8 unk14[0xC];
    FieldVec4B unk20;
    FieldSequenceTail state;
};

/**
 * Partial FieldClass159810 with vtable D_1591E0 in main data. It stores the
 * keyframes itself and resets the cached segment indices on each change.
 */
class FieldClass1591E0 : public FieldClass159810
{
public:
    /** @brief Destroy the track. */
    virtual ~FieldClass1591E0()
    {
    }
    /**
     * @brief Read an indexed keyframe.
     * @param index Keyframe index.
     * @param key Optional; receives the sort key.
     * @param value Optional; receives the value.
     * @param first Unused.
     * @param second Unused.
     * @return One when the index is within the capacity, otherwise zero.
     */
    virtual s32 func_001DF2E0(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;
    /** @brief Append a keyframe. @param value Keyframe value. @param key Sort key. @return Nonzero when the keyframe was stored. */
    virtual s32 func_002B9CC0(const FieldVec4A* value, float key);
    /** @brief Replace an indexed keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @return Nonzero when the keyframe was stored. */
    virtual s32 func_002B9C80(s32 index, float key, const FieldVec4A* value);
    /** @brief Insert a keyframe at an index. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @return Nonzero when the keyframe was stored. */
    virtual s32 func_002B9C40(s32 index, float key, const FieldVec4A* value);
    /** @brief Store a single keyframe in the cached entry. @param value Keyframe value. @param key Sort key. */
    virtual void func_002B9C00(const FieldVec4A* value, float key);
};

/**
 * Partial vector-keyframe base with root table D_1598A0, derived directly from
 * FieldClass14FF50. Its slots mirror FieldClass1595D0's, with 48-byte entries with the key first, and sequence state at offset 0x40.
 */
class FieldClass1598A0 : public FieldClass14FF50
{
public:
    /** @brief Clear the pooled flag and reset the sequence. */
    FieldClass1598A0();
    /**
     * @brief Release the track storage.
     */
    virtual ~FieldClass1598A0();
    /**
     * @brief Allocate storage for the requested keyframe count.
     * @param count Requested keyframe count.
     */
    virtual void func_002BAF20(s32 count);
    /**
     * @brief Bind an external keyframe array.
     * @param count Keyframe count.
     * @param entries External keyframe storage.
     */
    virtual void func_002BAFD0(s32 count, void* entries);
    /**
     * @brief Set the lower mode nibble.
     * @param mode Mode value.
     */
    virtual void func_002BAD00(s32 mode);
    /**
     * @brief Set the upper mode nibble.
     * @param mode Mode value.
     */
    virtual void func_002BB020(s32 mode);
    /**
     * @brief Return the stored word at offset 0x40.
     * @return Stored word.
     */
    virtual s32 func_002BB080() const;
    /**
     * @brief Append a vector keyframe.
     * @param value Keyframe value.
     * @param first Optional first auxiliary vector.
     * @param second Optional second auxiliary vector.
     * @param key Sort key.
     * @return Append status.
     */
    virtual s32 func_002BB0C0(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);
    /**
     * @brief Run the default track hook.
     */
    virtual void func_001DF220();
    /**
     * @brief Replace an indexed vector keyframe.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @param first Optional first auxiliary vector.
     * @param second Optional second auxiliary vector.
     * @return Replacement status.
     */
    virtual s32 func_002BB100(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
    /**
     * @brief Insert an indexed vector keyframe.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @param first Optional first auxiliary vector.
     * @param second Optional second auxiliary vector.
     * @return Insertion status.
     */
    virtual s32 func_002BB140(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
    /**
     * @brief Read an indexed vector keyframe.
     * @param index Keyframe index.
     * @param key Receives the sort key.
     * @param value Receives the value.
     * @param first Receives the first auxiliary vector.
     * @param second Receives the second auxiliary vector.
     * @return Nonzero when the keyframe is available.
     */
    virtual s32 func_001DF2E0(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;
    /**
     * @brief Add a vector keyframe through the track implementation.
     * @param value Keyframe value.
     * @param first Optional first auxiliary vector.
     * @param second Optional second auxiliary vector.
     * @param key Sort key.
     */
    virtual void func_002BB180(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);
    /**
     * @brief Run the default update hook.
     */
    virtual void func_001DF300();
    /**
     * @brief Test whether the track contains the supplied key.
     * @param key Key to find.
     * @return Nonzero when the key exists.
     */
    virtual s32 func_002BB1B0(float key) const;
    /**
     * @brief Return the difference between the endpoint vectors.
     * @param output Receives the vector difference.
     */
    virtual void func_slot40(FieldVec4B* output) const = 0;
    /**
     * @brief Wrap a key into the stored key range.
     * @param key Key to wrap.
     * @return Wrapped key.
     */
    virtual float func_002BB330(float key) const;
    /**
     * @brief Return the cached vector.
     * @param output Receives the cached vector.
     */
    virtual void func_slot48(FieldVec4B* output) const = 0;
    /**
     * @brief Return the span between the first and last keys.
     * @return Key span, or zero when fewer than two keys are stored.
     */
    virtual float func_002BB220() const;
    /**
     * @brief Evaluate the vector track at a key.
     * @param key Evaluation key.
     * @param output Receives the evaluated vector.
     */
    virtual void func_002BB2E0(float key, FieldVec4B* output) const;
    /**
     * @brief Return the stored keyframe count.
     * @return Keyframe count.
     */
    virtual s16 func_002BB090() const;
    /**
     * @brief Return a pooled track or delete an ordinary track.
     */
    virtual void func_001DF230();
    // Slots 0x5C-0x64 in vtable order; only their positions are known.
    virtual void* func_002BB3D0();
    virtual void func_002BAE90();
    virtual s16 func_002BB0A0();
    /** @brief Handle a vector set with a key; the base implementation ignores it. @return Handler result. */
    virtual s32 func_002BB0B0(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);
    /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
    virtual s32 func_002BB0F0(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
    /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
    virtual s32 func_002BB130(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
    /** @brief Handle a vector set with a key; the base implementation ignores it. */
    virtual void func_002BB170(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);
    /** @brief Return a zero vector. @return Zero vector. */
    virtual FieldVec4A func_002BB200() const;
    /** @brief Return the value of the keyframe with the supplied key. @param key Key to find. @return Keyframe value, or zero when the key is absent. */
    virtual FieldVec4A func_002BB270(float key) const;
    /** @brief Evaluate the track at a key. @param key Evaluation key. @return Evaluated vector. */
    virtual FieldVec4A func_slot80(float key) const = 0;
    // Pure virtual slot 0x84; only its position is known.
    virtual void func_slot84() = 0;

    void* unk04;
    u8 unk08[0x38];
    FieldSequenceTail state;
};

/**
 * Partial vector-keyframe base with root table D_159540, derived directly from
 * FieldClass14FF50. Its slots mirror FieldClass1595D0's, with 8-byte compressed entries with a halfword key at offset 6, and sequence state at offset 0x10.
 */
class FieldClass159540 : public FieldClass14FF50
{
public:
    /** @brief Clear the pooled flag and reset the sequence. */
    FieldClass159540();
    /**
     * @brief Release the track storage.
     */
    virtual ~FieldClass159540();
    /**
     * @brief Allocate storage for the requested keyframe count.
     * @param count Requested keyframe count.
     */
    virtual void func_002BBAC0(s32 count);
    /**
     * @brief Bind an external keyframe array.
     * @param count Keyframe count.
     * @param entries External keyframe storage.
     */
    virtual void func_002BBB60(s32 count, void* entries);
    /**
     * @brief Set the lower mode nibble.
     * @param mode Mode value.
     */
    virtual void func_002BAC40(s32 mode);
    /**
     * @brief Set the upper mode nibble.
     * @param mode Mode value.
     */
    virtual void func_002BBBC0(s32 mode);
    /**
     * @brief Return the stored word at offset 0x10.
     * @return Stored word.
     */
    virtual s32 func_002BBC20() const;
    /**
     * @brief Append a vector keyframe.
     * @param value Keyframe value.
     * @param first Optional first auxiliary vector.
     * @param second Optional second auxiliary vector.
     * @param key Sort key.
     * @return Append status.
     */
    virtual s32 func_002BBC60(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);
    /**
     * @brief Run the default track hook.
     */
    virtual void func_001DF220();
    /**
     * @brief Replace an indexed vector keyframe.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @param first Optional first auxiliary vector.
     * @param second Optional second auxiliary vector.
     * @return Replacement status.
     */
    virtual s32 func_002BBCA0(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
    /**
     * @brief Insert an indexed vector keyframe.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @param first Optional first auxiliary vector.
     * @param second Optional second auxiliary vector.
     * @return Insertion status.
     */
    virtual s32 func_002BBCE0(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
    /**
     * @brief Read an indexed vector keyframe.
     * @param index Keyframe index.
     * @param key Receives the sort key.
     * @param value Receives the value.
     * @param first Receives the first auxiliary vector.
     * @param second Receives the second auxiliary vector.
     * @return Nonzero when the keyframe is available.
     */
    virtual s32 func_001DF2E0(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;
    /**
     * @brief Add a vector keyframe through the track implementation.
     * @param value Keyframe value.
     * @param first Optional first auxiliary vector.
     * @param second Optional second auxiliary vector.
     * @param key Sort key.
     */
    virtual void func_002BBD20(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);
    /**
     * @brief Run the default update hook.
     */
    virtual void func_001DF300();
    /**
     * @brief Test whether the track contains the supplied key.
     * @param key Key to find.
     * @return Nonzero when the key exists.
     */
    virtual s32 func_002BBD50(float key) const;
    /**
     * @brief Return the difference between the endpoint vectors.
     * @param output Receives the vector difference.
     */
    virtual void func_slot40(FieldVec4B* output) const = 0;
    /**
     * @brief Wrap a key into the stored key range.
     * @param key Key to wrap.
     * @return Wrapped key.
     */
    virtual float func_002BBF70(float key) const;
    /**
     * @brief Return the cached vector.
     * @param output Receives the cached vector.
     */
    virtual void func_slot48(FieldVec4B* output) const = 0;
    /**
     * @brief Return the span between the first and last keys.
     * @return Key span, or zero when fewer than two keys are stored.
     */
    virtual float func_002BBDD0() const;
    /**
     * @brief Evaluate the vector track at a key.
     * @param key Evaluation key.
     * @param output Receives the evaluated vector.
     */
    virtual void func_002BBF20(float key, FieldVec4B* output) const;
    /**
     * @brief Return the stored keyframe count.
     * @return Keyframe count.
     */
    virtual s16 func_002BBC30() const;
    /**
     * @brief Return a pooled track or delete an ordinary track.
     */
    virtual void func_001DF230();
    // Slots 0x5C-0x64 in vtable order; only their positions are known.
    virtual void* func_002BC010();
    virtual void func_002BBA30();
    virtual s16 func_002BBC40();
    /** @brief Handle a vector set with a key; the base implementation ignores it. @return Handler result. */
    virtual s32 func_002BBC50(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);
    /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
    virtual s32 func_002BBC90(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
    /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
    virtual s32 func_002BBCD0(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
    /** @brief Handle a vector set with a key; the base implementation ignores it. */
    virtual void func_002BBD10(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);
    /** @brief Return a zero vector. @return Zero vector. */
    virtual FieldVec4A func_002BBDB0() const;
    /** @brief Return the value of the keyframe with the supplied key. @param key Key to find. @return Keyframe value, or zero when the key is absent. */
    virtual FieldVec4A func_002BBE30(float key) const;
    /** @brief Evaluate the track at a key. @param key Evaluation key. @return Evaluated vector. */
    virtual FieldVec4A func_slot80(float key) const = 0;
    // Pure virtual slot 0x84; only its position is known.
    virtual void func_slot84() = 0;

    void* unk04;
    u8 unk08[0x8];
    FieldSequenceTail state;
};

/**
 * Partial vector-keyframe base with root table D_159660, derived directly from
 * FieldClass14FF50. Its slots mirror FieldClass1595D0's, with 32-byte entries with the key first, and sequence state at offset 0x30.
 */
class FieldClass159660 : public FieldClass14FF50
{
public:
    /** @brief Clear the pooled flag and reset the sequence. */
    FieldClass159660();
    /**
     * @brief Release the track storage.
     */
    virtual ~FieldClass159660();
    /**
     * @brief Allocate storage for the requested keyframe count.
     * @param count Requested keyframe count.
     */
    virtual void func_002BB6B0(s32 count);
    /**
     * @brief Bind an external keyframe array.
     * @param count Keyframe count.
     * @param entries External keyframe storage.
     */
    virtual void func_002BC1B0(s32 count, void* entries);
    /**
     * @brief Set the lower mode nibble.
     * @param mode Mode value.
     */
    virtual void func_002BACA0(s32 mode);
    /**
     * @brief Set the upper mode nibble.
     * @param mode Mode value.
     */
    virtual void func_002BB760(s32 mode);
    /**
     * @brief Return the stored word at offset 0x30.
     * @return Stored word.
     */
    virtual s32 func_002BB7C0() const;
    /**
     * @brief Append a vector keyframe.
     * @param value Keyframe value.
     * @param first Optional first auxiliary vector.
     * @param second Optional second auxiliary vector.
     * @param key Sort key.
     * @return Append status.
     */
    virtual s32 func_002BB800(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);
    /**
     * @brief Run the default track hook.
     */
    virtual void func_001DF220();
    /**
     * @brief Replace an indexed vector keyframe.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @param first Optional first auxiliary vector.
     * @param second Optional second auxiliary vector.
     * @return Replacement status.
     */
    virtual s32 func_002BB840(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
    /**
     * @brief Insert an indexed vector keyframe.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @param first Optional first auxiliary vector.
     * @param second Optional second auxiliary vector.
     * @return Insertion status.
     */
    virtual s32 func_002BB880(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
    /**
     * @brief Read an indexed vector keyframe.
     * @param index Keyframe index.
     * @param key Receives the sort key.
     * @param value Receives the value.
     * @param first Receives the first auxiliary vector.
     * @param second Receives the second auxiliary vector.
     * @return Nonzero when the keyframe is available.
     */
    virtual s32 func_001DF2E0(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;
    /**
     * @brief Add a vector keyframe through the track implementation.
     * @param value Keyframe value.
     * @param first Optional first auxiliary vector.
     * @param second Optional second auxiliary vector.
     * @param key Sort key.
     */
    virtual void func_002BB8C0(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);
    /**
     * @brief Run the default update hook.
     */
    virtual void func_001DF300();
    /**
     * @brief Test whether the track contains the supplied key.
     * @param key Key to find.
     * @return Nonzero when the key exists.
     */
    virtual s32 func_002BC160(float key) const;
    /**
     * @brief Return the difference between the endpoint vectors.
     * @param output Receives the vector difference.
     */
    virtual void func_slot40(FieldVec4B* output) const = 0;
    /**
     * @brief Wrap a key into the stored key range.
     * @param key Key to wrap.
     * @return Wrapped key.
     */
    virtual float func_002BC020(float key) const;
    /**
     * @brief Return the cached vector.
     * @param output Receives the cached vector.
     */
    virtual void func_slot48(FieldVec4B* output) const = 0;
    /**
     * @brief Return the span between the first and last keys.
     * @return Key span, or zero when fewer than two keys are stored.
     */
    virtual float func_002BC110() const;
    /**
     * @brief Evaluate the vector track at a key.
     * @param key Evaluation key.
     * @param output Receives the evaluated vector.
     */
    virtual void func_002BB910(float key, FieldVec4B* output) const;
    /**
     * @brief Return the stored keyframe count.
     * @return Keyframe count.
     */
    virtual s16 func_002BB7D0() const;
    /**
     * @brief Return a pooled track or delete an ordinary track.
     */
    virtual void func_001DF230();
    // Slots 0x5C-0x64 in vtable order; only their positions are known.
    virtual void* func_002BB960();
    virtual void func_002BB620();
    virtual s16 func_002BB7E0();
    /** @brief Handle a vector set with a key; the base implementation ignores it. @return Handler result. */
    virtual s32 func_002BB7F0(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);
    /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
    virtual s32 func_002BB830(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
    /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
    virtual s32 func_002BB870(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
    /** @brief Handle a vector set with a key; the base implementation ignores it. */
    virtual void func_002BB8B0(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);
    /** @brief Return a zero vector. @return Zero vector. */
    virtual FieldVec4A func_002BB8F0() const;
    /** @brief Return the value of the keyframe with the supplied key. @param key Key to find. @return Keyframe value, or zero when the key is absent. */
    virtual FieldVec4A func_002BC0B0(float key) const;
    /** @brief Evaluate the track at a key. @param key Evaluation key. @return Evaluated vector. */
    virtual FieldVec4A func_slot80(float key) const = 0;
    // Pure virtual slot 0x84; only its position is known.
    virtual void func_slot84() = 0;

    void* unk04;
    u8 unk08[0x28];
    FieldSequenceTail state;
};

/**
 * Partial scalar-keyframe base with root table D_1596F0, derived directly from
 * FieldClass14FF50. Its slots mirror FieldClass1595D0's, with 8-byte {key, value}
 * entries and float values; D_159420 derives from it.
 */
class FieldClass1596F0 : public FieldClass14FF50
{
public:
    /** @brief Clear the pooled flag and reset the sequence. */
    FieldClass1596F0();
    /** @brief Release the track storage. */
    virtual ~FieldClass1596F0();
    /** @brief Allocate storage for the requested keyframe count. @param count Requested keyframe count. */
    virtual void func_002B88F0(s32 count);
    /** @brief Bind an external keyframe array. @param count Keyframe count. @param entries External keyframe storage. */
    virtual void func_002B9750(s32 count, void* entries);
    /** @brief Set the lower mode nibble. @param mode Mode value. */
    virtual void func_002B8990(s32 mode);
    /** @brief Set the upper mode nibble. @param mode Mode value. */
    virtual void func_002B89F0(s32 mode);
    /** @brief Return the stored word at offset 0x10. @return Stored word. */
    virtual s32 func_002B8A50() const;
    /** @brief Append a keyframe. @param value Keyframe value. @param key Sort key. @return Append status. */
    virtual s32 func_002B9710(const float* value, float key);
    /** @brief Run the default track hook. */
    virtual void func_001DF220();
    /** @brief Replace an indexed keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @return Replacement status. */
    virtual s32 func_002B96D0(s32 index, float key, const float* value);
    /** @brief Insert an indexed keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @return Insertion status. */
    virtual s32 func_002B9690(s32 index, float key, const float* value);
    /** @brief Read an indexed keyframe. @param index Keyframe index. @param key Receives the sort key. @param value Receives the value. @param first Receives the first auxiliary value. @param second Receives the second auxiliary value. @return Nonzero when the keyframe is available. */
    virtual s32 func_001DF2E0(s32 index, float* key, float* value, float* first, float* second) const;
    /** @brief Add a keyframe through the track implementation. @param value Keyframe value. @param key Sort key. */
    virtual void func_002B9650(const float* value, float key);
    /** @brief Run the default update hook. */
    virtual void func_001DF300();
    /** @brief Test whether the track contains the supplied key. @param key Key to find. @return Nonzero when the key exists. */
    virtual s32 func_002B9600(float key) const;
    /** @brief Return the difference between the endpoint values. @param output Receives the difference. */
    virtual void func_002B7480(float* output) const = 0;
    /** @brief Wrap a key into the stored key range. @param key Key to wrap. @return Wrapped key. */
    virtual float func_002B94C0(float key) const;
    /** @brief Return the cached value. @param output Receives the cached value. */
    virtual void func_002B74B0(float* output) const = 0;
    /** @brief Return the span between the first and last keys. @return Key span, or zero when fewer than two keys are stored. */
    virtual float func_002B95B0() const;
    /** @brief Evaluate the track at a key. @param key Evaluation key. @param output Receives the evaluated value. */
    virtual void func_002B8A90(float key, float* output) const;
    /** @brief Return the stored keyframe count. @return Keyframe count. */
    virtual s16 func_002B8A60() const;
    /** @brief Return a pooled track or delete an ordinary track. */
    virtual void func_001DF230();
    // Slots 0x5C-0x64 in vtable order; only their positions are known.
    virtual void* func_002B8AC0();
    /** @brief Reset the sequence fields and set both modes to one. */
    virtual void func_002B8860();
    virtual s16 func_002B8A70();
    /** @brief Handle a keyframe with a key; the base implementation ignores it. @return Handler result. */
    virtual s32 func_002B9740(const float* value, float key);
    /** @brief Handle an indexed keyframe with a key; the base implementation ignores it. @return Handler result. */
    virtual s32 func_002B9700(s32 index, float key, const float* value);
    /** @brief Handle an indexed keyframe with a key; the base implementation ignores it. @return Handler result. */
    virtual s32 func_002B96C0(s32 index, float key, const float* value);
    /** @brief Handle a keyframe with a key; the base implementation ignores it. */
    virtual void func_002B9680(const float* value, float key);
    /** @brief Return zero. @return Zero. */
    virtual float func_002B8A80() const;
    /** @brief Return the value of the keyframe with the supplied key. @param key Key to find. @return Keyframe value, or zero when the key is absent. */
    virtual float func_002B9550(float key) const;
    /** @brief Evaluate the track at a key. @param key Evaluation key. @return Evaluated value. */
    virtual float func_slot80(float key) const = 0;
    // Pure virtual slot 0x84; only its position is known.
    virtual void func_slot84() = 0;

    void* unk04;
    float unk08;
    float unk0c;
    FieldSequenceTail state;
};

/**
 * Partial FieldClass1596F0 with vtable D_159420 in main data. It stores the
 * keyframes itself and resets the cached segment indices on each change.
 */
class FieldClass159420 : public FieldClass1596F0
{
public:
    /** @brief Destroy the track. */
    virtual ~FieldClass159420()
    {
    }
    /**
     * @brief Read an indexed keyframe.
     * @param index Keyframe index.
     * @param key Optional; receives the sort key.
     * @param value Optional; receives the value.
     * @param first Unused.
     * @param second Unused.
     * @return One when the index is within the capacity, otherwise zero.
     */
    virtual s32 func_001DF2E0(s32 index, float* key, float* value, float* first, float* second) const;
    /** @brief Append a keyframe. @param value Keyframe value. @param key Sort key. @return Nonzero when the keyframe was stored. */
    virtual s32 func_002B9740(const float* value, float key);
    /** @brief Replace an indexed keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @return Nonzero when the keyframe was stored. */
    virtual s32 func_002B9700(s32 index, float key, const float* value);
    /** @brief Insert a keyframe at an index. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @return Nonzero when the keyframe was stored. */
    virtual s32 func_002B96C0(s32 index, float key, const float* value);
    /** @brief Store a single keyframe in the cached key and value. @param value Keyframe value. @param key Sort key. */
    virtual void func_002B9680(const float* value, float key);
};

/** Partial FieldClass159420 with vtable D_1594B0 in main data and a cached value at offset 0x4C. */
class FieldClass1594B0 : public FieldClass159420
{
public:
    /** @brief Destroy the track. */
    virtual ~FieldClass1594B0()
    {
    }
    /** @brief Reset to a single zero keyframe at key zero, then set the lower mode to one. */
    virtual void func_001DF300();
    /** @brief Clear the word at offset 0x48 and reset the sequence. */
    virtual void func_002B8860();
    /** @brief Return the difference between the endpoint values. @param output Receives the difference. */
    virtual void func_002B7480(float* output) const;
    /** @brief Return the cached value. @param output Receives the cached value. */
    virtual void func_002B74B0(float* output) const;
    /** @brief Evaluate the track at a key. @param key Evaluation key. @return Evaluated value. */
    virtual float func_slot80(float key) const;

    u8 unk24[0x24];
    s32 unk48;
    float unk4c;
};
/** Partial FieldClass1594B0 with vtable D_177F70 in main data; its other slots are Lib functions. */
class FieldClass177F70 : public FieldClass1594B0
{
public:
    /** @brief Construct the track. */
    FieldClass177F70();
    /** @brief Destroy the track. */
    virtual ~FieldClass177F70();
    // Slots implemented by Lib functions; only their positions are known.
    virtual void func_slot84();
};

/** Partial FieldClass1591E0 with vtable D_177EE0 in main data; its other slots are Lib functions. */
class FieldClass177EE0 : public FieldClass1591E0
{
public:
    /** @brief Construct the track. */
    FieldClass177EE0();
    /** @brief Destroy the track. */
    virtual ~FieldClass177EE0();
    // Slots implemented by Lib functions; only their positions are known.
    virtual void func_slot40(FieldVec4B* output) const;
    virtual void func_slot48(FieldVec4B* output) const;
    virtual FieldVec4A func_slot80(float key) const;
    virtual void func_slot84();

    u8 unk50[0x70];
};

/** Partial FieldClass1598A0 with vtable D_174440 in main data; its other slots are Lib functions. */
class FieldClass174440 : public FieldClass1598A0
{
public:
    /** @brief Construct the track. */
    FieldClass174440();
    /** @brief Destroy the track. */
    virtual ~FieldClass174440();
    // Slots implemented by Lib functions; only their positions are known.
    virtual void func_slot40(FieldVec4B* output) const;
    virtual void func_slot48(FieldVec4B* output) const;
    virtual FieldVec4A func_slot80(float key) const;
    virtual void func_slot84();

    u8 unk54[0x3C];
};

/** Partial FieldClass159540 with vtable D_1730F0 in main data; its other slots are Lib functions. */
class FieldClass1730F0 : public FieldClass159540
{
public:
    /** @brief Construct the track. */
    FieldClass1730F0();
    /** @brief Destroy the track. */
    virtual ~FieldClass1730F0();
    // Slots implemented by Lib functions; only their positions are known.
    virtual void func_slot40(FieldVec4B* output) const;
    virtual void func_slot48(FieldVec4B* output) const;
    virtual FieldVec4A func_slot80(float key) const;
    virtual void func_slot84();

    u8 unk24[8];
};

/** Partial FieldClass159660 with vtable D_177BE0 in main data; its other slots are Lib functions. */
class FieldClass177BE0 : public FieldClass159660
{
public:
    /** @brief Construct the track. */
    FieldClass177BE0();
    /** @brief Destroy the track. */
    virtual ~FieldClass177BE0();
    // Slots implemented by Lib functions; only their positions are known.
    virtual void func_slot40(FieldVec4B* output) const;
    virtual void func_slot48(FieldVec4B* output) const;
    virtual FieldVec4A func_slot80(float key) const;
    virtual void func_slot84();

    u8 unk44[0x3C];
};

#endif

typedef struct FieldByte60AE9E0 FieldByte60AE9E0;
typedef struct FieldFloat4CAE9E0 FieldFloat4CAE9E0;


/** Partial receiver containing sequence state at offset 0x10. */
typedef struct FieldSequenceState10
{
    u8 unk00[4];
    void* unk04;
    u8 unk08[0x8];
    FieldSequenceTail state;
} FieldSequenceState10;

/** Partial receiver containing sequence state at offset 0x20. */
typedef struct FieldSequenceState20
{
    u8 unk00[4];
    void* unk04;
    u8 unk08[0x18];
    FieldSequenceTail state;
} FieldSequenceState20;

/** Partial receiver containing sequence state at offset 0x40. */
typedef struct FieldSequenceState40
{
    u8 unk00[4];
    void* unk04;
    u8 unk08[0x38];
    FieldSequenceTail state;
} FieldSequenceState40;

/** Partial receiver containing sequence state at offset 0x30. */
typedef struct FieldSequenceState30
{
    u8 unk00[4];
    void* unk04;
    u8 unk08[0x28];
    FieldSequenceTail state;
} FieldSequenceState30;

/** Four words reset together by several sequence callbacks. */
typedef struct FieldResetWords00
{
    u32 words[4];
} FieldResetWords00;

/** Partial target with a halfword flag field at offset 0x6A. */
typedef struct FieldFlagTarget2AFD90
{
    u8 unk00[0x6A];
    u16 flags;
} FieldFlagTarget2AFD90;

/** Partial receiver with a flag target at offset 0x1B4. */
typedef struct FieldFlagOwner2AFD90
{
    u8 unk00[0x1B4];
    FieldFlagTarget2AFD90* target;
} FieldFlagOwner2AFD90;

/** Partial target with two state bits at offset 0x34. */
typedef struct FieldFlagTarget2B0BC0
{
    u8 unk00[0x34];
    u8 first : 1;
    u8 second : 1;
    u8 rest : 6;
} FieldFlagTarget2B0BC0;

/** Partial receiver with an optional state target at offset 0x20. */
typedef struct FieldFlagOwner2B0BC0
{
    u8 unk00[0x20];
    FieldFlagTarget2B0BC0* target;
} FieldFlagOwner2B0BC0;

/** Partial receiver with a value array and signed selector. */
typedef struct FieldSampleOwner2B7480
{
    u8 unk00[4];
    float* values;
    u8 unk08[0x10];
    s16 index;
} FieldSampleOwner2B7480;

/** Opaque common callback base with table D_154D50. */
typedef struct FieldObject154D50 FieldObject154D50;
#ifdef __cplusplus
/** Partial sequence receiver containing a vector at offset 0xA0. */
typedef struct FieldSequenceVectorA0
{
    u8 unk00[0xA0];
    FieldVec4A unkA0;
} FieldSequenceVectorA0;

/** Partial sequence receiver containing a vector at offset 0xC0. */
typedef struct FieldSequenceVectorC0
{
    u8 unk00[0xC0];
    FieldVec4A unkC0;
} FieldSequenceVectorC0;
#endif

#ifdef __cplusplus
/** Transform and DMA notification receiver with MAIN tables D_1599E0 and D_159A54. */
class FieldClass1599E0 : public LibClass174610
{
public:
    /** @brief Initialize the transform receiver and clear its three added words. */
    FieldClass1599E0();
    /** @brief Destroy the transform and notification bases. */
    virtual ~FieldClass1599E0();
    /** @brief Report the transform kind. @return Fourteen. */
    virtual s32 func_003EEBC0();
    /** @brief Queue the receiver for release. */
    virtual void func_003EF740();
    /** @brief Leave the default update state unchanged. */
    virtual void func_003EEBE0();
    u32 unkb0;
    u32 unkb4;
    u32 unkb8;
};

/** Partial packet drawer with vtable D_159A70 in main data; its data comes before the vptr. */
class FieldClass159A70
{
public:
    u32 unk00;
    void* unk04;
    FieldClass1525F0* unk08;
    float unk0c;
    float unk10;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s32 unk1c;
    s32 unk20;
    s32 unk24;
    s32 unk28;

    /** @brief Start with no packet, a 96.0 width and a 5.0 height. */
    FieldClass159A70();

    /** @brief Release the packet. */
    virtual ~FieldClass159A70();

    /** @brief Do nothing (the default draw). */
    virtual void func_002BC4F0();
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Store four in the receiver's byte at offset 0x60.
 * @param object Receiver containing the byte.
 */
void func_002B0A80(FieldByte60AE9E0* object);

/**
 * @brief Copy the receiver's float at offset 0x4C to an output location.
 * @param object Receiver containing the float.
 * @param output Destination for the value.
 */
void func_002B74B0(const FieldFloat4CAE9E0* object, float* output);

#ifdef __cplusplus
/**
 * @brief Test the two low state bits of the optional target.
 * @param object Receiver holding the optional target.
 * @return True when either bit is set; false when both are clear or the target is absent.
 */
bool func_002B0BC0(FieldFlagOwner2B0BC0* object);
#endif

/**
 * @brief Write the selected value minus the value at index one when an array exists.
 * @param object Receiver holding the value array and selector.
 * @param output Destination for the difference.
 */
void func_002B7480(FieldSampleOwner2B7480* object, float* output);

/**
 * @brief Set the low bit of the attached target's halfword flags when present.
 * @param object Receiver holding the optional target.
 */
void func_002AFD90(FieldFlagOwner2AFD90* object);

/**
 * @brief Clear the low bit of the attached target's halfword flags when present.
 * @param object Receiver holding the optional target.
 */
void func_002AFDB0(FieldFlagOwner2AFD90* object);

/**
 * @brief Clear the receiver's four words.
 * @param object Receiver containing the words.
 */
void func_002B8090(FieldResetWords00* object);

/**
 * @brief Clear the receiver's four words.
 * @param object Receiver containing the words.
 */
void func_002B85E0(FieldResetWords00* object);

/**
 * @brief Clear the receiver's four words.
 * @param object Receiver containing the words.
 */
void func_002B8EB0(FieldResetWords00* object);

/**
 * @brief Clear the receiver's four words.
 * @param object Receiver containing the words.
 */
void func_002BB200(FieldResetWords00* object);

/**
 * @brief Clear the receiver's four words.
 * @param object Receiver containing the words.
 */
void func_002BB8F0(FieldResetWords00* object);

/**
 * @brief Clear the receiver's four words.
 * @param object Receiver containing the words.
 */
void func_002BBDB0(FieldResetWords00* object);

/**
 * @brief Set the lower mode and record whether either mode equals four.
 * @param object Receiver containing the sequence state.
 * @param mode Mode value; only its low four bits are stored.
 */
void func_002B84A0(FieldSequenceState20* object, u8 mode);

/**
 * @brief Set the upper mode and record whether either mode equals four.
 * @param object Receiver containing the sequence state.
 * @param mode Mode value; only its low four bits are stored.
 */
void func_002B8500(FieldSequenceState20* object, u8 mode);


/**
 * @brief Set the lower mode and record whether either mode equals four.
 * @param object Receiver containing the sequence state.
 * @param mode Mode value; only its low four bits are stored.
 */
void func_002B8990(FieldSequenceState10* object, u8 mode);

/**
 * @brief Set the upper mode and record whether either mode equals four.
 * @param object Receiver containing the sequence state.
 * @param mode Mode value; only its low four bits are stored.
 */
void func_002B89F0(FieldSequenceState10* object, u8 mode);

/**
 * @brief Set the lower mode and record whether either mode equals four.
 * @param object Receiver containing the sequence state.
 * @param mode Mode value; only its low four bits are stored.
 */
void func_002B8D30(FieldSequenceState40* object, u8 mode);

/**
 * @brief Set the upper mode and record whether either mode equals four.
 * @param object Receiver containing the sequence state.
 * @param mode Mode value; only its low four bits are stored.
 */
void func_002B8D90(FieldSequenceState40* object, u8 mode);

/**
 * @brief Set the lower mode and record whether either mode equals four.
 * @param object Receiver containing the sequence state.
 * @param mode Mode value; only its low four bits are stored.
 */
void func_002BAC40(FieldSequenceState10* object, u8 mode);

/**
 * @brief Set the lower mode and record whether either mode equals four.
 * @param object Receiver containing the sequence state.
 * @param mode Mode value; only its low four bits are stored.
 */
void func_002BAD00(FieldSequenceState40* object, u8 mode);

/**
 * @brief Reset the sequence fields and set both modes to one.
 * @param object Receiver containing the sequence state.
 */
void func_002BAE90(FieldSequenceState40* object);

/**
 * @brief Set the upper mode and record whether either mode equals four.
 * @param object Receiver containing the sequence state.
 * @param mode Mode value; only its low four bits are stored.
 */
void func_002BB020(FieldSequenceState40* object, u8 mode);

/**
 * @brief Reset the sequence fields and set both modes to one.
 * @param object Receiver containing the sequence state.
 */
void func_002BBA30(FieldSequenceState10* object);

/**
 * @brief Set the upper mode and record whether either mode equals four.
 * @param object Receiver containing the sequence state.
 * @param mode Mode value; only its low four bits are stored.
 */
void func_002BBBC0(FieldSequenceState10* object, u8 mode);

/**
 * @brief Return the default callback value.
 * @param object Callback receiver.
 * @return One.
 */
float func_002AF510(FieldObject154D50* object);

/**
 * @brief Return the default callback value.
 * @param object Callback receiver.
 * @return One.
 */
float func_002AF520(FieldObject154D50* object);

/**
 * @brief Return the default callback value.
 * @param object Callback receiver.
 * @return One.
 */
float func_002AF530(FieldObject154D50* object);

/**
 * @brief Return the default callback value.
 * @param object Callback receiver.
 * @return One.
 */
float func_002AF540(FieldObject154D50* object);

/**
 * @brief Return the default callback value.
 * @param object Callback receiver.
 * @return One.
 */
float func_002AF590(FieldObject154D50* object);

/**
 * @brief Read the signed sequence word.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence word.
 */
s32 func_002B8070(FieldSequenceState30* object);

/**
 * @brief Read the signed sequence halfword.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence halfword.
 */
s16 func_002B8080(FieldSequenceState30* object);

/**
 * @brief Read the sequence record pointer.
 * @param object Sequence receiver.
 * @return Current value of the sequence record pointer.
 */
void* func_002B8100(FieldSequenceState30* object);

/**
 * @brief Read the signed sequence word.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence word.
 */
s32 func_002B8560(FieldSequenceState20* object);

/**
 * @brief Read the signed sequence halfword.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence halfword.
 */
s16 func_002B8570(FieldSequenceState20* object);

/**
 * @brief Read the signed sequence halfword.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence halfword.
 */
s16 func_002B8580(FieldSequenceState20* object);

/**
 * @brief Read the sequence record pointer.
 * @param object Sequence receiver.
 * @return Current value of the sequence record pointer.
 */
void* func_002B8790(FieldSequenceState20* object);

/**
 * @brief Read the signed sequence word.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence word.
 */
s32 func_002B8A50(FieldSequenceState10* object);

/**
 * @brief Read the signed sequence halfword.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence halfword.
 */
s16 func_002B8A60(FieldSequenceState10* object);

/**
 * @brief Read the signed sequence halfword.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence halfword.
 */
s16 func_002B8A70(FieldSequenceState10* object);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 0.0f.
 */
float func_002B8A80(FieldSequenceState10* object);

/**
 * @brief Read the sequence record pointer.
 * @param object Sequence receiver.
 * @return Current value of the sequence record pointer.
 */
void* func_002B8AC0(FieldSequenceState10* object);

/**
 * @brief Read the signed sequence word.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence word.
 */
s32 func_002B8DF0(FieldSequenceState40* object);

/**
 * @brief Read the signed sequence halfword.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence halfword.
 */
s16 func_002B8E00(FieldSequenceState40* object);

/**
 * @brief Read the signed sequence halfword.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence halfword.
 */
s16 func_002B8E10(FieldSequenceState40* object);

/**
 * @brief Read the sequence record pointer.
 * @param object Sequence receiver.
 * @return Current value of the sequence record pointer.
 */
void* func_002B9080(FieldSequenceState40* object);


#ifdef __cplusplus
/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 9.
 */
s32 func_002B0B20(FieldClass150070* object);

/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 14.
 */
s32 func_002B4030(FieldClass150070* object);

/**
 * @brief Copy the receiver's vector to the output.
 * @param object Sequence receiver.
 * @param output Destination vector.
 */
void func_002B7440(FieldSequenceVectorA0* object, FieldVec4B* output);

/**
 * @brief Copy the receiver's vector to the output.
 * @param object Sequence receiver.
 * @param output Destination vector.
 */
void func_002B7C80(FieldSequenceVectorC0* object, FieldVec4B* output);

#endif

/**
 * @brief Read the signed sequence word.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence word.
 */
s32 func_002BB080(FieldSequenceState40* object);

/**
 * @brief Read the signed sequence halfword.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence halfword.
 */
s16 func_002BB090(FieldSequenceState40* object);

/**
 * @brief Read the signed sequence halfword.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence halfword.
 */
s16 func_002BB0A0(FieldSequenceState40* object);

/**
 * @brief Read the sequence record pointer.
 * @param object Sequence receiver.
 * @return Current value of the sequence record pointer.
 */
void* func_002BB3D0(FieldSequenceState40* object);

/**
 * @brief Read the signed sequence word.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence word.
 */
s32 func_002BB7C0(FieldSequenceState30* object);

/**
 * @brief Read the signed sequence halfword.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence halfword.
 */
s16 func_002BB7D0(FieldSequenceState30* object);

/**
 * @brief Read the signed sequence halfword.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence halfword.
 */
s16 func_002BB7E0(FieldSequenceState30* object);

/**
 * @brief Read the sequence record pointer.
 * @param object Sequence receiver.
 * @return Current value of the sequence record pointer.
 */
void* func_002BB960(FieldSequenceState30* object);

/**
 * @brief Read the signed sequence word.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence word.
 */
s32 func_002BBC20(FieldSequenceState10* object);

/**
 * @brief Read the signed sequence halfword.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence halfword.
 */
s16 func_002BBC30(FieldSequenceState10* object);

/**
 * @brief Read the signed sequence halfword.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence halfword.
 */
s16 func_002BBC40(FieldSequenceState10* object);

/**
 * @brief Read the sequence record pointer.
 * @param object Sequence receiver.
 * @return Current value of the sequence record pointer.
 */
void* func_002BC010(FieldSequenceState10* object);

#ifdef __cplusplus
/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 14.
 */
s32 func_002BC220(FieldClass150070* object);
#endif

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002AFBD0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B8E20(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B8E30(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B8E40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B8E50(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B9680(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B96C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B9700(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B9740(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B9840(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B9880(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B98C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B9900(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B9C00(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B9C40(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B9C80(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B9CC0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002BB0B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002BB0F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002BB130(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BB170(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002BB7F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002BB830(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002BB870(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BB8B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002BBC50(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002BBC90(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002BBCD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BBD10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BC230(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BC260(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002BC270(void* object);

#ifdef __cplusplus
}
#endif

#endif
