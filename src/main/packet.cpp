#include "main/resident_data.h"
#include "sdk/main/libdma_0012B2C8.h"
#include "main/packet.h"

#define GIF_TAG_AD_WRITE 0x1000000000000001ULL
#define GIF_TAG_END 0x8000
#define GIF_TAG_LINE 0x4400000000000001ULL
#define GIF_TAG_RECTANGLE 0x6400000000000001ULL

#define VIF_CODE_FLUSH 0x11000000

#define VIF_CODE_MSKPATH3 0x06000000
#define GS_PRIM_LINE 0x281
#define GS_PRIM_TRIANGLE_STRIP 0x204
#define GS_PRIM_ALPHA_BLEND 0x40

extern "C" {
extern ResidentDisplayContext* g_display;
extern struct LibPacketQueue* g_packet_queue;

s32 func_4DC4F0(struct LibPacketQueue* queue, u32 operation, u32 flags, u32 address, u32 value, void* completion);
}

/**
 * @brief Build an XYZ2 register value from a screen position.
 * @param x Horizontal GS coordinate in pixels.
 * @param y Vertical GS coordinate in pixels.
 * @param z Depth.
 * @return Packed XYZ2 value with 4-bit subpixel X and Y.
 */
static inline u64 resident_gs_xyz(s32 x, s32 y, s32 z)
{
    return ((u64)z << 32) | ((x << 4) | ((u64)(y << 4) << 16));
}

/**
 * @brief Get the packet cursor when a number of quadwords still fits.
 * @param packet Packet to inspect.
 * @param quadwords Number of 16-byte words required.
 * @return Current cursor, or null when the packet is too full.
 */
static inline u8* resident_packet_space(ResidentPacket* packet, s32 quadwords)
{
    u8* cursor = packet->unk08;

    if (cursor + quadwords * 16 > packet->unk00 + packet->unk10 * 8)
    {
        return 0;
    }

    return cursor;
}

/**
 * @brief Move the packet cursor to the next 16-byte boundary at or after a position.
 * @param packet Packet to update.
 * @param cursor New cursor.
 */
static inline void resident_packet_set_cursor(ResidentPacket* packet, u8* cursor)
{
    if (((u32)cursor & 0xF) != 0)
    {
        cursor = (u8*)(((u32)cursor + 0xF) & 0xFFFFFFF0);
    }

    packet->unk08 = cursor;
}

/**
 * @brief Append a GIF A+D write of one GS register when the packet has room.
 * @param packet Packet to append to.
 * @param address GS register address.
 * @param data Register value.
 */
void resident_packet_add_register(ResidentPacket* packet, u64 address, u64 data)
{
    ResidentGsRegisterWrite* write = (ResidentGsRegisterWrite*)resident_packet_space(packet, 2);

    if (write != 0)
    {
        write->tag.tag = GIF_TAG_AD_WRITE;
        write->tag.registers = 0;
        write->tag.fields.register0 = GIF_REGISTER_AD;
        write->data = data;
        write->address = address;
        resident_packet_set_cursor(packet, (u8*)(write + 1));
    }
}

/**
 * @brief Append a GIF A+D write of the GS PRIM register when the packet has room.
 * @param packet Packet to append to.
 * @param data Register value.
 */
void resident_packet_set_prim(ResidentPacket* packet, u64 data)
{
    ResidentGsRegisterWrite* write = (ResidentGsRegisterWrite*)resident_packet_space(packet, 2);

    if (write != 0)
    {
        write->tag.tag = GIF_TAG_AD_WRITE;
        write->tag.registers = 0;
        write->tag.fields.register0 = GIF_REGISTER_AD;
        write->data = data;
        write->address = GS_REGISTER_PRIM;
        resident_packet_set_cursor(packet, (u8*)(write + 1));
    }
}

/**
 * @brief Append a GIF A+D write of the GS TEX0_2 register when the packet has room.
 * @param packet Packet to append to.
 * @param data Register value.
 */
