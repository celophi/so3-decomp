#ifndef SO3_MAIN_STREAM_THREAD_H
#define SO3_MAIN_STREAM_THREAD_H

#include "types.h"
#include "sdk/main/libkernl_00121940.h"
#include "ee.h"
#include "main/semaphore.h"
#include "main/resource_queue.h"
#include "main/thread.h"
#include "main/dma_queue.h"
#include "main/sound_stream.h"

#ifndef __cplusplus
typedef struct ResidentStreamDma ResidentStreamDma;
typedef struct ResidentStreamThread ResidentStreamThread;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Report whether one of the stream thread's two states is set.
 * @param thread Stream thread.
 * @param which One for the first state; any other value selects the second.
 * @return Nonzero when the selected state is nonzero.
 */
s32 resident_stream_thread_is_state_set(struct ResidentStreamThread* thread, s32 which);

/**
 * @brief Take samples out of one of the stream thread's sample rings and convert them to floats.
 * @param thread Stream thread.
 * @param ring Ring index, 0 or 1.
 * @param count Number of samples to take; a multiple of four.
 * @param output Receives the samples.
 * @return One when the samples were taken, or zero when the ring doesn't hold that many yet.
 */
s32 resident_stream_read_samples(struct ResidentStreamThread* thread, s32 ring, s32 count, float* output);

/**
 * @brief Report whether the stream's two channels hold mid and side instead of left and right.
 * @param thread Stream thread.
 * @return The stream header's mid/side flag.
 */
s32 resident_stream_is_mid_side(const struct ResidentStreamThread* thread);

/**
 * @brief Set the receiver flag when the input value is positive.
 * @param object Receiver whose field at offset 0xB0 is set.
 * @param value Input value to check and return.
 * @return The positive input value, or zero.
 */
s32 resident_stream_thread_set_second_state(void* object, const s32* value);

/**
 * @brief Set two receiver flags when the input value is positive.
 * @param object Receiver whose fields at offsets 0xAC and 0x110 are set.
 * @param value Input value to check and return.
 * @return The positive input value, or zero.
 */
s32 resident_stream_thread_set_first_state(void* object, const s32* value);

/**
 * @brief Take samples out of one of the stream DMA transfer's rings and convert them to floats.
 * @param dma Stream DMA transfer.
 * @param ring Ring index, 0 or 1.
 * @param count Number of samples to take; a multiple of four.
 * @param output Receives the samples.
 * @return One when the samples were taken, or zero when the ring doesn't hold that many yet.
 */
s32 resident_stream_dma_read_samples(struct ResidentStreamDma* dma, s32 ring, s32 count, float* output);

struct ResidentStreamDma;



/**
 * @brief Account for one finished 4 KiB block and queue the next VIF1 transfer, or swap buffers once both are full.
 * @param thread Stream thread.
 */
void resident_stream_dma_finish_block(struct ResidentStreamThread* thread);

/**
 * @brief Set the two sample rings of the stream DMA transfer and empty them.
 * @param thread Stream thread.
 * @param first_ring Start of the first ring.
 * @param second_ring Start of the second ring.
 * @param ring_size Size of each ring in bytes.
 */
void resident_stream_set_sample_rings(struct ResidentStreamThread* thread, u32 first_ring, u32 second_ring, u32 ring_size);

/**
 * @brief Get how many times the playing stream has looped.
 * @param thread Stream thread.
 * @return Loop count, or zero when nothing is playing.
 */
s32 resident_stream_get_loop_count(struct ResidentStreamThread* thread);

/**
 * @brief Move one of the stream thread's two states to two when it is one or two.
 * @param thread Stream thread.
 * @param which One for the first state, two for the second.
 * @return One when the state was moved, otherwise zero.
 */
s32 resident_stream_thread_finish_state(struct ResidentStreamThread* thread, s32 which);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
class ResidentStreamThread;

class ResidentStreamDma;

/**
 * Thread owned by the sound stream that moves stream data between the IOP and VU1: it sends blocks to the IOP and
 * fills two output buffers. The sound stream's thread pointer points to one. Vtables D_0014FAE0 and D_0014FAF0
 * (the thread).
 */
