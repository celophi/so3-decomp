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
} ResidentContext08;

/** Partial attached receiver reached through the field context at offset 0x44. */
typedef struct ResidentContextObject52
{
    u8 unk00[0x52];
    u8 unk52_0 : 1;
    u8 unk52_1_7 : 7;
} ResidentContextObject52;

/** Partial field context reached through D_001B6430. */
typedef struct ResidentContext
{
    u8 unk00[4];
    void* unk04;
    ResidentContext08* unk08;
    u8 unk0c[0x34];
    void* unk40;
    ResidentContextObject52* unk44;
    u8 unk48[0x10];
    void* unk58;
    u8 unk5c[0x10];
    void* unk6c;
    u8 unk70[0x38];
    u16 unka8;
    u16 unkaa;
    u8 unkac[4];
    u16 unkb0;
    u8 unkb2[0x1E];
    u32 unkd0;
    u32 unkd4;
    u8 unkd8[4];
    s8 unkdc;
    u8 unkdd_0 : 1;
    u8 unkdd_1 : 1;
    u8 unkdd_2 : 1;
    u8 unkdd_3 : 1;
    u8 unkdd_4 : 1;
    u8 unkdd_5 : 1;
    u8 unkdd_6 : 1;
    u8 unkdd_7 : 1;
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
extern void* D_001B65E4;
extern ResidentObjectQueue* D_001B65F4;
extern ResidentContextRef* D_001B6430;
extern FieldRuntime* D_001B657C;
extern u8 D_001B6448;
extern void* D_001B6458;
extern void* D_001B661C;

#ifdef __cplusplus
}
#endif

#endif
