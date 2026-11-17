#ifndef SO3_MAIN_DMA_QUEUE_H
#define SO3_MAIN_DMA_QUEUE_H

#include "types.h"
#include "ee.h"
#include "sdk/main/libkernl_00121940.h"

#ifdef __cplusplus
class DmaSubmission;

/**
 * Ring of DMA submissions waiting for one DMA channel, with the DMAC interrupt handler that starts the next one;
 * vtable D_0014FB48.
 */
class ResidentDmaQueue
{
    public:
        DmaSubmission* entries[0x400];
        DmaSubmission* current;

        // TODO: The indices are volatile because the DMAC handler changes them from interrupt context; the target
        // reloads them after every store, and nothing else I tried does that.

        volatile s32 write_index;
        volatile s32 read_index;
        s32 handler_id;
        u8 channel;
        volatile u8 busy;
        u8 unk1012;

        /**
         * @brief Register the queue as its channel's and install the channel's DMAC handler.
         * @param channel DMA channel number.
         */
        ResidentDmaQueue(s32 channel);

        /**
         * @brief Queue a submission, and start it straight away if the channel is idle.
         * @param submission Transfer to queue.
         * @return False when the queue is full.
         */
        bool push(DmaSubmission* submission);

        /** @brief Wait until the running transfer finishes. */
        void wait_idle()
        {
            while (busy)
            {
            }
        }

        /** @brief Forget the current submission and stop the channel's DMAC interrupts. */
        void stop()
        {
            current = 0;
            DisableDmac(channel);
        }

        /** @brief Disable the channel and remove its DMAC handler. */
        virtual ~ResidentDmaQueue();
};
#endif

#ifndef __cplusplus
typedef struct ResidentDmaQueue ResidentDmaQueue;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** Resident VIF1 DMA queue initialized by the Lib runtime. */
extern ResidentDmaQueue* g_vif1_dma_queue;

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/** Interface called by the resident queue when a DMA transfer starts or completes. */
class DmaSubmission
{
public:
    /**
     * @brief Start the queued DMA transfer.
     * @param channel DMA channel number.
     */
    virtual void submit_dma(u32 channel) = 0;

    /**
     * @brief Complete the queued DMA transfer.
     * @param channel DMA channel number.
     */
    virtual void complete_dma(u32 channel) = 0;
};
#endif

#ifndef __cplusplus
typedef struct DmaSubmission DmaSubmission;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Queue a DMA submission and start processing if the channel is idle.
 *
 * This is ResidentDmaQueue::push as the overlays declare it: they treat the result as an int, while the method
 * returns bool.
 * @param queue Resident queue for the DMA channel.
 * @param submission Transfer callbacks to enqueue.
 * @return 1 on success, 0 when the queue is full.
 */
s32 resident_dma_queue_push(ResidentDmaQueue* queue, DmaSubmission* submission);

/**
 * @brief Set the queue's unk1012 flag.
 * @param queue DMA queue.
 */
void resident_dma_queue_pause(ResidentDmaQueue* queue);

/**
 * @brief Report whether the queue's transfer is running, or wait until it finishes.
 * @param queue DMA queue.
 * @param poll Nonzero returns the busy flag straight away; zero waits until the transfer finishes.
 * @return The busy flag when polling, otherwise zero.
 */
u32 resident_dma_queue_wait(ResidentDmaQueue* queue, s32 poll);

#ifdef __cplusplus
}
#endif

#endif
