#ifndef SO3_OVERLAYS_LIB_TEXT_0043BD00_H
#define SO3_OVERLAYS_LIB_TEXT_0043BD00_H

#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/text_0049B820.h"

#ifdef __cplusplus
/** Partial transform base with vtable D_173BB0 in main data; its subclasses fill in its two extra slots. */
class LibClass173BB0 : public LibTransform
{
public:
    virtual ~LibClass173BB0()
    {
    }

    virtual void func_slot84() = 0;

    virtual void func_slot88() = 0;

    float unk210;
    u8 unk214[0xC];
    u8 started;
    u8 unk221;
};

/** Partial transform with vtable D_173B10 in main data. */
class LibClass173B10 : public LibClass173BB0
{
public:
    virtual ~LibClass173B10();

    virtual void update();

    virtual void func_slot84();

    virtual void func_slot88();

    u8 unk230[0x20];
    FieldVec4B previous_position;
    FieldVec4B velocity;
};

/** Partial transform with vtable D_173C40 in main data. */
class LibClass173C40 : public LibClass173BB0
{
public:
    virtual ~LibClass173C40();

    virtual void update();

    virtual void func_slot84();

    virtual void func_slot88();

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

/** Partial grid with vtable D_173CD0 in main data. */
class LibClass173CD0 : public LibClass173DA0
{
public:
    virtual ~LibClass173CD0();
};
#endif

#endif
