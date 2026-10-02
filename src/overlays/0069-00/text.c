#include "include_asm.h"
#include "overlays/0069-00/text.h"
#include "boot/resident_data.h"
#include "overlays/1067-00/text_0028E240.h"
#include "overlays/1067-00/text_0023B1D0.h"

typedef struct SkillVector4
{
    float x;
    float y;
    float z;
    float w;
} SkillVector4;

typedef struct RecordWithMethods
{
    void* methods;
} RecordWithMethods;

typedef struct State003620F0
{
    u8 unk00[0xE5];
    u8 flag;
} State003620F0;

typedef struct Mode003620F0
{
    u8 unk00[0x10];
    s8 mode;
} Mode003620F0;

typedef struct Record003620F0
{
    u8 unk00[0xA8];
    Record00363740* primary;
    Mode003620F0* mode;
    State003620F0* state;
} Record003620F0;

typedef struct Record003611B0
{
    u8 unk00[0x104];
    u8 unk104;
} Record003611B0;

typedef struct ListOwnerWithMethods
{
    void* head;
    u32 count;
    void* methods;
} ListOwnerWithMethods;

typedef struct StatusItem
{
    u8 unk00[0x3C];
    u8 unk3c;
    u8 unk3d[2];
    u8 unk3f;
    u8 unk40[0xBC];
    s32 unkfc;
} StatusItem;

typedef struct StatusOwner003534C0
{
    u8 unk00[0x108];
    StatusItem* unk108[7];
    u8 unk124[4];
    s32 unk128[6];
} StatusOwner003534C0;

typedef struct StatusOwner003580D0
{
    u8 unk00[0xD4];
    StatusItem* items[4];
} StatusOwner003580D0;

typedef struct Record003581B0Inner
{
    u8 unk00[0x12];
    u8 flag;
} Record003581B0Inner;

typedef struct Record003581B0
{
    u8 unk00[0xA8];
    Record003581B0Inner* inner;
    u8 unkac[0x48];
    u8 flag;
} Record003581B0;

typedef struct PacketBuffer0035DDE0
{
    u8* base;
    u32 unk04;
    u8* cursor;
    u8* unk0c;
    u32 capacity;
    u8 unk14;
    u8 unk15;
} PacketBuffer0035DDE0;

typedef struct Record0035E2A0
{
    u8 unk00[0xAC];
    FieldObject23B1D0* child;
} Record0035E2A0;

typedef struct Record0035BE50
{
    u8 unk00[0x44];
    FieldRecordSelection* selection;
} Record0035BE50;

typedef struct Record0035DDE0
{
    u8 unk00[8];
    PacketBuffer0035DDE0* buffer;
} Record0035DDE0;

typedef struct Record0035DE40
{
    u8 unk00[0x2C];
    void* methods;
} Record0035DE40;

typedef struct Record0035D4A0
{
    void* methods;
    u8 unk04[0x8C];
    void* secondary_methods;
    u8 unk94[0x2C];
    Record0035DE40 nested;
} Record0035D4A0;

typedef struct ListItem0035CCE0
{
    u8 unk00[0x3C];
    u8 unk3c;
    u8 unk3d[0x57];
    u32 unk94;
} ListItem0035CCE0;

typedef struct ListNode0035CCE0
{
    ListItem0035CCE0* value;
    struct ListNode0035CCE0* next;
} ListNode0035CCE0;

typedef struct ListOwner0035CCE0
{
    u8 unk00[0x2C];
    ListNode0035CCE0* head;
} ListOwner0035CCE0;

typedef struct Record00349DB0
{
    void* methods;
    u8 unk04[0x3C];
    u8 unk40;
} Record00349DB0;

typedef struct Record0034BC40
{
    void* methods;
    u8 unk04[0xC4];
    ListOwnerWithMethods nested;
} Record0034BC40;

typedef struct Record00351790
{
    void* methods;
    u8 unk04[0x20C];
    ListOwnerWithMethods nested;
} Record00351790;

typedef struct Record00355420
{
    void* methods;
    u8 unk04[0x3C];
    u8 unk40;
} Record00355420;

typedef struct Record00355490
{
    RecordWithMethods base;
    u8 unk04[0xC];
    void* methods;
} Record00355490;

typedef struct Record00355500
{
    void* methods;
    u8 unk04[0xD4];
    ListOwnerWithMethods first;
    ListOwnerWithMethods second;
} Record00355500;

typedef struct Record003610F0
{
    u8 unk00[0x38];
    void* methods;
} Record003610F0;

typedef struct Record00361060
{
    void* methods;
    u8 unk04[0x3C];
    Record003610F0 nested;
} Record00361060;

typedef struct Record00364810
{
    void* methods;
    u8 unk04[0xB8];
    u8 nested;
} Record00364810;

