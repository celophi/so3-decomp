#include "include_asm.h"
#include "main/resident_data.h"
#include "main/resident_0010A0E0.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/1067-00/text_00202240.h"
#include "overlays/1067-00/text_002CEAF0.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_002636B0.h"
#include "overlays/cequip/cequip.h"
#include "overlays/cstatus/text.h"
#include "overlays/cskill/text.h"
#include "overlays/citem/item_controller.h"
#include "overlays/cconfig/config_controller.h"
#include "overlays/cmc/text.h"
#include "overlays/ctactics/ctactics.h"
#include "overlays/cshop/cshop.h"
#include "overlays/citemcreation/text_003684D0.h"

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

/** Partial runtime directory containing the deferred window-removal list. */
struct FieldWindowRemovalContext
{
    u8 pad00[0x30];
    FieldCountedList pending_removals;
};

extern "C" void func_00264460(FieldCountedList* list, void* value);

/** Partial menu manager with vtable D_15B020 in main data; it creates the requested menu's controller. */
typedef struct FieldMenuManager
{
    u8 unk00[0x14];
    FieldClass153E30* state;
    u8 menu;
    u8 unk19;
    u16 argument;
    u8 unk1c[0x6C];
    u8 unk88;
} FieldMenuManager;

enum FieldMenuId
{
    FIELD_MENU_1 = 1,
    FIELD_MENU_EQUIP = 2,
    FIELD_MENU_STATUS = 3,
    FIELD_MENU_SKILL = 4,
    FIELD_MENU_ITEM = 5,
    FIELD_MENU_CONFIG = 6,
    FIELD_MENU_7 = 7,
    FIELD_MENU_TACTICS = 8,
    FIELD_MENU_SHOP = 11,
    FIELD_MENU_ITEM_CREATION = 12
};

FieldClass15AE70::~FieldClass15AE70()
{
}

FieldClass15AE70::FieldClass15AE70()
{
    unk04 = 0;
    unk08 = 0;
    unk0a = 0x80;
    unk0c = 0;
    unk10 = 0;
    unk98 = 0;
    unk9c = 0;
    unk0d = 0;
    unka4 = 0.0f;
    unka0 = 0;
}

