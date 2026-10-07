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

/** Resident descriptor table used by the keyed resource-size lookup. */
struct ResidentObject1B65E4;

/** Opaque receiver for resident request allocation. */
typedef struct ResidentRequest112400 ResidentRequest112400;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Return the resident runtime table owner.
 * @return Opaque table owner.
 */
void* func_0010D8E0(void);

/** @brief Allocate a block from the resident heap. @param heap Heap receiver. @param size Requested byte count. @return Allocated block, or null. */
void* func_00113710(void* heap, s32 size);
/** @brief Return a block to the resident heap. @param memory Allocated block. */
void func_001134C0(void* memory);

/**
 * @brief Store a request target, float value, and squared distance value.
 * @param request Resident request receiver.
 * @param target Target pointer to store.
 * @param value Float value to store.
 * @param distance Value to square and store.
 */
void func_0010EA70(ResidentRequest112400* request, void* target, float value, float distance);

/**
 * @brief Advance the resident random sequence and return its next word.
 * @return Next unsigned random word.
 */
u32 func_0010CF80(void);

/**
 * @brief Read the byte size associated with a key in the resident descriptor table.
 * @param object Resident descriptor table owner.
 * @param key Descriptor key.
 * @return Resource size in bytes.
 */
u32 func_0011C8C0(struct ResidentObject1B65E4* object, s32 key);

/**
 * @brief Append an object to the ring buffer unless it is full.
 * @param queue Queue to append to.
 * @param object Object to append; null is accepted and ignored.
 * @return 1 when the object was appended or is null, 0 when the queue is full.
 */
s32 func_0011ED90(ResidentObjectQueue* queue, void* object);

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
s32 func_00112400(ResidentRequest112400* receiver, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);

#ifdef __cplusplus
}
#endif

#endif
