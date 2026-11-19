#include "include_asm.h"
#include "overlays/lib/particle_grid.h"
#include "overlays/lib/particle_history.h"
#include "overlays/lib/text_004CD3A0.h"
#include "vu0.h"
#include "ee.h"
#include "overlays/lib/grid_frame.h"
#include "overlays/lib/grid_frame_vu0.h"
#include "main/resident_data.h"

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
    object->primary_emitter = other->primary_emitter;
    object->unk4C = other->unk4C;
    object->unk4D = other->unk4D;
    object->primary_emission_flags = other->primary_emission_flags;
    object->primary_emission_count = other->primary_emission_count;
    object->secondary_emitter = other->secondary_emitter;
    object->secondary_emission_flags = other->secondary_emission_flags;
    object->secondary_emission_count = other->secondary_emission_count;
    object->unk3C = other->unk3C;
    object->frame_header = other->frame_header;
    object->frame_records = other->frame_records;
}

/**
 * @brief Advance active cells' frame vectors and playback state into an output batch.
 * @param object Grid owning the cells and frame resource.
 * @param capacity Output-entry budget, counted in steps of the grid column count.
 * @param output Output records, with each cell written at the start of its row.
 * @param preserve_row_vector Nonzero to retain the saved xyz components in the first row element.
 */
extern "C" void func_0048B3D0(GridOwner0048B3D0* object, s32 capacity, GridOutputRecord* output, s32 preserve_row_vector)
{
    s32 columns = object->unk10;
    s32 index = object->unk2C;
    s32 cells = object->unk0C;
    u64* words = object->unk1C->unk08;
    u64 mask = (u64)1 << (index & 63);
    s32 word_index = index / 64;
    u64 active_word = words[word_index++];

    if (object->skip_frame_playback != 0)
    {
        s32 consumed = 0;
        vu0_set_grid_frame_delta(g_frame_seconds);

        if (columns == 1)
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;

                mask <<= 1;

                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }

                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_0048B3D0(&object->unk14[index]);
                vu0_load_grid_frame_vectors(&state->value, &state->rate);
                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
        else
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;
                GridFrameVector* previous;

                mask <<= 1;

                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }

                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_0048B3D0(&object->unk14[index]);
                previous = &object->unk20[index * (columns - 1)].unk30;

                if (preserve_row_vector == 0)
                {
                    previous->packed = state->value.packed;
                }

                vu0_load_grid_frame_vectors(&state->value, &state->rate);
                previous->components.frame_index = 0;
                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
    }
    else
    {
        s32 consumed = 0;
        s32 frame_count = object->frame_header->frame_count;
        s32 loop_mode = object->frame_header->loop_mode;
        s32 boundary_limit = (s32)object->unk30;
        float frame_seconds = 1.0f / 60.0f;
        vu0_set_grid_frame_delta(g_frame_seconds);

        if (columns == 1)
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;
                GridFrameState* frame;
                s32 frame_index;

                mask <<= 1;

                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }

                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_0048B3D0(&object->unk14[index]);
                frame = &state->frame;

                if (object->unk4C == 4 && boundary_limit < frame->boundary_count)
                {
                    grid_clear_cell_bit(object->unk1C, index);
                    index++;
                    continue;
                }

                frame->remaining_time -= g_frame_seconds;
                frame_index = frame->frame_index;
                vu0_load_grid_frame_vectors(&state->value, &state->rate);

                while (frame->remaining_time <= 0.0f)
                {
                    frame_index += frame->reverse != 0 ? -1 : 1;

                    if (frame_index >= frame_count)
                    {
                        switch (loop_mode)
                        {
                            case 0:
                                frame_index = 0;
                                break;
                            case 1:
                                frame->reverse = 1;
                                frame_index--;
                                break;
                            case 2:
                                frame_index--;
                                break;
                        }

                        frame->boundary_count++;
                    }
                    else if (frame_index < 0)
                    {
                        frame->reverse = 0;
                        frame_index = 0;
                        frame->boundary_count++;
                    }

                    frame->frame_index = frame_index;
                    frame->remaining_time += frame_seconds * object->frame_records[frame_index].duration_frames;
                }

                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                output->frame_vector.components.frame_index = frame_index;
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
        else
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;
                GridFrameState* frame;
                GridFrameVector* previous;
                s32 frame_index;

                mask <<= 1;

                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }

                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_0048B3D0(&object->unk14[index]);
                frame = &state->frame;

                if (object->unk4C == 4 && boundary_limit < frame->boundary_count)
                {
                    grid_clear_cell_bit(object->unk1C, index);
                    index++;
                    continue;
                }

                frame->remaining_time -= g_frame_seconds;
                frame_index = frame->frame_index;
                previous = &object->unk20[index * (columns - 1)].unk30;

                if (preserve_row_vector == 0)
                {
                    previous->packed = state->value.packed;
                }

                previous->components.frame_index = frame_index;
                vu0_load_grid_frame_vectors(&state->value, &state->rate);

                while (frame->remaining_time <= 0.0f)
                {
                    frame_index += frame->reverse != 0 ? -1 : 1;

                    if (frame_index >= frame_count)
                    {
                        switch (loop_mode)
                        {
                            case 0:
                                frame_index = 0;
                                break;
                            case 1:
                                frame->reverse = 1;
                                frame_index--;
                                break;
                            case 2:
                                frame_index--;
                                break;
                        }

                        frame->boundary_count++;
                    }
                    else if (frame_index < 0)
                    {
                        frame->reverse = 0;
                        frame_index = 0;
                        frame->boundary_count++;
                    }

                    frame->frame_index = frame_index;
                    frame->remaining_time += frame_seconds * object->frame_records[frame_index].duration_frames;
                }

                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                output->frame_vector.components.frame_index = frame_index;
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
    }
}