typedef struct Record0035D3E0
{
    u8 unk00[0x20];
    u32 unk20;
    u32 unk24;
    u32 unk28;
    float unk2c;
    u8 unk30[0x3C];
    u16 unk6c;
    u8 unk6e[0x46];
    u32 unkb4;
    u32 unkb8;
} Record0035D3E0;

extern FieldRecordSelection* func_0028E4D0(FieldRecordSelection* selection);
extern u64 D_4ED330[];
extern void func_11F140(PacketBuffer0035DDE0* buffer, u64 value);
extern u8 D_50CD30[];
extern u8 D_183C60[];
extern u8 D_183070[];
extern u8 D_183E60[];
extern u8 D_183570[];
extern u8 D_183970[];
extern u8 D_184160[];
extern u8 D_183F60[];
extern u8 D_184060[];
extern u8 D_182E40[];
extern u8 D_182F70[];
extern u8 D_182F50[];
extern u8 D_182F60[];
extern u8 D_178A70[];
extern u8 D_183370[];
extern u8 D_183670[];
extern u8 D_183770[];
extern u8 D_183870[];
extern u8 D_183A70[];
extern u8 D_183E50[];
extern u8 D_183DB0[];
extern u8 D_183E24[];
extern u8 D_183E3C[];
extern void func_2CEAF0(void* object, s32 flag);
extern void* func_2BC410(void* object, s16 flag);
extern void* func_002BC280(void* object, s16 flag);
extern void func_100B40(void* object);
extern void func_44B210(void* record);
extern u8 D_183C48[];
extern u8 D_183C38[];
extern u8 D_184258[];
extern void func_0035C810(ListOwnerWithMethods* record);
extern void func_0035CA60(ListOwnerWithMethods* record);
extern void func_00364B70(ListOwnerWithMethods* record);
extern u8 D_175110[];
extern u8 D_175030[];
extern u8 D_175054[];
extern void* func_4618F0(void* record, s16 flag);
extern void* func_4C48B0(void* record, s16 flag);
extern u8 D_183170[];
extern u8 D_183270[];
extern u8 D_159FE0[];
extern u8 D_183470[];
extern u8 D_183DA0[];
extern void func_00364960(void* object, s32 flag);
extern void func_44B110(void* object, s32 arg1, s32 arg2, void* arg3, float value, s32 flag);
extern void* func_100AC0(u32 size, s32 flags);
extern void func_2CEBE0(void* object);
extern void func_003648E0(void* object);
extern void func_0035C8D0(void* object);
extern void func_00358200(void* object);
extern void func_4CE4C0(void* destination, const void* source);

static inline RecordWithMethods* release_record182f50(RecordWithMethods* record, s16 flag);
static inline RecordWithMethods* release_record182f60(RecordWithMethods* record, s16 flag);
static inline Record003610F0* release_record183da0(Record003610F0* record, s16 flag);
static inline Record0035DE40* release_record183e50(Record0035DE40* record, s16 flag);

/**
 * @brief Reset the base record's method table and optionally free its storage.
 * @param record Record to release, or null.
 * @param flag Positive values release the record's storage.
 * @return Original record pointer.
 */
