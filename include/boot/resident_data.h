#ifndef SO3_BOOT_RESIDENT_DATA_H
#define SO3_BOOT_RESIDENT_DATA_H

#include "boot/resident_001001E0.h"
#include "boot/resident_00101550.h"
#include "boot/resident_0010A0E0.h"

/** Partial field context reached through D_001B6430. */
typedef struct ResidentContext
{
    u8 unk00[0x40];
    void* unk40;
    u8 unk44[0x28];
    void* unk6c;
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
extern ResidentObjectQueue* D_001B65F4;
extern ResidentContextRef* D_001B6430;

#ifdef __cplusplus
}
#endif

#endif
