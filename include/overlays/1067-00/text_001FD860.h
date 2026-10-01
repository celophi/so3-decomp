#ifndef SO3_OVERLAYS_1067_00_TEXT_001FD860_H
#define SO3_OVERLAYS_1067_00_TEXT_001FD860_H

#include "types.h"

/** Partial resource-list link; the complete node extent is unknown. */
typedef struct FieldResourceListNode
{
    u8 unk00[8];
    struct FieldResourceListNode* next;
} FieldResourceListNode;

/** Partial resource entry with size words, keys, a counter and flags. */
typedef struct FieldResourceListEntry
{
    FieldResourceListNode link;
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
    FieldResourceListNode unk14;
} FieldResourceList14;

/** Partial owner containing a word used in packed resource keys. */
typedef struct FieldPackedKeyOwner3AC
{
    u8 unk00[0x3AC];
    u32 unk3ac;
} FieldPackedKeyOwner3AC;

/** Partial receiver supplying three components of a packed resource key. */
typedef struct FieldPackedKeySource
{
    u8 unk00[8];
    FieldPackedKeyOwner3AC* unk08;
    u16* unk0c;
    u8 unk10[4];
    u32 unk14;
} FieldPackedKeySource;

/** Partial receiver containing word flags and an object pointer. */
typedef struct FieldFlaggedPointerA0
{
    u8 unk00[0x70];
    u32 unk70;
    u8 unk74[0xD];
    u8 unk81_0 : 1;
    u8 unk81_rest : 7;
    u8 unk82[0x1E];
    void* unka0;
    s32 unka4;
} FieldFlaggedPointerA0;

/** Partial receiver containing an object pointer, flag and float value. */
typedef struct FieldFloatGateState7C
{
    u8 unk00[0x7C];
    void* unk7c;
    u8 unk80[0xC];
    u8 unk8c_0 : 1;
    u8 unk8c_1_4 : 4;
    u8 unk8c_5 : 1;
    u8 unk8c_6_7 : 2;
    u8 unk8d[3];
    float unk90;
} FieldFloatGateState7C;

/** Partial receiver with a word at offset 0xC4. */
typedef struct FieldAtC4 { u8 pad[0xC4]; u32 value; } FieldAtC4;

/** Partial receiver with a size and its 128-byte rounded form. */
typedef struct FieldAlignedSize { u8 pad[0xAC]; u32 size; u32 rounded; } FieldAlignedSize;

/** Partial receiver containing float and aligned 16-byte copy fields. */
typedef struct FieldCopyState
{
    u8 pad00[0x94]; float src94;
    u8 pad98[4]; float dst9C;
    u8 padA0[0x10]; float srcB0;
    u8 padB4[4]; float dstB8;
    u8 padBC[0xC]; float srcC8;
    u8 padCC[4]; float dstD0;
    u8 padD4[0x1C]; unsigned __int128 srcF0;
    u8 pad100[0x10]; unsigned __int128 dst110;
    u8 pad120[0x20]; unsigned __int128 src140;
    unsigned __int128 dst150;
} FieldCopyState;

/** Partial callback receiver with a target and active word. */
typedef struct FieldCallbackObject FieldCallbackObject;
typedef struct FieldCallbackState { u8 pad[0xA8]; FieldCallbackObject* target; u8 padAC[4]; u32 active; } FieldCallbackState;

/** Linked entry and list owner used for kind lookup. */
typedef struct FieldCbLink { u8 pad[8]; struct FieldCbLink* next; } FieldCbLink;
typedef struct FieldCbEntry { FieldCbLink link; u8 padC[0x62]; u16 kind; } FieldCbEntry;
typedef struct FieldCbOwner { u8 pad[0x10]; FieldCbLink sentinel; } FieldCbOwner;

/** Partial receiver with a bit at offset 0x81. */
typedef struct FieldState81
{
    u8 pad[0x81];
    u8 bit0 : 1;
    u8 other : 7;
} FieldState81;

