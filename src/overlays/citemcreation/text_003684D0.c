#include "include_asm.h"
#include "main/resident_data.h"
#include "overlays/citemcreation/text_003684D0.h"
#include "overlays/citemcreation/text_00358440.h"
#include "overlays/citemcreation/text_003483C0.h"
#include "overlays/1067-00/text_0023B1D0.h"

enum
{
    ITEM_CREATION_FLAG_0 = 0x1,
    ITEM_CREATION_FLAG_1 = 0x2,
    ITEM_CREATION_FLAG_2 = 0x4,
    ITEM_CREATION_FLAG_3 = 0x8,
    ITEM_CREATION_FLAG_4 = 0x10,
    ITEM_CREATION_FLAG_5 = 0x20,
    ITEM_CREATION_FLAG_6 = 0x40,
    ITEM_CREATION_FLAG_7 = 0x80
};

typedef struct ItemCreationRuntimeRecord
{
    u16 unk00;
    u8 unk02[0x32];
} ItemCreationRuntimeRecord;

typedef struct ItemCreationRuntimeRecordState
{
    u8 unk00[0x10F80];
    ItemCreationRuntimeRecord unk10f80[5];
} ItemCreationRuntimeRecordState;

typedef struct ItemCreationRuntimeRoot ItemCreationRuntimeRoot;
typedef struct ItemCreationRuntimeDirectory ItemCreationRuntimeDirectory;
typedef struct ItemCreationRuntimeFlags
{
    u8 unk00[0x7A];
    u8 unk7a;
    u8 unk7b;
} ItemCreationRuntimeFlags;

typedef struct ItemCreationListDisplay
{
    u8 unk00[0x2C];
    ItemCreationList unk2c;
    u8 unk30[0x78];
    ItemCreationSelectedDisplayState* unka8;
} ItemCreationListDisplay;

typedef struct ItemCreationThreeSlotDisplay
{
    u8 unk00[0x120];
    ItemCreationSelectedDisplayState* unk120;
    u8 unk124;
    u8 unk125;
    u8 unk126[2];
    ItemCreationColorDisplay* unk128[3];
    ItemCreationColorDisplay* unk134[3];
} ItemCreationThreeSlotDisplay;

struct ItemCreationOptionDisplay
{
    u8 unk00[0xC8];
    FieldObject23CEA0* unkc8;
};

// Resident interfaces are scoped here because the shared declarations belong to another overlay.
ItemCreationRuntimeRoot* func_10D8E0(void);
ItemCreationRuntimeDirectory* func_101290(ItemCreationRuntimeRoot* root);
ItemCreationRuntimeFlags* func_101440(ItemCreationRuntimeDirectory* directory, s32 key);

extern ItemCreationRuntimeRecordState* D_001B64F8;
extern u8 D_50CD30[];
extern void func_4CE4C0(void* destination, const float* source);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_003684D0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_00368540);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_003685B0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_00368610);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_003687C0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_00368AD0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_00368B30);

void func_00368BD0(ItemCreationScrollState* object)
{
    ItemCreationScrollPosition* position = object->unkac;
    float x = position->unk18;
    float y = position->unk1c;
    float z = position->unk20;
    float w = position->unk24;
    float start;
    if (object->unkba == 0)
    {
        position->unk18 = object->unkc0;
        position->unk1c = y;
        position->unk20 = z;
        position->unk24 = w;
        position->unk3c = 1;
        object->unkb8++;
        if (!((float)object->unkb8 <= 120.0f))
        {
            object->unkb8 = 0;
            object->unkba = 1;
        }
        return;
    }
    start = object->unkc4;
    x -= 108.0f * D_001B6690;
    if (x < start - (float)object->unkb0)
    {
        x = start + object->unkc8 + 2.0f;
    }
    position->unk18 = x;
    position->unk1c = y;
    position->unk20 = z;
    position->unk24 = w;
    position->unk3c = 1;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_00368CC0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_00369060);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_003690C0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_003693A0);

