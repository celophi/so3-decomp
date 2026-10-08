#include "include_asm.h"
#include "overlays/1067-00/field_class_154D40.h"
#include "overlays/1067-00/field_class_154EF0.h"
#include "overlays/1067-00/text_0027E520.h"
#include "main/resident_0010A0E0.h"
#include "main/resident_data.h"
#include "overlays/1067-00/text_001DD3C0.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/1067-00/text_0027D380.h"

extern "C" s32 func_10CC40(s32 lower, s32 upper);

void func_0027E520(FieldHeldObject20* object)
{
    object->unk250--;
    if (object->unk250 == 0)
    {
        if (object->unk20 != 0)
        {
            func_004D65C0(object->unk20);
            object->unk20->func_001DD7B0();
            object->unk20 = 0;
        }
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027E580);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027E6D0);

void func_0027E7D0(FieldHeldObject20* object)
{
    if (object->unk20 != 0)
    {
        func_004D65C0(object->unk20);
        object->unk20->func_001DD7B0();
        object->unk20 = 0;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027E820);

/** Partial LibClass178EA0 with vtable D_155840 in main data. */
class FieldClass155840 : public LibClass178EA0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass155840();
};

FieldClass155840::~FieldClass155840()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027E970);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027EB80);

/** Partial FieldClass154E20 object with vtable D_155F30 in main data, tracked by D_001B6458. */
class FieldClass155F30 : public FieldClass154E20
{
public:
    /** @brief Clear D_001B6458 if it refers to this object, then destroy the object. */
    virtual ~FieldClass155F30();
    /** @brief Run the base update. */
    virtual void func_001DF360();
};

