#include "include_asm.h"
#include "main/resident_data.h"
#include "main/resident_0010A0E0.h"
#include "overlays/1067-00/text_001DD3C0.h"
#include "overlays/1067-00/text_0023B1D0.h"

extern "C" {
void func_44B210(void* object);
extern void* __vt__23ItemCreationClass172870[];
extern void* D_153170[];
extern void* D_1531D0[];
extern void* D_153244[];
extern void* D_153258[];
FieldObject23B950* func_4C4960(FieldObject23B950* object);
FieldObject23C180* func_0023D0C0(FieldObject23C180* object, s16 flags);
void __dl__FPv(void* object);
void func_466E40(void* point, float x, float y, float scale);
void func_002CFE40(void* target, s32 value);
void func_467570(FieldObject23D020* object, s32 enabled, s32 first, s32 second, float first_float, float second_float, float third_float);
void func_465B20(FieldRuntime* runtime, FieldObject23D020* object);
void func_421170(FieldObject23B850* object, FieldTarget23B850* target,
                 float x, float y, float z, float scale);
void func_420D20(FieldObject23B850* object, u32 color);
}

struct FieldObject23C180
{
    void** table;
    u8 unk04[0x8C];
    void** secondary_table;
    u8 unk94[0x54];
    void** third_table;
};

struct FieldTarget23B850
{
    u8 unk00[0xE8];
    float x;
    float y;
    float z;
};

struct FieldObject23B850
{
    u8 unk00[0x58];
    FieldTarget23B850* target;
};

struct FieldObject23D020
{
    u8 unk00[0xF0];
    u8 unkF0;
    u8 unkF1;
    u8 unkF2;
    u8 unkF3;
    float unkF4;
    float unkF8;
    u32 unkFC;
    u32 unk100;
    u8 unk104[8];
    s16 unk10C;
    s16 unk10E;
    s16 unk110;
    s16 unk112;
    s16 unk114;
    s16 unk116;
    u8 unk118;
    u8 unk119;
    u8 unk11A;
    u8 unk11B[9];
    s16 unk124;
    s16 unk126;
    u32 unk128;
    u32 unk12C;
};




struct FieldObject23BAB0
{
    u8 unk00[0x18];
    float x;
    float y;
    float z;
    float unk24;
    u8 unk28[0x14];
    u8 unk3C;
    u8 unk3D[0x1B];
    void* target;
    u8 unk5C[8];
    float unk64;
};

struct FieldObject23B280
{
    u8 unk00[0x3C];
    u8 flag3C;
    u8 unk3D[0x13];
    float x;
    float y;
    u8 unk58[0x1D];
    u8 flag75;
    u8 unk76[6];
    u8 width;
    u8 unk7D[3];
    float x_step;
    float y_step;
    float x_base;
    float y_base;
    u16 count;
};

struct FieldGlobal643C
{
    u8 unk00[0x10];
    void* target;
};

extern struct FieldGlobal643C* D_001B643C;

s32 func_0023B1D0(FieldObject23B1D0* object, s32 index, s32 direct)
{
    FieldNode23D310* node = func_0023D310(&object->nodes, index);
    if (node == 0)
    {
        return 0;
    }
    if (direct != 0)
    {
        float y = node->y;
        float x = node->x;
        object->x = x;
        object->y = y;
        object->flag75 = 1;
        object->flag3C = 1;
    }
    else
    {
        func_466E40(object->point40, node->x, node->y, 0.05f);
        func_002CFE40(D_001B643C->target, 0);
    }
    object->selected = index;
    return 1;
}

void func_0023B280(FieldObject23B280* object, u16 count)
{
    u16 current;
    float x;
    float y;
    object->count = count;
    current = object->count;
    y = object->y_base + (float)current * object->y_step;
    x = object->x_base + object->x_step * (float)(current % object->width);
    object->x = x;
    object->y = y;
    object->flag75 = 1;
    object->flag3C = 1;
}

void func_0023B310(FieldObject23B280* object)
{
    u16 current;
    float x;
    float y;
    object->count = 0;
    current = object->count;
    y = object->y_base + (float)current * object->y_step;
    x = object->x_base + object->x_step * (float)(current % object->width);
    object->x = x;
    object->y = y;
    object->flag75 = 1;
    object->flag3C = 1;
}

u16 func_0023B3A0(FieldState23B3A0* object)
{
    return object->unk90;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023B3B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023B530);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023B620);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023B6D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023B780);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023B7E0);

void func_0023B850(FieldObject23B850* object, FieldTarget23B850* target, u32 color)
{
    object->target = target;
    if (object->target != 0)
    {
        func_421170(object, target, target->x, target->y, target->z, 2.2f);
    }
    else
    {
        func_421170(object, target, 0.0f, 0.0f, 0.0f, 0.0f);
    }
    func_420D20(object, color);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023B8D0);

FieldObject23B950* func_0023B950(FieldObject23B950* object)
{
    func_4C4960(object);
    object->table = __vt__23ItemCreationClass172870;
    object->unk40 = 0;
    object->state = 6;
    object->table = D_153170;
    object->target = 0;
    object->unk5C = 0;
    return object;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023B9B0);

