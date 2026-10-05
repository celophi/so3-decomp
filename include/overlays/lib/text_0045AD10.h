#ifndef SO3_OVERLAYS_LIB_TEXT_0045AD10_H
#define SO3_OVERLAYS_LIB_TEXT_0045AD10_H

#include "types.h"
#include "overlays/lib/ui_object.h"

typedef struct LibClass174EF0 LibClass174EF0;
typedef struct LibObject174F20 LibObject174F20;
#ifdef __cplusplus
/** Partial 0xFC-byte drawing widget, with MAIN vtable D_174EF0. */
struct LibClass174EF0 : public LibClass178600
{
    /** @brief Initialize the drawing widget. */
    LibClass174EF0();
    /** @brief Destroy the drawing widget. */
    virtual ~LibClass174EF0();
    u8 unk40[0x40];
    float unk80;
    float unk84;
    u8 unk88[0xC];
    u32 unk94;
    u8 unk98[4];
    u32 unk9c;
    u32 unka0;
    u8 unka4[0x58];
    /** @brief Set the display scale. @param x Horizontal scale. @param y Vertical scale. */
    void set_scale(float x, float y)
    {
        unk84 = y;
        unk80 = x;
        unk3c = 1;
    }
    /** @brief Set the packed display color. @param color Packed color. */
    void set_color(u32 color)
    {
        unk94 = color;
        unk3c = 1;
    }
    /**
     * @brief Select vertical alignment within the display rectangle.
     * @param alignment Zero uses the origin; one centers; other values align to the end.
     */
    void set_vertical_alignment(u32 alignment)
    {
        unka0 = alignment;
        unk3c = 1;
    }
    /** @brief Set the display mode. @param mode Mode value. */
    void set_mode(u32 mode)
    {
        unk9c = mode;
        unk3c = 1;
    }
};
/** Partial 0x100-byte image widget, with MAIN vtable D_174F20. */
struct LibObject174F20 : public LibClass174EF0
{
    /** @brief Initialize the image widget and select widget kind 13. */
    LibObject174F20()
    {
        unk38 = 13;
    }
    /** @brief Destroy the image widget. */
    virtual ~LibObject174F20();
    u8 unkfc[4];
};
#endif

typedef struct FieldRuntime FieldRuntime;
typedef struct LibClass178A90 LibClass178A90;

/** Partial 0x1C-byte prefix of the result selected by Lib shape predicates. */
typedef struct LibShapeTestResult1C
{
    u32 unk00; /**< Predicate result state. */
    void* unk04; /**< First matched descriptor. */
    void* unk08; /**< Second matched descriptor. */
    void* unk0c; /**< First matched 0x20-byte record. */
    void* unk10; /**< Second matched 0x20-byte record. */
    struct LibClass178A90* unk14; /**< Transform for the first record. */
    struct LibClass178A90* unk18; /**< Transform for the second record. */
} LibShapeTestResult1C;


#ifdef __cplusplus
extern "C" {
#endif

/** Last result selected by the Lib shape predicates. */
extern LibShapeTestResult1C D_0050CB30;

/**
 * @brief Test a shape descriptor against a position query.
 * @param shape Descriptor supplying the transform and shape record index.
 * @param query Query position.
 * @return Predicate status.
 */
s32 func_0045BFB0(void* shape, void* query);

/**
 * @brief Publish the two bound shape record arrays for subsequent predicates.
 * @param first First shape resource storage.
 * @param second Second shape resource storage.
 */
void func_0045F580(void* first, void* second);

/**
 * @brief Evaluate the shape descriptor against two query values.
 * @param shape Shape descriptor.
 * @param first First query value.
 * @param second Second query value.
 * @return Predicate status.
 */
s32 func_0045B920(void* shape, void* first, void* second);

/**
 * @brief Bind shape storage to the supplied attribute resource.
 * @param storage Shape resource storage.
 * @param resource Attribute resource header and payload.
 * @return Status returned by the resource loader.
 */
s32 func_0045B210(void* storage, const void* resource);

/**
 * @brief Evaluate the shape descriptor against the supplied query.
 * @param shape Shape descriptor.
 * @param query Predicate input.
 * @return Predicate status.
 */
s32 func_0045CBE0(void* shape, void* query);

/**
 * @brief Attach a transform receiver to the runtime.
 * @param runtime Runtime manager.
 * @param object Transform receiver.
 */
void func_00465B20(FieldRuntime* runtime, LibClass178A90* object);
/**
 * @brief Bind resource storage in the runtime.
 * @param runtime Runtime manager.
 * @param data Aligned resource storage.
 * @return Bound resource slot.
 */
s32 func_004656B0(FieldRuntime* runtime, void* data);

/**
 * @brief Configure one image slot and its rectangle.
 * @param object Image widget.
 * @param value Resource value.
 * @param slot Image slot index.
 * @param flag Slot state flag.
 * @param x Rectangle origin x.
 * @param y Rectangle origin y.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return Configuration status.
 */
s32 func_00464D90(LibObject174F20* object, u32 value, s32 slot, u8 flag, float x, float y, float width, float height);

/**
 * @brief Release one slot of the manager's table of 0x50-byte slots at offset 0x14.
 *
 * A slot in use has its object queued on the resident object queue, then is
 * cleared and marked free, and the data cache is flushed.
 * @param manager Slot manager.
 * @param index Slot to release.
 */
void func_00465430(void* manager, s32 index);

/**
 * @brief Run the test at offset 0x30 of the object referenced by the first word of object.
 * @param object Object whose first word refers to the tested object.
 * @param arg0 First argument passed to the test.
 * @param arg1 Second argument passed to the test.
 * @return The test result.
 */
s32 func_0045BD20(void* object, void* arg0, void* arg1);

/**
 * @brief Run func_0045EBD0 on the objects referenced by the first words of two objects.
 *
 * The word at offset 0xC of each referenced object is stored in a global first.
 * @param object Object whose first word refers to the first tested object.
 * @param other Object whose first word refers to the second tested object.
 * @return The func_0045EBD0 result.
 */
s32 func_0045F5A0(void* object, void* other);

/**
 * @brief Test two shape descriptors.
 * @param first First shape descriptor.
 * @param second Second shape descriptor.
 * @return One when the shape test succeeds, otherwise zero.
 */
s32 func_0045EBD0(void* first, void* second);

#ifdef __cplusplus
}
#endif

#endif
