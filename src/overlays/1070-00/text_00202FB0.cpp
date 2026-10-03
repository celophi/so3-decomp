#include "include_asm.h"
#include "vu0.h"
#include "overlays/1070-00/text_00202FB0.h"

/** Partial list element with a word key at offset 0x54. */
typedef struct FieldKeyListElement54
{
    FieldFlagListElement base;
    u8 unk50[4];
    u32 unk54;
} FieldKeyListElement54;

/** Partial list element with a word key at offset 0x270. */
typedef struct FieldKeyListElement270
{
    FieldFlagListElement base;
    u8 unk50[0x220];
    u32 unk270;
} FieldKeyListElement270;


static inline FieldStateListElement3C* find_state_element(FieldContext34* object, s32 key);

/**
 * @brief Find the first element whose signed key matches the supplied key.
 * @param object Receiver containing the circular list.
 * @param key Signed key to find.
 * @return The matching element, or null at the sentinel.
 */
static inline FieldStateListElement3C* find_state_element(FieldContext34* object, s32 key)
{
    FieldListNode* node = &object->unk14;
    for (;;)
    {
        node = node->next;
        if (&object->unk14 == node)
        {
            break;
        }
        if (key == ((FieldStateListElement3C*)node)->unk3c)
        {
            return (FieldStateListElement3C*)node;
        }
    }
    return 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00202FB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00203070);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_002030C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00203110);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00203180);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_002033C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00203450);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_002034D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_002035B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00203690);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_002036C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00203750);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00203770);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00203810);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00203850);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00203890);

s32 func_00203900(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00203910);

/**
 * @brief Clear bit six of the receiver's flag word at offset 0x204.
 * @param object Receiver whose flag is cleared.
 */
void func_00203920(FieldWordFlags204* object)
{
    object->unk204 &= ~0x40;
}

void func_00203940(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00203950);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_002039C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_002039D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_002039E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_002039F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00203A00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00203B90);

bool func_00203BE0(const FieldByteFlags81* object)
{
    return object->unk81_0 != 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00203BF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00203CA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00203DD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00204120);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00204190);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00204230);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00204290);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00204300);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_002043B0);

s32 func_00204470(void* object)
{
    return 2;
}

void func_00204480(FieldRecordQueue* object)
{
    if (object->unk1c != 0)
    {
        for (s32 index = 0; index < object->unk24; index++)
        {
            FieldRecord1C* record = &object->unk1c[index];
            record->unk0c = -1;
            record->unk04 = 0;
            record->unk10 = 0;
            record->unk16_0 = 0;
            record->unk16_1 = 1;
            record->unk08_0 = 0;
            record->unk16_2 = 0;
            record->unk14 = 0;
            record->unk15 = 0;
        }
    }
    object->unk20 = 0;
    object->unk33 = 0;
    object->unk31 = 0;
    object->unk32 = 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00204550);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00204580);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00204870);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00204AD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00205090);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_002050D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00205260);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00205410);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00205480);

FieldRecord1C* func_00205620(FieldRecord1C* record)
{
    record->unk0c = -1;
    record->unk04 = 0;
    record->unk10 = 0;
    record->unk16_0 = 0;
    record->unk16_1 = 1;
    record->unk08_0 = 0;
    record->unk16_2 = 0;
    record->unk14 = 0;
    record->unk15 = 0;
    return record;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_002056A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00205710);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_002057A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00205840);

u8 func_002058A0(FieldContext34* object, s32 key)
{
    FieldStateListElement3C* found = find_state_element(object, key);
    if (found == 0)
    {
        return 0xFE;
    }
    return found->unk15;
}

FieldStateListElement3C* func_002058F0(FieldContext34* object, s32 key, s32 unused)
{
    return find_state_element(object, key);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00205930);

s32 func_002059A0(void* object)
{
    return 3;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_002059B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00205A70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00205B10);