static inline RecordWithMethods* release_record182f50(RecordWithMethods* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_182F50;
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

/**
 * @brief Release the derived record's base state and optionally free its storage.
 * @param record Record to release, or null.
 * @param flag Positive values release the record's storage.
 * @return Original record pointer.
 */
static inline RecordWithMethods* release_record182f60(RecordWithMethods* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_182F60;
        release_record182f50(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

/**
 * @brief Release the nested record state and optionally free its storage.
 * @param record Record to release, or null.
 * @param flag Positive values release the record's storage.
 * @return Original record pointer.
 */
static inline Record003610F0* release_record183da0(Record003610F0* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_183DA0;
        func_4618F0(record, -1);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

/**
 * @brief Release the nested record state and optionally free its storage.
 * @param record Record to release, or null.
 * @param flag Positive values release the record's storage.
 * @return Original record pointer.
 */
static inline Record0035DE40* release_record183e50(Record0035DE40* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_183E50;
        func_2BC410(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003483C0);

void func_00348400(u8* object, u8 value)
{
    object[0xC] = value;
}

u8 func_00348410(u8* object)
{
    return object[0xC];
}

void func_00348420(u8* object, u8 value)
{
    object[0x8] = value;
}

u8 func_00348430(u8* object)
{
    return object[0x8];
}

void func_00348440(u8* object, u16 value)
{
    *(u16*)(object + 0xA) = value;
}

u16 func_00348450(u8* object)
{
    return *(u16*)(object + 0xA);
}

void func_00348460(u8* object, u32 value)
{
    *(u32*)(object + 0x98) = value;
}

u32 func_00348470(u8* object)
{
    return *(u32*)(object + 0x98);
}

void func_00348480(u8* object, u32 value)
{
    *(u32*)(object + 0x9C) = value;
}

u32 func_00348490(u8* object)
{
    return *(u32*)(object + 0x9C);
}

void func_003484A0(u8* object, u32 value)
{
    *(u32*)(object + 0x4) = value;
}

u32 func_003484B0(u8* object)
{
    return *(u32*)(object + 0x4);
}

u32 func_003484C0(u8* object)
{
    return *(u32*)(object + 0x10);
}

void func_003484D0(void* object)
{
}

void func_003484E0(void* object)
{
}

void func_003484F0(void* object)
{
}

void func_00348500(void* object)
{
}

void func_00348510(void* object)
{
}

void func_00348520(void* object)
{
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

s32 func_00348610(void* object)
{
    return 0;
}

s32 func_00348620(void* object)
{
    return 0;
}

s32 func_00348630(void* object)
{
    return 0;
}

s32 func_00348640(void* object)
{
    return 0;
}

s32 func_00348650(void* object)
{
    return 0;
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

void func_003486D0(void* object)
{
}

void func_003486E0(void* object)
{
}

u8 func_003486F0(u8* object)
{
    return object[0xD];
}

void func_00348700(u8* object, u8 value)
{
    object[0xD] = value;
}

void func_00348710(void* object)
{
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00348720);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00348CB0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00348D10);

RecordWithMethods* func_00349840(RecordWithMethods* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_182E40;
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003498A0);

void func_00349920(u8* object, s32 mode)
{
    if (mode == 0)
    {
        (*(u8**)(object + 0xA8))[0x3F] = 0;
        (*(u8**)(object + 0xB8))[0x3F] = 0;
        (*(u8**)(object + 0xC0))[0x3F] = 0;
        (*(u8**)(object + 0xAC))[0x3F] = 0;
        (*(u8**)(object + 0xB0))[0x3F] = 0;
        (*(u8**)(object + 0xB4))[0x3F] = 0;
        (*(u8**)(object + 0xBC))[0x3F] = 0;
    }
    else if (mode > 0)
    {
        (*(u8**)(object + 0xAC))[0x3F] = 1;
        (*(u8**)(object + 0xB0))[0x3F] = 0;
    }
    else
    {
        (*(u8**)(object + 0xAC))[0x3F] = 0;
        (*(u8**)(object + 0xB0))[0x3F] = 1;
    }
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003499B0);

Record00349DB0* func_00349DB0(Record00349DB0* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_175110;
        func_4618F0(&record->unk40, -1);
        func_4C48B0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

RecordWithMethods* func_00349E20(RecordWithMethods* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_182F70;
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00349E80);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00349F30);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034A130);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034A2B0);

s32 func_0034A560(void* object)
{
    return 0;
}

s32 func_0034A570(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034A580);

void func_0034A640(u8* object, u32 value)
{
    *(u32*)(object + 0x20) = value;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034A650);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034AF00);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034AF90);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034B090);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034B190);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034B2C0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034B3F0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034B720);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034BA30);

Record0034BC40* func_0034BC40(Record0034BC40* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_183070;
        func_0035C950(&record->nested, -1);
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

u8* func_0034BCB0(u8* object)
{
    func_2CEBE0(object);
    *(u32*)object = (u32)D_183070;
    func_0035C8D0(object + 0xC8);
    *(u32*)(object + 0xA8) = 0;
    *(u32*)(object + 0xB0) = 0;
    *(u32*)(object + 0xC0) = 0;
    *(u32*)(object + 0xAC) = 0;
    *(u32*)(object + 0xB4) = 0;
    *(u32*)(object + 0xC4) = 0;
    *(s16*)(object + 0xB8) = -1;
    *(u32*)(object + 0xBC) = 0;
    *(u32*)(object + 0xE8) = 0;
    *(u32*)(object + 0xEC) = 0;
    *(u32*)(object + 0xF0) = 0;
    *(u32*)(object + 0xF4) = 0;
    *(u32*)(object + 0xE0) = 0;
    *(u32*)(object + 0xE4) = 0;
    *(u8*)(object + 0xF8) = 0;
    return object;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034BD30);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034BEE0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034C060);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034C110);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034C1F0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034C320);

u32 func_0034C520(u8* object)
{
    return *(u32*)(object + 0x20);
}

s32 func_0034C530(void* object)
{
    return 0;
}

s32 func_0034C540(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034C550);

u32 func_0034C7C0(u8* object)
{
    return *(u32*)(object + 0x44);
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034C7D0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034DA70);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034DCE0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034DF00);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034E0B0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034E260);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034E380);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034F1A0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034FB40);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034FC30);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003505C0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003506B0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00350890);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00351090);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00351360);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00351490);

Record00351790* func_00351790(Record00351790* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_183170;
        func_0035C700(&record->nested, -1);
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00351800);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00351980);

