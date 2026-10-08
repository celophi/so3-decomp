#ifndef SO3_OVERLAYS_1067_00_TEXT_001ED7E0_H
#define SO3_OVERLAYS_1067_00_TEXT_001ED7E0_H

#include "types.h"
#ifdef __cplusplus
#include "overlays/1067-00/text_001DD3C0.h"
#include "overlays/1067-00/text_001E6C50.h"
#include "main/resident_0010A0E0.h"

class FieldClass152210;

/** Partial common loader prefix observed through byte 0x30. */
class FieldClass150700 : public FieldClass150010, public FieldClass1DD400
{
public:
    /** @brief Initialize the common resource-loader state. */
    FieldClass150700()
    {
        unk2c = 0x80;
        unk24 = 0;
        unk28 = 0x34BC0;
        unk1c = 0;
        unk30_1 = 0;
        unk30_0 = 0;
        func_001F2DE0();
    }
    /** @brief Test whether the request callback is ready. @return True when ready. */
    bool request_ready() const
    {
        return unk30_1;
    }
    /** @brief Destroy the common resource-loader state. */
    virtual ~FieldClass150700();
    /** @brief Handle the loader request. @param request Request value. */
    virtual void func_001E0A50(s32 request);
    /** @brief Query pending-record progress. @return Progress value. */
    virtual s32 func_001E07A0();
    /** @brief Submit record requests or detach the loader. @return One after detaching, otherwise zero. */
    virtual s32 func_001DF640();
    /** @brief Run the loader callback. */
    virtual void func_001F8CB0();
    /** @brief Run the loader callback. */
    virtual void func_001F98E0();
    /** @brief Reset the retained loader records and flags. */
    virtual void func_001F2DE0();
    /** @brief Release each counted record. */
    virtual void func_001F9050();
    /** @brief Mark the pending request ready. @param arg Unused callback argument. */
    virtual void func_001DDB30(void* arg);

    FieldClass152210* unk1c;
    FieldClass1DD400* unk20;
    s32 unk24;
    s32 unk28;
    u8 unk2c;
    u8 unk2d;
    u8 unk2e;
    u8 unk2f;
    u8 unk30_0 : 1;
    u8 unk30_1 : 1;
    u8 unk30_2_7 : 6;
};

/** Lib-heap loader wrapper; its constructor adds only the two vtable stores. */
class FieldClass150750 : public FieldClass150700
{
public:
    /** @brief Initialize the inherited loader. */
    FieldClass150750()
    {
    }
    /** @brief Destroy the inherited loader. */
    virtual ~FieldClass150750();
    /** @brief Allocate through the Lib heap. @param size Allocation size. @return Storage or null. */
    static void* operator new(u32 size);
    /** @brief Release through the Lib heap. @param object Storage to release. */
    static void operator delete(void* object);
};

/** Command node retaining a copied record buffer. */
class FieldClass152C70 : public FieldClass150440
{
public:
    /** @brief Clear the record buffer and count. */
    FieldClass152C70()
    {
        unk18 = 0x1001A;
        unk1c = 0;
        unk20 = 0;
    }
    /** @brief Release the retained record buffer and destroy the node. */
    virtual ~FieldClass152C70();
    /** @brief Apply the retained records. @return One when complete. */
    virtual s32 func_0022D6C0();
    void* unk1c;
    s32 unk20;
};

/** @brief Release the retained record buffer and destroy the command node. */
inline FieldClass152C70::~FieldClass152C70()
{
    if (unk1c)
    {
        func_001134C0(unk1c);
    }
}

/** Command node waiting for the owning actor's state bit. */
class FieldClass152DD0 : public FieldClass150440
{
public:
    /** @brief Set the command kind. */
    FieldClass152DD0()
    {
        unk18 = 0x10014;
    }
    /** @brief Destroy the command node. */
    virtual ~FieldClass152DD0();
    /** @brief Wait for the owning actor's state. @return Zero while waiting, otherwise one. */
    virtual s32 func_0022E170();
};


