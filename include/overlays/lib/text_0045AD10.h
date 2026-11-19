#ifndef SO3_OVERLAYS_LIB_TEXT_0045AD10_H
#define SO3_OVERLAYS_LIB_TEXT_0045AD10_H

#include "types.h"
#include "overlays/lib/ui_object.h"
#include "overlays/lib/shape.h"


struct FieldShapeRecord20;
class LibScene;

typedef struct LibDrawWidget LibDrawWidget;
typedef struct LibObject174D90 LibObject174D90;
typedef struct LibObject174F20 LibObject174F20;
typedef struct LibObject172410 LibObject172410;
typedef struct LibObject172440 LibObject172440;
typedef struct LibStringLabel LibStringLabel;
typedef struct LibTextExtent LibTextExtent;
#ifndef __cplusplus
typedef struct ItemCreationClass175030 LibClass175030;
#endif
#ifdef __cplusplus
class LibDisplayManager;

/** List object that copies its first display manager's camera state to the others, with vtable D_174D70 in main data. */
class LibClass174D70 : public LibListObject
{
public:
    /** @brief Start with no objects and flag 0x1 set. */
    LibClass174D70();

    /** @brief Free the buffer and detach. */
    virtual ~LibClass174D70();

    /**
     * @brief Report the list kind.
     * @return Nine.
     */
    virtual s32 get_default_list_kind();

    /** @brief Copy the first display manager's camera transform (flag 0x1), fog (0x2) and view (0x4) to the others. */
    virtual void update();

    u8 count;
    u8 flags;
    u8 unk16[2];
    LibDisplayManager* managers[9];
    u8* unk3c;
};
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

/** Resource header prefix containing section offsets, counts, and total size. */
struct LibResourceHeader
{
    u8 unk00[0x10];
    s32 offsets[4];
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2c;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3c;
    s32 size;
};

/** One 0x50-byte resource slot in the runtime table. */
struct LibManagedResourceSlot
{
    void* allocation;
    LibResourceHeader* data;
    u8* sections[4];
    s32 unk18;
    s32 unk1c;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2c;
    s32 unk30;
    s32 loaded;
    s32 unit_count;
    s32 loaded_units;
    s32 start;
    s32 end;
    s32 unk48;
    u16 identifier;
    u8 flag;
    u8 active;
};

#define LIB_DRAW_RECORD_CONTROL 0x4000
#define LIB_DRAW_RECORD_RUN 0x4010
#define LIB_DRAW_RECORD_NUMBER 0x401C

/** One 0x20-byte record a drawing widget lays out: a glyph, or the head of a run of glyphs. */
struct LibDrawRecord
{
    float left;
    float top;
    float right;
    float bottom;
    void* unk10;

    union
    {
        s32 width;
        float scale;
        LibDrawRecord* end;
    } unk14;

    union
    {
        u32 color;
        float scale_y;
    };

    u16 code;
    u16 glyph;
};

/** Text extent kept at a text widget's offset 0xE8. */
typedef struct LibTextExtent
{
    float unk00;
    float unk04;
    float width;
    float height;
} LibTextExtent;

/** Partial 0xFC-byte drawing widget, with vtable D_174EF0 in main data. */
struct LibDrawWidget : public LibWidget
{
    /** @brief Initialize the drawing widget. */
    LibDrawWidget();

    /** @brief Destroy the drawing widget. */
    virtual ~LibDrawWidget();

    /**
     * @brief Set the display rectangle; a zero width or height selects 1024.
     * @param x Left edge.
     * @param y Top edge.
     * @param width Width.
     * @param height Height.
     */
    void set_rectangle(float x, float y, float width, float height);

    /** @brief Hand the drawing storage to the resident release queue. */
    void release_storage();

    /**
     * @brief Size and allocate the drawing storage.
     * @param first First entry count.
     * @param capacity Second entry count.
     * @param second Third entry count.
     * @param third Fourth entry count.
     * @return One on success, or zero when nothing could be allocated.
     */
    s32 allocate_storage(s32 first, s32 capacity, s32 second, s32 third);

    /** @brief Clear the storage and restore the default scale, colours and alignment. */
    void reset_drawing_state();

    /**
     * @brief Start laying out records at the left edge of a line.
     * @param records First record to fill.
     * @param y Vertical pen position; zero also resets the measured extent.
     */
    void begin_layout(LibDrawRecord* records, float y);

