#include "include_asm.h"
#include "main/resident_data.h"
#include "main/resident_0010A0E0.h"
#include "main/resident_001001E0.h"
#include "overlays/1067-00/text_002AE9E0.h"
#include "overlays/lib/text_004AB8B0.h"
#include "overlays/1067-00/text_001DED80.h"
#include "overlays/1067-00/text_0029E9E0.h"

/** Partial fixed pool of tracks with a bitmap of used slots. */
template <class T>
struct FieldTrackPool
{
    s32 count;
    s32 unk04;
    T* items;
    s32 capacity;
    s32 words;
    u64* used;
    bool external;
};

/** Partial view of the global state object at D_001B6650. */
struct FieldGlobal3E6C
{
    u8 unk00[0x3E6C];
    u8 unk3e6c;
    u8 unk3e6d[3];
    float unk3e70;
};

extern "C" void* D_001B6650;
extern "C" void func_4DCFA0(void* state);
extern "C" FieldTrackPool<FieldClass159130>* D_001B6674;
extern "C" FieldTrackPool<FieldClass159390>* D_001B6668;
extern "C" void func_002B9090(FieldClass1595D0* track);
extern "C" void func_002B87A0(FieldClass159780* track);
extern "C" void func_002B91F0(FieldTrackPool<FieldClass159130>* pool, FieldClass159130* track);
extern "C" void func_002B91A0(FieldTrackPool<FieldClass159390>* pool, FieldClass159390* track);

/** 16-byte keyframe of FieldClass159780; the value's fourth component is its key. */
struct FieldTrackKey159780
{
    /** @brief Leave the value uninitialized. */
    FieldTrackKey159780()
    {
    }

    FieldVec4B value;
};

/** 48-byte vector keyframe of FieldClass1595D0: a FieldClass159780 keyframe and two auxiliary vectors. */
struct FieldTrackKey1595D0 : public FieldTrackKey159780
{
    /** @brief Leave the vectors uninitialized. */
    FieldTrackKey1595D0()
    {
    }

    FieldVec4B first;
    FieldVec4B second;
};

/** 32-byte keyframe of FieldClass159810: a key and a value at offset 0x10. */
struct FieldTrackKey159810
{
    /** @brief Leave the keyframe uninitialized. */
    FieldTrackKey159810();

    float key;
    FieldVec4B value;
};

/** Partial 48-byte keyframe of FieldClass1598A0 with its key first. */
struct FieldTrackKey1598A0
{
    /** @brief Leave the keyframe uninitialized. */
    FieldTrackKey1598A0();

    float key;
    u8 unk04[0x2C];
};

/** Partial 32-byte keyframe of FieldClass159660 with its key first. */
struct FieldTrackKey159660
{
    /** @brief Leave the keyframe uninitialized. */
    FieldTrackKey159660();

    float key;
    u8 unk04[0x1C];
};

/** 8-byte packed keyframe of FieldClass159540: three halfword values and a halfword key. */
struct FieldTrackKey159540
{
    /**
     * @brief Copy the values and key.
     * @param entry Entry to copy.
     * @return This entry.
     */
    FieldTrackKey159540& operator=(const FieldTrackKey159540& entry)
    {
        unk00[0] = entry.unk00[0];
        unk00[1] = entry.unk00[1];
        unk00[2] = entry.unk00[2];
        key = entry.key;
        return *this;
    }

    s16 unk00[3];
    s16 key;
};

/** 8-byte scalar keyframe of FieldClass1596F0: a key followed by its value. */
struct FieldTrackKey1596F0
{
    /**
     * @brief Copy the key and value.
     * @param entry Entry to copy.
     * @return This entry.
     */
    FieldTrackKey1596F0& operator=(const FieldTrackKey1596F0& entry)
    {
        key = entry.key;
        value = entry.value;
        return *this;
    }

    float key;
    float value;
};

/**
 * @brief Subtract the first three components.
 * @param left Vector to subtract from.
 * @param right Vector to subtract.
 * @return Difference, keeping the left vector's fourth component.
 */
static inline FieldVec4A sequence_difference(const FieldVec4B& left, const FieldVec4B& right)
{
    FieldVec4A value;
    *(unsigned __int128*)&value = *(const unsigned __int128*)&left;
    value.x -= right.x;
    value.y -= right.y;
    value.z -= right.z;
    return value;
}

/** @brief Return a FieldClass1595D0 keyframe. @param object Sequence receiver. @param index Entry index. @return Entry. */
static inline const FieldTrackKey1595D0* entry_1595D0(const FieldSequenceState40* object, s32 index)
{
    return &static_cast<const FieldTrackKey1595D0*>(object->unk04)[index];
}

/** @brief Return a FieldClass159780 keyframe. @param object Sequence receiver. @param index Entry index. @return Entry. */
static inline const FieldTrackKey159780* entry_159780(const FieldSequenceState20* object, s32 index)
{
    return &static_cast<const FieldTrackKey159780*>(object->unk04)[index];
}

/** @brief Return a FieldClass159810 keyframe. @param object Sequence receiver. @param index Entry index. @return Entry. */
static inline const FieldTrackKey159810* entry_159810(const FieldSequenceState30* object, s32 index)
{
    return &static_cast<const FieldTrackKey159810*>(object->unk04)[index];
}

/** @brief Return a FieldClass1598A0 keyframe. @param object Sequence receiver. @param index Entry index. @return Entry. */
static inline const FieldTrackKey1598A0* entry_1598A0(const FieldSequenceState40* object, s32 index)
{
    return &static_cast<const FieldTrackKey1598A0*>(object->unk04)[index];
}

/** @brief Return a FieldClass159660 keyframe. @param object Sequence receiver. @param index Entry index. @return Entry. */
static inline const FieldTrackKey159660* entry_159660(const FieldSequenceState30* object, s32 index)
{
    return &static_cast<const FieldTrackKey159660*>(object->unk04)[index];
}

/** @brief Return a FieldClass159540 keyframe. @param object Sequence receiver. @param index Entry index. @return Entry. */
static inline const FieldTrackKey159540* entry_159540(const FieldSequenceState10* object, s32 index)
{
    return &static_cast<const FieldTrackKey159540*>(object->unk04)[index];
}

/** @brief Return a FieldClass159540 keyframe's key. @param object Sequence receiver. @param index Entry index. @return Key as a float. */
static inline float key_159540(const FieldSequenceState10* object, s32 index)
{
    return entry_159540(object, index)->key;
}

/** @brief Return a FieldClass1596F0 keyframe. @param object Sequence receiver. @param index Entry index. @return Entry. */
static inline const FieldTrackKey1596F0* entry_1596F0(const FieldSequenceState10* object, s32 index)
{
    return &static_cast<const FieldTrackKey1596F0*>(object->unk04)[index];
}

/** Partial receiver with a byte at offset 0x60. */
struct FieldByte60AE9E0
{
    u8 pad[0x60];
    u8 value;
};

/** Partial receiver with a float at offset 0x4C. */
struct FieldFloat4CAE9E0
{
    u8 pad[0x4C];
    float value;
};

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002AE9E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002AEB60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002AED30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002AEEB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002AF080);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002AF200);

FieldClass158DD0::FieldClass158DD0()
{
    unk04 = 0;
    unk14 = 0;
    unk18 = 0;
    unk1C = 0;
    unk20 = 0;
    unk24 = 0;
}

FieldClass158DD0::~FieldClass158DD0()
{
    delete[] unk18;
    delete unk1C;
    delete[] unk24;
}

float func_002AF510(FieldObject154D50* object)
{
    return 1.0f;
}

float func_002AF520(FieldObject154D50* object)
{
    return 1.0f;
}

float func_002AF530(FieldObject154D50* object)
{
    return 1.0f;
}

float func_002AF540(FieldObject154D50* object)
{
    return 1.0f;
}

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
extern "C" void func_002AF550(FieldClass158DD0* object, const FieldClass158DD0* other)
{
    object->unk0C = other->unk0C;
    object->unk10 = other->unk10;
    object->resize(object->unk0C, object->unk10);
}

float func_002AF590(FieldObject154D50* object)
{
    return 1.0f;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002AF5A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002AF670);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002AF700);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002AF760);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002AF7C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002AF810);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002AF8A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002AF950);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002AFA40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002AFAF0);

s32 func_002AFBD0(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002AFBE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002AFCA0);

void func_002AFD90(FieldFlagOwner2AFD90* object)
{
    FieldFlagTarget2AFD90* target = object->target;
    if (target != 0)
    {
        target->flags |= 1;
    }
}

void func_002AFDB0(FieldFlagOwner2AFD90* object)
{
    FieldFlagTarget2AFD90* target = object->target;
    if (target != 0)
    {
        target->flags &= 0xFFFE;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002AFDD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B0110);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B0210);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B0930);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B0A10);

extern "C" void func_002B0A80(FieldByte60AE9E0* object)
{
    object->value = 4;
}

/** Partial FieldClass150070 object with vtable D_158FF0 in main data. */
class FieldClass158FF0 : public FieldClass150070
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass158FF0();
};

FieldClass158FF0::~FieldClass158FF0()
{
}

s32 func_002B0B20(FieldClass150070* object)
{
    return 9;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B0B30);

bool func_002B0BC0(FieldFlagOwner2B0BC0* object)
{
    FieldFlagTarget2B0BC0* target = object->target;
    if (target == 0)
    {
        return false;
    }
    return target->first || target->second;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B0C00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B0D80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B14C0);

void FieldClass159050::func_001DD7B0()
{
    func_004D65C0(this);
    func_0011ED90(D_001B65F4, this);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B1600);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B1650);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B16A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B1880);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B1B90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B1BC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B24C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B2550);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B3EA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B3F60);

FieldClass159050::~FieldClass159050()
{
    FieldGlobal3E6C* state = static_cast<FieldGlobal3E6C*>(D_001B6650);
    state->unk3e6c = 0;
    state->unk3e70 = 0.5f;
}

s32 func_002B4030(FieldClass150070* object)
{
    return 14;
}

