#include "include_asm.h"
#include "vu0.h"
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
#include "overlays/lib/image_model.h"
#include "overlays/lib/widget_aggregate.h"
#include "overlays/lib/message_window.h"
#include "overlays/lib/text_004095C0.h"
#include "overlays/lib/item_allocation.h"
#include "sdk/main/libm_guess_0013F3E0.h"

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

/** @brief Free the buffer and detach. */
LibClass174D70::~LibClass174D70()
{
    delete[] unk3c;
}

/** @brief Start with no objects and flag 0x1 set. */
LibClass174D70::LibClass174D70()
{
    count = 0;
    flags = 1;
    unk3c = 0;
}

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

/**
 * @brief Test whether an allocation record is in use.
 * @param record Allocation record.
 * @return Its allocated flag.
 */
static inline bool allocation_in_use(const ItemCreationAllocationRecord* record)
{
    return record->allocated;
}

extern "C" ResidentObject1B64F8* D_001B64F8;

extern "C" char* func_004642E0(void* context, s32 index);

extern "C" s32 func_00464040(LibDrawWidget* widget, u16* codes, const char* text);

extern "C" s32 func_00463E60(LibDrawWidget* widget, u16* codes, u16 id, s32 variant);

/**
 * @brief Count the glyphs a text lays out, expanding numbers, names and item names, up to its end code.
 * @param widget Widget the text is laid out for.
 * @param source Encoded text.
 * @return Number of glyphs.
 */
extern "C" s32 func_0045FE90(LibDrawWidget* widget, const u8* source)
{
    u16 codes[64];
    s32 count = 0;
    const u8* text = source;

    for (;;)
    {
        s32 c = *text++;

        if (c & 0x80)
        {
            u16 code = (c & 0x7F) | (*text++ << 7);

            if (code & 0x4000)
            {
                switch (code)
                {
                case 0x4002:
                case 0x4008:
                case 0x401A:
                case 0x4020:
                    text++;
                    break;
                case 0x4005:
                case 0x4006:
                case 0x400A:
                case 0x400C:
                case 0x400E:
                case 0x4014:
                case 0x4015:
                    text += 4;
                    break;
                case 0x4011:
                    while (*text)
                    {
                        text++;
                    }

                    text++;
                    break;
                case 0x4012:
                    count += widget->format_number_codes(codes, g_field_runtime->message_arguments[*text++]);
                    break;
                case 0x4013:
                case 0x4021:
                {
                    s32 index = *text++;

                    index = code == 0x4013 ? index : g_field_runtime->message_arguments[index];

                    count += func_00464040(widget, codes, func_004642E0(widget, index));
                    break;
                }
                case 0x4022:
                case 0x4023:
                {
                    s32 value = g_field_runtime->message_arguments[*text++];
                    u16 id = 0;
                    s32 variant = 0;

                    if (code == 0x4022)
                    {
                        id = value;
                    }
                    else
                    {
                        LibGameState* state = reinterpret_cast<LibGameState*>(D_001B64F8);
                        s16 identifier = value;
                        bool valid = false;

                        if (identifier > 0 && identifier <= LIB_ALLOCATION_COUNT)
                        {
                            valid = true;
                        }

                        ItemCreationAllocationRecord* record;

                        if (valid)
                        {
                            record = reinterpret_cast<ItemCreationAllocationRecord*>(&state->allocations[identifier - 1]);
                        }
                        else
                        {
                            record = 0;
                        }

                        if (record != 0 && allocation_in_use(record))
                        {
                            id = record->definition_index() + 1;
                            variant = record->modification_number;
                        }
                    }

                    count += func_00463E60(widget, codes, id, variant);
                    break;
                }
                case 0x401C:
                    while (*text)
                    {
                        text++;
                    }

                    text++;
                    count++;
                    break;
                case 0x401D:
                    text++;
                    count++;
                    break;
                case 0x401F:
                    // TODO: A goto out of the switch is what puts the shared count++ block before the return like the game.
                    goto end;
                }

                continue;
            }
        }

        count++;
    }

end:
    return count;
}

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

/**
 * @brief Find where a laid-out line may break: walk back from the last record while the glyph classes on either side
 *        must stay together.
 * @param object Multiline text widget.
 * @param first First record of the line.
 * @param last Record the line would break at.
 * @return Record to break at.
 */
