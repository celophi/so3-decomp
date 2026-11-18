#include "include_asm.h"
#include "overlays/lib/text_00419A70.h"
#include "main/resident_data.h"
#include "sdk/main/libkernl_00121940.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_0044ABE0.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "overlays/lib/render_buffer.h"
#include "overlays/lib/character_names.h"
#include "overlays/lib/text_004DD440.h"
#include "overlays/lib/text_0046AE20.h"
#include "overlays/lib/widget_aggregate.h"
#include "overlays/lib/text_004095C0.h"

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

/**
 * @brief Return a shape's record at an offset from its first record.
 * @param shape Shape descriptor.
 * @param records Record array of the shape data.
 * @param offset Record offset from the shape's first record.
 * @return The record, or null when the shape has no records.
 */
static inline FieldShapeRecord20* shape_record_at(FieldShapeOwner18* shape, FieldShapeRecord20* records, s32 offset)
{
    return shape->unk0e == -1 ? 0 : &records[shape->unk0e + offset];
}

/**
 * @brief Count the children of a shape.
 * @param shape Shape descriptor.
 * @return Number of child shapes.
 */
static inline s32 shape_child_count(FieldShapeOwner18* shape)
{
    s32 count = 0;
    FieldShapeOwner18* child = shape->unk00;

    if (child == 0)
    {
        return 0;
    }

    for (;;)
    {
        count++;

        if (child->is_last())
        {
            break;
        }

        child++;
    }

    return count;
}

/**
 * @brief Return one child of a shape.
 * @param shape Shape descriptor.
 * @param index Child index.
 * @return The child, or null when the shape has fewer children.
 */
static inline FieldShapeOwner18* shape_child_at(FieldShapeOwner18* shape, s32 index)
{
    FieldShapeOwner18* child = shape->unk00;

    if (child == 0)
    {
        return 0;
    }

    while (child)
    {
        if (--index < 0)
        {
            return child;
        }

        if (child->is_last())
        {
            return 0;
        }

        child++;
    }

    return child;
}

/**
 * @brief Find a record of the shape with the given name in bound shape data.
 * @param storage Shape resource storage.
 * @param name Shape name, compared over sixteen characters.
 * @param offset Record offset from the shape's first record.
 * @return The record, or null when the data is not bound, no shape has the name or the shape has no records.
 */
FieldShapeRecord20* func_0045AE10(FieldClass1515D0* storage, const char* name, s32 offset)
{
    FieldShapeData30* data = storage->unk00;

    if (!(data->prefix.flags & LIB_SHAPE_DATA_BOUND))
    {
        return 0;
    }

    FieldShapeOwner18* shape = reinterpret_cast<FieldShapeOwner18*>(data + 1);
    FieldShapeRecord20* records = data->prefix.unk0c;
    s32 count = data->prefix.shape_count;

    for (s32 i = 0; i < count; i++)
    {
        if (lib_compare_bounded_strings(name, reinterpret_cast<const char*>(&storage->unk00->prefix.unk08[shape->unk0c].unk04),
                                        LIB_SHAPE_NAME_LENGTH) == 0)
        {
            return shape_record_at(shape, records, offset);
        }

        shape++;
    }

    return 0;
}

/**
 * @brief Set the flag of the record with the given identifier, searching a sibling run of shapes and their children.
 * @param storage Shape resource storage.
 * @param shape First shape of the sibling run.
 * @param id Record identifier.
 * @param flag New flag value.
 */
void func_0045AF10(FieldClass1515D0* storage, FieldShapeOwner18* shape, u16 id, s32 flag)
{
    FieldShapeRecord20* records = storage->unk00->prefix.unk0c;

    while (shape)
    {
        if (shape->unk0e != -1)
        {
            FieldShapeRecord20* record = &records[shape->unk0e];

            for (;;)
            {
                FieldShapeRecordInfo* info = &record->unk0c;

                if (record->unk0c.unk02 == id)
                {
                    info->unk00_4 = flag;
                    return;
                }

                if (info->unk00_5)
                {
                    break;
                }

                record++;
            }
        }

        s32 count = shape_child_count(shape);

        for (s32 i = 0; i < count; i++)
        {
            func_0045AF10(storage, shape_child_at(shape, i), id, flag);
        }

        if (shape->is_last())
        {
            return;
        }

        shape++;
    }
}

/**
 * @brief Set the flag of the record with the given identifier anywhere in the shape data.
 * @param storage Shape resource storage.
 * @param id Record identifier.
 * @param flag New flag value.
 */
void func_0045B0E0(FieldClass1515D0* storage, s32 id, s32 flag)
{
    func_0045AF10(storage, reinterpret_cast<FieldShapeOwner18*>(storage->unk00 + 1), id, flag);
}

/**
 * @brief Bind shape data: turn its offsets into pointers once and look up each shape's transform by name.
 * @param storage Shape resource storage.
 * @param manager Entry table searched for the shape names.
 */
