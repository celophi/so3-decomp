#ifndef SO3_OVERLAYS_LIB_TEXT_004CD3A0_H
#define SO3_OVERLAYS_LIB_TEXT_004CD3A0_H

#include "types.h"
#include "main/dma_queue.h"
#include "gs.h"
#include "ee.h"
#include "main/microcode_loader.h"
#include "overlays/lib/text_003E68C0.h"
#include "overlays/lib/counted_list.h"
#include "overlays/lib/render_channel.h"
#include "overlays/lib/vector.h"
#include "overlays/lib/image_header.h"
#include "main/main.h"
#include "sdk/main/libgraph_0012EAC8.h"

/** Partial object with a busy flag that something else clears; the rest is unknown. */
typedef struct LibBusyObject
{
    u8 unk00[0x50];
    volatile u8 busy;
    u8 channel;
} LibBusyObject;

/** Partial list node; the leading bytes and full object extent are unknown. */
typedef struct LibListNode
{
    u8 unk00[8];
    struct LibListNode* next;
    s16 unk0c;
} LibListNode;

#ifdef __cplusplus

#define LIB_VU1_PROGRAM_COUNT 11

/** Data of each VU1 microprogram, for LibMicrocodeLoader::select_program. */
extern "C" const void* const lib_vu1_programs[LIB_VU1_PROGRAM_COUNT];

/** DMA chain that uploads Lib's resident VU1 microcode. */
extern "C" u8 lib_vu1_upload_chain[];

/** Aligned four-row matrix whose assignment returns a copy of the matrix. */
class LibMatrix44Value
{
public:
    LibMatrix44Value()
    {
    }

    /** @brief Set the matrix to the identity transformation. */
    void set_identity();

    /**
     * @brief Copy all sixteen components.
     * @param other Matrix to copy.
     */
    LibMatrix44Value(const LibMatrix44Value& other)
    {
        ((unsigned __int128*)this)[0] = ((const unsigned __int128*)&other)[0];
        ((unsigned __int128*)this)[1] = ((const unsigned __int128*)&other)[1];
        ((unsigned __int128*)this)[2] = ((const unsigned __int128*)&other)[2];
        ((unsigned __int128*)this)[3] = ((const unsigned __int128*)&other)[3];
    }

    /**
     * @brief Copy all components.
     * @param other Source matrix.
     * @return A copy of this matrix.
     */
    LibMatrix44Value operator=(const LibMatrix44Value& other)
    {
        ((unsigned __int128*)this)[0] = ((const unsigned __int128*)&other)[0];
        ((unsigned __int128*)this)[1] = ((const unsigned __int128*)&other)[1];
        ((unsigned __int128*)this)[2] = ((const unsigned __int128*)&other)[2];
        ((unsigned __int128*)this)[3] = ((const unsigned __int128*)&other)[3];
        return *this;
    }

    float m[4][4];
} __attribute__((aligned(16)));

class LibModel;

extern "C"
{
    /**
     * @brief Find the model's render-data record for an index and report its image's two keys.
     * @param model Model whose mesh holds the records.
     * @param index Record index.
     * @param first_key Receives the image's first key.
     * @param second_key Receives the image's second key.
     */
    void func_004D5E10(LibModel* model, s32 index, u32* first_key, u32* second_key);

    /**
     * @brief Normalize the first three floating-point components in place.
     * @param value At least three components with nonzero squared length.
     */
    void lib_normalize_vector3(float* value);

    /**
     * @brief Normalize four floating-point components in place, leaving a zero vector unchanged.
     * @param value Four components, such as a quaternion.
     */
    void func_004CF640(float* value);

    /**
     * @brief Convert a quaternion by mapping each matrix row from (x, y, z) to (x, -z, y).
     * @param quaternion Source quaternion.
     * @return Quaternion extracted from the converted matrix.
     */
    FieldVec4B func_004CD570(const FieldVec4B& quaternion);

    /**
     * @brief Invert an orthonormal rotation and its row-vector translation.
     * @param input Source matrix.
     * @param output Destination matrix, distinct from input.
     */
    void func_004CEF20(const LibMatrix44Value* input, LibMatrix44Value* output);

    /**
     * @brief Invert an orthonormal rotation and its translation column.
     * @param input Source transformation matrix.
     * @return Inverse transformation matrix.
     */
    LibMatrix44Value func_004CF0B0(const LibMatrix44Value& input);

    /**
     * @brief Invert a nonsingular matrix.
     * @param input Source matrix.
     * @param output Destination matrix, which may alias input.
     */
    void func_004CF1C0(const LibMatrix44Value* input, LibMatrix44Value* output);

    /**
     * @brief Multiply a matrix by a column vector.
     * @param matrix Source matrix.
     * @param value Source vector.
     * @return Transformed vector.
     */
    FieldVec4A func_004CF6C0(const LibMatrix44Value& matrix, const FieldVec4A& value);

    /**
     * @brief Combine two matrices with the VU0 microprogram at 0x250.
     * @param left First matrix (vf1-vf4).
     * @param right Second matrix (vf5-vf8).
     * @return Combined matrix.
     */
    LibMatrix44Value func_004CF7C0(const LibMatrix44Value& left, const LibMatrix44Value& right);

    /**
     * @brief Run a matrix through the VU0 microprogram at 0x2D0.
     * @param input Source matrix (vf1-vf4).
     * @return Result matrix.
     */
    LibMatrix44Value func_004CF580(const LibMatrix44Value& input);

    /**
     * @brief Multiply a row vector by a matrix.
     * @param value Source vector.
     * @param matrix Source matrix.
     * @return Transformed vector.
     */
    FieldVec4A func_004CF830(const FieldVec4B& value, const LibMatrix44Value& matrix);

    /**
     * @brief Compose a projection that exchanges depth and homogeneous coordinates with an inverse transform.
     * @param output Destination matrix.
     * @param input Orthonormal source transformation.
     * @param scale Projection scale, halved before division.
     * @param x_divisor Divisor for the horizontal scale.
     * @param y_divisor Divisor for the vertical scale.
     * @param x_offset Horizontal projection offset.
     * @param y_offset Vertical projection offset.
     */
    void func_004CFB20(LibMatrix44Value* output, const LibMatrix44Value& input, float scale, float x_divisor, float y_divisor, float x_offset, float y_offset);

    /**
     * @brief Compose a projection with third-column offsets with an inverse transform.
     * @param output Destination matrix.
     * @param input Orthonormal source transformation.
     * @param scale Projection scale, halved before division.
     * @param x_divisor Divisor for the horizontal scale.
     * @param y_divisor Divisor for the vertical scale.
     * @param x_offset Horizontal projection offset.
     * @param y_offset Vertical projection offset.
     */
    void func_004CFC50(LibMatrix44Value* output, const LibMatrix44Value& input, float scale, float x_divisor, float y_divisor, float x_offset, float y_offset);

    /**
     * @brief Build a perspective matrix with depth-range coefficients.
     * @param output Destination matrix.
     * @param x_scale Horizontal projection scale.
     * @param y_scale_factor Multiplier for the vertical projection scale.
     * @param x_offset Horizontal projection offset.
     * @param y_offset Vertical projection offset.
     * @param first_depth First depth-range coefficient.
     * @param second_depth Second depth-range coefficient.
     * @param near_plane Near clipping distance.
     * @param far_plane Far clipping distance.
     */
    void func_004CFD80(LibMatrix44Value* output, float x_scale, float y_scale_factor, float x_offset, float y_offset,
                      float first_depth, float second_depth, float near_plane, float far_plane);

    /**
     * @brief Set the upper 3x3 rotation from three angles.
     * @param output Matrix whose rotation is updated.
     * @param angles Three rotation angles in radians.
     */
    void func_004CFDE0(LibMatrix44Value* output, const float* angles);

    /**
     * @brief Set the upper 3x3 rotation about the Y axis.
     * @param output Matrix whose rotation is updated.
     * @param angle Rotation angle in radians.
     */
    void func_004CFEE0(LibMatrix44Value* output, float angle);

    /**
     * @brief Clear all sixteen matrix components.
     * @param matrix Matrix to clear.
     */
    void func_004CFF80(LibMatrix44Value* matrix);

    /**
     * @brief Extract three rotation components from a matrix.
     * @param angles Destination for three floats.
     * @param matrix Transformation matrix.
     */
    void func_004CEBA0(float* angles, const LibMatrix44Value* matrix);

    /**
     * @brief Extract rotation angles from a quaternion, through its rotation matrix.
     * @param angles Receives the angles about x, y and z.
     * @param quaternion Source quaternion.
     */
    void func_004CD8C0(LibVector4* angles, const LibVector4* quaternion);

    /**
     * @brief Extract rotation components from a quaternion.
     * @param angles Destination rotation vector.
     * @param quaternion Source quaternion.
     */
    void func_004CDA40(LibVector4* angles, const LibVector4* quaternion);

    /**
     * @brief Normalize a quaternion in place.
     * @param quaternion Quaternion to normalize.
     */
    void lib_normalize_quaternion(FieldVec4B* quaternion);

    /**
     * @brief Build the unit quaternion for a rotation about an axis.
     * @param output Receives the quaternion.
     * @param axis_angle Axis in x, y and z, angle in radians in w.
     */
    void lib_quaternion_from_axis_angle(FieldVec4B* output, const LibVector4* axis_angle);

    /**
     * @brief Convert a quaternion to a matrix.
     * @param quaternion Rotation to convert.
     * @return Rotation matrix.
     */
    LibMatrix44Value func_004CE930(const FieldVec4B& quaternion);

    /**
     * @brief Build a matrix from quaternion products, retaining the quaternion's squared norm.
     * @param quaternion Quaternion components in x, y, z, w order.
     * @return Row-vector rotation matrix with the squared norm in its homogeneous diagonal.
     */
    LibMatrix44Value func_004CE980(const FieldVec4B& quaternion);

    /**
     * @brief Build a rotation quaternion from three angles.
     * @param output Destination quaternion.
     * @param angles Angles in radians in x, y and z.
     */
    void func_004CE040(LibVector4* output, const LibVector4* angles);

    /**
     * @brief Transpose a matrix.
     * @param input Source matrix.
     * @return Transposed matrix.
     */
    LibMatrix44Value func_004CECD0(const LibMatrix44Value& input);

    /**
     * @brief Invert a rigid transform.
     * @param input Source transform, or null for the identity.
     * @param output Destination matrix.
     */
    void func_004CEFD0(const LibMatrix44Value* input, LibMatrix44Value* output);

    /**
     * @brief Build a matrix from a camera's screen bounds.
     * @param output Destination matrix.
     * @param min Screen minimum corner.
     * @param max Screen maximum corner.
     * @param distance Projection distance.
     * @param aspect Aspect factor.
     */
    void func_004CF930(LibMatrix44Value* output, const FieldVec4A* min, const FieldVec4A* max, float distance, float aspect);

    /**
     * @brief Build a clip matrix from a camera's screen bounds and depth range.
     * @param output Destination matrix.
     * @param min Screen minimum corner.
     * @param max Screen maximum corner.
     * @param distance Projection distance.
     * @param aspect Aspect factor.
     * @param x_offset Horizontal projection offset.
     * @param y_offset Vertical projection offset.
     * @param first_depth First depth-range coefficient.
     * @param second_depth Second depth-range coefficient.
     */
    void func_004CFA30(LibMatrix44Value* output, const FieldVec4A* min, const FieldVec4A* max, float distance, float aspect,
                       float x_offset, float y_offset, float first_depth, float second_depth);
}

