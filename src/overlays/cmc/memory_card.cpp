#include "include_asm.h"
#include "overlays/cmc/cmc.h"
#include "sdk/main/libc_0013CA60.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "overlays/1067-00/field_runtime.h"

/** Partial system record holding the last save's identifier. */
struct CmcSystemRecord
{
    u8 unk000[0x188];
    u32 unk188;
};

extern "C" {
extern FieldWindowRuntime* D_001B643C;

extern void func_002F2890(FieldClass15B9C0* object);

extern u8 func_002EFFF0(FieldClass15B9C0* object);

extern LibCardFileRequest* func_002EF000(FieldClass15B9C0* object);

extern u8 func_002EF6B0(FieldClass15B9C0* object);

extern u8 func_002F1E60(FieldClass15B9C0* object);

extern u8 func_002F1B20(FieldClass15B9C0* object);

extern void func_00432710(LibMemoryCard* card, u32 flags);

extern void func_002EEE00(FieldClass15B9C0* object, CmcRowRecord* entry);

extern u8 func_002EEE90(FieldClass15B9C0* object, s16 index);

extern void func_002F23E0(FieldClass15B9C0* object, const char* game, const char* suffix);

extern void func_002EF010(FieldClass15B9C0* object, s16 value);

extern u8 func_002EF520(FieldClass15B9C0* object);

extern u8 func_002EED90(FieldClass15B9C0* object);

extern u8 func_002EEC90(FieldClass15B9C0* object);

extern s32 func_002EEB30(FieldClass15B9C0* object);

extern void func_002EE9E0(FieldClass15B9C0* object);

extern void func_431770(LibMemoryCard* card, s32 value);

extern const char g_cmc_save_directory_wildcard[];
extern const char g_cmc_trophy_directory_suffix[];

extern const char g_cmc_product_code[];

extern u8 func_002F2470(FieldClass15B9C0* object, s32 mode);

extern LibUpdateList* g_update_list;
}

/**
 * @brief Return the handler's list kind.
 * @return Two.
 */
s32 CardTask::get_default_list_kind()
{
    return 2;
}

/**
 * @brief Parse five hexadecimal digits; anything that isn't a hex digit counts as zero.
 * @param text Text holding the digits.
 * @param offset Offset of the first digit.
 * @return The parsed value.
 */
static inline s32 cmc_parse_hex5(const char* text, s32 offset)
{
    char digits[6];
    digits[5] = 0;
    digits[4] = 0;
    digits[3] = 0;
    digits[2] = 0;
    digits[1] = 0;
    digits[0] = 0;

    for (s32 index = 0; index < 5; index++)
    {
        digits[index] = text[index + offset];
    }

    s32 value = 0;

    for (s32 index = 0; index < 5; index++)
    {
        s32 digit = digits[index];

        if (digit >= '0' && digit <= '9')
        {
            digit -= '0';
        }
        else if (digit >= 'a' && digit <= 'f')
        {
            digit -= 'a' - 10;
        }
        else if (digit >= 'A' && digit <= 'F')
        {
            digit -= 'A' - 10;
        }
        else
        {
            digit = 0;
        }

        value = value * 16 + digit;
    }

    return value;
}

/**
 * @brief Record the file just read as a save entry, then start reading the next file or finish.
 * @param skip Nonzero to skip recording the entry.
 */
