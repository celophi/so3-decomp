#ifndef SO3_BOOT_RESIDENT_DATA_H
#define SO3_BOOT_RESIDENT_DATA_H

#include "boot/resident_001001E0.h"
#include "boot/resident_00101550.h"
#include "boot/resident_0010A0E0.h"

typedef struct FieldRuntime FieldRuntime;

/** Partial object at offset 0x8 of the field context. */
typedef struct ResidentContext08
{
    u8 unk00[0xDC];
    void* unkdc;
    u8 unke0[0x15];
    u8 unkf5_0_2 : 3;
    u8 unkf5_3 : 1;
    u8 unkf5_4 : 1;
    u8 unkf5_5 : 1;
    u8 unkf5_6_7 : 2;
} ResidentContext08;

/** Partial attached receiver reached through the field context at offset 0x44. */
typedef struct ResidentContextObject52
{
    u8 unk00[0x52];
    u8 unk52_0 : 1;
    u8 unk52_1_7 : 7;
} ResidentContextObject52;

/** Partial resident object reached through D_001B65E4. */
typedef struct ResidentObject1B65E4
{
    u8 unk00[0x12183];
    u8 unk12183;
} ResidentObject1B65E4;

/** Partial object at offset 0x38 of the field context. */
typedef struct ResidentContextObject38
{
    u8 unk00[0x4C8];
    u8 unk4c8_0 : 1;
    u8 unk4c8_1_7 : 7;
} ResidentContextObject38;

/** Flag byte at field context offset 0xDD (a separate member: functions testing two of its bits keep its address). */
typedef struct ResidentContextFlagsDD
{
    u8 unk0 : 1;
    u8 unk1 : 1;
    u8 unk2 : 1;
    u8 unk3 : 1;
    u8 unk4 : 1;
    u8 unk5 : 1;
    u8 unk6 : 1;
    u8 unk7 : 1;
} ResidentContextFlagsDD;

/** Partial object at field context offset 0x58. */
typedef struct ResidentContextObject58
{
    u8 unk00[0x1E0];
    float unk1e0;
} ResidentContextObject58;

/** Partial field context reached through D_001B6430. */
typedef struct ResidentContext
{
    u8 unk00[4];
    void* unk04;
    ResidentContext08* unk08;
    u8 unk0c[8];
    void* unk14;
    void* unk18;
    void* unk1c;
    u8 unk20[4];
    void* unk24;
    u8 unk28[8];
    void* unk30;
    u8 unk34[4];
    ResidentContextObject38* unk38;
    u8 unk3c[4];
    void* unk40;
    ResidentContextObject52* unk44;
    u8 unk48[0x10];
    ResidentContextObject58* unk58;
    u8 unk5c[0x10];
    void* unk6c;
    u8 unk70[0x38];
    u16 unka8;
    s16 unkaa;
    u8 unkac[4];
    u16 unkb0;
    u8 unkb2[0x1E];
    u32 unkd0;
    u32 unkd4;
    u8 unkd8[4];
    s8 unkdc;
    ResidentContextFlagsDD unkdd;
    u8 unkde_0 : 1;
    u8 unkde_1 : 1;
    u8 unkde_2 : 1;
    u8 unkde_3 : 1;
    u8 unkde_4 : 1;
    u8 unkde_5 : 1;
    u8 unkde_6_7 : 2;
} ResidentContext;

/** Partial holder of the current field context. */
typedef struct ResidentContextRef
{
    ResidentContext* context;
} ResidentContextRef;

#ifdef __cplusplus
extern "C" {
#endif

extern const ResidentDispatchTable D_159070;
extern ResidentObject1B65E4* D_001B65E4;
extern ResidentObject1B65E8* D_001B65E8;
extern ResidentObjectQueue* D_001B65F4;
extern ResidentContextRef* D_001B6430;
extern FieldRuntime* D_001B657C;
extern u8 D_001B6448;
extern void* D_001B6458;
extern void* D_001B661C;

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * @brief Report whether record processing must wait for the resident objects.
 *
 * Shared by FieldClass14FFB0::func_001E0F60 and its FieldClass155640 override.
 * @return True when the byte at offset 0x12183 of D_001B65E4 is set,
 *         func_00102AA0(D_001B65E8) reports work, or the byte at offset 0x30
 *         of D_001B65E8 is set.
 */
static inline bool field_records_blocked()
{
    if (D_001B65E4->unk12183 || func_00102AA0(D_001B65E8) || D_001B65E8->unk30)
    {
        return true;
    }
    return false;
}
#endif

#endif
