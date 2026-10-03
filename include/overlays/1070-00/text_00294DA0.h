#ifndef SO3_OVERLAYS_1070_00_TEXT_00294DA0_H
#define SO3_OVERLAYS_1070_00_TEXT_00294DA0_H

#include "types.h"

/** Partial receiver with six float values and two control flags. */
typedef struct FieldFloatRangeState20
{
    u8 unk00[0x20];
    float unk20;
    float unk24;
    float unk28;
    float unk2c;
    float unk30;
    float unk34;
    u8 unk38_0 : 1;
    u8 unk38_1 : 1;
    u8 unk38_2_7 : 6;
} FieldFloatRangeState20;

/** Partial embedded receiver containing two words with unknown meanings. */
typedef struct FieldInitialWordPair
{
    u32 unk00;
    s32 unk04;
} FieldInitialWordPair;

/** Partial receiver for the 0029B860 field-access family. */
typedef struct FieldState29B860
{
    u8 unk00[0x28];
    float unk28;
    u32 unk2c;
    float unk30;
    float unk34;
    float unk38;
    float unk3c;
    float unk40;
    float unk44;
    u32 unk48;
    u8 unk4c;
    u8 unk4d;
    u8 unk4e;
    u8 unk4f;
    u32 unk50;
    u8 unk54;
    u8 unk55;
    u8 unk56;
    u8 unk57;
    u8 unk58[8];
    unsigned __int128 unk60;
    unsigned __int128 unk70;
    unsigned __int128 unk80;
    unsigned __int128 unk90;
    const u8* unka0;
    u32 unka4;
} FieldState29B860;

/** Partial receiver for the 0029EA90 field-access family. */
typedef struct FieldState29EA90
{
    u8 unk00[0x28];
    float unk28;
    u32 unk2c;
    float unk30;
    float unk34;
    float unk38;
    float unk3c;
    float unk40;
    float unk44;
    u32 unk48;
    u8 unk4c;
    u8 unk4d;
    u8 unk4e;
    u8 unk4f;
    u32 unk50;
    u8 unk54;
    u8 unk55;
    u8 unk56;
    u8 unk57;
    u8 unk58[8];
    unsigned __int128 unk60;
    unsigned __int128 unk70;
    unsigned __int128 unk80;
    unsigned __int128 unk90;
    const u8* unka0;
    u32 unka4;
} FieldState29EA90;

/** Partial receiver for the 002A1DA0 field-access family. */
typedef struct FieldState2A1DA0
{
    u8 unk00[0x28];
    float unk28;
    u32 unk2c;
    float unk30;
    float unk34;
    float unk38;
    float unk3c;
    float unk40;
    float unk44;
    u32 unk48;
    u8 unk4c;
    u8 unk4d;
    u8 unk4e;
    u8 unk4f;
    u32 unk50;
    u8 unk54;
    u8 unk55;
    u8 unk56;
    u8 unk57;
    u8 unk58[8];
    unsigned __int128 unk60;
    unsigned __int128 unk70;
    unsigned __int128 unk80;
    unsigned __int128 unk90;
    const u8* unka0;
    u32 unka4;
} FieldState2A1DA0;

/** Partial source containing four aligned quadword values. */
typedef struct FieldCopySource29BA30
{
    u8 unk00[0x150];
    unsigned __int128 unk150;
    unsigned __int128 unk160;
    unsigned __int128 unk170;
    unsigned __int128 unk180;
} FieldCopySource29BA30;

/** Partial source containing four aligned quadword values. */
typedef struct FieldCopySource29ECA0
{
    u8 unk00[0x150];
    unsigned __int128 unk150;
    unsigned __int128 unk160;
    unsigned __int128 unk170;
    unsigned __int128 unk180;
} FieldCopySource29ECA0;

/** Partial source containing four aligned quadword values. */
typedef struct FieldCopySource2A1FB0
{
    u8 unk00[0x150];
    unsigned __int128 unk150;
    unsigned __int128 unk160;
    unsigned __int128 unk170;
    unsigned __int128 unk180;
} FieldCopySource2A1FB0;

/** Partial receiver whose word at offset 0xA0 points to a byte flag. */
typedef struct FieldBytePointerA0
{
    u8 unk00[0xA0];
    u8* unka0;
} FieldBytePointerA0;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set the float range and reset its progress and control flags.
 * @param object Receiver to initialize.
 * @param first Initial float value.
 * @param second Final float value.
 * @param third Float limit for progress.
 */
void func_00296310(FieldFloatRangeState20* object, float first, float second, float third);

/**
 * @brief Initialize the two observed words of an embedded receiver.
 * @param object Embedded receiver to initialize.
 * @return The supplied receiver.
 */
