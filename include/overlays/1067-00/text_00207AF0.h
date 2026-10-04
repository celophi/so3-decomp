#ifndef SO3_OVERLAYS_1067_00_TEXT_00207AF0_H
#define SO3_OVERLAYS_1067_00_TEXT_00207AF0_H

#include "types.h"
#include "overlays/1067-00/curve.h"
#include "overlays/1067-00/text_00207580.h"
#ifdef __cplusplus
#include "overlays/1067-00/text_002DBC50.h"
#include "overlays/1067-00/text_001E6C50.h"
#include "overlays/1067-00/text_001ED7E0.h"
#include "overlays/1067-00/text_0020D9A0.h"
#include "overlays/1067-00/text_0022DC70.h"

#endif

typedef struct FieldMotionRange FieldMotionRange;
typedef struct FieldMotionAngle FieldMotionAngle;
typedef struct FieldMotionRotation210 FieldMotionRotation210;
typedef struct FieldMotionF0 FieldMotionF0;
typedef struct FieldMotionC8 FieldMotionC8;
typedef struct FieldShapeListOwner20 FieldShapeListOwner20;
struct FieldClass154D20;
struct FieldClass1515D0;
struct FieldVec4B;
struct FieldClass151640;
struct FieldShapeOwner18;
struct FieldShapeData10;
struct FieldClass1515B0;
struct FieldClass151570;
struct FieldClass151620;
struct LibClass178A90;
struct LibClass178220;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Create specialized nodes for descriptors and mark their associated records.
 * @param object Receiver supplying shape data and the destination list.
 * @param shape First descriptor in the terminated array.
 */
void func_0020D810(struct FieldClass151640* object, struct FieldShapeOwner18* shape);

/**
 * @brief Test the attached shape and its listed entries against two vectors.
 * @param object Shape storage and list owner.
 * @param query Two contiguous query vectors.
 * @return One when a predicate succeeds, otherwise zero.
 */
s32 func_0020D1A0(struct FieldClass154D20* object, struct FieldVec4B* query);

/**
 * @brief Test the attached shape and its listed entries against another resource.
 * @param object Shape storage and list owner.
 * @param other Resource storage supplying the other shape descriptors.
 * @return One when a predicate succeeds, otherwise zero.
 */
s32 func_0020D330(struct FieldClass154D20* object, struct FieldClass1515D0* other);

/**
 * @brief Test the shape entries with a temporary borrowed attribute resource.
 * @param object Shape list owner.
 * @param query Input passed to the shape predicate.
 * @return One when a shape passes the predicate, otherwise zero.
 */
s32 func_0020D060(FieldShapeListOwner20* object, void* query);

/**
 * @brief Allocate a transform attachment and append it to the receiver's list.
 * @param object Receiver containing the attachment list.
 * @param shape Shape descriptor supplying the transform receiver.
 */
void func_0020D4C0(struct FieldClass151640* object, struct FieldShapeOwner18* shape);

/** @brief Copy the shape entry name and look up its transform. @param entry Entry to update. @param name Seventeen name bytes. @return Located transform, or null. */
struct LibClass178A90* func_0020CA10(struct FieldClass151620* entry, const char* name);

/** @brief Append attachments for descriptors with animation channels. @param object Attachment list owner. @param manager Animation manager. @param shape First descriptor in the terminated array. @return Last attachment created, or null. */
struct FieldClass151570* func_0020D5E0(struct FieldClass151640* object, struct LibClass178220* manager, struct FieldShapeOwner18* shape);

/**
 * @brief Test a specialized node against a shape descriptor.
 * @param node Node supplying the shape resource and record index.
 * @param other Other descriptor to test.
 * @return Predicate status.
 */
s32 func_0020C230(struct FieldClass1515B0* node, struct FieldShapeOwner18* other);

/**
 * @brief Find a specialized node passing the shape test and its vertical offset.
 * @param object Shape list and resource owner.
 * @param other Other descriptor to test.
 * @param data Resource supplying the other descriptor's records.
 * @param height Receives the transformed record's vertical offset.
 * @return Matching specialized node, or null.
 */
struct FieldClass1515B0* func_0020CB70(struct FieldClass151640* object,
    struct FieldShapeOwner18* other, struct FieldShapeData10* data, float* height);

/** Shape record currently selected by the attribute predicate. */
extern struct FieldShapeRecord20* D_001B656C;
extern struct FieldShapeRecord20* D_001B6570;