s32 func_00205BD0(void* object)
{
    return 3;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00205BE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00205C10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00205E50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00205F20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00206030);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_002064D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00206760);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00206880);

/**
 * @brief Set bit zero of the receiver's flag byte at offset 0x34.
 * @param object Receiver whose flag is set.
 */
void func_002068F0(FieldByteFlags34* object)
{
    object->unk34_0 = 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00206910);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_002069A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00206A80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00206A90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00206AA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00206AB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00206B70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00206BB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00206BC0);

void func_00206BD0(void* object)
{
}

void func_00206BE0(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00206BF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00206C10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00206CA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00206D10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00206DC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00206EA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00206FC0);

/**
 * @brief Preserve the prior state, select state three, and update the adjacent flags.
 * @param object Receiver whose state and flags are updated.
 * @param value Value whose low byte is stored at offset 0x323.
 */
void func_00207020(FieldStateBytes321* object, u32 value)
{
    object->unk322 = object->unk321;
    object->unk321 = 3;
    object->unk324_0 = 0;
    object->unk323 = value;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00207050);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_002071F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00207310);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_002074B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_002075F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00207630);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00207830);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00207A60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00207AE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00207CC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00207D10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00207DB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00207E10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00207EE0);

void func_00207FE0(FieldFlagElement6D* object)
{
    object->base.unk4c_2 = 0;
    object->base.unk24 = -3;
    object->unk6d_1 = 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00208020);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00208170);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00208200);

void func_002082E0(FieldFlagElement69* object)
{
    object->base.unk4c_2 = 0;
    object->base.unk24 = -3;
    object->unk69_1 = 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00208320);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_002083B0);

void func_002085D0(FieldFlagVectorElement* object, u32 value14,
    const unsigned __int128* value280, const unsigned __int128* value290,
    u32 value18, s32 value28, s32 value2c, s32 value30)
{
    object->base.unk28 = value28;
    object->base.unk2c = value2c;
    object->base.unk30 = value30;
    object->base.unk14 = value14;
    object->base.unk18 = value18;
    object->unk280 = *value280;
    object->unk290 = *value290;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00208600);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00208690);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_002087F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00208870);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00208B70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00208D10);

void func_00208E70(FieldFlagListElement* object, u32 value14, u32 value18,
    s32 value28, s32 value34, s32 value2c, s32 value30)
{
    object->unk14 = value14;
    object->unk18 = value18;
    object->unk28 = value28;
    object->unk34 = value34;
    object->unk2c = value2c;
    object->unk30 = value30;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00208E90);

void func_00208EF0(FieldFlagListElement* object)
{
    object->unk4c_2 = 0;
    object->unk24 = -3;
}

void func_00208F20(FieldContext58* object)
{
    FieldListNode* node = &object->unk14;
    for (;;)
    {
        node = node->next;
        if (&object->unk14 == node)
        {
            break;
        }
        ((FieldFlagListElement*)node)->unk4c_2 = 1;
    }
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00208F60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00208FC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_002090B0);

s32 func_002091E0(FieldContext58* object)
{
    FieldListNode* node = &object->unk14;
    for (;;)
    {
        node = node->next;
        if (&object->unk14 == node)
        {
            break;
        }
        s32 nonnegative = ((FieldFlagListElement*)node)->unk24 > -1;
        if (nonnegative)
        {
            return 1;
        }
    }
    return 0;
}

void func_00209230(FieldContext58* object, u32 key)
{
    enum
    {
        FIELD_LIST_FLAG_1 = 0x2,
        FIELD_LIST_FLAG_3 = 0x8
    };
    FieldListNode* node = &object->unk14;
    for (;;)
    {
        node = node->next;
        if (&object->unk14 == node)
        {
            break;
        }
        FieldFlagListElement* element = (FieldFlagListElement*)node;
        if (element->unk1c & FIELD_LIST_FLAG_1)
        {
            if (key == ((FieldKeyListElement54*)element)->unk54)
            {
                element->unk4c_0 = 1;
            }
        }
        else if (element->unk1c & FIELD_LIST_FLAG_3)
        {
            if (key == ((FieldKeyListElement270*)element)->unk270)
            {
                element->unk4c_0 = 1;
            }
        }
    }
}

