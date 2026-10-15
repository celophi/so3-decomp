#include "include_asm.h"
#include "overlays/boot/text_001DD3C0.h"
#include "sdk/main/libc_0013C6D0.h"
#include "sdk/main/libc_0013CA60.h"
#include "vu0.h"

#define BOOT_TRANSFER_BUFFER_SIZE 1158050

typedef struct FieldU16At06A
{
    u8 pad[0x6A];
    u16 value;
} FieldU16At06A;

typedef struct FieldU16At06C
{
    u8 pad[0x6C];
    u16 value;
} FieldU16At06C;

typedef struct FieldU8At018
{
    u8 pad[0x18];
    u8 value;
} FieldU8At018;

typedef struct FieldU8At060
{
    u8 pad[0x60];
    u8 value;
} FieldU8At060;

typedef struct FieldU8At79C
{
    u8 pad[0x79C];
    u8 value;
} FieldU8At79C;

typedef struct FieldU8At570
{
    u8 pad[0x570];
    u8 value;
} FieldU8At570;

typedef struct FieldU8At090
{
    u8 pad[0x90];
    u8 value;
} FieldU8At090;

typedef struct FieldU8At1D0
{
    u8 pad[0x1D0];
    u8 value;
} FieldU8At1D0;

typedef struct FieldU8At1E0
{
    u8 pad[0x1E0];
    u8 value;
} FieldU8At1E0;

typedef struct FieldU8At1F0
{
    u8 pad[0x1F0];
    u8 value;
} FieldU8At1F0;

typedef struct FieldU32At704
{
    u8 pad[0x704];
    u32 value;
} FieldU32At704;

typedef struct FieldU8At794
{
    u8 pad[0x794];
    u8 value;
} FieldU8At794;

typedef struct Record001E94E0
{
    u8 unk00[0x210];
    u8 value;
    u8 unk211[0x38C];
    u8 unk59d:3;
    u8 active:1;
    u8 unk59dhi:4;
} Record001E94E0;

extern u8 D_170D50[];
extern u8 D_50CD30[];
extern void func_4A4550(void* object);
extern void func_4A4510(void* object);
extern void func_4CE4C0(void* destination, const float* source);

static inline void copy_vector(BootVector4DDAA0* destination, const BootVector4DDAA0* source);
static inline void copy_transfer_name(BootState1E1A40* object, const char* base, const char* suffix);
static inline s32 prepare_transfer_request(BootState1E1A40* object);
static inline void set_resource_bit(BootResourceBits0970* bits, u32 index, s32 enabled);

/**
 * @brief Copy all 128 bits of an aligned four-component vector.
 * @param destination Vector receiving the copy.
 * @param source Vector to copy.
 */
static inline void copy_vector(BootVector4DDAA0* destination, const BootVector4DDAA0* source)
{
    *(unsigned __int128*)destination = *(const unsigned __int128*)source;
}

/**
 * @brief Clear the stored filename and copy the optional base and suffix.
 * @param object State containing the filename buffer.
 * @param base Base filename; a null pointer leaves the buffer unchanged.
 * @param suffix Optional suffix to append after the base.
 */
static inline void copy_transfer_name(BootState1E1A40* object, const char* base, const char* suffix)
{
    s32 index;
    if (base != 0)
    {
        for (index = 0; index < BOOT_TRANSFER_NAME_CAPACITY; index++)
        {
            object->unk2E[index] = 0;
        }
        func_13C948(object->unk2E, base);
        if (suffix != 0)
        {
            strcat(object->unk2E, suffix);
        }
    }
}

/**
 * @brief Clear an allocated buffer and populate its transfer request records.
 * @param object State containing the buffer and filename storage.
 * @return 1 when the records are prepared, or 0 when no buffer is allocated.
 */
static inline s32 prepare_transfer_request(BootState1E1A40* object)
{
    u8 ready;
    if (object->unkDC4 == 0)
    {
        ready = 0;
    }
    else
    {
        func_13A678(object->unkDC4, 0, BOOT_TRANSFER_BUFFER_SIZE);
        if (strlen(D_205100) + 1 <= BOOT_TRANSFER_NAME_CAPACITY)
        {
            copy_transfer_name(object, D_205100, D_205980);
        }
        object->unkDD4.unk00 = object->unk2E;
        object->unkDD4.unk04 = object->unkDC4;
        object->unkDD4.unk08 = BOOT_TRANSFER_BUFFER_SIZE;
        object->unkDD4.unk0C = 0;
        object->unkDE4.unk00 = object->unk2E;
        object->unkDE4.unk04 = 1;
        object->unkDE4.unk08 = 0;
        object->unkDE4.unk0C = &object->unkDD4;
        ready = 1;
    }
    return ready;
}

