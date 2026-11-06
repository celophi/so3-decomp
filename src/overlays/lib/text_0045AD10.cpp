#include "include_asm.h"
#include "main/func_0011EE00.h"
#include "main/resident_data.h"
#include "sdk/main/libkernl_00121940.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/lib/text_004BD360.h"
#include "main/resident_001001E0.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "overlays/lib/text_004DD440.h"
#include "main/resident_0010A0E0.h"

extern "C" void func_00461830(void* embedded, void* adjusted);

enum
{
    DRAWING_STORAGE_ALIGNMENT = 128,
    DRAWING_STORAGE_PREFIX = 64,
    DRAWING_STORAGE_DMA_ADDRESS_TAG = 0x30000000
};

/** Partial text resource fields and the inherited redraw flag. */
typedef struct LibMultilineResourceState
{
    u8 pad00[0x3C];
    u8 redraw;
    u8 pad3d[0xCB];
    u32 source;
    u32 key;
    u8 flag;
    u8 pending;
    u8 pad112[0x432];
    u32 mode;
} LibMultilineResourceState;

/** Partial runtime queue links carried by each transform receiver. */
typedef struct LibRuntimeListNode
{
    u8 pad00[0x94];
    FieldRuntime* owner;
    struct LibRuntimeListNode* previous;
    struct LibRuntimeListNode* next;
} LibRuntimeListNode;
/** Partial runtime display queue with its head, tail, and count. */
typedef struct LibRuntimeListState
{
    u8 pad00[0x55C];
    LibRuntimeListNode* first;
    LibRuntimeListNode* last;
    s32 count;
} LibRuntimeListState;

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045AD10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045ADB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045AE10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045AF10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045B0E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045B110);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045B210);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045B2B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045B320);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045B360);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045B740);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045B920);

/** Select the referenced shape record and test its descriptor. */
s32 func_0045BD20(void* object, void* arg0, void* arg1)
{
    void* descriptor = *(void**)object;
    D_001B656C = (struct FieldShapeRecord20*)*(void**)((u8*)descriptor + 0xC);
    return func_0045B920((u8*)descriptor + 0x30, arg0, arg1);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045BD50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045BE60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045BED0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045BFB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045C350);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045C420);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045C770);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045C910);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045CB40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045CBE0);

/** Select the referenced shape record and run the two argument test. */
s32 func_0045D030(void* object, void* query)
{
    void* descriptor = *(void**)object;
    D_001B656C = (struct FieldShapeRecord20*)*(void**)((u8*)descriptor + 0xC);
    return func_0045CBE0((u8*)descriptor + 0x30, query);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045D060);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045D140);

/** Select the referenced shape record and run the four argument test. */
s32 func_0045D590(void* object, s32 arg0, s32 arg1, float value)
{
    void* descriptor = *(void**)object;
    D_001B656C = (struct FieldShapeRecord20*)*(void**)((u8*)descriptor + 0xC);
    return func_0045D140((u8*)descriptor + 0x30, arg0, arg1, value);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045D5C0);

/** Select the referenced shape record and run the five argument test. */
s32 func_0045DA90(void* object, s32 arg0, s32 arg1, s32 arg2, float value)
{
    void* descriptor = *(void**)object;
    D_001B656C = (struct FieldShapeRecord20*)*(void**)((u8*)descriptor + 0xC);
    return func_0045D5C0((u8*)descriptor + 0x30, arg0, arg1, arg2, value);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045DAC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045DCC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045E240);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045E400);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045E980);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045EA10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045EBD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045F2B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045F580);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045F5A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045F5E0);

void func_0045F600(void* object)
{
}

void func_0045F610(void* object)
{
}

void func_0045F620(void* object)
{
}

void func_0045F630(void* object)
{
}

void func_0045F640(void* object)
{
}

void func_0045F650(void* object)
{
}

extern "C" s32 func_00451B90(s32 code);

/**
 * @brief Run func_00451B90 on the value at offset 0x564 when the byte at 0x57A is set.
 * @return The func_00451B90 result, or zero.
 */
s32 LibObject174D90::func_0045F660()
{
    s32 result = 0;

    if (unk57a)
    {
        result = func_00451B90(unk564);
    }

    return result;
}

