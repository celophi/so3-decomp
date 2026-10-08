#ifndef SO3_OVERLAYS_1067_00_TEXT_002BC510_H
#define SO3_OVERLAYS_1067_00_TEXT_002BC510_H

#include "overlays/1067-00/text_001DD3C0.h"

/** Partial receiver shared by the two direct-called setters. */
typedef struct FieldState2BC510
{
    u8 unk00[0x38];
    float unk38;
    float unk3C;
    u8 unk40[0x0C];
    u8 unk4C;
    u8 unk4D[3];
    s32 unk50;
    s32 unk54;
    s32 unk58;
    s32 unk5C;
} FieldState2BC510;

/** Partial receiver with a state byte at offset 0x124. */
typedef struct FieldState2BD1F0
{
    u8 unk00[0x124];
    u8 unk124;
} FieldState2BD1F0;

struct FieldState2BDF70;

#ifdef __cplusplus
/** Partial Field object with vtable D_159A80 in main data. */
class FieldClass159A80 : public FieldClass150070
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass159A80();
    void* unk14;
    u16 unk18;
};

extern "C" {
#endif

/**
 * @brief Apply a mode to the object.
 * @param object Object to update.
 * @param mode Mode value; zero and one select different updates.
 */
void func_002BC650(void* object, u16 mode);

/**
 * @brief Append this receiver to the resident object queue.
 * @param object Receiver to append.
 */
void func_002BC5B0(FieldClass150070* object);

/**
 * @brief Apply the requested state when the global receiver is available.
 * @param object Caller receiver; unused by the imported routine.
 * @param enabled State passed to the imported routine.
 * @return True when the global receiver is available.
 */
bool func_002BC610(void* object, bool enabled);

/**
 * @brief Store four integer values and mark them present.
 * @param object Receiver to update.
 * @param first First value.
 * @param second Second value.
 * @param third Third value.
 * @param fourth Fourth value.
 */
void func_002BD080(FieldState2BC510* object, s32 first, s32 second, s32 third, s32 fourth);

/**
 * @brief Run the imported update routine for this receiver.
 * @param object Receiver to update.
 */
void func_002BD0A0(void* object);

/**
 * @brief Mark the receiver active and append it to the resident object queue.
 * @param object Receiver to mark and queue.
 */
void func_002BD1F0(FieldState2BD1F0* object);

/**
 * @brief Store two float values in the receiver.
 * @param object Receiver to update.
 * @param first First float.
 * @param second Second float.
 */
void func_002BDF60(FieldState2BC510* object, float first, float second);

/**
 * @brief Store a value and four coordinates derived from global state.
 * @param object State to update.
 * @param value Stored halfword; zero leaves the state unchanged.
 * @return True when the ID was accepted.
 */
bool func_002BDF70(FieldState2BDF70* object, u16 value);

#ifdef __cplusplus
/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 9.
 */
s32 func_002BC5A0(FieldClass150070* object);
}
#endif

#endif
