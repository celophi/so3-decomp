#ifndef SO3_OVERLAYS_1067_00_TEXT_0027E520_H
#define SO3_OVERLAYS_1067_00_TEXT_0027E520_H

#include "types.h"

/** Partial holder of an attached object at offset 0x20, reached through D_001B645C. */
typedef struct FieldHeldObject20
{
    u8 unk00[0x20];
    void* unk20;
    u8 unk24[0x22C];
    s32 unk250;
} FieldHeldObject20;

/** Partial receiver containing its signed iteration count. */
typedef struct FieldObject1559A0
{
    u8 unk00[0x28];
    s32 unk28;
} FieldObject1559A0;

/** Partial receiver containing its signed iteration count. */
typedef struct FieldObject155B80
{
    u8 unk00[0x28];
    s32 unk28;
} FieldObject155B80;

/** Partial receiver containing its signed iteration count. */
typedef struct FieldObject155D90
{
    u8 unk00[0x28];
    s32 unk28;
} FieldObject155D90;

/** Partial receiver containing its signed iteration count. */
typedef struct FieldObject156150
{
    u8 unk00[0x28];
    s32 unk28;
} FieldObject156150;

/** Partial receiver containing its signed iteration count. */
typedef struct FieldObject156400
{
    u8 unk00[0x28];
    s32 unk28;
} FieldObject156400;

/** Base callback receivers identified by their installed tables. */
typedef struct FieldObject1564D0 FieldObject1564D0;
typedef struct FieldObject156080 FieldObject156080;

/** Base callback receiver identified by table D_156220. */
typedef struct FieldObject156220 FieldObject156220;

/** Base callback receivers identified by their installed tables. */
typedef struct FieldObject155C50 FieldObject155C50;
typedef struct FieldObject155E60 FieldObject155E60;

typedef struct FieldFloatSourceAF0 FieldFloatSourceAF0;
typedef struct FieldResourceHeader273720 FieldResourceHeader273720;
typedef struct FieldResourceRecord273720 FieldResourceRecord273720;

typedef struct FieldBitset154E80 FieldBitset154E80;

/** Partial array owner associated with table D_156A50. */
typedef struct FieldObject156A50
{
    u8 unk00[0xC];
    s32 unk0C;
    s32 unk10;
    u8 unk14[8];
    FieldBitset154E80* unk1C;
} FieldObject156A50;

/** Partial array owner associated with table D_156980. */
typedef struct FieldObject156980
{
    u8 unk00[0xC];
    s32 unk0C;
    s32 unk10;
    u8 unk14[8];
    FieldBitset154E80* unk1C;
} FieldObject156980;

/** Partial array owner associated with table D_1568B0. */
typedef struct FieldObject1568B0
{
    u8 unk00[0xC];
    s32 unk0C;
    s32 unk10;
    u8 unk14[8];
    FieldBitset154E80* unk1C;
} FieldObject1568B0;

/** Partial array owner associated with table D_1567E0. */
typedef struct FieldObject1567E0
{
    u8 unk00[0xC];
    s32 unk0C;
    s32 unk10;
    u8 unk14[8];
    FieldBitset154E80* unk1C;
} FieldObject1567E0;

/** Partial array owner associated with table D_156710. */
typedef struct FieldObject156710
{
    u8 unk00[0xC];
    s32 unk0C;
    s32 unk10;
    u8 unk14[8];
    FieldBitset154E80* unk1C;
} FieldObject156710;

/** Partial array owner associated with table D_156640. */
typedef struct FieldObject156640
{
    u8 unk00[0xC];
    s32 unk0C;
    s32 unk10;
    u8 unk14[8];
    FieldBitset154E80* unk1C;
} FieldObject156640;

/** Partial receiver containing its signed iteration count. */
typedef struct FieldObject156B70
{
    u8 unk00[0x28];
    s32 unk28;
} FieldObject156B70;

/** Partial receiver containing its signed iteration count. */
typedef struct FieldObject156C80
{
    u8 unk00[0x28];
    s32 unk28;
} FieldObject156C80;