    /**
     * @brief Lay out a number as one record.
     * @param value Value stored in the record.
     * @param digits Number of digits.
     */
    void add_number_record(void* value, s32 digits);

    /**
     * @brief Close the current run of records.
     * @param value Value stored in the run's head record.
     * @param count Value stored as the run's glyph index.
     */
    void end_run(void* value, s32 count);

    /** @brief Start a run of records at the pen position. */
    void begin_run();

    /**
     * @brief Format a number as character codes: one plus the digit for digits, 11 for anything else.
     * @param codes Receives the codes and a terminating zero.
     * @param value Number to format.
     * @return Number of codes written before the terminator.
     */
    s32 format_number_codes(u16* codes, s32 value);

    /**
     * @brief Convert text to character codes.
     *
     * Digits, letters and the symbols in the symbol table map to their own codes, half-width katakana (with a following
     * voiced or semi-voiced mark folded in) map to katakana, or to hiragana after an odd number of '~', and anything
     * else maps to 0xF1.
     * @param codes Receives the codes and a terminating zero.
     * @param text Text to convert; null gives no codes.
     * @return Number of codes written before the terminator.
     */
    s32 decode_text(u16* codes, const char* text);

    /**
     * @brief Lay out text glyph by glyph.
     * @param text Text to lay out.
     */
    void add_text(const char* text);

    /**
     * @brief Lay out a number glyph by glyph.
     * @param value Number to lay out.
     */
    void add_number(s32 value);

    /**
     * @brief Look up one of the eleven text palette colours.
     * @param index Palette index; larger values select the last colour.
     * @return Packed colour.
     */
    u32 get_palette_color(u8 index);

    /**
     * @brief Shift laid-out records to the horizontal alignment.
     * @param records Records to shift.
     * @param count Number of records.
     */
    void func_004637A0(LibDrawRecord* records, s32 count);

    /**
     * @brief Shift laid-out records to the vertical alignment and finish the extent.
     * @param records Records to shift.
     * @param count Number of records.
     */
    void align_records_vertically(LibDrawRecord* records, s32 count);

    /**
     * @brief Build the drawing packet for laid-out records.
     * @param records Records to draw.
     * @param count Number of records.
     */
    void draw_records(LibDrawRecord* records, s32 count);

    /**
     * @brief Start the drawing packet.
     * @param records Records to draw.
     * @param count Number of records.
     */
    void func_00463500(LibDrawRecord* records, s32 count);

    /** @brief Close the drawing packet. */
    void func_004623F0();

    /**
     * @brief Draw a glyph record.
     * @param record Record to draw.
     */
    void func_004624E0(LibDrawRecord* record);

    /**
     * @brief Draw a number record.
     * @param record Record to draw.
     */
    void func_00462C70(LibDrawRecord* record);

    /**
     * @brief Draw the head record of a run.
     * @param record Record to draw.
     */
    void func_00462FC0(LibDrawRecord* record);

    /**
     * @brief Lay out one glyph and advance the pen.
     * @param code Character code.
     */
    void add_glyph(s32 code);

    void* allocation;
    void* aligned;
    u32 unk48;
    u32 unk4c;
    u32 unk50;
    u32 dma_address;
    u64* packet_cursor;
    u8* unk5c;
    u8* unk60;
    u8* unk64;
    u8* unk68;
    LibManagedResourceSlot* resource_slot;
    u8* unk70;
    u8* unk74;

    float unk78;
    float unk7c;
    float draw_scale;
    float draw_scale_y;
    float unk88;
    float unk8c;
    float unk90;
    u32 tint;
    u32 draw_color;
    s32 horizontal_align;
    s32 vertical_align;
    s32 unka4;
    s32 unka8;
    s32 unkac;
    s32 unkb0;
    s32 unkb4;
    s32 record_count;
    LibDrawRecord* run_head;
    LibDrawRecord* next_record;
    float pen_x;
    float pen_y;
    float line_height;
    float min_height;
    float max_height;
    s32 unkd8;
    s32 unkdc;
    s32 unke0;
    s32 unke4;
    LibTextExtent extent;
    u8 unkf8;
    u8 unkf9;
    u8 unkfa;
    u8 unkfb;

