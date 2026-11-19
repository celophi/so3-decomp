#include "include_asm.h"
#include "overlays/1067-00/text_00293610.h"
#include "overlays/1067-00/text_0029E9E0.h"
#include "overlays/lib/text_0044ABE0.h"
#include "overlays/lib/model.h"
#include "overlays/lib/text_0046AE20.h"
#include "overlays/lib/particle_history.h"
#include "overlays/lib/row_fill.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_004CD3A0.h"
#include "vu0.h"
#include "ee.h"

extern "C" float g_frame_ticks;
extern "C" u8 g_fixed_frame_step;
extern "C" float g_frame_seconds;

extern "C" void func_428670(void* object);

extern "C" void func_426C20(void* object);

/**
 * @brief Advance a nonnegative countdown and report whether it has expired.
 * @param delay Countdown to update; negative values remain disabled.
 * @return True once the countdown reaches zero.
 */
static inline bool update_delay(float& delay)
{
    if (delay < 0.0f)
    {
        return false;
    }

    if (delay > 0.0f)
    {
        delay -= g_frame_ticks;

        if (delay > 0.0f)
        {
            return false;
        }

        delay = 0.0f;
    }

    return true;
}

// Deleting destructor; needs the recovered class hierarchy.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00293610);

// Base destructor; needs the recovered class hierarchy.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_002936D0);

s32 func_00293740(FieldClass157400* object)
{
    return 5;
}

void func_00293750(FieldClass157400* object)
{
    float previous = object->delay;

    if (update_delay(object->delay))
    {
        if (previous > 0.0f)
        {
            func_428670(object);
        }

        func_426C20(object);
    }
}

/** Type-35 grid entry with vtable D_158800 in main data that updates with a fixed time step when that's enabled. */
class FieldClass158800 : public LibClass174C20
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass158800();

    /**
     * @brief Return the entry's type code.
     * @return 35.
     */
    virtual s32 func_slot14();

    /**
     * @brief Run the base update, with a fixed 1/60 s frame time while fixed stepping is on.
     * @return The base update's result.
     */
    virtual s32 func_slot1C(LibTransform* root);
};

/**
 * @brief Run the base update, with a fixed 1/60 s frame time while fixed stepping is on.
 * @param root Model transform, passed on.
 * @return The base update's result.
 */
s32 FieldClass158800::func_slot1C(LibTransform* root)
{
    float previous = g_frame_seconds;
    u8 result;

    if (g_fixed_frame_step)
    {
        g_frame_seconds = 1.0f / 60.0f;
    }

    result = LibClass174C20::func_slot1C(root);
    g_frame_seconds = previous;
    return result;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00293840);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00293A40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00294C30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00294F20);

extern "C" FieldScalarPair293610* func_00294FD0(FieldScalarPair293610* object)
{
    object->unk00 = 5.0f;
    object->unk04 = -1;
    return object;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00294FF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295090);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295100);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295180);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_002951F0);

FieldClass157540::~FieldClass157540()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_002952E0);

/**
 * @brief Resize the grid with the default heap selected.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
extern "C" void func_00295340(FieldClass157540* object, s32 rows, s32 columns)
{
    void* heap = resident_exchange_allocation_heap(0);
    func_002A78C0(object, rows, columns);
    resident_exchange_allocation_heap(heap);
}

FieldClass157610::~FieldClass157610()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295440);

/**
 * @brief Resize the grid with the default heap selected.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
extern "C" void func_002954A0(FieldClass157610* object, s32 rows, s32 columns)
{
    void* heap = resident_exchange_allocation_heap(0);
    func_002A6910(object, rows, columns);
    resident_exchange_allocation_heap(heap);
}

FieldClass157880::~FieldClass157880()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_002955A0);

/**
 * @brief Resize the grid with the default heap selected.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
extern "C" void func_00295600(FieldClass157880* object, s32 rows, s32 columns)
{
    void* heap = resident_exchange_allocation_heap(0);
    func_002A70D0(object, rows, columns);
    resident_exchange_allocation_heap(heap);
}

FieldClass157BC0::~FieldClass157BC0()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295700);

/**
 * @brief Resize the grid with the default heap selected.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
extern "C" void func_00295760(FieldClass157BC0* object, s32 rows, s32 columns)
{
    void* heap = resident_exchange_allocation_heap(0);
    func_002A6910(object, rows, columns);
    resident_exchange_allocation_heap(heap);
}

FieldClass157F00::~FieldClass157F00()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295860);

/**
 * @brief Resize the grid with the default heap selected.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
extern "C" void func_002958C0(FieldClass157F00* object, s32 rows, s32 columns)
{
    void* heap = resident_exchange_allocation_heap(0);
    func_002A6170(object, rows, columns);
    resident_exchange_allocation_heap(heap);
}

FieldClass158240::~FieldClass158240()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_002959C0);

/**
 * @brief Resize the grid with the default heap selected.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
extern "C" void func_00295A20(FieldClass158240* object, s32 rows, s32 columns)
{
    void* heap = resident_exchange_allocation_heap(0);
    func_002A5A70(object, rows, columns);
    resident_exchange_allocation_heap(heap);
}

bool func_00295A90(FieldObject158240* object)
{
    return *object->unkA0 != 1;
}

FieldClass1584B0::~FieldClass1584B0()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295B40);

/**
 * @brief Resize the grid with the default heap selected.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
extern "C" void func_00295BA0(FieldClass1584B0* object, s32 rows, s32 columns)
{
    void* heap = resident_exchange_allocation_heap(0);
    func_002A5A70(object, rows, columns);
    resident_exchange_allocation_heap(heap);
}

bool func_00295C10(FieldObject1584B0* object)
{
    return *object->unkA0 != 1;
}


FieldClass158800::~FieldClass158800()
{
}

/**
 * @brief Return the entry's type code.
 * @return 35.
 */
