#include "include_asm.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/lib/text_004DD440.h"
#include "overlays/lib/camera_vu0.h"
#include "sdk/main/libm_guess_0013F3E0.h"
#include "vu0.h"

extern "C" void func_004D00B0(void* object);
extern "C" void* D_001B6674;
extern "C" void resident_packet_submit(void* owner, void* object);
extern "C" void* D_001B6668;
extern "C" void func_004E6690(void* object);
extern "C" void func_004E6B30(void* owner, void* object);
extern "C" void func_004E6A90(void* object);
extern "C" void func_004E6AE0(void* owner, void* object);

extern "C" u8 D_00179270[];
extern "C" u8 D_00179260[];
extern "C" u8 D_00179250[];
extern "C" u8 D_00179240[];
extern "C" u8 D_00179230[];
extern "C" u8 D_00179220[];
extern "C" u8 D_00179210[];
extern "C" u8 D_00179200[];
extern "C" u8 D_00173F58[];

typedef struct FieldArgumentInitializerState
{
    u32 unk00;
    u8 pad04[4];
    u32 unk08;
    u8 pad0c[8];
    u32 unk14;
    u8 unk18;
    u8 pad19[3];
    u32 unk1c;
    u32 unk20;
} FieldArgumentInitializerState;

#define DEFINE_FIELD_ARGUMENT_INITIALIZER(name, first_global) \
    void* name(void* object) \
    { \
        FieldArgumentInitializerState* state = (FieldArgumentInitializerState*)object; \
        state->unk20 = (u32)first_global; \
        state->unk1c = (u32)D_00173F58; \
        state->unk14 = 0; \
        state->unk18 = 0; \
        state->unk08 = 0; \
        state->unk00 = 0; \
        return object; \
    }

typedef struct ConstantByteSetterOwnertext_004DD440
{
    u8 unk00[0x60];
    u8 unk60;
} ConstantByteSetterOwnertext_004DD440;

typedef struct ByteClearOwnertext_004DD440
{
    u8 unk00[0xCB];
    u8 unkcb;
} ByteClearOwnertext_004DD440;

typedef struct ByteClear64Ownertext_004DD440
{
    u8 unk00[0x64];
    u8 unk64;
} ByteClear64Ownertext_004DD440;

typedef struct WordClearOwnertext_004DD440
{
    u8 unk00[0x114];
    u32 unk114;
} WordClearOwnertext_004DD440;

extern "C" u8 D_50CD80[];



typedef struct HalfwordGetterOwnertext_004DD440
{
    u8 unk00[0x28];
    s16 unk28;
    s16 unk2a;
    u8 unk2c[0x1C];
    s16 unk48;
    s16 unk4a;
} HalfwordGetterOwnertext_004DD440;



typedef struct WordGetterOwnertext_004DD440
{
    u8 unk00[0x4];
    u32 unk04;
} WordGetterOwnertext_004DD440;


static inline void lib_get_transform_translation(FieldVec4B& result, const LibTransform& object);
static inline float lib_vector_length(const FieldVec4B& vector);

/** @brief Read the matrix translation into a position vector. @param result Destination vector. @param object Transform source. */
static inline void lib_get_transform_translation(FieldVec4B& result, const LibTransform& object)
{
    result.x = object.transform.m[0][3];
    result.y = object.transform.m[1][3];
    result.z = object.transform.m[2][3];
    result.w = 1.0f;
}

/** @brief Compute the xyz vector length. @param vector Vector to measure. @return Vector length. */
static inline float lib_vector_length(const FieldVec4B& vector)
{
    FieldVec4A result;
    vu0_length_xyz(&result, &vector);
    return result.x;
}

typedef struct FourWordClearOwnertext_004DD440 { u32 words[4]; } FourWordClearOwnertext_004DD440;

typedef struct PackedModePair
{
    u8 lowMode : 4;
    u8 highMode : 4;
    u8 hasModeFour : 1;
    u8 unk01_1_7 : 7;
} PackedModePair;

typedef struct PackedModesOwner
{
    u8 unk00[0x32];
    PackedModePair at32;
    u8 unk34[0x1E];
    PackedModePair at52;
} PackedModesOwner;

