#ifndef SO3_OVERLAYS_LIB_RENDER_BUFFER_H
#define SO3_OVERLAYS_LIB_RENDER_BUFFER_H

#include "types.h"
#include "main/resident_001001E0.h"
#include "main/resident_00101550.h"
#include "sdk/main/libkernl_00121940.h"
#include "overlays/lib/vector.h"

#ifdef __cplusplus
class LibListSentinel;

/** Partially known payload header with an offset to its data. */
struct LibResourcePayloadHeader
{
    u8 unk00[8];
    u32 data_offset;
};

/** Rendering-resource base with its virtual pointer after two state bytes. */
class LibRenderResource
{
public:
    u8 unk00;
    u8 unk01;

    /** @brief Clear the resource state bytes. */
    LibRenderResource()
    {
        unk00 = 0;
        unk01 = 0;
    }

    /** @brief Destroy the resource base. */
    virtual ~LibRenderResource()
    {
    }
};

/** Resource storage with borrowed-data and manager-registration state. */
class LibResourceBuffer : public LibRenderResource
{
public:
    /** @brief Initialize the resource pointers and state flags. */
    LibResourceBuffer()
    {
        data = 0;
        unk14 = 0;
        children = 0;
        external_data = 0;
        unk1d = 0;
        registered = 0;
    }

    /** @brief Unregister the resource and release owned data. */
    virtual ~LibResourceBuffer();

    /**
     * @brief Read the data referenced by the resource payload header.
     * @return Data pointer, or null when storage or the stored data offset is zero.
     */
    virtual void* get_data();

    /**
     * @brief Resolve a stored byte offset relative to the resource payload.
     *
     * Borrowed storage has a 16-byte prefix. Owned storage is aligned to
     * 128 bytes before skipping that prefix. Nonzero offsets require storage.
     * @param offset Pointer to the stored byte offset.
     * @return Resolved pointer, or null when the stored offset is zero.
     */
    virtual void* resolve_offset(const u32* offset);

    /**
     * @brief Find an indexed entry across the linked child resources.
     *
     * Skip children whose entry count is zero or negative.
     * @param index Entry index across the children; negative values reach the first nonempty child.
     * @return Entry pointer, or null when no child supplies the index.
     */
    virtual void* find_child_data(s32 index);

    /** Backing allocation or borrowed resource block. */
    void* data;

    u8 unk0c[8];
    u32 unk14;

    /** Intrusive sentinel for the channels supplying child entries. */
    LibListSentinel* children;

    /** Nonzero when data is borrowed and must not be freed. */
    u8 external_data;

    u8 unk1d;

    /** Nonzero while registered with the resource manager. */
    u8 registered;

    u8 unk1f;
};

/** Header shared by the linked image and sequence chunks. */
struct LibResourceChunkHeader
{
    u32 magic;
    u32 payload_size;
    u32 previous_offset;
    u32 next_offset;
};

/** Magic of a FIS image chunk ("FIS"). */
#define LIB_IMAGE_CHUNK_MAGIC 0x00534946

/** Header of a FIS image; the image block sits image_offset bytes after it. */
struct LibImageHeader
{
    u8 unk00[4];
    char name[4];
    s32 id;
    u32 image_offset;
    u8 unk10[4];

    /** Offset of the palette block from the header. */
    u32 palette_offset;
};

/** Block of a FIS image that holds its size; the width and height are powers of two. */
struct LibImageInfo
{
    u8 unk00[8];

    /** Offset of the pixel block from the image header. */
    u32 pixel_offset;

    u16 texture_code;
    u8 width_log2;
    u8 height_log2;
};

/** A FIS image chunk: the chunk header, then the image header. */
struct LibImageResource
{
    LibResourceChunkHeader chunk;
    LibImageHeader header;
};

/**
 * @brief Return the size block of an image.
 * @param resource Image chunk.
 * @return Its size block.
 */
static inline const LibImageInfo* lib_image_info(const LibImageResource* resource)
{
    const LibImageHeader* header = &resource->header;
    return (const LibImageInfo*)((const u8*)header + header->image_offset);
}

/**
 * @brief Step to the next chunk in a resource's chunk list.
 * @param chunk Current chunk.
 * @return The next chunk, or null at the end of the list.
 */
static inline LibResourceChunkHeader* lib_next_chunk(LibResourceChunkHeader* chunk)
{
    return chunk->next_offset == 0 ? 0 :
        reinterpret_cast<LibResourceChunkHeader*>(reinterpret_cast<u8*>(chunk) + chunk->next_offset);
}

/**
 * @brief Step to the next chunk in a read-only chunk list.
 * @param chunk Current chunk.
 * @return The next chunk, or null at the end of the list.
 */
static inline const LibResourceChunkHeader* lib_next_chunk(const LibResourceChunkHeader* chunk)
{
    return chunk->next_offset == 0 ? 0 :
        reinterpret_cast<const LibResourceChunkHeader*>(reinterpret_cast<const u8*>(chunk) + chunk->next_offset);
}

