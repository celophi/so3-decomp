#ifndef SO3_OVERLAYS_LIB_TEXT_0045AD10_H
#define SO3_OVERLAYS_LIB_TEXT_0045AD10_H

#include "types.h"
#include "overlays/lib/ui_object.h"

typedef struct LibClass174EF0 LibClass174EF0;
typedef struct LibObject174D90 LibObject174D90;
typedef struct LibObject174F20 LibObject174F20;
typedef struct LibObject172410 LibObject172410;
typedef struct LibObject172440 LibObject172440;
typedef struct LibObject175140 LibObject175140;
typedef struct LibBounds4C69B0 LibBounds4C69B0;
#ifndef __cplusplus
typedef struct ItemCreationClass175030 LibClass175030;
#endif
#ifdef __cplusplus
/** Managed three-word DMA storage, initialized by clearing its allocation. */
class LibStorageBlock0C
{
public:
    /** @brief Clear the owned allocation. */
    LibStorageBlock0C()
    {
        allocation = 0;
    }
    /** @brief Release the owned allocation. */
    ~LibStorageBlock0C();
    void* allocation;
    void* aligned;
    u32 dma_address;
};

/**
 * @brief Allocate aligned drawing storage for an empty block.
 * @param storage Storage block to initialize.
 * @param word_count Number of 64-bit drawing words requested.
 * @return One on success, or zero if storage exists or allocation fails.
 */
extern "C" s32 lib_allocate_drawing_storage(LibStorageBlock0C* storage, s32 word_count);

/** Partial 0xFC-byte drawing widget, with MAIN vtable D_174EF0. */
struct LibClass174EF0 : public LibClass178600
{
    /** @brief Initialize the drawing widget. */
    LibClass174EF0();
    /** @brief Destroy the drawing widget. */
    virtual ~LibClass174EF0();
    /** Backing drawing-storage allocation. */
    void* allocation;
    u8 unk44[0x2C];
    void* unk70;
    u8 unk74[4];
    u32 unk78;
    u32 unk7c;
    float unk80;
    float unk84;
    float unk88;
    float unk8c;
    u32 unk90;
    u32 unk94;
    u32 unk98;
    u32 unk9c;
    u32 unka0;
    u8 unka4[0x44];
    float unke8;
    float unkec;
    float unkf0;
    float unkf4;
    u8 unkf8;
    u8 unkf9;
    u8 unkfa;
    u8 unkfb;
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
/** 0x3C-byte storage receiver, with its dispatch pointer after the stored state. */
class ItemCreationClass185050
{
public:
    LibStorageBlock0C unk00;
    u8 unk0c[4];
    float unk10;
    float unk14;
    float unk18;
    float unk1c;
    float unk20;
    float unk24;
    u8 unk28[8];
    float unk30;
    u8 unk34;
    u8 unk35;
    u8 unk36[2];

