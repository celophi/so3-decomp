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

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Clear a matching object pointer when the word flag is set.
 * @param object Receiver containing the pointer and flags.
 * @param value Object pointer to compare.
 */
void func_001FF4A0(FieldFlaggedPointerA0* object, void* value);

/**
 * @brief Decrement counters for matching resource entries that pass their flag checks.
 * @param object Resource list to update.
 * @param first Low-halfword key for kinds 0x43484152 and 0x41545243.
 * @param second Low-halfword key for kind 0x414E494D.
 */
void func_002016F0(FieldResourceList14* object, s32 first, s32 second);

/**
 * @brief Increment counters for matching resource entries that pass their flag checks.
 * @param object Resource list to update.
 * @param first Low-halfword key for kinds 0x43484152 and 0x41545243.
 * @param second Low-halfword key for kind 0x414E494D.
 */
void func_002017B0(FieldResourceList14* object, s32 first, s32 second);

/**
 * @brief Find the size selected by a resource entry's flag.
 * @param object Resource list to search.
 * @param kind Resource kind to match.
 * @param key Resource key to match.
 * @return The selected size, or zero when no matching entry exists.
 */
u32 func_00201E20(FieldResourceList14* object, u32 kind, u32 key);

/**
 * @brief Combine the receiver and owner components into a packed resource key.
 * @param object Receiver supplying the key components.
 * @return The combined packed key.
 */
u32 func_00202240(const FieldPackedKeySource* object);

/**
 * @brief Test the float value when the object pointer and flag permit it.
 * @param object Receiver containing the pointer, flag and float value.
 * @return True when the object pointer is nonnull, bit zero is clear and the float value is not positive.
 */
bool func_00204420(const FieldFloatGateState7C* object);

/**
 * @brief Copy the receiver's float and aligned vector fields.
 * @param object Receiver to update.
 */