FieldClass15B008::FieldClass15B008()
{
    head = new (0) FieldListNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

FieldClass15B008::~FieldClass15B008()
{
    func_002CEDA0(this);
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

/** @brief Delete every node after the head node and reset the count. @param list List to clear. */
extern "C" void func_002CEDA0(FieldCountedList* list)
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

FieldClass15AFF8::FieldClass15AFF8()
{
    head = new (0) FieldListNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

FieldClass15AFF8::~FieldClass15AFF8()
{
    func_002CEF20(this);
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

/** @brief Delete every node after the head node and reset the count. @param list List to clear. */
extern "C" void func_002CEF20(FieldCountedList* list)
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

/**
 * @brief Remove the first value from the list.
 * @param list List to take from.
 * @param value Receives the removed value.
 * @return One when a value was removed, otherwise zero.
 */
extern "C" s32 func_002CEFA0(FieldCountedList* list, void** value)
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

FieldClass15AFE8::FieldClass15AFE8()
{
    head = new (0) FieldListNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

FieldClass15AFE8::~FieldClass15AFE8()
{
    func_002CF110(this);
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

/** @brief Delete every node after the head node and reset the count. @param list List to clear. */
extern "C" void func_002CF110(FieldCountedList* list)
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

/**
 * @brief Remove the first value from the list.
 * @param list List to take from.
 * @param value Receives the removed value.
 * @return One when a value was removed, otherwise zero.
 */
extern "C" s32 func_002CF190(FieldCountedList* list, void** value)
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

FieldClass15AFD8::FieldClass15AFD8()
{
    head = new (0) FieldListNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

FieldClass15AFD8::~FieldClass15AFD8()
{
    func_002CF300(this);
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

/** @brief Delete every node after the head node and reset the count. @param list List to clear. */
extern "C" void func_002CF300(FieldCountedList* list)
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

FieldClass15AFC8::FieldClass15AFC8()
{
    head = new (0) FieldListNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

FieldClass15AFC8::~FieldClass15AFC8()
{
    func_002CF480(this);
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

/** @brief Delete every node after the head node and reset the count. @param list List to clear. */
extern "C" void func_002CF480(FieldCountedList* list)
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

FieldClass15AFB8::FieldClass15AFB8()
{
    head = new (0) FieldListNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

FieldClass15AFB8::~FieldClass15AFB8()
{
    func_002CF600(this);
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

/** @brief Delete every node after the head node and reset the count. @param list List to clear. */
extern "C" void func_002CF600(FieldCountedList* list)
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

FieldClass15AFA8::FieldClass15AFA8()
{
    head = new (0) FieldListNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

FieldClass15AFA8::~FieldClass15AFA8()
{
    func_002CF780(this);
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

/** @brief Delete every node after the head node and reset the count. @param list List to clear. */
extern "C" void func_002CF780(FieldCountedList* list)
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

FieldClass15AF98::FieldClass15AF98()
{
    head = new (0) FieldListNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

FieldClass15AF98::~FieldClass15AF98()
{
    func_002CF900(this);
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

/** @brief Delete every node after the head node and reset the count. @param list List to clear. */
extern "C" void func_002CF900(FieldCountedList* list)
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

FieldClass15AF88::FieldClass15AF88()
{
    head = new (0) FieldListNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

FieldClass15AF88::~FieldClass15AF88()
{
    func_002CFA80(this);
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

/** @brief Delete every node after the head node and reset the count. @param list List to clear. */
extern "C" void func_002CFA80(FieldCountedList* list)
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

FieldClass15AF78::FieldClass15AF78()
{
    head = new (0) FieldListNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

FieldClass15AF78::~FieldClass15AF78()
{
    func_002CFC00(this);
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

/** @brief Delete every node after the head node and reset the count. @param list List to clear. */
extern "C" void func_002CFC00(FieldCountedList* list)
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

FieldClass15AF68::FieldClass15AF68()
{
    head = new (0) FieldListNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

FieldClass15AF68::~FieldClass15AF68()
{
    func_002CFD80(this);
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

/** @brief Delete every node after the head node and reset the count. @param list List to clear. */
extern "C" void func_002CFD80(FieldCountedList* list)
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

/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 3.
 */
s32 func_002CFE00(FieldListObject* object)
{
    return 3;
}

void field_queue_window_removal(FieldWindowRemovalContext* context, FieldClass15AE70* window)
{
    if (window != 0)
    {
        func_00264460(&context->pending_removals, window);
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CFE40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002CFF60);

/**
 * @brief Create the requested menu's controller, register it, and make it the active State.
 *
 * Every menu overlay loads at the same address, so each case calls the
 * constructor of whichever overlay the manager loaded for that menu.
 * @param manager Menu manager.
 * @param menu Menu to open.
 * @return True when the controller's record selection was created; false for an unknown menu.
 */
extern "C" bool field_launch_menu(FieldMenuManager* manager, u8 menu)
{
    u8 result = 0;

    switch (menu)
    {
        case FIELD_MENU_1:
        {
            FieldClass154AD0* controller = new (0) FieldClass154AD0;
            D_001B6614->append_node(static_cast<FieldClass153E30*>(controller), LibClass178DD0::DEFAULT_NODE_KIND);
            manager->state = controller;
            result = controller->func_00264110();
            break;
        }
        case FIELD_MENU_ITEM:
        {
            ItemController* controller = new (0) ItemController;
            D_001B6614->append_node(static_cast<FieldClass153E30*>(controller), LibClass178DD0::DEFAULT_NODE_KIND);
            manager->state = controller;
            result = controller->func_00264110();
            break;
        }
        case FIELD_MENU_EQUIP:
        {
            EquipController* controller = new (0) EquipController;
            D_001B6614->append_node(static_cast<FieldClass153E30*>(controller), LibClass178DD0::DEFAULT_NODE_KIND);
            manager->state = controller;
            result = controller->func_00264110();
            break;
        }
        case FIELD_MENU_SKILL:
        {
            SkillController* controller = new (0) SkillController;
            D_001B6614->append_node(static_cast<FieldClass153E30*>(controller), LibClass178DD0::DEFAULT_NODE_KIND);
            manager->state = controller;
            result = controller->func_00264110();
            break;
        }
        case FIELD_MENU_STATUS:
        {
            StatusResourceState* controller = new (0) StatusResourceState;
            D_001B6614->append_node(static_cast<FieldClass153E30*>(controller), LibClass178DD0::DEFAULT_NODE_KIND);
            manager->state = controller;
            result = controller->func_00264110();
            break;
        }
        case FIELD_MENU_CONFIG:
        {
            ConfigController* controller = new (0) ConfigController;
            D_001B6614->append_node(static_cast<FieldClass153E30*>(controller), LibClass178DD0::DEFAULT_NODE_KIND);
            manager->state = controller;
            result = controller->func_00264110();
            break;
        }
        case FIELD_MENU_TACTICS:
        {
            TacticsController* controller = new (0) TacticsController;
            D_001B6614->append_node(static_cast<FieldClass153E30*>(controller), LibClass178DD0::DEFAULT_NODE_KIND);
            manager->state = controller;
            result = controller->func_00264110();
            break;
        }
        case FIELD_MENU_7:
        {
            CmcClass18AF20* controller = new (0) CmcClass18AF20;
            D_001B6614->append_node(static_cast<FieldClass153E30*>(controller), LibClass178DD0::DEFAULT_NODE_KIND);
            manager->state = controller;
            controller->func_00263CA0(manager->argument);
            result = controller->func_00264110();
            break;
        }
        case FIELD_MENU_SHOP:
        {
            ShopState* controller = new (0) ShopState;
            D_001B6614->append_node(static_cast<FieldClass153E30*>(controller), LibClass178DD0::DEFAULT_NODE_KIND);
            shop_set_id(controller, manager->argument);
            manager->state = controller;
            result = controller->func_00264110();
            break;
        }
        case FIELD_MENU_ITEM_CREATION:
        {
            ItemCreationSelectedDisplayState* controller = new (0) ItemCreationSelectedDisplayState;
            D_001B6614->append_node(static_cast<FieldClass153E30*>(controller), LibClass178DD0::DEFAULT_NODE_KIND);
            manager->state = controller;
            result = controller->func_00264110();
            break;
        }    }

    return result != 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D0D30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D1100);

s32 func_002D1440(FieldMenuManager* object, u8 value, u32 flags)
{
    object->menu = value;
    if (flags != 0)
    {
        object->argument = flags;
    }
    else
    {
        object->argument = 0;
    }
    if (((u16)flags) & 8)
    {
        object->unk88 = 0;
    }
    else
    {
        object->unk88 = 1;
    }
    return 1;
}

/** @brief Detach the object and add it to the resident release queue. @param object Object to release. */
extern "C" void func_002D1480(void* object)
{
    lib_object_detach_owner(object);
    resident_enqueue_object(D_001B65F4, object);
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
    lib_object_detach_owner(object);
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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", __ct__16FieldClass15B0E0Fv);

/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 4.
 */
s32 func_002D3BB0(FieldListObject* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", func_002D3BC0);