extern "C" void lib_multiline_text_set_resource(LibObject174D90* object, u32 source, s32 key, u32 mode, u32 flag)
{
    LibMultilineResourceState* state = (LibMultilineResourceState*)object;
    state->source = source;
    state->key = key;
    state->mode = mode;
    state->flag = flag;
    state->pending = 1;
    state->redraw = 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045F6B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045F710);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045FE90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004601F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004602B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00460750);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00461230);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004614E0);

typedef struct LibMultilineRectangleState
{
    u8 pad00[0x70];
    void* display;
    u8 pad74[0x84];
    u8 flag;
    u8 padf9[0x1B];
    void* allocation;
    u8 pad118[0x40C];
    float unk524;
    float unk528;
    u8 pad52c[0x28];
    u32 unk554;
    u8 pad558[0xC];
    u32 unk564;
    u8 pad568[0xC];
    u8 unk574;
} LibMultilineRectangleState;
/**
 * @brief Initialize the text rectangle and reset the multiline drawing state.
 * @param object Multiline text widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 */
extern "C" void lib_multiline_text_init_rectangle(LibObject174D90* object, float x, float y, float width, float height)
{
    LibMultilineRectangleState* state = (LibMultilineRectangleState*)object;
    lib_text_init_rectangle((LibTextWidget*)object, x, y, width, height);
    state->allocation = 0;
    state->display = 0;
    state->unk524 = 0.05f;
    state->unk528 = 1.5f;
    state->unk554 = 2;
    state->unk564 = 0;
    state->unk574 = 0;
}

extern "C" s32 func_004614E0(LibObject174D90* object, s32 slot, s32 key, u32 mode, u32 flag);

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
extern "C" s32 lib_multiline_text_init_resource_rectangle(LibObject174D90* object, float x, float y, float width, float height, s32 slot, s32 key, u32 mode, u32 flag)
{
    LibMultilineRectangleState* state = (LibMultilineRectangleState*)object;
    state->flag = flag;
    lib_text_init_rectangle((LibTextWidget*)object, x, y, width, height);
    state->allocation = 0;
    state->display = 0;
    state->unk524 = 0.05f;
    state->unk528 = 1.5f;
    state->unk554 = 2;
    state->unk564 = 0;
    state->unk574 = 0;
    return func_004614E0(object, slot, key, mode, 1);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004617B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00461830);

/**
 * @brief Allocate aligned drawing storage for an empty block and flush the data cache.
 * @param storage Storage block to initialize.
 * @param word_count Number of 64-bit drawing words requested.
 * @return One on success, or zero if storage exists or allocation fails.
 */
extern "C" s32 lib_allocate_drawing_storage(LibStorageBlock0C* storage, s32 word_count)
{
    if (storage->allocation != 0)
    {
        return 0;
    }
    storage->allocation = new (0) u8[word_count * sizeof(u64) + DRAWING_STORAGE_PREFIX + DRAWING_STORAGE_ALIGNMENT];
    if (storage->allocation == 0)
    {
        return 0;
    }
    u8* buffer = static_cast<u8*>(storage->allocation) + DRAWING_STORAGE_PREFIX;
    storage->aligned = reinterpret_cast<void*>((reinterpret_cast<u32>(buffer) + DRAWING_STORAGE_ALIGNMENT - 1) & ~(DRAWING_STORAGE_ALIGNMENT - 1u));
    storage->dma_address = reinterpret_cast<u32>(storage->aligned) | DRAWING_STORAGE_DMA_ADDRESS_TAG;
    FlushCache(0);
    return 1;
}

/** @brief Free the owned byte array and clear its allocation pointer. */
LibStorageBlock0C::~LibStorageBlock0C()
{
    if (allocation)
    {
        delete[] (u8*)allocation;
        allocation = 0;
    }
}

void func_00461960(void* object)
{
}

void func_00461970(void* object)
{
}

void func_00461980(void* object)
{
}

void func_00461990(void* object)
{
}

void func_004619A0(void* object)
{
}

void func_004619B0(void* object)
{
}

void func_004619C0(void* object)
{
}

void func_004619D0(void* object)
{
}

void func_004619E0(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004619F0);

/** Message window states that wait to be advanced. */
#define LIB_MESSAGE_WINDOW_STATE_WAIT 4
#define LIB_MESSAGE_WINDOW_STATE_WAIT_END 6

/**
 * @brief Advance from state 4 or 6 to the next state.
 * @return One when the state advanced, otherwise zero.
 */