extern "C" LibDrawRecord* func_004602B0(LibObject174D90* object, LibDrawRecord* first, LibDrawRecord* last)
{
    s32 next = 0;
    bool joined = false;
    s32 count = 0;
    LibDrawRecord* record = last;

    for (;;)
    {
        if (record == first)
        {
            return last;
        }

        s32 kind;
        s32 code = record->code;

        if (code & 0x4000)
        {
            if (code == 0xFFFF)
            {
                kind = 9;
            }
            else if (code == 0x401C)
            {
                kind = 14;
            }
            else if (code == 0x401D)
            {
                kind = 15;
            }
            else
            {
                if (code == 0x4019)
                {
                    break;
                }

                if (code == 0x4018)
                {
                    joined = true;
                }

                goto keep;
            }
        }
        else if (code == 11)
        {
            kind = 0;
        }
        else if (code == 12)
        {
            kind = 1;
        }
        else if (code > 0 && code < 11)
        {
            kind = 2;
        }
        else if (code >= 13 && code < 0x42)
        {
            kind = 3;
        }
        else if (code == 0x42)
        {
            kind = 10;
        }
        else if (code == 0x9D || code == 0x11B)
        {
            kind = 4;
        }
        else if (code >= 0x43 && code < 0x4D)
        {
            kind = 5;
        }
        else if (code >= 0x4D && code < 0x93)
        {
            kind = 6;
        }
        else if (code >= 0x94 && code < 0x9D)
        {
            kind = 7;
        }
        else if (code >= 0x93 && code < 0xE5)
        {
            kind = 8;
        }
        else if (code == 0xE8 || code == 0xE9)
        {
            kind = 9;
        }
        else if (code == 0x102)
        {
            kind = 3;
        }
        else if (code >= 0xEA && code < 0x107)
        {
            kind = 10;
        }
        else if (code >= 0x107 && code < 0x114)
        {
            kind = 11;
        }
        else if (code == 0x114)
        {
            kind = 16;
        }
        else if (code >= 0x114 && code < 0x125)
        {
            kind = 12;
        }
        else
        {
            kind = 13;
        }

        if (count == 0 && kind == 9)
        {
            return record + 1;
        }

        if (count == 0 || kind == 11 || joined)
        {
            next = kind;
            joined = false;
            goto keep;
        }

        if (kind == next)
        {
            if (kind == 6)
            {
                return record + 1;
            }

            goto keep;
        }

        switch (next)
        {
        case 0:
        case 1:
            if (kind == 2 || kind == 3)
            {
                next = kind;
                goto keep;
            }

            break;
        case 2:
            if (kind == 0 || kind == 1)
            {
                next = kind;
                goto keep;
            }

            break;
        case 4:
        case 5:
        case 7:
        case 10:
            next = kind;
            goto keep;
        case 6:
            switch (kind)
            {
            case 4:
            case 5:
                next = kind;
                goto keep;
            case 13:
                if (object->unk558 < 2)
                {
                    break;
                }

                next = kind;
                goto keep;
            }

            break;
        case 8:
            switch (kind)
            {
            case 4:
            case 7:
                next = kind;
                goto keep;
            case 13:
                if (object->unk558 < 2)
                {
                    break;
                }

                next = kind;
                goto keep;
            }

            break;
        case 13:
            if (object->unk558 < 2)
            {
                break;
            }

            if (kind == 2)
            {
                next = kind;
                goto keep;
            }

            if (kind == 6 && (code == 0x51 || code == 0x7E))
            {
                goto keep;
            }

            break;
        case 14:
            next = kind;
            goto keep;
        case 16:
            switch (kind)
            {
            case 1:
            case 3:
                next = kind;
                goto keep;
            }

            break;
        case 3:
            if (kind == 16)
            {
                next = kind;
                goto keep;
            }

            break;
        }

        return record + 1;

    keep:
        count++;
        record--;
    }

    return record;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00460750);

/**
 * @brief Measure the widget's text page by page: per page, count the glyphs found in its resource (or the runtime's
 *        first slot) and missing ones, the space control codes add, line breaks, quoted string bytes and button
 *        glyphs, and keep the largest page's counts.
 * @param object Multiline text widget.
 */
extern "C" void func_00461230(LibObject174D90* object)
{
    object->unkb0 = 0;
    object->unkac = 0;
    object->unka8 = 0;
    object->unka4 = 0;
    object->glyph_count = 0;
    object->unkb4 = 0;
    const u8* text = static_cast<const u8*>(object->unk100);
    bool more = true;

    do
    {
        s32 lines = 0;
        s32 buttons = 0;
        s32 found = 0;
        s32 missing = 0;
        s32 breaks = 0;
        s32 quoted = 0;

        for (;;)
        {
            s32 code = *text++;

            // TODO: The game sign-extends the code before this test, which a compare with a long zero gives.
            if (code == 0L)
            {
                more = false;
                break;
            }

            if (code & 0x80)
            {
                code = (code & 0x7F) | (*text++ << 7);

                if (code & 0x4000)
                {
                    switch (code)
                    {
                    case 0x4000:
                    case 0x4004:
                    case 0x4007:
                    case 0x4016:
                    case 0x4017:
                    case 0x4018:
                    case 0x4019:
                    case 0x401F:
                        lines++;
                        break;
                    case 0x4001:
                        lines++;
                        goto page_end;
                    case 0x4020:
                        lines++;
                        text++;
                        break;
                    case 0x4002:
                    case 0x4008:
                    case 0x401A:
                        text++;
                        break;
                    case 0x4005:
                    case 0x4006:
                    case 0x4014:
                    case 0x4015:
                    case 0x401E:
                        lines++;
                        text += 4;
                        break;
                    case 0x400A:
                    case 0x400C:
                    case 0x400E:
                        text += 4;
                        break;
                    case 0x4012:
                        found += 11;
                        text++;
                        break;
                    case 0x4013:
                    case 0x4021:
                        found += 0x20;
                        text++;
                        break;
                    case 0x4022:
                    case 0x4023:
                        missing += 0x40;
                        text++;
                        break;
                    case 0x4010:
                        lines++;
                        breaks++;
                        break;
                    case 0x4011:
                        while (*text)
                        {
                            quoted++;
                            text++;
                        }

                        text++;
                        break;
                    case 0x401C:
                        lines++;
                        breaks++;

                        while (*text)
                        {
                            text++;
                            quoted++;
                        }

                        text++;
                        break;
                    case 0x401D:
                        lines++;
                        buttons++;
                        text++;
                        break;
                    }

                    continue;
                }
            }

            s32 index;
            LibManagedResourceSlot* slot;

            slot = object->resource_slot;
            index = code - 1;

            if (slot->flag)
            {
                if (code <= 300)
                {
                    slot = &g_field_runtime->resource_slots[0];
                }
                else
                {
                    index -= 300;
                }
            }

            if (index < slot->loaded)
            {
                found++;
            }
            else
            {
                missing++;
            }
        }

    page_end:
        lines += found + missing;

        if (object->unkb4 < lines)
        {
            object->unkb4 = lines;
        }

        if (object->glyph_count < buttons)
        {
            object->glyph_count = buttons;
        }

        if (object->unka4 < found)
        {
            object->unka4 = found;
        }

        if (object->unka8 < missing)
        {
            object->unka8 = missing;
        }

        if (object->unkac < breaks)
        {
            object->unkac = breaks;
        }

        if (object->unkb0 < quoted)
        {
            object->unkb0 = quoted;
        }
    } while (more);

    object->unkb4 += 0x80;
}

/**
 * @brief Point the multiline widget at a keyed text of a resource slot: measure it and allocate its drawing storage,
 *        glyph states and line table.
 * @param object Multiline text widget.
 * @param slot Resource slot index.
 * @param key Key of the text in the slot's index.
 * @param mode Drawing mode mask.
 * @param flag Nonzero to reset the drawing state and the scroll speed first.
 * @return One, or zero when an allocation failed.
 */