RecordWithMethods* func_00351A60(RecordWithMethods* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_183270;
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00351AC0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00351B30);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00351BE0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003521C0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00352240);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003522C0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003523A0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00352630);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003527A0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00352920);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00352A90);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00352B30);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00352C00);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00353040);

RecordWithMethods* func_00353380(RecordWithMethods* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_183370;
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003533E0);

s32 func_003534C0(StatusOwner003534C0* owner, s32 mode)
{
    s32 sum = 0;
    s32 i;
    owner->unk108[0]->unk3f = mode;
    if (mode != 0)
    {
        for (i = 0; i < 6; i++)
        {
            s32 value = owner->unk128[i];
            StatusItem* item = owner->unk108[i + 1];
            item->unkfc = value;
            item->unk3c = 1;
            if (value == -1)
            {
                owner->unk108[i + 1]->unk3f = 0;
                value = 0;
            }
            else
            {
                owner->unk108[i + 1]->unk3f = 1;
            }
            sum += value;
        }
    }
    else
    {
        for (i = 0; i < 6; i++)
        {
            owner->unk108[i + 1]->unk3f = 0;
        }
    }
    return sum;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00353570);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00353670);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00353720);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003538A0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003538F0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003539F0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00353B40);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00353CA0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00353DC0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00353EE0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00354060);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00354190);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003547C0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00354D80);

Record00355420* func_00355420(Record00355420* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_159FE0;
        func_4618F0(&record->unk40, -1);
        func_4C48B0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

Record00355490* func_00355490(Record00355490* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_178A70;
        release_record182f60(&record->base, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

Record00355500* func_00355500(Record00355500* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_183470;
        func_0035C950(&record->second, -1);
        func_0035C950(&record->first, -1);
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00355580);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003556B0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003558B0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003559F0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00355CA0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00355D90);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00355E80);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00355FD0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00356130);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00356220);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00356CB0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00356EE0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00356F80);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00357000);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00357230);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003572D0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00357350);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003573D0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003575A0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00357BF0);

RecordWithMethods* func_00357E80(RecordWithMethods* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_183570;
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

u8* func_00357EE0(u8* object)
{
    func_2CEBE0(object);
    *(u32*)object = (u32)D_183570;
    *(u32*)(object + 0xA8) = 0;
    *(u32*)(object + 0xAC) = 0;
    *(u32*)(object + 0xB0) = 0;
    *(u32*)(object + 0xB4) = 0;
    *(float*)(object + 0xB8) = 32.0f;
    *(float*)(object + 0xBC) = 62.0f;
    *(u32*)(object + 0xC0) = 0;
    *(u32*)(object + 0xC4) = 0;
    *(u32*)(object + 0xC8) = 0;
    *(u32*)(object + 0xCC) = 0;
    *(u8*)(object + 0x100) = 0;
    *(u32*)(object + 0xD0) = 0;
    *(u32*)(object + 0xE0) = 0;
    *(u32*)(object + 0xF0) = 0;
    *(u32*)(object + 0xD4) = 0;
    *(u32*)(object + 0xE4) = 0;
    *(u32*)(object + 0xF4) = 0;
    *(u32*)(object + 0xD8) = 0;
    *(u32*)(object + 0xE8) = 0;
    *(u32*)(object + 0xF8) = 0;
    *(u32*)(object + 0xDC) = 0;
    *(u32*)(object + 0xEC) = 0;
    *(u32*)(object + 0xFC) = 0;
    return object;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00357F80);

RecordWithMethods* func_00358070(RecordWithMethods* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_183670;
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

void func_003580D0(StatusOwner003580D0* owner, s32 first, s32 second, s32 third)
{
    if (second == -1)
    {
        owner->items[1]->unk3f = 0;
    }
    else
    {
        StatusItem* item = owner->items[1];
        item->unkfc = second - 1;
        item->unk3c = 1;
        owner->items[1]->unk3f = 1;
    }
    if (first == -1)
    {
        owner->items[0]->unk3f = 0;
    }
    else
    {
        StatusItem* item = owner->items[0];
        item->unkfc = first;
        item->unk3c = 1;
        owner->items[0]->unk3f = 1;
    }
    if (third == -1)
    {
        owner->items[2]->unk3f = 0;
        owner->items[3]->unk3f = 0;
    }
    else if (first == 10)
    {
        owner->items[2]->unk3f = 0;
        owner->items[3]->unk3f = 1;
    }
    else
    {
        StatusItem* item = owner->items[2];
        item->unkfc = third;
        item->unk3c = 1;
        owner->items[2]->unk3f = 1;
        owner->items[3]->unk3f = 0;
    }
}

void func_003581B0(void* object)
{
    Record003581B0* record = (Record003581B0*)object;
    if (record->flag == 1)
    {
        if (record->inner->flag == 1)
        {
            func_00358200(record);
            record->flag = 0;
        }
    }
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00358200);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00358310);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00358410);