/** Command interpolating a scalar component of its owning actor. */
class FieldClass152DF0 : public FieldClass150440
{
public:
    /**
     * @brief Initialize the scalar command.
     * @param value Target value.
     * @param word Word passed to the actor callback.
     * @param duration Duration.
     */
    FieldClass152DF0(float value, u32 word, float duration);
    /** @brief Destroy the command node. */
    virtual ~FieldClass152DF0();
    /** @brief Update the owning actor. @return One when complete, otherwise zero. */
    virtual s32 func_0022E1B0();
    float unk1c;
    float unk20;
    u32 unk24;
    float unk28;
    float unk2c;
};


/** Command node requesting removal of its owning actor. */
class FieldClass152E10 : public FieldClass150440
{
public:
    /** @brief Set the command kind. */
    FieldClass152E10()
    {
        unk18 = 0x10012;
    }
    /** @brief Destroy the command node. */
    virtual ~FieldClass152E10();
    /** @brief Remove the owning actor. @return Always one. */
    virtual s32 func_0022E350();
};


/** Command node that sets its owning command-list timer. */
class FieldClass152E30 : public FieldClass150440
{
public:
    /** @brief Set the command kind and timer. @param timer Timer value. */
    FieldClass152E30(float timer)
    {
        unk18 = 0x10011;
        unk1c = timer;
    }
    /** @brief Destroy the command node. */
    virtual ~FieldClass152E30();
    /** @brief Set the owning command-list timer. @return Always one. */
    virtual s32 func_0022E380();
    float unk1c;
};


/** Partial queue object with the native 1507A0 virtual interface. */
class FieldClass1507A0 : public FieldClass150070
{
public:
    /** @brief Clear the queue state word. */
    FieldClass1507A0()
    {
        unk18 = 0;
    }
    /** @brief Allocate through the Lib heap. @param size Required storage. @return Allocated storage or null. */
    static void* operator new(u32 size);
    /** @brief Release through the Lib heap. @param object Storage to release. */
    static void operator delete(void* object);
    /** @brief Destroy the inherited queue state. */
    virtual ~FieldClass1507A0()
    {
    }
    /** @brief Add this object to the resident queue. */
    virtual void func_001DD7B0();
    u8 unk14[4];
    u32 unk18;
};

/** Partial queue object whose callback examines resident entries. */
class FieldClass150650 : public FieldClass1507A0
{
public:
    /** @brief Destroy the queue object. */
    virtual ~FieldClass150650();
    /** @brief Unlink and add this object to the resident queue. */
    virtual void func_001DD7B0();
    /** @brief Process the resident entries. */
    virtual void func_001DF360();
    float unk1c;
};

/** Small callback object storing three byte flags and a word. */
class FieldClass150630 : public FieldClass150070
{
public:
    /** @brief Allocate from the Lib heap. @param size Allocation size. @return Allocated storage or null. */
    static void* operator new(u32 size);
    /** @brief Release through the Lib heap. @param object Storage to release. */
    static void operator delete(void* object);
    /** @brief Destroy the callback object. */
    virtual ~FieldClass150630();
    /** @brief Return the object kind. @return Sixteen. */
    virtual s32 func_001DF3D0();
    /** @brief Unlink and release the object. */
    virtual void func_001DD7B0();
    /** @brief Invoke the packed-field callback and release this object. */
    virtual void func_001DF360();
    u8 unk14[4];
    u8 unk18;
    u8 unk19;
    u8 unk1a;
    s32 unk1c;
};

/** Shape list whose destructor releases the inherited entries. */
class FieldClass1505F0 : public FieldClass1502A0
{
public:
    /** @brief Release every listed shape and the inherited list state. */
    virtual ~FieldClass1505F0();
    /** @brief Release storage through the Lib heap. @param object Storage to release. */
    static void operator delete(void* object);
};
#endif

#include "overlays/1067-00/text_001ED7E0_callbacks.h"

