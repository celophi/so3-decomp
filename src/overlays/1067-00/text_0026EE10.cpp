#include "include_asm.h"
#include "overlays/1067-00/text_001DD3C0.h"
#include "main/resident_data.h"
#include "main/resident_0010A0E0.h"
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

typedef struct FieldFlag272290
{
    u8 unk00[0x1C];
    u8 unk1c_0 : 1;
    u8 unk1c_1_7 : 7;
} FieldFlag272290;

/** Partial FieldListObject subclass with vtable D_154BB0 in main data. */
class FieldClass154BB0 : public FieldListObject
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
    lib_object_detach_owner(object);
    resident_enqueue_object(D_001B65F4, object);
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
struct FieldKeyedContextEntry
{
    u8 unk00[8];

    FieldKeyedContextEntry* next;

    u8 unk0c[8];

    void* value;

    u8 unk18[0x10];

    u32 key;

    u8 flags;
};

/** Context entry list whose sentinel entry starts at offset 0x14. */
struct FieldKeyedContextList
{
    u8 unk00[0x14];

    FieldKeyedContextEntry head;
};

/** Partial context holding its entry list. */
struct FieldKeyedContext
{
    u8 unk00[0xD8];

    FieldKeyedContextList* list;
};

/**
 * @brief Test flag bit 0 of the first context entry with the supplied key.
 * @param context Context containing the keyed entry list.
 * @param key Entry key.
 * @return Flag bit 0, or zero when no entry has the key.
 */
s32 field_context_test_entry_flag(void* context, u32 key)
{
    FieldKeyedContextEntry* entry;
    FieldKeyedContextEntry* head = &static_cast<FieldKeyedContext*>(context)->list->head;

    for (entry = head; ; )
    {
        entry = entry->next;

        if (entry == 0 || head == entry)
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

/**
 * @brief Return the value pointer of the first context entry with the supplied key.
 * @param context Context containing the keyed entry list.
 * @param key Entry key.
 * @return Stored pointer, or null when no entry has the key.
 */
void* field_context_get_entry_value(void* context, u32 key)
{
    FieldKeyedContextEntry* entry;
    FieldKeyedContextEntry* head = &static_cast<FieldKeyedContext*>(context)->list->head;

    for (entry = head; ; )
    {
        entry = entry->next;

        if (entry == 0 || head == entry)
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

/**
 * @brief Reset the first entry with the supplied key and apply an integer value.
 * @param context Context containing the keyed entry list.
 * @param key Entry key.
 * @param value Signed integer converted to float by the entry update.
 */
void field_context_apply_entry_value(void* context, u32 key, s32 value)
{
    FieldKeyedContextEntry* entry;
    FieldKeyedContextEntry* head = &static_cast<FieldKeyedContext*>(context)->list->head;

    for (entry = head; ; )
    {
        entry = entry->next;

        if (entry == 0 || head == entry)
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

/** Partial FieldListObject subclass with vtable D_156F60 in main data. */
class FieldClass156F60 : public FieldListObject
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
        lib_object_detach_owner(unkd8);
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
extern "C" void func_00271560(FieldListObject* object)
{
    lib_object_detach_owner(object);
    object->func_001DD7B0();
}

/** Partial FieldListObject subclass with vtable D_154BF0 in main data. */
class FieldClass154BF0 : public FieldListObject
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

/**
 * @brief Release request buffers and delay the next read when cleanup found a buffer.
 * @return The inherited request-release result.
 */
s32 FieldContextResourceLoader::poll_request_release()
{
    s32 result = FieldSceneResourceLoader::poll_request_release();
    if (result == 1)
    {
        start_delay = 10;
    }
    return result;
}

/** @brief Notify the context callback and finish the loader requests. */
void FieldContextResourceLoader::finish_requests()
{
    FieldClass1DD400* child = completion_callback;

    if (child != 0)
    {
        child->func_001DDB30(this);
    }

    request_state = 5;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_002717E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00271B50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", func_00271C60);

/**
 * @brief Append a file-backed resource request when a slot remains.
 * @param loader Resource loader.
 * @param file_key File key used to look up the resource size.
 * @param kind Resource kind stored in the request.
 * @return Appended request, or null when the array is full.
 */
extern "C" FieldSceneResourceRequest* field_append_file_request(FieldContextResourceLoader* loader, s32 file_key, s32 kind)
{
    if (loader->request_count >= loader->request_capacity)
    {
        return 0;
    }

    loader->requests[loader->request_count].reset_request();
    loader->requests[loader->request_count].file_key = file_key;
    loader->requests[loader->request_count].set_capacity(func_0011C8C0(D_001B65E4, loader->requests[loader->request_count].file_key));
    loader->requests[loader->request_count].slot_index = loader->request_count;
    loader->requests[loader->request_count].kind = kind;
    loader->request_count++;
    return &loader->requests[loader->request_count - 1];
}

/** @brief Destroy the field node and its secondary list. */
FieldClass154CC0::~FieldClass154CC0()
{
}

/**
 * @brief Report this object's default list kind.
 * @return Always 3.
 */
s32 FieldClass154CC0::get_default_list_kind()
{
    return 3;
}

/** @brief Detach this node and queue it for release. */
void FieldClass154CC0::func_001DD7B0()
{
    lib_object_detach_owner(this);
    resident_enqueue_object(D_001B65F4, this);
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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0026EE10", update__16FieldClass154CC0Fv);