    /**
     * @brief Set the display scale.
     * @param x Horizontal scale.
     * @param y Vertical scale.
     */
    void set_scale(float x, float y)
    {
        draw_scale_y = y;
        draw_scale = x;
        needs_redraw = 1;
    }

    /**
     * @brief Set the draw colour and mark the widget for redraw.
     * @param color Packed colour.
     */
    void set_color(u32 color)
    {
        draw_color = color;
        needs_redraw = 1;
    }

    /**
     * @brief Set the scale and mark the widget for redraw.
     * @param scale Horizontal scale.
     */
    void set_scale(float scale)
    {
        draw_scale = scale;
        needs_redraw = 1;
    }

    /**
     * @brief Set the spacing added between glyphs and mark the widget for redraw.
     * @param spacing Spacing added between glyphs before horizontal scaling.
     */
    void set_glyph_spacing(float spacing)
    {
        unk88 = spacing;
        needs_redraw = 1;
    }

    /**
     * @brief Set the alpha and mark the widget for redraw.
     * @param alpha Alpha.
     */
    void set_alpha(float alpha)
    {
        draw_alpha = alpha;
        needs_redraw = 1;
    }

    /**
     * @brief Set the colour the widget is modulated by and mark it for redraw.
     * @param color Packed colour.
     */
    void set_tint(u32 color)
    {
        tint = color;
        needs_redraw = 1;
    }

    /**
     * @brief Select vertical alignment within the display rectangle.
     * @param alignment Zero uses the origin; one centers; other values align to the end.
     */
    void set_vertical_align(s32 alignment)
    {
        vertical_align = alignment;
        needs_redraw = 1;
    }

    /**
     * @brief Set the horizontal alignment and mark the widget for redraw.
     * @param align Alignment.
     */
    void set_horizontal_align(s32 align)
    {
        horizontal_align = align;
        needs_redraw = 1;
    }
};
/** Two-dimensional screen position. */
struct LibPoint2
{
    float x;
    float y;
};

/** 0x3C-byte state that moves a widget towards a target position over a set time, with its vptr after the state. */
class LibMovementState
{
public:
    LibStorageBlock0C unk00;
    u8 unk0c[4];
    LibPoint2 position;
    LibPoint2 previous_position;
    LibPoint2 target;
    float move_frames;
    float speed;
    float alpha;
    u8 speed_ready;
    u8 arrived;
    u8 unk36[2];

    /** @brief Initialize the storage and clear its three scalar pairs. */
    LibMovementState()
    {
        position.y = 0.0f;
        position.x = 0.0f;
        previous_position.y = 0.0f;
        previous_position.x = 0.0f;
        target.y = 0.0f;
        target.x = 0.0f;
    }

    virtual ~LibMovementState()
    {
    }

    /** @brief Called once the position reaches the target; the base version does nothing. */
    virtual void on_arrived();

    /**
     * @brief Check whether the state is still moving towards its target.
     * @return True until the position reaches the target.
     */
    bool is_moving() const
    {
        return !arrived;
    }

    /**
     * @brief Allocate the drawing storage and show the state at a position at full alpha.
     * @param x Horizontal position.
     * @param y Vertical position.
     * @return One on success, or zero when the storage couldn't be allocated.
     */
    s32 init_position(float x, float y);

    /**
     * @brief Set the movement target and reset its completion flags.
     * @param x Target horizontal coordinate.
     * @param y Target vertical coordinate.
     * @param duration Duration in seconds, converted to sixty frames per second.
     */
    void set_move_target(float x, float y, float duration);

    /**
     * @brief Move one frame's distance towards the target, and then call on_arrived once it reaches the target.
     * @return One if the position changed since the last step, otherwise zero.
     */
    bool step();

    /**
     * @brief Rebuild the drawing packet at an offset from an origin.
     * @param origin Origin the position is relative to.
     * @param tag Packet tag word.
     * @param alpha Draw alpha.
     */
    void func_00466E70(const LibVector4* origin, u32 tag, float alpha);
};

/** Partial kind-9 widget with a storage base at offset 0x40. */
class ItemCreationClass175030 : public LibWidget, public LibMovementState
{
public:
    /** @brief Initialize the widget and select kind 9. */
    inline ItemCreationClass175030();

    virtual ~ItemCreationClass175030();

