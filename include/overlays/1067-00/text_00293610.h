#ifndef SO3_OVERLAYS_1067_00_TEXT_00293610_H
#define SO3_OVERLAYS_1067_00_TEXT_00293610_H

#include "types.h"
#include "overlays/1067-00/text_001ED7E0.h"

/** Partial receiver with the countdown used by its update callback. */
typedef struct FieldClass157400
{
    u8 unk00[0x50];
    float delay;
} FieldClass157400;

typedef struct FieldClass1587E8 FieldClass1587E8;
typedef struct FieldResourceRecord273720 FieldResourceRecord273720;

/** Partial scalar state of the distinct D_158240 hierarchy. */
typedef struct FieldObject158240
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
    u8 unk48[4];
    u8 unk4C;
    u8 unk4D;
    u8 unk4E;
    u8 unk4F;
    u8 unk50[4];
    u8 unk54;
    u8 unk55;
    u8 unk56;
    u8 unk57;
    u8 unk58[0x48];
    u8* unkA0;
    FieldResourceRecord273720* unkA4;
} FieldObject158240;

/** Partial receiver for the distinct D_1584B0 hierarchy. */
typedef struct FieldObject1584B0
{
    u8 unk00[0xA0];
    u8* unkA0;
} FieldObject1584B0;

/** Partial scalar initializer receiver embedded at parent offset 0x50. */
typedef struct FieldScalarPair293610
{
    float unk00;
    s32 unk04;
} FieldScalarPair293610;

typedef struct FieldObject1583E0 FieldObject1583E0;
typedef struct FieldObject158650 FieldObject158650;

typedef struct FieldObject175360 FieldObject175360;
typedef struct FieldObject175370 FieldObject175370;

/** Partial receiver containing two callback object links. */
typedef struct FieldObject1577B0Links
{
    u8 unk00[0xB0];
    FieldObject175360* unkB0;
    FieldObject175370* unkB4;
} FieldObject1577B0Links;

/** Partial receiver containing parallel byte and four-float buffers. */
typedef struct FieldVectorBuffer293610
{
    u8 unk00[0xB0];
    u8* unkB0;
    FieldVector4* unkB4;
    FieldObject175360* unkB8;
    FieldObject175370* unkBC;
    s32 unkC0;
    s32 unkC4;
} FieldVectorBuffer293610;

typedef struct FieldObject158860Link48 FieldObject158860Link48;
typedef struct FieldObject158860Link50 FieldObject158860Link50;

/** Partial scalar state shared by the D_158860 and D_158930 class hierarchy. */
typedef struct FieldObject158860
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
    FieldObject158860Link48* unk48;
    u8 unk4C;
    u8 unk4D;
    u8 unk4E;
    u8 unk4F;
    FieldObject158860Link50* unk50;
    u8 unk54;
    u8 unk55;
    u8 unk56;
    u8 unk57;
    u8 unk58[8];
    FieldVector4 unk60;
    FieldVector4 unk70;
    FieldVector4 unk80;
    FieldVector4 unk90;
    u8* unkA0;
    FieldResourceRecord273720* unkA4;
} FieldObject158860;

typedef struct FieldLinkedObject157AF0 FieldLinkedObject157AF0;

/** Partial scalar and vector state of the D_157AF0 class hierarchy. */
typedef struct FieldObject157AF0
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
    FieldLinkedObject157AF0* unk48;
    u8 unk4C;
    u8 unk4D;
    u8 unk4E;
    u8 unk4F;
    FieldLinkedObject157AF0* unk50;
    u8 unk54;
    u8 unk55;
    u8 unk56;
    u8 unk57;
    u8 unk58[8];
    FieldVector4 unk60;
    FieldVector4 unk70;
    FieldVector4 unk80;
    FieldVector4 unk90;
    u8* unkA0;
    FieldResourceRecord273720* unkA4;
} FieldObject157AF0;

typedef struct FieldLinkedObject157BC0 FieldLinkedObject157BC0;

/** Partial scalar and vector state of the D_157BC0 class hierarchy. */
typedef struct FieldObject157BC0
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
    FieldLinkedObject157BC0* unk48;
    u8 unk4C;
    u8 unk4D;
    u8 unk4E;
    u8 unk4F;
    FieldLinkedObject157BC0* unk50;
    u8 unk54;
    u8 unk55;
    u8 unk56;
    u8 unk57;
    u8 unk58[8];
    FieldVector4 unk60;
    FieldVector4 unk70;
    FieldVector4 unk80;
    FieldVector4 unk90;
    u8* unkA0;
    FieldResourceRecord273720* unkA4;
} FieldObject157BC0;