s32 FieldClass158800::func_slot14()
{
    return 35;
}

/** Partial LibClass175320 with vtable D_158820 in main data. */
class FieldClass158820 : public LibClass175320
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass158820();
};

FieldClass158820::~FieldClass158820()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295D00);

extern "C" void func_00295D30(FieldVectorBuffer293610* object, u8 value, const FieldVector4* vector)
{
    if (object->unkC4 < object->unkC0)
    {
        object->unkB0[object->unkC4] = value;

        if (vector != 0)
        {
            object->unkB4[object->unkC4].packed = vector->packed;
        }

        object->unkC4++;
    }
}

void func_00295D90(FieldVectorBuffer293610* object)
{
}

bool func_00295DA0(FieldVectorBuffer293610* object)
{
    return true;
}

void func_00295DB0(FieldVectorBuffer293610* object, FieldObject175360* value)
{
    object->unkB8 = value;
}

FieldObject175360* func_00295DC0(FieldVectorBuffer293610* object)
{
    return object->unkB8;
}

void func_00295DD0(FieldVectorBuffer293610* object, FieldObject175370* value)
{
    object->unkBC = value;
}

FieldObject175370* func_00295DE0(FieldVectorBuffer293610* object)
{
    return object->unkBC;
}

void func_00295DF0(FieldObject1577B0Links* object, FieldObject175360* value)
{
    object->unkB0 = value;
}

FieldObject175360* func_00295E00(FieldObject1577B0Links* object)
{
    return object->unkB0;
}

void func_00295E10(FieldObject1577B0Links* object, FieldObject175370* value)
{
    object->unkB4 = value;
}

FieldObject175370* func_00295E20(FieldObject1577B0Links* object)
{
    return object->unkB4;
}

bool func_00295E30(FieldObject1583E0* object)
{
    return false;
}

bool func_00295E40(FieldObject158650* object)
{
    return false;
}

/**
 * @brief Copy selected group histories and extend the caller's VU0 bounds.
 * @param object Receiver containing selection masks, source records, and histories.
 * @param capacity Output-record count at which processing stops before the next group.
 * @param output Destination array of three-vector records.
 * @param stamp Nonzero to copy the receiver's raw word at 0x28 into control records.
 */
