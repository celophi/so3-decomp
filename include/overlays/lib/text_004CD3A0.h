#ifndef SO3_OVERLAYS_LIB_TEXT_004CD3A0_H
#define SO3_OVERLAYS_LIB_TEXT_004CD3A0_H

#include "types.h"
#include "overlays/lib/text_003E68C0.h"

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
class FieldVec4B;

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
    /** @brief Normalize a quaternion in place. @param quaternion Quaternion to normalize. */
    void func_004CD8A0(FieldVec4B* quaternion);
    /** @brief Convert a quaternion to a matrix. @param quaternion Rotation to convert. @return Rotation matrix. */
    LibMatrix44Value func_004CE930(const FieldVec4B& quaternion);
}

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
    virtual const void* func_004D00A0();

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
    u8 unk62[8];
    u16 unk6a;
    u16 unk6c;
    u8 unk6e[0x22];
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

/**
 * Partial Lib base class with its vtable pointer at offset 0x10, with vtable D_178DD0 in main data.
 * Its twelve virtual slots are declared in vtable order; slots 5-9 keep opaque parameters
 * until their Lib implementations are reconstructed.
 */
class LibClass178DD0
{
public:
    u8 unk00[0xC];
    s32 unk0c;

    /** @brief Construct an empty list. */
    LibClass178DD0();

    /** @brief Destroy the object. */
    virtual ~LibClass178DD0();

    /**
     * @brief Link a node before the list's first node and increment the count at offset 0xC.
     * @param node Node to link.
     */
    virtual void func_004CA020(void* node);

    /**
     * @brief Link a node after the list's last node and increment the count at offset 0xC.
     * @param node Node to link.
     */
    virtual void func_004C9FF0(void* node);

    /**
     * @brief Link a node after another node and increment the count at offset 0xC.
     * @param position Node to link after.
     * @param node Node to link.
     */
    virtual void func_004C9FC0(void* position, void* node);

    /**
     * @brief Unlink a node and decrement the nonzero count at offset 0xC.
     * @param node Node to unlink; the list itself and null are ignored.
     */
    virtual void func_004C9F60(void* node);

    /**
     * @brief Lib virtual slot 5.
     * @param value Opaque argument.
     */
    virtual void func_004D72A0(void* value);

    /** @brief Lib virtual slot 6. */
    virtual void func_004D6730();

    /**
     * @brief Lib virtual slot 7.
     * @param a Opaque first argument.
     * @param b Opaque second argument.
     */
    virtual void func_004D74F0(void* a, void* b);

    /**
     * @brief Lib virtual slot 8.
     * @param a Opaque first argument.
     * @param b Opaque second argument.
     */
    virtual void func_004D7450(void* a, void* b);

    /**
     * @brief Lib virtual slot 9.
     * @param a Opaque first argument.
     * @param b Opaque second argument.
     * @param c Opaque third argument.
     */
    virtual void func_004D73B0(void* a, void* b, void* c);

    /**
     * @brief Store the attached object pointer at offset 0x70.
     * @param attached Object pointer to store.
     */
    virtual void func_004295B0(void* attached);

    /** @brief Default handler that performs no work. */
    virtual void func_004295C0();

    u8 unk14[0x48];
    s32 unk5c;
    s32 unk60;
    u8 unk64[8];
    void** unk6c;
    void* unk70;
    u8 unk74[4];
};

/** Partial Lib class used as a member object, with vtable D_178EA0 in main data. */
class LibClass178EA0 : public LibClass178A90
{
public:
    /** @brief Initialize the object and its transform state. */
    LibClass178EA0();

    /** @brief Destroy the object. */
    virtual ~LibClass178EA0();

    u8 unk90[0x180];
};
#endif

#ifdef __cplusplus
extern "C" {
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
void func_004D65C0(void* object);

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