typedef struct FloatKeyScanEntry_text_004DD440_10
{
    float key00;
    u8 unk04[0x8];
    float key0c;
} FloatKeyScanEntry_text_004DD440_10;

typedef struct FloatKeyScanOwner_text_004DD440_10
{
    u8 unk00[0x4];
    FloatKeyScanEntry_text_004DD440_10* entries;
    u8 unk08[0x20];
    s16 count28;
    u8 unk2a[0x1E];
    s16 count48;
} FloatKeyScanOwner_text_004DD440_10;

typedef struct FloatKeyScanEntry_text_004DD440_30
{
    float key00;
    u8 unk04[0x8];
    float key0c;
    u8 unk10[0x20];
} FloatKeyScanEntry_text_004DD440_30;

typedef struct FloatKeyScanOwner_text_004DD440_30
{
    u8 unk00[0x4];
    FloatKeyScanEntry_text_004DD440_30* entries;
    u8 unk08[0x20];
    s16 count28;
    u8 unk2a[0x1E];
    s16 count48;
} FloatKeyScanOwner_text_004DD440_30;

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004DD440);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004DD520);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004DD830);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004DE010);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004DE1E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004DE250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004DE270);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004DE500);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004DEA70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004DF270);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004DF6E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004DF890);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E02C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E03C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E09B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E0BC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E0D20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E0E60);

const void* func_004E0FB0(void)
{
    return D_50CD80;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E0FC0);

extern "C" void func_004E1020(void* object)
{
    ((ByteClear64Ownertext_004DD440*)object)->unk64 = 0;
    func_004D00B0(object);
}

struct N50Owner114_004DD440 { u8 pad00[0x64]; u8 active; u8 pad65[0xAF]; void* owner; };

void func_004E1040(N50Owner114_004DD440* object)
{
    object->active = 1;
    void* adjusted = object;
    if (object != 0)
    {
        adjusted = (u8*)adjusted + 0x108;
    }
    resident_packet_submit(object->owner, adjusted);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E1080);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E10B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E1140);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E1280);

extern "C" void func_004E13D0(void* object)
{
    WordClearOwnertext_004DD440* receiver = static_cast<WordClearOwnertext_004DD440*>(object);
    receiver->unk114 = 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E13E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E1450);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E1460);

/** @brief Clear the manager camera reference, then detach and queue the transform. */
void LibClass179080::func_003EF740()
{
    LibClass178F30* manager = static_cast<LibClass178F30*>(owner);
    if (manager != 0 && manager->current_display == this)
    {
        manager->current_display = 0;
    }
    LibClass178A90::func_003EF740();
}

/** @brief Initialize viewport bounds and default projection settings. @param context Resident viewport context. */
void LibClass179080::initialize_projection(const LibCameraContext* context)
{
    horizontal_fov = 0.7853982f;
    s32 half_height = context->viewport_height / 2;
    s32 half_width = context->viewport_width / 2;
    screen_min.x = 2048 - half_width;
    screen_min.y = 2048 - half_height;
    screen_min.z = 100.0f;
    screen_min.w = 1.0f;
    screen_max.x = 2048 + half_width;
    screen_max.y = 2048 + half_height;
    screen_max.z = 16770000.0f;
    screen_max.w = 1.0f;
    unk3c8 = 10;
    unk3cc = 16770000;
    unk3d2 = 1;
    unk280 = 2048.0f;
    unk284 = 2048.0f;
    unk278 = (1.3333334f * (1.0714285f * context->viewport_height)) / context->viewport_width;
    unk250 = 1.0f;
    unk270 = 1.0f;
}

/** @brief Upload the camera's clip geometry into VU0 data memory. */
void LibClass179080::upload_clip_geometry() const
{
    vu0_upload_clip_geometry(clip_points, clip_normals);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E1670);

