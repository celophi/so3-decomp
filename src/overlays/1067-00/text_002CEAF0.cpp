#include "include_asm.h"
#include "main/resident_data.h"
#include "main/resident_0010A0E0.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/1067-00/text_00202240.h"
#include "overlays/1067-00/text_002CEAF0.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_002636B0.h"
#include "overlays/1067-00/text_002607B0.h"
#include "overlays/1067-00/text_0020E4B0.h"
#include "overlays/1067-00/text_0023B1D0.h"
#include "sdk/main/libc_guess_0013A4C0.h"
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

extern "C" u8 func_0022A160(FieldScreenTransition* transition);

extern "C" void* D_001B6694;

/** Menu manager with vtable D_15B020 in main data; it loads the requested menu and runs its controller. */
class FieldMenuManager : public FieldListObject
{
    public:
        FieldMenuManager();

        virtual ~FieldMenuManager();

        /** @brief Report this object's list kind. @return Always 3. */
        virtual s32 get_default_list_kind();

        /** @brief Detach the manager and add it to the resident release queue. */
        virtual void func_001DD7B0();

        /**
         * @brief Pass the pad's buttons to the active window and play the sound for its result.
         * @param window Active window.
         * @return One once the menu is running; zero for a null window or while loading.
         */
        u8 handle_input(FieldClass15AE70* window);

        /** @brief Load the requested menu, poll the active controller for the next menu or a close request, flush deferred window removals and fade out on close. */
        virtual void update();

        FieldClass153E30* state;
        u8 menu;
        u8 unk19;
        u16 argument;
        FieldClass153E00* owner;
        FieldResourceRequestHandler* request;
        s32 resource_key;
        u8 phase;
        u8 load_state;
        u16 unk2a;
        u8 skip_transition;
        u8 unk2d[3];
        FieldClass153EC0 removals;
        s32 sounds[8];
        u32 unk5c;
        u8 ready;
        u8 closed;
        u8 unk62;
        u8 unk63;
        float transition_time;
        u8 shown;
        u8 unk69[3];
        u32 unk6c;
        u8 unk70;
        u8 unk71[3];
        float timer;
        u32 unk78;
        u32 unk7c;
        u32 unk80;
        u32 unk84;
        u8 unk88;
};

/**
 * @brief Select the resources for a menu.
 * @param owner Menu owner.
 * @param menu Menu to open.
 * @param argument Menu argument.
 * @return The menu's keyed resource, or -1 when it has none.
 */
static inline s32 menu_resource_key(FieldClass153E00* const& owner, s32 menu, s32 argument)
{
    return func_00261160(owner, menu, argument);
}

/** Partial resident object reached through the menu runtime. */
struct FieldMenuRuntimeObject
{
    u8 unk00[0x40];
    u8 unk40;
};

/** Partial resident menu runtime. */
struct FieldMenuRuntime
{
    u8 unk00[0xC];
    FieldMenuRuntimeObject* unk0c;
    FieldMenuManager* manager;
};

extern "C" FieldMenuRuntime* D_001B643C;

extern "C" s32 func_110C10(ResidentRequest112400* request, s32 handle);

extern "C" s32 func_110920(ResidentRequest112400* request, s32 handle, s32 flag);

/** Partial pad state with its button masks. */
struct FieldMenuPad
{
    u8 unk00[0x14];
    u32 unk14;
    u8 unk18[0xC];
    u32 pressed;
    u8 unk28[4];
    u32 repeat;
};

/** @brief Return the pad state. @return Pad state. */
static inline FieldMenuPad* menu_pad()
{
    return reinterpret_cast<FieldMenuPad*>(D_001B6430->context->input);
}

/** @brief Return the configured button masks. @return Button masks, one per menu command. */
static inline u16* menu_buttons()
{
    return reinterpret_cast<u16*>(D_001B6430->unk04);
}

extern "C" void func_00264580(FieldCountedList* list);

extern "C" s32 func_00264650(FieldCountedList* list, void** value);

/** @brief Return the field object that owns the screen effects. @return Field display object. */
static inline FieldClass1516A0* field_display()
{
    return reinterpret_cast<FieldClass1516A0*>(D_001B6430->context->unk38);
}

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

s32 FieldMenuManager::get_default_list_kind()
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

/**
 * @brief Start one of the menu's eight sounds, restarting it when it is already playing.
 * @param manager Menu manager.
 * @param sound Sound slot.
 * @return One when the sound was started; zero for a slot out of range.
 */
