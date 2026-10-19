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

extern "C" void func_004D00B0(void* object);
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_0045F660);

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
    lib_text_init_rectangle((LibObject178750*)object, x, y, width, height);
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
    lib_text_init_rectangle((LibObject178750*)object, x, y, width, height);
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00461B60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00461BA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00461C30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00461E50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00461FA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004621E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00462200);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00462220);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00462240);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00462270);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00462280);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00462290);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004622F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00462300);

void LibClass178600::draw()
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00462320);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004623F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004624E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00462C70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00462FC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00463500);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00463610);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004637A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00463C00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00463C90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00463DD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00463E60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00463FC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00464040);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004642E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00464340);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004643C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00464460);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00464540);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00464590);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004645F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004647E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00464830);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00464870);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004648C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00464900);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00464A30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", __dt__14LibClass174EF0Fv);

/** @brief Initialize drawing storage, bounds, scale, colors, and display flags. */
LibClass174EF0::LibClass174EF0()
{
    unkf4 = 0.0f;
    unkf0 = 0.0f;
    unkec = 0.0f;
    unke8 = 0.0f;
    unk38 = 10;
    unkf8 = 0;
    unkf9 = 1;
    unkfa = 0;
    allocation = 0;
    unk7c = 0;
    unk78 = 0;
    unk84 = 1.0f;
    unk80 = 1.0f;
    unk88 = 0.0f;
    unk8c = 2.0f;
    unk90 = 0;
    unk94 = 0x808080;
    unk98 = 0x020202;
    unk9c = 0;
    unka0 = 0;
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

extern "C" void func_00464870(void* object, float x, float y, float width, float height);
extern "C" s32 func_00464900(void* object, s32 first, s32 capacity, s32 second, s32 third);

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
    func_00464870(object, x, y, width, height);
    state->source = &((LibNumericResourceOwner*)D_001B657C)->slots[slot];
    if (!func_00464900(object, 0, 16, 0, 0))
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

/** Resource header prefix containing section offsets, counts, and total size. */
struct LibResourceHeader {
    u8 unk00[0x10];
    s32 offsets[4];
    s32 unk20, unk24, unk28, unk2c, unk30, unk34, unk38, unk3c;
    s32 size;
};

/** One 0x50-byte resource slot in the runtime table. */
struct LibManagedResourceSlot {
    void* allocation;
    LibResourceHeader* data;
    u8* sections[4];
    s32 unk18, unk1c, unk20, unk24, unk28, unk2c, unk30;
    s32 loaded, unit_count, loaded_units, start, end, unk48;
    u16 identifier;
    u8 flag, active;
};

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
            resident_queue_allocation_release(D_001B65F4, slot->allocation);
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
    source = (LibResourceHeader*)(((u32)allocation + 127) & ~127u);
    func_0013A4C0(source, data, prefix);
    if (remainder_size != 0)
        func_0013A4C0((u8*)source + prefix, remainder, remainder_size);
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
extern "C" s32 lib_queue_display_object(FieldRuntime* runtime, LibClass178A90* object)
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00466E40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00466E70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004670B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00467250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004672C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00467320);

typedef struct LibFieldWidgetState
{
    u8 pad00[0x34];
    u32 unk34;
    u8 pad38;
    u8 unk39;
    u8 pad3a[6];
    u8 storage[0x3C];
} LibFieldWidgetState;
extern "C" s32 func_00467250(void* object, float x, float y);
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
    if (!func_00467250(state->storage, x, y))
    {
        return 0;
    }
    state->unk34 = 8;
    state->unk39 = 1;
    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004673B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_004673C0);

/** Forward the receiver to func_004D00B0. */
void func_00467480(void* object)
{
    func_004D00B0(object);
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00467570);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0045AD10", func_00467AD0);

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

/** Forward the receiver to func_004D00B0. */
void func_0046A3F0(void* object)
{
    func_004D00B0(object);
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