class LibDisplayManager;
class LibCameraContext;

#define LIB_TEXTURE_CACHE_ENTRY_COUNT 256
#define LIB_TEXTURE_CACHE_MAX_CLUTS 64

/** Partial object that owns a cached texture. */
struct LibTextureUser
{
    u8 unk00[0x2C];
    s32 priority;
};

/** States of a LibTextureBlock. */
enum LibTextureBlockState
{
    /** Free VRAM in the texture area. */
    LIB_TEXTURE_BLOCK_FREE = 0,

    /** Holds a cached texture. */
    LIB_TEXTURE_BLOCK_USED = 1,

    /** Record not in the block list. */
    LIB_TEXTURE_BLOCK_UNUSED = 2,

    /** Record 0: the head of the block list. */
    LIB_TEXTURE_BLOCK_HEAD = 3
};

/**
 * One piece of the texture area. The records form a list in address order through previous_block and
 * next_block, starting and ending at record 0. A used record's index is also its texture's cache index.
 */
struct LibTextureBlock
{
    u32 id;
    u32 address;
    u32 size;
    u8 previous_block;
    u8 next_block;
    u8 state;
    u8 stamp;
};

/** One CLUT record of a texture cache. */
struct LibTextureClut
{
    u32 id;
    u32 tag;
    u64 tex0;
};

/** Partial value half of a cache entry. */
struct LibTextureEntry
{
    u32 tag;
    LibTextureUser* user;
    u64 tex0;
};

/** VRAM area a texture cache miss asks for. */
struct LibTextureRequest
{
    u16 width;
    s16 height;
    s32 size;
    u8 unk08[4];
    u16 psm;
    u8 width_log2;
    u8 height_log2;
};

#define LIB_TEXTURE_TAG_MLPS 0x4D6C5073
#define LIB_TEXTURE_TAG_LATF 0x4674404C
#define LIB_TEXTURE_PRIORITY_MAX 10
#define LIB_TEXTURE_PRIORITY_MIN -10
#define LIB_TEXTURE_PRIORITY_KEEP -5
#define LIB_TEXTURE_PRIORITY_RECENT -3
#define LIB_TEXTURE_FLAG_DOUBLE_WIDTH 0x2000

/** Partial 0x2910-byte VRAM texture cache (g_texture_cache). It may sit at the start of scratchpad memory. */
class LibTextureCache
{
public:
    LibTextureCache();

    /**
     * @brief Allocate the texture and CLUT areas in VRAM and reset the cache.
     * @param size Size of the texture area in bytes.
     * @param count Number of CLUTs to hold; rounded up to a power of two, at least 8. At most 64.
     */
    LibTextureCache(s32 size, s32 count);

    /** @brief Empty the cache: one free block over the whole texture area, no textures and no CLUTs. */
    void reset();

    /**
     * @brief Release a texture's block back to the free area.
     * @param index Cache index of the texture.
     */
    void release_block(u32 index);

    /**
     * @brief Release every block no lookup has stamped since the stamps were cleared; with none stamped, empty the cache.
     */
    void release_unstamped();

    /**
     * @brief Detach the user from every cached copy of a texture.
     * @param tag Texture tag.
     * @param id Texture ID.
     */
    void detach_user(u32 tag, u32 id);

    /**
     * @brief Release the most recently used cached copy of a texture.
     * @param tag Texture tag.
     * @param id Texture ID.
     */
    void release_texture(u32 tag, u32 id);

    /**
     * @brief Build the CLUT half of TEX0 for the CLUT a slot last found.
     * @param slot Slot whose CLUT to use.
     * @param entry CLUT entry offset (CSA).
     * @param load_mode 0 to always load the CLUT, 1 to load it and keep CBP 0, 2 not to load it; anything else
     *        loads it and keeps CBP 1.
     * @return CBP, CPSM, CSA and CLD in TEX0's layout.
     */
    u64 get_clut_tex0(s16 slot, s16 entry, s32 load_mode);

    /**
     * @brief Release every used block that overlaps the last bytes of the texture area.
     * @param size Size of the area to clear at the end.
     */
    void release_area_end(u32 size);

    /**
     * @brief Clear the stamp of every block holding a texture ID, and the cache's own stamp.
     * @param id Texture ID.
     */
    void expire_texture(u32 id);

    /** @brief Clear the cache's stamp, the stamp of every block stamped 1, and the CLUT use flags. */
    void clear_stamps();

    /**
     * @brief Check that both VRAM areas were allocated.
     * @return Whether the texture and CLUT slots are valid.
     */
    bool is_allocated() const
    {
        return !(texture_slot == -1 || clut_slot == -1);
    }

    /**
     * @brief Allocate the cache through the resident allocator, or place it at the scratchpad.
     * @param size Object size in bytes.
     * @param heap Heap selector, or EE_SCRATCHPAD.
     * @return The allocated storage.
     */
    static void* operator new(u32 size, s32 heap)
    {
        if (heap == EE_SCRATCHPAD)
        {
            return (void*)EE_SCRATCHPAD;
        }

        return ::operator new(size, heap);
    }

    /**
     * @brief Release the storage when construction fails, unless it is the scratchpad.
     * @param object Storage to release.
     * @param heap Heap selector passed to operator new.
     */
    static void operator delete(void* object, s32 heap)
    {
        if (object != (void*)EE_SCRATCHPAD)
        {
            ::operator delete(object);
        }
    }

    /**
     * @brief Look up a cached texture, loading it on a miss.
     * @param request Texture to load on a miss, or null to only look.
     * @param tag Request tag.
     * @param id Texture ID.
     * @param slot Slot whose last hit is recorded.
     * @param unk5 Passed to the loader on a miss.
     * @param want_address Nonzero to return the texture's VRAM address.
     * @param user Object whose priority a hit on a user-owned texture lowers.
     * @return VRAM word address of the texture, or 0.
     */
    u32 find_texture(LibTextureRequest* request, u32 tag, s32 id, s32 slot, u16 unk5, s32 want_address,
                     LibTextureUser* user);

    /**
     * @brief Look up an image's texture and record a hit for a slot, raising a user-owned texture's priority.
     * @param image Image header whose name and ID identify the texture.
     * @param slot Slot whose last hit is recorded.
     * @param user Object that would own the texture; unused.
     * @return Zero on a hit or for an 'MlPs' image, one when the texture still has to be loaded.
     */
    s32 func_004A6D20(const struct LibImageHeader* image, s32 slot, LibTextureUser* user);

    /**
     * @brief Find an image's CLUT and record a hit for a slot; on a miss, claim the next free CLUT for it.
     * @param image Image header whose name and ID identify the CLUT.
     * @param slot Slot whose CLUT is recorded.
     * @param want_address Nonzero to return the CLUT's VRAM address on a hit.
     * @return The CLUT's VRAM word address (always on a miss), or 0 on a hit without want_address or when every
     *         CLUT is in use.
     */
    u32 func_004A6EA0(const struct LibImageHeader* image, s32 slot, u8 want_address);

    /**
     * @brief Move an entry to the front of the most-recently-used list.
     * @param index Entry to move; it must not already be at the front.
     */
    void move_to_front(u32 index)
    {
        next[previous[index]] = next[index];
        previous[next[index]] = previous[index];
        next[index] = next[0];
        previous[index] = 0;
        previous[next[0]] = index;
        next[0] = index;
    }

    s16 texture_slot;
    s16 clut_slot;
    u32 unk04;
    LibTextureBlock blocks[LIB_TEXTURE_CACHE_ENTRY_COUNT];
    LibTextureEntry entries[LIB_TEXTURE_CACHE_ENTRY_COUNT];
    u8 next[LIB_TEXTURE_CACHE_ENTRY_COUNT];
    u8 previous[LIB_TEXTURE_CACHE_ENTRY_COUNT];
    s32 texture_size;
    u32 unk220c;
    u32 next_clut;
    u8 unk2214[4];
    LibTextureClut cluts[LIB_TEXTURE_CACHE_MAX_CLUTS];
    u8 unk2618[8];
    u8 clut_used[LIB_TEXTURE_CACHE_MAX_CLUTS];


    u32 texture_address;
    u32 clut_address;
    u8 unk2668[4];
    s32 clut_count;
    s16 slot_entries[LIB_TEXTURE_CACHE_ENTRY_COUNT];
    s16 clut_slot_entries[LIB_TEXTURE_CACHE_MAX_CLUTS];
    u8 stamp;
    u8 unk28f1[0x1F];
};

/** The game's texture cache. */
extern "C" LibTextureCache* g_texture_cache;

/** DMA queues of channels 8 and 9 (scratchpad transfers). */
extern "C" ResidentDmaQueue* D_001B6604;
extern "C" ResidentDmaQueue* D_001B6608;

/**
 * @brief Stop the channel 8 queue and start a 0x291-quadword transfer from the scratchpad.
 * @param address Main memory address.
 * @param scratchpad Scratchpad address.
 */
extern "C" void func_004D9030(void* address, void* scratchpad);

