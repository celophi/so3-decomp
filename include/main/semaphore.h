#ifndef SO3_MAIN_SEMAPHORE_H
#define SO3_MAIN_SEMAPHORE_H

#include "types.h"
#include "sdk/main/libkernl_00121940.h"
#include "ee.h"
#include "main/main.h"

#ifndef __cplusplus
typedef struct ResidentSemaphore ResidentSemaphore;
#endif

#ifdef __cplusplus

/** Kernel semaphore that deletes itself when destroyed; vtable D_0014F9E0. */
class ResidentSemaphore
{
public:
    /**
     * @brief Free a semaphore through the resident heap.
     * @param memory Allocation, or null.
     */
    static void operator delete(void* memory) throw()
    {
        resident_delete(memory);
    }

    s32 id;

    /** @brief Start without a kernel semaphore. */
    ResidentSemaphore() : id(-1)
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
     * @brief Take the semaphore without waiting.
     * @return True when the semaphore was taken.
     */
    bool poll_in_thread()
    {
        if (PollSema(id) < 0)
        {
            return false;
        }

        return true;
    }

    /**
     * @brief Take the semaphore without waiting, from interrupt context.
     * @return True when the semaphore was taken.
     */
    bool ipoll()
    {
        if (iPollSema(id) < 0)
        {
            return false;
        }

        return true;
    }

    /**
     * @brief Take the semaphore without waiting, with the interrupt-context call when interrupts are disabled.
     * @return True when the semaphore was taken.
     */
    bool poll()
    {
        if (ee_get_status() & EE_STATUS_EIE)
        {
            return poll_in_thread();
        }

        return ipoll();
    }

    /**
     * @brief Signal the semaphore from interrupt context.
     * @return True on success.
     */
    bool isignal()
    {
        if (iSignalSema(id) < 0)
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
    virtual ~ResidentSemaphore()
    {
        if (id >= 0)
        {
            DeleteSema(id);
        }
    }
};

/** Holds a semaphore for as long as it lives; vtable D_0014FAA8. */
class ResidentSemaphoreLock
{
public:
    ResidentSemaphore* semaphore;
    u8 held;

    /**
     * @brief Wait on a semaphore and hold it.
     * @param semaphore Semaphore to hold.
     */
    ResidentSemaphoreLock(ResidentSemaphore* semaphore)
    {
        this->semaphore = semaphore;
        held = 1;
        (void)semaphore->wait();
    }

    /** @brief Signal the semaphore if the lock holds it. */
    virtual ~ResidentSemaphoreLock()
    {
        if (held)
        {
            (void)semaphore->signal();
        }
    }
};
#endif

#endif