extern "C" void func_00295E50(LibHistoryReceiver441C40* object, s32 capacity, LibHistoryOutput30* output, u32 stamp)
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
                            LibHistorySource170* source = &object->source[index - 1];
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
                            LibHistorySource170* source = &object->source[index - 1];
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
                            LibHistorySource170* source = &object->source[index - 1];
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
                            LibHistorySource170* source = &object->source[index - 1];
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
                            LibHistorySource170* source = &object->source[index - 1];
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
                            LibHistorySource170* source = &object->source[index - 1];
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
                            LibHistorySource170* source = &object->source[index - 1];
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
                            LibHistorySource170* source = &object->source[index - 1];
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
                            LibHistorySource170* source = &object->source[index - 1];
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
                            LibHistorySource170* source = &object->source[index - 1];
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
                            LibHistorySource170* source = &object->source[index - 1];
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
                            LibHistorySource170* source = &object->source[index - 1];
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
                            LibHistorySource170* source = &object->source[index - 1];
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
                            LibHistorySource170* source = &object->source[index - 1];
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
                            LibHistorySource170* source = &object->source[index - 1];
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
                            LibHistorySource170* source = &object->source[index - 1];
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
                            LibHistorySource170* source = &object->source[index - 1];
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
                            LibHistorySource170* source = &object->source[index - 1];
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
                            LibHistorySource170* source = &object->source[index - 1];
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
                            LibHistorySource170* source = &object->source[index - 1];
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
                            LibHistorySource170* source = &object->source[index - 1];
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
                            LibHistorySource170* source = &object->source[index - 1];
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
                            LibHistorySource170* source = &object->source[index - 1];
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
                            LibHistorySource170* source = &object->source[index - 1];
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

/** Leading 0x140 bytes of a FieldElement2989C0. */
struct FieldElementHead2989C0
{
    u8 unk00[0x140];
};

/** Part at offset 0x140 of a FieldElement2989C0. */
struct FieldElementPart2989C0
{
    u8 unk00[0x30];
};

/** Partial 0x170-byte element whose second base starts at offset 0x140. */
struct FieldElement2989C0 : public FieldElementHead2989C0, public FieldElementPart2989C0
{
};

/** Partial owner of an element array at offset 0x14. */
struct FieldOwner2989C0
{
    u8 unk00[0x14];
    FieldElement2989C0* unk14;
};

/**
 * @brief Return an element's part at offset 0x140.
 * @param object Owner of the elements.
 * @param index Element index.
 * @return The element's part, or null when the element pointer is null.
 */
extern "C" FieldElementPart2989C0* func_002989C0(const FieldOwner2989C0* object, s32 index)
{
    return &object->unk14[index];
}

void func_002989F0(FieldObject158860* object, float value)
{
    object->unk28 = value;
}

void func_00298A00(FieldObject158860* object, float value)
{
    object->unk30 = value;
}

float func_00298A10(FieldObject158860* object)
{
    return object->unk30;
}

void func_00298A20(FieldObject158860* object, u8 value)
{
    object->unk4D = value;
}

u8 func_00298A30(FieldObject158860* object)
{
    return object->unk4D;
}

void func_00298A40(FieldObject158860* object, float value)
{
    object->unk34 = value;
}

void func_00298A50(FieldObject158860* object, u8 value)
{
    object->unk56 = value;
}

u8 func_00298A60(FieldObject158860* object)
{
    return object->unk56;
}

void func_00298A70(FieldObject158860* object, float value)
{
    object->unk44 = value;
}

float func_00298A80(FieldObject158860* object)
{
    return object->unk44;
}

float func_00298A90(FieldObject158860* object)
{
    return object->unk28;
}

/**
 * @brief Set the grid's primary linked emitter.
 * @param value Emitter to store.
 */
void FieldClass158860::set_primary_emitter(LibClass173990* value)
{
    primary_emitter = value;
}

/**
 * @brief Return the grid's primary linked emitter.
 * @return Stored emitter.
 */
LibClass173990* FieldClass158860::get_primary_emitter() const
{
    return primary_emitter;
}

/**
 * @brief Set the entry count for primary emission.
 * @param value Entry count.
 */
void FieldClass158860::set_primary_emission_count(u8 value)
{
    primary_emission_count = value;
}

/**
 * @brief Select the vectors supplied to primary emission.
 * @param value Bits selecting position, first offset, second offset and color.
 */
void FieldClass158860::set_primary_emission_flags(u8 value)
{
    primary_emission_flags = value;
}

/**
 * @brief Set the grid's secondary linked emitter.
 * @param value Emitter to store.
 */
void FieldClass158860::set_secondary_emitter(LibClass173990* value)
{
    secondary_emitter = value;
}

/**
 * @brief Return the grid's secondary linked emitter.
 * @return Stored emitter.
 */
LibClass173990* FieldClass158860::get_secondary_emitter() const
{
    return secondary_emitter;
}

/**
 * @brief Set the entry count for secondary emission.
 * @param value Entry count.
 */
void FieldClass158860::set_secondary_emission_count(u8 value)
{
    secondary_emission_count = value;
}

void func_00298B10(FieldObject158860* object, float value)
{
    object->unk3C = value;
}

