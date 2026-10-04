#include "include_asm.h"
#include "overlays/1067-00/text_001E6C50.h"
#include "main/resident_0012F0F8.h"
#include "overlays/lib/text_00429B00.h"
#include "main/resident_data.h"
#include "sdk/main/syscalls_00121940.h"
#include "overlays/1067-00/text_001ED7E0.h"
#include "overlays/1067-00/text_0020E4B0.h"
#include "overlays/1067-00/text_001DED80_callbacks.h"
#include "overlays/1067-00/text_002CEAF0.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/1067-00/text_0022DC70.h"
#include "overlays/1067-00/text_0021FB80.h"
#include "overlays/1067-00/text_001FF260.h"
#include "overlays/1067-00/text_002DBC50.h"
#include "overlays/1067-00/text_00207AF0.h"
#include "overlays/1067-00/text_00212560.h"
#include "overlays/1067-00/text_00202240.h"
#include "overlays/1067-00/text_0022B490.h"
#include "main/resident_001001E0.h"
#include "vu0.h"

extern "C" void func_4D9F40(FieldWordAt210*, const FieldWordAt210*);
extern "C" u32 D_001B65B4;
extern "C" u8 D_50CD30[];
extern "C" void* D_001B6628;
extern "C" void* D_001B6650;


struct FieldScriptCursorF32 { u8 pad[0x548]; float* current; };
struct FieldScriptCursorS8 { u8 pad[0x548]; s8* current; };
struct FieldScriptCursorS32 { u8 pad[0x548]; s32* current; };
struct FieldScriptCursorU32
{
    u8 unk00[0x14];
    float unk14;
    u8 unk18[0x408];
    u32 unk420;
    u8 unk424[0x124];
    u32* current;
};

/** Partial command holder and its containing context object. */
struct FieldCommandList8
{
    u8 unk00[4];
    LibClass178DD0* list;
};
struct FieldContext14Commands
{
    u8 unk00[0x30];
    FieldCommandList8 unk30;
    u8 unk38[0x218];
    FieldCommandList8 unk250;
};
struct FieldState3D3
{
    u8 unk00[0x24C];
    float unk24c;
    u8 unk250[0x183];
    u8 unk3d3;
};
struct FieldPosition30 { u8 unk00[0x20]; FieldVec4A position; };
struct FieldRangeContext371
{
    u8 unk00[0x30];
    FieldMotionRange motion;
    u8 unk1d0[0x130];
    FieldClass150070* unk300;
    u8 unk304[4];
    FieldState3D3* unk308;
    u8 unk30c[0x28];
    float current;
    float target;
    float change;
    float duration;
    u8 unk344[0x2C];
    u8 unk370_0 : 1;
    u8 unk370_1_7 : 7;
};

/** Partial motion state containing its saved vector and active index. */
struct FieldMotionCaptureAC
{
    u8 unk00[0x10];
    FieldVec4A unk10;
    u8 unk20[0x50];
    u32 unk70;
    u8 unk74[0x1C];
    FieldVec4A unk90;
    u32 unkA0;
    s32 unkA4;
    s32 unkA8;
};
/** Partial context containing both motion states and its copied name. */
struct FieldContextName36E
{
    u8 unk00[0x30];
    FieldCopyState unk30;
    u8 unk190[0xC0];
    FieldMotionCaptureAC unk250;
    u8 unk300[0x5D];
    char unk35d[17];
};
extern "C" const char D_31A7E0[];

struct FieldContextMotionChannels
{
    u8 unk00[0x30];
    FieldClass151460 unk30;
    u8 unkB8[0x198];
    FieldClass151460 unk250;
};

/** Partial actor view containing its command list and status flags. */
struct FieldActorCommandState
{
    u8 unk00[0x8D];
    u8 unk8d_0 : 1;
    u8 unk8d_1 : 1;
    u8 unk8d_2_7 : 6;
    u8 unk8e[0x36];
    FieldClass152FA0 commands;
    u8 unk140[0x48D];
    u8 unk5cd_0_1 : 2;
    u8 unk5cd_2 : 1;
    u8 unk5cd_3 : 1;
    u8 unk5cd_4_7 : 4;

    /** @brief Test the command-wait flags. @return True when bit two is clear or bit three is set. */
    bool test_unk5cd() const
    {
        if (!unk5cd_2)
        {
            return true;
        }
        if (unk5cd_3)
        {
            return true;
        }
        return false;
    }
};


struct FieldContext18F2420 { u8 unk00[0x18]; void* target; };
struct FieldContext14F0E40 { u8 unk00[0x14]; u8* object; };
struct FieldObjectBit240
{
    u8 pad[0x240];
    u8 unk240_0_1 : 2;
    u8 unk240_2 : 1;
    u8 unk240_3_7 : 5;
};
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
extern "C" void func_002099B0(u8* object);
extern "C" void func_002097F0(u8* object, float first, float second);

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


extern "C" s32 func_0023AEB0(FieldClass1530D0* owner, FieldClass150070* loader);

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

// FieldClass1504F0 constructor; needs recovered classes and global state.
/** @brief Initialize the field interface and attach its container and widgets. */
FieldClass1504F0::FieldClass1504F0()
{
    unk14 = 0;
    unk40 = 0;
    unk4c = 0;
    unk3c = -1;
    unk4d_0 = 1;
    unk4d_1 = 0;
    unk4d_2 = 0;
    unk4d_3 = 0;
    unk4d_4 = 0;
    unk4d_5 = 0;
    unk4d_6 = 0;
    unk4d_7 = 0;
    unk48 = 1.0f;
    for (s32 i = 0; i < 2; i++)
    {
        unk24[i] = 0;
        unk2c[i] = 0;
        unk34[i] = 0;
    }
    D_001B6430->context->unk64->unk48 = this;
    D_001B6430->context->unkde_3 = 1;
    unk18 = new(0) LibObject178660;
    if (!unk18)
    {
        return;
    }
    func_00465B20(D_001B657C, unk18);
    unk1c = new(0) LibClass178630;
    if (!unk1c)
    {
        return;
    }
    if (!func_004C5A80(unk1c, 0, 0.0f, 52.0f, 528.0f, 48.0f, 88.0f))
    {
        return;
    }
    unk1c->unk3d = 1;
    func_004C6190(unk18, unk1c);
    for (s32 i = 0; i < 2; i++)
    {
        unk24[i] = new(0) LibClass178630;
        if (unk24[i])
        {
            if (func_004C5A80(unk24[i], 0, 0.0f, 20.0f, i == 0 ? 132.0f : 120.0f, 40.0f, 88.0f))
            {
                unk24[i]->unk3d = 0;
            }
            func_004C6190(unk18, unk24[i]);
        }
    }
    void* data = func_00201EA0(D_001B6430->context->unk2c, 0x535953, 0, 0);
    if (data)
    {
        unk3c = func_004656B0(D_001B657C, (void*)(((u32)data + 127) & ~127));
        unk20 = new(0) LibObject178750;
        if (unk20 && func_004C7FE0(unk20, unk3c, 1, 0, 16.0f, 56.0f, 352.0f, 48.0f))
        {
            func_004C6190(unk18, unk20);
            func_001ED160();
        }
    }
    if (D_001B6428)
    {
        D_001B6428->func_001DD7B0();
    }
    D_001B6428 = this;
}

