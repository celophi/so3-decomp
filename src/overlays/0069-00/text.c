#include "include_asm.h"
#include "overlays/0069-00/text.h"

typedef struct SkillVector4
{
    float x;
    float y;
    float z;
    float w;
} SkillVector4;

extern u8 D_50CD30[];
extern u8 D_183C60[];
extern u8 D_183070[];
extern u8 D_183E60[];
extern u8 D_183570[];
extern u8 D_183970[];
extern u8 D_184160[];
extern u8 D_183F60[];
extern u8 D_184060[];
extern void func_2CEBE0(void* object);
extern void func_003648E0(void* object);
extern void func_0035C8D0(void* object);
extern void func_4CE4C0(void* destination, const void* source);

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

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00349840);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003498A0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00349920);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003499B0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00349DB0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00349E20);

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

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0034BC40);

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

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00351790);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00351800);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00351980);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00351A60);

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

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00353380);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003533E0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003534C0);

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

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00355420);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00355490);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00355500);

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

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00357E80);

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

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00358070);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003580D0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003581B0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00358200);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00358310);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00358410);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003591A0);

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

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035A500);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035A560);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035A650);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035A6E0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035AB60);

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

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035AEA0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035AF00);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035B440);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035B4B0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035B4E0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035BD90);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035BE50);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035BEC0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035BF70);

void func_0035C030(void* object)
{
}

void func_0035C040(void* object)
{
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035C050);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035C0A0);

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

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035C440);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035C4D0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035C560);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035C5F0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035C680);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035C700);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035C780);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035C810);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035C890);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035C8D0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035C950);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035C9D0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CA60);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CAE0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CB20);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CBB0);

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

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CCE0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CD50);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CDB0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CDF0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CE30);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CEB0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035CF30);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035D2A0);

u8* func_0035D300(u8* object)
{
    func_2CEBE0(object);
    *(u32*)object = (u32)D_183C60;
    *(u32*)(object + 0xA8) = 0;
    *(s16*)(object + 0xAC) = -1;
    return object;
}

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035D340);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035D3E0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035D440);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035D460);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035D4A0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035D540);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035DDE0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035DE40);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035DEA0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035E2A0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035E2F0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035E340);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035E3C0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035E470);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035E5C0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035FA20);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_0035FAA0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00361060);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003610F0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00361150);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003611B0);

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

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003620F0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00362170);

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

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003635B0);

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

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00364610);

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

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00364810);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00364880);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003648E0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00364960);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_003649E0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00364A70);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00364AF0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00364B70);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00364BF0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00364CA0);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00364D30);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00364D40);

INCLUDE_ASM("build/overlays/0069-00/asm/nonmatchings/text", func_00364D50);