typedef struct FieldCondition16 FieldCondition16;
struct FieldVec4B;
struct FieldClass150590;
struct FieldClass150570;
struct FieldClass150530;
struct LibClass178DD0;
struct FieldClass151510;
struct FieldClass150060;
#ifdef __cplusplus
extern "C" {
#endif

/** @brief Test listed conditional shapes and dispatch their events. @param list Circular shape sentinel. @param actor Query receiver. @param mask Condition selection mask. @return One when an event was dispatched, otherwise zero. */
s32 func_001EF150(struct FieldClass150060* list, struct FieldClass151510* actor, u32 mask);
/** @brief Test listed script shapes and dispatch their events. @param list Circular shape list. @param actor Query receiver. @param kind Shape flag selector. @return Whether an event was dispatched. */
bool func_001EF4A0(struct LibClass178DD0* list, struct FieldClass151510* actor, u8 kind);
#ifdef __cplusplus
}
#endif


#include "overlays/1067-00/field_vector4.h"

/** Partial receiver with three four-float values and a byte flag. */
typedef struct FieldVectorState50
{
    u8 unk00[0x20];
    FieldVector4 unk20;
    FieldVector4 unk30;
    FieldVector4 unk40;
    u8 unk50;
} FieldVectorState50;

/** Partial receiver with a byte flag at offset 0x60. */
typedef struct FieldByteState60
{
    u8 unk00[0x60];
    u8 unk60;
} FieldByteState60;

/** Partial receiver with four floats at offset 0x20. */
typedef struct FieldFloat4At20
{
    u8 unk00[0x20];
    float unk20[4];
} FieldFloat4At20;

/** Partial objects used by field helpers. */
typedef struct FieldValueAt18 { u8 pad[0x18]; u32 value; } FieldValueAt18;
typedef struct FieldFlagsAt78 { u8 pad[0x78]; u32 flags; } FieldFlagsAt78;
typedef struct FieldWordAt210 { u8 pad[0x210]; u32 value; } FieldWordAt210;

/** Opaque partial receiver types defined by the owning source unit. */
typedef struct FieldScriptCursorF32 FieldScriptCursorF32;
typedef struct FieldScriptCursorS8 FieldScriptCursorS8;
typedef struct FieldScriptCursorS32 FieldScriptCursorS32;
typedef struct FieldScriptCursorU32 FieldScriptCursorU32;
typedef struct FieldScriptCursorBytes FieldScriptCursorBytes;
typedef struct FieldActorCommandState FieldActorCommandState;
#ifdef __cplusplus
class FieldClass152F00;
class FieldClass150F90;
#else
typedef struct FieldClass152F00 FieldClass152F00;
typedef struct FieldClass150F90 FieldClass150F90;
#endif

/**
 * @brief Remove shapes associated with the script's current owner word.
 * @param cursor Script cursor whose current word supplies the owner pointer.
 * @return Always one.
 */
#ifdef __cplusplus
extern "C"
#endif
s32 func_001EF6C0(FieldScriptCursorU32* cursor);
typedef struct FieldRecords FieldRecords;
typedef struct FieldScriptVec FieldScriptVec;
typedef struct FieldLateNodes FieldLateNodes;
typedef struct FieldLateFlag30 FieldLateFlag30;
typedef struct FieldLateCommandStream FieldLateCommandStream;
typedef struct FieldLatePointer40 FieldLatePointer40;
typedef struct FieldLateLarge FieldLateLarge;
typedef struct FieldLateRecords FieldLateRecords;
typedef struct FieldLateFloatArgs FieldLateFloatArgs;
typedef struct FieldLateDeleting FieldLateDeleting;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Retain the operand record and its optional trailing flag.
 * @param cursor Current packed operand record.
 * @param count Operand count supplied by the dispatcher.
 * @return Always one.
 */
s32 func_001F1E10(FieldScriptCursorBytes* cursor, u32 count);

/**
 * @brief Create and register the selected resource loader.
 * @param cursor Script key operand; not advanced.
 * @return Always one.
 */
s32 func_001F2B00(FieldScriptCursorU32* cursor);

/**
 * @brief Create a named actor once the resident focus is ready.
 * @param cursor Script cursor supplying the key, scalar settings, mask and name.
 * @return Zero while waiting for the focus, otherwise one.
 */