void func_00369400(ItemCreationSelection* object)
{
    object->unk00[0][0] = 136.0f;
    object->unk00[0][1] = 164.0f;
    object->unk00[1][0] = 136.0f;
    object->unk00[1][1] = 180.0f;
    object->unk00[2][0] = 60.0f;
    object->unk00[2][1] = 168.0f;
    object->unk00[3][0] = 348.0f;
    object->unk00[3][1] = 44.0f;
    object->unk00[4][0] = 340.0f;
    object->unk00[4][1] = 92.0f;
    object->unk00[5][0] = 212.0f;
    object->unk00[5][1] = 196.0f;
    object->unk00[6][0] = 160.0f;
    object->unk00[6][1] = 96.0f;
    object->unk00[7][0] = 96.0f;
    object->unk00[7][1] = 80.0f;
    object->unk00[8][0] = 108.0f;
    object->unk00[8][1] = 56.0f;
    object->unk00[9][0] = 60.0f;
    object->unk00[9][1] = 16.0f;
    object->unk00[10][0] = 380.0f;
    object->unk00[10][1] = 20.0f;
    object->unk00[11][0] = 16.0f;
    object->unk00[11][1] = 198.0f;
    object->unk6d[0] = 1;
    object->unk6d[1] = 2;
    object->unk6d[2] = 0;
    object->unk6d[3] = 5;
    object->unk6d[4] = 4;
    object->unk6d[5] = 3;
    object->unk6d[6] = 10;
    object->unk6d[7] = 9;
    object->unk6d[8] = 8;
    object->unk6d[9] = 7;
    object->unk6d[10] = 6;
    object->unk6d[11] = 11;
}

void func_00369510(ItemCreationSelection* object)
{
    s32 enabled;
    ItemCreationRuntimeFlags* flags = func_101440(func_101290(func_10D8E0()), 4);
    if (flags != 0)
    {
        enabled = (flags->unk7a & ITEM_CREATION_FLAG_4) != 0;
        if (enabled)
        {
            object->unk60[0] = 1;
        }
        enabled = (flags->unk7a & ITEM_CREATION_FLAG_5) != 0;
        if (enabled)
        {
            object->unk60[1] = 1;
        }
        enabled = (flags->unk7a & ITEM_CREATION_FLAG_6) != 0;
        if (enabled)
        {
            object->unk60[2] = 1;
        }
        enabled = (flags->unk7a & ITEM_CREATION_FLAG_7) != 0;
        if (enabled)
        {
            object->unk60[3] = 1;
        }
        enabled = (flags->unk7b & ITEM_CREATION_FLAG_0) != 0;
        if (enabled)
        {
            object->unk60[4] = 1;
        }
        enabled = (flags->unk7b & ITEM_CREATION_FLAG_1) != 0;
        if (enabled)
        {
            object->unk60[5] = 1;
        }
        enabled = (flags->unk7b & ITEM_CREATION_FLAG_2) != 0;
        if (enabled)
        {
            object->unk60[6] = 1;
        }
        enabled = (flags->unk7b & ITEM_CREATION_FLAG_3) != 0;
        if (enabled)
        {
            object->unk60[7] = 1;
        }
        enabled = (flags->unk7b & ITEM_CREATION_FLAG_4) != 0;
        if (enabled)
        {
            object->unk60[8] = 1;
        }
        enabled = (flags->unk7b & ITEM_CREATION_FLAG_5) != 0;
        if (enabled)
        {
            object->unk60[9] = 1;
        }
        enabled = (flags->unk7b & ITEM_CREATION_FLAG_6) != 0;
        if (enabled)
        {
            object->unk60[10] = 1;
        }
        enabled = (flags->unk7b & ITEM_CREATION_FLAG_7) != 0;
        if (enabled)
        {
            object->unk60[11] = 1;
        }
        if (object->unk79 == 1 || object->unk79 == 2)
        {
            object->unk60[5] = 0;
            object->unk60[6] = 0;
            object->unk60[7] = 0;
            object->unk60[8] = 0;
            object->unk60[9] = 0;
            object->unk60[10] = 0;
            object->unk60[11] = 0;
        }
    }
}

