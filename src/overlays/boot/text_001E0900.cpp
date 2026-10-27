#include "include_asm.h"
#include "overlays/boot/text_001E0900.h"
#include "main/resident_001001E0.h"
#include "main/resident_0010A0E0.h"
#include "main/resident_00101550.h"
#include "sdk/main/libc_0013C6D0.h"
#include "sdk/main/libc_0013CA60.h"
#include "vu0.h"

extern "C" {
extern BootClass170F20* D_001B65AC;
u16 func_457470(u16 seed, const void* data, s32 size);
void func_10DA70(BootSound1B65F8* sound, s32 mode);
void func_11E030(BootInputRoot9670* root, s32 slot, s32 enabled);
s32 func_4656B0(BootRuntime1B657C* runtime, void* data);
void func_11E210(BootInputRoot9670* root, s32 first, s32 second, s32 third);
extern void* D_001B65F4;
void func_11ED90(void* queue, void* object);
}

static inline void copy_transfer_name(BootClass170EB0* object, const char* base, const char* suffix);
static inline s32 prepare_transfer_request(BootClass170EB0* object);
static inline void set_resource_bit(BootResourceBits0970* bits, u32 index, s32 enabled);


/**
 * @brief Clear the stored filename and copy the optional base and suffix.
 * @param object State containing the filename buffer.
 * @param base Base filename; a null pointer leaves the buffer unchanged.
 * @param suffix Optional suffix to append after the base.
 */
static inline void copy_transfer_name(BootClass170EB0* object, const char* base, const char* suffix)
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
static inline s32 prepare_transfer_request(BootClass170EB0* object)
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
 * @brief Read settings byte 0x28 when the protected bytes pass the checksum.
 * @param settings System settings.
 * @return Stored byte, or zero when the checksum fails.
 */
static inline u8 settings_value(BootResource0970* settings)
{
    if (settings->checksum != func_457470(settings->key, &settings->unk26, (u8*)&settings->checksum - &settings->unk26))
    {
        return 0;
    }
    return settings->unk28;
}

/**
 * @brief Store settings byte 0x28 and regenerate the key and checksum when the stored checksum is valid.
 * @param settings System settings.
 * @param value Byte to store.
 */
static inline void settings_set_value(BootResource0970* settings, u8 value)
{
    s32 length = (u8*)&settings->checksum - &settings->unk26;
    if (settings->checksum == func_457470(settings->key, &settings->unk26, length))
    {
        settings->unk28 = value;
        settings->key = resident_next_random_word();
        settings->checksum = func_457470(settings->key, &settings->unk26, length);
    }
}

/**
 * @brief Read settings byte 0x1A1 when the extra protected bytes pass their checksum.
 * @param settings System settings.
 * @return Stored byte, or zero when the checksum fails.
 */
static inline u8 settings_extra_1a1(BootResource0970* settings)
{
    u8* data = &settings->unk1A0;
    if (settings->extra_checksum != func_457470(settings->extra_key, data, (u8*)&settings->extra_checksum - data))
    {
        return 0;
    }
    return settings->unk1A1;
}

/**
 * @brief Read settings byte 0x1A2 when the extra protected bytes pass their checksum.
 * @param settings System settings.
 * @return Stored byte, or zero when the checksum fails.
 */