extern "C" s32 func_004614E0(LibObject174D90* object, s32 slot, s32 key, u32 mode, u32 flag)
{
    object->unk39 = 0;

    if (object->unk70)
    {
        resident_queue_allocation_release(g_resident_release_queues, object->unk70);
        object->unk70 = 0;
    }

    func_004C7D00(object);

    if (flag)
    {
        object->reset_drawing_state();
    }

    object->resource_slot = &g_field_runtime->resource_slots[slot];
    object->unk100 = func_00465340(g_field_runtime, slot, key);
    func_00461230(object);

    if (!object->allocate_storage(object->unka4, object->unka8, object->unkac, object->unkb0))
    {
        return 0;
    }

    if (object->glyph_count > 0)
    {
        object->unkfc = new (0) LibClass178780;

        if (object->unkfc == 0)
        {
            return 0;
        }

        if (!static_cast<LibClass178780*>(object->unkfc)->init(object->glyph_count))
        {
            return 0;
        }
    }

    object->unk70 = static_cast<u8*>(::operator new[](object->unkb4 * 32, 0));

    if (object->unk70 == 0)
    {
        return 0;
    }

    if (flag)
    {
        object->unk52c = object->unk524;
        object->unk558 = object->unk554;
    }

    object->mode = mode;
    object->unk118 = object->unk100;
    object->unk568 = 0;
    object->unk550 = 5;
    object->unk575 = 0;
    object->unk577 = 0;
    object->pending = 0;
    object->unk57a = 1;
    object->unk39 = 1;
    return 1;
}

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

/** @brief Hook run when the text restarts; the base window does nothing. */
void LibMessageWindow::func_00461960()
{
}

/** @brief Hook run at the end of the text; the base window does nothing. */
void LibMessageWindow::func_00461970()
{
}

/**
 * @brief Hook for a text control code with three values; the base window does nothing.
 * @param first First value.
 * @param second Second value.
 * @param third Third value.
 */
void LibMessageWindow::func_00461980(s16 first, s16 second, u32 third)
{
}

/** @brief Hook for the event flagged at 0x105F; the base window does nothing. */
void LibMessageWindow::func_00461990()
{
}

/** @brief Hook for the event flagged at 0x1060; the base window does nothing. */
void LibMessageWindow::func_004619A0()
{
}

/** @brief Window hook at slot 0xC8; the base window does nothing. */
void LibMessageWindow::func_004619B0()
{
}

/**
 * @brief Hook for a text control code with one value; the base window does nothing.
 * @param value Control value.
 */
void LibMessageWindow::func_004619C0(u32 value)
{
}

/**
 * @brief Hook for a second text control code with one value; the base window does nothing.
 * @param value Control value.
 */
void LibMessageWindow::func_004619D0(u32 value)
{
}

/** @brief Hook for a text control code; the base window does nothing. */
void LibMessageWindow::func_004619E0()
{
}

/** @brief Destroy the panel. */
inline LibClass1722E0::~LibClass1722E0()
{
}

/** @brief Release the widget storage and destroy its base. */
inline ItemCreationClass1746A0::~ItemCreationClass1746A0()
{
}

/** @brief Destroy the widget. */
inline LibClass175170::~LibClass175170()
{
}

/** @brief Destroy the window and its widgets. */
LibMessageWindow::~LibMessageWindow()
{
}

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

/**
 * @brief Step the window's open/close sequence: open the frame, show the panel and text, wait for the text to finish,
 *        hide the text, close the frame and finish.
 * @param first Unused.
 * @param second Unused.
 * @param third Unused.
 */
void LibMessageWindow::func_00412C40(u32 first, u32 second, u32 third)
{
    switch (state)
    {
    case 0:
        if (!(mode & 0x10000))
        {
            frame.unk3d = 1;
            frame.transition_state = 1;
            state++;
        }
        else
        {
            state = 2;
        }

        break;
    case 1:
        if (frame.in_transition_state(0))
        {
            state++;
        }

        break;
    case 2:
        unk180.unk3d = 1;
        text.unk3d = 1;
        state++;
        break;
    case 3:
        if (!text.text_finished())
        {
            break;
        }

        if (mode & 0x80000)
        {
            unk105f = 1;
        }

        state++;
    case 4:
        if (mode & 0x80000)
        {
            break;
        }

        state++;
    case 5:
        text.unk3d = 0;

        if (mode & 0x100000)
        {
            unk1060 = 1;
        }

        state++;
    case 6:
        if (mode & 0x100000)
        {
            break;
        }

        state++;
    case 7:
        if (!(mode & 0x10000))
        {
            frame.transition_state = 5;
            state++;
        }
        else
        {
            state = 9;
        }

        break;
    case 8:
        if (frame.in_transition_state(0))
        {
            frame.unk3d = 0;
            unk180.unk3d = 0;
            state++;
        }

        break;
    case 9:
        state = -1;
        unkab = 0;
        func_004619B0();

        if (mode & 0x80000000)
        {
            destroy();
        }

        break;
    }
}

/**
 * @brief Update and draw the container, then run the hooks for the text events flagged since the last call.
 * @param first Nonzero to chain the widget packets.
 * @param second Nonzero to update the widgets.
 * @param third Nonzero to draw the widgets.
 */
void LibMessageWindow::func_0044B100(u32 first, u32 second, u32 third)
{
    LibContainer::func_0044B100(first, second, third);

    if (unk105c)
    {
        func_00461960();
        unk105c = 0;
    }

    if (unk105d)
    {
        func_00461970();
        unk105d = 0;
    }

    if (unk105e)
    {
        func_00461980(unk1054, unk1056, unk1058);
        unk105e = 0;
    }

    if (unk1061)
    {
        func_004619C0(unk1050);
        unk1061 = 0;
    }

    if (unk1062)
    {
        func_004619D0(unk1050);
        unk1062 = 0;
    }

    if (unk1063)
    {
        func_004619E0();
        unk1063 = 0;
    }

    if (unk105f)
    {
        func_00461990();
        unk105f = 0;
    }

    if (unk1060)
    {
        func_004619A0();
        unk1060 = 0;
    }
}

extern "C" s32 func_00468230(LibClass175170* object, float x, float y);