u8 func_003696B0(ItemCreationSelection* object, u16 direction)
{
    s32 selected = object->unk6d[object->unk6c - 1];
    s32 slot;
    s32 index;

    do
    {
        switch (direction)
        {
        case 1:
        case 4:
            selected--;
            break;
        case 3:
        case 2:
            selected++;
            break;
        }
        if (selected < 0)
        {
            selected = 11;
        }
        if (selected >= 12)
        {
            selected = 0;
        }
        slot = -1;
        for (index = 0; index < 12; index++)
        {
            if (selected == object->unk6d[index])
            {
                slot = index + 1;
                break;
            }
        }
    } while (!object->unk60[slot - 1]);
    object->unk6c = slot;
    return object->unk6c;
}

s32 func_00369780(ItemCreationSelection* object)
{
    func_00369510(object);
    return 1;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_003697A0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_003697F0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_003698E0);

void func_00369B80(ItemCreationSelectedDisplayState* object, s32 value)
{
    ItemCreationSelection* selection;
    ItemCreationFlagResetOwner* owner;
    s32 selected;
    switch (object->unk129)
    {
    case 0:
        if (value == -1)
        {
            object->unk129 = 0;
            object->unk12a = 0;
            object->unk12b = 0;
            object->unk12c = 0;
            object->unk12d = 0;
        }
        else
        {
            object->unk12a = value;
            object->unk129 = 1;
        }
        break;
    case 1:
        if (value == -1)
        {
            object->unk12b = 0;
            object->unk129 = 0;
        }
        else
        {
            object->unk12b = value;
            object->unk129 = 2;
        }
        break;
    case 2:
        if (value == -1)
        {
            object->unk12c = 0;
            object->unk129 = 1;
        }
        else
        {
            object->unk12c = value;
            object->unk129 = 3;
        }
        break;
    case 3:
        if (value == -1)
        {
            object->unk12d = 0;
            object->unk129 = 2;
            break;
        }
        object->unk12d = value;
        if (object->unk12b != 0)
        {
            u8 code = object->unk12c == 0 ? 0 : object->unk12c + 1;
            if (object->unk40 != 0)
            {
                object->unk40->unk188[object->unk12b] = code;
            }
        }
        if (object->unk12d != 0)
        {
            u8 code = object->unk12a == 0 ? 0 : object->unk12a + 1;
            if (object->unk40 != 0)
            {
                object->unk40->unk188[object->unk12d] = code;
            }
        }
        selected = object->unk12a;
        if (object->unkf8 != 0)
        {
            func_0036A780(object, selected, 1);
            func_0034D340(object->unkf8);
            if (object->unkf8->unkc8 != 0)
            {
                func_0023CEA0(object->unkf8->unkc8, 0);
            }
        }
        object->unk129 = 0;
        object->unk12a = 0;
        object->unk12b = 0;
        object->unk12c = 0;
        object->unk12d = 0;
        owner = object->unkf4;
        if (owner != 0)
        {
            const float* position;
            ItemCreationTransferDisplay* display;
            float x;
            float y;
            owner->unk160->unk6c = selected;
            selection = owner->unk160;
            if ((u8)selected <= 0)
            {
                position = 0;
            }
            else if ((u8)selected > 12)
            {
                position = 0;
            }
            else
            {
                position = selection->unk00[(u8)selected - 1];
            }
            display = owner->unk15c;
            x = position[0];
            y = position[1];
            display->unk50 = x;
            display->unk54 = y;
            display->unk75 = 1;
            display->unk3c = 1;
            owner = object->unkf4;
            switch (owner->unk164->unk129)
            {
            case 0:
                owner->unk16c->unk3f = 0;
                owner->unk15c->unk3f = 1;
                break;
            case 1:
                break;
            case 2:
                owner->unk15c->unk3f = 1;
                break;
            case 3:
                break;
            }
            func_0034DA30(object->unkf4);
            func_0034DB00(object->unkf4, selected);
        }
        if (object->unkfc != 0)
        {
            object->unk77[0] = 0;
            object->unk77[1] = 0;
            object->unk77[2] = 0;
            object->unk77[3] = 0;
            object->unk77[4] = 0;
            object->unk77[5] = 0;
            func_0034D340(object->unkfc);
            if (object->unkfc->unkc8 != 0)
            {
                func_0023CEA0(object->unkfc->unkc8, 0);
            }
        }
        break;
    }
}

