#include "include_asm.h"
#include "main/double_compare.h"

extern "C" {

s32 func_00135320(double left, double right);

s32 _dpfgt(double left, double right)
{
    return func_00135320(left, right) > 0;
}

s32 _dpflt(double left, double right)
{
    return func_00135320(left, right) < 0;
}

s32 _dpfeq(double left, double right)
{
    return func_00135320(left, right) == 0;
}
}