/**
 * @brief Copy the receiver's float and aligned vector fields.
 * @param object Receiver to update.
 */
void func_00209B30(FieldCopyState* object);

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
 * @brief Test bit zero of the byte at offset 0x81.
 * @param object Receiver to test.
 * @return True when the bit is set.
 */
bool func_00208C80(const FieldState81* object);

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
void func_00209780(FieldMotionF0* object, float target, float duration);

/**
 * @brief Set a range target and its change rate.
 *
 * A zero target is replaced by the xyz distance from the receiver's position
 * to the vector at offset 0x260 of the field context's object at offset 0x14.
 * A zero duration copies the target to the start; otherwise the step is the
 * start-to-target change per unit of duration and flag 0x100 is set.
 * @param object Range receiver.
 * @param target New target value, or zero to measure it.
 * @param duration Duration used for the rate, or zero for an immediate change.
 */
void func_002098C0(FieldMotionRange* object, float target, float duration);

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

/** @brief Set an angular target and its change rate. @param object Motion receiver. @param target Target angle. @param duration Transition duration. */
void func_00209CF0(FieldMotionAngle* object, float target, float duration);

/** @brief Begin a rotation transition using the receiver's vectors and matrices. @param object Rotation state. @param angle Target angle. @param duration Transition duration. */
void func_0020A600(FieldMotionRotation210* object, float angle, float duration);

/**
 * @brief Set or immediately apply the motion target.
 * @param object Motion receiver.
 * @param target New target value.
 * @param duration Duration used for the rate.
 */
void func_00209C90(FieldMotionC8* object, float target, float duration);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
struct FieldState544;

/** Partial motion state supplying the target and rate fields. */
struct FieldMotionF0
{
    FieldState544* source;
    u8 pad04[0x6C];
    u32 flags;
    u8 pad74[0x1C];
    struct FieldObject1573D0* unk90;
    u8 pad94[0x1C];
    float unkb0;
    u8 padb4[0x2C];
    float start;
    float target;
    float duration;
    float step;
};

/** Partial range motion state with an aligned position and target fields. */
struct FieldMotionRange
{
    u8 pad00[0x10];
    FieldVec4A position;
    u8 pad20[0x50];
    u32 flags;
    u8 pad74[0x114];
    float start;
    float target;
    float duration;
    float step;
};

/** Partial motion state containing a target and change rate. */
struct FieldMotionC8
{
    u8 pad00[0x70];
    u32 flags;
    u8 pad74[0x3C];
    float current;
    float previous;
    u8 padB8[4];
    float duration;
    float change;
    float target;
};

/** Partial receiver containing the first angular transition. */
struct FieldMotionAngle
{
    u8 unk00[0x70];
    u32 flags;
    u8 unk74[0x20];
    float current;
    float previous;
    u8 unk9c[4];
    float duration;
    u8 unka4[4];
    float change;
    float target;
};

/** Partial motion state used by the rotation command. */
struct FieldMotionRotation210
{
    u8 unk00[0x10];
    FieldVec4A unk10;
    u8 unk20[0x10];
    FieldVec4A unk30;
    u8 unk40[0x30];
    u32 flags;
    u8 unk74[0x7C];
    FieldMatrix44 unkf0;
    u8 unk130[0x14];
    float unk144;
    u8 unk148[0x18];
    FieldVec4A unk160;
    FieldVec4A unk170;
    u32 unk180;
    float unk184;
    u8 unk188[0x48];
    FieldMatrix44 unk1d0;
};

/** Command node storing a motion target and duration. */
class FieldClass1513C0 : public FieldClass150440
{
public:
    /** @brief Set the command kind and operands. @param duration Duration. @param target Motion target. */
    FieldClass1513C0(float duration, float target)
    {
        unk18 = 0x3004D;
        unk1c = duration;
        unk20 = target;
    }
    /** @brief Destroy the command node. */
    virtual ~FieldClass1513C0();
    /** @brief Begin the queued motion. @return Always one. */
    virtual s32 func_00207F30();
    float unk1c;
    float unk20;
};

/** Command node storing a motion target and duration. */
class FieldClass1513A0 : public FieldClass150440
{
public:
    /** @brief Set the command kind and operands. @param duration Duration. @param target Motion target. */
    FieldClass1513A0(float duration, float target)
    {
        unk18 = 0x3004E;
        unk1c = duration;
        unk20 = target;
    }
    /** @brief Destroy the command node. */
    virtual ~FieldClass1513A0();
    /** @brief Begin the queued motion. @return Always one. */
    virtual s32 func_00207EF0();
    float unk1c;
    float unk20;
};

