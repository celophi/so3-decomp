#include "include_asm.h"
#include "overlays/lib/particle_grid.h"
#include "overlays/lib/particle_history.h"
#include "overlays/lib/text_004CD3A0.h"
#include "vu0.h"
#include "ee.h"

/**
 * @brief Copy another grid's size and settings, reallocating this grid to match.
 *
 * LibClass176050's copy_settings (vtable slot 0xB4).
 * @param object Grid to update.
 * @param other Grid to copy.
 */
void func_0048B300(LibGridEmitter* object, const LibGridEmitter* other)
{
    object->cell_count = other->cell_count;
    object->columns = other->columns;
    object->resize(object->cell_count, object->columns);
    object->unk28 = other->unk28;
    object->unk30 = other->unk30;
    object->unk34 = other->unk34;
    object->unk38 = other->unk38;
    object->unk48 = other->unk48;
    object->unk4C = other->unk4C;
    object->unk4D = other->unk4D;
    object->unk4E = other->unk4E;
    object->unk4F = other->unk4F;
    object->unk50 = other->unk50;
    object->unk54 = other->unk54;
    object->unk55 = other->unk55;
    object->unk3C = other->unk3C;
    object->frame_header = other->frame_header;
    object->frame_records = other->frame_records;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0048B300", func_0048B3D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0048B300", func_0048BAB0);

/**
 * @brief Copy another grid's size and settings, reallocating this grid to match.
 *
 * LibClass175DE0's copy_settings (vtable slot 0xB4).
 * @param object Grid to update.
 * @param other Grid to copy.
 */
