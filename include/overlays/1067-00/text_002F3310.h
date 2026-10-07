#ifndef SO3_OVERLAYS_1067_00_TEXT_002F3310_H
#define SO3_OVERLAYS_1067_00_TEXT_002F3310_H

#include "types.h"
#include "overlays/1067-00/text_002F1B20.h"

#include "overlays/1067-00/text_001DD3C0.h"

typedef struct FieldByte60F3310 FieldByte60F3310;

#ifdef __cplusplus
/** Partial Field object with vtable D_15BA10 in main data and an owned child at offset 0x14. */
class FieldClass15BA10 : public FieldClass150070
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass15BA10();
    /** @brief Detach and delete the child, then delete this object. */
    virtual void func_001DD7B0();
    FieldClass150070* unk14;
};

/** Partial Field object with vtable D_15BA50 in main data and an owned child at offset 0x18. */
class FieldClass15BA50 : public FieldClass150070
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass15BA50();
    /** @brief Detach this object, delete the child when present, then delete this object. */
    virtual void func_001DD7B0();
    u8 unk14[4];
    FieldClass150070* unk18;
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Store two in the receiver's byte at offset 0x60.
 * @param object Receiver containing the byte.
 */
void func_002F9760(FieldByte60F3310* object);


#ifdef __cplusplus
/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 9.
 */
s32 func_002F3860(FieldClass150070* object);
#endif

#ifdef __cplusplus
}
#endif

#endif
