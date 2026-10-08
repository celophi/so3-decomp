#include "include_asm.h"
#include "overlays/1067-00/text_001DD3C0.h"
#include "main/resident_data.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/1067-00/text_001ED7E0_callbacks.h"
#include "overlays/1067-00/text_0026EE10.h"
#include "overlays/1067-00/text_00207580.h"
#include "overlays/1067-00/text_0021FB80.h"



extern "C" void func_45B110(void* object, void* value);

typedef struct FieldWords270E90
{
    u32 words[4];
} FieldWords270E90;

typedef struct FieldState270EE0
{
    u8 unk00[0x1D0];
    u32 value;
    u8 unk1d4[0x0C];
    u32 flags;
    u8 unk1e4[0x16];
    u8 unk1fa_0 : 1;
    u8 unk1fa_1 : 1;
    u8 unk1fa_2_7 : 6;
} FieldState270EE0;

typedef struct FieldState271750
{
    u8 unk00[0x3C];
    u32 state;
} FieldState271750;

typedef struct FieldFlag272290
{
    u8 unk00[0x1C];
    u8 unk1c_0 : 1;
    u8 unk1c_1_7 : 7;
} FieldFlag272290;

/** Partial FieldClass150070 object with vtable D_154BB0 in main data. */
class FieldClass154BB0 : public FieldClass150070
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass154BB0();
};

FieldClass154BB0::~FieldClass154BB0()
{
}

void func_0026EEA0(void* object)
{
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

s32 func_0026EED0(const void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026EEE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026EFA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026F120);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026F1F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026F2C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026F3A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026F460);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026F670);

/** Keyed context entry linked from the context's entry list. */
struct FieldContextEntry26F690
{
    u8 unk00[8];
    FieldContextEntry26F690* next;
    u8 unk0c[8];
    void* value;
    u8 unk18[0x10];
    u32 key;
    u8 flags;
};

/** Context entry list whose sentinel entry starts at offset 0x14. */
struct FieldContextList26F690
{
    u8 unk00[0x14];
    FieldContextEntry26F690 head;
};

/** Partial context holding its entry list. */
struct FieldContext26F690
{
    u8 unk00[0xD8];
    FieldContextList26F690* list;
};

s32 func_0026F690(void* context, u32 key)
{
    FieldContextEntry26F690* entry;
    FieldContextEntry26F690* head = &static_cast<FieldContext26F690*>(context)->list->head;
    entry = head;
    while (1)
    {
        entry = entry->next;
        if (entry == 0)
        {
            break;
        }
        if (head == entry)
        {
            break;
        }
        if (key == entry->key)
        {
            return entry->flags & 1;
        }
    }
    return 0;
}

void* func_0026F6E0(void* context, u32 key)
{
    FieldContextEntry26F690* entry;
    FieldContextEntry26F690* head = &static_cast<FieldContext26F690*>(context)->list->head;
    entry = head;
    while (1)
    {
        entry = entry->next;
        if (entry == 0)
        {
            break;
        }
        if (head == entry)
        {
            break;
        }
        if (key == entry->key)
        {
            return entry->value;
        }
    }
    return 0;
}

void func_0026F730(void* context, u32 key, u32 value)
{
    FieldContextEntry26F690* entry;
    FieldContextEntry26F690* head = &static_cast<FieldContext26F690*>(context)->list->head;
    entry = head;
    while (1)
    {
        entry = entry->next;
        if (entry == 0)
        {
            break;
        }
        if (head == entry)
        {
            break;
        }
        if (key == entry->key)
        {
            func_002077B0(reinterpret_cast<FieldState2C*>(entry), value);
            break;
        }
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026F780);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026F800);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026F870);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026F8F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026FA40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026FC00);

/** Partial FieldClass150070 object with vtable D_156F60 in main data. */
class FieldClass156F60 : public FieldClass150070
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass156F60();
};

FieldClass156F60::~FieldClass156F60()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026FF10);

void func_0026FF70(FieldRoot26FF70* root)
{
    struct FieldClass151640* object = root->unkA8;
    FieldContext26FF70* context;
    func_0045B210(object, root->unkB0);
    func_45B110(object, root->unk7C);
    context = root->unkD8;
    if (context->unk8c != 0)
    {
        func_0020DDD0(object, context);
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_0026FFD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00270100);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00270190);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00270600);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_002706D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00270770);

FieldWords270E90* func_00270E90(FieldWords270E90* object)
{
    object->words[3] = 0;
    object->words[2] = 0;
    object->words[1] = 0;
    object->words[0] = 0;
    return object;
}

void func_00270EB0(FieldState270EE0* object, u32 flags)
{
    object->flags = flags;
    object->unk1fa_1 = (flags & 2) != 0;
}

void func_00270EE0(FieldState270EE0* object, u32 value, u32 flags)
{
    object->unk1fa_0 = 0;
    object->value = value;
    object->flags = flags;
    object->unk1fa_1 = (flags & 2) != 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00270F30);

void FieldClass154C10::func_001DD7B0()
{
    if (unkd8 != 0)
    {
        func_004D65C0(unkd8);
        unkd8->func_001DD7B0();
        unkd8 = 0;
    }
    FieldClass150F90::func_001DD7B0();
    func_00226340(D_001B6430->context->unk14);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00271130);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00271370);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_002714B0);

/**
 * @brief Detach the object, then delete it through its virtual handler.
 * @param object Object to release.
 */
extern "C" void func_00271560(FieldClass150070* object)
{
    func_004D65C0(object);
    object->func_001DD7B0();
}

/** Partial FieldClass150070 object with vtable D_154BF0 in main data. */
class FieldClass154BF0 : public FieldClass150070
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass154BF0();
};

FieldClass154BF0::~FieldClass154BF0()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00271630);

s32 func_002716B0(const void* object)
{
    return 9;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_002716C0);

void func_00271750(FieldState271750* object)
{
    if (func_001F9120(object) == 1)
    {
        object->state = 10;
    }
}

struct FieldObject271790;

/** Partial interface of the child notified by func_00271790. */
class FieldChild271790
{
public:
    // Placeholder virtuals in their vtable order (byte offset in the name); only
    // their positions are known.
    virtual void func_slot08();
    /** @brief Notify the child that its owner changed state. @param owner Owning field object. */
    virtual void func_slot0c(FieldObject271790* owner);
};

/** Partial field object with a state byte and an optional notified child. */
struct FieldObject271790
{
    u8 unk00[0x15];
    u8 state;
    u8 unk16[0xA];
    FieldChild271790* child;
};

/**
 * @brief Notify the child, if any, and set the object's state to five.
 * @param object Field object.
 */
extern "C" void func_00271790(FieldObject271790* object)
{
    FieldChild271790* child = object->child;
    if (child != 0)
    {
        child->func_slot0c(object);
    }
    object->state = 5;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_002717E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00271B50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00271C60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00271E60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00271FC0);

s32 func_00272080(const void* object)
{
    return 3;
}

void func_00272090(void* object)
{
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_002720C0);

void func_00272130(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00272140);

void func_002721A0(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_002721B0);

void func_00272220(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00272230);

void func_00272290(FieldFlag272290* object)
{
    object->unk1c_0 = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_002722B0);

// Compiler-generated this-adjustment thunk; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00272350);
