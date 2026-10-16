#ifndef SO3_OVERLAYS_1067_00_TEXT_00257750_H
#define SO3_OVERLAYS_1067_00_TEXT_00257750_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Process a value on the field context with two option words.
 * @param context Field context receiver.
 * @param value Value to process.
 * @param option_a First option word.
 * @param option_b Second option word.
 * @return The created object.
 */
void* func_00258C90(void* context, u32 value, u32 option_a, u32 option_b);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include "overlays/1067-00/text_001DD3C0.h"

/** Query the resource loader using a position and optional transform receiver. */
class FieldClass153AA8
{
public:
    virtual float func_00259270(const FieldVec4B* position, LibClass172000* object) = 0;
};

/** Field resource loader with a position query and context callback. */
class FieldClass153CD0 : public FieldClass150070, public FieldClass153AA8, public FieldClass1DD400
{
public:
    FieldClass153CD0();

    virtual ~FieldClass153CD0();

    virtual s32 func_001DF3D0();

    virtual void func_001DD7B0();

    virtual void func_001DF360();

    virtual void func_001DDB30(void* request);

    virtual s32 func_00259700(void* resource, u32 unused, u8 flag, void* argument);

    virtual float func_00259270(const FieldVec4B* position, LibClass172000* object);

    u8 unk1c[0xE4];
};
#endif

#endif
