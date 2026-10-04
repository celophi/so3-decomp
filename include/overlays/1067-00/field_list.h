#ifndef SO3_OVERLAYS_1067_00_FIELD_LIST_H
#define SO3_OVERLAYS_1067_00_FIELD_LIST_H

#include "overlays/lib/ui_object.h"

#ifdef __cplusplus
/**
 * Lib list class with vtable D_1502A0 in main data. It adds no data to
 * LibClass178DD0; its sentinel is the list's first 12 bytes (unk00).
 */
class FieldClass1502A0 : public LibClass178DD0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass1502A0()
    {
    }

    /**
     * @brief Store the attached object pointer at offset 0x70.
     * @param attached Object pointer to store.
     */
    virtual void func_004295B0(void* attached);

    /** @brief Default handler that performs no work. */
    virtual void func_004295C0();

    /** @brief Detach and delete every listed object; traversal stops on return to the sentinel or at a null link. */
    virtual void func_001DD730();
};
#endif

#endif