// Deleting destructor; needs recovered classes and global state.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", __dt__14LibClass174610Fv);

// Deleting destructor; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", __dt__14LibClass178A70Fv);

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

/** @brief Clear the inherited transform mask and detach the object. */
FieldClass1503A0::~FieldClass1503A0()
{
}

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

void* func_001EE1A0()
{
    return D_50CD30;
}

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

// Kept copy of FieldClass150490's inline empty func_001EAC90; emitted once this unit's users are compiled.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EAC90__16FieldClass150490FP14ResidentPacket);

s32 func_001EE260(void* object)
{
    return 3;
}

void func_001EE270(void* object)
{
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

/** @brief Subtract position components while preserving the left vector's fourth component. */
static inline FieldVec4A field_difference(const FieldVec4B& left, const FieldVec4B& right)
{
    FieldVec4A value;
    *(unsigned __int128*)&value = *(const unsigned __int128*)&left;
    value.x -= right.x;
    value.y -= right.y;
    value.z -= right.z;
    return value;
}
/** @brief Subtract the position components of vectors with different value representations. */
static inline FieldVec4A field_difference(const FieldVec4B& left, const FieldVec4A& right)
{
    FieldVec4A value;
    *(unsigned __int128*)&value = *(const unsigned __int128*)&left;
    float x = value.x;
    value.x = x - right.x;
    value.y -= right.y;
    value.z -= right.z;
    return value;
}
/** @brief Update the context flag and its linked receiver. @param object Context receiver. @param value New flag value. */
static inline void field_range_flag(FieldRangeContext371* object, u8 value)
{
    object->unk370_0 = value;
    if (object->unk308)
    {
        object->unk308->unk3d3 = value;
    }
}
/** @brief Subtract xyz coordinates and return the updated copy. @param value Vector to update. @param other Coordinates to subtract. @return Updated vector. */
static inline FieldVec4B field_subtract(FieldVec4B& value, const FieldVec4A& other)
{
    float x = value.x;
    value.x = x - other.x;
    value.y -= other.y;
    value.z -= other.z;
    FieldVec4B updated(value);
    return updated;
}
/** @brief Return the xyz length computed by the shared VU helper. */
/** @brief Test vertical overlap and the expanded bounds of a transformed rectangle. */
static inline bool field_inside_geometry(FieldClass150510* object, const FieldVec4B* input, float tolerance)
{
    float center_y = object->unk20.y;
    float y = input->y;
    if (center_y < y - tolerance || center_y - object->unk30 > y)
    {
        return false;
    }
    FieldVec4B transformed;
    transformed = field_difference(*input, object->unk20);
    transformed.w = 1.0f;
    func_00433730(&object->unk50, &transformed, &transformed);
    float diameter = 2.0f * input->w;
    float bound_x = (object->unk40 + diameter) / 2.0f;
    float bound_z = (object->unk44 + diameter) / 2.0f;
    float z;
    if (transformed.x < -bound_x || !(transformed.x < bound_x) ||
        (z = transformed.z) < -bound_z || !(z < bound_z))
    {
        return false;
    }
    else
    {
        return true;
    }
}

/**
 * @brief Test the shape condition and its expanded rectangular bounds.
 * @param object Conditional rectangular shape.
 * @param input Position and radius to test.
 * @param mask Selected condition bits.
 * @param direction Direction used by the angle condition.
 * @param tolerance Vertical overlap allowance.
 * @return Whether the condition and geometry tests succeed.
 */
extern "C" bool func_001EE2A0(FieldClass150590* object, const FieldVec4B* input, u32 mask, float direction, float tolerance)
{
    if (func_001EEDB0(&object->unk90, mask, input, &object->unk20, direction))
    {
        return field_inside_geometry(object, input, tolerance);
    }
    return false;
}

/**
 * @brief Initialize the fields shared by the shape families.
 * @param object Shape to initialize.
 * @param owner Associated owner.
 * @param position Shape position.
 * @param height Vertical extent.
 * @param word38 Word stored at offset 0x38.
 * @param word34 Word stored at offset 0x34.
 * @param kind Shape family mask.
 */
static inline void field_initialize_shape(FieldClass1505B0* object, void* owner, FieldVec4A position, float height, u32 word38, u32 word34, u8 kind)
{
    object->unk18 = owner;
    object->unk20 = position;
    object->unk30 = height;
    object->unk1c = kind;
    object->unk38 = word38;
    object->unk34 = word34;
}

FieldClass150590::FieldClass150590(void* owner, FieldVec4A position, FieldVec4A dimensions, FieldVec4A angles, u32 word38, u32 word34, u32 mask, u8 flags)
{
    field_initialize_shape(this, owner, position, dimensions.z, word38, word34, 3);
    unk40 = dimensions.x;
    unk44 = dimensions.y;
    unk48 = dimensions.w;
    unk90.unk04 = angles.x;
    unk90.unk08 = angles.y;
    unk90.unk00 = mask;
    unk90.unk0c = flags;
    float cosine = func_004CC3E0(0.5f * unk48);
    FieldVec4B quaternion(0.0f, -func_004CC5B0(0.5f * unk48), 0.0f, cosine);
    func_004CD8A0(&quaternion);
    unk50 = func_004CE930(quaternion);
}

/**
 * @brief Test the flag selected by a shape evaluation kind.
 * @param object Rectangular shape supplying the flags.
 * @param kind Flag selector; values above two are unrestricted.
 * @return Whether the selected flag allows the evaluation.
 */
static inline bool field_shape_accepts_kind(FieldClass150570* object, u8 kind)
{
    switch (kind)
    {
    case 0:
        if (!(object->unk90 & 2))
        {
            return false;
        }
        break;
    case 1:
        if (!(object->unk90 & 4))
        {
            return false;
        }
        break;
    case 2:
        if (!(object->unk90 & 8))
        {
            return false;
        }
        break;
    }
    return true;
}
/**
 * @brief Test the selected shape flag and its expanded rectangular bounds.
 * @param object Rectangular shape.
 * @param input Position and radius to test.
 * @param kind Flag selector.
 * @param tolerance Vertical overlap allowance.
 * @return Whether the flag and geometry tests succeed.
 */
extern "C" bool func_001EE630(FieldClass150570* object, const FieldVec4B* input, u8 kind, float tolerance)
{
    if (field_shape_accepts_kind(object, kind))
    {
        return field_inside_geometry(object, input, tolerance);
    }
    return false;
}

/** @brief Initialize the rectangular shape and its optional script condition. */
FieldClass150570::FieldClass150570(void* owner, FieldVec4A position, FieldVec4A dimensions, u8 flags, u32 word38, u32 word34)
{
    u8 mode = flags;
    field_initialize_shape(this, owner, position, dimensions.z, word38, word34, 2);
    unkb4_0 = 0;
    unk91 = 0;
    if (mode & 0x10)
    {
        mode = (mode & ~0xC) | 3;
        u32 packed;
        func_0020EF90(D_001B6430->context->unk38, word34, &unka0.x, &unkb0, &packed);
        unk91 = packed;
        unkb4_0 = (packed & 0xFF000000) != 0;
    }
    unk90 = mode;
    unk40 = dimensions.x;
    unk44 = dimensions.y;
    unk48 = dimensions.w;
    float cosine = func_004CC3E0(0.5f * unk48);
    FieldVec4B quaternion(0.0f, -func_004CC5B0(0.5f * unk48), 0.0f, cosine);
    func_004CD8A0(&quaternion);
    unk50 = func_004CE930(quaternion);
}

/** @brief Initialize the cylindrical shape and its angular condition. */
FieldClass150550::FieldClass150550(void* owner, FieldVec4A position, FieldVec4A dimensions, u32 word38, u32 word34, u32 mask, u8 flags)
{
    field_initialize_shape(this, owner, position, dimensions.y, word38, word34, 1);
    unk40 = dimensions.x;
    unk50.unk00 = mask;
    unk50.unk0c = flags;
    unk50.unk04 = dimensions.z;
    unk50.unk08 = dimensions.w;
}

/**
 * @brief Test the flag selected by a shape evaluation kind.
 * @param object Cylindrical shape supplying the flags.
 * @param kind Flag selector; values above two are unrestricted.
 * @return Whether the selected flag allows the evaluation.
 */
static inline bool field_shape_accepts_kind(FieldClass150530* object, u8 kind)
{
    switch (kind)
    {
    case 0:
        if (!(object->unk50 & 2))
        {
            return false;
        }
        break;
    case 1:
        if (!(object->unk50 & 4))
        {
            return false;
        }
        break;
    case 2:
        if (!(object->unk50 & 8))
        {
            return false;
        }
        break;
    }
    return true;
}
/** @brief Return the xyz length computed by the shared VU helper. */
static inline float field_length_xyz(const FieldVec4B& value)
{
    FieldVec4A result;
    vu0_length_xyz(&result, &value);
    return result.x;
}
/** @brief Test vertical overlap and the radius bound against full xyz distance. */
static inline bool field_inside_cylinder(FieldClass1505D0* object, const FieldVec4B* input, float tolerance)
{
    float center_y = object->unk20.y;
    float y = input->y;
    if (center_y < y - tolerance || center_y - object->unk30 > y)
    {
        return false;
    }
    FieldVec4B difference;
    difference = field_difference(object->unk20, *input);
    if (field_length_xyz(difference) < object->unk40 + input->w)
    {
        return true;
    }
    else
    {
        return false;
    }
}
/**
 * @brief Test the selected shape flag, vertical overlap and xyz radius bound.
 * @param object Cylindrical shape.
 * @param input Position and radius to test.
 * @param kind Flag selector; values above two are unrestricted.
 * @param tolerance Vertical overlap allowance.
 * @return Whether the flag and geometry tests succeed.
 */
extern "C" bool func_001EEAE0(FieldClass150530* object, const FieldVec4B* input, u8 kind, float tolerance)
{
    if (field_shape_accepts_kind(object, kind))
    {
        return field_inside_cylinder(object, input, tolerance);
    }
    return false;
}

/** @brief Initialize the cylinder and its optional script condition. */
FieldClass150530::FieldClass150530(void* owner, FieldVec4A position, FieldVec4A dimensions, u8 flags, u32 word38, u32 word34)
{
    u8 mode = flags;
    field_initialize_shape(this, owner, position, dimensions.y, word38, word34, 0);
    unk74_0 = 0;
    unk51 = 0;
    if (mode & 0x10)
    {
        mode = (mode & ~0xC) | 3;
        u32 packed;
        func_0020EF90(D_001B6430->context->unk38, word34, &unk60.x, &unk70, &packed);
        unk51 = packed;
        unk74_0 = (packed & 0xFF000000) != 0;
    }
    unk50 = mode;
    unk40 = dimensions.x;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EEDB0);


/** @brief Test a cylinder condition and its expanded radius bound. */
static inline bool field_inside_conditional_cylinder(FieldClass150550* object, const FieldVec4B* input, u32 mask, float heading, float tolerance)
{
    if (func_001EEDB0(&object->unk50, mask, input, &object->unk20, heading))
    {
        return field_inside_cylinder(object, input, tolerance);
    }
    return false;
}
/** @brief Clear the actor vector at offset 0x1C0. */
static inline void field_clear_actor_vector(FieldClass151510* actor)
{
    const FieldVec4A& zero = FieldVec4A(0, 0, 0, 0);
    actor->unk1c0 = zero;
}
/** @brief Test whether traversal has returned to the circular list sentinel. */
/** @brief Test whether traversal has reached the circular list sentinel. */
static inline bool field_at_sentinel(FieldClass150060* head, FieldClass150060* node)
{
    if (head == node)
    {
        return true;
    }
    return false;
}
/** @brief Test the flag requesting the shape direction response. */
/** @brief Test the condition flag that enables the direction response. */
static inline bool field_condition_moves(const FieldCondition16* condition)
{
    if (condition->unk0c & 1)
    {
        return true;
    }
    return false;
}
/**
 * @brief Dispatch the first accepted conditional shape and apply its optional direction response.
 * @param head Circular shape-list sentinel.
 * @param actor Actor supplying position, radius, height and direction.
 * @param mask Selected shape condition bits.
 * @return One when an uncached shape is accepted, otherwise zero.
 */
extern "C" s32 func_001EF150(FieldClass150060* head, FieldClass151510* actor, u32 mask)
{
    FieldClass150060* current = head;
    for (;;)
    {
        current = current->unk08;
        if (field_at_sentinel(head, current))
        {
            break;
        }
        FieldClass1505B0* shape = static_cast<FieldClass1505B0*>(current);
        if (!(shape->unk1c & 1))
        {
            continue;
        }
        FieldVec4B input(actor->unk20);
        input.w = actor->unkA0;
        float tolerance = actor->unkA4;
        float heading = func_002273B0(actor);
        bool hit;
        bool moves;
        FieldVec4B* position;
        void* receiver = shape;
        if (shape->unk1c & 2)
        {
            FieldClass150590* rectangle = static_cast<FieldClass150590*>(receiver);
            hit = func_001EE2A0(rectangle, &input, mask, heading, tolerance);
            moves = field_condition_moves(&rectangle->unk90);
            position = &rectangle->unk20;
        }
        else
        {
            FieldClass150550* cylinder = static_cast<FieldClass150550*>(receiver);
            hit = field_inside_conditional_cylinder(cylinder, &input, mask, heading, tolerance);
            moves = field_condition_moves(&cylinder->unk50);
            position = &cylinder->unk20;
        }
        if (!hit)
        {
            continue;
        }
        if (!func_00237420(actor, shape))
        {
            continue;
        }
        u32 packet;
        if ((shape->unk38 & 0xFF) == 2)
        {
            packet = (actor->unk70 << 16) | 0x202;
        }
        else
        {
            packet = (shape->unk38 << 8) | 2;
        }
        FieldClass151D40* context = reinterpret_cast<FieldClass151D40*>(D_001B6430->context->unk38);
        context->func_0021DC60(shape->unk34, packet);
        if (moves)
        {
            input = field_difference(*position, actor->unk20);
            input.y = 0;
            input.w = 0;
            func_00227740(actor, &input, 0.25f);
            field_clear_actor_vector(actor);
        }
        return 1;
    }
    return 0;
}

/**
 * @brief Test the listed script shapes and dispatch commands for newly overlapping entries.
 * @param list Circular shape list.
 * @param actor Actor whose position, radius and height supply the query.
 * @param kind Shape flag selector.
 * @return Whether a new overlapping entry dispatched a command.
 */
extern "C" bool func_001EF4A0(LibClass178DD0* list, FieldClass151510* actor, u8 kind)
{
    FieldClass1505B0* current = reinterpret_cast<FieldClass1505B0*>(list);
    bool result = false;
    while (true)
    {
        current = static_cast<FieldClass1505B0*>(current->unk08);
        if (reinterpret_cast<FieldClass1505B0*>(list) == current)
        {
            break;
        }
        if (current->unk1c & 1)
        {
            continue;
        }
        FieldVec4B input(actor->unk20);
        input.w = actor->unkA0;
        float tolerance = actor->unkA4;
        void* receiver = current;
        bool inside;
        if (current->unk1c & 2)
        {
            FieldClass150570* rectangle = static_cast<FieldClass150570*>(receiver);
            if ((rectangle->unk90 & 0xE) == 2 && D_001B6430->context->unk38->unk4c8_0)
            {
                continue;
            }
            inside = func_001EE630(rectangle, &input, kind, tolerance);
        }
        else
        {
            FieldClass150530* cylinder = static_cast<FieldClass150530*>(receiver);
            if ((cylinder->unk50 & 0xE) == 2 && D_001B6430->context->unk38->unk4c8_0)
            {
                continue;
            }
            inside = func_001EEAE0(cylinder, &input, kind, tolerance);
        }
        if (inside && func_00237420(actor, current))
        {
            reinterpret_cast<FieldClass151D40*>(D_001B6430->context->unk38)->func_0021DC60(
                current->unk34,
                (current->unk38 & 0xFF) == 2 ? (actor->unk70 << 16) | 0x201 : (current->unk38 << 8) | 1);
            result = true;
        }
    }
    return result;
}

/** @brief Delete the listed shapes and destroy the inherited list. */
FieldClass1505F0::~FieldClass1505F0()
{
    func_001DD730();
}

/** @brief Remove and queue shapes associated with the script's current owner word. */
extern "C" s32 func_001EF6C0(FieldScriptCursorU32* cursor)
{
    LibClass178DD0* list;
    void* owner = (void*)*cursor->current;
    list = (LibClass178DD0*)D_001B6430->context->unk3c;
    LibListNode* node;
    LibListNode* next = ((LibListNode*)list)->next;
    for (;;)
    {
        node = next;
        if (!next || (LibListNode*)list == next)
        {
            break;
        }
        next = next->next;
        if (owner == ((FieldClass1505B0*)node)->unk18)
        {
            list->func_004D72A0(node);
            func_0011ED90(D_001B65F4, node);
        }
    }
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001EF760);

/**
 * @brief Create a rectangular script shape and append it to the shape list.
 * @param cursor Operand cursor supplying the owner, coordinates, dimensions and condition.
 * @return Always one.
 */
extern "C" s32 func_001EFA20(FieldScriptCursorU32* cursor)
{
    void* owner = (void*)*cursor->current++;
    FieldVec4A position;
    position.x = (float)(s32)*cursor->current++;
    position.y = (float)(s32)*cursor->current++;
    position.z = (float)(s32)*cursor->current++;
    position.w = 1.0f;
    FieldVec4A dimensions;
    dimensions.x = (float)*cursor->current++;
    dimensions.y = (float)*cursor->current++;
    dimensions.z = (float)*cursor->current++;
    dimensions.w = (3.1415927f * (2.0f * (float)*cursor->current++)) / 360.0f;
    u8 flags = *(u8*)cursor->current++;
    u32 word34;
    u32 word38 = *cursor->current++;
    word34 = *cursor->current;
    FieldClass150570* shape = new FieldClass150570(owner, position, dimensions, flags, word38, word34);
    LibClass178DD0* list = (LibClass178DD0*)D_001B6430->context->unk3c;
    list->func_004D74F0(shape, (void*)-1);
    return 1;
}

/**
 * @brief Create a conditional cylindrical shape and append it to the script shape list.
 * @param cursor Operand cursor supplying owner, coordinates, dimensions and condition.
 * @return Always one.
 */
extern "C" s32 func_001EFC80(FieldScriptCursorU32* cursor)
{
    void* owner = (void*)*cursor->current++;
    u32 word34;
    u32 mask;
    u32 word38;
    u8 flags;
    FieldVec4A position;
    position.x = (float)(s32)*cursor->current++;
    position.y = (float)(s32)*cursor->current++;
    position.z = (float)(s32)*cursor->current++;
    position.w = 1.0f;
    FieldVec4A dimensions;
    dimensions.x = (float)(s32)*cursor->current++;
    dimensions.y = (float)(s32)*cursor->current++;
    dimensions.z = (6.2831855f * (float)*cursor->current++) / 360.0f;
    dimensions.w = (6.2831855f * (float)*cursor->current++) / 360.0f;
    mask = *cursor->current & 0xFFFFFF;
    flags = *cursor->current++ >> 24;
    word38 = *cursor->current++;
    word34 = *cursor->current;
    FieldClass150550* shape = new FieldClass150550(owner, position, dimensions, word38, word34, mask, flags);
    LibClass178DD0* list = (LibClass178DD0*)D_001B6430->context->unk3c;
    list->func_004D74F0(shape, (void*)-1);
    return 1;
}

/**
 * @brief Create a cylindrical script shape and append it to the shape list.
 * @param cursor Operand cursor supplying the owner, coordinates, dimensions and condition.
 * @return Always one.
 */
extern "C" s32 func_001EFEC0(FieldScriptCursorU32* cursor)
{
    void* owner = (void*)*cursor->current++;
    FieldVec4A position;
    position.x = (float)(s32)*cursor->current++;
    position.y = (float)(s32)*cursor->current++;
    position.z = (float)(s32)*cursor->current++;
    position.w = 1.0f;
    FieldVec4A dimensions;
    dimensions.x = (float)(s32)*cursor->current++;
    dimensions.y = (float)(s32)*cursor->current++;
    u8 flags = *(u8*)cursor->current++;
    u32 word34;
    u32 word38 = *cursor->current++;
    word34 = *cursor->current;
    FieldClass150530* shape = new FieldClass150530(owner, position, dimensions, flags, word38, word34);
    LibClass178DD0* list = (LibClass178DD0*)D_001B6430->context->unk3c;
    list->func_004D74F0(shape, (void*)-1);
    return 1;
}

/** @brief Destroy the cylinder and detach its inherited node. */
FieldClass150530::~FieldClass150530()
{
}

/** @brief Destroy the cylinder and its inherited state. */
FieldClass150550::~FieldClass150550()
{
}

/** @brief Destroy the script-conditioned shape and detach it from its owner. */
FieldClass150570::~FieldClass150570()
{
}

/** @brief Destroy the conditional shape and its inherited state. */
FieldClass150590::~FieldClass150590()
{
}

/**
 * @brief Set two float bounds for the context object, optionally selecting a named entry.
 * @param cursor Float operand cursor followed by the optional entry name.
 * @param count Number of command operands; the second bound defaults to one million.
 * @return Always one.
 */
extern "C" s32 func_001F02E0(FieldScriptCursorF32* cursor, u32 count)
{
    float first = *cursor->current++;
    float second = 1000000.0f;
    const char* name = 0;
    if (count > 1)
    {
        second = *cursor->current++;
        if (count > 2)
        {
            name = (const char*)cursor->current;
        }
    }
    func_00225150(D_001B6430->context->unk14, name, first, second);
    return 1;
}

/**
 * @brief Queue a curve command borrowing the remaining pairs from the script.
 * @param cursor Script operands and channel-selection state.
 * @param count Number of operand words.
 * @return Always one.
 */
extern "C" s32 func_001F0360(FieldScriptCursorU32* cursor, u32 count)
{
    u32 pair_count = (count - 2) >> 1;
    if (pair_count == 0)
    {
        return 1;
    }
    FieldClass1512C0* command = new FieldClass1512C0;
    if (command == 0)
    {
        cursor->unk14 = 1.0f;
        return 1;
    }
    float first = *(float*)cursor->current++;
    float second = (float)*cursor->current++;
    FieldFloatPair8* pairs = (FieldFloatPair8*)cursor->current;
    command->unk1c = pair_count;
    command->unk20 = first;
    command->unk24 = second;
    command->unk28 = pairs;
    FieldContext14Commands* object = (FieldContext14Commands*)D_001B6430->context->unk14;
    FieldCommandList8* channel;
    if (((cursor->unk420 >> 16) & 0xFFFF) == 0)
    {
        channel = &object->unk30;
    }
    else
    {
        channel = &object->unk250;
    }
    channel->list->func_004D74F0(command, (void*)-1);
    return 1;
}

/**
 * @brief Queue a command with a float value and an unsigned duration.
 * @param cursor Script operands and channel-selection state.
 * @return Always one; allocation failure sets the cursor wait value to one.
 */
extern "C" s32 func_001F04D0(FieldScriptCursorU32* cursor)
{
    float first = *(float*)cursor->current++;
    float second = (float)*cursor->current;
    FieldClass1512E0* command = new FieldClass1512E0(first, second);
    if (command == 0)
    {
        cursor->unk14 = 1.0f;
        return 1;
    }
    FieldContext14Commands* object = (FieldContext14Commands*)D_001B6430->context->unk14;
    FieldCommandList8* channel;
    if (((cursor->unk420 >> 16) & 0xFFFF) == 0)
    {
        channel = &object->unk30;
    }
    else
    {
        channel = &object->unk250;
    }
    channel->list->func_004D74F0(command, (void*)-1);
    return 1;
}

extern "C" s32 func_001F0620(FieldScriptCursorF32* cursor)
{
    float first = *cursor->current++;
    float second = *cursor->current;
    FieldContext14F0E40* context = (FieldContext14F0E40*)D_001B6430->context;
    func_002097F0(context->object + 0x30, first, second);
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F0670);

/** @brief Select a range mode and update its transition. @param cursor Script operands. @param count Operand count. @return Always one. */
extern "C" s32 func_001F06E0(FieldScriptCursorU32* cursor, u32 count)
{
    float duration = 0.0f;
    FieldRangeContext371* object = (FieldRangeContext371*)D_001B6430->context->unk14;
    FieldMotionRange* motion;
    u32 mode = *cursor->current++;
    motion = &object->motion;
    if (mode != 2 && object->unk300)
    {
        func_004D65C0(object->unk300);
        object->unk300->func_001DD7B0();
        object->unk300 = 0;
    }
    switch (mode)
    {
    case 0:
        if (count > 1)
        {
            duration = *(float*)cursor->current++;
        }
        field_range_flag(object, 1);
        func_002098C0(motion, 0.0f, duration);
        break;
    case 1:
    {
        s32 key = *cursor->current++;
        float height = *(float*)cursor->current++;
        if (count > 3)
        {
            duration = *(float*)cursor->current++;
        }
        FieldFlaggedListObject* found = func_001DEE30((FieldFlaggedListObject*)D_001B6430->context->unk04, key, 0xFFFFFFFF);
        if (found)
        {
            FieldVec4B position = ((FieldPosition30*)found)->position;
            position.y += height;
            field_subtract(position, object->motion.position);
            field_range_flag(object, 0);
            func_002098C0(motion, field_length_xyz(position), duration);
        }
        break;
    }
    case 2:
    {
        float first = *(float*)cursor->current++;
        u32 value = *cursor->current;
        func_00225550(object, value, first);
        break;
    }
    default:
        if (count > 1)
        {
            duration = *(float*)cursor->current++;
        }
        field_range_flag(object, 1);
        func_002098C0(motion, 0.0f, duration);
        break;
    }
    return 1;
}

/**
 * @brief Queue a callback using the packed script word.
 * @param cursor Script operand cursor.
 * @return Always one.
 */
extern "C" s32 func_001F09C0(FieldScriptCursorU32* cursor)
{
    u32 operand = *cursor->current;
    u32 value = operand & 0xFF;
    bool mode = (operand & 0x100) != 0;
    FieldClass150630* command = new FieldClass150630;
    command->unk18 = 1;
    command->unk19 = 1;
    command->unk1a = mode;
    command->unk1c = value;
    D_001B6614->func_004D74F0(command, (void*)-1);
    return 1;
}

/** @brief Set a range bound or its transition rate. @param cursor Script operands. @param count Operand count. @return One. */
extern "C" s32 func_001F0A80(FieldScriptCursorU32* cursor, u32 count)
{
    float target = *(float*)cursor->current++;
    s32 steps = 15;
    if (count > 1)
    {
        steps = (s32)*cursor->current;
    }
    FieldRangeContext371* object = (FieldRangeContext371*)D_001B6430->context->unk14;
    if ((float)steps == 0.0f)
    {
        object->current = target;
        if (object->unk308)
        {
            float value = object->current;
            if (value < 1.0f)
            {
                value = 1.0f;
            }
            if (!(value <= 44.0f))
            {
                value = 44.0f;
            }
            object->unk308->unk24c = value;
        }
    }
    else
    {
        object->target = target;
        object->change = (target - object->current) / (float)steps;
        object->duration = (float)steps;
    }
    return 1;
}

s32 func_001F0B40(FieldScriptCursorU32* cursor)
{
    FieldContext14F0E40* context = (FieldContext14F0E40*)D_001B6430->context;
    FieldObjectBit240* object = (FieldObjectBit240*)context->object;
    object->unk240_2 = (*cursor->current & 1) != 0;
    return 1;
}

/**
 * @brief Wait while the selected command list has a timer or queued nodes.
 * @param cursor Script channel-selection and wait state.
 * @return Zero while waiting, otherwise one.
 */
extern "C" s32 func_001F0B80(FieldScriptCursorU32* cursor)
{
    FieldContext14Commands* object = (FieldContext14Commands*)D_001B6430->context->unk14;
    FieldCommandList8* channel;
    if (((cursor->unk420 >> 16) & 0xFFFF) == 0)
    {
        channel = &object->unk30;
    }
    else
    {
        channel = &object->unk250;
    }
    if (static_cast<FieldClass151490*>(channel->list)->func_00239880())
    {
        cursor->unk14 = 1.0f;
        return 0;
    }
    return 1;
}

/**
 * @brief Queue a motion target with the script duration.
 * @param cursor Script operands and channel-selection state.
 * @return Always one.
 */
extern "C" s32 func_001F0C00(FieldScriptCursorU32* cursor)
{
    float target = ((float*)cursor->current)[1];
    FieldClass151300* command = new FieldClass151300((float)*cursor->current, target);
    FieldContext14Commands* object = (FieldContext14Commands*)D_001B6430->context->unk14;
    FieldCommandList8* channel;
    if (((cursor->unk420 >> 16) & 0xFFFF) == 0)
    {
        channel = &object->unk30;
    }
    else
    {
        channel = &object->unk250;
    }
    channel->list->func_004D74F0(command, (void*)-1);
    return 1;
}

/**
 * @brief Queue planar movement from the script duration and magnitude.
 * @param cursor Script operands and channel-selection state.
 * @return Always one.
 */
extern "C" s32 func_001F0D20(FieldScriptCursorU32* cursor)
{
    float magnitude = ((float*)cursor->current)[1];
    FieldClass151320* command = new FieldClass151320((float)*cursor->current, magnitude);
    FieldContext14Commands* object = (FieldContext14Commands*)D_001B6430->context->unk14;
    FieldCommandList8* channel;
    if (((cursor->unk420 >> 16) & 0xFFFF) == 0)
    {
        channel = &object->unk30;
    }
    else
    {
        channel = &object->unk250;
    }
    channel->list->func_004D74F0(command, (void*)-1);
    return 1;
}

s32 func_001F0E40(void* unused)
{
    FieldContext14F0E40* context = (FieldContext14F0E40*)D_001B6430->context;
    u8* object = context->object;
    func_001FF400(object + 0x250);
    func_002099B0(object + 0x30);
    return 1;
}

/**
 * @brief Test the default camera name and save motion state for other names.
 * @param cursor Script wait state.
 * @return Zero when the default name is active, otherwise one.
 */
extern "C" s32 func_001F0E80(FieldScriptCursorU32* cursor)
{
    FieldContextName36E* object = (FieldContextName36E*)D_001B6430->context->unk14;
    if (func_0013C800(object->unk35d, D_31A7E0) == 0)
    {
        cursor->unk14 = 1.0f;
        return 0;
    }
    func_00209B30(&object->unk30);
    func_001FF460((u8*)&object->unk250);
    return 1;
}

/** @brief Clear the selected command list and motion track. @param cursor Channel selection. @return One. */
extern "C" s32 func_001F0F00(FieldScriptCursorU32* cursor)
{
    FieldContextMotionChannels* context = (FieldContextMotionChannels*)D_001B6430->context->unk14;
    FieldClass151460* channel;
    if (((cursor->unk420 >> 16) & 0xFFFF) == 0)
    {
        channel = &context->unk30;
    }
    else
    {
        channel = &context->unk250;
    }
    channel->unk04->func_001DD730();
    channel->unk04->unk78 = 0.0f;
    channel->unk81_0 = 0;
    channel->unk08->func_002DDA70();
    return 1;
}

void FieldClass15B900::func_002DDA70()
{
    FieldClass15B950::func_002DDA70();
    func_002DCD20();
}

/** @brief Queue a command waiting to set the selected owner timer. @param cursor Duration and channel selection. @return One. */
extern "C" s32 func_001F0FC0(FieldScriptCursorU32* cursor)
{
    FieldClass1513E0* command = new FieldClass1513E0(*cursor->current);
    FieldContext14Commands* object = (FieldContext14Commands*)D_001B6430->context->unk14;
    FieldCommandList8* channel;
    if (((cursor->unk420 >> 16) & 0xFFFF) == 0)
    {
        channel = &object->unk30;
    }
    else
    {
        channel = &object->unk250;
    }
    channel->list->func_004D74F0(command, (void*)-1);
    return 1;
}

/**
 * @brief Queue a command waiting for the selected motion receiver.
 * @param cursor Script operands and channel-selection state.
 * @return Always one.
 */
extern "C" s32 func_001F10B0(FieldScriptCursorU32* cursor)
{
    FieldClass151340* command = new FieldClass151340;
    FieldContext14Commands* object = (FieldContext14Commands*)D_001B6430->context->unk14;
    FieldCommandList8* channel;
    if (((cursor->unk420 >> 16) & 0xFFFF) == 0)
    {
        channel = &object->unk30;
    }
    else
    {
        channel = &object->unk250;
    }
    channel->list->func_004D74F0(command, (void*)-1);
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F1190);

/**
 * @brief Queue a command waiting to invoke the selected motion callback.
 * @param cursor Script operands and channel-selection state.
 * @return Always one.
 */
extern "C" s32 func_001F1410(FieldScriptCursorU32* cursor)
{
    FieldClass151400* command = new FieldClass151400;
    FieldContext14Commands* object = (FieldContext14Commands*)D_001B6430->context->unk14;
    FieldCommandList8* channel;
    if (((cursor->unk420 >> 16) & 0xFFFF) == 0)
    {
        channel = &object->unk30;
    }
    else
    {
        channel = &object->unk250;
    }
    channel->list->func_004D74F0(command, (void*)-1);
    return 1;
}

/**
 * @brief Queue scalar motion from the script duration and target.
 * @param cursor Script operands and channel-selection state.
 * @return Always one.
 */
extern "C" s32 func_001F14F0(FieldScriptCursorU32* cursor)
{
    float target = ((float*)cursor->current)[1];
    FieldClass151360* command = new FieldClass151360((float)*cursor->current, target);
    FieldContext14Commands* object = (FieldContext14Commands*)D_001B6430->context->unk14;
    FieldCommandList8* channel;
    if (((cursor->unk420 >> 16) & 0xFFFF) == 0)
    {
        channel = &object->unk30;
    }
    else
    {
        channel = &object->unk250;
    }
    channel->list->func_004D74F0(command, (void*)-1);
    return 1;
}

/**
 * @brief Queue scalar motion from the script duration and target.
 * @param cursor Script operands and channel-selection state.
 * @return Always one.
 */
extern "C" s32 func_001F1610(FieldScriptCursorU32* cursor)
{
    float target = ((float*)cursor->current)[1];
    FieldClass151380* command = new FieldClass151380((float)*cursor->current, target);
    FieldContext14Commands* object = (FieldContext14Commands*)D_001B6430->context->unk14;
    FieldCommandList8* channel;
    if (((cursor->unk420 >> 16) & 0xFFFF) == 0)
    {
        channel = &object->unk30;
    }
    else
    {
        channel = &object->unk250;
    }
    channel->list->func_004D74F0(command, (void*)-1);
    return 1;
}

/**
 * @brief Queue angular motion from the script duration and target.
 * @param cursor Script operands and channel-selection state.
 * @return Always one.
 */
extern "C" s32 func_001F1730(FieldScriptCursorU32* cursor)
{
    float target = 6.2831854820251465f * ((float)(s32)cursor->current[1] / 360.0f);
    FieldClass1513A0* command = new FieldClass1513A0((float)*cursor->current, target);
    FieldContext14Commands* object = (FieldContext14Commands*)D_001B6430->context->unk14;
    FieldCommandList8* channel;
    if (((cursor->unk420 >> 16) & 0xFFFF) == 0)
    {
        channel = &object->unk30;
    }
    else
    {
        channel = &object->unk250;
    }
    channel->list->func_004D74F0(command, (void*)-1);
    return 1;
}

/**
 * @brief Queue rotation from the script duration and target.
 * @param cursor Script operands and channel-selection state.
 * @return Always one.
 */
extern "C" s32 func_001F1880(FieldScriptCursorU32* cursor)
{
    float target = 6.2831854820251465f * ((float)(s32)cursor->current[1] / 360.0f);
    FieldClass1513C0* command = new FieldClass1513C0((float)*cursor->current, target);
    FieldContext14Commands* object = (FieldContext14Commands*)D_001B6430->context->unk14;
    FieldCommandList8* channel;
    if (((cursor->unk420 >> 16) & 0xFFFF) == 0)
    {
        channel = &object->unk30;
    }
    else
    {
        channel = &object->unk250;
    }
    channel->list->func_004D74F0(command, (void*)-1);
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F19D0);



INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F1CD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F1E10);

