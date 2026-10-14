#include "include_asm.h"
#include "overlays/1070-00/text_002D55D0.h"
#include "overlays/lib/vector.h"
#include "overlays/1070-00/text_001E2B40.h"

extern "C" u8 D_1752C0[];

/** Partial callback interface with a method at offset 0x58. */
class FieldCallbackDispatch58
{
public:
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2c();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3c();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4c();
    virtual void slot50();
    virtual void slot54();
    virtual void callback(u32 first, u32 second);
};

/** Partial callback interface with methods at offsets 0x64 through 0x70. */
class FieldCallbackDispatch70
{
public:
    virtual void slot8();
    virtual void slotc();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2c();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3c();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4c();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5c();
    virtual void slot60();
    virtual void slot64();
    virtual void slot68();
    virtual void slot6c();
    virtual void slot70();
    virtual void slot74();
    virtual void slot78();
    virtual float slot7c();
};

extern "C" u8 D_1752A0[];
extern "C" u8 D_1752B0[];
extern "C" u8 D_175290[];
extern "C" u8 D_175280[];
extern "C" u8 D_175270[];
extern "C" float D_001B66B4;
extern "C" void* D_001B6620;
extern "C" void func_121E80(void* owner, void* object);


typedef struct PackedModePair
{
    u8 lowMode : 4;
    u8 highMode : 4;
    u8 hasModeFour : 1;
    u8 unk01_1_7 : 7;
} PackedModePair;

typedef struct PackedModesOwner
{
    u8 unk00[0x22];
    PackedModePair at22;
    u8 unk24[0x1E];
    PackedModePair at42;
    u8 unk44[0xE];
    PackedModePair at52;
} PackedModesOwner;

typedef struct FloatKeyScanEntry_text_002D55D0_08
{
    float key00;
    u8 unk04[0x4];
} FloatKeyScanEntry_text_002D55D0_08;

typedef struct FloatKeyScanOwner_text_002D55D0_08
{
    u8 unk00[0x4];
    FloatKeyScanEntry_text_002D55D0_08* entries;
    u8 unk08[0x10];
    s16 count18;
    u8 unk1a[0xE];
    s16 count28;
    u8 unk2a[0xE];
    s16 count38;
    u8 unk3a[0xE];
    s16 count48;
} FloatKeyScanOwner_text_002D55D0_08;

typedef struct FloatKeyScanEntry_text_002D55D0_10
{
    float key00;
    u8 unk04[0x8];
    float key0c;
} FloatKeyScanEntry_text_002D55D0_10;

typedef struct FloatKeyScanOwner_text_002D55D0_10
{
    u8 unk00[0x4];
    FloatKeyScanEntry_text_002D55D0_10* entries;
    u8 unk08[0x10];
    s16 count18;
    u8 unk1a[0xE];
    s16 count28;
    u8 unk2a[0xE];
    s16 count38;
    u8 unk3a[0xE];
    s16 count48;
} FloatKeyScanOwner_text_002D55D0_10;

typedef struct FloatKeyScanEntry_text_002D55D0_20
{
    float key00;
    u8 unk04[0x8];
    float key0c;
    u8 unk10[0x10];
} FloatKeyScanEntry_text_002D55D0_20;

typedef struct FloatKeyScanOwner_text_002D55D0_20
{
    u8 unk00[0x4];
    FloatKeyScanEntry_text_002D55D0_20* entries;
    u8 unk08[0x10];
    s16 count18;
    u8 unk1a[0xE];
    s16 count28;
    u8 unk2a[0xE];
    s16 count38;
    u8 unk3a[0xE];
    s16 count48;
} FloatKeyScanOwner_text_002D55D0_20;

typedef struct FloatKeyScanEntry_text_002D55D0_30
{
    float key00;
    u8 unk04[0x8];
    float key0c;
    u8 unk10[0x20];
} FloatKeyScanEntry_text_002D55D0_30;

typedef struct FloatKeyScanOwner_text_002D55D0_30
{
    u8 unk00[0x4];
    FloatKeyScanEntry_text_002D55D0_30* entries;
    u8 unk08[0x10];
    s16 count18;
    u8 unk1a[0xE];
    s16 count28;
    u8 unk2a[0xE];
    s16 count38;
    u8 unk3a[0xE];
    s16 count48;
} FloatKeyScanOwner_text_002D55D0_30;

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D55D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D5620);

