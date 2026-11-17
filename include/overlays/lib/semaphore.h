#ifndef SO3_OVERLAYS_LIB_SEMAPHORE_H
#define SO3_OVERLAYS_LIB_SEMAPHORE_H

#include "types.h"
#include "sdk/main/libkernl_00121940.h"
#include "ee.h"

#ifdef __cplusplus
extern "C" s32 DIntr(void);

extern "C" s32 EIntr(void);

/** Lib's own copy of the resident interrupt lock, with vtable D_001724D8 in main data. */
class LibInterruptLock
{
public:
    u8 disabled;

    /** @brief Disable interrupts if they're enabled. */
    LibInterruptLock()
    {
        disabled = 0;

        if (ee_get_status() & EE_STATUS_EIE)
        {
            DIntr();
            disabled = 1;
        }
    }

    /** @brief Enable interrupts again if the lock disabled them. */
    virtual ~LibInterruptLock()
    {
        if (disabled)
        {
            EIntr();
        }
    }
};

/**
 * Lib's own copy of the resident kernel semaphore, with vtable D_001724C8 in main data. Unlike the resident one it has
 * no operator delete of its own.
 */
class LibSemaphore
{
public:
    s32 id;

    /** @brief Start without a kernel semaphore. */
    LibSemaphore() : id(-1)
    {
    }

    /**
     * @brief Create the kernel semaphore.
     * @param initial Starting count.
     * @param maximum Largest count.
     */
    void create(s32 initial, s32 maximum)
    {
        SemaParam param;
        param.initCount = initial;
        param.maxCount = maximum;
        id = CreateSema(&param);
    }

    /**
     * @brief Wait on the semaphore.
     * @return True on success.
     */
    bool wait()
    {
        if (WaitSema(id) < 0)
        {
            return false;
        }

        return true;
    }

    /**
     * @brief Signal the semaphore, with the interrupt-context call when interrupts are disabled.
     * @return True on success.
     */
    bool signal()
    {
        if (ee_get_status() & EE_STATUS_EIE)
        {
            if (SignalSema(id) < 0)
            {
                return false;
            }

            return true;
        }

        if (iSignalSema(id) < 0)
        {
            return false;
        }

        return true;
    }

    /** @brief Delete the kernel semaphore, if one was created. */
    virtual ~LibSemaphore()
    {
        if (id >= 0)
        {
            DeleteSema(id);
        }
    }
};

/** Lib's own copy of the resident semaphore lock, with vtable D_001724A0 in main data. */
class LibSemaphoreLock
{
public:
    LibSemaphore* semaphore;
    u8 held;

    /**
     * @brief Wait on a semaphore and hold it.
     * @param semaphore Semaphore to hold.
     */
    LibSemaphoreLock(LibSemaphore* semaphore)
    {
        this->semaphore = semaphore;
        held = 1;
        (void)semaphore->wait();
    }

    /** @brief Signal the semaphore if the lock holds it. */
    virtual ~LibSemaphoreLock()
    {
        if (held)
        {
            (void)semaphore->signal();
        }
    }
};
#endif

#endif