/**
 * @brief Copy selected group histories and extend the caller's VU0 bounds.
 * @param object Receiver containing selection masks, source records, and histories.
 * @param capacity Output-record count at which processing stops before the next group.
 * @param output Destination array of three-vector records.
 * @param stamp Nonzero to copy the receiver's raw word at 0x28 into control records.
 */
extern "C" void func_0048BAB0(LibHistoryReceiver48BAB0* object, s32 capacity, LibHistoryOutput30* output, u32 stamp)
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
                            LibHistorySource80* source = &object->source[index - 1];
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
                            LibHistorySource80* source = &object->source[index - 1];
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
                            LibHistorySource80* source = &object->source[index - 1];
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
                            LibHistorySource80* source = &object->source[index - 1];
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
                            LibHistorySource80* source = &object->source[index - 1];
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
                            LibHistorySource80* source = &object->source[index - 1];
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
                            LibHistorySource80* source = &object->source[index - 1];
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
                            LibHistorySource80* source = &object->source[index - 1];
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
                            LibHistorySource80* source = &object->source[index - 1];
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
                            LibHistorySource80* source = &object->source[index - 1];
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
                            LibHistorySource80* source = &object->source[index - 1];
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
                            LibHistorySource80* source = &object->source[index - 1];
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
                            LibHistorySource80* source = &object->source[index - 1];
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
                            LibHistorySource80* source = &object->source[index - 1];
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
                            LibHistorySource80* source = &object->source[index - 1];
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
                            LibHistorySource80* source = &object->source[index - 1];
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
                            LibHistorySource80* source = &object->source[index - 1];
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
                            LibHistorySource80* source = &object->source[index - 1];
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
                            LibHistorySource80* source = &object->source[index - 1];
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
                            LibHistorySource80* source = &object->source[index - 1];
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
                            LibHistorySource80* source = &object->source[index - 1];
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
                            LibHistorySource80* source = &object->source[index - 1];
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
                            LibHistorySource80* source = &object->source[index - 1];
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
                            LibHistorySource80* source = &object->source[index - 1];
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
    object->primary_emitter = other->primary_emitter;
    object->unk4C = other->unk4C;
    object->unk4D = other->unk4D;
    object->primary_emission_flags = other->primary_emission_flags;
    object->primary_emission_count = other->primary_emission_count;
    object->secondary_emitter = other->secondary_emitter;
    object->secondary_emission_flags = other->secondary_emission_flags;
    object->secondary_emission_count = other->secondary_emission_count;
    object->unk3C = other->unk3C;
    object->frame_header = other->frame_header;
    object->frame_records = other->frame_records;
}

/**
 * @brief Clear an active cell bit.
 * @param object Bit set owning the storage.
 * @param index Unsigned cell index.
 */
static inline void lib_clear_grid_cell_bit(LibGridBitset* object, u32 index)
{
    u32 word_index = index >> 6;
    u64 keep_mask = ~((u64)1 << (index & 63));
    object->bits[word_index] &= keep_mask;
}

/**
 * @brief Advance active cells' frame vectors and playback state into an output batch.
 * @param object Grid owning the cells and frame resource.
 * @param capacity Output-entry budget, counted in steps of the grid column count.
 * @param output Output records, with each cell written at the start of its row.
 * @param preserve_row_vector Nonzero to retain the saved xyz components in the first secondary element.
 */
