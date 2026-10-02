#ifndef SO3_OVERLAYS_1067_00_TEXT_0023B1D0_H
#define SO3_OVERLAYS_1067_00_TEXT_0023B1D0_H

#include "types.h"

typedef struct FieldObject23CE80 FieldObject23CE80;
typedef struct FieldObject23CEB0 FieldObject23CEB0;
typedef struct FieldObject23CEA0 FieldObject23CEA0;
typedef struct FieldObject23CB30 FieldObject23CB30;
typedef struct FieldObject23BAB0 FieldObject23BAB0;
typedef struct FieldState23B3A0 FieldState23B3A0;
typedef struct FieldObject153270 FieldObject153270;
typedef struct FieldNode23D310 FieldNode23D310;
typedef struct FieldObject23D310 FieldObject23D310;
typedef struct FieldObject23D020 FieldObject23D020;
typedef struct FieldObject23B950 FieldObject23B950;
typedef struct FieldObject23B850 FieldObject23B850;
typedef struct FieldTarget23B850 FieldTarget23B850;
typedef struct FieldObject23C180 FieldObject23C180;
typedef struct FieldObject23B1D0 FieldObject23B1D0;
typedef struct FieldObject23B280 FieldObject23B280;

/** Linked nodes used by the field coordinate selector. */
struct FieldObject23D310
{
    FieldNode23D310* first;
};

/** Coordinate selection state and its currently selected node index. */
struct FieldObject23B1D0
{
    u8 unk00[0x3C];
    u8 flag3C;
    u8 unk3D[3];
    u8 point40[0x10];
    float x;
    float y;
    u8 unk58[0x1D];
    u8 flag75;
    u8 unk76[6];
    FieldObject23D310 nodes;
    u8 unk80[8];
    s32 selected;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Select a node and either copy or apply its coordinates.
 * @param object Receiver with the node list.
 * @param index Number of links to follow and value stored on success.
 * @param direct Copy coordinates directly when nonzero; otherwise apply them through the field helper.
 * @return One when a node is found, otherwise zero.
 */
s32 func_0023B1D0(FieldObject23B1D0* object, s32 index, s32 direct);

/**
 * @brief Set the unsigned count and update position from the receiver's grid values.
 * @param object Receiver to update.
 * @param count Count stored at offset 0x90.
 */
void func_0023B280(FieldObject23B280* object, u16 count);

/**
 * @brief Clear the unsigned count and update position from the receiver's grid values.
 * @param object Receiver to update.
 */
void func_0023B310(FieldObject23B280* object);

/**
 * @brief Set a target and pass its position to the field helper.
 * @param object Receiver that stores the target.
 * @param target Target with the position to pass, or null for zero values.
 * @param extra Additional value passed to the final helper.
 */
void func_0023B850(FieldObject23B850* object, FieldTarget23B850* target, void* extra);

/**
 * @brief Detach an object and add it to the resident queue.
 * @param object Object to detach and queue.
 */
void func_0023BF50(void* object);

/**
 * @brief Initialize the receiver's table and state fields after its base initializer.
 * @param object Receiver to initialize.
 * @return The receiver.
 */
FieldObject23B950* func_0023B950(FieldObject23B950* object);

/**
 * @brief Restore three table pointers, call base cleanup, and optionally delete the receiver.
 * @param object Receiver to release, or null.
 * @param flags Signed deletion flag.
 * @return The original receiver pointer.
 */
FieldObject23C180* func_0023C180(FieldObject23C180* object, s16 flags);

/**
 * @brief Clear the receiver state, initialize its resident data, and attach it to the field runtime.
 * @param object Receiver to initialize.
 * @param first_float First value forwarded to the resident initializer.
 * @param second_float Second value forwarded to the resident initializer.
 */
void func_0023D020(FieldObject23D020* object, float first_float, float second_float);

/**
 * @brief Store three floats and update receiver state when a target exists and the third float is nonzero.
 * @param object Receiver to update.
 * @param x First float.
 * @param y Second float.
 * @param z Third float.
 * @return One when updated, otherwise zero.
 */
s32 func_0023BAB0(FieldObject23BAB0* object, float x, float y, float z);

/**
 * @brief Set the total from the current index, row count, and width.
 * @param object Receiver to update.
 */
void func_0023CB30(FieldObject23CB30* object);

/**
 * @brief Store two floats at receiver offsets 0xFC and 0x100.
 * @param object Receiver to update.
 * @param first Value stored at 0xFC.
 * @param second Value stored at 0x100.
 */
void func_0023CE60(FieldObject23CE80* object, float first, float second);

/**
 * @brief Store two floats at receiver offsets 0xF4 and 0xF8.
 * @param object Receiver to update.
 * @param first Value stored at 0xF4.
 * @param second Value stored at 0xF8.
 */
void func_0023CE70(FieldObject23CEB0* object, float first, float second);

/**
 * @brief Update position from the signed count and width.
 * @param object Receiver to update.
 * @return Always 1.
 */
s32 func_0023CEE0(FieldObject23CEB0* object);

/**
 * @brief Apply position offsets, optionally update the count, then refresh position.
 * @param object Receiver to update.
 * @param value New signed count when positive.
 * @param first_delta First position offset.
 * @param second_delta Second position offset.
 * @return Always 1.
 */
s32 func_0023CF50(FieldObject23CEB0* object, s16 value, float first_delta, float second_delta);

/**
 * @brief Store a byte at receiver offset 0xAD.
 * @param object Receiver to update.
 * @param value Byte to store.
 */
void func_0023CEA0(FieldObject23CEA0* object, u8 value);

/**
 * @brief Store two byte dimensions and their product minus one.
 * @param object Receiver to update.
 * @param width First byte value.
 * @param height Second byte value.
 */
void func_0023CE80(FieldObject23CE80* object, u8 width, u8 height);

/**
 * @brief Store two floats in both state pairs and set two state bytes.
 * @param object Receiver to update.
 * @param first Value stored at offsets 0xF4 and 0xC0.
 * @param second Value stored at offsets 0xF8 and 0xC4.
 * @return Always 1.
 */
s32 func_0023CEB0(FieldObject23CEB0* object, float first, float second);

/**
 * @brief Advance through a receiver's linked nodes.
 * @param object Receiver holding the first node.
 * @param count Additional next links to follow from the first node's next pointer.
 * @return The reached node, or null if the list ends early.
 */
FieldNode23D310* func_0023D310(FieldObject23D310* object, s32 count);

/**
 * @brief Read the unsigned halfword at offset 0x90.
 * @param object Receiver.
 * @return The current unsigned halfword.
 */
u16 func_0023B3A0(FieldState23B3A0* object);

/**
 * @brief Report the fixed category for this object.
 * @param object Receiver.
 * @return Always 4.
 */
s32 func_0023D2B0(FieldObject153270* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0023D2A0(void* object);

#ifdef __cplusplus
}
#endif

#endif