s32 LibMessageWindow::func_00461B60()
{
    if (state != LIB_MESSAGE_WINDOW_STATE_WAIT && state != LIB_MESSAGE_WINDOW_STATE_WAIT_END)
    {
        return 0;
    }

    state++;
    return 1;
}

/** Message window states that wait to be advanced. */
#define LIB_MESSAGE_WINDOW_STATE_WAIT 4
#define LIB_MESSAGE_WINDOW_STATE_WAIT_END 6

/** Message window state that loads the text. */
#define LIB_MESSAGE_WINDOW_STATE_LOAD 2

/** Mode bits kept when new text is loaded. */
#define LIB_MESSAGE_WINDOW_KEPT_MODE 0x50000

/**
 * @brief In state 4 or 6, load new text into the window and go back to state 2.
 * @param source Resource source word.
 * @param key Text resource key.
 * @param mode Drawing mode; its bits 16 and 18 are kept from the current mode.
 * @param flag Resource state flag.
 * @return One when the text was loaded, otherwise zero.
 */
s32 LibMessageWindow::func_00461BA0(u32 source, s32 key, u32 mode, u32 flag)
{
    if (state != LIB_MESSAGE_WINDOW_STATE_WAIT && state != LIB_MESSAGE_WINDOW_STATE_WAIT_END)
    {
        return 0;
    }

    this->source = source;
    this->key = key;
    this->mode = (this->mode & LIB_MESSAGE_WINDOW_KEPT_MODE) | (mode & ~LIB_MESSAGE_WINDOW_KEPT_MODE);
    lib_multiline_text_set_resource(&text, this->source, this->key, this->mode, flag);
    state = LIB_MESSAGE_WINDOW_STATE_LOAD;
    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00461C30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00461E50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00461FA0);

/** @brief Flag a control code for the window and set its flag byte at 0x1064. */
void LibMessageWindowText::func_0045F650()
{
    owner->unk1063 = 1;
    owner->unk1064 = 1;
}

/**
 * @brief Pass a one-value control code to the window and set its flag byte at 0x1064.
 * @param value Control value.
 */
void LibMessageWindowText::func_0045F640(u32 value)
{
    owner->unk1062 = 1;
    owner->unk1050 = value;
    owner->unk1064 = 1;
}

/**
 * @brief Pass a one-value control code to the window.
 * @param value Control value.
 */
void LibMessageWindowText::func_0045F630(u32 value)
{
    owner->unk1061 = 1;
    owner->unk1050 = value;
}

/**
 * @brief Pass a three-value control code to the window.
 * @param first First value.
 * @param second Second value.
 * @param third Third value.
 */
void LibMessageWindowText::func_0045F620(s16 first, s16 second, u32 third)
{
    owner->unk1054 = first;
    owner->unk1056 = second;
    owner->unk1058 = third;
    owner->unk105e = 1;
}

/** @brief Flag the end of the text for the window. */
void LibMessageWindowText::func_0045F610()
{
    owner->unk105d = 1;
}

/** @brief Flag the restart for the window. */
void LibMessageWindowText::func_0045F600()
{
    owner->unk105c = 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00462290);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004622F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00462300);

void LibWidget::draw()
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00462320);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004623F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004624E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00462C70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00462FC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00463500);

/** LibDrawWidget::vertical_align value that centres the text. */
#define LIB_ALIGN_CENTER 1

/**
 * @brief Shift laid-out records to the vertical alignment and finish the extent.
 * @param records Records to shift.
 * @param count Number of records.
 */
void LibDrawWidget::align_records_vertically(LibDrawRecord* records, s32 count)
{
    if (vertical_align != 0)
    {
        float offset = unk18.unk0c - (pen_y - unk8c);
        if (vertical_align == LIB_ALIGN_CENTER)
        {
            offset /= 2.0f;
        }

        for (s32 i = 0; i < count; i++)
        {
            records->top += offset;
            records->bottom += offset;
            records++;
        }

        extent.unk04 = offset;
    }

    extent.height = pen_y - unk8c;
    extent.width = extent.width - extent.unk00;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004637A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00463C00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00463C90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00463DD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00463E60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00463FC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00464040);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004642E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00464340);

/** Character code of anything in a formatted number that isn't a digit. */
#define LIB_NUMBER_CODE_OTHER 11

/** "%d". */
extern const char D_505CF8[];

/**
 * @brief Format a number as character codes: one plus the digit for digits, 11 for anything else.
 * @param codes Receives the codes and a terminating zero.
 * @param value Number to format.
 * @return Number of codes written before the terminator.
 */