void func_00369EB0(ItemCreationRuntimeRecordSelection* object)
{
    object->unk7e[0] = D_001B64F8->unk10f80[0].unk00;
    object->unk7e[1] = D_001B64F8->unk10f80[1].unk00;
    object->unk7e[2] = D_001B64F8->unk10f80[2].unk00;
    object->unk7e[3] = D_001B64F8->unk10f80[3].unk00;
    object->unk7e[4] = D_001B64F8->unk10f80[4].unk00;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_00369F20);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_00369FA0);

void func_0036A050(ItemCreationSelectedDisplayState* object, void* selected, s16 index)
{
    switch (object->unk128)
    {
    case 0:
        if (index == -1)
        {
            object->unk120 = 0;
            object->unk11c = 0;
            object->unk126 = -1;
            object->unk124 = -1;
            object->unk128 = 0;
        }
        else
        {
            object->unk11c = selected;
            object->unk120 = 0;
            object->unk124 = index;
            object->unk128 = 1;
        }
        break;
    case 1:
        if (index == -1)
        {
            object->unk120 = 0;
            object->unk11c = 0;
            object->unk126 = -1;
            object->unk124 = -1;
            object->unk128 = 0;
        }
        else
        {
            object->unk120 = selected;
            object->unk126 = index;
            object->unk128 = 2;
        }
        break;
    }
    if (object->unk11c != 0 && object->unk120 != 0 && object->unk128 == 2)
    {
        void* first = object->unk11c;
        void* second = object->unk120;
        u8 first_value = 0;
        u8 second_value = 0;
        ItemCreationFourteenSlotView* fourteen;
        ItemCreationNineSlotView* nine;

        if (first == object->unkb8)
        {
            first_value = object->unk5a[(u16)object->unk124];
        }
        else if (first == object->unkbc)
        {
            first_value = object->unk68[(u16)object->unk124];
        }
        if (second == object->unkb8)
        {
            second_value = object->unk5a[(u16)object->unk126];
        }
        else if (second == object->unkbc)
        {
            second_value = object->unk68[(u16)object->unk126];
        }
        if (first == object->unkb8)
        {
            object->unk5a[(u16)object->unk124] = second_value;
        }
        else if (first == object->unkbc)
        {
            object->unk68[(u16)object->unk124] = second_value;
        }
        if (object->unk120 == object->unkb8)
        {
            s32 marker;
            object->unk5a[(u16)object->unk126] = first_value;
            fourteen = object->unkb8;
            if (fourteen->unkb4 != 0)
            {
                s32 active = fourteen->unkb4->unk114;
                for (marker = 0; marker < 14; marker++)
                {
                    if (active == marker)
                    {
                        fourteen->unkb8[marker]->unk3f = 1;
                    }
                    else
                    {
                        fourteen->unkb8[marker]->unk3f = 0;
                    }
                }
            }
        }
        else if (object->unk120 == object->unkbc)
        {
            object->unk68[(u16)object->unk126] = first_value;
            func_00361220(object->unkbc);
        }
        func_00364D20(object->unkb8);
        func_003614B0(object->unkbc);
        first = object->unk11c;
        fourteen = object->unkb8;
        if (fourteen == first)
        {
            FieldObject23CEA0* restore;
            FieldObject23CEA0* display = fourteen->unkb4;
            if (display == fourteen->unkb0)
            {
                s16 selected_index = display->unk114;
                float x;
                float y;
                restore = fourteen->unkac;
                restore->unkE0 = 128.0f;
                restore->unkAE = 1;
                x = display->unkC0;
                y = display->unkC4;
                restore = fourteen->unkac;
                restore->unkC0 = x;
                restore->unkC4 = y;
                restore->unkE5 = 1;
                restore->unkAE = 1;
                restore = fourteen->unkac;
                restore->index = selected_index;
                func_0023CB30(restore);
                func_0023C7B0(fourteen->unkac);
                func_0023CEA0(fourteen->unkb0, 0);
                fourteen->unkb4 = fourteen->unkac;
            }
            func_00364090(object->unkb8, 0);
            if (object->unkb8 == object->unk120)
            {
                func_00364090(object->unkb8, 1);
            }
            else if (object->unkbc == object->unk120)
            {
                func_00360E60(object->unkbc, 1);
                func_003698E0(object, (u8)(object->unk126 / 3));
            }
        }
        else
        {
            nine = object->unkbc;
            if (nine == first)
            {
                FieldObject23CEA0* restore;
                FieldObject23CEA0* display = nine->unkb4;
                if (display == nine->unkb0)
                {
                    s16 selected_index = display->unk114;
                    float x;
                    float y;
                        restore = nine->unkac;
                    restore->unkE0 = 128.0f;
                    restore->unkAE = 1;
                    x = display->unkC0;
                    y = display->unkC4;
                    restore = nine->unkac;
                    restore->unkC0 = x;
                    restore->unkC4 = y;
                    restore->unkE5 = 1;
                    restore->unkAE = 1;
                    restore = nine->unkac;
                    restore->index = selected_index;
                    func_0023CB30(restore);
                    func_0023C7B0(nine->unkac);
                    func_0023CEA0(nine->unkb0, 0);
                    nine->unkb4 = nine->unkac;
                }
                func_00360E60(object->unkbc, 0);
                if (object->unkb8 == object->unk120)
                {
                    func_00364090(object->unkb8, 1);
                    func_003698E0(object, (u8)(object->unk124 / 3));
                }
                else if (object->unkbc == object->unk120)
                {
                    func_00360E60(object->unkbc, 1);
                    func_003698E0(object, (u8)(object->unk124 / 3));
                    func_003698E0(object, (u8)(object->unk126 / 3));
                }
            }
        }
        func_0036A500(object, object->unk120, object->unk126);
        object->unk120 = 0;
        object->unk11c = 0;
        object->unk126 = -1;
        object->unk124 = -1;
        object->unk128 = 0;
    }
}

