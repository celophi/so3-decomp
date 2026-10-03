#include "include_asm.h"
#include "overlays/cequip/text.h"

typedef struct
{
    u8 pad_00[4];
    u32 field_04;
    u8 field_08;
    u8 pad_09;
    u16 field_0a;
    u8 field_0c;
    u8 field_0d;
    u8 pad_0e[2];
    u32 field_10;
    u8 pad_14[0xC];
    u32 field_20;
    u8 pad_24[0x74];
    u32 field_98;
    u32 field_9c;
} EquipObjectFields;

typedef struct
{
    u8 pad_00[0x12C];
    u8 field_12c;
} EquipSelectionFields;

typedef struct
{
    u8 pad_00[0x34];
    u32 field_34;
    u32 field_38;
} EquipValueFields;

typedef struct
{
    u8 pad_00[0x24];
    u32 field_24;
    s8 field_28;
    u8 pad_29[0x13];
    u8 field_3c;
} EquipEntryFields;

typedef struct
{
    u8 pad_00[0xF0];
    u8 flag_f0;
} EquipToggleTarget;

typedef struct
{
    u8 pad_00[0x54];
    EquipToggleTarget* target;
} EquipToggleHolder;

typedef struct
{
    u8 pad_00[0xA8];
    EquipToggleHolder* holder;
} EquipToggleOwnerA8;

typedef struct
{
    u8 pad_00[0x180];
    EquipToggleHolder* holder;
} EquipToggleOwner180;

typedef struct
{
    u8 pad_00[0x188];
    EquipToggleHolder* holder;
} EquipToggleOwner188;

typedef struct EquipLinkedNode
{
    s16 value;
    u8 pad_02[2];
    struct EquipLinkedNode* next;
} EquipLinkedNode;

struct EquipLinkedList
{
    EquipLinkedNode* head;
    u32 count;
};

typedef struct EquipWordNode
{
    u32 value;
    struct EquipWordNode* next;
} EquipWordNode;

struct EquipWordList
{
    EquipWordNode* head;
    u32 count;
};

typedef struct
{
    u8 pad_00[0x3C];
    u8 field_3c;
    u8 pad_3d[2];
    u8 field_3f;
    u8 pad_40[0x30];
    float field_70;
} EquipNested;

typedef struct
{
    u8 pad_00[0xAC];
    EquipNested* nested;
} EquipOwner;

typedef struct
{
    u8 pad_00[0x3C];
    u8 active;
    u8 pad_3d[0x57];
    u32 color;
} EquipIcon;

typedef struct EquipIconNode
{
    EquipIcon* icon;
    struct EquipIconNode* next;
} EquipIconNode;

typedef struct
{
    u8 pad_00[4];
    EquipIconNode* next;
} EquipIconList;

typedef struct
{
    u8 pad_00[0x2C];
    EquipIconList* list;
} EquipIconOwner;

typedef struct
{
    u8 pad_00[0x1C];
    float position;
    u8 pad_20[0x1C];
    u8 active;
} EquipLayoutTarget;

typedef struct
{
    u8 pad_00[0xF0];
    EquipLayoutTarget* first[9];
    u8 pad_114[0x24];
    EquipLayoutTarget* second[9];
    EquipLayoutTarget* third[9];
} EquipLayout;
typedef struct
{
    void* methods;
} EquipDestructorObject;

extern u8 D_182220[];
extern u8 D_182350[];
extern u8 D_182450[];
extern u8 D_182790[];
extern u8 D_182890[];
extern u8 D_182A90[];
extern u8 D_182990[];
extern u8 D_182B90[];
extern u8 D_182C90[];
extern void func_2CEAF0(void* object, s32 flags);
extern void* func_100AC0(s32 size, s32 align);
extern void func_100B40(void* object);


INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_003483C0);

void func_00348400(void* object, u8 value)
{
    ((EquipObjectFields*)object)->field_0c = value;
}

