#ifndef SO3_OVERLAYS_LIB_TEXT_003E68C0_H
#define SO3_OVERLAYS_LIB_TEXT_003E68C0_H

#include "types.h"

#ifdef __cplusplus
extern "C" void func_003EF030(u8* object);
#endif

typedef struct N50Owner94_003E68C0 N50Owner94_003E68C0;

#ifdef __cplusplus
/** Partial owner whose nonvirtual destructor releases its two buffers. */
class LibBufferOwner
{
public:
    void* first;
    u8 unk04[4];
    void* second;

    LibBufferOwner();

    /** @brief Release both owned buffers. */
    ~LibBufferOwner();
};

class LibClass178A90;
class LibPositionTransform;
class LibOrientedTransform;
struct LibVector4;

/** @brief Store state value 8 in the transform's byte at offset 0x60. @param object Transform owner. */
extern "C" void func_003F4500(LibClass178A90* object);
/** @brief Store state value 7 in the transform's byte at offset 0x60. @param object Transform owner. */
extern "C" void func_003F4560(LibClass178A90* object);
/** @brief Return the fixed value 14. @param object Receiver or first argument; unused. @return Always 14. */
extern "C" s32 func_003F4550(void* object);
/** @brief Return the fixed value 9. @param object Unused receiver. @return Always 9. */
extern "C" s32 func_003EF900(void* object);
/** @brief Return the fixed value 9. @param object Unused receiver. @return Always 9. */
extern "C" s32 func_003F4370(void* object);
/** @brief Store state value 9 in the transform's byte at offset 0x60. @param object Transform owner. */
extern "C" void func_003EF910(LibClass178A90* object);
/** @brief Provide the empty default hook. */
extern "C" void func_003F4410(void);
/** @brief Forward the transform receiver to its state-update handler. @param object Transform owner. */
extern "C" void func_003EF070(LibClass178A90* object);
/** @brief Provide the empty default handler. @param object Unused receiver. */
extern "C" void func_003EFA90(void* object);

/** @brief Store a word at receiver offset 0x14. @param object Receiver. @param value Word value. */
extern "C" void func_003F3E60(void* object, u32 value);
/** @brief Read the word at receiver offset 0x3C78. @param object Receiver. @return Stored word. */
extern "C" u32 func_003F3E70(const void* object);
/** @brief Store a word at receiver offset 0x4. @param object Receiver. @param value Word value. */
extern "C" void func_003F3E80(void* object, u32 value);
/** @brief Store a word at receiver offset 0x8C. @param object Receiver. @param value Word value. */
extern "C" void func_003F3E90(void* object, u32 value);
/** @brief Return the receiver address at offset 0x3C60. @param object Receiver. @return Address of the field. */
extern "C" void* func_003F3EF0(void* object);
/** @brief Store a word at receiver offset 0x3C7C. @param object Receiver. @param value Word value. */
extern "C" void func_003F3F00(void* object, u32 value);
/** @brief Copy the byte at offset 0xB4 to offset 0x60. @param object Receiver to update. */
extern "C" void func_003EEDE0(void* object);
/** Build and return a pointer to the four-word stack value. */
extern "C" void* func_003EEDF0(void);
/** Build and return a pointer to the four-word stack value. */
extern "C" void* func_003F4570(void);
/** @brief Clear the receiver's first two words and return the receiver. @param object Receiver. @return The receiver. */
extern "C" void* func_003F42A0(void* object);

/** Four aligned floating-point vector components. */
struct LibVector4
{
    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16)));

/**
 * @brief Copy a vector as one 128-bit value.
 *
 * Plain assignment copies four words; the game uses this for most copies.
 * @param destination Vector receiving the copy.
 * @param source Vector to copy.
 */
static inline void copy_vector(LibVector4* destination, const LibVector4* source)
{
    *(unsigned __int128*)destination = *(const unsigned __int128*)source;
}

/**
 * @brief Zero all four components with one 128-bit store.
 * @param vector Vector to clear.
 */
static inline void clear_vector(LibVector4* vector)
{
    *(unsigned __int128*)vector = 0;
}