/**
 * @brief Initialize the secondary receiver pointer and return the object.
 * @param object Receiver to initialize.
 * @return The initialized receiver.
 */
extern "C" FieldPointerAt10* func_002D56A0(FieldPointerAt10* object)
{
    func_002D66B0(object);
    object->unk10 = D_1752C0;
    *(void**)object = 0;
    return object;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D56E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D5780);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D5810);

/** Receiver field initialized by func_002D5890 before resetting its sequence. */
struct FieldSequenceResetReceiver
{
    u8 unk00[0xB0];
    FieldVec4B value;
};

/**
 * @brief Clear the receiver's vector and reset its sequence state.
 * @param object Receiver whose vector and sequence state are reset.
 */
extern "C" void func_002D5890(FieldSequenceResetReceiver* object)
{
    object->value = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    func_002D78D0((FieldSequenceState40*)object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D58D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D6040);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D6120);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D6190);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D6240);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D62B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D6320);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D6390);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D6470);

void func_002D64B0(const void* object, void* result)
{
    *(FieldVec4B*)result = *(const FieldVec4A*)((const u8*)object + 0xC0);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D64D0);

FieldPointerAt4C* func_002D6550(FieldPointerAt4C* object)
{
    object->unk4c = D_1752B0;
    return object;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D6570);

FieldPointerAt1C* func_002D65D0(FieldPointerAt1C* object)
{
    object->unk1c = D_1752A0;
    return object;
}

FieldPointerAt1C* func_002D65F0(FieldPointerAt1C* object)
{
    object->unk1c = D_175290;
    func_002D6630((FieldResetState10*)object);
    return object;
}

void func_002D6630(FieldResetState10* object)
{
    object->unk10 = 0;
    object->unk12 = 0;
    object->unk14 = 0;
    object->unk18 = 0;
}

FieldPointerAt1C* func_002D6650(FieldPointerAt1C* object)
{
    object->unk1c = D_175280;
    func_002D6690((FieldResetState10*)object);
    return object;
}

void func_002D6690(FieldResetState10* object)
{
    object->unk10 = 0;
    object->unk12 = 0;
    object->unk14 = 0;
    object->unk18 = 0;
}

FieldPointerAt10* func_002D66B0(FieldPointerAt10* object)
{
    object->unk10 = D_175270;
    func_002D66F0((FieldResetState04*)object);
    return object;
}

void func_002D66F0(FieldResetState04* object)
{
    object->unk04 = 0;
    object->unk06 = 0;
    object->unk08 = 0;
    object->unk0c = 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D6710);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D67C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D6810);

/** Set the low packed mode at 0x42 and record whether either mode equals four. */
void func_002D68C0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at42.lowMode = mode;
    receiver->at42.hasModeFour = receiver->at42.lowMode == 4 || receiver->at42.highMode == 4;
}

/** Set the high packed mode at 0x42 and record whether either mode equals four. */
void func_002D6920(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at42.highMode = mode;
    receiver->at42.hasModeFour = receiver->at42.lowMode == 4 || receiver->at42.highMode == 4;
}

u32 func_002D6980(const FieldWordAt30* object)
{
    return object->unk30;
}

s16 func_002D6990(const FieldSignedHalfAt38* object)
{
    return object->unk38;
}

void func_002D69A0(FieldWords002D69A0* object)
{
    object->words[0] = 0;
    object->words[1] = 0;
    object->words[2] = 0;
    object->words[3] = 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D69C0);

void* func_002D6A10(const FieldPointerAt04* object)
{
    return object->unk04;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D6A20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D6B00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D6C60);

void func_002D6D10(FieldSequenceState20* object)
{
    object->unk04 = 0;
    object->state.unk12_0_3 = 1;
    object->state.unk12_4_7 = 1;
    object->state.unk0a = 0;
    object->state.unk08 = 0;
    object->state.unk0c = -1;
    object->state.unk00 = 0;
    object->state.unk0e = -1;
    object->state.unk10 = -1;
    object->state.unk13_0 = 0;
    object->state.unk13_1 = 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D6DA0);

