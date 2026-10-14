#include "include_asm.h"
#include "overlays/1070-00/text_002B4F20.h"
#include "overlays/1070-00/text_001E2B40.h"


extern "C" u8 D_173ED0[];
extern "C" u8 D_335C88[];
extern "C" u8 D_335C90[];
extern "C" FieldContextRef* D_001B64B0;
extern "C" void* D_001B6620;
extern "C" void func_121E80(void* owner, void* object);
extern "C" void func_43AC90(void* object);
extern "C" void func_002B5200(void* object, u16 value);
extern "C" void func_4F4740(void* object, u32 value, u32 flags);
extern "C" void* D_001B667C;
extern "C" void func_139C10(void* context, const void* table, ...);
extern "C" void func_002BB300(void* context, u32 first, u32 second, void* object);

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

/** Partial receiver with a value at 0x18 and result word at 0x1C. */
struct FieldLookupState18
{
    u8 unk00[0x18];
    void* value;
    u32 result;
};

/** Partial initialized object with its table pointer at offset 0x10. */
struct FieldStateTableAt10
{
    u32 unk00;
    u32 unk04;
    u8 unk08;
    u8 unk09;
    u8 unk0a[2];
    u32 unk0c;
    void* table;
};

/** Partial receiver whose state flag is bit zero of the byte at offset 0x1C. */
struct FieldFlagByte1C
{
    u8 unk00[0x1C];
    u8 unk1c_0 : 1;
    u8 unk1c_1_7 : 7;
};

/** Partial receiver whose state flag is bit zero of the byte at offset 0x4B5. */
struct FieldFlagByte4B5
{
    u8 unk00[0x4B5];
    u8 unk4b5_0 : 1;
    u8 unk4b5_1_7 : 7;
};

extern "C" void func_4EABF0(void);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B4F20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B50C0);

s32 func_002B5150(void* object)
{
    return 9;
}

void func_002B5160(void* object)
{
    func_121E80(D_001B6620, object);
}

/** Receiver fields passed to func_002B5200. */
struct FieldCallbackInput5180
{
    u8 unk00[0x14];
    void* state;
    u16 value;
};

/**
 * @brief Update the receiver's state and invoke its callback.
 * @param object Receiver providing the state and callback fields.
 */
extern "C" void func_002B5180(FieldCallbackInput5180* object)
{
    func_002B5200(object->state, object->value);
    ((FieldCallbackDispatch58*)object)->slot10();
}

/**
 * @brief Apply a shared update when its optional state is present.
 * @param object Receiver retained by the callback signature.
 * @param value Value forwarded to the shared update.
 * @return One when the shared state exists, otherwise zero.
 */
extern "C" s32 func_002B51C0(void* object, u32 value)
{
    if (D_001B667C == 0) {
        return 0;
    }

    func_4F4740(D_001B667C, value, 0);
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B5200);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B5340);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B5490);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B5A80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B5BF0);

void* func_002B5C80(void* object)
{
    FieldStateTableAt10* state = (FieldStateTableAt10*)object;
    state->table = D_173ED0;
    state->unk00 = 0;
    state->unk04 = 0;
    state->unk08 = 0;
    state->unk09 = 0;
    state->unk0c = 0;
    return object;
}

void func_002B5CB0(FieldFourValueState48* object, s32 first, s32 second, s32 third, s32 fourth)
{
    object->unk44 = 1;
    object->unk48 = first;
    object->unk4c = second;
    object->unk50 = third;
    object->unk54 = fourth;
}

void func_002B5CD0(void)
{
    func_4EABF0();
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B5CF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B5D30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B5DC0);

/**
 * @brief Mark the receiver active, initialize it, and pass it to the owner.
 * @param object Receiver to initialize and process.
 */
extern "C" void func_002B5E20(void* object)
{
    ((u8*)object)[0x11C] = 1;
    func_43AC90(object);
    func_121E80(D_001B6620, object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B5E60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B5F00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B5FA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B69D0);

void func_002B6BC0(FieldFloatPair30* object, float first, float second)
{
    object->unk30 = first;
    object->unk34 = second;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B6BD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B6C80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B6CE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B6CF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B6D00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B6D60);

s32 func_002B6DE0(void* object)
{
    return 3;
}

extern "C" void func_002B6DF0(void* object)
{
    *(u32*)((u8*)object + 0x28) = 0;
}

extern "C" float func_002B6E00(void* object)
{
    return 2500.0f;
}

s32 func_002B6E20(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B6E30);

void func_002B7070(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B7080);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B7260);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B7560);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B7610);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B76E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B7740);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B77B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B7820);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B7900);

