#include "include_asm.h"
#include "overlays/1070-00/text_00254730.h"

/** Minimal observed prefix containing the predicate word at offset 0x0C. */
struct FieldWordPredicate0C
{
    u8 unk00[0xC];
    u32 unk0c;
};

/** Minimal observed input prefix containing a float at offset 0x04. */
struct FieldScalar04
{
    u8 unk00[4];
    float unk04;
};

/** Observed 28-byte record containing the advancement flag. */
struct FieldAdvanceRecord1C
{
    u8 unk00[0x16];
    u8 unk16_0 : 1;
    u8 unk16_1_7 : 7;
    u8 unk17[5];
};

/** Observed queue prefix containing the update flag, state, limit and index. */
struct FieldAdvanceQueue34
{
    u8 unk00[0x15];
    u8 unk15;
    u8 unk16[6];
    FieldAdvanceRecord1C* unk1c;
    u8 unk20[0x11];
    u8 unk31;
    u8 unk32;
    u8 unk33;
    union
    {
        u8 raw;
        struct
        {
            u8 bit0 : 1;
            u8 bits1_7 : 7;
        } bits;
    } unk34;
};

/** Minimal observed prefix containing a word at offset 0x18. */
struct FieldWord18
{
    u8 unk00[0x18];
    u32 unk18;
};

/** Minimal observed prefix containing a word at offset 0x3B4. */
struct FieldWord3B4
{
    u8 unk00[0x3B4];
    u32 unk3b4;
};

/** Minimal observed prefix containing the byte at offset 0x60. */
struct FieldByte60
{
    u8 unk00[0x60];
    u8 unk60;
};

/** Minimal observed prefix whose flag byte is at offset 0x20. */
typedef struct FieldClearFlag20
{
    u8 unk00[0x20];
    u8 unk20_0 : 1;
    u8 unk20_1_7 : 7;
} FieldClearFlag20;

/** Minimal observed prefix whose flag byte is at offset 0x39. */
typedef struct FieldSetFlag39
{
    u8 unk00[0x39];
    u8 unk39_0 : 1;
    u8 unk39_1 : 1;
    u8 unk39_2_7 : 6;
} FieldSetFlag39;

/** Minimal observed prefix whose flag byte is at offset 0x04. */
typedef struct FieldSetFlag04
{
    u8 unk00[4];
    u8 unk04_0 : 1;
    u8 unk04_1_7 : 7;
} FieldSetFlag04;

/** Minimal observed prefix whose flag byte is at offset 0x20. */
typedef struct FieldSetFlag20
{
    u8 unk00[0x20];
    u8 unk20_0 : 1;
    u8 unk20_1_7 : 7;
} FieldSetFlag20;

/** Partial receiver with a flag byte and six separately observed word slots. */
typedef struct FieldWordReset20
{
    u8 unk00[0x20];
    u8 unk20_0 : 1;
    u8 unk20_1_7 : 7;
    u8 unk21[0x11B];
    u32 unk13c;
    u8 unk140[0xC];
    u32 unk14c;
    u8 unk150[0xC];
    u32 unk15c;
    u8 unk160[0xC];
    u32 unk16c;
    u8 unk170[0xC];
    u32 unk17c;
    u8 unk180[0xC];
    u32 unk18c;
} FieldWordReset20;

/** Partial list element with a signed key and signed state byte. */
typedef struct FieldKeyedStateElementE4
{
    FieldListNode link;
    u8 unk0c[0xD8];
    s16 unke4;
    u8 unke6[0x17];
    s8 unkfd;
} FieldKeyedStateElementE4;

/** Partial record with a relative next offset and a trailing word discriminator. */
typedef struct FieldRelativeRecord18
{
    u32 unk00;
    u8 unk04[8];
    u32 unk0c;
    u8 unk10[8];
    u32 unk18;
} FieldRelativeRecord18;

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00254730);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00254FB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00255060);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00255180);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00255360);

