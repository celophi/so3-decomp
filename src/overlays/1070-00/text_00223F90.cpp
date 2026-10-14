#include "include_asm.h"
#include "overlays/1070-00/text_00223F90.h"
#include "overlays/1070-00/text_00284BF0.h"

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

extern "C" float D_001B66B4;
extern "C" FieldContextRef* D_001B64B0;
extern "C" void* D_001B6620;
extern "C" void func_4D7EB0(void* object);
extern "C" void func_4EAB40(void* object);
extern "C" s32 func_00209810(void* object);
extern "C" s32 func_00209860(void* object);
extern "C" void func_00248FD0(void* object, u32 value, u32 nextValue);
extern "C" void func_0023BC00(void* object);
extern "C" void func_001FE900(void* object);

/** Partial receiver with a word cursor at offset 0x540. */
struct FieldWordCursor540
{
    u8 unk00[0x540];
    u32* cursor;
};

/** Shared flag byte whose bit two reflects the receiver's cursor value. */
struct FieldSharedFlag230
{
    u8 unk00[0x230];
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 bit2 : 1;
    u8 bits3_7 : 5;
};
extern "C" void func_121E80(void* owner, void* object);
extern "C" void func_002090B0(void* object);
extern "C" u8 func_002CDB60(void* object);
extern "C" void func_4D9140(void* object);
extern "C" u8 D_16ACE0[];

/** Partial receiver exposing the secondary vtable pointer at offset 0x10. */
struct FieldSecondaryVTable10
{
    u8 unk00[0x10];
    void* vtable;
};

/** Partial callback interface with methods at offsets 0x64 through 0x70. */
class FieldCallbackDispatch64
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
    virtual void slot34(s32 value);
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

/** Partial callback interface with a method at vtable offset 0x98. */
class FieldCallbackDispatch98 : public FieldCallbackDispatch64
{
public:
    virtual void slot80();
    virtual void slot84();
    virtual void slot88();
    virtual void slot8c();
    virtual void slot90();
    virtual void slot94();
    virtual void callback98();
};


struct FieldBitState204
{
    u8 pad00[0x204];
    u32 value204;
};

/** Partial receiver containing the float initialized by func_00228A00. */
struct FieldFloatState5C
{
    u8 unk00[0x5C];
    float value;
};

struct FieldFloatTargetD690
{
    u8 pad00[0x28];
    u32 value28;
    u8 pad2c[0xB8];
    float valueE4;
};

struct FieldFloatSourceD690
{
    u8 pad00[0xAF0];
    float valueAF0;
};

struct FieldOptionalValue2F170
{
    u8 pad00[0x618];
    u32 present;
};

struct FieldIndexedTable2FCE0
{
    u8 pad00[0x10];
    s32 count;
    u8 pad14[0x0C];
    void* table;
};

u32 func_00223F90(const void* object)
{
    return *(const u32*)((const u8*)object + 0x18);
}

s32 func_00223FA0(const void* object)
{
    return *(const s16*)((const u8*)object + 0x20);
}

s32 func_00223FB0(void* object)
{
    return 0;
}

s32 func_00223FC0(void* object)
{
    return 0;
}

s32 func_00223FD0(void* object)
{
    return 0;
}

void func_00223FE0(void* object)
{
}

float func_00223FF0(void* object)
{
    return 0.0f;
}

/**
 * @brief Store the receiver's virtual float result in the supplied output.
 * @param object Receiver with the float callback at vtable offset 0x7C.
 * @param output Destination for the returned float.
 */
void func_00224000(void* object, float* output)
{
    *output = ((FieldCallbackDispatch64*)object)->slot7c();
}

u32 func_00224030(const void* object)
{
    return *(const u32*)((const u8*)object + 0x04);
}

typedef struct FloatKeyScanEntry_text_00223F90_10
{
    float key00;
    u8 unk04[0x8];
    float key0c;
} FloatKeyScanEntry_text_00223F90_10;

typedef struct FloatKeyScanOwner_text_00223F90_10
{
    u8 unk00[0x4];
    FloatKeyScanEntry_text_00223F90_10* entries;
    u8 unk08[0x18];
    s16 count20;
} FloatKeyScanOwner_text_00223F90_10;

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00224040);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00224090);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00224120);

