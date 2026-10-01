#ifndef SO3_OVERLAYS_1067_00_TEXT_0027E520_H
#define SO3_OVERLAYS_1067_00_TEXT_0027E520_H

#include "types.h"

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

#ifdef __cplusplus
}
#endif

#endif
