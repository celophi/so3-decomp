#include "include_asm.h"
#include "overlays/1070-00/text_00234310.h"
#include "overlays/1070-00/text_00284BF0.h"

extern "C" void func_00234930(void* object);
extern "C" FieldContextRef* D_001B64B0;
extern "C" void* D_001B6620;
extern "C" void func_002CE4F0(FieldContext* context, float value);
extern "C" void func_4D7EB0(void* object);
extern "C" void func_00203B90(void* object);
extern "C" void func_002656C0(void* object);
extern "C" void func_002CE6C0(void* context, float value);
extern "C" u32 func_00248B10(void* object, u32 first, u32 second);
extern "C" void func_001E30E0(void* object, float value, s32 first, s32 second);
extern "C" void func_121E80(void* owner, void* object);
extern "C" void func_123020(void* owner, void* object);
extern "C" void func_42C4B0(void* object);

/** Partial receiver with a float pointer at offset 0x540. */
struct FieldFloatSource540
{
    u8 unk00[0x540];
    float* unk540;
};

/** Partial receiver with an optional child pointer at offset 0x90. */
struct FieldOptionalChild90
{
    u8 unk00[0x90];
    void* unk90;
};

/** Partial callback interface with a method at vtable offset 0x10. */
class FieldCallbackDispatch10Local
{
public:
    virtual void slot08();
    virtual void slot0c();
    virtual void callback();
};

/** Partial receiver with an optional callback object at offset 0x44. */
struct FieldOptionalCallback44
{
    u8 unk00[0x44];
    void* callback;
};

/** Partial receiver with an optional child pointer at offset 0x5BC. */
struct FieldOptionalChild5BC
{
    u8 unk00[0x5BC];
    void* child;
};

/** Child object whose callback interface begins at offset 0x20. */
struct FieldChildCallbackAt20
{
    u8 unk00[0x20];
    FieldCallbackDispatch10Local callback;
};

/** Partial receiver with a pointer to the two words passed by func_0023F900. */
struct FieldSourcePair540
{
    u8 unk00[0x424];
    u32 unk424;
    u8 unk428[0x118];
    u32* unk540;
};

/** Partial shared state with the flag byte updated by func_00238FA0. */
struct FieldSharedFlag50
{
    u8 unk00[0x50];
    u8 unk50;
};

/** Shared state fields populated by the word-pair callbacks. */
struct FieldSharedPair34
{
    u8 unk00[0x34];
    u32 unk34;
    u32 unk38;
    u32 unk3C;
    u32 unk40;
};

/** Partial receiver with a flag and owner pointer used by func_0023D5F0. */
struct FieldOptionalOwnerC4
{
    u8 unk00[0x64];
    u8 unk64;
    u8 unk65[0x5F];
    void* owner;
};

/** Partial receiver with the table index byte at offset 0xF1. */
struct FieldSlotIndexF1
{
    u8 unk00[0xF1];
    u8 unkf1;
};

/** Partial context containing the float updated by func_00238F60. */
struct FieldContextFloatA0
{
    u8 unk00[0xA0];
    float unkA0;
};

/** Partial receiver with the word cleared by func_00243AE0. */
struct FieldWordState250
{
    u8 unk00[0x250];
    u32 unk250;
};

extern "C" void func_4967C0(void);
extern "C" void func_4EABF0(void);

/** Minimal observed prefix containing three independent flags at offset 0x1059. */
struct FieldByteFlags1059
{
    u8 unk00[0x1059];
    u8 unk1059_0 : 1;
    u8 unk1059_1 : 1;
    u8 unk1059_2 : 1;
    u8 unk1059_3_7 : 5;
};

/** Minimal observed prefix containing flag bit one at offset 0x146C. */
struct FieldSetBit146C
{
    u8 unk00[0x146C];
    u8 unk146c_0 : 1;
    u8 unk146c_1 : 1;
    u8 unk146c_2_7 : 6;
};