u8 func_00348410(void* object)
{
    return ((EquipObjectFields*)object)->field_0c;
}

void func_00348420(void* object, u8 value)
{
    ((EquipObjectFields*)object)->field_08 = value;
}

u8 func_00348430(void* object)
{
    return ((EquipObjectFields*)object)->field_08;
}

void func_00348440(void* object, u16 value)
{
    ((EquipObjectFields*)object)->field_0a = value;
}

u16 func_00348450(void* object)
{
    return ((EquipObjectFields*)object)->field_0a;
}

void func_00348460(void* object, u32 value)
{
    ((EquipObjectFields*)object)->field_98 = value;
}

u32 func_00348470(void* object)
{
    return ((EquipObjectFields*)object)->field_98;
}

void func_00348480(void* object, u32 value)
{
    ((EquipObjectFields*)object)->field_9c = value;
}

u32 func_00348490(void* object)
{
    return ((EquipObjectFields*)object)->field_9c;
}

void func_003484A0(void* object, u32 value)
{
    ((EquipObjectFields*)object)->field_04 = value;
}

u32 func_003484B0(void* object)
{
    return ((EquipObjectFields*)object)->field_04;
}

u32 func_003484C0(void* object)
{
    return ((EquipObjectFields*)object)->field_10;
}

void func_003484D0(void* object)
{
}

void func_003484E0(void* object)
{
}

void func_003484F0(void* object)
{
}

void func_00348500(void* object)
{
}

void func_00348510(void* object)
{
}

void func_00348520(void* object)
{
}

void func_00348530(void* object)
{
}

void func_00348540(void* object)
{
}

void func_00348550(void* object)
{
}

void func_00348560(void* object)
{
}

void func_00348570(void* object)
{
}

void func_00348580(void* object)
{
}

void func_00348590(void* object)
{
}

void func_003485A0(void* object)
{
}

void func_003485B0(void* object)
{
}

void func_003485C0(void* object)
{
}

void func_003485D0(void* object)
{
}

void func_003485E0(void* object)
{
}

s32 func_003485F0(void* object)
{
    return 0;
}

s32 func_00348600(void* object)
{
    return 0;
}

s32 func_00348610(void* object)
{
    return 0;
}

s32 func_00348620(void* object)
{
    return 0;
}

s32 func_00348630(void* object)
{
    return 0;
}

s32 func_00348640(void* object)
{
    return 0;
}

s32 func_00348650(void* object)
{
    return 0;
}

s32 func_00348660(void* object)
{
    return 0;
}

s32 func_00348670(void* object)
{
    return 0;
}

s32 func_00348680(void* object)
{
    return 0;
}

void func_00348690(void* object)
{
}

void func_003486A0(void* object)
{
}

u8 func_003486B0(void* object)
{
    return ((EquipObjectFields*)object)->field_0d;
}

void func_003486C0(void* object, u8 value)
{
    ((EquipObjectFields*)object)->field_0d = value;
}

void func_003486D0(void* object)
{
}

void func_003486E0(void* object, s16 selected)
{
    s32 index = 0;
    EquipIconNode* node = ((EquipIconOwner*)object)->list->next;
    if (node != 0)
    {
        do
        {
            EquipIcon* icon = node->icon;
            if (index == selected)
            {
                icon->color = 0x288080;
                icon->active = 1;
            }
            else
            {
                icon->color = 0x808080;
                icon->active = 1;
            }
            node = node->next;
            index++;
        } while (node != 0);
    }
}

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00348750);

u32 func_003487B0(void* object)
{
    return ((EquipObjectFields*)object)->field_20;
}

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_003487C0);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00348800);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00348840);

void func_003488C0(void* object, u32 value)
{
    ((EquipObjectFields*)object)->field_20 = value;
}

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_003488D0);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00348950);

void* func_00348CB0(void* object, s32 flags)
{
    if (object != 0)
    {
        ((EquipDestructorObject*)object)->methods = D_182220;
        func_2CEAF0(object, 0);
        if ((s16)flags > 0)
        {
            func_100B40(object);
        }
    }
    return object;
}

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00348D10);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00348E00);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00348E90);

