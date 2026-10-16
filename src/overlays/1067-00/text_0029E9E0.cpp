#include "include_asm.h"
#include "overlays/1067-00/field_class_154D40.h"
#include "overlays/1067-00/text_0029E9E0.h"
#include "main/resident_data.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/emission_vu0.h"
#include "overlays/1067-00/grid_frame_vu0.h"
#include "ee.h"

static inline void field_clear_grid_cell_bit(FieldBitset154E80* object, u32 index);

bool func_0029E9E0(FieldObject157BC0* object)
{
    return true;
}

/** Leading 0x80 bytes of a FieldElement29E9F0. */
struct FieldElementHead29E9F0
{
    u8 unk00[0x80];
};

/** Part at offset 0x80 of a FieldElement29E9F0. */
struct FieldElementPart29E9F0
{
    u8 unk00[0x30];
};

/** Partial 0xB0-byte element whose second base starts at offset 0x80. */
struct FieldElement29E9F0 : public FieldElementHead29E9F0, public FieldElementPart29E9F0
{
};

/** Partial owner of an element array at offset 0x14. */
struct FieldOwner29E9F0
{
    u8 unk00[0x14];
    FieldElement29E9F0* unk14;
};

/**
 * @brief Return an element's part at offset 0x80.
 * @param object Owner of the elements.
 * @param index Element index.
 * @return The element's part, or null when the element pointer is null.
 */
extern "C" FieldElementPart29E9F0* func_0029E9F0(const FieldOwner29E9F0* object, s32 index)
{
    return &object->unk14[index];
}

/**
 * @brief Position a secondary row using optional linear and angular steps.
 * @param object Grid owning the row.
 * @param cell Cell supplying the initial position and secondary vector.
 * @param row First secondary element of the row.
 * @param index Nonzero to initialize each stepped element's first auxiliary value.
 * @param position_step Displacement subtracted per element, or null to copy the cell position.
 * @param angle_pair Initial two angles in radians, or null for linear stepping only.
 * @param axis_radii Initial per-axis radii used with the two angles.
 * @param angle_step Change subtracted from the two angles per element.
 * @param radius_step Change subtracted from the three radii per element.
 */
