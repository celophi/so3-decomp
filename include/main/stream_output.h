#ifndef SO3_MAIN_STREAM_OUTPUT_H
#define SO3_MAIN_STREAM_OUTPUT_H

#include "ee.h"
#include "main/microcode_loader.h"
#include "main/stream_thread.h"

#ifdef __cplusplus
extern "C" {
#endif
extern u8 g_stream_output_tag_0[];
extern u8 g_stream_output_tag_0_address[];
extern u8 g_stream_output_tag_1[];
extern u8 g_stream_output_tag_1_address[];
#ifdef __cplusplus
}

/**
 * @brief Start the VIF1 transfer of the next output block: log its first byte, put the unpack code at the start of
 * both halves, point the two DMA chains at them and queue the transfer.
 * @param thread Stream thread.
 */
static inline void start_output_dma(ResidentStreamThread* thread)
{
    thread->dma->phase = 1;
    *thread->log_cursor++ = *(u8*)((u32)thread->output_cursor | UNCACHED_SEGMENT);
    *(u32*)((u32)thread->output_cursor | UNCACHED_SEGMENT) = 0x6DE80100;
    *(u32*)((u32)(thread->output_cursor + 0x800) | UNCACHED_SEGMENT) = 0x6DE80100;
    *(u16*)((u32)g_stream_output_tag_0 | UNCACHED_SEGMENT) = 0x74;
    *(u32*)((u32)g_stream_output_tag_0_address | UNCACHED_SEGMENT) = (u32)thread->output_cursor;
    *(u16*)((u32)g_stream_output_tag_1 | UNCACHED_SEGMENT) = 0x74;
    *(u32*)((u32)g_stream_output_tag_1_address | UNCACHED_SEGMENT) = (u32)(thread->output_cursor + 0x800);
    thread->dma->output = (u32)thread->input_cursor | UNCACHED_SEGMENT;

    LibMicrocodeLoader* loader = g_microcode_loader;
    loader->unk06 = 1;
    loader->current_program = LIB_VU1_PROGRAM_NONE;

    if (!g_vif1_dma_queue->push(thread->dma))
    {
        g_microcode_loader->unk06 = 0;
    }
}
#endif

#endif