static inline u8 settings_extra_1a2(BootResource0970* settings)
{
    u8* data = &settings->unk1A0;
    if (settings->extra_checksum != func_457470(settings->extra_key, data, (u8*)&settings->extra_checksum - data))
    {
        return 0;
    }
    return settings->unk1A2;
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



s32 BootClass170EB0::get_default_list_kind()
{
    return 2;
}

u16 BootClass170EB0::func_001E0910()
{
    BootModeOwner0910* owner = unk14;
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

void BootClass170EB0::func_001E0970()
{
    u8 saved_bits[BOOT_TRANSFER_FLAG_BYTES];
    s32 index;
    u8* saved;
    BootResourceBits0970* bits;
    if (unkDC4 != 0)
    {
        saved = (u8*)unkDC4 + 0x4B4;
        bits = &unkDF4->unk1A8;
        func_13A678(saved_bits, 0, BOOT_TRANSFER_FLAG_BYTES);
        func_13A4C0(saved_bits, saved, BOOT_TRANSFER_FLAG_BYTES);
        for (index = 0; index < BOOT_TRANSFER_FLAG_COUNT; index++)
        {
            set_resource_bit(bits, index, saved_bits[index / 8] & (1 << (index % 8)));
        }
        bits->unk14 = *(u32*)unkDC4;
        func_13A4C0(bits->unk18, saved + BOOT_TRANSFER_FLAG_BYTES, 8);
        func_13A4C0(unkDC8, (u8*)unkDC4 + 0x4E2, 0x11A6C0);
        if (unkDC4 != 0)
        {
            func_100BE0(unkDC4);
            unkDC4 = 0;
        }
    }
}

s32 BootClass170EB0::func_001E0AD0()
{
    return unkDD0;
}

s16 BootClass170EB0::func_001E0AE0()
{
    return unkDCE;
}

s16 BootClass170EB0::func_001E0AF0()
{
    s16 result = -1;
    switch (unkDC0)
    {
    case 0:
        unkDF9 = 1;
        result = func_432310(unk14, unkDCC, &unkDE4);
        if (result == -1)
        {
            unkDF8 = 0;
            unkDCE = 1;
            unk1C = 0;
            unkDCC = -1;
            unkDC0 = -1;
        }
        else if (result == 0)
        {
            unkDC0++;
        }
        break;
    case 1:
        result = func_432270(unk14, unkDCC, &unkDD0);
        if (result == 0)
        {
            break;
        }
        if (result == 1)
        {
            unkDF8 = 0;
            if (unkDD0 >= 0)
            {
                func_001E0970();
                unkDCE = 1;
                unk1C = 0;
                unkDCC = -1;
                unkDC0 = -1;
            }
            else
            {
                unkDCE = 1;
                unkDCC = -1;
                unkDC0 = -1;
                unk1C = 1;
                unkDF8 = 0;
                if (unkDF9 == 1)
                {
                    unkDF9 = 0;
                }
            }
        }
        break;
    }
    return result;
}

s32 BootClass170EB0::func_001E0C30(u16 mode, void* destination)
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
    unkDC8 = destination;
    unkDCC = mode;
    unkDD0 = -1;
    unkDC0 = 0;
    unkDF8 = 1;
    unk18 = unkDCC;
    unk1E = 0;
    if (unkDC4 == 0)
    {
        unkDC4 = func_100B00(BOOT_TRANSFER_BUFFER_SIZE, 0);
    }
    ready = prepare_transfer_request(this);
    if (!ready)
    {
        return 0;
    }
    unkDF9 = 0;
    return 1;
}

void BootClass170EB0::func_001E0DE0(u8 mode)
{
    if (mode == 1 || mode == 2)
    {
        unkD34 = mode;
        func_001E1A40(0);
    }
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", update__15BootClass170EB0Fv);

/**
 * @brief Return a mode's stored byte, or zero for an unsupported mode.
 * @param object State holding the mode values.
 * @param mode Mode 0 or 1 to query.
 * @return The stored byte, or zero when the mode is unsupported.
 */
static inline u8 state_mode_value(BootClass170EB0* object, u16 mode)
{
    if (mode != 0 && mode != 1)
    {
        return 0;
    }
    return object->unkD37[mode];
}

u16 BootClass170EB0::func_001E1410(u16 mode, u16 kind)
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
            if (!unk29)
            {
                value = 0;
            }
            else
            {
                value = unk2B;
            }
        }
        else if (mode == 1)
        {
            if (!unk2A)
            {
                value = 0;
            }
            else
            {
                value = unk2C;
            }
        }
    }
    else
    {
        value = state_mode_value(this, mode);
    }
    if (unk28)
    {
        func_001E1A40(0);
    }
    return value;
}

