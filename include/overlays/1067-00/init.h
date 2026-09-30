#ifndef SO3_OVERLAYS_1067_00_INIT_H
#define SO3_OVERLAYS_1067_00_INIT_H

#include "boot/resident_00101550.h"
#include "types.h"

/** Partial module object containing its dispatch prefix and state flags. */
typedef struct FieldModuleObject
{
    ResidentRegisteredObject registered;
    u8 unk04[0xD9];
    u8 unkdd;
    u8 unkde;
    u8 unkdf;
} FieldModuleObject;

#ifdef __cplusplus
extern "C" {
#endif

extern FieldModuleObject D_32B6B0;

/** @brief Run the empty module initialization callback. */
void func_0032A880(void);

/** @brief Register the module object and install its dispatch table. */
void func_0032A890(void);

#ifdef __cplusplus
}
#endif

#endif