/**
 * @brief Load a texture the cache missed.
 * @param cache Cache to add the texture to.
 * @param request Texture to load.
 * @param tag Request tag.
 * @param id Texture ID.
 * @param slot Slot whose last hit is recorded.
 * @param flags Loader flags (LIB_TEXTURE_FLAG_*).
 * @param user Object that owns the texture, or null.
 * @return VRAM word address of the texture, 0 when no spare block record is left, or 1 when no block is large
 *         enough.
 */
extern "C" u32 func_004A7100(LibTextureCache* cache, LibTextureRequest* request, u32 tag, s32 id, s32 slot, u16 flags,
                             LibTextureUser* user);


extern "C" u32 D_001B65BC;
extern "C" u8 D_001B65C0;

/** Bits of LibTransformOwner::draw_flags. */
enum
{
    /** Don't draw the object. */
    LIB_DRAW_HIDDEN = 0x0001,

    /** Keep the object under the camera: its x and z follow the camera's position every update. */
    LIB_DRAW_FOLLOW_CAMERA = 0x0004,

    /** Set by a level-selection controller on the objects outside its active level. */
    LIB_DRAW_FLAG_0008 = 0x0008,

    LIB_DRAW_FLAG_0010 = 0x0010,

    /** Test the transform chain's combined unk200 factor every update and set LIB_DRAW_FLAG_0040 below one half. */
    LIB_DRAW_FLAG_0020 = 0x0020,

    LIB_DRAW_FLAG_0040 = 0x0040,

    /** Turn the object with the camera about x, y or z. */
    LIB_DRAW_FACE_CAMERA_X = 0x0080,
    LIB_DRAW_FACE_CAMERA_Y = 0x0100,
    LIB_DRAW_FACE_CAMERA_Z = 0x0200,

    LIB_DRAW_FLAG_0400 = 0x0400
};

class LibDisplayManager;

/** One 0x68-byte layer record of a scene. */
struct LibSceneLayer
{
    LibDisplayManager* display_manager;
    u8 unk04[0x64];
};

// TODO: This is LibRenderer::layers seen 0x64 bytes early (each LibRenderLayer's display_manager at +4), indexed by
// layer number; LibColorModel::update only matches through this indexing, not layers[layer - 1].
/** Partial view of the update list that owns a scene's objects, reaching its layer records. */
struct LibSceneLayerTable
{
    /**
     * @brief Read a layer's display manager.
     * @param layer Layer index.
     * @return The layer's display manager.
     */
    LibDisplayManager* get_display_manager(s32 layer)
    {
        return layers[layer].display_manager;
    }

    u8 unk00[0xB30C];
    LibSceneLayer layers[1];
};

/** Partial oriented box Lib tests against the view. */
struct LibCullBox
{
    LibVector4 center;
    FieldVec4B axes[3];
    LibVector4 half_extents;
};

struct LibProjectionVolume;

/**
 * @brief Test an oriented box against a projection volume.
 * @param volume View volume.
 * @param box Box in view space.
 * @return Nonzero when the box reaches into the volume.
 */
extern "C" s32 func_004CAB20(const LibProjectionVolume* volume, const LibCullBox* box);

/** Partial 0x90-byte transform owner with vtable D_178A90 in main data. */
class LibTransformOwner : public LibOrientedTransform
{
public:
    /** @brief Initialize the owner's state bytes and tracking words. */
    inline LibTransformOwner();

    /** @brief Remove this object's mask from the resident flags, then destroy the transform. */
    virtual ~LibTransformOwner()
    {
        u32 mask = ~unk8c;
        u32 previous = D_001B65BC;
        unk8c &= mask;
        D_001B65BC &= mask;

        if (previous != D_001B65BC)
        {
            D_001B65C0 = 1;
        }
    }

    /** @brief Virtual slot 4; the owner's implementation does nothing. */
    virtual void render();

    /** @brief Detach and queue the owner. */
    virtual void destroy();

    /** @brief Draw in the main list (bucket zero). */
    virtual void set_default_draw_bucket();

    /**
     * @brief Give the centre for Lib's oriented-box visibility test; this owner has none.
     * @param output Receives the centre in local space.
     * @return Nonzero when a centre was written; zero here, so the test is skipped.
     */
    virtual s32 get_box_cull_center(void* output);

    /**
     * @brief Fade the owner as it nears the camera; Lib calls this for owners with draw flag 0x800. This owner doesn't fade.
     * @param value Distance in front of the camera over the fade range, clamped to one.
     * @param mode Two from Lib's caller; unused here.
     * @return Whether the value is negative.
     */
    virtual s32 set_fade_alpha(float value, float mode);

    /**
     * @brief Return the bounding sphere Lib culls against (centre in xyz, radius in w); this owner has Lib's shared default.
     * @return Bounding sphere.
     */
    virtual const LibVector4* get_bounding_sphere();

    /**
     * @brief Default matrix handler; does nothing.
     * @param matrix Matrix supplied by the caller.
     * @param context Opaque caller context.
     */
    virtual void build_packet(const void* matrix, void* context);

    /** @brief Mark the matrix state ready. */
    virtual void update_transform_matrix();

    /**
     * @brief Read the stored transformation matrix.
     * @return Matrix pointer.
     */
    virtual const LibMatrix44Value* get_transform_matrix();

    /**
     * @brief Copy the source transformation state.
     * @param source Transform source.
     */
    virtual void copy_transform_state(const LibTransformOwner* source);

    /**
     * @brief Make a copy of this object that stays linked to it; this owner can't be copied.
     * @return The copy, or null.
     */
    virtual LibTransformOwner* clone();

    /** @brief Unlink a copy from its original and queue it for release; this owner never has copies, so it does nothing. */
    virtual void release_clone();

    /**
     * @brief Read the draw flags (LIB_DRAW_*).
     * @return Flags.
     */
    inline u16 get_draw_flags() const;

    /**
     * @brief Set the draw flags (LIB_DRAW_*).
     * @param value New flags.
     */
    inline void set_draw_flags(u16 value);

    /**
     * @brief Set the object's type ID.
     * @param value Type ID.
     */
    inline void set_type_id(u16 value);

    u8 draw_bucket;
    u8 matrix_ready;
    u8 unk62;
    u8 unk63;
    u8 dma_pending;
    u8 unk65;
    u8 unk66;
    u8 unk67;
    u8 layer;
    u8 unk69;
    u16 draw_flags;
    u16 type_id;
    u8 unk6e[2];
    LibVector4 unk70;
    LibDisplayManager* display_manager;
    float depth;
    u32 unk88;
    u32 unk8c;
};

/** Values of LibLight::kind; kinds with LIB_LIGHT_LOCAL set are local lights, the rest directional. */
enum
{
    LIB_LIGHT_LOCAL = 4,
    LIB_LIGHT_KIND_SPOT = 6
};

class LibLight;

/**
 * @brief Read a spotlight's position, direction, and the cosine and sine of its cone angle.
 * @param light Spotlight; its transform matrix is updated first if it isn't ready.
 * @param frame Receives the position (w 1), the direction, and the cosine and sine in x and y.
 */
extern "C" void lib_spot_light_get_frame(LibLight* light, LibVector4* frame);

/**
 * @brief Read a light's direction (its transform's y axis) from its current transform matrix.
 * @param out Receives the direction, w one.
 * @param light Light.
 */
extern "C" void lib_light_get_direction(LibVector4* out, LibLight* light);

/**
 * @brief Return how strongly a spotlight lights a point: zero behind it, rising to one inside its inner cone.
 * @param light Spotlight.
 * @param point Point to light.
 * @return Falloff from zero to one.
 */
extern "C" float func_004C9D80(LibLight* light, const LibVector4* point);

/**
 * @brief Return the direction a light shines on a point: from the light's position for point and spot kinds when
 *        it has one, otherwise its own direction.
 * @param light Light.
 * @param out Receives the unit direction.
 * @param point Point being lit.
 */
extern "C" void func_004C9E80(LibLight* light, LibVector4* out, const LibVector4* point);


/** Two-callback DMA interface, with vtable D_171FF0 in main data. */
class LibDmaCallbacks
{
public:
    inline LibDmaCallbacks();

    /**
     * @brief Default DMA notification hook; does nothing.
     * @param value Notification value.
     */
    virtual void on_packet_notify(u32 value);

    /**
     * @brief Default preparation hook; does nothing.
     * @param value Notification word or packet address.
     */
    virtual void on_packet_complete(u32 value);
};

/** Transform subclass between D_178A90 and D_174610, with vtable D_172000 in main data. */
class LibClass172000 : public LibTransformOwner
{
public:
    /** @brief Initialize the transform subclass. */
    LibClass172000();

    virtual ~LibClass172000()
    {
    }
};

/** Partial list owner with resident vtable at 0x178DD0 and an owned node buffer. */
class LibUpdateList : public LibListReceiver
{
public:
    enum
    {
        DEFAULT_NODE_KIND = -1,
        NODE_KIND_COUNT = 17
    };

    /** @brief Initialize the list owner, kind counts, and node-buffer state. */
    LibUpdateList();

    /** @brief Release the owned node buffer and destroy the list base. */
    virtual ~LibUpdateList();

    /**
     * @brief Remove a registered node and clear its pending buffer entries.
     * @param object Node to remove.
     */
    virtual void remove_node(void* object);

    /**
     * @brief Run update handlers for registered nodes in list-kind order.
     *
     * Snapshot the list chain, skip null or detached nodes, and honor each
     * node's update flags. Derived lists can choose their own update order.
     */
    virtual void update_nodes();

    /**
     * @brief Register and append a node.
     * @param object Node to append.
     * @param kind List kind, or DEFAULT_NODE_KIND to use the node's virtual kind.
     */
    virtual void append_node(void* object, s32 kind);

    /**
     * @brief Register and prepend a node.
     * @param object Node to prepend.
     * @param kind List kind, or DEFAULT_NODE_KIND to use the node's virtual kind.
     */
    virtual void prepend_node(void* object, s32 kind);

    /**
     * @brief Register a node after a list position.
     * @param position Insertion position.
     * @param object Node to insert.
     * @param kind List kind, or DEFAULT_NODE_KIND to use the node's virtual kind.
     */
    virtual void insert_node_after(void* position, void* object, s32 kind);

    /**
     * @brief Set the next list in the chain.
     * @param attached List that follows this list.
     */
    virtual void set_next_list(void* attached)
    {
        next_list = static_cast<LibUpdateList*>(attached);
    }

    /** @brief Default handler that performs no work. */
    virtual void idle()
    {
    }