void FieldClass159050::func_001DF360()
{
    func_4DCFA0(D_001B6650);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B4060);

/**
 * @brief Allocate the pool's tracks, mark them pooled and clear the used bitmap.
 * @param pool Pool to fill.
 * @param count Number of tracks.
 * @return One on success, or zero when the tracks could not be allocated.
 */
extern "C" s32 func_002B41A0(FieldTrackPool<FieldClass177F70>* pool, s32 count)
{
    s32 index;
    s32 words;
    s32 word;
    pool->items = new (0) FieldClass177F70[count];
    if (pool->items == 0)
    {
        return 0;
    }
    for (index = 0; index < count; index++)
    {
        pool->items[index].state.unk13_2 = true;
    }
    if (!pool->external)
    {
        delete[] pool->used;
    }
    pool->capacity = count;
    pool->words = (u32)(count + 63) >> 6;
    pool->used = new (0) u64[pool->words];
    pool->external = false;
    pool->count = count;
    pool->unk04 = 0;
    words = pool->words;
    for (word = 0; word < words; word++)
    {
        pool->used[word] = 0;
    }
    return 1;
}

FieldClass177F70::~FieldClass177F70()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", __ct__16FieldClass177F70Fv);



/**
 * @brief Release every track in the pool and its storage.
 * @param pool Pool to clear.
 */
extern "C" void func_002B4620(FieldTrackPool<FieldClass177F70>* pool)
{
    s32 count = pool->count;
    s32 index;
    for (index = 0; index < count; index++)
    {
        pool->items[index].state.unk13_2 = false;
    }
    delete[] pool->items;
    if (!pool->external)
    {
        delete[] pool->used;
        pool->used = 0;
    }
    pool->items = 0;
    pool->count = 0;
}

/**
 * @brief Allocate the pool's tracks, mark them pooled and clear the used bitmap.
 * @param pool Pool to fill.
 * @param count Number of tracks.
 * @return One on success, or zero when the tracks could not be allocated.
 */
extern "C" s32 func_002B47C0(FieldTrackPool<FieldClass159390>* pool, s32 count)
{
    s32 index;
    s32 words;
    s32 word;
    pool->items = new (0) FieldClass159390[count];
    if (pool->items == 0)
    {
        return 0;
    }
    for (index = 0; index < count; index++)
    {
        pool->items[index].state.unk13_2 = true;
    }
    if (!pool->external)
    {
        delete[] pool->used;
    }
    pool->capacity = count;
    pool->words = (u32)(count + 63) >> 6;
    pool->used = new (0) u64[pool->words];
    pool->external = false;
    pool->count = count;
    pool->unk04 = 0;
    words = pool->words;
    for (word = 0; word < words; word++)
    {
        pool->used[word] = 0;
    }
    return 1;
}

FieldClass159390::~FieldClass159390()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", __ct__16FieldClass159390Fv);



/**
 * @brief Release every track in the pool and its storage.
 * @param pool Pool to clear.
 */
extern "C" void func_002B4C50(FieldTrackPool<FieldClass159390>* pool)
{
    s32 count = pool->count;
    s32 index;
    for (index = 0; index < count; index++)
    {
        pool->items[index].state.unk13_2 = false;
    }
    delete[] pool->items;
    if (!pool->external)
    {
        delete[] pool->used;
        pool->used = 0;
    }
    pool->items = 0;
    pool->count = 0;
}

/**
 * @brief Allocate the pool's tracks, mark them pooled and clear the used bitmap.
 * @param pool Pool to fill.
 * @param count Number of tracks.
 * @return One on success, or zero when the tracks could not be allocated.
 */
extern "C" s32 func_002B4DF0(FieldTrackPool<FieldClass177EE0>* pool, s32 count)
{
    s32 index;
    s32 words;
    s32 word;
    pool->items = new (0) FieldClass177EE0[count];
    if (pool->items == 0)
    {
        return 0;
    }
    for (index = 0; index < count; index++)
    {
        pool->items[index].state.unk13_2 = true;
    }
    if (!pool->external)
    {
        delete[] pool->used;
    }
    pool->capacity = count;
    pool->words = (u32)(count + 63) >> 6;
    pool->used = new (0) u64[pool->words];
    pool->external = false;
    pool->count = count;
    pool->unk04 = 0;
    words = pool->words;
    for (word = 0; word < words; word++)
    {
        pool->used[word] = 0;
    }
    return 1;
}

FieldClass177EE0::~FieldClass177EE0()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", __ct__16FieldClass177EE0Fv);


/**
 * @brief Release every track in the pool and its storage.
 * @param pool Pool to clear.
 */
extern "C" void func_002B51F0(FieldTrackPool<FieldClass177EE0>* pool)
{
    s32 count = pool->count;
    s32 index;
    for (index = 0; index < count; index++)
    {
        pool->items[index].state.unk13_2 = false;
    }
    delete[] pool->items;
    if (!pool->external)
    {
        delete[] pool->used;
        pool->used = 0;
    }
    pool->items = 0;
    pool->count = 0;
}

/**
 * @brief Allocate the pool's tracks, mark them pooled and clear the used bitmap.
 * @param pool Pool to fill.
 * @param count Number of tracks.
 * @return One on success, or zero when the tracks could not be allocated.
 */
extern "C" s32 func_002B5390(FieldTrackPool<FieldClass177C70>* pool, s32 count)
{
    s32 index;
    s32 words;
    s32 word;
    pool->items = new (0) FieldClass177C70[count];
    if (pool->items == 0)
    {
        return 0;
    }
    for (index = 0; index < count; index++)
    {
        pool->items[index].unk2b_2 = true;
    }
    if (!pool->external)
    {
        delete[] pool->used;
    }
    pool->capacity = count;
    pool->words = (u32)(count + 63) >> 6;
    pool->used = new (0) u64[pool->words];
    pool->external = false;
    pool->count = count;
    pool->unk04 = 0;
    words = pool->words;
    for (word = 0; word < words; word++)
    {
        pool->used[word] = 0;
    }
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", __ct__16FieldClass177C70Fv);

/**
 * @brief Release every track in the pool and its storage.
 * @param pool Pool to clear.
 */
extern "C" void func_002B56D0(FieldTrackPool<FieldClass177C70>* pool)
{
    s32 count = pool->count;
    s32 index;
    for (index = 0; index < count; index++)
    {
        pool->items[index].unk2b_2 = false;
    }
    delete[] pool->items;
    if (!pool->external)
    {
        delete[] pool->used;
        pool->used = 0;
    }
    pool->items = 0;
    pool->count = 0;
}

/**
 * @brief Allocate the pool's tracks, mark them pooled and clear the used bitmap.
 * @param pool Pool to fill.
 * @param count Number of tracks.
 * @return One on success, or zero when the tracks could not be allocated.
 */
extern "C" s32 func_002B5870(FieldTrackPool<FieldClass159130>* pool, s32 count)
{
    s32 index;
    s32 words;
    s32 word;
    pool->items = new (0) FieldClass159130[count];
    if (pool->items == 0)
    {
        return 0;
    }
    for (index = 0; index < count; index++)
    {
        pool->items[index].state.unk13_2 = true;
    }
    if (!pool->external)
    {
        delete[] pool->used;
    }
    pool->capacity = count;
    pool->words = (u32)(count + 63) >> 6;
    pool->used = new (0) u64[pool->words];
    pool->external = false;
    pool->count = count;
    pool->unk04 = 0;
    words = pool->words;
    for (word = 0; word < words; word++)
    {
        pool->used[word] = 0;
    }
    return 1;
}

FieldClass159130::~FieldClass159130()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", __ct__16FieldClass159130Fv);


/**
 * @brief Release every track in the pool and its storage.
 * @param pool Pool to clear.
 */
extern "C" void func_002B5C80(FieldTrackPool<FieldClass159130>* pool)
{
    s32 count = pool->count;
    s32 index;
    for (index = 0; index < count; index++)
    {
        pool->items[index].state.unk13_2 = false;
    }
    delete[] pool->items;
    if (!pool->external)
    {
        delete[] pool->used;
        pool->used = 0;
    }
    pool->items = 0;
    pool->count = 0;
}

/**
 * @brief Allocate the pool's tracks, mark them pooled and clear the used bitmap.
 * @param pool Pool to fill.
 * @param count Number of tracks.
 * @return One on success, or zero when the tracks could not be allocated.
 */
extern "C" s32 func_002B5E20(FieldTrackPool<FieldClass177BE0>* pool, s32 count)
{
    s32 index;
    s32 words;
    s32 word;
    pool->items = new (0) FieldClass177BE0[count];
    if (pool->items == 0)
    {
        return 0;
    }
    for (index = 0; index < count; index++)
    {
        pool->items[index].state.unk13_2 = true;
    }
    if (!pool->external)
    {
        delete[] pool->used;
    }
    pool->capacity = count;
    pool->words = (u32)(count + 63) >> 6;
    pool->used = new (0) u64[pool->words];
    pool->external = false;
    pool->count = count;
    pool->unk04 = 0;
    words = pool->words;
    for (word = 0; word < words; word++)
    {
        pool->used[word] = 0;
    }
    return 1;
}

FieldClass177BE0::~FieldClass177BE0()
{
}

FieldClass177BE0::FieldClass177BE0()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B6180);

/**
 * @brief Allocate the pool's tracks, mark them pooled and clear the used bitmap.
 * @param pool Pool to fill.
 * @param count Number of tracks.
 * @return One on success, or zero when the tracks could not be allocated.
 */
extern "C" s32 func_002B6310(FieldTrackPool<FieldClass174440>* pool, s32 count)
{
    s32 index;
    s32 words;
    s32 word;
    pool->items = new (0) FieldClass174440[count];
    if (pool->items == 0)
    {
        return 0;
    }
    for (index = 0; index < count; index++)
    {
        pool->items[index].state.unk13_2 = true;
    }
    if (!pool->external)
    {
        delete[] pool->used;
    }
    pool->capacity = count;
    pool->words = (u32)(count + 63) >> 6;
    pool->used = new (0) u64[pool->words];
    pool->external = false;
    pool->count = count;
    pool->unk04 = 0;
    words = pool->words;
    for (word = 0; word < words; word++)
    {
        pool->used[word] = 0;
    }
    return 1;
}

