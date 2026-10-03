#include "include_asm.h"
#include "overlays/0002-00/text_001DD3C0.h"
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
            func_13C6D0(object->unk2E, suffix);
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
        if (func_13CA60(D_205100) + 1 <= BOOT_TRANSFER_NAME_CAPACITY)
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

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DD3C0);

s32 func_001DD400(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DD410);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DD440);

void func_001DD4C0(void* object)
{
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DD4D0);

void func_001DD620(u8* object, float first, float second, float third)
{
    object[0x50] = 1;
    *(float*)(object + 0x20) = first;
    *(float*)(object + 0x24) = second;
    *(float*)(object + 0x28) = third;
    *(float*)(object + 0x2C) = 1.0f;
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DD640);

void func_001DDAA0(BootVectorStateDDAA0* object)
{
    vu0_multiply_xyzw(&object->unk580, &object->unk560, &object->unk570);
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DDAC0);

void func_001DDED0(u8* object, float first, float second, float third)
{
    object[0x50] = 1;
    *(float*)(object + 0x40) = first;
    *(float*)(object + 0x44) = second;
    *(float*)(object + 0x48) = third;
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DDEF0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DFB70);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DFBD0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DFCE0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DFD50);

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

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DFE90);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DFF00);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001DFFA0);

void func_001E0250(void* object, u8 value)
{
    ((FieldU8At018*)object)->value = value;
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E0260);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E0430);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E0490);

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

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E0540);

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

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E0690);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E06C0);

void func_001E06F0(u8* object, float first, float second, float third)
{
    float vector[4];
    object[0x50] = 1;
    vector[0] = first;
    vector[1] = second;
    vector[2] = third;
    vector[3] = 1.0f;
    func_4CE4C0(object + 0x30, vector);
}

void func_001E0730(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x40) = *value;
}

void func_001E0750(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x40) = *value;
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E0770);

void func_001E0860(void* object)
{
    ((FieldU8At060*)object)->value = 0;
}

void func_001E0870(void* object)
{
}

s32 func_001E0880(void* object)
{
    return 0;
}

s32 func_001E0890(void* object, float value)
{
    return value < 0.0f;
}

void* func_001E08B0(void* object)
{
    return D_50CD30;
}

void func_001E08C0(void* object)
{
}

s32 func_001E08D0(void* object)
{
    return 0;
}

void func_001E08E0(void* object)
{
}

void func_001E08F0(void* object)
{
}

s32 func_001E0900(void* object)
{
    return 2;
}

u16 func_001E0910(BootState1E1A40* object)
{
    BootModeOwner0910* owner = object->unk14;
    BootModePair0910* modes;
    u16 flags;

    if (owner->unk20 == 0)
    {
        return 0;
    }

    modes = owner->unk14;
    flags = 0;
    if (modes->unk48 == 2)
    {
        flags |= BOOT_MODE_0910_FLAG_0;
    }
    if (modes->unk148 == 2)
    {
        flags |= BOOT_MODE_0910_FLAG_1;
    }
    return flags;
}

void func_001E0970(BootState1E1A40* object)
{
    u8 saved_bits[BOOT_TRANSFER_FLAG_BYTES];
    s32 index;
    u8* saved;
    BootResourceBits0970* bits;
    if (object->unkDC4 != 0)
    {
        saved = (u8*)object->unkDC4 + 0x4B4;
        bits = &object->unkDF4->unk1A8;
        func_13A678(saved_bits, 0, BOOT_TRANSFER_FLAG_BYTES);
        func_13A4C0(saved_bits, saved, BOOT_TRANSFER_FLAG_BYTES);
        for (index = 0; index < BOOT_TRANSFER_FLAG_COUNT; index++)
        {
            set_resource_bit(bits, index, saved_bits[index / 8] & (1 << (index % 8)));
        }
        bits->unk14 = *(u32*)object->unkDC4;
        func_13A4C0(bits->unk18, saved + BOOT_TRANSFER_FLAG_BYTES, 8);
        func_13A4C0(object->unkDC8, (u8*)object->unkDC4 + 0x4E2, 0x11A6C0);
        if (object->unkDC4 != 0)
        {
            func_100BE0(object->unkDC4);
            object->unkDC4 = 0;
        }
    }
}

s32 func_001E0AD0(BootState1E1A40* object)
{
    return object->unkDD0;
}