void FieldClass155F30::func_001DF360()
{
    FieldClass154EF0::func_001DF360();
    if (unk20_2)
    {
        return;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027ECD0);

FieldClass155F30::~FieldClass155F30()
{
    if (D_001B6458 == this)
    {
        D_001B6458 = 0;
    }
}

extern "C" void func_00288460(void* object);

/** @brief Forward the object to func_00288460. @param object Object to forward. */
extern "C" void func_0027EE10(void* object)
{
    func_00288460(object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027EE30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027F140);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027F1E0);

void func_0027F3D0(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027F3E0);

/** Partial FieldClass154E20 object with vtable D_1563C0 in main data, tracked by D_001B6450. */
class FieldClass1563C0 : public FieldClass154E20
{
public:
    /** @brief Clear D_001B6450 if it refers to this object, then destroy the object. */
    virtual ~FieldClass1563C0();
    /** @brief Run the base update. */
    virtual void func_001DF360();
};

void FieldClass1563C0::func_001DF360()
{
    FieldClass154EF0::func_001DF360();
    if (unk20_2)
    {
        return;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027FA10);

FieldClass1563C0::~FieldClass1563C0()
{
    if (D_001B6450 == this)
    {
        D_001B6450 = 0;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027FB50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027FF50);

/** Partial FieldClass154E20 object with vtable D_1565A0 in main data, tracked by D_001B644C. */
class FieldClass1565A0 : public FieldClass154E20
{
public:
    /** @brief Clear D_001B644C if it refers to this object, then destroy the object. */
    virtual ~FieldClass1565A0();
    /** @brief Run the base update. */
    virtual void func_001DF360();
};

void FieldClass1565A0::func_001DF360()
{
    FieldClass154EF0::func_001DF360();
    if (unk20_2)
    {
        return;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00280480);

FieldClass1565A0::~FieldClass1565A0()
{
    if (D_001B644C == this)
    {
        D_001B644C = 0;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00280580);

FieldClass1558D0::~FieldClass1558D0()
{
}

u32 func_00280620(FieldObject1559A0* object)
{
    return 3;
}

void func_00280630(FieldObject1559A0* object, FieldFloatSourceAF0* actor)
{
    object->unk28 = 0;
}

float func_00280640(FieldObject1559A0* object)
{
    return 2500.0f;
}

s32 func_00280660(void* object)
{
    return 1;
}

FieldClass155B40::~FieldClass155B40()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002807A0);

FieldClass155B80::~FieldClass155B80()
{
}

u32 func_002808F0(FieldObject155B80* object)
{
    return 3;
}

void func_00280900(FieldObject155B80* object, FieldFloatSourceAF0* actor)
{
    object->unk28 = 0;
}

float func_00280910(FieldObject155B80* object)
{
    return 2500.0f;
}

s32 func_00280930(void* object)
{
    return 1;
}

/** Partial FieldClass154EF0 with vtable D_155D20 in main data. */
class FieldClass155D20 : public FieldClass154EF0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass155D20();
};

FieldClass155D20::~FieldClass155D20()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00280A00);

s32 func_00280AE0(void* object)
{
    return 4;
}

void func_00280AF0(FieldHeldObject20* object)
{
    if (object->unk20 != 0)
    {
        func_004D65C0(object->unk20);
        object->unk20->func_001DD7B0();
        object->unk20 = 0;
    }
    object->unk250 = 0;
}

FieldClass155D90::~FieldClass155D90()
{
}

u32 func_00280BC0(FieldObject155D90* object)
{
    return 3;
}

void func_00280BD0(FieldObject155D90* object, FieldFloatSourceAF0* actor)
{
    object->unk28 = 0;
}

float func_00280BE0(FieldObject155D90* object)
{
    return 2500.0f;
}

s32 func_00280C00(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00280C70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00280D40);

void func_00280EE0(void* object)
{
}

FieldClass156150::~FieldClass156150()
{
}

u32 func_00280F70(FieldObject156150* object)
{
    return 3;
}

void func_00280F80(FieldObject156150* object, FieldFloatSourceAF0* actor)
{
    object->unk28 = 0;
}

float func_00280F90(FieldObject156150* object)
{
    return 2500.0f;
}

s32 func_00280FB0(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00281090);

FieldClass156400::~FieldClass156400()
{
}

u32 func_002811D0(FieldObject156400* object)
{
    return 3;
}

void func_002811E0(FieldObject156400* object, FieldFloatSourceAF0* actor)
{
    object->unk28 = 0;
}

float func_002811F0(FieldObject156400* object)
{
    return 2500.0f;
}

s32 func_00281210(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00281280);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00281340);

/** Partial receiver holding a byte pointer, a word and a flag byte. */
struct FieldState281980
{
    u8 unk00[0x2C];
    const u8* unk2C;
    s32 unk30;
    u8 unk34;
};

/**
 * @brief Store the byte pointer and word, then record whether the pointed byte is one.
 * @param object Receiver.
 * @param bytes Byte pointer to store.
 * @param value Word to store.
 */
extern "C" void func_00281980(FieldState281980* object, const u8* bytes, s32 value)
{
    object->unk2C = bytes;
    object->unk30 = value;
    if (*object->unk2C == 1)
    {
        object->unk34 = 1;
    }
    else
    {
        object->unk34 = 0;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002819C0);

/**
 * @brief Store the byte pointer and word, then record whether the pointed byte is one.
 * @param object Receiver.
 * @param bytes Byte pointer to store.
 * @param value Word to store.
 */
extern "C" void func_00282000(FieldState281980* object, const u8* bytes, s32 value)
{
    object->unk2C = bytes;
    object->unk30 = value;
    if (*object->unk2C == 1)
    {
        object->unk34 = 1;
    }
    else
    {
        object->unk34 = 0;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00282040);

/**
 * @brief Store the byte pointer and word, then record whether the pointed byte is one.
 * @param object Receiver.
 * @param bytes Byte pointer to store.
 * @param value Word to store.
 */
extern "C" void func_00282680(FieldState281980* object, const u8* bytes, s32 value)
{
    object->unk2C = bytes;
    object->unk30 = value;
    if (*object->unk2C == 1)
    {
        object->unk34 = 1;
    }
    else
    {
        object->unk34 = 0;
    }
}

s32 func_002826C0(void* object)
{
    return 0;
}

void func_002826D0(FieldObject1559A0* object)
{
}

float func_002826E0(FieldObject1559A0* object)
{
    return 100.0f;
}

void func_002826F0(void* object)
{
}

void func_00282700(FieldObject1559A0* object, FieldResourceHeader273720* header, FieldResourceRecord273720* records)
{
}

void func_00282710(void* object)
{
}

void func_00282720(void* object)
{
}

void func_00282730(void* object)
{
}

void func_00282740(void* object)
{
}

s32 func_00282750(FieldObject1559A0* object)
{
    return 0;
}

void func_00282760(void* object)
{
}

void func_00282770(void* object)
{
}

void func_00282780(void* object)
{
}

s32 func_00282790(FieldObject1559A0* object)
{
    return 0;
}

void func_002827A0(void* object)
{
}

void func_002827B0(void* object)
{
}

void func_002827C0(void* object)
{
}

void func_002827D0(void* object)
{
}

void func_002827E0(void* object)
{
}

s32 func_002827F0(void* object)
{
    return 0;
}

void func_00282800(void* object)
{
}

s32 func_00282810(void* object)
{
    return 0;
}

void func_00282820(FieldObject1559A0* object, float value)
{
}

float func_00282830(FieldObject1559A0* object)
{
    return 0.0f;
}

void func_00282840(void* object)
{
}

void func_00282850(void* object)
{
}

u8 func_00282860(FieldObject1559A0* object)
{
    return 0;
}

void func_00282870(void* object)
{
}

s32 func_00282880(void* object)
{
    return 0;
}

void func_00282890(void* object)
{
}

float func_002828A0(FieldObject1559A0* object)
{
    return 0.0f;
}

void func_002828B0(void* object)
{
}

s32 func_002828C0(void* object)
{
    return 0;
}

void func_002828D0(FieldObject155C50* object)
{

}

float func_002828E0(FieldObject155C50* object)
{
    return 100.0f;
}

void func_002828F0(void* object)
{
}

void func_00282900(FieldObject155C50* object, FieldResourceHeader273720* header, FieldResourceRecord273720* records)
{

}

void func_00282910(void* object)
{
}

void func_00282920(void* object)
{
}

void func_00282930(void* object)
{
}

void func_00282940(void* object)
{
}

s32 func_00282950(FieldObject155C50* object)
{
    return 0;
}

void func_00282960(void* object)
{
}

void func_00282970(void* object)
{
}

void func_00282980(void* object)
{
}

s32 func_00282990(FieldObject155C50* object)
{
    return 0;
}

void func_002829A0(void* object)
{
}

void func_002829B0(void* object)
{
}

void func_002829C0(void* object)
{
}

void func_002829D0(void* object)
{
}

void func_002829E0(void* object)
{
}

s32 func_002829F0(void* object)
{
    return 0;
}

void func_00282A00(void* object)
{
}

s32 func_00282A10(void* object)
{
    return 0;
}

void func_00282A20(FieldObject155C50* object, float value)
{

}

float func_00282A30(FieldObject155C50* object)
{
    return 0.0f;
}

void func_00282A40(void* object)
{
}

void func_00282A50(void* object)
{
}

u8 func_00282A60(FieldObject155C50* object)
{
    return 0;
}

void func_00282A70(void* object)
{
}

s32 func_00282A80(void* object)
{
    return 0;
}

void func_00282A90(void* object)
{
}

float func_00282AA0(FieldObject155C50* object)
{
    return 0.0f;
}

void func_00282AB0(void* object)
{
}

s32 func_00282AC0(void* object)
{
    return 0;
}

void func_00282AD0(FieldObject155E60* object)
{

}

float func_00282AE0(FieldObject155E60* object)
{
    return 100.0f;
}

void func_00282AF0(void* object)
{
}

void func_00282B00(FieldObject155E60* object, FieldResourceHeader273720* header, FieldResourceRecord273720* records)
{

}

void func_00282B10(void* object)
{
}

void func_00282B20(void* object)
{
}

void func_00282B30(void* object)
{
}

void func_00282B40(void* object)
{
}

s32 func_00282B50(FieldObject155E60* object)
{
    return 0;
}

void func_00282B60(void* object)
{
}

void func_00282B70(void* object)
{
}

void func_00282B80(void* object)
{
}

s32 func_00282B90(FieldObject155E60* object)
{
    return 0;
}

void func_00282BA0(void* object)
{
}

void func_00282BB0(void* object)
{
}

void func_00282BC0(void* object)
{
}

void func_00282BD0(void* object)
{
}

void func_00282BE0(void* object)
{
}

s32 func_00282BF0(void* object)
{
    return 0;
}

void func_00282C00(void* object)
{
}

s32 func_00282C10(void* object)
{
    return 0;
}

void func_00282C20(FieldObject155E60* object, float value)
{

}

float func_00282C30(FieldObject155E60* object)
{
    return 0.0f;
}

void func_00282C40(void* object)
{
}

void func_00282C50(void* object)
{
}

u8 func_00282C60(FieldObject155E60* object)
{
    return 0;
}

void func_00282C70(void* object)
{
}

s32 func_00282C80(void* object)
{
    return 0;
}

void func_00282C90(void* object)
{
}

float func_00282CA0(FieldObject155E60* object)
{
    return 0.0f;
}

void func_00282CB0(void* object)
{
}

s32 func_00282CC0(void* object)
{
    return 0;
}

void func_00282CD0(FieldObject156220* object)
{

}

float func_00282CE0(FieldObject156220* object)
{
    return 100.0f;
}

void func_00282CF0(void* object)
{
}

void func_00282D00(FieldObject156220* object, FieldResourceHeader273720* header, FieldResourceRecord273720* records)
{

}

void func_00282D10(void* object)
{
}

void func_00282D20(void* object)
{
}

void func_00282D30(void* object)
{
}

void func_00282D40(void* object)
{
}

s32 func_00282D50(FieldObject156220* object)
{
    return 0;
}

void func_00282D60(void* object)
{
}

void func_00282D70(void* object)
{
}

void func_00282D80(void* object)
{
}

s32 func_00282D90(FieldObject156220* object)
{
    return 0;
}

void func_00282DA0(void* object)
{
}

void func_00282DB0(void* object)
{
}

void func_00282DC0(void* object)
{
}

void func_00282DD0(void* object)
{
}

void func_00282DE0(void* object)
{
}

s32 func_00282DF0(void* object)
{
    return 0;
}

void func_00282E00(void* object)
{
}

s32 func_00282E10(void* object)
{
    return 0;
}

void func_00282E20(FieldObject156220* object, float value)
{

}

float func_00282E30(FieldObject156220* object)
{
    return 0.0f;
}

void func_00282E40(void* object)
{
}

void func_00282E50(void* object)
{
}

u8 func_00282E60(FieldObject156220* object)
{
    return 0;
}

void func_00282E70(void* object)
{
}

s32 func_00282E80(void* object)
{
    return 0;
}

void func_00282E90(void* object)
{
}

float func_00282EA0(FieldObject156220* object)
{
    return 0.0f;
}

void func_00282EB0(void* object)
{
}

s32 func_00282EC0(void* object)
{
    return 0;
}

void func_00282ED0(FieldObject1564D0* object)
{

}

float func_00282EE0(FieldObject1564D0* object)
{
    return 100.0f;
}

void func_00282EF0(void* object)
{
}

void func_00282F00(FieldObject1564D0* object, FieldResourceHeader273720* header, FieldResourceRecord273720* records)
{

}

void func_00282F10(void* object)
{
}

void func_00282F20(void* object)
{
}

void func_00282F30(void* object)
{
}

void func_00282F40(void* object)
{
}

s32 func_00282F50(FieldObject1564D0* object)
{
    return 0;
}

void func_00282F60(void* object)
{
}

void func_00282F70(void* object)
{
}

void func_00282F80(void* object)
{
}

s32 func_00282F90(FieldObject1564D0* object)
{
    return 0;
}

void func_00282FA0(void* object)
{
}

void func_00282FB0(void* object)
{
}

void func_00282FC0(void* object)
{
}

void func_00282FD0(void* object)
{
}

void func_00282FE0(void* object)
{
}

s32 func_00282FF0(void* object)
{
    return 0;
}

void func_00283000(void* object)
{
}

s32 func_00283010(void* object)
{
    return 0;
}

void func_00283020(FieldObject1564D0* object, float value)
{

}

float func_00283030(FieldObject1564D0* object)
{
    return 0.0f;
}

void func_00283040(void* object)
{
}

void func_00283050(void* object)
{
}

u8 func_00283060(FieldObject1564D0* object)
{
    return 0;
}

void func_00283070(void* object)
{
}

s32 func_00283080(void* object)
{
    return 0;
}

void func_00283090(void* object)
{
}

float func_002830A0(FieldObject1564D0* object)
{
    return 0.0f;
}

void func_002830B0(void* object)
{
}

s32 func_002830C0(void* object)
{
    return 0;
}

void func_002830D0(FieldObject156080* object)
{

}

float func_002830E0(FieldObject156080* object)
{
    return 100.0f;
}

void func_002830F0(void* object)
{
}

void func_00283100(FieldObject156080* object, FieldResourceHeader273720* header, FieldResourceRecord273720* records)
{

}

void func_00283110(void* object)
{
}

void func_00283120(void* object)
{
}

void func_00283130(void* object)
{
}

void func_00283140(void* object)
{
}

s32 func_00283150(FieldObject156080* object)
{
    return 0;
}

void func_00283160(void* object)
{
}

void func_00283170(void* object)
{
}

void func_00283180(void* object)
{
}

s32 func_00283190(FieldObject156080* object)
{
    return 0;
}

void func_002831A0(void* object)
{
}

void func_002831B0(void* object)
{
}

void func_002831C0(void* object)
{
}

void func_002831D0(void* object)
{
}

void func_002831E0(void* object)
{
}

s32 func_002831F0(void* object)
{
    return 0;
}

void func_00283200(void* object)
{
}

s32 func_00283210(void* object)
{
    return 0;
}

void func_00283220(FieldObject156080* object, float value)
{

}

float func_00283230(FieldObject156080* object)
{
    return 0.0f;
}

void func_00283240(void* object)
{
}

void func_00283250(void* object)
{
}

u8 func_00283260(FieldObject156080* object)
{
    return 0;
}

void func_00283270(void* object)
{
}

s32 func_00283280(void* object)
{
    return 0;
}

void func_00283290(void* object)
{
}

float func_002832A0(FieldObject156080* object)
{
    return 0.0f;
}

void func_002832B0(void* object)
{
}

FieldClass156A50::FieldClass156A50()
{
    unk04 = 0;
    base14 = 0;
    unk18 = 0;
    unk1C = 0;
    base20 = 0;
    unk24 = 0;
}

void* func_00283320(FieldClass156A50* object, s32 index)
{
    return object->base14 + index * 128;
}

void* func_00283330(FieldClass156A50* object, s32 row, s32 column)
{
    return object->base20 + (row * (object->unk10 - 1) + column) * 0x40;
}

FieldBitset154E80* func_00283350(FieldClass156A50* object)
{
    return object->unk1C;
}

s32 func_00283360(FieldClass156A50* object)
{
    return object->unk0C;
}

s32 func_00283370(FieldClass156A50* object)
{
    return object->unk10;
}

u32 func_00283380(FieldClass156A50* object)
{
    return 0x20;
}

s32 func_00283390(FieldClass156A50* object)
{
    return object->base14 != 0;
}

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
void func_002833A0(FieldClass156A50* object, const FieldClass156A50* other)
{
    object->unk0C = other->unk0C;
    object->unk10 = other->unk10;
    object->resize(object->unk0C, object->unk10);
}

FieldClass156980::FieldClass156980()
{
    unk04 = 0;
    base14 = 0;
    unk18 = 0;
    unk1C = 0;
    base20 = 0;
    unk24 = 0;
}

void* func_00283440(FieldClass156980* object, s32 index)
{
    return object->base14 + index * 80;
}

void* func_00283460(FieldClass156980* object, s32 row, s32 column)
{
    return object->base20 + (row * (object->unk10 - 1) + column) * 0x40;
}

FieldBitset154E80* func_00283480(FieldClass156980* object)
{
    return object->unk1C;
}

s32 func_00283490(FieldClass156980* object)
{
    return object->unk0C;
}

s32 func_002834A0(FieldClass156980* object)
{
    return object->unk10;
}

u32 func_002834B0(FieldClass156980* object)
{
    return 1;
}

s32 func_002834C0(FieldClass156980* object)
{
    return object->base14 != 0;
}

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
void func_002834D0(FieldClass156980* object, const FieldClass156980* other)
{
    object->unk0C = other->unk0C;
    object->unk10 = other->unk10;
    object->resize(object->unk0C, object->unk10);
}

FieldClass1568B0::FieldClass1568B0()
{
    unk04 = 0;
    base14 = 0;
    unk18 = 0;
    unk1C = 0;
    base20 = 0;
    unk24 = 0;
}

void* func_00283570(FieldClass1568B0* object, s32 index)
{
    return object->base14 + index * 112;
}

void* func_00283590(FieldClass1568B0* object, s32 row, s32 column)
{
    return object->base20 + (row * (object->unk10 - 1) + column) * 0x40;
}

FieldBitset154E80* func_002835B0(FieldClass1568B0* object)
{
    return object->unk1C;
}

s32 func_002835C0(FieldClass1568B0* object)
{
    return object->unk0C;
}

s32 func_002835D0(FieldClass1568B0* object)
{
    return object->unk10;
}

u32 func_002835E0(FieldClass1568B0* object)
{
    return 0x20;
}

s32 func_002835F0(FieldClass1568B0* object)
{
    return object->base14 != 0;
}

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
void func_00283600(FieldClass1568B0* object, const FieldClass1568B0* other)
{
    object->unk0C = other->unk0C;
    object->unk10 = other->unk10;
    object->resize(object->unk0C, object->unk10);
}

FieldClass1567E0::FieldClass1567E0()
{
    unk04 = 0;
    base14 = 0;
    unk18 = 0;
    unk1C = 0;
    base20 = 0;
    unk24 = 0;
}

void* func_002836A0(FieldClass1567E0* object, s32 index)
{
    return object->base14 + index * 128;
}

void* func_002836B0(FieldClass1567E0* object, s32 row, s32 column)
{
    return object->base20 + (row * (object->unk10 - 1) + column) * 0x40;
}

FieldBitset154E80* func_002836D0(FieldClass1567E0* object)
{
    return object->unk1C;
}

s32 func_002836E0(FieldClass1567E0* object)
{
    return object->unk0C;
}

s32 func_002836F0(FieldClass1567E0* object)
{
    return object->unk10;
}

u32 func_00283700(FieldClass1567E0* object)
{
    return 0x20;
}

s32 func_00283710(FieldClass1567E0* object)
{
    return object->base14 != 0;
}

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
void func_00283720(FieldClass1567E0* object, const FieldClass1567E0* other)
{
    object->unk0C = other->unk0C;
    object->unk10 = other->unk10;
    object->resize(object->unk0C, object->unk10);
}

FieldClass156710::FieldClass156710()
{
    unk04 = 0;
    base14 = 0;
    unk18 = 0;
    unk1C = 0;
    base20 = 0;
    unk24 = 0;
}

void* func_002837C0(FieldClass156710* object, s32 index)
{
    return object->base14 + index * 96;
}

void* func_002837E0(FieldClass156710* object, s32 row, s32 column)
{
    return object->base20 + (row * (object->unk10 - 1) + column) * 0x40;
}

FieldBitset154E80* func_00283800(FieldClass156710* object)
{
    return object->unk1C;
}

s32 func_00283810(FieldClass156710* object)
{
    return object->unk0C;
}

s32 func_00283820(FieldClass156710* object)
{
    return object->unk10;
}

u32 func_00283830(FieldClass156710* object)
{
    return 1;
}

s32 func_00283840(FieldClass156710* object)
{
    return object->base14 != 0;
}

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
void func_00283850(FieldClass156710* object, const FieldClass156710* other)
{
    object->unk0C = other->unk0C;
    object->unk10 = other->unk10;
    object->resize(object->unk0C, object->unk10);
}

FieldClass156640::FieldClass156640()
{
    unk04 = 0;
    base14 = 0;
    unk18 = 0;
    unk1C = 0;
    base20 = 0;
    unk24 = 0;
}

void* func_002838F0(FieldClass156640* object, s32 index)
{
    return object->base14 + index * 128;
}

void* func_00283900(FieldClass156640* object, s32 row, s32 column)
{
    return object->base20 + (row * (object->unk10 - 1) + column) * 0x40;
}

FieldBitset154E80* func_00283920(FieldClass156640* object)
{
    return object->unk1C;
}

s32 func_00283930(FieldClass156640* object)
{
    return object->unk0C;
}

s32 func_00283940(FieldClass156640* object)
{
    return object->unk10;
}

u32 func_00283950(FieldClass156640* object)
{
    return 0x20;
}

s32 func_00283960(FieldClass156640* object)
{
    return object->base14 != 0;
}

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
void func_00283970(FieldClass156640* object, const FieldClass156640* other)
{
    object->unk0C = other->unk0C;
    object->unk10 = other->unk10;
    object->resize(object->unk0C, object->unk10);
}

/**
 * @brief Reallocate the cells, the bit set and the secondary elements for a new size.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
void func_002839B0(FieldClass156640* object, s32 rows, s32 columns)
{
    object->base14 = 0;
    object->base20 = 0;
    delete[] object->unk18;
    object->unk18 = new (0) FieldClass156630[rows + 2];
    if (object->unk18 == 0)
    {
        return;
    }
    delete object->unk1C;
    if (D_001B6684 != 0)
    {
        void* heap = func_00100C80(D_001B6684);
        object->unk1C = new (0) FieldBitset154E80(rows);
        if (object->unk1C == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            func_00100C80(heap);
            return;
        }
        if (object->unk1C->unk08 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            func_00100C80(heap);
            return;
        }
        func_00100C80(heap);
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
        object->base14 = (u8*)(object->unk18 + 1);
    }
    if (object->unk24 != 0)
    {
        object->base20 = (u8*)(object->unk24 + 1);
    }
    object->unk0C = rows;
    object->unk10 = columns;
    object->unk1C->clear();
}

FieldClass156630::FieldClass156630()
{
    unk60 = 1.0f;
    unk64 = 0;
}

FieldClass156630::~FieldClass156630()
{
}

FieldClass156640::~FieldClass156640()
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
void func_002840B0(FieldClass156710* object, s32 rows, s32 columns)
{
    object->base14 = 0;
    object->base20 = 0;
    delete[] object->unk18;
    object->unk18 = new (0) FieldClass156620[rows + 2];
    if (object->unk18 == 0)
    {
        return;
    }
    delete object->unk1C;
    if (D_001B6684 != 0)
    {
        void* heap = func_00100C80(D_001B6684);
        object->unk1C = new (0) FieldBitset154E80(rows);
        if (object->unk1C == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            func_00100C80(heap);
            return;
        }
        if (object->unk1C->unk08 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            func_00100C80(heap);
            return;
        }
        func_00100C80(heap);
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
        object->base14 = (u8*)(object->unk18 + 1);
    }
    if (object->unk24 != 0)
    {
        object->base20 = (u8*)(object->unk24 + 1);
    }
    object->unk0C = rows;
    object->unk10 = columns;
    object->unk1C->clear();
}

FieldClass156620::FieldClass156620()
{
    unk30 = func_10CC40(0x3C, 0x78);
    unk50 = 0;
    unk38 = 0;
}

FieldClass156620::~FieldClass156620()
{
}

FieldClass156710::~FieldClass156710()
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
void func_002847F0(FieldClass1567E0* object, s32 rows, s32 columns)
{
    object->base14 = 0;
    object->base20 = 0;
    delete[] object->unk18;
    object->unk18 = new (0) FieldClass156610[rows + 2];
    if (object->unk18 == 0)
    {
        return;
    }
    delete object->unk1C;
    if (D_001B6684 != 0)
    {
        void* heap = func_00100C80(D_001B6684);
        object->unk1C = new (0) FieldBitset154E80(rows);
        if (object->unk1C == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            func_00100C80(heap);
            return;
        }
        if (object->unk1C->unk08 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            func_00100C80(heap);
            return;
        }
        func_00100C80(heap);
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
        object->base14 = (u8*)(object->unk18 + 1);
    }
    if (object->unk24 != 0)
    {
        object->base20 = (u8*)(object->unk24 + 1);
    }
    object->unk0C = rows;
    object->unk10 = columns;
    object->unk1C->clear();
}

FieldClass156610::FieldClass156610()
{
    unk60 = 1.0f;
}

FieldClass156610::~FieldClass156610()
{
}

FieldClass1567E0::~FieldClass1567E0()
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
void func_00284EE0(FieldClass1568B0* object, s32 rows, s32 columns)
{
    object->base14 = 0;
    object->base20 = 0;
    delete[] object->unk18;
    object->unk18 = new (0) FieldClass156600[rows + 2];
    if (object->unk18 == 0)
    {
        return;
    }
    delete object->unk1C;
    if (D_001B6684 != 0)
    {
        void* heap = func_00100C80(D_001B6684);
        object->unk1C = new (0) FieldBitset154E80(rows);
        if (object->unk1C == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            func_00100C80(heap);
            return;
        }
        if (object->unk1C->unk08 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            func_00100C80(heap);
            return;
        }
        func_00100C80(heap);
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
        object->base14 = (u8*)(object->unk18 + 1);
    }
    if (object->unk24 != 0)
    {
        object->base20 = (u8*)(object->unk24 + 1);
    }
    object->unk0C = rows;
    object->unk10 = columns;
    object->unk1C->clear();
}

FieldClass156600::FieldClass156600()
{
    unk60 = 0;
    unk64 = 1.0f;
}

FieldClass156600::~FieldClass156600()
{
}

FieldClass1568B0::~FieldClass1568B0()
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
void func_002855F0(FieldClass156980* object, s32 rows, s32 columns)
{
    object->base14 = 0;
    object->base20 = 0;
    delete[] object->unk18;
    object->unk18 = new (0) FieldClass1565F0[rows + 2];
    if (object->unk18 == 0)
    {
        return;
    }
    delete object->unk1C;
    if (D_001B6684 != 0)
    {
        void* heap = func_00100C80(D_001B6684);
        object->unk1C = new (0) FieldBitset154E80(rows);
        if (object->unk1C == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            func_00100C80(heap);
            return;
        }
        if (object->unk1C->unk08 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            func_00100C80(heap);
            return;
        }
        func_00100C80(heap);
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
        object->base14 = (u8*)(object->unk18 + 1);
    }
    if (object->unk24 != 0)
    {
        object->base20 = (u8*)(object->unk24 + 1);
    }
    object->unk0C = rows;
    object->unk10 = columns;
    object->unk1C->clear();
}

FieldClass1565F0::FieldClass1565F0()
{
    unk40 = 64.0f;
    unk44_0 = 1;
}

FieldClass1565F0::~FieldClass1565F0()
{
}

FieldClass156980::~FieldClass156980()
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
void func_00285D10(FieldClass156A50* object, s32 rows, s32 columns)
{
    object->base14 = 0;
    object->base20 = 0;
    delete[] object->unk18;
    object->unk18 = new (0) FieldClass1565E0[rows + 2];
    if (object->unk18 == 0)
    {
        return;
    }
    delete object->unk1C;
    if (D_001B6684 != 0)
    {
        void* heap = func_00100C80(D_001B6684);
        object->unk1C = new (0) FieldBitset154E80(rows);
        if (object->unk1C == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            func_00100C80(heap);
            return;
        }
        if (object->unk1C->unk08 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            func_00100C80(heap);
            return;
        }
        func_00100C80(heap);
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
        object->base14 = (u8*)(object->unk18 + 1);
    }
    if (object->unk24 != 0)
    {
        object->base20 = (u8*)(object->unk24 + 1);
    }
    object->unk0C = rows;
    object->unk10 = columns;
    object->unk1C->clear();
}

FieldClass1565E0::FieldClass1565E0()
{
}

FieldClass1565E0::~FieldClass1565E0()
{
}

FieldClass156A50::~FieldClass156A50()
{
    delete[] unk18;
    delete unk1C;
    delete[] unk24;
}

float func_00286400(FieldClass156A50* object)
{
    return 1.0f;
}

float func_00286410(FieldClass156980* object)
{
    return 1.0f;
}

float func_00286420(FieldClass1568B0* object)
{
    return 1.0f;
}

float func_00286430(FieldClass1567E0* object)
{
    return 1.0f;
}

float func_00286440(FieldClass156710* object)
{
    return 1.0f;
}

float func_00286450(FieldClass156640* object)
{
    return 1.0f;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00286460);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002864A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00286530);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00286570);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002865A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002865F0);

s32 func_00286620(FieldScriptObject151D40* object, u32 count)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00286630);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00286670);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00286770);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00286810);

s32 func_00286880(FieldScriptObject151D40* object, u32 count)
{
    return 1;
}

s32 func_00286890(FieldScriptObject151D40* object, u32 count)
{
    return 1;
}

s32 func_002868A0(FieldScriptObject151D40* object, u32 count)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002868B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00286920);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00286960);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00286B70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00286DB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00286F50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002870C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00287340);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002873C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00287410);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00287490);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00287520);

s32 func_00287600(void* object)
{
    return 3;
}

/** Partial FieldClass150070 object with vtable D_156B50 in main data. */
class FieldClass156B50 : public FieldClass150070
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass156B50();
};

FieldClass156B50::~FieldClass156B50()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002876A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00287770);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00287830);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00287B00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002880A0);