/** @brief Build the local perspective volume for visibility tests. @param volume Destination volume. */
void LibClass179080::build_projection_volume(LibProjectionVolume* volume) const
{
    FieldVec4A transverse_axis;
    FieldVec4A depth_axis;
    volume->origin = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    transverse_axis.x = -1.0f;
    transverse_axis.y = 0.0f;
    transverse_axis.z = 0.0f;
    transverse_axis.w = 1.0f;
    volume->near_half_width = (screen_min.z * (0.5f * (screen_max.x - screen_min.x))) / projection_distance;
    volume->x_axis = transverse_axis;
    float inverse_aspect = 1.0f / unk278;
    transverse_axis.x = 0.0f;
    transverse_axis.y = -1.0f;
    transverse_axis.z = 0.0f;
    transverse_axis.w = 1.0f;
    volume->near_half_height = (screen_min.z * (inverse_aspect * (0.5f * (screen_max.y - screen_min.y)))) /
                             projection_distance;
    volume->y_axis = transverse_axis;
    depth_axis.x = 0.0f;
    depth_axis.y = 0.0f;
    depth_axis.z = 1.0f;
    depth_axis.w = 1.0f;
    volume->z_axis = depth_axis;
    volume->near_distance = screen_min.z;
    volume->far_distance = screen_max.z;
    volume->update_coefficients();
}

/**
 * @brief Read the configured far and near fog factors.
 * @param far_factor Receives the far fog factor.
 * @param near_factor Receives the near fog factor.
 */
void LibClass179080::get_fog_factors(float* far_factor, float* near_factor) const
{
    *far_factor = far_fog_factor;
    *near_factor = near_fog_factor;
}

/** @brief Update the transform and extract its rotation components. */
void LibClass179080::update_transform_matrix()
{
    LibLookAtTransform::update_transform_matrix();
    func_004CEBA0(rotation_angles, get_transform_matrix());
}

/** @brief Update camera state and its attached-transform distance. */
void LibClass179080::update()
{
    unk63 = 0;
    LibTransform::update();
    transform_dirty = 1;
    if (static_cast<LibClass178F30*>(owner)->current_display == this)
    {
        func_004E24D0();
    }
    if (look_at_target != 0 && unk3d3 != 0)
    {
        FieldVec4B attached_position;
        FieldVec4B difference;
        lib_get_transform_translation(attached_position, *look_at_target);
        lib_get_transform_translation(difference, *this);
        difference -= attached_position;
        unk244 = lib_vector_length(difference);
    }
}

/**
 * @brief Set the perspective fog mapping coefficients directly.
 * @param offset Constant fog coefficient.
 * @param reciprocal_scale Reciprocal-distance fog coefficient.
 */
void LibClass179080::set_fog_coefficients(float offset, float reciprocal_scale)
{
    fog_offset = offset;
    fog_reciprocal_scale = reciprocal_scale;
}

/**
 * @brief Read the perspective fog mapping coefficients.
 * @param offset Receives the constant fog coefficient.
 * @param reciprocal_scale Receives the reciprocal-distance fog coefficient.
 */
void LibClass179080::get_fog_coefficients(float* offset, float* reciprocal_scale) const
{
    *offset = fog_offset;
    *reciprocal_scale = fog_reciprocal_scale;
}

/** @brief Set the near fog-distance fraction and recompute fog coefficients. @param fraction Fraction of the configured distance range. */
void LibClass179080::set_near_fog_fraction(float fraction)
{
    near_fog_fraction = fraction;
    update_fog_coefficients(far_fog_factor, near_fog_factor);
}

/** @brief Set the far fog-distance fraction and recompute fog coefficients. @param fraction Fraction of the configured distance range. */
void LibClass179080::set_far_fog_fraction(float fraction)
{
    far_fog_fraction = fraction;
    update_fog_coefficients(far_fog_factor, near_fog_factor);
}

/**
 * @brief Set the fog color, factors and distance range, then recompute the perspective coefficients.
 * @param color Packed RGB fog color.
 * @param far_factor Fog factor at the far distance.
 * @param near_factor Fog factor at the near distance.
 * @param near_distance Near fog distance.
 * @param far_distance Far fog distance.
 */
