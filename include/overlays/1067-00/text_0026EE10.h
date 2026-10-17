#ifndef SO3_OVERLAYS_1067_00_TEXT_0026EE10_H
#define SO3_OVERLAYS_1067_00_TEXT_0026EE10_H

#include "types.h"
#include "overlays/1067-00/text_0020DA30.h"

/** Resource sizes, base file key, and auxiliary file offset for a field selection. */
typedef struct FieldResourceDescriptor
{
    u32 byte_count;

    u32 unk04;

    u32 unk08;

    s16 file_key;

    u8 unk0e[3];

    u8 auxiliary_file_offset;

    u8 unk12[2];
} FieldResourceDescriptor;

#ifdef __cplusplus
#include "overlays/1067-00/text_00202240.h"
#include "overlays/lib/text_004BD360.h"

/** 0x90-byte field list with its secondary list base at offset 0x14. */
class FieldClass154CC0 : public FieldListObject, public FieldClass1502A0
{
public:
    /** @brief Allocate through the Lib heap. @param size Allocation size. @return Allocated storage or null. */
    static void* operator new(u32 size);

    /** @brief Release storage through the Lib heap. @param object Storage to release. */
    static void operator delete(void* object)
    {
        func_004DB570(object);
    }

    /** @brief Initialize the inherited node and list. */
    FieldClass154CC0()
    {
    }

    /** @brief Destroy both list bases. */
    virtual ~FieldClass154CC0();

    /**
     * @brief Report this object's default list kind.
     * @return The class's default list kind.
     */
    virtual s32 get_default_list_kind();

    /** @brief Detach this node and queue it for release. */
    virtual void func_001DD7B0();

    /** @brief Advance the list's objects when their update conditions hold. */
    virtual void update();

    u8 unk8c[4];
};

#endif

struct LibClass178220;
/** Partial context containing its animation manager. */
typedef struct FieldContext26FF70
{
    u8 unk00[0x8C];
    struct LibClass178220* unk8c;
} FieldContext26FF70;

/** Partial field receiver containing the active shape resource and context. */
struct FieldRoot26FF70
{
    u8 unk00[0x7C];
    void* unk7C;
    u8 unk80[0x28];
    struct FieldClass151640* unkA8;
    u8 unkAC[4];
    void* unkB0;
    u8 unkB4[0x24];
    FieldContext26FF70* unkD8;
};

typedef struct FieldWords270E90 FieldWords270E90;
typedef struct FieldState270EE0 FieldState270EE0;
typedef struct FieldFlag272290 FieldFlag272290;

