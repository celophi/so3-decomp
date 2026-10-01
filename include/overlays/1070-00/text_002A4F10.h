#ifndef SO3_OVERLAYS_1070_00_TEXT_002A4F10_H
#define SO3_OVERLAYS_1070_00_TEXT_002A4F10_H

#include "overlays/1070-00/text_00284BF0.h"

/** Partial resource list entry with its size, keys and observed flag byte. */
typedef struct FieldResourceListEntry
{
    FieldListNode link;
    u8 unk0c[8];
    u32 unk14;
    u32 unk18;
    u32 unk1c;
    u32 unk20;
    u8 unk24[0x1C];
    s32 unk40;
    u8 unk44[5];
    u8 unk49_0 : 1;
    u8 unk49_1 : 1;
    u8 unk49_2 : 1;
    u8 unk49_3 : 1;
    u8 unk49_4_7 : 4;
} FieldResourceListEntry;

/** Partial resource-list owner with an embedded sentinel. */
typedef struct FieldResourceList14
{
    u8 unk00[0x14];
    FieldListNode unk14;
} FieldResourceList14;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Find the size selected by a resource entry's flag.
 * @param object Resource list to search.
 * @param kind Resource kind to match.
 * @param key Resource key to match.
 * @return The selected size, or zero when no matching entry exists.
 */
u32 func_002B3140(FieldResourceList14* object, u32 kind, u32 key);

/**
 * @brief Count flagged resource entries matching either of two kind and key conditions.
 * @param object Resource list to search.
 * @param first Low-halfword key for kinds 0x43484152 and 0x41545243.
 * @param second Low-halfword key for kind 0x414E494D.
 * @return Number of flagged entries with a matching kind and key.
 */
s32 func_002B2950(FieldResourceList14* object, s32 first, s32 second);

/**
 * @brief Decrement counters for matching resource entries that pass their flag checks.
 * @param object Resource list to update.
 * @param first Low-halfword key for kinds 0x43484152 and 0x41545243.
 * @param second Low-halfword key for kind 0x414E494D.
 */
void func_002B29F0(FieldResourceList14* object, s32 first, s32 second);

/**
 * @brief Increment counters for matching resource entries that pass their flag checks.
 * @param object Resource list to update.
 * @param first Low-halfword key for kinds 0x43484152 and 0x41545243.
 * @param second Low-halfword key for kind 0x414E494D.
 */
void func_002B2AB0(FieldResourceList14* object, s32 first, s32 second);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A51E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A51F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A5200(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A5210(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A5250(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002A7D30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A8450(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A8460(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A8470(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A8480(void* object);

/**
 * @brief Return the fixed value 63.
 * @param object Receiver or first argument; unused.
 * @return Always 63.
 */
s32 func_002A8500(void* object);

/**
 * @brief Return the fixed value 47.
 * @param object Receiver or first argument; unused.
 * @return Always 47.
 */
s32 func_002A85F0(void* object);

/**
 * @brief Return the fixed value 39.
 * @param object Receiver or first argument; unused.
 * @return Always 39.
 */
s32 func_002A86E0(void* object);

/**
 * @brief Return the fixed value 35.
 * @param object Receiver or first argument; unused.
 * @return Always 35.
 */
s32 func_002A87D0(void* object);

/**
 * @brief Return the fixed value 33.
 * @param object Receiver or first argument; unused.
 * @return Always 33.
 */
s32 func_002A88C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B0AB0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002B0AC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B1B10(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B1B20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B1B30(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B1B40(void* object);

/**
 * @brief Return the fixed value 12.
 * @param object Receiver or first argument; unused.
 * @return Always 12.
 */
s32 func_002B3440(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002B3640(void* object);

/**
 * @brief Return the fixed value 14.
 * @param object Receiver or first argument; unused.
 * @return Always 14.
 */
s32 func_002B4520(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B4530(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B4560(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B4570(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B4810(void* object);

#ifdef __cplusplus
}
#endif

#endif
