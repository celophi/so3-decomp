#include "include_asm.h"
#include "main/resident_data.h"
#include "main/resident_0010A0E0.h"
#include "overlays/citemcreation/text_003684D0.h"
#include "overlays/citemcreation/text_00358440.h"
#include "overlays/citemcreation/text_003483C0.h"
#include "overlays/1067-00/text_0023B1D0.h"
#include "overlays/1067-00/text_002F9C90.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/text_004095C0.h"

enum
{
    ITEM_CREATION_FLAG_0 = 0x1,
    ITEM_CREATION_FLAG_1 = 0x2,
    ITEM_CREATION_FLAG_2 = 0x4,
    ITEM_CREATION_FLAG_3 = 0x8,
    ITEM_CREATION_FLAG_4 = 0x10,
    ITEM_CREATION_FLAG_5 = 0x20,
    ITEM_CREATION_FLAG_6 = 0x40,
    ITEM_CREATION_FLAG_7 = 0x80,
    ITEM_CREATION_FLAG_8 = 0x100
};

struct ItemCreationAssignedRecord
{
    u8 unk00[0x30];
    u16 unk30;
    u8 unk32;
};

struct ItemCreationTransformState
{
    u8 unk00[0x30];
    float unk30[4];
    u8 unk40[0x10];
    u8 unk50;
};

/** One sixteen-byte option group stored in a runtime record. */
typedef struct ItemCreationRuntimeOptions
{
    u8 options[3];
    u8 marker;
    u8 unk04[0xC];
} ItemCreationRuntimeOptions;

typedef struct ItemCreationRuntimeRecord
{
    ItemCreationRuntimeOptions groups[3];
    u16 unk30;
    u8 unk32[2];
} ItemCreationRuntimeRecord;

