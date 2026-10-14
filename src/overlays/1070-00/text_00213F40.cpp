#include "include_asm.h"
#include "overlays/1070-00/text_00202FB0.h"
#include "overlays/1070-00/text_00213F40.h"

extern "C" void func_43AC40(void* object);
extern "C" void func_459DB0(void* object);
extern "C" void func_459960(void* object);
extern "C" void func_4781A0(void* object);
extern "C" void func_0027D300(void* object, u32 value, u8 old_flags);
extern "C" void* D_001B6620;
extern "C" u8 D_17B8A0[];
extern "C" void func_121E80(void* owner, void* object);

/** Partial callback interface with a virtual method at offset 0x54. */
class FieldCallbackDispatch54
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
    virtual void callback();
};

/** Partial callback interface with a method at vtable offset 0x10. */
class FieldCallbackDispatch10
{
public:
    virtual void slot08();
    virtual void slot0c();
    virtual void callback();
};

/** Partial callback interface with a three-output method at offset 0x34. */
class FieldCallbackOutputs34
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
    virtual void callback(float value, u32* first, u32* second, u32* third);
};

/** Partial receiver with a float at 0x78 and a word at 0x0C. */
struct FieldFloatWordState78
{
    u8 unk00[0x0C];
    u32 unk0c;
    u8 unk10[0x68];
    float unk78;
};

/** Partial receiver initialized by func_00215CC0. */
struct FieldInitializedState3C
{
    void* vtable;
    u8 unk04[0x38];
    u8 unk3c;
};


INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00213F40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00214030);

s32 func_002140E0(const FieldCheckedState00* object)
{
    s32 check = object->unk10c ^ (object->unk0a ^ (object->unk06 + object->unk08));
    if (object->unkec != check)
    {
        return 0;
    }
    return object->unk0a ^ 0x7E93;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00214120);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00214150);

s32 func_00214200(const FieldCheckedState00* object)
{
    s32 check = object->unk10c ^ (object->unk04 ^ (object->unk00 + object->unk02));
    if (object->unke8 != check)
    {
        return 0;
    }
    return object->unk04 ^ 0x7E93;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00214240);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00214270);

s32 func_00214320(const FieldCheckedState7C* object)
{
    s32 check = object->unka8 ^ (object->unk80 ^ (object->unk7c + object->unk7e));
    if (object->unkac != check)
    {
        return 0;
    }
    return object->unk80 ^ 0x7E93;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00214360);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00214390);

s32 func_00214490(const FieldCheckedState7C* object)
{
    u32 check = object->unka8 ^ (object->unk60 ^ (object->unk58 + object->unk5c));
    if (object->unka0 != check)
    {
        return 0;
    }
    return object->unk6c ^ 0x7DE3F7E3;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002144E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00214550);

s32 func_00214650(const FieldCheckedState7C* object)
{
    u32 check = object->unka8 ^ (object->unk60 ^ (object->unk58 + object->unk5c));
    if (object->unka0 != check)
    {
        return 0;
    }
    return object->unk60 ^ 0x7DE3F7E3;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00214690);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00214700);

s32 func_002148D0(const FieldCheckedState7C* object)
{
    u32 check = object->unka8 ^ (object->unk54 ^ (object->unk4c + object->unk50));
    if (object->unk9c != check)
    {
        return 0;
    }
    return object->unk50 ^ 0x7DE3F7E3;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00214910);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00214980);

s32 func_00214AA0(const FieldCheckedState7C* object)
{
    u32 check = object->unka8 ^ (object->unk48 ^ (object->unk40 + object->unk44));
    if (object->unk98 != check)
    {
        return 0;
    }
    return object->unk48 ^ 0x7DE3F7E3;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00214AE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00214B70);

s32 func_00214C70(const FieldCheckedState7C* object)
{
    u32 check = object->unka8 ^ (object->unk3c ^ (object->unk34 + object->unk38));
    if (object->unk94 != check)
    {
        return 0;
    }
    return object->unk3c ^ 0x7DE3F7E3;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00214CB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00214D30);