/**
 * @brief Select the vectors supplied to secondary emission.
 * @param value Bits selecting position, first offset, second offset and color.
 */
void FieldClass158860::set_secondary_emission_flags(u8 value)
{
    secondary_emission_flags = value;
}

/**
 * @brief Set the scale applied to the first secondary-emission offset.
 * @param value Offset scale.
 */
void FieldClass158860::set_secondary_emission_scale(float value)
{
    secondary_emission_scale = value;
}

/**
 * @brief Bind a frame resource, skipping playback when it contains one frame.
 * @param object Grid to update.
 * @param header Frame resource header.
 * @param records Frame records containing duration values.
 */
void field_bind_grid_frame_resource(FieldObject158860* object, FieldResourceHeader273720* header, FieldResourceRecord273720* records)
{
    object->frame_header = header;
    object->frame_records = records;

    if (object->frame_header->frame_count == 1)
    {
        object->skip_frame_playback = 1;
    }
    else
    {
        object->skip_frame_playback = 0;
    }
}

/**
 * @brief Clear the frame resource bindings and select whether playback is skipped.
 * @param object Grid to update.
 * @param skip_playback Nonzero to skip frame playback.
 */
void field_clear_grid_frame_resource(FieldObject158860* object, s32 skip_playback)
{
    object->frame_header = 0;
    object->frame_records = 0;

    if (skip_playback)
    {
        object->skip_frame_playback = 1;
    }
    else
    {
        object->skip_frame_playback = 0;
    }
}

void func_00298BB0(FieldObject158860* object, float value)
{
    object->unk38 = value;
}

void func_00298BC0(FieldObject157AF0* object, const FieldVectorSource150* source)
{
    object->unk2C = 0;
    object->transform_rows[0] = source->unk150;
    object->transform_rows[1] = source->unk160;
    object->transform_rows[2] = source->unk170;
    object->transform_rows[3] = source->unk180;
}

void func_00298BF0(FieldObject157AF0* object)
{
}

/**
 * @brief Copy selected group histories and extend the caller's VU0 bounds.
 * @param object Receiver containing selection masks, source records, and histories.
 * @param capacity Output-record count at which processing stops before the next group.
 * @param output Destination array of three-vector records.
 * @param stamp Nonzero to copy the receiver's raw word at 0x28 into control records.
 */
extern "C" void func_00298C00(LibHistoryReceiver4952D0* object, s32 capacity, LibHistoryOutput30* output, u32 stamp)
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

bool func_0029B6D0(FieldObject157AF0* object)
{
    return true;
}

void* func_0029B6E0(FieldClass158D00* object, s32 index)
{
    FieldClass158A18* item = &object->unk14[index];
    void* result = item;

    if (item != 0)
    {
        result = &item->unkF0;
    }

    return result;
}

/**
 * @brief Position a row using optional linear and angular steps.
 * @param object Grid settings whose count (minus one) gives the row length.
 * @param cell Cell supplying the initial position and secondary vector.
 * @param row First element of the row.
 * @param index Nonzero to initialize each stepped element's first auxiliary value.
 * @param position_step Displacement subtracted per element, or null to copy the cell position.
 * @param angle_pair Initial two angles in radians, or null for linear stepping only.
 * @param axis_radii Initial per-axis radii used with the two angles.
 * @param angle_step Change subtracted from the two angles per element.
 * @param radius_step Change subtracted from the three radii per element.
 */
