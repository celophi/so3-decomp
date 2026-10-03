#ifndef SO3_OVERLAYS_1070_00_TEXT_00284BF0_H
#define SO3_OVERLAYS_1070_00_TEXT_00284BF0_H

#include "types.h"

/** Partial list node; the leading bytes and full object extent are unknown. */
typedef struct FieldListNode
{
    u8 unk00[8];
    struct FieldListNode* next;
} FieldListNode;

/** Four adjacent floating-point components observed in vector operations. */
typedef struct FieldVector
{
    float x;
    float y;
    float z;
    float w;
} FieldVector;

/** Partial object reached through context field 0xE4; full extent is unknown. */
typedef struct FieldContextE4
{
    u8 unk00[0xB4];
    u8 unkb4[0x8C];
    char unk140[1];
} FieldContextE4;

/** Partial object held in the context-0x38 receiver's indexed slots. */
typedef struct FieldSlotObject
{
    u8 unk00[0xA0];
    s32 unka0;
    float unka4;
    float unka8;
    u8 unkac[0x46];
    s8 unkf2;
    s8 unkf3;
} FieldSlotObject;

/** Partial receiver used by the observed offset-0x78 owners. */
typedef struct FieldReceiver78
{
    s32 unk00;
    u8 unk04[0x130];
    s32 unk134;
    u8 unk138;
} FieldReceiver78;

/** Partial state initialized by the allocation path in func_0028A8E0. */
typedef struct FieldAllocatedState
{
    u8 unk00[0xC];
    s32 unk0c;
    u8 unk10[8];
    u8 unk18;
} FieldAllocatedState;

/** Partial object reached through context field 0x38. */
typedef struct FieldContext38
{
    u8 unk00[0x4C4];
    FieldListNode unk4c4;
    u8 unk4d0[0xC8];
    FieldSlotObject* unk598[8];
    u8 unk5b8[8];
    void* unk5c0;
    void* unk5c4;
} FieldContext38;

/** Partial object reached through context field 0x18. */
typedef struct FieldContext18
{
    u8 unk00[0x3A0];
    void* unk3a0;
} FieldContext18;

/** One of the eight 0x20-byte entries initialized in the context-0x58 object. */
typedef struct FieldContext58Entry
{
    u8 unk00[0x16];
    u8 unk16_0 : 1;
    u8 unk16_1 : 1;
    u8 unk16_2 : 1;
    u8 unk16_3_7 : 5;
    u8 unk17[9];
} FieldContext58Entry;

/** Partial object reached through context field 0x58. */
typedef struct FieldContext58
{
    u8 unk00[0x14];
    FieldListNode unk14;
    u8 unk20[0x90];
    FieldContext58Entry unkb0[8];
    s32 unk1b0;
    s32 unk1b4;
    u8 unk1b8[0x14];
    void* unk1cc;
    void* unk1d0;
    float unk1d4;
    float unk1d8;
    float unk1dc;
    float unk1e0;
    u8 unk1e4[8];
    s8 unk1ec;
} FieldContext58;

/** Common prefix used by the observed halfword flag accessors. */
typedef struct FieldObjectFlags
{
    u8 unk00[0x6C];
    u16 unk6c;
    u16 unk6e;
} FieldObjectFlags;

/** Partial state object allocated by the observed callers. */
typedef struct FieldWordState
{
    u8 unk00[0x2C];
    s32 unk2c;
} FieldWordState;

/** Partial embedded byte state; the surrounding object is unresolved. */
typedef struct FieldByteState
{
    u8 unk00[4];
    u8 unk04;
} FieldByteState;

/** Partial link object with an observed receiver pointer at offset 0x18. */
typedef struct FieldLinkedObject
{
    u8 unk00[0x18];
    void* unk18;
} FieldLinkedObject;

/** Partial object whose byte at 0x49 supplies a flag. */
typedef struct FieldFlaggedObject
{
    u8 unk00[0x49];
    u8 unk49;
} FieldFlaggedObject;

