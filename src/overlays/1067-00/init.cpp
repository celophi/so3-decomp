#include "overlays/1067-00/init.h"
#include "main/resident_data.h"

void func_0032A880(void)
{
}

void func_0032A890(void)
{
    resident_program_construct(&D_32B6B0.registered);
    D_32B6B0.registered.dispatch = &g_field_program_vtable;
}