extern "C" void func_0048E550(LibGridReceiver48E550* object, s32 capacity, LibGridOutputRecord* output, s32 preserve_row_vector)
{
    s32 columns = object->columns;
    s32 index = object->index;
    s32 cells = object->cell_count;
    u64* words = object->active->bits;
    u64 mask = (u64)1 << (index & 63);
    s32 word_index = index / 64;
    u64 active_word = words[word_index++];

    if (object->skip_frame_playback != 0)
    {
        s32 consumed = 0;
        vu0_set_grid_frame_delta(g_frame_seconds);

        if (columns == 1)
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                mask <<= 1;

                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }

                if (active == 0)
                {
                    index++;
                    continue;
                }

                LibGridFrameMotion* state = &object->cells[index];

                vu0_load_grid_frame_vectors(&state->value, &state->rate);
                index++;
                ee_prefetch(&object->cells[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
        else
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                mask <<= 1;

                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }

                if (active == 0)
                {
                    index++;
                    continue;
                }

                LibGridFrameMotion* state = &object->cells[index];

                LibGridFrameVector* previous = &object->rows[index * (columns - 1)].unk30;

                if (preserve_row_vector == 0)
                {
                    previous->packed = state->value.packed;
                }

                vu0_load_grid_frame_vectors(&state->value, &state->rate);
                previous->components.frame_index = 0;
                index++;
                ee_prefetch(&object->cells[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
    }
    else
    {
        s32 consumed = 0;
        s32 frame_count = object->frame_header->frame_count;
        s32 loop_mode = object->frame_header->loop_mode;
        s32 boundary_limit = (s32)object->unk30;
        float frame_seconds = 1.0f / 60.0f;
        vu0_set_grid_frame_delta(g_frame_seconds);

        if (columns == 1)
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                mask <<= 1;

                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }

                if (active == 0)
                {
                    index++;
                    continue;
                }

                LibGridFrameMotion* state = &object->cells[index];

                LibGridFrameState* frame = &state->frame;

                if (object->unk4C == 4 && boundary_limit < frame->boundary_count)
                {
                    lib_clear_grid_cell_bit(object->active, index);
                    index++;
                    continue;
                }

                frame->remaining_time -= g_frame_seconds;

                s32 frame_index = frame->frame_index;
                vu0_load_grid_frame_vectors(&state->value, &state->rate);

                while (frame->remaining_time <= 0.0f)
                {
                    frame_index += frame->reverse != 0 ? -1 : 1;

                    if (frame_index >= frame_count)
                    {
                        switch (loop_mode)
                        {
                        case LIB_GRID_FRAME_WRAP:
                            frame_index = 0;
                            break;
                        case LIB_GRID_FRAME_PING_PONG:
                            frame->reverse = 1;
                            frame_index--;
                            break;
                        case LIB_GRID_FRAME_HOLD_LAST:
                            frame_index--;
                            break;
                        }

                        frame->boundary_count++;
                    }
                    else if (frame_index < 0)
                    {
                        frame->reverse = 0;
                        frame_index = 0;
                        frame->boundary_count++;
                    }

                    frame->frame_index = frame_index;
                    frame->remaining_time += frame_seconds * object->frame_records[frame_index].duration_frames;
                }

                index++;
                ee_prefetch(&object->cells[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                output->frame_vector.components.frame_index = frame_index;
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
        else
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                mask <<= 1;

                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }

                if (active == 0)
                {
                    index++;
                    continue;
                }

                LibGridFrameMotion* state = &object->cells[index];

                LibGridFrameState* frame = &state->frame;

                if (object->unk4C == 4 && boundary_limit < frame->boundary_count)
                {
                    lib_clear_grid_cell_bit(object->active, index);
                    index++;
                    continue;
                }

                frame->remaining_time -= g_frame_seconds;

                s32 frame_index = frame->frame_index;
                LibGridFrameVector* previous = &object->rows[index * (columns - 1)].unk30;

                if (preserve_row_vector == 0)
                {
                    previous->packed = state->value.packed;
                }

                previous->components.frame_index = frame_index;
                vu0_load_grid_frame_vectors(&state->value, &state->rate);

                while (frame->remaining_time <= 0.0f)
                {
                    frame_index += frame->reverse != 0 ? -1 : 1;

                    if (frame_index >= frame_count)
                    {
                        switch (loop_mode)
                        {
                        case LIB_GRID_FRAME_WRAP:
                            frame_index = 0;
                            break;
                        case LIB_GRID_FRAME_PING_PONG:
                            frame->reverse = 1;
                            frame_index--;
                            break;
                        case LIB_GRID_FRAME_HOLD_LAST:
                            frame_index--;
                            break;
                        }

                        frame->boundary_count++;
                    }
                    else if (frame_index < 0)
                    {
                        frame->reverse = 0;
                        frame_index = 0;
                        frame->boundary_count++;
                    }

                    frame->frame_index = frame_index;
                    frame->remaining_time += frame_seconds * object->frame_records[frame_index].duration_frames;
                }

                index++;
                ee_prefetch(&object->cells[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                output->frame_vector.components.frame_index = frame_index;
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
    }
}

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
    object->primary_emitter = other->primary_emitter;
    object->unk4C = other->unk4C;
    object->unk4D = other->unk4D;
    object->primary_emission_flags = other->primary_emission_flags;
    object->primary_emission_count = other->primary_emission_count;
    object->secondary_emitter = other->secondary_emitter;
    object->secondary_emission_flags = other->secondary_emission_flags;
    object->secondary_emission_count = other->secondary_emission_count;
    object->unk3C = other->unk3C;
    object->frame_header = other->frame_header;
    object->frame_records = other->frame_records;
}

/**
 * @brief Advance active cells' frame vectors and playback state into an output batch.
 * @param object Grid owning the cells and frame resource.
 * @param capacity Output-entry budget, counted in steps of the grid column count.
 * @param output Output records, with each cell written at the start of its row.
 * @param preserve_row_vector Nonzero to retain the saved xyz components in the first row element.
 */
extern "C" void func_004918F0(GridOwner004918F0* object, s32 capacity, GridOutputRecord* output, s32 preserve_row_vector)
{
    s32 columns = object->unk10;
    s32 index = object->unk2C;
    s32 cells = object->unk0C;
    u64* words = object->unk1C->unk08;
    u64 mask = (u64)1 << (index & 63);
    s32 word_index = index / 64;
    u64 active_word = words[word_index++];

    if (object->skip_frame_playback != 0)
    {
        s32 consumed = 0;
        vu0_set_grid_frame_delta(g_frame_seconds);

        if (columns == 1)
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;

                mask <<= 1;

                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }

                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_004918F0(&object->unk14[index]);
                vu0_load_grid_frame_vectors(&state->value, &state->rate);
                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
        else
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;
                GridFrameVector* previous;

                mask <<= 1;

                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }

                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_004918F0(&object->unk14[index]);
                previous = &object->unk20[index * (columns - 1)].unk30;

                if (preserve_row_vector == 0)
                {
                    previous->packed = state->value.packed;
                }

                vu0_load_grid_frame_vectors(&state->value, &state->rate);
                previous->components.frame_index = 0;
                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
    }
    else
    {
        s32 consumed = 0;
        s32 frame_count = object->frame_header->frame_count;
        s32 loop_mode = object->frame_header->loop_mode;
        s32 boundary_limit = (s32)object->unk30;
        float frame_seconds = 1.0f / 60.0f;
        vu0_set_grid_frame_delta(g_frame_seconds);

        if (columns == 1)
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;
                GridFrameState* frame;
                s32 frame_index;

                mask <<= 1;

                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }

                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_004918F0(&object->unk14[index]);
                frame = &state->frame;

                if (object->unk4C == 4 && boundary_limit < frame->boundary_count)
                {
                    grid_clear_cell_bit(object->unk1C, index);
                    index++;
                    continue;
                }

                frame->remaining_time -= g_frame_seconds;
                frame_index = frame->frame_index;
                vu0_load_grid_frame_vectors(&state->value, &state->rate);

                while (frame->remaining_time <= 0.0f)
                {
                    frame_index += frame->reverse != 0 ? -1 : 1;

                    if (frame_index >= frame_count)
                    {
                        switch (loop_mode)
                        {
                            case 0:
                                frame_index = 0;
                                break;
                            case 1:
                                frame->reverse = 1;
                                frame_index--;
                                break;
                            case 2:
                                frame_index--;
                                break;
                        }

                        frame->boundary_count++;
                    }
                    else if (frame_index < 0)
                    {
                        frame->reverse = 0;
                        frame_index = 0;
                        frame->boundary_count++;
                    }

                    frame->frame_index = frame_index;
                    frame->remaining_time += frame_seconds * object->frame_records[frame_index].duration_frames;
                }

                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                output->frame_vector.components.frame_index = frame_index;
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
        else
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;
                GridFrameState* frame;
                GridFrameVector* previous;
                s32 frame_index;

                mask <<= 1;

                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }

                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_004918F0(&object->unk14[index]);
                frame = &state->frame;

                if (object->unk4C == 4 && boundary_limit < frame->boundary_count)
                {
                    grid_clear_cell_bit(object->unk1C, index);
                    index++;
                    continue;
                }

                frame->remaining_time -= g_frame_seconds;
                frame_index = frame->frame_index;
                previous = &object->unk20[index * (columns - 1)].unk30;

                if (preserve_row_vector == 0)
                {
                    previous->packed = state->value.packed;
                }

                previous->components.frame_index = frame_index;
                vu0_load_grid_frame_vectors(&state->value, &state->rate);

                while (frame->remaining_time <= 0.0f)
                {
                    frame_index += frame->reverse != 0 ? -1 : 1;

                    if (frame_index >= frame_count)
                    {
                        switch (loop_mode)
                        {
                            case 0:
                                frame_index = 0;
                                break;
                            case 1:
                                frame->reverse = 1;
                                frame_index--;
                                break;
                            case 2:
                                frame_index--;
                                break;
                        }

                        frame->boundary_count++;
                    }
                    else if (frame_index < 0)
                    {
                        frame->reverse = 0;
                        frame_index = 0;
                        frame->boundary_count++;
                    }

                    frame->frame_index = frame_index;
                    frame->remaining_time += frame_seconds * object->frame_records[frame_index].duration_frames;
                }

                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                output->frame_vector.components.frame_index = frame_index;
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
    }
}

