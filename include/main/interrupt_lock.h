#ifndef SO3_MAIN_INTERRUPT_LOCK_H
#define SO3_MAIN_INTERRUPT_LOCK_H

#include "types.h"
#include "sdk/main/libkernl_00121940.h"
#include "ee.h"

#ifndef __cplusplus
typedef struct ResidentInterruptLock ResidentInterruptLock;
#endif

#ifdef __cplusplus
extern "C" s32 DIntr(void);

extern "C" s32 EIntr(void);

/** Scoped lock that disables interrupts while it lives, if they were enabled; vtable at 0x14FA60. */
class ResidentInterruptLock
{
public:
    u8 disabled;

    /** @brief Disable interrupts if they're enabled. */
    ResidentInterruptLock()
    {
        disabled = 0;

        if (ee_get_status() & EE_STATUS_EIE)
        {
            DIntr();
            disabled = 1;
        }
    }

    /** @brief Enable interrupts again if the lock disabled them. */
    virtual ~ResidentInterruptLock()
    {
        if (disabled)
        {
            EIntr();
        }
    }

    /**
     * @brief Report whether interrupts were enabled when the lock was taken.
     * @return True when the lock disabled them.
     */
    bool was_enabled() const
    {
        return disabled;
    }

    /** @brief Enable interrupts again early if the lock disabled them. */
    void unlock()
    {
        if (disabled)
        {
            EIntr();
            disabled = 0;
        }
    }

    /** @brief Disable interrupts again after unlock(), if they're enabled. */
    void relock()
    {
        if (ee_get_status() & EE_STATUS_EIE)
        {
            DIntr();
            disabled = 1;
        }
    }
};
#endif

#endif