    /** @brief Initialize the storage and clear its three scalar pairs. */
    ItemCreationClass185050()
    {
        unk14 = 0.0f;
        unk10 = 0.0f;
        unk1c = 0.0f;
        unk18 = 0.0f;
        unk24 = 0.0f;
        unk20 = 0.0f;
    }
    /** @brief Release the owned storage. */
    virtual ~ItemCreationClass185050()
    {
    }
    virtual void func_slot0c();
    /**
     * @brief Set the movement target and reset its completion flags.
     * @param x Target horizontal coordinate.
     * @param y Target vertical coordinate.
     * @param duration Duration in seconds, converted to sixty frames per second.
     */
    void func_00466E40(float x, float y, float duration);

};

/** Partial kind-9 widget with a storage base at offset 0x40. */
class ItemCreationClass175030 : public LibClass178600, public ItemCreationClass185050
{
public:
    /** @brief Initialize the widget and select kind 9. */
    inline ItemCreationClass175030();
    /** @brief Destroy the storage base and widget base. */
    virtual ~ItemCreationClass175030();
    /** @brief Update the movement state and its refresh flag. */
    virtual void func_00413D20();
    /** @brief Draw the moving widget. */
    virtual void func_00462310();
};

typedef ItemCreationClass185050 LibMovementState;
typedef ItemCreationClass175030 LibClass175030;

/** String-backed drawing widget with MAIN vtable at 0x175140. */
struct LibObject175140 : public LibClass174EF0
{
    /** @brief Initialize the string-backed drawing widget. */
    LibObject175140()
    {
        unk38 = 14;
    }
    /** @brief Destroy the string-backed drawing widget. */
    virtual ~LibObject175140();
    /** @brief Draw the string-backed widget. */
    virtual void func_00462310();
    /**
     * @brief Configure the drawing rectangle and string.
     * @param x Horizontal position.
     * @param y Vertical position.
     * @param width Drawing width.
     * @param height Drawing height.
     * @param value String to draw.
     * @param flag Drawing flag.
     * @return Configuration status.
     */
    s32 func_00467AD0(float x, float y, float width, float height, const char* value, u8 flag);
    const char* unkfc;
};

/** Partial 0x100-byte numeric widget, with MAIN vtable D_174F20. */
struct LibObject174F20 : public LibClass174EF0
{
    /** @brief Initialize the numeric widget and select widget kind 13. */
    LibObject174F20()
    {
        unk38 = 13;
    }
    /** @brief Destroy the numeric widget. */
    virtual ~LibObject174F20();
    /** @brief Draw the numeric widget. */
    virtual void func_00462310();
    /**
     * @brief Configure the numeric widget and its rectangle.
     * @param x Rectangle origin x.
     * @param y Rectangle origin y.
     * @param width Rectangle width.
     * @param height Rectangle height.
     * @param value Numeric value.
     * @param slot Slot argument.
     * @param flag Flag argument.
     * @return Configuration status.
     */
    s32 init_numeric_resource_rectangle(float x, float y, float width, float height, u32 value, s32 slot, u8 flag);
    u32 numeric_value;
};
/** Item code widget with MAIN vtable at 0x172410. */
struct LibObject172410 : public LibClass174EF0
{
    /** @brief Initialize the item code widget and select kind 15. */
    LibObject172410()
    {
        unk38 = 15;
    }
    /** @brief Destroy the item code widget. */
    virtual ~LibObject172410();
    /** @brief Draw the code widget. */
    virtual void func_00462310();
    u16 unkfc;
    u8 unkfe;
    u8 unkff;
};
/** Detail code widget with MAIN vtable at 0x172440. */
struct LibObject172440 : public LibClass174EF0
{
    /** @brief Initialize the detail code widget and select kind 16. */
    LibObject172440()
    {
        unk38 = 16;
    }
    /** @brief Destroy the detail code widget. */
    virtual ~LibObject172440();
    /** @brief Draw the code widget. */
    virtual void func_00462310();
    u16 unkfc;
    u8 unkfe;
    u8 unkff;
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

/**
 * @brief Initialize the item code widget's rectangle and drawing storage.
 * @param object Item code widget.
 * @param x Rectangle origin x.
 * @param y Rectangle origin y.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @param code Initial item code.
 * @param variation Code variation.
 * @param flag Drawing state flag.
 * @return One on successful initialization, otherwise zero.
 */
s32 lib_item_code_init_rectangle(LibObject172410* object, float x, float y, float width, float height, u16 code, u8 variation, u8 flag);

/**
 * @brief Initialize the detail code widget's rectangle and drawing storage.
 * @param object Detail code widget.
 * @param code Initial detail code.
 * @param variation Code variation.
 * @param flag Drawing state flag.
 * @param x Rectangle origin x.
 * @param y Rectangle origin y.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return One on successful initialization, otherwise zero.
 */
s32 lib_detail_code_init_rectangle(LibObject172440* object, u16 code, u8 variation, u8 flag, float x, float y, float width, float height);

/** @brief Select the multiline text resource and drawing mode, then request a redraw.
 * @param object Multiline text widget.
 * @param source Resource source word.
 * @param key Text resource key.
 * @param mode Drawing mode.
 * @param flag Resource state flag.
 */
void lib_multiline_text_set_resource(LibObject174D90* object, u32 source, s32 key, u32 mode, u32 flag);

/**
 * @brief Initialize the native drawing-widget base and install its table.
 * @param object Storage for the 0xFC-byte drawing widget.
 * @return The constructed drawing widget.
 */
LibClass174EF0* func_00464B10(LibClass174EF0* object);

/**
 * @brief Reset the multiline widget rectangle, allocation, and scrolling state.
 * @param object Multiline text widget.
 * @param x Rectangle origin x.
 * @param y Rectangle origin y.
 * @param width Rectangle width.
 * @param height Rectangle height.
 */
void lib_multiline_text_init_rectangle(LibObject174D90* object, float x, float y, float width, float height);

/**
 * @brief Initialize the multiline text rectangle and load its resource.
 * @param object Multiline text widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @param slot Resource source word.
 * @param key Text resource key.
 * @param mode Drawing mode mask.
 * @param flag Slot state flag whose low byte is stored.
 * @return Resource initialization status.
 */
s32 lib_multiline_text_init_resource_rectangle(LibObject174D90* object, float x, float y, float width, float height, s32 slot, s32 key, u32 mode, u32 flag);

/**
 * @brief Set the widget movement target and reset its completion flags.
 * @param object Widget movement storage.
 * @param x Target horizontal coordinate.
 * @param y Target vertical coordinate.
 * @param duration Duration in seconds, converted to sixty frames per second.
 */
void func_00466E40(void* object, float x, float y, float duration);

/**
 * @brief Initialize the moving widget's storage and position.
 * @param object Moving widget with its storage base at offset 0x40.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @return One on successful setup, otherwise zero.
 */
s32 lib_moving_widget_init_position(LibClass175030* object, float x, float y);

/**
 * @brief Refresh the record widget and return its measured bounds.
 * @param object Record widget holding the display data.
 * @return Four bounds components stored at offset 0xE8.
 */
LibBounds4C69B0* func_00467950(LibObject175140* object);
/** @brief Count glyphs in the widget's current text. @param object String-backed widget. @return Converted glyph count. */
s32 func_004679B0(LibObject175140* object);

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
 * @brief Append a transform receiver to the runtime display queue.
 * @param runtime Runtime manager.
 * @param object Transform receiver.
 * @return One when queued, or zero if the receiver already has an owner.
 */
s32 lib_queue_display_object(FieldRuntime* runtime, LibClass178A90* object);
/**
 * @brief Load resource data into an owned runtime slot.
 * @param runtime Runtime manager.
 * @param data Source resource data.
 * @return Loaded slot identifier, or zero when allocation fails.
 */
s32 lib_load_resource_slot(FieldRuntime* runtime, void* data);

/**
 * @brief Initialize the numeric widget rectangle, resource slot, and displayed value.
 * @param object Numeric widget.
 * @param value Initial numeric value.
 * @param slot Runtime resource slot index.
 * @param flag Slot state flag.
 * @param x Rectangle origin x.
 * @param y Rectangle origin y.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return Configuration status.
 */
s32 lib_numeric_widget_init_rectangle(LibObject174F20* object, u32 value, s32 slot, u8 flag, float x, float y, float width, float height);

/**
 * @brief Release one slot of the manager's table of 0x50-byte slots at offset 0x14.
 *
 * A slot in use has its object queued on the resident object queue, then is
 * cleared and marked free, and the data cache is flushed.
 * @param manager Slot manager.
 * @param index Slot to release.
 */
void lib_release_resource_slot(void* manager, s32 index);

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

/** Return the fixed integer value 3. */
s32 func_00464E30(void* object);

/** Return the fixed integer value 7. */
s32 func_00468360(void* object);

/** Return the fixed value 0. */
s32 func_00468370(void* object);

void func_0045F600(void* object);
void func_0045F610(void* object);
void func_0045F620(void* object);
void func_0045F630(void* object);
void func_0045F640(void* object);
void func_0045F650(void* object);
void func_00461960(void* object);
void func_00461970(void* object);
void func_00461980(void* object);
void func_00461990(void* object);
void func_004619A0(void* object);
void func_004619B0(void* object);
void func_004619C0(void* object);
void func_004619D0(void* object);
void func_004619E0(void* object);
void func_004662A0(void* object);


/** Forward the receiver to func_004D00B0. */
void func_00467480(void* object);

/** Forward the receiver to func_004D00B0. */
void func_0046A3F0(void* object);

#ifdef __cplusplus
}
#endif

#endif