void* func_00349230(void* object, s32 flags)
{
    if (object != 0)
    {
        ((EquipDestructorObject*)object)->methods = D_182350;
        func_2CEAF0(object, 0);
        if ((s16)flags > 0)
        {
            func_100B40(object);
        }
    }
    return object;
}

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00349290);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_003494F0);

void* func_00349560(void* object, s32 flags)
{
    if (object != 0)
    {
        ((EquipDestructorObject*)object)->methods = D_182450;
        func_2CEAF0(object, 0);
        if ((s16)flags > 0)
        {
            func_100B40(object);
        }
    }
    return object;
}

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_003495C0);

s32 func_00349680(void* object)
{
    return 0;
}

s32 func_00349690(void* object)
{
    EquipToggleTarget* target = ((EquipToggleOwner188*)object)->holder->target;
    target->flag_f0 = !target->flag_f0;
    return 1;
}

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_003496B0);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00349750);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_003498D0);

void func_00349B30(void* object, float offset)
{
    EquipLayout* layout = (EquipLayout*)object;
    float position = (16.0f + offset) - 4.0f;
    s32 index = 0;
    do
    {
        EquipLayoutTarget* target_third;
        EquipLayoutTarget* target_second;
        target_third = layout->third[index];
        target_third->position = position;
        target_third->active = 1;
        target_second = layout->second[index];
        target_second->position = position;
        target_second->active = 1;
        position += 28.0f;
        index++;
    } while (index < 9);
}

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00349BA0);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00349D50);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00349E30);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034A330);

void func_0034A390(void* object, u8 value)
{
    ((EquipSelectionFields*)object)->field_12c = value;
}

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034A3A0);

s32 func_0034A460(void* object)
{
    EquipToggleTarget* target = ((EquipToggleOwner180*)object)->holder->target;
    target->flag_f0 = !target->flag_f0;
    return 1;
}

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034A480);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034A540);

u32 func_0034A710(void* object)
{
    return ((EquipValueFields*)object)->field_34;
}

void func_0034A720(void* object, s32 unused, s32 value)
{
    EquipOwner* owner = (EquipOwner*)object;
    if (owner->nested != 0)
    {
        owner->nested->field_3f = value;
        if (value != 0)
        {
            EquipNested* nested = owner->nested;
            nested->field_70 = 128.0f;
            nested->field_3c = 1;
        }
        else
        {
            EquipNested* nested = owner->nested;
            nested->field_70 = 64.0f;
            nested->field_3c = 1;
        }
    }
}

void func_0034A770(void* object, float offset)
{
    EquipLayout* layout = (EquipLayout*)object;
    float position = 16.0f + offset;
    s32 index;
    index = 0;
    do
    {
        EquipLayoutTarget* target_first;
        EquipLayoutTarget* target_second;
        EquipLayoutTarget* target_third;
        target_first = layout->first[index];
        target_first->position = position;
        target_first->active = 1;
        target_second = layout->second[index];
        target_second->position = position;
        target_second->active = 1;
        target_third = layout->third[index];
        target_third->position = position;
        target_third->active = 1;
        position += 28.0f;
        index++;
    } while (index < 9);
}

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034A7D0);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034A9E0);

u32 func_0034AC10(void* object)
{
    return ((EquipValueFields*)object)->field_38;
}

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034AC20);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034AD40);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034B1D0);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034B2A0);

void* func_0034B370(void* object, s32 flags)
{
    if (object != 0)
    {
        ((EquipDestructorObject*)object)->methods = D_182790;
        func_2CEAF0(object, 0);
        if ((s16)flags > 0)
        {
            func_100B40(object);
        }
    }
    return object;
}

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034B3D0);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034BA90);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034BEF0);

