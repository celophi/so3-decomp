#include "overlays/1070-00/text_00284BF0.h"
#include "overlays/1070-00/text_002649B0.h"
#include "overlays/1070-00/text_001E2B40.h"
#include "include_asm.h"

extern "C" void* D_001B6620;
extern "C" void func_121E80(void* owner, void* object);

extern "C" u64 D_4FC540[];
extern "C" float D_001B66B4;
extern "C" FieldContextRef* D_001B64B0;
extern "C" void func_4EA1E0(void);
extern "C" void* D_001B661C;
extern "C" u32 func_120ED0(void* object);
extern "C" void func_441010(void* object);
extern "C" void func_441070(void* object);
extern "C" void func_4DC5C0(void);
extern "C" void func_002776B0(void* object);
extern "C" void func_002881D0(void* object);
extern "C" s32 func_002064D0(void* object);
extern "C" void func_00248FD0(void* object, u32 value, u32 nextValue);
extern "C" void func_002783E0(void* object, float first, float second, float third);
extern "C" void func_002772B0(void* object, u32 value);
extern "C" void func_0020CE90(void* object, u32 value);
extern "C" void func_001FCB70(void* object, float value);
extern "C" void func_001FCB00(void* object, u32 value);
extern "C" void func_00273B00(void* object, u32 value);
extern "C" void func_00276D80(void* object, float value);

extern "C" void func_0020A000(FieldContext58* context, u32 first, u32 second);
extern "C" void func_00223580(void* owner, void* object);
extern "C" void* __vt__16FieldClass16AB80;
extern "C" void func_4441E0(void* object);
extern "C" u8 D_171680[];
extern "C" u8 D_171690[];
extern "C" void func_123230(void);
extern "C" u8 D_16C380[];
extern "C" void func_0025A0C0(void* target, u32 nested_value, u32 receiver_value);
extern "C" void func_0025A230(void* target, u32 nested_value, u32 receiver_value);
extern "C" s32 func_108030(void* object, u32 first, u32 second, u32 third, u32 fourth);

/** Partial receiver initialized by func_00288210. */
struct FieldClassStateAB80
{
    void* vtable;
    u32 unk04;
    u32 unk08;
};

/** Partial receiver with the conditional word at offset 0x40. */
struct FieldConditionalWord40
{
    u8 unk00[0x40];
    u32 unk40;
};

/** Partial receiver with a word cursor at offset 0x540. */
struct FieldWordCursor540
{
    u8 unk00[0x540];
    u32* cursor;
};

/** Partial receiver with the shared value pointer at offset 0x80D8. */
struct FieldSharedValue80D8
{
    u8 unk00[0x80D8];
    void* unk80d8;
};

/** Partial receiver initialized by func_0028B110. */
struct FieldInitializedStateB110
{
    u8 unk00[4];
    u32 unk04;
    u8 unk08[0x0D];
    u8 unk15;
    u8 unk16[2];
    void* unk18;
};

/** Child value forwarded by func_00291560. */
struct FieldNestedChild91560
{
    u8 unk00[0x70];
    u32 unk70;
};

/** Nested receiver value read by func_00291560. */
struct FieldNestedValue91560
{
    u8 unk00[0x7C];
    FieldNestedChild91560* unk7c;
};

/** Partial receiver with a nested pointer and word at offset 0x1C. */
struct FieldReceiver91560
{
    u8 unk00[0x10];
    FieldNestedValue91560* unk10;
    u8 unk14[8];
    u32 unk1c;
};

/** Partial receiver with a unit float and a flag at offset 0x591. */
struct FieldUnitFlag591
{
    u8 unk00[0x14];
    float unk14;
    u8 unk18[0x579];
    u8 unk591_0 : 1;
    u8 unk591_1_7 : 7;
};

/** Partial source with a linked target and three float values. */
struct FieldThreeFloatValueSource
{
    u8 unk00[0x10];
    FieldTargetLink* unk10;
    u8 unk14[8];
    float unk1c;
    float unk20;
    float unk24;
};



INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00284BF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00284CA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00284D10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00284E40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00284F90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002850C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00285220);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00285410);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002855A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00285770);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00285980);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00285DA0);

void func_00286050(FieldWordFlags* object, u32 mask)
{
    object->unk78 |= mask;
}

FieldVector* func_00286060(FieldVector* vector, float value)
{
    vector->x = value;
    vector->y = value;
    vector->z = value;
    vector->w = value;
    return vector;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00286080);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00286190);

void func_00286210(void* destination, const void* source)
{
    *(u32*)((u8*)destination + 0x210) = *(const u32*)((const u8*)source + 0x210);
    func_4DC5C0();
}

/**
 * @brief Initialize the receiver, then pass it to the shared owner.
 * @param object Receiver to initialize and process.
 */
void func_00286230(void* object)
{
    func_4D7EB0(object);
    func_121E80(D_001B6620, object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00286260);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00286320);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002863A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002865D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00286780);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00286A10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00286CA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00287440);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00287DD0);

s32 func_00288030(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00288040);

void func_002880B0(unsigned __int128* destination, const unsigned __int128* source)
{
    *destination = *source;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002880C0);

s32 func_00288180(const FieldReceiver78* object)
{
    return object->unk134;
}

/**
 * @brief Initialize the receiver, install its vtable, and return it.
 * @param object Receiver to initialize.
 * @return The initialized receiver.
 */
extern "C" FieldClassStateAB80* func_00288190(FieldClassStateAB80* object)
{
    func_002881D0(object);
    object->vtable = D_171690;
    return object;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002881D0);

/** Initialize the object through its base helper and set its derived state. */
void* func_00288210(void* object)
{
    FieldClassStateAB80* state = (FieldClassStateAB80*)object;
    func_00288250(object);
    state->vtable = &__vt__16FieldClass16AB80;
    state->unk04 = 0;
    state->unk08 = 0;
    return object;
}

extern "C" void* __vt__16FieldClass16AB70;

void* func_00288250(void* object)
{
    *(void**)object = &__vt__16FieldClass16AB70;
    return object;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00288270);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00288310);

FieldContext* func_00288640(const FieldContextRef* ref)
{
    return ref->context;
}

s32 func_00288650(const void* sentinel, const void* node)
{
    return sentinel == node;
}

FieldListNode* func_00288660(const FieldListNode* node)
{
    return node->next;
}

void* func_00288670(void* object)
{
    return object;
}

char* func_00288680(FieldContextE4* object)
{
    return object->unk140;
}

void* func_00288690(const FieldContextRef* ref)
{
    return ref->context->unke4;
}

u8 func_002886A0(const FieldReceiver78* object)
{
    return object->unk138;
}

void func_002886B0(const FieldContextRef* ref, void* object)
{
    ref->context->unke0 = object;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002886C0);

void func_00288710(FieldContext* context, s32 value)
{
    context->unkde_3 = value;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00288730);

void func_00288820(FieldReceiver78* object, s32 value)
{
    object->unk00 = value;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00288830);

u64 func_002893B0(s32 index)
{
    return D_4FC540[index];
}

/**
 * @brief Copy four vectors to an intermediate destination, then to the receiver.
 * @param destination Final destination for the vectors.
 * @param intermediate Destination copied from source before the final copy.
 * @param source Source of the four vectors.
 * @return The final destination pointer.
 */
void* func_002893D0(void* destination, void* intermediate, const void* source)
{
    unsigned __int128* intermediateWords = (unsigned __int128*)intermediate;
    const unsigned __int128* sourceWords = (const unsigned __int128*)source;
    intermediateWords[0] = sourceWords[0];
    intermediateWords[1] = sourceWords[1];
    intermediateWords[2] = sourceWords[2];
    intermediateWords[3] = sourceWords[3];
    return func_00289410(destination, intermediate);
}

void* func_00289410(void* destination, const void* source)
{
    unsigned __int128* destinationWords = (unsigned __int128*)destination;
    const unsigned __int128* sourceWords = (const unsigned __int128*)source;
    destinationWords[0] = sourceWords[0];
    destinationWords[1] = sourceWords[1];
    destinationWords[2] = sourceWords[2];
    destinationWords[3] = sourceWords[3];
    return destination;
}