/** @brief Destroy the callback object. */
FieldClass150630::~FieldClass150630()
{
}

/** @brief Apply the packed callback fields, then unlink and release this object. */
void FieldClass150630::func_001DF360()
{
    func_004DAFE0(D_001B6628, D_001B6650, unk18 != 0, unk19 != 0, unk1a != 0, unk1c, 0xFFFFFF);
    func_004D65C0(this);
    func_001DD7B0();
}

/** @brief Return the object kind. @return Sixteen. */
s32 FieldClass150630::func_001DF3D0()
{
    return 16;
}

/** @brief Unlink the callback and add it to the resident queue. */
void FieldClass150630::func_001DD7B0()
{
    func_004D65C0(this);
    func_0011ED90(D_001B65F4, this);
}

/** @brief Destroy the queue object. */
FieldClass150650::~FieldClass150650()
{
}

/** @brief Unlink and add this object to the resident queue. */
void FieldClass150650::func_001DD7B0()
{
    func_004D65C0(this);
    func_0011ED90(D_001B65F4, this);
}

extern "C" s32 func_001F2070(FieldScriptCursorF32* cursor)
{
    FieldPair57C* pair = (FieldPair57C*)func_0020F520(cursor);
    float value = *cursor->current;
    pair->first->value = value;
    pair->second->value = value;
    return 1;
}