/** Command node storing a motion target and duration. */
class FieldClass151380 : public FieldClass150440
{
public:
    /** @brief Set the command kind and operands. @param duration Duration. @param target Motion target. */
    FieldClass151380(float duration, float target)
    {
        unk18 = 0x3004F;
        unk1c = duration;
        unk20 = target;
    }
    /** @brief Destroy the command node. */
    virtual ~FieldClass151380();
    /** @brief Begin the queued motion. @return Always one. */
    virtual s32 func_00207E90();
    float unk1c;
    float unk20;
};

/** Command node storing a motion target and duration. */
class FieldClass151360 : public FieldClass150440
{
public:
    /** @brief Set the command kind and operands. @param duration Duration. @param target Motion target. */
    FieldClass151360(float duration, float target)
    {
        unk18 = 0x30050;
        unk1c = duration;
        unk20 = target;
    }
    /** @brief Destroy the command node. */
    virtual ~FieldClass151360();
    /** @brief Begin the queued motion. @return Always one. */
    virtual s32 func_00207E50();
    float unk1c;
    float unk20;
};

/** Command list retaining a pointer to its owning receiver. */
class FieldClass151490 : public FieldClass152FA0
{
public:
    /** @brief Destroy the command list. */
    virtual ~FieldClass151490();
    void* unk7c;
};

/** Command node that sets the owner timer after the resident state becomes ready. */
class FieldClass1513E0 : public FieldClass150440
{
public:
    /** @brief Set the command kind and duration. @param duration Timer value. */
    FieldClass1513E0(u32 duration)
    {
        unk18 = 0x30076;
        unk1c = duration;
    }
    /** @brief Destroy the command and its inherited node. */
    virtual ~FieldClass1513E0();
    /** @brief Wait for readiness, then set the list timer. @return One when ready, otherwise zero. */
    virtual s32 func_00207F70();
    u32 unk1c;
};

/** Command node that invokes its motion receiver after resident readiness. */
class FieldClass151400 : public FieldClass150440
{
public:
    /** @brief Set the command kind. */
    FieldClass151400()
    {
        unk18 = 0x30078;
    }
    /** @brief Destroy the command and its inherited node. */
    virtual ~FieldClass151400();
    /** @brief Wait for readiness and invoke the owner motion callback. @return One when ready, otherwise zero. */
    virtual s32 func_00207FE0();
};

/** Command node that waits for its owning motion receiver. */
class FieldClass151340 : public FieldClass150440
{
public:
    /** @brief Set the command kind. */
    FieldClass151340()
    {
        unk18 = 0x30052;
    }
    /** @brief Destroy the command node. */
    virtual ~FieldClass151340();
    /** @brief Wait for the owner's motion state. @return Zero while active, otherwise one. */
    virtual s32 func_00207DF0();
};

/** Command node storing a planar magnitude and duration. */
class FieldClass151320 : public FieldClass150440
{
public:
    /** @brief Initialize the command kind and operands. @param duration Duration. @param magnitude Movement magnitude. */
    FieldClass151320(float duration, float magnitude)
    {
        unk18 = 0x3007E;
        unk1c = duration;
        unk20 = magnitude;
    }
    /** @brief Destroy the command node. */
    virtual ~FieldClass151320();
    /** @brief Apply a queued planar movement at the current angle. @return One. */
    virtual s32 func_00207D40();
    float unk1c;
    float unk20;
};

class FieldClass15B900;

/** Partial motion interface whose virtual pointer follows the receiver's data. */
class FieldClass151460
{
public:
    u8 unk00[4];
    FieldClass151490* unk04;
    FieldClass15B900* unk08;
    u8 unk0c[0x75];
    u8 unk81_0 : 1;
    u8 unk81_1_7 : 7;
    u8 unk82[2];
    virtual ~FieldClass151460();
    virtual void func_00208E60();
    virtual void func_00209160(void* source, u32 flags);
    virtual void func_00208AB0();
    virtual void func_00208C30();
    virtual bool func_00208C80() const;
    virtual void func_00207EE0(float target, float duration);
};

/** Command node retaining a second buffer and two float operands. */
class FieldClass151420 : public FieldClass152C70
{
public:
    /** @brief Set the command kind and clear the second buffer. */
    FieldClass151420()
    {
        unk18 = 0x3004C;
        unk24 = 0;
    }
    /** @brief Destroy the command node and its inherited record buffer. */
    virtual ~FieldClass151420();
    /** @brief Apply the retained records and second buffer. @return One when complete. */
    virtual s32 func_0022D6C0();
    void* unk24;
    float unk28;
    float unk2c;
    s32 unk30;
};