s32 func_0023BAB0(FieldObject23BAB0* object, float x, float y, float z)
{
    if (object->target == 0)
    {
        return 0;
    }
    if (z == 0.0f)
    {
        return 0;
    }
    object->unk64 = z;
    object->x = x;
    object->y = y;
    object->z = z;
    object->unk24 = 2.2f;
    object->unk3C = 1;
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023BB20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023BCC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023BD80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023BE00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023BE70);

void func_0023BF50(void* object)
{
    func_44B210(object);
    func_0011ED90(D_001B65F4, object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023BF80);

FieldObject23C180* func_0023C180(FieldObject23C180* object, s16 flags)
{
    if (object != 0)
    {
        object->table = D_1531D0;
        object->secondary_table = D_153244;
        object->third_table = D_153258;
        func_0023D0C0(object, 0);
        if (flags > 0)
        {
            __dl__FPv(object);
        }
    }
    return object;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023C200);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023C2F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023C360);

/** Partial FieldClass150070 object with vtable D_153270 in main data. */
class FieldClass153270 : public FieldClass150070
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass153270();
};

FieldClass153270::~FieldClass153270()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023C4F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023C550);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023C710);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023C7B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023C830);

void func_0023CB30(FieldObject23CB30* object)
{
    s32 row_count = object->row_count;
    s32 width = object->width;
    s32 index = object->index;
    object->unk114 = index + row_count * width;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023CB50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023CDB0);

void func_0023CE60(FieldObject23CE80* object, float first, float second)
{
    object->unkFC = first;
    object->unk100 = second;
}

void func_0023CE70(FieldObject23CEB0* object, float first, float second)
{
    object->unkF4 = first;
    object->unkF8 = second;
}

void func_0023CE80(FieldObject23CE80* object, u8 width, u8 height)
{
    object->width = width;
    object->height = height;
    object->count = object->width * object->height - 1;
}

void func_0023CEA0(FieldObject23CEA0* object, u32 value)
{
    object->unkad = value;
}

s32 func_0023CEB0(FieldObject23CEB0* object, float first, float second)
{
    object->unkF4 = first;
    object->unkF8 = second;
    object->unkC0 = object->unkF4;
    object->unkC4 = second;
    object->unkE5 = 1;
    object->unkAE = 1;
    return 1;
}

s32 func_0023CEE0(FieldObject23CEB0* object)
{
    s32 width = object->width;
    s32 count = object->count;
    float second = object->unkF8 + object->unk100 * (float)(count / width);
    float first = object->unkF4 + object->unkFC * (float)(count % width);
    object->unkC0 = first;
    object->unkC4 = second;
    object->unkE5 = 1;
    object->unkAE = 1;
    return 1;
}

s32 func_0023CF50(FieldObject23CEB0* object, s16 value, float first_delta, float second_delta)
{
    s32 width;
    s32 count;
    float second;
    float first;
    object->unk104 = first_delta;
    object->unk108 = second_delta;
    object->unkF4 = first_delta + object->unkC0;
    object->unkF8 = 16.0f + (second_delta + object->unkC4);
    if (value > 0)
    {
        object->count = value;
        object->unk114 = object->count + object->unk110 * object->width;
    }
    width = object->width;
    count = object->count;
    second = object->unkF8 + object->unk100 * (float)(count / width);
    first = object->unkF4 + object->unkFC * (float)(count % width);
    object->unkC0 = first;
    object->unkC4 = second;
    object->unkE5 = 1;
    object->unkAE = 1;
    return 1;
}

void func_0023D020(FieldObject23D020* object, float first_float, float second_float)
{
    object->unkF0 = 0;
    object->unkF1 = 0;
    object->unkF2 = 0;
    object->unkF3 = 0;
    object->unkF4 = -128.0f;
    object->unkF8 = -128.0f;
    object->unkFC = 0;
    object->unk100 = 0;
    object->unk10C = 0;
    object->unk10E = 0;
    object->unk110 = 0;
    object->unk112 = 0;
    object->unk114 = 0;
    object->unk116 = 0;
    object->unk118 = 1;
    object->unk119 = 1;
    object->unk11A = 0;
    object->unk126 = 0;
    object->unk124 = 0;
    object->unk12C = 0;
    object->unk128 = 0;
    func_467570(object, 1, 0, 0, first_float, second_float, 0.0f);
    func_465B20(D_001B657C, object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023D0C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023D170);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023D230);

void func_0023D2A0(void* object)
{
}

s32 func_0023D2B0(FieldObject153270* object)
{
    return 4;
}

/** Partial object with an attached Field object at offset 0x14. */
struct FieldObject23D2C0
{
    u8 unk00[0x14];
    FieldClass150070* attachment;
};

/**
 * @brief Delete the attached object, detach this object and release it.
 * @param object Object to release.
 */
extern "C" void func_0023D2C0(FieldObject23D2C0* object)
{
    object->attachment->func_001DD7B0();
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

FieldNode23D310* func_0023D310(FieldObject23D310* object, s32 count)
{
    FieldNode23D310* node = object->first->next;
    s32 i;
    for (i = 0; i < count; i++)
    {
        if (node == 0)
        {
            return 0;
        }
        node = node->next;
    }
    return node;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023D350);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023D360);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023D370);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023B1D0", func_0023D380);
