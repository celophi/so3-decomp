#include "include_asm.h"
#include "boot/resident_data.h"
#include "sdk/boot/syscalls_00121940.h"
#include "overlays/1067-00/text_001ED7E0.h"
#include "overlays/1067-00/text_002CEAF0.h"
#include "overlays/0002-01/text_004CD3A0.h"
#include "overlays/1067-00/text_0022DC70.h"
#include "overlays/1067-00/text_002DBC50.h"

extern "C" void func_4D9F40(FieldWordAt210*, const FieldWordAt210*);
extern "C" u32 D_001B65B4;


struct FieldScriptCursorF32 { u8 pad[0x548]; float* current; };
struct FieldScriptCursorS8 { u8 pad[0x548]; s8* current; };
struct FieldScriptCursorS32 { u8 pad[0x548]; s32* current; };
struct FieldScriptCursorU32 { u8 pad[0x548]; u32* current; };
struct FieldFloatA4 { u8 pad[0xA4]; float value; };
struct FieldPair57C { u8 pad[0x57C]; FieldFloatA4* first; FieldFloatA4* second; };
struct FieldFloat1F8 { u8 pad[0x1F8]; float value; };
struct FieldByte5C8 { u8 pad[0x5C8]; u8 value; };
struct FieldFlags208 { u8 pad[0x208]; u32 flags; };
struct FieldScriptVec { u8 pad[0x428]; float x; float y; float z; u32 flags; };
struct FieldSourceVec { u8 pad[0x20]; float x; float y; float z; u8 rest[0x44]; u32 flags; };
struct FieldRecord20 {
    u32 unk0;
    u32 value4;
    u8 flag8 : 1;
    u8 other8 : 7;
    u8 pad9[3];
    s32 indexC;
    u32 value10;
    u8 byte14;
    u8 byte15;
    u8 flag160 : 1;
    u8 flag161 : 1;
    u8 flag162 : 1;
    u8 other16 : 5;
    u8 pad17[9];
};
struct FieldRecords {
    u8 pad0[0x1C];
    FieldRecord20* records;
    u32 value20;
    s32 count;
    u8 pad28[5];
    u8 byte2D;
    u8 byte2E;
    u8 byte2F;
};
extern "C" void* func_0020F520(void*);
extern "C" void func_00232450(void*);
extern "C" void func_00232520(void*, s32);

struct FieldLateNodePrefix
{
    u8 unk00[0x18];
};

struct FieldLateNode20 : FieldLateNodePrefix
{
    virtual void unk00();
    virtual void unk04();
    virtual void unk08();
    u8 unk1C[4];
};

struct FieldLateNodes
{
    u8 unk00[0x1C];
    FieldLateNode20* nodes;
    u8 unk20[4];
    s32 count;
};

struct FieldLateFlag30
{
    char unused[0x30];
    unsigned char unk30_0 : 1;
    unsigned char unk30_1 : 1;
};


struct FieldLateRetryNode
{
    u8 unk00[0x20];
    s32 unk20;
};

struct FieldLateRetryOwner
{
    u8 unk00[0x10];
    void* unk10;
};

extern "C" void func_433AA0();
extern "C" s32 func_433880(void*, s32);
extern "C" s32 func_139700(s32, void*);
extern "C" s32 func_0023AEB0(FieldLateRetryNode*, FieldLateRetryOwner*);

extern "C" void func_00222840(void*, void*);
extern "C" void func_00238530(void*, void*);

struct FieldLatePointer40
{
    char unused00[0x38];
    FieldLatePointer40* unk38;
    void* unk3C;
    void* unk40;
    char unused44[5];
    unsigned char unk49_0 : 1;
};

union FieldLateVec4
{
    u32 words[4];
    unsigned __int128 qword;
};

struct FieldLateLarge
{
    u8 unk00[0x5D8];
    s32 unk5D8;
    u8 unk5DC[4];
    FieldLateVec4 unk5E0;
    FieldLateVec4 unk5F0;
    s32 unk600;
    u8 unk604_0 : 1;
};

extern "C" void func_00217AD0(FieldLateLarge*);
extern "C" void func_001FEDF0(FieldLateLarge*);