/** Partial owner of the object passed to the flag accessor. */
typedef struct FieldFlaggedObjectRef
{
    u8 unk00[0x1C];
    FieldFlaggedObject* unk1c;
} FieldFlaggedObjectRef;

/** Partial target reached through the large embedded object's stored pointer. */
typedef struct FieldLargeTarget
{
    u8 unk00[0x8098];
    s32 unk8098;
    u8 unk809c[0x10];
    s32 unk80ac;
    s32 unk80b0;
    s32 unk80b4;
    u8 unk80b8[0xC];
    float unk80c4;
    float unk80c8;
    u8 unk80cc[8];
    u8 unk80d4;
} FieldLargeTarget;

/** Partial embedded object used by the connected large-state accessors. */
typedef struct FieldLargeSubobject
{
    u8 unk00[0x15E640];
    FieldLargeTarget* unk15e640;
} FieldLargeSubobject;

/** Partial large state; member relationships come from shared caller receivers. */
typedef struct FieldLargeState
{
    u8 unk00[0xC0];
    FieldLargeSubobject unkc0;
    u8 unk15e704[0x80];
    s16 unk15e784;
    s16 unk15e786;
    u8 unk15e788[4];
    u8 unk15e78c;
    u8 unk15e78d[3];
    void* unk15e790;
} FieldLargeState;

/** Partial owner of the byte-state subobject at offset 0x120. */
typedef struct FieldByteStateOwner
{
    u8 unk00[0x120];
    FieldByteState unk120;
} FieldByteStateOwner;

/** Separate state reached through the observed secondary global receiver. */
typedef struct FieldSecondaryState
{
    u8 unk00[0xF17B];
    u8 unkf17b;
} FieldSecondaryState;

/** Partial receiver reached through context field 0x08 and its 0xDC pointer. */
typedef struct FieldContext08Target
{
    u8 unk00[0x7C];
    void* unk7c;
} FieldContext08Target;

/** Partial object reached through context field 0x08. */
typedef struct FieldContext08
{
    u8 unk00[0xDC];
    FieldContext08Target* unkdc;
} FieldContext08;

/** Partial Field context; the pointed-to object types and full extent are unknown. */
typedef struct FieldContext
{
    u8 unk00[4];
    void* unk04;
    FieldContext08* unk08;
    u8 unk0c[8];
    void* unk14;
    FieldContext18* unk18;
    u8 unk1c[16];
    void* unk2c;
    void* unk30;
    u8 unk34[4];
    FieldContext38* unk38;
    void* unk3c;
    void* unk40;
    u8 unk44[8];
    void* unk4c;
    u8 unk50[4];
    void* unk54;
    FieldContext58* unk58;
    u8 unk5c[0x80];
    u8 unkdc_0 : 1;
    u8 unkdc_1 : 1;
    u8 unkdc_2_7 : 6;
    u8 unkdd;
    u8 unkde_0_2 : 3;
    u8 unkde_3 : 1;
    u8 unkde_4_7 : 4;
    u8 unkdf;
    void* unke0;
    FieldContextE4* unke4;
} FieldContext;

/** Reference to the Field context shared by the observed accessor callers. */
typedef struct FieldContextRef
{
    FieldContext* context;
} FieldContextRef;

/** Partial receiver whose word at 0x78 contains independent flags. */
typedef struct FieldWordFlags
{
    u8 unk00[0x78];
    u32 unk78;
} FieldWordFlags;

/** Partial receiver with a byte flag at offset 0x2F0. */
typedef struct FieldFlag2F0
{
    u8 unk00[0x2F0];
    u8 unk2f0;
} FieldFlag2F0;

/** Partial target with three word fields used by linked value setters. */
typedef struct FieldTargetValues
{
    u8 unk00[0x1FC];
    u32 unk1fc;
    u8 unk200[0x37C];
    u32 unk57c;
    u32 unk580;
} FieldTargetValues;