s32 LibDrawWidget::format_number_codes(u16* codes, s32 value)
{
    char text[32];
    s32 count = 0;

    sprintf_guess(text, D_505CF8, value);
    for (char* cursor = text;; count++)
    {
        u16 character = *cursor++;
        u16 code;
        // TODO: Comparing with 0L (long is 64 bits here) is the only way I've found to get the sign extension before
        // this test. My guess is the original compared the character with NULL.
        if (character == 0L)
        {
            *codes = 0;
            break;
        }

        if (character >= '0' && character <= '9')
        {
            code = character - '0' + 1;
        }
        else
        {
            code = LIB_NUMBER_CODE_OTHER;
        }

        *codes++ = code;
    }

    return count;
}

/** Record kind of a number laid out as one record. */
#define LIB_DRAW_RECORD_NUMBER 0x401C

/** Width of one digit of a number record. */
#define LIB_NUMBER_DIGIT_WIDTH 9.0f

/**
 * @brief Lay out a number as one record.
 * @param value Value stored in the record.
 * @param digits Number of digits.
 */
void LibDrawWidget::add_number_record(void* value, s32 digits)
{
    float width = LIB_NUMBER_DIGIT_WIDTH * digits;

    next_record->code = LIB_DRAW_RECORD_NUMBER;
    next_record->left = pen_x - unk88 - unk90;
    next_record->right = next_record->left + width * draw_scale;
    next_record->top = pen_y;
    next_record->bottom = next_record->top + line_height;
    next_record->unk14.scale = draw_scale_y;
    next_record->color = tint;
    next_record->unk10 = value;
    next_record->glyph = digits;
    pen_x = next_record->right + unk88 + unk90;
    next_record++;
    record_count++;
}

/**
 * @brief Close the current run of records.
 * @param value Value stored in the run's head record.
 * @param count Value stored as the run's glyph index.
 */
void LibDrawWidget::end_run(void* value, s32 count)
{
    run_head->unk10 = value;
    run_head->glyph = count;
    run_head->right = pen_x - unk88;
    run_head->bottom = run_head->top + line_height;
    run_head->unk14.end = next_record;
}

/** Record kind of a run's head record. */
#define LIB_DRAW_RECORD_RUN 0x4010

/** @brief Start a run of records at the pen position. */
void LibDrawWidget::begin_run()
{
    run_head = next_record;
    run_head->code = LIB_DRAW_RECORD_RUN;
    run_head->color = tint;
    run_head->left = pen_x;
    run_head->top = pen_y;
    next_record++;
    record_count++;
}

/** First character code past the shared font slot; higher codes index the widget's own slot. */
#define LIB_SHARED_GLYPH_COUNT 300

/**
 * @brief Lay out one glyph and advance the pen.
 * @param code Character code.
 */
void LibDrawWidget::add_glyph(s32 code)
{
    LibManagedResourceSlot* slot;
    float spacing;
    float width;
    float height;

    next_record->glyph = code - 1;
    slot = resource_slot;
    spacing = unk88;
    if (slot->flag)
    {
        if (code <= LIB_SHARED_GLYPH_COUNT)
        {
            slot = g_field_runtime->resource_slots;
            if (code == 0xE8 || code == 0xE9)
            {
                code = 0xFFFF;
            }
        }
        else
        {
            next_record->glyph -= LIB_SHARED_GLYPH_COUNT;
        }

        if ((code >= 0x94 && code <= 0x9C) || (code >= 0x43 && code < 0x4D))
        {
            pen_x -= 1.0f;
            spacing -= 1.5f;
        }
        else if (code >= 0x93 && code < 0xEA && code != 0x9D)
        {
            spacing -= 1.0f;
        }
    }

    next_record->unk10 = slot;
    next_record->code = code;
    next_record->color = tint;
    next_record->unk14.width = slot->sections[2][next_record->glyph];
    width = next_record->unk14.width * draw_scale;
    next_record->left = pen_x;
    next_record->right = pen_x + width;
    pen_x += unk90 + (width + spacing * draw_scale);
    height = slot->unk24 * draw_scale_y;
    next_record->top = pen_y;
    next_record->bottom = pen_y + height;
    line_height = height;
    if (height < min_height)
    {
        min_height = height;
    }

    if (height > max_height)
    {
        max_height = height;
    }

    next_record++;
    record_count++;
}