    /** @brief Update the movement state and its refresh flag. */
    virtual void func_00413D20();

    /** @brief Draw the moving widget. */
    virtual void draw();

    /**
     * @brief Put the widget at a position without moving there, and mark it for redraw.
     * @param x Horizontal position.
     * @param y Vertical position.
     */
    void snap_to(float x, float y)
    {
        position.x = x;
        position.y = y;
        arrived = 1;
        needs_redraw = 1;
    }
};

typedef ItemCreationClass175030 LibClass175030;

/** String-backed drawing widget with MAIN vtable at 0x175140. */
struct LibStringLabel : public LibDrawWidget
{
    /** @brief Initialize the string-backed drawing widget. */
    LibStringLabel()
    {
        unk38 = 14;
    }

    /**
     * @brief Initialize the label with its string and rectangle.
     * @param value String to draw.
     * @param flag Text flag.
     * @param x Left edge.
     * @param y Top edge.
     * @param width Width.
     * @param height Height.
     */
    LibStringLabel(const char* value, u8 flag, float x, float y, float width, float height)
    {
        unk38 = 14;
        init_text_rectangle(x, y, width, height, value, flag);
    }

    /**
     * @brief Change the string and mark the label for redraw.
     * @param value New string.
     */
    void set_text(const char* value)
    {
        text = value;
        needs_redraw = 1;
    }

    virtual ~LibStringLabel();

    /** @brief Draw the string-backed widget. */
    virtual void draw();

    /**
     * @brief Lay the string out off screen and measure it.
     * @return Extent of the laid-out string.
     */
    LibTextExtent* measure();

    /**
     * @brief Count the character codes in the string.
     * @return Number of codes.
     */
    s32 count_codes();

    /**
     * @brief Configure the drawing rectangle and string.
     * @param x Horizontal position.
     * @param y Vertical position.
     * @param width Drawing width.
     * @param height Drawing height.
     * @param value String to draw.
     * @param flag Drawing flag.
     * @return One on success, or zero when the drawing storage couldn't be set up.
     */
    s32 init_text_rectangle(float x, float y, float width, float height, const char* value, u8 flag);

    const char* text;
};

/** Partial 0x100-byte numeric widget, with MAIN vtable D_174F20. */
struct LibObject174F20 : public LibDrawWidget
{
    /** @brief Initialize the numeric widget and select widget kind 13. */
    LibObject174F20()
    {
        unk38 = 13;
    }

    virtual ~LibObject174F20();

    /** @brief Draw the numeric widget. */
    virtual void draw();

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

    /**
     * @brief Lay the number out off screen and measure it.
     * @return Extent of the laid-out number.
     */
    LibTextExtent* measure();

    u32 numeric_value;
};
/** Item code widget with MAIN vtable at 0x172410. */
struct LibObject172410 : public LibDrawWidget
{
    /** @brief Initialize the item code widget and select kind 15. */
    LibObject172410()
    {
        unk38 = 15;
    }

    virtual ~LibObject172410();

    /** @brief Draw the code widget. */
    virtual void draw();

    u16 unkfc;
    u8 unkfe;
    u8 unkff;
};
/** Detail code widget with MAIN vtable at 0x172440. */
struct LibObject172440 : public LibDrawWidget
{
    /** @brief Initialize the detail code widget and select kind 16. */
    LibObject172440()
    {
        unk38 = 16;
    }

    virtual ~LibObject172440();

    /** @brief Draw the code widget. */
    virtual void draw();

    u16 unkfc;
    u8 unkfe;
    u8 unkff;
};

#endif

#ifdef __cplusplus
/**
 * The display runtime reached through g_field_runtime: sixteen resource slots, the display list and the numbers that
 * formatted messages print. Resident vtable at 0x174F50.
 */
class FieldRuntime : public LibListObject
{
public:
    /**
     * @brief Initialize the runtime for a screen size.
     * @param width Screen width.
     * @param height Screen height.
     * @param reserved_width Width of an area kept out of the resource space, or zero.
     * @param reserved_height Height of that area, or zero.
     * @param scale Scale factor.
     */
    FieldRuntime(float width, float height, u16 reserved_width, u16 reserved_height, float scale);

    /** @brief Release the runtime's retained objects and storage. */
    virtual ~FieldRuntime();