FieldClass174440::~FieldClass174440()
{
}

FieldClass174440::FieldClass174440()
{
}

/**
 * @brief Release every track in the pool and its storage.
 * @param pool Pool to clear.
 */
extern "C" void func_002B6680(FieldTrackPool<FieldClass174440>* pool)
{
    s32 count = pool->count;
    s32 index;
    for (index = 0; index < count; index++)
    {
        pool->items[index].state.unk13_2 = false;
    }
    delete[] pool->items;
    if (!pool->external)
    {
        delete[] pool->used;
        pool->used = 0;
    }
    pool->items = 0;
    pool->count = 0;
}

/**
 * @brief Allocate the pool's tracks, mark them pooled and clear the used bitmap.
 * @param pool Pool to fill.
 * @param count Number of tracks.
 * @return One on success, or zero when the tracks could not be allocated.
 */
extern "C" s32 func_002B6820(FieldTrackPool<FieldClass1730F0>* pool, s32 count)
{
    s32 index;
    s32 words;
    s32 word;
    pool->items = new (0) FieldClass1730F0[count];
    if (pool->items == 0)
    {
        return 0;
    }
    for (index = 0; index < count; index++)
    {
        pool->items[index].state.unk13_2 = true;
    }
    if (!pool->external)
    {
        delete[] pool->used;
    }
    pool->capacity = count;
    pool->words = (u32)(count + 63) >> 6;
    pool->used = new (0) u64[pool->words];
    pool->external = false;
    pool->count = count;
    pool->unk04 = 0;
    words = pool->words;
    for (word = 0; word < words; word++)
    {
        pool->used[word] = 0;
    }
    return 1;
}

FieldClass1730F0::~FieldClass1730F0()
{
}

FieldClass1730F0::FieldClass1730F0()
{
}

/**
 * @brief Release every track in the pool and its storage.
 * @param pool Pool to clear.
 */
extern "C" void func_002B6BA0(FieldTrackPool<FieldClass1730F0>* pool)
{
    s32 count = pool->count;
    s32 index;
    for (index = 0; index < count; index++)
    {
        pool->items[index].state.unk13_2 = false;
    }
    delete[] pool->items;
    if (!pool->external)
    {
        delete[] pool->used;
        pool->used = 0;
    }
    pool->items = 0;
    pool->count = 0;
}

extern "C" void func_4B1640(void* object);

/** @brief Forward the object to func_4B1640. @param object Object to forward. */
extern "C" void func_002B6D40(void* object)
{
    func_4B1640(object);
}

void FieldClass159130::func_001DF230()
{
    if (this != 0)
    {
        if (state.unk13_2)
        {
            func_slot94();
        }
        else
        {
            delete this;
        }
    }
}

void FieldClass159130::func_slot94()
{
    func_002B9090(this);
    func_002B91F0(D_001B6674, this);
}

float FieldClass1591D0::func_002B6DF0(float key)
{
    return func_4B16C0(this, key);
}

void FieldClass159390::func_001DF230()
{
    if (this != 0)
    {
        if (state.unk13_2)
        {
            func_slot84();
        }
        else
        {
            delete this;
        }
    }
}

void FieldClass159390::func_slot84()
{
    func_002B87A0(this);
    func_002B91A0(D_001B6668, this);
}

void FieldClass159300::func_002B83C0()
{
    unk90 = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    FieldClass159780::func_002B83C0();
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B6EE0);

void FieldClass159300::func_002B73D0(FieldVec4B* output) const
{
    if (unk04 != 0)
    {
        *output = sequence_difference(static_cast<const FieldTrackKey159780*>(unk04)[state.unk08 - 1].value, static_cast<const FieldTrackKey159780*>(unk04)[0].value);
    }
}

void func_002B7440(FieldSequenceVectorA0* object, FieldVec4B* output)
{
    *output = object->unkA0;
}

void FieldClass1594B0::func_002B8860()
{
    unk48 = 0;
    FieldClass1596F0::func_002B8860();
}

void func_002B7480(FieldSampleOwner2B7480* object, float* output)
{
    float* values = object->values;
    if (values != 0)
    {
        *output = values[2 * object->index - 1] - values[1];
    }
}

extern "C" void func_002B74B0(const FieldFloat4CAE9E0* object, float* output)
{
    *output = object->value;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B74C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B7510);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B7560);

FieldClass159980::FieldClass159980()
{
    unk00 = 0;
}

s32 FieldClass159270::func_002B9900(const FieldVec4A* value, float key)
{
    if (unk04 == 0)
    {
        return 0;
    }
    if (state.unk08 >= state.unk0a)
    {
        return 0;
    }
    static_cast<FieldTrackKey159780*>(unk04)[state.unk08].value = *value;
    static_cast<FieldTrackKey159780*>(unk04)[state.unk08].value.w = key;
    state.span = key - static_cast<FieldTrackKey159780*>(unk04)[0].value.w;
    state.unk0e = -1;
    state.unk10 = -1;
    state.unk08++;
    return 1;
}

s32 FieldClass159270::func_002B98C0(s32 index, float key, const FieldVec4A* value)
{
    if (unk04 == 0)
    {
        return 0;
    }
    if (index >= state.unk0a)
    {
        return 0;
    }
    static_cast<FieldTrackKey159780*>(unk04)[index].value = *value;
    static_cast<FieldTrackKey159780*>(unk04)[index].value.w = key;
    if (index == state.unk08 - 1)
    {
        state.span = key - static_cast<FieldTrackKey159780*>(unk04)[0].value.w;
    }
    state.unk0e = -1;
    state.unk10 = -1;
    return 1;
}