FieldInitialWordPair* func_00297E10(FieldInitialWordPair* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00295BC0(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00296300(void* object);

/**
 * @brief Return the fixed value 5.
 * @param object Receiver or first argument; unused.
 * @return Always 5.
 */
s32 func_00296570(void* object);

/**
 * @brief Test whether the byte pointed to by offset 0xA0 differs from 1.
 * @param object Receiver holding the byte pointer.
 * @return 1 if the byte isn't 1, otherwise 0.
 */
s32 func_002988D0(FieldBytePointerA0* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00298C00(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00298C10(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00298CA0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00298CB0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0029BA60(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_0029E540(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0029EC60(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0029EC70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0029EC80(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0029EC90(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0029ECD0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002A1850(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A1F70(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A1F80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A1F90(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A1FA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A1FE0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002A4AC0(void* object);

/**
 * @brief Set the unk28 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B860(FieldState29B860* object, float value);

/**
 * @brief Set the unk30 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B870(FieldState29B860* object, float value);

/**
 * @brief Read the unk30 float value.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
float func_0029B880(FieldState29B860* object);

/**
 * @brief Set the unk4d stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B890(FieldState29B860* object, u8 value);

/**
 * @brief Read the unk4d stored byte.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
u8 func_0029B8A0(FieldState29B860* object);

/**
 * @brief Set the unk34 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B8B0(FieldState29B860* object, float value);

/**
 * @brief Set the unk56 stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B8C0(FieldState29B860* object, u8 value);

/**
 * @brief Read the unk56 stored byte.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
u8 func_0029B8D0(FieldState29B860* object);

/**
 * @brief Set the unk44 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B8E0(FieldState29B860* object, float value);

/**
 * @brief Read the unk44 float value.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
float func_0029B8F0(FieldState29B860* object);

/**
 * @brief Read the unk28 float value.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
float func_0029B900(FieldState29B860* object);

/**
 * @brief Set the unk48 stored word.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B910(FieldState29B860* object, u32 value);

/**
 * @brief Read the unk48 stored word.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
u32 func_0029B920(FieldState29B860* object);

/**
 * @brief Set the unk4f stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B930(FieldState29B860* object, u8 value);

/**
 * @brief Set the unk4e stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B940(FieldState29B860* object, u8 value);

/**
 * @brief Set the unk50 stored word.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B950(FieldState29B860* object, u32 value);

/**
 * @brief Read the unk50 stored word.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
u32 func_0029B960(FieldState29B860* object);

/**
 * @brief Set the unk55 stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B970(FieldState29B860* object, u8 value);

/**
 * @brief Set the unk3c float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B980(FieldState29B860* object, float value);

/**
 * @brief Set the unk54 stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B990(FieldState29B860* object, u8 value);

/**
 * @brief Set the unk40 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B9A0(FieldState29B860* object, float value);

/**
 * @brief Set the unk38 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029BA20(FieldState29B860* object, float value);

/**
 * @brief Set the unk28 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EA90(FieldState29EA90* object, float value);

/**
 * @brief Set the unk30 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EAA0(FieldState29EA90* object, float value);

/**
 * @brief Read the unk30 float value.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
float func_0029EAB0(FieldState29EA90* object);

/**
 * @brief Set the unk4d stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EAC0(FieldState29EA90* object, u8 value);

/**
 * @brief Read the unk4d stored byte.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
u8 func_0029EAD0(FieldState29EA90* object);

/**
 * @brief Set the unk34 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EAE0(FieldState29EA90* object, float value);

/**
 * @brief Set the unk56 stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EAF0(FieldState29EA90* object, u8 value);

/**
 * @brief Read the unk56 stored byte.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
u8 func_0029EB00(FieldState29EA90* object);

/**
 * @brief Set the unk44 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EB10(FieldState29EA90* object, float value);

/**
 * @brief Read the unk44 float value.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
float func_0029EB20(FieldState29EA90* object);

/**
 * @brief Read the unk28 float value.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
float func_0029EB30(FieldState29EA90* object);

/**
 * @brief Set the unk48 stored word.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EB40(FieldState29EA90* object, u32 value);

/**
 * @brief Read the unk48 stored word.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
u32 func_0029EB50(FieldState29EA90* object);

/**
 * @brief Set the unk4f stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EB60(FieldState29EA90* object, u8 value);

/**
 * @brief Set the unk4e stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EB70(FieldState29EA90* object, u8 value);

/**
 * @brief Set the unk50 stored word.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EB80(FieldState29EA90* object, u32 value);

/**
 * @brief Read the unk50 stored word.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
u32 func_0029EB90(FieldState29EA90* object);

/**
 * @brief Set the unk55 stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EBA0(FieldState29EA90* object, u8 value);

/**
 * @brief Set the unk3c float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EBB0(FieldState29EA90* object, float value);

/**
 * @brief Set the unk54 stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EBC0(FieldState29EA90* object, u8 value);

/**
 * @brief Set the unk40 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EBD0(FieldState29EA90* object, float value);

/**
 * @brief Set the unk38 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EC50(FieldState29EA90* object, float value);

/**
 * @brief Set the unk28 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1DA0(FieldState2A1DA0* object, float value);

/**
 * @brief Set the unk30 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1DB0(FieldState2A1DA0* object, float value);

/**
 * @brief Read the unk30 float value.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
float func_002A1DC0(FieldState2A1DA0* object);

/**
 * @brief Set the unk4d stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1DD0(FieldState2A1DA0* object, u8 value);

/**
 * @brief Read the unk4d stored byte.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
u8 func_002A1DE0(FieldState2A1DA0* object);

/**
 * @brief Set the unk34 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1DF0(FieldState2A1DA0* object, float value);

/**
 * @brief Set the unk56 stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1E00(FieldState2A1DA0* object, u8 value);

/**
 * @brief Read the unk56 stored byte.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
u8 func_002A1E10(FieldState2A1DA0* object);

/**
 * @brief Set the unk44 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1E20(FieldState2A1DA0* object, float value);

/**
 * @brief Read the unk44 float value.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
float func_002A1E30(FieldState2A1DA0* object);

/**
 * @brief Read the unk28 float value.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
float func_002A1E40(FieldState2A1DA0* object);

/**
 * @brief Set the unk48 stored word.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1E50(FieldState2A1DA0* object, u32 value);

/**
 * @brief Read the unk48 stored word.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
u32 func_002A1E60(FieldState2A1DA0* object);

/**
 * @brief Set the unk4f stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1E70(FieldState2A1DA0* object, u8 value);

/**
 * @brief Set the unk4e stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1E80(FieldState2A1DA0* object, u8 value);

/**
 * @brief Set the unk50 stored word.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1E90(FieldState2A1DA0* object, u32 value);

/**
 * @brief Read the unk50 stored word.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
u32 func_002A1EA0(FieldState2A1DA0* object);

/**
 * @brief Set the unk55 stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1EB0(FieldState2A1DA0* object, u8 value);

/**
 * @brief Set the unk3c float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1EC0(FieldState2A1DA0* object, float value);

/**
 * @brief Set the unk54 stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1ED0(FieldState2A1DA0* object, u8 value);

/**
 * @brief Set the unk40 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1EE0(FieldState2A1DA0* object, float value);

/**
 * @brief Set the unk38 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1F60(FieldState2A1DA0* object, float value);

/**
 * @brief Clear the stored data and set the control byte.
 * @param object Receiver to update.
 * @param value Nonzero to set the control byte.
 */
void func_0029B9F0(FieldState29B860* object, s32 value);

/**
 * @brief Store the data reference and derive its control byte.
 * @param object Receiver to update.
 * @param data Data whose first byte selects the control value.
 * @param value Word associated with the data reference.
 */
void func_0029B9B0(FieldState29B860* object, const u8* data, u32 value);

/**
 * @brief Clear the stored data and set the control byte.
 * @param object Receiver to update.
 * @param value Nonzero to set the control byte.
 */
void func_0029EC20(FieldState29EA90* object, s32 value);

/**
 * @brief Store the data reference and derive its control byte.
 * @param object Receiver to update.
 * @param data Data whose first byte selects the control value.
 * @param value Word associated with the data reference.
 */
void func_0029EBE0(FieldState29EA90* object, const u8* data, u32 value);

/**
 * @brief Clear the stored data and set the control byte.
 * @param object Receiver to update.
 * @param value Nonzero to set the control byte.
 */
void func_002A1F30(FieldState2A1DA0* object, s32 value);

/**
 * @brief Store the data reference and derive its control byte.
 * @param object Receiver to update.
 * @param data Data whose first byte selects the control value.
 * @param value Word associated with the data reference.
 */
void func_002A1EF0(FieldState2A1DA0* object, const u8* data, u32 value);

/**
 * @brief Clear the stored word and copy four aligned quadwords.
 * @param object Receiver to update.
 * @param source Source of the quadword values.
 */
void func_0029BA30(FieldState29B860* object, const FieldCopySource29BA30* source);

/**
 * @brief Clear the stored word and copy four aligned quadwords.
 * @param object Receiver to update.
 * @param source Source of the quadword values.
 */
void func_0029ECA0(FieldState29EA90* object, const FieldCopySource29ECA0* source);

/**
 * @brief Clear the stored word and copy four aligned quadwords.
 * @param object Receiver to update.
 * @param source Source of the quadword values.
 */
void func_002A1FB0(FieldState2A1DA0* object, const FieldCopySource2A1FB0* source);

#ifdef __cplusplus
}
#endif

#endif