float func_00214DA0(const FieldFloatState30* object)
{
    return 0.0625f * object->unk30;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00214DC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00214E00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00215030);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002150D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00215150);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002151D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00215400);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002154A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00215520);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002155A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002155D0);

void func_002156B0(void* object)
{
    func_43AC40((u8*)object + 0x20);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002156D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002157E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00215840);

/** Initialize the receiver's table pointer and state byte after its helper. */
void* func_00215CC0(void* object)
{
    FieldInitializedState3C* state = (FieldInitializedState3C*)object;
    func_4781A0(object);
    state->vtable = D_17B8A0;
    state->unk3c = 13;
    return object;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00215D00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00215DE0);

void func_00215EB0(void* object)
{
}

s32 func_00215EC0(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00215ED0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00215EE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00215EF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00215F00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00215F10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00215F20);

s32 func_00215FE0(void* object)
{
    return 3;
}

void func_00215FF0(void* object)
{
    func_4D7EB0(object);
    func_121E80(D_001B6620, object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00216020);

void func_00216090(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002160A0);

void func_00216100(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00216110);

void func_00216180(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00216190);

void func_002161F0(FieldFlagAt1C* object)
{
    object->unk1c_0 = 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00216210);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002162A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002162B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002166F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00216820);

void func_00216870(void* object)
{
}

void func_00216880(void* object)
{
}

s32 func_00216890(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002168A0);

s32 func_00216910(void* object)
{
    return 300;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00216920);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002169B0);

void func_00216A20(void* object)
{
    func_459DB0((u8*)object + 0x5A4);
    func_459960(object);
}

void func_00216A50(FieldFlagMirrorAt20* object)
{
    object->unk20_2 = 0;
    object->unk20_0 = object->unk20_1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00216A90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00216B90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00216BD0);

s32 func_00216C30(void* object)
{
    return -1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00216C40);

void func_00216CA0(void* object)
{
}

void func_00216CB0(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00216CC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00216D00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00216D70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00216DF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00216E60);

void func_00216F00(void* object)
{
    func_4D7EB0(object);
    func_121E80(D_001B6620, object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00216F30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002170C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00217190);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002171F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00217350);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002175E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002178A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002178F0);

s32 func_002179B0(const FieldKeyList18* object, s32 key)
{
    const FieldKeyNode6E* node = &object->sentinel;
    for (;;)
    {
        node = node->next;
        if (&object->sentinel == node)
        {
            break;
        }
        if (node->key6e == (u16)key)
        {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00217A00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00217AE0);

void* func_00217CC0(void* object)
{
    return object;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00217CD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00217E80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00217FC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00218150);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00218310);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00218470);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002186E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00218880);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00218910);

void func_00218AE0(FieldWordTriplet14* object, u32 value18, u32 value14, u32 value1c)
{
    object->unk14 = value14;
    object->unk18 = value18;
    object->unk1c = value1c;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00218AF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00218D30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00218DB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00218EC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00218F30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00218FC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00219050);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002190E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00219140);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00219200);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002192A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00219340);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002193E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00219540);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00219550);

struct FieldFlagAt69F
{
    u8 pad00[0x69F];
    u8 unk69f_0 : 1;
    u8 unk69f_1 : 1;
    u8 unk69f_2 : 1;
    u8 unk69f_3 : 5;
};

/**
 * @brief Set bit 2 at receiver offset 0x69F, then pass the old byte to the helper.
 * @param object Receiver whose flag byte is updated.
 * @param value Second value forwarded to the helper.
 */
extern "C" void func_00219560(FieldFlagAt69F* object, u32 value)
{
    u8 old_flags = *(u8*)((u8*)object + 0x69F);
    object->unk69f_2 = 1;
    func_0027D300(object, value, old_flags);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00219590);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00219630);

