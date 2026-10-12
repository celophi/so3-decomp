#ifndef SO3_SDK_MAIN_LIBDMA_0012B2C8_H
#define SO3_SDK_MAIN_LIBDMA_0012B2C8_H

#include "types.h"

/** DMA channel control register bit fields. */
typedef struct DmaChannelControl
{
    u32 direction : 1;
    u32 reserved1 : 1;
    u32 mode : 2;
    u32 address_stack_pointer : 2;
    u32 tag_transfer_enable : 1;
    u32 tag_interrupt_enable : 1;
    u32 start : 1;
    u32 reserved9 : 7;
    u32 tag : 16;
} DmaChannelControl;

/** Partial DMA channel register block, beginning at CHCR. */
typedef struct DmaChannel
{
    volatile DmaChannelControl chcr;
} DmaChannel;

/** DMA source-chain tag and its two payload words. */
typedef struct DmaSourceTag
{
    u64 control;
    u64 data;
} __attribute__((aligned(16))) DmaSourceTag;

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Select a DMA channel. @param channel Channel number. @return Register block, or null for an invalid channel. */
DmaChannel* sceDmaGetChan(u32 channel);

/** @brief Start a source-chain DMA transfer. @param channel Channel register block. @param chain Source-chain head. */
void sceDmaSend(DmaChannel* channel, void* chain);

#ifdef __cplusplus
}
#endif

#endif