    u32 node_counts_by_kind[NODE_KIND_COUNT];
    u32 unk58;
    s32 active_node_index;
    s32 active_node_count;
    s32 node_buffer_capacity;
    void** owned_node_buffer;
    void** active_node_buffer;
    LibUpdateList* next_list;
    LibUpdateList* active_buffer_owner;
};

/** Ring of 256 0x80-byte packet slots that are written through the uncached accelerated segment. */
class LibPacketRing
{
public:
    /** @brief Flush the data cache and start writing at slot one. */
    LibPacketRing();

    u8 slots[256][0x80];
    s32 next_slot;
    u8 unk8004[0x7C];
};

class LibRenderResource;

/** Fixed-capacity table of the registered render resources, with vtable D_178B10 in main data. */
class LibImageRegistry : public LibListObject
{
public:
    /**
     * @brief Allocate an empty table.
     * @param capacity Number of resources the table can hold.
     */
    LibImageRegistry(s32 capacity);

    /** @brief Release the table, then detach from the owner. */
    virtual ~LibImageRegistry();

    /**
     * @brief Report the list kind used when registration requests the default.
     * @return Sixteen.
     */
    virtual s32 get_default_list_kind();

    /** @brief Clear each registered resource's second state byte. */
    virtual void update();

    /**
     * @brief Step the search cursor down to the next registered resource.
     * @return The resource at the cursor, or null once the cursor has passed the first one.
     */
    LibRenderResource* next_entry()
    {
        return cursor < 0 ? 0 : entries[cursor--];
    }

    LibRenderResource** entries;
    s32 capacity;
    s32 count;
    s32 cursor;
};


extern "C"
{
    /**
     * @brief Remove a resource from the registry, keeping the rest in order.
     * @param registry Registry to search.
     * @param resource Resource to remove; nothing happens when it isn't registered.
     */
    void func_004D0260(LibImageRegistry* registry, LibRenderResource* resource);

    /**
     * @brief Append a resource to the registry.
     * @param registry Registry to fill.
     * @param resource Resource to add.
     * @return One, or zero when the registry is full.
     */
    s32 func_004D02E0(LibImageRegistry* registry, LibRenderResource* resource);
}

/**
 * @brief Allocate the owned node-pointer buffer and store its capacity.
 * @param owner List that owns the buffer.
 * @param node_count Number of node pointers to allocate.
 */
extern "C" void lib_list_allocate_node_buffer(LibUpdateList* owner, s32 node_count);

/**
 * @brief Release the owned node buffer when no node buffer is active.
 * @param owner List that owns the buffer.
 * @return One if the buffer was released, or zero while a buffer is active.
 */
extern "C" s32 lib_list_release_node_buffer(LibUpdateList* owner);

/**
 * @brief Transfer one node count from the node's stored kind to a new kind.
 * @param owner List whose per-kind counts are updated.
 * @param node Node supplying the old kind.
 * @param new_kind Kind whose count is incremented.
 */
extern "C" void lib_list_change_node_kind_counts(LibUpdateList* owner, const LibListObject* node, s32 new_kind);

/**
 * @brief Update the owner's kind counts, then store the node's list kind.
 * @param node Node whose list kind is changed.
 * @param kind Kind passed to the owner; its low halfword is stored in the node.
 */
extern "C" void lib_object_set_list_kind(LibListObject* node, s32 kind);

/**
 * @brief Collect the list chain's nodes into an array grouped by list kind.
 * @param list First list whose nodes are collected.
 * @param items Array with room for every node in the chain.
 */
extern "C" void lib_list_collect_nodes_by_kind(LibUpdateList* list, void** items);

/**
 * @brief Give a list and every list chained after it the same active buffer owner.
 * @param list First list.
 * @param owner Owner of the active node buffer.
 */
extern "C" void func_004D68F0(LibUpdateList* list, LibUpdateList* owner);

/**
 * @brief Count the nodes of a list and every list chained after it.
 * @param list First list.
 * @return Total node count.
 */
extern "C" s32 func_004D69A0(LibUpdateList* list);

/**
 * @brief Add each list's per-kind prefix sums to the chain's kind offsets.
 * @param list First list whose counts are added.
 * @param offsets Array of NODE_KIND_COUNT offsets to update.
 */
extern "C" void lib_list_add_chain_kind_offsets(LibUpdateList* list, u32* offsets);

/** 0x98-byte display manager with a list interface and secondary intrusive receiver. */
class LibDisplayManager : public LibUpdateList, public LibListObject
{
public:
    /** @brief Initialize the manager interfaces and current display. */
    LibDisplayManager();

    /** @brief Destroy both manager interfaces. */
    virtual ~LibDisplayManager();

    /**
     * @brief Report the manager type.
     * @return Manager type value.
     */
    virtual s32 get_default_list_kind();

    /** @brief Update the manager's intrusive receiver. */
    virtual void update();

    /**
     * @brief Turn the display's effect on or off and pick its level.
     * @param display Display the effect applies to.
     * @param enabled Nonzero to turn the effect on.
     * @param first_flag Passed to the display unchanged.
     * @param second_flag Passed to the display and kept here.
     * @param level Effect level; it picks the two scales passed to the display.
     * @param mask Passed to the display unchanged.
     */
    void set_display_effect(LibCameraContext* display, bool enabled, bool first_flag, bool second_flag, s32 level,
                            u32 mask);

    /** @brief Run LibCamera::func_004E1E70 on the current camera, if there is one. */
    void func_004DB0F0();

    /** @brief Queue the current camera, if there is one, for VIF1 DMA. */
    void submit_camera();

    /** @brief Set unk94 and write the current camera's matrices, if there is one. */
    void prepare_camera();

    LibCameraContext* effect_display;
    LibListObject* current_display;
    u8 unk94;
    u8 effect_enabled;
    u8 unk96;
    u8 effect_level;
};

/**
 * The scene's lights: a 0x390-byte update list with vtable D_179690 in main data (constructor 0x4E95C0), made once by
 * Lib's initialization and kept in g_light_list. The renderer holds it as light_list and calls into it before drawing
 * models and at the end of the frame; the scene builder appends a scene's lights to it and writes the three
 * non-negative floats at 0x310.
 */
class LibLightList : public LibUpdateList, public LibListObject
{
    public:
        /** @brief Start with no lights, a (0, 0, 0, 1) ambient colour and white light scales. */
        LibLightList();

        virtual ~LibLightList();

        /**
         * @brief Return the list's kind.
         * @return Eight.
         */
        virtual s32 get_default_list_kind();

        /** @brief Update the listed nodes. */
        virtual void update();

        /**
         * @brief Give each enabled spotlight its own bit (8 up to 31) in its mask, then set that bit on every model in the
         * renderer that shares one of the light's groups and whose bounding sphere reaches into the light's cone.
         * @param renderer Renderer whose models are tested.
         */
        void assign_spot_lights(class LibRenderer* renderer);

        u8 unk8c[4];
        LibMatrix44Value unk90;
        LibMatrix44Value unkd0;
        LibVector4 directions[4];
        float colors[4][4];
        u8 unk190[0x40];
        LibMatrix44Value unk1d0;
        LibVector4 unk210[3];
        LibMatrix44Value unk240;
        LibVector4 unk280;
        unsigned __int128 unk290[2];
        unsigned __int128 unk2b0[2];
        unsigned __int128 unk2d0[2];
        unsigned __int128 unk2f0[2];
        FieldVec4B unk310;
        FieldVec4B unk320;
        FieldVec4B unk330;
        LibVector4 unk340;
        unsigned __int128 unk350;
        LibDisplayManager* manager;
        LibLight* unk364[3];
        u32 mask;
        float unk374;
        s16 light_count;
        s16 unk364_count;
        s8 unk37c;
        s8 unk37d;
        u8 unk37e;
        u8 has_local_lights;
        u8 unk380;
        u8 unk381;
        u8 unk382;
        u8 unk383[0xD];
};

/**
 * @brief Set a light list's ambient colour, clamping negative channels to zero.
 * @param lights Light list.
 * @param red Red.
 * @param green Green.
 * @param blue Blue.
 */
static inline void lib_light_list_set_ambient(LibLightList* lights, float red, float green, float blue)
{
    if (red < 0.0f)
    {
        red = 0.0f;
    }

    if (green < 0.0f)
    {
        green = 0.0f;
    }

    if (blue < 0.0f)
    {
        blue = 0.0f;
    }

    lights->unk310.x = red;
    lights->unk310.y = green;
    lights->unk310.z = blue;
}

extern LibLightList* g_light_list;

/** Display manager whose current camera objects face by default. */
extern LibDisplayManager* g_display_manager;

/** Display Lib draws on. */
extern LibCameraContext* g_display;

/** Second copy of the draw display that LibRenderer::set_display keeps; Lib's image code reads it. */
extern LibCameraContext* D_001B6520;

#define LIB_RENDERER_BUFFER_SIZE 0x2000

/** Partial renderer pass that draws to the display at 0x94. */
struct LibRendererPass : public LibTransformOwner
{
    u8 unk90[4];
    LibCameraContext* display;
    u8 unk98[4];
    u8 unk9c;
    u8 unk9d;
    u8 unk9e[2];
    float unka0;
    float unka4;
    u32 unka8;
    u8 unkac;
    u8 unkad;
    u8 unkae;
    u8 unkaf;
};

/** Partial renderer pass that lib_initialize can switch on, drawing to the display at 0x128. */
struct LibRendererExtra : public LibTransformOwner
{
    u8 unk90[6];
    u8 enabled;
    u8 unk97[0x91];
    LibCameraContext* display;
};

/** Resident hit-test flags; bit 0 is set when a hit-test node is removed. */
extern "C" u8 g_hit_test_restart;

/**
 * @brief Set up one of the renderer's extra layers as a square render target, with its MLPS image header and info
 *        block built in place.
 * @param renderer Renderer.
 * @param layer Layer number, from 1.
 * @param size Width and height in pixels, a power of two.
 * @param manager Display manager the layer draws with.
 */
extern "C" void func_004D08D0(class LibRenderer* renderer, s32 layer, s32 size, LibDisplayManager* manager);

/**
 * @brief Run the renderer's per-frame packet passes.
 * @param renderer Renderer.
 */
extern "C" void func_004D0F80(class LibRenderer* renderer);

