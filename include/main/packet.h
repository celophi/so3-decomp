#ifndef SO3_MAIN_PACKET_H
#define SO3_MAIN_PACKET_H

#include "types.h"
#include "gs.h"
#include "ee.h"
#include "sdk/main/libkernl_00121940.h"

/**
 * Partial GS packet buffer: base, allocated storage, write cursor, capacity in 64-bit words, a
 * borrowed-storage flag at offset 0x14 and a flag byte at offset 0x15.
 */
typedef struct ResidentPacket
{
    u8* unk00;
    u8* unk04;
    u8* unk08;
    u8* unk0c;
    s32 unk10;
    u8 unk14;
    u8 unk15;
} ResidentPacket;

#define RESIDENT_PACKET_HEADER_SIZE 0x40

/**
 * @brief Empty a packet: move its write cursor and start back to just after the header.
 * @param packet Packet to empty.
 */
static inline void resident_packet_rewind(ResidentPacket* packet)
{
    packet->unk08 = packet->unk00 + RESIDENT_PACKET_HEADER_SIZE;
    packet->unk0c = packet->unk08;
}

#ifdef __cplusplus
/** Main's GS packet buffer class (vtable D_0014FDF0); its data comes before the vptr. Boot and Field have their own. */
class ResidentPacketBuffer : public ResidentPacket
{
public:
    /** @brief Free the packet storage unless it is borrowed. */
    virtual ~ResidentPacketBuffer();
};
#endif

/** One GS register write in A+D (address plus data) form. */
typedef struct ResidentGsRegisterWrite
{
    GsGifTag tag;
    u64 data;
    u64 address;
} ResidentGsRegisterWrite;

/** Packed GIF tag, PRIM, colour and two XYZ2 vertices drawing one line. */
typedef struct ResidentLinePacket
{
    GsGifTag tag;
    u64 prim;
    u32 rgba;
    u32 q;
    u64 vertices[2];
} ResidentLinePacket;

/** Packed GIF tag, PRIM, colour and four XYZ2 vertices drawing one filled rectangle as a triangle strip. */
typedef struct ResidentRectanglePacket
{
    GsGifTag tag;
    u64 prim;
    u32 rgba;
    u32 q;
    u64 vertices[4];
} ResidentRectanglePacket;

/** Display context holding the signed viewport size; the packet builders centre vertices on the GS drawing area. */
typedef struct ResidentDisplayContext
{
    u8 unk00[0x3C6C];
    s16 viewport_width;
    s16 viewport_height;
} ResidentDisplayContext;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Append a GIF A+D write of one GS register when the packet has room.
 * @param packet Packet to append to.
 * @param address GS register address.
 * @param data Register value.
 */
void resident_packet_add_register(ResidentPacket* packet, u64 address, u64 data);

/**
 * @brief Append a GIF A+D write of the GS PRIM register when the packet has room.
 * @param packet Packet to append to.
 * @param data Register value.
 */
void resident_packet_set_prim(ResidentPacket* packet, u64 data);

/**
 * @brief Append a GIF A+D write of the GS ALPHA_2 register when the packet has room.
 * @param packet Packet to append to.
 * @param data Register value.
 */
void resident_packet_set_alpha_2(ResidentPacket* packet, u64 data);

/**
 * @brief End the packet's pending data with a GIF end tag and send it on DMA channel 2.
 * @param packet Packet buffer to submit.
 * @param notification Object notified when the transfer finishes, or null.
 */
void resident_packet_submit(ResidentPacket* packet, void* notification);

/**
 * @brief Advance the packet cursor to the next 16-byte boundary at or after a supplied cursor.
 * @param packet Packet to update.
 * @param cursor Requested cursor.
 * @return Rounded cursor.
 */
u8* resident_packet_align_cursor(ResidentPacket* packet, u8* cursor);

/**
 * @brief Get the current packet cursor when a requested range fits.
 * @param packet Packet to inspect.
 * @param quadwords Number of 16-byte words required.
 * @return Current cursor, or null when there is insufficient capacity.
 */
u8* resident_packet_reserve(ResidentPacket* packet, s32 quadwords);

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
void resident_packet_add_line(ResidentPacket* packet, s32 x0, s32 y0, s32 x1, s32 y1, s32 z, u32 color);

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
void resident_packet_add_rectangle(ResidentPacket* packet, s32 x0, s32 y0, s32 x1, s32 y1, s32 z, u32 color);

/**
 * @brief Append a GIF A+D write of the GS TEX0_2 register when the packet has room.
 * @param packet Packet to append to.
 * @param data Register value.
 */
void resident_packet_set_tex0_2(ResidentPacket* packet, u64 data);

/**
 * @brief Append a GIF A+D write of the GS ALPHA_1 register when the packet has room.
 * @param packet Packet to append to.
 * @param data Register value.
 */
void resident_packet_set_alpha_1(ResidentPacket* packet, u64 data);

/**
 * @brief Queue the packet's pending data on the packet queue without an end tag.
 * @param packet Packet whose data is queued.
 * @param completion Object notified when the transfer finishes, or null.
 */
void resident_packet_queue_pending(ResidentPacket* packet, void* completion);

/**
 * @brief End the packet's pending data with a GIF end tag and send it straight to the GS on DMA channel 2.
 * @param packet Packet buffer to send.
 */
void resident_packet_send(ResidentPacket* packet);

/**
 * @brief Write a GIF end tag and a VIF FLUSH + MSKPATH3 (unmask) pair after the pending data, without advancing the cursor.
 * @param packet Packet to terminate.
 * @return Quadwords from the pending data's start through the end, or zero when nothing is pending.
 */
u32 resident_packet_end_unmask_path3(ResidentPacket* packet);

/**
 * @brief Write a GIF end tag after the pending data without advancing the cursor.
 * @param packet Packet to terminate.
 * @return Quadwords from the pending data's start through the end tag, or zero when nothing is pending.
 */
u32 resident_packet_end(ResidentPacket* packet);

/**
 * @brief Replace the packet storage with a new allocation for a number of quadwords.
 * @param packet Packet to allocate storage for.
 * @param quadwords Capacity in 16-byte words, not counting the 0x40-byte header the cursor starts after.
 */
void resident_packet_allocate(ResidentPacket* packet, s32 quadwords);

/**
 * @brief Get the hardware address of the packet's pending data.
 * @param packet Packet to inspect.
 * @return The start of the pending data with its upper four address bits cleared.
 */
u32 resident_packet_get_address(const void* packet);

#ifdef __cplusplus
}
#endif

#endif
