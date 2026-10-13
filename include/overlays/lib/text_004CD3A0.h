#ifndef SO3_OVERLAYS_LIB_TEXT_004CD3A0_H
#define SO3_OVERLAYS_LIB_TEXT_004CD3A0_H

#include "types.h"
#include "overlays/lib/text_003E68C0.h"
#include "overlays/lib/counted_list.h"
#include "overlays/lib/vector.h"

/** Partial object with a busy flag that something else clears; the rest is unknown. */
typedef struct LibBusyObject
{
    u8 unk00[0x50];
    /** Nonzero while the object is busy. It changes outside the code that waits on it. */
    volatile u8 busy;
} LibBusyObject;

/** Partial list node; the leading bytes and full object extent are unknown. */
typedef struct LibListNode
{
    u8 unk00[8];
    struct LibListNode* next;
    s16 unk0c;
} LibListNode;

#ifdef __cplusplus
/** @brief Configure the attached callback and its flags. @param object Receiver. @param attached Attached object. @param enabled Whether the callback is enabled. @param first_flag First callback flag. @param second_flag Second callback flag. @param level Signed callback level. @param mask Callback mask. */
extern "C" void func_004DAFE0(void* object, void* attached, bool enabled, bool first_flag, bool second_flag, s32 level, u32 mask);

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
    void func_004CD8A0(FieldVec4B* quaternion);
    /** @brief Convert a quaternion to a matrix. @param quaternion Rotation to convert. @return Rotation matrix. */
    LibMatrix44Value func_004CE930(const FieldVec4B& quaternion);
    /**
     * @brief Build a matrix from quaternion products, retaining the quaternion's squared norm.
     * @param quaternion Quaternion components in x, y, z, w order.
     * @return Row-vector rotation matrix with the squared norm in its homogeneous diagonal.
     */
    LibMatrix44Value func_004CE980(const FieldVec4B& quaternion);
}

class LibClass178F30;

/** Partial 0x90-byte transform owner with vtable D_178A90 in main data. */
class LibClass178A90 : public LibClass171EF0
{
public:
    /** @brief Destroy the transform owner. */
    virtual ~LibClass178A90();

    /** @brief Detach and queue the transform owner, then clear its tracking mask. */
    virtual void func_003EF740();

    /** @brief Run the default transform update hook. */
    virtual void func_003EEBE0();

    /**
     * @brief Set the translation coordinates and mark the transform dirty.
     * @param x Horizontal translation.
     * @param y Vertical translation.
     * @param z Third translation component.
     */
    virtual void func_003EF790(float x, float y, float z);

    /**
     * @brief Copy the translation vector and mark the transform dirty.
     * @param value Translation vector to copy.
     */
    virtual void func_003EF780(const LibVector4* value);

    /**
     * @brief Copy the translation vector and mark the transform dirty.
     * @param value Translation vector to copy.
     */
    virtual void func_003EF770(const LibVector4* value);

    /** @brief Clear the byte at offset 0x60. */
    virtual void func_003F4420();

    /**
     * @brief Default output handler.
     * @param output Opaque output object.
     * @return Zero in the base implementation.
     */
    virtual s32 func_003EEE20(void* output);

    /**
     * @brief Test the supplied value in the base implementation.
     * @param value Value to test.
     * @param mode Additional mode used by derived implementations.
     * @return Whether the value is negative.
     */
    virtual s32 func_003EEE30(float value, float mode);

    /** @brief Return the transform's vector. @return Vector pointer. */
    virtual const LibVector4* func_003EFAA0();

    /**
     * @brief Default matrix handler.
     * @param matrix Matrix supplied by the caller.
     * @param context Opaque caller context.
     */
    virtual void func_003F4440(const void* matrix, void* context);

    /** @brief Mark the matrix ready. */
    virtual void func_004D0090();

    /** @brief Return the transformation matrix. @return Matrix pointer, or null in the base implementation. */
    virtual const LibMatrix44Value* func_004D00A0();

    /**
     * @brief Copy the source transformation state.
     * @param source Transform source.
     */
    virtual void func_004CFFA0(const LibClass178A90* source);

    /**
     * @brief Produce a transformation receiver, or null.
     * @return New transform receiver, or null.
     */
    virtual LibClass178A90* func_003EEE50();

    /** @brief Detach and queue the transform receiver. */
    virtual void func_003EEE60();

    u8 unk60;
    u8 unk61;
    u8 unk62;
    u8 unk63;
    /** Nonzero while the submitted packet awaits its DMA notification. */
    u8 dma_pending;
    u8 unk65[5];
    u16 unk6a;
    u16 unk6c;
    u8 unk6e[0x12];
    LibClass178F30* unk80;
    u8 unk84[0xC];
};

/** Transform subclass with resident vtable D_172000. */
class LibClass172000 : public LibClass178A90
{
public:
    /** @brief Initialize the transform subclass. */
    LibClass172000();

    /** @brief Destroy the transform subclass. */
    virtual ~LibClass172000();
};

/** Partial list owner with resident vtable at 0x178DD0 and an owned node buffer. */
class LibClass178DD0 : public LibClass178A70
{
public:
    enum
    {
        DEFAULT_NODE_KIND = -1,
        NODE_KIND_COUNT = 17
    };

    /** @brief Initialize the list owner, kind counts, and node-buffer state. */
    LibClass178DD0();
    /** @brief Release the owned node buffer and destroy the list base. */
    virtual ~LibClass178DD0();

