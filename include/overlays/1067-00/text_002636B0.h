#ifndef SO3_OVERLAYS_1067_00_TEXT_002636B0_H
#define SO3_OVERLAYS_1067_00_TEXT_002636B0_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Store an encoded word.
 * @param word Destination word.
 * @param value Encoded value to store.
 */
void func_002636F0(u32* word, u32 value);

typedef struct FieldOuterC000 FieldOuterC000;

/** Partial field object with two object pointers and a signed state byte. */
typedef struct FieldObject153E20
{
    u8 unk00[0x20];
    void* unk20;
    void* unk24;
    s8 unk28;
} FieldObject153E20;

/** @brief Store the object pointer at offset 0x20. */
void func_00263C70(FieldObject153E20* object, void* value);

/** @brief Store the object pointer at offset 0x24. */
void func_00263C80(FieldObject153E20* object, void* value);

/** @brief Read the object pointer at offset 0x24. */
void* func_00263C90(const FieldObject153E20* object);

/** @brief Store the signed state byte at offset 0x28. */
void func_00263CA0(FieldObject153E20* object, s8 value);

/** @brief Read the signed state byte at offset 0x28. */
s8 func_00263CB0(const FieldObject153E20* object);

/** Partial shared field base object used by the D_15AE70 vtable family. */
typedef struct FieldObject15AE70
{
    void* vtable;
    void* unk04;
    u8 unk08;
    u8 unk09;
    u16 unk0A;
    u8 unk0C;
    u8 unk0D;
    u8 unk0E[2];
    void* unk10;
    u8 unk14[0x84];
    void* unk98;
    void* unk9C;
} FieldObject15AE70;

/** @brief Store the unsigned byte at offset 0x0C. */
void func_002646C0(FieldObject15AE70* object, u8 value);
/** @brief Read the unsigned byte at offset 0x0C. */
u8 func_002646D0(const FieldObject15AE70* object);
/** @brief Store the unsigned byte at offset 0x08. */
void func_002646E0(FieldObject15AE70* object, u8 value);
/** @brief Store the unsigned halfword at offset 0x0A. */
void func_002646F0(FieldObject15AE70* object, u16 value);
/** @brief Store the object pointer at offset 0x98. */
/** @brief Read the object pointer at offset 0x98. */
/** @brief Store the object pointer at offset 0x9C. */
void func_00264720(FieldObject15AE70* object, void* value);
/** @brief Read the object pointer at offset 0x9C. */
void* func_00264730(const FieldObject15AE70* object);
/** @brief Store the object pointer at offset 0x04. */
void func_00264740(FieldObject15AE70* object, void* value);
/** @brief Read the object pointer at offset 0x04. */
void* func_00264750(const FieldObject15AE70* object);
/** @brief Read the object pointer at offset 0x10. */
void* func_00264760(const FieldObject15AE70* object);
/** @brief Read the unsigned byte at offset 0x0D. */
u8 func_00264970(const FieldObject15AE70* object);
/** @brief Store the unsigned byte at offset 0x0D. */
void func_00264980(FieldObject15AE70* object, u8 value);

/** Partial field object using the D_15AD40 vtable. */
typedef struct FieldObject15AD40
{
    u8 unk00[0x12C];
    u8 unk12C;
} FieldObject15AD40;

/** Partial field object using the D_1549D0 vtable. */
typedef struct FieldObject1549D0
{
    u8 unk00[0x38];
    void* unk38;
    u8 unk3C;
} FieldObject1549D0;

/** @brief Store the unsigned byte at offset 0x12C. */
void func_00265490(FieldObject15AD40* object, u8 value);
/** @brief Return the zero result for the shared field callback at slot 0xB0. */
u8 func_0026E3A0(const FieldObject15AE70* object);
/** @brief Return the zero result for the shared field callback at slot 0xB4. */
u8 func_0026E3B0(const FieldObject15AE70* object);
/** @brief Read the unsigned byte at offset 0x3C. */
u8 func_0026E3C0(const FieldObject1549D0* object);
/** @brief Read the object pointer at offset 0x38. */
void* func_0026E3D0(const FieldObject1549D0* object);

/** Field object callbacks used by secondary-base adjustment thunks. */
void func_00264CB0(void* object);
void* func_00264D30(void* object, s32 flags);
void func_00265870(void* object, float value);
void func_002658E0(void* object, s32 value);
u8 func_0026DAF0(void* object);
u8 func_0026DF90(void* object, void* value);
void func_0026E050(void* object);
void func_0026E0F0(void* object);
void func_0026E170(void* object);
void* func_0026E1A0(void* object, s32 flags);


/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00263CC0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00263CD0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00263CE0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00263CF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00263D00(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00263D10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00263D20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00263D30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00263D40(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00263D50(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00263D60(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00263D70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00263E80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00263F40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00264770(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00264780(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00264790(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002647A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002647B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002647C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002647D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002647E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002647F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00264800(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00264810(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00264820(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00264830(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00264840(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00264850(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00264860(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00264870(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00264880(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00264890(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002648A0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002648B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002648C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002648D0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002648E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002648F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00264900(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00264910(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00264920(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00264930(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00264940(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00264950(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00264960(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00264990(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026E390(void* object);

/**
 * @brief Set a present nested object's float to 128.0f and mark it active.
 * @param object Receiver containing the optional nested object.
 */
void func_0026C000(FieldOuterC000* object);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include "overlays/1067-00/text_002CD390.h"

/** Partial Field window with vtable D_1547D0 in main data and an object list at offset 0xFC. */
class FieldClass1547D0 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window. */
    virtual ~FieldClass1547D0();
    /** @brief Delete the listed objects, reset the list, then run the base handler. */
    virtual void func_slot0c();
    u8 unka8[0x54];
    u8 unkfc[4];
};

/** Partial Field window with vtable D_1548D0 in main data and an object list at offset 0xB8. */
class FieldClass1548D0 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window. */
    virtual ~FieldClass1548D0();
    /** @brief Run the base handler, then delete the listed objects. */
    virtual void func_slot0c();
    u8 unka8[0x10];
    u8 unkb8[4];
};
#endif

#endif