/** Minimal observed prefix containing flag bit one at offset 0x103C. */
struct FieldSetBit103C
{
    u8 unk00[0x103C];
    u8 unk103c_0 : 1;
    u8 unk103c_1 : 1;
    u8 unk103c_2_7 : 6;
};

/** Partial receiver containing observed word bits and a flag byte. */
struct FieldFlagWord29
{
    u8 unk00[0x1C];
    u32 unk1c;
    u8 unk20[9];
    u8 unk29_0 : 1;
    u8 unk29_1_7 : 7;
};

/** Minimal observed prefix containing the two byte fields copied here. */
struct FieldByteCopyF0
{
    u8 unk00[0x60];
    u8 unk60;
    u8 unk61[0x8F];
    u8 unkf0;
};

/** Minimal observed prefix containing the two byte fields copied here. */
struct FieldByteCopy94
{
    u8 unk00[0x60];
    u8 unk60;
    u8 unk61[0x33];
    u8 unk94;
};

/** Minimal observed prefix containing the word written here. */
struct FieldWordWrite424
{
    u8 unk00[0x424];
    u32 unk424;
};

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00234310);

/** Initialize the receiver, then process it through the shared owner. */
extern "C" void func_002343C0(void* object)
{
    func_4D7EB0(object);
    func_121E80(D_001B6620, object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_002343F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_002346B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00234930);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00234B10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_002352D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00235350);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_002354D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_002356D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00235760);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00235940);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00235BD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00235D20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00235EA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00236070);

void func_002362D0(void* receiver)
{
    FieldOptionalChild90* object = (FieldOptionalChild90*)receiver;
    if (object->unk90 != 0)
    {
        func_00234930(object->unk90);
    }
}

void func_00236300(void* receiver)
{
    FieldOptionalChild90* object = (FieldOptionalChild90*)receiver;
    if (object->unk90 != 0)
    {
        ((FieldCallbackDispatch10Local*)object->unk90)->callback();
        object->unk90 = 0;
    }
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00236340);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00236410);

void func_002364C0(FieldOptionalColor44* object)
{
    FieldColorState30* state = object->unk44;
    if (state != 0)
    {
        state->unk34 = (state->unk30->unk1c & 1) != 0 ? 0xFF008000 : 0xFF0040E0;
    }
}

void func_00236500(void* receiver)
{
    FieldOptionalCallback44* object = (FieldOptionalCallback44*)receiver;
    if (object->callback != 0)
    {
        ((FieldCallbackDispatch10Local*)object->callback)->callback();
        object->callback = 0;
    }
}

/** Initialize the receiver, then process it through the shared owner. */
extern "C" void func_00236540(void* object)
{
    func_4D7EB0(object);
    func_121E80(D_001B6620, object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00236570);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00236620);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_002366D0);

void func_00236740(void* object)
{
}

void func_00236750(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00236760);

void func_002367C0(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_002367D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00236B20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00236CB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00236D70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00236E10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00237120);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_002373D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00237650);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00237800);

/** Initialize the receiver, then process it through the shared owner. */
extern "C" void func_002378C0(void* object)
{
    func_4D7EB0(object);
    func_121E80(D_001B6620, object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_002378F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_002379B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00237A70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00237B30);

s32 func_00237BE0(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00237BF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00237C40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00237D00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00237D60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00237DC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00237E40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00237EB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00237F00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00237F70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00237FF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00238110);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00238210);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_002382B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00238380);

/** Initialize the shared context's float transition state. */
s32 func_00238390(void)
{
    func_001E30E0(D_001B64B0->context->unk44, 8.0f, 12, 0);
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_002383D0);

void func_00238420(void* receiver)
{
    FieldOptionalChild5BC* object = (FieldOptionalChild5BC*)receiver;
    if (object->child != 0)
    {
        ((FieldChildCallbackAt20*)object->child)->callback.callback();
        object->child = 0;
    }
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00238460);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00238670);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_002386E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00238740);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00238840);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00238850);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_002388F0);