/**
 * @brief Set the message window up at a position and size: its frame, cursor, two clipping widgets and its text,
 *        loaded from a keyed text.
 * @param window Window to set up.
 * @param source Resource source word.
 * @param key Text resource key.
 * @param mode Drawing mode; bit 17 hides the text, bit 18 keeps the cursor detached from it.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Window width.
 * @param height Window height.
 * @param flag Resource state flag.
 * @return One on success, or zero when a widget can't be set up.
 */
extern "C" s32 func_00461FA0(LibMessageWindow* window, u32 source, s32 key, u32 mode, float x, float y, float width,
                             float height, u32 flag)
{
    window->source = source;
    window->key = key;
    window->mode = mode;
    lib_container_init(window, 4, x, y, 0, 0.0f, 0);

    if (!window->frame.init_frame(width, height))
    {
        return 0;
    }

    if (!func_00468230(&window->unk180, width - 28.0f, height - 8.0f))
    {
        return 0;
    }

    if (!lib_scissor_init_rectangle(&window->unka18, 0.0f, 16.0f, width, height - 32.0f))
    {
        return 0;
    }

    if (!lib_scissor_init_reset(&window->unka6c, 1))
    {
        return 0;
    }

    if (!lib_multiline_text_init_resource_rectangle(&window->text, 16.0f, 16.0f, width - 32.0f, height - 32.0f,
                                                     window->source, window->key, window->mode, flag))
    {
        return 0;
    }

    window->text.owner = window;
    window->frame.unk3d = 0;
    window->unk180.unk3d = 0;
    window->text.unk3d = 0;

    if (window->mode & 0x20000)
    {
        window->text.visible = 0;
    }

    if (!(window->mode & 0x40000))
    {
        window->text.unk114 = &window->unk180;
    }

    lib_container_attach_widget(window, &window->frame);
    lib_container_attach_widget(window, &window->unka18);
    lib_container_attach_widget(window, &window->text);
    lib_container_attach_widget(window, &window->unka6c);
    lib_container_attach_widget(window, &window->unk180);
    window->state = 0;
    window->unk1064 = 0;
    window->unk1063 = 0;
    window->unk1062 = 0;
    window->unk1061 = 0;
    window->unk1060 = 0;
    window->unk105f = 0;
    window->unk105e = 0;
    window->unk105d = 0;
    window->unk105c = 0;
    return 1;
}

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

/** @brief Close the drawing packet: a texture flush when unkdc is set, REF tags for the two blocks in use, then END. */
void LibDrawWidget::func_004623F0()
{
    u64* packet = packet_cursor;

    if (unkdc > 0)
    {
        packet[0] = DMA_TAG(2, DMA_TAG_ID_CNT, 0);
        packet[2] = GIF_TAG_NREG(1) | GIF_TAG_EOP | 1;
        packet[3] = GIF_REGISTER_AD;
        packet[4] = 0;
        packet[5] = GS_REGISTER_TEXFLUSH;
        packet += 6;
    }

    if (unke0 > 0)
    {
        packet[0] = DMA_TAG((u32)(unk60 - unk5c) >> 4, DMA_TAG_ID_REF, (u32)unk5c & 0x0FFFFFFF);
        packet += 2;
    }

    if (unke4 > 0)
    {
        packet[0] = DMA_TAG((u32)(unk68 - unk64) >> 4, DMA_TAG_ID_REF, (u32)unk64 & 0x0FFFFFFF);
        packet += 2;
    }

    packet_tag = packet;
    packet[0] = DMA_TAG(0, DMA_TAG_ID_END, 0);
    packet_cursor = packet + 2;
}

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

/** "%d". */
extern const char D_00505CF8[];

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

/**
 * @brief Count the 0x401E control codes in a keyed text and copy their four-byte arguments.
 * @param runtime Field runtime.
 * @param slot Resource slot index.
 * @param key Key of the text in the slot's index.
 * @param arguments Receives four bytes per code, or null.
 * @return Number of 0x401E codes.
 */
extern "C" s32 func_00465100(FieldRuntime* runtime, s32 slot, s32 key, u8* arguments)
{
    s32 count = 0;
    const u8* text = static_cast<const u8*>(func_00465340(runtime, slot, key));

    while (*text)
    {
        u16 code = *text++;

        // TODO: The game sign-extends the code before this test, which a compare with a long zero gives.
        if (code == 0L)
        {
            break;
        }

        if (code & 0x80)
        {
            code = (code & 0x7F) | (*text++ << 7);

            if (code & 0x4000)
            {
                switch (code)
                {
                case 0x4002:
                case 0x4008:
                case 0x4012:
                case 0x4013:
                case 0x401A:
                case 0x401D:
                case 0x4020:
                case 0x4021:
                case 0x4022:
                case 0x4023:
                    text++;
                    break;
                case 0x4005:
                case 0x4006:
                case 0x400A:
                case 0x400C:
                case 0x400E:
                case 0x4014:
                case 0x4015:
                    text += 4;
                    break;
                case 0x4011:
                case 0x401C:
                    while (*text)
                    {
                        text++;
                    }

                    text++;
                    break;
                case 0x401E:
                    count++;

                    if (arguments)
                    {
                        arguments[0] = text[0];
                        arguments[1] = text[1];
                        arguments[2] = text[2];
                        arguments[3] = text[3];
                        text += 4;
                        arguments += 4;
                    }
                    else
                    {
                        text += 4;
                    }

                    break;
                }
            }
        }
    }

    return count;
}

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

/**
 * @brief Called by the state hook when the list closes; the base does nothing.
 * @param result Chosen item number, or zero when cancelled.
 */
void LibClass174F70::func_004662A0(s32 result)
{
}

/** @brief Release the widget storage and destroy its bases. */
inline ItemCreationClass175030::~ItemCreationClass175030()
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

/**
 * @brief Run the list's open, select and close states: open the frame, show the items, fade in, move the cursor with
 *        the pad until an item is confirmed or the list cancelled, then fade out, hide and close.
 * @param first First update flag, unused here.
 * @param second Second update flag, unused here.
 * @param third Third update flag, unused here.
 */