struct FieldLateRecord20
{
    u8 unk00[4];
    s32 unk04;
    u8 unk08_0 : 1;
    u8 unk08_rest : 7;
    u8 unk09[3];
    s32 unk0C;
    s32 unk10;
    u8 unk14;
    u8 unk15;
    u8 unk16_0 : 1;
    u8 unk16_1 : 1;
    u8 unk16_2 : 1;
    u8 unk16_rest : 5;
    u8 unk17[9];
};

struct FieldLateRecords
{
    u8 unk00[0x1C];
    FieldLateRecord20* records;
    s32 unk20;
    s32 count;
    u8 unk28[5];
    u8 unk2D;
    u8 unk2E;
    u8 unk2F;
    u8 unk30[8];
    void* unk38;
    s32 unk3C;
    u8 unk40[4];
    u8 unk44;
    u8 unk45_0 : 1;
};

class FieldLateVirtual
{
public:
    virtual void unk00();
    virtual void unk04();
    virtual void unk08();
};

extern "C" FieldLateVirtual* func_00217A90(void*, s32);

struct FieldLateFloatArgs
{
    u8 unk00[0x548];
    u32* args;
};

extern "C" void func_0020F050(FieldLateFloatArgs*, u32, float, float, float, float);

class FieldLateDeleting
{
public:
    virtual void unk00(s32);
};



class FieldLateIndexedObject
{
public:
    virtual void unk00();
    virtual void unk04();
    virtual void unk08();
    u8 pad04[0x68];
    u16 kind;
    u8 unk6E[0x1D6];
    u32 key244;
    u8 unk248[0xC];
    u32 key254;
    u8 unk258[0x1C];
    u32 key274;
};

struct FieldLateCommandStream
{
    u8 unk00[0x548];
    u32* args;
};

extern "C" FieldLateIndexedObject* D_507E50[];
extern "C" FieldLateIndexedObject* D_507CD0[];
extern "C" void func_4289B0(FieldLateIndexedObject*);
extern "C" void func_428C80(FieldLateIndexedObject*);

// Constructor; needs recovered classes and global state.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001ED7E0);

// Deleting destructor; needs recovered classes and global state.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EDCE0);

// Deleting destructor; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EDDF0);

void func_001EDE60(FieldVectorState50* state, const FieldQword* input)
{
    state->unk50 = 1;
    state->unk20.packed = *input;
}

void func_001EDE80(FieldVectorState50* state, float x, float y, float z)
{
    state->unk50 = 1;
    state->unk20.floats[0] = x;
    state->unk20.floats[1] = y;
    state->unk20.floats[2] = z;
    state->unk20.floats[3] = 1.0f;
}

void func_001EDEA0(FieldVectorState50* state, float x, float y, float z, float w)
{
    state->unk50 = 1;
    state->unk30.floats[0] = x;
    state->unk30.floats[1] = y;
    state->unk30.floats[2] = z;
    state->unk30.floats[3] = w;
}

void func_001EDEC0(FieldVectorState50* state, const FieldQword* input)
{
    state->unk50 = 1;
    state->unk30.packed = *input;
}

void func_001EDEE0(FieldVectorState50* state, const float* input)
{
    state->unk50 = 1;
    func_004CE4C0(state->unk30.floats, input);
}

void func_001EDF10(FieldVectorState50* state, const float* input)
{
    state->unk50 = 1;
    func_004CE4C0(state->unk30.floats, input);
}

void func_001EDF40(FieldVectorState50* state, float x, float y, float z)
{
    float value[4];
    state->unk50 = 1;
    value[0] = x;
    value[1] = y;
    value[2] = z;
    value[3] = 1.0f;
    func_004CE4C0(state->unk30.floats, value);
}

void func_001EDF80(FieldVectorState50* state, const FieldQword* input)
{
    state->unk50 = 1;
    state->unk40.packed = *input;
}

void func_001EDFA0(FieldVectorState50* state, float x, float y, float z)
{
    state->unk50 = 1;
    state->unk40.floats[0] = x;
    state->unk40.floats[1] = y;
    state->unk40.floats[2] = z;
}

// Deleting destructor; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EDFC0);

// Deleting destructor; needs recovered classes and global state.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EE060);

void func_001EE150(FieldByteState60* state)
{
    state->unk60 = 0;
}