s16 func_001E0AE0(BootState1E1A40* object)
{
    return object->unkDCE;
}

s16 func_001E0AF0(BootState1E1A40* object)
{
    s16 result = -1;
    switch (object->unkDC0)
    {
    case 0:
        object->unkDF9 = 1;
        result = func_432310(object->unk14, object->unkDCC, &object->unkDE4);
        if (result == -1)
        {
            object->unkDF8 = 0;
            object->unkDCE = 1;
            object->unk1C = 0;
            object->unkDCC = -1;
            object->unkDC0 = -1;
        }
        else if (result == 0)
        {
            object->unkDC0++;
        }
        break;
    case 1:
        result = func_432270(object->unk14, object->unkDCC, &object->unkDD0);
        if (result == 0)
        {
            break;
        }
        if (result == 1)
        {
            object->unkDF8 = 0;
            if (object->unkDD0 >= 0)
            {
                func_001E0970(object);
                object->unkDCE = 1;
                object->unk1C = 0;
                object->unkDCC = -1;
                object->unkDC0 = -1;
            }
            else
            {
                object->unkDCE = 1;
                object->unkDCC = -1;
                object->unkDC0 = -1;
                object->unk1C = 1;
                object->unkDF8 = 0;
                if (object->unkDF9 == 1)
                {
                    object->unkDF9 = 0;
                }
            }
        }
        break;
    }
    return result;
}

s32 func_001E0C30(BootState1E1A40* object, u16 mode, void* destination)
{
    u8 ready;
    if (mode != 0 && mode != 1)
    {
        return 0;
    }
    if (destination == 0)
    {
        return 0;
    }
    object->unkDC8 = destination;
    object->unkDCC = mode;
    object->unkDD0 = -1;
    object->unkDC0 = 0;
    object->unkDF8 = 1;
    object->unk18 = object->unkDCC;
    object->unk1E = 0;
    if (object->unkDC4 == 0)
    {
        object->unkDC4 = func_100B00(BOOT_TRANSFER_BUFFER_SIZE, 0);
    }
    ready = prepare_transfer_request(object);
    if (!ready)
    {
        return 0;
    }
    object->unkDF9 = 0;
    return 1;
}

void func_001E0DE0(BootState1E1A40* object, u8 mode)
{
    if (mode == 1 || mode == 2)
    {
        object->unkD34 = mode;
        func_001E1A40(object, 0);
    }
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E0E20);

/**
 * @brief Return a mode's stored byte, or zero for an unsupported mode.
 * @param object State holding the mode values.
 * @param mode Mode 0 or 1 to query.
 * @return The stored byte, or zero when the mode is unsupported.
 */
static inline u8 state_mode_value(BootState1E1A40* object, u16 mode)
{
    if (mode != 0 && mode != 1)
    {
        return 0;
    }
    return object->unkD37[mode];
}

u16 func_001E1410(BootState1E1A40* object, u16 mode, u16 kind)
{
    u16 value = 0;
    if (mode != 0 && mode != 1)
    {
        return 0;
    }
    if (kind == 1)
    {
        if (mode == 0)
        {
            if (!object->unk29)
            {
                value = 0;
            }
            else
            {
                value = object->unk2B;
            }
        }
        else if (mode == 1)
        {
            if (!object->unk2A)
            {
                value = 0;
            }
            else
            {
                value = object->unk2C;
            }
        }
    }
    else
    {
        value = state_mode_value(object, mode);
    }
    if (object->unk28)
    {
        func_001E1A40(object, 0);
    }
    return value;
}