void func_002D6DF0(FieldSequenceState20* object, u8 mode)
{
    object->state.unk12_0_3 = mode;
    object->state.unk13_0 = object->state.unk12_0_3 == 4 || object->state.unk12_4_7 == 4;
}

void func_002D6E50(FieldSequenceState20* object, u8 mode)
{
    object->state.unk12_4_7 = mode;
    object->state.unk13_0 = object->state.unk12_0_3 == 4 || object->state.unk12_4_7 == 4;
}

s32 func_002D6EB0(const FieldSequenceState20* object)
{
    return object->state.unk00;
}

s16 func_002D6EC0(const FieldSequenceState20* object)
{
    return object->state.unk08;
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_002D6ED0(void* object, float key)
{
    FloatKeyScanOwner_text_002D55D0_10* receiver = static_cast<FloatKeyScanOwner_text_002D55D0_10*>(object);
    s16 count = receiver->count28;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == receiver->entries[index].key0c)
        {
            return 1;
        }
    }
    return 0;
}

void func_002D6F20(FieldWords002D6F20* object)
{
    object->words[0] = 0;
    object->words[1] = 0;
    object->words[2] = 0;
    object->words[3] = 0;
}

float func_002D6F40(const FieldFloatValueSequence28* object)
{
    if (object->count < 2)
    {
        return 0.0f;
    }
    s32 lastIndex = object->count - 1;
    const FieldFloatValueEntryC16* last = object->entries + lastIndex;
    return last->value - object->entries[0].value;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D6F90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D6FF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D7040);

void* func_002D70D0(const FieldSequenceState10* object)
{
    return object->unk04;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D70E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D7130);

void func_002D71E0(FieldSequenceState10* object)
{
    object->unk04 = 0;
    object->state.unk12_0_3 = 1;
    object->state.unk12_4_7 = 1;
    object->state.unk0a = 0;
    object->state.unk08 = 0;
    object->state.unk0c = -1;
    object->state.unk00 = 0;
    object->state.unk0e = -1;
    object->state.unk10 = -1;
    object->state.unk13_0 = 0;
    object->state.unk13_1 = 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D7270);

void func_002D7340(FieldSequenceState10* object, u8 mode)
{
    object->state.unk12_0_3 = mode;
    object->state.unk13_0 = object->state.unk12_0_3 == 4 || object->state.unk12_4_7 == 4;
}

void func_002D73A0(FieldSequenceState10* object, u8 mode)
{
    object->state.unk12_4_7 = mode;
    object->state.unk13_0 = object->state.unk12_0_3 == 4 || object->state.unk12_4_7 == 4;
}

s32 func_002D7400(const FieldSequenceState10* object)
{
    return object->state.unk00;
}

s16 func_002D7410(const FieldSequenceState10* object)
{
    return object->state.unk08;
}

float func_002D7420(void* object)
{
    return 0.0f;
}

/**
 * @brief Store the receiver's virtual float result in the supplied output.
 * @param object Receiver with the float callback at vtable offset 0x7C.
 * @param output Destination for the returned float.
 */
void func_002D7430(void* object, float* output)
{
    *output = ((FieldCallbackDispatch70*)object)->slot7c();
}

void* func_002D7460(const FieldPointerAt04* object)
{
    return object->unk04;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D7470);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D74C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D7570);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D75C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D76B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D7820);

void func_002D78D0(FieldSequenceState40* object)
{
    object->unk04 = 0;
    object->state.unk12_0_3 = 1;
    object->state.unk12_4_7 = 1;
    object->state.unk0a = 0;
    object->state.unk08 = 0;
    object->state.unk0c = -1;
    object->state.unk00 = 0;
    object->state.unk0e = -1;
    object->state.unk10 = -1;
    object->state.unk13_0 = 0;
    object->state.unk13_1 = 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D7960);

void func_002D79B0(FieldSequenceState40* object, u8 mode)
{
    object->state.unk12_0_3 = mode;
    object->state.unk13_0 = object->state.unk12_0_3 == 4 || object->state.unk12_4_7 == 4;
}

