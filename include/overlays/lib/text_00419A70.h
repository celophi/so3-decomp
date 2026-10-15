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
void func_00423930(u8* object);
void func_0041E880(u8* object);
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
s32 lib_list_indicator_init(ItemCreationClass1725D0* object, float x, float y, float height, float first, float second);

/**
 * @brief Allocate marker drawing storage and initialize its rectangle and colors.
 * @param object Marker widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return One on success, or zero if storage cannot be allocated.
 */
s32 lib_marker_init_rectangle(ItemCreationClass172870* object, float x, float y, float width, float height);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0041A530(void* object);

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

/**
 * @brief Set the receiver's byte at offset 0x60 to seven.
 * @param object Receiver to update.
 */
void func_0041AD80(void* object);

/** @brief Clear the intrusive owner and call the transform release hook. @param object Transform owner to detach. */
void func_0041ADC0(LibClass178A90* object);

/**
 * @brief Set the receiver's byte at offset 0x60 to seven.
 * @param object Receiver to update.
 */
void func_0041F130(void* object);

/**
 * @brief Set the receiver's byte at offset 0x60 to seven.
 * @param object Receiver to update.
 */
void func_0041F190(void* object);

/** @brief Clear the intrusive owner and call the transform release hook. @param object Transform owner to detach. */
void func_0041F170(LibClass178A90* object);
/** @brief Clear the intrusive owner and call the transform release hook. @param object Transform owner to detach. */
void func_0041F1D0(LibClass178A90* object);
/** @brief Clear the intrusive owner and call the transform release hook. @param object Transform owner to detach. */
void func_0041F290(LibClass178A90* object);

/**
 * @brief Set the receiver's byte at offset 0x60 to seven.
 * @param object Receiver to update.
 */
void func_0041F250(void* object);

/**
 * @brief Return the fixed value 16.
 * @param object Receiver or first argument; unused.
 * @return Always 16.
 */
s32 func_00421240(void* object);

/**
 * @brief Store two pointers in the receiver at offsets 0x14 and 0x18.
 * @param object Receiver to update.
 * @param first Pointer stored at offset 0x14.
 * @param second Pointer stored at offset 0x18.
 */
void func_004214C0(void* object, void* first, void* second);

/**
 * @brief Return the fixed value 398.
 * @param object Receiver or first argument; unused.
 * @return Always 398.
 */
s32 func_004249C0(void* object);

/**
 * @brief Return the fixed value 230.
 * @param object Receiver or first argument; unused.
 * @return Always 230.
 */
s32 func_00424A50(void* object);

/**
 * @brief Set the receiver's byte at offset 0x60 to nine.
 * @param object Receiver to update.
 */
void func_00424A60(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00424AD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00425280(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_004284E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_004284F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00428500(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00428DC0(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00428E40(void* object);

/**
 * @brief Return the fixed value 5.
 * @param object Receiver or first argument; unused.
 * @return Always 5.
 */
s32 func_004294F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_004295C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00429850(void* object);


/** Store the word at receiver offset 0x70. */
void func_004295B0(void* object, u32 value);


/** Forward the receiver to func_004D00B0. */
void func_0041AE30(void* object);

/** Forward the receiver to func_004D00B0. */
void func_0041D210(void* object);

/** Forward the receiver to func_004D00B0. */
void func_0041E8C0(void* object);

/** Forward the receiver to func_004D00B0. */
void func_0041F300(void* object);

/** Forward the receiver to func_004D00B0. */
void func_00423970(void* object);

/** Build and return a pointer to the four-word stack value. */
void* func_0041AD90(void);
/** Build and return a pointer to the four-word stack value. */
void* func_0041F140(void);
/** Build and return a pointer to the four-word stack value. */
void* func_0041F1A0(void);
/** Build and return a pointer to the four-word stack value. */
void* func_0041F260(void);
/** Build and return a pointer to the four-word stack value. */
void* func_00424A70(void);

#ifdef __cplusplus
/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_004297F0(void* object, u8 mode);


}
#endif

#ifdef __cplusplus
extern "C" s32 func_0041A170(void* object);
extern "C" s32 func_0041AE50(void* object);
extern "C" s32 func_0041D230(void* object);
extern "C" s32 func_0041E8E0(void* object);
extern "C" s32 func_0041F320(void* object);
extern "C" s32 func_00423990(void* object);
/** Set the output values when the input float is positive. */
extern "C" s32 func_004284A0(void* object, const void* value, float* zero_output, float* small_output);
#endif

#endif