s32 func_001F8230(FieldScriptCursorU32* cursor);

/**
 * @brief Create a named actor when the resident timer allows it.
 * @param cursor Script cursor supplying the actor key, name and optional flags.
 * @param count Number of script operands.
 * @return One when the actor was queued, zero while waiting.
 */
s32 func_001F83A0(FieldScriptCursorU32* cursor, u32 count);

/**
 * @brief Initialize an actor from script operands and queue it after loading its resources.
 * @param cursor Script cursor supplying actor keys, coordinates, heading and flags.
 * @param actor Actor to initialize.
 * @param count Number of supplied operands.
 * @param previous Previously selected actor; unused.
 * @return One when queued, zero when actor resource loading fails.
 */
s32 func_001F84D0(FieldScriptCursorU32* cursor, FieldClass152F00* actor, u32 count, FieldClass150F90* previous);

/**
 * @brief Create an actor once a previously selected actor is ready.
 * @param cursor Script cursor supplying the actor setup operands.
 * @param count Number of operands supplied.
 * @return Zero while the previous actor is waiting, otherwise one.
 */
s32 func_001F8AE0(FieldScriptCursorU32* cursor, u32 count);

/** @brief Queue an actor command with optional byte and scalar settings. @param cursor Script operands. @param count Operand count. @return Always one. */
s32 func_001F75C0(FieldScriptCursorU32* cursor, u32 count);
/** @brief Reset the actor command queue and attached scalar track. @param cursor Script receiver selecting the actor. @return Always one. */
s32 func_001F7690(FieldScriptCursorU32* cursor);

/**
 * @brief Queue a callback while resident actors have pending commands.
 * @param cursor Script cursor supplying the callback scalar and receiving the wait value.
 * @return Always one.
 */
s32 func_001F7850(FieldScriptCursorU32* cursor);
/** @brief Clear the actor command queue and mark its state flag when required. @param actor Actor command state. */
void func_001F76F0(FieldActorCommandState* actor);

/**
 * @brief Create a rectangular script shape and append it to the script shape list.
 * @param cursor Operand cursor supplying the shape parameters.
 * @return Always one.
 */
s32 func_001EFA20(FieldScriptCursorU32* cursor);

/**
 * @brief Create a conditional cylindrical shape and append it to the script shape list.
 * @param cursor Operand cursor supplying the shape parameters.
 * @return Always one.
 */
s32 func_001EFC80(FieldScriptCursorU32* cursor);

/**
 * @brief Create a cylindrical script shape and append it to the shape list.
 * @param cursor Operand cursor supplying the shape parameters.
 * @return Always one.
 */
s32 func_001EFEC0(FieldScriptCursorU32* cursor);

/**
 * @brief Set context bounds and optionally select a named entry.
 * @param cursor Float operand cursor followed by the optional name.
 * @param count Number of command operands.
 * @return Always one.
 */
s32 func_001F02E0(FieldScriptCursorF32* cursor, u32 count);

/** @brief Queue a command borrowing pairs from the script. @param cursor Script cursor and channel selection. @param count Operand count. @return Always one. */
s32 func_001F0360(FieldScriptCursorU32* cursor, u32 count);

/** @brief Queue a command with a float value and duration. @param cursor Script cursor and channel selection. @return Always one. */
s32 func_001F04D0(FieldScriptCursorU32* cursor);

/** @brief Queue a target and duration command. @param cursor Script operands and channel selection. @return One. */
s32 func_001F0C00(FieldScriptCursorU32* cursor);

/** @brief Wait while the selected command list is pending. @param cursor Channel selection and wait state. @return Zero while waiting, otherwise one. */
s32 func_001F0B80(FieldScriptCursorU32* cursor);

/** @brief Allocate a packed-field callback and append it to the object list. @param cursor Script packed operand. @return One. */
s32 func_001F09C0(FieldScriptCursorU32* cursor);

/** @brief Set the current bound or its transition rate. @param cursor Script operands. @param count Operand count. @return One. */
s32 func_001F0A80(FieldScriptCursorU32* cursor, u32 count);

