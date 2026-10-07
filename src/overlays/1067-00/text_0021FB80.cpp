#include "include_asm.h"
#include "main/resident_data.h"
#include "main/resident_0010A0E0.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/1067-00/text_0021FB80.h"
#include "overlays/1067-00/text_0022DC70.h"




typedef struct FieldContextIndex228E0
{
    u8 unk00[0xB8];
    s32 index;
} FieldContextIndex228E0;

typedef struct FieldRecord228E0
{
    u8 bytes[0x14];
} FieldRecord228E0;

struct FieldObject228E0
{
    u8 unk00[0x5C8];
    u8 state;
};

extern FieldRecord228E0 D_303CB0[];

struct FieldObject224E50
{
    u8 unk00[0x14];
    u32 unk14[8];
};

struct FieldObject29250
{
    u8 unk00[0x60];
    u8 unk60;
    u8 unk61[0x8F];
    u8 unkF0;
};

struct FieldObject22CC0
{
    u8 unk00[0x204];
    u32 flags;
};

typedef struct FieldContext10Object22CC0
{
    u8 unk00[0x24];
    u32 value;
} FieldContext10Object22CC0;

typedef struct FieldContext22CC0
{
    u8 unk00[0x10];
    FieldContext10Object22CC0* unk10;
    u8 unk14[0x28];
    struct FieldClass150060* unk3C;
} FieldContext22CC0;


typedef struct FieldOwner29310
{
    u8 unk00[0x5C4];
    void* linked;
} FieldOwner29310;

typedef struct FieldContext29310
{
    u8 unk00[0x38];
    FieldOwner29310* owner;
} FieldContext29310;

extern "C" s32 func_00202310(void* object);
extern "C" void func_4CEE30(float* vector);

struct FieldObject2B440
{
    u8 unk00[0x60];
    u8 unk60;
    u8 unk61[0x33];
    u8 unk94;
};

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_0021FB80);

s32 func_0021FC10(FieldObject152320* object)
{
    return 14;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_0021FC20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_0021FCF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_0021FD80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_0021FE00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_0021FE90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_0021FEC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_0021FFA0);

void func_00220150(void* object, s32 flag)
{
    FieldObject220150* state = static_cast<FieldObject220150*>(object);
    if (state->unk6D3_2 == 0)
    {
        state->unk6D2_6 = 1;
        state->unk6D2_7 = flag;
        state->value = 5.0f;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_002201B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00220420);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00220510);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_002205E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00220630);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_002207F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00220DB0);

FieldVector2624* func_00221430(FieldVector2624* vector, float first, float second, float third, float fourth)
{
    vector->x = first;
    vector->y = second;
    vector->z = third;
    vector->w = fourth;
    return vector;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00221450);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00221A70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00221CE0);

void func_002227F0(void* object)
{
    func_00233660((FieldObject232640*)object);
    while (!func_00202310(object))
    {
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00222840);

void func_002228E0(FieldObject228E0* object)
{
    FieldContextIndex228E0* context = (FieldContextIndex228E0*)D_001B6430->context->unk08;
    u8* record = D_303CB0[context->index].bytes;
    if (record[0x11] == 0)
    {
        object->state = 1;
    }
    else
    {
        object->state = 9;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00222930);

s32 func_00222CC0(FieldObject22CC0* object)
{
    FieldContext22CC0* context;
    u32 value;
    if (object->flags & 0x200)
    {
        return 0;
    }
    context = (FieldContext22CC0*)D_001B6430->context;
    value = context->unk10->value;
    if (value != 0)
    {
        return func_001EF150(context->unk3C, reinterpret_cast<FieldClass151510*>(object), value);
    }
    return 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00222D20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00222EF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00222F50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00223A40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00223FF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_002249A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00224A00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00224B90);

s32 func_00224C30(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00224C40);

s32 func_00224CD0(void* object)
{
    return 0;
}

void func_00224CE0(void* object)
{
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00224D10);

void func_00224E50(FieldObject224E50* object)
{
    object->unk14[0] = 0;
    object->unk14[1] = 0;
    object->unk14[2] = 0;
    object->unk14[3] = 0;
    object->unk14[4] = 0;
    object->unk14[5] = 0;
    object->unk14[6] = 0;
    object->unk14[7] = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00224E80);

s32 func_00224FC0(FieldObject152410* object)
{
    return 2;
}

void FieldClass152410::func_001DD7B0()
{
    if (unk300 != 0)
    {
        func_004D65C0(unk300);
        unk300->func_001DD7B0();
        unk300 = 0;
    }
    func_004D65C0(this);
    func_0011ED90(D_001B65F4, this);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00225040);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00225150);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_002252D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00225420);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00225550);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00225610);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00225700);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00225790);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00225800);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00225D80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00226000);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00226110);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00226340);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_002263B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_002267E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00226980);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_002269A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00226A50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00226B90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00226C10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00226CC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00227090);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_002270D0);

void func_00227130(void* object)
{
    FieldClass150F90* actor = static_cast<FieldClass150F90*>(object);
    actor->func_00204A10(actor->unk74);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00227160);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00227280);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00227310);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_002273B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00205710__16FieldClass152430FPC10FieldVec4A);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_002274F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00227610);

void func_002276F0(void* unused0, void* unused1, float* output)
{
    float vector[4];
    vector[0] = 0.0f;
    vector[1] = 0.0f;
    vector[2] = 0.0f;
    vector[3] = 1.0f;
    func_4CEE30(vector);
    func_004CE4C0(output, vector);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00227740);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00227840);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_002278F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00227CC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00228D30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00228DD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", __dt__16FieldClass152430Fv);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00228F80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", __ct__16FieldClass152430Fv);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00229150);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_002291B0);

s32 func_00229240(void* object)
{
    return 3;
}

void func_00229250(FieldObject29250* object)
{
    object->unk60 = object->unkF0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00229260);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_002292F0);

void func_00229310(void* object)
{
    FieldContext29310* context = (FieldContext29310*)D_001B6430->context;
    FieldOwner29310* owner = context->owner;
    if (object == owner->linked)
    {
        owner->linked = 0;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00229340);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00229440);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00229A80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00229E80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_00229FD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_0022A080);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_0022A160);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_0022A1C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_0022A1E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_0022A2D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_0022A310);

/** Partial object holding its slot in the owner's link table. */
typedef struct FieldObject2AA90
{
    u8 unk00[0xF1];
    u8 index;
} FieldObject2AA90;

/** Partial owner holding the table of linked objects. */
typedef struct FieldOwner2AA90
{
    u8 unk00[0x5A4];
    void* linked[256];
} FieldOwner2AA90;

/** Partial field context holding the link-table owner. */
typedef struct FieldContext2AA90
{
    u8 unk00[0x38];
    FieldOwner2AA90* owner;
} FieldContext2AA90;

/**
 * @brief Clear the object's slot in the owner's link table when it still holds the object.
 * @param object Linked object.
 */
extern "C" void func_0022AA90(FieldObject2AA90* object)
{
    void** links = ((FieldContext2AA90*)D_001B6430->context)->owner->linked;
    void** link = &links[object->index];
    if (object == *link)
    {
        *link = 0;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_0022AAD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_0022AD90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_0022AEF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_0022B010);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_0022B080);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_0022B110);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_0022B1A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", __dt__16FieldClass178A90Fv);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_0022B3D0);

void func_0022B440(FieldObject2B440* object)
{
    object->unk60 = object->unk94;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_0022B450);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_0022B460);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_0022B470);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0021FB80", func_0022B480);
