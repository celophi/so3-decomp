#ifndef SO3_MAIN_RESIDENT_0011EE70_H
#define SO3_MAIN_RESIDENT_0011EE70_H

#include "types.h"

struct LibClass171FF0;

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

#ifdef __cplusplus
extern "C" {
void func_00121730(u8* object, float x, float y, float z);
#endif

/** Mark the transform as changed and copy a four-float value into it. */
void func_001216D0(u8* object, const float* input);
/** Mark the transform as changed and copy a four-float value into it. */
void func_00121700(u8* object, const float* input);

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
 * @brief Finish pending packet data and submit it with a DMA notification receiver.
 * @param packet Packet buffer to submit.
 * @param notification Secondary interface notified after submission.
 */
void func_0011F770(ResidentPacket* packet, struct LibClass171FF0* notification);

/**
 * @brief Advance the packet cursor to the next 16-byte boundary at or after a supplied cursor.
 * @param packet Packet to update.
 * @param cursor Requested cursor.
 * @return Rounded cursor.
 */
u8* func_0011F830(ResidentPacket* packet, u8* cursor);

/**
 * @brief Get the current packet cursor when a requested range fits.
 * @param packet Packet to inspect.
 * @param quadwords Number of 16-byte words required.
 * @return Current cursor, or null when there is insufficient capacity.
 */
u8* func_0011F860(ResidentPacket* packet, s32 quadwords);

/**
 * @brief Read the byte at offset 0x25 of an object.
 * @param object Object to read; the field context passes its object at offset 0x24.
 * @return The byte at offset 0x25.
 */
u8 func_0011F9D0(void* object);

/** Clear the byte at receiver offset 0x60. */
void func_001215C0(void* object);

/** Return the address of the shared global at 0x50CD30. */
const void* func_00121610(void);

/** Return the word at receiver offset 0x14. */
u32 func_001205A0(const void* object);
/** Return the word at receiver offset 0x10. */
u32 func_001205E0(const void* object);
/** Return the word at receiver offset 0xC. */
u32 func_00120630(const void* object);
/** Return the word at receiver offset 0x8. */
u32 func_00120670(const void* object);
/** Return the word at receiver offset 0x4. */
u32 func_001206B0(const void* object);
/** Return the word at receiver offset 0x0. */
u32 func_001206F0(const void* object);

/** Clamp the value to [0, 100], store it at offset 0x10, and return it. */
s32 func_001205B0(void* object, s32 value);

/** Clamp the value to [0, 255], store it at offset 0x8, and return it. */
s32 func_00120640(void* object, s32 value);

/** Clamp the value to [0, 999], store it at offset 0x4, and return it. */
s32 func_00120680(void* object, s32 value);

/** Clamp the value to [0, 9999], store it at offset 0, and return it. */
s32 func_001206C0(void* object, s32 value);


/** Store the word at receiver offset 0x70. */
void func_001207B0(void* object, u32 value);

/** Return the fixed integer value 9. */
s32 func_001207D0(void* object);

/** Return the fixed integer value -1. */
s32 func_00121860(void* object);

/** Return the fixed value 0. */
s32 func_00121570(void* object);

/** Return the fixed value 0. */
s32 func_001215E0(void* object);

/** Test whether a floating-point value is negative. */
s32 func_001215F0(float value);

/** Return the fixed value 0. */
s32 func_00121630(void* object);

/** Return the fixed value 0. */
s32 func_001217D0(void* object);

void func_001207C0(void* object);
void func_001215D0(void* object);
void func_00121620(void* object);
void func_00121640(void* object);
void func_00121870(void* object);
void func_00121880(void* object);
void func_00121890(void* object);

/** Return the receiver address at byte offset 0x90. */
void* func_00121580(void* object);

/** Return the receiver address at byte offset 0x1D0. */
void* func_00121590(void* object);

/** Return the receiver address at byte offset 0x1E0. */
void* func_001215A0(void* object);

/** Return the receiver address at byte offset 0x1F0. */
void* func_001215B0(void* object);

/** Set the ready flag and copy a 128-bit value into the receiver. */
void func_00120EB0(void* object, const unsigned __int128* value);

/** Set the ready flag and copy a 128-bit value into the receiver. */
void func_00120ED0(void* object, const unsigned __int128* value);

/** Set the ready flag and copy a 128-bit value into the receiver. */
void func_00121650(void* object, const unsigned __int128* value);

/** Set the ready flag and copy a 128-bit value into the receiver. */
void func_001216B0(void* object, const unsigned __int128* value);

/** Set the ready flag and copy a 128-bit value into the receiver. */
void func_00121770(void* object, const unsigned __int128* value);

/** Set the ready flag and copy a 128-bit value into the receiver. */
void func_00121790(void* object, const unsigned __int128* value);


#ifdef __cplusplus
/** Set the receiver flag and store four float values. */
void func_00121690(void* object, float x, float y, float z, float w);

/** Set a receiver flag and store three float values. */
void func_001217B0(void* object, float x, float y, float z);

}
#endif

#endif
