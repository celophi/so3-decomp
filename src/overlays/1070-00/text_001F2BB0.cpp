#include "include_asm.h"
#include "overlays/1070-00/text_001F2BB0.h"
#include "overlays/1070-00/text_00284BF0.h"

extern "C" void func_43ACC0(void* object);
extern "C" void func_002E63F0(void* first, void* second, s32 value);
extern "C" void func_001F8420(void* object, s32 value);
extern "C" void __dl__FPv(void* object);
extern "C" void* D_001B6620;
extern "C" FieldContextRef* D_001B64B0;
extern "C" void func_121E80(void* owner, void* object);
extern "C" void func_001FEC40(FieldFloatTransitions70* object, float target, float duration);

/** Partial callback interface with a method at offset 0x1C. */
class FieldCallbackDispatch1C
{
public:
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void callback(u32 first, u32 second);
};

#define FIELD_USE_SAVED_FLOAT_TARGET 3.402823466e38f

/** Partial target whose state byte is set before deletion. */
struct FieldDeleteTarget5F4
{
    u8 unk00[0x5F4];
    u8 state;
};

/** Partial owner containing the target pointer at offset four. */
struct FieldDeleteOwner04
{
    u32 unk00;
    FieldDeleteTarget5F4* target;
};

/** Partial transition state showing the observed cached source/destination pairs. */
struct FieldFloatTransitionCopyState
{
    u8 unk00[0x94];
    float source94;
    u8 unk98[4];
    float destination9c;
    u8 unka0[0x10];
    float sourceB0;
    u8 unkb4[4];
    float destinationB8;
    u8 unkbc[0xC];
    float sourceC8;
    u8 unkcc[4];
    float destinationD0;
    u8 unkd4[0x1C];
    unsigned __int128 sourceF0;
    unsigned __int128 destination100;
    u8 unk110[0x20];
    unsigned __int128 source130;
    unsigned __int128 destination140;
};

/** Minimal observed prefix containing the accessed value. */
struct FieldUnsignedByteRead3C
{
    u8 unk00[0x3C];
    u8 unk3C;
};

/** Minimal observed prefix containing the accessed value. */
struct FieldWordRead38
{
    u8 unk00[0x38];
    u32 unk38;
};

/** Minimal target prefix containing the written byte and word. */
struct FieldWordTarget74
{
    u8 unk00[0x40];
    u8 unk40;
    u8 unk41[0x33];
    u32 unk74;
};

/** Minimal receiver prefix containing the optional writable target. */
struct FieldNullableWordOwnerD4
{
    u8 unk00[0xD4];
    FieldWordTarget74* unkD4;
};

/** Partial receiver containing the two float inputs at offsets 0x1C and 0x20. */
struct FieldFloatPair1C
{
    u8 unk00[0x1C];
    float first;
    float second;
};

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F2BB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F2C50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F2CE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F2EB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F33B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F3410);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F3510);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F35D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F3620);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F3670);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F3710);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F3770);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F3970);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F3DD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F3E30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F3FB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F40B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F4130);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F4780);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F47E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F4860);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F4BC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F55B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F5650);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F57A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F5890);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F5920);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F59B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F5CD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F7540);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F7610);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F7680);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F76F0);

void func_001F77D0(const void* object)
{
    const FieldNullableWordOwnerD4* state = (const FieldNullableWordOwnerD4*)object;
    FieldWordTarget74* target = state->unkD4;

    if (target)
    {
        target->unk74 = 0x43000000;
        target->unk40 = 1;
    }
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F7800);

/**
 * @brief Call the receiver's callback with 0xFF and 0x80, then return two.
 * @param object Receiver with the callback dispatch table at offset zero.
 * @return Two after the callback.
 */
s32 func_001F7980(void* object)
{
    ((FieldCallbackDispatch1C*)object)->callback(0xFF, 0x80);
    return 2;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F79B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F7EB0);

void func_001F83C0(void* first, void* second)
{
    func_002E63F0(first, second, 0x7F);
}