void resident_packet_set_tex0_2(ResidentPacket* packet, u64 data)
{
    ResidentGsRegisterWrite* write = (ResidentGsRegisterWrite*)resident_packet_space(packet, 2);

    if (write != 0)
    {
        write->tag.tag = GIF_TAG_AD_WRITE;
        write->tag.registers = 0;
        write->tag.fields.register0 = GIF_REGISTER_AD;
        write->data = data;
        write->address = GS_REGISTER_TEX0_2;
        resident_packet_set_cursor(packet, (u8*)(write + 1));
    }
}

/**
 * @brief Append a GIF A+D write of the GS ALPHA_1 register when the packet has room.
 * @param packet Packet to append to.
 * @param data Register value.
 */
void resident_packet_set_alpha_1(ResidentPacket* packet, u64 data)
{
    ResidentGsRegisterWrite* write = (ResidentGsRegisterWrite*)resident_packet_space(packet, 2);

    if (write != 0)
    {
        write->tag.tag = GIF_TAG_AD_WRITE;
        write->tag.registers = 0;
        write->tag.fields.register0 = GIF_REGISTER_AD;
        write->data = data;
        write->address = GS_REGISTER_ALPHA_1;
        resident_packet_set_cursor(packet, (u8*)(write + 1));
    }
}

/**
 * @brief Append a GIF A+D write of the GS ALPHA_2 register when the packet has room.
 * @param packet Packet to append to.
 * @param data Register value.
 */
void resident_packet_set_alpha_2(ResidentPacket* packet, u64 data)
{
    ResidentGsRegisterWrite* write = (ResidentGsRegisterWrite*)resident_packet_space(packet, 2);

    if (write != 0)
    {
        write->tag.tag = GIF_TAG_AD_WRITE;
        write->tag.registers = 0;
        write->tag.fields.register0 = GIF_REGISTER_AD;
        write->data = data;
        write->address = GS_REGISTER_ALPHA_2;
        resident_packet_set_cursor(packet, (u8*)(write + 1));
    }
}

/**
 * @brief Append a flat-coloured rectangle, drawn as a triangle strip, when the packet has room.
 * @param packet Packet to append to.
 * @param x0 Left edge, relative to the centre of the viewport.
 * @param y0 Top edge, relative to the centre of the viewport.
 * @param x1 Right edge, relative to the centre of the viewport.
 * @param y1 Bottom edge, relative to the centre of the viewport.
 * @param z Depth.
 * @param color RGBA colour.
 */
void resident_packet_add_rectangle(ResidentPacket* packet, s32 x0, s32 y0, s32 x1, s32 y1, s32 z, u32 color)
{
    ResidentRectanglePacket* rectangle = (ResidentRectanglePacket*)resident_packet_space(packet, 4);

    if (rectangle != 0)
    {
        s32 offset_x;
        s32 offset_y;

        rectangle->tag.tag = GIF_TAG_RECTANGLE;
        rectangle->tag.registers = 0;
        rectangle->tag.fields.register0 = GIF_REGISTER_PRIM;
        rectangle->tag.fields.register1 = GIF_REGISTER_RGBAQ;
        rectangle->tag.fields.register2 = GIF_REGISTER_XYZ2;
        rectangle->tag.fields.register3 = GIF_REGISTER_XYZ2;
        rectangle->tag.fields.register4 = GIF_REGISTER_XYZ2;
        rectangle->tag.fields.register5 = GIF_REGISTER_XYZ2;
        rectangle->prim = (packet->unk15 ? GS_PRIM_ALPHA_BLEND : 0) | GS_PRIM_TRIANGLE_STRIP;
        rectangle->rgba = color;
        offset_x = GS_COORDINATE_CENTRE - g_display->viewport_width / 2;
        offset_y = GS_COORDINATE_CENTRE - g_display->viewport_height / 2;
        rectangle->vertices[0] = resident_gs_xyz(x0 + offset_x, y0 + offset_y, z);
        rectangle->vertices[1] = resident_gs_xyz(x1 + offset_x, y0 + offset_y, z);
        rectangle->vertices[2] = resident_gs_xyz(x0 + offset_x, y1 + offset_y, z);
        rectangle->vertices[3] = resident_gs_xyz(x1 + offset_x, y1 + offset_y, z);
        resident_packet_set_cursor(packet, (u8*)(rectangle + 1));
    }
}