/** Partial link containing a target pointer at offset 0x7C. */
typedef struct FieldTargetLink
{
    u8 unk00[0x7C];
    FieldTargetValues* unk7c;
} FieldTargetLink;

/** Partial receiver containing a target link and a word value. */
typedef struct FieldValueSource
{
    u8 unk00[0x10];
    FieldTargetLink* unk10;
    u8 unk14[8];
    u32 unk1c;
} FieldValueSource;

/** Partial receiver with a word and a pointer to a source word. */
typedef struct FieldWordSource540
{
    u8 unk00[0x18];
    u32 unk18;
    u8 unk1c[0x524];
    const u32* unk540;
} FieldWordSource540;

/** Partial target with a floating-point field at offset 0x78. */
typedef struct FieldFloatTarget78
{
    u8 unk00[0x78];
    float unk78;
} FieldFloatTarget78;

/** Partial receiver with a target pointer and floating-point value. */
typedef struct FieldFloatSource10
{
    u8 unk00[0x10];
    FieldFloatTarget78* unk10;
    u8 unk14[8];
    float unk1c;
} FieldFloatSource10;

/** Partial word array beginning at offset 0x24. */
typedef struct FieldIndexedWords24
{
    u8 unk00[0x24];
    u32 words[1];
} FieldIndexedWords24;

/** Partial receiver with a word-array pointer at offset 0x10. */
typedef struct FieldIndexedSource10
{
    u8 unk00[0x10];
    FieldIndexedWords24* unk10;
} FieldIndexedSource10;

/** Reference to a receiver with an indexed word array. */
typedef struct FieldIndexedRef
{
    FieldIndexedSource10* source;
} FieldIndexedRef;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Copy the pointed-to word into the receiver and return zero.
 * @param object Receiver to update.
 * @return Always zero.
 */
s32 func_0028F860(FieldWordSource540* object);

/**
 * @brief Copy a floating-point value into the linked target.
 * @param object Receiver containing the target and value.
 * @return Always 1.
 */
s32 func_00292690(const FieldFloatSource10* object);

/**
 * @brief Read an indexed word through the receiver's source pointer.
 * @param object Reference to the source receiver.
 * @param index Word index.
 * @return Selected word.
 */
u32 func_00289CC0(const FieldIndexedRef* object, s32 index);


/**
 * @brief Copy one 128-bit value into another location.
 * @param destination Destination value.
 * @param source Source value.
 */
void func_002880B0(unsigned __int128* destination, const unsigned __int128* source);

/**
 * @brief Set the receiver byte flag at offset 0x2F0.
 * @param object Receiver to update.
 */
void func_0028E440(FieldFlag2F0* object);

/**
 * @brief Copy the receiver's word into the linked target at offset 0x580.
 * @param object Receiver containing the link and word.
 * @return Always 1.
 */
s32 func_00290450(const FieldValueSource* object);

/**
 * @brief Copy the receiver's word into the linked target at offset 0x57C.
 * @param object Receiver containing the link and word.
 * @return Always 1.
 */
s32 func_00290470(const FieldValueSource* object);

/**
 * @brief Copy the receiver's word into the linked target at offset 0x1FC.
 * @param object Receiver containing the link and word.
 * @return Always 1.
 */
s32 func_00291890(const FieldValueSource* object);

/**
 * @brief Test whether a list traversal has reached its sentinel.
 * @param sentinel List sentinel.
 * @param node Current node.
 * @return 1 if node is the sentinel, otherwise 0.
 */
s32 func_00288650(const void* sentinel, const void* node);

/**
 * @brief Get the next node in a circular list traversal.
 * @param node Current node or list sentinel.
 * @return Next node, which may be the list sentinel.
 */
FieldListNode* func_00288660(const FieldListNode* node);

/**
 * @brief Get the referenced Field context.
 * @param ref Reference to the Field context.
 * @return The context pointer.
 */
FieldContext* func_00288640(const FieldContextRef* ref);