/** Starting smallest glyph height, above any real glyph. */
#define LIB_LAYOUT_HEIGHT_MAX 9999.0f

/**
 * @brief Start laying out records at the left edge of a line.
 * @param records First record to fill.
 * @param y Vertical pen position; zero also resets the measured extent.
 */
void LibDrawWidget::begin_layout(LibDrawRecord* records, float y)
{
    min_height = LIB_LAYOUT_HEIGHT_MAX;
    max_height = 0.0f;
    line_height = 0.0f;
    pen_x = 0.0f;
    pen_y = y;
    run_head = 0;
    next_record = records;
    record_count = 0;
    if (y == 0.0f)
    {
        extent.unk00 = LIB_LAYOUT_HEIGHT_MAX;
        extent.height = 0.0f;
        extent.width = 0.0f;
        extent.unk04 = 0.0f;
    }
}

/** Number of colours in the text palette. */
#define LIB_TEXT_PALETTE_SIZE 11

/** Text palette colours. */
extern u32 D_4ED200[LIB_TEXT_PALETTE_SIZE];

/**
 * @brief Look up one of the eleven text palette colours.
 * @param index Palette index; larger values select the last colour.
 * @return Packed colour.
 */
u32 LibDrawWidget::get_palette_color(u8 index)
{
    if (index > LIB_TEXT_PALETTE_SIZE - 1)
    {
        index = LIB_TEXT_PALETTE_SIZE - 1;
    }

    return D_4ED200[index];
}

/** Size used for a display rectangle dimension given as zero. */
#define LIB_DRAW_WIDGET_DEFAULT_EXTENT 1024.0f

/**
 * @brief Set the display rectangle; a zero width or height selects 1024.
 * @param x Left edge.
 * @param y Top edge.
 * @param width Width.
 * @param height Height.
 */
void LibDrawWidget::set_rectangle(float x, float y, float width, float height)
{
    if (width == 0.0f)
    {
        width = LIB_DRAW_WIDGET_DEFAULT_EXTENT;
    }

    if (height == 0.0f)
    {
        height = LIB_DRAW_WIDGET_DEFAULT_EXTENT;
    }

    unk18.unk00 = x;
    unk18.unk04 = y;
    unk18.unk08 = width;
    unk18.unk0c = height;
}

/** @brief Hand the drawing storage to the resident release queue. */
void LibDrawWidget::release_storage()
{
    if (allocation != 0)
    {
        resident_queue_allocation_release(g_resident_release_queues, allocation);
        allocation = 0;
    }
}

/**
 * @brief Size and allocate the drawing storage.
 * @param first First entry count.
 * @param capacity Second entry count.
 * @param second Third entry count.
 * @param third Fourth entry count.
 * @return One on success, or zero when nothing could be allocated.
 */
s32 LibDrawWidget::allocate_storage(s32 first, s32 capacity, s32 second, s32 third)
{
    s32 lines;

    unka4 = first;
    unka8 = capacity;
    unkac = second;
    unkb0 = third;
    if (capacity == 0)
    {
        lines = 0;
    }
    else
    {
        lines = (capacity - 1) / g_field_runtime->unk550 + 1;
    }

    unk48 = capacity * 128 + 160 + lines * 64;
    unk4c = (unkf8 ? 368 : 96) * (first + capacity);
    unk50 = second == 0 ? 0 : unkac * 16 + 48 + unkb0 * 80;
    allocation = new (0) u8[unk48 + unk4c + unk50 + 256];
    if (allocation == 0)
    {
        return 0;
    }

    u8* buffer = static_cast<u8*>(allocation) + DRAWING_STORAGE_PREFIX;
    aligned = reinterpret_cast<void*>((reinterpret_cast<u32>(buffer) + DRAWING_STORAGE_ALIGNMENT - 1) & ~(DRAWING_STORAGE_ALIGNMENT - 1u));
    dma_address = reinterpret_cast<u32>(aligned) | DRAWING_STORAGE_DMA_ADDRESS_TAG;
    FlushCache(0);
    return 1;
}

/** @brief Clear the storage and restore the default scale, colours and alignment. */
void LibDrawWidget::reset_drawing_state()
{
    allocation = 0;
    unk7c = 0;
    unk78 = 0;
    draw_scale_y = 1.0f;
    draw_scale = 1.0f;
    unk88 = 0.0f;
    unk8c = 2.0f;
    unk90 = 0.0f;
    tint = 0x808080;
    draw_color = 0x020202;
    horizontal_align = 0;
    vertical_align = 0;
}

