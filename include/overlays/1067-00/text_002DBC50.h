#ifndef SO3_OVERLAYS_1067_00_TEXT_002DBC50_H
#define SO3_OVERLAYS_1067_00_TEXT_002DBC50_H

#include "types.h"
#include "overlays/1067-00/text_002DB1D0.h"
#include "overlays/1067-00/text_002AE9E0.h"

struct FieldReset2DCA70;
struct FieldReset2DCA90;
struct FieldFloatState2DCCF0;

#ifdef __cplusplus
class FieldClass15B900;

/** Partial list owner with vtable D_15B950 in main data and three track handlers. */
class FieldClass15B950 : public FieldClass1502A0
{
public:
    /** @brief Release the owned track, then destroy the list. */
    virtual ~FieldClass15B950();

    /**
     * @brief Append the listed vectors to the track and release their nodes.
     * @param key Running sort value updated for each node.
     */
    virtual void func_002DD7B0(float* key);

    /**
     * @brief Replace the track using the supplied initial component.
     * @param first Initial first component.
     * @param reuse Nonzero allows derived handlers to reuse existing track data.
     */
    virtual void func_002DD870(const float* first, s32 reuse);

    /** @brief Clear the listed nodes and release the owned track. */
    virtual void func_002DDA70();

    FieldClass1595D0* unk78;
    u8 unk7c[0x0C];
    u8 unk88;
    u8 unk89[3];
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Return the array element unchanged during construction.
 * @param object Array element.
 * @return The same element.
 */
void* func_002DBFF0(void* object);

/**
 * @brief Detach the object and append it to the resident object queue.
 * @param object Object to detach and queue.
 */
void func_002DCA40(FieldClass150070* object);

/**
 * @brief Clear the state at offsets 0x40 through 0x50.
 * @param object State to reset.
 */
void func_002DCA70(FieldReset2DCA70* object);

/**
 * @brief Clear the state at offsets 0x18 through 0x28.
 * @param object State to reset.
 */
void func_002DCA90(FieldReset2DCA90* object);

/**
 * @brief Store a float divisor and ratio, then clear two state words.
 * @param object State to update.
 * @param value_a0 Pointer stored at offset 0xA0.
 * @param value_a4 Value stored at offset 0xA4.
 * @param value_90 Divisor stored at offset 0x90.
 * @param value_98 Numerator used to derive the value at offset 0x98.
 */
void func_002DCCF0(FieldFloatState2DCCF0* object, void* value_a0, s32 value_a4, float value_90, float value_98);

#ifdef __cplusplus
}
#endif

#endif