/** Partially known 8-byte buffer entry; the signed value is at offset 6. */
struct LibClass3F5B80Entry
{
    u32 unk00;
    u8 unk04;
    u8 unk05;
    s16 unk06;
};

/** Partially known 0x680-byte backing buffer for LibClass3F5B80. */
struct LibClass3F5B80Buffer
{
    LibClass3F5B80Entry entries[0x1A];
    u8 unk0D0[0x598];
    s16 unk668;
    u8 unk66A[0x0B];
    u8 unk675[3];
    u8 unk678[3];
    u8 unk67B[5];
};

/**
 * Partial 0x794-byte Lib object. Its constructor picks a 16-byte aligned
 * buffer inside the object (pointer at offset 0x790), clears 0x680 bytes of it
 * and fills its entry table. No destructor is known.
 */
class LibClass3F5B80
{
public:
    /** @brief Initialize the buffer and its entry table. */
    LibClass3F5B80();

    /**
     * @brief Fill the buffer for the given settings.
     * @param id First setting.
     * @param kind Second setting.
     * @param area Third setting.
     * @param flags Option bits.
     */
    void func_003F4EB0(s32 id, s32 kind, s32 area, u8 flags);

    /** @brief Pick a new aligned buffer and reset it as the constructor does. */
    void func_003F5AC0();

    /** @brief Store a byte in one of three backing-buffer slots. @param index Slot index. @param value Byte value. */
    void func_003F4A10(s32 index, u8 value);
    /** @brief Store a byte in one of three backing-buffer slots. @param index Slot index. @param value Byte value. */
    void func_003F4A50(s32 index, u8 value);
    /** @brief Store a byte in one of three backing-buffer slots. @param index Slot index. @param value Byte value. */
    void func_003F4A90(s32 index, u8 value);
    /** @brief Read an entry's state byte when the index is in range. @param index Entry index. @return The state byte, or zero when the index is invalid. */
    u8 func_003F4AD0(s32 index);
    /** @brief Read an entry's first word when the index is in range. @param index Entry index. @return The word, or zero when the index is invalid. */
    u32 func_003F4B10(s32 index);

    /**
     * @brief Read the 16-bit value of a buffer entry.
     * @param index Entry index, valid below 0x1A.
     * @return The entry's signed halfword, or -1 for an invalid index.
     */
    s32 func_003F4B50(s32 index);
    /** @brief Store a halfword value in the backing buffer, mapping -1 to 0x37. @param value Value to store. */
    void func_003F4B90(s32 value);
    /** @brief Store two values in an entry when the index is in range. @param index Entry index. @param value Word value. @param state Byte value. */
    void func_003F4BC0(s32 index, u32 value, u8 state);

    u8 unk00[0x790];
    LibClass3F5B80Buffer* buffer;
};

/** Virtual intrusive-link root. */
class LibLink
{
public:
    /** @brief Destroy the intrusive-link root. */
    virtual ~LibLink()
    {
    }
};
/** Intrusive list sentinel initialized by the resident list constructor. */
class LibListSentinel : public LibLink
{
public:
    /** @brief Clear the intrusive links before a sentinel owner installs itself. */
    LibListSentinel() : previous(0), next(0)
    {
    }
    /** @brief Destroy the list sentinel and its virtual root. */
    virtual ~LibListSentinel()
    {
    }
    LibListSentinel* previous;
    LibListSentinel* next;
};
class LibClass178DD0;
/** @brief Detach an object from its owner. @param object Intrusive receiver. */
extern "C" void lib_object_detach_owner(void* object);

/** 0x14-byte object kept in an owner's intrusive list, with vtable D_171EA0 in main data. */
class LibListObject : public LibListSentinel
{
public:
    /** @brief Clear the object flags and its owner after initializing the links. */
    LibListObject() : is_listed(0), object_kind(0), owner(0)
    {
    }
    /** @brief Detach from the owner, then destroy the intrusive links. */
    virtual ~LibListObject()
    {
        lib_object_detach_owner(this);
    }

    /** @brief Report the list kind used when registration requests the default. @return Three in the base implementation. */
    virtual s32 get_default_list_kind();

