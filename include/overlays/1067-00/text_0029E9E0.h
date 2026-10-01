#ifndef SO3_OVERLAYS_1067_00_TEXT_0029E9E0_H
#define SO3_OVERLAYS_1067_00_TEXT_0029E9E0_H

#include "overlays/1067-00/text_00293610.h"

typedef struct FieldLinkedObject157F00 FieldLinkedObject157F00;

/** Partial scalar state of the distinct D_157F00 class hierarchy. */
typedef struct FieldObject157F00
{
    u8 unk00[0x28];
    float unk28;
    s32 unk2C;
    float unk30;
    float unk34;
    float unk38;
    float unk3C;
    float unk40;
    float unk44;
    FieldLinkedObject157F00* unk48;
    u8 unk4C;
    u8 unk4D;
    u8 unk4E;
    u8 unk4F;
    FieldLinkedObject157F00* unk50;
    u8 unk54;
    u8 unk55;
    u8 unk56;
    u8 unk57;
} FieldObject157F00;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Store the floating-point value at offset 0x28.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029EF30(FieldObject157BC0* object, float value);

/**
 * @brief Store the floating-point value at offset 0x30.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029EF40(FieldObject157BC0* object, float value);

/**
 * @brief Read the floating-point value at offset 0x30.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_0029EF50(FieldObject157BC0* object);

/**
 * @brief Store the byte state at offset 0x4D.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029EF60(FieldObject157BC0* object, u8 value);

/**
 * @brief Read the byte state at offset 0x4D.
 * @param object Object to inspect.
 * @return Stored value.
 */
u8 func_0029EF70(FieldObject157BC0* object);

/**
 * @brief Store the floating-point value at offset 0x34.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029EF80(FieldObject157BC0* object, float value);

/**
 * @brief Store the byte state at offset 0x56.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029EF90(FieldObject157BC0* object, u8 value);

/**
 * @brief Read the byte state at offset 0x56.
 * @param object Object to inspect.
 * @return Stored value.
 */
u8 func_0029EFA0(FieldObject157BC0* object);

/**
 * @brief Store the floating-point value at offset 0x44.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029EFB0(FieldObject157BC0* object, float value);

/**
 * @brief Read the floating-point value at offset 0x44.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_0029EFC0(FieldObject157BC0* object);

/**
 * @brief Read the floating-point value at offset 0x28.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_0029EFD0(FieldObject157BC0* object);

/**
 * @brief Store the linked object at offset 0x48.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029EFE0(FieldObject157BC0* object, FieldLinkedObject157BC0* value);

/**
 * @brief Read the linked object at offset 0x48.
 * @param object Object to inspect.
 * @return Stored value.
 */
FieldLinkedObject157BC0* func_0029EFF0(FieldObject157BC0* object);

/**
 * @brief Store the byte state at offset 0x4F.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029F000(FieldObject157BC0* object, u8 value);

/**
 * @brief Store the byte state at offset 0x4E.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029F010(FieldObject157BC0* object, u8 value);

/**
 * @brief Store the linked object at offset 0x50.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029F020(FieldObject157BC0* object, FieldLinkedObject157BC0* value);

/**
 * @brief Read the linked object at offset 0x50.
 * @param object Object to inspect.
 * @return Stored value.
 */
FieldLinkedObject157BC0* func_0029F030(FieldObject157BC0* object);

/**
 * @brief Store the byte state at offset 0x55.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029F040(FieldObject157BC0* object, u8 value);

/**
 * @brief Store the floating-point value at offset 0x3C.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029F050(FieldObject157BC0* object, float value);

/**
 * @brief Store the byte state at offset 0x54.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029F060(FieldObject157BC0* object, u8 value);

/**
 * @brief Store the floating-point value at offset 0x40.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029F070(FieldObject157BC0* object, float value);

/**
 * @brief Store the floating-point value at offset 0x38.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029F0F0(FieldObject157BC0* object, float value);

/**
 * @brief Store the floating-point value at offset 0x28.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A21A0(FieldObject157F00* object, float value);

/**
 * @brief Store the floating-point value at offset 0x30.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A21B0(FieldObject157F00* object, float value);

/**
 * @brief Read the floating-point value at offset 0x30.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_002A21C0(FieldObject157F00* object);

/**
 * @brief Store the byte state at offset 0x4D.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A21D0(FieldObject157F00* object, u8 value);

/**
 * @brief Read the byte state at offset 0x4D.
 * @param object Object to inspect.
 * @return Stored value.
 */
u8 func_002A21E0(FieldObject157F00* object);

/**
 * @brief Store the floating-point value at offset 0x34.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A21F0(FieldObject157F00* object, float value);

/**
 * @brief Store the byte state at offset 0x56.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A2200(FieldObject157F00* object, u8 value);

/**
 * @brief Read the byte state at offset 0x56.
 * @param object Object to inspect.
 * @return Stored value.
 */
u8 func_002A2210(FieldObject157F00* object);

/**
 * @brief Store the floating-point value at offset 0x44.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A2220(FieldObject157F00* object, float value);

/**
 * @brief Read the floating-point value at offset 0x44.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_002A2230(FieldObject157F00* object);

/**
 * @brief Read the floating-point value at offset 0x28.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_002A2240(FieldObject157F00* object);

/**
 * @brief Store the linked object at offset 0x48.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A2250(FieldObject157F00* object, FieldLinkedObject157F00* value);

/**
 * @brief Read the linked object at offset 0x48.
 * @param object Object to inspect.
 * @return Stored value.
 */
FieldLinkedObject157F00* func_002A2260(FieldObject157F00* object);

/**
 * @brief Store the byte state at offset 0x4F.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A2270(FieldObject157F00* object, u8 value);

/**
 * @brief Store the byte state at offset 0x4E.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A2280(FieldObject157F00* object, u8 value);

/**
 * @brief Store the linked object at offset 0x50.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A2290(FieldObject157F00* object, FieldLinkedObject157F00* value);

/**
 * @brief Read the linked object at offset 0x50.
 * @param object Object to inspect.
 * @return Stored value.
 */
FieldLinkedObject157F00* func_002A22A0(FieldObject157F00* object);

/**
 * @brief Store the byte state at offset 0x55.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A22B0(FieldObject157F00* object, u8 value);

/**
 * @brief Store the floating-point value at offset 0x3C.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A22C0(FieldObject157F00* object, float value);

/**
 * @brief Store the byte state at offset 0x54.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A22D0(FieldObject157F00* object, u8 value);

/**
 * @brief Store the floating-point value at offset 0x40.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A22E0(FieldObject157F00* object, float value);

/**
 * @brief Enable the default callback predicate for this receiver.
 * @param object Receiver to query.
 * @return Always true.
 */
bool func_0029E9E0(FieldObject157BC0* object);

/**
 * @brief Enable the default callback predicate for this receiver.
 * @param object Receiver to query.
 * @return Always true.
 */
bool func_002A1C50(FieldObject157F00* object);

#ifdef __cplusplus
}
#endif
#endif
