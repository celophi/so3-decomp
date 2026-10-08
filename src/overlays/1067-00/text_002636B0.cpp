#include "include_asm.h"
#include "overlays/1067-00/text_002636B0.h"
#include "overlays/1067-00/text_0026E460.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/lib/text_00419A70.h"
#include "overlays/lib/text_0044ABE0.h"

extern "C" void func_00264580(FieldCountedList* list);

/** Partial receiver and guarded nested state for the constant reset. */
typedef struct FieldInnerC000
{
    u8 pad00[0x3C];
    u8 active;
    u8 pad3d[0x33];
    float value;
} FieldInnerC000;

typedef struct FieldOuterC000
{
    u8 pad00[0xD4];
    FieldInnerC000* inner;
} FieldOuterC000;


INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002636B0);

void func_002636F0(u32* word, u32 value)
{
    *word = value;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00263700);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002637C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002637E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00263890);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00263940);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00263A30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00263AF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00263BF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00263C40);

void func_00263C70(FieldObject153E20* object, void* value)
{
    object->unk20 = value;
}

void func_00263C80(FieldObject153E20* object, void* value)
{
    object->unk24 = value;
}

void* func_00263C90(const FieldObject153E20* object)
{
    return object->unk24;
}

void func_00263CA0(FieldObject153E20* object, s8 value)
{
    object->unk28 = value;
}

s8 func_00263CB0(const FieldObject153E20* object)
{
    return object->unk28;
}

s32 func_00263CC0(void* object)
{
    return 0;
}

s32 func_00263CD0(void* object)
{
    return 0;
}

s32 func_00263CE0(void* object)
{
    return 0;
}

s32 func_00263CF0(void* object)
{
    return 0;
}

void func_00263D00(void* object)
{
}

s32 func_00263D10(void* object)
{
    return 0;
}

void func_00263D20(void* object)
{
}

void func_00263D30(void* object)
{
}

void func_00263D40(void* object)
{
}

s32 func_00263D50(void* object)
{
    return 0;
}

s32 func_00263D60(void* object)
{
    return 0;
}

s32 func_00263D70(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00263D80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00263E20);

void func_00263E80(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00263E90);

void func_00263F40(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00263F50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00263FD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264010);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264080);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264110);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264200);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264230);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002642D0);

FieldClass153EC0::FieldClass153EC0()
{
    unk00 = new (0) FieldListNode;
    if (unk00 == 0)
    {
        throw;
    }
    unk00->unk04 = 0;
    unk04 = 0;
}

FieldClass153EC0::~FieldClass153EC0()
{
    func_00264580(this);
    if (unk00 != 0)
    {
        ::operator delete(unk00);
        unk00 = 0;
    }
}

/** @brief Append a value at the tail of the list. @param list List to extend. @param value Value to append. */
extern "C" void func_00264460(FieldCountedList* list, void* value)
{
    FieldListNode* node = new (0) FieldListNode;
    if (node != 0)
    {
        FieldListNode* tail;
        node->unk00 = value;
        node->unk04 = 0;
        tail = list->unk00;
        while (tail->unk04 != 0)
        {
            tail = tail->unk04;
        }
        tail->unk04 = node;
        list->unk04++;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002644F0);

/** @brief Delete every node after the sentinel and reset the count. @param list List to clear. */
extern "C" void func_00264580(FieldCountedList* list)
{
    FieldListNode* node = list->unk00->unk04;
    if (node == 0)
    {
        return;
    }
    while (node != 0)
    {
        FieldListNode* next = node->unk04;
        delete node;
        node = next;
    }
    list->unk00->unk04 = 0;
    list->unk04 = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264600);

/**
 * @brief Remove the first value from the list.
 * @param list List to take from.
 * @param value Receives the removed value.
 * @return One when a value was removed, otherwise zero.
 */
extern "C" s32 func_00264650(FieldCountedList* list, void** value)
{
    FieldListNode* node = list->unk00->unk04;
    if (node != 0)
    {
        *value = node->unk00;
    }
    else
    {
        return 0;
    }
    list->unk00->unk04 = node->unk04;
    delete node;
    list->unk04--;
    return 1;
}

void func_002646C0(FieldObject15AE70* object, u8 value)
{
    object->unk0C = value;
}

u8 func_002646D0(const FieldObject15AE70* object)
{
    return object->unk0C;
}

void func_002646E0(FieldObject15AE70* object, u8 value)
{
    object->unk08 = value;
}

void func_002646F0(FieldObject15AE70* object, u16 value)
{
    object->unk0A = value;
}

void func_00264720(FieldObject15AE70* object, void* value)
{
    object->unk9C = value;
}

void* func_00264730(const FieldObject15AE70* object)
{
    return object->unk9C;
}

void func_00264740(FieldObject15AE70* object, void* value)
{
    object->unk04 = value;
}

void* func_00264750(const FieldObject15AE70* object)
{
    return object->unk04;
}

void* func_00264760(const FieldObject15AE70* object)
{
    return object->unk10;
}

void func_00264770(void* object)
{
}

void func_00264780(void* object)
{
}

void func_00264790(void* object)
{
}

void func_002647A0(void* object)
{
}

void func_002647B0(void* object)
{
}

void func_002647C0(void* object)
{
}

void func_002647D0(void* object)
{
}

void func_002647E0(void* object)
{
}

void func_002647F0(void* object)
{
}

void func_00264800(void* object)
{
}

void func_00264810(void* object)
{
}

void func_00264820(void* object)
{
}

void func_00264830(void* object)
{
}

void func_00264840(void* object)
{
}

void func_00264850(void* object)
{
}

void func_00264860(void* object)
{
}

void func_00264870(void* object)
{
}

void func_00264880(void* object)
{
}

void func_00264890(void* object)
{
}

void func_002648A0(void* object)
{
}

s32 func_002648B0(void* object)
{
    return 0;
}

s32 func_002648C0(void* object)
{
    return 0;
}

s32 func_002648D0(void* object)
{
    return 0;
}

s32 func_002648E0(void* object)
{
    return 0;
}

s32 func_002648F0(void* object)
{
    return 0;
}

s32 func_00264900(void* object)
{
    return 0;
}

s32 func_00264910(void* object)
{
    return 0;
}

s32 func_00264920(void* object)
{
    return 0;
}

s32 func_00264930(void* object)
{
    return 0;
}

s32 func_00264940(void* object)
{
    return 0;
}

void func_00264950(void* object)
{
}

void func_00264960(void* object)
{
}

u8 func_00264970(const FieldObject15AE70* object)
{
    return object->unk0D;
}

void func_00264980(FieldObject15AE70* object, u8 value)
{
    object->unk0D = value;
}

void func_00264990(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002649A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264A30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264AC0);

/** Partial FieldClass15AE70 window with vtable D_153ED0 in main data. */
class FieldClass153ED0 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window. */
    virtual ~FieldClass153ED0();
};