/**
 * @brief Set or clear a selected bit in the resource's flag array.
 * @param bits Resource storage containing the flag array.
 * @param index Unsigned flag index.
 * @param enabled Nonzero to set the bit, or zero to clear it.
 */
static inline void set_resource_bit(BootResourceBits0970* bits, u32 index, s32 enabled)
{
    u32 byte_index = index / 8;
    u32 bit_index = index % 8;
    u8 mask;
    if (enabled)
    {
        mask = 1ULL << bit_index;
        bits->unk08[byte_index] |= mask;
    }
    else
    {
        mask = ~(1ULL << bit_index);
        bits->unk08[byte_index] &= mask;
    }
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001DD3C0", func_001DD3C0);

s32 func_001DD400(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001DD3C0", func_001DD410);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001DD3C0", func_001DD440);

void func_001DD4C0(void* object)
{
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001DD3C0", func_001DD4D0);

void func_001DD620(u8* object, float first, float second, float third)
{
    object[0x50] = 1;
    *(float*)(object + 0x20) = first;
    *(float*)(object + 0x24) = second;
    *(float*)(object + 0x28) = third;
    *(float*)(object + 0x2C) = 1.0f;
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001DD3C0", func_001DD640);

void func_001DDAA0(BootVectorStateDDAA0* object)
{
    vu0_multiply_xyzw(&object->unk580, &object->unk560, &object->unk570);
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001DD3C0", func_001DDAC0);

void func_001DDED0(u8* object, float first, float second, float third)
{
    object[0x50] = 1;
    *(float*)(object + 0x40) = first;
    *(float*)(object + 0x44) = second;
    *(float*)(object + 0x48) = third;
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001DD3C0", func_001DDEF0);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001DD3C0", func_001DFB70);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001DD3C0", func_001DFBD0);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001DD3C0", func_001DFCE0);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001DD3C0", func_001DFD50);

void func_001DFE30(void* object, u16 value)
{
    ((FieldU16At06A*)object)->value = value;
}

void func_001DFE40(void* object, u16 value)
{
    ((FieldU16At06C*)object)->value = value;
}

void* func_001DFE50(u32* object)
{
    object[3] = 0;
    object[2] = 0;
    object[1] = 0;
    object[0] = 0;
    return object;
}

void* func_001DFE70(void** object)
{
    *object = D_170D50;
    return object;
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001DD3C0", func_001DFE90);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001DD3C0", func_001DFF00);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001DD3C0", func_001DFFA0);

void func_001E0250(void* object, u8 value)
{
    ((FieldU8At018*)object)->value = value;
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001DD3C0", func_001E0260);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001DD3C0", func_001E0430);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001DD3C0", func_001E0490);

void func_001E04E0(void* object)
{
}

void func_001E04F0(void* object)
{
}

void func_001E0500(u8* object, const unsigned __int128* value)
{
    *(unsigned __int128*)(object + 0x20) = *value;
}

void func_001E0510(u8* object, const unsigned __int128* value)
{
    *(unsigned __int128*)(object + 0x20) = *value;
}

void func_001E0520(u8* object, float first, float second, float third)
{
    *(float*)(object + 0x20) = first;
    *(float*)(object + 0x24) = second;
    *(float*)(object + 0x28) = third;
    *(float*)(object + 0x2C) = 1.0f;
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001DD3C0", func_001E0540);

s32 func_001E05D0(void* object)
{
    return 3;
}

void func_001E05E0(void* object)
{
}

void func_001E05F0(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x20) = *value;
}

void func_001E0610(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x20) = *value;
}

void func_001E0630(u8* object, float first, float second, float third, float fourth)
{
    object[0x50] = 1;
    *(float*)(object + 0x30) = first;
    *(float*)(object + 0x34) = second;
    *(float*)(object + 0x38) = third;
    *(float*)(object + 0x3C) = fourth;
}

void func_001E0650(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x30) = *value;
}

void func_001E0670(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x30) = *value;
}