/**
 * @brief Copy the source pair into shared state offsets 0x40 and 0x3C.
 * @param object Receiver whose cursor points to the source pair.
 * @return One after updating the shared state.
 */
extern "C" s32 func_00238930(const FieldSourcePair540* object)
{
    u32 first = object->unk540[0];
    u32 second = object->unk540[1];
    FieldSharedPair34* state = (FieldSharedPair34*)D_001B64B0->context->unk44;
    state->unk40 = first;
    state->unk3C = second;
    return 1;
}

/**
 * @brief Copy the source pair into shared state offsets 0x38 and 0x34.
 * @param object Receiver whose cursor points to the source pair.
 * @return One after updating the shared state.
 */
extern "C" s32 func_00238960(const FieldSourcePair540* object)
{
    u32 first = object->unk540[0];
    u32 second = object->unk540[1];
    FieldSharedPair34* state = (FieldSharedPair34*)D_001B64B0->context->unk44;
    state->unk38 = first;
    state->unk34 = second;
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00238990);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00238A40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00238B10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00238B70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00238CB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00238E70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00238EB0);

/**
 * @brief Update the shared field state using the receiver's float value.
 * @param object Receiver containing a pointer to the float at offset 0x540.
 * @return One after the update.
 */
s32 func_00238F30(const void* object)
{
    const FieldFloatSource540* state = (const FieldFloatSource540*)object;
    func_002CE4F0(D_001B64B0->context, *state->unk540);
    return 1;
}

/** Store the receiver's float in shared context and refresh the helper state. */
s32 func_00238F60(void* receiver)
{
    FieldFloatSource540* source = (FieldFloatSource540*)receiver;
    FieldContextFloatA0* context = (FieldContextFloatA0*)D_001B64B0->context;
    context->unkA0 = *source->unk540;
    func_002CE6C0(D_001B64B0->context, 0.0f);
    return 1;
}

/** Copy the source low bit into the shared state flag. */
s32 func_00238FA0(void* receiver)
{
    FieldSourcePair540* source = (FieldSourcePair540*)receiver;
    FieldSharedFlag50* state = (FieldSharedFlag50*)D_001B64B0->context->unk44;
    state->unk50 = (state->unk50 & ~1) | ((source->unk540[0] & 1) != 0);
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00238FE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00239390);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00239430);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_002394D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00239630);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00239770);

/** Partial callback interface with a two-argument method at vtable offset 0x64. */
class FieldCallbackDispatch64WithValues
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
    virtual void slot58();
    virtual void slot5c();
    virtual void slot60();
    virtual void dispatch(u32 first, u32 second);
};

/** Partial context containing the callback receiver at offset 0x38. */
struct FieldCallbackContext38
{
    u8 unk00[0x38];
    FieldCallbackDispatch64WithValues* callback;
};

/** Values forwarded to the shared callback by func_00239840. */
struct FieldCallbackValues08
{
    u8 unk00[8];
    u32 first;
    u32 second;
};

/**
 * @brief Dispatch two receiver values through the shared field callback.
 * @param object Receiver containing the two values at offsets 0x08 and 0x0C.
 */
extern "C" void func_00239840(const FieldCallbackValues08* object)
{
    FieldCallbackContext38* context =
        (FieldCallbackContext38*)D_001B64B0->context;
    context->callback->dispatch(object->first, object->second);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00239880);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00239970);

void func_002399E0(void* object)
{
    FieldSetBit146C* state = (FieldSetBit146C*)object;

    state->unk146c_1 = 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00239A00);

s32 func_00239AD0(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00239AE0);

void func_00239B90(void)
{
    func_4967C0();
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00239BB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00239D10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00239E30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00239E90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00239ED0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00239F10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00239F80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023A190);

void func_0023A2D0(FieldConditionalState103C* object)
{
    if (!object->unk103c_2)
    {
        object->unk103c_2 = 1;
        if (object->unkcb != 0 && object->unk100c >= 3)
        {
            object->unkabd = 0;
            object->unk100c = 7;
            object->unk1008 &= ~0x80000;
            object->unk1008 |= 0x80000000;
        }
    }
}