float func_00224180(const FieldFloatValueSequence20* object)
{
    if (object->count < 2)
    {
        return 0.0f;
    }
    s32 lastIndex = object->count - 1;
    const FieldFloatValueEntry16* last = object->entries + lastIndex;
    return last->unk00 - object->entries[0].unk00;
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_002241D0(void* object, float key)
{
    FloatKeyScanOwner_text_00223F90_10* receiver = static_cast<FloatKeyScanOwner_text_00223F90_10*>(object);
    s16 count = receiver->count20;
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

void func_00224220(FieldFloatSequenceState2C* object, s32 count, FieldFloatValueEntry16* entries)
{
    object->flags2b_1 = 1;
    object->entries = entries;
    object->count22 = count;
    object->count20 = count;
    const FieldFloatValueEntry16* last = object->entries + (count - 1);
    object->range1c = last->unk00 - object->entries[0].unk00;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00224270);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00224330);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_002243B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_002244D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00224570);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00224630);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00224A50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00224AA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00224B80);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x64.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_00224CE0(void* object)
{
    ((FieldCallbackDispatch64*)object)->slot64();
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x68.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_00224D10(void* object)
{
    ((FieldCallbackDispatch64*)object)->slot68();
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x6C.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_00224D40(void* object)
{
    ((FieldCallbackDispatch64*)object)->slot6c();
}

/**
 * @brief Invoke the receiver's callback at vtable offset 0x70.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_00224D70(void* object)
{
    ((FieldCallbackDispatch64*)object)->slot70();
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00224DA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00224DB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00224DC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00224DD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00224DE0);

s32 func_00224DF0(void* object)
{
    return 4;
}

void func_00224E00(void* object)
{
    func_121E80(D_001B6620, object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00224E20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00224F40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_002250D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00225B20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00226320);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00226640);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00226CE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_002272B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00227430);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_002277F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_002278B0);

void func_002279E0(FieldWordByteState30* object, u32 value, u8 state)
{
    object->unk30 = value;
    object->unk34 = state;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_002279F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00227AD0);

void func_00227BC0(void* object)
{
    func_121E80(D_001B6620, object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00227BE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00227F40);

void func_00228020(void* object)
{
    ((u8*)object)[0x48] = 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00228030);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00228110);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00228190);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_002283A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_002283B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_002283C0);

/**
 * @brief Detach the receiver, then process it through the shared owner.
 * @param object Receiver to detach and process.
 */
extern "C" void func_00228480(void* object)
{
    func_4D7EB0(object);
    func_121E80(D_001B6620, object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_002284B0);

void func_00228670(FieldFloatResetState1C* object, u8 first_state, u8 second_state, float first, float second)
{
    object->unk1c = 0;
    object->unk1e = 0;
    object->unk1d = 0;
    object->unk2c = 0.0f;
    object->unk28 = 0.0f;
    object->unk24 = 0.0f;
    object->unk20 = 0.0f;
    object->unk1c = first_state;
    object->unk1d = second_state;
    object->unk20 = first;
    object->unk28 = second;
    if (second == 0.0f)
    {
        object->unk1e = object->unk1d;
    }
}

void func_002286C0(FieldFloatResetState1C* object)
{
    object->unk1c = 0;
    object->unk1e = 0;
    object->unk1d = 0;
    object->unk2c = 0.0f;
    object->unk28 = 0.0f;
    object->unk24 = 0.0f;
    object->unk20 = 0.0f;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_002286E0);

s32 func_00228770(void* object)
{
    return 14;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00228780);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00228850);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_002288E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00228960);

/**
 * @brief Set the receiver's float at 0x5C to one and call its vtable slot 0x34.
 * @param object Receiver with the initialized field and callback table.
 */
void func_00228A00(void* object)
{
    ((FieldFloatState5C*)object)->value = 1.0f;
    ((FieldCallbackDispatch64*)object)->slot34(0);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00228A30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00228B30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00228D00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00228D80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00228FD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00229020);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_002291E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_002297A0);

FieldVector* func_00229DF0(FieldVector* vector, float x, float y, float z, float w)
{
    vector->x = x;
    vector->y = y;
    vector->z = z;
    vector->w = w;
    return vector;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00229E10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022A430);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022A710);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022B200);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022B250);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022B2A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022B670);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022B6D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022B8A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022B900);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022C3F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022C8F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022D2B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022D310);

void func_0022D480(void* object)
{
    FieldBitState204* state = (FieldBitState204*)object;
    state->value204 &= ~0x40;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022D4A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022D540);

s32 func_0022D5F0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022D600);

s32 func_0022D680(void* object)
{
    return 3;
}

