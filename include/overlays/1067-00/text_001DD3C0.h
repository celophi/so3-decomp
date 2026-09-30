#ifndef SO3_OVERLAYS_1067_00_TEXT_001DD3C0_H
#define SO3_OVERLAYS_1067_00_TEXT_001DD3C0_H

#include "types.h"
#include "overlays/1067-00/text_001FD860.h"

/** Partial receiver whose word at offset 0x70 refers to an attached object. */
typedef struct FieldAttachedObject70
{
    u8 unk00[0x70];
    void* unk70;
} FieldAttachedObject70;

/** Partial object linked into a circular list, with flag and state words. */
typedef struct FieldFlaggedListObject
{
    u8 unk00[8];
    struct FieldFlaggedListObject* next;
    u8 unk0c[0x68];
    s32 unk74;
    u32 unk78;
    void* unk7c;
    u8 unk80[0xC];
    u8 unk8c_0_1 : 2;
    u8 unk8c_2 : 1;
    u8 unk8c_3_7 : 5;
    u8 unk8d[0x17B];
    u32 unk208;
} FieldFlaggedListObject;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Default virtual handler that performs no work.
 * @param object Receiver of the virtual call.
 */
void func_001DD400(void* object);

/**
 * @brief Default virtual handler that performs no work.
 * @param object Receiver of the virtual call.
 */
void func_001DD410(void* object);

/**
 * @brief Store the attached object pointer at offset 0x70.
 * @param object Receiver to update.
 * @param attached Object pointer to store.
 */
void func_001DD420(FieldAttachedObject70* object, void* attached);

/**
 * @brief Default virtual handler that performs no work.
 * @param object Receiver of the virtual call.
 */
void func_001DD430(void* object);

/**
 * @brief Report the fixed value 4 for this receiver class.
 * @param object Receiver of the virtual call.
 * @return Always 4.
 */
s32 func_001DD490(const void* object);

/**
 * @brief Call func_002379A0 with a nonzero flag for each listed object whose flag bit 3 is set.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 */
void func_001DD570(FieldFlaggedListObject* list);

/**
 * @brief Clear the word at offset 0x208 for each listed object whose flag bit 1 is set.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 */
void func_001DD6E0(FieldFlaggedListObject* list);

/**
 * @brief Call func_00227130 for each listed object whose flag bit 1 is set.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 */
void func_001DDB30(FieldFlaggedListObject* list);

/**
 * @brief Return the receiver unchanged.
 * @param object Receiver of the virtual call.
 * @return object.
 */
void* func_001DDCD0(void* object);

/**
 * @brief Combine the func_00204420 test with a clear bit 5 at offset 0x8C.
 * @param object Receiver passed to func_00204420.
 * @return True when func_00204420 succeeds and bit 5 of the byte at offset 0x8C is clear.
 */
bool func_001DDCE0(const FieldFloatGateState7C* object);

/**
 * @brief Find a listed object with a matching key, bit 2 at offset 0x8C clear and a nonnull pointer at offset 0x7C.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 * @param key Value compared with the word at offset 0x74.
 * @return The first matching object, or null if none matches.
 */
FieldFlaggedListObject* func_001DDF50(FieldFlaggedListObject* list, s32 key);

/**
 * @brief Default virtual handler that performs no work.
 * @param object Receiver of the virtual call.
 */
void func_001DE3B0(void* object);

/**
 * @brief Default virtual handler that performs no work.
 * @param object Receiver of the virtual call.
 */
void func_001DE3C0(void* object);

#ifdef __cplusplus
}
#endif

#endif