/**
 * @brief Apply the script setting to each listed object with type bit 0x20.
 * @param cursor Script operands.
 * @return Always one.
 */
extern "C" s32 func_001F20B0(FieldScriptCursorU32* cursor)
{
    FieldClass150060* head = (FieldClass150060*)D_001B6430->context->unk04;
    FieldClass150060* current = head;
    while (true)
    {
        current = current->unk08;
        if (head == current)
        {
            break;
        }
        FieldClass150F90* object = static_cast<FieldClass150F90*>(current);
        if (object->unk78 & 0x20)
        {
            object->func_002042A0((*cursor->current & 1) != 0);
        }
    }
    return 1;
}

/**
 * @brief Queue the selected channel with the script value and flags.
 * @param cursor Script operands and channel selection.
 * @return Always one.
 */
extern "C" s32 func_001F2140(FieldScriptCursorU32* cursor)
{
    func_0020F520(cursor);
    float value = *(float*)cursor->current++;
    u32 flags = *cursor->current;
    FieldClass150F50* object = new(0) FieldClass150F50;
    if (object == 0)
    {
        cursor->unk14 = 1.0f;
        return 1;
    }
    object->unk14 = (cursor->unk420 >> 16) & 0xFFFF;
    object->unk18 = value;
    object->unk1c = flags;
    D_001B6614->func_004D74F0(object, (void*)-1);
    return 1;
}