void BootClass170EB0::func_001E1500(u8 enabled, u16 event, u16 kind)
{
    u8 ready;
    if (enabled == 1)
    {
        if (unk18 == 1)
        {
            if (kind == 1)
            {
                func_001E17C0(event, &unk2C);
                if (unkD34 != 1)
                {
                    unk2A = 1;
                }
                if (unkD34 == 1)
                {
                    ready = 0;
                    switch (event)
                    {
                    case 16:
                        if (unk20 == 0)
                        {
                            unk2A = 1;
                            ready = 1;
                        }
                        break;
                    case 15:
                    case 5:
                    case 6:
                        unk2A = 1;
                        ready = 1;
                        break;
                    }
                    if (ready)
                    {
                        unk28 = 1;
                    }
                }
                else if (unkD34 == 2)
                {
                    switch (event)
                    {
                    case 15:
                        unkD37[1] = 15;
                        unkD35[1] = 1;
                        unk28 = 1;
                        break;
                    }
                }
            }
            else if (kind == 2)
            {
                unkD37[1] = event;
                unkD35[1] = 1;
                unk28 = 1;
            }
        }
        if (unk18 == 0)
        {
            if (kind == 1)
            {
                func_001E17C0(event, &unk2B);
                if (unkD34 == 1)
                {
                    ready = 0;
                    switch (event)
                    {
                    case 16:
                        if (unk20 == 0)
                        {
                            unk29 = 1;
                            ready = 1;
                        }
                        break;
                    case 15:
                    case 5:
                    case 6:
                        unk29 = 1;
                        ready = 1;
                        break;
                    }
                    if (ready == 1)
                    {
                        func_001E1A40(1);
                    }
                }
                else
                {
                    switch (event)
                    {
                    case 15:
                        if (unkD34 == 2)
                        {
                            unkD37[0] = 15;
                            unkD35[0] = 1;
                            func_001E1A40(1);
                        }
                        /* fall through */
                    case 2:
                    case 16:
                    case 17:
                        unk29 = 1;
                        break;
                    }
                    if (unkD34 == 1)
                    {
                        func_001E1A40(1);
                    }
                }
            }
            else if (kind == 2)
            {
                unkD37[0] = event;
                unkD35[0] = 1;
                func_001E1A40(1);
            }
        }
    }
    if (unk28 == 0)
    {
        unk1E = 0;
    }
    else
    {
        unk1E = enabled;
    }
}