class ResidentStreamThread : public ResidentListener, public ResidentThread
{
    public:
        u8* allocation;
        u8 unk18[2];
        // TODO: volatile is my guess; the SIF handler and the DMA completion write it, and resident_stream_thread_receive_pass rereads it
        volatile u8 output_half;
        u8 unk1B;

        // TODO: output_cursor and input_cursor are volatile because the DMA completion (resident_stream_dma_finish_block) moves them from
        // interrupt context; it reads input_cursor before output_cursor, and nothing else I tried keeps that order.

        u8* volatile output_cursor;
        u8* unk20;
        // TODO: volatile is my guess; the SIF handler and the DMA completion write it, and resident_stream_thread_receive_pass rereads it
        u8* volatile unk24;
        s32 unk28;
        // TODO: volatile is my guess; the SIF handler and the DMA completion write it, and resident_stream_thread_receive_pass rereads it
        volatile s32 output_pending[2];
        volatile u32 unk34[2];
        u8* output_buffers[2];
        u8* unk44;
        // TODO: volatile is my guess; the SIF handler and the DMA completion write it, and resident_stream_thread_receive_pass rereads it
        volatile u8 input_ready[2];

        // TODO: unk4A and unk4C are volatile because the send path (resident_stream_thread_send_chunk) also runs from the SIF interrupt;
        // the target rereads both after every use, and nothing else I tried does that.

        volatile u8 unk4A;
        // TODO: volatile is my guess; the SIF handler and the DMA completion write it, and resident_stream_thread_receive_pass rereads it
        volatile u8 input_half;
        u8* volatile unk4C;
        u8* volatile input_cursor;
        s32 unk54[2];
        void* unk5C[2];
        u8* input_buffers[2];
        u8* unk6C;
        u8* unk70;
        s32 unk74;
        u8 unk78[2];
        u8 unk7A;
        u8 unk7B;

        /**
         * Read position in the ring. The ring pointers are shared with interrupt context.
         * TODO: volatile is my guess from that; nothing else rereads them the way resident_stream_thread_append does.
         */
        u8* volatile unk7C;
        u8* volatile unk80;
        u8* volatile unk84;
        u8* volatile unk88;
        u8* volatile unk8C;
        s32 unk90;
        u8 unk94;
        u8 unk95;
        // TODO: volatile is my guess for unk96, unkA8 and unk110 too; resident_stream_thread_receive_pass rereads each after testing it
        volatile s8 unk96;
        s32 unk98;
        void* unk9C;
        s32 unkA0;
        u32 unkA4;
        volatile u32 unkA8;
        volatile s32 first_state;
        volatile s32 second_state;
        u8 unkB4[3];
        u8 unkB7;
        u8 unkB8;
        u8 unkB9;
        u8 unkBA;
        u8 unkBB;
        s8 mid_side;
        u8 unkBD;
        u8 unkBE;
        s32 loop_count;
        u8 unkC4;
        u8 unkC5[3];
        u8* log_cursor;
        u8 unkCC[0x20];

        /**
         * Thread to wake after the next pass of the streaming thread, or zero; other threads set it, then sleep.
         * TODO: volatile is my guess from that; it's the only form I found where ResidentStreamThread::run rereads it.
         */
        volatile s32 waiting_thread;

        u32* unkF0;
        u32* unkF4;
        ResidentSoundStream* stream;
        u8 unkFC[4];
        ResidentStreamDma* dma;
        u8 unk104;
        ResidentSemaphore semaphore;
        volatile s32 unk110;

        /**
         * @brief Allocate the buffers, clear the streaming state, patch the VU1 programs and create the DMA transfer.
         * @param stream Sound stream that owns the thread.
         */
        ResidentStreamThread(ResidentSoundStream* stream);

        /** @brief Free the buffers and stop the thread. */
        virtual ~ResidentStreamThread();

        /** @brief Run the streaming passes on every wakeup, then wake the waiting thread, if any. */
        virtual void run();

        /**
         * @brief Handle a SIF command forwarded to the thread.
         * @param data Command data.
         */
        virtual void notify(void* data);
};

/** VIF1 DMA transfer of the stream thread, with two sample rings it reads back; vtable D_0014FAC0. */
class ResidentStreamDma : public DmaSubmission
{
    public:
        ResidentStreamThread* owner;
        u32 output;
        s8 phase;
        u32 ring_start[2];
        u32 ring_size;
        u32 ring_read[2];
        u32 ring_write[2];

