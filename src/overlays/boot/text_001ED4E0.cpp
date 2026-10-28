#include "include_asm.h"
#include "overlays/lib/vector.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/boot/text_001ED4E0.h"
#include "overlays/boot/text_001DD3C0.h"
#include "overlays/boot/text_001E0900.h"
#include "overlays/boot/text_001FF0A0.h"
#include "overlays/boot/text_001FF9E0.h"
#include "overlays/boot/init.h"
#include "overlays/boot/resident.h"
#include "overlays/lib/render_buffer.h"

extern "C" {

extern void func_4D00B0(void* object);
void func_4B1640(void* object);
extern BootTrackPool<BootClass1711D0>* D_001B6674;
void func_001F2320(BootTrackPool<BootClass1711D0>* pool, BootClass1711D0* track);
float func_4B16C0(void* object, float key);
extern BootTrackPool<BootClass1714D0>* D_001B6668;
void func_001F22D0(BootTrackPool<BootClass1714D0>* pool, BootClass1714D0* track);
u8 func_001F4E70(BootClass171950* track, float key, s32* lower, s32* upper);
extern float D_001B668C;
void func_001F79A0(BootProgressBar* object, s32 done, s32 total);
void func_4D6430(BootClass177820* model, LibDrawBuffer* buffer);
extern void* D_001B6630;
void func_4333A0(BootClass1735A0* image, u8* data, s16 address, s16 width, s32 first, s16 x, s32 second, s32 strip_width, s16 height);
char* func_13CD50(char* destination, const char* source, u32 size);

/** Name given to every trophy texture. */
extern const char g_trophy_texture_name[];

extern const char g_new_game_node_name[];
extern const char g_continue_node_name[];
extern const char g_battle_collection_node_name[];
extern const char g_install_node_name[];
extern const char g_title_camera_node_name[];
void func_455DF0(LibDrawBuffer* buffer, s32 first, s32 second);
void func_455040(LibDrawBuffer* buffer, const BootTextureResource* resource);
void func_455150(LibDrawBuffer* buffer, BootSettings1F86C0* settings);
void func_4550F0(LibDrawBuffer* buffer, s32 count);
void func_455BD0(LibDrawBuffer* buffer, u8 mode, float distance, s32 flag);
void func_4791F0(BootClass175320* scene, u8* data);
void func_40B3A0(u8* data);
void func_473AA0(BootClass175320* scene);
s32 func_112610(BootSound1B65F8* sound, s32 key);
void func_100B40(void* allocation);
s32 func_457220(BootTrophyRecordF10* record);
void func_001F93B0(BootImage* image, s32 x, s32 y, s32 width, s32 height, s32 palette_x, s32 palette_y, s32 palette_width, s32 palette_height, u32 color,
                   s32 depth);

/**
 * @brief Recompute the checksum of a flag block from its key.
 * @param bits Flag block.
 */
void func_457520(BootResourceBits0970* bits);

void func_11F510(void* owner, void* object);

typedef struct FieldF32At050
{
    u8 pad[0x50];
    float value;
} FieldF32At050;

typedef struct FieldF32At04C
{
    u8 pad[0x4C];
    float value;
} FieldF32At04C;

typedef struct FieldU32At004
{
    u8 pad[0x4];
    u32 value;
} FieldU32At004;

typedef struct FieldU32At010
{
    u8 pad[0x10];
    u32 value;
} FieldU32At010;

typedef struct FieldS16At018
{
    u8 pad[0x18];
    s16 value;
} FieldS16At018;

typedef struct FieldU32At018
{
    u8 pad[0x18];
    u32 value;
} FieldU32At018;

typedef struct FieldS16At01A
{
    u8 pad[0x1A];
    s16 value;
} FieldS16At01A;

typedef struct FieldS16At020
{
    u8 pad[0x20];
    s16 value;
} FieldS16At020;

typedef struct FieldU32At020
{
    u8 pad[0x20];
    u32 value;
} FieldU32At020;

typedef struct FieldS16At022
{
    u8 pad[0x22];
    s16 value;
} FieldS16At022;

typedef struct FieldU32At030
{
    u8 pad[0x30];
    u32 value;
} FieldU32At030;

typedef struct FieldS16At038
{
    u8 pad[0x38];
    s16 value;
} FieldS16At038;

typedef struct FieldS16At03A
{
    u8 pad[0x3A];
    s16 value;
} FieldS16At03A;

typedef struct FieldU32At040
{
    u8 pad[0x40];
    u32 value;
} FieldU32At040;

typedef struct FieldU32At048
{
    u8 pad[0x48];
    u32 value;
} FieldU32At048;

typedef struct FieldU32At04C
{
    u8 pad[0x4C];
    u32 value;
} FieldU32At04C;

typedef struct FieldS16At048
{
    u8 pad[0x48];
    s16 value;
} FieldS16At048;

typedef struct FieldS16At04A
{
    u8 pad[0x4A];
    s16 value;
} FieldS16At04A;

BootClass177C70::~BootClass177C70()
{
}

BootClass177C70::BootClass177C70()
{
}

/**
 * @brief Release every track in the pool and its storage.
 * @param pool Pool to clear.
 */
void func_001ED610(BootTrackPool<BootClass177C70>* pool)
{
    pool->release();
}

/**
 * @brief Allocate the pool's tracks, mark them pooled and clear the used bitmap.
 * @param pool Pool to fill.
 * @param count Number of tracks.
 * @return One on success, or zero when the tracks could not be allocated.
 */
s32 func_001ED7B0(BootTrackPool<BootClass1711D0>* pool, s32 count)
{
    return pool->init(count);
}

BootClass1711D0::~BootClass1711D0()
{
}

BootClass1711D0::BootClass1711D0()
{
}

/**
 * @brief Release every track in the pool and its storage.
 * @param pool Pool to clear.
 */
void func_001EDBC0(BootTrackPool<BootClass1711D0>* pool)
{
    pool->release();
}

/**
 * @brief Allocate the pool's tracks, mark them pooled and clear the used bitmap.
 * @param pool Pool to fill.
 * @param count Number of tracks.
 * @return One on success, or zero when the tracks could not be allocated.
 */
s32 func_001EDD60(BootTrackPool<BootClass177BE0>* pool, s32 count)
{
    return pool->init(count);
}

BootClass177BE0::~BootClass177BE0()
{
}

BootClass177BE0::BootClass177BE0()
{
}

/**
 * @brief Release every track in the pool and its storage.
 * @param pool Pool to clear.
 */
void func_001EE0C0(BootTrackPool<BootClass177BE0>* pool)
{
    pool->release();
}

/**
 * @brief Allocate the pool's tracks, mark them pooled and clear the used bitmap.
 * @param pool Pool to fill.
 * @param count Number of tracks.
 * @return One on success, or zero when the tracks could not be allocated.
 */
s32 func_001EE250(BootTrackPool<BootClass174440>* pool, s32 count)
{
    return pool->init(count);
}

BootClass174440::~BootClass174440()
{
}

BootClass174440::BootClass174440()
{
}

/**
 * @brief Release every track in the pool and its storage.
 * @param pool Pool to clear.
 */
void func_001EE5C0(BootTrackPool<BootClass174440>* pool)
{
    pool->release();
}

/**
 * @brief Allocate the pool's tracks, mark them pooled and clear the used bitmap.
 * @param pool Pool to fill.
 * @param count Number of tracks.
 * @return One on success, or zero when the tracks could not be allocated.
 */
s32 func_001EE760(BootTrackPool<BootClass1730F0>* pool, s32 count)
{
    return pool->init(count);
}

BootClass1730F0::~BootClass1730F0()
{
}

BootClass1730F0::BootClass1730F0()
{
}

/**
 * @brief Release every track in the pool and its storage.
 * @param pool Pool to clear.
 */
void func_001EEAE0(BootTrackPool<BootClass1730F0>* pool)
{
    pool->release();
}

void func_001EEC80(void* object)
{
    func_4B1640(object);
}

void func_001EECA0(void* object)
{
}

/** @brief Delete the track; pooled tracks override this to return to their pool. */
void BootClass171950::func_001EECB0()
{
    delete this;
}

s32 func_001EED30(void* object)
{
    return 0;
}

s32 func_001EED40(void* object)
{
    return 0;
}

s32 func_001EED50(void* object)
{
    return 0;
}

s32 func_001EED60(void* object)
{
    return 0;
}

void func_001EED70(void* object)
{
}

void func_001EED80(void* object)
{
}

/** @brief Return a pooled track to its pool, or delete an ordinary track. */
void BootClass1711D0::func_001EECB0()
{
    if (this != 0)
    {
        if (state.pooled)
        {
            func_001EEDF0();
        }
        else
        {
            delete this;
        }
    }
}

void func_001EEDF0(BootClass1711D0* track)
{
    func_001F10C0(track);
    func_001F2320(D_001B6674, track);
}

float func_001EEE20(void* object, float key)
{
    return func_4B16C0(object, key);
}

/** @brief Return a pooled track to its pool, or delete an ordinary track. */
void BootClass1714D0::func_001EECB0()
{
    if (this != 0)
    {
        if (state.pooled)
        {
            func_slot84();
        }
        else
        {
            delete this;
        }
    }
}

void func_001EEEA0(BootClass1714D0* track)
{
    func_001F1DD0(track);
    func_001F22D0(D_001B6668, track);
}

struct ResetVectorB0_001ED4E0
{
    u8 pad[0xB0];
    FieldVec4B value;
};

void func_001EEED0(void* object)
{
    ((ResetVectorB0_001ED4E0*)object)->value = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    func_001F0C80((BootState1F0D60*)object);
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001ED4E0", func_001EEF10);

/**
 * @brief Append a keyframe.
 * @param value Keyframe value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Sort key.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootClass1710D0::func_slot84(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    if (unk04 == 0)
    {
        return 0;
    }

    if (state.unk08 >= state.unk0a)
    {
        return 0;
    }

    static_cast<BootTrackKey1719E0*>(unk04)[state.unk08].value = *value;
    static_cast<BootTrackKey1719E0*>(unk04)[state.unk08].first = *first;
    static_cast<BootTrackKey1719E0*>(unk04)[state.unk08].second = *second;
    static_cast<BootTrackKey1719E0*>(unk04)[state.unk08].value.w = key;
    state.span = key - static_cast<BootTrackKey1719E0*>(unk04)[0].value.w;
    state.unk08++;
    return 1;
}

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

/** @brief Append a keyframe, using zero vectors for missing auxiliary vectors. */
s32 BootClass1710D0::func_001F4CD0(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    FieldVec4A zero_first;
    FieldVec4A zero_second;
    second = track_vector(second, &zero_second);
    first = track_vector(first, &zero_first);
    return func_slot84(value, first, second, key);
}

/**
 * @brief Replace an indexed keyframe.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootClass1710D0::func_001EF7D0(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    if (unk04 == 0)
    {
        return 0;
    }

    if (index >= state.unk0a)
    {
        return 0;
    }

    static_cast<BootTrackKey1719E0*>(unk04)[index].value = *value;
    static_cast<BootTrackKey1719E0*>(unk04)[index].first = *first;
    static_cast<BootTrackKey1719E0*>(unk04)[index].second = *second;
    static_cast<BootTrackKey1719E0*>(unk04)[index].value.w = key;

    if (index == state.unk08 - 1)
    {
        state.span = key - static_cast<BootTrackKey1719E0*>(unk04)[0].value.w;
    }

    return 1;
}

/** @brief Replace an indexed keyframe, using zero vectors for missing auxiliary vectors. */
s32 BootClass1710D0::func_001F4D00(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    FieldVec4A zero_first;
    FieldVec4A zero_second;
    second = track_vector(second, &zero_second);
    first = track_vector(first, &zero_first);
    return func_001EF7D0(index, key, value, first, second);
}

/** @brief Insert a keyframe, using zero vectors for missing auxiliary vectors. */
s32 BootClass1710D0::func_001F4D30(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    FieldVec4A zero_first;
    FieldVec4A zero_second;
    second = track_vector(second, &zero_second);
    first = track_vector(first, &zero_first);
    return func_001F45F0(index, key, value, first, second);
}

/** @brief Store a single keyframe, using zero vectors for missing auxiliary vectors. */
void BootClass1710D0::func_001F4D60(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    FieldVec4A zero_first;
    FieldVec4A zero_second;
    second = track_vector(second, &zero_second);
    first = track_vector(first, &zero_first);
    func_001F4560(value, first, second, key);
}

/**
 * @brief Read an indexed keyframe.
 * @param index Keyframe index.
 * @param key Receives the sort key.
 * @param value Receives the value.
 * @param first Receives the first auxiliary vector.
 * @param second Receives the second auxiliary vector.
 * @return One when the index is within the capacity, otherwise zero.
 */
s32 BootClass1710D0::func_001EED60(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const
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
        *key = static_cast<const BootTrackKey1719E0*>(unk04)[index].value.w;
    }

    if (value)
    {
        *value = static_cast<const BootTrackKey1719E0*>(unk04)[index].value;
    }

    if (first)
    {
        *first = static_cast<const BootTrackKey1719E0*>(unk04)[index].first;
    }

    if (second)
    {
        *second = static_cast<const BootTrackKey1719E0*>(unk04)[index].second;
    }

    return 1;
}

/** @brief Reset to a single zero keyframe at key zero. */
void BootClass1710D0::func_001EED80()
{
    FieldVec4A zero(0.0f, 0.0f, 0.0f, 0.0f);
    func_001F4D60(&zero, &zero, &zero, 0.0f);
}

extern "C" void func_001EFAF0(const void* object, FieldVec4B* output)
{
    *output = *(const FieldVec4A*)((const u8*)object + 0xC0);
}

/**
 * @brief Return the difference between the endpoint vectors.
 * @param output Receives the difference.
 */
void BootClass1710D0::func_slot40(FieldVec4B* output) const
{
    if (unk04 != 0)
    {
        *output =
            sequence_difference(static_cast<const BootTrackKey1719E0*>(unk04)[state.unk08 - 1].value, static_cast<const BootTrackKey1719E0*>(unk04)[0].value);
    }
}

void func_001EFB90(BootState1F12B0* object)
{
    ((FieldU32At04C*)object)->value = 0;
    func_001F1180(object);
}

/** @brief Append an entry, using zero for missing components. */
s32 BootClass171280::func_001F4FD0(const float* x, const float* y, const float* z, float key)
{
    float y_value;
    float z_value;
    z_value = (z == 0) ? 0.0f : *z;
    z = &z_value;
    y_value = (y == 0) ? 0.0f : *y;
    y = &y_value;
    return func_slot84(x, y, z, key);
}

/** @brief Replace an indexed entry, using zero for missing components. */
s32 BootClass171280::func_001F5000(s32 index, float key, const float* x, const float* y, const float* z)
{
    float y_value;
    float z_value;
    z_value = (z == 0) ? 0.0f : *z;
    z = &z_value;
    y_value = (y == 0) ? 0.0f : *y;
    y = &y_value;
    return func_001F3FE0(index, key, x, y, z);
}

/** @brief Insert an entry, using zero for missing components. */
s32 BootClass171280::func_001F5030(s32 index, float key, const float* x, const float* y, const float* z)
{
    float y_value;
    float z_value;
    z_value = (z == 0) ? 0.0f : *z;
    z = &z_value;
    y_value = (y == 0) ? 0.0f : *y;
    y = &y_value;
    return func_001F3EC0(index, key, x, y, z);
}

/** @brief Store a single entry, using zero for missing components. */
void BootClass171280::func_001F5060(const float* x, const float* y, const float* z, float key)
{
    float y_value;
    float z_value;
    z_value = (z == 0) ? 0.0f : *z;
    z = &z_value;
    y_value = (y == 0) ? 0.0f : *y;
    y = &y_value;
    func_001F3E40(x, y, z, key);
}

/** @brief Reset to a single zero keyframe at key zero. */
void BootClass171280::func_001EED80()
{
    float zero = 0.0f;
    func_001F5060(&zero, &zero, &zero, 0.0f);
}

void func_001EFD70(void* object, float* value)
{
    *value = ((FieldF32At050*)object)->value;
}

void func_001EFD80(void* object, float* result)
{
    float* values = *(float**)((u8*)object + 4);

    if (values != 0)
    {
        s16 count = *(s16*)((u8*)object + 0x20);
        *result = values[count * 4 - 3] - values[1];
    }
}

BootClass171B98::BootClass171B98()
{
}

/**
 * @brief Set the range from two endpoint vectors and their tangents.
 * @param first First endpoint vector.
 * @param second First endpoint tangent.
 * @param third Second endpoint vector.
 * @param fourth Second endpoint tangent.
 * @param start Start key.
 * @param end End key.
 */
void BootClass171B98::func_001EFDD0(const FieldVec4A* first, const FieldVec4A* second, const FieldVec4A* third, const FieldVec4A* fourth, float start,
                                    float end)
{
    unk00 = *first;
    unk40 = start;
    unk20 = *second;
    unk10 = *third;
    unk44 = end;
    unk30 = *fourth;
    unk48 = end - start;

    if (unk48 == 0.0f)
    {
        unk48 = 1.0f;
    }
}

BootClass171B88::BootClass171B88()
{
}

void func_001EFE50(BootScalarRangeFE50* object, const float* first, const float* second, const float* third, const float* fourth, float start, float end)
{
    object->unk00 = *first;
    object->unk10 = start;
    object->unk08 = *second;
    object->unk04 = *third;
    object->unk14 = end;
    object->unk0C = *fourth;
    object->unk18 = end - start;

    if (object->unk18 == 0.0f)
    {
        object->unk18 = 1.0f;
    }
}

struct ResetVector90_001ED4E0
{
    u8 pad[0x90];
    FieldVec4B value;
};

void func_001EFEA0(void* object)
{
    ((ResetVector90_001ED4E0*)object)->value = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    func_001F19F0((BootState1F1AD0*)object);
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001ED4E0", func_001EFEE0);

/**
 * @brief Return the difference between the endpoint values.
 * @param output Receives the difference.
 */
void BootClass171440::func_slot40(FieldVec4B* output) const
{
    if (unk04 != 0)
    {
        *output =
            sequence_difference(static_cast<const BootTrackKey171830*>(unk04)[state.unk08 - 1].value, static_cast<const BootTrackKey171830*>(unk04)[0].value);
    }
}

extern "C" void func_001F0440(const void* object, FieldVec4B* output)
{
    *output = *(const FieldVec4A*)((const u8*)object + 0xA0);
}

void func_001F0460(BootState1F1FC0* object)
{
    ((FieldU32At048*)object)->value = 0;
    func_001F1E90(object);
}

void func_001F0480(void* object, float* result)
{
    float* values = *(float**)((u8*)object + 4);

    if (values != 0)
    {
        s16 count = *(s16*)((u8*)object + 0x18);
        *result = values[count * 2 - 1] - values[1];
    }
}

void func_001F04B0(void* object, float* value)
{
    *value = ((FieldF32At04C*)object)->value;
}

BootClass171B70::BootClass171B70()
{
    unk00 = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

BootClass171B50::BootClass171B50()
{
    unk00 = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Store a value and key in the two-entry history and count it, up to two.
 * @param value Value to store.
 * @param key Key to store.
 */
void BootClass171B50::func_001F0560(const FieldVec4A* value, float key)
{
    unk20[unk12] = *value;
    unk40[unk12] = key;

    if (++unk12 >= 2)
    {
        unk12 = 0;
    }

    if (++unk10 > 2)
    {
        unk10 = 2;
    }
}

BootClass171B30::BootClass171B30()
{
    unk00 = 0;
}

BootClass171B20::BootClass171B20()
{
    func_001F0660(this);
}

void func_001F0660(void* object)
{
    *(u16*)((u8*)object + 0x10) = 0;
    *(u16*)((u8*)object + 0x12) = 0;
    *(u32*)((u8*)object + 0x14) = 0;
    *(u32*)((u8*)object + 0x18) = 0;
}

BootClass171B10::BootClass171B10()
{
    func_001F06C0(this);
}

void func_001F06C0(void* object)
{
    *(u16*)((u8*)object + 0x10) = 0;
    *(u16*)((u8*)object + 0x12) = 0;
    *(u32*)((u8*)object + 0x14) = 0;
    *(u32*)((u8*)object + 0x18) = 0;
}

BootClass171B00::BootClass171B00()
{
    func_001F0720(this);
}

void func_001F0720(void* object)
{
    *(u16*)((u8*)object + 0x4) = 0;
    *(u16*)((u8*)object + 0x6) = 0;
    *(u32*)((u8*)object + 0x8) = 0;
    *(u32*)((u8*)object + 0xC) = 0;
}

/**
 * @brief Append a keyframe.
 * @param value Keyframe value.
 * @param key Sort key.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootClass1713B0::func_001F2890(const FieldVec4A* value, float key)
{
    if (unk04 == 0)
    {
        return 0;
    }

    if (state.unk08 >= state.unk0a)
    {
        return 0;
    }

    static_cast<BootTrackKey171830*>(unk04)[state.unk08].value = *value;
    static_cast<BootTrackKey171830*>(unk04)[state.unk08].value.w = key;
    state.span = key - static_cast<BootTrackKey171830*>(unk04)[0].value.w;
    state.unk0e = -1;
    state.unk10 = -1;
    state.unk08++;
    return 1;
}

/**
 * @brief Replace an indexed keyframe.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootClass1713B0::func_001F2850(s32 index, float key, const FieldVec4A* value)
{
    if (unk04 == 0)
    {
        return 0;
    }

    if (index >= state.unk0a)
    {
        return 0;
    }

    static_cast<BootTrackKey171830*>(unk04)[index].value = *value;
    static_cast<BootTrackKey171830*>(unk04)[index].value.w = key;

    if (index == state.unk08 - 1)
    {
        state.span = key - static_cast<BootTrackKey171830*>(unk04)[0].value.w;
    }

    state.unk0e = -1;
    state.unk10 = -1;
    return 1;
}

/**
 * @brief Read an indexed keyframe.
 * @param index Keyframe index.
 * @param key Receives the sort key.
 * @param value Receives the value.
 * @param first Unused; this track has no auxiliary vectors.
 * @param second Unused; this track has no auxiliary vectors.
 * @return One when the index is within the capacity, otherwise zero.
 */
s32 BootClass1713B0::func_001EED60(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const
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
        *key = static_cast<const BootTrackKey171830*>(unk04)[index].value.w;
    }

    if (value)
    {
        *value = static_cast<const BootTrackKey171830*>(unk04)[index].value;
    }

    return 1;
}

/** @brief Release the keyframe storage. */
BootClass171A70::~BootClass171A70()
{
    func_001F0960(this);
}

void func_001F0960(BootClass171A70* track)
{
    if (!track->state.unk13_1)
    {
        if (track->unk04)
        {
            func_100BE0((u8*)track->unk04 - 16);
        }
    }

    track->unk04 = 0;
}

float func_001F09B0(BootState1F0D60* object, float key)
{
    float first = object->entries[0].key;
    float quotient = (key - first) / object->span;

    if (key < first)
    {
        quotient -= 1.0f;
    }

    object->unk40 = quotient;

    if (object->unk40)
    {
        float result = key - (float)object->unk40 * object->span;

        if ((object->unk52_lo == 3 && object->unk40 < 0) || (object->unk52_hi == 3 && object->unk40 > 0))
        {
            s32 last_index = object->count - 1;
            BootRecord48F0E90* last_entry = object->entries + last_index;
            float last = last_entry->key;

            if (object->unk40 & 1)
            {
                result = first + (last - result);
            }
        }

        return result;
    }

    return key;
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001ED4E0", func_001F0AA0);

/** @brief Release the keyframe storage. */
BootClass1719E0::~BootClass1719E0()
{
    func_001F10C0(this);
}

void func_001F0C80(BootState1F0D60* object)
{
    object->entries = 0;
    object->unk52_lo = 1;
    object->unk52_hi = 1;
    object->capacity = 0;
    object->count = 0;
    object->unk4C = -1;
    object->unk40 = 0;
    object->unk4E = -1;
    object->unk50 = -1;
    object->unk53_bit0 = 0;
    object->unk53_bit1 = 0;
}

void func_001F0D10(BootState1F0D60* object, s32 count, BootRecord48F0E90* entries)
{
    s32 last_index = count - 1;
    BootRecord48F0E90* last;
    object->unk53_bit1 = 1;
    object->entries = entries;
    object->capacity = count;
    object->count = count;
    last = object->entries + last_index;
    object->span = last->key - object->entries[0].key;
}

void func_001F0D60(BootState1F0D60* state, u32 value)
{
    state->unk52_lo = value;
    state->unk53_bit0 = state->unk52_lo == 4 || state->unk52_hi == 4;
}

void func_001F0DC0(BootState1F0D60* state, u32 value)
{
    state->unk52_hi = value;
    state->unk53_bit0 = state->unk52_lo == 4 || state->unk52_hi == 4;
}

u32 func_001F0E20(void* object)
{
    return ((FieldU32At040*)object)->value;
}

s16 func_001F0E30(void* object)
{
    return ((FieldS16At048*)object)->value;
}

s16 func_001F0E40(void* object)
{
    return ((FieldS16At04A*)object)->value;
}

s32 func_001F0E50(void* object)
{
    return 0;
}

s32 func_001F0E60(void* object)
{
    return 0;
}

s32 func_001F0E70(void* object)
{
    return 0;
}

void func_001F0E80(void* object)
{
}

s32 func_001F0E90(BootState1F0D60* object, float key)
{
    s32 index;

    for (index = 0; index < object->count; index++)
    {
        if (key == object->entries[index].key)
        {
            return 1;
        }
    }

    return 0;
}

void func_001F0EE0(void* object)
{
    *(u32*)((u8*)object + 0x0) = 0;
    *(u32*)((u8*)object + 0x4) = 0;
    *(u32*)((u8*)object + 0x8) = 0;
    *(u32*)((u8*)object + 0xC) = 0;
}

float func_001F0F00(BootState1F0D60* object)
{
    s32 last_index;
    BootRecord48F0E90* last_entry;

    if (object->count < 2)
    {
        return 0.0f;
    }

    last_index = object->count - 1;
    last_entry = object->entries + last_index;
    return last_entry->key - object->entries[0].key;
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001ED4E0", func_001F0F50__15BootClass1719E0CFf);

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void BootClass1719E0::func_001F0FC0(float key, FieldVec4B* output) const
{
    *output = func_slot80(key);
}

float func_001F1010(BootState1F0D60* object, float key)
{
    s32 last_index = object->count - 1;
    BootRecord48F0E90* entries = object->entries;
    BootRecord48F0E90* last = entries + last_index;
    float first = entries[0].key;
    float span = last->key - first;
    float quotient = (key - first) / span;
    s32 periods;

    if (quotient < 0.0f)
    {
        quotient -= 1.0f;
    }

    periods = quotient;

    if (periods != 0)
    {
        return key - (float)periods * span;
    }

    return key;
}

u32 func_001F10B0(void* object)
{
    return ((FieldU32At004*)object)->value;
}

void func_001F10C0(BootClass1719E0* track)
{
    if (!track->state.unk13_1)
    {
        if (track->unk04)
        {
            func_100BE0((u8*)track->unk04 - 16);
        }
    }

    track->unk04 = 0;
}

/** @brief Release the keyframe storage. */
BootClass171950::~BootClass171950()
{
    func_001F1430(this);
}

void func_001F1180(BootState1F12B0* object)
{
    object->entries = 0;
    object->unk2A_lo = 1;
    object->unk2A_hi = 1;
    object->capacity = 0;
    object->count = 0;
    object->unk24 = -1;
    object->unk18 = 0;
    object->unk26 = -1;
    object->unk28 = -1;
    object->unk2B_bit0 = 0;
    object->unk2B_bit1 = 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param count Requested keyframe count.
 */
void BootClass171950::func_001F1210(s32 count)
{
    state.unk13_1 = 0;
    delete[] unk04;
    unk04 = new (0) BootTrackKey171950[count];
    state.unk0a = count;

    if (!unk04)
    {
        state.unk0a = 0;
    }
}

void func_001F12B0(BootState1F12B0* state, u32 value)
{
    state->unk2A_lo = value;
    state->unk2B_bit0 = state->unk2A_lo == 4 || state->unk2A_hi == 4;
}

void func_001F1310(BootState1F12B0* state, u32 value)
{
    state->unk2A_hi = value;
    state->unk2B_bit0 = state->unk2A_lo == 4 || state->unk2A_hi == 4;
}

u32 func_001F1370(void* object)
{
    return ((FieldU32At018*)object)->value;
}

s16 func_001F1380(void* object)
{
    return ((FieldS16At020*)object)->value;
}

s16 func_001F1390(void* object)
{
    return ((FieldS16At022*)object)->value;
}

s32 func_001F13A0(void* object)
{
    return 0;
}

s32 func_001F13B0(void* object)
{
    return 0;
}

s32 func_001F13C0(void* object)
{
    return 0;
}

void func_001F13D0(void* object)
{
}

float func_001F13E0(void* object)
{
    return 0.0f;
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void BootClass171950::func_001F13F0(float key, float* output)
{
    *output = func_slot80(key);
}

u32 func_001F1420(void* object)
{
    return ((FieldU32At004*)object)->value;
}

void func_001F1430(BootClass171950* track)
{
    if (!track->state.unk13_1)
    {
        if (track->unk04)
        {
            func_100BE0((u8*)track->unk04 - 16);
        }
    }

    track->unk04 = 0;
}

/** @brief Release the keyframe storage. */
BootClass1718C0::~BootClass1718C0()
{
    func_001F16F0(this);
}

void func_001F14F0(BootState1F1580* object)
{
    object->entries = 0;
    object->unk42_lo = 1;
    object->unk42_hi = 1;
    object->capacity = 0;
    object->count = 0;
    object->unk3C = -1;
    object->unk30 = 0;
    object->unk3E = -1;
    object->unk40 = -1;
    object->unk43_bit0 = 0;
    object->unk43_bit1 = 0;
}

void func_001F1580(BootState1F1580* state, u32 value)
{
    state->unk42_lo = value;
    state->unk43_bit0 = state->unk42_lo == 4 || state->unk42_hi == 4;
}

void func_001F15E0(BootState1F1580* state, u32 value)
{
    state->unk42_hi = value;
    state->unk43_bit0 = state->unk42_lo == 4 || state->unk42_hi == 4;
}

u32 func_001F1640(void* object)
{
    return ((FieldU32At030*)object)->value;
}

s16 func_001F1650(void* object)
{
    return ((FieldS16At038*)object)->value;
}

s16 func_001F1660(void* object)
{
    return ((FieldS16At03A*)object)->value;
}

void func_001F1670(void* object)
{
    *(u32*)((u8*)object + 0x0) = 0;
    *(u32*)((u8*)object + 0x4) = 0;
    *(u32*)((u8*)object + 0x8) = 0;
    *(u32*)((u8*)object + 0xC) = 0;
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void BootClass1718C0::func_001F1690(float key, FieldVec4B* output) const
{
    *output = func_slot80(key);
}

u32 func_001F16E0(void* object)
{
    return ((FieldU32At004*)object)->value;
}

void func_001F16F0(BootClass1718C0* track)
{
    if (!track->state.unk13_1)
    {
        if (track->unk04)
        {
            func_100BE0((u8*)track->unk04 - 16);
        }
    }

    track->unk04 = 0;
}

float func_001F1740(BootState1F1AD0* object, float key)
{
    float first = object->entries[0].key;
    float quotient = (key - first) / object->span;

    if (key < first)
    {
        quotient -= 1.0f;
    }

    object->unk20 = quotient;

    if (object->unk20)
    {
        float result = key - (float)object->unk20 * object->span;

        if ((object->unk32_lo == 3 && object->unk20 < 0) || (object->unk32_hi == 3 && object->unk20 > 0))
        {
            s32 last_index = object->count - 1;
            BootVectorKeyEntry1F1D30* last_entry = object->entries + last_index;
            float last = last_entry->key;

            if (object->unk20 & 1)
            {
                result = first + (last - result);
            }
        }

        return result;
    }

    return key;
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001ED4E0", func_001F1820);

/** @brief Release the keyframe storage. */
BootClass171830::~BootClass171830()
{
    func_001F1DD0(this);
}

void func_001F19F0(BootState1F1AD0* object)
{
    object->entries = 0;
    object->unk32_lo = 1;
    object->unk32_hi = 1;
    object->capacity = 0;
    object->count = 0;
    object->unk2C = -1;
    object->unk20 = 0;
    object->unk2E = -1;
    object->unk30 = -1;
    object->unk33_bit0 = 0;
    object->unk33_bit1 = 0;
}

void func_001F1A80(BootState1F1AD0* object, s32 count, BootVectorKeyEntry1F1D30* entries)
{
    s32 last_index = count - 1;
    BootVectorKeyEntry1F1D30* last;
    object->unk33_bit1 = 1;
    object->entries = entries;
    object->capacity = count;
    object->count = count;
    last = object->entries + last_index;
    object->span = last->key - object->entries[0].key;
}

void func_001F1AD0(BootState1F1AD0* state, u32 value)
{
    state->unk32_lo = value;
    state->unk33_bit0 = state->unk32_lo == 4 || state->unk32_hi == 4;
}

void func_001F1B30(BootState1F1AD0* state, u32 value)
{
    state->unk32_hi = value;
    state->unk33_bit0 = state->unk32_lo == 4 || state->unk32_hi == 4;
}

u32 func_001F1B90(void* object)
{
    return ((FieldU32At020*)object)->value;
}

s16 func_001F1BA0(BootState1F1AD0* object)
{
    return object->count;
}

s16 func_001F1BB0(BootState1F1AD0* object)
{
    return object->capacity;
}

s32 func_001F1BC0(BootState1F1AD0* object, float key)
{
    s32 index;

    for (index = 0; index < object->count; index++)
    {
        if (key == object->entries[index].key)
        {
            return 1;
        }
    }

    return 0;
}

void func_001F1C10(void* object)
{
    *(u32*)((u8*)object + 0x0) = 0;
    *(u32*)((u8*)object + 0x4) = 0;
    *(u32*)((u8*)object + 0x8) = 0;
    *(u32*)((u8*)object + 0xC) = 0;
}

float func_001F1C30(BootState1F1AD0* object)
{
    BootVectorKeyEntry1F1D30* last;

    if (object->count < 2)
    {
        return 0.0f;
    }

    last = object->entries + (object->count - 1);
    return last->key - object->entries[0].key;
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001ED4E0", func_001F1C80);

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void BootClass171830::func_001F1CE0(float key, FieldVec4B* output) const
{
    *output = func_slot80(key);
}

float func_001F1D30(BootState1F1AD0* object, float key)
{
    BootVectorKeyEntry1F1D30* last = object->entries + (object->count - 1);
    float first = object->entries[0].key;
    float span = last->key - first;
    float position = (key - first) / span;
    s32 cycles;

    if (position < 0.0f)
    {
        position -= 1.0f;
    }

    cycles = (s32)position;

    if (cycles != 0)
    {
        return key - cycles * span;
    }

    return key;
}

u32 func_001F1DC0(void* object)
{
    return ((FieldU32At004*)object)->value;
}

void func_001F1DD0(BootClass171830* track)
{
    if (!track->state.unk13_1)
    {
        if (track->unk04)
        {
            func_100BE0((u8*)track->unk04 - 16);
        }
    }

    track->unk04 = 0;
}

/** @brief Release the keyframe storage. */
BootClass1717A0::~BootClass1717A0()
{
    func_001F2100(this);
}

void func_001F1E90(BootState1F1FC0* object)
{
    object->entries = 0;
    object->unk22_lo = 1;
    object->unk22_hi = 1;
    object->capacity = 0;
    object->count = 0;
    object->unk1C = -1;
    object->unk10 = 0;
    object->unk1E = -1;
    object->unk20 = -1;
    object->unk23_bit0 = 0;
    object->unk23_bit1 = 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param count Requested keyframe count.
 */
void BootClass1717A0::func_001F1F20(s32 count)
{
    state.unk13_1 = 0;
    delete[] static_cast<BootTrackKey1717A0*>(unk04);
    unk04 = new (0) BootTrackKey1717A0[count];
    state.unk0a = count;

    if (!unk04)
    {
        state.unk0a = 0;
    }
}

void func_001F1FC0(BootState1F1FC0* state, u32 value)
{
    state->unk22_lo = value;
    state->unk23_bit0 = state->unk22_lo == 4 || state->unk22_hi == 4;
}

void func_001F2020(BootState1F1FC0* state, u32 value)
{
    state->unk22_hi = value;
    state->unk23_bit0 = state->unk22_lo == 4 || state->unk22_hi == 4;
}

u32 func_001F2080(void* object)
{
    return ((FieldU32At010*)object)->value;
}

s16 func_001F2090(void* object)
{
    return ((FieldS16At018*)object)->value;
}

s16 func_001F20A0(void* object)
{
    return ((FieldS16At01A*)object)->value;
}

float func_001F20B0(void* object)
{
    return 0.0f;
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void BootClass1717A0::func_001F20C0(float key, float* output) const
{
    *output = func_slot80(key);
}

u32 func_001F20F0(void* object)
{
    return ((FieldU32At004*)object)->value;
}

void func_001F2100(BootClass1717A0* track)
{
    if (!track->state.unk13_1)
    {
        if (track->unk04)
        {
            func_100BE0((u8*)track->unk04 - 16);
        }
    }

    track->unk04 = 0;
}

/** @brief Release the keyframe storage. */
BootClass171710::~BootClass171710()
{
    func_001F21C0(this);
}

void func_001F21C0(BootClass171710* track)
{
    if (!track->state.unk13_1)
    {
        if (track->unk04)
        {
            func_100BE0((u8*)track->unk04 - 16);
        }
    }

    track->unk04 = 0;
}

/** @brief Release the keyframe storage. */
BootClass171680::~BootClass171680()
{
    func_001F2280(this);
}

void func_001F2280(BootClass171680* track)
{
    if (!track->state.unk13_1)
    {
        if (track->unk04)
        {
            func_100BE0((u8*)track->unk04 - 16);
        }
    }

    track->unk04 = 0;
}

/**
 * @brief Mark a track's pool slot as free.
 * @param pool Pool that owns the track.
 * @param track Track to release.
 */
void func_001F22D0(BootTrackPool<BootClass1714D0>* pool, BootClass1714D0* track)
{
    pool->free(track);
}

/**
 * @brief Mark a track's pool slot as free.
 * @param pool Pool that owns the track.
 * @param track Track to release.
 */
void func_001F2320(BootTrackPool<BootClass1711D0>* pool, BootClass1711D0* track)
{
    pool->free(track);
}

/** @brief Clear the pooled flag and reset the sequence. */
BootClass171680::BootClass171680()
{
    state.pooled = false;
    func_001F58C0();
}

/** @brief Clear the pooled flag and reset the sequence. */
BootClass171710::BootClass171710()
{
    state.pooled = false;
    func_001F52D0();
}

float func_001F2450(BootState1F1FC0* object, float key)
{
    s32 last_index = object->count - 1;
    float first = object->entries[0].key;
    float span = object->entries[last_index].key - first;
    float position = (key - first) / span;
    s32 cycles;

    if (position < 0.0f)
    {
        position -= 1.0f;
    }

    cycles = (s32)position;

    if (cycles != 0)
    {
        return key - cycles * span;
    }

    return key;
}

float func_001F24E0(BootState1F1FC0* object, float key)
{
    s32 index;

    for (index = 0; index < object->count; index++)
    {
        if (key == object->entries[index].key)
        {
            BootFloatEntry1F33B0* entry = object->entries + index;
            return entry->value;
        }
    }

    return 0.0f;
}

float func_001F2540(BootState1F1FC0* object)
{
    s32 last_index;

    if (object->count < 2)
    {
        return 0.0f;
    }

    last_index = object->count - 1;
    return object->entries[last_index].key - object->entries[0].key;
}

s32 func_001F2590(BootState1F1FC0* object, float key)
{
    s32 index;

    for (index = 0; index < object->count; index++)
    {
        if (key == object->entries[index].key)
        {
            return 1;
        }
    }

    return 0;
}

/** @brief Forward a keyframe with a key to slot 0x74. */
void func_001F25E0(BootClass1717A0* object, const float* value, float key)
{
    object->func_001F2610(value, key);
}

void func_001F2610(void* object)
{
}

/** @brief Forward an indexed keyframe with a key to slot 0x70. */
s32 func_001F2620(BootClass1717A0* object, s32 index, float key, const float* value)
{
    return object->func_001F2650(index, key, value);
}

s32 func_001F2650(void* object)
{
    return 0;
}

/** @brief Forward an indexed keyframe with a key to slot 0x6C. */
s32 func_001F2660(BootClass1717A0* object, s32 index, float key, const float* value)
{
    return object->func_001F2690(index, key, value);
}

s32 func_001F2690(void* object)
{
    return 0;
}

/** @brief Forward a keyframe with a key to slot 0x68. */
s32 func_001F26A0(BootClass1717A0* object, const float* value, float key)
{
    return object->func_001F26D0(value, key);
}

s32 func_001F26D0(void* object)
{
    return 0;
}

void func_001F26E0(BootState1F1FC0* object, s32 count, BootFloatEntry1F33B0* entries)
{
    s32 last_index = count - 1;
    object->unk23_bit1 = 1;
    object->entries = entries;
    object->capacity = count;
    object->count = count;
    object->span = object->entries[last_index].key - object->entries[0].key;
}

/** @brief Clear the pooled flag and reset the sequence. */
BootClass1717A0::BootClass1717A0()
{
    state.pooled = false;
    func_001F1E90();
}

/** @brief Forward to slot 0x74. */
void func_001F27A0(BootClass171830* object, const FieldVec4A* value, float key)
{
    object->func_001F27D0(value, key);
}

void func_001F27D0(void* object)
{
}

/** @brief Forward to slot 0x70. */
s32 func_001F27E0(BootClass171830* object, s32 index, float key, const FieldVec4A* value)
{
    return object->func_001F2810(index, key, value);
}

s32 func_001F2810(void* object)
{
    return 0;
}

/** @brief Forward to slot 0x6C. */
s32 func_001F2820(BootClass171830* object, s32 index, float key, const FieldVec4A* value)
{
    return object->func_001F2850(index, key, value);
}

s32 func_001F2850(void* object)
{
    return 0;
}

/** @brief Forward to slot 0x68. */
s32 func_001F2860(BootClass171830* object, const FieldVec4A* value, float key)
{
    return object->func_001F2890(value, key);
}

s32 func_001F2890(void* object)
{
    return 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param count Requested keyframe count.
 */
void BootClass171830::func_001F28A0(s32 count)
{
    state.unk13_1 = 0;
    delete[] static_cast<BootTrackKey171830*>(unk04);
    unk04 = new (0) BootTrackKey171830[count];
    state.unk0a = count;

    if (!unk04)
    {
        state.unk0a = 0;
    }
}

/** @brief Clear the pooled flag and reset the sequence. */
BootClass171830::BootClass171830()
{
    state.pooled = false;
    func_001F19F0();
}

float func_001F29D0(BootState1F1580* object, float key)
{
    s32 last_index = object->count - 1;
    BootKeyEntry32* entries = object->entries;
    BootKeyEntry32* last = entries + last_index;
    float first = entries[0].key;
    float span = last->key - first;
    float quotient = (key - first) / span;
    s32 periods;

    if (quotient < 0.0f)
    {
        quotient -= 1.0f;
    }

    periods = quotient;

    if (periods != 0)
    {
        return key - (float)periods * span;
    }

    return key;
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001ED4E0", func_001F2A60);

float func_001F2AC0(BootState1F1580* object)
{
    s32 last_index;
    BootKeyEntry32* last_entry;

    if (object->count < 2)
    {
        return 0.0f;
    }

    last_index = object->count - 1;
    last_entry = object->entries + last_index;
    return last_entry->key - object->entries[0].key;
}

s32 func_001F2B10(BootState1F1580* object, float key)
{
    s32 index;

    for (index = 0; index < object->count; index++)
    {
        if (key == object->entries[index].key)
        {
            return 1;
        }
    }

    return 0;
}

/** @brief Forward to slot 0x74. */
void func_001F2B60(BootClass1718C0* object, const FieldVec4A* value, float key)
{
    object->func_001F2B90(value, key);
}

void func_001F2B90(void* object)
{
}

/** @brief Forward to slot 0x70. */
s32 func_001F2BA0(BootClass1718C0* object, s32 index, float key, const FieldVec4A* value)
{
    return object->func_001F2BD0(index, key, value);
}

s32 func_001F2BD0(void* object)
{
    return 0;
}

/** @brief Forward to slot 0x6C. */
s32 func_001F2BE0(BootClass1718C0* object, s32 index, float key, const FieldVec4A* value)
{
    return object->func_001F2C10(index, key, value);
}

s32 func_001F2C10(void* object)
{
    return 0;
}

/** @brief Forward to slot 0x68. */
s32 func_001F2C20(BootClass1718C0* object, const FieldVec4A* value, float key)
{
    return object->func_001F2C50(value, key);
}

s32 func_001F2C50(void* object)
{
    return 0;
}

void func_001F2C60(BootState1F1580* object, s32 count, BootKeyEntry32* entries)
{
    s32 last_index = count - 1;
    BootKeyEntry32* last;
    object->unk43_bit1 = 1;
    object->entries = entries;
    object->capacity = count;
    object->count = count;
    last = object->entries + last_index;
    object->span = last->key - object->entries[0].key;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param count Requested keyframe count.
 */
void BootClass1718C0::func_001F2CB0(s32 count)
{
    state.unk13_1 = 0;
    delete[] static_cast<BootTrackKey1718C0*>(unk04);
    unk04 = new (0) BootTrackKey1718C0[count];
    state.unk0a = count;

    if (!unk04)
    {
        state.unk0a = 0;
    }
}

BootTrackKey1718C0::BootTrackKey1718C0()
{
}

/** @brief Clear the pooled flag and reset the sequence. */
BootClass1718C0::BootClass1718C0()
{
    state.pooled = false;
    func_001F14F0();
}

float func_001F2DE0(BootState1F12B0* object, float key)
{
    s32 last_index = object->count - 1;
    BootKeyEntry16* entries = object->entries;
    BootKeyEntry16* last = entries + last_index;
    float first = entries[0].key;
    float span = last->key - first;
    float quotient = (key - first) / span;
    s32 periods;

    if (quotient < 0.0f)
    {
        quotient -= 1.0f;
    }

    periods = quotient;

    if (periods != 0)
    {
        return key - (float)periods * span;
    }

    return key;
}

float func_001F2E70(BootState1F12B0* object, float key)
{
    s32 index;

    for (index = 0; index < object->count; index++)
    {
        if (key == object->entries[index].key)
        {
            BootKeyEntry16* entry = object->entries + index;
            return entry->value;
        }
    }

    return 0.0f;
}

float func_001F2ED0(BootState1F12B0* object)
{
    s32 last_index;
    BootKeyEntry16* last_entry;

    if (object->count < 2)
    {
        return 0.0f;
    }

    last_index = object->count - 1;
    last_entry = object->entries + last_index;
    return last_entry->key - object->entries[0].key;
}

s32 func_001F2F20(BootState1F12B0* object, float key)
{
    s32 index;

    for (index = 0; index < object->count; index++)
    {
        if (key == object->entries[index].key)
        {
            return 1;
        }
    }

    return 0;
}

void func_001F2F70(BootState1F12B0* object, s32 count, BootKeyEntry16* entries)
{
    s32 last_index = count - 1;
    BootKeyEntry16* last;
    object->unk2B_bit1 = 1;
    object->entries = entries;
    object->capacity = count;
    object->count = count;
    last = object->entries + last_index;
    object->span = last->key - object->entries[0].key;
}

/** @brief Clear the pooled flag and reset the sequence. */
BootClass171950::BootClass171950()
{
    state.pooled = false;
    func_001F1180();
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param count Requested keyframe count.
 */
void BootClass1719E0::func_001F3030(s32 count)
{
    state.unk13_1 = 0;
    delete[] static_cast<BootTrackKey1719E0*>(unk04);
    unk04 = new (0) BootTrackKey1719E0[count];
    state.unk0a = count;

    if (!unk04)
    {
        state.unk0a = 0;
    }
}

/** @brief Clear the pooled flag and reset the sequence. */
BootClass1719E0::BootClass1719E0()
{
    state.pooled = false;
    func_001F0C80();
}

/** @brief Clear the pooled flag and reset the sequence. */
BootClass171A70::BootClass171A70()
{
    state.pooled = false;
    func_001F4980();
}

/**
 * @brief Store a single keyframe in the cached key and value.
 * @param value Keyframe value.
 * @param key Sort key.
 */
void BootClass171560::func_001F2610(const float* value, float key)
{
    func_001F1FC0(6);
    unk0c = *value;
    unk08 = key;
}

s32 func_001F3230(BootState1F1FC0* object, s32 index, float* key, float* value)
{
    if (object->entries == 0)
    {
        return 0;
    }

    if (index >= object->capacity)
    {
        return 0;
    }

    if (key != 0)
    {
        *key = object->entries[index].key;
    }

    if (value != 0)
    {
        *value = object->entries[index].value;
    }

    return 1;
}

s32 func_001F32B0(BootState1F1FC0* object, s32 index, const float* value, float key)
{
    s32 cursor;

    if (object->entries == 0)
    {
        return 0;
    }

    if (index >= object->count)
    {
        return 0;
    }

    if (object->count >= object->capacity)
    {
        return 0;
    }

    for (cursor = object->count; cursor > index; cursor--)
    {
        BootFloatEntry1F33B0* destination = &object->entries[cursor];
        BootFloatEntry1F33B0* source = &object->entries[cursor - 1];
        destination->key = source->key;
        destination->value = source->value;
    }

    object->entries[index].value = *value;
    object->entries[index].key = key;

    if (index == object->count - 1)
    {
        object->span = key - object->entries[0].key;
    }

    object->unk1E = -1;
    object->unk20 = -1;
    object->count++;
    return 1;
}

s32 func_001F33B0(BootState1F1FC0* object, s32 index, const float* value, float key)
{
    if (object->entries == 0)
    {
        return 0;
    }

    if (index >= object->capacity)
    {
        return 0;
    }

    object->entries[index].value = *value;
    object->entries[index].key = key;

    if (index == object->count - 1)
    {
        object->span = key - object->entries[0].key;
    }

    object->unk1E = -1;
    object->unk20 = -1;
    return 1;
}

s32 func_001F3440(BootState1F1FC0* object, const float* value, float key)
{
    if (object->entries == 0)
    {
        return 0;
    }

    if (object->count >= object->capacity)
    {
        return 0;
    }

    object->entries[object->count].value = *value;
    object->entries[object->count].key = key;
    object->span = key - object->entries[0].key;
    object->unk1E = -1;
    object->unk20 = -1;
    object->count++;
    return 1;
}

/**
 * @brief Store a single keyframe in the cached value.
 * @param value Keyframe value.
 * @param key Key, stored in the value's fourth component.
 */
void BootClass1713B0::func_001F27D0(const FieldVec4A* value, float key)
{
    func_001F1AD0(6);
    unk10 = *value;
    unk10.w = key;
}

/**
 * @brief Insert a keyframe at an index.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootClass1713B0::func_001F2810(s32 index, float key, const FieldVec4A* value)
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
        static_cast<BootTrackKey171830*>(unk04)[i] = static_cast<BootTrackKey171830*>(unk04)[i - 1];
    }

    static_cast<BootTrackKey171830*>(unk04)[index].value = *value;
    static_cast<BootTrackKey171830*>(unk04)[index].value.w = key;

    if (index == state.unk08 - 1)
    {
        state.span = key - static_cast<BootTrackKey171830*>(unk04)[0].value.w;
    }

    state.unk0e = -1;
    state.unk10 = -1;
    state.unk08++;
    return 1;
}

/**
 * @brief Store a single keyframe in the cached key and value.
 * @param value Keyframe value.
 * @param key Sort key.
 */
void BootClass171320::func_001F2B90(const FieldVec4A* value, float key)
{
    func_001F1580(6);
    unk20 = *value;
    unk10 = key;
}

/**
 * @brief Read an indexed keyframe.
 * @param index Keyframe index.
 * @param key Receives the sort key.
 * @param value Receives the value.
 * @param first Unused; this track has no auxiliary vectors.
 * @param second Unused; this track has no auxiliary vectors.
 * @return One when the index is within the capacity, otherwise zero.
 */
s32 BootClass171320::func_001EED60(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const
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
        *key = static_cast<const BootTrackKey1718C0*>(unk04)[index].key;
    }

    if (value)
    {
        *value = static_cast<const BootTrackKey1718C0*>(unk04)[index].value;
    }

    return 1;
}

/**
 * @brief Insert a keyframe at an index.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootClass171320::func_001F2BD0(s32 index, float key, const FieldVec4A* value)
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
        static_cast<BootTrackKey1718C0*>(unk04)[i] = static_cast<BootTrackKey1718C0*>(unk04)[i - 1];
    }

    static_cast<BootTrackKey1718C0*>(unk04)[index].value = *value;
    static_cast<BootTrackKey1718C0*>(unk04)[index].key = key;

    if (index == state.unk08 - 1)
    {
        state.span = key - static_cast<BootTrackKey1718C0*>(unk04)[0].key;
    }

    state.unk0e = -1;
    state.unk10 = -1;
    state.unk08++;
    return 1;
}

/**
 * @brief Replace an indexed keyframe.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootClass171320::func_001F2C10(s32 index, float key, const FieldVec4A* value)
{
    if (unk04 == 0)
    {
        return 0;
    }

    if (index >= state.unk0a)
    {
        return 0;
    }

    static_cast<BootTrackKey1718C0*>(unk04)[index].value = *value;
    static_cast<BootTrackKey1718C0*>(unk04)[index].key = key;

    if (index == state.unk08 - 1)
    {
        state.span = key - static_cast<BootTrackKey1718C0*>(unk04)[0].key;
    }

    state.unk0e = -1;
    state.unk10 = -1;
    return 1;
}

/**
 * @brief Append a keyframe.
 * @param value Keyframe value.
 * @param key Sort key.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootClass171320::func_001F2C50(const FieldVec4A* value, float key)
{
    if (unk04 == 0)
    {
        return 0;
    }

    if (state.unk08 >= state.unk0a)
    {
        return 0;
    }

    static_cast<BootTrackKey1718C0*>(unk04)[state.unk08].value = *value;
    static_cast<BootTrackKey1718C0*>(unk04)[state.unk08].key = key;
    state.span = key - static_cast<BootTrackKey1718C0*>(unk04)[0].key;
    state.unk0e = -1;
    state.unk10 = -1;
    state.unk08++;
    return 1;
}

/** @brief Reset to a single zero keyframe at key zero, then set the lower mode to one. */
void BootClass1715F0::func_001EED80()
{
    float zero = 0.0f;
    func_001F2610(&zero, 0.0f);
    func_001F1FC0(1);
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001ED4E0", func_001F3990);

/** @brief Reset to a single zero keyframe at key zero, then set the lower mode to one. */
void BootClass171440::func_001EED80()
{
    FieldVec4A zero(0.0f, 0.0f, 0.0f, 0.0f);
    func_001F27D0(&zero, 0.0f);
    func_001F1AD0(1);
}

s32 func_001F3D80(BootState1F12B0* object, s32 index, float* key, float* first, float* second, float* third)
{
    if (!object->entries)
    {
        return 0;
    }

    if (index >= object->capacity)
    {
        return 0;
    }

    if (key)
    {
        *key = object->entries[index].key;
    }

    if (first)
    {
        *first = object->entries[index].value;
    }

    if (second)
    {
        *second = object->entries[index].second;
    }

    if (third)
    {
        *third = object->entries[index].third;
    }

    return 1;
}

/**
 * @brief Store a single entry in the cached entry.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 * @param key Sort value.
 */
void BootClass171280::func_001F3E40(const float* x, const float* y, const float* z, float key)
{
    func_001F12B0(6);
    unk08.unk04 = *x;
    unk08.unk08 = *y;
    unk08.unk0c = *z;
    unk08.unk00 = key;
}

s32 func_001F3EC0(BootState1F12B0* object, s32 index, const float* first, const float* second, const float* third, float key)
{
    s32 cursor;

    if (!object->entries)
    {
        return 0;
    }

    if (index >= object->count)
    {
        return 0;
    }

    if (object->count >= object->capacity)
    {
        return 0;
    }

    for (cursor = object->count; cursor > index; cursor--)
    {
        BootKeyEntry16* destination = &object->entries[cursor];
        BootKeyEntry16* source = &object->entries[cursor - 1];
        destination->key = source->key;
        destination->value = source->value;
        destination->second = source->second;
        destination->third = source->third;
    }

    object->entries[index].value = *first;
    object->entries[index].second = *second;
    object->entries[index].third = *third;
    object->entries[index].key = key;

    if (index == object->count - 1)
    {
        object->span = key - object->entries[0].key;
    }

    object->count++;
    return 1;
}

s32 func_001F3FE0(BootState1F12B0* object, s32 index, const float* first, const float* second, const float* third, float key)
{
    if (!object->entries)
    {
        return 0;
    }

    if (index >= object->capacity)
    {
        return 0;
    }

    object->entries[index].value = *first;
    object->entries[index].second = *second;
    object->entries[index].third = *third;
    object->entries[index].key = key;

    if (index == object->count - 1)
    {
        object->span = key - object->entries[0].key;
    }

    return 1;
}

s32 func_001F4080(BootState1F12B0* object, const float* first, const float* second, const float* third, float key)
{
    if (!object->entries)
    {
        return 0;
    }

    if (object->count >= object->capacity)
    {
        return 0;
    }

    object->entries[object->count].value = *first;
    object->entries[object->count].second = *second;
    object->entries[object->count].third = *third;
    object->entries[object->count].key = key;
    object->span = key - object->entries[0].key;
    object->count++;
    return 1;
}

/**
 * @brief Evaluate the track with cached interpolation, wrapping and endpoint extrapolation.
 * @param key Sort value.
 * @return Evaluated value; updates the cached value and its scaled change.
 */
float BootClass171280::func_slot80(float key)
{
    s32 lower;
    s32 upper;
    float wrapped_key;
    u8 extrapolate;
    float result;

    if (!unk04 || !state.unk08)
    {
        return 0.0f;
    }

    if (state.unk0c >= state.unk0a)
    {
        state.unk0c = 0;
    }

    if (state.unk08 == 1 && (!(key < unk04[0].unk00) || state.unk12_0_3 != 6))
    {
        return unk04[0].unk04;
    }

    extrapolate = 0;

    if (key < unk04[0].unk00 && state.unk12_0_3 == 6)
    {
        upper = 0;
        wrapped_key = key;
        lower = -1;
    }
    else
    {
        wrapped_key = func_001F4D90(reinterpret_cast<BootState1F12B0*>(this), key);

        if (state.unk00)
        {
            if (state.unk12_0_3 == 0 && state.unk00 < 0)
            {
                return unk04[0].unk04;
            }

            if (state.unk12_4_7 == 0 && state.unk00 > 0)
            {
                return unk04[state.unk08 - 1].unk04;
            }
        }

        extrapolate = func_001F4E70(this, wrapped_key, &lower, &upper);

        if (extrapolate)
        {
            wrapped_key = key;
        }
    }

    if (!extrapolate)
    {
        if (state.unk0e != lower || state.unk10 != upper)
        {
            state.unk0e = lower;
            state.unk10 = upper;
            BootTrackKey171950* first = lower >= 0 ? unk04 + lower : &unk08;
            s32 last = state.unk08 - 1;

            if (upper == last && ((!(key < unk04[0].unk00) && state.unk12_4_7 == 2) || (key < unk04[0].unk00 && state.unk12_0_3 == 2)))
            {
                BootTrackKey171950* entries = unk04;
                unk2C.func_001EFE50(&first->unk04, &first->unk0c, &entries[0].unk04, &entries[0].unk08, first->unk00, entries[upper].unk00);
            }
            else if (lower < upper)
            {
                BootTrackKey171950* second = unk04 + upper;
                unk2C.func_001EFE50(&first->unk04, &first->unk0c, &second->unk04, &second->unk08, first->unk00, second->unk00);
            }
            else
            {
                BootTrackKey171950* second = unk04 + last;
                unk2C.func_001EFE50(&first->unk04, &first->unk0c, &second->unk04, &second->unk08, first->unk00, second->unk00);
            }
        }

        result = func_4B16C0(&unk2C, wrapped_key);

        if (state.unk00 && ((state.unk12_0_3 == 5 && state.unk00 < 0) || (state.unk12_4_7 == 5 && state.unk00 > 0)))
        {
            float delta = unk04[state.unk08 - 1].unk04 - unk04[0].unk04;
            result += delta * state.unk00;
        }
    }
    else if (wrapped_key < key)
    {
        s32 count = state.unk08;
        BootTrackKey171950* entries = unk04;
        BootTrackKey171950* last_entry = entries + (count - 1);
        BootTrackKey171950* previous_entry = entries + (count - 2);
        float last_key = last_entry->unk00;
        float previous_key = previous_entry->unk00;
        float slope = entries[count - 1].unk08 / (last_key - previous_key);
        result = entries[count - 1].unk04 + slope * (key - last_key);
    }
    else
    {
        BootTrackKey171950* entries = unk04;
        float first_key = entries[0].unk00;
        result = entries[0].unk04 + (entries[0].unk0c / (entries[1].unk00 - first_key)) * (key - first_key);
    }

    unk50 = D_001B668C * (result - unk4c);
    unk4c = result;
    return result;
}

/**
 * @brief Store a single keyframe in the cached vectors.
 * @param value Keyframe value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key, stored in the value's fourth component.
 */
void BootClass1710D0::func_001F4560(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    func_001F0D60(6);
    unk10 = *value;
    unk20 = *first;
    unk30 = *second;
    unk10.w = key;
}

/**
 * @brief Insert a keyframe at an index.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootClass1710D0::func_001F45F0(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
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
        static_cast<BootTrackKey1719E0*>(unk04)[i] = static_cast<BootTrackKey1719E0*>(unk04)[i - 1];
    }

    static_cast<BootTrackKey1719E0*>(unk04)[index].value = *value;
    static_cast<BootTrackKey1719E0*>(unk04)[index].first = *first;
    static_cast<BootTrackKey1719E0*>(unk04)[index].second = *second;
    static_cast<BootTrackKey1719E0*>(unk04)[index].value.w = key;

    if (index == state.unk08 - 1)
    {
        state.span = key - static_cast<BootTrackKey1719E0*>(unk04)[0].value.w;
    }

    state.unk08++;
    return 1;
}

void func_001F4730(BootState1F4730* state, u32 value)
{
    state->unk52_lo = value;
    state->unk53_bit0 = state->unk52_lo == 4 || state->unk52_hi == 4;
}

void func_001F4790(BootState1F4790* state, u32 value)
{
    state->unk22_lo = value;
    state->unk23_bit0 = state->unk22_lo == 4 || state->unk22_hi == 4;
}

void func_001F47F0(BootState1F47F0* state, u32 value)
{
    state->unk42_lo = value;
    state->unk43_bit0 = state->unk42_lo == 4 || state->unk42_hi == 4;
}

/**
 * @brief Store a value and key in the two-entry history and count it, up to two.
 * @param value Value to store.
 * @param key Key to store.
 */
void BootClass171B70::func_001F4850(const FieldVec4A* value, float key)
{
    unk20[unk12] = *value;
    unk40[unk12] = key;

    if (++unk12 >= 2)
    {
        unk12 = 0;
    }

    if (++unk10 > 2)
    {
        unk10 = 2;
    }
}

void func_001F48D0(BootFloatHistory1F48D0* history, const float* value, float associated)
{
    history->values[history->next_index] = *value;
    history->unk1C[history->next_index] = associated;

    if (++history->next_index >= 2)
    {
        history->next_index = 0;
    }

    if (++history->count > 2)
    {
        history->count = 2;
    }
}

void func_001F4950(void* object)
{
}

void func_001F4960(void* object)
{
}

void func_001F4970(void* object)
{
}

void func_001F4980(BootState1F47F0* object)
{
    object->entries = 0;
    object->unk42_lo = 1;
    object->unk42_hi = 1;
    object->capacity = 0;
    object->count = 0;
    object->unk3C = -1;
    object->unk30 = 0;
    object->unk3E = -1;
    object->unk40 = -1;
    object->unk43_bit0 = 0;
    object->unk43_bit1 = 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param count Requested keyframe count.
 */
void BootClass171A70::func_001F4A10(s32 count)
{
    state.unk13_1 = 0;
    delete[] static_cast<BootTrackKey171A70*>(unk04);
    unk04 = new (0) BootTrackKey171A70[count];
    state.unk0a = count;

    if (!unk04)
    {
        state.unk0a = 0;
    }
}

void func_001F4AC0(BootState1F47F0* state, u32 value)
{
    state->unk42_hi = value;
    state->unk43_bit0 = state->unk42_lo == 4 || state->unk42_hi == 4;
}

u32 func_001F4B20(void* object)
{
    return ((FieldU32At030*)object)->value;
}

s16 func_001F4B30(void* object)
{
    return ((FieldS16At038*)object)->value;
}

s16 func_001F4B40(void* object)
{
    return ((FieldS16At03A*)object)->value;
}

s32 func_001F4B50(void* object)
{
    return 0;
}

/** @brief Forward to slot 0x68. */
s32 func_001F4B60(BootClass171A70* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return object->func_001F4B50(value, first, second, key);
}

s32 func_001F4B90(void* object)
{
    return 0;
}

/** @brief Forward to slot 0x6C. */
s32 func_001F4BA0(BootClass171A70* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->func_001F4B90(index, key, value, first, second);
}

s32 func_001F4BD0(void* object)
{
    return 0;
}

/** @brief Forward to slot 0x70. */
s32 func_001F4BE0(BootClass171A70* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->func_001F4BD0(index, key, value, first, second);
}

void func_001F4C10(void* object)
{
}

/** @brief Forward to slot 0x74. */
void func_001F4C20(BootClass171A70* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    object->func_001F4C10(value, first, second, key);
}

void func_001F4C50(void* object)
{
    *(u32*)((u8*)object + 0x0) = 0;
    *(u32*)((u8*)object + 0x4) = 0;
    *(u32*)((u8*)object + 0x8) = 0;
    *(u32*)((u8*)object + 0xC) = 0;
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void BootClass171A70::func_001F4C70(float key, FieldVec4B* output) const
{
    *output = func_slot80(key);
}

u32 func_001F4CC0(void* object)
{
    return ((FieldU32At004*)object)->value;
}

/** @brief Forward to slot 0x68. */
s32 func_001F4CD0(BootClass1719E0* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return object->func_001F0E50(value, first, second, key);
}

/** @brief Forward to slot 0x6C. */
s32 func_001F4D00(BootClass1719E0* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->func_001F0E60(index, key, value, first, second);
}

/** @brief Forward to slot 0x70. */
s32 func_001F4D30(BootClass1719E0* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->func_001F0E70(index, key, value, first, second);
}

/** @brief Forward to slot 0x74. */
void func_001F4D60(BootClass1719E0* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    object->func_001F0E80(value, first, second, key);
}

float func_001F4D90(BootState1F12B0* object, float key)
{
    float first = object->entries[0].key;
    float quotient = (key - first) / object->span;

    if (key < first)
    {
        quotient -= 1.0f;
    }

    object->unk18 = quotient;

    if (object->unk18)
    {
        float result = key - (float)object->unk18 * object->span;

        if ((object->unk2A_lo == 3 && object->unk18 < 0) || (object->unk2A_hi == 3 && object->unk18 > 0))
        {
            s32 last_index = object->count - 1;
            BootKeyEntry16* last_entry = object->entries + last_index;
            float last = last_entry->key;

            if (object->unk18 & 1)
            {
                result = first + (last - result);
            }
        }

        return result;
    }

    return key;
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001ED4E0", func_001F4E70);

/** @brief Forward to slot 0x68. */
s32 func_001F4FD0(BootClass171950* object, const float* x, const float* y, const float* z, float key)
{
    return object->func_001F13A0(x, y, z, key);
}

/** @brief Forward to slot 0x6C. */
s32 func_001F5000(BootClass171950* object, s32 index, float key, const float* x, const float* y, const float* z)
{
    return object->func_001F13B0(index, key, x, y, z);
}

/** @brief Forward to slot 0x70. */
s32 func_001F5030(BootClass171950* object, s32 index, float key, const float* x, const float* y, const float* z)
{
    return object->func_001F13C0(index, key, x, y, z);
}

/** @brief Forward to slot 0x74. */
void func_001F5060(BootClass171950* object, const float* x, const float* y, const float* z, float key)
{
    object->func_001F13D0(x, y, z, key);
}

float func_001F5090(BootState1F1FC0* object, float key)
{
    float first = object->entries[0].key;
    float quotient = (key - first) / object->span;

    if (key < first)
    {
        quotient -= 1.0f;
    }

    object->unk10 = quotient;

    if (object->unk10)
    {
        float result = key - (float)object->unk10 * object->span;

        if ((object->unk22_lo == 3 && object->unk10 < 0) || (object->unk22_hi == 3 && object->unk10 > 0))
        {
            s32 last_index = object->count - 1;
            BootFloatEntry1F33B0* last_entry = object->entries + last_index;
            float last = last_entry->key;

            if (object->unk10 & 1)
            {
                result = first + (last - result);
            }
        }

        return result;
    }

    return key;
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001ED4E0", func_001F5170);

void func_001F52D0(BootState1F4790* object)
{
    object->entries = 0;
    object->unk22_lo = 1;
    object->unk22_hi = 1;
    object->capacity = 0;
    object->count = 0;
    object->unk1C = -1;
    object->unk10 = 0;
    object->unk1E = -1;
    object->unk20 = -1;
    object->unk23_bit0 = 0;
    object->unk23_bit1 = 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param count Requested keyframe count.
 */
void BootClass171710::func_001F5360(s32 count)
{
    state.unk13_1 = 0;
    delete[] static_cast<BootTrackKey171710*>(unk04);
    unk04 = new (0) BootTrackKey171710[count];
    state.unk0a = count;

    if (!unk04)
    {
        state.unk0a = 0;
    }
}

void func_001F5400(BootState1F4790* object, s32 count, BootShortKeyEntry8* entries)
{
    s32 last_index = count - 1;
    BootShortKeyEntry8* last;
    object->unk23_bit1 = 1;
    object->entries = entries;
    object->capacity = count;
    object->count = count;
    last = object->entries + last_index;
    object->span = (float)last->key - (float)object->entries[0].key;
}

void func_001F5460(BootState1F4790* state, u32 value)
{
    state->unk22_hi = value;
    state->unk23_bit0 = state->unk22_lo == 4 || state->unk22_hi == 4;
}

u32 func_001F54C0(void* object)
{
    return ((FieldU32At010*)object)->value;
}

s16 func_001F54D0(void* object)
{
    return ((FieldS16At018*)object)->value;
}

s16 func_001F54E0(void* object)
{
    return ((FieldS16At01A*)object)->value;
}

s32 func_001F54F0(void* object)
{
    return 0;
}

/** @brief Forward to slot 0x68. */
s32 func_001F5500(BootClass171710* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return object->func_001F54F0(value, first, second, key);
}

s32 func_001F5530(void* object)
{
    return 0;
}

/** @brief Forward to slot 0x6C. */
s32 func_001F5540(BootClass171710* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->func_001F5530(index, key, value, first, second);
}

s32 func_001F5570(void* object)
{
    return 0;
}

/** @brief Forward to slot 0x70. */
s32 func_001F5580(BootClass171710* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->func_001F5570(index, key, value, first, second);
}

void func_001F55B0(void* object)
{
}

/** @brief Forward to slot 0x74. */
void func_001F55C0(BootClass171710* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    object->func_001F55B0(value, first, second, key);
}

s32 func_001F55F0(BootState1F4790* object, float key)
{
    s32 index;

    for (index = 0; index < object->count; index++)
    {
        if (key == object->entries[index].key)
        {
            return 1;
        }
    }

    return 0;
}

void func_001F5650(void* object)
{
    *(u32*)((u8*)object + 0x0) = 0;
    *(u32*)((u8*)object + 0x4) = 0;
    *(u32*)((u8*)object + 0x8) = 0;
    *(u32*)((u8*)object + 0xC) = 0;
}

float func_001F5670(BootState1F4790* object)
{
    s32 last_index;
    BootShortKeyEntry8* last_entry;

    if (object->count < 2)
    {
        return 0.0f;
    }

    last_index = object->count - 1;
    last_entry = object->entries + last_index;
    return (float)last_entry->key - (float)object->entries[0].key;
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001ED4E0", func_001F56D0);

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void BootClass171710::func_001F57C0(float key, FieldVec4B* output) const
{
    *output = func_slot80(key);
}

float func_001F5810(BootState1F4790* object, float key)
{
    s32 last_index = object->count - 1;
    BootShortKeyEntry8* entries = object->entries;
    BootShortKeyEntry8* last = entries + last_index;
    float first = entries[0].key;
    float span = last->key - first;
    float position = (key - first) / span;
    s32 cycles;

    if (position < 0.0f)
    {
        position -= 1.0f;
    }

    cycles = (s32)position;

    if (cycles != 0)
    {
        return key - cycles * span;
    }

    return key;
}

u32 func_001F58B0(void* object)
{
    return ((FieldU32At004*)object)->value;
}

void func_001F58C0(BootState1F4730* object)
{
    object->entries = 0;
    object->unk52_lo = 1;
    object->unk52_hi = 1;
    object->capacity = 0;
    object->count = 0;
    object->unk4C = -1;
    object->unk40 = 0;
    object->unk4E = -1;
    object->unk50 = -1;
    object->unk53_bit0 = 0;
    object->unk53_bit1 = 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param count Requested keyframe count.
 */
void BootClass171680::func_001F5950(s32 count)
{
    state.unk13_1 = 0;
    delete[] static_cast<BootTrackKey171680*>(unk04);
    unk04 = new (0) BootTrackKey171680[count];
    state.unk0a = count;

    if (!unk04)
    {
        state.unk0a = 0;
    }
}

void func_001F5A00(BootState1F4730* object, s32 count, BootKeyEntry48* entries)
{
    s32 last_index = count - 1;
    BootKeyEntry48* last;
    object->unk53_bit1 = 1;
    object->entries = entries;
    object->capacity = count;
    object->count = count;
    last = object->entries + last_index;
    object->span = last->key - object->entries[0].key;
}

void func_001F5A50(BootState1F4730* state, u32 value)
{
    state->unk52_hi = value;
    state->unk53_bit0 = state->unk52_lo == 4 || state->unk52_hi == 4;
}

u32 func_001F5AB0(void* object)
{
    return ((FieldU32At040*)object)->value;
}

s16 func_001F5AC0(void* object)
{
    return ((FieldS16At048*)object)->value;
}

s16 func_001F5AD0(void* object)
{
    return ((FieldS16At04A*)object)->value;
}

s32 func_001F5AE0(void* object)
{
    return 0;
}

/** @brief Forward to slot 0x68. */
s32 func_001F5AF0(BootClass171680* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return object->func_001F5AE0(value, first, second, key);
}

s32 func_001F5B20(void* object)
{
    return 0;
}

/** @brief Forward to slot 0x6C. */
s32 func_001F5B30(BootClass171680* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->func_001F5B20(index, key, value, first, second);
}

s32 func_001F5B60(void* object)
{
    return 0;
}

/** @brief Forward to slot 0x70. */
s32 func_001F5B70(BootClass171680* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->func_001F5B60(index, key, value, first, second);
}

void func_001F5BA0(void* object)
{
}

/** @brief Forward to slot 0x74. */
void func_001F5BB0(BootClass171680* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    object->func_001F5BA0(value, first, second, key);
}

s32 func_001F5BE0(BootState1F4730* object, float key)
{
    s32 index;

    for (index = 0; index < object->count; index++)
    {
        if (key == object->entries[index].key)
        {
            return 1;
        }
    }

    return 0;
}

void func_001F5C30(void* object)
{
    *(u32*)((u8*)object + 0x0) = 0;
    *(u32*)((u8*)object + 0x4) = 0;
    *(u32*)((u8*)object + 0x8) = 0;
    *(u32*)((u8*)object + 0xC) = 0;
}

float func_001F5C50(BootState1F4730* object)
{
    s32 last_index;
    BootKeyEntry48* last_entry;

    if (object->count < 2)
    {
        return 0.0f;
    }

    last_index = object->count - 1;
    last_entry = object->entries + last_index;
    return last_entry->key - object->entries[0].key;
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001ED4E0", func_001F5CA0);

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void BootClass171680::func_001F5D10(float key, FieldVec4B* output) const
{
    *output = func_slot80(key);
}

float func_001F5D60(BootState1F4730* object, float key)
{
    s32 last_index = object->count - 1;
    BootKeyEntry48* entries = object->entries;
    BootKeyEntry48* last = entries + last_index;
    float first = entries[0].key;
    float span = last->key - first;
    float quotient = (key - first) / span;
    s32 periods;

    if (quotient < 0.0f)
    {
        quotient -= 1.0f;
    }

    periods = quotient;

    if (periods != 0)
    {
        return key - (float)periods * span;
    }

    return key;
}

u32 func_001F5E00(void* object)
{
    return ((FieldU32At004*)object)->value;
}

BootTrackKey171680::BootTrackKey171680()
{
}

float func_001F5E20(BootState1F47F0* object, float key)
{
    s32 last_index = object->count - 1;
    BootKeyEntry32* entries = object->entries;
    BootKeyEntry32* last = entries + last_index;
    float first = entries[0].key;
    float span = last->key - first;
    float quotient = (key - first) / span;
    s32 periods;

    if (quotient < 0.0f)
    {
        quotient -= 1.0f;
    }

    periods = quotient;

    if (periods != 0)
    {
        return key - (float)periods * span;
    }

    return key;
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001ED4E0", func_001F5EB0);

float func_001F5F10(BootState1F47F0* object)
{
    s32 last_index;
    BootKeyEntry32* last_entry;

    if (object->count < 2)
    {
        return 0.0f;
    }

    last_index = object->count - 1;
    last_entry = object->entries + last_index;
    return last_entry->key - object->entries[0].key;
}

s32 func_001F5F60(BootState1F47F0* object, float key)
{
    s32 index;

    for (index = 0; index < object->count; index++)
    {
        if (key == object->entries[index].key)
        {
            return 1;
        }
    }

    return 0;
}

void func_001F5FB0(BootState1F47F0* object, s32 count, BootKeyEntry32* entries)
{
    s32 last_index = count - 1;
    BootKeyEntry32* last;
    object->unk43_bit1 = 1;
    object->entries = entries;
    object->capacity = count;
    object->count = count;
    last = object->entries + last_index;
    object->span = last->key - object->entries[0].key;
}

BootTrackKey171A70::BootTrackKey171A70()
{
}

/**
 * @brief Find the scene node of a title menu item.
 * @param menu Title menu.
 * @param item Item number, from 0 to 3.
 * @return The item's node, or null if the scene has none.
 */
static inline BootClass170F30* find_menu_item(BootTitleMenu* menu, s32 item)
{
    BootClass170F30* node;

    switch (item)
    {
    case 0:
        node = func_473940(menu->scene, g_new_game_node_name);
        break;
    case 1:
        node = func_473940(menu->scene, g_continue_node_name);
        break;
    case 2:
        node = func_473940(menu->scene, g_battle_collection_node_name);
        break;
    case 3:
        node = func_473940(menu->scene, g_install_node_name);
        break;
    }

    return node;
}

/**
 * @brief Grow and pulse the selected item and ease the others back to normal.
 * @param snap Nonzero to put the selected item straight at full size.
 */
void BootTitleMenu::animate_items(u8 snap)
{
    if (scene == 0)
    {
        return;
    }

    for (s32 item = 0; item < 4; item++)
    {
        BootClass170F30* node = find_menu_item(this, item);

        if (node == 0)
        {
            continue;
        }

        if (item == selected)
        {
            BootVector4DDAA0 value;
            copy_vector(&value, &node->unk40);

            if (value.x < 1.08f && !snap)
            {
                value.x += 0.02f * D_001B6688;
                value.y += 0.02f * D_001B6688;
                value.z += 0.02f * D_001B6688;
            }
            else
            {
                value.x = 1.1f;
                value.y = 1.1f;
                value.z = 1.1f;
            }

            node->func_001E0750(&value);
            copy_vector(&value, &node->unk560);

            if (value.w > 0.9f)
            {
                if (!pulse_up)
                {
                    value.x -= 0.01f * D_001B6688;
                    value.y -= 0.005f * D_001B6688;

                    if (value.y < 0.5f)
                    {
                        value.y = 0.5f;
                    }

                    if (value.x < 0.5f)
                    {
                        value.x = 0.5f;
                        pulse_up = 1;
                    }
                }
                else if (pulse_up)
                {
                    value.x += 0.01f * D_001B6688;
                    value.y += 0.005f * D_001B6688;

                    if (value.y > 1.0f)
                    {
                        value.y = 1.0f;
                    }

                    if (value.x > 1.0f)
                    {
                        value.x = 1.0f;
                        pulse_up = 0;
                    }
                }

                copy_vector(&node->unk560, &value);
                node->func_001DDAA0();
            }
        }
        else
        {
            BootVector4DDAA0 value;
            copy_vector(&value, &node->unk40);

            if (value.x > 1.05f)
            {
                value.x -= 0.05f * D_001B6688;
                value.y -= 0.05f * D_001B6688;
                value.z -= 0.05f * D_001B6688;
            }
            else
            {
                value.x = 1.0f;
                value.y = 1.0f;
                value.z = 1.0f;
            }

            node->func_001E0750(&value);
            copy_vector(&value, &node->unk560);

            if (value.x < 1.0f)
            {
                value.x += 0.025f * D_001B6688;
                value.y += 0.05f * D_001B6688;

                if (value.x > 1.0f)
                {
                    value.x = 1.0f;
                }

                if (value.y > 1.0f)
                {
                    value.y = 1.0f;
                }
            }

            copy_vector(&node->unk560, &value);
            node->func_001DDAA0();
        }
    }
}

/**
 * @brief Work out the screen position of the cursor beside the selected item.
 * @param x Receives the horizontal position, or zero if the item has no node.
 * @param y Receives the vertical position, or zero if the item has no node.
 */
void BootTitleMenu::get_cursor_position(float* x, float* y)
{
    BootResource0970* settings = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);
    BootClass170F30* node = find_menu_item(this, selected);

    if (node == 0)
    {
        *x = 0.0f;
        *y = 0.0f;
        return;
    }

    if (!node->unk61)
    {
        node->update_transform_matrix();
    }

    float screen_x = node->unkD0.vectors[0].w;
    float screen_y = node->unkD0.vectors[1].w;

    if (settings->widescreen)
    {
        *x = 319.0f + 0.75f * screen_x;
        *y = 224.0f + screen_y;
    }
    else
    {
        *x = 320.0f + screen_x;
        *y = 224.0f + screen_y;
    }

    if (selected == 1)
    {
        *x -= 6.0f;
    }

    if (selected < 4)
    {
        *y += 24.0f;
    }
}

/** @brief Dim Continue and Battle Collection unless a memory card holds the data they need. */
void BootTitleMenu::update_item_availability()
{
    if (scene == 0)
    {
        return;
    }

    BootClass170F30* continue_node;
    BootInput* input = g_boot_program.input;
    u32 slot1 = input->slot1_state;
    u32 slot2 = input->slot2_state;
    u32 first = input->unk28;
    u32 second = input->unk2C;
    continue_node = func_473940(scene, g_continue_node_name);

    if (continue_node == 0)
    {
        return;
    }

    BootClass170F30* collection_node = func_473940(scene, g_battle_collection_node_name);

    if (collection_node == 0)
    {
        return;
    }

    BootVector4DDAA0 color;
    copy_vector(&color, &collection_node->unk560);

    if (first == 5 || second == 5)
    {
        color.w = 1.0f;
        collection_ready = 1;
        copy_vector(&collection_node->unk560, &color);
        collection_node->func_001DDAA0();
    }
    else
    {
        color.x = 1.0f;
        color.y = 1.0f;
        color.z = 1.0f;
        color.w = 0.5f;
        collection_ready = 0;
        copy_vector(&collection_node->unk560, &color);
        collection_node->func_001DDAA0();
    }

    copy_vector(&color, &continue_node->unk560);

    if (slot1 == 0x11 || slot2 == 0x11)
    {
        color.w = 1.0f;
        continue_ready = 1;
        copy_vector(&continue_node->unk560, &color);
        continue_node->func_001DDAA0();
    }
    else
    {
        color.x = 1.0f;
        color.y = 1.0f;
        color.z = 1.0f;
        color.w = 0.5f;
        continue_ready = 0;
        copy_vector(&continue_node->unk560, &color);
        continue_node->func_001DDAA0();
    }
}

/** @brief Run the menu state machine. */
void BootTitleMenu::update()
{
    BootResource0970* settings;
    BootInput* input = g_boot_program.input;
    settings = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);

    switch (step)
    {
    case 0:
    {
        if (func_102D00(D_001B65E8) == 0)
        {
            break;
        }

        if ((((u32)g_boot_program.message_block + 0x7F) & ~0x7F) == 0)
        {
            break;
        }

        check_main_code();
        scene = new (0) BootClass175320;
        func_4791F0(scene, scene_data);
        func_474010(scene, g_boot_program.display, D_001B6614, D_001B6624, D_001B6628, D_001B661C, 1);
        delete[] scene_data;
        scene_data = 0;
        func_40B3A0(unk30);
        delete[] unk30;
        unk30 = 0;
        camera = func_473680(scene, g_title_camera_node_name);
        D_001B6628->current_display = camera;

        if (initial_item != -1)
        {
            selected = initial_item;
        }
        else if (input->slot1_state == 0x11 || input->slot2_state == 0x11)
        {
            selected = 1;
        }
        else
        {
            selected = 0;
        }

        animate_items(1);
        D_001B661C->prepend_node(new (0) BootClass179150, -1);
        float x;
        float y;
        get_cursor_position(&x, &y);
        cursor = new (0) BootClass175070;
        func_467570(cursor, 1, 0, 0, x, y, 0.0f);
        func_465B20(D_001B657C, cursor);
        step++;
        break;
    }
    case 1:
        if (func_112990(D_001B65F8, 2, 1, 0, 0) == 0)
        {
            break;
        }

        check_main_code();
        step++;
        idle_time = 0.0f;
        break;
    case 2:
    {
        check_main_code();

        if (input->repeated == 0x80 && cursor->unk35)
        {
            selected--;

            if (selected > 2)
            {
                selected = 2;
            }

            float x;
            float y;
            get_cursor_position(&x, &y);
            cursor->func_00466E40(x, y, 0.05f);
            pulse_up = 0;
            func_112400(D_001B65F8, 0, 0, 0, 0x7F, 0x40, 0);
        }

        if (input->repeated == 0x20 && cursor->unk35)
        {
            selected++;

            if (selected > 2)
            {
                selected = 0;
            }

            float x;
            float y;
            get_cursor_position(&x, &y);
            cursor->func_00466E40(x, y, 0.05f);
            func_112400(D_001B65F8, 0, 0, 0, 0x7F, 0x40, 0);
        }

        idle_time += D_001B6690;

        if (input->pressed & settings->unk00)
        {
            u8 accepted = 0;

            if (selected == 0)
            {
                step++;
                accepted = 1;
            }

            if (selected == 1 && continue_ready)
            {
                settings->unk25_mid = 1;
                accepted = 1;
                step = 5;
            }

            if (selected == 2 && collection_ready)
            {
                accepted = 1;
                step = 7;
            }

            if (selected == 3 && unk2c)
            {
                accepted = 1;
                step = 6;
            }

            if (accepted)
            {
                queue_fade();
                func_10F000(D_001B65F8, 0x1E, -1);
                func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
            }
            else
            {
                func_112400(D_001B65F8, 3, 0, 0, 0x7F, 0x40, 0);
            }
        }
        else if (!(idle_time < 45.0f) && func_112610(D_001B65F8, -1) == 0 && func_115270(D_001B65E4, 1) == 1)
        {
            queue_fade();
            func_10F000(D_001B65F8, 0x1E, -1);
            step = 4;
        }

        break;
    }
    case 3:
        check_main_code();
        g_boot_program.select_projection();
        step++;
        func_473AA0(scene);
        scene->destroy();
        scene = 0;
        cursor->destroy();
        cursor = 0;
        D_001B6614->append_node(new (0) BootNewGameSettings, -1);
        lib_object_detach_owner(this);
        destroy();
        break;
    case 4:
        check_main_code();
        g_boot_program.select_projection();
        step++;
        func_473AA0(scene);
        scene->destroy();
        scene = 0;
        cursor->destroy();
        cursor = 0;
        func_10F000(D_001B65F8, 0, -1);
        D_001B6614->append_node(new (0) BootOpeningMovie, -1);
        lib_object_detach_owner(this);
        destroy();
        break;
    case 5:
        check_main_code();
        g_boot_program.select_projection();
        step++;
        func_473AA0(scene);
        scene->destroy();
        scene = 0;
        cursor->destroy();
        cursor = 0;
        D_001B6614->append_node(new (0) BootGameLauncher, -1);
        lib_object_detach_owner(this);
        destroy();
        break;
    case 6:
        check_main_code();
        g_boot_program.select_projection();
        step++;
        func_473AA0(scene);
        scene->destroy();
        scene = 0;
        cursor->destroy();
        cursor = 0;
        D_001B6614->append_node(new (0) BootInstaller, -1);
        lib_object_detach_owner(this);
        destroy();
        break;
    case 7:
    {
        check_main_code();
        g_boot_program.select_projection();
        step++;
        func_473AA0(scene);
        scene->destroy();
        scene = 0;
        cursor->destroy();
        cursor = 0;
        void* block = func_100B00(func_10CE00(), 0);
        D_001B6614->append_node(new (0) BootBattleTrophyViewer, -1);
        func_100B40(block);
        lib_object_detach_owner(this);
        destroy();
        break;
    }
    }

    update_item_availability();
    animate_items(0);

    if (step > 0)
    {
        check_main_code();
    }
}

/** @brief Free the resource buffers, then destroy the scene and its model. */
BootTitleMenu::~BootTitleMenu()
{
    delete[] scene_data;
    delete[] unk30;

    if (scene != 0)
    {
        scene->destroy();
    }

    if (cursor != 0)
    {
        cursor->destroy();
    }
}

/**
 * @brief Queue the scene resources and remember the item to start on.
 * @param initial_item Item to select first, or -1 to pick Continue when a card holds a save.
 */
BootTitleMenu::BootTitleMenu(s32 initial_item)
{
    step = 0;
    scene_data = func_139700(0x40, func_11C8C0(D_001B65E4, 0x27));
    func_103E70(D_001B65E8, 0x27, scene_data, 1, 0x34BC0, 0, 0, 0, 1);
    unk30 = func_139700(0x40, func_11C8C0(D_001B65E4, 0xA));
    func_103E70(D_001B65E8, 0xA, unk30, 1, 0x34BC0, 0, 0, 0, 1);
    scene = 0;
    cursor = 0;
    pulse_up = 0;
    continue_ready = 0;
    unk2c = 0;
    collection_ready = 0;
    this->initial_item = initial_item;
    g_boot_program.trophy_card->func_001E0DE0(2);
}

/** @brief Detach the bar and its model, destroy the model and delete the bar. */
void BootProgressBar::destroy()
{
    lib_object_detach_owner(this);

    if (unk18 != 0)
    {
        lib_object_detach_owner(this);
        unk18->destroy();
    }

    unk18 = 0;
    delete this;
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001ED4E0", func_001F79A0);

void func_001F86C0(BootSettings1F86C0* settings)
{
    settings->unk00 = 12;
    settings->unk03 = 0;
    settings->unk02 = 0;
    settings->unk04 = 0;
    settings->unk05 = 0;
    settings->unk06 = 1;
    settings->unk07 = 1;
    settings->unk08 = 1.0f;
    settings->unk0C = 1.0f;
    settings->unk10 = 0.5f;
    settings->unk18 = 0;
    settings->unk19 = 0;
    settings->unk1A = 0;
    settings->unk1B = 0;
    settings->unk1C = 0;
    settings->unk14 = 0.0f;
}

/**
 * @brief Recreate the bar's draw buffer and model, then draw it empty and show it.
 * @param bar Progress bar.
 * @param width Bar width.
 * @param height Bar height.
 * @param color Bar color.
 * @param mode Draw mode.
 */
void func_001F8720(BootProgressBar* bar, s32 width, s32 height, u32 color, s32 mode)
{
    if (bar->draw_buffer != 0)
    {
        delete bar->draw_buffer;
    }

    if (bar->unk18 != 0)
    {
        bar->unk18->destroy();
    }

    bar->draw_buffer = new (0) LibDrawBuffer;
    bar->unk18 = new (0) BootClass177820;
    bar->draw_buffer->allocate_storage(2, 0x600, 1, 8);
    bar->width = width;
    bar->height = height;
    bar->color = color;
    bar->mode = mode;
    func_001F79A0(bar, 0, 1);
    func_4D6430(bar->unk18, bar->draw_buffer);
    bar->unk18->unk80 = D_001B6630;
    bar->unk18->unk6a |= 0x400;
    D_001B661C->append_node(bar->unk18, -1);
}

/** @brief Destroy the bar's model, then the bar. */
BootProgressBar::~BootProgressBar()
{
    if (unk18 != 0)
    {
        unk18->destroy();
    }
}

/** @brief Clear the bar's model and state. */
BootProgressBar::BootProgressBar()
{
    draw_buffer = 0;
    unk18 = 0;
}

/** @brief Fade out; once transparent, destroy the strips and the fade. */
void BootClass171C00::update()
{
    unkcc -= unkd0 * D_001B6690;

    if (unkcc <= 0.0f)
    {
        for (s32 i = 0; i < 10; i++)
        {
            if (images[i] != 0)
            {
                lib_object_detach_owner(images[i]);
                images[i]->destroy();
                images[i] = 0;
            }
        }

        lib_object_detach_owner(this);
        destroy();
    }
}

/** @brief Mark the fade inactive and run the Lib release helper. @param value Unused. */
void BootClass171C00::func_001E04F0(u32 value)
{
    unk64 = 0;
    func_4D00B0(this);
}

/** @brief Mark the fade active and submit its packet. */
void BootClass171C00::func_001DD4C0()
{
    unk64 = 1;
    func_11F510(packet, static_cast<BootClass170D50*>(this));
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001ED4E0", func_001E08C0__15BootClass171C00FPCvPv);

/** @brief Destroy the strips, the copy buffer and the packet. */
BootClass171C00::~BootClass171C00()
{
    for (s32 i = 0; i < 10; i++)
    {
        if (images[i] != 0)
        {
            lib_object_detach_owner(images[i]);
            images[i]->destroy();
        }
    }

    delete[] buffer;
    delete packet;
}

/** @brief Release the packet storage unless it is external. */
BootClass171BF0::~BootClass171BF0()
{
    if (!unk14)
    {
        delete unk04;
    }
}

#include "overlays/boot/transform_inlines.h"

/** @brief Copy the display into ten strips and show them, fully opaque. @param display Display to copy. */
BootClass171C00::BootClass171C00(BootDimensionsACD0* display)
{
    s32 width;
    s32 height;
    s32 i;
    this->display = display;
    width = display->unk3C60.width / 2 + display->unk3C60.width / 2;
    height = display->unk3C60.height / 2 + display->unk3C60.height / 2;
    buffer = new (0) u8[width * height * 3 / 16 * 16];

    for (i = 0; i < 10; i++)
    {
        images[i] = new (0) BootClass1735A0;
        images[i]->unk65 = 1;
        func_4333A0(images[i], buffer + height * (i * 64) * 3 / 16 * 16, (display->unk160 & 0x1FF) << 5, width / 64, 1, i * 64, 0, 0x40, height);
        D_001B661C->append_node(images[i], -1);
    }

    func_001DFE40(0x4000);
    unk65 = 1;
    func_001DFE30(0x400);
    packet = new (0) BootClass171BF0(0x400);
    unkcc = 1.0f;
    unkd0 = 1.0f;
    unkc8 = 0;
}

/** @brief Detach the image and its model, destroy the model and delete the image. */
void BootImage::destroy()
{
    lib_object_detach_owner(this);

    if (unk18 != 0)
    {
        lib_object_detach_owner(this);
        unk18->destroy();
    }

    unk18 = 0;
    delete this;
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001ED4E0", func_001F93B0);

/**
 * @brief Append one vertex to a draw buffer's streams.
 * @param buffer Draw buffer.
 * @param position Vertex position.
 * @param unk Value for the second vector stream.
 * @param texcoord Packed texture coordinates.
 * @param color Vertex color.
 */
static inline void add_vertex(LibDrawBuffer* buffer, const FieldVec4A& position, const FieldVec4A& unk, u32 texcoord, u32 color)
{
    *buffer->positions = position;
    buffer->positions++;
    *buffer->unk4c = unk;
    buffer->unk4c++;
    *buffer->texcoords++ = texcoord;
    *buffer->colors++ = color;
    buffer->vertex_count++;
}

/**
 * @brief Build the image's quad from a rectangle of its texture and queue the model for drawing.
 * @param x Left edge of the rectangle in the texture, in texels.
 * @param y Top edge of the rectangle in the texture.
 * @param width Rectangle width, which is also the quad's width.
 * @param height Rectangle height, which is also the quad's height.
 * @param color Vertex color.
 * @param depth Z position of the quad.
 */
void BootImage::set_rectangle(s32 x, s32 y, s32 width, s32 height, u32 color, s32 depth)
{
    BootSettings1F86C0 settings;

    func_455DF0(draw_buffer, 0, 1);
    func_001F86C0(&settings);
    settings.unk06 = 0;
    settings.unk02 = 2;
    settings.unk00 = 0x5C;
    settings.unk05 = 1;
    func_455150(draw_buffer, &settings);
    func_4550F0(draw_buffer, 4);
    FieldVec4A normal(0.0f, 0.0f, -1.0f, 1.0f);

    if (centered)
    {
        float half_width = 0.5f * (float)width;
        float half_height = 0.5f * (float)height;
        add_vertex(draw_buffer, FieldVec4A(-half_width, -half_height, (float)depth, 1.0f), normal,
                   ((x << 12) / texture_width) | (((y << 12) / texture_height) << 16), color);
        add_vertex(draw_buffer, FieldVec4A(half_width, -half_height, (float)depth, 1.0f), normal,
                   (((y << 12) / texture_height) << 16) | (((x + width) << 12) / texture_width), color);
        add_vertex(draw_buffer, FieldVec4A(-half_width, half_height, (float)depth, 1.0f), normal,
                   ((x << 12) / texture_width) | ((((y + height) << 12) / texture_height) << 16), color);
        add_vertex(draw_buffer, FieldVec4A(half_width, half_height, (float)depth, 1.0f), normal,
                   (((x + width) << 12) / texture_width) | ((((y + height) << 12) / texture_height) << 16), color);
    }
    else
    {
        add_vertex(draw_buffer, FieldVec4A(0.0f, 0.0f, (float)depth, 1.0f), normal, ((x << 12) / texture_width) | (((y << 12) / texture_height) << 16), color);
        add_vertex(draw_buffer, FieldVec4A((float)width, 0.0f, (float)depth, 1.0f), normal,
                   (((y << 12) / texture_height) << 16) | (((x + width) << 12) / texture_width), color);
        add_vertex(draw_buffer, FieldVec4A(0.0f, (float)height, (float)depth, 1.0f), normal,
                   ((x << 12) / texture_width) | ((((y + height) << 12) / texture_height) << 16), color);
        add_vertex(draw_buffer, FieldVec4A((float)width, (float)height, (float)depth, 1.0f), normal,
                   (((x + width) << 12) / texture_width) | ((((y + height) << 12) / texture_height) << 16), color);
    }

    func_455BD0(draw_buffer, unk2c, 500.0f, 0);
    func_4D6430(unk18, draw_buffer);
    unk18->unk80 = D_001B6630;
    unk18->unk6a |= 0x400;
    D_001B661C->append_node(unk18, -1);
}

/**
 * @brief Recreate the image's draw buffer and model and upload a texture and optional palette.
 * @param texture Texture resource.
 * @param palette Palette resource, or null.
 */
void BootImage::set_texture(const BootTextureResource* texture, const BootTextureResource* palette)
{
    if (draw_buffer != 0)
    {
        delete draw_buffer;
    }

    if (unk18 != 0)
    {
        unk18->destroy();
    }

    draw_buffer = new (0) LibDrawBuffer;
    unk18 = new (0) BootClass177820;
    draw_buffer->allocate_storage(1, 0x600, 2, 8);
    func_455040(draw_buffer, texture);

    if (palette != 0)
    {
        func_455040(draw_buffer, palette);
    }

    const BootTextureImage* info = texture_image(texture);
    texture_width = 1 << info->width_log2;
    texture_height = 1 << info->height_log2;

    if (palette != 0)
    {
        info = texture_image(palette);
        palette_width = 1 << info->width_log2;
        palette_height = 1 << info->height_log2;
        has_palette = 1;
    }
}

/** @brief Destroy the image's model, then the image. */
BootImage::~BootImage()
{
    if (unk18 != 0)
    {
        unk18->destroy();
    }
}

/** @brief Clear the image's model and state. */
BootImage::BootImage()
{
    draw_buffer = 0;
    unk18 = 0;
    centered = 0;
    has_palette = 0;
    unk2c = 0;
}

/** @brief Set the byte at offset 0x60 to 10. */
void BootClass171C00::func_001E0860()
{
    unk60 = 10;
}

/** @brief Run the launch steps: seed, movie, load, hand over. */
void BootGameLauncher::update()
{
    BootResource0970* settings;
    BootInput* input = g_boot_program.input;
    settings = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);
    u32 previous;

    switch (step)
    {
    case 0:
        previous = resident_next_random_word();

        while (previous == resident_next_random_word())
        {
        }

        previous = func_10CE00();

        while (previous == func_10CE00())
        {
        }

        previous = func_10CAA0(1000);

        while (previous == func_10CAA0(1000))
        {
        }

        previous = func_10CC40(0, 1000);

        while (previous == func_10CC40(0, 1000))
        {
        }

        if ((u8)settings->unk25_mid == 0)
        {
            BootSealedRecord* record = &settings->unkD4;
            func_13A678(record, 0, sizeof(BootSealedRecord));
            seal_record(record);
            BootResourceBits0970* bits = &settings->unk1A8;
            s32 size = bits->size;

            for (s32 i = 0; i < size; i++)
            {
                bits->unk08[i] = 0;
            }

            bits->unk14 = resident_next_random_word();
            func_457520(bits);
        }

        if ((u8)settings->unk25_mid == 0 && settings->sound_output == 2)
        {
            step++;
            timer = 0;
        }
        else
        {
            step = 5;
            timer = 0;
        }

        break;
    case 1:
        if (++timer > 60)
        {
            if (func_115430(D_001B65E4) == 0 && func_115670(D_001B65E4) != 0 && func_115650(D_001B65E4) != 0)
            {
                break;
            }

            movie_heap = new (0) BootResident113E40;
            movie_heap->unk2C = 0x40;
            func_113930(movie_heap, 0x579F2C);
            void* heap = resident_exchange_allocation_heap(movie_heap);
            player = new (0) BootClass172500(640, 448);
            resident_exchange_allocation_heap(heap);
            player->state->set_scale(1.0f, 1.0f);
            player->state->set_words(0x800, 0x800, 1);

            if (((BootResource0970*)func_101440(func_101290(func_10D8E0()), 1))->widescreen)
            {
                player->state->unk80D8 = 1;
            }

            func_419A70(player, 13, 1);
            step++;
        }
        else if (input->held & 8)
        {
            step = 5;
        }

        break;
    case 2:
        timer++;

        if ((input->held & 8) || !player->unk15E794)
        {
            step++;
        }

        break;
    case 3:
        func_41A210(player);
        player->destroy();
        player = 0;
        step++;
        break;
    case 4:
        delete movie_heap;
        movie_heap = 0;
        step++;
        break;
    case 5:
        program = func_139700(0x40, func_11C8C0(D_001B65E4, 0x42B));
        func_103E70(D_001B65E8, 0x42B, program, 1, 0x34BC0, 0, 0, 0, 1);
        step++;
        break;
    case 6:
        if (func_102D00(D_001B65E8) != 0 && ++timer > 40)
        {
            lib_object_detach_owner(this);
            destroy();
            g_boot_program.next_program = program;
            return;
        }

        break;
    }
}

/**
 * @brief Encode a saved record and seal it with a fresh checksum; a damaged record is wiped instead.
 * @param record Record to seal; an already sealed record is left alone.
 */
void seal_record(BootSealedRecord* record)
{
    s32 i;

    if (record->sealed == 0)
    {
        record->sealed = BOOT_RECORD_SEALED;
        record->unk00 ^= 0xD7;
        record->unk02 ^= 0xF393;
        record->unk04 ^= 0x7CE3C7F7;
        record->unk08 ^= 0x7CE3C7F7;
        record->unk0C ^= 0x7CE3C7F7;
        record->unk10 ^= 0x7CE3C7F7;
        record->unk14 ^= 0x7CE3C7F7;
        record->unk18 ^= 0x7CE3C7F7;
        record->unk1C ^= 0x7CE3C7F7;
        record->unk20 ^= 0x7CE3C7F7;
        record->unk24 ^= 0x7CE3C7F7;
        record->unk28 ^= 0x7CE3C7F7;
        record->unk2C ^= 0x7CE3C7F7;
        record->unk30 ^= 0x7CE3C7F7;
        record->unk34 ^= 0x7CE3C7F7;
        record->unk38 ^= 0x7CE3C7F7;
        record->unk3C ^= 0x7CE3C7F7;
        record->unk40 ^= 0x7CE3C7F7;
        record->unk44 ^= 0x7CE3C7F7;
        record->unk48 ^= 0x7CE3C7F7;
        record->unk4C ^= 0x7CE3C7F7;
        record->unk50 ^= 0x7CE3C7F7;
        record->unk54 ^= 0x7CE3C7F7;
        record->unk58 ^= 0x7CE3C7F7;

        for (i = 0; i < 76; i++)
        {
            record->unk64[i] ^= 0xD7;
        }

        record->key = resident_next_random_word();
        record->checksum = func_457470(record->key * 37, record, (u8*)&record->checksum - (u8*)record);
    }
    else if (record->sealed != BOOT_RECORD_SEALED)
    {
        func_13A678(record, 0, sizeof(BootSealedRecord));
    }
}

/** @brief Release the player, its heap and the work buffer. */
BootGameLauncher::~BootGameLauncher()
{
    if (player != 0)
    {
        player->destroy();
    }

    delete movie_heap;
    delete buffer;
}

/** @brief Clear the state and allocate the 0x12000-byte work buffer. */
BootGameLauncher::BootGameLauncher()
{
    program = 0;
    step = 0;
    buffer = func_139700(0x40, 0x12000);
    movie_heap = 0;
    player = 0;
}

/** @brief Report the list kind used when registration requests the default. @return Four. */
s32 BootBattleTrophyViewer::get_default_list_kind()
{
    return 4;
}

/**
 * @brief Return the time a trophy was earned, as one comparable number.
 * @param viewer Viewer holding the records and display order.
 * @param position List position of the trophy.
 * @return Year, month, day, hour, minute and second packed from the highest byte down, or zero if not earned.
 */
static inline u64 trophy_time(BootBattleTrophyViewer* viewer, s32 position)
{
    BootResource0970* settings = boot_settings();
    s32 index = viewer->order[position];

    if (resource_bit(&settings->unk1A8, index))
    {
        BootTrophyTime* time = &viewer->records[index].time;
        return time->second + (time->minute << 8) + (time->hour << 16) + (time->day << 24) + ((u64)time->month << 32) + ((u64)time->year << 40);
    }

    return 0;
}

/**
 * @brief Reset the display order to trophy number order, then optionally sort it newest first.
 * @param newest_first Nonzero to sort by the time each trophy was earned; unearned ones go last.
 */
void BootBattleTrophyViewer::sort_trophies(u8 newest_first)
{
    for (s32 i = 0; i < 300; i++)
    {
        order[i] = i;
    }

    if (!newest_first)
    {
        return;
    }

    BootResourceBits0970* bits = &boot_settings()->unk1A8;
    u32 seed = bits->checksum_seed;
    u32 checksum;
    func_457670(bits, &seed, &checksum);

    if (bits->checksum != checksum)
    {
        return;
    }

    for (s32 i = 1; i < 300; i++)
    {
        u64 time = trophy_time(this, i);
        s16 current = order[i];
        s32 j;

        for (j = i - 1; j >= 0 && trophy_time(this, j) < time; j--)
        {
            order[j + 1] = order[j];
        }

        order[j + 1] = current;
    }
}

/**
 * @brief Build a trophy's texture from the picture template, the trophy's packed picture and the first palette.
 * @param record Trophy record holding the picture.
 * @param texture Texture resource to fill.
 * @param index Trophy index.
 */
void BootBattleTrophyViewer::build_trophy_texture(const BootTrophyRecordF10* record, BootTextureResource* texture, s32 index)
{
    func_13A4C0(texture, (void*)(((u32)unk1C[2] + 0x7F) & ~0x7F), 0x4600);
    BootTextureHeader* header = &texture->header;
    u32* palette = (u32*)((u8*)header + header->palette_offset + 0x80);
    u8* pixels = (u8*)header + ((BootTextureImage*)((u8*)header + header->image_offset))->pixel_offset + 0x80;
    func_13CD50(header->name, g_trophy_texture_name, 4);
    header->id = index + 1;

    for (s32 i = 0; i < 32; i++)
    {
        palette[i] = palettes[0][i];
    }

    const u8* source = record->image;
    u16 bits = *source++;
    s32 bit_count = 8;

    for (s32 y = 0; y < 96; y++)
    {
        for (s32 x = 0; x < 64; x++)
        {
            *pixels++ = bits & 0x1F;
            bits >>= 5;
            bit_count -= 5;

            if (bit_count < 9)
            {
                bits |= *source++ << bit_count;
                bit_count += 8;
            }
        }

        pixels += 64;
    }
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001ED4E0", update_grid__22BootBattleTrophyViewerFv);

/**
 * @brief Check a flag block against its stored checksum.
 * @param bits Flag block.
 * @return True when the checksum matches.
 */
static inline bool flags_intact(BootResourceBits0970* bits)
{
    u32 seed = bits->checksum_seed;
    u32 checksum;
    func_457670(bits, &seed, &checksum);
    return bits->checksum == checksum;
}

/**
 * @brief Set a clip region's rectangle and clear its display.
 * @param clip Clip region.
 * @param left Left edge.
 * @param top Top edge.
 * @param right Right edge.
 * @param bottom Bottom edge.
 */
static inline void set_clip(BootClass171DD0* clip, s32 left, s32 top, s32 right, s32 bottom)
{
    clip->left = left;
    clip->top = top;
    clip->right = right;
    clip->bottom = bottom;
    clip->display = 0;
}

/**
 * @brief Check the trophy data and create a picture for each trophy: its own picture when earned, a blank frame
 * otherwise.
 * @return One when done, or zero when a trophy record fails its check, after clearing that trophy.
 */
s32 BootBattleTrophyViewer::create_trophy_images()
{
    BootResource0970* settings = boot_settings();
    BootResourceBits0970* bits = &settings->unk1A8;

    if (!flags_intact(bits))
    {
        return 0;
    }

    earned_count = 0;

    if (flags_intact(bits))
    {
        for (s32 i = 0; i < 300; i++)
        {
            BootTrophyRecordF10* record = &records[i];

            if (func_457220(record) == 0 || *((BootResidentRoot15CC0*)func_10D8E0())->status == 0x67)
            {
                set_resource_bit(bits, i, 0);
                record->unk0C = 0;
                func_457520(bits);
                return 0;
            }
        }
    }

    for (s32 i = 0; i < 300; i++)
    {
        order[i] = i;
        textures[i] = (BootTextureResource*)func_139700(0x80, 0x4600);
    }

    unkB8 = new (0) BootClass171DD0;
    D_001B661C->append_node(unkB8, -1);

    if (settings->widescreen)
    {
        set_clip(unkB8, 0, 0x4D, 0x27F, 0x180);
    }
    else
    {
        set_clip(unkB8, 0, 0x50, 0x27F, 0x17C);
    }

    if (flags_intact(bits))
    {
        for (s32 i = 0; i < 300; i++)
        {
            trophy_images[i] = new (0) BootImage;
            trophy_images[i]->centered = 1;
            unkC94[i] = 0.0f;

            if (resource_bit(bits, i))
            {
                build_trophy_texture(&records[i], textures[i], i);
                trophy_images[i]->set_texture((const BootTextureResource*)(((u32)unk1C[0] + 0x7F) & ~0x7F), textures[i]);
                func_001F93B0(trophy_images[i], 0, 0xE2, 0x44, 0x64, 0, 0, 0x40, 0x60, 0x80808080, 0);
                earned_count++;
            }
            else
            {
                trophy_images[i]->set_texture((const BootTextureResource*)(((u32)unk1C[0] + 0x7F) & ~0x7F), 0);
                trophy_images[i]->set_rectangle(0, 0xE2, 0x44, 0x64, 0x80808080, 0);
            }

            trophy_images[i]->unk18->func_001E0520(-236.0f + (i & 7) * 68, -94.0f + i / 8 * 100, 0.0f);
        }
    }
    else
    {
        for (s32 i = 0; i < 300; i++)
        {
            trophy_images[i] = new (0) BootImage;
            trophy_images[i]->centered = 1;
            trophy_images[i]->set_texture((const BootTextureResource*)(((u32)unk1C[0] + 0x7F) & ~0x7F), 0);
            trophy_images[i]->set_rectangle(0, 0xE2, 0x44, 0x64, 0x80808080, 0);
            trophy_images[i]->unk18->func_001E0520(-236.0f + (i & 7) * 68, -94.0f + i / 8 * 100, 0.0f);
        }
    }

    func_121FE0(0);
    unkBC = new (0) BootClass171DD0;
    D_001B661C->append_node(unkBC, -1);
    unkBC->display = g_boot_program.display;
    return 1;
}

/**
 * @brief Give the bar's model an even color modulation and recompute its combined color.
 * @param bar Loading bar.
 * @param red Red factor.
 * @param green Green factor.
 * @param blue Blue factor.
 * @param alpha Alpha factor.
 */
static inline void set_bar_color(BootProgressBar* const& bar, float red, float green, float blue, float alpha)
{
    BootVector4DDAA0 color;
    color.x = red;
    color.y = green;
    color.z = blue;
    color.w = alpha;
    BootClass177820* model = bar->unk18;
    copy_vector(&model->unk560, &color);
    model->func_001DDAA0();
}

/** @brief Create the two screen images once the pictures load, place them for the screen shape and fade out the bar. */
void BootBattleTrophyViewer::update_images()
{
    if (unk1C[2] == 0)
    {
        return;
    }

    if (unk28[0] == 0)
    {
        unk28[0] = new (0) BootImage;
        unk28[0]->set_texture((const BootTextureResource*)(((u32)unk1C[0] + 0x7F) & ~0x7F), 0);
        unk28[0]->set_rectangle(0, 1, 488, 223, 0x80808080, 0);
        unk28[0]->unk18->func_001E0520(-244.0f, -112.0f, 0.0f);
    }

    if (unk28[1] == 0)
    {
        unk28[1] = new (0) BootImage;
        unk28[1]->set_texture((const BootTextureResource*)(((u32)unk1C[1] + 0x7F) & ~0x7F), 0);
        unk28[1]->set_rectangle(0, 0, 640, 80, 0x80808080, 0);
        unk28[1]->unk18->func_001E0520(-320.0f, -216.0f, 0.0f);
    }

    if (boot_settings()->widescreen)
    {
        if (unk28[1] != 0)
        {
            unk28[1]->unk18->func_001E0520(-422.66668f, -216.0f, 0.0f);
            unk28[1]->unk18->func_001DDED0(1.31f, 1.0f, 1.0f);
        }
    }
    else if (unk28[1] != 0)
    {
        unk28[1]->unk18->func_001E0520(-320.0f, -216.0f, 0.0f);
        unk28[1]->unk18->func_001DDED0(1.0f, 1.0f, 1.0f);
    }

    if (bar_fading && unkC0 != 0)
    {
        unkC0->unk18->func_001E94E0(2);
        set_bar_color(unkC0, 1.0f, 1.0f, 1.0f, bar_alpha);
        bar_alpha -= 2.0f * D_001B6690;

        if (bar_alpha < 0.0f)
        {
            bar_fading = 0;
            lib_object_detach_owner(unkC0);
            unkC0->destroy();
            unkC0 = 0;
        }
    }
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001ED4E0", update__22BootBattleTrophyViewerFv);
}