typedef struct ItemCreationRuntimeRecordState
{
    u8 unk00[0x10F50];
    ItemCreationRuntimeRecord unk10f50[12];
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
extern "C"
{
    ItemCreationRuntimeRoot* func_10D8E0(void);
    ItemCreationRuntimeDirectory* func_101290(ItemCreationRuntimeRoot* root);
    ItemCreationRuntimeFlags* func_101440(ItemCreationRuntimeDirectory* directory, s32 key);

    extern ItemCreationRuntimeRecordState* D_001B64F8;
    extern u8 D_50CD30[];
}

/**
 * @brief Convert an option code to its runtime index.
 * @param value Option code.
 * @return Zero for an empty code, or the code minus 31.
 */
static inline u32 runtime_option_index(u8 value);

/**
 * @brief Test a one-based runtime record index.
 * @param index Record index.
 * @return True for indices one through twelve.
 */
static inline bool runtime_record_valid(u8 index);

/**
 * @brief Test a nonzero runtime option index.
 * @param index Option index.
 * @return True for indices one through thirty-eight.
 */
static inline bool runtime_option_valid(u8 index);

/**
 * @brief Test a nonzero runtime marker.
 * @param index Marker value.
 * @return True for values one through nine.
 */
static inline bool runtime_marker_valid(u8 index);

/**
 * @brief Store an option group whose supplied indices are valid.
 * @param state Runtime records.
 * @param record One-based record index.
 * @param group Group index.
 * @param first First option.
 * @param second Second option.
 * @param third Third option.
 * @param marker Marker value.
 */
static inline void store_runtime_options(ItemCreationRuntimeRecordState* state, u8 record, u8 group, u8 first, u8 second, u8 third, u8 marker);

static inline void enable_record_flag(ItemCreationSelectedDisplayState* object, u16 mask)
{
    if (object->unk134 != 0)
    {
        object->unk134->unk30 |= mask;
    }
}

/**
 * @brief Convert an option code to its runtime index.
 * @param value Option code.
 * @return Zero for an empty code, or the code minus 31.
 */
static inline u32 runtime_option_index(u8 value)
{
    if (value == 0)
    {
        return 0;
    }
    return value - 31;
}

/**
 * @brief Test a one-based runtime record index.
 * @param index Record index.
 * @return True for indices one through twelve.
 */
static inline bool runtime_record_valid(u8 index)
{
    return index > 0 && index < 13;
}

/**
 * @brief Test a nonzero runtime option index.
 * @param index Option index.
 * @return True for indices one through thirty-eight.
 */
static inline bool runtime_option_valid(u8 index)
{
    return index >= 1 && index < 39;
}

/**
 * @brief Test a nonzero runtime marker.
 * @param index Marker value.
 * @return True for values one through nine.
 */
static inline bool runtime_marker_valid(u8 index)
{
    return index >= 1 && index < 10;
}

/**
 * @brief Store an option group whose supplied indices are valid.
 * @param state Runtime records.
 * @param record One-based record index.
 * @param group Group index.
 * @param first First option.
 * @param second Second option.
 * @param third Third option.
 * @param marker Marker value.
 */
static inline void store_runtime_options(ItemCreationRuntimeRecordState* state, u8 record, u8 group, u8 first, u8 second, u8 third, u8 marker)
{
    if (!runtime_record_valid(record) || (s32)group < 0 || (s32)group >= 3)
    {
        return;
    }
    if (first > 0 && !runtime_option_valid(first))
    {
        return;
    }
    if (second > 0 && !runtime_option_valid(second))
    {
        return;
    }
    if (third > 0 && !runtime_option_valid(third))
    {
        return;
    }
    if (marker > 0 && !runtime_marker_valid(marker))
    {
        return;
    }
    ItemCreationRuntimeRecord* selected = &state->unk10f50[record - 1];
    ItemCreationRuntimeOptions* options = &selected->groups[group];
    options->options[0] = first;
    options->options[1] = second;
    options->options[2] = third;
    options->marker = marker;
}

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

/** @brief Initialize the twelve float pairs and their selection order. */
void ItemCreationSelection::func_slot10()
{
    unk00[0].unk00[0] = 136.0f;
    unk00[0].unk00[1] = 164.0f;
    unk00[1].unk00[0] = 136.0f;
    unk00[1].unk00[1] = 180.0f;
    unk00[2].unk00[0] = 60.0f;
    unk00[2].unk00[1] = 168.0f;
    unk00[3].unk00[0] = 348.0f;
    unk00[3].unk00[1] = 44.0f;
    unk00[4].unk00[0] = 340.0f;
    unk00[4].unk00[1] = 92.0f;
    unk00[5].unk00[0] = 212.0f;
    unk00[5].unk00[1] = 196.0f;
    unk00[6].unk00[0] = 160.0f;
    unk00[6].unk00[1] = 96.0f;
    unk00[7].unk00[0] = 96.0f;
    unk00[7].unk00[1] = 80.0f;
    unk00[8].unk00[0] = 108.0f;
    unk00[8].unk00[1] = 56.0f;
    unk00[9].unk00[0] = 60.0f;
    unk00[9].unk00[1] = 16.0f;
    unk00[10].unk00[0] = 380.0f;
    unk00[10].unk00[1] = 20.0f;
    unk00[11].unk00[0] = 16.0f;
    unk00[11].unk00[1] = 198.0f;
    unk6d[0] = 1;
    unk6d[1] = 2;
    unk6d[2] = 0;
    unk6d[3] = 5;
    unk6d[4] = 4;
    unk6d[5] = 3;
    unk6d[6] = 10;
    unk6d[7] = 9;
    unk6d[8] = 8;
    unk6d[9] = 7;
    unk6d[10] = 6;
    unk6d[11] = 11;
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

/**
 * @brief Refresh the enabled selection slots.
 * @return Always one.
 */
s32 ItemCreationSelection::func_slot0c()
{
    func_00369510(this);
    return 1;
}

/** @brief Initialize the selection coordinates, slot flags, and order. */
ItemCreationSelection::ItemCreationSelection()
{
    for (s32 index = 0; index < 12; index++)
    {
        unk00[index].unk00[0] = 0.0f;
        unk00[index].unk00[1] = 0.0f;
        unk60[index] = 0;
        unk6d[index] = 0;
    }
    unk6c = 0;
    func_slot10();
}

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
                position = selection->unk00[(u8)selected - 1].unk00;
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
    object->unk7e[0] = D_001B64F8->unk10f50[0].unk30;
    object->unk7e[1] = D_001B64F8->unk10f50[1].unk30;
    object->unk7e[2] = D_001B64F8->unk10f50[2].unk30;
    object->unk7e[3] = D_001B64F8->unk10f50[3].unk30;
    object->unk7e[4] = D_001B64F8->unk10f50[4].unk30;
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
                restore->FieldClass151C50::unk30 = 128.0f;
                restore->unkae = 1;
                x = display->unk10;
                y = display->unk14;
                restore = fourteen->unkac;
                restore->unk10 = x;
                restore->unk14 = y;
                restore->unk35 = 1;
                restore->unkae = 1;
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
                    restore->FieldClass151C50::unk30 = 128.0f;
                    restore->unkae = 1;
                    x = display->unk10;
                    y = display->unk14;
                    restore = nine->unkac;
                    restore->unk10 = x;
                    restore->unk14 = y;
                    restore->unk35 = 1;
                    restore->unkae = 1;
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
                    ItemCreationColorDisplay* view = (ItemCreationColorDisplay*)node->unk00;
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

/**
 * @brief Store the displayed option groups in the selected runtime record.
 * @param object Selected display state.
 */
void func_0036A8F0(ItemCreationSelectedDisplayState* object)
{
    for (s32 index = 0; index < object->unk57; index++)
    {
        store_runtime_options(D_001B64F8, object->unk134->unk32, index,
            runtime_option_index(object->unk68[index * 3]),
            runtime_option_index(object->unk68[index * 3 + 1]),
            runtime_option_index(object->unk68[index * 3 + 2]), object->unk1c0[index]);
    }
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036AAA0);

void func_0036AE20(ItemCreationSelectedDisplayState* object)
{
    if (object->unk134 != 0)
    {
        object->unk130 = object->unk134->unk30;
        if (object->unk130 & ITEM_CREATION_FLAG_0)
        {
            enable_record_flag(object, ITEM_CREATION_FLAG_0);
            object->unk4e[0] = 1;
        }
        if (object->unk130 & ITEM_CREATION_FLAG_1)
        {
            enable_record_flag(object, ITEM_CREATION_FLAG_1);
            object->unk4e[1] = 1;
        }
        if (object->unk130 & ITEM_CREATION_FLAG_2)
        {
            enable_record_flag(object, ITEM_CREATION_FLAG_2);
            object->unk4e[2] = 1;
        }
        if (object->unk130 & ITEM_CREATION_FLAG_3)
        {
            enable_record_flag(object, ITEM_CREATION_FLAG_3);
            object->unk4e[3] = 1;
        }
        if (object->unk130 & ITEM_CREATION_FLAG_4)
        {
            enable_record_flag(object, ITEM_CREATION_FLAG_4);
            object->unk4e[4] = 1;
        }
        if (object->unk130 & ITEM_CREATION_FLAG_5)
        {
            enable_record_flag(object, ITEM_CREATION_FLAG_5);
            object->unk4e[5] = 1;
        }
        if (object->unk130 & ITEM_CREATION_FLAG_6)
        {
            enable_record_flag(object, ITEM_CREATION_FLAG_6);
            object->unk4e[6] = 1;
        }
        if (object->unk130 & ITEM_CREATION_FLAG_7)
        {
            enable_record_flag(object, ITEM_CREATION_FLAG_7);
            object->unk4e[7] = 1;
        }
        enable_record_flag(object, ITEM_CREATION_FLAG_8);
        object->unk56 = 1;
    }
}

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

void ItemCreationSelectedDisplayState::func_0036BF30(s32 index, s32 enabled)
{
    ItemCreationAllocationRecord* records[100];
    unk148[index] = enabled;
    unk1b1[index] = 0;
    if (unk1b4[index] == 0)
    {
        unk1b1[index] = 1;
        unk148[index] = 0;
    }
    if (enabled != 0 && unk1b4[index] != 0)
    {
        s32 category = 0;
        if (unk1c3[index] >= 2)
        {
            switch (unk1c0[index])
            {
                case 1:
                    category = 20;
                    break;
                case 2:
                    category = 23;
                    break;
                case 3:
                    category = 36;
                    break;
                case 4:
                    category = 37;
                    break;
                case 5:
                    category = 33;
                    break;
                case 6:
                    category = 30;
                    break;
                case 7:
                    category = 31;
                    break;
                case 8:
                    category = 32;
                    break;
            }
            if (func_0040CF90(D_001B64F8, records, (u16)category) != 0)
            {
                func_0040C9F0(D_001B64F8, func_0040D890(records[0]));
            }
        }
    }
    unk188[index][0] = 0;
    unk188[index][1] = 0;
    unk188[index][2] = 0;
    unk191[index][0] = 1;
    unk191[index][1] = 1;
    unk191[index][2] = 1;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036C080);

void func_0036C1C0(ItemCreationSelectedDisplayState* object)
{
    if (object->unk1b1[0] == 0 || object->unk1b1[1] == 0 || object->unk1b1[2] == 0)
    {
        s32 index;
        s32 group;
        s32 value;
        for (;;)
        {
            index = func_0010CF80() % 9;
            group = index / 3;
            if (object->unk1b4[group] == 0)
            {
                continue;
            }
            if (object->unk1b1[group] != 0)
            {
                continue;
            }
            if (func_002FB510(object->unk1b4[group], index % 3) == 3)
            {
                continue;
            }
            value = object->unk68[index];
            if (value > 0)
            {
                break;
            }
        }
        if (value >= 32 && value < 60)
        {
            s32 resource = value + 596;
            if (object->unk19c != 0)
            {
                func_002FD940(object->unk19c);
                object->unk1a8 = 1;
            }
            object->unk1a0 = resource;
            object->unk1a4 = 0;
        }
        else
        {
            s32 resource = (value - 60) * 9 + 538;
            s32 code = object->unk1c0[group];
            if (object->unk19c != 0)
            {
                func_002FD940(object->unk19c);
                object->unk1a8 = 1;
            }
            object->unk1a0 = resource;
            if (code != 0)
            {
                object->unk1a4 = resource + code;
            }
            else
            {
                object->unk1a4 = 0;
            }
        }
    }
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036C340);

s32 func_0036CD60(void* object)
{
    return -1;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036CD70);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036CE00);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036DDC0);