/** @brief Queue planar movement from the script duration and magnitude. @param cursor Script operands and channel selection. @return One. */
s32 func_001F0D20(FieldScriptCursorU32* cursor);

/** @brief Queue a command that waits for the owning motion. @param cursor Script channel selection. @return One. */
s32 func_001F10B0(FieldScriptCursorU32* cursor);

/** @brief Queue a planar target and duration. @param cursor Script operands and channel selection. @return One. */
s32 func_001F14F0(FieldScriptCursorU32* cursor);

/** @brief Queue a motion target on the selected owner. @param cursor Script operands and channel selection. @return One. */
s32 func_001F1610(FieldScriptCursorU32* cursor);

/** @brief Queue an angular target converted from script degrees. @param cursor Script operands and channel selection. @return One. */
s32 func_001F1730(FieldScriptCursorU32* cursor);

/** @brief Queue rotation from the script duration and target. @param cursor Script operands and channel selection. @return One. */
s32 func_001F1880(FieldScriptCursorU32* cursor);

/** @brief Test the default camera name and save motion state for other names. @param cursor Script wait state. @return Zero for the default name, otherwise one. */
s32 func_001F0E80(FieldScriptCursorU32* cursor);

/** @brief Clear the selected command list and motion track. @param cursor Channel selection. @return One. */
s32 func_001F0F00(FieldScriptCursorU32* cursor);

/** @brief Queue a command waiting to set the selected owner timer. @param cursor Duration and channel selection. @return One. */
s32 func_001F0FC0(FieldScriptCursorU32* cursor);

/** @brief Apply a script flag to the selected resident entries. @param cursor Script flag operand. @return One. */
s32 func_001F20B0(FieldScriptCursorU32* cursor);

/** @brief Queue the selected channel with a script value and flags. @param cursor Script operands and channel selection. @return One. */
s32 func_001F2140(FieldScriptCursorU32* cursor);

/** @brief Apply a script flag to each selected resident entry. @param cursor Script flag operand. @return One. */
s32 func_001F2230(FieldScriptCursorU32* cursor);

/** @brief Queue the resource-key setting on the selected object. @param cursor Script operands and selection. @return One. */
s32 func_001F22C0(FieldScriptCursorU32* cursor);

/** @brief Wait while the selected actor has command-list activity. @param cursor Actor selection and wait state. @return Zero while waiting, otherwise one. */
s32 func_001F7A90(FieldScriptCursorU32* cursor);

/** @brief Queue a wait command on the selected actor. @param cursor Actor selection. @return One. */
s32 func_001F7B80(FieldScriptCursorU32* cursor);

/** @brief Queue scalar interpolation on the selected actor. @param cursor Script operands and actor selection. @return One. */
s32 func_001F7C30(FieldScriptCursorU32* cursor);

/** @brief Queue a motion callback after resident readiness. @param cursor Channel selection. @return One. */
s32 func_001F1410(FieldScriptCursorU32* cursor);

/** @brief Queue a script word on the selected object. @param cursor Script operand and object selection. @return One. */
s32 func_001F2470(FieldScriptCursorU32* cursor);

/** @brief Queue an actor removal request and set its state bit. @param cursor Actor selection. @return One. */
s32 func_001F7D10(FieldScriptCursorU32* cursor);

/** @brief Queue an unsigned script timer on the selected actor. @param cursor Actor selection and timer operand. @return One. */
s32 func_001F7DE0(FieldScriptCursorU32* cursor);

/** @brief Create an actor at script coordinates or a matching resident position. @param cursor Script operands. @return One. */
s32 func_001F7EE0(FieldScriptCursorU32* cursor);

/** @brief Create a named actor when the resident timer allows it. @param cursor Script key and name. @return One when created, otherwise zero. */
s32 func_001F80E0(FieldScriptCursorU32* cursor);

/** @brief Queue a script float on the selected object. @param cursor Script operand and object selection. @return One. */
s32 func_001F2560(FieldScriptCursorU32* cursor);