void func_0036A500(ItemCreationSelectedDisplayState* object, void* selected, s16 index)
{
    if (selected != 0 && object->unkb8 != 0 && object->unkbc != 0 && object->unkc0 != 0)
    {
        u8 value = 0;
        ItemCreationDetailDisplay* display;
        object->unk118 = selected;
        if (object->unk118 == object->unkb8)
        {
            value = object->unk5a[(u16)index];
        }
        else if (object->unk118 == object->unkbc)
        {
            value = object->unk68[(u16)index];
        }
        display = object->unkc0;
        display->unk101 = value;
        if (display->unka8 != 0)
        {
            display->unk102 = 0;
            display->unk102 = func_00369FA0(display->unka8, display->unk101);
        }
        func_00358850(display);
        object->unk118 = 0;
    }
}

void func_0036A5D0(ItemCreationSelectedDisplayState* object, u8 mode)
{
    switch (mode)
    {
    case 1:
        if (object->unka8 != 0)
        {
            ItemCreationListDisplay* display = object->unka8;
            if (display->unka8 != 0)
            {
                s32 index;
                for (index = 0; index < 8; index++)
                {
                    ItemCreationListNode* node = func_0036F230(&display->unk2c, index);
                    ItemCreationColorDisplay* view = node->unk00;
                    if (view != 0)
                    {
                        u8 slot = index + 1;
                        if (display->unka8->unk4e[slot - 1] != 0)
                        {
                            view->unk94 = 0x808080;
                            view->unk3c = 1;
                        }
                        else
                        {
                            view->unk94 = 0x505050;
                            view->unk3c = 1;
                        }
                    }
                }
            }
        }
        if (object->unkb0 != 0)
        {
            ItemCreationThreeSlotDisplay* display = object->unkb0;
            s32 index;
            display->unk125 = display->unk120->unk57;
            for (index = 0; index < 3; index++)
            {
                if (index < display->unk125)
                {
                    ItemCreationColorDisplay* view = display->unk128[index];
                    view->unk94 = 0x1E8CFF;
                    view->unk3c = 1;
                    view = display->unk134[index];
                    view->unk94 = 0x1E8CFF;
                    view->unk3c = 1;
                }
                else
                {
                    ItemCreationColorDisplay* view = display->unk128[index];
                    view->unk94 = 0x505050;
                    view->unk3c = 1;
                    view = display->unk134[index];
                    view->unk94 = 0x505050;
                    view->unk3c = 1;
                }
            }
        }
        break;
    case 6:
        if (object->unkf8 != 0)
        {
            func_0034D340(object->unkf8);
        }
        break;
    case 7:
        if (object->unkfc != 0)
        {
            func_0034D340(object->unkfc);
        }
        break;
    }
}