void func_002D7A10(FieldSequenceState40* object, u8 mode)
{
    object->state.unk12_4_7 = mode;
    object->state.unk13_0 = object->state.unk12_0_3 == 4 || object->state.unk12_4_7 == 4;
}

s32 func_002D7A70(const FieldSequenceState40* object)
{
    return object->state.unk00;
}

s16 func_002D7A80(const FieldSequenceState40* object)
{
    return object->state.unk08;
}

s32 func_002D7A90(void* object)
{
    return 0;
}

s32 func_002D7AA0(void* object)
{
    return 0;
}

s32 func_002D7AB0(void* object)
{
    return 0;
}

void func_002D7AC0(void* object)
{
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_002D7AD0(void* object, float key)
{
    FloatKeyScanOwner_text_002D55D0_30* receiver = static_cast<FloatKeyScanOwner_text_002D55D0_30*>(object);
    s16 count = receiver->count48;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == receiver->entries[index].key0c)
        {
            return 1;
        }
    }
    return 0;
}

void func_002D7B20(FieldWords002D7B20* object)
{
    object->words[0] = 0;
    object->words[1] = 0;
    object->words[2] = 0;
    object->words[3] = 0;
}

float func_002D7B40(const FieldFloatValueSequence48* object)
{
    if (object->count < 2)
    {
        return 0.0f;
    }
    s32 lastIndex = object->count - 1;
    const FieldFloatValueEntry48* last = object->entries + lastIndex;
    return last->value - object->entries[0].value;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D7B90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D7C00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D7C50);

void* func_002D7CF0(const FieldPointerAt04* object)
{
    return object->unk04;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D7D00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D7D50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D7E00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D7E50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D7EA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D7EF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D7F60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D7FD0);

void* func_002D80B0(void* object)
{
    return object;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D80C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D8130);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D81A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D8230);

