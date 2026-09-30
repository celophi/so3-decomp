#include "include_asm.h"
#include "overlays/1067-00/text_00207580.h"

typedef unsigned __int128 FieldLocalQword;
extern "C" s32 func_0022A160(void*);
extern "C" void func_00208C30(void*);
extern "C" void func_00209160(void*, void*, u32);
extern "C" void func_001FF5A0(void*, u32, u32);
extern "C" void func_001FF7F0(FieldFlaggedPointerA0*, u32);

union FieldLocalVector4
{
    u32 words[4];
    FieldLocalQword packed;
};
extern "C" void func_00228DD0(FieldTransform*);
extern "C" bool func_00227280(FieldState3BA*);

struct FieldSlot { u8 pad[0x20]; FieldLocalQword unk20; };
struct FieldState704 { u8 pad[0x704]; u32 unk704; };
struct FieldState79C { u8 pad[0x79C]; u8 unk79c; };
struct FieldState794 { u8 pad[0x794]; u8 unk794; };
struct FieldState570 { u8 pad[0x570]; u8 unk570; };
struct FieldNested634 { u8 pad[0x634]; u32 unk634; };
struct FieldOuter870 { u8 pad[0x838]; FieldNested634* unk838; u8 pad83c[0x34]; void* unk870; };
struct FieldFlagTarget { u8 pad[0x6A]; u16 flags; };
struct FieldItem10 {
    FieldFlagTarget* target;
    u8 pad04[8];
    u8 unk0_1 : 2;
    u8 unk2 : 1;
    u8 unk3_7 : 5;
    u8 pad0d[3];
};
struct FieldListAC { u8 pad[0xA4]; FieldItem10* items; s32 count; };
struct FieldStateAD { u8 pad[0xA0]; void* unka0; u8 pad_a4[9]; u8 unkad_0 : 1; u8 unkad_rest : 7; };
struct FieldState820 { u8 pad[0x820]; void* unk820; };
struct FieldState634 { u8 pad[0x5A0]; u8 unk5a0; u8 pad5a1[0x93]; void* unk634; };
struct FieldState2C { u8 pad[0x1C]; u32 unk1c; u32 unk20; float unk24; u8 pad28[4]; u8 unk2c_0 : 1; u8 unk2c_rest : 7; };
extern "C" int func_00206280(void*);
extern "C" void func_4C9010(FieldOuter870*, void*, void*);
extern "C" void func_4A5E60(FieldState820*, void*, void*);
extern "C" void func_4D5C90(void*);
extern "C" void func_448250(FieldState634*);

struct FieldState544 { u8 pad[0x544]; float source; };
struct FieldMotion {
    FieldState544* source;
    u8 pad04[0x6C];
    u32 flags;
    u8 pad74[0x6C];
    float start;
    float target;
    float duration;
    float step;
};
struct FieldMotion2 {
    u8 pad00[0x70]; u32 flags;
    u8 pad74[0x84]; float current;
    u8 padFC[0xC]; float fallback;
    u8 pad10C[0x14]; float duration;
    float change;
    float target;
};
struct FieldMotion3 {
    u8 pad00[0x70]; u32 flags;
    float duration;
    float change;
    float target;
    u8 pad80[0x74]; float current;
    u8 padF8[0xC]; float fallback;
};
struct FieldMotion4 {
    u8 pad00[0x70]; u32 flags;
    u8 pad74[0x3C]; float current;
    float previous;
    u8 padB8[4]; float duration;
    float change;
    float target;
};

struct FieldCallbackBase { u8 pad[0xC]; };
class FieldCallbackObject : FieldCallbackBase
{
public:
    virtual void action(s32);
    virtual void finish();
};
extern "C" void func_00205260(FieldCallbackState*);
extern "C" void func_00204E40(FieldCallbackState*);

extern "C" void* func_00204A10(void*);
extern "C" void func_45B0E0(void*, void*, bool);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207580", func_00207580);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207580", func_00207630);

extern "C" void func_002077B0(FieldState2C* object, int value)
{
    object->unk1c = 0;
    object->unk20 = 0;
    object->unk24 = (float)value;
    object->unk2c_0 = 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207580", func_002077E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207580", func_002078A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207580", func_002078F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207580", func_002079D0);

extern "C" int func_00207AD0(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207580", func_00207AE0);