void func_0022D690(void* object, const void* source)
{
    FieldFloatTargetD690* target = (FieldFloatTargetD690*)object;
    const FieldFloatSourceD690* input = (const FieldFloatSourceD690*)source;
    target->value28 = 0;
    target->valueE4 = input->valueAF0;
}

float func_0022D6A0(void* object)
{
    return 2500.0f;
}

s32 func_0022D6C0(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022D6D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022DAC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022DB20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022DBA0);

void func_0022DE80(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022DE90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022E890);

s32 func_0022EAB0(void* object)
{
    return 240;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022EAC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022EB80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022EE90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022EFE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022F050);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022F0B0);

s32 func_0022F140(void* object)
{
    return 7;
}

s32 func_0022F150(void* object)
{
    return 0;
}

s32 func_0022F160(void* object)
{
    return 0;
}

void* func_0022F170(const void* object)
{
    const FieldOptionalValue2F170* state = (const FieldOptionalValue2F170*)object;
    if (state->present != 0)
    {
        return (u8*)object + 0x620;
    }
    return 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022F190);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022F270);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022F360);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022F3F0);

void func_0022FA30(FieldByteSourceState* object, const u8* source, u32 value)
{
    object->source = source;
    object->unk30 = value;
    if (*object->source == 1)
    {
        object->unk34 = 1;
    }
    else
    {
        object->unk34 = 0;
    }
}

s32 func_0022FA70(void* object)
{
    return 0;
}

void func_0022FA80(void* object)
{
}

float func_0022FA90(void* object)
{
    return 100.0f;
}

void func_0022FAA0(void* object)
{
}

void func_0022FAB0(void* object)
{
}

void func_0022FAC0(void* object)
{
}

void func_0022FAD0(void* object)
{
}

void func_0022FAE0(void* object)
{
}

void func_0022FAF0(void* object)
{
}

s32 func_0022FB00(void* object)
{
    return 0;
}

void func_0022FB10(void* object)
{
}

void func_0022FB20(void* object)
{
}

void func_0022FB30(void* object)
{
}

s32 func_0022FB40(void* object)
{
    return 0;
}

void func_0022FB50(void* object)
{
}

void func_0022FB60(void* object)
{
}

void func_0022FB70(void* object)
{
}

void func_0022FB80(void* object)
{
}

void func_0022FB90(void* object)
{
}

s32 func_0022FBA0(void* object)
{
    return 0;
}

void func_0022FBB0(void* object)
{
}

s32 func_0022FBC0(void* object)
{
    return 0;
}

void func_0022FBD0(void* object)
{
}

float func_0022FBE0(void* object)
{
    return 0.0f;
}

void func_0022FBF0(void* object)
{
}

void func_0022FC00(void* object)
{
}

s32 func_0022FC10(void* object)
{
    return 0;
}

void func_0022FC20(void* object)
{
}

s32 func_0022FC30(void* object)
{
    return 0;
}

void func_0022FC40(void* object)
{
}

float func_0022FC50(void* object)
{
    return 0.0f;
}

void func_0022FC60(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022FC70);

void* func_0022FCD0(const void* object, u32 index)
{
    const u32* table = (const u32*)((const u8*)object + 0x14);
    return (void*)(*table + (index << 7));
}

void* func_0022FCE0(const void* object, s32 index, s32 row)
{
    const FieldIndexedTable2FCE0* table = (const FieldIndexedTable2FCE0*)object;
    s32 offset = index * (table->count - 1) + row;
    return (u8*)table->table + (offset << 6);
}

u32 func_0022FD00(const void* object)
{
    return *(const u32*)((const u8*)object + 0x1C);
}

u32 func_0022FD10(const void* object)
{
    return *(const u32*)((const u8*)object + 0x0C);
}

u32 func_0022FD20(const void* object)
{
    return *(const u32*)((const u8*)object + 0x10);
}

s32 func_0022FD30(void* object)
{
    return 32;
}

s32 func_0022FD40(const void* object)
{
    const u32* value = (const u32*)((const u8*)object + 0x14);
    return *value != 0;
}

void func_0022FD50(void* object, const void* source)
{
    u32* destinationWords = (u32*)object;
    const u32* sourceWords = (const u32*)source;
    destinationWords[3] = sourceWords[3];
    destinationWords[4] = sourceWords[4];
    ((FieldCallbackDispatch58*)object)->callback(destinationWords[3], destinationWords[4]);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_0022FD90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_002302F0);

float func_002303D0(void* object)
{
    return 1.0f;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_002303E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_002303F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00230400);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00230410);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00230420);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00230430);