float func_002D8290(const FieldFloatValueSequence18* object)
{
    if (object->count < 2)
    {
        return 0.0f;
    }
    s32 lastIndex = object->count - 1;
    const FieldFloatValueEntry8* last = object->entries + lastIndex;
    return last->value - object->entries[0].value;
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_002D82E0(void* object, float key)
{
    FloatKeyScanOwner_text_002D55D0_08* receiver = static_cast<FloatKeyScanOwner_text_002D55D0_08*>(object);
    s16 count = receiver->count18;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == receiver->entries[index].key00)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x70.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D8330(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot70();
}

void func_002D8360(void* object)
{
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x6C.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D8370(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot6c();
}

s32 func_002D83A0(void* object)
{
    return 0;
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x68.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D83B0(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot68();
}

s32 func_002D83E0(void* object)
{
    return 0;
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x64.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D83F0(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot64();
}

s32 func_002D8420(void* object)
{
    return 0;
}

void func_002D8430(FieldFloatSequenceState24* object, s32 count, FieldFloatValueEntry8* entries)
{
    object->flags23_1 = 1;
    object->entries = entries;
    object->count1a = count;
    object->count18 = count;
    const FieldFloatValueEntry8* last = object->entries + (count - 1);
    object->range14 = last->value - object->entries[0].value;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D8480);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x70.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D84F0(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot70();
}

void func_002D8520(void* object)
{
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x6C.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D8530(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot6c();
}

s32 func_002D8560(void* object)
{
    return 0;
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x68.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D8570(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot68();
}

s32 func_002D85A0(void* object)
{
    return 0;
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x64.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D85B0(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot64();
}

s32 func_002D85E0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D85F0);

void* func_002D86C0(void* object)
{
    return object;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D86D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D8740);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D87D0);

float func_002D8830(const FieldFloatValueSequence38* object)
{
    if (object->count < 2)
    {
        return 0.0f;
    }
    s32 lastIndex = object->count - 1;
    const FieldFloatValueEntry32* last = object->entries + lastIndex;
    return last->value - object->entries[0].value;
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_002D8880(void* object, float key)
{
    FloatKeyScanOwner_text_002D55D0_20* receiver = static_cast<FloatKeyScanOwner_text_002D55D0_20*>(object);
    s16 count = receiver->count38;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == receiver->entries[index].key00)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x70.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D88D0(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot70();
}

void func_002D8900(void* object)
{
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x6C.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D8910(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot6c();
}

s32 func_002D8940(void* object)
{
    return 0;
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x68.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D8950(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot68();
}

s32 func_002D8980(void* object)
{
    return 0;
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x64.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D8990(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot64();
}

s32 func_002D89C0(void* object)
{
    return 0;
}

void func_002D89D0(FieldFloatSequenceState44* object, s32 count, FieldFloatValueEntry32* entries)
{
    object->flags43_1 = 1;
    object->entries = entries;
    object->count3a = count;
    object->count38 = count;
    const FieldFloatValueEntry32* last = object->entries + (count - 1);
    object->range34 = last->value - object->entries[0].value;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D8A20);

void* func_002D8AF0(void* object)
{
    return object;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D8B00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D8B70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D8BE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D8C70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D8DB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D8E10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D8E90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D8F90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D9020);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D90B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D9110);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D9210);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D9270);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D92F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D93F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D9480);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D9520);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D9570);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D9900);

/** Set the low packed mode at 0x22 and record whether either mode equals four. */
void func_002D9960(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at22.lowMode = mode;
    receiver->at22.hasModeFour = receiver->at22.lowMode == 4 || receiver->at22.highMode == 4;
}

/** Set the low packed mode at 0x42 and record whether either mode equals four. */
void func_002D99C0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at42.lowMode = mode;
    receiver->at42.hasModeFour = receiver->at42.lowMode == 4 || receiver->at42.highMode == 4;
}

/** Set the low packed mode at 0x52 and record whether either mode equals four. */
void func_002D9A20(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at52.lowMode = mode;
    receiver->at52.hasModeFour = receiver->at52.lowMode == 4 || receiver->at52.highMode == 4;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D9A80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D9B00);

void func_002D9B80(void* object)
{
}

void func_002D9B90(void* object)
{
}

void func_002D9BA0(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D9BB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D9C40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D9D20);

/** Set the high packed mode at 0x52 and record whether either mode equals four. */
void func_002D9D70(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at52.highMode = mode;
    receiver->at52.hasModeFour = receiver->at52.lowMode == 4 || receiver->at52.highMode == 4;
}

s32 func_002D9DD0(const FieldSequenceState40* object)
{
    return object->state.unk00;
}

s16 func_002D9DE0(const FieldSequenceState40* object)
{
    return object->state.unk08;
}

s32 func_002D9DF0(void* object)
{
    return 0;
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x64.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D9E00(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot64();
}

s32 func_002D9E30(void* object)
{
    return 0;
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x68.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D9E40(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot68();
}

s32 func_002D9E70(void* object)
{
    return 0;
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x6C.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D9E80(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot6c();
}

void func_002D9EB0(void* object)
{
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x70.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D9EC0(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot70();
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_002D9EF0(void* object, float key)
{
    FloatKeyScanOwner_text_002D55D0_30* receiver = static_cast<FloatKeyScanOwner_text_002D55D0_30*>(object);
    s16 count = receiver->count48;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == receiver->entries[index].key00)
        {
            return 1;
        }
    }
    return 0;
}

void func_002D9F40(FieldWords002D9F40* object)
{
    object->words[0] = 0;
    object->words[1] = 0;
    object->words[2] = 0;
    object->words[3] = 0;
}

float func_002D9F60(const FieldFloatFirstSequence48* object)
{
    if (object->count < 2)
    {
        return 0.0f;
    }
    s32 lastIndex = object->count - 1;
    const FieldFloatFirstEntry48* last = object->entries + lastIndex;
    return last->value - object->entries[0].value;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002D9FB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DA020);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DA070);

void* func_002DA110(const FieldPointerAt04* object)
{
    return object->unk04;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DA120);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DA200);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DA360);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DA3F0);

/** Set the high packed mode at 0x42 and record whether either mode equals four. */
void func_002DA4C0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at42.highMode = mode;
    receiver->at42.hasModeFour = receiver->at42.lowMode == 4 || receiver->at42.highMode == 4;
}