/** Partial source containing four aligned values starting at offset 0x150. */
typedef struct FieldVectorSource150
{
    u8 unk00[0x150];
    FieldVector4 unk150;
    FieldVector4 unk160;
    FieldVector4 unk170;
    FieldVector4 unk180;
} FieldVectorSource150;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Report the fixed value 5 for this receiver class.
 * @param object Receiver to inspect.
 * @return Always 5.
 */
s32 func_00293740(FieldClass157400* object);

/**
 * @brief Advance a nonnegative countdown and update the receiver when it expires.
 * @param object Receiver whose countdown controls its update.
 */
void func_00293750(FieldClass157400* object);

/**
 * @brief Update the receiver with a temporary fixed time step when enabled.
 * @param object Receiver to update.
 * @param context Object passed to the underlying update.
 * @return The underlying update result.
 */
u8 func_002937F0(FieldClass1587E8* object, void* context);

/**
 * @brief Initialize the embedded scalar pair to 5.0 and -1.
 * @param object Scalar pair to initialize.
 * @return The initialized receiver.
 */
FieldScalarPair293610* func_00294FD0(FieldScalarPair293610* object);

/**
 * @brief Test whether the linked byte state differs from one.
 * @param object Object to inspect.
 * @return Whether the linked state is not one.
 */
bool func_00295A90(FieldObject158240* object);

/**
 * @brief Test whether the linked byte state differs from one.
 * @param object Object to inspect.
 * @return Whether the linked state is not one.
 */
bool func_00295C10(FieldObject1584B0* object);

/**
 * @brief Store the linked object at B8.
 * @param object Receiver to update.
 * @param value Linked object to store.
 */
void func_00295DB0(FieldVectorBuffer293610* object, FieldObject175360* value);

/**
 * @brief Read the linked object at B8.
 * @param object Receiver to inspect.
 * @return Stored linked object.
 */
FieldObject175360* func_00295DC0(FieldVectorBuffer293610* object);

/**
 * @brief Store the linked object at BC.
 * @param object Receiver to update.
 * @param value Linked object to store.
 */
void func_00295DD0(FieldVectorBuffer293610* object, FieldObject175370* value);

/**
 * @brief Read the linked object at BC.
 * @param object Receiver to inspect.
 * @return Stored linked object.
 */
FieldObject175370* func_00295DE0(FieldVectorBuffer293610* object);

/**
 * @brief Store the linked object at B0.
 * @param object Receiver to update.
 * @param value Linked object to store.
 */
void func_00295DF0(FieldObject1577B0Links* object, FieldObject175360* value);

/**
 * @brief Read the linked object at B0.
 * @param object Receiver to inspect.
 * @return Stored linked object.
 */
FieldObject175360* func_00295E00(FieldObject1577B0Links* object);

/**
 * @brief Store the linked object at B4.
 * @param object Receiver to update.
 * @param value Linked object to store.
 */
void func_00295E10(FieldObject1577B0Links* object, FieldObject175370* value);

/**
 * @brief Read the linked object at B4.
 * @param object Receiver to inspect.
 * @return Stored linked object.
 */
FieldObject175370* func_00295E20(FieldObject1577B0Links* object);

/**
 * @brief Report the default callback state.
 * @param object Callback receiver.
 * @return Always true.
 */
bool func_00295DA0(FieldVectorBuffer293610* object);

/**
 * @brief Report the default callback state.
 * @param object Callback receiver.
 * @return Always false.
 */
bool func_00295E30(FieldObject1583E0* object);

/**
 * @brief Report the default callback state.
 * @param object Callback receiver.
 * @return Always false.
 */
bool func_00295E40(FieldObject158650* object);

/**
 * @brief Append a byte and an optional four-float value while capacity remains.
 * @param object Receiver containing parallel buffers and their count.
 * @param value Byte stored at the current count.
 * @param vector Optional aligned value copied into the corresponding slot.
 */
void func_00295D30(FieldVectorBuffer293610* object, u8 value, const FieldVector4* vector);

/**
 * @brief Store the floating-point value at offset 0x28.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002989F0(FieldObject158860* object, float value);

/**
 * @brief Store the floating-point value at offset 0x30.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_00298A00(FieldObject158860* object, float value);

/**
 * @brief Read the floating-point value at offset 0x30.
 * @param object Object to inspect.
 * @return Stored floating-point value.
 */
float func_00298A10(FieldObject158860* object);

/**
 * @brief Store the byte state at offset 0x4D.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_00298A20(FieldObject158860* object, u8 value);

/**
 * @brief Read the byte state at offset 0x4D.
 * @param object Object to inspect.
 * @return Stored byte state.
 */
