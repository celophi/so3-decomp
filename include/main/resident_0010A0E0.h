#ifndef SO3_MAIN_RESIDENT_0010A0E0_H
#define SO3_MAIN_RESIDENT_0010A0E0_H

#include "types.h"

/** Partial ring buffer of 0x400 object pointers with write and read indices. */
typedef struct ResidentObjectQueue
{
    u8 unk00[0x1008];
    s32 write;
    s32 read;
    void* entries[0x400];
} ResidentObjectQueue;

struct BootInputRoot9670;

/** Resident descriptor table used by the keyed resource-size lookup. */
struct ResidentObject1B65E4;

/** Opaque receiver for resident request allocation. */
typedef struct ResidentRequest112400 ResidentRequest112400;

/** Opaque resident queue of DMA submissions for a single channel. */
typedef struct ResidentDmaQueue ResidentDmaQueue;

#ifdef __cplusplus
/** Interface called by the resident queue when a DMA transfer starts or completes. */
class DmaSubmission
{
public:
    /** @brief Start the queued DMA transfer. @param channel DMA channel number. */
    virtual void submit_dma(u32 channel) = 0;
    /** @brief Complete the queued DMA transfer. @param channel DMA channel number. */
    virtual void complete_dma(u32 channel) = 0;
};
#else
typedef struct DmaSubmission DmaSubmission;
#endif

