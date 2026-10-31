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
#include "main/resident_00101260.h"
#include "overlays/1067-00/text_00200710.h"
#include "overlays/1067-00/text_001E6C50.h"
#include "overlays/lib/render_buffer.h"
#include "overlays/lib/text_0046AE20.h"
#include "overlays/1067-00/text_0022DC70.h"
#include "sdk/main/libkernl_00121940.h"
#include "overlays/lib/text_00429B00.h"
#include "overlays/cequip/cequip.h"
#include "overlays/cstatus/text.h"
#include "overlays/cskill/text.h"
#include "overlays/citem/citem.h"
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

extern "C" s32 resident_sound_is_active(ResidentSound* request, s32 handle);

extern "C" s32 resident_sound_stop(ResidentSound* request, s32 handle, s32 flag);

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
        manager->sounds[index] = resident_sound_play(g_sound, index, 0, 0, 0x7F, 0x40, 0);
    }
    else
    {
        if (static_cast<u8>(resident_sound_is_active(g_sound, manager->sounds[index])) == 1)
        {
            manager->unk5c = static_cast<u8>(resident_sound_stop(g_sound, manager->sounds[index], 0));
            manager->sounds[index] = -1;
        }

        manager->sounds[index] = resident_sound_play(g_sound, sound, 0, 0, 0x7F, 0x40, 0);
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
    resident_enqueue_object(g_resident_release_queues, this);
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
    memset_guess(sounds, 0, sizeof(sounds));
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

void FieldClass15B040::update_requests(s32 cancel_request)
{
    ResidentContext* context = D_001B6430->context;

    if (context->unkdd.unk4 || context->unkdd.unk6)
    {
        return;
    }

    if (request_state == 0)
    {
        if (cancel_request != 0)
        {
            return;
        }

        if (!(context->unk58->unk1e0 <= 0.0f))
        {
            return;
        }

        if (field_records_blocked())
        {
            return;
        }

        while (current_request < request_count)
        {
            if (!requests[current_request].unk16_0)
            {
                break;
            }

            current_request++;
        }

        func_00433AA0();
        FlushCache(0);
        u32 size = requests[current_request].byte_capacity + 0x80;
        void* buffer = func_00433880(size, 0);

        if (buffer == 0)
        {
            FieldResourceLoaderList* manager = static_cast<FieldResourceLoaderList*>(owner);
            FieldClass150060* node = reinterpret_cast<FieldClass150060*>(&manager->sentinel);
            u8 busy = 0;

            for (;;)
            {
                node = node->unk08;

                if (reinterpret_cast<FieldClass150060*>(&manager->sentinel) == node)
                {
                    break;
                }

                FieldResourceLoadTask* loader = static_cast<FieldResourceLoadTask*>(node);

                if ((loader->get_load_kind() == 1 || loader->get_load_kind() == 2) && this != loader && loader->poll_request_release() == 1)
                {
                    busy = 1;
                }
            }

            if (busy)
            {
                return;
            }

            buffer = func_00433880(size, 0);

            if (buffer == 0)
            {
                return;
            }
        }

        if (buffer != 0)
        {
            FieldResourceRequest* record = &requests[current_request];
            record->buffer_base = (u32)buffer;
            record->unk08_0 = 0;
            start_current_read();
        }
    }
    else
    {
        FieldResourceLoader::update_requests(cancel_request);
    }
}

FieldClass15B040::~FieldClass15B040()
{
    if (!unk34_0)
    {
        D_001B6430->context->unk58->unk1c8 = 0;
    }
}

extern "C" u32 D_001B65B8;

/** @brief Advance the field random seed with the 1664525/1013904223 linear congruential step. @return New seed. */
static inline u32 field_random()
{
    return D_001B65B8 = 1664525L * D_001B65B8 + 1013904223L;
}

/** Partial FieldClass150F90 with vtable D_15B090 in main data. */
class FieldClass15B090 : public FieldClass150F90
{
public:
    FieldClass15B090();

    /** @brief Destroy the object. */
    virtual ~FieldClass15B090();

    /** @brief Fade, spin and drop the object, releasing it once it has faded out. */
    virtual void update();

    /** @brief Run the base release handler, detach the object, then release it. */
    virtual void func_00204E40();

    /** @brief Forward the object to func_00204FC0. */
    virtual void func_001DE3B0();

    float unka0;
    float unka4;
    float unka8;
    float unkac;
    float unkb0;
    u8 unkb4_0 : 1;
    u8 unkb4_1 : 1;
    u8 unkb4_2_7 : 6;
    u8 unkb5[0xB];
};

FieldClass15B090::~FieldClass15B090()
{
}

void FieldClass15B090::func_00204E40()
{
    FieldClass150F90::func_00204E40();
    lib_object_detach_owner(this);
    func_001DD7B0();
}

extern "C" void func_00204FC0(void* object);

void FieldClass15B090::func_001DE3B0()
{
    func_00204FC0(this);
}

void FieldClass15B090::update()
{
    if (!unkb4_1)
    {
        unkb0 = unk20.y;
        unkb4_1 = 1;
    }

    unka0 -= g_frame_ticks;

    if (unka0 <= 0.0f)
    {
        float scale = (unka0 + 16.0f) / 16.0f;
        unk40.z = scale;
        unk40.x = scale;

        if (scale <= 0.0f)
        {
            lib_object_detach_owner(this);
            func_001DD7B0();
            return;
        }

        unk8c_4 = 1;
    }

    float dt = g_frame_ticks;
    float speed = unkb4_0 ? 0.05f : -0.05f;
    unka4 += speed * dt;
    LibVector4 direction;
    LibVector4 angles;
    LibVector4 rotation;
    direction.components[0] = -lib_sine_degree9(unka4);
    direction.components[1] = 0.0f;
    direction.components[2] = lib_cosine_degree9(unka4);
    angles.components[0] = 0.0f;
    angles.components[1] = 0.0f;
    angles.components[2] = 0.0f;
    angles.components[3] = 1.0f;
    lib_direction_angles_xz(&angles, &direction, 0.0f);
    func_004CE4C0(rotation.components, angles.components);
    func_004CD3A0(reinterpret_cast<FieldVec4B*>(&unk30), reinterpret_cast<FieldVec4B*>(&unk30), reinterpret_cast<FieldVec4B*>(&rotation), 1.0f);
    unk20.y += unka8 * g_frame_ticks;
    unka8 += 0.5f * g_frame_ticks;

    if (!(unk20.y <= unkb0))
    {
        unk20.y = unkb0;
        unkac = unka8 = 0.5f * unkac;
    }

    FieldClass150F90::update();
}

/** Partial renderable entry with its kind and flags. */
struct FieldRenderableEntry
{
    u8 unk00[0x6A];
    u16 flags;
    u16 kind;
};

FieldClass15B090::FieldClass15B090()
{
    unk78 |= 0x20000;
    unk70 = 0x7FFFFFFF;
    unka0 = 285.0f;
    unka4 = 0.0f;
    unka8 = -10.0f;
    unkac = -10.0f;
    unkb4_0 = field_random() & 1;
    unkb4_1 = 0;
    unk74 = 0xF900;
    func_00204A10(0xF900);

    for (FieldRenderableEntry* entry = static_cast<FieldRenderableEntry*>(lib_find_renderable_entry(static_cast<LibEntryManager*>(unk7c), 0)); entry != 0;
         entry = static_cast<FieldRenderableEntry*>(func_00472EB0(unk7c, entry)))
    {
        if (entry->kind == 0x100)
        {
            entry->flags |= 0x1000;
        }
    }
}

/** Partial Lib display object with vtables D_1538D0, D_1538EC and D_153960 in main data. */
class FieldClass1538D0 : public LibClass178A70, public LibClass174610
{
};

/** Partial resident state entry 4: a timer and its counters. */
struct FieldResidentEntry4
{
    u8 unk00[0xD];
    u8 flags;
    u8 unk0e[0x1B6];
    s32 unk1c4;
    float unk1c8;
    u8 unk1cc[8];
    u8 unk1d4[0xC];
};

/** @brief Return resident state entry 4. @return Entry 4. */
static inline FieldResidentEntry4* resident_entry4()
{
    return reinterpret_cast<FieldResidentEntry4*>(resident_find_entry(resident_get_entry_table(resident_get_runtime_owner()), 4));
}

/**
 * @brief Pick a random pair from a 0xFFFF-terminated pair list.
 * @param pairs First pair; left at the terminator.
 * @param first Receives the pair's first value.
 * @param second Receives the pair's second value.
 * @return Always one.
 */
static inline s32 pick_pair(u16*& pairs, u32* first, u32* second)
{
    u16* start = pairs;
    s32 count = 0;

    while (*pairs != 0xFFFF)
    {
        pairs += 2;
        count++;
    }

    u16* pair = start + (field_random() % count) * 2;
    *first = pair[0];
    *second = pair[1];
    return 1;
}

static inline void release_container(FieldClass15B0E0* object)
{
    object->unk50 = 0;

    if (object->unk4c != 0)
    {
        object->unk4c->func_003EF740();
        object->unk4c = 0;
    }

    object->unk55_3 = 0;
}

static inline void release_retained(FieldClass15B0E0* object)
{
    if (object->unk44 != 0)
    {
        object->unk44->func_003EF740();
        object->unk44 = 0;
    }

    if (!object->unk55_1)
    {
        delete object->unk40;
        object->unk40 = 0;
    }

    object->unk40 = 0;
    object->unk55_1 = 0;
    object->unk24 = 10.0f;
}

static inline void reset_entry_timer(FieldClass15B0E0* object)
{
    FieldResidentEntry4* entry = resident_entry4();
    entry->unk1c8 = 0.0f;
    entry->unk1c4 = 0;
    s32 flags = entry->flags;
    flags &= ~1;
    entry->flags = flags;
    object->unk28 = -140.0f;
    memset_guess(entry->unk1d4, 0, sizeof(entry->unk1d4));
}

void FieldClass15B0E0::func_002D1D70()
{
    release_container(this);
}

void FieldClass15B0E0::func_001DDB30(void* arg)
{
    unk20 = 0;
}

s32 FieldClass15B0E0::func_002D1DE0(u32* first, u32* second, s32 level)
{
    u16* entry = table;

    if (entry == 0)
    {
        return 0;
    }

    if (*entry != 0xFFFF)
    {
        do
        {
            if (level < *entry)
            {
                entry++;
                return pick_pair(entry, first, second);
            }

            u16* group = entry;

            while (*entry != 0xFFFF)
            {
                entry++;
            }

            entry++;

            if (*entry == 0xFFFF)
            {
                group++;
                return pick_pair(group, first, second);
            }
        } while (*entry != 0xFFFF);
    }

    return 0;
}

void FieldClass15B0E0::func_002D1FD0()
{
    table = static_cast<u16*>(func_00201EA0(D_001B6430->context->unk2c, 'ITEM', 0, 0));
}

void FieldClass15B0E0::func_002D2020()
{
    if (unk48 != 0)
    {
        unk48->unk4d_3 = 1;
    }
}

void FieldClass15B0E0::func_001DD7B0()
{
    release_retained(this);
    resident_enqueue_object(g_resident_release_queues, this);

    if (unk48 != 0)
    {
        unk48->func_001DD7B0();
        unk48 = 0;
    }

    release_container(this);
}

void FieldClass15B0E0::func_002D2170()
{
    release_retained(this);
}

void FieldClass15B0E0::func_002D2210(s32 flag)
{
    if (flag != 0 && !unk55_0)
    {
        resident_entry4()->unk1c8 = 0.0f;
    }

    unk55_0 = flag;
    unk38 = unk34;
    unk34 = D_001B6430->context->unk08->unkb8;
    unk24 = 10.0f;
}

s32 FieldClass15B0E0::func_002D22B0(const FieldVec4A* position)
{
    if (table == 0)
    {
        return 0;
    }

    FieldClass15B090* child = new (0) FieldClass15B090;

    if (child == 0)
    {
        return 0;
    }

    child->func_00205710(position);
    static_cast<LibClass178DD0*>(D_001B6430->context->unk04)->append_node(child, LibClass178DD0::DEFAULT_NODE_KIND);
    FieldResidentEntry4* entry = resident_entry4();
    entry->flags = (entry->flags & ~1) | 1;
    entry->unk1c4++;
    entry->unk1c8 = 540.0f;
    return 1;
}

void FieldClass15B0E0::func_002D23B0()
{
    float* timer = &resident_entry4()->unk1c8;

    if (*timer > 1.0f)
    {
        *timer -= 3.0f;

        if (*timer < 1.0f)
        {
            *timer = 1.0f;
        }
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CEAF0", update__16FieldClass15B0E0Fv);

void FieldClass15B0E0::func_002D3920()
{
    reset_entry_timer(this);
}

FieldClass15B0E0::~FieldClass15B0E0()
{
    if (unk20 != 0)
    {
        unk20->func_003EF740();
        unk20 = 0;
    }
}

FieldClass15B0E0::FieldClass15B0E0()
{
    unk55_0 = 0;
    unk55_1 = 0;
    unk55_2 = 0;
    unk55_3 = 0;
    unk24 = 0.0f;
    unk28 = -140.0f;
    unk2c = 0;
    unk3c = 0;
    unk40 = 0;
    unk44 = 0;
    unk48 = 0;
    table = 0;
    unk20 = 0;
    unk54 = -1;
    unk4c = 0;
    unk50 = 0;
    reset_entry_timer(this);
}

s32 FieldClass15B0E0::get_default_list_kind()
{
    return 4;
}
