#include "include_asm.h"
#include "sdk/boot/syscalls_00121940.h"
#include "overlays/1067-00/text_001F9B70.h"
#include "overlays/1067-00/text_002CEAF0.h"
#include "overlays/1067-00/text_002D3BD0.h"
#include "overlays/0002-01/text_004CD3A0.h"

extern "C" void func_4D9F40(FieldWordAt210*, const FieldWordAt210*);


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
extern "C" void func_00232090(FieldObject232090*, s8);
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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001F9B70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FA1E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FA270);

extern "C" int func_001FA2A0(void* object)
{
    return 9;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FA2B0);

extern "C" s32 func_001FA2D0(FieldLateCommandStream* stream)
{
    u32* arg = stream->args;
    stream->args = arg + 1;
    u32 key = *arg;
    if (key & 0x80000000)
    {
        key &= 0x7FFFFFFF;
        for (s32 i = 0; i < 64; i++)
        {
            FieldLateIndexedObject* entry = D_507E50[i];
            if (entry)
            {
                switch (entry->kind)
                {
                case 0x4041:
                    if (key == entry->key244)
                    {
                        func_4289B0(entry);
                        func_004D65C0(entry);
                        entry->unk08();
                    }
                    break;
                case 0x4042:
                    if (key == entry->key254)
                    {
                        func_4289B0(entry);
                        func_004D65C0(entry);
                        entry->unk08();
                    }
                    break;
                }
            }
        }
    }
    else
    {
        for (s32 i = 0; i < 64; i++)
        {
            FieldLateIndexedObject* entry = D_507CD0[i];
            if (entry && entry->kind == 0x4040 && key == entry->key274)
            {
                func_428C80(entry);
                func_004D65C0(entry);
                entry->unk08();
            }
        }
    }
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FA460);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FA630);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FA8E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FAB10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FAB40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FACE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FB030);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FB090);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FB180);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FB260);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FB340);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FB5D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FB6A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FB8C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FB910);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FB9D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FBA30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FBD10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FBD40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FBEE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FC020);

extern "C" void func_001FC370(void* object)
{
    LibClass178DD0::operator delete(object);
}

extern "C" void func_001FC390(void* object, void* other)
{
    func_00222840(object, other);
    func_00238530(object, other);
}

extern "C" void func_001FC3D0(FieldLatePointer40* object, FieldLatePointer40* target)
{
    object->unk49_0 = 1;
    object->unk38 = target;
    object->unk38->unk40 = object->unk3C;
    object->unk40 = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FC400);

extern "C" void func_001FC900(FieldLateLarge* object)
{
    func_00217AD0(object);
    FieldLateVec4 first;
    first.words[0] = 0;
    first.words[1] = 0;
    first.words[2] = 0;
    first.words[3] = 0;
    object->unk5E0.qword = first.qword;
    FieldLateVec4 second;
    second.words[0] = 0;
    second.words[1] = 0;
    second.words[2] = 0;
    second.words[3] = 0;
    object->unk5F0.qword = second.qword;
    object->unk600 = 0;
    object->unk5D8 = 0;
    object->unk604_0 = 0;
    func_001FEDF0(object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FC980);

extern "C" void func_001FC9C0(FieldLateRecords* object)
{
    if (object->records != 0)
    {
        for (int i = 0; i < object->count; i++)
        {
            FieldLateRecord20* record = &object->records[i];
            record->unk0C = -1;
            record->unk04 = 0;
            record->unk10 = 0;
            record->unk16_0 = 0;
            record->unk16_1 = 1;
            record->unk08_0 = 0;
            record->unk16_2 = 0;
            record->unk14 = 0;
            record->unk15 = 0;
        }
    }
    object->unk20 = 0;
    object->unk2F = 0;
    object->unk2D = 0;
    object->unk2E = 0;
    object->unk38 = 0;
    object->unk2F = 1;
    object->unk45_0 = 0;
    object->unk3C = 10;
    object->unk44 = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FCAC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FCBD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FCC20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FCC80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FCCD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FCD20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FCD60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FD180);

extern "C" s32 func_001FD340(void* object)
{
    FieldLateVirtual* target = func_00217A90(object, 5);
    if (target)
    {
        func_004D65C0(target);
        target->unk08();
    }
    return 1;
}

extern "C" s32 func_001FD390(FieldLateFloatArgs* object, u32 count)
{
    float w = 1.0f;
    float z = 0.0f;
    u32* first = object->args;
    object->args = first + 1;
    float x = (float)*first;
    u32* second = object->args;
    object->args = second + 1;
    float y = (float)*second;
    if (count > 2)
    {
        u32* third = object->args;
        object->args = third + 1;
        z = (float)*third;
        if (count > 3)
        {
            w = *(float*)object->args;
        }
    }
    func_0020F050(object, count, x, y, z, w);
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FD490);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FD510);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FD580);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FD600);

extern "C" int func_001FD670(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FD680);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FD700);

extern "C" void func_001FD770(void* object)
{
}

extern "C" void func_001FD780(FieldLateDeleting* object)
{
    func_002D47A0(object);
    func_004D65C0(object);
    if (object)
    {
        object->unk00(1);
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FD7D0);