void func_0045B110(FieldClass1515D0* storage, LibScene* manager)
{
    if (!(storage->unk00->prefix.flags & LIB_SHAPE_DATA_BOUND))
    {
        storage->unk00->prefix.unk08 =
            reinterpret_cast<FieldShapeEntry14*>(reinterpret_cast<u8*>(storage->unk00) + reinterpret_cast<s32>(storage->unk00->prefix.unk08));
        storage->unk00->prefix.unk0c =
            reinterpret_cast<FieldShapeRecord20*>(reinterpret_cast<u8*>(storage->unk00) + reinterpret_cast<s32>(storage->unk00->prefix.unk0c));
    }

    FieldShapeOwner18* shape = reinterpret_cast<FieldShapeOwner18*>(storage->unk00 + 1);
    s32 count = storage->unk00->prefix.shape_count;

    for (s32 i = 0; i < count; i++)
    {
        if (!(storage->unk00->prefix.flags & LIB_SHAPE_DATA_BOUND) && shape->unk00)
        {
            shape->unk00 = reinterpret_cast<FieldShapeOwner18*>(reinterpret_cast<u8*>(storage->unk00) + reinterpret_cast<s32>(shape->unk00));
        }

        shape->unk04 = static_cast<LibTransformOwner*>(
            lib_find_named_entry_cached(manager, reinterpret_cast<const char*>(&storage->unk00->prefix.unk08[shape->unk0c].unk04), 0));
        shape++;
    }

    storage->unk00->prefix.flags |= LIB_SHAPE_DATA_BOUND;
}

/**
 * @brief Bind shape storage to a resource, freeing the previous one unless it was borrowed, and find its attribute
 *        chunk.
 * @param storage Shape resource storage.
 * @param resource Resource chunks; the storage borrows them.
 * @return One when an attribute chunk was found, otherwise zero.
 */
s32 func_0045B210(FieldClass1515D0* storage, void* resource)
{
    if (!storage->unk08)
    {
        ::operator delete(storage->unk04);
    }

    storage->unk08 = 1;
    storage->unk04 = resource;
    LibResourceChunkHeader* chunk = static_cast<LibResourceChunkHeader*>(resource);

    for (;;)
    {
        if (chunk->magic == LIB_SHAPE_ATTRIBUTE_MAGIC)
        {
            break;
        }

        chunk = lib_next_chunk(chunk);

        if (chunk == 0)
        {
            return 0;
        }
    }

    storage->unk00 = reinterpret_cast<FieldShapeData30*>(chunk + 1);
    return 1;
}

/**
 * @brief Return one child of a shape.
 * @param shape Shape descriptor.
 * @param index Child index.
 * @return The child, or null when the shape has fewer children.
 */
FieldShapeOwner18* func_0045B2B0(FieldShapeOwner18* shape, s32 index)
{
    return shape_child_at(shape, index);
}

/**
 * @brief Count the children of a shape.
 * @param shape Shape descriptor.
 * @return Number of child shapes.
 */
s32 func_0045B320(FieldShapeOwner18* shape)
{
    return shape_child_count(shape);
}

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

/**
 * @brief Clip a ray's fraction interval against one slab plane.
 * @param near_fraction Entry fraction, raised when the plane cuts the start of the interval.
 * @param far_fraction Exit fraction, lowered when the plane cuts the end of the interval.
 * @param direction Ray direction along the slab axis.
 * @param distance Signed distance from the ray start to the plane along the axis.
 * @return One while the interval is not empty, otherwise zero.
 */
extern "C" s32 func_0045C350(float* near_fraction, float* far_fraction, float direction, float distance)
{
    if (direction > 0.0f)
    {
        if (distance > direction * *far_fraction)
        {
            return 0;
        }

        if (distance > direction * *near_fraction)
        {
            *near_fraction = distance / direction;
        }

        return 1;
    }

    if (direction < 0.0f)
    {
        if (distance > direction * *near_fraction)
        {
            return 0;
        }

        if (distance > direction * *far_fraction)
        {
            *far_fraction = distance / direction;
        }

        return 1;
    }

    s32 result = 1;

    if (!(distance <= 0.0f))
    {
        result = 0;
    }

    return result;
}

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

/**
 * @brief Publish the two bound shape record arrays for subsequent predicates.
 * @param first First shape resource storage.
 * @param second Second shape resource storage.
 */
void func_0045F580(void* first, void* second)
{
    D_001B656C = (struct FieldShapeRecord20*)*(void**)(*(u8**)first + 0xC);
    D_001B6570 = (struct FieldShapeRecord20*)*(void**)(*(u8**)second + 0xC);
}

/**
 * @brief Run func_0045EBD0 on the objects referenced by the first words of two objects.
 *
 * The word at offset 0xC of each referenced object is stored in a global first.
 * @param object Object whose first word refers to the first tested object.
 * @param other Object whose first word refers to the second tested object.
 * @return The func_0045EBD0 result.
 */
s32 func_0045F5A0(void* object, void* other)
{
    u8* first = *(u8**)object;
    u8* second = *(u8**)other + 0x30;
    D_001B656C = (struct FieldShapeRecord20*)*(void**)(first + 0xC);
    D_001B6570 = (struct FieldShapeRecord20*)*(void**)(*(u8**)other + 0xC);
    return func_0045EBD0(first + 0x30, second);
}

/** Matrix func_0045F5E0 resets. */
extern "C" LibMatrix44Value D_0050CAF0;

/** @brief Reset D_0050CAF0 to the identity matrix. */
extern "C" void func_0045F5E0()
{
    D_0050CAF0.set_identity();
}

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