void func_00289440(void)
{
    func_4EA1E0();
}

void* func_00289460(void* object)
{
    return object;
}

s32 func_00289470(const FieldLargeTarget* object)
{
    return object->unk8098 == 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00289490);

void func_00289660(FieldLargeState* object, void* value)
{
    object->unk15e790 = value;
}

float func_00289670(void* object)
{
    return D_001B66B4;
}

FieldLargeTarget* func_00289680(const FieldLargeSubobject* object)
{
    return object->unk15e640;
}

FieldLargeSubobject* func_00289690(FieldLargeState* object)
{
    return &object->unkc0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002896A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00289790);

FieldVector* func_00289830(FieldVector* vectors, s32 index)
{
    return &vectors[index];
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00289840);

void func_002898B0(void* object)
{
    func_441010((u8*)object + 0xC0);
}

s16 func_002898D0(const FieldLargeState* object)
{
    return object->unk15e786;
}

s16 func_002898E0(const FieldLargeState* object)
{
    return object->unk15e784;
}

void func_002898F0(void* object)
{
    func_441070((u8*)object + 0xC0);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00289910);

void func_002899A0(FieldObjectFlags* object, u16 mask)
{
    object->unk6c &= mask;
}

void func_002899B0(FieldObjectFlags* object, s32 value)
{
    object->unk6e = value;
}

void* func_002899C0(void* object)
{
    return object;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002899D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00289A80);

u32 func_00289CC0(const FieldIndexedRef* object, s32 index)
{
    return object->source->unk10->words[index];
}

u8 func_00289CE0(const FieldLargeState* object)
{
    return object->unk15e78c;
}

u8 func_00289CF0(const FieldSecondaryState* object)
{
    return object->unkf17b;
}

void* func_00289D00(const FieldContextRef* ref)
{
    return ref->context->unk58;
}

/**
 * @brief Initialize the receiver, then pass it to the shared owner.
 * @param object Receiver to initialize and process.
 */
void func_00289D10(void* object)
{
    func_4D7EB0(object);
    func_121E80(D_001B6620, object);
}

void func_00289D40(FieldContext38* object)
{
    object->unk5c4 = 0;
}

void* func_00289D50(const FieldContextRef* ref)
{
    return ref->context->unk38;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00289D60);

void func_0028A0A0(FieldLargeState* object, s32 first, s32 second, s32 third)
{
    func_0028A100(func_00289680(&object->unkc0), first, second, third);
}

void func_0028A100(FieldLargeTarget* object, s32 first, s32 second, s32 third)
{
    object->unk80ac = first;
    object->unk80b0 = second;
    object->unk80b4 = third;
}

void func_0028A130(FieldLargeState* object, float first, float second)
{
    func_0028A180(func_00289680(&object->unkc0), first, second);
}

void func_0028A180(FieldLargeTarget* object, float first, float second)
{
    object->unk80c4 = first;
    object->unk80c8 = second;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028A1A0);

/** Initialize the receiver and install its shared value pointer. */
void* func_0028A210(void* object)
{
    FieldSharedValue80D8* state = (FieldSharedValue80D8*)object;
    func_4441E0(object);
    state->unk80d8 = D_171680;
    return object;
}

s32 func_0028A250(s32 first, s32 second)
{
    s32 product = first * second;
    s32 half = product * 9 / 2;
    s32 subtotal = half + 1283948;
    return subtotal + product * 8 + 677824;
}

void func_0028A290(FieldWordState* object, s32 value)
{
    object->unk2c = value;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028A2A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028A360);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028A440);

void func_0028A790(FieldLargeState* object, u8 value)
{
    func_0028A7D0(func_00289680(&object->unkc0), value);
}

void func_0028A7D0(FieldLargeTarget* object, u8 value)
{
    object->unk80d4 = value;
}

u8 func_0028A7E0(const FieldByteStateOwner* object)
{
    return func_0028A800(&object->unk120);
}