void func_002B79A0(void* receiver)
{
    FieldFlagByte1C* object = (FieldFlagByte1C*)receiver;
    object->unk1c_0 = 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B79C0);

void func_002B8040(FieldPointerValueState2C* object, const u8* source, u32 value)
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

extern "C" s32 func_002B8080(void* object)
{
    return 0;
}

void func_002B8090(void* object)
{
}

extern "C" float func_002B80A0(void* object)
{
    return 100.0f;
}

void func_002B80B0(void* object)
{
}

void func_002B80C0(void* object)
{
}

void func_002B80D0(void* object)
{
}

void func_002B80E0(void* object)
{
}

void func_002B80F0(void* object)
{
}

extern "C" void func_002B8100(void* object)
{
}

s32 func_002B8110(void* object)
{
    return 0;
}

void func_002B8120(void* object)
{
}

void func_002B8130(void* object)
{
}

void func_002B8140(void* object)
{
}

s32 func_002B8150(void* object)
{
    return 0;
}

void func_002B8160(void* object)
{
}

void func_002B8170(void* object)
{
}

void func_002B8180(void* object)
{
}

void func_002B8190(void* object)
{
}

void func_002B81A0(void* object)
{
}

s32 func_002B81B0(void* object)
{
    return 0;
}

void func_002B81C0(void* object)
{
}

s32 func_002B81D0(void* object)
{
    return 0;
}

void func_002B81E0(void* object)
{
}

extern "C" float func_002B81F0(void* object)
{
    return 0.0f;
}

void func_002B8200(void* object)
{
}

void func_002B8210(void* object)
{
}

s32 func_002B8220(void* object)
{
    return 0;
}

void func_002B8230(void* object)
{
}

s32 func_002B8240(void* object)
{
    return 0;
}

void func_002B8250(void* object)
{
}

extern "C" float func_002B8260(void* object)
{
    return 0.0f;
}

void func_002B8270(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B8280);

FieldEntry90* func_002B82E0(const FieldEntryArray90At14* object, s32 index)
{
    return &object->entries[index];
}

u8* func_002B8300(const FieldIndexedStorage20* object, s32 row, s32 column)
{
    s32 index = row * (object->count - 1) + column;
    return object->data + (index << 6);
}

extern "C" u32 func_002B8320(void* object)
{
    return *(u32*)((u8*)object + 0x1C);
}

extern "C" u32 func_002B8330(void* object)
{
    return *(u32*)((u8*)object + 0xC);
}

extern "C" u32 func_002B8340(void* object)
{
    return *(u32*)((u8*)object + 0x10);
}

s32 func_002B8350(void* object)
{
    return 32;
}

extern "C" s32 func_002B8360(void* object)
{
    return *(u32*)((u8*)object + 0x14) != 0;
}

void func_002B8370(void* object, const void* source)
{
    u32* destinationWords = (u32*)object;
    const u32* sourceWords = (const u32*)source;
    destinationWords[3] = sourceWords[3];
    destinationWords[4] = sourceWords[4];
    ((FieldCallbackDispatch58*)object)->callback(destinationWords[3], destinationWords[4]);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B83B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B8920);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B8960);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B89E0);

extern "C" float func_002B8AC0(void* object)
{
    return 1.0f;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B8AD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B8BA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B8BF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B8D70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B9010);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B9080);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B90F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B9150);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B9160);

s32 func_002B91D0(void* object)
{
    return 3;
}

extern "C" void func_002B91E0(void* object)
{
    *(u32*)((u8*)object + 0x28) = 0;
}

extern "C" float func_002B91F0(void* object)
{
    return *(float*)((u8*)object + 0x2C);
}

s32 func_002B9200(void* object)
{
    return 1;
}

u8* func_002B9210(const FieldIndexedStorage20* object, s32 row, s32 column)
{
    s32 index = row * (object->count - 1) + column;
    return object->data + (index << 6);
}

FieldEntry50* func_002B9230(const FieldEntryArray50At14* object, s32 index)
{
    return &object->entries[index];
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B9250);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B9770);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B9A10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B9E10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B9EB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B9F20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002B9F80);

void func_002B9FF0(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BA000);

s32 func_002BA1F0(void* object)
{
    return 0;
}

void func_002BA200(void* object)
{
}

extern "C" float func_002BA210(void* object)
{
    return 100.0f;
}

void func_002BA220(void* object)
{
}

void func_002BA230(void* object)
{
}

void func_002BA240(void* object)
{
}

void func_002BA250(void* object)
{
}

void func_002BA260(void* object)
{
}

void func_002BA270(void* object)
{
}

s32 func_002BA280(void* object)
{
    return 0;
}

void func_002BA290(void* object)
{
}

