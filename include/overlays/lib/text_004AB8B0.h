#ifndef SO3_OVERLAYS_LIB_TEXT_004AB8B0_H
#define SO3_OVERLAYS_LIB_TEXT_004AB8B0_H

#include "types.h"
#include "overlays/lib/text_004BD360.h"

#ifdef __cplusplus
struct FieldFloatSpan1C;
class LibClass178220;
class LibClass178370;
/** 32-byte key and aligned vector entry. Its constructor leaves the fields uninitialized. */
struct LibVectorChannelEntry20
{
    /** @brief Leave the entry uninitialized. */
    LibVectorChannelEntry20();

    float unk00;
    LibVector4 unk10;
};

/** Partial vector-channel base with vtable D_177B50 and an owned or borrowed entry array. */
class LibClass177B50 : public LibClass173180
{
public:
    LibVectorChannelEntry20* unk04;
    LibVectorChannelEntry20 unk10;
    s32 unk30;
    float unk34;
    s16 unk38;
    s16 unk3a;
    s16 unk3c;
    s16 unk3e;
    s16 unk40;
    u8 unk42_0_3 : 4;
    u8 unk42_4_7 : 4;
    u8 unk43_0 : 1;
    u8 unk43_1 : 1;
    u8 unk43_2 : 1;
    u8 unk43_3_7 : 5;
};

/** Partial vector-channel specialization with vtable D_177AC0 and no additional storage before offset 0x50. */
class LibClass177AC0 : public LibClass177B50
{
};

/** Partial 192-byte vector channel with vtable D_177EE0, also used by the Field channel pool. */
class LibClass177EE0 : public LibClass177AC0
{
public:
    u8 unk50[0x70];
};

extern "C" {

/**
 * @brief Evaluate four interpolation coefficients over their cached key range.
 * @param span Coefficients and segment bounds.
 * @param key Sort value.
 * @return Interpolated value.
 */
float func_4B16C0(FieldFloatSpan1C* span, float key);

/**
 * @brief Update the animation state for a requested frame.
 * @param object Animation object.
 * @param frame Requested frame.
 * @param flag Update flag.
 * @return Processing result.
 */
s32 func_004B4550(LibClass178220* object, float frame, s32 flag);

/**
 * @brief Evaluate the animation into its vector state.
 * @param object Animation object.
 * @param target Vector state.
 */
void func_004B3DE0(LibClass178220* object, LibClass178370* target);

/**
 * @brief Process the animation at a requested frame.
 * @param object Animation object.
 * @param frame Requested frame.
 * @param mode Processing mode.
 * @return Processing status.
 */
s32 func_004B43C0(LibClass178220* object, float frame, s32 mode);

/**
 * @brief Process the animation into a vector state at a requested frame.
 * @param object Animation object.
 * @param target Vector state.
 * @param frame Requested frame.
 * @param mode Processing mode.
 * @return Processing status.
 */
s32 func_004B46E0(LibClass178220* object, LibClass178370* target, float frame, s32 mode);

}
#endif

#endif