u8 func_0028A800(const FieldByteState* object)
{
    return object->unk04;
}

void* func_0028A810(const FieldContextRef* ref)
{
    return ref->context->unk30;
}

void* func_0028A820(const FieldContextRef* ref)
{
    return ref->context->unk40;
}

void* func_0028A830(const FieldContextRef* ref)
{
    return ref->context->unk2c;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028A840);

void* func_0028A8B0(const FieldContext18* object)
{
    return object->unk3a0;
}

void* func_0028A8C0(const FieldContextRef* ref)
{
    return ref->context->unk18;
}

void* func_0028A8D0(FieldContextE4* object)
{
    return object->unkb4;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028A8E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028AFB0);

s32 func_0028B040(void* object)
{
    void* target = *(void**)object;
    return func_108030(target, 0, 0, 0, 1) != 0;
}

void func_0028B070(FieldAllocatedState* object, s32 value)
{
    object->unk0c = value;
}

void func_0028B080(FieldAllocatedState* object, u8 value)
{
    object->unk18 = value;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028B090);

/** Initialize the receiver fields and run its no-argument helper. */
void* func_0028B110(void* object)
{
    FieldInitializedStateB110* state = (FieldInitializedStateB110*)object;
    state->unk18 = D_16C380;
    state->unk04 = 0;
    state->unk15 = 0;
    func_123230();
    return object;
}

s32 func_0028B150(const FieldContext58* object)
{
    return object->unk1b4 == -2;
}

s32 func_0028B170(const FieldSlotObject* object)
{
    return object->unka0;
}

FieldSlotObject* func_0028B180(const FieldContext38* object, u8 index)
{
    return object->unk598[index];
}

void* func_0028B1A0(const FieldContextRef* ref)
{
    return ref->context->unk3c;
}

void* func_0028B1B0(const FieldContextRef* ref)
{
    return ref->context->unk14;
}

void func_0028B1C0(FieldLinkedObject* object, void* receiver)
{
    object->unk18 = receiver;
}

void* func_0028B1D0(const FieldContextRef* ref)
{
    return ref->context->unk54;
}

void* func_0028B1E0(const FieldContextRef* ref)
{
    return ref->context->unk04;
}

void* func_0028B1F0(const FieldContextRef* ref)
{
    return ref->context->unk4c;
}

s32 func_0028B200(const FieldFlaggedObject* object)
{
    return object->unk49 & 1;
}

FieldFlaggedObject* func_0028B210(const FieldFlaggedObjectRef* object)
{
    return object->unk1c;
}

void func_0028B220(FieldContext* context, s32 value)
{
    context->unkdc_1 = value;
}

void func_0028B240(FieldContext38* object)
{
    object->unk5c0 = 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028B250);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028B2A0);

extern "C" void* __vt__16FieldClass16AB60;

void* func_0028B380(void* object)
{
    *(void**)object = &__vt__16FieldClass16AB60;
    return object;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028B3A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028B400);

s32 func_0028B460(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028B470);

s32 func_0028B4E0(void* object)
{
    return 9;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028B4F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028B500);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028B510);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028B520);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028B590);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028B6B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028B760);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028B7B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028B810);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028BA40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028BB10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028BB60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028C830);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028C910);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028C990);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028CBE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028CC60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028D2C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028D390);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028D6C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028D790);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028D870);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028D910);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028D990);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028E090);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028E350);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028E380);

s32 func_0028E3C0(void* object)
{
    return D_001B64B0->context->unk38->unk5c8 != 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028E3E0);

void func_0028E440(FieldFlag2F0* object)
{
    object->unk2f0 = 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028E450);

u8 func_0028E520(const FieldFlag2F0* object)
{
    return object->unk2f0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028E530);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028E660);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028E6D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028E7B0);

/**
 * @brief Store the helper result in the receiver's word at offset 0x424.
 * @param object Receiver containing the output word.
 * @return One after the helper call.
 */
s32 func_0028E900(void* object)
{
    FieldWordSource540* state = (FieldWordSource540*)object;
    state->unk424 = func_120ED0(D_001B661C);
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028E930);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028E980);