void func_0036DEA0(ItemCreationSelectedDisplayState* object)
{
    func_0036A8F0(object);
    func_0011ED90(D_001B65F4, object);
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036DED0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036E0D0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003684D0", func_0036E170);

ItemCreationClass184F18::~ItemCreationClass184F18()
{
}

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

void func_0036E630(ItemCreationTransformState* object, const float* input)
{
    object->unk50 = 1;
    func_004CE4C0(object->unk30, input);
}

void func_0036E660(ItemCreationTransformState* object, const float* input)
{
    object->unk50 = 1;
    func_004CE4C0(object->unk30, input);
}

void func_0036E690(u8* object, float x, float y, float z)
{
    ItemCreationTransformState* transform = (ItemCreationTransformState*)object;
    float value[4];
    transform->unk50 = 1;
    value[0] = x;
    value[1] = y;
    value[2] = z;
    value[3] = 1.0f;
    func_004CE4C0(transform->unk30, value);
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
    s32 result = 1;
    if (!(value < 0.0f))
    {
        result = 0;
    }
    return result;
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

/**
 * @brief Destroy the result window through its Field base.
 */
ItemCreationClass186370::~ItemCreationClass186370()
{
}

/**
 * @brief Destroy the result prompt window and release its Field base.
 */
ItemCreationClass186470::~ItemCreationClass186470()
{
}

/**
 * @brief Destroy the selected item prompt window through its Field base.
 */
ItemCreationClass186570::~ItemCreationClass186570()
{
}

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

void func_0036EDB0(ItemCreationCountedList* object, void* record)
{
    ItemCreationListNode* node = (ItemCreationListNode*)func_00100AC0(sizeof(ItemCreationListNode), 0);
    if (node != 0)
    {
        ItemCreationListNode* tail;
        ItemCreationListNode* next;
        node->unk00 = record;
        node->unk04 = 0;
        tail = object->unk00;
        next = tail->unk04;
        while (next != 0)
        {
            tail = next;
            next = next->unk04;
        }
        tail->unk04 = node;
        object->unk04++;
    }
}

void func_0036EE40(ItemCreationCountedList* object, ItemCreationListNode* after, void* const* record)
{
    ItemCreationListNode* node = (ItemCreationListNode*)func_00100AC0(sizeof(ItemCreationListNode), 0);
    node->unk00 = *record;
    if (after != 0)
    {
        node->unk04 = after->unk04;
        after->unk04 = node;
    }
    else
    {
        ItemCreationListNode* tail = object->unk00;
        ItemCreationListNode* next = tail->unk04;
        while (next != 0)
        {
            tail = next;
            next = next->unk04;
        }
        tail->unk04 = node;
        node->unk04 = 0;
    }
    object->unk04++;
}

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

void func_0036EFB0(ItemCreationCountedList* object, void* value)
{
    ItemCreationListNode* node = (ItemCreationListNode*)func_00100AC0(sizeof(ItemCreationListNode), 0);
    if (node != 0)
    {
        ItemCreationListNode* tail;
        ItemCreationListNode* next;
        node->unk00 = value;
        node->unk04 = 0;
        tail = object->unk00;
        next = tail->unk04;
        while (next != 0)
        {
            tail = next;
            next = next->unk04;
        }
        tail->unk04 = node;
        object->unk04++;
    }
}

void func_0036F040(ItemCreationCountedList* object, void* value)
{
    ItemCreationListNode* node = (ItemCreationListNode*)func_00100AC0(sizeof(ItemCreationListNode), 0);
    if (node != 0)
    {
        ItemCreationListNode* tail;
        ItemCreationListNode* next;
        node->unk00 = value;
        node->unk04 = 0;
        tail = object->unk00;
        next = tail->unk04;
        while (next != 0)
        {
            tail = next;
            next = next->unk04;
        }
        tail->unk04 = node;
        object->unk04++;
    }
}

void func_0036F0D0(ItemCreationCountedList* object, void* value)
{
    ItemCreationListNode* node = (ItemCreationListNode*)func_00100AC0(sizeof(ItemCreationListNode), 0);
    if (node != 0)
    {
        ItemCreationListNode* tail;
        ItemCreationListNode* next;
        node->unk00 = value;
        node->unk04 = 0;
        tail = object->unk00;
        next = tail->unk04;
        while (next != 0)
        {
            tail = next;
            next = next->unk04;
        }
        tail->unk04 = node;
        object->unk04++;
    }
}

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

void func_0036F1A0(ItemCreationCountedList* object, void* value)
{
    ItemCreationListNode* node = (ItemCreationListNode*)func_00100AC0(sizeof(ItemCreationListNode), 0);
    if (node != 0)
    {
        ItemCreationListNode* tail;
        ItemCreationListNode* next;
        node->unk00 = value;
        node->unk04 = 0;
        tail = object->unk00;
        next = tail->unk04;
        while (next != 0)
        {
            tail = next;
            next = next->unk04;
        }
        tail->unk04 = node;
        object->unk04++;
    }
}

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

void func_0036F270(ItemCreationCountedList* object, void* value)
{
    ItemCreationListNode* node = (ItemCreationListNode*)func_00100AC0(sizeof(ItemCreationListNode), 0);
    if (node != 0)
    {
        ItemCreationListNode* tail;
        ItemCreationListNode* next;
        node->unk00 = value;
        node->unk04 = 0;
        tail = object->unk00;
        next = tail->unk04;
        while (next != 0)
        {
            tail = next;
            next = next->unk04;
        }
        tail->unk04 = node;
        object->unk04++;
    }
}

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
