#include "include_asm.h"
#include "overlays/1067-00/text_001FD860.h"
#include "overlays/1067-00/text_001ED7E0.h"
#include "main/resident_data.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_00419A70.h"
#include "overlays/lib/text_0044ABE0.h"

struct FieldScriptCursorU32
{
    u8 pad[0x548];
    u32* current;
};

struct FieldContextDE
{
    u8 pad[0xDE];
    u8 unkde_0_4 : 5;
    u8 unkde_5 : 1;
    u8 unkde_6_7 : 2;
};

struct FieldContextBit4
{
    u8 pad[0xDE];
    u8 unkde_0_3 : 4;
    u8 unkde_4 : 1;
    u8 unkde_5_7 : 3;
};

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FD860);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FD8D0);

s32 func_001FD950(void)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FD960);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FD9D0);

s32 func_001FDA50(void)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FDA60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FDAD0);

/** Partial FieldClass1507A0 object with vtable D_150BF0 in main data. */
class FieldClass150BF0 : public FieldClass1507A0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass150BF0();
};

FieldClass150BF0::~FieldClass150BF0()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FDBF0);

s32 func_001FDC90(FieldScriptCursorU32* object)
{
    bool low_bit = (*object->current & 1) != 0;
    ((FieldContextBit4*)D_001B6430->context)->unkde_4 = !low_bit;
    return 1;
}

s32 func_001FDCD0(FieldScriptCursorU32* object)
{
    u32 second;
    u32* words = object->current;
    second = words[1];
    u32 first = words[0];
    ResidentContextObject52* target = D_001B6430->context->unk44;
    target->unk40 = first;
    target->unk3c = second;
    return 1;
}

s32 func_001FDD00(FieldScriptCursorU32* object)
{
    u32 second;
    u32* words = object->current;
    second = words[1];
    ResidentContextObject52* target = D_001B6430->context->unk44;
    u32 first = words[0];
    target->unk38 = first;
    target->unk34 = second;
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FDD30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FDDE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FDEC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FDF20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FE010);

s32 func_001FE230(FieldScriptCursorU32* object)
{
    ((FieldContextDE*)D_001B6430->context)->unkde_5 = *object->current != 0;
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FE270);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FE2F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FE320);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FE360);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FE3A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FE6D0);

/** @brief Detach the object and add it to the resident release queue. @param object Object to release. */
extern "C" void func_001FE7A0(void* object)
{
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FE7D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FE8B0);

s32 func_001FE950(u8* object, s32 has_index)
{
    s32 index = 0;
    if (has_index) index = **(s32**)(object + 0x548);
    if (index == -1) {
        if (*(u32*)(object + 0x5C4)) {
            *(float*)(object + 0x14) = 1.0f;
            return 0;
        }
    } else {
        void** items = (void**)(object + 0x5A4);
        void* item = items[index];
        if (!item) return 1;
        if (func_0022A160(item)) {
            *(float*)(object + 0x14) = 1.0f;
            return 0;
        }
    }
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FE9F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FEB50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FEC10);

void func_001FECE0(u8* object)
{
    *(u32*)(object + 0x204) &= ~0x40u;
}

void func_001FED00(u8* object)
{
    *(u32*)(object + 0x204) &= ~0x40u;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FED20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FED60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FEDA0);

/** Partial owner of a Lib container at offset 0x5C8. */
struct FieldOwner1FEDF0
{
    u8 unk00[0x5C8];
    LibObject178660* unk5c8;
};

/**
 * @brief Release the owned Lib container.
 * @param owner Owner of the container.
 */
extern "C" void func_001FEDF0(FieldOwner1FEDF0* owner)
{
    if (owner->unk5c8 != 0)
    {
        owner->unk5c8->func_003EF740();
        owner->unk5c8 = 0;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FEE30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FEF40);

LibClass174790::~LibClass174790()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FF0D0);

void func_001FF110(u8* object)
{
    object[0x60] = object[0xA8];
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FF120);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FF220);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FF230);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FF240);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FF250);