void func_001F83E0(void* object)
{
    func_001F8420(object, 1);
}

void func_001F8400(void* object)
{
    func_001F8420(object, 0);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F8420);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F8540);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F8AC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F8EB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F8F20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F8F90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F9080);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F9490);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F94F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F9AA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F9BB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F9C50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F9CD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F9D00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F9D70);

void func_001F9E40(void* object)
{
}

void func_001F9E50(void* object)
{
}

void func_001F9E60(void* object)
{
}

void func_001F9E70(void* object)
{
}

void func_001F9E80(void* object)
{
}

void func_001F9E90(void* object)
{
}

void func_001F9EA0(void* object)
{
}

void func_001F9EB0(void* object)
{
}

s32 func_001F9EC0(void* object)
{
    return 0;
}

s32 func_001F9ED0(void* object)
{
    return 0;
}

u32 func_001F9EE0(const void* object)
{
    const FieldUnsignedByteRead3C* state = (const FieldUnsignedByteRead3C*)object;

    return state->unk3C;
}

u32 func_001F9EF0(const void* object)
{
    const FieldWordRead38* state = (const FieldWordRead38*)object;

    return state->unk38;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F9F00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001F9FA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FA020);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FA0E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FA160);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FA1D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FA270);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FA2F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FA370);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FA3E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FA4A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FA560);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FA620);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FA6E0);

FieldIndexedListNode* func_001FA7A0(const FieldIndexedList* list, s32 index)
{
    FieldIndexedListNode* node = list->head->next;
    for (s32 i = 0; i < index; i++)
    {
        if (node == 0)
        {
            return 0;
        }
        node = node->next;
    }
    return node;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FA7E0);

FieldIndexedListNode* func_001FA8A0(const FieldIndexedList* list, s32 index)
{
    FieldIndexedListNode* node = list->head->next;
    for (s32 i = 0; i < index; i++)
    {
        if (node == 0)
        {
            return 0;
        }
        node = node->next;
    }
    return node;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FA8E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FA9A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FAA60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FAA70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FAA80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FAA90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FAAA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FAAB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FAAC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FAAD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FAAE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FAAF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FAB00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FAB10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FAB20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FAB30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FAB40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FAB50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FAB60);

void func_001FAC00(void* object)
{
    func_4D7EB0(object);
    func_121E80(D_001B6620, object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FAC30);

FieldVector1FAD90::FieldVector1FAD90()
{
}

/**
 * @brief Initialize the shared float transition from the receiver's pair.
 * @param object Receiver containing the target and duration floats.
 * @return One after initializing the transition.
 */
extern "C" s32 func_001FADA0(const FieldFloatPair1C* object)
{
    func_001FE6D0(
        (FieldFloatTransitions70*)((u8*)D_001B64B0->context->unk14 + 0x30),
        object->first,
        object->second);
    return 1;
}

/**
 * @brief Initialize a shared float transition from the receiver's reversed pair.
 * @param object Receiver containing duration and target floats.
 * @return One after initializing the transition.
 */
extern "C" s32 func_001FADE0(const FieldFloatPair1C* object)
{
    func_001FEBE0(
        (FieldFloatTransitions70*)((u8*)D_001B64B0->context->unk14 + 0x30),
        object->second,
        object->first);
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FAE20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FAED0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FAF30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FAF70);

void func_001FAFC0(void* object)
{
}

/**
 * @brief Initialize the shared float transition through the alternate helper.
 * @param object Receiver containing duration and target floats.
 * @return One after initializing the transition.
 */
extern "C" s32 func_001FAFD0(const FieldFloatPair1C* object)
{
    func_001FEC40(
        (FieldFloatTransitions70*)((u8*)D_001B64B0->context->unk14 + 0x30),
        object->second,
        object->first);
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FB010);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FB050);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FB0C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FB120);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FB310);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FB3E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FB470);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FB510);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FB5B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FB650);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FB6F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FB790);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FB830);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FB8D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FB970);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FBA10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FBAB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FBB90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FBC30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FBCC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FBD30);

