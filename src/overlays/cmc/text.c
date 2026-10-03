#include "include_asm.h"
#include "overlays/cmc/text.h"

struct Overlay0072Object00349670
{
    u8 unknown_0[0x4];
    s32 field_4;
};

struct Overlay0072Object00349AB0
{
    u8 unknown_0[0xC];
    u8 field_C;
};

struct Overlay0072Object0034A1D0
{
    u8 unknown_0[0xC];
    u8 field_C;
    u8 unknown_D[0x13];
    s32 field_20;
};

struct Overlay0072Object0034A690
{
    u8 unknown_0[0x38];
    s32 field_38;
};

struct Overlay0072Object0034BB10
{
    u8 unknown_0[0x20];
    s32 field_20;
    s32 field_24;
    u8 unknown_28[0x70];
    s32 field_98;
};

struct Overlay0072Object0034CF80
{
    u8 unknown_0[0x6C];
    u16 field_6C;
};

struct Overlay0072Object003494F0
{
    u8 unknown_0[0x20];
    unsigned __int128 field_20;
    u8 unknown_30[0x20];
    u8 field_50;
};

struct Overlay0072Object00358FC0
{
    u8 unknown_0[0x20];
    unsigned __int128 field_20;
    u8 unknown_30[0x20];
    u8 field_50;
};

struct Overlay0072Object00359000
{
    u8 unknown_0[0x30];
    unsigned __int128 field_30;
    u8 unknown_40[0x10];
    u8 field_50;
};

struct Overlay0072Object003590E0
{
    u8 unknown_0[0x40];
    unsigned __int128 field_40;
    u8 field_50;
};

struct Overlay0072Object00353710
{
    u8 unknown_0[0x20];
    float field_20;
    float field_24;
    float field_28;
    float field_2C;
    u8 unknown_30[0x20];
    u8 field_50;
};

struct Overlay0072Object00358FE0
{
    u8 unknown_0[0x30];
    float field_30;
    float field_34;
    float field_38;
    float field_3C;
    u8 unknown_40[0x10];
    u8 field_50;
};

struct Overlay0072Object00359210
{
    u8 unknown_0[0x4];
    s32 field_4;
    u8 field_8;
    u8 unknown_9[0x1];
    u16 field_A;
    u8 unknown_C[0x4];
    s32 field_10;
    u8 unknown_14[0x2C];
    float field_40;
    float field_44;
    float field_48;
    u8 unknown_4C[0x4];
    u8 field_50;
    u8 unknown_51[0xF];
    u8 field_60;
    u8 unknown_61[0x3B];
    s32 field_9C;
    u8 unknown_A0[0x8];
    u8 field_A8;
};

struct Overlay0072Object003594A0
{
    u8 unknown_0[0xD];
    u8 field_D;
};

struct Overlay0072Object00359600
{
    u8 unknown_0[0x24];
    s32 field_24;
    s8 field_28;
    u8 unknown_29[0xB];
    s32 field_34;
    u8 unknown_38[0x4];
    s32 field_3C;
    u8 field_40;
};

typedef struct
{
    u8 unknown_0[0x48];
    s32 field_48;
    s32 field_4C;
    s32 field_50;
    u8 unknown_54[0xAC];
} Overlay0072Record0035AF80;

typedef struct
{
    u8 unknown_0[0x14];
    Overlay0072Record0035AF80* field_14;
} Overlay0072Inner0035AF80;

struct Overlay0072Object0035AFC0
{
    u8 unknown_0[0x14];
    Overlay0072Inner0035AF80* field_14;
    u8 unknown_18[0x4];
    s16 field_1C;
    s16 field_1E;
    s16 field_20;
    s16 field_22;
    u8 unknown_24[0xC];
    s32 field_30;
    u8 field_34;
    u8 unknown_35[0x4];
    u8 field_39;
};

struct Overlay0072Nested00359C10
{
    u8 unknown_0[0x28];
    u8 field_28;
};

struct Overlay0072Nested00359C20
{
    u8 unknown_0[0x1250];
    s32 field_1250;
};

struct Overlay0072Object00359C10
{
    u8 unknown_0[0x14];
    struct Overlay0072Nested00359C10* field_14;
    struct Overlay0072Nested00359C20* field_18;
};

