#include "overlays/lib/dma_callbacks_inlines.h"
#include "include_asm.h"
#include "overlays/lib/text_0045AD10.h"
#include "angle.h"
#include "vu0.h"
#include "clamp.h"
#include "overlays/lib/character_record.h"
#include "overlays/lib/render_buffer.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "sdk/main/libm_guess_0013F3E0.h"
#include "sdk/main/libc_guess_00137290.h"
#include "overlays/lib/text_003F90C0.h"
#include "overlays/lib/text_003E68C0.h"
#include "sdk/main/libdma_0012B2C8.h"
#include "sdk/main/libkernl_00121940.h"
#include "overlays/lib/text_0044ABE0.h"
#include "overlays/lib/text_004BD360.h"
#include "main/resident_data.h"
#include "overlays/lib/image_capture.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/lib/transform_owner_inlines.h"
#include "main/system.h"
#include "main/utility.h"
#include "main/dma_queue.h"
#include "overlays/lib/model.h"
#include "overlays/lib/text_004DD440.h"
#include "overlays/lib/emission.h"

/** LibShortBitTableHeader with a colour after the records offset; the words start at 0x10. */
struct LibColorBitTableHeader
{
    s16 bit_count;
    s16 unk02;
    s32 records_offset;
    float color[4];
    u32 unk18[2];
    u32 words[1];
};

/** LibColorBitTableHeader whose colour holds texture offsets, a scale and a mapping mode. */
struct LibOffsetBitTableHeader
{
    s16 bit_count;
    s16 unk02;
    s32 records_offset;
    float offset[2];
    float scale;
    s32 mapping;
    u32 unk18[2];
    u32 words[1];
};

/** Record in a resource entry's record list; each starts with its size at 0x8. */
struct LibEntryRecord
{
    u32 unk00[2];
    s32 size;
};

/**
 * @brief Return the record at the cursor and move past it, when the entry is complete or has bit `index`.
 * @param entry Resource entry.
 * @param cursor Entry's record cursor.
 * @param index Bit index.
 * @param size Receives the record's size.
 * @return Record, or null.
 */
static inline u8* lib_entry_read_record(LibClass1779F0* entry, u8*& cursor, u32 index, u32* size)
{
    if (entry->unk19 || ((entry->bits.words[index / 32] >> (index % 32)) & 1))
    {
        *size = reinterpret_cast<LibEntryRecord*>(cursor)->size;
        u8* record = cursor;
        cursor += reinterpret_cast<LibEntryRecord*>(cursor)->size;
        return record;
    }

    return 0;
}

/** Bit table at the start of a resource entry's data: one bit per record, then the records at records_offset. */
struct LibBitTableHeader
{
    u32 bit_count;
    s32 unk04;
    s32 records_offset;
    u32 unk0c;
    u32 words[1];
};

/** LibBitTableHeader with a halfword bit count and the records offset in the second word. */
struct LibShortBitTableHeader
{
    s16 bit_count;
    s16 unk02;
    s32 records_offset;
    u32 unk08;
    u32 unk0c;
    u32 words[1];
};

/** LibClass174C90 subclass with vtable D_00174C70 in main data. */
class LibClass174C70 : public LibClass174C90
{
public:
    LibClass174C70();

    virtual ~LibClass174C70();

    /**
     * @brief Return the entry's type code.
     * @return 43.
     */
    virtual s32 func_slot14();

    /**
     * @brief Use a resource's bit table and the records after it, without owning them.
     * @param value Resource data.
     */
    virtual void set_borrowed_data(void* value);

    /**
     * @brief Return the record at the cursor and move past it, when the entry is complete or has bit `index`.
     * @param index Bit index.
     * @param size Receives the record's size.
     * @return Record, or null.
     */
    virtual u8* read_record(u32 index, u32* size);

    LibBitTableHeader* table;
    u8* records;
    u8* cursor;
};

/** LibClass174C90 subclass with vtable D_00174CB0 in main data. */
class LibClass174CB0 : public LibClass174C90
{
public:
    LibClass174CB0();

    virtual ~LibClass174CB0();

    /**
     * @brief Return the entry's type code.
     * @return 43.
     */
    virtual s32 func_slot14();

    /**
     * @brief Use a resource's bit table and the records after it, without owning them.
     * @param value Resource data.
     */
    virtual void set_borrowed_data(void* value);

    /**
     * @brief Return the record at the cursor and move past it, when the entry is complete or has bit `index`.
     * @param index Bit index.
     * @param size Receives the record's size.
     * @return Record, or null.
     */
    virtual u8* read_record(u32 index, u32* size);

    LibShortBitTableHeader* table;
    u8* records;
    u8* cursor;
};

/** LibClass174C90 subclass with vtable D_00174D10 in main data. */
class LibClass174D10 : public LibClass174C90
{
public:
    /** @brief Start as an entry of kind 5 with blend mode 0. */
    LibClass174D10();

    virtual ~LibClass174D10();

    /**
     * @brief Return the entry's type code.
     * @return 40.
     */
    virtual s32 func_slot14();

    /**
     * @brief Use a resource's bit table, records and two offsets without owning them.
     * @param value Resource data.
     */
    virtual void set_borrowed_data(void* value);

    /**
     * @brief Return the record at the cursor and move past it, when the entry is complete or has bit `index`.
     * @param index Bit index.
     * @param size Receives the record's size.
     * @return Record, or null.
     */
    virtual u8* read_record(u32 index, u32* size);

    /**
     * @brief Note whether every bit is set; in mapping mode 2 scroll the offsets by the camera's reflection off the
     *        model, otherwise count the blend mode down. Rewind the records.
     * @param root Model transform; unused.
     * @return Zero on the step the countdown ends, otherwise one.
     */
    virtual s32 func_slot1C(LibTransform* root);

    /**
     * @brief Pick the blend mode: offsets other than zero mark the owning list the first time; zero offsets use
     *        mode 2 once the list was marked.
     */
    void update_blend_mode()
    {
        if (offset_u != 0.0f || offset_v != 0.0f)
        {
            if (blend_mode == 0)
            {
                if (unk18 != 1 && list != 0)
                {
                    list->unk8d_1 = 1;
                }

                unk18 = 1;
                blend_mode = 0;
            }
        }
        else if (unk18)
        {
            blend_mode = 2;
        }
    }

    /**
     * @brief Set the first offset and refresh the blend mode.
     * @param value Offset.
     */
    void set_offset_u(float value)
    {
        offset_u = value;
        update_blend_mode();
    }

    /**
     * @brief Set the second offset and refresh the blend mode.
     * @param value Offset.
     */
    void set_offset_v(float value)
    {
        offset_v = value;
        update_blend_mode();
    }

    LibOffsetBitTableHeader* table;
    u8* records;
    u8* cursor;
    u8 unk3c[4];
    float offset_u;
    float offset_v;
    u8 unk48[8];
    s32 blend_mode;
};

/** LibClass1779F0 subclass with vtable D_00174D30 in main data; only its destructors are known. */
class LibClass174D30 : public LibClass1779F0
{
public:
    /** @brief Start unattached, with unk0e set to two. */
    LibClass174D30();

    virtual ~LibClass174D30()
    {
    }

    /**
     * @brief Return the entry's type code.
     * @return Six.
     */
    virtual s32 func_slot14();
};

/** LibClass174D30 subclass with vtable D_00174D50 in main data. */
class LibClass174D50 : public LibClass174D30
{
public:
    /** @brief Start as an entry of kind 6 with a white colour. */
    LibClass174D50();

    virtual ~LibClass174D50();

    /**
     * @brief Return the entry's type code.
     * @return 36.
     */
    virtual s32 func_slot14();

    /**
     * @brief Use a resource's bit table, records and colour without owning them; a colour other than white
     *        marks the owning list.
     * @param value Resource data.
     */
    virtual void set_borrowed_data(void* value);

    /**
     * @brief Return the record at the cursor and move past it, when the entry is complete or has bit `index`.
     * @param index Bit index.
     * @param size Receives the record's size.
     * @return Record, or null.
     */
    virtual u8* read_record(u32 index, u32* size);

    /**
     * @brief Note whether every bit is set, count the blend mode down and rewind the records.
     * @param root Model transform; unused.
     * @return Zero on the step the countdown ends, otherwise one.
     */
    virtual s32 func_slot1C(LibTransform* root);

    LibColorBitTableHeader* table;
    u8* records;
    u8* cursor;
    u8 unk3c[4];
    FieldVec4B color;
    s32 blend_mode;
};

/** Transform owner with vtable D_001747C0 in main data that expires the cached texture 1 when it's drawn. */
class LibClass1747C0 : public LibTransformOwner
{
public:
    virtual ~LibClass1747C0();

    /** @brief Do nothing. */
    virtual void render();

    /** @brief Draw in bucket 8. */
    virtual void set_default_draw_bucket();

    /**
     * @brief Return the shared bounding sphere every object of this class uses.
     * @return Bounding sphere.
     */
    virtual const LibVector4* get_bounding_sphere();

    /**
     * @brief Expire every cached copy of texture 1.
     * @param matrix Unused.
     * @param context Unused.
     */
    virtual void build_packet(const void* matrix, void* context);
};

class LibCameraContext;

#define LIB_CLASS_1745F0_STRIP_WORDS 64
#define LIB_CLASS_1745F0_CAPTURE_COUNT 5

/** List object that keeps up to five VRAM captures and their positions, with vtable D_1745F0 in main data. */
class LibClass1745F0 : public LibListObject
{
public:
    /**
     * @brief Set up the capture positions and one capture.
     * @param display Display the captures read from.
     * @param unk78 Object whose transform the update reads.
     */
    LibClass1745F0(LibCameraContext* display, void* unk78);

    /** @brief Destroy the captures, then the list object. */
    virtual ~LibClass1745F0();

    /**
     * @brief Return the fixed list kind 14.
     * @return Always 14.
     */
    virtual s32 get_default_list_kind();

    /** @brief Destroy the captures, then queue the object for release. */
    virtual void destroy();

    /** @brief Queue this frame's captures. */
    virtual void update();

    /**
     * @brief Destroy the current captures and create new ones, registering each with the renderer.
     * @param count Captures to create.
     */
    void set_capture_count(s32 count);

    /** @brief Detach and destroy every capture. */
    void release_captures()
    {
        for (s32 i = 0; i < LIB_CLASS_1745F0_CAPTURE_COUNT; i++)
        {
            if (captures[i])
            {
                lib_object_detach_owner(captures[i]);
                captures[i]->destroy();
                captures[i] = 0;
            }
        }
    }

    u8 unk14[0xC];
    FieldVec4A positions[LIB_CLASS_1745F0_CAPTURE_COUNT];
    s32 capture_count;
    LibCameraContext* display;
    void* unk78;
    u8 unk7c[8];
    float unk84;
    u8 unk88;
    u8 recreated;
    u8 unk8a[6];
    u32 strips[LIB_CLASS_1745F0_CAPTURE_COUNT][LIB_CLASS_1745F0_STRIP_WORDS];
    LibImageCapture* captures[LIB_CLASS_1745F0_CAPTURE_COUNT];
};

/** Corner of a LibClass174790 quad, relative to the widget's position. */
struct LibQuadCorner
{
    float x;
    float y;
};

/** Quad widget that grows in and then settles, with vtable D_174790 in main data. */
class LibClass174790 : public LibWidget
{
public:
    /** @brief Release the drawing storage and the widget base. */
    virtual ~LibClass174790()
    {
    }

    /** @brief Advance the grow-in animation and request a redraw. */
    virtual void func_00413D20();

    /** @brief Write the quad into the drawing packet. */
    virtual void draw();

    /**
     * @brief Set the quad's position, color and shape, and allocate its drawing storage.
     * @param color Packed vertex color.
     * @param mirrored Nonzero to mirror the quad horizontally.
     * @param x Horizontal position.
     * @param y Vertical position.
     * @param width Extra width added to the quad.
     * @return One on success, or zero if the storage couldn't be allocated.
     */
    s32 init(u32 color, u32 mirrored, float x, float y, float width);

    LibStorageBlock0C storage;
    u8 unk4c[4];
    LibQuadCorner corners[4];
    u32 color;
    float scale_x;
    float scale_y;
    float speed;
    s32 state;
};

/** Container with a quad frame and a text line that fade in, wait and fade out; vtable D_1746D0 in main data. */
class LibClass1746D0 : public LibContainer
{
public:
    /** @brief Destroy the text, the frame and the container. */
    virtual ~LibClass1746D0();

    /**
     * @brief Run the show, wait and fade-out steps.
     * @param first First update flag.
     * @param second Second update flag.
     * @param third Third update flag.
     */
    virtual void func_00412C40(u32 first, u32 second, u32 third);

    /**
     * @brief Set up the frame and the text and attach them.
     * @param flags Bit 0 puts the frame at the right edge, bit 1 at the bottom.
     * @param color Index into the frame color table.
     * @param slot Text resource slot.
     * @param key Text resource key.
     * @return One on success, otherwise zero.
     */
    s32 init(u32 flags, s32 color, s32 slot, s32 key);

    LibClass174790 frame;
    LibTextWidget text;
    float timer;
    s32 state;
};

/** Packed frame colors that LibClass1746D0::init picks from. */
extern "C" const u32 D_004ED130[];

/** Hardware address register of DMA channel 1 (VIF1). Proposed for ee.h next to D1_QWC. */
#define D1_MADR ((volatile u32*)0x10009010)

extern "C" u64 D_001B6560;

/** Transform owner that sends its own packet on VIF1, with vtable D_174840 in main data. */
class LibClass174840 : public LibTransformOwner, public DmaSubmission
{
public:
    /**
     * @brief Set up the transform and allocate the packet.
     * @param unk94 Stored at unk94.
     */
    LibClass174840(void* unk94);

    /** @brief Delete the packet and destroy the transform owner. */
    virtual ~LibClass174840();

    /**
     * @brief Build the packet for this frame.
     * @param matrix Matrix supplied by the caller.
     * @param context Opaque caller context.
     */
    virtual void build_packet(const void* matrix, void* context);

    /** @brief Detach from the owner and release the transform. */
    virtual void destroy();

    /** @brief Queue the packet on VIF1. */
    virtual void render();

    /** @brief Draw in bucket 8. */
    virtual void set_default_draw_bucket();

    /**
     * @brief Return the bounding sphere D_00508230.
     * @return Bounding sphere.
     */
    virtual const LibVector4* get_bounding_sphere();

    /**
     * @brief Send the packet's pending data on VIF1 in normal mode.
     * @param channel DMA channel; unused.
     */
    virtual void submit_dma(u32 channel);

    /**
     * @brief Finish the packet.
     * @param channel DMA channel; unused.
     */
    virtual void complete_dma(u32 channel);