void CardTask::func_00359970(s32 skip)
{
    if (static_cast<u8>(skip) == 0)
    {
        CmcRowRecord* entry = static_cast<CmcRowRecord*>(operator new(0x80, 0));
        memset_guess(entry, 0, 0x80);
        s32 value = cmc_parse_hex5(unk18->unk100b, strlen(g_cmc_product_code) + 1);

        if (0 < value && value < 0x2E)
        {
            entry->slot = value;
        }
        else
        {
            entry->slot = 0;
        }

        func_002EEE00(unk18, entry);
    }

    func_00431730(card);
    func_004317B0(card, 3);
    unk36++;

    if (unk36 == unk18->unk105a)
    {
        unk22 = unk36;
        unk1e = 0;
        unk39 = 1;
        unk34 = 1;
        unk1e = 0;
        return;
    }

    unk20 = 0;
    unk1e = 4;
    unk22 = 0;
    unk39 = 0;
    unk34 = 0;
    unk30 = -1;

    if (func_002EEE90(unk18, unk36) == 0)
    {
        unk22 = -1;
        unk1e = 0;
        unk39 = 0;
        unk34 = 1;
        unk1e = 0;
        return;
    }

    if (lib_memory_card_start_transfer(card, selected, func_002EF000(unk18)) == 0)
    {
        unk20 = 0;
        unk1e = 4;
        unk22 = 0;
        unk39 = 0;
        unk34 = 0;
        unk30 = -1;
        return;
    }

    unk22 = -1;
    unk1e = 0;
    unk39 = 0;
    unk34 = 1;
    unk1e = 0;
}

/**
 * @brief Read the card object's byte at offset 0x28.
 * @return Stored byte.
 */
u8 CardTask::func_00359C10()
{
    return card->unk28;
}

/**
 * @brief Read the Field save object's word at offset 0x1250, clamped to zero.
 * @return The word, or zero when it isn't positive.
 */
s32 CardTask::func_00359C20()
{
    s32 value = unk18->unk1250;

    if (value > 0)
    {
        return value;
    }

    return 0;
}

/**
 * @brief Run one step of saving the Field object's data to the selected card slot.
 * @return Zero while the save runs, one once it finished, or -1 when the data isn't ready.
 */
s32 CardTask::func_00359C50()
{
    s32 result = 0;

    switch (unk20)
    {
    case 0:
        if (unk18->unk1009 == 0)
        {
            result = func_002EFFF0(unk18);
        }

        if (result == 0)
        {
            return -1;
        }

        result = lib_memory_card_start_transfer(card, selected, func_002EF000(unk18));

        if (result == 0)
        {
            unk20++;
            unk58 = -1;
            unk5c = -1;
        }

        break;
    case 1:
        if (lib_memory_card_get_result(card, selected, &unk30) != 0)
        {
            unk20++;
            result = 1;

            if (unk30 >= 0)
            {
                if (func_002EF6B0(unk18) == 0)
                {
                    unk30 = -1;
                    unk58 = -1;
                }
                else
                {
                    unk58 = result;
                }
            }
            else
            {
                unk58 = -1;
                unk5c = -1;
            }
        }

        break;
    case 2:
        break;
    }

    return result;
}

/**
 * @brief Run one step of loading the selected card slot into the Field object.
 * @return Zero while the load runs, one once a step finished, or -1 when the Field object isn't ready.
 */
s32 CardTask::func_00359DA0()
{
    s32 result = 0;

    switch (unk20)
    {
    case 0:
        if (unk18->unk1008 == 0)
        {
            if (unk48 != 0)
            {
                func_00432710(card, 0x202);
                unk18->unk1244 = 1;
            }
            else
            {
                func_00432710(card, 2);
                unk18->unk1244 = 0;
            }

            result = func_002F1E60(unk18);
        }

        if (result == 0)
        {
            return -1;
        }

        card->unk28 = 0;
        result = func_004324D0(card, selected, func_002EF000(unk18));

        if (result == 0)
        {
            unk20++;
        }

        break;
    case 1:
        result = lib_memory_card_get_result(card, selected, &unk30);

        if (result != 0 && result == 1)
        {
            if (unk48 != 0)
            {
                if (unk30 >= 0)
                {
                    unk20++;
                    result = 0;
                    func_00432710(card, 2);
                }
                else
                {
                    unk20 += 4;
                    func_00432710(card, 0x202);
                }
            }
            else
            {
                unk20 += 4;
                func_00432710(card, 0x202);
            }
        }

        break;
    case 2:
        if (unk48 != 0)
        {
            if (func_002F1B20(unk18) == 0)
            {
                return -1;
            }

            result = func_004324D0(card, selected, func_002EF000(unk18));

            if (result == 0)
            {
                unk20++;
            }
        }

        break;
    case 3:
        if (unk48 != 0)
        {
            result = lib_memory_card_get_result(card, selected, &unk30);

            if (result != 0 && result == 1)
            {
                unk20++;
                func_00432710(card, 0x202);
            }
        }

        break;
    }

    return result;
}

