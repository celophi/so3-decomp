#ifndef SO3_MAIN_DOUBLE_COMPARE_H
#define SO3_MAIN_DOUBLE_COMPARE_H

#include "types.h"
#include "ee.h"
#include "sdk/main/libkernl_00121940.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Return whether the resident double comparison reports left greater than right. */
s32 _dpfgt(double left, double right);

/** Return whether the resident double comparison reports left less than right. */
s32 _dpflt(double left, double right);

/** Return whether the resident double comparison reports the values equal. */
s32 _dpfeq(double left, double right);

#ifdef __cplusplus
}
#endif

#endif