void func_001EE160(void* object)
{
}

s32 func_001EE170(void* object)
{
    return 0;
}

bool func_001EE180(void* object, float value)
{
    return value < 0.0f;
}

// Returns a library global; its symbol mapping is unresolved.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EE1A0);

void func_001EE1B0(void* object)
{
}

s32 func_001EE1C0(void* object)
{
    return 0;
}

void func_001EE1D0(void* object)
{
}

void func_001EE1E0(void* object)
{
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

void func_001EE210(FieldVectorState50* state, const FieldQword* input)
{
    state->unk20.packed = *input;
}

void func_001EE220(FieldVectorState50* state, const FieldQword* input)
{
    state->unk20.packed = *input;
}

void func_001EE230(FieldFloat4At20* state, float x, float y, float z)
{
    state->unk20[0] = x;
    state->unk20[1] = y;
    state->unk20[2] = z;
    state->unk20[3] = 1.0f;
}

void func_001EE250(void* object)
{
}

s32 func_001EE260(void* object)
{
    return 3;
}

// Calls a library constructor using an unresolved global.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EE270);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EE2A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EE420);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EE5A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EE630);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EE810);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EEA20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EEAE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EEC60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EEDB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EF010);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EF0B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EF150);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EF4A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EF630);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EF6C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EF760);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EFA20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EFC80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EFEC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F0020);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F00D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F0180);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F0230);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F02E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F0360);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F04D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F0620);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F0670);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F06E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F09C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F0A80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F0B40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F0B80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F0C00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F0D20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F0E40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F0E80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F0F00);

void func_001F0F90(void* object)
{
    func_002DDA70(object);
    func_002DCD20(object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F0FC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F10B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F1190);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F1410);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F14F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F1610);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F1730);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F1880);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F19D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F1C10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F1CD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F1E10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F1E60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F1EF0);

extern "C" s32 func_001F1F60(void* object) { return 16; }

void func_001F1F70(void* object)
{
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F1FA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F2040);

extern "C" s32 func_001F2070(FieldScriptCursorF32* cursor)
{
    FieldPair57C* pair = (FieldPair57C*)func_0020F520(cursor);
    float value = *cursor->current;
    pair->first->value = value;
    pair->second->value = value;
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F20B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F2140);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F2230);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F22C0);

extern "C" s32 func_001F23E0(FieldScriptCursorF32* cursor)
{
    FieldFloat1F8* state = (FieldFloat1F8*)func_0020F520(cursor);
    state->value = *cursor->current;
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F2420);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F2470);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F2560);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F2650);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F2750);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F2840);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F29A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F2B00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F2BA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F2C40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F2D70);

extern "C" void func_001F2DE0(FieldRecords* state)
{
    if (state->records != 0) {
        for (s32 i = 0; i < state->count; ++i) {
            FieldRecord20& record = state->records[i];
            record.indexC = -1;
            record.value4 = 0;
            record.value10 = 0;
            record.flag160 = 0;
            record.flag161 = 1;
            record.flag8 = 0;
            record.flag162 = 0;
            record.byte14 = 0;
            record.byte15 = 0;
        }
    }
    state->value20 = 0;
    state->byte2F = 0;
    state->byte2D = 0;
    state->byte2E = 0;
}


extern "C" s32 func_001F2EB0(FieldScriptCursorU32* cursor, u32 count)
{
    D_001B65B4 = *cursor->current;
    D_001B6430->context->unkd4 = *cursor->current;
    return 1;
}

extern "C" s32 func_001F2EE0(void* object) { return 1; }

extern "C" s32 func_001F2EF0(FieldScriptCursorS8* cursor)
{
    void* state = func_0020F520(cursor);
    func_00232090((FieldObject232090*)state, *cursor->current);
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F2F30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F3020);

extern "C" s32 func_001F3120(FieldScriptCursorS32* cursor, u32 count)
{
    void* state = func_0020F520(cursor);
    if (*cursor->current == -1) {
        func_00232450(state);
    } else {
        for (u32 i = 0; i < count; ++i) {
            s32 value = *cursor->current++;
            func_00232520(state, value);
        }
    }
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F31D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F32F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F33E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F39A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F3A70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F3AD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F3BA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F3C70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F3DE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F3F20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F3FF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F40C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F4120);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F41D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F4280);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F43B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F44A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F4640);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F4770);

