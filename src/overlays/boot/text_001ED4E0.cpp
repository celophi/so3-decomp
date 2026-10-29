#include "include_asm.h"
#include "clamp.h"
#include "vu0.h"
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
extern void* D_001B663C;
u32 func_4D93A0(void* heap, BootVramRequest* request, u32 tag, s32 count, s32 unk4, s32 unk5, s32 unk6, s32 unk7);
u8* func_11F860(ResidentPacket* packet, s32 quadwords);
u8* func_11F830(ResidentPacket* packet, u8* cursor);

extern void func_4D00B0(void* object);
FieldVec4B func_4B1640(const BootVectorSegmentBase* range, float key);
extern BootTrackPool<BootPooledVectorCurveTrack>* g_vector_curve_track_pool;
void vector_curve_track_pool_free(BootTrackPool<BootPooledVectorCurveTrack>* pool, BootPooledVectorCurveTrack* track);
float func_4B16C0(void* object, float key);
extern BootTrackPool<BootPooledVectorTrack>* g_vector_track_pool;
void vector_track_pool_free(BootTrackPool<BootPooledVectorTrack>* pool, BootPooledVectorTrack* track);
extern float D_001B668C;
void progress_bar_draw(BootProgressBar* bar, s32 done, s32 total);
void func_4D6430(BootModel* model, LibDrawBuffer* buffer);
extern void* D_001B6630;
void func_4333A0(BootImageStrip* image, u8* data, s16 address, s16 width, s32 first, s16 x, s32 second, s32 strip_width, s16 height);

extern const char g_new_game_node_name[];
extern const char g_continue_node_name[];
extern const char g_battle_collection_node_name[];
extern const char g_install_node_name[];
extern const char g_title_camera_node_name[];
void func_455DF0(LibDrawBuffer* buffer, s32 first, s32 second);
void func_455040(LibDrawBuffer* buffer, const BootTextureResource* resource);
void func_455150(LibDrawBuffer* buffer, BootDrawSettings* settings);
void func_4550F0(LibDrawBuffer* buffer, s32 count);
void func_455BD0(LibDrawBuffer* buffer, u8 mode, float distance, s32 flag);
void func_4791F0(BootScene* scene, u8* data);
void func_40B3A0(u8* data);
void func_473AA0(BootScene* scene);
s32 func_112610(BootSound1B65F8* sound, s32 key);
void func_100B40(void* allocation);

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

BootPooledFloatCurveTrack::~BootPooledFloatCurveTrack()
{
}

BootPooledFloatCurveTrack::BootPooledFloatCurveTrack()
{
}

/**
 * @brief Release every track in the pool and its storage.
 * @param pool Pool to clear.
 */
void float_curve_track_pool_release(BootTrackPool<BootPooledFloatCurveTrack>* pool)
{
    pool->release();
}

/**
 * @brief Allocate the pool's tracks, mark them pooled and clear the used bitmap.
 * @param pool Pool to fill.
 * @param count Number of tracks.
 * @return One on success, or zero when the tracks could not be allocated.
 */
s32 vector_curve_track_pool_allocate(BootTrackPool<BootPooledVectorCurveTrack>* pool, s32 count)
{
    return pool->init(count);
}

BootPooledVectorCurveTrack::~BootPooledVectorCurveTrack()
{
}

BootPooledVectorCurveTrack::BootPooledVectorCurveTrack()
{
}

/**
 * @brief Release every track in the pool and its storage.
 * @param pool Pool to clear.
 */
void vector_curve_track_pool_release(BootTrackPool<BootPooledVectorCurveTrack>* pool)
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
s32 quaternion_track_pool_allocate(BootTrackPool<BootPooledQuaternionTrack>* pool, s32 count)
{
    return pool->init(count);
}

BootPooledQuaternionTrack::~BootPooledQuaternionTrack()
{
}

BootPooledQuaternionTrack::BootPooledQuaternionTrack()
{
}

/**
 * @brief Release every track in the pool and its storage.
 * @param pool Pool to clear.
 */
void quaternion_track_pool_release(BootTrackPool<BootPooledQuaternionTrack>* pool)
{
    pool->release();
}

/**
 * @brief Evaluate a vector range at a key.
 * @param range Range to evaluate.
 * @param key Evaluation key.
 * @return Evaluated vector.
 */
FieldVec4B vector_segment_evaluate(const BootVectorSegmentBase* range, float key)
{
    return func_4B1640(range, key);
}

void func_001EECA0(void* object)
{
}

/** @brief Delete the track; pooled tracks override this to return to their pool. */
void BootFloatCurveTrackBase::release()
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
void BootPooledVectorCurveTrack::release()
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

void func_001EEDF0(BootPooledVectorCurveTrack* track)
{
    vector_curve_track_free_keys(track);
    vector_curve_track_pool_free(g_vector_curve_track_pool, track);
}

float func_001EEE20(void* object, float key)
{
    return func_4B16C0(object, key);
}

/** @brief Return a pooled track to its pool, or delete an ordinary track. */
void BootPooledVectorTrack::release()
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

void func_001EEEA0(BootPooledVectorTrack* track)
{
    vector_track_free_keys(track);
    vector_track_pool_free(g_vector_track_pool, track);
}

struct ResetVectorB0_001ED4E0
{
    u8 pad[0xB0];
    FieldVec4B value;
};

void func_001EEED0(void* object)
{
    ((ResetVectorB0_001ED4E0*)object)->value = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    vector_curve_track_reset_state((BootVectorCurveTrackState*)object);
}

/**
 * @brief Subtract the first three components of one vector from another.
 * @param left Vector to subtract from.
 * @param right Vector to subtract.
 * @return left minus right, keeping left's fourth component.
 */
static inline FieldVec4B difference(const FieldVec4B& left, const FieldVec4B& right)
{
    FieldVec4B value(left);
    value.x -= right.x;
    value.y -= right.y;
    value.z -= right.z;
    return value;
}

/**
 * @brief Scale all four components of a vector.
 * @param scale Factor to multiply by.
 * @param vector Vector to scale.
 * @return The scaled vector.
 */
static inline FieldVec4B scaled(float scale, const FieldVec4B& vector)
{
    FieldVec4B value(vector);
    return value *= scale;
}

/**
 * @brief Add the first three components of two vectors.
 * @param left First vector.
 * @param right Vector to add.
 * @return left plus right, keeping left's fourth component.
 */
static inline FieldVec4B sum(const FieldVec4B& left, const FieldVec4B& right)
{
    FieldVec4B value(left);
    value.x += right.x;
    value.y += right.y;
    value.z += right.z;
    return value;
}

/**
 * @brief Return a vector track's last keyframe.
 * @param track Track with at least one keyframe.
 * @return The last keyframe.
 */
static inline BootTrackKey1719E0& last_entry(BootVectorCurveTrackBase* track)
{
    return static_cast<BootTrackKey1719E0*>(track->unk04)[track->state.key_count - 1];
}

/**
 * @brief Return a keyframe's key.
 * @param entry Keyframe.
 * @return The key, stored in the value's fourth component.
 */
static inline float key_of(const BootTrackKey1719E0* entry)
{
    return entry->value.w;
}

/**
 * @brief Evaluate the track at a key, extrapolating past either end, and cache the value and its change per frame.
 * @param key Evaluation key.
 * @return Evaluated vector.
 */
FieldVec4A BootVectorCurveTrack::sample(float key)
{
    s32 lower;
    s32 upper;
    float wrapped_key;
    u8 extrapolate;
    FieldVec4B result;

    if (!unk04 || !state.key_count)
    {
        return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    }

    if (state.unk0c >= state.key_capacity)
    {
        state.unk0c = 0;
    }

    if (state.key_count == 1 && (!(key < static_cast<BootTrackKey1719E0*>(unk04)[0].value.w) || state.before_mode != 6))
    {
        return *reinterpret_cast<FieldVec4A*>(&static_cast<BootTrackKey1719E0*>(unk04)[0].value);
    }

    extrapolate = 0;

    if (key < static_cast<BootTrackKey1719E0*>(unk04)[0].value.w && state.before_mode == 6)
    {
        upper = 0;
        wrapped_key = key;
        lower = -1;
    }
    else
    {
        wrapped_key = vector_curve_track_update_cycle_count(reinterpret_cast<BootVectorCurveTrackState*>(this), key);

        if (state.cycle_count)
        {
            if (state.before_mode == 0 && state.cycle_count < 0)
            {
                return *reinterpret_cast<FieldVec4A*>(&static_cast<BootTrackKey1719E0*>(unk04)[0].value);
            }

            if (state.after_mode == 0 && state.cycle_count > 0)
            {
                return *reinterpret_cast<FieldVec4A*>(&static_cast<BootTrackKey1719E0*>(unk04)[state.key_count - 1].value);
            }
        }

        extrapolate = vector_curve_track_find_surrounding_keys(this, wrapped_key, &lower, &upper);

        if (extrapolate)
        {
            wrapped_key = key;
        }
    }

    if (!extrapolate)
    {
        if (state.unk0e != lower || state.cached_index != upper)
        {
            state.unk0e = lower;
            state.cached_index = upper;
            BootTrackKey1719E0* first = lower >= 0 ? static_cast<BootTrackKey1719E0*>(unk04) + lower : reinterpret_cast<BootTrackKey1719E0*>(&unk10);
            s32 last = state.key_count - 1;

            if (upper == last && ((!(key < static_cast<BootTrackKey1719E0*>(unk04)[0].value.w) && state.after_mode == 2) ||
                                  (key < static_cast<BootTrackKey1719E0*>(unk04)[0].value.w && state.before_mode == 2)))
            {
                BootTrackKey1719E0* entries = static_cast<BootTrackKey1719E0*>(unk04);
                BootTrackKey1719E0* second = entries + upper;
                unk60.set_endpoints(first->value.w, second->value.w, reinterpret_cast<const FieldVec4A*>(&first->value),
                                    reinterpret_cast<const FieldVec4A*>(&first->second), reinterpret_cast<const FieldVec4A*>(&entries[0].value),
                                    reinterpret_cast<const FieldVec4A*>(&entries[0].first));
            }
            else if (lower < upper)
            {
                BootTrackKey1719E0* second = static_cast<BootTrackKey1719E0*>(unk04) + upper;
                unk60.set_endpoints(first->value.w, second->value.w, reinterpret_cast<const FieldVec4A*>(&first->value),
                                    reinterpret_cast<const FieldVec4A*>(&first->second), reinterpret_cast<const FieldVec4A*>(&second->value),
                                    reinterpret_cast<const FieldVec4A*>(&second->first));
            }
            else
            {
                BootTrackKey1719E0* second = static_cast<BootTrackKey1719E0*>(unk04) + last;
                unk60.set_endpoints(first->value.w, second->value.w, reinterpret_cast<const FieldVec4A*>(&first->value),
                                    reinterpret_cast<const FieldVec4A*>(&first->second), reinterpret_cast<const FieldVec4A*>(&second->value),
                                    reinterpret_cast<const FieldVec4A*>(&second->first));
            }
        }

        result = func_4B1640(&unk60, wrapped_key);

        if (state.cycle_count && ((state.before_mode == 5 && state.cycle_count < 0) || (state.after_mode == 5 && state.cycle_count > 0)))
        {
            FieldVec4B delta = difference(static_cast<BootTrackKey1719E0*>(unk04)[state.key_count - 1].value, static_cast<BootTrackKey1719E0*>(unk04)[0].value);
            result += scaled((float)state.cycle_count, delta);
        }
    }
    else
    {
        FieldVec4B slope;

        if (wrapped_key < key)
        {
            slope = scaled(1.0f / (last_entry(this).value.w - key_of(static_cast<BootTrackKey1719E0*>(unk04) + (state.key_count - 2))),
                           static_cast<BootTrackKey1719E0*>(unk04)[state.key_count - 1].first);
            result = sum(static_cast<BootTrackKey1719E0*>(unk04)[state.key_count - 1].value, scaled(key - last_entry(this).value.w, slope));
        }
        else
        {
            slope = scaled(1.0f / (key_of(static_cast<BootTrackKey1719E0*>(unk04) + 1) - key_of(static_cast<BootTrackKey1719E0*>(unk04))),
                           static_cast<BootTrackKey1719E0*>(unk04)[0].second);
            result = sum(static_cast<BootTrackKey1719E0*>(unk04)[0].value, scaled(key - static_cast<BootTrackKey1719E0*>(unk04)[0].value.w, slope));
        }
    }

    unkC0 = scaled(D_001B668C, difference(result, unkB0));
    unkB0 = result;
    return *reinterpret_cast<FieldVec4A*>(&result);
}