void func_00209B30(FieldCopyState* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_0020BCF0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_0020BD00(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_0020BDA0(void* object);

/**
 * @brief Test whether the lookup helper returns an object.
 * @param object Receiver to query.
 * @return True when the helper returns a nonnull object.
 */
bool func_0020BDB0(void* object);

/**
 * @brief Run an update helper and finish the attached callback object.
 * @param object Callback receiver.
 */
void func_0020BD60(FieldCallbackState* object);

/**
 * @brief Forward the callback when the receiver is active.
 * @param object Callback receiver.
 * @param context Context passed to the callback.
 * @param enabled Value converted to a boolean for the callback.
 */
void func_0020BDD0(FieldCallbackState* object, void* context, u32 enabled);

/**
 * @brief Clear the attached callback object after notifying it.
 * @param object Callback receiver.
 */
void func_0020BE00(FieldCallbackState* object);

/**
 * @brief Store a word at offset 0xC4.
 * @param object Receiver to update.
 * @param value Word to store.
 */
void func_0020BEF0(FieldAtC4* object, u32 value);

/**
 * @brief Store a size and its 128-byte rounded form.
 * @param object Receiver to update.
 * @param size Size to store and round.
 */
void func_0020BF50(FieldAlignedSize* object, u32 size);

/**
 * @brief Find a list entry with the requested kind.
 * @param object List owner.
 * @param kind Kind to search for.
 * @return One if found, otherwise zero.
 */
s32 func_0020CB20(FieldCbOwner* object, u16 kind);

/**
 * @brief Return the receiver unchanged.
 * @param object Receiver of the call.
 * @return The receiver.
 */
void* func_0020CE30(void* object);

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

/**
 * @brief Run the update helper and clear flag 0x10.
 * @param object Receiver to update.
 */
void func_001FF2C0(u8* object);

/**
 * @brief Run the update helper and conditionally copy the saved vector.
 * @param object Receiver to update.
 * @param value Value passed to the update helper.
 * @param flags Update options.
 */
void func_001FF300(u8* object, void* value, u32 flags);

/**
 * @brief Restore saved vectors and select the pending index.
 * @param object Receiver to update.
 */
void func_001FF400(u8* object);

/**
 * @brief Save the vector and active index.
 * @param object Receiver to update.
 */
void func_001FF460(u8* object);

/**
 * @brief Test the receiver through its state helper, flags, and byte.
 * @param object Receiver to test.
 * @return One when either first test passes; otherwise the stored byte.
 */
s32 func_001FF4D0(u8* object);

/**
 * @brief Store a selected object and update its active flag.
 * @param object Receiver to update.
 * @param value Selected object.
 * @param option Option passed to the selection helper.
 */
void func_001FF530(FieldFlaggedPointerA0* object, void* value, u32 option);

/**
 * @brief Set a float target and its change rate.
 * @param object Receiver to update.
 * @param first Target value.
 * @param second Duration used for the rate.
 */
void func_001FF630(u8* object, float first, float second);

/**
 * @brief Store a word at offset 0x3B4.
 * @param object Receiver to update.
 * @param value Word to store.
 */
void func_00200110(u8* object, u32 value);

/**
 * @brief Test the word at offset 0xC.
 * @param object Receiver to test.
 * @return True when the word is nonzero.
 */
bool func_002006D0(u8* object);

/**
 * @brief Read the word at offset 0x88.
 * @param object Receiver to read.
 * @return The stored word.
 */
u32 func_002006E0(u8* object);

/**
 * @brief Test bit zero of the byte at offset 0x81.
 * @param object Receiver to test.
 * @return True when the bit is set.
 */
bool func_00208C80(const FieldState81* object);

/**
 * @brief Return the fixed value one.
 * @param object Receiver of the call.
 * @return One.
 */
s32 func_00201510(void* object);

/**
 * @brief Return the fixed value one.
 * @param object Receiver of the call.
 * @return One.
 */
s32 func_00201520(void* object);

/**
 * @brief Return the fixed value twelve.
 * @param object Receiver of the call.
 * @return Twelve.
 */
s32 func_00202120(void* object);

/**
 * @brief Copy the known fields from one record to another.
 * @param dest Destination record.
 * @param src Source record.
 * @return The destination record.
 */
FieldAssign14* func_00202990(FieldAssign14* dest, const FieldAssign14* src);

/**
 * @brief Initialize two aligned vectors and clear related fields.
 * @param obj Transform receiver.
 */
void func_00202BF0(FieldTransform* obj);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_00203500(void* object);

/**
 * @brief Set the receiver flag after a successful helper call.
 * @param obj Receiver to update.
 * @return True if the helper succeeds.
 */
bool func_00203930(FieldState3BA* obj);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
s32 func_00203990(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002039B0(void* object);

/**
 * @brief Test whether any of three vector components is nonzero.
 * @param obj Receiver containing the vector.
 * @return True when any component is nonzero.
 */
bool func_002039C0(const FieldVector180* obj);

/**
 * @brief Return the fixed value four.
 * @param object Receiver of the call.
 * @return Four.
 */
s32 func_00203A70(void* object);

/**
 * @brief Return the fixed value five.
 * @param object Receiver of the call.
 * @return Five.
 */
s32 func_00203B10(void* object);

/**
 * @brief Store a byte and set the related bit flag.
 * @param obj Receiver to update.
 * @param value Byte to store.
 */
void func_00204FA0(FieldByteState210* obj, u8 value);

/**
 * @brief Return the fixed value fourteen.
 * @param object Receiver of the call.
 * @return Fourteen.
 */
s32 func_00205700(void* object);

/**
 * @brief Copy a 16-byte value into the receiver.
 * @param object Receiver to update.
 * @param value Value to copy.
 */
void func_00205710(FieldSlot* object, const unsigned __int128* value);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_00205790(void* object);

/**
 * @brief Return the fixed value eleven.
 * @param object Receiver of the call.
 * @return Eleven.
 */
int func_002057A0(void* object);

/**
 * @brief Return the fixed value one.
 * @param object Receiver of the call.
 * @return One.
 */
int func_002057B0(void* object);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_002057C0(void* object);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_002057D0(void* object);

/**
 * @brief Test the word at offset 0x704.
 * @param object Receiver to test.
 * @return True when the word is nonzero.
 */
bool func_002057E0(const FieldState704* object);

/**
 * @brief Find the field at offset 0x79C.
 * @param object Containing receiver.
 * @return The field address.
 */
void* func_002057F0(FieldState79C* object);

/**
 * @brief Read the byte at offset 0x794.
 * @param object Receiver to read.
 * @return The byte value.
 */
u32 func_00205800(const FieldState794* object);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_00205810(void* object);

/**
 * @brief Find the field at offset 0x570.
 * @param object Containing receiver.
 * @return The field address.
 */
void* func_00205850(FieldState570* object);

/**
 * @brief Run the callback when nested state and helper permit it.
 * @param object Receiver to inspect.
 * @param arg First callback argument.
 * @param other Second callback argument.
 */
void func_00206020(FieldOuter870* object, void* arg, void* other);

/**
 * @brief Update target flags for marked list entries.
 * @param object List owner.
 * @param value Selects whether to clear or set the flag.
 */
void func_00206200(FieldListAC* object, bool value);

/**
 * @brief Run the helper and clear a receiver bit when an object is present.
 * @param object Receiver to update.
 */
void func_002067F0(FieldStateAD* object);

/**
 * @brief Run the callback when the state helper succeeds.
 * @param object Receiver to inspect.
 * @param arg First callback argument.
 * @param other Second callback argument.
 */
void func_00207360(FieldState820* object, void* arg, void* other);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_002073C0(void* object);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_002073D0(void* object);

/**
 * @brief Return the second argument.
 * @param object Receiver of the call.
 * @param value Value to return.
 * @return The second argument.
 */
void* func_002073E0(void* object, void* value);

/**
 * @brief Return the second argument.
 * @param object Receiver of the call.
 * @param value Value to return.
 * @return The second argument.
 */
void* func_002073F0(void* object, void* value);

/**
 * @brief Run the receiver cleanup helpers.
 * @param object Receiver to clean up.
 */
void func_00207400(FieldState634* object);

/**
 * @brief Reset two words, store a float value and set a bit.
 * @param object Receiver to update.
 * @param value Integer converted to the float value.
 */
void func_002077B0(FieldState2C* object, int value);

/**
 * @brief Return the fixed value four.
 * @param object Receiver of the call.
 * @return Four.
 */
int func_00207AD0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_00207EE0(void* object);

/**
 * @brief Set a target float and its change rate.
 * @param object Motion receiver.
 * @param target New target value.
 * @param duration Duration used for the rate.
 */
void func_00209780(FieldMotion* object, float target, float duration);

/**
 * @brief Set the first motion target and rate, substituting the fallback sentinel.
 * @param object Motion receiver.
 * @param target New value or sentinel.
 * @param duration Duration used for the rate.
 */
void func_00209BB0(FieldMotion2* object, float target, float duration);

/**
 * @brief Set the second motion target and rate, substituting the fallback sentinel.
 * @param object Motion receiver.
 * @param target New value or sentinel.
 * @param duration Duration used for the rate.
 */
void func_00209C20(FieldMotion3* object, float target, float duration);

/**
 * @brief Set or immediately apply the motion target.
 * @param object Motion receiver.
 * @param target New target value.
 * @param duration Duration used for the rate.
 */
void func_00209C90(FieldMotion4* object, float target, float duration);

#ifdef __cplusplus
}
#endif

#endif
