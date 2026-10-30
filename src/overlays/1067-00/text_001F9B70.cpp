#include "include_asm.h"
#include "main/resident_data.h"
#include "overlays/1067-00/text_001F9B70.h"
#include "overlays/1067-00/text_0026EE10.h"
#include "overlays/1067-00/text_0027E520.h"
#include "overlays/1067-00/text_0024DE80.h"
#include "overlays/1067-00/text_00257750.h"
#include "overlays/1067-00/text_002CEAF0.h"
#include "overlays/1067-00/text_002D3BD0.h"
#include "overlays/lib/text_004CD3A0.h"

extern "C" void func_4D9F40(FieldWordAt210*, const FieldWordAt210*);
extern "C" u8 D_001B6518;


struct FieldScriptCursorF32 { u8 pad[0x548]; float* current; };
struct FieldScriptCursorS8 { u8 pad[0x548]; s8* current; };
struct FieldScriptCursorS32 { u8 pad[0x548]; s32* current; };
struct FieldFlagScriptCursor
{
    u8 pad[0x4C8];
    u8 bit0 : 1;
    u8 rest : 7;
    u8 pad4C9[0x7F];
    u32* current;
};
struct FieldScriptCursorU16 { u8 pad[0x548]; u16* current; };
struct FieldScriptCursorF14 { u8 pad[0x14]; float value; u8 pad18[0x530]; u32* current; };
struct FieldScriptCursorU32 { u8 pad[0x548]; u32* current; };
struct FieldContext68 { u8 pad[0x68]; void* target; };
struct FieldContext08E0 { u8 pad[0xE0]; FieldOwner24E860* target; };
struct FieldContext08Flags { u8 pad[0xF3]; u8 valueF3; u8 valueF4; };
extern "C" void func_002D4AA0(void* target, u32 value);
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

/** Partial FieldListObject subclass with vtable D_1507C0 in main data. */
class FieldClass1507C0 : public FieldListObject
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass1507C0();
};

FieldClass1507C0::~FieldClass1507C0()
{
}

extern "C" void func_001FA270(void* object)
{
    lib_object_detach_owner(object);
    resident_enqueue_object(g_resident_release_queues, object);
}

extern "C" int func_001FA2A0(void* object)
{
    return 9;
}

extern "C" s32 func_001FA2B0(FieldScriptCursorU32* cursor)
{
    D_001B6518 = (*cursor->current & 1) != 0;
    return 1;
}

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
                        lib_object_detach_owner(entry);
                        entry->unk08();
                    }
                    break;
                case 0x4042:
                    if (key == entry->key254)
                    {
                        func_4289B0(entry);
                        lib_object_detach_owner(entry);
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
                lib_object_detach_owner(entry);
                entry->unk08();
            }
        }
    }
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FA460);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FA630);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FA8E0);

extern "C" s32 func_001FAB10(FieldScriptCursorU32* cursor)
{
    func_002D4AA0(((FieldContext68*)D_001B6430->context)->target, *cursor->current);
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FAB40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FACE0);

/** Partial LibTransform with vtable D_150990 in main data. */
class FieldClass150990 : public LibTransform
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass150990();

    /**
     * @brief Default transform hook that performs no work.
     */
    virtual void func_003EEBE0();

    /**
     * @brief Store the translation coordinates and mark the transform dirty.
     * @param x Horizontal translation.
     * @param y Vertical translation.
     * @param z Third translation component.
     */
    virtual void func_003EF790(float x, float y, float z);

    /**
     * @brief Copy the translation vector and mark the transform dirty.
     * @param value Translation vector to copy.
     */
    virtual void func_003EF780(const LibVector4* value);

    /**
     * @brief Copy the translation vector and mark the transform dirty.
     * @param value Translation vector to copy.
     */
    virtual void func_003EF770(const LibVector4* value);

    /**
     * @brief Build the rotation quaternion from three angles and mark the transform dirty.
     * @param x First rotation angle.
     * @param y Second rotation angle.
     * @param z Third rotation angle.
     */
    virtual void func_003EEF90(float x, float y, float z);

    /**
     * @brief Build the rotation quaternion from an angle vector and mark the transform dirty.
     * @param value Rotation angles to convert.
     */
    virtual void func_003EEF60(const LibVector4* value);

    /**
     * @brief Build the rotation quaternion from an angle vector and mark the transform dirty.
     * @param value Rotation angles to convert.
     */
    virtual void func_003EEF30(const LibVector4* value);

    /**
     * @brief Copy the rotation quaternion and mark the transform dirty.
     * @param value Quaternion to copy.
     */
    virtual void func_003EEF10(const LibVector4* value);

    /**
     * @brief Copy the rotation quaternion and mark the transform dirty.
     * @param value Quaternion to copy.
     */
    virtual void func_003EEEF0(const LibVector4* value);

    /**
     * @brief Store the quaternion components and mark the transform dirty.
     * @param x First quaternion component.
     * @param y Second quaternion component.
     * @param z Third quaternion component.
     * @param w Scalar quaternion component.
     */
    virtual void func_003EEED0(float x, float y, float z, float w);

    /**
     * @brief Store the scale components and mark the transform dirty.
     * @param x Horizontal scale factor.
     * @param y Vertical scale factor.
     * @param z Third scale factor.
     */
    virtual void func_003EF010(float x, float y, float z);

    /**
     * @brief Copy the scale vector and mark the transform dirty.
     * @param value Scale vector to copy.
     */
    virtual void func_003EEFF0(const LibVector4* value);

    /**
     * @brief Copy the scale vector and mark the transform dirty.
     * @param value Scale vector to copy.
     */
    virtual void func_003EEFD0(const LibVector4* value);

    /**
     * @brief Clear the inherited state byte.
     */
    virtual void func_003F4420();

    /**
     * @brief Default output hook that returns zero.
     * @param output Caller output; unused.
     * @return Zero.
     */
    virtual s32 func_003EEE20(void* output);

    /**
     * @brief Test whether the supplied value is negative.
     * @param value Value to test.
     * @param mode Additional caller mode; unused.
     * @return One if the value is negative, otherwise zero.
     */
    virtual s32 func_003EEE30(float value, float mode);

    /**
     * @brief Read the stored translation vector.
     * @return Pointer to the translation vector.
     */
    virtual const LibVector4* func_003EFAA0();

    /**
     * @brief Default matrix hook that performs no work.
     * @param matrix Caller matrix; unused.
     * @param context Caller context; unused.
     */
    virtual void func_003F4440(const void* matrix, void* context);

    /**
     * @brief Return the default transform creation result.
     * @return Null.
     */
    virtual LibClass178A90* func_003EEE50();

    /**
     * @brief Default receiver hook that performs no work.
     */
    virtual void func_003EEE60();

    /**
     * @brief Read the additional local translation.
     * @return Stored translation vector; only xyz is used to build the offset matrix.
     */
    virtual const LibVector4* get_offset_translation() const;

    /**
     * @brief Read the additional local rotation.
     * @return Stored quaternion in x, y, z, w order.
     */
    virtual const LibVector4* get_offset_rotation() const;

    /**
     * @brief Read the additional local scale.
     * @return Stored scale vector; only xyz is used to build the offset matrix.
     */
    virtual const LibVector4* get_offset_scale() const;

    /** @brief Return the object transformation matrix. @return Transformation matrix. */
    virtual const LibMatrix44Value* get_transform_matrix();
};