/**
 * @brief Apply and store the script setting for each listed object with type bit 0x20.
 * @param cursor Script operands.
 * @return Always one.
 */
extern "C" s32 func_001F2230(FieldScriptCursorU32* cursor)
{
    FieldClass150060* head = (FieldClass150060*)D_001B6430->context->unk04;
    FieldClass150060* current = head;
    while (true)
    {
        current = current->unk08;
        if (head == current)
        {
            break;
        }
        FieldClass150F90* object = static_cast<FieldClass150F90*>(current);
        if (object->unk78 & 0x20)
        {
            object->func_00204370((*cursor->current & 1) != 0, 1);
        }
    }
    return 1;
}

/**
 * @brief Queue the resource-key setting on the selected object's command list.
 * @param cursor Script operands and object selection.
 * @return Always one.
 */
extern "C" s32 func_001F22C0(FieldScriptCursorU32* cursor)
{
    FieldActorCommandState* owner = (FieldActorCommandState*)func_0020F520(cursor);
    FieldClass1526C0* object = new FieldClass1526C0((*cursor->current & 1) != 0, cursor->current + 1);
    if (object == 0)
    {
        cursor->unk14 = 1.0f;
        return 1;
    }
    owner->commands.func_004D74F0(object, (void*)-1);
    return 1;
}