void func_0036A780(ItemCreationOptionState* object, u16 option, u8 list)
{
    s32 clear_index;
    u16 count;
    s32 index;
    u8 selected;

    if (object->unk40 != 0 && (option == 0 ? 0 : option + 1) > 1 && (option == 0 ? 0 : option + 1) < 13)
    {
        clear_index = 0;
        do
        {
            switch (list)
            {
            case 1:
                object->unk71[clear_index] = 0;
                break;
            case 2:
                object->unk77[clear_index] = 0;
                break;
            }
            clear_index++;
        } while (clear_index < 6);
        selected = 0;
        switch (list)
        {
        case 1:
            object->unk58 = option;
            selected = object->unk58;
            break;
        case 2:
            object->unk59 = option;
            selected = object->unk59;
            break;
        }
        count = 0;
        index = 32;
        do
        {
            s32 code = object->unk40->unk188[index];
            if (code > 1 && code == (selected == 0 ? 0 : selected + 1))
            {
                switch (list)
                {
                case 1:
                    object->unk71[count++] = index;
                    break;
                case 2:
                    object->unk77[count++] = index;
                    break;
                }
            }
            index++;
        } while (index <= 59);
    }
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036A8F0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036AAA0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036AE20);

u8 func_0036AFE0(ItemCreationSelectedDisplayState* object)
{
    u8 code;
    switch (D_001B6430->context->unk08->unkb8)
    {
    case 31:
        code = 1;
        break;
    case 32:
        code = 2;
        break;
    case 94:
        code = 3;
        break;
    case 113:
        code = 4;
        break;
    case 142:
        code = 5;
        break;
    case 499:
        code = 6;
        break;
    case 575:
        code = 7;
        break;
    case 602:
        code = 8;
        break;
    case 652:
        code = 9;
        break;
    case 664:
        code = 10;
        break;
    case 805:
        code = 11;
        break;
    case 1135:
        code = 12;
        break;
    default:
        code = 0;
        break;
    }
    return code;
}

u16 func_0036B0E0(void* object)
{
    switch (D_001B6430->context->unk08->unkb8)
    {
    case 31:
        return 0x3521;
    case 32:
        return 0x3522;
    case 94:
        return 0x3523;
    case 113:
        return 0x3524;
    case 142:
        return 0x3525;
    case 499:
        return 0x3526;
    case 575:
        return 0x3527;
    case 602:
        return 0x3528;
    case 652:
        return 0x3529;
    case 664:
        return 0x352A;
    case 805:
        return 0x352B;
    case 1135:
        return 0x352C;
    default:
        return 0x3520;
    }
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036B1E0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036B360);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036B6E0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036BA10);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036BC90);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036BF30);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036C080);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036C1C0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036C340);

s32 func_0036CD60(void* object)
{
    return -1;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036CD70);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036CE00);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036DDC0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036DEA0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036DED0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036E0D0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036E170);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036E490);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036E4E0);

s32 func_0036E540(void* object)
{
    return 3;
}

void func_0036E550(void* object)
{
}

void func_0036E560(void* object)
{
}

void func_0036E570(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x20) = *value;
}

void func_0036E590(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x20) = *value;
}

void func_0036E5B0(u8* object, float x, float y, float z)
{
    object[0x50] = 1;
    *(float*)(object + 0x20) = x;
    *(float*)(object + 0x24) = y;
    *(float*)(object + 0x28) = z;
    *(float*)(object + 0x2C) = 1.0f;
}

void func_0036E5D0(u8* object, float x, float y, float z, float w)
{
    object[0x50] = 1;
    *(float*)(object + 0x30) = x;
    *(float*)(object + 0x34) = y;
    *(float*)(object + 0x38) = z;
    *(float*)(object + 0x3C) = w;
}

