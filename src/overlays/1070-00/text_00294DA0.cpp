#include "include_asm.h"
#include "overlays/1070-00/text_00294DA0.h"
#include "overlays/1070-00/text_00284BF0.h"
#include "overlays/1070-00/text_002B4F20.h"
#include "ee.h"
#include "vu0.h"

// These resident interfaces use the build addresses expected by this overlay.
struct RequestQueue;

/** Partial request guard containing its blocking byte. */
struct FieldRequestGuard6610
{
    u8 unk00[0xF17B];
    u8 unkf17b;
};

extern "C" void* func_100CA0(void* heap);
extern "C" void func_100CB0(void* storage);
extern "C" void func_452C90(void* object, s32 count, FieldScaleEntry296670* entries);
extern "C" RequestQueue* D_001B6614;
extern "C" FieldContextRef* D_001B64B0;
extern "C" const char D_335660[];
extern "C" const char D_335680[];
extern "C" const char D_3356F0[];
extern "C" const char D_3356D0[];
extern "C" const char D_335690[];
extern "C" const char D_3356B0[];
extern "C" void func_13DAA0(s32 value);
extern "C" FieldRequestGuard6610* D_001B6610;
extern "C" s32 func_102D90(RequestQueue* queue);
extern "C" void func_103FD0(void* queue, s32 handle, u32 address, u32 flags, u32 byte_count, u32 argument);
extern "C" void func_104320(RequestQueue*, s32, u32, u32, s32, FieldRequestObserver294DA0*, u32, s32, u64);
extern "C" u32 func_103AF0(RequestQueue*, s32, u32, u32, u32, s32);
extern "C" void func_139128(const char*, ...);

extern "C" void func_4EA000(FieldQuad128* vector);

extern "C" float D_001B66B4;
extern "C" u8 D_001B64CC;
extern "C" float D_001B66BC;
extern "C" u8 func_43E360(void* object, void* context);
extern "C" void func_428520(void* object);
extern "C" void func_426AD0(void* object);
extern "C" void func_424F20(void* object);
extern "C" void func_425100(void* object);
extern "C" void* D_001B6554;
extern "C" u8 D_001B6560;
extern "C" void func_460160();
extern "C" s32 func_45FF30(u32 value, s32 size);
extern "C" s32 func_460280(s32 size, u32 value);

/** Observed context prefix containing its control byte at offset 7. */
struct FieldByteState07
{
    u8 unk00[7];
    u8 unk07;
};

extern "C" void* func_10E3B0();
extern "C" void* func_101570(void* value);
extern "C" FieldByteState07* func_101720(void* value, s32 index);

/** Bit view of the context control byte at offset 0xDD. */
struct FieldFlagsDD
{
    u8 bits0_5 : 6;
    u8 bit6 : 1;
    u8 bit7 : 1;
};

extern "C" void func_115C20(s32 arg0, const char* file, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                            s32 arg6);

/** The string "progparticles.h". */
extern "C" char D_3357D0[];

void func_00294DA0(FieldRequestState294DA0* object)
{
    FieldEntry1C* entry = &object->unk1c[object->unk32];
    if (entry->rounded_unk04())
    {
        func_104320(D_001B6614, entry->unk0c, entry->rounded_unk04(), 0x80000000,
                    object->unk28, static_cast<FieldRequestObserver294DA0*>(object), entry->byte_count(), 0, 1);
        entry->unk10 = func_103AF0(D_001B6614, entry->unk0c, entry->rounded_unk04(), 0x80000000, entry->byte_count(), 0);
        func_139128(D_335660, entry->unk0c, entry->rounded_unk04(), entry->rounded_unk04() + entry->byte_count(), entry->byte_count());
        if (object->unk2c != -1)
        {
            func_002BAF30(D_001B64B0->context->unke4, object->unk2c);
        }
        object->unk2c = func_002BAFB0(D_001B64B0->context->unke4, D_335680, &object->unk15, 1);
        object->unk15 = 1;
    }
}

void func_00294FE0(FieldFlagState34* object)
{
    if ((*(const u8*)&object->unk34 & 1) != 0)
    {
        object->unk34.bits.bit0 = 0;
        if (object->unk15 == 1)
        {
            while (object->unk32 < object->unk31)
            {
                object->unk32++;
                if (!object->unk1c[object->unk32].unk16_0)
                {
                    break;
                }
            }
            if (object->unk32 >= object->unk31)
            {
                object->unk15 = 5;
            }
            else
            {
                object->unk15 = 0;
            }
        }
    }
}

/** Release the allocation prefix of a nonnull entry buffer. */
static inline void release_buffer(void* buffer)
{
    if (buffer)
    {
        func_100CB0((u8*)buffer - 0x10);
    }
}
FieldClass16C970::~FieldClass16C970()
{
    if (unk1c)
    {
        func_slot48();
        release_buffer(unk1c);
        unk1c = 0;
    }
    if (unk2c != -1)
    {
        func_002BAF30(D_001B64B0->context->unke4, unk2c);
    }
}