s32 FieldClass159270::func_001DF2E0(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const
{
    if (unk04 == 0)
    {
        return 0;
    }
    if (index >= state.unk0a)
    {
        return 0;
    }
    if (key)
    {
        *key = static_cast<const FieldTrackKey159780*>(unk04)[index].value.w;
    }
    if (value)
    {
        *value = static_cast<const FieldTrackKey159780*>(unk04)[index].value;
    }
    return 1;
}

void FieldClass159090::func_002B8C50()
{
    unkB0 = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    FieldClass1595D0::func_002B8C50();
}

s32 FieldClass159090::func_002B7810(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    if (unk04 == 0)
    {
        return 0;
    }
    if (state.unk08 >= state.unk0a)
    {
        return 0;
    }
    static_cast<FieldTrackKey1595D0*>(unk04)[state.unk08].value = *value;
    static_cast<FieldTrackKey1595D0*>(unk04)[state.unk08].first = *first;
    static_cast<FieldTrackKey1595D0*>(unk04)[state.unk08].second = *second;
    static_cast<FieldTrackKey1595D0*>(unk04)[state.unk08].value.w = key;
    state.span = key - static_cast<FieldTrackKey1595D0*>(unk04)[0].value.w;
    state.unk08++;
    return 1;
}

/**
 * @brief Return a vector, or a zeroed fallback when it is missing.
 * @param vector Optional vector.
 * @param zero Storage for the zero vector.
 * @return The vector, or zero after clearing it.
 */
static inline const FieldVec4A* track_vector(const FieldVec4A* vector, FieldVec4A* zero)
{
    if (!vector)
    {
        zero->x = 0.0f;
        zero->y = 0.0f;
        zero->z = 0.0f;
        zero->w = 0.0f;
        return zero;
    }
    return vector;
}

s32 FieldClass159090::func_002BB970(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    FieldVec4A zero_first;
    FieldVec4A zero_second;
    second = track_vector(second, &zero_second);
    first = track_vector(first, &zero_first);
    return func_002B7810(value, first, second, key);
}

s32 FieldClass159090::func_002B7960(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    if (unk04 == 0)
    {
        return 0;
    }
    if (index >= state.unk0a)
    {
        return 0;
    }
    static_cast<FieldTrackKey1595D0*>(unk04)[index].value = *value;
    static_cast<FieldTrackKey1595D0*>(unk04)[index].first = *first;
    static_cast<FieldTrackKey1595D0*>(unk04)[index].second = *second;
    static_cast<FieldTrackKey1595D0*>(unk04)[index].value.w = key;
    if (index == state.unk08 - 1)
    {
        state.span = key - static_cast<FieldTrackKey1595D0*>(unk04)[0].value.w;
    }
    return 1;
}

s32 FieldClass159090::func_002BB9A0(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    FieldVec4A zero_first;
    FieldVec4A zero_second;
    second = track_vector(second, &zero_second);
    first = track_vector(first, &zero_first);
    return func_002B7960(index, key, value, first, second);
}

s32 FieldClass159090::func_002BB9D0(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    FieldVec4A zero_first;
    FieldVec4A zero_second;
    second = track_vector(second, &zero_second);
    first = track_vector(first, &zero_first);
    return func_002B9F50(index, key, value, first, second);
}

void FieldClass159090::func_002BBA00(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    FieldVec4A zero_first;
    FieldVec4A zero_second;
    second = track_vector(second, &zero_second);
    first = track_vector(first, &zero_first);
    func_002B9EC0(value, first, second, key);
}

s32 FieldClass159090::func_001DF2E0(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const
{
    if (unk04 == 0)
    {
        return 0;
    }
    if (index >= state.unk0a)
    {
        return 0;
    }
    if (key)
    {
        *key = static_cast<const FieldTrackKey1595D0*>(unk04)[index].value.w;
    }
    if (value)
    {
        *value = static_cast<const FieldTrackKey1595D0*>(unk04)[index].value;
    }
    if (first)
    {
        *first = static_cast<const FieldTrackKey1595D0*>(unk04)[index].first;
    }
    if (second)
    {
        *second = static_cast<const FieldTrackKey1595D0*>(unk04)[index].second;
    }
    return 1;
}

void FieldClass159090::func_001DF300()
{
    FieldVec4A zero(0.0f, 0.0f, 0.0f, 0.0f);
    func_002BBA00(&zero, &zero, &zero, 0.0f);
}

void func_002B7C80(FieldSequenceVectorC0* object, FieldVec4B* output)
{
    *output = object->unkC0;
}

/**
 * @brief Return the difference between the endpoint vectors.
 * @param object Sequence receiver.
 * @param output Receives the difference; unchanged when there are no entries.
 */
extern "C" void func_002B7CA0(const FieldSequenceState40* object, FieldVec4B* output)
{
    if (object->unk04 != 0)
    {
        *output = sequence_difference(entry_1595D0(object, object->state.unk08 - 1)->value, entry_1595D0(object, 0)->value);
    }
}

FieldClass159970::FieldClass159970()
{
}

FieldClass159960::FieldClass159960()
{
}

FieldClass159950::FieldClass159950()
{
    func_002B7DA0();
}

void FieldClass159950::func_002B7DA0()
{
    unk10 = 0;
    unk12 = 0;
    unk14 = 0;
    unk18 = 0;
}

FieldClass159940::FieldClass159940()
{
    func_002B7E00();
}

void FieldClass159940::func_002B7E00()
{
    unk10 = 0;
    unk12 = 0;
    unk14 = 0;
    unk18 = 0;
}

FieldClass159930::FieldClass159930()
{
    func_002B7E60();
}

void FieldClass159930::func_002B7E60()
{
    unk04 = 0;
    unk06 = 0;
    unk08 = 0;
    unk0c = 0;
}

extern "C" void func_002B7EF0(FieldClass1598A0* track);

FieldClass1598A0::~FieldClass1598A0()
{
    func_002B7EF0(this);
}

/**
 * @brief Release owned keyframe storage and clear the keyframe pointer.
 * @param track Track whose storage is released; external storage is left alone.
 */
extern "C" void func_002B7EF0(FieldClass1598A0* track)
{
    if (!track->state.unk13_1)
    {
        delete[] static_cast<FieldTrackKey1598A0*>(track->unk04);
    }
    track->unk04 = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", __dt__16FieldClass159810Fv);

void FieldClass159810::func_002B7FB0(s32 mode)
{
    state.unk12_0_3 = mode;
    state.unk13_0 = state.unk12_0_3 == 4 || state.unk12_4_7 == 4;
}

void FieldClass159810::func_002B8010(s32 mode)
{
    state.unk12_4_7 = mode;
    state.unk13_0 = state.unk12_0_3 == 4 || state.unk12_4_7 == 4;
}

s32 func_002B8070(FieldSequenceState30* object)
{
    return object->state.unk00;
}

s16 func_002B8080(FieldSequenceState30* object)
{
    return object->state.unk08;
}

void func_002B8090(FieldResetWords00* object)
{
    object->words[0] = 0;
    object->words[1] = 0;
    object->words[2] = 0;
    object->words[3] = 0;
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated vector.
 */
void FieldClass159810::func_002B80B0(float key, FieldVec4B* output) const
{
    *output = func_slot80(key);
}

void* func_002B8100(FieldSequenceState30* object)
{
    return object->unk04;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B8110);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B81F0);

extern "C" void func_002B87A0(FieldClass159780* track);

FieldClass159780::~FieldClass159780()
{
    func_002B87A0(this);
}

void FieldClass159780::func_002B83C0()
{
    unk04 = 0;
    state.unk12_0_3 = 1;
    state.unk12_4_7 = 1;
    state.unk0a = 0;
    state.unk08 = 0;
    state.unk0c = -1;
    state.unk00 = 0;
    state.unk0e = -1;
    state.unk10 = -1;
    state.unk13_0 = 0;
    state.unk13_1 = 0;
}

/**
 * @brief Bind an external keyframe array.
 * @param object Sequence receiver.
 * @param count Keyframe count.
 * @param entries External keyframe storage.
 */
extern "C" void func_002B8450(FieldSequenceState20* object, s32 count, void* entries)
{
    object->state.unk13_1 = 1;
    object->unk04 = entries;
    object->state.unk0a = count;
    object->state.unk08 = count;
    object->state.span = entry_159780(object, count - 1)->value.w - entry_159780(object, 0)->value.w;
}

void func_002B84A0(FieldSequenceState20* object, u8 mode)
{
    object->state.unk12_0_3 = mode;
    object->state.unk13_0 = object->state.unk12_0_3 == 4 || object->state.unk12_4_7 == 4;
}

void func_002B8500(FieldSequenceState20* object, u8 mode)
{
    object->state.unk12_4_7 = mode;
    object->state.unk13_0 = object->state.unk12_0_3 == 4 || object->state.unk12_4_7 == 4;
}

s32 func_002B8560(FieldSequenceState20* object)
{
    return object->state.unk00;
}

s16 func_002B8570(FieldSequenceState20* object)
{
    return object->state.unk08;
}

s16 func_002B8580(FieldSequenceState20* object)
{
    return object->state.unk0a;
}

/**
 * @brief Test whether the track contains the supplied key.
 * @param object Sequence receiver.
 * @param key Key to find.
 * @return One when the key exists, otherwise zero.
 */
extern "C" s32 func_002B8590(const FieldSequenceState20* object, float key)
{
    s16 count = object->state.unk08;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == entry_159780(object, index)->value.w)
        {
            return 1;
        }
    }
    return 0;
}

void func_002B85E0(FieldResetWords00* object)
{
    object->words[0] = 0;
    object->words[1] = 0;
    object->words[2] = 0;
    object->words[3] = 0;
}

/**
 * @brief Return the span between the first and last keys.
 * @param object Sequence receiver.
 * @return Last key minus first key, or zero with fewer than two entries.
 */
extern "C" float func_002B8600(const FieldSequenceState20* object)
{
    if (object->state.unk08 < 2)
    {
        return 0.0f;
    }
    return entry_159780(object, object->state.unk08 - 1)->value.w - entry_159780(object, 0)->value.w;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B8650);

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated vector.
 */
void FieldClass159780::func_002B86B0(float key, FieldVec4B* output) const
{
    *output = func_slot80(key);
}

/**
 * @brief Wrap a key into the stored key range.
 * @param object Sequence receiver.
 * @param key Key to wrap.
 * @return The key less a whole number of key spans.
 */
extern "C" float func_002B8700(const FieldSequenceState20* object, float key)
{
    float first = entry_159780(object, 0)->value.w;
    float range = entry_159780(object, object->state.unk08 - 1)->value.w - first;
    float position = (key - first) / range;
    s32 spans;
    if (position < 0.0f)
    {
        position -= 1.0f;
    }
    spans = (s32)position;
    if (spans != 0)
    {
        return key - spans * range;
    }
    return key;
}

void* func_002B8790(FieldSequenceState20* object)
{
    return object->unk04;
}

/**
 * @brief Release owned keyframe storage and clear the keyframe pointer.
 * @param track Track whose storage is released; external storage is left alone.
 */
extern "C" void func_002B87A0(FieldClass159780* track)
{
    if (!track->state.unk13_1)
    {
        delete[] static_cast<FieldTrackKey159780*>(track->unk04);
    }
    track->unk04 = 0;
}

extern "C" void func_002B8AD0(FieldClass1596F0* track);

FieldClass1596F0::~FieldClass1596F0()
{
    func_002B8AD0(this);
}

void FieldClass1596F0::func_002B8860()
{
    unk04 = 0;
    state.unk12_0_3 = 1;
    state.unk12_4_7 = 1;
    state.unk0a = 0;
    state.unk08 = 0;
    state.unk0c = -1;
    state.unk00 = 0;
    state.unk0e = -1;
    state.unk10 = -1;
    state.unk13_0 = 0;
    state.unk13_1 = 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param object Sequence receiver.
 * @param count Requested keyframe count.
 */
extern "C" void func_002B88F0(FieldSequenceState10* object, s32 count)
{
    object->state.unk13_1 = 0;
    delete[] static_cast<FieldTrackKey1596F0*>(object->unk04);
    object->unk04 = new (0) FieldTrackKey1596F0[count];
    object->state.unk0a = count;
    if (!object->unk04)
    {
        object->state.unk0a = 0;
    }
}

void func_002B8990(FieldSequenceState10* object, u8 mode)
{
    object->state.unk12_0_3 = mode;
    object->state.unk13_0 = object->state.unk12_0_3 == 4 || object->state.unk12_4_7 == 4;
}

void func_002B89F0(FieldSequenceState10* object, u8 mode)
{
    object->state.unk12_4_7 = mode;
    object->state.unk13_0 = object->state.unk12_0_3 == 4 || object->state.unk12_4_7 == 4;
}

s32 func_002B8A50(FieldSequenceState10* object)
{
    return object->state.unk00;
}

s16 func_002B8A60(FieldSequenceState10* object)
{
    return object->state.unk08;
}

s16 func_002B8A70(FieldSequenceState10* object)
{
    return object->state.unk0a;
}

extern "C" float func_002B8A80(FieldSequenceState10* object)
{
    return 0.0f;
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void FieldClass1596F0::func_002B8A90(float key, float* output) const
{
    *output = func_slot80(key);
}

void* func_002B8AC0(FieldSequenceState10* object)
{
    return object->unk04;
}

/**
 * @brief Release owned keyframe storage and clear the keyframe pointer.
 * @param track Track whose storage is released; external storage is left alone.
 */
extern "C" void func_002B8AD0(FieldClass1596F0* track)
{
    if (!track->state.unk13_1)
    {
        delete[] static_cast<FieldTrackKey1596F0*>(track->unk04);
    }
    track->unk04 = 0;
}

extern "C" void func_002B8B90(FieldClass159660* track);

FieldClass159660::~FieldClass159660()
{
    func_002B8B90(this);
}

/**
 * @brief Release owned keyframe storage and clear the keyframe pointer.
 * @param track Track whose storage is released; external storage is left alone.
 */
extern "C" void func_002B8B90(FieldClass159660* track)
{
    if (!track->state.unk13_1)
    {
        delete[] static_cast<FieldTrackKey159660*>(track->unk04);
    }
    track->unk04 = 0;
}

FieldClass1595D0::~FieldClass1595D0()
{
    func_002B9090(this);
}

void FieldClass1595D0::func_002B8C50()
{
    unk04 = 0;
    state.unk12_0_3 = 1;
    state.unk12_4_7 = 1;
    state.unk0a = 0;
    state.unk08 = 0;
    state.unk0c = -1;
    state.unk00 = 0;
    state.unk0e = -1;
    state.unk10 = -1;
    state.unk13_0 = 0;
    state.unk13_1 = 0;
}

/**
 * @brief Bind an external keyframe array.
 * @param object Sequence receiver.
 * @param count Keyframe count.
 * @param entries External keyframe storage.
 */
extern "C" void func_002B8CE0(FieldSequenceState40* object, s32 count, void* entries)
{
    object->state.unk13_1 = 1;
    object->unk04 = entries;
    object->state.unk0a = count;
    object->state.unk08 = count;
    object->state.span = entry_1595D0(object, count - 1)->value.w - entry_1595D0(object, 0)->value.w;
}

void func_002B8D30(FieldSequenceState40* object, u8 mode)
{
    object->state.unk12_0_3 = mode;
    object->state.unk13_0 = object->state.unk12_0_3 == 4 || object->state.unk12_4_7 == 4;
}

void func_002B8D90(FieldSequenceState40* object, u8 mode)
{
    object->state.unk12_4_7 = mode;
    object->state.unk13_0 = object->state.unk12_0_3 == 4 || object->state.unk12_4_7 == 4;
}

s32 func_002B8DF0(FieldSequenceState40* object)
{
    return object->state.unk00;
}

s16 func_002B8E00(FieldSequenceState40* object)
{
    return object->state.unk08;
}

s16 func_002B8E10(FieldSequenceState40* object)
{
    return object->state.unk0a;
}

s32 func_002B8E20(void* object)
{
    return 0;
}

s32 func_002B8E30(void* object)
{
    return 0;
}

s32 func_002B8E40(void* object)
{
    return 0;
}

void func_002B8E50(void* object)
{
}

/**
 * @brief Test whether the track contains the supplied key.
 * @param object Sequence receiver.
 * @param key Key to find.
 * @return One when the key exists, otherwise zero.
 */
extern "C" s32 func_002B8E60(const FieldSequenceState40* object, float key)
{
    s16 count = object->state.unk08;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == entry_1595D0(object, index)->value.w)
        {
            return 1;
        }
    }
    return 0;
}

void func_002B8EB0(FieldResetWords00* object)
{
    object->words[0] = 0;
    object->words[1] = 0;
    object->words[2] = 0;
    object->words[3] = 0;
}

/**
 * @brief Return the span between the first and last keys.
 * @param object Sequence receiver.
 * @return Last key minus first key, or zero with fewer than two entries.
 */
extern "C" float func_002B8ED0(const FieldSequenceState40* object)
{
    if (object->state.unk08 < 2)
    {
        return 0.0f;
    }
    return entry_1595D0(object, object->state.unk08 - 1)->value.w - entry_1595D0(object, 0)->value.w;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B8F20);

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated vector.
 */
void FieldClass1595D0::func_002B8F90(float key, FieldVec4B* output) const
{
    *output = func_slot80(key);
}

/**
 * @brief Wrap a key into the stored key range.
 * @param object Sequence receiver.
 * @param key Key to wrap.
 * @return The key less a whole number of key spans.
 */
extern "C" float func_002B8FE0(const FieldSequenceState40* object, float key)
{
    float first = entry_1595D0(object, 0)->value.w;
    float range = entry_1595D0(object, object->state.unk08 - 1)->value.w - first;
    float position = (key - first) / range;
    s32 spans;
    if (position < 0.0f)
    {
        position -= 1.0f;
    }
    spans = (s32)position;
    if (spans != 0)
    {
        return key - spans * range;
    }
    return key;
}

void* func_002B9080(FieldSequenceState40* object)
{
    return object->unk04;
}

/**
 * @brief Release owned keyframe storage and clear the keyframe pointer.
 * @param track Track whose storage is released; external storage is left alone.
 */
extern "C" void func_002B9090(FieldClass1595D0* track)
{
    if (!track->state.unk13_1)
    {
        delete[] static_cast<FieldTrackKey1595D0*>(track->unk04);
    }
    track->unk04 = 0;
}

extern "C" void func_002B9150(FieldClass159540* track);

FieldClass159540::~FieldClass159540()
{
    func_002B9150(this);
}

/**
 * @brief Release owned keyframe storage and clear the keyframe pointer.
 * @param track Track whose storage is released; external storage is left alone.
 */
extern "C" void func_002B9150(FieldClass159540* track)
{
    if (!track->state.unk13_1)
    {
        delete[] static_cast<FieldTrackKey159540*>(track->unk04);
    }
    track->unk04 = 0;
}

/**
 * @brief Mark a track's pool slot as free.
 * @param pool Pool that owns the track.
 * @param track Track to release.
 */
extern "C" void func_002B91A0(FieldTrackPool<FieldClass159390>* pool, FieldClass159390* track)
{
    u32 index = ((u32)track - (u32)pool->items) / ((u32)&pool->items[1] - (u32)pool->items);
    pool->used[index >> 6] &= ~((u64)1 << (index & 0x3F));
}

/**
 * @brief Mark a track's pool slot as free.
 * @param pool Pool that owns the track.
 * @param track Track to release.
 */
extern "C" void func_002B91F0(FieldTrackPool<FieldClass159130>* pool, FieldClass159130* track)
{
    u32 index = ((u32)track - (u32)pool->items) / ((u32)&pool->items[1] - (u32)pool->items);
    pool->used[index >> 6] &= ~((u64)1 << (index & 0x3F));
}

FieldClass159540::FieldClass159540()
{
    state.unk13_2 = false;
    func_002BBA30();
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B92B0);

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param object Sequence receiver.
 * @param count Requested keyframe count.
 */
extern "C" void func_002B9320(FieldSequenceState40* object, s32 count)
{
    object->state.unk13_1 = 0;
    delete[] static_cast<FieldTrackKey1595D0*>(object->unk04);
    object->unk04 = new (0) FieldTrackKey1595D0[count];
    object->state.unk0a = count;
    if (!object->unk04)
    {
        object->state.unk0a = 0;
    }
}


FieldClass1595D0::FieldClass1595D0()
{
    state.unk13_2 = false;
    func_002B8C50();
}

FieldClass159660::FieldClass159660()
{
    state.unk13_2 = false;
    func_002BB620();
}

/**
 * @brief Wrap a key into the stored key range.
 * @param object Sequence receiver.
 * @param key Key to wrap.
 * @return The key less a whole number of key spans.
 */
extern "C" float func_002B94C0(const FieldSequenceState10* object, float key)
{
    float first = entry_1596F0(object, 0)->key;
    float range = entry_1596F0(object, object->state.unk08 - 1)->key - first;
    float position = (key - first) / range;
    s32 spans;
    if (position < 0.0f)
    {
        position -= 1.0f;
    }
    spans = (s32)position;
    if (spans != 0)
    {
        return key - spans * range;
    }
    return key;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B9550);

/**
 * @brief Return the span between the first and last keys.
 * @param object Sequence receiver.
 * @return Last key minus first key, or zero with fewer than two entries.
 */
extern "C" float func_002B95B0(const FieldSequenceState10* object)
{
    if (object->state.unk08 < 2)
    {
        return 0.0f;
    }
    return entry_1596F0(object, object->state.unk08 - 1)->key - entry_1596F0(object, 0)->key;
}

/**
 * @brief Test whether the track contains the supplied key.
 * @param object Sequence receiver.
 * @param key Key to find.
 * @return One when the key exists, otherwise zero.
 */
extern "C" s32 func_002B9600(const FieldSequenceState10* object, float key)
{
    s16 count = object->state.unk08;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == entry_1596F0(object, index)->key)
        {
            return 1;
        }
    }
    return 0;
}

