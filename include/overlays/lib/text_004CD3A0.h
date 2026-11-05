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
}

class LibDisplayManager;
class LibCameraContext;

/** Entries a texture cache tracks; entry 0 is the head of the most-recently-used list. */
#define LIB_TEXTURE_CACHE_ENTRY_COUNT 256

/** Partial object that owns a cached texture. */
struct LibTextureUser
{
    u8 unk00[0x2C];
    s32 priority;
};

/** Partial key half of a cache entry. */
struct LibTextureKey
{
    u32 id;
    u8 unk04[0xB];

    /** Cache stamp of the last lookup that found the entry. */
    u8 stamp;
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

/** Partial 0x2910-byte VRAM texture cache (D_001B663C). It may sit at the start of scratchpad memory. */
class LibTextureCache
{
public:
    /**
     * @brief Create the cache.
     * @param size Size in bytes.
     * @param count Block count.
     */
    LibTextureCache(s32 size, s32 count);

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

    u8 unk00[8];
    LibTextureKey keys[LIB_TEXTURE_CACHE_ENTRY_COUNT];
    LibTextureEntry entries[LIB_TEXTURE_CACHE_ENTRY_COUNT];
    u8 next[LIB_TEXTURE_CACHE_ENTRY_COUNT];
    u8 previous[LIB_TEXTURE_CACHE_ENTRY_COUNT];
    u8 unk2208[0x468];

    /** Entry each slot last found. */
    u16 slot_entries[LIB_TEXTURE_CACHE_ENTRY_COUNT];

    u8 unk2870[0x80];
    u8 stamp;
    u8 unk28f1[0x1F];
};

/** The game's texture cache. */
extern "C" LibTextureCache* D_001B663C;

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
    LIB_DRAW_FLAG_0010 = 0x0010,
    LIB_DRAW_FLAG_0400 = 0x0400
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
    u8 unk68;
    u8 unk69;
    u16 draw_flags;

    /** Type ID that Lib and scene code compare against (0x100 for scene models, 0x110 in Lib's scene setup). */
    u16 type_id;

    u8 unk6e[0x12];
    LibDisplayManager* unk80;
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

    /** Display the effect is set on, or null while it's off. */
    LibCameraContext* effect_display;

    LibListObject* current_display;
    u8 unk94;

    /** Nonzero while the display effect is on. */
    u8 effect_enabled;

    u8 unk96;
    u8 effect_level;
};

/** Bytes in each of the renderer's two packet buffers. */
#define LIB_RENDERER_BUFFER_SIZE 0x2000

/** Partial Lib renderer (D_001B661C); it alternates between two packet buffers each frame. */
class LibRenderer : public LibUpdateList
{
public:
    /** @brief Destroy the renderer. */
    virtual ~LibRenderer();

    /** @brief Start a frame: swap packet buffers and, with a list and a camera, build the frame's packets. */
    void begin_frame();

    void func_004D4700();
    void func_004D4560();

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
    u32 unk40a4;
    u32 unk40a8;
    u8 unk40ac[4];
    u32 unk40b0;
    u8 unk40b4[0xC];
    u32 unk40c0;
    u8 unk40c4[6];
    u8 unk40ca;
    u8 unk40cb;
    u8 unk40cc[5];

    /** Packet buffer the next frame writes to. */
    u8 buffer_index;
};

/** Reciprocal of g_frame_ticks, refreshed each frame. */
extern float D_001B668C;

extern "C" LibBusyObject* D_001B65FC;
extern "C" u64 D_001B65C8;

/**
 * @brief Queue the busy object on a channel.
 * @param object Busy object.
 * @param channel Channel number.
 * @return Queue status.
 */
extern "C" s32 func_004D9A80(LibBusyObject* object, u8 channel);

extern "C" void func_004DB150(LibDisplayManager* manager);
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

    u8 unk150[0x80];
    LibVector4 offset_translation;

    /** Quaternion used to build the offset transform. */
    LibVector4 offset_rotation;

    LibVector4 offset_scale;
    float unk200;
    u8 unk204[4];
    /** Parent used when updating the matrix and invalidating the transform chain. */
    LibTransform* parent_transform;
    u16 unk20c;
    u8 unk20e[2];
};

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
 * @param output Aligned destination quaternion; may alias either input.
 * @param first First aligned quaternion.
 * @param second Second aligned quaternion.
 * @param fraction Interpolation fraction.
 */
void func_004CD3A0(FieldVec4B* output, const FieldVec4B* first, const FieldVec4B* second, float fraction);

/**
 * @brief Interpolate along the shorter quaternion arc and normalize the result.
 * @param output Aligned destination quaternion; may alias either input.
 * @param first First aligned quaternion.
 * @param second Second aligned quaternion.
 * @param fraction Interpolation fraction.
 */
void func_004CD630(FieldVec4B* output, const FieldVec4B* first, const FieldVec4B* second, float fraction);

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
#endif

/**
 * @brief Transform a four-float input into an output vector.
 * @param output Destination vector.
 * @param input Source vector.
 */
void func_004CE4C0(float* output, const float* input);

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

/** The game's VRAM allocator. */
extern LibVramAllocator* D_001B65E0;

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
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_004D5D70(void* object);

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
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_004D9B50(void* object);

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
extern LibPacketQueue* D_001B65DC;

/** Wait for or finish the packet queue according to the flag. */
void func_004DBEE0(LibPacketQueue* queue, s32 flag);

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