extern "C" s32 func_001F23E0(FieldScriptCursorF32* cursor)
{
    FieldFloat1F8* state = (FieldFloat1F8*)func_0020F520(cursor);
    state->value = *cursor->current;
    return 1;
}

s32 func_001F2420(FieldScriptCursorU32* cursor)
{
    FieldContext18F2420* context = (FieldContext18F2420*)D_001B6430->context;
    if (context->target != 0)
    {
        func_00220150(context->target, (*cursor->current & 1) != 0);
    }
    return 1;
}

/** Partial actor view containing its command list and status flags. */
struct FieldActorCommandState
{
    u8 unk00[0xC4];
    FieldClass152FA0 commands;
    u8 unk140[0x48D];
    u8 unk5cd_0_1 : 2;
    u8 unk5cd_2 : 1;
    u8 unk5cd_3 : 1;
    u8 unk5cd_4_7 : 4;

    /** @brief Test the command-wait flags. @return True when bit two is clear or bit three is set. */
    bool test_unk5cd() const
    {
        if (!unk5cd_2)
        {
            return true;
        }
        if (unk5cd_3)
        {
            return true;
        }
        return false;
    }
};


extern "C" void* func_0020F520(void*);

/**
 * @brief Queue the target word on the selected object's command list.
 * @param cursor Script operands and object selection.
 * @return Always one.
 */