void func_00219670(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00219680);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002196E0);

struct FieldVectorState19810
{
    u8 pad00[0x20];
    unsigned __int128 value20;
    u8 pad30[0x620];
    unsigned __int128 value650;
    u8 pad660[0x20];
    float value680;
    u8 pad684[4];
    float value688;
    float value68C;
};

struct FieldFloatState50
{
    u8 pad00[0x50];
    float value50;
};

void func_00219810(void* object, float x, float y, float z)
{
    FieldVectorState19810* state = (FieldVectorState19810*)object;
    state->value650 = state->value20;
    state->value680 = x;
    state->value688 = y;
    state->value68C = z;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00219830);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00219940);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021A2D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021A3D0);

void* func_0021A460(void* object)
{
    return object;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021A470);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021A590);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021A630);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021A6B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021A760);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021A7F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021A880);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x54.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_0021A930(void* object)
{
    ((FieldCallbackDispatch54*)object)->callback();
}

s32 func_0021A960(void* object)
{
    return 12;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021A970);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021A9D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021AA70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021AB20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021AC50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021AD90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021ADA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021ADB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021AE40);

/**
 * @brief Return the word predicate when the float is nonpositive, otherwise one.
 * @param object Receiver with the word at 0x0C and float at 0x78.
 * @return The selected zero-or-one result.
 */
s32 func_0021AF10(const void* receiver)
{
    const FieldFloatWordState78* object = (const FieldFloatWordState78*)receiver;
    if (object->unk78 > 0.0f)
    {
        return 1;
    }
    return object->unk0c != 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021AF40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021AFD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021B060);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021B130);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021B180);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021B290);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021B490);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021B940);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021BBB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021BC00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021BFC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021C200);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021C310);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021C7B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021CA40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021CB60);

void func_0021CBD0(void* object)
{
    FieldByteFlags34* state = (FieldByteFlags34*)object;
    state->unk34_0 = 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021CBF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021CCC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021CDA0);

/**
 * @brief Detach the receiver, then process it with the shared owner.
 * @param object Receiver passed to both helpers.
 */
extern "C" void func_0021CDB0(void* object)
{
    func_4D7EB0(object);
    func_121E80(D_001B6620, object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021CDE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021CEC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021D280);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021D3A0);

void* func_0021D710(void* object)
{
    return object;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021D720);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021DBD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021DE30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021DF40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021E020);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021E2A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021E300);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021E580);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021E630);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021E750);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021E880);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021E9C0);

FieldTraversalRecord* func_0021EC30(FieldTraversalRecord* record)
{
    return record + 1;
}

s32 func_0021EC40(const FieldTraversalRecord* record)
{
    return (record->unk0a & 0x20) != 0;
}

FieldTraversalRecord* func_0021EC50(const FieldTraversalRecord* record)
{
    return record->children;
}

s16 func_0021EC60(const FieldTraversalRecord* record)
{
    return record->unk0e;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021EC70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021EE10);

/**
 * @brief Detach the receiver, then process it through the shared owner.
 * @param object Receiver to detach and process.
 */
extern "C" void func_0021EEE0(void* object)
{
    func_4D7EB0(object);
    func_121E80(D_001B6620, object);
}

void func_0021EF10(FieldValueOwner34* object, s32 value)
{
    FieldValueState100* target = object->unk34;
    if (target != 0)
    {
        target->unk100 = value;
        target->unk40 = 1;
    }
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_0021EF30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002207D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00220870);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00220900);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00220A70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00221110);

s32 func_00221620(void* object)
{
    return 3;
}

/**
 * @brief Detach the receiver, then process it through the shared owner.
 * @param object Receiver to detach and process.
 */
void func_00221630(void* object)
{
    func_4D7EB0(object);
    func_121E80(D_001B6620, object);
}

s32 func_00221660(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00221670);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00221A30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00221AC0);