/**
 * @brief Copy selected group histories and extend the caller's VU0 bounds.
 * @param object Receiver containing selection masks, source records, and histories.
 * @param capacity Output-record count at which processing stops before the next group.
 * @param output Destination array of three-vector records.
 * @param stamp Nonzero to copy the receiver's raw word at 0x28 into control records.
 */
extern "C" void func_00492010(LibHistoryReceiver492010* object, s32 capacity, LibHistoryOutput30* output, u32 stamp)
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
                            LibHistorySourceF0* source = &object->source[index - 1];
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
                            LibHistorySourceF0* source = &object->source[index - 1];
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
                            LibHistorySourceF0* source = &object->source[index - 1];
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
                            LibHistorySourceF0* source = &object->source[index - 1];
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
                            LibHistorySourceF0* source = &object->source[index - 1];
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
                            LibHistorySourceF0* source = &object->source[index - 1];
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
                            LibHistorySourceF0* source = &object->source[index - 1];
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
                            LibHistorySourceF0* source = &object->source[index - 1];
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
                            LibHistorySourceF0* source = &object->source[index - 1];
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
                            LibHistorySourceF0* source = &object->source[index - 1];
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
                            LibHistorySourceF0* source = &object->source[index - 1];
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
                            LibHistorySourceF0* source = &object->source[index - 1];
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
                            LibHistorySourceF0* source = &object->source[index - 1];
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
                            LibHistorySourceF0* source = &object->source[index - 1];
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
                            LibHistorySourceF0* source = &object->source[index - 1];
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
                            LibHistorySourceF0* source = &object->source[index - 1];
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
                            LibHistorySourceF0* source = &object->source[index - 1];
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
                            LibHistorySourceF0* source = &object->source[index - 1];
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
                            LibHistorySourceF0* source = &object->source[index - 1];
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
                            LibHistorySourceF0* source = &object->source[index - 1];
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
                            LibHistorySourceF0* source = &object->source[index - 1];
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
                            LibHistorySourceF0* source = &object->source[index - 1];
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
                            LibHistorySourceF0* source = &object->source[index - 1];
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
                            LibHistorySourceF0* source = &object->source[index - 1];
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
    object->primary_emitter = other->primary_emitter;
    object->unk4C = other->unk4C;
    object->unk4D = other->unk4D;
    object->primary_emission_flags = other->primary_emission_flags;
    object->primary_emission_count = other->primary_emission_count;
    object->secondary_emitter = other->secondary_emitter;
    object->secondary_emission_flags = other->secondary_emission_flags;
    object->secondary_emission_count = other->secondary_emission_count;
    object->unk3C = other->unk3C;
    object->frame_header = other->frame_header;
    object->frame_records = other->frame_records;
}

