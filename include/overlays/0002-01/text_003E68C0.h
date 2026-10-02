#ifndef SO3_OVERLAYS_0002_01_TEXT_003E68C0_H
#define SO3_OVERLAYS_0002_01_TEXT_003E68C0_H

#include "types.h"

#ifdef __cplusplus
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
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_003ED0E8(void* object);

#ifdef __cplusplus
}
#endif

#endif