RecordWithMethods* func_003591A0(RecordWithMethods* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_183770;
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00359200);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003592E0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00359340);

void func_00359480(void* object)
{
}

u32 func_00359490(u8* object)
{
    return *(u32*)(object + 0x24);
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003594A0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003595E0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00359730);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00359870);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00359D80);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00359E30);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00359EE0);

RecordWithMethods* func_0035A500(RecordWithMethods* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_183870;
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035A560);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035A650);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035A6E0);

RecordWithMethods* func_0035AB60(RecordWithMethods* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_183970;
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

u8* func_0035ABC0(u8* object)
{
    func_2CEBE0(object);
    *(u32*)object = (u32)D_183970;
    *(u32*)(object + 0xA8) = 0;
    *(u32*)(object + 0xAC) = 0;
    *(u8*)(object + 0xB0) = 0xFF;
    *(u8*)(object + 0xB4) = 0;
    *(u16*)(object + 0xB2) = 0;
    *(float*)(object + 0xB8) = -96.0f;
    *(u32*)(object + 0xBC) = 0;
    *(u32*)(object + 0xC0) = 0;
    *(u32*)(object + 0xC4) = 0;
    *(u32*)(object + 0xC8) = 0;
    *(u32*)(object + 0xCC) = 0;
    *(u32*)(object + 0xD0) = 0;
    *(u32*)(object + 0xD4) = 1;
    return object;
}

void func_0035AC40(void* object)
{
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035AC50);

RecordWithMethods* func_0035AEA0(RecordWithMethods* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_183A70;
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035AF00);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035B440);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035B4B0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035B4E0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035BD90);

s32 func_0035BE50(Record0035BE50* record)
{
    FieldRecordSelection* selection = func_100AC0(24, 0);
    if (selection != 0)
    {
        selection = func_0028E4D0(selection);
    }
    record->selection = selection;
    if (record->selection == 0)
    {
        return 0;
    }
    return (u8)func_0028E3D0(record->selection) != 0;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035BEC0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035BF70);

void func_0035C030(void* object)
{
}

void func_0035C040(void* object)
{
}

RecordWithMethods* func_0035C050(RecordWithMethods* record, s16 flag)
{
    return release_record182f50(record, flag);
}

RecordWithMethods* func_0035C0A0(RecordWithMethods* record, s16 flag)
{
    return release_record182f60(record, flag);
}

s32 func_0035C100(void* object)
{
    return 3;
}

void func_0035C110(void* object)
{
}

void func_0035C120(void* object)
{
}

void func_0035C130(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x20) = *value;
}

void func_0035C150(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x20) = *value;
}

void func_0035C170(u8* object, float x, float y, float z)
{
    object[0x50] = 1;
    *(float*)(object + 0x20) = x;
    *(float*)(object + 0x24) = y;
    *(float*)(object + 0x28) = z;
    *(float*)(object + 0x2C) = 1.0f;
}

void func_0035C190(u8* object, float x, float y, float z, float w)
{
    object[0x50] = 1;
    *(float*)(object + 0x30) = x;
    *(float*)(object + 0x34) = y;
    *(float*)(object + 0x38) = z;
    *(float*)(object + 0x3C) = w;
}

void func_0035C1B0(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x30) = *value;
}

void func_0035C1D0(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x30) = *value;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035C1F0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035C220);

void func_0035C250(u8* object, float x, float y, float z)
{
    SkillVector4 value;
    object[0x50] = 1;
    value.x = x;
    value.y = y;
    value.z = z;
    value.w = 1.0f;
    func_4CE4C0(object + 0x30, &value);
}

void func_0035C290(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x40) = *value;
}

void func_0035C2B0(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x40) = *value;
}

void func_0035C2D0(u8* object, float x, float y, float z)
{
    object[0x50] = 1;
    *(float*)(object + 0x40) = x;
    *(float*)(object + 0x44) = y;
    *(float*)(object + 0x48) = z;
}

s32 func_0035C2F0(void* object)
{
    return 0;
}

s32 func_0035C300(float value)
{
    return value < 0.0f;
}

u8* func_0035C320(void)
{
    return D_50CD30;
}

s32 func_0035C330(void* object)
{
    return 0;
}

void func_0035C340(void* object)
{
}

void func_0035C350(u8* object, u32 value)
{
    *(u32*)(object + 0x24) = value;
}

void func_0035C360(u8* object, u8 value)
{
    object[0x28] = value;
}

s8 func_0035C370(u8* object)
{
    return ((s8*)object)[0x28];
}

s32 func_0035C380(void* object)
{
    return 0;
}

s32 func_0035C390(void* object)
{
    return 0;
}

void func_0035C3A0(void* object)
{
}

void func_0035C3B0(void* object)
{
}

void func_0035C3C0(void* object)
{
}

void func_0035C3D0(void* object)
{
}