/**
 * @brief Third of the renderer's light steps.
 * @param renderer Renderer.
 */
extern "C" void func_004D3290(class LibRenderer* renderer);

/**
 * @brief Second of the renderer's light steps.
 * @param renderer Renderer.
 */
extern "C" void func_004D3480(class LibRenderer* renderer);

/**
 * @brief First of the renderer's light steps.
 * @param renderer Renderer.
 */
/**
 * @brief Sort a renderer's objects into a draw list.
 * @param renderer Renderer.
 * @param list Receives the objects.
 * @param layer Layer to collect; zero for the main list.
 * @return Number of objects written.
 */
extern "C" s32 func_004D1550(class LibRenderer* renderer, class LibTransformOwner** list, s32 layer);

extern "C" void func_004D3780(class LibRenderer* renderer);

class LibClass1734D0;

/** The renderer's occluders are LibClass1734D0 rectangles. */
typedef LibClass1734D0 LibOccluder;

/** LibUpdateList subclass with vtable D_00178B30 in main data, holding the renderer's occluders. */
class LibClass178B30 : public LibUpdateList
{
public:
    virtual ~LibClass178B30();

    LibOccluder* nodes[128];
    float nearest_depth;
    u8 unk27c[0xC];
};

/**
 * @brief Collect up to 128 occluders, upload the ones in view to VU0 (nine qwords each from qword 8) and note the
 *        nearest one's depth.
 * @param list Occluder list.
 * @param camera Camera to test against.
 * @param matrix Depth-scaled view matrix.
 * @return Number of occluders uploaded.
 */
extern "C" s32 func_00430E00(LibClass178B30* list, class LibCamera* camera, const LibMatrix44Value* matrix);

/**
 * @brief Upload an occluder to VU0 data memory at a slot if it's in view.
 * @param occluder Occluder.
 * @param position Camera position, w one.
 * @param slot First VU0 data qword to write.
 * @return Nonzero when the occluder was uploaded.
 */
extern "C" s32 func_00431090(LibOccluder* occluder, const LibVector4* position, s32 slot);

/** Update list that is also a list object (vtables D_00178F30 and D_00178F68 in main data); only its destructor is known. */
class LibClass178F30 : public LibUpdateList, public LibListObject
{
public:
    /** @brief Start with nothing displayed and object kind bit 2 set. */
    inline LibClass178F30();

    virtual ~LibClass178F30();

    /**
     * @brief Return the list kind.
     * @return Eight.
     */
    virtual s32 get_default_list_kind();

    /** @brief Update the display list. */
    virtual void update();

    LibCameraContext* effect_display;
    LibListObject* current_display;
    u8 unk94;
    u8 effect_enabled;
    u8 unk96;
    s8 effect_level;
};

/** Transform owner that is also a DMA submission (vtables D_00178C00 and D_00178C74 in main data); only its destructor is known. */
class LibClass178C00 : public LibTransformOwner, public DmaSubmission
{
public:
    /** @brief Set the object's type ID after the base constructors. */
    LibClass178C00();

    virtual ~LibClass178C00();

    /** @brief Forget the owning list, then destroy through the base. */
    virtual void destroy();

    /** @brief Queue this object's DMA submission on the VIF1 queue. */
    virtual void render();

    /**
     * @brief Build this object's VIF1 packet.
     * @param matrix View matrix.
     * @param context Packet building context.
     */
    virtual void build_packet(const void* matrix, void* context);

    /**
     * @brief Start the object's DMA chain on channel 1 (VIF1).
     * @param channel DMA channel; unused.
     */
    virtual void submit_dma(u32 channel);

    /**
     * @brief Finish the object's packet.
     * @param channel DMA channel; unused.
     */
    virtual void complete_dma(u32 channel);

    u8 unk94[0x4C];
    u8 chain[0x20];
    u8 unk100[0x80];
};

/** Transform owner that is also a DMA submission (vtables D_00178B70 and D_00178BE4 in main data); only its destructor is known. */
class LibClass178B70 : public LibTransformOwner, public DmaSubmission
{
public:
    /** @brief Set the object's type ID after the base constructors. */
    LibClass178B70();

    virtual ~LibClass178B70();

    /** @brief Forget the owning list, then destroy through the base. */
    virtual void destroy();

    /** @brief Queue this object's DMA submission on the VIF1 queue. */
    virtual void render();

    /**
     * @brief Build this object's VIF1 packet.
     * @param matrix View matrix.
     * @param context Packet building context.
     */
    virtual void build_packet(const void* matrix, void* context);

    /**
     * @brief Start the object's DMA chain on channel 1 (VIF1).
     * @param channel DMA channel; unused.
     */
    virtual void submit_dma(u32 channel);

    /**
     * @brief Finish the object's packet.
     * @param channel DMA channel; unused.
     */
    virtual void complete_dma(u32 channel);

    u8 unk94[0x4C];
    u8 chain[0x10];
    u8 unkf0[0x70];
};

/**
 * One of the renderer's 32 extra layers: a square render target of `size` pixels, with an MLPS image header and its
 * info block built in place so the layer can be looked up like any other image.
 */
struct LibRenderLayer
{
    s32 size;
    LibDisplayManager* display_manager;
    u32 unk08;
    s16 unk0c;
    s16 unk0e;
    u32 tag;
    s32 index;
    u8 unk18[0x18];
    LibImageHeader* image;
    u8 unk34[4];
    LibImageHeader header;
    u8 unk54[4];
    LibImageInfo info;
};

/** GS packet that draws eight sprite vertices with the depth test and scissor set around them. */
struct LibSpritePacket
{
    LibSpritePacket();

    u32 dma_tag[2];
    u32 vif_flush;
    u32 vif_direct;
    u64 gif_tag;

    union
    {
        u64 gif_registers;

        struct
        {
            u64 register0 : 4;
            u64 unused : 60;
        } gif_register_fields;
    };

    GsRegisterValue test;
    GsRegisterValue fba;
    GsRegisterValue prim;
    GsRegisterValue rgbaq;
    GsRegisterValue xyz[8];
    GsRegisterValue restore_test;
    GsRegisterValue scissor;
};

/** Packet that sets FRAME_1, ZBUF_1, XYOFFSET_1 and SCISSOR_1 through A+D. */
struct LibDrawEnvPacket
{
    /** @brief Set up the packet's fixed words: its tags and the register each write goes to. */
    LibDrawEnvPacket()
    {
        vif_flush = 0x11000000;
        vif_nop[0] = 0;
        vif_nop[1] = 0;
        vif_direct = 0x51000005;
        gif_tag = 4 | GIF_TAG_EOP | GIF_TAG_NREG(1);
        gif_registers = 0;
        gif_register_fields.register0 = GIF_REGISTER_AD;
        frame.address = GS_REGISTER_FRAME_1;
        zbuf.address = GS_REGISTER_ZBUF_1;
        xyoffset.address = GS_REGISTER_XYOFFSET_1;
        scissor.address = GS_REGISTER_SCISSOR_1;
    }

    u32 vif_flush;
    u32 vif_nop[2];
    u32 vif_direct;
    u64 gif_tag;

    union
    {
        u64 gif_registers;

        struct
        {
            u64 register0 : 4;
            u64 unused : 60;
        } gif_register_fields;
    };

    GsRegisterValue frame;
    GsRegisterValue zbuf;
    GsRegisterValue xyoffset;
    GsRegisterValue scissor;
};

/** Partial Lib renderer (g_renderer); it alternates between two packet buffers each frame. */
class LibRenderer : public LibUpdateList
{
public:
    /**
     * @brief Build the renderer's members, passes and per-layer cameras, then draw on a display.
     * @param target Display to draw on.
     */
    LibRenderer(LibCameraContext* target);

    /** @brief Destroy the renderer. */
    virtual ~LibRenderer();

    /**
     * @brief Draw everything on a display: the renderer, its manager's effect, its passes, g_display and D_001B6520.
     * @param target Display to draw on.
     */
    void set_display(LibCameraContext* target)
    {
        display = target;
        g_display = target;

        if (manager != 0)
        {
            manager->effect_display = target;
        }

        unk4458->display = target;
        unk4460->display = target;
        unk4464->display = target;
        unk4468->display = target;
        extra->display = target;
        D_001B6520 = target;
    }

    /** @brief Start a frame: swap packet buffers and, with a list and a camera, build the frame's packets. */
    void begin_frame();

    void func_004D4700();

    /**
     * @brief Kick the packet queue if a main packet is waiting, then render every object in the current list that is a
     *        bucket packet with work; with none, flag the display once the main packet is done.
     */
    void func_004D4560();

    /**
     * @brief Build this frame's draw list. With layered objects, the first object to name a layer in its mask gets that
     *        layer's start marker, the layer's own list and its end marker in front of it.
     */
    void func_004D2C70();

    /**
     * @brief Test or wait for the renderer's packets in flight.
     * @param poll Nonzero to only test; zero to wait until none is in flight.
     * @return Whether a packet is in flight (when polling).
     */
    bool func_004D44D0(s32 poll);

    /** @brief Do nothing. */
    virtual void func_slot38();

    /** @brief Update the listed nodes, then make the next hit test start from the first node. */
    virtual void func_slot3C();

    /** @brief Run the light steps and hand the spot lights to the light list. */
    void update_lights();

    u8* cursor;
    u8* unk7c;
    u8 buffers[2][LIB_RENDERER_BUFFER_SIZE];
    LibDisplayManager* manager;
    LibLightList* light_list;
    LibCameraContext* display;
    u32 unk408c;
    s32 unk4090;
    s32 current_count;
    s32 list_counts[2];
    u32 unk40a0;
    s32 packet_ticks;
    LibTransformOwner* main_packet;
    LibTransformOwner* bucket_packet;
    u32 unk40b0;
    u32 unk40b4;
    float fade_distance;
    u8 unk40bc[4];
    s32 packet_start_time;
    s32 unk40c4;
    u8 main_packet_busy;
    u8 bucket_packet_busy;
    u8 unk40ca;
    u8 unk40cb;
    u8 unk40cc;
    u8 unk40cd;
    u8 unk40ce;
    u8 unk40cf;
    u8 box_cull_enabled;
    u8 buffer_index;
    u8 unk40d2;
    u8 unk40d3;
    LibTextureCache* unk40d4;
    LibClass178B30 unk40d8;
    LibMatrix44Value unk4360;
    u8* sphere_buffer;
    LibTransformOwner** buckets[11];
    u8 unk43d0[4];
    u8* unk43d4;
    u8* unk43d8[32];
    LibRendererPass* unk4458;
    LibRendererPass* unk445c;
    LibRendererPass* unk4460;
    LibRendererPass* unk4464;
    LibRendererPass* unk4468;
    LibRendererExtra* extra;
    LibClass178F30 unk4470[32];
    LibClass178C00 unk5770[32];
    LibClass178B70 unk8770[32];
    LibRenderLayer layers[32];
    class LibCamera* cameras[32];
    u8 unkc0f0[0x40];
    LibSpritePacket sprite_packets[32];
    LibDrawEnvPacket draw_envs[2][32];
    u8 unkf930[0x40];
    s32 visible_count;
};