void func_001FBDC0(void* object)
{
    func_4D7EB0(object);
    func_121E80(D_001B6620, object);
}

s32 func_001FBDF0(void* object)
{
    return 14;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FBE00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FC610);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FC7A0);

void func_001FC8E0(void* object)
{
    func_4D7EB0(object);
    func_121E80(D_001B6620, object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FC910);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FC990);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FCA80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FCB00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FCB70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FCCA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FCD30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FCE00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FCEB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FCF10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FD1C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FD390);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FD640);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FD930);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FD9E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FDA90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FDB60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FDCE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FDE00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FDFA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FE050);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FE240);

s32 func_001FE2D0(void* object)
{
    return 5;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FE2E0);

s32 func_001FE370(void* object)
{
    return 14;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FE380);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FE430);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", __dt__16FieldClass16C478Fv);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FE590);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", __dt__16FieldClass172140Fv);

void func_001FE6D0(FieldFloatTransitions70* object, float target, float duration)
{
    object->unke0 = object->owner->unk544;
    object->unke4 = target;
    object->unke8 = duration;
    if (duration > 0.0f)
    {
        object->unkec = (object->unke4 - object->unke0) / object->unke8;
    }
    else
    {
        object->unkec = object->unke4 - object->unke0;
    }
    object->unk70 |= 0x200;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FE740);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FE810);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FE900);

void func_001FEA80(void* receiver)
{
    FieldFloatTransitionCopyState* object = (FieldFloatTransitionCopyState*)receiver;
    object->destinationB8 = object->sourceB0;
    object->destination9c = object->source94;
    object->destinationD0 = object->sourceC8;
    object->destination100 = object->sourceF0;
    object->destination140 = object->source130;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FEAB0);

void func_001FEB00(FieldFloatTransitions70* object, float target, float duration)
{
    if (target == FIELD_USE_SAVED_FLOAT_TARGET)
    {
        target = object->unk108;
    }
    object->unk114 = target - object->unkf8;
    if (duration)
    {
        object->unk114 /= duration;
    }
    object->unk118 = target;
    object->unk110 = duration;
    object->unk70 |= 0x8;
}

void func_001FEB70(FieldFloatTransitions70* object, float target, float duration)
{
    if (target == FIELD_USE_SAVED_FLOAT_TARGET)
    {
        target = object->unk104;
    }
    object->unk78 = target - object->unkf4;
    if (duration)
    {
        object->unk78 /= duration;
    }
    object->unk7c = target;
    object->unk74 = duration;
    object->unk70 |= 0x4;
}

void func_001FEBE0(FieldFloatTransitions70* object, float target, float duration)
{
    if (duration)
    {
        object->unkbc = duration;
        object->unkc4 = target;
        object->unkc0 = (target - object->unkb0) / duration;
        object->unk70 |= 0x20;
    }
    else
    {
        object->unkb0 = target;
        object->unkb4 = target;
        object->unk70 &= ~0x20;
    }
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FEC40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FEE00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FEEA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FEFE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FF130);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FF280);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FF3B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FF540);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FF6D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FF910);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_001FF960);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_00200D70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_00200DE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_00200E70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_00200FE0);

void func_002010C0(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_002010D0);

void func_00201180(void* object)
{
    func_43ACC0((u8*)object + 0x20);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_002011A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_002011F0);

void func_00201320(void* object)
{
    func_43ACC0((u8*)object + 0x20);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_00201340);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_002015E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_00201700);

void func_00201760(void* object)
{
    FieldDeleteTarget5F4* target = ((FieldDeleteOwner04*)object)->target;
    target->state = 5;
    __dl__FPv(object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_00201790);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_002017E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_00201840);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_00201A20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_00201A90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_00201B50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_002027C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_002028B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_00202980);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_001F2BB0", func_00202B70);