u32 func_002DA520(const FieldWordAt30* object)
{
    return object->unk30;
}

s16 func_002DA530(const FieldSignedHalfAt38* object)
{
    return object->unk38;
}

s32 func_002DA540(void* object)
{
    return 0;
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x64.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002DA550(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot64();
}

s32 func_002DA580(void* object)
{
    return 0;
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x68.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002DA590(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot68();
}

s32 func_002DA5C0(void* object)
{
    return 0;
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x6C.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002DA5D0(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot6c();
}

void func_002DA600(void* object)
{
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x70.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002DA610(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot70();
}

void func_002DA640(FieldWords002DA640* object)
{
    object->words[0] = 0;
    object->words[1] = 0;
    object->words[2] = 0;
    object->words[3] = 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DA660);

void* func_002DA6B0(const FieldPointerAt04* object)
{
    return object->unk04;
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x64.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002DA6C0(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot64();
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x68.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002DA6F0(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot68();
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x6C.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002DA720(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot6c();
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x70.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002DA750(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot70();
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DA780);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DA810);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DA8E0);

/** Set the high packed mode at 0x22 and record whether either mode equals four. */
void func_002DA940(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at22.highMode = mode;
    receiver->at22.hasModeFour = receiver->at22.lowMode == 4 || receiver->at22.highMode == 4;
}

s32 func_002DA9A0(const FieldWordAt10* object)
{
    return object->unk10;
}

s16 func_002DA9B0(const FieldSignedHalfAt18* object)
{
    return object->unk18;
}

s32 func_002DA9C0(void* object)
{
    return 0;
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x64.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002DA9D0(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot64();
}

s32 func_002DAA00(void* object)
{
    return 0;
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x68.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002DAA10(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot68();
}

s32 func_002DAA40(void* object)
{
    return 0;
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x6C.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002DAA50(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot6c();
}

void func_002DAA80(void* object)
{
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x70.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002DAA90(void* object)
{
    ((FieldCallbackDispatch70*)object)->slot70();
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DAAC0);

void func_002DAB20(FieldWords002DAB20* object)
{
    object->words[0] = 0;
    object->words[1] = 0;
    object->words[2] = 0;
    object->words[3] = 0;
}

float func_002DAB40(const FieldSignedValueSequence18* object)
{
    if (object->count < 2)
    {
        return 0.0f;
    }
    s32 lastIndex = object->count - 1;
    const FieldSignedValueEntry8* last = object->entries + lastIndex;
    return (float)last->value - (float)object->entries[0].value;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DABA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DAC90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DACE0);

void* func_002DAD80(const FieldPointerAt04* object)
{
    return object->unk04;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DAD90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DAE20);

float func_002DAE80(const FieldFloatValueSequence38* object)
{
    if (object->count < 2)
    {
        return 0.0f;
    }
    s32 lastIndex = object->count - 1;
    const FieldFloatValueEntry32* last = object->entries + lastIndex;
    return last->value - object->entries[0].value;
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_002DAED0(void* object, float key)
{
    FloatKeyScanOwner_text_002D55D0_20* receiver = static_cast<FloatKeyScanOwner_text_002D55D0_20*>(object);
    s16 count = receiver->count38;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == receiver->entries[index].key00)
        {
            return 1;
        }
    }
    return 0;
}

void func_002DAF20(FieldFloatSequenceState44* object, s32 count, FieldFloatValueEntry32* entries)
{
    object->flags43_1 = 1;
    object->entries = entries;
    object->count3a = count;
    object->count38 = count;
    const FieldFloatValueEntry32* last = object->entries + (count - 1);
    object->range34 = last->value - object->entries[0].value;
}

void* func_002DAF70(void* object)
{
    return object;
}

void* func_002DAF80(void* object)
{
    return object;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DAF90);

s32 func_002DB010(void* object)
{
    return 3;
}

void func_002DB020(FieldWordAt28* object)
{
    object->unk28 = 0;
}

float func_002DB030(void* object)
{
    return 2500.0f;
}

s32 func_002DB050(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DB060);

void func_002DB250(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DB260);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DB6A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DB790);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DB7F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DB860);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DB8D0);

void func_002DB9D0(FieldPointerValueState2C* object, const u8* source, u32 value)
{
    object->unk2c = source;
    object->unk30 = value;
    if (*object->unk2c == 1)
    {
        object->unk34 = 1;
    }
    else
    {
        object->unk34 = 0;
    }
}

s32 func_002DBA10(void* object)
{
    return 0;
}

void func_002DBA20(void* object)
{
}

float func_002DBA30(void* object)
{
    return 100.0f;
}

void func_002DBA40(void* object)
{
}

void func_002DBA50(void* object)
{
}

void func_002DBA60(void* object)
{
}

void func_002DBA70(void* object)
{
}

void func_002DBA80(void* object)
{
}

void func_002DBA90(void* object)
{
}

s32 func_002DBAA0(void* object)
{
    return 0;
}

void func_002DBAB0(void* object)
{
}

void func_002DBAC0(void* object)
{
}

void func_002DBAD0(void* object)
{
}

s32 func_002DBAE0(void* object)
{
    return 0;
}

void func_002DBAF0(void* object)
{
}

void func_002DBB00(void* object)
{
}

void func_002DBB10(void* object)
{
}

void func_002DBB20(void* object)
{
}

void func_002DBB30(void* object)
{
}

s32 func_002DBB40(void* object)
{
    return 0;
}

void func_002DBB50(void* object)
{
}

s32 func_002DBB60(void* object)
{
    return 0;
}

void func_002DBB70(void* object)
{
}

float func_002DBB80(void* object)
{
    return 0.0f;
}

void func_002DBB90(void* object)
{
}

void func_002DBBA0(void* object)
{
}

s32 func_002DBBB0(void* object)
{
    return 0;
}

void func_002DBBC0(void* object)
{
}

s32 func_002DBBD0(void* object)
{
    return 0;
}

void func_002DBBE0(void* object)
{
}

float func_002DBBF0(void* object)
{
    return 0.0f;
}

void func_002DBC00(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DBC10);

FieldEntryA0* func_002DBC70(const FieldEntryArray14* object, s32 index)
{
    return &object->entries[index];
}

u8* func_002DBC90(const FieldIndexedStorageAt20* object, s32 row, s32 column)
{
    s32 index = row * (object->count - 1) + column;
    return object->data + (index << 6);
}

u32 func_002DBCB0(const FieldWordsAt0C10and1C* object)
{
    return object->unk1c;
}

u32 func_002DBCC0(const FieldWordsAt0C10and1C* object)
{
    return object->unk0c;
}

u32 func_002DBCD0(const FieldWordsAt0C10and1C* object)
{
    return object->unk10;
}

s32 func_002DBCE0(void* object)
{
    return 32;
}

s32 func_002DBCF0(const FieldWordAt14* object)
{
    return object->unk14 != 0;
}

void func_002DBD00(void* object, const void* source)
{
    u32* destinationWords = (u32*)object;
    const u32* sourceWords = (const u32*)source;
    destinationWords[3] = sourceWords[3];
    destinationWords[4] = sourceWords[4];
    ((FieldCallbackDispatch58*)object)->callback(destinationWords[3], destinationWords[4]);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DBD40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DC2B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DC2F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DC370);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DC450);

float func_002DCAD0(void* object)
{
    return 1.0f;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DCAE0);

/**
 * @brief Initialize the receiver, then pass it to the shared owner.
 * @param object Receiver to initialize and process.
 */
void func_002DCB80(void* object)
{
    func_4D7EB0(object);
    func_121E80(D_001B6620, object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DCBB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DD1B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DD220);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DD3F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DD8D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DDB60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DDC00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DDC90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DDF90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DE220);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DE6B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DE940);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DE9B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DEB20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DECB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DED70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DEE00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DEF10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DEFB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DF000);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DF3D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DF440);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DF650);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002DF6B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E0B00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E0B90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E0C30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E0DD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E0E50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E0E90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E0EF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E0F50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E0F90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E1080);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E1180);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E1250);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E1730);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E1830);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E1C10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E2BA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E2C50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E2D00);