/** @brief Forward a keyframe with a key to slot 0x74. */
extern "C" void func_002B9650(FieldClass1596F0* object, const float* value, float key)
{
    object->func_002B9680(value, key);
}

void func_002B9680(void* object)
{
}

/** @brief Forward an indexed keyframe insertion to slot 0x70. */
extern "C" s32 func_002B9690(FieldClass1596F0* object, s32 index, float key, const float* value)
{
    return object->func_002B96C0(index, key, value);
}

s32 func_002B96C0(void* object)
{
    return 0;
}

/** @brief Forward an indexed keyframe replacement to slot 0x6C. */
extern "C" s32 func_002B96D0(FieldClass1596F0* object, s32 index, float key, const float* value)
{
    return object->func_002B9700(index, key, value);
}

s32 func_002B9700(void* object)
{
    return 0;
}

/** @brief Forward a keyframe with a key to slot 0x68. */
extern "C" s32 func_002B9710(FieldClass1596F0* object, const float* value, float key)
{
    return object->func_002B9740(value, key);
}

s32 func_002B9740(void* object)
{
    return 0;
}

/**
 * @brief Bind an external keyframe array.
 * @param object Sequence receiver.
 * @param count Keyframe count.
 * @param entries External keyframe storage.
 */
extern "C" void func_002B9750(FieldSequenceState10* object, s32 count, void* entries)
{
    object->state.unk13_1 = 1;
    object->unk04 = entries;
    object->state.unk0a = count;
    object->state.unk08 = count;
    object->state.span = entry_1596F0(object, count - 1)->key - entry_1596F0(object, 0)->key;
}

FieldClass1596F0::FieldClass1596F0()
{
    state.unk13_2 = false;
    func_002B8860();
}

