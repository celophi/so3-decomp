#ifndef SO3_SDK_MAIN_LIBCDVD_00130000_H
#define SO3_SDK_MAIN_LIBCDVD_00130000_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Initialize the CD/DVD library. @param mode 0 for a normal initialization. @return Nonzero on success. */
s32 sceCdInit(s32 mode);

/** @brief Set the disc media type. @param media 1 for CD, 2 for DVD. @return Nonzero on success. */
s32 sceCdMmode(s32 media);

#ifdef __cplusplus
}
#endif

#endif