void func_0023A350(void)
{
    func_4967C0();
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023A370);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023A6E0);

void func_0023A830(FieldConditionalState103C* object)
{
    object->unk103c_1 = 1;
    ((FieldCallbackDispatch10Local*)((u8*)object + 0x20))->callback();
}

void func_0023A870(void* object)
{
    FieldByteFlags1059* state = (FieldByteFlags1059*)object;

    state->unk1059_2 = 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023A890);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023AA90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023AC00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023AC50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023B0F0);

s32 func_0023B250(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023B260);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023B300);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023B980);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023BA10);

s32 func_0023BA60(void* object)
{
    return 13;
}

void func_0023BA70(void* object)
{
    FieldSetBit103C* state = (FieldSetBit103C*)object;

    state->unk103c_1 = 1;
}

void func_0023BA90(void* object)
{
    FieldByteFlags1059* state = (FieldByteFlags1059*)object;

    state->unk1059_0 = 1;
}

void func_0023BAB0(void* object)
{
    FieldByteFlags1059* state = (FieldByteFlags1059*)object;

    state->unk1059_1 = 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023BAD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023BAE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023BAF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023BB00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023BB10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023BB20);

/** Initialize the linked receiver and clear its observed state bit. */
void func_0023BB30(FieldConditionalLinkA0* object)
{
    func_00203B90(object);
    object->unk70 &= ~0x10;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023BB70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023BC00);

void func_0023BC60(FieldConditionalVectorState* object)
{
    object->unk90 = object->unk10;
    if (object->unk70 & 0x10)
    {
        object->unka8 = object->unka4;
    }
    else
    {
        object->unka8 = -1;
    }
}

void func_0023BCA0(FieldConditionalLinkA0* object, void* target)
{
    if ((object->unk70 & 0x10) && object->unka0 == target)
    {
        object->unka0 = 0;
    }
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023BCD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023BD30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023BDA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023BE50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023BEA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023BF60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023C010);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023C230);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023C410);

s32 func_0023C4E0(void* object)
{
    return 3;
}

void func_0023C4F0(void* object)
{
    FieldByteCopyF0* state = (FieldByteCopyF0*)object;

    state->unk60 = state->unkf0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023C500);

void func_0023C5D0(void)
{
    func_4EABF0();
}

/**
 * @brief Clear the context's observed receiver pointer when it matches object.
 * @param object Receiver to compare with the pointer at context offset 0x5B8.
 */
extern "C" void func_0023C5F0(void* object)
{
    FieldContext38* state = D_001B64B0->context->unk38;
    if (object == state->unk5b8)
    {
        state->unk5b8 = 0;
    }
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023C620);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023C790);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023CDB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023D190);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023D2F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023D3A0);

bool func_0023D480(const FieldSlotObject* object)
{
    if ((object->unkf3 == 1 || object->unkf3 == 2) && object->unkf2 == 0)
    {
        return true;
    }
    if (!(object->unka4 < object->unka8))
    {
        return false;
    }
    else
    {
        return true;
    }
}

void func_0023D4E0(void)
{
    func_4EABF0();
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023D500);

/**
 * @brief Set the receiver flag and forward its optional adjusted pointer.
 * @param object Receiver containing the flag and helper owner fields.
 */
extern "C" void func_0023D5F0(FieldOptionalOwnerC4* object)
{
    object->unk64 = 1;
    void* adjusted = object;
    if (object != 0)
    {
        adjusted = (u8*)adjusted + 0x90;
    }
    func_123020(object->owner, adjusted);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023D630);

/** Clear the indexed context slot when it still points to this receiver. */
void func_0023DDC0(void* object)
{
    FieldSlotIndexF1* receiver = (FieldSlotIndexF1*)object;
    FieldContext38* state = D_001B64B0->context->unk38;
    u8 index = receiver->unkf1;
    if (object == state->unk598[index])
    {
        state->unk598[index] = 0;
    }
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023DE00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023E0C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023E220);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023E2B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023E380);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023E410);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023E560);