/** @brief Queue a motion vector and its command flags. @param cursor Script operands and channel selection. @return One. */
s32 func_001F1CD0(FieldScriptCursorU32* cursor);

/** @brief Fill the selected actor resource slots. @param cursor Script keys. @param count Operand count. @return One. */
s32 func_001F2650(FieldScriptCursorU32* cursor, u32 count);

/** @brief Wait for pending releases, then remove requested resource entries. @param cursor Script keys. @param count Operand count. @return Zero while waiting, otherwise one. */
s32 func_001F2840(FieldScriptCursorU32* cursor, u32 count);

/** @brief Copy script words into a command and append it to the selected receiver. @param cursor Script operands and selection. @param word_count Number of words to copy. @return One. */
s32 func_001F7470(FieldScriptCursorU32* cursor, s32 word_count);

/** @brief Select a range mode and update its transition. @param cursor Script operands. @param count Operand count. @return One. */
s32 func_001F06E0(FieldScriptCursorU32* cursor, u32 count);

/**
 * @brief Test the shape condition and its expanded rectangular bounds.
 * @param object Conditional rectangular shape.
 * @param input Position and radius to test.
 * @param mask Selected condition bits.
 * @param direction Direction used by the angle condition.
 * @param tolerance Vertical overlap allowance.
 * @return Whether both tests succeed.
 */
bool func_001EE2A0(struct FieldClass150590* object, const struct FieldVec4B* input, u32 mask, float direction, float tolerance);

/**
 * @brief Test the selected shape flag and its expanded rectangular bounds.
 * @param object Rectangular shape.
 * @param input Position and radius to test.
 * @param kind Flag selector.
 * @param tolerance Vertical overlap allowance.
 * @return Whether the flag and geometry tests succeed.
 */
bool func_001EE630(struct FieldClass150570* object, const struct FieldVec4B* input, u8 kind, float tolerance);

/**
 * @brief Test the selected shape flag, vertical overlap and xyz radius bound.
 * @param object Cylindrical shape.
 * @param input Position and radius to test.
 * @param kind Flag selector.
 * @param tolerance Vertical overlap allowance.
 * @return Whether the flag and geometry tests succeed.
 */
bool func_001EEAE0(struct FieldClass150530* object, const struct FieldVec4B* input, u8 kind, float tolerance);

/**
 * @brief Test a selected mask and angular interval.
 * @param condition Mask selector and angle range.
 * @param mask Selected condition bits.
 * @param position Position used by relative angle conditions.
 * @param center Center used by relative angle conditions.
 * @param direction Direction in radians.
 * @return One when the condition succeeds, otherwise zero.
 */
s32 func_001EEDB0(FieldCondition16* condition, u32 mask, const struct FieldVec4B* position, const struct FieldVec4B* center, float direction);

/**
 * @brief Mark the vector state and copy a 16-byte value into its first vector.
 * @param state Receiver to update.
 * @param input Value to copy.
 */
void func_001EDE60(FieldVectorState50* state, const FieldQword* input);

/**
 * @brief Mark the vector state and copy a 16-byte value into its second vector.
 * @param state Receiver to update.
 * @param input Value to copy.
 */
void func_001EDEC0(FieldVectorState50* state, const FieldQword* input);

/**
 * @brief Mark the vector state and copy a 16-byte value into its third vector.
 * @param state Receiver to update.
 * @param input Value to copy.
 */
void func_001EDF80(FieldVectorState50* state, const FieldQword* input);

/**
 * @brief Copy a 16-byte value into the first vector.
 * @param state Receiver to update.
 * @param input Value to copy.
 */
void func_001EE210(FieldVectorState50* state, const FieldQword* input);

/**
 * @brief Copy a 16-byte value into the first vector.
 * @param state Receiver to update.
 * @param input Value to copy.
 */
void func_001EE220(FieldVectorState50* state, const FieldQword* input);

/**
 * @brief Mark the vector state and set its first four-float value with a final component of one.
 * @param state Receiver to update.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void func_001EDE80(FieldVectorState50* state, float x, float y, float z);

/**
 * @brief Mark the vector state and set its second four-float value.
 * @param state Receiver to update.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 * @param w Fourth component.
 */
