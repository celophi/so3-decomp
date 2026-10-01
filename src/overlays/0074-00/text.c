#include "include_asm.h"
#include "overlays/0074-00/text.h"

struct ObjectFields
{
    u8 unknown_0[0x4];
    u32 field_4;
    u8 field_8;
    u8 unknown_9;
    u16 field_a;
    u8 field_c;
    u8 field_d;
    u8 unknown_e[0x2];
    u32 field_10;
    u8 unknown_14[0x84];
    u32 field_98;
    u32 field_9c;
};

struct ObjectField20
{
    u8 unknown_0[0x20];
    u32 field_20;
};

struct ObjectField34
{
    u8 unknown_0[0x34];
    u32 field_34;
};

struct ObjectField12C
{
    u8 unknown_0[0x12C];
    u8 field_12c;
};

struct ObjectStatusFields
{
    u8 unknown_0[0x24];
    u32 field_24;
    s8 field_28;
    u8 unknown_29[0xF];
    u8 field_38;
};

typedef struct ObjectElement
{
    u8 unknown_0[0x1C];
    float position;
    u8 unknown_20[0x1C];
    u8 active;
} ObjectElement;

struct ObjectElements5
{
    u8 unknown_0[0x138];
    ObjectElement* first[5];
    ObjectElement* second[5];
};

struct ObjectElements6
{
    u8 unknown_0[0x138];
    ObjectElement* first[6];
    ObjectElement* second[6];
};

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_003483C0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00348400);

void func_00348460(ObjectFields* object, u8 value)
{
    object->field_c = value;
}

u8 func_00348470(ObjectFields* object)
{
    return object->field_c;
}

void func_00348480(ObjectFields* object, u8 value)
{
    object->field_8 = value;
}

u8 func_00348490(ObjectFields* object)
{
    return object->field_8;
}

void func_003484A0(ObjectFields* object, u16 value)
{
    object->field_a = value;
}

u16 func_003484B0(ObjectFields* object)
{
    return object->field_a;
}

void func_003484C0(ObjectFields* object, u32 value)
{
    object->field_98 = value;
}

u32 func_003484D0(ObjectFields* object)
{
    return object->field_98;
}

void func_003484E0(ObjectFields* object, u32 value)
{
    object->field_9c = value;
}

u32 func_003484F0(ObjectFields* object)
{
    return object->field_9c;
}

void func_00348500(ObjectFields* object, u32 value)
{
    object->field_4 = value;
}

u32 func_00348510(ObjectFields* object)
{
    return object->field_4;
}

u32 func_00348520(ObjectFields* object)
{
    return object->field_10;
}

void func_00348530(void* object)
{
}

void func_00348540(void* object)
{
}

void func_00348550(void* object)
{
}

void func_00348560(void* object)
{
}

void func_00348570(void* object)
{
}

void func_00348580(void* object)
{
}

void func_00348590(void* object)
{
}

void func_003485A0(void* object)
{
}

void func_003485B0(void* object)
{
}

void func_003485C0(void* object)
{
}

void func_003485D0(void* object)
{
}

void func_003485E0(void* object)
{
}

void func_003485F0(void* object)
{
}

void func_00348600(void* object)
{
}

void func_00348610(void* object)
{
}

void func_00348620(void* object)
{
}

void func_00348630(void* object)
{
}

void func_00348640(void* object)
{
}

void func_00348650(void* object)
{
}

s32 func_00348660(void* object)
{
    return 0;
}

s32 func_00348670(void* object)
{
    return 0;
}

s32 func_00348680(void* object)
{
    return 0;
}

s32 func_00348690(void* object)
{
    return 0;
}

s32 func_003486A0(void* object)
{
    return 0;
}

s32 func_003486B0(void* object)
{
    return 0;
}

s32 func_003486C0(void* object)
{
    return 0;
}

s32 func_003486D0(void* object)
{
    return 0;
}

s32 func_003486E0(void* object)
{
    return 0;
}

s32 func_003486F0(void* object)
{
    return 0;
}

void func_00348700(void* object)
{
}

void func_00348710(void* object)
{
}

u8 func_00348720(ObjectFields* object)
{
    return object->field_d;
}

void func_00348730(ObjectFields* object, u8 value)
{
    object->field_d = value;
}