/**
 * @brief Advance active cells' frame vectors and playback state into an output batch.
 * @param object Grid owning the cells and frame resource.
 * @param capacity Output-entry budget, counted in steps of the grid column count.
 * @param output Output records, with each cell written at the start of its row.
 * @param preserve_row_vector Nonzero to retain the saved xyz components in the first row element.
 */
extern "C" void func_00494BB0(GridOwner00494BB0* object, s32 capacity, GridOutputRecord* output, s32 preserve_row_vector)
{
    s32 columns = object->unk10;
    s32 index = object->unk2C;
    s32 cells = object->unk0C;
    u64* words = object->unk1C->unk08;
    u64 mask = (u64)1 << (index & 63);
    s32 word_index = index / 64;
    u64 active_word = words[word_index++];

    if (object->skip_frame_playback != 0)
    {
        s32 consumed = 0;
        vu0_set_grid_frame_delta(g_frame_seconds);

        if (columns == 1)
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;

                mask <<= 1;

                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }

                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_00494BB0(&object->unk14[index]);
                vu0_load_grid_frame_vectors(&state->value, &state->rate);
                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
        else
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;
                GridFrameVector* previous;

                mask <<= 1;

                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }

                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_00494BB0(&object->unk14[index]);
                previous = &object->unk20[index * (columns - 1)].unk30;

                if (preserve_row_vector == 0)
                {
                    previous->packed = state->value.packed;
                }

                vu0_load_grid_frame_vectors(&state->value, &state->rate);
                previous->components.frame_index = 0;
                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
    }
    else
    {
        s32 consumed = 0;
        s32 frame_count = object->frame_header->frame_count;
        s32 loop_mode = object->frame_header->loop_mode;
        s32 boundary_limit = (s32)object->unk30;
        float frame_seconds = 1.0f / 60.0f;
        vu0_set_grid_frame_delta(g_frame_seconds);

        if (columns == 1)
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;
                GridFrameState* frame;
                s32 frame_index;

                mask <<= 1;

                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }

                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_00494BB0(&object->unk14[index]);
                frame = &state->frame;

                if (object->unk4C == 4 && boundary_limit < frame->boundary_count)
                {
                    grid_clear_cell_bit(object->unk1C, index);
                    index++;
                    continue;
                }

                frame->remaining_time -= g_frame_seconds;
                frame_index = frame->frame_index;
                vu0_load_grid_frame_vectors(&state->value, &state->rate);

                while (frame->remaining_time <= 0.0f)
                {
                    frame_index += frame->reverse != 0 ? -1 : 1;

                    if (frame_index >= frame_count)
                    {
                        switch (loop_mode)
                        {
                            case 0:
                                frame_index = 0;
                                break;
                            case 1:
                                frame->reverse = 1;
                                frame_index--;
                                break;
                            case 2:
                                frame_index--;
                                break;
                        }

                        frame->boundary_count++;
                    }
                    else if (frame_index < 0)
                    {
                        frame->reverse = 0;
                        frame_index = 0;
                        frame->boundary_count++;
                    }

                    frame->frame_index = frame_index;
                    frame->remaining_time += frame_seconds * object->frame_records[frame_index].duration_frames;
                }

                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                output->frame_vector.components.frame_index = frame_index;
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
        else
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;
                GridFrameState* frame;
                GridFrameVector* previous;
                s32 frame_index;

                mask <<= 1;

                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }

                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_00494BB0(&object->unk14[index]);
                frame = &state->frame;

                if (object->unk4C == 4 && boundary_limit < frame->boundary_count)
                {
                    grid_clear_cell_bit(object->unk1C, index);
                    index++;
                    continue;
                }

                frame->remaining_time -= g_frame_seconds;
                frame_index = frame->frame_index;
                previous = &object->unk20[index * (columns - 1)].unk30;

                if (preserve_row_vector == 0)
                {
                    previous->packed = state->value.packed;
                }

                previous->components.frame_index = frame_index;
                vu0_load_grid_frame_vectors(&state->value, &state->rate);

                while (frame->remaining_time <= 0.0f)
                {
                    frame_index += frame->reverse != 0 ? -1 : 1;

                    if (frame_index >= frame_count)
                    {
                        switch (loop_mode)
                        {
                            case 0:
                                frame_index = 0;
                                break;
                            case 1:
                                frame->reverse = 1;
                                frame_index--;
                                break;
                            case 2:
                                frame_index--;
                                break;
                        }

                        frame->boundary_count++;
                    }
                    else if (frame_index < 0)
                    {
                        frame->reverse = 0;
                        frame_index = 0;
                        frame->boundary_count++;
                    }

                    frame->frame_index = frame_index;
                    frame->remaining_time += frame_seconds * object->frame_records[frame_index].duration_frames;
                }

                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                output->frame_vector.components.frame_index = frame_index;
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
    }
}

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