/** Lowest address of drawing storage the widget owns; smaller values aren't heap allocations. */
#define LIB_DRAW_WIDGET_HEAP_ADDRESS_MIN 0x10000

/** @brief Free the drawing storage, then destroy the widget. */
LibDrawWidget::~LibDrawWidget()
{
    if (allocation != 0)
    {
        if (reinterpret_cast<u32>(allocation) >= LIB_DRAW_WIDGET_HEAP_ADDRESS_MIN)
        {
            delete[] static_cast<u8*>(allocation);
        }

        allocation = 0;
    }
}

/** @brief Initialize drawing storage, bounds, scale, colors, and display flags. */
LibDrawWidget::LibDrawWidget()
{
    extent.height = 0.0f;
    extent.width = 0.0f;
    extent.unk04 = 0.0f;
    extent.unk00 = 0.0f;
    unk38 = 10;
    unkf8 = 0;
    unkf9 = 1;
    unkfa = 0;
    allocation = 0;
    unk7c = 0;
    unk78 = 0;
    draw_scale_y = 1.0f;
    draw_scale = 1.0f;
    unk88 = 0.0f;
    unk8c = 2.0f;
    unk90 = 0;
    tint = 0x808080;
    draw_color = 0x020202;
    horizontal_align = 0;
    vertical_align = 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00464BC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00464C20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00464C80);

/** One opaque 0x50-byte resource slot in the runtime's sixteen-slot table. */
typedef struct LibNumericResourceSlot
{
    u8 bytes[0x50];
} LibNumericResourceSlot;

/** Partial runtime prefix containing the resource slot table. */
typedef struct LibNumericResourceOwner
{
    u8 pad00[0x14];
    LibNumericResourceSlot slots[16];
} LibNumericResourceOwner;

/** Partial numeric widget fields used during resource initialization. */
typedef struct LibNumericResourceState
{
    u8 pad00[0x39];
    u8 initialized;
    u8 pad3a[0x32];
    LibNumericResourceSlot* source;
    u8 pad70[0x2C];
    s32 mode;
    u8 pada0[0x58];
    u8 flag;
    u8 padf9[3];
    u32 value;
} LibNumericResourceState;


/**
 * @brief Initialize the numeric widget rectangle, resource slot, and displayed value.
 * @param object Numeric widget.
 * @param value Initial numeric value.
 * @param slot Runtime resource slot index.
 * @param flag Slot state flag.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return One when initialization succeeds, otherwise zero.
 */
extern "C" s32 lib_numeric_widget_init_rectangle(LibObject174F20* object, u32 value, s32 slot, u8 flag, float x, float y, float width, float height)
{
    LibNumericResourceState* state = (LibNumericResourceState*)object;
    state->flag = flag;
    object->set_rectangle(x, y, width, height);
    state->source = &((LibNumericResourceOwner*)g_field_runtime)->slots[slot];
    if (!object->allocate_storage(0, 16, 0, 0))
    {
        return 0;
    }
    state->value = value;
    state->mode = 2;
    state->initialized = 1;
    return 1;
}

s32 func_00464E30(void* object)
{
    return 3;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00464E40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00464EF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004650B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00465100);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00465340);

typedef struct LibResourceSlotOwner
{
    u8 pad00[0x14];
    LibManagedResourceSlot slots[16];
} LibResourceSlotOwner;

/**
 * @brief Queue the slot allocation for release and deactivate the resource slot.
 * @param manager Owner of the sixteen resource slots.
 * @param index Resource slot to release.
 */
extern "C" void lib_release_resource_slot(void* manager, s32 index)
{
    LibManagedResourceSlot* slot = &((LibResourceSlotOwner*)manager)->slots[index];
    if (slot->active)
    {
        if (slot->allocation)
        {
            resident_queue_allocation_release(g_resident_release_queues, slot->allocation);
            slot->allocation = 0;
        }
        slot->active = 0;
        FlushCache(0);
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004654A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00465520);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00465610);

/** Available transfer range in one of the runtime's sixteen resource slots. */
struct LibResourceGap {
    u8 available;
    u8 unk01[3];
    s32 start, end, size;
};
extern "C" LibManagedResourceSlot* func_004659B0(FieldRuntime*, LibResourceGap*);
extern "C" u8* func_00451C00(LibResourceHeader*, s32, s32);


