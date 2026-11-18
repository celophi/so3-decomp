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
};

/** Partial transform with vtable D_173B10 in main data. */
class LibClass173B10 : public LibClass173BB0
{
public:
    /** @brief Destroy the transform. */
    virtual ~LibClass173B10();

    virtual void update();

    virtual void func_slot84();

    virtual void func_slot88();
};

/** Partial transform with vtable D_173C40 in main data. */
class LibClass173C40 : public LibClass173BB0
{
public:
    /** @brief Destroy the transform. */
    virtual ~LibClass173C40();

    virtual void update();

    virtual void func_slot84();

    virtual void func_slot88();
};

/** Partial grid with vtable D_173CD0 in main data. */
class LibClass173CD0 : public LibClass173DA0
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass173CD0();
};
#endif

#endif
