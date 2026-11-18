#include "include_asm.h"
#include "main/stream_output.h"
#include "main/interrupt_lock.h"
#include "sdk/main/libkernl_00121940.h"

#define DMA_CHANNEL_TO_SPR 9

/** Low byte of the DMAC control register D_CTRL. */
typedef struct DmaControlLow
{
    u8 dma_enable : 1;
    u8 release : 1;
    u8 memory_fifo_drain : 2;
    u8 stall_source : 2;
    u8 stall_drain : 2;
} DmaControlLow;

#define D_CTRL_BITS (*(volatile DmaControlLow*)0x1000E000)

extern "C" {

/** Each DMA channel's queue, by channel number. */
extern ResidentDmaQueue* g_dma_channel_queues[];

/**
 * @brief Report whether the queue's transfer is running, or wait until it finishes.
 * @param queue DMA queue.
 * @param poll Nonzero returns the busy flag straight away; zero waits until the transfer finishes.
 * @return The busy flag when polling, otherwise zero.
 */
u32 resident_dma_queue_wait(ResidentDmaQueue* queue, s32 poll)
{
    if (poll != 0)
    {
        return queue->busy;
    }

    while (queue->busy != 0)
    {
    }

    return 0;
}

/**
 * @brief Finish the queue's current submission, then start the next one unless the queue is empty or paused.
 * @param queue DMA queue.
 */
static inline void dma_queue_advance(ResidentDmaQueue* queue)
{
    if (queue->current)
    {
        queue->current->complete_dma(queue->channel);
        queue->current = 0;
    }

    if (queue->write_index == queue->read_index)
    {
        queue->busy = 0;
    }
    else if (!queue->unk1012)
    {
        queue->current = queue->entries[queue->read_index];
        s32 index = queue->read_index;

        if (++queue->read_index >= 0x400)
        {
            queue->read_index = 0;
        }

        queue->entries[index]->submit_dma(queue->channel);
    }
}

/**
 * @brief DMAC interrupt handler: finish the channel's current submission and start the next one.
 * @param channel DMA channel.
 * @return One.
 */
s32 resident_dma_interrupt_handler(s32 channel)
{
    dma_queue_advance(g_dma_channel_queues[channel]);
    ee_exit_handler();
    return 1;
}

/**
 * @brief Clear the queue's unk1012 pause flag and restart it, if it was paused.
 * @param queue DMA queue.
 */
extern "C" void resident_dma_queue_resume(ResidentDmaQueue* queue)
{
    if (!queue->unk1012)
    {
        return;
    }

    ResidentInterruptLock lock;
    queue->unk1012 = 0;
    queue->current = 0;
    dma_queue_advance(queue);
}

/**
 * @brief Set the queue's unk1012 flag.
 * @param queue DMA queue.
 */
void resident_dma_queue_pause(ResidentDmaQueue* queue)
{
    queue->unk1012 = 1;
}

/**
 * @brief Queue a submission, and start it straight away if the channel is idle.
 * @param submission Transfer to queue.
 * @return False when the queue is full.
 */
bool ResidentDmaQueue::push(DmaSubmission* submission)
{
    ResidentInterruptLock lock;
    s32 next = write_index + 1;

    if (next >= 0x400)
    {
        next = 0;
    }

    if (next == read_index)
    {
        return false;
    }

    entries[write_index] = submission;

    if (++write_index >= 0x400)
    {
        write_index = 0;
    }

    if (!busy)
    {
        busy = 1;
        current = 0;
        dma_queue_advance(this);
    }

    return true;
}

/** @brief Disable the channel and remove its DMAC handler. */
ResidentDmaQueue::~ResidentDmaQueue()
{
    DisableDmac(channel);
    RemoveDmacHandler(channel, handler_id);
}

/**
 * @brief Register the queue as its channel's and install the channel's DMAC handler.
 * @param channel DMA channel number.
 */
ResidentDmaQueue::ResidentDmaQueue(s32 channel)
{
    g_dma_channel_queues[channel] = this;
    this->channel = channel;
    handler_id = AddDmacHandler(channel, resident_dma_interrupt_handler, 0);
    EnableDmac(this->channel);
    busy = 0;
    unk1012 = 0;
    write_index = 0;
    read_index = 0;

    if (channel == DMA_CHANNEL_TO_SPR)
    {
        D_CTRL_BITS.release = 1;
    }
}
}