void FieldClass16C970::func_slot1c(s32 flag)
{
    switch (unk15)
    {
    case 0:
        if (!flag && unk1c)
        {
            func_13DAA0(0);
            FieldEntry1C* record = &unk1c[unk32];
            s32 size = func_002069A0(this, record->unk00 + 0x80, 1);
            if (size)
            {
                record->unk04 = size;
                record->unk08_0 = 0;
                func_slot3c();
            }
        }
        break;
    case 1:
        if (flag == 1)
        {
            for (s32 i = 0; i < unk31; i++)
            {
                FieldEntry1C* record = &unk1c[i];
                u32 word = record->unk00;
                u32 size = record->rounded_unk04();
                func_103FD0(D_001B6614, record->unk0c, size, 0x80000000, word, 0);
            }
            unk15 = 9;
        }
        else
        {
            FieldEntry1C* record = &unk1c[unk32];
            u32 word = record->unk00;
            u32 size = record->rounded_unk04();
            if (!func_103AF0(D_001B6614, record->unk0c, size, 0x80000000, word, 0))
            {
                func_slot0c(0);
            }
        }
        break;
    case 9:
        if (!flag)
        {
            func_slot3c();
        }
        break;
    case 10:
    {
        bool done = true;
        FieldEntry1C* records = unk1c;
        for (s32 i = 0; i < unk31; i++)
        {
            FieldEntry1C* record = &records[i];
            u32 word = record->unk00;
            u32 size = record->rounded_unk04();
            record->unk10 = func_103AF0(D_001B6614, record->unk0c, size, 0x80000000, word, 0);
            if (record->unk10)
            {
                done = false;
            }
        }
        if (D_001B6610->unkf17b || func_102D90(D_001B6614))
        {
            done = false;
        }
        if (done)
        {
            for (s32 i = 0; i < unk24; i++, records++)
            {
                func_0021A970(records);
            }
            unk32 = 0;
            unk15 = 0;
            func_139128(D_335690);
        }
        break;
    }
    case 7:
    {
        bool done = true;
        FieldEntry1C* record = unk1c;
        for (s32 i = 0; i < unk31; i++, record++)
        {
            u32 word = record->unk00;
            u32 size = record->rounded_unk04();
            record->unk10 = func_103AF0(D_001B6614, record->unk0c, size, 0x80000000, word, 0);
            if (record->unk10)
            {
                done = false;
            }
        }
        if (D_001B6610->unkf17b || func_102D90(D_001B6614))
        {
            done = false;
        }
        if (done)
        {
            if (unk10)
            {
                func_4D7EB0(this);
            }
            func_slot10();
            func_139128(D_3356B0);
        }
        break;
    }
    }
    func_slot40();
}

s32 FieldClass16C970::func_slot20()
{
    s32 result = 0;
    FieldEntry1C* entries = unk1c;
    switch (unk15)
    {
    case 1:
    {
        for (s32 i = 0; i < unk31; i++)
        {
            FieldEntry1C* entry = &entries[i];
            if (!entry->unk08_0)
            {
                func_103FD0(D_001B6614, entry->unk0c, entry->rounded_unk04(),
                    0x80000000, entry->byte_count(), 0);
            }
        }
        unk15 = 10;
        break;
    }
    case 10:
        break;
    case 9:
        if (D_001B6610->unkf17b || func_102D90(D_001B6614))
        {
            break;
        }
    default:
    {
        for (s32 i = 0; i < unk31; i++)
        {
            if (entries[i].rounded_unk04())
            {
                result = 1;
                break;
            }
        }
        for (s32 i = 0; i < unk24; i++)
        {
            func_0021A970(&entries[i]);
        }
        unk15 = 0;
        unk32 = 0;
        break;
    }
    }
    if (result != 1)
    {
        for (s32 i = 0; i < unk31; i++)
        {
            if (entries[i].rounded_unk04())
            {
                result = 2;
                break;
            }
        }
    }
    if (result == 1)
    {
        func_139128(D_3356D0);
    }
    return result;
}

s32 FieldClass16C970::func_slot24()
{
    if (unk15 != 1)
    {
        if (unk10)
        {
            func_4D7EB0(this);
        }
        func_slot10();
        func_139128(D_3356F0);
        return 1;
    }
    FieldEntry1C* entry = unk1c;
    for (s32 i = 0; i < unk31; i++, entry++)
    {
        if (!entry->unk08_0)
        {
            func_103FD0(D_001B6614, entry->unk0c, entry->rounded_unk04(),
                0x80000000, entry->byte_count(), 0);
        }
    }
    unk15 = 7;
    return 0;
}