#ifdef __cplusplus
extern "C" {
#endif

s32 func_0011CC00(void* object, void* entry, void* descriptor);
void func_0011D060(void* object, void* entry, void* descriptor);

/**
 * @brief Forward the manager's first pointer and the argument to func_00107D90.
 * @param argument Value forwarded as the helper's second argument.
 */
void func_0010DFC0(void* argument);

/** Run the resident helper on the object's pointer when it is non-null. */
void func_0010ECF0(void* object);

/**
 * @brief Queue a DMA submission and start processing if the channel is idle.
 * @param queue Resident queue for the DMA channel.
 * @param submission Transfer callbacks to enqueue.
 * @return 1 on success, 0 when the queue is full.
 */
s32 func_00114100(ResidentDmaQueue* queue, DmaSubmission* submission);

/**
 * @brief Return the resident runtime table owner.
 * @return Opaque table owner.
 */
void* resident_get_runtime_owner(void);

/** @brief Allocate a block from the resident heap. @param heap Heap receiver. @param size Requested byte count. @return Allocated block, or null. */
void* resident_heap_allocate(void* heap, s32 size);
/** @brief Return a block to the resident heap. @param memory Allocated block. */
void resident_heap_release(void* memory);

/** Clear bytes at 0x78-0x7B and copy the word at 0x84 to offsets 0x7C and 0x80. */
void func_0010B730(void* object);

/** Copy the default resident float quad into the receiver's float fields. */
void func_0010DA30(void* object);
/** Store the low byte at offset 0x450, then run the resident helper on the pointer at offset 0. */
void func_0010DA70(void* object, u32 value);

/**
 * @brief Store a request target, float value, and squared distance value.
 * @param request Resident request receiver.
 * @param target Target pointer to store.
 * @param value Float value to store.
 * @param distance Value to square and store.
 */
void func_0010EA70(ResidentRequest112400* request, void* target, float value, float distance);
/** Store the float at receiver offset 0x139C for index. */
void func_0010EA90(void* object, s32 index, float value);
/** Copy four floats to receiver offsets 0x139C, 0x13A0, 0x13A4, and 0x13A8. */
void func_0010EAA0(void* object, const float* values);
/** Append the pointer at object offset zero to the resident manager array. */
void func_0010EF50(const void* object);
/** Run the resident helper on the pointer at offset zero with its final flag set. */
s32 func_0010EFD0(void* object);

/** Return whether the resident double comparison reports left greater than right. */
s32 func_001143E0(double left, double right);
/** Return whether the resident double comparison reports left less than right. */
s32 func_00114400(double left, double right);
/** Return whether the resident double comparison reports the values equal. */
s32 func_00114420(double left, double right);

/** Store a halfword at offset 0x10, then request resident processing with mode 50. */
s32 func_00114560(void* object, s16 value, s32 size);

/**
 * @brief Advance the resident random sequence and return its next word.
 * @return Next unsigned random word.
 */
u32 resident_next_random_word(void);

/**
 * @brief Read the byte size associated with a key in the resident descriptor table.
 * @param object Resident descriptor table owner.
 * @param key Descriptor key.
 * @return Resource size in bytes.
 */
u32 func_0011C8C0(struct ResidentObject1B65E4* object, s32 key);

/**
 * @brief Store a slot input flag and reset its retained state when disabled.
 * @param root Resident input root.
 * @param slot Input slot index.
 * @param flag Flag whose low byte is stored; zero resets the retained state.
 */
void func_0011E030(struct BootInputRoot9670* root, s32 slot, u32 flag);

/**
 * @brief Append an object to the ring buffer unless it is full.
 * @param queue Queue to append to.
 * @param object Object to append; null is accepted and ignored.
 * @return 1 when the object was appended or is null, 0 when the queue is full.
 */
s32 resident_enqueue_object(ResidentObjectQueue* queue, void* object);

/**
 * @brief Allocate a resident request using its selector and packed values.
 * @param receiver Resident request storage.
 * @param arg1 First request value; its low 16 bits are stored.
 * @param arg2 Request selector.
 * @param arg3 Value forwarded to request dispatch.
 * @param arg4 Value stored and packed into the upper byte.
 * @param arg5 Value packed into the next byte.
 * @param arg6 Value packed into the lower 16 bits.
 * @return Request identifier, zero on dispatch failure, one when disabled, or minus one when unavailable.
 */
s32 resident_allocate_request(ResidentRequest112400* receiver, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);

/** @brief Check a resident request key and its active state. @param request Resident request receiver. @param key Request key. @return Nonzero when the request state is active. */
s32 func_00112610(ResidentRequest112400* request, s32 key);

/** Return the word at receiver offset 0x110. */
u32 func_00115640(const void* object);
/** Return the word at receiver offset 0x10C. */
u32 func_00115650(const void* object);
/** Return the word at receiver offset 0x118. */
u32 func_00115660(const void* object);
/** Return the word at receiver offset 0x104. */
u32 func_00115830(const void* object);
/** Sum each of 0x1800 entry values whose resident flag word is nonzero. */
u32 func_001158A0(const void* object);
/** Return and clear the word at receiver offset 0x10. */
u32 func_0011DF00(void* object);
/** Store the word at receiver offset 0x8 and clear its byte at offset 0x2F9. */
void func_0011DF60(void* object, u32 value);
/** Return the word at receiver offset 0x8. */
u32 func_0011DF70(const void* object);
/** Clear the word at receiver offset 0x8 and its byte at offset 0x2F9. */
void func_0011DF80(void* object);
/** Clear the halfwords at receiver offsets 0x268 and 0x26C for index. */
void func_0011DF90(void* object, s32 index);


/** Store the word at receiver offset 0x134. */
void func_001156B0(void* object, u32 value);


/** Store the byte constant at receiver offset 0x1012. */
void func_001140F0(void* object);

void func_0010EE50(void* object);

/**
 * @brief Store a word and pointer at receiver offsets 0x10 and 0x14.
 * @param object Receiver to update.
 * @param value Word stored at offset 0x10.
 * @param pointer Pointer stored at offset 0x14.
 */
void func_00112D70(void* object, u32 value, void* pointer);

void func_00113180(void* object);
void func_00113EA0(void* object);

/**
 * @brief Return the state byte or wait for it to clear when requested.
 * @param object State receiver whose byte is at offset 0x1011.
 * @param wait Nonzero returns the current byte; zero waits until it is clear.
 * @return Current state byte when waiting is disabled, otherwise zero.
 */
u32 func_00113EB0(void* object, s32 wait);
void func_00114450(void* object);

/** Return whether waking the resident thread succeeds. */
s32 func_00114DD0(const void* object);
/** Return whether the resident thread sleep request succeeds. */
s32 func_00114E80(void);
/** Return whether the resident thread starts successfully. */
s32 func_00114EB0(void* object);

/** Store six words at receiver offsets 0x15C through 0x170. */
void func_001152C0(void* object, u32 arg1, u32 arg2, u32 arg3,
                   u32 arg4, u32 arg5, u32 arg6);

/** Clear the receiver's bytes at offsets 0x140 and 0x6C. */
void func_00115420(void* object);

/** Call func_00114E00 with the second argument. */
void func_00118B80(void* object, void* value);

void func_0011C6B0(void* object);
/** Return bit 0 of the word at receiver offset 0xCC. */
s32 func_0011C7C0(const void* object);

#ifdef __cplusplus
}
#endif

#endif
