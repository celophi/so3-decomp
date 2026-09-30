#ifndef SO3_OVERLAYS_1070_00_TEXT_00244310_H
#define SO3_OVERLAYS_1070_00_TEXT_00244310_H

#include "overlays/1070-00/text_00284BF0.h"

/** Partial circular-list element with a numeric key at offset 0x18. */
typedef struct FieldKeyedListElement18
{
    FieldListNode link;
    u8 unk0c[0xC];
    u32 unk18;
} FieldKeyedListElement18;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Find the first circular-list element with the requested numeric key.
 * @param object Context containing the list sentinel.
 * @param key Numeric key to find.
 * @return The matching element, or null after returning to the sentinel.
 */
FieldKeyedListElement18* func_002492E0(FieldContext38* object, u32 key);

#ifdef __cplusplus
}
#endif

#endif