/** @brief Draw the laid-out records once, then finish the text widget's drawing. */
void LibObject174D90::draw()
{
    if (!unk3b)
    {
        s32 count = (u32)(unk74 - unk70) / sizeof(LibDrawRecord);

        if (count > 0)
        {
            draw_records(reinterpret_cast<LibDrawRecord*>(unk70), count);
            func_004C7010();
            unk3b = 1;
        }
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045F710);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045FE90);

/**
 * @brief Work out the extra spacing that spreads a run of draw records to the widget's width.
 * @param widget Widget whose width the run should fill.
 * @param first First record of the run.
 * @param last Last record of the run.
 * @return Extra spacing per glyph record, at most three, or zero when the run already fills the width.
 */
extern "C" float func_004601F0(LibDrawWidget* widget, LibDrawRecord* first, LibDrawRecord* last)
{
    float spacing = 0.0f;
    s32 count = 0;
    float right = 0.0f;

    for (LibDrawRecord* record = first; record <= last; record++)
    {
        if (!(record->code & 0x4000))
        {
            right = record->right;
            count++;
        }
        else if (record->code == 0x401C)
        {
            right = record->right;
        }
    }

    if (right > 0.0f && count > 0)
    {
        float extra = widget->unk18.unk08 - right;

        if (extra > 0.0f)
        {
            spacing = extra / count;

            if (spacing > 3.0f)
            {
                spacing = 3.0f;
            }
        }
    }

    return spacing;
}

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

/** @brief Release the multiline allocation and destroy the text widget. */
LibObject174D90::~LibObject174D90()
{
    if (unk70 != 0)
    {
        delete[] unk70;
        unk70 = 0;
    }
}

/**
 * @brief Queue an embedded packet's data for sending, with a DMA submission to call when it's done.
 * @param embedded Packet embedded in its owner.
 * @param adjusted Owner's DMA submission, or null.
 */
extern "C" void func_00461830(void* embedded, void* adjusted)
{
    func_004DC4F0(g_packet_queue, 3, 0, static_cast<ResidentPacket*>(embedded)->unk04, 0, adjusted);
}

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

#define LIB_MESSAGE_WINDOW_STATE_WAIT 4
#define LIB_MESSAGE_WINDOW_STATE_WAIT_END 6
#define LIB_MESSAGE_WINDOW_STATE_LOAD 2
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

/** @brief Destroy the text. */
LibMessageWindowText::~LibMessageWindowText()
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004622F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00462300);

void LibWidget::draw()
{
}

/**
 * @brief Draw laid-out records: runs and numbers by their own routines, glyphs by the glyph routine, other
 *        control records not at all.
 * @param records Records to draw.
 * @param count Number of records.
 */
void LibDrawWidget::draw_records(LibDrawRecord* records, s32 count)
{
    func_00463500(records, count);

    for (s32 i = 0; i < count; i++, records++)
    {
        if (records->code == LIB_DRAW_RECORD_RUN)
        {
            func_00462FC0(records);
        }
        else if (records->code == LIB_DRAW_RECORD_NUMBER)
        {
            func_00462C70(records);
        }
        else if (!(records->code & LIB_DRAW_RECORD_CONTROL))
        {
            func_004624E0(records);
        }
    }

    func_004623F0();
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004623F0__13LibDrawWidgetFv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004624E0__13LibDrawWidgetFP13LibDrawRecord);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00462C70__13LibDrawWidgetFP13LibDrawRecord);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00462FC0__13LibDrawWidgetFP13LibDrawRecord);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00463500__13LibDrawWidgetFP13LibDrawRecordi);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004637A0__13LibDrawWidgetFP13LibDrawRecordi);

extern "C" s32 func_00463C90(LibDrawWidget* widget, u16* codes, u16 id, s32 variant);

extern "C" s32 func_00463E60(LibDrawWidget* widget, u16* codes, u16 id, s32 variant);

/**
 * @brief Lay out the text for a 16-bit ID glyph by glyph.
 * @param widget Widget to lay out into.
 * @param id ID passed to the code lookup.
 * @param variant Second lookup argument.
 */
