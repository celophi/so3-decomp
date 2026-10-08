#include "include_asm.h"
#include "main/resident_data.h"
#include "main/resident_0010A0E0.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/1067-00/text_00202240.h"
#include "overlays/1067-00/text_002CEAF0.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/1067-00/text_002CD390.h"

extern "C" void func_002CEDA0(FieldCountedList* list);
extern "C" void func_002CEF20(FieldCountedList* list);

extern "C" void func_002CF110(FieldCountedList* list);
extern "C" void func_002CF300(FieldCountedList* list);
extern "C" void func_002CF480(FieldCountedList* list);
extern "C" void func_002CF600(FieldCountedList* list);
extern "C" void func_002CF780(FieldCountedList* list);
extern "C" void func_002CF900(FieldCountedList* list);
extern "C" void func_002CFA80(FieldCountedList* list);
extern "C" void func_002CFC00(FieldCountedList* list);
extern "C" void func_002CFD80(FieldCountedList* list);

/** Partial object with byte values at 0x18 and 0x88, and flags at 0x1A. */
typedef struct FieldD1440Object
{
    u8 pad00[0x18];
    u8 value18;
    u8 pad19;
    u16 flags;
    u8 pad1c[0x6C];
    u8 value88;
} FieldD1440Object;

FieldClass15AE70::~FieldClass15AE70()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CEBE0);

FieldClass15B008::FieldClass15B008()
{
    unk00 = new (0) FieldListNode;
    if (unk00 == 0)
    {
        throw;
    }
    unk00->unk04 = 0;
    unk04 = 0;
}

FieldClass15B008::~FieldClass15B008()
{
    func_002CEDA0(this);
    if (unk00 != 0)
    {
        ::operator delete(unk00);
        unk00 = 0;
    }
}

/** @brief Delete every node after the sentinel and reset the count. @param list List to clear. */
extern "C" void func_002CEDA0(FieldCountedList* list)
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

FieldClass15AFF8::FieldClass15AFF8()
{
    unk00 = new (0) FieldListNode;
    if (unk00 == 0)
    {
        throw;
    }
    unk00->unk04 = 0;
    unk04 = 0;
}

FieldClass15AFF8::~FieldClass15AFF8()
{
    func_002CEF20(this);
    if (unk00 != 0)
    {
        ::operator delete(unk00);
        unk00 = 0;
    }
}

/** @brief Delete every node after the sentinel and reset the count. @param list List to clear. */
extern "C" void func_002CEF20(FieldCountedList* list)
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

/**
 * @brief Remove the first value from the list.
 * @param list List to take from.
 * @param value Receives the removed value.
 * @return One when a value was removed, otherwise zero.
 */
extern "C" s32 func_002CEFA0(FieldCountedList* list, void** value)
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

FieldClass15AFE8::FieldClass15AFE8()
{
    unk00 = new (0) FieldListNode;
    if (unk00 == 0)
    {
        throw;
    }
    unk00->unk04 = 0;
    unk04 = 0;
}

FieldClass15AFE8::~FieldClass15AFE8()
{
    func_002CF110(this);
    if (unk00 != 0)
    {
        ::operator delete(unk00);
        unk00 = 0;
    }
}

/** @brief Delete every node after the sentinel and reset the count. @param list List to clear. */
extern "C" void func_002CF110(FieldCountedList* list)
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

/**
 * @brief Remove the first value from the list.
 * @param list List to take from.
 * @param value Receives the removed value.
 * @return One when a value was removed, otherwise zero.
 */
extern "C" s32 func_002CF190(FieldCountedList* list, void** value)
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

FieldClass15AFD8::FieldClass15AFD8()
{
    unk00 = new (0) FieldListNode;
    if (unk00 == 0)
    {
        throw;
    }
    unk00->unk04 = 0;
    unk04 = 0;
}

FieldClass15AFD8::~FieldClass15AFD8()
{
    func_002CF300(this);
    if (unk00 != 0)
    {
        ::operator delete(unk00);
        unk00 = 0;
    }
}

/** @brief Delete every node after the sentinel and reset the count. @param list List to clear. */
extern "C" void func_002CF300(FieldCountedList* list)
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

FieldClass15AFC8::FieldClass15AFC8()
{
    unk00 = new (0) FieldListNode;
    if (unk00 == 0)
    {
        throw;
    }
    unk00->unk04 = 0;
    unk04 = 0;
}

FieldClass15AFC8::~FieldClass15AFC8()
{
    func_002CF480(this);
    if (unk00 != 0)
    {
        ::operator delete(unk00);
        unk00 = 0;
    }
}

/** @brief Delete every node after the sentinel and reset the count. @param list List to clear. */
extern "C" void func_002CF480(FieldCountedList* list)
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

FieldClass15AFB8::FieldClass15AFB8()
{
    unk00 = new (0) FieldListNode;
    if (unk00 == 0)
    {
        throw;
    }
    unk00->unk04 = 0;
    unk04 = 0;
}

FieldClass15AFB8::~FieldClass15AFB8()
{
    func_002CF600(this);
    if (unk00 != 0)
    {
        ::operator delete(unk00);
        unk00 = 0;
    }
}

/** @brief Delete every node after the sentinel and reset the count. @param list List to clear. */
extern "C" void func_002CF600(FieldCountedList* list)
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

FieldClass15AFA8::FieldClass15AFA8()
{
    unk00 = new (0) FieldListNode;
    if (unk00 == 0)
    {
        throw;
    }
    unk00->unk04 = 0;
    unk04 = 0;
}