void LibClass174F70::func_00412C40(u32 first, u32 second, u32 third)
{
    if (unk13f8 == 0)
    {
        return;
    }

    switch (unk13f8)
    {
    case 1:
        if (show_frame)
        {
            unk16c.transition_state = 1;
            unk13f8++;
        }
        else
        {
            unk13f8 = 3;
        }

        break;
    case 2:
        if (unk16c.in_transition_state(0))
        {
            unk13f8++;
        }

        break;
    case 3:
    {
        LibTextWidget* item = items;

        for (s32 i = 0; i < item_capacity; i++, item++)
        {
            item->unk3d = 1;
        }

        unk1fc.unk3d = 1;
        unk250.unk3d = 1;
        unkf0.unk3d = 1;
        s32 index = unk13f0 < 0 ? 0 : unk13f0 - 1;
        float y = index * 28;
        LibTextWidget* selected = &items[index];
        unk1fc.unk18.unk04 = 16.0f + y;
        unk1fc.needs_redraw = 1;
        unk250.unk18.unk04 = 40.0f + y;
        unk250.needs_redraw = 1;
        unkf0.position.y = 30.0f + y;
        unkf0.needs_redraw = 1;
        float width = selected->extent.width;
        unk1fc.unk18.unk08 = 2.0f + width;
        unk250.unk18.unk08 = width;

        if (show_frame)
        {
            unk13f8 = 5;
        }
        else
        {
            unkE0 = 0.0f;
            unk13f8++;
        }

        break;
    }
    case 4:
    {
        float alpha = unkE0;

        alpha += 21.333334f * field_rate(g_field_runtime);

        if (!(alpha < 128.0f))
        {
            alpha = 128.0f;
            unk13f8++;
        }

        unkE0 = alpha;
        geometry_dirty = 1;
        break;
    }
    case 5:
        if (unk13f0 < 0)
        {
            unk13f0 = 1;
        }

        unk13f4 = -1;
        unk13f8++;
        break;
    case 6:
    {
        if (!unkf0.arrived)
        {
            break;
        }

        s32 index = unk13f0 < 0 ? 0 : unk13f0 - 1;
        float y = index * 28;
        LibTextWidget* selected = &items[index];
        unk1fc.unk18.unk04 = 16.0f + y;
        unk1fc.needs_redraw = 1;
        unk250.unk18.unk04 = 40.0f + y;
        unk250.needs_redraw = 1;
        unkf0.position.y = 30.0f + y;
        unkf0.needs_redraw = 1;
        float width = selected->extent.width;
        unk1fc.unk18.unk08 = 2.0f + width;
        unk250.unk18.unk08 = width;

        u16 repeat = g_field_runtime->inputs[unk13fc].unk04;
        bool moved = false;

        if (repeat & 0x10)
        {
            if (unk13f0 > 1)
            {
                unk13f0--;
            }
            else
            {
                unk13f0 = item_capacity;
            }

            moved = true;
        }
        else if (repeat & 0x40)
        {
            if (unk13f0 < item_capacity)
            {
                unk13f0++;
            }
            else
            {
                unk13f0 = 1;
            }

            moved = true;
        }

        if (moved)
        {
            resident_sound_play(g_sound, 0, 0, 0, 127, 64, 0);

            if (show_cursor)
            {
                unkf0.set_move_target(36.0f, (unk13f0 - 1) * 28 + 30, 0.05f);
            }

            break;
        }

        u16 pressed = g_field_runtime->inputs[unk13fc].unk02;

        if (pressed & g_field_runtime->button_map->buttons[0])
        {
            resident_sound_play(g_sound, 1, 0, 0, 127, 64, 0);
            unk13f4 = unk13f0;
        }
        else if (unk13fe && (pressed & g_field_runtime->button_map->buttons[1]))
        {
            resident_sound_play(g_sound, 2, 0, 0, 127, 64, 0);
            unk13f4 = 0;
        }

        if (unk13f4 >= 0)
        {
            if (unk13ff)
            {
                unk13f8 = 0;
            }
            else
            {
                unk13f8++;
            }
        }

        break;
    }
    case 7:
        if (show_frame)
        {
            unk13f8 = 9;
        }
        else
        {
            unk13f8++;
        }

        break;
    case 8:
    {
        float alpha = unkE0;

        alpha -= 21.333334f * field_rate(g_field_runtime);

        if (alpha <= 0.0f)
        {
            alpha = 0.0f;
            unk13f8++;
        }

        unkE0 = alpha;
        geometry_dirty = 1;
        break;
    }
    case 9:
        LibTextWidget* item = items;

        for (s32 i = 0; i < item_capacity; i++, item++)
        {
            item->unk3d = 0;
        }

        unk1fc.unk3d = 0;
        unk250.unk3d = 0;
        unkf0.unk3d = 0;

        if (show_frame)
        {
            unk16c.transition_state = 5;
            unk13f8++;
        }
        else
        {
            unk13f8 = 11;
        }

        break;
    case 10:
        if (unk16c.in_transition_state(0))
        {
            unk13f8++;
        }

        break;
    case 11:
        unk13f8 = 0;
        unkab = 0;
        func_004662A0(unk13f4);

        if (unk1404)
        {
            destroy();
        }

        break;
    }
}

/**
 * @brief Set the list up for up to 16 items: frame, cursor, markers and item text widgets, attached by the flags.
 * @param capacity Number of items, at most 16.
 * @param flags Bit 0x10000 hides the frame, 0x4 the cursor, 0x8 both markers; 0x2 picks the single marker over the
 *        pair; 0x20 clears unk13f8 and unkab; 0x1, 0x10 and 0x80000000 are kept as flags.
 * @param text_flag Flag passed to each item's text setup.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Frame width.
 * @param height Frame height.
 * @return 1 on success, 0 when a part can't be set up or the capacity is too large.
 */
