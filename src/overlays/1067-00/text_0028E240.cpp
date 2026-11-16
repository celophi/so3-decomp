#include "include_asm.h"
#include "overlays/1067-00/text_0028E240.h"
#include "sdk/main/libc_guess_0013A4C0.h"

typedef struct FieldSourceContext
{
    u8 pad[0x62];
    u8 unk62;
} FieldSourceContext;

typedef struct FieldRecordSource
{
    u8 pad[4];
    FieldRecord* records;
    void* unk08;
    u8 pad0c[4];
    FieldSourceContext* context;
} FieldRecordSource;

extern "C" FieldRecordSource* D_001B643C;

extern "C" s32 func_0028E240(FieldRecordSelection* selection, s8 value)
{
    s32 index;
    s32 result = -1;

    for (index = 0; index < 8; index++)
    {
        if (selection->records[(s16)index].unk00 == value)
        {
            result = (s8)index;
            break;
        }
    }

    return result;
}

/**
 * @brief Move the current slot to the next filled one forward or backward, wrapping round, unless a move is already
 * active, then mark a move active.
 * @param selection Record selection.
 * @param forward Nonzero to move forward.
 */
extern "C" void func_0028E2B0(FieldRecordSelection* selection, s32 forward)
{
    s32 index;
    u8 found = 0;

    if (selection->active)
    {
        return;
    }

    if (forward)
    {
        for (index = selection->current + 1; index < 8; index++)
        {
            if (selection->slots[index] > 0)
            {
                selection->current = index;
                found = 1;
                break;
            }
        }

        if (found == 0)
        {
            for (index = 0; index < 8; index++)
            {
                if (selection->slots[index] > 0)
                {
                    selection->current = index;
                    break;
                }
            }
        }
    }
    else
    {
        for (index = selection->current - 1; index >= 0; index--)
        {
            if (selection->slots[index] > 0)
            {
                selection->current = index;
                found = 1;
                break;
            }
        }

        if (found == 0)
        {
            for (index = 7; index >= 0; index--)
            {
                if (selection->slots[index] > 0)
                {
                    selection->current = index;
                    break;
                }
            }
        }
    }

    selection->active = 1;
}

extern "C" s32 func_0028E3D0(FieldRecordSelection* selection)
{
    s32 index;
    selection->records = D_001B643C->records;
    selection->unk04 = D_001B643C->unk08;

    if (selection->records == 0 || selection->unk04 == 0)
    {
        return 0;
    }

    for (index = 0; index < 8; index++)
    {
        FieldRecord* record = &selection->records[index];
        s32 value = record->unk00;
        s16 state = record->unk02;

        if (state == 0 && value != 0)
        {
            selection->count++;
            selection->slots[index] = value;
        }
    }

    selection->current = D_001B643C->context->unk62;
    return 1;
}

/** @brief Destroy the record selection through its native virtual destructor. */
FieldRecordSelection::~FieldRecordSelection()
{
}

/** @brief Clear record links and slot bytes, then select no current slot. */
FieldRecordSelection::FieldRecordSelection()
{
    records = 0;
    unk04 = 0;
    memset_guess(slots, 0, 8);
    count = 0;
    current = -1;
    active = 0;
}