void func_0048E480(LibGridEmitter* object, const LibGridEmitter* other)
{
    object->cell_count = other->cell_count;
    object->columns = other->columns;
    object->resize(object->cell_count, object->columns);
    object->unk28 = other->unk28;
    object->unk30 = other->unk30;
    object->unk34 = other->unk34;
    object->unk38 = other->unk38;
    object->unk48 = other->unk48;
    object->unk4C = other->unk4C;
    object->unk4D = other->unk4D;
    object->unk4E = other->unk4E;
    object->unk4F = other->unk4F;
    object->unk50 = other->unk50;
    object->unk54 = other->unk54;
    object->unk55 = other->unk55;
    object->unk3C = other->unk3C;
    object->frame_header = other->frame_header;
    object->frame_records = other->frame_records;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0048B300", func_0048E550);

/**
 * @brief Copy selected group histories and extend the caller's VU0 bounds.
 * @param object Receiver containing selection masks, source records, and histories.
 * @param capacity Output-record count at which processing stops before the next group.
 * @param output Destination array of three-vector records.
 * @param stamp Nonzero to copy the receiver's raw word at 0x28 into control records.
 */
void func_0048ECB0(LibHistoryReceiver48ECB0* object, s32 capacity, LibHistoryOutput30* output, u32 stamp)
{
    s32 samples = object->samples;
    s32 index = object->index;
    s32 limit = object->limit;
    const u64* masks = object->mask->bits;
    u64 bit = (u64)1 << (index & 63);
    s32 mask_index = index / 64;
    s32 processed = 0;
    u64 mask = masks[mask_index++];
    switch (object->policy)
    {
        case 0:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySourceB0* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySourceB0* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySourceB0* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySourceB0* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySourceB0* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySourceB0* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySourceB0* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySourceB0* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
        case 1:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySourceB0* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySourceB0* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySourceB0* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySourceB0* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySourceB0* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySourceB0* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySourceB0* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySourceB0* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
        case 2:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            LibHistorySourceB0* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            LibHistorySourceB0* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            LibHistorySourceB0* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            LibHistorySourceB0* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            LibHistorySourceB0* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            LibHistorySourceB0* source = &object->source[index - 1];
                            s32 history_index = index * (samples - 1) - 1;
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            LibHistorySourceB0* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            LibHistorySourceB0* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
    }
}

/**
 * @brief Copy another grid's size and settings, reallocating this grid to match.
 *
 * LibClass175B70's copy_settings (vtable slot 0xB4).
 * @param object Grid to update.
 * @param other Grid to copy.
 */
void func_00491820(LibGridEmitter* object, const LibGridEmitter* other)
{
    object->cell_count = other->cell_count;
    object->columns = other->columns;
    object->resize(object->cell_count, object->columns);
    object->unk28 = other->unk28;
    object->unk30 = other->unk30;
    object->unk34 = other->unk34;
    object->unk38 = other->unk38;
    object->unk48 = other->unk48;
    object->unk4C = other->unk4C;
    object->unk4D = other->unk4D;
    object->unk4E = other->unk4E;
    object->unk4F = other->unk4F;
    object->unk50 = other->unk50;
    object->unk54 = other->unk54;
    object->unk55 = other->unk55;
    object->unk3C = other->unk3C;
    object->frame_header = other->frame_header;
    object->frame_records = other->frame_records;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0048B300", func_004918F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0048B300", func_00492010);

/**
 * @brief Copy another grid's size and settings, reallocating this grid to match.
 *
 * LibClass176EF0's copy_settings (vtable slot 0xB4).
 * @param object Grid to update.
 * @param other Grid to copy.
 */
void func_00494AE0(LibGridEmitter* object, const LibGridEmitter* other)
{
    object->cell_count = other->cell_count;
    object->columns = other->columns;
    object->resize(object->cell_count, object->columns);
    object->unk28 = other->unk28;
    object->unk30 = other->unk30;
    object->unk34 = other->unk34;
    object->unk38 = other->unk38;
    object->unk48 = other->unk48;
    object->unk4C = other->unk4C;
    object->unk4D = other->unk4D;
    object->unk4E = other->unk4E;
    object->unk4F = other->unk4F;
    object->unk50 = other->unk50;
    object->unk54 = other->unk54;
    object->unk55 = other->unk55;
    object->unk3C = other->unk3C;
    object->frame_header = other->frame_header;
    object->frame_records = other->frame_records;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0048B300", func_00494BB0);

/**
 * @brief Copy selected group histories and extend the caller's VU0 bounds.
 * @param object Receiver containing selection masks, source records, and histories.
 * @param capacity Output-record count at which processing stops before the next group.
 * @param output Destination array of three-vector records.
 * @param stamp Nonzero to copy the receiver's raw word at 0x28 into control records.
 */
void func_004952D0(LibHistoryReceiver4952D0* object, s32 capacity, LibHistoryOutput30* output, u32 stamp)
{
    s32 samples = object->samples;
    s32 index = object->index;
    s32 limit = object->limit;
    const u64* masks = object->mask->bits;
    u64 bit = (u64)1 << (index & 63);
    s32 mask_index = index / 64;
    s32 processed = 0;
    u64 mask = masks[mask_index++];
    switch (object->policy)
    {
        case 0:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource120* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource120* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource120* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource120* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource120* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource120* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource120* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                current_position->raw = *(const unsigned __int128*)previous->position.data();
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource120* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            current_position->raw = *(const unsigned __int128*)source->position.data();
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
        case 1:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource120* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource120* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource120* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource120* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource120* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource120* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource120* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_position = &current->position;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = *current_position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibHistorySource120* source = &object->source[index - 1];
                            LibQuad128* current_position = &current->position;
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = *current_position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
        case 2:
        {
            if (stamp)
            {
                u32 stamp_value = object->unk28.bits;
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            LibHistorySource120* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            LibHistorySource120* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            LibHistorySource120* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            LibHistorySource120* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            out->control.word[0] = stamp_value;
                            current_control->word[0] = stamp_value;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            output->control.word[0] = stamp_value;
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            else
            {
                switch (object->mode)
                {
                case 3:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            LibHistorySource120* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->value[3] = previous->attributes.data()[3];
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->value[3] = source->attributes.data()[3];
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            LibHistorySource120* source = &object->source[index - 1];
                            s32 history_index = index * (samples - 1) - 1;
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                float value = out->attributes.value[3];
                                value -= object->decrement * sample;
                                value = ee_max(value, 0.0f);
                                out->attributes.value[3] = value;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            out->attributes.value[3] = ee_max(out->attributes.value[3] - object->decrement, 0.0f);
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 1:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            LibHistorySource120* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                case 0:
                {
                    while (processed < capacity && index < limit)
                    {
                        u64 selected = mask & bit;
                        bit <<= 1;
                        if (!bit)
                        {
                            bit = 1;
                            mask = masks[mask_index++];
                        }
                        index++;
                        if (selected)
                        {
                            s32 history_index = index * (samples - 1) - 1;
                            LibHistorySource120* source = &object->source[index - 1];
                            LibQuad128 position;
                            position = source->position;
                            lib_normalize_vector3(position.data());
                            position.value[0] *= object->scale;
                            position.value[1] *= object->scale;
                            position.value[2] *= object->scale;
                            for (s32 sample = samples - 1; sample >= 2; sample--)
                            {
                                LibHistoryOutput30* out = &output[sample];
                                LibHistoryRecord40* current = &object->history[history_index--];
                                LibHistoryRecord40* previous = current - 1;
                                LibQuad128* current_attributes = &current->attributes;
                                out->position = position;
                                vu0_load_vf1(&out->position);
                                current_attributes->raw = *(const unsigned __int128*)previous->attributes.data();
                                out->attributes = *current_attributes;
                                LibQuad128* current_control = &current->control;
                                current_control->raw = *(const unsigned __int128*)previous->control.data();
                                out->control = *current_control;
                                ee_prefetch(previous - 1);
                                vu0_extend_bounds_vf1();
                            }
                            LibHistoryOutput30* out = &output[1];
                            LibHistoryRecord40* current = &object->history[history_index];
                            LibQuad128* current_attributes = &current->attributes;
                            out->position = position;
                            vu0_load_vf1(&out->position);
                            current_attributes->raw = *(const unsigned __int128*)source->attributes.data();
                            out->attributes = *current_attributes;
                            LibQuad128* current_control = &current->control;
                            out->control = *current_control;
                            ee_prefetch(source - 1);
                            vu0_extend_bounds_vf1();
                            processed += samples;
                            output += samples;
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0048B300", func_00497DA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0048B300", func_004984C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0048B300", func_0049AF90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0048B300", func_0049B060);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0048B300", func_0049B130);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0048B300", func_0049B200);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0048B300", func_0049B2D0);
