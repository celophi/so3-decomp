#include "overlays/lib/dma_callbacks_inlines.h"
#include "include_asm.h"
#include "overlays/lib/render_buffer.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "main/resident_00101260.h"
#include "overlays/lib/text_003F90C0.h"
#include "overlays/lib/text_003E68C0.h"
#include "sdk/main/libdma_0012B2C8.h"
#include "sdk/main/libkernl_00121940.h"
#include "overlays/lib/text_0044ABE0.h"
#include "overlays/lib/text_004BD360.h"
#include "main/resident_data.h"

extern "C" u8 D_00174D30[];
extern "C" void func_004A8F10(void* object);
/** Partial indexed-resource fields at CC and D0. */
typedef struct LibIndexedResourceState
{
    u8 pad00[0xCC];
    s32 current;
    s32 selected;
} LibIndexedResourceState;
extern "C" s32 func_00464EF0(FieldRuntime* runtime, s32 index);
extern "C" s32 func_00467800(ItemCreationClass174C40* object, s32 resource, s32 first, s32 second, s32 third, s32 fourth, float x, float y);
extern "C" void func_00465A90(void* owner, LibCallbackTransform* object);
extern "C" ResidentDmaQueue* g_vif1_dma_queue;
extern "C" ResidentDmaQueue* D_001B6604;
extern "C" void func_00454E90(LibDrawBuffer* buffer);
extern "C" void func_004D5A50(LibDrawBuffer* buffer, u32* commands);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044ABE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044ACF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044AD80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044AE70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", __dt__20LibCallbackTransformFv);

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
    unkae = 1;
}

/** @brief Update the vector's x and y components while preserving z. */
extern "C" void func_0044B190(LibVectorUpdateView* state, float x, float y)
{
    float z = state->unk20.z;
    state->unk20.x = x;
    state->unk20.y = y;
    state->unk20.z = z;
    state->unk20.w = 1.0f;
    state->unkAE = 1;
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044B240);

/** @brief Initialize transform flags and drawing modes after the base receivers. */
LibCallbackTransform::LibCallbackTransform()
{
    draw_flags |= 0x400;
    unk94 = 0;
    unkaf = 0;
    unkae = 1;
    unkad = 1;
    unkac = 1;
    unkab = 1;
    unkaa = 2;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044B350);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044B5E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044B6A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044B860);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044B9E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044BCC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044BDF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044BEE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044BF50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044BF60);

/** @brief Set the receiver's byte at offset 0x60 to 8. @param object Receiver to update. */
void func_0044C050(LibObjectByte60* object)
{
    object->unk60 = 8;
}

/** @brief Perform no work. @param object Unused receiver. */
void func_0044C060(void* object)
{
}

extern "C" u8 D_00508240[];

/** @brief Return the address of D_00508240. @return The data symbol's address. */
const void* func_0044C070(void)
{
    return D_00508240;
}

/** @brief Expire every cached copy of texture 1. */
void func_0044C080(void)
{
    g_texture_cache->expire_texture(1);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044C0A0);

/** @brief Forward the receiver to the base transform update. @param object Transform receiver. */
void func_0044C0F0(void* object)
{
    lib_finish_packet(static_cast<LibTransformOwner*>(object));
}

/** @brief Queue the receiver's DMA callback interface. */
extern "C" s32 func_0044C110(LibCallbackTransform* object)
{
    LibDmaCallbacks* submission = static_cast<LibDmaCallbacks*>(object);
    return func_00114100(g_vif1_dma_queue, reinterpret_cast<DmaSubmission*>(submission));
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044C140);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044CE10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044CF30);

/** @brief Set the receiver's byte at offset 0x60 to 8. @param object Receiver to update. */
extern "C" void func_0044D070(LibObjectByte60* object)
{
    object->unk60 = 8;
}

extern "C" u8 D_00508230[];

/** @brief Return the address of D_00508230. @return The data symbol's address. */
extern "C" const void* func_0044D080(void)
{
    return D_00508230;
}

/** @brief Clear the intrusive owner and invoke the base transform release. @param object Transform owner to detach. */
extern "C" void func_0044D090(LibTransformOwner* object)
{
    object->owner = 0;
    object->LibTransformOwner::destroy();
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044D0B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044D0C0);

/** Partial singleton view for the display pointer at +0x4458. */
typedef struct LibDisplayManagerView
{
    u8 unk00[0x4458];
    void* current_display;
} LibDisplayManagerView;

/** Partial display view for the ready byte at +0x9C. */
typedef struct LibDisplayReadyView
{
    u8 unk00[0x9C];
    u8 ready;
} LibDisplayReadyView;

/** @brief Update the transform and mark the current display ready. @param object Transform receiver. */
extern "C" void func_0044D0D0(void* object)
{
    static_cast<LibTransform*>(object)->LibTransform::update();
    LibDisplayManagerView* manager = static_cast<LibDisplayManagerView*>(g_renderer);
    LibDisplayReadyView* display = static_cast<LibDisplayReadyView*>(manager->current_display);
    display->ready = 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044D100);

/** @brief Forward the receiver to the base transform update. @param object Transform receiver. */
extern "C" void func_0044D150(void* object)
{
    lib_finish_packet(static_cast<LibTransformOwner*>(object));
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044D170);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044D1D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044D600);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044D9C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044E080);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044E140);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044E430);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044E4D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044E560);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044E5F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044ED10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044ED80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044EE40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044EE90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044FC90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044FD30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044FDA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044FF80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044FFF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004517B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00451850);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004519F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00451A60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00451AA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00451AD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00451B20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00451B60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00451B90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00451C00);