void* func_0034C400(void* object, s32 flags)
{
    if (object != 0)
    {
        ((EquipDestructorObject*)object)->methods = D_182890;
        func_2CEAF0(object, 0);
        if ((s16)flags > 0)
        {
            func_100B40(object);
        }
    }
    return object;
}

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034C460);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034C540);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034C830);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034C940);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034CA50);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034CC00);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034CD50);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034CE60);

s32 func_0034CFE0(void* object)
{
    EquipToggleTarget* target = ((EquipToggleOwnerA8*)object)->holder->target;
    target->flag_f0 = !target->flag_f0;
    return 1;
}

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034D000);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034D200);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034D360);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034D4C0);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034D790);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034DBA0);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034DC60);

void* func_0034DD30(void* object, s32 flags)
{
    if (object != 0)
    {
        ((EquipDestructorObject*)object)->methods = D_182A90;
        func_2CEAF0(object, 0);
        if ((s16)flags > 0)
        {
            func_100B40(object);
        }
    }
    return object;
}

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034DD90);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034E450);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034E930);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034E9C0);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034EA30);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034F1F0);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_0034F2A0);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00350910);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00350980);

void func_003509A0(void* object)
{
}

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_003509B0);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00350EA0);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00350F10);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00350F80);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00350FE0);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_003510C0);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00351140);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_003511E0);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_003512A0);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_003512F0);

void func_00351350(void* object)
{
}

void func_00351360(void* object)
{
}

void func_00351370(void* object)
{
}

void func_00351380(void* object)
{
}

s32 func_00351390(void* object)
{
    return 0;
}

s32 func_003513A0(void* object)
{
    return 0;
}

void func_003513B0(void* object)
{
}

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_003513C0);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00351430);

void* func_003514C0(void* object, s32 flags)
{
    if (object != 0)
    {
        ((EquipDestructorObject*)object)->methods = D_182990;
        func_2CEAF0(object, 0);
        if ((s16)flags > 0)
        {
            func_100B40(object);
        }
    }
    return object;
}

void* func_00351520(void* object, s32 flags)
{
    if (object != 0)
    {
        ((EquipDestructorObject*)object)->methods = D_182B90;
        func_2CEAF0(object, 0);
        if ((s16)flags > 0)
        {
            func_100B40(object);
        }
    }
    return object;
}

void* func_00351580(void* object, s32 flags)
{
    if (object != 0)
    {
        ((EquipDestructorObject*)object)->methods = D_182C90;
        func_2CEAF0(object, 0);
        if ((s16)flags > 0)
        {
            func_100B40(object);
        }
    }
    return object;
}

u32 func_003515E0(void* object)
{
    return ((EquipEntryFields*)object)->field_3c & 1;
}

s32 func_003515F0(void* object)
{
    return 4;
}

void func_00351600(void* object, u32 value)
{
    ((EquipEntryFields*)object)->field_24 = value;
}

u32 func_00351610(void* object)
{
    return ((EquipEntryFields*)object)->field_24;
}

void func_00351620(void* object, s8 value)
{
    ((EquipEntryFields*)object)->field_28 = value;
}

s8 func_00351630(void* object)
{
    return ((EquipEntryFields*)object)->field_28;
}

s32 func_00351640(void* object)
{
    return 0;
}

s32 func_00351650(void* object)
{
    return 0;
}

void func_00351660(void* object)
{
}

void func_00351670(void* object)
{
}

void func_00351680(void* object)
{
}

void func_00351690(void* object)
{
}

s32 func_003516A0(void* object)
{
    return 0;
}

s32 func_003516B0(void* object)
{
    return 0;
}

s32 func_003516C0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_003516D0);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00351750);

void func_003517D0(EquipLinkedList* list, s16 value)
{
    EquipLinkedNode* node;
    EquipLinkedNode* cursor;
    node = (EquipLinkedNode*)func_100AC0(8, 0);
    if (node != 0)
    {
        node->value = value;
        node->next = 0;
        cursor = list->head;
        while (cursor->next != 0)
        {
            cursor = cursor->next;
        }
        cursor->next = node;
        list->count++;
    }
}

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00351860);

