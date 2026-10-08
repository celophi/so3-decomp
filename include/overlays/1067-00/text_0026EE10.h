#ifndef SO3_OVERLAYS_1067_00_TEXT_0026EE10_H
#define SO3_OVERLAYS_1067_00_TEXT_0026EE10_H

#include "types.h"
#include "overlays/1067-00/text_0020DA30.h"
#ifdef __cplusplus
#include "overlays/1067-00/text_00202240.h"
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
typedef struct FieldState271750 FieldState271750;

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Return the type value for the D_154BB0 callback table. */
s32 func_0026EED0(const void* object);
/** @brief Return the type value for the D_154BF0 callback table. */
s32 func_002716B0(const void* object);
/** @brief Destroy the field object and its embedded list base. */
void* func_00271FC0(void* object, s32 flags);
/** @brief Return the type value for the embedded-list field object. */
s32 func_00272080(const void* object);
/** @brief Default callback for the embedded-list field object. */
void func_00272130(void* object);
/** @brief Default callback for the embedded-list field object. */
void func_002721A0(void* object);
/** @brief Default callback for the embedded-list field object. */
void func_00272220(void* object);
/** @brief Destroy the owner after adjusting from the embedded base at offset 0x14. */
void* func_00272350(void* object, s32 flags);


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
 * @brief Detach and queue the receiver.
 * @param object Receiver to detach and queue.
 */
void func_00272090(void* object);

/**
 * @brief Set state 10 when the receiver reports category 1.
 * @param object Receiver to inspect and update.
 */
void func_00271750(FieldState271750* object);

/**
 * @brief Clear the low bit of the receiver's flag byte.
 * @param object Receiver to update.
 */
void func_00272290(FieldFlag272290* object);

typedef struct FieldRoot26FF70 FieldRoot26FF70;

/**
 * @brief Test the active bit of a context entry selected by key.
 * @param context Context containing entries.
 * @param key Entry key.
 * @return One when the selected entry has its active bit set, otherwise zero.
 */
s32 func_0026F690(void* context, u32 key);

/**
 * @brief Find a context entry by key and return its value pointer.
 * @param context Context containing entries.
 * @param key Entry key.
 * @return Value of the selected entry, or null when no entry has the key.
 */
void* func_0026F6E0(void* context, u32 key);

/**
 * @brief Find a context entry by key and apply the supplied word.
 * @param context Context containing entries.
 * @param key Entry key.
 * @param value Word to apply.
 */
void func_0026F730(void* context, u32 key, u32 value);

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
    u8 unka0[0x38];
    FieldClass150070* unkd8;
};
#endif

#endif