s32 func_0035C3E0(void* object)
{
    return 0;
}

s32 func_0035C3F0(void* object)
{
    return 0;
}

s32 func_0035C400(void* object)
{
    return 0;
}

s32 func_0035C410(void* object)
{
    return 4;
}

u8 func_0035C420(u8* object)
{
    return object[0x40];
}

u32 func_0035C430(u8* object)
{
    return *(u32*)(object + 0x3C);
}

void func_0035C440(SkillList* list, void* value)
{
    SkillListNode* node = (SkillListNode*)func_100AC0(8, 0);
    if (node != 0)
    {
        SkillListNode* current;
        SkillListNode* next;
        node->value = value;
        node->next = 0;
        current = list->head;
        next = current->next;
        while (next != 0)
        {
            current = next;
            next = next->next;
        }
        current->next = node;
        list->count++;
    }
}

void func_0035C4D0(SkillList* list, void* value)
{
    SkillListNode* node = (SkillListNode*)func_100AC0(8, 0);
    if (node != 0)
    {
        SkillListNode* current;
        SkillListNode* next;
        node->value = value;
        node->next = 0;
        current = list->head;
        next = current->next;
        while (next != 0)
        {
            current = next;
            next = next->next;
        }
        current->next = node;
        list->count++;
    }
}

void func_0035C560(SkillList* list, void* value)
{
    SkillListNode* node = (SkillListNode*)func_100AC0(8, 0);
    if (node != 0)
    {
        SkillListNode* current;
        SkillListNode* next;
        node->value = value;
        node->next = 0;
        current = list->head;
        next = current->next;
        while (next != 0)
        {
            current = next;
            next = next->next;
        }
        current->next = node;
        list->count++;
    }
}

void func_0035C5F0(SkillList* list, void* value)
{
    SkillListNode* node = (SkillListNode*)func_100AC0(8, 0);
    if (node != 0)
    {
        SkillListNode* current;
        SkillListNode* next;
        node->value = value;
        node->next = 0;
        current = list->head;
        next = current->next;
        while (next != 0)
        {
            current = next;
            next = next->next;
        }
        current->next = node;
        list->count++;
    }
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035C680);

ListOwnerWithMethods* func_0035C700(ListOwnerWithMethods* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_183C48;
        func_0035C810(record);
        if (record->head != 0)
        {
            func_100B40(record->head);
            record->head = 0;
        }
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

void func_0035C780(SkillList* list, void* value)
{
    SkillListNode* node = (SkillListNode*)func_100AC0(8, 0);
    if (node != 0)
    {
        SkillListNode* current;
        SkillListNode* next;
        node->value = value;
        node->next = 0;
        current = list->head;
        next = current->next;
        while (next != 0)
        {
            current = next;
            next = next->next;
        }
        current->next = node;
        list->count++;
    }
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035C810);

SkillListNode* func_0035C890(SkillList* list, s32 index)
{
    SkillListNode* node = list->head->next;
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

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035C8D0);

ListOwnerWithMethods* func_0035C950(ListOwnerWithMethods* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_183C38;
        func_0035CA60(record);
        if (record->head != 0)
        {
            func_100B40(record->head);
            record->head = 0;
        }
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

void func_0035C9D0(SkillList* list, void* value)
{
    SkillListNode* node = (SkillListNode*)func_100AC0(8, 0);
    if (node != 0)
    {
        SkillListNode* current;
        SkillListNode* next;
        node->value = value;
        node->next = 0;
        current = list->head;
        next = current->next;
        while (next != 0)
        {
            current = next;
            next = next->next;
        }
        current->next = node;
        list->count++;
    }
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CA60);

SkillListNode* func_0035CAE0(SkillList* list, s32 index)
{
    SkillListNode* node = list->head->next;
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

void func_0035CB20(SkillList* list, void* value)
{
    SkillListNode* node = (SkillListNode*)func_100AC0(8, 0);
    if (node != 0)
    {
        SkillListNode* current;
        SkillListNode* next;
        node->value = value;
        node->next = 0;
        current = list->head;
        next = current->next;
        while (next != 0)
        {
            current = next;
            next = next->next;
        }
        current->next = node;
        list->count++;
    }
}

void func_0035CBB0(SkillList* list, void* value)
{
    SkillListNode* node = (SkillListNode*)func_100AC0(8, 0);
    if (node != 0)
    {
        SkillListNode* current;
        SkillListNode* next;
        node->value = value;
        node->next = 0;
        current = list->head;
        next = current->next;
        while (next != 0)
        {
            current = next;
            next = next->next;
        }
        current->next = node;
        list->count++;
    }
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CC40);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CC50);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CC60);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CC70);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CC80);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CC90);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CCA0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CCB0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CCC0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CCD0);