    /**
     * @brief Return the list kind the runtime is queued under.
     * @return Three.
     */
    virtual s32 get_default_list_kind();

    /** @brief Hand the runtime to the release queues once, so it's deleted after the frame. */
    virtual void destroy();

    /** @brief Update the runtime once per frame. */
    virtual void update();

    LibManagedResourceSlot resource_slots[16];
    struct TextBank
    {
        s32 resource_slot;
        u32 base_key;
    } text_banks[2];
    float unk524;
    float unk528;
    s32 unk52c;
    s32 unk530;
    float screen_scale_x;
    float screen_scale_y;
    float screen_offset_x;
    float screen_offset_y;

    s32 unk544;
    u32 unk548;
    s32 resource_area_end;
    s32 unk550;
    struct ButtonMap
    {
        u16 buttons[8];
    }* button_map;
    void* display_chunks;
    void* display_first;
    void* display_last;
    s32 display_count;
    s32 message_arguments[10];
    u8 unk590[0x58];
    struct FieldCharacterNames* character_names;
    float rate;
    struct Input
    {
        u16 unk00;
        u16 unk02;
        u16 unk04;
    } inputs[2];
    u16 unk5fc;
    u8 unk5fe;
    u8 unk5ff;
    u8 unk600;
    u8 release_queued;
    u8 unk602[2];
};

/**
 * @brief Read the runtime's frame rate.
 * @param runtime Field runtime.
 * @return Frames elapsed this update.
 */
static inline float field_rate(const FieldRuntime* runtime)
{
    return runtime->rate;
}
#endif

typedef struct FieldRuntime FieldRuntime;
typedef struct LibTransformOwner LibTransformOwner;

/** Partial result selected by Lib shape predicates. */
typedef struct LibShapeTestResult1C
{
    u32 unk00;
    void* unk04;
    void* unk08;
    void* unk0c;
    void* unk10;
    struct LibTransformOwner* unk14;
    struct LibTransformOwner* unk18;
    const void* unk1c;
    const void* unk20;
    const void* unk24;
    const void* unk28;
    const void* unk2c;
    const void* unk30;
} LibShapeTestResult1C;


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Find one of the field runtime's display chunks.
 * @param runtime Field runtime.
 * @param index Chunk index.
 * @return Chunk, or null when the list is shorter.
 */
struct LibResourceChunkHeader* func_004650B0(FieldRuntime* runtime, s32 index);

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

/**
 * @brief Select the multiline text resource and drawing mode, then request a redraw.
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
LibDrawWidget* func_00464B10(LibDrawWidget* object);

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
 * @brief Initialize the moving widget's storage and position.
 * @param object Moving widget with its storage base at offset 0x40.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @return One on successful setup, otherwise zero.
 */
s32 lib_moving_widget_init_position(LibClass175030* object, float x, float y);

/**
 * @brief Lay the numeric widget's number out off screen and measure it.
 * @param object Numeric widget to measure.
 * @return Extent of the laid-out number.
 */
LibTextExtent* func_00464C20(LibObject174F20* object);

/**
 * @brief Refresh the record widget and return its measured bounds.
 * @param object Record widget holding the display data.
 * @return Four bounds components stored at offset 0xE8.
 */
LibTextExtent* func_00467950(LibStringLabel* object);

/**
 * @brief Count glyphs in the widget's current text.
 * @param object String-backed widget.
 * @return Converted glyph count.
 */
s32 func_004679B0(LibStringLabel* object);

/** Last result selected by the Lib shape predicates. */
extern LibShapeTestResult1C D_0050CB30;

/**
 * @brief Test a shape descriptor against a position query.
 * @param shape Descriptor supplying the transform and shape record index.
 * @param query Query position.
 * @return Predicate status.
 */
s32 func_0045BFB0(FieldShapeOwner18* shape, const LibVector4* query);

/**
 * @brief Test whether a sphere, moved by vf1-vf4 or vf5-vf8, overlaps a box moved by a matrix.
 * @param centre Box centre.
 * @param half_extents Aligned half extents in xyz.
 * @param sphere Aligned sphere: centre in xyz, radius in w.
 * @param second Non-zero to move the sphere by vf5-vf8 and scale it by vf9.y rather than vf1-vf4 and vf9.x.
 * @param matrix Aligned matrix that moves the sphere into the box's space.
 * @return Whether they overlap.
 */
