#include "include_asm.h"
#include "main/resident_data.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/1067-00/text_001DED80_callbacks.h"
#include "overlays/1067-00/text_0021FB80.h"
#include "overlays/1067-00/text_00202240_callbacks.h"
#include "overlays/1067-00/text_0022B490.h"
#include "overlays/1067-00/text_0022DC70.h"
#include "overlays/1067-00/text_0023DC90.h"
#include "overlays/1067-00/text_0026EE10.h"
#include "overlays/1067-00/text_002764D0.h"
#include "overlays/1067-00/text_0028E530.h"


typedef struct FieldTarget22BDD0
{
    u8 unk00[0x580];
    u32 value;
} FieldTarget22BDD0;

typedef struct FieldHandle22BDD0
{
    u8 unk00[0x7C];
    FieldTarget22BDD0* target;
} FieldHandle22BDD0;

typedef struct FieldCallback22BDD0
{
    u8 unk00[0x10];
    FieldHandle22BDD0* handle;
    u8 unk14[8];
    u32 value;
} FieldCallback22BDD0;

typedef struct FieldTarget22BDF0
{
    u8 unk00[0x57C];
    u32 value;
} FieldTarget22BDF0;

typedef struct FieldHandle22BDF0
{
    u8 unk00[0x7C];
    FieldTarget22BDF0* target;
} FieldHandle22BDF0;

typedef struct FieldCallback22BDF0
{
    u8 unk00[0x10];
    FieldHandle22BDF0* handle;
    u8 unk14[8];
    u32 value;
} FieldCallback22BDF0;

typedef struct FieldTarget22D4A0
{
    u8 unk00[0x1FC];
    u32 value;
} FieldTarget22D4A0;

typedef struct FieldHandle22D4A0
{
    u8 unk00[0x7C];
    FieldTarget22D4A0* target;
} FieldHandle22D4A0;

typedef struct FieldCallback22D4A0
{
    u8 unk00[0x10];
    FieldHandle22D4A0* handle;
    u8 unk14[8];
    u32 value;
} FieldCallback22D4A0;

typedef struct FieldObject22B790
{
    u8 unk00[0x1C];
    u8 unk1C;
    u8 unk1D;
    u8 unk1E;
    u8 unk1F;
    u32 unk20;
    u32 unk24;
    u32 unk28;
    u32 unk2C;
} FieldObject22B790;

typedef struct FieldTarget22C9E0
{
    u8 unk00[0x3AC];
    s32 selected;
    s32 current;
} FieldTarget22C9E0;

typedef struct FieldHandle22C9E0
{
    u8 unk00[0x7C];
    FieldTarget22C9E0* target;
} FieldHandle22C9E0;

typedef struct FieldCallback22C9E0
{
    u8 unk00[0x10];
    FieldHandle22C9E0* handle;
    u8 unk14[8];
    s32 value;
} FieldCallback22C9E0;

typedef struct FieldChild22BC90
{
    u8 unk00[0x48];
    u32 value;
    u8 unk4C[8];
    u16* limit;
} FieldChild22BC90;

typedef struct FieldNode22BC90
{
    u8 unk00[0x1C];
    FieldChild22BC90* child;
    u32 value;
} FieldNode22BC90;

typedef struct FieldTarget22BC90
{
    u8 unk00[0x584];
    FieldNode22BC90* node;
} FieldTarget22BC90;

typedef struct FieldHandle22BC90
{
    u8 unk00[0x7C];
    FieldTarget22BC90* target;
} FieldHandle22BC90;

typedef struct FieldCallback22BC90
{
    u8 unk00[0x10];
    FieldHandle22BC90* handle;
    u8 unk14[8];
    u32 value;
} FieldCallback22BC90;

typedef struct FieldTarget22C860
{
    u8 unk00[0x7C];
    FieldFloatState28F00* state;
} FieldTarget22C860;

typedef struct FieldCallback22C860
{
    u8 unk00[0x10];
    FieldTarget22C860* handle;
    u8 unk14[8];
    float target;
    float duration;
} FieldCallback22C860;

typedef struct FieldFlagTarget22D110
{
    u8 unk00[0x204];
    u32 flags;
} FieldFlagTarget22D110;

typedef struct FieldFlagHandle22D110
{
    u8 unk00[0x78];
    float value;
    FieldFlagTarget22D110* target;
} FieldFlagHandle22D110;

typedef struct FieldFlagCallback22D110
{
    u8 unk00[0x10];
    FieldFlagHandle22D110* handle;
} FieldFlagCallback22D110;

typedef struct FieldHandle22D150
{
    u8 unk00[0x7C];
    FieldObject233470* target;
} FieldHandle22D150;

typedef struct FieldCallback22D150
{
    u8 unk00[0x10];
    FieldHandle22D150* handle;
    u8 unk14[8];
    float first;
    float second;
    float third;
} FieldCallback22D150;