void func_002092C0(FieldContext58* object)
{
    FieldListNode* node = &object->unk14;
    for (;;)
    {
        node = node->next;
        if (&object->unk14 == node)
        {
            break;
        }
        ((FieldFlagListElement*)node)->unk4c_0 = 1;
    }
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00209300);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00209330);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_002093C0);

FieldRecord18* func_002096A0(FieldRecord18* record)
{
    record->unk0c = -1;
    record->unk04 = 0;
    record->unk10 = 0;
    record->unk16_0 = 0;
    record->unk16_1 = 1;
    record->unk08_0 = 0;
    record->unk16_2 = 0;
    record->unk14 = 0;
    record->unk15 = 0;
    return record;
}

void func_00209720(FieldRecordQueue18* object)
{
    if (object->unk1c != 0)
    {
        for (s32 index = 0; index < object->unk24; index++)
        {
            FieldRecord18* record = &object->unk1c[index];
            record->unk0c = -1;
            record->unk04 = 0;
            record->unk10 = 0;
            record->unk16_0 = 0;
            record->unk16_1 = 1;
            record->unk08_0 = 0;
            record->unk16_2 = 0;
            record->unk14 = 0;
            record->unk15 = 0;
        }
    }
    object->unk20 = 0;
    object->unk33 = 0;
    object->unk31 = 0;
    object->unk32 = 0;
}

void func_002097F0(FieldContext58* object, void* value, s32 unused)
{
    object->unk1d0 = object->unk1cc;
    object->unk1cc = value;
    object->unk1ec = 1;
}

s32 func_00209810(const FieldContext58* object, s8 index)
{
    const FieldContext58Entry* entry = &object->unkb0[index];
    if (entry->unk16_2 != 0)
    {
        return 1;
    }
    if (entry->unk16_0 != 0)
    {
        return 2;
    }
    return 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00209860);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00209B60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00209CA0);

FieldFlagListElement* func_00209E40(FieldContext58* object, u32 key)
{
    FieldListNode* node = &object->unk14;
    for (;;)
    {
        node = node->next;
        if (node == 0 || &object->unk14 == node)
        {
            break;
        }
        if (key == ((FieldFlagListElement*)node)->unk14)
        {
            return (FieldFlagListElement*)node;
        }
    }
    return 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00209E90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_00209EF0);

void func_00209F50(FieldFlagListElement* object)
{
    if (object->unk4c_4 == 0)
    {
        object->unk4c_0 = 1;
    }
    else
    {
        object->unk4c_2 = 1;
    }
}

void func_00209FA0(FieldContext58* object, u32 key, u32 value38, u32 value44, u32 value3c, u32 value40)
{
    FieldListNode* node = &object->unk14;
    for (;;)
    {
        node = node->next;
        if (&object->unk14 == node)
        {
            break;
        }
        FieldFlagListElement* element = (FieldFlagListElement*)node;
        if (key == element->unk14)
        {
            element->unk38 = value38;
            element->unk44 = value44;
            element->unk3c = value3c;
            element->unk40 = value40;
            element->unk4c_1 = 1;
            element->unk48 = 5;
            break;
        }
    }
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020A000);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020A050);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020A0D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020A170);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020A9D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020AA00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020ABF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020AD50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020AEF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020AFF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020B120);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020B1A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020B1D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020B2E0);

s32 func_0020B400(void* object)
{
    return 2;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020B410);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020B440);

void func_0020B680(FieldRecordQueue18* object)
{
    advance_record_queue(object);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020B750);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020B860);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020BD00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020BF90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020C0B0);

void func_0020C120(FieldRecordQueue18* object)
{
    object->unk34.bits.bit0 = 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020C140);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020C2E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020C3C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020C3D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020C3E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020C3F0);