void func_0035CCE0(void* object, s16 selected)
{
    ListOwner0035CCE0* owner = (ListOwner0035CCE0*)object;
    s32 index = 0;
    ListNode0035CCE0* node = owner->head->next;
    while (node != 0)
    {
        ListItem0035CCE0* item = node->value;
        if (index == selected)
        {
            item->unk94 = 0x288080;
            item->unk3c = 1;
        }
        else
        {
            item->unk94 = 0x808080;
            item->unk3c = 1;
        }
        node = node->next;
        index++;
    }
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CD50);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CDB0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CDF0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CE30);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CEB0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CF30);

RecordWithMethods* func_0035D2A0(RecordWithMethods* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_183C60;
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

u8* func_0035D300(u8* object)
{
    func_2CEBE0(object);
    *(u32*)object = (u32)D_183C60;
    *(u32*)(object + 0xA8) = 0;
    *(s16*)(object + 0xAC) = -1;
    return object;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035D340);

s32 func_0035D3E0(Record0035D3E0* record, s32 arg1, s32 arg2, void* arg3, float first, float second, float third)
{
    record->unk6c = 0x6006;
    record->unk20 = 0;
    record->unk24 = 0;
    record->unk28 = 0;
    record->unk2c = 1.0f;
    func_44B110(record, arg1, arg2, arg3, third, 0);
    record->unkb4 = 0;
    record->unkb8 = 0;
    return 1;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035D440);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035D460);

Record0035D4A0* func_0035D4A0(Record0035D4A0* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_183DB0;
        record->secondary_methods = D_183E24;
        record->nested.methods = D_183E3C;
        release_record183e50(&record->nested, 0);
        func_002BC280(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035D540);

void func_0035DDE0(Record0035DDE0* record)
{
    PacketBuffer0035DDE0* buffer = record->buffer;
    if (buffer != 0)
    {
        buffer->cursor = buffer->base + 64;
        buffer->unk0c = buffer->cursor;
        buffer->unk15 = 0;
        func_11F140(buffer, D_4ED330[0]);
        func_0035D540(record);
    }
}

Record0035DE40* func_0035DE40(Record0035DE40* record, s16 flag)
{
    return release_record183e50(record, flag);
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035DEA0);

void func_0035E2A0(Record0035E2A0* record)
{
    FieldObject23B1D0* child = record->child;
    s32 inactive = !child->flag75;
    if (inactive == 0)
    {
        s32 index = child->selected - 1;
        if (index < 0)
        {
            index = 7;
        }
        func_0023B1D0(child, index, 0);
    }
}

void func_0035E2F0(Record0035E2A0* record)
{
    FieldObject23B1D0* child = record->child;
    s32 inactive = !child->flag75;
    if (inactive == 0)
    {
        s32 index = child->selected + 1;
        if (index >= 8)
        {
            index = 0;
        }
        func_0023B1D0(child, index, 0);
    }
}

void func_0035E340(Record0035E2A0* record)
{
    FieldObject23B1D0* child = record->child;
    s32 inactive = !child->flag75;
    if (inactive == 0)
    {
        s32 index = child->selected;
        switch (index)
        {
        case 0:
            index = 3;
            break;
        case 1:
            index = 5;
            break;
        case 2:
            index = 6;
            break;
        default:
            return;
        }
        func_0023B1D0(child, index, 0);
    }
}

void func_0035E3C0(Record0035E2A0* record)
{
    FieldObject23B1D0* child = record->child;
    s32 inactive = !child->flag75;
    if (inactive == 0)
    {
        s32 index = child->selected;
        switch (index)
        {
        case 3:
            index = 0;
            break;
        case 4:
            index = 1;
            break;
        case 5:
            index = 1;
            break;
        case 6:
            index = 2;
            break;
        case 7:
            index = 2;
            break;
        default:
            return;
        }
        func_0023B1D0(child, index, 0);
    }
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035E470);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035E5C0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035FA20);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035FAA0);

Record00361060* func_00361060(Record00361060* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_175030;
        record->nested.methods = D_175054;
        release_record183da0(&record->nested, -1);
        func_4C48B0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

Record003610F0* func_003610F0(Record003610F0* record, s16 flag)
{
    return release_record183da0(record, flag);
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00361150);

void func_003611B0(Record003611B0* record)
{
    record->unk104 = 1;
    func_44B210(record);
    func_0011ED90(D_001B65F4, record);
}

u8* func_003611F0(u8* object)
{
    func_2CEBE0(object);
    *(u32*)object = (u32)D_183E60;
    func_003648E0(object + 0xBC);
    *(u32*)(object + 0xA8) = 0;
    *(u32*)(object + 0xAC) = 0;
    *(u32*)(object + 0xB0) = 0;
    *(u32*)(object + 0xB4) = 0;
    *(u32*)(object + 0xB8) = 0;
    *(u32*)(object + 0x208) = 0;
    return object;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00361250);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003619C0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00361B90);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00361D60);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00361E50);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00361F30);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00362010);