void LibClass179080::set_fog(u32 color, float far_factor, float near_factor, float near_distance, float far_distance)
{
    fog_color = color;
    far_fog_factor = far_factor;
    near_fog_factor = near_factor;
    far_fog_distance = far_distance;
    near_fog_distance = near_distance;
    update_fog_coefficients(far_factor, near_factor);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E1E70);

/** @brief Copy camera settings, the attached transform and inherited transform state. @param source Camera to copy. */
void LibClass179080::copy_camera(const LibClass179080* source)
{
    copy_view_and_fog(source);
    look_at_target = source->look_at_target;
    LibTransform::copy_transform_state(source);
}

/** @brief Copy the camera's view and fog settings. @param source Camera to copy. */
void LibClass179080::copy_view_and_fog(const LibClass179080* source)
{
    unk3c8 = source->unk3c8;
    unk3cc = source->unk3cc;
    unk278 = source->unk278;
    screen_min = source->screen_min;
    screen_max = source->screen_max;
    unk280 = source->unk280;
    unk284 = source->unk284;
    unk3d2 = source->unk3d2;
    unk250 = source->unk250;
    unk254 = source->unk254;
    unk270 = source->unk270;
    unk3d1 = source->unk3d1;
    horizontal_fov = source->horizontal_fov;
    unk3d3 = source->unk3d3;
    unk244 = source->unk244;
    unk24c = source->unk24c;
    unk3d0 = source->unk3d0;
    unk3d4 = source->unk3d4;
    unk260 = source->unk260;
    unk264 = source->unk264;
    unk268 = source->unk268;
    unk26c = source->unk26c;
    fog_color = source->fog_color;
    float near_factor = source->near_fog_factor;
    float far_factor = source->far_fog_factor;
    far_fog_factor = far_factor;
    near_fog_factor = near_factor;
    near_fog_distance = source->near_fog_distance;
    far_fog_distance = source->far_fog_distance;
    near_fog_fraction = source->near_fog_fraction;
    update_fog_coefficients(far_fog_factor, near_fog_factor);
    far_fog_fraction = source->far_fog_fraction;
    update_fog_coefficients(far_fog_factor, near_fog_factor);
    fog_enabled = source->fog_enabled;
}

/** @brief Submit the camera's DMA chain. @param channel DMA channel number. */
void LibClass179080::submit_dma(u32 channel)
{
    DmaChannel* dma = sceDmaGetChan(channel);
    dma->chcr.tag_transfer_enable = 0;
    sceDmaSend(dma, &dma_chain);
}

/** @brief Complete the camera transfer. @param channel DMA channel number; unused. */
void LibClass179080::complete_dma(u32 channel)
{
}

/** @brief Queue the camera for VIF1 DMA. @return 1 on success, 0 when the queue is full. */
s32 LibClass179080::enqueue_submission()
{
    return func_00114100(g_vif1_dma_queue, this);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E2120);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E22B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E24D0__14LibClass179080Fv);

/**
 * @brief Calculate the scaled screen-plane distance from the horizontal field of view.
 * @return Perspective projection distance.
 */
float LibClass179080::compute_projection_distance() const
{
    float half_width = (unk254 * unk250) * (screen_max.x - screen_min.x) / 2.0f;
    return half_width / func_00141EC0(horizontal_fov / 2.0f);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E2940);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E29E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E2DE0);

void func_004E2E30(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E2E40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E2EC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E2ED0);

/** Store 0xA at receiver offset 0x60. */
void func_004E2EE0(void* object)
{
    ConstantByteSetterOwnertext_004DD440* receiver = static_cast<ConstantByteSetterOwnertext_004DD440*>(object);
    receiver->unk60 = 0xA;
}

s32 func_004E2EF0(void* object)
{
    return 3;
}

/** Forward the receiver to func_004D00B0. */
void func_004E2F00(void* object)
{
    func_004D00B0(object);
}

struct N50OwnerBC_004DD440 { u8 pad00[0x64]; u8 active; u8 pad65[0x57]; void* owner; };

