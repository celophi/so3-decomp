#ifndef SO3_OVERLAYS_LIB_TEXT_004DD440_H
#define SO3_OVERLAYS_LIB_TEXT_004DD440_H

#include "types.h"

typedef struct N50Owner114_004DD440 N50Owner114_004DD440;
typedef struct N50OwnerBC_004DD440 N50OwnerBC_004DD440;
#include "main/resident_0010A0E0.h"
#include "sdk/main/libdma_0012B2C8.h"

#ifdef __cplusplus
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/vector.h"

/** Display state with its virtual pointer after the display data. */
class LibDisplayState
{
public:
    u8 unk00[0x3E6C];

    /** Enable alpha blending in the display drawing commands. */
    u8 blend_enabled;

    u8 unk3e6d[3];

    /** Alpha multiplied by 128 when building display drawing commands. */
    float blend_alpha;

    u8 unk3e74[0x98];

    /** @brief Destroy the display state. */
    virtual ~LibDisplayState();
};

/** Transform that faces an optional target with a roll about the viewing direction. */
class LibLookAtTransform : public LibTransform
{
public:
    /** @brief Initialize the transform without a look-at target or roll. */
    LibLookAtTransform();
    /** @brief Destroy the look-at transform and its transform base. */
    virtual ~LibLookAtTransform();

    /**
     * @brief Copy the look-at target and inherited transform state.
     * @param source Transform to copy; its roll angle is not copied.
     */
    virtual void copy_look_at_state(const LibLookAtTransform* source);

    /** @brief Update the matrix to face the target when one is attached. */
    virtual void update_transform_matrix();

    /** Transform whose position supplies the viewing direction, or null. */
    LibTransform* look_at_target;

    /** Rotation about the viewing direction, passed to the sine/cosine helper. */
    float roll_angle;
};
/** Partial resident context supplying signed viewport dimensions. */
struct LibCameraContext
{
    u8 unk00[0x3C6C];
    s16 viewport_width;
    s16 viewport_height;
};