    /** @brief Remove a registered node and clear its pending buffer entries. @param object Node to remove. */
    virtual void remove_node(void* object);

    /** @brief Lib virtual slot 6. */
    virtual void func_004D6730();

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
        next_list = static_cast<LibClass178DD0*>(attached);
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
    LibClass178DD0* next_list;
    LibClass178DD0* active_buffer_owner;
};

/**
 * @brief Allocate the owned node-pointer buffer and store its capacity.
 * @param owner List that owns the buffer.
 * @param node_count Number of node pointers to allocate.
 */
extern "C" void lib_list_allocate_node_buffer(LibClass178DD0* owner, s32 node_count);

/**
 * @brief Release the owned node buffer when no node buffer is active.
 * @param owner List that owns the buffer.
 * @return One if the buffer was released, or zero while a buffer is active.
 */
extern "C" s32 lib_list_release_node_buffer(LibClass178DD0* owner);

/**
 * @brief Transfer one node count from the node's stored kind to a new kind.
 * @param owner List whose per-kind counts are updated.
 * @param node Node supplying the old kind.
 * @param new_kind Kind whose count is incremented.
 */
extern "C" void lib_list_change_node_kind_counts(LibClass178DD0* owner, const LibClass171EA0* node, s32 new_kind);

/**
 * @brief Update the owner's kind counts, then store the node's list kind.
 * @param node Node whose list kind is changed.
 * @param kind Kind passed to the owner; its low halfword is stored in the node.
 */
extern "C" void lib_object_set_list_kind(LibClass171EA0* node, s32 kind);

/** 0x98-byte display manager with a list interface and secondary intrusive receiver. */
class LibClass178F30 : public LibClass178DD0, public LibClass171EA0
{
public:
    /** @brief Initialize the manager interfaces and current display. */
    LibClass178F30();
    /** @brief Destroy both manager interfaces. */
    virtual ~LibClass178F30();
    /** @brief Report the manager type. @return Manager type value. */
    virtual s32 func_003EEBC0();
    /** @brief Update the manager's intrusive receiver. */
    virtual void func_003EEBD0();
    u8 unk8c[4];
    LibClass171EA0* current_display;
    u8 unk94;
    u8 unk95;
    u8 unk96[2];
};

/** Partial Lib class used as a member object, with vtable D_178EA0 in main data. */
class LibClass178EA0 : public LibClass178A90
{
public:
    /** @brief Initialize the object and its transform state. */
    LibClass178EA0();

    /** @brief Destroy the object. */
    virtual ~LibClass178EA0();

    /** @brief Return the first local transform vector. @return Vector at offset 0x1D0. */
    virtual const LibVector4* func_003F4520() const;
    /** @brief Return the second local transform vector. @return Vector at offset 0x1E0. */
    virtual const LibVector4* func_003F4530() const;
    /** @brief Return the third local transform vector. @return Vector at offset 0x1F0. */
    virtual const LibVector4* func_003F4540() const;
    /** @brief Copy transform state from another receiver. @param source Transform to copy. */
    virtual void func_004D9F40(const LibClass178EA0* source);
    /** @brief Update transform state relative to the current camera. */
    virtual void func_003EEBD0();
    /** @brief Update the object transformation matrix. */
    virtual void func_004D0090();
    /** @brief Return the object transformation matrix. @return Transformation matrix. */
    virtual const LibMatrix44Value* func_004D00A0();
    LibMatrix44Value transform;
    u8 unkd0[0x100];
    LibVector4 unk1d0;
    LibVector4 unk1e0;
    LibVector4 unk1f0;
    float unk200;
    u8 unk204[4];
    LibClass178EA0* unk208;
    u16 unk20c;
    u8 unk20e[2];
};

/** @brief Copy a complete local vector. @param output Destination vector. @param input Source vector. */
extern "C" void func_004DA040(LibVector4* output, const LibVector4* input);

/** @brief Extract the transform's translation column. @param object Transform owner. @return Translation coordinates with homogeneous component one. */
extern "C" FieldVec4B func_004DA6F0(const LibClass178EA0* object);
/** @brief Store the local scalar and update its threshold flag. @param object Transform receiver. @param value Local scalar value. */
extern "C" void func_004DA050(LibClass178EA0* object, float value);
/** @brief Update the local transformation matrix. @param object Transform receiver. */
extern "C" void func_004DAB50(LibClass178EA0* object);

/** @brief Mark each transform in the parent chain dirty. @param object First transform, or null. */
extern "C" void lib_invalidate_transform_chain(LibClass178EA0* object);
#endif

#ifdef __cplusplus
extern "C" {
#endif

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
 * @brief Fill an array with the list's items.
 * @param list List whose items are collected.
 * @param items Array that receives the item pointers.
 */
void func_004D6AF0(void* list, void** items);

/**
 * @brief Release heap storage, choosing between two resident heap release routines by a resident flag.
 *
 * Several Field classes route their operator delete here; the Lib list class's own
 * deleting destructor uses the global operator delete instead.
 * @param object Storage to release; null is ignored.
 */
void func_004DB570(void* object);

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
 * @brief Return the base transform's null matrix pointer.
 * @param object Transform receiver; unused.
 * @return Null.
 */
const void* func_004D00A0(void* object);

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

#endif
