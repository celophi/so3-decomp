#ifndef SO3_OVERLAYS_LIB_TEXT_003E68C0_H
#define SO3_OVERLAYS_LIB_TEXT_003E68C0_H

#include "types.h"

#ifdef __cplusplus
/** Four-float Lib vector with a packed representation for full-width transfers. */
union LibVector4
{
    unsigned __int128 packed;
    float components[4];
} __attribute__((aligned(16)));

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

    /**
     * @brief Read the 16-bit value of a buffer entry.
     * @param index Entry index, valid below 0x1A.
     * @return The entry's halfword at offset 6, or a default for an invalid index.
     */
    s32 func_003F4B50(s32 index);

    u8 unk00[0x790];
    void* unk790;
};

/**
 * Partial Lib root class with its vtable pointer at offset 0, with vtable
 * D_171EA0 in main data (its own bases D_171E90 and D_171E80 are not modelled).
 * Slots 3 and 4 keep placeholder signatures.
 */
class LibClass171EA0
{
public:
    /** @brief Destroy the object. */
    virtual ~LibClass171EA0();

    /** @brief Report the fixed object kind. @return Always 3. */
    virtual s32 func_003EEBC0();

    /** @brief Delete the object through its virtual destructor; null is ignored. */
    virtual void func_003EF740();

    /** @brief Virtual slot 3. */
    virtual void func_003EEBD0();

    /** @brief Virtual slot 4. */
    virtual void func_003EEBE0();
};

/** Position transform, with root vtable D_171EC0. */
class LibClass171EC0 : public LibClass171EA0
{
public:
    /** @brief Destroy the transform. */
    virtual ~LibClass171EC0();
    /**
     * @brief Update transform components.
     * @param x Scalar component.
     * @param y Scalar component.
     * @param z Scalar component.
     */
    virtual void func_003EF790(float x, float y, float z);
    /**
     * @brief Update transform components.
     * @param value Vector components.
     */
    virtual void func_003EF780(const LibVector4* value);
    /**
     * @brief Update transform components.
     * @param value Vector components.
     */
    virtual void func_003EF770(const LibVector4* value);
    u8 unk04[0x1C];
    LibVector4 unk20;
};
/** Position, quaternion and scale transform, with root vtable D_171EF0. */
class LibClass171EF0 : public LibClass171EC0
{
public:
    /** @brief Destroy the transform. */
    virtual ~LibClass171EF0();
    /**
     * @brief Update transform components.
     * @param x Scalar component.
     * @param y Scalar component.
     * @param z Scalar component.
     */
    virtual void func_003EF790(float x, float y, float z);
    /**
     * @brief Update transform components.
     * @param value Vector components.
     */
    virtual void func_003EF780(const LibVector4* value);
    /**
     * @brief Update transform components.
     * @param value Vector components.
     */
    virtual void func_003EF770(const LibVector4* value);
    /**
     * @brief Update transform components.
     * @param x Scalar component.
     * @param y Scalar component.
     * @param z Scalar component.
     */
    virtual void func_003EEF90(float x, float y, float z);
    /**
     * @brief Update transform components.
     * @param value Vector components.
     */
    virtual void func_003EEF60(const LibVector4* value);
    /**
     * @brief Update transform components.
     * @param value Vector components.
     */
    virtual void func_003EEF30(const LibVector4* value);
    /**
     * @brief Update transform components.
     * @param value Vector components.
     */
    virtual void func_003EEF10(const LibVector4* value);
    /**
     * @brief Update transform components.
     * @param value Vector components.
     */
    virtual void func_003EEEF0(const LibVector4* value);
    /**
     * @brief Update transform components.
     * @param x Scalar component.
     * @param y Scalar component.
     * @param z Scalar component.
     * @param w Scalar component.
     */
    virtual void func_003EEED0(float x, float y, float z, float w);
    /**
     * @brief Update transform components.
     * @param x Scalar component.
     * @param y Scalar component.
     * @param z Scalar component.
     */
    virtual void func_003EF010(float x, float y, float z);
    /**
     * @brief Update transform components.
     * @param value Vector components.
     */
    virtual void func_003EEFF0(const LibVector4* value);
    /**
     * @brief Update transform components.
     * @param value Vector components.
     */
    virtual void func_003EEFD0(const LibVector4* value);
    LibVector4 unk30;
    LibVector4 unk40;
    u8 unk50;
    u8 unk51;
};
#endif

#endif
