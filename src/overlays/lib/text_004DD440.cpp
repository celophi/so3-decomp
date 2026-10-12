#include "include_asm.h"
#include "overlays/lib/text_004DD440.h"
#include "overlays/lib/camera_vu0.h"
#include "sdk/main/libm_guess_0013F3E0.h"
#include "vu0.h"

static inline void lib_get_transform_translation(FieldVec4B& result, const LibClass178EA0& object);
static inline float lib_vector_length(const FieldVec4B& vector);

/** @brief Read the matrix translation into a position vector. @param result Destination vector. @param object Transform source. */
static inline void lib_get_transform_translation(FieldVec4B& result, const LibClass178EA0& object)
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E0FB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E0FC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E1020);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E1040);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E1080);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E10B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E1140);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E1280);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E13D0);

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
void LibClass179080::func_004D0090()
{
    FieldClass175290::func_004D0090();
    func_004CEBA0(rotation_angles, func_004D00A0());
}

/** @brief Update camera state and its attached-transform distance. */
void LibClass179080::func_003EEBD0()
{
    unk63 = 0;
    LibClass178EA0::func_003EEBD0();
    unk50 = 1;
    if (static_cast<LibClass178F30*>(owner)->current_display == this)
    {
        func_004E24D0();
    }
    if (unk210 != 0 && unk3d3 != 0)
    {
        FieldVec4B attached_position;
        FieldVec4B difference;
        lib_get_transform_translation(attached_position, *unk210);
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
    unk210 = source->unk210;
    LibClass178EA0::func_004D9F40(source);
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E2EE0);

s32 func_004E2EF0(void* object)
{
    return 3;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E2F00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E2F20);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E44F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4500);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4590);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E45C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4650);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4680);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4710);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4740);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E47D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4800);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4890);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E48C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4950);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4980);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4A10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4A40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4AD0);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E59A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E59D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5A30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5AA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5B00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5B30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5C10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5C80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5D30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5DA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5E10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5E80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5F60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5FA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5FC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6040);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E60B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E60D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6170);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6200);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6280);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E62F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6340);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E63A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6400);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6410);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6460);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E64B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E64D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6520);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6590);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E65E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6680);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6690);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E66E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6750);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E67A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6800);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6860);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6870);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6880);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E68D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E68F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6940);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E69A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E69F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6A80);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6D30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6D40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6DF0);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E97A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E97B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E9940);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E9BC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E9CD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E9F70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E9FE0);