void BootClass170EB0::func_001E17C0(u16 event, u8* result)
{
    s32 value;
    *result = 0;
    if (unkD34 == 1)
    {
        value = unkDFC[unk18];
        switch (event)
        {
        case 15:
            *result = 15;
            break;
        case 2:
            unkE04[unk18] = 10;
            break;
        case 16:
            if (unk20 == 0)
            {
                *result = 16;
            }
            else
            {
                unkE04[unk18] = 16;
            }
            break;
        case 17:
            unkE04[unk18] = 17;
            break;
        case 6:
            if (unkE04[unk18] == 17)
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
                *result = unkE04[unk18];
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
            if (unkE04[unk18] == 17)
            {
                *result = 17;
            }
            else
            {
                if (value < 0 || value > 8000)
                {
                    *result = 15;
                }
                *result = unkE04[unk18];
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

void BootClass170EB0::func_001E1A40(s16 mode)
{
    s32 selected = mode;
    unk18 = mode;
    unk1A = -1;
    unk1E = 0;
    unk1C = 0;
    unk2D = 0;
    if (selected == 0)
    {
        unk29 = 0;
        unk2B = 0;
        unk28 = 0;
        unk1E = 0;
        unkD37[0] = 0;
        unkD35[0] = 0;
    }
    if (selected == 1)
    {
        unk2A = 0;
        unk2C = 0;
        unkD37[1] = 0;
        unkD35[1] = 0;
    }
    if (selected == 0 || selected == 1)
    {
        unkDFC[selected] = -1;
        unkE04[selected] = -1;
    }
}

s32 BootClass170EB0::func_001E1AD0()
{
    BootModeOwner0910* owner;
    u8 ready;

    owner = new (0) BootModeOwner0910;
    unk14 = owner;
    if (unk14 == 0)
    {
        return 0;
    }
    func_432720(unk14, D_001B6614);
    func_432660(unk14, 0, 0, 0);
    func_432660(unk14, 1, 1, 0);
    unk1C = 0;
    func_001E1A40(0);
    unkDF4 = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);
    if (unkDF4 == 0)
    {
        return 0;
    }
    if (unkDC4 == 0)
    {
        unkDC4 = func_100B00(BOOT_TRANSFER_BUFFER_SIZE, 0);
    }
    ready = prepare_transfer_request(this);
    if (!ready)
    {
        return 0;
    }
    return 1;
}

/** @brief Release the transfer buffer and the memory card object, then queue this object for deletion. */
void BootClass170EB0::destroy()
{
    if (unkDC4 != 0)
    {
        func_100BE0(unkDC4);
        unkDC4 = 0;
    }

    if (unk14 != 0)
    {
        unk14->destroy();
    }

    func_11ED90(D_001B65F4, this);
}

/** @brief Clear the transfer state, both modes, and the filename. */
BootClass170EB0::BootClass170EB0()
{
    s32 index;
    unk14 = 0;
    unk1C = -1;
    unk18 = -1;
    unk1A = -1;
    unk1E = 0;
    unk20 = 0;
    unk24 = 0;
    unk28 = 0;
    func_13A678(unk6E, 0, sizeof(unk6E));
    unkD30 = (u8*)(((u32)unk6E + 0x3F) & ~0x3F);
    unk2D = 0;
    unk29 = 0;
    unkD35[0] = 0;
    unk2B = 0;
    unkD37[0] = 0;
    unk2A = 0;
    unkD35[1] = 0;
    unk2C = 0;
    unkD37[1] = 0;
    unkD34 = 1;
    unkDBC = 0;
    func_13A678(unkD39, 0, sizeof(unkD39));
    unkDBC = (u8*)(((u32)unkD39 + 0x3F) & ~0x3F);
    unkDC0 = -1;
    unkDC4 = 0;
    unkDCC = -1;
    unkDD0 = -1;
    unkDCE = -1;
    unkDC8 = 0;
    unkDF4 = 0;
    unkDF8 = 0;
    for (index = 0; index < BOOT_TRANSFER_NAME_CAPACITY; index++)
    {
        unk2E[index] = 0;
    }

    unkDF9 = 0;
    unkDFC[0] = -1;
    unkE04[0] = -1;
    unkDFC[1] = -1;
    unkE04[1] = -1;
}

/** @brief Destroy the object. */
BootClass170ED0::~BootClass170ED0()
{
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", update__15BootClass170ED0Fv);

/** @brief Clear the object's state. */
BootClass170ED0::BootClass170ED0()
{
    unk14 = 0;
    unk18 = 0;
    unk1C = 0;
    unk34 = 0;
    unk38 = 0;
}

s32 BootClass170EF0::get_default_list_kind()
{
    return 4;
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001E3FF0);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001E4610);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001E4760);

/** @brief Load the selected option's current value from the settings. */
void BootClass170EF0::func_001E4B50()
{
    BootResource0970* settings = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);
    switch (unk68)
    {
    case 0:
        if (settings->widescreen != 0)
        {
            unk6A = 1;
        }
        else
        {
            unk6A = 0;
        }
        break;
    case 1:
        switch (D_001B65F8->unk450)
        {
        case 1:
            unk6A = 0;
            break;
        case 0:
            unk6A = 1;
            break;
        case 2:
            unk6A = 2;
            break;
        case 3:
            unk6A = 3;
            break;
        }
        break;
    case 2:
        unk6A = !settings->unk24_bit7;
        break;
    case 3:
        unk6A = settings->unk25_mode;
        break;
    case 4:
        unk6A = !settings->unk24_bit5;
        break;
    case 5:
        unk6A = settings_value(settings);
        break;
    }
}

/** @brief Apply the selected option's value to the settings and the hardware. */
void BootClass170EF0::func_001E4CE0()
{
    BootResource0970* settings = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);
    switch (unk68)
    {
    case 0:
        switch (unk6A)
        {
        case 0:
            settings->widescreen = 0;
            D_001B6654->unk278 = (1.3333334f * (1.0714285f * (float)D_205E10.unk04->unk3C6E)) / (float)D_205E10.unk04->unk3C6C;
            D_001B6654->unk25C = 1.5707964f;
            D_205E10.func_001EACD0();
            break;
        case 1:
            settings->widescreen = 1;
            D_001B6654->unk278 =
                (1.7777778f * ((1.3333334f * (1.0714285f * (float)D_205E10.unk04->unk3C6E)) / (float)D_205E10.unk04->unk3C6C)) /
                1.3333334f;
            D_001B6654->unk25C = 1.8325958f;
            D_205E10.func_001EACD0();
            break;
        }
        break;
    case 1:
        switch (unk6A)
        {
        case 0:
            func_10DA70(D_001B65F8, 1);
            settings->unk18E = 0;
            break;
        case 1:
            func_10DA70(D_001B65F8, 0);
            settings->unk18E = 1;
            break;
        case 2:
            func_10DA70(D_001B65F8, 2);
            settings->unk18E = 2;
            break;
        case 3:
            func_10DA70(D_001B65F8, 3);
            settings->unk18E = 3;
            break;
        }
        break;
    case 2:
        switch (unk6A)
        {
        case 0:
            settings->unk24_bit7 = 1;
            break;
        case 1:
            settings->unk24_bit7 = 0;
            break;
        }
        break;
    case 3:
        settings->unk25_mode = unk6A;
        break;
    case 4:
        switch (unk6A)
        {
        case 0:
            settings->unk24_bit5 = 1;
            func_11E030(D_001B65F0, 0, 1);
            func_11E210(D_001B65F0, 0, 1, 0x40);
            unk7C = 10;
            break;
        case 1:
            settings->unk24_bit5 = 0;
            func_11E030(D_001B65F0, 0, 0);
            break;
        }
        break;
    case 5:
        settings_set_value(settings, unk6A);
        break;
    }
}