/** @brief Forward a vector set with a key to slot 0x74. */
extern "C" void func_002B9810(FieldClass159780* object, const FieldVec4A* value, float key)
{
    object->func_002B9840(value, key);
}

void func_002B9840(void* object)
{
}

/** @brief Forward an indexed vector insertion to slot 0x70. */
extern "C" s32 func_002B9850(FieldClass159780* object, s32 index, float key, const FieldVec4A* value)
{
    return object->func_002B9880(index, key, value);
}

s32 func_002B9880(void* object)
{
    return 0;
}

/** @brief Forward an indexed vector replacement to slot 0x6C. */
extern "C" s32 func_002B9890(FieldClass159780* object, s32 index, float key, const FieldVec4A* value)
{
    return object->func_002B98C0(index, key, value);
}

s32 func_002B98C0(void* object)
{
    return 0;
}

/** @brief Forward a vector set with a key to slot 0x68. */
extern "C" s32 func_002B98D0(FieldClass159780* object, const FieldVec4A* value, float key)
{
    return object->func_002B9900(value, key);
}

s32 func_002B9900(void* object)
{
    return 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param object Sequence receiver.
 * @param count Requested keyframe count.
 */
extern "C" void func_002B9910(FieldSequenceState20* object, s32 count)
{
    object->state.unk13_1 = 0;
    delete[] static_cast<FieldTrackKey159780*>(object->unk04);
    object->unk04 = new (0) FieldTrackKey159780[count];
    object->state.unk0a = count;
    if (!object->unk04)
    {
        object->state.unk0a = 0;
    }
}


FieldClass159780::FieldClass159780()
{
    state.unk13_2 = false;
    func_002B83C0();
}

/**
 * @brief Wrap a key into the stored key range.
 * @param object Sequence receiver.
 * @param key Key to wrap.
 * @return The key less a whole number of key spans.
 */
extern "C" float func_002B9A40(const FieldSequenceState30* object, float key)
{
    float first = entry_159810(object, 0)->key;
    float range = entry_159810(object, object->state.unk08 - 1)->key - first;
    float position = (key - first) / range;
    s32 spans;
    if (position < 0.0f)
    {
        position -= 1.0f;
    }
    spans = (s32)position;
    if (spans != 0)
    {
        return key - spans * range;
    }
    return key;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B9AD0);

/**
 * @brief Return the span between the first and last keys.
 * @param object Sequence receiver.
 * @return Last key minus first key, or zero with fewer than two entries.
 */
extern "C" float func_002B9B30(const FieldSequenceState30* object)
{
    if (object->state.unk08 < 2)
    {
        return 0.0f;
    }
    return entry_159810(object, object->state.unk08 - 1)->key - entry_159810(object, 0)->key;
}

/**
 * @brief Test whether the track contains the supplied key.
 * @param object Sequence receiver.
 * @param key Key to find.
 * @return One when the key exists, otherwise zero.
 */
extern "C" s32 func_002B9B80(const FieldSequenceState30* object, float key)
{
    s16 count = object->state.unk08;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == entry_159810(object, index)->key)
        {
            return 1;
        }
    }
    return 0;
}

/** @brief Forward a vector set with a key to slot 0x74. */
extern "C" void func_002B9BD0(FieldClass159810* object, const FieldVec4A* value, float key)
{
    object->func_002B9C00(value, key);
}

void func_002B9C00(void* object)
{
}

/** @brief Forward an indexed vector insertion to slot 0x70. */
extern "C" s32 func_002B9C10(FieldClass159810* object, s32 index, float key, const FieldVec4A* value)
{
    return object->func_002B9C40(index, key, value);
}

s32 func_002B9C40(void* object)
{
    return 0;
}

/** @brief Forward an indexed vector replacement to slot 0x6C. */
extern "C" s32 func_002B9C50(FieldClass159810* object, s32 index, float key, const FieldVec4A* value)
{
    return object->func_002B9C80(index, key, value);
}

s32 func_002B9C80(void* object)
{
    return 0;
}

/** @brief Forward a vector set with a key to slot 0x68. */
extern "C" s32 func_002B9C90(FieldClass159810* object, const FieldVec4A* value, float key)
{
    return object->func_002B9CC0(value, key);
}

s32 func_002B9CC0(void* object)
{
    return 0;
}

/**
 * @brief Bind an external keyframe array.
 * @param object Sequence receiver.
 * @param count Keyframe count.
 * @param entries External keyframe storage.
 */