FieldClass150990::~FieldClass150990()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FB090);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FB180);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FB260);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FB340);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FB5D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FB6A0);

extern "C" s32 func_001FB8C0(FieldScriptCursorS32* cursor)
{
    s32* arg = cursor->current;
    cursor->current = arg + 1;
    s32 first = *arg;
    s32 second = *cursor->current;
    if (first >= 0)
    {
        ((FieldContext08Flags*)D_001B6430->context->unk08)->valueF3 = first;
    }
    if (second >= 0)
    {
        ((FieldContext08Flags*)D_001B6430->context->unk08)->valueF4 = second;
    }
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FB910);

extern "C" s32 func_001FB9D0(FieldFlagScriptCursor* cursor)
{
    if (!cursor->bit0)
    {
        return 1;
    }
    func_00258C90(D_001B6430->context->unk08, *cursor->current, 0, 0);
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FBA30);

extern "C" void func_001FBD10(void* object)
{
    lib_object_detach_owner(object);
    resident_enqueue_object(g_resident_release_queues, object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FBD40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FBEE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FC020);

extern "C" void func_001FC370(void* object)
{
    func_004DB570(object);
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

extern "C" void func_001FC980(FieldHeldObject20* object)
{
    func_0027E7D0(object);
    object->unk250 = 0;
    lib_object_detach_owner(object);
    resident_enqueue_object(g_resident_release_queues, object);
}

/**
 * @brief Reset request slots, counts, and auxiliary-file settings.
 * Existing buffer addresses are cleared without freeing their storage.
 * @param object Context loader view containing the allocated request slots.
 */
extern "C" void field_reset_context_resource_requests(FieldLateRecords* object)
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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", __ct__28FieldHeapSceneResourceLoaderFv);

extern "C" s32 func_001FCBD0(FieldScriptCursorU32* cursor)
{
    FieldOwner24E860* target = ((FieldContext08E0*)D_001B6430->context->unk08)->target;
    if (target == 0)
    {
        return 1;
    }
    func_0024E860(target, *cursor->current);
    return 1;
}

extern "C" s32 func_001FCC20(FieldScriptCursorF14* cursor)
{
    if (field_context_test_entry_flag(D_001B6430->context->unk08->current_object, *cursor->current))
    {
        cursor->value = 1.0f;
        return 0;
    }
    return 1;
}

extern "C" s32 func_001FCC80(FieldScriptCursorU32* cursor)
{
    u32* arg = cursor->current;
    cursor->current = arg + 1;
    u32 key = *arg;
    field_context_apply_entry_value(D_001B6430->context->unk08->current_object, key, *cursor->current);
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FCCD0);

extern "C" s32 func_001FCD20(FieldScriptCursorU16* cursor)
{
    func_0026FF10(D_001B6430->context->unk08->current_object, *cursor->current);
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FCD60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001F9B70", func_001FD180);

extern "C" s32 func_001FD340(void* object)
{
    FieldLateVirtual* target = func_00217A90(object, 5);
    if (target)
    {
        lib_object_detach_owner(target);
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
    lib_object_detach_owner(object);
    if (object)
    {
        object->unk00(1);
    }
}

/** Partial FieldListObject subclass with vtable D_150A20 in main data. */
class FieldClass150A20 : public FieldListObject
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass150A20();

    /**
     * @brief Release the object's storage through the Lib heap.
     * @param object Storage to release.
     */
    static void operator delete(void* object);
};

FieldClass150A20::~FieldClass150A20()
{
}