FieldClass15AFA8::~FieldClass15AFA8()
{
    func_002CF780(this);
    if (unk00 != 0)
    {
        ::operator delete(unk00);
        unk00 = 0;
    }
}

/** @brief Delete every node after the sentinel and reset the count. @param list List to clear. */
extern "C" void func_002CF780(FieldCountedList* list)
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

FieldClass15AF98::FieldClass15AF98()
{
    unk00 = new (0) FieldListNode;
    if (unk00 == 0)
    {
        throw;
    }
    unk00->unk04 = 0;
    unk04 = 0;
}

FieldClass15AF98::~FieldClass15AF98()
{
    func_002CF900(this);
    if (unk00 != 0)
    {
        ::operator delete(unk00);
        unk00 = 0;
    }
}

/** @brief Delete every node after the sentinel and reset the count. @param list List to clear. */
extern "C" void func_002CF900(FieldCountedList* list)
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

FieldClass15AF88::FieldClass15AF88()
{
    unk00 = new (0) FieldListNode;
    if (unk00 == 0)
    {
        throw;
    }
    unk00->unk04 = 0;
    unk04 = 0;
}

FieldClass15AF88::~FieldClass15AF88()
{
    func_002CFA80(this);
    if (unk00 != 0)
    {
        ::operator delete(unk00);
        unk00 = 0;
    }
}

/** @brief Delete every node after the sentinel and reset the count. @param list List to clear. */
extern "C" void func_002CFA80(FieldCountedList* list)
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

FieldClass15AF78::FieldClass15AF78()
{
    unk00 = new (0) FieldListNode;
    if (unk00 == 0)
    {
        throw;
    }
    unk00->unk04 = 0;
    unk04 = 0;
}

FieldClass15AF78::~FieldClass15AF78()
{
    func_002CFC00(this);
    if (unk00 != 0)
    {
        ::operator delete(unk00);
        unk00 = 0;
    }
}

/** @brief Delete every node after the sentinel and reset the count. @param list List to clear. */
extern "C" void func_002CFC00(FieldCountedList* list)
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

FieldClass15AF68::FieldClass15AF68()
{
    unk00 = new (0) FieldListNode;
    if (unk00 == 0)
    {
        throw;
    }
    unk00->unk04 = 0;
    unk04 = 0;
}

FieldClass15AF68::~FieldClass15AF68()
{
    func_002CFD80(this);
    if (unk00 != 0)
    {
        ::operator delete(unk00);
        unk00 = 0;
    }
}

/** @brief Delete every node after the sentinel and reset the count. @param list List to clear. */
extern "C" void func_002CFD80(FieldCountedList* list)
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

/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 3.
 */
s32 func_002CFE00(FieldClass150070* object)
{
    return 3;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CFE10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CFE40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CFF60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D08B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D0D30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D1100);

s32 func_002D1440(FieldD1440Object* object, u8 value, u32 flags)
{
    object->value18 = value;
    if (flags != 0)
    {
        object->flags = flags;
    }
    else
    {
        object->flags = 0;
    }
    if (((u16)flags) & 8)
    {
        object->value88 = 0;
    }
    else
    {
        object->value88 = 1;
    }
    return 1;
}

/** @brief Detach the object and add it to the resident release queue. @param object Object to release. */
extern "C" void func_002D1480(void* object)
{
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D14B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D1550);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D1640);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D18E0);

/** Partial FieldClass150F90 with vtable D_15B090 in main data. */
class FieldClass15B090 : public FieldClass150F90
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass15B090();
};

FieldClass15B090::~FieldClass15B090()
{
}

/**
 * @brief Run the base release handler, detach the object, then delete it.
 * @param object Object to release.
 */
extern "C" void func_002D19E0(FieldClass150F90* object)
{
    object->FieldClass150F90::func_00204E40();
    func_004D65C0(object);
    object->func_001DD7B0();
}

extern "C" void func_00204FC0(void* object);

/** @brief Forward the object to func_00204FC0. @param object Object to forward. */
extern "C" void func_002D1A20(void* object)
{
    func_00204FC0(object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D1A40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D1C10);

/** Partial owner of a Lib container with a state bit at offset 0x55. */
struct FieldOwner2D1D70
{
    u8 unk00[0x4C];
    LibObject178660* unk4c;
    u32 unk50;
    u8 unk54;
    u8 unk55_0_2 : 3;
    u8 unk55_3 : 1;
    u8 unk55_4_7 : 4;
};

/**
 * @brief Release the owned Lib container and clear the state bit.
 * @param owner Owner of the container.
 */
extern "C" void func_002D1D70(FieldOwner2D1D70* owner)
{
    owner->unk50 = 0;
    if (owner->unk4c != 0)
    {
        owner->unk4c->func_003EF740();
        owner->unk4c = 0;
    }
    owner->unk55_3 = 0;
}

/** Partial receiver with a word at offset 0x20. */
struct FieldWord002D1DD0
{
    u8 unk00[0x20];
    s32 unk20;
};

/** @brief Clear the word at offset 0x20. @param object Receiver. */
extern "C" void func_002D1DD0(FieldWord002D1DD0* object)
{
    object->unk20 = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D1DE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D1FD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D2020);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D2050);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D2170);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D2210);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D22B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D23B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D2420);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D3920);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D3990);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D3A50);

/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 4.
 */
s32 func_002D3BB0(FieldClass150070* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D3BC0);
