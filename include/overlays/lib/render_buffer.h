#ifndef SO3_OVERLAYS_LIB_RENDER_BUFFER_H
#define SO3_OVERLAYS_LIB_RENDER_BUFFER_H

#include "types.h"
#include "main/decode.h"
#include "sdk/main/libkernl_00121940.h"
#include "overlays/lib/vector.h"
#include "gs.h"
#include "ee.h"

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
        payload_override = 0;
        children = 0;
        external_data = 0;
        unk1d = 0;
        registered = 0;
    }

    /** @brief Unregister the resource and release owned data. */
    virtual ~LibResourceBuffer();

    /** @brief Unregister the resource from the resource manager if it is registered. */
    void unregister();

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

    void* data;
    void* record_cursor;
    void* unk10;
    void* payload_override;
    LibListSentinel* children;
    u8 external_data;
    u8 unk1d;
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

#define LIB_IMAGE_CHUNK_MAGIC 0x00534946

/** Header of a FIS image; the image block sits image_offset bytes after it. */
struct LibImageHeader
{
    u8 unk00[4];
    char name[4];
    s32 id;
    u32 image_offset;
    u8 unk10[4];
    u32 palette_offset;
};

/** Block of a FIS image that holds its size; the width and height are powers of two. */
struct LibImageInfo
{
    u8 unk00[8];
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

/**
 * @brief Return the payload a model draws: the override when one is set, otherwise the resource's own.
 * @param buffer Resource to read.
 * @return Payload pointer, or null when there's neither.
 */
static inline u8* lib_resource_active_payload(LibResourceBuffer* buffer)
{
    if (buffer->payload_override != 0)
    {
        return static_cast<u8*>(buffer->payload_override);
    }

    if (buffer->data == 0)
    {
        return 0;
    }

    return buffer->external_data ? static_cast<u8*>(buffer->data) + sizeof(LibResourceChunkHeader) :
                                   reinterpret_cast<u8*>(RESIDENT_ALIGN_RESOURCE(buffer->data)) + sizeof(LibResourceChunkHeader);
}

/** Primitive command buffers with block storage and eight texture slots. */
/** Packet at the start of each draw buffer's commands, written through the uncached segment. */
struct LibDrawSetupPacket
{
    u32 size;
    u32 unk04;
    u8 unk08[4];
    u32 unk0c;
    u32 unk10;
    u32 unk14;
    float unk18;
    u8 unk1c[0x18];
    u32 batch_count;
    u32 command_size;
    u8 unk3C;
    u8 unk3D;
    u8 unk3e;
    u8 unk3f;
    u8 unk40[4];
    u32 unk44;
    u32 unk48;
    u32 unk4c;
    u32 unk50;
    s16 unk54;
    u8 unk56;
    u8 unk57[9];
};

#define LIB_DRAW_QWORD_SIZE 16
#define LIB_DRAW_INFO_VU_QWORDS 7
#define LIB_DRAW_STATE_VU_QWORDS 14
#define LIB_DRAW_BATCH_HAS_STATE 0x1
#define LIB_DRAW_BATCH_FLAG_04 0x4
#define LIB_DRAW_BATCH_FLAG_08 0x8
#define LIB_DRAW_ALPHA_SUBTRACT 0x42
#define LIB_DRAW_REGISTER_WRITES 4
#define LIB_DRAW_AD_REGISTERS 0xEEEEEEEE

/** GIF register list and tag for each primitive's vertices: ST, RGBAQ and XYZF2. */
#define LIB_DRAW_VERTEX_REGISTERS (GIF_REGISTER_ST | (GIF_REGISTER_RGBAQ << 4) | (GIF_REGISTER_XYZF2 << 8))
#define LIB_DRAW_PRIMITIVE_TAG (GIF_TAG_NREG(3) | GIF_TAG_PRE | GIF_TAG_EOP)

#define LIB_DRAW_TEXTURE_PACKET_SIZE 48

/** ALPHA_1 value for each blend mode. */
extern "C" const u64 D_004ED320[];

#define LIB_DRAW_BATCH_VERTEX_COUNT 40
#define LIB_DRAW_BATCH_PRIMITIVE_COUNT 32
#define LIB_DRAW_BATCH_STRIDE 0xC00

/** Start of each scratchpad block: the DMA tag that copies it out, then the VIF codes that unpack it. */
struct LibDrawBlockHeader
{
    u64 dma_tag;
    u64 unk08;