    void* unk94;
    LibPacketBuffer* packet;
    u8 unk9c;
    u8 unk9d;
    u8 unk9e[2];
    u32 qwc;
    u8 unka4[4];
    u32 unka8;
    s16 unkac;
    s16 unkae;
    float unkb0;
    s32 unkb4;
    u8 unkb8[0x18];
    void* unkd0;
    s32 unkd4;
    u8 unkd8[2];
    s16 unkda;
    float unkdc;
    s32 unke0;
    u32 unke4;
};


extern "C" void func_004A8F10(void* object);

/** Partial indexed-resource fields at CC and D0. */
typedef struct LibIndexedResourceState
{
    u8 pad00[0xCC];
    s32 current;
    s32 selected;
} LibIndexedResourceState;

extern "C" s32 func_00464EF0(FieldRuntime* runtime, s32 index);

extern "C" s32 func_00467800(ItemCreationClass175110* object, s32 resource, void* source, const LibImageFormat* format, u32 first, u8 second, float x,
                             float y);

extern "C" void func_00465A90(void* owner, LibCallbackTransform* object);

extern "C" ResidentDmaQueue* g_vif1_dma_queue;
extern "C" ResidentDmaQueue* D_001B6604;

extern "C" void func_00454E90(LibDrawBuffer* buffer);

extern "C" void func_004D5A50(LibDrawBuffer* buffer, u32* commands);

/**
 * @brief Destroy the current captures and create new ones, registering each with the renderer.
 * @param count Captures to create.
 */
void LibClass1745F0::set_capture_count(s32 count)
{
    capture_count = count;
    release_captures();

    for (s32 i = 0; i < count; i++)
    {
        captures[i] = new (0) LibImageCapture;

        if (captures[i])
        {
            ((LibUpdateList*)g_renderer)->append_node(captures[i], -1);
        }
    }

    recreated = 1;
}

/** @brief Destroy the captures, then queue the object for release. */
void LibClass1745F0::destroy()
{
    release_captures();
    resident_enqueue_object(g_resident_release_queues, this);
}

/** @brief Destroy the captures, then the list object. */
LibClass1745F0::~LibClass1745F0()
{
    release_captures();
}

/**
 * @brief Set up the capture positions and one capture.
 * @param display Display the captures read from.
 * @param unk78 Object whose transform the update reads.
 */
LibClass1745F0::LibClass1745F0(LibCameraContext* display, void* unk78)
{
    positions[0] = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    positions[1] = FieldVec4A(160.0f, 0.0f, 0.0f, 1.0f);
    positions[2] = FieldVec4A(-160.0f, 0.0f, 0.0f, 1.0f);
    positions[3] = FieldVec4A(80.0f, 0.0f, 0.0f, 1.0f);
    positions[4] = FieldVec4A(-80.0f, 0.0f, 0.0f, 1.0f);
    this->display = display;
    this->unk78 = unk78;
    unk88 = 1;
    recreated = 1;
    unk84 = 10.0f;

    for (s32 i = 0; i < LIB_CLASS_1745F0_CAPTURE_COUNT; i++)
    {
        captures[i] = 0;

        for (s32 j = 0; j < LIB_CLASS_1745F0_STRIP_WORDS; j++)
        {
            strips[i][j] = 0;
        }
    }

    set_capture_count(1);
}

#pragma inline_depth(7)

/** @brief Destroy the transform receiver. */
LibCallbackTransform::~LibCallbackTransform()
{
}

/** @brief Run the default transform state hook. */
void LibCallbackTransform::func_0044B100(u32 first, u32 second, u32 third)
{
}

/**
 * @brief Set transform codes and the third coordinate while preserving x and y.
 * @param code Transform code.
 * @param first First byte value.
 * @param z Third coordinate.
 * @param second Word value.
 * @param third Second byte value.
 */
void LibCallbackTransform::set_codes_and_z(s32 code, u32 first, float z, u32 second, u32 third)
{
    if (code != 0)
    {
        z = (float)(code * 16);
        first = 9;
        second = 0xFFFFFE - code * 16;
    }

    unka0 = code;
    unka8 = first;
    unka4 = second;

    if (code >= 13 && code < 21)
    {
        third = 255 - (code - 13);
    }

    unka9 = third;
    float x = translation.x;
    float y = translation.y;
    translation.x = x;
    translation.y = y;
    translation.z = z;
    translation.w = 1.0f;
    geometry_dirty = 1;
}

/**
 * @brief Move the transform in x and y, keeping its z, and mark its geometry for rebuilding.
 * @param x Horizontal position.
 * @param y Vertical position.
 */
void LibCallbackTransform::set_position(float x, float y)
{
    float z = translation.z;
    translation.x = x;
    translation.y = y;
    translation.z = z;
    translation.w = 1.0f;
    geometry_dirty = 1;
}

/** @brief Detach the transform once and mark it released. */
extern "C" void func_0044B1C0(LibCallbackTransform* object)
{
    if (object->unkaf == 0)
    {
        if (object->unk94 != 0)
        {
            func_00465A90(object->unk94, object);
        }

        object->LibTransformOwner::destroy();
        object->unkaf = 1;
    }
}

