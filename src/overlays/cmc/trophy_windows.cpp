#include "include_asm.h"
#include "overlays/cmc/cmc.h"
#include "overlays/1067-00/field_runtime.h"

extern "C" {
extern FieldWindowRuntime* D_001B643C;

extern void func_420D20(ItemCreationClass172870* object, u32 color);
}

/**
 * @brief Return the stored resource source word.
 * @return Stored word.
 */
u32 FieldClass15AE70::func_slot54()
{
    return unk04;
}

/**
 * @brief Request controller action 0x79 and hide the nested display.
 * @return One.
 */
u8 TrophyNoDataWindow::func_slotb0()
{
    CardMenuController* controller = unka8;

    if (controller != 0)
    {
        controller->unk54 = 0x79;

        if (controller->unk54 != 0)
        {
            controller->dispatch_window_request();
        }
    }

    func_slot20(0);
    return 1;
}

/**
 * @brief Create the window frame, its panel, and its resource text.
 * @param associated Full resource source word.
 * @return One.
 */
s32 TrophyNoDataWindow::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 56.0f, 200.0f, 13);
    LibPanel* panel = new (0) LibPanel;
    unkac = new (0) LibTextWidget;
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 528.0f, 128.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    lib_text_init_resource_rectangle(unkac, static_cast<s32>(associated), 0x234A, 0, 16.0f, 16.0f, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, unkac);
    return 1;
}

/** @brief Destroy the window. */
TrophyNoDataWindow::~TrophyNoDataWindow()
{
}

/**
 * @brief Request controller action 0x79, hide the nested display, and select the second choice.
 * @return Two.
 */
u8 TrophySkipConfirmWindow::func_slotb4()
{
    CardMenuController* controller = unka8;

    if (controller != 0)
    {
        controller->unk54 = 0x79;

        if (controller->unk54 != 0)
        {
            controller->dispatch_window_request();
        }
    }

    func_slot20(0);
    selector->func_0023B280(1);
    unkb0->set_tint(0x808080);
    unkb4->set_tint(0x288080);
    marker->func_0023B7E0(unkb4);
    return 2;
}

/**
 * @brief Confirm the first choice, or behave like func_slotb4 for the second.
 * @return Zero while the selector is still moving, otherwise one.
 */
u8 TrophySkipConfirmWindow::func_slotb0()
{
    if (selector->is_moving())
    {
        return 0;
    }

    if (selector->func_0023B3A0() == 0)
    {
        func_slot24(1);
        set_state(0xFF, 0x40);
        unka8->unk54 = 0;
        ResidentCheckedRecord* record = static_cast<ResidentCheckedRecord*>(func_101440(func_101290(resident_get_system()), 1));

        if (record != 0)
        {
            record->unk25_6 = 0;
        }

        unka8->func_003583B0();
    }
    else
    {
        CardMenuController* controller = unka8;

        if (controller != 0)
        {
            controller->unk54 = 0x79;

            if (controller->unk54 != 0)
            {
                controller->dispatch_window_request();
            }
        }
    }

    func_slot20(0);
    selector->func_0023B280(1);
    unkb0->set_tint(0x808080);
    unkb4->set_tint(0x288080);
    marker->func_0023B7E0(unkb4);
    return 1;
}

/**
 * @brief Store the window control byte.
 * @param value Control value.
 */
void FieldClass15AE70::func_slot24(u8 value)
{
    unk0c = value;
}

/** @brief Move the selector in direction two and recolour the choices. */
void TrophySkipConfirmWindow::func_slot74()
{
    if (selector->func_0023B3B0(2) != 1)
    {
        u16 selected = selector->func_0023B3A0();

        for (s32 index = 0; index < 2; index++)
        {
            LibTextWidget* text = static_cast<LibTextWidget*>(unk2c.at(index)->value);

            if (index == selected)
            {
                text->set_tint(0x288080);
                marker->func_0023B7E0(text);
            }
            else
            {
                text->set_tint(0x808080);
            }
        }
    }
}

/** @brief Move the selector in direction three and recolour the choices. */
void TrophySkipConfirmWindow::func_slot70()
{
    if (selector->func_0023B3B0(3) != 1)
    {
        u16 selected = selector->func_0023B3A0();

        for (s32 index = 0; index < 2; index++)
        {
            LibTextWidget* text = static_cast<LibTextWidget*>(unk2c.at(index)->value);

            if (index == selected)
            {
                text->set_tint(0x288080);
                marker->func_0023B7E0(text);
            }
            else
            {
                text->set_tint(0x808080);
            }
        }
    }
}

