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
    head = new (0) FieldListNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

FieldClass15B9F8::~FieldClass15B9F8()
{
    func_002F31D0(this);
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

/** @brief Append a value at the tail of the list. @param list List to extend. @param value Value to append. */
extern "C" void func_002F30A0(FieldCountedList* list, void* value)
{
    FieldListNode* node = new (0) FieldListNode;
    if (node != 0)
    {
        FieldListNode* tail;
        node->value = value;
        node->next = 0;
        tail = list->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        list->count++;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F3130);

/** @brief Delete every node after the head node and reset the count. @param list List to clear. */
extern "C" void func_002F31D0(FieldCountedList* list)
{
    FieldListNode* node = list->head->next;
    if (node == 0)
    {
        return;
    }
    while (node != 0)
    {
        FieldListNode* next = node->next;
        delete node;
        node = next;
    }
    list->head->next = 0;
    list->count = 0;
}

extern "C" void* func_002F3250(void* object, s32 count)
{
    void* node;
    s32 traversed;
    node = *(void**)(*(u8**)object + 4);
    traversed = 0;
    while (traversed < count)
    {
        if (node == 0)
        {
            return 0;
        }
        node = *(void**)((u8*)node + 4);
        traversed += 1;
    }
    return node;
}

/**
 * @brief Remove the first value from the list.
 * @param list List to take from.
 * @param value Receives the removed value.
 * @return One when a value was removed, otherwise zero.
 */
extern "C" s32 func_002F3290(FieldCountedList* list, void** value)
{
    FieldListNode* node = list->head->next;
    if (node != 0)
    {
        *value = node->value;
    }
    else
    {
        return 0;
    }
    list->head->next = node->next;
    delete node;
    list->count--;
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F3300);