inline void LibRenderer::update_lights()
{
    func_004D3780(this);
    func_004D3480(this);
    func_004D3290(this);
    light_list->assign_spot_lights(this);
}

/**
 * @brief Build the packets of one of the renderer's extra layers.
 * @param renderer Renderer.
 * @param layer Layer number, from 1.
 */
extern "C" s32 func_004D0B10(LibRenderer* renderer, u32 layer);

/** Reciprocal of g_frame_ticks, refreshed each frame. */
extern float g_inverse_frame_ticks;

extern "C" LibBusyObject* D_001B65FC;
extern "C" u64 D_001B65C8;

/**
 * @brief Queue the busy object on a channel.
 * @param object Busy object.
 * @param channel Channel number.
 * @return Queue status.
 */
extern "C" s32 func_004D9A80(LibBusyObject* object, u8 channel);

extern "C" void func_004C8390(LibDisplayManager* manager);

/**
 * @brief Return the frame buffer page of the draw buffer the display is on.
 * @param display Display to read.
 * @return FRAME base pointer of the second drawing context of draw buffer 0 or 1.
 */
extern "C" s32 func_004DBC70(LibCameraContext* display);

extern "C" u64 func_004DBCA0(LibCameraContext* display, s32 index);

/** Transform with local vectors, a cached matrix, and a parent link. */
class LibTransform : public LibTransformOwner
{
public:
    /** @brief Initialize the object and its transform state. */
    LibTransform();

    /** @brief Destroy the object. */
    virtual ~LibTransform();

    /**
     * @brief Read the additional local translation.
     * @return Stored translation vector; only xyz is used to build the offset matrix.
     */
    virtual const LibVector4* get_offset_translation() const;

    /**
     * @brief Read the additional local rotation.
     * @return Stored quaternion in x, y, z, w order.
     */
    virtual const LibVector4* get_offset_rotation() const;

    /**
     * @brief Read the additional local scale.
     * @return Stored scale vector; only xyz is used to build the offset matrix.
     */
    virtual const LibVector4* get_offset_scale() const;

    /**
     * @brief Copy local transform state and its inherited state.
     * @param source Transform to copy.
     */
    virtual void copy_offset_transform_state(const LibTransform* source);

    /** @brief Update transform state relative to the current camera. */
    virtual void update();

    /** @brief Update the cached transformation matrices. */
    virtual void update_transform_matrix();

    /**
     * @brief Read the cached combined transformation matrix.
     * @return Pointer to the stored matrix; this call does not update it.
     */
    virtual const LibMatrix44Value* get_transform_matrix();

    /**
     * @brief Move a world-space position into the transform's local space.
     * @param world Position in world space.
     * @param local Receives the position in local space.
     */
    void to_local(const LibVector4* world, LibVector4* local);

    LibMatrix44Value transform;
    LibMatrix44Value base_transform;
    LibMatrix44Value offset_transform;
    LibMatrix44Value transposed_transform;
    LibMatrix44Value inverse_transform;
    LibVector4 offset_translation;
    LibVector4 offset_rotation;
    LibVector4 offset_scale;
    float unk200;
    float unk204;
    LibTransform* parent_transform;
    u16 unk20c;
    u8 unk20e_0 : 1;
    u8 unk20e_1 : 1;
    u8 unk20e_2 : 1;
    u8 unk20e_3 : 1;
    u8 unk20e_4 : 1;
    u8 unk20e_5_7 : 3;
    u8 unk20f;
};

/**
 * @brief Read the parent's combined matrix, updating the parent first if needed.
 * @param object Transform whose parent is read.
 * @return Parent's base transform, or null without a parent.
 */
static inline const LibMatrix44Value* lib_get_parent_matrix(LibTransform* object)
{
    if (object->parent_transform == 0)
    {
        return 0;
    }

    if (!object->parent_transform->matrix_ready)
    {
        object->parent_transform->update_transform_matrix();

        if (object->parent_transform->unk51)
        {
            object->transform_dirty = 1;
        }
    }

    return &object->parent_transform->base_transform;
}

/**
 * @brief View one row of a matrix as a vector.
 * @param matrix Matrix.
 * @param row Row index.
 * @return The row.
 */
static inline const LibVector4* matrix_row(const LibMatrix44Value* matrix, s32 row)
{
    return (const LibVector4*)matrix->m[row];
}

/**
 * @brief Multiply the transform's unk200 factor by its parents', climbing parent_transform while bit 0x200 of unk20c
 * is set.
 * @param transform Transform to start from.
 * @return The combined factor.
 */
extern "C" float func_004DA0F0(LibTransform* transform);

/** Transform that faces an optional target with a roll about the viewing direction. */
class LibLookAtTransform : public LibTransform
{
public:
    /** @brief Initialize the transform without a look-at target or roll. */
    LibLookAtTransform();

    virtual ~LibLookAtTransform();

    /**
     * @brief Copy the look-at target and inherited transform state.
     * @param source Transform to copy; its roll angle is not copied.
     */
    virtual void copy_look_at_state(const LibLookAtTransform* source);

    /** @brief Update the matrix to face the target when one is attached. */
    virtual void update_transform_matrix();

    LibTransform* look_at_target;
    float roll_angle;
};

/**
 * 16-byte vector that Lib keeps its constructors and identity setter out of line for: LibClass173490's grid arrays
 * and a light's colour, position and direction.
 */
struct LibClass173490Entry
{
    inline LibClass173490Entry();

    /**
     * @brief Set all four components to one value.
     * @param value Value for every component.
     */
    inline LibClass173490Entry(float value);

    /**
     * @brief Set the four components.
     * @param px First component.
     * @param py Second component.
     * @param pz Third component.
     * @param pw Fourth component.
     */
    LibClass173490Entry(float px, float py, float pz, float pw)
    {
        x = px;
        y = py;
        z = pz;
        w = pw;
    }

    /**
     * @brief Copy all 16 bytes.
     * @param other Element to copy.
     * @return This element.
     */
    LibClass173490Entry& operator=(const LibClass173490Entry& other)
    {
        *(unsigned __int128*)this = *(const unsigned __int128*)&other;
        return *this;
    }

    /** @brief Set the vector to (0, 0, 0, 1). */
    inline void set_identity();

    float x;
    float y;
    float z;
    float w;
};

/**
 * @brief Copy a light vector as one 128-bit value, like copy_vector does for LibVector4.
 * @param destination Vector receiving the copy.
 * @param source Vector to copy.
 */
static inline void copy_vector(LibClass173490Entry* destination, const LibClass173490Entry* source)
{
    *(unsigned __int128*)destination = *(const unsigned __int128*)source;
}

/**
 * @brief Copy a vector into a light vector as one 128-bit value.
 * @param destination Vector receiving the copy.
 * @param source Vector to copy.
 */
static inline void copy_vector(LibClass173490Entry* destination, const LibVector4* source)
{
    *(unsigned __int128*)destination = *(const unsigned __int128*)source;
}

/**
 * @brief Copy a light vector into a vector as one 128-bit value.
 * @param destination Vector receiving the copy.
 * @param source Vector to copy.
 */
static inline void copy_vector(LibVector4* destination, const LibClass173490Entry* source)
{
    *(unsigned __int128*)destination = *(const unsigned __int128*)source;
}

/** Partial light, kept in g_light_list, with vtable 0x1789E0 in main data. */
class LibLight : public LibLookAtTransform
{
public:
    /** @brief Start as a white type-3 light with the default cone and ranges, every mask bit and no direction. */
    LibLight() : color(1.0f)
    {
        cone_angle = 40.0f;
        packed_intensity = 0.0f;
        unk268 = 480.0f;
        unk274 = 0.0f;
        unk278 = 44.0f;
        unk27c = 1.0f;
        unk288 = 0;
        unk289 = 0;
        unk28a = 0;
        unk28b = 0;
        unk28c = 0;
        unk28d = 0;
        unk28e = 0;
        enabled = 0;
        unk290 = 0;
        unk291 = 0;
        kind = 0;
        mask = 7;
        set_light_type(3);
        direction.set_identity();
    }

    virtual ~LibLight();

    /** @brief Face the look-at target, if any, by turning the light's orientation towards it, then update the matrix. */
    virtual void update_transform_matrix();

    /**
     * @brief Copy another light's colour, frame, cone and flags.
     * @param source Light to copy.
     */
    virtual void copy_light_state(const LibLight* source);

    /** @brief Update the transform matrix if it isn't ready, then cache the position and direction from it. */
    void update_frame();

    inline void set_light_type(u32 type);

    LibClass173490Entry color;
    LibClass173490Entry tinted_color;
    LibClass173490Entry position;
    LibClass173490Entry direction;
    float cone_angle;
    float packed_intensity;
    float unk268;
    float unk26c;
    float unk270;
    float unk274;
    float unk278;
    float unk27c;
    float unk280;
    float unk284;
    u8 unk288;
    u8 unk289;
    u8 unk28a;
    u8 unk28b;
    u8 unk28c;
    u8 unk28d;
    u8 unk28e;
    u8 enabled;
    u8 unk290;
    u8 unk291;
    s32 kind;
    u32 mask;
};

/**
 * @brief Cache the spotlight's cone falloff terms from the cosines of its two half-angles.
 * @param light Spotlight to update.
 */
extern "C" void func_004C9BA0(LibLight* light);

/**
 * @brief Invert the transform's transposed matrix into its inverse transform.
 * @param transform Transform whose transposed_transform is up to date.
 */
extern "C" void func_004D9E70(LibTransform* transform);

class LibResourceBuffer;
struct LibRenderDataRecord;
struct LibImageSequenceHeader;