/**
 * @brief Advance the receiver cursor and pass its adjusted words to the helper.
 * @param object Receiver containing the word cursor at offset 0x540.
 * @return One after the helper call.
 */
extern "C" s32 func_0028EA40(void* object)
{
    FieldWordCursor540* state = (FieldWordCursor540*)object;
    u32* cursor = state->cursor;
    state->cursor = cursor + 1;
    u32 first = cursor[0];
    u32 second = state->cursor[0];
    func_00248FD0(object, first + 0x2000, second);
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028EA80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028F5C0);

s32 func_0028F630(FieldWordSource540* object)
{
    object->count1c++;
    const u32* source = object->unk540;
    object->unk540 = source + 1;
    object->values20[0x100 - object->count1c] = *source;

    object->count1c++;
    object->values20[0x100 - object->count1c] = *object->unk540;
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028F6A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028F760);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028F810);

s32 func_0028F860(FieldWordSource540* object)
{
    object->unk18 = *object->unk540;
    return 0;
}

s32 func_0028F880(FieldWordSource540* object)
{
    if (object->unk424 != 0)
    {
        object->unk18 = *object->unk540;
        return 0;
    }
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028F8B0);

s32 func_0028F980(FieldUnsignedFloatSource540* object)
{
    object->unk14 = *object->unk540;
    return 1;
}

s32 func_0028F9C0(void* receiver)
{
	FieldUnitFlag591* object = (FieldUnitFlag591*)receiver;
    object->unk591_0 = 1;
    object->unk14 = 1.0f;
    return 0;
}

s32 func_0028F9F0(void* object)
{
    return 3;
}

/**
 * @brief Initialize the receiver, then pass it to the shared owner.
 * @param object Receiver to initialize and process.
 */
void func_0028FA00(void* object)
{
    func_4D7EB0(object);
    func_121E80(D_001B6620, object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028FA30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028FC00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028FCF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028FDB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028FE30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028FED0);

s32 func_0028FF70(const FieldValueSource* object)
{
    func_001FCB00(object->unk10->unk7c, object->unk1c);
    return 1;
}

s32 func_0028FFA0(const FieldTwoFloatValueSource* object)
{
    func_001FCB70(object->unk10->unk7c, object->unk1c);
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_0028FFD0);

s32 func_00290010(const FieldValueSource* object)
{
    func_002772B0(object->unk10->unk7c, object->unk1c);
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00290040);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00290120);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002901A0);

s32 func_002902B0(const FieldValueSource* object)
{
    func_0020CE90(object->unk10->unk7c, object->unk1c);
    return 1;
}

s32 func_002902E0(const FieldByteValueSource10* object)
{
    func_00273B00(object->unk10->unk7c, object->unk1c);
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00290310);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00290360);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002903B0);

s32 func_00290450(const FieldValueSource* object)
{
    object->unk10->unk7c->unk580 = object->unk1c;
    return 1;
}

s32 func_00290470(const FieldValueSource* object)
{
    object->unk10->unk7c->unk57c = object->unk1c;
    return 1;
}

s32 func_00290490(const FieldValueSource* object)
{
    func_002776B0(object->unk10->unk7c);
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002904C0);

/**
 * @brief Pass four receiver words and the shared context to the helper.
 * @param object Receiver containing the words at offsets 0x1C through 0x28.
 * @return One after the helper call.
 */
s32 func_00290520(const void* object)
{
    const u32* words = (const u32*)object;
    func_00209FA0(D_001B64B0->context->unk58, words[7], words[8], 0x40,
                  words[9], words[10]);
    return 1;
}

/** Partial receiver with two observed words at offsets 0x1C and 0x20. */
struct FieldWordState1C20
{
    u8 pad00[0x1C];
    u32 unk1c;
    u32 unk20;
};

/**
 * @brief Forward the receiver's two words and shared context to func_0020A000.
 * @param object Receiver containing the words at offsets 0x1C and 0x20.
 * @return One after the helper call.
 */