FieldClass156B70::~FieldClass156B70()
{
}

u32 func_00288220(FieldObject156B70* object)
{
    return 3;
}

void func_00288230(FieldObject156B70* object, FieldFloatSourceAF0* actor)
{
    object->unk28 = 0;
}

float func_00288240(FieldObject156B70* object)
{
    return 2500.0f;
}

s32 func_00288260(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00288270);

void func_00288450(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00288460);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002884B0);

/** Partial FieldClass154E20 object with vtable D_156C40 in main data. */
class FieldClass156C40 : public FieldClass154E20
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass156C40();
};

FieldClass156C40::~FieldClass156C40()
{
}

FieldClass156C80::~FieldClass156C80()
{
}

u32 func_00288640(FieldObject156C80* object)
{
    return 3;
}

void func_00288650(FieldObject156C80* object, FieldFloatSourceAF0* actor)
{
    object->unk28 = 0;
}

float func_00288660(FieldObject156C80* object)
{
    return 2500.0f;
}

s32 func_00288680(FieldObject156C80* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00288690);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00288990);

/** Partial FieldClass154E20 object with vtable D_156E20 in main data. */
class FieldClass156E20 : public FieldClass154E20
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass156E20();
    /** @brief Run the base update. */
    virtual void func_001DF360();
};