bool func_002553D0(void* object, const void* input, float* zero_output, float* small_output)
{
    const FieldScalar04* state = (const FieldScalar04*)input;

    if (!(state->unk04 <= 0.0f))
    {
        *zero_output = 0.0f;
        *small_output = 0.05f;
        return true;
    }
    return false;
}

s32 func_00255410(void* object)
{
    return 16;
}

s32 func_00255420(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00255430);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00255460);

void func_002556A0(FieldRecordQueue* object)
{
    advance_record_queue(object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00255770);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00255880);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00255D20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00255FB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_002560D0);

void func_00256140(void* object)
{
    FieldByteFlags34* state = (FieldByteFlags34*)object;

    state->unk34_0 = 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00256160);

void func_002563A0(void* object)
{
    FieldAdvanceQueue34* state = (FieldAdvanceQueue34*)object;

    advance_record_queue(state);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00256470);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00256580);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00256A20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00256CB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00256DD0);

void func_00256E40(void* object)
{
    FieldByteFlags34* state = (FieldByteFlags34*)object;

    state->unk34_0 = 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00256E60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00256F20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00257000);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_002570E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_002570F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00257100);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00257110);

s32 func_00257120(void* object)
{
    return 9;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00257130);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00257160);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_002571B0);

void func_00258310(void* object)
{
    FieldSetFlag04* state = (FieldSetFlag04*)object;

    state->unk04_0 = 1;
}

void func_00258330(void* object)
{
    FieldSetFlag39* state = (FieldSetFlag39*)object;

    state->unk39_1 = 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00258350);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_002583F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00258940);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00258950);

void func_002589F0(void* object, u32 value)
{
    FieldWord18* state = (FieldWord18*)object;

    state->unk18 = value;
}

void func_00258A00(void* object)
{
    FieldClearFlag20* state = (FieldClearFlag20*)object;

    state->unk20_0 = 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00258A20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00258A80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00258CC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00258E00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00258EA0);

void func_002590D0(void* object)
{
    FieldSetFlag20* state = (FieldSetFlag20*)object;

    state->unk20_0 = 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_002590F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00259180);

void func_00259220(void* object)
{
    FieldWordReset20* state = (FieldWordReset20*)object;

    state->unk20_0 = 0;
    state->unk13c = 0;
    state->unk14c = 0;
    state->unk15c = 0;
    state->unk16c = 0;
    state->unk17c = 0;
    state->unk18c = 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00259260);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_002592B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00259450);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00259600);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_002596E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_002597A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00259920);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_002599F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00259AC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00259BA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00259DC0);

s32 func_00259E20(const FieldKeyedFlagOwnerD8* object, u32 key)
{
    FieldListNode* node;
    FieldKeyedFlagList14* list = object->unkd8;
    FieldListNode* sentinel = &list->unk14;
    node = sentinel;
    for (;;)
    {
        node = node->next;
        if (node == 0 || sentinel == node)
        {
            break;
        }
        FieldKeyedFlagElement28* element = (FieldKeyedFlagElement28*)node;
        if (key == element->unk28)
        {
            return element->unk2c_0;
        }
    }
    return 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00259E70);

void func_00259EC0(FieldKeyedFlagOwnerD8* object, u32 key, s32 value)
{
    FieldListNode* sentinel = &object->unkd8->unk14;
    FieldListNode* node = sentinel;
    for (;;)
    {
        node = node->next;
        if (node == 0 || sentinel == node)
        {
            break;
        }
        FieldKeyedFlagElement28* element = (FieldKeyedFlagElement28*)node;
        if (key == element->unk28)
        {
            func_001E7020(element, value);
            break;
        }
    }
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00259F10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00259FD0);

s32 func_0025A040(const FieldKeyedFlagOwnerD8* object, s32 key)
{
    const FieldListNode* node = &object->unkdc;
    const FieldListNode* sentinel = node;
    for (;;)
    {
        node = node->next;
        bool absent = !node;
        if (absent || sentinel == node)
        {
            break;
        }
        const FieldKeyedStateElementE4* element = (const FieldKeyedStateElementE4*)node;
        if (key == element->unke4)
        {
            bool active;
            if (element->unkfd <= 0 || element->unkfd >= 6)
            {
                active = false;
            }
            else
            {
                active = true;
            }
            if (active)
            {
                return 1;
            }
        }
    }
    return 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025A0C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025A230);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025A410);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025A6E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025A770);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025A7D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025A830);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025A9A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025AA30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025AC80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025B0F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025B2D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025B370);