typedef struct FieldHandle22B8F0
{
    u8 unk00[0x7C];
    void* target;
} FieldHandle22B8F0;

typedef struct FieldCallback22B8F0
{
    u8 unk00[0x10];
    FieldHandle22B8F0* handle;
    u8 unk14[8];
    u32 value;
} FieldCallback22B8F0;

typedef struct FieldCallback22B920
{
    u8 unk00[0x10];
    FieldHandle22B8F0* handle;
    u8 unk14[8];
    float value;
} FieldCallback22B920;

typedef struct FieldCallback22BC30
{
    u8 unk00[0x10];
    FieldHandle22B8F0* handle;
    u8 unk14[8];
    s32 value;
} FieldCallback22BC30;

typedef struct FieldChild22D680
{
    u8 unk00[0x88];
    u8 value;
} FieldChild22D680;

typedef struct FieldTarget22D680
{
    u8 unk00[0x144];
    FieldChild22D680* child;
} FieldTarget22D680;

typedef struct FieldHandle22D680
{
    u8 unk00[0x78];
    float value;
    FieldTarget22D680* target;
} FieldHandle22D680;

typedef struct FieldCallback22D680
{
    u8 unk00[0x10];
    FieldHandle22D680* handle;
    u8 unk14[8];
    u8 value;
} FieldCallback22D680;

typedef struct FieldObject22B740
{
    u8 unk00[0x1C];
    u8 unk1C;
    u8 unk1D;
    u8 unk1E;
    u8 unk1F;
    float first;
    u32 unk24;
    float second;
    u32 unk2C;
} FieldObject22B740;

typedef struct FieldCallback22BCE0
{
    u8 unk00[0x10];
    FieldHandle22BC90* handle;
    u8 unk14[8];
    float first;
    float second;
    float third;
    float fourth;
    float fifth;
} FieldCallback22BCE0;

typedef struct FieldTarget22CA10
{
    u8 unk00[0x588];
    void* node;
} FieldTarget22CA10;

typedef struct FieldHandle22CA10
{
    u8 unk00[0x7C];
    FieldTarget22CA10* target;
} FieldHandle22CA10;

typedef struct FieldCallback22CA10
{
    u8 unk00[0x10];
    FieldHandle22CA10* handle;
    u8 unk14[8];
    u32 packed;
    float x;
    float y;
    float z;
} FieldCallback22CA10;

typedef struct FieldCallback22BEC0
{
    u8 unk00[0x1C];
    s32 id;
    u32 first;
    u32 second;
    u32 third;
} FieldCallback22BEC0;

typedef struct FieldHandle22C7D0
{
    u8 unk00[0x78];
    float value;
    void* state;
} FieldHandle22C7D0;

typedef struct FieldCallback22C7D0
{
    u8 unk00[0x10];
    FieldHandle22C7D0* handle;
    u8 unk14[8];
    s32 key;
    u8 data[16];
} FieldCallback22C7D0;

typedef struct FieldTarget22D180
{
    u8 unk00[0x70];
    s32 selector;
} FieldTarget22D180;

typedef struct FieldHandle22D180
{
    u8 unk00[0x78];
    float value;
    FieldTarget22D180* target;
} FieldHandle22D180;

typedef struct FieldCallback22D180
{
    u8 unk00[0x10];
    FieldHandle22D180* handle;
    u8 unk14[8];
    u32 value;
} FieldCallback22D180;