void field_position_secondary_row_157e30(FieldClass157E30* object, FieldClass158A38* cell, FieldClass154E60* row, s32 index,
                                         const FieldVector4* position_step, const FieldVector4* angle_pair, const FieldVector4* axis_radii,
                                         const FieldVector4* angle_step, const FieldVector4* radius_step)
{
    if (object->secondary_emitter != 0)
    {
        cell->unk3C = object->unk3C;
    }

    bool copy_secondary_vector = false;

    if (object->unk4D != 1 && object->unk4D != 3)
    {
        copy_secondary_vector = true;
    }

    if (position_step != 0)
    {
        if (angle_pair != 0)
        {
            const FieldClass158A38* source_cell = cell;
            FieldVector4 position;
            FieldVector4 radii;
            FieldVector4 angles;
            LibVector4 second_trig;
            LibVector4 first_trig;
            s32 count = object->unk10 - 1;
            angles.packed = angle_pair->packed;
            radii.packed = axis_radii->packed;
            lib_compute_sine_cosine_pair(&first_trig, angles.floats[0]);
            lib_compute_sine_cosine_pair(&second_trig, angles.floats[1]);
            float previous_x = first_trig.components[2] * (radii.floats[0] * second_trig.components[2]);
            float previous_y = radii.floats[1] * first_trig.components[3];
            float previous_z = first_trig.components[2] * (radii.floats[2] * second_trig.components[3]);
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
                float x = first_trig.components[2] * (radii.floats[0] * second_trig.components[2]);
                position.floats[0] += x - previous_x;
                previous_x = x;
                float y = radii.floats[1] * first_trig.components[3];
                position.floats[1] += y - previous_y;
                previous_y = y;
                float z = first_trig.components[2] * (radii.floats[2] * second_trig.components[3]);
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
            FieldVector4 position;
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
void func_0029EE30(FieldClass157E30* object, FieldClass158A38* cell, FieldClass154E60* row, s32 index, const FieldVector4* source)
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

void func_0029EF30(FieldObject157BC0* object, float value)
{
    object->unk28 = value;
}

void func_0029EF40(FieldObject157BC0* object, float value)
{
    object->unk30 = value;
}

float func_0029EF50(FieldObject157BC0* object)
{
    return object->unk30;
}

void func_0029EF60(FieldObject157BC0* object, u8 value)
{
    object->unk4D = value;
}

u8 func_0029EF70(FieldObject157BC0* object)
{
    return object->unk4D;
}

void func_0029EF80(FieldObject157BC0* object, float value)
{
    object->unk34 = value;
}

void func_0029EF90(FieldObject157BC0* object, u8 value)
{
    object->unk56 = value;
}

u8 func_0029EFA0(FieldObject157BC0* object)
{
    return object->unk56;
}

void func_0029EFB0(FieldObject157BC0* object, float value)
{
    object->unk44 = value;
}

float func_0029EFC0(FieldObject157BC0* object)
{
    return object->unk44;
}

float func_0029EFD0(FieldObject157BC0* object)
{
    return object->unk28;
}

/**
 * @brief Set the grid's primary linked emitter.
 * @param object Grid to update.
 * @param value Emitter to store.
 */
void field_set_primary_emitter_157e30(FieldObject157BC0* object, LibClass173990* value)
{
    object->primary_emitter = value;
}

/**
 * @brief Return the grid's primary linked emitter.
 * @param object Grid to inspect.
 * @return Stored emitter.
 */
LibClass173990* field_primary_emitter_157e30(FieldObject157BC0* object)
{
    return object->primary_emitter;
}

/**
 * @brief Set the number of entries generated by primary emission.
 * @param object Grid to update.
 * @param value Entry count.
 */
void field_set_primary_emission_count_157e30(FieldObject157BC0* object, u8 value)
{
    object->primary_emission_count = value;
}

/**
 * @brief Set the optional inputs supplied to primary emission.
 * @param object Grid to update.
 * @param value Input flags.
 */
void field_set_primary_emission_flags_157e30(FieldObject157BC0* object, u8 value)
{
    object->primary_emission_flags = value;
}

/**
 * @brief Set the grid's secondary linked emitter.
 * @param object Grid to update.
 * @param value Emitter to store.
 */
void field_set_secondary_emitter_157e30(FieldObject157BC0* object, LibClass173990* value)
{
    object->secondary_emitter = value;
}

/**
 * @brief Return the grid's secondary linked emitter.
 * @param object Grid to inspect.
 * @return Stored emitter.
 */
LibClass173990* field_secondary_emitter_157e30(FieldObject157BC0* object)
{
    return object->secondary_emitter;
}

/**
 * @brief Set the number of entries generated by secondary emission.
 * @param object Grid to update.
 * @param value Entry count.
 */
void field_set_secondary_emission_count_157e30(FieldObject157BC0* object, u8 value)
{
    object->secondary_emission_count = value;
}

void func_0029F050(FieldObject157BC0* object, float value)
{
    object->unk3C = value;
}

/**
 * @brief Set the optional inputs supplied to secondary emission.
 * @param object Grid to update.
 * @param value Input flags.
 */
void field_set_secondary_emission_flags_157e30(FieldObject157BC0* object, u8 value)
{
    object->secondary_emission_flags = value;
}

/**
 * @brief Set the scale applied to the first secondary-emission offset.
 * @param object Grid to update.
 * @param value Offset scale.
 */
void field_set_secondary_emission_scale_157e30(FieldObject157BC0* object, float value)
{
    object->secondary_emission_scale = value;
}

/**
 * @brief Bind the resource bytes and records and set the mode from byte zero.
 * @param object Receiver to update.
 * @param header Resource header bytes.
 * @param records Resource records to bind.
 */
void func_0029F080(FieldObject157BC0* object, u8* header, FieldResourceRecord273720* records)
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

/** Partial receiver with two cleared words and a flag byte. */
struct FieldReset29F0C0
{
    u8 unk00[0x57];
    u8 unk57;
    u8 unk58[0x48];
    s32 unkA0;
    s32 unkA4;
};

/**
 * @brief Clear the words at offsets 0xA0 and 0xA4 and store whether the flag is set.
 * @param object Receiver.
 * @param flag Nonzero to set the byte at offset 0x57.
 */
extern "C" void func_0029F0C0(FieldReset29F0C0* object, s32 flag)
{
    object->unkA0 = 0;
    object->unkA4 = 0;
    if (flag)
    {
        object->unk57 = 1;
    }
    else
    {
        object->unk57 = 0;
    }
}

void func_0029F0F0(FieldObject157BC0* object, float value)
{
    object->unk38 = value;
}

void func_0029F100(void* object)
{
}

s32 func_0029F110(void* object)
{
    return 0;
}

void func_0029F120(void* object)
{
}

s32 func_0029F130(void* object)
{
    return 0;
}

/**
 * @brief Clear the index and copy four aligned values from the source.
 * @param object Receiver to update.
 * @param source Source of the four aligned values.
 */
void func_0029F140(FieldObject157BC0* object, const FieldVectorSource150* source)
{
    object->unk2C = 0;
    object->transform_rows[0] = source->unk150;
    object->transform_rows[1] = source->unk160;
    object->transform_rows[2] = source->unk170;
    object->transform_rows[3] = source->unk180;
}

void func_0029F170(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_0029F180);

bool func_002A1C50(FieldObject157F00* object)
{
    return true;
}

/** Leading 0x60 bytes of a FieldElement2A1C60. */
struct FieldElementHead2A1C60
{
    u8 unk00[0x60];
};

/** Part at offset 0x60 of a FieldElement2A1C60. */
struct FieldElementPart2A1C60
{
    u8 unk00[0x30];
};

/** Partial 0x90-byte element whose second base starts at offset 0x60. */
struct FieldElement2A1C60 : public FieldElementHead2A1C60, public FieldElementPart2A1C60
{
};

/** Partial owner of an element array at offset 0x14. */
struct FieldOwner2A1C60
{
    u8 unk00[0x14];
    FieldElement2A1C60* unk14;
};

/**
 * @brief Return an element's part at offset 0x60.
 * @param object Owner of the elements.
 * @param index Element index.
 * @return The element's part, or null when the element pointer is null.
 */
extern "C" FieldElementPart2A1C60* func_002A1C60(const FieldOwner2A1C60* object, s32 index)
{
    return &object->unk14[index];
}

/**
 * @brief Position a secondary row using optional linear and angular steps.
 * @param object Grid owning the row.
 * @param cell Cell supplying the initial position and secondary vector.
 * @param row First secondary element of the row.
 * @param index Nonzero to initialize each stepped element's first auxiliary value.
 * @param position_step Displacement subtracted per element, or null to copy the cell position.
 * @param angle_pair Initial two angles in radians, or null for linear stepping only.
 * @param axis_radii Initial per-axis radii used with the two angles.
 * @param angle_step Change subtracted from the two angles per element.
 * @param radius_step Change subtracted from the three radii per element.
 */
void field_position_secondary_row_158170(FieldClass158170* object, FieldClass158A58* cell, FieldClass154E60* row, s32 index,
                                         const FieldVector4* position_step, const FieldVector4* angle_pair, const FieldVector4* axis_radii,
                                         const FieldVector4* angle_step, const FieldVector4* radius_step)
{
    if (object->secondary_emitter != 0)
    {
        cell->unk3C = object->unk3C;
    }

    bool copy_secondary_vector = false;

    if (object->unk4D != 1 && object->unk4D != 3)
    {
        copy_secondary_vector = true;
    }

    if (position_step != 0)
    {
        if (angle_pair != 0)
        {
            const FieldClass158A58* source_cell = cell;
            FieldVector4 position;
            FieldVector4 radii;
            FieldVector4 angles;
            LibVector4 second_trig;
            LibVector4 first_trig;
            s32 count = object->unk10 - 1;
            angles.packed = angle_pair->packed;
            radii.packed = axis_radii->packed;
            lib_compute_sine_cosine_pair(&first_trig, angles.floats[0]);
            lib_compute_sine_cosine_pair(&second_trig, angles.floats[1]);
            float previous_x = first_trig.components[2] * (radii.floats[0] * second_trig.components[2]);
            float previous_y = radii.floats[1] * first_trig.components[3];
            float previous_z = first_trig.components[2] * (radii.floats[2] * second_trig.components[3]);
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
                float x = first_trig.components[2] * (radii.floats[0] * second_trig.components[2]);
                position.floats[0] += x - previous_x;
                previous_x = x;
                float y = radii.floats[1] * first_trig.components[3];
                position.floats[1] += y - previous_y;
                previous_y = y;
                float z = first_trig.components[2] * (radii.floats[2] * second_trig.components[3]);
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
            FieldVector4 position;
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
void func_002A20A0(FieldClass158170* object, FieldClass158A58* cell, FieldClass154E60* row, s32 index, const FieldVector4* source)
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

void func_002A21A0(FieldObject157F00* object, float value)
{
    object->unk28 = value;
}

void func_002A21B0(FieldObject157F00* object, float value)
{
    object->unk30 = value;
}

float func_002A21C0(FieldObject157F00* object)
{
    return object->unk30;
}

void func_002A21D0(FieldObject157F00* object, u8 value)
{
    object->unk4D = value;
}

u8 func_002A21E0(FieldObject157F00* object)
{
    return object->unk4D;
}

void func_002A21F0(FieldObject157F00* object, float value)
{
    object->unk34 = value;
}

void func_002A2200(FieldObject157F00* object, u8 value)
{
    object->unk56 = value;
}

u8 func_002A2210(FieldObject157F00* object)
{
    return object->unk56;
}

void func_002A2220(FieldObject157F00* object, float value)
{
    object->unk44 = value;
}

float func_002A2230(FieldObject157F00* object)
{
    return object->unk44;
}

float func_002A2240(FieldObject157F00* object)
{
    return object->unk28;
}

/**
 * @brief Set the grid's primary linked emitter.
 * @param object Grid to update.
 * @param value Emitter to store.
 */
void field_set_primary_emitter_158170(FieldObject157F00* object, LibClass173990* value)
{
    object->primary_emitter = value;
}

/**
 * @brief Return the grid's primary linked emitter.
 * @param object Grid to inspect.
 * @return Stored emitter.
 */
LibClass173990* field_primary_emitter_158170(FieldObject157F00* object)
{
    return object->primary_emitter;
}

/**
 * @brief Set the number of entries generated by primary emission.
 * @param object Grid to update.
 * @param value Entry count.
 */
void field_set_primary_emission_count_158170(FieldObject157F00* object, u8 value)
{
    object->primary_emission_count = value;
}

/**
 * @brief Set the optional inputs supplied to primary emission.
 * @param object Grid to update.
 * @param value Input flags.
 */
void field_set_primary_emission_flags_158170(FieldObject157F00* object, u8 value)
{
    object->primary_emission_flags = value;
}

/**
 * @brief Set the grid's secondary linked emitter.
 * @param object Grid to update.
 * @param value Emitter to store.
 */
void field_set_secondary_emitter_158170(FieldObject157F00* object, LibClass173990* value)
{
    object->secondary_emitter = value;
}

/**
 * @brief Return the grid's secondary linked emitter.
 * @param object Grid to inspect.
 * @return Stored emitter.
 */
LibClass173990* field_secondary_emitter_158170(FieldObject157F00* object)
{
    return object->secondary_emitter;
}

/**
 * @brief Set the number of entries generated by secondary emission.
 * @param object Grid to update.
 * @param value Entry count.
 */
void field_set_secondary_emission_count_158170(FieldObject157F00* object, u8 value)
{
    object->secondary_emission_count = value;
}

void func_002A22C0(FieldObject157F00* object, float value)
{
    object->unk3C = value;
}

/**
 * @brief Set the optional inputs supplied to secondary emission.
 * @param object Grid to update.
 * @param value Input flags.
 */
void field_set_secondary_emission_flags_158170(FieldObject157F00* object, u8 value)
{
    object->secondary_emission_flags = value;
}

/**
 * @brief Set the scale applied to the first secondary-emission offset.
 * @param object Grid to update.
 * @param value Offset scale.
 */
void field_set_secondary_emission_scale_158170(FieldObject157F00* object, float value)
{
    object->secondary_emission_scale = value;
}

/**
 * @brief Bind the resource bytes and records and set the mode from byte zero.
 * @param object Receiver to update.
 * @param header Resource header bytes.
 * @param records Resource records to bind.
 */
void func_002A22F0(FieldObject157F00* object, u8* header, FieldResourceRecord273720* records)
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

/**
 * @brief Clear the words at offsets 0xA0 and 0xA4 and store whether the flag is set.
 * @param object Receiver.
 * @param flag Nonzero to set the byte at offset 0x57.
 */
extern "C" void func_002A2330(FieldReset29F0C0* object, s32 flag)
{
    object->unkA0 = 0;
    object->unkA4 = 0;
    if (flag)
    {
        object->unk57 = 1;
    }
    else
    {
        object->unk57 = 0;
    }
}

/**
 * @brief Store the floating-point value at offset 0x38.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A2360(FieldObject157F00* object, float value)
{
    object->unk38 = value;
}

void func_002A2370(void* object)
{
}

s32 func_002A2380(void* object)
{
    return 0;
}

void func_002A2390(void* object)
{
}

s32 func_002A23A0(void* object)
{
    return 0;
}

/**
 * @brief Clear the index and copy four aligned values from the source.
 * @param object Receiver to update.
 * @param source Source of the four aligned values.
 */
void func_002A23B0(FieldObject157F00* object, const FieldVectorSource150* source)
{
    object->unk2C = 0;
    object->transform_rows[0] = source->unk150;
    object->transform_rows[1] = source->unk160;
    object->transform_rows[2] = source->unk170;
    object->transform_rows[3] = source->unk180;
}

void func_002A23E0(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A23F0);

/**
 * @brief Report the default enabled callback state.
 * @param object Object being queried.
 * @return Always true.
 */
bool func_002A4EC0(FieldObject158240* object)
{
    return true;
}

/** Leading 0x30 bytes of a FieldElement2A4ED0. */
struct FieldElementHead2A4ED0
{
    u8 unk00[0x30];
};

/** Part at offset 0x30 of a FieldElement2A4ED0. */
struct FieldElementPart2A4ED0
{
    u8 unk00[0x30];
};

/** Partial 0x30-byte element whose second base starts at offset 0x30. */
struct FieldElement2A4ED0 : public FieldElementHead2A4ED0, public FieldElementPart2A4ED0
{
};

/** Partial owner of an element array at offset 0x14. */
struct FieldOwner2A4ED0
{
    u8 unk00[0x14];
    FieldElement2A4ED0* unk14;
};

/**
 * @brief Return an element's part at offset 0x30.
 * @param object Owner of the elements.
 * @param index Element index.
 * @return The element's part, or null when the element pointer is null.
 */
extern "C" FieldElementPart2A4ED0* func_002A4ED0(const FieldOwner2A4ED0* object, s32 index)
{
    return &object->unk14[index];
}

/**
 * @brief Position a secondary row using optional linear and angular steps.
 * @param object Grid owning the row.
 * @param cell Cell supplying the initial position and secondary vector.
 * @param row First secondary element of the row.
 * @param index Nonzero to initialize each stepped element's first auxiliary value.
 * @param position_step Displacement subtracted per element, or null to copy the cell position.
 * @param angle_pair Initial two angles in radians, or null for linear stepping only.
 * @param axis_radii Initial per-axis radii used with the two angles.
 * @param angle_step Change subtracted from the two angles per element.
 * @param radius_step Change subtracted from the three radii per element.
 */
void field_position_secondary_row_158720(FieldClass158720* object, FieldClass158A78* cell, FieldClass154E60* row, s32 index,
                                         const FieldVector4* position_step, const FieldVector4* angle_pair, const FieldVector4* axis_radii,
                                         const FieldVector4* angle_step, const FieldVector4* radius_step)
{
    if (object->unk50 != 0)
    {
        cell->unk3C = object->unk3C;
    }

    bool copy_secondary_vector = false;

    if (object->unk4D != 1 && object->unk4D != 3)
    {
        copy_secondary_vector = true;
    }

    if (position_step != 0)
    {
        if (angle_pair != 0)
        {
            const FieldClass158A78* source_cell = cell;
            FieldVector4 position;
            FieldVector4 radii;
            FieldVector4 angles;
            LibVector4 second_trig;
            LibVector4 first_trig;
            s32 count = object->unk10 - 1;
            angles.packed = angle_pair->packed;
            radii.packed = axis_radii->packed;
            lib_compute_sine_cosine_pair(&first_trig, angles.floats[0]);
            lib_compute_sine_cosine_pair(&second_trig, angles.floats[1]);
            float previous_x = first_trig.components[2] * (radii.floats[0] * second_trig.components[2]);
            float previous_y = radii.floats[1] * first_trig.components[3];
            float previous_z = first_trig.components[2] * (radii.floats[2] * second_trig.components[3]);
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
                float x = first_trig.components[2] * (radii.floats[0] * second_trig.components[2]);
                position.floats[0] += x - previous_x;
                previous_x = x;
                float y = radii.floats[1] * first_trig.components[3];
                position.floats[1] += y - previous_y;
                previous_y = y;
                float z = first_trig.components[2] * (radii.floats[2] * second_trig.components[3]);
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
            FieldVector4 position;
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
void func_002A5310(FieldClass158720* object, FieldClass158A78* cell, FieldClass154E60* row, s32 index, const FieldVector4* source)
{
    if (object->unk50 != 0)
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

/**
 * @brief Store the floating-point value at offset 0x28.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5410(FieldObject158240* object, float value)
{
    object->unk28 = value;
}

/**
 * @brief Store the floating-point value at offset 0x30.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5420(FieldObject158240* object, float value)
{
    object->unk30 = value;
}

/**
 * @brief Read the floating-point value at offset 0x30.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_002A5430(FieldObject158240* object)
{
    return object->unk30;
}

/**
 * @brief Store the byte state at offset 0x4D.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5440(FieldObject158240* object, u8 value)
{
    object->unk4D = value;
}

/**
 * @brief Read the byte state at offset 0x4D.
 * @param object Object to inspect.
 * @return Stored value.
 */
u8 func_002A5450(FieldObject158240* object)
{
    return object->unk4D;
}

/**
 * @brief Store the floating-point value at offset 0x34.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5460(FieldObject158240* object, float value)
{
    object->unk34 = value;
}

/**
 * @brief Store the byte state at offset 0x56.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5470(FieldObject158240* object, u8 value)
{
    object->unk56 = value;
}

/**
 * @brief Read the byte state at offset 0x56.
 * @param object Object to inspect.
 * @return Stored value.
 */
u8 func_002A5480(FieldObject158240* object)
{
    return object->unk56;
}

/**
 * @brief Store the floating-point value at offset 0x44.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5490(FieldObject158240* object, float value)
{
    object->unk44 = value;
}

/**
 * @brief Read the floating-point value at offset 0x44.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_002A54A0(FieldObject158240* object)
{
    return object->unk44;
}

/**
 * @brief Read the floating-point value at offset 0x28.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_002A54B0(FieldObject158240* object)
{
    return object->unk28;
}

/** Partial receiver with a word at offset 0x48. */
struct FieldWord002A54C0
{
    u8 unk00[0x48];
    s32 unk48;
};

/** @brief Store a word at offset 0x48. @param object Receiver. @param value Word to store. */
extern "C" void func_002A54C0(FieldWord002A54C0* object, s32 value)
{
    object->unk48 = value;
}

/** Partial receiver with a word at offset 0x48. */
struct FieldWord002A54D0
{
    u8 unk00[0x48];
    s32 unk48;
};

/** @brief Return the word at offset 0x48. @param object Receiver. @return Stored word. */
extern "C" s32 func_002A54D0(const FieldWord002A54D0* object)
{
    return object->unk48;
}

/**
 * @brief Store the byte state at offset 0x4F.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A54E0(FieldObject158240* object, u8 value)
{
    object->unk4F = value;
}

/**
 * @brief Store the byte state at offset 0x4E.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A54F0(FieldObject158240* object, u8 value)
{
    object->unk4E = value;
}

/** Partial receiver with a word at offset 0x50. */
struct FieldWord002A5500
{
    u8 unk00[0x50];
    s32 unk50;
};

/** @brief Store a word at offset 0x50. @param object Receiver. @param value Word to store. */
extern "C" void func_002A5500(FieldWord002A5500* object, s32 value)
{
    object->unk50 = value;
}

/** Partial receiver with a word at offset 0x50. */
struct FieldWord002A5510
{
    u8 unk00[0x50];
    s32 unk50;
};

/** @brief Return the word at offset 0x50. @param object Receiver. @return Stored word. */
extern "C" s32 func_002A5510(const FieldWord002A5510* object)
{
    return object->unk50;
}

/**
 * @brief Store the byte state at offset 0x55.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5520(FieldObject158240* object, u8 value)
{
    object->unk55 = value;
}

/**
 * @brief Store the floating-point value at offset 0x3C.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5530(FieldObject158240* object, float value)
{
    object->unk3C = value;
}

/**
 * @brief Store the byte state at offset 0x54.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5540(FieldObject158240* object, u8 value)
{
    object->unk54 = value;
}

/**
 * @brief Store the floating-point value at offset 0x40.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5550(FieldObject158240* object, float value)
{
    object->unk40 = value;
}

/**
 * @brief Bind the resource bytes and records and set the mode from byte zero.
 * @param object Receiver to update.
 * @param header Resource header bytes.
 * @param records Resource records to bind.
 */
void func_002A5560(FieldObject158240* object, u8* header, FieldResourceRecord273720* records)
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

/**
 * @brief Clear the words at offsets 0xA0 and 0xA4 and store whether the flag is set.
 * @param object Receiver.
 * @param flag Nonzero to set the byte at offset 0x57.
 */
extern "C" void func_002A55A0(FieldReset29F0C0* object, s32 flag)
{
    object->unkA0 = 0;
    object->unkA4 = 0;
    if (flag)
    {
        object->unk57 = 1;
    }
    else
    {
        object->unk57 = 0;
    }
}

/**
 * @brief Store the floating-point value at offset 0x38.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A55D0(FieldObject158240* object, float value)
{
    object->unk38 = value;
}

void func_002A55E0(void* object)
{
}

s32 func_002A55F0(void* object)
{
    return 0;
}

void func_002A5600(void* object)
{
}

s32 func_002A5610(void* object)
{
    return 0;
}

/**
 * @brief Get an indexed primary array element.
 * @param object Object owning the array.
 * @param index Signed element index.
 * @return Address of the indexed element.
 */
FieldClass1589F8* func_002A5620(FieldClass158DD0* object, s32 index)
{
    return &object->unk14[index];
}

/**
 * @brief Get an element from a secondary array row.
 * @param object Object owning the array.
 * @param row Signed primary element index.
 * @param column Signed index within its secondary row.
 * @return Address of the indexed secondary element.
 */
FieldObject154E60* func_002A5640(FieldClass158DD0* object, s32 row, s32 column)
{
    return &object->unk20[row * (object->unk10 - 1) + column];
}

/**
 * @brief Get the associated bitset object.
 * @param object Object to query.
 * @return Stored value.
 */
FieldBitset154E80* func_002A5660(FieldClass158DD0* object)
{
    return object->unk1C;
}

/**
 * @brief Get the first signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5670(FieldClass158DD0* object)
{
    return object->unk0C;
}

/**
 * @brief Get the second signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5680(FieldClass158DD0* object)
{
    return object->unk10;
}

/**
 * @brief Report supported operation flags.
 * @param object Object to query.
 * @return Supported flags.
 */
u32 func_002A5690(FieldClass158DD0* object)
{
    return 0x3F;
}

/**
 * @brief Test whether the primary array is present.
 * @param object Object to query.
 * @return Whether the array is present.
 */
bool func_002A56A0(FieldClass158DD0* object)
{
    return object->unk14 != 0;
}

FieldClass158D00::FieldClass158D00()
{
    unk04 = 0;
    unk14 = 0;
    unk18 = 0;
    unk1C = 0;
    unk20 = 0;
    unk24 = 0;
}

/**
 * @brief Get an indexed primary array element.
 * @param object Object owning the array.
 * @param index Signed element index.
 * @return Address of the indexed element.
 */
FieldClass158A18* func_002A5710(FieldClass158D00* object, s32 index)
{
    return &object->unk14[index];
}

/**
 * @brief Get an element from a secondary array row.
 * @param object Object owning the array.
 * @param row Signed primary element index.
 * @param column Signed index within its secondary row.
 * @return Address of the indexed secondary element.
 */
FieldObject154E60* func_002A5730(FieldClass158D00* object, s32 row, s32 column)
{
    return &object->unk20[row * (object->unk10 - 1) + column];
}

/**
 * @brief Get the associated bitset object.
 * @param object Object to query.
 * @return Stored value.
 */
FieldBitset154E80* func_002A5750(FieldClass158D00* object)
{
    return object->unk1C;
}

/**
 * @brief Get the first signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5760(FieldClass158D00* object)
{
    return object->unk0C;
}

/**
 * @brief Get the second signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5770(FieldClass158D00* object)
{
    return object->unk10;
}

/**
 * @brief Report supported operation flags.
 * @param object Object to query.
 * @return Supported flags.
 */
u32 func_002A5780(FieldClass158D00* object)
{
    return 0x2F;
}

/**
 * @brief Test whether the primary array is present.
 * @param object Object to query.
 * @return Whether the array is present.
 */
bool func_002A5790(FieldClass158D00* object)
{
    return object->unk14 != 0;
}

FieldClass158C30::FieldClass158C30()
{
    unk04 = 0;
    unk14 = 0;
    unk18 = 0;
    unk1C = 0;
    unk20 = 0;
    unk24 = 0;
}

/**
 * @brief Get an indexed primary array element.
 * @param object Object owning the array.
 * @param index Signed element index.
 * @return Address of the indexed element.
 */
FieldClass158A38* func_002A5800(FieldClass158C30* object, s32 index)
{
    return &object->unk14[index];
}

/**
 * @brief Get an element from a secondary array row.
 * @param object Object owning the array.
 * @param row Signed primary element index.
 * @param column Signed index within its secondary row.
 * @return Address of the indexed secondary element.
 */
FieldObject154E60* func_002A5820(FieldClass158C30* object, s32 row, s32 column)
{
    return &object->unk20[row * (object->unk10 - 1) + column];
}

/**
 * @brief Get the associated bitset object.
 * @param object Object to query.
 * @return Stored value.
 */
FieldBitset154E80* func_002A5840(FieldClass158C30* object)
{
    return object->unk1C;
}

/**
 * @brief Get the first signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5850(FieldClass158C30* object)
{
    return object->unk0C;
}

/**
 * @brief Get the second signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5860(FieldClass158C30* object)
{
    return object->unk10;
}

/**
 * @brief Report supported operation flags.
 * @param object Object to query.
 * @return Supported flags.
 */
u32 func_002A5870(FieldClass158C30* object)
{
    return 0x27;
}

/**
 * @brief Test whether the primary array is present.
 * @param object Object to query.
 * @return Whether the array is present.
 */
bool func_002A5880(FieldClass158C30* object)
{
    return object->unk14 != 0;
}

FieldClass158B60::FieldClass158B60()
{
    unk04 = 0;
    unk14 = 0;
    unk18 = 0;
    unk1C = 0;
    unk20 = 0;
    unk24 = 0;
}

/**
 * @brief Get an indexed primary array element.
 * @param object Object to query.
 * @param index Signed element index.
 * @return Address of the indexed element.
 */
FieldClass158A58* func_002A58F0(FieldClass158B60* object, s32 index)
{
    return &object->unk14[index];
}

/**
 * @brief Get an element from a secondary array row.
 * @param object Object owning the array.
 * @param row Signed primary element index.
 * @param column Signed index within its secondary row.
 * @return Address of the indexed secondary element.
 */
FieldObject154E60* func_002A5910(FieldClass158B60* object, s32 row, s32 column)
{
    return &object->unk20[row * (object->unk10 - 1) + column];
}

/**
 * @brief Get the associated bitset object.
 * @param object Object to query.
 * @return Stored bitset object pointer.
 */
FieldBitset154E80* func_002A5930(FieldClass158B60* object)
{
    return object->unk1C;
}

/**
 * @brief Get the first signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5940(FieldClass158B60* object)
{
    return object->unk0C;
}

/**
 * @brief Get the second signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5950(FieldClass158B60* object)
{
    return object->unk10;
}

/**
 * @brief Report supported operation flags.
 * @param object Object to query.
 * @return Supported flags.
 */
u32 func_002A5960(FieldClass158B60* object)
{
    return 0x23;
}

/**
 * @brief Test whether the primary array is present.
 * @param object Object to query.
 * @return Whether the array is present.
 */
bool func_002A5970(FieldClass158B60* object)
{
    return object->unk14 != 0;
}

FieldClass158A90::FieldClass158A90()
{
    unk04 = 0;
    unk14 = 0;
    unk18 = 0;
    unk1C = 0;
    unk20 = 0;
    unk24 = 0;
}

/**
 * @brief Get an indexed primary array element.
 * @param object Object to query.
 * @param index Signed element index.
 * @return Address of the indexed element.
 */
FieldClass158A78* func_002A59E0(FieldClass158A90* object, s32 index)
{
    return &object->unk14[index];
}

/**
 * @brief Get an element from a secondary array row.
 * @param object Object owning the array.
 * @param row Signed primary element index.
 * @param column Signed index within its secondary row.
 * @return Address of the indexed secondary element.
 */
FieldObject154E60* func_002A5A00(FieldClass158A90* object, s32 row, s32 column)
{
    return &object->unk20[row * (object->unk10 - 1) + column];
}

/**
 * @brief Get the associated bitset object.
 * @param object Object to query.
 * @return Stored bitset object pointer.
 */
FieldBitset154E80* func_002A5A20(FieldClass158A90* object)
{
    return object->unk1C;
}

/**
 * @brief Get the first signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5A30(FieldClass158A90* object)
{
    return object->unk0C;
}

/**
 * @brief Get the second signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5A40(FieldClass158A90* object)
{
    return object->unk10;
}

/**
 * @brief Report supported operation flags.
 * @param object Object to query.
 * @return Supported flags.
 */
u32 func_002A5A50(FieldClass158A90* object)
{
    return 0x21;
}

/**
 * @brief Test whether the primary array is present.
 * @param object Object to query.
 * @return Whether the array is present.
 */
bool func_002A5A60(FieldClass158A90* object)
{
    return object->unk14 != 0;
}

/**
 * @brief Reallocate the cells, the bit set and the secondary elements for a new size.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
void func_002A5A70(FieldClass158A90* object, s32 rows, s32 columns)
{
    object->unk14 = 0;
    object->unk20 = 0;
    delete[] object->unk18;
    object->unk18 = new (0) FieldClass158A78[rows + 2];
    if (object->unk18 == 0)
    {
        return;
    }
    delete object->unk1C;
    if (D_001B6684 != 0)
    {
        void* heap = resident_exchange_allocation_heap(D_001B6684);
        object->unk1C = new (0) FieldBitset154E80(rows);
        if (object->unk1C == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            resident_exchange_allocation_heap(heap);
            return;
        }
        if (object->unk1C->unk08 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            resident_exchange_allocation_heap(heap);
            return;
        }
        resident_exchange_allocation_heap(heap);
    }
    else
    {
        object->unk1C = new (0) FieldBitset154E80(rows);
        if (object->unk1C == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            return;
        }
        if (object->unk1C->unk08 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            return;
        }
    }
    if (columns > 1)
    {
        delete[] object->unk24;
        object->unk24 = new (0) FieldClass154E60[rows * (columns - 1) + 2];
        if (object->unk24 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            return;
        }
    }
    else
    {
        delete[] object->unk24;
        object->unk24 = 0;
    }
    if (object->unk18 != 0)
    {
        object->unk14 = object->unk18 + 1;
    }
    if (object->unk24 != 0)
    {
        object->unk20 = (FieldObject154E60*)(object->unk24 + 1);
    }
    object->unk0C = rows;
    object->unk10 = columns;
    object->unk1C->clear();
}

FieldClass158A78::FieldClass158A78()
{
}

FieldClass158A78::~FieldClass158A78()
{
}

FieldClass158A90::~FieldClass158A90()
{
    delete[] unk18;
    delete unk1C;
    delete[] unk24;
}

/**
 * @brief Reallocate the cells, the bit set and the secondary elements for a new size.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
void func_002A6170(FieldClass158B60* object, s32 rows, s32 columns)
{
    object->unk14 = 0;
    object->unk20 = 0;
    delete[] object->unk18;
    object->unk18 = new (0) FieldClass158A58[rows + 2];
    if (object->unk18 == 0)
    {
        return;
    }
    delete object->unk1C;
    if (D_001B6684 != 0)
    {
        void* heap = resident_exchange_allocation_heap(D_001B6684);
        object->unk1C = new (0) FieldBitset154E80(rows);
        if (object->unk1C == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            resident_exchange_allocation_heap(heap);
            return;
        }
        if (object->unk1C->unk08 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            resident_exchange_allocation_heap(heap);
            return;
        }
        resident_exchange_allocation_heap(heap);
    }
    else
    {
        object->unk1C = new (0) FieldBitset154E80(rows);
        if (object->unk1C == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            return;
        }
        if (object->unk1C->unk08 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            return;
        }
    }
    if (columns > 1)
    {
        delete[] object->unk24;
        object->unk24 = new (0) FieldClass154E60[rows * (columns - 1) + 2];
        if (object->unk24 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            return;
        }
    }
    else
    {
        delete[] object->unk24;
        object->unk24 = 0;
    }
    if (object->unk18 != 0)
    {
        object->unk14 = object->unk18 + 1;
    }
    if (object->unk24 != 0)
    {
        object->unk20 = (FieldObject154E60*)(object->unk24 + 1);
    }
    object->unk0C = rows;
    object->unk10 = columns;
    object->unk1C->clear();
}

FieldClass158A58::FieldClass158A58()
{
}

FieldClass158A58::~FieldClass158A58()
{
}

FieldClass158B60::~FieldClass158B60()
{
    delete[] unk18;
    delete unk1C;
    delete[] unk24;
}

/**
 * @brief Reallocate the cells, the bit set and the secondary elements for a new size.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
void func_002A6910(FieldClass158C30* object, s32 rows, s32 columns)
{
    object->unk14 = 0;
    object->unk20 = 0;
    delete[] object->unk18;
    object->unk18 = new (0) FieldClass158A38[rows + 2];
    if (object->unk18 == 0)
    {
        return;
    }
    delete object->unk1C;
    if (D_001B6684 != 0)
    {
        void* heap = resident_exchange_allocation_heap(D_001B6684);
        object->unk1C = new (0) FieldBitset154E80(rows);
        if (object->unk1C == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            resident_exchange_allocation_heap(heap);
            return;
        }
        if (object->unk1C->unk08 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            resident_exchange_allocation_heap(heap);
            return;
        }
        resident_exchange_allocation_heap(heap);
    }
    else
    {
        object->unk1C = new (0) FieldBitset154E80(rows);
        if (object->unk1C == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            return;
        }
        if (object->unk1C->unk08 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            return;
        }
    }
    if (columns > 1)
    {
        delete[] object->unk24;
        object->unk24 = new (0) FieldClass154E60[rows * (columns - 1) + 2];
        if (object->unk24 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            return;
        }
    }
    else
    {
        delete[] object->unk24;
        object->unk24 = 0;
    }
    if (object->unk18 != 0)
    {
        object->unk14 = object->unk18 + 1;
    }
    if (object->unk24 != 0)
    {
        object->unk20 = (FieldObject154E60*)(object->unk24 + 1);
    }
    object->unk0C = rows;
    object->unk10 = columns;
    object->unk1C->clear();
}

FieldClass158A38::FieldClass158A38()
{
}

FieldClass158A38::~FieldClass158A38()
{
}

FieldClass158C30::~FieldClass158C30()
{
    delete[] unk18;
    delete unk1C;
    delete[] unk24;
}

/**
 * @brief Reallocate the cells, the bit set and the secondary elements for a new size.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
void func_002A70D0(FieldClass158D00* object, s32 rows, s32 columns)
{
    object->unk14 = 0;
    object->unk20 = 0;
    delete[] object->unk18;
    object->unk18 = new (0) FieldClass158A18[rows + 2];
    if (object->unk18 == 0)
    {
        return;
    }
    delete object->unk1C;
    if (D_001B6684 != 0)
    {
        void* heap = resident_exchange_allocation_heap(D_001B6684);
        object->unk1C = new (0) FieldBitset154E80(rows);
        if (object->unk1C == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            resident_exchange_allocation_heap(heap);
            return;
        }
        if (object->unk1C->unk08 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            resident_exchange_allocation_heap(heap);
            return;
        }
        resident_exchange_allocation_heap(heap);
    }
    else
    {
        object->unk1C = new (0) FieldBitset154E80(rows);
        if (object->unk1C == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            return;
        }
        if (object->unk1C->unk08 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            return;
        }
    }
    if (columns > 1)
    {
        delete[] object->unk24;
        object->unk24 = new (0) FieldClass154E60[rows * (columns - 1) + 2];
        if (object->unk24 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            return;
        }
    }
    else
    {
        delete[] object->unk24;
        object->unk24 = 0;
    }
    if (object->unk18 != 0)
    {
        object->unk14 = object->unk18 + 1;
    }
    if (object->unk24 != 0)
    {
        object->unk20 = (FieldObject154E60*)(object->unk24 + 1);
    }
    object->unk0C = rows;
    object->unk10 = columns;
    object->unk1C->clear();
}

FieldClass158A18::FieldClass158A18()
{
}

FieldClass158A18::~FieldClass158A18()
{
}

FieldClass158D00::~FieldClass158D00()
{
    delete[] unk18;
    delete unk1C;
    delete[] unk24;
}

/**
 * @brief Reallocate the cells, the bit set and the secondary elements for a new size.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
void func_002A78C0(FieldClass158DD0* object, s32 rows, s32 columns)
{
    object->unk14 = 0;
    object->unk20 = 0;
    delete[] object->unk18;
    object->unk18 = new (0) FieldClass1589F8[rows + 2];
    if (object->unk18 == 0)
    {
        return;
    }
    delete object->unk1C;
    if (D_001B6684 != 0)
    {
        void* heap = resident_exchange_allocation_heap(D_001B6684);
        object->unk1C = new (0) FieldBitset154E80(rows);
        if (object->unk1C == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            resident_exchange_allocation_heap(heap);
            return;
        }
        if (object->unk1C->unk08 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            resident_exchange_allocation_heap(heap);
            return;
        }
        resident_exchange_allocation_heap(heap);
    }
    else
    {
        object->unk1C = new (0) FieldBitset154E80(rows);
        if (object->unk1C == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            return;
        }
        if (object->unk1C->unk08 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            return;
        }
    }
    if (columns > 1)
    {
        delete[] object->unk24;
        object->unk24 = new (0) FieldClass154E60[rows * (columns - 1) + 2];
        if (object->unk24 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            return;
        }
    }
    else
    {
        delete[] object->unk24;
        object->unk24 = 0;
    }
    if (object->unk18 != 0)
    {
        object->unk14 = object->unk18 + 1;
    }
    if (object->unk24 != 0)
    {
        object->unk20 = (FieldObject154E60*)(object->unk24 + 1);
    }
    object->unk0C = rows;
    object->unk10 = columns;
    object->unk1C->clear();
}

FieldClass1589F8::FieldClass1589F8()
{
}

FieldClass1589F8::~FieldClass1589F8()
{
}

/**
 * @brief Copy another grid's size and settings, reallocating this grid to match.
 * @param object Grid to update.
 * @param other Grid to copy.
 */
void func_002A8000(FieldClass158720* object, const FieldClass158720* other)
{
    object->unk0C = other->unk0C;
    object->unk10 = other->unk10;
    object->resize(object->unk0C, object->unk10);
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
    object->unkA0 = other->unkA0;
    object->unkA4 = other->unkA4;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A80D0);

/**
 * @brief Copy another grid's size and settings, reallocating this grid to match.
 * @param object Grid to update.
 * @param other Grid to copy.
 */
void func_002A87F0(FieldClass158170* object, const FieldClass158170* other)
{
    object->unk0C = other->unk0C;
    object->unk10 = other->unk10;
    object->resize(object->unk0C, object->unk10);
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
    object->unkA0 = other->unkA0;
    object->unkA4 = other->unkA4;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A88C0);

/**
 * @brief Copy another grid's size and settings, reallocating this grid to match.
 * @param object Grid to update.
 * @param other Grid to copy.
 */
void func_002A8FE0(FieldClass157E30* object, const FieldClass157E30* other)
{
    object->unk0C = other->unk0C;
    object->unk10 = other->unk10;
    object->resize(object->unk0C, object->unk10);
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
    object->unkA0 = other->unkA0;
    object->unkA4 = other->unkA4;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A90B0);

/**
 * @brief Copy another grid's size and settings, reallocating this grid to match.
 * @param object Grid to update.
 * @param other Grid to copy.
 */
void func_002A9810(FieldClass157AF0* object, const FieldClass157AF0* other)
{
    object->unk0C = other->unk0C;
    object->unk10 = other->unk10;
    object->resize(object->unk0C, object->unk10);
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
    object->unkA0 = other->unkA0;
    object->unkA4 = other->unkA4;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A98E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AA000);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AA0D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AA1A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AA6F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AAD70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AB570);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AB650);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002ABD90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002ABE80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002ABF90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AD4E0);

FieldClass158930::~FieldClass158930()
{
    if (!unkC9)
    {
        delete[] unkB0;
        delete[] unkB4;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AD670);

/**
 * @brief Copy another grid's size and settings, reallocating this grid to match.
 * @param object Grid to update.
 * @param other Grid to copy.
 */
void func_002AD760(FieldClass158860* object, const FieldClass158860* other)
{
    object->unk0C = other->unk0C;
    object->unk10 = other->unk10;
    object->resize(object->unk0C, object->unk10);
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
 * @brief Clear the index and copy four aligned values from the source.
 * @param object Receiver to update.
 * @param source Source of the four aligned values.
 */
void func_002AD830(FieldObject158860* object, const FieldVectorSource150* source)
{
    object->unk2C = 0;
    object->transform_rows[0] = source->unk150;
    object->transform_rows[1] = source->unk160;
    object->transform_rows[2] = source->unk170;
    object->transform_rows[3] = source->unk180;
}

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
void func_002AD860(FieldClass158A90* object, const FieldClass158A90* other)
{
    object->unk0C = other->unk0C;
    object->unk10 = other->unk10;
    object->resize(object->unk0C, object->unk10);
}

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
void func_002AD8A0(FieldClass158B60* object, const FieldClass158B60* other)
{
    object->unk0C = other->unk0C;
    object->unk10 = other->unk10;
    object->resize(object->unk0C, object->unk10);
}

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
void func_002AD8E0(FieldClass158C30* object, const FieldClass158C30* other)
{
    object->unk0C = other->unk0C;
    object->unk10 = other->unk10;
    object->resize(object->unk0C, object->unk10);
}

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
void func_002AD920(FieldClass158D00* object, const FieldClass158D00* other)
{
    object->unk0C = other->unk0C;
    object->unk10 = other->unk10;
    object->resize(object->unk0C, object->unk10);
}

/**
 * @brief Clear four trailing cell bytes and prepare the associated row.
 * @param object Grid owning the row.
 * @param cell Cell whose trailing bytes are cleared.
 * @param row First secondary element of the row.
 * @param index Value passed through to the row handler.
 * @param position_step Displacement subtracted per row element.
 * @param angle_pair Optional angle pair used by the row handler.
 * @param axis_radii Initial per-axis radii used with the angle pair.
 * @param angle_step Per-row change to the angle pair.
 * @param radius_step Change subtracted from the radii per row element.
 */
void field_prepare_cell_row(FieldClass158860* object, FieldClass1589F8* cell, FieldClass154E60* row, s32 index,
                            const FieldVector4* position_step, const FieldVector4* angle_pair, const FieldVector4* axis_radii,
                            const FieldVector4* angle_step, const FieldVector4* radius_step)
{
    cell->unk130 = 0;
    cell->unk132 = 0;
    cell->unk131 = 0;
    cell->unk133 = 0;
    field_position_secondary_row(object, cell, row, index, position_step, angle_pair, axis_radii, angle_step, radius_step);
}

/**
 * @brief Clear four trailing cell bytes and prepare the row using a vector.
 * @param object Grid owning the row.
 * @param cell Cell whose trailing bytes are cleared.
 * @param row First secondary element of the row.
 * @param index Value passed through to the row handler.
 * @param source Vector supplied to the row handler.
 */
void field_prepare_cell_row_from_vector(FieldClass158860* object, FieldClass1589F8* cell, FieldClass154E60* row, s32 index, const FieldVector4* source)
{
    cell->unk130 = 0;
    cell->unk132 = 0;
    cell->unk131 = 0;
    cell->unk133 = 0;
    field_fill_secondary_row(object, cell, row, index, source);
}

void func_002AD9C0(void* object)
{
}

/**
 * @brief Report the default enabled callback state.
 * @param object Object to query.
 * @return Always true.
 */
bool func_002AD9D0(FieldObject158860* object)
{
    return true;
}

/**
 * @brief Position a secondary row using optional linear and angular steps.
 * @param object Grid owning the row.
 * @param cell Cell supplying the initial position and secondary vector.
 * @param row First secondary element of the row.
 * @param index Nonzero to initialize each stepped element's first auxiliary value.
 * @param position_step Displacement subtracted per element, or null to copy the cell position.
 * @param angle_pair Initial two angles in radians, or null for linear stepping only.
 * @param axis_radii Initial per-axis radii used with the two angles.
 * @param angle_step Change subtracted from the two angles per element.
 * @param radius_step Change subtracted from the three radii per element.
 */
void field_position_secondary_row(FieldClass158860* object, FieldClass1589F8* cell, FieldClass154E60* row, s32 index,
                                  const FieldVector4* position_step, const FieldVector4* angle_pair, const FieldVector4* axis_radii,
                                  const FieldVector4* angle_step, const FieldVector4* radius_step)
{
    if (object->secondary_emitter != 0)
    {
        cell->unk3C = object->unk3C;
    }

    bool copy_secondary_vector = false;

    if (object->unk4D != 1 && object->unk4D != 3)
    {
        copy_secondary_vector = true;
    }

    if (position_step != 0)
    {
        if (angle_pair != 0)
        {
            const FieldClass1589F8* source_cell = cell;
            FieldVector4 position;
            FieldVector4 radii;
            FieldVector4 angles;
            LibVector4 second_trig;
            LibVector4 first_trig;
            s32 count = object->unk10 - 1;
            angles.packed = angle_pair->packed;
            radii.packed = axis_radii->packed;
            lib_compute_sine_cosine_pair(&first_trig, angles.floats[0]);
            lib_compute_sine_cosine_pair(&second_trig, angles.floats[1]);
            float previous_x = first_trig.components[2] * (radii.floats[0] * second_trig.components[2]);
            float previous_y = radii.floats[1] * first_trig.components[3];
            float previous_z = first_trig.components[2] * (radii.floats[2] * second_trig.components[3]);
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
                float x = first_trig.components[2] * (radii.floats[0] * second_trig.components[2]);
                position.floats[0] += x - previous_x;
                previous_x = x;
                float y = radii.floats[1] * first_trig.components[3];
                position.floats[1] += y - previous_y;
                previous_y = y;
                float z = first_trig.components[2] * (radii.floats[2] * second_trig.components[3]);
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
            FieldVector4 position;
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
void field_fill_secondary_row(FieldClass158860* object, FieldClass1589F8* cell, FieldClass154E60* row, s32 index, const FieldVector4* source)
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

/**
 * @brief Emit entries through the primary linked emitter.
 * @param object Grid owning the emission settings.
 * @param position Position transformed when the position flag is set.
 * @param first_offset First offset, transformed when its flag is set.
 * @param second_offset Second offset, transformed when its flag is set.
 * @param color_scale Color multiplier used when its flag is set.
 */
void field_emit_primary_entries(FieldClass158860* object, const LibVector4* position, const LibVector4* first_offset, const LibVector4* second_offset,
                                const LibVector4* color_scale)
{
    LibVector4 transformed_position;
    LibVector4 transformed_first;
    LibVector4 transformed_second;
    LibVector4 saved_state[2];
    const LibVector4* position_arg;
    const LibVector4* first_offset_arg;
    const LibVector4* second_offset_arg;
    const LibVector4* color_arg;
    u8 flags = object->primary_emission_flags;

    if (flags & FIELD_EMISSION_POSITION)
    {
        vu0_transform_emission_point(object->transform_rows, position, &transformed_position);
        position_arg = &transformed_position;
    }
    else
    {
        position_arg = 0;
    }

    if (flags & FIELD_EMISSION_FIRST_OFFSET)
    {
        vu0_transform_emission_direction(object->transform_rows, first_offset, &transformed_first);
        first_offset_arg = &transformed_first;
    }
    else
    {
        first_offset_arg = 0;
    }

    if (flags & FIELD_EMISSION_SECOND_OFFSET)
    {
        vu0_transform_emission_direction(object->transform_rows, second_offset, &transformed_second);
        second_offset_arg = &transformed_second;
    }
    else
    {
        second_offset_arg = 0;
    }

    if (flags & FIELD_EMISSION_COLOR_SCALE)
    {
        color_arg = color_scale;
    }
    else
    {
        color_arg = 0;
    }

    vu0_save_emission_state(saved_state);
    object->primary_emitter->emit_entries(object->primary_emission_count, position_arg, first_offset_arg, second_offset_arg, color_arg,
                                         0, 0, 0, 0, 0, 0);
    vu0_reset_emission_state();
    vu0_set_emission_delta(D_001B6690);
    vu0_restore_emission_state(saved_state);
}

/**
 * @brief Emit entries through the secondary linked emitter.
 * @param object Grid owning the emission settings.
 * @param position Position transformed when the position flag is set.
 * @param first_offset First offset, transformed when its flag is set. Its fourth component receives the grid value after emission.
 * @param second_offset Second offset, transformed when its flag is set.
 * @param color_scale Color multiplier used when its flag is set.
 */
void field_emit_secondary_entries(FieldClass158860* object, const LibVector4* position, LibVector4* first_offset, const LibVector4* second_offset,
                                  const LibVector4* color_scale)
{
    if (object->secondary_emitter != 0)
    {
        LibVector4 transformed_position;
        LibVector4 transformed_first;
        LibVector4 transformed_second;
        LibVector4 saved_state[2];
        const LibVector4* position_arg;
        const LibVector4* first_offset_arg;
        const LibVector4* second_offset_arg;
        const LibVector4* color_arg;
        u8 flags = object->secondary_emission_flags;

        if (flags & FIELD_EMISSION_POSITION)
        {
            vu0_transform_emission_point(object->transform_rows, position, &transformed_position);
            position_arg = &transformed_position;
        }
        else
        {
            position_arg = 0;
        }

        if (flags & FIELD_EMISSION_FIRST_OFFSET)
        {
            vu0_transform_emission_direction(object->transform_rows, first_offset, &transformed_first);
            first_offset_arg = &transformed_first;
            float scale = object->secondary_emission_scale;
            transformed_first.components[0] *= scale;
            transformed_first.components[1] *= scale;
            transformed_first.components[2] *= scale;
        }
        else
        {
            first_offset_arg = 0;
        }

        if (flags & FIELD_EMISSION_SECOND_OFFSET)
        {
            vu0_transform_emission_direction(object->transform_rows, second_offset, &transformed_second);
            second_offset_arg = &transformed_second;
        }
        else
        {
            second_offset_arg = 0;
        }

        if (flags & FIELD_EMISSION_COLOR_SCALE)
        {
            color_arg = color_scale;
        }
        else
        {
            color_arg = 0;
        }

        vu0_save_emission_state(saved_state);
        object->secondary_emitter->emit_entries(object->secondary_emission_count, position_arg, first_offset_arg, second_offset_arg, color_arg,
                                               0, 0, 0, 0, 0, 0);
        vu0_reset_emission_state();
        vu0_set_emission_delta(D_001B6690);
        vu0_restore_emission_state(saved_state);
        first_offset->components[3] = object->unk3C;
    }
}

/**
 * @brief Clear an active cell bit.
 * @param object Bit set owning the storage.
 * @param index Unsigned cell index.
 */
static inline void field_clear_grid_cell_bit(FieldBitset154E80* object, u32 index)
{
    u32 word_index = index >> 6;
    u64 keep_mask = ~((u64)1 << (index & 63));
    object->unk08[word_index] &= keep_mask;
}

/**
 * @brief Advance active cells' frame vectors and playback state into an output batch.
 * @param object Grid owning the cells and frame resource.
 * @param capacity Output-entry budget, counted in steps of the grid column count.
 * @param output Output records, with each cell written at the start of its row.
 * @param preserve_row_vector Nonzero to retain the saved xyz components in the first secondary element.
 */
void field_update_grid_frame_vectors(FieldClass158860* object, s32 capacity, FieldGridOutputRecord* output, s32 preserve_row_vector)
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
        vu0_set_grid_frame_delta(D_001B6690);

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

                FieldGridFrameMotion* state = &object->unk14[index];

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

                FieldGridFrameMotion* state = &object->unk14[index];

                FieldGridFrameVector* previous = &object->unk20[index * (columns - 1)].unk30;

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
        vu0_set_grid_frame_delta(D_001B6690);

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

                FieldGridFrameMotion* state = &object->unk14[index];

                FieldGridFrameState* frame = &state->frame;

                if (object->unk4C == 4 && boundary_limit < frame->boundary_count)
                {
                    field_clear_grid_cell_bit(object->unk1C, index);
                    index++;
                    continue;
                }

                frame->remaining_time -= D_001B6690;

                s32 frame_index = frame->frame_index;
                vu0_load_grid_frame_vectors(&state->value, &state->rate);

                while (frame->remaining_time <= 0.0f)
                {
                    frame_index += frame->reverse != 0 ? -1 : 1;

                    if (frame_index >= frame_count)
                    {
                        switch (loop_mode)
                        {
                        case FIELD_GRID_FRAME_WRAP:
                            frame_index = 0;
                            break;
                        case FIELD_GRID_FRAME_PING_PONG:
                            frame->reverse = 1;
                            frame_index--;
                            break;
                        case FIELD_GRID_FRAME_HOLD_LAST:
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

                FieldGridFrameMotion* state = &object->unk14[index];

                FieldGridFrameState* frame = &state->frame;

                if (object->unk4C == 4 && boundary_limit < frame->boundary_count)
                {
                    field_clear_grid_cell_bit(object->unk1C, index);
                    index++;
                    continue;
                }

                frame->remaining_time -= D_001B6690;

                s32 frame_index = frame->frame_index;
                FieldGridFrameVector* previous = &object->unk20[index * (columns - 1)].unk30;

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
                        case FIELD_GRID_FRAME_WRAP:
                            frame_index = 0;
                            break;
                        case FIELD_GRID_FRAME_PING_PONG:
                            frame->reverse = 1;
                            frame_index--;
                            break;
                        case FIELD_GRID_FRAME_HOLD_LAST:
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

void func_002AE9A0(void* object)
{
}

s32 func_002AE9B0(void* object)
{
    return 0;
}

void func_002AE9C0(void* object)
{
}

s32 func_002AE9D0(void* object)
{
    return 0;
}