    /** @brief Delete the object through its virtual destructor; null is ignored. */
    virtual void destroy();

    /** @brief Advance this registered object's state; the owning list's update pass calls it. */
    virtual void update();

    /** @brief Virtual slot 4; the base implementation does nothing. */
    virtual void render();
    s16 list_kind;
    u8 is_listed;

    /** Type tag; zero by default, two for transform owners. */
    u8 object_kind;

    LibClass178DD0* owner;
};

/** Position transform, with vtable D_171EC0 in main data. */
class LibPositionTransform : public LibListObject
{
public:
    /** @brief Destroy the transform. */
    virtual ~LibPositionTransform()
    {
    }

    /**
     * @brief Set the position and a w component of one.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     */
    virtual void set_translation(float x, float y, float z);

    /**
     * @brief Copy the position.
     * @param value Source vector.
     */
    virtual void set_translation_vector(const LibVector4* value);

    /**
     * @brief Copy the position.
     * @param value Source vector.
     */
    virtual void copy_translation(const LibVector4* value);

    u8 unk14[0xC];
    LibVector4 translation;
};
/** Position, rotation and scale transform, with vtable D_171EF0 in main data. */
class LibOrientedTransform : public LibPositionTransform
{
public:
    /** @brief Initialize the transform. */
    LibOrientedTransform();

    /** @brief Destroy the transform. */
    virtual ~LibOrientedTransform()
    {
    }

    /**
     * @brief Set the position and a w component of one, and mark the transform dirty.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     */
    virtual void set_translation(float x, float y, float z);

    /**
     * @brief Copy the position and mark the transform dirty.
     * @param value Source vector.
     */
    virtual void set_translation_vector(const LibVector4* value);

    /**
     * @brief Copy the position and mark the transform dirty.
     * @param value Source vector.
     */
    virtual void copy_translation(const LibVector4* value);

    /**
     * @brief Convert three rotation components into the rotation vector and mark the transform dirty.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     */
    virtual void set_rotation(float x, float y, float z);

    /**
     * @brief Convert a rotation into the rotation vector and mark the transform dirty.
     * @param value Source rotation.
     */
    virtual void set_rotation_vector(const LibVector4* value);

    /**
     * @brief Convert a rotation into the rotation vector and mark the transform dirty.
     * @param value Source rotation.
     */
    virtual void convert_rotation(const LibVector4* value);

    /**
     * @brief Copy the rotation vector and mark the transform dirty.
     * @param value Source vector.
     */
    virtual void set_orientation(const LibVector4* value);

    /**
     * @brief Copy the rotation vector and mark the transform dirty.
     * @param value Source vector.
     */
    virtual void copy_orientation(const LibVector4* value);

    /**
     * @brief Set all four rotation components and mark the transform dirty.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     * @param w Fourth component.
     */
    virtual void set_orientation_components(float x, float y, float z, float w);

    /**
     * @brief Set the scale's xyz components and mark the transform dirty.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     */
    virtual void set_scale(float x, float y, float z);

    /**
     * @brief Copy the scale vector and mark the transform dirty.
     * @param value Source vector.
     */
    virtual void set_scale_vector(const LibVector4* value);

    /**
     * @brief Copy the scale vector and mark the transform dirty.
     * @param value Source vector.
     */
    virtual void copy_scale(const LibVector4* value);

    /** Rotation as a quaternion; Euler angles are converted on the way in. */
    LibVector4 orientation;

    LibVector4 scale;

    /** Nonzero when the transformation matrices need rebuilding. */
    u8 transform_dirty;

    u8 unk51;
};
#endif

#ifdef __cplusplus
/** Forward the receiver to func_004D00B0. */
extern "C" void func_003F2550(LibClass178A90* object);
#endif


#ifdef __cplusplus
extern "C" s32 func_003EF090(void* object);
extern "C" s32 func_003F2570(void* object);
extern "C" void func_003EFAF0(N50Owner94_003E68C0* object);
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** Release the resident category storage and clear its counters. */
void func_003EF860(void);

/** Remove and free the keyed Lib resource. */
void func_003EF8A0(void);

#ifdef __cplusplus
}
#endif

#endif