/** @brief Run the selected memory card operation one frame further. */
void CardTask::update()
{
    if (card == 0 || unk18 == 0)
    {
        return;
    }

    if (func_002F2880(unk18) == 0)
    {
        return;
    }

    s16 previous = unk24;
    s32 state = previous;

    if (unk34 == 0)
    {
        state = selected < 0 ? -1 : card->slots[selected].card_state;

        if (state != previous)
        {
            unk24 = state;

            if (mode == 0)
            {
                unk1e = 1;

                if (unk60 != 0)
                {
                    unk60 = 0;
                    return;
                }
            }
            else if (unk44 == 0)
            {
                unk1e = 5;
            }
            else
            {
                unk1e = 9;
            }

            if (unk39 == 1)
            {
                unk38 = 1;
                unk1e = 0;
            }

            return;
        }
    }

    s32 result = 0;

    switch (unk1e)
    {
    case 0:
        break;
    case 1:
        if (state != 2)
        {
            stop(0);
            unk22 = -1;
            unk30 = -12;
            unk1e = 0;
            break;
        }

        unk22 = 0;
        unk28 = card->slots[selected].formatted;

        if (unk28 == 0)
        {
            stop(1);
            break;
        }

        unk2c = card->slots[selected].free_space;

        if (unk64 > 0)
        {
            unk64--;
            break;
        }

        unk1e = 2;
        unk39 = 0;
        break;
    case 2:
        func_002F23E0(unk18, g_cmc_product_code, g_cmc_save_directory_wildcard);

        if (lib_memory_card_probe_file(card, selected, unk18->unk100b, 0, 0x32, unk18->unkF7C) != -1)
        {
            func_002F2890(unk18);
            unk1e = 3;
        }

        break;
    case 3:
    {
        s32 status = lib_memory_card_get_result(card, selected, &result);

        if (status == 0 || status != 1)
        {
            break;
        }

        if (result > 0)
        {
            func_002EF010(unk18, result);
            unk36 = 0;
            unk54 = 0;
            unk50 = 0;
            unk69 = 0;
            func_002F2890(unk18);
            func_00431730(card);
            func_004317B0(card, 3);
        }

        if (result == 0)
        {
            unk22 = 0;
            stop(1);
            unk1e = 0;
        }
        else if (result > 0)
        {
            unk20 = 0;
            unk1e = 4;
            unk22 = 0;
            unk39 = 0;
            unk34 = 0;
            unk30 = -1;

            if (func_002EEE90(unk18, unk36) == 0)
            {
                unk22 = -1;
                stop(0);
                unk1e = 0;
            }
            else if (lib_memory_card_start_transfer(card, selected, func_002EF000(unk18)) == 0)
            {
                unk20 = 0;
                unk1e = 4;
                unk22 = 0;
                unk39 = 0;
                unk34 = 0;
                unk30 = -1;
            }
            else
            {
                unk22 = -1;
                stop(0);
                unk1e = 0;
            }
        }
        else if (result < -10)
        {
            unk22 = -1;
            stop(0);
            unk1e = 0;
            unk30 = result;
        }
        else
        {
            func_00359970(0);
        }

        break;
    }
    case 4:
    {
        s32 status = lib_memory_card_get_result(card, selected, &result);

        if (status == 0 || status != 1)
        {
            break;
        }

        if (result == 0)
        {
            unk46 = selected;

            if (func_002EF520(unk18) != 0)
            {
                unk40 = 1;
            }

            CmcRowRecord* copy = new (0) CmcRowRecord;
            memset_guess(copy, 0, 0x80);
            memcpy_guess(copy, unk18->unkF8C, 0x80);

            if (unk50 < copy->unk3c && unk69 == 0 && 0 < static_cast<u16>(copy->slot) && static_cast<u16>(copy->slot) < 0x2E)
            {
                unk50 = copy->unk3c;
                unk54 = copy->slot;
            }

            CmcSystemRecord* system = static_cast<CmcSystemRecord*>(func_101440(func_101290(resident_get_system()), 1));

            if (system->unk188 != 0 && copy->unk58 == system->unk188 && 0 < static_cast<u16>(copy->slot) && static_cast<u16>(copy->slot) < 0x2E)
            {
                unk50 = copy->unk3c;
                unk54 = copy->slot;
                unk69 = 1;
            }

            func_431770(card, 3);
            s32 value = cmc_parse_hex5(unk18->unk100b, strlen(g_cmc_product_code) + 1);

            if (0 < value && value < 0x2E)
            {
                copy->slot = value;
            }
            else
            {
                copy->slot = 0;
            }

            func_002EEE00(unk18, copy);
            func_00359970(1);
        }
        else if (result < -10)
        {
            unk22 = -1;
            stop(0);
            unk1e = 0;
            unk30 = result;
        }
        else
        {
            func_00359970(0);
        }

        break;
    }
    case 5:
        if (state != 2)
        {
            unk42[selected] = 0x81;
        }
        else
        {
            unk28 = card->slots[selected].formatted;

            if (unk28 == 0)
            {
                unk42[selected] = 0x81;
            }
        }

        unk1e = 6;
        break;
    case 6:
        if (unk42[selected] != 0x81)
        {
            func_002F23E0(unk18, g_cmc_product_code, g_cmc_trophy_directory_suffix);

            if (lib_memory_card_probe_file(card, selected, unk18->unk100b, 0, 1, unk18->unkF7C) != -1)
            {
                unk1e = 7;
            }
        }
        else
        {
            unk1e = 7;
        }

        break;
    case 7:
        if (unk42[selected] != 0x81)
        {
            s32 status = lib_memory_card_get_result(card, selected, &result);

            if (status == 0 || status != 1)
            {
                break;
            }

            if (result == 0)
            {
                unk42[selected] = 0x81;
            }
            else if (result > 0)
            {
                unk42[selected] = 0x82;
            }

            if (selected == 0)
            {
                selected = 1;
                unk1e = 5;
            }
            else
            {
                unk1e = 8;
            }
        }
        else if (selected == 0)
        {
            unk1e = 5;
            selected = 1;
        }
        else
        {
            unk1e = 8;
        }

        break;
    case 8:
        if (unk42[0] == 0x81 && unk42[1] == 0x81)
        {
            if (static_cast<u8>(D_001B643C->unk00->unk25_6) == 1)
            {
                unk30 = 0;
                unk4c = 0x81;
            }
            else
            {
                unk30 = 0;
                unk4c = 0;
            }

            stop(0);
        }
        else if (unk42[0] == 0x82 && unk42[1] == 0x81)
        {
            selected = 0;
            unk1e = 9;
        }
        else if (unk42[0] == 0x81 && unk42[1] == 0x82)
        {
            selected = 1;
            unk1e = 9;
        }
        else
        {
            unk30 = 0;
            unk4c = 0x85;
            stop(0);
        }

        unk44 = 1;
        break;
    case 9:
        if (state != 2)
        {
            unk22 = -1;
            stop(0);
            unk1e = 0;
            unk5c = -1;
            unk4c = 0x86;
            break;
        }

        unk28 = card->slots[selected].formatted;

        if (unk28 == 0 && unk44 == 1)
        {
            unk4c = 0x81;
            unk30 = -2;
            stop(0);
            break;
        }

        unk1e = 0xA;
        break;
    case 0xA:
        func_002F23E0(unk18, g_cmc_product_code, g_cmc_trophy_directory_suffix);

        if (lib_memory_card_probe_file(card, selected, unk18->unk100b, 0, 1, unk18->unkF7C) != -1)
        {
            unk1e = 0xB;
        }

        break;
    case 0xB:
    {
        s32 status = lib_memory_card_get_result(card, selected, &result);

        if (status == 0)
        {
            break;
        }

        if (status == 1)
        {
            if (result == 0)
            {
                unk30 = result;
                unk4c = 0x81;
                stop(0);
                break;
            }

            if (result > 0)
            {
                unk30 = result;

                if (func_002EED90(unk18) == 0)
                {
                    status = func_002EEC90(unk18);
                }

                if (status == 0)
                {
                    unk22 = -1;
                    stop(0);
                    unk1e = 0;
                    break;
                }

                if (lib_memory_card_start_transfer(card, selected, func_002EF000(unk18)) == 0)
                {
                    unk1e = 0xC;
                }

                break;
            }

            stop(0);
            unk30 = result;

            if (result < -10)
            {
                unk22 = result;
                unk4c = 0x81;
            }
            else
            {
                unk22 = -1;
                unk4c = 0x86;
            }

            unk1e = 0;
            unk5c = -1;
            break;
        }

        unk30 = result;
        unk22 = -1;
        stop(0);
        unk1e = 0;
        break;
    }
    case 0xC:
    {
        s32 status = lib_memory_card_get_result(card, selected, &unk30);

        if (status == 0)
        {
            break;
        }

        if (status == 1)
        {
            if (unk30 >= 0)
            {
                if (func_002EEB30(unk18) != 0)
                {
                    func_002EE9E0(unk18);
                    unk4c = 0;
                    stop(0);
                    unk1e = 0;
                    unk5c = 1;
                }
                else
                {
                    unk4c = 0x83;
                    stop(0);
                    unk1e = 0;
                    unk5c = -1;
                }
            }
            else
            {
                unk22 = unk30;
                stop(0);
                unk1e = 0;
                unk4c = 0x86;
                unk5c = -1;
            }

            break;
        }

        unk22 = -1;
        stop(0);
        unk1e = 0;
        break;
    }
    case 0x20:
    {
        s32 status = func_0035AE70();

        if (status != 0)
        {
            unk22 = status;
            unk1e = 0;
        }

        break;
    }
    case 0x40:
        if (func_00359DA0() != 0)
        {
            stop(0);
        }

        break;
    case 0x30:
        if (func_00359C50() == 0)
        {
            break;
        }

        if (unk30 < 0)
        {
            stop(0);
            break;
        }

        if (unk49 == 0)
        {
            unk39 = 0;
            mode = 1;
            unk1e = 5;
            selected = 0;
            break;
        }

        stop(0);
        break;
    }
}