/**
 * @brief Append a keyframe.
 * @param value Keyframe value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Sort key.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootVectorCurveTrack::append_curve_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    if (unk04 == 0)
    {
        return 0;
    }

    if (state.key_count >= state.key_capacity)
    {
        return 0;
    }

    static_cast<BootTrackKey1719E0*>(unk04)[state.key_count].value = *value;
    static_cast<BootTrackKey1719E0*>(unk04)[state.key_count].first = *first;
    static_cast<BootTrackKey1719E0*>(unk04)[state.key_count].second = *second;
    static_cast<BootTrackKey1719E0*>(unk04)[state.key_count].value.w = key;
    state.span = key - static_cast<BootTrackKey1719E0*>(unk04)[0].value.w;
    state.key_count++;
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
s32 BootVectorCurveTrack::append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    FieldVec4A zero_first;
    FieldVec4A zero_second;
    second = track_vector(second, &zero_second);
    first = track_vector(first, &zero_first);
    return append_curve_key(value, first, second, key);
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
s32 BootVectorCurveTrack::replace_curve_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    if (unk04 == 0)
    {
        return 0;
    }

    if (index >= state.key_capacity)
    {
        return 0;
    }

    static_cast<BootTrackKey1719E0*>(unk04)[index].value = *value;
    static_cast<BootTrackKey1719E0*>(unk04)[index].first = *first;
    static_cast<BootTrackKey1719E0*>(unk04)[index].second = *second;
    static_cast<BootTrackKey1719E0*>(unk04)[index].value.w = key;

    if (index == state.key_count - 1)
    {
        state.span = key - static_cast<BootTrackKey1719E0*>(unk04)[0].value.w;
    }

    return 1;
}

/** @brief Replace an indexed keyframe, using zero vectors for missing auxiliary vectors. */
s32 BootVectorCurveTrack::replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    FieldVec4A zero_first;
    FieldVec4A zero_second;
    second = track_vector(second, &zero_second);
    first = track_vector(first, &zero_first);
    return replace_curve_key(index, key, value, first, second);
}

/** @brief Insert a keyframe, using zero vectors for missing auxiliary vectors. */
s32 BootVectorCurveTrack::insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    FieldVec4A zero_first;
    FieldVec4A zero_second;
    second = track_vector(second, &zero_second);
    first = track_vector(first, &zero_first);
    return insert_curve_key(index, key, value, first, second);
}