/**
 * @brief Locate the payload after the resource's chunk header. Owned storage is aligned before the header.
 * @param buffer Resource whose backing storage is inspected.
 * @return Payload pointer, or null when no backing storage is present.
 */
static inline u8* lib_resource_payload(LibResourceBuffer* buffer)
{
    return buffer->data == 0 ? 0 :
        buffer->external_data ? static_cast<u8*>(buffer->data) + sizeof(LibResourceChunkHeader) :
        reinterpret_cast<u8*>(RESIDENT_ALIGN_RESOURCE(buffer->data)) + sizeof(LibResourceChunkHeader);
}

/** Primitive command buffers with block storage and eight texture slots. */
/** Packet at the start of each draw buffer's commands, written through the uncached segment. */
struct LibDrawSetupPacket
{
    u8 unk00[0x3C];
    u8 unk3C;
    u8 unk3D;
    u8 unk3E[0x16];
    s16 unk54;
    u8 unk56;
    u8 unk57[9];
};

/** Words at the start of each command buffer before the setup packet. */
#define LIB_DRAW_COMMAND_HEADER_WORDS 16

/** Textures one draw buffer can use at once. */
#define LIB_DRAW_BUFFER_TEXTURE_COUNT 8

class LibDrawBuffer : public LibResourceBuffer
{
public:
    /** @brief Initialize empty command storage and texture bookkeeping. */
    LibDrawBuffer();

    /** @brief Release command buffers, block sizes and packet storage. */
    virtual ~LibDrawBuffer();

    /**
     * @brief Allocate command buffers, block sizes and packet storage.
     *
     * Earlier allocations remain stored when a later allocation fails.
     * @param buffer_count Command-buffer count, at most two.
     * @param word_capacity Word count before the 32-word allocation overhead.
     * @param block_capacity Number of entries in the block-size array.
     * @param staging_blocks Packet-block count, capped at block_capacity before adding two extra blocks.
     * @return True when all allocations succeed; false on the first failure.
     */
    bool allocate_storage(s32 buffer_count, s32 word_capacity, s32 block_capacity, s32 staging_blocks);

    u32* command_buffers[2];
    u32* command_begin;

    /** Next free word of the command buffer. */
    u32* command_cursor;

    u8 unk30[0xC];

    /** Next byte of the per-primitive vertex counts. */
    u8* primitive_sizes;

    u8 unk40[4];

    /** Next free slot of the vertex position stream. */
    FieldVec4A* positions;

    u8 unk48[4];

    /** Next free slot of the second per-vertex vector stream. */
    FieldVec4A* unk4c;

    u8 unk50[4];

    /** Next free slot of the packed texture coordinate stream: u in the low half, v in the high half, 4.12 fixed point. */
    u32* texcoords;

    u8 unk58[4];

    /** Next free slot of the vertex color stream. */
    u32* colors;
    u32* block_sizes;
    u8* block_packets;
    LibDrawSetupPacket* setup_packet;
    u32 unk6c;
    s32 word_capacity;
    s32 block_capacity;
    s32 block_count;
    s32 texture_count;
    s16 vertex_count;
    s16 primitive_count;
    u16 texture_codes[LIB_DRAW_BUFFER_TEXTURE_COUNT];
    u8 texture_width_log2[LIB_DRAW_BUFFER_TEXTURE_COUNT];
    u8 texture_height_log2[LIB_DRAW_BUFFER_TEXTURE_COUNT];
    const LibImageHeader* textures[LIB_DRAW_BUFFER_TEXTURE_COUNT];
    u8 command_buffer_index;
    u8 command_buffer_count;
    u8 scratchpad_index;
    u8 unkc7[4];
    u8 unkcb;
    u8 unkcc;
    u8 unkcd;
    u8 unkce;
    u8 unkcf;
};

#endif

#ifdef __cplusplus
extern "C"
{
    /**
     * @brief Start a primitive of some vertices, flushing the buffer first when they wouldn't fit in 40.
     * @param buffer Draw buffer.
     * @param count Vertices in the primitive.
     */
    void lib_draw_buffer_begin_primitive(LibDrawBuffer* buffer, s32 count);

    /**
     * @brief Add an image's texture to the draw buffer's next texture slot.
     * @param buffer Draw buffer.
     * @param resource Resource whose chunk list holds the image.
     * @return The slot, or -1 when the resource has no image chunk or every slot is taken.
     */
    s32 lib_draw_buffer_add_texture(LibDrawBuffer* buffer, const LibImageResource* resource);

    /**
     * @brief Start a new packet in the draw buffer's current command buffer, then stop the DMA queue it goes out on.
     * @param buffer Draw buffer.
     * @param unk3C Stored in the setup packet at 0x3C.
     * @param unk3D Stored in the setup packet at 0x3D.
     */
    void lib_draw_buffer_begin(LibDrawBuffer* buffer, u8 unk3C, u8 unk3D);
}
#endif

#endif
