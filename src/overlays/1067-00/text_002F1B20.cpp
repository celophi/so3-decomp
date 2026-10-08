#include "include_asm.h"
#include "overlays/1067-00/text_002F1B20.h"
#include "overlays/1067-00/text_002CD390.h"

extern "C" void func_002F31D0(FieldCountedList* list);

/** Partial target with a byte at offset 0x140. */
struct FieldByte140
{
    u8 pad[0x140];
    u8 value;
};

/** Partial global state with a target pointer at offset 0x20. */
struct FieldGlobal20
{
    u8 pad[0x20];
    FieldByte140* target;
};

extern "C" FieldGlobal20* D_001B643C;


INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F1B20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F1B60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F1E60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F2340);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F23E0);

void func_002F2460(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F2470);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F2740);

extern "C" u8 func_002F2880(void)
{
    return D_001B643C->target->value;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F2890);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F2900);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F2B20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F2EC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F2F30);

FieldClass15B9F8::FieldClass15B9F8()
{
    unk00 = new (0) FieldListNode;
    if (unk00 == 0)
    {
        throw;
    }
    unk00->unk04 = 0;
    unk04 = 0;
}

FieldClass15B9F8::~FieldClass15B9F8()
{
    func_002F31D0(this);
    if (unk00 != 0)
    {
        ::operator delete(unk00);
        unk00 = 0;
    }
}

/** @brief Append a value at the tail of the list. @param list List to extend. @param value Value to append. */
extern "C" void func_002F30A0(FieldCountedList* list, void* value)
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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F3130);

/** @brief Delete every node after the sentinel and reset the count. @param list List to clear. */
extern "C" void func_002F31D0(FieldCountedList* list)
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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F3250);

/**
 * @brief Remove the first value from the list.
 * @param list List to take from.
 * @param value Receives the removed value.
 * @return One when a value was removed, otherwise zero.
 */
extern "C" s32 func_002F3290(FieldCountedList* list, void** value)
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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F3300);