/** @brief Detach this transform from its owner when attached. */
extern "C" void func_0044B210(LibCallbackTransform* object)
{
    if (object->unk94 != 0)
    {
        func_00465A90(object->unk94, object);
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", build_packet__20LibCallbackTransformFPCvPv);

/** @brief Initialize transform flags and drawing modes after the base receivers. */
LibCallbackTransform::LibCallbackTransform()
{
    draw_flags |= 0x400;
    unk94 = 0;
    unkaf = 0;
    geometry_dirty = 1;
    unkad = 1;
    unkac = 1;
    unkab = 1;
    unkaa = 2;
}

#define GS_REGISTER_SCISSOR_2 0x41
#define GS_SCISSOR(x0, x1, y0, y1) ((u64)(x0) | ((u64)(x1) << 16) | ((u64)(y0) << 32) | ((u64)(y1) << 48))
#define GIF_TAG_NLOOP(count) ((u64)(count))

/** @brief Write the widget clipping bounds into its drawing packet. */
void ItemCreationClass1746A0::draw()
{
    if (unk3b)
    {
        return;
    }

    u64 scissor;

    if (unk50)
    {
        scissor = GS_SCISSOR(0, g_field_runtime->unk52c, 0, g_field_runtime->unk530);
    }
    else
    {
        s32 x0;
        s32 x1;
        s32 y0;
        s32 y1;
        FieldRuntime* runtime = g_field_runtime;
        const LibVector4* origin = &container->translation;

        float left = origin->x + unk18.unk00;
        float scale_x = runtime->screen_scale_x / 16.0f;
        x0 = left * scale_x;

        if (x0 < 0)
        {
            x0 = 0;
        }

        x1 = scale_x * (left + unk18.unk08);

        if (x1 > runtime->unk52c)
        {
            x1 = runtime->unk52c;
        }

        float top = origin->y + unk18.unk04;
        float scale_y = runtime->screen_scale_y / 16.0f;
        y0 = top * scale_y;

        if (y0 < 0)
        {
            y0 = 0;
        }

        y1 = scale_y * (top + unk18.unk0c);

        if (y1 > runtime->unk530)
        {
            y1 = runtime->unk530;
        }

        scissor = GS_SCISSOR(x0, x1, y0, y1);
    }

    u64* cursor = reinterpret_cast<u64*>(unk40.dma_address);
    packet_tag = cursor;
    packet = cursor;
    cursor[2] = GIF_TAG_NREG(1) | GIF_TAG_EOP | GIF_TAG_NLOOP(1);
    cursor[3] = GIF_REGISTER_AD;
    cursor[4] = scissor;
    cursor[5] = GS_REGISTER_SCISSOR_2;
    cursor += 6;
    *packet_tag = DMA_TAG((reinterpret_cast<u32>(cursor) - reinterpret_cast<u32>(packet_tag) - LIB_DRAW_QWORD_SIZE) / LIB_DRAW_QWORD_SIZE, DMA_TAG_ID_END, 0);
    unk3b = 1;
}

/**
 * @brief Initialize a widget that restores the runtime clipping bounds.
 * @param object Clipping widget.
 * @param code Retained initialization argument; this routine does not use it.
 * @return True when the six-entry drawing storage was allocated.
 */
extern "C" bool lib_scissor_init_reset(ItemCreationClass1746A0* object, s32 code)
{
    object->unk50 = 1;
    object->needs_redraw = 1;
    bool success;

    if (!lib_allocate_drawing_storage(&object->unk40, 6))
    {
        success = false;
    }
    else
    {
        object->unk39 = 1;
        success = true;
    }

    return success;
}

/**
 * @brief Initialize a widget that sets a clipping rectangle.
 * @param object Clipping widget.
 * @param x Rectangle's horizontal position.
 * @param y Rectangle's vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return True when the six-entry drawing storage was allocated.
 */
extern "C" bool lib_scissor_init_rectangle(ItemCreationClass1746A0* object, float x, float y, float width, float height)
{
    object->unk18.unk00 = x;
    object->unk18.unk04 = y;
    object->unk18.unk08 = width;
    object->unk18.unk0c = height;
    object->unk50 = 0;
    object->needs_redraw = 1;
    bool success;

    if (!lib_allocate_drawing_storage(&object->unk40, 6))
    {
        success = false;
    }
    else
    {
        object->unk39 = 1;
        success = true;
    }

    return success;
}

/** @brief Destroy the text, the frame and the container. */
LibClass1746D0::~LibClass1746D0()
{
}

/**
 * @brief Run the show, wait and fade-out steps.
 * @param first First update flag.
 * @param second Second update flag.
 * @param third Third update flag.
 */
void LibClass1746D0::func_00412C40(u32 first, u32 second, u32 third)
{
    switch (state)
    {
    case 0:
        if (frame.state == 1)
        {
            timer = 15.0f;
            state++;
        }

        break;
    case 1:
        timer -= g_field_runtime->rate;

        if (timer <= 0.0f)
        {
            text.unk3d = 1;
            text.draw_alpha = 0.0f;
            text.needs_redraw = 1;
            state++;
        }

        break;
    case 2:
    {
        float alpha = text.draw_alpha;
        alpha += 2.1333334f * field_rate(g_field_runtime);

        if (128.0f <= alpha)
        {
            alpha = 128.0f;
            state++;
        }

        text.draw_alpha = alpha;
        text.needs_redraw = 1;
        break;
    }
    case 3:
        if (frame.state == 2)
        {
            timer = 150.0f;
            state++;
        }

        break;
    case 4:
        timer -= g_field_runtime->rate;

        if (timer <= 0.0f)
        {
            state++;
        }

        break;
    case 5:
    {
        float alpha = unkE0;
        alpha -= 4.266667f * field_rate(g_field_runtime);

        if (alpha <= 0.0f)
        {
            destroy();
        }

        unkE0 = alpha;
        geometry_dirty = 1;
        break;
    }
    }
}

/**
 * @brief Lay out the label: its text 40 units in from the chosen corner (bit 0 of flags: right, bit 1: bottom) and
 *        the frame around it in one of the packed colors.
 * @param flags Corner bits.
 * @param color Index into the frame colors.
 * @param slot Text resource slot.
 * @param key Text key.
 * @return 1 on success, 0 when the text or frame can't be set up.
 */
s32 LibClass1746D0::init(u32 flags, s32 color, s32 slot, s32 key)
{
    lib_container_init(this, 2, 0.0f, 0.0f, 0, 0.0f, 0);

    if (!lib_text_init_resource_rectangle(&text, slot, key, 1, 0.0f, 0.0f, 0.0f, 0.0f))
    {
        return 0;
    }

    text.unk3d = 0;
    LibTextExtent* bounds = lib_text_measure_bounds(&text);
    float text_x = 40.0f;
    float width = text_x + bounds->width;
    float frame_x;
    float text_y;

    if ((flags & 1) == 0)
    {
        frame_x = 0.0f;
    }
    else
    {
        frame_x = g_field_runtime->unk524;
        text_x = frame_x - width;
    }

    if ((flags & 2) == 0)
    {
        text_y = 32.0f;
    }
    else
    {
        text_y = g_field_runtime->unk528 - (40.0f + bounds->height);
    }

    float frame_y = text_y + bounds->height;

    text.unk18.unk00 = text_x;
    text.unk18.unk04 = text_y;
    text.needs_redraw = 1;

    if (!frame.init(D_004ED130[color], flags & 1, frame_x, frame_y, width))
    {
        return 0;
    }

    lib_container_attach_widget(this, &frame);
    lib_container_attach_widget(this, &text);
    state = 0;
    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", draw__14LibClass174790Fv);

/** @brief Advance the grow-in animation and request a redraw. */
void LibClass174790::func_00413D20()
{
    switch (state)
    {
    case 0:
    {
        float alpha = draw_alpha;
        alpha += 6.0f;

        if (!(alpha < 128.0f))
        {
            alpha = 128.0f;
        }

        draw_alpha = alpha;
        float scale = scale_x;
        scale += speed;
        scale_x = scale;

        if (!(scale < 1.0f))
        {
            state++;
        }

        break;
    }
    case 1:
    {
        float velocity = speed;
        velocity += -0.0075f;

        if (velocity < -0.0075f)
        {
            velocity = -0.0075f;
        }

        speed = velocity;
        float scale = scale_x;
        scale += velocity;

        if (scale < 1.0f)
        {
            scale = 1.0f;
        }

        scale_x = scale;
        float stretch = scale_y;
        stretch -= 0.02f;

        if (stretch <= 1.0f)
        {
            stretch = 1.0f;
            state++;
        }

        scale_y = stretch;
        break;
    }
    }

    needs_redraw = 1;
}

/**
 * @brief Set the quad's position, color and shape, and allocate its drawing storage.
 * @param color Packed vertex color.
 * @param mirrored Nonzero to mirror the quad horizontally.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Extra width added to the quad.
 * @return One on success, or zero if the storage couldn't be allocated.
 */
s32 LibClass174790::init(u32 color, u32 mirrored, float x, float y, float width)
{
    unk18.unk00 = x;
    unk18.unk04 = y;
    this->color = color;

    if (!lib_allocate_drawing_storage(&storage, 14))
    {
        return 0;
    }

    float left = 0.0f;
    float middle = 64.0f + width;
    float right = 80.0f + width;

    if (mirrored)
    {
        left = -left;
        middle = -middle;
        right = -right;
    }

    corners[0].x = left;
    corners[1].x = middle;
    corners[2].x = left;
    corners[3].x = right;
    corners[0].y = -12.0f;
    corners[1].y = -12.0f;
    corners[2].y = 8.0f;
    corners[3].y = 8.0f;
    draw_alpha = 0.0f;
    scale_x = 0.0f;
    scale_y = 2.24f;
    speed = 0.07f;
    state = 0;
    unk39 = 1;
    return 1;
}

LibClass1747C0::~LibClass1747C0()
{
}

/** @brief Draw in bucket 8. */
void LibClass1747C0::set_default_draw_bucket()
{
    draw_bucket = 8;
}

/** @brief Do nothing. */
void LibClass1747C0::render()
{
}

extern "C" float D_00508230[];

/**
 * @brief Return the shared bounding sphere every object of this class uses.
 * @return Bounding sphere.
 */
const LibVector4* LibClass1747C0::get_bounding_sphere()
{
    return reinterpret_cast<const LibVector4*>(&D_00508230[4]);
}

/**
 * @brief Expire every cached copy of texture 1.
 * @param matrix Unused.
 * @param context Unused.
 */
void LibClass1747C0::build_packet(const void* matrix, void* context)
{
    g_texture_cache->expire_texture(1);
}

/**
 * @brief Send the packet's pending data on VIF1 in normal mode.
 * @param channel DMA channel; unused.
 */
void LibClass174840::submit_dma(u32 channel)
{
    dma_pending = 1;
    *D1_QWC = qwc;
    *D1_MADR = resident_packet_get_address(packet);
    *D_STAT = D_STAT_CIS1;
    *D1_CHCR = DMA_CHCR_START | DMA_CHCR_DIR_FROM_MEMORY;
}

/**
 * @brief Finish the packet once its transfer is done.
 * @param channel DMA channel; unused.
 */
void LibClass174840::complete_dma(u32 channel)
{
    lib_finish_packet(this);
}

/** @brief Queue the receiver's DMA callback interface. */
extern "C" s32 func_0044C110(LibCallbackTransform* object)
{
    LibDmaCallbacks* submission = static_cast<LibDmaCallbacks*>(object);
    return resident_dma_queue_push(g_vif1_dma_queue, reinterpret_cast<DmaSubmission*>(submission));
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044C140);

/** @brief Delete the packet and destroy the object. */
LibClass174840::~LibClass174840()
{
    delete packet;
}

/**
 * @brief Set up the transform and allocate the packet.
 * @param unk94 Stored at unk94.
 */
LibClass174840::LibClass174840(void* unk94)
{
    this->unk94 = unk94;
    unk9c = 0;
    unk9d = 0;
    unk65 = 0;
    type_id = 0x900;
    draw_flags = 0x400;
    unka8 = 0;
    unkac = 0;
    unkae = 0;
    unkb0 = 15632.07421875f;
    unkb4 = 1;
    unkd4 = 10;
    unkd0 = unkd8;
    unkdc = 15632.07421875f;
    unke0 = 1;
    unkda = 0;
    unke4 = 0;
    packet = new (0) LibPacketBuffer(0x80);
    D_001B6560 = 0;
}

/**
 * @brief Set the receiver's byte at offset 0x60 to 8.
 * @param object Receiver to update.
 */
extern "C" void func_0044D070(LibObjectByte60* object)
{
    object->unk60 = 8;
}

/**
 * @brief Return the address of D_00508230.
 * @return The data symbol's address.
 */
extern "C" const void* func_0044D080(void)
{
    return D_00508230;
}

/**
 * @brief Clear the intrusive owner and invoke the base transform release.
 * @param object Transform owner to detach.
 */
extern "C" void func_0044D090(LibTransformOwner* object)
{
    object->owner = 0;
    object->LibTransformOwner::destroy();
}

/** @brief Update the transform and mark the renderer's first pass ready. */
void LibClass1748D0::update()
{
    LibTransform::update();
    static_cast<LibRenderer*>(g_renderer)->unk4458->unk9c = 1;
}

/**
 * @brief Send the packet on VIF1 in normal mode.
 * @param channel DMA channel; unused.
 */
void LibClass1748D0::submit_dma(u32 channel)
{
    dma_pending = 1;
    *D1_QWC = qwc;
    *D1_MADR = resident_packet_get_address(packet);
    *D_STAT = D_STAT_CIS1;
    *D1_CHCR = DMA_CHCR_START | DMA_CHCR_DIR_FROM_MEMORY;
}

/**
 * @brief Finish the packet.
 * @param channel DMA channel; unused.
 */
void LibClass1748D0::complete_dma(u32 channel)
{
    lib_finish_packet(this);
}

/** @brief Close the packet with a DIRECTHL tag for its size and queue it on VIF1. */
void LibClass1748D0::render()
{
    qwc = resident_packet_end_unmask_path3(packet);
    *packet_tag = VIF_DIRECTHL(qwc - 2);
    resident_dma_queue_push(g_vif1_dma_queue, this);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044D1D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044D600);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044D9C0);

/** Packet that sets context 1's depth buffer, depth test and clamping for the object's drawing. */
struct LibDepthStatePacket
{
    GsGifTag tag;
    GsRegisterValue registers[3];
};

/**
 * @brief Add the depth state packet to the object's packet: the display's depth buffer with writes enabled, the depth
 * test, and the clamp mode.
 * @param object Object whose packet to extend.
 */
extern "C" void func_0044E080(LibClass1748D0* object)
{
    if (object->packet == 0)
    {
        return;
    }

    LibDepthStatePacket* state = reinterpret_cast<LibDepthStatePacket*>(resident_packet_reserve(object->packet, 0));
    state->tag.tag = GIF_TAG_NREG(1) | 3;
    state->tag.registers = 0;
    state->tag.fields.register0 = GIF_REGISTER_AD;
    state->registers[0].data = *reinterpret_cast<const u32*>(&static_cast<LibRenderer*>(g_renderer)->display->buffers[0].environment.context1.depth_buffer);
    state->registers[0].address = GS_REGISTER_ZBUF_1;
    state->registers[1].data = 0x5000B;
    state->registers[1].address = GS_REGISTER_TEST_1;
    state->registers[2].data = 0xFFFFFFF0ULL;
    state->registers[2].address = GS_REGISTER_CLAMP_1;
    resident_packet_align_cursor(object->packet, reinterpret_cast<u8*>(state + 1));
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", build_packet__14LibClass1748D0FPCvPv);

/**
 * @brief Place the bounding sphere at the transform's origin, with the cull radius.
 * @return Bounding sphere.
 */
const LibVector4* LibClass1748D0::get_bounding_sphere()
{
    LibVector4 origin;
    origin.w = 1.0f;
    origin.x = 0.0f;
    origin.y = 0.0f;
    origin.z = 0.0f;
    vu0_dot_matrix_rows(&transform, &origin, &bounding_sphere);
    bounding_sphere.w = unk248;
    return &bounding_sphere;
}

/** @brief Delete the packet buffer. */
LibClass1748D0::~LibClass1748D0()
{
    delete packet;
}

/** LibClass1748D0 with its own packet builder, with vtables D_174970 and D_1749F4 in main data. */
class LibClass174970 : public LibClass1748D0
{
public:
    /** @brief Start with type ID 0xA02 and no buffers. */
    LibClass174970();

    /** @brief Destroy the transform. */
    virtual ~LibClass174970();

    virtual void build_packet(const void* matrix, void* context);

    /**
     * @brief Set the grid size and replace the packet buffer with one big enough for it.
     * @param columns Number of columns.
     * @param rows Number of rows.
     */
    void set_grid_size(s32 columns, s32 rows);

    u8 unk260[0x20];
    s32 columns;
    s32 rows;
};

/** LibClass1748D0 that LibClass174AC0 and LibClass174B70 build on, with vtables D_174A10 and D_174A94 in main data. */
class LibClass174A10 : public LibClass1748D0
{
public:
    /** @brief Construct the transform. */
    LibClass174A10()
    {
    }

    /** @brief Destroy the transform. */
    virtual ~LibClass174A10()
    {
    }
};

/** LibClass174A10 with a sample grid and two angle setters, with vtables D_174AC0 and D_174B44 in main data. */
class LibClass174AC0 : public LibClass174A10
{
public:
    /** @brief Start with type ID 0xA02 and no buffers. */
    LibClass174AC0();

    /** @brief Free the sample buffer. */
    virtual ~LibClass174AC0();

    virtual void build_packet(const void* matrix, void* context);

    virtual void func_0044FDA0(s32 columns, s32 rows);

    /**
     * @brief Store three values: the first as degrees, the third as turns.
     * @param values Three values.
     */
    virtual void func_00451AD0(const float* values);

    /**
     * @brief Store three values, the first and third as degrees.
     * @param values Three values.
     */
    virtual void func_00451B20(const float* values);

    s32 columns;
    s32 rows;
    float unk268;
    float unk26c;
    float unk270;
    float unk274;
    float unk278;
    float unk27c;
    void* samples;
};

/** LibClass174A10 with a sample grid and two setters, with vtables D_174B70 and D_174BF4 in main data. */
class LibClass174B70 : public LibClass174A10
{
public:
    /** @brief Start with type ID 0xA01 and no buffers. */
    LibClass174B70();

    /** @brief Free the sample buffer. */
    virtual ~LibClass174B70();

    virtual void build_packet(const void* matrix, void* context);

    virtual void func_00451850(s32 columns, s32 rows);

    /**
     * @brief Store three values, the third as turns.
     * @param values Three values.
     */
    virtual void func_00451A60(const float* values);

    /**
     * @brief Store three values, the first as degrees.
     * @param values Three values.
     */
    virtual void func_00451AA0(const float* values);

    s32 columns;
    s32 rows;
    float unk268;
    float unk26c;
    float unk270;
    float unk274;
    float unk278;
    float unk27c;
    void* samples;
};

/** @brief Start with no packet buffer, type ID 0xA00 and the class's draw bucket. */
LibClass1748D0::LibClass1748D0()
{
    packet = 0;
    unk65 = 0;
    type_id = 0xA00;
    unk248 = 1000.0f;
    unk244 = 0;
    unk245 = 1;
    unk24c = 1.0f;
    unk250 = 1.0f;
    set_default_draw_bucket();
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", build_packet__14LibClass174970FPCvPv);

/** @brief Destroy the transform. */
LibClass174970::~LibClass174970()
{
}

/**
 * @brief Set the grid size and replace the packet buffer with one big enough for it.
 * @param columns Number of columns.
 * @param rows Number of rows.
 */
void LibClass174970::set_grid_size(s32 columns, s32 rows)
{
    this->columns = columns;
    this->rows = rows;
    delete packet;
    packet = new (0) LibPacketBuffer(columns * rows * 6 + rows * 16 + 0x20);
}

/** @brief Start with type ID 0xA02 and no buffers. */
LibClass174970::LibClass174970()
{
    type_id = 0xA02;
    packet = 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", build_packet__14LibClass174AC0FPCvPv);

/** @brief Free the sample buffer. */
LibClass174AC0::~LibClass174AC0()
{
    ::operator delete(samples);
}

/**
 * @brief Set the grid size (2 to 256 columns, at least 2 rows), reallocate the packet and refill the sample table
 *        with the cosine and sine of each column's angle around a full turn; drops the packet when the table can't
 *        be allocated.
 * @param columns Column count.
 * @param rows Row count.
 */
void LibClass174AC0::func_0044FDA0(s32 columns, s32 rows)
{
    if (columns > 256)
    {
        columns = 256;
    }

    if (columns < 2)
    {
        columns = 2;
    }

    this->columns = columns;

    if (rows < 2)
    {
        rows = 2;
    }

    this->rows = rows;
    delete packet;
    packet = new (0) LibPacketBuffer(rows * 16 + columns * rows * 6 + 0x20);

    if (packet == 0)
    {
        return;
    }

    ::operator delete(samples);
    samples = new (0) float[columns * 2];

    if (samples == 0)
    {
        delete packet;
        packet = 0;
        return;
    }

    for (s32 i = 0; i < columns; i++)
    {
        LibVector4 pair;

        lib_compute_sine_cosine_pair(&pair, 6.2831855f * i / (columns - 1.0f));
        static_cast<float*>(samples)[i * 2] = pair.z;
        static_cast<float*>(samples)[i * 2 + 1] = pair.w;
    }
}

/** @brief Start with type ID 0xA02 and no buffers. */
LibClass174AC0::LibClass174AC0()
{
    type_id = 0xA02;
    packet = 0;
    samples = 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", build_packet__14LibClass174B70FPCvPv);

/** @brief Free the sample buffer. */
LibClass174B70::~LibClass174B70()
{
    ::operator delete(samples);
}

/**
 * @brief Set the grid size (2 to 256 columns, at least 2 rows), reallocate the packet and refill the sample table
 *        with the cosine and sine of each column's angle around a full turn.
 * @param columns Column count.
 * @param rows Row count.
 */
void LibClass174B70::func_00451850(s32 columns, s32 rows)
{
    if (columns > 256)
    {
        columns = 256;
    }

    if (columns < 2)
    {
        columns = 2;
    }

    this->columns = columns;

    if (rows < 2)
    {
        rows = 2;
    }

    this->rows = rows;
    delete packet;
    packet = new (0) LibPacketBuffer(rows * 16 + columns * rows * 6 + 0x20);
    ::operator delete(samples);
    samples = new (0) float[columns * 2];

    for (s32 i = 0; i < columns; i++)
    {
        LibVector4 pair;

        lib_compute_sine_cosine_pair(&pair, 6.2831855f * i / (columns - 1.0f));
        static_cast<float*>(samples)[i * 2] = pair.z;
        static_cast<float*>(samples)[i * 2 + 1] = pair.w;
    }
}

/** @brief Start with type ID 0xA01 and no buffers. */
LibClass174B70::LibClass174B70()
{
    type_id = 0xA01;
    packet = 0;
    samples = 0;
}

/**
 * @brief Store three values, the third as turns.
 * @param values Three values.
 */
void LibClass174B70::func_00451A60(const float* values)
{
    unk268 = values[0];
    unk26c = values[1];
    unk270 = 3.1415927f * (2.0f * values[2]);
}

/**
 * @brief Store three values, the first as degrees.
 * @param values Three values.
 */
void LibClass174B70::func_00451AA0(const float* values)
{
    unk274 = DEGREES_TO_RADIANS * values[0];
    unk278 = values[1];
    unk27c = values[2];
}

/**
 * @brief Store three values: the first as degrees, the third as turns.
 * @param values Three values.
 */
void LibClass174AC0::func_00451AD0(const float* values)
{
    unk268 = DEGREES_TO_RADIANS * values[0];
    unk26c = values[1];
    unk270 = 3.1415927f * (2.0f * values[2]);
}

/**
 * @brief Store three values, the first and third as degrees.
 * @param values Three values.
 */
void LibClass174AC0::func_00451B20(const float* values)
{
    unk274 = DEGREES_TO_RADIANS * values[0];
    unk278 = values[1];
    unk27c = DEGREES_TO_RADIANS * values[2];
}

/**
 * @brief Pick 0x200020 for codes whose low four bits are below 14, else 0x200030.
 * @param code Code.
 * @return Selected value.
 */
extern "C" s32 func_00451B60(s32 code)
{
    return (code & 0xF) < 14 ? 0x200020 : 0x200030;
}

/**
 * @brief Test whether a code is in 1-10, 14-231 or from 301 on, other than 121 and 202.
 * @param code Code to test.
 * @return 1 when it is.
 */
extern "C" s32 func_00451B90(s32 code)
{
    if (code == 121 || code == 202)
    {
        return 0;
    }

    if ((code > 0 && code <= 10) || (code >= 14 && code <= 231) || code > 300)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief Upload a resource's image blocks into VRAM rows, packing them left to right across 1024 pixels, and wait
 *        for the transfer.
 * @param source Resource with the block layout.
 * @param start First destination row.
 * @param count Number of blocks.
 * @return The data after the last uploaded block.
 */
extern "C" u8* func_00451C00(LibResourceHeader* source, s32 start, s32 count)
{
    u64* packet = static_cast<u64*>(memalign(0x80, (count << 7) + 0x110));
    u8* data = reinterpret_cast<u8*>(source) + source->offsets[3];
    s32 limit = (0x400 / source->unk30) * source->unk30;
    s32 x = 0;
    u64* cursor = packet;

    for (s32 i = 0; i < count; i++)
    {
        cursor[0] = DMA_TAG(6, DMA_TAG_ID_CNT, 0);
        cursor[2] = GIF_TAG_NREG(1) | 4;
        cursor[3] = 0xE;
        cursor[4] = (u64)0x24100000 << 32;
        cursor[5] = GS_REGISTER_BITBLTBUF;
        cursor[6] = ((u64)x << 32) | ((u64)start << 48);
        cursor[7] = GS_REGISTER_TRXPOS;
        cursor[8] = source->unk30 | ((u64)source->unk34 << 32);
        cursor[9] = GS_REGISTER_TRXREG;
        cursor[10] = 0;
        cursor[11] = GS_REGISTER_TRXDIR;
        cursor[12] = (source->unk24 / 16) | (GIF_TAG_FLG_IMAGE | GIF_TAG_EOP);
        cursor[13] = 0;
        cursor[14] = DMA_TAG(source->unk24 / 16, DMA_TAG_ID_REF, data);
        x += source->unk30;
        cursor += 16;

        if (x >= limit)
        {
            start += source->unk34;
            x = 0;
        }

        data += source->unk28;
    }

    *cursor = DMA_TAG_ID_END;
    FlushCache(0);
    func_004DC4F0(g_packet_queue, 3, 0, packet, 0, 0);
    func_004DBEE0(g_packet_queue, 0);
    free_guess(packet);
    FlushCache(0);
    return data;
}

/**
 * @brief Return the entry's type code.
 * @return 35.
 */
s32 LibClass174C20::func_slot14()
{
    return 35;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00451E30);

/**
 * @brief Add an amount at a position, spread bilinearly over the four cells around it.
 * @param entry Grid entry.
 * @param position Position to add at.
 * @param amount Amount to add.
 */
extern "C" void func_00452270(LibClass174C20* entry, const LibVector4* position, float amount)
{
    s32 stride = entry->header->columns + 2;
    s32 cell;
    float x;
    float y;

    if (func_00452390(entry, position, &cell, &x, &y))
    {
        float* cells = entry->unk44;

        cells[cell] += amount * ((1.0f - x) * (1.0f - y));
        cells[cell + 1] += amount * (x * (1.0f - y));
        cells[cell + stride] += amount * ((1.0f - x) * y);
        cells[cell + stride + 1] += amount * (x * y);
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00452390);

/**
 * @brief Fill the output's vertices for a bit: each vertex's cell index picks its depth (stored in y) and its
 *        16-byte value.
 * @param output Output to fill.
 * @param index Bit index, which picks the record of cell indices.
 */
void LibClass174C20::func_slot10(LibEntryOutput* output, s32 index)
{
    LibVector4* vectors = output->vectors;
    LibClass173490Entry* values = output->values;
    u16* cells = static_cast<u16*>(output->records[index]);
    s32 count = output->count;
    float* depths = unk40;
    LibClass173490Entry* entries = unk4c;

    for (s32 i = 0; i < count; i++)
    {
        u16 cell = *cells++;

        vectors->y = depths[cell];
        *values = entries[cell];
        vectors++;
        values++;
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_slot1C__14LibClass174C20FP12LibTransform);

/**
 * @brief Return the record at the cursor and move past it; the size is given in halfwords and rounded up to 16 bytes.
 * @param index Bit index; unused.
 * @param size Size in halfwords; receives the size in bytes.
 * @return Record.
 */
u8* LibClass174C20::read_record(u32 index, u32* size)
{
    *size = (*size * 2 + 15) & ~15;
    u8* record = cursor;
    cursor += *size;
    return record;
}

/** @brief Zero both cell arrays over the grid, including its border. */
void LibClass174C20::clear_cells()
{
    s32 rows;
    s32 columns;
    float* first;
    float* second;

    first = unk40;

    if (first == 0)
    {
        return;
    }

    rows = header->rows + 2;
    columns = header->columns + 2;
    second = unk44;

    for (s32 row = 0; row < rows; row++)
    {
        for (s32 column = 0; column < columns; column++)
        {
            *first++ = 0;
            *second++ = 0;
        }
    }
}

/**
 * @brief Use borrowed data, allocate the cell arrays for its grid and clear them.
 * @param value Borrowed data.
 */
void LibClass174C20::set_borrowed_data(void* value)
{
    data = value;
    data_is_borrowed = 1;
    header = reinterpret_cast<LibClass174C20Header*>(static_cast<u8*>(value) + 0x10);
    s32 count = (header->columns + 2) * (header->rows + 2) + 1;
    unk48 = reinterpret_cast<u32*>(header + 1);
    unk34 = unk48 + ((count + 2) & ~3);
    unk44 = new (0) float[count];
    unk40 = new (0) float[count];
    unk4c = new (0) LibClass173490Entry[count];

    if (unk40 == 0 || unk44 == 0 || unk4c == 0)
    {
        delete[] unk40;
        delete[] unk44;
        delete[] unk4c;
        unk40 = 0;
        unk44 = 0;
    }

    clear_cells();
}

/** @brief Free the cell arrays. */
LibClass174C20::~LibClass174C20()
{
    delete[] unk40;
    delete[] unk44;
    delete[] unk4c;
}

/** @brief Start with no arrays. */
LibClass174C20::LibClass174C20()
{
    unk19 = 1;
    unk0f = 7;
    unk40 = 0;
    unk44 = 0;
    unk4c = 0;
    unk3c = 0;
}

// TODO: The resource widget's destructor inlines its base's, which other modules keep out of line, so the base
// destructor is only inline in this unit.
inline ItemCreationClass175110::~ItemCreationClass175110()
{
}

ItemCreationClass174C40::~ItemCreationClass174C40()
{
}

/** @brief Pick up a changed resource index, then refresh the drawing state like the base widget. */
void ItemCreationClass174C40::func_00413D20()
{
    if (unkd0 != unkcc)
    {
        unkcc = unkd0;
        unkc0 = func_00464EF0(g_field_runtime, unkcc) + 0x22;
        unkc4 = 0;
        unkc9 = 1;
        needs_redraw = 1;
    }

    ItemCreationClass175110::func_00413D20();
}

/**
 * @brief Select the indexed resource and initialize its drawing position.
 * @param object Resource widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param index Resource index.
 * @return Initialization status.
 */
extern "C" s32 lib_indexed_resource_init(ItemCreationClass174C40* object, float x, float y, s32 index)
{
    LibIndexedResourceState* state = (LibIndexedResourceState*)object;
    state->selected = index;
    state->current = index;
    return func_00467800(object, func_00464EF0(g_field_runtime, state->current) + 0x22, 0, 0, 0, 0, x, y);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00453150);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004535B0);

/**
 * @brief Count the frame time down and move on when it runs out.
 * @return -1 once the last frame ended, 2 after moving to the next frame, 1 after jumping back, 0 otherwise.
 */
s8 LibImageAnimation::step()
{
    state = 0;

    if (resource && active)
    {
        timer -= static_cast<FieldRuntime*>(g_field_runtime)->rate;

        if (timer <= 0.0f)
        {
            s32 current = index;
            LibImageFrame* entry = &frame[current];
            u8 kind = entry->kind;

            if (kind == 1)
            {
                state = -1;
                active = 0;
            }
            else
            {
                if (kind == 0)
                {
                    index = current + 1;
                    state = 2;
                }
                else
                {
                    index = current - (kind - 1);
                    state = 1;
                }

                LibImageFrame* next = &frame[index];
                timer = (u32)next->duration;
            }
        }
    }

    return state;
}

/**
 * @brief Start playing from a frame.
 * @param frame Frame index.
 */
void LibImageAnimation::start(s32 frame)
{
    if (resource)
    {
        LibImageFrameList* list = reinterpret_cast<LibImageFrameList*>(static_cast<u8*>(resource) + 0x10);
        this->frame = list->frames;
        frame_count = list->count;
        index = frame;
        timer = (u32)this->frame->duration;
        state = 1;
        active = 1;
    }
}

/**
 * @brief Use an image resource and, when given, its drawing format.
 * @param resource Image resource.
 * @param format Drawing format, or null to keep the current one.
 */
void LibImageAnimation::set_resource(void* resource, const LibImageFormat* format)
{
    this->resource = resource;

    if (format)
    {
        this->format.unk00 = format->unk00;
        this->format.unk02 = format->unk02;
        this->format.unk04 = format->unk04;
        this->format.unk05 = format->unk05;
        this->format.unk06 = format->unk06;
        this->format.unk07 = format->unk07;
    }
}

/**
 * @brief Use one of the field runtime's display chunks, with the default drawing format for its range.
 * @param id Chunk index; below 34 and from 34 on use different defaults.
 */
void LibImageAnimation::set_display_chunk(s32 id)
{
    resource = func_004650B0(g_field_runtime, id);

    if (id < 34)
    {
        format.unk00 = 0;
        format.unk02 = 0x3FFC;
    }
    else
    {
        format.unk00 = 0x400;
        format.unk02 = 0x3FF8;
    }

    format.unk04 = 4;
    format.unk05 = 0x2C;
    format.unk06 = 8;
    format.unk07 = 8;
}

/**
 * @brief Initialize resource pointers, drawing scales, colors, and descriptor defaults.
 * @param state State to initialize.
 */
extern "C" void lib_draw_state_init(LibDrawState64* state)
{
    state->resource = 0;
    state->unk00 = 0;
    state->frame = 0;
    state->unk18 = state->unk1c = 0.0f;
    state->unk20 = state->unk24 = 0.0f;
    state->unk28 = state->unk2c = 0.0f;
    state->unk30 = state->unk34 = 1.0f;
    state->unk38 = state->unk3c = 0.0f;
    state->unk40 = 0.0f;
    state->unk44 = state->unk48 = state->unk4c = state->unk50 = 128.0f;
    state->unk5e = -1;
    state->unk5f = 0;
    state->unk60 = 0;
}

LibClass174C70::~LibClass174C70()
{
}

/**
 * @brief Return the entry's type code.
 * @return 43.
 */
s32 LibClass174C70::func_slot14()
{
    return 0x2B;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004540E0);

/**
 * @brief Return the record at the cursor and move past it, when the entry is complete or has bit `index`.
 * @param index Bit index.
 * @param size Receives the record's size.
 * @return Record, or null.
 */
u8* LibClass174C70::read_record(u32 index, u32* size)
{
    return lib_entry_read_record(this, cursor, index, size);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00454360);

/**
 * @brief Use a resource's bit table and the records after it, without owning them.
 * @param value Resource data.
 */
void LibClass174C70::set_borrowed_data(void* value)
{
    data = value;
    data_is_borrowed = 1;
    table = reinterpret_cast<LibBitTableHeader*>(static_cast<u8*>(value) + 0x10);
    u32* words = table->words;
    u32 count = table->bit_count;
    bits.borrow_words(count, words);
    records = reinterpret_cast<u8*>(table) + table->records_offset;
}

/** Rotation that turns (x, y, z) into (x, -z, y), rebuilt whenever a LibClass174C70 is constructed. */
extern "C" LibMatrix44Value D_0050CA50;

/** @brief Start as an entry of kind 3 and rebuild the axis-swap matrix at D_0050CA50. */
LibClass174C70::LibClass174C70()
{
    unk19 = 0;
    unk0f = 3;
    D_0050CA50.set_identity();
    D_0050CA50.m[1][1] = 0.0f;
    D_0050CA50.m[2][2] = 0.0f;
    D_0050CA50.m[1][2] = -1.0f;
    D_0050CA50.m[2][1] = 1.0f;
}

/**
 * @brief Return the entry's type code.
 * @return Ten.
 */
s32 LibClass174C90::func_slot14()
{
    return 10;
}

LibClass174CB0::~LibClass174CB0()
{
}

/**
 * @brief Return the entry's type code.
 * @return 43.
 */
s32 LibClass174CB0::func_slot14()
{
    return 0x2B;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004547C0);

/**
 * @brief Return the record at the cursor and move past it, when the entry is complete or has bit `index`.
 * @param index Bit index.
 * @param size Receives the record's size.
 * @return Record, or null.
 */
u8* LibClass174CB0::read_record(u32 index, u32* size)
{
    return lib_entry_read_record(this, cursor, index, size);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00454A50);

/**
 * @brief Use a resource's bit table and the records after it, without owning them.
 * @param value Resource data.
 */
void LibClass174CB0::set_borrowed_data(void* value)
{
    data = value;
    data_is_borrowed = 1;
    table = reinterpret_cast<LibShortBitTableHeader*>(static_cast<u8*>(value) + 0x10);
    u32* words = table->words;
    s32 count = table->bit_count;
    bits.borrow_words(count, words);
    records = reinterpret_cast<u8*>(table) + table->records_offset;
}

/** Rotation that turns (x, y, z) into (x, -z, y), rebuilt whenever a LibClass174CB0 is constructed. */
extern "C" LibMatrix44Value D_0050CA90;

/** @brief Start as an entry of kind 4 and rebuild the axis-swap matrix at D_0050CA90. */
LibClass174CB0::LibClass174CB0()
{
    unk19 = 0;
    unk0f = 4;
    D_0050CA90.set_identity();
    D_0050CA90.m[1][1] = 0.0f;
    D_0050CA90.m[2][2] = 0.0f;
    D_0050CA90.m[1][2] = -1.0f;
    D_0050CA90.m[2][1] = 1.0f;
}

/**
 * @brief Read the data referenced by the resource payload header.
 * @return Data pointer, or null when storage or the stored data offset is zero.
 */
void* LibResourceBuffer::get_data()
{
    LibResourcePayloadHeader* header = reinterpret_cast<LibResourcePayloadHeader*>(lib_resource_payload(this));

    if (header == 0)
    {
        return 0;
    }

    if (header->data_offset == 0)
    {
        return 0;
    }

    return reinterpret_cast<u8*>(header) + header->data_offset;
}

/**
 * @brief Resolve a stored byte offset relative to the resource payload.
 *
 * Nonzero offsets require backing storage.
 * @param offset Pointer to the stored byte offset.
 * @return Resolved pointer, or null when the stored offset is zero.
 */
void* LibResourceBuffer::resolve_offset(const u32* offset)
{
    u32 byte_offset = *offset;

    if (byte_offset == 0)
    {
        return 0;
    }

    return lib_resource_payload(this) + byte_offset;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00454E90);

/**
 * @brief Add an image's texture to the draw buffer's next texture slot.
 * @param buffer Draw buffer.
 * @param resource Resource whose chunk list holds the image.
 * @return The slot, or -1 when the resource has no image chunk or every slot is taken.
 */
s32 lib_draw_buffer_add_texture(LibDrawBuffer* buffer, const LibImageResource* resource)
{
    const LibResourceChunkHeader* chunk = &resource->chunk;
    const LibImageResource* image;
    const LibImageInfo* info;
    s32 index;

    for (;;)
    {
        if (chunk->magic == LIB_IMAGE_CHUNK_MAGIC)
        {
            break;
        }

        chunk = lib_next_chunk(chunk);

        if (chunk == 0)
        {
            return -1;
        }
    }

    index = buffer->texture_count;

    if (index >= LIB_DRAW_BUFFER_TEXTURE_COUNT)
    {
        return -1;
    }

    image = reinterpret_cast<const LibImageResource*>(chunk);
    info = lib_image_info(image);
    buffer->textures[index] = &image->header;
    buffer->texture_width_log2[index] = info->width_log2;
    buffer->texture_height_log2[index] = info->height_log2;
    buffer->texture_codes[index] = info->texture_code;
    buffer->texture_count++;
    return index;
}

/**
 * @brief Start a primitive of some vertices, flushing the buffer first when they wouldn't fit in 40.
 * @param buffer Draw buffer.
 * @param count Vertices in the primitive.
 */
void lib_draw_buffer_begin_primitive(LibDrawBuffer* buffer, s32 count)
{
    if (buffer->vertex_count + count >= 40)
    {
        lib_draw_buffer_start_batch(buffer);
    }

    *buffer->primitive_sizes++ = count;
    buffer->primitive_count++;
}

/**
 * @brief Copy out any pending vertices, then write the draw state the next primitives use.
 *
 * Sets the texture, blend, primitive tags and the settings' other parameters, and marks the state for the next batch.
 * @param buffer Draw buffer.
 * @param settings Settings to apply.
 */
void lib_draw_buffer_apply_settings(LibDrawBuffer* buffer, LibDrawSettings* settings)
{
    if (buffer->vertex_count != 0)
    {
        lib_draw_buffer_start_batch(buffer);
    }

    buffer->unkcf = 0;
    LibDrawState* state = &buffer->state_block->state;
    memset_guess(state, 0, sizeof(LibDrawState));

    u32 index = settings->texture_index;
    u8 width_log2 = buffer->texture_width_log2[index];
    u64 tex0 = GS_TEX0_PSM(buffer->texture_codes[index]) | GS_TEX0_TW(width_log2) | GS_TEX0_TH(buffer->texture_height_log2[index]) |
               GS_TEX0_TBW((1 << width_log2) / GS_BUFFER_WIDTH_PIXELS) | GS_TEX0_TCC;
    state->tex0 = tex0;
    state->tex0_address = GS_REGISTER_TEX0_1;
    state->unk40 = tex0;
    state->unk48 = GS_REGISTER_TEX0_1;

    if (settings->unk19 != 0 && buffer->setup_packet->unk56 < 1)
    {
        buffer->setup_packet->unk56 = 1;
    }

    if (settings->unk1A != 0 && buffer->setup_packet->unk56 < 2)
    {
        buffer->setup_packet->unk56 = 2;
    }

    if (settings->unk1B != 0 && buffer->setup_packet->unk56 < 3)
    {
        buffer->setup_packet->unk56 = 3;
    }

    if (settings->unk1C != 0 && buffer->setup_packet->unk56 < 4)
    {
        buffer->setup_packet->unk56 = 4;
    }

    state->unk80 = settings->unk05;
    state->unk24 = settings->unk06;

    if (settings->unk06 >= 2)
    {
        state->tex0_address_words[1] = settings->unk07;
    }

    if (settings->unk06 != 0)
    {
        buffer->unkcc = 1;
    }

    if (settings->unk06 == 3)
    {
        state->unk50 = settings->unk08;
        state->unk54 = settings->unk0C;
        state->unk58 = settings->unk10;
    }

    state->alpha = D_004ED320[settings->blend_mode];
    state->unk94 = settings->unk14;
    state->alpha_address = GS_REGISTER_ALPHA_1;
    state->blend = 0;

    if (settings->blend_mode != 0)
    {
        state->blend = 1;
    }

    state->register_tag.tag = GIF_TAG_NREG(1) | GIF_TAG_EOP | LIB_DRAW_REGISTER_WRITES;
    state->register_tag.registers = LIB_DRAW_AD_REGISTERS;
    state->primitive_tag.tag = GIF_TAG_PRIM(settings->prim) | LIB_DRAW_PRIMITIVE_TAG;
    state->primitive_tag.registers = LIB_DRAW_VERTEX_REGISTERS;
    state->fan_tag.tag = GIF_TAG_PRIM((settings->prim & ~GS_PRIM_TYPE_MASK) | GS_PRIM_TRIANGLE_FAN) | LIB_DRAW_PRIMITIVE_TAG;
    state->fan_tag.registers = LIB_DRAW_VERTEX_REGISTERS;
    state->texture_index = settings->texture_index;
    state->unk8c = settings->unk04;
    buffer->unkce = settings->unk18 != 0;

    if (settings->unk14 > 0.0f)
    {
        state->alpha = LIB_DRAW_ALPHA_SUBTRACT;
        state->blend = 1;
        state->unkac = 1;
        buffer->unkcf = 1;
    }

    buffer->unkc7[0] = settings->unk19;
    buffer->unkc7[1] = settings->unk1A;
    buffer->unkc7[2] = settings->unk1B;
    buffer->unkc7[3] = settings->unk1C;
    buffer->state_pending = 1;
}

/**
 * @brief Close the scratchpad batch and copy it into the command buffer.
 *
 * Writes each block's DMA tag and VIF codes, pads the streams to whole quadwords, then waits for the previous copy
 * and starts this one. A batch that wouldn't fit in the command buffer is dropped and its vertices stay pending.
 * @param buffer Draw buffer.
 */
void lib_draw_buffer_flush_batch(LibDrawBuffer* buffer)
{
    LibDrawChainBlock* chain = buffer->chain_block;
    s32 address = 0;
    s32 size = 0;

    chain->dma_tag = DMA_TAG(sizeof(LibDrawBatchInfo) / LIB_DRAW_QWORD_SIZE, DMA_TAG_ID_CNT, buffer->command_cursor);
    chain->info.vif_code = VIF_UNPACK(VIF_UNPACK_V4_16, LIB_DRAW_INFO_VU_QWORDS, VIF_UNPACK_ADD_TOPS);
    chain->info.unk24 = 0;
    chain->info.unk28 = 0;
    chain->info.unk34 = 0;
    chain->info.unk38 = 0;
    buffer->command_cursor += sizeof(LibDrawBatchInfo) / sizeof(u32);
    size += sizeof(LibDrawBatchInfo);
    LibDrawBatchInfo* info = &chain->info;

    if (buffer->state_pending)
    {
        size += sizeof(LibDrawState);
        buffer->state_block->state.vif_codes[3] = VIF_UNPACK(VIF_UNPACK_V4_32, LIB_DRAW_STATE_VU_QWORDS, VIF_UNPACK_ADD_TOPS | LIB_DRAW_INFO_VU_QWORDS);
        buffer->state_block->dma_tag = DMA_TAG(sizeof(LibDrawState) / LIB_DRAW_QWORD_SIZE, DMA_TAG_ID_CNT, buffer->command_cursor);
        buffer->block_sizes[buffer->block_count++] = ((u32)buffer->command_cursor - (u32)buffer->command_begin) / LIB_DRAW_QWORD_SIZE;
        buffer->command_cursor += sizeof(LibDrawState) / sizeof(u32);
        info->flags = LIB_DRAW_BATCH_HAS_STATE;
    }
    else
    {
        info->flags = 0;
        unsigned __int128* qwords = reinterpret_cast<unsigned __int128*>(buffer->state_block);
        qwords[0] = 0;
        qwords[1] = 0;
        qwords[2] = 0;
        qwords[3] = 0;
        qwords[4] = 0;
        qwords[5] = 0;
        qwords[6] = 0;
        qwords[7] = 0;
        qwords[8] = 0;
        qwords[9] = 0;
        qwords[10] = 0;
        qwords[11] = 0;
        qwords[12] = 0;
        qwords[13] = 0;
        qwords[14] = 0;
        qwords[15] = 0;
    }

    if (buffer->unkcf)
    {
        info->flags |= LIB_DRAW_BATCH_FLAG_08;
    }

    info->flags |= (u16)(buffer->unkce ? LIB_DRAW_BATCH_FLAG_04 : 0);
    address += LIB_DRAW_INFO_VU_QWORDS + LIB_DRAW_STATE_VU_QWORDS;

    buffer->primitive_block->header.vif_qword = 0;
    buffer->primitive_block->header.dma_tag =
        DMA_TAG((buffer->primitive_count + LIB_DRAW_QWORD_SIZE - 1) / LIB_DRAW_QWORD_SIZE + 1, DMA_TAG_ID_CNT, buffer->command_cursor);
    buffer->primitive_block->header.vif_codes[3] = VIF_UNPACK(VIF_UNPACK_S_8, buffer->primitive_count, address | VIF_UNPACK_ADD_TOPS | VIF_UNPACK_UNSIGNED);
    info->primitive_count = buffer->primitive_count;
    info->unk22 = buffer->primitive_count;
    info->primitive_offset = size + LIB_DRAW_QWORD_SIZE;
    info->primitive_address = address;
    info->unk2c[0] = buffer->unkc7[0];
    info->unk2c[1] = buffer->unkc7[1];
    info->unk2c[2] = buffer->unkc7[2];
    info->unk2c[3] = buffer->unkc7[3];
    s32 primitive_count = buffer->primitive_count;
    s32 block_size = ((primitive_count + LIB_DRAW_QWORD_SIZE - 1) & ~(LIB_DRAW_QWORD_SIZE - 1)) + LIB_DRAW_QWORD_SIZE;
    buffer->command_cursor = reinterpret_cast<u32*>(reinterpret_cast<u8*>(buffer->command_cursor) + block_size);
    size += block_size;

    info->vertex_count = buffer->vertex_count;
    LibDrawVectorBlock* normals = buffer->normal_block;
    normals->header.dma_tag = DMA_TAG(buffer->vertex_count + 1, DMA_TAG_ID_CNT, buffer->command_cursor);
    normals->header.vif_qword = 0;
    address += primitive_count;

    for (s32 i = buffer->vertex_count; i < LIB_DRAW_BATCH_VERTEX_COUNT; i++)
    {
        normals->vectors[i] = 0;
    }

    buffer->normal_block->header.vif_codes[2] = VIF_STCYCL(4, 1);
    buffer->normal_block->header.vif_codes[3] = VIF_UNPACK(VIF_UNPACK_V4_32, buffer->vertex_count, address | VIF_UNPACK_ADD_TOPS);
    info->unk4c_offset = size + LIB_DRAW_QWORD_SIZE;
    info->unk4c_address = address;
    block_size = buffer->vertex_count * LIB_DRAW_QWORD_SIZE + LIB_DRAW_QWORD_SIZE;
    buffer->command_cursor = reinterpret_cast<u32*>(reinterpret_cast<u8*>(buffer->command_cursor) + block_size);
    size += block_size;

    {
        s16 count;
        s32 index;
        s32 pad;
        s32 qword;
        LibDrawWordBlock* texcoords = buffer->texcoord_block;
        texcoords->header.dma_tag = DMA_TAG((buffer->vertex_count + 3) / 4 + 1, DMA_TAG_ID_CNT, buffer->command_cursor);
        texcoords->header.vif_qword = 0;
        count = buffer->vertex_count;
        qword = count / 4 + 1;
        index = count;

        for (pad = 0; index < LIB_DRAW_BATCH_VERTEX_COUNT && pad < 4; index++, pad++)
        {
            *buffer->texcoords++ = 0;
        }

        for (s32 i = qword; i < LIB_DRAW_BATCH_VERTEX_COUNT / 4; i++)
        {
            texcoords->qwords[i] = 0;
        }

        buffer->texcoord_block->header.vif_codes[3] = VIF_UNPACK(VIF_UNPACK_V2_16_MASKED, buffer->vertex_count, (address + 1) | VIF_UNPACK_ADD_TOPS);
        info->texcoord_offset = size + LIB_DRAW_QWORD_SIZE;
        block_size = ((buffer->vertex_count + 3) & ~3) * sizeof(u32) + LIB_DRAW_QWORD_SIZE;
        buffer->command_cursor = reinterpret_cast<u32*>(reinterpret_cast<u8*>(buffer->command_cursor) + block_size);
        size += block_size;
    }

    {
        s16 count;
        s32 index;
        s32 pad;
        s32 qword;
        LibDrawWordBlock* colors = buffer->color_block;
        colors->header.dma_tag = DMA_TAG((buffer->vertex_count + 3) / 4 + 1, DMA_TAG_ID_CNT, buffer->command_cursor);
        colors->header.vif_qword = 0;
        count = buffer->vertex_count;
        qword = count / 4 + 1;
        index = count;

        for (pad = 0; index < LIB_DRAW_BATCH_VERTEX_COUNT && pad < 4; index++, pad++)
        {
            *buffer->colors++ = 0;
        }

        for (s32 i = qword; i < LIB_DRAW_BATCH_VERTEX_COUNT / 4; i++)
        {
            colors->qwords[i] = 0;
        }

        buffer->color_block->header.vif_codes[3] = VIF_UNPACK(VIF_UNPACK_V4_8, buffer->vertex_count, (address + 2) | VIF_UNPACK_ADD_TOPS | VIF_UNPACK_UNSIGNED);
        info->color_offset = size + LIB_DRAW_QWORD_SIZE;
        block_size = ((buffer->vertex_count + 3) & ~3) * sizeof(u32) + LIB_DRAW_QWORD_SIZE;
        buffer->command_cursor = reinterpret_cast<u32*>(reinterpret_cast<u8*>(buffer->command_cursor) + block_size);
        size += block_size;
    }

    LibDrawVectorBlock* positions = buffer->position_block;
    positions->header.dma_tag = DMA_TAG(buffer->vertex_count + 2, DMA_TAG_ID_CNT, buffer->command_cursor);
    positions->header.vif_qword = 0;
    buffer->position_block->header.vif_codes[3] = VIF_UNPACK(VIF_UNPACK_V4_32, buffer->vertex_count, (address + 3) | VIF_UNPACK_ADD_TOPS);
    info->position_offset = size + LIB_DRAW_QWORD_SIZE;
    positions->vectors[buffer->vertex_count] = 0;
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(positions) + (buffer->vertex_count + 2) * LIB_DRAW_QWORD_SIZE) = VIF_STCYCL(1, 1);
    block_size = buffer->vertex_count * LIB_DRAW_QWORD_SIZE + 2 * LIB_DRAW_QWORD_SIZE;
    buffer->command_cursor = reinterpret_cast<u32*>(reinterpret_cast<u8*>(buffer->command_cursor) + block_size);
    *reinterpret_cast<u64*>(reinterpret_cast<u8*>(positions) + (buffer->vertex_count + 3) * LIB_DRAW_QWORD_SIZE) = DMA_TAG_ID_END;
    size += block_size;

    if (buffer->command_cursor <= buffer->command_begin + buffer->word_capacity)
    {
        info->size = size;

        if (buffer->batch_count != 0)
        {
            while (!(*D_STAT & D_STAT_CIS8))
            {
            }
        }

        *D8_SADR = reinterpret_cast<u32>(buffer->chain_block);
        *D8_QWC = 0;
        *D_STAT = D_STAT_CIS8;
        *D8_CHCR = DMA_CHCR_START | DMA_CHCR_MODE_CHAIN | DMA_CHCR_DIR_FROM_MEMORY;
        buffer->batch_count++;
        buffer->vertex_count = 0;
    }
}

/**
 * @brief Copy out any pending vertices, then lay out the next scratchpad batch and switch to the other half.
 * @param buffer Draw buffer.
 */
void lib_draw_buffer_start_batch(LibDrawBuffer* buffer)
{
    if (buffer->vertex_count != 0)
    {
        lib_draw_buffer_flush_batch(buffer);
    }

    buffer->chain_block = reinterpret_cast<LibDrawChainBlock*>(reinterpret_cast<u8*>(EE_SCRATCHPAD) + buffer->scratchpad_index * LIB_DRAW_BATCH_STRIDE);
    buffer->state_block = reinterpret_cast<LibDrawStateBlock*>(buffer->chain_block + 1);
    buffer->primitive_block = reinterpret_cast<LibDrawPrimitiveBlock*>(buffer->state_block + 1);
    buffer->normal_block = reinterpret_cast<LibDrawVectorBlock*>(buffer->primitive_block + 1);
    buffer->texcoord_block = reinterpret_cast<LibDrawWordBlock*>(buffer->normal_block + 1);
    buffer->color_block = buffer->texcoord_block + 1;
    buffer->position_block = reinterpret_cast<LibDrawVectorBlock*>(buffer->color_block + 1);
    buffer->primitive_sizes = buffer->primitive_block->sizes;
    reinterpret_cast<unsigned __int128*>(buffer->primitive_sizes)[0] = 0;
    reinterpret_cast<unsigned __int128*>(buffer->primitive_sizes)[1] = 0;
    buffer->positions = reinterpret_cast<FieldVec4A*>(buffer->position_block->vectors);
    buffer->normals = reinterpret_cast<FieldVec4A*>(buffer->normal_block->vectors);
    buffer->texcoords = buffer->texcoord_block->words;
    buffer->colors = buffer->color_block->words;
    buffer->vertex_count = 0;
    buffer->primitive_count = 0;
    buffer->scratchpad_index ^= 1;
    buffer->state_pending = 0;
}

/**
 * @brief Copy out any pending vertices and finish the commands, unless they've run into the space kept for the block
 *        sizes and texture packets.
 *
 * Fills in the setup packet, appends the block sizes, hands the commands over, switches command buffers, waits for
 * the draw buffer's DMA channel and turns its interrupts back on.
 * @param buffer Draw buffer.
 * @param mode Nonzero stores the setup packet's size at its offset 0x04 too.
 * @param distance Stored in the setup packet at 0x18.
 * @param flag Stored in the setup packet at 0x3F.
 */
extern "C" void lib_draw_buffer_end(LibDrawBuffer* buffer, s32 mode, float distance, s32 flag)
{
    if (buffer->vertex_count != 0)
    {
        lib_draw_buffer_flush_batch(buffer);
    }

    if (reinterpret_cast<u8*>(buffer->command_cursor) < reinterpret_cast<u8*>(buffer->command_begin) + buffer->word_capacity -
                                                            buffer->block_capacity * sizeof(u32) - buffer->texture_count * LIB_DRAW_TEXTURE_PACKET_SIZE)
    {
        buffer->setup_packet->size = sizeof(LibDrawSetupPacket);
        buffer->setup_packet->unk04 = mode != 0 ? sizeof(LibDrawSetupPacket) : 0;
        buffer->setup_packet->unk0c = 0;
        buffer->setup_packet->unk10 = 0;
        buffer->setup_packet->unk14 = 0;
        buffer->setup_packet->unk18 = distance;
        buffer->setup_packet->unk50 = 0;
        buffer->setup_packet->batch_count = buffer->batch_count;
        buffer->setup_packet->unk3e = buffer->unkcc;
        buffer->setup_packet->unk3f = flag;
        buffer->setup_packet->command_size = reinterpret_cast<u8*>(buffer->command_cursor) - reinterpret_cast<u8*>(buffer->command_begin);
        buffer->setup_packet->unk44 = 0;
        buffer->setup_packet->unk48 = 0;
        buffer->setup_packet->unk4c = 0;

        u32* words = reinterpret_cast<u32*>(reinterpret_cast<u32>(buffer->command_cursor) | UNCACHED_SEGMENT);

        *words++ = buffer->block_count;

        for (s32 i = 0; i < buffer->block_count; i++)
        {
            *words++ = buffer->block_sizes[i];
        }

        buffer->command_cursor += ((buffer->block_count + 1) * sizeof(u32) + 15) / 16 * (16 / sizeof(u32));
        func_00454E90(buffer);

        if (buffer->unkcd)
        {
            func_004D5A50(buffer, buffer->command_begin - 4);
            buffer->unkcd = 0;
        }
        else
        {
            buffer->data = buffer->command_begin - 4;
        }

        if (buffer->command_buffer_count == 2)
        {
            buffer->command_buffer_index ^= 1;
        }

        sceDmaSync(sceDmaGetChan(D_001B6604->channel), 0, 0);
        EnableDmac(D_001B6604->channel);
    }
}

/**
 * @brief Start a new packet in the draw buffer's current command buffer, then stop the DMA queue it goes out on.
 * @param buffer Draw buffer.
 * @param unk3C Stored in the setup packet at 0x3C.
 * @param unk3D Stored in the setup packet at 0x3D.
 */
void lib_draw_buffer_begin(LibDrawBuffer* buffer, u8 unk3C, u8 unk3D)
{
    buffer->command_begin = buffer->command_buffers[buffer->command_buffer_index] + LIB_DRAW_COMMAND_HEADER_WORDS;
    buffer->command_cursor = buffer->command_begin;
    buffer->setup_packet = reinterpret_cast<LibDrawSetupPacket*>(reinterpret_cast<u32>(buffer->command_cursor) | UNCACHED_SEGMENT);
    buffer->command_cursor += sizeof(LibDrawSetupPacket) / sizeof(u32);
    buffer->setup_packet->unk3C = unk3C;
    buffer->setup_packet->unk3D = unk3D;
    buffer->setup_packet->unk54 = 0;
    buffer->setup_packet->unk56 = 0;
    buffer->scratchpad_index = 0;
    buffer->vertex_count = 0;
    buffer->batch_count = 0;
    buffer->block_count = 0;
    buffer->unkcc = 0;
    lib_draw_buffer_start_batch(buffer);

    D_001B6604->wait_idle();
    D_001B6604->stop();
}

/**
 * @brief Allocate command buffers, block sizes and packet storage.
 * @param buffer_count Command-buffer count, at most two.
 * @param word_capacity Word count before the 32-word allocation overhead.
 * @param block_capacity Number of entries in the block-size array.
 * @param staging_blocks Packet-block count, capped before adding two extra blocks.
 * @return True when all allocations succeed; false on the first failure.
 */
bool LibDrawBuffer::allocate_storage(s32 buffer_count, s32 word_capacity, s32 block_capacity, s32 staging_blocks)
{
    command_buffer_count = buffer_count;
    this->word_capacity = word_capacity;
    this->block_capacity = block_capacity;
    command_buffer_index = 0;
    ::operator delete(command_buffers[0]);
    ::operator delete(command_buffers[1]);
    command_buffers[0] = 0;
    command_buffers[1] = 0;

    for (s32 i = 0; i < buffer_count; i++)
    {
        command_buffers[i] = new (0) u32[word_capacity + 32];

        if (command_buffers[i] == 0)
        {
            return false;
        }
    }

    ::operator delete(block_sizes);
    block_sizes = new (0) u32[block_capacity];

    if (block_sizes == 0)
    {
        return false;
    }

    if (staging_blocks > block_capacity)
    {
        staging_blocks = block_capacity;
    }

    block_packets = new (0) u8[(staging_blocks + 2) * 48];

    if (block_packets == 0)
    {
        return false;
    }

    FlushCache(0);
    return true;
}

/** @brief Release command buffers, block sizes and packet storage. */
LibDrawBuffer::~LibDrawBuffer()
{
    ::operator delete(command_buffers[0]);
    ::operator delete(command_buffers[1]);
    ::operator delete(block_sizes);
    delete[] block_packets;
}

/** @brief Initialize empty command storage and texture bookkeeping. */
LibDrawBuffer::LibDrawBuffer()
{
    FlushCache(0);
    command_buffers[0] = 0;
    command_buffers[1] = 0;
    block_sizes = 0;
    texture_count = 0;
    unkcd = 1;
    unkce = 0;
    block_packets = 0;
    command_begin = 0;
}


LibClass174D10::~LibClass174D10()
{
}

/**
 * @brief Return the entry's type code.
 * @return 40.
 */
s32 LibClass174D10::func_slot14()
{
    return 40;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456210);

/**
 * @brief Return the record at the cursor and move past it, when the entry is complete or has bit `index`.
 * @param index Bit index.
 * @param size Receives the record's size.
 * @return Record, or null.
 */
u8* LibClass174D10::read_record(u32 index, u32* size)
{
    return lib_entry_read_record(this, cursor, index, size);
}

/**
 * @brief Note whether every bit is set; in mapping mode 2 scroll the offsets by the camera's reflection off the
 *        model, otherwise count the blend mode down. Rewind the records.
 * @param root Model transform; unused.
 * @return Zero on the step the countdown ends, otherwise one.
 */
s32 LibClass174D10::func_slot1C(LibTransform* root)
{
    if (table->bit_count == table->unk02)
    {
        unk19 = 1;
    }
    else
    {
        unk19 = 0;
    }

    if (table->mapping == 2)
    {
        LibVector4 normal;
        LibVector4 view;
        LibVector4 reflection;
        const LibMatrix44Value* matrix = list->model->get_transform_matrix();
        normal.x = matrix->m[0][1];
        normal.y = -matrix->m[1][1];
        normal.z = matrix->m[2][1];
        lib_normalize_vector3(&normal.x);

        LibCamera* camera = static_cast<LibCamera*>(g_display_manager->current_display);

        if (camera != 0)
        {
            view.x = camera->transform.m[0][3];
            view.y = camera->transform.m[1][3];
            view.z = camera->transform.m[2][3];
            view.w = 1.0f;
        }

        view.x -= matrix->m[0][3];
        view.y -= matrix->m[1][3];
        view.z -= matrix->m[2][3];
        lib_normalize_vector3(&view.x);
        float scale = 2.0f * (normal.x * view.x + normal.y * view.y + normal.z * view.z);
        reflection.x = scale * normal.x - view.x;
        reflection.y = scale * normal.y - view.y;
        reflection.z = scale * normal.z - view.z;
        float u = 0.5f - 0.1591554433f * func_00142148(ee_abs(reflection.z), reflection.x);
        float v = 0.5f - 0.1591554433f * func_00142148(reflection.y, reflection.z);
        offset_u = u * table->scale;

        while (offset_u >= 2.0f)
        {
            offset_u -= 2.0f;
        }

        while (offset_u <= 0.0f)
        {
            offset_u += 1.0f;
        }

        offset_v = v * table->scale;

        while (offset_v >= 2.0f)
        {
            offset_v -= 2.0f;
        }

        while (offset_v <= 0.0f)
        {
            offset_v += 1.0f;
        }
    }
    else if (blend_mode != 0 && --blend_mode == 0)
    {
        if (unk18 && list)
        {
            list->unk8d_1 = 1;
        }

        unk18 = 0;
        return 0;
    }

    cursor = records;
    return 1;
}

/**
 * @brief Use a resource's bit table, records and two offsets without owning them.
 * @param value Resource data.
 */
void LibClass174D10::set_borrowed_data(void* value)
{
    data = value;
    data_is_borrowed = 1;
    table = reinterpret_cast<LibOffsetBitTableHeader*>(static_cast<u8*>(value) + 0x10);
    u32* words = table->words;
    s32 count = table->bit_count;
    bits.borrow_words(count, words);
    records = reinterpret_cast<u8*>(table) + table->records_offset;
    set_offset_u(table->offset[0]);
    set_offset_v(table->offset[1]);
}

/** @brief Start as an entry of kind 5 with blend mode 0. */
LibClass174D10::LibClass174D10()
{
    unk19 = 0;
    unk0f = 5;
    blend_mode = 0;
}

/** @brief Start unattached, with unk0e set to two. */
LibClass174D30::LibClass174D30()
{
    unk0e = 2;
}

/**
 * @brief Return the entry's type code.
 * @return Six.
 */
s32 LibClass174D30::func_slot14()
{
    return 6;
}

LibClass174D50::~LibClass174D50()
{
}

/**
 * @brief Return the entry's type code.
 * @return 36.
 */
s32 LibClass174D50::func_slot14()
{
    return 36;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004569D0);

/**
 * @brief Return the record at the cursor and move past it, when the entry is complete or has bit `index`.
 * @param index Bit index.
 * @param size Receives the record's size.
 * @return Record, or null.
 */
u8* LibClass174D50::read_record(u32 index, u32* size)
{
    return lib_entry_read_record(this, cursor, index, size);
}

/**
 * @brief Note whether every bit is set, count the blend mode down and rewind the records.
 * @param root Model transform; unused.
 * @return Zero on the step the countdown ends, otherwise one.
 */
s32 LibClass174D50::func_slot1C(LibTransform* root)
{
    if (table->bit_count == table->unk02)
    {
        unk19 = 1;
    }
    else
    {
        unk19 = 0;
    }

    if (blend_mode != 0 && --blend_mode == 0)
    {
        if (unk18 && list)
        {
            list->unk8d_1 = 1;
        }

        unk18 = 0;
        return 0;
    }

    blend_mode = 0;
    cursor = records;
    return 1;
}

/**
 * @brief Use a resource's bit table, records and colour without owning them; a colour other than white marks the
 *        owning list.
 * @param value Resource data.
 */
void LibClass174D50::set_borrowed_data(void* value)
{
    data = value;
    data_is_borrowed = 1;
    table = reinterpret_cast<LibColorBitTableHeader*>(static_cast<u8*>(value) + 0x10);
    u32* words = table->words;
    s32 count = table->bit_count;
    bits.borrow_words(count, words);
    records = reinterpret_cast<u8*>(table) + table->records_offset;
    FieldVec4A source(table->color[0], table->color[1], table->color[2], table->color[3]);
    color = source;

    if (color.x != 1.0f || color.y != 1.0f || color.z != 1.0f || color.w != 1.0f)
    {
        if (unk18 != 1 && list != 0)
        {
            list->unk8d_1 = 1;
        }

        unk18 = 1;
        blend_mode = 0;
    }
    else
    {
        blend_mode = 2;
    }
}

/** @brief Start as an entry of kind 6 with a white colour. */
LibClass174D50::LibClass174D50()
{
    unk19 = 0;
    unk0f = 6;
    color = FieldVec4A(1.0f, 1.0f, 1.0f, 1.0f);
    blend_mode = 0;
}

/**
 * @brief Find the first DTT chunk in a chunk list.
 * @param out Receives the chunk's data size and address.
 * @param chunk First chunk.
 * @return Whether a DTT chunk was found.
 */
bool func_00456D60(LibChunkData* out, LibResourceChunkHeader* chunk)
{
    for (;;)
    {
        if (chunk->magic == LIB_DTT_CHUNK_MAGIC)
        {
            break;
        }

        chunk = chunk->next_offset == 0 ? 0 : (LibResourceChunkHeader*)((u8*)chunk + chunk->next_offset);

        if (!chunk)
        {
            return false;
        }
    }

    u32* block = (u32*)(chunk + 1);
    out->size = *block;
    out->data = block + 1;
    return true;
}

/** Factor IDs whose counts LibFactorCounts keeps, padded with an unused ID. */
extern "C" const u16 D_004ED1B0[LIB_COUNTED_FACTOR_COUNT];

#define LIB_FACTOR_COUNTS_KEY 0x1C62
#define LIB_FACTOR_TABLE_KEY 0x83A8

// TODO: Like the other saved-data checksums here, these only match at optimization level 0.
#pragma push
#pragma optimization_level 0

/**
 * @brief Add up a byte range for a factor count list's checksums, each byte plus three times its index.
 * @param list Factor count list; unused.
 * @param data Bytes to add up.
 * @param size Byte count.
 * @return Sum.
 */
u16 lib_factor_checksum(LibFactorCounts* list, const u8* data, s32 size)
{
    u16 sum = 0;
    s32 i;

    for (i = 0; i < size; i++)
    {
        sum += *data;
        sum += (u16)(i * 3);
        data++;
    }

    return sum;
}

/**
 * @brief Check both of a factor count list's checksums.
 * @param list Factor count list.
 * @return Whether the counts and the factor table both match their checksums.
 */
bool lib_factor_counts_valid(LibFactorCounts* list)
{
    s32 checksum = list->checksum;

    if (checksum != (lib_factor_checksum(list, (const u8*)list->counts, sizeof(list->counts)) ^ LIB_FACTOR_COUNTS_KEY))
    {
        return false;
    }

    checksum = list->table_checksum;

    if (checksum != (lib_factor_checksum(list, (const u8*)D_004ED1B0, sizeof(D_004ED1B0)) ^ LIB_FACTOR_TABLE_KEY))
    {
        return false;
    }

    return true;
}

/**
 * @brief Check whether a factor has been counted, clearing the list first if its checksums are bad.
 * @param list Factor count list.
 * @param factor Factor ID.
 * @return Whether the factor's count is positive.
 */
bool lib_factor_counted(LibFactorCounts* list, s32 factor)
{
    if (!lib_factor_counts_valid(list))
    {
        lib_factor_counts_reset(list);
        return false;
    }

    if (lib_factor_count(list, factor) > 0)
    {
        return true;
    }

    return false;
}

/**
 * @brief Lower a factor's count by one.
 * @param list Factor count list.
 * @param factor Factor ID.
 */
void lib_factor_count_lower(LibFactorCounts* list, s32 factor)
{
    lib_factor_count_set(list, factor, lib_factor_count(list, factor) - 1);
}

/**
 * @brief Raise a factor's count by one.
 * @param list Factor count list.
 * @param factor Factor ID.
 */
void lib_factor_count_raise(LibFactorCounts* list, s32 factor)
{
    lib_factor_count_set(list, factor, lib_factor_count(list, factor) + 1);
}

/**
 * @brief Look up a factor's count.
 * @param list Factor count list.
 * @param factor Factor ID.
 * @return Count, or zero for a factor that isn't counted.
 */
s32 lib_factor_count(LibFactorCounts* list, s32 factor)
{
    s32 i;

    for (i = 0; i < LIB_COUNTED_FACTOR_COUNT; i++)
    {
        if (factor == D_004ED1B0[i])
        {
            return (s8)list->counts[i];
        }
    }

    return 0;
}

/**
 * @brief Set a factor's count and refresh the counts' checksum.
 * @param list Factor count list.
 * @param factor Factor ID.
 * @param count New count.
 * @return Whether the factor is counted.
 */
bool lib_factor_count_set(LibFactorCounts* list, s32 factor, s32 count)
{
    s32 i;

    for (i = 0; i < LIB_COUNTED_FACTOR_COUNT; i++)
    {
        if (factor == D_004ED1B0[i])
        {
            list->counts[i] = count;
            list->checksum = lib_factor_checksum(list, (const u8*)list->counts, sizeof(list->counts)) ^ LIB_FACTOR_COUNTS_KEY;
            return true;
        }
    }

    return false;
}

/**
 * @brief Clear every count and rewrite both checksums.
 * @param list Factor count list.
 */
void lib_factor_counts_reset(LibFactorCounts* list)
{
    memset_guess(list->counts, 0, sizeof(list->counts));
    list->checksum = lib_factor_checksum(list, (const u8*)list->counts, sizeof(list->counts)) ^ LIB_FACTOR_COUNTS_KEY;
    list->table_checksum = lib_factor_checksum(list, (const u8*)D_004ED1B0, sizeof(D_004ED1B0)) ^ LIB_FACTOR_TABLE_KEY;
}

#pragma pop

/** Keys of the trophy record encoding. */
enum
{
    LIB_TROPHY_RECORD_KEY_SEED = 0x437312F8,
    LIB_TROPHY_RECORD_KEY_STEP = 0x12D953F6,
    LIB_TROPHY_RECORD_CHECKSUM_SEED = 0x13129FDE,
    LIB_TROPHY_RECORD_CHECKSUM_MASK = 0xFEFCFEFD
};

// TODO: This only matches at optimization level 0, like the other saved-data checksums here.
#pragma push
#pragma optimization_level 0

/**
 * @brief Decode a trophy record in place, then check it against the checksum in its first word.
 * @param record Encoded record (LIB_TROPHY_RECORD_SIZE bytes).
 * @return Whether the decoded record's checksum matches.
 */
bool lib_trophy_record_decode(void* record)
{
    u32* word;
    u32 key;
    u32 checksum;
    s32 i;
    s32 count;
    s32 j;
    bool valid;

    word = (u32*)record;
    count = LIB_TROPHY_RECORD_SIZE / sizeof(u32);
    key = LIB_TROPHY_RECORD_KEY_SEED;

    for (i = 0; i < count; i++)
    {
        *word ^= key;
        word++;

        if (i & 1)
        {
            key <<= 2;
        }
        else
        {
            key >>= 2;
        }

        key += LIB_TROPHY_RECORD_KEY_STEP;
    }

    word = (u32*)record;
    word++;
    count = LIB_TROPHY_RECORD_SIZE / sizeof(u32) - 1;
    checksum = LIB_TROPHY_RECORD_CHECKSUM_SEED;

    for (j = 0; j < count; j++)
    {
        checksum <<= 1;
        checksum += *word++ ^ LIB_TROPHY_RECORD_CHECKSUM_MASK;
    }

    if (*(u32*)record == checksum)
    {
        valid = true;
    }
    else
    {
        valid = false;
    }

    return valid;
}

#pragma pop

// TODO: Like the decoder, this only matches at optimization level 0.
#pragma push
#pragma optimization_level 0

/**
 * @brief Store a trophy record's checksum in its first word, then encode the record in place.
 * @param record Decoded record (LIB_TROPHY_RECORD_SIZE bytes).
 */
void lib_trophy_record_encode(void* record)
{
    u32* word;
    u32 key;
    u32 checksum;
    s32 i;
    s32 count;
    s32 j;

    word = (u32*)record;
    word++;
    count = LIB_TROPHY_RECORD_SIZE / sizeof(u32) - 1;
    checksum = LIB_TROPHY_RECORD_CHECKSUM_SEED;

    for (j = 0; j < count; j++)
    {
        checksum <<= 1;
        checksum += *word++ ^ LIB_TROPHY_RECORD_CHECKSUM_MASK;
    }

    *(u32*)record = checksum;

    word = (u32*)record;
    count = LIB_TROPHY_RECORD_SIZE / sizeof(u32);
    key = LIB_TROPHY_RECORD_KEY_SEED;

    for (i = 0; i < count; i++)
    {
        *word ^= key;
        word++;

        if (i & 1)
        {
            key <<= 2;
        }
        else
        {
            key >>= 2;
        }

        key += LIB_TROPHY_RECORD_KEY_STEP;
    }
}

#pragma pop

// TODO: This only matches at optimization level 0, and with an unused local cleared at the start; I don't know
// what the local was for. The grid functions below inline it, so auto inlining is on for it too.
#pragma push
#pragma optimization_level 0
#pragma auto_inline on

/**
 * @brief Compute the checksum the game stores with its saved records.
 * @param seed Starting value, usually the record's key.
 * @param data Bytes to check.
 * @param size Number of bytes.
 * @return Checksum.
 */
u16 lib_compute_checksum(u16 seed, const void* data, s32 size)
{
    u32 checksum = seed;
    u32 total = 0;
    const u8* bytes = (const u8*)data;

    for (s32 i = 0; i < size; i++)
    {
        u8 value = *bytes++;
        checksum = (value << 8) + (checksum * LIB_CHECKSUM_MULTIPLIER + LIB_CHECKSUM_INCREMENT);
    }

    return checksum;
}

#pragma pop


// TODO: Like the checksum above, this only matches at optimization level 0.
#pragma push
#pragma optimization_level 0

/**
 * @brief Read one trophy flag.
 * @param flags Trophy flags.
 * @param index Trophy number.
 * @return Whether the flag is set.
 */
static inline bool lib_trophy_flag(LibTrophyFlags* flags, u32 index)
{
    u32 byte = index / 8;
    u32 bit = index & 7;
    return !!((flags->flags.bytes[byte] >> bit) & 1);
}

/**
 * @brief Pick a new random checksum seed for the trophy flags and recompute their checksum.
 * @param flags Trophy flags.
 */
void lib_trophy_flags_update_checksum(LibTrophyFlags* flags)
{
    flags->checksum_seed = resident_next_random_word();
    u32 value = flags->checksum_seed;
    u32 sum = 0;

    for (s32 i = 0; i < LIB_TROPHY_COUNT; i++)
    {
        u32 index = i;
        s32 bit = lib_trophy_flag(flags, index);

        if (value & 1)
        {
            bit ^= 1;
        }

        value = value * LIB_CHECKSUM_MULTIPLIER + LIB_CHECKSUM_INCREMENT;
        sum += bit * value;
        value = (u64)(value * value) + 0xD45666F2;
    }

    sum += flags->trophy_key ^ value;
    flags->checksum = sum;
}

/**
 * @brief Compute the trophy flags' checksum from a seed: each flag, flipped by the seed's low bit, weighted by the next
 *        value of the seed sequence, plus the trophy key mixed with the final seed.
 * @param flags Trophy flags.
 * @param seed Seed.
 * @param checksum Receives the checksum.
 */
void lib_trophy_flags_checksum(LibTrophyFlags* flags, const u32* seed, u32* checksum)
{
    u32 value = *seed;
    u32 sum = 0;
    s32 i;

    for (i = 0; i < LIB_TROPHY_COUNT; i++)
    {
        s32 bit = lib_trophy_flag(flags, i);

        if (value & 1)
        {
            bit ^= 1;
        }

        value = value * LIB_CHECKSUM_MULTIPLIER + LIB_CHECKSUM_INCREMENT;
        sum += bit * value;
        value = (u64)(value * value) + 0xD45666F2;
    }

    sum += flags->trophy_key ^ value;
    *checksum = sum;
}

#pragma pop

// TODO: This only matches at optimization level 1 with the peephole and tree transformations off, which keeps the
// inlined checksum's O0 shape; I haven't found what the original build did instead.
#pragma push
#pragma optimization_level 1
#pragma peephole off
#pragma opt_treetransformation off

/**
 * @brief Store an entry of the settings' 10 by 10 byte grid, limited to 0 through 70, when the settings checksum is
 *        valid, and reseal the checksum.
 * @param settings System settings.
 * @param row Row, 1 through 10.
 * @param column Column, 1 through 10.
 * @param value Value to store.
 */
void func_004577A0(LibSystemSettings* settings, s32 row, s32 column, s32 value)
{
    if (settings->checksum != lib_compute_checksum(settings->key, &settings->checksum_start, (u8*)&settings->checksum - &settings->checksum_start))
    {
        return;
    }

    if (column <= 0 || column > LIB_SETTINGS_GRID_SIZE)
    {
        return;
    }

    if (row <= 0 || row > LIB_SETTINGS_GRID_SIZE)
    {
        return;
    }

    value += 40597;
    value = clamp(value, 40597, 40667);
    value -= 40597;
    settings->unk40[row - 1][column - 1] = value ^ LIB_RECORD_XOR_BYTE;
    settings->key = resident_next_random_word();
    settings->checksum = lib_compute_checksum(settings->key, &settings->checksum_start, (u8*)&settings->checksum - &settings->checksum_start);
}

#pragma pop

// TODO: Like the checksums above, this only matches at optimization level 0.
#pragma push
#pragma optimization_level 0

/**
 * @brief Read an entry of the settings' 10 by 10 byte grid.
 * @param settings System settings.
 * @param row Row, 1 through 10.
 * @param column Column, 1 through 10.
 * @return Entry, or zero when the checksum is invalid or the position is out of range.
 */
s32 func_00457980(LibSystemSettings* settings, s32 row, s32 column)
{
    if (settings->checksum != lib_compute_checksum(settings->key, &settings->checksum_start, (u8*)&settings->checksum - &settings->checksum_start))
    {
        return 0;
    }

    if (column <= 0 || column > LIB_SETTINGS_GRID_SIZE)
    {
        return 0;
    }

    if (row <= 0 || row > LIB_SETTINGS_GRID_SIZE)
    {
        return 0;
    }

    return settings->unk40[row - 1][column - 1] ^ LIB_RECORD_XOR_BYTE;
}

#pragma pop

/** "Sophia". */
extern const char D_00505B18[];

/** "Fate". */
extern const char D_00505B20[];

// TODO: Like the saved-data functions around them, these only match at optimization level 0.
#pragma push
#pragma optimization_level 0

/**
 * @brief Give Sophia's records their starting values: level 1, three equipment slots with the first three
 *        emptied, base stamina 15, base luck 135 and Sophia's name.
 * @param record Character record.
 * @param equipment Character equipment record.
 */
extern "C" void func_00457B20(LibCharacterRecord* record, LibCharacterEquipment* equipment)
{
    set_character_base_level(record, 1);
    set_character_level(record, 1);
    set_character_experience(record, 0);
    set_equipment_slot_limit(equipment, 3);
    set_equipment_item_id(equipment, 0, 0);
    set_equipment_item_id(equipment, 1, 0);
    set_equipment_item_id(equipment, 2, 0);
    set_equipment_base_stamina(equipment, 15);
    set_equipment_base_luck(equipment, 135);

    const char* source = D_00505B18;
    char* destination = equipment->character_name;

    while ((*destination++ = *source++))
    {
    }
}

/**
 * @brief Give Fate's records their starting values: level 1, three equipment slots with the first three
 *        emptied, base stamina 15, base luck 120 and Fate's name.
 * @param record Character record.
 * @param equipment Character equipment record.
 */
extern "C" void func_00458110(LibCharacterRecord* record, LibCharacterEquipment* equipment)
{
    set_character_base_level(record, 1);
    set_character_level(record, 1);
    set_character_experience(record, 0);
    set_equipment_slot_limit(equipment, 3);
    set_equipment_item_id(equipment, 0, 0);
    set_equipment_item_id(equipment, 1, 0);
    set_equipment_item_id(equipment, 2, 0);
    set_equipment_base_stamina(equipment, 15);
    set_equipment_base_luck(equipment, 120);

    const char* source = D_00505B20;
    char* destination = equipment->character_name;

    while ((*destination++ = *source++))
    {
    }
}

#pragma pop

// TODO: Like the saved-data functions around it, this only matches at optimization level 0.
#pragma push
#pragma optimization_level 0

/**
 * @brief Clear a character's record pair, run the kind's setup and store the kind.
 * @param output Output record.
 * @param input Input record.
 * @param kind Record kind; 1 and 2 have setups.
 */
extern "C" void func_00458700(LibResourceRecordC4* output, LibResourceRecord114* input, s32 kind)
{
    memset_guess(output, 0, sizeof(LibResourceRecordC4));
    memset_guess(input, 0, sizeof(LibResourceRecord114));

    switch (kind)
    {
    case 1:
        func_00458110(reinterpret_cast<LibCharacterRecord*>(output), reinterpret_cast<LibCharacterEquipment*>(input));
        break;
    case 2:
        func_00457B20(reinterpret_cast<LibCharacterRecord*>(output), reinterpret_cast<LibCharacterEquipment*>(input));
        break;
    case 0:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        break;
    }

    output->kind = kind;
    output->unk02 = 0;
}

#pragma pop

// TODO: Like the saved-data functions around it, this only matches at optimization level 0.
#pragma push
#pragma optimization_level 0

/**
 * @brief Apply the saved sound output mode, speaker angles and vibration setting.
 * @param settings System settings.
 */
void func_004587C0(LibSystemSettings* settings)
{
    u8 output = settings->sound_output;

    switch (output)
    {
    case 0:
        resident_sound_set_output_mode(g_sound, 1);
        break;
    case 1:
        resident_sound_set_output_mode(g_sound, 0);
        break;
    case 2:
        resident_sound_set_output_mode(g_sound, 2);
        break;
    case 3:
        resident_sound_set_output_mode(g_sound, 3);
        break;
    }

    float* angles = settings->speaker_angles;
    resident_sound_set_speaker_angles(g_sound, angles);
    s32 vibration = (u8)settings->vibration;
    resident_pad_set_vibration_enabled(g_input_system, 0, vibration);
}

#pragma pop

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004588E0);

// TODO: This only matches with tree transformation, constant folding, lifetime splitting and loop rotation
// off: the inlined checksum keeps unfolded loop bounds and one accumulator register. I haven't found the
// build setting behind it.
#pragma push
#pragma opt_treetransformation off
#pragma opt_foldconstants off
#pragma opt_lifetimes off
#pragma opt_rotateloops off

/**
 * @brief Encode a saved record and seal it with a fresh checksum; a damaged record is wiped instead.
 * @param record Record to seal; an already sealed record is left alone.
 */
extern "C" void lib_seal_record(LibSealedRecord* record)
{
    s32 i;

    if (record->sealed == 0)
    {
        record->sealed = LIB_RECORD_SEALED;
        record->unk00 ^= LIB_RECORD_XOR_BYTE;
        record->unk02 ^= LIB_RECORD_XOR_HALFWORD;
        record->unk04 ^= LIB_RECORD_XOR_WORD;
        record->unk08 ^= LIB_RECORD_XOR_WORD;
        record->unk0C ^= LIB_RECORD_XOR_WORD;
        record->unk10 ^= LIB_RECORD_XOR_WORD;
        record->unk14 ^= LIB_RECORD_XOR_WORD;
        record->unk18 ^= LIB_RECORD_XOR_WORD;
        record->unk1C ^= LIB_RECORD_XOR_WORD;
        record->unk20 ^= LIB_RECORD_XOR_WORD;
        record->unk24 ^= LIB_RECORD_XOR_WORD;
        record->unk28 ^= LIB_RECORD_XOR_WORD;
        record->unk2C ^= LIB_RECORD_XOR_WORD;
        record->unk30 ^= LIB_RECORD_XOR_WORD;
        record->unk34 ^= LIB_RECORD_XOR_WORD;
        record->unk38 ^= LIB_RECORD_XOR_WORD;
        record->unk3C ^= LIB_RECORD_XOR_WORD;
        record->unk40 ^= LIB_RECORD_XOR_WORD;
        record->unk44 ^= LIB_RECORD_XOR_WORD;
        record->unk48 ^= LIB_RECORD_XOR_WORD;
        record->unk4C ^= LIB_RECORD_XOR_WORD;
        record->unk50 ^= LIB_RECORD_XOR_WORD;
        record->unk54 ^= LIB_RECORD_XOR_WORD;
        record->unk58 ^= LIB_RECORD_XOR_WORD;

        for (i = 0; i < LIB_RECORD_ENCODED_TAIL_SIZE; i++)
        {
            record->encoded_tail[i] ^= LIB_RECORD_XOR_BYTE;
        }

        record->key = resident_next_random_word();
        record->checksum = lib_compute_checksum(record->key * LIB_RECORD_CHECKSUM_KEY_FACTOR, record, (u8*)&record->checksum - (u8*)record);
    }
    else if (record->sealed != LIB_RECORD_SEALED)
    {
        memset_guess(record, 0, sizeof(LibSealedRecord));
    }
}

#pragma pop

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", lib_options_set_color_unlock_level);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", lib_options_set_fourth_dimension_unlocked);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", lib_options_set_universe_unlocked);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", lib_options_set_unk18);





// TODO: Freeing the settings inlines the trophy flags' destructor, which text_004095C0 keeps out of line, so it's
// only inline in this unit.
/** @brief Destroy the flags. */
inline LibTrophyFlags::~LibTrophyFlags()
{
}

// TODO: Like the saved-data functions before it, this only matches at optimization level 0.
#pragma push
#pragma optimization_level 0

/** @brief Free the system settings, the two record arrays and the padding block, and remove their entries. */
void lib_free_system_data(void)
{
    ResidentEntryTable* table = resident_get_entry_table(resident_get_system());

    LibSystemSettings* settings = reinterpret_cast<LibSystemSettings*>(resident_find_entry(table, LIB_ENTRY_SYSTEM_SETTINGS));
    delete settings;
    LibResourceRecordC4* outputs = reinterpret_cast<LibResourceRecordC4*>(resident_find_entry(table, LIB_ENTRY_RECORD_OUTPUTS));
    delete[] outputs;
    LibResourceRecord114* inputs = reinterpret_cast<LibResourceRecord114*>(resident_find_entry(table, LIB_ENTRY_RECORD_INPUTS));
    delete[] inputs;
    u8* padding = reinterpret_cast<u8*>(resident_find_entry(table, LIB_ENTRY_PADDING));
    delete[] padding;
    resident_remove_entry(table, LIB_ENTRY_SYSTEM_SETTINGS);
    resident_remove_entry(table, LIB_ENTRY_RECORD_OUTPUTS);
    resident_remove_entry(table, LIB_ENTRY_RECORD_INPUTS);
    resident_remove_entry(table, LIB_ENTRY_PADDING);
    func_003EF860();
}

#pragma pop

#define LIB_SYSTEM_DATA_SHUFFLES 100
#define LIB_RESOURCE_RECORD_COUNT 8

extern "C" void func_0040B760(void);

extern "C" void func_004588E0(LibSystemSettings* settings);

// TODO: Like the saved-data functions before it, this only matches at optimization level 0.
#pragma push
#pragma optimization_level 0

/**
 * @brief Allocate the system settings, the two record arrays and func_0040B760's data in a random order, after a
 *        random-sized padding block, register them in the resident entry table and initialize them.
 *
 * Entry 8 is allocated and cleared only when it is missing.
 */
void lib_allocate_system_data(void)
{
    s32 order[4];
    s32 i;
    u8* entry8;
    ResidentEntryTable* table;
    s32 j;
    LibSystemSettings* settings;
    LibResourceRecordC4* outputs;
    LibResourceRecord114* inputs;

    for (i = 0; i < 4; i++)
    {
        order[i] = i;
    }

    for (s32 k = 0; k < LIB_SYSTEM_DATA_SHUFFLES; k++)
    {
        s32 first = resident_random_below(4);
        s32 second = resident_random_below(4);
        s32 swap = order[first];
        order[first] = order[second];
        order[second] = swap;
    }

    entry8 = 0;
    table = resident_get_entry_table(resident_get_system());
    entry8 = reinterpret_cast<u8*>(resident_find_entry(table, LIB_ENTRY_08));

    if (entry8 == 0)
    {
        entry8 = reinterpret_cast<u8*>(new (0) u64);
        memset_guess(entry8, 0, sizeof(u64));
        resident_store_entry(table, entry8, LIB_ENTRY_08);
    }

    u8* padding = new (0) u8[resident_random_below(16) * sizeof(u32) + 16];
    resident_store_entry(table, padding, LIB_ENTRY_PADDING);

    for (j = 0; j < 4; j++)
    {
        switch (order[j])
        {
        case 0:
            settings = new (0) LibSystemSettings;
            memset_guess(settings, 0, sizeof(LibSystemSettings));
            break;
        case 1:
            outputs = new (0) LibResourceRecordC4[LIB_RESOURCE_RECORD_COUNT];
            memset_guess(outputs, 0, sizeof(LibResourceRecordC4));
            break;
        case 2:
            inputs = new (0) LibResourceRecord114[LIB_RESOURCE_RECORD_COUNT];
            memset_guess(inputs, 0, sizeof(LibResourceRecord114));
            break;
        case 3:
            func_0040B760();
            break;
        }
    }

    resident_store_entry(table, settings, LIB_ENTRY_SYSTEM_SETTINGS);
    resident_store_entry(table, outputs, LIB_ENTRY_RECORD_OUTPUTS);
    resident_store_entry(table, inputs, LIB_ENTRY_RECORD_INPUTS);
    func_00458700(&outputs[0], &inputs[0], 1);
    func_00458700(&outputs[1], &inputs[1], 0);
    func_00458700(&outputs[2], &inputs[2], 0);
    func_00458700(&outputs[3], &inputs[3], 0);
    func_00458700(&outputs[4], &inputs[4], 0);
    func_00458700(&outputs[5], &inputs[5], 0);
    func_00458700(&outputs[6], &inputs[6], 0);
    func_00458700(&outputs[7], &inputs[7], 0);
    func_004588E0(settings);
}

#pragma pop

/**
 * @brief Report the list kind.
 * @return Nine.
 */
s32 LibClass174D70::get_default_list_kind()
{
    return 9;
}

/** @brief Copy the first display manager's camera transform (flag 0x1), fog (0x2) and view (0x4) to the others. */
void LibClass174D70::update()
{
    LibCamera* source = static_cast<LibCamera*>(managers[0]->current_display);

    if (source)
    {
        for (s32 i = 0; i < count; i++)
        {
            LibCamera* camera = static_cast<LibCamera*>(managers[i + 1]->current_display);

            if (camera)
            {
                if (flags & 0x1)
                {
                    camera->set_translation_vector(&source->translation);
                    camera->set_orientation(&source->orientation);
                    camera->set_scale_vector(&source->scale);
                }

                if (flags & 0x2)
                {
                    float offset;
                    float reciprocal_scale;

                    camera->fog_color = source->fog_color;
                    source->get_fog_coefficients(&offset, &reciprocal_scale);
                    camera->set_fog_coefficients(offset, reciprocal_scale);
                    camera->set_near_fog_fraction(source->near_fog_fraction);
                    camera->set_far_fog_fraction(source->far_fog_fraction);
                    camera->fog_enabled = source->fog_enabled;
                }

                if (flags & 0x4)
                {
                    camera->horizontal_fov = source->horizontal_fov;
                    camera->pixel_aspect = source->pixel_aspect;
                    camera->width_scale = source->width_scale;
                }
            }
        }
    }
}