extern "C" void func_00463C00(LibDrawWidget* widget, u16 id, s32 variant)
{
    u16 codes[0x80];
    s32 count = func_00463C90(widget, codes, id, variant);

    if (count > 0)
    {
        u16* code = codes;

        for (s32 i = 0; i < count; i++)
        {
            widget->add_glyph(*code++);
        }
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00463C90);

/**
 * @brief Lay out the text for a 16-bit ID glyph by glyph.
 * @param widget Widget to lay out into.
 * @param id ID passed to the code lookup.
 * @param variant Second lookup argument.
 */
extern "C" void func_00463DD0(LibDrawWidget* widget, u16 id, s32 variant)
{
    u16 codes[0x80];
    s32 count = func_00463E60(widget, codes, id, variant);

    if (count > 0)
    {
        u16* code = codes;

        for (s32 i = 0; i < count; i++)
        {
            widget->add_glyph(*code++);
        }
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00463E60);

extern "C" s32 func_00464040(LibDrawWidget* widget, u16* codes, const char* text);

/**
 * @brief Lay out text glyph by glyph.
 * @param text Text to lay out.
 */
void LibDrawWidget::add_text(const char* text)
{
    u16 codes[0x80];
    s32 count = func_00464040(this, codes, text);

    if (count > 0)
    {
        u16* code = codes;

        for (s32 i = 0; i < count; i++)
        {
            add_glyph(*code++);
        }
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00464040);

/**
 * @brief Text code callback: the name of party slot `index`.
 * @param context Text layout context; unused.
 * @param index One-based character slot, 1 through 10.
 * @return Name, or null for an out-of-range slot or with no name provider.
 */
extern "C" char* func_004642E0(void* context, s32 index)
{
    if (index <= 0 || index > 10)
    {
        return 0;
    }

    if (g_field_runtime->character_names == 0)
    {
        return 0;
    }

    return g_field_runtime->character_names->get_character_name(index);
}

/**
 * @brief Lay out a number glyph by glyph.
 * @param value Number to lay out.
 */
void LibDrawWidget::add_number(s32 value)
{
    u16 codes[0x80];
    s32 count = format_number_codes(codes, value);
    u16* code = codes;

    for (s32 i = 0; i < count; i++)
    {
        add_glyph(*code++);
    }
}

#define LIB_NUMBER_CODE_OTHER 11

/** "%d". */
extern const char D_00505CF8[];

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

    sprintf_guess(text, D_00505CF8, value);

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

#define LIB_TEXT_PALETTE_SIZE 11

/** Text palette colours. */
extern u32 D_004ED200[LIB_TEXT_PALETTE_SIZE];

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

    return D_004ED200[index];
}

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

/** @brief Destroy the widget. */
LibObject174F20::~LibObject174F20()
{
}

/**
 * @brief Lay the numeric widget's number out off screen and measure it.
 * @param object Numeric widget to measure.
 * @return Extent of the laid-out number.
 */
LibTextExtent* func_00464C20(LibObject174F20* object)
{
    LibDrawRecord records[0x40];
    object->begin_layout(records, 0.0f);
    object->add_number(object->numeric_value);
    object->func_004637A0(records, object->record_count);
    object->align_records_vertically(records, object->record_count);
    return &object->extent;
}

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

/**
 * @brief Return the list kind the runtime is queued under.
 * @return Three.
 */
s32 FieldRuntime::get_default_list_kind()
{
    return 3;
}

/**
 * @brief Copy both pads' held, pressed and repeated buttons into the runtime, or clear them while time is stopped.
 * @param runtime Field runtime.
 */
extern "C" void func_00464E40(FieldRuntime* runtime)
{
    if (runtime->rate != 0.0f)
    {
        ResidentInputSystem* input = g_input_system;
        FieldRuntime::Input* entry = runtime->inputs;

        for (s32 slot = 0; slot < 2; slot++, entry++)
        {
            entry->unk00 = resident_pad_get_held(input, slot);
            entry->unk02 = resident_pad_get_pressed(input, slot);
            entry->unk04 = resident_pad_get_repeated(input, slot);
        }
    }
    else
    {
        memset_guess(runtime->inputs, 0, sizeof(runtime->inputs));
    }
}

extern "C" const u16 D_004ED2D0[16];

/**
 * @brief Turn a button glyph code into the glyph of the pad button the player has mapped to it.
 * @param runtime Runtime holding the button map.
 * @param code Glyph code; 0x20-0x27 and 0x30-0x37 name the eight mapped actions in two glyph styles.
 * @return Codes below 0x20 unchanged; otherwise the mapped button's index in the first style or index + 0x10 in the
 *         second, or 0x20 when the code or its button isn't known.
 */
extern "C" s32 func_00464EF0(FieldRuntime* runtime, s32 code)
{
    s32 result;

    if (code < 0x20)
    {
        result = code;
    }
    else if (code < 0x40)
    {
        u16 button;

        switch (code)
        {
        case 0x20:
        case 0x30:
            button = runtime->button_map->buttons[0];
            break;

        case 0x21:
        case 0x31:
            button = runtime->button_map->buttons[1];
            break;

        case 0x22:
        case 0x32:
            button = runtime->button_map->buttons[2];
            break;

        case 0x23:
        case 0x33:
            button = runtime->button_map->buttons[3];
            break;

        case 0x24:
        case 0x34:
            button = runtime->button_map->buttons[4];
            break;

        case 0x25:
        case 0x35:
            button = runtime->button_map->buttons[5];
            break;

        case 0x26:
        case 0x36:
            button = runtime->button_map->buttons[6];
            break;

        case 0x27:
        case 0x37:
            button = runtime->button_map->buttons[7];
            break;
        }

        const u16* entry = D_004ED2D0;
        s32 index;

        for (index = 0; index < 16; index++, entry++)
        {
            if (*entry == button)
            {
                break;
            }
        }

        if (index < 16)
        {
            if (code < 0x30)
            {
                result = index;
            }
            else
            {
                result = index + 0x10;
            }
        }
        else
        {
            result = 0x20;
        }
    }
    else
    {
        result = 0x20;
    }

    return result;
}

/**
 * @brief Find one of the field runtime's display chunks.
 * @param runtime Field runtime.
 * @param index Chunk index.
 * @return Chunk, or null when the list is shorter.
 */
extern "C" LibResourceChunkHeader* func_004650B0(FieldRuntime* runtime, s32 index)
{
    LibResourceChunkHeader* chunk = static_cast<LibResourceChunkHeader*>(runtime->display_chunks);

    for (s32 i = 0;; i++)
    {
        if (i == index)
        {
            return chunk;
        }

        chunk = chunk->next_offset == 0 ? 0 : reinterpret_cast<LibResourceChunkHeader*>(reinterpret_cast<u8*>(chunk) + chunk->next_offset);

        if (!chunk)
        {
            break;
        }
    }

    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00465100);

/** One entry of a resource slot's key index: a key and the offset of its data in the second section. */
struct LibResourceIndexEntry
{
    s32 key;
    s32 offset;
};

extern "C" u8 D_00505D00[];

/**
 * @brief Look a key up in a resource slot's sorted index by halving steps.
 * @param runtime Runtime that owns the slot table.
 * @param slot_index Resource slot index.
 * @param key Key to find.
 * @return The key's data in the slot's second section, or the placeholder text at D_00505D00 when it isn't there.
 */
extern "C" void* func_00465340(FieldRuntime* runtime, s32 slot_index, s32 key)
{
    void* result = D_00505D00;
    LibManagedResourceSlot* slot = &runtime->resource_slots[slot_index];
    LibResourceIndexEntry* table = reinterpret_cast<LibResourceIndexEntry*>(slot->sections[0]);
    s32 step = slot->unk30;
    LibResourceIndexEntry* end = table + step;
    step /= 2;
    LibResourceIndexEntry* entry = table + step;
    LibResourceIndexEntry* previous = 0;

    for (;;)
    {
        if (key == entry->key)
        {
            result = slot->sections[1] + entry->offset;
            break;
        }

        if (step >= 2)
        {
            step /= 2;
        }

        LibResourceIndexEntry* next;

        if (entry->key < key)
        {
            next = entry + step;

            if (next >= end)
            {
                break;
            }
        }
        else
        {
            next = entry - step;

            if (next < table)
            {
                break;
            }
        }

        if (next == previous)
        {
            break;
        }

        previous = entry;
        entry = next;
    }

    return result;
}

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

extern "C" void func_00465610(void* manager, LibManagedResourceSlot* slot, void* data, void* allocation);

/**
 * @brief Find the first inactive resource slot.
 * @param manager Owner of the sixteen resource slots.
 * @return Slot, or null when all are active.
 */
static inline LibManagedResourceSlot* find_free_resource_slot(void* manager)
{
    LibManagedResourceSlot* slot = ((LibResourceSlotOwner*)manager)->slots;

    for (s32 i = 0; i < 16; i++, slot++)
    {
        if (!slot->active)
        {
            return slot;
        }
    }

    return 0;
}

/**
 * @brief Put resource data that's already in memory into a free resource slot.
 * @param manager Owner of the sixteen resource slots.
 * @param data Resource data.
 * @return The slot's identifier, or zero when no slot is free.
 */
extern "C" u16 func_004654A0(void* manager, void* data)
{
    LibManagedResourceSlot* slot = find_free_resource_slot(manager);

    if (!slot)
    {
        return 0;
    }

    func_00465610(manager, slot, data, 0);
    FlushCache(0);
    return slot->identifier;
}

/**
 * @brief Copy a resource into a new 128-byte aligned allocation and bind a free resource slot to the copy.
 * @param manager Runtime that owns the slot table.
 * @param data Resource to copy.
 * @return The slot's identifier, or zero when no slot is free or the allocation fails.
 */
extern "C" u16 func_00465520(void* manager, void* data)
{
    LibManagedResourceSlot* slot = find_free_resource_slot(manager);

    if (!slot)
    {
        return 0;
    }

    LibResourceHeader* header = static_cast<LibResourceHeader*>(data);
    u8* allocation = new (0) u8[header->size + 128];

    if (!allocation)
    {
        return 0;
    }

    void* aligned = reinterpret_cast<void*>((reinterpret_cast<u32>(allocation) + 127) & ~127);
    memcpy_guess(aligned, header, header->size);
    func_00465610(manager, slot, aligned, allocation);
    FlushCache(0);
    return slot->identifier;
}

/**
 * @brief Bind a resource slot to a resource: resolve its four section offsets and copy its header values.
 * @param manager Runtime that owns the slot table; unused.
 * @param slot Slot to fill.
 * @param data Resource header.
 * @param allocation Allocation that holds the resource when the slot owns it, otherwise null.
 */
extern "C" void func_00465610(void* manager, LibManagedResourceSlot* slot, void* data, void* allocation)
{
    LibResourceHeader* header = static_cast<LibResourceHeader*>(data);
    slot->allocation = allocation;
    slot->data = header;
    slot->sections[0] = reinterpret_cast<u8*>(header) + header->offsets[0];
    slot->sections[1] = reinterpret_cast<u8*>(header) + header->offsets[1];
    slot->sections[2] = reinterpret_cast<u8*>(header) + header->offsets[2];
    slot->sections[3] = reinterpret_cast<u8*>(header) + header->offsets[3];
    slot->unk18 = header->unk20;
    slot->unk1c = header->unk24;
    slot->unk20 = header->unk28;
    slot->unk24 = header->unk2c;
    slot->unk28 = header->unk30;
    slot->unk2c = header->unk34;
    slot->unk30 = header->unk3c;
    slot->loaded = 0;
    slot->unk48 = header->unk20;
    slot->flag = header->unk38 != 1;
    slot->active = 1;
}

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

/**
 * @brief List the free space after each loaded resource slot and find a free slot.
 * @param runtime Runtime that owns the slot table.
 * @param gaps Sixteen entries, one per slot; each receives the gap between its slot's end and the next loaded
 *             slot's start (or the end of the resource area) and is marked available when the gap is not empty.
 * @return The first inactive slot, or null when every slot is active.
 */
extern "C" LibManagedResourceSlot* func_004659B0(FieldRuntime* runtime, LibResourceGap* gaps)
{
    LibManagedResourceSlot* free_slot = 0;
    LibManagedResourceSlot* slot = runtime->resource_slots;

    for (s32 i = 0; i < 16; i++, slot++, gaps++)
    {
        gaps->available = 0;

        if (slot->active)
        {
            if (slot->loaded > 0)
            {
                s32 start = slot->end;
                s32 end = runtime->resource_area_end;
                LibManagedResourceSlot* other = runtime->resource_slots;

                for (s32 j = 0; j < 16; j++, other++)
                {
                    if (other->active && other->loaded > 0)
                    {
                        s32 other_start = other->start;

                        if (other_start >= start && other_start < end)
                        {
                            end = other_start;
                        }
                    }
                }

                if (start != end)
                {
                    gaps->start = start;
                    gaps->end = end;
                    gaps->size = end - start;
                    gaps->available = 1;
                }
            }
        }
        else if (!free_slot)
        {
            free_slot = slot;
        }
    }

    return free_slot;
}

/**
 * @brief Remove a transform receiver from the runtime display queue and detach it from its update list.
 * @param runtime Runtime manager.
 * @param object Transform receiver.
 * @return One when it was queued, otherwise zero.
 */
extern "C" s32 func_00465A90(FieldRuntime* runtime, LibTransformOwner* object)
{
    LibRuntimeListState* list = (LibRuntimeListState*)runtime;
    LibRuntimeListNode* node = (LibRuntimeListNode*)object;

    if (!node->owner)
    {
        return 0;
    }

    node->owner = 0;
    LibRuntimeListNode* previous = node->previous;
    LibRuntimeListNode* next = node->next;

    if (!previous)
    {
        list->first = next;
    }
    else
    {
        previous->next = next;
    }

    if (!next)
    {
        list->last = previous;
    }
    else
    {
        next->previous = previous;
    }

    if (object->owner)
    {
        lib_object_detach_owner(object);
    }

    list->count--;
    return 1;
}

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

/** One queued display object with the keys FieldRuntime::update sorts by. */
struct FieldDisplayEntry
{
    LibCallbackTransform* object;
    s32 order;
    s32 unk08;
    s32 priority;
};

/** @brief Hand the queued display objects to the renderer, ordered by priority and then by their order value. */
void FieldRuntime::update()
{
    if (display_count <= 0)
    {
        return;
    }

    FieldDisplayEntry entries[256];
    LibCallbackTransform* object = static_cast<LibCallbackTransform*>(display_first);
    FieldDisplayEntry* entry = entries;

    for (; object; object = reinterpret_cast<LibCallbackTransform*>(reinterpret_cast<LibRuntimeListNode*>(object)->next))
    {
        if (object->owner)
        {
            lib_object_detach_owner(object);
        }

        entry->object = object;
        entry->order = object->unka4;
        entry->unk08 = object->unka0;
        entry->priority = object->unka9;
        entry++;
    }

    if (display_count >= 2)
    {
        for (s32 i = 0; i < display_count - 1; i++)
        {
            s32 j = display_count - 1;
            FieldDisplayEntry* current = &entries[j];
            FieldDisplayEntry* previous = current - 1;

            for (; j > i; j--, current--, previous--)
            {
                if (current->order < previous->order)
                {
                    LibCallbackTransform* first = previous->object;
                    s32 order = previous->order;
                    s32 unk08 = previous->unk08;
                    s32 priority = previous->priority;
                    previous->object = current->object;
                    previous->order = current->order;
                    previous->unk08 = current->unk08;
                    previous->priority = current->priority;
                    current->object = first;
                    current->order = order;
                    current->unk08 = unk08;
                    current->priority = priority;
                }
            }
        }

        for (s32 i = 0; i < display_count - 1; i++)
        {
            s32 j = display_count - 1;
            FieldDisplayEntry* current = &entries[j];
            FieldDisplayEntry* previous = current - 1;

            for (; j > i; j--, current--, previous--)
            {
                if (previous->priority < current->priority)
                {
                    LibCallbackTransform* first = previous->object;
                    s32 order = previous->order;
                    s32 unk08 = previous->unk08;
                    s32 priority = previous->priority;
                    previous->object = current->object;
                    previous->order = current->order;
                    previous->unk08 = current->unk08;
                    previous->priority = current->priority;
                    current->object = first;
                    current->order = order;
                    current->unk08 = unk08;
                    current->priority = priority;
                }
            }
        }
    }

    FieldDisplayEntry* queued = entries;

    for (s32 i = 0; i < display_count; i++, queued++)
    {
        static_cast<LibUpdateList*>(g_renderer)->append_node(queued->object, -1);
    }
}

/** @brief Hand the runtime to the release queues once, so it's deleted after the frame. */
void FieldRuntime::destroy()
{
    if (!release_queued)
    {
        resident_enqueue_object(g_resident_release_queues, this);
        release_queued = 1;
    }
}

/** @brief Destroy the queued display objects and release every loaded resource slot's allocation but the first. */
FieldRuntime::~FieldRuntime()
{
    lib_object_detach_owner(this);

    if (display_count > 0)
    {
        for (;;)
        {
            LibTransformOwner* node = static_cast<LibTransformOwner*>(display_first);

            if (!node)
            {
                break;
            }

            func_00465A90(this, node);
            node->destroy();
        }
    }

    LibManagedResourceSlot* slot = &resource_slots[1];

    for (s32 i = 1; i < 16; i++, slot++)
    {
        if (slot->active && slot->allocation)
        {
            resident_queue_allocation_release(g_resident_release_queues, slot->allocation);
            slot->allocation = 0;
        }
    }
}

extern LibUpdateList* g_update_list;


/**
 * @brief Initialize the runtime for a screen size: its screen scale, resource space, first resource slot and queues.
 * @param width Screen width.
 * @param height Screen height.
 * @param reserved_width Width of an area kept out of the resource space, or zero.
 * @param reserved_height Height of that area, or zero.
 * @param scale Scale factor.
 */
FieldRuntime::FieldRuntime(float width, float height, u16 reserved_width, u16 reserved_height, float scale)
{
    g_vram_allocator->unk14 = 0xFFD00;
    s32 display_width = g_display->display_area.width;
    s32 display_height = g_display->display_area.height;
    LibDisplayArea* area = &g_display->display_area;
    unk524 = width;
    unk528 = height;
    unk52c = display_width - 1;
    unk530 = display_height - 1;
    screen_scale_x = 16.0f * (display_width / width);
    screen_scale_y = 16.0f * (display_height / height);
    screen_offset_x = 16.0f * (GS_COORDINATE_CENTRE - display_width / 2);
    screen_offset_y = 16.0f * (GS_COORDINATE_CENTRE - display_height / 2);
    unk544 = screen_scale_x * scale;
    u32 size = display_width * display_height + area->base_width * area->base_height;
    u16 pages = 0;

    if (reserved_width > 0 && reserved_height > 0)
    {
        size = (size - reserved_width * reserved_height) & ~0x3F;
        pages = size >> 6;
    }

    unk548 = size;
    unk5fc = pages;
    size >>= 10;
    u32 end = size & ~0x1F;
    s32 low = size & 0x1F;
    s32 remainder = (low << 10) / 32 / 32;

    if (remainder == 0)
    {
        end -= 32;
        remainder = 32;
    }

    resource_area_end = end;
    unk550 = remainder;
    ResidentEntryTable* table = resident_get_entry_table(resident_get_system());
    button_map = reinterpret_cast<ButtonMap*>(resident_find_entry(table, 1));
    void** chunks = reinterpret_cast<void**>(resident_find_entry(table, 0x25466887));
    display_chunks = chunks[1];
    LibResourceHeader* header = static_cast<LibResourceHeader*>(chunks[0]);
    LibManagedResourceSlot* slot = resource_slots;

    for (s32 i = 0; i < 16; i++, slot++)
    {
        slot->identifier = i;

        if (i == 0)
        {
            slot->data = header;
            slot->sections[2] = reinterpret_cast<u8*>(header) + header->offsets[2];
            slot->sections[3] = 0;
            slot->sections[0] = 0;
            slot->sections[1] = 0;
            slot->unk18 = header->unk20;
            slot->unk1c = header->unk24;
            slot->unk20 = header->unk28;
            slot->unk24 = header->unk2c;
            slot->unk28 = header->unk30;
            slot->unk2c = header->unk34;
            slot->unk30 = 0;
            slot->loaded = slot->unk18;
            slot->unit_count = 1024 / slot->unk28;
            slot->loaded_units = slot->unk18 / slot->unit_count + 1;
            slot->start = 0;
            slot->end = slot->unk2c * slot->loaded_units;
            slot->unk48 = 0;
            slot->flag = 1;
            slot->active = 1;
        }
        else
        {
            slot->active = 0;
        }
    }

    display_last = 0;
    display_first = 0;
    display_count = 0;
    text_banks[0].resource_slot = 0;
    text_banks[0].base_key = 0;
    text_banks[1].resource_slot = 0;
    text_banks[1].base_key = 0;
    character_names = 0;
    rate = 1.0f;
    inputs[0].unk02 = 0;
    inputs[0].unk00 = 0;
    inputs[1].unk02 = 0;
    inputs[1].unk00 = 0;
    unk600 = 1;
    unk5ff = 1;
    unk5fe = 1;
    release_queued = 0;
    g_update_list->append_node(this, -1);
}

/** @brief Called by the state hook; the base does nothing. */
void LibClass174F70::func_004662A0()
{
}

/** @brief Release the widget storage and destroy its bases. */
inline ItemCreationClass175030::~ItemCreationClass175030()
{
}

/** @brief Destroy the panel. */
inline LibClass1722E0::~LibClass1722E0()
{
}

/** @brief Release the widget storage and destroy its base. */
inline ItemCreationClass172600::~ItemCreationClass172600()
{
}

/** @brief Release the widget storage and destroy its base. */
inline ItemCreationClass172870::~ItemCreationClass172870()
{
}

/** @brief Destroy the lines, the frame widgets and the container. */
LibClass174F70::~LibClass174F70()
{
}

/**
 * @brief Add a line of text from a resource slot.
 * @param slot Resource slot index.
 * @param key Key of the text in the slot.
 * @return The line's widget, or null when the lines are used up or the text can't be measured.
 */
LibTextWidget* LibClass174F70::add_item(s32 slot, u32 key)
{
    if (item_count >= item_capacity)
    {
        return 0;
    }

    LibTextWidget* item = &items[item_count];
    lib_text_set_resource(item, slot, key, 0);

    if (!lib_text_measure_bounds(item))
    {
        return 0;
    }

    item_count++;
    return item;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00412C40__14LibClass174F70FUiUiUi);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00466AD0);

/**
 * @brief Set the movement target and reset its completion flags.
 * @param x Target horizontal coordinate.
 * @param y Target vertical coordinate.
 * @param duration Duration in seconds, converted to sixty frames per second.
 */
void LibMovementState::set_move_target(float x, float y, float duration)
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
s32 LibMovementState::init_position(float x, float y)
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

// TODO: The cursor's destructor inlines LibCallbackTransform's (which text_0044ABE0 keeps out of line) but not
// LibClass172000's, so the base destructor is only inline in this unit and the inline depth is one here.
inline LibCallbackTransform::~LibCallbackTransform()
{
}

#pragma push
#pragma inline_depth(1)

LibSelectionCursor::~LibSelectionCursor()
{
}

#pragma pop

/**
 * @brief Finish the cursor's drawing packet.
 * @param value Notification word.
 */
void LibSelectionCursor::on_packet_complete(u32 value)
{
    lib_finish_packet(this);
}

/** @brief Mark the DMA pending and queue the cursor's packet. */
void LibSelectionCursor::render()
{
    dma_pending = 1;
    func_00461830(&this->LibMovementState::unk00, static_cast<LibDmaCallbacks*>(this));
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0044B100__18LibSelectionCursorFUiUiUi);

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

/** @brief Release the widget storage and destroy its base. */
ItemCreationClass175110::~ItemCreationClass175110()
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", draw__23ItemCreationClass175110Fv);

/** @brief Restart the animation when its resource changed, otherwise step it and redraw on a frame change. */
void ItemCreationClass175110::func_00413D20()
{
    if (unkc0 < 0 && !unkb4)
    {
        return;
    }

    if (unkc9)
    {
        if (!unkb4)
        {
            unk50.set_display_chunk(unkc0);
        }
        else
        {
            unk50.set_resource(unkb4, &unkb8);
        }

        unk50.start(unkc4);
        unkc9 = 0;
    }
    else if (!unkc8 && unk50.step())
    {
        needs_redraw = 1;
    }
}

/**
 * @brief Set the animated image widget up: its position, drawing storage, resource and image format.
 * @param object Widget to set up.
 * @param resource Resource identifier, or negative for none.
 * @param source Image source, or null.
 * @param format Image format to copy, or null to keep the widget's.
 * @param first Value stored at unkc4.
 * @param second Value stored at unkc8.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @return One on success, or zero when the drawing storage can't be allocated.
 */
extern "C" s32 func_00467800(ItemCreationClass175110* object, s32 resource, void* source, const LibImageFormat* format, u32 first, u8 second, float x, float y)
{
    object->unk18.unk00 = x;
    object->unk18.unk04 = y;

    if (!lib_allocate_drawing_storage(&object->unk40, 16))
    {
        return 0;
    }

    object->unkc0 = resource;
    object->unkb4 = source;

    if (format)
    {
        object->unkb8 = *format;
    }

    object->unkc4 = first;
    object->unkc8 = second;
    object->unkc9 = 1;
    object->unk34 = 6;
    object->unk39 = 1;
    return 1;
}

/** @brief Destroy the label. */
LibStringLabel::~LibStringLabel()
{
}

/**
 * @brief Lay the label's string out off screen and measure it.
 * @param object Label to measure.
 * @return Extent of the laid-out string.
 */
LibTextExtent* func_00467950(LibStringLabel* object)
{
    LibDrawRecord records[0x40];
    object->begin_layout(records, 0.0f);
    object->add_text(object->text);
    object->func_004637A0(records, object->record_count);
    object->align_records_vertically(records, object->record_count);
    return &object->extent;
}

/**
 * @brief Count the character codes in the label's string.
 * @param object Label to read.
 * @return Number of codes.
 */
s32 func_004679B0(LibStringLabel* object)
{
    u16 codes[0x80];
    return func_00464040(object, codes, object->text);
}

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

/** @brief Destroy the widget. */
LibClass175170::~LibClass175170()
{
}

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

/** Partial receiver with an embedded buffer after the word at offset 0x618. */
typedef struct LibEmbeddedBuffer468380
{
    u8 unk00[0x618];
    u32 unk618;
    u8 unk61C[4];
    u8 unk620;
} LibEmbeddedBuffer468380;

/**
 * @brief Get the embedded buffer while the word before it is set.
 * @param object Receiver.
 * @return The buffer at offset 0x620, or null.
 */
extern "C" u8* func_00468380(LibEmbeddedBuffer468380* object)
{
    if (object->unk618 != 0)
    {
        return &object->unk620;
    }

    return 0;
}

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

    return resident_dma_queue_push(g_vif1_dma_queue, submission);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0046A440);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0046AAC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0046AB80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0046AC10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0046ACC0);