/**
 * @brief Return the supplied object pointer.
 * @param object Object or subobject pointer.
 * @return The same pointer.
 */
void* func_00288670(void* object);

/**
 * @brief Read the Field context pointer at offset 0xE4.
 * @param ref Reference to the Field context.
 * @return The stored object pointer.
 */
void* func_00288690(const FieldContextRef* ref);

/**
 * @brief Return the supplied object pointer.
 * @param object Object or subobject pointer.
 * @return The same pointer.
 */
void* func_00289460(void* object);

/**
 * @brief Return the supplied object pointer.
 * @param object Object or subobject pointer.
 * @return The same pointer.
 */
void* func_002899C0(void* object);

/**
 * @brief Read the Field context pointer at offset 0x58.
 * @param ref Reference to the Field context.
 * @return The stored object pointer.
 */
void* func_00289D00(const FieldContextRef* ref);

/**
 * @brief Read the Field context pointer at offset 0x38.
 * @param ref Reference to the Field context.
 * @return The stored object pointer.
 */
void* func_00289D50(const FieldContextRef* ref);

/**
 * @brief Read the Field context pointer at offset 0x30.
 * @param ref Reference to the Field context.
 * @return The stored object pointer.
 */
void* func_0028A810(const FieldContextRef* ref);

/**
 * @brief Read the Field context pointer at offset 0x40.
 * @param ref Reference to the Field context.
 * @return The stored object pointer.
 */
void* func_0028A820(const FieldContextRef* ref);

/**
 * @brief Read the Field context pointer at offset 0x2C.
 * @param ref Reference to the Field context.
 * @return The stored object pointer.
 */
void* func_0028A830(const FieldContextRef* ref);

/**
 * @brief Read the Field context pointer at offset 0x18.
 * @param ref Reference to the Field context.
 * @return The stored object pointer.
 */
void* func_0028A8C0(const FieldContextRef* ref);

/**
 * @brief Read the Field context pointer at offset 0x3C.
 * @param ref Reference to the Field context.
 * @return The stored object pointer.
 */
void* func_0028B1A0(const FieldContextRef* ref);

/**
 * @brief Read the Field context pointer at offset 0x14.
 * @param ref Reference to the Field context.
 * @return The stored object pointer.
 */
void* func_0028B1B0(const FieldContextRef* ref);

/**
 * @brief Read the Field context pointer at offset 0x54.
 * @param ref Reference to the Field context.
 * @return The stored object pointer.
 */
void* func_0028B1D0(const FieldContextRef* ref);

/**
 * @brief Read the Field context pointer at offset 0x04.
 * @param ref Reference to the Field context.
 * @return The stored object pointer.
 */
void* func_0028B1E0(const FieldContextRef* ref);

/**
 * @brief Read the Field context pointer at offset 0x4C.
 * @param ref Reference to the Field context.
 * @return The stored object pointer.
 */
void* func_0028B1F0(const FieldContextRef* ref);

/**
 * @brief Set all four vector components to one value.
 * @param vector Destination vector.
 * @param value Component value.
 * @return The destination vector.
 */
FieldVector* func_00286060(FieldVector* vector, float value);

/**
 * @brief Get the embedded character data at offset 0x140.
 * @param object Object reached through context field 0xE4.
 * @return Start of the character data; its full extent is unknown.
 */
char* func_00288680(FieldContextE4* object);

/**
 * @brief Set the context object pointer at offset 0xE0.
 * @param ref Reference to the Field context.
 * @param object Object pointer to store.
 */
void func_002886B0(const FieldContextRef* ref, void* object);

/**
 * @brief Get an indexed four-component vector.
 * @param vectors Contiguous vector elements.
 * @param index Element index.
 * @return The selected vector.
 */
FieldVector* func_00289830(FieldVector* vectors, s32 index);

/**
 * @brief Mask the halfword flags at offset 0x6C.
 * @param object Object containing the flags.
 * @param mask Bits to retain.
 */
