#ifndef SO3_MAIN_MICROCODE_LOADER_H
#define SO3_MAIN_MICROCODE_LOADER_H

#include "types.h"
#include "main/dma_queue.h"

#ifdef __cplusplus

#define LIB_VU1_PROGRAM_NONE 0xFF

/** Tracks which VU1 microprogram is loaded, with vtable D_178E80 in main data. */
class LibMicrocodeLoader : public DmaSubmission
{
public:
    /** @brief Start with no program and an empty upload packet. */
    LibMicrocodeLoader();

    /**
     * @brief Send the resident microcode upload chain on VIF1.
     * @param channel DMA channel; unused.
     */
    virtual void submit_dma(u32 channel);

    /**
     * @brief Nothing to do once the upload finishes.
     * @param channel DMA channel; unused.
     */
    virtual void complete_dma(u32 channel);

    /** @brief Forget the loaded program and queue the resident microcode upload. */
    void start_upload();

    /**
     * @brief Switch to a microprogram.
     * @param program Program index.
     * @return The program's data when it has to be uploaded, or null when it's already loaded.
     */
    const void* select_program(s32 program);

    /**
     * @brief Return the DMA tag that uploads a microprogram.
     * @param program Program index.
     * @return DMA REF tag.
     */
    u64 get_program_tag(s32 program);

    u8 unk04;
    u8 current_program;
    u8 unk06;
    u8 unk07[0xD];
    u32 unk14[3];
    u32 unk20[3];
    u32 flush;
};

/** Lib's VU1 microcode loader, made by lib_initialize. */
extern LibMicrocodeLoader* g_microcode_loader;

#endif

#endif