extern "C" s32 func_001F4840(FieldScriptCursorS32* cursor)
{
    FieldByte5C8* state = (FieldByte5C8*)func_0020F520(cursor);
    state->value = *cursor->current;
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F4880);

extern "C" s32 func_001F49C0(FieldScriptCursorU32* cursor)
{
    FieldFlags208* state = (FieldFlags208*)func_0020F520(cursor);
    if (state == 0) {
        return 1;
    }
    u32* operand = cursor->current++;
    u32 mask = *operand;
    if (*cursor->current & 1) {
        state->flags |= mask;
    } else {
        state->flags &= ~mask;
    }
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F4A40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F4B60);

extern "C" s32 func_001F4CA0(FieldScriptVec* cursor)
{
    FieldSourceVec* state = (FieldSourceVec*)func_0020F520(cursor);
    cursor->x = state->x;
    cursor->y = state->y;
    cursor->z = state->z;
    cursor->flags = state->flags;
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F4CF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F4E60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F4F30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F5000);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F51B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F5260);

void func_001F5580(FieldQword* first, FieldQword* second, const FieldQword* source)
{
    *first = *second = *source;
}

void func_001F5590(FieldVector4* destination, const FieldVector4* left, const FieldVector4* right)
{
    FieldVector4 result;
    result.packed = left->packed;
    result.floats[0] -= right->floats[0];
    result.floats[1] -= right->floats[1];
    result.floats[2] -= right->floats[2];
    destination->packed = result.packed;
}

void func_001F55E0(FieldQword* destination, const FieldQword* source)
{
    *destination = *source;
}

void func_001F55F0(FieldValueAt18* object, u32 value)
{
    object->value = value;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F5600);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F5650);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F5730);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F57E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F58C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F5990);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F5A60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F5B10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F5C70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F5D20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F5E20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F5ED0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F5FB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F6270);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F63A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F65A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F66D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F6870);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F6B30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F6C50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F6D40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F6E10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F72A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F73A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F7470);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F75C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F7690);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F76F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F7750);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F7850);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F7A00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F7A90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F7B40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F7B80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F7C30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F7D10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F7DE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F7EE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F80E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F8230);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F83A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F84D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F87F0);

void func_001F8A70(FieldFlagsAt78* object, u32 flags)
{
    object->flags |= flags;
}

float* func_001F8A80(float* values, float value)
{
    values[0] = value;
    values[1] = value;
    values[2] = value;
    values[3] = value;
    return values;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F8AA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F8AE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F8BC0);

void func_001F8C40(FieldWordAt210* destination, const FieldWordAt210* source)
{
    destination->value = source->value;
    func_4D9F40(destination, source);
}

void* func_001F8C60(void* object)
{
    return (u8*)object + 0x1D0;
}

void* func_001F8C70(void* object)
{
    return (u8*)object + 0x1E0;
}

extern "C" void* func_001F8C80(void* object)
{
    return (char*)object + 0x1F0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F8C90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F8CB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F8E20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F8F10);

extern "C" void func_001F9050(FieldLateNodes* object)
{
    for (int i = 0; i < object->count; i++)
    {
        FieldLateNode20* node = &object->nodes[i];
        node->unk00();
    }
}

extern "C" void func_001F90D0(FieldLateFlag30* object)
{
    if (!object->unk30_1)
    {
        func_00121FE0(0);
        object->unk30_1 = 1;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F9120);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F93D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F98E0);

extern "C" s32 func_001F9A80(FieldLateRetryOwner* owner, void* buffer, s32 mode)
{
    FieldLateRetryNode* node = (FieldLateRetryNode*)owner->unk10;
    if (node)
    {
        node = (FieldLateRetryNode*)((char*)node - 0x14);
    }
    for (s32 i = 0; i < 8; i++)
    {
        s32 result;
        if (mode)
        {
            func_433AA0();
            result = func_433880(buffer, 0x80);
        }
        else
        {
            result = func_139700(0x80, buffer);
        }
        if (result)
        {
            return result;
        }
        if (node->unk20 == 1 || !func_0023AEB0(node, owner))
        {
            break;
        }
    }
    return 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F9B60);