struct Overlay0072CtorObject0034D0E0
{
    void* table;
    u8 unknown_4[0x34];
    u8 state;
    u8 unknown_39[7];
    s32 field_40;
};

struct Overlay0072CtorObject0034DC00
{
    void* table;
    u8 unknown_4[0x34];
    u8 state;
};

struct Overlay0072CtorObject0034DB40
{
    void* table;
    u8 unknown_4[0x34];
    u8 state;
};

struct Overlay0072ListNode
{
    void* value;
    Overlay0072ListNode* next;
};

struct Overlay0072List
{
    Overlay0072ListNode* head;
    s32 count;
};

extern u8 D_50CD30[];
extern void* func_100AC0(s32 size, s32 flags);
extern void func_4C4960(void* object);
extern void func_464B10(void* object);
extern u8 D_172870[];
extern u8 D_172600[];
extern u8 D_1725D0[];
extern u8 D_1746A0[];
extern u8 D_174F20[];
extern u8 D_178750[];
extern void func_4C7FB0(Overlay0072CtorObject0034DB40* object, float x, float y, float z, float w);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003483C0);

s32 func_00348400(void* object)
{
    return 3;
}

void func_00348410(void* object)
{
}

void func_00348420(void* object)
{
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00348430);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003484A0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00348520);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00349280);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003492E0);

void func_003494F0(Overlay0072Object003494F0* object, const unsigned __int128* value)
{
    object->field_50 = 1;
    object->field_20 = *value;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00349510);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003495C0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00349620);

s32 func_00349670(Overlay0072Object00349670* object)
{
    return object->field_4;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00349680);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003496E0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00349840);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003498A0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00349950);

void func_00349AB0(Overlay0072Object00349AB0* object, u8 value)
{
    object->field_C = value;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00349AC0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00349B80);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00349C40);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00349FA0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034A000);

u8 func_0034A1D0(Overlay0072Object0034A1D0* object)
{
    return object->field_C;
}

s32 func_0034A1E0(Overlay0072Object0034A1D0* object)
{
    return object->field_20;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034A1F0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034A210);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034A230);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034A290);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034A3C0);

s32 func_0034A690(Overlay0072Object0034A690* object)
{
    return object->field_38;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034A6A0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034A700);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034A760);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034A8C0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034A920);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034A9A0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034AAB0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034AB70);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034AC30);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034AFB0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034B010);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034B070);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034B1D0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034B230);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034B2E0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034B440);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034B4A0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034B660);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034B800);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034B860);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034B8C0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034B920);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034BAA0);

void func_0034BB00(void* object)
{
}

s32 func_0034BB10(Overlay0072Object0034BB10* object)
{
    return object->field_24;
}

void func_0034BB20(Overlay0072Object0034BB10* object, s32 value)
{
    object->field_20 = value;
}

void func_0034BB30(Overlay0072Object0034BB10* object, s32 value)
{
    object->field_98 = value;
}

s32 func_0034BB40(Overlay0072Object0034BB10* object)
{
    return object->field_98;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034BB50);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034BC40);

void func_0034BD60(void* object)
{
}

void func_0034BD70(void* object)
{
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034BD80);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034BE20);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034C010);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034C460);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034C5D0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034C970);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034CA60);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034CAF0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034CBA0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034CCA0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034CD30);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034CDA0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034CE10);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034CEA0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034CF10);

void func_0034CF80(Overlay0072Object0034CF80* object, u16 value)
{
    object->field_6C = value;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034CF90);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034D070);

Overlay0072CtorObject0034D0E0* func_0034D0E0(Overlay0072CtorObject0034D0E0* object)
{
    func_4C4960(object);
    object->table = D_172870;
    object->field_40 = 0;
    object->state = 6;
    return object;
}

Overlay0072CtorObject0034D0E0* func_0034D120(Overlay0072CtorObject0034D0E0* object)
{
    func_4C4960(object);
    object->table = D_172600;
    object->field_40 = 0;
    object->state = 5;
    return object;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034D160);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034D1D0);