FieldFloatRecord16* func_0025BB50(FieldFloatRecord16* object)
{
    object->unk00 = object->unk04 = object->unk08 = object->unk0c = 0.0f;
    return object;
}

void func_0025BB70(FieldMirroredFlags* object, u32 value)
{
    object->unk1dc = value;
    object->unk1f6_1 = (value & 0x2) != 0;
}

void func_0025BBA0(FieldMirroredFlags* object, void* data, u32 flags)
{
    object->unk1f6_0 = 0;
    object->unk1d0 = data;
    object->unk1dc = flags;
    object->unk1f6_1 = (flags & 0x2) != 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025BBF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025BDD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025BE50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025C0A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025C1E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025C290);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025C2D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025C360);

s32 func_0025C390(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025C3A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025C3B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025C3C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025C3D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025C3E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025C4C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025C580);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025C5A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025C620);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025C650);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025C700);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025CE20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025DDD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025E7F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025E9A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025E9E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025EB20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025FC90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_0025FDC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00260140);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00260C60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00260CA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00260D40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_002610C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_002611C0);

void func_00261470(void* object)
{
    FieldSetFlag04* state = (FieldSetFlag04*)object;

    state->unk04_0 = 1;
}

s32 func_00261490(void* object)
{
    return 3;
}

void func_002614A0(void* object)
{
    FieldByte60* state = (FieldByte60*)object;

    state->unk60 = 9;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_002614B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_002614C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_002614D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_002614E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00261590);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_002617A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00261940);

void func_00261A00(void* object, u32 value)
{
    FieldWord3B4* state = (FieldWord3B4*)object;

    state->unk3b4 = value;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00261A10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00261BF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00261D90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00261DD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00261F40);

bool func_00261FC0(const void* object)
{
    const FieldWordPredicate0C* state = (const FieldWordPredicate0C*)object;

    return state->unk0c != 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00261FD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00261FE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00261FF0);

s32 func_00262000(const void* source)
{
    const FieldRelativeRecord18* record = (const FieldRelativeRecord18*)source;
    for (;;)
    {
        if (record->unk00 == 0x53414648)
        {
            break;
        }
        record = record->unk0c == 0 ? 0 : (const FieldRelativeRecord18*)((const u8*)record + record->unk0c);
        if (record == 0)
        {
            return 0;
        }
    }
    return record->unk18 == 8;
}

void func_00262060(FieldPointerReset66* object)
{
    object->unk14 = 0;
    object->unk18 = 0;
    object->unk66_1 = 0;
    object->unk10 = 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00262090);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00262160);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_002621B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_002623D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00262AA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00262CF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00262E40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00262FC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_002630E0);

FieldKeyedListElement54* func_00263230(FieldKeyedFloatState98* object, u32 key)
{
    FieldListNode* node = &object->link;
    for (;;)
    {
        node = node->next;
        if (&object->link == node)
        {
            break;
        }
        if (key == ((FieldKeyedListElement54*)node)->unk54)
        {
            return (FieldKeyedListElement54*)node;
        }
    }
    return 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00263280);

void func_00263B20(FieldKeyedFloatState98* object, u32 key, u16 flags, float first, float second, float third, float fourth, float fifth)
{
    object->unkac = 300.0f;
    object->unk98 = key;
    object->unk9c = first;
    object->unka0 = second;
    object->unka8 = third;
    object->unkb0 = fourth;
    object->unkb8 = 2;
    object->unkb4 = (object->unkb4 & ~0xFF) | flags;
    object->unka4 = fifth;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00263B70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00263CA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00263D30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00263E50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00263EA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00264090);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_002640E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00264210);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_002642A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_002643C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00264410);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00264490);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00254730", func_00264680);