/** Image-sequence channel backed by linked FIS chunks. */
class LibImageSequenceChannel : public LibRenderChannel
{
public:
    /** @brief Initialize an empty image-sequence channel. */
    LibImageSequenceChannel();

    /** @brief Release the image-pointer table and destroy the channel base. */
    virtual ~LibImageSequenceChannel();

    /**
     * @brief Select the image for the stored frame position.
     *
     * The sequence duration must be nonzero and covered by its frame durations.
     */
    virtual void update();

    /**
     * @brief Report the stored sequence's image count.
     * @return Image count, or zero when no sequence header is stored.
     */
    virtual s32 get_entry_count();

    /**
     * @brief Read an indexed image pointer.
     * @param index Caller-validated image index.
     * @return Image pointer at index.
     */
    virtual void* get_entry(s32 index);

    /**
     * @brief Bind a resource record and build its image-pointer table.
     *
     * Offsets are relative to the first image chunk in the chain.
     * Rebinding does not release an older entry table.
     * @param record Resource record containing inline or resolved image chunks.
     * @param use_inline True to select inline chunks even when a data pointer is set.
     * @return True when a sequence is found and its pointer table is allocated.
     */
    bool bind_record(LibRenderDataRecord* record, bool use_inline);

    /**
     * @brief Bind the selected record from the source resource.
     * @return True when no record is bound or binding succeeds; false for a missing resource or failed binding.
     */
    bool load_resource();

    s32 frame;
    LibRenderDataRecord* target;
    void** entries;
    const LibImageSequenceHeader* sequence;
    LibResourceBuffer* resource;
};

/**
 * @brief Copy a complete local vector.
 * @param output Destination vector.
 * @param input Source vector.
 */
extern "C" void func_004DA040(LibVector4* output, const LibVector4* input);

/**
 * @brief Return the transform's 16-bit state value.
 * @param object Transform owner.
 * @return Stored state value.
 */
extern "C" u16 func_004DA2B0(const LibTransform* object);

/**
 * @brief Extract the transform's translation column.
 * @param object Transform owner.
 * @return Translation coordinates with homogeneous component one.
 */
extern "C" FieldVec4B func_004DA6F0(const LibTransform* object);

/**
 * @brief Store the local scalar and update its threshold flag.
 * @param object Transform receiver.
 * @param value Local scalar value.
 */
extern "C" void func_004DA050(LibTransform* object, float value);

/**
 * @brief Rebuild the offset matrix from the stored translation, quaternion and scale.
 * @param object Transform whose offset matrix is updated.
 */
extern "C" void lib_rebuild_offset_transform(LibTransform* object);

/**
 * @brief Mark each transform in the parent chain dirty.
 * @param object First transform, or null.
 */
extern "C" void lib_invalidate_transform_chain(LibTransform* object);

/**
 * @brief Turn the joints above a transform so that it reaches toward a target (cyclic coordinate descent).
 * @param end Transform at the end of the chain.
 * @param target Target point, in the same space as the base transforms.
 * @param links Most parent joints to turn per iteration.
 * @param iterations Most passes over the chain.
 * @param include_root Nonzero to also turn the chain's root.
 * @param weight Fraction of each joint's full correction to apply.
 */
extern "C" void lib_solve_ik_chain(LibTransform* end, const LibVector4* target, s32 links, s32 iterations, s32 include_root,
                                   float weight);

/**
 * @brief Finish an object's packet once its DMA completes.
 * @param object Object whose packet completed.
 */
extern "C" void lib_finish_packet(LibTransformOwner* object);
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief LibRenderer::begin_frame, for modules that only have an untyped view of the renderer.
 * @param object Renderer.
 */
void func_4D4BE0(void* object);

/**
 * @brief LibScreenText::begin, for modules that only have their own view of the printer.
 * @param object Screen text printer.
 * @param x Left margin in screen pixels.
 * @param y Top line in screen pixels.
 */
void func_4D76C0(void* object, u16 x, u16 y);

#ifdef __cplusplus
/**
 * @brief Interpolate along the shorter quaternion arc and normalize the result.
 *
 * Same result as lib_quaternion_slerp, but the sines run on the VU0 microprogram while the CPU waits.
 * @param output Aligned destination quaternion; may alias either input.
 * @param first First aligned quaternion.
 * @param second Second aligned quaternion.
 * @param fraction Interpolation fraction.
 */
void lib_quaternion_slerp_async(FieldVec4B* output, const FieldVec4B* first, const FieldVec4B* second, float fraction);

/**
 * @brief Interpolate along the shorter quaternion arc and normalize the result.
 * @param output Aligned destination quaternion; may alias either input.
 * @param first First aligned quaternion.
 * @param second Second aligned quaternion.
 * @param fraction Interpolation fraction.
 */
void lib_quaternion_slerp(FieldVec4B* output, const FieldVec4B* first, const FieldVec4B* second, float fraction);

/**
 * @brief Add all four components to a quaternion and return its updated value.
 * @param first Quaternion to update.
 * @param second Quaternion components to add.
 * @return Copy of the updated quaternion.
 */
FieldVec4B lib_quaternion_add_assign(FieldVec4B& first, const FieldVec4B& second);

/**
 * @brief Multiply a quaternion by a second quaternion and return its updated value.
 * @param first Quaternion to update with first * second.
 * @param second Right-hand quaternion factor.
 * @return Copy of the updated quaternion.
 */
FieldVec4B lib_quaternion_multiply_assign(FieldVec4B& first, const FieldVec4B& second);

/**
 * @brief Divide a quaternion's conjugate by its squared norm.
 * @param quaternion Quaternion to invert.
 * @return Inverse quaternion.
 */
FieldVec4B lib_quaternion_inverse(const FieldVec4B& quaternion);

/**
 * @brief Replace a position with direction angles toward a target, using the XY plane for heading.
 * @param value Source position, overwritten with elevation in x, heading in z, and w set to one.
 * @param target Target position; only x, y, and z are read.
 * @param y_angle Angle to store in the y component.
 */
void lib_direction_angles_xy(LibVector4* value, const LibVector4* target, float y_angle);

/**
 * @brief Convert rotation angles to an orientation quaternion.
 * @param orientation Receives the quaternion.
 * @param angles Rotation angles in xyz.
 */
void func_004CDBC0(LibVector4* orientation, const LibVector4* angles);

/**
 * @brief Replace a position with direction angles toward a target, using the XZ plane for heading.
 * @param value Source position, overwritten with elevation in x, heading in y, and w set to one.
 * @param target Target position; only x, y, and z are read.
 * @param z_angle Angle to store in the z component.
 */
void lib_direction_angles_xz(LibVector4* value, const LibVector4* target, float z_angle);

/**
 * @brief Build the unit quaternion for three rotation angles.
 *
 * The x and y angles turn about the negative axes and z about the positive axis.
 * @param output Receives the quaternion.
 * @param angles Angles in radians about x, y and z.
 */
void lib_quaternion_from_euler(FieldVec4B* output, const float* angles);
#endif

/**
 * @brief Pass a batch of table entry handles to the manager.
 * @param manager Manager object that receives the entries.
 * @param count Number of entries.
 * @param entries Entry handles.
 */
void func_004D4010(void* manager, s32 count, void** entries);

/**
 * @brief Compare two strings for equality up to a signed character limit.
 * @param first First string.
 * @param second Second string.
 * @param count Maximum characters to compare; nonpositive limits compare none.
 * @return Zero when the compared characters match, otherwise one.
 */
s32 lib_compare_bounded_strings(const char* first, const char* second, s32 count);

/**
 * @brief Update one node of an update list.
 * @param list Update list that owns the node; unused.
 * @param node Node to update.
 */
void lib_update_list_update_node(void* list, void* node);



/**
 * @brief Release heap storage, choosing between two resident heap release routines by a resident flag.
 *
 * Several Field classes route their operator delete here; the Lib list class's own
 * deleting destructor uses the global operator delete instead.
 * @param object Storage to release; null is ignored.
 */
void func_004DB570(void* object);

/** VRAM allocator: hands out texture space after the display's buffers. */
typedef struct LibVramAllocator
{
    u32 base_address;
    u32* unk04;
    u32* allocations;
    s16 unk04_count;
    s16 allocation_count;
    s16 unk04_capacity;
    s16 allocation_capacity;
    u32 unk14;

#ifdef __cplusplus
    /**
     * @brief Allocate the two tables, with the end address at 0x100000 words.
     * @param first_capacity Entries in unk04.
     * @param allocation_capacity Entries in allocations.
     */
    LibVramAllocator(s16 first_capacity, s16 allocation_capacity);

    /** @brief Free the allocation tables. */
    virtual ~LibVramAllocator();
#endif
} LibVramAllocator;

/**
 * @brief Build the CLUT half of a TEX0 value for a VRAM slot.
 * @param vram Allocator holding the slot's CLUT address.
 * @param slot VRAM slot.
 * @param entry CLUT entry offset (CSA).
 * @param mode CLUT load mode.
 * @return CBP, CSA and CLD bits of TEX0.
 */
u64 func_004DC800(LibVramAllocator* vram, s16 slot, s16 entry, s32 mode);

/**
 * @brief Measure how far the allocator's unk14 address is past its base address.
 * @param vram VRAM allocator.
 * @return Distance in words.
 */
u32 func_004DC7F0(LibVramAllocator* vram);

/**
 * @brief Upload an image to a VRAM slot.
 * @param image Decoded image.
 * @param slot VRAM slot.
 * @return Negative on failure.
 */
s32 func_004D8D20(u8* image, s32 slot);

/** 16x16 CT32 image (256 colors) in Lib data. */
extern const u32 D_004EC600[];

/**
 * @brief Reserve VRAM for a 16 by 16 CT32 image and queue its upload.
 * @param colors Pixels to upload.
 * @param slot VRAM slot to reuse, or -1 for a new one.
 * @return The slot, or -1 when the packet can't be allocated.
 */
s16 func_004D8C20(const void* colors, s32 slot);

/** The game's VRAM allocator. */
extern LibVramAllocator* g_vram_allocator;

/**
 * @brief Allocate an aligned area from the texture side of the VRAM allocator.
 * @param vram Allocator.
 * @param size Size in bytes.
 * @param alignment Alignment in bytes.
 * @param slot Slot to reuse, or -1 for a new one.
 * @return Slot of the area, or -1 when VRAM is full.
 */