void func_0023E5D0(void* object)
{
    FieldByteCopy94* state = (FieldByteCopy94*)object;

    state->unk60 = state->unk94;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023E5E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023E5F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023E600);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023E610);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023E620);

s32 func_0023E800(void)
{
    void* object = D_001B64B0->context->unke0;
    if (object != 0)
    {
        void* target = *(void**)((u8*)object + 0x78);
        if (target != 0)
        {
            func_42C4B0(target);
        }
    }
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023E840);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023EA50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023EB50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023EC10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023ECC0);

s32 func_0023ED60(void* object)
{
    FieldWordWrite424* state = (FieldWordWrite424*)object;

    state->unk424 = 0;
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023ED70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023EE00);

/** Build and store the receiver's word from its source pair. */
s32 func_0023F900(void* receiver)
{
    FieldSourcePair540* object = (FieldSourcePair540*)receiver;
    u32 first = object->unk540[0];
    u32 second = object->unk540[1];
    object->unk424 = func_00248B10(receiver, first, second);
    return 1;
}

s32 func_0023F940(void* object)
{
    FieldWordWrite424* state = (FieldWordWrite424*)object;

    state->unk424 = 1;
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_0023F950);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00242110);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00242160);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_002422E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_002423B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_002426C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00242720);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00242B00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00242E80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00242F30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_002431C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00243270);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_002433D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00243460);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00243550);

/** Initialize the receiver, then process it through the shared owner. */
extern "C" void func_002435F0(void* object)
{
    func_4D7EB0(object);
    func_121E80(D_001B6620, object);
}

s32 func_00243620(void* object)
{
    return 9;
}

void func_00243630(void* object, u32 value)
{
    FieldFlagWord29* state = (FieldFlagWord29*)object;

    state->unk29_0 = 1;
    state->unk1c = value;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00243650);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00243870);

/** Reset the receiver's word, initialize it, then process it through the shared owner. */
void func_00243AE0(void* object)
{
    FieldWordState250* state = (FieldWordState250*)object;
    func_002656C0(object);
    state->unk250 = 0;
    func_4D7EB0(object);
    func_121E80(D_001B6620, object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00243B20);

s32 func_00243B30(void* object)
{
    return 1;
}

s32 func_00243B40(void* object)
{
    return 1;
}

s32 func_00243B50(void* object)
{
    return 1;
}

s32 func_00243B60(void* object)
{
    return 1;
}

s32 func_00243B70(void* object)
{
    return 1;
}

s32 func_00243B80(void* object)
{
    return 1;
}

s32 func_00243B90(void* object)
{
    return 1;
}

s32 func_00243BA0(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00243BB0);

/** Initialize the receiver, then process it through the shared owner. */
extern "C" void func_00243C40(void* object)
{
    func_4D7EB0(object);
    func_121E80(D_001B6620, object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00243C70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_00243FC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00234310", func_002441C0);

void func_00244220(FieldFlagState4C0* object, u32 value)
{
    object->unk4c0_0 = (value & 1) != 0;
}

s32 func_00244240(void* object)
{
    return 1;
}

s32 func_00244250(void* object)
{
    return 1;
}

s32 func_00244260(void* object)
{
    return 1;
}

s32 func_00244270(void* object)
{
    return 1;
}

s32 func_00244280(void* object)
{
    return 1;
}

s32 func_00244290(void* object)
{
    return 1;
}

s32 func_002442A0(void* object)
{
    return 1;
}

s32 func_002442B0(void* object)
{
    return 1;
}

s32 func_002442C0(void* object)
{
    return 1;
}

s32 func_002442D0(void* object)
{
    return 1;
}

s32 func_002442E0(void* object)
{
    return 1;
}

s32 func_002442F0(void* object)
{
    return 1;
}

s32 func_00244300(void* object)
{
    return 1;
}