void func_001E1500(BootState1E1A40* object, u8 enabled, u16 event, u16 kind)
{
    u8 ready;
    if (enabled == 1)
    {
        if (object->unk18 == 1)
        {
            if (kind == 1)
            {
                func_001E17C0(object, event, &object->unk2C);
                if (object->unkD34 != 1)
                {
                    object->unk2A = 1;
                }
                if (object->unkD34 == 1)
                {
                    ready = 0;
                    switch (event)
                    {
                    case 16:
                        if (object->unk20 == 0)
                        {
                            object->unk2A = 1;
                            ready = 1;
                        }
                        break;
                    case 15:
                    case 5:
                    case 6:
                        object->unk2A = 1;
                        ready = 1;
                        break;
                    }
                    if (ready)
                    {
                        object->unk28 = 1;
                    }
                }
                else if (object->unkD34 == 2)
                {
                    switch (event)
                    {
                    case 15:
                        object->unkD37[1] = 15;
                        object->unkD35[1] = 1;
                        object->unk28 = 1;
                        break;
                    }
                }
            }
            else if (kind == 2)
            {
                object->unkD37[1] = event;
                object->unkD35[1] = 1;
                object->unk28 = 1;
            }
        }
        if (object->unk18 == 0)
        {
            if (kind == 1)
            {
                func_001E17C0(object, event, &object->unk2B);
                if (object->unkD34 == 1)
                {
                    ready = 0;
                    switch (event)
                    {
                    case 16:
                        if (object->unk20 == 0)
                        {
                            object->unk29 = 1;
                            ready = 1;
                        }
                        break;
                    case 15:
                    case 5:
                    case 6:
                        object->unk29 = 1;
                        ready = 1;
                        break;
                    }
                    if (ready == 1)
                    {
                        func_001E1A40(object, 1);
                    }
                }
                else
                {
                    switch (event)
                    {
                    case 15:
                        if (object->unkD34 == 2)
                        {
                            object->unkD37[0] = 15;
                            object->unkD35[0] = 1;
                            func_001E1A40(object, 1);
                        }
                        /* fall through */
                    case 2:
                    case 16:
                    case 17:
                        object->unk29 = 1;
                        break;
                    }
                    if (object->unkD34 == 1)
                    {
                        func_001E1A40(object, 1);
                    }
                }
            }
            else if (kind == 2)
            {
                object->unkD37[0] = event;
                object->unkD35[0] = 1;
                func_001E1A40(object, 1);
            }
        }
    }
    if (object->unk28 == 0)
    {
        object->unk1E = 0;
    }
    else
    {
        object->unk1E = enabled;
    }
}

void func_001E17C0(BootState1E1A40* object, u16 event, u8* result)
{
    s32 value;
    *result = 0;
    if (object->unkD34 == 1)
    {
        value = object->unkDFC[object->unk18];
        switch (event)
        {
        case 15:
            *result = 15;
            break;
        case 2:
            object->unkE04[object->unk18] = 10;
            break;
        case 16:
            if (object->unk20 == 0)
            {
                *result = 16;
            }
            else
            {
                object->unkE04[object->unk18] = 16;
            }
            break;
        case 17:
            object->unkE04[object->unk18] = 17;
            break;
        case 6:
            if (object->unkE04[object->unk18] == 17)
            {
                if (value < 0 || value > 8000)
                {
                    *result = 15;
                }
                *result = 17;
                if (0 <= value && value < 1200)
                {
                    *result = 13;
                }
            }
            else
            {
                if (value < 0 || value > 8000)
                {
                    *result = 15;
                }
                *result = object->unkE04[object->unk18];
                if (0 <= value && value < 1375)
                {
                    *result = 12;
                }
                if (0 <= value && value < 175)
                {
                    *result = 10;
                }
                else if (value >= 175 && value < 1200)
                {
                    *result = 11;
                }
                else if (value >= 1200 && value < 1375)
                {
                    *result = 12;
                }
            }
            break;
        case 5:
            if (object->unkE04[object->unk18] == 17)
            {
                *result = 17;
            }
            else
            {
                if (value < 0 || value > 8000)
                {
                    *result = 15;
                }
                *result = object->unkE04[object->unk18];
                if (0 <= value && value < 175)
                {
                    *result = 14;
                }
            }
            break;
        }
    }
    else
    {
        switch (event)
        {
        case 15:
            *result = 15;
            break;
        case 2:
            *result = 2;
            break;
        case 16:
            *result = 16;
            break;
        case 17:
            *result = 17;
            break;
        }
    }
}

void func_001E1A40(BootState1E1A40* object, s16 mode)
{
    s32 selected = mode;
    object->unk18 = mode;
    object->unk1A = -1;
    object->unk1E = 0;
    object->unk1C = 0;
    object->unk2D = 0;
    if (selected == 0)
    {
        object->unk29 = 0;
        object->unk2B = 0;
        object->unk28 = 0;
        object->unk1E = 0;
        object->unkD37[0] = 0;
        object->unkD35[0] = 0;
    }
    if (selected == 1)
    {
        object->unk2A = 0;
        object->unk2C = 0;
        object->unkD37[1] = 0;
        object->unkD35[1] = 0;
    }
    if (selected == 0 || selected == 1)
    {
        object->unkDFC[selected] = -1;
        object->unkE04[selected] = -1;
    }
}