/**
 * @brief Create the panel, the question and both choices, the selector, and its marker.
 * @param associated Full resource source word.
 * @return One.
 */
s32 TrophySkipConfirmWindow::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 20.0f, 180.0f, 13);
    LibPanel* panel = new (0) LibPanel;
    unkac = new (0) LibTextWidget;
    unkb0 = new (0) LibTextWidget;
    unkb4 = new (0) LibTextWidget;
    selector = new (0) FieldClass153130;
    marker = new (0) FieldClass153170;
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 600.0f, 164.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    lib_text_init_resource_rectangle(unkac, static_cast<s32>(associated), 0x2349, 0, 16.0f, 16.0f, 568.0f, 120.0f);
    lib_text_init_resource_rectangle(unkb0, static_cast<s32>(associated), 0x7E8, 0, 188.0f, 128.0f, 0.0f, 0.0f);
    lib_text_init_resource_rectangle(unkb4, static_cast<s32>(associated), 0x7E9, 0, 328.0f, 128.0f, 0.0f, 0.0f);
    unkac->set_horizontal_align(1);
    lib_container_attach_widget(unk10, unkac);
    lib_container_attach_widget(unk10, unkb0);
    lib_container_attach_widget(unk10, unkb4);
    unk2c.append(unkb0);
    unk2c.append(unkb4);
    selector->func_0023B530(2, 1, 1, 1, 1, 188.0f, 140.0f, 140.0f, 0.0f);
    lib_container_attach_widget(unk10, selector);
    marker->func_0023B850(unkb4, 0x288080);
    lib_container_attach_widget(unk10, marker);
    unkb4->set_tint(0x288080);
    marker->func_0023B7E0(unkb4);
    return 1;
}

/** @brief Destroy the dialog. */
TrophySkipConfirmWindow::~TrophySkipConfirmWindow()
{
}

/** @brief While this is the focused window, colour each choice by its record state and move the marker. */
void TrophySlotSelectWindow::func_slot5c()
{
    if (D_001B643C->unk10->unk14->func_00261150() != this)
    {
        return;
    }

    if (func_slot28())
    {
        return;
    }

    u16 selected = selector->func_0023B3A0();

    if (linked->func_0035AFD0(0) == 2)
    {
        first_text->set_tint(0x288080);

        if (marker != 0 && selected == 0)
        {
            marker->func_0023B7E0(first_text);
            func_420D20(marker, 0x288080);
        }
    }
    else
    {
        first_text->set_tint(0x505050);

        if (marker != 0 && selected == 0)
        {
            marker->func_0023B7E0(first_text);
            func_420D20(marker, 0x505050);
        }
    }

    if (linked->func_0035AFD0(1) == 2)
    {
        second_text->set_tint(0x288080);

        if (marker != 0 && selected == 1)
        {
            marker->func_0023B7E0(second_text);
            func_420D20(marker, 0x288080);
        }
    }
    else
    {
        second_text->set_tint(0x505050);

        if (marker != 0 && selected == 1)
        {
            marker->func_0023B7E0(second_text);
            func_420D20(marker, 0x505050);
        }
    }
}

/**
 * @brief Read the window control byte.
 * @return Control value.
 */
u8 FieldClass15AE70::func_slot28()
{
    return unk0c;
}

void* FieldClass153E30::func_00261150()
{
    return unk20;
}

/** @brief Move the child selector forward. */
void TrophySlotSelectWindow::func_slot6c()
{
    selector->func_0023B3B0(1);
}

/** @brief Move the child selector backward. */
void TrophySlotSelectWindow::func_slot68()
{
    selector->func_0023B3B0(0);
}

/**
 * @brief Request the controller action, hide this window's nested display, and return status two.
 * @return Two.
 */
u8 TrophySlotSelectWindow::func_slotb4()
{
    CardMenuController* controller = unka8;

    if (controller != 0)
    {
        controller->unk54 = 0x7A;

        if (controller->unk54 != 0)
        {
            controller->dispatch_window_request();
        }
    }

    func_slot20(0);
    return 2;
}

/**
 * @brief Pick the selected record when its state is two, or request controller window 0x6C otherwise.
 * @return Zero while the selector is still moving, three when the record isn't ready, otherwise one.
 */
u8 TrophySlotSelectWindow::func_slotb0()
{
    if (selector->is_moving())
    {
        return 0;
    }

    u16 selected = selector->func_0023B3A0();
    u16 state = linked->func_0035AFD0(selected);
    g_field_runtime->message_arguments[1] = static_cast<s16>(selected + 1);

    if (state != 2)
    {
        unka8->request_window(0x6C);
        return 3;
    }

    unka8->request_window(0x73);
    linked->unk5c = -1;
    linked->func_0035ADD0(selected, 1);

    if (unka8 != 0)
    {
        CardMessageWindow* window = unka8->unk4c;
        window->unkB8 = selected;
        window->unkB9 = 1;
    }

    func_slot20(0);
    return 1;
}