/** Command node storing a target and duration. */
class FieldClass151300 : public FieldClass150440
{
public:
    /** @brief Initialize the command kind and operands. @param duration Duration. @param target Target value. */
    FieldClass151300(float duration, float target)
    {
        unk18 = 0x3007F;
        unk1c = duration;
        unk20 = target;
    }
    /** @brief Destroy the command node. */
    virtual ~FieldClass151300();
    /** @brief Set or apply the target and complete the command. @return One. */
    virtual s32 func_00207D00();
    float unk1c;
    float unk20;
};

struct FieldFloatPair8;

/** Command node with a count and a borrowed array of float pairs. */
class FieldClass1512C0 : public FieldClass150440
{
public:
    /** @brief Set the command kind and clear the borrowed array. */
    FieldClass1512C0()
    {
        unk18 = 0x3009C;
        unk28 = 0;
    }
    /** @brief Destroy the command node. */
    virtual ~FieldClass1512C0();
    /** @brief Apply the queued curve command. @return One when complete. */
    virtual s32 func_00207B90();
    s32 unk1c;
    float unk20;
    float unk24;
    FieldFloatPair8* unk28;
};

/** Command node storing a float value and duration. */
class FieldClass1512E0 : public FieldClass150440
{
public:
    /** @brief Set the command kind and float operands. @param first First operand. @param second Second operand. */
    FieldClass1512E0(float first, float second)
    {
        unk18 = 0x300C1;
        unk1c = first;
        unk20 = second;
    }
    /** @brief Destroy the command node. */
    virtual ~FieldClass1512E0();
    /** @brief Apply the queued float command. @return One when complete. */
    virtual s32 func_00207CC0();
    float unk1c;
    float unk20;
};

class FieldClass151570;

/** Partial transform receiver with a parent transform link. */
struct FieldTransformParentLink20C
{
    u8 unk00[0x208];
    LibClass178A90* unk208;
};

class FieldClass151620;

/** Transform attachment with two matrices and an optional owner. */
class FieldClass151570 : public FieldClass150070
{
public:
    /** @brief Initialize an unattached object and its identity matrix. */
    FieldClass151570()
    {
        unk14 = 0;
        unk70.set_identity();
        unk20 = 0;
    }
    /** @brief Detach the optional owner, then destroy the inherited node. */
    virtual ~FieldClass151570();
    /** @brief Detach this node and enqueue it for deferred removal. */
    virtual void func_001DD7B0();
    /** @brief Update both matrices from the attached transform. */
    virtual void func_001DF360();

    LibClass178A90* unk14;
    LibClass178A90* unk18;
    FieldShapeOwner18* unk1c;
    FieldClass151620* unk20;
    u8 unk24[0xC];
    LibMatrix44Value unk30;
    LibMatrix44Value unk70;
};

/** A0-byte shape entry identified by MAIN vtable151620 and caller1FCD60. */
class FieldClass151620 : public FieldClass150070
{
public:
    /** @brief Allocate through the Lib heap. @param size Required storage. @return Allocated storage or null. */
    static void* operator new(u32 size);
    /** @brief Release through the Lib heap. @param object Storage to release. */
    static void operator delete(void* object);
    /** @brief Detach the optional attachment and destroy the inherited list node. */
    virtual ~FieldClass151620();
    u8 unk14[0xC];
    FieldShapeOwner18 shape;
    u8 unk40[0x20];
    FieldShapeRecord20 record;
    FieldClass151570* unk80;
    char unk84[17];
};


/** Partial receiver containing a list sentinel and its count word. */
struct FieldShapeListOwner20
{
    u8 unk00[0x10];
    u8 unk10[8];
    FieldClass151620* next;
    u32 count;
};

/** Fixed attribute payload header: Lib45B110 begins descriptor entries at0x30. */
struct FieldShapeData30
{
    FieldShapeData10 prefix;
    u8 unk10[0x20];
};

/** Attribute resource header followed by the shape data bound by the Lib loader. */
struct FieldShapeAttributeResource
{
    u32 tag;
    u8 unk04[0xC];
    FieldShapeData30 data;
};

/** Pair of components in the optional allocation owned by FieldClass15B900. */
struct FieldFloatPair8
{
    float unk00;
    float unk04;
};

