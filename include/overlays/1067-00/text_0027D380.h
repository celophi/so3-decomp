#ifndef SO3_OVERLAYS_1067_00_TEXT_0027D380_H
#define SO3_OVERLAYS_1067_00_TEXT_0027D380_H

#include "types.h"
#include "overlays/1067-00/field_class_155780.h"
#include "overlays/1067-00/field_class_154EF0.h"

#ifdef __cplusplus
/** Partial Field object with vtable D_155810 in main data. */
class FieldClass155810 : public FieldClass152740
{
public:
    /** @brief Destroy the object through its base chain. */
    virtual ~FieldClass155810();
    /** @brief Release one use of the keyed context object, then delete this object. */
    virtual void func_001DD7B0();
    /** @brief Run the base handler, detach the object and delete it. */
    virtual void func_slot20();
    u32 unk270;
};

/** Partial Field object with vtable D_155B40 in main data. */
class FieldClass155B40 : public FieldClass154EF0
{
public:
    /** @brief Destroy the object through its base. */
    virtual ~FieldClass155B40();
    /** @brief Create the grid for this object. */
    virtual void func_slot30();
    /** @brief Update the base, then place the target at this object's position. */
    virtual void func_001DF360();
};
#endif

#endif
