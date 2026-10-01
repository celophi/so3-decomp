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

#ifdef __cplusplus
}
#endif

#endif