void func_00348740(void* object)
{
}

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00348750);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00348810);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_003488D0);

void func_00348960(ObjectField20* object, u32 value)
{
    object->field_20 = value;
}

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00348970);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00348AF0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00348F90);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00349050);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00349110);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_003491A0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00349310);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_003497B0);

u32 func_00349820(ObjectField20* object)
{
    return object->field_20;
}

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00349830);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_003498F0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_003499B0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00349A40);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00349B40);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00349FF0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034A0A0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034A0F0);

u32 func_0034A1D0(ObjectField34* object)
{
    return object->field_34;
}

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034A1E0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034A2C0);

void func_0034A480(ObjectElements5* object, float position)
{
    s32 i = 0;
    float current = position + 16.0f;
    do
    {
        ObjectElement* first;
        ObjectElement* second;
        first = object->first[i];
        first->position = current;
        first->active = 1;
        second = object->second[i];
        second->position = current;
        second->active = 1;
        current += 28.0f;
        i++;
    } while (i < 5);
}

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034A4E0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034A640);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034A720);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034AE20);

void func_0034AE80(ObjectField12C* object, u8 value)
{
    object->field_12c = value;
}

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034AE90);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034AF50);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034AFA0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034AFF0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034B020);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034B050);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034B170);

void func_0034B260(ObjectElements6* object, float position)
{
    s32 i = 0;
    float current = position + 16.0f;
    do
    {
        ObjectElement* first;
        ObjectElement* second;
        first = object->first[i];
        first->position = current;
        first->active = 1;
        second = object->second[i];
        second->position = current;
        second->active = 1;
        current += 28.0f;
        i++;
    } while (i < 6);
}

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034B2C0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034B3C0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034B5B0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034BA30);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034BAB0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034BB00);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034C620);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034C690);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034C6D0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034C750);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034C7D0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034C890);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034C970);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034CA50);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034CAA0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034CAF0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034CB20);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034CBD0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034CC10);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034CD10);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034CE00);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034CF20);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034CFB0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034D1E0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034D860);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034D920);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034DA60);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034DE30);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034DE90);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034DEF0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034DF50);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034DFC0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034E110);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034E5C0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034E630);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034ED20);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034F350);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_0034FEE0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00350360);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_003503E0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00350520);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_003508D0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00350B30);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00350D00);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00350EC0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00350FE0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_003510B0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_003510D0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00351460);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00351540);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00351570);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_003515F0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00351640);

void func_003516A0(void* object)
{
}

void func_003516B0(void* object)
{
}

void func_003516C0(void* object)
{
}

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_003516D0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00351730);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00351790);

void func_00351800(void* object)
{
}

void func_00351810(void* object)
{
}

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00351820);

s32 func_00351890(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_003518A0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00351910);

s32 func_00351970(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00351980);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_003519E0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00351A40);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00351AA0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00351B00);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00351B60);

u8 func_00351BD0(ObjectStatusFields* object)
{
    return object->field_38;
}

s32 func_00351BE0(void* object)
{
    return 4;
}

void func_00351BF0(ObjectStatusFields* object, u32 value)
{
    object->field_24 = value;
}

u32 func_00351C00(ObjectStatusFields* object)
{
    return object->field_24;
}

void func_00351C10(ObjectStatusFields* object, s8 value)
{
    object->field_28 = value;
}

s8 func_00351C20(ObjectStatusFields* object)
{
    return object->field_28;
}

s32 func_00351C30(void* object)
{
    return 0;
}

s32 func_00351C40(void* object)
{
    return 0;
}

void func_00351C50(void* object)
{
}

s32 func_00351C60(void* object)
{
    return 0;
}

void func_00351C70(void* object)
{
}

void func_00351C80(void* object)
{
}

void func_00351C90(void* object)
{
}

s32 func_00351CA0(void* object)
{
    return 0;
}

s32 func_00351CB0(void* object)
{
    return 0;
}

s32 func_00351CC0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00351CD0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00351D60);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00351DF0);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00351E80);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00351F10);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00351F20);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00351F30);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00351F40);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00351F50);

INCLUDE_ASM("build/overlays/0074-00/asm/nonmatchings/text", func_00351F60);
