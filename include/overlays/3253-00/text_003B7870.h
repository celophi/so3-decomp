#ifndef SO3_OVERLAYS_3253_00_TEXT_003B7870_H
#define SO3_OVERLAYS_3253_00_TEXT_003B7870_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Return the address of the nested state word at offset 0x60.
 * @param object Object containing the nested state pointer at offset 0x50.
 * @return Address of the nested state word.
 */
void* func_003C6040(void* object);

/**
 * @brief Read the nested state's float at offset 0x4C.
 * @param object Object containing the nested state pointer at offset 0x50.
 * @return Stored float value.
 */
float func_003C6050(void* object);

/**
 * @brief Read and scale the nested state's float at offset 0x2C.
 * @param object Object containing the nested state pointer at offset 0x50.
 * @return Stored value scaled by 1/128.
 */
float func_003C6120(void* object);

/**
 * @brief Return the address of the nested state word at offset 0x20.
 * @param object Object containing the nested state pointer at offset 0x50.
 * @return Address of the nested state word.
 */
void* func_003C6420(void* object);

/**
 * @brief Read the nested state's float at offset 0x57C.
 * @param object Object containing the nested state pointer at offset 0x50.
 * @return Stored float value.
 */
float func_003C6430(void* object);

/**
 * @brief Evaluate the nested state value selected by the receiver's index.
 * @param object Object containing the nested state pointer and index.
 */
void func_003C6530(void* object);

/**
 * @brief Return the default floating-point callback value.
 * @param object Receiver or first argument; unused.
 * @return Always 1.0f.
 */
float func_003C7470(void* object);

/**
 * @brief Return the default floating-point callback value.
 * @param object Receiver or first argument; unused.
 * @return Always 1.0f.
 */
float func_003C74B0(void* object);

/**
 * @brief Clear the receiver's word at offset 0x44.
 * @param object Receiver to update.
 */
void func_003C7460(void* object);

/**
 * @brief Clear the receiver's word at offset 0x44.
 * @param object Receiver to update.
 */
void func_003C74A0(void* object);

/**
 * @brief Read the receiver's word at offset 0x1C.
 * @param object Receiver containing the word.
 * @return Stored word.
 */
u32 func_003B9000(void* object);

/**
 * @brief Test whether the receiver's word at offset 0x14 is nonzero.
 * @param object Receiver to inspect.
 * @return One when the word is nonzero; otherwise zero.
 */
s32 func_003B8B30(const void* object);

/**
 * @brief Mark the indexed battle entry active and clear its state word.
 * @param object Object containing the entry table at offset 0x14.
 * @param index Entry index.
 */
void func_003B8D30(void* object, s32 index);

/**
 * @brief Set the receiver's byte at offset 0x1AC to two.
 * @param object Receiver to update.
 */
void func_003C1FF0(void* object);

/**
 * @brief Set the receiver's byte at offset 0x518 to one.
 * @param object Receiver to update.
 */
void func_003C6DB0(void* object);

/**
 * @brief Store a word in the indexed record and mark it present.
 * @param object Owner of the indexed record table.
 * @param index Record index.
 * @param value Word stored at record offset +0x14.
 */
void func_003C36B0(void* object, s32 index, u32 value);
/**
 * @brief Store a word in the indexed record and mark it present.
 * @param object Owner of the indexed record table.
 * @param index Record index.
 * @param value Word stored at record offset +0x10.
 */
void func_003C36E0(void* object, s32 index, u32 value);
/**
 * @brief Store a word in the indexed record and mark it present.
 * @param object Owner of the indexed record table.
 * @param index Record index.
 * @param value Word stored at record offset +0x0C.
 */
void func_003C3710(void* object, s32 index, u32 value);
/**
 * @brief Store a word in the indexed record and mark it present.
 * @param object Owner of the indexed record table.
 * @param index Record index.
 * @param value Word stored at record offset +0x08.
 */
void func_003C3740(void* object, s32 index, u32 value);
/**
 * @brief Store two floats in the indexed record and mark them present.
 * @param object Owner of the indexed record table.
 * @param index Record index.
 * @param first First value stored at record offset +0x00.
 * @param second Second value stored at record offset +0x04.
 */
void func_003C3770(void* object, s32 index, float first, float second);
/**
 * @brief Mark the indexed record's additional value present.
 * @param object Owner of the indexed record table.
 * @param index Record index.
 */
void func_003C37A0(void* object, s32 index);

/**
 * @brief Set the update bit in the receiver and run its update routine.
 * @param object Receiver whose byte at +0x38C is updated.
 */
void func_003C4680(void* object);
/**
 * @brief Set the update bit in the receiver and run its update routine.
 * @param object Receiver whose byte at +0x1CC is updated.
 */
void func_003C5010(void* object);
/**
 * @brief Set the readiness byte when it has not yet been initialized.
 * @param object Receiver whose byte at +0x36C is updated.
 */
void func_003C5430(void* object);


/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003C6140(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003C6150(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_003C65C0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_003C65D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003C6660(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_003C6670(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_003C6680(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_003C6690(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003C66A0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_003C6800(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003C6890(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_003C68A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003C6BA0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_003C6BB0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_003C6BC0(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_003C6C30(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_003C6C40(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_003C6DA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003C7140(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_003C7150(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003C7160(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_003C7170(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
/** Recompute the receiver's scale at offset 0x70 after its update. */
void func_003C6A20(void* object);

/** Recompute the receiver's scale at offset 0x60 after its update. */
void func_003C6AC0(void* object);

/** Recompute the receiver's scale at offset 0x60 after its update. */
void func_003C6B60(void* object);

void func_003C7180(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_003C7450(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_003C7480(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_003C7490(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_003C74C0(void* object);

#ifdef __cplusplus
}
#endif

#endif