s32 LibClass174F70::init(s32 capacity, u32 flags, u8 text_flag, float x, float y, float width, float height)
{
    if (capacity > 16)
    {
        return 0;
    }

    item_capacity = capacity;
    item_count = 0;
    unk13f4 = -1;
    unk13f0 = -1;
    unk13fc = 0;
    this->text_flag = text_flag;
    unk13fe = (flags & 0x1) != 0;
    unk13ff = (flags & 0x10) != 0;
    show_frame = (flags & 0x10000) == 0;
    show_cursor = (flags & 0x4) == 0;
    unk1404 = (flags & 0x80000000) != 0;
    bool marker = false;
    bool markers = false;

    if (!(flags & 0x8))
    {
        if (flags & 0x2)
        {
            marker = true;
        }
        else
        {
            markers = true;
        }
    }

    show_marker = marker;
    show_markers = markers;
    lib_container_init(this, 3, x, y, 0, 0.0f, 0);

    if (!unk16c.init_frame(width, height))
    {
        return 0;
    }

    if (show_frame)
    {
        lib_container_attach_widget(this, &unk16c);
    }

    if (!func_0041AD10(&unk1fc, 40.0f, 16.0f, 0.0f, 28.0f))
    {
        return 0;
    }

    if (show_markers)
    {
        lib_container_attach_widget(this, &unk1fc);
    }

    if (!lib_marker_init_rectangle(&unk250, 40.0f, 40.0f, 0.0f, 2.25f))
    {
        return 0;
    }

    if (show_marker)
    {
        lib_container_attach_widget(this, &unk250);
    }

    LibTextWidget* item = items;

    for (s32 i = 0; i < item_capacity; i++, item++)
    {
        if (!lib_text_init_resource_rectangle(item, 0, 0, this->text_flag, 0.0f, 0.0f, 0.0f, 0.0f))
        {
            return 0;
        }

        item->unk18.unk00 = 40.0f;
        item->unk18.unk04 = 16 + i * 28;
        item->needs_redraw = 1;
        lib_container_attach_widget(this, item);
    }

    if (!lib_moving_widget_init_position(&unkf0, 36.0f, 30.0f))
    {
        return 0;
    }

    if (show_cursor)
    {
        lib_container_attach_widget(this, &unkf0);
    }

    LibTextWidget* hidden = items;

    for (s32 i = 0; i < item_capacity; i++, hidden++)
    {
        hidden->unk3d = 0;
    }

    unk1fc.unk3d = 0;
    unk250.unk3d = 0;
    unkf0.unk3d = 0;

    if (flags & 0x20)
    {
        unk13f8 = 0;
        unkab = 0;
    }
    else
    {
        unk13f8 = 1;
    }

    return 1;
}

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00466E70__16LibMovementStateFPC10LibVector4Uif);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", step__16LibMovementStateFv);

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

/** @brief Build the packet once, at the container's position, and point the widget's packet at it. */
void ItemCreationClass175030::draw()
{
    if (!unk3b)
    {
        LibContainer* owner = container;
        LibCallbackTransform& transform = *owner;

        func_00466E70(&transform.translation, transform.unka4 + unk34, owner->unkE0);
        packet = packet_tag = reinterpret_cast<u64*>(unk00.dma_address);
        unk3b = 1;
    }
}

/** @brief Move one step and redraw when the position changed. */
void ItemCreationClass175030::func_00413D20()
{
    if (step())
    {
        needs_redraw = 1;
    }
}

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

/**
 * @brief Move the cursor one step and redraw it when asked.
 * @param first Nothing happens unless set.
 * @param second Step the movement; a changed position marks the geometry dirty.
 * @param third Rebuild the packet if the geometry is dirty, then mark the cursor for drawing.
 */
void LibSelectionCursor::func_0044B100(u32 first, u32 second, u32 third)
{
    if (!first)
    {
        return;
    }

    if (second && step())
    {
        geometry_dirty = 1;
    }

    if (third)
    {
        if (geometry_dirty)
        {
            func_00466E70(0, unka4, 128.0f);
        }

        unk63 = 1;
    }
}

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

/** @brief Draw the animation's current frame into the widget's packet. */
void ItemCreationClass175110::draw()
{
    if (unkc0 < 0 && !unkb4)
    {
        unk3b = 0;
        return;
    }

    if (unk3b)
    {
        return;
    }

    unk50.set_position(unk18.unk00, unk18.unk04);
    unk50.unk50 = draw_alpha;
    u64* start = reinterpret_cast<u64*>(unk40.dma_address);
    u64* cursor = start;
    packet_tag = start;
    packet = start;
    cursor += 2;
    LibContainer* owner = container;
    LibCallbackTransform& transform = *owner;

    func_004535B0(&unk50, &cursor, &transform.translation, transform.unka4 + unk34, owner->unkE0, 0);
    *packet_tag = DMA_TAG((reinterpret_cast<u32>(cursor) - reinterpret_cast<u32>(packet_tag) - LIB_DRAW_QWORD_SIZE) / LIB_DRAW_QWORD_SIZE, DMA_TAG_ID_END, 0);
    unk3b = 1;
}

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", draw__14LibClass175170Fv);

/** @brief Fade the widget in or out while it opens or closes, and turn the rings while it shows. */
void LibClass175170::func_00413D20()
{
    if (unk890)
    {
        if (unk88c == 0)
        {
            if (unk890 == 1)
            {
                unk888 = 0.0f;
                draw_alpha = 0.0f;
                unk894 = 1;
                unk890++;
            }

            unk888 += 0.12f * field_rate(g_field_runtime);
            draw_alpha += 17.066668f * field_rate(g_field_runtime);

            if (!(draw_alpha < 128.0f))
            {
                draw_alpha = 128.0f;
                unk890 = 0;
            }
        }
        else
        {
            unk888 -= 0.12f * field_rate(g_field_runtime);
            draw_alpha -= 17.066668f * field_rate(g_field_runtime);

            if (draw_alpha <= 0.0f)
            {
                unk894 = 0;
                unk890 = 0;
            }
        }
    }

    if (unk894)
    {
        unk884 += 5.0f * field_rate(g_field_runtime);

        if (!(unk884 <= 360.0f))
        {
            unk884 -= 360.0f;
        }

        unk50.step();
        needs_redraw = 1;
    }
}

/**
 * @brief Place the widget and set up its animations: the main one from display chunk 0x43, then two rows of ten
 *        cells from chunk 0x44 in the two row colors.
 * @param object Widget to set up.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @return 1 on success, 0 when the drawing storage can't be allocated.
 */