/** @brief Store a single keyframe, using zero vectors for missing auxiliary vectors. */
void BootVectorCurveTrack::set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    FieldVec4A zero_first;
    FieldVec4A zero_second;
    second = track_vector(second, &zero_second);
    first = track_vector(first, &zero_first);
    set_single_curve_key(value, first, second, key);
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
s32 BootVectorCurveTrack::read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const
{
    if (unk04 == 0)
    {
        return 0;
    }

    if (index >= state.key_capacity)
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
void BootVectorCurveTrack::reset_keys()
{
    FieldVec4A zero(0.0f, 0.0f, 0.0f, 0.0f);
    set_single_key(&zero, &zero, &zero, 0.0f);
}

extern "C" void func_001EFAF0(const void* object, FieldVec4B* output)
{
    *output = *(const FieldVec4A*)((const u8*)object + 0xC0);
}

/**
 * @brief Return the difference between the endpoint vectors.
 * @param output Receives the difference.
 */
void BootVectorCurveTrack::get_end_delta(FieldVec4B* output) const
{
    if (unk04 != 0)
    {
        *output =
            sequence_difference(static_cast<const BootTrackKey1719E0*>(unk04)[state.key_count - 1].value, static_cast<const BootTrackKey1719E0*>(unk04)[0].value);
    }
}

void func_001EFB90(BootFloatCurveTrackState* object)
{
    ((FieldU32At04C*)object)->value = 0;
    float_curve_track_reset_state(object);
}

/** @brief Append an entry, using zero for missing components. */
s32 BootFloatCurveTrack::append_key(const float* x, const float* y, const float* z, float key)
{
    float y_value;
    float z_value;
    z_value = (z == 0) ? 0.0f : *z;
    z = &z_value;
    y_value = (y == 0) ? 0.0f : *y;
    y = &y_value;
    return append_curve_key(x, y, z, key);
}

/** @brief Replace an indexed entry, using zero for missing components. */
s32 BootFloatCurveTrack::replace_key(s32 index, float key, const float* x, const float* y, const float* z)
{
    float y_value;
    float z_value;
    z_value = (z == 0) ? 0.0f : *z;
    z = &z_value;
    y_value = (y == 0) ? 0.0f : *y;
    y = &y_value;
    return replace_curve_key(index, key, x, y, z);
}

/** @brief Insert an entry, using zero for missing components. */
s32 BootFloatCurveTrack::insert_key(s32 index, float key, const float* x, const float* y, const float* z)
{
    float y_value;
    float z_value;
    z_value = (z == 0) ? 0.0f : *z;
    z = &z_value;
    y_value = (y == 0) ? 0.0f : *y;
    y = &y_value;
    return insert_curve_key(index, key, x, y, z);
}

/** @brief Store a single entry, using zero for missing components. */
void BootFloatCurveTrack::set_single_key(const float* x, const float* y, const float* z, float key)
{
    float y_value;
    float z_value;
    z_value = (z == 0) ? 0.0f : *z;
    z = &z_value;
    y_value = (y == 0) ? 0.0f : *y;
    y = &y_value;
    set_single_curve_key(x, y, z, key);
}

/** @brief Reset to a single zero keyframe at key zero. */
void BootFloatCurveTrack::reset_keys()
{
    float zero = 0.0f;
    set_single_key(&zero, &zero, &zero, 0.0f);
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

BootVectorSegmentBase::BootVectorSegmentBase()
{
}

/**
 * @brief Set the range from two endpoint vectors and their tangents.
 * @param start Start key.
 * @param end End key.
 * @param first First endpoint vector.
 * @param second First endpoint tangent.
 * @param third Second endpoint vector.
 * @param fourth Second endpoint tangent.
 */
void BootVectorSegmentBase::set_endpoints(float start, float end, const FieldVec4A* first, const FieldVec4A* second, const FieldVec4A* third,
                                    const FieldVec4A* fourth)
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

BootFloatSegmentBase::BootFloatSegmentBase()
{
}

void float_segment_set_endpoints(BootFloatSegmentState* object, const float* first, const float* second, const float* third, const float* fourth, float start, float end)
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
    vector_track_reset_state((BootVectorTrackState*)object);
}

/**
 * @brief Evaluate the track at a key and cache the value and its change per frame.
 * @param key Evaluation key.
 * @return Evaluated vector.
 */
FieldVec4A BootVectorTrack::sample(float key)
{
    s32 lower;
    s32 upper;
    float wrapped_key;
    u8 extrapolate;

    if (!unk04 || !state.key_count)
    {
        return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    }

    if (state.unk0c >= state.key_capacity)
    {
        state.unk0c = 0;
    }

    if (state.key_count == 1 && (!(key < unk04[0].value.w) || state.before_mode != 6))
    {
        return *reinterpret_cast<FieldVec4A*>(&unk04[0].value);
    }

    if (key < unk04[0].value.w && state.before_mode == 6)
    {
        upper = 0;
        wrapped_key = key;
        lower = -1;
    }
    else
    {
        wrapped_key = vector_track_update_cycle_count(reinterpret_cast<BootVectorTrackState*>(this), key);

        if (state.before_mode == 0 && state.cycle_count < 0)
        {
            return *reinterpret_cast<FieldVec4A*>(&unk04[0].value);
        }

        if (state.after_mode == 0 && state.cycle_count > 0)
        {
            return *reinterpret_cast<FieldVec4A*>(&unk04[state.key_count - 1].value);
        }

        extrapolate = vector_track_find_surrounding_keys(this, wrapped_key, &lower, &upper);

        if (extrapolate)
        {
            wrapped_key = key;
        }
    }

    if (state.unk0e != lower || state.cached_index != upper)
    {
        state.unk0e = lower;
        state.cached_index = upper;
        BootVectorTrackKey* first = lower >= 0 ? unk04 + lower : reinterpret_cast<BootVectorTrackKey*>(&unk10);
        func_001F06C0(&unk40);
        unk40.push_sample(first->value.w, reinterpret_cast<const FieldVec4A*>(&first->value));
        s32 last = state.key_count - 1;
        // TODO: My guess; copying upper into its own local is the only way I found that matches.
        s32 upper_index = upper;

        if (upper_index == last && ((!(key < unk04[0].value.w) && state.after_mode == 2) || (key < unk04[0].value.w && state.before_mode == 2)))
        {
            BootVectorTrackKey* entries = unk04;
            BootVectorTrackKey* second = entries + upper_index;
            unk40.push_sample(second->value.w, reinterpret_cast<const FieldVec4A*>(&entries[0].value));
        }
        else if (lower < upper_index)
        {
            BootVectorTrackKey* second = unk04 + upper_index;
            unk40.push_sample(second->value.w, reinterpret_cast<const FieldVec4A*>(&second->value));
        }
        else
        {
            BootVectorTrackKey* second = unk04 + last;
            unk40.push_sample(second->value.w, reinterpret_cast<const FieldVec4A*>(&unk04[upper_index].value));
        }
    }

    FieldVec4B result = unk40.sample(wrapped_key);

    if ((state.before_mode == 5 && state.cycle_count < 0) || (state.after_mode == 5 && state.cycle_count > 0))
    {
        FieldVec4B delta = difference(unk04[state.key_count - 1].value, unk04[0].value);
        result += scaled((float)state.cycle_count, delta);
    }

    unkA0 = scaled(1.0f / D_001B6688, difference(result, unk90));
    unk90 = result;
    return *reinterpret_cast<FieldVec4A*>(&result);
}

/**
 * @brief Return the difference between the endpoint values.
 * @param output Receives the difference.
 */
void BootVectorTrack::get_end_delta(FieldVec4B* output) const
{
    if (unk04 != 0)
    {
        *output =
            sequence_difference(static_cast<const BootVectorTrackKey*>(unk04)[state.key_count - 1].value, static_cast<const BootVectorTrackKey*>(unk04)[0].value);
    }
}

extern "C" void func_001F0440(const void* object, FieldVec4B* output)
{
    *output = *(const FieldVec4A*)((const u8*)object + 0xA0);
}

void func_001F0460(BootFloatTrackState* object)
{
    ((FieldU32At048*)object)->value = 0;
    float_track_reset_state(object);
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

BootVectorHistory::BootVectorHistory()
{
    unk00 = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Store a value and key in the two-entry history and count it, up to two.
 * @param key Key to store.
 * @param value Value to store.
 */
void BootVectorHistory::push_sample(float key, const FieldVec4A* value)
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

BootFloatHistory::BootFloatHistory()
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

BootVectorHistoryBase::BootVectorHistoryBase()
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

BootFloatHistoryBase::BootFloatHistoryBase()
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
s32 BootVectorKeyTrack::on_append_key(const FieldVec4A* value, float key)
{
    if (unk04 == 0)
    {
        return 0;
    }

    if (state.key_count >= state.key_capacity)
    {
        return 0;
    }

    static_cast<BootVectorTrackKey*>(unk04)[state.key_count].value = *value;
    static_cast<BootVectorTrackKey*>(unk04)[state.key_count].value.w = key;
    state.span = key - static_cast<BootVectorTrackKey*>(unk04)[0].value.w;
    state.unk0e = -1;
    state.cached_index = -1;
    state.key_count++;
    return 1;
}

/**
 * @brief Replace an indexed keyframe.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootVectorKeyTrack::on_replace_key(s32 index, float key, const FieldVec4A* value)
{
    if (unk04 == 0)
    {
        return 0;
    }

    if (index >= state.key_capacity)
    {
        return 0;
    }

    static_cast<BootVectorTrackKey*>(unk04)[index].value = *value;
    static_cast<BootVectorTrackKey*>(unk04)[index].value.w = key;

    if (index == state.key_count - 1)
    {
        state.span = key - static_cast<BootVectorTrackKey*>(unk04)[0].value.w;
    }

    state.unk0e = -1;
    state.cached_index = -1;
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
s32 BootVectorKeyTrack::read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const
{
    if (unk04 == 0)
    {
        return 0;
    }

    if (index >= state.key_capacity)
    {
        return 0;
    }

    if (key)
    {
        *key = static_cast<const BootVectorTrackKey*>(unk04)[index].value.w;
    }

    if (value)
    {
        *value = static_cast<const BootVectorTrackKey*>(unk04)[index].value;
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
    if (!track->state.external_keys)
    {
        if (track->unk04)
        {
            func_100BE0((u8*)track->unk04 - 16);
        }
    }

    track->unk04 = 0;
}

float vector_curve_track_update_cycle_count(BootVectorCurveTrackState* object, float key)
{
    float first = object->entries[0].key;
    float quotient = (key - first) / object->span;

    if (key < first)
    {
        quotient -= 1.0f;
    }

    object->cycle_count = quotient;

    if (object->cycle_count)
    {
        float result = key - (float)object->cycle_count * object->span;

        if ((object->before_mode == 3 && object->cycle_count < 0) || (object->after_mode == 3 && object->cycle_count > 0))
        {
            s32 last_index = object->count - 1;
            BootVectorCurveStateKey* last_entry = object->entries + last_index;
            float last = last_entry->key;

            if (object->cycle_count & 1)
            {
                result = first + (last - result);
            }
        }

        return result;
    }

    return key;
}

/**
 * @brief Find the entries around a key, starting from the cached cursor.
 * @param track Track to search.
 * @param key Key to place.
 * @param lower Receives the lower entry index.
 * @param upper Receives the upper entry index.
 * @return One when a reflecting end mode extends the first or last segment, otherwise zero.
 */
u8 vector_curve_track_find_surrounding_keys(BootVectorCurveTrackBase* track, float key, s32* lower, s32* upper)
{
    s32 index;
    s32 count;
    s32 next;

    if (track->state.repeats)
    {
        if (track->state.before_mode == 4 && track->state.cycle_count < 0)
        {
            *lower = 0;
            *upper = 1;
            track->state.unk0c = 0;
            return 1;
        }

        if (track->state.after_mode == 4 && track->state.cycle_count > 0)
        {
            *lower = track->state.key_count - 2;
            *upper = track->state.key_count - 1;
            track->state.unk0c = track->state.key_count - 2;
            return 1;
        }
    }

    index = track->state.unk0c;
    count = track->state.key_count;

    while (index > 0 && key < static_cast<BootTrackKey1719E0*>(track->unk04)[index].value.w)
    {
        index--;
    }

    index = clamp_low(index, 0);

    while ((next = index + 1) < count && !(key < static_cast<BootTrackKey1719E0*>(track->unk04)[next].value.w))
    {
        index++;
    }

    if (index >= count - 1)
    {
        *lower = count - 2;
        *upper = count - 1;
    }
    else
    {
        *lower = index;
        *upper = index + 1;
    }

    track->state.unk0c = index;
    return 0;
}
/** @brief Release the keyframe storage. */
BootVectorCurveTrackBase::~BootVectorCurveTrackBase()
{
    vector_curve_track_free_keys(this);
}

void vector_curve_track_reset_state(BootVectorCurveTrackState* object)
{
    object->entries = 0;
    object->before_mode = 1;
    object->after_mode = 1;
    object->capacity = 0;
    object->count = 0;
    object->unk4C = -1;
    object->cycle_count = 0;
    object->unk4E = -1;
    object->cached_index = -1;
    object->repeats = 0;
    object->external_keys = 0;
}

void vector_curve_track_bind_keys(BootVectorCurveTrackState* object, s32 count, BootVectorCurveStateKey* entries)
{
    s32 last_index = count - 1;
    BootVectorCurveStateKey* last;
    object->external_keys = 1;
    object->entries = entries;
    object->capacity = count;
    object->count = count;
    last = object->entries + last_index;
    object->span = last->key - object->entries[0].key;
}

void vector_curve_track_set_before_mode(BootVectorCurveTrackState* state, u32 value)
{
    state->before_mode = value;
    state->repeats = state->before_mode == 4 || state->after_mode == 4;
}

void vector_curve_track_set_after_mode(BootVectorCurveTrackState* state, u32 value)
{
    state->after_mode = value;
    state->repeats = state->before_mode == 4 || state->after_mode == 4;
}

s32 vector_curve_track_get_cycle_count(const BootVectorCurveTrackState* object)
{
    return object->cycle_count;
}

s16 vector_curve_track_get_key_count(const BootVectorCurveTrackState* object)
{
    return object->count;
}

s16 vector_curve_track_get_key_capacity(const BootVectorCurveTrackState* object)
{
    return object->capacity;
}

s32 vector_curve_track_on_append_key(void* object)
{
    return 0;
}

s32 vector_curve_track_on_replace_key(void* object)
{
    return 0;
}

s32 vector_curve_track_on_insert_key(void* object)
{
    return 0;
}

void vector_curve_track_on_set_single_key(void* object)
{
}

s32 vector_curve_track_has_key(BootVectorCurveTrackState* object, float key)
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

void vector_curve_track_get_zero_value(void* object)
{
    *(u32*)((u8*)object + 0x0) = 0;
    *(u32*)((u8*)object + 0x4) = 0;
    *(u32*)((u8*)object + 0x8) = 0;
    *(u32*)((u8*)object + 0xC) = 0;
}

float vector_curve_track_get_key_span(BootVectorCurveTrackState* object)
{
    s32 last_index;
    BootVectorCurveStateKey* last_entry;

    if (object->count < 2)
    {
        return 0.0f;
    }

    last_index = object->count - 1;
    last_entry = object->entries + last_index;
    return last_entry->key - object->entries[0].key;
}

/**
 * @brief Read the vector value associated with the first exactly equal key.
 * @param object Receiver with 48-byte records, valid when its count is positive.
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A vector_curve_track_find_key_value(BootVectorCurveTrackState* object, float key)
{
    s32 index;

    for (index = 0; index < object->count; index++)
    {
        if (key == object->entries[index].key)
        {
            BootVectorCurveStateKey* entry = object->entries + index;
            return *reinterpret_cast<const FieldVec4A*>(entry->value);
        }
    }

    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void BootVectorCurveTrackBase::evaluate(float key, FieldVec4B* output)
{
    *output = sample(key);
}

float vector_curve_track_wrap_key(BootVectorCurveTrackState* object, float key)
{
    s32 last_index = object->count - 1;
    BootVectorCurveStateKey* entries = object->entries;
    BootVectorCurveStateKey* last = entries + last_index;
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

BootVectorCurveStateKey* vector_curve_track_get_keys(const BootVectorCurveTrackState* object)
{
    return object->entries;
}

void vector_curve_track_free_keys(BootVectorCurveTrackBase* track)
{
    if (!track->state.external_keys)
    {
        if (track->unk04)
        {
            func_100BE0((u8*)track->unk04 - 16);
        }
    }

    track->unk04 = 0;
}

/** @brief Release the keyframe storage. */
BootFloatCurveTrackBase::~BootFloatCurveTrackBase()
{
    float_curve_track_free_keys(this);
}

void float_curve_track_reset_state(BootFloatCurveTrackState* object)
{
    object->entries = 0;
    object->before_mode = 1;
    object->after_mode = 1;
    object->capacity = 0;
    object->count = 0;
    object->unk24 = -1;
    object->cycle_count = 0;
    object->unk26 = -1;
    object->cached_index = -1;
    object->repeats = 0;
    object->external_keys = 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param count Requested keyframe count.
 */
void BootFloatCurveTrackBase::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] unk04;
    unk04 = new (0) BootFloatCurveTrackKey[count];
    state.key_capacity = count;

    if (!unk04)
    {
        state.key_capacity = 0;
    }
}

void float_curve_track_set_before_mode(BootFloatCurveTrackState* state, u32 value)
{
    state->before_mode = value;
    state->repeats = state->before_mode == 4 || state->after_mode == 4;
}

void float_curve_track_set_after_mode(BootFloatCurveTrackState* state, u32 value)
{
    state->after_mode = value;
    state->repeats = state->before_mode == 4 || state->after_mode == 4;
}

s32 float_curve_track_get_cycle_count(const BootFloatCurveTrackState* object)
{
    return object->cycle_count;
}

s16 float_curve_track_get_key_count(const BootFloatCurveTrackState* object)
{
    return object->count;
}

s16 float_curve_track_get_key_capacity(const BootFloatCurveTrackState* object)
{
    return object->capacity;
}

s32 float_curve_track_on_append_key(void* object)
{
    return 0;
}

s32 float_curve_track_on_replace_key(void* object)
{
    return 0;
}

s32 float_curve_track_on_insert_key(void* object)
{
    return 0;
}

void float_curve_track_on_set_single_key(void* object)
{
}

float float_curve_track_get_zero_value(void* object)
{
    return 0.0f;
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void BootFloatCurveTrackBase::evaluate(float key, float* output)
{
    *output = sample(key);
}

BootFloatCurveStateKey* float_curve_track_get_keys(const BootFloatCurveTrackState* object)
{
    return object->entries;
}

void float_curve_track_free_keys(BootFloatCurveTrackBase* track)
{
    if (!track->state.external_keys)
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
    object->before_mode = 1;
    object->after_mode = 1;
    object->capacity = 0;
    object->count = 0;
    object->unk3C = -1;
    object->cycle_count = 0;
    object->unk3E = -1;
    object->cached_index = -1;
    object->repeats = 0;
    object->external_keys = 0;
}

void func_001F1580(BootState1F1580* state, u32 value)
{
    state->before_mode = value;
    state->repeats = state->before_mode == 4 || state->after_mode == 4;
}

void func_001F15E0(BootState1F1580* state, u32 value)
{
    state->after_mode = value;
    state->repeats = state->before_mode == 4 || state->after_mode == 4;
}

s32 func_001F1640(const BootState1F1580* object)
{
    return object->cycle_count;
}

s16 func_001F1650(const BootState1F1580* object)
{
    return object->count;
}

s16 func_001F1660(const BootState1F1580* object)
{
    return object->capacity;
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
void BootClass1718C0::evaluate(float key, FieldVec4B* output) const
{
    *output = sample(key);
}

BootKeyEntry32* func_001F16E0(const BootState1F1580* object)
{
    return object->entries;
}

void func_001F16F0(BootClass1718C0* track)
{
    if (!track->state.external_keys)
    {
        if (track->unk04)
        {
            func_100BE0((u8*)track->unk04 - 16);
        }
    }

    track->unk04 = 0;
}

float vector_track_update_cycle_count(BootVectorTrackState* object, float key)
{
    float first = object->entries[0].key;
    float quotient = (key - first) / object->span;

    if (key < first)
    {
        quotient -= 1.0f;
    }

    object->cycle_count = quotient;

    if (object->cycle_count)
    {
        float result = key - (float)object->cycle_count * object->span;

        if ((object->before_mode == 3 && object->cycle_count < 0) || (object->after_mode == 3 && object->cycle_count > 0))
        {
            s32 last_index = object->count - 1;
            BootVectorStateKey* last_entry = object->entries + last_index;
            float last = last_entry->key;

            if (object->cycle_count & 1)
            {
                result = first + (last - result);
            }
        }

        return result;
    }

    return key;
}

/**
 * @brief Find the entries around a key, starting from the cached cursor.
 * @param track Track to search.
 * @param key Key to place.
 * @param lower Receives the lower entry index.
 * @param upper Receives the upper entry index.
 * @return One when a reflecting end mode extends the first or last segment, otherwise zero.
 */
u8 vector_track_find_surrounding_keys(BootVectorTrackBase* track, float key, s32* lower, s32* upper)
{
    s32 index;
    s32 count;
    s32 next;

    if (track->state.repeats)
    {
        if (track->state.before_mode == 4 && track->state.cycle_count < 0)
        {
            *lower = 0;
            *upper = 1;
            track->state.unk0c = 0;
            return 1;
        }

        if (track->state.after_mode == 4 && track->state.cycle_count > 0)
        {
            *lower = track->state.key_count - 2;
            *upper = track->state.key_count - 1;
            track->state.unk0c = track->state.key_count - 2;
            return 1;
        }
    }

    index = track->state.unk0c;
    count = track->state.key_count;

    while (index > 0 && key < static_cast<BootVectorTrackKey*>(track->unk04)[index].value.w)
    {
        index--;
    }

    index = clamp_low(index, 0);

    while ((next = index + 1) < count && !(key < static_cast<BootVectorTrackKey*>(track->unk04)[next].value.w))
    {
        index++;
    }

    if (index >= count - 1)
    {
        *lower = count - 2;
        *upper = count - 1;
    }
    else
    {
        *lower = index;
        *upper = index + 1;
    }

    track->state.unk0c = index;
    return 0;
}
/** @brief Release the keyframe storage. */
BootVectorTrackBase::~BootVectorTrackBase()
{
    vector_track_free_keys(this);
}

void vector_track_reset_state(BootVectorTrackState* object)
{
    object->entries = 0;
    object->before_mode = 1;
    object->after_mode = 1;
    object->capacity = 0;
    object->count = 0;
    object->unk2C = -1;
    object->cycle_count = 0;
    object->unk2E = -1;
    object->cached_index = -1;
    object->repeats = 0;
    object->external_keys = 0;
}

void vector_track_bind_keys(BootVectorTrackState* object, s32 count, BootVectorStateKey* entries)
{
    s32 last_index = count - 1;
    BootVectorStateKey* last;
    object->external_keys = 1;
    object->entries = entries;
    object->capacity = count;
    object->count = count;
    last = object->entries + last_index;
    object->span = last->key - object->entries[0].key;
}

void vector_track_set_before_mode(BootVectorTrackState* state, u32 value)
{
    state->before_mode = value;
    state->repeats = state->before_mode == 4 || state->after_mode == 4;
}

void vector_track_set_after_mode(BootVectorTrackState* state, u32 value)
{
    state->after_mode = value;
    state->repeats = state->before_mode == 4 || state->after_mode == 4;
}

s32 vector_track_get_cycle_count(const BootVectorTrackState* object)
{
    return object->cycle_count;
}

s16 vector_track_get_key_count(BootVectorTrackState* object)
{
    return object->count;
}

s16 vector_track_get_key_capacity(BootVectorTrackState* object)
{
    return object->capacity;
}

s32 vector_track_has_key(BootVectorTrackState* object, float key)
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

void vector_track_get_zero_value(void* object)
{
    *(u32*)((u8*)object + 0x0) = 0;
    *(u32*)((u8*)object + 0x4) = 0;
    *(u32*)((u8*)object + 0x8) = 0;
    *(u32*)((u8*)object + 0xC) = 0;
}

float vector_track_get_key_span(BootVectorTrackState* object)
{
    BootVectorStateKey* last;

    if (object->count < 2)
    {
        return 0.0f;
    }

    last = object->entries + (object->count - 1);
    return last->key - object->entries[0].key;
}

/**
 * @brief Read the vector value associated with the first exactly equal key.
 * @param object Receiver with vector-key entries, valid when its count is positive.
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A vector_track_find_key_value(BootVectorTrackState* object, float key)
{
    s32 index;

    for (index = 0; index < object->count; index++)
    {
        if (key == object->entries[index].key)
        {
            BootVectorStateKey* entry = object->entries + index;
            return *reinterpret_cast<const FieldVec4A*>(entry);
        }
    }

    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void BootVectorTrackBase::evaluate(float key, FieldVec4B* output)
{
    *output = sample(key);
}

float vector_track_wrap_key(BootVectorTrackState* object, float key)
{
    BootVectorStateKey* last = object->entries + (object->count - 1);
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

BootVectorStateKey* vector_track_get_keys(const BootVectorTrackState* object)
{
    return object->entries;
}

void vector_track_free_keys(BootVectorTrackBase* track)
{
    if (!track->state.external_keys)
    {
        if (track->unk04)
        {
            func_100BE0((u8*)track->unk04 - 16);
        }
    }

    track->unk04 = 0;
}

/** @brief Release the keyframe storage. */
BootFloatTrackBase::~BootFloatTrackBase()
{
    float_track_free_keys(this);
}

void float_track_reset_state(BootFloatTrackState* object)
{
    object->entries = 0;
    object->before_mode = 1;
    object->after_mode = 1;
    object->capacity = 0;
    object->count = 0;
    object->unk1C = -1;
    object->cycle_count = 0;
    object->unk1E = -1;
    object->cached_index = -1;
    object->repeats = 0;
    object->external_keys = 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param count Requested keyframe count.
 */
void BootFloatTrackBase::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] unk04;
    unk04 = new (0) BootFloatTrackKey[count];
    state.key_capacity = count;

    if (!unk04)
    {
        state.key_capacity = 0;
    }
}

void float_track_set_before_mode(BootFloatTrackState* state, u32 value)
{
    state->before_mode = value;
    state->repeats = state->before_mode == 4 || state->after_mode == 4;
}

void float_track_set_after_mode(BootFloatTrackState* state, u32 value)
{
    state->after_mode = value;
    state->repeats = state->before_mode == 4 || state->after_mode == 4;
}

s32 float_track_get_cycle_count(const BootFloatTrackState* object)
{
    return object->cycle_count;
}

s16 float_track_get_key_count(const BootFloatTrackState* object)
{
    return object->count;
}

s16 float_track_get_key_capacity(const BootFloatTrackState* object)
{
    return object->capacity;
}

float float_track_get_zero_value(void* object)
{
    return 0.0f;
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void BootFloatTrackBase::evaluate(float key, float* output)
{
    *output = sample(key);
}

BootFloatStateKey* float_track_get_keys(const BootFloatTrackState* object)
{
    return object->entries;
}

void float_track_free_keys(BootFloatTrackBase* track)
{
    if (!track->state.external_keys)
    {
        if (track->unk04)
        {
            func_100BE0((u8*)track->unk04 - 16);
        }
    }

    track->unk04 = 0;
}

/** @brief Release the keyframe storage. */
BootQuaternionTrackBase::~BootQuaternionTrackBase()
{
    quaternion_track_free_keys(this);
}

void quaternion_track_free_keys(BootQuaternionTrackBase* track)
{
    if (!track->state.external_keys)
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
    if (!track->state.external_keys)
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
void vector_track_pool_free(BootTrackPool<BootPooledVectorTrack>* pool, BootPooledVectorTrack* track)
{
    pool->free(track);
}

/**
 * @brief Mark a track's pool slot as free.
 * @param pool Pool that owns the track.
 * @param track Track to release.
 */
void vector_curve_track_pool_free(BootTrackPool<BootPooledVectorCurveTrack>* pool, BootPooledVectorCurveTrack* track)
{
    pool->free(track);
}

/** @brief Clear the pooled flag and reset the sequence. */
BootClass171680::BootClass171680()
{
    state.pooled = false;
    reset_state();
}

/** @brief Clear the pooled flag and reset the sequence. */
BootQuaternionTrackBase::BootQuaternionTrackBase()
{
    state.pooled = false;
    reset_state();
}

float float_track_wrap_key(BootFloatTrackState* object, float key)
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

float float_track_find_key_value(BootFloatTrackState* object, float key)
{
    s32 index;

    for (index = 0; index < object->count; index++)
    {
        if (key == object->entries[index].key)
        {
            BootFloatStateKey* entry = object->entries + index;
            return entry->value;
        }
    }

    return 0.0f;
}

float float_track_get_key_span(BootFloatTrackState* object)
{
    s32 last_index;

    if (object->count < 2)
    {
        return 0.0f;
    }

    last_index = object->count - 1;
    return object->entries[last_index].key - object->entries[0].key;
}

s32 float_track_has_key(BootFloatTrackState* object, float key)
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
void float_track_set_single_key(BootFloatTrackBase* object, const float* value, float key)
{
    object->on_set_single_key(value, key);
}

void float_track_on_set_single_key(void* object)
{
}

/** @brief Forward an indexed keyframe with a key to slot 0x70. */
s32 float_track_insert_key(BootFloatTrackBase* object, s32 index, float key, const float* value)
{
    return object->on_insert_key(index, key, value);
}

s32 float_track_on_insert_key(void* object)
{
    return 0;
}

/** @brief Forward an indexed keyframe with a key to slot 0x6C. */
s32 float_track_replace_key(BootFloatTrackBase* object, s32 index, float key, const float* value)
{
    return object->on_replace_key(index, key, value);
}

s32 float_track_on_replace_key(void* object)
{
    return 0;
}

/** @brief Forward a keyframe with a key to slot 0x68. */
s32 float_track_append_key(BootFloatTrackBase* object, const float* value, float key)
{
    return object->on_append_key(value, key);
}

s32 float_track_on_append_key(void* object)
{
    return 0;
}

void float_track_bind_keys(BootFloatTrackState* object, s32 count, BootFloatStateKey* entries)
{
    s32 last_index = count - 1;
    object->external_keys = 1;
    object->entries = entries;
    object->capacity = count;
    object->count = count;
    object->span = object->entries[last_index].key - object->entries[0].key;
}

/** @brief Clear the pooled flag and reset the sequence. */
BootFloatTrackBase::BootFloatTrackBase()
{
    state.pooled = false;
    reset_state();
}

/** @brief Forward to slot 0x74. */
void vector_track_set_single_key(BootVectorTrackBase* object, const FieldVec4A* value, float key)
{
    object->on_set_single_key(value, key);
}

void vector_track_on_set_single_key(void* object)
{
}

/** @brief Forward to slot 0x70. */
s32 vector_track_insert_key(BootVectorTrackBase* object, s32 index, float key, const FieldVec4A* value)
{
    return object->on_insert_key(index, key, value);
}

s32 vector_track_on_insert_key(void* object)
{
    return 0;
}

/** @brief Forward to slot 0x6C. */
s32 vector_track_replace_key(BootVectorTrackBase* object, s32 index, float key, const FieldVec4A* value)
{
    return object->on_replace_key(index, key, value);
}

s32 vector_track_on_replace_key(void* object)
{
    return 0;
}

/** @brief Forward to slot 0x68. */
s32 vector_track_append_key(BootVectorTrackBase* object, const FieldVec4A* value, float key)
{
    return object->on_append_key(value, key);
}

s32 vector_track_on_append_key(void* object)
{
    return 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param count Requested keyframe count.
 */
void BootVectorTrackBase::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] static_cast<BootVectorTrackKey*>(unk04);
    unk04 = new (0) BootVectorTrackKey[count];
    state.key_capacity = count;

    if (!unk04)
    {
        state.key_capacity = 0;
    }
}

/** @brief Clear the pooled flag and reset the sequence. */
BootVectorTrackBase::BootVectorTrackBase()
{
    state.pooled = false;
    reset_state();
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

/**
 * @brief Read the vector value associated with the first exactly equal key.
 * @param object Receiver with 32-byte records, valid when its count is positive.
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A func_001F2A60(BootState1F1580* object, float key)
{
    s32 index;

    for (index = 0; index < object->count; index++)
    {
        if (key == object->entries[index].key)
        {
            BootKeyEntry32* entry = object->entries + index;
            return *reinterpret_cast<const FieldVec4A*>(entry->value);
        }
    }

    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

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
    object->on_set_single_key(value, key);
}

void func_001F2B90(void* object)
{
}

/** @brief Forward to slot 0x70. */
s32 func_001F2BA0(BootClass1718C0* object, s32 index, float key, const FieldVec4A* value)
{
    return object->on_insert_key(index, key, value);
}

s32 func_001F2BD0(void* object)
{
    return 0;
}

/** @brief Forward to slot 0x6C. */
s32 func_001F2BE0(BootClass1718C0* object, s32 index, float key, const FieldVec4A* value)
{
    return object->on_replace_key(index, key, value);
}

s32 func_001F2C10(void* object)
{
    return 0;
}

/** @brief Forward to slot 0x68. */
s32 func_001F2C20(BootClass1718C0* object, const FieldVec4A* value, float key)
{
    return object->on_append_key(value, key);
}

s32 func_001F2C50(void* object)
{
    return 0;
}

void func_001F2C60(BootState1F1580* object, s32 count, BootKeyEntry32* entries)
{
    s32 last_index = count - 1;
    BootKeyEntry32* last;
    object->external_keys = 1;
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
void BootClass1718C0::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] static_cast<BootTrackKey1718C0*>(unk04);
    unk04 = new (0) BootTrackKey1718C0[count];
    state.key_capacity = count;

    if (!unk04)
    {
        state.key_capacity = 0;
    }
}

BootTrackKey1718C0::BootTrackKey1718C0()
{
}

/** @brief Clear the pooled flag and reset the sequence. */
BootClass1718C0::BootClass1718C0()
{
    state.pooled = false;
    reset_state();
}

float float_curve_track_wrap_key(BootFloatCurveTrackState* object, float key)
{
    s32 last_index = object->count - 1;
    BootFloatCurveStateKey* entries = object->entries;
    BootFloatCurveStateKey* last = entries + last_index;
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

float float_curve_track_find_key_value(BootFloatCurveTrackState* object, float key)
{
    s32 index;

    for (index = 0; index < object->count; index++)
    {
        if (key == object->entries[index].key)
        {
            BootFloatCurveStateKey* entry = object->entries + index;
            return entry->value;
        }
    }

    return 0.0f;
}

float float_curve_track_get_key_span(BootFloatCurveTrackState* object)
{
    s32 last_index;
    BootFloatCurveStateKey* last_entry;

    if (object->count < 2)
    {
        return 0.0f;
    }

    last_index = object->count - 1;
    last_entry = object->entries + last_index;
    return last_entry->key - object->entries[0].key;
}

s32 float_curve_track_has_key(BootFloatCurveTrackState* object, float key)
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

void float_curve_track_bind_keys(BootFloatCurveTrackState* object, s32 count, BootFloatCurveStateKey* entries)
{
    s32 last_index = count - 1;
    BootFloatCurveStateKey* last;
    object->external_keys = 1;
    object->entries = entries;
    object->capacity = count;
    object->count = count;
    last = object->entries + last_index;
    object->span = last->key - object->entries[0].key;
}

/** @brief Clear the pooled flag and reset the sequence. */
BootFloatCurveTrackBase::BootFloatCurveTrackBase()
{
    state.pooled = false;
    reset_state();
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param count Requested keyframe count.
 */
void BootVectorCurveTrackBase::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] static_cast<BootTrackKey1719E0*>(unk04);
    unk04 = new (0) BootTrackKey1719E0[count];
    state.key_capacity = count;

    if (!unk04)
    {
        state.key_capacity = 0;
    }
}

/** @brief Clear the pooled flag and reset the sequence. */
BootVectorCurveTrackBase::BootVectorCurveTrackBase()
{
    state.pooled = false;
    reset_state();
}

/** @brief Clear the pooled flag and reset the sequence. */
BootClass171A70::BootClass171A70()
{
    state.pooled = false;
    reset_state();
}

/**
 * @brief Store a single keyframe in the cached key and value.
 * @param value Keyframe value.
 * @param key Sort key.
 */
void BootFloatKeyTrack::on_set_single_key(const float* value, float key)
{
    set_before_mode(6);
    unk08.value = *value;
    unk08.key = key;
}

s32 float_track_read_entry(BootFloatTrackState* object, s32 index, float* key, float* value)
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

s32 float_track_insert_entry(BootFloatTrackState* object, s32 index, const float* value, float key)
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
        BootFloatStateKey* destination = &object->entries[cursor];
        BootFloatStateKey* source = &object->entries[cursor - 1];
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
    object->cached_index = -1;
    object->count++;
    return 1;
}

s32 float_track_replace_entry(BootFloatTrackState* object, s32 index, const float* value, float key)
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
    object->cached_index = -1;
    return 1;
}

s32 float_track_append_entry(BootFloatTrackState* object, const float* value, float key)
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
    object->cached_index = -1;
    object->count++;
    return 1;
}

/**
 * @brief Store a single keyframe in the cached value.
 * @param value Keyframe value.
 * @param key Key, stored in the value's fourth component.
 */
void BootVectorKeyTrack::on_set_single_key(const FieldVec4A* value, float key)
{
    set_before_mode(6);
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
s32 BootVectorKeyTrack::on_insert_key(s32 index, float key, const FieldVec4A* value)
{
    s32 count;
    s32 i;

    if (unk04 == 0)
    {
        return 0;
    }

    count = state.key_count;

    if (index >= count)
    {
        return 0;
    }

    if (count >= state.key_capacity)
    {
        return 0;
    }

    for (i = count; i > index; i--)
    {
        static_cast<BootVectorTrackKey*>(unk04)[i] = static_cast<BootVectorTrackKey*>(unk04)[i - 1];
    }

    static_cast<BootVectorTrackKey*>(unk04)[index].value = *value;
    static_cast<BootVectorTrackKey*>(unk04)[index].value.w = key;

    if (index == state.key_count - 1)
    {
        state.span = key - static_cast<BootVectorTrackKey*>(unk04)[0].value.w;
    }

    state.unk0e = -1;
    state.cached_index = -1;
    state.key_count++;
    return 1;
}

/**
 * @brief Store a single keyframe in the cached key and value.
 * @param value Keyframe value.
 * @param key Sort key.
 */
void BootClass171320::on_set_single_key(const FieldVec4A* value, float key)
{
    set_before_mode(6);
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
s32 BootClass171320::read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const
{
    if (unk04 == 0)
    {
        return 0;
    }

    if (index >= state.key_capacity)
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
s32 BootClass171320::on_insert_key(s32 index, float key, const FieldVec4A* value)
{
    s32 count;
    s32 i;

    if (unk04 == 0)
    {
        return 0;
    }

    count = state.key_count;

    if (index >= count)
    {
        return 0;
    }

    if (count >= state.key_capacity)
    {
        return 0;
    }

    for (i = count; i > index; i--)
    {
        static_cast<BootTrackKey1718C0*>(unk04)[i] = static_cast<BootTrackKey1718C0*>(unk04)[i - 1];
    }

    static_cast<BootTrackKey1718C0*>(unk04)[index].value = *value;
    static_cast<BootTrackKey1718C0*>(unk04)[index].key = key;

    if (index == state.key_count - 1)
    {
        state.span = key - static_cast<BootTrackKey1718C0*>(unk04)[0].key;
    }

    state.unk0e = -1;
    state.cached_index = -1;
    state.key_count++;
    return 1;
}

/**
 * @brief Replace an indexed keyframe.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootClass171320::on_replace_key(s32 index, float key, const FieldVec4A* value)
{
    if (unk04 == 0)
    {
        return 0;
    }

    if (index >= state.key_capacity)
    {
        return 0;
    }

    static_cast<BootTrackKey1718C0*>(unk04)[index].value = *value;
    static_cast<BootTrackKey1718C0*>(unk04)[index].key = key;

    if (index == state.key_count - 1)
    {
        state.span = key - static_cast<BootTrackKey1718C0*>(unk04)[0].key;
    }

    state.unk0e = -1;
    state.cached_index = -1;
    return 1;
}

/**
 * @brief Append a keyframe.
 * @param value Keyframe value.
 * @param key Sort key.
 * @return Nonzero when the keyframe was stored.
 */
s32 BootClass171320::on_append_key(const FieldVec4A* value, float key)
{
    if (unk04 == 0)
    {
        return 0;
    }

    if (state.key_count >= state.key_capacity)
    {
        return 0;
    }

    static_cast<BootTrackKey1718C0*>(unk04)[state.key_count].value = *value;
    static_cast<BootTrackKey1718C0*>(unk04)[state.key_count].key = key;
    state.span = key - static_cast<BootTrackKey1718C0*>(unk04)[0].key;
    state.unk0e = -1;
    state.cached_index = -1;
    state.key_count++;
    return 1;
}

/** @brief Reset to a single zero keyframe at key zero, then set before_mode to one. */
void BootFloatTrack::reset_keys()
{
    float zero = 0.0f;
    on_set_single_key(&zero, 0.0f);
    set_before_mode(1);
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @return Evaluated value.
 */
float BootFloatTrack::sample(float key)
{
    s32 lower;
    s32 upper;
    float wrapped_key;
    float result;
    u8 extrapolate;

    if (!unk04 || !state.key_count)
    {
        return 0.0f;
    }

    if (state.unk0c >= state.key_capacity)
    {
        state.unk0c = 0;
    }

    if (state.key_count == 1 && (!(key < unk04[0].key) || state.before_mode != 6))
    {
        return unk04[0].value;
    }

    if (key < unk04[0].key && state.before_mode == 6)
    {
        upper = 0;
        wrapped_key = key;
        lower = -1;
    }
    else
    {
        wrapped_key = float_track_update_cycle_count(reinterpret_cast<BootFloatTrackState*>(this), key);

        if (state.before_mode == 0 && state.cycle_count < 0)
        {
            return unk04[0].value;
        }

        if (state.after_mode == 0 && state.cycle_count > 0)
        {
            return unk04[state.key_count - 1].value;
        }

        extrapolate = float_track_find_surrounding_keys(this, wrapped_key, &lower, &upper);

        if (extrapolate)
        {
            wrapped_key = key;
        }
    }

    if (state.unk0e != lower || state.cached_index != upper)
    {
        state.unk0e = lower;
        state.cached_index = upper;
        BootFloatTrackKey* first = lower >= 0 ? unk04 + lower : &unk08;
        unk24.unk04 = 0;
        unk24.unk06 = 0;
        unk24.unk08 = 0;
        unk24.unk0C = 0;
        unk24.add_sample(first->key, first->value);
        s32 last = state.key_count - 1;
        // TODO: My guess; copying upper into its own local is the only way I found that matches.
        s32 upper_index = upper;

        if (upper_index == last && ((!(key < unk04[0].key) && state.after_mode == 2) || (key < unk04[0].key && state.before_mode == 2)))
        {
            BootFloatTrackKey* entries = unk04;
            unk24.add_sample(entries[upper_index].key, entries[0].value);
        }
        else if (lower < upper_index)
        {
            BootFloatTrackKey* second = unk04 + upper_index;
            unk24.add_sample(second->key, second->value);
        }
        else
        {
            unk24.add_sample(unk04[last].key, unk04[upper_index].value);
        }
    }

    result = unk24.sample(wrapped_key);

    if ((state.before_mode == 5 && state.cycle_count < 0) || (state.after_mode == 5 && state.cycle_count > 0))
    {
        float delta = unk04[state.key_count - 1].value - unk04[0].value;
        result += delta * state.cycle_count;
    }

    unk4c = (result - unk48) / D_001B6688;
    unk48 = result;
    return result;
}

/** @brief Reset to a single zero keyframe at key zero, then set before_mode to one. */
void BootVectorTrack::reset_keys()
{
    FieldVec4A zero(0.0f, 0.0f, 0.0f, 0.0f);
    on_set_single_key(&zero, 0.0f);
    set_before_mode(1);
}

s32 float_curve_track_read_entry(BootFloatCurveTrackState* object, s32 index, float* key, float* first, float* second, float* third)
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
void BootFloatCurveTrack::set_single_curve_key(const float* x, const float* y, const float* z, float key)
{
    set_before_mode(6);
    unk08.unk04 = *x;
    unk08.unk08 = *y;
    unk08.unk0c = *z;
    unk08.unk00 = key;
}

s32 float_curve_track_insert_curve_key(BootFloatCurveTrackState* object, s32 index, const float* first, const float* second, const float* third, float key)
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
        BootFloatCurveStateKey* destination = &object->entries[cursor];
        BootFloatCurveStateKey* source = &object->entries[cursor - 1];
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

s32 float_curve_track_replace_curve_key(BootFloatCurveTrackState* object, s32 index, const float* first, const float* second, const float* third, float key)
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

s32 float_curve_track_append_entry(BootFloatCurveTrackState* object, const float* first, const float* second, const float* third, float key)
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
float BootFloatCurveTrack::sample(float key)
{
    s32 lower;
    s32 upper;
    float wrapped_key;
    u8 extrapolate;
    float result;

    if (!unk04 || !state.key_count)
    {
        return 0.0f;
    }

    if (state.unk0c >= state.key_capacity)
    {
        state.unk0c = 0;
    }

    if (state.key_count == 1 && (!(key < unk04[0].unk00) || state.before_mode != 6))
    {
        return unk04[0].unk04;
    }

    extrapolate = 0;

    if (key < unk04[0].unk00 && state.before_mode == 6)
    {
        upper = 0;
        wrapped_key = key;
        lower = -1;
    }
    else
    {
        wrapped_key = float_curve_track_update_cycle_count(reinterpret_cast<BootFloatCurveTrackState*>(this), key);

        if (state.cycle_count)
        {
            if (state.before_mode == 0 && state.cycle_count < 0)
            {
                return unk04[0].unk04;
            }

            if (state.after_mode == 0 && state.cycle_count > 0)
            {
                return unk04[state.key_count - 1].unk04;
            }
        }

        extrapolate = float_curve_track_find_surrounding_keys(this, wrapped_key, &lower, &upper);

        if (extrapolate)
        {
            wrapped_key = key;
        }
    }

    if (!extrapolate)
    {
        if (state.unk0e != lower || state.cached_index != upper)
        {
            state.unk0e = lower;
            state.cached_index = upper;
            BootFloatCurveTrackKey* first = lower >= 0 ? unk04 + lower : &unk08;
            s32 last = state.key_count - 1;

            if (upper == last && ((!(key < unk04[0].unk00) && state.after_mode == 2) || (key < unk04[0].unk00 && state.before_mode == 2)))
            {
                BootFloatCurveTrackKey* entries = unk04;
                unk2C.set_endpoints(&first->unk04, &first->unk0c, &entries[0].unk04, &entries[0].unk08, first->unk00, entries[upper].unk00);
            }
            else if (lower < upper)
            {
                BootFloatCurveTrackKey* second = unk04 + upper;
                unk2C.set_endpoints(&first->unk04, &first->unk0c, &second->unk04, &second->unk08, first->unk00, second->unk00);
            }
            else
            {
                BootFloatCurveTrackKey* second = unk04 + last;
                unk2C.set_endpoints(&first->unk04, &first->unk0c, &second->unk04, &second->unk08, first->unk00, second->unk00);
            }
        }

        result = func_4B16C0(&unk2C, wrapped_key);

        if (state.cycle_count && ((state.before_mode == 5 && state.cycle_count < 0) || (state.after_mode == 5 && state.cycle_count > 0)))
        {
            float delta = unk04[state.key_count - 1].unk04 - unk04[0].unk04;
            result += delta * state.cycle_count;
        }
    }
    else if (wrapped_key < key)
    {
        s32 count = state.key_count;
        BootFloatCurveTrackKey* entries = unk04;
        BootFloatCurveTrackKey* last_entry = entries + (count - 1);
        BootFloatCurveTrackKey* previous_entry = entries + (count - 2);
        float last_key = last_entry->unk00;
        float previous_key = previous_entry->unk00;
        float slope = entries[count - 1].unk08 / (last_key - previous_key);
        result = entries[count - 1].unk04 + slope * (key - last_key);
    }
    else
    {
        BootFloatCurveTrackKey* entries = unk04;
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
void BootVectorCurveTrack::set_single_curve_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    set_before_mode(6);
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
s32 BootVectorCurveTrack::insert_curve_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    s32 count;
    s32 i;

    if (unk04 == 0)
    {
        return 0;
    }

    count = state.key_count;

    if (index >= count)
    {
        return 0;
    }

    if (count >= state.key_capacity)
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

    if (index == state.key_count - 1)
    {
        state.span = key - static_cast<BootTrackKey1719E0*>(unk04)[0].value.w;
    }

    state.key_count++;
    return 1;
}

void func_001F4730(BootState1F4730* state, u32 value)
{
    state->before_mode = value;
    state->repeats = state->before_mode == 4 || state->after_mode == 4;
}

void quaternion_track_set_before_mode(BootQuaternionTrackState* state, u32 value)
{
    state->before_mode = value;
    state->repeats = state->before_mode == 4 || state->after_mode == 4;
}

void func_001F47F0(BootState1F47F0* state, u32 value)
{
    state->before_mode = value;
    state->repeats = state->before_mode == 4 || state->after_mode == 4;
}

/**
 * @brief Store a value and key in the two-entry history and count it, up to two.
 * @param value Value to store.
 * @param key Key to store.
 */
void BootClass171B70::push_sample(const FieldVec4A* value, float key)
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

void float_history_push(BootFloatHistoryState* history, const float* value, float associated)
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
    object->before_mode = 1;
    object->after_mode = 1;
    object->capacity = 0;
    object->count = 0;
    object->unk3C = -1;
    object->cycle_count = 0;
    object->unk3E = -1;
    object->cached_index = -1;
    object->repeats = 0;
    object->external_keys = 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param count Requested keyframe count.
 */
void BootClass171A70::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] static_cast<BootTrackKey171A70*>(unk04);
    unk04 = new (0) BootTrackKey171A70[count];
    state.key_capacity = count;

    if (!unk04)
    {
        state.key_capacity = 0;
    }
}

void func_001F4AC0(BootState1F47F0* state, u32 value)
{
    state->after_mode = value;
    state->repeats = state->before_mode == 4 || state->after_mode == 4;
}

s32 func_001F4B20(const BootState1F47F0* object)
{
    return object->cycle_count;
}

s16 func_001F4B30(const BootState1F47F0* object)
{
    return object->count;
}

s16 func_001F4B40(const BootState1F47F0* object)
{
    return object->capacity;
}

s32 func_001F4B50(void* object)
{
    return 0;
}

/** @brief Forward to slot 0x68. */
s32 func_001F4B60(BootClass171A70* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return object->on_append_key(value, first, second, key);
}

s32 func_001F4B90(void* object)
{
    return 0;
}

/** @brief Forward to slot 0x6C. */
s32 func_001F4BA0(BootClass171A70* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->on_replace_key(index, key, value, first, second);
}

s32 func_001F4BD0(void* object)
{
    return 0;
}

/** @brief Forward to slot 0x70. */
s32 func_001F4BE0(BootClass171A70* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->on_insert_key(index, key, value, first, second);
}

void func_001F4C10(void* object)
{
}

/** @brief Forward to slot 0x74. */
void func_001F4C20(BootClass171A70* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    object->on_set_single_key(value, first, second, key);
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
void BootClass171A70::evaluate(float key, FieldVec4B* output) const
{
    *output = sample(key);
}

BootKeyEntry32* func_001F4CC0(const BootState1F47F0* object)
{
    return object->entries;
}

/** @brief Forward to slot 0x68. */
s32 vector_curve_track_append_key(BootVectorCurveTrackBase* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return object->on_append_key(value, first, second, key);
}

/** @brief Forward to slot 0x6C. */
s32 vector_curve_track_replace_key(BootVectorCurveTrackBase* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first,
                                   const FieldVec4A* second)
{
    return object->on_replace_key(index, key, value, first, second);
}

/** @brief Forward to slot 0x70. */
s32 vector_curve_track_insert_key(BootVectorCurveTrackBase* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first,
                                  const FieldVec4A* second)
{
    return object->on_insert_key(index, key, value, first, second);
}

/** @brief Forward to slot 0x74. */
void vector_curve_track_set_single_key(BootVectorCurveTrackBase* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    object->on_set_single_key(value, first, second, key);
}

float float_curve_track_update_cycle_count(BootFloatCurveTrackState* object, float key)
{
    float first = object->entries[0].key;
    float quotient = (key - first) / object->span;

    if (key < first)
    {
        quotient -= 1.0f;
    }

    object->cycle_count = quotient;

    if (object->cycle_count)
    {
        float result = key - (float)object->cycle_count * object->span;

        if ((object->before_mode == 3 && object->cycle_count < 0) || (object->after_mode == 3 && object->cycle_count > 0))
        {
            s32 last_index = object->count - 1;
            BootFloatCurveStateKey* last_entry = object->entries + last_index;
            float last = last_entry->key;

            if (object->cycle_count & 1)
            {
                result = first + (last - result);
            }
        }

        return result;
    }

    return key;
}

/**
 * @brief Find the entries around a key, starting from the cached cursor.
 * @param track Track to search.
 * @param key Key to place.
 * @param lower Receives the lower entry index.
 * @param upper Receives the upper entry index.
 * @return One when a reflecting end mode extends the first or last segment, otherwise zero.
 */
u8 float_curve_track_find_surrounding_keys(BootFloatCurveTrackBase* track, float key, s32* lower, s32* upper)
{
    s32 index;
    s32 count;
    s32 next;

    if (track->state.repeats)
    {
        if (track->state.before_mode == 4 && track->state.cycle_count < 0)
        {
            *lower = 0;
            *upper = 1;
            track->state.unk0c = 0;
            return 1;
        }

        if (track->state.after_mode == 4 && track->state.cycle_count > 0)
        {
            *lower = track->state.key_count - 2;
            *upper = track->state.key_count - 1;
            track->state.unk0c = track->state.key_count - 2;
            return 1;
        }
    }

    index = track->state.unk0c;
    count = track->state.key_count;

    while (index > 0 && key < track->unk04[index].unk00)
    {
        index--;
    }

    index = clamp_low(index, 0);

    while ((next = index + 1) < count && !(key < track->unk04[next].unk00))
    {
        index++;
    }

    if (index >= count - 1)
    {
        *lower = count - 2;
        *upper = count - 1;
    }
    else
    {
        *lower = index;
        *upper = index + 1;
    }

    track->state.unk0c = index;
    return 0;
}
/** @brief Forward to slot 0x68. */
s32 float_curve_track_append_key(BootFloatCurveTrackBase* object, const float* x, const float* y, const float* z, float key)
{
    return object->on_append_key(x, y, z, key);
}

/** @brief Forward to slot 0x6C. */
s32 float_curve_track_replace_key(BootFloatCurveTrackBase* object, s32 index, float key, const float* x, const float* y, const float* z)
{
    return object->on_replace_key(index, key, x, y, z);
}

/** @brief Forward to slot 0x70. */
s32 float_curve_track_insert_key(BootFloatCurveTrackBase* object, s32 index, float key, const float* x, const float* y, const float* z)
{
    return object->on_insert_key(index, key, x, y, z);
}

/** @brief Forward to slot 0x74. */
void float_curve_track_set_single_key(BootFloatCurveTrackBase* object, const float* x, const float* y, const float* z, float key)
{
    object->on_set_single_key(x, y, z, key);
}

float float_track_update_cycle_count(BootFloatTrackState* object, float key)
{
    float first = object->entries[0].key;
    float quotient = (key - first) / object->span;

    if (key < first)
    {
        quotient -= 1.0f;
    }

    object->cycle_count = quotient;

    if (object->cycle_count)
    {
        float result = key - (float)object->cycle_count * object->span;

        if ((object->before_mode == 3 && object->cycle_count < 0) || (object->after_mode == 3 && object->cycle_count > 0))
        {
            s32 last_index = object->count - 1;
            BootFloatStateKey* last_entry = object->entries + last_index;
            float last = last_entry->key;

            if (object->cycle_count & 1)
            {
                result = first + (last - result);
            }
        }

        return result;
    }

    return key;
}

/**
 * @brief Find the entries around a key, starting from the cached cursor.
 * @param track Track to search.
 * @param key Key to place.
 * @param lower Receives the lower entry index.
 * @param upper Receives the upper entry index.
 * @return One when a reflecting end mode extends the first or last segment, otherwise zero.
 */
u8 float_track_find_surrounding_keys(BootFloatTrackBase* track, float key, s32* lower, s32* upper)
{
    s32 index;
    s32 count;
    s32 next;

    if (track->state.repeats)
    {
        if (track->state.before_mode == 4 && track->state.cycle_count < 0)
        {
            *lower = 0;
            *upper = 1;
            track->state.unk0c = 0;
            return 1;
        }

        if (track->state.after_mode == 4 && track->state.cycle_count > 0)
        {
            *lower = track->state.key_count - 2;
            *upper = track->state.key_count - 1;
            track->state.unk0c = track->state.key_count - 2;
            return 1;
        }
    }

    index = track->state.unk0c;
    count = track->state.key_count;

    while (index > 0 && key < track->unk04[index].key)
    {
        index--;
    }

    index = clamp_low(index, 0);

    while ((next = index + 1) < count && !(key < track->unk04[next].key))
    {
        index++;
    }

    if (index >= count - 1)
    {
        *lower = count - 2;
        *upper = count - 1;
    }
    else
    {
        *lower = index;
        *upper = index + 1;
    }

    track->state.unk0c = index;
    return 0;
}
void quaternion_track_reset_state(BootQuaternionTrackState* object)
{
    object->entries = 0;
    object->before_mode = 1;
    object->after_mode = 1;
    object->capacity = 0;
    object->count = 0;
    object->unk1C = -1;
    object->cycle_count = 0;
    object->unk1E = -1;
    object->cached_index = -1;
    object->repeats = 0;
    object->external_keys = 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param count Requested keyframe count.
 */
void BootQuaternionTrackBase::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] static_cast<BootQuaternionTrackKey*>(unk04);
    unk04 = new (0) BootQuaternionTrackKey[count];
    state.key_capacity = count;

    if (!unk04)
    {
        state.key_capacity = 0;
    }
}

void quaternion_track_bind_keys(BootQuaternionTrackState* object, s32 count, BootQuaternionStateKey* entries)
{
    s32 last_index = count - 1;
    BootQuaternionStateKey* last;
    object->external_keys = 1;
    object->entries = entries;
    object->capacity = count;
    object->count = count;
    last = object->entries + last_index;
    object->span = (float)last->key - (float)object->entries[0].key;
}

void quaternion_track_set_after_mode(BootQuaternionTrackState* state, u32 value)
{
    state->after_mode = value;
    state->repeats = state->before_mode == 4 || state->after_mode == 4;
}

s32 quaternion_track_get_cycle_count(const BootQuaternionTrackState* object)
{
    return object->cycle_count;
}

s16 quaternion_track_get_key_count(const BootQuaternionTrackState* object)
{
    return object->count;
}

s16 quaternion_track_get_key_capacity(const BootQuaternionTrackState* object)
{
    return object->capacity;
}

s32 quaternion_track_on_append_key(void* object)
{
    return 0;
}

/** @brief Forward to slot 0x68. */
s32 quaternion_track_append_key(BootQuaternionTrackBase* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return object->on_append_key(value, first, second, key);
}

s32 quaternion_track_on_replace_key(void* object)
{
    return 0;
}

/** @brief Forward to slot 0x6C. */
s32 quaternion_track_replace_key(BootQuaternionTrackBase* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first,
                                 const FieldVec4A* second)
{
    return object->on_replace_key(index, key, value, first, second);
}

s32 quaternion_track_on_insert_key(void* object)
{
    return 0;
}

/** @brief Forward to slot 0x70. */
s32 quaternion_track_insert_key(BootQuaternionTrackBase* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first,
                                const FieldVec4A* second)
{
    return object->on_insert_key(index, key, value, first, second);
}

void quaternion_track_on_set_single_key(void* object)
{
}

/** @brief Forward to slot 0x74. */
void quaternion_track_set_single_key(BootQuaternionTrackBase* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    object->on_set_single_key(value, first, second, key);
}

s32 quaternion_track_has_key(BootQuaternionTrackState* object, float key)
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

void quaternion_track_get_zero_value(void* object)
{
    *(u32*)((u8*)object + 0x0) = 0;
    *(u32*)((u8*)object + 0x4) = 0;
    *(u32*)((u8*)object + 0x8) = 0;
    *(u32*)((u8*)object + 0xC) = 0;
}

float quaternion_track_get_key_span(BootQuaternionTrackState* object)
{
    s32 last_index;
    BootQuaternionStateKey* last_entry;

    if (object->count < 2)
    {
        return 0.0f;
    }

    last_index = object->count - 1;
    last_entry = object->entries + last_index;
    return (float)last_entry->key - (float)object->entries[0].key;
}

/**
 * @brief Read the result pointer back through its address.
 * @param out Result pointer.
 */
static inline void reread_result(FieldVec4A*& out)
{
    // TODO: The original reads the result pointer again after the copy; a volatile read is the only way I found that matches.
    FieldVec4A* volatile* slot = &out;
    (void)*slot;
}

/**
 * @brief Find the keyframe with a key and decode its rotation.
 * @param out Receives the rotation, or zero when the key is absent.
 * @param object Keyframe array.
 * @param key Key to find.
 */
void quaternion_track_find_key_value(FieldVec4A* out, BootQuaternionTrackState* object, float key)
{
    s32 index;

    for (index = 0; index < object->count; index++)
    {
        BootQuaternionStateKey* entry = object->entries + index;

        if (key == entry->key)
        {
            FieldVec4A value;
            vu0_decode_short_quaternion(entry);
            vu0_store_decoded_quaternion(&value);
            *out = value;
            reread_result(out);
            return;
        }
    }

    FieldVec4A* result = out;
    result->x = 0.0f;
    result->y = 0.0f;
    result->z = 0.0f;
    result->w = 0.0f;
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void BootQuaternionTrackBase::evaluate(float key, FieldVec4B* output) const
{
    *output = sample(key);
}

float quaternion_track_wrap_key(BootQuaternionTrackState* object, float key)
{
    s32 last_index = object->count - 1;
    BootQuaternionStateKey* entries = object->entries;
    BootQuaternionStateKey* last = entries + last_index;
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

BootQuaternionStateKey* quaternion_track_get_keys(const BootQuaternionTrackState* object)
{
    return object->entries;
}

void func_001F58C0(BootState1F4730* object)
{
    object->entries = 0;
    object->before_mode = 1;
    object->after_mode = 1;
    object->capacity = 0;
    object->count = 0;
    object->unk4C = -1;
    object->cycle_count = 0;
    object->unk4E = -1;
    object->cached_index = -1;
    object->repeats = 0;
    object->external_keys = 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param count Requested keyframe count.
 */
void BootClass171680::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] static_cast<BootTrackKey171680*>(unk04);
    unk04 = new (0) BootTrackKey171680[count];
    state.key_capacity = count;

    if (!unk04)
    {
        state.key_capacity = 0;
    }
}

void func_001F5A00(BootState1F4730* object, s32 count, BootKeyEntry48* entries)
{
    s32 last_index = count - 1;
    BootKeyEntry48* last;
    object->external_keys = 1;
    object->entries = entries;
    object->capacity = count;
    object->count = count;
    last = object->entries + last_index;
    object->span = last->key - object->entries[0].key;
}

void func_001F5A50(BootState1F4730* state, u32 value)
{
    state->after_mode = value;
    state->repeats = state->before_mode == 4 || state->after_mode == 4;
}

s32 func_001F5AB0(const BootState1F4730* object)
{
    return object->cycle_count;
}

s16 func_001F5AC0(const BootState1F4730* object)
{
    return object->count;
}

s16 func_001F5AD0(const BootState1F4730* object)
{
    return object->capacity;
}

s32 func_001F5AE0(void* object)
{
    return 0;
}

/** @brief Forward to slot 0x68. */
s32 func_001F5AF0(BootClass171680* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return object->on_append_key(value, first, second, key);
}

s32 func_001F5B20(void* object)
{
    return 0;
}

/** @brief Forward to slot 0x6C. */
s32 func_001F5B30(BootClass171680* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->on_replace_key(index, key, value, first, second);
}

s32 func_001F5B60(void* object)
{
    return 0;
}

/** @brief Forward to slot 0x70. */
s32 func_001F5B70(BootClass171680* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->on_insert_key(index, key, value, first, second);
}

void func_001F5BA0(void* object)
{
}

/** @brief Forward to slot 0x74. */
void func_001F5BB0(BootClass171680* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    object->on_set_single_key(value, first, second, key);
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

/**
 * @brief Read the vector value associated with the first exactly equal key.
 * @param object Receiver with 48-byte records, valid when its count is positive.
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A func_001F5CA0(BootState1F4730* object, float key)
{
    s32 index;

    for (index = 0; index < object->count; index++)
    {
        if (key == object->entries[index].key)
        {
            BootKeyEntry48* entry = object->entries + index;
            return *reinterpret_cast<const FieldVec4A*>(entry->value);
        }
    }

    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void BootClass171680::evaluate(float key, FieldVec4B* output) const
{
    *output = sample(key);
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

BootKeyEntry48* func_001F5E00(const BootState1F4730* object)
{
    return object->entries;
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

/**
 * @brief Read the vector value associated with the first exactly equal key.
 * @param object Receiver with 32-byte records, valid when its count is positive.
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A func_001F5EB0(BootState1F47F0* object, float key)
{
    s32 index;

    for (index = 0; index < object->count; index++)
    {
        if (key == object->entries[index].key)
        {
            BootKeyEntry32* entry = object->entries + index;
            return *reinterpret_cast<const FieldVec4A*>(entry->value);
        }
    }

    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

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
    object->external_keys = 1;
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
        node = lib_find_renderable_entry(menu->scene, g_new_game_node_name);
        break;
    case 1:
        node = lib_find_renderable_entry(menu->scene, g_continue_node_name);
        break;
    case 2:
        node = lib_find_renderable_entry(menu->scene, g_battle_collection_node_name);
        break;
    case 3:
        node = lib_find_renderable_entry(menu->scene, g_install_node_name);
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

            node->set_scale_vector(&value);
            copy_vector(&value, &node->base_color_factor);

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

                copy_vector(&node->base_color_factor, &value);
                node->update_combined_color_factor();
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

            node->set_scale_vector(&value);
            copy_vector(&value, &node->base_color_factor);

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

            copy_vector(&node->base_color_factor, &value);
            node->update_combined_color_factor();
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
    BootSystemSettings* settings = (BootSystemSettings*)func_101440(func_101290(func_10D8E0()), 1);
    BootClass170F30* node = find_menu_item(this, selected);

    if (node == 0)
    {
        *x = 0.0f;
        *y = 0.0f;
        return;
    }

    if (!node->matrix_ready)
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
    continue_node = lib_find_renderable_entry(scene, g_continue_node_name);

    if (continue_node == 0)
    {
        return;
    }

    BootClass170F30* collection_node = lib_find_renderable_entry(scene, g_battle_collection_node_name);

    if (collection_node == 0)
    {
        return;
    }

    BootVector4DDAA0 color;
    copy_vector(&color, &collection_node->base_color_factor);

    if (first == 5 || second == 5)
    {
        color.w = 1.0f;
        collection_ready = 1;
        copy_vector(&collection_node->base_color_factor, &color);
        collection_node->update_combined_color_factor();
    }
    else
    {
        color.x = 1.0f;
        color.y = 1.0f;
        color.z = 1.0f;
        color.w = 0.5f;
        collection_ready = 0;
        copy_vector(&collection_node->base_color_factor, &color);
        collection_node->update_combined_color_factor();
    }

    copy_vector(&color, &continue_node->base_color_factor);

    if (slot1 == 0x11 || slot2 == 0x11)
    {
        color.w = 1.0f;
        continue_ready = 1;
        copy_vector(&continue_node->base_color_factor, &color);
        continue_node->update_combined_color_factor();
    }
    else
    {
        color.x = 1.0f;
        color.y = 1.0f;
        color.z = 1.0f;
        color.w = 0.5f;
        continue_ready = 0;
        copy_vector(&continue_node->base_color_factor, &color);
        continue_node->update_combined_color_factor();
    }
}

/** @brief Run the menu state machine. */
void BootTitleMenu::update()
{
    BootSystemSettings* settings;
    BootInput* input = g_boot_program.input;
    settings = (BootSystemSettings*)func_101440(func_101290(func_10D8E0()), 1);

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
        scene = new (0) BootScene;
        func_4791F0(scene, scene_data);
        func_474010(scene, g_boot_program.display, D_001B6614, D_001B6624, D_001B6628, D_001B661C, 1);
        delete[] scene_data;
        scene_data = 0;
        func_40B3A0(unk30);
        delete[] unk30;
        unk30 = 0;
        camera = lib_find_camera_entry(scene, g_title_camera_node_name);
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
        cursor = new (0) BootSelectionCursor;
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

        if (input->pressed & settings->confirm_buttons)
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
    g_boot_program.trophy_card->set_mode(2);
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
 * @brief Draw a progress bar: a dark border, the bar outline and a fill proportional to done / total.
 * @param bar Progress bar to draw.
 * @param done Completed amount; clamped to total.
 * @param total Total amount.
 */
void progress_bar_draw(BootProgressBar* bar, s32 done, s32 total)
{
    BootDrawSettings settings;
    s32 fill;

    func_455DF0(bar->draw_buffer, 0, 1);
    init_draw_settings(&settings);
    settings.unk00 = 0xC;
    settings.unk02 = 0;
    settings.unk05 = 1;
    settings.unk06 = 0;
    FieldVec4A normal(0.0f, 0.0f, -1.0f, 1.0f);

    if (total < done)
    {
        done = total;
    }

    if (total > 999)
    {
        fill = done / (total / 1000);
    }
    else
    {
        fill = done * 1000 / total;
    }

    func_455150(bar->draw_buffer, &settings);
    s32 width = bar->width;
    s32 height = bar->height;
    u32 color = bar->color;
    s32 depth = bar->mode;
    func_4550F0(bar->draw_buffer, 4);
    add_vertex(bar->draw_buffer, FieldVec4A(-2.0f, -1.0f, (float)depth, 1.0f), normal, 0, 0x80301004);
    add_vertex(bar->draw_buffer, FieldVec4A(2.0f + width, -1.0f, (float)depth, 1.0f), normal, 0, 0x80301004);
    add_vertex(bar->draw_buffer, FieldVec4A(-2.0f, 1.0f + height, (float)depth, 1.0f), normal, 0, 0x80301004);
    add_vertex(bar->draw_buffer, FieldVec4A(2.0f + width, 1.0f + height, (float)depth, 1.0f), normal, 0, 0x80301004);
    func_4550F0(bar->draw_buffer, 4);
    add_vertex(bar->draw_buffer, FieldVec4A(0.0f, 0.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A((float)width, 0.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(0.0f, 1.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A((float)width, 1.0f, (float)depth, 1.0f), normal, 0, color);
    func_4550F0(bar->draw_buffer, 4);
    add_vertex(bar->draw_buffer, FieldVec4A(0.0f, height - 1.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A((float)width, height - 1.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(0.0f, (float)height, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A((float)width, (float)height, (float)depth, 1.0f), normal, 0, color);
    func_4550F0(bar->draw_buffer, 4);
    add_vertex(bar->draw_buffer, FieldVec4A(-1.0f, 0.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(1.0f, 0.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(-1.0f, (float)height, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(1.0f, (float)height, (float)depth, 1.0f), normal, 0, color);
    func_4550F0(bar->draw_buffer, 4);
    add_vertex(bar->draw_buffer, FieldVec4A(width - 1.0f, 0.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(1.0f + width, 0.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(width - 1.0f, (float)height, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(1.0f + width, (float)height, (float)depth, 1.0f), normal, 0, color);
    func_4550F0(bar->draw_buffer, 4);
    add_vertex(bar->draw_buffer, FieldVec4A(3.0f, 3.0f, (float)depth, 1.0f), normal, 0, color);
    float right = 3.0f + ((width - 6.0f) * fill) / 1000.0f;
    add_vertex(bar->draw_buffer, FieldVec4A(right, 3.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(3.0f, height - 3.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(right, height - 3.0f, (float)depth, 1.0f), normal, 0, color);
    func_455BD0(bar->draw_buffer, 0, 1.0f, 0);
}

void init_draw_settings(BootDrawSettings* settings)
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
void progress_bar_reset(BootProgressBar* bar, s32 width, s32 height, u32 color, s32 mode)
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
    bar->unk18 = new (0) BootModel;
    bar->draw_buffer->allocate_storage(2, 0x600, 1, 8);
    bar->width = width;
    bar->height = height;
    bar->color = color;
    bar->mode = mode;
    progress_bar_draw(bar, 0, 1);
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
void BootScreenFade::update()
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
void BootScreenFade::on_packet_complete(u32 value)
{
    dma_pending = 0;
    func_4D00B0(this);
}

/** @brief Mark the fade active and submit its packet. */
void BootScreenFade::render()
{
    dma_pending = 1;
    func_11F510(packet, static_cast<BootDmaCallbacks*>(this));
}

/**
 * @brief Build the fade's GS packet: upload each of the ten strips to VRAM and draw it as a sprite at the fade's
 * alpha. The first call only arms the fade.
 * @param matrix Matrix supplied by the caller; unused.
 * @param context Opaque caller context; unused.
 */
void BootScreenFade::build_packet(const void* matrix, void* context)
{
    if (!unkc8)
    {
        unkc8 = 1;
        return;
    }

    BootPacketBuffer* buffer_packet = packet;
    buffer_packet->unk08 = buffer_packet->unk00 + 0x40;
    buffer_packet->unk0c = buffer_packet->unk08;
    BootFadeStripPacket* strip = reinterpret_cast<BootFadeStripPacket*>(func_11F860(packet, 0));
    BootVramRequest request;
    request.width = 64;
    request.height = 448;
    request.size = 0x1C000;
    request.unk0c = 1;
    request.unk0e = 6;
    request.unk0f = 10;
    u32 address = func_4D93A0(D_001B663C, &request, 0x54744664, 1, 0, 0, 1, 0);

    if (address != 0)
    {
        u32 base = address >> 6;
        float top = 1824.0f;
        float bottom = 2272.0f;
        float left = 1728.0f;
        float width = 64.0f;

        for (s32 i = 0; i < 10; i++)
        {
            u8* image = buffer + 448 * (i * 64) * 3 / 16 * 16;
            strip->transfer_dma = 0x10000006;
            strip->transfer_tag.tag = 0x1000000000000004ULL;
            strip->transfer_tag.registers = 0;
            strip->transfer_tag.fields.register0 = 0xE;
            strip->bitbltbuf = ((u64)base << 32) | 0x0101000000000000ULL;
            strip->bitbltbuf_register = 0x50;
            strip->trxpos = 1;
            strip->trxpos_register = 0x51;
            strip->trxreg = 0x000001C000000040ULL;
            strip->trxreg_register = 0x52;
            strip->trxdir = 0;
            strip->trxdir_register = 0x53;
            strip->image_tag = 0x1800000000001500ULL;
            strip->image_dma = ((u64)(u32)image << 32) | 0x30001500;
            strip->draw_dma = 0x10000008;
            strip->draw_tag.tag = 0x1000000000008004ULL;
            strip->draw_tag.registers = 0;
            strip->draw_tag.fields.register0 = 0xE;
            strip->texflush = 0;
            strip->texflush_register = 0x3F;
            strip->tex0 = base | 0x0000000298104000ULL;
            strip->tex0_register = 7;
            strip->prim = 0x356;
            strip->prim_register = 0;
            u32 color = 0x808080;
            color |= (s32)(128.0f * unkcc) << 24;
            strip->rgbaq = color;
            strip->rgbaq_register = 1;
            strip->sprite_tag.tag = 0x4400000000008001ULL;
            strip->sprite_tag.registers = 0;
            strip->sprite_tag.fields.register0 = 3;
            strip->sprite_tag.fields.register1 = 5;
            strip->sprite_tag.fields.register2 = 3;
            strip->sprite_tag.fields.register3 = 5;
            strip->uv0 = 0x80008;
            strip->xyz0 = ((u64)(s32)(top * 16.0f) << 16) | (u64)((s32)(left + i * width) << 4) | ((u64)0xFFFFFF << 32);
            strip->uv1 = 0x1C080408;
            strip->xyz1 = ((u64)(s32)(bottom * 16.0f) << 16) | (u64)((s32)(left + (1.0f + i) * width) << 4) | ((u64)0xFFFFFF << 32);
            strip++;
        }

        *reinterpret_cast<u64*>(strip) = 0x70000000;
        func_11F830(packet, reinterpret_cast<u8*>(strip) + 0x10);
        unk63 = 1;
    }
}

/** @brief Destroy the strips, the copy buffer and the packet. */
BootScreenFade::~BootScreenFade()
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
BootPacketBuffer::~BootPacketBuffer()
{
    if (!unk14)
    {
        delete unk04;
    }
}

#include "overlays/boot/transform_inlines.h"

/** @brief Copy the display into ten strips and show them, fully opaque. @param display Display to copy. */
BootScreenFade::BootScreenFade(BootDimensionsACD0* display)
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
        images[i] = new (0) BootImageStrip;
        images[i]->unk65 = 1;
        func_4333A0(images[i], buffer + height * (i * 64) * 3 / 16 * 16, (display->unk160 & 0x1FF) << 5, width / 64, 1, i * 64, 0, 0x40, height);
        D_001B661C->append_node(images[i], -1);
    }

    func_001DFE40(0x4000);
    unk65 = 1;
    func_001DFE30(0x400);
    packet = new (0) BootPacketBuffer(0x400);
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

/**
 * @brief Build an image's quad from a rectangle of its texture and a rectangle of its palette, and queue the
 * model for drawing.
 * @param image Image to build.
 * @param x Left edge of the texture rectangle, in texels.
 * @param y Top edge of the texture rectangle.
 * @param width Rectangle width, which is also the quad's width.
 * @param height Rectangle height, which is also the quad's height.
 * @param palette_x Left edge of the palette rectangle.
 * @param palette_y Top edge of the palette rectangle.
 * @param palette_width Palette rectangle width.
 * @param palette_height Palette rectangle height.
 * @param color Vertex color.
 * @param depth Z position of the quad.
 */
void image_set_rectangle_with_palette(BootImage* image, s32 x, s32 y, s32 width, s32 height, s32 palette_x, s32 palette_y, s32 palette_width,
                                      s32 palette_height, u32 color, s32 depth)
{
    BootDrawSettings settings;

    func_455DF0(image->draw_buffer, 1, 1);
    init_draw_settings(&settings);
    settings.unk06 = 0;
    settings.unk02 = 2;
    settings.unk00 = 0x5C;
    settings.unk05 = 1;
    FieldVec4A normal(0.0f, 0.0f, -1.0f, 1.0f);
    func_455150(image->draw_buffer, &settings);
    func_4550F0(image->draw_buffer, 4);

    if (image->centered)
    {
        float half_width = 0.5f * (float)width;
        float half_height = 0.5f * (float)height;
        add_vertex(image->draw_buffer, FieldVec4A(-half_width, -half_height, (float)depth, 1.0f), normal,
                   ((x << 12) / image->texture_width) | (((y << 12) / image->texture_height) << 16), color);
        add_vertex(image->draw_buffer, FieldVec4A(half_width, -half_height, (float)depth, 1.0f), normal,
                   (((y << 12) / image->texture_height) << 16) | (((x + width) << 12) / image->texture_width), color);
        add_vertex(image->draw_buffer, FieldVec4A(-half_width, half_height, (float)depth, 1.0f), normal,
                   ((x << 12) / image->texture_width) | ((((y + height) << 12) / image->texture_height) << 16), color);
        add_vertex(image->draw_buffer, FieldVec4A(half_width, half_height, (float)depth, 1.0f), normal,
                   (((x + width) << 12) / image->texture_width) | ((((y + height) << 12) / image->texture_height) << 16), color);
    }
    else
    {
        add_vertex(image->draw_buffer, FieldVec4A(0.0f, 0.0f, (float)depth, 1.0f), normal,
                   ((x << 12) / image->texture_width) | (((y << 12) / image->texture_height) << 16), color);
        // TODO: right as its own variable shifted in place is a guess; it's what gets the
        // sum and its shift to share a register like the original.
        s32 right = x + width;
        right = (u32)right << 12;
        add_vertex(image->draw_buffer, FieldVec4A((float)width, 0.0f, (float)depth, 1.0f), normal,
                   (((y << 12) / image->texture_height) << 16) | (right / image->texture_width), color);
        add_vertex(image->draw_buffer, FieldVec4A(0.0f, (float)height, (float)depth, 1.0f), normal,
                   ((x << 12) / image->texture_width) | ((((y + height) << 12) / image->texture_height) << 16), color);
        add_vertex(image->draw_buffer, FieldVec4A((float)width, (float)height, (float)depth, 1.0f), normal,
                   (right / image->texture_width) | ((((y + height) << 12) / image->texture_height) << 16), color);
    }

    if (image->has_palette)
    {
        settings.unk05 = 0;
        settings.unk03 = 1;
        func_455150(image->draw_buffer, &settings);
        func_4550F0(image->draw_buffer, 4);

        if (image->centered)
        {
            float half_width = 0.5f * (float)palette_width;
            float half_height = 0.5f * (float)palette_height;
            add_vertex(image->draw_buffer, FieldVec4A(-half_width, -half_height, (float)depth, 1.0f), normal,
                       (((palette_y << 12) / image->palette_height) << 16) | (((palette_x + palette_width) << 12) / image->palette_width), color);
            add_vertex(image->draw_buffer, FieldVec4A(half_width, -half_height, (float)depth, 1.0f), normal,
                       ((palette_x << 12) / image->palette_width) | (((palette_y << 12) / image->palette_height) << 16), color);
            add_vertex(image->draw_buffer, FieldVec4A(-half_width, half_height, (float)depth, 1.0f), normal,
                       (((palette_x + palette_width) << 12) / image->palette_width) | ((((palette_y + palette_height) << 12) / image->palette_height) << 16),
                       color);
            add_vertex(image->draw_buffer, FieldVec4A(half_width, half_height, (float)depth, 1.0f), normal,
                       ((palette_x << 12) / image->palette_width) | ((((palette_y + palette_height) << 12) / image->palette_height) << 16), color);
        }
        else
        {
            add_vertex(image->draw_buffer, FieldVec4A(0.0f, 0.0f, (float)depth, 1.0f), normal,
                       (((palette_y << 12) / image->palette_height) << 16) | (((palette_x + palette_width) << 12) / image->texture_width), color);
            add_vertex(image->draw_buffer, FieldVec4A((float)palette_width, 0.0f, (float)depth, 1.0f), normal,
                       ((palette_x << 12) / image->texture_width) | (((palette_y << 12) / image->texture_height) << 16), color);
            add_vertex(image->draw_buffer, FieldVec4A(0.0f, (float)palette_height, (float)depth, 1.0f), normal,
                       (((palette_x + palette_width) << 12) / image->texture_width) | ((((palette_y + palette_height) << 12) / image->texture_height) << 16),
                       color);
            add_vertex(image->draw_buffer, FieldVec4A((float)palette_width, (float)palette_height, (float)depth, 1.0f), normal,
                       ((palette_x << 12) / image->texture_width) | ((((palette_y + palette_height) << 12) / image->palette_height) << 16), color);
        }
    }

    func_455BD0(image->draw_buffer, image->unk2c, 500.0f, 0);
    func_4D6430(image->unk18, image->draw_buffer);
    image->unk18->unk80 = D_001B6630;
    image->unk18->unk6a |= 0x400;
    D_001B661C->append_node(image->unk18, -1);
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
    BootDrawSettings settings;

    func_455DF0(draw_buffer, 0, 1);
    init_draw_settings(&settings);
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
    unk18 = new (0) BootModel;
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
void BootScreenFade::func_001E0860()
{
    unk60 = 10;
}

/** @brief Run the launch steps: seed, movie, load, hand over. */
void BootGameLauncher::update()
{
    BootSystemSettings* settings;
    BootInput* input = g_boot_program.input;
    settings = (BootSystemSettings*)func_101440(func_101290(func_10D8E0()), 1);
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
            BootSealedRecord* record = &settings->sealed_record;
            func_13A678(record, 0, sizeof(BootSealedRecord));
            seal_record(record);
            BootTrophyFlags* bits = &settings->trophy_flags;
            s32 size = bits->size;

            for (s32 i = 0; i < size; i++)
            {
                bits->flag_bytes[i] = 0;
            }

            bits->trophy_key = resident_next_random_word();
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
            player = new (0) BootMoviePlayer(640, 448);
            resident_exchange_allocation_heap(heap);
            player->state->set_scale(1.0f, 1.0f);
            player->state->set_words(0x800, 0x800, 1);

            if (((BootSystemSettings*)func_101440(func_101290(func_10D8E0()), 1))->widescreen)
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
}