/**
 * @brief Append an antialiased, flat-coloured line when the packet has room.
 * @param packet Packet to append to.
 * @param x0 First end's X, relative to the centre of the viewport.
 * @param y0 First end's Y, relative to the centre of the viewport.
 * @param x1 Second end's X, relative to the centre of the viewport.
 * @param y1 Second end's Y, relative to the centre of the viewport.
 * @param z Depth.
 * @param color RGBA colour.
 */
void resident_packet_add_line(ResidentPacket* packet, s32 x0, s32 y0, s32 x1, s32 y1, s32 z, u32 color)
{
    ResidentLinePacket* line = (ResidentLinePacket*)resident_packet_space(packet, 3);

    if (line != 0)
    {
        s32 offset_x;
        s32 offset_y;

        line->tag.tag = GIF_TAG_LINE;
        line->tag.registers = 0;
        line->tag.fields.register0 = GIF_REGISTER_PRIM;
        line->tag.fields.register1 = GIF_REGISTER_RGBAQ;
        line->tag.fields.register2 = GIF_REGISTER_XYZ2;
        line->tag.fields.register3 = GIF_REGISTER_XYZ2;
        line->prim = (packet->unk15 ? GS_PRIM_ALPHA_BLEND : 0) | GS_PRIM_LINE;
        line->rgba = color;
        offset_x = GS_COORDINATE_CENTRE - g_display->viewport_width / 2;
        offset_y = GS_COORDINATE_CENTRE - g_display->viewport_height / 2;
        line->vertices[0] = resident_gs_xyz(x0 + offset_x, y0 + offset_y, z);
        line->vertices[1] = resident_gs_xyz(x1 + offset_x, y1 + offset_y, z);
        resident_packet_set_cursor(packet, (u8*)(line + 1));
    }
}

/**
 * @brief Queue the packet's pending data on the packet queue without an end tag.
 * @param packet Packet whose data is queued.
 * @param completion Object notified when the transfer finishes, or null.
 */
void resident_packet_queue_pending(ResidentPacket* packet, void* completion)
{
    if (resident_packet_space(packet, 0) != packet->unk0c)
    {
        func_4DC4F0(g_packet_queue, 3, 0, (u32)packet->unk0c & 0x0FFFFFFF, 0, completion);
    }
}

/**
 * @brief End the packet's pending data with a GIF end tag and send it straight to the GS on DMA channel 2.
 * @param packet Packet buffer to send.
 */
void resident_packet_send(ResidentPacket* packet)
{
    u64* cursor = (u64*)resident_packet_space(packet, 1);
    u32 count;

    if (cursor == 0)
    {
        return;
    }

    if ((u8*)cursor == packet->unk0c)
    {
        return;
    }

    *cursor++ = GIF_TAG_END;
    *cursor++ = 0;
    ee_sync();
    count = (u32)((u8*)cursor - packet->unk0c) >> 4;
    sceDmaSendN(sceDmaGetChan(2), (void*)((u32)packet->unk0c & 0x0FFFFFFF), count);
    packet->unk08 = (u8*)cursor;
    packet->unk0c = (u8*)cursor;
}

/**
 * @brief Write a GIF end tag and a VIF FLUSH + MSKPATH3 (unmask) pair after the pending data, without advancing the cursor.
 * @param packet Packet to terminate.
 * @return Quadwords from the pending data's start through the end, or zero when nothing is pending.
 */