void func_002899A0(FieldObjectFlags* object, u16 mask);

/**
 * @brief Set the halfword value at offset 0x6E.
 * @param object Object containing the halfword.
 * @param value Value whose low 16 bits are stored.
 */
void func_002899B0(FieldObjectFlags* object, s32 value);

/**
 * @brief Clear the object pointer at offset 0x5C4.
 * @param object Object reached through context field 0x38.
 */
void func_00289D40(FieldContext38* object);

/**
 * @brief Set the state word at offset 0x2C.
 * @param object State object.
 * @param value State value to store.
 */
void func_0028A290(FieldWordState* object, s32 value);

/**
 * @brief Read the embedded state byte at offset 0x04.
 * @param object Embedded byte state.
 * @return The stored byte.
 */
u8 func_0028A800(const FieldByteState* object);

/**
 * @brief Read the object pointer at offset 0x3A0.
 * @param object Object reached through context field 0x18.
 * @return The stored object pointer.
 */
void* func_0028A8B0(const FieldContext18* object);

/**
 * @brief Get the embedded receiver at offset 0xB4.
 * @param object Object reached through context field 0xE4.
 * @return The embedded receiver.
 */
void* func_0028A8D0(FieldContextE4* object);

/**
 * @brief Test whether the state word equals the -2 sentinel.
 * @param object Object reached through context field 0x58.
 * @return One when the state is -2, otherwise zero.
 */
s32 func_0028B150(const FieldContext58* object);

/**
 * @brief Set the linked receiver pointer.
 * @param object Link object.
 * @param receiver Receiver pointer to store.
 */
void func_0028B1C0(FieldLinkedObject* object, void* receiver);

/**
 * @brief Read bit zero of the byte at offset 0x49.
 * @param object Object containing the flag byte.
 * @return The flag as zero or one.
 */
s32 func_0028B200(const FieldFlaggedObject* object);

/**
 * @brief Get the referenced object containing the flag byte.
 * @param object Reference owner.
 * @return The stored object pointer.
 */
FieldFlaggedObject* func_0028B210(const FieldFlaggedObjectRef* object);

/**
 * @brief Clear the object pointer at offset 0x5C0.
 * @param object Object reached through context field 0x38.
 */
void func_0028B240(FieldContext38* object);


/**
 * @brief Test whether the state word at offset 0x8098 is zero.
 * @param object Large target object.
 * @return One when the word is zero, otherwise zero.
 */
s32 func_00289470(const FieldLargeTarget* object);

/**
 * @brief Store the result pointer at offset 0x15E790.
 * @param object Large state object.
 * @param value Result pointer to store.
 */
void func_00289660(FieldLargeState* object, void* value);

/**
 * @brief Get the target pointer from the embedded object.
 * @param object Embedded large subobject.
 * @return The stored target pointer.
 */
FieldLargeTarget* func_00289680(const FieldLargeSubobject* object);

/**
 * @brief Get the large subobject at offset 0xC0.
 * @param object Large state object.
 * @return The embedded subobject.
 */
FieldLargeSubobject* func_00289690(FieldLargeState* object);

/**
 * @brief Read the signed halfword at offset 0x15E786.
 * @param object Large state object.
 * @return The stored signed value.
 */
s16 func_002898D0(const FieldLargeState* object);

/**
 * @brief Read the signed halfword at offset 0x15E784.
 * @param object Large state object.
 * @return The stored signed value.
 */
s16 func_002898E0(const FieldLargeState* object);

/**
 * @brief Read the state byte at offset 0x15E78C.
 * @param object Large state object.
 * @return The stored byte.
 */
u8 func_00289CE0(const FieldLargeState* object);

/**
 * @brief Read the secondary state byte at offset 0xF17B.
 * @param object Secondary state object.
 * @return The stored byte.
 */
u8 func_00289CF0(const FieldSecondaryState* object);