Overlay0072CtorObject0034D0E0* func_0034D230(Overlay0072CtorObject0034D0E0* object)
{
    func_4C4960(object);
    object->table = D_1725D0;
    object->field_40 = 0;
    object->state = 3;
    return object;
}

Overlay0072CtorObject0034D0E0* func_0034D270(Overlay0072CtorObject0034D0E0* object)
{
    func_4C4960(object);
    object->table = D_1746A0;
    object->field_40 = 0;
    object->state = 4;
    return object;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034D2B0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034D320);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034D3A0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034D5B0);

void func_0034D880(u8* object, void* unused, u8 value)
{
    object[0x45] = value;
    object[0xD5] = value;
    object[0x1E9] = value;
    object[0x3FD] = value;
    object[0x4FD] = value;
    object[0x5FD] = value;
    object[0x6FD] = value;
    object[0x7FD] = value;
    object[0x8FD] = value;
    object[0xA11] = value;
    object[0x2E9] = value;
    object[0xC39] = value;
    object[0xB25] = value;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034D8C0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034DA90);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034DAF0);

Overlay0072CtorObject0034DB40* func_0034DB40(Overlay0072CtorObject0034DB40* object)
{
    func_464B10(object);
    object->table = D_178750;
    object->state = 11;
    func_4C7FB0(object, 0.0f, 0.0f, 0.0f, 0.0f);
    return object;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034DBA0);

Overlay0072CtorObject0034DC00* func_0034DC00(Overlay0072CtorObject0034DC00* object)
{
    func_464B10(object);
    object->table = D_174F20;
    object->state = 13;
    return object;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034DC40);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034DC70);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034DD40);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034DED0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034DF30);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034DF60);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034E040);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034E1D0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034E230);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034E3B0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034E6D0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034E820);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034E860);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034E8A0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034E980);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034EBC0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034F280);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034F310);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034F370);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034F3D0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034F3F0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034F550);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034F760);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034F7D0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034F830);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034FA90);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00350070);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00350200);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00350260);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003504F0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003509D0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00350B60);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00350BC0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00350BF0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00350CC0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00350E40);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00350EA0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00350ED0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00350FA0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00351130);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00351190);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003511C0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00351470);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00351660);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003516C0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003516F0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003517C0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00351950);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003519B0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00351C60);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00351CF0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00351D40);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00352010);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003521D0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00352230);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00352440);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00352A80);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00352CE0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00352D40);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00352F10);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003533C0);

void func_00353710(Overlay0072Object00353710* object, float x, float y, float z)
{
    object->field_50 = 1;
    object->field_20 = x;
    object->field_24 = y;
    object->field_28 = z;
    object->field_2C = 1.0f;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00353730);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003537D0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00353810);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00353840);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00353970);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00353B00);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00353B60);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00353D00);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00353EC0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00354080);

void func_003540E0(void* object)
{
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003540F0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00354120);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003542B0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00354560);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003545C0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003547D0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003548E0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00354920);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00354960);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00354A50);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00354C20);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00355020);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00355080);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00355240);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00355410);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00355D50);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00355D70);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00355F70);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00355FD0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00355FF0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003560E0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003561D0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00356380);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003563E0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00356400);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00356460);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003564C0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00356840);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00356870);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003568C0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00356A40);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00356BF0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00356F60);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00356FC0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00357190);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00357320);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00357BC0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00357C20);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00357CA0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00357F60);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00357FC0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003583B0);

void func_003585A0(void* object)
{
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003585B0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00358600);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00358620);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00358C90);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00358D50);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00358E60);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00358EF0);

float func_00358F80(void* object)
{
    return 0.0f;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00358F90);

void func_00358FC0(Overlay0072Object00358FC0* object, const unsigned __int128* value)
{
    object->field_50 = 1;
    object->field_20 = *value;
}

void func_00358FE0(Overlay0072Object00358FE0* object, float x, float y, float z, float w)
{
    object->field_50 = 1;
    object->field_30 = x;
    object->field_34 = y;
    object->field_38 = z;
    object->field_3C = w;
}

void func_00359000(Overlay0072Object00359000* object, const unsigned __int128* value)
{
    object->field_50 = 1;
    object->field_30 = *value;
}