    union
    {
        u32 vif_codes[4];
        unsigned __int128 vif_qword;
    };
};

/** Batch description the microprogram reads: where each stream starts, in VU memory and in the commands. */
struct LibDrawBatchInfo
{
    u32 vif_code;
    s16 size;
    s16 unk4c_address;
    s16 primitive_count;
    s16 primitive_address;
    u8 unk0c[8];
    u16 flags;
    s16 vertex_count;
    s16 position_offset;
    s16 unk4c_offset;
    s16 texcoord_offset;
    s16 color_offset;
    s16 primitive_offset;
    s16 unk22;
    u32 unk24;
    u32 unk28;
    s16 unk2c[4];
    u32 unk34;
    u64 unk38;
};

/** First block of a batch: its DMA tag, then the batch description. */
struct LibDrawChainBlock
{
    u64 dma_tag;
    u64 unk08;
    LibDrawBatchInfo info;
};

/**
 * Draw state the batch microprogram reads: GS register writes in A+D form, with its own
 * parameters in the words the GS ignores.
 */
struct LibDrawState
{
    u32 vif_codes[4];
    GsGifTag register_tag;
    u32 alpha;
    u32 unk24;
    u32 alpha_address;
    u32 blend;
    u64 tex0;

    union
    {
        u64 tex0_address;
        u32 tex0_address_words[2];
    };

    u64 unk40;
    u64 unk48;

    float unk50;
    float unk54;
    float unk58;
    u8 unk5c[4];
    GsGifTag primitive_tag;
    GsGifTag fan_tag;
    u32 unk80;
    u8 unk84[4];
    u32 texture_index;
    u32 unk8c;
    u8 unk90[4];
    float unk94;
    u8 unk98[0x14];
    u32 unkac;
    u8 unkb0[0x40];
};

/** Draw state block: its DMA tag, then the state. */
struct LibDrawStateBlock
{
    u64 dma_tag;
    u64 unk08;
    LibDrawState state;
};

/** Per-primitive vertex counts. */
struct LibDrawPrimitiveBlock
{
    LibDrawBlockHeader header;
    u8 sizes[LIB_DRAW_BATCH_PRIMITIVE_COUNT];
};

/** One vector per vertex. */
struct LibDrawVectorBlock
{
    LibDrawBlockHeader header;
    unsigned __int128 vectors[LIB_DRAW_BATCH_VERTEX_COUNT];
};

/** One word per vertex. */
struct LibDrawWordBlock
{
    LibDrawBlockHeader header;

    union
    {
        u32 words[LIB_DRAW_BATCH_VERTEX_COUNT];
        unsigned __int128 qwords[LIB_DRAW_BATCH_VERTEX_COUNT / 4];
    };
};

/** Settings applied to a draw buffer before its next primitives. */
struct LibDrawSettings
{
    u16 prim;
    u8 blend_mode;
    u8 texture_index;
    u8 unk04;
    u8 unk05;
    u8 unk06;
    u8 unk07;
    float unk08;
    float unk0C;
    float unk10;
    float unk14;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
};

#define LIB_DRAW_COMMAND_HEADER_WORDS 16
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
    u32* command_cursor;
    LibDrawChainBlock* chain_block;
    LibDrawStateBlock* state_block;
    LibDrawPrimitiveBlock* primitive_block;
    u8* primitive_sizes;
    LibDrawVectorBlock* position_block;
    FieldVec4A* positions;
    LibDrawVectorBlock* normal_block;
    FieldVec4A* normals;
    LibDrawWordBlock* texcoord_block;
    u32* texcoords;
    LibDrawWordBlock* color_block;
    u32* colors;
    u32* block_sizes;
    u8* block_packets;
    LibDrawSetupPacket* setup_packet;
    u32 batch_count;
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
    u8 state_pending;
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

    /**
     * @brief Copy out any pending vertices, then write the draw state the next primitives use.
     *
     * Sets the texture, blend, primitive tags and the settings' other parameters, and marks the state for the next batch.
     * @param buffer Draw buffer.
     * @param settings Settings to apply.
     */
    void lib_draw_buffer_apply_settings(LibDrawBuffer* buffer, LibDrawSettings* settings);

    /**
     * @brief Close the scratchpad batch and copy it into the command buffer.
     *
     * Writes each block's DMA tag and VIF codes, pads the streams to whole quadwords, then waits for the previous copy
     * and starts this one. A batch that wouldn't fit in the command buffer is dropped and its vertices stay pending.
     * @param buffer Draw buffer.
     */
    void lib_draw_buffer_flush_batch(LibDrawBuffer* buffer);

    /**
     * @brief Copy out any pending vertices, then lay out the next scratchpad batch and switch to the other half.
     * @param buffer Draw buffer.
     */
    void lib_draw_buffer_start_batch(LibDrawBuffer* buffer);

    // lib_draw_buffer_end isn't declared here: its definition takes an s32 mode, but the image code in boot and the
    // field calls it through a u8 prototype, so each side declares its own.
}
#endif

#endif