s32 func_001E1AD0(BootState1E1A40* object)
{
    BootModeOwner0910* owner;
    u8 ready;

    owner = func_100AC0(0x58, 0);
    if (owner != 0)
    {
        owner = func_432900(owner);
    }
    object->unk14 = owner;
    if (object->unk14 == 0)
    {
        return 0;
    }
    func_432720(object->unk14, D_001B6614);
    func_432660(object->unk14, 0, 0, 0);
    func_432660(object->unk14, 1, 1, 0);
    object->unk1C = 0;
    func_001E1A40(object, 0);
    object->unkDF4 = func_101440(func_101290(func_10D8E0()), 1);
    if (object->unkDF4 == 0)
    {
        return 0;
    }
    if (object->unkDC4 == 0)
    {
        object->unkDC4 = func_100B00(BOOT_TRANSFER_BUFFER_SIZE, 0);
    }
    ready = prepare_transfer_request(object);
    if (!ready)
    {
        return 0;
    }
    return 1;
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E1CD0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E1D40);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E1DD0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E1F50);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E1FE0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E3F80);

s32 func_001E3FE0(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E3FF0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E4610);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E4760);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E4B50);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E4CE0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E5090);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E5250);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E5510);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E63B0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E6C60);

/**
 * @brief Detach the gated attached object, then perform the receiver cleanup.
 * @param object Receiver containing the cleanup gate and attached object.
 */
void func_001E8D80(BootCleanupState8D80* object)
{
    if (object->unk5A0 != 0 && object->unk634 != 0)
    {
        func_4D5C90(object->unk634);
    }
    func_448250(object);
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E8DD0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E9070);

/**
 * @brief Negate the second stored matrix vector, then update the receiver.
 * @param object Receiver containing the matrix and update flag.
 * @param first First opaque argument forwarded to the shared update routine.
 * @param second Second opaque argument forwarded to the shared update routine.
 */
void func_001E92D0(BootCleanupState8D80* object, void* first, void* second)
{
    BootMatrix92D0 matrix;
    BootVector4DDAA0* vector1 = &matrix.vectors[1];
    BootVector4DDAA0* vector2 = &matrix.vectors[2];
    BootVector4DDAA0* vector3 = &matrix.vectors[3];
    copy_vector(&matrix.vectors[0], &object->unk90.vectors[0]);
    copy_vector(vector1, &object->unk90.vectors[1]);
    copy_vector(vector2, &object->unk90.vectors[2]);
    copy_vector(vector3, &object->unk90.vectors[3]);
    vector1->x *= -1.0f;
    vector1->y *= -1.0f;
    vector1->z *= -1.0f;
    vector1->w *= -1.0f;
    copy_vector(&object->unk90.vectors[0], &matrix.vectors[0]);
    copy_vector(&object->unk90.vectors[1], vector1);
    copy_vector(&object->unk90.vectors[2], vector2);
    copy_vector(&object->unk90.vectors[3], vector3);
    object->unk50 = 1;
    func_4A5E60(object, first, second);
}

float func_001E9380(void* object)
{
    return 0.0f;
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E9390);

s32 func_001E9400(void* object)
{
    return 0;
}

s32 func_001E9410(void* object)
{
    return 0;
}

s32 func_001E9420(void* object, s32 value)
{
    return value;
}

s32 func_001E9430(void* object, s32 value)
{
    return value;
}

s32 func_001E9440(void* object)
{
    return 0;
}

s32 func_001E9450(void* object)
{
    return 0;
}

s32 func_001E9460(void* object)
{
    return ((FieldU32At704*)object)->value != 0;
}

u8* func_001E9470(void* object)
{
    return &((FieldU8At79C*)object)->value;
}

u8 func_001E9480(void* object)
{
    return ((FieldU8At794*)object)->value;
}

s32 func_001E9490(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E94A0);

u8* func_001E94D0(void* object)
{
    return &((FieldU8At570*)object)->value;
}

void func_001E94E0(Record001E94E0* object, u8 value)
{
    object->value = value;
    object->active = 1;
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E9500);

u8* func_001E9550(void* object)
{
    return &((FieldU8At090*)object)->value;
}

