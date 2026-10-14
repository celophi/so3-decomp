#include "include_asm.h"
#include "overlays/1070-00/text_002C55D0.h"
#include "overlays/1070-00/text_002D55D0.h"
#include "overlays/1070-00/text_001E2B40.h"

extern "C" void* D_001B6620;
extern "C" void func_121E80(void* owner, void* object);
extern "C" void __ct__17LibReceiver4DD1F0Fv(void* object);
extern "C" u32 D_17C610[];


/** Partial callback interface with a method at offset 0x10. */
class FieldCallbackDispatch10
{
public:
    virtual void slot08();
    virtual void slot0c();
    virtual void callback();
};

/** Partial receiver with its table pointer and two words at 0x210. */
struct FieldConstructorReceiver210
{
    u8 unk00[0x210];
    u32 unk210;
    u32 unk214;
};

extern "C" void func_002CFA20(void* object);
extern "C" void func_002CE8E0(void* object);
#include "overlays/lib/vector.h"

extern "C" void func_4815A0(void);
extern "C" void func_481620(void);
extern "C" void* D_001B66A0;
extern "C" void* D_001B6694;
extern "C" void func_002D7D00(void* object);
extern "C" void func_002D7EA0(void* context, void* object);
extern "C" void func_002D70E0(void* object);
extern "C" void func_002D7E50(void* context, void* object);
extern "C" void func_137F40(void* object, s32 start, s32 size);
extern "C" void* D_001B667C;
extern "C" void func_4F4840(void* object);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002C55D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002C5650);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002C5AF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002C6330);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002C6F30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002C7250);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002C7460);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002C7620);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002C7720);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002C7E30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002C7F60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002C84A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002C8560);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002C8750);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002C8790);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002C9540);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002C9980);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002C9AF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CA1E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CA8F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CAC00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CACA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CAEA0);

s32 func_002CAF30(void* object)
{
    return 2;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CAF40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CAFA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CB0D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CB160);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CB3D0);

void func_002CB620(void* object)
{
    u8* bytes = (u8*)object;
    *(FieldVec4B*)(bytes + 0x8F0) = *(const FieldVec4A*)(bytes + 0x290);
    *(FieldVec4B*)(bytes + 0x900) = *(const FieldVec4A*)(bytes + 0x2A0);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CB650);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CB710);

/**
 * @brief Invoke the callback at offset 0x10 on the receiver's field at 0x4C.
 * @param object Receiver containing the callback interface at offset 0x4C.
 */
void func_002CB7A0(void* object)
{
    FieldCallbackDispatch10* callback = *(FieldCallbackDispatch10**)((u8*)object + 0x4C);
    callback->callback();
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CB7D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CB840);

void func_002CB980(FieldLinkedState* object, void* receiver, u32 value)
{
    object->unk24 = receiver;
    object->unk28 = value;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CB990);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CBA50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CBED0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CC000);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CC160);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CC1C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CC300);

void func_002CC6B0(FieldVectorSlots880* object, const unsigned __int128* value)
{
    object->unk890 = *value;
    object->unk50 = 1;
    object->unk20 = *value;
}

extern "C" void func_002CC6D0(unsigned __int128* vector)
{
    *vector = 0;
}

void func_002CC6E0(unsigned __int128* first, unsigned __int128* second, const unsigned __int128* source)
{
    unsigned __int128 value = *source;
    *second = value;
    *first = value;
}

FieldVector* func_002CC6F0(FieldVector* vector, float value)
{
    vector->x = value;
    vector->y = value;
    vector->z = value;
    vector->w = value;
    return vector;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CC710);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CC800);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CC850);

void func_002CCB50(FieldVectorBits* value)
{
    value->bits = 0;
    value->vector.w = 1.0f;
}

/** Initialize the receiver's constructor state and return it. */
void* func_002CCB60(void* object)
{
    FieldConstructorReceiver210* state = (FieldConstructorReceiver210*)object;
    __ct__17LibReceiver4DD1F0Fv(object);
    *(u32**)object = D_17C610;
    state->unk210 = 0;
    state->unk214 = 0;
    return object;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CCBA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CCD30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CCE40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CD0B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CD120);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CD200);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CD250);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CD310);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CD390);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CD4E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CD5C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CD660);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CD6F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CD870);