s32 func_003620F0(Record003620F0* record)
{
    u8 inactive = !record->state->flag;
    Record00363740* primary;
    if (inactive == 1)
    {
        return 0;
    }
    primary = record->primary;
    if (primary == 0)
    {
        return 0;
    }
    if (record->mode->mode < 2)
    {
        return 0;
    }
    return func_00363740(primary, 1);
}

s32 func_00362170(Record003620F0* record)
{
    u8 inactive = !record->state->flag;
    Record00363740* primary;
    if (inactive == 1)
    {
        return 0;
    }
    primary = record->primary;
    if (primary == 0)
    {
        return 0;
    }
    if (record->mode->mode < 2)
    {
        return 0;
    }
    return func_00363740(primary, 0);
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003621F0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00362210);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00362500);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00362650);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003629E0);

u8* func_00362F70(u8* object)
{
    func_2CEBE0(object);
    *(u32*)object = (u32)D_183F60;
    *(u32*)(object + 0xAC) = 0;
    *(u32*)(object + 0xB0) = 0;
    *(u32*)(object + 0xA8) = 0;
    *(u32*)(object + 0x1A8) = 0;
    return object;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00362FC0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00363190);

RecordWithMethods* func_003635B0(RecordWithMethods* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_184060;
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

u8* func_00363610(u8* object)
{
    func_2CEBE0(object);
    *(u32*)object = (u32)D_184060;
    *(u32*)(object + 0xA8) = 0;
    *(u32*)(object + 0xAC) = 0;
    *(u32*)(object + 0xB0) = 0;
    *(u32*)(object + 0xB4) = 0;
    *(u32*)(object + 0xB8) = 0;
    *(u32*)(object + 0xBC) = 0;
    return object;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00363660);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00363740);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00363890);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00363AE0);

RecordWithMethods* func_00364610(RecordWithMethods* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_184160;
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

u8* func_00364670(u8* object)
{
    func_2CEBE0(object);
    *(u32*)object = (u32)D_184160;
    *(u32*)(object + 0xA8) = 0;
    *(u32*)(object + 0xAC) = 0;
    *(u32*)(object + 0xB0) = 0;
    *(u32*)(object + 0xB4) = 0;
    *(u32*)(object + 0xC4) = 0;
    *(u32*)(object + 0xC0) = 0;
    *(u32*)(object + 0xD4) = 0;
    *(u32*)(object + 0xD8) = 0;
    *(u8*)(object + 0x114) = 0;
    *(u32*)(object + 0xDC) = 0;
    *(u32*)(object + 0xE0) = 0;
    *(u8*)(object + 0x115) = 0;
    *(u32*)(object + 0xE4) = 0;
    *(u32*)(object + 0xE8) = 0;
    *(u8*)(object + 0x116) = 0;
    *(u32*)(object + 0xEC) = 0;
    *(u32*)(object + 0xF0) = 0;
    *(u8*)(object + 0x117) = 0;
    *(u32*)(object + 0xF4) = 0;
    *(u32*)(object + 0xF8) = 0;
    *(u8*)(object + 0x118) = 0;
    *(u32*)(object + 0xFC) = 0;
    *(u32*)(object + 0x100) = 0;
    *(u8*)(object + 0x119) = 0;
    *(u32*)(object + 0x104) = 0;
    *(u32*)(object + 0x108) = 0;
    *(u8*)(object + 0x11A) = 0;
    *(u32*)(object + 0x10C) = 0;
    *(u32*)(object + 0x110) = 0;
    *(u8*)(object + 0x11B) = 0;
    *(u8*)(object + 0x11C) = 0;
    return object;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00364720);

void func_003647E0(void* object)
{
}

s32 func_003647F0(void* object)
{
    return 14;
}

void func_00364800(u8* object)
{
    object[0x60] = object[0xa8];
}

Record00364810* func_00364810(Record00364810* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_183E60;
        func_00364960(&record->nested, -1);
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

RecordWithMethods* func_00364880(RecordWithMethods* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_183F60;
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003648E0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00364960);

void func_003649E0(SkillList* list, void* value)
{
    SkillListNode* node = (SkillListNode*)func_100AC0(8, 0);
    if (node != 0)
    {
        SkillListNode* current;
        SkillListNode* next;
        node->value = value;
        node->next = 0;
        current = list->head;
        next = current->next;
        while (next != 0)
        {
            current = next;
            next = next->next;
        }
        current->next = node;
        list->count++;
    }
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00364A70);

ListOwnerWithMethods* func_00364AF0(ListOwnerWithMethods* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_184258;
        func_00364B70(record);
        if (record->head != 0)
        {
            func_100B40(record->head);
            record->head = 0;
        }
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00364B70);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00364BF0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00364CA0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00364D30);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00364D40);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00364D50);