FieldClass153ED0::~FieldClass153ED0()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264CB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264CE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264D30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264E10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00264ED0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002650F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00265130);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00265360);

void func_00265490(FieldObject15AD40* object, u8 value)
{
    object->unk12C = value;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002654A0);

/** Partial FieldClass15AE70 window with vtable D_1540B0 in main data. */
class FieldClass1540B0 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window. */
    virtual ~FieldClass1540B0();
};

FieldClass1540B0::~FieldClass1540B0()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00265870);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002658E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00265A70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00265C40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00265D90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00265FC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00266060);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00266190);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002666C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00266730);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00266820);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002669A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002669C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002669E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00266A60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00266B90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00266EB0);

ItemCreationClass175110::~ItemCreationClass175110()
{
}

/** Partial FieldClass15AE70 window with vtable D_1542D0 in main data. */
class FieldClass1542D0 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window. */
    virtual ~FieldClass1542D0();
};

FieldClass1542D0::~FieldClass1542D0()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00267390);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00267410);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00267500);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002675F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00267690);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00267720);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002678F0);

/** Partial FieldClass15AE70 window with vtable D_1543D0 in main data. */
class FieldClass1543D0 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window. */
    virtual ~FieldClass1543D0();
};

FieldClass1543D0::~FieldClass1543D0()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00267E30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00267EE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00267FA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00267FF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00268040);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002680E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00268170);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00268370);

/** Partial FieldClass15AE70 window with vtable D_1544D0 in main data. */
class FieldClass1544D0 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window. */
    virtual ~FieldClass1544D0();
};

FieldClass1544D0::~FieldClass1544D0()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00268810);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00268990);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00268A80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00268B10);

/** Partial FieldClass15AE70 window with vtable D_1545D0 in main data. */
class FieldClass1545D0 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window. */
    virtual ~FieldClass1545D0();
};

FieldClass1545D0::~FieldClass1545D0()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00269120);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_002691A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00269340);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00269670);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00269F20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_00269FC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026A110);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026A210);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026A2A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026A330);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026A650);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026BD60);

void FieldClass1547D0::func_slot0c()
{
    FieldClass150070* item = 0;
    while (func_0026E5F0(unkfc, &item))
    {
        item->func_001DD7B0();
    }
    func_0026E570(unkfc);
    FieldClass15AE70::func_slot0c();
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026BEA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026BF10);

void func_0026C000(FieldOuterC000* object)
{
    FieldInnerC000* inner = object->inner;
    if (inner != 0)
    {
        inner->value = 128.0f;
        inner->active = 1;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026C030);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026C1B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026C1E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026C650);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026CB00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026CB20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026CB40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026CB60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026CC80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026D140);

void FieldClass1548D0::func_slot0c()
{
    FieldClass15AE70::func_slot0c();
    FieldClass150070* item = 0;
    while (func_0026E7E0(unkb8, &item))
    {
        item->func_001DD7B0();
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026D560);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026D5D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026D6A0);

/** Partial FieldClass15AE70 window with vtable D_1549D0 in main data. */
class FieldClass1549D0 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window. */
    virtual ~FieldClass1549D0();
};

FieldClass1549D0::~FieldClass1549D0()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026DAF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026DF90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026E050);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026E0F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026E170);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026E1A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026E210);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002636B0", func_0026E2E0);

void func_0026E390(void* object)
{
}

u8 func_0026E3A0(const FieldObject15AE70* object)
{
    return 0;
}

u8 func_0026E3B0(const FieldObject15AE70* object)
{
    return 0;
}

u8 func_0026E3C0(const FieldObject1549D0* object)
{
    return object->unk3C;
}

void* func_0026E3D0(const FieldObject1549D0* object)
{
    return object->unk38;
}

FieldClass154BA0::FieldClass154BA0()
{
    unk00 = new (0) FieldListNode;
    if (unk00 == 0)
    {
        throw;
    }
    unk00->unk04 = 0;
    unk04 = 0;
}