/**
 * @brief Create the panel, the two choices and their selector and marker.
 * @param associated Full resource source word.
 * @return Zero when the controller has no linked object, otherwise one.
 */
s32 TrophySlotSelectWindow::func_slotf4(u32 associated)
{
    linked = reinterpret_cast<CardTask*>(unka8->func_slot60());

    if (linked == 0)
    {
        return 0;
    }

    FieldClass15AE70::func_slot10(associated, 140.0f, 212.0f, 16);
    LibPanel* panel = new (0) LibPanel;
    first_text = new (0) LibTextWidget;
    second_text = new (0) LibTextWidget;
    selector = new (0) FieldClass153130;
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 360.0f, 112.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    unk14.append(panel);
    lib_text_init_resource_rectangle(first_text, static_cast<s32>(associated), 0x513, 0, 70.0f, 24.0f, 0.0f, 0.0f);
    lib_text_init_resource_rectangle(second_text, static_cast<s32>(associated), 0x514, 0, 70.0f, 64.0f, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, first_text);
    lib_container_attach_widget(unk10, second_text);
    selector->func_0023B530(1, 2, 1, 0, 1, 70.0f, 36.0f, 0.0f, 40.0f);
    lib_container_attach_widget(unk10, selector);
    marker = new (0) FieldClass153170;
    marker->func_0023B850(first_text, 0x288080);
    lib_container_attach_widget(unk10, marker);
    return 1;
}

/**
 * @brief Return the linked memory card handler.
 * @return Handler pointer as a word.
 */
s32 CardMenuController::func_slot60()
{
    return reinterpret_cast<s32>(linked_object);
}

/** @brief Destroy the window and its Field parent. */
TrophySlotSelectWindow::~TrophySlotSelectWindow()
{
}

/**
 * @brief Request controller action 0x79 and hide the nested display.
 * @return One.
 */
u8 TrophyCorruptWindow::func_slotb0()
{
    CardMenuController* controller = unka8;

    if (controller != 0)
    {
        controller->unk54 = 0x79;

        if (controller->unk54 != 0)
        {
            controller->dispatch_window_request();
        }
    }

    func_slot20(0);
    return 1;
}

/**
 * @brief Create the window frame, its panel, and its resource text.
 * @param associated Full resource source word.
 * @return One.
 */
s32 TrophyCorruptWindow::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 78.0f, 180.0f, 13);
    LibPanel* panel = new (0) LibPanel;
    unkac = new (0) LibTextWidget;
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 486.0f, 164.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    lib_text_init_resource_rectangle(unkac, static_cast<s32>(associated), 0x2348, 0, 16.0f, 16.0f, 454.0f, 120.0f);
    lib_container_attach_widget(unk10, unkac);
    return 1;
}

/** @brief Destroy the window. */
TrophyCorruptWindow::~TrophyCorruptWindow()
{
}

/**
 * @brief Request controller action 0x79 and hide the nested display once the selector stops.
 * @return Zero while the selector is still moving, otherwise one.
 */
u8 TrophyNoDataConfirmWindow::func_slotb4()
{
    if (selector->is_moving())
    {
        return 0;
    }

    CardMenuController* controller = unka8;
    controller->unk54 = 0x79;

    if (controller->unk54 != 0)
    {
        controller->dispatch_window_request();
    }

    func_slot20(0);
    return 1;
}

/**
 * @brief Confirm the first choice, or request controller action 0x79 for the second.
 * @return Zero while the selector is still moving, otherwise one.
 */
u8 TrophyNoDataConfirmWindow::func_slotb0()
{
    if (selector->is_moving())
    {
        return 0;
    }

    if (selector->func_0023B3A0() == 0)
    {
        func_slot24(1);
        set_state(0xFF, 0x40);
        unka8->unk54 = 0;
        ResidentCheckedRecord* record = static_cast<ResidentCheckedRecord*>(func_101440(func_101290(resident_get_system()), 1));

        if (record != 0)
        {
            record->unk25_6 = 0;
        }

        unka8->func_003583B0();
    }
    else
    {
        CardMenuController* controller = unka8;
        controller->unk54 = 0x79;

        if (controller->unk54 != 0)
        {
            controller->dispatch_window_request();
        }
    }

    func_slot20(0);
    return 1;
}