s32 func_002CD940(void* object)
{
    return 2;
}

void func_002CD950(FieldVectorSlots880* object, const unsigned __int128* value)
{
    object->unk880 = *value;
    object->unk50 = 1;
    object->unk30 = *value;
}

void func_002CD970(FieldVectorSlots880* object, const unsigned __int128* value)
{
    object->unk880 = *value;
    object->unk50 = 1;
    object->unk30 = *value;
}

void func_002CD990(FieldVectorSlots880* object, const unsigned __int128* value)
{
    object->unk890 = *value;
    object->unk50 = 1;
    object->unk20 = *value;
}

s32 func_002CD9B0(void* object)
{
    return 3;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CD9C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CD9D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CD9E0);

s32 func_002CDA70(void* object)
{
    return 9;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CDA80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CDB10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CDB60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CDBA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CDD20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CE4F0);

/**
 * @brief Initialize the receiver, then pass it to the shared owner.
 * @param object Receiver to initialize and process.
 */
void func_002CE640(void* object)
{
    func_4D7EB0(object);
    func_121E80(D_001B6620, object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CE670);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CE6C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CE710);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CE8E0);

void func_002CEEB0(void* object)
{
    func_002CFA20(object);
    func_002CE8E0(object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CEEE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CF990);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002CFA20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D1AB0);

void func_002D1B70(void* object)
{
    func_137F40((u8*)object + 0x184, 0, 4);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D1BA0);

s32 func_002D1C40(void* object)
{
    return 14;
}

void func_002D1C50(void)
{
    func_4F4840(D_001B667C);
}

void func_002D1C70(FieldRecordQueue* object, u32 value, u8 kind, u8 flag)
{
    if (object->unk31 < object->unk24)
    {
        FieldRecord1C* record = &object->unk1c[object->unk31];
        record->unk0c = -1;
        record->unk04 = 0;
        record->unk10 = 0;
        record->unk16_0 = 0;
        record->unk16_1 = 1;
        record->unk08_0 = 0;
        record->unk16_2 = 0;
        record->unk14 = 0;
        record->unk15 = 0;
        record = &object->unk1c[object->unk31];
        record->unk04 = value;
        record->unk08_0 = 1;
        object->unk1c[object->unk31].unk16_1 = flag;
        object->unk1c[object->unk31].unk16_0 = 1;
        object->unk1c[object->unk31].unk14 = object->unk31;
        object->unk1c[object->unk31].unk15 = kind;
        object->unk31++;
    }
}

s32 func_002D1DE0(const FieldBitCountState* object)
{
    s32 limit = object->unk00;
    s32 count = 0;
    for (s32 index = 0; index < limit; index++)
    {
        if ((object->unk14[(u32)index >> 6] >> ((u32)index & 0x3F)) & 1)
        {
            count++;
        }
    }
    return count;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D1E40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D2140);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D21C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D2220);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D2290);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D22F0);

s32 func_002D2490(const FieldBitCountState* object)
{
    s32 limit = object->unk00;
    s32 count = 0;
    for (s32 index = 0; index < limit; index++)
    {
        if ((object->unk14[(u32)index >> 6] >> ((u32)index & 0x3F)) & 1)
        {
            count++;
        }
    }
    return count;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D24F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D2800);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D2880);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D28E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D2950);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D29B0);

s32 func_002D2B50(const FieldBitCountState* object)
{
    s32 limit = object->unk00;
    s32 count = 0;
    for (s32 index = 0; index < limit; index++)
    {
        if ((object->unk14[(u32)index >> 6] >> ((u32)index & 0x3F)) & 1)
        {
            count++;
        }
    }
    return count;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D2BB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D2EB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D2F20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D2F80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D2FE0);