void func_00359020(Overlay0072Object00359000* object, const unsigned __int128* value)
{
    object->field_50 = 1;
    object->field_30 = *value;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00359040);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00359070);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003590A0);

void func_003590E0(Overlay0072Object003590E0* object, const unsigned __int128* value)
{
    object->field_50 = 1;
    object->field_40 = *value;
}

void func_00359100(Overlay0072Object003590E0* object, const unsigned __int128* value)
{
    object->field_50 = 1;
    object->field_40 = *value;
}

void func_00359120(Overlay0072Object00359210* object, float x, float y, float z)
{
    object->field_50 = 1;
    object->field_40 = x;
    object->field_44 = y;
    object->field_48 = z;
}

s32 func_00359140(void* object)
{
    return 0;
}

s32 func_00359150(float value)
{
    return value < 0.0f;
}

u8* func_00359170(void* object)
{
    return D_50CD30;
}

s32 func_00359180(void* object)
{
    return 0;
}

void func_00359190(void* object)
{
}

void func_003591A0(void* object)
{
}

void func_003591B0(void* object)
{
}

void func_003591C0(void* object)
{
}

float func_003591D0(void* object)
{
    return 0.0f;
}

void func_003591E0(void* object)
{
}

void func_003591F0(Overlay0072Object00359210* object)
{
    object->field_60 = object->field_A8;
}

void func_00359200(void* object)
{
}

void func_00359210(Overlay0072Object00359210* object, u8 value)
{
    object->field_8 = value;
}

u8 func_00359220(Overlay0072Object00359210* object)
{
    return object->field_8;
}

void func_00359230(Overlay0072Object00359210* object, u16 value)
{
    object->field_A = value;
}

u16 func_00359240(Overlay0072Object00359210* object)
{
    return object->field_A;
}

void func_00359250(Overlay0072Object00359210* object, s32 value)
{
    object->field_9C = value;
}

s32 func_00359260(Overlay0072Object00359210* object)
{
    return object->field_9C;
}

void func_00359270(Overlay0072Object00359210* object, s32 value)
{
    object->field_4 = value;
}

s32 func_00359280(Overlay0072Object00359210* object)
{
    return object->field_10;
}

void func_00359290(void* object)
{
}

void func_003592A0(void* object)
{
}

void func_003592B0(void* object)
{
}

void func_003592C0(void* object)
{
}

void func_003592D0(void* object)
{
}

void func_003592E0(void* object)
{
}

void func_003592F0(void* object)
{
}

void func_00359300(void* object)
{
}

void func_00359310(void* object)
{
}

void func_00359320(void* object)
{
}

void func_00359330(void* object)
{
}

void func_00359340(void* object)
{
}

void func_00359350(void* object)
{
}

void func_00359360(void* object)
{
}

void func_00359370(void* object)
{
}

void func_00359380(void* object)
{
}

void func_00359390(void* object)
{
}

void func_003593A0(void* object)
{
}

void func_003593B0(void* object)
{
}

void func_003593C0(void* object)
{
}

s32 func_003593D0(void* object)
{
    return 0;
}

s32 func_003593E0(void* object)
{
    return 0;
}

s32 func_003593F0(void* object)
{
    return 0;
}

s32 func_00359400(void* object)
{
    return 0;
}

s32 func_00359410(void* object)
{
    return 0;
}

s32 func_00359420(void* object)
{
    return 0;
}

s32 func_00359430(void* object)
{
    return 0;
}

s32 func_00359440(void* object)
{
    return 0;
}

s32 func_00359450(void* object)
{
    return 0;
}

s32 func_00359460(void* object)
{
    return 0;
}

s32 func_00359470(void* object)
{
    return 0;
}

void func_00359480(void* object)
{
}

void func_00359490(void* object)
{
}

u8 func_003594A0(Overlay0072Object003594A0* object)
{
    return object->field_D;
}

void func_003594B0(Overlay0072Object003594A0* object, u8 value)
{
    object->field_D = value;
}

void func_003594C0(void* object)
{
}

s32 func_003594D0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003594E0);

s32 func_00359600(Overlay0072Object00359600* object)
{
    return object->field_34;
}

u8 func_00359610(Overlay0072Object00359600* object)
{
    return object->field_40;
}