extern "C" s32 func_00468230(LibClass175170* object, float x, float y)
{
    object->unk18.unk00 = x;
    object->unk18.unk04 = y;

    if (!lib_allocate_drawing_storage(&object->unk40, 0x138))
    {
        return 0;
    }

    object->unk50.set_display_chunk(0x43);
    object->unk50.start(0);
    object->unk50.unk20 = 12.0f;
    object->unk50.unk24 = 12.0f;

    LibImageAnimation* cell = object->cells[0];

    for (s32 row = 0; row < 2; row++)
    {
        for (s32 column = 0; column < 10; column++, cell++)
        {
            cell->set_display_chunk(0x44);
            cell->start(0);
            cell->unk20 = 4.0f;
            cell->unk24 = 4.0f;

            if (row == 0)
            {
                cell->unk44 = 128.0f;
                cell->unk48 = 28.0f;
                cell->unk4c = 28.0f;
            }
            else
            {
                cell->unk44 = 40.0f;
                cell->unk48 = 40.0f;
                cell->unk4c = 128.0f;
            }
        }
    }

    object->unk884 = 0;
    object->unk890 = 0;
    object->unk894 = 0;
    object->unk34 = 7;
    object->unk39 = 1;
    return 1;
}

/**
 * @brief Report the model's list kind.
 * @return Seven.
 */
s32 LibObject1751A0::get_default_list_kind()
{
    return 7;
}

/**
 * @brief Resolve an offset; this model has none.
 * @param offset Offset to resolve.
 * @return Null.
 */
void* LibObject1751A0::resolve_offset(const u32* offset)
{
    return 0;
}

/**
 * @brief Return the image record while an image is set.
 * @return The record, or null.
 */
void* LibObject1751A0::get_data()
{
    if (image != 0)
    {
        return &unk620;
    }

    return 0;
}

/** Next phase handed out by LibObject1751A0::set_phase_period. */
extern "C" u8 D_001B6580;

/**
 * @brief Take the next phase of a shared counter that cycles through a period.
 * @param period Period length; zero leaves the counter alone.
 */