extern "C" s32 func_00290560(void* object)
{
    FieldWordState1C20* state = (FieldWordState1C20*)object;
    func_0020A000(D_001B64B0->context->unk58, state->unk1c, state->unk20);
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00290590);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002909B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00290AF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00290B30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00290BF0);

s32 func_00290C60(const FieldTwoFloatValueSource* object)
{
    func_00273EA0((FieldFloatTransition330*)object->unk10->unk7c, object->unk1c, object->unk20);
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00290C90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00290D20);

s32 func_00290D70(const FieldValueSource* object)
{
    FieldTargetValues* target = object->unk10->unk7c;
    u32 value = object->unk1c;
    if (value == 0xFFFFFFFF)
    {
        value = target->unk3b0;
    }
    target->unk3ac = value;
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00290DA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00290E20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00291370);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002913B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002914F0);

s32 func_00291530(const void* receiver)
{
    const FieldThreeFloatValueSource* object = (const FieldThreeFloatValueSource*)receiver;
    func_002783E0(object->unk10->unk7c, object->unk1c, object->unk20, object->unk24);
    return 1;
}

/** Forward the context target and two receiver values to its helper. */
s32 func_00291560(void* receiver)
{
    FieldReceiver91560* object = (FieldReceiver91560*)receiver;
    func_0025A0C0(D_001B64B0->context->unk08->unkdc,
                  object->unk10->unk7c->unk70, object->unk1c);
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002915A0);

/** Forward the context target and two receiver values to its helper. */
s32 func_00291610(void* receiver)
{
    FieldReceiver91560* object = (FieldReceiver91560*)receiver;
    func_0025A230(D_001B64B0->context->unk08->unkdc,
                  object->unk10->unk7c->unk70, object->unk1c);
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00291650);

s32 func_00291890(const FieldValueSource* object)
{
    object->unk10->unk7c->unk1fc = object->unk1c;
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002918B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00291970);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002919F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00291A70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00291AB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00291BE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00291C70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00291D30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00291E90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00291F90);

s32 func_00292070(const FieldTwoFloatValueSource* object)
{
    func_00276D80(object->unk10->unk7c, object->unk1c);
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002920A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00292110);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00292160);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00292230);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00292480);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002924C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002925E0);

/** Partial receiver with an object pointer at offset 0x7C. */
struct FieldPointerAt7C
{
    u8 pad00[0x7C];
    void* value7c;
};

/** Partial receiver with a pointer to FieldPointerAt7C at offset 0x10. */
struct FieldPointerAt10
{
    u8 pad00[0x10];
    FieldPointerAt7C* object;
};

/**
 * @brief Pass the nested pointer and shared context to func_00223580.
 * @param object Receiver containing the nested object pointer.
 * @return One after the helper call.
 */
extern "C" s32 func_00292660(void* object)
{
    FieldPointerAt10* state = (FieldPointerAt10*)object;
    func_00223580(D_001B64B0->context->unk04, state->object->value7c);
    return 1;
}

s32 func_00292690(const FieldFloatSource10* object)
{
    object->unk10->unk78 = object->unk1c;
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002926B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00292730);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00292840);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00292960);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00292A00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00292AA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00292B40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00292BE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00292C80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00292D20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00292DC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00292E60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00292F00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00292FA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00293040);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002930E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00293180);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00293220);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002932C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00293360);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00293400);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002934A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00293540);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002935E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00293680);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00293720);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002937C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00293860);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00293900);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002939A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00293A40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00293AE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00293B80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00293C20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00293CC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00293D60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00293E00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00293EA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00293F40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00293FE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00294080);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00294120);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002941C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00294260);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00294300);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002943A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00294440);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002944E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00294580);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00294620);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002946C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00294760);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00294800);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002948A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00294940);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_002949E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00294A80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00294AF0);

/**
 * @brief Store ten in the receiver word when its predicate returns one.
 * @param object Receiver checked by the predicate.
 */
extern "C" void func_00294BA0(FieldConditionalWord40* object)
{
    if (func_002064D0(object) == 1)
    {
        object->unk40 = 10;
    }
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00284BF0", func_00294BE0);