extern "C" s32 func_001F2470(FieldScriptCursorU32* cursor)
{
    FieldActorCommandState* owner = (FieldActorCommandState*)func_0020F520(cursor);
    FieldClass152770* object = new FieldClass152770(*cursor->current);
    if (object == 0)
    {
        cursor->unk14 = 1.0f;
        return 1;
    }
    owner->commands.func_004D74F0(object, (void*)-1);
    return 1;
}

/**
 * @brief Queue the target float on the selected object's command list.
 * @param cursor Script operands and object selection.
 * @return Always one.
 */
extern "C" s32 func_001F2560(FieldScriptCursorU32* cursor)
{
    FieldActorCommandState* owner = (FieldActorCommandState*)func_0020F520(cursor);
    FieldClass152790* object = new FieldClass152790(*(float*)cursor->current);
    if (object == 0)
    {
        cursor->unk14 = 1.0f;
        return 1;
    }
    owner->commands.func_004D74F0(object, (void*)-1);
    return 1;
}

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

/**
 * @brief Copy scripted records into a command attached to the selected actor.
 * @param cursor Script cursor and actor-selection state.
 * @param word_count Number of record words to copy.
 * @return Always one.
 */
extern "C" s32 func_001F7470(FieldScriptCursorU32* cursor, s32 word_count)
{
    FieldActorCommandState* actor = (FieldActorCommandState*)func_0020F520(cursor);
    FieldClass152C70* command = new FieldClass152C70;
    u32* source = cursor->current;
    s32 byte_count = word_count * 4;
    command->unk1c = func_00113710(D_001B6430->context->unk6c, byte_count);
    if (command->unk1c != 0)
    {
        func_0013A4C0(command->unk1c, source, byte_count);
        command->unk20 = word_count / 10;
    }
    actor->commands.func_004D74F0(command, (void*)-1);
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F75C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F7690);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F76F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001DF360__16FieldClass150650Fv);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F7850);