/** Scene and model-preview camera, with its submission callback interface at 0x220. */
class LibClass179080 : public LibLookAtTransform, public DmaSubmission
{
public:
    /** @brief Initialize the camera from the resident context. @param context Resident context. */
    LibClass179080(void* context);
    /** @brief Release camera resources and its transform base. */
    virtual ~LibClass179080();
    /** @brief Clear the manager camera reference, then detach and queue the transform. */
    virtual void func_003EF740();
    /** @brief Initialize viewport bounds and default projection settings. @param context Resident viewport context. */
    void initialize_projection(const LibCameraContext* context);
    /** @brief Build the local perspective volume for visibility tests. @param volume Destination volume. */
    void build_projection_volume(LibProjectionVolume* volume) const;
    /** @brief Upload the camera's clip geometry into VU0 data memory. */
    void upload_clip_geometry() const;
    /** @brief Update the transform and extract its rotation components. */
    virtual void update_transform_matrix();
    /** @brief Update camera state and its attached-transform distance. */
    virtual void update();
    /** @brief Update the active camera projection state. */
    void func_004E24D0();
    /** @brief Submit the camera's DMA chain. @param channel DMA channel number. */
    virtual void submit_dma(u32 channel);
    /** @brief Complete the camera transfer. @param channel DMA channel number. */
    virtual void complete_dma(u32 channel);
    /** @brief Queue the camera for VIF1 DMA. @return 1 on success, 0 when the queue is full. */
    s32 enqueue_submission();
    /** @brief Copy view and projection state from another camera. @param source Camera source. */
    virtual void copy_camera(const LibClass179080* source);
    /** @brief Copy the camera's view and fog settings. @param source Camera to copy. */
    void copy_view_and_fog(const LibClass179080* source);
    /**
     * @brief Read the configured far and near fog factors.
     * @param far_factor Receives the far fog factor.
     * @param near_factor Receives the near fog factor.
     */
    void get_fog_factors(float* far_factor, float* near_factor) const;
    /**
     * @brief Set the perspective fog mapping coefficients directly.
     * @param offset Constant fog coefficient.
     * @param reciprocal_scale Reciprocal-distance fog coefficient.
     */
    void set_fog_coefficients(float offset, float reciprocal_scale);
    /**
     * @brief Read the perspective fog mapping coefficients.
     * @param offset Receives the constant fog coefficient.
     * @param reciprocal_scale Receives the reciprocal-distance fog coefficient.
     */
    void get_fog_coefficients(float* offset, float* reciprocal_scale) const;
    /** @brief Set the near fog-distance fraction and recompute fog coefficients. @param fraction Fraction of the configured distance range. */
    void set_near_fog_fraction(float fraction);
    /** @brief Set the far fog-distance fraction and recompute fog coefficients. @param fraction Fraction of the configured distance range. */
    void set_far_fog_fraction(float fraction);
    /**
     * @brief Set the fog color, factors and distance range, then recompute the perspective coefficients.
     * @param color Packed RGB fog color.
     * @param far_factor Fog factor at the far distance.
     * @param near_factor Fog factor at the near distance.
     * @param near_distance Near fog distance.
     * @param far_distance Far fog distance.
     */
    void set_fog(u32 color, float far_factor, float near_factor, float near_distance, float far_distance);
    /**
     * @brief Calculate the scaled screen-plane distance from the horizontal field of view.
     * @return Perspective projection distance.
     */
    float compute_projection_distance() const;
private:
    /** @brief Recompute the perspective fog mapping. @param far_factor Far fog factor. @param near_factor Near fog factor. */
    void update_fog_coefficients(float far_factor, float near_factor)
    {
        float distance_span = far_fog_distance - near_fog_distance;
        lib_compute_perspective_fog_coefficients(&fog_offset, &fog_reciprocal_scale, far_factor, near_factor,
                                               near_fog_distance + near_fog_fraction * distance_span,
                                               near_fog_distance + far_fog_fraction * distance_span);
    }
public:
    u8 unk224[0xC];
    DmaSourceTag dma_chain;
    float unk240;
    float unk244;
    u32 unk248;
    float unk24c;
    float unk250;
    float unk254;
    u32 unk258;
    float horizontal_fov;
    float unk260;
    float unk264;
    float unk268;
    float unk26c;
    float unk270;
    float projection_distance;
    float unk278;
    u32 unk27c;
    float unk280;
    float unk284;
    u8 unk288[8];
    FieldVec4B screen_min;
    FieldVec4B screen_max;
    u8 unk2b0[0x118];
    u32 unk3c8;
    u32 unk3cc;
    u8 unk3d0;
    u8 unk3d1;
    u8 unk3d2;
    u8 unk3d3;
    u32 unk3d4;
    u8 unk3d8[0x18];
    FieldVec4A clip_points[10];
    FieldVec4A clip_normals[10];
    u32 fog_color;
    u8 fog_enabled;
    u8 unk535[3];
    float fog_offset;
    float fog_reciprocal_scale;
    float far_fog_fraction;
    float near_fog_fraction;
    float far_fog_distance;
    float near_fog_distance;
    float near_fog_factor;
    float far_fog_factor;
    u8 unk558[8];
    float rotation_angles[3];
    u8 unk56c[0x314];
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** Resident VIF1 DMA queue initialized by the Lib runtime. */
extern ResidentDmaQueue* g_vif1_dma_queue;

struct FieldPacketQueue;

/**
 * @brief Process the render iteration and submit its queued packets.
 * @param object Display state.
 * @param frame Render iteration.
 * @param queue Packet queue to process.
 */
void func_4DD830(void* object, s32 frame, struct FieldPacketQueue* queue);


void func_004E59A0(void* object);
void func_004E5B00(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_004E2E30(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_004E2EF0(void* object);

/**
 * @brief Return the fixed value 16.
 * @param object Receiver or first argument; unused.
 * @return Always 16.
 */
s32 func_004E44E0(void* object);

/** @brief Toggle bit zero of the word at receiver offset 0x14. @param object Receiver containing the word. */
void func_004E44F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_004E6420(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_004E6430(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_004E6440(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_004E6450(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_004E6BB0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_004E6BF0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_004E6C30(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_004E6C70(void* object);

/**
 * @brief Return the fixed value 8.
 * @param object Receiver or first argument; unused.
 * @return Always 8.
 */
s32 func_004E7820(void* object);


/** Return the word at receiver offset 0x4. */
u32 func_004E6680(const void* object);

/** Return the word at receiver offset 0x4. */
u32 func_004E6A80(const void* object);


/** Return the signed halfword at receiver offset 0x48. */
s16 func_004E6400(const void* object);

/** Return the signed halfword at receiver offset 0x4A. */
s16 func_004E6410(const void* object);

/** Return the signed halfword at receiver offset 0x28. */
s16 func_004E6860(const void* object);

/** Return the signed halfword at receiver offset 0x2A. */
s16 func_004E6870(const void* object);


/** Store the byte constant at receiver offset 0x60. */
void func_004E2EE0(void* object);

/** Clear the byte at receiver offset 0xCB. */
void func_004E97A0(void* object);

/** Clear the word at receiver offset 0x114. */
void func_004E13D0(void* object);

/** Return the address of the global at 0x50CD80. */
const void* func_004E0FB0(void);

/** Set the active flag and forward the optional child pointer. */
void func_004E1040(N50Owner114_004DD440* object);
/** Set the active flag and forward the optional child pointer. */
void func_004E2F20(N50OwnerBC_004DD440* object);

#ifdef __cplusplus
/** Return the first pointer argument unchanged. */
void* func_004E6D30(void* value);
/** Return the first pointer argument unchanged. */
void* func_004E6DF0(void* value);

/** Clear four consecutive words at the start of the receiver. */
void func_004E64B0(void* object);

/** Clear four consecutive words at the start of the receiver. */
void func_004E68D0(void* object);

/** Forward the receiver to func_004D00B0. */
void func_004E2F00(void* object);

/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_004E6340(void* object, u8 mode);

/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_004E67A0(void* object, u8 mode);


/** Set the high packed mode at its target field and record whether either mode equals four. */
void func_004E63A0(void* object, u8 mode);

/** Set the high packed mode at its target field and record whether either mode equals four. */
void func_004E6800(void* object, u8 mode);


/** Find a key in the receiver's fixed-size entry array. */
s32 func_004E6460(void* object, float key);

/** Return the key span between the first and last entries. */
float func_004E68F0(void* object);

/** Find a key in the receiver's fixed-size entry array. */
s32 func_004E6880(void* object, float key);

/**
 * @brief Clear the byte at offset 0x64 and run the cleanup helper.
 * @param object Object containing the byte.
 */
void func_004E1020(void* object);

void* func_004E4590(void* object);
void* func_004E4650(void* object);
void* func_004E4710(void* object);
void* func_004E47D0(void* object);
void* func_004E4890(void* object);
void* func_004E4950(void* object);
void* func_004E4A10(void* object);
void* func_004E4AD0(void* object);


}
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** Release the retained display objects and storage. */
void func_004E33B0(void);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/** Transform owner with an intrusive list and DMA notification interface. */
class LibClass178FC0 : public LibClass172000, public LibClass178DD0, public LibClass171FF0
{
public:
    LibClass178FC0();

    virtual ~LibClass178FC0();

    virtual void update();

    virtual void func_003EEBE0();

    virtual const LibVector4* func_003EFAA0();

    virtual void func_003F4440(const void* matrix, void* context);

    virtual void func_003F4410(u32 value);

    void func_004E13D0();

    s32 func_004E10B0(s32 size);

    u8 unk10c[8];

    void* unk114;
};
#endif

#endif
