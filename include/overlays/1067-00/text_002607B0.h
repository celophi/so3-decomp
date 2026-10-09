#ifndef SO3_OVERLAYS_1067_00_TEXT_002607B0_H
#define SO3_OVERLAYS_1067_00_TEXT_002607B0_H

#include "overlays/1067-00/text_002636B0.h"

typedef struct FieldObject261810 FieldObject261810;
typedef struct FieldObject262F70 FieldObject262F70;
typedef struct FieldObject262E20 FieldObject262E20;
typedef struct FieldObject262490 FieldObject262490;
typedef struct FieldObject153D20 FieldObject153D20;
typedef struct FieldObject153E00 FieldObject153E00;

#ifdef __cplusplus
#include "overlays/1067-00/text_001DD3C0.h"
#include "overlays/lib/text_004CD3A0.h"

/** Partial LibClass178EA0 with vtable D_175290 in main data. */
class FieldClass175290 : public LibClass178EA0
{
public:
    /** @brief Construct the object and clear the words at offsets 0x210 and 0x214. */
    FieldClass175290();
    /** @brief Destroy the object. */
    virtual ~FieldClass175290();

    u32 unk210;
    u32 unk214;
};
/** Four aligned floating-point components; C++ copies them as one 128-bit word. */
typedef FieldVec4A FieldVector2624;

/** Partial Field object with vtable D_153E00 in main data; it adds vtable slot 0x1C. */
class FieldClass153E00 : public FieldClass150070
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass153E00();
    /** @brief Delete the attached object at offset 0x4C. */
    virtual void func_slot1c();
    u8 unk14[0x38];
    FieldClass150070* unk4c;
};
#else
/** Four aligned floating-point components used by the field vector helpers. */
typedef struct FieldVector2624
{
    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16))) FieldVector2624;
#endif

/** Aligned four-float value that can be cleared as one packed word. */
typedef union FieldVector262900
{
    float floats[4];
    unsigned __int128 packed;
} FieldVector262900;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Restore the receiver's table pointer and delete it when the signed flag is positive.
 * @param object Receiver to release, or null.
 * @param flags Signed deletion flag.
 * @return The original receiver pointer.
 */
FieldObject262F70* func_00262F70(FieldObject262F70* object, s16 flags);

/**
 * @brief Restore two table pointers, call the base cleanup, and optionally delete the receiver.
 * @param object Receiver to release, or null.
 * @param flags Signed deletion flag.
 * @return The original receiver pointer.
 */
FieldObject262E20* func_00262E20(FieldObject262E20* object, s16 flags);

/**
 * @brief Clear an aligned vector and set its fourth component to 1.0.
 * @param vector Vector to initialize.
 */
/**
 * @brief Clear an aligned vector.
 * @param vector Vector to clear.
 */
void func_002624B0(FieldVector262900* vector);

void func_00262900(FieldVector262900* vector);

/**
 * @brief Report the fixed type value for this receiver.
 * @param object Receiver to inspect.
 * @return Always 2.
 */
s32 func_00260840(FieldObject153D20* object);



/**
 * @brief Report the fixed type value for this receiver.
 * @param object Receiver to inspect.
 * @return Always 3.
 */
s32 func_00263680(FieldObject153E00* object);

/**
 * @brief Copy an aligned vector to receiver offsets 0x890 and 0x20, and set byte 0x50.
 * @param object Receiver to update.
 * @param vector Vector to copy.
 */
void func_00262490(FieldObject262490* object, const FieldVector2624* vector);

/**
 * @brief Copy an aligned vector to receiver offsets 0x880 and 0x30, and set byte 0x50.
 * @param object Receiver to update.
 * @param vector Vector to copy.
 */
void func_00263620(FieldObject262490* object, const FieldVector2624* vector);

/**
 * @brief Copy an aligned vector to receiver offsets 0x880 and 0x30, and set byte 0x50.
 * @param object Receiver to update.
 * @param vector Vector to copy.
 */
void func_00263640(FieldObject262490* object, const FieldVector2624* vector);

/**
 * @brief Copy an aligned vector to receiver offsets 0x890 and 0x20, and set byte 0x50.
 * @param object Receiver to update.
 * @param vector Vector to copy.
 */
void func_00263660(FieldObject262490* object, const FieldVector2624* vector);

/**
 * @brief Copy one aligned vector to two destinations.
 * @param first First destination.
 * @param second Second destination.
 * @param source Vector to copy.
 */
void func_002624C0(FieldVector2624* first, FieldVector2624* second,
                   const FieldVector2624* source);

/**
 * @brief Set all four vector components to one value.
 * @param vector Vector to update.
 * @param value Value to store in each component.
 * @return The vector.
 */
FieldVector2624* func_002624D0(FieldVector2624* vector, float value);

/**
 * @brief Return the supplied vector pointer.
 * @param vector Vector to return.
 * @return The supplied pointer.
 */
FieldVector2624* func_002624F0(FieldVector2624* vector);

/**
 * @brief Store two pointers at receiver offsets 0x24 and 0x28.
 * @param object Receiver to update.
 * @param first Pointer stored at 0x24.
 * @param second Pointer stored at 0x28.
 */
void func_00261810(FieldObject261810* object, void* first, void* second);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00261D20(void* object);

/**
 * @brief Return the fixed value 2.
 * @param object Receiver or first argument; unused.
 * @return Always 2.
 */
s32 func_00263610(void* object);

#ifdef __cplusplus
}
#endif

#endif