/**
 * @brief Set the state and the companion byte, clearing unk1e when the state is one.
 * @param value New state.
 * @param other New companion byte.
 */
void CardTask::func_0035ADA0(u8 value, u8 other)
{
    if (value == 1)
    {
        unk1e = 0;
    }

    unk39 = other;
    unk34 = value;
}

/**
 * @brief Select a record and reset the run state for the given mode.
 * @param index Record index to select.
 * @param mode Run mode; mode one skips the colour defaults.
 */
void CardTask::func_0035ADD0(s16 index, u8 mode)
{
    selected = index;
    unk24 = -1;
    unk39 = 0;
    unk38 = 0;
    unk22 = 0;
    unk39 = 0;
    unk34 = 0;
    unk3c = 0;
    unk40 = 0;
    this->mode = mode;

    if (this->mode == 1)
    {
        unk34 = 0;
    }
    else
    {
        unk44 = 0;
        unk42[0] = 0x80;
        unk42[1] = 0x80;
    }

    if (unk18 != 0)
    {
        func_002F2890(unk18);
    }

    unk64 = 4;
}

/**
 * @brief Run one step of the selected card slot's two-step check.
 * @return Zero while the check runs, one once it passed, or -1 on failure.
 */
s32 CardTask::func_0035AE70()
{
    s32 result = 0;
    s32 failed = 0;

    switch (unk20)
    {
    case 0:
        if (func_004325A0(card, selected) == -1)
        {
            result = -1;
        }
        else
        {
            unk20++;
        }

        break;
    case 1:
        result = lib_memory_card_get_result(card, selected, &failed);

        if (result == 0)
        {
            if (failed != 0)
            {
                result = -1;
            }
        }
        else if (result == 1)
        {
            if (failed == 0)
            {
                result = 1;
            }
            else
            {
                result = -1;
            }

            unk20++;
        }

        break;
    }

    return result;
}