extern "C" void func_002B9CD0(FieldSequenceState30* object, s32 count, void* entries)
{
    object->state.unk13_1 = 1;
    object->unk04 = entries;
    object->state.unk0a = count;
    object->state.unk08 = count;
    object->state.span = entry_159810(object, count - 1)->key - entry_159810(object, 0)->key;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param object Sequence receiver.
 * @param count Requested keyframe count.
 */
extern "C" void func_002B9D20(FieldSequenceState30* object, s32 count)
{
    object->state.unk13_1 = 0;
    delete[] static_cast<FieldTrackKey159810*>(object->unk04);
    object->unk04 = new (0) FieldTrackKey159810[count];
    object->state.unk0a = count;
    if (!object->unk04)
    {
        object->state.unk0a = 0;
    }
}

FieldTrackKey159810::FieldTrackKey159810()
{
}

FieldClass159810::FieldClass159810()
{
    state.unk13_2 = false;
    func_001E94F0();
}

FieldClass1598A0::FieldClass1598A0()
{
    state.unk13_2 = false;
    func_002BAE90();
}

void FieldClass159090::func_002B9EC0(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    func_002B8D30(6);
    unk10 = *value;
    unk20 = *first;
    unk30 = *second;
    unk10.w = key;
}

s32 FieldClass159090::func_002B9F50(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    s32 count;
    s32 i;
    if (unk04 == 0)
    {
        return 0;
    }
    count = state.unk08;
    if (index >= count)
    {
        return 0;
    }
    if (count >= state.unk0a)
    {
        return 0;
    }
    for (i = count; i > index; i--)
    {
        static_cast<FieldTrackKey1595D0*>(unk04)[i] = static_cast<FieldTrackKey1595D0*>(unk04)[i - 1];
    }
    static_cast<FieldTrackKey1595D0*>(unk04)[index].value = *value;
    static_cast<FieldTrackKey1595D0*>(unk04)[index].first = *first;
    static_cast<FieldTrackKey1595D0*>(unk04)[index].second = *second;
    static_cast<FieldTrackKey1595D0*>(unk04)[index].value.w = key;
    if (index == state.unk08 - 1)
    {
        state.span = key - static_cast<FieldTrackKey1595D0*>(unk04)[0].value.w;
    }
    state.unk08++;
    return 1;
}

void FieldClass159420::func_002B9680(const float* value, float key)
{
    func_002B8990(6);
    unk0c = *value;
    unk08 = key;
}

s32 FieldClass159420::func_001DF2E0(s32 index, float* key, float* value, float* first, float* second) const
{
    if (unk04 == 0)
    {
        return 0;
    }
    if (index >= state.unk0a)
    {
        return 0;
    }
    if (key)
    {
        *key = static_cast<const FieldTrackKey1596F0*>(unk04)[index].key;
    }
    if (value)
    {
        const FieldTrackKey1596F0* entries = static_cast<const FieldTrackKey1596F0*>(unk04);
        *value = entries[index].value;
    }
    return 1;
}

s32 FieldClass159420::func_002B96C0(s32 index, float key, const float* value)
{
    s32 count;
    s32 i;
    if (unk04 == 0)
    {
        return 0;
    }
    count = state.unk08;
    if (index >= count)
    {
        return 0;
    }
    if (count >= state.unk0a)
    {
        return 0;
    }
    for (i = count; i > index; i--)
    {
        static_cast<FieldTrackKey1596F0*>(unk04)[i] = static_cast<FieldTrackKey1596F0*>(unk04)[i - 1];
    }
    FieldTrackKey1596F0* entries = static_cast<FieldTrackKey1596F0*>(unk04);
    entries[index].value = *value;
    static_cast<FieldTrackKey1596F0*>(unk04)[index].key = key;
    if (index == state.unk08 - 1)
    {
        state.span = key - static_cast<FieldTrackKey1596F0*>(unk04)[0].key;
    }
    state.unk0e = -1;
    state.unk10 = -1;
    state.unk08++;
    return 1;
}

s32 FieldClass159420::func_002B9700(s32 index, float key, const float* value)
{
    if (unk04 == 0)
    {
        return 0;
    }
    if (index >= state.unk0a)
    {
        return 0;
    }
    FieldTrackKey1596F0* entries = static_cast<FieldTrackKey1596F0*>(unk04);
    entries[index].value = *value;
    static_cast<FieldTrackKey1596F0*>(unk04)[index].key = key;
    if (index == state.unk08 - 1)
    {
        state.span = key - static_cast<FieldTrackKey1596F0*>(unk04)[0].key;
    }
    state.unk0e = -1;
    state.unk10 = -1;
    return 1;
}

s32 FieldClass159420::func_002B9740(const float* value, float key)
{
    if (unk04 == 0)
    {
        return 0;
    }
    if (state.unk08 >= state.unk0a)
    {
        return 0;
    }
    FieldTrackKey1596F0* entries = static_cast<FieldTrackKey1596F0*>(unk04);
    entries[state.unk08].value = *value;
    static_cast<FieldTrackKey1596F0*>(unk04)[state.unk08].key = key;
    state.span = key - static_cast<FieldTrackKey1596F0*>(unk04)[0].key;
    state.unk0e = -1;
    state.unk10 = -1;
    state.unk08++;
    return 1;
}

void FieldClass159270::func_002B9840(const FieldVec4A* value, float key)
{
    func_002B84A0(6);
    unk10 = *value;
    unk10.w = key;
}

s32 FieldClass159270::func_002B9880(s32 index, float key, const FieldVec4A* value)
{
    s32 count;
    s32 i;
    if (unk04 == 0)
    {
        return 0;
    }
    count = state.unk08;
    if (index >= count)
    {
        return 0;
    }
    if (count >= state.unk0a)
    {
        return 0;
    }
    for (i = count; i > index; i--)
    {
        static_cast<FieldTrackKey159780*>(unk04)[i] = static_cast<FieldTrackKey159780*>(unk04)[i - 1];
    }
    static_cast<FieldTrackKey159780*>(unk04)[index].value = *value;
    static_cast<FieldTrackKey159780*>(unk04)[index].value.w = key;
    if (index == state.unk08 - 1)
    {
        state.span = key - static_cast<FieldTrackKey159780*>(unk04)[0].value.w;
    }
    state.unk0e = -1;
    state.unk10 = -1;
    state.unk08++;
    return 1;
}

void FieldClass1591E0::func_002B9C00(const FieldVec4A* value, float key)
{
    func_002B7FB0(6);
    unk20 = *value;
    unk10 = key;
}

s32 FieldClass1591E0::func_001DF2E0(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const
{
    if (unk04 == 0)
    {
        return 0;
    }
    if (index >= state.unk0a)
    {
        return 0;
    }
    if (key)
    {
        *key = static_cast<const FieldTrackKey159810*>(unk04)[index].key;
    }
    if (value)
    {
        *value = static_cast<const FieldTrackKey159810*>(unk04)[index].value;
    }
    return 1;
}

s32 FieldClass1591E0::func_002B9C40(s32 index, float key, const FieldVec4A* value)
{
    s32 count;
    s32 i;
    if (unk04 == 0)
    {
        return 0;
    }
    count = state.unk08;
    if (index >= count)
    {
        return 0;
    }
    if (count >= state.unk0a)
    {
        return 0;
    }
    for (i = count; i > index; i--)
    {
        static_cast<FieldTrackKey159810*>(unk04)[i] = static_cast<FieldTrackKey159810*>(unk04)[i - 1];
    }
    static_cast<FieldTrackKey159810*>(unk04)[index].value = *value;
    static_cast<FieldTrackKey159810*>(unk04)[index].key = key;
    if (index == state.unk08 - 1)
    {
        state.span = key - static_cast<FieldTrackKey159810*>(unk04)[0].key;
    }
    state.unk0e = -1;
    state.unk10 = -1;
    state.unk08++;
    return 1;
}

s32 FieldClass1591E0::func_002B9C80(s32 index, float key, const FieldVec4A* value)
{
    if (unk04 == 0)
    {
        return 0;
    }
    if (index >= state.unk0a)
    {
        return 0;
    }
    static_cast<FieldTrackKey159810*>(unk04)[index].value = *value;
    static_cast<FieldTrackKey159810*>(unk04)[index].key = key;
    if (index == state.unk08 - 1)
    {
        state.span = key - static_cast<FieldTrackKey159810*>(unk04)[0].key;
    }
    state.unk0e = -1;
    state.unk10 = -1;
    return 1;
}

s32 FieldClass1591E0::func_002B9CC0(const FieldVec4A* value, float key)
{
    if (unk04 == 0)
    {
        return 0;
    }
    if (state.unk08 >= state.unk0a)
    {
        return 0;
    }
    static_cast<FieldTrackKey159810*>(unk04)[state.unk08].value = *value;
    static_cast<FieldTrackKey159810*>(unk04)[state.unk08].key = key;
    state.span = key - static_cast<FieldTrackKey159810*>(unk04)[0].key;
    state.unk0e = -1;
    state.unk10 = -1;
    state.unk08++;
    return 1;
}

void FieldClass1594B0::func_001DF300()
{
    float zero = 0.0f;
    func_002B9680(&zero, 0.0f);
    func_002B8990(1);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BA850);

void FieldClass159300::func_001DF300()
{
    FieldVec4A zero(0.0f, 0.0f, 0.0f, 0.0f);
    func_002B9840(&zero, 0.0f);
    func_002B84A0(1);
}

void func_002BAC40(FieldSequenceState10* object, u8 mode)
{
    object->state.unk12_0_3 = mode;
    object->state.unk13_0 = object->state.unk12_0_3 == 4 || object->state.unk12_4_7 == 4;
}

void FieldClass159660::func_002BACA0(s32 mode)
{
    state.unk12_0_3 = mode;
    state.unk13_0 = state.unk12_0_3 == 4 || state.unk12_4_7 == 4;
}

void func_002BAD00(FieldSequenceState40* object, u8 mode)
{
    object->state.unk12_0_3 = mode;
    object->state.unk13_0 = object->state.unk12_0_3 == 4 || object->state.unk12_4_7 == 4;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BAD60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BADE0);

void FieldClass159950::func_002BAE60()
{
}

void FieldClass159940::func_002BAE70()
{
}

void FieldClass159930::func_002BAE80()
{
}

void func_002BAE90(FieldSequenceState40* object)
{
    object->unk04 = 0;
    object->state.unk12_0_3 = 1;
    object->state.unk12_4_7 = 1;
    object->state.unk0a = 0;
    object->state.unk08 = 0;
    object->state.unk0c = -1;
    object->state.unk00 = 0;
    object->state.unk0e = -1;
    object->state.unk10 = -1;
    object->state.unk13_0 = 0;
    object->state.unk13_1 = 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param object Sequence receiver.
 * @param count Requested keyframe count.
 */
extern "C" void func_002BAF20(FieldSequenceState40* object, s32 count)
{
    object->state.unk13_1 = 0;
    delete[] static_cast<FieldTrackKey1598A0*>(object->unk04);
    object->unk04 = new (0) FieldTrackKey1598A0[count];
    object->state.unk0a = count;
    if (!object->unk04)
    {
        object->state.unk0a = 0;
    }
}

/**
 * @brief Bind an external keyframe array.
 * @param object Sequence receiver.
 * @param count Keyframe count.
 * @param entries External keyframe storage.
 */
extern "C" void func_002BAFD0(FieldSequenceState40* object, s32 count, void* entries)
{
    object->state.unk13_1 = 1;
    object->unk04 = entries;
    object->state.unk0a = count;
    object->state.unk08 = count;
    object->state.span = entry_1598A0(object, count - 1)->key - entry_1598A0(object, 0)->key;
}

void func_002BB020(FieldSequenceState40* object, u8 mode)
{
    object->state.unk12_4_7 = mode;
    object->state.unk13_0 = object->state.unk12_0_3 == 4 || object->state.unk12_4_7 == 4;
}

s32 func_002BB080(FieldSequenceState40* object)
{
    return object->state.unk00;
}

s16 func_002BB090(FieldSequenceState40* object)
{
    return object->state.unk08;
}

s16 func_002BB0A0(FieldSequenceState40* object)
{
    return object->state.unk0a;
}

s32 func_002BB0B0(void* object)
{
    return 0;
}

/** @brief Forward a vector set with a key to slot 0x68. */
extern "C" s32 func_002BB0C0(FieldClass1598A0* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return object->func_002BB0B0(value, first, second, key);
}

s32 func_002BB0F0(void* object)
{
    return 0;
}

/** @brief Forward an indexed vector replacement to slot 0x6C. */
extern "C" s32 func_002BB100(FieldClass1598A0* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->func_002BB0F0(index, key, value, first, second);
}

s32 func_002BB130(void* object)
{
    return 0;
}

/** @brief Forward an indexed vector insertion to slot 0x70. */
extern "C" s32 func_002BB140(FieldClass1598A0* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->func_002BB130(index, key, value, first, second);
}

void func_002BB170(void* object)
{
}

/** @brief Forward a vector set with a key to slot 0x74. */
extern "C" void func_002BB180(FieldClass1598A0* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    object->func_002BB170(value, first, second, key);
}

/**
 * @brief Test whether the track contains the supplied key.
 * @param object Sequence receiver.
 * @param key Key to find.
 * @return One when the key exists, otherwise zero.
 */
extern "C" s32 func_002BB1B0(const FieldSequenceState40* object, float key)
{
    s16 count = object->state.unk08;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == entry_1598A0(object, index)->key)
        {
            return 1;
        }
    }
    return 0;
}

void func_002BB200(FieldResetWords00* object)
{
    object->words[0] = 0;
    object->words[1] = 0;
    object->words[2] = 0;
    object->words[3] = 0;
}

/**
 * @brief Return the span between the first and last keys.
 * @param object Sequence receiver.
 * @return Last key minus first key, or zero with fewer than two entries.
 */
extern "C" float func_002BB220(const FieldSequenceState40* object)
{
    if (object->state.unk08 < 2)
    {
        return 0.0f;
    }
    return entry_1598A0(object, object->state.unk08 - 1)->key - entry_1598A0(object, 0)->key;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BB270);

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated vector.
 */
void FieldClass1598A0::func_002BB2E0(float key, FieldVec4B* output) const
{
    *output = func_slot80(key);
}

/**
 * @brief Wrap a key into the stored key range.
 * @param object Sequence receiver.
 * @param key Key to wrap.
 * @return The key less a whole number of key spans.
 */
extern "C" float func_002BB330(const FieldSequenceState40* object, float key)
{
    float first = entry_1598A0(object, 0)->key;
    float range = entry_1598A0(object, object->state.unk08 - 1)->key - first;
    float position = (key - first) / range;
    s32 spans;
    if (position < 0.0f)
    {
        position -= 1.0f;
    }
    spans = (s32)position;
    if (spans != 0)
    {
        return key - spans * range;
    }
    return key;
}

void* func_002BB3D0(FieldSequenceState40* object)
{
    return object->unk04;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BB3E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BB4C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BB620);

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param object Sequence receiver.
 * @param count Requested keyframe count.
 */
extern "C" void func_002BB6B0(FieldSequenceState30* object, s32 count)
{
    object->state.unk13_1 = 0;
    delete[] static_cast<FieldTrackKey159660*>(object->unk04);
    object->unk04 = new (0) FieldTrackKey159660[count];
    object->state.unk0a = count;
    if (!object->unk04)
    {
        object->state.unk0a = 0;
    }
}

void FieldClass159660::func_002BB760(s32 mode)
{
    state.unk12_4_7 = mode;
    state.unk13_0 = state.unk12_0_3 == 4 || state.unk12_4_7 == 4;
}

s32 func_002BB7C0(FieldSequenceState30* object)
{
    return object->state.unk00;
}

s16 func_002BB7D0(FieldSequenceState30* object)
{
    return object->state.unk08;
}

s16 func_002BB7E0(FieldSequenceState30* object)
{
    return object->state.unk0a;
}

s32 func_002BB7F0(void* object)
{
    return 0;
}

/** @brief Forward a vector set with a key to slot 0x68. */
extern "C" s32 func_002BB800(FieldClass159660* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return object->func_002BB7F0(value, first, second, key);
}

s32 func_002BB830(void* object)
{
    return 0;
}

/** @brief Forward an indexed vector replacement to slot 0x6C. */
extern "C" s32 func_002BB840(FieldClass159660* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->func_002BB830(index, key, value, first, second);
}

s32 func_002BB870(void* object)
{
    return 0;
}

/** @brief Forward an indexed vector insertion to slot 0x70. */
extern "C" s32 func_002BB880(FieldClass159660* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->func_002BB870(index, key, value, first, second);
}

void func_002BB8B0(void* object)
{
}

/** @brief Forward a vector set with a key to slot 0x74. */
extern "C" void func_002BB8C0(FieldClass159660* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    object->func_002BB8B0(value, first, second, key);
}

void func_002BB8F0(FieldResetWords00* object)
{
    object->words[0] = 0;
    object->words[1] = 0;
    object->words[2] = 0;
    object->words[3] = 0;
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated vector.
 */
void FieldClass159660::func_002BB910(float key, FieldVec4B* output) const
{
    *output = func_slot80(key);
}

void* func_002BB960(FieldSequenceState30* object)
{
    return object->unk04;
}

/** @brief Forward a vector set with a key to slot 0x68. */
extern "C" s32 func_002BB970(FieldClass1595D0* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return object->func_002B8E20(value, first, second, key);
}

/** @brief Forward an indexed vector set with a key to slot 0x6C. */
extern "C" s32 func_002BB9A0(FieldClass1595D0* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->func_002B8E30(index, key, value, first, second);
}

/** @brief Forward an indexed vector set with a key to slot 0x70. */
extern "C" s32 func_002BB9D0(FieldClass1595D0* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->func_002B8E40(index, key, value, first, second);
}

/** @brief Forward a vector set with a key to slot 0x74. */
extern "C" void func_002BBA00(FieldClass1595D0* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    object->func_002B8E50(value, first, second, key);
}

void func_002BBA30(FieldSequenceState10* object)
{
    object->unk04 = 0;
    object->state.unk12_0_3 = 1;
    object->state.unk12_4_7 = 1;
    object->state.unk0a = 0;
    object->state.unk08 = 0;
    object->state.unk0c = -1;
    object->state.unk00 = 0;
    object->state.unk0e = -1;
    object->state.unk10 = -1;
    object->state.unk13_0 = 0;
    object->state.unk13_1 = 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param object Sequence receiver.
 * @param count Requested keyframe count.
 */
extern "C" void func_002BBAC0(FieldSequenceState10* object, s32 count)
{
    object->state.unk13_1 = 0;
    delete[] static_cast<FieldTrackKey159540*>(object->unk04);
    object->unk04 = new (0) FieldTrackKey159540[count];
    object->state.unk0a = count;
    if (!object->unk04)
    {
        object->state.unk0a = 0;
    }
}

/**
 * @brief Bind an external keyframe array.
 * @param object Sequence receiver.
 * @param count Keyframe count.
 * @param entries External keyframe storage.
 */
extern "C" void func_002BBB60(FieldSequenceState10* object, s32 count, void* entries)
{
    object->state.unk13_1 = 1;
    object->unk04 = entries;
    object->state.unk0a = count;
    object->state.unk08 = count;
    object->state.span = key_159540(object, count - 1) - key_159540(object, 0);
}

void func_002BBBC0(FieldSequenceState10* object, u8 mode)
{
    object->state.unk12_4_7 = mode;
    object->state.unk13_0 = object->state.unk12_0_3 == 4 || object->state.unk12_4_7 == 4;
}

s32 func_002BBC20(FieldSequenceState10* object)
{
    return object->state.unk00;
}

s16 func_002BBC30(FieldSequenceState10* object)
{
    return object->state.unk08;
}

s16 func_002BBC40(FieldSequenceState10* object)
{
    return object->state.unk0a;
}

s32 func_002BBC50(void* object)
{
    return 0;
}

/** @brief Forward a vector set with a key to slot 0x68. */
extern "C" s32 func_002BBC60(FieldClass159540* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return object->func_002BBC50(value, first, second, key);
}

s32 func_002BBC90(void* object)
{
    return 0;
}

/** @brief Forward an indexed vector replacement to slot 0x6C. */
extern "C" s32 func_002BBCA0(FieldClass159540* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->func_002BBC90(index, key, value, first, second);
}

s32 func_002BBCD0(void* object)
{
    return 0;
}

/** @brief Forward an indexed vector insertion to slot 0x70. */
extern "C" s32 func_002BBCE0(FieldClass159540* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->func_002BBCD0(index, key, value, first, second);
}

void func_002BBD10(void* object)
{
}

/** @brief Forward a vector set with a key to slot 0x74. */
extern "C" void func_002BBD20(FieldClass159540* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    object->func_002BBD10(value, first, second, key);
}

/**
 * @brief Test whether the track contains the supplied key.
 * @param object Sequence receiver.
 * @param key Key to find.
 * @return One when the key exists, otherwise zero.
 */
extern "C" s32 func_002BBD50(const FieldSequenceState10* object, float key)
{
    s16 count = object->state.unk08;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == key_159540(object, index))
        {
            return 1;
        }
    }
    return 0;
}

void func_002BBDB0(FieldResetWords00* object)
{
    object->words[0] = 0;
    object->words[1] = 0;
    object->words[2] = 0;
    object->words[3] = 0;
}

/**
 * @brief Return the span between the first and last keys.
 * @param object Sequence receiver.
 * @return Last key minus first key, or zero with fewer than two entries.
 */
extern "C" float func_002BBDD0(const FieldSequenceState10* object)
{
    if (object->state.unk08 < 2)
    {
        return 0.0f;
    }
    return key_159540(object, object->state.unk08 - 1) - key_159540(object, 0);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BBE30);

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated vector.
 */
void FieldClass159540::func_002BBF20(float key, FieldVec4B* output) const
{
    *output = func_slot80(key);
}

/**
 * @brief Wrap a key into the stored key range.
 * @param object Sequence receiver.
 * @param key Key to wrap.
 * @return The key less a whole number of key spans.
 */
extern "C" float func_002BBF70(const FieldSequenceState10* object, float key)
{
    float first = key_159540(object, 0);
    float range = key_159540(object, object->state.unk08 - 1) - first;
    float position = (key - first) / range;
    s32 spans;
    if (position < 0.0f)
    {
        position -= 1.0f;
    }
    spans = (s32)position;
    if (spans != 0)
    {
        return key - spans * range;
    }
    return key;
}

void* func_002BC010(FieldSequenceState10* object)
{
    return object->unk04;
}

/**
 * @brief Wrap a key into the stored key range.
 * @param object Sequence receiver.
 * @param key Key to wrap.
 * @return The key less a whole number of key spans.
 */
extern "C" float func_002BC020(const FieldSequenceState30* object, float key)
{
    float first = entry_159660(object, 0)->key;
    float range = entry_159660(object, object->state.unk08 - 1)->key - first;
    float position = (key - first) / range;
    s32 spans;
    if (position < 0.0f)
    {
        position -= 1.0f;
    }
    spans = (s32)position;
    if (spans != 0)
    {
        return key - spans * range;
    }
    return key;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BC0B0);

/**
 * @brief Return the span between the first and last keys.
 * @param object Sequence receiver.
 * @return Last key minus first key, or zero with fewer than two entries.
 */
extern "C" float func_002BC110(const FieldSequenceState30* object)
{
    if (object->state.unk08 < 2)
    {
        return 0.0f;
    }
    return entry_159660(object, object->state.unk08 - 1)->key - entry_159660(object, 0)->key;
}

/**
 * @brief Test whether the track contains the supplied key.
 * @param object Sequence receiver.
 * @param key Key to find.
 * @return One when the key exists, otherwise zero.
 */
extern "C" s32 func_002BC160(const FieldSequenceState30* object, float key)
{
    s16 count = object->state.unk08;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == entry_159660(object, index)->key)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Bind an external keyframe array.
 * @param object Sequence receiver.
 * @param count Keyframe count.
 * @param entries External keyframe storage.
 */
extern "C" void func_002BC1B0(FieldSequenceState30* object, s32 count, void* entries)
{
    object->state.unk13_1 = 1;
    object->unk04 = entries;
    object->state.unk0a = count;
    object->state.unk08 = count;
    object->state.span = entry_159660(object, count - 1)->key - entry_159660(object, 0)->key;
}

FieldTrackKey159660::FieldTrackKey159660()
{
}

FieldTrackKey1598A0::FieldTrackKey1598A0()
{
}

/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 14.
 */
s32 func_002BC220(FieldClass150070* object)
{
    return 14;
}

void func_002BC230(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BC240);

void func_002BC260(void* object)
{
}

void func_002BC270(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BC280);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BC310);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BC370);

FieldClass159A70::~FieldClass159A70()
{
    if (unk08 != 0)
    {
        delete unk08;
        unk08 = 0;
    }
}

FieldClass159A70::FieldClass159A70()
{
    unk00 = 0;
    unk1c = 0;
    unk20 = 0;
    unk24 = 0;
    unk28 = 0;
    unk18 = 0;
    unk16 = 0;
    unk14 = 0;
    unk04 = 0;
    unk08 = 0;
    unk0c = 96.0f;
    unk10 = 5.0f;
}

void FieldClass159A70::func_002BC4F0()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BC500);
