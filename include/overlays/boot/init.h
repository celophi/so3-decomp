#ifndef SO3_OVERLAYS_BOOT_INIT_H
#define SO3_OVERLAYS_BOOT_INIT_H

#include "overlays/boot/text_001E0900.h"

extern "C" {
/** The boot program; boot's static initializer constructs it. */
extern BootProgram g_boot_program;
}

#endif