s32 func_002D3180(const FieldBitCountState* object)
{
    s32 limit = object->unk00;
    s32 count = 0;
    for (s32 index = 0; index < limit; index++)
    {
        if ((object->unk14[(u32)index >> 6] >> ((u32)index & 0x3F)) & 1)
        {
            count++;
        }
    }
    return count;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D31E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D34F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D3550);

s32 func_002D36F0(const FieldBitCountState* object)
{
    s32 limit = object->unk00;
    s32 count = 0;
    for (s32 index = 0; index < limit; index++)
    {
        if ((object->unk14[(u32)index >> 6] >> ((u32)index & 0x3F)) & 1)
        {
            count++;
        }
    }
    return count;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D3750);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D3A60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D3AD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D3B30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D3B90);

s32 func_002D3D30(const FieldBitCountState* object)
{
    s32 limit = object->unk00;
    s32 count = 0;
    for (s32 index = 0; index < limit; index++)
    {
        if ((object->unk14[(u32)index >> 6] >> ((u32)index & 0x3F)) & 1)
        {
            count++;
        }
    }
    return count;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D3D90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D4080);

extern "C" u8 D_17BB30[];
extern "C" u8 D_17ACD0[];
extern "C" u8 D_179540[];

struct FieldPrimaryVTableState
{
    void* vtable;
};

extern "C" void* func_002D40E0(void* object)
{
    FieldPrimaryVTableState* state = (FieldPrimaryVTableState*)object;
    func_002D8130(object);
    state->vtable = D_17BB30;
    return object;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D4120);

s32 func_002D42B0(const FieldBitCountState* object)
{
    s32 limit = object->unk00;
    s32 count = 0;
    for (s32 index = 0; index < limit; index++)
    {
        if ((object->unk14[(u32)index >> 6] >> ((u32)index & 0x3F)) & 1)
        {
            count++;
        }
    }
    return count;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D4310);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D4610);

void* func_002D4670(void* object)
{
    FieldPrimaryVTableState* state = (FieldPrimaryVTableState*)object;
    func_002D8B70(object);
    state->vtable = D_17ACD0;
    return object;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D46B0);

s32 func_002D4850(const FieldBitCountState* object)
{
    s32 limit = object->unk00;
    s32 count = 0;
    for (s32 index = 0; index < limit; index++)
    {
        if ((object->unk14[(u32)index >> 6] >> ((u32)index & 0x3F)) & 1)
        {
            count++;
        }
    }
    return count;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D48B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D4BC0);

void* func_002D4C20(void* object)
{
    FieldPrimaryVTableState* state = (FieldPrimaryVTableState*)object;
    func_002D7EF0(object);
    state->vtable = D_179540;
    return object;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D4C60);

void func_002D4E00(void)
{
    func_4815A0();
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D4E20);

/**
 * @brief Clear the receiver state, then update it through the shared context.
 * @param object Receiver to update.
 */
void func_002D4E80(void* object)
{
    func_002D7D00(object);
    func_002D7EA0(D_001B66A0, object);
}

void func_002D4EB0(void)
{
    func_481620();
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D4ED0);

/**
 * @brief Reset receiver state, then update it through the shared context.
 * @param object Receiver to update.
 */
void func_002D4F30(void* object)
{
    func_002D70E0(object);
    func_002D7E50(D_001B6694, object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D4F60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D4FA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D5490);

void func_002D5500(const void* object, void* result)
{
    *(FieldVec4B*)result = *(const FieldVec4A*)((const u8*)object + 0xA0);
}

void func_002D5520(void* object)
{
    *(u32*)((u8*)object + 0x48) = 0;
    func_002D71E0((FieldSequenceState10*)object);
}

extern "C" void func_002D5540(void* object, float* result)
{
    float* values = *(float**)((u8*)object + 4);
    if (values != 0)
    {
        s16 count = *(s16*)((u8*)object + 0x18);
        *result = values[count * 2 - 1] - values[1];
    }
}

void func_002D5570(const FieldFloat4C* object, float* result)
{
    *result = object->unk4c;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002C55D0", func_002D5580);