#ifdef __cplusplus
extern "C" {
#endif

extern FieldResourceDescriptor D_303CB0[];

/** @brief Return the type value for the D_154BB0 callback table. */
s32 func_0026EED0(const void* object);
/** @brief Return the type value for the D_154BF0 callback table. */
s32 func_002716B0(const void* object);
/** @brief Default callback for the embedded-list field object. */
void func_00272130(void* object);
/** @brief Default callback for the embedded-list field object. */
void func_002721A0(void* object);
/** @brief Default callback for the embedded-list field object. */
void func_00272220(void* object);


/**
 * @brief Detach and queue the receiver.
 * @param object Receiver to detach and queue.
 */
void func_0026EEA0(void* object);

/**
 * @brief Clear four words and return the receiver.
 * @param object Receiver to reset.
 * @return The receiver.
 */
FieldWords270E90* func_00270E90(FieldWords270E90* object);

/**
 * @brief Store the flags and update flag bit 1.
 * @param object Receiver to update.
 * @param flags Value to store and test.
 */
void func_00270EB0(FieldState270EE0* object, u32 flags);

/**
 * @brief Clear flag bit 0, store two words, and update flag bit 1.
 * @param object Receiver to update.
 * @param value Word stored at offset 0x1D0.
 * @param flags Word stored at offset 0x1E0 and tested for bit 1.
 */
void func_00270EE0(FieldState270EE0* object, u32 value, u32 flags);

/**
 * @brief Clear the low bit of the receiver's flag byte.
 * @param object Receiver to update.
 */
void func_00272290(FieldFlag272290* object);

typedef struct FieldRoot26FF70 FieldRoot26FF70;

/**
 * @brief Test flag bit 0 of the first context entry with the supplied key.
 * @param context Context containing entries.
 * @param key Entry key.
 * @return Flag bit 0, or zero when no entry has the key.
 */
s32 field_context_test_entry_flag(void* context, u32 key);

/**
 * @brief Find a context entry by key and return its value pointer.
 * @param context Context containing entries.
 * @param key Entry key.
 * @return Value of the selected entry, or null when no entry has the key.
 */
void* field_context_get_entry_value(void* context, u32 key);

/**
 * @brief Reset the first entry with the supplied key and apply an integer value.
 * @param context Context containing entries.
 * @param key Entry key.
 * @param value Signed integer converted to float by the entry update.
 */
void field_context_apply_entry_value(void* context, u32 key, s32 value);

/**
 * @brief Find a context entry by halfword key and process it.
 * @param context Context containing entries.
 * @param key Halfword entry key.
 */
void func_0026FF10(void* context, u16 key);

/**
 * @brief Apply the receiver's field values and update its active context.
 * @param root Receiver holding the values and context.
 */
void func_0026FF70(FieldRoot26FF70* root);

/**
 * @brief Test a field-context entry by selector.
 * @param context Field-context object.
 * @param selector Entry selector.
 * @return Nonzero when a matching entry is active.
 */
s32 func_0026F870(void* context, s32 selector);

/**
 * @brief Apply a selected field-context entry and callback word.
 * @param context Field-context object.
 * @param selector Entry selector.
 * @param value Callback word.
 * @return Zero.
 */
s32 func_0026F8F0(void* context, s32 selector, u32 value);

/**
 * @brief Apply the selected field-context entry with an alternate mode.
 * @param context Field-context object.
 * @param selector Entry selector.
 * @param value Callback word.
 * @return 1 when an entry is applied; otherwise 0.
 */
s32 func_0026FA40(void* context, s32 selector, u32 value);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/** Partial FieldClass150F90 with vtable D_154C10 in main data and an owned child at offset 0xD8. */
class FieldClass154C10 : public FieldClass150F90
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass154C10();
    /** @brief Detach and delete the child, release the base object and notify the field context. */
    virtual void func_001DD7B0();
    /**
     * @brief Test the inherited gate while the field context permits it.
     * @return False when context flag bit 5 at offset 0xF5 is clear, context
     *         bit 7 at offset 0xDD is set, or context bit 1 at offset 0xDE is set;
     *         otherwise the inherited gate result.
     */
    virtual bool func_00204420();
    u8 unka0[0x38];
    FieldListObject* unkd8;
};
#endif

#ifdef __cplusplus
#include "overlays/1067-00/text_001ED7E0.h"

/** Field resource loader that restores retained requests. */
class FieldContextResourceLoader : public FieldHeapSceneResourceLoader
{
public:
    /** @brief Clear the retained resource selection and reset the loader. */
    FieldContextResourceLoader()
    {
        resource_index = 0;

        unk40 = 0;

        load_kind = 1;

        reset_requests();
    }

    /** @brief Notify the context callback and finish the loader requests. */
    void finish_requests();

    virtual ~FieldContextResourceLoader();

    /**
     * @brief Advance retained resource reads and handle cancellation or field-state changes.
     * @param cancel_request One requests cancellation; zero advances loading.
     */
    virtual void update_requests(s32 cancel_request);

    /**
     * @brief Release request buffers and delay the next read when cleanup found a buffer.
     * @return One if a buffer was present before cleanup, two if a buffer remains pending, otherwise zero.
     */
    virtual s32 poll_request_release();

    /** @brief Consume completion and advance past requests already marked available. */
    virtual void advance_requests();

    /**
     * @brief Reset request slots, counts, and auxiliary-file settings.
     * Existing buffer addresses are cleared without freeing their storage.
     */
    virtual void reset_requests();

    u8 unk34[8];

    s32 start_delay;

    u32 unk40;

    /** Zero compares auxiliary file offsets, one loads the file, and two skips it. */
    u8 auxiliary_policy;

    u8 load_auxiliary : 1;

    u8 unk45_1_7 : 7;

    u8 unk46[2];

    s32 resource_index;
};
#endif

#ifdef __cplusplus
extern "C"
{
    /**
     * @brief Append a file-backed resource request when a slot remains.
     * @param loader Resource loader.
     * @param file_key File key used to look up the resource size.
     * @param kind Resource kind stored in the request.
     * @return Appended request, or null when the request array is full.
     */
    FieldSceneResourceRequest* field_append_file_request(FieldContextResourceLoader* loader, s32 file_key, s32 kind);

}
#endif

#endif