/**
 * @brief Select the message describing the selected option's value.
 * @return Message key, or zero for an unknown option.
 */
s32 BootClass170EF0::func_001E5090()
{
    BootResource0970* settings = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);
    switch (unk68)
    {
    case 0:
        return unk6A + 10;
    case 1:
        if (unk6A == 3)
        {
            return 27;
        }
        return unk6A + 12;
    case 2:
        return unk6A + 16;
    case 3:
        if (unk6A == 3)
        {
            return 28;
        }
        return unk6A + 18;
    case 4:
        return unk6A + 21;
    case 5:
        if (unk6A == 3)
        {
            if (settings_extra_1a2(settings))
            {
                return 0x51;
            }
            return 0x50;
        }

        if (settings_extra_1a1(settings) && unk6A == 2)
        {
            return 0x1A;
        }
        return unk6A + 23;
    }
    return 0;
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001E5250);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001E5510);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001E63B0);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", update__15BootClass170EF0Fv);

/** @brief Release the menu's buffers and owned objects. */
BootClass170EF0::~BootClass170EF0()
{
    delete unk14;
    delete unk2C;
    for (s32 i = 0; i < 5; i++)
    {
        delete unk18[i];
    }

    for (s32 i = 0; i < 8; i++)
    {
        delete unk30[i];
    }

    for (s32 i = 0; i < 21; i++)
    {
        if (unk84[i] != 0)
        {
            lib_object_detach_owner(unk84[i]);
            unk84[i]->destroy();
        }
    }

    for (s32 i = 0; i < 10; i++)
    {
        if (unkE0[i] != 0)
        {
            lib_object_detach_owner(unkE0[i]);
            unkE0[i]->destroy();
        }
    }

    for (s32 i = 0; i < 6; i++)
    {
        if (unk108[i] != 0)
        {
            unk108[i]->destroy();
        }

        if (unk120[i] != 0)
        {
            unk120[i]->destroy();
        }
    }

    if (unkD8 != 0)
    {
        unkD8->destroy();
    }

    if (unkDC != 0)
    {
        unkDC->destroy();
    }

    if (unk13C != 0)
    {
        unk13C->destroy();
    }

    if (unk140 != 0)
    {
        unk140->destroy();
    }

    if (unk144 != 0)
    {
        unk144->destroy();
    }

    if (unk7C != 0)
    {
        func_11E210(D_001B65F0, 0, 0, 0);
    }

    D_001B65AC = 0;
}

