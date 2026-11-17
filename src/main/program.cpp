#include "include_asm.h"
#include "main/program.h"

/** Vtable of the running program. */
extern const ResidentDispatchTable g_resident_program_vtable;

/** @brief Run the program; the base class does nothing. */
void ResidentProgram::run()
{
}

/**
 * @brief Construct the running program and register it as g_current_program.
 * @param object Program to construct.
 * @return The program.
 */
extern "C" ResidentRegisteredObject* resident_program_construct(ResidentRegisteredObject* object)
{
    object->dispatch = &g_resident_program_vtable;
    g_current_program = reinterpret_cast<ResidentProgram*>(object);
    return object;
}