/**
 * @brief Set three adjacent state words.
 * @param object Large target object.
 * @param first Value for offset 0x80AC.
 * @param second Value for offset 0x80B0.
 * @param third Value for offset 0x80B4.
 */
void func_0028A100(FieldLargeTarget* object, s32 first, s32 second, s32 third);

/**
 * @brief Set the two floating-point values at offsets 0x80C4 and 0x80C8.
 * @param object Large target object.
 * @param first First value.
 * @param second Second value.
 */
void func_0028A180(FieldLargeTarget* object, float first, float second);

/**
 * @brief Set the state byte at offset 0x80D4.
 * @param object Large target object.
 * @param value Byte to store.
 */
void func_0028A7D0(FieldLargeTarget* object, u8 value);

/**
 * @brief Read the embedded state byte through its accessor.
 * @param object Owner of the byte-state subobject.
 * @return The stored byte.
 */
u8 func_0028A7E0(const FieldByteStateOwner* object);

/**
 * @brief Set the target state byte through the embedded object.
 * @param object Large state object.
 * @param value Byte to store.
 */
void func_0028A790(FieldLargeState* object, u8 value);

/**
 * @brief Set the target floating-point values through the embedded object.
 * @param object Large state object.
 * @param first First value.
 * @param second Second value.
 */
void func_0028A130(FieldLargeState* object, float first, float second);

/**
 * @brief Set three target state words through the embedded object.
 * @param object Large state object.
 * @param first First state word.
 * @param second Second state word.
 * @param third Third state word.
 */
void func_0028A0A0(FieldLargeState* object, s32 first, s32 second, s32 third);


/**
 * @brief Read the receiver word at offset 0x134.
 * @param object Receiver reached through its owner.
 * @return The stored word.
 */
s32 func_00288180(const FieldReceiver78* object);

/**
 * @brief Read the receiver state byte at offset 0x138.
 * @param object Receiver reached through its owner.
 * @return The stored state byte.
 */
u8 func_002886A0(const FieldReceiver78* object);

/**
 * @brief Set the receiver's leading word.
 * @param object Receiver to update.
 * @param value Word to store.
 */
void func_00288820(FieldReceiver78* object, s32 value);

/**
 * @brief Set the state word at offset 0x0C.
 * @param object Allocated state object.
 * @param value Word to store.
 */
void func_0028B070(FieldAllocatedState* object, s32 value);

/**
 * @brief Set the state byte at offset 0x18.
 * @param object Allocated state object.
 * @param value Byte to store.
 */
void func_0028B080(FieldAllocatedState* object, u8 value);

/**
 * @brief Read the slot object's word at offset 0xA0.
 * @param object Object obtained from an indexed slot.
 * @return The stored word.
 */
s32 func_0028B170(const FieldSlotObject* object);

/**
 * @brief Get an object from the eight indexed slots.
 * @param object Object reached through context field 0x38.
 * @param index Slot index, from 0 through 7.
 * @return The stored object pointer, which may be null.
 */
FieldSlotObject* func_0028B180(const FieldContext38* object, u8 index);

/**
 * @brief Replace bit three of the context byte at offset 0xDE.
 * @param context Field context to update.
 * @param value Value whose low bit replaces the flag.
 */
void func_00288710(FieldContext* context, s32 value);

/**
 * @brief Replace bit one of the context byte at offset 0xDC.
 * @param context Field context to update.
 * @param value Value whose low bit replaces the flag.
 */
void func_0028B220(FieldContext* context, s32 value);

/**
 * @brief Set the selected bits in the flag word at offset 0x78.
 * @param object Object containing the flag word.
 * @param mask Bits to set.
 */
void func_00286050(FieldWordFlags* object, u32 mask);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00288030(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_0028B460(void* object);

/**
 * @brief Return the fixed value 9.
 * @param object Receiver or first argument; unused.
 * @return Always 9.
 */
s32 func_0028B4E0(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_0028F9F0(void* object);

#ifdef __cplusplus
}
#endif

#endif