/** @brief Load the menu's resources and clear its owned objects. */
BootClass170EF0::BootClass170EF0()
{
    BootResource0970* resource;
    unk14 = func_139700(0x40, func_11C8C0(D_001B65E4, 0x28));
    func_103E70(D_001B65E8, 0x28, unk14, 1, 0x34BC0, 0, 0, 0, 1);
    unk2C = func_139700(0x40, func_11C8C0(D_001B65E4, 0x29));
    unk50 = 0;
    for (s32 i = 0; i < 5; i++)
    {
        unk18[i] = 0;
    }

    for (s32 i = 0; i < 21; i++)
    {
        unk84[i] = 0;
    }

    for (s32 i = 0; i < 8; i++)
    {
        unk30[i] = 0;
    }

    for (s32 i = 0; i < 6; i++)
    {
        unk108[i] = 0;
        unk120[i] = 0;
    }

    for (s32 i = 0; i < 10; i++)
    {
        unkE0[i] = 0;
    }

    unk13C = 0;
    unk140 = 0;
    unk144 = 0;
    unkD8 = 0;
    unkDC = 0;
    unk6D = 0;
    unk7C = 0;
    D_001B65AC = &unk138;
    unk68 = 0;
    unk6E = 0;
    resource = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);
    switch (D_001B65F8->unk450)
    {
    case 1:
        resource->unk18E = 0;
        break;
    case 0:
        resource->unk18E = 1;
        break;
    case 2:
        resource->unk18E = 2;
        break;
    case 3:
        resource->unk18E = 3;
        break;
    }
}

/**
 * @brief Negate the matrix's second vector, then apply the matrix through the Lib model.
 * @param matrix Matrix supplied by the caller.
 * @param context Opaque caller context.
 */
void BootClass170F30::func_001E08C0(const void* matrix, void* context)
{
    BootMatrix92D0 negated;
    BootVector4DDAA0* vector1 = &negated.vectors[1];
    BootVector4DDAA0* vector2 = &negated.vectors[2];
    BootVector4DDAA0* vector3 = &negated.vectors[3];
    copy_vector(&negated.vectors[0], &unk90.vectors[0]);
    copy_vector(vector1, &unk90.vectors[1]);
    copy_vector(vector2, &unk90.vectors[2]);
    copy_vector(vector3, &unk90.vectors[3]);
    vector1->x *= -1.0f;
    vector1->y *= -1.0f;
    vector1->z *= -1.0f;
    vector1->w *= -1.0f;
    copy_vector(&unk90.vectors[0], &negated.vectors[0]);
    copy_vector(&unk90.vectors[1], vector1);
    copy_vector(&unk90.vectors[2], vector2);
    copy_vector(&unk90.vectors[3], vector3);
    transform_dirty = 1;
    BootClass177820::func_001E08C0(matrix, context);
}

/** @brief Destroy the model object. */
BootClass170F30::~BootClass170F30()
{
}

s32 BootClass171030::func_001E9640()
{
    return 0;
}

void BootClass171030::func_001E9650()
{
    unk20 = 0;
    unk24 = 0;
    unk28 = 0;
    unk2C = 0;
    unk30 = 0;
    unk34 = 0;
}

void BootClass171030::update()
{
    BootClass170EB0* state;
    u16 first;
    u16 second;
    u16 third;
    u16 fourth;
    u16 flags;
    unk16 = func_11E010(D_001B65F0, 0);
    unk18 = func_11DFF0(D_001B65F0, 0);
    unk1A = func_11E000(D_001B65F0, 0);
    unk1C = func_11DFB0(D_001B65F0, 0);
    func_11DF90(D_001B65F0, 0);
    state = D_205E10.unk24;
    if (unk14 != 0)
    {
        first = state->func_001E1410(0, 1);
        second = state->func_001E1410(1, 1);
        third = state->func_001E1410(0, 2);
        fourth = state->func_001E1410(1, 2);
        flags = state->func_001E0910();
        if (first != 0)
        {
            unk20 = first;
        }
        if (second != 0)
        {
            unk24 = second;
        }
        if (third != 0)
        {
            unk28 = third;
        }
        if (fourth != 0)
        {
            unk2C = fourth;
        }
        if (flags & 1)
        {
            unk30 = 1;
        }
        else
        {
            unk30 = 0;
        }
        if (flags & 2)
        {
            unk34 = 1;
        }
        else
        {
            unk34 = 0;
        }
    }
}