void func_00295A10(FieldEntryArray295A10* object)
{
    s32 i;

    for (i = 0; i < object->unk24; i++)
    {
        func_0021A970(&object->unk1c[i]);
    }
}

void func_00295A80(FieldFlagState34* object)
{
    object->unk34.bits.bit0 = 1;
}

s32 func_00295AA0(FieldRetryState295AA0* object, u32 value, s32 mode)
{
    FieldReceiver21AB20* receiver = static_cast<FieldReceiver21AB20*>(object->unk10);
    for (s32 attempt = 0; attempt < 8; attempt++)
    {
        s32 result;
        if (mode)
        {
            func_460160();
            result = func_45FF30(value, 0x40);
        }
        else
        {
            result = func_460280(0x80, value);
        }
        if (result)
        {
            return result;
        }
        if (receiver->unk0c == 1 || !func_0021AB20(receiver, object))
        {
            break;
        }
    }
    return 0;
}

void FieldClass172110::func_slot10()
{
    delete this;
}

s32 FieldClass172110::func_slot0c()
{
    return 4;
}

FieldClass172110::~FieldClass172110()
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00294DA0", func_slot0c__16FieldClass172110FPv);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00294DA0", func_slot14__16FieldClass172110Fv);

void func_00296190(FieldValueFlagState18* object, s32 value)
{
    object->unk18 = value;
    object->unk25_0 = 0;
    ((FieldFlagsDD*)&D_001B64B0->context->unkdd)->bit6 = 1;
}

FieldClass172110::FieldClass172110()
{
    unk24 = 0;
    unk20 = 60.0f;
    unk25_1 = 0;
    unk25_0 = 0;
    FieldByteState07* state = func_101720(func_101570(func_10E3B0()), 4);
    s32 flags = state->unk07;
    flags &= ~4;
    state->unk07 = flags;
}

void FieldClass172140::func_slot10()
{
    delete this;
}

s32 FieldClass172140::func_slot0c()
{
    return 4;
}

void FieldClass172140::func_00296310(float first, float second, float third)
{
    unk20 = second;
    unk24 = first;
    unk28 = unk20 - unk24;
    unk2c = third;
    unk30 = 0.0f;
    unk34 = 1.0f;
    unk38_0 = 1;
    unk38_1 = 0;
}

void FieldClass172140::func_slot14()
{
    if (unk38_0 && !unk38_1)
    {
        unk30 += D_001B66B4;
        if (!(unk30 < unk2c))
        {
            unk34 = unk20;
            unk38_1 = 1;
        }
        else
        {
            unk34 = unk24 + unk28 * func_002166F0(&curve, unk30 / unk2c);
        }
    }
}

FieldClass172170::~FieldClass172170()
{
}

FieldClass173568::~FieldClass173568()
{
    if (unk0c)
    {
        func_100CB0(unk0c - 0x10);
    }
}

s32 func_00296570(void* object)
{
    return 5;
}

/**
 * @brief Advance an enabled countdown and report when it reaches zero.
 * @param delay Countdown to advance; a negative value disables it.
 * @return True when the countdown is active and has elapsed.
 */
static inline bool update_delay(float& delay)
{
    if (delay < 0.0f)
    {
        return false;
    }
    if (delay > 0.0f)
    {
        delay -= D_001B66B4;
        if (delay > 0.0f)
        {
            return false;
        }
        delay = 0.0f;
    }
    return true;
}

void func_00296580(FieldDelayState50* object)
{
    float previous = object->delay;
    if (update_delay(object->delay))
    {
        if (previous > 0.0f)
        {
            func_428520(object);
        }
        func_426AD0(object);
    }
}

u8 func_00296620(void* object, void* context)
{
    float previous = D_001B66BC;
    u8 result;
    if (D_001B64CC)
    {
        D_001B66BC = 1.0f / 60.0f;
    }
    result = func_43E360(object, context);
    D_001B66BC = previous;
    return result;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00294DA0", func_00296670);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00294DA0", func_00296870);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00294DA0", func_00297A30);

FieldInitialWordPair* func_00297E10(FieldInitialWordPair* object)
{
    object->unk00 = 0x40A00000;
    object->unk04 = -1;
    return object;
}

