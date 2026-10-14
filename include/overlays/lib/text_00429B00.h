#ifndef SO3_OVERLAYS_LIB_TEXT_00429B00_H
#define SO3_OVERLAYS_LIB_TEXT_00429B00_H

#include "types.h"

typedef struct {
    u8 unk00[4];
    void* unk04;
    u8 unk08[8];
    u32 unk10;
    u8 unk14[4];
    s16 unk18;
    s16 unk1A;
} LibTextSequenceState;

typedef struct {
    u8 unk000[0x60];
    u8 unk60;
    u8 unk61;
    u8 unk62;
    u8 unk63;
    u8 unk64;
    u8 unk65[0x1AB];
    u8 unk210;
    u8 unk211[0x35F];
    unsigned __int128 unk570;
    u8 unk580[0x1D];
    u8 unk59d_0_2 : 3;
    u8 unk59d_3 : 1;
    u8 unk59d_4_7 : 4;
    u8 unk59e[0x166];
    u32 unk704;
    u8 unk708[0x8C];
    u8 unk794;
    u8 unk795[7];
    u8 unk79C[0x84];
    unsigned __int128 unk820;
    u8 unk830[0x0C];
    u8 unk83C;
} LibTextBufferState;

typedef struct {
    u8 unk00[0x0C];
    u8 unk0C;
    u8 unk0D[3];
    u8 unk10[4];
    u32 unk14;
} LibTextValueState;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Multiply a vector by the 4x4 matrix whose rows are already loaded in vf1-vf4.
 *
 * Callers load the rows once with vu0_load_matrix and then transform several
 * vectors. Each result component is the dot product of one row with the vector.
 * @param vector 16-byte aligned source vector.
 * @param result 16-byte aligned destination; may equal vector.
 */
void func_004336E0(const void* vector, void* result);

/**
 * @brief Load a 4x4 matrix into vf1-vf4, then multiply a vector by it as func_004336E0 does.
 * @param matrix 16-byte aligned matrix of four rows.
 * @param vector 16-byte aligned source vector.
 * @param result 16-byte aligned destination.
 */
void func_00433730(const void* matrix, const void* vector, void* result);

/**
 * @brief Allocate an aligned buffer by selecting among temporary allocations.
 * @param size Requested buffer size in bytes.
 * @param alignment Buffer alignment in bytes.
 * @return Selected allocated buffer, or null when allocation fails.
 */
void* func_00433880(u32 size, u32 alignment);

/** @brief Allocate and release temporary blocks before a buffer allocation. */
void func_00433AA0(void);

/**
 * @brief Clear four consecutive words.
 * @param words Pointer to the first word to clear.
 */
void func_0042A460(u32* words);

/**
 * @brief Read the word at offset 0x10 in a sequence state.
 * @param state Sequence state to read.
 * @return The stored word.
 */
u32 func_0042A3A0(const LibTextSequenceState* state);

/**
 * @brief Read the signed halfword at offset 0x18 in a sequence state.
 * @param state Sequence state to read.
 * @return The stored count.
 */
s16 func_0042A3B0(const LibTextSequenceState* state);

/**
 * @brief Read the signed halfword at offset 0x1A in a sequence state.
 * @param state Sequence state to read.
 * @return The stored count.
 */
s16 func_0042A3C0(const LibTextSequenceState* state);

/**
 * @brief Read the buffer pointer from a sequence state.
 * @param state Sequence state to read.
 * @return The stored buffer pointer.
 */
void* func_0042A6C0(const LibTextSequenceState* state);

/**
 * @brief Return the embedded buffer at byte offset 0x79C.
 * @param object Pointer to the containing object.
 * @return Pointer to the embedded buffer.
 */
u8* func_0042AAB0(LibTextBufferState* object);

/**
 * @brief Read the byte at offset 0x794 in a buffer state.
 * @param object Buffer state to read.
 * @return The stored byte.
 */
u8 func_0042AAC0(const LibTextBufferState* object);

/**
 * @brief Store a byte at offset 0x210 in a buffer state.
 * @param object Buffer state to update.
 * @param value Byte to store.
 */
void func_0042ABA0(LibTextBufferState* object, u8 value);

/**
 * @brief Set the bytes at offsets 0x62 and 0x64 in a buffer state.
 * @param object Buffer state to update.
 */
void func_0042ABB0(LibTextBufferState* object);

/**
 * @brief Copy a 16-byte value to offset 0x820 in a buffer state.
 * @param object Buffer state to update.
 * @param value 16-byte aligned source value.
 */
void func_0042ABE0(LibTextBufferState* object, const unsigned __int128* value);

/**
 * @brief Test whether the word at offset 0x704 is nonzero.
 * @param object Buffer state to inspect.
 * @return One if the word is nonzero, otherwise zero.
 */
u32 func_0042AAA0(const LibTextBufferState* object);

/**
 * @brief Default append handler for a channel.
 * @param object Channel object receiving the request.
 * @param value Channel value.
 * @param optional1 Optional second component.
 * @param optional2 Optional third component.
 * @param key Sort value.
 * @return Status.
 */
s32 func_0042A7C0(void* object, const void* value, const void* optional1, const void* optional2, float key);

/**
 * @brief Default set handler for a channel.
 * @param object Channel object receiving the request.
 * @param index Entry index.
 * @param key Sort value.
 * @param value Channel value.
 * @return Status.
 */
s32 func_0042A7D0(void* object, s32 index, float key, const void* value);

/**
 * @brief Default insert handler for a channel.
 * @param object Channel object receiving the request.
 * @param index Entry index.
 * @param key Sort value.
 * @param value Channel value.
 * @return Status.
 */
s32 func_0042A7E0(void* object, s32 index, float key, const void* value);

/**
 * @brief Default channel entry reader.
 * @param object Channel object receiving the request.
 * @param index Entry index.
 * @param key Receives the sort value.
 * @param value Receives the channel value.
 * @return Status.
 */
s32 func_0042A7F0(void* object, s32 index, float* key, void* value);

/**
 * @brief Default channel add handler.
 * @param object Channel object receiving the request.
 * @param value Channel value.
 * @param key Sort value.
 */
void func_0042A800(void* object, const void* value, float key);

/**
 * @brief Perform no work for the default channel handler.
 * @param object Channel object receiving the request.
 */
void func_0042A810(void* object);

/**
 * @brief Return the embedded vector at offset 0x570.
 * @param object Buffer state containing the vector.
 * @return Pointer to the 16-byte embedded vector.
 */
unsigned __int128* func_0042AB20(LibTextBufferState* object);

/**
 * @brief Copy the byte at offset 0x83C to offset 0x60.
 * @param object Buffer state to update.
 */
void func_0042AE70(LibTextBufferState* object);

/**
 * @brief Store the low byte at 0x210 and set bit 3 at 0x59D.
 * @param object Buffer state containing the value and flag bytes.
 * @param value Value whose low byte is stored.
 */
void func_0042AB30(LibTextBufferState* object, u32 value);

/**
 * @brief Return the input pointer unchanged.
 * @param object Pointer to return.
 * @return The input pointer.
 */
void* func_0042E9A0(void* object);

/**
 * @brief Store a word at offset 0x14 and mark the state active at 0x0C.
 * @param state State to update.
 * @param value Word to store.
 */
void func_0042EB30(LibTextValueState* state, u32 value);

#ifdef __cplusplus
}
#endif

#endif