/** @brief Clear the retained values and enable the memory card query. */
BootClass171030::BootClass171030()
{
    unk20 = 0;
    unk24 = 0;
    unk28 = 0;
    unk2C = 0;
    unk30 = 0;
    unk34 = 0;
    unk14 = 1;
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", update__15BootClass171050Fv);

/** @brief Release the owned objects. */
BootClass171050::~BootClass171050()
{
    if (unk2C != 0)
    {
        unk2C->destroy();
    }

    if (unk30 != 0)
    {
        unk30->destroy();
    }

    if (unk34 != 0)
    {
        unk34->destroy();
    }

    if (unk28 != 0)
    {
        unk28->destroy();
    }

    delete unk24;
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", __ct__15BootClass171050Fv);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", update__15BootClass171070Fv);

/** @brief Destroy the object. */
BootClass171070::~BootClass171070()
{
}

/** @brief Release the owned objects, then queue this object for deletion. */
void BootClass171070::destroy()
{
    if (unk24 != 0)
    {
        unk24->destroy();
        unk24 = 0;
    }

    if (unk20 != 0)
    {
        unk20->destroy();
        unk20 = 0;
    }

    if (unk1C != 0)
    {
        unk1C->destroy();
        unk1C = 0;
    }

    func_11ED90(D_001B65F4, this);
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001EAA40);

/**
 * @brief Copy the owner's stored pointer into the resident context.
 * @param object Owner containing the pointer to bind.
 */
void BootClass1710B0::func_001EACC0()
{
    D_001B6628->unk90 = unk08;
}

/**
 * @brief Update projection parameters using the resource mode and stored dimensions.
 * @param object Owner containing the projection object to update.
 */
void BootClass1710B0::func_001EACD0()
{
    BootResource0970* resource = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);
    BootDimensionsACD0* dimensions;
    if (resource->widescreen != 0)
    {
        dimensions = D_205E10.unk04;
        unk08->unk278 =
            (1.7777778f * ((1.3333334f * (1.0714285f * (float)dimensions->unk3C6E)) /
                (float)dimensions->unk3C6C)) / 1.3333334f;
        unk08->unk250 = 0.75f;
        dimensions = D_205E10.unk04;
        D_001B6654->unk278 =
            (1.7777778f * ((1.3333334f * (1.0714285f * (float)dimensions->unk3C6E)) /
                (float)dimensions->unk3C6C)) / 1.3333334f;
        D_001B6654->unk25C = 1.8325958f;
    }
    else
    {
        dimensions = D_205E10.unk04;
        unk08->unk278 =
            (1.3333334f * (1.0714285f * (float)dimensions->unk3C6E)) /
                (float)dimensions->unk3C6C;
        unk08->unk250 = 1.0f;
        dimensions = D_205E10.unk04;
        D_001B6654->unk278 =
            (1.3333334f * (1.0714285f * (float)dimensions->unk3C6E)) /
                (float)dimensions->unk3C6C;
        D_001B6654->unk25C = 1.5707964f;
    }
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001EAE80);

/** @brief Decode the next of the program's three resource blocks, then destroy this object after the last. */
void BootClass171090::update()
{
    u8* buffer;
    u8* aligned;
    if (func_102D00(D_001B65E8) != 0)
    {
        if (block >= 3)
        {
            func_100BE0(data);
            lib_object_detach_owner(this);
            destroy();
            return;
        }

        buffer = func_102920(D_001B65EC, data, block, 1);
        aligned = (u8*)(((u32)buffer + 0x7F) & ~0x7F);
        func_1025A0(D_001B65EC, data, aligned, block);
        switch (block)
        {
        case 0:
            program->unk10 = buffer;
            program->messages = func_4656B0(D_001B657C, aligned);
            break;
        case 1:
            program->unk18 = buffer;
            program->unk1C = func_4656B0(D_001B657C, aligned);
            break;
        case 2:
            program->unk20 = buffer;
            break;
        }

        block++;
    }
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001EB210);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", run__15BootClass1710B0Fv);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001EBCF0);

/** @brief Release the program's objects, resources, and buffers. */
BootClass1710B0::~BootClass1710B0()
{
    if (input != 0)
    {
        lib_object_detach_owner(input);
        input->destroy();
    }

    if (unk24 != 0)
    {
        unk24->destroy();
    }

    if (unk08 != 0)
    {
        unk08->destroy();
    }

    delete unk10;
    delete unk18;
    delete unk20;
    delete unk40;
}

/** @brief Destroy the object. */
BootClass171090::~BootClass171090()
{
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001EC010);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001EC2E0);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001EC360);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001EC3C0);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001EC430);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001EC490);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001EC630);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001EC910);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001EC990);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001EC9F0);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001ECA60);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001ECAC0);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001ECC60);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001ECF30);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001ECFA0);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001ED000);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001ED060);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001E0900", func_001ED200);