void LibObject1751A0::set_phase_period(u8 period)
{
    phase_period = period;
    phase = D_001B6580;

    if (period)
    {
        D_001B6580 = (D_001B6580 + 1) % period;
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004683E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00468590);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", claim_cell__15LibObject1751A0FPC10LibVector4PP14LibClass174228Pi);

/**
 * @brief Make a copy of this model that stays linked to it.
 * @return The copy, or null.
 */
LibTransformOwner* LibObject1751A0::clone()
{
    LibObject1751A0* copy = new (0) LibObject1751A0;

    if (copy == 0)
    {
        return 0;
    }

    copy->copy_image_state(this);
    add_clone(copy);
    lib_object_set_list_kind(this, LIB_LIST_KIND_LATE_MODEL);
    return copy;
}

/**
 * @brief Copy another model's image state.
 * @param model Model to copy.
 */
void LibObject1751A0::copy_image_state(LibObject1751A0* model)
{
    unkaa4 = model->unkaa4;
    unkadf = model->unkadf;
    unkabc = model->unkabc;
    unkac0 = model->unkac0;
    unkae0 = model->unkae0;
    image = model->image;
    unkae6 = model->unkae6;
    unkac4 = model->unkac4;
    copied = 1;
    source = model;

    if (image)
    {
        unk648 = model->unk648;
        unk624 = model->unk624;
        unk640 = 0;
        unk620 = 0;
        reset_texture_uploads();
        setup = model->setup;
    }

    hold_reference(model->reference);
    diagonal = model->diagonal;
    unkade = model->unkade;
    unkadd = model->unkadd;
    kind = model->kind;
    unkae2 = model->unkae2;
    LibColorModel::copy_color_state(model);

    if (unka90 == 0)
    {
        allocate_packets();
    }

    unk59d_0 = 1;
}

/**
 * @brief Turn fogging on or off in the model's packet.
 * @param enabled Nonzero for fog.
 */
void LibObject1751A0::set_fog_enabled(u8 enabled)
{
    if (packet != 0 && fog_enabled != enabled)
    {
        unk59d_0 = 1;
        LibImagePacket* uncached = reinterpret_cast<LibImagePacket*>(reinterpret_cast<u32>(packet) | UNCACHED_SEGMENT);

        if (enabled)
        {
            uncached->primitive_tag_words[1] |= GIF_TAG_HIGH_PRIM_FGE;
        }
        else
        {
            uncached->primitive_tag_words[1] &= ~GIF_TAG_HIGH_PRIM_FGE;
        }

        fog_enabled = enabled;
    }
}

/**
 * @brief Set the primitive the model draws, its blend mode and the packet values that go with them.
 * @param primitive Primitive kind, 0 to 6.
 * @param value Value stored in the packet and at unkade.
 * @param blend Blend mode; nonzero also turns alpha blending on in the primitive.
 * @param unk54 Value stored in the packet at 0x54.
 */
void LibObject1751A0::set_primitive(s32 primitive, u8 value, s32 blend, float unk54)
{
    kind = primitive;

    if (unka90 == 0)
    {
        allocate_packets();
    }

    if (unka90 != 0 && packet != 0)
    {
        LibImagePacket* uncached = reinterpret_cast<LibImagePacket*>(reinterpret_cast<u32>(packet) | EE_UNCACHED_ACCELERATED);
        uncached->unpack = VIF_UNPACK(VIF_UNPACK_V4_32, 0xE, 0x60);
        uncached->unk54 = unk54;
        uncached->unk24 = value;
        unkade = value;

        if (image)
        {
            for (s32 i = 0; i < image->flag_count; i++)
            {
                if (image->flags[i])
                {
                    unkae2 = 1;
                    break;
                }
            }
        }
        else
        {
            unkae2 = blend;
        }

        uncached->alpha = D_004ED320[blend];
        uncached->alpha_address = GS_REGISTER_ALPHA_1;

        if (blend)
        {
            uncached->unk2c = 1;
        }

        uncached->gif_tag = 4 | GIF_TAG_EOP | GIF_TAG_NREG(1);
        uncached->gif_registers = LIB_DRAW_AD_REGISTERS;

        switch (primitive)
        {
        case 0:
            uncached->primitive_tag = GIF_TAG_EOP | GIF_TAG_PRE | GIF_TAG_PRIM((u32)(blend ? GS_PRIM_ABE : 0)) | GIF_TAG_NREG(2);
            uncached->primitive_registers = 0x41;
            break;
        case 1:
            uncached->primitive_tag = GIF_TAG_EOP | GIF_TAG_PRE | GIF_TAG_PRIM((u32)(blend ? GS_PRIM_ABE : 0) | 0xA) | GIF_TAG_NREG(2);
            uncached->primitive_registers = 0x41;
            break;
        case 2:
            uncached->primitive_tag = GIF_TAG_EOP | GIF_TAG_PRE | GIF_TAG_PRIM((u32)(blend ? GS_PRIM_ABE : 0) | 0xC) | GIF_TAG_NREG(2);
            uncached->primitive_registers = 0x41;
            break;
        case 3:
            uncached->primitive_tag = GIF_TAG_EOP | GIF_TAG_PRE | GIF_TAG_PRIM(0x54) | GIF_TAG_NREG(3);
            uncached->primitive_registers = 0x412;
            break;
        case 4:
            uncached->primitive_tag = GIF_TAG_EOP | GIF_TAG_PRE | GIF_TAG_PRIM(0x5C) | GIF_TAG_NREG(3);
            uncached->primitive_registers = 0x412;
            break;
        case 5:
            uncached->primitive_tag = GIF_TAG_EOP | GIF_TAG_PRE | GIF_TAG_PRIM((u32)(blend ? GS_PRIM_ABE : 0) | 0x14) | GIF_TAG_NREG(3);
            uncached->primitive_registers = 0x412;
            break;
        case 6:
            uncached->primitive_tag = GIF_TAG_EOP | GIF_TAG_PRE | GIF_TAG_PRIM(0x54) | GIF_TAG_NREG(3);
            uncached->primitive_registers = 0x412;
            break;
        }

        if (fog_enabled)
        {
            uncached->primitive_tag_words[1] |= GIF_TAG_HIGH_PRIM_FGE;
        }

        unk59d_0 = 1;
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00469180);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", update__15LibObject1751A0Fv);

/**
 * @brief Send the model's packet chain on VIF1.
 * @param channel DMA channel; unused.
 */
void LibObject1751A0::submit_dma(u32 channel)
{
    dma_pending = 1;
    *D1_QWC = 0;
    *D1_TADR = chain_address;
    *D_STAT = D_STAT_CIS1;
    *D1_CHCR = DMA_CHCR_START | DMA_CHCR_MODE_CHAIN | DMA_CHCR_DIR_FROM_MEMORY;
}

/**
 * @brief Finish the model's packet.
 * @param channel DMA channel; unused.
 */
void LibObject1751A0::complete_dma(u32 channel)
{
    lib_finish_packet(this);
}

/** @brief Queue the model's DMA submission. */
void LibObject1751A0::render()
{
    resident_dma_queue_push(g_vif1_dma_queue, this);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", build_packet__15LibObject1751A0FPCvPv);

/**
 * @brief Give the centre and half extent of the image's bounding box.
 * @param output Receives the box (LibCullBox).
 * @return Nonzero when the shared object is ready and the box was written.
 */
s32 LibObject1751A0::get_box_cull_center(void* output)
{
    LibVector4 extent;

    if (!reference->unk04)
    {
        return 0;
    }

    LibCullBox* box = static_cast<LibCullBox*>(output);
    extent.x = 0.5f * (box_max.x - box_min.x);
    extent.y = 0.5f * (box_max.y - box_min.y);
    extent.z = 0.5f * (box_max.z - box_min.z);
    extent.w = 1.0f;
    copy_vector(&box->half_extents, &extent);
    extent.x += box_min.x;
    extent.y += box_min.y;
    extent.z += box_min.z;
    copy_vector(&box->center, &extent);
    return 1;
}

/**
 * @brief Transform the bounding sphere's centre into world space; the radius stays.
 * @return Bounding sphere in world space.
 */
const LibVector4* LibObject1751A0::get_bounding_sphere()
{
    LibVector4 center;
    copy_vector(&center, &bounding_sphere);
    center.w = 1.0f;
    vu0_dot_matrix_rows(&transform, &center, &world_bounding_sphere);
    world_bounding_sphere.w = bounding_sphere.w;
    return &world_bounding_sphere;
}

/** @brief Pick the draw bucket from the blend and image state. */
void LibObject1751A0::set_default_draw_bucket()
{
    draw_bucket = blend_mode ? 2 : 0;

    if (draw_flags & 0x1000)
    {
        draw_bucket = 7;
    }
    else if (kind == 5)
    {
        draw_bucket = 8;
    }
    else if (unkae2)
    {
        switch (unkae0)
        {
        case 0:
            draw_bucket = 1;
            break;
        case 1:
            draw_bucket = 5;
            break;
        case 2:
            draw_bucket = 2;
            break;
        case 3:
            draw_bucket = 3;
            break;
        }
    }
}

/** @brief Clear the image and reset the texture state. */
void LibObject1751A0::clear_image()
{
    unk648 = 0;
    image = 0;
    unk624 = 0;
    unk640 = 0;
    reset_texture_uploads();
    memset_guess(&setup, 0, sizeof(setup));
    setup.unpack = VIF_UNPACK(VIF_UNPACK_V4_32, 9, 0x2E0);
    setup.unk10 = 1;
    setup.unk14 = 1;
    setup.unk18 = 1;
    setup.texture_tag = 2 | GIF_TAG_NREG(1);
    setup.texture_registers = 0;
    setup.texture_register_fields.register0 = GIF_REGISTER_AD;
    setup.texture_address = GS_REGISTER_TEX0_1;
    setup.texture_2_address = GS_REGISTER_TEX0_1;
    setup.alpha_tag = 1 | GIF_TAG_NREG(1);
    setup.alpha_registers = 0;
    setup.alpha_register_fields.register0 = GIF_REGISTER_AD;
    setup.alpha_address = GS_REGISTER_ALPHA_1;
    FlushCache(0);

    if (reference)
    {
        reference->func_slot54(1);
    }

    unk620 = 0;
}