void func_001EDEA0(FieldVectorState50* state, float x, float y, float z, float w);

/**
 * @brief Mark the vector state and transform an input into its second value.
 * @param state Receiver to update.
 * @param input Four-float input to transform.
 */
void func_001EDEE0(FieldVectorState50* state, const float* input);

/**
 * @brief Mark the vector state and transform an input into its second value.
 * @param state Receiver to update.
 * @param input Four-float input to transform.
 */
void func_001EDF10(FieldVectorState50* state, const float* input);

/**
 * @brief Mark the vector state and transform a three-float input with a final component of one.
 * @param state Receiver to update.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void func_001EDF40(FieldVectorState50* state, float x, float y, float z);

/**
 * @brief Mark the vector state and set the first three components of its third value.
 * @param state Receiver to update.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void func_001EDFA0(FieldVectorState50* state, float x, float y, float z);

/**
 * @brief Clear the byte flag at offset 0x60.
 * @param state Receiver to update.
 */
void func_001EE150(FieldByteState60* state);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_001EE160(void* object);

/**
 * @brief Return zero for this receiver.
 * @param object Receiver of the call.
 * @return Zero.
 */
s32 func_001EE170(void* object);

/**
 * @brief Test whether a value is negative.
 * @param object Receiver of the call.
 * @param value Value to test.
 * @return True when value is negative, otherwise false.
 */
bool func_001EE180(void* object, float value);

/**
 * @brief Return the address of D_50CD30.
 * @return Address of the data.
 */
void* func_001EE1A0();

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_001EE1B0(void* object);

/**
 * @brief Return zero for this receiver.
 * @param object Receiver of the call.
 * @return Zero.
 */
s32 func_001EE1C0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_001EE1D0(void* object);

/**
 * @brief Set four floats at offset 0x20, using one as the last component.
 * @param state Receiver to update.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void func_001EE230(FieldFloat4At20* state, float x, float y, float z);

/**
 * @brief Return three for this receiver.
 * @param object Receiver of the call.
 * @return Three.
 */
s32 func_001EE260(void* object);

/**
 * @brief Clean up the receiver and add it to the resident queue.
 * @param object Receiver to clean up and queue.
 */
void func_001EE270(void* object);

/**
 * @brief Pass two float operands to the current resident field object.
 * @param cursor Cursor holding the operands.
 * @return One.
 */
s32 func_001F0620(FieldScriptCursorF32* cursor);

/**
 * @brief Reset two parts of the current resident field object.
 * @param unused Callback argument; unused.
 * @return One.
 */
s32 func_001F0E40(void* unused);





/**
 * @brief Copy the current float operand to two receiver objects.
 * @param cursor Operand cursor.
 * @return One.
 */
s32 func_001F2070(FieldScriptCursorF32* cursor);

/**
 * @brief Add the current cursor object to the resident list.
 * @param cursor Cursor used to fetch the object.
 * @return One.
 */
s32 func_001F7B40(void* cursor);



/**
 * @brief Store the current float operand in the receiver.
 * @param cursor Operand cursor.
 * @return One.
 */
s32 func_001F23E0(FieldScriptCursorF32* cursor);

/**
 * @brief Pass the current bit to the resident field target when present.
 * @param cursor Cursor holding the current word.
 * @return One.
 */
s32 func_001F2420(FieldScriptCursorU32* cursor);

/**
 * @brief Reset the records and related state fields.
 * @param state Record owner to reset.
 */
void func_001F2DE0(FieldRecords* state);

/**
 * @brief Return the fixed value one.
 * @param object Receiver of the call.
 * @return One.
 */
s32 func_001F2EE0(void* object);

/**
 * @brief Copy the current script operand to the shared word and field context.
 * @param cursor Current script operand cursor.
 * @param count Operand count supplied by the script dispatcher; unused.
 * @return Always 1.
 */
s32 func_001F2EB0(FieldScriptCursorU32* cursor, u32 count);