s32 func_0020C480(void* object)
{
    return 2;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020C490);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020C760);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020C7F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020C930);

void* func_0020CBC0(const FieldContext08Target* object)
{
    return object->unk7c;
}

FieldContext08Target* func_0020CBD0(const FieldContext08* object)
{
    return object->unkdc;
}

FieldContext08* func_0020CBE0(const FieldContextRef* ref)
{
    return ref->context->unk08;
}

void func_0020CBF0(FieldVectorProduct560* object, const unsigned __int128* source)
{
    object->unk560 = *source;
    vu0_multiply_xyzw(&object->unk580, &object->unk560, &object->unk570);
}

u16 func_0020CC20(const FieldObjectFlags* object)
{
    return object->unk6e;
}

void func_0020CC30(FieldVector* out, const FieldVector* left, const FieldVector* right)
{
    vu0_multiply_xyzw(out, left, right);
}

void func_0020CC50(unsigned __int128* out, const unsigned __int128* source)
{
    *out = *source;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020CC60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020CCB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020CD40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020CE90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020CF70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020D0F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020D240);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020D390);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020D3E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020D410);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020D670);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020D760);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020D7B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020D810);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020DAE0);

void func_0020DC30(void* object, FieldBytePair* pair, s8 first, s8 second)
{
    if (pair != 0)
    {
        pair->unk08 = first;
        pair->unk09 = second;
    }
}

void func_0020DC50(FieldBytePairOwner* object)
{
    object->unk590_0 = 1;
    object->unk590_1 = 1;
    object->unk58d = 4;
    object->unk570 = 40.0f;
    FieldBytePair* pair = object->unk448;
    if (pair != 0)
    {
        pair->unk08 = 0;
        pair->unk09 = 0;
    }
    func_0020D240(object);
    func_0020D810(object, 70.0f);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020DCE0);

/**
 * @brief Test two nonzero words and the cleared bit-five flag at offset 0x8C.
 * @param object Receiver to inspect.
 * @return One when both words are nonzero and the flag is clear, otherwise zero.
 */
s32 func_0020DDA0(const FieldWordFlags8C* object)
{
    if (object->unk80 == 0 || object->unk448 == 0 || object->unk8c_5 != 0)
    {
        return 0;
    }
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020DDF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020E600);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020E850);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020EA40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020EA80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020EB10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020EE70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020EF10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020F180);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020F380);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020F450);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020F5A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020F600);

/**
 * @brief Conditionally set flag bit five according to whether the supplied value is zero.
 * @param object Receiver whose flag byte is updated.
 * @param value Zero to set the flag, or a nonzero value to clear it.
 * @param update Nonzero to update the flag, or zero to preserve it.
 */
void func_0020F6D0(FieldByteFlags8C* object, u32 value, u32 update)
{
    if (update != 0)
    {
        object->unk8c_5 = !value;
    }
}

/**
 * @brief Copy an aligned 16-byte value when the source is present.
 * @param object Receiver containing the aligned destination value.
 * @param source Aligned value to copy, or null to preserve the destination.
 */
void func_0020F710(FieldAlignedValue20* object, const unsigned __int128* source)
{
    if (source != 0)
    {
        object->unk20 = *source;
    }
}

/**
 * @brief Set bit one of the pointed-to receiver's flag byte at offset 0x2C.
 * @param object Owner of the receiver whose flag is set.
 */
void func_0020F730(FieldFlags2COwner* object)
{
    object->unk04->unk2c_1 = 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020F750);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020F840);

/**
 * @brief Set bit zero of the pointed-to receiver's flag byte at offset 0x7AF.
 * @param object Owner of the receiver whose flag is set.
 */
void func_0020FAC0(FieldFlags7AFOwner* object)
{
    object->unk04->unk7af_0 = 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020FAE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020FBF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020FCF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020FE70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020FF40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00202FB0", func_0020FFE0);