static inline s32 play_menu_sound(FieldMenuManager* manager, s16 sound)
{
    u32 index = sound;

    if (sound < 0 || sound >= 8)
    {
        return 0;
    }

    if (manager->sounds[index] == -1)
    {
        manager->sounds[index] = resident_allocate_request(D_001B65F8, index, 0, 0, 0x7F, 0x40, 0);
    }
    else
    {
        if (static_cast<u8>(func_110C10(D_001B65F8, manager->sounds[index])) == 1)
        {
            manager->unk5c = static_cast<u8>(func_110920(D_001B65F8, manager->sounds[index], 0));
            manager->sounds[index] = -1;
        }

        manager->sounds[index] = resident_allocate_request(D_001B65F8, sound, 0, 0, 0x7F, 0x40, 0);
    }

    return 1;
}

/**
 * @brief Start one of the menu's eight sounds.
 * @param manager Menu manager.
 * @param sound Sound slot.
 * @return One when the sound was started; zero for a slot out of range.
 */
extern "C" s32 field_play_menu_sound(FieldMenuManager* manager, s16 sound)
{
    return play_menu_sound(manager, sound);
}

u8 FieldMenuManager::handle_input(FieldClass15AE70* window)
{
    if (window == 0)
    {
        return 0;
    }

    if (phase != 6)
    {
        return 0;
    }

    u8 result = 0;
    u32 pressed = menu_pad()->pressed;
    u32 repeat = menu_pad()->repeat;

    if (unk78 != 0)
    {
        unk78--;
    }

    if (unk7c != 0)
    {
        unk7c--;
    }

    if (unk80 != 0)
    {
        unk80--;
    }

    if (unk84 != 0)
    {
        unk84--;
    }

    if (pressed & menu_buttons()[0])
    {
        result = window->func_slotb0();
    }
    else if (pressed & menu_buttons()[1])
    {
        result = window->func_slotb4();
    }
    else if (pressed & menu_buttons()[2])
    {
        result = window->func_slotb8();
    }
    else if (pressed & menu_buttons()[3])
    {
        result = window->func_slotbc();
    }
    else
    {
        if ((repeat & menu_buttons()[4]) && unk78 == 0)
        {
            unk78 = 4;
            result = window->func_slotd0();

            if (result != 0)
            {
                goto play;
            }
        }

        if ((repeat & menu_buttons()[5]) && unk7c == 0)
        {
            unk7c = 4;
            result = window->func_slotd4();

            if (result != 0)
            {
                goto play;
            }
        }

        if ((repeat & menu_buttons()[6]) && unk80 == 0)
        {
            unk80 = 4;
            result = window->func_slotd8();

            if (result != 0)
            {
                goto play;
            }
        }

        if ((repeat & menu_buttons()[7]) && unk84 == 0)
        {
            unk84 = 4;
            result = window->func_slotdc();

            if (result != 0)
            {
                goto play;
            }
        }

        if (pressed & menu_buttons()[4])
        {
            result = window->func_slotc0();
        }
        else if (pressed & menu_buttons()[5])
        {
            result = window->func_slotc4();
        }
        else if (pressed & menu_buttons()[6])
        {
            result = window->func_slotc8();
        }
        else if (pressed & menu_buttons()[7])
        {
            result = window->func_slotcc();
        }
        else if (pressed & 8)
        {
            window->func_slote0();
        }
        else if (pressed & 1)
        {
            window->func_slote4();
        }
        else
        {
            if (window->func_slote8())
            {
                if (pressed & 0x10)
                {
                    window->func_slota0();
                    goto play;
                }

                if (pressed & 0x40)
                {
                    window->func_slota4();
                    goto play;
                }

                if (pressed & 0x80)
                {
                    window->func_slota8();
                    goto play;
                }

                if (pressed & 0x20)
                {
                    window->func_slotac();
                    goto play;
                }
            }


            u16* buttons = menu_buttons();
            FieldMenuPad* pad = menu_pad();

            if (buttons[0] & pad->unk14)
            {
                window->func_slot78();
            }
            else if (buttons[1] & pad->unk14)
            {
                window->func_slot7c();
            }
            else if (buttons[2] & pad->unk14)
            {
                window->func_slot80();
            }
            else if (buttons[3] & pad->unk14)
            {
                window->func_slot84();
            }
            else if (buttons[4] & pad->unk14)
            {
                window->func_slot88();
            }
            else if (buttons[5] & pad->unk14)
            {
                window->func_slot8c();
            }
            else if (buttons[6] & pad->unk14)
            {
                window->func_slot90();
            }
            else if (buttons[7] & pad->unk14)
            {
                window->func_slot94();
            }
            else if (pad->unk14 & 8)
            {
                window->func_slot98();
            }
            else if (pad->unk14 & 1)
            {
                window->func_slot9c();
            }
            else
            {
                if (menu_pad()->repeat & 0x10)
                {
                    window->func_slot68();
                }

                if (menu_pad()->repeat & 0x40)
                {
                    window->func_slot6c();
                }

                if (menu_pad()->repeat & 0x80)
                {
                    window->func_slot70();
                }

                if (menu_pad()->repeat & 0x20)
                {
                    window->func_slot74();
                }
            }
        }
    }

play:
    switch (result)
    {
        case 1:
            play_menu_sound(this, 1);
            break;
        case 2:
            play_menu_sound(this, 2);
            break;
        case 3:
            play_menu_sound(this, 3);
            break;
        case 4:
            play_menu_sound(this, 0);
            break;
        case 0:
            break;
    }

    return 1;
}