/**
 * @brief Reset the state for a new run starting at unk1e = value.
 * @param value Starting value for unk1e.
 */
void CardTask::func_0035AF60(s16 value)
{
    unk20 = 0;
    unk1e = value;
    unk22 = 0;
    unk39 = 0;
    unk34 = 0;
    unk30 = -1;
}

/**
 * @brief Read the selected card slot's formatted flag.
 * @return Formatted flag.
 */
s32 CardTask::func_0035AF80()
{
    return card->slots[selected].formatted;
}

/**
 * @brief Read the selected card slot's free space.
 * @return Free space.
 */
s32 CardTask::func_0035AFA0()
{
    return card->slots[selected].free_space;
}

/**
 * @brief Read unk22.
 * @return Stored value.
 */
s16 CardTask::func_0035AFC0()
{
    return unk22;
}

/**
 * @brief Read a card slot's state.
 * @param index Card slot.
 * @return Card state.
 */
s32 CardTask::func_0035AFD0(s16 index)
{
    return card->slots[index].card_state;
}

/**
 * @brief Create the memory card and the Field object and open both card slots.
 * @return One on success, or zero when an allocation or the Field object's setup fails.
 */
u8 CardTask::func_0035AFF0()
{
    card = new (0) LibMemoryCard;

    if (card == 0)
    {
        return 0;
    }

    lib_memory_card_init(card, g_update_list);
    lib_memory_card_open_slot(card, 0, 0, 0);
    lib_memory_card_open_slot(card, 1, 1, 0);
    unk18 = new (0) FieldClass15B9C0;

    if (unk18 == 0)
    {
        return 0;
    }

    if (func_002F2470(unk18, 0) == 0)
    {
        return 0;
    }

    unk1e = 0;
    return 1;
}