        /**
         * @brief Start with both rings unset.
         * @param owner Stream thread the transfer belongs to.
         */
        ResidentStreamDma(ResidentStreamThread* owner) : owner(owner)
        {
            ring_start[0] = 0;
            ring_start[1] = 0;
        }

        virtual void submit_dma(u32 channel);

        virtual void complete_dma(u32 channel);
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** Clear bytes at 0x78-0x7B and copy the word at 0x84 to offsets 0x7C and 0x80. */
void resident_stream_thread_reset_blocks(void* object);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {

/**
 * @brief Reset the streaming state and send a stream request (command -5) to the IOP.
 * @param stream Streaming thread.
 * @param arg1 Request argument.
 * @param callback Called when the request completes.
 * @param argument Passed to callback.
 * @param entry Resource entry to stream; its words at 0x10 and 0x14 are kept.
 * @param value Kept at unk90.
 * @param arg6 Request argument.
 * @return The request result, or zero while a request is already running.
 */
s32 resident_stream_thread_request_5(ResidentStreamThread* stream, s32 arg1, void* callback, void* argument, u32* entry, s32 value,
                  s32 arg6);

/**
 * @brief Reset the streaming state and send a stream request (command -4) to the IOP.
 * @param stream Streaming thread.
 * @param arg1 Request argument.
 * @param callback Called when the request completes.
 * @param argument Passed to callback.
 * @param entry Resource entry to stream; its words at 0x10 and 0x14 are kept.
 * @param arg6 Request argument.
 * @return The request result, or zero while a request is already running.
 */
s32 resident_stream_thread_request_4(ResidentStreamThread* stream, s32 arg1, void* callback, void* argument, u32* entry, s32 arg6);

/**
 * @brief Reset the block state and send a stream request (command -3) to the IOP; the ring is left alone.
 * @param stream Streaming thread.
 * @param arg1 Request argument.
 * @param callback Called when the request completes.
 * @param argument Passed to callback.
 * @param entry Resource entry to stream; its words at 0x10 and 0x14 are kept.
 * @param arg6 Request argument.
 * @return The request result, or zero while a request is already running.
 */
s32 resident_stream_thread_request_3(ResidentStreamThread* stream, s32 arg1, void* callback, void* argument, u32* entry, s32 arg6);

/**
 * @brief Send command -2 to the IOP.
 * @param stream Streaming thread.
 * @param arg1 Request argument.
 * @param callback Called when the request completes.
 * @param argument Passed to callback.
 * @param arg6 Request argument.
 * @return The request result, or zero while unkB0 is set.
 */
s32 resident_stream_thread_request_2(ResidentStreamThread* stream, s32 arg1, void* callback, void* argument, s32 arg6);

/**
 * @brief Reset the block state and send command -1 to the IOP at full volume, centred.
 * @param stream Streaming thread.
 * @param arg1 Request argument.
 * @param callback Called when the request completes.
 * @param argument Passed to callback.
 * @param value Kept at unk90.
 * @param arg6 Request argument.
 * @param arg10 Request argument.
 * @return The request result, or zero while a request is already running.
 */
s32 resident_stream_thread_request_1(ResidentStreamThread* stream, s32 arg1, void* callback, void* argument, s32 value, s32 arg6,
                  u8 arg10);

/**
 * @brief Append bytes to the ring, first moving unread data back to the start of the ring when the end is too close.
 * @param stream Streaming thread.
 * @param data Bytes to append.
 * @param size Number of bytes in data.
 * @return Number of bytes appended.
 */
s32 resident_stream_thread_append(ResidentStreamThread* stream, const void* data, s32 size);

/**
 * @brief Copy words into the ring half being written, marking the half full and moving to the other half when it
 * fills.
 * @param stream Streaming thread.
 * @param words Words to copy.
 * @param size Number of bytes in words.
 * @return Number of bytes copied, or zero when the ring can't take data.
 */
s32 resident_stream_thread_write_words(ResidentStreamThread* stream, const u32* words, s32 size);

/**
 * @brief Handle a notification from the IOP side of the stream.
 * @param stream Streaming thread.
 * @param event 0 when a receive block arrived, 2 to set unk74, 4 to send the next chunk.
 */
void resident_stream_thread_handle_event(ResidentStreamThread* stream, s32 event);
}
#endif

#endif