void FieldClass156E20::func_001DF360()
{
    FieldClass154EF0::func_001DF360();
    if (unk20_2)
    {
        return;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00288D00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00288D70);

void FieldClass156E60::func_001DD7B0()
{
    if (unk40 != 0)
    {
        func_004D65C0(unk40);
        unk40->func_001DD7B0();
        unk40 = 0;
    }
    func_004D65C0(this);
    func_0011ED90(D_001B65F4, this);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002890B0);


FieldClass156E20::~FieldClass156E20()
{
}

void func_002892C0(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002892D0);

FieldClass156E60::~FieldClass156E60()
{
}

s32 func_00289430(void* object)
{
    return 4;
}

s32 func_00289440(void* object)
{
    return 0;
}

void func_00289450(FieldObject156D50* object)
{

}

float func_00289460(FieldObject156D50* object)
{
    return 100.0f;
}

void func_00289470(FieldObject156D50* object)
{

}

void func_00289480(FieldObject156D50* object, FieldResourceHeader273720* resource, FieldResourceRecord273720* records)
{

}

void func_00289490(void* object)
{
}

void func_002894A0(void* object)
{
}

void func_002894B0(void* object)
{
}

void func_002894C0(void* object)
{
}

s32 func_002894D0(FieldObject156D50* object)
{
    return 0;
}

void func_002894E0(void* object)
{
}

void func_002894F0(void* object)
{
}

void func_00289500(void* object)
{
}

s32 func_00289510(FieldObject156D50* object)
{
    return 0;
}

void func_00289520(void* object)
{
}

void func_00289530(void* object)
{
}

void func_00289540(void* object)
{
}

void func_00289550(void* object)
{
}

void func_00289560(void* object)
{
}

s32 func_00289570(void* object)
{
    return 0;
}

void func_00289580(void* object)
{
}

s32 func_00289590(void* object)
{
    return 0;
}

void func_002895A0(FieldObject156D50* object, float value)
{

}

float func_002895B0(FieldObject156D50* object)
{
    return 0.0f;
}

void func_002895C0(void* object)
{
}

void func_002895D0(void* object)
{
}

u8 func_002895E0(FieldObject156D50* object)
{
    return 0;
}

void func_002895F0(void* object)
{
}

s32 func_00289600(void* object)
{
    return 0;
}

void func_00289610(void* object)
{
}

float func_00289620(FieldObject156D50* object)
{
    return 0.0f;
}

void func_00289630(void* object)
{
}

FieldClass156E90::FieldClass156E90()
{
    unk04 = 0;
    base14 = 0;
    unk18 = 0;
    unk1C = 0;
    base20 = 0;
    unk24 = 0;
}

void* func_002896A0(FieldClass156E90* object, s32 index)
{
    return object->base14 + index * 112;
}

void* func_002896C0(FieldClass156E90* object, s32 row, s32 column)
{
    return object->base20 + (row * (object->unk10 - 1) + column) * 0x40;
}

FieldBitset154E80* func_002896E0(FieldClass156E90* object)
{
    return object->unk1C;
}

s32 func_002896F0(FieldClass156E90* object)
{
    return object->unk0C;
}

s32 func_00289700(FieldClass156E90* object)
{
    return object->unk10;
}

u32 func_00289710(FieldClass156E90* object)
{
    return 1;
}

s32 func_00289720(FieldClass156E90* object)
{
    return object->base14 != 0;
}

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
void func_00289730(FieldClass156E90* object, const FieldClass156E90* other)
{
    object->unk0C = other->unk0C;
    object->unk10 = other->unk10;
    object->resize(object->unk0C, object->unk10);
}

/**
 * @brief Reallocate the cells, the bit set and the secondary elements for a new size.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
void func_00289770(FieldClass156E90* object, s32 rows, s32 columns)
{
    object->base14 = 0;
    object->base20 = 0;
    delete[] object->unk18;
    object->unk18 = new (0) FieldClass156E80[rows + 2];
    if (object->unk18 == 0)
    {
        return;
    }
    delete object->unk1C;
    if (D_001B6684 != 0)
    {
        void* heap = func_00100C80(D_001B6684);
        object->unk1C = new (0) FieldBitset154E80(rows);
        if (object->unk1C == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            func_00100C80(heap);
            return;
        }
        if (object->unk1C->unk08 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            func_00100C80(heap);
            return;
        }
        func_00100C80(heap);
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
        object->base14 = (u8*)(object->unk18 + 1);
    }
    if (object->unk24 != 0)
    {
        object->base20 = (u8*)(object->unk24 + 1);
    }
    object->unk0C = rows;
    object->unk10 = columns;
    object->unk1C->clear();
}

FieldClass156E80::FieldClass156E80()
{
    unk60 = 15.0f;
    unk64 = 15.0f;
    unk6C_0 = 0;
    unk6C_1 = 0;
}

FieldClass156E80::~FieldClass156E80()
{
}

FieldClass156E90::~FieldClass156E90()
{
    delete[] unk18;
    delete unk1C;
    delete[] unk24;
}

float func_00289EB0(FieldClass156E90* object)
{
    return 1.0f;
}

/** @brief Detach the object and add it to the resident release queue. @param object Object to release. */
extern "C" void func_00289EC0(void* object)
{
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00289EF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00289FB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0028A030);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0028A260);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0028A410);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0028A6C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0028A970);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0028B0E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0028BA70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0028BCA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0028BD20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0028C8D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0028CA60);

/** @brief Detach the object and add it to the resident release queue. @param object Object to release. */
extern "C" void func_0028CCE0(void* object)
{
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0028CD10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0028D200);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0028D270);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0028D350);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0028D4A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0028DF10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0028DF60);

s32 func_0028E090(void* object)
{
    return 4;
}

/** Partial FieldClass150070 object with vtable D_157020 in main data. */
class FieldClass157020 : public FieldClass150070
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass157020();
};

FieldClass157020::~FieldClass157020()
{
}

s32 func_0028E130(FieldObject157020* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0028E140);

s32 func_0028E1E0(FieldObject157040* object)
{
    return 2;
}

void func_0028E1F0(FieldObject157040* object)
{
    object->unk30_6 = 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0028E210);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0028E220);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0028E230);