static inline s32 field_has_flag_22d110(FieldFlagTarget22D110* target, u32 mask)
{
    if (target->flags & mask)
    {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022B490);

void func_0022B550(void* object)
{
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022B580);

void func_0022B740(FieldObject22B740* object, u8 first, u8 second, float x, float y)
{
    object->unk1C = 0;
    object->unk1E = 0;
    object->unk1D = 0;
    object->unk2C = 0;
    object->second = 0.0f;
    object->unk24 = 0;
    object->first = 0.0f;
    object->unk1C = first;
    object->unk1D = second;
    object->first = x;
    object->second = y;
    if (y == 0.0f)
    {
        object->unk1E = object->unk1D;
    }
}

void func_0022B790(FieldObject22B790* object)
{
    object->unk1C = 0;
    object->unk1E = 0;
    object->unk1D = 0;
    object->unk2C = 0;
    object->unk28 = 0;
    object->unk24 = 0;
    object->unk20 = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022B7B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022B850);

s32 func_0022B8F0(FieldCallback22B8F0* object)
{
    func_00204070(object->handle->target, object->value);
    return 1;
}

s32 func_0022B920(FieldCallback22B920* object)
{
    func_002040E0(object->handle->target, object->value);
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022B950);

s32 func_0022B990(FieldCallback22B8F0* object)
{
    func_00232360(object->handle->target, object->value);
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022B9C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022BAA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022BB20);

s32 func_0022BC30(FieldCallback22BC30* object)
{
    func_00249AB0(object->handle->target, object->value);
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022BC60);

s32 func_0022BC90(FieldCallback22BC90* object)
{
    FieldNode22BC90* node = object->handle->target->node;
    FieldChild22BC90* child;
    if (node != 0)
    {
        node->value = object->value;
        child = node->child;
        if (child != 0 && node->value < *child->limit)
        {
            child->value = node->value;
        }
    }
    return 1;
}

s32 func_0022BCE0(FieldCallback22BCE0* object)
{
    FieldNode22BC90* node = object->handle->target->node;
    if (node != 0)
    {
        func_0028F710(node, object->first, object->second, object->third, object->fourth, object->fifth);
    }
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022BD30);

s32 func_0022BDD0(FieldCallback22BDD0* object)
{
    object->handle->target->value = object->value;
    return 1;
}

s32 func_0022BDF0(FieldCallback22BDF0* object)
{
    object->handle->target->value = object->value;
    return 1;
}

s32 func_0022BE10(FieldCallback22B8F0* object)
{
    func_00232730(object->handle->target);
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022BE40);

s32 func_0022BEC0(FieldCallback22BEC0* object)
{
    func_0027C0D0(D_001B6430->context->unk58, object->id, object->first, 0x40,
                  object->second, object->third);
    return 1;
}

s32 func_0022BF00(FieldCallback22BEC0* object)
{
    func_0027C130(D_001B6430->context->unk58, object->id, object->first);
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022BF30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022C380);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022C480);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022C590);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022C6F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022C730);

s32 func_0022C7D0(FieldCallback22C7D0* object)
{
    FieldHandle22C7D0* handle = object->handle;
    void* state = handle->state;
    FieldFlaggedListObject* node;
    if (object->key < 0)
    {
        node = 0;
    }
    else
    {
        node = func_001DEE30((FieldFlaggedListObject*)D_001B6430->context->unk04,
                              object->key, (u32)-1);
    }
    if (!func_00278D90(state, node, object->data))
    {
        handle->value = 1.0f;
        return 0;
    }
    return 1;
}

s32 func_0022C860(FieldCallback22C860* object)
{
    func_00278F00(object->handle->state, object->target, object->duration);
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022C890);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022C920);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022C990);

s32 func_0022C9E0(FieldCallback22C9E0* object)
{
    FieldTarget22C9E0* target = object->handle->target;
    s32 value = object->value;
    if (value == -1)
    {
        value = target->current;
    }
    target->selected = value;
    return 1;
}

s32 func_0022CA10(FieldCallback22CA10* object)
{
    void* node = object->handle->target->node;
    u32 packed;
    s32 index;
    if (node == 0)
    {
        return 1;
    }
    packed = object->packed;
    index = packed & 0xFFFF;
    if (index == 0xFFFF)
    {
        index = -1;
    }
    func_0028F5B0(node, index, (packed >> 16) & 0xFF, packed >> 24, object->x, object->y, object->z);
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022CA90);

s32 func_0022CF90(FieldFlagCallback22D110* object)
{
    FieldFlagHandle22D110* handle = object->handle;
    if (field_has_flag_22d110(handle->target, 0x400))
    {
        handle->value = 1.0f;
        return 0;
    }
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022CFD0);

s32 func_0022D110(FieldFlagCallback22D110* object)
{
    FieldFlagHandle22D110* handle = object->handle;
    if (field_has_flag_22d110(handle->target, 0x100))
    {
        handle->value = 1.0f;
        return 0;
    }
    return 1;
}

s32 func_0022D150(FieldCallback22D150* object)
{
    func_00233470(object->handle->target, object->first, object->second, object->third);
    return 1;
}

s32 func_0022D180(FieldCallback22D180* object)
{
    func_0026F8F0(D_001B6430->context->unk08->unkdc, object->handle->target->selector, object->value);
    return 1;
}

s32 func_0022D1C0(FieldCallback22D180* object)
{
    if (func_0026F870(D_001B6430->context->unk08->unkdc, object->handle->target->selector))
    {
        object->handle->value = 1.0f;
        return 0;
    }
    return 1;
}

s32 func_0022D230(FieldCallback22D180* object)
{
    func_0026FA40(D_001B6430->context->unk08->unkdc, object->handle->target->selector, object->value);
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022D270);

s32 func_0022D4A0(FieldCallback22D4A0* object)
{
    object->handle->target->value = object->value;
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022D4C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022D580);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022D600);

s32 func_0022D680(FieldCallback22D680* object)
{
    FieldHandle22D680* handle = object->handle;
    FieldChild22D680* child = handle->target->child;
    if (child != 0)
    {
        child->value = object->value;
        return 1;
    }
    handle->value = 1.0f;
    return 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022D6C0__16FieldClass152C70Fv);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022D800);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022D8C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022D960);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022DA10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0022B490", func_0022DB70);