/**
 * @brief Detach the receiver, then process it through the shared owner.
 * @param object Receiver to detach and process.
 */
void func_00221C30(void* object)
{
    func_4D7EB0(object);
    func_121E80(D_001B6620, object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00221C60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00221D10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00221DB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00221ED0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00221F60);

s32 func_00221FB0(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00221FC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00222090);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00222100);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00222200);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00222250);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00222350);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002224D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00222540);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00222670);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00222880);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002228F0);

/** Partial receiver containing the source and destination vectors. */
struct FieldVectorInitState
{
    u8 unk00[0x20];
    unsigned __int128 unk20;
    u8 unk30[0x140];
    unsigned __int128 unk170;
    u8 unk180[0x10];
    unsigned __int128 unk190;
};

/** Vector view used to initialize the destination with an identity vector. */
union FieldVectorConstant
{
    unsigned __int128 raw;
    float components[4];
};

/**
 * @brief Copy the source vector and initialize the destination vector.
 * @param object Receiver containing vectors at offsets 0x20, 0x170, and 0x190.
 */
void func_00222D20(void* object)
{
    FieldVectorInitState* state = (FieldVectorInitState*)object;
    state->unk170 = state->unk20;
    FieldVectorConstant identity;
    identity.components[0] = 0.0f;
    identity.components[1] = 0.0f;
    identity.components[2] = 0.0f;
    identity.components[3] = 1.0f;
    state->unk190 = identity.raw;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00222D50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00222DC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00222E40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00223330);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00223410);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002234A0);

void func_00223580(void* unused, void* object)
{
    func_4D7EB0(object);
    ((FieldCallbackDispatch10*)object)->callback();
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002235C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00223620);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00223690);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00223700);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002237D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00223820);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00223890);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00223950);

void func_002239B0(void* object)
{
}

void func_002239C0(void* object)
{
    if (object != 0)
    {
        ((FieldUnaryCallback*)object)->callback(1);
    }
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_002239F0);

s32 func_00223A40(void* object)
{
    return 0;
}

s32 func_00223A50(void* object)
{
    return 0;
}

s32 func_00223A60(void* object)
{
    return 0;
}

s32 func_00223A70(void* object)
{
    return 0;
}

void func_00223A80(void* object)
{
}

void func_00223A90(void* object)
{
}

void func_00223AA0(void* object)
{
    *(u32*)((u8*)object + 0x4C) = 0;
    func_00223D70(object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00223AC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00223B20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00223B80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00223BE0);

/**
 * @brief Call the receiver's output callback with zero and one local word.
 * @param object Receiver with the output callback at vtable offset 0x34.
 */
void func_00223C40(void* object)
{
    u32 result = 0;
    ((FieldCallbackOutputs34*)object)->callback(0.0f, &result, &result, &result);
}

void func_00223C80(const void* object, float* value)
{
    const FieldFloatState50* state = (const FieldFloatState50*)object;
    *value = state->value50;
}

/** Record with an observed float at offset 4 and a 16-byte stride. */
struct FieldFloatRecord4
{
    u32 unk00;
    float value04;
    u32 unk08;
    u32 unk0c;
};

/** Receiver prefix with a record pointer at +4 and signed index at +0x20. */
struct FieldIndexedFloatState
{
    u8 pad00[4];
    const FieldFloatRecord4* records;
    u8 pad08[0x18];
    s16 index;
};

/**
 * @brief Store the indexed record's float relative to the first record.
 * @param object Receiver containing the record pointer and signed index.
 * @param result Destination for the difference when the record pointer exists.
 */
extern "C" void func_00223C90(const FieldIndexedFloatState* object, float* result)
{
    const FieldFloatRecord4* records = object->records;
    if (records != 0)
    {
        *result = records[object->index - 1].value04 - records[0].value04;
    }
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00223CC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00223D70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00223E00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00223ED0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00213F40", func_00223F30);