s16 func_004DCA70(LibVramAllocator* vram, u32 size, u32 alignment, s16 slot);

/** @brief Fill all of VRAM with zeros, one 256x256 32-bit upload at a time. */
void lib_clear_vram(void);

/**
 * @brief Empty the allocator and make it start allocating at a VRAM page.
 * @param vram Allocator.
 * @param page First VRAM page to hand out.
 */
void lib_vram_reset(LibVramAllocator* vram, u32 page);

/**
 * @brief Clear the display's halfword at 0x3E78 and toggle the one at 0x3E7A.
 * @param display Display to update.
 */
void func_004DBB70(struct LibCameraContext* display);

/**
 * @brief Detach the object from the owner stored at offset 0x10, then clear that pointer.
 * @param object Object to detach; the owner receives it through its virtual handler at vtable offset 0x1C.
 */
void lib_object_detach_owner(void* object);

/**
 * @brief Get the next node in a circular list traversal.
 * @param node Current node or list sentinel.
 * @return Next node, which may be the list sentinel.
 */
LibListNode* func_004D6DD0(const LibListNode* node);

/**
 * @brief Read the signed index used to select a node output counter.
 * @param node Current list node.
 * @return The sign-extended index value.
 */
s32 func_004D6DB0(const LibListNode* node);

/**
 * @brief Return the supplied object pointer.
 * @param object Object or subobject pointer.
 * @return The same pointer.
 */
void* func_004D6DE0(void* object);


/**
 * @brief Wait until the object's busy flag clears.
 * @param object Object to wait on.
 */
void func_004D99B0(LibBusyObject* object);

/**
 * @brief Queue the object again when its DMA channel changes.
 * @param object Transfer object implementing the DMA callbacks.
 * @param channel Requested DMA channel.
 */
void func_004D9AB0(LibBusyObject* object, u8 channel);

/**
 * @brief Pass the pointer at offset 0x634 and the remaining arguments to a helper.
 * @param receiver Object containing the pointer.
 * @param arg1 First value passed to the helper.
 * @param arg2 Second value passed to the helper.
 * @return What the helper returns.
 */
void* func_004D6230(void* receiver, u32 arg1, u32 arg2);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_004D66F0(void* object);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

#endif

#ifdef __cplusplus
extern "C" {
#endif

/** Lib's queue of GS packet operations. */
typedef struct LibPacketQueue LibPacketQueue;

/** The game's packet queue. */
extern LibPacketQueue* g_packet_queue;

/** The queue the DMA channel 2 interrupt handler serves; set by the newest queue's constructor. */
extern LibPacketQueue* g_interrupt_packet_queue;

/**
 * @brief Finish the packet operation at the queue's head: release an image upload's buffers when asked and tell
 * the operation's completion object.
 * @param queue Packet queue.
 */
void func_004DBFB0(LibPacketQueue* queue);

/**
 * @brief DMA channel 2 interrupt handler: finish the current packet operation and start the next.
 * @param channel DMA channel.
 * @return One.
 */
s32 func_004DC140(s32 channel);

/**
 * @brief Sync the GS path once the packet queue is full; with a zero flag, wait for that.
 * @param queue Packet queue.
 * @param flag Nonzero checks once and syncs with that value; zero waits until the queue is full and syncs with zero.
 * @return The sync result, or 0x8000 when the queue had room.
 */
s32 func_004DBEE0(LibPacketQueue* queue, s32 flag);

/**
 * @brief Start the next queued packet operation when the queue has work and is enabled.
 * @param queue Packet queue.
 * @param value Passed on by the DMA completion path; func_004DC420 passes zero.
 */
void func_004DC200(LibPacketQueue* queue, s32 value);

/**
 * @brief Test whether a live entry holds an operation for a packet.
 * @param queue Packet queue.
 * @param operation Operation number.
 * @param packet Packet or object the operation is for.
 * @return One when such an entry is queued.
 */
s32 func_004DC180(LibPacketQueue* queue, u16 operation, const void* packet);

/**
 * @brief Let queued packets start, or hold them back.
 * @param queue Packet queue.
 * @param enable Nonzero lets packets start.
 */
void func_004DC420(LibPacketQueue* queue, s32 enable);

/**
 * @brief Test whether the packet queue is full.
 * @param queue Packet queue.
 * @return Nonzero when no more operations fit.
 */
s32 func_004DBD80(LibPacketQueue* queue);

/**
 * @brief Queue a packet operation, and start the queue if it's idle.
 * @param queue Packet queue.
 * @param operation Operation number.
 * @param flags Operation flags.
 * @param packet Packet to send, or the object the operation is for.
 * @param value Operation value, such as a quadword count.
 * @param completion Object told when the operation finishes, or null.
 * @return One when queued, zero when the queue is full.
 */
u8 func_004DC4F0(LibPacketQueue* queue, u32 operation, u32 flags, const void* packet, u32 value, void* completion);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

#define LIB_PACKET_ENTRY_LIVE 0x8000

#define LIB_PACKET_LOAD_IMAGE 1

enum
{
    /** Release the queued LibImageUpload record once its operation finishes. */
    LIB_PACKET_FREE_RECORD = 1,

    /** Release the record's pixels once its operation finishes. */
    LIB_PACKET_FREE_PIXELS = 2
};

/** A LIB_PACKET_LOAD_IMAGE operation's packet: the GS image transfer and the pixels it sends. */
struct LibImageUpload
{
    GsLoadImage packet;
    const void* pixels;
};

/** One queued packet operation, as func_004DC4F0 stores it. */
struct LibPacketQueueEntry
{
    u16 operation;
    u16 flags;
    const void* packet;
    u32 value;
    LibDmaCallbacks* completion;
};

/** Partial Lib packet queue; its vtable D_00178F90 comes after its data. */
struct LibPacketQueue
{
    s32 unk00;
    LibPacketQueueEntry* entries;
    s16 capacity;

    // TODO: Volatile because the wait loop in func_004DBEE0 reloads both every pass; the DMA side moves them.
    volatile s16 write_index;
    volatile s16 read_index;
    u8 unk0E;
    u8 unk0F;
    u8 enabled;
    u8 unk11;

    /**
     * @brief Allocate the entries and install the DMA channel 2 interrupt handler.
     * @param capacity Number of entries.
     */
    LibPacketQueue(s16 capacity);

    /** @brief Destroy the queue. */
    virtual ~LibPacketQueue();
};
#endif

#ifdef __cplusplus

/** Temporary object-node buffer. */
class LibClass178B10 : public LibListObject
{
public:
    LibClass178B10(s32 count);

    virtual ~LibClass178B10();

    void** objects;
    s32 count;
    u32 unk1c;
    u8 unk20[4];
};
#endif

#ifdef __cplusplus
/**
 * DMA submission that sends a VIF0 tag chain, picked by its channel byte from the global table or, from 0x80 up, from
 * its own; the queue helpers above use it through LibBusyObject. Vtable D_178E70 in main data.
 */
class LibVif0Channel : public DmaSubmission
{
public:
    /** @brief Start idle with no channel and seed VU0's random register. */
    LibVif0Channel();

    /**
     * @brief Mark the transfer done.
     * @param dma_channel DMA channel; unused.
     */
    virtual void complete_dma(u32 dma_channel);

    /**
     * @brief Start the channel's VIF0 tag chain.
     * @param dma_channel DMA channel; unused.
     */
    virtual void submit_dma(u32 dma_channel);

    u8 unk04[0x4C];
    volatile u8 busy;
    u8 channel;
    u8 unk52[2];
    u32 unk54;
    u32 tags[18];
};

/** DMA callbacks object g_display_callbacks that records the display (vtable D_0014FDE0 in main data). */
class LibDebugListener : public LibDmaCallbacks
{
public:
    /**
     * @brief Record the display.
     * @param display Display.
     */
    LibDebugListener(LibCameraContext* display) : display(display)
    {
    }

    /**
     * @brief Main's reserved hook.
     * @param value Notification value.
     */
    virtual void on_packet_notify(u32 value);

    /**
     * @brief Main's debug notification.
     * @param value Notification word or packet address.
     */
    virtual void on_packet_complete(u32 value);

    LibCameraContext* display;
};

/**
 * Update list that is also a list object, with vtables D_0014FCB0 and D_0014FCE8 in main data (main's
 * ResidentUpdateList), made by lib_initialize.
 */
class LibResidentUpdateList : public LibUpdateList, public LibListObject
{
public:
    /** @brief Start with unk8c clear. */
    LibResidentUpdateList() : unk8c(0)
    {
    }

    virtual ~LibResidentUpdateList();

    u32 unk8c;
};

/** Transform owner with vtable D_00174570 in main data that sends its display manager's effect packet. */
class LibClass174570 : public LibTransformOwner
{
public:
    /** @brief Start as a type 0x800 object with draw flag 0x400. */
    LibClass174570()
    {
        unk65 = 1;
        type_id = 0x800;
        draw_flags = 0x400;
    }

    virtual ~LibClass174570();

    /** @brief Send the effect display's ready packet and finish this object's packet. */
    virtual void render();

    /** @brief Draw in bucket 8. */
    virtual void set_default_draw_bucket();

    /**
     * @brief Return a bounding sphere at the origin with a huge radius, so the object is never culled.
     * @return Bounding sphere; it lives on this function's stack.
     */
    virtual const LibVector4* get_bounding_sphere();

    /**
     * @brief Promote the effect display's pending packet to the ready one when the effect is on.
     * @param matrix Unused.
     * @param context Unused.
     */
    virtual void build_packet(const void* matrix, void* context);

    LibDisplayManager* manager;
};
#endif

#ifdef __cplusplus
/** List object with vtable D_178C90 in main data that runs the renderer's frame passes. */
class LibClass178C90 : public LibListObject
{
public:
    /**
     * @brief Run the given renderer's passes, on the scratchpad stack.
     * @param renderer Renderer.
     */
    LibClass178C90(LibRenderer* renderer) : renderer(renderer)
    {
        object_kind |= 4;
    }

    virtual ~LibClass178C90();

    /**
     * @brief Return the list kind.
     * @return Ten.
     */
    virtual s32 get_default_list_kind();

    /** @brief Run the renderer's per-frame passes, then its light steps. */
    virtual void update();

    LibRenderer* renderer;
};
#endif


#endif