void func_004E2F20(N50OwnerBC_004DD440* object)
{
    object->active = 1;
    void* adjusted = object;
    if (object != 0)
    {
        adjusted = (u8*)adjusted + 0x90;
    }
    resident_packet_submit(object->owner, adjusted);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E2F60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E3020);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E31D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E32F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E33A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E33B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E3830);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4450);

s32 func_004E44E0(void* object)
{
    return 16;
}

typedef struct LibToggleWord14
{
    u8 unk00[0x14];
    u32 unk14;
} LibToggleWord14;

/** Toggle bit zero of the word at receiver offset 0x14. */
void func_004E44F0(void* object)
{
    LibToggleWord14* receiver = (LibToggleWord14*)object;
    receiver->unk14 ^= 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4500);

DEFINE_FIELD_ARGUMENT_INITIALIZER(func_004E4590, D_00179270)

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E45C0);

DEFINE_FIELD_ARGUMENT_INITIALIZER(func_004E4650, D_00179260)

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4680);

DEFINE_FIELD_ARGUMENT_INITIALIZER(func_004E4710, D_00179250)

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4740);

DEFINE_FIELD_ARGUMENT_INITIALIZER(func_004E47D0, D_00179240)

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4800);

DEFINE_FIELD_ARGUMENT_INITIALIZER(func_004E4890, D_00179230)

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E48C0);

DEFINE_FIELD_ARGUMENT_INITIALIZER(func_004E4950, D_00179220)

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4980);

DEFINE_FIELD_ARGUMENT_INITIALIZER(func_004E4A10, D_00179210)

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4A40);

DEFINE_FIELD_ARGUMENT_INITIALIZER(func_004E4AD0, D_00179200)

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4B00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4CA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4E40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4EC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5060);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5200);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E53A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5410);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E55A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5740);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E58E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5940);

void func_004E59A0(void* object)
{
    func_004E6690(object);
    func_004E6B30(D_001B6674, object);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E59D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5A30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5AA0);

void func_004E5B00(void* object)
{
    func_004E6A90(object);
    func_004E6AE0(D_001B6668, object);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5B30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5C10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5C80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5D30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5DA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5E10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5E80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5F60);

extern "C" void func_004E5FA0(const void* object, FieldVec4B* output)
{
    *output = *(const FieldVec4A*)((const u8*)object + 0xC0);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5FC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6040);

extern "C" void func_004E60B0(const void* object, FieldVec4B* output)
{
    *output = *(const FieldVec4A*)((const u8*)object + 0xA0);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E60D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6170);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6200);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6280);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E62F0);

/** Set the low packed mode at 0x52 and record whether either mode equals four. */
void func_004E6340(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at52.lowMode = mode;
    receiver->at52.hasModeFour = receiver->at52.lowMode == 4 || receiver->at52.highMode == 4;
}

/** Set the high packed mode at 0x52 and record whether either mode equals four. */
void func_004E63A0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at52.highMode = mode;
    receiver->at52.hasModeFour = receiver->at52.lowMode == 4 || receiver->at52.highMode == 4;
}

/** Return the signed halfword at receiver offset 0x48. */
s16 func_004E6400(const void* object)
{
    const HalfwordGetterOwnertext_004DD440* receiver = static_cast<const HalfwordGetterOwnertext_004DD440*>(object);
    return receiver->unk48;
}

/** Return the signed halfword at receiver offset 0x4A. */
s16 func_004E6410(const void* object)
{
    const HalfwordGetterOwnertext_004DD440* receiver = static_cast<const HalfwordGetterOwnertext_004DD440*>(object);
    return receiver->unk4a;
}

s32 func_004E6420(void* object)
{
    return 0;
}

s32 func_004E6430(void* object)
{
    return 0;
}

s32 func_004E6440(void* object)
{
    return 0;
}

void func_004E6450(void* object)
{
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_004E6460(void* object, float key)
{
    FloatKeyScanOwner_text_004DD440_30* receiver = static_cast<FloatKeyScanOwner_text_004DD440_30*>(object);
    s16 count = receiver->count48;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == receiver->entries[index].key0c)
        {
            return 1;
        }
    }
    return 0;
}