/**
 * @brief Advance active cells' frame vectors and playback state into an output batch.
 * @param object Grid owning the cells and frame resource.
 * @param capacity Output-entry budget, counted in steps of the grid column count.
 * @param output Output records, with each cell written at the start of its row.
 * @param preserve_row_vector Nonzero to retain the saved xyz components in the first row element.
 */
extern "C" void func_00497DA0(GridOwner00497DA0* object, s32 capacity, GridOutputRecord* output, s32 preserve_row_vector)
{
    s32 columns = object->unk10;
    s32 index = object->unk2C;
    s32 cells = object->unk0C;
    u64* words = object->unk1C->unk08;
    u64 mask = (u64)1 << (index & 63);
    s32 word_index = index / 64;
    u64 active_word = words[word_index++];

    if (object->skip_frame_playback != 0)
    {
        s32 consumed = 0;
        vu0_set_grid_frame_delta(g_frame_seconds);

        if (columns == 1)
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;

                mask <<= 1;

                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }

                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_00497DA0(&object->unk14[index]);
                vu0_load_grid_frame_vectors(&state->value, &state->rate);
                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
        else
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;
                GridFrameVector* previous;

                mask <<= 1;

                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }

                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_00497DA0(&object->unk14[index]);
                previous = &object->unk20[index * (columns - 1)].unk30;

                if (preserve_row_vector == 0)
                {
                    previous->packed = state->value.packed;
                }

                vu0_load_grid_frame_vectors(&state->value, &state->rate);
                previous->components.frame_index = 0;
                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
    }
    else
    {
        s32 consumed = 0;
        s32 frame_count = object->frame_header->frame_count;
        s32 loop_mode = object->frame_header->loop_mode;
        s32 boundary_limit = (s32)object->unk30;
        float frame_seconds = 1.0f / 60.0f;
        vu0_set_grid_frame_delta(g_frame_seconds);

        if (columns == 1)
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;
                GridFrameState* frame;
                s32 frame_index;

                mask <<= 1;

                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }

                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_00497DA0(&object->unk14[index]);
                frame = &state->frame;

                if (object->unk4C == 4 && boundary_limit < frame->boundary_count)
                {
                    grid_clear_cell_bit(object->unk1C, index);
                    index++;
                    continue;
                }

                frame->remaining_time -= g_frame_seconds;
                frame_index = frame->frame_index;
                vu0_load_grid_frame_vectors(&state->value, &state->rate);

                while (frame->remaining_time <= 0.0f)
                {
                    frame_index += frame->reverse != 0 ? -1 : 1;

                    if (frame_index >= frame_count)
                    {
                        switch (loop_mode)
                        {
                            case 0:
                                frame_index = 0;
                                break;
                            case 1:
                                frame->reverse = 1;
                                frame_index--;
                                break;
                            case 2:
                                frame_index--;
                                break;
                        }

                        frame->boundary_count++;
                    }
                    else if (frame_index < 0)
                    {
                        frame->reverse = 0;
                        frame_index = 0;
                        frame->boundary_count++;
                    }

                    frame->frame_index = frame_index;
                    frame->remaining_time += frame_seconds * object->frame_records[frame_index].duration_frames;
                }

                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                output->frame_vector.components.frame_index = frame_index;
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
        else
        {
            while (consumed < capacity && index < cells)
            {
                u64 active = active_word & mask;
                GridFrameMotion* state;
                GridFrameState* frame;
                GridFrameVector* previous;
                s32 frame_index;

                mask <<= 1;

                if (mask == 0)
                {
                    mask = 1;
                    active_word = words[word_index++];
                }

                if (active == 0)
                {
                    index++;
                    continue;
                }

                state = grid_cell_motion_00497DA0(&object->unk14[index]);
                frame = &state->frame;

                if (object->unk4C == 4 && boundary_limit < frame->boundary_count)
                {
                    grid_clear_cell_bit(object->unk1C, index);
                    index++;
                    continue;
                }

                frame->remaining_time -= g_frame_seconds;
                frame_index = frame->frame_index;
                previous = &object->unk20[index * (columns - 1)].unk30;

                if (preserve_row_vector == 0)
                {
                    previous->packed = state->value.packed;
                }

                previous->components.frame_index = frame_index;
                vu0_load_grid_frame_vectors(&state->value, &state->rate);

                while (frame->remaining_time <= 0.0f)
                {
                    frame_index += frame->reverse != 0 ? -1 : 1;

                    if (frame_index >= frame_count)
                    {
                        switch (loop_mode)
                        {
                            case 0:
                                frame_index = 0;
                                break;
                            case 1:
                                frame->reverse = 1;
                                frame_index--;
                                break;
                            case 2:
                                frame_index--;
                                break;
                        }

                        frame->boundary_count++;
                    }
                    else if (frame_index < 0)
                    {
                        frame->reverse = 0;
                        frame_index = 0;
                        frame->boundary_count++;
                    }

                    frame->frame_index = frame_index;
                    frame->remaining_time += frame_seconds * object->frame_records[frame_index].duration_frames;
                }

                index++;
                ee_prefetch(&object->unk14[index]);
                vu0_advance_grid_frame_vector();
                consumed += columns;
                vu0_store_grid_frame_vector(&output->frame_vector);
                output->frame_vector.components.frame_index = frame_index;
                vu0_store_grid_frame_vector(&state->value);
                output += columns;
            }
        }
    }
}

