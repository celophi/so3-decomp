#include "include_asm.h"
#include "overlays/1067-00/text_0027E520.h"
#include "main/resident_0010A0E0.h"
#include "main/resident_data.h"
#include "overlays/1067-00/text_001DD3C0.h"

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027E910);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027E970);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027EB80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027ECA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027ECD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027ED80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027EE10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027EE30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027F140);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027F1E0);

void func_0027F3D0(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027F3E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027F9E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027FA10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027FAC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027FB50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0027FF50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00280450);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00280480);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002804F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00280580);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002805A0);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00280670);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002806D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00280740);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002807A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00280880);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00280940);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002809A0);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00280B50);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00280C10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00280C70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00280D40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00280E10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00280E80);

void func_00280EE0(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00280EF0);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00280FC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00281020);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00281090);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00281160);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00281220);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00281280);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00281340);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00281980);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002819C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00282000);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00282040);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00282680);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002832C0);

void* func_00283320(FieldObject156A50* object, s32 index)
{
    return object->base14 + index * 128;
}

void* func_00283330(FieldObject156A50* object, s32 row, s32 column)
{
    return object->base20 + (row * (object->unk10 - 1) + column) * 0x40;
}

FieldBitset154E80* func_00283350(FieldObject156A50* object)
{
    return object->unk1C;
}

s32 func_00283360(FieldObject156A50* object)
{
    return object->unk0C;
}

s32 func_00283370(FieldObject156A50* object)
{
    return object->unk10;
}

u32 func_00283380(FieldObject156A50* object)
{
    return 0x20;
}

s32 func_00283390(FieldObject156A50* object)
{
    return object->base14 != 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002833A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002833E0);

void* func_00283440(FieldObject156980* object, s32 index)
{
    return object->base14 + index * 80;
}

void* func_00283460(FieldObject156980* object, s32 row, s32 column)
{
    return object->base20 + (row * (object->unk10 - 1) + column) * 0x40;
}

FieldBitset154E80* func_00283480(FieldObject156980* object)
{
    return object->unk1C;
}

s32 func_00283490(FieldObject156980* object)
{
    return object->unk0C;
}

s32 func_002834A0(FieldObject156980* object)
{
    return object->unk10;
}

u32 func_002834B0(FieldObject156980* object)
{
    return 1;
}

s32 func_002834C0(FieldObject156980* object)
{
    return object->base14 != 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002834D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00283510);

void* func_00283570(FieldObject1568B0* object, s32 index)
{
    return object->base14 + index * 112;
}

void* func_00283590(FieldObject1568B0* object, s32 row, s32 column)
{
    return object->base20 + (row * (object->unk10 - 1) + column) * 0x40;
}

FieldBitset154E80* func_002835B0(FieldObject1568B0* object)
{
    return object->unk1C;
}

s32 func_002835C0(FieldObject1568B0* object)
{
    return object->unk0C;
}

s32 func_002835D0(FieldObject1568B0* object)
{
    return object->unk10;
}

u32 func_002835E0(FieldObject1568B0* object)
{
    return 0x20;
}

s32 func_002835F0(FieldObject1568B0* object)
{
    return object->base14 != 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00283600);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00283640);

void* func_002836A0(FieldObject1567E0* object, s32 index)
{
    return object->base14 + index * 128;
}

void* func_002836B0(FieldObject1567E0* object, s32 row, s32 column)
{
    return object->base20 + (row * (object->unk10 - 1) + column) * 0x40;
}

FieldBitset154E80* func_002836D0(FieldObject1567E0* object)
{
    return object->unk1C;
}

s32 func_002836E0(FieldObject1567E0* object)
{
    return object->unk0C;
}

s32 func_002836F0(FieldObject1567E0* object)
{
    return object->unk10;
}

u32 func_00283700(FieldObject1567E0* object)
{
    return 0x20;
}

s32 func_00283710(FieldObject1567E0* object)
{
    return object->base14 != 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00283720);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00283760);

void* func_002837C0(FieldObject156710* object, s32 index)
{
    return object->base14 + index * 96;
}

void* func_002837E0(FieldObject156710* object, s32 row, s32 column)
{
    return object->base20 + (row * (object->unk10 - 1) + column) * 0x40;
}

FieldBitset154E80* func_00283800(FieldObject156710* object)
{
    return object->unk1C;
}

s32 func_00283810(FieldObject156710* object)
{
    return object->unk0C;
}

s32 func_00283820(FieldObject156710* object)
{
    return object->unk10;
}

u32 func_00283830(FieldObject156710* object)
{
    return 1;
}

s32 func_00283840(FieldObject156710* object)
{
    return object->base14 != 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00283850);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00283890);

void* func_002838F0(FieldObject156640* object, s32 index)
{
    return object->base14 + index * 128;
}

void* func_00283900(FieldObject156640* object, s32 row, s32 column)
{
    return object->base20 + (row * (object->unk10 - 1) + column) * 0x40;
}

FieldBitset154E80* func_00283920(FieldObject156640* object)
{
    return object->unk1C;
}

s32 func_00283930(FieldObject156640* object)
{
    return object->unk0C;
}

s32 func_00283940(FieldObject156640* object)
{
    return object->unk10;
}

u32 func_00283950(FieldObject156640* object)
{
    return 0x20;
}

s32 func_00283960(FieldObject156640* object)
{
    return object->base14 != 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00283970);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002839B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00283F00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00283F50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00283FD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002840B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00284610);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00284690);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00284710);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002847F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00284D40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00284D80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00284E00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00284EE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00285440);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00285490);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00285510);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002855F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00285B50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00285BB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00285C30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00285D10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00286260);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002862A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00286320);

float func_00286400(FieldObject156A50* object)
{
    return 1.0f;
}

float func_00286410(FieldObject156980* object)
{
    return 1.0f;
}

float func_00286420(FieldObject1568B0* object)
{
    return 1.0f;
}

float func_00286430(FieldObject1567E0* object)
{
    return 1.0f;
}

float func_00286440(FieldObject156710* object)
{
    return 1.0f;
}

float func_00286450(FieldObject156640* object)
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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00287610);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002876A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00287770);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00287830);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00287B00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002880A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002881A0);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00288560);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002885D0);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00288CD0);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002891F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00289250);

void func_002892C0(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002892D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_002893A0);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00289640);

void* func_002896A0(FieldObject156E90* object, s32 index)
{
    return object->base14 + index * 112;
}

void* func_002896C0(FieldObject156E90* object, s32 row, s32 column)
{
    return object->base20 + (row * (object->unk10 - 1) + column) * 0x40;
}

FieldBitset154E80* func_002896E0(FieldObject156E90* object)
{
    return object->unk1C;
}

s32 func_002896F0(FieldObject156E90* object)
{
    return object->unk0C;
}

s32 func_00289700(FieldObject156E90* object)
{
    return object->unk10;
}

u32 func_00289710(FieldObject156E90* object)
{
    return 1;
}

s32 func_00289720(FieldObject156E90* object)
{
    return object->base14 != 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00289730);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00289770);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00289CD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00289D50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00289DD0);

float func_00289EB0(FieldObject156E90* object)
{
    return 1.0f;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_00289EC0);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0028CCE0);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0027E520", func_0028E0A0);

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