void func_002E2DB0(FieldFloatState4C* object)
{
    if (object->unk48 <= 0.0f)
    {
        return;
    }

    object->unk48 -= D_001B66B4;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E2DE0);

s32 func_002E2E60(void* object)
{
    return 3;
}

void func_002E2E70(FieldWordAt28* object)
{
    object->unk28 = 0;
}

void func_002E2E80(void* object)
{
}

float func_002E2E90(void* object)
{
    return 2500.0f;
}

s32 func_002E2EB0(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E2EC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E2F20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E2F90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E3000);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E30E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E3180);

s32 func_002E3220(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E3230);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E3340);

void func_002E3950(FieldPointerValueState2C* object, const u8* source, u32 value)
{
    object->unk2c = source;
    object->unk30 = value;
    if (*object->unk2c == 1)
    {
        object->unk34 = 1;
    }
    else
    {
        object->unk34 = 0;
    }
}

s32 func_002E3990(void* object)
{
    return 0;
}

void func_002E39A0(void* object)
{
}

float func_002E39B0(void* object)
{
    return 100.0f;
}

void func_002E39C0(void* object)
{
}

void func_002E39D0(void* object)
{
}

void func_002E39E0(void* object)
{
}

void func_002E39F0(void* object)
{
}

void func_002E3A00(void* object)
{
}