extern "C" s32 lib_load_resource_slot(FieldRuntime* runtime, void* data)
{
    LibResourceHeader* source = (LibResourceHeader*)data;
    LibResourceGap gaps[16];
    LibManagedResourceSlot* slot = func_004659B0(runtime, gaps);
    s32 prefix;
    u8* remainder;
    s32 remainder_size;
    if (slot == 0)
        return 0;
    remainder = 0;
    slot->unk18 = source->unk20;
    slot->unk1c = source->unk24;
    slot->unk20 = source->unk28;
    slot->unk24 = source->unk2c;
    slot->unk28 = source->unk30;
    slot->unk2c = source->unk34;
    slot->unk30 = source->unk3c;
    slot->flag = source->unk38 != 1;
    remainder_size = 0;
    if (slot->unk18 > 0)
    {
        slot->unit_count = 1024 / slot->unk28;
        s32 required = slot->unk18 / slot->unit_count + 1;
        s32 selected = -1;
        s32 capacity = 0;
        LibResourceGap* gap = gaps;
        for (s32 i = 0; i < 16; i++, gap++)
        {
            if (gap->available)
            {
                s32 units = gap->size / slot->unk2c;
                if (capacity < required)
                {
                    if (capacity < units)
                    {
                        capacity = units;
                        selected = i;
                    }
                }
                else if (units >= required && units < capacity)
                {
                    capacity = units;
                    selected = i;
                }
            }
        }
        if (selected >= 0)
        {
            prefix = source->offsets[3];
            slot->start = gaps[selected].start;
            if (capacity >= required)
            {
                slot->loaded = source->unk20;
                slot->loaded_units = required;
                slot->unk48 = 0;
                func_00451C00(source, slot->start, slot->loaded);
            }
            else
            {
                slot->loaded = slot->unit_count * capacity;
                slot->loaded_units = capacity;
                slot->unk48 = slot->unk18 - slot->loaded;
                remainder = func_00451C00(source, slot->start, slot->loaded);
                remainder_size = source->size - (remainder - (u8*)source);
            }
            slot->end = slot->start + slot->unk2c * slot->loaded_units;
        }
        else
        {
            prefix = source->size;
            slot->loaded = 0;
            slot->unk48 = slot->unk18;
        }
    }
    else
    {
        prefix = source->size;
        slot->unk48 = 0;
        slot->loaded = 0;
    }
    u8* allocation = new (0) u8[prefix + remainder_size + 128];
    if (allocation == 0)
        return 0;
    source = (LibResourceHeader*)RESIDENT_ALIGN_RESOURCE(allocation);
    memcpy_guess(source, data, prefix);
    if (remainder_size != 0)
        memcpy_guess((u8*)source + prefix, remainder, remainder_size);
    slot->allocation = allocation;
    slot->data = source;
    slot->sections[0] = (u8*)source + source->offsets[0];
    slot->sections[1] = (u8*)source + source->offsets[1];
    slot->sections[2] = (u8*)source + source->offsets[2];
    slot->sections[3] = (u8*)source + source->offsets[3];
    slot->active = 1;
    FlushCache(0);
    return slot->identifier;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004659B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00465A90);

/**
 * @brief Append a transform receiver to the runtime display queue.
 * @param runtime Runtime manager.
 * @param object Transform receiver.
 * @return One when queued, or zero if the receiver already has an owner.
 */
extern "C" s32 lib_queue_display_object(FieldRuntime* runtime, LibTransformOwner* object)
{
    LibRuntimeListState* list = (LibRuntimeListState*)runtime;
    LibRuntimeListNode* node = (LibRuntimeListNode*)object;
    if (node->owner)
    {
        return 0;
    }
    node->owner = runtime;
    if (!list->first)
    {
        list->last = node;
        list->first = node;
        node->previous = 0;
        node->next = 0;
    }
    else
    {
        LibRuntimeListNode* last = list->last;
        last->next = node;
        node->previous = last;
        node->next = 0;
        list->last = node;
    }
    list->count++;
    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00465B90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00465DC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00465E00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00465F20);

void func_004662A0(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004662B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00466440);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004664E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00466AD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00466E30);

/**
 * @brief Set the movement target and reset its completion flags.
 * @param x Target horizontal coordinate.
 * @param y Target vertical coordinate.
 * @param duration Duration in seconds, converted to sixty frames per second.
 */