extern "C" void func_0029B710(RowFillOwner* object, RowFillCell* cell, RowFillElement* row, s32 index, const RowFillVector* position_step, const RowFillVector* angle_pair,
                         const RowFillVector* axis_radii,
                         const RowFillVector* angle_step, const RowFillVector* radius_step)
{
    if (object->secondary_emitter != 0)
    {
        cell->unk3c = object->unk3c;
    }

    bool copy_secondary_vector = false;

    if (object->unk4d != 1 && object->unk4d != 3)
    {
        copy_secondary_vector = true;
    }

    if (position_step != 0)
    {
        if (angle_pair != 0)
        {
            const RowFillCell* source_cell = cell;
            RowFillVector position;
            RowFillVector radii;
            RowFillVector angles;
            LibVector4 second_trig;
            LibVector4 first_trig;
            s32 count = object->unk10 - 1;
            angles.packed = angle_pair->packed;
            radii.packed = axis_radii->packed;
            lib_compute_sine_cosine_pair(&first_trig, angles.floats[0]);
            lib_compute_sine_cosine_pair(&second_trig, angles.floats[1]);
            float previous_x = first_trig.z * (radii.floats[0] * second_trig.z);
            float previous_y = radii.floats[1] * first_trig.w;
            float previous_z = first_trig.z * (radii.floats[2] * second_trig.w);
            position.packed = source_cell->position().packed;
            position.floats[3] = 1.0f;

            for (s32 i = 0; i < count; i++)
            {
                angles.floats[0] -= angle_step->floats[0];
                angles.floats[1] -= angle_step->floats[1];
                radii.floats[0] -= radius_step->floats[0];
                radii.floats[1] -= radius_step->floats[1];
                radii.floats[2] -= radius_step->floats[2];
                lib_compute_sine_cosine_pair(&first_trig, angles.floats[0]);
                lib_compute_sine_cosine_pair(&second_trig, angles.floats[1]);
                float x = first_trig.z * (radii.floats[0] * second_trig.z);
                position.floats[0] += x - previous_x;
                previous_x = x;
                float y = radii.floats[1] * first_trig.w;
                position.floats[1] += y - previous_y;
                previous_y = y;
                float z = first_trig.z * (radii.floats[2] * second_trig.w);
                position.floats[2] += z - previous_z;
                previous_z = z;
                position.floats[0] -= position_step->floats[0];
                position.floats[1] -= position_step->floats[1];
                position.floats[2] -= position_step->floats[2];
                row->unk10.packed = position.packed;

                if (copy_secondary_vector)
                {
                    row->unk20 = source_cell->unk20;
                }

                row->unk30.packed = 0;

                if (index != 0)
                {
                    row->unk30.floats[0] = object->unk28;
                }

                row++;
            }
        }
        else
        {
            s32 count = object->unk10 - 1;
            RowFillVector position;
            position.packed = cell->position().packed;

            for (s32 i = 0; i < count; i++)
            {
                position.floats[0] -= position_step->floats[0];
                position.floats[1] -= position_step->floats[1];
                position.floats[2] -= position_step->floats[2];
                row->unk10.packed = position.packed;

                if (copy_secondary_vector)
                {
                    row->unk20 = cell->unk20;
                }

                row->unk30.packed = 0;

                if (index != 0)
                {
                    row->unk30.floats[0] = object->unk28;
                }

                row++;
            }
        }
    }
    else
    {
        s32 count = object->unk10 - 1;

        for (s32 i = 0; i < count; i++)
        {
            row->unk10 = cell->position();

            if (copy_secondary_vector)
            {
                row->unk20 = cell->unk20;
            }

            row->unk30.packed = 0;
            row++;
        }
    }
}

/**
 * @brief Fill a row of secondary elements from a cell (or an explicit vector).
 * @param object Grid owning the row.
 * @param cell Cell whose vectors are copied.
 * @param row First secondary element of the row.
 * @param index Unused.
 * @param source Vector copied to each element, or null to use the cell's.
 */
extern "C" void func_0029BB20(FieldClass157AF0* object, FieldClass158A18* cell, FieldClass154E60* row, s32 index, const FieldVector4* source)
{
    if (object->secondary_emitter != 0)
    {
        cell->unk3C = object->unk3C;
    }

    bool blend = false;

    if (object->unk4D != 1 && object->unk4D != 3)
    {
        blend = true;
    }

    s32 count = object->unk10 - 1;

    if (source == 0)
    {
        for (s32 i = 0; i < count; i++)
        {
            row->unk10 = cell->position();

            if (blend)
            {
                row->unk20 = cell->unk20;
            }

            row->unk30.packed = 0;
            row++;
        }
    }
    else
    {
        for (s32 i = 0; i < count; i++)
        {
            row->unk10 = *source;

            if (blend)
            {
                row->unk20 = cell->unk20;
            }

            row->unk30.packed = 0;
            row++;
        }
    }
}

void func_0029BC20(FieldObject157AF0* object, float value)
{
    object->unk28 = value;
}

void func_0029BC30(FieldObject157AF0* object, float value)
{
    object->unk30 = value;
}

float func_0029BC40(const FieldObject157AF0* object)
{
    return object->unk30;
}

void func_0029BC50(FieldObject157AF0* object, u8 value)
{
    object->unk4D = value;
}

u8 func_0029BC60(const FieldObject157AF0* object)
{
    return object->unk4D;
}

void func_0029BC70(FieldObject157AF0* object, float value)
{
    object->unk34 = value;
}

