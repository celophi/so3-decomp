#ifndef SO3_MAIN_THREAD_H
#define SO3_MAIN_THREAD_H

#include "types.h"
#include "sdk/main/libkernl_00121940.h"
#include "ee.h"
#include "main/semaphore.h"

#ifndef __cplusplus
typedef struct ResidentThread ResidentThread;
typedef struct ResidentThreadScheduler ResidentThreadScheduler;
typedef struct ResidentTimeSlicedThread ResidentTimeSlicedThread;
#endif

#ifdef __cplusplus
/** Kernel thread with its own stack; vtable D_0014FBA0. */
class ResidentThread
{
    public:
        /** @brief Start without a stack or a kernel thread. */
        ResidentThread() : stack(0), thread_id(-1)
        {
        }

        s32 priority;
        u8* stack;
        s32 thread_id;

        /** @brief Stop and delete the kernel thread. */
        virtual ~ResidentThread();

        /**
         * @brief Start the kernel thread.
         * @return Nonzero on success.
         */
        virtual s32 start();

        /** @brief The thread's body; the base class does nothing. */
        virtual void run();
};

/** Thread that shares the CPU with the scheduler's other threads in time slices; vtable D_0014FB60. */
class ResidentTimeSlicedThread : public ResidentThread
{
    public:
        s16 time_slice;

        /** @brief Remove the thread from the scheduler and destroy it. */
        virtual ~ResidentTimeSlicedThread();

        /**
         * @brief Start the thread and add it to the scheduler, stopping it again when the scheduler is full.
         * @return One on success, otherwise zero.
         */
        virtual s32 start_sliced();
};

/** Thread that hands out time slices to up to eight time-sliced threads in turn; vtable D_0014FB80. */
class ResidentThreadScheduler : public ResidentThread
{
    public:
        ResidentTimeSlicedThread* registered[8];
        ResidentTimeSlicedThread* threads[8];
        ResidentTimeSlicedThread* current;

        // TODO: next and alarm_id are volatile because the alarm handler changes them from interrupt context; the
        // target reloads them after every store and test, and nothing else I tried does that.

        volatile s32 next;
        ResidentSemaphore semaphore;
        u8 active;
        u8 unk61[3];
        s32 unk64;
        volatile s32 alarm_id;

        virtual ~ResidentThreadScheduler();

        /**
         * @brief Body of the scheduler's thread: on every wakeup while no round is running, copy the added threads
         * into the round and start it.
         */
        virtual void run();
};

extern "C" s32 resident_thread_create(ResidentThread* thread, s32 priority, s32 stack_size);
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set a time-sliced thread's slice and create it at the normal resident priority.
 * @param thread Thread.
 * @param time_slice Horizontal syncs per slice.
 * @param stack_size Stack size in bytes.
 * @return Nonzero when the thread was created.
 */
s32 resident_sliced_thread_create(ResidentTimeSlicedThread* thread, s16 time_slice, s32 stack_size);

/** Return whether waking the resident thread succeeds. */
s32 resident_thread_wakeup(const void* object);

/** Return whether the resident thread sleep request succeeds. */
s32 resident_thread_sleep(void);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
    /**
     * @brief Start a thread, or stop it (exiting when it is the calling thread).
     * @param object Thread.
     * @param run Nonzero to start it; stored in the sound system's unk351.
     */
    void resident_thread_set_running(void* object, u8 run);

    /**
     * @brief Stop handing out time slices, returning the running thread to the normal priority.
     * @param scheduler Scheduler.
     */
    void resident_scheduler_stop(ResidentThreadScheduler* scheduler);

    /**
     * @brief End the running time slice and give the next thread its slice, from interrupt context.
     * @param scheduler Scheduler.
     */
    void resident_scheduler_next_slice(ResidentThreadScheduler* scheduler);

    /**
     * @brief Entry point of every resident thread: run the thread's body, then delete the thread.
     * @param argument The thread.
     */
    void resident_thread_entry(void* argument);

    /**
     * @brief Create the kernel thread with a new stack; it runs the thread's body once started.
     * @param thread Thread.
     * @param priority Thread priority.
     * @param stack_size Stack size in bytes.
     * @return Nonzero when the thread was created, zero when it already exists or creation failed.
     */
    s32 resident_thread_create(ResidentThread* thread, s32 priority, s32 stack_size);

    /**
     * @brief Wake a thread, with the interrupt-context call when interrupts are disabled.
     * @param thread Thread to wake.
     * @return True on success.
     */
    bool resident_thread_wake(ResidentThread* thread);
}
#endif

#endif