s32 func_00359620(Overlay0072Object00359600* object)
{
    return object->field_3C;
}

s32 func_00359630(void* object)
{
    return 4;
}

void func_00359640(Overlay0072Object00359600* object, s32 value)
{
    object->field_24 = value;
}

void func_00359650(Overlay0072Object00359600* object, u8 value)
{
    object->field_28 = value;
}

s8 func_00359660(Overlay0072Object00359600* object)
{
    return object->field_28;
}

void func_00359670(void* object)
{
}

s32 func_00359680(void* object)
{
    return 0;
}

void func_00359690(void* object)
{
}

void func_003596A0(void* object)
{
}

void func_003596B0(void* object)
{
}

s32 func_003596C0(void* object)
{
    return 0;
}

s32 func_003596D0(void* object)
{
    return 0;
}

s32 func_003596E0(void* object)
{
    return 0;
}

void func_003596F0(Overlay0072List* list, void* value)
{
    Overlay0072ListNode* node = (Overlay0072ListNode*)func_100AC0(8, 0);
    Overlay0072ListNode* cursor;

    if (node != 0)
    {
        node->value = value;
        node->next = 0;
        cursor = list->head;
        while (cursor->next != 0)
        {
            cursor = cursor->next;
        }
        cursor->next = node;
        list->count++;
    }
}

void func_00359780(Overlay0072List* list, void* value)
{
    Overlay0072ListNode* node = (Overlay0072ListNode*)func_100AC0(8, 0);
    Overlay0072ListNode* cursor;

    if (node != 0)
    {
        node->value = value;
        node->next = 0;
        cursor = list->head;
        while (cursor->next != 0)
        {
            cursor = cursor->next;
        }
        cursor->next = node;
        list->count++;
    }
}

Overlay0072ListNode* func_00359810(Overlay0072List* list, s32 index)
{
    Overlay0072ListNode* node = list->head->next;
    s32 i;

    for (i = 0; i < index; i++)
    {
        if (node == 0)
        {
            return 0;
        }
        node = node->next;
    }
    return node;
}

void func_00359850(Overlay0072List* list, void* value)
{
    Overlay0072ListNode* node = (Overlay0072ListNode*)func_100AC0(8, 0);
    Overlay0072ListNode* cursor;

    if (node != 0)
    {
        node->value = value;
        node->next = 0;
        cursor = list->head;
        while (cursor->next != 0)
        {
            cursor = cursor->next;
        }
        cursor->next = node;
        list->count++;
    }
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003598E0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003598F0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00359900);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00359910);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00359920);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00359930);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00359940);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00359950);

s32 func_00359960(void* object)
{
    return 2;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00359970);

u8 func_00359C10(Overlay0072Object00359C10* object)
{
    return object->field_14->field_28;
}

s32 func_00359C20(Overlay0072Object00359C10* object)
{
    s32 value = object->field_18->field_1250;
    if (value > 0)
    {
        return value;
    }
    return 0;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00359C50);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00359DA0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0035A010);

void func_0035ADA0(Overlay0072Object0035AFC0* object, u8 value, u8 other)
{
    if (value == 1)
    {
        object->field_1E = 0;
    }
    object->field_39 = other;
    object->field_34 = value;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0035ADD0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0035AE70);

void func_0035AF60(Overlay0072Object0035AFC0* object, s16 value)
{
    object->field_20 = 0;
    object->field_1E = value;
    object->field_22 = 0;
    object->field_39 = 0;
    object->field_34 = 0;
    object->field_30 = -1;
}

s32 func_0035AF80(Overlay0072Object0035AFC0* object)
{
    return object->field_14->field_14[object->field_1C].field_50;
}

s32 func_0035AFA0(Overlay0072Object0035AFC0* object)
{
    return object->field_14->field_14[object->field_1C].field_4C;
}

s16 func_0035AFC0(Overlay0072Object0035AFC0* object)
{
    return object->field_22;
}

s32 func_0035AFD0(Overlay0072Object0035AFC0* object, s16 index)
{
    return object->field_14->field_14[index].field_48;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0035AFF0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0035B0E0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0035B170);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0035B200);