/** @brief Move the selector in direction two and recolour the choices. */
void TrophyNoDataConfirmWindow::func_slot74()
{
    if (selector->func_0023B3B0(2) != 1)
    {
        u16 selected = selector->func_0023B3A0();

        for (s32 index = 0; index < 2; index++)
        {
            LibTextWidget* text = static_cast<LibTextWidget*>(unk2c.at(index)->value);

            if (index == selected)
            {
                text->set_tint(0x288080);
                marker->func_0023B7E0(text);
            }
            else
            {
                text->set_tint(0x808080);
            }
        }
    }
}

/** @brief Move the selector in direction three and recolour the choices. */
void TrophyNoDataConfirmWindow::func_slot70()
{
    if (selector->func_0023B3B0(3) != 1)
    {
        u16 selected = selector->func_0023B3A0();

        for (s32 index = 0; index < 2; index++)
        {
            LibTextWidget* text = static_cast<LibTextWidget*>(unk2c.at(index)->value);

            if (index == selected)
            {
                text->set_tint(0x288080);
                marker->func_0023B7E0(text);
            }
            else
            {
                text->set_tint(0x808080);
            }
        }
    }
}

/**
 * @brief Create the panel, the question and both choices, the selector, and its marker.
 * @param associated Full resource source word.
 * @return One.
 */
s32 TrophyNoDataConfirmWindow::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 52.0f, 158.0f, 13);
    LibPanel* panel = new (0) LibPanel;
    unkac = new (0) LibTextWidget;
    unkb0 = new (0) LibTextWidget;
    unkb4 = new (0) LibTextWidget;
    selector = new (0) FieldClass153130;
    marker = new (0) FieldClass153170;
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 520.0f, 232.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    lib_text_init_resource_rectangle(unkac, static_cast<s32>(associated), 0x2345, 0, 16.0f, 40.0f, 488.0f, 120.0f);
    lib_text_init_resource_rectangle(unkb0, static_cast<s32>(associated), 0x7E8, 0, 168.0f, 196.0f, 0.0f, 0.0f);
    lib_text_init_resource_rectangle(unkb4, static_cast<s32>(associated), 0x7E9, 0, 288.0f, 196.0f, 0.0f, 0.0f);
    unkac->set_horizontal_align(1);
    unkac->set_vertical_align(1);
    lib_container_attach_widget(unk10, unkac);
    lib_container_attach_widget(unk10, unkb0);
    lib_container_attach_widget(unk10, unkb4);
    unk2c.append(unkb0);
    unk2c.append(unkb4);
    selector->func_0023B530(2, 1, 1, 1, 1, 168.0f, 208.0f, 120.0f, 0.0f);
    lib_container_attach_widget(unk10, selector);
    marker->func_0023B850(unkb4, 0x288080);
    lib_container_attach_widget(unk10, marker);
    unkb4->set_tint(0x288080);
    marker->func_0023B7E0(unkb4);
    marker->unk5c = 1;
    return 1;
}

/** @brief Destroy the dialog. */
TrophyNoDataConfirmWindow::~TrophyNoDataConfirmWindow()
{
}

/**
 * @brief Request controller action 0x79 and hide the nested display.
 * @return One.
 */
u8 TrophyLoadFailedWindow::func_slotb0()
{
    CardMenuController* controller = unka8;

    if (controller != 0)
    {
        controller->unk54 = 0x79;

        if (controller->unk54 != 0)
        {
            controller->dispatch_window_request();
        }
    }

    func_slot20(0);
    return 1;
}

/**
 * @brief Create the window frame, its panel, and its resource text.
 * @param associated Full resource source word.
 * @return One.
 */
s32 TrophyLoadFailedWindow::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 98.0f, 208.0f, 13);
    LibPanel* panel = new (0) LibPanel;
    unkac = new (0) LibTextWidget;
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 444.0f, 112.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    lib_text_init_resource_rectangle(unkac, static_cast<s32>(associated), 0x2344, 0, 16.0f, 16.0f, 412.0f, 120.0f);
    lib_container_attach_widget(unk10, unkac);
    return 1;
}

/** @brief Destroy the window. */
TrophyLoadFailedWindow::~TrophyLoadFailedWindow()
{
}

/**
 * @brief Set bit 6 of the checked record's byte 0x25, lock the window, and run the controller's closing step.
 * @return One.
 */
u8 TrophyLoadedWindow::func_slotb0()
{
    func_slot24(1);
    set_state(0xFF, 0x40);
    unka8->unk54 = 0;
    ResidentCheckedRecord* record = static_cast<ResidentCheckedRecord*>(func_101440(func_101290(resident_get_system()), 1));

    if (record != 0)
    {
        record->unk25_6 = 1;
    }

    unka8->func_003583B0();
    func_slot20(0);
    return 1;
}