/**
 * @brief Create the requested menu's controller, register it, and make it the active State.
 *
 * Every menu overlay loads at the same address, so each case calls the
 * constructor of whichever overlay the manager loaded for that menu.
 * @param manager Menu manager.
 * @param menu Menu to open.
 * @return True when the controller's record selection was created; false for an unknown menu.
 */
extern "C" s32 field_launch_menu(FieldMenuManager* manager, u8 menu)
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

/**
 * @brief Advance the menu load: request resources, fade out, release the old controller, launch the new one and fade in.
 * @param manager Menu manager.
 * @return Load state after this step, or zero while waiting on resources or when the launch fails.
 */
extern "C" u8 field_advance_menu_load(FieldMenuManager* manager)
{
    switch (manager->load_state)
    {
        case 0:
            break;
        case 1:
            manager->ready = 0;
            manager->resource_key = menu_resource_key(manager->owner, manager->menu, manager->argument);

            if (manager->resource_key != -1)
            {
                field_start_keyed_resource_request(manager->request, manager->resource_key, 1);
                field_set_next_resource_request(manager->request, manager->owner->menu_resource_key, 0);
            }
            else
            {
                field_start_keyed_resource_request(manager->request, manager->owner->menu_resource_key, 0);
            }

            if (manager->skip_transition != 0)
            {
                manager->skip_transition = 0;
                manager->load_state = 5;
                manager->transition_time = 4.0f;
            }
            else
            {
                func_0020F230(field_display(), 0, 0, 0x80000000, 0, 0, 0, 10.0f, 0.0f, 0.0f);
                FieldScreenTransition* transition;
                (transition = field_display()->effects.transition)->unkc0 = D_001B6694;
                transition->unkf0 = 10;
                manager->load_state = 2;
                manager->transition_time = 4.0f;
            }

            break;
        case 2:
            if (func_0022A160(field_display()->effects.transition) == 0)
            {
                manager->load_state = 3;
            }

            break;
        case 3:
            if (manager->state != 0)
            {
                func_00264010(manager->state);
                manager->state->func_slot5c();
                manager->state = 0;
            }

            manager->ready = 0;

            if (manager->resource_key != -1)
            {
                manager->load_state = 4;
            }
            else
            {
                manager->load_state = 5;
            }

            break;
        case 4:
            if (manager->request->unk1e == 0)
            {
                return 0;
            }

            manager->load_state = 5;
        case 5:
        {
            FieldClass153E00* owner = manager->owner;

            if (owner->unk3c->unk09 == 0)
            {
                return 0;
            }

            if (owner->unk2e == 0)
            {
                return 0;
            }

            if (manager->request->unk20 == 0)
            {
                return 0;
            }

            if (manager->request->unk1c == 0)
            {
                return 0;
            }

            manager->request->unk28 = manager->menu;

            bool launched = field_launch_menu(manager, manager->menu);

            if (!launched)
            {
                return 0;
            }

            manager->request->deliver_completed_request();
            manager->load_state = 6;
        }
        case 6:
        {
            func_0020F230(field_display(), 0, 0x80000000, 0, 0, 0, 0, manager->transition_time, 0.0f, 0.0f);
            FieldScreenTransition* transition = field_display()->effects.transition;
            void* value = D_001B6694;
            FieldTransitionRect rect;
            rect.bounds[0] = 0;
            rect.bounds[1] = 0;
            rect.bounds[2] = 768;
            rect.bounds[3] = 448;
            const s32* source = rect.bounds;

            for (s32 i = 0; i < 4; i++)
            {
                transition->rect.bounds[i] = source[i];
            }

            transition->unkc0 = value;
            transition->unkf0 = 10;
            manager->load_state = 7;
            manager->timer = 0.0f;
        }
        case 7:
            if (func_0022A160(field_display()->effects.transition) == 0)
            {
                manager->load_state = 8;
                static_cast<FieldClass15AE70*>(manager->state->func_00261150())->func_slot24(0);
            }

            if (!(manager->timer < 2.0f))
            {
                manager->ready = 1;
            }
            else
            {
                manager->timer += 1.0f;
            }

            break;
    }

    return manager->load_state;
}

