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

void func_004AD380(void* object);
void func_004B1890(void* object);
void func_004B2580(void* object);

/** Clear receiver state at 0x58 and 0x50, then run the shared reset helper. */
void func_004ACFF0(void* object);
/** Reset receiver state at 0xB0 and 0xB4, then run the shared reset helper. */
void func_004B1800(void* object);
void func_004B04C0(void* object);
void func_004AC770(void* object);

/** Forward two float values, passing the second through a stack address. */
void func_004B24A0(void* object, float value1, float value2);
void func_004B2500(void* object, float value1, float value2);
void func_004B3A70(void* object, float value1, float value2);
void func_004B2EB0(void* object, const float* value2, float value1);
void func_004B3120(void* object, const float* value2, float value1);
void func_004B3C30(void* object, const float* value2, float value1);

/** Copy the float at receiver offset 0x54 to the output. */
void func_004AD2B0(const void* object, float* value);

/** Copy the float at receiver offset 0x50 to the output. */
void func_004AFF60(const void* object, float* value);

/** Copy the float at receiver offset 0xB8 to the output. */
void func_004B1820(const void* object, float* value);

/** Copy the float at receiver offset 0x4C to the output. */
void func_004B2750(const void* object, float* value);

/** Write the difference between the selected 16-byte entry value and the first value. */
void func_004AFF70(const void* object, float* output);

/** Write the difference between the selected 8-byte entry value and the first value. */
void func_004B2720(const void* object, float* output);

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

/**
 * @brief Return the floating-point value 0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_004B0E20(void* object);

/**
 * @brief Return the floating-point value 0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_004B2A90(void* object);

/** Return the word at receiver offset 0x30. */
u32 func_004AC910(const void* object);

/** Return the word at receiver offset 0x4. */
u32 func_004ACAE0(const void* object);

/** Return the word at receiver offset 0x30. */
u32 func_004B0600(const void* object);

/** Return the word at receiver offset 0x4. */
u32 func_004B0810(const void* object);

/** Return the word at receiver offset 0x18. */
u32 func_004B0D60(const void* object);

/** Return the word at receiver offset 0x4. */
u32 func_004B0F40(const void* object);

/** Return the word at receiver offset 0x10. */
u32 func_004B2A60(const void* object);

/** Return the word at receiver offset 0x4. */
u32 func_004B2AD0(const void* object);


/** Return the signed halfword at receiver offset 0x38. */
s16 func_004AC920(const void* object);

/** Return the signed halfword at receiver offset 0x3A. */
s16 func_004AC930(const void* object);

/** Return the signed halfword at receiver offset 0x38. */
s16 func_004B0610(const void* object);

/** Return the signed halfword at receiver offset 0x3A. */
s16 func_004B0620(const void* object);

/** Return the signed halfword at receiver offset 0x20. */
s16 func_004B0D70(const void* object);

/** Return the signed halfword at receiver offset 0x22. */
s16 func_004B0D80(const void* object);

/** Return the signed halfword at receiver offset 0x18. */
s16 func_004B2A70(const void* object);

/** Return the signed halfword at receiver offset 0x1A. */
s16 func_004B2A80(const void* object);


/** Return the fixed integer value 99. */
s32 func_004ABAA0(void* object);

/** Return the fixed value 0. */
s32 func_004ACC10(void* object);

/** Return the fixed value 0. */
s32 func_004ACC50(void* object);

/** Return the fixed value 0. */
s32 func_004ACC90(void* object);

/** Return the fixed value 0. */
s32 func_004B0630(void* object);

/** Return the fixed value 0. */
s32 func_004B0640(void* object);

/** Return the fixed value 0. */
s32 func_004B0650(void* object);

/** Return the fixed value 0. */
s32 func_004B0D90(void* object);

/** Return the fixed value 0. */
s32 func_004B0DA0(void* object);

/** Return the fixed value 0. */
s32 func_004B0DB0(void* object);

/** Return the fixed value 0. */
s32 func_004B2DD0(void* object);

/** Return the fixed value 0. */
s32 func_004B2E10(void* object);

/** Return the fixed value 0. */
s32 func_004B2E50(void* object);

/** Return the fixed value 0. */
s32 func_004B3D60(void* object);

/** Return the fixed value 0. */
s32 func_004B3D70(void* object);

void func_004ABAB0(void* object);
void func_004ABD30(void* object);
void func_004AC430(void* object);
void func_004ACBD0(void* object);
void func_004B0660(void* object);
void func_004B0DC0(void* object);
void func_004B2D90(void* object);
void func_004B3D40(void* object);
void func_004B3D50(void* object);

/** Return the first pointer argument unchanged. */
void* func_004ACD50(void* value);
/** Return the first pointer argument unchanged. */
void* func_004B11B0(void* value);

/** Clear four consecutive words at the start of the receiver. */
void func_004AC990(void* object);

/** Clear four consecutive words at the start of the receiver. */
void func_004B06C0(void* object);

/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_004AC850(void* object, u8 mode);

/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_004AD410(void* object, u8 mode);

/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_004B0CA0(void* object, u8 mode);

/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_004B29A0(void* object, u8 mode);


/** Set the high packed mode at its target field and record whether either mode equals four. */
void func_004AC8B0(void* object, u8 mode);

/** Set the high packed mode at its target field and record whether either mode equals four. */
void func_004B05A0(void* object, u8 mode);

/** Set the high packed mode at its target field and record whether either mode equals four. */
void func_004B0D00(void* object, u8 mode);

/** Set the high packed mode at its target field and record whether either mode equals four. */
void func_004B2A00(void* object, u8 mode);


/** Find a key in the receiver's fixed-size entry array. */
s32 func_004AC940(void* object, float key);

/** Return the key span between the first and last entries. */
float func_004AC9B0(void* object);
float func_004B06E0(void* object);
float func_004B0E30(void* object);
float func_004B2CC0(void* object);

/** Find a key in the receiver's fixed-size entry array. */
s32 func_004B0670(void* object, float key);

/** Find a key in the receiver's fixed-size entry array. */
s32 func_004B0DD0(void* object, float key);

/** Find a key in the receiver's fixed-size entry array. */
s32 func_004B2D10(void* object, float key);


}
#endif

#endif
