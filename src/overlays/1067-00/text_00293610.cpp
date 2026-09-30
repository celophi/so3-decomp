#include "include_asm.h"
#include "overlays/1067-00/text_00293610.h"

extern "C" float D_001B6688;
extern "C" u8 D_001B6448;
extern "C" float D_001B6690;
extern "C" void func_428670(void* object);
extern "C" void func_426C20(void* object);
extern "C" u8 func_452870(void* object, void* context);

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
        delay -= D_001B6688;
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

u8 func_002937F0(FieldClass1587E8* object, void* context)
{
    float previous = D_001B6690;
    u8 result;
    if (D_001B6448)
    {
        D_001B6690 = 1.0f / 60.0f;
    }
    result = func_452870(object, context);
    D_001B6690 = previous;
    return result;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00293840);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00293A40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00294510);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00294590);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00294600);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00294680);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_002946F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00294750);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_002947D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00294840);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_002948A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00294920);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00294990);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_002949F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00294A70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00294AE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00294B60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00294BD0);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295270);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_002952E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295340);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_002953B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295440);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_002954A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295510);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_002955A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295600);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295670);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295700);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295760);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_002957D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295860);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_002958C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295930);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_002959C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295A20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295A90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295AB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295B40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295BA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295C10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295C30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295C90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295CA0);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295D90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295DA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295DB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295DC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295DD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295DE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295DF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295E00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295E10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295E20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295E30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295E40);

// Vector dispatcher; runtime layouts and vector-unit operations remain unresolved.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00295E50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_002989C0);

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

void func_00298AA0(FieldObject158860* object, FieldObject158860Link48* value)
{
    object->unk48 = value;
}

FieldObject158860Link48* func_00298AB0(FieldObject158860* object)
{
    return object->unk48;
}

void func_00298AC0(FieldObject158860* object, u8 value)
{
    object->unk4F = value;
}

void func_00298AD0(FieldObject158860* object, u8 value)
{
    object->unk4E = value;
}

void func_00298AE0(FieldObject158860* object, FieldObject158860Link50* value)
{
    object->unk50 = value;
}

FieldObject158860Link50* func_00298AF0(FieldObject158860* object)
{
    return object->unk50;
}

void func_00298B00(FieldObject158860* object, u8 value)
{
    object->unk55 = value;
}

void func_00298B10(FieldObject158860* object, float value)
{
    object->unk3C = value;
}

void func_00298B20(FieldObject158860* object, u8 value)
{
    object->unk54 = value;
}

void func_00298B30(FieldObject158860* object, float value)
{
    object->unk40 = value;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00298B40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00298B80);

void func_00298BB0(FieldObject158860* object, float value)
{
    object->unk38 = value;
}

void func_00298BC0(FieldObject157AF0* object, const FieldVectorSource150* source)
{
    object->unk2C = 0;
    object->unk60 = source->unk150;
    object->unk70 = source->unk160;
    object->unk80 = source->unk170;
    object->unk90 = source->unk180;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00298BF0);

// Vector dispatcher; runtime layouts and vector-unit operations remain unresolved.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_00298C00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_0029B6D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_0029B6E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_0029B710);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_0029BB20);

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

void func_0029BCD0(FieldObject157AF0* object, FieldLinkedObject157AF0* value)
{
    object->unk48 = value;
}

FieldLinkedObject157AF0* func_0029BCE0(const FieldObject157AF0* object)
{
    return object->unk48;
}

void func_0029BCF0(FieldObject157AF0* object, u8 value)
{
    object->unk4F = value;
}

void func_0029BD00(FieldObject157AF0* object, u8 value)
{
    object->unk4E = value;
}

void func_0029BD10(FieldObject157AF0* object, FieldLinkedObject157AF0* value)
{
    object->unk50 = value;
}

FieldLinkedObject157AF0* func_0029BD20(const FieldObject157AF0* object)
{
    return object->unk50;
}

void func_0029BD30(FieldObject157AF0* object, u8 value)
{
    object->unk55 = value;
}

void func_0029BD40(FieldObject157AF0* object, float value)
{
    object->unk3C = value;
}

void func_0029BD50(FieldObject157AF0* object, u8 value)
{
    object->unk54 = value;
}

void func_0029BD60(FieldObject157AF0* object, float value)
{
    object->unk40 = value;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_0029BD70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_0029BDB0);

void func_0029BDE0(FieldObject157AF0* object, float value)
{
    object->unk38 = value;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_0029BDF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_0029BE00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_0029BE10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_0029BE20);

void func_0029BE30(FieldObject157BC0* object, const FieldVectorSource150* source)
{
    object->unk2C = 0;
    object->unk60 = source->unk150;
    object->unk70 = source->unk160;
    object->unk80 = source->unk170;
    object->unk90 = source->unk180;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_0029BE60);

// Vector dispatcher; runtime layouts and vector-unit operations remain unresolved.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00293610", func_0029BE70);
