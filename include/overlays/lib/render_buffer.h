#ifndef SO3_OVERLAYS_LIB_RENDER_BUFFER_H
#define SO3_OVERLAYS_LIB_RENDER_BUFFER_H

#include "types.h"
#include "main/resident_001001E0.h"
#include "sdk/main/libkernl_00121940.h"

#ifdef __cplusplus
class LibClass171E90;

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
    LibClass171E90* children;

    /** Nonzero when data is borrowed and must not be freed. */
    u8 external_data;

    u8 unk1d;

    /** Nonzero while registered with the resource manager. */
    u8 registered;

    u8 unk1f;
};

/** Primitive command buffers with block storage and eight texture slots. */
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
    u8 unk2c[0x34];
    u32* block_sizes;
    u8* block_packets;
    u8* setup_packet;
    u32 unk6c;
    s32 word_capacity;
    s32 block_capacity;
    s32 block_count;
    s32 texture_count;
    s16 vertex_count;
    s16 primitive_count;
    u16 texture_codes[8];
    u8 texture_width_log2[8];
    u8 texture_height_log2[8];
    void* textures[8];
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

#endif
