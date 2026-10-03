#ifndef SO3_OVERLAYS_LIB_TEXT_004BD360_H
#define SO3_OVERLAYS_LIB_TEXT_004BD360_H

#include "types.h"
#include "overlays/lib/text_003E68C0.h"

/** Opaque Lib text receiver using the main table D_178750. */
typedef struct LibObject178750 LibObject178750;

/** Four scalar float bounds returned from the receiver at offset 0xE8. */
typedef struct LibBounds4C69B0
{
    float unk00;
    float unk04;
    float unk08;
    float unk0c;
} LibBounds4C69B0;

#ifdef __cplusplus
/**
 * Partial 0x70-byte Lib animation object, with vtable D_178220 in main data.
 * It holds a data block at offset 0x30 (owned unless the byte at 0x68 is set)
 * and an array at offset 0x40.
 */
class LibClass178220 : public LibClass171EA0
{
public:
    /** @brief Construct an empty object. */
    LibClass178220();

    u8 unk04[0x2C];
    void* unk30;
    u8 unk34[0xC];
    u8* unk40;
    u8 unk44[0x24];
    u8 unk68;
    u8 unk69[5];
    u8 unk6e;
    u8 unk6f;
};

/** Partial 0xD0-byte Lib object, with vtable D_178370 in main data. */
class LibClass178370 : public LibClass171EA0
{
public:
    /** @brief Construct an empty object. */
    LibClass178370();

    u8 unk04[0xCC];
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Rebuild the receiver's data and return its scalar bounds.
 * @param object Lib text receiver to rebuild.
 * @return Bounds at offset 0xE8, or null when rebuilding fails.
 */
LibBounds4C69B0* func_004C69B0(LibObject178750* object);

/**
 * @brief Release the data a LibClass178220 builds from its block at offset 0x40.
 * @param object Object to update.
 */
void func_004BDD10(void* object);

/**
 * @brief Bind a LibClass178220 to a second object.
 * @param object Object to update.
 * @param target Object to bind; FieldClass150EB0 passes its object at offset 0x7C.
 */
void func_004BFE10(void* object, void* target);

/**
 * @brief Evaluate a VU0 polynomial approximation of a trigonometric function.
 *
 * Inferred to be the cosine: Field's ring builder uses it for the height of a
 * point measured from the pole.
 * @param angle Angle in radians.
 * @return The approximated value.
 */
float func_004CC3E0(float angle);

/**
 * @brief Evaluate a VU0 polynomial approximation of a trigonometric function.
 *
 * Inferred to be the sine, the partner of func_004CC3E0.
 * @param angle Angle in radians.
 * @return The approximated value.
 */
float func_004CC690(float angle);

#ifdef __cplusplus
}
#endif

#endif