u8* func_001E9560(void* object)
{
    return &((FieldU8At1D0*)object)->value;
}

u8* func_001E9570(void* object)
{
    return &((FieldU8At1E0*)object)->value;
}

u8* func_001E9580(void* object)
{
    return &((FieldU8At1F0*)object)->value;
}

void func_001E9590(u8* object)
{
    func_4A4550(object - 0x640);
}

void func_001E95A0(u8* object)
{
    func_4A4510(object - 0x640);
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E95B0);

s32 func_001E9640(void* object)
{
    return 0;
}

void func_001E9650(u32* object)
{
    object[8] = 0;
    object[9] = 0;
    object[10] = 0;
    object[11] = 0;
    object[12] = 0;
    object[13] = 0;
}

void func_001E9670(BootInputStatus9670* object)
{
    BootState1E1A40* state;
    u16 first;
    u16 second;
    u16 third;
    u16 fourth;
    u16 flags;
    object->unk16 = func_11E010(D_001B65F0, 0);
    object->unk18 = func_11DFF0(D_001B65F0, 0);
    object->unk1A = func_11E000(D_001B65F0, 0);
    object->unk1C = func_11DFB0(D_001B65F0, 0);
    func_11DF90(D_001B65F0, 0);
    state = D_205E10.unk24;
    if (object->unk14 != 0)
    {
        first = func_001E1410(state, 0, 1);
        second = func_001E1410(state, 1, 1);
        third = func_001E1410(state, 0, 2);
        fourth = func_001E1410(state, 1, 2);
        flags = func_001E0910(state);
        if (first != 0)
        {
            object->unk20 = first;
        }
        if (second != 0)
        {
            object->unk24 = second;
        }
        if (third != 0)
        {
            object->unk28 = third;
        }
        if (fourth != 0)
        {
            object->unk2C = fourth;
        }
        if (flags & 1)
        {
            object->unk30 = 1;
        }
        else
        {
            object->unk30 = 0;
        }
        if (flags & 2)
        {
            object->unk34 = 1;
        }
        else
        {
            object->unk34 = 0;
        }
    }
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E97F0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001E9860);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EA350);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EA480);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EA6A0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EA920);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EA9B0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EAA40);

/**
 * @brief Copy the owner's stored pointer into the resident context.
 * @param object Owner containing the pointer to bind.
 */
void func_001EACC0(BootPointerOwnerACC0* object)
{
    D_001B6628->unk90 = object->unk08;
}

/**
 * @brief Update projection parameters using the resource mode and stored dimensions.
 * @param object Owner containing the projection object to update.
 */
void func_001EACD0(BootPointerOwnerACC0* object)
{
    BootResource0970* resource = func_101440(func_101290(func_10D8E0()), 1);
    BootDimensionsACD0* dimensions;
    if (resource->unk18C != 0)
    {
        dimensions = D_205E10.unk04;
        object->unk08->unk278 =
            (1.7777778f * ((1.3333334f * (1.0714285f * (float)dimensions->unk3C6E)) /
                (float)dimensions->unk3C6C)) / 1.3333334f;
        object->unk08->unk250 = 0.75f;
        dimensions = D_205E10.unk04;
        D_001B6654->unk278 =
            (1.7777778f * ((1.3333334f * (1.0714285f * (float)dimensions->unk3C6E)) /
                (float)dimensions->unk3C6C)) / 1.3333334f;
        D_001B6654->unk25C = 1.8325958f;
    }
    else
    {
        dimensions = D_205E10.unk04;
        object->unk08->unk278 =
            (1.3333334f * (1.0714285f * (float)dimensions->unk3C6E)) /
                (float)dimensions->unk3C6C;
        object->unk08->unk250 = 1.0f;
        dimensions = D_205E10.unk04;
        D_001B6654->unk278 =
            (1.3333334f * (1.0714285f * (float)dimensions->unk3C6E)) /
                (float)dimensions->unk3C6C;
        D_001B6654->unk25C = 1.5707964f;
    }
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EAE80);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EB0E0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EB210);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EB350);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EBCF0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EBEA0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EBF80);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EC010);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EC2E0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EC360);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EC3C0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EC430);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EC490);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EC630);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EC910);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EC990);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001EC9F0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001ECA60);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001ECAC0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001ECC60);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001ECF30);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001ECFA0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001ED000);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001ED060);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001DD3C0", func_001ED200);