void func_004E64B0(void* object)
{
    FourWordClearOwnertext_004DD440* receiver = (FourWordClearOwnertext_004DD440*)object;
    receiver->words[0] = 0;
    receiver->words[1] = 0;
    receiver->words[2] = 0;
    receiver->words[3] = 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E64D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6520);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6590);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E65E0);

/** Return the word at receiver offset 0x4. */
u32 func_004E6680(const void* object)
{
    const WordGetterOwnertext_004DD440* receiver = static_cast<const WordGetterOwnertext_004DD440*>(object);
    return receiver->unk04;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6690);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E66E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6750);

/** Set the low packed mode at 0x32 and record whether either mode equals four. */
void func_004E67A0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at32.lowMode = mode;
    receiver->at32.hasModeFour = receiver->at32.lowMode == 4 || receiver->at32.highMode == 4;
}

/** Set the high packed mode at 0x32 and record whether either mode equals four. */
void func_004E6800(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at32.highMode = mode;
    receiver->at32.hasModeFour = receiver->at32.lowMode == 4 || receiver->at32.highMode == 4;
}

/** Return the signed halfword at receiver offset 0x28. */
s16 func_004E6860(const void* object)
{
    const HalfwordGetterOwnertext_004DD440* receiver = static_cast<const HalfwordGetterOwnertext_004DD440*>(object);
    return receiver->unk28;
}

/** Return the signed halfword at receiver offset 0x2A. */
s16 func_004E6870(const void* object)
{
    const HalfwordGetterOwnertext_004DD440* receiver = static_cast<const HalfwordGetterOwnertext_004DD440*>(object);
    return receiver->unk2a;
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_004E6880(void* object, float key)
{
    FloatKeyScanOwner_text_004DD440_10* receiver = static_cast<FloatKeyScanOwner_text_004DD440_10*>(object);
    s16 count = receiver->count28;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == receiver->entries[index].key0c)
        {
            return 1;
        }
    }
    return 0;
}

void func_004E68D0(void* object)
{
    FourWordClearOwnertext_004DD440* receiver = (FourWordClearOwnertext_004DD440*)object;
    receiver->words[0] = 0;
    receiver->words[1] = 0;
    receiver->words[2] = 0;
    receiver->words[3] = 0;
}

/** Return the key span between the first and last entries. */
float func_004E68F0(void* object)
{
    const FloatKeyScanOwner_text_004DD440_10* receiver = static_cast<const FloatKeyScanOwner_text_004DD440_10*>(object);
    s32 count = receiver->count28;
    if (count < 2)
    {
        return 0.0f;
    }
    const FloatKeyScanEntry_text_004DD440_10* entries = receiver->entries;
    const FloatKeyScanEntry_text_004DD440_10* lastEntry = entries + --count;
    float first = entries[0].key0c;
    float last = lastEntry->key0c;
    return last - first;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6940);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E69A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E69F0);

/** Return the word at receiver offset 0x4. */
u32 func_004E6A80(const void* object)
{
    const WordGetterOwnertext_004DD440* receiver = static_cast<const WordGetterOwnertext_004DD440*>(object);
    return receiver->unk04;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6A90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6AE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6B30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6B80);

void func_004E6BB0(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6BC0);

s32 func_004E6BF0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6C00);

s32 func_004E6C30(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6C40);

s32 func_004E6C70(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6C80);

void* func_004E6D30(void* value)
{
    return value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6D40);

void* func_004E6DF0(void* value)
{
    return value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6E00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6E60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6F60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6FC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E7050);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E7190);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E71C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E71F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E7220);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E7250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E7770);

s32 func_004E7820(void* object)
{
    return 8;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E7830);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E7AA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E8510);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E9260);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E9290);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E95C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E96A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E96B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E96C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E96D0);

extern "C" void lib_factor_tooltip_hide(void* object)
{
    ByteClearOwnertext_004DD440* receiver = static_cast<ByteClearOwnertext_004DD440*>(object);
    receiver->unkcb = 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", lib_factor_tooltip_show);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E9940);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", lib_factor_tooltip_init);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E9CD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E9F70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E9FE0);