float func_00230440(void* object)
{
    return D_001B66B4;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00230450);

s32 func_002304D0(void* object)
{
    return D_001B64B0->context->unk50 != 0;
}

s32 func_002304F0(void* object)
{
    return 1;
}

s32 func_00230500(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00230510);

void func_00230570(void)
{
    func_002090B0(D_001B64B0->context->unk58);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_002305A0);

s32 func_00230680(void)
{
    u8 result = func_002CDB60(D_001B64B0->context);
    return (result != 0) ^ 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_002306B0);

/**
 * @brief Return -1 for a negative byte, otherwise query the shared context.
 * @param object Unused receiver retained by the callback signature.
 * @param value Signed byte used to select the result path.
 * @return Negative one or the shared helper result.
 */
extern "C" s32 func_00230790(void* object, s8 value)
{
    if (value < 0)
    {
        return -1;
    }
    return func_00209810(D_001B64B0->context->unk58);
}

/**
 * @brief Return -1 for a negative byte, otherwise query the shared context.
 * @param object Unused receiver retained by the callback signature.
 * @param value Signed byte used to select the result path.
 * @return Negative one or the shared helper result.
 */
extern "C" s32 func_002307D0(void* object, s8 value)
{
    if (value < 0)
    {
        return -1;
    }
    return func_00209860(D_001B64B0->context->unk58);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00230810);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_002308A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_002309B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00230A20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00230FF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00231060);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00231120);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00231210);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00231360);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00231620);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_002316B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_002316F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00231830);

/**
 * @brief Detach the receiver, then process it through the shared owner.
 * @param object Receiver to detach and process.
 */
extern "C" void func_00231920(void* object)
{
    func_4D7EB0(object);
    func_121E80(D_001B6620, object);
}

/**
 * @brief Invoke the receiver's callback, then run its shared follow-up helper.
 * @param object Receiver used for both calls.
 */
extern "C" void func_00231950(FieldCallbackDispatch98* object)
{
    object->callback98();
    func_4EAB40(object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00231990);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00231A10);

void* func_00231BA0(void* object)
{
    FieldSecondaryVTable10* state = (FieldSecondaryVTable10*)object;
    func_4D9140(object);
    state->vtable = D_16ACE0;
    return object;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00231BE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00231C70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00231C80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00231C90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00231D10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00231E80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00231FD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00232020);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00232090);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00232390);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00232490);

/**
 * @brief Copy the receiver's low bit into bit two of the shared flag byte.
 * @param object Receiver whose word cursor is at offset 0x540.
 * @return One after updating the shared flag.
 */
extern "C" s32 func_00232550(const FieldWordCursor540* object)
{
    FieldSharedFlag230* flags = (FieldSharedFlag230*)D_001B64B0->context->unk14;
    flags->bit2 = (object->cursor[0] & 1) != 0;
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00232590);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00232610);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00232770);

/**
 * @brief Refresh two embedded context objects and report success.
 * @param object Unused receiver retained by the callback signature.
 * @return One after refreshing both objects.
 */
extern "C" s32 func_002328D0(void* object)
{
    u8* state = (u8*)D_001B64B0->context->unk14;
    func_0023BC00(state + 0x240);
    func_001FE900(state + 0x30);
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00232910);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00232990);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00232A20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00232B40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00232C50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00232ED0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00232FE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00233140);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_002332A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00233430);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_002335C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00233850);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00233920);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00233AA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00233AF0);

/**
 * @brief Advance the receiver's word cursor and pass its values to a helper.
 * @param object Receiver containing the cursor at offset 0x540.
 * @return One after the helper call.
 */
s32 func_00233B40(void* object)
{
    FieldWordCursor540* state = (FieldWordCursor540*)object;
    u32* cursor = state->cursor;
    state->cursor = cursor + 1;
    u32 first = cursor[0];
    u32 second = state->cursor[0];
    func_00248FD0(object, first + 0x5000, second);
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00233B80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00233C40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00233CF0);

s32 func_00233D50(const FieldWordSource540* object)
{
    D_001B64B0->context->unkb0 = *object->unk540;
    return 1;
}

s32 func_00233D70(const FieldWordSource540* object)
{
    D_001B64B0->context->unka4 = *object->unk540;
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00233D90);

s32 func_00233EA0(const FieldWordSource540* object)
{
    D_001B64B0->context->unka6 = *object->unk540;
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00223F90", func_00233EC0);