void func_0036E5F0(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x30) = *value;
}

void func_0036E610(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x30) = *value;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036E630);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036E660);

void func_0036E690(u8* object, float x, float y, float z)
{
    float value[4];
    object[0x50] = 1;
    value[0] = x;
    value[1] = y;
    value[2] = z;
    value[3] = 1.0f;
    func_4CE4C0(object + 0x30, value);
}

void func_0036E6D0(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x40) = *value;
}

void func_0036E6F0(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x40) = *value;
}

void func_0036E710(u8* object, float x, float y, float z)
{
    object[0x50] = 1;
    *(float*)(object + 0x40) = x;
    *(float*)(object + 0x44) = y;
    *(float*)(object + 0x48) = z;
}

s32 func_0036E730(void* object)
{
    return 0;
}

s32 func_0036E740(void* object, float value)
{
    return value < 0.0f;
}

u8* func_0036E760(void)
{
    return D_50CD30;
}

s32 func_0036E770(void* object)
{
    return 0;
}

void func_0036E780(void* object)
{
}

void func_0036E790(void* object)
{
}

void func_0036E7A0(void* object)
{
}

float func_0036E7B0(void* object)
{
    return 0.0f;
}

void func_0036E7C0(void* object)
{
}

void func_0036E7D0(u8* object)
{
    object[0x60] = object[0xA8];
}

void func_0036E7E0(void* object)
{
}

float func_0036E7F0(void* object)
{
    return 0.0f;
}

void func_0036E800(void* object)
{
}

void func_0036E810(void* object)
{
}

void func_0036E820(void* object)
{
}

void func_0036E830(void* object)
{
}

s32 func_0036E840(void* object)
{
    return 0;
}

s32 func_0036E850(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036E860);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036E900);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036E960);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036E9C0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036EA20);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036EA80);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036EAE0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036EB60);

u8 func_0036EBC0(void* object)
{
    return *(u8*)((u8*)object + 0x38);
}

s32 func_0036EBD0(void* object)
{
    return 4;
}

void func_0036EBE0(void* object, u32 value)
{
    *(u32*)((u8*)object + 0x24) = value;
}

void func_0036EBF0(void* object, u8 value)
{
    *(u8*)((u8*)object + 0x28) = value;
}

s8 func_0036EC00(void* object)
{
    return *(s8*)((u8*)object + 0x28);
}

s32 func_0036EC10(void* object)
{
    return 0;
}

s32 func_0036EC20(void* object)
{
    return 0;
}

void func_0036EC30(void* object)
{
}

s32 func_0036EC40(void* object)
{
    return 0;
}

void func_0036EC50(void* object)
{
}

void func_0036EC60(void* object)
{
}

void func_0036EC70(void* object)
{
}

s32 func_0036EC80(void* object)
{
    return 0;
}

s32 func_0036EC90(void* object)
{
    return 0;
}

s32 func_0036ECA0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036ECB0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036ED30);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036EDB0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036EE40);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036EEF0);

void* func_0036EF70(u8* object, s32 index)
{
    u8* node = *(u8**)object;
    s32 current = 0;
    node = *(u8**)(node + 4);
    for (current = 0; current < index; current++)
    {
        if (node == 0)
        {
            return 0;
        }
        node = *(u8**)(node + 4);
    }
    return node;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036EFB0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036F040);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036F0D0);

void* func_0036F160(u8* object, s32 index)
{
    u8* node = *(u8**)object;
    s32 current = 0;
    node = *(u8**)(node + 4);
    for (current = 0; current < index; current++)
    {
        if (node == 0)
        {
            return 0;
        }
        node = *(u8**)(node + 4);
    }
    return node;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036F1A0);

ItemCreationListNode* func_0036F230(ItemCreationList* object, s32 index)
{
    ItemCreationListNode* node = object->unk00;
    s32 current = 0;
    node = node->unk04;
    for (current = 0; current < index; current++)
    {
        if (node == 0)
        {
            return 0;
        }
        node = node->unk04;
    }
    return node;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036F270);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036F300);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036F310);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036F320);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036F330);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036F340);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036F350);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036F360);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036F370);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036F380);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036F390);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036F3A0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036F3B0);