void ItemCreationClass185050::set_move_target(float x, float y, float duration)
{
    target.x = x;
    target.y = y;
    move_frames = 60.0f * duration;
    speed_ready = 0;
    arrived = 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00466E70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004670B0);

/**
 * @brief Allocate the drawing storage and show the state at a position at full alpha.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @return One on success, or zero when the storage couldn't be allocated.
 */
s32 ItemCreationClass185050::init_position(float x, float y)
{
    if (!lib_allocate_drawing_storage(&unk00, 0x12))
    {
        return 0;
    }

    position.x = x;
    position.y = y;
    alpha = 128.0f;
    speed_ready = 0;
    arrived = 1;
    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004672C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00467320);

typedef struct LibFieldWidgetState
{
    u8 pad00[0x34];
    u32 unk34;
    u8 pad38;
    u8 unk39;
    u8 pad3a[6];
    LibMovementState movement;
} LibFieldWidgetState;
/**
 * @brief Initialize the moving widget storage and position, then set its drawing flags.
 * @param object Moving widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @return One on success, or zero when storage initialization fails.
 */
extern "C" s32 lib_moving_widget_init_position(LibClass175030* object, float x, float y)
{
    LibFieldWidgetState* state = (LibFieldWidgetState*)object;
    if (!state->movement.init_position(x, y))
    {
        return 0;
    }
    state->unk34 = 8;
    state->unk39 = 1;
    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004673B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004673C0);

/**
 * @brief Finish the cursor's drawing packet.
 * @param value Notification word.
 */
void LibSelectionCursor::on_packet_complete(u32 value)
{
    lib_finish_packet(this);
}

struct N54Owner64_0045AD10 { u8 pad00[0x64]; u8 active; };

void func_004674A0(N54Owner64_0045AD10* object)
{
    object->active = 1;
    void* adjusted = object;
    if (object != 0)
    {
        adjusted = (u8*)adjusted + 0x90;
    }
    func_00461830((u8*)object + 0xB0, adjusted);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004674E0);

/**
 * @brief Reset the translation, set the drawing codes and depth, and place the cursor.
 * @param code Drawing code.
 * @param first First drawing value.
 * @param second Second drawing value.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param z Depth.
 */
void LibSelectionCursor::init(s32 code, u32 first, u32 second, float x, float y, float z)
{
    translation.x = 0.0f;
    translation.y = 0.0f;
    translation.z = 0.0f;
    translation.w = 1.0f;
    set_codes_and_z(code, first, z, second, 0);
    init_position(x, y);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004675E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004675F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00467600);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00467670);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00467750);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00467800);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004678F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00467950);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004679B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004679D0);

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
s32 LibStringLabel::init_text_rectangle(float x, float y, float width, float height, const char* value, u8 flag)
{
    unkf8 = flag;
    set_rectangle(x, y, width, height);
    resource_slot = g_field_runtime->resource_slots;

    if (!allocate_storage(32, 0, 0, 0))
    {
        return 0;
    }

    text = value;
    unk39 = 1;
    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00467B50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00467BC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004680B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00468230);

s32 func_00468360(void* object)
{
    return 7;
}

s32 func_00468370(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00468380);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004683A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004683E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00468590);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00468900);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00468AA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00468B70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00468DB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00468E50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00469180);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00469970);

void func_0046A3B0(void* receiver)
{
    u8* object = (u8*)receiver;
    *(u8*)(object + 0x64) = 1;
    *(volatile u32*)0x10009020 = 0;
    *(volatile u32*)0x10009030 = *(u32*)(object + 0x610);
    *(volatile u32*)0x1000E010 = 2;
    *(volatile u32*)0x10009000 = 0x105;
}

/** Forward the receiver to lib_finish_packet. */
void func_0046A3F0(void* object)
{
    lib_finish_packet(static_cast<LibTransformOwner*>(object));
}

/** Queue the DMA submission embedded at offset 0x5a0 when present. */
s32 func_0046A410(void* object)
{
    DmaSubmission* submission = reinterpret_cast<DmaSubmission*>(object);
    if (object != 0)
    {
        submission = (DmaSubmission*)((u8*)submission + 0x5a0);
    }
    return func_00114100(g_vif1_dma_queue, submission);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0046A440);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0046AAC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0046AB80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0046AC10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0046ACC0);
