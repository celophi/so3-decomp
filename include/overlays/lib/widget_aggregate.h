#ifndef SO3_OVERLAYS_LIB_WIDGET_AGGREGATE_H
#define SO3_OVERLAYS_LIB_WIDGET_AGGREGATE_H

#include "types.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_0044ABE0.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/lib/text_00419A70.h"

/** Panel with vtable D_1722E0 in main data; the frame of a widget aggregate. */
class LibClass1722E0 : public LibPanel
{
public:
    /** @brief Initialize the panel. */
    LibClass1722E0();

    virtual ~LibClass1722E0();
};

/** Widget aggregate with grid settings and selection callbacks, with vtable D_1723F0 in main data after its data. */
class LibClass1723F0
{
public:
    LibClass1722E0 unk00;
    ItemCreationClass1746A0 unk90;
    ItemCreationClass1746A0 unke4;
    LibListIndicator unk138;
    ItemCreationClass175030 unk190;
    ItemCreationClass172600 unk20c;
    ItemCreationClass172870 unk260;
    u8 unk2b8[8];
    float unk2c0;
    float unk2c4;
    float unk2c8;
    float unk2cc;
    float unk2d0;
    u8 unk2d4[0x24];
    s32 unk2f8;
    float unk2fc;
    s32 unk300;
    s32 unk304;
    s32 unk308;
    s32 unk30c;
    s8 unk310;
    s8 unk311;
    s8 unk312;
    s8 unk313;
    s8 unk314;
    s8 unk315;
    s8 unk316;
    u8 unk317;
    u8 unk318;
    u8 unk319[3];

    /**
     * @brief Update the aggregate index; the base does nothing.
     * @param index Requested index.
     */
    virtual void func_00412C10(s32 index);

    /**
     * @brief Update the aggregate float setting; the base does nothing.
     * @param value Requested setting.
     */
    virtual void func_00412C20(float value);

    /**
     * @brief Read the aggregate float setting.
     * @return Zero in the base.
     */
    virtual float func_00412C30();

    /** @brief Refresh the aggregate. */
    virtual void func_00413020();
};

/** Widget container with a selection aggregate, with vtable D_172320 in main data. */
class LibClass172320 : public LibContainer, public LibClass1723F0
{
public:
    LibClass172320();

    virtual ~LibClass172320();
};

/** Container owning up to 32 interface rows, with MAIN vtable at 0x1721F0. */
class LibClass1721F0 : public LibClass172320
{
public:
    /** @brief Initialize the container and set its transform type. */
    LibClass1721F0();

    virtual ~LibClass1721F0();

    /**
     * @brief Run the container state hook.
     * @param first First update flag.
     * @param second Second update flag.
     * @param third Third update flag.
     */
    virtual void func_00412C40(u32 first, u32 second, u32 third);

    /**
     * @brief Create the row for an index.
     * @param index Row index.
     * @return The new row.
     */
    virtual void* create_row(s32 index) = 0;

    /**
     * @brief Called when the selected index changes.
     * @param index Selected index.
     */
    virtual void notify_index(s32 index);

    /** @brief Called when the selection is cancelled. */
    virtual void notify_cancel();

    /**
     * @brief Update the aggregate index.
     * @param index Requested index.
     */
    virtual void func_00412C10(s32 index);

    /**
     * @brief Update the aggregate float setting.
     * @param value Requested setting.
     */
    virtual void func_00412C20(float value);

    /**
     * @brief Read the aggregate float setting.
     * @return Current setting.
     */
    virtual float func_00412C30();

    void* rows[32];
    float unk490;
    float unk494;
    float unk498;
    float unk49c;
    s32 unk4a0;
    s32 unk4a4;
    u8 unk4a8;
    u8 unk4a9;
    u8 unk4aa;
    u8 unk4ab[5];
};

#endif