void func_002E3A10(void* object)
{
}

s32 func_002E3A20(void* object)
{
    return 0;
}

void func_002E3A30(void* object)
{
}

void func_002E3A40(void* object)
{
}

void func_002E3A50(void* object)
{
}

s32 func_002E3A60(void* object)
{
    return 0;
}

void func_002E3A70(void* object)
{
}

void func_002E3A80(void* object)
{
}

void func_002E3A90(void* object)
{
}

void func_002E3AA0(void* object)
{
}

void func_002E3AB0(void* object)
{
}

s32 func_002E3AC0(void* object)
{
    return 0;
}

void func_002E3AD0(void* object)
{
}

s32 func_002E3AE0(void* object)
{
    return 0;
}

void func_002E3AF0(void* object)
{
}

float func_002E3B00(void* object)
{
    return 0.0f;
}

void func_002E3B10(void* object)
{
}

void func_002E3B20(void* object)
{
}

s32 func_002E3B30(void* object)
{
    return 0;
}

void func_002E3B40(void* object)
{
}

s32 func_002E3B50(void* object)
{
    return 0;
}

void func_002E3B60(void* object)
{
}

float func_002E3B70(void* object)
{
    return 0.0f;
}

void func_002E3B80(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E3B90);

FieldEntry40* func_002E3BF0(const FieldEntryArray40At14* object, s32 index)
{
    return &object->entries[index];
}

u8* func_002E3C00(const FieldIndexedStorageAt20* object, s32 row, s32 column)
{
    s32 index = row * (object->count - 1) + column;
    return object->data + (index << 6);
}

u32 func_002E3C20(const FieldWordsAt0C10and1C* object)
{
    return object->unk1c;
}

u32 func_002E3C30(const FieldWordsAt0C10and1C* object)
{
    return object->unk0c;
}

u32 func_002E3C40(const FieldWordsAt0C10and1C* object)
{
    return object->unk10;
}

s32 func_002E3C50(void* object)
{
    return 1;
}

s32 func_002E3C60(const FieldWordAt14* object)
{
    return object->unk14 != 0;
}

void func_002E3C70(void* object, const void* source)
{
    u32* destinationWords = (u32*)object;
    const u32* sourceWords = (const u32*)source;
    destinationWords[3] = sourceWords[3];
    destinationWords[4] = sourceWords[4];
    ((FieldCallbackDispatch58*)object)->callback(destinationWords[3], destinationWords[4]);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E3CB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E4210);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E4250);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E42D0);

float func_002E43B0(void* object)
{
    return 1.0f;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E43C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E43D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E4660);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E4930);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E4A00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E4ED0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E5190);

s32 func_002E5260(FieldConditionalFloat14* object)
{
    if ((object->unk5f4 & 1) != 0)
    {
        object->unk14 = 1.0f;
        return 0;
    }
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E5290);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002D55D0", func_002E5310);
