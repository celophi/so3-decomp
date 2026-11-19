#ifndef SO3_OVERLAYS_LIB_TEXT_0043BD00_H
#define SO3_OVERLAYS_LIB_TEXT_0043BD00_H

#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/text_0049B820.h"
#include "vu0.h"

#ifdef __cplusplus
/** Saves every VU0 register while it lives and loads them back when it goes, with vtable D_173BA0 in main data. */
class LibVu0StateGuard
{
public:
    unsigned __int128 registers[31];

    /** @brief Save vf1-vf31. */
    LibVu0StateGuard()
    {
        vu0_save_registers(registers);
    }

    /** @brief Load vf1-vf31 back. */
    virtual ~LibVu0StateGuard();
};

/** Partial transform base with vtable D_173BB0 in main data; its subclasses fill in its two extra slots. */
class LibClass173BB0 : public LibTransform
{
public:
    virtual ~LibClass173BB0()
    {
    }

    virtual void func_slot84(const LibMatrix44Value* matrix, const LibMatrix44Value* second, const LibMatrix44Value* third) = 0;

    /**
     * @brief Test a moving point against the collider and push it out on a hit.
     * @param previous Position before the step.
     * @param position Position after the step.
     * @param velocity Velocity over the step.
     * @param out_velocity Receives the velocity after the bounce.
     * @param out_position Receives the corrected position.
     * @return Whether the point hit the collider.
     */
    virtual bool collide(const LibVector4* previous, const LibVector4* position, const LibVector4* velocity, LibVector4* out_velocity, LibVector4* out_position) = 0;

    float unk210;
    float unk214;
    u8 unk218[8];
    u8 started;
    u8 unk221;
    u8 unk222[2];
    float radius;
    float radius_squared;
};

/** Partial transform with vtable D_173B10 in main data. */
class LibClass173B10 : public LibClass173BB0
{
public:
    virtual ~LibClass173B10();

    virtual void update();

    virtual void func_slot84(const LibMatrix44Value* matrix, const LibMatrix44Value* second, const LibMatrix44Value* third);

    virtual bool collide(const LibVector4* previous, const LibVector4* position, const LibVector4* velocity, LibVector4* out_velocity, LibVector4* out_position);

    float unk230;
    float unk234;
    float unk238;
    u8 unk23c[4];
    LibVector4 centre;
    FieldVec4B previous_position;
    FieldVec4B velocity;
};

/** Partial transform with vtable D_173C40 in main data. */
class LibClass173C40 : public LibClass173BB0
{
public:
    virtual ~LibClass173C40();

    virtual void update();

    virtual void func_slot84(const LibMatrix44Value* matrix, const LibMatrix44Value* second, const LibMatrix44Value* third);

    virtual bool collide(const LibVector4* previous, const LibVector4* position, const LibVector4* velocity, LibVector4* out_velocity, LibVector4* out_position);

    u8 unk230[0x30];
    FieldVec4B unk260;
    FieldVec4B unk270;
    FieldVec4B unk280;
    FieldVec4B unk290;
    FieldVec4B previous_position;
    FieldVec4B velocity;
    u8 unk2c0[0x40];
    LibMatrix44Value previous_transform;
};

/** Colliders a particle grid tests its moving particles against. */
struct LibColliderList
{
    u8 unk00[2];
    s16 count;
    LibClass173BB0** colliders;
    u8 unk08[4];
    u8 hit;
};

/** Partial grid with vtable D_173CD0 in main data. */
class LibClass173CD0 : public LibClass173DA0
{
public:
    virtual ~LibClass173CD0();
};
#endif

#endif
