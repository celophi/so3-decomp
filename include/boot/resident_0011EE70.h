#ifndef SO3_BOOT_RESIDENT_0011EE70_H
#define SO3_BOOT_RESIDENT_0011EE70_H

#include "types.h"

/** Partial GS packet buffer: base, write cursor, capacity in 64-bit words, and a flag byte at offset 0x15. */
typedef struct ResidentPacket
{
    u8* unk00;
    u8 unk04[4];
    u8* unk08;
    u8 unk0c[4];
    s32 unk10;
    u8 unk14;
    u8 unk15;
} ResidentPacket;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Append a GIF A+D write of one GS register when the packet has room.
 * @param packet Packet to append to.
 * @param reg GS register address.
 * @param data Register value.
 */
void func_0011EF00(ResidentPacket* packet, u32 reg, u64 data);

/**
 * @brief Append a GIF A+D write of GS register 0x00 when the packet has room.
 * @param packet Packet to append to.
 * @param data Register value.
 */
void func_0011EF90(ResidentPacket* packet, u64 data);

/**
 * @brief Append a GIF A+D write of GS register 0x43 when the packet has room.
 * @param packet Packet to append to.
 * @param data Register value.
 */
void func_0011F140(ResidentPacket* packet, u64 data);

/**
 * @brief Read the byte at offset 0x25 of an object.
 * @param object Object to read; the field context passes its object at offset 0x24.
 * @return The byte at offset 0x25.
 */
u8 func_0011F9D0(void* object);

#ifdef __cplusplus
}
#endif

#endif