/** List owner with table D_15B900 and optional interpolation storage. */
class FieldClass15B900 : public FieldClass15B950
{
public:
    FieldClass1514F8* unk8c;
    float unk90;
    float unk94;
    float unk98;
    float unk9c;
    FieldFloatPair8* unkA0;
    s32 unkA4;
    u8 unkA8[8];

    /** @brief Release interpolation storage, then destroy the inherited list. */
    virtual ~FieldClass15B900();

    /**
     * @brief Build interpolation storage and append the listed vectors.
     * @param key Running sort value updated for each node.
     */
    virtual void func_002DD7B0(float* key);

    /** @brief Clear the inherited list and release interpolation storage. */
    virtual void func_002DDA70();

    /** @brief Release the owned vector array and component allocation. */
    void func_002DCD20();
};

/**
 * Partial 16-byte class with vtable D_1515D0 in main data. Its vtable pointer
 * follows its data at offset 0xC.
 */
class FieldClass1515D0
{
public:
    /** @brief Initialize empty owned resource storage. */
    FieldClass1515D0()
    {
        unk08 = 0;
        unk04 = 0;
        unk00 = 0;
    }

    void* unk00;
    void* unk04;
    u8 unk08;
    u8 unk09[3];

    /** @brief Release the buffer when this object owns its storage. */
    virtual ~FieldClass1515D0()
    {
        if (!unk08)
        {
            ::operator delete(unk04);
        }
    }
};

/** Partial FieldClass1515D0 with four more virtual slots, with vtable D_154D20 in main data. */
class FieldClass154D20 : public FieldClass1515D0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass154D20();

    /** @brief Virtual handler slot 1. */
    virtual void func_0020BDA0();

    /** @brief Virtual handler slot 2. */
    virtual void func_0020BD00();

    /**
     * @brief Return the FieldClass1515D0 part to use.
     * @return This object.
     */
    virtual FieldClass1515D0* func_001DDCD0();

    /** @brief Virtual handler slot 4. */
    virtual void func_0020BCF0();
};

/** Shape-resource and list owner identified by MAIN vtable D_151640. */
class FieldClass151640 : public FieldClass154D20, public FieldClass1502A0
{
public:
    /** @brief Destroy all shape lists and the inherited resource storage. */
    virtual ~FieldClass151640();
    /** @brief Update the list at offset 0x88. */
    virtual void func_0020BDA0();
    /** @brief Return this shape resource. @return The inherited resource receiver. */
    virtual FieldClass1515D0* func_001DDCD0();
    /** @brief Delete all nodes in the inherited list. */
    virtual void func_001DD730();
    FieldClass1502A0 unk88;
    FieldClass1502A0 unk100;
    FieldClass1502A0 unk178;
    FieldClass1502A0 unk1f0;
};

class FieldClass15B950;

/**
 * Partial FieldClass150F90 with three more virtual slots, with vtable D_151510
 * in main data. Its constructor (func_0020BF70) sets type bit 0x1 in unk78.
 * Overrides of earlier slots are not declared yet.
 */
class FieldClass151510 : public FieldClass150F90
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass151510();

    /** @brief Virtual handler slot 16. */
    virtual void func_0020BE50();

    /** @brief Virtual handler slot 17. */
    virtual void func_0020BF00();

    /**
     * @brief Virtual handler slot 18.
     * @param arg Argument whose meaning is not yet known.
     */
    virtual void func_0020BF50(void* arg);

    /**
     * @brief Test whether an object is stored at offset 0x148.
     * @return True when the pointer at offset 0x148 is set.
     */
    bool test_unk148() const
    {
        if (unk148)
        {
            return true;
        }
        return false;
    }

    /**
     * @brief Test bits of the word at offset 0x204.
     * @param mask Bits to test.
     * @return True when any bit in mask is set.
     */
    bool test_unk204(u32 mask) const
    {
        if (unk204 & mask)
        {
            return true;
        }
        return false;
    }

    float unkA0;
    float unkA4;
    FieldClass154D20* unkA8;
    u32 unkAC;
    u32 unkB0;
    u8 unkB4[0x90];
    FieldClass15B950* unk144;
    void* unk148;
    u8 unk14c[0x24];
    FieldVec4A unk170;
    FieldVec4A unk180;
    FieldVec4A unk190;
    u8 unk1a0[0x20];
    FieldVec4A unk1c0;
    u8 unk1d0[0x34];
    u32 unk204;
    u32 unk208;
};
#endif

#endif
