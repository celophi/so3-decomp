#ifndef SO3_OVERLAYS_LIB_TEXT_00419A70_H
#define SO3_OVERLAYS_LIB_TEXT_00419A70_H

#include "types.h"
#include "overlays/lib/text_004BD360.h"

#ifdef __cplusplus
/** Partial widget with resident vtable at 0x1725D0. */
class ItemCreationClass1725D0 : public LibClass178600
{
public:
    /** @brief Initialize the widget storage and select kind 3. */
    inline ItemCreationClass1725D0();
    /** @brief Release the widget storage and destroy its base. */
    virtual ~ItemCreationClass1725D0();
    /** @brief Draw the list indicator. */
    virtual void func_00462310();
    LibStorageBlock0C unk40;
    u8 unk4c[4];
    float unk50;
    float unk54;
};

/** Partial widget with resident vtable at 0x172870. */
class ItemCreationClass172870 : public LibClass178600
{
public:
    /** @brief Initialize the widget storage and select kind 6. */
    inline ItemCreationClass172870();
    /** @brief Release the widget storage and destroy its base. */
    virtual ~ItemCreationClass172870();
    /** @brief Draw the marker widget. */
    virtual void func_00462310();
    LibStorageBlock0C unk40;
    u8 unk4c[4];
    u32 unk50;
    u32 unk54;
};

/** Partial widget with resident vtable at 0x172600. */
class ItemCreationClass172600 : public LibClass178600
{
public:
    /** @brief Initialize the widget storage and select kind 5. */
    inline ItemCreationClass172600();
    /** @brief Release the widget storage and destroy its base. */
    virtual ~ItemCreationClass172600();
    /** @brief Advance the scalar indicator and mark it for refresh. */
    virtual void func_00413D20();
    /** @brief Draw the scalar indicator. */
    virtual void func_00462310();
    LibStorageBlock0C unk40;
    u8 unk4c[4];
    float unk50;
};


/** Partial Lib widget with vtable D_174790 in main data. */
class LibClass174790 : public LibClass178600
{
public:
    /** @brief Release the widget storage and destroy its base. */
    virtual ~LibClass174790();
    LibStorageBlock0C unk40;
};

/** Partial Lib widget with vtable D_175170 in main data. */
class LibClass175170 : public LibClass178600
{
public:
    /** @brief Release the widget storage and destroy its base. */
    virtual ~LibClass175170();
    LibStorageBlock0C unk40;
};

typedef ItemCreationClass172600 LibClass172600;
typedef ItemCreationClass1725D0 LibClass1725D0;
typedef ItemCreationClass172870 LibClass172870;
extern "C" {
#else
typedef struct ItemCreationClass172600 ItemCreationClass172600;
typedef struct ItemCreationClass1725D0 ItemCreationClass1725D0;
typedef struct ItemCreationClass172870 ItemCreationClass172870;
#endif

/**
 * @brief Configure the list indicator's rectangle and scalar pair.
 * @param object List indicator widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param height Rectangle height.
 * @param first First scalar value.
 * @param second Second scalar value.
 * @return One on success, or zero if its storage could not be initialized.
 */
s32 func_41A930(ItemCreationClass1725D0* object, float x, float y, float height, float first, float second);

/**
 * @brief Initialize the scalar indicator rectangle and storage.
 * @param object Scalar indicator widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return One on success, or zero when storage initialization fails.
 */
s32 func_0041AD10(ItemCreationClass172600* object, float x, float y, float width, float height);

#ifdef __cplusplus
}
#endif

#endif
