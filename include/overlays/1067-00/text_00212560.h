#ifndef SO3_OVERLAYS_1067_00_TEXT_00212560_H
#define SO3_OVERLAYS_1067_00_TEXT_00212560_H

#include "types.h"

/** Opaque script receiver using the table at 0x151D40. */
typedef struct FieldScriptObject151D40 FieldScriptObject151D40;

/** A 16-byte script-resource record with a signed key and opaque payload. */
typedef struct FieldScriptRecord217590
{
    s32 unk00;
    u8 unk04[12];
} FieldScriptRecord217590;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set the low flag bit from the low bit of the command value.
 * @param object Script receiver to update.
 * @param value Command value supplying the flag bit.
 */
void func_002125C0(FieldScriptObject151D40* object, u32 value);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002127C0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002127D0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212A50(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212A60(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212A70(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212A80(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212A90(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212AA0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212AB0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212AC0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212AD0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212AE0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212AF0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212B00(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212B10(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212B20(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212B30(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212B40(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212B50(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212B60(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212B70(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212B80(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212B90(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212BA0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212BB0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212BC0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212BD0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212BE0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212BF0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212C00(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212C10(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212C20(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212C30(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212C40(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212C50(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212C60(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212C70(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212C80(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212C90(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212CA0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212CB0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212CC0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212CD0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212CE0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212CF0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212D00(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212D10(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212D20(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212D30(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212D40(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212D50(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212D60(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212D70(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212D80(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212D90(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212DA0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212DB0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212DC0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212DD0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212DE0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212DF0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212E00(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212E10(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212E20(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212E30(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212E40(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212E50(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212E60(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212E70(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212E80(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212E90(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212EA0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212EB0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212EC0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212ED0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212EE0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212EF0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212F00(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212F10(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212F20(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212F30(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212F40(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212F50(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212F60(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212F70(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212F80(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212F90(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212FA0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212FB0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212FC0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212FD0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212FE0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212FF0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213000(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213010(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213020(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213030(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213040(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213050(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213060(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213070(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213080(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213090(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002130A0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002130B0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002130C0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Copy the first command word to the global word.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002130D0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002130F0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213100(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213110(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213120(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213130(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213140(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213150(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213160(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213170(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213180(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213190(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002131A0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002131B0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002131C0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002131D0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002131E0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002131F0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213200(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213210(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213220(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213230(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213240(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213250(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213260(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213270(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213280(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213290(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002132A0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002132B0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002132C0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002132D0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002132E0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002132F0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213300(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213310(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213320(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213330(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213340(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213350(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213360(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213370(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213380(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213390(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002133A0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002133B0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002133C0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002133D0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002133E0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002133F0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213400(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213410(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213420(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213430(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213440(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213450(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213460(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213470(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213480(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213490(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002134A0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002134B0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002134C0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002134D0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002134E0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002134F0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213500(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213510(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213520(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213530(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213540(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213550(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213560(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213570(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213580(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213590(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002135A0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002135B0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002135C0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002135D0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002135E0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002135F0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213600(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213610(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213620(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213630(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213640(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213650(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213660(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213670(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213680(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213690(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002136A0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002136B0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002136C0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002136D0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Find a record in the script resource's sentinel-terminated table.
 * @param object Script receiver containing the resource header.
 * @param key Record key to find, or -1 to return the first record.
 * @return Matching record, or null when the table is absent or the key is missing.
 */
FieldScriptRecord217590* func_00217590(FieldScriptObject151D40* object, s32 key);

/**
 * @brief Read a script variable word or a packed runtime flag.
 * @param object Script receiver containing local variable words.
 * @param key Encoded storage selector and index, or 0xFFFF for the current word.
 * @return Stored word or normalized flag value; zero for an unknown selector.
 */
u32 func_00217920(FieldScriptObject151D40* object, s32 key);

#ifdef __cplusplus
}
#endif

#endif