/** @brief Return the fixed value 35. @param object Unused receiver. @return Always 35. */
extern "C" s32 func_00451E20(void* object)
{
    return 35;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00451E30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00452270);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00452390);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004526A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00452870);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00452CA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00452CD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00452DC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00452F00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00452FA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00453000);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00453080);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00453DD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00453EC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00453F30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00453F70);

/**
 * @brief Initialize resource pointers, drawing scales, colors, and descriptor defaults.
 * @param state State to initialize.
 */
extern "C" void lib_draw_state_init(LibDrawState64* state)
{
    state->unk04 = 0;
    state->unk00 = 0;
    state->unk08 = 0;
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00454060);

extern "C" s32 func_004540D0(void)
{
    return 0x2B;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004540E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00454300);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00454360);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004545C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00454650);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004546D0);

extern "C" s32 func_00454730(void)
{
    return 10;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00454740);

extern "C" s32 func_004547B0(void)
{
    return 0x2B;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004547C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004549F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00454A50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00454CB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00454D40);

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

extern "C" void func_00455AD0(LibDrawBuffer* buffer);

/**
 * @brief Start a primitive of some vertices, flushing the buffer first when they wouldn't fit in 40.
 * @param buffer Draw buffer.
 * @param count Vertices in the primitive.
 */
void lib_draw_buffer_begin_primitive(LibDrawBuffer* buffer, s32 count)
{
    if (buffer->vertex_count + count >= 40)
    {
        func_00455AD0(buffer);
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

    state->alpha = D_4ED320[settings->blend_mode];
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
    LibDrawVectorBlock* normals = buffer->unk4c_block;
    normals->header.dma_tag = DMA_TAG(buffer->vertex_count + 1, DMA_TAG_ID_CNT, buffer->command_cursor);
    normals->header.vif_qword = 0;
    address += primitive_count;

    for (s32 i = buffer->vertex_count; i < LIB_DRAW_BATCH_VERTEX_COUNT; i++)
    {
        normals->vectors[i] = 0;
    }

    buffer->unk4c_block->header.vif_codes[2] = VIF_STCYCL(4, 1);
    buffer->unk4c_block->header.vif_codes[3] = VIF_UNPACK(VIF_UNPACK_V4_32, buffer->vertex_count, address | VIF_UNPACK_ADD_TOPS);
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
    buffer->unk4c_block = reinterpret_cast<LibDrawVectorBlock*>(buffer->primitive_block + 1);
    buffer->texcoord_block = reinterpret_cast<LibDrawWordBlock*>(buffer->unk4c_block + 1);
    buffer->color_block = buffer->texcoord_block + 1;
    buffer->position_block = reinterpret_cast<LibDrawVectorBlock*>(buffer->color_block + 1);
    buffer->primitive_sizes = buffer->primitive_block->sizes;
    reinterpret_cast<unsigned __int128*>(buffer->primitive_sizes)[0] = 0;
    reinterpret_cast<unsigned __int128*>(buffer->primitive_sizes)[1] = 0;
    buffer->positions = reinterpret_cast<FieldVec4A*>(buffer->position_block->vectors);
    buffer->unk4c = reinterpret_cast<FieldVec4A*>(buffer->unk4c_block->vectors);
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
void lib_draw_buffer_end(LibDrawBuffer* buffer, s32 mode, float distance, s32 flag)
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
    func_00455AD0(buffer);

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


INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456190);

extern "C" s32 func_00456200(void)
{
    return 40;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456210);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456300);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456360);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456690);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456850);

void* func_004568A0(void* receiver)
{
    func_004A8F10(receiver);
    *(void**)receiver = D_00174D30;
    ((u8*)receiver)[0xE] = 2;
    return receiver;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004568E0);

extern "C" s32 func_00456940(void)
{
    return 6;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456950);

extern "C" s32 func_004569C0(void)
{
    return 36;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004569D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456A90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456AF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456B90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456CF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456D60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456DD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456E60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456F10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456F90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456FE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00457030);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004570C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00457190);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00457360);

// TODO: This only matches at optimization level 0, and with an unused local cleared at the start; I don't know
// what the local was for.
#pragma push
#pragma optimization_level 0

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", lib_trophy_flags_update_checksum);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004577A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00457980);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00457B20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00458110);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00458700);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004587C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004588E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004595C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00459990);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00459CA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00459FB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0045A2C0);

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

/** Times the allocation order is shuffled. */
#define LIB_SYSTEM_DATA_SHUFFLES 100

/** Records in each of the two record arrays. */
#define LIB_RESOURCE_RECORD_COUNT 8

extern "C" void func_0040B760(void);
extern "C" void func_00458700(LibResourceRecordC4* output, LibResourceRecord114* input, s32 mode);
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
        func_001014B0(table, entry8, LIB_ENTRY_08);
    }

    u8* padding = new (0) u8[resident_random_below(16) * sizeof(u32) + 16];
    func_001014B0(table, padding, LIB_ENTRY_PADDING);

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

    func_001014B0(table, settings, LIB_ENTRY_SYSTEM_SETTINGS);
    func_001014B0(table, outputs, LIB_ENTRY_RECORD_OUTPUTS);
    func_001014B0(table, inputs, LIB_ENTRY_RECORD_INPUTS);
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

extern "C" s32 func_0045ABA0(void)
{
    return 9;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0045ABB0);