void* func_003518E0(void* object, s32 count)
{
    EquipLinkedNode* node = ((EquipLinkedList*)object)->head->next;
    s32 index = 0;
    while (index < count)
    {
        if (node == 0)
        {
            return 0;
        }
        index++;
        node = node->next;
    }
    return node;
}

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00351920);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_003519A0);

void func_00351A20(EquipWordList* list, u32 value)
{
    EquipWordNode* node;
    EquipWordNode* cursor;
    node = (EquipWordNode*)func_100AC0(8, 0);
    if (node != 0)
    {
        node->value = value;
        node->next = 0;
        cursor = list->head;
        while (cursor->next != 0)
        {
            cursor = cursor->next;
        }
        cursor->next = node;
        list->count++;
    }
}

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00351AB0);

void* func_00351B30(void* object, s32 count)
{
    EquipWordNode* node = ((EquipWordList*)object)->head->next;
    s32 index = 0;
    while (index < count)
    {
        if (node == 0)
        {
            return 0;
        }
        index++;
        node = node->next;
    }
    return node;
}

void func_00351B70(EquipWordList* list, u32 value)
{
    EquipWordNode* node;
    EquipWordNode* cursor;
    node = (EquipWordNode*)func_100AC0(8, 0);
    if (node != 0)
    {
        node->value = value;
        node->next = 0;
        cursor = list->head;
        while (cursor->next != 0)
        {
            cursor = cursor->next;
        }
        cursor->next = node;
        list->count++;
    }
}

void func_00351C00(EquipWordList* list, u32 value)
{
    EquipWordNode* node;
    EquipWordNode* cursor;
    node = (EquipWordNode*)func_100AC0(8, 0);
    if (node != 0)
    {
        node->value = value;
        node->next = 0;
        cursor = list->head;
        while (cursor->next != 0)
        {
            cursor = cursor->next;
        }
        cursor->next = node;
        list->count++;
    }
}

void func_00351C90(EquipWordList* list, u32 value)
{
    EquipWordNode* node;
    EquipWordNode* cursor;
    node = (EquipWordNode*)func_100AC0(8, 0);
    if (node != 0)
    {
        node->value = value;
        node->next = 0;
        cursor = list->head;
        while (cursor->next != 0)
        {
            cursor = cursor->next;
        }
        cursor->next = node;
        list->count++;
    }
}

void func_00351D20(EquipWordList* list, u32 value)
{
    EquipWordNode* node;
    EquipWordNode* cursor;
    node = (EquipWordNode*)func_100AC0(8, 0);
    if (node != 0)
    {
        node->value = value;
        node->next = 0;
        cursor = list->head;
        while (cursor->next != 0)
        {
            cursor = cursor->next;
        }
        cursor->next = node;
        list->count++;
    }
}

void func_00351DB0(EquipWordList* list, u32 value)
{
    EquipWordNode* node;
    EquipWordNode* cursor;
    node = (EquipWordNode*)func_100AC0(8, 0);
    if (node != 0)
    {
        node->value = value;
        node->next = 0;
        cursor = list->head;
        while (cursor->next != 0)
        {
            cursor = cursor->next;
        }
        cursor->next = node;
        list->count++;
    }
}

void func_00351E40(EquipWordList* list, u32 value)
{
    EquipWordNode* node;
    EquipWordNode* cursor;
    node = (EquipWordNode*)func_100AC0(8, 0);
    if (node != 0)
    {
        node->value = value;
        node->next = 0;
        cursor = list->head;
        while (cursor->next != 0)
        {
            cursor = cursor->next;
        }
        cursor->next = node;
        list->count++;
    }
}

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00351ED0);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00351EE0);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00351EF0);

INCLUDE_ASM("build/overlays/cequip/asm/nonmatchings/text", func_00351F00);