bool func_0045E240(const LibVector4* centre, const void* half_extents, const LibVector4* sphere, s32 second,
                  const void* matrix);

/**
 * @brief Test whether two boxes, moved by the matrices in vf1-vf4 and vf5-vf8, overlap.
 * @param first_centre First box centre.
 * @param first_half_extents Aligned half extents of the first box in xyz.
 * @param second_centre Second box centre.
 * @param second_half_extents Aligned half extents of the second box in xyz.
 * @return Whether they overlap.
 */
bool func_0045E400(const LibVector4* first_centre, const void* first_half_extents, const LibVector4* second_centre,
                   const void* second_half_extents);

/**
 * @brief Test whether two spheres, moved by the matrices in vf1-vf4 and vf5-vf8 and scaled by vf9.x and vf9.y, touch.
 * @param first First sphere: centre in xyz, radius in w.
 * @param second Second sphere.
 * @return Whether they overlap or touch.
 */
bool func_0045E980(const LibVector4* first, const LibVector4* second);

/**
 * @brief Publish the two bound shape record arrays for subsequent predicates.
 * @param first First shape resource storage.
 * @param second Second shape resource storage.
 */
void func_0045F580(void* first, void* second);

/**
 * @brief Test a segment against a shape, its records and its children, recording the first record it touches.
 *
 * The shape's bounding sphere is checked first, with the shape's transform in vf1-vf5. The caller's vf1-vf5 come
 * back only when nothing is hit.
 * @param shape Shape to test.
 * @param start Aligned segment start.
 * @param end Aligned segment end.
 * @return One when the segment touches a record, otherwise zero.
 */
s32 func_0045B920(FieldShapeOwner18* shape, const LibVector4* start, const LibVector4* end);

/**
 * @brief Clip a ray's fraction interval against one slab plane.
 * @param near_fraction Entry fraction, raised when the plane cuts the start of the interval.
 * @param far_fraction Exit fraction, lowered when the plane cuts the end of the interval.
 * @param direction Ray direction along the slab axis.
 * @param distance Signed distance from the ray start to the plane along the axis.
 * @return One while the interval is not empty, otherwise zero.
 */
s32 func_0045C350(float* near_fraction, float* far_fraction, float direction, float distance);

/**
 * @brief Test whether a segment touches a box moved by the matrix in vf1-vf4, its half extents grown by vf5.y,
 *        recording where it enters and leaves.
 * @param centre Aligned box centre.
 * @param half_extents Aligned half extents in xyz.
 * @param start Aligned segment start.
 * @param end Aligned segment end.
 * @return Whether the segment touches the box.
 */
bool func_0045B360(const LibVector4* centre, const void* half_extents, const LibVector4* start,
                   const LibVector4* end);

/**
 * @brief Find a record of the shape with the given name in bound shape data.
 * @param storage Shape resource storage.
 * @param name Shape name, compared over sixteen characters.
 * @param offset Record offset from the shape's first record.
 * @return The record, or null when the data is not bound, no shape has the name or the shape has no records.
 */
FieldShapeRecord20* func_0045AE10(FieldClass1515D0* storage, const char* name, s32 offset);

/**
 * @brief Set the flag of the record with the given identifier, searching a sibling run of shapes and their children.
 * @param storage Shape resource storage.
 * @param shape First shape of the sibling run.
 * @param id Record identifier.
 * @param flag New flag value.
 */
void func_0045AF10(FieldClass1515D0* storage, FieldShapeOwner18* shape, u16 id, s32 flag);

/**
 * @brief Set the flag of the record with the given identifier anywhere in the shape data.
 * @param storage Shape resource storage.
 * @param id Record identifier.
 * @param flag New flag value.
 */
void func_0045B0E0(FieldClass1515D0* storage, s32 id, s32 flag);

/**
 * @brief Bind shape data: turn its offsets into pointers once and look up each shape's transform by name.
 * @param storage Shape resource storage.
 * @param manager Entry table searched for the shape names.
 */
void func_0045B110(FieldClass1515D0* storage, LibScene* manager);

/**
 * @brief Bind shape storage to a resource, freeing the previous one unless it was borrowed, and find its attribute
 *        chunk.
 * @param storage Shape resource storage.
 * @param resource Resource chunks; the storage borrows them.
 * @return One when an attribute chunk was found, otherwise zero.
 */
