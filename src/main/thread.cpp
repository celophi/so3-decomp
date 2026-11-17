#include "include_asm.h"
#include "main/interrupt_lock.h"
#include "main/system.h"

#define RESIDENT_THREAD_PRIORITY 50
#define RESIDENT_THREAD_SLICE_PRIORITY 44

/** Kernel thread creation parameters (libkernl ThreadParam). */
struct ThreadParam
{
    s32 status;
    void (*entry)(void*);
    void* stack;
    s32 stackSize;
    void* gpReg;
    s32 initPriority;
    s32 currentPriority;
    u32 attr;
    u32 option;
    s32 waitType;
    s32 waitId;
    s32 wakeupCount;
};

extern "C" {
/** The time-slice scheduler. */
extern ResidentThreadScheduler g_scheduler;

void resident_scheduler_remove(ResidentThreadScheduler* scheduler, ResidentTimeSlicedThread* thread);

void resident_scheduler_slice_alarm(s32 alarm_id, u16 time, void* common);

s32 iReleaseAlarm(s32 alarm_id);

s32 iChangeThreadPriority(s32 thread_id, s32 priority);

/** The global pointer value threads start with. */
extern u8 _gp;

s32 CreateThread(ThreadParam* param);

s32 TerminateThread(s32 thread_id);

s32 iTerminateThread(s32 thread_id);

bool resident_scheduler_add(ResidentThreadScheduler* scheduler, ResidentTimeSlicedThread* thread);

void ExitThread(void);

s32 DeleteThread(s32 thread_id);

void ExitDeleteThread(void);

s32 StartThread(s32 thread_id, void* argument);

s32 SleepThread(void);

/** @brief Stop and delete the kernel thread. */
inline ResidentThread::~ResidentThread()
{
    s32 id = thread_id;

    if (id >= 0)
    {
        if (id == GetThreadId())
        {
            delete stack;
            ExitDeleteThread();
        }
        else
        {
            TerminateThread(id);
            DeleteThread(thread_id);
            delete stack;
        }
    }
}

/** @brief The thread's body; the base class does nothing. */
void ResidentThread::run()
{
}

/**
 * @brief Start a thread's kernel thread, passing the thread as its argument.
 * @param thread Thread to start.
 * @return True on success.
 */
static inline bool thread_start(ResidentThread* thread)
{
    if (StartThread(thread->thread_id, thread) < 0)
    {
        return false;
    }

    return true;
}

/**
 * @brief Stop a thread: exit when it is the calling thread, otherwise terminate it, from interrupt context when
 * interrupts are disabled.
 * @param thread Thread to stop.
 * @return True on success.
 */
static inline bool thread_stop(ResidentThread* thread)
{
    if (ee_get_status() & EE_STATUS_EIE)
    {
        if (thread->thread_id == GetThreadId())
        {
            ExitThread();
            return true;
        }

        if (TerminateThread(thread->thread_id) < 0)
        {
            return false;
        }

        return true;
    }

    if (iTerminateThread(thread->thread_id) < 0)
    {
        return false;
    }

    return true;
}

/**
 * @brief Start a time-sliced thread and add it to the scheduler, stopping it again when the scheduler is full.
 * @return One on success, otherwise zero.
 */
s32 ResidentTimeSlicedThread::start_sliced()
{
    if (thread_start(this))
    {
        if (resident_scheduler_add(&g_scheduler, this))
        {
            return 1;
        }

        (void)thread_stop(this);
        return 0;
    }

    return 0;
}

/**
 * @brief Set a time-sliced thread's slice and create it at the normal resident priority.
 * @param thread Thread.
 * @param time_slice Horizontal syncs per slice.
 * @param stack_size Stack size in bytes.
 * @return Nonzero when the thread was created.
 */
s32 resident_sliced_thread_create(ResidentTimeSlicedThread* thread, s16 time_slice, s32 stack_size)
{
    thread->time_slice = time_slice;
    return resident_thread_create(thread, RESIDENT_THREAD_PRIORITY, stack_size);
}

/** @brief Remove the thread from the scheduler and destroy it. */
ResidentTimeSlicedThread::~ResidentTimeSlicedThread()
{
    resident_scheduler_remove(&g_scheduler, this);
}

/**
 * @brief Start a thread, or stop it (exiting when it is the calling thread).
 * @param object Thread.
 * @param run Nonzero to start it; stored in the sound system's unk351.
 */
void resident_thread_set_running(void* object, u8 run)
{
    ResidentThread* thread = (ResidentThread*)object;

    resident_system_get_sound(&g_system)->unk351 = run;

    if (run)
    {
        thread->start();
        return;
    }

    (void)thread_stop(thread);
}

/**
 * @brief Stop handing out time slices, returning the running thread to the normal priority.
 * @param scheduler Scheduler.
 */
void resident_scheduler_stop(ResidentThreadScheduler* scheduler)
{
    if (scheduler->active)
    {
        if (scheduler->current)
        {
            if (scheduler->alarm_id >= 0)
            {
                iReleaseAlarm(scheduler->alarm_id);
                scheduler->alarm_id = -1;
            }

            iChangeThreadPriority(scheduler->current->thread_id, RESIDENT_THREAD_PRIORITY);
            scheduler->current = 0;
        }

        scheduler->active = 0;
    }
}

static inline bool scheduler_slot_empty(ResidentThreadScheduler* scheduler, s32 index)
{
    if (scheduler->threads[index])
    {
        return false;
    }

    return true;
}

/**
 * @brief End the running time slice and give the next thread its slice, from interrupt context.
 * @param scheduler Scheduler.
 */
void resident_scheduler_next_slice(ResidentThreadScheduler* scheduler)
{
    scheduler->alarm_id = -1;

    if (scheduler->current)
    {
        iChangeThreadPriority(scheduler->current->thread_id, RESIDENT_THREAD_PRIORITY);
        scheduler->current = 0;
    }

    do
    {
        if (!scheduler_slot_empty(scheduler, scheduler->next))
        {
            scheduler->current = scheduler->threads[scheduler->next];
            iChangeThreadPriority(scheduler->current->thread_id, RESIDENT_THREAD_SLICE_PRIORITY);
            scheduler->next++;
            scheduler->alarm_id = resident_system_iset_alarm(&g_system, scheduler->current->time_slice,
                                                             resident_scheduler_slice_alarm, scheduler);
            return;
        }

        scheduler->next++;
    } while (scheduler->next < 8);

    scheduler->active = 0;
}

/**
 * @brief Alarm handler that ends the running time slice while the scheduler is active.
 * @param alarm_id Alarm.
 * @param time Time the alarm fired.
 * @param common Scheduler.
 */
void resident_scheduler_slice_alarm(s32 alarm_id, u16 time, void* common)
{
    ResidentThreadScheduler* scheduler = (ResidentThreadScheduler*)common;

    if (scheduler->active)
    {
        resident_scheduler_next_slice(scheduler);
    }

    ee_exit_handler();
}

/**
 * @brief Sleep until another thread wakes this one.
 * @return True on success.
 */
static inline bool thread_sleep(void)
{
    if (SleepThread() < 0)
    {
        return false;
    }

    return true;
}

/**
 * @brief Body of the scheduler's thread: on every wakeup while no round is running, copy the added threads into the
 * round and, when there are any, start handing out slices.
 */
void ResidentThreadScheduler::run()
{
    for (;;)
    {
        do
        {
            (void)thread_sleep();
        } while (this->active);

        (void)this->semaphore.wait();
        bool any = false;

        for (s32 i = 0; i < 8; i++)
        {
            if ((this->threads[i] = this->registered[i]) != 0 && !any)
            {
                any = true;
            }
        }

        (void)this->semaphore.signal();

        if (this->active || !any)
        {
            continue;
        }

        DIntr();
        this->active = 1;
        this->next = 0;
        this->current = 0;
        this->alarm_id = resident_system_set_alarm(&g_system, this->unk64 + 2, resident_scheduler_slice_alarm, this);
        EIntr();
    }
}

/**
 * @brief Set a thread's priority, with the interrupt-context call when interrupts are disabled.
 * @param thread Thread.
 * @param priority New priority.
 * @return True on success.
 */
static inline bool thread_change_priority(ResidentThread* thread, s32 priority)
{
    u32 status = ee_get_status();

    thread->priority = priority;

    if (status & EE_STATUS_EIE)
    {
        if (ChangeThreadPriority(thread->thread_id, priority) < 0)
        {
            return false;
        }

        return true;
    }

    if (iChangeThreadPriority(thread->thread_id, priority) < 0)
    {
        return false;
    }

    return true;
}

/**
 * @brief Remove a time-sliced thread from the scheduler, returning it to the normal priority if its slice is running.
 * @param scheduler Scheduler.
 * @param thread Thread to remove.
 */
void resident_scheduler_remove(ResidentThreadScheduler* scheduler, ResidentTimeSlicedThread* thread)
{
    ResidentSemaphoreLock lock(&scheduler->semaphore);
    ResidentInterruptLock interrupts;

    for (s32 i = 0; i < 8; i++)
    {
        if (scheduler->registered[i] == thread)
        {
            scheduler->registered[i] = 0;
            scheduler->threads[i] = 0;

            if (scheduler->current == thread)
            {
                (void)thread_change_priority(scheduler->current, RESIDENT_THREAD_PRIORITY);
                scheduler->current = 0;
            }
        }
    }
}

/**
 * @brief Add a time-sliced thread to the scheduler's first free entry.
 * @param scheduler Scheduler.
 * @param thread Thread to add.
 * @return True when it was added, false when all eight entries are taken.
 */
bool resident_scheduler_add(ResidentThreadScheduler* scheduler, ResidentTimeSlicedThread* thread)
{
    ResidentSemaphoreLock lock(&scheduler->semaphore);
    ResidentInterruptLock interrupts;

    for (s32 i = 0; i < 8; i++)
    {
        if (scheduler->registered[i] == 0)
        {
            scheduler->registered[i] = thread;
            return true;
        }
    }

    return false;
}

/**
 * @brief Wake a thread from interrupt context.
 * @param object Thread.
 * @return True on success.
 */
s32 resident_thread_wakeup(const void* object)
{
    return iWakeupThread(static_cast<const ResidentThread*>(object)->thread_id) >= 0;
}

/**
 * @brief Wake a sleeping thread.
 * @param thread_id Thread ID.
 * @return True on success.
 */
static inline bool thread_wakeup(s32 thread_id)
{
    if (WakeupThread(thread_id) < 0)
    {
        return false;
    }

    return true;
}

/**
 * @brief Wake a sleeping thread from interrupt context.
 * @param thread_id Thread ID.
 * @return True on success.
 */
static inline bool thread_iwakeup(s32 thread_id)
{
    if (iWakeupThread(thread_id) < 0)
    {
        return false;
    }

    return true;
}

/**
 * @brief Wake a thread, with the interrupt-context call when interrupts are disabled.
 * @param thread Thread to wake.
 * @return True on success.
 */
bool resident_thread_wake(ResidentThread* thread)
{
    if (ee_get_status() & EE_STATUS_EIE)
    {
        return thread_wakeup(thread->thread_id);
    }

    return thread_iwakeup(thread->thread_id);
}

/** Return whether the resident thread sleep request succeeds. */
s32 resident_thread_sleep(void)
{
    return SleepThread() >= 0;
}

/**
 * @brief Start the kernel thread, passing the thread as its argument.
 * @return Nonzero on success.
 */
s32 ResidentThread::start()
{
    return StartThread(thread_id, this) >= 0;
}

// TODO: This only matches at optimization level 0. It homes its argument and leaves its delay slots empty, so I
// think the original turned the optimizer off here, maybe to keep the thread entry easy to step through.
#pragma push
#pragma optimization_level 0

/**
 * @brief Entry point of every resident thread: run the thread's body, then delete the thread.
 * @param argument The thread.
 */
void resident_thread_entry(void* argument)
{
    ResidentThread* thread = (ResidentThread*)argument;
    thread->run();
    delete thread;
}
#pragma pop

/**
 * @brief Create the kernel thread with a new stack; it runs the thread's body once started.
 * @param thread Thread.
 * @param priority Thread priority.
 * @param stack_size Stack size in bytes.
 * @return Nonzero when the thread was created, zero when it already exists or creation failed.
 */
s32 resident_thread_create(ResidentThread* thread, s32 priority, s32 stack_size)
{
    if (thread->thread_id >= 0)
    {
        return 0;
    }

    thread->stack = new (0) u8[stack_size];

    if (thread->stack == 0)
    {
        return 0;
    }

    FlushCache(0);
    ThreadParam param;
    param.entry = resident_thread_entry;
    param.stack = thread->stack;
    param.stackSize = stack_size;
    param.gpReg = &_gp;
    param.initPriority = priority;
    thread->priority = priority;
    thread->thread_id = CreateThread(&param);
    return thread->thread_id >= 0;
}

/** @brief Destroy the scheduler and its semaphore. */
ResidentThreadScheduler::~ResidentThreadScheduler()
{
}
}