/** Partial fourteen-byte field assignment target. */
typedef struct FieldAssign14
{
    u8 unk00[4];
    u32 unk04;
    u32 unk08;
    s16 unk0c;
    u8 unk0e;
    u8 unk0f;
    u32 unk10;
} FieldAssign14;

/** Partial transform receiver with two aligned vectors. */
typedef struct FieldTransform
{
    u8 unk00[0x1A0];
    unsigned __int128 unk1a0;
    u8 unk1b0[0x10];
    unsigned __int128 unk1c0;
    u8 unk1d0[0x1D4];
    u32 unk3a4;
    u32 unk3a8;
} FieldTransform;

/** Partial state with two adjacent byte flags. */
typedef struct FieldState3BA
{
    u8 unk00[0x3BA];
    u8 unk3ba;
    u8 unk3bb_0 : 1;
    u8 unk3bb_1_7 : 7;
} FieldState3BA;

/** Partial state containing a three-float vector. */
typedef struct FieldVector180 { u8 unk00[0x180]; float x; float y; float z; } FieldVector180;

/** Partial state with one byte value and one bit flag. */
typedef struct FieldByteState210
{
    u8 unk00[0x210];
    u8 unk210;
    u8 unk211[0x38C];
    u8 unk59d_0_2 : 3;
    u8 unk59d_3 : 1;
    u8 unk59d_4_7 : 4;
} FieldByteState210;

/** Partial receiver layouts defined in the owning source. */
typedef struct FieldSlot FieldSlot;
typedef struct FieldState704 FieldState704;
typedef struct FieldState79C FieldState79C;
typedef struct FieldState794 FieldState794;
typedef struct FieldState570 FieldState570;
typedef struct FieldNested634 FieldNested634;
typedef struct FieldOuter870 FieldOuter870;
typedef struct FieldFlagTarget FieldFlagTarget;
typedef struct FieldItem10 FieldItem10;
typedef struct FieldListAC FieldListAC;
typedef struct FieldStateAD FieldStateAD;
typedef struct FieldState820 FieldState820;
typedef struct FieldState634 FieldState634;
typedef struct FieldState2C FieldState2C;

/** Partial float-motion receivers defined in the owning source. */
typedef struct FieldMotion FieldMotion;
typedef struct FieldMotion2 FieldMotion2;
typedef struct FieldMotion3 FieldMotion3;
typedef struct FieldMotion4 FieldMotion4;
typedef struct FieldScriptCursorU32 FieldScriptCursorU32;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Return the fixed value four.
 * @return Four.
 */
s32 func_001FD950(void);

/**
 * @brief Return the fixed value four.
 * @return Four.
 */
s32 func_001FDA50(void);

/**
 * @brief Test the selected object and update the completion float.
 * @param object Receiver and argument cursor.
 * @param has_index Whether to read an index operand.
 * @return Zero when the selected object succeeds, otherwise one.
 */
s32 func_001FE950(u8* object, s32 has_index);

/**
 * @brief Set field-context bit 5 from the current script word.
 * @param object Receiver containing the current script word pointer.
 * @return Always 1.
 */
s32 func_001FE230(FieldScriptCursorU32* object);

/**
 * @brief Set field-context bit 4 when the current script word has a clear low bit.
 * @param object Receiver containing the current script word pointer.
 * @return Always 1.
 */
s32 func_001FDC90(FieldScriptCursorU32* object);

/**
 * @brief Clear bit 0x40 in the word at offset 0x204.
 * @param object Receiver to update.
 */
void func_001FECE0(u8* object);

/**
 * @brief Clear bit 0x40 in the word at offset 0x204.
 * @param object Receiver to update.
 */
void func_001FED00(u8* object);

/**
 * @brief Copy the byte at offset 0xA8 to offset 0x60.
 * @param object Receiver to update.
 */
void func_001FF110(u8* object);

#ifdef __cplusplus
}
#endif

#endif