void func_0029BC80(FieldObject157AF0* object, u8 value)
{
    object->unk56 = value;
}

u8 func_0029BC90(const FieldObject157AF0* object)
{
    return object->unk56;
}

void func_0029BCA0(FieldObject157AF0* object, float value)
{
    object->unk44 = value;
}

float func_0029BCB0(const FieldObject157AF0* object)
{
    return object->unk44;
}

float func_0029BCC0(const FieldObject157AF0* object)
{
    return object->unk28;
}

/**
 * @brief Set the grid's primary linked emitter.
 * @param value Emitter to store.
 */
void FieldClass157AF0::set_primary_emitter(LibClass173990* value)
{
    primary_emitter = value;
}

/**
 * @brief Return the grid's primary linked emitter.
 * @return Stored emitter.
 */
LibClass173990* FieldClass157AF0::get_primary_emitter() const
{
    return primary_emitter;
}

/**
 * @brief Set the number of entries generated by primary emission.
 * @param value Entry count.
 */
void FieldClass157AF0::set_primary_emission_count(u8 value)
{
    primary_emission_count = value;
}

/**
 * @brief Set the optional inputs supplied to primary emission.
 * @param value Input flags.
 */
void FieldClass157AF0::set_primary_emission_flags(u8 value)
{
    primary_emission_flags = value;
}

/**
 * @brief Set the grid's secondary linked emitter.
 * @param value Emitter to store.
 */
void FieldClass157AF0::set_secondary_emitter(LibClass173990* value)
{
    secondary_emitter = value;
}

/**
 * @brief Return the grid's secondary linked emitter.
 * @return Stored emitter.
 */
LibClass173990* FieldClass157AF0::get_secondary_emitter() const
{
    return secondary_emitter;
}

/**
 * @brief Set the number of entries generated by secondary emission.
 * @param value Entry count.
 */
void FieldClass157AF0::set_secondary_emission_count(u8 value)
{
    secondary_emission_count = value;
}

void func_0029BD40(FieldObject157AF0* object, float value)
{
    object->unk3C = value;
}

/**
 * @brief Set the optional inputs supplied to secondary emission.
 * @param value Input flags.
 */
void FieldClass157AF0::set_secondary_emission_flags(u8 value)
{
    secondary_emission_flags = value;
}

/**
 * @brief Set the scale applied to the first secondary-emission offset.
 * @param value Offset scale.
 */
void FieldClass157AF0::set_secondary_emission_scale(float value)
{
    secondary_emission_scale = value;
}

void func_0029BD70(FieldObject157AF0* object, u8* header, FieldResourceRecord273720* records)
{
    object->unkA0 = header;
    object->unkA4 = records;

    if (*object->unkA0 == 1)
    {
        object->unk57 = 1;
    }
    else
    {
        object->unk57 = 0;
    }
}

void func_0029BDB0(FieldObject157AF0* object, s32 enabled)
{
    object->unkA0 = 0;
    object->unkA4 = 0;

    if (enabled)
    {
        object->unk57 = 1;
    }
    else
    {
        object->unk57 = 0;
    }
}

void func_0029BDE0(FieldObject157AF0* object, float value)
{
    object->unk38 = value;
}

void func_0029BDF0(FieldObject157AF0* object, FieldObject175360* value)
{
}

FieldObject175360* func_0029BE00(FieldObject157AF0* object)
{
    return 0;
}

void func_0029BE10(FieldObject157AF0* object, FieldObject175370* value)
{
}

FieldObject175370* func_0029BE20(FieldObject157AF0* object)
{
    return 0;
}

void func_0029BE30(FieldObject157BC0* object, const FieldVectorSource150* source)
{
    object->unk2C = 0;
    object->transform_rows[0] = source->unk150;
    object->transform_rows[1] = source->unk160;
    object->transform_rows[2] = source->unk170;
    object->transform_rows[3] = source->unk180;
}

void func_0029BE60(void* object)
{
}

/**
 * @brief Copy selected group histories and extend the caller's VU0 bounds.
 * @param object Receiver containing selection masks, source records, and histories.
 * @param capacity Output-record count at which processing stops before the next group.
 * @param output Destination array of three-vector records.
 * @param stamp Nonzero to copy the receiver's raw word at 0x28 into control records.
 */
extern "C" void func_0029BE70(LibHistoryReceiver48ECB0* object, s32 capacity, LibHistoryOutput30* output, u32 stamp)
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