FieldClass179470::FieldClass179470()
{
    unk14 = 0;
    unk16 = 0;
    unk1a = 0;
    unk24 = 0;
    unk28 = 0;
    unk2c = 0;
    unk30 = 0;
    unk40 = 0;
    unk44 = 0;
    unk48 = 0;
    unk4c = 0;
    unk1c = D_001B6554;
    unk1b = D_001B6560;
    unk0f |= 4;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00294DA0", func_00297ED0);

void func_00297F40(FieldDelayState230* object)
{
    if (update_delay(object->delay))
    {
        func_424F20(object);
    }
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00294DA0", func_00297FC0);

void func_00298030(FieldDelayState240* object)
{
    if (update_delay(object->delay))
    {
        func_425100(object);
    }
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00294DA0", func_002980B0);

void func_00298120(FieldScaleOwnerD0* object, s32 count, FieldScaleEntry296670* entries)
{
    func_452C90(object, count, entries);
    func_00296670(&object->unkd0, entries, count, object->unk2c, object->unk10, object->unk0c, object->unk1c->unk08);
}

void func_00298180(void* object, s32 count, s32 group_size)
{
    void* previous = func_100CA0(0);
    func_002AA770(object, count, group_size);
    func_100CA0(previous);
}

FieldClass172390::~FieldClass172390()
{
}

void func_00298280(FieldScaleOwnerC0* object, s32 count, FieldScaleEntry296670* entries)
{
    func_002AC070(object, count, entries);
    func_00296670(&object->unkc0, entries, count, object->unk2c, object->unk10, object->unk0c, object->unk1c->unk08);
}

void func_002982E0(void* object, s32 count, s32 group_size)
{
    void* previous = func_100CA0(0);
    func_002A97A0(object, count, group_size);
    func_100CA0(previous);
}

FieldClass172600::~FieldClass172600()
{
}

void func_002983E0(FieldScaleOwnerB0* object, s32 count, FieldScaleEntry296670* entries)
{
    func_002AC920(object, count, entries);
    func_00296670(&object->unkb0, entries, count, object->unk2c, object->unk10, object->unk0c, object->unk1c->unk08);
}

void func_00298440(void* object, s32 count, s32 group_size)
{
    void* previous = func_100CA0(0);
    func_002A9F70(object, count, group_size);
    func_100CA0(previous);
}

FieldClass172940::~FieldClass172940()
{
}

void func_00298540(FieldScaleOwnerB0* object, s32 count, FieldScaleEntry296670* entries)
{
    func_002AC070(object, count, entries);
    func_00296670(&object->unkb0, entries, count, object->unk2c, object->unk10, object->unk0c, object->unk1c->unk08);
}

void func_002985A0(void* object, s32 count, s32 group_size)
{
    void* previous = func_100CA0(0);
    func_002A97A0(object, count, group_size);
    func_100CA0(previous);
}

FieldClass172C80::~FieldClass172C80()
{
}

void func_002986A0(FieldScaleOwnerB0* object, s32 count, FieldScaleEntry296670* entries)
{
    func_002AB800(object, count, entries);
    func_00296670(&object->unkb0, entries, count, object->unk2c, object->unk10, object->unk0c, object->unk1c->unk08);
}

void func_00298700(void* object, s32 count, s32 group_size)
{
    void* previous = func_100CA0(0);
    func_002A8FF0(object, count, group_size);
    func_100CA0(previous);
}

FieldClass172FC0::~FieldClass172FC0()
{
}

void func_00298800(FieldScaleOwnerB0* object, s32 count, FieldScaleEntry296670* entries)
{
    func_002AAF90(object, count, entries);
    func_00296670(&object->unkb0, entries, count, object->unk2c, object->unk10, object->unk0c, object->unk1c->unk08);
}

void func_00298860(void* object, s32 count, s32 group_size)
{
    void* previous = func_100CA0(0);
    func_002A88E0(object, count, group_size);
    func_100CA0(previous);
}

s32 func_002988D0(FieldBytePointerA0* object)
{
    return *object->unka0 != 1;
}

FieldClass173230::~FieldClass173230()
{
}

void func_00298980(FieldScaleOwnerB0* object, s32 count, FieldScaleEntry296670* entries)
{
    func_002AAF90(object, count, entries);
    func_00296670(&object->unkb0, entries, count, object->unk2c, object->unk10, object->unk0c, object->unk1c->unk08);
}

void func_002989E0(void* object, s32 count, s32 group_size)
{
    void* previous = func_100CA0(0);
    func_002A88E0(object, count, group_size);
    func_100CA0(previous);
}

s32 func_00298A50(FieldBytePointerA0* object)
{
    return *object->unka0 != 1;
}

FieldClass173580::~FieldClass173580()
{
}

s32 func_00298AD0(void* object)
{
    return 35;
}

FieldClass1735A0::~FieldClass1735A0()
{
}

void func_00298B40(LibReceiver4A71F0* object)
{
    object->func_slot1c(17);
}

void func_00298B70(FieldParallelArrays298B70* object, u8 value, const unsigned __int128* data)
{
    if (object->unkc4 >= object->unkc0)
    {
        func_115C20(0xC8, D_3357D0, 0x47, object->unkc0, 0, 0, 0);
        return;
    }
    object->unkb0[object->unkc4] = value;
    if (data)
    {
        object->unkb4[object->unkc4] = *data;
    }
    object->unkc4++;
}

void func_00298C00(void* object)
{
}

s32 func_00298C10(void* object)
{
    return 1;
}

void func_00298C20(FieldParallelArrays298B70* object, u32 value)
{
    object->unkb8 = value;
}

u32 func_00298C30(FieldParallelArrays298B70* object)
{
    return object->unkb8;
}

void func_00298C40(FieldParallelArrays298B70* object, u32 value)
{
    object->unkbc = value;
}

u32 func_00298C50(FieldParallelArrays298B70* object)
{
    return object->unkbc;
}

void func_00298C60(FieldParallelArrays298B70* object, u8* value)
{
    object->unkb0 = value;
}

u8* func_00298C70(FieldParallelArrays298B70* object)
{
    return object->unkb0;
}

void func_00298C80(FieldParallelArrays298B70* object, unsigned __int128* value)
{
    object->unkb4 = value;
}

unsigned __int128* func_00298C90(FieldParallelArrays298B70* object)
{
    return object->unkb4;
}

s32 func_00298CA0(void* object)
{
    return 0;
}

s32 func_00298CB0(void* object)
{
    return 0;
}

void func_00298CC0(FieldHistoryReceiver298CC0* object, s32 capacity, FieldHistoryOutput30* output, u32 stamp)
{
    s32 samples = object->samples;
    s32 index = object->index;
    s32 limit = object->limit;
    const u64* masks = object->mask->unk08;
    u64 bit = (u64)1 << (index & 63);
    s32 mask_index = index / 64;
    s32 processed = 0;
    u64 mask = masks[mask_index++];
    switch (object->policy)
    {
        case 0:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes[3] = previous->attributes.data()[3];
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource170* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes[3] = source->attributes.data()[3];
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource170* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource170* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource170* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes[3] = previous->attributes.data()[3];
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource170* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes[3] = source->attributes.data()[3];
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource170* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource170* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource170* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
        case 1:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes[3] = previous->attributes.data()[3];
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource170* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes[3] = source->attributes.data()[3];
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource170* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource170* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource170* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes[3] = previous->attributes.data()[3];
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource170* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes[3] = source->attributes.data()[3];
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource170* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource170* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource170* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
        case 2:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySource170* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes[3] = previous->attributes.data()[3];
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes[3] = source->attributes.data()[3];
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySource170* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySource170* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySource170* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySource170* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes[3] = previous->attributes.data()[3];
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes[3] = source->attributes.data()[3];
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            FieldHistorySource170* source = &object->source[index - 1];
                            s32 history_index = index * (samples - 1) - 1;
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySource170* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySource170* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
    }
}

FieldEntryTail29B830* func_0029B830(FieldEntryOwner29B830* object, s32 index)
{
    return &object->unk14[index];
}

void func_0029B860(FieldState29B860* object, float value)
{
    object->unk28 = value;
}

void func_0029B870(FieldState29B860* object, float value)
{
    object->unk30 = value;
}

float func_0029B880(FieldState29B860* object)
{
    return object->unk30;
}

void func_0029B890(FieldState29B860* object, u8 value)
{
    object->unk4d = value;
}

u8 func_0029B8A0(FieldState29B860* object)
{
    return object->unk4d;
}

void func_0029B8B0(FieldState29B860* object, float value)
{
    object->unk34 = value;
}

void func_0029B8C0(FieldState29B860* object, u8 value)
{
    object->unk56 = value;
}

u8 func_0029B8D0(FieldState29B860* object)
{
    return object->unk56;
}

void func_0029B8E0(FieldState29B860* object, float value)
{
    object->unk44 = value;
}

float func_0029B8F0(FieldState29B860* object)
{
    return object->unk44;
}

float func_0029B900(FieldState29B860* object)
{
    return object->unk28;
}

void func_0029B910(FieldState29B860* object, u32 value)
{
    object->unk48 = value;
}

u32 func_0029B920(FieldState29B860* object)
{
    return object->unk48;
}

void func_0029B930(FieldState29B860* object, u8 value)
{
    object->unk4f = value;
}

void func_0029B940(FieldState29B860* object, u8 value)
{
    object->unk4e = value;
}

void func_0029B950(FieldState29B860* object, u32 value)
{
    object->unk50 = value;
}

u32 func_0029B960(FieldState29B860* object)
{
    return object->unk50;
}

void func_0029B970(FieldState29B860* object, u8 value)
{
    object->unk55 = value;
}

void func_0029B980(FieldState29B860* object, float value)
{
    object->unk3c = value;
}

void func_0029B990(FieldState29B860* object, u8 value)
{
    object->unk54 = value;
}

void func_0029B9A0(FieldState29B860* object, float value)
{
    object->unk40 = value;
}

void func_0029B9B0(FieldState29B860* object, const u8* data, u32 value)
{
    object->unka0 = data;
    object->unka4 = value;
    if (*object->unka0 == 1)
    {
        object->unk57 = 1;
    }
    else
    {
        object->unk57 = 0;
    }
}

void func_0029B9F0(FieldState29B860* object, s32 value)
{
    object->unka0 = 0;
    object->unka4 = 0;
    if (value != 0)
    {
        object->unk57 = 1;
    }
    else
    {
        object->unk57 = 0;
    }
}

void func_0029BA20(FieldState29B860* object, float value)
{
    object->unk38 = value;
}

void func_0029BA30(FieldState29B860* object, const FieldCopySource29BA30* source)
{
    object->unk2c = 0;
    object->unk60 = source->unk150;
    object->unk70 = source->unk160;
    object->unk80 = source->unk170;
    object->unk90 = source->unk180;
}

void func_0029BA60(void* object)
{
}

void func_0029BA70(FieldHistoryReceiver29BA70* object, s32 capacity, FieldHistoryOutput30* output, u32 stamp)
{
    s32 samples = object->samples;
    s32 index = object->index;
    s32 limit = object->limit;
    const u64* masks = object->mask->unk08;
    u64 bit = (u64)1 << (index & 63);
    s32 mask_index = index / 64;
    s32 processed = 0;
    u64 mask = masks[mask_index++];
    switch (object->policy)
    {
        case 0:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes[3] = previous->attributes.data()[3];
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource120* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes[3] = source->attributes.data()[3];
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource120* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource120* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource120* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes[3] = previous->attributes.data()[3];
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource120* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes[3] = source->attributes.data()[3];
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource120* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource120* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource120* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
        case 1:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes[3] = previous->attributes.data()[3];
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource120* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes[3] = source->attributes.data()[3];
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource120* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource120* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource120* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes[3] = previous->attributes.data()[3];
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource120* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes[3] = source->attributes.data()[3];
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource120* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource120* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource120* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
        case 2:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySource120* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes[3] = previous->attributes.data()[3];
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes[3] = source->attributes.data()[3];
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySource120* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySource120* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySource120* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySource120* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes[3] = previous->attributes.data()[3];
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes[3] = source->attributes.data()[3];
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            FieldHistorySource120* source = &object->source[index - 1];
                            s32 history_index = index * (samples - 1) - 1;
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySource120* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySource120* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
    }
}

s32 func_0029E540(void* object)
{
    return 1;
}

FieldEntryTail0029E550* func_0029E550(FieldEntryOwner0029E550* object, s32 index)
{
    return &object->unk14[index];
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00294DA0", func_0029E580);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00294DA0", func_0029E990);

void func_0029EA90(FieldState29EA90* object, float value)
{
    object->unk28 = value;
}

void func_0029EAA0(FieldState29EA90* object, float value)
{
    object->unk30 = value;
}

float func_0029EAB0(FieldState29EA90* object)
{
    return object->unk30;
}

void func_0029EAC0(FieldState29EA90* object, u8 value)
{
    object->unk4d = value;
}

u8 func_0029EAD0(FieldState29EA90* object)
{
    return object->unk4d;
}

void func_0029EAE0(FieldState29EA90* object, float value)
{
    object->unk34 = value;
}

void func_0029EAF0(FieldState29EA90* object, u8 value)
{
    object->unk56 = value;
}

u8 func_0029EB00(FieldState29EA90* object)
{
    return object->unk56;
}

void func_0029EB10(FieldState29EA90* object, float value)
{
    object->unk44 = value;
}

float func_0029EB20(FieldState29EA90* object)
{
    return object->unk44;
}

float func_0029EB30(FieldState29EA90* object)
{
    return object->unk28;
}

void func_0029EB40(FieldState29EA90* object, u32 value)
{
    object->unk48 = value;
}

u32 func_0029EB50(FieldState29EA90* object)
{
    return object->unk48;
}

void func_0029EB60(FieldState29EA90* object, u8 value)
{
    object->unk4f = value;
}

void func_0029EB70(FieldState29EA90* object, u8 value)
{
    object->unk4e = value;
}

void func_0029EB80(FieldState29EA90* object, u32 value)
{
    object->unk50 = value;
}

u32 func_0029EB90(FieldState29EA90* object)
{
    return object->unk50;
}

void func_0029EBA0(FieldState29EA90* object, u8 value)
{
    object->unk55 = value;
}

void func_0029EBB0(FieldState29EA90* object, float value)
{
    object->unk3c = value;
}

void func_0029EBC0(FieldState29EA90* object, u8 value)
{
    object->unk54 = value;
}

void func_0029EBD0(FieldState29EA90* object, float value)
{
    object->unk40 = value;
}

void func_0029EBE0(FieldState29EA90* object, const u8* data, u32 value)
{
    object->unka0 = data;
    object->unka4 = value;
    if (*object->unka0 == 1)
    {
        object->unk57 = 1;
    }
    else
    {
        object->unk57 = 0;
    }
}

void func_0029EC20(FieldState29EA90* object, s32 value)
{
    object->unka0 = 0;
    object->unka4 = 0;
    if (value != 0)
    {
        object->unk57 = 1;
    }
    else
    {
        object->unk57 = 0;
    }
}

void func_0029EC50(FieldState29EA90* object, float value)
{
    object->unk38 = value;
}

void func_0029EC60(void* object)
{
}

s32 func_0029EC70(void* object)
{
    return 0;
}

void func_0029EC80(void* object)
{
}

s32 func_0029EC90(void* object)
{
    return 0;
}

void func_0029ECA0(FieldState29EA90* object, const FieldCopySource29ECA0* source)
{
    object->unk2c = 0;
    object->unk60 = source->unk150;
    object->unk70 = source->unk160;
    object->unk80 = source->unk170;
    object->unk90 = source->unk180;
}

void func_0029ECD0(void* object)
{
}

void func_0029ECE0(FieldHistoryReceiver29ECE0* object, s32 capacity, FieldHistoryOutput30* output, u32 stamp)
{
    s32 samples = object->samples;
    s32 index = object->index;
    s32 limit = object->limit;
    const u64* masks = object->mask->unk08;
    u64 bit = (u64)1 << (index & 63);
    s32 mask_index = index / 64;
    s32 processed = 0;
    u64 mask = masks[mask_index++];
    switch (object->policy)
    {
        case 0:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes[3] = previous->attributes.data()[3];
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySourceB0* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes[3] = source->attributes.data()[3];
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySourceB0* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySourceB0* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySourceB0* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes[3] = previous->attributes.data()[3];
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySourceB0* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes[3] = source->attributes.data()[3];
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySourceB0* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySourceB0* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySourceB0* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
        case 1:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes[3] = previous->attributes.data()[3];
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySourceB0* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes[3] = source->attributes.data()[3];
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySourceB0* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySourceB0* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySourceB0* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes[3] = previous->attributes.data()[3];
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySourceB0* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes[3] = source->attributes.data()[3];
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySourceB0* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySourceB0* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySourceB0* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
        case 2:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySourceB0* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes[3] = previous->attributes.data()[3];
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes[3] = source->attributes.data()[3];
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySourceB0* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySourceB0* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySourceB0* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySourceB0* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes[3] = previous->attributes.data()[3];
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes[3] = source->attributes.data()[3];
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            FieldHistorySourceB0* source = &object->source[index - 1];
                            s32 history_index = index * (samples - 1) - 1;
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySourceB0* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySourceB0* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
    }
}

s32 func_002A1850(void* object)
{
    return 1;
}

FieldEntryTail002A1860* func_002A1860(FieldEntryOwner002A1860* object, s32 index)
{
    return &object->unk14[index];
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00294DA0", func_002A1890);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00294DA0", func_002A1CA0);

void func_002A1DA0(FieldState2A1DA0* object, float value)
{
    object->unk28 = value;
}

void func_002A1DB0(FieldState2A1DA0* object, float value)
{
    object->unk30 = value;
}

float func_002A1DC0(FieldState2A1DA0* object)
{
    return object->unk30;
}

void func_002A1DD0(FieldState2A1DA0* object, u8 value)
{
    object->unk4d = value;
}

u8 func_002A1DE0(FieldState2A1DA0* object)
{
    return object->unk4d;
}

void func_002A1DF0(FieldState2A1DA0* object, float value)
{
    object->unk34 = value;
}

void func_002A1E00(FieldState2A1DA0* object, u8 value)
{
    object->unk56 = value;
}

u8 func_002A1E10(FieldState2A1DA0* object)
{
    return object->unk56;
}

void func_002A1E20(FieldState2A1DA0* object, float value)
{
    object->unk44 = value;
}

float func_002A1E30(FieldState2A1DA0* object)
{
    return object->unk44;
}

float func_002A1E40(FieldState2A1DA0* object)
{
    return object->unk28;
}

void func_002A1E50(FieldState2A1DA0* object, u32 value)
{
    object->unk48 = value;
}

u32 func_002A1E60(FieldState2A1DA0* object)
{
    return object->unk48;
}

void func_002A1E70(FieldState2A1DA0* object, u8 value)
{
    object->unk4f = value;
}

void func_002A1E80(FieldState2A1DA0* object, u8 value)
{
    object->unk4e = value;
}

void func_002A1E90(FieldState2A1DA0* object, u32 value)
{
    object->unk50 = value;
}

u32 func_002A1EA0(FieldState2A1DA0* object)
{
    return object->unk50;
}

void func_002A1EB0(FieldState2A1DA0* object, u8 value)
{
    object->unk55 = value;
}

void func_002A1EC0(FieldState2A1DA0* object, float value)
{
    object->unk3c = value;
}

void func_002A1ED0(FieldState2A1DA0* object, u8 value)
{
    object->unk54 = value;
}

void func_002A1EE0(FieldState2A1DA0* object, float value)
{
    object->unk40 = value;
}

void func_002A1EF0(FieldState2A1DA0* object, const u8* data, u32 value)
{
    object->unka0 = data;
    object->unka4 = value;
    if (*object->unka0 == 1)
    {
        object->unk57 = 1;
    }
    else
    {
        object->unk57 = 0;
    }
}

void func_002A1F30(FieldState2A1DA0* object, s32 value)
{
    object->unka0 = 0;
    object->unka4 = 0;
    if (value != 0)
    {
        object->unk57 = 1;
    }
    else
    {
        object->unk57 = 0;
    }
}

void func_002A1F60(FieldState2A1DA0* object, float value)
{
    object->unk38 = value;
}

void func_002A1F70(void* object)
{
}

s32 func_002A1F80(void* object)
{
    return 0;
}

void func_002A1F90(void* object)
{
}

s32 func_002A1FA0(void* object)
{
    return 0;
}

void func_002A1FB0(FieldState2A1DA0* object, const FieldCopySource2A1FB0* source)
{
    object->unk2c = 0;
    object->unk60 = source->unk150;
    object->unk70 = source->unk160;
    object->unk80 = source->unk170;
    object->unk90 = source->unk180;
}

void func_002A1FE0(void* object)
{
}

void func_002A1FF0(FieldHistoryReceiver2A1FF0* object, s32 capacity, FieldHistoryOutput30* output, u32 stamp)
{
    s32 samples = object->samples;
    s32 index = object->index;
    s32 limit = object->limit;
    const u64* masks = object->mask->unk08;
    u64 bit = (u64)1 << (index & 63);
    s32 mask_index = index / 64;
    s32 processed = 0;
    u64 mask = masks[mask_index++];
    switch (object->policy)
    {
        case 0:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes[3] = previous->attributes.data()[3];
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource90* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes[3] = source->attributes.data()[3];
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource90* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource90* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource90* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes[3] = previous->attributes.data()[3];
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource90* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes[3] = source->attributes.data()[3];
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource90* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource90* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                *(unsigned __int128*)current_position = *(const unsigned __int128*)previous->position.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource90* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            *(unsigned __int128*)current_position = *(const unsigned __int128*)source->position.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
        case 1:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes[3] = previous->attributes.data()[3];
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource90* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes[3] = source->attributes.data()[3];
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource90* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource90* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource90* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes[3] = previous->attributes.data()[3];
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource90* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes[3] = source->attributes.data()[3];
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource90* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource90* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_position = current->position.data();
                                float* current_attributes = current->attributes.data();
                                out->position.raw = *(const unsigned __int128*)current_position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            FieldHistorySource90* source = &object->source[index - 1];
                            float* current_position = current->position.data();
                            float* current_attributes = current->attributes.data();
                            out->position.raw = *(const unsigned __int128*)current_position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
        case 2:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySource90* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes[3] = previous->attributes.data()[3];
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes[3] = source->attributes.data()[3];
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySource90* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySource90* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySource90* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            out->control.word[0] = stamp_value;
                            *(u32*)current_control = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySource90* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes[3] = previous->attributes.data()[3];
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes[3] = source->attributes.data()[3];
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            FieldHistorySource90* source = &object->source[index - 1];
                            s32 history_index = index * (samples - 1) - 1;
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySource90* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            FieldHistorySource90* source = &object->source[index - 1];
                            FieldQuad128 position;
                            position.raw = *(const unsigned __int128*)source->position.data();
                            func_4EA000(&position);
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                FieldHistoryOutput30* out = &output[sample];
                                FieldHistoryRecord40* current = &object->history[history_index--];
                                FieldHistoryRecord40* previous = current - 1;
                                float* current_attributes = current->attributes.data();
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                *(unsigned __int128*)current_attributes = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes.raw = *(const unsigned __int128*)current_attributes;
                                float* current_control = current->control.data();
                                *(unsigned __int128*)current_control = *(const unsigned __int128*)previous->control.data();
                                out->control.raw = *(const unsigned __int128*)current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds();
                            }
                            FieldHistoryOutput30* out = &output[1];
                            FieldHistoryRecord40* current = &object->history[history_index];
                            float* current_attributes = current->attributes.data();
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            *(unsigned __int128*)current_attributes = *(const unsigned __int128*)source->attributes.data();
                            out->attributes.raw = *(const unsigned __int128*)current_attributes;
                            float* current_control = current->control.data();
                            out->control.raw = *(const unsigned __int128*)current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
    }
}

s32 func_002A4AC0(void* object)
{
    return 1;
}

FieldEntryTail002A4AD0* func_002A4AD0(FieldEntryOwner002A4AD0* object, s32 index)
{
    return &object->unk14[index];
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00294DA0", func_002A4B00);
