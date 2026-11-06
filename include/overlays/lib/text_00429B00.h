#ifndef SO3_OVERLAYS_LIB_TEXT_00429B00_H
#define SO3_OVERLAYS_LIB_TEXT_00429B00_H

#include "types.h"

#ifdef __cplusplus
class LibTransformOwner;
class LibClass173990;
#else
typedef struct LibTransformOwner LibTransformOwner;
typedef struct LibClass173990 LibClass173990;
#endif

typedef struct {
    u8 unk000[0x60];
    u8 unk60;
    u8 unk61;
    u8 unk62;
    u8 unk63;
    u8 unk64;
    u8 unk65[0x1AB];
    u8 unk210;
    u8 unk211[0x34F];

    /** Packed four-float RGBA factor supplied by the object's own state. */
    unsigned __int128 base_color_factor;

    /** Packed four-float RGBA factor applied over the base factor. */
    unsigned __int128 color_modulation;

    /** Component-wise product of the base and modulation factors. */
    unsigned __int128 combined_color_factor;

    u8 unk590[0xD];
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

void func_00434FA0(void* object);

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
 * @brief Recompute the RGBA factor from the stored base and modulation factors.
 * @param object Rendering state whose combined factor is updated.
 */
void lib_update_color_factor(LibTextBufferState* object);

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


/** Store the word at receiver offset 0x24. */
void func_00432710(void* object, u32 value);

/**
 * @brief Free memory through the heap at D_001B6684 when one is set, otherwise through operator delete.
 * @param memory Allocation, or null.
 */
void func_00434FD0(void* memory);

/**
 * @brief Free memory through the heap at D_001B6684 when one is set, otherwise through operator delete.
 * @param memory Allocation, or null.
 */
void func_00435020(void* memory);

/**
 * @brief Free memory through the heap at D_001B6684 when one is set, otherwise through operator delete.
 * @param memory Allocation, or null.
 */
void func_00435070(void* memory);

/**
 * @brief Free memory through the heap at D_001B6684 when one is set, otherwise through operator delete.
 * @param memory Allocation, or null.
 */
void func_004350C0(void* memory);

/**
 * @brief Allocate from the heap at D_001B6684 when one is set, otherwise through operator new.
 * @param size Size in bytes.
 * @param heap Heap selector passed on to operator new.
 * @return The allocation.
 */
void* func_00435110(u32 size, s32 heap);

/**
 * @brief Allocate from the heap at D_001B6684 when one is set, otherwise through operator new.
 * @param size Size in bytes.
 * @param heap Heap selector passed on to operator new.
 * @return The allocation.
 */
void* func_00435150(u32 size, s32 heap);

/**
 * @brief Store unk428.
 * @param emitter Emitter to update.
 * @param value Word to store.
 */
void func_00435190(LibClass173990* emitter, u32 value);

/**
 * @brief Store unk49c bit 2 and the bytes unk492 and unk493.
 * @param emitter Emitter to update.
 * @param flag Low bit goes to unk49c bit 2.
 * @param first Stored in unk492.
 * @param second Stored in unk493.
 */
void func_004351A0(LibClass173990* emitter, u32 flag, u8 first, u8 second);

/**
 * @brief Store unk49c bit 1 and two angles, and cache the squared cosines of their halves.
 * @param emitter Emitter to update.
 * @param flag Low bit goes to unk49c bit 1.
 * @param first Angle stored in unk410.
 * @param second Angle stored in unk414.
 */
void func_004351D0(LibClass173990* emitter, u32 flag, float first, float second);

/**
 * @brief Store unk49b bit 7, unk49c bit 0, unk491 and unk40c.
 * @param emitter Emitter to update.
 * @param first_flag Low bit goes to unk49b bit 7.
 * @param second_flag Low bit goes to unk49c bit 0.
 * @param value Stored in unk491.
 * @param factor Stored in unk40c.
 */
void func_00435270(LibClass173990* emitter, u32 first_flag, u32 second_flag, u8 value, float factor);

/**
 * @brief Store unk49b bit 6 and the floats unk404 and unk408.
 * @param emitter Emitter to update.
 * @param flag Low bit goes to unk49b bit 6.
 * @param first Stored in unk404.
 * @param second Stored in unk408.
 */
void func_004352B0(LibClass173990* emitter, u32 flag, float first, float second);

/** Return the fixed integer value 6. */
s32 func_00434F20(void* object);

/** Return the fixed value 0. */
s32 func_0042EB40(void* object);

#ifdef __cplusplus
}
#endif

/** Entry-table key the shared font (archive resources 8 and 9) is stored under. */
#define LIB_ENTRY_SHARED_FONT 0x25466887

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Free the shared font (archive resources 8 and 9) and remove it from the entry table. */
void lib_release_shared_font(void);

/** @brief Upload the palette image at D_4EC600. */
void lib_upload_default_palette(void);

#ifdef __cplusplus
}
#endif

#endif