s32 func_0045B210(FieldClass1515D0* storage, void* resource);

/**
 * @brief Return one child of a shape.
 * @param shape Shape descriptor.
 * @param index Child index.
 * @return The child, or null when the shape has fewer children.
 */
FieldShapeOwner18* func_0045B2B0(FieldShapeOwner18* shape, s32 index);

/**
 * @brief Count the children of a shape.
 * @param shape Shape descriptor.
 * @return Number of child shapes.
 */
s32 func_0045B320(FieldShapeOwner18* shape);

/**
 * @brief Look a key up in a resource slot's sorted index by halving steps.
 * @param runtime Runtime that owns the slot table.
 * @param slot_index Resource slot index.
 * @param key Key to find.
 * @return The key's data in the slot's second section, or the placeholder text when it isn't there.
 */
void* func_00465340(FieldRuntime* runtime, u32 slot_index, s32 key);

/**
 * @brief Test a ray against a shape, its records and its children, recording the first record it passes through.
 *
 * The shape's bounding sphere is checked first, with the shape's transform in vf1-vf5. The caller's vf1-vf5 come
 * back only when nothing is hit.
 * @param shape Shape to test.
 * @param ray Aligned ray: origin, then direction.
 * @return One when the ray passes through a record, otherwise zero.
 */
s32 func_0045CBE0(FieldShapeOwner18* shape, const LibVector4* ray);

/**
 * @brief Append a transform receiver to the runtime display queue.
 * @param runtime Runtime manager.
 * @param object Transform receiver.
 * @return One when queued, or zero if the receiver already has an owner.
 */
s32 lib_queue_display_object(FieldRuntime* runtime, LibTransformOwner* object);

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

/** Run the two argument shape test on the referenced descriptor at offset 0x30. */
s32 func_0045D030(void* object, void* query);

/** Run the four argument shape test on the referenced descriptor at offset 0x30. */
s32 func_0045D590(void* object, const LibVector4* sphere, const void* matrix, float scale);

/** Run the five argument shape test on the referenced descriptor at offset 0x30. */
s32 func_0045DA90(void* object, const LibVector4* box, const void* matrix, const void* inverse, float scale);

/** Current shape record selected by a shape test. */
extern struct FieldShapeRecord20* D_001B656C;

/** Shape record of the other descriptor in a two-descriptor test. */
extern struct FieldShapeRecord20* D_001B6570;

/**
 * @brief Test a sphere against a shape, its records and its children, recording the first record it touches.
 *
 * The shape's bounding sphere is checked first, with the shape's transform in vf1-vf4 and the sphere's matrix in
 * vf5-vf8. The caller's vf1-vf9 come back only when nothing is hit.
 * @param shape Shape to test.
 * @param sphere Aligned sphere: centre in xyz, radius in w.
 * @param matrix Aligned matrix that moves the sphere.
 * @param scale Scale of the sphere's radius.
 * @return One when a record touches the sphere, otherwise zero.
 */
s32 func_0045D140(FieldShapeOwner18* shape, const LibVector4* sphere, const void* matrix, float scale);

/**
 * @brief Test a box against a shape, its records and its children, recording the first record it touches.
 *
 * The shape's bounding sphere is checked against the box's first, with the shape's transform in vf1-vf4 and the
 * box's matrix in vf5-vf8. The caller's vf1-vf9 come back only when nothing is hit.
 * @param shape Shape to test.
 * @param box Aligned box block: its bounding sphere (centred on the box) at index 2, its half extents at index 3.
 * @param matrix Aligned matrix that moves the box.
 * @param inverse Aligned inverse of the box's matrix.
 * @param scale Scale of the box.
 * @return One when a record touches the box, otherwise zero.
 */
s32 func_0045D5C0(FieldShapeOwner18* shape, const LibVector4* box, const void* matrix, const void* inverse,
                  float scale);

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
s32 func_0045EBD0(FieldShapeOwner18* first, FieldShapeOwner18* second);

void func_0045F600(void* object);

void func_0045F610(void* object);

void func_0045F620(void* object);

void func_0045F630(void* object);

void func_0045F640(void* object);

void func_0045F650(void* object);




#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
extern "C"
{
    void func_0045F5E0();
}
#endif

#endif