/**
 * @brief Create the window frame, its panel, and its resource text.
 * @param associated Full resource source word.
 * @return One.
 */
s32 TrophyLoadedWindow::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 98.0f, 208.0f, 13);
    LibPanel* panel = new (0) LibPanel;
    unkac = new (0) LibTextWidget;
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 444.0f, 112.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    lib_text_init_resource_rectangle(unkac, static_cast<s32>(associated), 0x2343, 0, 16.0f, 16.0f, 412.0f, 120.0f);
    lib_container_attach_widget(unk10, unkac);
    return 1;
}

/** @brief Destroy the window. */
TrophyLoadedWindow::~TrophyLoadedWindow()
{
}

/** @brief Once this is the focused window and the linked object has finished, hide the window and request the follow-up window its result codes select. */
void TrophyCheckingWindow::func_slot5c()
{
    if (D_001B643C->unk10->unk14->func_00261150() == this)
    {
        CardTask* result = unkac;

        if (result->unk34 != 0)
        {
            s32 first = result->unk30;
            s32 second = result->unk4c;
            func_slot20(0);

            if (first < 0)
            {
                if (first == -2)
                {
                    unka8->request_window(0x7B);
                    return;
                }
                else
                {
                    unka8->request_window(0x75);
                    return;
                }
            }
            else if (first == 0 && second == 0)
            {
                unka8->request_window(0x74);
                return;
            }
            else if (second == 0x81)
            {
                unka8->request_window(0x7B);
                return;
            }
            else if (second == 0x83)
            {
                unka8->request_window(0x78);
                return;
            }
            else if (second == 0x86)
            {
                unka8->request_window(0x75);
                return;
            }
        }
    }
}

/**
 * @brief Take the controller's linked object, then create the window frame, its panel, and its resource text.
 * @param associated Full resource source word.
 * @return Zero when the controller has no linked object, otherwise one.
 */
s32 TrophyCheckingWindow::func_slotf4(u32 associated)
{
    unkac = reinterpret_cast<CardTask*>(unka8->func_slot60());

    if (unkac == 0)
    {
        return 0;
    }

    FieldClass15AE70::func_slot10(associated, 100.0f, 202.0f, 13);
    LibPanel* panel = new (0) LibPanel;
    unkb0 = new (0) LibTextWidget;
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 440.0f, 164.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    lib_text_init_resource_rectangle(unkb0, static_cast<s32>(associated), 0x2342, 0, 16.0f, 16.0f, 408.0f, 120.0f);
    lib_container_attach_widget(unk10, unkb0);
    return 1;
}

/** @brief Destroy the window. */
TrophyCheckingWindow::~TrophyCheckingWindow()
{
}

/**
 * @brief Request controller action 0x79 and hide the nested display.
 * @return One.
 */
u8 TrophyNoCardWindow::func_slotb4()
{
    CardMenuController* controller = unka8;

    if (controller != 0)
    {
        controller->unk54 = 0x79;

        if (controller->unk54 != 0)
        {
            controller->dispatch_window_request();
        }
    }

    func_slot20(0);
    return 1;
}

/**
 * @brief Request controller action 0x79 and hide the nested display.
 * @return One.
 */
u8 TrophyNoCardWindow::func_slotb0()
{
    CardMenuController* controller = unka8;

    if (controller != 0)
    {
        controller->unk54 = 0x79;

        if (controller->unk54 != 0)
        {
            controller->dispatch_window_request();
        }
    }

    func_slot20(0);
    return 1;
}

/**
 * @brief Create the window frame, its panel, and its resource text.
 * @param associated Full resource source word.
 * @return Zero when either widget couldn't be allocated, otherwise one.
 */
s32 TrophyNoCardWindow::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 52.0f, 208.0f, 14);
    LibPanel* panel = new (0) LibPanel;
    unkac = new (0) LibTextWidget;

    if (panel == 0 || unkac == 0)
    {
        return 0;
    }

    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 540.0f, 120.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    lib_text_init_resource_rectangle(unkac, static_cast<s32>(associated), 0x519, 0, 24.0f, 24.0f, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, unkac);
    return 1;
}

/** @brief Destroy the window. */
TrophyNoCardWindow::~TrophyNoCardWindow()
{
}

void FieldClass15AE70::func_slot60(s32 text_key)
{
}

void* FieldClass153E30::func_00263C90()
{
    return unk24;
}

void FieldClass153E30::func_00263C70(void* value)
{
    unk20 = value;
}