/** Base callback receiver identified by table D_156D50. */
typedef struct FieldObject156D50 FieldObject156D50;

/** Partial array owner associated with table D_156E90. */
typedef struct FieldObject156E90
{
    u8 unk00[0xC];
    s32 unk0C;
    s32 unk10;
    u8 unk14[8];
    FieldBitset154E80* unk1C;
} FieldObject156E90;


/** Callback receiver identified by table D_157020. */
typedef struct FieldObject157020 FieldObject157020;

/** Partial receiver containing the state bit at offset 0x30. */
typedef struct FieldObject157040
{
    u8 unk00[0x30];
    u8 unk30_0_5 : 6;
    u8 unk30_6 : 1;
    u8 unk30_7 : 1;
} FieldObject157040;


typedef struct FieldScriptObject151D40 FieldScriptObject151D40;

#ifdef __cplusplus
extern "C" {
#endif

extern FieldHeldObject20* D_001B645C;

/**
 * @brief Detach and release the object at offset 0x20 through its virtual handler at vtable offset 0x10, then clear the pointer.
 * @param object Holder of the attached object; nothing happens when the pointer is null.
 */
void func_0027E7D0(FieldHeldObject20* object);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 3.
 */
u32 func_00280620(FieldObject1559A0* object);

/**
 * @brief Reset the signed iteration count.
 * @param object Callback receiver.
 * @param actor Actor supplied by the dispatcher.
 */
void func_00280630(FieldObject1559A0* object, FieldFloatSourceAF0* actor);

/**
 * @brief Return the floating-point limit.
 * @param object Callback receiver.
 * @return Always 2500.0f.
 */
float func_00280640(FieldObject1559A0* object);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 3.
 */
u32 func_002808F0(FieldObject155B80* object);

/**
 * @brief Reset the signed iteration count.
 * @param object Callback receiver.
 * @param actor Actor supplied by the dispatcher.
 */
void func_00280900(FieldObject155B80* object, FieldFloatSourceAF0* actor);

/**
 * @brief Return the floating-point limit.
 * @param object Callback receiver.
 * @return Always 2500.0f.
 */
float func_00280910(FieldObject155B80* object);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 3.
 */
u32 func_00280BC0(FieldObject155D90* object);

/**
 * @brief Reset the signed iteration count.
 * @param object Callback receiver.
 * @param actor Actor supplied by the dispatcher.
 */
void func_00280BD0(FieldObject155D90* object, FieldFloatSourceAF0* actor);

/**
 * @brief Return the floating-point limit.
 * @param object Callback receiver.
 * @return Always 2500.0f.
 */
float func_00280BE0(FieldObject155D90* object);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 3.
 */
u32 func_00280F70(FieldObject156150* object);

/**
 * @brief Reset the signed iteration count.
 * @param object Callback receiver.
 * @param actor Actor supplied by the dispatcher.
 */
void func_00280F80(FieldObject156150* object, FieldFloatSourceAF0* actor);

/**
 * @brief Return the floating-point limit.
 * @param object Callback receiver.
 * @return Always 2500.0f.
 */
float func_00280F90(FieldObject156150* object);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 3.
 */
u32 func_002811D0(FieldObject156400* object);

/**
 * @brief Reset the signed iteration count.
 * @param object Callback receiver.
 * @param actor Actor supplied by the dispatcher.
 */
void func_002811E0(FieldObject156400* object, FieldFloatSourceAF0* actor);

/**
 * @brief Return the floating-point limit.
 * @param object Callback receiver.
 * @return Always 2500.0f.
 */
float func_002811F0(FieldObject156400* object);

/**
 * @brief Leave the receiver unchanged after processing.
 * @param object Callback receiver.
 */
void func_002826D0(FieldObject1559A0* object);

/**
 * @brief Return the floating-point limit.
 * @param object Callback receiver.
 * @return Always 100.0f.
 */
float func_002826E0(FieldObject1559A0* object);

/**
 * @brief Leave resource binding unchanged.
 * @param object Callback receiver.
 * @param header Resource descriptor supplied by the caller.
 * @param records Resource records supplied by the caller.
 */
void func_00282700(FieldObject1559A0* object, FieldResourceHeader273720* header, FieldResourceRecord273720* records);

/**
 * @brief Report the default count for callback slot 0x80.
 * @param object Callback receiver.
 * @return Zero entries.
 */
s32 func_00282750(FieldObject1559A0* object);

/**
 * @brief Report the default count for callback slot 0x90.
 * @param object Callback receiver.
 * @return Zero entries.
 */
s32 func_00282790(FieldObject1559A0* object);

/**
 * @brief Leave the receiver unchanged for the scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00282820(FieldObject1559A0* object, float value);

/**
 * @brief Report the default mode value.
 * @param object Callback receiver.
 * @return Always zero.
 */
u8 func_00282860(FieldObject1559A0* object);

/**
 * @brief Leave the receiver unchanged after processing.
 * @param object Callback receiver.
 */
void func_002828D0(FieldObject155C50* object);

/**
 * @brief Return the default floating-point limit.
 * @param object Callback receiver.
 * @return Always 100.0f.
 */
float func_002828E0(FieldObject155C50* object);

/**
 * @brief Leave resource binding unchanged.
 * @param object Callback receiver.
 * @param header Resource descriptor supplied by the caller.
 * @param records Resource records supplied by the caller.
 */
void func_00282900(FieldObject155C50* object, FieldResourceHeader273720* header, FieldResourceRecord273720* records);

/**
 * @brief Report the default count for callback slot 0x80.
 * @param object Callback receiver.
 * @return Zero entries.
 */
s32 func_00282950(FieldObject155C50* object);

/**
 * @brief Report the default count for callback slot 0x90.
 * @param object Callback receiver.
 * @return Zero entries.
 */
s32 func_00282990(FieldObject155C50* object);

/**
 * @brief Leave the receiver unchanged for the scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00282A20(FieldObject155C50* object, float value);

/**
 * @brief Report the default mode value.
 * @param object Callback receiver.
 * @return Always zero.
 */
u8 func_00282A60(FieldObject155C50* object);

/**
 * @brief Leave the receiver unchanged after processing.
 * @param object Callback receiver.
 */
void func_00282AD0(FieldObject155E60* object);

/**
 * @brief Return the default floating-point limit.
 * @param object Callback receiver.
 * @return Always 100.0f.
 */
float func_00282AE0(FieldObject155E60* object);

/**
 * @brief Leave resource binding unchanged.
 * @param object Callback receiver.
 * @param header Resource descriptor supplied by the caller.
 * @param records Resource records supplied by the caller.
 */
void func_00282B00(FieldObject155E60* object, FieldResourceHeader273720* header, FieldResourceRecord273720* records);

/**
 * @brief Report the default count for callback slot 0x80.
 * @param object Callback receiver.
 * @return Zero entries.
 */
s32 func_00282B50(FieldObject155E60* object);

/**
 * @brief Report the default count for callback slot 0x90.
 * @param object Callback receiver.
 * @return Zero entries.
 */
s32 func_00282B90(FieldObject155E60* object);

/**
 * @brief Leave the receiver unchanged for the scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00282C20(FieldObject155E60* object, float value);

/**
 * @brief Report the default mode value.
 * @param object Callback receiver.
 * @return Always zero.
 */
u8 func_00282C60(FieldObject155E60* object);

/**
 * @brief Leave the receiver unchanged after processing.
 * @param object Callback receiver.
 */
void func_00282CD0(FieldObject156220* object);

/**
 * @brief Return the default floating-point limit.
 * @param object Callback receiver.
 * @return Always 100.0f.
 */
float func_00282CE0(FieldObject156220* object);

/**
 * @brief Leave resource binding unchanged.
 * @param object Callback receiver.
 * @param header Resource descriptor supplied by the caller.
 * @param records Resource records supplied by the caller.
 */
void func_00282D00(FieldObject156220* object, FieldResourceHeader273720* header, FieldResourceRecord273720* records);

/**
 * @brief Report the default count for callback slot 0x80.
 * @param object Callback receiver.
 * @return Zero entries.
 */
s32 func_00282D50(FieldObject156220* object);

/**
 * @brief Report the default count for callback slot 0x90.
 * @param object Callback receiver.
 * @return Zero entries.
 */
s32 func_00282D90(FieldObject156220* object);

/**
 * @brief Leave the receiver unchanged for the scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00282E20(FieldObject156220* object, float value);

/**
 * @brief Report the default mode value.
 * @param object Callback receiver.
 * @return Always zero.
 */
u8 func_00282E60(FieldObject156220* object);

/**
 * @brief Leave the receiver unchanged after processing.
 * @param object Callback receiver.
 */
void func_00282ED0(FieldObject1564D0* object);

/**
 * @brief Return the default floating-point limit.
 * @param object Callback receiver.
 * @return Always 100.0f.
 */
float func_00282EE0(FieldObject1564D0* object);

/**
 * @brief Leave resource binding unchanged.
 * @param object Callback receiver.
 * @param header Resource descriptor supplied by the caller.
 * @param records Resource records supplied by the caller.
 */
void func_00282F00(FieldObject1564D0* object, FieldResourceHeader273720* header, FieldResourceRecord273720* records);

/**
 * @brief Report the default count for callback slot 0x80.
 * @param object Callback receiver.
 * @return Zero entries.
 */
s32 func_00282F50(FieldObject1564D0* object);

/**
 * @brief Report the default count for callback slot 0x90.
 * @param object Callback receiver.
 * @return Zero entries.
 */
s32 func_00282F90(FieldObject1564D0* object);

/**
 * @brief Leave the receiver unchanged for the scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00283020(FieldObject1564D0* object, float value);

/**
 * @brief Report the default mode value.
 * @param object Callback receiver.
 * @return Always zero.
 */
u8 func_00283060(FieldObject1564D0* object);

/**
 * @brief Leave the receiver unchanged after processing.
 * @param object Callback receiver.
 */
void func_002830D0(FieldObject156080* object);

/**
 * @brief Return the default floating-point limit.
 * @param object Callback receiver.
 * @return Always 100.0f.
 */
float func_002830E0(FieldObject156080* object);

/**
 * @brief Leave resource binding unchanged.
 * @param object Callback receiver.
 * @param header Resource descriptor supplied by the caller.
 * @param records Resource records supplied by the caller.
 */
void func_00283100(FieldObject156080* object, FieldResourceHeader273720* header, FieldResourceRecord273720* records);

/**
 * @brief Report the default count for callback slot 0x80.
 * @param object Callback receiver.
 * @return Zero entries.
 */
s32 func_00283150(FieldObject156080* object);

/**
 * @brief Report the default count for callback slot 0x90.
 * @param object Callback receiver.
 * @return Zero entries.
 */
s32 func_00283190(FieldObject156080* object);

/**
 * @brief Leave the receiver unchanged for the scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00283220(FieldObject156080* object, float value);

/**
 * @brief Report the default mode value.
 * @param object Callback receiver.
 * @return Always zero.
 */
u8 func_00283260(FieldObject156080* object);

/**
 * @brief Get the associated bitset object.
 * @param object Callback receiver.
 * @return Stored bitset object pointer.
 */
FieldBitset154E80* func_00283350(FieldObject156A50* object);

/**
 * @brief Get the first configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0xC.
 */
s32 func_00283360(FieldObject156A50* object);

/**
 * @brief Get the second configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0x10.
 */
s32 func_00283370(FieldObject156A50* object);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 0x20.
 */
u32 func_00283380(FieldObject156A50* object);

/**
 * @brief Get the associated bitset object.
 * @param object Callback receiver.
 * @return Stored bitset object pointer.
 */
FieldBitset154E80* func_00283480(FieldObject156980* object);

/**
 * @brief Get the first configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0xC.
 */
s32 func_00283490(FieldObject156980* object);

/**
 * @brief Get the second configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0x10.
 */
s32 func_002834A0(FieldObject156980* object);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 1.
 */
u32 func_002834B0(FieldObject156980* object);

/**
 * @brief Get the associated bitset object.
 * @param object Callback receiver.
 * @return Stored bitset object pointer.
 */
FieldBitset154E80* func_002835B0(FieldObject1568B0* object);

/**
 * @brief Get the first configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0xC.
 */
s32 func_002835C0(FieldObject1568B0* object);

/**
 * @brief Get the second configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0x10.
 */
s32 func_002835D0(FieldObject1568B0* object);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 0x20.
 */
u32 func_002835E0(FieldObject1568B0* object);

/**
 * @brief Get the associated bitset object.
 * @param object Callback receiver.
 * @return Stored bitset object pointer.
 */
FieldBitset154E80* func_002836D0(FieldObject1567E0* object);

/**
 * @brief Get the first configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0xC.
 */
s32 func_002836E0(FieldObject1567E0* object);

/**
 * @brief Get the second configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0x10.
 */
s32 func_002836F0(FieldObject1567E0* object);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 0x20.
 */
u32 func_00283700(FieldObject1567E0* object);

/**
 * @brief Get the associated bitset object.
 * @param object Callback receiver.
 * @return Stored bitset object pointer.
 */
FieldBitset154E80* func_00283800(FieldObject156710* object);

/**
 * @brief Get the first configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0xC.
 */
s32 func_00283810(FieldObject156710* object);

/**
 * @brief Get the second configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0x10.
 */
s32 func_00283820(FieldObject156710* object);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 1.
 */
u32 func_00283830(FieldObject156710* object);

/**
 * @brief Get the associated bitset object.
 * @param object Callback receiver.
 * @return Stored bitset object pointer.
 */
FieldBitset154E80* func_00283920(FieldObject156640* object);

/**
 * @brief Get the first configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0xC.
 */
s32 func_00283930(FieldObject156640* object);

/**
 * @brief Get the second configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0x10.
 */
s32 func_00283940(FieldObject156640* object);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 0x20.
 */
u32 func_00283950(FieldObject156640* object);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 1.0f.
 */
float func_00286400(FieldObject156A50* object);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 1.0f.
 */
float func_00286410(FieldObject156980* object);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 1.0f.
 */
float func_00286420(FieldObject1568B0* object);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 1.0f.
 */
float func_00286430(FieldObject1567E0* object);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 1.0f.
 */
float func_00286440(FieldObject156710* object);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 1.0f.
 */
float func_00286450(FieldObject156640* object);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Callback receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00286620(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Callback receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00286880(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Callback receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00286890(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Callback receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002868A0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 3.
 */
u32 func_00288220(FieldObject156B70* object);

/**
 * @brief Reset the signed iteration count.
 * @param object Callback receiver.
 * @param actor Actor supplied by the dispatcher.
 */
void func_00288230(FieldObject156B70* object, FieldFloatSourceAF0* actor);

/**
 * @brief Return the floating-point limit.
 * @param object Callback receiver.
 * @return Always 2500.0f.
 */
float func_00288240(FieldObject156B70* object);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 3.
 */
u32 func_00288640(FieldObject156C80* object);

/**
 * @brief Reset the signed iteration count.
 * @param object Callback receiver.
 * @param actor Actor supplied by the dispatcher.
 */
void func_00288650(FieldObject156C80* object, FieldFloatSourceAF0* actor);

/**
 * @brief Return the floating-point limit.
 * @param object Callback receiver.
 * @return Always 2500.0f.
 */
float func_00288660(FieldObject156C80* object);

/**
 * @brief Perform the default callback without changing the receiver.
 * @param object Callback receiver.
 */
void func_00289450(FieldObject156D50* object);

/**
 * @brief Return the default floating-point limit.
 * @param object Callback receiver.
 * @return Always 100.0f.
 */
float func_00289460(FieldObject156D50* object);

/**
 * @brief Handle the resource callback without changing the receiver.
 * @param object Callback receiver.
 * @param resource Resource descriptor supplied by the dispatcher.
 * @param records Resource records supplied by the dispatcher.
 */
void func_00289480(FieldObject156D50* object, FieldResourceHeader273720* resource, FieldResourceRecord273720* records);

/**
 * @brief Get the first default element count.
 * @param object Callback receiver.
 * @return Always zero.
 */
s32 func_002894D0(FieldObject156D50* object);

/**
 * @brief Get the second default element count.
 * @param object Callback receiver.
 * @return Always zero.
 */
s32 func_00289510(FieldObject156D50* object);

/**
 * @brief Handle the floating-point callback without changing the receiver.
 * @param object Callback receiver.
 * @param value Floating-point value supplied by the dispatcher.
 */
void func_002895A0(FieldObject156D50* object, float value);

/**
 * @brief Get the default byte mode.
 * @param object Callback receiver.
 * @return Always zero.
 */
u8 func_002895E0(FieldObject156D50* object);

/**
 * @brief Get the associated bitset object.
 * @param object Callback receiver.
 * @return Stored bitset object pointer.
 */
FieldBitset154E80* func_002896E0(FieldObject156E90* object);

/**
 * @brief Get the first configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0xC.
 */
s32 func_002896F0(FieldObject156E90* object);

/**
 * @brief Get the second configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0x10.
 */
s32 func_00289700(FieldObject156E90* object);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 1.
 */
u32 func_00289710(FieldObject156E90* object);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 1.0f.
 */
float func_00289EB0(FieldObject156E90* object);

/**
 * @brief Report the default signed category.
 * @param object Callback receiver.
 * @return Always 4.
 */
s32 func_0028E130(FieldObject157020* object);

/**
 * @brief Report the default signed category.
 * @param object Callback receiver.
 * @return Always 2.
 */
s32 func_0028E1E0(FieldObject157040* object);

/**
 * @brief Set bit 6 of the receiver state byte.
 * @param object Callback receiver.
 */
void func_0028E1F0(FieldObject157040* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0027F3D0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00280660(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00280930(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00280AE0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00280C00(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00280EE0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00280FB0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00281210(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002826C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002826F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282710(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282720(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282730(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282740(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282760(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282770(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282780(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002827A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002827B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002827C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002827D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002827E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002827F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282800(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282810(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282840(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282850(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282870(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282880(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282890(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002828B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002828C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002828F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282910(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282920(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282930(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282940(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282960(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282970(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282980(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002829A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002829B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002829C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002829D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002829E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002829F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282A00(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282A10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282A40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282A50(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282A70(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282A80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282A90(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282AB0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282AC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282AF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282B10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282B20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282B30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282B40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282B60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282B70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282B80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282BA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282BB0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282BC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282BD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282BE0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282BF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282C00(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282C10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282C40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282C50(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282C70(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282C80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282C90(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282CB0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282CC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282CF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282D10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282D20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282D30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282D40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282D60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282D70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282D80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282DA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282DB0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282DC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282DD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282DE0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282DF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282E00(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282E10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282E40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282E50(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282E70(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282E80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282E90(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282EB0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282EC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282EF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282F10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282F20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282F30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282F40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282F60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282F70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282F80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282FA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282FB0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282FC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282FD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282FE0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282FF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283000(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00283010(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283040(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283050(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283070(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00283080(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283090(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002830B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002830C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002830F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283110(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283120(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283130(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283140(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283160(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283170(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283180(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002831A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002831B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002831C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002831D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002831E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002831F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283200(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00283210(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283240(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283250(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283270(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00283280(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283290(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002832B0(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_00287600(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00288260(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00288450(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002892C0(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00289430(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00289440(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00289490(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002894A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002894B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002894C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002894E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002894F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00289500(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00289520(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00289530(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00289540(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00289550(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00289560(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00289570(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00289580(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00289590(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002895C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002895D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002895F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00289600(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00289610(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00289630(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_0028E090(void* object);

#ifdef __cplusplus
}
#endif

#endif