u8 func_00298A30(FieldObject158860* object);

/**
 * @brief Store the floating-point value at offset 0x34.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_00298A40(FieldObject158860* object, float value);

/**
 * @brief Store the byte state at offset 0x56.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_00298A50(FieldObject158860* object, u8 value);

/**
 * @brief Read the byte state at offset 0x56.
 * @param object Object to inspect.
 * @return Stored byte state.
 */
u8 func_00298A60(FieldObject158860* object);

/**
 * @brief Store the floating-point value at offset 0x44.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_00298A70(FieldObject158860* object, float value);

/**
 * @brief Read the floating-point value at offset 0x44.
 * @param object Object to inspect.
 * @return Stored floating-point value.
 */
float func_00298A80(FieldObject158860* object);

/**
 * @brief Read the floating-point value at offset 0x28.
 * @param object Object to inspect.
 * @return Stored floating-point value.
 */
float func_00298A90(FieldObject158860* object);

/**
 * @brief Store the byte state at offset 0x4F.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_00298AC0(FieldObject158860* object, u8 value);

/**
 * @brief Store the byte state at offset 0x4E.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_00298AD0(FieldObject158860* object, u8 value);

/**
 * @brief Store the byte state at offset 0x55.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_00298B00(FieldObject158860* object, u8 value);

/**
 * @brief Store the floating-point value at offset 0x3C.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_00298B10(FieldObject158860* object, float value);

/**
 * @brief Store the byte state at offset 0x54.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_00298B20(FieldObject158860* object, u8 value);

/**
 * @brief Store the floating-point value at offset 0x40.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_00298B30(FieldObject158860* object, float value);

/**
 * @brief Store the floating-point value at offset 0x38.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_00298BB0(FieldObject158860* object, float value);

/**
 * @brief Store the linked object at offset 0x48.
 * @param object Object to update.
 * @param value Linked object to store.
 */
void func_00298AA0(FieldObject158860* object, FieldObject158860Link48* value);

/**
 * @brief Read the linked object at offset 0x48.
 * @param object Object to inspect.
 * @return Stored linked object.
 */
FieldObject158860Link48* func_00298AB0(FieldObject158860* object);

/**
 * @brief Store the linked object at offset 0x50.
 * @param object Object to update.
 * @param value Linked object to store.
 */
void func_00298AE0(FieldObject158860* object, FieldObject158860Link50* value);

/**
 * @brief Read the linked object at offset 0x50.
 * @param object Object to inspect.
 * @return Stored linked object.
 */
FieldObject158860Link50* func_00298AF0(FieldObject158860* object);

/**
 * @brief Reset the word at offset 0x2C and copy four aligned values.
 * @param object Object receiving the values.
 * @param source Source containing the four values at offset 0x150.
 */
void func_00298BC0(FieldObject157AF0* object, const FieldVectorSource150* source);

/**
 * @brief Reset the word at offset 0x2C and copy four aligned values.
 * @param object Object receiving the values.
 * @param source Source containing the four values at offset 0x150.
 */
void func_0029BE30(FieldObject157BC0* object, const FieldVectorSource150* source);

/**
 * @brief Store the value in unk28.
 * @param object Receiver to update.
 * @param value Value to store.
 */
void func_0029BC20(FieldObject157AF0* object, float value);

/**
 * @brief Store the value in unk30.
 * @param object Receiver to update.
 * @param value Value to store.
 */
void func_0029BC30(FieldObject157AF0* object, float value);

/**
 * @brief Read the value in unk30.
 * @param object Receiver to inspect.
 * @return Stored value.
 */
float func_0029BC40(const FieldObject157AF0* object);

/**
 * @brief Store the value in unk4D.
 * @param object Receiver to update.
 * @param value Value to store.
 */
void func_0029BC50(FieldObject157AF0* object, u8 value);

/**
 * @brief Read the value in unk4D.
 * @param object Receiver to inspect.
 * @return Stored value.
 */
u8 func_0029BC60(const FieldObject157AF0* object);

/**
 * @brief Store the value in unk34.
 * @param object Receiver to update.
 * @param value Value to store.
 */
void func_0029BC70(FieldObject157AF0* object, float value);

/**
 * @brief Store the value in unk56.
 * @param object Receiver to update.
 * @param value Value to store.
 */
void func_0029BC80(FieldObject157AF0* object, u8 value);

/**
 * @brief Read the value in unk56.
 * @param object Receiver to inspect.
 * @return Stored value.
 */
u8 func_0029BC90(const FieldObject157AF0* object);