/**
 * @brief Wait while the selected actor has command-list activity.
 * @param cursor Script cursor selecting the actor.
 * @return Zero while waiting, otherwise one.
 */
extern "C" s32 func_001F7A90(FieldScriptCursorU32* cursor)
{
    FieldActorCommandState* actor = (FieldActorCommandState*)func_0020F520(cursor);
    if (!actor)
    {
        return 1;
    }
    if (actor->test_unk5cd() && actor->commands.func_00239880())
    {
        cursor->unk14 = 1.0f;
        return 0;
    }
    return 1;
}

s32 func_001F7B40(void* cursor)
{
    void* object = func_0020F520(cursor);
    func_001DEDF0(D_001B6430->context->unk04, object);
    return 1;
}

/**
 * @brief Queue a command waiting for the selected actor's state bit.
 * @param cursor Script cursor selecting the actor.
 * @return Always one.
 */
extern "C" s32 func_001F7B80(FieldScriptCursorU32* cursor)
{
    FieldActorCommandState* actor = (FieldActorCommandState*)func_0020F520(cursor);
    FieldClass152DD0* command = new FieldClass152DD0;
    actor->commands.func_004D74F0(command, (void*)-1);
    return 1;
}

/**
 * @brief Queue a scalar interpolation command for the selected actor.
 * @param cursor Script cursor selecting the actor and supplying the command words.
 * @return Always one.
 */
extern "C" s32 func_001F7C30(FieldScriptCursorU32* cursor)
{
    FieldActorCommandState* actor = (FieldActorCommandState*)func_0020F520(cursor);
    float value = *(float*)cursor->current++;
    u32 word = *cursor->current++;
    float duration = *cursor->current;
    FieldClass152DF0* command = new FieldClass152DF0(value, word, duration);
    actor->commands.func_004D74F0(command, (void*)-1);
    return 1;
}

/**
 * @brief Queue removal of the selected actor and set its request flag.
 * @param cursor Script cursor selecting the actor.
 * @return Always one.
 */
extern "C" s32 func_001F7D10(FieldScriptCursorU32* cursor)
{
    FieldActorCommandState* actor = (FieldActorCommandState*)func_0020F520(cursor);
    FieldClass152E10* command = new FieldClass152E10;
    actor->commands.func_004D74F0(command, (void*)-1);
    actor->unk8d_1 = 1;
    return 1;
}

/**
 * @brief Queue a timer update for the selected actor's command list.
 * @param cursor Script cursor selecting the actor and supplying the timer word.
 * @return Always one.
 */
extern "C" s32 func_001F7DE0(FieldScriptCursorU32* cursor)
{
    FieldActorCommandState* actor = (FieldActorCommandState*)func_0020F520(cursor);
    FieldClass152E30* command = new FieldClass152E30((float)*cursor->current);
    actor->commands.func_004D74F0(command, (void*)-1);
    return 1;
}

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

/** @brief Add this object to the resident queue. */
void FieldClass1507A0::func_001DD7B0()
{
    func_0011ED90(D_001B65F4, this);
}

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

/**
 * @brief Allocate a 128-byte-aligned buffer, retrying after other listed loaders release storage.
 * @param owner Loader attached to the resource list.
 * @param size Requested buffer size in bytes.
 * @param mode Nonzero to use the Lib allocation path, zero to use the resident allocator.
 * @return Allocated buffer, or null when allocation or recovery fails after at most eight attempts.
 */
extern "C" void* func_001F9A80(FieldClass150070* owner, u32 size, s32 mode)
{
    FieldClass1530D0* manager = static_cast<FieldClass1530D0*>(static_cast<LibClass178DD0*>(owner->unk10));
    for (s32 attempt = 0; attempt < 8; attempt++)
    {
        void* result;
        if (mode)
        {
            func_00433AA0();
            result = func_00433880(size, 128);
        }
        else
        {
            result = func_00139700(128, size);
        }
        if (result)
        {
            return result;
        }
        if (manager->LibClass178DD0::unk0c == 1 || !func_0023AEB0(manager, owner))
        {
            break;
        }
    }
    return 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001ED7E0", func_001F9B60);