u32 resident_packet_end_unmask_path3(ResidentPacket* packet)
{
    u64* cursor = (u64*)resident_packet_space(packet, 2);
    u32 count;

    if (cursor == 0)
    {
        return 0;
    }

    if ((u8*)cursor == packet->unk0c)
    {
        return 0;
    }

    *cursor++ = GIF_TAG_END;
    *cursor++ = 0;
    *cursor++ = 0;
    ((u32*)cursor)[0] = VIF_CODE_FLUSH;
    ((u32*)cursor)[1] = VIF_CODE_MSKPATH3;
    cursor++;
    count = (u32)((u8*)cursor - packet->unk0c) >> 4;
    ee_sync();
    return count;
}

/**
 * @brief Write a GIF end tag after the pending data without advancing the cursor.
 * @param packet Packet to terminate.
 * @return Quadwords from the pending data's start through the end tag, or zero when nothing is pending.
 */
u32 resident_packet_end(ResidentPacket* packet)
{
    u64* end = (u64*)resident_packet_space(packet, 1);

    if (end == 0)
    {
        return 0;
    }

    if ((u8*)end == packet->unk0c)
    {
        return 0;
    }

    end[0] = GIF_TAG_END;
    end[1] = 0;
    return (u32)((u8*)(end + 2) - packet->unk0c) >> 4;
}

/**
 * @brief Return the low 28 bits of the word at receiver offset 0xC.
 * @param object Object containing the word.
 * @return The word with its upper four bits cleared.
 */
u32 resident_packet_get_address(const void* object)
{
    const u32* words = (const u32*)object;
    return words[3] & 0x0FFFFFFF;
}

/**
 * @brief End the packet's pending data with a GIF end tag and send it on DMA channel 2.
 * @param packet Packet buffer to submit.
 * @param notification Object notified when the transfer finishes, or null.
 */
void resident_packet_submit(ResidentPacket* packet, void* notification)
{
    u64* cursor = (u64*)resident_packet_space(packet, 1);
    u32 count;

    if (cursor == 0)
    {
        return;
    }

    if ((u8*)cursor == packet->unk0c)
    {
        return;
    }

    *cursor++ = GIF_TAG_END;
    *cursor++ = 0;
    count = (u32)((u8*)cursor - packet->unk0c) >> 4;
    ee_sync();
    func_4DC4F0(g_packet_queue, 2, 0, (u32)packet->unk0c & 0x0FFFFFFF, count, notification);
    packet->unk08 = (u8*)cursor;
    packet->unk0c = (u8*)cursor;
}

/**
 * @brief Advance the packet cursor to the next 16-byte boundary.
 * @param packet Packet whose cursor is updated.
 * @param cursor Requested cursor.
 * @return The updated packet cursor.
 */
u8* resident_packet_align_cursor(ResidentPacket* packet, u8* cursor)
{
    if (((u32)cursor & 0xF) != 0)
    {
        cursor = (u8*)(((u32)cursor + 0xF) & 0xFFFFFFF0);
    }

    packet->unk08 = cursor;
    return packet->unk08;
}

/**
 * @brief Get the current packet cursor when a requested range fits.
 * @param packet Packet to inspect.
 * @param quadwords Number of 16-byte words required.
 * @return Current cursor, or null when there is insufficient capacity.
 */
u8* resident_packet_reserve(ResidentPacket* packet, s32 quadwords)
{
    return resident_packet_space(packet, quadwords);
}

/**
 * @brief Replace the packet storage with a new allocation for a number of quadwords.
 * @param packet Packet to allocate storage for.
 * @param quadwords Capacity in 16-byte words, not counting the 0x40-byte header the cursor starts after.
 */
void resident_packet_allocate(ResidentPacket* packet, s32 quadwords)
{
    if (!packet->unk14)
    {
        delete packet->unk04;
    }

    s32 words = quadwords * 2;
    packet->unk14 = 0;
    packet->unk04 = new (0) u8[(words + 0x10) * 8];

    if (packet->unk04 == 0)
    {
        packet->unk10 = 0;
        return;
    }

    FlushCache(0);
    packet->unk10 = words;
    packet->unk00 = (u8*)((u32)packet->unk04 | 0x30000000);
    resident_packet_rewind(packet);
}
