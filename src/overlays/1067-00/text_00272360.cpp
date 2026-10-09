#include "include_asm.h"
#include "overlays/1067-00/field_class_154D40.h"
#include "overlays/1067-00/text_00272360.h"
#include "overlays/1067-00/field_class_154EF0.h"
#include "overlays/1067-00/text_00207AF0.h"
#include "overlays/lib/text_0046AE20.h"
#include "main/resident_0010A0E0.h"
#include "main/resident_data.h"


/** @brief Destroy the derived shape storage and release its owned base buffer. */
FieldClass154D20::~FieldClass154D20()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00272360", func_002723E0);

/**
 * @brief Evaluate the cubic curve using its neighboring stored points.
 * @param curve Curve owner containing the points and coefficients.
 * @param position Input position.
 * @return Curve value, or zero when fewer than two points are stored.
 */
extern "C" float func_00272820(FieldClass1514F8* curve, float position)
{
    s32 count = curve->unk00;
    if (count < 2)
    {
        return 0.0f;
    }
    s32 lower = 0;
    s32 upper = count - 1;
    while (lower < upper)
    {
        s32 middle = (s32)((float)(lower + upper) / 2.0f);
        if (curve->unk04[middle].x < position)
        {
            lower = middle + 1;
        }
        else
        {
            upper = middle;
        }
    }
    if (lower > 0)
    {
        lower--;
    }
    FieldVec4B* point = &curve->unk04[lower];
    float delta = position - point->x;
    float width = point[1].x - point->x;
    return point->y + delta * ((point[1].y - point->y) / width - width * (2.0f * point->z + point[1].z) +
                              delta * (3.0f * point->z + delta * (point[1].z - point->z) / width));
}

/**
 * @brief Append a component pair to the preallocated curve array.
 * @param object Curve owner with space for another point.
 * @param first First component.
 * @param second Second component.
 * @return Index of the appended point.
 */
extern "C" s32 func_00272950(FieldClass1514F8* object, float first, float second)
{
    object->unk04[object->unk00] = FieldVec4A(first, second, 0.0f, 1.0f);
    object->unk00++;
    return object->unk00 - 1;
}

void FieldClass154D50::func_002729A0()
{
}

void FieldClass154D50::func_002729B0()
{
}

s32 FieldClass154EF0::func_001DF3D0()
{
    return 4;
}

void FieldClass154EF0::func_001DD7B0()
{
    func_004D65C0(this);
    if (!unk20_3)
    {
        func_slot28();
        func_0011ED90(D_001B65F4, this);
        unk20_3 = 1;
    }
}

s32 FieldClass154EF0::func_slot24()
{
    return 300;
}

void FieldClass154EF0::func_slot28()
{
    if (unk18 != 0)
    {
        func_0046B3F0(unk18);
        if (unk18 != 0)
        {
            unk18->func_00434FA0();
            unk18 = 0;
        }
    }
    if (unk1c != 0 && unk1c->unk08 == 0)
    {
        delete unk1c;
        unk1c = 0;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00272360", func_00272B50);

void FieldClass154EF0::func_slot2c()
{
    unk20_2 = 0;
    unk20_0 = unk20_1;
}

void FieldClass154EF0::func_slot38()
{
    if (unk1c != 0)
    {
        unk1c->func_slot30()->clear();
    }
}

void FieldClass154EF0::func_slot3c(s32 enabled)
{
    if (unk18 != 0)
    {
        if (enabled)
        {
            unk18->unk6A |= 1;
        }
        else
        {
            unk18->unk6A = unk18->unk6A & ~1;
        }
    }
}


s32 FieldClass154D50::func_00272D60()
{
    return -1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00272360", __dt__16FieldClass154E20Fv);

void FieldClass154EF0::func_slot1c(LibObject1751A0* target)
{
}

void FieldClass154EF0::func_slot20()
{
}

FieldClass154E60::FieldClass154E60()
{
}


FieldClass154E60::~FieldClass154E60()
{
}

FieldBitset154E80::~FieldBitset154E80()
{
    if (!unk0C)
    {
        delete[] unk08;
    }
}

s32 func_00272F90(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00272360", func_00272FA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00272360", func_00272FF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00272360", func_002730B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00272360", func_00273110);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00272360", func_00273170);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00272360", func_002731F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00272360", func_00273260);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00272360", func_002732B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00272360", func_00273320);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00272360", func_002733A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00272360", func_slot34__16FieldClass154EF0Fv);

FieldClass154EF0::~FieldClass154EF0()
{
    func_slot28();
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00272360", func_00273640);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00272360", func_00273710);