/**
 * @brief Copy selected group histories and extend the caller's VU0 bounds.
 * @param object Receiver containing selection masks, source records, and histories.
 * @param capacity Output-record count at which processing stops before the next group.
 * @param output Destination array of three-vector records.
 * @param stamp Nonzero to copy the receiver's raw word at 0x28 into control records.
 */
extern "C" void func_004984C0(LibHistoryReceiver4984C0* object, s32 capacity, LibHistoryOutput30* output, u32 stamp)
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
                            LibHistorySource140* source = &object->source[index - 1];
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
                            LibHistorySource140* source = &object->source[index - 1];
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
                            LibHistorySource140* source = &object->source[index - 1];
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
                            LibHistorySource140* source = &object->source[index - 1];
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
                            LibHistorySource140* source = &object->source[index - 1];
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
                            LibHistorySource140* source = &object->source[index - 1];
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
                            LibHistorySource140* source = &object->source[index - 1];
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
                            LibHistorySource140* source = &object->source[index - 1];
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
                            LibHistorySource140* source = &object->source[index - 1];
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
                            LibHistorySource140* source = &object->source[index - 1];
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
                            LibHistorySource140* source = &object->source[index - 1];
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
                            LibHistorySource140* source = &object->source[index - 1];
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
                            LibHistorySource140* source = &object->source[index - 1];
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
                            LibHistorySource140* source = &object->source[index - 1];
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
                            LibHistorySource140* source = &object->source[index - 1];
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
                            LibHistorySource140* source = &object->source[index - 1];
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
                            LibHistorySource140* source = &object->source[index - 1];
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
                            LibHistorySource140* source = &object->source[index - 1];
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
                            LibHistorySource140* source = &object->source[index - 1];
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
                            LibHistorySource140* source = &object->source[index - 1];
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
                            LibHistorySource140* source = &object->source[index - 1];
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
                            LibHistorySource140* source = &object->source[index - 1];
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
                            LibHistorySource140* source = &object->source[index - 1];
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
                            LibHistorySource140* source = &object->source[index - 1];
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
 * @brief Test a history source's bit.
 * @param mask Active-source mask.
 * @param index Source index.
 * @return The bit.
 */