/**
 * @brief Pass the signed byte operand to the receiver.
 * @param cursor Operand cursor.
 * @return One.
 */
s32 func_001F2EF0(FieldScriptCursorS8* cursor);

/**
 * @brief Process a sentinel or a sequence of integer operands.
 * @param cursor Operand cursor.
 * @param count Maximum number of operands to process.
 * @return One.
 */
s32 func_001F3120(FieldScriptCursorS32* cursor, u32 count);

/**
 * @brief Store the low byte of the current operand.
 * @param cursor Operand cursor.
 * @return One.
 */
s32 func_001F4840(FieldScriptCursorS32* cursor);

/**
 * @brief Set or clear receiver flags from two operands.
 * @param cursor Operand cursor.
 * @return One.
 */
s32 func_001F49C0(FieldScriptCursorU32* cursor);

/**
 * @brief Set bit 2 of the current field object byte from the script word's low bit.
 * @param cursor Operand cursor.
 * @return Always 1.
 */
s32 func_001F0B40(FieldScriptCursorU32* cursor);

/**
 * @brief Copy three components and flags from the receiver to the cursor.
 * @param cursor Destination cursor.
 * @return One.
 */
s32 func_001F4CA0(FieldScriptVec* cursor);

/**
 * @brief Copy one 16-byte value to two destinations.
 * @param first First destination.
 * @param second Second destination.
 * @param source Value to copy.
 */
void func_001F5580(FieldQword* first, FieldQword* second, const FieldQword* source);

/**
 * @brief Subtract the first three components of one vector from another.
 * @param destination Result vector.
 * @param left Minuend vector.
 * @param right Subtrahend vector.
 */
void func_001F5590(FieldVector4* destination, const FieldVector4* left, const FieldVector4* right);

/**
 * @brief Copy a 16-byte value.
 * @param destination Destination value.
 * @param source Value to copy.
 */
void func_001F55E0(FieldQword* destination, const FieldQword* source);

/**
 * @brief Store a 32-bit value in the receiver.
 * @param object Receiver to update.
 * @param value Value to store.
 */
void func_001F55F0(FieldValueAt18* object, u32 value);

/**
 * @brief Set flag bits in the receiver.
 * @param object Receiver to update.
 * @param flags Bits to set.
 */
void func_001F8A70(FieldFlagsAt78* object, u32 flags);

/**
 * @brief Fill four floats with one value.
 * @param values Destination array.
 * @param value Value for each component.
 * @return The destination array.
 */
float* func_001F8A80(float* values, float value);

/**
 * @brief Copy a receiver word and run the copy helper.
 * @param destination Destination receiver.
 * @param source Source receiver.
 */
void func_001F8C40(FieldWordAt210* destination, const FieldWordAt210* source);

/**
 * @brief Find the subobject at offset 0x1D0.
 * @param object Containing object.
 * @return Subobject address.
 */
void* func_001F8C60(void* object);

/**
 * @brief Find the subobject at offset 0x1E0.
 * @param object Containing object.
 * @return Subobject address.
 */
void* func_001F8C70(void* object);

/**
 * @brief Find the subobject at offset 0x1F0.
 * @param object Containing object.
 * @return Subobject address.
 */
void* func_001F8C80(void* object);

/**
 * @brief Invoke the first virtual method on each record.
 * @param object Record owner.
 */
void func_001F9050(FieldLateNodes* object);

/**
 * @brief Run an initialization helper once and set the guard bit.
 * @param object Receiver containing the guard bit.
 */
void func_001F90D0(FieldLateFlag30* object);

#ifdef __cplusplus
/**
 * @brief Allocate a 128-byte-aligned buffer, retrying after other loaders release storage.
 * @param owner Loader attached to the resource list.
 * @param size Requested buffer size in bytes.
 * @param mode Nonzero for the library allocator, zero for the resident allocator.
 * @return Allocated buffer, or null when allocation or recovery fails.
 */
void* func_001F9A80(class FieldClass150070* owner, u32 size, s32 mode);
#endif

#ifdef __cplusplus
}
#endif

#endif
