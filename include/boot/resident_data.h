#ifndef SO3_BOOT_RESIDENT_DATA_H
#define SO3_BOOT_RESIDENT_DATA_H

#include "boot/resident_001001E0.h"
#include "boot/resident_00101550.h"
#include "boot/resident_0010A0E0.h"

/** Partial object at offset 0x8 of the field context. */
typedef struct ResidentContext08
{
    u8 unk00[0xDC];
    void* unkdc;
} ResidentContext08;

/** Partial field context reached through D_001B6430. */
typedef struct ResidentContext
{
    u8 unk00[8];
    ResidentContext08* unk08;
    u8 unk0c[0x34];
    void* unk40;
    u8 unk44[0x28];
    void* unk6c;
    u8 unk70[0x6D];
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
extern void* D_001B661C;

#ifdef __cplusplus
}
#endif

#endif