static inline u64 history_source_active(const LibHistoryMask* mask, u32 index)
{
    u32 bit = index & 63;
    return (mask->bits[index >> 6] >> bit) & 1;
}

/**
 * @brief Copy the active 0x30-byte sources' position and attributes into an output batch, growing the vf26/vf27 bounds.
 * @param object Receiver; its index moves past every source looked at.
 * @param capacity Output budget, counted in steps of the receiver's sample count.
 * @param output Output records, one per sample.
 * @return Entries used.
 */
extern "C" s32 func_0049AF90(LibHistoryReceiver43EA10* object, s32 capacity, LibHistoryOutput30* output)
{
    s32 processed = 0;

    while (processed < capacity && object->index < object->limit)
    {
        if (!history_source_active(object->mask, object->index))
        {
            object->index++;
            continue;
        }

        LibHistorySource30* source = &object->source[object->index];
        output->position = source->position;
        vu0_load_vf1(&output->position);
        output->attributes.raw = *(const unsigned __int128*)source->attributes.data();
        vu0_extend_bounds_vf1();
        object->index++;
        output += object->samples;
        processed += object->samples;
    }

    return processed;
}

/**
 * @brief Copy the active 0x60-byte sources' position and attributes into an output batch, growing the vf26/vf27 bounds.
 * @param object Receiver; its index moves past every source looked at.
 * @param capacity Output budget, counted in steps of the receiver's sample count.
 * @param output Output records, one per sample.
 * @return Entries used.
 */
extern "C" s32 func_0049B060(LibHistoryReceiver43EA10* object, s32 capacity, LibHistoryOutput30* output)
{
    s32 processed = 0;

    while (processed < capacity && object->index < object->limit)
    {
        if (!history_source_active(object->mask, object->index))
        {
            object->index++;
            continue;
        }

        LibHistorySource60* source = &((LibHistorySource60*)object->source)[object->index];
        output->position = source->position;
        vu0_load_vf1(&output->position);
        output->attributes.raw = *(const unsigned __int128*)source->attributes.data();
        vu0_extend_bounds_vf1();
        object->index++;
        output += object->samples;
        processed += object->samples;
    }

    return processed;
}

/**
 * @brief Copy the active 0x30-byte sources' position and attributes, with the receiver's unk28 as the control w, into an output batch.
 * @param object Receiver; its index moves past every source looked at.
 * @param capacity Output budget, counted in steps of the receiver's sample count.
 * @param output Output records, one per sample.
 * @return Entries used.
 */
extern "C" s32 func_0049B130(LibHistoryReceiver43EA10* object, s32 capacity, LibHistoryOutput30* output)
{
    s32 processed = 0;

    while (processed < capacity && object->index < object->limit)
    {
        if (!history_source_active(object->mask, object->index))
        {
            object->index++;
            continue;
        }

        LibHistorySource30* source = &object->source[object->index];
        output->position = source->position;
        vu0_load_vf1(&output->position);
        output->attributes.raw = *(const unsigned __int128*)source->attributes.data();
        vu0_extend_bounds_vf1();
        output->control.value[3] = object->unk28.value;
        output += object->samples;
        object->index++;
        processed += object->samples;
    }

    return processed;
}

/**
 * @brief Copy the active 0x60-byte sources' position and attributes, with the receiver's unk28 as the control w, into an output batch.
 * @param object Receiver; its index moves past every source looked at.
 * @param capacity Output budget, counted in steps of the receiver's sample count.
 * @param output Output records, one per sample.
 * @return Entries used.
 */
extern "C" s32 func_0049B200(LibHistoryReceiver43EA10* object, s32 capacity, LibHistoryOutput30* output)
{
    s32 processed = 0;

    while (processed < capacity && object->index < object->limit)
    {
        if (!history_source_active(object->mask, object->index))
        {
            object->index++;
            continue;
        }

        LibHistorySource60* source = &((LibHistorySource60*)object->source)[object->index];
        output->position = source->position;
        vu0_load_vf1(&output->position);
        output->attributes.raw = *(const unsigned __int128*)source->attributes.data();
        vu0_extend_bounds_vf1();
        output->control.value[3] = object->unk28.value;
        output += object->samples;
        object->index++;
        processed += object->samples;
    }

    return processed;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0048B300", func_0049B2D0);
