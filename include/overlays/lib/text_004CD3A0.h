#ifndef SO3_OVERLAYS_LIB_TEXT_004CD3A0_H
#define SO3_OVERLAYS_LIB_TEXT_004CD3A0_H

#include "types.h"
#include "gs.h"
#include "ee.h"
#include "overlays/lib/text_003E68C0.h"
#include "overlays/lib/counted_list.h"
#include "overlays/lib/render_channel.h"
#include "overlays/lib/vector.h"

/** Partial object with a busy flag that something else clears; the rest is unknown. */
typedef struct LibBusyObject
{
    u8 unk00[0x50];
    /** Nonzero while the object is busy. It changes outside the code that waits on it. */
    volatile u8 busy;
    /** Channel selector stored with the queued DMA submission. */
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

/** VU1 microprograms Lib can load. */
#define LIB_VU1_PROGRAM_COUNT 11

/** LibMicrocodeLoader::current_program before any program is loaded. */
#define LIB_VU1_PROGRAM_NONE 0xFF

/** Data of each VU1 microprogram, for LibMicrocodeLoader::select_program. */
extern "C" const void* const lib_vu1_programs[LIB_VU1_PROGRAM_COUNT];

/** DMA chain that uploads Lib's resident VU1 microcode. */
extern "C" u8 lib_vu1_upload_chain[];

/** Tracks which VU1 microprogram is loaded, with vtable D_178E80 in main data. */
class LibMicrocodeLoader : public DmaSubmission
{
public:
    /** @brief Start with no program and an empty upload packet. */
    LibMicrocodeLoader();

    /**
     * @brief Send the resident microcode upload chain on VIF1.
     * @param channel DMA channel; unused.
     */
    virtual void submit_dma(u32 channel);

    /**
     * @brief Nothing to do once the upload finishes.
     * @param channel DMA channel; unused.
     */
    virtual void complete_dma(u32 channel);

    /** @brief Forget the loaded program and queue the resident microcode upload. */
    void start_upload();

    /**
     * @brief Switch to a microprogram.
     * @param program Program index.
     * @return The program's data when it has to be uploaded, or null when it's already loaded.
     */
    const void* select_program(s32 program);

    /**
     * @brief Return the DMA tag that uploads a microprogram.
     * @param program Program index.
     * @return DMA REF tag.
     */
    u64 get_program_tag(s32 program);

    u8 unk04;

    /** Program now in VU1 micro memory, or LIB_VU1_PROGRAM_NONE. */
    u8 current_program;

    u8 unk06;
    u8 unk07[0xD];
    u32 unk14[3];
    u32 unk20[3];

    /** VIF FLUSH code that ends the packet. */
    u32 flush;
};

/** Lib's VU1 microcode loader, made by lib_initialize. */
extern LibMicrocodeLoader* g_microcode_loader;

/** Aligned four-row matrix whose assignment returns a copy of the matrix. */
class LibMatrix44Value
{
public:
    /** @brief Leave the matrix uninitialized. */
    LibMatrix44Value()
    {
    }

    /** @brief Set the matrix to the identity transformation. */
    void set_identity();

    /** @brief Copy all sixteen components. @param other Matrix to copy. */
    LibMatrix44Value(const LibMatrix44Value& other)
    {
        ((unsigned __int128*)this)[0] = ((const unsigned __int128*)&other)[0];
        ((unsigned __int128*)this)[1] = ((const unsigned __int128*)&other)[1];
        ((unsigned __int128*)this)[2] = ((const unsigned __int128*)&other)[2];
        ((unsigned __int128*)this)[3] = ((const unsigned __int128*)&other)[3];
    }

    /** @brief Copy all components. @param other Source matrix. @return A copy of this matrix. */
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

extern "C"
{
    /**
     * @brief Normalize the first three floating-point components in place.
     * @param value At least three components with nonzero squared length.
     */
    void lib_normalize_vector3(float* value);

    /**
     * @brief Convert a quaternion by mapping each matrix row from (x, y, z) to (x, -z, y).
     * @param quaternion Source quaternion.
     * @return Quaternion extracted from the converted matrix.
     */
    FieldVec4B func_004CD570(const FieldVec4B& quaternion);
    /** @brief Invert an orthonormal rotation and its row-vector translation. @param input Source matrix. @param output Destination matrix, distinct from input. */
    void func_004CEF20(const LibMatrix44Value* input, LibMatrix44Value* output);
    /** @brief Invert an orthonormal rotation and its translation column. @param input Source transformation matrix. @return Inverse transformation matrix. */
    LibMatrix44Value func_004CF0B0(const LibMatrix44Value& input);
    /** @brief Invert a nonsingular matrix. @param input Source matrix. @param output Destination matrix, which may alias input. */
    void func_004CF1C0(const LibMatrix44Value* input, LibMatrix44Value* output);
    /** @brief Multiply a matrix by a column vector. @param matrix Source matrix. @param value Source vector. @return Transformed vector. */
    FieldVec4A func_004CF6C0(const LibMatrix44Value& matrix, const FieldVec4A& value);
    /**
     * @brief Combine two matrices with the VU0 microprogram at 0x250.
     * @param left First matrix (vf1-vf4).
     * @param right Second matrix (vf5-vf8).
     * @return Combined matrix.
     */
    LibMatrix44Value func_004CF7C0(const LibMatrix44Value& left, const LibMatrix44Value& right);
    /** @brief Multiply a row vector by a matrix. @param value Source vector. @param matrix Source matrix. @return Transformed vector. */
    FieldVec4A func_004CF830(const FieldVec4A& value, const LibMatrix44Value& matrix);
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
    /** @brief Set the upper 3x3 rotation from three angles. @param output Matrix whose rotation is updated. @param angles Three rotation angles in radians. */
    void func_004CFDE0(LibMatrix44Value* output, const float* angles);
    /** @brief Set the upper 3x3 rotation about the Y axis. @param output Matrix whose rotation is updated. @param angle Rotation angle in radians. */
    void func_004CFEE0(LibMatrix44Value* output, float angle);
    /** @brief Clear all sixteen matrix components. @param matrix Matrix to clear. */
    void func_004CFF80(LibMatrix44Value* matrix);
    /** @brief Extract three rotation components from a matrix. @param angles Destination for three floats. @param matrix Transformation matrix. */
    void func_004CEBA0(float* angles, const LibMatrix44Value* matrix);
    /** @brief Extract rotation components from a quaternion. @param angles Destination rotation vector. @param quaternion Source quaternion. */
    void func_004CDA40(LibVector4* angles, const LibVector4* quaternion);
    /** @brief Normalize a quaternion in place. @param quaternion Quaternion to normalize. */
    void lib_normalize_quaternion(FieldVec4B* quaternion);
    /**
     * @brief Build the unit quaternion for a rotation about an axis.
     * @param output Receives the quaternion.
     * @param axis_angle Axis in x, y and z, angle in radians in w.
     */
    void lib_quaternion_from_axis_angle(FieldVec4B* output, const LibVector4* axis_angle);
    /** @brief Convert a quaternion to a matrix. @param quaternion Rotation to convert. @return Rotation matrix. */
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
    /** @brief Transpose a matrix. @param input Source matrix. @return Transposed matrix. */
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

/** Entries a texture cache tracks; entry 0 is the head of the most-recently-used list. */
#define LIB_TEXTURE_CACHE_ENTRY_COUNT 256

/** Most CLUTs a texture cache can hold. */
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
    /** Texture ID the block holds. */
    u32 id;

    /** Start of the block, in the units of LibTextureCache::texture_address. */
    u32 address;

    /** Size of the block. */
    u32 size;

    u8 previous_block;
    u8 next_block;

    /** LibTextureBlockState. */
    u8 state;

    /** Cache stamp of the last lookup that found the texture. */
    u8 stamp;
};

/** One CLUT record of a texture cache. */
struct LibTextureClut
{
    u32 unk00;
    u8 unk04[4];

    /** CLUT half of TEX0 (CBP and CPSM) for textures that use it. */
    u64 tex0;
};

/** Partial value half of a cache entry. */
struct LibTextureEntry
{
    u32 tag;
    LibTextureUser* user;

    /** TEX0 value for the texture; TBP0 gives its VRAM address. */
    u64 tex0;
};

/** VRAM area a texture cache miss asks for. */
struct LibTextureRequest
{
    s16 width;
    s16 height;
    s32 size;
    u8 unk08[4];

    /** GS pixel storage mode (1 is PSMCT24). */
    s16 psm;

    /** Texture width as a power of two (TEX0's TW). */
    u8 width_log2;

    /** Texture height as a power of two (TEX0's TH). */
    u8 height_log2;
};

/** Request tag ('MlPs') whose misses are only loaded when an address is wanted. */
#define LIB_TEXTURE_TAG_MLPS 0x4D6C5073

/** Highest and lowest priority a cached texture's user can reach. */
#define LIB_TEXTURE_PRIORITY_MAX 10
#define LIB_TEXTURE_PRIORITY_MIN -10

/** Lowest priority at which a hit still moves a user's texture to the front. */
#define LIB_TEXTURE_PRIORITY_KEEP -5

/** Partial 0x2910-byte VRAM texture cache (g_texture_cache). It may sit at the start of scratchpad memory. */
class LibTextureCache
{
public:
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
     * @brief Allocate the cache through the resident allocator.
     * @param size Object size in bytes.
     * @param heap Heap selector.
     * @return The allocated storage.
     */
    static void* operator new(u32 size, s32 heap)
    {
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
    u32 find_texture(LibTextureRequest* request, u32 tag, u32 id, s32 slot, s32 unk5, s32 want_address,
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

    /** VRAM slot of the texture area. */
    s16 texture_slot;

    /** VRAM slot of the CLUT area. */
    s16 clut_slot;

    u32 unk04;

    /** VRAM blocks of the texture area; record 0 heads the list. */
    LibTextureBlock blocks[LIB_TEXTURE_CACHE_ENTRY_COUNT];

    LibTextureEntry entries[LIB_TEXTURE_CACHE_ENTRY_COUNT];
    u8 next[LIB_TEXTURE_CACHE_ENTRY_COUNT];
    u8 previous[LIB_TEXTURE_CACHE_ENTRY_COUNT];

    /** Size of the texture area in bytes. */
    s32 texture_size;

    u32 unk220c;
    u32 unk2210;
    u8 unk2214[4];

    /** CLUT records, clut_count of them. */
    LibTextureClut cluts[LIB_TEXTURE_CACHE_MAX_CLUTS];

    u8 unk2618[8];

    /** Nonzero for each CLUT record in use. */
    u8 clut_used[LIB_TEXTURE_CACHE_MAX_CLUTS];


    /** VRAM word address of the texture area. */
    u32 texture_address;

    u32 unk2664;
    u8 unk2668[4];

    /** Number of CLUTs the CLUT area holds. */
    s32 clut_count;

    /** Entry each slot last found. */
    u16 slot_entries[LIB_TEXTURE_CACHE_ENTRY_COUNT];

    /** CLUT record each slot last found. */
    s16 clut_slot_entries[LIB_TEXTURE_CACHE_MAX_CLUTS];

    u8 stamp;
    u8 unk28f1[0x1F];
};

/** The game's texture cache. */
extern "C" LibTextureCache* g_texture_cache;

/**
 * @brief Load a texture the cache missed.
 * @param cache Cache to add the texture to.
 * @param request Texture to load.
 * @param tag Request tag.
 * @param id Texture ID.
 * @param slot Slot whose last hit is recorded.
 * @param unk5 Unknown.
 * @param user Object that owns the texture, or null.
 * @return VRAM word address of the texture, or 0.
 */
extern "C" u32 func_004A7100(LibTextureCache* cache, LibTextureRequest* request, u32 tag, u32 id, s32 slot, s32 unk5,
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
    /** Display manager whose camera the layer's objects face. */
    LibDisplayManager* display_manager;

    u8 unk04[0x64];
};

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
     * @brief Set the draw flags (LIB_DRAW_*).
     * @param value New flags.
     */
    inline void set_draw_flags(u16 value);

    /**
     * @brief Set the object's type ID.
     * @param value Type ID.
     */
    inline void set_type_id(u16 value);

    /** Lib's renderer draws objects with zero in its main list and the rest in bucket[draw_bucket]. */
    u8 draw_bucket;

    /** Nonzero when callers can reuse the cached matrix without an update. */
    u8 matrix_ready;

    u8 unk62;
    u8 unk63;

    /** Nonzero while the submitted packet awaits its DMA notification. */
    u8 dma_pending;

    u8 unk65;
    u8 unk66;
    u8 unk67;

    /** Layer of the owning scene the object belongs to; picks its display manager from the scene's layer records. */
    u8 layer;

    u8 unk69;
    u16 draw_flags;

    /** Type ID that Lib and scene code compare against (0x100 for scene models, 0x110 in Lib's scene setup). */
    u16 type_id;

    u8 unk6e[0x12];

    /** Display manager whose current camera the object faces; null for g_display_manager's. */
    LibDisplayManager* display_manager;
    u8 unk84[4];
    u32 unk88;
    u32 unk8c;
};


/** Two-callback DMA interface, with vtable D_171FF0 in main data. */
class LibDmaCallbacks
{
public:
    /** @brief Install the interface's vtable. */
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

    /** @brief Destroy the transform subclass. */
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

    /** @brief Remove a registered node and clear its pending buffer entries. @param object Node to remove. */
    virtual void remove_node(void* object);

    /**
     * @brief Run update handlers for registered nodes in list-kind order.
     *
     * Snapshot the list chain, skip null or detached nodes, and honor each
     * node's update flags. Derived lists can choose their own update order.
     */
    virtual void update_nodes();

    /** @brief Register and append a node. @param object Node to append. @param kind List kind, or DEFAULT_NODE_KIND to use the node's virtual kind. */
    virtual void append_node(void* object, s32 kind);
    /** @brief Register and prepend a node. @param object Node to prepend. @param kind List kind, or DEFAULT_NODE_KIND to use the node's virtual kind. */
    virtual void prepend_node(void* object, s32 kind);
    /** @brief Register a node after a list position. @param position Insertion position. @param object Node to insert. @param kind List kind, or DEFAULT_NODE_KIND to use the node's virtual kind. */
    virtual void insert_node_after(void* position, void* object, s32 kind);

    /**
     * @brief Set the next list in the chain.
     * @param attached List that follows this list.
     */
    virtual void func_004295B0(void* attached)
    {
        next_list = static_cast<LibUpdateList*>(attached);
    }

    /** @brief Default handler that performs no work. */
    virtual void func_004295C0()
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
    /** @brief Report the manager type. @return Manager type value. */
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

    /** @brief Run LibClass179080::func_004E1E70 on the current camera, if there is one. */
    void func_004DB0F0();

    /** @brief Queue the current camera, if there is one, for VIF1 DMA. */
    void submit_camera();

    /** @brief Set unk94 and write the current camera's matrices, if there is one. */
    void prepare_camera();

    /** Display the effect is set on, or null while it's off. */
    LibCameraContext* effect_display;

    LibListObject* current_display;
    u8 unk94;

    /** Nonzero while the display effect is on. */
    u8 effect_enabled;

    u8 unk96;
    u8 effect_level;
};

/** Display manager whose current camera objects face by default. */
extern LibDisplayManager* g_display_manager;

/** Display Lib draws on. */
extern LibCameraContext* g_display;

/** Second copy of the draw display that LibRenderer::set_display keeps; Lib's image code reads it. */
extern LibCameraContext* D_001B6520;

/** Bytes in each of the renderer's two packet buffers. */
#define LIB_RENDERER_BUFFER_SIZE 0x2000

/** Partial renderer pass that draws to the display at 0x94. */
struct LibRendererPass
{
    u8 unk00[0x94];
    LibCameraContext* display;
    u8 unk98[4];
    u8 unk9c;
};

/** Partial renderer pass that lib_initialize can switch on, drawing to the display at 0x128. */
struct LibRendererExtra
{
    u8 unk00[0x96];

    /** Set when Lib starts with both extra renderer arguments nonzero. */
    u8 enabled;

    u8 unk97[0x91];
    LibCameraContext* display;
};

/** Partial Lib renderer (g_renderer); it alternates between two packet buffers each frame. */
class LibRenderer : public LibUpdateList
{
public:
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
    void func_004D4560();
    void func_004D2C70();

    /**
     * @brief Test or wait for the renderer's packets in flight.
     * @param poll Nonzero to only test; zero to wait until none is in flight.
     * @return Nonzero while a packet is in flight (when polling).
     */
    s32 func_004D44D0(s32 poll);

    /** Write position in the current packet buffer. */
    u8* cursor;

    u8 unk7c[4];
    u8 buffers[2][LIB_RENDERER_BUFFER_SIZE];

    /** Scene manager whose current camera the frame is drawn with. */
    LibDisplayManager* manager;

    void* unk4084;
    LibCameraContext* display;
    u32 unk408c;
    u8 unk4090[4];

    /** Entry of lists picked for this frame. */
    void* current_list;

    void* lists[2];
    u32 unk40a0;

    /** EE timer 0 ticks the last finished packet took. */
    s32 packet_ticks;

    /** Object whose main-list packet is in flight. */
    LibTransformOwner* main_packet;

    /** Object whose bucket-list packet is in flight. */
    LibTransformOwner* bucket_packet;

    u32 unk40b0;
    u8 unk40b4[0xC];

    /** EE timer 0 count when the in-flight packet started. */
    s32 packet_start_time;

    u8 unk40c4[4];

    /** Nonzero while the main-list packet is in flight. */
    u8 main_packet_busy;

    /** Nonzero while the bucket-list packet is in flight. */
    u8 bucket_packet_busy;

    u8 unk40ca;
    u8 unk40cb;
    u8 unk40cc[2];

    /**
     * Nonzero (the default) to give bucket 0's own list the main-list objects whose unk66 byte is set; boot clears
     * it while its own frame loop runs.
     */
    u8 unk40ce;

    u8 unk40cf[2];

    /** Packet buffer the next frame writes to. */
    u8 buffer_index;

    u8 unk40d2[0x386];
    LibRendererPass* unk4458;
    u8 unk445c[4];
    LibRendererPass* unk4460;
    LibRendererPass* unk4464;
    LibRendererPass* unk4468;
    LibRendererExtra* extra;
};

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
    LibMatrix44Value transform;
    /** Transform composed from the inherited components and the parent. */
    LibMatrix44Value base_transform;

    /** Additional local transform composed with the base transform. */
    LibMatrix44Value offset_transform;

    /** Transpose of transform, which func_004D9E70 inverts into inverse_transform. */
    LibMatrix44Value transposed_transform;

    /** Inverse of transform: world space to local space. */
    LibMatrix44Value inverse_transform;

    LibVector4 offset_translation;

    /** Quaternion used to build the offset transform. */
    LibVector4 offset_rotation;

    LibVector4 offset_scale;
    float unk200;
    u8 unk204[4];
    /** Parent used when updating the matrix and invalidating the transform chain. */
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
 * @brief Multiply the transform's unk200 factor by its parents', climbing parent_transform while bit 0x200 of unk20c
 * is set.
 * @param transform Transform to start from.
 * @return The combined factor.
 */
extern "C" float func_004DA0F0(LibTransform* transform);

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

/** @brief Copy a complete local vector. @param output Destination vector. @param input Source vector. */
extern "C" void func_004DA040(LibVector4* output, const LibVector4* input);
/** @brief Return the transform's 16-bit state value. @param object Transform owner. @return Stored state value. */
extern "C" u16 func_004DA2B0(const LibTransform* object);

/** @brief Extract the transform's translation column. @param object Transform owner. @return Translation coordinates with homogeneous component one. */
extern "C" FieldVec4B func_004DA6F0(const LibTransform* object);
/** @brief Store the local scalar and update its threshold flag. @param object Transform receiver. @param value Local scalar value. */
extern "C" void func_004DA050(LibTransform* object, float value);
/**
 * @brief Rebuild the offset matrix from the stored translation, quaternion and scale.
 * @param object Transform whose offset matrix is updated.
 */
extern "C" void lib_rebuild_offset_transform(LibTransform* object);

/** @brief Mark each transform in the parent chain dirty. @param object First transform, or null. */
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
 * @brief Pass one list item to its virtual handler at vtable offset 0x14.
 * @param list List that owns the item.
 * @param item Item to process.
 */
void func_004D6700(void* list, void* item);



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
    /** Word address allocations start from. */
    u32 base_address;

    u32* unk04;

    /** Word address of each allocation. */
    u32* allocations;

    s16 unk04_count;
    s16 allocation_count;
    s16 unk04_capacity;
    s16 allocation_capacity;
    u32 unk14;

#ifdef __cplusplus
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
 * @brief Upload an image to a VRAM slot.
 * @param image Decoded image.
 * @param slot VRAM slot.
 * @return Negative on failure.
 */
s32 func_004D8D20(u8* image, s32 slot);

/** 16x16 CT32 image (256 colors) in Lib data. */
extern const u32 D_4EC600[];

/**
 * @brief Allocate VRAM for a 16x16 CT32 image and queue its upload.
 * @param image Image to upload.
 * @param count Passed to the VRAM allocator.
 * @return VRAM slot, or -1.
 */
s16 func_004D8C20(const void* image, s32 count);

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
 * @brief Test whether a list traversal has reached its sentinel.
 * @param sentinel List sentinel.
 * @param node Current node.
 * @return 1 if node is the sentinel, otherwise 0.
 */
s32 func_004D6DC0(const void* sentinel, const void* node);

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
 * @brief Return the supplied object pointer.
 * @param object Object or subobject pointer.
 * @return The same pointer.
 */
void* func_004D99A0(void* object);

/**
 * @brief Wait until the object's busy flag clears.
 * @param object Object to wait on.
 */
void func_004D99B0(LibBusyObject* object);

/**
 * @brief Return the fixed value 16.
 * @param object Receiver or first argument; unused.
 * @return Always 16.
 */
s32 func_004D0160(void* object);

/**
 * @brief Return the fixed value 10.
 * @param object Receiver or first argument; unused.
 * @return Always 10.
 */
s32 func_004D5810(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_004D5820(void* object);

/**
 * @brief Pass the pointer at offset 0x634 and the remaining arguments to a helper.
 * @param receiver Object containing the pointer.
 * @param arg1 First value passed to the helper.
 * @param arg2 Second value passed to the helper.
 */
void func_004D6230(void* receiver, u32 arg1, u32 arg2);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_004D66F0(void* object);

/**
 * @brief Return the fixed value 8.
 * @param object Receiver or first argument; unused.
 * @return Always 8.
 */
s32 func_004DAFD0(void* object);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" s32 func_004D04C0(void* object);
extern "C" s32 func_004D0740(void* object);
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** Lib's queue of GS packet operations. */
typedef struct LibPacketQueue LibPacketQueue;

/** The game's packet queue. */
extern LibPacketQueue* g_packet_queue;

/** Wait for or finish the packet queue according to the flag. */
void func_004DBEE0(LibPacketQueue* queue, s32 flag);

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
 * @brief Queue a packet operation.
 * @param queue Packet queue.
 * @param operation Operation number.
 * @param flags Operation flags.
 * @param packet Packet to send, or the object the operation is for.
 * @param value Operation value, such as a quadword count.
 * @param completion Called when the operation is done, or null.
 * @return Queue status.
 */
s32 func_004DC4F0(LibPacketQueue* queue, u32 operation, u32 flags, const void* packet, u32 value, void* completion);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/** Partial Lib packet queue; its vtable D_00178F90 comes after its data. */
struct LibPacketQueue
{
    s32 unk00;
    void* entries;
    s16 capacity;
    s16 unk0A;
    s16 unk0C;
    u8 unk0E;
    u8 unk0F;

    /** Queued packets may start; func_004DC420 sets it. */
    u8 enabled;

    u8 unk11;

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

#endif