/** @brief Release the Field object and the memory card, then queue the handler for release. */
void CardTask::destroy()
{
    if (unk18 != 0)
    {
        if (unk18 != 0)
        {
            delete unk18;
            unk18 = 0;
        }
    }

    if (card != 0)
    {
        card->destroy();
    }

    resident_enqueue_object(g_resident_release_queues, this);
}

/** @brief Destroy the handler. */
CardTask::~CardTask()
{
}

/** @brief Initialize the handler with nothing selected. */
CardTask::CardTask()
{
    card = 0;
    unk18 = 0;
    unk22 = 0;
    unk1e = -1;
    unk20 = 0;
    selected = -1;
    unk24 = -1;
    unk28 = 0;
    unk2c = 0;
    unk34 = 0;
    unk36 = 0;
    unk38 = 0;
    unk39 = 0;
    unk3c = 0;
    unk40 = 0;
    unk48 = 0;
    mode = 0;
    unk44 = 0;
    unk42[0] = 0x80;
    unk42[1] = 0x80;
    unk46 = 0;
    unk49 = 0;
    unk4c = 0;
    unk50 = 0;
    unk54 = 0;
    unk30 = -1;
    unk60 = 0;
    unk58 = -1;
    unk5c = -1;
    unk64 = 0;
    unk69 = 0;
}