/**
 * @brief Store the value in unk44.
 * @param object Receiver to update.
 * @param value Value to store.
 */
void func_0029BCA0(FieldObject157AF0* object, float value);

/**
 * @brief Read the value in unk44.
 * @param object Receiver to inspect.
 * @return Stored value.
 */
float func_0029BCB0(const FieldObject157AF0* object);

/**
 * @brief Read the value in unk28.
 * @param object Receiver to inspect.
 * @return Stored value.
 */
float func_0029BCC0(const FieldObject157AF0* object);

/**
 * @brief Store the value in unk48.
 * @param object Receiver to update.
 * @param value Value to store.
 */
void func_0029BCD0(FieldObject157AF0* object, FieldLinkedObject157AF0* value);

/**
 * @brief Read the value in unk48.
 * @param object Receiver to inspect.
 * @return Stored value.
 */
FieldLinkedObject157AF0* func_0029BCE0(const FieldObject157AF0* object);

/**
 * @brief Store the value in unk4F.
 * @param object Receiver to update.
 * @param value Value to store.
 */
void func_0029BCF0(FieldObject157AF0* object, u8 value);

/**
 * @brief Store the value in unk4E.
 * @param object Receiver to update.
 * @param value Value to store.
 */
void func_0029BD00(FieldObject157AF0* object, u8 value);

/**
 * @brief Store the value in unk50.
 * @param object Receiver to update.
 * @param value Value to store.
 */
void func_0029BD10(FieldObject157AF0* object, FieldLinkedObject157AF0* value);

/**
 * @brief Read the value in unk50.
 * @param object Receiver to inspect.
 * @return Stored value.
 */
FieldLinkedObject157AF0* func_0029BD20(const FieldObject157AF0* object);

/**
 * @brief Store the value in unk55.
 * @param object Receiver to update.
 * @param value Value to store.
 */
void func_0029BD30(FieldObject157AF0* object, u8 value);

/**
 * @brief Store the value in unk3C.
 * @param object Receiver to update.
 * @param value Value to store.
 */
void func_0029BD40(FieldObject157AF0* object, float value);

/**
 * @brief Store the value in unk54.
 * @param object Receiver to update.
 * @param value Value to store.
 */
void func_0029BD50(FieldObject157AF0* object, u8 value);

/**
 * @brief Store the value in unk40.
 * @param object Receiver to update.
 * @param value Value to store.
 */
void func_0029BD60(FieldObject157AF0* object, float value);

/**
 * @brief Store the value in unk38.
 * @param object Receiver to update.
 * @param value Value to store.
 */
void func_0029BDE0(FieldObject157AF0* object, float value);

/**
 * @brief Report the default enabled callback state.
 * @param object Callback receiver.
 * @return Always true.
 */
bool func_0029B6D0(FieldObject157AF0* object);

/**
 * @brief Perform no work.
 * @param object Callback receiver.
 */
void func_00295D90(FieldVectorBuffer293610* object);

/**
 * @brief Bind the resource bytes and records and set the mode from byte zero.
 * @param object Callback receiver.
 * @param header Resource header bytes.
 * @param records Resource records to bind.
 */
void func_00298B40(FieldObject158860* object, u8* header, FieldResourceRecord273720* records);

/**
 * @brief Perform no work.
 * @param object Callback receiver.
 */
void func_00298BF0(FieldObject157AF0* object);

/**
 * @brief Bind the resource bytes and records and set the mode from byte zero.
 * @param object Callback receiver.
 * @param header Resource header bytes.
 * @param records Resource records to bind.
 */
void func_0029BD70(FieldObject157AF0* object, u8* header, FieldResourceRecord273720* records);

/**
 * @brief Ignore the supplied linked object.
 * @param object Callback receiver.
 * @param value Unused linked object.
 */
void func_0029BDF0(FieldObject157AF0* object, FieldObject175360* value);

/**
 * @brief Report that no linked object is available.
 * @param object Callback receiver.
 * @return Null.
 */
FieldObject175360* func_0029BE00(FieldObject157AF0* object);

/**
 * @brief Ignore the supplied linked object.
 * @param object Callback receiver.
 * @param value Unused linked object.
 */
void func_0029BE10(FieldObject157AF0* object, FieldObject175370* value);

/**
 * @brief Report that no linked object is available.
 * @param object Callback receiver.
 * @return Null.
 */
FieldObject175370* func_0029BE20(FieldObject157AF0* object);

/**
 * @brief Perform no work.
 * @param object Callback receiver.
 */
void func_0029BE60(void* object);

#ifdef __cplusplus
}
#endif

#endif