void func_002BA2A0(void* object)
{
}

void func_002BA2B0(void* object)
{
}

s32 func_002BA2C0(void* object)
{
    return 0;
}

void func_002BA2D0(void* object)
{
}

void func_002BA2E0(void* object)
{
}

void func_002BA2F0(void* object)
{
}

void func_002BA300(void* object)
{
}

void func_002BA310(void* object)
{
}

s32 func_002BA320(void* object)
{
    return 0;
}

void func_002BA330(void* object)
{
}

s32 func_002BA340(void* object)
{
    return 0;
}

void func_002BA350(void* object)
{
}

extern "C" float func_002BA360(void* object)
{
    return 0.0f;
}

void func_002BA370(void* object)
{
}

void func_002BA380(void* object)
{
}

s32 func_002BA390(void* object)
{
    return 0;
}

void func_002BA3A0(void* object)
{
}

s32 func_002BA3B0(void* object)
{
    return 0;
}

void func_002BA3C0(void* object)
{
}

extern "C" float func_002BA3D0(void* object)
{
    return 0.0f;
}

void func_002BA3E0(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BA3F0);

extern "C" u32 func_002BA450(void* object)
{
    return *(u32*)((u8*)object + 0x1C);
}

extern "C" u32 func_002BA460(void* object)
{
    return *(u32*)((u8*)object + 0xC);
}

extern "C" u32 func_002BA470(void* object)
{
    return *(u32*)((u8*)object + 0x10);
}

s32 func_002BA480(void* object)
{
    return 1;
}

extern "C" s32 func_002BA490(void* object)
{
    return *(u32*)((u8*)object + 0x14) != 0;
}

void func_002BA4A0(void* object, const void* source)
{
    u32* destinationWords = (u32*)object;
    const u32* sourceWords = (const u32*)source;
    destinationWords[3] = sourceWords[3];
    destinationWords[4] = sourceWords[4];
    ((FieldCallbackDispatch58*)object)->callback(destinationWords[3], destinationWords[4]);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BA4E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BAA50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BAA90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BAB10);

extern "C" float func_002BABF0(void* object)
{
    return 1.0f;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BAC00);

/**
 * @brief Initialize the receiver, then pass it to the shared owner.
 * @param object Receiver to initialize and process.
 */
void func_002BAC90(void* object)
{
    func_4D7EB0(object);
    func_121E80(D_001B6620, object);
}

extern "C" s16 func_002BACC0(void* object)
{
    return *(s16*)((u8*)object + 0x14);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BACD0);

/**
 * @brief Pass the shared context field and constants to the receiver helper.
 * @param object Receiver passed as the helper's final argument.
 */
void func_002BAE90(void* object)
{
    func_002BB300(D_001B64B0->context->unke4, 1, 3, object);
}

void func_002BAEC0(void* object, void* context)
{
    FieldLookupState18* state = (FieldLookupState18*)object;
    func_139C10(context, D_335C88, state->value, &state->result);
}

struct FieldLookupState24
{
    u8 unk00[0x18];
    void* first;
    void* second;
    void* third;
};

/**
 * @brief Look up a field using three values stored on the receiver.
 * @param object Receiver holding the lookup values at offsets 0x18 through 0x20.
 * @param context Context passed to the lookup helper.
 */
extern "C" void func_002BAEF0(FieldLookupState24* object, void* context)
{
    func_139C10(context, D_335C90, object->first, object->second, object->third);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BAF30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BAFB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BB090);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BB0E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BB270);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BB300);

void func_002BB490(void)
{
    func_4EABF0();
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BB4B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BB500);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BB6A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BDA30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BE640);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BE6B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BE790);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BE8F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BEDA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BEE40);

s32 func_002BEEE0(void* object)
{
    return 2;
}

extern "C" void func_002BEEF0(void* object)
{
    ((u8*)object)[0x60] = 10;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BEF00);

void func_002BEF10(void* object)
{
}

void func_002BEF20(void* object)
{
}

void func_002BEF30(void* object)
{
}

void func_002BEF40(void* receiver, u32 enabled)
{
    FieldFlagByte4B5* object = (FieldFlagByte4B5*)receiver;
    object->unk4b5_0 = enabled;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BEF60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BF0F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BF1A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BF270);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BF350);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BF630);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BF7B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BF8F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BF950);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BF9B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BFBE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BFCD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BFDC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BFE10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002BFEF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002C0000);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002C0130);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002C0500);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002C0600);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002C0A40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002C0D00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002C16E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002C1990);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002C1B20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002C1BE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002C1D60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002C2640);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002C27D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002C31F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002B4F20", func_002C3BA0);