void FieldMenuManager::update()
{
    switch (phase)
    {
        case 0:
            break;
        case 1:
            phase = 2;
            break;
        case 2:
            phase = 3;
            break;
        case 3:
            if (menu == 0)
            {
                break;
            }

            phase = 4;
            load_state = 1;
        case 4:
            if (field_advance_menu_load(this) != 8)
            {
                break;
            }

            phase = 6;
        case 6:
        {
            if (state == 0)
            {
                break;
            }

            FieldClass15AE70* window = static_cast<FieldClass15AE70*>(state->func_00261150());
            u8 next = window->func_slot30();

            if (next != 0)
            {
                switch (next & 0xFF)
                {
                    case 0xFF:
                        phase = 7;
                        break;
                    default:
                        menu = next;

                        if (window->func_slot38() != 0x80)
                        {
                            argument = window->func_slot38();
                        }

                        phase = 4;
                        load_state = 1;
                        break;
                }

                return;
            }

            state->func_00263E90();

            if (ready == 0)
            {
                break;
            }

            FieldClass153270* child = state->unk30;

            if (child != 0)
            {
                switch (child->unk18)
                {
                    case 1:
                        return;
                    case 2:
                        child->unk18 = 3;
                        break;
                }
            }

            handle_input(window);

            if (removals.count != 0)
            {
                void* value = 0;

                while (func_00264650(&removals, &value))
                {
                    state->remove_child(value);
                }

                func_00264580(&removals);
            }

            if (shown == 0)
            {
                shown = 1;
            }

            break;
        }
        case 7:
        {
            func_0020F230(field_display(), 0, 0, 0x80000000, 0, 0, 0, 10.0f, 0.0f, 0.0f);
            FieldScreenTransition* transition;
            (transition = field_display()->effects.transition)->unkc0 = D_001B6694;
            transition->unkf0 = 10;
            phase = 8;
            break;
        }
        case 8:
            if (func_0022A160(field_display()->effects.transition) != 0)
            {
                break;
            }

            if (state != 0)
            {
                FieldClass15AE70* window = static_cast<FieldClass15AE70*>(state->func_00261150());

                if (window->func_slot38() == 0x40)
                {
                    D_001B643C->unk0c->unk40 = 1;
                }

                func_00264010(state);
                state->func_slot5c();
                state = 0;
            }

            closed = 1;
            phase = 9;
            break;
        case 9:
            break;
    }
}

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

void FieldMenuManager::func_001DD7B0()
{
    lib_object_detach_owner(this);
    resident_enqueue_object(D_001B65F4, this);
}

FieldMenuManager::~FieldMenuManager()
{
}

FieldMenuManager::FieldMenuManager()
{
    state = 0;
    resource_key = 0;
    menu = 0;
    argument = 0x80;
    owner = 0;
    request = 0;
    unk80 = 0;
    unk84 = 0;
    phase = 3;
    load_state = 0;
    unk2a = 0;
    skip_transition = 0;
    func_0013A678(sounds, 0, sizeof(sounds));
    unk5c = 0;
    ready = 0;
    unk62 = 0;
    closed = 0;
    shown = 0;
    transition_time = 0.0f;
    unk6c = 0;
    unk70 = 0;
    timer = 0.0f;
    unk88 = 0;
    unk78 = 0;
    // unk80 and unk84 are cleared twice in the original.
    unk80 = 0;
    unk7c = 0;
    unk84 = 0;
}

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
